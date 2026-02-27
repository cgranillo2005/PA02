// Winter'25
// Instructor: Diba Mirza
// Student name: Carlos Granillo, Luke Nguyen

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>
#include <sstream>
using namespace std;

#include "utilities.h"
#include "movies.h"

bool parseLine(string &line, string &movieName, double &movieRating);

int main(int argc, char** argv){
    if (argc < 2){
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[ 0 ] << " moviesFilename prefixFilename " << endl;
        exit(1);
    }

    ifstream movieFile (argv[1]);
 
    if (movieFile.fail()){
        cerr << "Could not open file " << argv[1];
        exit(1);
    }
  
    vector<Movie> allMovies;

    string line, movieName;
    double movieRating;
    // Read each file and store the name and rating
    while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
        allMovies.push_back({movieName, movieRating});
    }

    movieFile.close();

    sort(allMovies.begin(), allMovies.end());

    if (argc == 2){
            for (const auto& m: allMovies) {
                cout << m.name << ", " << fixed << setprecision(1) << m.rating << endl;
            }
            return 0;
    }


    ifstream prefixFile (argv[2]);
    if (prefixFile.fail()) {
        cerr << "Could not open file " << argv[2];
        exit(1);
    }

    vector<string> prefixes;
    while (getline (prefixFile, line)) {
        if (!line.empty()) {
            prefixes.push_back(line);
        }
    }

    struct BestTracker {
        string prefix;
        string movieName;
        double rating;
        bool found;
    };

    vector<BestTracker> summary;

    for (const string& pre : prefixes) {
        // Finding the strat of the prefix range using binary search
        auto it = lower_bound(allMovies.begin(), allMovies.end(), Movie{pre, 0.0});

        vector<Movie> matches;
        // Collect all the movies that satisfy the prefix
        while (it != allMovies.end() && it->name.compare(0, pre.length(), pre) == 0) {
            matches.push_back(*it);
            ++it;
        } 

        if (matches.empty()) {
            cout << "No movies found with prefix " << pre << endl;
        } else {
            sort(matches.begin(), matches.end(), compareByRating);

            for (const auto& m : matches) {
                cout << m.name << ", " << fixed << setprecision(1) << m.rating << endl;
            }
            cout << endl;

            summary.push_back({pre, matches[0].name, matches[0].rating, true});
        }
    }

    for (const auto& item: summary) {
        if (item.found) {
            cout << "Best movie with prefix " << item.prefix << " is: " << item.movieName << " with rating " << fixed << setprecision(1) << item.rating << endl;
        }
    }

    return 0;
}

/*
Time Complexity Analysis
Let:
- n = total number of movies in the dataset
- m = the number of prefixes to search
- k = max num of movies that start with a given prefix
- l - max length of a movie name
*/

bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}