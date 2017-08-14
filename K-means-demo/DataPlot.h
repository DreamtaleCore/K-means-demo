#pragma once
#include "GeneralHeader.h"
#include "DataStructure.h"

class DataPlot
{
public:
	DataPlot();
	~DataPlot();

	static void plot(vector<float> X, vector<float> Y, Scalar color = Scalar(0), string pattern = "o");
	static void plot(vector<Point2f> points, Scalar color = Scalar(0), string pattern = "o");
	static void plot(vector<DataSet> points);
};

