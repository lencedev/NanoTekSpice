/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-tekspice-nils.colire
** File description:
** NanoTekSpice
*/

#include "NanoTekSpice.hpp"
#include "ElementaryComponent.hpp"
#include "SpecialComponent.hpp"


std :: ostream & operator <<( std :: ostream & s , nts :: Tristate v )
{
    if ( v == nts::Undefined )
        s << "U" ;
    else if ( v == nts::True )
        s << "1" ;
    else if ( v == nts::False )
        s << "0" ;
    return s ;
}

nts::Tristate nts::IComponent::compute(std::size_t pin)
{
    return (nts::Tristate::Undefined);
}

nts::Tristate nts::AComponent::getLink(std::size_t pin)
{
    if (_links.find(pin) == _links.end())
        return (nts::Tristate::Undefined);
    return (_links[pin].first->compute(_links[pin].second));
}

void nts::AComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    _links[pin] = std::make_pair(&other, otherPin);
}

std::map<std::size_t, std::pair<nts::IComponent *, std::size_t>> nts::AComponent::getLinks() const
{
    return (_links);
}

void nts::AComponent::simulate(std::size_t tick)
{
    std::cout << "simulate" << _name << std::endl;
}

void nts::Circuit::addComponent(const std::string &name, nts::IComponent &component)
{
    components_[name] = &component;
}

nts::IComponent &nts::Circuit::findComponent(const std::string &name)
{
    if (components_.find(name) == components_.end()) {
        std::cerr << "Component " << name << " not found" << std::endl;
        exit(84);
    }
    return (*components_[name]);
}

void nts::AComponent::reset()
{
    _state = nts::Tristate::Undefined;
}

void nts::Circuit::simulate2(std::size_t tick)
{
   if (tick == 0)
        return;
    for (const auto &component : components_) {
        // std::cout << "simulate " << component.first << std::endl;
        // if (component.second->_isInput == true) {
        //     continue;
        // } 
        component.second->compute();
    }
    simulate2(tick - 1);
}

void nts::Circuit::simulate(std::size_t tick)
{
   if (tick == 0)
        return;
    for (const auto &component : components_) {
        if (component.second->_isInput == true) {
            continue;
        } else {
            component.second->reset();
        }
    }
    for (const auto &component : components_) {
        // std::cout << "simulate " << component.first << std::endl;
        if (component.second->_isInput == true) {
            continue;
        } 
        component.second->compute();
    }
    // simulate2(tick - 1);
}

void nts::Circuit::display() {
    for (const auto &component : components_) {
        if (component.second->getType() == "output") {
            std::cout << component.first << "=" << component.second->getState() << std::endl;
        }
    }
}

void nts::Circuit::setLink(const std::string &name1, const std::string &name2)
{
    std::size_t pin1 = 0;
    std::size_t pin2 = 0;
    std::string name1_ = name1;
    std::string name2_ = name2;

    if (name1.find(":") != std::string::npos) {
        pin1 = std::stoi(name1.substr(name1.find(":") + 1));
        name1_ = name1.substr(0, name1.find(":"));
    }
    if (name2.find(":") != std::string::npos) {
        pin2 = std::stoi(name2.substr(name2.find(":") + 1));
        name2_ = name2.substr(0, name2.find(":"));
    }
    findComponent(name1_).setLink(pin1, findComponent(name2_), pin2);
}
