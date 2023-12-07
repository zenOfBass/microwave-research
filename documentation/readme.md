Microwave Antenna Sweep and Imaging System Readme
===============================

**Authors:** Colton Cox (<ccox60@uco.edu>), Nathan G Wiley (<nwiley@uco.edu>)

This project encompasses two interconnected systems: the Antenna Sweep and the Microwave Imaging programs. Both systems work together to facilitate electromagnetic measurements using a Vector Network Analyzer (VNA) and a custom antenna setup.

## Antenna Sweep Program
### Overview
The Antenna Sweep Program is implemented in C# and is designed to work in tandem with the Microwave Imaging System. It enables electromagnetic measurements using a Vector Network Analyzer (VNA) and a custom antenna setup. The program connects to the VNA, configures experiment parameters, performs a series of sweeps, and records the data in both CSV and SQL formats.

### File Structure
- `AppDbContext.cs`: DbContext for interacting with the SQL database.
- `ComplexData.cs`: A record representing a complex data point with real and imaginary parts. This record is utilized to store data obtained during sweeps.
- `Connection.cs`: A record encapsulating information required for connecting to the MegiQ VNA hardware and the Arduino controlling the antennas. It includes details such as COM port information.
- `Experiment.cs`: A struct representing an electromagnetic experiment. It encapsulates experiment parameters such as frequency range, steps, and the number of antennas. The struct is used in conjunction with the ExperimentBuilder for creating experiment instances.
- `ExperimentBuilder.cs`: Builder class for constructing Experiment instances.
- `ISweepStrategy.cs`: Interface for sweep strategies, facilitating future expansion.
- `MonoStaticSweep.cs`: Concrete class implementing the mono-static sweep strategy.
- `MultiStaticSweep.cs`: Concrete class implementing the multi-static sweep strategy.
- `Program.cs`: Contains the main program logic and orchestrates the execution of the entire microwave sweeping process.
- `Sweeper`: Implements context for the sweeping algorithms.
- `Writer`: Provides methods to write data to CSV and SQL.

### Prerequisites
- Microsoft .NET Core SDK
- MiQVNA API
- MiQVNA sofware and API

### Usage
1. **Connecting to MegiQ**
   - Ensure that the MegiQ VNA software and API are installed correctly.
2. **Connecting to Antennas**
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
The Microwave Imaging System processes IQ data from the VNA system and generates a microwave image using the Delay-and-Sum algorithm. The system is implemented in C and consists of several components.

### File Structure
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
1. **Data and Configuration**
   - Ensure the necessary CSV files are in the `data/` and `configuration/` directories.
   - Confirm that the correct files with the correct values are in the `configuration/` directory.
2. **Compilation**
   - Compile the code using a C compiler.
3. **Run the Program** 
   - The program will generate microwave imaging data in `output.csv` file.
   - A heatmap visualization as an image using the GNUplot script command `gnuplot -p PlotImage.p` will generate from the resulting data, which will pop-up in a seperate window when it is completed.