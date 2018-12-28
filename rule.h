#ifndef RULE_H
#define RULE_H

#include <QString>

class Rule
{
public:
    Rule();
    Rule(const QString &LHS, const QString &rhs, double Probability);

    QString LHS() const;
    void setLHS(const QString &LHS);

    QString RHS() const;
    void setRHS(const QString &RHS);

    double Probability() const;
    void setProbability(double Probability);

private:
    QString m_LHS;
    QString m_RHS;
    double m_Probability;
};

#endif // RULE_H
