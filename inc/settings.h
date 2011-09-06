#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <fstream>
#include <boost/shared_ptr.hpp>

typedef std::map<std::string,std::vector<std::string> > fileMap;

class Settings
{
   public:
      // Constructor
      Settings(std::string const & fileName);

      // Destructor
      ~Settings(){}

      // Settings reader
      bool readSettings();

      // Get file list
      std::vector< std::string > const &getFileList() const { return m_fileList; }

      // Get output file name
      std::string const &outputFile() const {return m_outFileName;}
   private:

      std::string                m_settingsFile; // Text file containing settings
      std::vector< std::string > m_fileList;     // List of input images
      std::string                m_outFileName;  // Output file name
     
};

typedef boost::shared_ptr<Settings> SettingsPtr;
#endif
