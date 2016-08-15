#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv){
  Mat image, mask;
  int width, height;
  int nobjects;
  
  CvPoint p;
  image = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
  
  if(!image.data){
    std::cout << "imagem nao carregou corretamente\n";
    return(-1);
  }
  width=image.size().width;
  height=image.size().height;

  p.x=0;
  p.y=0;

  nobjects=0;

int j= 0;

    for(int i=0; i<height; i++){
      if(image.at<uchar>(i,j) == 255){      
          p.x= j;
          p.y= i;

          floodFill(image, p, 0);
        }
      if(image.at<uchar>(j,i) == 255){
          p.x= i;
          p.y= j;

          floodFill(image, p, 0);
      }
    }

j = height-1;

    for(int i=0; i<width; i++){
      if(image.at<uchar>(i,j) == 255){      
          p.x= j;
          p.y= i;

          floodFill(image, p, 0);
        }
      if(image.at<uchar>(j,i) == 255){
          p.x= i;
          p.y= j;

          floodFill(image, p, 0);
      }
    }

    for(int i=0; i<height; i++){
      for(int j=0; j<width; j++){
        if(i==0 && j==0){
          p.x=j;
          p.y=i;
          floodFill(image,p,100);
        }
        else if(image.at<uchar>(i,j) == 255){
          // achou um objeto
          nobjects++;
          p.x=j;
          p.y=i;
          floodFill(image,p,100);
        }
      }
    }

    nobjects = 0;
    for(int i=0; i<height; i++){
      for(int j=0; j<width; j++){
        if(image.at<uchar>(i,j) == 0){
          // achou um objeto
          nobjects++;
          p.x=j;
          p.y=i;
          floodFill(image,p,200);
        }
      }
    }


      imshow("image", image);
      imwrite("labeling.png", image);
      std::cout << nobjects << " bolhas com buraco" << std::endl;
      waitKey();
  return 0;
    }