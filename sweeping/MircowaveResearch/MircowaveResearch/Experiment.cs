using Microsoft.EntityFrameworkCore;
using MiQVNA;
using System.Numerics;


public struct Experiment
{
    // Strings for name of experiment
    private string fullExpName;
    private string filePath;
    private string minFreq, maxFreq, freqSteps, numAntennas, objName, code;

    // Sweeping variables
    Connection connection;
    private double doubleMinFreq, doubleMaxFreq;
    private int intFreqSteps, intNumAntennas, totalTraces;
    private int row, col;            // Row and column counters for complexData
    private int transmittingAntenna;
    private Complex[,]? complexData = null;

    public Experiment(Connection connection)
    {
        this.connection = connection;

        doubleMinFreq = doubleMaxFreq = 0;
        intFreqSteps = intNumAntennas = totalTraces = 0;
        fullExpName = filePath = minFreq = maxFreq = freqSteps = numAntennas = objName = code = "";
        row = col = 0;
        transmittingAntenna = 0;

        PromptUserInput();
        intFreqSteps++;
        totalTraces = 2 * intNumAntennas * (intNumAntennas - 1);
        complexData = new Complex[intFreqSteps, totalTraces];  // Set the number of rows and columns based on user input
        fullExpName = $"{code}_{objName}_{minFreq}_{maxFreq}_{freqSteps}_{numAntennas}";
        filePath = $"data/{code}-{objName}_{minFreq}-{maxFreq}_{freqSteps}_{numAntennas}_0.csv";
    }

    public void PromptUserInput()
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

        Console.WriteLine("Maximum Frequency: ");
        while (true)
        {
            maxFreq = Console.ReadLine();
            if (double.TryParse(maxFreq, out doubleMaxFreq) && doubleMaxFreq > 0 && doubleMaxFreq > doubleMinFreq) break;
            else Console.WriteLine("Invalid input. Please enter a valid positive value greater than the minimum frequency.");
        }

        Console.WriteLine("Number of Frequency Steps: ");
        while (true)
        {
            freqSteps = Console.ReadLine();
            if (int.TryParse(freqSteps, out intFreqSteps) && intFreqSteps > 0) break;
            else Console.WriteLine("Invalid input. Please enter a valid positive integer value.");
        }

        Console.WriteLine("Number of Antennas: ");
        while (true)
        {
            numAntennas = Console.ReadLine();
            if (int.TryParse(numAntennas, out intNumAntennas) && intNumAntennas > 0) break;
            else Console.WriteLine("Invalid input. Please enter a valid positive integer value.");
        }
    }

    public void Run()
    {
        Console.WriteLine("Scan starting.");                                            // Print a startup message
        DateTime startTime = DateTime.Now;                                              // Get the current time for measuring execution time
        Sweep();                                                                        // Start sweep alogrithm
        WriteToCSV();                                                                   // Write the data to a CSV file
        WriteToSQL();                                                                   // Write the data to the SQL database
        TimeSpan totalTime = DateTime.Now - startTime;                                  // Calculate the total time
        Console.WriteLine("Scan has finished.");
        Console.WriteLine($"Total time in minutes: {totalTime.TotalMinutes} minutes."); // Report total time
    }

    private void Sweep()
    {
        for (int i = 1; i <= intNumAntennas; i++)
        {
            Switch(i + 10);          // Change the signal path on the switch to the RF channel (i + 10)
            transmittingAntenna = i; // Set transmitting antenna

            for (int j = 1; j <= intNumAntennas; j++)
            {
                if (j == transmittingAntenna) continue; // Skip this iteration if i is the same as the transmitting antenna number
                else
                {
                    Switch(j);                                                                                // Change the signal path on the switch to the RF channel (j)
                    connection.VNA.RunSweepOnce();                                                            // Initiate sweep in MegiQ
                    row = 0;                                                                                  // Start at first row
                    ProcessTraceValues(connection.VNA.TraceSet.Traces[1].Channels["S21"].DataSet["Through"]); // Loop over 21 trace data
                    row = 0;                                                                                  // Start at first row again
                    col++;                                                                                    // Go to next column
                    ProcessTraceValues(connection.VNA.TraceSet.Traces[1].Channels["S12"].DataSet["Through"]); // Loop over 12 trace data
                }
                col++; // Go to next column
            }
        }
    }

    private readonly void Switch(int rfPath) // Function to switch signal path on the switch
    {
        string rfPathStr = rfPath.ToString();                   // Convert the RF path to a string
        connection.Antennas.Write(rfPathStr);                   // Write the RF path to the antennas using serial communication
        Thread.Sleep(3000);                                     // Pause
        Console.WriteLine($"Switching to RF path {rfPathStr}"); // Print the RF path to the console
    }

    private void ProcessTraceValues(mvnaIQData data)
    {
        foreach (mvnaIQ val in data.Values)
        {
            complexData[row, col] = new Complex(val.IVal, val.QVal); // Store IQ data together in the 2D array of complex numbers
            row++;                                                   // Move to next row
        }
    }

    private readonly void WriteToCSV()
    {
        using StreamWriter writer = new(filePath);
        for (int i = 0; i < intFreqSteps; i++) // Loop over columns
        {
            for (int j = 0; j < totalTraces; j++) //  Loop over rows
            {
                Complex value = complexData[i, j];                  // Set the value to be recorded from the 2D array
                writer.Write($"{value.Real} + {value.Imaginary}i"); // Write the value to the .csv file
                if (j < totalTraces - 1) writer.Write(",");
            }
            writer.WriteLine();
        }
    }

    private readonly void WriteToSQL()
    {
        using AppDbContext db = new(); // Write the SQL database
        db.Database.EnsureCreated();
        db.Database.ExecuteSqlRaw($"CREATE TABLE {fullExpName} (Id int PRIMARY KEY IDENTITY(1,1), Real float, Imaginary float)");

        for (int i = 0; i < intFreqSteps; i++) // Populate the table with data
        {
            for (int j = 0; j < totalTraces; j++)
            {
                Complex value = complexData[i, j];
                db.ComplexData.Add(new ComplexData { Real = value.Real, Imaginary = value.Imaginary });
            }
        }
        db.SaveChanges();
    }
}