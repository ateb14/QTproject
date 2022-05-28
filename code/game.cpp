#include "game.h"

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

//    /* Buttons */
//    /* Start */
//    QPushButton *startBtn = new QPushButton("Start");
//    connect(startBtn, &QPushButton::clicked, this, &Game::start);
//    startButton = (QGraphicsWidget *)addWidget(startBtn);
//    startButton->setPos((WIDTH-100)/2,300);
//    startButton->resize(100,50);
//    /* Exit */
//    QPushButton *quitBtn = new QPushButton("Quit");
//    connect(quitBtn, &QPushButton::clicked, this, &Game::quit);
//    quitButton = (QGraphicsWidget *)addWidget(quitBtn);
//    quitButton->setPos((WIDTH-100)/2,400);
//    quitButton->resize(100,50);

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
        if(winMode == GAMING){
            pause();
        }
        else if(winMode == MENU){
            continueGame();
        }
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

/* Parse Keyboard */
ActionSet Game::parseKeyboard(int playerID){
    ActionSet res;
    if(playerID==1){
        if(isPressingW) res.addAction(UP);
        if(isPressingA) res.addAction(LEFT);
        if(isPressingS) res.addAction(DOWN);
        if(isPressingD) res.addAction(RIGHT);
        // Todo
        // shooting parser
    }
    else if(playerID==2){
        if(isPressingUp) res.addAction(UP);
        if(isPressingLeft) res.addAction(LEFT);
        if(isPressingDown) res.addAction(DOWN);
        if(isPressingRight) res.addAction(RIGHT);
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

void Game::pause(){
    this->timer->stop();
    winMode = MENU;
    // Todo:
    // Menu
}

void Game::continueGame(){
    winMode = GAMING;
    this->timer->start(T);
}

void Game::updateGame()
{
    globalTime += 1;
    // Todo
    // call Function for players and ball->getDebugInfo() returns QString
    QString str = QString("<font color = white>Interval: ")+QString(int2str(globalTime).c_str())+QString("</font>");
    AIBoard->setHtml(str);

    player1->playerAct(parseKeyboard(1));
    player2->playerAct(parseKeyboard(2));

    // 物体之间碰撞
    for(list<GameObject *>::iterator it1 = gameObjects.begin(); it1!=gameObjects.end(); it1++)
    {
        list<GameObject *>::iterator it1_ = it1;
        for(list<GameObject *>::iterator it2 = ++it1_; it2!=gameObjects.end(); it2++)
        {
            GameObject *ptr1 = *it1, *ptr2 = *it2;
            if(ptr1->collideJudge(ptr2))
            {
                std::cout << "Colliding: " << ptr1->type << ptr2->type << endl;
                ptr1->collides(ptr2);
            }
        }
    }
    /* add new Objects */
    // call Function for all object->fetchGeneratedObject() returns vector<GameObject *>

    for(GameObject *ptr: this->gameObjects)
    {
        ptr->updateInGame();
    }

    /* ball position */
    // win()

    /* delete */
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

