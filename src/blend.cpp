#include <blend.h>

void simpleBlend( cv::Mat const &inImg1, cv::Mat const &inImg2, cv::Mat &outImg)
{
   // Create masks of the zero and non-zero areas
   cv::Mat gray1, gray2;
   cv::cvtColor(inImg1,gray1,CV_RGB2GRAY);
   cv::cvtColor(inImg2,gray2,CV_RGB2GRAY);

   // Get the common areas
   cv::multiply(gray1,gray2,gray1);
   cv::Mat oMask = gray1 >  0;             // Overlap Mask
   cv::Mat nMask = gray1 == 0;             // non-Overlap Mask

   // Create a zero image
   cv::Mat zImg1 = cv::Mat::zeros(inImg1.size(),inImg1.type());
   cv::Mat zImg2 = cv::Mat::zeros(inImg1.size(),inImg1.type());

   // Add the zero parts together
   cv::add(inImg1    ,inImg2    ,zImg1,nMask);
   cv::add(inImg1*0.5,inImg2*0.5,zImg2,oMask);
   cv::add(zImg1,zImg2,outImg);
}

