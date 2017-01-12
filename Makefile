CXX =  g++
CXXFLAGS = -Wall 
LDFLAGS = -L/usr/local/opt/opencv3/lib
INCLUDES = -I/usr/local/opt/opencv3/include
PKG_CONFIG_PATH = /usr/local/opt/opencv3/lib/pkgconfig

MAIN = ./imgtosound

all: $(MAIN)

#$(MAIN): 
#	$(CXX) $(CXXFLAGS) imgtosound.cpp -o $(MAIN) $(INCLUDES) $(LDFLAGS)

$(MAIN): ./imgtosound.cpp 
	$(CXX) $(CXXFLAGS) `pkg-config --cflags --libs opencv` imgtosound.cpp -o $(MAIN)

clean: 
	@rm -f ./imgtosound
	@rm -fr ./imgtosound.dSYM
