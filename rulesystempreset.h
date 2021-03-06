#ifndef RULESYSTEMPRESET_H
#define RULESYSTEMPRESET_H

#include "lsystempreset.h"

enum RSP {
    HEIGHWAY_DRAGON,
    RANDOMCIRCLE,
    RANDOMCIRCLE_COLOR,
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
    PENROSE_TILING_COLOR,
    EYE_OF_SAURON,
    FERN_CLAW,
    NECKLACE,
    TWO_EYES_OF_SAURON,
    DANDELIONS,
    ABSTRACT_DANCE,
    KOLAM_PATTERN,
    KOCH_ISLAND,
    PENTAPLEXITY,
    STARRY_NECKLACE,
};

class RuleSystemPresetFactory
{
public:
    RuleSystemPresetFactory();
    LSystemPreset CreateRuleSystemPreset(RSP type, int NoOfIterations=-1); // -1 uses a default value
    double getRecommendedAngle(RSP type) const;
};

#endif // RULESYSTEMPRESET_H
