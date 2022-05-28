#include "game.h"

// #define DEBUG

const int T = 10;
const int WIDTH = 1280;
const int HEIGHT = 800;
const char player1Src[] = ":/art/liuhan.png";
const char player2Src[] = ":/art/kuqi.png";
const char ballSrc[] = ":/art/football.png";
const char postSrc[] = ":/art/post.png";
std::string int2str(int integer);

Game::Game(){
    setSceneRect(0,0,WIDTH,HEIGHT);
    winMode = HOME;

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

    board = new GameBoard();
}

/* keyboard reading */
void Game::keyPressEvent(QKeyEvent *event){
    auto key = event->key();

    switch(key){
    case Qt::Key_W:isPressingW = true;break;
    case Qt::Key_A:isPressingA = true;break;
    case Qt::Key_S:isPressingS = true;break;
    case Qt::Key_D:isPressingD = true;break;
    case Qt::Key_Up:isPressingUp = true;break;
    case Qt::Key_Left:isPressingLeft = true;break;
    case Qt::Key_Down:isPressingDown = true;break;
    case Qt::Key_Right:isPressingRight = true;break;
    case Qt::Key_T:isPressingT = true;break;
    case Qt::Key_F:isPressingF = true;break;
    case Qt::Key_G:isPressingG = true;break;
    case Qt::Key_H:isPressingH = true;break;
    case Qt::Key_L:isPressingL = true;break;
    case Qt::Key_Less:isPressingLess = true;break;
    case Qt::Key_Greater:isPressingGreater = true;break;
    case Qt::Key_Question:isPressingQuestion = true;break;
    case Qt::Key_F1:{
        if(AIBoardIsShow == false){
            showAIBoard();
        }
        else{
            hideAIBoard();
        }
        break;
    }
    case Qt::Key_Escape:{
        if(winMode == GAMING){
            pause();
        }
        else if(winMode == MENU){
            continueGame();
        }
        break;
    }
    }
}

void Game::keyReleaseEvent(QKeyEvent *event){
    auto key = event->key();

    switch(key){
    case Qt::Key_W:isPressingW = false;break;
    case Qt::Key_A:isPressingA = false;break;
    case Qt::Key_S:isPressingS = false;break;
    case Qt::Key_D:isPressingD = false;break;
    case Qt::Key_Up:isPressingUp = false;break;
    case Qt::Key_Left:isPressingLeft = false;break;
    case Qt::Key_Down:isPressingDown = false;break;
    case Qt::Key_Right:isPressingRight = false;break;
    }
}

/* Parse Keyboard */
ActionSet Game::parseKeyboard(int playerID){
    ActionSet res;
    if(playerID==1){
        if(isPressingW) res.addAction(UP);
        if(isPressingA) res.addAction(LEFT);
        if(isPressingS) res.addAction(DOWN);
        if(isPressingD) res.addAction(RIGHT);
        if(isPressingT) res.addAction(UPSHOOT);
        if(isPressingF) res.addAction(LEFTSHOOT);
        if(isPressingG) res.addAction(DOWNSHOOT);
        if(isPressingH) res.addAction(RIGHTSHOOT);
        // Todo
        // shooting parser
    }
    else if(playerID==2){
        if(isPressingUp) res.addAction(UP);
        if(isPressingLeft) res.addAction(LEFT);
        if(isPressingDown) res.addAction(DOWN);
        if(isPressingRight) res.addAction(RIGHT);
        if(isPressingL) res.addAction(UPSHOOT);
        if(isPressingLess) res.addAction(LEFTSHOOT);
        if(isPressingGreater) res.addAction(DOWNSHOOT);
        if(isPressingQuestion) res.addAction(RIGHTSHOOT);
    }
    return res;
}

/* GameWindowsAction */

void Game::start(){
    /* GAMING Mode On */
//    this->quitButton->hide();
//    this->startButton->hide();
    this->winMode = GAMING;

    /* Initialize the clock */
    this->timer = new QTimer;
    connect(timer, &QTimer::timeout, this, &Game::updateGame);

    /* Player Init */
    player1 = new GamePlayer(WIDTH/4, HEIGHT/2, 30, player1Src, this);
    player2 = new GamePlayer(3*WIDTH/4, HEIGHT/2, 30, player2Src, this);
    /* ball Init */
    GameBall *ball = new GameBall(WIDTH/2, HEIGHT/2, 20, 1, ballSrc, this);
    ballptr = ball;
    GameObstacle *post[4]; // 球门柱
    post[0] = new GameObstacle(70, HEIGHT/2-100, 10, postSrc, this);
    post[1] = new GameObstacle(70, HEIGHT/2+100, 10, postSrc, this);
    post[2] = new GameObstacle(WIDTH-70, HEIGHT/2-100, 10, postSrc, this);
    post[3] = new GameObstacle(WIDTH-70, HEIGHT/2+100, 10, postSrc, this);

    this->gameObjects.push_back(player1);
    this->gameObjects.push_back(player2);
    this->gameObjects.push_back(ball);
    for(int i = 0;i<4;i++) this->gameObjects.push_back(post[i]);

    this->globalTime = 0;
    this->timer->start(T);
}

void Game::endGame(){
    // Todo
    // implement this function
}

void Game::pause(int ms){
    /* for menu */
    if(ms <= 0){
        this->timer->stop();
        winMode = MENU;
    }
    /* for game */
    else if(ms > 0){
        this->timer->stop();
        QTimer::singleShot(ms, this, &continueGame);
    }
    // Todo:
    // Menu
}

void Game::continueGame(){
    winMode = GAMING;
    this->timer->start(T);
}

/* Update */

void Game::collisionChecker(){
    for(list<GameObject *>::iterator it1 = gameObjects.begin(); it1!=gameObjects.end(); it1++)
    {
        list<GameObject *>::iterator it1_ = it1;
        for(list<GameObject *>::iterator it2 = ++it1_; it2!=gameObjects.end(); it2++)
        {
            GameObject *ptr1 = *it1, *ptr2 = *it2;
            if(ptr1->collideJudge(ptr2))
            {
#ifdef DEBUG
                std::cout << "Colliding: " << ptr1->type << ptr2->type << endl;
#endif
                ptr1->collides(ptr2);
            }
        }
    }
}

void Game::deadChecker(){
    for(list<GameObject *>::iterator it = gameObjects.begin(); it!=gameObjects.end(); )
    {
        if(!(*it)->isDead)
        {
            it++;
            continue;
        }
        list<GameObject *>::iterator it2 = gameObjects.erase(it);
        it = it2; // 遍历删除
    }
}

void Game::ballChecker(){
    auto x = ballptr->centerX(), y = ballptr->centerY();
    bool player1WinFlag = false, player2WinFlag = false;
    /* player1 score */
    if(x>=0 && x<70 && y>HEIGHT/2-100 && y<HEIGHT/2+100){
        player1WinFlag = true;
    }
    /* player2 score */
    else if(x>=WIDTH-70 && x<=WIDTH && y>HEIGHT/2-100 && y<HEIGHT/2+100){
        player2WinFlag = true;
    }
    if(player1WinFlag || player2WinFlag){
        pause(10);
        Sleep(2000);
        player1->setVelocity(0,0);
        player2->setVelocity(0,0);
        ballptr->setVelocity(0,0);
        player1->setPos(WIDTH/4-player1->radius, HEIGHT/2-player1->radius);
        player2->setPos(3*WIDTH/4-player2->radius, HEIGHT/2-player2->radius);
        ballptr->setPos(WIDTH/2-ballptr->radius, HEIGHT/2-ballptr->radius);
    }
}

void Game::boardChecker(){
    // Todo
    // call Function for players and ball->getDebugInfo() returns QString
    QString str = QString("<font color = white>Interval: ")+QString(int2str(globalTime).c_str());
    str += QString("<br>player1 x: ") + QString(int2str(player1->centerX()).c_str())+QString(" y:")+QString(int2str(player1->centerY()).c_str());
    str += QString("<br>player2 x: ") + QString(int2str(player2->centerX()).c_str())+QString(" y:")+QString(int2str(player2->centerY()).c_str());
    str += QString("<br>ball x: ") + QString(int2str(ballptr->centerX()).c_str())+QString(" y:")+QString(int2str(ballptr->centerY()).c_str());
    str += QString("</font>");
    AIBoard->setHtml(str);
}

void Game::updateGame()
{
    globalTime += 1;
    // Todo
    // call Function for players and ball->getDebugInfo() returns QString
    boardChecker();

    player1->playerAct(parseKeyboard(1));
    player2->playerAct(parseKeyboard(2));

    // 物体之间碰撞
    collisionChecker();

    /* add new Objects */
    // call Function for all object->fetchGeneratedObject() returns vector<GameObject *>

    /* Update Objects in the scene */
    for(GameObject *ptr: this->gameObjects)
    {
        ptr->updateInGame();
    }

    /* ball position */
    ballChecker();

    /* delete */
    deadChecker();
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

GameBoard *Game::getBoard(){
    return board;
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

