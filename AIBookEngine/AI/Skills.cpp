//
//  Skills.cpp
//  AIBookEngine
//
//  Created by Armando Meabe on 03/05/2024.
//

#include "Skills.hpp"

Skill::Skill() {
    // Inicializa el mapa de habilidades con algunos ejemplos.
    skills["simplify"] = "Por favor simplifica el siguiente texto: {{ TEXTO }}";
    // Puedes agregar más habilidades aquí.
}

std::string Skill::applySkill(const std::string& skillName, const std::string& text) const {
    auto it = skills.find(skillName);
    if (it != skills.end()) {
        std::string skillPrompt = it->second;
        // Reemplaza "{{ TEXTO }}" con el texto proporcionado.
        size_t startPos = skillPrompt.find("{{ TEXTO }}");
        if (startPos != std::string::npos) {
            skillPrompt.replace(startPos, std::string("{{ TEXTO }}").length(), text);
        }
        return skillPrompt;
    } else {
        return "Habilidad no encontrada.";
    }
}
