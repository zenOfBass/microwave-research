/***************************************
/ Program.cs            
/ Colton Cox - ccox60@uco.edu
/ Nathan G Wiley - nwiley@uco.edu
/ University of Central Oklahoma
/ See changelog.md for detailed changes 
***************************************/

using MicrowaveResearch;


Connection connection = Connection.Instance;

while (true)
{
    try
    {
        Experiment experiment = new ExperimentBuilder()
            .SetConnection(connection)
            .SetUserInput()
            .Build; // Use the Build property to get the constructed Experiment instance
        experiment.Run();
    }
    catch (Exception ex)
    {
        Console.WriteLine($"Error message: {ex.Message}\nExiting experiment."); // Display the specific error message
    }
    Console.WriteLine("Would you like to scan again? Y/N: ");
    while (true)
    {
        var repeat = Console.ReadLine();
        if (repeat != null) repeat = repeat.ToUpper();
        if (repeat == "Y") break;                     // Repeat
        else if (repeat == "N") connection.Dispose(); // Close all connections
        else Console.WriteLine("Invalid input. Please enter Y or N");
    }
}