//
//  Skills.hpp
//  AIBookEngine
//
//  Created by Armando Meabe on 03/05/2024.
//

#ifndef Skills_hpp
#define Skills_hpp

#include <stdio.h>

#include <string>
#include <unordered_map>

class Skill {
private:
    std::unordered_map<std::string, std::string> skills;

public:
    Skill(); // Constructor que inicializa las habilidades disponibles.
    std::string applySkill(const std::string& skillName, const std::string& text) const;
};

#endif /* Skills_hpp */
