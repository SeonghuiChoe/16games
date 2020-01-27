#include <SFML/Graphics.hpp>
using namespace sf;

struct point
{
  int x, y;
};

int main()
{
  RenderWindow app(VideoMode(400, 533), "Doodle Game!");

  Texture t1, t2, t3;
  t1.loadFromFile("images/background.png");
  t2.loadFromFile("images/platform.png");
  t3.loadFromFile("images/doodle.png");

  Sprite sBackground(t1), sPlat(t2), sPers(t3);

  while (app.isOpen())
  {
    Event e;
    while (app.pollEvent(e))
    {
      if (e.type == Event::Closed)
        app.close();
    }

    app.draw(sBackground);
    app.draw(sPers);
    app.display();
  }
  return 0;
}
