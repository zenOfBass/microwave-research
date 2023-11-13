using Microsoft.EntityFrameworkCore;
using System.Numerics;


internal static class Writer
{
    internal static void ToCSV(int intFreqSteps, int totalTraces, Complex[,] complexData, string filePath)
    {
        try
        {
            using StreamWriter writer = new(filePath);
            for (int i = 0; i < intFreqSteps; i++) // Loop over columns
            {
                for (int j = 0; j < totalTraces; j++) //  Loop over rows
                {
                    Complex value = complexData[i, j];                  // Set the value to be recorded from the 2D array
                    writer.Write($"{value.Real} + {value.Imaginary}i"); // Write the value to the .csv file
                    if (j < totalTraces - 1) writer.Write(",");
                }
                writer.WriteLine();
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error writing to CSV: {ex.Message}\nExiting writer.");
        }
    }

    internal static void ToSQL(int intFreqSteps, int totalTraces, Complex[,] complexData, string fullExpName)
    {
        try
        {
            using AppDbContext db = new(); // Write the SQL database
            db.Database.EnsureCreated();
            db.Database.ExecuteSqlRaw($"CREATE TABLE {fullExpName} (Id int PRIMARY KEY IDENTITY(1,1), Real float, Imaginary float)");

            for (int i = 0; i < intFreqSteps; i++) // Populate the table with data
            {
                for (int j = 0; j < totalTraces; j++)
                {
                    Complex value = complexData[i, j];
                    db.ComplexData.Add(new ComplexData { Real = value.Real, Imaginary = value.Imaginary });
                }
            }
            db.SaveChanges();
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error writing to SQL: {ex.Message}\nExiting writer.");
        }
    }
}