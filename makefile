a.exe: main.o ImagingDomain.o CSVReader.o CallHeatmap.o
	gcc main.o ImagingDomain.o CSVReader.o CallHeatmap.o

ImagingDomain.o: ImagingDomain.c ImagingDomain.h
	gcc -c ImagingDomain.c

CSVReader.o: CSVReader.c CSVReader.h
	gcc -c CSVReader.c

CallHeatmap.o: CallHeatmap.c CallHeatmap.h
	gcc -c CallHeatmap.c

main.o: main.c ImagingDomain.h CSVReader.h CallHeatmap.h
	gcc -c main.c

clean:
	rm *.o a.exe