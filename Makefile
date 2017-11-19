CXX=g++
CPPFLAGS=-Wall -O2
LDLIBS=-lwiringPi -lcurl

fanControl: fanControl.o requestCurl.o
	$(CXX) $(CPPFLAGS) $(LDLIBS) -o fanControl fanControl.o requestCurl.o

fanControl.o: fanControl.cpp
	$(CXX) $(CPPFLAGS) -c fanControl.cpp -o fanControl.o

requestCurl.o: requestCurl.cpp config.h
	$(CXX) $(CPPFLAGS) -c requestCurl.cpp -o requestCurl.o

clean: 
	rm -f *.o
