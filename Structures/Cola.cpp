#include <iostream>
#include <stdlib.h>
#include <string>
#include "ListaDobleEnlazada.cpp"
//#include <sstream>
//#include <fstream>
using namespace std;

class QueueCoin
{
public:
    NodeCoin *first;

public:
    //CONSTRUCTOR
    QueueCoin()
    {
        first = NULL;
    }
    
    //DEVUELVE SI LA LISTA ESTA VACIA O NO   
    bool isEmpty()
    {
        return first==NULL;        
    }    

    //ADD A NEW NODE TO LISTA
    void enqueueCoin(string letter, int value)
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

    void dequeueCoin(){
        //NodeCoin* tmp = first;
        first=first->next;        
        //return tmp;
    }    
    

    //SHOW ELEMENTS TO THE LIST
    void showList()
    {
        NodeCoin *aux = first;   
        while (aux->next != NULL)
        {           
            cout << aux->letter << endl;
            cout << aux->value << endl;            
            cout << "Next: "<< aux->next->letter << endl;
            cout <<"------------------------------\n";            
            aux=aux->next;
        }
        cout << aux->letter << endl;
        cout << aux->value << endl;                    
        cout << "Next: NULL"<< endl;                    
    }    
};


int main()
{
    QueueCoin *list = new QueueCoin();
    list->enqueueCoin("a",2);
    list->enqueueCoin("b",3);
    list->enqueueCoin("c",9);
    list->enqueueCoin("d",8);
    list->enqueueCoin("e",7);   
    cout<<"\n";
    list->showList();
    return 0;
}