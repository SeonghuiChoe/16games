#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
// #include "./Connector.hpp"
using namespace sf;

int size = 56;
Vector2f offset(28, 28);

Sprite f[32]; //figures
std::string position = "";

int board[8][8] =
    {-1, -2, -3, -4, -5, -3, -2, -1,
     -6, -6, -6, -6, -6, -6, -6, -6,
     0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0,
     6, 6, 6, 6, 6, 6, 6, 6,
     1, 2, 3, 4, 5, 3, 2, 1};

std::string toChessNote(Vector2f p)
{
  std::string s = "";
  s += char(p.x / size + 97);
  s += char(7 - p.y / size + 49);
  return s;
}

Vector2f toCoord(char a, char b)
{
  int x = int(a) - 97;
  int y = 7 - int(b) + 49;
  return Vector2f(x * size, y * size);
}

void move(std::string str)
{
  Vector2f oldPos = toCoord(str[0], str[1]);
  Vector2f newPos = toCoord(str[2], str[3]);

  for (int i = 0; i < 32; i++)
    if (f[i].getPosition() == newPos)
      f[i].setPosition(-100, -100);

  for (int i = 0; i < 32; i++)
    if (f[i].getPosition() == oldPos)
      f[i].setPosition(newPos);
}

void loadPosition()
{
  int k = 0;
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++)
    {
      int n = board[i][j];
      if (!n)
        continue;
      int x = abs(n) - 1;
      int y = n > 0 ? 1 : 0;
      f[k].setTextureRect(IntRect(size * x, size * y, size, size));
      f[k].setPosition(size * j, size * i);
      k++;
    }

  for (int i = 0; i < position.length(); i += 5)
    move(position.substr(i, 4));
}

int main()
{
  RenderWindow window(VideoMode(504, 504), "The Chess! (press SPACE)");

  Texture t1, t2;
  t1.loadFromFile("images/figures.png");
  t2.loadFromFile("images/board.png");

  for (int i = 0; i < 32; i++)
    f[i].setTexture(t1);

  Sprite s(t1);
  Sprite sBoard(t2);

  loadPosition();

  bool isMove = false;
  float dx = 0, dy = 0;
  Vector2f oldPos, newPos;
  std::string str;
  int n = 0;
  bool isAuto = false;

  while (window.isOpen())
  {
    Vector2i pos = Mouse::getPosition(window) - Vector2i(offset);

    Event e;
    while (window.pollEvent(e))
    {
      if (e.type == Event::Closed)
        window.close();

      ////move back//////
      if (e.type == Event::KeyPressed)
        if (e.key.code == Keyboard::BackSpace)
        {
          if (position.length() > 6)
            position.erase(position.length() - 6, 5);
          loadPosition();
        }

      /////drag and drop///////
      if (e.type == Event::MouseButtonPressed)
        if (e.mouseButton.button == Mouse::Left)
          for (int i = 0; i < 32; i++)
            if (f[i].getGlobalBounds().contains(pos.x, pos.y))
            {
              isMove = true;
              n = i;
              dx = pos.x - f[i].getPosition().x;
              dy = pos.y - f[i].getPosition().y;
              oldPos = f[i].getPosition();
            }

      if (e.type == Event::MouseButtonReleased)
        if (e.mouseButton.button == Mouse::Left)
        {
          isMove = false;
          Vector2f p = f[n].getPosition() + Vector2f(size / 2, size / 2);
          newPos = Vector2f(size * int(p.x / size), size *int(p.y / size));
          str = toChessNote(oldPos) + toChessNote(newPos);
          move(str);
          position += str + " ";
          std::cout << str << std::endl;
          f[n].setPosition(newPos);
        }

      //comp move
      if (e.type == Event::KeyPressed)
        if (e.key.code == Keyboard::Space)
        {
          str = "d7d5"; // getNextMove(position);

          oldPos = toCoord(str[0], str[1]);
          newPos = toCoord(str[2], str[3]);

          for (int i = 0; i < 32; i++)
            if (f[i].getPosition() == oldPos)
              n = i;

          // 뒤로가게 할 수 있도록 정보 저장
          position += str + " ";
          isAuto = true;
        }
    }

    if (isAuto)
    {
      Vector2f p = newPos - oldPos;
      float x = 0, y = 0;
      if (p.x)
        x = 0.1;
      if (p.y)
        y = 0.1;
      f[n].move(x, y);
      if (f[n].getPosition().x >= newPos.x && f[n].getPosition().y >= newPos.y)
        isAuto = false;
    }

    if (isMove)
      f[n].setPosition(pos.x - dx, pos.y - dy);

    window.clear();
    window.draw(sBoard);
    for (int i = 0; i < 32; i++)
      f[i].move(offset);
    for (int i = 0; i < 32; i++)
      window.draw(f[i]);
    for (int i = 0; i < 32; i++)
      f[i].move(-offset);
    window.display();
  }

  return 0;
}
