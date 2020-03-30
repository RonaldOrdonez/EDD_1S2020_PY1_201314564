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
private:
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

    //****************************************
    //SHOW ELEMENTS OF THE LIST
    //****************************************
private:
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
    list->graphDictinary();
    return 0;
}*/
