#include "BreadthFirstSearch.h"
//#include <queue>

BreadthFirstSearch::BreadthFirstSearch(Graph* graph, Agent* agent, Vector2D coinPos)
{
    findPath(graph,agent,coinPos);
}

BreadthFirstSearch::~BreadthFirstSearch()
{

}

void BreadthFirstSearch::findPath(Graph* graph,Agent* agent,Vector2D coinPos)
{
    //En que node del graph es troba el player?
    //Funcio que pasa de posPixels a grid de la posicio player. Buscar en el graf amb un for el node que correspon a aquesta pos.
    //
    //Un cop es troba fer un 
    //std::queue<node>
    std::vector<Node> _adjList;
    _adjList = graph->getAdjList();

    std::list<Node> queue; // es la frontera, els nodes que estan en cua per ser explorats.
    int numNodes;
    numNodes = graph->getnumNodes();
    std::vector<bool>visited(numNodes,false);

    //Ara s'a d'aconseguir el node d'start i passarlo a la llista fent push_back. Aleshores el node start es posa en visited. Posariem el id en l'index?¿?¿
    Node startNode;
    for (int i = 0; i < _adjList.size(); i++)
    {
        if (agent->getPosition() == _adjList[i].coord)
            startNode = _adjList[i];
    }
    Vector2D targetPos = _adjList[3].coord; //Ha d'arribar a l'algotisme de cerca!
    for (int i = 0; i < _adjList.size(); i++)
    {
        if (coinPos == _adjList[i].coord)
            targetPos = _adjList[i].coord;
    }
    Node currentNodeTemp;
    queue.push_back(startNode);
    std::map<int,int> cameFrom;
    cameFrom[startNode.id] = startNode.id;
    visited[startNode.id] = true;


    while (!queue.empty())
    {
        if (currentNodeTemp.coord == targetPos)
        {
            break;
        }
        currentNodeTemp = queue.front();
        queue.pop_front();
        
        for (int i = 0; i < currentNodeTemp.neighbours.size(); i++)
        {
            Node nodeToPush = _adjList[currentNodeTemp.neighbours[i].id];

            if (!cameFrom[nodeToPush.id])
            {
                frontierCount++;
                cameFrom[nodeToPush.id] = currentNodeTemp.id;
                queue.push_back(nodeToPush);
            }
        }

    }

    //Print de Nodes explorats
    std::cout << "Nodes explorats BFS: " << frontierCount << std::endl;

    std::list<Vector2D>finalPath;
    while (currentNodeTemp.id!=startNode.id)
    {
       finalPath.push_front(currentNodeTemp.coord);
        
        currentNodeTemp =_adjList[cameFrom[currentNodeTemp.id]];
    }

    std::list<Vector2D>finalPathAux = finalPath;
    for (int i = 0; i < finalPath.size(); i++)
    {
        agent->addPathPoint(finalPathAux.front());
        finalPathAux.pop_front();
    }
}