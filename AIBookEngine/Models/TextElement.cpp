//
//  TextElement.cpp
//  AIBookEngine
//
//  Created by Armando Meabe on 09/05/2024.
//

#include "TextElement.hpp"

TextElement::TextElement(const std::string& content, const std::vector<Embedding>& embeddings)
    : content(content), embeddings(embeddings) {
}

std::vector<std::pair<TextElement, float>> TextElement::findClosestN(const std::vector<TextElement>& textElements, int N) const {
    std::vector<std::pair<TextElement, float>> closestN;
    std::vector<float> distances;

    for (const TextElement& other : textElements) {
        float minDistance = std::numeric_limits<float>::max();
        std::pair<Embedding, Embedding> closestPair;

        for (const Embedding& emb1 : embeddings) {
            for (const Embedding& emb2 : other.embeddings) {
                float embDistance = Embedding::cosine_distance(emb1, emb2);
                if (embDistance < minDistance) {
                    minDistance = embDistance;
                    closestPair = std::make_pair(emb1, emb2);
                }
            }
        }

//        if (closestPair.first != Embedding() && closestPair.second != Embedding()) {
            distances.push_back(minDistance);
            closestN.emplace_back(other, minDistance);
//        }
    }

    // Ordenar los índices de los elementos en base a las distancias ascendentes
    std::vector<size_t> indices(distances.size());
    std::iota(indices.begin(), indices.end(), 0);
    std::sort(indices.begin(), indices.end(), [&](size_t a, size_t b) {
        return distances[a] < distances[b];
    });

    // Obtener los N TextElement más cercanos con sus distancias correspondientes
    std::vector<std::pair<TextElement, float>> result;
    for (int i = 0; i < N && i < indices.size(); ++i) {
        result.push_back(closestN[indices[i]]);
    }

    return result;
}
