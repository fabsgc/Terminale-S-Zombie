#include "include.hpp"

int getScreen()
{
    int screen;

    TiXmlDocument doc("config/game_config.xml");

    if(doc.LoadFile()){
        std::cout << "[INFORMATION] : [getScreen] chargement de \"config/game_config.xml\"" << std::endl;

        TiXmlHandle hdl(&doc);
        TiXmlElement *elem = hdl.FirstChildElement().Element();

        if(!elem)
        {
            std::cout << "[ERREUR] : [getScreen] : le noeud levels n'existe pas" << std::endl;
            screen = WIDTH;
        }
        else
        {
            elem->QueryIntAttribute("screen", &screen);
        }
    }

    return screen;
}

int getGameplay()
{
    int gamePlay;

    TiXmlDocument doc("config/game_config.xml");

    if(doc.LoadFile()){
        std::cout << "[INFORMATION] : [getGameplay] chargement de \"config/game_config.xml\"" << std::endl;

        TiXmlHandle hdl(&doc);
        TiXmlElement *elem = hdl.FirstChildElement().Element();

        if(!elem)
        {
            std::cout << "[ERREUR] : [getGameplay] : le noeud levels n'existe pas" << std::endl;
            gamePlay = 1;
        }
        else
        {
            elem->QueryIntAttribute("gameplay", &gamePlay);
        }
    }

    return gamePlay;
}

int distancePoint(int x1, int y1, int x2, int y2)
{
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}
