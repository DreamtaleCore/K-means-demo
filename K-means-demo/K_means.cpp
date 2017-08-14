#include "K_means.h"



K_means::K_means()
{
}


K_means::~K_means()
{
}

void K_means::generatePoints(vector<Point2f>& data, int sum, float data_min, float data_max)
{
	RNG rng;
	for (int i = 0; i < sum; i++)
	{
		data.push_back(Point2f(
			rng.uniform(data_min, data_max), 
			rng.uniform(data_min, data_max)
			));
	}
}

void K_means::loadPoints(vector<Point2f>& data, string filename)
{
	fstream file;
	file.open(filename, ios::in);
	if (file.is_open())
	{
		while (!file.eof())
		{
			char buf[128];
			file.getline(buf, 128);
			stringstream ss(buf);
			Point2f d;
			ss >> d.x >> d.y;
			data.push_back(d);
		}
		file.close();
	}
	else
	{
		cout << "Load failed, because: the file: " << filename << " does NOT exist." << endl;
	}
}

void K_means::compute(vector<Point2f> data, vector<DataSet>& result)
{
	// bounder consideration
	if (data.size() < 2)
	{
		DataSet ds;
		ds.data = data;
		if (data.size() > 0)
		{
			ds.center = data[0];
			ds.bounder = RotatedRect(data[0], Size2f(30, 30), 0);
			result.push_back(ds);
		}
	}

	float threshold = 1e-2;
	int class_num = 1;
	float last_error = 1e8;
	float x_min, x_max, y_min, y_max;
	// find the random range
	x_min = x_max = data[0].x;
	y_min = y_max = data[0].y;
	for (auto p : data)
	{
		x_min = x_min < p.x ? x_min : p.x;
		x_max = x_max > p.x ? x_max : p.x;
		y_min = y_min < p.y ? y_min : p.y;
		y_max = y_max > p.y ? y_max : p.y;
	}
	RNG rng;
	while (class_num++)
	{
		// step1: init class_num points randomly
		cout << "Trying the " << class_num << " clusters..." << endl;
		vector<DataSet> tmp_rlt;
		for (int i = 0; i < class_num; i++)
		{
			DataSet ds;
			ds.center = Point2f(rng.uniform(x_min, x_max), rng.uniform(y_min, y_max));
			tmp_rlt.push_back(ds);
		}
		// just do below until convergence
		while (true)
		{
			// step2: class all data into the class_num teams
			for (auto p : data)
			{
				int index = 0;
				float min_distance = 1e8;
				for (int i = 0; i < class_num; i++)
				{
					float cur_distance = norm(p - tmp_rlt[i].center);
					if (min_distance > cur_distance)
					{
						min_distance = cur_distance;
						index = i;
					}
				}
				tmp_rlt[index].data.push_back(p);
			}
			// step3: update the center point into mean-data-points
			float move_distance = 0.0;
			for (int i = 0; i < class_num; i++)
			{
				Point2f mean = Point2f(0.0, 0.0);
				for (auto elem : tmp_rlt[i].data)
				{
					mean = mean + elem;
				}
				if (tmp_rlt[i].data.size() > 0)
				{
					mean = mean / (float)tmp_rlt[i].data.size();
					tmp_rlt[i].center = mean;
				}
				move_distance = move_distance + norm(mean - tmp_rlt[i].center);
			}
			// if convergence, break
			if (move_distance < threshold)
			{
				break;
			}
		}
		// step4: compute the class error
		float error_sum = 0.0;
		for (int i = 0; i < class_num; i++)
		{
			for (auto p : tmp_rlt[i].data)
			{
				error_sum = error_sum + norm(p - tmp_rlt[i].center);
			}
		}
		cout << "In the " << class_num << " clusters, total error sum is: " << error_sum << endl;
		if (error_sum > last_error || class_num > 5)
		{
			cout << "I find the best cluster number: " << class_num << " returning" << endl;
			result = tmp_rlt;
			// step5: find the bounder of cluster
			// TODO: update the function of finding bounders
			for (auto& elem : result)
			{
				// just for test
				elem.bounder = RotatedRect(elem.center, Size(50, 50), 0);
			}
			break;
		}
	}
}
