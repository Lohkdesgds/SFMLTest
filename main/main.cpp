#include <iostream>
#include <SFML/Graphics.hpp>
#include <battery/embed.hpp>
#include <chrono>

#include "logo.h"
#include "async_update.h"
#include "fps_counter.h"

int main(int argc, char* argv[]) {
    const char* game_name = "SFML Test";

    const auto def_windowed_res = sf::VideoMode({1280u, 720u});
    auto window = sf::RenderWindow(def_windowed_res, game_name);
    int fps_limit = 60;
    bool window_fs = false;
    bool fps_show = true;

    const auto font_file = b::embed<"assets/EMprint-Regular.ttf">();
    const auto image_file = b::embed<"assets/misu.png">();


    const sf::Font font(font_file.data(), font_file.size());
    sf::Text text(font, "FPS: 0", 15);
    FPSCounter fps_counter;
    Logo logo(image_file);

    text.setPosition({10.0f, 5.0f});
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(1.0f);

    window.setFramerateLimit(fps_limit);    

    const auto update_window_size = [&window]() {
        const auto size = window.getSize();
        auto curr_view = window.getView();
        curr_view.setSize({1.0f * size.x, 1.0f  * size.y});
        curr_view.setCenter({0.5f * size.x, 0.5f * size.y});
        window.setView(curr_view);
    };

    AsyncUpdate logo_refresh(
        std::chrono::milliseconds(1000 / 30),
        [&logo, &window]() {
            logo.update_position(window.getSize().x, window.getSize().y);
        }
    );

    AsyncUpdate fps_refresh(
        std::chrono::milliseconds(200),
        [&text, &fps_counter, &window, &window_fs, &fps_limit]() {
            text.setString(
                "FPS: " + std::to_string(fps_counter.get_fps()) + "\n"
                "Resolution: " + std::to_string(window.getSize().x) + "x" + std::to_string(window.getSize().y) + "\n"
                "Fullscreen: " + std::string(window_fs ? "true" : "false") + "\n"
                "FPS limit: " + (fps_limit > 0 ? std::to_string(fps_limit) : "unlimited") + "\n\n"
                "Press F11 to toggle fullscreen\n"
                "Press F3 to toggle this overlay\n"
                "Press F5 to change FPS limit\n"                
            );
        }
    );

    update_window_size();

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            if (event->is<sf::Event::Resized>())
            {
                update_window_size();
            }
            if (event->is<sf::Event::KeyPressed>())
            {
                switch(event->getIf<sf::Event::KeyPressed>()->code) {
                case sf::Keyboard::Key::F11:
                {   
                    std::cout << "Fullscreen toggle activated." << std::endl;

                    if (window_fs = !window_fs)
                    {
                        const auto fs_modes = sf::VideoMode::getFullscreenModes();

                        //std::cout << "Available fullscreen modes:" << std::endl;
                        //for(const auto& i : fs_modes) std::cout << "- " << i.size.x << "x" << i.size.y << std::endl;
                        
                        window.create(fs_modes[0], game_name, sf::State::Fullscreen);
                    }
                    else
                    {
                        window.create(def_windowed_res, game_name, sf::State::Windowed);
                    }
                    
                    window.setFramerateLimit(fps_limit);
                    update_window_size();
                }
                    break;
                case sf::Keyboard::Key::F3:
                {
                    std::cout << "Toggling FPS overlay" << std::endl;
                    fps_show = !fps_show;
                }
                    break;
                case sf::Keyboard::Key::F5:
                {
                    switch(fps_limit) {
                    case 0: fps_limit = 30; break;
                    case 30: fps_limit = 60; break;
                    case 60: fps_limit = 120; break;
                    case 120: fps_limit = 240; break;
                    case 240: fps_limit = 500; break;
                    case 500: fps_limit = 1000; break;
                    default: fps_limit = 0; break;
                    }

                    std::cout << "FPS limit set to " << fps_limit << std::endl;
                    window.setFramerateLimit(fps_limit);
                }
                    break;
                }
            }
        }

        fps_counter.tick();

        const auto current_run_time = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()
        ).count() / 1000.0;

        const auto r = static_cast<unsigned char>(127 + 80 * cos(current_run_time * 0.5));
        const auto g = static_cast<unsigned char>(127 + 80 * cos(current_run_time * 0.3 + 1.4));
        const auto b = static_cast<unsigned char>(127 + 80 * cos(current_run_time * 0.2 + 2.3));

        window.clear(sf::Color(r, g, b));
        logo.update_draw(fps_counter.get_fps());
        window.draw(logo);
        if (fps_show) window.draw(text);
        window.display();
    }

    return 0;
}