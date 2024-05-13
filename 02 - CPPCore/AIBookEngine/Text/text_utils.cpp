// text_utils.cpp

#include "text_utils.hpp"
#include <algorithm>
#include <sstream>
#include <unordered_set>
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <sstream>

// Lee el contenido completo de un archivo y lo devuelve como una cadena de texto.
std::string TextUtils::readFileContents(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return buffer.str();
}

/**
 * Converts a string to lowercase.
 * @param str The string to be converted to lowercase.
 * @return A new string with all characters in lowercase.
 */
std::string TextUtils::toLowerCase(const std::string& str) {
    std::string lower_case_str = str;
    std::transform(lower_case_str.begin(), lower_case_str.end(), lower_case_str.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return lower_case_str;
}

/**
 * Removes punctuation from a string.
 * @param str The string from which to remove punctuation.
 * @return A new string with punctuation removed.
 */
std::string TextUtils::removePunctuation(const std::string& str) {
    std::string no_punct_str;
    std::remove_copy_if(str.begin(), str.end(), std::back_inserter(no_punct_str),
        [](unsigned char c) { return std::ispunct(c); });
    return no_punct_str;
}

/**
 * Tokenizes a string into a vector of words.
 * @param str The string to tokenize.
 * @return A vector of tokens (words) from the given string.
 */
std::vector<std::string> TextUtils::tokenize(const std::string& str) {
    std::istringstream iss(str);
    std::vector<std::string> tokens;
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

/**
 * Trims leading and trailing whitespace and reduces multiple spaces to a single space.
 * @param input The string to trim and reduce.
 * @return A new string with excess whitespace removed.
 */
std::string TextUtils::trimAndReduce(const std::string& input) {
    std::string result;
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

/**
 * Removes common stop words from a vector of tokens.
 * @param tokens The vector of tokens from which to remove stop words.
 * @return A new vector of tokens with stop words removed.
 */
std::vector<std::string> TextUtils::removeStopWords(const std::vector<std::string>& tokens) {
    std::vector<std::string> filtered_tokens;
    std::unordered_set<std::string> stop_words{
        "a", "al", "algo", "algún", "alguna", "algunas", "alguno", "algunos", "ante", "antes", "como", "con", "contra", "cual",
        "cuando", "de", "del", "desde", "donde", "durante", "e", "el", "ella", "ellas", "ello", "ellos", "en", "entre", "era",
        "erais", "eran", "eras", "eres", "es", "esa", "esas", "ese", "eso", "esos", "esta", "estaba", "estabais", "estaban",
        "estabas", "estad", "estada", "estadas", "estado", "estados", "estamos", "estando", "estar", "estaremos", "estará",
        "estarán", "estarás", "estaré", "estaréis", "estaría", "estaríais", "estaríamos", "estarían", "estarías", "estas",
        "este", "estemos", "esto", "estos", "estoy", "estuve", "estuviera", "estuvierais", "estuvieran", "estuvieras",
        "estuvieron", "estuviese", "estuvieseis", "estuviesen", "estuvieses", "estuvimos", "estuviste", "estuvisteis",
        "estuvo", "está", "estábamos", "estáis", "están", "estás", "esté", "estéis", "estén", "estés", "fue", "fuera",
        "fuerais", "fueran", "fueras", "fueron", "fuese", "fueseis", "fuesen", "fueses", "fui", "fuimos", "fuiste",
        "fuisteis", "fácil", "ha", "habida", "habidas", "habido", "habidos", "habiendo", "habremos", "habrá", "habrán",
        "habrás", "habré", "habréis", "habría", "habríais", "habríamos", "habrían", "habrías", "habéis", "había", "habíais",
        "habíamos", "habían", "habías", "han", "has", "hasta", "hay", "haya", "hayamos", "hayan", "hayas", "hayáis", "he",
        "hemos", "hube", "hubiera", "hubierais", "hubieran", "hubieras", "hubieron", "hubiese", "hubieseis", "hubiesen",
        "hubieses", "hubimos", "hubiste", "hubisteis", "hubo", "la", "las", "le", "les", "lo", "los", "me", "mi", "mis",
        "mucho", "muchos", "muy", "más", "mí", "mía", "mías", "mío", "míos", "nada", "ni", "no", "nos", "nosotras", "nosotros",
        "nuestra", "nuestras", "nuestro", "nuestros", "o", "os", "otra", "otras", "otro", "otros", "para", "pero", "poco",
        "por", "porque", "que", "quien", "quienes", "qué", "se", "sea", "seamos", "sean", "seas", "seremos", "será", "serán",
        "serás", "seré", "seréis", "sería", "seríais", "seríamos", "serían", "serías", "seáis", "sido", "siendo", "sin",
        "sobre", "sois", "somos", "son", "soy", "su", "sus", "suya", "suyas", "suyo", "suyos", "sí", "también", "tanto",
        "te", "tendremos", "tendrá", "tendrán", "tendrás", "tendré", "tendréis", "tendría", "tendríais", "tendríamos",
        "tendrían", "tendrías", "tened", "tenemos", "tenga", "tengamos", "tengan", "tengas", "tengo", "tengáis", "tenida",
        "tenidas", "tenido", "tenidos", "teniendo", "tenéis", "tenía", "teníais", "teníamos", "tenían", "tenías", "ti",
        "tiene", "tienen", "tienes", "todo", "todos", "tu", "tus", "tuve", "tuviera", "tuvierais", "tuvieran", "tuvieras",
        "tuvieron", "tuviese", "tuvieseis", "tuviesen", "tuvieses", "tuvimos", "tuviste", "tuvisteis", "tuvo", "tuya",
        "tuyas", "tuyo", "tuyos", "tú", "un", "una", "unas", "uno", "unos", "vosotras", "vosotros", "vuestra", "vuestras",
        "vuestro", "vuestros", "y", "ya", "yo", "él", "éramos"
    };

    std::copy_if(tokens.begin(), tokens.end(), std::back_inserter(filtered_tokens),
        [&stop_words](const std::string& token) { return stop_words.find(token) == stop_words.end(); });
    return filtered_tokens;
}

/**
 * Combines a vector of tokens into a single string, with tokens separated by spaces.
 * @param tokens The vector of tokens to combine.
 * @return A single string containing all the tokens separated by a single space.
 */
std::string TextUtils::stringifyTokens(const std::vector<std::string>& tokens) {
    std::string combined;
    for (const auto& token : tokens) {
        if (!combined.empty()) {
            combined += " "; // Add a space before each token, except the first one
        }
        combined += token;
    }
    return combined;
}


/**
 * Processes a string by applying a series of text preprocessing steps:
 * converting to lowercase, removing punctuation, tokenizing, trimming and
 * reducing whitespace, and removing stop words.
 * @param input The string to process.
 * @return A vector of processed tokens with stop words removed.
 */
std::string TextUtils::processText(const std::string& input) {
    // Convert to lowercase
    std::string lower = toLowerCase(input);
    
    // Remove punctuation
    std::string noPunct = removePunctuation(lower);
    
    // Tokenize the text
    std::vector<std::string> tokens = tokenize(noPunct);
    
    // Trim and reduce spaces (Note: This might not be necessary after tokenization)
    std::string trimmedAndReduced = trimAndReduce(noPunct); // Should we still use 'noPunct' or 'tokens'?
    
    // Remove stop words from tokens
    std::vector<std::string> filteredTokens = removeStopWords(tokens);
    
    auto stringify = stringifyTokens(filteredTokens);
    
    return stringify;
}

std::vector<std::string> TextUtils::splitString(const std::string& str) {
    std::vector<std::string> words;
    std::stringstream ss(str);
    std::string word;

    while (std::getline(ss, word, ',')) {
        words.push_back(word);
    }

    return words;
}
