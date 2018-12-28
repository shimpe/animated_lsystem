#include "mainwindow.h"
#include "stringinterpreter.h"
#include <QString>
#include <QGraphicsView>
#include <QVector2D>
#include <QtMath>
#include <QRectF>
#include <QPointF>
#include <QLineF>

#include <QDebug>

StringInterpreter::StringInterpreter()
{
    QColor Default("black");
    Default.setAlphaF(0.5);
    m_CurrentColor = Default;
}

StringInterpreter::~StringInterpreter()
{
}

void StringInterpreter::Draw(const QString &String,
                             const QSet<QChar> &Constants,
                             const QVector<QColor> &Colors,
                             double AngleInDegrees,
                             bool ClearScreen,
                             MainWindow* window)
{
    qreal minx = 1e100;
    qreal miny = 1e100;
    qreal maxx = -1e100;
    qreal maxy = -1e100;

    bool nextCharIsColor = false;

    QVector2D currentPosition;
    double currentAngle = 270.0;
    m_PositionStack.clear();
    m_PositionStack.push(currentPosition);
    m_AngleStack.clear();
    m_AngleStack.push(currentAngle);

    QGraphicsView &view = window->View();

    if (ClearScreen)
        view.scene()->clear();

    for (const auto &c : String)
    {
        if (nextCharIsColor)
        {
            int Index = c.unicode() - QChar('0').unicode();
            if (Colors.size() > Index)
            {
                m_CurrentColor = Colors.at(Index);
            }
            nextCharIsColor = false;
        }
        else
        {
            switch(c.unicode())
            {
                case 'C':
                {
                    nextCharIsColor = true;
                }
                break;
                case '+':
                {
                    currentAngle = currentAngle + AngleInDegrees;
                }
                break;

                case '-':
                {
                    currentAngle = currentAngle - AngleInDegrees;
                }
                break;

                case '[':
                {
                    m_PositionStack.push(currentPosition);
                    m_AngleStack.push(currentAngle);
                }
                break;

                case ']':
                {
                    if (!m_PositionStack.empty())
                    {
                        currentPosition = m_PositionStack.pop();
                    }
                    if (!m_AngleStack.empty())
                    {
                        currentAngle = m_AngleStack.pop();
                    }
                }
                break;

                default:
                {
                    if (!Constants.contains(c))
                    {
                        QVector2D newPos;
                        int depth = m_PositionStack.size();
                        newPos.setX(currentPosition.x() + GetLength(depth)*cos(qDegreesToRadians(currentAngle)));
                        newPos.setY(currentPosition.y() + GetLength(depth)*sin(qDegreesToRadians(currentAngle)));
                        view.scene()->addLine(QLineF(QPointF(currentPosition.x(), currentPosition.y()),
                                                      QPointF(newPos.x(), newPos.y())),
                                               QPen(QBrush(GetColor(depth), Qt::SolidPattern),
                                                    GetThickness(depth)));
                        currentPosition = newPos;

                        if (newPos.x() < minx)
                            minx = newPos.x();
                        if (newPos.x() > maxx)
                            maxx = newPos.x();
                        if (newPos.y() < miny)
                            miny = newPos.y();
                        if (newPos.y() > maxy)
                            maxy = newPos.y();
                    }
                }
                break;
            }
        }
    }

    window->View().scene()->setSceneRect(QRectF(QPointF(minx,miny), QPointF(maxx,maxy)));
}

double StringInterpreter::GetLength(int /*depth*/) const
{
    return 10.0;
}

float StringInterpreter::GetThickness(int depth) const
{
    //return (10-depth)/2.0;
    return 0.0;
}

QColor StringInterpreter::GetColor(int /*depth*/) const
{
    return m_CurrentColor;
}