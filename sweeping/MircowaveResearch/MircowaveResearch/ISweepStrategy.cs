using MicrowaveResearch;
using System.Numerics;


internal interface ISweepStrategy
{
    void Sweep(Connection connection, int intNumAntennas, int totalTraces, Complex[,] complexData);
}