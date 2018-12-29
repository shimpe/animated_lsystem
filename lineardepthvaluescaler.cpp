#include "lineardepthvaluescaler.h"

LinearDepthValueScaler::LinearDepthValueScaler()
    : IDoubleFromDepthCalculator (false)
    , m_Mode(DEEPER_IS_LESS)
    , m_MaxDepth(10)
    , m_Scale(1.0)
    , m_Offset(0)
{
}

LinearDepthValueScaler::LinearDepthValueScaler(bool ScaleWithZoom, LinearThicknessMode mode, int maxdepth, double scale, double offset)
    : IDoubleFromDepthCalculator(ScaleWithZoom)
    , m_Mode(mode)
    , m_MaxDepth(maxdepth)
    , m_Scale(scale)
    , m_Offset(offset)
{
}

double LinearDepthValueScaler::Calculate(int depth)
{
    double val = 0;
    if (m_Mode == DEEPER_IS_LESS) {
        val = (m_MaxDepth - depth)*m_Scale + m_Offset;
    } else {
        val = (depth*m_Scale) + m_Offset;
    }
    if (val < 0)
        return 0;
    if (val > m_MaxDepth)
        return m_MaxDepth;
    return val;
}

