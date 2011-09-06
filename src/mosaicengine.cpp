#include <mosaicengine.h>

MosaicEngine::MosaicEngine(std::string const &settingsFile) :
m_settingsFile(settingsFile)
{
   // Create the settings object
   m_settings.reset( new Settings(settingsFile));
}

bool MosaicEngine::runEngine()
{
   // Read the settings file
   if( m_settings->readSettings() )
   {
      // Get the list of files   
      std::vector< std::string > fileList = m_settings->getFileList();
      for( size_t idx = 0; idx < fileList.size(); ++idx)
      {
         Input newInput(fileList[idx]);
         if( newInput.success() ) m_input.push_back(newInput);
      }
      if( m_input.size() <= 1 ) return false;

      // Create a bigger version of the first image and call it the 'mosaic'
      cv::Mat mosaic;
      m_input[0].extendImage(mosaic);
  
      // Now loop over the other images
      for( size_t idx = 1; idx < m_input.size(); ++idx)
      {
         // Create an extended image
         cv::Mat extImg;
         m_input[idx].extendImage(extImg);

         // Create the registration object and calculate the homography
         m_register.reset( new Surf( mosaic, extImg, 400) );
         m_register->calculateHomography();

         cv::Mat homog = m_register->getHomog();

         cv::Mat outImg;
         cv::warpPerspective(extImg,outImg,homog,mosaic.size());
 
         // Reset the extImg
         extImg.setTo(0.);
         simpleBlend(mosaic,outImg,extImg);
         extImg.copyTo(mosaic);

         // Display the current result
         cv::namedWindow("test",1);
         cv::imshow("test",mosaic);
         cv::waitKey(0); 
      }

  
   } else return false;

   return true;

}

void outputImage()
{
   std::cout << "output" << std::endl;
}
