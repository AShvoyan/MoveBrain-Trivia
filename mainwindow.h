
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <json.hpp>

using json = nlohmann::json;


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int currentQuestionIndex = 0;
    json data;
    int point_count = 0;
    QTimer* timer;
    int remainingTime;

private slots:
    void on_playbutton_clicked();
    void on_playbutton_pressed();
    void onAnswerButtonClicked();
    void displayQuestion(int questionIndex);
    void onTimerExpired();
private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
