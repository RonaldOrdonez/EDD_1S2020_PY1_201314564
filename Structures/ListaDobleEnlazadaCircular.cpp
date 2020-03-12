#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

class NodeValidateWord
{

public:    
    string word;
    NodeValidateWord *next;
    NodeValidateWord *previous;

public:
    NodeValidateWord()
    {
        this->word = "";        
        this->next = NULL;
        this->previous = NULL;
    }

    NodeValidateWord(string word)
    {        
        this->word = word;
        this->next = NULL;
        this->previous = NULL;
    }
};


class ListWords
{
public:
    NodeValidateWord *first;
    NodeValidateWord *last;

public:
    //CONSTRUCTOR
    ListWords()
    {
        first = NULL;
        last = NULL;
    }

    //RETURN TRUE IF LIST IS EMPTY
    bool isEmpty(){
        return first==NULL;        
    }

    //ADD WORD TO THE TOP OF THE LIST
    void addWord(string word)
    {
        NodeValidateWord* new_node = new NodeValidateWord(word);
        
        if (first == NULL)
        {
            first=new_node;
            last=new_node;
            first->next=first;
            first->previous=last;
        }
        else
        {
            last->next=new_node;
            new_node->previous=last;
            first->previous = new_node;
            new_node->next=first;
            last=new_node;           
        }
    }

    //SHOW ELEMENTS OF THE LIST
    void showList()
    {
        NodeValidateWord* aux = first;
        do
        {
            cout << aux->word << "\n";
            cout<<"next: "<<aux->next->word<<"\n";
            cout<<"prev: "<<aux->previous->word<<"\n";
            cout<<"-------------------- \n";
            aux = aux->next;

        } while (aux != first);
    }   
};

/*
int main()
{
    ListWords* list = new ListWords();
    list->addWord("hola");
    list->addWord("hoy ");
    list->addWord("martes");
    list->addWord("jueves");    
    cout<<"\n";
    list->showList();
    return 0;
*/
