#ifndef __DISTANCES_H
#define __DISTANCES_H
#include <cmath>

#include "weighted_struct_digraph.h"

// In all of these cases I assume that a and b are of the same type
// and that a is the current node and b is the node I want to go to

const double EARTH_RADIUS =
    6371.0;  // Earth's radius in kilometers (use this one)

double toRadians(double degrees) { return degrees * M_PI / 180.0; }

template <typename T>
float haversine(const WeightedStructDigraph<T> &g, const T &a, const T &b) {
    // I return the geodesic distance between a and b
    // Meaning the distance on a great circle.
    // I use the haversine formula for this.

    double lat1_rad = toRadians(a.lat);
    double lon1_rad = toRadians(a.lon);
    double lat2_rad = toRadians(b.lat);
    double lon2_rad = toRadians(b.lon);

    double dLat = lat2_rad - lat1_rad;
    double dLon = lon2_rad - lon1_rad;

    double ta = pow(sin(dLat / 2), 2) +
                cos(lat1_rad) * cos(lat2_rad) * pow(sin(dLon / 2), 2);
    double c = 2 * atan2(sqrt(ta), sqrt(1 - ta));

    return EARTH_RADIUS * c;
}

template <typename T>
float euclidean(const WeightedStructDigraph<T> &sdg, const T &a, const T &b) {
    /*
    I return the euclidean distance between a and b
    S . . . .
    . \ . . .
    . . \ . .
    . . . Z .
    . . . . .
    */
    auto x = a.lat - b.lat;
    auto y = a.lon - b.lon;
    return sqrt(x * x + y * y);
};

template <typename T>
float manhattan(const WeightedStructDigraph<T> &g, const T &a, const T &b) {
    /*
    I return the manhattan distance between a and b
    S - - ┐ .
    . . . | .
    . . . | .
    . . . Z .
    . . . . .
    */
    auto x = a.lat - b.lat;
    auto y = a.lon - b.lon;
    return abs(x) + abs(y);
};

template <typename T>
float out_degree(const WeightedStructDigraph<T> &g, const T &a, const T &b) {
    // I return a heuristik which is dependend on the indegree of b
    // meaning the number of edges going out of b
    int idx_b = g.index_of(b);
    return -(g.get_graph()->outdegree(idx_b));
};

#endif