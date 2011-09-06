#ifndef __REGISTER_H__
#define __REGISTER_H__

#include <cv.h>
#include <opencv2/core/core.hpp>
#include <vector>
#include <boost/shared_ptr.hpp>

///////////////////////////////////////////////////////////////////
//
// Register
//
// This base class describes the behavior of a registration
// object.  A new image is compared to a reference image and
// a list of keypoints is created. The keypoints are matched
// and a homography is found.  
//
///////////////////////////////////////////////////////////////////
class Register
{

   public:
      // Constructor
      Register(){}

      // Destructor
      virtual ~Register(){}

      // Detect register
      virtual void calculateHomography()=0;

      // Get Homography
      cv::Mat const & getHomog(){ return m_homog; }

   protected:

      // Homography
      cv::Mat                   m_homog;
};

typedef boost::shared_ptr<Register> RegisterPtr;

#endif
