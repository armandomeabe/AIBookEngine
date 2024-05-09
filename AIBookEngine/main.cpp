#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <sstream>
#include "CurlHelper.hpp"
#include "text_utils.hpp"
#include "skills.hpp"
#include "AIClient.hpp"
#include "Embedding.hpp"

using namespace std;

std::vector<std::string> splitString(const std::string& str) {
    std::vector<std::string> words;
    std::stringstream ss(str);
    std::string word;

    while (std::getline(ss, word, ',')) {
        words.push_back(word);
    }

    return words;
}

int main() {
    // Define la ruta al archivo que se va a procesar.
    const string filename = "/Users/armandomeabe/Code/AIBookEngine/AIBookEngine/sample_prompt";
    
    // Lee el contenido del archivo y lo prepara para la solicitud.
    string description = TextUtils::readFileContents(filename);
    
    AIClient ai;
    auto keywords = ai.Generate(description);
    auto keywordsVector = splitString(keywords);
    
    std::vector<Embedding> embeddings;
    
    for (const std::string& word : keywordsVector) {
        auto embed = ai.Embed(word);
        embeddings.push_back(embed);
        std::cout << "Embedding palabra: " << embed.originalText << std::endl;
    }
    
    while (true) {
        std::cout << std::endl << std::endl << "Ingrese un prompt" << std::endl;
        std::string prompt;
        std::getline(std::cin, prompt);
        
        auto promptKeywords = ai.Generate(prompt);
        auto promptKeywordsVector = splitString(promptKeywords);
        std::vector<Embedding> promptEmbeddings;
        
        for (const std::string& word : promptKeywordsVector) {
            auto embed = ai.Embed(word);
            promptEmbeddings.push_back(embed);
            std::cout << std::endl << "Embedding palabra de prompt: " << embed.originalText;
        }
        
        auto bestMatch = Embedding::findClosestPair(embeddings, promptEmbeddings);
        
        std::cout << std::endl << "___________BUSCANDO LIBROS___________" << std::endl;
        std::cout << "BEST MATCH ORIGEN: " << bestMatch.first.originalText << std::endl;
        std::cout << "BEST MATCH DESTINO: " << bestMatch.second.originalText << std::endl;
        std::cout << "BEST MATCH DISTANCIA: " << Embedding::cosine_distance(bestMatch.first, bestMatch.second) << std::endl;
        
    }
    
    return 0;
}
