/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-tekspice-nils.colire
** File description:
** Parser
*/

#pragma once

#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <string>

struct ParsingData
{
    std::vector<std::pair<std::string, std::string>> components;
    std::vector<std::pair<std::string, int>> connections;
} typedef ParsingData;

struct ComponentParsingData
{
    std::string type;
    std::string name;
    char value;
    std::vector<std::pair<std::string, int>> pins;
} typedef ComponentParsingData;


ComponentParsingData **parse_input(std::string path);
