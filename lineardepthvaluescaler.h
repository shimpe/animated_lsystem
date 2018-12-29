#ifndef LINEARDEPTHLINETHICKNESS_H
#define LINEARDEPTHLINETHICKNESS_H

#include "idoublefromdepthcalculator.h"

enum LinearThicknessMode {
    DEEPER_IS_LESS,
    DEEPER_IS_MORE
};

class LinearDepthValueScaler : public IDoubleFromDepthCalculator
{
public:
    LinearDepthValueScaler();
    LinearDepthValueScaler(bool ScaleWithZoom, LinearThicknessMode mode, int maxdepth, double scale, double offset);
    virtual double Calculate(int depth) override;

private:
    LinearThicknessMode m_Mode;
    int m_MaxDepth;
    double m_Scale;
    double m_Offset;
};

#endif // LINEARDEPTHLINETHICKNESS_H
