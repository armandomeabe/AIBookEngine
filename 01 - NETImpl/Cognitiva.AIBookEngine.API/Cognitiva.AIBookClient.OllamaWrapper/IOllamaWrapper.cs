using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Cognitiva.AIBookClient.OllamaWrapper
{
    public interface IOllamaWrapper
    {
        Task<HttpResponseMessage> GenerateCompletionAsync(string model, string prompt, object options, string system, string template);
        Task<HttpResponseMessage> CreateModelAsync(string name, string path);
        Task<HttpResponseMessage> ListLocalModelsAsync();
        Task<HttpResponseMessage> ShowModelInformationAsync(string name);
        Task<HttpResponseMessage> CopyModelAsync(string source, string destination);
        Task<HttpResponseMessage> DeleteModelAsync(string model);
        Task<HttpResponseMessage> PullModelAsync(string name, bool insecure);
        Task<HttpResponseMessage> PushModelAsync(string name, bool insecure);
        Task<HttpResponseMessage> GenerateEmbeddingsAsync(string model, string prompt, object options);
    }
}
