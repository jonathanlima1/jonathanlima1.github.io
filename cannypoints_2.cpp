#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <numeric>
#include <ctime>
#include <cstdlib>

using namespace std;
using namespace cv;

#define JITTER 1
#define RAIO 1

int top_slider = 1;
int top_slider_max = 20;

char TrackbarName[50];

Mat image, border, points, out;
int width, height;
int x, y, raio;
Vec3b val;


void on_trackbar_canny(int, void*){
  Canny(image, border, 10*top_slider, 30*top_slider);
  //imshow("canny", border);

  points = Mat(height, width, CV_8UC3, Scalar(255,255,255));
  //points = Scalar(255,255,255);

  for(int l=0; l<height ;l++){
      for(int c=0; c<width ;c++){
        if(border.at<uchar>(l,c) == 255){
         //raio = 1+rand()%3;
          if(top_slider < 5) raio = 1;
          else if(top_slider >= 5 && top_slider < 10) raio = 2;
          else if(top_slider >= 10 && top_slider < 15) raio = 3;
          else raio = 4;
          x = l+rand()%(2*JITTER)-JITTER+1;
          y = c+rand()%(2*JITTER)-JITTER+1;
          val[0] = (int)(image.at<Vec3b>(x,y)[0]);
          val[1] = (int)(image.at<Vec3b>(x,y)[1]);
          val[2] = (int)(image.at<Vec3b>(x,y)[2]);
          circle(points,
                 cv::Point(y,x),
                 raio,
                 cv::Scalar(val[0],val[1],val[2]),
                 -1);    
        }
      }
  } 
    imshow("canny", points);
    //waitKey();
}

int main(int argc, char** argv){

  image= imread(argv[1],CV_LOAD_IMAGE_COLOR);

  srand(time(0));

  width=image.size().width;
  height=image.size().height;

  if(!image.data){
  cout << "nao abriu" << argv[1] << endl;
    cout << argv[0] << " imagem.jpg";
    exit(0);
  }

  points = Mat(height, width, CV_8U, Scalar(255,255,255));

  sprintf( TrackbarName, "Threshold inferior x %d", top_slider_max);
  namedWindow("canny",1);
  createTrackbar( TrackbarName, "canny",
                &top_slider,
                top_slider_max,
                on_trackbar_canny );

  on_trackbar_canny(top_slider, 0 );

  waitKey(0);
  return 0;
}