#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
using namespace sf;

int width = 1024;
int height = 768;
int roadW = 2000;
int segL = 200;    //segment length
float camD = 0.84; //camera depth

void drawQuad(RenderWindow &w, Color c, int x1, int y1, int w1, int x2, int y2, int w2)
{
    ConvexShape shape(4);
    shape.setFillColor(c);
    shape.setPoint(0, Vector2f(x1 - w1, y1));
    shape.setPoint(1, Vector2f(x2 - w2, y2));
    shape.setPoint(2, Vector2f(x2 + w2, y2));
    shape.setPoint(3, Vector2f(x1 + w1, y1));
    w.draw(shape);
}

struct Line
{
    float x, y, z; //3d center of line
    float X, Y, W; //screen coord
    float curve, spriteX, clip, scale;
    Sprite sprite;

    Line()
    {
        spriteX = curve = x = y = z = 0;
    }

    void project(int camX, int camY, int camZ)
    {
        scale = camD / (z - camZ);
        X = (1 + scale * (x - camX)) * width / 2;
        Y = (1 - scale * (y - camY)) * height / 2;
        W = scale * roadW * width / 2;
    }
};

int main()
{
    RenderWindow app(VideoMode(width, height), "Outrun Racing!");
    app.setFramerateLimit(60);

    std::vector<Line> lines;

    for (int i = 0; i < 1600; i++)
    {
        Line line;
        line.z = i * segL;
        lines.push_back(line);
    }

    int N = lines.size();
    float playerX = 0;
    int pos = 0;
    int H = 1500;

    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();
            else if (e.key.code == Keyboard::Up)
                pos = +200;
            else if (e.key.code == Keyboard::Down)
                pos = -200;
            else if (e.key.code == Keyboard::Right)
                playerX += 0.1;
            else if (e.key.code == Keyboard::Left)
                playerX -= 0.1;
        }

        int speed = 0;

        pos += speed;
        while (pos >= N * segL)
            pos -= N * segL;
        while (pos < 0)
            pos += N * segL;

        int startPos = pos / segL;
        int camH = lines[startPos].y + H;

        int maxy = height;
        float x = 0, dx = 0;

        ///////draw road////////
        for (int n = startPos; n < startPos + 300; n++)
        {
            Line &l = lines[n % N];
            l.project(playerX * roadW - x, camH, startPos * segL - (n >= N ? N * segL : 0));
            x += dx;
            dx += l.curve;

            l.clip = maxy;
            if (l.Y >= maxy)
                continue;
            maxy = l.Y;

            Color grass = (n / 3) % 2 ? Color(16, 200, 16) : Color(0, 154, 0);
            Color rumble = (n / 3) % 2 ? Color(255, 255, 255) : Color(0, 0, 0);
            Color road = (n / 3) % 2 ? Color(107, 107, 107) : Color(105, 105, 105);

            Line p = lines[(n - 1) % N]; //previous line

            drawQuad(app, grass, 0, p.Y, width, 0, l.Y, width);
            drawQuad(app, rumble, p.X, p.Y, p.W * 1.2, l.X, l.Y, l.W * 1.2);
            drawQuad(app, road, p.X, p.Y, p.W, l.X, l.Y, l.W);
        }

        app.display();
    }

    return 0;
}
