#ifndef CONSTANTLINETHICKNESS_H
#define CONSTANTLINETHICKNESS_H

#include "idoublefromdepthcalculator.h"

class ConstantValueProvider : public IDoubleFromDepthCalculator
{
public:
    ConstantValueProvider();
    ConstantValueProvider(bool ScaleWithZoom, double thickness);
    double Calculate(const QChar &c, int depth) override;

private:
    double m_Thickness;
};

#endif // CONSTANTLINETHICKNESS_H
