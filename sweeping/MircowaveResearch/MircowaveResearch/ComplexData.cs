using System.ComponentModel.DataAnnotations;

public class ComplexData
{
    [Key]
    public int Id { get; set; }
    public double Real { get; set; }
    public double Imaginary { get; set; }
}