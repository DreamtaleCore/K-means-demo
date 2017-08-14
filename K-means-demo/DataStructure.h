#pragma once
#include "GeneralHeader.h"

struct DataSet
{
	vector<Point2f> data;
	Point2f center;
	RotatedRect bounder;
};