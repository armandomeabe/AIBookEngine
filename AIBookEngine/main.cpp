#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <sstream>
#include "CurlHelper.hpp"
#include "text_utils.hpp"
#include "skills.hpp"

using namespace std;



int main() {
    // Define la ruta al archivo que se va a procesar.
    const string filename = "/Users/armandomeabe/Code/AIBookEngine/AIBookEngine/sample_prompt";
    
    // Lee el contenido del archivo y lo prepara para la solicitud.
    string description = TextUtils::readFileContents(filename);
    
    // Procesa la solicitud a la API utilizando el contenido del archivo.
    processAIRequest(description);
    
    // todo list
    // hacer que processAIRequest sea una version especializada en "chat" y aparte haya otra implementacion para embeddings
    // hacer que ademas de escribir en consola, devuelvan el string
    
    return 0;
}
