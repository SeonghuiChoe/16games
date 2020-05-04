#include <SFML/Graphics.hpp>
#include <time.h>
#include <list>
#include <math.h>
using namespace sf;

const int W = 1200;
const int H = 800;

int main()
{
  srand(time(0));

  RenderWindow app(VideoMode(W, H), "Asteroids!");
  app.setFramerateLimit(60);

  Texture t1, t2;
  t1.loadFromFile("images/spaceship.png");
  t2.loadFromFile("images/background.jpg");

  Sprite sPlayer(t1), sBackground(t2);
  sPlayer.setTextureRect(IntRect(40, 0, 40, 40));
  sPlayer.setOrigin(-1160 / 2, -760 / 2);

  /////main loop/////
  while (app.isOpen())
  {
    Event event;
    while (app.pollEvent(event))
    {
      if (event.type == Event::Closed)
        app.close();

      //////draw//////
      app.clear();
      app.draw(sBackground);
      app.draw(sPlayer);
      app.display();
    }
  }

  return 0;
}
