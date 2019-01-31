#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include <QString>

class LSystemPreset;
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

    void setRenderLive();
    void setRenderToFile(const QString &renderFolder);
    bool renderLive() const;

    void startAnimation(double fps, int startFrame=0, int endFrame=-1);
    void redrawScene();

public slots:
    void animate();
    void animateSave();

private:
    std::unique_ptr<Ui::MainWindow> ui;
    std::unique_ptr<LSystemPreset> m_LSystemPreset;
    std::unique_ptr<StringInterpreter> m_Interpreter;
    std::unique_ptr<QTimer> m_Timer;
    unsigned long m_Ticks;
    bool m_RenderToFile;
    QString m_RenderFolder;
    double m_Fps; // frames per second
    double m_TimerDuration;
    int m_Frame;
    int m_startFrame;
    int m_endFrame;
};


#endif // MAINWINDOW_H
