#pragma once

enum labels { addstation = 1,removestation,travel,addstop,removestop, journey,back, };

class sidemenu{
	//play
	sf::Text addstation_text;
	sf::Text removestation_text;
	sf::Text travel_text;
	sf::Text addstop_text;
	sf::Text removestop_text;
	sf::Text journey_text;
	sf::Text exit_text;

	int selected_index;

public:
	sidemenu(sf::Font& font) {

		int charSize = 30;

		addstation_text.setFont(font);
		addstation_text.setString("Add Station ");
		addstation_text.setCharacterSize(charSize);
		addstation_text.setFillColor(sf::Color::White);
		addstation_text.setPosition(20, 70);

		removestation_text.setFont(font);
		removestation_text.setString("Remove Station");
		removestation_text.setCharacterSize(charSize);
		removestation_text.setFillColor(sf::Color::White);
		removestation_text.setPosition(20, 150);

		travel_text.setFont(font);
		travel_text.setString("Travel ");
		travel_text.setCharacterSize(charSize);
		travel_text.setFillColor(sf::Color::White);
		travel_text.setPosition(25, 220);

		addstop_text.setFont(font);
		addstop_text.setString("Add Stop ");
		addstop_text.setCharacterSize(charSize);
		addstop_text.setFillColor(sf::Color::White);
		addstop_text.setPosition(20, 70);

		journey_text.setFont(font);
		journey_text.setString("Show Journey");
		journey_text.setCharacterSize(charSize);
		journey_text.setFillColor(sf::Color::White);
		journey_text.setPosition(20, 220);

		removestop_text.setFont(font);
		removestop_text.setString("Remove Stop ");
		removestop_text.setCharacterSize(charSize);
		removestop_text.setFillColor(sf::Color::White);
		removestop_text.setPosition(20, 150);

		exit_text.setFont(font);
		exit_text.setString("Back ");
		exit_text.setCharacterSize(charSize);
		exit_text.setFillColor(sf::Color::White);
		exit_text.setPosition(20, 300);

		selected_index = -1;
	}


	void draw_Menu(sf::RenderWindow& window, int num) {

		

		if (!num) {
			
			window.draw(addstop_text);
			window.draw(removestop_text);
			window.draw(journey_text);
		}
		else {
			
			window.draw(addstation_text);
			window.draw(removestation_text);
			window.draw(travel_text);
		}

		window.draw(exit_text);
	}

	void Check_cursor(sf::RenderWindow& window) {
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

		if (addstation_text.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
		{
			addstation_text.setFillColor(sf::Color::Red);
		}
		else
		{
			addstation_text.setFillColor(sf::Color::White);

		}
		if (removestation_text.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
		{
			removestation_text.setFillColor(sf::Color::Red);
		}
		else
		{
			removestation_text.setFillColor(sf::Color::White);

		}

		if (exit_text.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
		{
			exit_text.setFillColor(sf::Color::Red);
		}
		else
		{
			exit_text.setFillColor(sf::Color::White);

		}

		if (travel_text.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
		{
			travel_text.setFillColor(sf::Color::Red);
		}
		else
		{
			travel_text.setFillColor(sf::Color::White);

		}
		if (removestop_text.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
		{
			removestop_text.setFillColor(sf::Color::Red);
		}
		else
		{
			removestop_text.setFillColor(sf::Color::White);

		}
		if (addstop_text.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
		{
			addstop_text.setFillColor(sf::Color::Red);
		}
		else
		{
			addstop_text.setFillColor(sf::Color::White);

		}

		if (journey_text.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
		{
			journey_text.setFillColor(sf::Color::Red);
		}
		else
		{
			journey_text.setFillColor(sf::Color::White);

		}
	}

	int Check_cursor_click(sf::RenderWindow& window, int num) {

		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

		if (num) {
			if (travel_text.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
			{
				return labels::travel ;
			}

			if (removestation_text.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
			{
				return labels::removestation;
			}
			if (addstation_text.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
			{
				return labels::addstation;
			}

		}
		else {
			if (removestop_text.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
			{
				return labels::removestop;
			}
			if (addstop_text.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
			{
				return labels::addstop;
			}
			if (journey_text.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
			{
				return labels::journey;
			}
		}

		if (exit_text.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
		{
			return labels::back;
		}

		return -1;
	}

};
