#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

/******************************************************************************
 ****************************CLASS NodeBoxTriple*******************************
 ****************************************************************************** 
 */
class NodeBoxTriple
{
    //****************************************
    //DEFINITION OF ATTRIBUTES OF CLASS
    //****************************************
public:
    int position_x;
    int position_y;    
    NodeBoxTriple *next;
    //****************************************
    //DEFINITION OF PUBLIC FUNCTIONS
    //****************************************
public:
    //****************************************
    //CONSTRUCTOR WITHOUT PARAMETERS
    //****************************************
    NodeBoxTriple()
    {
        position_x = 0;
        position_y = 0;
        next = NULL;
    }
    //****************************************
    //CONSTRUCTOR WITH PARAMETERS
    //****************************************
    NodeBoxTriple(int position_x, int position_y)
    {
        this->position_x = position_x;
        this->position_y = position_y;
        this->next = NULL;
    }
};

/******************************************************************************
 ****************************CLASS BOX_TRIPLE**********************************
 ******************************************************************************
 */
class BoxTriple
{
    //****************************************
    //DEFINITION OF ATTRIBUTES OF CLASS
    //****************************************
public:
    NodeBoxTriple *first;

    //****************************************
    //DEFINITION OF PUBLIC FUNCTIONS
    //****************************************
public:
    //*************************************
    //CONTRUCTOR
    //*************************************
    BoxTriple()
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
    //INSERT BOX TRIPLE
    //*************************************
    void addBoxTriple(int x, int y)
    {
        NodeBoxTriple *new_node = new NodeBoxTriple(x, y);
        if (isEmpty())
        {
            first = new_node;
        }
        else
        {
            new_node->next = first;
            first = new_node;            
        }
    }

    //**************************************************
    //SHOW IN CONSOLE THE BOX DOUBLE
    //**************************************************
    void printBoxTriple()
    {
        if (isEmpty())
        {
            cout << "SIN CASILLAS TRIPLES\n";
        }
        else
        {
            NodeBoxTriple *aux = first;
            while (aux->next != NULL)
            {
                cout <<"(";
                cout << aux->position_x;
                cout << ",";
                cout << aux->position_y;
                cout <<")->";
                aux = aux->next;
            }
            cout <<"(";
            cout << aux->position_x;
            cout << ",";
            cout << aux->position_y;
            cout <<")";            
            cout << "\n";
        }
    }

    bool verifyBoxTriple(int x, int y)
    {
        bool response = false;
        NodeBoxTriple* tmp=first;        
        while (tmp !=NULL && response==false)
        {
            if((tmp->position_x==x) && (tmp->position_y==y))
            {
                response=true;
                tmp=tmp->next;
            }
            else
            {
                tmp=tmp->next;
            }            
        }        
        return response;
    }
};

/*
int main()
{
    BoxTriple *list=new BoxTriple();
    list->addBoxTriple(2,5);
    list->addBoxTriple(3,6);
    list->addBoxTriple(1,5);
    list->addBoxTriple(2,9);
    list->addBoxTriple(10,15);
    list->addBoxTriple(18,5);
    list->addBoxTriple(4,11);
    list->printBoxTriple();
    cout<<"\n";
    cout<<"Verificando: 2"<<endl;
    cout<<"Verificando: 30"<<endl;

    if(list->verifyBoxTriple(2,30))
        cout<<"PUNTEO TRIPLE";
    else
        cout<<"NO EXISTE";
    cout<<"\n";    
    return 0;
}*/
