using MiQVNA;
using System.IO.Ports;

DateTime startTime = DateTime.Now;

Console.WriteLine("Program boot.");

// Number of iterations (sweeps) to perform
int defaultIterations = 77;
int iterations = 8;

mvnaVNAMain VNA = new mvnaVNAMain();
VNA.Connect();

// Create an empty log session
mvnaSession session = VNA.OpenSession("");
mvnaMeasurement measurement;

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

// Serial parameters for interfacing with control arm
/* string comPortArm = "COM17"; // COM port used for communicating with control arm
int armBaudrate = 115200;   // Baudrate for control arm
int armTimeout = 1000;      // Timeout in milliseconds
SerialPort arm = null;
try
{
    arm = new SerialPort(comPortArm, antBaudrate);
    arm.ReadTimeout = armTimeout;
    arm.Open();
}
catch (Exception ex)
{
    Console.WriteLine($"Couldn't find BlackBox on {comPortArm} - Is it connected? Ensure motor control program isn't connected.");
    Console.WriteLine($"Error message: {ex.Message}");
} */

for (int j = 0; j < iterations; j++)
{
    // RaiseToCompressor(arm);
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
            if (session == null)
                return;
            if (VNA.get_Measurement().get_Name() == "[new]")
                session.Measurements.AddItem(VNA.get_Measurement(), VNA.get_Measurement().get_Name() + "NEW ITEM", DateTime.Now);
            else
                session.Measurements.AddItem(VNA.get_Measurement(), VNA.get_Measurement().get_Name() + "-NEW", DateTime.Now);
            //measurement = VNA.get_Measurement();
            //mvnaTraceSet trace = measurement.TraceSet;
            //double QVal1 = VNA.TraceSet.Traces[transmittingAntenna].Channels["S11"].DataSet["Through"].get_QValue(1);
        }
    }
}

session.SaveSession("Test", false, mvnaVNADataOptions.mvnaVDO_DATA);

// Calculate and print the total time
TimeSpan totalTime = DateTime.Now - startTime;
Console.WriteLine("Testing process has finished.");

// Close everything and report total time
antennas.Close();
// arm.Close();
VNA.Disconnect();
Console.WriteLine($"Total time: {totalTime.TotalSeconds} seconds");

static void SendGCode(SerialPort arm, string gcode)
{
    // Ensure the G-code string ends with a newline character
    gcode = gcode.Trim() + "\n";
    arm.Write(gcode); // Write the G-code to the control arm using serial communication
    Console.WriteLine($"Code: {gcode.Trim()} sent");

    while (true)
    {
        string response = arm.ReadLine().Trim();
        if (response == "ok")
        {
            break; // Exit the loop when the 'ok' response is received
        }
        else if (response.StartsWith("error"))
        {
            throw new Exception(response); // Raise an exception if the response starts with 'error'
        }
        Thread.Sleep(100); // Short delay before reading the next response
    }
}

static void RaiseToCompressor(SerialPort arm)
{
    SendGCode(arm, "$X");
    SendGCode(arm, "G10 P0 L20 Y0");
    SendGCode(arm, "$J=G91G21Y500F3600");
    Thread.Sleep(10000);
    SendGCode(arm, "G90\nG21\nG0 Y0");
}

static void Switch(SerialPort antennas, int rfPath)
{
    string rfPathStr = rfPath.ToString();                   // Convert the RF path to a string
    antennas.Write(rfPathStr);                              // Write the RF path to the antennas using serial communication
    Console.WriteLine($"Switching to RF path {rfPathStr}"); // Print the RF path to the console
}