//
//  CurlHelper.cpp
//  AIBookEngine
//
//  Created by Armando Meabe on 07/05/2024.
//

#include "CurlHelper.hpp"
#include <iostream>
#include <sstream>

using namespace std;

// Constructor
CurlHelper::CurlHelper() {
    // Inicialización de CURL podría ir aquí si es necesaria
}

// Destructor
CurlHelper::~CurlHelper() {
    // Limpieza de CURL podría ir aquí si es necesaria
}

size_t CurlHelper::writeCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t realSize = size * nmemb;
    string temp(static_cast<const char*>(contents), realSize);
    json jFragment;
    try {
        // Intenta analizar los datos recibidos como JSON.
        jFragment = json::parse(temp);
        // Si el fragmento tiene la clave "response", concatena su contenido.
        if (jFragment.contains("response")) {
            string response = jFragment["response"].get<string>();
            cout << response; // Imprime cada fragmento de la respuesta conforme llega.
            // Acumula solo el fragmento de la respuesta en el string userp.
            ((std::string*)userp)->append(response);
        }
    } catch (json::parse_error& e) {
        // Si hay un error al analizar el JSON, imprime un mensaje de error.
        cerr << "JSON parse error: " << e.what() << endl;
    }
    return realSize;
}

size_t CurlHelper::writeCallbackNoStream(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t realSize = size * nmemb;
    // Acumula la respuesta completa en el string userp.
    ((std::string*)userp)->append(static_cast<const char*>(contents), realSize);
    return realSize;
}

// Configura las opciones de CURL para realizar la solicitud HTTP POST y devuelve la respuesta del servidor.
string CurlHelper::setupCurl(const string& jsonBody, const string& endpoint, bool stream) {
    CURL* curl = curl_easy_init(); // Inicializa una sesión CURL.
    if (!curl) {
        cerr << "Failed to initialize CURL" << endl;
        return ""; // Devuelve una cadena vacía si CURL no se pudo inicializar.
    }
    
    struct curl_slist* headers = nullptr;
    string response; // Aquí almacenaremos la respuesta del servidor.
    
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_URL, endpoint.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonBody.c_str());

    if (stream)
    {
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlHelper::writeCallback);
    }
    else
    {
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlHelper::writeCallbackNoStream);
    }
    
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response); // Almacenamos la respuesta aquí.
    
    // Realiza la solicitud HTTP POST y maneja errores.
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        cerr << "Error in POST request: " << curl_easy_strerror(res) << endl;
    }
    
    // Limpia los encabezados HTTP y la sesión CURL para evitar fugas de memoria.
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl); // Limpia la sesión CURL.
    
    return response; // Devolvemos la respuesta del servidor.
}

// Crea el cuerpo de la solicitud JSON para enviar a la API.
string CurlHelper::createChatJsonBody(const string& model, const string& prompt) {
    json j;
    j["model"] = model;
    j["prompt"] = prompt;
    j["stream"] = true;
    j["options"]["temperature"] = 0.1;
    // Serializa el objeto JSON a una cadena de texto.
    return j.dump();
}

// Crea el cuerpo de la solicitud JSON para enviar a la API. (Embeddings models only!!!)
string CurlHelper::createEmbeddingJsonBody(const string& model, const string& prompt) {
    json j;
    j["model"] = model;
    j["prompt"] = prompt;
    return j.dump();
}
