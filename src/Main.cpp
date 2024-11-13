/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-tekspice-nils.colire
** File description:
** Main
*/

#include <iostream>
#include "NanoTekSpice.hpp"
#include "Parser.hpp"
#include "ElementaryComponent.hpp"
#include "SpecialComponent.hpp"

nts::Circuit createCircuit(ComponentParsingData **data)
{
    nts::Circuit circuit;

   
    for (int i = 0; data[i]; i++) {
        if (data[i]->type == "input") {
            circuit.addComponent(data[i]->name, *new nts::InputComponent(nts::Tristate::Undefined));
            circuit.findComponent(data[i]->name)._isInput = true;
            circuit.findComponent(data[i]->name)._state = nts::Tristate::Undefined;
        }
        if (data[i]->type == "output") {
            circuit.addComponent(data[i]->name, *new nts::OutputComponent());
            circuit.findComponent(data[i]->name)._state = nts::Tristate::Undefined;
        }
        if (data[i]->type == "true") {
            circuit.addComponent(data[i]->name, *new nts::TrueComponent());
            circuit.findComponent(data[i]->name)._state = nts::Tristate::True;
            circuit.findComponent(data[i]->name)._isInput = true;
        }
        if (data[i]->type == "false") {
            circuit.addComponent(data[i]->name, *new nts::FalseComponent());
            circuit.findComponent(data[i]->name)._state = nts::Tristate::False;
            circuit.findComponent(data[i]->name)._isInput = true;
        }
        if (data[i]->type == "clock") {
            circuit.addComponent(data[i]->name, *new nts::ClockComponent());
            circuit.findComponent(data[i]->name)._state = nts::Tristate::Undefined;
            circuit.findComponent(data[i]->name)._isInput = true;
        }
        if (data[i]->type == "or") {
            circuit.addComponent(data[i]->name, *new nts::OrComponent());
            circuit.findComponent(data[i]->name)._state = nts::Tristate::Undefined;
        }
        if (data[i]->type == "and") {
            circuit.addComponent(data[i]->name, *new nts::AndComponent());
            circuit.findComponent(data[i]->name)._state = nts::Tristate::Undefined;

        }
        if (data[i]->type == "xor") {
            circuit.addComponent(data[i]->name, *new nts::XorComponent());
            circuit.findComponent(data[i]->name)._state = nts::Tristate::Undefined;
        }
        if (data[i]->type == "not") {
            circuit.addComponent(data[i]->name, *new nts::NotComponent());
            circuit.findComponent(data[i]->name)._state = nts::Tristate::Undefined;
        }
    }

    for (int i = 0; data[i]; i++) {
        for (int j = 0; j < data[i]->pins.size(); j++) {
            circuit.findComponent(data[i]->name).setLink(j + 1, circuit.findComponent(data[i]->pins[j].first), data[i]->pins[j].second);
            circuit.findComponent(data[i]->pins[j].first).setLink(data[i]->pins[j].second, circuit.findComponent(data[i]->name), j + 1);
        }
    }
    
    return (circuit);
}

std::string inputUser(std::string &input, nts::Circuit &circuit)
{
    std::string name;
    std::string value;

    name = input.substr(0, input.find("="));
    value = input.substr(input.find("=") + 1);
    if (value != "0" && value != "1" && value != "U")
        exit(84);
    if (value[0] == 'U')
        value = "-1";
    if (value[0] == '0') {
        circuit.findComponent(name)._state = nts::Tristate::False;
    } else if (value[0] == '1') {
        circuit.findComponent(name)._state = nts::Tristate::True;
    }
    else if (value == "-1") {
        circuit.findComponent(name)._state = nts::Tristate::Undefined;
    }

    return (name + "/" + value);
}

int main(int ac, char **av)
{
    if (ac != 2)
        return (84);
    ComponentParsingData **data = parse_input(av[1]);
    if (data == nullptr)
        return (84);

    nts::Circuit circuit;
    int tick = 0;
    std::vector<std::string> changed_names;
    std::vector<std::string> changed_values;
    std::string components[9] = {"input","output","true","false","clock","and","or","xor", "not"};

    circuit = createCircuit(data);

    int passed = 0;

    for (int i = 0; data[i]; i++) {
       if (data[i]->type == "false") {
            circuit.findComponent(data[i]->name)._state = nts::Tristate::False;
            data[i]->value = '0';
            passed++;
        }
        if (data[i]->type == "true") {
            circuit.findComponent(data[i]->name)._state = nts::Tristate::True;
            data[i]->value = '1';
            passed++;
        }
    }

    if (passed != 0) {
        circuit.simulate(1);

        for (int i = 0; data[i]; i++) {
            if (data[i]->type == "output") {
                data[i]->value = circuit.findComponent(data[i]->name)._state == nts::Tristate::True ? '1' : '0';
            }
        }
    }


    while (1) {
        std::cout << "> ";
        std::string input;
        std::cin >> input;

        if (std::cin.eof()) {
            exit(0);
        }
        if (input == "exit")
            break;
        if (input == "simulate") {
            tick++;

            int varChanged = 0;
            
            for (int i = 0; data[i]; i++) {
                if (changed_names.size()) {
                    varChanged = 1;
                    for (int j = 0; j < changed_names.size(); j++) {
                        if (data[i]->name == changed_names[j]) {
                            if (changed_values[j][0] == '0')
                                circuit.findComponent(data[i]->name)._state = nts::Tristate::False;
                            else if (changed_values[j][0] == '1')
                                circuit.findComponent(data[i]->name)._state = nts::Tristate::True;
                            else if (changed_values[j][0] == 'U' || changed_values[j][0] == '-')
                                circuit.findComponent(data[i]->name)._state = nts::Tristate::Undefined;
                            changed_names.erase(changed_names.begin() + j);
                            changed_values.erase(changed_values.begin() + j);

                            
                        }
                    }
                }
            }
            if (varChanged == 1) {
                circuit.simulate(tick);
                circuit.simulate(tick);
            } else {
                circuit.simulate(tick);
            }

            for (int i = 0; data[i]; i++) {
                if (data[i]->type == "false") {
                    circuit.findComponent(data[i]->name)._state = nts::Tristate::False;
                    continue;
                }
                if (data[i]->type == "true") {
                    circuit.findComponent(data[i]->name)._state = nts::Tristate::True;
                    continue;
                }
                if (circuit.findComponent(data[i]->name).getState() == nts::Tristate::True) {
                    data[i]->value = '1';
                } else if (circuit.findComponent(data[i]->name).getState() == nts::Tristate::False) {
                    data[i]->value = '0';
                } else if (circuit.findComponent(data[i]->name).getState() == nts::Tristate::Undefined) {
                    data[i]->value = 'U';
                }   
            }
        }

        if (input.find("=") != std::string::npos) {
            std::string name = inputUser(input, circuit);
            changed_names.push_back(name.substr(0, name.find("/")));
            changed_values.push_back(name.substr(name.find("/") + 1));
        }
        if (input == "display") {
            std::cout << "tick: " << tick << std::endl;
            std::cout << "input(s):" << std::endl;
            for (int i = 0; data[i]; i++) {
                for (int j = 0; j < 9; j++) {
                    if (data[i]->type == components[j] && data[i]->type != "output") {
                        std::cout << "  " << data[i]->name << ": " << data[i]->value << std::endl;
                    }
                }
            }
            std::cout << "output(s):" << std::endl;
            for (int i = 0; data[i]; i++) {
                if (data[i]->type == "output") {
                    std::cout << "  " << data[i]->name << ": " << data[i]->value << std::endl;
                }
            }
        }
    }

    return (0);
}
