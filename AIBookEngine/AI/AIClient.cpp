//
//  AIClient.cpp
//  AIBookEngine
//
//  Created by Armando Meabe on 07/05/2024.
//

#include "AIClient.hpp"

std::string AIClient::Chat(const std::string &text) {
    // Inicializa CURL globalmente.
    curl_global_init(CURL_GLOBAL_DEFAULT);
    
    // Preprocesamiento
    auto sanitizedDescription = TextUtils::processText(text);

    auto skillSet = new Skill(); //heap: just for fun.
    std::string prompt = skillSet->applySkill("extractKeywords", sanitizedDescription);
    
    // Instancia de la clase CurlHelper
    CurlHelper curlHelper;

    // Crea el cuerpo de la solicitud JSON.
    string jsonBody = curlHelper.createJsonBody("phi3", prompt);
    
    // Configura CURL con las opciones necesarias y realiza la solicitud.
    string serverResponse = curlHelper.setupCurl(jsonBody); // Almacenamos la respuesta del servidor.
    
    // Generar embedding
    string embedJsonBody = curlHelper.createJsonBody("nomic-embed-text", serverResponse);// SEGUIR ACA: SERVERRESPONSE TIENE BASURA Y NO LA RESPUESTA
    
    // Limpia CURL globalmente.
    curl_global_cleanup();

    // Liberar la memoria si usas 'new' para crear objetos.
    delete skillSet;

    return "";
};

std::string AIClient::Embed(const std::string &text) {
    // Inicializa CURL globalmente.
    curl_global_init(CURL_GLOBAL_DEFAULT);
    
    // Preprocesamiento
    auto sanitizedDescription = TextUtils::processText(text);

    auto skillSet = new Skill(); //heap: just for fun.
    std::string prompt = skillSet->applySkill("extractKeywords", sanitizedDescription);
    
    // Instancia de la clase CurlHelper
    CurlHelper curlHelper;

    // Crea el cuerpo de la solicitud JSON.
    string jsonBody = curlHelper.createJsonBody("phi3", prompt);
    
    // Configura CURL con las opciones necesarias y realiza la solicitud.
    string serverResponse = curlHelper.setupCurl(jsonBody); // Almacenamos la respuesta del servidor.
    
    // Generar embedding
    string embedJsonBody = curlHelper.createJsonBody("nomic-embed-text", serverResponse);// SEGUIR ACA: SERVERRESPONSE TIENE BASURA Y NO LA RESPUESTA
    
    // Limpia CURL globalmente.
    curl_global_cleanup();

    // Liberar la memoria si usas 'new' para crear objetos.
    delete skillSet;

    return "";
};
