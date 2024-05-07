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
#include "skills.hpp"

class AIClient {
private:
    
public:
    AIClient();
    std::string Chat(const std::string& text);
    std::string Embed(const std::string& text);
};

#endif /* AIClient_hpp */
