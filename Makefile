all: mosaic

CFLAGS=-fPIC -g -Wall `pkg-config --cflags opencv`
LIBS = `pkg-config --libs opencv`
INCLUDE = -I/usr/local/include/boost/ -I/home/nick/opencvtest/mosaic/inc

mosaic:  *.cpp src/*.cpp
	$(CXX) $(INCLUDE) $(CFLAGS) $? -o $@  $(LIBS)

%.o: %.cpp
	$(CXX) -c $(CFLAGS) $< -o $@

clean:
	rm -rf *.o mosaic

