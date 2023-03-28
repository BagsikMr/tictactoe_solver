#include <iostream>
#include <string.h>

using namespace std;

typedef struct
{
	int N, M, K;
	char** board;
	char active_player,enemy;
	int possible_moves;
	int ile;
}gameEngine;

#define RIGHT_X 1 // pole o 1 w prawo
#define LEFT_X -1 // pole o 1 w lewo
#define DOWN_Y 1 //pole o 1 w góre
#define SAME_XY 0 //te samo pole

void StartedData(gameEngine* gameEngine);
void DeleteArray(gameEngine* gameEngine);
void CreateGameBoard(gameEngine* gameEngine);
void CoutTable(gameEngine* gameEngine);
void PrintAllPossibleMoves(gameEngine* gameEngine);
void GenAllPosMov(gameEngine* gameEngine);
bool CheckSide(gameEngine* gameEngine, char active_player, int i, int j, int tempx, int tempy);
char CheckWin(gameEngine* gameEngine);
bool IsWin(gameEngine* game);
bool CutIfWin(gameEngine* gameEngine);
void GAPMCutIfGameOver(gameEngine* gameEngine);
char EnemyPlayer(char active_player);
bool CanEnemyWin(gameEngine* gameEngine, char active_player);
bool KBeamOptimize(gameEngine* gameEngine, char active_player);
char Minimax(gameEngine* gameEngine, int possible_moves, char active_player, int depth);
void SolveGameState(gameEngine* gameEngine);
int main()
{
	char command[40];
	gameEngine gameEngine;
	gameEngine.ile = 0;
	StartedData(&gameEngine);

	while (cin.good())
	{
		cin >> command;
		cin >> gameEngine.N >> gameEngine.M >> gameEngine.K >> gameEngine.active_player;

		gameEngine.possible_moves = 0;
		CreateGameBoard(&gameEngine);

			if (strcmp(command, "GEN_ALL_POS_MOV") == 0)
			{
				if (IsWin(&gameEngine))
				{
					cout << "0\n";
				}
				else GenAllPosMov(&gameEngine);
			}
			else if (strcmp(command, "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER") == 0)
			{
				if (IsWin(&gameEngine))
				{
					cout << "0\n";
				}
				else GAPMCutIfGameOver(&gameEngine);
			}
			else if (strcmp(command, "SOLVE_GAME_STATE") == 0)
			{
				SolveGameState(&gameEngine);
			}

			//cout << gameEngine.ile;
		DeleteArray(&gameEngine);
	}
	
}
void StartedData(gameEngine* gameEngine)
{
	gameEngine->N = 0;
	gameEngine->M = 0;
	gameEngine->K = 0;
	gameEngine->active_player = 0;
	gameEngine->enemy = 0;
	gameEngine->possible_moves = 0;
}
void DeleteArray(gameEngine* gameEngine)
{
	for (int i = 0; i < gameEngine->N; i++) //dynamiczna dealokacja tablicy 2d o podanych rozmiarach
	{
		delete[] gameEngine->board[i];
	}
	delete gameEngine->board;
}
void CreateGameBoard(gameEngine* gameEngine)
{
	gameEngine->board = new char* [gameEngine->N];
	for (int i = 0; i < gameEngine->N; i++) //dynamiczna alokacja tablicy 2d a podanych rozmiarach
	{
		gameEngine->board[i] = new char[gameEngine->M];
		for (int j = 0; j < gameEngine->M; j++)
		{
			cin >> gameEngine->board[i][j];
			if (gameEngine->board[i][j] == '0')
			{
				gameEngine->possible_moves++;
			}
		}
	}
}
void CoutTable(gameEngine* gameEngine)
{
	for (int i = 0; i < gameEngine->N; i++)
	{
		for (int j = 0; j < gameEngine->M; j++)
		{
			cout << gameEngine->board[i][j] << " ";
		}
		cout << "\n";
	}
}
void PrintAllPossibleMoves(gameEngine* gameEngine)
{
	for (int i = 0; i < gameEngine->N; i++)
	{
		for (int j = 0; j < gameEngine->M; j++)
		{
			if (gameEngine->board[i][j] == '0')
			{
				gameEngine->possible_moves--;
				gameEngine->board[i][j] = gameEngine->active_player;

				CoutTable(gameEngine);

				gameEngine->board[i][j] = '0'; //powrót do stanu sprzed wpisania active playera w pole
			}
		}
	}
}
void GenAllPosMov(gameEngine* gameEngine)
{
	cout << gameEngine->possible_moves << "\n";
	PrintAllPossibleMoves(gameEngine);
}
bool CheckSide(gameEngine* gameEngine, char active_player, int i, int j, int tempx, int tempy)
{
	bool win = true; // na początku ustawiam true i jeśli ciąg znaków będzie krótszy od warunku zwycięstwa to zmienie na false

	for (int a = 0; a < gameEngine->K; a++)
	{
		if (i + tempy * a < gameEngine->N && j + tempx * a < gameEngine->M && i + tempy * a >= 0 && j + tempx * a >= 0)
		{
			if (gameEngine->board[i + a * tempy][j + a * tempx] != active_player)
			{
				win = false;
			}
		}
		else
		{
			win = false;
		}
	}
	if (i + tempy < gameEngine->N && j + tempx < gameEngine->M && i + tempy >= 0 && j + tempx >= 0) {

		if (win == true)
		{

			return true;
		}
	}
	return false;
}
char CheckWin(gameEngine* gameEngine)//dla sprawdzenia zwycięstwa muszę sprawdzić 4 kierunki
{
	char temp; //przyjmie wartosc znaku ktory stoi aktualnie na tablicy
	for (int i = 0; i < gameEngine->N; i++)
	{
		for (int j = 0; j < gameEngine->M; j++)
		{
			if (gameEngine->board[i][j] != '0')
			{
				temp = gameEngine->board[i][j];
				if (CheckSide(gameEngine, temp, i, j, RIGHT_X, DOWN_Y)) //prawy dol //sprawdzenie zwyciestwa dla 4 kierunków
				{
					return temp;
				}
				if (CheckSide(gameEngine, temp, i, j, RIGHT_X, SAME_XY)) //prawo
				{
					return temp;
				}
				if (CheckSide(gameEngine, temp, i, j, SAME_XY, DOWN_Y)) //dol
				{
					return temp;
				}
				if (CheckSide(gameEngine, temp, i, j, LEFT_X, DOWN_Y)) //lewy dol
				{
					return temp;
				}
			}
		}
	}
	return '0';
}
bool IsWin(gameEngine* game)
{
	char won = CheckWin(game);
	if (won != '0')
	{
		return true;
	}
	else return false;
}
bool CutIfWin(gameEngine* gameEngine)
{
	for (int i = 0; i < gameEngine->N; i++)
	{
		for (int j = 0; j < gameEngine->M; j++)
		{
			if (gameEngine->board[i][j] == '0')
			{
				gameEngine->board[i][j] = gameEngine->active_player;

				if (IsWin(gameEngine))
				{
					cout << "1\n";
					CoutTable(gameEngine);
					return true;
				}

				gameEngine->board[i][j] = '0'; //powrót do stanu sprzed wpisania active playera w pole
			}
		}
	}
	return false;
}
void GAPMCutIfGameOver(gameEngine* gameEngine) // GAPM - Gen All Pos Mov
{
	if (!CutIfWin(gameEngine)) //jak da mi fałsz to pokaże wszystkie możliwości
	{
		GenAllPosMov(gameEngine);
	}
}
char EnemyPlayer(char active_player)
{
	if (active_player == '1') return '2';
	else if (active_player == '2') return '1';
	return 0;
}
bool CanEnemyWin(gameEngine* gameEngine, char active_player)
{
	for (int i = 0; i < gameEngine->N; i++)
	{
		for (int j = 0; j < gameEngine->M; j++)
		{
			if (gameEngine->board[i][j] == '0')
			{
				gameEngine->board[i][j] = active_player;
				if (IsWin(gameEngine))
				{
					gameEngine->board[i][j] = '0';
					return true;
				}
				gameEngine->board[i][j] = '0';
			}
		}
	}
	return false;
}
bool KBeamOptimize(gameEngine* gameEngine, char active_player) //niewielka modyfikacja checkwina
{
	int how_much_wins = 0;
	if (!CanEnemyWin(gameEngine, EnemyPlayer(active_player)))
	{
		for (int i = 0; i < gameEngine->N; i++)
		{
			for (int j = 0; j < gameEngine->M; j++)
			{
				if (gameEngine->board[i][j] == '0')
				{
					gameEngine->board[i][j] = active_player;
					if (IsWin(gameEngine))
					{
						how_much_wins++;
					}
					gameEngine->board[i][j] = '0';

					if (how_much_wins >= 2)
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}
char Minimax(gameEngine* gameEngine, int possible_moves, char active_player, int depth)
{
	char score = '0', bestscore = '3';
	gameEngine->ile++;
	//CoutTable(gameEngine);
	//cout << endl;
	if (possible_moves != 0)
	{
		possible_moves--;

		for (int i = 0; i < gameEngine->N; i++)
		{
			for (int j = 0; j < gameEngine->M; j++)
			{
				if (gameEngine->board[i][j] == '0')
				{
					gameEngine->board[i][j] = active_player;
					if (KBeamOptimize(gameEngine, active_player))
					{
						gameEngine->board[i][j] = '0';
						return active_player;
					}
					if (IsWin(gameEngine))
					{
						gameEngine->board[i][j] = '0';
						return active_player;
					}

					gameEngine->board[i][j] = '0';
				}
			}
		}

		for (int i = 0; i < gameEngine->N; i++)
		{
			for (int j = 0; j < gameEngine->M; j++)
			{
				if (gameEngine->board[i][j] == '0')
				{
					gameEngine->board[i][j] = active_player;

					score = Minimax(gameEngine, possible_moves, EnemyPlayer(active_player), depth + 1);


					if (score == active_player) //zwyciestwo active playera
					{
						bestscore = score;
						gameEngine->board[i][j] = '0';
						return score;
					}
					else if (score == '0' && bestscore != active_player) //
					{
						bestscore = score;
					}
					else if (score == EnemyPlayer(active_player) && bestscore != '0' && bestscore != active_player)//
					{
						bestscore = score;
					}
					gameEngine->board[i][j] = '0';
				}
			}
		}
		return bestscore;
	}
	else
	{
		return '0';
	}
	return '0';
}
void SolveGameState(gameEngine* gameEngine)
{
	char score, won_pl = CheckWin(gameEngine);
	if (won_pl == '1')
	{
		cout << "FIRST_PLAYER_WINS\n";
	}
	else if (won_pl == '2')
	{
		cout << "SECOND_PLAYER_WINS\n";
	}
	else
	{
		score = Minimax(gameEngine, gameEngine->possible_moves, gameEngine->active_player, 0);

		switch (score)
		{
		case '1':
			cout << "FIRST_PLAYER_WINS\n";
			break;
		case '2':
			cout << "SECOND_PLAYER_WINS\n";
			break;
		case '0':
			cout << "BOTH_PLAYERS_TIE\n";
			break;
		}
	}
}