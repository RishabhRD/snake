#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>
#include <cstddef>
#include <optional>
#include <vector>
#include "direction.hpp"
#include "event.hpp"
#include "property.hpp"
#include "ui/color.hpp"

namespace snk::ui {
inline std::optional<events::event> transform_event(sf::Event const& evt) {
  if (evt.type == sf::Event::Closed)
    return snk::events::quit{};
  if (evt.type == sf::Event::KeyPressed) {
    switch (evt.key.code) {
      case sf::Keyboard::H:
      case sf::Keyboard::Left:
      case sf::Keyboard::A:
        return events::direction_change{direction::left};
      case sf::Keyboard::J:
      case sf::Keyboard::Down:
      case sf::Keyboard::S:
        return events::direction_change{direction::down};
      case sf::Keyboard::K:
      case sf::Keyboard::Up:
      case sf::Keyboard::W:
        return events::direction_change{direction::up};
      case sf::Keyboard::L:
      case sf::Keyboard::Right:
      case sf::Keyboard::D:
        return events::direction_change{direction::right};
      case sf::Keyboard::Escape:
        return events::quit{};
      case sf::Keyboard::Space:
        return events::play_pause{};
      case sf::Keyboard::Return:
        return events::start{};
      default:
        return std::nullopt;
    }
  } else {
    return std::nullopt;
  }
}

class sfml_window {
  sf::RenderWindow win;
  sf::Color background;

 public:
  sfml_window(unsigned int width, unsigned int height, color bg,
              std::string_view title)
      : win(sf::VideoMode(width, height), title.data(), sf::Style::None),
        background(bg.r, bg.g, bg.b) {
    repaint();
  }

  inline std::vector<events::event> poll_events() {
    std::vector<events::event> res;
    sf::Event evt{};
    while (win.pollEvent(evt)) {
      auto transformed_event = transform_event(evt);
      if (transformed_event)
        res.push_back(transformed_event.value());
    }
    return res;
  }

  inline std::size_t width() const { return win.getSize().x; }

  inline std::size_t height() const { return win.getSize().y; }

  void draw_square(std::size_t x, std::size_t y, std::size_t size, color c) {
    sf::RectangleShape rect{
        sf::Vector2f(static_cast<float>(size), static_cast<float>(size))};
    rect.setPosition(static_cast<float>(x), static_cast<float>(y));
    rect.setFillColor(sf::Color(c.r, c.g, c.b));
    win.draw(rect);
  }

  bool draw_image(std::string_view path) {
    sf::Texture texture;
    sf::Sprite sprite;
    auto res = texture.loadFromFile(path.data());
    sprite.setTexture(texture);
    win.draw(sprite);
    return res;
  }

  void clear(color c) { win.clear(sf::Color{c.r, c.g, c.b}); }

  void repaint() { win.display(); }
};

inline auto make_window(app_properties const& prop) {
  unsigned int width = static_cast<unsigned int>(
      prop.game_properties.board_width * prop.ui_properties.scale_factor);
  unsigned int height = static_cast<unsigned int>(
      prop.game_properties.board_height * prop.ui_properties.scale_factor);
  return sfml_window{width, height, prop.ui_properties.bg_color, prop.title};
}
}  // namespace snk::ui
