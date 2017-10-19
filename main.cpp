
/**
 * libdmtx - Data Matrix Encoding/Decoding Library
 * Copyright 2008, 2009 Mike Laughton. All rights reserved.
 *
 * See LICENSE file in the main project directory for full
 * terms of use and distribution.
 *
 * Contact: Mike Laughton <mike@dragonflylogic.com>
 *
 * \file simple_test.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <dmtx.h>
#include<string>
#include<iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include "opencv2/imgproc/imgproc.hpp"    
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <sys/stat.h>


using namespace std;
using namespace cv;

string numToString2(int value)   //conver 2bit int to string    
{  
    string str;  
    char buf[2];  
    sprintf(buf, "%d", value);  
    str = buf;        
return str;
} 

int main(int argc, char *argv[])
{
  
  
  mkdir("./output/",S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);  //creat a folder to store the barcode
   int startindex=1;
   int idmax=110;   
   
  /////////判断输入参数   
  for (int i=0; i<argc; i++) {
    if (std::string(argv[i]) == "--startindex")
      startindex = atoi(argv[i+1]);
    else if (std::string(argv[i]) == "--endindex")
     idmax = atoi(argv[i+1]);
    else if (std::string(argv[i]) == "--help") {
      std::cout << "Usage: " << argv[0]
                << " [--startindex <the first barcode to be creat>] [---endindex <the last barcode to be creat>] [--help]"
                << std::endl;
      return 0;
    }
  }
 //====================================================================xiu add here 
//====================================================================
//====================================================================
 for(int fucknum=0;fucknum<20;fucknum++)  
{
//====================================================================
//==================================================================== 

string path="./output";
stringstream ss;
ss<<(fucknum+1);
path=path+ss.str()+"/";

const char* path_data= path.data();


mkdir(path_data,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH); 
  
int base=fucknum*10000;  
 startindex=1010001 +base;
idmax=startindex+49;
   
     
//读入公司logo载入图片    
     
     
 //Mat logo_com_src= imread("logo4.png");
// Mat logo_com_des;
//namedWindow("Image");
//imshow("Image",  logo_com_src);
//waitKey(0);
//threshold(logo_com_src, logo_com_des, 253, 255,CV_THRESH_BINARY_INV);
//namedWindow("twoImage");imshow("twoImage", logo_com_des);

 
   DmtxEncode* enc = dmtxEncodeCreate();     //creat the enc
   dmtxEncodeSetProp(enc,DmtxPropMarginSize,30); //设置边缘大小 100像素
   dmtxEncodeSetProp(enc,DmtxPropModuleSize,15);  //单个cell的像素10 ,20,30 
      assert(enc != NULL);  
//dmtxEncodeSetProp( enc, DmtxPropWidth, 121);
 //dmtxEncodeSetProp( enc,DmtxPropHeight, 121);
  
 
 //dmtxImageSetProp( enc->image, DmtxPropWidth, 121);
 // dmtxImageSetProp( enc->image, DmtxPropHeight, 121);


/* *** 省略了错误处理 */

/* 设置二维码图像属性 */
//dmtxImageSetProp(img, DmtxPropImageFlip, DmtxFlipNone);
/*
 string str="1234567890";
 int ret = dmtxEncodeDataMatrix(enc, strlen(str.c_str()), (unsigned char*)str.c_str());  
  dmtxImageSetProp( enc->image, DmtxPropWidth, 121);
  dmtxImageSetProp( enc->image, DmtxPropHeight, 121);
 ret = dmtxEncodeDataMatrix(enc, strlen(str.c_str()), (unsigned char*)str.c_str());  
 
   int width = dmtxImageGetProp(enc->image, DmtxPropWidth);  
    int    height = dmtxImageGetProp(enc->image, DmtxPropHeight);  
       int bytesPerPixel = dmtxImageGetProp(enc->image, DmtxPropBytesPerPixel);  
      fprintf(stderr, "image width: %d, image height: %d, channels: %d\n", width, height, bytesPerPixel);  
   
   cout<<"ok"<<endl;
   */
   //while(1);
  for (int k=startindex;k<=idmax;k++)
  {
      

    
    //convert the last two bits into string 
 char tagid_back[8];
  int  num_tag=k;
  sprintf(tagid_back, "%08d", num_tag);  
  cout<<"hello"<<tagid_back<<endl; 
  
  
  
string tagid[4][4];     //convert the two bits to string      


int width;
int height ;
int bytesPerPixel ;
cv::Mat mat16[4][4];  
  ///////////合成///
cv::Mat mat_combine; 
  
  ///////////该循环实现获得4*4 的二维码
  for(int i=0;i<4;i++)
    for (int j=0;j<4;j++)
    {
          int val= 10*(j+3)+6-i; 
	 // cout<<val;
         tagid[i][j]=numToString2(val)+tagid_back;	  
	 cout<<tagid[i][j]<<"  " ;	 
         if(j==3)
	 cout<<endl;	 
	    std::string str =  tagid[i][j];  
	 

      int ret = dmtxEncodeDataMatrix(enc, strlen(str.c_str()), (unsigned char*)str.c_str());  
    assert(ret == 1);  
	 
	      width = dmtxImageGetProp(enc->image, DmtxPropWidth);  
       height = dmtxImageGetProp(enc->image, DmtxPropHeight);  
       bytesPerPixel = dmtxImageGetProp(enc->image, DmtxPropBytesPerPixel);  
      fprintf(stderr, "image width: %d, image height: %d, channels: %d\n", width, height, bytesPerPixel);  
    assert(bytesPerPixel == 1 || bytesPerPixel == 3 || bytesPerPixel == 4);  
  
  
    if (bytesPerPixel == 1)  
        mat16[i][j] = cv::Mat(height, width, CV_8UC1);  
    else if (bytesPerPixel == 3)  
        mat16[i][j] = cv::Mat(height, width, CV_8UC3);  
    else  
        mat16[i][j] = cv::Mat(height, width, CV_8UC4);    
    
    mat16[i][j].data = enc->image->pxl;    
    //single barcode save
    //std::string image_name = "./output1/"+tagid[i][j]+".png";  
    //cv::imwrite(image_name, mat16[i][j]);    
    }
    
    

   //double heigt_ratio=121.0/1803;
  //double width_ratio=121.0/1275;
    
  int height4=height*4+240;
   int width4=width*4+240;
   
  //int height4=80.0/heigt_ratio;
 //int width4=80.0/width_ratio;
  //cout<<height4<<endl;
  //cout<<width4<<endl;
  
     //int height4=1170;
  // int width4=828;
    if (bytesPerPixel == 1)  
        mat_combine= cv::Mat(height4, width4, CV_8UC1,cv::Scalar(255));  
    else if (bytesPerPixel == 3)  
        mat_combine= cv::Mat(height4, width4,CV_8UC3,cv::Scalar(255,255,255));  
    else  
        mat_combine= cv::Mat(height4, width4,CV_8UC4); 
    
    //cv::Rect rect(80,80, 80, 80);
    for(int i=0;i<4;i++)
      for (int j=0;j<4;j++)    
      {
		cv::Rect rect(i*240+120,j*240+120 , 240,240);
		mat16[j][i].copyTo(mat_combine(rect));  
	 cout<<"ffhello"<<rect<<"   ";
      }
      ///draw something
 
    // rectangle
    /*
     cv::rectangle( mat_combine, cv::Point(90, 90 ),
         cv:: Point( 1110, 1110),
         cv:: Scalar( 0, 0, 0 ),
         2,
          8 ); 
   
    
    */
   /*    cv::rectangle( mat1[k], cv::Point(30, 30 ),
         cv:: Point( 370, 370),
         cv:: Scalar( 0, 0, 0 ),
         0.2,
          8 ); 
    */ 
     /////////////
     
 //    line(mat1[k], cv:: Point( 200, 200), cv:: Point( 350, 200),cv::Scalar(0,0,0));  //x axis
     
   //  line(mat1[k], cv:: Point( 200, 200), cv:: Point( 200, 50),cv::Scalar(0,0,0));  //y axis

     //draw a cross
     line(mat_combine, cv:: Point( 600, 580), cv:: Point(600, 620),cv::Scalar(0,0,0),2);  //
     line(mat_combine, cv:: Point( 580, 600), cv:: Point(620, 600),cv::Scalar(0,0,0),2);  //
 
/*
      for(int i=0;i<51;i++)
      {
	     line(mat_combine, cv:: Point( 90, 90+20*i), cv:: Point(90, 90+20*i+10),cv::Scalar(0,0,0),2);  //
	
      }
      
         for(int i=0;i<51;i++)
      {
	     line(mat_combine, cv:: Point( 90+20*i, 1110), cv:: Point(90+20*i+10, 1110),cv::Scalar(0,0,0),2);  //
	
      }
      
            for(int i=0;i<51;i++)
      {
	     line(mat_combine, cv:: Point(1110, 1110-20*i), cv:: Point(1110, 1110-20*i-10),cv::Scalar(0,0,0),2);  //
	
      }
      
           for(int i=0;i<51;i++)
      {
	     line(mat_combine, cv:: Point(1110-20*i,90 ), cv:: Point(1110-20*i-10,90 ),cv::Scalar(0,0,0),2);  //
	
      }
      */
      
      
     //draw four lines

     line(mat_combine, cv:: Point( 600, 90), cv:: Point(600, 120),cv::Scalar(0,0,0),2);  //
      line(mat_combine, cv:: Point( 600, 1110), cv:: Point(600,1080),cv::Scalar(0,0,0),2);  //   
      
      
      line(mat_combine, cv:: Point( 90, 600), cv:: Point(120, 600),cv::Scalar(0,0,0),2);  //
      line(mat_combine, cv:: Point( 1110, 600), cv:: Point(1080, 600),cv::Scalar(0,0,0),2);  // 
      
  
      ////////////更改logo
      
     // cv::Rect rect(30,15, 146,22);
      
      /*
       cv::Rect rect(37,20, 150,15);
      logo_com_src.copyTo(mat_combine(rect));  
     */
             cv::Rect rect(200,107, 309,25);
   //   logo_com_src.copyTo(mat_combine(rect));  
    //////// 
   // CvFont  myfont;
    //void cvInitFont( CvFont* font, int font_face, double hscale,
  //               double vscale, double shear=0,
     //            int thickness=1, int line_type=8 );
    // cvInitFont( &myfont, CV_FONT_HERSHEY_COMPLEX , 1.0,1.0,0,1, 8 );
      
  
      string words= "X";
        
	cv::putText( mat_combine, words, cv::Point(1065,590),  FONT_HERSHEY_SIMPLEX ,1, cv::Scalar(0, 0, 0),3);  //x axis
       words="Y";
       cv::putText( mat_combine, words, cv::Point( 610,128), FONT_HERSHEY_SIMPLEX , 1,cv::Scalar(0, 0, 0),3);  //y axisFONT_HERSHEY_DUPLEX
      //cv::arrowedLine(mat1[k], cv:: Point( 200, 200), cv:: Point( 200, 380), cv::Scalar(255,0,0), 1, 8, 0, 0.1);
       
     
      
    string  temp=tagid_back;    
       char tempchar[9];
         sprintf(tempchar, "%09d", 0);    
	 tempchar[4]='-';
       for(int i=0;i<8;i++)
       {
	 if(i<4)
	 tempchar[i]=tagid_back[i];
	 else 
	  tempchar[i+1]=tagid_back[i];	 
      }

   //   string  temp1="ID:";
    //    words=temp1+tempchar;
           words=tempchar;
	//void putText( Mat& img, const string& text, Point org,
                 //        int fontFace, double fontScale, Scalar color,
                      //   int thickness=1, int lineType=8,
                      //   bool bottomLeftOrigin=false );
	 cv::putText( mat_combine, words, cv::Point(821,130),cv:: FONT_HERSHEY_SIMPLEX  ,1, cv::Scalar(0, 0, 0) ,2); //put the id
//	   words="Standard Robots";
    //   cv::putText( mat_combine, words, cv::Point( 20,40), CV_FONT_HERSHEY_SCRIPT_COMPLEX  , 0.8, cv::Scalar(0, 0, 0) );  //put the company
	 
  /////vector<int> param = vector<int>(2);
  //   param[0]=CV_IMWRITE_JPEG_QUALITY;
  //  param[1]=100;  
         ///保存
	 
	 ///CV_IMWRITE_PNG_COMPRESSION
	 
	 vector<int> compression_params;
	 compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
compression_params.push_back(100);
//vector<int> compression_params;
//compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
 //compression_params.push_back(0); 
       std::string image_name = path+temp+".jpg";  
    // cv::imwrite(image_name, mat_combine,compression_params);  

Mat final_turtle=mat_combine(Range(90,1110), Range(90,1110));
cv::imwrite(image_name, final_turtle,compression_params);  

    ///////////

    
  }
    ////////////////
    
    
        dmtxEncodeDestroy(&enc);  
    }   
///////////////// 

    
    
    return 0;  
}
