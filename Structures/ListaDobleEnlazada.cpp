#include <iostream>
#include <stdlib.h>
#include <string>
//#include <sstream>
//#include <fstream>
using namespace std;

class NodeCoin
{
public:
    string letter;
    int value;
    NodeCoin *next;
    NodeCoin *previous;

public:
    NodeCoin()
    {
        letter="";
        value=0;
        next = NULL;
        previous = NULL;
    }

    NodeCoin(string letter, int value)
    {
        this->letter=letter;
        this->value = value;
        this->next=NULL;
        this->previous = NULL;
    }
};



class ListCoinPLayer
{
public:
    NodeCoin *first;

public:
    //CONSTRUCTOR
    ListCoinPLayer()
    {
        first = NULL;
    }
    
    //DEVUELVE SI LA LISTA ESTA VACIA O NO   
    bool isEmpty()
    {
        return first==NULL;        
    }    

    //ADD A NEW NODE TO LISTA
    void addCoin(string letter, int value)
    {
        NodeCoin* new_node = new NodeCoin(letter,value);
        if (first == NULL)
        {
            first = new_node;
        }
        else
        {
            NodeCoin* tmp=first;
            while(tmp->next!=NULL){
                tmp=tmp->next;
            }
            tmp->next=new_node;
            new_node->previous=tmp;            
        }
    }

    //SHOW ELEMENTS TO THE LIST
    void showList()
    {
        NodeCoin *aux = first;   

        if(first->next==NULL)
        {
            cout << first->letter << endl;
            cout << "Previous: NULL \n";             
            cout << "Next: NULL \n";
            cout <<"----------------------------- \n";
        }

        while (aux->next != NULL)
        {
            if(aux==first){
                cout << aux->letter << endl;
                cout << "Previous: NULL"<<endl;;                
                cout << "Next: "<< aux->next->letter << endl;
                cout <<"------------------------------\n";
            }
            else
            {
                cout << aux->letter << endl;
                cout << "Previous: " << aux->previous->letter <<endl;          
                cout << "Next: "<< aux->next->letter << endl;
                cout <<"------------------------------\n";
            }           
            aux=aux->next;
        }
        if(aux!=first){
            cout << aux->letter << endl;
            cout << "Previous: " << aux->previous->letter <<endl;          
            cout << "Next: NULL"<< endl;
            cout <<"------------------------------\n";        
        }        
    }    
};

/*
int main()
{
    ListCoinPLayer *list = new ListCoinPLayer();
    list->addCoin("a",2);
    list->addCoin("b",3);
    list->addCoin("c",9);
    list->addCoin("d",8);
    list->addCoin("e",7);
    list->addCoin("f",6);
    list->addCoin("g",3);
    list->addCoin("h",4);
    cout<<"\n";
    list->showList();
    return 0;
}
*/