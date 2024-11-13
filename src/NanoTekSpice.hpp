/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-tekspice-nils.colire
** File description:
** NanoTekSpice
*/

#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <map>

namespace nts {
    enum Tristate {
        Undefined = (-true),
        True = true,
        False = false
    };

    class IComponent {
    public:
        virtual ~IComponent() = default;

        virtual nts::Tristate compute(std::size_t pin = 1) = 0;
        virtual void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) = 0;
        virtual std::string getType() const { return ""; }
        virtual void setState(nts::Tristate state) { _state = state; }
        virtual nts::Tristate getState() const { return _state; }
        virtual void simulate(std::size_t tick) = 0;
        virtual void reset() = 0;

        bool _isInput = false;
        nts::Tristate _clockState = nts::Tristate::Undefined;
        nts::Tristate _state;
    protected:
    };

    class AComponent : public IComponent {
    public:
        AComponent(std::string const &name) : _name(name) {}

        void simulate(std::size_t tick);
        void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin);
        nts::Tristate getLink(std::size_t pin);
        std::map<std::size_t, std::pair<nts::IComponent *, std::size_t>> getLinks() const;
        void reset();

    protected:
        std::map<std::size_t, std::pair<nts::IComponent *, std::size_t>> _links;
        std::string _name;
    };

    class Circuit {
        public:
        Circuit() = default;
        ~Circuit() = default;
        
        void addComponent(const std::string& name, nts::IComponent& component);
        nts::IComponent& findComponent(const std::string& name);
        void simulate(std::size_t tick);
        void simulate2(std::size_t tick);
        void display();
        void setLink(const std::string& name1, const std::string& name2);

        private:
        std::unordered_map<std::string, nts::IComponent*> components_;
        std::vector<std::pair<std::string, std::string>> links_;
    };
};