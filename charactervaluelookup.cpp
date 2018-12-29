#include "charactervaluelookup.h"

CharacterValueLookup::CharacterValueLookup()
    : IDoubleFromDepthCalculator(false)
    , m_Default(1.0)
{
}

CharacterValueLookup::CharacterValueLookup(const QMap<QChar, double> &LookupTable, double Default)
    : IDoubleFromDepthCalculator (false)
    , m_LookupTable(LookupTable)
    , m_Default(Default)
{
}

double CharacterValueLookup::Calculate(const QChar &c, int /*depth*/)
{
    if (m_LookupTable.contains(c))
    {
        return m_LookupTable[c];
    }

    return m_Default;
}

const QMap<QChar, double> &CharacterValueLookup::LookupTable() const
{
    return m_LookupTable;
}

void CharacterValueLookup::setLookupTable(const QMap<QChar, double> &LookupTable)
{
    m_LookupTable = LookupTable;
}

double CharacterValueLookup::Default() const
{
    return m_Default;
}

void CharacterValueLookup::setDefault(double Default)
{
    m_Default = Default;
}
