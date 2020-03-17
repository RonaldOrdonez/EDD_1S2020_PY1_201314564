#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

class NodeScoreboard
{
public:
    int score;    
    NodeScoreboard *next;

public:
    NodeScoreboard()
    {
        score = 0;        
        next = NULL;
    }

    NodeScoreboard(int score)
    {
        this->score = score;        
        this->next = NULL;
    }
};

class Scoreboard
{
public:
    NodeScoreboard *first;

public:
    //CONTRUCTOR
    Scoreboard()
    {
        first = NULL;
    }

    //VERIFY IF LIST IS EMPTY
    bool isEmpty()
    {
        return first == NULL;
    }

    //SORT INSERT
    void addPlayer(int score)
    {
        NodeScoreboard *new_node = new NodeScoreboard(score);
        if (first == NULL)
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
                NodeScoreboard *tmp = first;
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

    void printScoreboard()
    {
        NodeScoreboard *aux = first;
        while (aux->next != NULL)
        {
            cout << aux->score << "->";                       
            aux = aux->next;
        }
        cout << aux->score;
        cout << "\n";
    }
};

/*
int main()
{
    Scoreboard *list=new Scoreboard();
    list->addPlayer(8);
    list->addPlayer(6);
    list->addPlayer(7);
    list->addPlayer(10);
    list->addPlayer(1);
    list->printScoreboard();
    return 0;
}*/
