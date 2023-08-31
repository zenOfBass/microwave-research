# makefile
# Revised 8/31/2023
# Nathan G Wiley - nwiley@uco.edu

# Compiler
CC = gcc

# Flags
CFLAGS = -Wall

# Output name
OUTPUT_NAME = a.exe

# Source files
SRCS = main.c ImagingDomain.c CSVReader.c CallHeatmap.c DelayAndSum.c

# Object files
OBJS = $(SRCS:.c=.o)

# OS detection
ifeq ($(OS),Windows_NT)
    RM = del /Q
    EXE_EXT = .exe
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        RM = rm -f
        EXE_EXT =
    endif
endif

# Targets
all: $(OUTPUT_NAME)

$(OUTPUT_NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJS) $(OUTPUT_NAME)$(EXE_EXT)