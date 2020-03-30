#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>

using namespace std;

/******************************************************************************
 ****************************CLASS NodeIndividualScore******************************
 *store the information necesary
 ******************************************************************************
 */
class NodeIndividualScore
{
    //****************************************
    //DEFINITION OF ATTRIBUTES OF CLASS
    //****************************************
public:
    int score;
    NodeIndividualScore *next;

    //****************************************
    //DEFINITION OF PUBLIC FUNCTIONS
    //****************************************
public:
    //****************************************
    //CONSTRUCTOR WITHOUT PARAMETERS
    //****************************************
    NodeIndividualScore()
    {
        score = 0;
        next = NULL;
    }

    //****************************************
    //CONSTRUCTOR WITH PARAMETERS
    //****************************************
    NodeIndividualScore(int score)
    {
        this->score = score;
        this->next = NULL;
    }
};

/******************************************************************************
 ****************************CLASS SCOREBOARD**********************************
 * THIS LIST IS A SCOREBOARD INDIVIDUAL FOR EACH PLAYER
 ******************************************************************************
 */
class ScoreboardIndividual
{
    //****************************************
    //DEFINITION OF ATTRIBUTES OF CLASS
    //****************************************
public:
    NodeIndividualScore *first;
    string name;

    //****************************************
    //DEFINITION OF PUBLIC FUNCTIONS
    //****************************************
public:
    //************************************
    //CONTRUCTOR
    //************************************
    ScoreboardIndividual(string name)
    {
        first = NULL;
        this->name = name;
    }

    ScoreboardIndividual()
    {
        first = NULL;
        this->name = "";
    }

    //************************************
    //VERIFY IF LIST IS EMPTY
    //************************************
    bool isEmpty()
    {
        return first == NULL;
    }

    //************************************
    //SORT INSERT
    //insert node in order of mayor
    // to lowest point
    //************************************
    void addScore(int score)
    {
        NodeIndividualScore *new_node = new NodeIndividualScore(score);
        //if list is empty, insert new node in first position
        if (isEmpty())
        {
            first = new_node;
        }
        //if list is not empty
        else
        {
            //verify if score of new node is bigger that first node
            //if is true insert node before to first
            if (score > first->score)
            {
                new_node->next = first;
                first = new_node;
            }
            //if not go through to the list comparing node for node
            //until you find your correct position
            else
            {
                NodeIndividualScore *tmp = first;
                bool flag = false;
                while ((tmp->next != NULL) && flag == false)
                {
                    if (score > tmp->next->score)
                    {
                        new_node->next = tmp->next;
                        tmp->next = new_node;
                        flag = true;
                    }
                    else
                    {
                        tmp = tmp->next;
                    }
                }
                //insert new node until the last list
                if (flag == false)
                {
                    tmp->next = new_node;
                    //new_node->next=NULL;
                }
            }
        }
    }

    //**************************************************
    //SHOW IN CONSOLE THE LIST IN ORDER
    //**************************************************
    void printScoreboard()
    {
        if (isEmpty())
        {
            cout << "PUNTAJE INDIVIDUAL VACIO \n";
        }
        else
        {
            NodeIndividualScore *aux = first;
            while (aux->next != NULL)
            {
                cout << aux->score << "->";
                aux = aux->next;
            }
            cout << aux->score;
            cout << "\n";
        }
    }

    //***************************************************
    //GRAPH THE LIST IN A PNG PICTURE
    //***************************************************
    void graphScoreIndividual()
    {
        string scriptGraph;
        int numNode = 0;

        if (isEmpty())
        {
            scriptGraph = "digraph ScoreBoardIndividual{\n";
            scriptGraph += "node[style=rounded,shape=box];\n";
            scriptGraph += "node0[label=\"USUARIO SIN PUNTAJES\"];\n";
            scriptGraph += "}";
        }
        else
        {
            NodeIndividualScore *aux = first;
            scriptGraph = "digraph ScoreBoardIndividual{\nrankdir=LR;\nnode[style=rounded,shape=box,fontsize=30];\n";
            while (aux->next != NULL)
            {
                scriptGraph += "node";
                scriptGraph += to_string(numNode);
                scriptGraph += "[label=\"" + to_string(aux->score) + "\"]; \n";
                scriptGraph += "node" + to_string(numNode) + "->" + "node" + to_string(numNode + 1) + "; \n";
                numNode++;
                aux = aux->next;
            }
            scriptGraph += "node";
            scriptGraph += to_string(numNode);
            scriptGraph += "[label=\"" + to_string(aux->score) + "\"]; \n";
            scriptGraph += "label=\"Puntaje de " + name + "\";\n";
            scriptGraph += "}";
        }
        ofstream myFile;
        myFile.open("ScoreBoardIndividual.dot");
        myFile << scriptGraph;
        myFile.close();
        system("dot -Tpng ScoreBoardIndividual.dot -o ScoreBoardIndividual.png");
        system("shotwell ScoreBoardIndividual.png");
    }
};

/*
int main()
{
    ScoreboardIndividual *list=new ScoreboardIndividual("Fernanda");
    list->addScore(8);
    list->addScore(6);
    list->addScore(7);
    list->addScore(10);
    list->addScore(1);
    list->addScore(8);
    list->addScore(90);
    list->addScore(45);
    list->printScoreboard();
    list->graphScoreIndividual();
    return 0;
}
*/