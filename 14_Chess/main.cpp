#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int main()
{
  RenderWindow window(VideoMode(504, 504), "The Chess! (press SPACE)");

  Texture t1;
  t1.loadFromFile("images/figures.png");

  Sprite s(t1);

  bool isMove = false;
  float dx = 0, dy = 0;

  while (window.isOpen())
  {
    Vector2i pos = Mouse::getPosition(window);

    Event e;
    while (window.pollEvent(e))
    {
      if (e.type == Event::Closed)
        window.close();

      /////drag and drop///////
      if (e.type == Event::MouseButtonPressed)
        if (e.mouseButton.button == Mouse::Left)
          if (s.getGlobalBounds().contains(pos.x, pos.y))
          {
            isMove = true;
            dx = pos.x - s.getPosition().x;
            dy = pos.y - s.getPosition().y;
          }

      if (e.type == Event::MouseButtonReleased)
        if (e.mouseButton.button == Mouse::Left)
        {
          isMove = false;
        }
    }
    if (isMove)
      s.setPosition(pos.x - dx, pos.y - dy);

    window.clear();
    window.draw(s);
    window.display();
  }

  return 0;
}
