using MiQVNA;
using System.Numerics;


internal struct Experiment
{
    // Strings for name of experiment
    private readonly string fullExpName;
    private readonly string filePath;
    private string minFreq, maxFreq, freqSteps, numAntennas, objName, code;

    // Sweeping variables
    private readonly Connection connection;
    private readonly int totalTraces;
    private double doubleMinFreq, doubleMaxFreq;
    private int intFreqSteps, intNumAntennas;
    private int row, col; // Row and column counters for complexData
    private int transmittingAntenna;
    private Complex[,]? complexData = null;

    internal Experiment(Connection connection)
    {
        this.connection = connection ?? throw new ArgumentNullException(nameof(connection));

        doubleMinFreq = doubleMaxFreq = 0;
        intFreqSteps = intNumAntennas = totalTraces = 0;
        fullExpName = filePath = minFreq = maxFreq = freqSteps = numAntennas = objName = code = "";
        row = col = 0;
        transmittingAntenna = 0;

        PromptUserInput();

        intFreqSteps++;
        totalTraces = 2 * intNumAntennas * (intNumAntennas - 1);
        complexData = new Complex[intFreqSteps, totalTraces]; // Set the number of rows and columns based on user input
        fullExpName = $"Exp_{code}_{objName}_{minFreq}_{maxFreq}_{freqSteps}_{numAntennas}";
        filePath = $"data/{code}-{objName}_{minFreq}-{maxFreq}_{freqSteps}_{numAntennas}_0.csv";
    }

    internal void PromptUserInput()
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

    internal void Run()
    {
        Console.WriteLine("Scan starting.");                                                                                 // Print a startup message
        DateTime startTime = DateTime.Now;                                                                                   // Get the current time for measuring execution time
        Sweep();                                                                                                             // Start sweep alogrithm
        Writer.ToCSV(intFreqSteps, totalTraces, complexData, filePath);                                                      // Write the data to a CSV file
        Writer.ToSQL(intFreqSteps, totalTraces, complexData, filePath);                                                      // Write the data to the SQL database
        Console.WriteLine($"Scan has finished.\nTotal time in minutes: {(DateTime.Now - startTime).TotalMinutes} minutes."); // Report total time
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
}