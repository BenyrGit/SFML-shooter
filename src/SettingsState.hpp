/****************************************
 Fichier		:	SettingsState.hpp
 Auteur			:	Benjamin Paquette
 Fonctionnalité :	Écran de configuration
 Date			:	25-06-2026

 Vérification	:
 JJ-MM-AAAA     Nom                     Approuvé
 =========================================================

 Historique de modifications :
 JJ-MM-AAAA     Nom                     Commentaire
 =========================================================

 ****************************************/
#pragma once

#include "Button.hpp"
#include "Container.hpp"
#include "Player.hpp"
#include "State.hpp"

#include <array>

class SettingsState : public State
{
public:
	SettingsState(StateStack& stack, Context context);

	void draw() override;
	bool update(sf::Time deltaTime) override;
	bool handleEvent(const sf::Event& event) override;

private:
	// méthodes
	void updateLabels();

	// attributs
	GUI::Container mGUIContainer;

	std::array<GUI::Button*, 4> mBindingButtons{};
	std::array<Player::Action, 4> mBindingActions{};

	std::size_t mActionBindingIndex = 0;
	bool mIsBinding = false;
};