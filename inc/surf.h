#ifndef __SURF_H__
#define __SURF_H__

#include <register.h>
#include <boost/shared_ptr.hpp>
#include <opencv2/features2d/features2d.hpp>

typedef boost::shared_ptr<cv::SurfFeatureDetector> surfDetectorPtr;

class Surf : public Register
{
   public:
      // Constructor
      Surf( cv::Mat const & refImg, cv::Mat const & newImg, double const & hThresh);

      // Destructor
      ~Surf(){}

      // Calculate the homography
      void calculateHomography();

   private:
      
      double                                 m_hThresh;     // Number of control points
      surfDetectorPtr                        m_detector;   // Pointer to the detector
      cv::SurfDescriptorExtractor            m_extractor;  // Extractor
      cv::BruteForceMatcher< cv::L2<float> > m_matcher;    // Matcher

      cv::Mat                                m_refGray;    // Grayscale of Reference
      cv::Mat                                m_newGray;    // Grayscale of New Image
      
};

typedef boost::shared_ptr<Surf> SurfPtr;
#endif
