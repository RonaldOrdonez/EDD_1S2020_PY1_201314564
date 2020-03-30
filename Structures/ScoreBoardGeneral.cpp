#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>

using namespace std;

/******************************************************************************
 ****************************CLASS NodeGeneralScore******************************
 *store the information necesary for general scoreboard
 ******************************************************************************
 */
class NodeGeneralScore
{
    //****************************************
    //DEFINITION OF ATTRIBUTES OF CLASS
    //****************************************
public:
    int score;
    string player;
    NodeGeneralScore *next;
    //****************************************
    //DEFINITION OF PUBLIC FUNCTIONS
    //****************************************
public:
    //****************************************
    //CONSTRUCTOR WITHOUT PARAMETERS
    //****************************************
    NodeGeneralScore()
    {
        score = 0;
        player = "";
        next = NULL;
    }
    //****************************************
    //CONSTRUCTOR WITH PARAMETERS
    //****************************************
    NodeGeneralScore(int score, string player)
    {
        this->score = score;
        this->player = player;
        this->next = NULL;
    }
};


/******************************************************************************
 ****************************CLASS SCOREBOARD**********************************
 * THIS LIST IS THE SCRABBLE GENERAL SCORE
 * ****************************************************************************
 */
class ScoreboardGeneral
{

    //****************************************
    //DEFINITION OF ATTRIBUTES OF CLASS
    //****************************************
public:
    NodeGeneralScore *first;

    //****************************************
    //DEFINITION OF PUBLIC FUNCTIONS
    //****************************************
public:
    //*************************************
    //CONTRUCTOR
    //*************************************
    ScoreboardGeneral()
    {
        first = NULL;
    }

    //*************************************
    //VERIFY IF LIST IS EMPTY
    //*************************************
    bool isEmpty()
    {
        return first == NULL;
    }

    //*************************************
    //SORT INSERT
    //*************************************
    void addPlayer(int score, string player)
    {
        NodeGeneralScore *new_node = new NodeGeneralScore(score, player);
        if (isEmpty())
        {
            first = new_node;
        }
        else
        {
            if (score > first->score)
            {
                new_node->next = first;
                first = new_node;
            }
            else
            {
                NodeGeneralScore *tmp = first;
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
            cout << "PUNTEOS GENERALES VACIO \n";
        }
        else
        {
            NodeGeneralScore *aux = first;
            while (aux->next != NULL)
            {
                cout << aux->score;
                cout << "   ";
                cout << aux->player;
                cout << "\n";
                aux = aux->next;
            }
            cout << aux->score;
            cout << "   ";
            cout << aux->player;
            cout << "\n";
        }
    }

    //***************************************************
    //GRAPH THE GENERAL SCORE IN A PNG PICTURE
    //***************************************************
    void graphScoreGeneral()
    {
        string scriptGraph;
        int numNode = 0;

        if (isEmpty())
        {
            scriptGraph = "digraph ScoreBoardGeneral{\n";
            scriptGraph += "node[style=rounded,shape=box];\n";
            scriptGraph += "node0[label=\"SIN SCOREBOARD GENERAL\"];\n";
            scriptGraph += "}";
        }
        else
        {
            NodeGeneralScore *aux = first;
            scriptGraph = "digraph ScoreBoardGeneral{\nrankdir=LR;\nnode[style=rounded,shape=box];\n";
            scriptGraph += "label=\"Scoreboard del Juego\";\n";
            while (aux->next != NULL)
            {
                scriptGraph += "node";
                scriptGraph += to_string(numNode);
                scriptGraph += "[label=\"" + aux->player + "\n" + to_string(aux->score) + "pts\"]; \n";
                scriptGraph += "node" + to_string(numNode) + "->" + "node" + to_string(numNode + 1) + "; \n";
                numNode++;
                aux = aux->next;
            }
            scriptGraph += "node";
            scriptGraph += to_string(numNode);
            scriptGraph += "[label=\"" + aux->player + "\n" + to_string(aux->score) + "pts\"]; \n";
            scriptGraph += "}";
        }
        ofstream myFile;
        myFile.open("ScoreBoardGeneral.dot");
        myFile << scriptGraph;
        myFile.close();
        system("dot -Tpng ScoreBoardGeneral.dot -o ScoreBoardGeneral.png");
        system("shotwell ScoreBoardGeneral.png");
    }
};

/*
int main()
{
    ScoreboardGeneral *list=new ScoreboardGeneral();
    list->addPlayer(8,"Juan");
    list->addPlayer(6,"Pedro");
    list->addPlayer(7,"Luis");
    list->addPlayer(10,"Ester");
    list->addPlayer(90,"Faby");
    list->addPlayer(50,"Isela");
    list->addPlayer(13,"Mariana");
    list->printScoreboard();
    list->graphScoreGeneral();
    return 0;
}
*/