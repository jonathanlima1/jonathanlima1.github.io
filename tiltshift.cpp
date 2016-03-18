#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>

using namespace cv;
using namespace std;

double d;
int d_slider = 0;
int d_slider_max = 100;

double altura;
int centro;

int altura_slider = 0;
int altura_slider_max = 100;

int centro_slider = 0;
int centro_slider_max = 100;

double alfa;

Mat imagemF, imagemFB;

Mat imagem, imagemB, tilt, imagem1, imagem2;

char TrackbarName[50];

void on_trackbar_blend(int, void*){
 d = (double) d_slider/1.0 ;
 int l1 = centro - altura/2;
 int l2 = centro + altura/2;

 imagem1 = imread("imagemTilt1.jpeg");
 imagem2 = imread("imagemTilt2.jpeg");
 
 for(int i = 0; i<imagem.size().height; i++){
	for(int j = 0; j<imagem.size().width; j++){
		if(i <= l1 || i>=l2){
	 		imagem1.at<uchar>(i,j) = 0;
			imagem2.at<uchar>(i,j) = 1;
		}else{
			imagem1.at<uchar>(i,j) = 1;
			imagem2.at<uchar>(i,j) = 0;
		}
	}
 }

 imshow("Teste", imagem1);
  imshow("Teste2", imagem2);

  multiply(imagem, imagem1, imagemF, 1.0, -1 );

  multiply(imagemB, imagem2, imagemFB, 1.0, -1 );

 //for(int i = 0; i<imagem.size().height; i++){
 //	alfa = 0.5 * ( tanh( (-l1)/d ) - tanh( (-l2)/d ) );
 //	addWeighted( imagemF, alfa, imagemFB, 1-alfa, 0.0, tilt);
 //}
   tilt = imagemF + imagemFB;
  //add(imagemF, imagemFB, tilt, Mat(), -1); 
  imshow("TiltShift", tilt);
}

void on_trackbar_line(int, void*){

  altura = altura_slider*imagem.size().height/altura_slider_max;

  on_trackbar_blend(d_slider,0);
}

void on_trackbar_line2(int, void*){
  centro = centro_slider*imagem.size().height/centro_slider_max;

  on_trackbar_blend(d_slider,0);
}

int main(int argvc, char** argv){

  imagem = imread("blend2.jpg");

  tilt = imread("blend2.jpg");

  erode(imagem, imagemB, Mat(), Point(-1,-1), 2, BORDER_CONSTANT, morphologyDefaultBorderValue() );

  imagem1 = imread("imagemTilt1.jpeg");
  imagem2 = imread("imagemTilt2.jpeg");

  namedWindow("TiltShift", 1);

  sprintf( TrackbarName, "Decaimento" );
  createTrackbar( TrackbarName, "TiltShift",
				  &d_slider,
				  d_slider_max,
				  on_trackbar_blend );
  on_trackbar_blend(d_slider, 0 );

  sprintf( TrackbarName, "Centro");
  createTrackbar( TrackbarName, "TiltShift",
				  &centro_slider,
				  centro_slider_max,
				  on_trackbar_line2 );
  on_trackbar_line2(centro_slider, 0 );

  sprintf( TrackbarName, "Altura");
  createTrackbar( TrackbarName, "TiltShift",
				  &altura_slider,
				  altura_slider_max,
				  on_trackbar_line );
  on_trackbar_line(altura_slider, 0 );

  waitKey(0);
  return 0;
}