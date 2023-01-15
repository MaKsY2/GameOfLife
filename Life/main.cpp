#include <SFML/Graphics.hpp>

#include <vector>
#include <cmath>

const unsigned int WIDTH = 1600;
const unsigned int HEIGHT = 900;

const size_t CIRCLES_COUNT = 7;

const double FORCE = 1.2;
const float GRAVITY = -9.8;
const float SPEED = 0.001;

sf::Vector2f rand_coordinates(unsigned int width, unsigned int height)
{
    sf::Vector2f rand(std::rand() % width, std::rand() % height);
    return rand;
}

sf::Vector2f way_vector(sf::CircleShape c1, sf::CircleShape c2)
{
    return {c1.getPosition().x - c2.getPosition().x, c1.getPosition().y - c2.getPosition().y};
}

float calc_dist(sf::CircleShape c1, sf::CircleShape c2)
{
    sf::Vector2f a = way_vector(c1, c2);
    return std::sqrt(pow(a.x, 2) + pow(a.y, 2));
}

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Life", sf::Style::Default, settings);
    std::vector<sf::CircleShape> circles(CIRCLES_COUNT);
    std::vector<sf::Vector2f> velocities(CIRCLES_COUNT);
    for (size_t i = 0; i < circles.size(); i++)
    {
        circles[i].setRadius(25);
        circles[i].setPosition(rand_coordinates(WIDTH, HEIGHT));
    }
    for (size_t i = 0; i < velocities.size(); i++)
    {
        velocities[i].x = 0;
        velocities[i].y = 0;
    }
    while (window.isOpen())
    {
        window.clear();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        for (size_t i = 0; i < circles.size(); i++)
        {
            sf::Vector2f force = {0, 0};

            for (size_t j = 0; j < circles.size(); j++)
            {
                sf::Vector2f dS = way_vector(circles[i], circles[j]);
                float dist = calc_dist(circles[i], circles[j]);
                if (dist > 0 && dist < 200)
                {
                    force.x += GRAVITY * dS.x / dist;
                    force.y += GRAVITY * dS.y / dist;
                }
            }
            velocities[i].x += force.x;
            velocities[i].y += force.y;
            circles[i].move(velocities[i] * SPEED);
            if (circles[i].getPosition().x <= 0 || circles[i].getPosition().x >= WIDTH)
                velocities[i].x *= -1;
            if (circles[i].getPosition().y <= 0 || circles[i].getPosition().y >= HEIGHT)
                velocities[i].y *= -1;
        }

        // for (size_t i = 0; i < circles.size(); i++)
        // {
        //     circles[i].move(velocities[i] * -SPEED);
        // }

        for (size_t i = 0; i < circles.size(); i++)
        {
            window.draw(circles[i]);
        }
        window.display();
    }
}