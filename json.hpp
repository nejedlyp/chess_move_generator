//
// Created by Petr on 17.03.2024.
//

#ifndef ENGINE_JSON_HPP
#define ENGINE_JSON_HPP
#include "string"
#include "map"
#include "sstream"
#include <fstream>
#include <iostream>

using namespace std;


std::map<std::string, std::vector<std::string>> parseSimpleJson(const std::string& path_json) {
    // Open the file
    std::ifstream file(path_json);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << path_json << std::endl;
        return {};
    }

    // Read the file content into a string
    std::string json((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    std::map<std::string, std::string> result;
    std::istringstream stream(json);
    stream >> std::noskipws;

    char ch;

    // Assuming the JSON starts with an object '{'
    stream >> ch;

    std::string key, value;
    bool isKey = true; // Toggle between key and value
    bool inString = false;

    while (stream >> ch) {
        if (ch == '"') {
            inString = !inString;
        } else if (inString) {
            (isKey ? key : value) += ch;
        } else if (ch == ':') {
            isKey = false; // Next, we read the value
        } else if (ch == ',' || ch == '}') {
            // End of the value, insert into map
            result[key] = value;
            key.clear();
            value.clear();
            isKey = true; // Next, we read a key
            if (ch == '}') break; // End of the object
        }
    }

    std::map<std::string, std::vector<std::string>> result_parsed;
    for (auto const& [key, val] : result) {
        std::istringstream stream(val);
        std::string token;
        std::vector<std::string> tokens;
        while (std::getline(stream, token, ',')) {
            tokens.push_back(token);
        }
        result_parsed[key] = tokens;
    }


    return result_parsed;
}

#endif //ENGINE_JSON_HPP
