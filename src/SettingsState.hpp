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
 10-07-2026		Benjamin Paquette		Sécuriser l'assignation des touches
 12-07-2026		Benjamin Paquette		Ajout d'informations contextuelles
 ****************************************/
#pragma once

#include "Button.hpp"
#include "Container.hpp"
#include "Player.hpp"
#include "State.hpp"
#include "Label.hpp"

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
	bool isBindingKeyAllowed(sf::Keyboard::Key key) const;

	// attributs
	GUI::Container mGUIContainer;
	GUI::Label* mInfoLabel = nullptr;

	std::array<GUI::Button*, 4> mBindingButtons{};
	std::array<Player::Action, 4> mBindingActions{};

	std::size_t mActionBindingIndex = 0;
	bool mIsBinding = false;
};