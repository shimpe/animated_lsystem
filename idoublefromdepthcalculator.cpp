#include "idoublefromdepthcalculator.h"

IDoubleFromDepthCalculator::IDoubleFromDepthCalculator(bool ScaleWithZoom)
    : m_ScaleWithZoom(ScaleWithZoom)
{
}

bool IDoubleFromDepthCalculator::ScaleWithZoom() const
{
    return m_ScaleWithZoom;
}

void IDoubleFromDepthCalculator::setScaleWithZoom(bool ScaleWithZoom)
{
    m_ScaleWithZoom = ScaleWithZoom;
}
