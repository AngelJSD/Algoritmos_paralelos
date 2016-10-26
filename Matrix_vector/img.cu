#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

__global__
void GScale(Mat* img, int iRow, int iCol){

	int col = blockIdx.x*blockDim.x + threadIdx.x;
	int row = blockIdx.y*blockDim.y + threadIdx.y;

	if (col < iCol && row < iRow){

		// int rgbOffset = (col*iCol + row) * 3;
		//
		// img.at<Vec3f>(row, col)[0] *= 0.07f;		//BLUE
		// img.at<Vec3f>(row, col)[1] = 0.71f;		//GREEN
		// img.at<Vec3f>(row, col)[2] = 0.21f;		//RED
	}
}

__host__
int main(){

	Mat* d_Image;

	Mat image;
	image = imread("tux.bmp", CV_LOAD_IMAGE_COLOR);

	namedWindow( "Display window", WINDOW_AUTOSIZE );
	imshow( "Display window", image );

	// cudaMalloc( (void**) &d_Image, sizeof(Mat));
	// cudaMemcpy(d_Image, image, sizeof(Mat), cudaMemcpyHostToDevice);

	cout<<image.at<Vec3b>(0, 0)<<endl;
	// for(int y = 0; y < image.rows; y++) {
	// 	for(int x = 0; x < image.cols; x++) {
	// 		image.at<Vec3b>(y, x)[0] *= 0.3;		//BLUE
	// 		image.at<Vec3b>(y, x)[1] *= 0.3;		//GREEN
	// 		image.at<Vec3b>(y, x)[2] *= 0.3;		//RED
	// 	}
	// }
	// GScale<<<1, 96>>>(image, image.rows, image.cols);

	// cudaMemcpy(image, d_Image, sizeof(Mat), cudaMemcpyDeviceToHost);

	namedWindow( "Display window GrayScale", WINDOW_AUTOSIZE );
	imshow( "Display window GrayScale", image );
	waitKey(0);

	return 0;
}
