using Cognitiva.AIBookClient.OllamaWrapper.DTO;
using Cognitiva.AIBookEngine.BLL;
using Cognitiva.AIBookEngine.Core;
using Cognitiva.AIBookEngine.DAL;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.DependencyInjection;
using System;
using System.Resources;
using System.Text;
using System.Text.Json;

namespace Cognitiva.AIBookEngine.Client
{
    internal class Program
    {
        static async Task Main(string[] args)
        {
            // Consola
            Console.WriteLine("Hello, World!");

            var ai = new AI(new HttpClient(new HttpClientHandler()));
            var embeddingsFromDb = GetEmbeddings();

            while (true)
            {
                Console.WriteLine("Prompt:");
                var prompt = Console.ReadLine();

                var userEmbedding = await ai.GenerateEmbeddingsAsync("nomic-embed-text", prompt, null);

                if (userEmbedding == null) { continue; }

                // Inicialización de variables para encontrar el vecino más cercano
                float minDistance = float.MaxValue;
                int closestId = -1;

                foreach (var item in embeddingsFromDb)
                {
                    float[] dbEmbedding = JsonSerializer.Deserialize<EmbeddingDto>(item.EmbeddingStr).Embedding.ToArray();
                    float distance = CalculateEuclideanDistance(userEmbedding.Embedding.ToArray(), dbEmbedding);

                    if (distance < minDistance)
                    {
                        minDistance = distance;
                        closestId = item.Id;
                    }
                }

                Console.WriteLine($"El embedding más cercano es el del ID: {closestId} con una distancia de: {minDistance}");
                var closestItem = embeddingsFromDb.First(x => x.Id == closestId);
                Console.WriteLine(closestItem.OriginalText);
            }
        }

        private static float CalculateEuclideanDistance(float[] embeddingA, float[] embeddingB)
        {
            if (embeddingA.Length != embeddingB.Length)
                throw new ArgumentException("Los embeddings deben tener la misma dimensión.");

            double distance = 0.0f;
            for (int i = 0; i < embeddingA.Length; i++)
            {
                distance += Math.Pow((embeddingA[i] - embeddingB[i]),2) * Math.Pow((embeddingA[i] - embeddingB[i]),2);
            }
            return (float)Math.Sqrt(distance);
        }

        private static List<Embedding> GetEmbeddings()
        {
            // Configuración
            // Configura el contenedor de servicios
            var serviceCollection = new ServiceCollection();
            ConfigureServices(serviceCollection);

            // Construye el proveedor de servicios
            var serviceProvider = serviceCollection.BuildServiceProvider();

            // Resuelve la dependencia de EmbeddingBLL
            var embeddingBLL = serviceProvider.GetRequiredService<EmbeddingBLL>();

            var embeddings = embeddingBLL.GetAllEmbeddings();

            return embeddings;
        }

        private async Task IngestAsync()
        {
            // Configuración
            // Configura el contenedor de servicios
            var serviceCollection = new ServiceCollection();
            ConfigureServices(serviceCollection);

            // Construye el proveedor de servicios
            var serviceProvider = serviceCollection.BuildServiceProvider();

            // Resuelve la dependencia de EmbeddingBLL
            var embeddingBLL = serviceProvider.GetRequiredService<EmbeddingBLL>();

            var ai = new AI(new HttpClient());

            var files = GetFilesFromFolder("E:\\dev\\Github\\AIBookEngine\\00 - Resources\\To-Embed");
            int i = 1;
            foreach (var file in files)
            {
                Console.WriteLine($"#############________________ {i} ________________#############");
                Console.WriteLine($"Inserting: {file}");
                var embedding = await ai.GenerateEmbeddingsAsync("nomic-embed-text", file, null);
                var embeddingEntity = new Embedding { EmbeddingStr = embedding.ToJsonString(), OriginalText = embedding.Text, ProcessedText = "UNPROCESSED" };

                embeddingBLL.AddEmbedding(embeddingEntity);
                i++;
            }
        }

        private static void ConfigureServices(IServiceCollection services)
        {
            // Configura la conexión a la base de datos
            var connectionString = "Server=192.168.100.100; Database=AIBookEngine; User Id=sa; Password=123456;TrustServerCertificate=true";

            services.AddDbContext<AIBookEngineContext>(options =>
                options.UseSqlServer(connectionString));

            // Registra EmbeddingBLL para inyección de dependencias
            services.AddScoped<EmbeddingBLL>();
        }

        private static List<string> GetFilesFromFolder(string directoryPath)
        {
            var fileContents = new List<string>();

            // Verifica si el directorio existe
            if (!Directory.Exists(directoryPath))
            {
                throw new Exception("El directorio no existe.");
            }

            try
            {
                // Obtén todos los archivos en el directorio
                string[] files = Directory.GetFiles(directoryPath);

                // Lee cada archivo y agrega su contenido a allFileContents
                foreach (var file in files)
                {
                    // Asegúrate de que solo lees archivos de texto (opcional)
                    if (Path.GetExtension(file) == ".txt")
                    {
                        string content = File.ReadAllText(file);
                        fileContents.Add(content);
                    }
                }

            }
            catch (Exception ex)
            {
                // Maneja cualquier excepción que pueda ocurrir durante la lectura de archivos
                Console.WriteLine($"Ocurrió un error al leer los archivos: {ex.Message}");
            }
            return fileContents;
        }
    }
}
