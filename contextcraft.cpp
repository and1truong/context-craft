#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <sstream>
#include <algorithm>
#include <map>

namespace fs = std::filesystem;

// Function to split a string by a delimiter
std::vector<std::string> splitString(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Function to check if a string ends with a specific extension
bool hasExtension(const std::string& filename, const std::vector<std::string>& extensions) {
    if (extensions.empty()) {
        return true; // If no extensions are specified, include all files
    }
    for (const std::string& ext : extensions) {
        if (filename.size() >= ext.size() &&
            filename.substr(filename.size() - ext.size()) == ext) {
            return true;
        }
    }
    return false;
}

// Function to generate the YAML output
std::string generateYAML(const std::map<std::string, std::string>& fileContents) {
    std::stringstream yamlStream;
    yamlStream << "context:\n";
    for (const auto& pair : fileContents) {
        yamlStream << "    " << pair.first << ": |\n";
        // Properly indent the file content
        std::istringstream iss(pair.second);
        std::string line;
        while (std::getline(iss, line)) {
            yamlStream << "        " << line << "\n";
        }
    }
    yamlStream << "instructions:\n";
    yamlStream << "    - TODO\n";
    return yamlStream.str();
}


int main(int argc, char* argv[]) {
    // Default values
    std::string directory = "";
    std::vector<std::string> extensions;

    // Parse command-line arguments
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--extensions") {
            if (i + 1 < argc) {
                extensions = splitString(argv[i + 1], ',');
                ++i; // Skip the next argument (extensions value)
            } else {
                std::cerr << "Error: --extensions requires a value." << std::endl;
                return 1;
            }
        } else if (directory.empty()) {
            directory = arg;
        } else {
          std::cerr << "Usage: contextcraft <directory> --extensions=go,yaml" << std::endl;
          return 1;
        }
    }

      if (directory.empty()) {
        std::cerr << "Usage: contextcraft <directory> --extensions=go,yaml" << std::endl;
        return 1;
    }


    // Check if the directory exists
    if (!fs::exists(directory) || !fs::is_directory(directory)) {
        std::cerr << "Error: Directory does not exist or is not a directory: " << directory << std::endl;
        return 1;
    }

    std::map<std::string, std::string> fileContents;

    // Walk through the directory
    for (const auto& entry : fs::recursive_directory_iterator(directory)) {
        if (fs::is_regular_file(entry) && hasExtension(entry.path().filename().string(), extensions)) {
            std::ifstream file(entry.path());
            if (file.is_open()) {
                std::stringstream buffer;
                buffer << file.rdbuf();
                std::string content = buffer.str();
                file.close();

                // Get the relative path
                std::string relativePath = fs::relative(entry.path(), directory).string();
                fileContents[relativePath] = content;
            } else {
                std::cerr << "Error: Could not open file: " << entry.path() << std::endl;
                return 1;
            }
        }
    }

    // Generate YAML output
    std::string yamlOutput = generateYAML(fileContents);
    std::cout << yamlOutput << std::endl;

    return 0;
}
