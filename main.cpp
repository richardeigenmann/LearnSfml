#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>

class Text {
public:
    Text (const sf::Font & font) : myText( sf::Text("Welcome to Davos", font, 60)) {
    }

    void setPosition (const sf::Vector2f & newPos) {
        myText.setPosition(newPos);
    }

    auto getPosition() {
        return myText.getPosition();
    }

    void draw (sf::RenderWindow & window ) {
        window.draw(myText);
    }
    auto getSfmlObject() {
        return myText;
    }
private:
    sf::Text myText;
};

sf::Vector2i textPosition {30, -5};
auto key_states = std::map<sf::Keyboard::Key, bool>{};
sf::Vector2i direction {0,0};
float speed = 5.0;

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(600, 395), "SFML Welcome to Davos window");
    window.setFramerateLimit(60);
    
    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("Davos.jpg"))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);

    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile("ChangaOne-Regular.ttf"))
        return EXIT_FAILURE;

    Text text{font};
    text.setPosition(sf::Vector2f{textPosition});

    // Load a music to play
    sf::Music music;
    if (!music.openFromFile("sound.ogg"))
        return EXIT_FAILURE;

    // Play the music
    music.play();
    music.setLoop(true);

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // check the type of the event...
            switch (event.type) {
                // window closed
                case sf::Event::Closed:
                    window.close();
                    break;

                // key pressed
                case sf::Event::KeyPressed:
                    switch (event.key.code) {
                        case sf::Keyboard::Escape:
                            std::cout << "KeyPressed Event detected: Escape: " << event.key.code << std::endl;
                            break;
                        case sf::Keyboard::Left:
                            std::cout << "KeyPressed Event detected: Left: " << event.key.code << std::endl;
                            direction.x = -1;
                            break;
                        case sf::Keyboard::Right:
                            std::cout << "KeyPressed Event detected: Right: " << event.key.code << std::endl;
                            direction.x = 1;
                            break;
                      case sf::Keyboard::Up:
                            std::cout << "KeyPressed Event detected: Up: " << event.key.code << std::endl;
                            direction.y = -1;
                            break;
                        case sf::Keyboard::Down:
                            std::cout << "KeyPressed Event detected: Down: " << event.key.code << std::endl;
                            direction.y = 1;
                            break;
                        default:
                            break;
                    }
                    break;
                case sf::Event::KeyReleased:
                    switch (event.key.code) {
                        case sf::Keyboard::Escape:
                            std::cout << "KeyReleased Event detected: Escape: " << event.key.code << std::endl;
                            break;
                        case sf::Keyboard::Left:
                            std::cout << "KeyReleased Event detected: Left: " << event.key.code << std::endl;
                            direction.x = 0;
                            break;
                        case sf::Keyboard::Right:
                            std::cout << "KeyReleased Event detected: Right: " << event.key.code << std::endl;
                            direction.x = 0;
                            break;
                      case sf::Keyboard::Up:
                            std::cout << "KeyReleased Event detected: Up: " << event.key.code << std::endl;
                            direction.y = 0;
                            break;
                        case sf::Keyboard::Down:
                            std::cout << "KeyReleased Event detected: Down: " << event.key.code << std::endl;
                            direction.y = 0;
                            break;
                        default:
                            break;
                    }       
                    break;

                // we don't process other types of events
                default:
                    break;
            }
        }

        // Clear screen
        window.clear();

        // Draw the sprite
        window.draw(sprite);

        // Draw the string
        sf::Vector2f newPosition = text.getPosition() + (sf::Vector2f{direction} * speed);
        text.setPosition(newPosition);
        text.draw(window);
        //window.draw(text.getSfmlObject());

        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}
