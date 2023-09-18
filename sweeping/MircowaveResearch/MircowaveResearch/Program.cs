/*
AntennaSweep.cs
Revised 9/14/2023
Colton Cox - ccox60@uco.edu
Nathan G Wiley - nwiley@uco.edu
*/

using MiQVNA;
using System.Diagnostics;
using System.IO.Ports;
using System.Numerics;

DateTime startTime = DateTime.Now;  // Get the current time for measuring execution time
Console.WriteLine("Program boot."); // Print a startup message

// Define program parameters
int iterations = 8;                                         // Number of iterations (sweeps)
double qVal;                                                // Variable for Q value
double iVal;                                                // Variable for I value
int frequencies = 201;                                      // Number of frequency points
int traces = 112;                                           // Number of traces
Complex[,] complexData = new Complex[frequencies, traces];  // 2D array for complex data
string filePath = "Test.csv";                               // File path for output data
int col = 0;                                                // Column counter for complexData
mvnaVNAMain VNA = new mvnaVNAMain();                        // Initialize VNA
VNA.Connect();                                              // Connect to VNA
mvnaIQData S21;                                             // Variable for S21 data
mvnaIQData S12;                                             // Variable for S12 data

// Serial parameters for interfacing with antennas
string comPortAnt = "COM19";    // COM port used for communicating with antennas
int antBaudrate = 115200;       // Baudrate for antennas
int antTimeout = 100;           // Timeout in milliseconds
SerialPort antennas = null;     // Initialize serial port for antennas

// Attempt to connect to antennas
try
{
    antennas = new SerialPort(comPortAnt, antBaudrate); // Create a new SerialPort object with specified port and baud rate
    antennas.ReadTimeout = antTimeout;                  // Set the read timeout in milliseconds
    antennas.Open();                                    // Open the serial port for communication
}
catch (Exception ex)
{
    Console.WriteLine($"Couldn't find Arduino on {comPortAnt} - Is it connected?"); // Display error message
    Console.WriteLine($"Error message: {ex.Message}");                              // Display the specific error message
}

mvnaSession Session = VNA.OpenSession("");           // Create a new VNA session object
mvnaMeasurement Measurement = VNA.get_Measurement(); // Get access to the most recent measurement

foreach (mvnaMeasurement mea in Session.Measurements)
{
    foreach (mvnaParameter par in mea.Parameters)
    {
        par.Steps = 200;
        par.StartValue = 1800;
        par.StopValue = 3200;
    }
}

// Sweeping process
for (int j = 0; j < iterations; j++)
{
    Switch(antennas, j + 11);        // Change the signal path on the switch to the RF channel (j + 11)
    int transmittingAntenna = j + 1; // Set transmitting antenna

    for (int i = 0; i < iterations; i++)
    {
        if ((i + 1) == transmittingAntenna)
        {
            continue; // Skip this iteration if i + 1 is the same as the transmitting antenna number
        }
        else
        {
            Switch(antennas, i + 1);                                         // Change the signal path on the switch to the RF channel (i + 1)
            VNA.RunSweepOnce();                                              // Initiate sweep in MegiQ
            S21 = VNA.TraceSet.Traces[1].Channels["S21"].DataSet["Through"]; // Set data for for 21 channel
            S12 = VNA.TraceSet.Traces[1].Channels["S12"].DataSet["Through"]; // Set data for for 12 channel
            int row = 0;                                                     // Start at first row

            foreach (mvnaIQ val in S21.Values) //  Loop over 21 data
            {
                iVal = val.IVal;                                 // Get the I value
                qVal = val.QVal;                                 // Get the Q value
                complexData[row, col] = new Complex(iVal, qVal); // Store IQ data together in the 2D array of complex numbers
                row++;                                           // Move to next row
            }

            row = 0; // Start at first row
            col++;   // Go to next column

            foreach (mvnaIQ val in S12.Values) //  Loop over 12 data
            {
                iVal = val.IVal;                                 // Get the I value
                qVal = val.QVal;                                 // Get the Q value
                complexData[row, col] = new Complex(iVal, qVal); // Store IQ data together in the 2D array of complex numbers
                row++;                                           // Move to next row
            }
        }
        col++; // Got to next column
    }
}

// Writing the data to a CSV file
using (StreamWriter writer = new StreamWriter(filePath))
{
    for (int i = 0; i < frequencies; i++) // Loop over columns
    {
        for (int j = 0; j < traces; j++)  //  Loop over rows
        {
            Complex value = complexData[i, j];                  // Set the value to be recorded from the 2D array
            writer.Write($"{value.Real} + {value.Imaginary}i"); // Write the value to the .csv file

            if (j < traces - 1)    // If this isn't the final column . . .
            {
                writer.Write(","); // . . . then end the number with a comma to seperate values
            }
        }
        writer.WriteLine();
    }
}

// Calculate the total time
TimeSpan totalTime = DateTime.Now - startTime;
Console.WriteLine("Testing process has finished.");

// Close everything and report total time
antennas.Close();
VNA.Disconnect();
CloseMegiQ();
Console.WriteLine($"Total time: {totalTime.TotalSeconds} seconds");

// Function to switch signal path on the switch
static void Switch(SerialPort antennas, int rfPath)
{
    string rfPathStr = rfPath.ToString();                   // Convert the RF path to a string
    antennas.Write(rfPathStr);                              // Write the RF path to the antennas using serial communication
    Thread.Sleep(3000);                                     // Pause for 3 seconds
    Console.WriteLine($"Switching to RF path {rfPathStr}"); // Print the RF path to the console
}

// Function to close the MegiQ process
static void CloseMegiQ()
{
    Process[] processes = Process.GetProcessesByName("MiQVNA");
    if (processes.Length > 0)
    {
        foreach (Process process in processes)
        {
            try
            {
                process.CloseMainWindow(); // Close the main window of the process
                process.WaitForExit();     // Wait for the process to exit
                Console.WriteLine($"Process MiQVNA closed.");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error closing MiQVNA.");
            }
        }
    }
    else
    {
        Console.WriteLine($"MiQVNA does not appear to be running.");
    }
}