Antenna Sweep System Readme
===============================

**Authors:** Colton Cox (ccox60@uco.edu), Nathan G Wiley (nwiley@uco.edu)

This C# program facilitates electromagnetic measurements using a Vector Network Analyzer (VNA) and an antenna setup. The program connects to the VNA, configures experiment parameters, performs a series of sweeps, and records the data in both CSV and SQL formats.

## Prerequisites
- Microsoft .NET Core SDK
- MiQVNA API
- MegiQ VNA hardware
- Arduino board for antenna control

## Usage
1. **Connecting to MegiQ**
   - Ensure that the MegiQ VNA hardware is properly connected.
   - Run the program, and it will attempt to connect to the VNA.
2. **Connecting to Antennas**
   - Connect an Arduino board to the specified COM port.
   - The program will establish a connection to the antennas.
3. **Performing a Sweep**
   - The program will prompt for experiment details such as code, object name, frequency range, steps, and number of antennas.
4. **Saving Data**
   - Data will be saved in both CSV and SQL formats. The CSV file will be named based on the experiment parameters.
5. **Repeating or Exiting**
   - After a scan is completed, the program will prompt if you want to scan again.

## Error Handling
- If a connection to MegiQ or antennas fails, the program will prompt for a retry or exit.

## Functions
- `ConnectToMegiQ()`: Connects to the MegiQ VNA hardware.
- `CloseMegiQ()`: Closes the MegiQ VNA process.
- `ConnectToAntennas()`: Connects to the Arduino controlling the antennas.
- `PromptUserInput()`: Prompts the user for experiment details.
- `Switch(int rfPath)`: Switches the signal path on the switch.
- `ProcessTraceValues(mvnaIQData data)`: Processes the trace values obtained during a sweep.
- `Sweep()`: Performs the sweep algorithm.
- `WriteToCSV(string filePath)`: Writes the data to a CSV file.
- `WriteToSQL(string fullExpName)`: Writes the data to an SQL database.

## Classes
- `ComplexData`: Represents a complex data point with real and imaginary parts.
- `AppDbContext`: DbContext for interacting with the SQL database.

## Database
- Server: `(localdb)\mssqllocaldb`
- Database: `ComplexDataDb`