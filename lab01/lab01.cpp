#include <opencv2/opencv.hpp>
#include <time.h>

using namespace cv;

int main() {
	int height(60);
	int width(256*3);
	clock_t start(0), end(0);
	double time(0.0);

	Mat I_1(height, width, CV_32F);
	for (int i(0); i < width; i+=3) {
		line(I_1, Point(i, 0), Point(i, height), (Scalar(i / 3, i / 3, i / 3))/255, 3);
	}

	start = clock();
	Mat G_1(height, width, CV_32F);
	pow(I_1, 2.3, G_1);
	end = clock();
	time = (end - start) / (double) CLOCKS_PER_SEC;
	std::cout << "time G_1: " << time;

	start = clock();
	Mat G_2(height, width, CV_32F);
	for (int i(0); i < height; ++i) {
		for (int j(0); j < width; ++j) {
			G_2.at<float>(i, j) = pow(I_1.at<float>(i, j), 2.3);
		}
	}
	end = clock();
	time = (end - start) / (double)CLOCKS_PER_SEC;
	std::cout << "\ntime G_2: " << time;

	Mat result(height * 3 + 2, width, CV_8U);
	result = 0;
	(I_1 *= 255).copyTo(result(Rect(0, 0, width, height)));
	(G_1 *= 255).copyTo(result(Rect(0, height + 1, width, height)));
	(G_2 *= 255).copyTo(result(Rect(0, 2 * (height + 1), width, height)));

	imwrite("C:/courses/opencv/lobova_m_o/prj.labs/lab01/lab01.png", result);
	imshow("Result", result);
	waitKey(0);
	return 0;
}