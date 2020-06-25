#include <opencv2/core/core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

#include <math.h>
#include <iostream>

#define coorX 1167
#define END 1030
#define Width 133
#define Height 100

/// Global variables

int threshold_value = 0;
int threshold_type = 3;
int const max_value = 150;
int const max_type = 4;
int const max_BINARY_value = 255;

using namespace std;
using namespace cv;

int main()
{
	bool flag = 1;
	Mat img, back, mask;

	//ñ÷èòûâàåì èç ôàéëà ôîí
	Mat fimg = imread("KNDR.png", CV_LOAD_IMAGE_COLOR);
	fimg.convertTo(img, CV_8UC3);
	namedWindow("img", CV_WINDOW_AUTOSIZE);
	//imshow("img", img);

	/*Point2f src_center(img.cols / 2.0F, img.rows / 2.0F);
	Mat rot_matrix = getRotationMatrix2D(src_center, -5, 1.0);
	Mat rotated_img(Size(img.size().height, img.size().width), img.type());
	warpAffine(img, rotated_img, rot_matrix, img.size());
	imwrite("rotated.jpg", rotated_img);*/

	//cvtColor(rotated_img, mask, CV_BGR2GRAY, 0);	
	//rotated_img.copyTo(rimg, mask);
	//imwrite("gray.jpg", rimg);
	//imwrite("mask.jpg", mask);
		
	//ñ÷èòûâàåì èç ôàéëà êàðåòêó
	Mat temp = imread("MBR.png", CV_LOAD_IMAGE_COLOR);
	temp.convertTo(temp, CV_8UC3);
	Rect r(0, 0, Width, Height);
	Mat img1 = temp(r);
	//imwrite("img1.jpg", img1);

	//ñîçäàåì êîíòåéíåð è çàïîëíÿåì åãî çíà÷åíèÿìè êîñèíóñà
	vector<Point> contour;

	for (float x = 0; x <= coorX; x += 5)
	{
		float y = -150*cos(x/50)+400;
		contour.push_back(Point(x, y));                      
	}	
	
	//ðèñóåì êîñèíóñîèäó
	Point *pts = (Point*)Mat(contour).data;
	int npts = Mat(contour).rows;
	polylines(img, &pts, &npts, 1, false, Scalar(50, 50, 150), 2, CV_AA, 0);
	img.copyTo(back);

	//ïåðåìåùàåì êîðåòêó ïî êîñèíóñîèäå
	for (float x = 0; x <= END; x += 5)
	{
		float y = -150 * cos(x / 50) + 400;

		//ïîâîðà÷èâàåì èçîáðàæåíèå ñ êàðåòêîé
		Point2f src_center(img1.cols / 2.0F, img1.rows / 2.0F);
		Mat rot_matrix = getRotationMatrix2D(src_center, -8, 1);
		Mat rotated_img(Size(img1.size().height, img1.size().width), img1.type());
		warpAffine(img1, rotated_img, rot_matrix, img1.size());
		//imwrite("rot1.jpg", rotated_img);

		//ïðèìåíÿåì ìàñêó äëÿ ôèëüòðàöèè
		cvtColor(rotated_img, mask, CV_BGR2GRAY);

		//ñîçäàòü êîïèþ ðàêåòû â ôîðìàòå HSV
		Mat src_hsv = rotated_img.clone();
		cvtColor(rotated_img, src_hsv, CV_BGR2GRAY);

		//ïðèìåíèòü ôóíêöèþ threshold
		Mat dst = rotated_img.clone();
		cvtColor(dst, dst, CV_BGR2GRAY);
		threshold(src_hsv, dst, 245, 255, THRESH_BINARY);
		imshow("mask2", dst);
		waitKey(50);

		bitwise_not(dst, dst);
		//îáðåçàåì êðàÿ
		Mat ROI = dst(Rect(10, 10, (Width-15), (Height-20)));
		imshow("mask22", ROI);
		waitKey(50);

		//ïåðåâåñòè èç HSV â áèíàðíûé ôîðìàò
		
		//bitwise_and(rotated_img, rimg, dst);
		Mat rimg = rotated_img(Rect(10, 10, (Width - 15), (Height - 20)));
		rimg.copyTo(rimg, ROI);
		bitwise_or(rimg, rimg, mask = ROI);
		//rotated_img.copyTo(rimg(Rect(10, 10, (Width - 15), (Height - 20))), ROI);
		imshow("rimg",rimg);
		waitKey(50);

		rimg.copyTo(img(Rect(x, y, Width-15, Height-20)));
		imshow("img", img);

		//ñîõðàíÿåì èçîáðàæåíèå, êîãäà êîðåòêà íà ïîëîâèíå ïóòè
		if (x >= coorX / 2 && flag == 1)
		{
			imwrite("centre.png", img);
			flag = 0;
		}

		waitKey(100);
		back.copyTo(img);
		rotated_img.copyTo(img1);
	}

	waitKey(0);
	destroyAllWindows();

	return 0;
}
