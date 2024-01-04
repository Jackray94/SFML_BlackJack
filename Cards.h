#ifndef CARDS_H
#define CARDS_H

#include <unordered_map>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <chrono>

//I want to return by non-const since const would interfere std::vector move constructor being called. The vector elements are non-const as well because std::shuffle is called on the vector. 
[[nodiscard]] std::vector<std::string> cardKeys();


// void randomizeListOfCardKeys(std::vector<std::string> & list);


// I want to const the key / value pair because values won't change for a deck of cards. I believe that the key (std::string) will default to const anyway, so really I should just const the value. Using std::unordered_map<key, T> const would do this as well.
//
// It turns out that the above reasoning is bad, since std::unordered_map<key, T> const will prevent move semantics. What I want to do is call std::unordered_maps move ctor and cannot use const with it (const prevents move ctor from being called) - tangenially, I believe its okay to use a const mapped type as the move ctor should be called anyway. 
[[nodiscard]] std::unordered_map<std::string, int const> mapOfCards();


#endif
