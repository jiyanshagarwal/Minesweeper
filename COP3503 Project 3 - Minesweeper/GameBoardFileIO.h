#pragma once
#include "GameBoard.h"

GameBoard ReadBoard(const char* file_name);
void WriteBoard(const GameBoard& board, const char* file_name);