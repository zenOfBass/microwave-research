/***************************************
/ Program.cs            
/ Colton Cox - ccox60@uco.edu
/ Nathan G Wiley - nwiley@uco.edu
/ University of Central Oklahoma
/ See changelog.md for detailed changes 
***************************************/


Connection connection = Connection.Instance;

while (true)
{
    Experiment experiment = new(connection);

    try
    {
        experiment.Run();
    }
    catch (Exception ex)
    {
        Console.WriteLine($"Error message: {ex.Message}\nExiting scan."); // Display the specific error message
    }
    Console.WriteLine("Would you like to scan again? Y/N: ");
    while (true)
    {
        string repeat = Console.ReadLine();
        if (repeat != null) repeat = repeat.ToUpper();
        if (repeat == "Y") break;                     // Repeat
        else if (repeat == "N") ((IDisposable)connection).Dispose(); // Close all connections
        else Console.WriteLine("Invalid input. Please enter Y or N");
    }
}