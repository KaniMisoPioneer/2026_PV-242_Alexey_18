#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , timer(new QTimer(this))
    , elapsedSeconds(0)
{
    ui->setupUi(this);

    connect(timer, &QTimer::timeout, this, &MainWindow::onTimerTick);

    connect(ui->exerciseBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onExerciseChanged);
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::onStartClicked);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::onStopClicked);

    ui->goalProgress->setValue(0);

    loadExercises();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::loadExercises() {
    ui->exerciseBox->addItem("Планка", 60);
    ui->exerciseBox->addItem("Отжимания", 45);
    ui->exerciseBox->addItem("Приседания", 90);

    onExerciseChanged(0);
}

void MainWindow::onExerciseChanged(int index) {
    if (timer->isActive()) {
        timer->stop();
    }
    resetProgress();
    updateTimerDisplay();

    QString name = ui->exerciseBox->itemText(index);
    int baseTime = ui->exerciseBox->itemData(index).toInt();
    QString desc = "Техника: выполняйте " + name.toLower() + " плавно. Рекомендуемое время подхода: " + QString::number(baseTime) + " сек.";

    currentExercise = SmartPointer<Exercise>(new Exercise(name, desc, baseTime));

    ui->exerciseDescription->setText(currentExercise->getDescription());
}

void MainWindow::onStartClicked() {
    if (!currentExercise.isNull() && !timer->isActive()) {
        timer->start(1000);
    }
}

void MainWindow::onStopClicked() {
    if (timer->isActive()) {
        timer->stop();
    }
    calculateProgress();
    elapsedSeconds = 0;
    updateTimerDisplay();
}

void MainWindow::onTimerTick() {
    elapsedSeconds++;
    updateTimerDisplay();

    if (elapsedSeconds >= currentExercise->getBaseTime()) {
        timer->stop();
        calculateProgress();
        elapsedSeconds = 0;
    }
}

void MainWindow::updateTimerDisplay() {
    int minutes = elapsedSeconds / 60;
    int seconds = elapsedSeconds % 60;
    QString timeText = QString("%1:%2")
                           .arg(minutes, 2, 10, QChar('0'))
                           .arg(seconds, 2, 10, QChar('0'));

    ui->timerDisplay->display(timeText);
}

void MainWindow::calculateProgress() {
    if (currentExercise.isNull()) return;

    int reps = ui->repsInput->value();

    int baseTime = currentExercise->getBaseTime();
    int targetTotalTime = baseTime * reps;

    int currentProgress = ui->goalProgress->value();

    double addedPercentage = (static_cast<double>(elapsedSeconds) / targetTotalTime) * 100.0;

    int newProgress = currentProgress + static_cast<int>(addedPercentage);
    if (newProgress > 100) {
        newProgress = 100;
    }

    ui->goalProgress->setValue(newProgress);
}

void MainWindow::resetProgress(){
    elapsedSeconds = 0;
    ui->goalProgress->setValue(elapsedSeconds);
}
