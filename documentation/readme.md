Microwave Antenna Sweep and Imaging System Readme
===============================

**Authors:** Colton Cox (<ccox60@uco.edu>), Nathan G Wiley (<nwiley@uco.edu>)

This project encompasses two interconnected systems: the Antenna Sweep and the Microwave Imaging programs. Both systems work together to facilitate electromagnetic measurements using a Vector Network Analyzer (VNA) and a custom antenna setup.

## Antenna Sweep Program
### Overview
The Antenna Sweep Program is implemented in C# and is designed to work in tandem with the Microwave Imaging System. It enables electromagnetic measurements using a Vector Network Analyzer (VNA) and a custom antenna setup. The program connects to the VNA, configures experiment parameters, performs a series of sweeps, and records the data in both CSV and SQL formats.

### Prerequisites
- Microsoft .NET Core SDK
- MiQVNA API
- MiQVNA sofware and API

### Usage
1. **Connecting to MegiQ**
   - Ensure that the MegiQ VNA software is and API are installed correctly.
2. **Connecting to AnThe project requires installationtennas**
   - Connect an Arduino board to the specified COM port.
   - The program will establish a connection to the antennas.
3. **Performing a Sweep**
   - Run the program, and it will attempt to connect to the VNA.
   - The program will prompt for experiment details such as code, object name, frequency range, steps, and number of antennas.
   - Data will be saved in both CSV and SQL formats. The CSV file and SQL table will be named based on the experiment parameters.
4. **Repeating or Exiting**
   - After a scan is completed, the program will prompt if you want to scan again.

## Microwave Imaging System
### Overview
The Microwave Imaging System processes IQ data from the VNA system and generates a microwave image using the Delay-and-Sum algorithm. The system is implemented in C and consists of several components:
- `main.c`: Contains the main program logic and orchestrates the execution of the entire microwave imaging process.
- `ImagingDomain.c` and `ImagingDomain.h`: Implements functions for generating the imaging domain, a critical component of the Delay-and-Sum algorithm.
- `DelayAndSum.c` and `DelayAndSum.h`: Implements the Delay-and-Sum algorithm to compute the imaging based on the IQ data, channel configurations, and antenna locations.
- `CSVReader.c` and `CSVReader.h`: Provides functions for reading data from CSV files, handling the extraction of channel names, frequencies, antenna locations, and IQ data sets.
- `CallHeatmap.c` and `CallHeatmap.h`: Facilitates the generation of a heatmap from the radar imaging data. The `callHeatmap` function invokes GNUplot to produce visual outputs.
- `Config.h`: Contains various constants and configurations used throughout the program.
- `PlotImage.p`: A GNUplot script responsible for generating the heatmap visualization from the output CSV file.
- `makefile`: Automates the build process for the microwave imaging system.

### Prerequisites
   - C Compiler (e.g., GCC)
   - GNUplot
   - C Standard Library

### Usage
1. Compile the code using a C compiler.
2. Ensure the necessary CSV files are in the same directory as the executable.
3. Run the program. It will generate microwave imaging data in `output.csv`.
4. The program will generate a heatmap visualization as an image using the GNUplot script command `gnuplot -p PlotImage.p`.