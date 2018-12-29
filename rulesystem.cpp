#include "rulesystem.h"
#include "rule.h"
#include <QColor>
#include <QRandomGenerator>
#include "idoublefromdepthcalculator.h"
#include "constantlinethickness.h"

RuleSystem::RuleSystem()
    : m_NoOfIterations(0)
    , m_CacheUpToDate(false)
{
}

void RuleSystem::addRule(const Rule &Rule)
{
    m_Rules.push_back(Rule);
    m_CacheUpToDate = false;
}

void RuleSystem::addConstant(const QChar &c)
{
    m_Constants.insert(c);
}

const QSet<QChar> &RuleSystem::getConstants() const
{
    return m_Constants;
}

void RuleSystem::addColor(const QColor &c)
{
    m_Colors.push_back(c);
}

const QVector<QColor> &RuleSystem::getColors() const
{
    return m_Colors;
}

void RuleSystem::setThicknessCalculator(std::unique_ptr<IDoubleFromDepthCalculator> Calculator)
{
    m_LineThicknessCalculator = std::move(Calculator);
}

double RuleSystem::getLineThickness(int depth)
{
    if (!m_LineThicknessCalculator)
        m_LineThicknessCalculator = std::unique_ptr<ConstantValueProvider>(new ConstantValueProvider(0));
    return m_LineThicknessCalculator->Calculate(depth);
}

int RuleSystem::NoOfIterations() const
{
    return m_NoOfIterations;
}

void RuleSystem::setNoOfIterations(int Iterations)
{
    if (Iterations != m_NoOfIterations)
    {
        m_NoOfIterations = Iterations;
        m_CacheUpToDate = false;
    }
}

bool RuleSystem::CacheUpToDate() const
{
    return m_CacheUpToDate;
}

void RuleSystem::setCacheUpToDate(bool UpToDate)
{
    m_CacheUpToDate = UpToDate;
}

const QString &RuleSystem::CalculatedString()
{
    if (!m_CacheUpToDate)
        Recalculate();

    return m_CalculatedString;
}

void RuleSystem::setCalculatedString(const QString &Rule)
{
    m_CalculatedString = Rule;
    m_CacheUpToDate = true;
}

void RuleSystem::Recalculate()
{
    m_CalculatedString = Axiom();
    for (int i = 0; i < m_NoOfIterations; ++i)
    {
        QString newString;
        for (const QChar &c : m_CalculatedString)
        {
            bool foundApplicableRule = false;
            for (const auto &r : m_Rules)
            {
                if (!foundApplicableRule && r.LHS() == c)
                {
                    bool Ok = true;
                    if (r.Probability() < 1.0)
                    {
                        double prob = QRandomGenerator::global()->generateDouble();
                        Ok = prob <= r.Probability();
                    }
                    if (Ok)
                    {
                        newString = newString + r.RHS();
                        foundApplicableRule = true;
                    }
                }
            }
            if (!foundApplicableRule)
            {
                newString = newString + c;
            }
        }
        m_CalculatedString = newString;
    }
    m_CacheUpToDate = true;
}

const QString &RuleSystem::Axiom() const
{
    return m_Axiom;
}

void RuleSystem::setAxiom(const QString &Axiom)
{
    if (m_Axiom != Axiom)
    {
        m_Axiom = Axiom;
        m_CacheUpToDate = false;
    }
}
