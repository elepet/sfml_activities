//This is a simple 2D acceleration/drag simulator.
//Control the circle with arrow keys.

 #include <SFML/Window.hpp>
 #include <SFML/Graphics.hpp>

 #include <cmath>

 void setRad(sf::Vector2f &v,float &rad,float &hyp);

 int main()
 {
     sf::RenderWindow window(sf::VideoMode(800, 600),"Acceleration");
     window.setFramerateLimit(60);
     sf::Event event;

     sf::Clock clock; //restarts every frame

     //movement settings
     //inputs and .move() modify cartesian coords
     //drag modifies polar coords
     sf::Vector2f v(0,0); //velocity cartesian coords
     float hyp {0}; //hypotenuse of vel for polar coords
     float rad {0}; //angle cw from +ve x axis in radians of vel for polar coords
     constexpr float accUp {30}; //acceleration (how much is added to vel per frame)
     constexpr float accDown {15};
     constexpr float accLeft {15};
     constexpr float accRight {15};
     float drg {10}; //deceleration
     float near0 {5}; //how close to 0 controls stop (+-)
     float g {15}; //gravity

     //circle instantiation
     sf::CircleShape circle(50);
     circle.setFillColor(sf::Color::Black);
     circle.setPosition(350, 250);

     while (window.isOpen()) //each iteration is a frame
     {
         window.setFramerateLimit(60);
         sf::Time dt=clock.restart(); //delta time

         //controls to close
         while (window.pollEvent(event))
         {
             if (event.type == sf::Event::Closed) window.close();
             if (event.type==sf::Event::KeyPressed&&event.key.code==sf::Keyboard::Escape) window.close();
         }

         //effect of drag
         hyp=sqrt(v.y*v.y+v.x*v.x);
         if (v.x>0) {
             rad=atan(v.y/v.x);
         } else if (v.x<0) {
             rad=atan(v.y/v.x)+M_PI;
         } else if (abs(0-v.x)<0.1&&v.y>0) {
             rad=M_PI/2;
         } else if (abs(0-v.x)<0.1&&v.y<0) {
             rad=-M_PI/2;
         }
         if (abs(0-hyp)<near0) {
             hyp=0;
             v.y=0;
             v.x=0;
         } else {
             hyp-=drg;
             v.y=sin(rad)*hyp;
             v.x=cos(rad)*hyp;
             circle.move(v.x*dt.asSeconds(),v.y*dt.asSeconds());
         }

         //movement
         //origin is top-left. imagine window as 1st cartesian quadrant flipped on x-axis
         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {//while holding, accelerate
             v.y-=accUp;
             circle.move(0,v.y*dt.asSeconds());
         } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
             v.y+=accDown;
             circle.move(0,v.y*dt.asSeconds());
         }
         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
             v.x-=accLeft;
             circle.move(v.x*dt.asSeconds(),0);
         } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
             v.x+=accRight;
             circle.move(v.x*dt.asSeconds(),0);
         }

         //effect of gravity (comment/uncomment to toggle)
         v.y+=g;

         //repositioning when out of frame
         if (circle.getPosition().y>600) {
             circle.setPosition(circle.getPosition().x,0);
         }
         if (circle.getPosition().y<0) {
             circle.setPosition(circle.getPosition().x,600);
         }
         if (circle.getPosition().x>800) {
             circle.setPosition(0,circle.getPosition().y);
         }
         if (circle.getPosition().x<0) {
             circle.setPosition(800,circle.getPosition().y);
         }
         window.clear(sf::Color::Blue);
         window.draw(circle);
         window.display();
     }
     return 0;
 }
 void setRad(sf::Vector2f &v,float &rad,float &hyp)
 {
     //formatting rad like this so that it is unique in each quadrant
     if (v.x>0&&v.y==0) {
         rad=0;
     } else if (v.x>0&&v.y>0) { //1st quadrant (0 to Pi/2)
         rad=asin(v.y/hyp);
     } else if (v.x==0&&v.y>0) { //Pi/2
         rad=M_PI/2;
     } else if (v.x<0&&v.y>0) { //2nd quadrant (Pi/2 to Pi)
         rad=asin(v.y/hyp)+M_PI/2;
     } else if (v.x<0&&v.y==0) { //Pi
         rad=M_PI;
     } else if (v.x<0&&v.y<0) { //3rd quadrant (Pi to 3*Pi/2)
         rad=asin(abs(v.y)/hyp)+M_PI;
     } else if (v.x==0&&v.y<0) { //3Pi/2
         rad=3*M_PI/2;
     } else if (v.x>0&&v.y<0) { //4th quadrant (3Pi/2 to 0)
         rad=asin(abs(v.y)/hyp)+3*M_PI/2;
     }
 }
