using MicrowaveResearch;
using MiQVNA;
using System.Numerics;


internal class MonoStaticSweep : ISweepStrategy
{
    public void Sweep(Connection connection,
                    int intNumAntennas,
                    int totalTraces,
                    Complex[,] complexData)
    {
        for (int i = 1; i <= intNumAntennas; i++)
        {
            Switch(connection, i + 10);
            int transmittingAntenna = i;
            Switch(connection, transmittingAntenna); // Use the same antenna for transmitting and receiving in mono-static sweeping
            connection.VNA!.RunSweepOnce();
            int row = 0;
            int col = i - 1;  // Use the current antenna index as the column index
            ProcessTraceValues(connection.VNA.TraceSet.Traces[1].Channels["S21"].DataSet["Through"],
                                complexData,
                                row,
                                col);
            row = 0;
            ProcessTraceValues(connection.VNA.TraceSet.Traces[1].Channels["S12"].DataSet["Through"],
                                complexData,
                                row,
                                col);
        }
    }

    private static void Switch(Connection connection, int rfPath)
    {
        string rfPathStr = rfPath.ToString();
        connection.Antennas!.Write(rfPathStr);
        Thread.Sleep(3000);
        Console.WriteLine($"Switching to RF path {rfPathStr}");
    }

    private static void ProcessTraceValues(mvnaIQData data,
                                        Complex[,] complexData,
                                        int row,
                                        int col)
    {
        foreach (mvnaIQ val in data.Values)
        {
            complexData[row, col] = new Complex(val.IVal, val.QVal);
            row++;
        }
    }
}