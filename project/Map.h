#pragma once

void print(const std::array<std::array<Square, HEIGHT>, WIDTH>& outline, sf::RenderWindow& window);
bool collision(int x, int y, std::array<std::array<Square, HEIGHT>, WIDTH>& map, bool score, bool exit);
