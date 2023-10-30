a.exe: ConfigurationSpace.o main.o Util.o ImagingDomain.o
	g++ main.o ConfigurationSpace.o Util.o ImagingDomain.o

ConfigurationSpace.o: ConfigurationSpace.cpp ConfigurationSpace.h Util.h ImagingDomain.h
	g++ -c -Wall -g ConfigurationSpace.cpp

main.o: main.cpp ConfigurationSpace.h
	g++ -c -Wall -g main.cpp

Util.o: Util.cpp Util.h
	g++ -c -Wall -g Util.cpp

ImagingDomain.o: ImagingDomain.cpp ImagingDomain.hpp
	g++ -c -Wall -g ImagingDomain.cpp

clean:
	del *.o a.exe