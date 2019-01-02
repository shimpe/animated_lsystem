#include "lsystempreset.h"
#include "rule.h"
#include "rulesystem.h"
#include "renderhints.h"

LSystemPreset::LSystemPreset()
{   
}

LSystemPreset::LSystemPreset(const RuleSystem &RSystem, const RenderHints &RHints)
    : m_RuleSystem(RSystem)
    , m_RenderHints(RHints)
{
}

LSystemPreset::~LSystemPreset()
{
}

RuleSystem &LSystemPreset::ruleSystem()
{
    return m_RuleSystem;
}

RenderHints &LSystemPreset::renderHints()
{
    return m_RenderHints;
}
