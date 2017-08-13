#pragma once
#include <vector>
#include <functional>
#include <mutex.hpp>

extern mutex<std::vector<std::function<void(unsigned char *)>>> renderers;
extern mutex<std::vector<std::function<void(unsigned char *)>>> runOnce;

void rendererThread();

