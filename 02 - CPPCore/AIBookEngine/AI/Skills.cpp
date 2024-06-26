//
//  Skills.cpp
//  AIBookEngine
//
//  Created by Armando Meabe on 03/05/2024.
//

#include "Skills.hpp"

Skill::Skill() {
    // Inicializa el mapa de habilidades con algunos ejemplos.
    skills["simplify"] = "Por favor simplifica el siguiente texto: {{ TEXT }}";
    skills["keywords"] = "Por favor extrae las palabras clave del siguiente texto, sin agregar nada mas que las palabras claves separadas por coma: {{ TEXT }}";
    skills["extractKeywords"] = "Dado el libro que describo a continuación: {{ TEXT }}... por favor extrae las palabras clave separads por coma. No agregues absolutamente nada ni antes ni después del texto que vas a generar, solamente expresa la idea principal sin agregado alguno. Es extremadamente importante que las palabras clave las extraigas en ESPAÑOL independientemente del idioma en el que el libro está escrito, y que NO AGREGUES ABSOLUTAMENTE NADA a las palabras clave, ninguna anotación posterior ni previa. SOLO LAS PALABRAS CLAVE.";
    skills["extractTLDR"] = "Dado el libro que describo a continuación: {{ TEXT }}... por favor elabora una oración que describa muy sintéticamente su idea principal en muy pocas palabras. Si tuviera más de una idea principal, sepáralas por coma.";

    skills["bookanalyze"] = "Dado el libro que describo a continuación: {{ TEXT }}... por favor extrae las palabras clave separads por coma. No agregues absolutamente nada ni antes ni después del texto que vas a generar, solamente expresa la idea principal sin agregado alguno.";
    // Puedes agregar más habilidades aquí.
}

std::string Skill::applySkill(const std::string& skillName, const std::string& text) const {
    auto it = skills.find(skillName);
    if (it != skills.end()) {
        std::string skillPrompt = it->second;
        // Reemplaza "{{ TEXT }}" con el texto proporcionado.
        size_t startPos = skillPrompt.find("{{ TEXT }}");
        if (startPos != std::string::npos) {
            skillPrompt.replace(startPos, std::string("{{ TEXT }}").length(), text);
        }
        return skillPrompt;
    } else {
        return "Habilidad no encontrada.";
    }
}
