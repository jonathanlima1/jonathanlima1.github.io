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

	int val;

	 for(int i=0;i<image.rows;i++)
{    for(int j=0;j<image.cols;j++){
      val = 255 - image.at<uchar>(i,j);
      image.at<uchar>(i,j) = val;
    }
  }

  imshow("janela", image);  
  waitKey();
  return 0;
}