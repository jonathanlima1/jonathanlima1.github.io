#include <iostream>
#include <opencv2/opencv.hpp>
#include <cv.h>
#include <highgui.h>
	
	using namespace cv;
	using namespace std;

int main(int argc, char** argv){

	int P1i, P1j, P2i, P2j;

	Mat image;

	image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if(!image.data)
		cout << "Não foi possível carregar a imagem" << endl;

	namedWindow("janela",WINDOW_AUTOSIZE);

	cout << "Digite P1 i" << endl;
	cin >> P1i;
	cout << "Digite P1 j" << endl;
	cin >> P1j;

	cout << "Digite P2 i" << endl;
	cin >> P2i;
	cout << "Digite P2 j" << endl;
	cin >> P2j;

	  Rect roi(P1i, P2i, P1j, P2j);

	int val;

	for(int i=0;i<image.rows;i++){
		for(int j=0;j<image.cols;j++){
			if(i >= P1i && i <= P2i && j >= P1j && j <= P2j ){
				val = 255 - image.at<uchar>(i,j);
			}else
				val = image.at<uchar>(i,j);

			image.at<uchar>(i,j) = val;
		}
	}

  imshow("janela", image);  
  waitKey();
  return 0;
}
