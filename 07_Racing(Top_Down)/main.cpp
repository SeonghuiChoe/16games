#include <SFML/Graphics.hpp>
#include <math.h>
using namespace sf;

int main()
{
  RenderWindow app(VideoMode(640, 480), "Car Racing Game!");
  app.setFramerateLimit(60);

  Texture t1, t2, t3;
  t1.loadFromFile("images/background.png");
  t2.loadFromFile("images/car.png");

  Sprite sBackground(t1), sCar(t2);
  sCar.setPosition(320, 340);
  sCar.setOrigin(22, 22);

  float x = 300, y = 300;
  float speed = 0, angle = 0;
  float maxSpeed = 12.0;
  float acc = 0.2, dec = 0.3;
  float turnSpeed = 0.08;

  while (app.isOpen())
  {

    Event e;
    while (app.pollEvent(e))
    {
      if (e.type == Event::Closed)
        app.close();
    }

    bool Up = 0, Right = 0, Down = 0, Left = 0;
    if (e.key.code == Keyboard::Up)
      Up = 1;
    if (e.key.code == Keyboard::Right)
      Right = 1;
    if (e.key.code == Keyboard::Down)
      Down = 1;
    if (e.key.code == Keyboard::Left)
      Left = 1;

    //car movement
    if (Up && speed < maxSpeed)
    {
      if (speed < 0)
        speed += dec;
      else
        speed += acc;
    }

    if (Down && speed > -maxSpeed)
    {
      if (speed > 0)
        speed -= dec;
      else
        speed -= acc;
    }

    if (!Up && !Down)
    {
      if (speed - dec > 0)
        speed -= dec;
      else if (speed + dec < 0)
        speed += dec;
      else
        speed = 0;
    }

    if (Right && speed != 0)
      angle += turnSpeed * speed / maxSpeed;
    if (Left && speed != 0)
      angle -= turnSpeed * speed / maxSpeed;

    x += sin(angle) * speed;
    y -= cos(angle) * speed;

    app.clear(Color::White);
    app.draw(sBackground);

    sCar.setPosition(x, y);
    sCar.setRotation(angle * 180 / 3.141592);
    sCar.setColor(Color::Red);
    app.draw(sCar);

    app.display();
  }

  return 0;
}
