/*
AntennaSweep.cs
Revised 8/30/2023
Nathan G Wiley - nwiley@uco.edu
*/

using MiQVNA;
using System.Diagnostics;
using System.IO.Ports;
using System.Numerics;

DateTime startTime = DateTime.Now;

Console.WriteLine("Program boot.");

int iterations = 8;
double qVal;
double iVal;
int frequencies = 201;
int traces = 112;
Complex[,] complexData = new Complex[frequencies, traces];
string filePath = "Test.csv";
int col = 0;
mvnaVNAMain VNA = new mvnaVNAMain();
VNA.Connect();
mvnaIQData S21;
mvnaIQData S12;

// Serial parameters for interfacing with antennas
string comPortAnt = "COM19"; // COM port used for communicating with antennas
int antBaudrate = 115200;    // Baudrate for antennas
int antTimeout = 100;        // Timeout in milliseconds
SerialPort antennas = null;
try
{
    antennas = new SerialPort(comPortAnt, antBaudrate);
    antennas.ReadTimeout = antTimeout;
    antennas.Open();
}
catch (Exception ex)
{
    Console.WriteLine($"Couldn't find Arduino on {comPortAnt} - Is it connected?");
    Console.WriteLine($"Error message: {ex.Message}");
}

mvnaSession Session = VNA.OpenSession("");
mvnaMeasurement Measurement = VNA.get_Measurement();

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
    Switch(antennas, j + 11); // Change the signal path on the switch to the RF channel (j + 11)
    int transmittingAntenna = j + 1;
    for (int i = 0; i < iterations; i++)
    {
        if ((i + 1) == transmittingAntenna)
        {
            continue; // Skip this iteration if i + 1 is the same as the transmitting antenna number
        }
        else
        {
            Switch(antennas, i + 1); // Change the signal path on the switch to the RF channel (i + 1)
            VNA.RunSweepOnce();      // Initiate sweep in MegiQ
            S21 = VNA.TraceSet.Traces[1].Channels["S21"].DataSet["Through"];
            S12 = VNA.TraceSet.Traces[1].Channels["S12"].DataSet["Through"];
            int row = 0;

            foreach (mvnaIQ val in S21.Values)
            {
                iVal = val.IVal;
                qVal = val.QVal;
                complexData[row, col] = new Complex(iVal, qVal);
                row++;
            }
            row = 0;
            col++;

            foreach (mvnaIQ val in S12.Values)
            {
                iVal = val.IVal;
                qVal = val.QVal;
                complexData[row, col] = new Complex(iVal, qVal);
                row++;
            }
        }
        col++;
    }
}

// Writing the data to a CSV file
using (StreamWriter writer = new StreamWriter(filePath))
{
    for (int i = 0; i < frequencies; i++)
    {
        for (int j = 0; j < traces; j++)
        {
            Complex value = complexData[i, j];
            writer.Write($"{value.Real} + {value.Imaginary}i");

            if (j < traces - 1)
            {
                writer.Write(",");
            }
        }
        writer.WriteLine();
    }
}

// Calculate and print the total time
TimeSpan totalTime = DateTime.Now - startTime;
Console.WriteLine("Testing process has finished.");

// Close everything and report total time
antennas.Close();
VNA.Disconnect();
CloseMegiQ();
Console.WriteLine($"Total time: {totalTime.TotalSeconds} seconds");

static void Switch(SerialPort antennas, int rfPath)
{
    string rfPathStr = rfPath.ToString();                   // Convert the RF path to a string
    antennas.Write(rfPathStr);                              // Write the RF path to the antennas using serial communication
    Thread.Sleep(3000);                                     // Pause for 3 seconds
    Console.WriteLine($"Switching to RF path {rfPathStr}"); // Print the RF path to the console
}

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
                Console.WriteLine($"Error closing process MiQVNA.");
            }
        }
    }
    else
    {
        Console.WriteLine($"MiQVNA does not appear to be running.");
    }
}