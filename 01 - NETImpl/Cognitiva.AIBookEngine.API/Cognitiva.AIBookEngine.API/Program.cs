using Cognitiva.AIBookEngine.BLL;
using Cognitiva.AIBookEngine.DAL;
using Microsoft.EntityFrameworkCore;

var builder = WebApplication.CreateBuilder(args);

// Add services to the container.

// Obtener la cadena de conexión del archivo appsettings.json
var connectionString = builder.Configuration.GetConnectionString("AIBookEngineDatabase");

// Configurar DbContext con la cadena de conexión
builder.Services.AddDbContext<AIBookEngineContext>(options =>
    options.UseSqlServer(connectionString));

// Registrar EmbeddingBLL como un servicio para que pueda ser inyectado
builder.Services.AddScoped<EmbeddingBLL>();

builder.Services.AddControllers();
// Learn more about configuring Swagger/OpenAPI at https://aka.ms/aspnetcore/swashbuckle
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();

var app = builder.Build();

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI();
}

app.UseHttpsRedirection();

app.UseAuthorization();

app.MapControllers();

app.Run();