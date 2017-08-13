#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	Mat src = imread("C:\\Users\\dell\\Pictures\\me.jpg");

	imshow("src", src);


	waitKey();

	return 0;
}