#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

/******************************************************************************
 ****************************CLASS NODE COIN**********************************
 *FOR USE IN THE CLASS INDIVIDUAL LIST COIN AND QUEUE COIN
 ******************************************************************************
 */
class NodeCoin
{

//****************************************
//DEFINITION OF ATTRIBUTES OF CLASS
//****************************************
public:
    string letter;
    int value;
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
        this->next=NULL;
        this->previous = NULL;
    }
};
