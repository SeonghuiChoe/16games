#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
using namespace sf;

const float SCALE = 30.f;
const float DEG = 57.29577f;

b2Vec2 Gravity(0.f, 9.8f);
b2World World(Gravity);

int main()
{
    RenderWindow window(VideoMode(800, 600), "Volleyball Game!");
    window.setFramerateLimit(60);

    Texture t1, t2;
    t1.loadFromFile("images/background.png");
    t2.loadFromFile("images/ball.png");
    t1.setSmooth(true);
    t2.setSmooth(true);

    Sprite sBackground(t1), sBall(t2);
    sBall.setOrigin(32, 32);

    /////////box2d///////////
    b2PolygonShape shape;
    shape.SetAsBox(30 / SCALE, 30 / SCALE);
    b2BodyDef bdef;
    bdef.type = b2_dynamicBody;
    /// ball /////////////
    bdef.position.Set(5, 1);
    b2CircleShape circle;
    circle.m_radius = 32 / SCALE;
    b2Body *b = World.CreateBody(&bdef);
    b2FixtureDef fdef;
    fdef.shape = &circle;
    fdef.restitution = 0.95;
    fdef.density = 0.2;
    b->CreateFixture(&fdef);
    b->SetUserData("ball");
    /////////////////////////

    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
        }

        //////////Draw///////////////
        window.draw(sBackground);

        for (b2Body *it = World.GetBodyList(); it != 0; it = it->GetNext())
        {
            b2Vec2 pos = it->GetPosition();
            float angle = it->GetAngle();

            if (it->GetUserData() == "ball")
            {
                sBall.setPosition(pos.x * SCALE, pos.y * SCALE);
                sBall.setRotation(angle * DEG);
                window.draw(sBall);
            }
        }

        window.display();
    }
    return 0;
}
