#include <opencv2/core/core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

#include <math.h>
#include <iostream>

#define width 3
#define height 3

using namespace std;
using namespace cv;

//void sort(uchar* buff, int i, int j);

int main()
{
	Mat img = imread("Lena.png"), img_temp;
	cvtColor(img, img, CV_BGR2GRAY);
	Mat img1 = img.clone();
	imshow("Lena", img);
	waitKey(0);

	uchar* q = img1.data;
	
	for (int x = 1; x < img.rows - 1; x++)
		for (int y = 1; y < img.cols - 1; y++)
		{
			Rect r(x - 1, y - 1, width, height);
			img_temp = img(r);
			uchar* p = img_temp.data;

			for (unsigned int i = 0; i < width * height; i++)
				for (unsigned int j = 0; j < width * height; j++)
				{
					if (p[j] > p[j + 1])
					{
						int temp = p[j];
						p[j] = p[j + 1];
						p[j + 1] = temp;
					}
				}	
		
			*((q + x) + y) = p[4];

		}
	imshow("img_s2", img1);
	waitKey(0);

	blur(img, img, Size(3,3));
	imshow("img_s3", img);
	waitKey(0);

	uchar* p = img1.data;
	q = img.data;
	float dif = 0;

	for (unsigned int i = 0; i < 512 * 512; i++)
		if (p[i] <= q[i]+1 && p[i] >= q[i]-1) dif++;

	dif = dif / (512 * 512);
	cout << "dif = " << dif << endl;		

	waitKey(0);
	destroyAllWindows();

	return 0;
}

//void sort(uchar* buff, int col, int row)
//{
//	int temp = 0;
//	for (int i = 0; i < col - 1; i++)
//		for (int j = 0; j < row - 1; j++)
//			for (int a = 0; a < col - 1; a++)
//				for (int b = 0; b < row - 1; b++)
//				{
//					if (*((buff + a) + b)> *((buff + i) + j))
//					{
//						temp = *((buff + a) + b);
//						*((buff + a) + b) = *((buff + i) + j)
//						*((buff + i) + j) = temp;
//					}
//				}
//		
//}
