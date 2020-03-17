#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

class NodeTree
{
    public:
        int name;
        NodeTree* left;
        NodeTree* right;

    public:

        NodeTree(){
            //name="";
            name=0;
            left=NULL;
            right=NULL;
        }

        NodeTree(int name){
            this->name = name;
            this->left=NULL;
            this->right=NULL;
        }    
};

class TreePlayer
{
    public:
        NodeTree *root;
    
    private:
        NodeTree* createNodePlayer(int name){
            NodeTree* new_node = new NodeTree(name);
            return new_node;
        }

    public:
        TreePlayer()
        {
            root=NULL;
        }

        bool isEmpty()
        {
            return root==NULL;
        }

        NodeTree* getRoot(){
            return root;
        }              
      

        void addPlayer(int name)
        {
            NodeTree* new_node = new NodeTree(name);
            if(isEmpty())
            {
                root=new_node;
            }
            else
            {
                recursive_addPlayer(root, new_node);
            }
        }

        void viewPreOrder(){
            preOrder(root);
        }

        void viewInOrder(){
            inOrder(root);
        }

        void viewPosOrder(){
            posOrder(root);
        }

        private:
        void recursive_addPlayer(NodeTree* root_sub, NodeTree* new_node)
        {
            if(new_node->name < root_sub->name)
            {
                if(root_sub->left != NULL)
                {
                    recursive_addPlayer(root_sub->left, new_node);
                }
                else
                {
                    root_sub->left = new_node;
                }                
            }

            else if (new_node->name > root_sub->name)
            {
                if (root_sub->right != NULL)
                {
                    recursive_addPlayer(root_sub->right, new_node);
                }
                else
                {
                    root_sub->right = new_node;
                }              
            }
            else
            {
                cout<<"EL NODO YA EXISTE";
            } 

        }

        void preOrder(NodeTree* root)
        {
            //root->left->right
            if(root)
            {
                cout<<root->name<<"->";
                preOrder(root->left);
                preOrder(root->right);
            }
        }

        void inOrder(NodeTree* root)
        {
            //left->root->right
            if(root)
            {                
                inOrder(root->left);
                cout<<root->name<<"->";
                inOrder(root->right);
            }
        }

        void posOrder(NodeTree* root)
        {
            //left->right->root
            if(root)
            {                
                posOrder(root->left);                
                posOrder(root->right);
                cout<<root->name<<"->";
            }
        }        
};

int main(){
    TreePlayer *tree = new TreePlayer();    
    tree->addPlayer(10);
    tree->addPlayer(8);
    tree->addPlayer(20);
    tree->addPlayer(5);
    tree->addPlayer(15);
    tree->addPlayer(9);
    tree->addPlayer(30);
    tree->addPlayer(1);
    tree->addPlayer(4);
    tree->addPlayer(28);
    cout<<"\n";
    tree->viewInOrder();
    cout<<"\n";    
    return 0;
}


