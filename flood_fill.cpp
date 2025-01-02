//This is an implementation of the flood fill algorithm.

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <queue>

int basicFill(int map[16][16],int x,int y);
int queueFill(int map[16][16],int x,int y);

int main()
{
    //window
    sf::RenderWindow window(sf::VideoMode(600, 600), "Flood Fill", sf::Style::Titlebar | sf::Style::Close);
    //queue
    std::queue<std::pair<int,int>> queue;
    int x{0},y{0};
    //making grid
    sf::VertexArray grid(sf::Lines, 80);
    float gridX = 0;
    float gridY = 0;
    //vertical lines
    for (int i = 0; i < 38; i++) {
        grid[i].position = sf::Vector2f(gridX, 0);
        grid[i].color = sf::Color::Black;
        i++;
        grid[i].position = sf::Vector2f(gridX, 600);
        grid[i].color = sf::Color::Black;
        gridX += 37.5;
    }
    //horizontal lines
    for (int i = 40; i < 80; i++) {
        grid[i].position = sf::Vector2f(0, gridY);
        grid[i].color = sf::Color::Black;
        i++;
        grid[i].position = sf::Vector2f(600, gridY);
        grid[i].color = sf::Color::Black;
        gridY += 37.5;
    }
    //tiles
    sf::RectangleShape tile;
    tile.setSize(sf::Vector2f(37.5, 37.5));
    //map
    int map[16][16] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    };
    unsigned int r{255},g{0},b{0};
    bool whileRunning{false};
    sf::Event event;

    while (window.isOpen())
    {
        window.setFramerateLimit(200);
        //controls to close
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type==sf::Event::KeyPressed&&event.key.code==sf::Keyboard::Escape) window.close();
        }
        //lmouse to place black square, rmouse to remove black square, shift+rmouse to place flood
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            map[static_cast<int>(16*sf::Mouse::getPosition(window).x/600)][static_cast<int>(16*sf::Mouse::getPosition(window).y/600)]=0;
        }else if(sf::Mouse::isButtonPressed(sf::Mouse::Right)&&sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)){
            if(whileRunning==false) {
                x=static_cast<int>(16*sf::Mouse::getPosition(window).x/600);
                y=static_cast<int>(16*sf::Mouse::getPosition(window).y/600);
                whileRunning=true;
            }
        }else if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
            map[static_cast<int>(16*sf::Mouse::getPosition(window).x/600)][static_cast<int>(16*sf::Mouse::getPosition(window).y/600)]=1;
        }
        if(whileRunning==true){
            map[x][y]=2;
            queue.push({x,y});
            if(!queue.empty()){
                if(!(map[x+1][y]==0||map[x+1][y]==2||x+1<0||x+1>15||y<0||y>15)){
                    map[x+1][y]=2;
                    queue.push({x+1,y});
                }
                if(!(map[x-1][y]==0||map[x-1][y]==2||x-1<0||x-1>15||y<0||y>15)){
                    map[x-1][y]=2;
                    queue.push({x-1,y});
                }
                if(!(map[x][y+1]==0||map[x][y+1]==2||x<0||x>15||y+1<0||y+1>15)){
                    map[x][y+1]=2;
                    queue.push({x,y+1});
                }
                if(!(map[x][y-1]==0||map[x][y-1]==2||x<0||x>15||y-1<0||y-1>15)){
                    map[x][y-1]=2;
                    queue.push({x,y-1});
                }
                x=queue.front().first;
                y=queue.front().second;
                queue.pop();
        } else whileRunning=false;
    }
        sf::Color color(r, g, b);
        window.clear(sf::Color::White);
        for(int i=0;i<16;i++){
            for(int j=0;j<16;j++){
                tile.setPosition(static_cast<float>(i)*37.5,static_cast<float>(j)*37.5);
                switch (map[i][j]){
                    case 0:tile.setFillColor(sf::Color::Black);
                        break;
                    case 1:tile.setFillColor(sf::Color::White);
                        break;
                    case 2:tile.setFillColor(sf::Color(color));
                        break;
                }
                window.draw(tile);
            }
        }
        window.draw(grid);
        window.display();
    }
    return 0;
}