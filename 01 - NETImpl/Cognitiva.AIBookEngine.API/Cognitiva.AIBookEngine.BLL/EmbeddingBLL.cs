using Cognitiva.AIBookEngine.DAL;
using System.Collections.Generic;
using System.Linq;

namespace Cognitiva.AIBookEngine.BLL
{
    public class EmbeddingBLL
    {
        private readonly AIBookEngineContext _context;

        public EmbeddingBLL(AIBookEngineContext context)
        {
            _context = context;
        }

        public List<Embedding> GetAllEmbeddings()
        {
            return _context.Embeddings.ToList();
        }

        public Embedding GetEmbeddingById(int id)
        {
            return _context.Embeddings.FirstOrDefault(e => e.Id == id);
        }

        public void AddEmbedding(Embedding embedding)
        {
            _context.Embeddings.Add(embedding);
            _context.SaveChanges();
        }

        public void UpdateEmbedding(Embedding embedding)
        {
            var existingEmbedding = _context.Embeddings.FirstOrDefault(e => e.Id == embedding.Id);
            if (existingEmbedding != null)
            {
                existingEmbedding.EmbeddingStr = embedding.EmbeddingStr;
                existingEmbedding.OriginalText = embedding.OriginalText;
                existingEmbedding.ProcessedText = embedding.ProcessedText;
                _context.SaveChanges();
            }
        }

        public void DeleteEmbedding(int id)
        {
            var embedding = _context.Embeddings.FirstOrDefault(e => e.Id == id);
            if (embedding != null)
            {
                _context.Embeddings.Remove(embedding);
                _context.SaveChanges();
            }
        }
    }
}