#ifndef LSYSTEMPRESET_H
#define LSYSTEMPRESET_H

#include "rulesystem.h"
#include "renderhints.h"

class LSystemPreset
{
public:
    LSystemPreset();
    LSystemPreset(const RuleSystem &RuleSystem, const RenderHints &RenderHints);
    ~LSystemPreset();

    RuleSystem &ruleSystem();
    RenderHints &renderHints();

private:
    RuleSystem m_RuleSystem;
    RenderHints m_RenderHints;
};

#endif // LSYSTEMPRESET_H
