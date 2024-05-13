namespace Cognitiva.AIBookEngine.DAL
{
    public class Embedding
    {
        public int Id { get; set; }
        public string EmbeddingStr { get; set; }
        public string OriginalText { get; set; }
        public string ProcessedText { get; set; }
    }
}