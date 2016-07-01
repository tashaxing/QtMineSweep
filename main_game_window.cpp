#include "main_game_window.h"
#include "ui_maingamewindow.h"
#include "game_model.h"

MainGameWindow::MainGameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainGameWindow)
{
    ui->setupUi(this);

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
    game->createGame();
}

void MainGameWindow::onLevelChooseClicked()
{

}

void MainGameWindow::onQuitClicked()
{

}
