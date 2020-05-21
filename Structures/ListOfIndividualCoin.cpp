#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

class NodeCoin
{

//****************************************
//DEFINITION OF ATTRIBUTES OF CLASS
//****************************************
public:
    string letter;
    int value;
    bool visitado;
    NodeCoin *next;
    NodeCoin *previous;

//****************************************
//DEFINITION OF PUBLIC FUNCTIONS
//****************************************
public:

    //***********************************
    //CONSTRUCTOR WITHOUT PARAMETERS
    //***********************************
    NodeCoin()
    {
        letter="";
        value=0;
        visitado=false;
        next = NULL;
        previous = NULL;
    }

    //***********************************
    //CONSTRUCTOR WITH 2 PARAMETERS
    //***********************************
    NodeCoin(string letter, int value)
    {
        this->letter=letter;
        this->value = value;
        this->visitado = false;
        this->next=NULL;
        this->previous = NULL;
    }
};



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
    void clearOut()
    {       
        first=NULL;
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

    int checkLetter(char letter)
    {
        int response=0;
        char l;
        if (isEmpty())
        {
            response=0;
        }
        else
        {
            NodeCoin *aux = first;
            while(aux != NULL )
            {
                l=aux->letter[0];
                if((l==letter) && (aux->visitado==false))
                {
                    aux->visitado=true;
                    response=1;
                    break;                    
                }
                aux=aux->next;               
            }
        }     
        return response;
    }

    NodeCoin* returnCoinOnly()
    {
        if(first->next==NULL)
        {
            NodeCoin *tmp = first;
            first->next=NULL;
            first->previous=NULL;
            first=NULL;
            return tmp;
        }
        else if(isEmpty())
        {
            return NULL;
        }
        else
        {
            NodeCoin *tmp = first;
            while (tmp->next != NULL)
            {
                tmp = tmp->next;
            }

            NodeCoin* aux = tmp->previous;
            aux->next = NULL;
            return tmp;          
        }          
    }


    NodeCoin *returnCoin(string letter)
    {
        if (isEmpty())
        {
            //cout << "SIN FICHAS" << endl;
            return NULL;
        }
        else
        {
            NodeCoin *tmp = first;
            if (first->letter.compare(letter) == 0)
            {
                if(first->next==NULL)
                {
                    first=NULL;

                    tmp->next = NULL;
                    tmp->previous = NULL;
                    return tmp;
                }
                else
                {
                    first = first->next;
                    first->previous = NULL;

                    tmp->next = NULL;
                    tmp->previous = NULL;
                    return tmp;                    
                }
            }
            else
            {
                int flag = 0;
                while (tmp->next != NULL && flag == 0)
                {
                    if (tmp->next->letter.compare(letter) == 0)
                    {
                        NodeCoin *aux = tmp->next;
                        NodeCoin *aux2 = tmp->next;
                        if (tmp->next->next == NULL)
                        {
                            flag = 1;
                            tmp->next = NULL;

                            aux2->next = NULL;
                            aux2->previous = NULL;

                            return aux2;
                        }
                        else
                        {
                            flag = 1;
                            tmp->next = aux->next;
                            aux->next->previous = tmp;

                            aux2->next = NULL;
                            aux2->previous = NULL;
                            return aux2;
                        }
                    }
                    else
                    {
                        tmp = tmp->next;
                    }
                }
                if(flag==0)
                {
                    //NodeCoin* fail= new NodeCoin("2",0);
                    //return fail;                    
                    return NULL;
                }
            }
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

    void graphListOfIndividualCoin(string name)
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
            scriptGraph += "label=\"Fichas de: "+name+"\";\n";
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
    ListCoinPLayer *list  =new ListCoinPLayer();
    list->addCoin("A",2);
    list->addCoin("B",2);
    list->addCoin("S",2);
    list->addCoin("T",2);
    list->addCoin("A",2);
    list->addCoin("C",2);
    list->showList();
    cout<<"\n";
    
    int x = 66; //letra en ascii
    char c = static_cast<char>(x);   
    
    if(list->checkLetter(c)==1)
    {
        cout<<"LETRA EXISTE"<<endl;        
    }
    else
    {
        cout<<"LETRA NO EXISTE"<<endl;        
    }            
    cout<<"\n";    

    x=66;
    c = static_cast<char>(x);       
    if(list->checkLetter(c)==1)
    {
        cout<<"LETRA EXISTE"<<endl;        
    }
    else
    {
        cout<<"LETRA NO EXISTE"<<endl;        
    }            
    cout<<"\n";  
    return 0;
    
}*/

/*
int main()
{
    ListCoinPLayer *list = new ListCoinPLayer();
    list->addCoin("C", 2);
    list->addCoin("K", 3);
    list->addCoin("O", 9);
    list->addCoin("T", 8);
    list->addCoin("S", 7);
    list->addCoin("E", 6);
    list->addCoin("A", 3);
    cout << "\n";
    cout << "\n";
    list->showList();
    //list->graphListOfIndividualCoin();
    NodeCoin *test = new NodeCoin();
    test = list->returnCoin("C");
    cout << "\n";
    cout << "\n";
    cout << "encontrada: " << test->letter << endl;
    cout << "\n";
    cout << "\n";
    test = list->returnCoin("O");
    cout << "\n";
    cout << "\n";
    cout << "encontrada: " << test->letter << endl;
    cout << "\n";
    cout << "\n";
    test = list->returnCoin("S");
    cout << "\n";
    cout << "\n";
    cout << "encontrada: " << test->letter << endl;
    cout << "\n";
    cout << "\n";
    test = list->returnCoin("A");
    cout << "\n";
    cout << "\n";
    cout << "encontrada: " << test->letter << endl;
    cout << "\n";
    cout << "\n";
    test=list->returnCoin("K");
    cout<<"\n";
    cout<<"\n";
    cout<< "encontrada: "<<test->letter<<endl;
    cout<<"\n";
    cout<<"\n";
    test=list->returnCoin("T");
    cout<<"\n";
    cout<<"\n";
    cout<< "encontrada: "<<test->letter<<endl;
    cout<<"\n";
    cout<<"\n";
    test=list->returnCoin("E");
    cout<<"\n";
    cout<<"\n";
    cout<< "encontrada: "<<test->letter<<endl;
    cout<<"\n";
    cout<<"\n";
    list->showList();
    return 0;
}*/
