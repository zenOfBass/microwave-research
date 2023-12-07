namespace MicrowaveResearch
{
    public interface IExperimentBuilder
    {
        IExperimentBuilder SetConnection(Connection connection);
        IExperimentBuilder SetUserInput();
    }
}