// FourInARaw.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Game.h"
#include "GameController.h"
#include "GameConsuleView.h"

#include "InitAckCmd.h"
#include "PlayTurnAckCmd.h"
#include "EasyLevelStrategy.h"


int main()
{
    std::cout << "Hello FourInARaw!\n";

    // Game ConsuleViewer
    CGameConsuleView* ConsuleView = new CGameConsuleView();

    // Create Game
    CGame* game = new CGame();

    // Init Cmds
    CInitAckCmd* initAckCmd = new CInitAckCmd();
    initAckCmd->SetCmdReceiver((ICmdReceiver*)game);
    CPlayTurnAckCmd* playAckCmd = new CPlayTurnAckCmd();
    playAckCmd->SetCmdReceiver((ICmdReceiver*)game);

    // Init GameController
    CGameController* gameController = new CGameController();
    gameController->RegisterToSubject(ConsuleView);
    gameController->SetInitAckCmd(initAckCmd);
    gameController->SetPlayTurnAckCmd(playAckCmd);

    // init Game
    game->InitGame(gameController);

    game->PlayAGame();

  //  CEasyLevelStrategy* levelStrategy = new CEasyLevelStrategy();

    /*CPlayerManual* pm1 = new CPlayerManual();
    RETCODE_e rc1 = pm1->InitPlayerManual(game,WHITE);
    pm1->SetPlayTurnCmd(playCmd);
    */

 /*   CPlayerAuto* pa1 = new CPlayerAuto();
    RETCODE_e rc1 = pa1->InitPlayerAuto(game, PLAYER1);
    pa1->SetPlayerLevel(EASY_LEVEL, levelStrategy);
    pa1->SetPlayTurnCmd(playCmd);

    CPlayerAuto* pa2 = new CPlayerAuto();
    RETCODE_e rc2 = pa2->InitPlayerAuto(game, PLAYER2);
    pa2->SetPlayerLevel(EASY_LEVEL, levelStrategy);
    pa2->SetPlayTurnCmd(playCmd);

    if(OK == rc1 && OK == rc2)
    { 
        game->PlayAGame();
    }
*/ 
   
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
