#include "node.hpp"

    /**
	 * constructeur
	 * @access public
	 * @return void
    */
    Node::Node()
    {
        m_obstacle = false;
        m_distStartCurrentG = m_distCurrentEndH = m_ghF = 0;
        m_parent.first = 0;
        m_parent.second = 0;
        m_x = m_y = 0;
    }

    /**
	 * modifie l'id du parent du node (l'id du parent est son indice dans la liste contenant le chemin)
	 * @param int parent : id du parent dans la liste des solutions
	 * @access public
	 * @return void
    */
    void Node::setParent(int parentX, int parentY)
    {
        m_parent.first = parentX;
        m_parent.second = parentY;
    }

    /**
	 * specifie si le node est un obstacle ou non
	 * @param bool obstacle : obstacle (true) ou non (false)
	 * @access public
	 * @return void
    */
    void Node::setObstacle(bool obstacle)
	{
        m_obstacle = obstacle;
    }

    /**
	 * specifie la distance parcourue entre le noeud de depart et le noeud courant
	 * @param int distStartCurrentG : distance
	 * @access public
	 * @return void
    */
    void Node::setDistStartCurrentG(int distStartCurrentG)
	{
        m_distStartCurrentG = distStartCurrentG;
    }

    /**
	 * specifie la distance entre le noeud courant et le dernier noeud
	 * @param int distStartCurrentG : distance
	 * @access public
	 * @return void
    */
    void Node::setDistCurrentEndH(int distCurrentEndH)
	{
        m_distCurrentEndH = distCurrentEndH;
    }

    /**
	 * donne la somme de m_distStartCurrentG + m_distCurrentEndH
	 * @param int ghF : somme
	 * @access public
	 * @return void
    */
    void Node::setGhF(int ghF)
	{
        m_ghF = ghF;
    }

    /**
	 * donne position X du noeud dans le monde
	 * @param int ghF : somme
	 * @access public
	 * @return void
    */
    void Node::setX(int x)
	{
        m_x = x;
    }

    /**
	 * donne position Y du noeud dans le monde
	 * @param int ghF : somme
	 * @access public
	 * @return void
    */
    void Node::setY(int y)
	{
        m_y = y;
    }

    /**
	 * retourne l'id du parent
	 * @param int ghF : somme
	 * @access public
	 * @return std::pair<int, int>
    */
    std::pair<int, int> Node::getParent()
	{
        return m_parent;
    }

    /**
	 * retourne si le noeud est un obstacle ou non
	 * @param int ghF : somme
	 * @access public
	 * @return bool
    */
    bool Node::getObstacle()
	{
        return m_obstacle;
    }

    /**
	 * retourne la distance entre le noeud de depart et le noeud courant
	 * @param int ghF : somme
	 * @access public
	 * @return int
    */
    int Node::getDistStartCurrentG()
	{
        return m_distStartCurrentG;
    }

    /**
	 * retourne la distance entre le noeud courant et le dernier noeud
	 * @param int ghF : somme
	 * @access public
	 * @return int
    */
    int Node::getDistCurrentEndH()
	{
        return m_distCurrentEndH;
    }

    /**
	 * retourne la somme des 2
	 * @param int ghF : somme
	 * @access public
	 * @return int
    */
    int Node::getGhF()
	{
        return m_ghF;
    }

    /**
	 * retourne la position X dans le monde
	 * @param int ghF : somme
	 * @access public
	 * @return int
    */
    int Node::getX()
	{
        return m_x;
    }

    /**
	 * retourne la position Y dans le monde
	 * @param int ghF : somme
	 * @access public
	 * @return int
    */
    int Node::getY()
	{
        return m_y;
    }

    /**
	 * destructeur
	 * @access public
	 * @return void
    */
    Node::~Node()
    {

    }
