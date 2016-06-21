#pragma once

#include "../screen.h"

class SFMLScreen : public Screen {
public:
    SFMLScreen();
    ~SFMLScreen();

    virtual void draw(const FrameBuffer& buffer);
    virtual bool is_open();

private:
    sf::RenderWindow window;
};