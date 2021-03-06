#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

struct point
{
  int x, y;
};

int main()
{
  // random의 seed를 위함
  srand(time(0));

  RenderWindow app(VideoMode(400, 533), "Doodle Game!");
  app.setFramerateLimit(60);

  Texture t1, t2, t3;
  t1.loadFromFile("images/background.png");
  t2.loadFromFile("images/platform.png");
  t3.loadFromFile("images/doodle.png");

  Sprite sBackground(t1), sPlat(t2), sPers(t3);

  point plat[20];

  for (int i = 0; i < 10; i++)
  {
    // rand() % M을 하면 0~(M-1)까지의 수가 생성
    plat[i].x = rand() % 400;
    plat[i].y = rand() % 533;
  }

  int x = 100, y = 100, h = 200;
  float dx = 0, dy = 0;

  while (app.isOpen())
  {
    Event e;
    while (app.pollEvent(e))
    {
      if (e.type == Event::Closed)
        app.close();
      else if (e.key.code == Keyboard::Right)
        x += 3;
      else if (e.key.code == Keyboard::Left)
        x -= 3;
    }

    dy += 0.2;
    y += dy;
    if (y > 500)
      dy = -10;

    // 발판을 밟았을 경우 화면을 위나 아래로 움직인다.
    if (y < h)
      for (int i = 0; i < 10; i++)
      {
        y = h;
        plat[i].y = plat[i].y - dy;
        if (plat[i].y > 533)
        {
          plat[i].y = 0;
          plat[i].x = rand() % 400;
        }
      }

    // 발판을 밟을 수 있도록한다.
    for (int i = 0; i < 10; i++)
      if ((x + 50 > plat[i].x) && (x + 20 < plat[i].x + 68) &&
          (y + 70 > plat[i].y) && (y + 70 < plat[i].y + 14) && (dy > 0))
        dy = -10;

    sPers.setPosition(x, y);

    app.draw(sBackground);
    app.draw(sPers);
    for (int i = 0; i < 10; i++)
    {
      sPlat.setPosition(plat[i].x, plat[i].y);
      app.draw(sPlat);
    }
    app.display();
  }
  return 0;
}
