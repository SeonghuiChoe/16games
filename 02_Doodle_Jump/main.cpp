#include <SFML/Graphics.hpp>
using namespace sf;

int main()
{
  RenderWindow app(VideoMode(400, 533), "Doodle Game!");
  app.setFramerateLimit(60);

  Texture t1;
  t1.loadFromFile("images/background.png");

  Sprite sBackground(t1);


  while (app.isOpen())
  {
    Event e;
    while (app.pollEvent(e))
    {
      if (e.type == Event::Closed)
        app.close();
    }

   app.draw(sBackground);
   app.display();
  }
  return 0;
}
