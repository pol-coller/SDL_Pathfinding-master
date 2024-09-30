#include "GreedyBestFirstSearch.h"

GreedyBestFirstSearch::GreedyBestFirstSearch(Graph* graph, Agent* agent, Vector2D coinPos)
{
    findPath(graph, agent, coinPos);
}

GreedyBestFirstSearch::~GreedyBestFirstSearch()
{

}

void GreedyBestFirstSearch::findPath(Graph* graph, Agent* agent, Vector2D coinPos)
{
    std::vector<Node> _adjList;
    _adjList = graph->getAdjList();

    //std::list<Node> queue; // es la frontera, els nodes que estan en cua per ser explorats.
    std::priority_queue<Node, std::vector<Node>, compareWeight> frontier;
    int numNodes;
    numNodes = graph->getnumNodes();

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
    frontier.push(startNode);
    std::map<int, int> cameFrom;
    //std::map<int, int> costSoFar; //ID - costSoFar

    cameFrom[startNode.id] = startNode.id;
    //costSoFar[startNode.id] = 0;


    while (!frontier.empty())
    {
        if (currentNodeTemp.coord == targetPos) //
        {
            break;
        }

        currentNodeTemp = frontier.top();
        frontier.pop();


        for (int i = 0; i < currentNodeTemp.neighbours.size(); i++)
        {
            //int newCost = costSoFar[currentNodeTemp.id] + currentNodeTemp.neighbours[i].weight;

            Node nodeToPush = _adjList[currentNodeTemp.neighbours[i].id]; //vei

            if (!cameFrom[nodeToPush.id])
            {
                //Fer contador de frontera AQUI!
                frontierCount++;
                nodeToPush.costSoFar = heuristicManhattan(nodeToPush.coord, targetPos);
                //costSoFar[nodeToPush.id] = newCost;
                frontier.push(nodeToPush);
                cameFrom[nodeToPush.id] = currentNodeTemp.id;
            }
        }
    }

    std::cout << "Nodes explorats GreedyBFS: " << frontierCount << std::endl;

    std::list<Vector2D>finalPath;
    while (currentNodeTemp.id != startNode.id)
    {
        finalPath.push_front(currentNodeTemp.coord);

        currentNodeTemp = _adjList[cameFrom[currentNodeTemp.id]];
    }

    std::list<Vector2D>finalPathAux = finalPath;
    for (int i = 0; i < finalPath.size(); i++)
    {
        agent->addPathPoint(finalPathAux.front());
        finalPathAux.pop_front();
    }


}


int GreedyBestFirstSearch::heuristicManhattan(Vector2D pos, Vector2D targetPos)
{
	return abs(pos.x - targetPos.x) + abs(pos.y - targetPos.y);
}
