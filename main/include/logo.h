#pragma once

#include <SFML/Graphics.hpp>
#include <battery/embed.hpp>
#include <math.h>
#include <memory>

class Logo {
    static constexpr float speed = 4.0f;
    static constexpr float smoothness = 10.0f; // lower is smoother

    sf::Texture texture;
    std::unique_ptr<sf::Sprite> sprite;

    float draw_x{}, draw_y{}, x{}, y{};
    float speed_x = speed, speed_y = speed;
public:
    Logo(const b::EmbedInternal::EmbeddedFile& file);
    ~Logo();

    operator const sf::Sprite&() const;

    void update_draw(const double fps);
    void update_position(const float lim_x, const float lim_y);
};