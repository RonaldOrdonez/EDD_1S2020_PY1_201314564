#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>

using namespace std;
/***********************************************************************
 * ***** CLASS NODE TREE THAT SAVE INFO AND POINT NEXT NODES
 * *********************************************************************
 */
class NodeTree
{
public:
    string name;
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
    }

    //****************************************************
    //CONSTRUCTOR WITH PARAMETERS
    //****************************************************
    NodeTree(string name)
    {
        this->name = name;
        this->left = NULL;
        this->right = NULL;
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
    string result;

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
        }
        //IF ROOT IS NOT EMPTY, SEND CURRENT ROOT AND NEW NODE
        //TO RECURSIVE ADD PLAYER FUNCTION
        else
        {
            recursive_addPlayer(root, new_node);
        }
    }

    //**********************************************
    //PREORDER TRAVERSAL
    //***********************************************
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

    void graphPreOrderTraverse()
    {        
        string script_preorder;              
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

    void preOrderRecursive(NodeTree *root)
    {
        //root->left->right
        if (root)
        {
            cout << root->name << "->";
            preOrder(root->left);
            preOrder(root->right);
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
            RecorrerNodosParaGraficarABB(root);
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
    void RecorrerNodosParaGraficarABB(NodeTree *root_)
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
            RecorrerNodosParaGraficarABB(root_->left);
            //CALL RECURSIVE FUNCTION TO TRAVERSE RIGHT SUBTREE
            RecorrerNodosParaGraficarABB(root_->right);
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
            }
        }
        else
        {
            cout << "NODE ALREADY EXIST"
                 << "\n";
        }
    }

    //*******************************************************
    //SHOW NODES IN CONSOLE ORDERED IN PREORDER FORM
    //*******************************************************
    void preOrder(NodeTree *root)
    {
        //root->left->right
        if (root)
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


int main()
{
    TreePlayer *tree = new TreePlayer();
    tree->addPlayer("marina");
    tree->addPlayer("carla");
    tree->addPlayer("eugenia");
    tree->addPlayer("roman");
    tree->addPlayer("ana");
    tree->addPlayer("norma");
    tree->addPlayer("zara");
    tree->addPlayer("FERNANDA");
    tree->addPlayer("ximena");
    tree->addPlayer("jonas");
    tree->addPlayer("Victor");
    tree->addPlayer("Esteban");
    tree->addPlayer("Victor");
    cout << "\n";
    tree->viewInOrder();
    cout << "\n";
    tree->graphUsersTree();
    return 0;
}
