#ifndef __AIRPORT_H
#define __AIRPORT_H
// das Test-Struct, das wir in den tests in Graphen packen
// bitte nicht verändern!
struct TestAirport {
    int id;
    float lat;
    float lon;
    bool operator<(const TestAirport& rhs) const { return id < rhs.id; }
    bool operator>(const TestAirport& rhs) const { return id > rhs.id; }
    bool operator==(const TestAirport& rhs) const { return id == rhs.id; }
};
#endif
