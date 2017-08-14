#pragma once
#include "DataStructure.h"

class K_means
{
public:
	K_means();
	~K_means();

	void generatePoints(vector<Point2f>& data, int sum, float data_min = 0, float data_max = 800);
	void loadPoints(vector<Point2f>& data, string filename);
	void compute(vector<Point2f> data, vector<DataSet>& result);
};

