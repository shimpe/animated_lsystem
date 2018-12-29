#ifndef LINEARDEPTHLINETHICKNESS_H
#define LINEARDEPTHLINETHICKNESS_H

#include "idoublefromdepthcalculator.h"

enum LinearThicknessMode {
    DEEPER_IS_THINNER,
    DEEPER_IS_THICKER
};

class LinearDepthLineThickness : public IDoubleFromDepthCalculator
{
public:
    LinearDepthLineThickness(LinearThicknessMode mode, int maxdepth, double scale);
    virtual double Calculate(int depth) override;

private:
    LinearThicknessMode m_Mode;
    int m_MaxDepth;
    double m_Scale;
};

#endif // LINEARDEPTHLINETHICKNESS_H
