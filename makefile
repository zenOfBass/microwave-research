a.exe: main.o ImagingDomain.o
	gcc main.o ImagingDomain.o

ImagingDomain.o: ImagingDomain.c ImagingDomain.h
	gcc -c ImagingDomain.c

main.o: main.c ImagingDomain.h
	gcc -c main.c

clean:
	rm *.o a.exe