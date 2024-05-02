#include <iostream>
#include <fstream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <string>
#include <cctype>
#include <sstream>
#include "text_utils.hpp"

// Utilizamos la biblioteca nlohmann/json para manejar JSON de forma sencilla.
using json = nlohmann::json;
using namespace std;

// Esta variable global almacena la respuesta completa de la API.
string global_res = "";

// Elimina los espacios adicionales y los saltos de línea de un texto.
string trimAndReduce(const string& input) {
    string result;
    bool prevSpace = false;
    for (char c : input) {
        if (isspace(c)) {
            if (!prevSpace) {
                result += ' ';
                prevSpace = true;
            }
        } else {
            result += c;
            prevSpace = false;
        }
    }
    return result;
}

// Función de callback que CURL usará para escribir los datos recibidos.
size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t realSize = size * nmemb;
    string temp(static_cast<const char*>(contents), realSize);
    json jFragment;
    try {
        // Intenta analizar los datos recibidos como JSON.
        jFragment = json::parse(temp);
        // Si el fragmento tiene la clave "response", imprime su contenido.
        if (jFragment.contains("response")) {
            string response = jFragment["response"].get<string>();
            cout << response; // Imprime cada fragmento de la respuesta conforme llega.
        }
    } catch (json::parse_error& e) {
        // Si hay un error al analizar el JSON, imprime un mensaje de error.
        cerr << "JSON parse error: " << e.what() << endl;
    }
    return realSize;
}

// Configura las opciones de CURL para realizar la solicitud HTTP POST.
void setupCurl(CURL* curl, const string& jsonBody) {
    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.100.100:11434/api/generate");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    // Establece el cuerpo de la solicitud con el JSON generado.
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonBody.c_str());
    // Establece la función de callback para manejar los datos recibidos.
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    // Realiza la solicitud HTTP POST y maneja errores.
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        cerr << "Error in POST request: " << curl_easy_strerror(res) << endl;
    }
    // Limpia los encabezados HTTP para evitar fugas de memoria.
    curl_slist_free_all(headers);
}

// Crea el cuerpo de la solicitud JSON para enviar a la API.
string createJsonBody(const string& prompt) {
    json j;
    j["model"] = "phi3";
    j["prompt"] = prompt;
    j["stream"] = true;
    j["options"]["temperature"] = 0.1;
    // Serializa el objeto JSON a una cadena de texto.
    return j.dump();
}

// Lee el contenido completo de un archivo y lo devuelve como una cadena de texto.
string readFileContents(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Unable to open file: " << filename << endl;
        return "";
    }
    stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return buffer.str();
}

// Procesa la solicitud a la API de inteligencia artificial.
void processAIRequest(const string& filename) {
    CURL* curl;
    // Inicializa CURL globalmente.
    curl_global_init(CURL_GLOBAL_DEFAULT);
    // Inicializa una sesión CURL.
    curl = curl_easy_init();
    if (curl) {
        // Lee el contenido del archivo y lo prepara para la solicitud.
        string description = readFileContents(filename);
        
        // Preprocesamiento
        description = TextUtils::toLowerCase(description);
        description = TextUtils::removePunctuation(description);
        std::vector<std::string> tokens = TextUtils::tokenize(description);
        tokens = TextUtils::removeStopWords(tokens);

        // Mostrar los tokens resultantes
        for (const auto& token : tokens) {
            std::cout << token << std::endl;
        }
        
        string prompt = "Dado el libro que describo a continuación: " + trimAndReduce(description) + "... por favor extrae la idea principal del mismo para generar un embedding eficiente con un modelo de inteligencia artificial. No agregues absolutamente nada ni antes ni después del texto que vas a generar, solamente expresa la idea principal sin agregado alguno.";
        
        cout << endl << "__________" << endl << prompt << endl << "__________" << endl;
        
        // Crea el cuerpo de la solicitud JSON.
        string jsonBody = createJsonBody(prompt);
        // Muestra el cuerpo de la solicitud JSON enviada al servidor.
        cout << endl<< endl << endl << "JSON body sent to the server: " << jsonBody << endl << endl << endl;
        // Configura CURL con las opciones necesarias y realiza la solicitud.
        setupCurl(curl, jsonBody);
        // Limpia la sesión CURL.
        curl_easy_cleanup(curl);
    } else {
        cerr << "Failed to initialize CURL" << endl;
    }
    // Limpia CURL globalmente.
    curl_global_cleanup();
}

int main() {
    // Define la ruta al archivo que se va a procesar.
    const string filename = "/Users/armandomeabe/Code/FICH/Proyectos/Prueba001/AIBookEngine/AIBookEngine/sample_prompt";
    // Procesa la solicitud a la API utilizando el contenido del archivo.
    processAIRequest(filename);
    return 0;
}
