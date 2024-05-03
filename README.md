# AIBookEngine
AIBookEngine is a robust C++ toolkit that harnesses the power of artificial intelligence to facilitate advanced book recommendation and literary analysis. By incorporating a series of sophisticated text preprocessing algorithms, AIBookEngine effectively normalizes, tokenizes, and filters textual data, paving the way for AI models to interpret and analyze book content with precision. Designed to be both modular and scalable, it offers a solid foundation for developers looking to build or enhance book discovery platforms and digital library services with intelligent, personalized user experiences.

AIBookEngine includes a suite of text preprocessing tools that prepare literary data for in-depth analysis and discovery.

## Features

- Text normalization to convert text to a uniform case
- Punctuation removal for cleaner text analysis
- Tokenization to split text into individual words or tokens
- Stop word removal to filter out common words in Spanish

## Getting Started

To get started with AIBookEngine, clone the repository to your local machine using the following command:

```bash
git clone https://github.com/armandomeabe/AIBookEngine.git
```

### Prerequisites

Make sure you have a C++ compiler installed on your system (such as `g++` on Linux or Clang on macOS).

### Building the Project

Navigate to the project directory and run the following command to build the project:

```bash
g++ -o AIBookEngine main.cpp text_utils.cpp
```

Replace `main.cpp` and `text_utils.cpp` with the paths to your source files.

## Usage

Here's a brief example of how to use the text preprocessing functionalities provided by AIBookEngine:

```cpp
#include "text_utils.hpp"
#include <iostream>
#include <vector>

int main() {
    std::string text = "El rápido zorro marrón salta sobre el perro perezoso.";

    // Normalize text to lowercase
    std::string lower = TextUtils::toLowerCase(text);

    // Remove punctuation
    std::string no_punct = TextUtils::removePunctuation(lower);

    // Tokenize the text
    std::vector<std::string> tokens = TextUtils::tokenize(no_punct);

    // Remove stop words
    std::vector<std::string> filtered_tokens = TextUtils::removeStopWords(tokens);

    // Output the processed tokens
    for (const auto& token : filtered_tokens) {
        std::cout << token << std::endl;
    }

    return 0;
}
```

## New Features

- Skills system to apply predefined prompts or transformations to text such as simplification, summarization, etc.

## Skills System

The Skills system is designed to apply specific transformations to a given text. These transformations are defined as "skills" and each skill is associated with a prompt that describes the action to be taken on the text.

### How to Use Skills

Here's an example of how to use the skills system:

```cpp
#include "Skills.hpp"
#include <iostream>

int main() {
    Skill skillSet;
    std::string textToSimplify = "Este es un ejemplo de texto que será simplificado.";
    std::string simplifiedText = skillSet.applySkill("simplificar", textToSimplify);
    
    std::cout << simplifiedText << std::endl;
    
    return 0;
}

## Contributing

We welcome contributions to AIBookEngine! If you have suggestions or improvements, please fork the repository and create a pull request, or open an issue with the tag "enhancement".

Don't forget to give the project a star if you find it helpful!

## Author

**Armando Andrés Meabe**

- LinkedIn: [Armando Meabe](https://www.linkedin.com/in/armandomeabe/)

---

Thank you for checking out AIBookEngine. If you have any questions or comments, please feel free to reach out.

## License

This project is open-source and available under the [MIT License](LICENSE).
