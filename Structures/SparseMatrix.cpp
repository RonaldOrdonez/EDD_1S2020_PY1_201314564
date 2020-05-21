#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
using namespace std;

class NodeCoinMatrix
{

//****************************************
//DEFINITION OF ATTRIBUTES OF CLASS
//****************************************
public:
    string letter;
    int value;
    NodeCoinMatrix *next;
    NodeCoinMatrix *previous;

//****************************************
//DEFINITION OF PUBLIC FUNCTIONS
//****************************************
public:

    //***********************************
    //CONSTRUCTOR WITHOUT PARAMETERS
    //***********************************
    NodeCoinMatrix()
    {
        letter="";
        value=0;
        next = NULL;
        previous = NULL;
    }

    //***********************************
    //CONSTRUCTOR WITH 2 PARAMETERS
    //***********************************
    NodeCoinMatrix(string letter, int value)
    {
        this->letter=letter;
        this->value = value;
        this->next=NULL;
        this->previous = NULL;
    }
};

/*****************************************************************************************************************
######################################### CLASS NODE'S MATRIX ###################################################
******************************************************************************************************************/
class NodeMatrix
{
    //-------------------------------------VARIABLES
    public:
    // position x,y
        int x;
        int y;
        NodeCoinMatrix *coin;        
        
    // direction of node
        NodeMatrix *right;
        NodeMatrix *left;
        NodeMatrix *down;
        NodeMatrix *up;

    //-------------------------------------FUNCTIONS AND METHODS
    public:
    //Constructor of class NodeMatrix
        
        //Constructor with parameters
        NodeMatrix(int x,int y, NodeCoinMatrix *coin)        
        {
            //position x,y
            this->x = x;
            this->y = y;            
            this->coin = coin;
            
            //direction right,left,down,up
            right = NULL;
            left = NULL;
            down = NULL;
            up = NULL;
        }

        //Constructor witout parameters
        NodeMatrix(){
            this->x=0;
            this->y=0;
            coin = NULL;                 
            
            right = NULL;
            left = NULL;
            down = NULL;
            up = NULL;
        }   
};

/*****************************************************************************************************************
############################################# CLASS MATRIX ########################################################
******************************************************************************************************************/
class SparseMatrix
{
    public:
        //BEGIN WITH NodeMatrix TYPE CALLED head
        NodeMatrix *head;

        //CONSTRUCTOR  
        SparseMatrix()
        {
            NodeMatrix *temp = new NodeMatrix();
            head = temp;
        }

        //CLEAR MATRIX

        void clearOut()
        {
            head->right=NULL;
            head->down=NULL;                       
        }

        //RETURN TRUE IF MATRIX IS EMPTY
        bool isEmpty()
        {
            return head->right==NULL;
        }

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+++++++++++++++++++++++++++++++++++++++ ADD NEW NODE +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
        //ADD NEW NODE TO MATRIX        
        void add(int x, int y, NodeCoinMatrix* coin)
        {            
            add_x_header(x); //create header for axis "x"
            add_y_header(y); //create header for axis "y"
            NodeMatrix *new_node = new NodeMatrix(x,y,coin); //create a new content node
            add_node_posX(new_node, x, y);  //add node to axis "x"
            add_node_posY(new_node, y, x);  //add node to axis "y"
        }

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++ HEADERS +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
        //CREATING HEADER FOR AXIS "X" - COLUMNS
        void add_x_header(int x)
        {
            if(head->right==NULL)   //when matriz dont have nodes in header x, header in x is empty
            {
                NodeMatrix *temp = new NodeMatrix(x,0,NULL);  //create a new node
                head->right = temp; // head right point to new node temp
                temp->left = head;  // new node temp left point to node head
            }
            else
            {
                NodeMatrix *temp = head; // create auxiliar node with reference to head 
                //travel to list verifying than temp node is less than the value x           
                while(temp->right != NULL && temp->right->x < x)
                {
                    temp = temp->right;
                }
                //add to end of the list
                if(temp->right==NULL)
                {
                    NodeMatrix *new_temp = new NodeMatrix(x,0,NULL);
                    temp->right = new_temp;
                    new_temp->left = temp;                
                }
                //add in the middle of the list if node doesn't exist
                else if(temp->right != NULL && temp->right->x != x)
                {
                    NodeMatrix *new_temp = new NodeMatrix(x,0,NULL);  // create new node with value x
                    NodeMatrix *der = temp->right; // node "der" keep to reference to value right to the node

                    temp->right = new_temp; // reference to current right node equals new node with value "x"
                    new_temp->left =temp;   // node with value "x", its left point to current node
                    new_temp->right = der;  // node with value "x", its right point to node "der"
                    der->left = new_temp;   // node "der" with reference saved point to new node 
                }
            }         
        }

        //CREATING HEADER FOR AXIS "Y" - ROWS
        void add_y_header(int y)
        {
            if(head->down == NULL)   //when matriz dont have nodes in header y, header in y is empty
            {
                NodeMatrix *temp = new NodeMatrix(0,y,NULL);  //create a new node
                head->down = temp; // head down point to new node temp
                temp->up = head;  // new node temp up point to node head
            }
            else
            {
                NodeMatrix *temp = head; // create auxiliar node with reference to head 
                //travel to list verifying than temp node is less than the value y           
                while(temp->down != NULL && temp->down->y < y)
                {
                    temp = temp->down;
                }
                
                //add to end of the list
                if(temp->down==NULL)
                {
                    NodeMatrix *new_temp = new NodeMatrix(0,y,NULL);
                    temp->down = new_temp;
                    new_temp->up = temp;                
                }
                //add in the middle of the list
                else if(temp->down != NULL && temp->down->y != y)
                {
                    NodeMatrix *new_temp = new NodeMatrix(0,y,NULL);  // create new node with value y
                    NodeMatrix *dwn = temp->down; // node "der" keep to reference to value down to the node

                    temp->down = new_temp; // reference to current down node equals new node with value "y"
                    new_temp->up =temp;   // node with value "y", its left point to current node
                    new_temp->down = dwn;  // node with value "y", its right point to node "der"
                    dwn->up = new_temp;   // node "der" with reference saved point to new node 
                }
            }

        }

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+++++++++++++++++++++++++++++++++++++++ ADD NEW NODE +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
 
        //ADD NODE IN AXIS "X" - COLUMNS
        void add_node_posX(NodeMatrix* new_node, int x, int y)
        {
            NodeMatrix *temp = head;
            //busca la cabecera que coincide con la que queremos insertar
            while(temp->x != x) 
            {
                temp = temp->right; 
            }            
            //significa que aun no hay nodos en la lista de la cabecera actual
            if(temp->down == NULL)
            {
                temp->down = new_node;
                new_node->up = temp;
            }        
            //hay x lo menos un nodo
            else{
                //verificar si el primer nodo de la lista es mayor que el que quiero insertar y si es TRUE, lo inserto antes
                if((temp->down->y > y)){
                    NodeMatrix *aux = temp->down;
                    new_node->down = aux;
                    aux->up = new_node;
                    temp->down = new_node;
                    new_node->up = temp;
                }
                //sino se inserta a la primera 
                else{
                    //avanza hasta que "y" sea menor que el aux->down
                    NodeMatrix *aux = temp;                    
                    while((aux->down!=NULL) && (aux->down->y < y))
                    {
                        aux=aux->down;
                    }
                    //si llego al final de la lista, significa que el aux->down es null y agrega el new_node al final de la lista
                    if(aux->down == NULL){
                        aux->down = new_node;
                        new_node->up = aux;
                    }
                    //sino la insercion se realiza en medio de la lista
                    else{
                                              
                            new_node->down = aux->down;
                            aux->down->up = new_node;
                            aux->down = new_node;
                            new_node->up = aux;
                                                                                            
                    }
                }             
            }                         
        }        

        //ADD NODE IN AXIS "Y"
        void add_node_posY(NodeMatrix* new_node, int y, int x)
        {
            NodeMatrix *temp = head;
            while(temp->y != y)
            {
                temp = temp->down;
            }
            //significa que aun no hay nodos en la lista de la cabecera actual
            if(temp->right == NULL)
            {
                temp->right = new_node;
                new_node->left = temp;
            }        
            //hay por lo menos un nodo
            else{
                //verificar si el primer nodo de la lista es mayor que el que quiero insertar y si es TRUE, lo inserto antes
                if(temp->right->x > x){
                    NodeMatrix *aux = temp->right;
                    new_node->right = aux;
                    aux->left = new_node;
                    temp->right = new_node;
                    new_node->left = temp;
                }
                //sino se inserta a la primera 
                else
                {
                    //avanza hasta que "y" sea menor que el aux->down
                    NodeMatrix *aux = temp;
                    while((aux->right!=NULL) && (aux->right->x < x))
                    {
                        aux=aux->right;
                    }
                    //si llego al final de la lista, significa que el aux->down es null y agrega el new_node al final de la lista
                    if(aux->right == NULL)
                    {
                        aux->right = new_node;
                        new_node->left = aux;
                    }
                    //sino la insercion se realiza en medio de la lista
                    else
                    {                        
                        new_node->right = aux->right;
                        aux->right->left = new_node;
                        aux->right = new_node;
                        new_node->left = aux;
                    }
                }
            }             
        }                 
                      
        

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+++++++++++++++++++++++++++++++++++++++++ PRINT HEADERS +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

        //PRINT IN CONSOLE THE VALUES LIST OF ROWS AND COLUMNS    
        void printHeaders()
        {
            print_x_header();
            print_y_header();
        }

        //PRINT HEADER IN X - COLUMNS
        void print_x_header()
        {
            NodeMatrix *temp = head;
            while(temp->right != NULL)
            {
                cout<<temp->x;
                cout<<"->";
                temp = temp->right;
            }        
            cout<< temp->x <<endl;
            cout<<"";
        } 
        
        //PRINT HEADER IN Y- ROWS
        void print_y_header()
        {
            NodeMatrix *temp = head->down;
            while(temp->down != NULL)
            {
                cout<<temp->y;
                cout<<"\n";
                temp = temp->down;
            }
            cout<< temp->y;
            cout<<"\n";
        }

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+++++++++++++++++++++++++++++++++++++++++ PRINT NODE CONTENTS++++++++++++++++++++++++++++++++++++++++++++++++++++++
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
        //PRINT NODES
        void printNodes()
        {
            print_nodes_x();
            cout<<"\n";
            print_nodes_y();
       }

       //PRINT NODES IN X - COLUMNS
        void print_nodes_x()
        {
            NodeMatrix *temp = head->right;
            while(temp->right != NULL)
            {
                NodeMatrix *aux=temp;
                cout<<temp->x; 
                cout<<"->";
                while(temp->down!=NULL){
                    cout<<"("<<temp->down->coin->letter <<"," <<temp->down->coin->value <<")";
                    cout<<"->";
                    temp = temp->down;                    
                }                
                cout<<"\n";
                temp = aux;
                temp= temp->right;
            }
            cout<< temp->x;
            cout<<"->";
            while(temp->down!=NULL){
                cout<<"("<<temp->down->coin->letter <<"," <<temp->down->coin->value<<")";
                cout<<"->";
                temp = temp->down;                    
            }   
            cout<<"\n";
        }

        //PRINT NODES IN Y- RAWS
        void print_nodes_y()        
        {
            NodeMatrix *temp = head->down;
            while(temp->down != NULL)
            {
                NodeMatrix *aux=temp;
                cout<<temp->y;
                cout<<"->";
                while(temp->right!=NULL){
                    cout<<"("<<temp->right->x<<","<<temp->right->y<<"/"<<temp->right->coin->letter <<"," <<temp->right->coin->value <<")";
                    cout<<"->";
                    temp = temp->right;                    
                }                   
                cout<<"\n";
                temp = aux;
                temp= temp->down;
            }
            cout<< temp->y;
            cout<<"->";
            while(temp->right!=NULL){
                cout<<"("<<temp->right->x<<","<<temp->right->y<<"/"<<temp->right->coin->letter <<"," <<temp->right->coin->value <<")";
                cout<<"->";
                temp = temp->right;                    
            }  
            cout<<"\n";            
        }
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+++++++++++++++++++++++++++++++++++++++++ GRAFICAR MATRIZ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

        void graficarMatriz(){
            NodeMatrix *tempCol = head;
            NodeMatrix *tempRaw = head;
            NodeMatrix *tempRawItera = head->down;               
            NodeMatrix *tempColItera = head->right;

            string rankSame ="{rank=same; MATRIZ";        
            string scriptGraphviz ="digraph{\n rankdir=TB;\n node[shape=rectangle];\n graph[nodesep=0.5];\n\n";                      
            scriptGraphviz+="MATRIZ";            
            scriptGraphviz+="->";
            /*********************************************************************************************************************/
            /*******************************Script que recorre las columnas para el dot*******************************************/
            /*********************************************************************************************************************/
            tempCol=tempCol->right;                       
            while(tempCol->right != NULL)
            {                
                scriptGraphviz +="C"+to_string(tempCol->x);
                rankSame+=" C"+to_string(tempCol->x);
                scriptGraphviz +="[dir=both];\n";
                scriptGraphviz +="C"+to_string(tempCol->x);
                scriptGraphviz +="->";                
                tempCol = tempCol->right;
            }  
            scriptGraphviz +="C"+to_string(tempCol->x);
            scriptGraphviz +="[dir=both];\n";
            rankSame+=" C"+to_string(tempCol->x);
            rankSame+=" }\n\n";
            scriptGraphviz+=rankSame; //concatena el script con la alineacion rankSame de las columnas
            rankSame = "";
            
            /*********************************************************************************************************************/
            /********************************Script que recorre las filas para el dot*********************************************/
            /*********************************************************************************************************************/
            scriptGraphviz+="MATRIZ";
            scriptGraphviz+="->";
            tempRaw=tempRaw->down;
            while(tempRaw->down != NULL)
            {                
                scriptGraphviz +="F"+to_string(tempRaw->y);
                scriptGraphviz +="[dir=both];\n";
                scriptGraphviz +="F"+to_string(tempRaw->y);
                scriptGraphviz +="->";                
                tempRaw = tempRaw->down;
            } 
            scriptGraphviz +="F"+to_string(tempRaw->y);
            scriptGraphviz +="[dir=both];\n\n"; //fin de recorrer las filas

            /*********************************************************************************************************************/
            /************************************SCRIPT POR CADA FILA DE LA MATRIZ************************************************/
            /*********************************************************************************************************************/
            while(tempRawItera->down!=NULL)
            {
                scriptGraphviz+="F"+to_string(tempRawItera->y);
                scriptGraphviz+="->";           
                rankSame+="{rank=same; ";
                rankSame+="F"+to_string(tempRawItera->y);                
                //imprime las listas de cada fila
                NodeMatrix *temp=tempRawItera->right;
                while (temp->right!=NULL)
                {
                    scriptGraphviz+="N"+to_string(temp->x)+to_string(temp->y);
                    scriptGraphviz+="[constraint=false,dir=both];\n";
                    scriptGraphviz+="N"+to_string(temp->x)+to_string(temp->y)+"[label=\""+temp->coin->letter+"\"];\n";
                    scriptGraphviz+="N"+to_string(temp->x)+to_string(temp->y);
                    scriptGraphviz+="->";
                    rankSame+=" N"+to_string(temp->x)+to_string(temp->y);
                    temp=temp->right;                    
                }
                scriptGraphviz+="N"+to_string(temp->x)+to_string(temp->y);
                scriptGraphviz+="[constraint=false,dir=both];\n";
                scriptGraphviz+="N"+to_string(temp->x)+to_string(temp->y)+"[label=\""+temp->coin->letter+"\"];\n";                
                rankSame+=" N"+to_string(temp->x)+to_string(temp->y);
                rankSame+=" }\n";
                scriptGraphviz+=rankSame+"\n";
                rankSame="";

                tempRawItera=tempRawItera->down;
            }
            scriptGraphviz+="F"+to_string(tempRawItera->y);
            scriptGraphviz+="->";           
            rankSame+="{rank=same; ";
            rankSame+="F"+to_string(tempRawItera->y);                
            //imprime las listas de cada fila
            NodeMatrix *temp=tempRawItera->right;
            while (temp->right!=NULL)
            {
                scriptGraphviz+="N"+to_string(temp->x)+to_string(temp->y);
                scriptGraphviz+="[constraint=false,dir=both];\n";
                scriptGraphviz+="N"+to_string(temp->x)+to_string(temp->y)+"[label=\""+temp->coin->letter+"\"];\n";
                scriptGraphviz+="N"+to_string(temp->x)+to_string(temp->y);
                scriptGraphviz+="->";
                rankSame+=" N"+to_string(temp->x)+to_string(temp->y);
                temp=temp->right;                    
            }
            scriptGraphviz+="N"+to_string(temp->x)+to_string(temp->y);
            scriptGraphviz+="[constraint=false,dir=both];\n";
            scriptGraphviz+="N"+to_string(temp->x)+to_string(temp->y)+"[label=\""+temp->coin->letter+"\"];\n";                
            rankSame+=" N"+to_string(temp->x)+to_string(temp->y);
            rankSame+=" }\n";
            scriptGraphviz+=rankSame+"\n";            
            rankSame="";  

            /*********************************************************************************************************************/
            /**********************************SCRIPT POR CADA COLUMNA DE LA MATRIZ***********************************************/
            /*********************************************************************************************************************/

            while(tempColItera->right!=NULL){
                scriptGraphviz+="C"+to_string(tempColItera->x);
                scriptGraphviz+="->";                           
                NodeMatrix *temp=tempColItera->down;
                while (temp->down!=NULL)
                {
                    scriptGraphviz+="N"+to_string(temp->x)+to_string(temp->y);
                    scriptGraphviz+="[dir=both];\n";                    
                    scriptGraphviz+="N"+to_string(temp->x)+to_string(temp->y);
                    scriptGraphviz+="->";                    
                    temp=temp->down;                    
                }
                scriptGraphviz+="N"+to_string(temp->x)+to_string(temp->y);
                scriptGraphviz+="[dir=both];\n\n";                
                tempColItera=tempColItera->right;
            }
            scriptGraphviz+="C"+to_string(tempColItera->x);
            scriptGraphviz+="->";                           
            NodeMatrix *temp_=tempColItera->down;
            while (temp_->down!=NULL)
            {
                scriptGraphviz+="N"+to_string(temp_->x)+to_string(temp_->y);
                scriptGraphviz+="[dir=both];\n";                    
                scriptGraphviz+="N"+to_string(temp_->x)+to_string(temp_->y);
                scriptGraphviz+="->";                    
                temp_=temp_->down;                    
            }                
            scriptGraphviz+="N"+to_string(temp_->x)+to_string(temp_->y);
            scriptGraphviz+="[dir=both];\n\n";                           
            scriptGraphviz+="}";
            ofstream myFile;
            myFile.open("SparseMatrix.dot");
            myFile<<scriptGraphviz;
            myFile.close();
            //Command for Ubuntu
            system("dot -Tpng SparseMatrix.dot -o SparseMatrix.png");
            system("shotwell SparseMatrix.png");
            //Command for Windows
            //const char* cmdCrear="dot -Tpng matrizDispersa.dot -o matrizDispersa.png";
            //const char* cmdExecute="cmd /c start matrizDispersa.png";
            //system(cmdCrear);
            //system(cmdExecute);

        }
};

/*****************************************************************************************************************
############################################# PRINCIPAL METHOD####################################################
******************************************************************************************************************/

/*
main()
{
    SparseMatrix *matrix = new SparseMatrix;
    NodeCoinMatrix* tp=new NodeCoinMatrix("O",2);    
    matrix->add(8,5,tp); //add(columna, fila, contenido)

    NodeCoinMatrix* tp2=new NodeCoinMatrix("S",4);    
    matrix->add(9,5,tp2);

    NodeCoinMatrix* tp3=new NodeCoinMatrix("H",5);    
    matrix->add(10,4,tp3);

    NodeCoinMatrix* tp4=new NodeCoinMatrix("O",9);    
    matrix->add(10,5,tp4);

    NodeCoinMatrix* tp5=new NodeCoinMatrix("L",6);    
    matrix->add(10,6,tp5);

    NodeCoinMatrix* tp6=new NodeCoinMatrix("A",3);    
    matrix->add(10,7,tp6);   

    NodeCoinMatrix* tp7=new NodeCoinMatrix("Z",5);    
    matrix->add(10,4,tp7);

    
    //matrix->printHeaders();
    //cout<<"\n";
    //cout<<"\n";
    //matrix->printNodes();
    matrix->graficarMatriz();
    return 0;
}*/