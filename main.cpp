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
int button_pause = 0;
int TurnoDePausa=1;

//
string word_entered_player1_global = "";
string word_entered_player2_global = "";

//Definition of functions
void startMenu();
void windowReadFile();
void windowStartGame();
void windowReports();
void exitGame();
void windowsReportPlayer();
bool readJSON(string);
void newPlayer1();
void newPlayer2();
void playerExists1();
void playerExists2();
void askplayer2();
void screenGameInterfacePlayer1();
void screenGameInterfacePlayer2();
void assignCoinsPlayer1();
void assignCoinsPlayer2();
void fillQueue();
void iniciarCoordenada();
void iniciarCoordenada2();
int verificarLetraListPLayer1(int);
int verificarLetraListPLayer2(int);
void dibujarEnMatriz(int, int, int);
void dibujarEnMatriz2(int, int, int);
void verificarCasillaDobleOTriple(int, int, string);
void verificarCasillaDobleOTriple2(int, int, string);
void cambiarFichasPlayer1();
void cambiarFichasPlayer2();
void pantallaDeGanador(int, string, int, string);
void verificarPausa();

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
        verificarPausa();     
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

void verificarPausa()
{
    if(button_pause==0) //no esta en pausa, juego nuevo
    {
    //reiniciar todas las variables y vaciar      

    //score per player
    score_player1_global = 0;
    score_player2_global = 0;

    //num coins in list
    numCoinsPlayer1 = 0;
    numCoinsPlayer2 = 0;

    //name per player
    name_player1_global="";
    name_player2_global="";

    //boton de finalizar y pausa
    button_pause = 0;
    TurnoDePausa=1;

    //palabra que ingreso cuando escribo algo con mis fichas disponibles
    word_entered_player1_global = "";
    word_entered_player2_global = "";
    matrix->clearOut();

    windowStartGame();

    }
    else //boton=1 esta el juego en pausa
    {
        if(TurnoDePausa==1)
        {
            screenGameInterfacePlayer1();        
        }
        else
        {
            screenGameInterfacePlayer2();
        }        
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
                //REPARTICION DE FICHAS POR JUGADOR Y LLENADO DE LA COLA DE FICHAS
                queeucoins->clearOut();
                fillQueue();
                numCoinsPlayer1 = 0;
                numCoinsPlayer2 = 0;
                listPlayer1Coins->clearOut();
                listPlayer2Coins->clearOut();
                assignCoinsPlayer1();
                assignCoinsPlayer2();
                screenGameInterfacePlayer1(); //start game interface
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
                //prepara el juego para iniciar
                queeucoins->clearOut();
                fillQueue();
                numCoinsPlayer1 = 0;
                numCoinsPlayer2 = 0;
                listPlayer1Coins->clearOut();
                listPlayer2Coins->clearOut();
                assignCoinsPlayer1();
                assignCoinsPlayer2();
                screenGameInterfacePlayer1(); //start game interface
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

//#######################################################
//######## GAME INTERFACE PLAYER 1
//#######################################################

void screenGameInterfacePlayer1()
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
    mvprintw(7, 0, "================================================================================");
    mvprintw(3, 0, "================================================================================");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(5) | A_BOLD);
    mvprintw(23, 0, "ESC - Finalizar Partida");
    attroff(COLOR_PAIR(5));

    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(23, 28, "1 - Pausar Partida");
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(2) | A_BOLD);
    mvprintw(23, 53, "2 - Cambiar Fichas");
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(4, 0, "Turno de: ");
    attroff(COLOR_PAIR(3));

    //para mostrar el nombre del jugador 1 en la descripcion TUrno de:
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

    //etiqueta punteo
    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(5, 0, "Punteo: ");
    attroff(COLOR_PAIR(3));

    //limpiar si hubiera algun punteo para reescribir el otro
    for (int i = 8; i < 15; i++)
    {
        mvaddch(5, i, 32);
        refresh();
    }

    //mostrar el punteo en pantalla si tengo uno
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

    //etiqueta fichas disponibles
    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(6, 0, "Fichas Disponibles: ");
    attron(COLOR_PAIR(2) | A_BOLD);
    int b = 20; //espacio de 3

    //mostrar las fichas disponibles en la pantalla
    if (listPlayer1Coins->isEmpty())
    {
        mvprintw(23, 25, "No hay Fichas Disponibles ");
        mvprintw(21, 25, "Presione ENTER para continuar...");
        refresh();
        getch();
        screenGameInterfacePlayer1();
    }
    else
    {
        NodeCoin *aux = listPlayer1Coins->first;
        if (listPlayer1Coins->first->next == NULL)
        {
            mvaddch(6, b, listPlayer1Coins->first->letter[0]);
            refresh();
            b += 3;
        }
        while (aux->next != NULL)
        {
            if (aux == listPlayer1Coins->first)
            {
                mvaddch(6, b, aux->letter[0]);
                refresh();
                b += 3;
            }
            else
            {
                mvaddch(6, b, aux->letter[0]);
                refresh();
                b += 3;
            }
            aux = aux->next;
        }
        if (aux != listPlayer1Coins->first)
        {
            mvaddch(6, b, aux->letter[0]);
            refresh();
            b += 3;
        }
    }
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(8, 0, "Ingrese Palabra que desea Jugar, Usando las fichas disponibles: ");
    mvprintw(9, 0, "");
    attroff(COLOR_PAIR(3));
    refresh();

    bool bool_verificar_letra = true;
    bool flag = true;
    int key;
    int column = 0;
    string word_entered = "";
    while (flag)
    {
        //get key enter by user
        key = getch();
        if (key == 27) //ESC return to menu
        {
            button_pause = 0;

            if (score_player1_global != 0 && score_player2_global != 0)
            {
                //añadir los puntajes individuales a cada uno
                treeplayer->searchPlayerAndAddScore(name_player1_global, score_player1_global);
                treeplayer->searchPlayerAndAddScore(name_player2_global, score_player2_global);

                //añadir los puntajes actuales a la tabla general
                generalscore->addPlayer(score_player1_global, name_player1_global);
                generalscore->addPlayer(score_player2_global, name_player2_global);
                pantallaDeGanador(score_player1_global, name_player1_global, score_player2_global, name_player2_global);
            }
            else if (score_player1_global == 0 && score_player2_global != 0)
            {
                treeplayer->searchPlayerAndAddScore(name_player2_global, score_player2_global);
                generalscore->addPlayer(score_player2_global, name_player2_global);
                pantallaDeGanador(score_player1_global, name_player1_global, score_player2_global, name_player2_global);
            }
            else if (score_player1_global != 0 && score_player2_global == 0)
            {
                treeplayer->searchPlayerAndAddScore(name_player1_global, score_player1_global);
                generalscore->addPlayer(score_player1_global, name_player1_global);
                pantallaDeGanador(score_player1_global, name_player1_global, score_player2_global, name_player2_global);
            }
            else
            {
                startMenu();
            }
        }
        else if (key == 49)
        {
            button_pause = 1; //poner el juego en pausa
            TurnoDePausa=1;
            startMenu();
        }
        else if (key == 50) //cambiar todas las fichas de la partida
        {
            //ejecutar metodo cambiarFichas() y pasar el turno al jugador 2
            cambiarFichasPlayer1();
            assignCoinsPlayer1();
            screenGameInterfacePlayer2(); //<-- MODIFICAR A SCREANPLAYER2
        }
        else if (key == 10) //cuando presiono ENTER para aceptar la cadena
        {
            bool resp = dictionarywords->checkWord(word_entered);
            if ((resp == true) && (bool_verificar_letra == true))
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
                //screenGameInterfacePlayer1();
            }
            else
            {
                attron(COLOR_PAIR(4) | A_BOLD);
                mvprintw(11, 10, "Palabra NO Existe o Letras Insuficientes");
                mvprintw(12, 10, "Presione una tecla para intentar de nuevo...");
                refresh();
                attroff(COLOR_PAIR(4));
                bool_verificar_letra=true;
                word_entered="";
                word_entered_player1_global="";
                getch();
                screenGameInterfacePlayer1();
            }
        }
        else
        {
            if (verificarLetraListPLayer1(key) == 0)
            {
                bool_verificar_letra = false; //letra no existe
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

//pantalla que muestra el ganador del juego
void pantallaDeGanador(int punteo1, string jugador1, int punteo2, string jugador2)
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
    mvprintw(18, 24, "Presione ENTER para continuar...");
    attroff(COLOR_PAIR(5));

    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(2, 0, "================================================================================");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(4, 0, "================================================================================");
    mvprintw(6, 0, "================================================================================");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(5, 34, "GANADOR");
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(4) | A_BOLD);
    mvprintw(11, 34, "PERDEDOR");
    attroff(COLOR_PAIR(4));

    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(10, 0, "================================================================================");
    mvprintw(12, 0, "================================================================================");
    attroff(COLOR_PAIR(1));
    refresh();

    //para limpiar una fila
    for (int i = 0; i < 70; i++)
    {
        mvaddch(8, i, 32);
        mvaddch(14, i, 32);
        refresh();
    }

    if (punteo1 > punteo2)
    {
        //para mostrar el nombre del jugador 1
        attron(COLOR_PAIR(2) | A_BOLD);
        int a = 30;
        char name[jugador1.length()];
        for (int i = 0; i < sizeof(name); i++)
        {
            name[i] = jugador1[i];
            mvaddch(8, a, name[i]);
            refresh();
            a++;
        }
        attroff(COLOR_PAIR(2));

        //mostrar el punteo en pantalla de jugador 1
        attron(COLOR_PAIR(2) | A_BOLD);
        string punteoo1 = to_string(punteo1);
        a = 42;
        char name2[punteoo1.length()];
        for (int i = 0; i < sizeof(name2); i++)
        {
            name2[i] = punteoo1[i];
            mvaddch(8, a, name2[i]);
            refresh();
            a++;
        }
        attroff(COLOR_PAIR(2));

        //para mostrar el nombre del jugador 2
        attron(COLOR_PAIR(2) | A_BOLD);
        int b = 30;
        char name3[jugador2.length()];
        for (int i = 0; i < sizeof(name3); i++)
        {
            name3[i] = jugador2[i];
            mvaddch(14, b, name3[i]);
            refresh();
            b++;
        }
        attroff(COLOR_PAIR(2));

        //mostrar el punteo en pantalla de jugador 2
        attron(COLOR_PAIR(2) | A_BOLD);
        string punteoo2 = to_string(punteo2);
        b = 42;
        char name4[punteoo2.length()];
        for (int i = 0; i < sizeof(name4); i++)
        {
            name4[i] = punteoo2[i];
            mvaddch(14, b, name4[i]);
            refresh();
            b++;
        }
        attroff(COLOR_PAIR(2));
    }
    else
    {
        //para mostrar el nombre del jugador 2
        attron(COLOR_PAIR(2) | A_BOLD);
        int b = 30;
        char name3[jugador2.length()];
        for (int i = 0; i < sizeof(name3); i++)
        {
            name3[i] = jugador2[i];
            mvaddch(8, b, name3[i]);
            refresh();
            b++;
        }
        attroff(COLOR_PAIR(2));

        //mostrar el punteo en pantalla de jugador 2
        attron(COLOR_PAIR(2) | A_BOLD);
        string punteoo2 = to_string(punteo2);
        b = 42;
        char name4[punteoo2.length()];
        for (int i = 0; i < sizeof(name4); i++)
        {
            name4[i] = punteoo2[i];
            mvaddch(8, b, name4[i]);
            refresh();
            b++;
        }
        attroff(COLOR_PAIR(2));

         //para mostrar el nombre del jugador 1
        attron(COLOR_PAIR(2) | A_BOLD);
        int a = 30;
        char name[jugador1.length()];
        for (int i = 0; i < sizeof(name); i++)
        {
            name[i] = jugador1[i];
            mvaddch(14, a, name[i]);
            refresh();
            a++;
        }
        attroff(COLOR_PAIR(2));

        //mostrar el punteo en pantalla de jugador 1
        attron(COLOR_PAIR(2) | A_BOLD);
        string punteoo1 = to_string(punteo1);
        a = 42;
        char name2[punteoo1.length()];
        for (int i = 0; i < sizeof(name2); i++)
        {
            name2[i] = punteoo1[i];
            mvaddch(14, a, name2[i]);
            refresh();
            a++;
        }
        attroff(COLOR_PAIR(2));        
    }    

    attron(COLOR_PAIR(5) | A_BOLD);
    mvprintw(19, 24, "");
    attroff(COLOR_PAIR(5));
    refresh();
    getch();
    startMenu();
}

//cambia todas las fichas del jugador 1
void cambiarFichasPlayer1()
{
    //1.) sacar la ficha de la lista
    //2.) la ficha sacada agregarla nuevamente a la cola de fichas
    //3.) restar el numero de fichas disponibles de player 1
    string letter;
    int value;
    while (numCoinsPlayer1 != 0)
    {
        //1)
        NodeCoin *tmp = listPlayer1Coins->returnCoinOnly();
        letter = tmp->letter;
        value = tmp->value;
        //2)
        queeucoins->enqueueCoin(letter, value);
        //3)
        numCoinsPlayer1--;
    }
}

//verifica si la letra que estoy ingresando la tengo disponible en mi lista de fichas de jugador 1
int verificarLetraListPLayer1(int letra)
{
    int x = letra;
    char c = static_cast<char>(x);
    int res = 0;
    if (listPlayer1Coins->checkLetter(c) == 1)
    {
        //letra existe
        res = 1;
    }
    else
    {
        res = 0;
        //letra no existe
    }
    return res;
}

//pide las coordenadas de inicio para empezar a meter letras
void iniciarCoordenada()
{
    int pos_x = 0;
    int pos_y = 0;
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
    mvaddch(11, j, ')');
    mvprintw(12, 0, "Coordenada X (Fila): ");
    refresh();
    attroff(COLOR_PAIR(3));

    //pedir coordenada en x
    bool flag = true;
    int key;
    int column = 21;
    string pos_entered = "";
    //string word_entered="123";
    //key = stoi(word_entered); convert string to int
    while (flag)
    {
        //get key enter by user
        key = getch();
        if (key == 10)
        {
            pos_x = stoi(pos_entered);
            flag = false;
        }
        else if (key >= 48 && key <= 57)
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
            flag = true;
        }
    }

    attron(COLOR_PAIR(3) | A_BOLD);
    //pedir coordenada en y
    mvprintw(13, 0, "Coordenada Y (Columna): ");
    refresh();
    attroff(COLOR_PAIR(3));
    flag = true;
    column = 24;
    pos_entered = "";
    //string word_entered="123";
    //key = stoi(word_entered); convert string to int
    while (flag)
    {
        //get key enter by user
        key = getch();
        if (key == 10) //ESC return to menu
        {
            pos_y = stoi(pos_entered);
            flag = false;
        }
        else if (key >= 48 && key <= 57)
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
            flag = true;
        }
    }

    //comparar los valores ingresados con el valor de la matriz
    if (pos_x <= dimensionMatrix && pos_y <= dimensionMatrix)
    {
        attron(COLOR_PAIR(4) | A_BOLD);
        mvprintw(14, 20, "Coordenada de Inicio Valida");
        refresh();
        attroff(COLOR_PAIR(4));

        attron(COLOR_PAIR(3) | A_BOLD);
        mvprintw(15, 0, "(H) Horizontal *** (V) Vertical:");
        attroff(COLOR_PAIR(3));

        int posic = 0; // 0 = horizontal; 1=vertical
        attron(COLOR_PAIR(3) | A_BOLD);
        mvprintw(15, 34, "");
        refresh();
        int key12 = getch();

        if (key12 == 72 || key12 == 104) // h
        {
            posic = 0;
            mvaddch(15, 34, 72);
            refresh();
            getch();
        }
        if (key12 == 86 || key12 == 118) //v
        {
            posic = 1;
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
    //screenGameInterfacePlayer1();
}

//dibuja las letras ingresadas en la matriz,
void dibujarEnMatriz(int fila, int columna, int posicionPalabra)
{
    char word[word_entered_player1_global.length()];
    if (posicionPalabra == 0) // palabra horizontal
    {
        for (int i = 0; i < sizeof(word); i++)
        {
            word[i] = word_entered_player1_global[i];
            NodeCoinMatrix *letra = new NodeCoinMatrix();
            letra->letter = word[i];
            //verificar cada coordenada y ver si es triple o doble, saca la letra y suma si valor
            verificarCasillaDobleOTriple(fila, columna + i, letra->letter);
            matrix->add(columna + i, fila, letra); //primero va columna, luego fila
        }
    }
    else //palabra vertical
    {
        for (int i = 0; i < sizeof(word); i++)
        {
            word[i] = word_entered_player1_global[i];
            NodeCoinMatrix *letra = new NodeCoinMatrix();
            letra->letter = word[i];
            //verificar cada coordenada y ver si es triple o doble, saca la letra y suma si valor
            verificarCasillaDobleOTriple(fila + i, columna, letra->letter);
            matrix->add(columna, fila + i, letra); //primero va columna, luego fila
        }
    }

    //mostrar la matriz
    matrix->graficarMatriz();

    //llenar nuevamente la lista del jugador 1
    assignCoinsPlayer1();

    //para limpiar una fila
    for (int i = 7; i < 15; i++)
    {
        mvaddch(5, i, 32);
        refresh();
    }

    for (int i = 0; i < 70; i++)
    {
        mvaddch(14, i, 32);
        mvaddch(15, i, 32);
        refresh();
    }
    //IMPRIMIR UN NUMERO EN PANTALLA
    attron(COLOR_PAIR(2) | A_BOLD);
    string punteo1 = to_string(score_player1_global);
    int a = 8;
    char name2[punteo1.length()];
    for (int i = 0; i < sizeof(name2); i++)
    {
        name2[i] = punteo1[i];
        mvaddch(5, a, name2[i]);
        refresh();
        a++;
    }
    attroff(COLOR_PAIR(2));
    a = 8;

    attron(COLOR_PAIR(4) | A_BOLD);
    mvprintw(15, 20, "Presione ENTER para turno de Jugador 2...");
    mvprintw(16, 20, "");
    refresh();
    attroff(COLOR_PAIR(4));
    getch();

    //iniciar el turno del jugador 2
    screenGameInterfacePlayer2();
}

//verifica si una casilla esta en doble o triple y si es asi multiplica x2 o x3
void verificarCasillaDobleOTriple(int fila, int columna, string a)
{
    //cout<<"x: "<<fila<<",";
    //cout<<"y: "<<columna<<endl;
    NodeCoin *n = new NodeCoin();
    int num = 0;
    if (boxdouble->verifyBoxDouble(fila, columna))
    {
        //cout<<"doble: ";
        n = listPlayer1Coins->returnCoin(a);
        //cout<<n->value<<",";
        num = int(n->value) * 2;
        //cout<<num<<endl;

        //score_player1_global = score_player1_global+(n->value*2);
    }
    else if (boxdtriple->verifyBoxTriple(fila, columna))
    {
        //cout<<"triple: ";
        n = listPlayer1Coins->returnCoin(a);
        //cout<<n->value<<",";
        num = int(n->value) * 3;
        //cout<<num<<endl;
        //score_player1_global = score_player1_global+(n->value*3);
    }
    else
    {
        //cout<<"simple: ";
        n = listPlayer1Coins->returnCoin(a);
        //cout<<n->value<<",";
        num = int(n->value);
        //cout<<num<<endl;
        //score_player1_global = score_player1_global+(n->value);
    }
    score_player1_global += num;
    //cout<<score_player1_global<<endl;
    numCoinsPlayer1--;
    num = 0;
}

//#######################################################
//######## GAME INTERFACE PLAYER 2
//#######################################################
void screenGameInterfacePlayer2()
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
    mvprintw(7, 0, "================================================================================");
    mvprintw(3, 0, "================================================================================");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(5) | A_BOLD);
    mvprintw(23, 0, "ESC - Finalizar Partida");
    attroff(COLOR_PAIR(5));

    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(23, 28, "1 - Pausar Partida");
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(2) | A_BOLD);
    mvprintw(23, 53, "2 - Cambiar Fichas");
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(4, 0, "Turno de: ");
    attroff(COLOR_PAIR(3));

    //para mostrar el nombre del jugador 1 en la descripcion TUrno de:
    attron(COLOR_PAIR(2) | A_BOLD);
    int a = 10;
    char name[name_player2_global.length()];
    for (int i = 0; i < sizeof(name); i++)
    {
        name[i] = name_player2_global[i];
        mvaddch(4, a, name[i]);
        refresh();
        a++;
    }
    attroff(COLOR_PAIR(2));

    //etiqueta punteo
    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(5, 0, "Punteo: ");
    attroff(COLOR_PAIR(3));

    //limpiar si hubiera algun punteo para reescribir el otro
    for (int i = 8; i < 15; i++)
    {
        mvaddch(5, i, 32);
        refresh();
    }

    //mostrar el punteo en pantalla si tengo uno
    attron(COLOR_PAIR(2) | A_BOLD);
    string punteo2 = to_string(score_player2_global);
    a = 8;
    char name2[punteo2.length()];
    for (int i = 0; i < sizeof(name2); i++)
    {
        name2[i] = punteo2[i];
        mvaddch(5, a, name2[i]);
        refresh();
        a++;
    }
    attroff(COLOR_PAIR(2));

    //etiqueta fichas disponibles
    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(6, 0, "Fichas Disponibles: ");
    attron(COLOR_PAIR(2) | A_BOLD);
    int b = 20; //espacio de 3

    //mostrar las fichas disponibles en la pantalla
    if (listPlayer2Coins->isEmpty())
    {
        mvprintw(23, 25, "No hay Fichas Disponibles ");
        mvprintw(21, 25, "Presione ENTER para continuar...");
        refresh();
        getch();
        screenGameInterfacePlayer2();
    }
    else
    {
        NodeCoin *aux = listPlayer2Coins->first;
        if (listPlayer2Coins->first->next == NULL)
        {
            mvaddch(6, b, listPlayer2Coins->first->letter[0]);
            refresh();
            b += 3;
        }
        while (aux->next != NULL)
        {
            if (aux == listPlayer2Coins->first)
            {
                mvaddch(6, b, aux->letter[0]);
                refresh();
                b += 3;
            }
            else
            {
                mvaddch(6, b, aux->letter[0]);
                refresh();
                b += 3;
            }
            aux = aux->next;
        }
        if (aux != listPlayer2Coins->first)
        {
            mvaddch(6, b, aux->letter[0]);
            refresh();
            b += 3;
        }
    }
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(8, 0, "Ingrese Palabra que desea Jugar, Usando las fichas disponibles: ");
    mvprintw(9, 0, "");
    attroff(COLOR_PAIR(3));
    refresh();

    bool bool_verificar_letra = true;
    bool flag = true;
    int key;
    int column = 0;
    string word_entered = "";
    while (flag)
    {
        //get key enter by user
        key = getch();
        if (key == 27) //ESC return to menu
        {
            button_pause = 0;

            if (score_player1_global != 0 && score_player2_global != 0)
            {
                //añadir los puntajes individuales a cada uno
                treeplayer->searchPlayerAndAddScore(name_player1_global, score_player1_global);
                treeplayer->searchPlayerAndAddScore(name_player2_global, score_player2_global);

                //añadir los puntajes actuales a la tabla general
                generalscore->addPlayer(score_player1_global, name_player1_global);
                generalscore->addPlayer(score_player2_global, name_player2_global);
                pantallaDeGanador(score_player1_global, name_player1_global, score_player2_global, name_player2_global);
            }
            else if (score_player1_global == 0 && score_player2_global != 0)
            {
                treeplayer->searchPlayerAndAddScore(name_player2_global, score_player2_global);
                generalscore->addPlayer(score_player2_global, name_player2_global);
                pantallaDeGanador(score_player1_global, name_player1_global, score_player2_global, name_player2_global);
            }
            else if (score_player1_global != 0 && score_player2_global == 0)
            {
                treeplayer->searchPlayerAndAddScore(name_player1_global, score_player1_global);
                generalscore->addPlayer(score_player1_global, name_player1_global);
                pantallaDeGanador(score_player1_global, name_player1_global, score_player2_global, name_player2_global);
            }
            else
            {
                startMenu();
            }
        }
        else if (key == 49)
        {
            button_pause = 1; //poner el juego en pausa
            TurnoDePausa=2;
            startMenu();
        }
        else if (key == 50) //cambiar todas las fichas de la partida
        {
            //ejecutar metodo cambiarFichas() y pasar el turno al jugador 2
            cambiarFichasPlayer2();
            assignCoinsPlayer2();
            screenGameInterfacePlayer1(); //<-- MODIFICAR A SCREANPLAYER1
        }
        else if (key == 10)
        {
            bool resp = dictionarywords->checkWord(word_entered);
            if ((resp == true) && (bool_verificar_letra == true))
            {
                word_entered_player2_global = word_entered;
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
                iniciarCoordenada2();
                //screenGameInterfacePlayer1();
            }
            else
            {
                attron(COLOR_PAIR(4) | A_BOLD);
                mvprintw(11, 10, "Palabra NO Existe o Letras Insuficientes");
                mvprintw(12, 10, "Presione una tecla para intentar de nuevo...");
                refresh();
                attroff(COLOR_PAIR(4));
                bool_verificar_letra=true;
                word_entered="";
                word_entered_player2_global="";
                getch();
                screenGameInterfacePlayer2();
            }
        }
        else
        {
            if (verificarLetraListPLayer2(key) == 0)
            {
                bool_verificar_letra = false; //letra no existe
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

//cambia todas las fichas del jugador 1
void cambiarFichasPlayer2()
{
    //1.) sacar la ficha de la lista
    //2.) la ficha sacada agregarla nuevamente a la cola de fichas
    //3.) restar el numero de fichas disponibles de player 1
    string letter;
    int value;
    while (numCoinsPlayer2 != 0)
    {
        //1)
        NodeCoin *tmp = listPlayer2Coins->returnCoinOnly();
        letter = tmp->letter;
        value = tmp->value;
        //2)
        queeucoins->enqueueCoin(letter, value);
        //3)
        numCoinsPlayer2--;
    }
}

//verifica si la letra que estoy ingresando la tengo disponible en mi lista de fichas de jugador 1
int verificarLetraListPLayer2(int letra)
{
    int x = letra;
    char c = static_cast<char>(x);
    int res = 0;
    if (listPlayer2Coins->checkLetter(c) == 1)
    {
        //letra existe
        res = 1;
    }
    else
    {
        res = 0;
        //letra no existe
    }
    return res;
}

//pide las coordenadas de inicio para empezar a meter letras
void iniciarCoordenada2()
{
    int pos_x = 0;
    int pos_y = 0;
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
    mvaddch(11, j, ')');
    mvprintw(12, 0, "Coordenada X (Fila): ");
    refresh();
    attroff(COLOR_PAIR(3));

    //pedir coordenada en x
    bool flag = true;
    int key;
    int column = 21;
    string pos_entered = "";
    //string word_entered="123";
    //key = stoi(word_entered); convert string to int
    while (flag)
    {
        //get key enter by user
        key = getch();
        if (key == 10)
        {
            pos_x = stoi(pos_entered);
            flag = false;
        }
        else if (key >= 48 && key <= 57)
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
            flag = true;
        }
    }

    attron(COLOR_PAIR(3) | A_BOLD);
    //pedir coordenada en y
    mvprintw(13, 0, "Coordenada Y (Columna): ");
    refresh();
    attroff(COLOR_PAIR(3));
    flag = true;
    column = 24;
    pos_entered = "";
    //string word_entered="123";
    //key = stoi(word_entered); convert string to int
    while (flag)
    {
        //get key enter by user
        key = getch();
        if (key == 10) //ESC return to menu
        {
            pos_y = stoi(pos_entered);
            flag = false;
        }
        else if (key >= 48 && key <= 57)
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
            flag = true;
        }
    }

    //comparar los valores ingresados con el valor de la matriz
    if (pos_x <= dimensionMatrix && pos_y <= dimensionMatrix)
    {
        attron(COLOR_PAIR(4) | A_BOLD);
        mvprintw(14, 20, "Coordenada de Inicio Valida");
        refresh();
        attroff(COLOR_PAIR(4));

        attron(COLOR_PAIR(3) | A_BOLD);
        mvprintw(15, 0, "(H) Horizontal *** (V) Vertical:");
        attroff(COLOR_PAIR(3));

        int posic = 0; // 0 = horizontal; 1=vertical
        attron(COLOR_PAIR(3) | A_BOLD);
        mvprintw(15, 34, "");
        refresh();
        int key12 = getch();

        if (key12 == 72 || key12 == 104) // h
        {
            posic = 0;
            mvaddch(15, 34, 72);
            refresh();
            getch();
        }
        if (key12 == 86 || key12 == 118) //v
        {
            posic = 1;
            mvaddch(15, 34, 86);
            refresh();
            getch();
        }
        dibujarEnMatriz2(pos_x, pos_y, posic);
    }
    else
    {
        attron(COLOR_PAIR(4) | A_BOLD);
        mvprintw(14, 20, "Coordenadas Sobrepasan el Limite");
        refresh();
        attroff(COLOR_PAIR(4));
        getch();
        iniciarCoordenada2();
    }

    //validar la coordenada de inicio
    //screenGameInterfacePlayer1();
}

//dibuja las letras ingresadas en la matriz,
void dibujarEnMatriz2(int fila, int columna, int posicionPalabra)
{
    char word[word_entered_player2_global.length()];
    if (posicionPalabra == 0) // palabra horizontal
    {
        for (int i = 0; i < sizeof(word); i++)
        {
            word[i] = word_entered_player2_global[i];
            NodeCoinMatrix *letra = new NodeCoinMatrix();
            letra->letter = word[i];
            //verificar cada coordenada y ver si es triple o doble, saca la letra y suma si valor
            verificarCasillaDobleOTriple2(fila, columna + i, letra->letter);
            matrix->add(columna + i, fila, letra); //primero va columna, luego fila
        }
    }
    else //palabra vertical
    {
        for (int i = 0; i < sizeof(word); i++)
        {
            word[i] = word_entered_player2_global[i];
            NodeCoinMatrix *letra = new NodeCoinMatrix();
            letra->letter = word[i];
            //verificar cada coordenada y ver si es triple o doble, saca la letra y suma si valor
            verificarCasillaDobleOTriple2(fila + i, columna, letra->letter);
            matrix->add(columna, fila + i, letra); //primero va columna, luego fila
        }
    }

    //mostrar la matriz
    matrix->graficarMatriz();

    //llenar nuevamente la lista del jugador 2
    assignCoinsPlayer2();

    //para limpiar una fila
    for (int i = 7; i < 15; i++)
    {
        mvaddch(5, i, 32);
        refresh();
    }

    for (int i = 0; i < 70; i++)
    {
        mvaddch(14, i, 32);
        mvaddch(15, i, 32);
        refresh();
    }
    //IMPRIMIR UN NUMERO EN PANTALLA
    attron(COLOR_PAIR(2) | A_BOLD);
    string punteo2 = to_string(score_player2_global);
    int a = 8;
    char name2[punteo2.length()];
    for (int i = 0; i < sizeof(name2); i++)
    {
        name2[i] = punteo2[i];
        mvaddch(5, a, name2[i]);
        refresh();
        a++;
    }
    attroff(COLOR_PAIR(2));
    a = 8;

    attron(COLOR_PAIR(4) | A_BOLD);
    mvprintw(15, 20, "Presione ENTER para turno de Jugador 1...");
    mvprintw(16, 20, "");
    refresh();
    attroff(COLOR_PAIR(4));
    getch();

    //iniciar el turno del jugador 1
    screenGameInterfacePlayer1();
}

//verifica si una casilla esta en doble o triple y si es asi multiplica x2 o x3
void verificarCasillaDobleOTriple2(int fila, int columna, string a)
{
    //cout<<"x: "<<fila<<",";
    //cout<<"y: "<<columna<<endl;
    NodeCoin *n = new NodeCoin();
    int num = 0;
    if (boxdouble->verifyBoxDouble(fila, columna))
    {
        //cout<<"doble: ";
        n = listPlayer2Coins->returnCoin(a);
        //cout<<n->value<<",";
        num = int(n->value) * 2;
        //cout<<num<<endl;

        //score_player1_global = score_player1_global+(n->value*2);
    }
    else if (boxdtriple->verifyBoxTriple(fila, columna))
    {
        //cout<<"triple: ";
        n = listPlayer2Coins->returnCoin(a);
        //cout<<n->value<<",";
        num = int(n->value) * 3;
        //cout<<num<<endl;
        //score_player1_global = score_player1_global+(n->value*3);
    }
    else
    {
        //cout<<"simple: ";
        n = listPlayer2Coins->returnCoin(a);
        //cout<<n->value<<",";
        num = int(n->value);
        //cout<<num<<endl;
        //score_player1_global = score_player1_global+(n->value);
    }
    score_player2_global += num;
    //cout<<score_player1_global<<endl;
    numCoinsPlayer2--;
    num = 0;
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

    attron(COLOR_PAIR(3));
    mvprintw(22, x, "ESC - Regresar al Menu Principal");
    attroff(COLOR_PAIR(3));
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
        windowsReportPlayer();
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

void windowsReportPlayer()
{
    clear();
    int x = 22;

    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(22, 20, "ESC - REGRESAR AL MENU DE REPORTES");
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(3, 20, "===============================================");
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(4, 27, "SCORE-BOARD POR JUGADOR");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(5, 20, "===============================================");
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(2));
    mvprintw(7, x, "Nombre de Jugador: ");
    mvprintw(8, x, "");
    refresh();

    //read character of keyboard
    bool flag = true;
    int key;
    int column = 22;
    string player_name_to_search;
    while (flag)
    {
        //get key enter by user
        key = getch();
        if (key == 27) //ESC return to menu
        {
            windowReports();
        }
        else if (key == 10)
        {
            NodeTree *n = treeplayer->searchPlayerAndReturn(player_name_to_search);
            if (n != NULL)
            {
                attron(COLOR_PAIR(4));
                mvprintw(10, 27, "!!..Nombre encontrado con exito..!!");
                mvprintw(11, 25, "Presione una tecla para continuar....");
                refresh();
                attroff(COLOR_PAIR(4));
                n->list->graphScoreIndividual(player_name_to_search);
                getch();
                windowsReportPlayer();
            }
            else
            {
                attron(COLOR_PAIR(5));
                mvprintw(9, 27, "!!!EL NOMBRE NO EXISTE!!!");
                mvprintw(10, 25, "Presione una tecla para reintentar....");
                refresh();
                attroff(COLOR_PAIR(5));
                getch();
                windowsReportPlayer();
            }
        }
        else
        {
            player_name_to_search += char(key);
            mvaddch(8, column, key);
            refresh();
            column++;
        }
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
        'A',
        'A',
        'A',
        'A',
        'A',
        'A',
        'A',
        'A',
        'A',
        'A',
        'A',
        'A',
        'B',
        'B',
        'C',
        'C',
        'C',
        'C',
        'D',
        'D',
        'D',
        'D',
        'D',
        'E',
        'E',
        'E',
        'E',
        'E',
        'E',
        'E',
        'E',
        'E',
        'E',
        'E',
        'E',
        'F',
        'G',
        'G',
        'H',
        'H',
        'I',
        'I',
        'I',
        'I',
        'I',
        'I',
        'J',
        'K',
        'L',
        'L',
        'L',
        'L',
        'M',
        'M',
        'N',
        'N',
        'N',
        'N',
        'N',
        'O',
        'O',
        'O',
        'O',
        'O',
        'O',
        'O',
        'O',
        'O',
        'P',
        'P',
        'Q',
        'R',
        'R',
        'R',
        'R',
        'R',
        'S',
        'S',
        'S',
        'S',
        'S',
        'S',
        'T',
        'T',
        'T',
        'T',
        'U',
        'U',
        'U',
        'U',
        'U',
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
    /*if(readJSON("entrada.json"))
    {
        cout<<"exito read file"<<endl;
        cout<<"LISTA DE DOBLES"<<endl;
        boxdouble->printBoxDouble();
        if(boxdouble->verifyBoxDouble(4,5))
        {
            cout<<"existe casilla doble"<<endl;
        }
        cout<<"\n";
        cout<<"LISTA DE TRIPLES"<<endl;
        boxdtriple->printBoxTriple();
        cout<<"\n";
    }
    else
    {
        cout<<"error de read";
        
    }*/

    return 0;
}
