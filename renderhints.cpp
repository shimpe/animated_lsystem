#include "constantvalueprovider.h"
#include "renderhints.h"
#include <QColor>

RenderHints::RenderHints()
    : m_AngleIncrementPerSecond(1.0)
    , m_InitialAngle(270)
    , m_InitialAnimationAngle(0)
{
}

RenderHints::~RenderHints()
{
}

RenderHints::RenderHints(const RenderHints &other)
    : m_Colors(other.m_Colors)
    , m_LineThicknessCalculator(other.m_LineThicknessCalculator)
    , m_SegmentLengthCalculator(other.m_SegmentLengthCalculator)
    , m_AngleIncrementPerSecond(other.m_AngleIncrementPerSecond)
    , m_LengthForChar(other.m_LengthForChar)
    , m_InitialAngle(other.m_InitialAngle)
    , m_InitialPosition(other.m_InitialPosition)
    , m_InitialAnimationAngle(other.m_InitialAngle)
{
}

double RenderHints::getInitialAnimationAngle() const
{
    return m_InitialAnimationAngle;
}

void RenderHints::setInitialAnimationAngle(double InitialAnimationAngle)
{
    m_InitialAnimationAngle = InitialAnimationAngle;
}

const QVector2D &RenderHints::getInitialPosition() const
{
    return m_InitialPosition;
}

void RenderHints::setInitialPosition(const QVector2D &InitialPosition)
{
    m_InitialPosition = InitialPosition;
}

double RenderHints::getInitialAngle() const
{
    return m_InitialAngle;
}

void RenderHints::setInitialAngle(double InitialAngle)
{
    m_InitialAngle = InitialAngle;
}

double RenderHints::getAngleIncrementPerSecond() const
{
    return m_AngleIncrementPerSecond;
}

void RenderHints::setAngleIncrementPerSecond(double AngleIncrementPerSecond)
{
    m_AngleIncrementPerSecond = AngleIncrementPerSecond;
}

bool RenderHints::getScaleWithZoom() const
{
    if (m_LineThicknessCalculator) {
        return m_LineThicknessCalculator->ScaleWithZoom();
    }
    return true;
}

void RenderHints::addLengthForChar(const QChar &c, double Length)
{
    m_LengthForChar[c] = Length;
}

const QMap<QChar, double> &RenderHints::getLengths() const
{
    return m_LengthForChar;
}

void RenderHints::addColor(const QColor &c)
{
    m_Colors.push_back(c);
}

const QVector<QColor> &RenderHints::getColors() const
{
    return m_Colors;
}

void RenderHints::setThicknessCalculator(std::shared_ptr<IDoubleFromDepthCalculator> Calculator)
{
    m_LineThicknessCalculator = std::move(Calculator);
}

double RenderHints::getLineThickness(const QChar &c, int depth)
{
    if (!m_LineThicknessCalculator)
        m_LineThicknessCalculator = std::make_shared<ConstantValueProvider>(false, 0);
    return m_LineThicknessCalculator->Calculate(c, depth);
}

void RenderHints::setSegmentLengthCalculator(std::shared_ptr<IDoubleFromDepthCalculator> Calculator)
{
    m_SegmentLengthCalculator = std::move(Calculator);
}

double RenderHints::getSegmentLength(const QChar& c, int depth)
{
    if (!m_SegmentLengthCalculator)
        m_SegmentLengthCalculator = std::make_shared<ConstantValueProvider>(false, 10);
    return m_SegmentLengthCalculator->Calculate(c, depth);
}

