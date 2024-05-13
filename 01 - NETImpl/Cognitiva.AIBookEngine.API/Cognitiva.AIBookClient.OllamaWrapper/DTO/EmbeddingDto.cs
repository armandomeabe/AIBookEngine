using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using System.Text.Json.Serialization;

namespace Cognitiva.AIBookClient.OllamaWrapper.DTO
{

    public class EmbeddingDto
    {
        [JsonPropertyName("embedding")]
        public List<float> Embedding { get; set; }

        [JsonPropertyName("text")]
        public string Text { get; set; }

        public EmbeddingDto(List<float> embedding, string text)
        {
            Embedding = embedding;
            Text = text;
        }

        // Method to convert the EmbeddingDto to a JSON string
        public string ToJsonString()
        {
            var options = new JsonSerializerOptions
            {
                WriteIndented = true // Set to false if you don't want the JSON to be indented
            };

            // Serialize the Embedding property to a JSON string
            return JsonSerializer.Serialize(new { embedding = Embedding }, options);
        }

        // Method to parse a JSON string into an EmbeddingDto
        public static EmbeddingDto ParseFromJsonString(string jsonString, string originalText)
        {
            if (string.IsNullOrWhiteSpace(jsonString))
            {
                throw new ArgumentException("Input JSON string cannot be null or whitespace.", nameof(jsonString));
            }

            try
            {
                // Deserialize the JSON string into an EmbeddingDto object
                var embeddingDto = JsonSerializer.Deserialize<EmbeddingDto>(jsonString);
                embeddingDto.Text = originalText;

                if (embeddingDto == null)
                {
                    throw new JsonException("Deserialization resulted in a null object.");
                }
                return embeddingDto;
            }
            catch (JsonException ex)
            {
                throw new FormatException("The provided string is not a valid JSON format for EmbeddingDto.", ex);
            }
        }
    }
}
