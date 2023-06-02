#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "json.hpp" //nlohmann json
#include <string>
#include <fstream>
#include <QJsonObject>
#include <QJsonDocument>
#include <QString>
#include <QLabel>
#include <QWidget>
#include <QPixmap> //для изображений
#include <QLabel>
#include <QMovie> //для гифок
#include <QPushButton>
#include <QRandomGenerator> //для рандомных чисел
#include <QTimer>
#include <windows.h>

using json = nlohmann::json;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // установка фона
    QPixmap pix;
    pix.load(":/new/img/C:/Users/Ashot/Desktop/MoveBrain/background.jpg");
    ui->label->setPixmap(pix);
    ui->label->setScaledContents(true);

    this->setFixedSize(QSize(1024, 576)); //установка фиксированного размера окна

    ui->question->setVisible(false); // чтобы поле с вопросом изначально было невидимым

    //для полей ответов
    ui->answerbutton->setVisible(false);
    ui->answerbutton_2->setVisible(false);
    ui->answerbutton_3->setVisible(false);
    ui->answerbutton_4->setVisible(false);
    ui->question_name->setVisible(false);
    ui->question_num->setVisible(false);
    ui->pointdisplay->setVisible(false);
    ui->points->setVisible(false);
    ui->timerlabel->setVisible(false);
    ui->timetext->setVisible(false);


    connect(ui->answerbutton, &QPushButton::clicked, this, &MainWindow::onAnswerButtonClicked);
    connect(ui->answerbutton_2, &QPushButton::clicked, this, &MainWindow::onAnswerButtonClicked);
    connect(ui->answerbutton_3, &QPushButton::clicked, this, &MainWindow::onAnswerButtonClicked);
    connect(ui->answerbutton_4, &QPushButton::clicked, this, &MainWindow::onAnswerButtonClicked);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimerExpired()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_playbutton_clicked(){}

//после нажатия на кнопку ИГРАТЬ
void MainWindow::on_playbutton_pressed()
{

    displayQuestion(0);

    QString start_points = QString::number(0);
    ui->points->setText(start_points);


    //закрыть видимость кнопок играть и темы
    ui->playbutton->setVisible(false);
    ui->comboBox->setVisible(false);
    ui->gamemode->setVisible(false);

}


void MainWindow::onTimerExpired()
{
    remainingTime--;

    if (remainingTime == 0) {
        // Timer expired, go to the next question
        onAnswerButtonClicked();
    }
    else {
        ui->timerlabel->setText(QString::number(remainingTime));
    }
}

void MainWindow::displayQuestion(int questionIndex)
{

    ui->question->setVisible(true);
    ui->answerbutton->setVisible(true);
    ui->answerbutton_2->setVisible(true);
    ui->answerbutton_3->setVisible(true);
    ui->answerbutton_4->setVisible(true);
    ui->question_name->setVisible(true);
    ui->question_num->setVisible(true);
    ui->pointdisplay->setVisible(true);
    ui->points->setVisible(true);
    ui->timerlabel->setVisible(true);
    ui->timetext->setVisible(true);

    //таймер
    if(ui->gamemode->currentIndex() == 0) {
        remainingTime = 30;
    }
    else {
        remainingTime = 5;
    }
    timer->start(1000);

    if (ui->comboBox->currentIndex() == 0) {
        std::ifstream rand("C:\\Users\\Ashot\\Desktop\\MoveBrain\\QuestionsJSON\\questions_random_eng.json");
        data = json::parse(rand);
    }
    else if(ui->comboBox->currentIndex() == 1) {
        std::ifstream geo("C:\\Users\\Ashot\\Desktop\\MoveBrain\\QuestionsJSON\\questions_geography.json");
        data = json::parse(geo);
    }
    else if(ui->comboBox->currentIndex() == 2) {
        std::ifstream his("C:\\Users\\Ashot\\Desktop\\MoveBrain\\QuestionsJSON\\questions_history.json");
        data = json::parse(his);
    }
    else if(ui->comboBox->currentIndex() == 3) {
        std::ifstream pol("C:\\Users\\Ashot\\Desktop\\MoveBrain\\QuestionsJSON\\questions_politics.json");
        data = json::parse(pol);
    }

    if (questionIndex >= 0 && questionIndex < data.size())
    {
        std::string question = data[questionIndex]["question"];
        QString qQuestion = QString::fromStdString(question);
        ui->question->setText(qQuestion);
        ui->question->setWordWrap(true);

        QString qnum = QString::number(currentQuestionIndex+1);
        ui->question_num->setText(qnum);

        std::string answer1 = data[questionIndex]["options"][0];
        QString qAnswer1 = QString::fromStdString(answer1);
        ui->answerbutton->setText(qAnswer1);
        std::string answer2 = data[questionIndex]["options"][1];
        QString qAnswer2 = QString::fromStdString(answer2);
        ui->answerbutton_2->setText(qAnswer2);
        std::string answer3 = data[questionIndex]["options"][2];
        QString qAnswer3 = QString::fromStdString(answer3);
        ui->answerbutton_3->setText(qAnswer3);
        std::string answer4 = data[questionIndex]["options"][3];
        QString qAnswer4 = QString::fromStdString(answer4);
        ui->answerbutton_4->setText(qAnswer4);
    }
}

void MainWindow::onAnswerButtonClicked() {

    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    int clickedButtonIndex = -1;

    if (clickedButton == ui->answerbutton)
        clickedButtonIndex = 0;
    else if (clickedButton == ui->answerbutton_2)
        clickedButtonIndex = 1;
    else if (clickedButton == ui->answerbutton_3)
        clickedButtonIndex = 2;
    else if (clickedButton == ui->answerbutton_4)
        clickedButtonIndex = 3;

    QString points = QString::number(point_count);
    // Check if the clicked answer is correct
    if (clickedButtonIndex == data[currentQuestionIndex]["answer"])
    {
        // Increment the point_count variable
        point_count++;
        ui->points->setText(points);
    }

    if (currentQuestionIndex >= 9) {

        // Reset the current question index to 0
        currentQuestionIndex = 0;
        point_count = 0;
        ui->points->setText(points);

        // Hide the question and answer buttons
        ui->question->setVisible(false);
        ui->answerbutton->setVisible(false);
        ui->answerbutton_2->setVisible(false);
        ui->answerbutton_3->setVisible(false);
        ui->answerbutton_4->setVisible(false);
        ui->question_name->setVisible(false);
        ui->question_num->setVisible(false);
        ui->pointdisplay->setVisible(false);
        ui->points->setVisible(false);
        ui->timerlabel->setVisible(false);
        ui->timetext->setVisible(false);

        timer->stop();

        // Show the play button again to return to the menu screen
        ui->comboBox->setVisible(true);
        ui->playbutton->setVisible(true);
        ui->gamemode->setVisible(true);

    } else {
        // Increment the current question index for the next iteration
        currentQuestionIndex++;

        // Generate a random question index for the next question
        QRandomGenerator randomGenerator;
        randomGenerator.seed(static_cast<quint64>(QDateTime::currentMSecsSinceEpoch()));
        int randomIndex = randomGenerator.bounded(data.size());

        // Display the next question and answers
        displayQuestion(randomIndex);
    }
}
