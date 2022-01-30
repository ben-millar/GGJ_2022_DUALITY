#include <SFML/Graphics.hpp>

class UI
{
public:
	UI() 
	{
		m_UIFont.loadFromFile("./assets/fonts/font.ttf");
		m_amountJumpsText.setFont(m_UIFont);
		m_amountJumpsText.setPosition(100, 50);
		m_amountJumpsText.setCharacterSize(28);
	};
	

	void draw(sf::RenderWindow& t_window) { t_window.draw(m_amountJumpsText); };

	void updateUI(int t_amountJumps, sf::Vector2f t_playerpos) { m_amountJumpsText.setString(" JUMPS: " + std::to_string(t_amountJumps)), m_amountJumpsText.setPosition(t_playerpos - sf::Vector2f(100,100)); };




private:
	sf::Font m_UIFont;
	sf::Text m_amountJumpsText;

};