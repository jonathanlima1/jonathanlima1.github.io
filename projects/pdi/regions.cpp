#include <iostream>
#include <cv.h>
#include <opencv2/opencv.hpp>
#include <highgui.h>

using namespace cv;
using namespace std;

int main(int, char**){
  Mat image;
  Vec3b val;
  int P1i, P1j, P2i, P2j;

  image= imread("bolhas.png",CV_LOAD_IMAGE_GRAYSCALE);
  if(!image.data)
    cout << "nao abriu bolhas.png" << endl;

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

  Mat image_roi = image(roi);

  val[0] = 0;   //B
  val[1] = 0;   //G
  val[2] = 255; //R
  
  for(int i=200;i<210;i++){
    for(int j=10;j<200;j++){
      image.at<double>(i,j) = 255 - image.at<double>(i,j);
    }
  }

  imshow("janela", image);  
  waitKey();
  return 0;
}
