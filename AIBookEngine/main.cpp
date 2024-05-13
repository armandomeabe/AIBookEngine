#include <iostream>
#include <fstream>
#include <string>
#include <execution>
#include <cctype>
#include <sstream>
#include <filesystem>
#include <vector>
#include <nlohmann/json.hpp>
#include "CurlHelper.hpp"
#include "text_utils.hpp"
#include "skills.hpp"
#include "AIClient.hpp"
#include "Embedding.hpp"
#include "Models/TextElement.hpp"

using namespace std;
namespace fs = std::filesystem;
using json = nlohmann::json;

auto dbName = "/Users/armandomeabe/Code/AIBookEngine/AIBookEngine/DataBase.armDb";

std::vector<std::string> loadTextFiles(const std::string& ruta) {
    std::vector<std::string> fileContents;

    try {
        for (const auto& archivo : fs::directory_iterator(ruta)) {
            if (archivo.is_regular_file()) {
                std::ifstream ifs(archivo.path());
                if (ifs) {
                    std::string contenido((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
                    fileContents.push_back(contenido);
                    ifs.close();
                } else {
                    std::cerr << "No se pudo abrir el archivo: " << archivo.path() << std::endl;
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error al recorrer la ruta: " << e.what() << std::endl;
    }

    return fileContents;
}

json embeddingToJson(const Embedding& embedding) {
    json j;
    j["embedding"] = embedding.embedding;
    j["originalText"] = embedding.originalText;
    return j;
}

void to_json(json& j, const std::vector<Embedding>& embeddings) {
    for (const auto& embedding : embeddings) {
        j.push_back(embeddingToJson(embedding));
    }
}

void from_json(const json& j, std::vector<Embedding>& embeddings) {
    for (const auto& item : j) {
        Embedding embedding;
        embedding.embedding = item["embedding"].get<std::vector<float>>();
        embedding.originalText = item["originalText"].get<std::string>();
        embeddings.push_back(embedding);
    }
}

std::vector<TextElement> cargarResultadosDesdeArchivo(const std::string& nombreArchivo) {
    std::vector<std::pair<std::vector<Embedding>, std::string>> resultados;
    
    std::ifstream archivo(nombreArchivo);
    if (archivo) {
        json j;
        archivo >> j;
        
        for (const auto& resultado : j) {
            std::vector<Embedding> embeddings = resultado["embeddings"].get<std::vector<Embedding>>();
            std::string nombreArchivo = resultado["nombreArchivo"];
            resultados.push_back(std::make_pair(embeddings, nombreArchivo));
        }
        
        archivo.close();
    } else {
        std::cerr << "No se pudo abrir el archivo: " << nombreArchivo << std::endl;
    }
    
    std::vector<TextElement> textElements;
    for (auto dbItem : resultados) {
        TextElement te(dbItem.second, dbItem.first);
        textElements.push_back(te);
    }
    
    return textElements;
}

void guardarResultadosEnArchivo(const std::string& nombreArchivo, const std::vector<std::pair<std::vector<Embedding>, std::string>>& resultados) {
    std::ofstream archivo(nombreArchivo);
    if (archivo) {
        json j;
        for (const auto& resultado : resultados) {
            json jResultado;
            jResultado["nombreArchivo"] = resultado.second;
            jResultado["embeddings"] = resultado.first;
            j.push_back(jResultado);
        }

        archivo << j.dump(4); // 4 espacios de indentación para una mejor legibilidad
        archivo.close();
    } else {
        std::cerr << "No se pudo crear el archivo: " << nombreArchivo << std::endl;
    }
}

void Ingest() {
    AIClient ai;
    auto ingestPath = "/Users/armandomeabe/Code/AIBookEngine/AIBookEngine/KB/booksToTextFilesSubSet/";

    std::vector<std::string> files = loadTextFiles(ingestPath);

    std::vector<std::pair<std::vector<Embedding>,string>> results;
    
    int i = 1;
    // Imprimir el contenido de cada archivo y comenzar el proces
    for (const auto& file : files) {
        i++;
        std::cout << "Contenido del archivo: " << i << std::endl;
        std::cout << file << std::endl;
        std::cout << "------------------------" << std::endl;
        
        auto keywords = ai.Generate(file);
        auto keywordsVector = TextUtils::splitString(keywords);
        
        std::vector<Embedding> embeddings;
        for (const std::string& word : keywordsVector) {
            auto embed = ai.Embed(word);
            embeddings.push_back(embed);
            std::cout << std::endl << "Embedding palabra: " << embed.originalText;
        }
        
        results.push_back(std::make_pair(embeddings, file));
        std::cout << std::endl << "_________________________________________________________________" << std::endl;
    }
    
    guardarResultadosEnArchivo(dbName, results);
}

int main() {
    AIClient ai;
    
//    Ingest();
//    return 0;

    auto db = cargarResultadosDesdeArchivo(dbName);
    
    while (true) {
        std::cout << std::endl << std::endl << "Ingrese un prompt" << std::endl;
        std::string prompt;
        std::getline(std::cin, prompt);
        
        auto promptKeywords = ai.Generate(prompt);
        auto promptKeywordsVector = TextUtils::splitString(promptKeywords);
        
        std::vector<Embedding> promptEmbeddings;
        
        for (const std::string& word : promptKeywordsVector) {
            auto embed = ai.Embed(word);
            promptEmbeddings.push_back(embed);
            std::cout << std::endl << "Embedding palabra de prompt: " << embed.originalText;
        }
        
        TextElement te(prompt, promptEmbeddings);
        
        auto recomendations = te.findClosestN(db, 1);
        
        for (auto r : recomendations) {
            std::cout << std::endl << "___________BUSCANDO LIBROS___________" << std::endl;
            std::cout << "BEST MATCH ORIGEN: " << te.content << std::endl; //textElement del prompt
            std::cout << "BEST MATCH DESTINO: " << r.first.content << std::endl; //recomendation de la bd
            std::cout << "BEST MATCH DISTANCIA: " << r.second << std::endl; // distancia entre la recomendation y la te del prompt
        }
    }
    
    return 0;
}
