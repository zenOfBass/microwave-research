# Antenna Sweep System Readme
**Authors:** Colton Cox (ccox60@uco.edu), Nathan G Wiley (nwiley@uco.edu)

This C# command line program facilitates electromagnetic measurements using a Vector Network Analyzer (VNA) and an antenna setup. The program connects to the VNA, configures experiment parameters, performs a series of sweeps, and records the data in both CSV and SQL formats.

## Prerequisites
- Microsoft .NET Core SDK
- MiQVNA software and API
- Arduino board for antenna control

## Usage
1. **Connecting to MegiQ**
   - Ensure that the MegiQ VNA software and API are installed correctly.
2. **Connecting to Antennas**
   - Connect an Arduino board to the specified COM port.
   - The program will establish a connection to the antennas.
3. **Performing a Sweep**
   - Run the program, and it will attempt to connect to the VNA.
   - The program will prompt for experiment details such as code number, name of the object being scanned, frequency range of the sweep, total steps in the sweep, and the number of antennas connected.
   - Data will be saved in both CSV and SQL formats. The CSV file and SQL table will be named based on the experiment parameters.
4. **Repeating or Exiting**
   - After a scan is completed, the program will prompt if you want to scan again.

## Error Handling
- If the connection to MegiQ or antennas fails, the program will prompt for a retry or exit.
- If any of the sweeping processes fail the program will exit the current `Experiment`.
- If writing to CVS or SQL fails the `Writer` will catch and exit the process.

## Objects
- `AppDbContext`: DbContext for interacting with the SQL database.
- `Sweeper`: Implements sweeping algorithms, including multi-static and mono-static sweeps.
- `ISweepStrategy`: Interface for sweep strategies, facilitating future expansion.
   - `MultiStaticSweep`: Concrete class implementing the multi-static sweep strategy.
   - `MonoStaticSweep`: Concrete class implementing the mono-static sweep strategy.
      - `Switch(int rfPath)`: Switches the signal path on the switch.
      - `ProcessTraceValues(mvnaIQData data)`: Processes the trace values obtained during a sweep.
      - `Sweep()`: Performs the sweep algorithm.
- `ExperimentBuilder`: Builder class for constructing `Experiment` instances.
   - `SetUserInput()`: Prompts the user for experiment details.
- `Writer`: Provides methods to write data to CSV and SQL.
   - `WriteToCSV(string filePath)`: Writes the data to a CSV file.
   - `WriteToSQL(string fullExpName)`: Writes the data to an SQL database.
- `Experiment`: A struct representing an electromagnetic experiment. It encapsulates experiment parameters such as frequency range, steps, and the number of antennas. The struct is used in conjunction with the `ExperimentBuilder` for creating experiment instances.
- `ComplexData`: A record representing a complex data point with real and imaginary parts. This record is utilized to store data obtained during sweeps.
- `Connection`: A record encapsulating information required for connecting to the MegiQ VNA hardware and the Arduino controlling the antennas. It includes details such as COM port information.
   - `ConnectToMegiQ()`: Connects to the MegiQ VNA hardware.
   - `CloseMegiQ()`: Closes the MegiQ VNA process.
   - `ConnectToAntennas()`: Connects to the Arduino controlling the antennas.

## Database
- Server: `(localdb)\mssqllocaldb`
- Database: `ComplexDataDb`

## Notes
- Troubleshooting: If you encounter connection issues with MegiQ or the antennas, check that the drivers are installed correctly.
- Configuration: Verify that the Arduino board is configured to the correct COM port before running the program.
- Performance: For optimal performance, it's recommended to run the program on a machine with sufficient resources, especially when dealing with large datasets.