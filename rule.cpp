#include "rule.h"
#include <string>

Rule::Rule()
    : m_Probability(1.0f)
{
}

Rule::Rule(const QString &LHS, const QString &RHS, double Probability)
    : m_LHS(LHS)
    , m_RHS(RHS)
    , m_Probability(Probability)
{
}

QString Rule::LHS() const
{
    return m_LHS;
}

void Rule::setLHS(const QString &LHS)
{
    m_LHS = LHS;
}

QString Rule::RHS() const
{
    return m_RHS;
}

void Rule::setRHS(const QString &RHS)
{
    m_RHS = RHS;
}

double Rule::Probability() const
{
    return m_Probability;
}

void Rule::setProbability(double Probability)
{
    m_Probability = Probability;
}
