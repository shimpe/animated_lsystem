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
    ~RuleSystem();

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

private:
    void Recalculate();

private:
    QString m_Axiom;
    QSet<QChar> m_Constants;
    QVector<Rule> m_Rules;
    int m_NoOfIterations;
    QString m_CalculatedString;
    bool m_CacheUpToDate;
};

#endif // RULESYSTEM_H
