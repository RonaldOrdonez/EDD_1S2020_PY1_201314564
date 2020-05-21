#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

/******************************************************************************
 ****************************CLASS NodeBoxDouble*******************************
 ****************************************************************************** 
 */
class NodeBoxDouble
{
    //****************************************
    //DEFINITION OF ATTRIBUTES OF CLASS
    //****************************************
public:
    int position_x;
    int position_y;    
    NodeBoxDouble *next;
    //****************************************
    //DEFINITION OF PUBLIC FUNCTIONS
    //****************************************
public:
    //****************************************
    //CONSTRUCTOR WITHOUT PARAMETERS
    //****************************************
    NodeBoxDouble()
    {
        position_x = 0;
        position_y = 0;
        next = NULL;
    }
    //****************************************
    //CONSTRUCTOR WITH PARAMETERS
    //****************************************
    NodeBoxDouble(int position_x, int position_y)
    {
        this->position_x = position_x;
        this->position_y = position_y;
        this->next = NULL;
    }
};

/******************************************************************************
 ****************************CLASS DOUBLEBOX***********************************
 ******************************************************************************
 */
class BoxDouble
{
    //****************************************
    //DEFINITION OF ATTRIBUTES OF CLASS
    //****************************************
public:
    NodeBoxDouble *first;

    //****************************************
    //DEFINITION OF PUBLIC FUNCTIONS
    //****************************************
public:
    //*************************************
    //CONTRUCTOR
    //*************************************
    BoxDouble()
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
    //INSERT BOX DOUBLE
    //*************************************
    void addBoxDouble(int x, int y)
    {
        NodeBoxDouble *new_node = new NodeBoxDouble(x, y);
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
    void printBoxDouble()
    {
        if (isEmpty())
        {
            cout << "SIN CASILLAS DOBLES \n";
        }
        else
        {
            NodeBoxDouble *aux = first;
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

    //**************************************************
    //CHECK IF THERE IS A BOX THAT GIVES DOUBLE VALUE
    //**************************************************
    bool verifyBoxDouble(int x, int y)
    {
        bool response = false;
        NodeBoxDouble* tmp=first;        
        while (tmp !=NULL && response==false)
        {
            if((tmp->position_x==x) && (tmp->position_y==y))
            {
                response=true;                
            }           
            tmp=tmp->next;            
        }        
        return response;
    }
};

/*
int main()
{
    BoxDouble *list=new BoxDouble();
    list->addBoxDouble(2,5);
    list->addBoxDouble(3,6);
    list->addBoxDouble(1,5);
    list->addBoxDouble(2,9);
    list->addBoxDouble(10,15);
    list->addBoxDouble(18,5);
    list->addBoxDouble(4,11);
    list->printBoxDouble();
    if(list->verifyBoxDouble(2,30))
        cout<<"PUNTEO DOBLE";
    else
        cout<<"NO EXISTE";
    cout<<"\n";    
    return 0;
}*/
