#include "constantlinethickness.h"

ConstantLineThickness::ConstantLineThickness(double thickness)
    : IDoubleFromDepthCalculator()
    , m_Thickness(thickness)
{
}

double ConstantLineThickness::Calculate(int /*depth*/)
{
    return m_Thickness;
}
