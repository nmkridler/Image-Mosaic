#include <input.h>

// Constructor
Input::Input(std::string const &fileName) :
m_valid(false),
m_fileName(fileName)                                        
{
   // Open up the input image
   cv::Mat inImg = cv::imread(m_fileName.c_str());
   cv::resize(inImg,m_image,cv::Size(),0.25,0.25,cv::INTER_NEAREST);

   // Determine whether or not the read was succesful
   if( !m_image.data ) 
   {
      m_valid = false;
      std::cout << "failed to open: " << m_fileName << std::endl;
   }
   m_valid = true;
}

void Input::extendImage( cv::Mat &output )
{
   // Create a bigger version of the first image and call it the 'mosaic'
   cv::Size mSize(3*m_image.cols,m_image.rows);
   output = cv::Mat::zeros(mSize,m_image.type());

   // Cut out the center and copy the image to it
   cv::Rect centerROI( cv::Point(m_image.cols,0),m_image.size());
   cv::Mat  centerImg = output(centerROI);
   m_image.copyTo(centerImg);
}

void Input::displayImage( std::string const & window,
                          int         const & windowNumber, 
                          double      const & scale)
{
   // Temporary image for display purposes
   cv::Mat displayImg;
   
   // Create the window
   cv::namedWindow(window.c_str(),windowNumber);
   // Resize the image if necessary
   if( scale < 1.0 )
   {
      cv::resize(m_image,displayImg,cv::Size(),scale,scale,cv::INTER_NEAREST);
   }
   else m_image.copyTo(displayImg);
   
   // Show the image
   cv::imshow(window.c_str(),displayImg);
   cv::waitKey(0);

}
