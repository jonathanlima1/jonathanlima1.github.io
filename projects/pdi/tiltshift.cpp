#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>

using namespace cv;
using namespace std;

double d;
int d_slider = 6;
int d_slider_max = 100;

double altura;
int centro;

int altura_slider = 20;
int altura_slider_max = 100;

int centro_slider = 0;
int centro_slider_max = 100;

Mat imagemF, imagemFB, alfa, alfa2;

Mat imagemOriginal, imagemBorrada, imagem32, imagemB32, tilt, tilt32;

char TrackbarName[50];

void atualizarImagem(){

  imagemOriginal.convertTo(imagem32, CV_32FC3);
  imagemBorrada.convertTo(imagemB32, CV_32FC3);

  multiply(imagem32, alfa, imagemF);
  multiply(imagemB32, alfa2, imagemFB);

  add(imagemF,imagemFB,tilt32);

  tilt32.convertTo(tilt, CV_8UC3);

  imshow("TiltShift", tilt);
}

void tiltShift(){
  int l1 = centro_slider - altura_slider/2 -50;
  int l2 = centro_slider + altura_slider/2 -50;

  alfa = Mat::zeros(imagemOriginal.rows, imagemOriginal.cols, CV_32F);
  alfa2 = Mat::zeros(imagemOriginal.rows, imagemOriginal.cols, CV_32F);

  for(int i=0; i < imagemOriginal.rows; i++){

    double x = 100*i/(imagemOriginal.size().height - 1) - 50;
    float valor = 0.5f * ( tanh( (x-l1)/d ) - tanh( (x-l2)/d ) );

    for(int j=0; j < imagemOriginal.cols; j++){
      alfa.at<float>(i,j) = valor;
      alfa2.at<float>(i,j) = 1 - valor;
    }
  }

  Mat imagem1[] = {alfa,alfa,alfa};
  Mat imagem2[] = {alfa2,alfa2,alfa2};

  merge(imagem1, 3, alfa);
  merge(imagem2, 3, alfa2);

  atualizarImagem();
}

void on_trackbar_blend(int, void*){
  d = (double) d_slider ;

  if (d < 1)
    d = 1;

  tiltShift();
}

void on_trackbar_line(int, void*){

  altura = altura_slider*imagemOriginal.size().height/altura_slider_max;

  if (altura == 0) {
      altura = 1;
  }

  if (altura > imagemOriginal.size().height) {
      altura = imagemOriginal.size().height;
  }

  tiltShift();
}

void on_trackbar_line2(int, void*){
  centro = centro_slider*imagemOriginal.size().height/centro_slider_max;

  tiltShift();
}

int main(int argvc, char** argv){

  imagemOriginal = imread("tiltshift.jpg");
  imagemBorrada = imagemOriginal.clone();

  Mat aux, mask, mask1;
  float media[] = {1,1,1,
                   1,1,1,
                   1,1,1};

  mask = Mat(3, 3, CV_32F, media);

  scaleAdd(mask, 1/9.0, Mat::zeros(3,3,CV_32F), mask1);
  mask = mask1;
  imagemBorrada.convertTo(aux, CV_32F);

  for (int i = 0; i < 7; i++) {
      filter2D(aux, aux, aux.depth(), mask, Point(1, 1), 0);
  }

  aux=abs(aux);
  aux.convertTo(imagemBorrada, CV_8UC3);

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
