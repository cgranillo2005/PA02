#ifndef MOVIES_H
#define MOVIES_H

#include <string>

struct Movie {
    std::string name;
    double rating;

    // Part 1
    bool operator<(const Movie& other) const {
        return name < other.name;
    }
};

// For Part 2:
bool compareByRating(const Movie& a, const Movie& b);

#endif