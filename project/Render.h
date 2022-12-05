#pragma once
#include "User.h"

std::array<std::array<Square, HEIGHT>, WIDTH> mapRendering(User& user, std::array<Position, 4>& enemy, const std::array<std::string, HEIGHT>& outline);