#include "movies.h"

bool compareByRating(const Movie& a, const Movie& b) {
    if (a.rating != b.rating) {
        return a.rating > b.rating;
    }
    return a.name < b.name;
}