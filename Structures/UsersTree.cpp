#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>

using namespace std;

/******************************************************************************
 ****************************CLASS NodeIndividualScore******************************
 *store the information necesary
 ******************************************************************************
 */

class NodeIndividualScore
{
    //****************************************
    //DEFINITION OF ATTRIBUTES OF CLASS
    //****************************************
public:
    int score;
    NodeIndividualScore *next;

    //****************************************
    //DEFINITION OF PUBLIC FUNCTIONS
    //****************************************
public:
    //****************************************
    //CONSTRUCTOR WITHOUT PARAMETERS
    //****************************************
    NodeIndividualScore()
    {
        score = 0;
        next = NULL;
    }

    //****************************************
    //CONSTRUCTOR WITH PARAMETERS
    //****************************************
    NodeIndividualScore(int score)
    {
        this->score = score;
        this->next = NULL;
    }
};

/******************************************************************************
 ****************************CLASS SCOREBOARD**********************************
 * THIS LIST IS A SCOREBOARD INDIVIDUAL FOR EACH PLAYER
 ******************************************************************************
 */
class scoreIndividual
{
    //****************************************
    //DEFINITION OF ATTRIBUTES OF CLASS
    //****************************************
public:
    NodeIndividualScore *first;
    string name;

    //****************************************
    //DEFINITION OF PUBLIC FUNCTIONS
    //****************************************
public:
    //************************************
    //CONTRUCTOR
    //************************************    

    scoreIndividual()
    {
        first = NULL;
        this->name = "";
    }

    //************************************
    //VERIFY IF LIST IS EMPTY
    //************************************
    bool isEmpty()
    {
        return first == NULL;
    }

    //************************************
    //SORT INSERT
    //insert node in order of mayor
    // to lowest point
    //************************************
    void addScore(int score)
    {
        NodeIndividualScore *new_node = new NodeIndividualScore(score);
        //if list is empty, insert new node in first position
        if (isEmpty())
        {
            first = new_node;
        }
        //if list is not empty
        else
        {
            //verify if score of new node is bigger that first node
            //if is true insert node before to first
            if (score > first->score)
            {
                new_node->next = first;
                first = new_node;
            }
            //if not go through to the list comparing node for node
            //until you find your correct position
            else
            {
                NodeIndividualScore *tmp = first;
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
                //insert new node until the last list
                if (flag == false)
                {
                    tmp->next = new_node;
                    //new_node->next=NULL;
                }
            }
        }
    }

    //**************************************************
    //SHOW IN CONSOLE THE LIST IN ORDER
    //**************************************************
    void printScoreboard()
    {
        if (isEmpty())
        {
            cout << "PUNTAJE INDIVIDUAL VACIO \n";
        }
        else
        {
            NodeIndividualScore *aux = first;
            while (aux->next != NULL)
            {
                cout << aux->score << "->";
                aux = aux->next;
            }
            cout << aux->score;
            cout << "\n";
        }
    }

    //***************************************************
    //GRAPH THE LIST IN A PNG PICTURE
    //***************************************************
    void graphScoreIndividual()
    {
        string scriptGraph;
        int numNode = 0;

        if (isEmpty())
        {
            scriptGraph = "digraph ScoreBoardIndividual{\n";
            scriptGraph += "node[style=rounded,shape=box];\n";
            scriptGraph += "node0[label=\"USUARIO SIN PUNTAJES\"];\n";
            scriptGraph += "}";
        }
        else
        {
            NodeIndividualScore *aux = first;
            scriptGraph = "digraph ScoreBoardIndividual{\nrankdir=LR;\nnode[style=rounded,shape=box,fontsize=30];\n";
            while (aux->next != NULL)
            {
                scriptGraph += "node";
                scriptGraph += to_string(numNode);
                scriptGraph += "[label=\"" + to_string(aux->score) + "\"]; \n";
                scriptGraph += "node" + to_string(numNode) + "->" + "node" + to_string(numNode + 1) + "; \n";
                numNode++;
                aux = aux->next;
            }
            scriptGraph += "node";
            scriptGraph += to_string(numNode);
            scriptGraph += "[label=\"" + to_string(aux->score) + "\"]; \n";
            scriptGraph += "label=\"Puntaje de " + name + "\";\n";
            scriptGraph += "}";
        }
        ofstream myFile;
        myFile.open("ScoreBoardIndividual.dot");
        myFile << scriptGraph;
        myFile.close();
        system("dot -Tpng ScoreBoardIndividual.dot -o ScoreBoardIndividual.png");
        system("shotwell ScoreBoardIndividual.png");
    }
};

/***********************************************************************
 * ***** CLASS NODE TREE THAT SAVE INFO AND POINT NEXT NODES
 * *********************************************************************
 */
class NodeTree
{
public:
    string name;
    scoreIndividual *list;
    NodeTree *left;
    NodeTree *right;        

public:
    //****************************************************
    //CONSTRUCTOR WITHOUT PARAMETERS
    //****************************************************
    NodeTree()
    {
        name = "";
        left = NULL;
        right = NULL;    
        list = new scoreIndividual();
    }

    //****************************************************
    //CONSTRUCTOR WITH PARAMETERS
    //****************************************************
    NodeTree(string name)
    {
        this->name = name;
        this->left = NULL;
        this->right = NULL;        
        list = new scoreIndividual();
    }
};


/*********************************************************************
 **************CLASS BINARY SERCH TREE********************************
 *********************************************************************
 */
class TreePlayer
{
//*******************************************
//DECLARATION OF ATTRIBUTES
//*******************************************
public:
    NodeTree *root;
    int numberNodes; 
private:
    string result;  
    string script_preorder;     
    string script_inorder;     
    string script_posorder;     
    int countVisit;

//*******************************************
//DECLARATION OF PUBLIC FUNCTIONS
//*******************************************
public:
    //***************************************
    //CONSTRUCTOR
    //***************************************
    TreePlayer()
    {
        root = NULL;
        result = "";
        script_preorder = "";
        numberNodes = 0;
        countVisit = 0;
    }

    //***************************************
    //RETURN IF TREE IS EMPTY
    //***************************************
    bool isEmpty()
    {
        return root == NULL;
    }

    //***************************************
    //RETURN TREE'S ROOT
    //***************************************
    NodeTree *getRoot()
    {
        return root;
    }

    //***************************************
    //ADD NEW NODE TO THE TREE
    //***************************************
    void addPlayer(string name)
    {
        //CREATION NEW NODE
        NodeTree *new_node = new NodeTree(name);
        //IF ROOT IS EMPTY, ASIGN NEW NODE TO THE ROOT
        if (isEmpty())
        {
            root = new_node;
            numberNodes++;
        }
        //IF ROOT IS NOT EMPTY, SEND CURRENT ROOT AND NEW NODE
        //TO RECURSIVE ADD PLAYER FUNCTION
        else
        {
            recursive_addPlayer(root, new_node);
        }
    }

    //***************************************
    //Search a exists name
    //***************************************
    int serchPlayer(string name)
    {
        int res;
        NodeTree* n;
        n=recursiveSearchPlayer(root, name);
        if(n==NULL)
        {
            //cout<<"nombre no existe"<<endl;
            res=0; //if name doen's exist return 0
        }
        else
        {
            //cout<<"nombre ya existe"<<endl;
            res=1; //if name exists return 1
        }        
        return res;       
    }

    //***************************************
    //return name of node if exist
    //***************************************
    string getName(string name)
    {
        string res;
        NodeTree* node_res;
        node_res=recursiveSearchPlayer(root, name);
        res = node_res->name;

        return res;       
    }

private:
    NodeTree* recursiveSearchPlayer(NodeTree *root, string nameSearch)
    {
        if(!root)
        {
            return NULL;
        }
        else if(checkAlphabeticalOrder(nameSearch,root->name)==0)
        {
            return root;
        }        
        else if(checkAlphabeticalOrder(nameSearch,root->name)==1)
        {
            return recursiveSearchPlayer(root->right, nameSearch);
        }
        else
        {
            return recursiveSearchPlayer(root->left, nameSearch);
        }       
    }



    /***********************************************************************************************
     * *********************************************************************************************
     *  START GRAPH PREORDER , INORDER, POSORDER
     ***********************************************************************************************
     ***********************************************************************************************
     * */   

    //***********************************************
    //GRAPH PREORDER TRAVERSAL
    //***********************************************
public:   
    void graphPreOrderTraverse()
    {      
        if (isEmpty())
        {
            script_preorder = "digraph traversePreorder{\n";
            script_preorder += "node[style=rounded,shape=box];\n";
            script_preorder += "node0[label=\"Arbol Vacio\"];\n";
            script_preorder += "}";
        }
        else
        {            
            script_preorder = "digraph traversePreorder{\nrankdir=LR;\nnode[style=rounded,shape=box,fontsize=20];\n";
            preOrderGraphRecursive(root); 
            script_preorder += ";\n";
            script_preorder += "label=\"Recorrido Preorden\";\nfontsize=25;";
            script_preorder += "}";
        }
        ofstream myFile;
        myFile.open("traversePreorder.dot");
        myFile << script_preorder;
        myFile.close();
        system("dot -Tpng traversePreorder.dot -o traversePreorder.png");
        system("shotwell traversePreorder.png"); 
        script_preorder = "";
        countVisit = 0;
    }
private:
    void preOrderGraphRecursive(NodeTree *root)
    {
        //root->left->right
        if (root!=NULL)
        {   
            if(countVisit==numberNodes-1)
            {
                script_preorder += root->name;                 
            }
            else
            {
                script_preorder += root->name +"->";                
                countVisit++;
                preOrderGraphRecursive(root->left);
                preOrderGraphRecursive(root->right);                
            }
        }
    }

    //**********************************************
    //GRAPH INORDER TRAVERSAL
    //***********************************************   
public:
    void graphInOrderTraverse()
    {      
        if (isEmpty())
        {
            script_inorder = "digraph traverseInorder{\n";
            script_inorder += "node[style=rounded,shape=box];\n";
            script_inorder += "node0[label=\"Arbol Vacio\"];\n";
            script_inorder += "}";
        }
        else
        {            
            script_inorder = "digraph traverseInorder{\nrankdir=LR;\nnode[style=rounded,shape=box,fontsize=20];\n";
            inOrderGraphRecursive(root); 
            script_inorder += ";\n";
            script_inorder += "label=\"Recorrido Inorden\";\nfontsize=25;";
            script_inorder += "}";
        }
        ofstream myFile;
        myFile.open("traverseInorder.dot");
        myFile << script_inorder;
        myFile.close();
        system("dot -Tpng traverseInorder.dot -o traverseInorder.png");
        system("shotwell traverseInorder.png"); 
        script_inorder = "";
        countVisit = 0;
    }
private:
    void inOrderGraphRecursive(NodeTree *root)
    {
        //root->left->right
        if (root!=NULL)
        {               
            inOrderGraphRecursive(root->left);
            if(countVisit==numberNodes-1)
            {
                script_inorder += root->name;                                 
            }
            else
            {                
                script_inorder += root->name +"->";                
                countVisit++;                  
            }
            inOrderGraphRecursive(root->right);                
        }
    }

    //**********************************************
    //GRAPH POSORDER TRAVERSAL
    //***********************************************   
public:
    void graphPosOrderTraverse()
    {      
        if (isEmpty())
        {
            script_posorder = "digraph traversePosorder{\n";
            script_posorder += "node[style=rounded,shape=box];\n";
            script_posorder += "node0[label=\"Arbol Vacio\"];\n";
            script_posorder += "}";
        }
        else
        {            
            script_posorder = "digraph traversePosorder{\nrankdir=LR;\nnode[style=rounded,shape=box,fontsize=20];\n";
            posOrderGraphRecursive(root); 
            script_posorder += ";\n";
            script_posorder += "label=\"Recorrido Posorden\";\nfontsize=25;";
            script_posorder += "}";
        }
        ofstream myFile;
        myFile.open("traversePosorder.dot");
        myFile << script_posorder;
        myFile.close();
        system("dot -Tpng traversePosorder.dot -o traversePosorder.png");
        system("shotwell traversePosorder.png"); 
        script_posorder = "";
        countVisit = 0;
    }
private:
    void posOrderGraphRecursive(NodeTree *root)
    {
        //root->left->right
        if (root!=NULL)
        {
            posOrderGraphRecursive(root->left);
            posOrderGraphRecursive(root->right); 
            if(countVisit==numberNodes-1)
            {
                script_posorder += root->name;                 
            }
            else
            {
                script_posorder += root->name +"->";                
                countVisit++;                               
            }
        }
    }


    /***********************************************************************************************
     **********************************************************************************************
     *  START ONLY TRAVERSE PREORDER , INORDER, POSORDER
     ***********************************************************************************************
     ***********************************************************************************************
     * */

    //**********************************************
    //PREORDER TRAVERSAL
    //***********************************************
private:
    void viewPreOrder()
    {
        if(isEmpty())
        {
            cout<<"Arbol Vacio"<<"\n";
        }
        else
        {            
            preOrder(root);
        }
    }

    //**********************************************
    //INORDER TRAVERSAL
    //***********************************************
    void viewInOrder()
    {
        if(isEmpty())
        {
            cout<<"Arbol Vacio"<<"\n";
        }
        else
        {
            inOrder(root);
        }        
    }

    //**********************************************
    //POSORDER TRAVERSAL
    //***********************************************
    void viewPosOrder()
    {
        if(isEmpty())
        {
            cout<<"Arbol Vacio"<<"\n";
        }
        else
        {
            posOrder(root);
        }
    }

    //****************************************************
    //GRAPH TREE AN SHOW IT IN A PNG PICTURE 
    //****************************************************
public:
    void graphUsersTree()
    {
        if(isEmpty())
        {
            result = "digraph UsersTree{\n";
            result += "node[style=rounded,shape=box];\n";
            result += "node0[label=\"NO HAY JUGADORES TODAVIA\"];\n";
            result += "}";
        }
        else
        {
            result += "digraph UsersTree{\n";        
            result += "node[shape=record, height=.1];\n";
            recursiveGraphTree(root);
            result += "fontsize=15;\n";
            result += "}";
        }
        ofstream myFile;
        myFile.open("UsersTree.dot");
        myFile << result;
        myFile.close();
        system("dot -Tpng UsersTree.dot -o UsersTree.png");
        system("shotwell UsersTree.png"); 
        result = "";        
    } 

//*******************************************
//DECLARATION OF PRIVATES FUNCTIONS
//*******************************************
private:
    //****************************************************
    //CREATE A NEW NODE AND RETURN IT
    //****************************************************
    NodeTree *createNodePlayer(string name)
    {
        NodeTree *new_node = new NodeTree(name);
        return new_node;
    }

    //****************************************************
    //RECURSIVE FUNCTION TO TRAVERSE TREE
    //****************************************************
    void recursiveGraphTree(NodeTree *root_)
    {
        if (root_ != NULL)
        {
            result += root_->name + "[label = \"<f0> |<f1> " + root_->name + "|<f2>\"]; \n";
            if (root_->left != NULL)
            {
                result += "\"" + root_->name + "\"" + ":f0 -> \"" + root_->left->name + "\":f1; \n";                
            }
            if (root_->right != NULL)
            {
                result += "\"" + root_->name + "\"" + ":f2 -> \"" + root_->right->name + "\":f1; \n";                
            }
            //CALL RECURSIVE FUNCTION TO TRAVERSE LEFT SUBTREE
            recursiveGraphTree(root_->left);
            //CALL RECURSIVE FUNCTION TO TRAVERSE RIGHT SUBTREE
            recursiveGraphTree(root_->right);
        }
    }

    //************************************************
    //CONVERT A NAME TO LOWERCASE
    //************************************************
    string nameToLower(string cadena)
    {
        for (int i = 0; i < cadena.length(); i++)
            cadena[i] = tolower(cadena[i]);
        return cadena;
    }

    //************************************************
    //CHECK IF NEW NAME GOES BEFORE OR AFTER THAT ROOT
    //************************************************
    int checkAlphabeticalOrder(string new_name, string root_name)
    {
        int response = 0;
        string newname = nameToLower(new_name);   //name new to compare
        string rootname = nameToLower(root_name); //root name to compare

        if (newname.compare(rootname) == 0)
        {
            //THE NAMES ARE SAME
            response = 0;
        }
        else if (newname.compare(rootname) > 0) // It's a right son
        {
            //THE NEW NAME IS THE RIGHT SONOF THE ROOT
            //new_name goes after to root_name
            response = 1;
        }
        else //It's a left son
        {
            //THE NEW NAME IS THE LEFT SON OF THE ROOT
            //new_name goes befor to root_name
            response = 2;
        }
        return response;
    }

    //***************************************
    //RECURSIVE FUNCTION TO ADD NEW NODE
    //***************************************
    void recursive_addPlayer(NodeTree *root_sub, NodeTree *new_node)
    {
        if ((checkAlphabeticalOrder(new_node->name, root_sub->name)) == 2) // new name is left son
        {
            if (root_sub->left != NULL) //if left son exists, use ecursive function
            {
                recursive_addPlayer(root_sub->left, new_node);
            }
            else //if left son doesn't exist, assign new node as left son
            {
                root_sub->left = new_node;
                numberNodes++;
            }
        }

        else if ((checkAlphabeticalOrder(new_node->name, root_sub->name)) == 1) //new name is right son
        {
            if (root_sub->right != NULL) //if right son exists, use recursive function
            {
                recursive_addPlayer(root_sub->right, new_node);
            }
            else //if right son doesn't exist, assign new node as right son
            {
                root_sub->right = new_node;
                numberNodes++;
            }
        }
        else
        {
            //cout << "NODE ALREADY EXIST"<< "\n";
        }
    }

    //*******************************************************
    //SHOW NODES IN CONSOLE ORDERED IN PREORDER FORM
    //*******************************************************
    void preOrder(NodeTree *root)
    {        
        //root->left->right
        if (root!=NULL)
        {   
            cout << root->name << "->";                
            preOrder(root->left);
            preOrder(root->right);                            
        }
    }

    //*******************************************************
    //SHOW NODES IN CONSOLE ORDERED IN INORDER FORM
    //*******************************************************
    void inOrder(NodeTree *root)
    {
        //left->root->right

        if (root)
        {
            inOrder(root->left);
            cout << root->name << "->";
            inOrder(root->right);
        }
    }

    //*******************************************************
    //SHOW NODES IN CONSOLE ORDERED IN POSORDER FORM
    //*******************************************************
    void posOrder(NodeTree *root)
    {
        //left->right->root
        if (root)
        {
            posOrder(root->left);
            posOrder(root->right);
            cout << root->name << "->";
        }
    }
};


/*
int main()
{
    TreePlayer *tree = new TreePlayer();    
    //add players to the tree
    tree->addPlayer("marina");
    tree->addPlayer("carla");
    tree->addPlayer("eugenia");
    tree->addPlayer("roman");
    tree->addPlayer("ana");
    tree->addPlayer("norma");
    tree->addPlayer("zara");
    tree->viewInOrder();
    cout<<"\n------\n";
    //tree->serchPlayer("raul");
    //cout<<"\n";
   
   string buscar="fernanda";
   if(tree->serchPlayer(buscar)==1)
   {    
       cout<<"no existe usuario: "<<buscar<<endl;
   }   
   else
   {
       cout<<"ya existe usuario: "<<buscar<<endl;
   }   
   tree->addPlayer("fernanda");
   tree->viewInOrder();
   cout<<"\n------\n";
    
    tree->addPlayer("FERNANDA");
    tree->addPlayer("ximena");
    tree->addPlayer("jonas");
    tree->addPlayer("Victor"); 
    tree->addPlayer("Esteban");   
    
    //show number nodes
    cout <<"Numero de Nodos: "<< tree->numberNodes;
    cout << "\n";
    
    //show in console all types orders
    tree->viewPreOrder();
    cout << "\n";
    tree->viewInOrder();
    cout << "\n";
    tree->viewPosOrder();
    cout << "\n";
    
    //graph in png picture tree's nodes
    cout << "\n";
    tree->graphUsersTree();    
    cout << "\n";
    
    //graph in png picture pre,in,pos order traverse
    tree->graphPreOrderTraverse();
    tree->graphInOrderTraverse();
    tree->graphPosOrderTraverse();        
    cout << "\n";
    
    return 0;
}*/
