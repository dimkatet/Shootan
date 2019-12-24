#include "Game/GSMPClient.h"

GSMPClient::GSMPClient(VideoSettings *_videoSettings, string _ip)
{
    //ctor
    ip = _ip;
    videoSettings = _videoSettings;
    state = MPS_MENU_CONNECTING;
    //host.setBlocking(false);
    setupSettings(_videoSettings);
    healthBar = new HealthBar(playerClient);
    ammoBar = new AmmoBar(playerClient);
    playerHost = new PlayerClient;
    playerHost->setOpponentTexture();
}

void GSMPClient::connect(string _ip)
{
    sf::SocketSelector selector;
    selector.add(host);
    cout << "Connecting to host" << endl;
    status = host.connect(_ip, 2000);
    if(status != sf::Socket::Done)
    {
        cout << "Couldn't connect to host!" << endl;
    }
    else
    {
        cout << "Succesfully connected to host!" << endl;
        state = MPS_MENU_WAITING;
        host.setBlocking(true);
    }
    sf::Packet readyPacket;
    readyPacket << "ready";
    host.send(readyPacket);
}

GameStates GSMPClient::update()
{
    sf::Packet outgoingPacket, incomingPacket;
    switch(state)
    {
    case MPS_MENU_CONNECTING:
        connect(ip);
        break;
    case MPS_START_GAME:
        //host.setBlocking(false);
        resources->getMusic("GXRCH - Race for Wind")->play();
        state = MPS_PLAY;
        return GameStates::GS_GAMEMODE_MPCLIENT;
        break;
    case MPS_PLAY:
        ClientEvents event;
        sf::Int8 disconnect = 0;
        sf::Int8 hostDisconnect = 0;
        event.keyDownW = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
        event.keyDownS = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
        event.keyDownA = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
        event.keyDownD = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
        event.keyDownR = sf::Keyboard::isKeyPressed(sf::Keyboard::R);
        event.keyDownLMB = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        event.angle = playerClient->setOrientation();
        outgoingPacket << disconnect << event << playerClient->getCurrentHealthPoints();
        host.send(outgoingPacket);
        host.receive(incomingPacket);
        sf::Vector2f posClient, posHost;
        incomingPacket >> hostDisconnect;
        if(hostDisconnect)
            return GameStates::GS_MAINMENU;
        float angleHost;
        incomingPacket >> posClient.x >> posClient.y >> posHost.x >> posHost.y >> angleHost;
        bool keyDownLMB;
        incomingPacket >> keyDownLMB;
        int gg;
        incomingPacket >> gg;
        playerClient->update(posClient, event.keyDownLMB);
        playerHost->update(posHost, keyDownLMB);
        playerHost->setOrientation(angleHost);
        checkObstacles();
        updateGlobal();
        checkProjectiles();
        updateListener();
        if(gg)
            rematch();
        return GameStates::GS_GAMEMODE_MPCLIENT;
    }
}

void GSMPClient::rematch()
{
    delete(playerHost);
    delete(playerClient);
    delete(healthBar);
    delete(ammoBar);
    vecProjectiles.clear();
    vecProjectiles.reserve(200);
    playerHost = new PlayerClient;
    playerClient = new PlayerClient;
    playerHost->setOpponentTexture();
    healthBar = new HealthBar(playerClient);
    ammoBar = new AmmoBar(playerClient);
    playerClient->setBorders(2000.f, 2000.f);
}

void GSMPClient::updateView()
{
    GSMPHost::updateView(playerClient);
}

void GSMPClient::updateTime()
{
    if(currentTime <= 0.f)
    {
        currentTime = overloadTime;
        counterWeapon++;
        Weapon* wp1;
        Weapon* wp2;
        switch(counterWeapon%3)
        {
            case 0: wp1 = new Shotgun(playerClient->getSpritePointer()); wp2 = new Shotgun(playerClient->getSpritePointer()); break;
            case 1: wp1 = new SniperRifle(playerClient->getSpritePointer()); wp2 = new SniperRifle(playerClient->getSpritePointer()); break;
            case 2: wp1 = new SniperRifle(playerClient->getSpritePointer()); wp2 = new SniperRifle(playerClient->getSpritePointer()); break;
            default: wp1 = new Shotgun(playerClient->getSpritePointer()); wp2 = new Shotgun(playerClient->getSpritePointer()); break;
        }
        vecPerks.push_back(new FindWeapon(100,100,wp1));
        vecPerks.push_back(new FindWeapon(1900,1900,wp2));
        vecPerks.push_back(new UpSpeed(200,100));
        vecPerks.push_back(new UpSpeed(1800,1900));
        vecPerks.push_back(new Medicine(300,100));
        vecPerks.push_back(new Medicine(1700,1900));
    }
    else
    {
        currentTime -= frameTime;
    }
    for(unsigned int i=0; i < vecPerks.size(); i++)
    {
        vecPerks[i]->update();
        if(checkCollision(playerHost, vecPerks[i]))
        {
            vecPerks[i]->pickUp(playerHost);
            vecPerks.erase(vecPerks.begin() + i);
            continue;
        }
        if(checkCollision(playerClient, vecPerks[i]))
        {
            vecPerks[i]->pickUp(playerClient);
            vecPerks.erase(vecPerks.begin() + i);
            continue;
        }
        if(vecPerks[i]->checkActive())
        {
            vecPerks.erase(vecPerks.begin() + i);
        }
    }
}

void GSMPClient::checkObstacles()
{
    for(unsigned int i = 0; i < vecObstacles.size(); i++)
    {
        for(unsigned int j = 0; j < vecProjectiles.size(); j++)
        {
            if(checkCollision(vecProjectiles[j], vecObstacles[i]) && !(vecObstacles[i]->passability))
            {
                vecProjectiles[j]->markToDelete();
                if(vecProjectiles[j]->toDelete())
                    vecProjectiles.erase(vecProjectiles.begin()+j);
            }
        }
    }

}

void GSMPClient::updateListener()
{
    sf::Listener::setPosition(playerClient->getSprite().getPosition().x, playerClient->getSprite().getPosition().y, 0.f);
}

GSMPClient::~GSMPClient()
{
    sf::Packet packet;
    packet << sf::Int8(1);
    host.send(packet);
    vecProjectiles.clear();
    delete(playerClient);
    delete(playerHost);
    resources->getMusic("GXRCH - Race for Wind")->stop();
}

void GSMPClient::checkProjectiles()
{
    for (unsigned int i = 0; i < vecProjectiles.size(); i++)
    {
        if (vecProjectiles[i]->getSource() != playerHost->getSpritePointer())
            if (checkCollision(vecProjectiles[i], playerHost))
            {
                playerHost->takeDamage(vecProjectiles[i]->getDamage());
                vecProjectiles[i]->markToDelete();
            }
        if (vecProjectiles[i]->getSource() != playerClient->getSpritePointer())
            if (checkCollision(vecProjectiles[i], playerClient))
            {
                playerClient->takeDamage(vecProjectiles[i]->getDamage());
                vecProjectiles[i]->markToDelete();
            }
        if (vecProjectiles[i]->toDelete())
            vecProjectiles.erase(vecProjectiles.begin() + i);
    }
}

void GSMPClient::draw()
{
    window.setView(view);
    window.draw(background);
    for(unsigned int i = 0; i < vecProjectiles.size(); i++)
        window.draw(*vecProjectiles[i]);
    for(unsigned int i = 0; i < vecObstacles.size(); i++)
        window.draw(*vecObstacles[i]);
    for (unsigned int i = 0; i < vecPerks.size(); i++)
        window.draw(*vecPerks[i]);
    window.draw(*playerClient);
    window.draw(*playerHost);
    window.setView(window.getDefaultView());
    window.draw(*healthBar);
    window.draw(*ammoBar);
}

