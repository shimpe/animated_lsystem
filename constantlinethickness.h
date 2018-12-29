#ifndef CONSTANTLINETHICKNESS_H
#define CONSTANTLINETHICKNESS_H

#include "idoublefromdepthcalculator.h"

class ConstantValueProvider : public IDoubleFromDepthCalculator
{
public:
    ConstantValueProvider(double thickness);
    double Calculate(int depth) override;
private:
    double m_Thickness;
};

#endif // CONSTANTLINETHICKNESS_H
