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

// Utilizamos la biblioteca nlohmann/json para manejar JSON de forma sencilla.
using json = nlohmann::json;

class CurlHelper {
public:
    // Constructor y destructor si son necesarios
    CurlHelper();
    ~CurlHelper();

    // Método para configurar y realizar la solicitud HTTP POST.
    std::string setupCurl(const string& jsonBody);

    // Método para crear el cuerpo de la solicitud JSON.
    std::string createJsonBody(const std::string& model, const std::string& prompt);

private:
    // Función de callback para escribir los datos recibidos.
    static size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userp);
};

#endif /* CurlHelper_hpp */
