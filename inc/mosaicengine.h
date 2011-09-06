#ifndef __MOSAICENGINE_H__
#define __MOSAICENGINE_H__

#include <cv.h>
#include <vector>
#include <opencv2/core/core.hpp>
#include <boost/shared_ptr.hpp>
#include <register.h>
#include <surf.h>
#include <input.h>
#include <iostream>
#include <settings.h>
#include <blend.h>

class MosaicEngine
{
   public:
      // Constructor
      MosaicEngine(std::string const &settingsFile);

      // Destructor
      ~MosaicEngine(){}

      // Execute
      bool runEngine();

      // Output results
      void outputImage();

   private:
      std::vector< Input >  m_input;        // List of images to process
      std::string           m_settingsFile; // Settings file
      RegisterPtr           m_register;     // Registration object
      SettingsPtr           m_settings;     // Settings object
     
};



#endif
