#include <QDebug>
#include "main_game_window.h"
#include "ui_maingamewindow.h"
#include "game_model.h"


MainGameWindow::MainGameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainGameWindow)
{
    ui->setupUi(this);

    // 关联信号槽
    connect(ui->actionStart, SIGNAL(triggered(bool)), this, SLOT(onStartGameClicked()));
    connect(ui->actionBasic, SIGNAL(triggered(bool)), this, SLOT(onLevelChooseClicked(QAction *)));

    // 创建游戏初始化游戏
    game = new GameModel;
    game->createGame();
}

MainGameWindow::~MainGameWindow()
{
    // 清理
    delete game;
    game = NULL;
    delete ui;
}

void MainGameWindow::onStartGameClicked()
{
    qDebug()<<"game started";
    game->createGame();
}

void MainGameWindow::onLevelChooseClicked(QAction *sender)
{
    if(sender == ui->actionBasic)
    {
        qDebug()<<"basic";
    }
    else if(sender == ui->actionMedium)
    {
        qDebug()<<"medium";
    }
}

void MainGameWindow::onQuitClicked()
{

}
