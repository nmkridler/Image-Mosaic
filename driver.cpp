
#include <iostream>
#include <string>
#include <mosaicengine.h>

int main( int argc, char **argv)
{
   // Settings file
   std::string settingsFile(argv[argc-1]);

   std::cout << " Running Mosaic Engine " << std::endl;
   std::cout << " Processing: " << settingsFile << std::endl;

   // Create the mosaic engine
   MosaicEngine engine(settingsFile);

   engine.runEngine();
   return 0;
}
