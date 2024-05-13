//
//  CurlHelper.hpp
//  AIBookEngine
//
//  Created by Armando Meabe on 07/05/2024.
//

#ifndef CurlHelper_hpp
#define CurlHelper_hpp

#include <stdio.h>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using namespace std;

// usar la biblioteca nlohmann/json para manejar JSON de forma facil.
using json = nlohmann::json;

class CurlHelper {
public:
    // Constructor y destructor si son necesarios
    CurlHelper();
    ~CurlHelper();

    // Método para configurar y realizar la solicitud HTTP POST.
    std::string setupCurl(const string& jsonBody, const string& endpoint, bool stream);

    // Método para crear el cuerpo de la solicitud JSON.
    std::string createChatJsonBody(const std::string& model, const std::string& prompt);

    // Método para crear el cuerpo de la solicitud JSON para usar con modelos de embeddings solamente
    std::string createEmbeddingJsonBody(const std::string& model, const std::string& prompt);

private:
    // Función de callback para escribir los datos recibidos.
    static size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userp);
    
    // Lo mismo pero sin streaming
    static size_t writeCallbackNoStream(void* contents, size_t size, size_t nmemb, void* userp);
};

#endif /* CurlHelper_hpp */
