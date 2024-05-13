using Cognitiva.AIBookClient.OllamaWrapper;
using Cognitiva.AIBookClient.OllamaWrapper.DTO;
using Cognitiva.AIBookClient.OllamaWrapper.OllamaWrapper;
using System;
using System.Net.Http;
using System.Threading.Tasks;

namespace Cognitiva.AIBookEngine.Core
{
    public class AI
    {
        private readonly OllamaWrapper _client;

        public AI(HttpClient httpClient)
        {
            _client = new OllamaWrapper(httpClient);
        }

        public async Task<CompletionResponseDto> GenerateCompletionAsync(string model, string prompt, object options, string system, string template)
        {
            return await _client.GenerateCompletionAsync(model, prompt, options, system, template);
        }

        public async Task<HttpResponseMessage> CreateModelAsync(string name, string path)
        {
            return await _client.CreateModelAsync(name, path);
        }

        public async Task<HttpResponseMessage> ListLocalModelsAsync()
        {
            return await _client.ListLocalModelsAsync();
        }

        public async Task<HttpResponseMessage> ShowModelInformationAsync(string name)
        {
            return await _client.ShowModelInformationAsync(name);
        }

        public async Task<HttpResponseMessage> CopyModelAsync(string source, string destination)
        {
            return await _client.CopyModelAsync(source, destination);
        }

        public async Task<HttpResponseMessage> DeleteModelAsync(string model)
        {
            return await _client.DeleteModelAsync(model);
        }

        public async Task<HttpResponseMessage> PullModelAsync(string name, bool insecure)
        {
            return await _client.PullModelAsync(name, insecure);
        }

        public async Task<HttpResponseMessage> PushModelAsync(string name, bool insecure)
        {
            return await _client.PushModelAsync(name, insecure);
        }

        public async Task<EmbeddingDto> GenerateEmbeddingsAsync(string model, string prompt, object options)
        {
            return await _client.GenerateEmbeddingsAsync(model, prompt, options);
        }
    }
}