#include "DataPlot.h"



DataPlot::DataPlot()
{
}


DataPlot::~DataPlot()
{
}

void DataPlot::plot(vector<float> X, vector<float> Y, Scalar color, string pattern)
{
	// canvas elements
	float bounder = 20;
	float cw = 800, ch = 800;
	Mat canvas = Mat(cw + 2 * bounder, ch + 2 * bounder, CV_8UC3, Scalar(255, 255, 255));
	// points properties
	float x_max = *std::max_element(X.begin(), X.end());
	float x_min = *std::min_element(X.begin(), X.end());
	float y_max = *std::max_element(Y.begin(), Y.end());
	float y_min = *std::min_element(Y.begin(), Y.end());
	// step1: compute the origin point's position
	Point2f origin;
	origin.x = x_min >= 0 ? 0 : x_max <= 0 ? cw : cw / 2;
	origin.y = y_min >= 0 ? ch : y_max <= 0 ? 0 : cw / 2;
	// step2: compute the map ratio
	int ratio_x_max = (int)abs(x_max - origin.x) / (int)cw + 1;
	int ratio_x_min = (int)abs(x_min - origin.x) / (int)cw + 1;
	int ratio_y_max = (int)abs(y_max - origin.y) / (int)ch + 1;
	int ratio_y_min = (int)abs(y_min - origin.y) / (int)ch + 1;
	int ratio = std::max(ratio_x_max, std::max(ratio_x_min, std::max(ratio_y_min, ratio_y_max)));
	// step3: draw the x and y axises, origin point and ruler number
	line(canvas, Point2f(bounder, origin.y + bounder), Point2f(bounder + cw, origin.y + bounder), Scalar(0), 2);
	line(canvas, Point2f(bounder + cw, origin.y + bounder), Point2f(bounder + cw - 6, origin.y + bounder - 3), Scalar(0), 2);
	line(canvas, Point2f(bounder + cw, origin.y + bounder), Point2f(bounder + cw - 6, origin.y + bounder + 3), Scalar(0), 2);
	line(canvas, Point2f(bounder + origin.x, bounder + ch), Point2f(bounder + origin.x, bounder), Scalar(0), 2);
	line(canvas, Point2f(bounder + origin.x, bounder), Point2f(bounder + origin.x - 3, bounder + 6), Scalar(0), 2);
	line(canvas, Point2f(bounder + origin.x, bounder), Point2f(bounder + origin.x + 3, bounder + 6), Scalar(0), 2);
	putText(canvas, "O", origin + Point2f(bounder + 2, bounder - 2), CV_FONT_HERSHEY_PLAIN, 1, Scalar(255));
	putText(canvas, "X", Point2f(bounder + cw, bounder + origin.y), CV_FONT_HERSHEY_PLAIN, 1, Scalar(255));
	putText(canvas, to_string((int)cw * ratio), Point2f(bounder + cw - 10 - 2.5*to_string((int)cw * ratio).length(), bounder + origin.y + 10 + 2), CV_FONT_HERSHEY_PLAIN, 1, Scalar(255));
	putText(canvas, "Y", Point2f(bounder + origin.x, bounder), CV_FONT_HERSHEY_PLAIN, 1, Scalar(255));
	putText(canvas, to_string((int)ch * ratio), Point2f(bounder + origin.x + 2, bounder + 10 + 2), CV_FONT_HERSHEY_PLAIN, 1, Scalar(255));

	// step3: show the points
	int sum = X.size() < Y.size() ? X.size() : Y.size();
	for (int i = 0; i < sum; i++)
	{
		circle(canvas, Point2f(bounder + (X[i] / (float)ratio - origin.x), bounder + (origin.y - Y[i] / (float)ratio)), 2, color, 2);
	}
	// step4: show the result
	imshow("figure", canvas);
	waitKey();
}

void DataPlot::plot(vector<Point2f> points, Scalar color, string pattern)
{
	vector<float> X, Y;
	for each (Point2f p in points)
	{
		X.push_back(p.x);
		Y.push_back(p.y);
	}
	plot(X, Y, color, pattern);
	X.clear();
	Y.clear();
}

void DataPlot::plot(vector<DataSet> points)
{
	// canvas elements
	float bounder = 20;
	float cw = 800, ch = 800;
	Mat canvas = Mat(cw + 2 * bounder, ch + 2 * bounder, CV_8UC3, Scalar(255, 255, 255));
	// points properties
	vector<float> X, Y;
	for (auto p : points)
	{
		for (auto d : p.data) 
		{
			X.push_back(d.x);
			Y.push_back(d.y);
		}
	}
	float x_max = *std::max_element(X.begin(), X.end());
	float x_min = *std::min_element(X.begin(), X.end());
	float y_max = *std::max_element(Y.begin(), Y.end());
	float y_min = *std::min_element(Y.begin(), Y.end());
	// step1: compute the origin point's position
	Point2f origin;
	origin.x = x_min >= 0 ? 0 : x_max <= 0 ? cw : cw / 2;
	origin.y = y_min >= 0 ? ch : y_max <= 0 ? 0 : cw / 2;
	// step2: compute the map ratio
	int ratio_x_max = (int)abs(x_max - origin.x) / (int)cw + 1;
	int ratio_x_min = (int)abs(x_min - origin.x) / (int)cw + 1;
	int ratio_y_max = (int)abs(y_max - origin.y) / (int)ch + 1;
	int ratio_y_min = (int)abs(y_min - origin.y) / (int)ch + 1;
	int ratio = std::max(ratio_x_max, std::max(ratio_x_min, std::max(ratio_y_min, ratio_y_max)));
	// step3: draw the x and y axises, origin point and ruler number
	line(canvas, Point2f(bounder, origin.y + bounder), Point2f(bounder + cw, origin.y + bounder), Scalar(0), 2);
	line(canvas, Point2f(bounder + cw, origin.y + bounder), Point2f(bounder + cw - 6, origin.y + bounder - 3), Scalar(0), 2);
	line(canvas, Point2f(bounder + cw, origin.y + bounder), Point2f(bounder + cw - 6, origin.y + bounder + 3), Scalar(0), 2);
	line(canvas, Point2f(bounder + origin.x, bounder + ch), Point2f(bounder + origin.x, bounder), Scalar(0), 2);
	line(canvas, Point2f(bounder + origin.x, bounder), Point2f(bounder + origin.x - 3, bounder + 6), Scalar(0), 2);
	line(canvas, Point2f(bounder + origin.x, bounder), Point2f(bounder + origin.x + 3, bounder + 6), Scalar(0), 2);
	putText(canvas, "O", origin + Point2f(bounder + 2, bounder - 2), CV_FONT_HERSHEY_PLAIN, 1, Scalar(255));
	putText(canvas, "X", Point2f(bounder + cw, bounder + origin.y), CV_FONT_HERSHEY_PLAIN, 1, Scalar(255));
	putText(canvas, to_string((int)cw * ratio), Point2f(bounder + cw - 10 - 2.5*to_string((int)cw * ratio).length(), bounder + origin.y + 10 + 2), CV_FONT_HERSHEY_PLAIN, 1, Scalar(255));
	putText(canvas, "Y", Point2f(bounder + origin.x, bounder), CV_FONT_HERSHEY_PLAIN, 1, Scalar(255));
	putText(canvas, to_string((int)ch * ratio), Point2f(bounder + origin.x + 2, bounder + 10 + 2), CV_FONT_HERSHEY_PLAIN, 1, Scalar(255));

	// step3: show the points
	RNG rng;
	for (auto p : points)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		for (auto d : p.data)
		{
			circle(canvas, Point2f(bounder + (d.x / (float)ratio - origin.x), bounder + (origin.y - d.y / (float)ratio)), 2, color, 2);
		}
		// draw the bounder ellipse
		RotatedRect rr;
		rr.center = Point2f(bounder + (p.bounder.center.x / (float)ratio - origin.x), bounder + (origin.y - p.bounder.center.y / (float)ratio));
		rr.size = p.bounder.size;
		rr.angle = p.bounder.angle;
		ellipse(canvas, rr, color);
	}

	// step4: show the result
	imshow("figure", canvas);
	waitKey();
}


