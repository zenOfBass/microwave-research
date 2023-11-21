using MiQVNA;
using System.Diagnostics;
using System.IO.Ports;


namespace MicrowaveResearch
{
    public record Connection(SerialPort? Antennas, mvnaVNAMain? VNA) : IDisposable
    {
        public readonly string? comPortAnt;  // COM port used for communicating with antennas
        public readonly int antBaudrate;     // Baudrate for antennas
        public readonly int antTimeout;      // Timeout in milliseconds
        private static Connection? instance; // Self instance for singleton pattern

        private Connection() : this(null, null)
        {
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

        public SerialPort? Antennas { get; private set; } = Antennas;
        public mvnaVNAMain? VNA { get; private set; } = VNA;

        private void ConnectToMegiQ()
        {
            while (true)
            {
                try
                {
                    Console.WriteLine("Connecting to VNA.");
                    VNA = new mvnaVNAMain(); // Open MegIQ and create VNA instance
                    VNA.Connect();           // Connect to VNA
                    break;
                }
                catch
                {
                    Console.WriteLine("Failed to connect. Retry? Y/N:");
                    while (true)
                    {
                        var retry = Console.ReadLine();
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
                Antennas = new SerialPort(comPortAnt ?? string.Empty, antBaudrate) { ReadTimeout = antTimeout }; // Create a new SerialPort object with specified port and baud rate                                      
                Antennas.Open();                                                                                 // Open the serial port for communication
            }

            catch (Exception ex)
            {
                Console.WriteLine($"Couldn't find Arduino on {comPortAnt} - Is it connected?"); // Display error message
                Console.WriteLine($"Error message: {ex.Message}");                              // Display the specific error message
                Environment.Exit(1);                                                            // Exit the program with exit code 1
            }
        }

        private static void CloseMegiQ() // Function to close the MegiQ process
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

        public void Dispose()
        {
            if (Antennas != null && Antennas.IsOpen) Antennas.Close(); // Close the serial port
            VNA!.Disconnect();                                         // Disconnect from the VNA
            CloseMegiQ();                                              // Close MegiQ resources
        }
    }
}