#include <getopt.h>
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
bool verboseMode {false};

void PrintHelp() {
    std::cout <<
        "-v or --verbose: Verbose output\n"
        "-h or --help:    Show help\n";
    exit(1);
}

// from https://gist.github.com/ashwin/d88184923c7161d368a9
void ProcessArgs(int argc, char** argv) {
    const char* const short_opts = "hv";
    const option long_opts[] = {
            {"help", no_argument, nullptr, 'h'},
            {"verbose", no_argument, nullptr, 'v'},
            {nullptr, no_argument, nullptr, 0}
    };

   while (true) {
        const auto opt = getopt_long(argc, argv, short_opts, long_opts, nullptr);

        if (-1 == opt)
            break;

        switch (opt) {
        case 'v':
            verboseMode = true;
            std::cout << "Verbose mode turned on." << std::endl;
            break;

        case 'h': // -h or --help
        case '?': // Unrecognized option
        default:
            PrintHelp();
            break;
        }
    }
}



int main(int argc, char* argv[]) {

    ProcessArgs(argc, argv);

    if (verboseMode) std::cout << "Creating the SFML window\n";
    auto VideoMode = sf::VideoMode(600, 395);
    if (verboseMode) std::cout << "VideoMode Created\n";
    sf::RenderWindow window(VideoMode, "SFML Welcome to Davos window");
    if (verboseMode) std::cout << "Window created\n";
    window.setFramerateLimit(60);
    
    sf::Texture texture;
    if (verboseMode) std::cout << "Loading the file Davos.jpg into the texture\n";
    if (!texture.loadFromFile("Davos.jpg"))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);

    sf::Font font;
    if (verboseMode) std::cout << "Loading the font file ChangaOne-Regular.ttf\n";
    if (!font.loadFromFile("ChangaOne-Regular.ttf"))
        return EXIT_FAILURE;

    Text text{font};
    text.setPosition(sf::Vector2f{textPosition});

    sf::Music music;
    if (verboseMode) std::cout << "Loading the music file sound.ogg\n";
    if (!music.openFromFile("sound.ogg"))
        return EXIT_FAILURE;

    if (verboseMode) std::cout << "Playing the music and setting loop to true\n";
    music.play();
    music.setLoop(true);

    if (verboseMode) std::cout << "Starting the game loop\n";
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    if (verboseMode) std::cout << "Handling the sf::Event::Closed event\n";
                    window.close();
                    break;

                case sf::Event::KeyPressed:
                    if (verboseMode) std::cout << "Handling a sf::Event::KeyPressed event. Key code; "<< event.key.code << "\n";
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
