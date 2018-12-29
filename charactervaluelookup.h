#ifndef CHARACTERVALUELOOKUP_H
#define CHARACTERVALUELOOKUP_H

#include "idoublefromdepthcalculator.h"
#include <QMap>

class QChar;

class CharacterValueLookup : public IDoubleFromDepthCalculator
{
public:
    CharacterValueLookup();
    CharacterValueLookup(const QMap<QChar, double> &LookupTable, double Default);

    virtual double Calculate(const QChar &c, int depth) override;

    const QMap<QChar, double> &LookupTable() const;
    void setLookupTable(const QMap<QChar, double> &LookupTable);

    double Default() const;
    void setDefault(double Default);

private:
    QMap<QChar, double> m_LookupTable;
    double m_Default;
};

#endif // CHARACTERVALUELOOKUP_H
