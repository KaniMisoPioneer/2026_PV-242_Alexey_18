#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "Exercise.h"
#include "SmartPointer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onExerciseChanged(int index);
    void onStartClicked();
    void onStopClicked();
    void onTimerTick();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    int elapsedSeconds;
    SmartPointer<Exercise> currentExercise;

    void loadExercises();
    void updateTimerDisplay();
    void calculateProgress();
    void resetProgress();
};
#endif // MAINWINDOW_H
