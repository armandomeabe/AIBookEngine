//
//  AIClient.hpp
//  AIBookEngine
//
//  Created by Armando Meabe on 07/05/2024.
//

#ifndef AIClient_hpp
#define AIClient_hpp

#include <stdio.h>
#include <string>

#include "CurlHelper.hpp"
#include "text_utils.hpp"
#include "Skills.hpp"
#include "Embedding.hpp"

class AIClient {
private:
    
public:
    AIClient();
    std::string Generate(const std::string& text);
    Embedding Embed(const std::string& text);
};

#endif /* AIClient_hpp */
