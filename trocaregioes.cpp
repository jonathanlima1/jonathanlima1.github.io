#include <iostream>
#include <cv.h>
#include <highgui.h>
	
	using namespace cv;
	using namespace std;

int main(int argc, char** argv){

	Mat image;

	image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if(!image.data)
		cout << "Não foi possível carregar a imagem" << endl;

	namedWindow("janela",WINDOW_AUTOSIZE);

	int aux_1, aux_2;

	 for(int i=0;i<(image.cols)/2;i++){
	     for(int j=0;j<(image.rows)/2;j++){
	     	aux_1 = image.at<uchar>((i+(image.cols/2)),(j+(image.rows/2)));
	     	aux_2 = image.at<uchar>((i+(image.cols/2)),j);

	     	image.at<uchar>((i+(image.cols/2)),(j+(image.rows/2))) = image.at<uchar>(i,j);
	     	image.at<uchar>((i+(image.cols/2)),j) = image.at<uchar>(i,(j+(image.rows/2)));

	     	image.at<uchar>(i,j) = aux_1;
	     	image.at<uchar>(i,(j+(image.rows/2))) = aux_2;
    }
  }

  imshow("janela", image);  
  waitKey();
  return 0;
}