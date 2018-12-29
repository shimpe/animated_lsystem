#include "lineardepthlinethickness.h"

LinearDepthLineThickness::LinearDepthLineThickness(LinearThicknessMode mode, int maxdepth, double scale)
    : IDoubleFromDepthCalculator()
    , m_Mode(mode)
    , m_MaxDepth(maxdepth)
    , m_Scale(scale)
{
}

double LinearDepthLineThickness::Calculate(int depth)
{
    if (m_Mode == DEEPER_IS_THINNER) {
        return (depth <= m_MaxDepth) ? (m_MaxDepth - depth)*m_Scale : 0;
    } else {
        return (depth <= m_MaxDepth) ? depth*m_Scale : m_MaxDepth*m_Scale;
    }
}

