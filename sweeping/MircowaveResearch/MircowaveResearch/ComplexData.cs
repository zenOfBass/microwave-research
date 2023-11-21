using System.ComponentModel.DataAnnotations;


namespace MicrowaveResearch
{
    public record ComplexData([property: Key] int Id, double Real, double Imaginary);
}