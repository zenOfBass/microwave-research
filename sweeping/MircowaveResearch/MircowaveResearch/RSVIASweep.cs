using MicrowaveResearch;
using MiQVNA;
using System.Numerics;


internal class RSVIASweep : ISweepStrategy
{
    public void Sweep(Connection connection,
                        int intNumAntennas,
                        int totalTraces,
                        Complex[,] complexData)
    {
        Complex[,] evenSweepData = new Complex[complexData.GetLength(0), complexData.GetLength(1)];
        Complex[,] oddSweepData = new Complex[complexData.GetLength(0), complexData.GetLength(1)];

        // Perform sweep with odd-numbered antennas
        EvenOddSweep(connection, intNumAntennas, oddSweepData, true);

        // Perform sweep with even-numbered antennas
        EvenOddSweep(connection, intNumAntennas, evenSweepData, false);

        // Subtract one sweep from the other
        SubtractSweeps(complexData, evenSweepData, oddSweepData);
    }

    private static void EvenOddSweep(Connection connection,
                                    int intNumAntennas,
                                    Complex[,] complexData,
                                    bool isOdd)
    {
        int col = 0;

        for (int i = isOdd ? 1 : 2; i <= intNumAntennas; i += 2)
        {
            Switch(connection, i + 10);
            int transmittingAntenna = i;

            for (int j = isOdd ? 1 : 2; j <= intNumAntennas; j += 2)
            {
                if (j == transmittingAntenna) continue;
                else
                {
                    Switch(connection, j);
                    connection.VNA!.RunSweepOnce();
                    int row = 0;
                    ProcessTraceValues(connection.VNA.TraceSet.Traces[1].Channels["S21"].DataSet["Through"],
                                        complexData,
                                        row,
                                        col);
                    row = 0;
                    col++;
                    ProcessTraceValues(connection.VNA.TraceSet.Traces[1].Channels["S12"].DataSet["Through"],
                                        complexData,
                                        row,
                                        col);
                }
                col++;
            }
        }
    }

    private static void SubtractSweeps(Complex[,] complexData, Complex[,] evenComplexData, Complex[,] oddComplexData)
    {
        int rows = complexData.GetLength(0);
        int cols = complexData.GetLength(1);

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                complexData[i, j] = evenComplexData[i, j] - oddComplexData[i, j];
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