#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include "NodeCoin.cpp"
using namespace std;

/******************************************************************************
 ************************CLASS LIST COIN PLAYER********************************
 *USING SIMPLE DOUBLE-LINKED LIST
 ******************************************************************************
 */
class ListCoinPLayer
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
    //************************************
    //CONSTRUCTOR
    //************************************
    ListCoinPLayer()
    {
        first = NULL;
    }

    //************************************
    //RETURN TRUE IS LIST IS EMPTY
    //************************************
    bool isEmpty()
    {
        return first == NULL;
    }

    //************************************
    //ADD A NEW COIN TO THE LIST OF PLAYER
    //************************************
    void addCoin(string letter, int value)
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
            new_node->previous = tmp;
        }
    }

    //************************************
    //SHOW ELEMENTS TO THE LIST
    //************************************
    void showList()
    {
        if (isEmpty())
        {
            cout << "USUARIO SIN FICHAS \n";
        }
        else
        {
            NodeCoin *aux = first;

            if (first->next == NULL)
            {
                cout << first->letter << endl;
                cout << "Previous: NULL \n";
                cout << "Next: NULL \n";
                cout << "----------------------------- \n";
            }

            while (aux->next != NULL)
            {
                if (aux == first)
                {
                    cout << aux->letter << endl;
                    cout << "Previous: NULL" << endl;
                    ;
                    cout << "Next: " << aux->next->letter << endl;
                    cout << "------------------------------\n";
                }
                else
                {
                    cout << aux->letter << endl;
                    cout << "Previous: " << aux->previous->letter << endl;
                    cout << "Next: " << aux->next->letter << endl;
                    cout << "------------------------------\n";
                }
                aux = aux->next;
            }
            if (aux != first)
            {
                cout << aux->letter << endl;
                cout << "Previous: " << aux->previous->letter << endl;
                cout << "Next: NULL" << endl;
                cout << "------------------------------\n";
            }
        }
    }

    //********************************************
    //SHOW IN A PNG PICTURE THE DICTIONARY WORDS
    //********************************************

    void graphListOfIndividualCoin()
    {
        string scriptGraph;
        int numNode = 0;
        if (isEmpty())
        {
            scriptGraph = "digraph ListOfIndividualCoin{\n node[shape=box];\n node0[label=\"Jugador Sin Fichas\"];\n }";
        }
        else
        {
            NodeCoin *aux = first;
            scriptGraph += "digraph ListOfIndividualCoin{\nrankdir=LR;\nnode[style=rounded];\nnode[shape=box, fontsize=30];\n";
            while (aux->next != NULL)
            {
                scriptGraph += "node" + to_string(numNode);
                scriptGraph += "[label=\"" + aux->letter + "\"];\n";
                scriptGraph += "node" + to_string(numNode) + "->node" + to_string(numNode + 1) + ";\n";
                scriptGraph += "node" + to_string(numNode + 1) + "->node" + to_string(numNode) + ";\n";
                numNode++;
                aux = aux->next;
            }
            scriptGraph += "node" + to_string(numNode);
            scriptGraph += "[label=\"" + aux->letter + "\"];\n";
            scriptGraph += "}\n";
        }
        ofstream myFile;
        myFile.open("ListOfIndividualCoin.dot");
        myFile << scriptGraph;
        myFile.close();
        system("dot -Tpng ListOfIndividualCoin.dot -o ListOfIndividualCoin.png");
        system("shotwell ListOfIndividualCoin.png");
    }
};

/*
int main()
{
    ListCoinPLayer *list = new ListCoinPLayer();
    list->addCoin("A",2);
    list->addCoin("K",3);
    list->addCoin("L",9);
    list->addCoin("T",8);
    list->addCoin("Z",7);
    list->addCoin("E",6);
    list->addCoin("F",3);    
    cout<<"\n";
    list->showList();
    list->graphListOfIndividualCoin();
    return 0;
}*/
