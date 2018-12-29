#ifndef CONSTANTLINETHICKNESS_H
#define CONSTANTLINETHICKNESS_H

#include "idoublefromdepthcalculator.h"

class ConstantLineThickness : public IDoubleFromDepthCalculator
{
public:
    ConstantLineThickness(double thickness);
    double Calculate(int depth) override;
private:
    double m_Thickness;
};

#endif // CONSTANTLINETHICKNESS_H
