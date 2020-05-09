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

class Entity
{
public:
  float x, y, dx, dy, R, angle;
  bool life;
  std::string name;
  Animation anim;

  Entity()
  {
    life = 1;
  }

  void settings(Animation &a, int X, int Y, float Angle = 0, int radius = 1)
  {
    anim = a;
    x = X;
    y = Y;
    angle = Angle;
    R = radius;
  }

  virtual void update(){};

  void draw(RenderWindow &app)
  {
    anim.sprite.setPosition(x, y);
    anim.sprite.setRotation(angle + 90);
    app.draw(anim.sprite);
  }
};

class asteroid : public Entity
{
public:
  asteroid()
  {
    dx = rand() % 8 - 4;
    dy = rand() % 8 - 4;
    name = "asteroid";
  }

  void update()
  {
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
  }
};

class bullet : public Entity
{
public:
  bullet()
  {
    name = "bullet";
  }

  void update()
  {
    dx = cos(angle * DEGTORAD) * 6;
    dy = sin(angle * DEGTORAD) * 6;
    x += dx;
    y += dy;

    if (x > W || x < 0 || y > H || y < 0)
      life = 0;
  }
};

int main()
{
  srand(time(0));

  RenderWindow app(VideoMode(W, H), "Asteroids!");
  app.setFramerateLimit(60);

  Texture t1, t2, t3, t4, t5;
  t1.loadFromFile("images/spaceship.png");
  t2.loadFromFile("images/background.jpg");
  t3.loadFromFile("images/explosions/type_A.png");
  t4.loadFromFile("images/rock.png");
  t5.loadFromFile("images/fire_blue.png");

  Animation sBullet(t5, 0, 0, 32, 64, 16, 0.8);

  Sprite sPlayer(t1), sBackground(t2), sExplosion(t3);
  sPlayer.setTextureRect(IntRect(40, 0, 40, 40));

  Animation sRock(t4, 0, 0, 64, 64, 16, 0.2);
  sRock.sprite.setPosition(400, 400);

  std::list<Entity *> entities;

  for (int i = 0; i < 15; i++)
  {
    asteroid *a = new asteroid();
    a->settings(sRock, rand() % W, rand() % H, rand() % 360, 25);
    entities.push_back(a);
  }

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

      if (e.type == Event::KeyPressed)
        if (e.key.code == Keyboard::Space)
        {
          bullet *b = new bullet();
          b->settings(sBullet, x, y, angle, 10);
          entities.push_back(b);
        }
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

    for (auto i = entities.begin(); i != entities.end();)
    {
      Entity *e = *i;

      e->update();
      e->anim.update();

      if (e->life == false)
      {
        i = entities.erase(i);
        delete e;
      }
      else
        i++;
    }

    sRock.update();
    //////draw//////
    app.clear();
    app.draw(sBackground);
    app.draw(sPlayer);
    for (auto i : entities)
      i->draw(app);
    app.display();
  }

  return 0;
}
