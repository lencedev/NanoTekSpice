/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-tekspice-nils.colire
** File description:
** Parser
*/

#include "Parser.hpp"
#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <string>
#include <unordered_map>

ComponentParsingData **parse_input(std::string path)
{
    std::ifstream f(path);

    std::vector<std::pair<std::string, std::string>> components;
    std::vector<std::pair<std::string, int>> connections;

    std::string line;
    while (std::getline(f, line)) {
        std::regex component_regex(R"(^(\w+)\s+(\w+))");
        std::smatch component_match;
        if (std::regex_match(line, component_match, component_regex)) {
            std::string component_name = component_match[1].str();
            std::string value = component_match[2].str();
            components.push_back(std::make_pair(component_name, value));
        }
        std::regex connection_regex(R"(^(\w+):(\d+)\s+(\w+):(\d+))");
        std::smatch connection_match;
        if (std::regex_match(line, connection_match, connection_regex)) {
            std::string from_component = connection_match[1].str();
            int from_port = std::stoi(connection_match[2].str());
            std::string to_component = connection_match[3].str();
            int to_port = std::stoi(connection_match[4].str());
            connections.push_back(std::make_pair(from_component, from_port));
            connections.push_back(std::make_pair(to_component, to_port));
        }
    }
    ParsingData data;
    data.components = components;
    data.connections = connections;

    for (int i = 0; i < data.components.size(); i++) {
        int is_valid = 0;
        for (int j = 0; j < data.connections.size(); j++) {
            if (data.components[i].second == data.connections[j].first) {
                is_valid = 1;
            }
        }
        if (!is_valid) {
            std::cerr << "Unknow component name" << std::endl;
            exit(84);
        }
    }

    if (!components.size() || !connections.size()) {
        std::cerr << "Error: Invalid file" << std::endl;
        exit(84);
    }

    ComponentParsingData **components_data = new ComponentParsingData *[components.size() + 1];

    // add components to components_data and add links in both components with the good pin number connections.second. LINKS ARE BI-DIRECTIONAL. In this format : linkfrom:pinfrom/linkto:pinto
    std::unordered_map<std::string, int> components_map;
    for (int i = 0; i < components.size(); i++) {
        components_map[components[i].second] = i;
        components_data[i] = new ComponentParsingData;
        components_data[i]->type = components[i].first;
        components_data[i]->name = components[i].second;
        components_data[i]->value = 'U';
    }

    for (int i = 0; i < connections.size(); i += 2) {
        std::string from_component = connections[i].first;
        int from_port = connections[i].second;
        std::string to_component = connections[i + 1].first;
        int to_port = connections[i + 1].second;
        components_data[components_map[from_component]]->pins.push_back(std::make_pair(to_component, to_port));
        components_data[components_map[to_component]]->pins.push_back(std::make_pair(from_component, from_port));
    }


    // std::cout << "Finished" << std::endl;

    components_data[components.size()] = nullptr;

    // for (int i = 0; components_data[i]; i++) {
    //     std::cout << "Component: " << components_data[i]->type << std::endl;
    //     std::cout << "Name: " << components_data[i]->name << std::endl;
    //     std::cout << "Value: " << components_data[i]->value << std::endl;
    //     std::cout << "pins: " << std::endl;
    //     for (int j = 0; j < components_data[i]->pins.size(); j++) {
    //         std::cout << "    " << components_data[i]->pins[j].first << ":" << components_data[i]->pins[j].second << std::endl;
    //     }
    //     std::cout << std::endl;
    // }

    return components_data;
}
