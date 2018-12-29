#include "constantvalueprovider.h"

ConstantValueProvider::ConstantValueProvider(double thickness)
    : IDoubleFromDepthCalculator()
    , m_Thickness(thickness)
{
}

double ConstantValueProvider::Calculate(int /*depth*/)
{
    return m_Thickness;
}
