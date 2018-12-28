#ifndef RULESYSTEMPRESET_H
#define RULESYSTEMPRESET_H

#include "rulesystem.h"

enum RSP {
    HEIGHWAY_DRAGON,
    RANDOMCIRCLE,
    KOCHCURVE,
    SIERPINSKY_CURVED,
    SIERPINSKY_TRIANGLES,
    DRAGON,
    KEVS_TREE,
    KEVS_WISPY_TREE,
    KOCH_SNOWFLAKE,
    PENTAGON_LAKE,
    SIERPINSKY_CARPET,
    PENROSE_TILING,
    PENROSE_TILING_TEST
};

class RuleSystemPreset
{
public:
    RuleSystemPreset();
    RuleSystem CreateRuleSystem(RSP type, int NoOfIterations=-1); // -1 uses a default value
    double GetDefaultAngle(RSP type) const;
};

#endif // RULESYSTEMPRESET_H
