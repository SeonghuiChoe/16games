#include <SFML/Graphics.hpp>
#include <math.h>
using namespace sf;

const int num = 3; //checkpoints
int points[num][2] = {300, 1700,
                      600, 1600,
                      500, 1800};

struct Car
{
  float x, y, speed, angle;
  int n;

  Car()
  {
    speed = 2;
    angle = 0;
    n = 0;
  }

  void move()
  {
    x += sin(angle) * speed;
    y -= cos(angle) * speed;

    float tx = points[n][0];
    float ty = points[n][1];
    float beta = angle - atan2(tx - x, -ty + y);
    if (sin(beta) < 0)
      angle += 0.08;
    else
      angle -= 0.08;

    if ((x - tx) * (x - tx) + (y - ty) * (y - ty) < 25 * 25)
      n = (n + 1) % num;
  }
};

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

  const int N = 5;
  Car car[N];
  for (int i = 0; i < N; i++)
  {
    car[i].x = 300 + i * 50;
    car[i].y = 1700 + i * 80;
    car[i].speed = 7 + i;
  }

  float x = 300, y = 300;
  float speed = 0, angle = 0;
  float maxSpeed = 12.0;
  float acc = 0.2, dec = 0.3;
  float turnSpeed = 0.08;

  int offsetX = 0, offsetY = 0;

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

    // if (!Up && !Down)
    // {
    //   if (speed - dec > 0)
    //     speed -= dec;
    //   else if (speed + dec < 0)
    //     speed += dec;
    //   else
    //     speed = 0;
    // }

    if (Right && speed != 0)
      angle += turnSpeed * speed / maxSpeed;
    if (Left && speed != 0)
      angle -= turnSpeed * speed / maxSpeed;

    car[0].speed = speed;
    car[0].angle = angle;

    for (int i = 0; i < N; i++)
      car[i].move();
    float R = 22;

    //collision
    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++)
      {
        int dx = 0, dy = 0;
        while (dx * dx + dy * dy < 4 * R * R)
        {
          car[i].x += dx / 10.0;
          car[i].x += dy / 10.0;
          car[j].x -= dx / 10.0;
          car[j].y -= dy / 10.0;
          dx = car[i].x - car[j].x;
          dy = car[i].y - car[j].y;
          if (!dx && !dy)
            break;
        }
      }

    if (car[0].x > 320)
      offsetX = car[0].x - 320;
    if (car[0].y > 240)
      offsetY = car[0].y - 240;

    app.clear(Color::White);

    sBackground.setPosition(-offsetX, -offsetY);
    app.draw(sBackground);

    Color colors[10] = {Color::Red, Color::Green, Color::Magenta, Color::Blue, Color::White};

    for (int i = 0; i < N; i++)
    {
      sCar.setPosition(car[i].x - offsetX, car[i].y - offsetY);
      sCar.setRotation(car[i].angle * 180 / 3.141593);
      sCar.setColor(colors[i]);
      app.draw(sCar);
    }

    app.display();
  }

  return 0;
}
