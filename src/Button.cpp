#pragma once

#include "Button.h"

Button::Button(sf::Vector2f position) :
	UIObject(position)
{}

bool Button::handle_click(const sf::Vector2f location) const {
	return create().getGlobalBounds().contains(location);
}

