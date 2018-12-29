#include "constantvalueprovider.h"

ConstantValueProvider::ConstantValueProvider()
    : IDoubleFromDepthCalculator (false)
    , m_Thickness(0)
{
}

ConstantValueProvider::ConstantValueProvider(bool ScaleWithZoom, double thickness)
    : IDoubleFromDepthCalculator(ScaleWithZoom)
    , m_Thickness(thickness)
{
}

double ConstantValueProvider::Calculate(const QChar &/*c*/, int /*depth*/)
{
    return m_Thickness;
}
