#pragma once

#define NUM_RAW 6
#define NUM_COL 7

typedef enum PLAYER_e
{
	PLAYER1 = 0,
	PLAYER2 = 1,
	NUM_PLAYERS = 2
}PLAYER_e;

typedef enum ORIENTATION_e
{
	RAW = 0,
	COL = 1,
	DIAG_LEFT = 2,
	DIAG_RIGHT = 3
}ORIENTATION_e;


typedef enum RETCODE_e
{
	OK = 0,
	NOT_OK = 1
}RETCODE_e;

typedef enum GAME_STATE_e
{
	INIT_STATE = 0,
	PLAY_TURN_STATE = 1,
	CHECK_GAME_STATE = 2,
	WIN_GAME_STATE = 3,
	END_GAME_STATE = 4,
	NUM_STATES = 5
}GAME_STATE_e;

typedef struct HOLE_STATUS
{
	bool taken;
	PLAYER_e player;
}HOLE_STATUS;

typedef struct BOARD_SNAPSHOT
{
	HOLE_STATUS disc[NUM_RAW][NUM_COL];
}BOARD_SNAPSHOT;

typedef struct GAME_STATUS
{
	GAME_STATE_e state;
	BOARD_SNAPSHOT bord;
	PLAYER_e colorTurn;
}GAME_STATUS;

typedef enum PLAYER_LEVEL_e
{
	EASY_LEVEL = 0,
	MEDIUN_LEVEL = 1,
	HARD_LEVEL = 2
}PLAYER_LEVEL_e;