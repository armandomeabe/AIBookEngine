// text_utils.hpp

#ifndef TEXT_UTILS_HPP
#define TEXT_UTILS_HPP

#include <string>
#include <vector>

class TextUtils {
public:
    static std::string toLowerCase(const std::string& str);
    static std::string removePunctuation(const std::string& str);
    static std::vector<std::string> tokenize(const std::string& str);
    static std::vector<std::string> removeStopWords(const std::vector<std::string>& tokens);
    static std::string trimAndReduce(const std::string& input);
    static std::string processText(const std::string& input);
    static std::string stringifyTokens(const std::vector<std::string>& tokens);
    static std::string readFileContents(const std::string& filename);
    static std::vector<std::string> splitString(const std::string& str);
};

#endif // TEXT_UTILS_HPP
