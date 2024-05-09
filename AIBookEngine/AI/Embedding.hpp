//
//  Embedding.hpp
//  AIBookEngine
//
//  Created by Armando Meabe on 08/05/2024.
//

#ifndef EMBEDDING_HPP
#define EMBEDDING_HPP

#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <iostream>
#include <cmath>

class Embedding {
public:
    std::vector<float> embedding;
    std::string originalText;

    // Constructor
    Embedding(const std::vector<float>& embedding);
    Embedding();

    // Método estático para crear una instancia desde un string JSON
    static Embedding from_json_string(const std::string& json_string);

    // Función para calcular la distancia coseno entre dos Embeddings
    static float cosine_distance(const Embedding& emb1, const Embedding& emb2);
    
    // Función para calcular el par mas cercano de embeddings dado un set de dos vectorses de embedding (uno de muestreo y uno de prompt para comparar temas relacionados)
    static std::pair<Embedding, Embedding> findClosestPair(const std::vector<Embedding>& embeddings1, const std::vector<Embedding>& embeddings2);
};

#endif // EMBEDDING_HPP
