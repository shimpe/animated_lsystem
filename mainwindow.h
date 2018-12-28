#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

class RuleSystem;
class StringInterpreter;
class QGraphicsView;
class QResizeEvent;
class QTimer;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow() override;

    QGraphicsView &View();
    virtual void resizeEvent(QResizeEvent *event) override;

public slots:
    void animate();

private:
    std::unique_ptr<Ui::MainWindow> ui;
    std::unique_ptr<RuleSystem> m_RuleSystem;
    std::unique_ptr<StringInterpreter> m_Interpreter;
    std::unique_ptr<QTimer> m_Timer;
    unsigned long m_Ticks;
};


#endif // MAINWINDOW_H
