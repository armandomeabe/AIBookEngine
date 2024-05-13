using Microsoft.EntityFrameworkCore;

namespace Cognitiva.AIBookEngine.DAL
{
    public class AIBookEngineContext : DbContext
    {
        string connectionString = "Server=localhost; Database=AIBookEngine; User Id=sa; Password=123456;";

        public AIBookEngineContext(DbContextOptions<AIBookEngineContext> options) : base(options)
        {
        }

        public DbSet<Embedding> Embeddings { get; set; }

        //protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        //{
        //    if (!optionsBuilder.IsConfigured)
        //    {
        //        optionsBuilder.UseSqlServer(connectionString);
        //    }
        //}
    }
}