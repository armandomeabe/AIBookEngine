//
//  AIClient.cpp
//  AIBookEngine
//
//  Created by Armando Meabe on 07/05/2024.
//

#include "AIClient.hpp"

AIClient::AIClient() { };

std::string AIClient::Generate(const std::string &text) {
    // Inicializa CURL globalmente.
    curl_global_init(CURL_GLOBAL_DEFAULT);
    
    // Preprocesamiento
    auto sanitizedDescription = TextUtils::processText(text);

    auto skillSet = new Skill(); //heap: just for fun.
    std::string prompt = skillSet->applySkill("extractKeywords", sanitizedDescription);
    
    // Instancia de la clase CurlHelper
    CurlHelper curlHelper;

    // Crea el cuerpo de la solicitud JSON.
    string jsonBody = curlHelper.createChatJsonBody("phi3", prompt);
    
    // Configura CURL con las opciones necesarias y realiza la solicitud.
    string serverResponse = curlHelper.setupCurl(jsonBody, "http://localhost:11434/api/generate", true); // Almacenamos la respuesta del servidor.
    
    // Limpia CURL globalmente.
    curl_global_cleanup();

    // Liberar la memoria si uso 'new' para crear objetos.
    delete skillSet;

    // Devuelve la respuesta completa.
    return serverResponse;
};

Embedding AIClient::Embed(const std::string &text) {
    // Inicializa CURL globalmente.
    curl_global_init(CURL_GLOBAL_DEFAULT);
    
    // Instancia de la clase CurlHelper
    CurlHelper curlHelper;

    // Crea el cuerpo de la solicitud JSON.
    string jsonBody = curlHelper.createEmbeddingJsonBody("nomic-embed-text", text);
    
    // Configura CURL con las opciones necesarias y realiza la solicitud.
    string serverResponse = curlHelper.setupCurl(jsonBody, "http://localhost:11434/api/embeddings", false); // Almacenamos la respuesta del servidor.
    
    // Limpia CURL globalmente.
    curl_global_cleanup();

    auto embedding_instance = Embedding::from_json_string(serverResponse);
    embedding_instance.originalText = text;
    
    return embedding_instance;
};
