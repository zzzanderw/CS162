#ifndef HARVESTER_HPP
#define HARVESTER_HPP

#include "../ant.hpp"
#include "../entity.hpp"

class Harvester : public Ant {
public:
    Harvester();

    void action(Board&);
};

#endif