using Microsoft.EntityFrameworkCore;

public class AppDbContext : DbContext
{
    public DbSet<ComplexData> ComplexData { get; set; }
    protected override void OnConfiguring(DbContextOptionsBuilder options)
        => options.UseSqlServer(@"Server=(localdb)\mssqllocaldb;Database=ComplexDataDb;Integrated Security=True");
}