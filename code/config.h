#ifndef CONFIG_H
#define CONFIG_H

#include <QMediaPlayer>
#include <QGraphicsItem>
#include <QMediaPlaylist>
#define WAV

/**
  * 这个文件里定义了所有游戏的的全局变量。
  * 包括若干部分：
  * 游戏参数（如玩家生命值、移动速度等）
  * 内存中的资源对象（图片、声音等），可引用
  */
//枚举量
typedef enum{
    LOVEMAN=0,
    SANTA,
    GUOSHEN,
    ANGRYBRO,
}PlayerType;

typedef enum{
    TWO_THREE=0,
    THREE_FIVE
}GameFormat;

typedef enum{
    LOW=0,
    MIDDLE,
    HIGH
}PlayerSpeed;


// 以下是游戏参数：

//一局游戏的设置参数
typedef struct{
    PlayerType player1Type, player2Type;
    GameFormat gameFormat;
    PlayerSpeed playerSpeed;
    bool enemyMode;
}GameSettings;
const int MAX_SMALL_SCORE = 3;

// 游戏本体（计时器、窗口等）参数
const int defaultT = 10;
const int WIDTH = 1280;
const int HEIGHT = 800;

// 玩家
const int PLAYER_RADIUS = 30;
const int PLAYER_HEALTH = 100;
const int PLAYER_SKILL_POINT_LIMIT = 100;
extern double PLAYER_SPEED;
const double DEFAULT_PLAYER_SPEED = 3.0;
const double PLAYER_MASS = 2.0;
const double PLAYER_VELOCITY_DECAY = 0.97;
const double TIME_TO_REACH_MAX_SPEED = 20;
extern double PLAYER_ACCELERATION;
const int PLAYER_SHOOTING_CD = 1*1000/defaultT; // 1s
const int PLAYER_SKILL_POINT_GAIN_CD = 0.1*1000/defaultT; // 10s回满
const int DeadTime = 400; // 4s复活

const double BULLET_SPEED = 7.0;
const double BULLET_MASS = 0.5;
const int BULLET_RADIUS = 15;
const int BULLET_DAMAGE = 10;
const int BULLET_TIME_TO_DESPAWN = 3*100;

//BUFF
const int BUFF_NUM = 4;

// 足球
const int BALL_RADIUS = 20;
const double BALL_MASS = 1.0;
const double BALL_VELOCITY_DECAY = 0.985;

// 障碍物
const double INFINITE_MASS = 1919810.114514;

// 道具
const int ITEM_RADIUS = 20;
const int ITEM_NUM = 5;

// 技能威力
const int BUFF_TIME = 5*1000/defaultT; // 5 seconds
const double MAGNET_FORCE = BALL_MASS*20.0;


// 以下是资源：


// 图片
const char startPNG[] = ":/art/start.png";
const char welcomePNG[] = ":/art/welcome.jpg";
const char backgroundPNG[] = ":/art/soccerField.png";

const char player1Src[] = ":/art/liuhan.png";
const char player2Src[] = ":/art/kuqi.png";
const char ballSrc[] = ":/art/football.png";
const char postSrc[] = ":/art/post.png";
const char itemSrc[ITEM_NUM][64] = {
    ":/art/speed.png", ":art/chicken.png", ":art/rage.png", ":art/magnet.png", ":art/star.png"
};

// 子弹贴图
const int PLAYER_TYPES = 4;
const char bulletSrc[PLAYER_TYPES][64] = {
    ":/art/heart.png", ":/art/snowflake.png", ":/art/bottle.png", ":/art/rock.png"
};
const char SSBulletSrc[PLAYER_TYPES][64] = {
    ":/art/heart.png", ":/art/freeze.png", ":/art/laptop.png", ":/art/chicken.png"
};

// 玩家贴图
const char angrySrc[] = ":/art/angry.png";
const char loveSrc[] = ":/art/love.png";
const char glsSrc[] = ":/art/gls.png";
const char santaSrc[] = ":/art/santa.png";

const char frozenManSrc[] = ":/art/frozen.png";
const char hotManSrc[] = ":/art/hot2.png";
const char magnetManSrc[] = ":/art/love_with_magnet.png";

// 音频

/* エレキ・デ・チョコボ 植松伸夫 */
const char backgroundMusic1Src[] = "./music/bg1.mp3";
const char bgmSrc[] = "qrc:///music/bgm.mp3";

//以下音效均来自https://sc.chinaz.com/yinxiao/
const char cheers1Src[] = "qrc:///music/cheers1.mp3";
const char cheers2Src[] = "qrc:///music/cheers2.mp3";
const char shootSrc[] = "qrc:///music/shoot.mp3";
const char whistleSrc[] = "qrc:///music/whistle.mp3";
const char victorySrc[] = "qrc:///music/victory.mp3";\
const char pickSrc[] = "qrc:///music/pick.wav";
#ifdef MP3
const char dieSrc[] = "qrc:///music/die.mp3";
const char skillSrc[PLAYER_TYPES][64] ={
    "qrc:///music/electricity.mp3","qrc:///music/frozen.mp3","qrc:///music/bomb.mp3","qrc:///music/roar.mp3"
};
#endif
#ifdef WAV
const char dieSrc[] = "qrc:///music/die.wav";
const char skillSrc[PLAYER_TYPES][64] ={
    "qrc:///music/electricity.mp3","qrc:///music/frozen.wav","qrc:///music/bomb.wav","qrc:///music/roar.wav"
};
#endif

// 资源对象
extern const QPixmap *player1Pixmap, *player2Pixmap, *frozenManPMap, *hotManPMap,*magnetManPMap,
                     *ballPixmap, *postPixmap, *bulletPixmap[PLAYER_TYPES], *SSBulletPixmap[PLAYER_TYPES],
                     *itemPMap[ITEM_NUM];

extern QMediaPlayer *shootPlayer, *skillPlayer[PLAYER_TYPES], *victoryPlayer, *diePlayer, *whistlePlayer, *pickPlayer;
extern QMediaPlaylist *shootPlaylist, *skillPlaylist[PLAYER_TYPES], *victoryPlaylist, *diePlaylist, *whistlePlaylist, *pickPlaylist;

#endif // CONFIG_H
