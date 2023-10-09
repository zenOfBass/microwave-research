a.exe: main.o ImagingDomain.o CSVReader.o CallHeatmap.o DelayAndSum.o
	gcc main.o ImagingDomain.o CSVReader.o CallHeatmap.o DelayAndSum.o

ImagingDomain.o: ImagingDomain.c ImagingDomain.h Config.h
	gcc -c -Wall ImagingDomain.c

CSVReader.o: CSVReader.c CSVReader.h Config.h
	gcc -c -Wall CSVReader.c

CallHeatmap.o: CallHeatmap.c CallHeatmap.h Config.h
	gcc -c -Wall CallHeatmap.c

DelayAndSum.o: DelayAndSum.c DelayAndSum.c Config.h
	gcc -c -Wall DelayAndSum.c

main.o: main.c ImagingDomain.h CSVReader.h CallHeatmap.h Config.h
	gcc -c -Wall main.c

clean:
	del *.o a.exe

