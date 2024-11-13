/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-tekspice-nils.colire
** File description:
** ElementaryComponent
*/

#pragma once

#include "NanoTekSpice.hpp"

namespace nts {
    class NotComponent : public AComponent {
        public:
            NotComponent() : AComponent("Not") {}

            nts::Tristate compute(std::size_t pin = 1);
    };

    class AndComponent : public AComponent {
        public:
            AndComponent() : AComponent("And") {}

            nts::Tristate compute(std::size_t pin = 1);
    };

    class OrComponent : public AComponent {
        public:
            OrComponent() : AComponent("Or") {}

            nts::Tristate compute(std::size_t pin = 1);
    };

    class XorComponent : public AComponent {
        public:
            XorComponent() : AComponent("Xor") {}

            nts::Tristate compute(std::size_t pin = 1);
    };
}