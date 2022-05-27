#include "game.h"

const int T = 10;
const int WIDTH = 1280;
const int HEIGHT = 800;
const char player1Src[50] = ":/art/liuhan.png";
const char player2Src[50] = ":/art/kuqi.png";
std::string int2str(int integer);

Game::Game(){
    setSceneRect(0,0,WIDTH,HEIGHT);
    winMode = HOME;

    /* Buttons */
    /* Start */
    QPushButton *startBtn = new QPushButton("Start");
    connect(startBtn, &QPushButton::clicked, this, &Game::start);
    startButton = (QGraphicsWidget *)addWidget(startBtn);
    startButton->setPos((WIDTH-100)/2,300);
    startButton->resize(100,50);
    /* Exit */
    QPushButton *quitBtn = new QPushButton("Quit");
    connect(quitBtn, &QPushButton::clicked, this, &Game::quit);
    quitButton = (QGraphicsWidget *)addWidget(quitBtn);
    quitButton->setPos((WIDTH-100)/2,400);
    quitButton->resize(100,50);

    /* Keyboard Control Flags Initializing */
    isPressingA = false;
    isPressingD = false;
    isPressingW = false;
    isPressingS = false;
    isPressingUp = false;
    isPressingLeft = false;
    isPressingDown = false;
    isPressingRight = false;

    /* Information Board Initializing */
    AIBoard = new QGraphicsTextItem;
    addItem(AIBoard);
    AIBoard->setPos(0,0);
    AIBoard->hide();
}

/* keyboard reading */
void Game::keyPressEvent(QKeyEvent *event){
    auto key = event->key();
    if(key == Qt::Key_W){
      isPressingW = true;
    }
    else if(key == Qt::Key_A){
      isPressingA = true;
    }
    else if(key == Qt::Key_S){
      isPressingS = true;
    }
    else if(key == Qt::Key_D){
      isPressingD = true;
    }
    else if(key == Qt::Key_Escape){
        if(winMode == GAMING)
            quit();
    }
    else if(key == Qt::Key_F1){
        if(AIBoardIsShow == false){
            showAIBoard();
        }
        else{
            hideAIBoard();
        }
    }
    else if(key == Qt::Key_Up){
      isPressingUp = true;
    }
    else if(key == Qt::Key_Down){
      isPressingDown = true;
    }
    else if(key == Qt::Key_Left){
      isPressingLeft = true;
    }
    else if(key == Qt::Key_Right){
      isPressingRight = true;
    }
}

void Game::keyReleaseEvent(QKeyEvent *event){
    auto key = event->key();
    if(key == Qt::Key_W){
        isPressingW = false;
    }
    else if(key == Qt::Key_A){
        isPressingA = false;
    }
    else if(key == Qt::Key_S){
        isPressingS = false;
    }
    else if(key == Qt::Key_D){
        isPressingD = false;
    }
    else if(key == Qt::Key_Up){
      isPressingUp = false;
    }
    else if(key == Qt::Key_Down){
      isPressingDown = false;
    }
    else if(key == Qt::Key_Left){
      isPressingLeft = false;
    }
    else if(key == Qt::Key_Right){
      isPressingRight = false;
    }
}

/* GameWindowsAction */

void Game::start(){
    /* GAMING Mode On */
    this->quitButton->hide();
    this->startButton->hide();
    this->winMode = GAMING;

    /* Initialize the clock */
    this->timer = new QTimer;
    connect(timer, &QTimer::timeout, this, &Game::updateGame);

    /* Player Init */
    player1 = new GamePlayer(WIDTH/4, HEIGHT/2, 60, player1Src, this);
    player2 = new GamePlayer(3*WIDTH/4, HEIGHT/2, 60, player2Src, this);

    this->globalTime = 0;
    this->timer->start(T);
}

void Game::pause(){
    this->timer->stop();
}

void Game::continueGame(){
    this->timer->start(T);
}

void Game::updateGame()
{
    globalTime += 1;
    if(globalTime < 0){
        // TODO:
        // Implement the Exception Function
    }
    QString str = QString("<font color = white>Interval: ")+QString(int2str(globalTime).c_str())+QString("</font>");
    AIBoard->setHtml(str);

    for(GameObject *ptr: this->gameObjects)
    {
        ptr->updateInGame();
    }
    for(list<GameObject *>::iterator it = gameObjects.begin();it!=gameObjects.end();)
    {
        if(!(*it)->isDead)
        {
            it++;
            continue;
        }
        list<GameObject *>::iterator it2 = gameObjects.erase(it);
        it = it2; // 遍历删除
    }

    player1->playerAct(parseKeyboard(1));
    player2->playerAct(parseKeyboard(2));
    player1->updateInGame();
    player2->updateInGame();
}

void Game::quit(){
    //Todo:
    //For keeping the consistency of our style, we should update this widget in the future.
    int res = QMessageBox::question(nullptr,"WARNING","Are you sure to exit？", QMessageBox::Yes|QMessageBox::No, QMessageBox::NoButton);
    if(res == QMessageBox::Yes){
        delete timer;
        exit(0);
    }
}

/* Information Board */
void Game::showAIBoard(){
    AIBoard->show();
    AIBoardIsShow = true;
}

void Game::hideAIBoard(){
    AIBoard->hide();
    AIBoardIsShow = false;
}

/* Parse Keyboard */
PlayerAction Game::parseKeyboard(int playerID){
    PlayerAction res = 0;
    if(playerID==1){
        if(isPressingW) res |= UP;
        if(isPressingA) res |= LEFT;
        if(isPressingS) res |= DOWN;
        if(isPressingD) res |= RIGHT;
    }
    else if(playerID==2){
        if(isPressingUp) res |= UP;
        if(isPressingLeft) res |= LEFT;
        if(isPressingDown) res |= DOWN;
        if(isPressingRight) res |= RIGHT;
    }
    return res;
}

/* Useful Functions */
std::string int2str(int integer){
    std::string res;
    while(integer){
        res.append(1,'0'+integer%10);
        integer /= 10;
    }
    reverse(res.begin(), res.end());
    return res;
}
