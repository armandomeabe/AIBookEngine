using Microsoft.AspNetCore.Mvc;
using Cognitiva.AIBookEngine.BLL;
using Cognitiva.AIBookEngine.DAL;
using System.Collections.Generic;

namespace Cognitiva.AIBookEngine.API.Controllers
{
    [ApiController]
    [Route("api/[controller]")]
    public class EmbeddingController : ControllerBase
    {
        private readonly EmbeddingBLL _embeddingBLL;

        public EmbeddingController(EmbeddingBLL embeddingBLL)
        {
            _embeddingBLL = embeddingBLL;
        }

        // GET: api/Embedding
        [HttpGet]
        public ActionResult<IEnumerable<Embedding>> GetEmbeddings()
        {
            return Ok(_embeddingBLL.GetAllEmbeddings());
        }

        // GET: api/Embedding/5
        [HttpGet("{id}")]
        public ActionResult<Embedding> GetEmbedding(int id)
        {
            var embedding = _embeddingBLL.GetEmbeddingById(id);

            if (embedding == null)
            {
                return NotFound();
            }

            return Ok(embedding);
        }

        // POST: api/Embedding
        [HttpPost]
        public ActionResult<Embedding> PostEmbedding(Embedding embedding)
        {
            _embeddingBLL.AddEmbedding(embedding);
            return CreatedAtAction(nameof(GetEmbedding), new { id = embedding.Id }, embedding);
        }

        // PUT: api/Embedding/5
        [HttpPut("{id}")]
        public IActionResult PutEmbedding(int id, Embedding embedding)
        {
            if (id != embedding.Id)
            {
                return BadRequest();
            }

            _embeddingBLL.UpdateEmbedding(embedding);

            return NoContent();
        }

        // DELETE: api/Embedding/5
        [HttpDelete("{id}")]
        public IActionResult DeleteEmbedding(int id)
        {
            var existingEmbedding = _embeddingBLL.GetEmbeddingById(id);
            if (existingEmbedding == null)
            {
                return NotFound();
            }

            _embeddingBLL.DeleteEmbedding(id);

            return NoContent();
        }
    }
}