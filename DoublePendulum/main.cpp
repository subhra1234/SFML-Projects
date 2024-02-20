#include <SFML/Graphics.hpp>
#include <math.h>
#define W 1300
#define H 766
#define g 130
#define trailLength 2000


int main(){

    sf::RenderWindow window(sf::VideoMode(W, H), "Double Pendulum");
    sf::Vector2f origin(W/2, 20);
    float l1=300,l2=300;
    float m1=20, m2=13;
    float theta=M_PI/3, phi=0;

    // Bobs
    sf::CircleShape bob1(m1), bob2(m2);
    bob2.setFillColor(sf::Color::Yellow);
    sf::Vector2f pos1, pos2;
    sf::VertexArray line1(sf::LinesStrip, 2), line2(sf::LinesStrip, 2);
    sf::VertexArray trail(sf::Points, trailLength);

    float dt=0.01;
    float omega1=0, omega2=0;
    // main loop
    while (window.isOpen())
    {
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Calculation of next position
        float alpha1= (-g*(2*m1+m2)*sin(theta)-m2*g*sin(theta-2*phi)-2*sin(theta-phi)*m2*(pow(omega2,2)*l2+pow(omega1,2)*l1*cos(theta-phi)))/
                        (l1*(2*m1+m2-m2*cos(2*theta- 2*phi)));
        
        float alpha2= (2*sin(theta-phi)*(pow(omega1,2)*l1*(m1+m2)+ g*(m1+m2)*cos(theta)) + pow(omega2, 2)*l2*m2*cos(theta-phi))/
                        (l2*(2*m1+m2- m2*cos(2*theta- 2*phi)));

        //euler integration
        omega1+=alpha1*dt;
        omega2+=alpha2*dt;
        theta+=omega1*dt;
        phi+=omega2*dt;
        

        // position of bobs
        pos1.x=origin.x + l1*sin(theta);
        pos1.y=origin.y + l1*cos(theta);
        pos2.x=pos1.x + l2*sin(phi);
        pos2.y=pos1.y + l2*cos(phi);
        bob1.setPosition(pos1);
        bob1.setOrigin(m1,m1);
        bob2.setPosition(pos2);
        bob2.setOrigin(m2,m2);
        // strings
        line1[0].position=origin;
        line1[1].position=pos1;
        line2[0].position=pos1;
        line2[1].position=pos2;
        // trail
       
        sf::Vector2f prevPos=trail[trailLength-1].position, currentPos;
        for(int i=trailLength-1; i>0; i--){
            currentPos= trail[i].position;
            trail[i].position=prevPos;
            float a=255*pow(i,2)/pow(trailLength,2);
            trail[i].color=sf::Color(a,a,0,a);
            prevPos=currentPos;
        }
        trail[trailLength-1].position=pos2;
        
        // draw
        window.clear();
        // drawing bobs
        window.draw(bob1);
        window.draw(bob2);
        //drawing strings
        window.draw(line1);
        window.draw(line2);
        window.draw(trail);
        window.display();
    }
    
}