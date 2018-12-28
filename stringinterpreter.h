#ifndef RULEINTERPRETER_H
#define RULEINTERPRETER_H

class QString;
class QGraphicsView;
class QVector2D;
class QColor;
class QChar;

#include <QStack>
#include <QSet>

class StringInterpreter
{
public:
    StringInterpreter();
    ~StringInterpreter();

    void Draw(const QString &String,
              const QSet<QChar> &Constants,
              const QVector<QColor> &Colors,
              double AngleInDegrees,
              bool ClearScreen,
              MainWindow *window);

private:
    double GetLength(int depth) const;
    float GetThickness(int depth) const;
    QColor GetColor(int depth) const;

private:
    QStack<QVector2D> m_PositionStack;
    QStack<qreal> m_AngleStack;
    QColor m_CurrentColor;
};

#endif // RULEINTERPRETER_H
