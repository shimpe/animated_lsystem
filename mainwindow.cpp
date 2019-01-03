#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <memory>
#include "rulesystem.h"
#include "stringinterpreter.h"
#include "rulesystempreset.h"
#include "rule.h"
#include <QTimer>
#include "idoublefromdepthcalculator.h"
//#include <QGLWidget>

#define TIMERDURATION (1000/25)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(std::unique_ptr<Ui::MainWindow>(new Ui::MainWindow))
    , m_LSystemPreset(std::unique_ptr<LSystemPreset>(new LSystemPreset()))
    , m_Interpreter(std::unique_ptr<StringInterpreter>(new StringInterpreter()))
    , m_Timer(std::unique_ptr<QTimer>(new QTimer(this)))
    , m_Ticks(0)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(new QGraphicsScene());
    //ui->graphicsView->setViewport(new QGLWidget());

    RuleSystemPresetFactory Presets;
    *m_LSystemPreset = Presets.CreateRuleSystemPreset(STARRY_NECKLACE);

    connect(m_Timer.get(), SIGNAL(timeout()), this, SLOT(animate()));
    m_Timer->start(TIMERDURATION);
}


QGraphicsView &MainWindow::View()
{
    return *ui->graphicsView;
}

void MainWindow::resizeEvent(QResizeEvent */*event*/)
{
    ui->graphicsView->fitInView(ui->graphicsView->sceneRect(), Qt::AspectRatioMode::KeepAspectRatio);
}

void MainWindow::animate()
{
    m_Ticks += 1;
    auto time_seconds = m_Ticks*TIMERDURATION/1000.0;
    auto Angle = m_LSystemPreset->renderHints().getInitialAnimationAngle() + time_seconds*m_LSystemPreset->renderHints().getAngleIncrementPerSecond();
    m_Interpreter->Draw(*m_LSystemPreset,
                        Angle,
                        true,
                        this);
    resizeEvent(nullptr);
}

MainWindow::~MainWindow()
{
}
