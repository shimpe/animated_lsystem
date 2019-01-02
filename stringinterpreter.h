#ifndef RULEINTERPRETER_H
#define RULEINTERPRETER_H

class QString;
class QGraphicsView;
class QVector2D;
class QColor;
class QChar;
class MainWindow;
class LSystemPreset;

#include <QStack>
#include <QSet>
#include <QColor>

class StringInterpreter
{
public:
    StringInterpreter();
    ~StringInterpreter();

    void Draw(LSystemPreset &RuleSystem,
              double AngleInDegrees,
              bool ClearScreen,
              MainWindow *window);

private:
    QColor GetColor(int depth) const;

private:
    QStack<QVector2D> m_PositionStack;
    QStack<qreal> m_AngleStack;
    QColor m_CurrentColor;
};

#endif // RULEINTERPRETER_H
