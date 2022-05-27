#include "game.h"

const int T = 20;
const int WIDTH = 1280;
const int HEIGHT = 800;
const char player1Src[50] = ":/art/liuhan.png";
const char player2Src[50] = ":/art/kuqi.png";
std::string int2str(int integer);

game::game(){
    setSceneRect(0,0,WIDTH,HEIGHT);
    winMode = HOME;

    /* Buttons */
    /* Start */
    QPushButton *startBtn = new QPushButton("Start");
    connect(startBtn, &QPushButton::clicked, this, &game::start);
    startButton = (QGraphicsWidget *)addWidget(startBtn);
    startButton->setPos((WIDTH-100)/2,300);
    startButton->resize(100,50);
    /* Exit */
    QPushButton *quitBtn = new QPushButton("Quit");
    connect(quitBtn, &QPushButton::clicked, this, &game::quit);
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
void game::keyPressEvent(QKeyEvent *event){
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

void game::keyReleaseEvent(QKeyEvent *event){
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

/* Clock */

void game::updateTime(){
    globalTime += 1;
    if(globalTime < 0){
        // TODO:
        // Implement the Exception Function
    }
    QString str = QString("<font color = white>Interval: ")+QString(int2str(globalTime).c_str())+QString("</font>");
    AIBoard->setHtml(str);
}

/* Keyboard */
void game::sendKeyboardMsg(){
    int status = 0;
    if(isPressingW) ADDSTATUS(W,status);
    if(isPressingA) ADDSTATUS(A,status);
    if(isPressingS) ADDSTATUS(S,status);
    if(isPressingD) ADDSTATUS(D,status);
    if(isPressingUp) ADDSTATUS(UP,status);
    if(isPressingDown) ADDSTATUS(DOWN,status);
    if(isPressingLeft) ADDSTATUS(LEFT,status);
    if(isPressingRight) ADDSTATUS(RIGHT,status);
    if(winMode == GAMING){
        int player1Mask = ~0xF0, player2Mask = ~0xF;
        player1->keyboardMove(status & player1Mask);
        player2->keyboardMove(status & player2Mask);
    }
}

/* GameWindowsAction */

void game::start(){
    /* GAMING Mode On */
    this->quitButton->hide();
    this->startButton->hide();
    this->winMode = GAMING;

    /* Initialize the clock */
    this->timer = new QTimer;
    connect(timer, &QTimer::timeout, this, &game::updateTime);

    /* Player Init */
    player1 = new player(WIDTH/4, HEIGHT/2, 65, 65, player1Src, this);
    connect(timer, &QTimer::timeout, this, &game::sendKeyboardMsg);

    player2 = new player(3*WIDTH/4, HEIGHT/2, 50, 50, player2Src, this);
    connect(timer, &QTimer::timeout, this, &game::sendKeyboardMsg);

    this->globalTime = 0;
    this->timer->start(T);
}

void game::pause(){
    this->timer->stop();
}

void game::continueGame(){
    this->timer->start(T);
}

void game::quit(){
    //Todo:
    //For keeping the consistency of our style, we should update this widget in the future.
    int res = QMessageBox::question(nullptr,"WARNING","Are you sure to exit？", QMessageBox::Yes|QMessageBox::No, QMessageBox::NoButton);
    if(res == QMessageBox::Yes){
        delete timer;
        exit(0);
    }
}

/* Information Board */
void game::showAIBoard(){
    AIBoard->show();
    AIBoardIsShow = true;
}

void game::hideAIBoard(){
    AIBoard->hide();
    AIBoardIsShow = false;
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


