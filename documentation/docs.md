Microwave Antenna Sweep and Imaging System Documentation
===============================

## Table of Contents
1. [Overview](#overview)
2. [Installation](#installation)
3. [Antenna Sweep System](#antenna-sweep-system)
4. [Microwave Imaging System](#microwave-imaging-system)
5. [FAQs and Troubleshooting](#faqs-and-troubleshooting)
6. [Version Control and Change Logs](#version-control-and-change-logs)

---

## Overview
This sytem is comprised of two distinct components: the Antenna Sweep and the Microwave Imaging sytems. Together, they enable electromagnetic measurements using a Vector Network Analyzer (VNA) and imaging with the resulting data. This documentation is tailored for individuals with a basic understanding of electromagnetism, microwave imaging, and software operation. Some familiarity with C and C# will be beneficial.

---

## Installation
The programs in this project require installation on a Windows or Linux system.

### Prerequisites
- For the Antenna Sweep System:
   - Microsoft .NET Core SDK
   - MiQVNA sofware and API
   - Arduino board for antenna control
- For the Microwave Imaging System: 
   - C Compiler (e.g., GCC)
   - GNUplot
   - C Standard Library

---
## Antenna Sweep System
The Antenna Sweep System is designed to complement the Microwave Imaging System. It enables electromagnetic measurements using a VNA and a custom antenna setup. The program connects to the VNA, configures experiment parameters, performs sweeps, and records data in CSV and SQL formats.

### Using the Antenna Sweep System
1. Connect an Arduino board to the specified COM port.
2. Run the program. It will attempt to connect to the VNA.
3. The program will establish a connection to the antennas.
4. Follow on-screen prompts to perform sweeps and save data.

---

## Microwave Imaging System
The Microwave Imaging System processes IQ data from the VNA and generates an image using the Delay-and-Sum algorithm. This system is implemented in C and consists of several components:
- `main.c`: Contains the main program logic.
- `ImagingDomain.c` and `ImagingDomain.h`: Generates points in the imaging domain.
- `DelayAndSum.c` and `DelayAndSum.h`: Implements the Delay-and-Sum algorithm.
- `CSVReader.c` and `CSVReader.h`: Provides functions for reading data from CSV files.
- `CallHeatmap.c` and `CallHeatmap.h`: Facilitates the generation of a heatmap.
- `Config.h`: Contains various constants and configurations.
- `PlotImage.p`: A GNUplot script for generating the heatmap visualization.
- `makefile`: Automates the build process.

### Using the Microwave Imaging System
1. Compile the code using a C compiler.
2. Ensure the required CSV files are in the same directory as the executable.
3. Run the program. It will generate microwave imaging data in `output.csv`.
4. The program will generate a heatmap visualization as an image using the GNUplot script command `gnuplot -p PlotImage.p`.

---

## FAQs and Troubleshooting
### Antenna Sweep Program
1. **The program is not connecting to the MegiQ VNA. What should I check?**
   - Confirm that the MegiQ VNA software and API are installed.
2. **The Arduino board isn't connecting. What could be the problem?**
   - Check the COM port connection and ensure the Arduino board is operational.

### Microwave Imaging System
1. **I'm encountering memory allocation errors. What should I do?**
   - Ensure that the system meets the prerequisites. Double-check CSV files and their format.
2. **I'm having trouble generating a heatmap. What could be the issue?**
   - Verify that GNUplot is installed and properly configured.

---

## Version Control and Change Logs
The change logs for all program code files are kept here in the same folder as this file. All notable changes to this project will be documented there. The format used is based on *[Keep a Changelog](https://keepachangelog.com/en/1.0.0/)*, and this project adheres to *[Semantic Versioning](https://semver.org/spec/v2.0.0.html)* for version control. A template for newly released versions is also here in the documentation folder, and contains helpful instructions for recording version documentation.

---