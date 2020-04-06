#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <algorithm> // std::shuffle
#include <array>     // std::array
#include <random>    // std::default_random_engine
#include <chrono>    // std::chrono::system_clock

//LIBRARIES FOR GRAPHIC ENVIRONMENT
#include <ncurses.h>
#include <unistd.h>
#include <limits.h>
//LIBRARIES FOR READ JSON FILE
#include <jsoncpp/json/json.h>
//EXPORT CLASSES
#include "Structures/DictionaryWords.cpp" //dictionary words, OPTION 0
#include "Structures/BoxDoubleValue.cpp"
#include "Structures/BoxTripleValue.cpp"
#include "Structures/QueueCoins.cpp" // coins available, OPTION 1
#include "Structures/UsersTree.cpp"  // player's tree, OPTION 2,3,4 AND 5
//#include "Structures/ScoreBoardIndividual.cpp" // player score history, OPTION 6
#include "Structures/ScoreBoardGeneral.cpp"    // General score history, OPTION 7
#include "Structures/SparseMatrix.cpp"         // Game Board, OPTION 8
#include "Structures/ListOfIndividualCoin.cpp" // player coins available, OPTION 9

using namespace std;
/******************************************************************
 * Compilation command to use "to_string" in UBUNTU 16.04LTS 
 * g++ -std=c++0x -o name_file_out  file_to_compile.cpp
 * 
 * -----------------------------------------------------------------
 * Compilation command to use "to_string" and "ncurses"
 * g++ -std=c++0x -o name_file_out  file_to_compile.cpp -lncurses
 * 
 * ----------------------------------------------------------------- 
 * Compilation command to use "jsoncpp"
 * g++ file_to_compile.cpp -o name_file_out -ljsoncpp
 * 
 * -----------------------------------------------------------------
 * Compilation command to use "to_string", "ncurses" and "jsoncpp" * 
 * g++ -std=c++0x -o salida main.cpp -lncurses -ljsoncpp
 * ****************************************************************
 * */

//Instances of classes used in program
ListWords *dictionarywords = new ListWords(); //add words to dictionary from input file
BoxDouble *boxdouble = new BoxDouble();       // add box double
BoxTriple *boxdtriple = new BoxTriple();      //add box triple
QueueCoin *queeucoins = new QueueCoin();      //add coind to the game board
TreePlayer *treeplayer = new TreePlayer();    //add new player
//pendiente para cada jugador, podria ser una lista para cada jugador en el arbol, como un atributo de cada nodo
//ScoreboardIndividual *individualscore = new ScoreboardIndividual(); //add score for
ScoreboardGeneral *generalscore = new ScoreboardGeneral(); //add players and their scores
SparseMatrix *matrix = new SparseMatrix();                 // game board

ListCoinPLayer *listPlayer1Coins = new ListCoinPLayer(); // coins player 1
ListCoinPLayer *listPlayer2Coins = new ListCoinPLayer(); // coind player 2

NodeTree *player1 = new NodeTree();
NodeTree *player2 = new NodeTree();

//Variables used

//dimension matrix
int dimensionMatrix = 0;

//score per player
int score_player1_global = 0;
int score_player2_global = 0;

//num coins in list
int numCoinsPlayer1 = 0;
int numCoinsPlayer2 = 0;

//name per player
string name_player1_global;
string name_player2_global;

//boton de finalizar y pausa
int button_pause=0;
string word_entered_player1_global="";

//Definition of functions
void startMenu();
void windowReadFile();
void windowStartGame();
void windowReports();
void exitGame();
bool readJSON(string);
void newPlayer1();
void newPlayer2();
void playerExists1();
void playerExists2();
void askplayer2();
void screenGameInterface();
void assignCoinsPlayer1();
void assignCoinsPlayer2();
void fillQueue();
void iniciarCoordenada();
int verificarLetraListPLayer1(int);
void dibujarEnMatriz(int, int, int);

//********************************************************************************
//*************************  START MENU  *****************************************
//********************************************************************************
void startMenu()
{
    //clean screen
    clear();
    //postion x to center menu
    int x = 22;
    //menu header
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLUE);   //text red, background blue
    init_pair(2, COLOR_WHITE, COLOR_BLUE);   //text white, background blue
    init_pair(3, COLOR_YELLOW, COLOR_BLUE);  //text yellow, background blue
    init_pair(4, COLOR_MAGENTA, COLOR_BLUE); //text magenta, background blue // it's ok
    init_pair(5, COLOR_RED, COLOR_BLUE);     //text red, background blue  // it's wrong
    bkgd(COLOR_PAIR(1));

    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(3, 20, "===============================================");
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(4, 35, "MENU DE JUEGO");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(5, 20, "===============================================");
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(2));
    mvprintw(6, x, "1. Leer Archivo");
    mvprintw(7, x, "2. Jugar");
    mvprintw(8, x, "3. Reportes");
    mvprintw(9, x, "4. Salir");
    mvprintw(11, x, "Seleccione un numero de opcion(1-4): ");
    refresh();
    //get key enter by user
    int inputkey = getch();

    //option 1, goes window that read file for configure to game
    if (inputkey == '1')
    {
        windowReadFile();
    }
    //option 2, start game
    else if (inputkey == '2')
    {
        windowStartGame();
    }
    //option 3, show reports menu
    else if (inputkey == '3')
    {
        windowReports();
    }
    //option 4, exit game
    else if (inputkey == '4')
    {
        exitGame();
    }
    //if key is any option, stay in menu
    else
    {
        startMenu();
    }
}

//********************************************************************************
//*************************  REQUEST FILE NAME  **********************************
//********************************************************************************
void windowReadFile()
{
    clear();
    int x = 22;
    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(3, 20, "===============================================");
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(4, 27, "ABRIR ARCHIVO DE CONFIGURACION");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(5, 20, "===============================================");
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(2));
    mvprintw(6, x, "Nombre de Archivo (ejemplo: entrada.json)");
    mvprintw(7, x, "");
    refresh();

    //read character of keyboard
    bool flag = true;
    int key;
    int column = 22;
    string file_name_enter;
    while (flag)
    {
        //get key enter by user
        key = getch();
        if (key == 27) //ESC return to menu
        {
            startMenu();
        }
        else if (key == 10)
        {
            if (readJSON(file_name_enter))
            {
                attron(COLOR_PAIR(4));
                mvprintw(9, 27, "!!.ARCHIVO CARGADO CON EXITO.!!");
                mvprintw(10, 25, "Presione una tecla para continuar....");
                refresh();
                attroff(COLOR_PAIR(4));
                getch();
                startMenu();
            }
            else
            {
                attron(COLOR_PAIR(5));
                mvprintw(9, 27, "!!!ERROR, ARCHIVO NO EXISTE!!!");
                mvprintw(10, 25, "Presione una tecla para continuar....");
                refresh();
                attroff(COLOR_PAIR(5));
                getch();
                //clean message ERROR, file name and continue message of the screen
                for (int i = 0; i < 70; i++)
                {
                    mvaddch(7, i, 32);
                    mvaddch(9, i, 32);
                    mvaddch(10, i, 32);
                    refresh();
                }
                //clean concatenation variable
                file_name_enter = "";
                column = 22;
                //return cursor
                mvprintw(7, x, "");
                refresh();
            }
        }
        else
        {
            file_name_enter += char(key);
            mvaddch(7, column, key);
            refresh();
            column++;
        }
    }
}

//#################################################################################################################
//################################# START GAME PROGRAM ############################################################
//#################################################################################################################

//********************************************************************************
//*************************  START GAME  *****************************************
//********************************************************************************
void windowStartGame()
{
    clear();
    //postion x to center menu
    int x = 18;
    //menu header
    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(3, x, "===============================================");
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(4, 30, "INICIO DEL JUEGO");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(5, x, "===============================================");
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(5) | A_BOLD);
    mvprintw(6, 33, "Jugador 1 ");
    attroff(COLOR_PAIR(5));

    attron(COLOR_PAIR(2) | A_BOLD);
    mvprintw(8, x, "1. Nuevo Jugador");
    mvprintw(9, x, "2. Jugador ya registrado");
    mvprintw(10, x, "3. Regresar");
    mvprintw(12, x, "Seleccione una opcion: ");
    mvprintw(13, x, "");
    refresh();
    //get key enter by user
    int inputkey = getch();

    if (inputkey == '1')
    {
        newPlayer1();
    }
    else if (inputkey == '2')
    {
        playerExists1();
    }
    else if (inputkey == '3')
    {
        startMenu();
    }
    else
    {
        windowStartGame();
    }
}

//*************************************************
//function to add new player to Scrabble
//*************************************************
void newPlayer1()
{
    clear();
    //postion x to center menu
    int x = 18;
    //menu header
    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(3, x, "===============================================");
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(4, 30, "Nuevo Jugador 1");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(5, x, "===============================================");
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(2) | A_BOLD);
    //mvprintw(6, 33, "Jugador 1 ");
    mvprintw(23, x, "ESC - Regresar a Menu Inicio");
    mvprintw(7, x, "Ingrese nombre de jugador:");
    mvprintw(8, x, "");
    refresh();

    //read character of keyboard
    bool flag = true;
    int key;
    int column = 18;
    string name_player1;
    while (flag)
    {
        //get key enter by user
        key = getch();
        if (key == 27) //ESC return to menu
        {
            startMenu();
        }
        else if (key == 10)
        {
            if (treeplayer->serchPlayer(name_player1) == 1) //name already exist
            {
                attron(COLOR_PAIR(5)); //color red
                mvprintw(10, x, "!!.Nombre de Jugador ya existe.!!");
                mvprintw(11, x, "Presione una tecla para ingresar otro nombre....");
                refresh();
                attroff(COLOR_PAIR(5));
                getch();
                for (int i = 0; i < 70; i++)
                {
                    mvaddch(10, i, 32);
                    mvaddch(11, i, 32);
                    refresh();
                }
                name_player1 = "";
                column = 18;
                newPlayer1();
            }
            else
            {
                treeplayer->addPlayer(name_player1);
                name_player1_global = name_player1;
                attron(COLOR_PAIR(5));
                mvprintw(10, x, "!! Nombre de Jugador Valido !!");
                mvprintw(11, x, "Presione una tecla para continuar...");
                refresh();
                attroff(COLOR_PAIR(5));
                getch();
                askplayer2();
            }
        }
        else
        {
            name_player1 += char(key);
            mvaddch(8, column, key);
            refresh();
            column++;
        }
    }
}

void askplayer2()
{
    clear();
    //postion x to center menu
    int x = 18;
    //menu header
    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(3, x, "===============================================");
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(4, 30, "INICIO DEL JUEGO");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(5, x, "===============================================");
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(5) | A_BOLD);
    mvprintw(6, 33, "Jugador 2 ");
    attroff(COLOR_PAIR(5));

    attron(COLOR_PAIR(2));
    mvprintw(8, x, "1. Nuevo Jugador");
    mvprintw(9, x, "2. Jugador ya registrado");
    mvprintw(10, x, "3. Regresar");
    mvprintw(12, x, "Seleccione una opcion: ");
    mvprintw(13, x, "");
    refresh();
    //get key enter by user
    int inputkey = getch();

    if (inputkey == '1')
    {
        newPlayer2();
    }
    else if (inputkey == '2')
    {
        playerExists2();
    }
    else if (inputkey == '3')
    {
        startMenu();
    }
    else
    {
        askplayer2();
    }
}

void newPlayer2()
{
    clear();
    //postion x to center menu
    int x = 18;
    //menu header
    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(3, x, "===============================================");
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(4, 30, "Nuevo Jugador 2");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(5, x, "===============================================");
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(2) | A_BOLD);
    //mvprintw(6, 33, "Jugador 1 ");
    mvprintw(23, x, "ESC - Regresar a Menu Inicio");
    mvprintw(7, x, "Ingrese nombre de jugador:");
    mvprintw(8, x, "");
    refresh();

    //read character of keyboard
    bool flag = true;
    int key;
    int column = 18;
    string name_player2;
    while (flag)
    {
        //get key enter by user
        key = getch();
        if (key == 27) //ESC return to menu
        {
            startMenu();
        }
        else if (key == 10)
        {
            if (treeplayer->serchPlayer(name_player2) == 1) //name already exist
            {
                attron(COLOR_PAIR(5)); //color red
                mvprintw(10, x, "!!.Nombre de Jugador ya existe.!!");
                mvprintw(11, x, "Presione una tecla para ingresar otro nombre....");
                refresh();
                attroff(COLOR_PAIR(5));
                getch();
                for (int i = 0; i < 70; i++)
                {
                    mvaddch(10, i, 32);
                    mvaddch(11, i, 32);
                    refresh();
                }
                name_player2 = "";
                column = 18;
                newPlayer2();
            }
            else
            {
                treeplayer->addPlayer(name_player2);
                name_player2_global = name_player2;
                attron(COLOR_PAIR(5));
                mvprintw(10, x, "!! Usuario Valido !!");
                mvprintw(11, x, "Presione una tecla para continuar...");
                refresh();
                attroff(COLOR_PAIR(5));
                getch();
                queeucoins->clearOut();
                fillQueue();
                numCoinsPlayer1=0;
                numCoinsPlayer2=0;
                listPlayer1Coins->clearOut();          
                listPlayer2Coins->clearOut();          
                assignCoinsPlayer1();  
                assignCoinsPlayer2();
                screenGameInterface(); //start game interface
            }
        }
        else
        {
            name_player2 += char(key);
            mvaddch(8, column, key);
            refresh();
            column++;
        }
    }
}

//*************************************************
//function to select player exist
//*************************************************
void playerExists1()
{
    clear();
    //postion x to center menu
    int x = 18;
    //menu header
    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(3, x, "===============================================");
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(4, 35, "Jugador 1");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(5, x, "===============================================");
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(2) | A_BOLD);
    //mvprintw(6, 33, "Jugador 1 ");
    mvprintw(23, x, "ESC - Regresar a Menu Inicio");
    mvprintw(7, x, "Ingrese nombre para cargar su Usuario:");
    mvprintw(8, x, "");
    refresh();

    //read character of keyboard
    bool flag = true;
    int key;
    int column = 18;
    string name_player1_exist;
    while (flag)
    {
        //get key enter by user
        key = getch();
        if (key == 27) //ESC return to menu
        {
            startMenu();
        }
        else if (key == 10)
        {
            if (treeplayer->serchPlayer(name_player1_exist) == 1) //name already exist
            {
                name_player1_global = treeplayer->getName(name_player1_exist);
                attron(COLOR_PAIR(3));                               //color yellow
                mvprintw(10, x, "Bienvenido a una nueva partida, "); //empezar en la 50 en x
                int a = 50;
                char name[name_player1_global.length()];
                for (int i = 0; i < sizeof(name); i++)
                {
                    name[i] = name_player1_global[i];
                    mvaddch(10, a, name[i]);
                    refresh();
                    a++;
                }
                mvprintw(11, x, "Presione una tecla para continuar....");
                refresh();
                getch();
                askplayer2();
            }
            else
            {
                attron(COLOR_PAIR(5)); //color red
                mvprintw(10, x, "!!.. Nombre No Encontrado ..!!");
                mvprintw(11, x, "Presione una tecla para intentar de nuevo....");
                refresh();
                attroff(COLOR_PAIR(5));
                getch();
                name_player1_exist = "";
                column = 18;
                playerExists1();
            }
        }
        else
        {
            name_player1_exist += char(key);
            mvaddch(8, column, key);
            refresh();
            column++;
        }
    }
}

void playerExists2()
{
    clear();
    //postion x to center menu
    int x = 18;
    //menu header
    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(3, x, "===============================================");
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(4, 35, "Jugador 2");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(5, x, "===============================================");
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(2) | A_BOLD);
    //mvprintw(6, 33, "Jugador 1 ");
    mvprintw(23, x, "ESC - Regresar a Menu Inicio");
    mvprintw(7, x, "Ingrese nombre para cargar su Usuario:");
    mvprintw(8, x, "");
    refresh();

    //read character of keyboard
    bool flag = true;
    int key;
    int column = 18;
    string name_player2_exist;
    while (flag)
    {
        //get key enter by user
        key = getch();
        if (key == 27) //ESC return to menu
        {
            startMenu();
        }
        else if (key == 10)
        {
            if (treeplayer->serchPlayer(name_player2_exist) == 1) //name already exist
            {
                name_player2_global = treeplayer->getName(name_player2_exist);
                attron(COLOR_PAIR(3));                               //color yellow
                mvprintw(10, x, "Bienvenido a una nueva partida, "); //empezar en la 50 en x
                int a = 50;
                char name[name_player2_global.length()];
                for (int i = 0; i < sizeof(name); i++)
                {
                    name[i] = name_player2_global[i];
                    mvaddch(10, a, name[i]);
                    refresh();
                    a++;
                }
                mvprintw(11, x, "Presione una tecla para continuar....");
                refresh();
                getch();
                queeucoins->clearOut();
                fillQueue();
                numCoinsPlayer1=0;
                numCoinsPlayer2=0;     
                listPlayer1Coins->clearOut();          
                listPlayer2Coins->clearOut();          
                assignCoinsPlayer1(); 
                assignCoinsPlayer2();
                screenGameInterface(); //start game interface
            }
            else
            {
                attron(COLOR_PAIR(5)); //color red
                mvprintw(10, x, "!!.. Nombre No Encontrado ..!!");
                mvprintw(11, x, "Presione una tecla para intentar de nuevo....");
                refresh();
                attroff(COLOR_PAIR(5));
                getch();
                name_player2_exist = "";
                column = 18;
                playerExists2();
            }
        }
        else
        {
            name_player2_exist += char(key);
            mvaddch(8, column, key);
            refresh();
            column++;
        }
    }
}

//*************************************************
//fill list of players
//*************************************************

void assignCoinsPlayer1()
{    
    string letter;
    int value;
    while (numCoinsPlayer1 < 7)
    {
        if (queeucoins->numElements() == 0)
        {
            break;
        }
        else
        {
            NodeCoinQueue *res = queeucoins->dequeueCoin();
            letter = res->letter;
            value = res->value;
            listPlayer1Coins->addCoin(letter, value);
            numCoinsPlayer1++;
        }
    }        
}

void assignCoinsPlayer2()
{    
    string letter;
    int value;
    while (numCoinsPlayer2 < 7)
    {
        if (queeucoins->numElements() == 0)
        {
            break;
        }
        else
        {
            NodeCoinQueue *res = queeucoins->dequeueCoin();
            letter = res->letter;
            value = res->value;
            listPlayer2Coins->addCoin(letter, value);
            numCoinsPlayer2++;
        }
    }    
}

//*************************************************
//Game Interface
//*************************************************
void screenGameInterface()
{
    clear();
    //postion x to center menu
    int x = 18;
    //menu header
    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(0, 0, "================================================================================");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(5) | A_BOLD);
    mvprintw(1, 34, "SCRABBLE");
    attroff(COLOR_PAIR(5));

    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(2, 0, "================================================================================");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(5) | A_BOLD);
    mvprintw(23, 0, "ESC - Finalizar Partida");
    attroff(COLOR_PAIR(4));

    attron(COLOR_PAIR(5) | A_BOLD);
    mvprintw(23, 35, "F1 - Pausar Partida e ir al Menu Principal");
    attroff(COLOR_PAIR(4));

    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(4, 0, "Turno de: ");
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(2) | A_BOLD);
    int a = 10;
    char name[name_player1_global.length()];
    for (int i = 0; i < sizeof(name); i++)
    {
        name[i] = name_player1_global[i];
        mvaddch(4, a, name[i]);
        refresh();
        a++;
    }
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(5, 0, "Punteo: ");
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(2) | A_BOLD);
    string punteo1 = to_string(score_player1_global);
    a = 8;
    char name2[punteo1.length()];
    for (int i = 0; i < sizeof(name2); i++)
    {
        name2[i] = punteo1[i];
        mvaddch(5, a, name2[i]);
        refresh();
        a++;
    }
    attroff(COLOR_PAIR(2));


    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(6, 0, "Fichas Disponibles: ");
    attron(COLOR_PAIR(2) | A_BOLD);
    int b = 20; //espacio de 3
    
    if (listPlayer1Coins->isEmpty())
    {
        mvprintw(23, 25, "No hay Fichas Disponibles ");
        refresh();
    }
    else
    {
        NodeCoin *aux = listPlayer1Coins->first;
        if (listPlayer1Coins->first->next == NULL)
        {
            mvaddch(6, b, listPlayer1Coins->first->letter[0]);
            refresh();
            b+=3;
        }
        while (aux->next != NULL)
        {
            if (aux == listPlayer1Coins->first)
            {
                mvaddch(6, b, aux->letter[0]);
                refresh();
                b+=3;
            }
            else
            {
                mvaddch(6, b, aux->letter[0]);
                refresh();
                b+=3;
            }
            aux = aux->next;
        }
        if (aux != listPlayer1Coins->first)
        {
            mvaddch(6, b, aux->letter[0]);
            refresh();
            b+=3;
        }
    }
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(8, 0, "Ingrese Palabra que desea Jugar, Usando las fichas disponibles: ");
    mvprintw(9,0,"");
    attroff(COLOR_PAIR(3));
    refresh();
    
    bool bool_verificar_letra=true;
    bool flag = true;
    int key;
    int column = 0;
    string word_entered;
    while (flag)
    {
        //get key enter by user
        key = getch();
        if (key == 27) //ESC return to menu
        {
            startMenu();
        }
        else if (key==KEY_F(1))
        {            
            button_pause=1;   
            startMenu();            
        }        
        else if (key == 10)
        {
            bool resp = dictionarywords->checkWord(word_entered);
            if((resp==true) && (bool_verificar_letra==true))
            {
                word_entered_player1_global = word_entered;                
                attron(COLOR_PAIR(4) | A_BOLD);
                mvprintw(11, 25, "Palabra Correcta");                                
                refresh();
                attroff(COLOR_PAIR(4));
                getch();
                for (int i = 0; i < 70; i++)
                {                    
                    mvaddch(11, i, 32);
                    refresh();
                }
                iniciarCoordenada();
                //screenGameInterface();
            }
            else
            {
                attron(COLOR_PAIR(4) | A_BOLD);
                mvprintw(11, 10, "Palabra NO Existe o Letras Insuficientes");
                mvprintw(12, 10, "Presione una tecla para intentar de nuevo...");
                refresh();
                attroff(COLOR_PAIR(4));
                getch();
                screenGameInterface();                
            }
        }
        else
        {
            if(verificarLetraListPLayer1(key)==0)
            {
                bool_verificar_letra=false; //letra no existe
            }
            attron(COLOR_PAIR(2) | A_BOLD);
            word_entered += char(key);
            mvaddch(9, column, key);
            refresh();
            column++;
            attroff(COLOR_PAIR(2));
        }
    }
}

int verificarLetraListPLayer1(int letra)
{
    int x=letra;
    char c = static_cast<char>(x);
    int res=0;
    if(listPlayer1Coins->checkLetter(c)==1)
    {
        //letra existe
        res=1;
    }
    else
    {
        res=0;
        //letra no existe
    }
    return res;
}


void iniciarCoordenada()
{
    int pos_x=0;
    int pos_y=0;
    //limpiar las lineas de informacion
    for (int i = 0; i < 70; i++)
    {
        mvaddch(11, i, 32);
        mvaddch(12, i, 32);
        mvaddch(13, i, 32);
        mvaddch(14, i, 32);
        mvaddch(15, i, 32);
        refresh();
    }

    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(11, 0, "Coordenada de Inicio, (Coordenada Maxima: ");                   
    
    string dimension = to_string(dimensionMatrix);
    int j = 42;
    char name2[dimension.length()];
    for (int i = 0; i < sizeof(name2); i++)
    {
        name2[i] = dimension[i];
        mvaddch(11, j, name2[i]);
        refresh();
        j++;
    }
    mvaddch(11, j,')');       
    mvprintw(12, 0, "Coordenada X (Fila): ");     
    refresh();
    attroff(COLOR_PAIR(3));
    
    //pedir coordenada en x
    bool flag = true;
    int key;
    int column = 21;
    string pos_entered="";
    //string word_entered="123";
    //key = stoi(word_entered); convert string to int
    while (flag)
    {
        //get key enter by user
        key = getch();
        if (key == 10) 
        {
            pos_x=stoi(pos_entered);            
            flag=false;
        }    
        else if(key>=48 && key<=57)    
        {
            attron(COLOR_PAIR(2) | A_BOLD);
            pos_entered += char(key);
            mvaddch(12, column, key);
            refresh();
            column++;
            attroff(COLOR_PAIR(2));
        }
        else
        {
            flag=true;
        }
    }

    attron(COLOR_PAIR(3) | A_BOLD);
    //pedir coordenada en x
    mvprintw(13, 0, "Coordenada Y (Columna): ");       
    refresh();
    attroff(COLOR_PAIR(3));
    flag = true;     
    column = 24;
    pos_entered="";
    //string word_entered="123";
    //key = stoi(word_entered); convert string to int
    while (flag)
    {
        //get key enter by user
        key = getch();
        if (key == 10) //ESC return to menu
        {
            pos_y=stoi(pos_entered);            
            flag=false;
        }   
        else if(key>=48 && key<=57)    
        {
            attron(COLOR_PAIR(2) | A_BOLD);
            pos_entered += char(key);
            mvaddch(13, column, key);
            refresh();
            column++;
            attroff(COLOR_PAIR(2));
        }
        else
        {
            flag=true;
        }     
    }

    //comparar los valores ingresados con el valor de la matriz
    if(pos_x<=dimensionMatrix && pos_y<=dimensionMatrix)
    {
        attron(COLOR_PAIR(4) | A_BOLD);
        mvprintw(14, 20, "Coordenada de Inicio Valida");               
        refresh();        
        attroff(COLOR_PAIR(4));
        
        attron(COLOR_PAIR(3) | A_BOLD);
        mvprintw(15, 0, "(H) Horizontal *** (V) Vertical:");       
        attroff(COLOR_PAIR(3));
        
        int posic=0; // 0 = horizontal; 1=vertical
        attron(COLOR_PAIR(3) | A_BOLD);
        mvprintw(15, 34, "");       
        refresh();                
        int key12 = getch();   

        if(key12== 72 || key12==104) // h
        {
            posic=0;
            mvaddch(15, 34, 72);
            refresh();
            getch();
        }
        if(key12==86 || key12==118) //v
        {
            posic=1;
            mvaddch(15, 34, 86);
            refresh();
            getch();
        }
        dibujarEnMatriz(pos_x, pos_y, posic);        
    }   
    else
    {
        attron(COLOR_PAIR(4) | A_BOLD);
        mvprintw(14, 20, "Coordenadas Sobrepasan el Limite");       
        refresh();
        attroff(COLOR_PAIR(4));
        getch();
        iniciarCoordenada();
    } 

    //validar la coordenada de inicio
    //screenGameInterface();
}

void dibujarEnMatriz(int fila, int columna, int posicionPalabra)
{       
    char word[word_entered_player1_global.length()];    
    if(posicionPalabra==0)// palabra horizontal
    {
        for (int i = 0; i < sizeof(word); i++)
        {
            word[i] = word_entered_player1_global[i];
            NodeCoinMatrix *letra = new NodeCoinMatrix();
            letra->letter=word[i];            
            //verificar cada coordenada y ver si es triple o doble
            //sacar letras de la lista
            //sumas punteo
            matrix->add(columna+i,fila,letra); //primero va columna, luego fila
        }       
        
    }
    else
    {
        for (int i = 0; i < sizeof(word); i++)
        {
            word[i] = word_entered_player1_global[i];
            NodeCoinMatrix *letra = new NodeCoinMatrix();
            letra->letter=word[i];            
            matrix->add(columna,fila+i,letra); //primero va columna, luego fila
        }
    }  
    matrix->graficarMatriz();
}


//#################################################################################################################
//################################# END GAME PROGRAM ##############################################################
//#################################################################################################################

//********************************************************************************
//*************************  DATA STRUCTURE REPORT  ******************************
//********************************************************************************
void windowReports()
{
    clear();
    int x = 7;
    attron(COLOR_PAIR(3));
    mvprintw(1, 7, "================================================================");
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(2, 30, "REPORTES");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(3));
    mvprintw(3, 7, "================================================================");
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(5));
    mvprintw(23, x, "ESC - Regresar al Menu Principal");
    attroff(COLOR_PAIR(5));
    attron(COLOR_PAIR(2));
    mvprintw(4, x, "0) Lista Doblemente Enlazada Circular: Diccionario");
    mvprintw(5, x, "1) Cola: Fichas disponibles del juego");
    mvprintw(6, x, "2) Arbol Binario de Busqueda: Jugadores");
    mvprintw(7, x, "3) Recorrido Preorden del ABB");
    mvprintw(8, x, "4) Recorrido Inorden del ABB");
    mvprintw(9, x, "5) Recorrido Postorden del ABB");
    mvprintw(10, x, "6) Lista Simple Ordenada: Historial de Puntaje Por Jugador");
    mvprintw(11, x, "7) Lista SImple Ordenada: Scoreboard");
    mvprintw(12, x, "8) Matriz Dispersa: Tablero");
    mvprintw(13, x, "9) Listas Doblemente Enlazadas: Fichas por Jugador");
    attron(COLOR_PAIR(3));
    mvprintw(14, x, "===============================================================");
    attroff(COLOR_PAIR(3));
    mvprintw(15, x, "Seleccione un numero para ver reporte:  ");
    attron(COLOR_PAIR(3));
    mvprintw(16, x, "===============================================================");
    attroff(COLOR_PAIR(3));
    mvprintw(15, 46, "");
    refresh();
    int key = getch();
    if (key == 27)
    {
        startMenu();
    }
    //print dictionary words, OPTION 0
    else if (key == 48)
    {
        if (dictionarywords->isEmpty())
        {
            //clean information line
            for (int i = 0; i < 70; i++)
            {
                mvaddch(18, i, 32);
                mvaddch(19, i, 32);
                refresh();
            }
            attron(COLOR_PAIR(5));
            mvprintw(18, x, "Diccionario de Palabras Vacio");
            mvprintw(19, x, "Presione una tecla para continuar....");
            mvprintw(15, 46, "");
            refresh();
            attroff(COLOR_PAIR(5));
            getch();
            //clean information line
            for (int i = 0; i < 70; i++)
            {
                mvaddch(18, i, 32);
                mvaddch(19, i, 32);
                refresh();
            }
            windowReports();
        }
        else
        {
            //clean information line
            for (int i = 0; i < 70; i++)
            {
                mvaddch(18, i, 32);
                refresh();
            }
            attron(COLOR_PAIR(5));
            mvprintw(18, x, "Diccionario de Palabras Mostrado con Exito");
            mvprintw(15, 46, "");
            refresh();
            attroff(COLOR_PAIR(5));
            //show graphic
            dictionarywords->graphDictinary();
            //return report menu
            windowReports();
        }
    }
    //print game's queue coins, OPTON 1
    else if (key == 49)
    {
        if (queeucoins->isEmpty())
        {
            //clean information line
            for (int i = 0; i < 70; i++)
            {
                mvaddch(18, i, 32);
                mvaddch(19, i, 32);
                refresh();
            }
            attron(COLOR_PAIR(5));
            mvprintw(18, x, "Cola De Fichas Vacia");
            mvprintw(19, x, "Presione una tecla para continuar....");
            mvprintw(15, 46, "");
            refresh();
            attroff(COLOR_PAIR(5));
            getch();
            //clean information line
            for (int i = 0; i < 70; i++)
            {
                mvaddch(18, i, 32);
                mvaddch(19, i, 32);
                refresh();
            }
            windowReports();
        }
        else
        {
            //clean information line
            for (int i = 0; i < 70; i++)
            {
                mvaddch(18, i, 32);
                refresh();
            }
            attron(COLOR_PAIR(5));
            mvprintw(18, x, "Cola De Fichas Mostrado con Exito");
            mvprintw(15, 46, "");
            refresh();
            attroff(COLOR_PAIR(5));
            //show graphic
            queeucoins->graphQueue();
            //return report menu
            windowReports();
        }
    }
    //show BST Tree, OPTION 2
    else if (key == 50)
    {
        if (treeplayer->isEmpty())
        {
            //clean information line
            for (int i = 0; i < 70; i++)
            {
                mvaddch(18, i, 32);
                mvaddch(19, i, 32);
                refresh();
            }
            attron(COLOR_PAIR(5));
            mvprintw(18, x, "Arbol de jugadores Vacio");
            mvprintw(19, x, "Presione una tecla para continuar....");
            mvprintw(15, 46, "");
            refresh();
            attroff(COLOR_PAIR(5));
            getch();
            //clean information line
            for (int i = 0; i < 70; i++)
            {
                mvaddch(18, i, 32);
                mvaddch(19, i, 32);
                refresh();
            }
            windowReports();
        }
        else
        {
            //clean information line
            for (int i = 0; i < 70; i++)
            {
                mvaddch(18, i, 32);
                refresh();
            }
            attron(COLOR_PAIR(5));
            mvprintw(18, x, "Arbol de Jugadores Mostrado con Exito");
            mvprintw(15, 46, "");
            refresh();
            attroff(COLOR_PAIR(5));
            //show graphic
            treeplayer->graphUsersTree();
            //return report menu
            windowReports();
        }
    }
    //show preorder traversal, OPTION 3
    else if (key == 51)
    {
        if (treeplayer->isEmpty())
        {
            //clean information line
            for (int i = 0; i < 70; i++)
            {
                mvaddch(18, i, 32);
                mvaddch(19, i, 32);
                refresh();
            }
            attron(COLOR_PAIR(5));
            mvprintw(18, x, "Arbol de jugadores Vacio");
            mvprintw(19, x, "Presione una tecla para continuar....");
            mvprintw(15, 46, "");
            refresh();
            attroff(COLOR_PAIR(5));
            getch();
            //clean information line
            for (int i = 0; i < 70; i++)
            {
                mvaddch(18, i, 32);
                mvaddch(19, i, 32);
                refresh();
            }
            windowReports();
        }
        else
        {
            //clean information line
            for (int i = 0; i < 70; i++)
            {
                mvaddch(18, i, 32);
                refresh();
            }
            attron(COLOR_PAIR(5));
            mvprintw(18, x, "Recorrido Preorden Generado con Exito");
            mvprintw(15, 46, "");
            refresh();
            attroff(COLOR_PAIR(5));
            //show graphic
            treeplayer->graphPreOrderTraverse();
            //return report menu
            windowReports();
        }
    }
    //show inorder traversal, OPTION 4
    else if (key == 52)
    {
        if (treeplayer->isEmpty())
        {
            //clean information line
            for (int i = 0; i < 70; i++)
            {
                mvaddch(18, i, 32);
                mvaddch(19, i, 32);
                refresh();
            }
            attron(COLOR_PAIR(5));
            mvprintw(18, x, "Arbol de jugadores Vacio");
            mvprintw(19, x, "Presione una tecla para continuar....");
            mvprintw(15, 46, "");
            refresh();
            attroff(COLOR_PAIR(5));
            getch();
            //clean information line
            for (int i = 0; i < 70; i++)
            {
                mvaddch(18, i, 32);
                mvaddch(19, i, 32);
                refresh();
            }
            windowReports();
        }
        else
        {
            //clean information line
            for (int i = 0; i < 70; i++)
            {
                mvaddch(18, i, 32);
                refresh();
            }
            attron(COLOR_PAIR(5));
            mvprintw(18, x, "Recorrido Inrden Generado con Exito");
            mvprintw(15, 46, "");
            refresh();
            attroff(COLOR_PAIR(5));
            //show graphic
            treeplayer->graphInOrderTraverse();
            //return report menu
            windowReports();
        }
    }
    //show postorder traversal. OPTION 5
    else if (key == 53)
    {
        if (treeplayer->isEmpty())
        {
            //clean information line
            for (int i = 0; i < 70; i++)
            {
                mvaddch(18, i, 32);
                mvaddch(19, i, 32);
                refresh();
            }
            attron(COLOR_PAIR(5));
            mvprintw(18, x, "Arbol de jugadores Vacio");
            mvprintw(19, x, "Presione una tecla para continuar....");
            mvprintw(15, 46, "");
            refresh();
            attroff(COLOR_PAIR(5));
            getch();
            //clean information line
            for (int i = 0; i < 70; i++)
            {
                mvaddch(18, i, 32);
                mvaddch(19, i, 32);
                refresh();
            }
            windowReports();
        }
        else
        {
            //clean information line
            for (int i = 0; i < 70; i++)
            {
                mvaddch(18, i, 32);
                refresh();
            }
            attron(COLOR_PAIR(5));
            mvprintw(18, x, "Recorrido Postorden Generado con Exito");
            mvprintw(15, 46, "");
            refresh();
            attroff(COLOR_PAIR(5));
            //show graphic
            treeplayer->graphPosOrderTraverse();
            //return report menu
            windowReports();
        }
    }
    //show individual score, OPTION 6
    else if (key == 54)
    {
        //pending
    }
    //show general score, OPTION 7
    else if (key == 55)
    {
        if (generalscore->isEmpty())
        {
            //clean information line
            for (int i = 0; i < 70; i++)
            {
                mvaddch(18, i, 32);
                mvaddch(19, i, 32);
                refresh();
            }
            attron(COLOR_PAIR(5));
            mvprintw(18, x, "Puntaje General Vacio");
            mvprintw(19, x, "Presione una tecla para continuar....");
            mvprintw(15, 46, "");
            refresh();
            attroff(COLOR_PAIR(5));
            getch();
            //clean information line
            for (int i = 0; i < 70; i++)
            {
                mvaddch(18, i, 32);
                mvaddch(19, i, 32);
                refresh();
            }
            windowReports();
        }
        else
        {
            //clean information line
            for (int i = 0; i < 70; i++)
            {
                mvaddch(18, i, 32);
                refresh();
            }
            attron(COLOR_PAIR(5));
            mvprintw(18, x, "Puntaje General Mostrado con Exito");
            mvprintw(15, 46, "");
            refresh();
            attroff(COLOR_PAIR(5));
            //show graphic
            generalscore->graphScoreGeneral();
            //return report menu
            windowReports();
        }
    }
    //show game board, OPTION 8
    else if (key == 56)
    {
        if (matrix->isEmpty())
        {
            //clean information line
            for (int i = 0; i < 70; i++)
            {
                mvaddch(18, i, 32);
                mvaddch(19, i, 32);
                refresh();
            }
            attron(COLOR_PAIR(5));
            mvprintw(18, x, "Tablero de Juego Vacio");
            mvprintw(19, x, "Presione una tecla para continuar....");
            mvprintw(15, 46, "");
            refresh();
            attroff(COLOR_PAIR(5));
            getch();
            //clean information line
            for (int i = 0; i < 70; i++)
            {
                mvaddch(18, i, 32);
                mvaddch(19, i, 32);
                refresh();
            }
            windowReports();
        }
        else
        {
            //clean information line
            for (int i = 0; i < 70; i++)
            {
                mvaddch(18, i, 32);
                refresh();
            }
            attron(COLOR_PAIR(5));
            mvprintw(18, x, "Tablero de Juego Generado con Exito");
            mvprintw(15, 46, "");
            refresh();
            attroff(COLOR_PAIR(5));
            //show graphic
            matrix->graficarMatriz();
            //return report menu
            windowReports();
        }
    }
    //show coins per player, OPTION 9
    else if (key == 57)
    {
        if (listPlayer1Coins->isEmpty() && listPlayer2Coins->isEmpty())
        {
            //clean information line
            for (int i = 0; i < 70; i++)
            {
                mvaddch(18, i, 32);
                mvaddch(19, i, 32);
                refresh();
            }
            attron(COLOR_PAIR(5));
            mvprintw(18, x, "Jugador 1 y Jugador 2 no tienen fichas de juego disponibles");
            mvprintw(19, x, "Presione una tecla para continuar....");
            mvprintw(15, 46, "");
            refresh();
            attroff(COLOR_PAIR(5));
            getch();
            //clean information line
            for (int i = 0; i < 70; i++)
            {
                mvaddch(18, i, 32);
                mvaddch(19, i, 32);
                refresh();
            }
            windowReports();
        }
        else
        {
            //clean information line
            for (int i = 0; i < 70; i++)
            {
                mvaddch(18, i, 32);
                refresh();
            }
            attron(COLOR_PAIR(5));
            mvprintw(18, x, "Fichas por Jugador Mostradas con Exito");
            mvprintw(15, 46, "");
            refresh();
            attroff(COLOR_PAIR(5));
            //show graphic
            if (listPlayer1Coins->isEmpty())
            {
                listPlayer2Coins->graphListOfIndividualCoin(name_player2_global);
            }
            else if (listPlayer2Coins->isEmpty())
            {
                listPlayer1Coins->graphListOfIndividualCoin(name_player1_global);
            }
            else
            {
                listPlayer1Coins->graphListOfIndividualCoin(name_player1_global);
                listPlayer2Coins->graphListOfIndividualCoin(name_player2_global);
            }
            //return report menu
            windowReports();
        }
    }
    else
    {
        windowReports();
    }
}

//********************************************************************************
// FUNCTION TO EXIT CURSES
//*********************************************************************************
void exitGame()
{
    endwin();
    exit(-1);
}

//********************************************************************************
// FUNCTION TO READ JSON FILE FOR SCRABBLE CONFIGURATION
//*********************************************************************************
bool readJSON(string file_name)
{
    bool response = false;
    //Convertr string to char
    char name[file_name.length()];
    for (int i = 0; i < sizeof(name); i++)
    {
        name[i] = file_name[i];
    }
    //file name
    ifstream input_file(name);

    //if file doesn't exist
    if (input_file.fail())
    {
        response = false;
    }
    //file exists
    else
    {
        Json::Reader reader;
        Json::Value tag;
        reader.parse(input_file, tag);

        //******************************************
        //Matrix Dimension
        //******************************************
        dimensionMatrix = tag["dimension"].asInt();

        //******************************************
        //Double Boxes
        //******************************************

        const Json::Value &double_boxes = tag["casillas"]["dobles"];
        for (int i = 0; i < double_boxes.size(); i++)
        {
            boxdouble->addBoxDouble(double_boxes[i]["x"].asInt(), double_boxes[i]["y"].asInt());
        }

        //******************************************
        //Triple Boxes
        //******************************************
        const Json::Value &triple_boxes = tag["casillas"]["triples"];
        for (int i = 0; i < triple_boxes.size(); i++)
        {
            boxdtriple->addBoxTriple(triple_boxes[i]["x"].asInt(), triple_boxes[i]["y"].asInt());
        }

        //******************************************
        //Dictionary of words
        //******************************************
        const Json::Value &dictionary = tag["diccionario"];
        for (int i = 0; i < dictionary.size(); i++)
        {
            dictionarywords->addWord(dictionary[i]["palabra"].asString());
        }
        response = true;
    }
    return response;
}

//********************************************************************************
// FUNCTION TO FILL QUEUE COINS
//*********************************************************************************
void fillQueue()
{
    //definition of the arrays of letters
    array<char, 96> foo{
        'A','A','A','A','A','A','A','A','A','A','A','A',
        'B','B',
        'C','C','C','C',
        'D','D','D','D','D',
        'E','E','E','E','E','E','E','E','E','E','E','E',
        'F',
        'G','G',
        'H','H',
        'I','I','I','I','I','I',
        'J',
        'K',
        'L','L','L','L',
        'M','M',
        'N','N','N','N','N',
        'O','O','O','O','O','O','O','O','O',
        'P','P',
        'Q',
        'R','R','R','R','R',
        'S','S','S','S','S','S',
        'T','T','T','T',
        'U','U','U','U','U',
        'V',
        'W',
        'X',
        'Y',
        'Z',
    };
    // obtain a time-based seed:
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(foo.begin(), foo.end(), std::default_random_engine(seed));
    for (char &x : foo)
    {
        switch (x)
        {
        case 'A':
            queeucoins->enqueueCoin("A", 1);
            break;
        case 'B':
            queeucoins->enqueueCoin("B", 3);
            break;
        case 'C':
            queeucoins->enqueueCoin("C", 3);
            break;
        case 'D':
            queeucoins->enqueueCoin("D", 2);
            break;
        case 'E':
            queeucoins->enqueueCoin("E", 1);
            break;
        case 'F':
            queeucoins->enqueueCoin("F", 4);
            break;
        case 'G':
            queeucoins->enqueueCoin("G", 2);
            break;
        case 'H':
            queeucoins->enqueueCoin("H", 4);
            break;
        case 'I':
            queeucoins->enqueueCoin("I", 1);
            break;
        case 'J':
            queeucoins->enqueueCoin("J", 8);
            break;
        case 'K':
            queeucoins->enqueueCoin("K", 5);
            break;
        case 'L':
            queeucoins->enqueueCoin("L", 1);
            break;
        case 'M':
            queeucoins->enqueueCoin("M", 3);
            break;
        case 'N':
            queeucoins->enqueueCoin("N", 1);
            break;
        case 'O':
            queeucoins->enqueueCoin("O", 1);
            break;
        case 'P':
            queeucoins->enqueueCoin("P", 3);
            break;
        case 'Q':
            queeucoins->enqueueCoin("Q", 5);
            break;
        case 'R':
            queeucoins->enqueueCoin("R", 1);
            break;
        case 'S':
            queeucoins->enqueueCoin("S", 1);
            break;
        case 'T':
            queeucoins->enqueueCoin("T", 1);
            break;
        case 'U':
            queeucoins->enqueueCoin("U", 1);
            break;
        case 'V':
            queeucoins->enqueueCoin("V", 4);
            break;
        case 'W':
            queeucoins->enqueueCoin("W", 4);
            break;
        case 'X':
            queeucoins->enqueueCoin("X", 8);
            break;
        case 'Y':
            queeucoins->enqueueCoin("Y", 4);
            break;
        case 'Z':
            queeucoins->enqueueCoin("Z", 10);
            break;
        default:
            break;
        }
    }
}

int main()
{
    
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    clear();
    //fillQueue();
    //queeucoins->graphQueue();
    //assignCoinsPlayer1();
    //listPlayer1Coins->graphListOfIndividualCoin();
    //queeucoins->graphQueue();
    startMenu();
    
    return 0;
}
