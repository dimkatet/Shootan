#ifndef GSSURVIVAL_H
#define GSSURVIVAL_H

#include "Game/GameState.h"

//*Field size 3840x2160 (2 times FullHD)

class GSSurvival : public GameState, public Collision
{
public:
    GSSurvival(VideoSettings *_videoSettings);
    virtual ~GSSurvival();
    void update();
    void draw();
    void handleEvents(sf::Event _event);
protected:
    Player*         player;
    sf::Sprite      background;
    sf::Text        info;
    sf::IntRect     fieldSize;
    sf::View        view;
    PauseMenu        *pauseMenu;
    VideoSettings   *videoSettings;
    EnemyFactory    *enemyFactory;
    bool            openPauseMenu;
    vector <Enemy*> vecEnemies;
    HealthBar       *healthBar;
    PerkMenu        *perkMenu;
    bool            openPerkMenu;
    void updateStats();
    void loadResources();
    void collectTrash();
    void checkProjectiles();
    void checkMelee();
    void checkPerks();
    void updateView();
    void updateListener();
    int k; //need for different perks( need rewrite)
private:
};

extern sf::RenderWindow     window;
extern float                frameTime;
extern vector <Projectile*> vecProjectiles;
extern vector <Perk*>       vecPerks;
extern ResourceManager      *resources;
#endif // GSSURVIVAL_H
