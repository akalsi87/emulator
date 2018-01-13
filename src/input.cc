#include "input.h"

#include "util/bitwise.h"

void Input::on_key_pressed(int keyCode) {
    on_key(keyCode, true);
}

void Input::on_key_released(int keyCode) {
    on_key(keyCode, false);
}

void Input::on_key(int keyCode, bool set) {
    if (keyCode == sf::Keyboard::Up) { up = set; }
    if (keyCode == sf::Keyboard::Down) { down = set; }
    if (keyCode == sf::Keyboard::Left) { left = set; }
    if (keyCode == sf::Keyboard::Right) { right = set; }
    if (keyCode == sf::Keyboard::Z) { a = set; }
    if (keyCode == sf::Keyboard::X) { b = set; }
    if (keyCode == sf::Keyboard::Return) { select = set; }
    if (keyCode == sf::Keyboard::BackSpace) { start = set; }
}

void Input::write(u8 set) {
    using bitwise::check_bit;

    direction_switch = check_bit(set, 4);
    button_switch = check_bit(set, 5);
}

u8 Input::get_input() const {
    using bitwise::set_bit_to;

    u8 buttons = 0b1111;

    if (direction_switch) {
        buttons = set_bit_to(buttons, 0, !right);
        if (!bitwise::check_bit(buttons, 0)) { log_error("right pressed"); }
        buttons = set_bit_to(buttons, 1, !left);
        if (!bitwise::check_bit(buttons, 1)) { log_error("left pressed"); }
        buttons = set_bit_to(buttons, 2, !up);
        if (!bitwise::check_bit(buttons, 2)) { log_error("up pressed"); }
        buttons = set_bit_to(buttons, 3, !down);
        if (!bitwise::check_bit(buttons, 3)) { log_error("down pressed"); }
    }

    if (button_switch) {
        buttons = set_bit_to(buttons, 0, !a);
        if (!bitwise::check_bit(buttons, 0)) { log_error("a pressed"); }
        buttons = set_bit_to(buttons, 1, !b);
        if (!bitwise::check_bit(buttons, 1)) { log_error("b pressed"); }
        buttons = set_bit_to(buttons, 2, !select);
        if (!bitwise::check_bit(buttons, 2)) { log_error("select pressed"); }
        buttons = set_bit_to(buttons, 3, !start);
        if (!bitwise::check_bit(buttons, 3)) { log_error("start pressed"); }
    }

    buttons = set_bit_to(buttons, 4, !direction_switch);
    buttons = set_bit_to(buttons, 5, !button_switch);

    return buttons;
}
