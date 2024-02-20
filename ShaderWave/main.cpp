#include<SFML/Graphics.hpp>

int W=800, H=600;

int main(){
    float t=0;
    float offset=0;
    //window
    sf::RenderWindow window(sf::VideoMode(W,H), "Wave Sim");

    //screen
    sf:: RectangleShape screen(sf::Vector2f(W,H));
    screen.setFillColor(sf::Color::Cyan);

    sf::Shader waveShader;
    waveShader.loadFromFile("wave.frag", sf::Shader::Fragment);
    //setting parameters
    waveShader.setUniform("u_resolution", sf::Vector2f(W,H));
    waveShader.setUniform("color",sf::Glsl::Vec4(0.1,0.9,0.3,1.0));

    sf::CircleShape point1(5);
    sf::CircleShape point2(5);
    
    //mainloop
    while(window.isOpen()){
        point1.setPosition(sf::Vector2f(W/2 -2.5+offset, H/2-2.5));
        point2.setPosition(sf::Vector2f(W/2 -2.5-offset, H/2-2.5));

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        waveShader.setUniform("u_time", t);
        waveShader.setUniform("pos1", point1.getPosition());
        waveShader.setUniform("pos2", point2.getPosition());
   //draw
        window.draw(screen, &waveShader);
        window.draw(point1);
        window.draw(point2);

        window.display();
        t+=0.01;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            offset+=0.1;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            offset-=0.1;
        }
    }

}