#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include "main_game_window.h"
#include "ui_maingamewindow.h"
#include "game_model.h"

// ---------全局变量------------ //
const int blockSize = 20;
const int offsetX = 5; // 横向边距
const int offsetY = 5; // 纵向边距
const int spaceY = 70; // 上方空白用于绘制记分板

// ------------------------------//

MainGameWindow::MainGameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainGameWindow)
{
    ui->setupUi(this);

    // 关联信号槽
    connect(ui->actionStart, SIGNAL(triggered(bool)), this, SLOT(onStartGameClicked()));
    connect(ui->actionBasic, SIGNAL(triggered(bool)), this, SLOT(onLevelChooseClicked()));
    connect(ui->actionMedium, SIGNAL(triggered(bool)), this, SLOT(onLevelChooseClicked()));
    connect(ui->actionHard, SIGNAL(triggered(bool)), this, SLOT(onLevelChooseClicked()));
    connect(ui->actionQuit, SIGNAL(triggered(bool)), this, SLOT(onQuitClicked()));

    // 创建游戏初始化游戏
    game = new GameModel;
    game->createGame(15, 20, 100);

    // 定义窗口大小(必须放在connect后面，该函数设置后大小不可变动)
    setFixedSize(game->mCol * blockSize + offsetX * 2, game->mRow * blockSize + offsetY * 2 + spaceY);

}

MainGameWindow::~MainGameWindow()
{
    // 清理
    delete game;
    game = NULL;
    delete ui;
}

void MainGameWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap bmpBlocks(":/res/blocks.bmp");
    QPixmap bmpFaces(":/res/faces.bmp");
    QPixmap bmpFrame(":/res/frame.bmp");
    QPixmap bmpTimenumber(":/res/timenumber.bmp");

    // 绘制雷区
    for(int i = 0; i < game->mRow; i++)
    {
        for(int j = 0; j < game->mCol; j++)
        {
            switch(game->gameMap[i][j].curState)
            {
            // 根据不同的方块状态绘制，算出在bmp中的偏移量
            case UN_DIG:
                painter.drawPixmap(j * blockSize + offsetX, i * blockSize + offsetY + spaceY , bmpBlocks, blockSize * 10, 0, blockSize, blockSize);
                break;
            case DIGGED:
                painter.drawPixmap(j * blockSize + offsetX, i * blockSize + offsetY + spaceY, bmpBlocks, blockSize * game->gameMap[i][j].valueFlag, 0, blockSize, blockSize);
                break;
            case MARKED:
                painter.drawPixmap(j * blockSize + offsetX, i * blockSize + offsetY + spaceY, bmpBlocks, blockSize * 11, 0, blockSize, blockSize);
                break;
            case BOMB:
                painter.drawPixmap(j * blockSize + offsetX, i * blockSize + offsetY + spaceY, bmpBlocks, blockSize * 9, 0, blockSize, blockSize);
                break;
            case WRONG_BOMB:
                if(game->gameState == PLAYING || game->gameState == FAULT)
                {
                    // 如果还在游戏中就显示旗子
                    painter.drawPixmap(j * blockSize + offsetX, i * blockSize + offsetY + spaceY, bmpBlocks, blockSize * 11, 0, blockSize, blockSize);
                }
                else if(game->gameState == OVER)
                {
                    // 如果游戏已经结束，就显示标错了
                    painter.drawPixmap(j * blockSize + offsetX, i * blockSize + offsetY + spaceY, bmpBlocks, blockSize * 10, 0, blockSize, blockSize);
                }
                break;
            default:
                break;
            }
        }
    }
}

void MainGameWindow::mousePressEvent(QMouseEvent *event)
{
    // 获得点击坐标
    int px = event->x() - offsetX;
    int py = event->y() - offsetY - spaceY;
    // 换算成方格索引
    int row = py / blockSize;
    int col = px / blockSize;
    // 根据不同情况响应
    switch(event->button())
    {
    case Qt::LeftButton:
        game->digMine(row, col);
        update(); // 每次点击都要重绘
        break;
    case Qt::RightButton:
        game->markMine(row, col);
        update();
        break;
    default:
        break;
    }
}

void MainGameWindow::onStartGameClicked()
{
    qDebug()<<"game started";
    game->createGame();
}

void MainGameWindow::onLevelChooseClicked()
{
    QAction *actionSender = (QAction *)dynamic_cast<QAction *>(sender());
    if(actionSender == ui->actionBasic)
    {
        qDebug() << "basic";
    }
    else if(actionSender == ui->actionMedium)
    {
        qDebug() << "medium";
    }
    else if(actionSender == ui->actionHard)
    {
        qDebug() << "hard";
    }
}

void MainGameWindow::onQuitClicked()
{
    QCoreApplication::quit();
}
