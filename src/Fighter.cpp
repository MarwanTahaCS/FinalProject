#pragma once
#include "Fighter.h"

Fighter::Fighter(const sf::Vector2f& p, const bool& objectTeam, const int& health, 
	const float& defaultAttack, const float& defaultGoldWorth)
	: AnimatedObject(p, objectTeam), LiveObject(p, objectTeam, health)
	, m_level(1), m_defaultAttack(defaultAttack), m_defaultGoldWorth(defaultGoldWorth),
	m_lastMovement(){
	// applying speed limits ------------------------------------------
	/*
	if (movementSpeed > MAX_MOVEMENT_SPEED &&
		movementSpeed < MIN_MOVEMENT_SPEED)
		m_movementSpeed = movementSpeed;
	else
		m_movementSpeed = (MIN_MOVEMENT_SPEED + MAX_MOVEMENT_SPEED) / 2;
	if (movementSpeed > MAX_ATTACK_SPEED &&
		movementSpeed < MIN_ATTACK_SPEED)
		m_attackSpeed = attackSpeed;
	else
		m_attackSpeed = (MIN_ATTACK_SPEED + MAX_ATTACK_SPEED) / 2;
		*/
	//-----------------------------------------------------------------
}

void Fighter::addLevel() {
	m_level++;
}

const float& Fighter::getLevel() const {
	return m_level;
}

const float& Fighter::getDefaultAttack() const {
	return m_defaultAttack;
}

float Fighter::getGoldWorth() const {
	return m_defaultGoldWorth;
}

//-------------------------------------------------
void Fighter::move(const std::shared_ptr<Fighter>& nextAlly,
	const std::shared_ptr<Fighter>& firstEnemy,
	const std::shared_ptr<Castle>& enemyCastle) {
	if ((nextAlly == NULL || !create(0).getGlobalBounds().intersects(nextAlly->create(0).getGlobalBounds())) &&
		(firstEnemy == NULL || !create(0).getGlobalBounds().intersects(firstEnemy->create(0).getGlobalBounds())) &&
		!create(0).getGlobalBounds().intersects(enemyCastle->create(0).getGlobalBounds())) {
		if (getAnimationType() == AnimationType::Idle)
			setAnimationType(AnimationType::Walk);
		if (getAnimationType() == AnimationType::Walk && m_clock.getElapsedTime().asMilliseconds() > FIGHTER_MOVEMENT_SPEED) {
			m_clock.restart();
			// moving enemy
			sf::Vector2f x = sf::Vector2f(
				WorldObject::get_position().x + ((WorldObject::get_object_team()) ? 1 : -1),
				WorldObject::get_position().y);

			WorldObject::set_position(x);
		}
	}
	else if (getAnimationType() == AnimationType::Walk) {
		setAnimationType(AnimationType::Idle);
	}
}