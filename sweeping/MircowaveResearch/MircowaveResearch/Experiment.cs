using System.Numerics;


namespace MicrowaveResearch
{
    public struct Experiment
    {
        // Sweeping variables
        private readonly string fullExpName, filePath;
        private readonly Connection connection;
        private readonly int totalTraces, intFreqSteps, intNumAntennas;

        public Complex[,] ComplexData { readonly get; set; }

        internal Experiment(Connection connection,
                            int intFreqSteps,
                            int intNumAntennas,
                            int totalTraces,
                            Complex[,] ComplexData,
                            string fullExpName,
                            string filePath)
        {
            this.connection = connection ?? throw new ArgumentNullException(nameof(connection));
            this.intFreqSteps = intFreqSteps;
            this.intNumAntennas = intNumAntennas;
            this.totalTraces = totalTraces;
            this.ComplexData = ComplexData;
            this.fullExpName = fullExpName;
            this.filePath = filePath;
        }

        internal readonly void Run()
        {
            Console.WriteLine("Scan starting.");
            DateTime startTime = DateTime.Now;
            MultiStaticSweep multiStaticSweep = new();
            ISweepStrategy strategy = multiStaticSweep;
            Sweeper Sweeper = new(strategy);
            Sweeper.Sweep(connection, intNumAntennas, totalTraces, ComplexData);
            Writer.ToCSV(intFreqSteps, totalTraces, ComplexData, filePath);
            Writer.ToSQL(intFreqSteps, totalTraces, ComplexData, fullExpName);
            Console.WriteLine($"Scan has finished.\nTotal time in minutes: {(DateTime.Now - startTime).TotalMinutes} minutes.");
        }
    }
}