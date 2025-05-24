#include "logo.h"

#include <iostream>
#include <battery/embed.hpp>
#include <math.h>

Logo::Logo(const b::EmbedInternal::EmbeddedFile& file) {

    if (!texture.loadFromMemory(file.data(), file.size())) {
        std::cerr << "Error loading texture" << std::endl;
        return;
    }

    sprite = std::make_unique<sf::Sprite>(texture);
}

Logo::~Logo() {
    sprite.reset();
}

Logo::operator const sf::Sprite&() const {
    return *sprite;
}


void Logo::update_draw(const double fps) {
    const auto factor = std::min((1.0f / static_cast<float>(std::max(fps, 1.0))) * smoothness, 1.0f);
    
    draw_x = (x * factor + draw_x) / (factor + 1.0f);
    draw_y = (y * factor + draw_y) / (factor + 1.0f);

    sprite->setPosition({draw_x, draw_y});
}

void Logo::update_position(const float lim_x, const float lim_y) {
    x += speed_x;
    y += speed_y;

    if (x < 0 || x > lim_x - texture.getSize().x) {
        speed_x = -speed_x;
        x = std::max(0.f, std::min(x, lim_x - texture.getSize().x));
    }
    if (y < 0 || y > lim_y - texture.getSize().y) {
        speed_y = -speed_y;
        y = std::max(0.f, std::min(y, lim_y - texture.getSize().y));
    }
}