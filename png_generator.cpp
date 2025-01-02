//This code can be used to generate 256x256 pixel PNGs with mathematical expressions.
//For example to make textures. Saves to current directory.

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

constexpr int screenWidth=600;
constexpr int screenHeight=600;

int main() {
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "PNG Generator");
    sf::Event event;
    sf::Image image;
    image.create(256,256);
    for(int z = 0; z < 256; z++) {
        for(int y = 0; y < 256; y++){
            for(int x = 0; x < 256; x++)
            {
                sf::Color color;

                // unsigned char value=static_cast<unsigned char>(x^y^z);
                // unsigned char value=x*y;
                unsigned char value=static_cast<unsigned char>(z%y+30);
                // unsigned char value=128+(256.f/2.f)*(sin(10*y*M_PI/255)+sin(10*x*M_PI/255));
                // unsigned char value=128+128*sin(sqrt(((x-128)*(x-128)+(y-128)*(y-128))*M_PI/255));
                // unsigned char value=256*((x^y)%5)/5.f;
                // unsigned char value=(x*x+y*y)/512.f;

                color={value,0,0};
                image.setPixel(x,y,color);
            }
        }
    }
    sf::Texture texture;
    texture.create(256,256);
    texture.loadFromImage(image);
    sf::RectangleShape rect;
    rect.setSize({screenWidth,screenHeight});
    rect.setPosition(0,0);
    rect.setFillColor(sf::Color::White);
    rect.setTexture(&texture);
    rect.setTextureRect(sf::IntRect({0,0},{256,256}));
    image.saveToFile("image.png");

    while (window.isOpen())
    {
        window.setFramerateLimit(10);

        //controls to close
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type==sf::Event::KeyPressed&&event.key.code==sf::Keyboard::Escape) window.close();
        }

        window.clear(sf::Color::Black);
        window.draw(rect);
        window.display();
    }
    return 0;
}