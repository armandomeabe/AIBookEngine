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
};

#endif // TEXT_UTILS_HPP
