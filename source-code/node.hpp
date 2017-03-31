#ifndef NODE_HPP_INCLUDED
#define NODE_HPP_INCLUDED

#include "include.hpp"

    class Node
    {
        public:
            Node();

            void setParent(int parentX, int parentY);
            void setObstacle(bool obstacle);
            void setDistStartCurrentG(int distStartCurrentG);
            void setDistCurrentEndH(int distCurrentEndH);
            void setGhF(int ghF);
            void setX(int x);
            void setY(int y);

            std::pair<int, int> getParent();
            bool getObstacle();
            int getDistStartCurrentG();
            int getDistCurrentEndH();
            int getGhF();
            int getX();
            int getY();

            ~Node();

        private:
            int m_distStartCurrentG;
            int m_distCurrentEndH;
            int m_ghF;
            int m_x;
            int m_y;
            bool m_obstacle;
            std::pair<int, int> m_parent; //sachant que les nodes ont des coordonnees uniques, le lien vers le parent est sa coordonnee
    };

#endif // NODE_HPP_INCLUDED
