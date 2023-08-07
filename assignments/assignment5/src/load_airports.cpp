#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

#include "vlib/bag.h"
#include "weighted_struct_digraph.h"

struct Airport {
    int id;
    float lat;
    float lon;
    std::string iata;
    std::string name;
    bool operator<(const Airport& rhs) const { return id < rhs.id; }
    bool operator>(const Airport& rhs) const { return id > rhs.id; }
    bool operator==(const Airport& rhs) const { return id == rhs.id; }
};

std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);

    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

WeightedStructDigraph<Airport>* load_data(std::string airports_file,
                                          std::string routes_file) {
    std::ifstream airports(airports_file);
    std::ifstream routes(routes_file);
    Bag<Airport> vertices;
    std::string line;
    while (std::getline(airports, line)) {
        std::vector<std::string> tokens = split(line, ',');
        Airport airport;
        airport.id = std::stoi(tokens[0]);
        airport.lat = std::stof(tokens[6]);
        airport.lon = std::stof(tokens[7]);
        airport.iata = tokens[4];
        airport.name = tokens[1];
        vertices.add(airport);
    }
    WeightedStructDigraph<Airport>* sdg =
        new WeightedStructDigraph<Airport>(vertices);
    while (std::getline(routes, line)) {
        std::vector<std::string> tokens = split(line, ',');
        Airport source = Airport{std::stoi(tokens[3]), 0, 0, "", ""};
        Airport dest = Airport{std::stoi(tokens[5]), 0, 0, "", ""};
        float dist = std::stof(tokens[8]);
        sdg->add_edge(source, dest, dist);
    }
    return sdg;
}