#include <SFML/Graphics.hpp>

//testing if sfml works
int main()
{
    sf::RenderWindow window(sf::VideoMode(300, 300), "SFML works!");
    sf::CircleShape shape(150.f);
    shape.setFillColor(sf::Color::Green);
    sf::CircleShape shape2(75.f);
    shape2.setFillColor(sf::Color::Blue);
    //Applying changes to the window
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.draw(shape2);
        window.display();
    }

    return 0;
}