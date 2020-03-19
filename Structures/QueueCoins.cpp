#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include "NodeCoin.cpp"
#include <sstream>
#include <fstream>
using namespace std;

/******************************************************************************
 ****************************CLASS QUEUE COIN**********************************
 *Queue coins: save all coins with letters to distribute them
 ******************************************************************************
 */
class QueueCoin
{
    //****************************************
    //DEFINITION OF ATTRIBUTES OF CLASS
    //****************************************
public:
    NodeCoin *first;

    //****************************************
    //DEFINITION OF PUBLIC FUNCTIONS
    //****************************************
public:
    //****************************************
    //CONSTRUCTOR
    //****************************************
    QueueCoin()
    {
        first = NULL;
    }
    //****************************************
    //RETURN TRUE IF LIST IS EMPTY
    //****************************************
    bool isEmpty()
    {
        return first == NULL;
    }

    //****************************************
    //ADD A NEW NODE AT THE START OF THE QUEUE
    //****************************************
    void enqueueCoin(string letter, int value)
    {
        NodeCoin *new_node = new NodeCoin(letter, value);
        if (isEmpty())
        {
            first = new_node;
        }
        else
        {
            NodeCoin *tmp = first;
            while (tmp->next != NULL)
            {
                tmp = tmp->next;
            }
            tmp->next = new_node;
            //new_node->previous=tmp;
        }
    }

    //****************************************
    //DEQUEUE A NODE AND RETURN THE NODE
    //****************************************
    NodeCoin *dequeueCoin()
    {
        NodeCoin *tmp = first;
        first = first->next;
        return tmp;
    }

    //****************************************
    //SHOW ELEMENTS TO THE LIST
    //****************************************
    void showList()
    {
        if (isEmpty())
        {
            cout << "COLA DE FICHAS VACIA \n";
        }
        else
        {
            NodeCoin *aux = first;
            while (aux->next != NULL)
            {
                cout << aux->letter << ",";
                cout << aux->value << endl;
                cout << "Next: " << aux->next->letter << endl;
                cout << "------------------------------\n";
                aux = aux->next;
            }
            cout << aux->letter << ",";
            cout << aux->value << endl;
            cout << "Next: NULL" << endl;
        }
    }

    //****************************************
    //GRAPH THE QUEUE IN A PNG PICTURE
    //****************************************
    void graphQueue()
    {
        string scriptGraph;
        int numNode = 0;

        if (isEmpty())
        {
            scriptGraph = "digraph QueueCoins{\n";
            scriptGraph += "node[style=rounded];\n";
            scriptGraph += "node[shape=record];\n";
            scriptGraph += "node0[label=\"COLA DE FICHAS VACIA\"];\n";
            scriptGraph += "}";
        }
        else
        {
            NodeCoin *aux = first;
            scriptGraph = "digraph QueueCoins{\n";
            scriptGraph += "rankdir=TB; \n";
            scriptGraph += "node[style=rounded];\n";
            scriptGraph += "node[shape=record];\n";
            while (aux->next != NULL)
            {
                scriptGraph += "node";
                scriptGraph += to_string(numNode);
                scriptGraph += "[label=\"";
                scriptGraph += aux->letter + " x ";
                scriptGraph += to_string(aux->value) + "pts";
                scriptGraph += "\"]; \n";
                scriptGraph += "node" + to_string(numNode) + "->" + "node" + to_string(numNode + 1) + "; \n";
                numNode++;
                aux = aux->next;
            }
            scriptGraph += "node";
            scriptGraph += to_string(numNode);
            scriptGraph += "[label=\"";
            scriptGraph += aux->letter + " x ";
            scriptGraph += to_string(aux->value) + "pts";
            scriptGraph += "\"]; \n";
            scriptGraph += "}";
        }
        ofstream myFile;
        myFile.open("QueueCoins.dot");
        myFile << scriptGraph;
        myFile.close();
        system("dot -Tpng QueueCoins.dot -o QueueCoins.png");
        system("shotwell QueueCoins.png");
    }
};

/*
int main()  
{
    QueueCoin *list = new QueueCoin();
    list->enqueueCoin("D",2);
    list->enqueueCoin("B",3);
    list->enqueueCoin("P",3);
    list->enqueueCoin("A",1);
    list->enqueueCoin("H",4);   
    list->enqueueCoin("V",4);   
    cout<<"\n";
    list->showList();
    list->graphQueue();
    //NodeCoin* pop = list->dequeueCoin();
    //cout<<"Nodo sacado: "<<pop->letter<<endl;
    //list->showList();
    return 0;
}*/