namespace Cognitiva.AIBookClient.OllamaWrapper
{
    using Cognitiva.AIBookClient.OllamaWrapper.DTO;
    using System;
    using System.Collections.Generic;
    using System.Net.Http;
    using System.Text;
    using System.Text.Json;
    using System.Threading.Tasks;

    namespace OllamaWrapper
    {
        public class OllamaWrapper //: IOllamaWrapper
        {
            private readonly HttpClient _httpClient;
            private readonly string _baseAddress = "http://localhost:11434"; // Change this to the actual API base address

            public OllamaWrapper(HttpClient httpClient)
            {
                _httpClient = httpClient;
            }

            public async Task<CompletionResponseDto> GenerateCompletionAsync(string model, string prompt, object options, string system, string template)
            {
                var requestBody = new
                {
                    model,
                    prompt,
                    options,
                    system,
                    template
                };

                var content = new StringContent(JsonSerializer.Serialize(requestBody), Encoding.UTF8, "application/json");
                var response = await _httpClient.PostAsync($"{_baseAddress}/api/generate", content);

                if (response.IsSuccessStatusCode)
                {
                    // Get the stream from the response
                    using var stream = await response.Content.ReadAsStreamAsync();
                    using var reader = new StreamReader(stream);

                    StringBuilder stringBuilder = new StringBuilder();
                    CompletionResponseDto finalResponse = null;

                    // Read the stream line by line
                    while (!reader.EndOfStream)
                    {
                        var line = await reader.ReadLineAsync();
                        if (!string.IsNullOrEmpty(line))
                        {
                            // Process each line (which is a JSON object)
                            var completionResponse = JsonSerializer.Deserialize<CompletionResponseDto>(line);
                            _ = stringBuilder.Append(value: completionResponse.Response);

                            // Check if the stream is done
                            if (completionResponse.Done)
                            {
                                finalResponse = completionResponse;
                                break;
                            }
                        }
                    }

                    // Set the final response text
                    if (finalResponse != null)
                    {
                        finalResponse.Response = stringBuilder.ToString();
                    }

                    return finalResponse;
                }
                else
                {
                    throw new HttpRequestException($"Error: {response.StatusCode}");
                }
            }

            public async Task<HttpResponseMessage> CreateModelAsync(string name, string path)
            {
                var requestBody = new
                {
                    name,
                    path
                };

                var content = new StringContent(JsonSerializer.Serialize(requestBody), Encoding.UTF8, "application/json");
                return await _httpClient.PostAsync($"{_baseAddress}/api/create", content);
            }

            public async Task<HttpResponseMessage> ListLocalModelsAsync()
            {
                return await _httpClient.GetAsync($"{_baseAddress}/api/tags");
            }

            public async Task<HttpResponseMessage> ShowModelInformationAsync(string name)
            {
                var requestBody = new
                {
                    name
                };

                var content = new StringContent(JsonSerializer.Serialize(requestBody), Encoding.UTF8, "application/json");
                return await _httpClient.PostAsync($"{_baseAddress}/api/show", content);
            }

            public async Task<HttpResponseMessage> CopyModelAsync(string source, string destination)
            {
                var requestBody = new
                {
                    source,
                    destination
                };

                var content = new StringContent(JsonSerializer.Serialize(requestBody), Encoding.UTF8, "application/json");
                return await _httpClient.PostAsync($"{_baseAddress}/api/copy", content);
            }

            public async Task<HttpResponseMessage> DeleteModelAsync(string model)
            {
                var requestUri = $"{_baseAddress}/api/delete?model={Uri.EscapeDataString(model)}";
                return await _httpClient.DeleteAsync(requestUri);
            }

            public async Task<HttpResponseMessage> PullModelAsync(string name, bool insecure)
            {
                var requestBody = new
                {
                    name,
                    insecure
                };

                var content = new StringContent(JsonSerializer.Serialize(requestBody), Encoding.UTF8, "application/json");
                return await _httpClient.PostAsync($"{_baseAddress}/api/pull", content);
            }

            public async Task<HttpResponseMessage> PushModelAsync(string name, bool insecure)
            {
                var requestBody = new
                {
                    name,
                    insecure
                };

                var content = new StringContent(JsonSerializer.Serialize(requestBody), Encoding.UTF8, "application/json");
                return await _httpClient.PostAsync($"{_baseAddress}/api/push", content);
            }

            public async Task<EmbeddingDto> GenerateEmbeddingsAsync(string model, string prompt, object options)
            {
                var requestBody = new
                {
                    model,
                    prompt,
                    options
                };

                var content = new StringContent(JsonSerializer.Serialize(requestBody), Encoding.UTF8, "application/json");
                var embedding = await _httpClient.PostAsync($"{_baseAddress}/api/embeddings", content);
                var temp = await embedding.Content.ReadAsStringAsync();
                var dto = EmbeddingDto.ParseFromJsonString(temp, prompt);
                return dto;
            }
        }
    }
}
