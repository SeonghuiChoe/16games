#include <SFML/Graphics.hpp>
#include <time.h>
#include <list>
#include <math.h>
using namespace sf;

const int W = 1200;
const int H = 800;

float DEGTORAD = 0.017453f;

class Animation
{
public:
  float Frame, speed;
  Sprite sprite;
  std::vector<IntRect> frames;

  Animation() {}

  Animation(Texture &t, int x, int y, int w, int h, int count, float Speed)
  {
    Frame = 0;
    speed = Speed;

    for (int i = 0; i < count; i++)
      frames.push_back(IntRect(x + i * w, y, w, h));

    sprite.setTexture(t);
    sprite.setOrigin(w / 2, h / 2);
    sprite.setTextureRect(frames[0]);
  }

  void update()
  {
    Frame += speed;
    int n = frames.size();
    if (Frame >= n)
      Frame -= n;
    if (n > 0)
      sprite.setTextureRect(frames[int(Frame)]);
  }
};

int main()
{
  srand(time(0));

  RenderWindow app(VideoMode(W, H), "Asteroids!");
  app.setFramerateLimit(60);

  Texture t1, t2, t3, t4;
  t1.loadFromFile("images/spaceship.png");
  t2.loadFromFile("images/background.jpg");
  t3.loadFromFile("images/explosions/type_A.png");
  t4.loadFromFile("images/rock.png");

  Sprite sPlayer(t1), sBackground(t2), sExplosion(t3);
  sPlayer.setTextureRect(IntRect(40, 0, 40, 40));

  Animation sRock(t4, 0, 0, 64, 64, 16, 0.2);
  sRock.sprite.setPosition(400, 400);

  sExplosion.setPosition(300, 300);
  float Frame = 0;
  float animSpeed = 0.4;
  int frameCount = 20;

  float x = 300, y = 300;
  float dx = 0, dy = 0, angle = 0;
  bool thrust;

  /////main loop/////
  while (app.isOpen())
  {
    Event e;
    while (app.pollEvent(e))
    {
      if (e.type == Event::Closed)
        app.close();
    }

    Frame += animSpeed;
    if (Frame > frameCount)
      Frame -= frameCount;
    sExplosion.setTextureRect(IntRect(int(Frame) * 50, 0, 50, 50));

    if (e.key.code == Keyboard::Right)
      angle += 3;
    if (e.key.code == Keyboard::Left)
      angle -= 3;
    if (e.key.code == Keyboard::Up)
      thrust = true;
    else
      thrust = false;

    //////spaceship movement//////
    if (thrust)
    {
      dx += cos(angle * DEGTORAD) * 0.2;
      dy += sin(angle * DEGTORAD) * 0.2;
    }
    else
    {
      dx *= 0.99;
      dy *= 0.99;
    }

    int maxSpeed = 15;
    float speed = sqrt(dx * dx + dy * dy);
    if (speed > maxSpeed)
    {
      dx *= maxSpeed / speed;
      dy *= maxSpeed / speed;
    }

    x += dx;
    y += dy;

    if (x > W)
      x = 0;
    if (x < 0)
      x = W;
    if (y > H)
      y = 0;
    if (y < 0)
      y = H;

    sPlayer.setPosition(x, y);
    sPlayer.setRotation(angle + 90);

    sRock.update();
    //////draw//////
    app.clear();
    app.draw(sBackground);
    app.draw(sPlayer);
    app.draw(sExplosion);
    app.draw(sRock.sprite);
    app.display();
  }

  return 0;
}
