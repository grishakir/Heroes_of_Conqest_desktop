#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamewindow.h"
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPalette>
#include <QPushButton>
#include <QTimer>
#include <QWidget>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFont uiFont("VEGeorgianBrushCyrillicGreek", 26);
    this->setFont(uiFont);

    this->setFixedSize(QSize(1280, 720));
    QPixmap background(":/backgrounds/res/menu_background.jpg");
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, background);
    this->setPalette(palette);

    menu = menuBar()->addMenu("Герои Завоеваний");
    singlePlayerAction = new QAction("Одиночная игра", this);
    duelAction = new QAction("Дуэль", this);
    aboutAction = new QAction("Информация", this);
    quitAction = new QAction("Выход", this);

    menu->addAction(singlePlayerAction);
    menu->addAction(duelAction);
    menu->addAction(aboutAction);
    menu->addAction(quitAction);

    singlePlayerPushButton = new QPushButton("Одиночная игра", this);
    duelPushButton = new QPushButton("Дуэль", this);
    aboutPushButton = new QPushButton("Информация", this);
    quitPushButton = new QPushButton("Выход", this);

    connect(aboutPushButton, &QPushButton::clicked,
	this, &MainWindow::about);
    connect(quitPushButton, &QPushButton::clicked,
	qApp, &QApplication::quit);
    connect(duelPushButton, &QPushButton::clicked,
	this, &MainWindow::duel);
    connect(singlePlayerPushButton, &QPushButton::clicked,
	this, &MainWindow::singlePlayer);


    label = new QLabel;
    label->setText("Герои Завоеваний");
    label->setAlignment(Qt::AlignHCenter);


    layout = new QVBoxLayout(this);
    layout->addWidget(label);
    layout->addWidget(singlePlayerPushButton);
    layout->addWidget(duelPushButton);
    layout->addWidget(aboutPushButton);
    layout->addWidget(quitPushButton);
    this->centralWidget()->setLayout(layout);

    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);
    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete label;
    delete quitPushButton;
    delete aboutPushButton;
    delete duelPushButton;
     delete singlePlayerPushButton;
     delete menu;
     delete singlePlayerAction;
     delete duelAction;
     delete aboutAction;
     delete quitAction;
     delete layout;
}

void MainWindow::about()
{
    QMessageBox::information(this, "About", "Kirsanov M8O-110B-20\n.\
	This is a fighter game. There is one game class --- Warrior.\
	So, it is really strong man! Push buttons to kill your enemy \
	and save the United Kindom!");
}

void MainWindow::duel()
{
    gameWindow = new GameWindow();
    connect(gameWindow, &GameWindow::returnToMainWindow, 
	this, &QMainWindow::show);
    connect(gameWindow, &GameWindow::returnToMainWindow, 
	this, &MainWindow::delGameWindow);
    gameWindow->show();
    this->close();
}

void MainWindow::singlePlayer()
{
    singlePlayerWindow = new SinglePlayerWindow();
    singlePlayerWindow->show();
    this->close();
}

void MainWindow::delGameWindow()
{
   free(gameWindow);
}

