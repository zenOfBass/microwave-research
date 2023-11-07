using MiQVNA;
using System.Diagnostics;
using System.IO.Ports;


public class Connection : IDisposable
{
    private readonly string comPortAnt;         // COM port used for communicating with antennas
    private readonly int antBaudrate;           // Baudrate for antennas
    private readonly int antTimeout;            // Timeout in milliseconds
    private mvnaVNAMain vna;
    private SerialPort? antennas = null;        // Initialize serial port for antennas
    private static Connection? instance = null; // Self instance for singleton pattern

    private Connection()
    {
        vna = new mvnaVNAMain();
        comPortAnt = "COM19";
        antBaudrate = 115200;
        antTimeout = 100;

        ConnectToMegiQ();
        ConnectToAntennas();
    }

    // Method to get the singleton instance
    public static Connection Instance
    {
        get
        {
            instance ??= new Connection();
            return instance;
        }
    }

    private void ConnectToMegiQ()
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

    private void ConnectToAntennas()
    {
        try
        {
            Console.WriteLine("Connecting to antennas.");
            antennas = new SerialPort(comPortAnt, antBaudrate) { ReadTimeout = antTimeout }; // Create a new SerialPort object with specified port and baud rate                                      
            antennas.Open();                                                                 // Open the serial port for communication
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Couldn't find Arduino on {comPortAnt} - Is it connected?"); // Display error message
            Console.WriteLine($"Error message: {ex.Message}");                              // Display the specific error message
            Environment.Exit(1);                                                            // Exit the program with exit code 1
        }
    }

    public static void CloseMegiQ() // Function to close the MegiQ process
    {
        if (Process.GetProcessesByName("MiQVNA").Length > 0)
        {
            foreach (Process process in Process.GetProcessesByName("MiQVNA"))
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
        else Console.WriteLine($"MiQVNA does not appear to be running.");
    }

    public SerialPort GetAntennas() => antennas;

    public mvnaVNAMain GetVNA() => vna;

    public void Dispose()
    {
        if (antennas != null && antennas.IsOpen) antennas.Close(); // Close the serial port
        vna.Disconnect();                                          // Disconnect from the VNA
        CloseMegiQ();                                              // Close MegiQ resources
    }
}