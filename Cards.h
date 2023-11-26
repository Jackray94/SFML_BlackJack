#ifndef CARDS_H
#define CARDS_H

#include <unordered_map>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <chrono>

std::vector<std::string> cardKeys();

std::unordered_map<std::string, int> mapOfCards();

#endif
