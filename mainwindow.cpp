#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <memory>
#include "rulesystem.h"
#include "stringinterpreter.h"
#include "rulesystempreset.h"
#include "rule.h"
#include <QTimer>
#include "idoublefromdepthcalculator.h"
#include <QFile>
#include <QDebug>
#include <QDir>
#include <QPixmap>
#include <QScreen>
#include <QWindow>
//#include <QGLWidget>

void MainWindow::startAnimation(double fps, int startFrame, int endFrame)
{
    m_Fps = fps;
    m_TimerDuration = 1000.0/fps;
    if (renderLive()) {
        connect(m_Timer.get(), SIGNAL(timeout()), this, SLOT(animate()));
        m_Timer->start(static_cast<int>(m_TimerDuration));
    } else {
        QFile f(m_RenderFolder);
        if (!f.exists())
        {
            qDebug() << "Folder does not exist: " << m_RenderFolder << ". Trying to create it...";
            if (!QDir().mkpath(m_RenderFolder)) {
                qDebug() << "Failed to create " << m_RenderFolder << ".";
            }
        }
        m_startFrame = startFrame;
        m_endFrame = endFrame;
        connect(m_Timer.get(), SIGNAL(timeout()), this, SLOT(animateSave()));
        m_Timer->start(static_cast<int>(m_TimerDuration));
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(std::unique_ptr<Ui::MainWindow>(new Ui::MainWindow))
    , m_LSystemPreset(std::unique_ptr<LSystemPreset>(new LSystemPreset()))
    , m_Interpreter(std::unique_ptr<StringInterpreter>(new StringInterpreter()))
    , m_Timer(std::unique_ptr<QTimer>(new QTimer(this)))
    , m_Ticks(0)
    , m_RenderToFile(false)
    , m_Fps(25)
    , m_TimerDuration(100)
    , m_Frame(0)
    , m_startFrame(0)
    , m_endFrame(0)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(new QGraphicsScene());
    //ui->graphicsView->setViewport(new QGLWidget());

    RuleSystemPresetFactory Presets;
    *m_LSystemPreset = Presets.CreateRuleSystemPreset(STARRY_NECKLACE);
}


QGraphicsView &MainWindow::View()
{
    return *ui->graphicsView;
}

void MainWindow::resizeEvent(QResizeEvent */*event*/)
{
    ui->graphicsView->fitInView(ui->graphicsView->sceneRect(), Qt::AspectRatioMode::KeepAspectRatio);
}

void MainWindow::setRenderLive()
{
    m_RenderToFile = false;
}

void MainWindow::setRenderToFile(const QString &renderFolder)
{
    m_RenderToFile = true;
    m_RenderFolder = renderFolder;
}

bool MainWindow::renderLive() const
{
    return !m_RenderToFile;
}

void MainWindow::redrawScene()
{
    m_Ticks += 1;
    auto time_seconds = m_Ticks*m_Fps/1000.0;
    auto Angle = m_LSystemPreset->renderHints().getInitialAnimationAngle() + time_seconds*m_LSystemPreset->renderHints().getAngleIncrementPerSecond();
    m_Interpreter->Draw(*m_LSystemPreset,
                        Angle,
                        true,
                        this);
}

void MainWindow::animate()
{
    redrawScene();
    resizeEvent(nullptr);
}

void MainWindow::animateSave()
{
    animate();
    if (m_Frame >= m_startFrame && m_Frame <= m_endFrame) {
        QString imageName = QString("frame_%1.png").arg(m_Frame, 6, 10, QChar('0'));
        QString fullPath = m_RenderFolder + QDir().separator() + imageName;
        qDebug() << "Writing frame " << m_Frame << " to file " << fullPath;
        QScreen *screen = QGuiApplication::primaryScreen();
        if (const QWindow *window = windowHandle())
            screen = window->screen();
        if (!screen) {
            qDebug() << "No screen found.";
            return;
        }
        QPixmap originalPixmap = screen->grabWindow(0);
        originalPixmap.save(fullPath);
    }
    qDebug() << "increase m_Frame to " << m_Frame << " startFrame = " << m_startFrame << " endFrame = " << m_endFrame;
    m_Frame++;
}

MainWindow::~MainWindow()
{
}
