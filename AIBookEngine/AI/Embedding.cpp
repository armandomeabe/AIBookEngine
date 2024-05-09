//
//  Embedding.cpp
//  AIBookEngine
//
//  Created by Armando Meabe on 08/05/2024.
//

#include "Embedding.hpp"

// Constructor
Embedding::Embedding(const std::vector<float>& embedding) : embedding(embedding) {}
Embedding::Embedding(){}

// Método estático para crear una instancia desde un string JSON
Embedding Embedding::from_json_string(const std::string& json_string) {
    auto json = nlohmann::json::parse(json_string);
    return Embedding(json.at("embedding").get<std::vector<float>>());
}

// Función para calcular el producto punto entre dos vectores
static float dot_product(const std::vector<float>& v1, const std::vector<float>& v2) {
    float sum = 0.0f;
    for (size_t i = 0; i < v1.size(); ++i) {
        sum += v1[i] * v2[i];
    }
    return sum;
}

// Función para calcular la norma de un vector
static float vector_norm(const std::vector<float>& v) {
    float sum = 0.0f;
    for (float elem : v) {
        sum += elem * elem;
    }
    return std::sqrt(sum);
}

// Función para calcular la distancia coseno entre dos Embeddings
float Embedding::cosine_distance(const Embedding& emb1, const Embedding& emb2) {
    float dot = dot_product(emb1.embedding, emb2.embedding);
    float norm1 = vector_norm(emb1.embedding);
    float norm2 = vector_norm(emb2.embedding);
    float similarity = dot / (norm1 * norm2);
    return 1.0f - similarity;
}

std::pair<Embedding, Embedding> Embedding::findClosestPair(const std::vector<Embedding>& embeddings1, const std::vector<Embedding>& embeddings2) {
    std::pair<Embedding, Embedding> closestPair;
    float minDistance = std::numeric_limits<float>::max();

    for (const Embedding& emb1 : embeddings1) {
        for (const Embedding& emb2 : embeddings2) {
            float distance = Embedding::cosine_distance(emb1, emb2);
            if (distance < minDistance) {
                minDistance = distance;
                closestPair = std::pair<Embedding, Embedding>(emb1, emb2);  // Utilizar el constructor de std::pair explícitamente
            }
        }
    }

    return closestPair;
}
