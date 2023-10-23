/**********************************
/ AntennaSweep.cs            
/ Colton Cox - ccox60@uco.edu
/ Nathan G Wiley - nwiley@uco.edu
/ University of Central Oklahoma
/ See changelog.md for detailed changes 
**********************************/

using Microsoft.EntityFrameworkCore;
using MiQVNA;
using System.Diagnostics;
using System.IO.Ports;
using System.Numerics;


// VNA,MegIQ, and experiment variables
mvnaVNAMain vna;
double doubleMinFreq, doubleMaxFreq = 0;
int intFreqSteps, intNumAntennas, totalTraces = 0;
string minFreq, maxFreq, freqSteps, numAntennas, objName, code;

// Serial antennas interfacing variables
string comPortAnt = "COM19"; // COM port used for communicating with antennas
int antBaudrate = 115200;    // Baudrate for antennas
int antTimeout = 100;        // Timeout in milliseconds
SerialPort antennas = null;  // Initialize serial port for antennas

// Sweep algorithm variables
double qVal, iVal;       // Variables for I and Q values
int row, col = 0;        // Row and column counters for complexData
int transmittingAntenna;
Complex[,] complexData;

ConnectToMegiQ();
//mvnaParameter freq = VNA.get_Measurement().Parameters["VNA_FREQUENCY"];

ConnectToAntennas();

while (true)
{
    PromptUserInput();
    //freq.Update();
    string fullExpName = code + "_" + objName + "_" + minFreq + "_" + maxFreq + "_" + freqSteps + "_" + numAntennas;
    string filePath = "data/" + code + "-" + objName + "_" + minFreq + "-" + maxFreq + "_" + freqSteps + "_" + numAntennas + "_0.csv";

    try
    {
        Console.WriteLine("Scan starting.");                                            // Print a startup message
        DateTime startTime = DateTime.Now;                                              // Get the current time for measuring execution time
        complexData = new Complex[intFreqSteps, totalTraces];                           // Set the number of rows and columns based on user input
        Sweep();                                                                        // Start sweep alogrithm
        WriteToCSV(filePath);                                                           // Write the data to a CSV file
        WriteToSQL(fullExpName);                                                        // Write the data to the SQL database
        TimeSpan totalTime = DateTime.Now - startTime;                                  // Calculate the total time
        Console.WriteLine("Scan has finished.");
        Console.WriteLine($"Total time in minutes: {totalTime.TotalMinutes} minutes."); // Report total time
    }
    catch (Exception ex)
    {
        Console.WriteLine($"Error message: {ex.Message}\nExiting scan."); // Display the specific error message
    }
    Console.WriteLine("Would you like to scan again? Y/N: ");
    while (true)
    {
        string repeat = Console.ReadLine();
        if (repeat != null) repeat = repeat.ToUpper();
        if (repeat == "Y") break; // Repeat
        else if (repeat == "N")   // Close all connections
        {
            antennas.Close();
            vna.Disconnect();
            CloseMegiQ();
        }
        else Console.WriteLine("Invalid input. Please enter Y or N");
    }
}

#region Functions

void ConnectToMegiQ()
{
    while (true)
    {
        try
        {
            Console.WriteLine("Connecting to VNA.");
            vna = new mvnaVNAMain(); // Open MegIQ and create VNA instance
            vna.Connect();           // Connect to VNA
            break;
        }
        catch
        {
            Console.WriteLine("Failed to connect. Retry? Y/N:");
            while (true)
            {
                string retry = Console.ReadLine();
                if (retry != null) retry = retry.ToUpper();
                if (retry == "Y")
                {
                    CloseMegiQ();
                    break;
                }
                else if (retry == "N") Environment.Exit(1); // Exit the program with code 1
                else Console.WriteLine("Invalid input. Please enter Y or N");
            }
        }
    }
}

static void CloseMegiQ() // Function to close the MegiQ process
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
            catch
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

void ConnectToAntennas()
{
    try
    {
        Console.WriteLine("Connecting to antennas.");
        antennas = new SerialPort(comPortAnt, antBaudrate); // Create a new SerialPort object with specified port and baud rate
        antennas.ReadTimeout = antTimeout;                  // Set the read timeout in milliseconds
        antennas.Open();                                    // Open the serial port for communication
    }
    catch (Exception ex)
    {
        Console.WriteLine($"Couldn't find Arduino on {comPortAnt} - Is it connected?"); // Display error message
        Console.WriteLine($"Error message: {ex.Message}");                              // Display the specific error message
        Environment.Exit(1);                                                            // Exit the program with exit code 1
    }
}

void PromptUserInput()
{
    Console.WriteLine("Experiment Code: ");
    while (true)
    {
        code = Console.ReadLine();
        if (string.IsNullOrEmpty(code)) Console.WriteLine("Invalid input. Experiment Code cannot be empty.");
        else break;
    }

    Console.WriteLine("Object Name: ");
    while (true)
    {
        objName = Console.ReadLine();
        if (string.IsNullOrEmpty(objName)) Console.WriteLine("Invalid input. Object Name cannot be empty.");
        else break;
    }

    Console.WriteLine("Minimum Frequency: ");
    while (true)
    {
        minFreq = Console.ReadLine();
        if (double.TryParse(minFreq, out doubleMinFreq) && doubleMinFreq > 0) break;
        else Console.WriteLine("Invalid input. Please enter a valid positive value.");
    }
    //freq.StartValue = doubleMinFreq;

    Console.WriteLine("Maximum Frequency: ");
    while (true)
    {
        maxFreq = Console.ReadLine();
        if (double.TryParse(maxFreq, out doubleMaxFreq) && doubleMaxFreq > 0 && doubleMaxFreq > doubleMinFreq) break;
        else Console.WriteLine("Invalid input. Please enter a valid positive value greater than the minimum frequency.");
    }
    //freq.StopValue = doubleMaxFreq; ;

    Console.WriteLine("Number of Frequency Steps: ");
    while (true)
    {
        freqSteps = Console.ReadLine();
        if (int.TryParse(freqSteps, out intFreqSteps) && intFreqSteps > 0) break;
        else Console.WriteLine("Invalid input. Please enter a valid positive integer value.");
    }
    //freq.Steps = intFreqSteps;
    intFreqSteps++;

    Console.WriteLine("Number of Antennas: ");
    while (true)
    {
        numAntennas = Console.ReadLine();
        if (int.TryParse(numAntennas, out intNumAntennas) && intNumAntennas > 0) break;
        else Console.WriteLine("Invalid input. Please enter a valid positive integer value.");
    }
    totalTraces = 2 * intNumAntennas * (intNumAntennas - 1);
}

void Switch(int rfPath) // Function to switch signal path on the switch
{
    string rfPathStr = rfPath.ToString();                   // Convert the RF path to a string
    antennas.Write(rfPathStr);                              // Write the RF path to the antennas using serial communication
    Thread.Sleep(3000);                                     // Pause for 3 seconds
    Console.WriteLine($"Switching to RF path {rfPathStr}"); // Print the RF path to the console
}

void ProcessTraceValues(mvnaIQData data)
{
    foreach (mvnaIQ val in data.Values)
    {
        iVal = val.IVal;                                 // Get the I value
        qVal = val.QVal;                                 // Get the Q value
        complexData[row, col] = new Complex(iVal, qVal); // Store IQ data together in the 2D array of complex numbers
        row++;                                           // Move to next row
    }
}

void Sweep()
{
    for (int i = 1; i < intNumAntennas; i++)
    {
        Switch(i + 10);          // Change the signal path on the switch to the RF channel (i + 10)
        transmittingAntenna = i; // Set transmitting antenna

        for (int j = 1; j < intNumAntennas; j++)
        {
            if (j == transmittingAntenna)
            {
                continue; // Skip this iteration if i is the same as the transmitting antenna number
            }
            else
            {
                Switch(j);                                                                     // Change the signal path on the switch to the RF channel (j)
                vna.RunSweepOnce();                                                            // Initiate sweep in MegiQ
                row = 0;                                                                       // Start at first row
                ProcessTraceValues(vna.TraceSet.Traces[1].Channels["S21"].DataSet["Through"]); // Loop over 21 trace data
                row = 0;                                                                       // Start at first row again
                col++;                                                                         // Go to next column
                ProcessTraceValues(vna.TraceSet.Traces[1].Channels["S12"].DataSet["Through"]); // Loop over 12 trace data
            }
            col++; // Go to next column
        }
    }
}

void WriteToCSV(string filePath)
{
    using StreamWriter writer = new StreamWriter(filePath);
    for (int i = 0; i < intFreqSteps; i++) // Loop over columns
    {
        for (int j = 0; j < totalTraces; j++)  //  Loop over rows
        {
            Complex value = complexData[i, j];                  // Set the value to be recorded from the 2D array
            writer.Write($"{value.Real} + {value.Imaginary}i"); // Write the value to the .csv file

            if (j < totalTraces - 1)    // If this isn't the final column . . .
            {
                writer.Write(","); // . . . then end the number with a comma to seperate values
            }
        }
        writer.WriteLine();
    }
}

void WriteToSQL(string fullExpName)
{
    using var db = new AppDbContext(); // Write the SQL database
    db.Database.EnsureCreated();
    db.Database.ExecuteSqlRaw($"CREATE TABLE {fullExpName} (Id int PRIMARY KEY IDENTITY(1,1), Real float, Imaginary float)"); // Populate the table with data

    for (int i = 0; i < intFreqSteps; i++) // Populate the table with data
    {
        for (int j = 0; j < totalTraces; j++)
        {
            var value = complexData[i, j];
            db.ComplexData.Add(new ComplexData { Real = value.Real, Imaginary = value.Imaginary });
        }
    }
    db.SaveChanges();
}

#endregion