#include <opencv2/core/core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

#include <math.h>
#include <iostream>

#define match 0.1

using namespace std;
using namespace cv;


int main()
{
	VideoCapture cap("Boom.mp4"); 
	if (!cap.isOpened())  
		return -1;
	namedWindow("frame", 1);

	int lowerC = 100, upperC = 255 ;
	createTrackbar("LowerC", "frame", &lowerC, 255, NULL);
	createTrackbar("UpperC", "frame", &upperC, 255, NULL);
	
	vector<Vec4i> hierarchy;
	std::vector < std::vector < cv::Point > >contours; 

	while(1)
	{
		Mat frame;
		cap  >> frame; 
		if (frame.empty()) break;

		Mat frame_copy(frame.rows, frame.cols, CV_8UC1);

		cvtColor(frame, frame_copy, CV_BGR2GRAY);
		Mat range;
		inRange(frame_copy, Scalar(0, 0, 0), Scalar(179, 255, 255), range);
		erode(range, range, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)));
		dilate(range, range, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)));
		

		Canny(range, range, 100, 200, 3);
		imshow("Range", range);
		waitKey(0);
		
		Mat image = range.clone();
		findContours(image, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));

		if (contours.empty()) continue;

		vector<Moments> mu(contours.size());
		for (size_t i = 0; i < contours.size(); i++)
		{
			mu[i] = moments(contours[i], false);
		}

		vector<Point2f> mc(contours.size());
		for (size_t i = 0; i < contours.size(); i++)
		{
			mc[i] = Point2f(static_cast<float>(mu[i].m10 / mu[i].m00), static_cast<float>(mu[i].m01 / mu[i].m00));
		}

		Mat drawing = frame.clone();
		for (int i = 0; i< contours.size(); i++)
		{
			drawContours(drawing, contours, (int)i, Scalar(255, 255, 255), 2, 8, hierarchy, 0, Point());
			circle(drawing, mc[i], 4, Scalar(0, 0, 255), -1, 8, 0);
		}

		char c = (char)waitKey(1);
		if (c == 27) waitKey(0);

		imshow("frame", range);
		if (waitKey(33) >= 0) break;
	}
	destroyAllWindows();
	return 0;

	//Задание №1
	//
	///*Mat img = imread("ig_0.jpg");
	//Mat img1 = imread("ig_1.jpg");
	//Mat img2 = imread("ig_2.jpg");

	//cvtColor(img, img, CV_BGR2GRAY);
	//cvtColor(img1, img1, CV_BGR2GRAY);
	//cvtColor(img2, img2, CV_BGR2GRAY);

	//blur(img, img, Size(3, 3));
	//blur(img1, img1, Size(3, 3));
	//blur(img2, img2, Size(3, 3));

	//threshold(img, img, 220, 255, THRESH_BINARY);
	//threshold(img1, img1, 220, 255, THRESH_BINARY);
	//threshold(img2, img2, 230, 255, THRESH_BINARY);

	//imshow("ig0", img);
	//imshow("ig1", img1);
	//imshow("ig2", img2);
	//waitKey(0);

	//Mat img_clone = img1, canny_output;
	//Mat img_clone1 = img1, canny_output1;
	//Mat img_clone2 = img2, canny_output2;

	//vector<Vec4i> hierarchy;
	//vector<vector<Point>> contours;
	//	
	//findContours(img_clone, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	//vector<Moments> mu(contours.size());
	//for (size_t i = 0; i < contours.size(); i++)
	//{
	//	mu[i] = moments(contours[i], false);
	//}
	//vector<Point2f> mc(contours.size());
	//for (size_t i = 0; i < contours.size(); i++)
	//{
	//	mc[i] = Point2f(static_cast<float>(mu[i].m10 / mu[i].m00), static_cast<float>(mu[i].m01 / mu[i].m00));
	//}
	//	
	//Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
	//for (int i = 0; i< contours.size(); i++)
	//{
	//	drawContours(drawing, contours, (int)i, Scalar(255,255,255), 2, 8, hierarchy, 0, Point());
	//	circle(drawing, mc[i], 4, Scalar(0,0,255), -1, 8, 0);
	//}

	//
	//	
	//imshow("drawing0", drawing);
	//waitKey(0);*/


	//Задание №2

	/*Mat bgrimg = imread("helicopter.jpg"), hsvimg;
	cvtColor(bgrimg, hsvimg, CV_BGR2HSV);
	
	Mat range;
	inRange(hsvimg, Scalar(20, 100, 100), Scalar(80, 255, 255), range);
	
	Mat img_clone = range, canny_output;
	vector<Vec4i> hierarchy;
	vector<vector<Point>> contours;

	Canny(img_clone, canny_output, 100, 255 * 2, 3);
	findContours(img_clone, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	vector<Moments> mu(contours.size());
	for (size_t i = 0; i < contours.size(); i++)
	{
		mu[i] = moments(contours[i], false);
	}
	vector<Point2f> mc(contours.size());
	for (size_t i = 0; i < contours.size(); i++)
	{
		mc[i] = Point2f(static_cast<float>(mu[i].m10 / mu[i].m00), static_cast<float>(mu[i].m01 / mu[i].m00));
	}

	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
	for (int i = 0; i< contours.size(); i++)
	{
		drawContours(drawing, contours, (int)i, Scalar(255, 255, 255), 2, 8, hierarchy, 0, Point());
		circle(drawing, mc[i], 4, Scalar(0, 0, 255), -1, 8, 0);
	}

	imshow("drawing0", drawing);
	imshow("helicopter", bgrimg);
	waitKey(0);*/

	//Задание №4

	/*Mat keys = imread("gk.jpg");
	Mat example = imread("gk_tmplt.jpg");
	Mat gk, gk_tmplt;

	cvtColor(keys, gk, CV_BGR2HSV);
	cvtColor(example, gk_tmplt, CV_BGR2HSV);

	inRange(gk, Scalar(0, 0, 0), Scalar(189, 255, 253), gk);

	erode(gk, gk, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)));
	dilate(gk, gk, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)));
	erode(gk_tmplt, gk_tmplt, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)));
	dilate(gk_tmplt, gk_tmplt, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)));

	vector<vector<Point> > contours_key;
	vector<Vec4i> hierarchy_key;
	Mat canny_output_key;


	Canny(gk, canny_output_key, 100, 255 * 2, 3);
	findContours(canny_output_key, contours_key, hierarchy_key, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	vector<vector<Point> > contours_example;
	vector<Vec4i> hierarchy_example;
	Mat canny_output_example;
	
	Canny(gk_tmplt, canny_output_example, 100, 255 * 2, 3);
	findContours(canny_output_example, contours_example, hierarchy_example, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	Mat drawing = keys.clone();

	for (int i = 0; i < contours_key.size(); i++)
	{
		double result = matchShapes(contours_key[i], contours_example[0], CV_CONTOURS_MATCH_I2, 0);
		if (result < match) 
		{
			drawContours(drawing, contours_key, i, Scalar(0, 0, 255), 2, 8, hierarchy_key, 0, Point());
		}
	}
	imshow("Right_keys", drawing);
	waitKey(0);*/

	//Задание №3

	/*Mat img = imread("robot.jpg"), back;
	cvtColor(img, back, CV_BGR2HSV);

	Mat blue, green, red_light, red_dark;
	inRange(back, Scalar(78, 45, 76), Scalar(160, 255, 255), blue);
	inRange(back, Scalar(66, 44, 110), Scalar(80, 180, 255), green);
	inRange(back, Scalar(0, 75, 48), Scalar(10, 255, 255), red_dark);
	inRange(back, Scalar(160, 70, 55), Scalar(185, 255, 255), red_light);

	Mat red = red_light | red_dark;

	Mat lamp;
	inRange(back, Scalar(0, 0, 250, 0), Scalar(178, 10, 255, 0), lamp);

	erode(red, red, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)));
	dilate(red, red, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)));
	erode(green, green, getStructuringElement(MORPH_ELLIPSE, Size(6, 6)));
	dilate(green, green, getStructuringElement(MORPH_ELLIPSE, Size(6, 6)));
	
	vector<vector<Point> > contours_red, contours_green, contours_blue, contours_lamp;
	vector<Vec4i> hierarchy_red, hierarchy_green, hierarchy_blue, hierarchy_lamp;
	Mat canny_output_red, canny_output_green, canny_output_blue, canny_output_lamp;

	Canny(blue, canny_output_blue, 100, 255 * 2, 3);
	Canny(green, canny_output_green, 100, 255 * 2, 3);
	Canny(red, canny_output_red, 100, 255 * 2, 3);
	Canny(lamp, canny_output_lamp, 100, 255 * 2, 3);

	findContours(canny_output_blue, contours_blue, hierarchy_blue, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	findContours(canny_output_green, contours_green, hierarchy_green, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	findContours(canny_output_red, contours_red, hierarchy_red, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	findContours(canny_output_lamp, contours_lamp, hierarchy_lamp, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	vector<Moments> mu(contours_lamp.size());
	for (int i = 0; i < contours_lamp.size(); i++)
	{
		mu[i] = moments(contours_lamp[i], false);
	}

	vector<Point2f> mc(contours_lamp.size());
	for (int i = 0; i < contours_lamp.size(); i++)
	{
		mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
	}

	Mat drawing = img.clone();
	float near_blue = 0, near_green = 0, near_red = 0;
	Point2f mc_blue, mc_green, mc_red;

	for (int i = 0; i< contours_blue.size(); i++)
	{
		drawContours(drawing, contours_blue, i, Scalar(255,0,0), 2, 8, hierarchy_blue, 0, Point());
		Moments mu_local = moments(contours_blue[i], false);
		Point2f mc_local = Point2f(mu_local.m10 / mu_local.m00, mu_local.m01 / mu_local.m00);
		double near = norm(mc[0] - mc_local);
		if (near < near_blue && near > 0)
		{
			near_blue = near;
			mc_blue = mc_local;
		}
		else if (near_blue == 0) near_blue = near;
	}
	circle(drawing, mc_blue, 4, Scalar(255, 0, 0), -1, 8, 0);

	for (int i = 0; i< contours_green.size(); i++)
	{
		drawContours(drawing, contours_green, i, Scalar(0, 255, 0), 2, 8, hierarchy_green, 0, Point());
		Moments mu_local = moments(contours_green[i], false);
		Point2f mc_local = Point2f(mu_local.m10 / mu_local.m00, mu_local.m01 / mu_local.m00);
		double near = norm(mc[0] - mc_local);
		if (near < near_green && near > 0)
		{
			near_green = near;
			mc_green = mc_local;
		}
		else if (near_green == 0) near_green = near;
	}
	circle(drawing, mc_green, 4, Scalar(0, 255, 0), -1, 8, 0);

	for (int i = 0; i< contours_red.size(); i++)
	{
		drawContours(drawing, contours_red, i, Scalar(0, 0, 255), 2, 8, hierarchy_red, 0, Point());
		Moments mu_local = moments(contours_red[i], false);
		Point2f mc_local = Point2f(mu_local.m10 / mu_local.m00, mu_local.m01 / mu_local.m00);
		double near = norm(mc[0] - mc_local);
		if (near < near_red && near > 0)
		{
			near_red = near;
			mc_red = mc_local;
		}
		else if (near_red == 0) near_red = near;
	}
	circle(drawing, mc_red, 4, Scalar(0, 0, 255), -1, 8, 0);

	for (int i = 0; i< contours_lamp.size(); i++)
	{
		drawContours(drawing, contours_lamp, i, Scalar(0, 150, 220), 2, 8, hierarchy_lamp, 0, Point());
	}

	imshow("Lamp", drawing);
	waitKey(0);

	destroyAllWindows();
	return 0;*/
}
