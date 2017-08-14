#include "DataPlot.h"
#include "K_means.h"

namespace test
{
	void opencvConfig()
	{
		Mat src = imread("C:\\Users\\dell\\Pictures\\me.jpg");

		imshow("src", src);
		printf("OpenCV version: %s\n", CV_VERSION);

		waitKey();
	}

	void showCoordinate()
	{
		vector<float> X = {	20, 1250.0 };
		vector<float> Y = {	20, 1250.0 };

		DataPlot::plot(X, Y);
	}

	void showDataGenerate()
	{
		K_means km;
		vector<Point2f> raw;
		km.generatePoints(raw, 50);

		DataPlot::plot(raw, Scalar(100, 100, 255));
	}

	void kMeans()
	{
		vector<Point2f> raw;
		K_means km;
		km.generatePoints(raw, 25);
		DataPlot::plot(raw, Scalar(100, 0, 100));
		vector<DataSet> result;
		km.compute(raw, result);
		DataPlot::plot(result);
	}
}

int main()
{
	//test::opencvConfig();
	//test::showCoordinate();
	//test::showDataGenerate();
	test::kMeans();

	return 0;
}