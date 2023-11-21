using MicrowaveResearch;
using System.Numerics;


internal class Sweeper
{
    private ISweepStrategy _strategy;

    public Sweeper(ISweepStrategy strategy) => _strategy = strategy;

    internal ISweepStrategy Strategy { get => _strategy; set => _strategy = value; }

    public void SetStrategy(ISweepStrategy strategy) => _strategy = strategy;

    public void Sweep(Connection connection,
                    int intNumAntennas,
                    int totalTraces,
                    Complex[,] complexData)
    {
        if (connection is null) throw new ArgumentNullException(nameof(connection));
        _strategy.Sweep(connection,
                        intNumAntennas,
                        totalTraces,
                        complexData);
    }
}