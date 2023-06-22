a.exe: main.o ImagingDomain.o csvreader.o
	gcc main.o ImagingDomain.o csvreader.o

ImagingDomain.o: ImagingDomain.c ImagingDomain.h
	gcc -c ImagingDomain.c

csvreader.o: csvreader.c csvreader.h
	gcc -c csvreader.c

main.o: main.c ImagingDomain.h
	gcc -c main.c

clean:
	rm *.o a.exe