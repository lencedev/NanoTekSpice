/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-tekspice-nils.colire
** File description:
** SpecialComponent
*/

#include "SpecialComponent.hpp"


nts::Tristate nts::InputComponent::compute(std::size_t pin)
{
    if (pin != 1)
        return (nts::Tristate::Undefined);
    return (_state);
}

nts::Tristate nts::InputComponent::getState()
{
    return (_state);
}

void nts::InputComponent::setState(nts::Tristate state)
{
    _state = state;
}

nts::Tristate nts::OutputComponent::compute(std::size_t pin)
{
    if (pin != 1)
        return (nts::Tristate::Undefined);
    nts::Tristate res = getLink(1);
    _state = res;
    return _state;
}

void nts::ClockComponent::simulate(std::size_t tick)
{
    (void)tick;
    if (_state == nts::Tristate::False) {
        _state = nts::Tristate::True;
    } else if (_state == nts::Tristate::True) {
        _state = nts::Tristate::False;
    } else {
        _state = nts::Tristate::Undefined;
    }
}

nts::Tristate nts::ClockComponent::compute(std::size_t pin)
{
    if (pin != 1)
        return (nts::Tristate::Undefined);
    if (_state == nts::Tristate::False) {
        _state = nts::Tristate::True;
    } else if (_state == nts::Tristate::True) {
        _state = nts::Tristate::False;
    } else {
        _state = nts::Tristate::Undefined;
    }
    return (_state);
}

nts::Tristate nts::TrueComponent::compute(std::size_t pin)
{
    if (pin != 1)
        return (nts::Tristate::Undefined);
    // _state = nts::Tristate::True;
    return (nts::Tristate::True);
}

nts::Tristate nts::FalseComponent::compute(std::size_t pin)
{
    if (pin != 1)
        return (nts::Tristate::Undefined);
    // _state = nts::Tristate::False;
    return (nts::Tristate::False);
}
