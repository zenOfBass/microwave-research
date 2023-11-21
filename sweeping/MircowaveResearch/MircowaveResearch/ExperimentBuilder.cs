using System.Numerics;


namespace MicrowaveResearch
{
    public class ExperimentBuilder
    {
        private string? fullExpName, filePath, minFreq, maxFreq, freqSteps, numAntennas, objName, code;
        private Connection? connection;
        private Complex[,]? complexData;
        private int totalTraces, intFreqSteps, intNumAntennas;
        private double doubleMinFreq, doubleMaxFreq;


        public ExperimentBuilder SetConnection(Connection connection)
        {
            this.connection = connection;
            return this;
        }

        public ExperimentBuilder SetUserInput()
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
            return this;
        }

        public Experiment Build
        {
            get
            {
                // Validate parameters and create Experiment instance
                intFreqSteps++;
                totalTraces = 2 * intNumAntennas * (intNumAntennas - 1); // The number of traces = 2n(n-1), where n is the number of antennas
                complexData = new Complex[intFreqSteps, totalTraces];    // Set the number of rows and columns based on user input
                fullExpName = $"ExpTable_{code}_{objName}_{minFreq}_{maxFreq}_{freqSteps}_{numAntennas}";
                filePath = $"data/{code}-{objName}_{minFreq}-{maxFreq}_{freqSteps}_{numAntennas}_0.csv";
                return new Experiment(connection!,
                                    intFreqSteps,
                                    intNumAntennas,
                                    totalTraces,
                                    complexData,
                                    fullExpName,
                                    filePath);
            }
        }
    }
}