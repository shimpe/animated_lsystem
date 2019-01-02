#ifndef RENDERHINTS_H
#define RENDERHINTS_H

#include <QVector>
#include <QVector2D>
#include <QMap>
#include <memory>

#include "idoublefromdepthcalculator.h"

class QColor;
class QChar;

class RenderHints
{
public:
    RenderHints();
    ~RenderHints();
    // RenderHints(const RenderHints &other);

    void addColor(const QColor &c);
    const QVector<QColor> &getColors() const;

    void setThicknessCalculator(std::shared_ptr<IDoubleFromDepthCalculator> Calculator);
    double getLineThickness(const QChar &c, int depth);

    void setSegmentLengthCalculator(std::shared_ptr<IDoubleFromDepthCalculator> Calculator);
    double getSegmentLength(const QChar &c, int depth);

    double getAngleIncrementPerSecond() const;
    void setAngleIncrementPerSecond(double AngleIncrementPerSecond);

    bool getScaleWithZoom() const;

    void addLengthForChar(const QChar &c, double Length);
    const QMap<QChar, double> &getLengths() const;

    double getInitialAngle() const;
    void setInitialAngle(double InitialAngle);

    const QVector2D &getInitialPosition() const;
    void setInitialPosition(const QVector2D &InitialPosition);

    double getInitialAnimationAngle() const;
    void setInitialAnimationAngle(double InitialAnimationAngle);

private:
    QVector<QColor> m_Colors;
    std::shared_ptr<IDoubleFromDepthCalculator> m_LineThicknessCalculator;
    std::shared_ptr<IDoubleFromDepthCalculator> m_SegmentLengthCalculator;
    double m_AngleIncrementPerSecond;
    QMap<QChar, double> m_LengthForChar;
    double m_InitialAngle;
    QVector2D m_InitialPosition;
    double m_InitialAnimationAngle;
};

#endif // RENDERHINTS_H
