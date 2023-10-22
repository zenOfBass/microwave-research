Microwave Antenna Sweep and Imaging System Documentation
===============================

## Table of Contents

1. [Overview](#overview)
2. [Installation](#installation)
3. [Using the Microwave Imaging System](#using-the-microwave-imaging-system)
4. [Using the Antenna Sweep Program](#using-the-antenna-sweep-program)
5. [FAQs and Troubleshooting](#faqs-and-troubleshooting)

---

## Overview
This integrated system comprises two distinct components: the Antenna Sweep and the Microwave Imaging programs. Together, they enable electromagnetic measurements using a Vector Network Analyzer (VNA) and imaging with the resulting data. This documentation is tailored for individuals with a basic understanding of electromagnetism, microwave imaging, and software operation. Some familiarity with C and C# will be beneficial.

---

## Installation
### Prerequisites
- For the Antenna Sweep Program:
   - Microsoft .NET Core SDK
   - MiQVNA API
   - MegiQ VNA hardware
   - Arduino board for antenna control
- For the Microwave Imaging System: 
   - C Compiler (e.g., GCC)
   - GNUplot
   - C Standard Library

### Antenna Sweep Program
The Antenna Sweep Program is designed to complement the Microwave Imaging System. It enables electromagnetic measurements using a VNA and a custom antenna setup. The program connects to the VNA, configures experiment parameters, performs sweeps, and records data in CSV and SQL formats.

### Microwave Imaging System
The Microwave Imaging System processes IQ data from the VNA system and generates a microwave image using the Delay-and-Sum algorithm. This system is implemented in C and consists of several components:
- `main.c`: Contains the main program logic.
- `ImagingDomain.c` and `ImagingDomain.h`: Generates points in the imaging domain.
- `DelayAndSum.c` and `DelayAndSum.h`: Implements the Delay-and-Sum algorithm.
- `CSVReader.c` and `CSVReader.h`: Provides functions for reading data from CSV files.
- `CallHeatmap.c` and `CallHeatmap.h`: Facilitates the generation of a heatmap.
- `Config.h`: Contains various constants and configurations.
- `PlotImage.p`: A GNUplot script for generating the heatmap visualization.
- `makefile`: Automates the build process.

---

## Using the Antenna Sweep Program
1. Connect the MegiQ VNA hardware properly.
2. Run the program. It will attempt to connect to the VNA.
3. Connect an Arduino board to the specified COM port.
4. The program will establish a connection to the antennas.
5. Follow on-screen prompts to perform sweeps and save data.

---

## Using the Microwave Imaging System
1. Compile the code using a C compiler.
2. Ensure the required CSV files are in the same directory as the executable.
3. Run the program. It will generate microwave imaging data in `output.csv`.
4. To generate a heatmap visualization, execute the GNUplot script using the command `gnuplot -p PlotImage.p`.

---

## FAQs and Troubleshooting
### Microwave Imaging System
1. **I'm encountering memory allocation errors. What should I do?**
   - Ensure that the system meets the prerequisites. Double-check CSV files and their format.

2. **I'm having trouble generating a heatmap. What could be the issue?**
   - Verify that GNUplot is installed and properly configured.

### Antenna Sweep Program
1. **The program is not connecting to the MegiQ VNA. What should I check?**
   - Confirm that the MegiQ VNA hardware is connected correctly and the MiQVNA API is installed.

2. **The Arduino board isn't connecting. What could be the problem?**
   - Check the COM port connection and ensure the Arduino board is operational.

---