//
//  TextElement.hpp
//  AIBookEngine
//
//  Created by Armando Meabe on 09/05/2024.
//

#ifndef TextElement_hpp
#define TextElement_hpp

#include <stdio.h>
#include <string>
#include "Embedding.hpp"

class TextElement {
public:
    std::string content;
    std::vector<Embedding> embeddings;

    TextElement(const std::string& content, const std::vector<Embedding>& embeddings);
    std::vector<std::pair<TextElement, float>> findClosestN(const std::vector<TextElement>& textElements, int N) const;
};

#endif // TextElement_hpp
