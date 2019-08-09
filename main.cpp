#include <getopt.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

bool verboseMode {false};

class Text {
public:
    Text (const sf::Font & font) : myText( sf::Text("Welcome to Davos", font, 60)) {}

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


class MagicNumbers {
public:
    sf::Vector2i textPosition {30, -5};
    sf::Vector2i direction {0,0};
    float speed = 5.0;
};



void printHelp() {
    std::cout <<
        "-v or --verbose: Verbose output\n"
        "-h or --help:    Show help\n";
    exit(1);
}

// from https://gist.github.com/ashwin/d88184923c7161d368a9
void processArgs(int argc, char** argv) {
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
            printHelp();
            break;
        }
    }
}


void handleKeyPressed(const sf::Keyboard::Key & keyCode, MagicNumbers & magicNumbers) {
    if (verboseMode) std::cout << "Handling a sf::Event::KeyPressed event. Key code; "<< keyCode << "\n";
    switch (keyCode) {
        case sf::Keyboard::Left:
            if (verboseMode) std::cout << "KeyPressed Event detected: Left: " << keyCode << std::endl;
            magicNumbers.direction.x = -1;
            break;
        case sf::Keyboard::Right:
            if (verboseMode) std::cout << "KeyPressed Event detected: Right: " << keyCode << std::endl;
            magicNumbers.direction.x = 1;
            break;
        case sf::Keyboard::Up:
            if (verboseMode) std::cout << "KeyPressed Event detected: Up: " << keyCode << std::endl;
            magicNumbers.direction.y = -1;
            break;
        case sf::Keyboard::Down:
            if (verboseMode) std::cout << "KeyPressed Event detected: Down: " << keyCode << std::endl;
            magicNumbers.direction.y = 1;
            break;
        default:
            break;
    }
}

void handleKeyReleased(const sf::Keyboard::Key & keyCode, MagicNumbers & magicNumbers) {
    if (verboseMode) std::cout << "Handling a sf::Event::KeyReleased event. Key code; "<< keyCode << "\n";
    switch (keyCode) {
        case sf::Keyboard::Left:
            if (verboseMode) std::cout << "KeyReleased Event detected: Left: " << keyCode << std::endl;
            magicNumbers.direction.x = 0;
            break;
        case sf::Keyboard::Right:
            if (verboseMode) std::cout << "KeyReleased Event detected: Right: " << keyCode << std::endl;
            magicNumbers.direction.x = 0;
            break;
        case sf::Keyboard::Up:
            if (verboseMode) std::cout << "KeyReleased Event detected: Up: " << keyCode << std::endl;
            magicNumbers.direction.y = 0;
            break;
        case sf::Keyboard::Down:
            if (verboseMode) std::cout << "KeyReleased Event detected: Down: " << keyCode << std::endl;
            magicNumbers.direction.y = 0;
            break;
        default:
            break;
    }       
}

int main(int argc, char* argv[]) {
    processArgs(argc, argv);

    MagicNumbers magicNumbers{};

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
    text.setPosition(sf::Vector2f{magicNumbers.textPosition});

    if (verboseMode) std::cout << "Loading the music file sound.ogg\n";
    sf::Music music;
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
                    handleKeyPressed(event.key.code, magicNumbers);
                    break;
                case sf::Event::KeyReleased:
                    handleKeyReleased(event.key.code, magicNumbers);
                    break;

                default:
                    break;
            }
        }

        window.clear();

        window.draw(sprite);

        sf::Vector2f newPosition = text.getPosition() + (sf::Vector2f{magicNumbers.direction} * magicNumbers.speed);
        text.setPosition(newPosition);
        text.draw(window);

        window.display();
    }
    return EXIT_SUCCESS;
}