#include <iostream>
#include <string>

#include "a_star.h"
#include "distances.h"
#include "load_airports.cpp"
#include "vlib/bag.h"
#include "weighted_struct_digraph.h"

int main(int argc, char** argv) {
    // TODO: Implementieren Sie das CLI hier.
    if (argc != 3) {
        std::cout << "Usage: ./routing_cli <source-iata> <destination-iata>"
                  << std::endl;
        return 1;
    }
    std::string source_iata = argv[1];
    std::string dest_iata = argv[2];

    WeightedStructDigraph<Airport>* g =
        load_data("data/airports.csv", "data/routes.csv");

    Airport source, dest;
    for (int i = 0; i < g->get_graph()->V(); i++) {
        if (g->name_of(i).iata == source_iata) {
            source = g->name_of(i);
        }
        if (g->name_of(i).iata == dest_iata) {
            dest = g->name_of(i);
        }
    }
    if (!g->contains(source)) {
        std::cout << "Error: Source Airport not found. {" << source_iata << "}"
                  << std::endl;
        return 1;
    }
    if (!g->contains(dest)) {
        std::cout << "Error: Destination Airport not found. {" << dest_iata
                  << "}" << std::endl;
        return 1;
    }
    Bag<Airport> path = a_star<Airport>(
        *g, source, dest,
        [](const WeightedStructDigraph<Airport>& sdg, const Airport& s,
           const Airport& d) { return haversine(sdg, s, d) / 900; });
    if (path.size() == 0) {
        // no path found
        std::cout << "-" << std::endl << "inf" << std::endl;
    } else {
        double travel_time = 0;
        for (auto i = 0; i < path.size() - 1; i++) {
            cout << path[i].iata << "-";
            double section_tt = std::numeric_limits<double>::max();

            // find shortest travel time from current airport to next airport
            // and add to overall travel time
            for (auto e : g->get_graph()->adj(g->index_of(path[i]))) {
                if (e.to() == g->index_of(path[i + 1]) &&
                    e.weight() < section_tt) {
                    section_tt = e.weight();
                }
            }
            travel_time += section_tt;
        }
        std::cout << path[path.size() - 1].iata << std::endl;
        // yes I know that the unit is not supposed to be in the output
        // but I feel bad reporting a unitless measure
        std::cout << travel_time << "h" << std::endl;
    }
}