#include "game.h"
#include "config.h"

// #define DEBUG

const QPixmap *player1Pixmap, *player2Pixmap,
              *ballPixmap, *postPixmap, *bulletPixmap[PLAYER_TYPES], *SSBulletPixmap[PLAYER_TYPES];

int Game::winFreeTime = -1;
bool Game::reviewMode = true;
std::string int2str(int integer);

Game::Game(){
    setSceneRect(0,0,WIDTH,HEIGHT);
    winMode = HOME;
    /* Music Player Init */
    cheersPlaylist = new QMediaPlaylist;
    cheersPlaylist->addMedia(QUrl(cheers1Src));
    cheersPlaylist->addMedia(QUrl(cheers2Src));
    cheersPlaylist->setPlaybackMode(QMediaPlaylist::Random);
    cheersPlayer = new QMediaPlayer;
    cheersPlayer->setPlaylist(cheersPlaylist);

    backgroundPlaylist = new QMediaPlaylist;
    backgroundPlaylist->addMedia(QUrl::fromLocalFile(backgroundMusic1Src));
    backgroundPlaylist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    backgroundPlayer = new QMediaPlayer;
    backgroundPlayer->setVolume(70);
    backgroundPlayer->setPlaylist(backgroundPlaylist);

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
        case Qt::Key_Comma:isPressingComma = true;break;
        case Qt::Key_Period:isPressingPeriod = true;break;
        case Qt::Key_Slash:isPressingDivision = true;break;
        case Qt::Key_E:isPressingE = true;break;
        case Qt::Key_Semicolon:isPressingSemi=true;break;
    case Qt::Key_F12: boardInfo.player1BigScore=3;break;
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
                emit gameispause();
            }
            else if(winMode == MENU && !isGameOver){
                continueGame();
                emit gamecontinue();
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
        case Qt::Key_T:isPressingT = false;break;
        case Qt::Key_F:isPressingF = false;break;
        case Qt::Key_G:isPressingG = false;break;
        case Qt::Key_H:isPressingH = false;break;
        case Qt::Key_L:isPressingL = false;break;
        case Qt::Key_Comma:isPressingComma = false;break;
        case Qt::Key_Period:isPressingPeriod = false;break;
        case Qt::Key_Slash:isPressingDivision = false;break;
        case Qt::Key_E:isPressingE = false;break;
        case Qt::Key_Semicolon:isPressingSemi=false;break;
    }
}

/* Parse Keyboard */
ActionSet Game::parseKeyboard(int playerID){
    ActionSet res;
    if(playerID==1 && player1DeadTime < 0){
        if(isPressingW) res.addAction(UP);
        if(isPressingA) res.addAction(LEFT);
        if(isPressingS) res.addAction(DOWN);
        if(isPressingD) res.addAction(RIGHT);
        if(isPressingT && winFreeTime < 0) res.addAction(UPSHOOT);
        if(isPressingF && winFreeTime < 0) res.addAction(LEFTSHOOT);
        if(isPressingG && winFreeTime < 0) res.addAction(DOWNSHOOT);
        if(isPressingH && winFreeTime < 0) res.addAction(RIGHTSHOOT);
        if(isPressingE && winFreeTime < 0) res.addAction(SKILL);
        // Todo
        // shooting parser
    }
    else if(playerID==2 && player2DeadTime < 0){
        if(isPressingUp) res.addAction(UP);
        if(isPressingLeft) res.addAction(LEFT);
        if(isPressingDown) res.addAction(DOWN);
        if(isPressingRight) res.addAction(RIGHT);
        if(isPressingL && winFreeTime < 0) res.addAction(UPSHOOT);
        if(isPressingComma && winFreeTime < 0) res.addAction(LEFTSHOOT);
        if(isPressingPeriod && winFreeTime < 0) res.addAction(DOWNSHOOT);
        if(isPressingDivision && winFreeTime < 0) res.addAction(RIGHTSHOOT);
        if(isPressingSemi && winFreeTime < 0) res.addAction(SKILL);
    }
    return res;
}
/* Generate Player */
void Game::createPlayers(PlayerType type1, PlayerType type2){
    switch (type1){
    case SANTA:
        player1Pixmap = new QPixmap(santaSrc);
        player1 = new SantaClaus(WIDTH/4, HEIGHT/2, player1Pixmap, this, &gameObjects);
        break;
    case LOVEMAN:
        player1Pixmap = new QPixmap(loveSrc);
        player1 = new LovingMan(WIDTH/4, HEIGHT/2, player1Pixmap, this, &gameObjects);break;
    case GUOSHEN:
        player1Pixmap = new QPixmap(glsSrc);
        player1 = new GuoShen(WIDTH/4, HEIGHT/2, player1Pixmap, this, &gameObjects);
        break;
    case ANGRYBRO:
        player1Pixmap = new QPixmap(angrySrc);
        player1 = new AngryBrother(WIDTH/4, HEIGHT/2, player1Pixmap, this, &gameObjects);
        break;
    }
    switch (type2){
    case SANTA:
        player2Pixmap = new QPixmap(santaSrc);
        player2 = new SantaClaus(3*WIDTH/4, HEIGHT/2, player2Pixmap, this, &gameObjects);
        break;
    case LOVEMAN:
        player2Pixmap = new QPixmap(loveSrc);
        player2 = new LovingMan(3*WIDTH/4, HEIGHT/2, player2Pixmap, this, &gameObjects);
        break;
    case GUOSHEN:
        player2Pixmap = new QPixmap(glsSrc);
        player2 = new GuoShen(3*WIDTH/4, HEIGHT/2, player2Pixmap, this, &gameObjects);
        break;
    case ANGRYBRO:
        player2Pixmap = new QPixmap(angrySrc);
        player2 = new AngryBrother(3*WIDTH/4, HEIGHT/2, player2Pixmap, this, &gameObjects);
        break;
    }
    player1->setOpponent(player2);
    player2->setOpponent(player1);
}
/* GameWindowsAction */
void Game::setGlobalVars(PlayerType player1Type_, PlayerType player2Type_, GameFormat gameFormat_, PlayerSpeed playerSpeed_, bool enemyMode){
    gameSettings.player1Type = player1Type_;
    gameSettings.player2Type = player2Type_;
    gameSettings.gameFormat = gameFormat_;
    gameSettings.playerSpeed = playerSpeed_;
    gameSettings.enemyMode = enemyMode;
}

void Game::setTimerT(int T_){
    this->timer->stop();
    T = T_;
    this->timer->start(T);
}

void Game::start(bool reviewMode){
    Game::reviewMode = reviewMode;
    emit refreshBoard(gameSettings.player1Type, gameSettings.player2Type);
    /* GAMING Mode On */
    this->winMode = GAMING;
    isGameOver = false;
    winFreeTime = -1;

    /* Initialize the clock */
    T = defaultT;
    this->timer = new QTimer;
    connect(timer, &QTimer::timeout, this, &Game::updateGame);

    /* Keyboard Control Flags Initializing */
    isPressingA = false;
    isPressingD = false;
    isPressingW = false;
    isPressingS = false;
    isPressingUp = false;
    isPressingLeft = false;
    isPressingDown = false;
    isPressingRight = false;
    isPressingT = false;
    isPressingF = false;
    isPressingG = false;
    isPressingH = false;
    isPressingL = false;
    isPressingComma = false;
    isPressingPeriod = false;
    isPressingDivision = false;
    isPressingE = false;
    isPressingSemi = false;

    /* GameBoard Init */
    boardInfo.player1BigScore = 0;
    boardInfo.player1SmallScore = 0;
    boardInfo.player2BigScore = 0;
    boardInfo.player2SmallScore = 0;
    boardInfo.player1Health = PLAYER_HEALTH;
    boardInfo.player2Health = PLAYER_HEALTH;
    boardInfo.player1Power = 0;
    boardInfo.player2Power = 0;
    memset(boardInfo.player1Buff,false,BUFF_TYPE_CNT);
    memset(boardInfo.player2Buff,false,BUFF_TYPE_CNT);


    /* Resources Init */
    ballPixmap = new QPixmap(ballSrc);
    postPixmap = new QPixmap(postSrc);
    for(int i = 0;i<PLAYER_TYPES;i++) bulletPixmap[i] = new QPixmap(bulletSrc[i]);
    for(int i = 0;i<PLAYER_TYPES;i++) SSBulletPixmap[i] = new QPixmap(SSBulletSrc[i]);

    /* Review Mode */
    infoReader = 0;
    gameInfos.clear();
    if(Game::reviewMode == true){
        ifstream inFile(recSrc.c_str(),ios::in|ios::binary);
        if(!inFile){
            std::cout << "Failed" << std::endl;
            isGameOver = true;
            emit gameOver(1,reviewMode);
        }
        else{
            inFile.read((char *) & gameSettings, sizeof(gameSettings));
            gameInfo info;
            std::cout << gameSettings.player1Type << gameSettings.player2Type << gameSettings.gameFormat << std::endl;
            while(inFile.read((char *) & info, sizeof(info))){
                gameInfos.push_back(info);
            }
            inFile.close();
        }
    }

    /* Player Init */
    player1DeadTime = -1;
    player2DeadTime = -1;
    createPlayers(gameSettings.player1Type, gameSettings.player2Type);
    /* ball Init */
    GameBall *ball = new GameBall(WIDTH/2, HEIGHT/2, ballPixmap, this);
    ballptr = ball;
    GameObstacle *post[8]; // 球门柱
    post[0] = new GameObstacle(70, HEIGHT/2-100, 10, postPixmap, this);
    post[1] = new GameObstacle(70, HEIGHT/2+100, 10, postPixmap, this);
    post[2] = new GameObstacle(WIDTH-70, HEIGHT/2-100, 10, postPixmap, this);
    post[3] = new GameObstacle(WIDTH-70, HEIGHT/2+100, 10, postPixmap, this);
    post[4] = new GameObstacle(35, HEIGHT/2-100, 10, postPixmap, this);
    post[5] = new GameObstacle(35, HEIGHT/2+100, 10, postPixmap, this);
    post[6] = new GameObstacle(WIDTH-35, HEIGHT/2-100, 10, postPixmap, this);
    post[7] = new GameObstacle(WIDTH-35, HEIGHT/2+100, 10, postPixmap, this);

    this->gameObjects.push_back(player1);
    this->gameObjects.push_back(player2);
    this->gameObjects.push_back(ball);
    for(int i = 0;i<8;i++) this->gameObjects.push_back(post[i]);

    this->globalTime = 0;
    this->timer->start(T);
    /* Music! */
    backgroundPlayer->play();
}

void Game::endGame(){
    winMode = HOME;
    backgroundPlayer->stop();
    cheersPlayer->stop();
    delete this->timer;
    for(GameObject * it:this->gameObjects){
        delete it;
    }
    gameObjects.clear();
}

void Game::setRecSrc(const QString & str){
    string name = "./record/"+str.toStdString()+".dat";
    recSrc = name;
    std::cout << recSrc << std::endl;
}

void Game::saveRecord(){
    QDateTime timeCurrent = QDateTime::currentDateTime();
    QString time = timeCurrent.toString("yy-MM-dd_hh-mm-ss");
    string dst = "./record/"+time.toStdString()+".dat";
    if(Game::reviewMode == false){
        ofstream outFile(dst.c_str(),ios::out|ios::binary);
        // Save Global Settings
        outFile.write((char *)&gameSettings,sizeof(gameSettings));
        int len = gameInfos.size();
        // Save Control Information
        for(int i=0;i<len;++i){
            outFile.write((char *)&gameInfos[i], sizeof(gameInfos[i]));
        }
        outFile.close();
        gameInfos.clear();

        QString dirTemp = "./record";
        QDir dirt(dirTemp);

        QStringList filterst;
        filterst << QString("*.dat") << QString("*.DAT");
        QFileInfoList file_list = dirt.entryInfoList(filterst, QDir::Files | QDir::NoSymLinks);
        dirTemp = "./record/";
        QString suffix = ".dat";

        if(file_list.size()>=5){
            int len = file_list.size();
            vector<QString> tmp;
            for(int i=0;i<len;++i){
                tmp.push_back(file_list[i].baseName());
            }
            sort(tmp.begin(), tmp.end());
            for(int i=0;i<len-5;++i){
                QFile file;
                file.setFileName(dirTemp+tmp[i]+suffix);
                file.remove();
            }
        }
    }
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
}

void Game::continueGame(){
    winMode = GAMING;
    this->timer->start(T);
}

/* Update */

void Game::collisionCheck(){
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

void Game::deadCheck(){
    for(list<GameObject *>::iterator it = gameObjects.begin(); it!=gameObjects.end(); )
    {
        if(!(*it)->isDead)
        {
            it++;
            continue;
        }
        delete *it;
        list<GameObject *>::iterator it2 = gameObjects.erase(it);
        it = it2; // 遍历删除
    }
}

void Game::goalCheck(){
    if(Game::winFreeTime < 0){
        auto x = ballptr->centerX(), y = ballptr->centerY();
        bool player1WinFlag = false, player2WinFlag = false;
        /* player1 score */
        if(x>=0 && x<70 && y>HEIGHT/2-100 && y<HEIGHT/2+100){
            player2WinFlag = true;
            boardInfo.player2SmallScore += 1;
            emit updateSmallScore(2);
        }
        /* player2 score */
        else if(x>=WIDTH-70 && x<=WIDTH && y>HEIGHT/2-100 && y<HEIGHT/2+100){
            player1WinFlag = true;
            boardInfo.player1SmallScore += 1;
            emit updateSmallScore(1);
        }
        if(player1WinFlag || player2WinFlag){
            winFreeTime = 600;
            cheersPlayer->setVolume(100);
            cheersPlayer->play();
        }
    }
    else if(Game::winFreeTime>0){
        winFreeTime -= 1;
    }
    else if(Game::winFreeTime == 0){
        winFreeTime = -1;
        cheersPlayer->stop();

        if(boardInfo.player1SmallScore == MAX_SMALL_SCORE || boardInfo.player2SmallScore == MAX_SMALL_SCORE){
            if(boardInfo.player1SmallScore == MAX_SMALL_SCORE){
                emit updateBigScore(1);
                boardInfo.player1BigScore += 1;
            }
            else{
                emit updateBigScore(2);
                boardInfo.player2BigScore += 1;
            }
            boardInfo.player1SmallScore = 0;
            boardInfo.player2SmallScore = 0;
            emit refreshBoard(gameSettings.player1Type, gameSettings.player2Type);
        }
        player1->reset(WIDTH/4, HEIGHT/2);
        player2->reset(3*WIDTH/4, HEIGHT/2);
        ballptr->setVelocity(0,0);
        ballptr->setPos(WIDTH/2-ballptr->radius, HEIGHT/2-ballptr->radius);
    }
}

void Game::healthCheck(){
    if(player1->getHealth() == 0){
        if(player1DeadTime < 0){
            player1DeadTime = DeadTime;
            player1->setPos(-20,-20);
            player1->hide();
        }
        else if(player1DeadTime > 0){
            --player1DeadTime;
        }
        else if(player1DeadTime == 0){
            player1->show();
            player1->reset(WIDTH/4, HEIGHT/2);
            player1DeadTime = -1;
        }
    }
    if(player2->getHealth() == 0){
        if(player2DeadTime < 0){
            player2DeadTime = DeadTime;
            player2->setPos(WIDTH+20,HEIGHT+20);
            player2->hide();
        }
        else if(player2DeadTime > 0){
            --player2DeadTime;
        }
        else if(player2DeadTime == 0){
            player2->show();
            player2->reset(3*WIDTH/4, HEIGHT/2);
            player2DeadTime = -1;
        }
    }
}

void Game::updateInfoBoard(){
    static QTime lastSecond = QTime::currentTime();
    static int timeDelta = 100;
    // Todo
    // call Function for players and ball->getDebugInfo() returns QString
    QString str = QString("<font color = white>Interval: ")+QString(int2str(globalTime).c_str());

    // 计算帧率
    if(globalTime%100==0)
    {
        QTime nowTime = QTime::currentTime();
        timeDelta = lastSecond.msecsTo(nowTime); // 计算一百帧的时间间隔（单位：毫秒）
        lastSecond = nowTime;
    }
    str += QString::asprintf("<br>fps: %f, standatd fps: %f",
                             1000.0*100.0/timeDelta, 1000.0/T);

    str += QString("<br>")+player1->debugInfo;
    str += QString("<br>")+player2->debugInfo;
    str += QString("<br>")+ballptr->debugInfo;

    str += QString("</font>");
    AIBoard->setHtml(str);

}

void Game::newObjectCheck(){
    int len = gameObjects.size();
    auto gameIt = gameObjects.begin();
    for(int i=0;i<len;++i,++gameIt){
        auto lst = (*gameIt)->getGeneratedObjects();
        for(auto it = lst.begin();it!=lst.end();++it){
            gameObjects.push_back(*it);
        }
    }
}

void Game::updateGameBoard(){
    int health1 = player1->getHealth(), health2 = player2->getHealth();
    int power1 = player1->getSkillPoint(), power2 = player2->getSkillPoint();
    if(health1 != boardInfo.player1Health){
        emit updatePlayer1Health(double(health1*1.0/PLAYER_HEALTH));
        boardInfo.player1Health = health1;
    }
    if(health2 != boardInfo.player2Health){
        emit updatePlayer2Health(double(health2*1.0/PLAYER_HEALTH));
        boardInfo.player2Health = health2;
    }
    if(power1 != boardInfo.player1Power){
        emit updatePlayer1Power(double(power1*1.0/PLAYER_SKILL_POINT_LIMIT));
        boardInfo.player1Power = power1;
    }
    if(power2 != boardInfo.player2Power){
        emit updatePlayer2Power(double(power2*1.0/PLAYER_SKILL_POINT_LIMIT));
        boardInfo.player2Power = power2;
    }
    int *hasBuff1 = player1->getBuffSet(), *hasBuff2 = player2->getBuffSet();
    for(int buff=0;buff<BUFF_TYPE_CNT;++buff){
        if(hasBuff1[buff] && !boardInfo.player1Buff[buff]){
            emit addPlayer1Buff(buff);
            boardInfo.player1Buff[buff] = true;
        }
        if(hasBuff2[buff] && !boardInfo.player2Buff[buff]){
            emit addPlayer2Buff(buff);
            boardInfo.player2Buff[buff] = true;
        }
        if(!hasBuff1[buff] && boardInfo.player1Buff[buff]){
            emit removePlayer1Buff(buff);
            boardInfo.player1Buff[buff] = false;
        }
        if(!hasBuff2[buff] && boardInfo.player2Buff[buff]){
            emit removePlayer2Buff(buff);
            boardInfo.player2Buff[buff] = false;
        }
    }
}

void Game::updateGame()
{
    /* Winner Check */
    if(gameSettings.gameFormat == TWO_THREE){
        if(boardInfo.player1BigScore >= 2){
            isGameOver = true;
            pause();
            emit gameOver(1,reviewMode);
        }
        else if(boardInfo.player2BigScore >= 2){
            isGameOver = true;
            pause();
            emit gameOver(2,reviewMode);
        }
    }
    else if(gameSettings.gameFormat == THREE_FIVE){
        if(boardInfo.player1BigScore >= 3){
            isGameOver = true;
            pause();
            emit gameOver(1,reviewMode);
        }
        else if(boardInfo.player2BigScore >= 3){
            isGameOver = true;
            pause();
            emit gameOver(2,reviewMode);
        }
    }

    globalTime += 1;
    // Todo
    // call Function for players and ball->getDebugInfo() returns QString
    updateInfoBoard();

    /* Record Mode */
    if(Game::reviewMode == false){
        gameInfo curInfo;
        curInfo.interval = globalTime;
        curInfo.action1 = parseKeyboard(1);
        curInfo.action2 = parseKeyboard(2);
        gameInfos.push_back(curInfo);
        player1->playerAct(curInfo.action1);
        player2->playerAct(curInfo.action2);
    }
    /* Review Mode */
    else if(Game::reviewMode == true){
        if(infoReader >= gameInfos.size()){
            player1->playerAct(ActionSet());
            player2->playerAct(ActionSet());
            gameInfos.clear();
        }
        else{
                if(gameInfos[infoReader].interval == Game::globalTime){
                player1->playerAct(gameInfos[infoReader].action1);
                player2->playerAct(gameInfos[infoReader].action2);
                infoReader += 1;
            }
            else{
                /* Empty Input */
                player1->playerAct(ActionSet());
                player2->playerAct(ActionSet());
            }
        }
    }
    // 物体之间碰撞
    collisionCheck();

    /* add new Objects */
    // call Function for all object->fetchGeneratedObject() returns vector<GameObject *>
    newObjectCheck();

    /* Update Objects in the scene */
    for(GameObject *ptr: this->gameObjects)
    {
        ptr->updateInGame();
    }
    /* Game Board */
    updateGameBoard();

    /* Health Check */
    healthCheck();

    /* ball position */
    goalCheck();

    /* delete */
    deadCheck();
}

void Game::quit(){
    delete timer;
    exit(0);
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

