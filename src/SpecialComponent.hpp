/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-tekspice-nils.colire
** File description:
** SpecialComponent
*/

#pragma once

#include "NanoTekSpice.hpp"

namespace nts {
    class InputComponent : public AComponent {
    public:
        InputComponent(nts::Tristate state) : AComponent("Input") {_state = state;};

        nts::Tristate compute(std::size_t pin = 1) override;
        void setState(nts::Tristate state);
        nts::Tristate getState();
    private:
        nts::Tristate _state;
    };

    class OutputComponent : public AComponent {
    public:
        OutputComponent() : AComponent("Output") {};

        nts::Tristate compute(std::size_t pin = 1);
    };

    class TrueComponent : public nts::AComponent {
    public:
        TrueComponent() : AComponent("True") {};

        nts::Tristate compute(std::size_t pin = 1);
    };

    class FalseComponent : public nts::AComponent {
    public:
        FalseComponent() : AComponent("False") {};

        nts::Tristate compute(std::size_t pin = 1);
    };

    class ClockComponent : public nts::AComponent {
    public:
        ClockComponent() : AComponent("Clock") {};
        
        void simulate(std::size_t tick);
        nts::Tristate compute(std::size_t pin = 1);
    };
}