#ifndef RULESYSTEM_H
#define RULESYSTEM_H

#include <QVector>
#include <QString>
#include <QSet>
#include <memory>
#include <QMap>
#include <QVector2D>

class Rule;
class QChar;
class QColor;
class IDoubleFromDepthCalculator;

class RuleSystem
{
public:
    RuleSystem();

    void addRule(const Rule &Rule);

    int NoOfIterations() const;
    void setNoOfIterations(int NoOfIterations);

    bool CacheUpToDate() const;
    void setCacheUpToDate(bool CacheUpToDate);

    const QString &CalculatedString();
    void setCalculatedString(const QString &CalculatedString);

    const QString &Axiom() const;
    void setAxiom(const QString &Axiom);

    void addConstant(const QChar &c);
    const QSet<QChar> &getConstants() const;

    void addColor(const QColor &c);
    const QVector<QColor> &getColors() const;

    void setThicknessCalculator(std::unique_ptr<IDoubleFromDepthCalculator> Calculator);
    double getLineThickness(const QChar &c, int depth);

    void setSegmentLengthCalculator(std::unique_ptr<IDoubleFromDepthCalculator> Calculator);
    double getSegmentLength(const QChar &c, int depth);

    double getAngleIncrementPerSecond() const;
    void setAngleIncrementPerSecond(double AngleIncrementPerSecond);

    bool getScaleWithZoom() const;

    bool addLengthForChar(const QChar &c, double Length);
    const QMap<QChar, double> &getLengths() const;

    double getInitialAngle() const;
    void setInitialAngle(double InitialAngle);

    const QVector2D &getInitialPosition() const;
    void setInitialPosition(const QVector2D &InitialPosition);

    double getInitialAnimationAngle() const;
    void setInitialAnimationAngle(double InitialAnimationAngle);

private:
    void Recalculate();

private:
    QString m_Axiom;
    QSet<QChar> m_Constants;
    QVector<Rule> m_Rules;
    int m_NoOfIterations;
    QString m_CalculatedString;
    bool m_CacheUpToDate;
    QVector<QColor> m_Colors;
    std::unique_ptr<IDoubleFromDepthCalculator> m_LineThicknessCalculator;
    std::unique_ptr<IDoubleFromDepthCalculator> m_SegmentLengthCalculator;
    double m_AngleIncrementPerSecond;
    QMap<QChar, double> m_LengthForChar;
    double m_InitialAngle;
    QVector2D m_InitialPosition;
    double m_InitialAnimationAngle;
};

#endif // RULESYSTEM_H
