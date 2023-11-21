using Microsoft.EntityFrameworkCore;


namespace MicrowaveResearch
{
    public class AppDbContext : DbContext
    {
        public DbSet<ComplexData> ComplexData { get; set; }
        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            if (optionsBuilder is null) throw new ArgumentNullException(nameof(optionsBuilder));
            optionsBuilder.UseSqlServer(@"Server=(localdb)\mssqllocaldb;Database=ComplexDataDb;Integrated Security=True");
        }
    }
}