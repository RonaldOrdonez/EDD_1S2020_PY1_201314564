#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
using namespace std;

/******************************************************************************
 ****************************CLASS NODE WORD***********************************
 *save words read from JSON file
 ******************************************************************************
 */

class NodeWord
{
    //****************************************
    //DECLARATION OF ATTRIBUTES
    //****************************************
public:
    string word;
    NodeWord *next;
    NodeWord *previous;

    //****************************************
    //DECLARATION OF PUBLIC FUNCTIONS
    //****************************************
public:
    //****************************************
    //CONTRUCTOR WITHOUT PARAMETERS
    //****************************************
    NodeWord()
    {
        this->word = "";
        this->next = NULL;
        this->previous = NULL;
    }

    //****************************************
    //CONSTRUCTOR WITH A PARAMETER
    //****************************************
    NodeWord(string word)
    {
        this->word = word;
        this->next = NULL;
        this->previous = NULL;
    }
};

/******************************************************************************
 ****************************CLASS LIST WORD***********************************
 ******************************************************************************
 */

class ListWords
{
    //****************************************
    //DECLARATION OF ATTRIBUTES
    //****************************************
public:
    NodeWord *first;
    NodeWord *last;

    //****************************************
    //DECLARATION OF PUBLIC FUNCTIONS
    //****************************************
public:
    //****************************************
    //CONSTRUCTOR
    //****************************************
    ListWords()
    {
        first = NULL;
        last = NULL;
    }

    void clearOut()
    {
        first=NULL;
        last=NULL;
    }

    //****************************************
    //RETURN TRUE IF LIST IS EMPTY
    //****************************************
    bool isEmpty()
    {
        return first == NULL;
    }

    //****************************************
    //ADD WORD TO THE TOP OF THE LIST
    //****************************************
    void addWord(string word)
    {
        NodeWord *new_node = new NodeWord(word);

        if (isEmpty())
        {
            first = new_node;
            last = new_node;
            first->next = first;
            first->previous = last;
        }
        else
        {
            last->next = new_node;
            new_node->previous = last;
            first->previous = new_node;
            new_node->next = first;
            last = new_node;
        }
    }

    bool checkWord(string word_)
    {
        int a;
        bool res = false;
        if (isEmpty())
        {
            res = false;            
        }
        else
        {
            NodeWord *aux = first;
            do
            {
                a = check_Word(aux->word, word_);
                if(a==0)
                {   
                    res=true;
                    break;
                }
                aux = aux->next;
            } while (aux != first);
        }
        return res;
    }

    //****************************************
    //SHOW ELEMENTS OF THE LIST
    //****************************************
public:
    string nameToLower(string cadena)
    {
        for (int i = 0; i < cadena.length(); i++)
            cadena[i] = tolower(cadena[i]);
        return cadena;
    }

    //************************************************
    //CHECK IF NEW NAME GOES BEFORE OR AFTER THAT ROOT
    //************************************************
    int check_Word(string node_word, string word_new)
    {
        int response = 0;
        string current_word = nameToLower(node_word);   //name new to compare
        string new_word = nameToLower(word_new); //root name to compare

        if (current_word.compare(new_word) == 0)
        {
            //THE NAMES ARE SAME
            response = 0;
        }
        else if (current_word.compare(new_word) > 0) // It's a right son
        {
            //THE NEW NAME IS THE RIGHT SONOF THE ROOT
            //node_word goes after to word_new
            response = 1;
        }
        else //It's a left son
        {
            //THE NEW NAME IS THE LEFT SON OF THE ROOT
            //node_word goes befor to word_new
            response = 2;
        }
        return response;
    }

    void showList()
    {
        if (isEmpty())
        {
            cout << "DICCIONARIO DE PALABRAS VACIO \n";
        }
        else
        {
            NodeWord *aux = first;
            do
            {
                cout << aux->word << "\n";
                cout << "next: " << aux->next->word << "\n";
                cout << "prev: " << aux->previous->word << "\n";
                cout << "-------------------- \n";
                aux = aux->next;

            } while (aux != first);
        }
    }

    //********************************************
    //SHOW IN A PNG PICTURE THE DICTIONARY WORDS
    //********************************************
public:
    void graphDictinary()
    {
        string scriptGraph;
        if (isEmpty())
        {
            scriptGraph = "digraph DictionaryWords{\n node[shape=box];\n node0[label=\"Diccionario Vacio\"];\n }";
        }
        else
        {
            NodeWord *aux = first;
            scriptGraph += "digraph DictionaryWords{\nrankdir=LR;\nnode[style=rounded];\nnode[shape=box];\n";
            do
            {
                scriptGraph += "\"" + aux->word + "\"->\"" + aux->next->word + "\";\n";
                scriptGraph += "\"" + aux->word + "\"->\"" + aux->previous->word + "\";\n";
                aux = aux->next;
            } while (aux != first);
            scriptGraph += "}\n";
        }
        ofstream myFile;
        myFile.open("DictionaryWords.dot");
        myFile << scriptGraph;
        myFile.close();
        system("dot -Tpng DictionaryWords.dot -o DictionaryWords.png");
        system("shotwell DictionaryWords.png");
    }
};

/*
int main()
{
    ListWords* list = new ListWords();
    list->addWord("HOLA");
    list->addWord("MUNDO");
    list->addWord("HOY");
    list->addWord("LUNES");    
    list->addWord("HAGO");    
    list->addWord("PRUEBAS");    
    list->addWord("PROYECTO");    
    list->addWord("UNO");    
    cout<<"\n";
    list->showList();
    if(list->checkWord("HOLA"))
    {
        cout<<"ENCONTRADO";
    }
    else
    {
        cout<<"NADA";
    }
    
    return 0;
}
*/