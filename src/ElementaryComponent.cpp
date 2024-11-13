/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-tekspice-nils.colire
** File description:
** ElementaryComponent
*/

#include "ElementaryComponent.hpp"

nts::Tristate nts::NotComponent::compute(std::size_t pin) {
    if (pin != 2)
        return nts::Undefined;
    nts::Tristate input = _links[1].first->compute(_links[1].second);
    if (input == nts::Undefined)
        return nts::Undefined;
    _state = input == nts::True ? nts::False : nts::True;
    return input == nts::True ? nts::False : nts::True;
}

nts::Tristate nts::AndComponent::compute(std::size_t pin) {
    if (pin != 3)
        return (nts::Tristate::Undefined);
    nts::Tristate input_state1 = _links[1].first->compute(_links[1].second);
    nts::Tristate input_state2 = _links[2].first->compute(_links[2].second);
    if (input_state1 == nts::False || input_state2 == nts::False) {
        _state = nts::False;
        return (nts::False);
    }
    _state = nts::True;
    return (nts::True);
}

nts::Tristate nts::OrComponent::compute(std::size_t pin) {
    if (pin != 3)
        return (nts::Tristate::Undefined);
    nts::Tristate input_state1 = _links[1].first->compute(_links[1].second);
    nts::Tristate input_state2 = _links[2].first->compute(_links[2].second);
    if (input_state1 == nts::True || input_state2 == nts::True) {
        _state = nts::True;
        return (nts::True);
    }
    _state = nts::False;
    return (nts::False);
}

nts::Tristate nts::XorComponent::compute(std::size_t pin)
{
    if (pin != 3)
        return (nts::Tristate::Undefined);
    nts::Tristate input_state1 = _links[1].first->compute(_links[1].second);
    nts::Tristate input_state2 = _links[2].first->compute(_links[2].second);
    if (input_state1 == nts::Undefined || input_state2 == nts::Undefined) {
        _state = nts::Undefined;
        return nts::Undefined;
    }
    _state = (input_state1 == nts::True && input_state2 == nts::False) || (input_state1 == nts::False && input_state2 == nts::True) ? nts::True : nts::False;
    return (input_state1 == nts::True && input_state2 == nts::False) || (input_state1 == nts::False && input_state2 == nts::True) ? nts::True : nts::False;
}
