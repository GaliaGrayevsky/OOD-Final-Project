#pragma once

#include "Disc.h"
#include "GameConst.h"


class CBoard
{
public:
	CBoard();

	void InitBoard();

	RETCODE_e SetDiscInPlace(CDisc& a_disc, int a_dstColumn);
	void GetBoardState(BOARD_SNAPSHOT& a_bord);
	bool IsBoardFull();
	void PrintBoard();

	HOLE_STATUS* GetBoardRaw(int a_raw, int col, ORIENTATION_e a_orientation);

private:
	CDisc* m_board[NUM_RAW][NUM_COL];

};

