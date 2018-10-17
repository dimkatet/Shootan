#ifndef BUTTON_H
#define BUTTON_H


#include "GameObject.h"

using namespace std;

class Button: public GameObject
{
public:
    Button(string _name, string _path, float _xPos, float _yPos, int _id);
    virtual ~Button();
    void setID(int _id);
    int getID();
private:
    sf::Texture texture;
    sf::Text text;
    sf::Font font;
    int id;
    virtual void update();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

extern sf::RenderWindow window;
extern float frameTime;

#endif // BUTTON_H
