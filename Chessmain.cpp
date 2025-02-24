#include<iostream>
#include<vector>
#include<string>
#include<fstream>

//enum of consts for more readable code
enum pieceType : const int
{
	PAWN = 1, ROOK, HORSE, BISHOP, QUEEN, KING
};

int turn = 0;
int win = 0;
int bDead = 0;
int wDead = 0;

std::string blackPawnCol = "\033[100;47;30mP\033[0m";
std::string blackRookCol = "\033[100;47;30mR\033[0m";
std::string blackBishopCol = "\033[100;47;30mB\033[0m";
std::string blackHorseCol = "\033[100;47;30mH\033[0m";
std::string blackQueenCol = "\033[100;47;30mQ\033[0m";
std::string blackKingCol = "\033[100;47;30mK\033[0m";

std::string whitePawnCol = "\033[100;47;93mP\033[0m";
std::string whiteRookCol = "\033[100;47;93mR\033[0m";
std::string whiteBishopCol = "\033[100;47;93mB\033[0m";
std::string whiteHorseCol = "\033[100;47;93mH\033[0m";
std::string whiteQueenCol = "\033[100;47;93mQ\033[0m";
std::string whiteKingCol = "\033[100;47;93mK\033[0m";

std::string whiteTile = "\033[100;47;10m       \033[0m";

std::string board[8][12] = {
	{"\033[100;47;10m \033[0m", " ", "\033[100;47;10m \033[0m", " ", "\033[100;47;10m \033[0m", " ", "\033[100;47;10m \033[0m", " ", "\033[100;47;10m \033[0m"," ", "\033[100;47;10m \033[0m", " "},   // row 1
	{" ", "\033[100;47;10m \033[0m", " ", "\033[100;47;10m \033[0m", " ", "\033[100;47;10m \033[0m", " ", "\033[100;47;10m \033[0m", " ", "\033[100;47;10m \033[0m", " ", "\033[100;47;10m \033[0m"},   // row 2
	{"\033[100;47;10m \033[0m", " ", "\033[100;47;10m \033[0m", " ", "\033[100;47;10m \033[0m", " ", "\033[100;47;10m \033[0m", " ", "\033[100;47;10m \033[0m"," ", "\033[100;47;10m \033[0m", " "},   // row 3
	{" ", "\033[100;47;10m \033[0m", " ", "\033[100;47;10m \033[0m", " ", "\033[100;47;10m \033[0m", " ", "\033[100;47;10m \033[0m", " ", "\033[100;47;10m \033[0m", " ", "\033[100;47;10m \033[0m"},   // row 4
	{"\033[100;47;10m \033[0m", " ", "\033[100;47;10m \033[0m", " ", "\033[100;47;10m \033[0m", " ", "\033[100;47;10m \033[0m", " ", "\033[100;47;10m \033[0m"," ", "\033[100;47;10m \033[0m", " "},   // row 5
	{" ", "\033[100;47;10m \033[0m", " ", "\033[100;47;10m \033[0m", " ", "\033[100;47;10m \033[0m", " ", "\033[100;47;10m \033[0m", " ", "\033[100;47;10m \033[0m", " ", "\033[100;47;10m \033[0m"},   // row 6
	{"\033[100;47;10m \033[0m", " ", "\033[100;47;10m \033[0m", " ", "\033[100;47;10m \033[0m", " ", "\033[100;47;10m \033[0m", " ", "\033[100;47;10m \033[0m"," ", "\033[100;47;10m \033[0m", " "},   // row 7
	{" ", "\033[100;47;10m \033[0m", " ", "\033[100;47;10m \033[0m", " ", "\033[100;47;10m \033[0m", " ", "\033[100;47;10m \033[0m", " ", "\033[100;47;10m \033[0m", " ", "\033[100;47;10m \033[0m"}	  // row 8
};

class bPieces {
public:
	int death = 0;
	int movesMade = 0;
	int x = 0;
	int y = 0;
	int check = 0;
	int piece = 1;
	int enPassantCnt = 0;

	bPieces()
	{}

	void piecePlacement(int X, int Y, int typePiece)
	{
		x = X;
		y = Y;
		piece = typePiece;
		death = 0;
		movesMade = 0;
		check = 0;
		enPassantCnt = 0;
		switch (typePiece)
		{
		case PAWN:
			//displays white background with piece if both x and y are even coordinates because
			//of the alternating pattern of the board
			if ((X % 2 == 0 && Y % 2 == 0) || (X % 2 == 1 && Y % 2 == 1))
			{
				board[Y][X] = blackPawnCol;
				break;
			}
			board[Y][X] = "\033[10;1;30mP\033[0m";
			break;
		case ROOK:
			if ((X % 2 == 0 && Y % 2 == 0) || (X % 2 == 1 && Y % 2 == 1))
			{
				board[Y][X] = blackRookCol;
				break;
			}
			board[Y][X] = "\033[10;1;30mR\033[0m";
			break;
		case BISHOP:
			if ((X % 2 == 0 && Y % 2 == 0) || (X % 2 == 1 && Y % 2 == 1))
			{
				board[Y][X] = blackBishopCol;
				break;
			}
			board[Y][X] = "\033[10;1;30mB\033[0m";
			break;
		case HORSE:
			if ((X % 2 == 0 && Y % 2 == 0) || (X % 2 == 1 && Y % 2 == 1))
			{
				board[Y][X] = blackHorseCol;
				break;
			}
			board[Y][X] = "\033[10;1;30mH\033[0m";
			break;
		case QUEEN:
			if ((X % 2 == 0 && Y % 2 == 0) || (X % 2 == 1 && Y % 2 == 1))
			{
				board[Y][X] = blackQueenCol;
				break;
			}
			board[Y][X] = "\033[10;1;30mQ\033[0m";
			break;
		case KING:
			if ((X % 2 == 0 && Y % 2 == 0) || (X % 2 == 1 && Y % 2 == 1))
			{
				board[Y][X] = blackKingCol;
				break;
			}
			board[Y][X] = "\033[10;1;30mK\033[0m";
			break;
		default:
			break;
		}
	}

	bPieces(int X, int Y, int typePiece)
	{
		piecePlacement(X, Y, typePiece);
	}

	void dead(int numDead)
	{
		if (death == 1)
		{
			if (numDead < 9)
			{
				if ((x % 2 == 0 && y % 2 == 0) || (x % 2 == 1 && y % 2 == 1))
				{
					board[y][x] = "\033[100;47;10m \033[0m";
				}
				else
				{
					board[y][x] = " ";
				}
				x = 8;
				y = 8 - numDead;

				switch (piece)
				{
				case PAWN:
					if ((x % 2 == 0 && y % 2 == 0) || (x % 2 == 1 && y % 2 == 1))
					{
						board[y][x] = blackPawnCol;
						return;
					}
					board[y][x] = "\033[10;1;30mP\033[0m";
					break;
				case ROOK:
					if ((x % 2 == 0 && y % 2 == 0) || (x % 2 == 1 && y % 2 == 1))
					{
						board[y][x] = blackRookCol;
						return;
					}
					board[y][x] = "\033[10;1;30mR\033[0m";
					break;
				case HORSE:
					if ((x % 2 == 0 && y % 2 == 0) || (x % 2 == 1 && y % 2 == 1))
					{
						board[y][x] = blackHorseCol;
						return;
					}
					board[y][x] = "\033[10;1;30mH\033[0m";
					break;
				case BISHOP:
					if ((x % 2 == 0 && y % 2 == 0) || (x % 2 == 1 && y % 2 == 1))
					{
						board[y][x] = blackBishopCol;
						return;
					}
					board[y][x] = "\033[10;1;30mB\033[0m";
					break;
				case QUEEN:
					if ((x % 2 == 0 && y % 2 == 0) || (x % 2 == 1 && y % 2 == 1))
					{
						board[y][x] = blackQueenCol;
						return;
					}
					board[y][x] = "\033[10;1;30mQ\033[0m";
					break;
				default:
					break;
				}
			}
			if (numDead > 8)
			{
				if ((x % 2 == 0 && y % 2 == 0) || (x % 2 == 1 && y % 2 == 1))
				{
					board[y][x] = "\033[100;47;10m \033[0m";
				}
				else
				{
					board[y][x] = " ";
				}
				x = 9;
				y = 16 - numDead;

				switch (piece)
				{
				case PAWN:
					if ((x % 2 == 0 && y % 2 == 0) || (x % 2 == 1 && y % 2 == 1))
					{
						board[y][x] = blackPawnCol;
						return;
					}
					board[y][x] = "\033[10;1;30mP\033[0m";
					break;
				case ROOK:
					if ((x % 2 == 0 && y % 2 == 0) || (x % 2 == 1 && y % 2 == 1))
					{
						board[y][x] = blackRookCol;
						return;
					}
					board[y][x] = "\033[10;1;30mR\033[0m";
					break;
				case HORSE:
					if ((x % 2 == 0 && y % 2 == 0) || (x % 2 == 1 && y % 2 == 1))
					{
						board[y][x] = blackHorseCol;
						return;
					}
					board[y][x] = "\033[10;1;30mH\033[0m";
					break;
				case BISHOP:
					if ((x % 2 == 0 && y % 2 == 0) || (x % 2 == 1 && y % 2 == 1))
					{
						board[y][x] = blackBishopCol;
						return;
					}
					board[y][x] = "\033[10;1;30mB\033[0m";
					break;
				case QUEEN:
					if ((x % 2 == 0 && y % 2 == 0) || (x % 2 == 1 && y % 2 == 1))
					{
						board[y][x] = blackQueenCol;
						return;
					}
					board[y][x] = "\033[10;1;30mQ\033[0m";
					break;
				default:
					break;
				}
			}
		}
	}
};

bPieces pawn1(0, 6, PAWN), pawn2(1, 6, PAWN), pawn3(2, 6, PAWN), pawn4(3, 6, PAWN), pawn5(4, 6, PAWN), 
pawn6(5, 6, PAWN), pawn7(6, 6, PAWN), pawn8(7, 6, PAWN), rook1(0, 7, ROOK), rook2(7, 7, ROOK), 
bishop1(2, 7, BISHOP), bishop2(5, 7, BISHOP), horse1(1, 7, HORSE), horse2(6, 7, HORSE), queen(4, 7, QUEEN), 
king(3, 7, KING);

std::vector<bPieces*> bPiece;

class wPieces {
public:
	int death = 0;
	int movesMade = 0;
	int x = 0;
	int y = 0;
	int check = 0;
	int piece = 1;
	int enPassantCnt = 0;

	wPieces()
	{}

	void piecePlacement(int X, int Y, int typePiece)
	{
		x = X;
		y = Y;
		piece = typePiece;
		death = 0;
		movesMade = 0;
		check = 0;
		enPassantCnt = 0;
		switch (typePiece)
		{
		case PAWN:
			if ((X % 2 == 0 && Y % 2 == 0) || (X % 2 == 1 && Y % 2 == 1))
			{
				board[Y][X] = whitePawnCol;
				break;
			}
			board[Y][X] = "\x1B[93mP\033[0m";
			break;
		case ROOK:
			if ((X % 2 == 0 && Y % 2 == 0) || (X % 2 == 1 && Y % 2 == 1))
			{
				board[Y][X] = whiteRookCol;
				break;
			}
			board[Y][X] = "\x1B[93mR\033[0m";
			break;
		case BISHOP:
			if ((X % 2 == 0 && Y % 2 == 0) || (X % 2 == 1 && Y % 2 == 1))
			{
				board[Y][X] = whiteBishopCol;
				break;
			}
			board[Y][X] = "\x1B[93mB\033[0m";
			break;
		case HORSE:
			if ((X % 2 == 0 && Y % 2 == 0) || (X % 2 == 1 && Y % 2 == 1))
			{
				board[Y][X] = whiteHorseCol;
				break;
			}
			board[Y][X] = "\x1B[93mH\033[0m";
			break;
		case QUEEN:
			if ((X % 2 == 0 && Y % 2 == 0) || (X % 2 == 1 && Y % 2 == 1))
			{
				board[Y][X] = whiteQueenCol;
				break;
			}
			board[Y][X] = "\x1B[93mQ\033[0m";
			break;
		case KING:
			if ((X % 2 == 0 && Y % 2 == 0) || (X % 2 == 1 && Y % 2 == 1))
			{
				board[Y][X] = whiteKingCol;
				break;
			}
			board[Y][X] = "\x1B[93mK\033[0m";
			break;
		default:
			break;
		}
	}

	wPieces(int X, int Y, int typePiece)
	{
		piecePlacement(X, Y, typePiece);
	}

	void dead(int numDead)
	{
		if (death == 1)
		{
			if (numDead < 9)
			{
				if ((x % 2 == 0 && y % 2 == 0) || (x % 2 == 1 && y % 2 == 1))
				{
					board[y][x] = "\033[100;47;10m \033[0m";
				}
				else
				{
					board[y][x] = " ";
				}
				x = 10;
				y = 8 - numDead;

				switch (piece)
				{
				case PAWN:
					if ((x % 2 == 0 && y % 2 == 0) || (x % 2 == 1 && y % 2 == 1))
					{
						board[y][x] = whitePawnCol;
						return;
					}
					board[y][x] = "\x1B[93mP\033[0m";
					break;
				case ROOK:
					if ((x % 2 == 0 && y % 2 == 0) || (x % 2 == 1 && y % 2 == 1))
					{
						board[y][x] = whiteRookCol;
						return;
					}
					board[y][x] = "\x1B[93mR\033[0m";
					break;
				case HORSE:
					if ((x % 2 == 0 && y % 2 == 0) || (x % 2 == 1 && y % 2 == 1))
					{
						board[y][x] = whiteHorseCol;
						return;
					}
					board[y][x] = "\x1B[93mH\033[0m";
					break;
				case BISHOP:
					if ((x % 2 == 0 && y % 2 == 0) || (x % 2 == 1 && y % 2 == 1))
					{
						board[y][x] = whiteBishopCol;
						return;
					}
					board[y][x] = "\x1B[93mB\033[0m";
					break;
				case QUEEN:
					if ((x % 2 == 0 && y % 2 == 0) || (x % 2 == 1 && y % 2 == 1))
					{
						board[y][x] = whiteQueenCol;
						return;
					}
					board[y][x] = "\x1B[93mP\033[0m";
					break;
				default:
					break;
				}
			}
			if (numDead > 8)
			{
				if ((x % 2 == 0 && y % 2 == 0) || (x % 2 == 1 && y % 2 == 1))
				{
					board[y][x] = "\033[100;47;10m \033[0m";
				}
				else
				{
					board[y][x] = " ";
				}
				x = 11;
				y = 16 - numDead;

				switch (piece)
				{
				case PAWN:
					if ((x % 2 == 0 && y % 2 == 0) || (x % 2 == 1 && y % 2 == 1))
					{
						board[y][x] = whitePawnCol;
						return;
					}
					board[y][x] = "\x1B[93mP\033[0m";
					break;
				case ROOK:
					if ((x % 2 == 0 && y % 2 == 0) || (x % 2 == 1 && y % 2 == 1))
					{
						board[y][x] = whiteRookCol;
						return;
					}
					board[y][x] = "\x1B[93mR\033[0m";
					break;
				case HORSE:
					if ((x % 2 == 0 && y % 2 == 0) || (x % 2 == 1 && y % 2 == 1))
					{
						board[y][x] = whiteHorseCol;
						return;
					}
					board[y][x] = "\x1B[93mH\033[0m";
					break;
				case BISHOP:
					if ((x % 2 == 0 && y % 2 == 0) || (x % 2 == 1 && y % 2 == 1))
					{
						board[y][x] = whiteBishopCol;
						return;
					}
					board[y][x] = "\x1B[93mB\033[0m";
					break;
				case QUEEN:
					if ((x % 2 == 0 && y % 2 == 0) || (x % 2 == 1 && y % 2 == 1))
					{
						board[y][x] = whiteQueenCol;
						return;
					}
					board[y][x] = "\x1B[93mP\033[0m";
					break;
				default:
					break;
				}
			}
		}
	}
};

wPieces wpawn1(0, 1, PAWN), wpawn2(1, 1, PAWN), wpawn3(2, 1, PAWN), wpawn4(3, 1, PAWN), wpawn5(4, 1, PAWN), 
wpawn6(5, 1, PAWN), wpawn7(6, 1, PAWN), wpawn8(7, 1, PAWN), wrook1(0, 0, ROOK), wrook2(7, 0, ROOK),
wbishop1(2, 0, BISHOP), wbishop2(5, 0, BISHOP), whorse1(1, 0, HORSE), whorse2(6, 0, HORSE), wqueen(4, 0, QUEEN),
wking(3, 0, KING);

std::vector<wPieces*> wPiece;

//add pieces to associated vectors for later looping through objects
void defaultVectors()
{
	//add references to black pieces in a vector
	bPiece.push_back(&pawn1);
	bPiece.push_back(&pawn2);
	bPiece.push_back(&pawn3);
	bPiece.push_back(&pawn4);
	bPiece.push_back(&pawn5);
	bPiece.push_back(&pawn6);
	bPiece.push_back(&pawn7);
	bPiece.push_back(&pawn8);
	bPiece.push_back(&rook1);
	bPiece.push_back(&rook2);
	bPiece.push_back(&bishop1);
	bPiece.push_back(&bishop2);
	bPiece.push_back(&horse1);
	bPiece.push_back(&horse2);
	bPiece.push_back(&queen);
	bPiece.push_back(&king);

	//add references to white pieces in a vector
	wPiece.push_back(&wpawn1);
	wPiece.push_back(&wpawn2);
	wPiece.push_back(&wpawn3);
	wPiece.push_back(&wpawn4);
	wPiece.push_back(&wpawn5);
	wPiece.push_back(&wpawn6);
	wPiece.push_back(&wpawn7);
	wPiece.push_back(&wpawn8);
	wPiece.push_back(&wrook1);
	wPiece.push_back(&wrook2);
	wPiece.push_back(&wbishop1);
	wPiece.push_back(&wbishop2);
	wPiece.push_back(&whorse1);
	wPiece.push_back(&whorse2);
	wPiece.push_back(&wqueen);
	wPiece.push_back(&wking);
}

//displays the current board
void drawBoard()
{
	system("cls");

	//your board
	std::cout << "       0      1      2      3      4      5      6      7             killed black pieces        killed white pieces" << std::endl << std::endl;
	std::cout << "    " << whiteTile << "    " << "   " << whiteTile << "   " << "    " << whiteTile << "   " << "    " << whiteTile << "   " << "                  " << whiteTile << "       " << "             " << whiteTile << std::endl;
	std::cout << " 0 " << " " << "\033[100;47;10m   \033[0m" << board[0][0] << "\033[100;47;10m   \033[0m" << "   " << board[0][1] << "   " << "\033[100;47;10m   \033[0m" << board[0][2] << "\033[100;47;10m   \033[0m" << "   " << board[0][3] << "   " << "\033[100;47;10m   \033[0m" << board[0][4] << "\033[100;47;10m   \033[0m" << "   " << board[0][5] << "   " << "\033[100;47;10m   \033[0m" << board[0][6] << "\033[100;47;10m   \033[0m" << "   " << board[0][7] << "              1  " << "\033[100;47;10m   \033[0m" << board[0][8] << "\033[100;47;10m   \033[0m" << "   " << board[0][9] << "   " << "          1  " << "\033[100;47;10m   \033[0m" << board[0][10] << "\033[100;47;10m   \033[0m" << "   " << board[0][11] << std::endl;
	std::cout << "    " << whiteTile << "    " << "   " << whiteTile << "    " << "   " << whiteTile << "    " << "   " << whiteTile << "    " << "                 " << whiteTile << "       " "             " << whiteTile << std::endl;
	std::cout << "    " << "       " << whiteTile << "       " << whiteTile << "       " << whiteTile << "       " << whiteTile << "                     " << whiteTile  << "             " << "       " << whiteTile << std::endl;
	std::cout << " 1 " << "    " << board[1][0] << "   " << "\033[100;47;10m   \033[0m" << board[1][1] << "\033[100;47;10m   \033[0m" << "   " << board[1][2] << "   " << "\033[100;47;10m   \033[0m" << board[1][3] << "\033[100;47;10m   \033[0m" << "   " << board[1][4] << "   " << "\033[100;47;10m   \033[0m" << board[1][5] << "\033[100;47;10m   \033[0m" << "   " << board[1][6] << "   " << "\033[100;47;10m   \033[0m" << board[1][7] << "\033[100;47;10m   \033[0m" << "           2  " << "   " << board[1][8] << "   " << "\033[100;47;10m   \033[0m" << board[1][9] << "\033[100;47;10m   \033[0m" << "          2  " << "   " << board[1][10] << "   " << "\033[100;47;10m   \033[0m" << board[1][11] << "\033[100;47;10m   \033[0m" << std::endl;
	std::cout << "         " << "  " << whiteTile << "       " << whiteTile << "       " << whiteTile << "       " << whiteTile << "                     " << whiteTile << "             " << "       " << whiteTile << std::endl;
	std::cout << "    " << whiteTile << "       " << whiteTile << "       " << whiteTile << "       " << whiteTile << "       "  << "              " << whiteTile << "       " << "             " << whiteTile << std::endl;
	std::cout << " 2 " << " " << "\033[100;47;10m   \033[0m" << board[2][0] << "\033[100;47;10m   \033[0m" << "   " << board[2][1] << "   " << "\033[100;47;10m   \033[0m" << board[2][2] << "\033[100;47;10m   \033[0m" << "   " << board[2][3] << "   " << "\033[100;47;10m   \033[0m" << board[2][4] << "\033[100;47;10m   \033[0m" << "   " << board[2][5] << "   " << "\033[100;47;10m   \033[0m" << board[2][6] << "\033[100;47;10m   \033[0m" << "   " << board[2][7] << "              3  " << "\033[100;47;10m   \033[0m" << board[2][8] << "\033[100;47;10m   \033[0m" << "   " << board[2][9] << "   " << "          3  " << "\033[100;47;10m   \033[0m" << board[2][10] << "\033[100;47;10m   \033[0m" << "   " << board[2][11] << std::endl;
	std::cout << "    " << whiteTile << "       " << whiteTile << "       " << whiteTile << "       " << whiteTile << "       " << "              " << whiteTile << "       " << "             " << whiteTile << std::endl;
	std::cout << "         " << "  " << whiteTile << "       " << whiteTile << "       " << whiteTile << "       " << whiteTile << "                     " << whiteTile << "             " << "       " << whiteTile << std::endl;
	std::cout << " 3 " << "    " << board[3][0] << "   " << "\033[100;47;10m   \033[0m" << board[3][1] << "\033[100;47;10m   \033[0m" << "   " << board[3][2] << "   " << "\033[100;47;10m   \033[0m" << board[3][3] << "\033[100;47;10m   \033[0m" << "   " << board[3][4] << "   " << "\033[100;47;10m   \033[0m" << board[3][5] << "\033[100;47;10m   \033[0m" << "   " << board[3][6] << "   " << "\033[100;47;10m   \033[0m" << board[3][7] << "\033[100;47;10m   \033[0m" << "           4  " << "   " << board[3][8] << "   " << "\033[100;47;10m   \033[0m" << board[3][9] << "\033[100;47;10m   \033[0m" << "          4  " << "   " << board[3][10] << "   " << "\033[100;47;10m   \033[0m" << board[3][11] << "\033[100;47;10m   \033[0m" << std::endl;
	std::cout << "           " << whiteTile << "       " << whiteTile << "       " << whiteTile << "       " << whiteTile << "                     " << whiteTile << "             " << "       " << whiteTile << std::endl;
	std::cout << "    " << whiteTile << "       " << whiteTile << "       " << whiteTile << "       " << whiteTile << "       " << "              " << whiteTile << "       " << "             " << whiteTile << std::endl;
	std::cout << " 4 " << " " << "\033[100;47;10m   \033[0m" << board[4][0] << "\033[100;47;10m   \033[0m" << "   " << board[4][1] << "   " << "\033[100;47;10m   \033[0m" << board[4][2] << "\033[100;47;10m   \033[0m" << "   " << board[4][3] << "   " << "\033[100;47;10m   \033[0m" << board[4][4] << "\033[100;47;10m   \033[0m" << "   " << board[4][5] << "   " << "\033[100;47;10m   \033[0m" << board[4][6] << "\033[100;47;10m   \033[0m" << "   " << board[4][7] << "   " << "           5  " << "\033[100;47;10m   \033[0m" << board[4][8] << "\033[100;47;10m   \033[0m" << "   " << board[4][9] << "   " << "          5  " << "\033[100;47;10m   \033[0m" << board[4][10] << "\033[100;47;10m   \033[0m" << "   " << board[4][11] << "   " << std::endl;
	std::cout << "    " << whiteTile << "       " << whiteTile << "       " << whiteTile << "       " << whiteTile << "       " << "              " << whiteTile << "       " << "             " << whiteTile << std::endl;
	std::cout << "         " << "  " << whiteTile << "       " << whiteTile << "       " << whiteTile << "       " << whiteTile << "                     " << whiteTile << "             " << "       " << whiteTile << std::endl;
	std::cout << " 5 " << "    " << board[5][0] << "   " << "\033[100;47;10m   \033[0m" << board[5][1] << "\033[100;47;10m   \033[0m" << "   " << board[5][2] << "   " << "\033[100;47;10m   \033[0m" << board[5][3] << "\033[100;47;10m   \033[0m" << "   " << board[5][4] << "   " << "\033[100;47;10m   \033[0m" << board[5][5] << "\033[100;47;10m   \033[0m" << "   " << board[5][6] << "   " << "\033[100;47;10m   \033[0m" << board[5][7] << "\033[100;47;10m   \033[0m" << "           6  " << "   " << board[5][8] << "   " << "\033[100;47;10m   \033[0m" << board[5][9] << "\033[100;47;10m   \033[0m" << "          6  " << "   " << board[5][10] << "   " << "\033[100;47;10m   \033[0m" << board[5][11] << "\033[100;47;10m   \033[0m" << std::endl;
	std::cout << "         " << "  " << whiteTile << "       " << whiteTile << "       " << whiteTile << "       " << whiteTile << "                     " << whiteTile << "             " << "       " << whiteTile << std::endl;
	std::cout << "    " << whiteTile << "       " << whiteTile << "       " << whiteTile << "       " << whiteTile << "       " << "              " << whiteTile << "       " << "             " << whiteTile << std::endl;
	std::cout << " 6 " << " " << "\033[100;47;10m   \033[0m" << board[6][0] << "\033[100;47;10m   \033[0m" << "   " << board[6][1] << "   " << "\033[100;47;10m   \033[0m" << board[6][2] << "\033[100;47;10m   \033[0m" << "   " << board[6][3] << "   " << "\033[100;47;10m   \033[0m" << board[6][4] << "\033[100;47;10m   \033[0m" << "   " << board[6][5] << "   " << "\033[100;47;10m   \033[0m" << board[6][6] << "\033[100;47;10m   \033[0m" << "   " << board[6][7] << "   " << "           7  " << "\033[100;47;10m   \033[0m" << board[6][8] << "\033[100;47;10m   \033[0m" << "   " << board[6][9] << "   " << "          7  " << "\033[100;47;10m   \033[0m" << board[6][10] << "\033[100;47;10m   \033[0m" << "   " << board[6][11] << std::endl;
	std::cout << "    " << whiteTile << "       " << whiteTile << "       " << whiteTile << "       " << whiteTile << "       " << "              " << whiteTile << "       " << "             " << whiteTile << std::endl;
	std::cout << "         " << "  " << whiteTile << "       " << whiteTile << "       " << whiteTile << "       " << whiteTile << "                     " << whiteTile << "             " << "       " << whiteTile << std::endl;
	std::cout << " 7 " << "    " << board[7][0] << "   " << "\033[100;47;10m   \033[0m" << board[7][1] << "\033[100;47;10m   \033[0m" << "   " << board[7][2] << "   " << "\033[100;47;10m   \033[0m" << board[7][3] << "\033[100;47;10m   \033[0m" << "   " << board[7][4] << "   " << "\033[100;47;10m   \033[0m" << board[7][5] << "\033[100;47;10m   \033[0m" << "   " << board[7][6] << "   " << "\033[100;47;10m   \033[0m" << board[7][7] << "\033[100;47;10m   \033[0m" << "           8  " << "   " << board[7][8] << "   " << "\033[100;47;10m   \033[0m" << board[7][9] << "\033[100;47;10m   \033[0m" << "          8  " << "   " << board[7][10] << "   " << "\033[100;47;10m   \033[0m" << board[7][11] << "\033[100;47;10m   \033[0m" << std::endl;
	std::cout << "         " << "  " << whiteTile << "       " << whiteTile << "       " << whiteTile << "       " << whiteTile << "                     " << whiteTile << "             " << "       " << whiteTile << std::endl;
}

//displays new piece position
void col(int selecty, int selectx, int curry, int currx, int piece)
{
	if ((selectx % 2 == 0 && selecty % 2 == 0) || (selectx % 2 == 1 && selecty % 2 == 1))
	{
		board[selecty][selectx] = "\033[100;47;10m \033[0m";
	}
	else
	{
		board[selecty][selectx] = " ";
	}

	switch (piece)
	{
	//black pieces
	case PAWN:
		if ((currx % 2 == 0 && curry % 2 == 0) || (currx % 2 == 1 && curry % 2 == 1))
		{
			board[curry][currx] = blackPawnCol;
			break;
		}
		board[curry][currx] = "\033[10;1;30mP\033[0m";
		break;
	case ROOK:
		if ((currx % 2 == 0 && curry % 2 == 0) || (currx % 2 == 1 && curry % 2 == 1))
		{
			board[curry][currx] = blackRookCol;
			break;
		}
		board[curry][currx] = "\033[10;1;30mR\033[0m";
		break;
	case BISHOP:
		if ((currx % 2 == 0 && curry % 2 == 0) || (currx % 2 == 1 && curry % 2 == 1))
		{
			board[curry][currx] = blackBishopCol;
			break;
		}
		board[curry][currx] = "\033[10;1;30mB\033[0m";
		break;
	case HORSE:
		if ((currx % 2 == 0 && curry % 2 == 0) || (currx % 2 == 1 && curry % 2 == 1))
		{
			board[curry][currx] = blackHorseCol;
			break;
		}
		board[curry][currx] = "\033[10;1;30mH\033[0m";
		break;
	case QUEEN:
		if ((currx % 2 == 0 && curry % 2 == 0) || (currx % 2 == 1 && curry % 2 == 1))
		{
			board[curry][currx] = blackQueenCol;
			break;
		}
		board[curry][currx] = "\033[10;1;30mQ\033[0m";
		break;
	case KING:
		if ((currx % 2 == 0 && curry % 2 == 0) || (currx % 2 == 1 && curry % 2 == 1))
		{
			board[curry][currx] = blackKingCol;
			break;
		}
		board[curry][currx] = "\033[10;1;30mK\033[0m";
		break;

	//white pieces
	case PAWN + 6:
		if ((currx % 2 == 0 && curry % 2 == 0) || (currx % 2 == 1 && curry % 2 == 1))
		{
			board[curry][currx] = whitePawnCol;
			break;
		}
		board[curry][currx] = "\x1B[93mP\033[0m";
		break;
	case ROOK + 6:
		if ((currx % 2 == 0 && curry % 2 == 0) || (currx % 2 == 1 && curry % 2 == 1))
		{
			board[curry][currx] = whiteRookCol;
			break;
		}
		board[curry][currx] = "\x1B[93mR\033[0m";
		break;
	case BISHOP + 6:
		if ((currx % 2 == 0 && curry % 2 == 0) || (currx % 2 == 1 && curry % 2 == 1))
		{
			board[curry][currx] = whiteBishopCol;
			break;
		}
		board[curry][currx] = "\x1B[93mB\033[0m";
		break;
	case HORSE + 6:
		if ((currx % 2 == 0 && curry % 2 == 0) || (currx % 2 == 1 && curry % 2 == 1))
		{
			board[curry][currx] = whiteHorseCol;
			break;
		}
		board[curry][currx] = "\x1B[93mH\033[0m";
		break;
	case QUEEN + 6:
		if ((currx % 2 == 0 && curry % 2 == 0) || (currx % 2 == 1 && curry % 2 == 1))
		{
			board[curry][currx] = whiteQueenCol;
			break;
		}
		board[curry][currx] = "\x1B[93mQ\033[0m";
		break;
	case KING + 6:
		if ((currx % 2 == 0 && curry % 2 == 0) || (currx % 2 == 1 && curry % 2 == 1))
		{
			board[curry][currx] = whiteKingCol;
			break;
		}
		board[curry][currx] = "\x1B[93mK\033[0m";
		break;
	default:
		break;
	}
}

//checks if king is in check
void check()
{
	int pbtwn = 0;
	king.check = 0;

	//check if black is in check
	for (auto& w : wPiece)
	{
		if (w->death == 0)
		{
			//pawn
			if (w->piece == PAWN)
			{
				if (w->y + 1 == king.y)
				{
					if (w->x + 1 == king.x)
					{
						king.check = 1;
						return;
					}
					if (w->x - 1 == king.x)
					{
						king.check = 1;
						return;
					}
				}
			}

			//rook
			if (w->piece == ROOK)
			{
				//vertical movement
				if (king.x == w->x)
				{
					for (auto& b : bPiece)
					{
						if (b->x == w->x && b->piece != KING)
						{
							if (king.y < b->y && b->y < w->y)
							{
								pbtwn = 1;
								break;
							}

							if (king.y > b->y && b->y > w->y)
							{
								pbtwn = 1;
								break;
							}
						}
					}

					for (auto& w1 : wPiece)
					{
						if (w1->x == w->x)
						{
							if (king.y < w1->y && w1->y < w->y)
							{
								pbtwn = 1;
								break;
							}

							if (king.y > w1->y && w1->y > w->y)
							{
								pbtwn = 1;
								break;
							}
						}
					}

					if (pbtwn == 0)
					{
						king.check = 1;
						return;
					}
				}

				//horizontal movement
				if (king.y == w->y)
				{
					for (auto& b : bPiece)
					{
						if (b->y == w->y && b->piece != KING)
						{
							if (king.x < b->x && b->x < w->x)
							{
								pbtwn = 1;
								break;
							}

							if (king.x > b->x && b->x > w->x)
							{
								pbtwn = 1;
								break;
							}
						}
					}

					for (auto& w1 : wPiece)
					{
						if (w1->y == w->y)
						{
							if (king.x < w1->x && w1->x < w->x)
							{
								pbtwn = 1;
								break;
							}

							if (king.x > w1->x && w1->x > w->x)
							{
								pbtwn = 1;
								break;
							}
						}
					}

					if (pbtwn == 0)
					{
						king.check = 1;
						return;
					}
				}
			}

			//horse
			if (w->piece == HORSE)
			{
				if (king.x == w->x - 2 && king.y == w->y - 1)
				{
					king.check = 1;
				}

				if (king.x == w->x - 2 && king.y == w->y + 1)
				{
					king.check = 1;
				}

				if (king.x == w->x + 2 && king.y == w->y - 1)
				{
					king.check = 1;
				}

				if (king.x == w->x + 2 && king.y == w->y + 1)
				{
					king.check = 1;
				}

				if (king.x == w->x - 1 && king.y == w->y - 2)
				{
					king.check = 1;
				}

				if (king.x == w->x - 1 && king.y == w->y + 2)
				{
					king.check = 1;
				}

				if (king.x == w->x + 1 && king.y == w->y - 2)
				{
					king.check = 1;
				}

				if (king.x == w->x + 1 && king.y == w->y + 2)
				{
					king.check = 1;
				}
			}

			//bishop
			if (w->piece == BISHOP)
			{
				//right up diagonal
				if (king.x > w->x && king.y < w->y && (king.x - w->x == w->y - king.y))
				{
					king.check = 1;
					for (auto& b : bPiece)
					{
						if ((w->x < b->x && w->y > b->y) && (king.x > b->x && king.y < b->y))
						{
							if (king.x - b->x == b->y - king.y)
							{
								king.check = 0;
							}
						}
					}

					for (auto& w1 : wPiece)
					{
						if ((w->x < w1->x && w->y > w1->y) && (king.x > w1->x && king.y < w1->y))
						{
							if (king.x - w1->x == w1->y - king.y)
							{
								king.check = 0;
							}
						}
					}
					if (king.check == 1)
					{
						return;
					}
				}

				//right down diagonal
				if (king.x > w->x && king.y > w->y && (king.x - w->x == king.y - w->y))
				{
					king.check = 1;
					for (auto& b : bPiece)
					{
						if ((w->x < b->x && w->y < b->y) && (king.x > b->x && king.y > b->y))
						{
							if (king.x - b->x == king.y - b->y)
							{
								king.check = 0;
							}
						}
					}

					for (auto& w1 : wPiece)
					{
						if ((w->x < w1->x && w->y < w1->y) && (king.x > w1->x && king.y > w1->y))
						{
							if (king.x - w1->x == king.y - w1->y)
							{
								king.check = 0;
							}
						}
					}
					if (king.check == 1)
					{
						return;
					}
				}

				//left up diagonal
				if (king.x < w->x && king.y < w->y && (w->x - king.x == w->y - king.y))
				{
					king.check = 1;
					for (auto& b : bPiece)
					{
						if ((w->x > b->x && w->y > b->y) && (king.x < b->x && king.y < b->y))
						{
							if (b->x - king.x == b->y - king.y)
							{
								king.check = 0;
							}
						}
					}

					for (auto& w1 : wPiece)
					{
						if ((w->x > w1->x && w->y > w1->y) && (king.x < w1->x && king.y < w1->y))
						{
							if (w1->x - king.x == w1->y - king.y)
							{
								king.check = 0;
							}
						}
					}
					if (king.check == 1)
					{
						return;
					}
				}

				//left down diagonal
				if (king.x < w->x && king.y > w->y && (w->x - king.x == king.y - w->y))
				{
					king.check = 1;
					for (auto& b : bPiece)
					{
						if ((w->x > b->x && w->y < b->y) && (king.x < b->x && king.y > b->y))
						{
							if (b->x - king.x == king.y - b->y)
							{
								king.check = 0;
							}
						}
					}

					for (auto& w1 : wPiece)
					{
						if ((w->x > w1->x && w->y < w1->y) && (king.x < w1->x && king.y > w1->y))
						{
							if (w1->x - king.x == king.y - w1->y)
							{
								king.check = 0;
							}
						}
					}
					if (king.check == 1)
					{
						return;
					}
				}
			}

			//queen
			if (w->piece == QUEEN)
			{
				//vertical movement
				if (king.x == w->x)
				{
					for (auto& b : bPiece)
					{
						if (b->x == w->x && b->piece != KING)
						{
							if (king.y < b->y && b->y < w->y)
							{
								pbtwn = 1;
								break;
							}

							if (king.y > b->y && b->y > w->y)
							{
								pbtwn = 1;
								break;
							}
						}
					}

					for (auto& w1 : wPiece)
					{
						if (w1->x == w->x)
						{
							if (king.y < w1->y && w1->y < w->y)
							{
								pbtwn = 1;
								break;
							}

							if (king.y > w1->y && w1->y > w->y)
							{
								pbtwn = 1;
								break;
							}
						}
					}

					if (pbtwn == 0)
					{
						king.check = 1;
						return;
					}
				}

				//horizontal movement
				if (king.y == w->y)
				{
					for (auto& b : bPiece)
					{
						if (b->y == w->y && b->piece != KING)
						{
							if (king.x < b->x && b->x < w->x)
							{
								pbtwn = 1;
								break;
							}

							if (king.x > b->x && b->x > w->x)
							{
								pbtwn = 1;
								break;
							}
						}
					}

					for (auto& w1 : wPiece)
					{
						if (w1->y == w->y)
						{
							if (king.x < w1->x && w1->x < w->x)
							{
								pbtwn = 1;
								break;
							}

							if (king.x > w1->x && w1->x > w->x)
							{
								pbtwn = 1;
								break;
							}
						}
					}

					if (pbtwn == 0)
					{
						king.check = 1;
						return;
					}
				}

				//right up diagonal
				if (king.x > w->x && king.y < w->y && (king.x - w->x == w->y - king.y))
				{
					king.check = 1;
					for (auto& b : bPiece)
					{
						if ((w->x < b->x && w->y > b->y) && (king.x > b->x && king.y < b->y))
						{
							if (king.x - b->x == b->y - king.y)
							{
								king.check = 0;
							}
						}
					}

					for (auto& w1 : wPiece)
					{
						if ((w->x < w1->x && w->y > w1->y) && (king.x > w1->x && king.y < w1->y))
						{
							if (king.x - w1->x == w1->y - king.y)
							{
								king.check = 0;
							}
						}
					}
					if (king.check == 1)
					{
						return;
					}
				}

				//right down diagonal
				if (king.x > w->x && king.y > w->y && (king.x - w->x == king.y - w->y))
				{
					king.check = 1;
					for (auto& b : bPiece)
					{
						if ((w->x < b->x && w->y < b->y) && (king.x > b->x && king.y > b->y))
						{
							if (king.x - b->x == king.y - b->y)
							{
								king.check = 0;
							}
						}
					}

					for (auto& w1 : wPiece)
					{
						if ((w->x < w1->x && w->y < w1->y) && (king.x > w1->x && king.y > w1->y))
						{
							if (king.x - w1->x == king.y - w1->y)
							{
								king.check = 0;
							}
						}
					}
					if (king.check == 1)
					{
						return;
					}
				}

				//left up diagonal
				if (king.x < w->x && king.y < w->y && (w->x - king.x == w->y - king.y))
				{
					king.check = 1;
					for (auto& b : bPiece)
					{
						if ((w->x > b->x && w->y > b->y) && (king.x < b->x && king.y < b->y))
						{
							if (b->x - king.x == b->y - king.y)
							{
								king.check = 0;
							}
						}
					}

					for (auto& w1 : wPiece)
					{
						if ((w->x > w1->x && w->y > w1->y) && (king.x < w1->x && king.y < w1->y))
						{
							if (w1->x - king.x == w1->y - king.y)
							{
								king.check = 0;
							}
						}
					}
					if (king.check == 1)
					{
						return;
					}
				}

				//left down diagonal
				if (king.x < w->x && king.y > w->y && (w->x - king.x == king.y - w->y))
				{
					king.check = 1;
					for (auto& b : bPiece)
					{
						if ((w->x > b->x && w->y < b->y) && (king.x < b->x && king.y > b->y))
						{
							if (b->x - king.x == king.y - b->y)
							{
								king.check = 0;
							}
						}
					}

					for (auto& w1 : wPiece)
					{
						if ((w->x > w1->x && w->y < w1->y) && (king.x < w1->x && king.y > w1->y))
						{
							if (w1->x - king.x == king.y - w1->y)
							{
								king.check = 0;
							}
						}
					}
					if (king.check == 1)
					{
						return;
					}
				}
			}
		}
	}

	wking.check = 0;
	//check if white is in check
	for (auto& b : bPiece)
	{
		pbtwn = 0;
		if (b->death == 0)
		{
			//pawn
			if (b->piece == PAWN)
			{
				if (b->y - 1 == wking.y)
				{
					if (b->x + 1 == wking.x)
					{
						wking.check = 1;
						return;
					}
					if (b->x - 1 == wking.x)
					{
						wking.check = 1;
						return;
					}
				}
			}

			//rook
			if (b->piece == ROOK)
			{
				//vertical movement
				if (wking.x == b->x)
				{
					for (auto& w : wPiece)
					{
						if (w->x == b->x && w->piece != KING)
						{
							if (wking.y < w->y && w->y < b->y)
							{
								pbtwn = 1;
								break;
							}

							if (wking.y > w->y && w->y > b->y)
							{
								pbtwn = 1;
								break;
							}
						}
					}

					for (auto& b1 : bPiece)
					{
						if (b1->x == b->x && b1->piece != KING)
						{
							if (wking.y < b1->y && b1->y < b->y)
							{
								pbtwn = 1;
								break;
							}

							if (wking.y > b1->y && b1->y > b->y)
							{
								pbtwn = 1;
								break;
							}
						}
					}

					if (pbtwn == 0)
					{
						wking.check = 1;
						return;
					}
				}

				//horizontal movement
				if (wking.y == b->y)
				{
					for (auto& w : wPiece)
					{
						if (w->y == b->y && w->piece != KING)
						{
							if (wking.x < w->x && w->x < b->x)
							{
								pbtwn = 1;
								break;
							}

							if (wking.x > w->x && w->x > b->x)
							{
								pbtwn = 1;
								break;
							}
						}
					}

					for (auto& b1 : bPiece)
					{
						if (b1->y == b->y && b1->piece != KING)
						{
							if (wking.x < b1->x && b1->x < b->x)
							{
								pbtwn = 1;
								break;
							}

							if (wking.x > b1->x && b1->x > b->x)
							{
								pbtwn = 1;
								break;
							}
						}
					}

					if (pbtwn == 0)
					{
						wking.check = 1;
						return;
					}
				}
			}

			//horse
			if (b->piece == HORSE)
			{
				if (wking.x == b->x - 2 && wking.y == b->y - 1)
				{
					wking.check = 1;
				}

				if (wking.x == b->x - 2 && wking.y == b->y + 1)
				{
					wking.check = 1;
				}

				if (wking.x == b->x + 2 && wking.y == b->y - 1)
				{
					wking.check = 1;
				}

				if (wking.x == b->x + 2 && wking.y == b->y + 1)
				{
					wking.check = 1;
				}

				if (wking.x == b->x - 1 && wking.y == b->y - 2)
				{
					wking.check = 1;
				}

				if (wking.x == b->x - 1 && wking.y == b->y + 2)
				{
					wking.check = 1;
				}

				if (wking.x == b->x + 1 && wking.y == b->y - 2)
				{
					wking.check = 1;
				}

				if (wking.x == b->x + 1 && wking.y == b->y + 2)
				{
					wking.check = 1;
				}
				if (wking.check == 1)
				{
					return;
				}
			}

			//bishop
			if (b->piece == BISHOP)
			{
				//right up diagonal
				if (wking.x > b->x && wking.y < b->y && (wking.x - b->x == b->y - wking.y))
				{
					wking.check = 1;
					for (auto& b1 : bPiece)
					{
						if ((b->x < b1->x && b->y > b1->y) && (wking.x > b1->x && wking.y < b1->y))
						{
							if (wking.x - b1->x == b1->y - wking.y)
							{
								wking.check = 0;
							}
						}
					}

					for (auto& w : wPiece)
					{
						if ((b->x < w->x && b->y > w->y) && (wking.x > w->x && wking.y < w->y))
						{
							if (wking.x - w->x == w->y - wking.y)
							{
								wking.check = 0;
							}
						}
					}
					if (wking.check == 1)
					{
						return;
					}
				}

				//right down diagonal
				if (wking.x > b->x && wking.y > b->y && (wking.x - b->x == wking.y - b->y))
				{
					wking.check = 1;
					for (auto& b1 : bPiece)
					{
						if ((b->x < b1->x && b->y < b1->y) && (wking.x > b1->x && wking.y > b1->y))
						{
							if (wking.x - b1->x == wking.y - b1->y)
							{
								wking.check = 0;
							}
						}
					}

					for (auto& w : wPiece)
					{
						if ((b->x < w->x && b->y < w->y) && (wking.x > w->x && wking.y > w->y))
						{
							if (wking.x - w->x == wking.y - w->y)
							{
								wking.check = 0;
							}
						}
					}
					if (wking.check == 1)
					{
						return;
					}
				}

				//left up diagonal
				if (wking.x < b->x && wking.y < b->y && (b->x - wking.x == b->y - wking.y))
				{
					wking.check = 1;
					for (auto& b1 : bPiece)
					{
						if ((b->x > b1->x && b->y > b1->y) && (wking.x < b1->x && wking.y < b1->y))
						{
							if (b1->x - wking.x == b1->y - wking.y)
							{
								wking.check = 0;
							}
						}
					}

					for (auto& w : wPiece)
					{
						if ((b->x > w->x && b->y > w->y) && (wking.x < w->x && wking.y < w->y))
						{
							if (w->x - wking.x == w->y - wking.y)
							{
								wking.check = 0;
							}
						}
					}
					if (wking.check == 1)
					{
						return;
					}
				}

				//left down diagonal
				if (wking.x < b->x && wking.y > b->y && (b->x - wking.x == wking.y - b->y))
				{
					wking.check = 1;
					for (auto& b1 : bPiece)
					{
						if ((b->x > b1->x && b->y < b1->y) && (wking.x < b1->x && wking.y > b1->y))
						{
							if (b1->x - wking.x == wking.y - b1->y)
							{
								wking.check = 0;
							}
						}
					}

					for (auto& w : wPiece)
					{
						if ((b->x > w->x && b->y < w->y) && (wking.x < w->x && wking.y > w->y))
						{
							if (w->x - wking.x == wking.y - w->y)
							{
								wking.check = 0;
							}
						}
					}
					if (wking.check == 1)
					{
						return;
					}
				}
			}

			//queen
			if (b->piece == QUEEN)
			{
				//vertical movement
				if (wking.x == b->x)
				{
					for (auto& w : wPiece)
					{
						if (w->x == b->x && w->piece != KING)
						{
							if (wking.y < w->y && w->y < b->y)
							{
								pbtwn = 1;
								break;
							}

							if (wking.y > w->y && w->y > b->y)
							{
								pbtwn = 1;
								break;
							}
						}
					}

					for (auto& b1 : bPiece)
					{
						if (b1->x == b->x && b1->piece != KING)
						{
							if (wking.y < b1->y && b1->y < b->y)
							{
								pbtwn = 1;
								break;
							}

							if (wking.y > b1->y && b1->y > b->y)
							{
								pbtwn = 1;
								break;
							}
						}
					}

					if (pbtwn == 0)
					{
						wking.check = 1;
						return;
					}
				}

				//horizontal movement
				if (wking.y == b->y)
				{
					for (auto& w : wPiece)
					{
						if (w->y == b->y && w->piece != KING)
						{
							if (wking.x < w->x && w->x < b->x)
							{
								pbtwn = 1;
								break;
							}

							if (wking.x > w->x && w->x > b->x)
							{
								pbtwn = 1;
								break;
							}
						}
					}

					for (auto& b1 : bPiece)
					{
						if (b1->y == b->y && b1->piece != KING)
						{
							if (wking.x < b1->x && b1->x < b->x)
							{
								pbtwn = 1;
								break;
							}

							if (wking.x > b1->x && b1->x > b->x)
							{
								pbtwn = 1;
								break;
							}
						}
					}

					if (pbtwn == 0)
					{
						wking.check = 1;
						return;
					}
				}

				//right up diagonal
				if (wking.x > b->x && wking.y < b->y && (wking.x - b->x == b->y - wking.y))
				{
					wking.check = 1;
					for (auto& b1 : bPiece)
					{
						if ((b->x < b1->x && b->y > b1->y) && (wking.x > b1->x && wking.y < b1->y))
						{
							if (wking.x - b1->x == b1->y - wking.y)
							{
								wking.check = 0;
							}
						}
					}

					for (auto& w : wPiece)
					{
						if ((b->x < w->x && b->y > w->y) && (wking.x > w->x && wking.y < w->y))
						{
							if (wking.x - w->x == w->y - wking.y)
							{
								wking.check = 0;
							}
						}
					}
					if (wking.check == 1)
					{
						return;
					}
				}

				//right down diagonal
				if (wking.x > b->x && wking.y > b->y && (wking.x - b->x == wking.y - b->y))
				{
					wking.check = 1;
					for (auto& b1 : bPiece)
					{
						if ((b->x < b1->x && b->y < b1->y) && (wking.x > b1->x && wking.y > b1->y))
						{
							if (wking.x - b1->x == wking.y - b1->y)
							{
								wking.check = 0;
							}
						}
					}

					for (auto& w : wPiece)
					{
						if ((b->x < w->x && b->y < w->y) && (wking.x > w->x && wking.y > w->y))
						{
							if (wking.x - w->x == wking.y - w->y)
							{
								wking.check = 0;
							}
						}
					}
					if (wking.check == 1)
					{
						return;
					}
				}

				//left up diagonal
				if (wking.x < b->x && wking.y < b->y && (b->x - wking.x == b->y - wking.y))
				{
					wking.check = 1;
					for (auto& b1 : bPiece)
					{
						if ((b->x > b1->x && b->y > b1->y) && (wking.x < b1->x && wking.y < b1->y))
						{
							if (b1->x - wking.x == b1->y - wking.y)
							{
								wking.check = 0;
							}
						}
					}

					for (auto& w : wPiece)
					{
						if ((b->x > w->x && b->y > w->y) && (wking.x < w->x && wking.y < w->y))
						{
							if (w->x - wking.x == w->y - wking.y)
							{
								wking.check = 0;
							}
						}
					}
					if (wking.check == 1)
					{
						return;
					}
				}

				//left down diagonal
				if (wking.x < b->x && wking.y > b->y && (b->x - wking.x == wking.y - b->y))
				{
					wking.check = 1;
					for (auto& b1 : bPiece)
					{
						if ((b->x > b1->x && b->y < b1->y) && (wking.x < b1->x && wking.y > b1->y))
						{
							if (b1->x - wking.x == wking.y - b1->y)
							{
								wking.check = 0;
							}
						}
					}

					for (auto& w : wPiece)
					{
						if ((b->x > w->x && b->y < w->y) && (wking.x < w->x && wking.y > w->y))
						{
							if (w->x - wking.x == wking.y - w->y)
							{
								wking.check = 0;
							}
						}
					}
					if (wking.check == 1)
					{
						return;
					}
				}
			}
		}
	}
}

int locAlg(int wx, int wy, int chngx, int chngy)
{
	wx += chngx;
	wy += chngy;
	if (wx > 7 || wx < 0 || wy > 7 || wy < 0)
	{
		return 0;
	}
	for (auto& w : wPiece)
	{
		if (w->x == wx && w->y == wy)
		{
			return 1;
		}
	}
	for (auto& b : bPiece)
	{
		if (wx == b->x && wy == b->y)
		{
			return 2;
		}
	}
	return 3;
}

//checks if color is in check
void checkmate()
{
	int valid = 1;
	int bxtemp = 0;
	int wxtemp = 0;
	int bytemp = 0;
	int wytemp = 0;
	int px = 0;
	int py = 0;
	int t = 0;

	//if white is in check
	if (wking.check == 1)
	{
		for (auto& w : wPiece)
		{
			if (w->death == 0)
			{
				valid = 1;
				bxtemp = -1;
				wxtemp = -1;
				bytemp = -1;
				wytemp = -1;
				px = 0;
				py = 0;

				//pawn
				if (w->piece == PAWN)
				{
					//piece in front
					for (auto& w1 : wPiece)
					{
						if (w->x == w1->x && w1->y == w->y + 1)
						{
							valid = 0;
							break;
						}
					}
					for (auto& b : bPiece)
					{
						if (w->x == b->x && b->y == w->y + 1)
						{
							valid = 0;
							break;
						}
					}

					if (valid == 1)
					{
						w->y += 1;
						check();
						w->y -= 1;
						if (wking.check == 0)
						{
							wking.check = 1;
							return;
						}
					}

					if (w->movesMade == 0)
					{
						for (auto& w1 : wPiece)
						{
							if (w->y + 2 == w1->y && w->x == w1->x)
							{
								valid = 0;
								break;
							}
						}
						for (auto& b : bPiece)
						{
							if (w->y + 2 == b->y && w->x == b->x)
							{
								valid = 0;
								break;
							}
						}
					}
					else
					{
						valid = 0;
					}

					if (valid == 1)
					{
						w->y += 2;
						check();
						w->y -= 2;
						if (wking.check == 0)
						{
							wking.check = 1;
							return;
						}
					}

					//killing piece
					for (auto& b : bPiece)
					{
						if (b->piece != KING)
						{
							if (b->x == w->x + 1 && b->y == w->y + 1)
							{
								bDead++;
								px = b->x;
								py = b->y;
								b->death = 1;
								b->dead(bDead);

								w->x += 1;
								w->y += 1;
								check();
								w->x -= 1;
								w->y -= 1;

								col(b->y, b->x, py, px, b->piece);
								bDead--;
								b->x = px;
								b->y = py;
								b->death = 0;

								if (wking.check == 0)
								{
									wking.check = 1;
									return;
								}
							}
							if (b->x == w->x - 1 && b->y == w->y + 1)
							{
								bDead++;
								px = b->x;
								py = b->y;
								b->death = 1;
								b->dead(bDead);

								w->x -= 1;
								w->y += 1;
								check();
								w->x += 1;
								w->y -= 1;

								col(b->y, b->x, py, px, b->piece);
								bDead--;
								b->x = px;
								b->y = py;
								b->death = 0;

								if (wking.check == 0)
								{
									wking.check = 1;
									return;
								}
							}
						}

						if (b->enPassantCnt == 1)
						{
							if (b->x == w->x + 1 && b->y == w->y)
							{
								bDead++;
								px = b->x;
								py = b->y;
								b->death = 1;
								b->dead(bDead);

								w->x += 1;
								w->y += 1;
								check();
								w->x -= 1;
								w->y -= 1;

								col(b->y, b->x, py, px, b->piece);
								bDead--;
								b->x = px;
								b->y = py;
								b->death = 0;

								if (wking.check == 0)
								{
									wking.check = 1;
									return;
								}
							}
							if (b->x == w->x - 1 && b->y == w->y)
							{
								bDead++;
								px = b->x;
								py = b->y;
								b->death = 1;
								b->dead(bDead);

								w->x -= 1;
								w->y += 1;
								check();
								w->x += 1;
								w->y -= 1;
								
								col(b->y, b->x, py, px, b->piece);
								bDead--;
								b->x = px;
								b->y = py;
								b->death = 0;

								if (wking.check == 0)
								{
									wking.check = 1;
									return;
								}
							}
						}
					}
				}
				//rook
				if (w->piece == ROOK)
				{
					//horizontal left movement
					for (auto& b : bPiece)
					{
						if (b->x < w->x && b->y == w->y && b->x > bxtemp)
						{
							//for multiple pieces in the same row select one and store its x value then compare 
							//its x location to other black pieces and see which one is closest to the rook being 
							//checked and say that bxtemp is that x value
							bxtemp = b->x;
						}
					}
					for (auto& w1 : wPiece)
					{
						if (w1->x < w->x && w1->y == w->y && w1->x > bxtemp && w1->x > wxtemp && w1->piece != KING)
						{
							wxtemp = w1->x;
						}
					}

					int t = 0;
					while (t <= 7)
					{
						t++;
						w->x -= t;
						if (w->x == wxtemp)
						{
							w->x += t;
							break;
						}
						if (w->x == bxtemp)
						{
							for (auto& b : bPiece)
							{
								if (b->x == bxtemp && b->y == w->y)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);
									check();
									w->x += t;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										wking.check = 1;
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						w->x += t;
						if (wking.check == 0)
						{
							wking.check = 1;
							return;
						}
					}

					wxtemp = 8;
					bxtemp = 8;

					//horizontal right movement
					for (auto& b : bPiece)
					{
						if (b->x > w->x && b->y == w->y && b->x < bxtemp)
						{
							bxtemp = b->x;
						}
					}
					for (auto& w1 : wPiece)
					{
						if (w1->x > w->x && w1->y == w->y && w1->x < bxtemp && w1->x < wxtemp && w1->piece != KING)
						{
							wxtemp = w1->x;
						}
					}

					t = 0;
					while (t <= 7)
					{
						t++;
						w->x += t;
						if (w->x == wxtemp)
						{
							w->x -= t;
							break;
						}
						if (w->x == bxtemp)
						{
							for (auto& b : bPiece)
							{
								if (b->x == bxtemp && b->y == w->y)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);

									check();
									w->x -= t;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										wking.check = 1;
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						w->x -= t;

						if (wking.check == 0)
						{
							wking.check = 1;
							return;
						}
					}

					//vertical up movement
					for (auto& b : bPiece)
					{
						if (b->y < w->y && b->x == w->x && b->y > bytemp)
						{
							bytemp = b->y;
						}
					}
					for (auto& w1 : wPiece)
					{
						if (w1->y < w->y && w1->x == w->x && w1->y > bytemp && w1->y > wytemp && w1->piece != KING)
						{
							wytemp = w1->y;
						}
					}

					t = 0;
					while (t <= 7)
					{
						t++;
						w->y -= t;
						if (w->y == wytemp)
						{
							w->y += t;
							break;
						}
						if (w->y == bytemp)
						{
							for (auto& b : bPiece)
							{
								if (b->y == bytemp && b->x == w->x)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);

									check();
									w->y += t;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										wking.check = 1;
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						w->y += t;
						if (wking.check == 0)
						{
							wking.check = 1;
							return;
						}
					}

					bytemp = 8;
					wytemp = 8;

					//vertical down movement
					for (auto& b : bPiece)
					{
						if (b->y > w->y && b->x == w->x && b->y < bytemp)
						{
							bytemp = b->y;
						}
					}
					for (auto& w1 : wPiece)
					{
						if (w1->y > w->y && w1->x == w->x && w1->y < bytemp && w1->y < wytemp && w1->piece != KING)
						{
							wytemp = w1->y;
						}
					}

					t = 0;
					while (t <= 7)
					{
						t++;
						w->y += t;
						if (w->y == wytemp)
						{
							w->y -= t;
							break;
						}
						if (w->y == bytemp)
						{
							for (auto& b : bPiece)
							{
								if (b->y == bytemp && b->x == w->x)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);

									check();
									w->y -= t;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										wking.check = 1;
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						w->y -= t;
						if (wking.check == 0)
						{
							wking.check = 1;
							return;
						}
					}
				}
				//horse
				if (w->piece == HORSE)
				{
					switch (locAlg(w->x, w->y, -2, -1))
					{
					case 0:
						break;
					case 1:
						break;
					case 2:
						w->x -= 2;
						w->y -= 1;
						//run death sequence
						for (auto& b : bPiece)
						{
							if (b->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);

									check();
									w->x += 2;
									w->y += 1;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										wking.check = 1;
										return;
									}
								}
							}
						}
						break;
					case 3:
						w->x -= 2;
						w->y -= 1;
						check();
						w->x += 2;
						w->y += 1;
					
						if (wking.check == 0)
						{
							wking.check = 1;
							return;
						}
						break;
					}
					
					switch (locAlg(w->x, w->y, -2, 1))
					{
					case 0:
						break;
					case 1:
						break;
					case 2:
						w->x -= 2;
						w->y += 1;
						//run death sequence
						for (auto& b : bPiece)
						{
							if (b->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);

									check();
									w->x += 2;
									w->y -= 1;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										wking.check = 1;
										return;
									}
								}
							}
						}
						break;
					case 3:
						w->x -= 2;
						w->y += 1;
						check();
						w->x += 2;
						w->y -= 1;

						if (wking.check == 0)
						{
							wking.check = 1;
							return;
						}
						break;
					}
					
					switch (locAlg(w->x, w->y, 2, -1))
					{
					case 0:
						break;
					case 1:
						break;
					case 2:
						w->x += 2;
						w->y -= 1;
						//run death sequence
						for (auto& b : bPiece)
						{
							if (b->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);

									check();
									w->x -= 2;
									w->y += 1;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										wking.check = 1;
										return;
									}
								}
							}
						}
						break;
					case 3:
						w->x += 2;
						w->y -= 1;
						check();
						w->x -= 2;
						w->y += 1;

						if (wking.check == 0)
						{
							wking.check = 1;
							return;
						}
						break;
					}
					
					switch (locAlg(w->x, w->y, 2, 1))
					{
					case 0:
						break;
					case 1:
						break;
					case 2:
						w->x += 2;
						w->y += 1;
						//run death sequence
						for (auto& b : bPiece)
						{
							if (b->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);

									check();
									w->x -= 2;
									w->y -= 1;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										wking.check = 1;
										return;
									}
								}
							}
						}
						break;
					case 3:
						w->x += 2;
						w->y += 1;
						check();
						w->x -= 2;
						w->y -= 1;

						if (wking.check == 0)
						{
							wking.check = 1;
							return;
						}
						break;
					}

					switch (locAlg(w->x, w->y, -1, -2))
					{
					case 0:
						break;
					case 1:
						break;
					case 2:
						w->x -= 1;
						w->y -= 2;
						//run death sequence
						for (auto& b : bPiece)
						{
							if (b->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);

									check();
									w->x += 1;
									w->y += 2;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										wking.check = 1;
										return;
									}
								}
							}
						}
						break;
					case 3:
						w->x -= 1;
						w->y -= 2;
						check();
						w->x += 1;
						w->y += 2;

						if (wking.check == 0)
						{
							wking.check = 1;
							return;
						}
						break;
					}

					switch (locAlg(w->x, w->y, -1, 2))
					{
					case 0:
						break;
					case 1:
						break;
					case 2:
						w->x -= 1;
						w->y += 2;
						//run death sequence
						for (auto& b : bPiece)
						{
							if (b->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);

									check();
									w->x += 1;
									w->y -= 2;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										wking.check = 1;
										return;
									}
								}
							}
						}
						break;
					case 3:
						w->x -= 1;
						w->y += 2;
						check();
						w->x += 1;
						w->y -= 2;

						if (wking.check == 0)
						{
							wking.check = 1;
							return;
						}
						break;
					}
					
					switch (locAlg(w->x, w->y, 1, -2))
					{
					case 0:
						break;
					case 1:
						break;
					case 2:
						w->x += 1;
						w->y -= 2;
						//run death sequence
						for (auto& b : bPiece)
						{
							if (b->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);

									check();
									w->x -= 1;
									w->y += 2;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										wking.check = 1;
										return;
									}
								}
							}
						}
						break;
					case 3:
						w->x += 1;
						w->y -= 2;
						check();
						w->x += 1;
						w->y -= 2;

						if (wking.check == 0)
						{
							wking.check = 1;
							return;
						}
						break;
					}
					
					switch (locAlg(w->x, w->y, 1, 2))
					{
					case 0:
						break;
					case 1:
						break;
					case 2:
						w->x += 1;
						w->y += 2;
						//run death sequence
						for (auto& b : bPiece)
						{
							if (b->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);

									check();
									w->x -= 1;
									w->y -= 2;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										wking.check = 1;
										return;
									}
								}
							}
						}
						break;
					case 3:
						w->x += 1;
						w->y += 2;
						check();
						w->x -= 1;
						w->y -= 2;

						if (wking.check == 0)
						{
							wking.check = 1;
							return;
						}
						break;
					}
				}
				//bishop
				if (w->piece == BISHOP)
				{
					//left down diagonal
					wytemp = 8;
					bytemp = 8;
					t = 0;

					for (auto& b : bPiece)
					{
						if (b->x < w->x && b->y > w->y && w->x - b->x == b->y - w->y && b->x > bxtemp && b->y < bytemp)
						{
							bxtemp = b->x;
							bytemp = b->y;
						}
					}

					for (auto& w1 : wPiece)
					{
						if (w1->x < w->x && w1->y > w->y && w->x - w1->x == w1->y - w->y && w1->x > bxtemp && w1->y < bytemp && w1->x > wxtemp && w1->y < wytemp)
						{
							wxtemp = w1->x;
							wytemp = w1->y;
						}
					}

					while (t <= 7)
					{
						t++;
						w->x -= t;
						w->y += t;
						
						if (w->x == wxtemp || w->y == wytemp)
						{
							w->x += t;
							w->y -= t;
							break;
						}

						if (w->x == bxtemp || w->y == bytemp)
						{
							for (auto& b : bPiece)
							{
								if (b->x == bxtemp && b->y == bytemp)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);
									check();
									w->x += t;
									w->y -= t;

									col(b->y, b->x, py, px, b->piece);

									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										wking.check = 1;
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						w->x += t;
						w->y -= t;

						if (wking.check == 0)
						{
							wking.check = 1;
							return;
						}
					}

					//right down diagonal
					bxtemp = 8;
					bytemp = 8;
					wxtemp = 8;
					wytemp = 8;
					t = 0;

					for (auto& b : bPiece)
					{
						if (b->x > w->x && b->y > w->y && b->x - w->x == b->y - w->y && b->x < bxtemp && b->y < bytemp)
						{
							bxtemp = b->x;
							bytemp = b->y;
						}
					}

					for (auto& w1 : wPiece)
					{
						if (w1->x > w->x && w1->y > w->y && w1->x - w->x == w1->y - w->y && w1->x < bxtemp && w1->y < bytemp && w1->x < wxtemp && w1->y < wytemp)
						{
							wxtemp = w1->x;
							wytemp = w1->y;
						}
					}

					while (t <= 7)
					{
						t++;
						w->x += t;
						w->y += t;

						if (w->x == wxtemp || w->y == wytemp)
						{
							w->x -= t;
							w->y -= t;
							break;
						}

						if (w->x == bxtemp || w->y == bytemp)
						{
							for (auto& b : bPiece)
							{
								if (b->x == bxtemp && b->y == bytemp)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);
									check();
									w->x -= t;
									w->y -= t;

									col(b->y, b->x, py, px, b->piece);

									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										wking.check = 1;
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						w->x -= t;
						w->y -= t;
						if (wking.check == 0)
						{
							wking.check = 1;
							return;
						}
					}

					//left up diagonal
					bxtemp = -1;
					bytemp = -1;
					wxtemp = -1;
					wytemp = -1;
					t = 0;

					for (auto& b : bPiece)
					{
						if (b->x < w->x && b->y < w->y && w->x - b->x == w->y - b->y && b->x > bxtemp && b->y > bytemp)
						{
							bxtemp = b->x;
							bytemp = b->y;
						}
					}

					for (auto& w1 : wPiece)
					{
						if (w1->x < w->x && w1->y < w->y && w->x - w1->x == w->y - w1->y && w1->x > bxtemp && w1->y > bytemp && w1->x > wxtemp && w1->y > wytemp)
						{
							wxtemp = w1->x;
							wytemp = w1->y;
						}
					}

					while (t <= 7)
					{
						t++;
						w->x -= t;
						w->y -= t;

						if (w->x == wxtemp || w->y == wytemp)
						{
							w->x += t;
							w->y += t;
							break;
						}

						if (w->x == bxtemp || w->y == bytemp)
						{
							for (auto& b : bPiece)
							{
								if (b->x == bxtemp && b->y == bytemp)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);
									check();
									w->x += t;
									w->y += t;

									col(b->y, b->x, py, px, b->piece);

									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										wking.check = 1;
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						w->x += t;
						w->y += t;
						if (wking.check == 0)
						{
							wking.check = 1;
							return;
						}
					}

					//right up diagonal
					bxtemp = 8;
					bytemp = -1;
					wxtemp = 8;
					wytemp = -1;
					t = 0;

					for (auto& b : bPiece)
					{
						if (b->x > w->x && b->y < w->y && b->x - w->x == w->y - b->y && b->x < bxtemp && b->y > bytemp)
						{
							bxtemp = b->x;
							bytemp = b->y; 
						}
					}
					
					for (auto& w1 : wPiece)
					{
						if (w1->x > w->x && w1->y < w->y && w1->x - w->x == w->y - w1->y && w1->x < bxtemp && w1->y > bytemp && w1->x < wxtemp && w1->y > wytemp)
						{
							wxtemp = w1->x;
							wytemp = w1->y;
						}
					}

					while (t <= 7)
					{
						t++;
						w->x += t;
						w->y -= t;

						if (w->x == wxtemp || w->y == wytemp)
						{
							w->x -= t;
							w->y += t;
							break;
						}

						if (w->x == bxtemp || w->y == bytemp)
						{
							for (auto& b : bPiece)
							{
								if (b->x == bxtemp && b->y == bytemp)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);
									check();
									w->x -= t;
									w->y += t;

									col(b->y, b->x, py, px, b->piece);

									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										wking.check = 1;
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						w->x -= t;
						w->y += t;
						if (wking.check == 0)
						{
							wking.check = 1;
							return;
						}
					}
				}
				//queen
				if (w->piece == QUEEN)
				{
					//horizontal left movement
					for (auto& b : bPiece)
					{
						if (b->x < w->x && b->y == w->y && b->x > bxtemp)
						{
							bxtemp = b->x;
						}
					}
					for (auto& w1 : wPiece)
					{
						if (w1->x < w->x && w1->y == w->y && w1->x > bxtemp && w1->x > wxtemp && w1->piece != KING)
						{
							wxtemp = w1->x;
						}
					}

					int t = 0;
					while (t <= 7)
					{
						t++;
						w->x -= t;
						if (w->x == wxtemp)
						{
							w->x += t;
							break;
						}
						if (w->x == bxtemp)
						{
							for (auto& b : bPiece)
							{
								if (b->x == bxtemp && b->y == w->y)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);
									check();
									w->x += t;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										wking.check = 1;
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						w->x += t;
						if (wking.check == 0)
						{
							wking.check = 1;
							return;
						}
					}

					wxtemp = 8;
					bxtemp = 8;

					//horizontal right movement
					for (auto& b : bPiece)
					{
						if (b->x > w->x && b->y == w->y && b->x < bxtemp)
						{
							bxtemp = b->x;
						}
					}
					for (auto& w1 : wPiece)
					{
						if (w1->x > w->x && w1->y == w->y && w1->x < bxtemp && w1->x < wxtemp && w1->piece != KING)
						{
							wxtemp = w1->x;
						}
					}

					t = 0;
					while (t <= 7)
					{
						t++;
						w->x += t;
						if (w->x == wxtemp)
						{
							w->x -= t;
							break;
						}
						if (w->x == bxtemp)
						{
							for (auto& b : bPiece)
							{
								if (b->x == bxtemp && b->y == w->y)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);

									check();
									w->x -= t;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										wking.check = 1;
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						w->x -= t;

						if (wking.check == 0)
						{
							wking.check = 1;
							return;
						}
					}

					//vertical up movement
					for (auto& b : bPiece)
					{
						if (b->y < w->y && b->x == w->x && b->y > bytemp)
						{
							bytemp = b->y;
						}
					}
					for (auto& w1 : wPiece)
					{
						if (w1->y < w->y && w1->x == w->x && w1->y > bytemp && w1->y > wytemp && w1->piece != KING)
						{
							wytemp = w1->y;
						}
					}

					t = 0;
					while (t <= 7)
					{
						t++;
						w->y -= t;
						if (w->y == wytemp)
						{
							w->y += t;
							break;
						}
						if (w->y == bytemp)
						{
							for (auto& b : bPiece)
							{
								if (b->y == bytemp && b->x == w->x)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);

									check();
									w->y += t;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										wking.check = 1;
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						w->y += t;
						if (wking.check == 0)
						{
							wking.check = 1;
							return;
						}
					}

					bytemp = 8;
					wytemp = 8;

					//vertical down movement
					for (auto& b : bPiece)
					{
						if (b->y > w->y && b->x == w->x && b->y < bytemp)
						{
							bytemp = b->y;
						}
					}
					for (auto& w1 : wPiece)
					{
						if (w1->y > w->y && w1->x == w->x && w1->y < bytemp && w1->y < wytemp && w1->piece != KING)
						{
							wytemp = w1->y;
						}
					}

					t = 0;
					while (t <= 7)
					{
						t++;
						w->y += t;
						if (w->y == wytemp)
						{
							w->y -= t;
							break;
						}
						if (w->y == bytemp)
						{
							for (auto& b : bPiece)
							{
								if (b->y == bytemp && b->x == w->x)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);

									check();
									w->y -= t;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										wking.check = 1;
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						w->y -= t;
						if (wking.check == 0)
						{
							wking.check = 1;
							return;
						}
					}


					//left down diagonal
					bxtemp = -1;
					bytemp = 8;
					wxtemp = -1;
					wytemp = 8;
					
					t = 0;

					for (auto& b : bPiece)
					{
						if (b->x < w->x && b->y > w->y && w->x - b->x == b->y - w->y && b->x > bxtemp && b->y < bytemp)
						{
							bxtemp = b->x;
							bytemp = b->y;
						}
					}

					for (auto& w1 : wPiece)
					{
						if (w1->x < w->x && w1->y > w->y && w->x - w1->x == w1->y - w->y && w1->x > bxtemp && w1->y < bytemp && w1->x > wxtemp && w1->y < wytemp)
						{
							wxtemp = w1->x;
							wytemp = w1->y;
						}
					}

					while (t <= 7)
					{
						t++;
						w->x -= t;
						w->y += t;

						if (w->x == wxtemp || w->y == wytemp)
						{
							w->x += t;
							w->y -= t;
							break;
						}

						if (w->x == bxtemp || w->y == bytemp)
						{
							for (auto& b : bPiece)
							{
								if (b->x == bxtemp && b->y == bytemp)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);
									check();
									w->x += t;
									w->y -= t;

									col(b->y, b->x, py, px, b->piece);

									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										wking.check = 1;
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						w->x += t;
						w->y -= t;

						if (wking.check == 0)
						{
							wking.check = 1;
							return;
						}
					}

					//right down diagonal
					bxtemp = 8;
					bytemp = 8;
					wxtemp = 8;
					wytemp = 8;
					t = 0;

					for (auto& b : bPiece)
					{
						if (b->x > w->x && b->y > w->y && b->x - w->x == b->y - w->y && b->x < bxtemp && b->y < bytemp)
						{
							bxtemp = b->x;
							bytemp = b->y;
						}
					}

					for (auto& w1 : wPiece)
					{
						if (w1->x > w->x && w1->y > w->y && w1->x - w->x == w1->y - w->y && w1->x < bxtemp && w1->y < bytemp && w1->x < wxtemp && w1->y < wytemp)
						{
							wxtemp = w1->x;
							wytemp = w1->y;
						}
					}

					while (t <= 7)
					{
						t++;
						w->x += t;
						w->y += t;

						if (w->x == wxtemp || w->y == wytemp)
						{
							w->x -= t;
							w->y -= t;
							break;
						}

						if (w->x == bxtemp || w->y == bytemp)
						{
							for (auto& b : bPiece)
							{
								if (b->x == bxtemp && b->y == bytemp)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);
									check();
									w->x -= t;
									w->y -= t;

									col(b->y, b->x, py, px, b->piece);

									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										wking.check = 1;
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						w->x -= t;
						w->y -= t;
						if (wking.check == 0)
						{
							wking.check = 1;
							return;
						}
					}

					//left up diagonal
					bxtemp = -1;
					bytemp = -1;
					wxtemp = -1;
					wytemp = -1;
					t = 0;

					for (auto& b : bPiece)
					{
						if (b->x < w->x && b->y < w->y && w->x - b->x == w->y - b->y && b->x > bxtemp && b->y > bytemp)
						{
							bxtemp = b->x;
							bytemp = b->y;
						}
					}

					for (auto& w1 : wPiece)
					{
						if (w1->x < w->x && w1->y < w->y && w->x - w1->x == w->y - w1->y && w1->x > bxtemp && w1->y > bytemp && w1->x > wxtemp && w1->y > wytemp)
						{
							wxtemp = w1->x;
							wytemp = w1->y;
						}
					}

					while (t <= 7)
					{
						t++;
						w->x -= t;
						w->y -= t;

						if (w->x == wxtemp || w->y == wytemp)
						{
							w->x += t;
							w->y += t;
							break;
						}

						if (w->x == bxtemp || w->y == bytemp)
						{
							for (auto& b : bPiece)
							{
								if (b->x == bxtemp && b->y == bytemp)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);
									check();
									w->x += t;
									w->y += t;

									col(b->y, b->x, py, px, b->piece);

									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										wking.check = 1;
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						w->x += t;
						w->y += t;
						if (wking.check == 0)
						{
							wking.check = 1;
							return;
						}
					}

					//right up diagonal
					bxtemp = 8;
					bytemp = -1;
					wxtemp = 8;
					wytemp = -1;
					t = 0;

					for (auto& b : bPiece)
					{
						if (b->x > w->x && b->y < w->y && b->x - w->x == w->y - b->y && b->x < bxtemp && b->y > bytemp)
						{
							bxtemp = b->x;
							bytemp = b->y;
						}
					}

					for (auto& w1 : wPiece)
					{
						if (w1->x > w->x && w1->y < w->y && w1->x - w->x == w->y - w1->y && w1->x < bxtemp && w1->y > bytemp && w1->x < wxtemp && w1->y > wytemp)
						{
							wxtemp = w1->x;
							wytemp = w1->y;
						}
					}

					while (t <= 7)
					{
						t++;
						w->x += t;
						w->y -= t;

						if (w->x == wxtemp || w->y == wytemp)
						{
							w->x -= t;
							w->y += t;
							break;
						}

						if (w->x == bxtemp || w->y == bytemp)
						{
							for (auto& b : bPiece)
							{
								if (b->x == bxtemp && b->y == bytemp)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);
									check();
									w->x -= t;
									w->y += t;

									col(b->y, b->x, py, px, b->piece);

									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										wking.check = 1;
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						w->x -= t;
						w->y += t;
						if (wking.check == 0)
						{
							wking.check = 1;
							return;
						}
					}
				}
				//king
				if (w->piece == KING)
				{
					//right
					switch (locAlg(w->x, w->y, 1, 0))
					{
					case 0:
						break;
					case 1:
						break;
					case 2:
						w->x += 1;
						if (king.x == w->x + 1 && (king.y == w->y || king.y == w->y + 1 || king.y == w->y - 1))
						{
							w->x -= 1;
							break;
						}
						//run death sequence
						for (auto& b : bPiece)
						{
							if (b->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);

									check();
									w->x -= 1;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										wking.check = 1;
										return;
									}
								}
							}
						}
						break;
					case 3:
						w->x += 1;
						if (king.x == w->x + 1 && (king.y == w->y || king.y == w->y + 1 || king.y == w->y - 1))
						{
							w->x -= 1;
							break;
						}
						check();
						w->x -= 1;

						if (wking.check == 0)
						{
							wking.check = 1;
							return;
						}
						break;
					}

					//left
					switch (locAlg(w->x, w->y, -1, 0))
					{
					case 0:
						break;
					case 1:
						break;
					case 2:
						w->x -= 1;
						if (king.x == w->x - 1 && (king.y == w->y || king.y == w->y + 1 || king.y == w->y - 1))
						{
							w->x += 1;
							break;
						}
						//run death sequence
						for (auto& b : bPiece)
						{
							if (b->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);

									check();
									w->x += 1;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										wking.check = 1;
										return;
									}
								}
							}
						}
						break;
					case 3:
						w->x -= 1;
						if (king.x == w->x - 1 && (king.y == w->y || king.y == w->y + 1 || king.y == w->y - 1))
						{
							w->x += 1;
							break;
						}
						check();
						w->x += 1;

						if (wking.check == 0)
						{
							wking.check = 1;
							return;
						}
						break;
					}

					//up
					switch (locAlg(w->x, w->y, 0, -1))
					{
					case 0:
						break;
					case 1:
						break;
					case 2:
						w->y -= 1;
						if (king.y == w->y - 1 && (king.x == w->x || king.x == w->x + 1 || king.x == w->x - 1))
						{
							w->y += 1;
							break;
						}
						//run death sequence
						for (auto& b : bPiece)
						{
							if (b->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);

									check();
									w->y += 1;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										wking.check = 1;
										return;
									}
								}
							}
						}
						break;
					case 3:
						w->y -= 1;
						if (king.y == w->y - 1 && (king.x == w->x || king.x == w->x + 1 || king.x == w->x - 1))
						{
							w->y += 1;
							break;
						}
						check();
						w->y += 1;

						if (wking.check == 0)
						{
							wking.check = 1;
							return;
						}
						break;
					}

					//down
					switch (locAlg(w->x, w->y, 0, 1))
					{
					case 0:
						break;
					case 1:
						break;
					case 2:
						w->y += 1;
						if (king.y == w->y + 1 && (king.x == w->x || king.x == w->x + 1 || king.x == w->x - 1))
						{
							w->y -= 1;
							break;
						}
						//run death sequence
						for (auto& b : bPiece)
						{
							if (b->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);

									check();
									w->y -= 1;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										wking.check = 1;
										return;
									}
								}
							}
						}
						break;
					case 3:
						w->y += 1;
						if (king.y == w->y + 1 && (king.x == w->x || king.x == w->x + 1 || king.x == w->x - 1))
						{
							w->y -= 1;
							break;
						}
						check();
						w->y -= 1;

						if (wking.check == 0)
						{
							wking.check = 1;
							return;
						}
						break;
					}
					
					//right up
					switch (locAlg(w->x, w->y, 1, -1))
					{
					case 0:
						break;
					case 1:
						break;
					case 2:
						w->x += 1;
						w->y -= 1;
						if (king.y == w->y - 1 && king.x == w->x + 1)
						{
							w->x -= 1;
							w->y += 1;
							break;
						}

						//run death sequence
						for (auto& b : bPiece)
						{
							if (b->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);

									check();
									w->x -= 1;
									w->y += 1;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										wking.check = 1;
										return;
									}
								}
							}
						}
						break;
					case 3:
						w->x += 1;
						w->y -= 1;
						if (king.y == w->y - 1 && king.x == w->x + 1)
						{
							w->x -= 1;
							w->y += 1;
							break;
						}
						check();
						w->x -= 1;
						w->y += 1;

						if (wking.check == 0)
						{
							wking.check = 1;
							return;
						}
						break;
					}
					
					//left up
					switch (locAlg(w->x, w->y, -1, -1))
					{
					case 0:
						break;
					case 1:
						break;
					case 2:
						w->x -= 1;
						w->y -= 1;
						if (king.y == w->y - 1 && king.x == w->x - 1)
						{
							w->x += 1;
							w->y += 1;
							break;
						}
						//run death sequence
						for (auto& b : bPiece)
						{
							if (b->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);

									check();
									w->x += 1;
									w->y += 1;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										wking.check = 1;
										return;
									}
								}
							}
						}
						break;
					case 3:
						w->x -= 1;
						w->y -= 1;
						if (king.y == w->y - 1 && king.x == w->x - 1)
						{
							w->x += 1;
							w->y += 1;
							break;
						}
						check();
						w->x += 1;
						w->y += 1;

						if (wking.check == 0)
						{
							wking.check = 1;
							return;
						}
						break;
					}

					//right down
					switch (locAlg(w->x, w->y, 1, 1))
					{
					case 0:
						break;
					case 1:
						break;
					case 2:
						w->x += 1;
						w->y += 1; 
						if (king.y == w->y + 1 && king.x == w->x + 1)
						{
							w->x -= 1;
							w->y -= 1;
							break;
						}

						//run death sequence
						for (auto& b : bPiece)
						{
							if (b->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);

									check();
									w->x -= 1;
									w->y -= 1;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										wking.check = 1;
										return;
									}
								}
							}
						}
						break;
					case 3:
						w->x += 1;
						w->y += 1;
						if (king.y == w->y + 1 && king.x == w->x + 1)
						{
							w->x -= 1;
							w->y -= 1;
							break;
						}
						check();
						w->x -= 1;
						w->y -= 1;

						if (wking.check == 0)
						{
							wking.check = 1;
							return;
						}
						break;
					}
					
					//left down
					switch (locAlg(w->x, w->y, -1, 1))
					{
					case 0:
						break;
					case 1:
						break;
					case 2:
						w->x -= 1;
						w->y += 1;
						if (king.y == w->y + 1 && king.x == w->x - 1)
						{
							w->x += 1;
							w->y -= 1;
							break;
						}
						//run death sequence
						for (auto& b : bPiece)
						{
							if (b->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);

									check();
									w->x += 1;
									w->y -= 1;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										wking.check = 1;
										return;
									}
								}
							}
						}
						break;
					case 3:
						w->x -= 1;
						w->y += 1;
						if (king.y == w->y + 1 && king.x == w->x - 1)
						{
							w->x += 1;
							w->y -= 1;
							break;
						}
						check();
						w->x += 1;
						w->y -= 1;

						if (wking.check == 0)
						{
							wking.check = 1;
							return;
						}
						break;
					}
				}
			}
		}
		//if this runs it means checkmate so black wins
		win = 1;
	}

	//if black is in check
	if (king.check == 1)
	{
		for (auto& b : bPiece)
		{
			if (b->death == 0)
			{
				valid = 1;
				bxtemp = -1;
				wxtemp = -1;
				bytemp = -1;
				wytemp = -1;
				px = 0;
				py = 0;

				//pawn
				if (b->piece == PAWN)
				{
					//piece in front
					for (auto& b1 : bPiece)
					{
						if (b->x == b1->x && b1->y == b->y - 1)
						{
							valid = 0;
							break;
						}
					}
					for (auto& w : wPiece)
					{
						if (b->x == w->x && w->y == b->y - 1)
						{
							valid = 0;
							break;
						}
					}

					if (valid == 1)
					{
						b->y -= 1;
						check();
						b->y += 1;
						if (king.check == 0)
						{
							king.check = 1;
							return;
						}
					}

					if (b->movesMade == 0)
					{
						for (auto& b1 : bPiece)
						{
							if (b->y - 2 == b1->y && b->x == b1->x)
							{
								valid = 0;
								break;
							}
						}
						for (auto& w : wPiece)
						{
							if (b->y - 2 == w->y && b->x == w->x)
							{
								valid = 0;
								break;
							}
						}
					}
					else 
					{
						valid = 0;
					}

					if (valid == 1)
					{
						b->y -= 2;
						check();
						b->y += 2;
						if (king.check == 0)
						{
							king.check = 1;
							return;
						}
					}

					//killing piece
					for (auto& w : wPiece)
					{
						if (w->piece != KING)
						{
							if (w->x == b->x + 1 && w->y == b->y - 1)
							{
								wDead++;
								px = w->x;
								py = w->y;
								w->death = 1;
								w->dead(wDead);

								b->x += 1;
								b->y -= 1;
								check();
								b->x -= 1;
								b->y += 1;

								col(w->y, w->x, py, px, w->piece + 6);
								wDead--;
								w->x = px;
								w->y = py;
								w->death = 0;

								if (king.check == 0)
								{
									king.check = 1;
									return;
								}
							}
							if (w->x == b->x - 1 && w->y == b->y - 1)
							{
								wDead++;
								px = w->x;
								py = w->y;
								w->death = 1;
								w->dead(wDead);

								b->x -= 1;
								b->y -= 1;
								check();
								b->x += 1;
								b->y += 1;

								col(w->y, w->x, py, px, w->piece + 6);
								wDead--;
								w->x = px;
								w->y = py;
								w->death = 0;

								if (king.check == 0)
								{
									king.check = 1;
									return;
								}
							}
						}
						if (w->enPassantCnt == 1)
						{
							if (w->x == b->x + 1 && w->y == b->y)
							{
								wDead++;
								px = w->x;
								py = w->y;
								w->death = 1;
								w->dead(wDead);

								b->x += 1;
								b->y -= 1;
								check();
								b->x -= 1;
								b->y += 1;

								col(w->y, w->x, py, px, w->piece + 6);
								wDead--;
								w->x = px;
								w->y = py;
								w->death = 0;

								if (king.check == 0)
								{
									king.check = 1;
									return;
								}
							}
							if (w->x == b->x - 1 && w->y == b->y)
							{
								wDead++;
								px = w->x;
								py = w->y;
								w->death = 1;
								w->dead(wDead);

								b->x -= 1;
								b->y -= 1;
								check();
								b->x += 1;
								b->y += 1;

								col(w->y, w->x, py, px, w->piece + 6);
								wDead--;
								w->x = px;
								w->y = py;
								w->death = 0;

								if (king.check == 0)
								{
									king.check = 1;
									return;
								}
							}
						}
					}
				}
				//rook
				if(b->piece == ROOK)
				{
					//horizontal left movement
					for (auto& w : wPiece)
					{
						if (w->x < b->x && w->y == b->y && w->x > wxtemp)
						{
							//for multiple pieces in the same row select one and store its x value then compare 
							//its x location to other black pieces and see which one is closest to the rook being 
							//checked and say that bxtemp is that x value
							wxtemp = w->x;
						}
					}
					for (auto& b1 : bPiece)
					{
						if (b1->x < b->x && b1->y == b->y && b1->x > wxtemp && b1->x > bxtemp && b1->piece != KING)
						{
							bxtemp = b1->x;
						}
					}

					int t = 0;
					while (t <= 7)
					{
						t++;
						b->x -= t;
						if (b->x == bxtemp)
						{
							b->x += t;
							break;
						}
						if (b->x == wxtemp)
						{
							for (auto& w : wPiece)
							{
								if (w->x == wxtemp && w->y == b->y)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);
									check();
									b->x += t;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										king.check = 1;
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						b->x += t;
						if (king.check == 0)
						{
							king.check = 1;
							return;
						}
					}
					
					wxtemp = 8;
					bxtemp = 8;

					//horizontal right movement
					for (auto& w : wPiece)
					{
						if (w->x > b->x && w->y == b->y && w->x < wxtemp)
						{
							wxtemp = w->x;
						}
					}
					for (auto& b1 : bPiece)
					{
						if (b1->x > b->x && b1->y == b->y && b1->x < wxtemp && b1->x < bxtemp && b1->piece != KING)
						{
							bxtemp = b1->x;
						}
					}

					t = 0;
					while (t <= 7)
					{
						t++;
						b->x += t;
						if (b->x == bxtemp)
						{
							b->x -= t;
							break;
						}
						if (b->x == wxtemp)
						{
							for (auto& w : wPiece)
							{
								if (w->x == wxtemp && w->y == b->y)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);

									check();
									b->x -= t;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										king.check = 1;
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						b->x -= t;

						if (king.check == 0)
						{
							king.check = 1;
							return;
						}
					}
					
					//vertical up movement
					for (auto& w : wPiece)
					{
						if (w->y < b->y && w->x == b->x && w->y > wytemp)
						{
							wytemp = w->y;
						}
					}
					for (auto& b1 : bPiece)
					{
						if (b1->y < b->y && b1->x == b->x && b1->y > wytemp && b1->y > bytemp && b1->piece != KING)
						{
							bytemp = b1->y;
						}
					}

					t = 0;
					while (t <= 7)
					{
						t++;
						b->y -= t;
						if (b->y == bytemp)
						{
							b->y += t;
							break;
						}
						if (b->y == wytemp)
						{
							for (auto& w : wPiece)
							{
								if (w->y == wytemp && w->x == b->x)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);

									check();
									b->y += t;

									col(w->y, w->x, py, px, w->piece + 6);
									bDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										king.check = 1;
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						b->y += t;
						if (king.check == 0)
						{
							king.check = 1;
							return;
						}
					}

					bytemp = 8;
					wytemp = 8;

					//vertical down movement
					for (auto& w : wPiece)
					{
						if (w->y > b->y && w->x == b->x && w->y < wytemp)
						{
							wytemp = w->y;
						}
					}
					for (auto& b1 : bPiece)
					{
						if (b1->y > b->y && b1->x == b->x && b1->y < wytemp && b1->y < bytemp && b1->piece != KING)
						{
							bytemp = b1->y;
						}
					}

					t = 0;
					while (t <= 7)
					{
						t++;
						b->y += t;
						if (b->y == bytemp)
						{
							b->y -= t;
							break;
						}
						if (b->y == wytemp)
						{
							for (auto& w : wPiece)
							{
								if (w->y == wytemp && w->x == b->x)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);

									check();
									b->y -= t;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										king.check = 1;
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						b->y -= t;
						if (king.check == 0)
						{
							king.check = 1;
							return;
						}
					}
				}
				//horse
				if (b->piece == HORSE)
				{
					switch (locAlg(b->x, b->y, -2, -1))
					{
					case 0:
						break;
					case 1:
						b->x -= 2;
						b->y -= 1;
						//run death sequence
						for (auto& w : wPiece)
						{
							if (w->piece != KING)
							{
								if (b->x == w->x && w->y == b->y)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);

									check();
									b->x += 2;
									b->y += 1;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										king.check = 1;
										return;
									}
								}
							}
						}
						break;
					case 2:
						break;
					case 3:
						b->x -= 2;
						b->y -= 1;
						check();
						b->x += 2;
						b->y += 1;

						if (king.check == 0)
						{
							king.check = 1;
							return;
						}
						break;
					}
					
					switch (locAlg(b->x, b->y, -2, 1))
					{
					case 0:
						break;
					case 1:
						b->x -= 2;
						b->y += 1;
						//run death sequence
						for (auto& w : wPiece)
						{
							if (w->piece != KING)
							{
								if (b->x == w->x && w->y == b->y)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);

									check();
									b->x += 2;
									b->y -= 1;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										king.check = 1;
										return;
									}
								}
							}
						}
						break;
					case 2:
						break;
					case 3:
						b->x -= 2;
						b->y += 1;
						check();
						b->x += 2;
						b->y -= 1;

						if (king.check == 0)
						{
							king.check = 1;
							return;
						}
						break;
					}

					switch (locAlg(b->x, b->y, 2, -1))
					{
					case 0:
						break;
					case 1:
						b->x += 2;
						b->y -= 1;
						//run death sequence
						for (auto& w : wPiece)
						{
							if (w->piece != KING)
							{
								if (b->x == w->x && w->y == b->y)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);

									check();
									b->x -= 2;
									b->y += 1;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										king.check = 1;
										return;
									}
								}
							}
						}
						break;
					case 2:
						break;
					case 3:
						b->x += 2;
						b->y -= 1;
						check();
						b->x -= 2;
						b->y += 1;

						if (king.check == 0)
						{
							king.check = 1;
							return;
						}
						break;
					}

					switch (locAlg(b->x, b->y, 2, 1))
					{
					case 0:
						break;
					case 1:
						b->x += 2;
						b->y += 1;
						//run death sequence
						for (auto& w : wPiece)
						{
							if (w->piece != KING)
							{
								if (b->x == w->x && w->y == b->y)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);

									check();
									b->x -= 2;
									b->y -= 1;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										king.check = 1;
										return;
									}
								}
							}
						}
						break;
					case 2:
						break;
					case 3:
						b->x += 2;
						b->y += 1;
						check();
						b->x -= 2;
						b->y -= 1;

						if (king.check == 0)
						{
							king.check = 1;
							return;
						}
						break;
					}

					switch (locAlg(b->x, b->y, -1, -2))
					{
					case 0:
						break;
					case 1:
						b->x -= 1;
						b->y -= 2;
						//run death sequence
						for (auto& w : wPiece)
						{
							if (w->piece != KING)
							{
								if (b->x == w->x && w->y == b->y)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);

									check();
									b->x += 1;
									b->y += 2;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										king.check = 1;
										return;
									}
								}
							}
						}
						break;
					case 2:
						break;
					case 3:
						b->x -= 1;
						b->y -= 2;
						check();
						b->x += 1;
						b->y += 2;

						if (king.check == 0)
						{
							king.check = 1;
							return;
						}
						break;
					}

					switch (locAlg(b->x, b->y, -1, 2))
					{
					case 0:
						break;
					case 1:
						b->x -= 1;
						b->y += 2;
						//run death sequence
						for (auto& w : wPiece)
						{
							if (w->piece != KING)
							{
								if (b->x == w->x && w->y == b->y)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);

									check();
									b->x += 1;
									b->y -= 2;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										king.check = 1;
										return;
									}
								}
							}
						}
						break;
					case 2:
						break;
					case 3:
						b->x -= 1;
						b->y += 2;
						check();
						b->x += 1;
						b->y -= 2;

						if (king.check == 0)
						{
							king.check = 1;
							return;
						}
						break;
					}

					switch (locAlg(b->x, b->y, 1, -2))
					{
					case 0:
						break;
					case 1:
						b->x += 1;
						b->y -= 2;
						//run death sequence
						for (auto& w : wPiece)
						{
							if (w->piece != KING)
							{
								if (b->x == w->x && w->y == b->y)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);

									check();
									b->x -= 1;
									b->y += 2;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										king.check = 1;
										return;
									}
								}
							}
						}
						break;
					case 2:
						break;
					case 3:
						b->x += 1;
						b->y -= 2;
						check();
						b->x += 1;
						b->y -= 2;

						if (king.check == 0)
						{
							king.check = 1;
							return;
						}
						break;
					}

					switch (locAlg(b->x, b->y, 1, 2))
					{
					case 0:
						break;
					case 1:
						b->x += 1;
						b->y += 2;
						//run death sequence
						for (auto& w : wPiece)
						{
							if (w->piece != KING)
							{
								if (b->x == w->x && w->y == b->y)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);

									check();
									b->x -= 1;
									b->y -= 2;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										king.check = 1;
										return;
									}
								}
							}
						}
						break;
					case 2:
						break;
					case 3:
						b->x += 1;
						b->y += 2;
						check();
						b->x -= 1;
						b->y -= 2;

						if (king.check == 0)
						{
							king.check = 1;
							return;
						}
						break;
					}
				}
				//bishop
				if (b->piece == BISHOP)
				{
					//left down diagonal
					wytemp = 8;
					bytemp = 8;
					t = 0;

					for (auto& w : wPiece)
					{
						if (w->x < b->x && w->y > b->y && b->x - w->x == w->y - b->y && w->x > wxtemp && w->y < wytemp)
						{
							wxtemp = w->x;
							wytemp = w->y;
						}
					}
					for (auto& b1 : wPiece)
					{
						if (b1->x < b->x && b1->y > b->y && b->x - b1->x == b1->y - b->y && b1->x > wxtemp && b1->y < wytemp && b1->x > bxtemp && b1->y < bytemp)
						{
							bxtemp = b1->x;
							bytemp = b1->y;
						}
					}

					while (t <= 7)
					{
						t++;
						b->x -= t;
						b->y += t;

						if (b->x == bxtemp || b->y == bytemp)
						{
							b->x += t;
							b->y -= t;
							break;
						}

						if (b->x == wxtemp || b->y == wytemp)
						{
							for (auto& w : wPiece)
							{
								if (w->x == wxtemp && w->y == wytemp)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);
									check();
									b->x += t;
									b->y -= t;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										king.check = 1;
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						b->x += t;
						b->y -= t;

						if (king.check == 0)
						{
							king.check = 1;
							return;
						}
					}

					//right down diagonal
					bxtemp = 8;
					bytemp = 8;
					wxtemp = 8;
					wytemp = 8;
					t = 0;

					for (auto& w : wPiece)
					{
						if (w->x > b->x && w->y > b->y && w->x - b->x == w->y - b->y && w->x < wxtemp && w->y < wytemp)
						{
							wxtemp = w->x;
							wytemp = w->y;
						}
					}
					for (auto& b1 : bPiece)
					{
						if (b1->x > b->x && b1->y > b->y && b1->x - b->x == b1->y - b->y && b1->x < wxtemp && b1->y < wytemp && b1->x < bxtemp && b1->y < bytemp)
						{
							bxtemp = b1->x;
							bytemp = b1->y;
						}
					}

					while (t <= 7)
					{
						t++;
						b->x += t;
						b->y += t;
						
						if (b->x == bxtemp || b->y == bytemp)
						{
							b->x -= t;
							b->y -= t;
							break;
						}

						if (b->x == wxtemp || b->y == wytemp)
						{
							for (auto& w : wPiece)
							{
								if (w->x == wxtemp && w->y == wytemp)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);
									check();
									b->x -= t;
									b->y -= t;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;
									
									if (king.check == 0)
									{
										king.check = 1;
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						b->x -= t;
						b->y -= t;
						if (king.check == 0)
						{
							king.check = 1;
							return;
						}
					}
					
					//left up diagonal
					bxtemp = -1;
					bytemp = -1;
					wxtemp = -1;
					wytemp = -1;
					t = 0;

					for (auto& w : wPiece)
					{
						if (w->x < b->x && w->y < b->y && b->x - w->x == b->y - w->y && w->x > wxtemp && w->y > wytemp)
						{
							wxtemp = w->x;
							wytemp = w->y;
						}
					}
					for (auto& b1 : bPiece)
					{
						if (b1->x < b->x && b1->y < b->y && b->x - b1->x == b->y - b1->y && b1->x > wxtemp && b1->y > wytemp && b1->x > bxtemp && b1->y > bytemp)
						{
							bxtemp = b1->x;
							bytemp = b1->y;
						}
					}

					while (t <= 7)
					{
						t++;
						b->x -= t;
						b->y -= t;
						
						if (b->x == bxtemp || b->y == bytemp)
						{
							b->x += t;
							b->y += t;
							break;
						}

						if (b->x == wxtemp || b->y == wytemp)
						{
							for (auto& w : wPiece)
							{
								if (w->x == wxtemp && w->y == wytemp)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);
									check();
									b->x += t;
									b->y += t;

									col(w->y, w->x, py, px, w->piece + 6);

									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;
								
									if (king.check == 0)
									{
										king.check = 1;
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						b->x += t;
						b->y += t;
						if (king.check == 0)
						{
							king.check = 1;
							return;
						}
					}
					
					//right up diagonal
					bxtemp = 8;
					bytemp = -1;
					wxtemp = 8;
					wytemp = -1;
					t = 0;

					for (auto& w : wPiece)
					{
						if (w->x > b->x && w->y < b->y && w->x - b->x == b->y - w->y && w->x < wxtemp && w->y > wytemp)
						{
							wxtemp = w->x;
							wytemp = w->y;
						}
					}
					for (auto& b1 : bPiece)
					{
						if (b1->x > b->x && b1->y < b->y && b1->x - b->x == b->y - b1->y && b1->x < wxtemp && b1->y > wytemp && b1->x < bxtemp && b1->y > bytemp)
						{
							bxtemp = b1->x;
							bytemp = b1->y;
						}
					}

					while (t <= 7)
					{
						t++;
						b->x += t;
						b->y -= t;
						
						if (b->x == bxtemp || b->y == bytemp)
						{
							b->x -= t;
							b->y += t;
							break;
						}

						if (b->x == wxtemp || b->y == wytemp)
						{
							for (auto& w : wPiece)
							{
								if (w->x == wxtemp && w->y == wytemp)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);
									check();
									b->x -= t;
									b->y += t;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;
									
									if (king.check == 0)
									{
										king.check = 1;
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						b->x -= t;
						b->y += t;
						if (king.check == 0)
						{
							king.check = 1;
							return;
						}
					}
				}
				//queen
				if (b->piece == QUEEN)
				{
					//horizontal left movement
					for (auto& w : wPiece)
					{
						if (w->x < b->x && w->y == b->y && w->x > wxtemp)
						{
							wxtemp = w->x;
						}
					}
					for (auto& b1 : bPiece)
					{
						if (b1->x < b->x && b1->y == b->y && b1->x > wxtemp && b1->x > bxtemp && b1->piece != KING)
						{
							bxtemp = b1->x;
						}
					}

					int t = 0;
					while (t <= 7)
					{
						t++;
						b->x -= t;
						if (b->x == bxtemp)
						{
							b->x += t;
							break;
						}
						if (b->x == wxtemp)
						{
							for (auto& w : wPiece)
							{
								if (w->x == wxtemp && w->y == b->y)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);
									check();
									b->x += t;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										king.check = 1;
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						b->x += t;
						if (king.check == 0)
						{
							king.check = 1;
							return;
						}
					}
					
					wxtemp = 8;
					bxtemp = 8;

					//horizontal right movement
					for (auto& w : wPiece)
					{
						if (w->x > b->x && w->y == b->y && w->x < wxtemp)
						{
							wxtemp = w->x;
						}
					}
					for (auto& b1 : bPiece)
					{
						if (b1->x > b->x && b1->y == b->y && b1->x < wxtemp && b1->x < bxtemp && b1->piece != KING)
						{
							bxtemp = b1->x;
						}
					}

					t = 0;
					while (t <= 7)
					{
						t++;
						b->x += t;
						if (b->x == bxtemp)
						{
							b->x -= t;
							break;
						}
						if (b->x == wxtemp)
						{
							for (auto& w : wPiece)
							{
								if (w->x == wxtemp && w->y == b->y)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);

									check();
									b->x -= t;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										king.check = 1;
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						b->x -= t;

						if (king.check == 0)
						{
							king.check = 1;
							return;
						}
					}
					
					//vertical up movement
					for (auto& w : wPiece)
					{
						if (w->y < b->y && w->x == b->x && w->y > wytemp)
						{
							wytemp = w->y;
						}
					}
					for (auto& b1 : bPiece)
					{
						if (b1->y < b->y && b1->x == b->x && b1->y > wytemp && b1->y > bytemp && b1->piece != KING)
						{
							bytemp = b1->y;
						}
					}

					t = 0;
					while (t <= 7)
					{
						t++;
						b->y -= t;
						if (b->y == bytemp)
						{
							b->y += t;
							break;
						}
						if (b->y == wytemp)
						{
							for (auto& w : wPiece)
							{
								if (w->y == wytemp && w->x == b->x)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);

									check();
									b->y += t;

									col(w->y, w->x, py, px, w->piece + 6);
									bDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										king.check = 1;
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						b->y += t;
						if (king.check == 0)
						{
							king.check = 1;
							return;
						}
					}

					bytemp = 8;
					wytemp = 8;

					//vertical down movement
					for (auto& w : wPiece)
					{
						if (w->y > b->y && w->x == b->x && w->y < wytemp)
						{
							wytemp = w->y;
						}
					}
					for (auto& b1 : bPiece)
					{
						if (b1->y > b->y && b1->x == b->x && b1->y < wytemp && b1->y < bytemp && b1->piece != KING)
						{
							bytemp = b1->y;
						}
					}

					t = 0;
					while (t <= 7)
					{
						t++;
						b->y += t;
						if (b->y == bytemp)
						{
							b->y -= t;
							break;
						}
						if (b->y == wytemp)
						{
							for (auto& w : wPiece)
							{
								if (w->y == wytemp && w->x == b->x)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);

									check();
									b->y -= t;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										king.check = 1;
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						b->y -= t;
						if (king.check == 0)
						{
							king.check = 1;
							return;
						}
					}

					//left down diagonal
					wytemp = 8;
					bytemp = 8;
					t = 0;

					for (auto& w : wPiece)
					{
						if (w->x < b->x && w->y > b->y && b->x - w->x == w->y - b->y && w->x > wxtemp && w->y < wytemp)
						{
							wxtemp = w->x;
							wytemp = w->y;
						}
					}
					for (auto& b1 : wPiece)
					{
						if (b1->x < b->x && b1->y > b->y && b->x - b1->x == b1->y - b->y && b1->x > wxtemp && b1->y < wytemp && b1->x > bxtemp && b1->y < bytemp)
						{
							bxtemp = b1->x;
							bytemp = b1->y;
						}
					}

					while (t <= 7)
					{
						t++;
						b->x -= t;
						b->y += t;

						if (b->x == bxtemp || b->y == bytemp)
						{
							b->x += t;
							b->y -= t;
							break;
						}

						if (b->x == wxtemp || b->y == wytemp)
						{
							for (auto& w : wPiece)
							{
								if (w->x == wxtemp && w->y == wytemp)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);
									check();
									b->x += t;
									b->y -= t;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										king.check = 1;
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						b->x += t;
						b->y -= t;

						if (king.check == 0)
						{
							king.check = 1;
							return;
						}
					}

					//right down diagonal
					bxtemp = 8;
					bytemp = 8;
					wxtemp = 8;
					wytemp = 8;
					t = 0;

					for (auto& w : wPiece)
					{
						if (w->x > b->x && w->y > b->y && w->x - b->x == w->y - b->y && w->x < wxtemp && w->y < wytemp)
						{
							wxtemp = w->x;
							wytemp = w->y;
						}
					}
					for (auto& b1 : bPiece)
					{
						if (b1->x > b->x && b1->y > b->y && b1->x - b->x == b1->y - b->y && b1->x < wxtemp && b1->y < wytemp && b1->x < bxtemp && b1->y < bytemp)
						{
							bxtemp = b1->x;
							bytemp = b1->y;
						}
					}

					while (t <= 7)
					{
						t++;
						b->x += t;
						b->y += t;

						if (b->x == bxtemp || b->y == bytemp)
						{
							b->x -= t;
							b->y -= t;
							break;
						}

						if (b->x == wxtemp || b->y == wytemp)
						{
							for (auto& w : wPiece)
							{
								if (w->x == wxtemp && w->y == wytemp)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);
									check();
									b->x -= t;
									b->y -= t;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										king.check = 1;
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						b->x -= t;
						b->y -= t;
						if (king.check == 0)
						{
							king.check = 1;
							return;
						}
					}

					//left up diagonal
					bxtemp = -1;
					bytemp = -1;
					wxtemp = -1;
					wytemp = -1;
					t = 0;

					for (auto& w : wPiece)
					{
						if (w->x < b->x && w->y < b->y && b->x - w->x == b->y - w->y && w->x > wxtemp && w->y > wytemp)
						{
							wxtemp = w->x;
							wytemp = w->y;
						}
					}
					for (auto& b1 : bPiece)
					{
						if (b1->x < b->x && b1->y < b->y && b->x - b1->x == b->y - b1->y && b1->x > wxtemp && b1->y > wytemp && b1->x > bxtemp && b1->y > bytemp)
						{
							bxtemp = b1->x;
							bytemp = b1->y;
						}
					}

					while (t <= 7)
					{
						t++;
						b->x -= t;
						b->y -= t;

						if (b->x == bxtemp || b->y == bytemp)
						{
							b->x += t;
							b->y += t;
							break;
						}

						if (b->x == wxtemp || b->y == wytemp)
						{
							for (auto& w : wPiece)
							{
								if (w->x == wxtemp && w->y == wytemp)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);
									check();
									b->x += t;
									b->y += t;

									col(w->y, w->x, py, px, w->piece + 6);

									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										king.check = 1;
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						b->x += t;
						b->y += t;
						if (king.check == 0)
						{
							king.check = 1;
							return;
						}
					}

					//right up diagonal
					bxtemp = 8;
					bytemp = -1;
					wxtemp = 8;
					wytemp = -1;
					t = 0;

					for (auto& w : wPiece)
					{
						if (w->x > b->x && w->y < b->y && w->x - b->x == b->y - w->y && w->x < wxtemp && w->y > wytemp)
						{
							wxtemp = w->x;
							wytemp = w->y;
						}
					}
					for (auto& b1 : bPiece)
					{
						if (b1->x > b->x && b1->y < b->y && b1->x - b->x == b->y - b1->y && b1->x < wxtemp && b1->y > wytemp && b1->x < bxtemp && b1->y > bytemp)
						{
							bxtemp = b1->x;
							bytemp = b1->y;
						}
					}

					while (t <= 7)
					{
						t++;
						b->x += t;
						b->y -= t;

						if (b->x == bxtemp || b->y == bytemp)
						{
							b->x -= t;
							b->y += t;
							break;
						}

						if (b->x == wxtemp || b->y == wytemp)
						{
							for (auto& w : wPiece)
							{
								if (w->x == wxtemp && w->y == wytemp)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);
									check();
									b->x -= t;
									b->y += t;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										king.check = 1;
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						b->x -= t;
						b->y += t;
						if (king.check == 0)
						{
							king.check = 1;
							return;
						}
					}
				}
				//king
				if (b->piece == KING)
				{
					//right
					switch (locAlg(b->x, b->y, 1, 0))
					{
					case 0:
						break;
					case 1:
						b->x += 1;
						if (wking.x == b->x + 1 && (wking.y == b->y || wking.y == b->y + 1 || wking.y == b->y - 1))
						{
							b->x -= 1;
							break;
						}
						
						for (auto& w : wPiece)
						{
							if (w->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);

									check();
									b->x -= 1;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										king.check = 1;
										return;
									}
								}
							}
						}
						break;
					case 2:
						break;
					case 3:
						b->x += 1;
						if (wking.x == b->x + 1 && (wking.y == b->y || wking.y == b->y + 1 || wking.y == b->y - 1))
						{
							b->x -= 1;
							break;
						}
						check();
						b->x -= 1;

						if (king.check == 0)
						{
							king.check = 1;
							return;
						}
						break;
					}

					//left
					switch (locAlg(b->x, b->y, -1, 0))
					{
					case 0:
						break;
					case 1:
						b->x -= 1;
						if (wking.x == b->x - 1 && (wking.y == b->y || wking.y == b->y + 1 || wking.y == b->y - 1))
						{
							b->x += 1;
							break;
						}

						for (auto& w : wPiece)
						{
							if (w->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);

									check();
									b->x += 1;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										king.check = 1;
										return;
									}
								}
							}
						}
						break;
					case 2:
						break;
					case 3:
						b->x -= 1;
						if (wking.x == b->x - 1 && (wking.y == b->y || wking.y == b->y + 1 || wking.y == b->y - 1))
						{
							b->x += 1;
							break;
						}
						check();
						b->x += 1;

						if (king.check == 0)
						{
							king.check = 1;
							return;
						}
						break;
					}

					//up
					switch (locAlg(b->x, b->y, 0, -1))
					{
					case 0:
						break;
					case 1:
						b->y -= 1;
						if (wking.y == b->y - 1 && (wking.x == b->x || wking.x == b->x + 1 || wking.x == b->x - 1))
						{
							b->y += 1;
							break;
						}

						for (auto& w : wPiece)
						{
							if (w->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);

									check();
									b->y += 1;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										king.check = 1;
										return;
									}
								}
							}
						}
						break;
					case 2:
						break;
					case 3:
						b->y -= 1;
						if (wking.y == b->y - 1 && (wking.x == b->x || wking.x == b->x + 1 || wking.x == b->x - 1))
						{
							b->y += 1;
							break;
						}
						check();
						b->y += 1;

						if (king.check == 0)
						{
							king.check = 1;
							return;
						}
						break;
					}

					//down
					switch (locAlg(b->x, b->y, 0, 1))
					{
					case 0:
						break;
					case 1:
						b->y += 1;
						if (wking.y == b->y + 1 && (wking.x == b->x || wking.x == b->x + 1 || wking.x == b->x - 1))
						{
							b->y -= 1;
							break;
						}

						for (auto& w : wPiece)
						{
							if (w->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);

									check();
									b->y -= 1;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										king.check = 1;
										return;
									}
								}
							}
						}
						break;
					case 2:
						break;
					case 3:
						b->y += 1;
						if (wking.y == b->y + 1 && (wking.x == b->x || wking.x == b->x + 1 || wking.x == b->x - 1))
						{
							b->y -= 1;
							break;
						}
						check();
						b->y -= 1;

						if (king.check == 0)
						{
							king.check = 1;
							return;
						}
						break;
					}

					//right up
					switch (locAlg(b->x, b->y, 1, -1))
					{
					case 0:
						break;
					case 1:
						b->x += 1;
						b->y -= 1;
						if (wking.y == b->y - 1 && wking.x == b->x + 1)
						{
							b->x -= 1;
							b->y += 1;
							break;
						}

						for (auto& w : wPiece)
						{
							if (w->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);

									check();
									b->x -= 1;
									b->y += 1;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										king.check = 1;
										return;
									}
								}
							}
						}
						break;
					case 2:
						break;
					case 3:
						b->x += 1;
						b->y -= 1;
						if (wking.y == b->y - 1 && wking.x == b->x + 1)
						{
							b->x -= 1;
							b->y += 1;
							break;
						}
						check();
						b->x -= 1;
						b->y += 1;

						if (king.check == 0)
						{
							king.check = 1;
							return;
						}
						break;
					}

					//left up
					switch (locAlg(b->x, b->y, -1, -1))
					{
					case 0:
						break;
					case 1:
						b->x -= 1;
						b->y -= 1;
						if (wking.y == b->y - 1 && wking.x == b->x - 1)
						{
							b->x += 1;
							b->y += 1;
							break;
						}

						for (auto& w : wPiece)
						{
							if (w->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);

									check();
									b->x += 1;
									b->y += 1;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										king.check = 1;
										return;
									}
								}
							}
						}
						break;
					case 2:
						break;
					case 3:
						b->x -= 1;
						b->y -= 1;
						if (wking.y == b->y - 1 && wking.x == b->x - 1)
						{
							b->x += 1;
							b->y += 1;
							break;
						}
						check();
						b->x += 1;
						b->y += 1;

						if (king.check == 0)
						{
							king.check = 1;
							return;
						}
						break;
					}

					//right down
					switch (locAlg(b->x, b->y, 1, 1))
					{
					case 0:
						break;
					case 1:
						b->x += 1;
						b->y += 1;
						if (wking.y == b->y + 1 && wking.x == b->x + 1)
						{
							b->x -= 1;
							b->y -= 1;
							break;
						}

						for (auto& w : wPiece)
						{
							if (w->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);

									check();
									b->x -= 1;
									b->y -= 1;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										king.check = 1;
										return;
									}
								}
							}
						}
						break;
					case 2:
						break;
					case 3:
						b->x += 1;
						b->y += 1;
						if (wking.y == b->y + 1 && wking.x == b->x + 1)
						{
							b->x -= 1;
							b->y -= 1;
							break;
						}
						check();
						b->x -= 1;
						b->y -= 1;

						if (king.check == 0)
						{
							king.check = 1;
							return;
						}
						break;
					}

					//left down
					switch (locAlg(b->x, b->y, -1, 1))
					{
					case 0:
						break;
					case 1:
						b->x -= 1;
						b->y += 1;
						if (wking.y == b->y + 1 && wking.x == b->x - 1)
						{
							b->x += 1;
							b->y -= 1;
							break;
						}

						for (auto& w : wPiece)
						{
							if (w->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);

									check();
									b->x += 1;
									b->y -= 1;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										king.check = 1;
										return;
									}
								}
							}
						}
						break;
					case 2:
						break;
					case 3:
						b->x -= 1;
						b->y += 1;
						if (wking.y == b->y + 1 && wking.x == b->x - 1)
						{
							b->x += 1;
							b->y -= 1;
							break;
						}
						check();
						b->x += 1;
						b->y -= 1;

						if (king.check == 0)
						{
							king.check = 1;
							return;
						}
						break;
					}
				}
			}
		}
		//if this runs it means checkmate so white wins
		win = 2;
	}
}

//checks if color is in stalemate
void stalemate()
{
	//uses checkmate function, but will only stop if the function results in a move thats not in check
	//otherwise it means that the color is in stalemate
	int valid = 1;
	int bxtemp = 0;
	int wxtemp = 0;
	int bytemp = 0;
	int wytemp = 0;
	int px = 0;
	int py = 0;
	int t = 0;

	//only kings on each side left
	for (auto& w : wPiece)
	{
		if (w->death == 0)
		{
			t++;
		}
	}
	for (auto& b : bPiece)
	{
		if (b->death == 0)
		{
			t++;
		}
	}
	if (t == 2)
	{
		win = 5;
		return;
	}
	t = 0;

	//if white is in check
	if (wking.check == 0)
	{
		for (auto& w : wPiece)
		{
			if (w->death == 0)
			{
				valid = 1;
				bxtemp = -1;
				wxtemp = -1;
				bytemp = -1;
				wytemp = -1;
				px = 0;
				py = 0;

				//pawn
				if (w->piece == PAWN)
				{
					//piece in front
					for (auto& w1 : wPiece)
					{
						if (w->x == w1->x && w1->y == w->y + 1)
						{
							valid = 0;
							break;
						}
					}
					for (auto& b : bPiece)
					{
						if (w->x == b->x && b->y == w->y + 1)
						{
							valid = 0;
							break;
						}
					}

					if (valid == 1)
					{
						w->y += 1;
						check();
						w->y -= 1;
						if (wking.check == 0)
						{
							return;
						}
					}

					if (w->movesMade == 0)
					{
						for (auto& w1 : wPiece)
						{
							if (w->y + 2 == w1->y && w->x == w1->x)
							{
								valid = 0;
								break;
							}
						}
						for (auto& b : bPiece)
						{
							if (w->y + 2 == b->y && w->x == b->x)
							{
								valid = 0;
								break;
							}
						}
					}
					else
					{
						valid = 0;
					}

					if (valid == 1)
					{
						w->y += 2;
						check();
						w->y -= 2;
						if (wking.check == 0)
						{
							return;
						}
					}

					//killing piece
					for (auto& b : bPiece)
					{
						if (b->piece != KING)
						{
							if (b->x == w->x + 1 && b->y == w->y + 1)
							{
								bDead++;
								px = b->x;
								py = b->y;
								b->death = 1;
								b->dead(bDead);

								w->x += 1;
								w->y += 1;
								check();
								w->x -= 1;
								w->y -= 1;

								col(b->y, b->x, py, px, b->piece);
								bDead--;
								b->x = px;
								b->y = py;
								b->death = 0;

								if (wking.check == 0)
								{
									return;
								}
							}
							if (b->x == w->x - 1 && b->y == w->y + 1)
							{
								bDead++;
								px = b->x;
								py = b->y;
								b->death = 1;
								b->dead(bDead);

								w->x -= 1;
								w->y += 1;
								check();
								w->x += 1;
								w->y -= 1;

								col(b->y, b->x, py, px, b->piece);
								bDead--;
								b->x = px;
								b->y = py;
								b->death = 0;

								if (wking.check == 0)
								{
									return;
								}
							}
						}

						if (b->enPassantCnt == 1)
						{
							if (b->x == w->x + 1 && b->y == w->y)
							{
								bDead++;
								px = b->x;
								py = b->y;
								b->death = 1;
								b->dead(bDead);

								w->x += 1;
								w->y += 1;
								check();
								w->x -= 1;
								w->y -= 1;

								col(b->y, b->x, py, px, b->piece);
								bDead--;
								b->x = px;
								b->y = py;
								b->death = 0;

								if (wking.check == 0)
								{
									return;
								}
							}
							if (b->x == w->x - 1 && b->y == w->y)
							{
								bDead++;
								px = b->x;
								py = b->y;
								b->death = 1;
								b->dead(bDead);

								w->x -= 1;
								w->y += 1;
								check();
								w->x += 1;
								w->y -= 1;

								col(b->y, b->x, py, px, b->piece);
								bDead--;
								b->x = px;
								b->y = py;
								b->death = 0;

								if (wking.check == 0)
								{
									return;
								}
							}
						}
					}
				}
				//rook
				if (w->piece == ROOK)
				{
					//horizontal left movement
					for (auto& b : bPiece)
					{
						if (b->x < w->x && b->y == w->y && b->x > bxtemp)
						{
							//for multiple pieces in the same row select one and store its x value then compare 
							//its x location to other black pieces and see which one is closest to the rook being 
							//checked and say that bxtemp is that x value
							bxtemp = b->x;
						}
					}
					for (auto& w1 : wPiece)
					{
						if (w1->x < w->x && w1->y == w->y && w1->x > bxtemp && w1->x > wxtemp && w1->piece != KING)
						{
							wxtemp = w1->x;
						}
					}

					int t = 0;
					while (t <= 7)
					{
						t++;
						w->x -= t;
						if (w->x == wxtemp)
						{
							w->x += t;
							break;
						}
						if (w->x == bxtemp)
						{
							for (auto& b : bPiece)
							{
								if (b->x == bxtemp && b->y == w->y)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);
									check();
									w->x += t;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						w->x += t;
						if (wking.check == 0)
						{
							return;
						}
					}

					wxtemp = 8;
					bxtemp = 8;

					//horizontal right movement
					for (auto& b : bPiece)
					{
						if (b->x > w->x && b->y == w->y && b->x < bxtemp)
						{
							bxtemp = b->x;
						}
					}
					for (auto& w1 : wPiece)
					{
						if (w1->x > w->x && w1->y == w->y && w1->x < bxtemp && w1->x < wxtemp && w1->piece != KING)
						{
							wxtemp = w1->x;
						}
					}

					t = 0;
					while (t <= 7)
					{
						t++;
						w->x += t;
						if (w->x == wxtemp)
						{
							w->x -= t;
							break;
						}
						if (w->x == bxtemp)
						{
							for (auto& b : bPiece)
							{
								if (b->x == bxtemp && b->y == w->y)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);

									check();
									w->x -= t;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						w->x -= t;

						if (wking.check == 0)
						{
							return;
						}
					}

					//vertical up movement
					for (auto& b : bPiece)
					{
						if (b->y < w->y && b->x == w->x && b->y > bytemp)
						{
							bytemp = b->y;
						}
					}
					for (auto& w1 : wPiece)
					{
						if (w1->y < w->y && w1->x == w->x && w1->y > bytemp && w1->y > wytemp && w1->piece != KING)
						{
							wytemp = w1->y;
						}
					}

					t = 0;
					while (t <= 7)
					{
						t++;
						w->y -= t;
						if (w->y == wytemp)
						{
							w->y += t;
							break;
						}
						if (w->y == bytemp)
						{
							for (auto& b : bPiece)
							{
								if (b->y == bytemp && b->x == w->x)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);

									check();
									w->y += t;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						w->y += t;
						if (wking.check == 0)
						{
							return;
						}
					}

					bytemp = 8;
					wytemp = 8;

					//vertical down movement
					for (auto& b : bPiece)
					{
						if (b->y > w->y && b->x == w->x && b->y < bytemp)
						{
							bytemp = b->y;
						}
					}
					for (auto& w1 : wPiece)
					{
						if (w1->y > w->y && w1->x == w->x && w1->y < bytemp && w1->y < wytemp && w1->piece != KING)
						{
							wytemp = w1->y;
						}
					}

					t = 0;
					while (t <= 7)
					{
						t++;
						w->y += t;
						if (w->y == wytemp)
						{
							w->y -= t;
							break;
						}
						if (w->y == bytemp)
						{
							for (auto& b : bPiece)
							{
								if (b->y == bytemp && b->x == w->x)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);

									check();
									w->y -= t;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						w->y -= t;
						if (wking.check == 0)
						{
							return;
						}
					}
				}
				//horse
				if (w->piece == HORSE)
				{
					switch (locAlg(w->x, w->y, -2, -1))
					{
					case 0:
						break;
					case 1:
						break;
					case 2:
						w->x -= 2;
						w->y -= 1;
						//run death sequence
						for (auto& b : bPiece)
						{
							if (b->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);

									check();
									w->x += 2;
									w->y += 1;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										return;
									}
								}
							}
						}
						break;
					case 3:
						w->x -= 2;
						w->y -= 1;
						check();
						w->x += 2;
						w->y += 1;

						if (wking.check == 0)
						{
							return;
						}
						break;
					}

					switch (locAlg(w->x, w->y, -2, 1))
					{
					case 0:
						break;
					case 1:
						break;
					case 2:
						w->x -= 2;
						w->y += 1;
						//run death sequence
						for (auto& b : bPiece)
						{
							if (b->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);

									check();
									w->x += 2;
									w->y -= 1;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										return;
									}
								}
							}
						}
						break;
					case 3:
						w->x -= 2;
						w->y += 1;
						check();
						w->x += 2;
						w->y -= 1;

						if (wking.check == 0)
						{
							return;
						}
						break;
					}

					switch (locAlg(w->x, w->y, 2, -1))
					{
					case 0:
						break;
					case 1:
						break;
					case 2:
						w->x += 2;
						w->y -= 1;
						//run death sequence
						for (auto& b : bPiece)
						{
							if (b->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);

									check();
									w->x -= 2;
									w->y += 1;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										return;
									}
								}
							}
						}
						break;
					case 3:
						w->x += 2;
						w->y -= 1;
						check();
						w->x -= 2;
						w->y += 1;

						if (wking.check == 0)
						{
							return;
						}
						break;
					}

					switch (locAlg(w->x, w->y, 2, 1))
					{
					case 0:
						break;
					case 1:
						break;
					case 2:
						w->x += 2;
						w->y += 1;
						//run death sequence
						for (auto& b : bPiece)
						{
							if (b->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);

									check();
									w->x -= 2;
									w->y -= 1;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										return;
									}
								}
							}
						}
						break;
					case 3:
						w->x += 2;
						w->y += 1;
						check();
						w->x -= 2;
						w->y -= 1;

						if (wking.check == 0)
						{
							return;
						}
						break;
					}

					switch (locAlg(w->x, w->y, -1, -2))
					{
					case 0:
						break;
					case 1:
						break;
					case 2:
						w->x -= 1;
						w->y -= 2;
						//run death sequence
						for (auto& b : bPiece)
						{
							if (b->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);

									check();
									w->x += 1;
									w->y += 2;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										return;
									}
								}
							}
						}
						break;
					case 3:
						w->x -= 1;
						w->y -= 2;
						check();
						w->x += 1;
						w->y += 2;

						if (wking.check == 0)
						{
							return;
						}
						break;
					}

					switch (locAlg(w->x, w->y, -1, 2))
					{
					case 0:
						break;
					case 1:
						break;
					case 2:
						w->x -= 1;
						w->y += 2;
						//run death sequence
						for (auto& b : bPiece)
						{
							if (b->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);

									check();
									w->x += 1;
									w->y -= 2;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										return;
									}
								}
							}
						}
						break;
					case 3:
						w->x -= 1;
						w->y += 2;
						check();
						w->x += 1;
						w->y -= 2;

						if (wking.check == 0)
						{
							return;
						}
						break;
					}

					switch (locAlg(w->x, w->y, 1, -2))
					{
					case 0:
						break;
					case 1:
						break;
					case 2:
						w->x += 1;
						w->y -= 2;
						//run death sequence
						for (auto& b : bPiece)
						{
							if (b->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);

									check();
									w->x -= 1;
									w->y += 2;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										return;
									}
								}
							}
						}
						break;
					case 3:
						w->x += 1;
						w->y -= 2;
						check();
						w->x += 1;
						w->y -= 2;

						if (wking.check == 0)
						{
							return;
						}
						break;
					}

					switch (locAlg(w->x, w->y, 1, 2))
					{
					case 0:
						break;
					case 1:
						break;
					case 2:
						w->x += 1;
						w->y += 2;
						//run death sequence
						for (auto& b : bPiece)
						{
							if (b->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);

									check();
									w->x -= 1;
									w->y -= 2;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										return;
									}
								}
							}
						}
						break;
					case 3:
						w->x += 1;
						w->y += 2;
						check();
						w->x -= 1;
						w->y -= 2;

						if (wking.check == 0)
						{
							return;
						}
						break;
					}
				}
				//bishop
				if (w->piece == BISHOP)
				{
					//left down diagonal
					wytemp = 8;
					bytemp = 8;
					t = 0;

					for (auto& b : bPiece)
					{
						if (b->x < w->x && b->y > w->y && w->x - b->x == b->y - w->y && b->x > bxtemp && b->y < bytemp)
						{
							bxtemp = b->x;
							bytemp = b->y;
						}
					}

					for (auto& w1 : wPiece)
					{
						if (w1->x < w->x && w1->y > w->y && w->x - w1->x == w1->y - w->y && w1->x > bxtemp && w1->y < bytemp && w1->x > wxtemp && w1->y < wytemp)
						{
							wxtemp = w1->x;
							wytemp = w1->y;
						}
					}

					while (t <= 7)
					{
						t++;
						w->x -= t;
						w->y += t;

						if (w->x == wxtemp || w->y == wytemp)
						{
							w->x += t;
							w->y -= t;
							break;
						}

						if (w->x == bxtemp || w->y == bytemp)
						{
							for (auto& b : bPiece)
							{
								if (b->x == bxtemp && b->y == bytemp)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);
									check();
									w->x += t;
									w->y -= t;

									col(b->y, b->x, py, px, b->piece);

									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						w->x += t;
						w->y -= t;

						if (wking.check == 0)
						{
							return;
						}
					}

					//right down diagonal
					bxtemp = 8;
					bytemp = 8;
					wxtemp = 8;
					wytemp = 8;
					t = 0;

					for (auto& b : bPiece)
					{
						if (b->x > w->x && b->y > w->y && b->x - w->x == b->y - w->y && b->x < bxtemp && b->y < bytemp)
						{
							bxtemp = b->x;
							bytemp = b->y;
						}
					}

					for (auto& w1 : wPiece)
					{
						if (w1->x > w->x && w1->y > w->y && w1->x - w->x == w1->y - w->y && w1->x < bxtemp && w1->y < bytemp && w1->x < wxtemp && w1->y < wytemp)
						{
							wxtemp = w1->x;
							wytemp = w1->y;
						}
					}

					while (t <= 7)
					{
						t++;
						w->x += t;
						w->y += t;

						if (w->x == wxtemp || w->y == wytemp)
						{
							w->x -= t;
							w->y -= t;
							break;
						}

						if (w->x == bxtemp || w->y == bytemp)
						{
							for (auto& b : bPiece)
							{
								if (b->x == bxtemp && b->y == bytemp)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);
									check();
									w->x -= t;
									w->y -= t;

									col(b->y, b->x, py, px, b->piece);

									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						w->x -= t;
						w->y -= t;
						if (wking.check == 0)
						{
							return;
						}
					}

					//left up diagonal
					bxtemp = -1;
					bytemp = -1;
					wxtemp = -1;
					wytemp = -1;
					t = 0;

					for (auto& b : bPiece)
					{
						if (b->x < w->x && b->y < w->y && w->x - b->x == w->y - b->y && b->x > bxtemp && b->y > bytemp)
						{
							bxtemp = b->x;
							bytemp = b->y;
						}
					}

					for (auto& w1 : wPiece)
					{
						if (w1->x < w->x && w1->y < w->y && w->x - w1->x == w->y - w1->y && w1->x > bxtemp && w1->y > bytemp && w1->x > wxtemp && w1->y > wytemp)
						{
							wxtemp = w1->x;
							wytemp = w1->y;
						}
					}

					while (t <= 7)
					{
						t++;
						w->x -= t;
						w->y -= t;

						if (w->x == wxtemp || w->y == wytemp)
						{
							w->x += t;
							w->y += t;
							break;
						}

						if (w->x == bxtemp || w->y == bytemp)
						{
							for (auto& b : bPiece)
							{
								if (b->x == bxtemp && b->y == bytemp)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);
									check();
									w->x += t;
									w->y += t;

									col(b->y, b->x, py, px, b->piece);

									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						w->x += t;
						w->y += t;
						if (wking.check == 0)
						{
							return;
						}
					}

					//right up diagonal
					bxtemp = 8;
					bytemp = -1;
					wxtemp = 8;
					wytemp = -1;
					t = 0;

					for (auto& b : bPiece)
					{
						if (b->x > w->x && b->y < w->y && b->x - w->x == w->y - b->y && b->x < bxtemp && b->y > bytemp)
						{
							bxtemp = b->x;
							bytemp = b->y;
						}
					}

					for (auto& w1 : wPiece)
					{
						if (w1->x > w->x && w1->y < w->y && w1->x - w->x == w->y - w1->y && w1->x < bxtemp && w1->y > bytemp && w1->x < wxtemp && w1->y > wytemp)
						{
							wxtemp = w1->x;
							wytemp = w1->y;
						}
					}

					while (t <= 7)
					{
						t++;
						w->x += t;
						w->y -= t;

						if (w->x == wxtemp || w->y == wytemp)
						{
							w->x -= t;
							w->y += t;
							break;
						}

						if (w->x == bxtemp || w->y == bytemp)
						{
							for (auto& b : bPiece)
							{
								if (b->x == bxtemp && b->y == bytemp)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);
									check();
									w->x -= t;
									w->y += t;

									col(b->y, b->x, py, px, b->piece);

									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						w->x -= t;
						w->y += t;
						if (wking.check == 0)
						{
							return;
						}
					}
				}
				//queen
				if (w->piece == QUEEN)
				{
					//horizontal left movement
					for (auto& b : bPiece)
					{
						if (b->x < w->x && b->y == w->y && b->x > bxtemp)
						{
							//for multiple pieces in the same row select one and store its x value then compare 
							//its x location to other black pieces and see which one is closest to the rook being 
							//checked and say that bxtemp is that x value
							bxtemp = b->x;
						}
					}
					for (auto& w1 : wPiece)
					{
						if (w1->x < w->x && w1->y == w->y && w1->x > bxtemp && w1->x > wxtemp && w1->piece != KING)
						{
							wxtemp = w1->x;
						}
					}

					int t = 0;
					while (t <= 7)
					{
						t++;
						w->x -= t;
						if (w->x == wxtemp)
						{
							w->x += t;
							break;
						}
						if (w->x == bxtemp)
						{
							for (auto& b : bPiece)
							{
								if (b->x == bxtemp && b->y == w->y)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);
									check();
									w->x += t;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						w->x += t;
						if (wking.check == 0)
						{
							return;
						}
					}

					wxtemp = 8;
					bxtemp = 8;

					//horizontal right movement
					for (auto& b : bPiece)
					{
						if (b->x > w->x && b->y == w->y && b->x < bxtemp)
						{
							bxtemp = b->x;
						}
					}
					for (auto& w1 : wPiece)
					{
						if (w1->x > w->x && w1->y == w->y && w1->x < bxtemp && w1->x < wxtemp && w1->piece != KING)
						{
							wxtemp = w1->x;
						}
					}

					t = 0;
					while (t <= 7)
					{
						t++;
						w->x += t;
						if (w->x == wxtemp)
						{
							w->x -= t;
							break;
						}
						if (w->x == bxtemp)
						{
							for (auto& b : bPiece)
							{
								if (b->x == bxtemp && b->y == w->y)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);

									check();
									w->x -= t;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						w->x -= t;

						if (wking.check == 0)
						{
							return;
						}
					}

					//vertical up movement
					for (auto& b : bPiece)
					{
						if (b->y < w->y && b->x == w->x && b->y > bytemp)
						{
							bytemp = b->y;
						}
					}
					for (auto& w1 : wPiece)
					{
						if (w1->y < w->y && w1->x == w->x && w1->y > bytemp && w1->y > wytemp && w1->piece != KING)
						{
							wytemp = w1->y;
						}
					}

					t = 0;
					while (t <= 7)
					{
						t++;
						w->y -= t;
						if (w->y == wytemp)
						{
							w->y += t;
							break;
						}
						if (w->y == bytemp)
						{
							for (auto& b : bPiece)
							{
								if (b->y == bytemp && b->x == w->x)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);

									check();
									w->y += t;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						w->y += t;
						if (wking.check == 0)
						{
							return;
						}
					}

					bytemp = 8;
					wytemp = 8;

					//vertical down movement
					for (auto& b : bPiece)
					{
						if (b->y > w->y && b->x == w->x && b->y < bytemp)
						{
							bytemp = b->y;
						}
					}
					for (auto& w1 : wPiece)
					{
						if (w1->y > w->y && w1->x == w->x && w1->y < bytemp && w1->y < wytemp && w1->piece != KING)
						{
							wytemp = w1->y;
						}
					}

					t = 0;
					while (t <= 7)
					{
						t++;
						w->y += t;
						if (w->y == wytemp)
						{
							w->y -= t;
							break;
						}
						if (w->y == bytemp)
						{
							for (auto& b : bPiece)
							{
								if (b->y == bytemp && b->x == w->x)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);

									check();
									w->y -= t;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						w->y -= t;
						if (wking.check == 0)
						{
							return;
						}
					}


					//left down diagonal
					bxtemp = -1;
					bytemp = 8;
					wxtemp = -1;
					wytemp = 8;

					t = 0;

					for (auto& b : bPiece)
					{
						if (b->x < w->x && b->y > w->y && w->x - b->x == b->y - w->y && b->x > bxtemp && b->y < bytemp)
						{
							bxtemp = b->x;
							bytemp = b->y;
						}
					}

					for (auto& w1 : wPiece)
					{
						if (w1->x < w->x && w1->y > w->y && w->x - w1->x == w1->y - w->y && w1->x > bxtemp && w1->y < bytemp && w1->x > wxtemp && w1->y < wytemp)
						{
							wxtemp = w1->x;
							wytemp = w1->y;
						}
					}

					while (t <= 7)
					{
						t++;
						w->x -= t;
						w->y += t;

						if (w->x == wxtemp || w->y == wytemp)
						{
							w->x += t;
							w->y -= t;
							break;
						}

						if (w->x == bxtemp || w->y == bytemp)
						{
							for (auto& b : bPiece)
							{
								if (b->x == bxtemp && b->y == bytemp)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);
									check();
									w->x += t;
									w->y -= t;

									col(b->y, b->x, py, px, b->piece);

									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						w->x += t;
						w->y -= t;

						if (wking.check == 0)
						{
							return;
						}
					}

					//right down diagonal
					bxtemp = 8;
					bytemp = 8;
					wxtemp = 8;
					wytemp = 8;
					t = 0;

					for (auto& b : bPiece)
					{
						if (b->x > w->x && b->y > w->y && b->x - w->x == b->y - w->y && b->x < bxtemp && b->y < bytemp)
						{
							bxtemp = b->x;
							bytemp = b->y;
						}
					}

					for (auto& w1 : wPiece)
					{
						if (w1->x > w->x && w1->y > w->y && w1->x - w->x == w1->y - w->y && w1->x < bxtemp && w1->y < bytemp && w1->x < wxtemp && w1->y < wytemp)
						{
							wxtemp = w1->x;
							wytemp = w1->y;
						}
					}

					while (t <= 7)
					{
						t++;
						w->x += t;
						w->y += t;

						if (w->x == wxtemp || w->y == wytemp)
						{
							w->x -= t;
							w->y -= t;
							break;
						}

						if (w->x == bxtemp || w->y == bytemp)
						{
							for (auto& b : bPiece)
							{
								if (b->x == bxtemp && b->y == bytemp)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);
									check();
									w->x -= t;
									w->y -= t;

									col(b->y, b->x, py, px, b->piece);

									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						w->x -= t;
						w->y -= t;
						if (wking.check == 0)
						{
							return;
						}
					}

					//left up diagonal
					bxtemp = -1;
					bytemp = -1;
					wxtemp = -1;
					wytemp = -1;
					t = 0;

					for (auto& b : bPiece)
					{
						if (b->x < w->x && b->y < w->y && w->x - b->x == w->y - b->y && b->x > bxtemp && b->y > bytemp)
						{
							bxtemp = b->x;
							bytemp = b->y;
						}
					}

					for (auto& w1 : wPiece)
					{
						if (w1->x < w->x && w1->y < w->y && w->x - w1->x == w->y - w1->y && w1->x > bxtemp && w1->y > bytemp && w1->x > wxtemp && w1->y > wytemp)
						{
							wxtemp = w1->x;
							wytemp = w1->y;
						}
					}

					while (t <= 7)
					{
						t++;
						w->x -= t;
						w->y -= t;

						if (w->x == wxtemp || w->y == wytemp)
						{
							w->x += t;
							w->y += t;
							break;
						}

						if (w->x == bxtemp || w->y == bytemp)
						{
							for (auto& b : bPiece)
							{
								if (b->x == bxtemp && b->y == bytemp)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);
									check();
									w->x += t;
									w->y += t;

									col(b->y, b->x, py, px, b->piece);

									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						w->x += t;
						w->y += t;
						if (wking.check == 0)
						{
							return;
						}
					}

					//right up diagonal
					bxtemp = 8;
					bytemp = -1;
					wxtemp = 8;
					wytemp = -1;
					t = 0;

					for (auto& b : bPiece)
					{
						if (b->x > w->x && b->y < w->y && b->x - w->x == w->y - b->y && b->x < bxtemp && b->y > bytemp)
						{
							bxtemp = b->x;
							bytemp = b->y;
						}
					}

					for (auto& w1 : wPiece)
					{
						if (w1->x > w->x && w1->y < w->y && w1->x - w->x == w->y - w1->y && w1->x < bxtemp && w1->y > bytemp && w1->x < wxtemp && w1->y > wytemp)
						{
							wxtemp = w1->x;
							wytemp = w1->y;
						}
					}

					while (t <= 7)
					{
						t++;
						w->x += t;
						w->y -= t;

						if (w->x == wxtemp || w->y == wytemp)
						{
							w->x -= t;
							w->y += t;
							break;
						}

						if (w->x == bxtemp || w->y == bytemp)
						{
							for (auto& b : bPiece)
							{
								if (b->x == bxtemp && b->y == bytemp)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);
									check();
									w->x -= t;
									w->y += t;

									col(b->y, b->x, py, px, b->piece);

									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						w->x -= t;
						w->y += t;
						if (wking.check == 0)
						{
							return;
						}
					}
				}
				//king
				if (w->piece == KING)
				{
					//right
					switch (locAlg(w->x, w->y, 1, 0))
					{
					case 0:
						break;
					case 1:
						break;
					case 2:
						w->x += 1;
						if (king.x == w->x + 1 && (king.y == w->y || king.y == w->y + 1 || king.y == w->y - 1))
						{
							w->x -= 1;
							break;
						}

						//run death sequence
						for (auto& b : bPiece)
						{
							if (b->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);

									check();
									w->x -= 1;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										return;
									}
								}
							}
						}
						break;
					case 3:
						w->x += 1;
						if (king.x == w->x + 1 && (king.y == w->y || king.y == w->y + 1 || king.y == w->y - 1))
						{
							w->x -= 1;
							break;
						}
						check();
						w->x -= 1;

						if (wking.check == 0)
						{
							return;
						}
						break;
					}

					//left
					switch (locAlg(w->x, w->y, -1, 0))
					{
					case 0:
						break;
					case 1:
						break;
					case 2:
						w->x -= 1;
						if (king.x == w->x - 1 && (king.y == w->y || king.y == w->y + 1 || king.y == w->y - 1))
						{
							w->x += 1;
							break;
						}

						//run death sequence
						for (auto& b : bPiece)
						{
							if (b->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);

									check();
									w->x += 1;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										return;
									}
								}
							}
						}
						break;
					case 3:
						w->x -= 1;
						if (king.x == w->x - 1 && (king.y == w->y || king.y == w->y + 1 || king.y == w->y - 1))
						{
							w->x += 1;
							break;
						}
						check();
						w->x += 1;

						if (wking.check == 0)
						{
							return;
						}
						break;
					}

					//up
					switch (locAlg(w->x, w->y, 0, -1))
					{
					case 0:
						break;
					case 1:
						break;
					case 2:
						w->y -= 1;
						if (king.y == w->y - 1 && (king.x == w->x || king.x == w->x + 1 || king.x == w->x - 1))
						{
							w->y += 1;
							break;
						}

						//run death sequence
						for (auto& b : bPiece)
						{
							if (b->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);

									check();
									w->y += 1;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										return;
									}
								}
							}
						}
						break;
					case 3:
						w->y -= 1;
						if (king.y == w->y - 1 && (king.x == w->x || king.x == w->x + 1 || king.x == w->x - 1))
						{
							w->y += 1;
							break;
						}
						check();
						w->y += 1;

						if (wking.check == 0)
						{
							return;
						}
						break;
					}

					//down
					switch (locAlg(w->x, w->y, 0, 1))
					{
					case 0:
						break;
					case 1:
						break;
					case 2:
						w->y += 1;
						if (king.y == w->y + 1 && (king.x == w->x || king.x == w->x + 1 || king.x == w->x - 1))
						{
							w->y -= 1;
							break;
						}

						//run death sequence
						for (auto& b : bPiece)
						{
							if (b->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);

									check();
									w->y -= 1;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										return;
									}
								}
							}
						}
						break;
					case 3:
						w->y += 1;
						if (king.y == w->y + 1 && (king.x == w->x || king.x == w->x + 1 || king.x == w->x - 1))
						{
							w->y -= 1;
							break;
						}
						check();
						w->y -= 1;

						if (wking.check == 0)
						{
							return;
						}
						break;
					}

					//right up
					switch (locAlg(w->x, w->y, 1, -1))
					{
					case 0:
						break;
					case 1:
						break;
					case 2:
						w->x += 1;
						w->y -= 1;
						if (king.y == w->y - 1 && king.x == w->x + 1)
						{
							w->x -= 1;
							w->y += 1;
							break;
						}

						//run death sequence
						for (auto& b : bPiece)
						{
							if (b->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);

									check();
									w->x -= 1;
									w->y += 1;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										return;
									}
								}
							}
						}
						break;
					case 3:
						w->x += 1;
						w->y -= 1;
						if (king.y == w->y - 1 && king.x == w->x + 1)
						{
							w->x -= 1;
							w->y += 1;
							break;
						}
						check();
						w->x -= 1;
						w->y += 1;

						if (wking.check == 0)
						{
							return;
						}
						break;
					}

					//left up
					switch (locAlg(w->x, w->y, -1, -1))
					{
					case 0:
						break;
					case 1:
						break;
					case 2:
						w->x -= 1;
						w->y -= 1;
						if (king.y == w->y - 1 && king.x == w->x - 1)
						{
							w->x += 1;
							w->y += 1;
							break;
						}

						//run death sequence
						for (auto& b : bPiece)
						{
							if (b->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);

									check();
									w->x += 1;
									w->y += 1;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										return;
									}
								}
							}
						}
						break;
					case 3:
						w->x -= 1;
						w->y -= 1;
						if (king.y == w->y - 1 && king.x == w->x - 1)
						{
							w->x += 1;
							w->y += 1;
							break;
						}
						check();
						w->x += 1;
						w->y += 1;

						if (wking.check == 0)
						{
							return;
						}
						break;
					}

					//right down
					switch (locAlg(w->x, w->y, 1, 1))
					{
					case 0:
						break;
					case 1:
						break;
					case 2:
						w->x += 1;
						w->y += 1;
						if (king.y == w->y + 1 && king.x == w->x + 1)
						{
							w->x -= 1;
							w->y -= 1;
							break;
						}

						//run death sequence
						for (auto& b : bPiece)
						{
							if (b->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);

									check();
									w->x -= 1;
									w->y -= 1;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										return;
									}
								}
							}
						}
						break;
					case 3:
						w->x += 1;
						w->y += 1;
						if (king.y == w->y + 1 && king.x == w->x + 1)
						{
							w->x -= 1;
							w->y -= 1;
							break;
						}
						check();
						w->x -= 1;
						w->y -= 1;

						if (wking.check == 0)
						{
							return;
						}
						break;
					}

					//left down
					switch (locAlg(w->x, w->y, -1, 1))
					{
					case 0:
						break;
					case 1:
						break;
					case 2:
						w->x -= 1;
						w->y += 1;
						if (king.y == w->y + 1 && king.x == w->x - 1)
						{
							w->x += 1;
							w->y -= 1;
							break;
						}

						//run death sequence
						for (auto& b : bPiece)
						{
							if (b->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									bDead++;
									px = b->x;
									py = b->y;
									b->death = 1;
									b->dead(bDead);

									check();
									w->x += 1;
									w->y -= 1;

									col(b->y, b->x, py, px, b->piece);
									bDead--;
									b->x = px;
									b->y = py;
									b->death = 0;

									if (wking.check == 0)
									{
										return;
									}
								}
							}
						}
						break;
					case 3:
						w->x -= 1;
						w->y += 1;
						if (king.y == w->y + 1 && king.x == w->x - 1)
						{
							w->x += 1;
							w->y -= 1;
							break;
						}
						check();
						w->x += 1;
						w->y -= 1;

						if (wking.check == 0)
						{
							return;
						}
						break;
					}
				}
			}
		}
		//if this runs it means stalemate, white cant move
		win = 3;
	}

	//if black is in check
	if (king.check == 0)
	{
		for (auto& b : bPiece)
		{
			if (b->death == 0)
			{
				valid = 1;
				bxtemp = -1;
				wxtemp = -1;
				bytemp = -1;
				wytemp = -1;
				px = 0;
				py = 0;

				//pawn
				if (b->piece == PAWN)
				{
					//piece in front
					for (auto& b1 : bPiece)
					{
						if (b->x == b1->x && b1->y == b->y - 1)
						{
							valid = 0;
							break;
						}
					}
					for (auto& w : wPiece)
					{
						if (b->x == w->x && w->y == b->y - 1)
						{
							valid = 0;
							break;
						}
					}

					if (valid == 1)
					{
						b->y -= 1;
						check();
						b->y += 1;
						if (king.check == 0)
						{
							return;
						}
					}

					if (b->movesMade == 0)
					{
						for (auto& b1 : bPiece)
						{
							if (b->y - 2 == b1->y && b->x == b1->x)
							{
								valid = 0;
								break;
							}
						}
						for (auto& w : wPiece)
						{
							if (b->y - 2 == w->y && b->x == w->x)
							{
								valid = 0;
								break;
							}
						}
					}
					else
					{
						valid = 0;
					}

					if (valid == 1)
					{
						b->y -= 2;
						check();
						b->y += 2;
						if (king.check == 0)
						{
							return;
						}
					}

					//killing piece
					for (auto& w : wPiece)
					{
						if (w->piece != KING)
						{
							if (w->x == b->x + 1 && w->y == b->y - 1)
							{
								wDead++;
								px = w->x;
								py = w->y;
								w->death = 1;
								w->dead(wDead);

								b->x += 1;
								b->y -= 1;
								check();
								b->x -= 1;
								b->y += 1;

								col(w->y, w->x, py, px, w->piece + 6);
								wDead--;
								w->x = px;
								w->y = py;
								w->death = 0;

								if (king.check == 0)
								{
									return;
								}
							}
							if (w->x == b->x - 1 && w->y == b->y - 1)
							{
								wDead++;
								px = w->x;
								py = w->y;
								w->death = 1;
								w->dead(wDead);

								b->x -= 1;
								b->y -= 1;
								check();
								b->x += 1;
								b->y += 1;

								col(w->y, w->x, py, px, w->piece + 6);
								wDead--;
								w->x = px;
								w->y = py;
								w->death = 0;

								if (king.check == 0)
								{
									return;
								}
							}
						}
						if (w->enPassantCnt == 1)
						{
							if (w->x == b->x + 1 && w->y == b->y)
							{
								wDead++;
								px = w->x;
								py = w->y;
								w->death = 1;
								w->dead(wDead);

								b->x += 1;
								b->y -= 1;
								check();
								b->x -= 1;
								b->y += 1;

								col(w->y, w->x, py, px, w->piece + 6);
								wDead--;
								w->x = px;
								w->y = py;
								w->death = 0;

								if (king.check == 0)
								{
									return;
								}
							}
							if (w->x == b->x - 1 && w->y == b->y)
							{
								wDead++;
								px = w->x;
								py = w->y;
								w->death = 1;
								w->dead(wDead);

								b->x -= 1;
								b->y -= 1;
								check();
								b->x += 1;
								b->y += 1;

								col(w->y, w->x, py, px, w->piece + 6);
								wDead--;
								w->x = px;
								w->y = py;
								w->death = 0;

								if (king.check == 0)
								{
									return;
								}
							}
						}
					}
				}
				//rook
				if (b->piece == ROOK)
				{
					//horizontal left movement
					for (auto& w : wPiece)
					{
						if (w->x < b->x && w->y == b->y && w->x > wxtemp)
						{
							//for multiple pieces in the same row select one and store its x value then compare 
							//its x location to other black pieces and see which one is closest to the rook being 
							//checked and say that bxtemp is that x value
							wxtemp = w->x;
						}
					}
					for (auto& b1 : bPiece)
					{
						if (b1->x < b->x && b1->y == b->y && b1->x > wxtemp && b1->x > bxtemp && b1->piece != KING)
						{
							bxtemp = b1->x;
						}
					}

					int t = 0;
					while (t <= 7)
					{
						t++;
						b->x -= t;
						if (b->x == bxtemp)
						{
							b->x += t;
							break;
						}
						if (b->x == wxtemp)
						{
							for (auto& w : wPiece)
							{
								if (w->x == wxtemp && w->y == b->y)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);
									check();
									b->x += t;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						b->x += t;
						if (king.check == 0)
						{
							return;
						}
					}

					wxtemp = 8;
					bxtemp = 8;

					//horizontal right movement
					for (auto& w : wPiece)
					{
						if (w->x > b->x && w->y == b->y && w->x < wxtemp)
						{
							wxtemp = w->x;
						}
					}
					for (auto& b1 : bPiece)
					{
						if (b1->x > b->x && b1->y == b->y && b1->x < wxtemp && b1->x < bxtemp && b1->piece != KING)
						{
							bxtemp = b1->x;
						}
					}

					t = 0;
					while (t <= 7)
					{
						t++;
						b->x += t;
						if (b->x == bxtemp)
						{
							b->x -= t;
							break;
						}
						if (b->x == wxtemp)
						{
							for (auto& w : wPiece)
							{
								if (w->x == wxtemp && w->y == b->y)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);

									check();
									b->x -= t;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						b->x -= t;

						if (king.check == 0)
						{
							return;
						}
					}

					//vertical up movement
					for (auto& w : wPiece)
					{
						if (w->y < b->y && w->x == b->x && w->y > wytemp)
						{
							wytemp = w->y;
						}
					}
					for (auto& b1 : bPiece)
					{
						if (b1->y < b->y && b1->x == b->x && b1->y > wytemp && b1->y > bytemp && b1->piece != KING)
						{
							bytemp = b1->y;
						}
					}

					t = 0;
					while (t <= 7)
					{
						t++;
						b->y -= t;
						if (b->y == bytemp)
						{
							b->y += t;
							break;
						}
						if (b->y == wytemp)
						{
							for (auto& w : wPiece)
							{
								if (w->y == wytemp && w->x == b->x)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);

									check();
									b->y += t;

									col(w->y, w->x, py, px, w->piece + 6);
									bDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						b->y += t;
						if (king.check == 0)
						{
							return;
						}
					}

					bytemp = 8;
					wytemp = 8;

					//vertical down movement
					for (auto& w : wPiece)
					{
						if (w->y > b->y && w->x == b->x && w->y < wytemp)
						{
							wytemp = w->y;
						}
					}
					for (auto& b1 : bPiece)
					{
						if (b1->y > b->y && b1->x == b->x && b1->y < wytemp && b1->y < bytemp && b1->piece != KING)
						{
							bytemp = b1->y;
						}
					}

					t = 0;
					while (t <= 7)
					{
						t++;
						b->y += t;
						if (b->y == bytemp)
						{
							b->y -= t;
							break;
						}
						if (b->y == wytemp)
						{
							for (auto& w : wPiece)
							{
								if (w->y == wytemp && w->x == b->x)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);

									check();
									b->y -= t;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						b->y -= t;
						if (king.check == 0)
						{
							return;
						}
					}
				}
				//horse
				if (b->piece == HORSE)
				{
					switch (locAlg(b->x, b->y, -2, -1))
					{
					case 0:
						break;
					case 1:
						b->x -= 2;
						b->y -= 1;
						//run death sequence
						for (auto& w : wPiece)
						{
							if (w->piece != KING)
							{
								if (b->x == w->x && w->y == b->y)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);

									check();
									b->x += 2;
									b->y += 1;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										return;
									}
								}
							}
						}
						break;
					case 2:
						break;
					case 3:
						b->x -= 2;
						b->y -= 1;
						check();
						b->x += 2;
						b->y += 1;

						if (king.check == 0)
						{
							return;
						}
						break;
					}

					switch (locAlg(b->x, b->y, -2, 1))
					{
					case 0:
						break;
					case 1:
						b->x -= 2;
						b->y += 1;
						//run death sequence
						for (auto& w : wPiece)
						{
							if (w->piece != KING)
							{
								if (b->x == w->x && w->y == b->y)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);

									check();
									b->x += 2;
									b->y -= 1;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										return;
									}
								}
							}
						}
						break;
					case 2:
						break;
					case 3:
						b->x -= 2;
						b->y += 1;
						check();
						b->x += 2;
						b->y -= 1;

						if (king.check == 0)
						{
							return;
						}
						break;
					}

					switch (locAlg(b->x, b->y, 2, -1))
					{
					case 0:
						break;
					case 1:
						b->x += 2;
						b->y -= 1;
						//run death sequence
						for (auto& w : wPiece)
						{
							if (w->piece != KING)
							{
								if (b->x == w->x && w->y == b->y)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);

									check();
									b->x -= 2;
									b->y += 1;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										return;
									}
								}
							}
						}
						break;
					case 2:
						break;
					case 3:
						b->x += 2;
						b->y -= 1;
						check();
						b->x -= 2;
						b->y += 1;

						if (king.check == 0)
						{
							return;
						}
						break;
					}

					switch (locAlg(b->x, b->y, 2, 1))
					{
					case 0:
						break;
					case 1:
						b->x += 2;
						b->y += 1;
						//run death sequence
						for (auto& w : wPiece)
						{
							if (w->piece != KING)
							{
								if (b->x == w->x && w->y == b->y)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);

									check();
									b->x -= 2;
									b->y -= 1;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										return;
									}
								}
							}
						}
						break;
					case 2:
						break;
					case 3:
						b->x += 2;
						b->y += 1;
						check();
						b->x -= 2;
						b->y -= 1;

						if (king.check == 0)
						{
							return;
						}
						break;
					}

					switch (locAlg(b->x, b->y, -1, -2))
					{
					case 0:
						break;
					case 1:
						b->x -= 1;
						b->y -= 2;
						//run death sequence
						for (auto& w : wPiece)
						{
							if (w->piece != KING)
							{
								if (b->x == w->x && w->y == b->y)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);

									check();
									b->x += 1;
									b->y += 2;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										return;
									}
								}
							}
						}
						break;
					case 2:
						break;
					case 3:
						b->x -= 1;
						b->y -= 2;
						check();
						b->x += 1;
						b->y += 2;

						if (king.check == 0)
						{
							return;
						}
						break;
					}

					switch (locAlg(b->x, b->y, -1, 2))
					{
					case 0:
						break;
					case 1:
						b->x -= 1;
						b->y += 2;
						//run death sequence
						for (auto& w : wPiece)
						{
							if (w->piece != KING)
							{
								if (b->x == w->x && w->y == b->y)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);

									check();
									b->x += 1;
									b->y -= 2;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										return;
									}
								}
							}
						}
						break;
					case 2:
						break;
					case 3:
						b->x -= 1;
						b->y += 2;
						check();
						b->x += 1;
						b->y -= 2;

						if (king.check == 0)
						{
							return;
						}
						break;
					}

					switch (locAlg(b->x, b->y, 1, -2))
					{
					case 0:
						break;
					case 1:
						b->x += 1;
						b->y -= 2;
						//run death sequence
						for (auto& w : wPiece)
						{
							if (w->piece != KING)
							{
								if (b->x == w->x && w->y == b->y)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);

									check();
									b->x -= 1;
									b->y += 2;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										return;
									}
								}
							}
						}
						break;
					case 2:
						break;
					case 3:
						b->x += 1;
						b->y -= 2;
						check();
						b->x += 1;
						b->y -= 2;

						if (king.check == 0)
						{
							return;
						}
						break;
					}

					switch (locAlg(b->x, b->y, 1, 2))
					{
					case 0:
						break;
					case 1:
						b->x += 1;
						b->y += 2;
						//run death sequence
						for (auto& w : wPiece)
						{
							if (w->piece != KING)
							{
								if (b->x == w->x && w->y == b->y)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);

									check();
									b->x -= 1;
									b->y -= 2;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										return;
									}
								}
							}
						}
						break;
					case 2:
						break;
					case 3:
						b->x += 1;
						b->y += 2;
						check();
						b->x -= 1;
						b->y -= 2;

						if (king.check == 0)
						{
							return;
						}
						break;
					}
				}
				//bishop
				if (b->piece == BISHOP)
				{
					//left down diagonal
					wytemp = 8;
					bytemp = 8;
					t = 0;

					for (auto& w : wPiece)
					{
						if (w->x < b->x && w->y > b->y && b->x - w->x == w->y - b->y && w->x > wxtemp && w->y < wytemp)
						{
							wxtemp = w->x;
							wytemp = w->y;
						}
					}
					for (auto& b1 : wPiece)
					{
						if (b1->x < b->x && b1->y > b->y && b->x - b1->x == b1->y - b->y && b1->x > wxtemp && b1->y < wytemp && b1->x > bxtemp && b1->y < bytemp)
						{
							bxtemp = b1->x;
							bytemp = b1->y;
						}
					}

					while (t <= 7)
					{
						t++;
						b->x -= t;
						b->y += t;

						if (b->x == bxtemp || b->y == bytemp)
						{
							b->x += t;
							b->y -= t;
							break;
						}

						if (b->x == wxtemp || b->y == wytemp)
						{
							for (auto& w : wPiece)
							{
								if (w->x == wxtemp && w->y == wytemp)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);
									check();
									b->x += t;
									b->y -= t;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						b->x += t;
						b->y -= t;

						if (king.check == 0)
						{
							return;
						}
					}

					//right down diagonal
					bxtemp = 8;
					bytemp = 8;
					wxtemp = 8;
					wytemp = 8;
					t = 0;

					for (auto& w : wPiece)
					{
						if (w->x > b->x && w->y > b->y && w->x - b->x == w->y - b->y && w->x < wxtemp && w->y < wytemp)
						{
							wxtemp = w->x;
							wytemp = w->y;
						}
					}
					for (auto& b1 : bPiece)
					{
						if (b1->x > b->x && b1->y > b->y && b1->x - b->x == b1->y - b->y && b1->x < wxtemp && b1->y < wytemp && b1->x < bxtemp && b1->y < bytemp)
						{
							bxtemp = b1->x;
							bytemp = b1->y;
						}
					}

					while (t <= 7)
					{
						t++;
						b->x += t;
						b->y += t;

						if (b->x == bxtemp || b->y == bytemp)
						{
							b->x -= t;
							b->y -= t;
							break;
						}

						if (b->x == wxtemp || b->y == wytemp)
						{
							for (auto& w : wPiece)
							{
								if (w->x == wxtemp && w->y == wytemp)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);
									check();
									b->x -= t;
									b->y -= t;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						b->x -= t;
						b->y -= t;
						if (king.check == 0)
						{
							return;
						}
					}

					//left up diagonal
					bxtemp = -1;
					bytemp = -1;
					wxtemp = -1;
					wytemp = -1;
					t = 0;

					for (auto& w : wPiece)
					{
						if (w->x < b->x && w->y < b->y && b->x - w->x == b->y - w->y && w->x > wxtemp && w->y > wytemp)
						{
							wxtemp = w->x;
							wytemp = w->y;
						}
					}
					for (auto& b1 : bPiece)
					{
						if (b1->x < b->x && b1->y < b->y && b->x - b1->x == b->y - b1->y && b1->x > wxtemp && b1->y > wytemp && b1->x > bxtemp && b1->y > bytemp)
						{
							bxtemp = b1->x;
							bytemp = b1->y;
						}
					}

					while (t <= 7)
					{
						t++;
						b->x -= t;
						b->y -= t;

						if (b->x == bxtemp || b->y == bytemp)
						{
							b->x += t;
							b->y += t;
							break;
						}

						if (b->x == wxtemp || b->y == wytemp)
						{
							for (auto& w : wPiece)
							{
								if (w->x == wxtemp && w->y == wytemp)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);
									check();
									b->x += t;
									b->y += t;

									col(w->y, w->x, py, px, w->piece + 6);

									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						b->x += t;
						b->y += t;
						if (king.check == 0)
						{
							return;
						}
					}

					//right up diagonal
					bxtemp = 8;
					bytemp = -1;
					wxtemp = 8;
					wytemp = -1;
					t = 0;

					for (auto& w : wPiece)
					{
						if (w->x > b->x && w->y < b->y && w->x - b->x == b->y - w->y && w->x < wxtemp && w->y > wytemp)
						{
							wxtemp = w->x;
							wytemp = w->y;
						}
					}
					for (auto& b1 : bPiece)
					{
						if (b1->x > b->x && b1->y < b->y && b1->x - b->x == b->y - b1->y && b1->x < wxtemp && b1->y > wytemp && b1->x < bxtemp && b1->y > bytemp)
						{
							bxtemp = b1->x;
							bytemp = b1->y;
						}
					}

					while (t <= 7)
					{
						t++;
						b->x += t;
						b->y -= t;

						if (b->x == bxtemp || b->y == bytemp)
						{
							b->x -= t;
							b->y += t;
							break;
						}

						if (b->x == wxtemp || b->y == wytemp)
						{
							for (auto& w : wPiece)
							{
								if (w->x == wxtemp && w->y == wytemp)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);
									check();
									b->x -= t;
									b->y += t;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						b->x -= t;
						b->y += t;
						if (king.check == 0)
						{
							return;
						}
					}
				}
				//queen
				if (b->piece == QUEEN)
				{
					//horizontal left movement
					for (auto& w : wPiece)
					{
						if (w->x < b->x && w->y == b->y && w->x > wxtemp)
						{
							//for multiple pieces in the same row select one and store its x value then compare 
							//its x location to other black pieces and see which one is closest to the rook being 
							//checked and say that bxtemp is that x value
							wxtemp = w->x;
						}
					}
					for (auto& b1 : bPiece)
					{
						if (b1->x < b->x && b1->y == b->y && b1->x > wxtemp && b1->x > bxtemp && b1->piece != KING)
						{
							bxtemp = b1->x;
						}
					}

					int t = 0;
					while (t <= 7)
					{
						t++;
						b->x -= t;
						if (b->x == bxtemp)
						{
							b->x += t;
							break;
						}
						if (b->x == wxtemp)
						{
							for (auto& w : wPiece)
							{
								if (w->x == wxtemp && w->y == b->y)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);
									check();
									b->x += t;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						b->x += t;
						if (king.check == 0)
						{
							return;
						}
					}

					wxtemp = 8;
					bxtemp = 8;

					//horizontal right movement
					for (auto& w : wPiece)
					{
						if (w->x > b->x && w->y == b->y && w->x < wxtemp)
						{
							wxtemp = w->x;
						}
					}
					for (auto& b1 : bPiece)
					{
						if (b1->x > b->x && b1->y == b->y && b1->x < wxtemp && b1->x < bxtemp && b1->piece != KING)
						{
							bxtemp = b1->x;
						}
					}

					t = 0;
					while (t <= 7)
					{
						t++;
						b->x += t;
						if (b->x == bxtemp)
						{
							b->x -= t;
							break;
						}
						if (b->x == wxtemp)
						{
							for (auto& w : wPiece)
							{
								if (w->x == wxtemp && w->y == b->y)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);

									check();
									b->x -= t;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						b->x -= t;

						if (king.check == 0)
						{
							return;
						}
					}

					//vertical up movement
					for (auto& w : wPiece)
					{
						if (w->y < b->y && w->x == b->x && w->y > wytemp)
						{
							wytemp = w->y;
						}
					}
					for (auto& b1 : bPiece)
					{
						if (b1->y < b->y && b1->x == b->x && b1->y > wytemp && b1->y > bytemp && b1->piece != KING)
						{
							bytemp = b1->y;
						}
					}

					t = 0;
					while (t <= 7)
					{
						t++;
						b->y -= t;
						if (b->y == bytemp)
						{
							b->y += t;
							break;
						}
						if (b->y == wytemp)
						{
							for (auto& w : wPiece)
							{
								if (w->y == wytemp && w->x == b->x)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);

									check();
									b->y += t;

									col(w->y, w->x, py, px, w->piece + 6);
									bDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						b->y += t;
						if (king.check == 0)
						{
							return;
						}
					}

					bytemp = 8;
					wytemp = 8;

					//vertical down movement
					for (auto& w : wPiece)
					{
						if (w->y > b->y && w->x == b->x && w->y < wytemp)
						{
							wytemp = w->y;
						}
					}
					for (auto& b1 : bPiece)
					{
						if (b1->y > b->y && b1->x == b->x && b1->y < wytemp && b1->y < bytemp && b1->piece != KING)
						{
							bytemp = b1->y;
						}
					}

					t = 0;
					while (t <= 7)
					{
						t++;
						b->y += t;
						if (b->y == bytemp)
						{
							b->y -= t;
							break;
						}
						if (b->y == wytemp)
						{
							for (auto& w : wPiece)
							{
								if (w->y == wytemp && w->x == b->x)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);

									check();
									b->y -= t;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						b->y -= t;
						if (king.check == 0)
						{
							return;
						}
					}

					//left down diagonal
					wytemp = 8;
					bytemp = 8;
					t = 0;

					for (auto& w : wPiece)
					{
						if (w->x < b->x && w->y > b->y && b->x - w->x == w->y - b->y && w->x > wxtemp && w->y < wytemp)
						{
							wxtemp = w->x;
							wytemp = w->y;
						}
					}
					for (auto& b1 : wPiece)
					{
						if (b1->x < b->x && b1->y > b->y && b->x - b1->x == b1->y - b->y && b1->x > wxtemp && b1->y < wytemp && b1->x > bxtemp && b1->y < bytemp)
						{
							bxtemp = b1->x;
							bytemp = b1->y;
						}
					}

					while (t <= 7)
					{
						t++;
						b->x -= t;
						b->y += t;

						if (b->x == bxtemp || b->y == bytemp)
						{
							b->x += t;
							b->y -= t;
							break;
						}

						if (b->x == wxtemp || b->y == wytemp)
						{
							for (auto& w : wPiece)
							{
								if (w->x == wxtemp && w->y == wytemp)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);
									check();
									b->x += t;
									b->y -= t;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						b->x += t;
						b->y -= t;

						if (king.check == 0)
						{
							return;
						}
					}

					//right down diagonal
					bxtemp = 8;
					bytemp = 8;
					wxtemp = 8;
					wytemp = 8;
					t = 0;

					for (auto& w : wPiece)
					{
						if (w->x > b->x && w->y > b->y && w->x - b->x == w->y - b->y && w->x < wxtemp && w->y < wytemp)
						{
							wxtemp = w->x;
							wytemp = w->y;
						}
					}
					for (auto& b1 : bPiece)
					{
						if (b1->x > b->x && b1->y > b->y && b1->x - b->x == b1->y - b->y && b1->x < wxtemp && b1->y < wytemp && b1->x < bxtemp && b1->y < bytemp)
						{
							bxtemp = b1->x;
							bytemp = b1->y;
						}
					}

					while (t <= 7)
					{
						t++;
						b->x += t;
						b->y += t;

						if (b->x == bxtemp || b->y == bytemp)
						{
							b->x -= t;
							b->y -= t;
							break;
						}

						if (b->x == wxtemp || b->y == wytemp)
						{
							for (auto& w : wPiece)
							{
								if (w->x == wxtemp && w->y == wytemp)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);
									check();
									b->x -= t;
									b->y -= t;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						b->x -= t;
						b->y -= t;
						if (king.check == 0)
						{
							return;
						}
					}

					//left up diagonal
					bxtemp = -1;
					bytemp = -1;
					wxtemp = -1;
					wytemp = -1;
					t = 0;

					for (auto& w : wPiece)
					{
						if (w->x < b->x && w->y < b->y && b->x - w->x == b->y - w->y && w->x > wxtemp && w->y > wytemp)
						{
							wxtemp = w->x;
							wytemp = w->y;
						}
					}
					for (auto& b1 : bPiece)
					{
						if (b1->x < b->x && b1->y < b->y && b->x - b1->x == b->y - b1->y && b1->x > wxtemp && b1->y > wytemp && b1->x > bxtemp && b1->y > bytemp)
						{
							bxtemp = b1->x;
							bytemp = b1->y;
						}
					}

					while (t <= 7)
					{
						t++;
						b->x -= t;
						b->y -= t;

						if (b->x == bxtemp || b->y == bytemp)
						{
							b->x += t;
							b->y += t;
							break;
						}

						if (b->x == wxtemp || b->y == wytemp)
						{
							for (auto& w : wPiece)
							{
								if (w->x == wxtemp && w->y == wytemp)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);
									check();
									b->x += t;
									b->y += t;

									col(w->y, w->x, py, px, w->piece + 6);

									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						b->x += t;
						b->y += t;
						if (king.check == 0)
						{
							return;
						}
					}

					//right up diagonal
					bxtemp = 8;
					bytemp = -1;
					wxtemp = 8;
					wytemp = -1;
					t = 0;

					for (auto& w : wPiece)
					{
						if (w->x > b->x && w->y < b->y && w->x - b->x == b->y - w->y && w->x < wxtemp && w->y > wytemp)
						{
							wxtemp = w->x;
							wytemp = w->y;
						}
					}
					for (auto& b1 : bPiece)
					{
						if (b1->x > b->x && b1->y < b->y && b1->x - b->x == b->y - b1->y && b1->x < wxtemp && b1->y > wytemp && b1->x < bxtemp && b1->y > bytemp)
						{
							bxtemp = b1->x;
							bytemp = b1->y;
						}
					}

					while (t <= 7)
					{
						t++;
						b->x += t;
						b->y -= t;

						if (b->x == bxtemp || b->y == bytemp)
						{
							b->x -= t;
							b->y += t;
							break;
						}

						if (b->x == wxtemp || b->y == wytemp)
						{
							for (auto& w : wPiece)
							{
								if (w->x == wxtemp && w->y == wytemp)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);
									check();
									b->x -= t;
									b->y += t;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										return;
									}
									t = 9;
									break;
								}
							}
						}
						if (t > 7)
						{
							break;
						}
						check();
						b->x -= t;
						b->y += t;
						if (king.check == 0)
						{
							return;
						}
					}
				}
				//king
				if (b->piece == KING)
				{
					//right
					switch (locAlg(b->x, b->y, 1, 0))
					{
					case 0:
						break;
					case 1:
						b->x += 1;
						if (wking.x == b->x + 1 && (wking.y == b->y || wking.y == b->y + 1 || wking.y == b->y - 1))
						{
							b->x -= 1;
							break;
						}

						for (auto& w : wPiece)
						{
							if (w->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);

									check();
									b->x -= 1;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										return;
									}
								}
							}
						}
						break;
					case 2:
						break;
					case 3:
						b->x += 1;
						if (wking.x == b->x + 1 && (wking.y == b->y || wking.y == b->y + 1 || wking.y == b->y - 1))
						{
							b->x -= 1;
							break;
						}
						check();
						b->x -= 1;

						if (king.check == 0)
						{
							return;
						}
						break;
					}

					//left
					switch (locAlg(b->x, b->y, -1, 0))
					{
					case 0:
						break;
					case 1:
						b->x -= 1;
						if (wking.x == b->x - 1 && (wking.y == b->y || wking.y == b->y + 1 || wking.y == b->y - 1))
						{
							b->x += 1;
							break;
						}

						for (auto& w : wPiece)
						{
							if (w->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);

									check();
									b->x += 1;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										return;
									}
								}
							}
						}
						break;
					case 2:
						break;
					case 3:
						b->x -= 1;
						if (wking.x == b->x - 1 && (wking.y == b->y || wking.y == b->y + 1 || wking.y == b->y - 1))
						{
							b->x += 1;
							break;
						}
						check();
						b->x += 1;

						if (king.check == 0)
						{
							return;
						}
						break;
					}

					//up
					switch (locAlg(b->x, b->y, 0, -1))
					{
					case 0:
						break;
					case 1:
						b->y -= 1;
						if (wking.y == b->y - 1 && (wking.x == b->x || wking.x == b->x + 1 || wking.x == b->x - 1))
						{
							b->y += 1;
							break;
						}

						for (auto& w : wPiece)
						{
							if (w->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);

									check();
									b->y += 1;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										return;
									}
								}
							}
						}
						break;
					case 2:
						break;
					case 3:
						b->y -= 1;
						if (wking.y == b->y - 1 && (wking.x == b->x || wking.x == b->x + 1 || wking.x == b->x - 1))
						{
							b->y += 1;
							break;
						}
						check();
						b->y += 1;

						if (king.check == 0)
						{
							return;
						}
						break;
					}

					//down
					switch (locAlg(b->x, b->y, 0, 1))
					{
					case 0:
						break;
					case 1:
						b->y += 1;
						if (wking.y == b->y + 1 && (wking.x == b->x || wking.x == b->x + 1 || wking.x == b->x - 1))
						{
							b->y -= 1;
							break;
						}

						for (auto& w : wPiece)
						{
							if (w->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);

									check();
									b->y -= 1;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										return;
									}
								}
							}
						}
						break;
					case 2:
						break;
					case 3:
						b->y += 1;
						if (wking.y == b->y + 1 && (wking.x == b->x || wking.x == b->x + 1 || wking.x == b->x - 1))
						{
							b->y -= 1;
							break;
						}
						check();
						b->y -= 1;

						if (king.check == 0)
						{
							return;
						}
						break;
					}

					//right up
					switch (locAlg(b->x, b->y, 1, -1))
					{
					case 0:
						break;
					case 1:
						b->x += 1;
						b->y -= 1;
						if (wking.y == b->y - 1 && wking.x == b->x + 1)
						{
							b->x -= 1;
							b->y += 1;
							break;
						}

						for (auto& w : wPiece)
						{
							if (w->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);

									check();
									b->x -= 1;
									b->y += 1;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										return;
									}
								}
							}
						}
						break;
					case 2:
						break;
					case 3:
						b->x += 1;
						b->y -= 1;
						if (wking.y == b->y - 1 && wking.x == b->x + 1)
						{
							b->x -= 1;
							b->y += 1;
							break;
						}
						check();
						b->x -= 1;
						b->y += 1;

						if (king.check == 0)
						{
							return;
						}
						break;
					}

					//left up
					switch (locAlg(b->x, b->y, -1, -1))
					{
					case 0:
						break;
					case 1:
						b->x -= 1;
						b->y -= 1;
						if (wking.y == b->y - 1 && wking.x == b->x - 1)
						{
							b->x += 1;
							b->y += 1;
							break;
						}

						for (auto& w : wPiece)
						{
							if (w->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);

									check();
									b->x += 1;
									b->y += 1;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										return;
									}
								}
							}
						}
						break;
					case 2:
						break;
					case 3:
						b->x -= 1;
						b->y -= 1;
						if (wking.y == b->y - 1 && wking.x == b->x - 1)
						{
							b->x += 1;
							b->y += 1;
							break;
						}
						check();
						b->x += 1;
						b->y += 1;

						if (king.check == 0)
						{
							return;
						}
						break;
					}

					//right down
					switch (locAlg(b->x, b->y, 1, 1))
					{
					case 0:
						break;
					case 1:
						b->x += 1;
						b->y += 1;
						if (wking.y == b->y + 1 && wking.x == b->x + 1)
						{
							b->x -= 1;
							b->y -= 1;
							break;
						}

						for (auto& w : wPiece)
						{
							if (w->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);

									check();
									b->x -= 1;
									b->y -= 1;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										return;
									}
								}
							}
						}
						break;
					case 2:
						break;
					case 3:
						b->x += 1;
						b->y += 1;
						if (wking.y == b->y + 1 && wking.x == b->x + 1)
						{
							b->x -= 1;
							b->y -= 1;
							break;
						}
						check();
						b->x -= 1;
						b->y -= 1;

						if (king.check == 0)
						{
							return;
						}
						break;
					}

					//left down
					switch (locAlg(b->x, b->y, -1, 1))
					{
					case 0:
						break;
					case 1:
						b->x -= 1;
						b->y += 1;
						if (wking.y == b->y + 1 && wking.x == b->x - 1)
						{
							b->x += 1;
							b->y -= 1;
							break;
						}

						for (auto& w : wPiece)
						{
							if (w->piece != KING)
							{
								if (w->x == b->x && b->y == w->y)
								{
									wDead++;
									px = w->x;
									py = w->y;
									w->death = 1;
									w->dead(wDead);

									check();
									b->x += 1;
									b->y -= 1;

									col(w->y, w->x, py, px, w->piece + 6);
									wDead--;
									w->x = px;
									w->y = py;
									w->death = 0;

									if (king.check == 0)
									{
										return;
									}
								}
							}
						}
						break;
					case 2:
						break;
					case 3:
						b->x -= 1;
						b->y += 1;
						if (wking.y == b->y + 1 && wking.x == b->x - 1)
						{
							b->x += 1;
							b->y -= 1;
							break;
						}
						check();
						b->x += 1;
						b->y -= 1;

						if (king.check == 0)
						{
							return;
						}
						break;
					}
				}
			}
		}
		//if this runs it means stalemate, white cant move
		win = 4;
	}
	return;
}

//restarts the game
void newGame()
{
	int px = 0;
	int py = 0;
	turn = 0;
	bDead = 0;
	wDead = 0;
	//empty out current taken locations
	for (int i = 0; i < 16; i++)
	{
		px = bPiece[i]->x;
		py = bPiece[i]->y;
		if ((px % 2 == 0 && py % 2 == 0) || (px % 2 == 1 && py % 2 == 1))
		{
			board[py][px] = "\033[100;47;10m \033[0m";
			continue;
		}
		board[py][px] = " ";
	}
	for (int i = 0; i < 16; i++)
	{
		px = wPiece[i]->x;
		py = wPiece[i]->y;
		if ((px % 2 == 0 && py % 2 == 0) || (px % 2 == 1 && py % 2 == 1))
		{
			board[py][px] = "\033[100;47;10m \033[0m";
			continue;
		}
		board[py][px] = " ";
	}

	//reset black and white pieces
	for (int i = 0; i < 16; i++)
	{
		if (i < 8)
		{
			bPiece[i]->piece = PAWN;
			wPiece[i]->piece = PAWN;
			bPiece[i]->piecePlacement(i, 6, PAWN);
			wPiece[i]->piecePlacement(i, 1, PAWN);
		}
		else if (i < 10)
		{
			if (i == 8)
			{
				bPiece[i]->piecePlacement(0, 7, ROOK);
				wPiece[i]->piecePlacement(0, 0, ROOK);
			}
			else
			{
				bPiece[i]->piecePlacement(7, 7, ROOK);
				wPiece[i]->piecePlacement(7, 0, ROOK);
			}
		}
		else if (i < 12)
		{
			if (i == 10)
			{
				bPiece[i]->piecePlacement(2, 7, BISHOP);
				wPiece[i]->piecePlacement(2, 0, BISHOP);
			}
			else
			{
				bPiece[i]->piecePlacement(5, 7, BISHOP);
				wPiece[i]->piecePlacement(5, 0, BISHOP);
			}
		}
		else if (i < 14)
		{
			if (i == 12)
			{
				bPiece[i]->piecePlacement(1, 7, HORSE);
				wPiece[i]->piecePlacement(1, 0, HORSE);
			}
			else
			{
				bPiece[i]->piecePlacement(6, 7, HORSE);
				wPiece[i]->piecePlacement(6, 0, HORSE);
			}
		}
		else
		{
			if (i == 14)
			{
				bPiece[i]->piecePlacement(4, 7, QUEEN);
				wPiece[i]->piecePlacement(4, 0, QUEEN);
			}
			else
			{
				bPiece[i]->piecePlacement(3, 7, KING);
				wPiece[i]->piecePlacement(3, 0, KING);
			}
		}
	}
	drawBoard();
}

//saves game to file
void save(std::string file)
{
	std::fstream File;
	File.open(file, std::ios::out);
	if (File.fail())
	{
		std::ofstream newFile(file);
		newFile.close();
		newFile.clear();
	}
	File.close();
	File.clear();

	File.open(file, std::ios::out);
	if (File.is_open())
	{
		for (auto& b : bPiece)
		{
			File << b->death << std::to_string(b->movesMade).length() << b->movesMade << std::to_string(b->x).length() << b->x << std::to_string(b->y).length() << b->y << std::to_string(b->check).length() << b->check << std::to_string(b->piece).length() << b->piece << std::to_string(b->enPassantCnt).length() << b->enPassantCnt << std::to_string(win).length() << win << std::to_string(turn).length() << turn << "\n";
		}
		for (auto& w : wPiece)
		{
			File << w->death << std::to_string(w->movesMade).length() << w->movesMade << std::to_string(w->x).length() << w->x << std::to_string(w->y).length() << w->y << std::to_string(w->check).length() << w->check << std::to_string(w->piece).length() << w->piece << std::to_string(w->enPassantCnt).length() << w->enPassantCnt << std::to_string(win).length() << win << std::to_string(turn).length() << turn << "\n";
		}
		File.close();
		File.clear();
		drawBoard();
		std::cout << "saved" << std::endl;
	}
}

//loads previously saved game
void load(std::string file)
{
	bDead = 0;
	wDead = 0;
	int px = 0;
	int py = 0;
	std::string p = "";
	std::string app = "";
	int size = 0;
	int cnt = 0;
	std::fstream File;
	std::string line = "";
	int ff = 0;

	File.open(file, std::ios::in);
	if (File.fail())
	{
		File.close();
		File.clear();
		drawBoard();
		std::cout << "file cannot be opened " << std::endl;
	}
	if (File.is_open())
	{
		//empty out current taken locations to prevent graphical errors from pieces
		for (int i = 0; i < 16; i++)
		{
			px = bPiece[i]->x;
			py = bPiece[i]->y;
			if ((px % 2 == 0 && py % 2 == 0) || (px % 2 == 1 && py % 2 == 1))
			{
				board[py][px] = "\033[100;47;10m \033[0m";
				continue;
			}
			board[py][px] = " ";
		}

		for (int i = 0; i < 16; i++)
		{
			px = wPiece[i]->x;
			py = wPiece[i]->y;
			if ((px % 2 == 0 && py % 2 == 0) || (px % 2 == 1 && py % 2 == 1))
			{
				board[py][px] = "\033[100;47;10m \033[0m";
				continue;
			}
			board[py][px] = " ";
		}

		//kill all dead pieces before placing new pieces
		for (auto& b : bPiece)
		{
			cnt = 1;
			if (ff < 16)
				getline(File, line);
			else
				break;
			//after 5 of these, it hits piece type
			for (int i = 0; i < 5; i++)
			{
				p = line[cnt];
				size = std::stoi(p);
				cnt++;
				for (int j = 0; j < size; j++)
				{
					p = line[cnt];
					app.append(p);
					cnt++;
				}
				if (i == 4)
				{
					b->piece = std::stoi(app);
				}
				app = "";
			}

			if (line[0] == '1')
			{
				b->death = 1;
				bDead++;
				b->dead(bDead);
			}
			ff++;
		}

		for (auto& w : wPiece)
		{
			cnt = 1;
			if (ff < 32)
				getline(File, line);
			else
				break;
			//after 5 of these, it hits piece type
			for (int i = 0; i < 5; i++)
			{
				p = line[cnt];
				size = std::stoi(p);
				cnt++;
				for (int j = 0; j < size; j++)
				{
					p = line[cnt];
					app.append(p);
					cnt++;
				}
				if (i == 4)
				{
					w->piece = std::stoi(app);
				}
				app = "";
			}
			
			if (line[0] == '1')
			{
				w->death = 1;
				wDead++;
				w->dead(wDead);
			}
			ff++;
		}
	}

	File.close();
	File.clear();
	File.open(file, std::ios::in);
	if (File.fail())
	{
		File.close();
		File.clear();
		drawBoard();
		std::cout << "file cannot be opened " << std::endl;
	}
	if (File.is_open())
	{
		px = 0;
		py = 0;
		ff = 0;

		for (auto& b : bPiece)
		{
			cnt = 1;
			px = b->x;
			py = b->y;
			app = "";

			if (ff < 16)
				getline(File, line);
			else
				break;
			
			p = line[0];
			app = p;
			b->death = std::stoi(app);
			app = "";

			p = line[cnt];
			size = std::stoi(p);
			cnt++;
			for (int i = 0; i < size; i++)
			{
				p = line[cnt];
				app.append(p);
				cnt++;
			}
			b->movesMade = std::stoi(app);
			app = "";

			p = line[cnt];
			size = std::stoi(p);
			cnt++;
			for (int i = 0; i < size; i++)
			{
				p = line[cnt];
				app.append(p);
				cnt++;
			}
			b->x = std::stoi(app);
			app = "";

			p = line[cnt];
			size = std::stoi(p);
			cnt++;
			for (int i = 0; i < size; i++)
			{
				p = line[cnt];
				app.append(p);
				cnt++;
			}
			b->y = std::stoi(app);
			app = "";

			p = line[cnt];
			size = std::stoi(p);
			cnt++;
			for (int i = 0; i < size; i++)
			{
				p = line[cnt];
				app.append(p);
				cnt++;
			}
			b->check = std::stoi(app);
			app = "";

			p = line[cnt];
			size = std::stoi(p);
			cnt++;
			for (int i = 0; i < size; i++)
			{
				p = line[cnt];
				app.append(p);
				cnt++;
			}
			b->piece = std::stoi(app);
			app = "";

			p = line[cnt];
			size = std::stoi(p);
			cnt++;
			for (int i = 0; i < size; i++)
			{
				p = line[cnt];
				app.append(p);
				cnt++;
			}
			b->enPassantCnt = std::stoi(app);
			app = "";

			p = line[cnt];
			size = std::stoi(p);
			cnt++;
			for (int i = 0; i < size; i++)
			{
				p = line[cnt];
				app.append(p);
				cnt++;
			}
			win = std::stoi(app);
			app = "";

			p = line[cnt];
			size = std::stoi(p);
			cnt++;
			for (int i = 0; i < size; i++)
			{
				p = line[cnt];
				app.append(p);
				cnt++;
			}
			turn = std::stoi(app);
			app = "";
			if (b->death == 0)
			{
				col(py, px, b->y, b->x, b->piece);
			}
			ff++;
		}

		for (auto& w : wPiece)
		{
			px = w->x;
			py = w->y;
			cnt = 1;
			app = "";

			if (ff < 32)
				getline(File, line);
			else
				break;
			
			p = line[0];
			app = p;
			w->death = std::stoi(app);
			app = "";

			p = line[cnt];
			size = std::stoi(p);
			cnt++;
			for (int i = 0; i < size; i++)
			{
				p = line[cnt];
				app.append(p);
				cnt++;
			}
			w->movesMade = std::stoi(app);
			app = "";

			p = line[cnt];
			size = std::stoi(p);
			cnt++;
			for (int i = 0; i < size; i++)
			{
				p = line[cnt];
				app.append(p);
				cnt++;
			}
			w->x = std::stoi(app);
			app = "";

			p = line[cnt];
			size = std::stoi(p);
			cnt++;
			for (int i = 0; i < size; i++)
			{
				p = line[cnt];
				app.append(p);
				cnt++;
			}
			w->y = std::stoi(app);
			app = "";

			p = line[cnt];
			size = std::stoi(p);
			cnt++;
			for (int i = 0; i < size; i++)
			{
				p = line[cnt];
				app.append(p);
				cnt++;
			}
			w->check = std::stoi(app);
			app = "";

			p = line[cnt];
			size = std::stoi(p);
			cnt++;
			for (int i = 0; i < size; i++)
			{
				p = line[cnt];
				app.append(p);
				cnt++;
			}
			w->piece = std::stoi(app);
			app = "";

			p = line[cnt];
			size = std::stoi(p);
			cnt++;
			for (int i = 0; i < size; i++)
			{
				p = line[cnt];
				app.append(p);
				cnt++;
			}
			w->enPassantCnt = std::stoi(app);
			app = "";

			p = line[cnt];
			size = std::stoi(p);
			cnt++;
			for (int i = 0; i < size; i++)
			{
				p = line[cnt];
				app.append(p);
				cnt++;
			}
			win = std::stoi(app);
			app = "";

			p = line[cnt];
			size = std::stoi(p);
			cnt++;
			for (int i = 0; i < size; i++)
			{
				p = line[cnt];
				app.append(p);
				cnt++;
			}
			turn = std::stoi(app);
			app = "";
			cnt = 0;

			if (w->death == 0)
			{
				col(py, px, w->y, w->x, w->piece + 6);
			}
			ff++;
		}
		File.close();
		File.clear();
		check();
		checkmate();
		stalemate();
		drawBoard();

		if (wking.check == 1)
		{
			std::cout << "white's in check" << std::endl;
			return;
		}
		if (king.check == 1)
		{
			std::cout << "black's in check" << std::endl;
			return;
		}
		std::cout << "loaded" << std::endl;
	}
}

//handles changes to saveslots
void saveSlot(std::string command)
{
	std::string fileName = "";
	std::vector<std::string> saveFiles;
	int size = 0;
	std::fstream File;
	int saveNum = 0;
	int newSave = 0;

	File.open("savefiles.txt", std::ios::in);
	if (File.fail())
	{
		std::ofstream newFile("saveFiles.txt");
		newFile.close();
	}
	if (File.is_open())
	{
		saveFiles.clear();
		while (getline(File, fileName))
		{
			saveFiles.push_back(fileName);
		}
		size = saveFiles.size();
		File.close();
		File.clear();
	}
	if (!saveFiles.empty())
	{
		for (int i = 0; i < size; i++)
		{
			std::cout << " ____________________________________" << std::endl;
			std::cout << "|                                    |" << std::endl;
			int spaceOffset = 33 - saveFiles[i].length();

			std::cout << "| " << i + 1 << " " << saveFiles[i];
			for (int j = 0; j < spaceOffset; j++)
			{
				std::cout << " ";
			}
			std::cout << "|" << std::endl;
			std::cout << "|____________________________________|" << std::endl;
		}

		if (command == "L")
		{
			std::cout << "Enter saveslot number: ";
			std::cin >> saveNum;
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore();
				drawBoard();
				std::cout << "cannot enter letter values" << std::endl;
				return;
			}
			if (saveNum <= size && saveNum > 0)
			{
				fileName = saveFiles[saveNum - 1];
			}
			else
			{
				drawBoard();
				std::cout << "saveslot number doesnt exist" << std::endl;
				return;
			}

			load(fileName);
		}
		if (command == "S")
		{
			std::cout << "To save to a previous save, enter 1. To create a new save press 2 ";
			std::cin >> newSave;
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore();
				drawBoard();
				std::cout << "cannot enter letter values" << std::endl;
				return;
			}
			
			switch (newSave)
			{
				case 1:
					std::cout << "Enter saveslot number: ";
					std::cin >> saveNum;
					if (std::cin.fail())
					{
						std::cin.clear();
						std::cin.ignore();
						drawBoard();
						std::cout << "cannot enter letter values" << std::endl;
						return;
					}
					if (saveNum <= size && saveNum > 0)
					{
						fileName = saveFiles[saveNum - 1];
					}
					else
					{
						drawBoard();
						std::cout << "saveslot number doesnt exist" << std::endl;
						return;
					}
					save(fileName);
					break;
				case 2:
					std::cout << "Enter the savefile name ";
					std::cin >> fileName;
					fileName.append(".txt");
					for (int i = 0; i < size; i++)
					{
						if (saveFiles[i] == fileName)
						{
							drawBoard();
							std::cout << "cannot enter the same name as another save" << std::endl;
							return;
						}
					}
					File.open("savefiles.txt", std::ios::app);
					File << fileName << "\n";
					File.close();
					File.clear();
					save(fileName);
					break;
				default:
					break;
			}
		}
		if (command == "D")
		{
			std::string temp = "";
			std::cout << "Enter saveslot number: ";
			std::cin >> saveNum;
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore();
				drawBoard();
				std::cout << "cannot enter letter values" << std::endl;
				return;
			}
			if (saveNum <= size && saveNum > 0)
			{
				fileName = saveFiles[saveNum - 1];
			}
			else
			{
				drawBoard();
				std::cout << "saveslot number doesnt exist" << std::endl;
				return;
			}
			std::cout << "Are you sure you want to delete " << fileName << "? y/n" << std::endl;
			std::cin >> temp;
			if (temp == "y")
			{
				saveFiles.erase(saveFiles.begin() + saveNum-1);

				size = saveFiles.size();

				File.open("savefiles.txt", std::ios::out);
				if (File.is_open())
				{
					for (int i = 0; i < size; i++)
					{
						File << saveFiles[i] << "\n";
					}
				}
				File.close();
				File.clear();

				if (remove(fileName.c_str()) != 0)
				{
					drawBoard();
					std::cout << "Could not delete file" << std::endl;
					return;
				}
				drawBoard();
				std::cout << "File deleted successfully" << std::endl;
				return;
			}
		}
		return;
	}
	if (saveFiles.empty())
	{
		if (command == "S")
		{
			std::cout << "Enter the savefile name ";
			std::cin >> fileName;
			fileName.append(".txt");
			File.open("savefiles.txt", std::ios::app);
			File << fileName;
			File.close();
			File.clear();
			save(fileName);
			return;
		}
		drawBoard();
		std::cout << "no save files exist" << std::endl;
		return;
	}
}

//moves black pieces
void bMove()
{
	if (win == 0)
	{
		int snum = 0;
		int valid = 0;
		int currx = 0;
		int curry = 0;
		std::string select = "";
		int selectx = 0;
		int selecty = 0;

		std::cout << "To operate a command, type N for newgame, D to delete a previous save, L for loading a previous save, Q for quitting," << std::endl << "or S to save the current game\n";
		std::cout << "Black's turn: select a piece ";

		//get selection piece or command
		std::cin >> select;
		//for loading commands
		try {
			//on number entry sets selectx to converted string select to int
			selectx = std::stoi(select);
		}
		catch (const std::invalid_argument& ia) {
			//fails conversion and checks if valid command entered
			if (select == "L")
			{
				saveSlot("L");
				return;
			}
			if (select == "S")
			{
				saveSlot("S");
				return;
			}
			if (select == "D")
			{
				saveSlot("D");
				return;
			}
			if (select == "Q")
			{
				exit(0);
			}
			if (select == "N")
			{
				newGame();
				std::cout << "new game loaded" << std::endl;
				return;
			}
			drawBoard();
			std::cout << "invalid command" << std::endl;
			bMove();
			return;
		}
		std::cin >> selecty;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore();
			drawBoard();
			std::cout << "cannot enter letter values" << std::endl;
			bMove();
			return;
		}

		if (selectx > 7 || selecty > 7)
		{
			std::cin.clear();
			std::cin.ignore();
			drawBoard();
			std::cout << "out of chess bounds" << std::endl;
			bMove();
			return;
		}

		if (selectx < 0 || selecty < 0)
		{
			std::cin.clear();
			std::cin.ignore();
			drawBoard();
			std::cout << "out of chess bounds" << std::endl;
			bMove();
			return;
		}

		for (auto& b : bPiece)
		{
			if (selectx == b->x && selecty == b->y)
			{
				snum++;
				//get selection piece
				std::cin >> currx;
				std::cin >> curry;

				if (std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore();
					drawBoard();
					std::cout << "cannot enter letter values" << std::endl;
					bMove();
					return;
				}

				if (currx > 7 || curry > 7)
				{
					std::cin.clear();
					std::cin.ignore();
					drawBoard();
					std::cout << "out of chess bounds" << std::endl;
					bMove();
					return;
				}

				if (currx < 0 || curry < 0)
				{
					std::cin.clear();
					std::cin.ignore();
					drawBoard();
					std::cout << "out of chess bounds" << std::endl;
					bMove();
					return;
				}

				//check moves for pawn
				if (b->piece == PAWN)
				{
					//moves forward 1
					if (currx == selectx && curry == selecty - 1)
					{
						valid = 1;
					}

					//moves forward 2
					if (b->movesMade == 0)
					{
						if (currx == selectx && curry == selecty - 2)
						{
							valid = 1;
							for (auto& b1 : bPiece)
							{
								if (currx == b1->x && b1->y == curry + 1)
								{
									valid = 0;
								}
								if (b1->x == currx && b1->y == curry)
								{
									valid = 0;
								}
							}
							for (auto& w : wPiece)
							{
								if (currx == w->x && w->y == curry + 1)
								{
									valid = 0;
								}
								if (w->x == currx && w->y == curry)
								{
									valid = 0;
								}
							}
							
							if (valid == 1)
							{
								check();
								if (king.check == 1)
								{
									drawBoard();
									std::cout << "Black is in check" << std::endl;
									bMove();
									return;
								}
								for (auto& w : wPiece)
								{
									if (w->piece == PAWN)
									{
										if (w->y == curry && (w->x == currx - 1 || w->x == currx + 1))
										{
											std::cout << "black en passant is active";
											int g;
											b->enPassantCnt = 1;
											std::cin >> g;
										}
									}
								}
							}
						}
					}

					for (auto& w : wPiece)
					{
						if (w->x == currx && w->y == curry)
						{
							valid = 0;
						}
					}

					if (currx == selectx + 1 && curry == selecty - 1)
					{
						for (auto& w : wPiece)
						{
							if (w->x == currx && w->y == curry)
							{
								valid = 1;
							}
							if (w->x == currx && w->y == curry + 1 && w->enPassantCnt == 1)
							{
								valid = 1;
							}
						}
					}

					if (currx == selectx - 1 && curry == selecty - 1)
					{
						for (auto& w : wPiece)
						{
							if (w->x == currx && w->y == curry)
							{
								valid = 1;
							}
							if (w->x == currx && w->y == curry + 1 && w->enPassantCnt == 1)
							{
								valid = 1;
							}
						}
					}
				}

				//check moves for rook
				if (b->piece == ROOK)
				{
					//vertical movement
					if (currx == selectx && (curry < selecty || curry > selecty))
					{
						valid = 1;
						for (auto& b1 : bPiece)
						{
							if (b1->x == selectx)
							{
								if (curry < selecty && (curry < b1->y && selecty > b1->y))
								{
									valid = 0;
								}
								if (curry > selecty && (curry > b1->y && selecty < b1->y))
								{
									valid = 0;
								}
							}
						}

						for (auto& w : wPiece)
						{
							if (w->x == selectx)
							{
								if (curry < selecty && (curry < w->y && selecty > w->y))
								{
									valid = 0;
								}
								if (curry > selecty && (curry > w->y && selecty < w->y))
								{
									valid = 0;
								}
							}
						}
					}

					//horizontal movement
					if (curry == selecty && (currx < selectx || currx > selectx))
					{
						valid = 1;
						for (auto& b1 : bPiece)
						{
							if (b1->y == selecty)
							{
								if (currx < selectx && (currx < b1->x && selectx > b1->x))
								{
									valid = 0;
								}
								if (currx > selectx && (currx > b1->x && selectx < b1->x))
								{
									valid = 0;
								}
							}
						}

						for (auto& w : wPiece)
						{
							if (w->y == selecty)
							{
								if (currx < selectx && (currx < w->x && selectx > w->x))
								{
									valid = 0;
								}
								if (currx > selectx && (currx > w->x && selectx < w->x))
								{
									valid = 0;
								}
							}
						}
					}
				}

				//check moves for horse
				if (b->piece == HORSE)
				{
					if (currx == selectx - 2 && curry == selecty - 1)
					{
						valid = 1;
					}

					if (currx == selectx - 2 && curry == selecty + 1)
					{
						valid = 1;
					}

					if (currx == selectx + 2 && curry == selecty - 1)
					{
						valid = 1;
					}

					if (currx == selectx + 2 && curry == selecty + 1)
					{
						valid = 1;
					}

					if (currx == selectx - 1 && curry == selecty - 2)
					{
						valid = 1;
					}

					if (currx == selectx - 1 && curry == selecty + 2)
					{
						valid = 1;
					}

					if (currx == selectx + 1 && curry == selecty - 2)
					{
						valid = 1;
					}

					if (currx == selectx + 1 && curry == selecty + 2)
					{
						valid = 1;
					}
				}

				//check moves for bishop
				if (b->piece == BISHOP)
				{
					//right up diagonal
					if (currx > selectx && curry < selecty && (currx - selectx == selecty - curry))
					{
						valid = 1;
						for (auto& b1 : bPiece)
						{
							if ((selectx < b1->x && selecty > b1->y) && (currx > b1->x && curry < b1->y))
							{
								if (currx - b1->x == b1->y - curry)
								{
									valid = 0;
								}
							}
						}

						for (auto& w : wPiece)
						{
							if ((selectx < w->x && selecty > w->y) && (currx > w->x && curry < w->y))
							{
								if (currx - w->x == w->y - curry)
								{
									valid = 0;
								}
							}
						}
					}

					//right down diagonal
					if (currx > selectx && curry > selecty && (currx - selectx == curry - selecty))
					{
						valid = 1;
						for (auto& b1 : bPiece)
						{
							if ((selectx < b1->x && selecty < b1->y) && (currx > b1->x && curry > b1->y))
							{
								if (currx - b1->x == curry - b1->y)
								{
									valid = 0;
								}
							}
						}

						for (auto& w : wPiece)
						{
							if ((selectx < w->x && selecty < w->y) && (currx > w->x && curry > w->y))
							{
								if (currx - w->x == curry - w->y)
								{
									valid = 0;
								}
							}
						}
					}

					//left up diagonal
					if (currx < selectx && curry < selecty && (selectx - currx == selecty - curry))
					{
						valid = 1;
						for (auto& b1 : bPiece)
						{
							if ((selectx > b1->x && selecty > b1->y) && (currx < b1->x && curry < b1->y))
							{
								if (b1->x - currx == b1->y - curry)
								{
									valid = 0;
								}
							}
						}

						for (auto& w : wPiece)
						{
							if ((selectx > w->x && selecty > w->y) && (currx < w->x && curry < w->y))
							{
								if (w->x - currx == w->y - curry)
								{
									valid = 0;
								}
							}
						}
					}

					//left down diagonal
					if (currx < selectx && curry > selecty && (selectx - currx == curry - selecty))
					{
						valid = 1;
						for (auto& b1 : bPiece)
						{
							if ((selectx > b1->x && selecty < b1->y) && (currx < b1->x && curry > b1->y))
							{
								if (b1->x - currx == curry - b1->y)
								{
									valid = 0;
								}
							}
						}

						for (auto& w : wPiece)
						{
							if ((selectx > w->x && selecty < w->y) && (currx < w->x && curry > w->y))
							{
								if (w->x - currx == curry - w->y)
								{
									valid = 0;
								}
							}
						}
					}
				}

				//check moves for queen
				if (b->piece == QUEEN)
				{
					//right up diagonal
					if (currx > selectx && curry < selecty && (currx - selectx == selecty - curry))
					{
						valid = 1;
						for (auto& b1 : bPiece)
						{
							if ((selectx < b1->x && selecty > b1->y) && (currx > b1->x && curry < b1->y))
							{
								if (currx - b1->x == b1->y - curry)
								{
									valid = 0;
								}
							}
						}

						for (auto& w : wPiece)
						{
							if ((selectx < w->x && selecty > w->y) && (currx > w->x && curry < w->y))
							{
								if (currx - w->x == w->y - curry)
								{
									valid = 0;
								}
							}
						}
					}

					//right down diagonal
					if (currx > selectx && curry > selecty && (currx - selectx == curry - selecty))
					{
						valid = 1;
						for (auto& b1 : bPiece)
						{
							if ((selectx < b1->x && selecty < b1->y) && (currx > b1->x && curry > b1->y))
							{
								if (currx - b1->x == curry - b1->y)
								{
									valid = 0;
								}
							}
						}

						for (auto& w : wPiece)
						{
							if ((selectx < w->x && selecty < w->y) && (currx > w->x && curry > w->y))
							{
								if (currx - w->x == curry - w->y)
								{
									valid = 0;
								}
							}
						}
					}

					//left up diagonal
					if (currx < selectx && curry < selecty && (selectx - currx == selecty - curry))
					{
						valid = 1;
						for (auto& b1 : bPiece)
						{
							if ((selectx > b1->x && selecty > b1->y) && (currx < b1->x && curry < b1->y))
							{
								if (b1->x - currx == b1->y - curry)
								{
									valid = 0;
								}
							}
						}

						for (auto& w : wPiece)
						{
							if ((selectx > w->x && selecty > w->y) && (currx < w->x && curry < w->y))
							{
								if (w->x - currx == w->y - curry)
								{
									valid = 0;
								}
							}
						}
					}

					//left down diagonal
					if (currx < selectx && curry > selecty && (selectx - currx == curry - selecty))
					{
						valid = 1;
						for (auto& b1 : bPiece)
						{
							if ((selectx > b1->x && selecty < b1->y) && (currx < b1->x && curry > b1->y))
							{
								if (b1->x - currx == curry - b1->y)
								{
									valid = 0;
								}
							}
						}

						for (auto& w : wPiece)
						{
							if ((selectx > w->x && selecty < w->y) && (currx < w->x && curry > w->y))
							{
								if (w->x - currx == curry - w->y)
								{
									valid = 0;
								}
							}
						}
					}

					//vertical movement
					if (currx == selectx && (curry < selecty || curry > selecty))
					{
						valid = 1;
						for (auto& b1 : bPiece)
						{
							if (b1->x == selectx)
							{
								if (curry < selecty && (curry < b1->y && selecty > b1->y))
								{
									valid = 0;
								}
								if (curry > selecty && (curry > b1->y && selecty < b1->y))
								{
									valid = 0;
								}
							}
						}

						for (auto& w : wPiece)
						{
							if (w->x == selectx)
							{
								if (curry < selecty && (curry < w->y && selecty > w->y))
								{
									valid = 0;
								}
								if (curry > selecty && (curry > w->y && selecty < w->y))
								{
									valid = 0;
								}
							}
						}
					}

					//horizontal movement
					if (curry == selecty && (currx < selectx || currx > selectx))
					{
						valid = 1;
						for (auto& b1 : bPiece)
						{
							if (b1->y == selecty)
							{
								if (currx < selectx && (currx < b1->x && selectx > b1->x))
								{
									valid = 0;
								}
								if (currx > selectx && (currx > b1->x && selectx < b1->x))
								{
									valid = 0;
								}
							}
						}

						for (auto& w : wPiece)
						{
							if (w->y == selecty)
							{
								if (currx < selectx && (currx < w->x && selectx > w->x))
								{
									valid = 0;
								}
								if (currx > selectx && (currx > w->x && selectx < w->x))
								{
									valid = 0;
								}
							}
						}
					}
				}

				//check moves for king
				if (b->piece == KING)
				{
					//right up
					if (currx == selectx + 1 && curry == selecty - 1)
					{
						valid = 1;
					}

					//right down
					if (currx == selectx + 1 && curry == selecty + 1)
					{
						valid = 1;
					}

					//left up
					if (currx == selectx - 1 && curry == selecty - 1)
					{
						valid = 1;
					}

					//left down
					if (currx == selectx - 1 && curry == selecty + 1)
					{
						valid = 1;
					}

					//up
					if (currx == selectx && curry == selecty - 1)
					{
						valid = 1;
					}

					//down
					if (currx == selectx && curry == selecty + 1)
					{
						valid = 1;
					}

					//left
					if (currx == selectx - 1 && curry == selecty)
					{
						valid = 1;
					}

					//right
					if (currx == selectx + 1 && curry == selecty)
					{
						valid = 1;
					}

					//up or down
					if (currx == wking.x && (curry - 1 == wking.y || curry + 1 == wking.y))
					{
						valid = 0;
					}

					//left up diagonal or left down diagonal
					if (currx - 1 == wking.x && (curry - 1 == wking.y || curry + 1 == wking.y))
					{
						valid = 0;
					}

					//right up diagonal or right down diagonal
					if (currx + 1 == wking.x && (curry - 1 == wking.y || curry + 1 == wking.y))
					{
						valid = 0;
					}

					//right or left
					if (curry == wking.y && (currx - 1 == wking.x || currx + 1 == wking.x))
					{
						valid = 0;
					}

					// if king is not in check
					if (king.check == 0)
					{
						//kings side castling
						if (currx == selectx - 2 && curry == selecty)
						{
							if (b->movesMade == 0 && rook1.movesMade == 0)
							{
								valid = 1;
							}

							for (auto& b1 : bPiece)
							{
								if (b1->y == 7)
								{
									if (b1->x < king.x && b1->x > rook1.x)
									{
										valid = 0;
									}
								}
							}
							for (auto& w : wPiece)
							{
								if (w->y == 7)
								{
									if (w->x < king.x && w->x > rook1.x)
									{
										valid = 0;
									}
								}
							}

							if (valid == 1)
							{
								rook1.movesMade++;
								rook1.x = 2;
								col(7, 0, 7, 2, 2);

								b->x = currx;
								check();
								if (king.check == 1)
								{
									b->x = selectx;
									rook1.movesMade--;
									rook1.x = 0;
									col(7, 2, 7, 0, 2);
									valid = 0;
								}
								b->x = selectx;
							}
						}

						//queens side castling
						if (currx == selectx + 2 && curry == selecty)
						{
							if (b->movesMade == 0 && rook2.movesMade == 0)
							{
								valid = 1;
							}

							for (auto& b1 : bPiece)
							{
								if (b1->y == 7)
								{
									if (b1->x > king.x && b1->x < rook2.x)
									{
										valid = 0;
									}
								}
							}
							for (auto& w : wPiece)
							{
								if (w->y == 7)
								{
									if (w->x > king.x && w->x < rook2.x)
									{
										valid = 0;
									}
								}
							}

							if (valid == 1)
							{
								rook2.movesMade++;
								rook2.x = 4;
								col(7, 7, 7, 4, 2);

								b->x = currx;
								check();
								if (king.check == 1)
								{
									b->x = selectx;
									rook2.movesMade--;
									rook2.x = 7;
									col(7, 4, 7, 7, 2);
									valid = 0;
								}
								b->x = selectx;
							}
						}
					}
				}

				for (auto& b1 : bPiece)
				{
					if (currx == b1->x && curry == b1->y)
					{
						valid = 0;
					}
					if (currx == wking.x && curry == wking.y)
					{
						valid = 0;
					}
				}

				if (valid == 1)
				{
					b->x = currx;
					b->y = curry;
					b->movesMade++;

					//runs promotion
					if (b->piece == PAWN && b->y == 0)
					{
						char promotion = ' ';
						std::cout << "Pawn has been promoted, please choose a piece to promote to" << std::endl;
						std::cout << "enter Q, H, B, or R: ";
						std::cin >> promotion;
						if (promotion != 'Q' && promotion != 'H' && promotion != 'B' && promotion != 'R')
						{
							b->x = selectx;
							b->y = selecty;
							col(curry, currx, selecty, selectx, b->piece);
							for (auto& w : wPiece)
							{
								if (currx == w->x && curry == w->y)
								{
									col(w->y, w->x, curry, currx, w->piece + 6);
								}
							}
							drawBoard();
							std::cout << "must enter a valid promotion value" << std::endl;
							bMove();
							return;
						}
						if (promotion == 'Q')
						{
							b->piece = QUEEN;
						}
						if (promotion == 'H')
						{
							b->piece = HORSE;
						}
						if (promotion == 'B')
						{
							b->piece = BISHOP;
						}
						if (promotion == 'R')
						{
							b->piece = ROOK;
						}
					}

					//killed white piece
					for (auto& w : wPiece)
					{
						if (currx == w->x && curry == w->y)
						{
							w->death = 1;
							wDead++;
							w->dead(wDead);

							check();

							if (king.check == 1)
							{
								col(w->y, w->x, curry, currx, w->piece + 6);
								w->x = currx;
								w->y = curry;
								w->death = 0;
								wDead--;
								b->x = selectx;
								b->y = selecty;
								b->movesMade--;
								drawBoard();
								std::cout << "black is in check" << std::endl;
								bMove();
								return;
							}
							col(curry, currx, w->y, w->x, w->piece + 6);
						}
						if (b->piece == PAWN)
						{
							if (currx == w->x && curry + 1 == w->y)
							{
								w->death = 1;
								wDead++;
								w->dead(wDead);

								check();

								if (king.check == 1)
								{
									col(w->y, w->x, curry + 1, currx, w->piece + 6);
									w->x = currx;
									w->y = curry - 1;
									w->death = 0;
									wDead--;
									b->x = selectx;
									b->y = selecty;
									b->movesMade--;
									drawBoard();
									std::cout << "black is in check" << std::endl;
									bMove();
									return;
								}
								col(curry - 1, currx, w->y, w->x, w->piece + 6);
							}
						}
					}

					check();

					if (king.check == 1)
					{
						b->x = selectx;
						b->y = selecty;
						b->movesMade--;
						drawBoard();
						std::cout << "black is in check" << std::endl;
						bMove();
						return;
					}

					checkmate();
					stalemate();

					col(selecty, selectx, curry, currx, b->piece);
					for (auto& w : wPiece)
					{
						if (w->piece == PAWN)
						{
							w->enPassantCnt = 0;
						}
					}
					turn = 1;
					if (wking.check == 1)
					{
						drawBoard();
						std::cout << "white is in check" << std::endl;
						return;
					}
					drawBoard();
				}
				else
				{
					if (king.check == 1)
					{
						drawBoard();
						std::cout << "black is in check" << std::endl;
						bMove();
						return;
					}
					drawBoard();
					std::cout << "invalid move" << std::endl;
					bMove();
					return;
				}
			}
		}
		if (snum == 0)
		{
			drawBoard();
			std::cout << "no valid piece selected" << std::endl;
			bMove();
			return;
		}
	}
}

//moves white pieces
void wMove()
{
	if (win == 0)
	{
		int snum = 0;
		int valid = 0;
		int currx = 0;
		int curry = 0;
		std::string select = "";
		int selectx = 0;
		int selecty = 0;

		std::cout << "To operate a command, type N for newgame, D to delete a previous save, L for loading a previous save, Q for quitting," << std::endl << "or S to save the current game\n";
		std::cout << "white's turn: select a piece ";

		//get selection piece
		std::cin >> select;
		//for loading commands
		try {
			//on number entry sets selectx to converted string select to int
			selectx = std::stoi(select);
		}
		catch (const std::invalid_argument& ia) {
			//fails conversion and checks if valid command entered
			if (select == "L")
			{
				saveSlot("L");
				return;
			}
			if (select == "S")
			{
				saveSlot("S");
				return;
			}
			if (select == "D")
			{
				saveSlot("D");
				return;
			}
			if (select == "Q")
			{
				exit(0);
			}
			if (select == "N")
			{
				newGame();
				std::cout << "new game loaded" << std::endl;
				return;
			}
			drawBoard();
			std::cout << "invalid command" << std::endl;
			wMove();
			return;
		}
		std::cin >> selecty;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore();
			drawBoard();
			std::cout << "cannot enter letter values" << std::endl;
			wMove();
			return;
		}

		if (selectx > 7 || selecty > 7)
		{
			std::cin.clear();
			std::cin.ignore();
			drawBoard();
			std::cout << "out of chess bounds" << std::endl;
			wMove();
			return;
		}

		if (selectx < 0 || selecty < 0)
		{
			std::cin.clear();
			std::cin.ignore();
			drawBoard();
			std::cout << "out of chess bounds" << std::endl;
			wMove();
			return;
		}

		for (auto& w : wPiece)
		{
			if (selectx == w->x && selecty == w->y)
			{
				snum++;
				//new location
				std::cin >> currx;
				std::cin >> curry;

				if (std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore();
					drawBoard();
					std::cout << "cannot enter letter values" << std::endl;
					wMove();
					return;
				}

				if (currx > 7 || curry > 7)
				{
					std::cin.clear();
					std::cin.ignore();
					drawBoard();
					std::cout << "out of chess bounds" << std::endl;
					wMove();
					return;
				}

				if (currx < 0 || curry < 0)
				{
					std::cin.clear();
					std::cin.ignore();
					drawBoard();
					std::cout << "out of chess bounds" << std::endl;
					wMove();
					return;
				}

				//check moves for pawn
				if (w->piece == PAWN)
				{
					//moves forward 1
					if (currx == selectx && curry == selecty + 1)
					{
						valid = 1;
					}

					//moves forward 2
					if (w->movesMade == 0)
					{
						if (currx == selectx && curry == selecty + 2)
						{
							valid = 1;
							for (auto& w1 : wPiece)
							{
								if (currx == w1->x && w1->y == curry - 1)
								{
									valid = 0;
								}
								if (w1->x == currx && w1->y == curry)
								{
									valid = 0;
								}
							}
							for (auto& b : bPiece)
							{
								if (currx == b->x && b->y == curry - 1)
								{
									valid = 0;
								}
								if (b->x == currx && b->y == curry)
								{
									valid = 0;
								}
							}
							if (valid == 1)
							{
								check();
								if (wking.check == 1)
								{
									drawBoard();
									std::cout << "White is in check" << std::endl;
									wMove();
									return;
								}
								for (auto& b : bPiece)
								{
									if (b->piece == PAWN)
									{
										if (b->y == curry && (b->x == currx - 1 || b->x == currx + 1))
										{
											std::cout << "white en passant is active";
											int g;
											w->enPassantCnt = 1;
											std::cin >> g;
										}
									}
								}
							}
						}
					}

					for (auto& b : bPiece)
					{
						if (b->x == currx && b->y == curry)
						{
							valid = 0;
						}
					}

					//enpassant
					if (currx == selectx + 1 && curry == selecty + 1)
					{
						for (auto& b : bPiece)
						{
							if (b->x == currx && b->y == curry)
							{
								valid = 1;
							}
							if (b->x == currx && b->y == curry - 1 && b->enPassantCnt == 1)
							{
								valid = 1;
							}
						}
					}

					if (currx == selectx - 1 && curry == selecty + 1)
					{
						for (auto& b : bPiece)
						{
							if (b->x == currx && b->y == curry)
							{
								valid = 1;
							}
							if (b->x == currx && b->y == curry - 1 && b->enPassantCnt == 1)
							{
								valid = 1;
							}
						}
					}
				}

				//check moves for rook
				if (w->piece == ROOK)
				{
					//vertical movement
					if (currx == selectx && (curry < selecty || curry > selecty))
					{
						valid = 1;
						for (auto& w1 : wPiece)
						{
							if (w1->x == selectx)
							{
								if (curry < selecty && (curry < w1->y && selecty > w1->y))
								{
									valid = 0;
								}
								if (curry > selecty && (curry > w1->y && selecty < w1->y))
								{
									valid = 0;
								}
							}
						}

						for (auto& b : bPiece)
						{
							if (b->x == selectx)
							{
								if (curry < selecty && (curry < b->y && selecty > b->y))
								{
									valid = 0;
								}
								if (curry > selecty && (curry > b->y && selecty < b->y))
								{
									valid = 0;
								}
							}
						}
					}

					//horizontal movement
					if (curry == selecty && (currx < selectx || currx > selectx))
					{
						valid = 1;
						for (auto& w1 : wPiece)
						{
							if (w1->y == selecty)
							{
								if (currx < selectx && (currx < w1->x && selectx > w1->x))
								{
									valid = 0;
								}
								if (currx > selectx && (currx > w1->x && selectx < w1->x))
								{
									valid = 0;
								}
							}
						}

						for (auto& b : bPiece)
						{
							if (b->y == selecty)
							{
								if (currx < selectx && (currx < b->x && selectx > b->x))
								{
									valid = 0;
								}
								if (currx > selectx && (currx > b->x && selectx < b->x))
								{
									valid = 0;
								}
							}
						}
					}
				}

				//check moves for horse
				if (w->piece == HORSE)
				{
					if (currx == selectx - 2 && curry == selecty - 1)
					{
						valid = 1;
					}

					if (currx == selectx - 2 && curry == selecty + 1)
					{
						valid = 1;
					}

					if (currx == selectx + 2 && curry == selecty - 1)
					{
						valid = 1;
					}

					if (currx == selectx + 2 && curry == selecty + 1)
					{
						valid = 1;
					}

					if (currx == selectx - 1 && curry == selecty - 2)
					{
						valid = 1;
					}

					if (currx == selectx - 1 && curry == selecty + 2)
					{
						valid = 1;
					}

					if (currx == selectx + 1 && curry == selecty - 2)
					{
						valid = 1;
					}

					if (currx == selectx + 1 && curry == selecty + 2)
					{
						valid = 1;
					}
				}

				//check moves for bishop
				if (w->piece == BISHOP)
				{
					//right up diagonal
					if (currx > selectx && curry < selecty && (currx - selectx == selecty - curry))
					{
						valid = 1;
						for (auto& w1 : wPiece)
						{
							if ((selectx < w1->x && selecty > w1->y) && (currx > w1->x && curry < w1->y))
							{
								if (currx - w1->x == w1->y - curry)
								{
									valid = 0;
								}
							}
						}

					}

					//right down diagonal
					if (currx > selectx && curry > selecty && (currx - selectx == curry - selecty))
					{
						valid = 1;
						for (auto& w1 : wPiece)
						{
							if ((selectx < w1->x && selecty < w1->y) && (currx > w1->x && curry > w1->y))
							{
								if (currx - w1->x == curry - w1->y)
								{
									valid = 0;
								}
							}
						}
					}

					//left up diagonal
					if (currx < selectx && curry < selecty && (selectx - currx == selecty - curry))
					{
						valid = 1;
						for (auto& w1 : wPiece)
						{
							if ((selectx > w1->x && selecty > w1->y) && (currx < w1->x && curry < w1->y))
							{
								if (w1->x - currx == w1->y - curry)
								{
									valid = 0;
								}
							}
						}
					}

					//left down diagonal
					if (currx < selectx && curry > selecty && (selectx - currx == curry - selecty))
					{
						valid = 1;
						for (auto& w1 : wPiece)
						{
							if ((selectx > w1->x && selecty < w1->y) && (currx < w1->x && curry > w1->y))
							{
								if (w1->x - currx == curry - w1->y)
								{
									valid = 0;
								}
							}
						}
					}
				}

				//check moves for queen
				if (w->piece == QUEEN)
				{
					//right up diagonal
					if (currx > selectx && curry < selecty && (currx - selectx == selecty - curry))
					{
						valid = 1;
						for (auto& w1 : wPiece)
						{
							if ((selectx < w1->x && selecty > w1->y) && (currx > w1->x && curry < w1->y))
							{
								if (currx - w1->x == w1->y - curry)
								{
									valid = 0;
								}
							}
						}
					}

					//right down diagonal
					if (currx > selectx && curry > selecty && (currx - selectx == curry - selecty))
					{
						valid = 1;
						for (auto& w1 : wPiece)
						{
							if ((selectx < w1->x && selecty < w1->y) && (currx > w1->x && curry > w1->y))
							{
								if (currx - w1->x == curry - w1->y)
								{
									valid = 0;
								}
							}
						}
					}

					//left up diagonal
					if (currx < selectx && curry < selecty && (selectx - currx == selecty - curry))
					{
						valid = 1;
						for (auto& w1 : wPiece)
						{
							if ((selectx > w1->x && selecty > w1->y) && (currx < w1->x && curry < w1->y))
							{
								if (w1->x - currx == w1->y - curry)
								{
									valid = 0;
								}
							}
						}
					}

					//left down diagonal
					if (currx < selectx && curry > selecty && (selectx - currx == curry - selecty))
					{
						valid = 1;
						for (auto& w1 : wPiece)
						{
							if ((selectx > w1->x && selecty < w1->y) && (currx < w1->x && curry > w1->y))
							{
								if (w1->x - currx == curry - w1->y)
								{
									valid = 0;
								}
							}
						}
					}

					//vertical movement
					if (currx == selectx && (curry < selecty || curry > selecty))
					{
						valid = 1;
						for (auto& w1 : wPiece)
						{
							if (w1->x == selectx)
							{
								if (curry < selecty && (curry < w1->y && selecty > w1->y))
								{
									valid = 0;
								}
								if (curry > selecty && (curry > w1->y && selecty < w1->y))
								{
									valid = 0;
								}
							}
						}
					}

					//horizontal movement
					if (curry == selecty && (currx < selectx || currx > selectx))
					{
						valid = 1;
						for (auto& w1 : wPiece)
						{
							if (w1->y == selecty)
							{
								if (currx < selectx && (currx < w1->x && selectx > w1->x))
								{
									valid = 0;
								}
								if (currx > selectx && (currx > w1->x && selectx < w1->x))
								{
									valid = 0;
								}
							}
						}
					}
				}

				//check moves for king
				if (w->piece == KING)
				{
					//right up
					if (currx == selectx + 1 && curry == selecty - 1)
					{
						valid = 1;
					}

					//right down
					if (currx == selectx + 1 && curry == selecty + 1)
					{
						valid = 1;
					}

					//left up
					if (currx == selectx - 1 && curry == selecty - 1)
					{
						valid = 1;
					}

					//left down
					if (currx == selectx - 1 && curry == selecty + 1)
					{
						valid = 1;
					}

					//up
					if (currx == selectx && curry == selecty - 1)
					{
						valid = 1;
					}

					//down
					if (currx == selectx && curry == selecty + 1)
					{
						valid = 1;
					}

					//left
					if (currx == selectx - 1 && curry == selecty)
					{
						valid = 1;
					}

					//right
					if (currx == selectx + 1 && curry == selecty)
					{
						valid = 1;
					}

					//other king up or down
					if (currx == king.x && (curry - 1 == king.y || curry + 1 == king.y))
					{
						valid = 0;
					}

					//other king left up diagonal or left down diagonal
					if (currx - 1 == king.x && (curry - 1 == king.y || curry + 1 == king.y))
					{
						valid = 0;
					}

					//other king right up diagonal or right down diagonal
					if (currx + 1 == king.x && (curry - 1 == king.y || curry + 1 == king.y))
					{
						valid = 0;
					}

					//other king right or left
					if (curry == king.y && (currx - 1 == king.x || currx + 1 == king.x))
					{
						valid = 0;
					}

					//if king is not in check it can castle	
					if (wking.check == 0)
					{
						//kings side castling
						if (currx == selectx - 2 && curry == selecty)
						{
							if (w->movesMade == 0 && wrook1.movesMade == 0)
							{
								valid = 1;
							}

							for (auto& b : bPiece)
							{
								if (b->y == 0)
								{
									if (b->x < wking.x && b->x > wrook1.x)
									{
										valid = 0;
									}
								}
							}

							for (auto& w1 : wPiece)
							{
								if (w1->y == 0)
								{
									if (w1->x < wking.x && w1->x > wrook1.x)
									{
										valid = 0;
									}
								}
							}

							if (valid == 1)
							{
								wrook1.movesMade++;
								wrook1.x = 2;
								col(0, 0, 0, 2, 8);

								w->x = currx;
								check();
								if (wking.check == 1)
								{
									w->x = selectx;
									wrook1.movesMade--;
									wrook1.x = 0;
									col(0, 2, 0, 0, 8);
									valid = 0;
								}
								w->x = selectx;
							}
						}

						//queens side castling
						if (currx == selectx + 2 && curry == selecty)
						{
							if (w->movesMade == 0 && wrook2.movesMade == 0)
							{
								valid = 1;
							}

							for (auto& b : bPiece)
							{
								if (b->y == 0)
								{
									if (b->x > wking.x && b->x < wrook2.x)
									{
										valid = 0;
									}
								}
							}

							for (auto& w1 : wPiece)
							{
								if (w1->y == 0)
								{
									if (w1->x > wking.x && w1->x < wrook2.x)
									{
										valid = 0;
									}
								}
							}

							if (valid == 1)
							{
								wrook2.movesMade++;
								wrook2.x = 4;
								col(0, 7, 0, 4, 8);

								w->x = currx;
								check();
								if (wking.check == 1)
								{
									w->x = selectx;
									wrook2.movesMade--;
									wrook2.x = 7;
									col(0, 4, 0, 7, 8);
									valid = 0;
								}
								w->x = selectx;
							}
						}
					}
				}

				for (auto& w1 : wPiece)
				{
					if (currx == w1->x && curry == w1->y)
					{
						valid = 0;
					}
					if (currx == king.x && curry == king.y)
					{
						valid = 0;
					}
				}

				if (valid == 1)
				{	
					w->x = currx;
					w->y = curry;
					w->movesMade++;
					
					//runs promotion
					if (w->piece == PAWN && w->y == 7)
					{
						char promotion = ' ';
						std::cout << "Pawn has been promoted, please choose a piece to promote to" << std::endl;
						std::cout << "enter Q, H, B, or R: ";
						std::cin >> promotion;
						if (promotion != 'Q' && promotion != 'H' && promotion != 'B' && promotion != 'R')
						{
							w->x = selectx;
							w->y = selecty;
							col(curry, currx, selecty, selectx, w->piece + 6);
							for (auto& b : bPiece)
							{
								if (currx == b->x && curry == b->y)
								{
									col(b->y, b->x, curry, currx, b->piece);
								}
							}
							drawBoard();
							std::cout << "must enter a valid promotion value" << std::endl;
							wMove();
							return;
						}
						if (promotion == 'Q')
						{
							w->piece = QUEEN;
						}
						if (promotion == 'H')
						{
							w->piece = HORSE;
						}
						if (promotion == 'B')
						{
							w->piece = BISHOP;
						}
						if (promotion == 'R')
						{
							w->piece = ROOK;
						}
					}

					for (auto& b : bPiece)
					{
						if (currx == b->x && curry == b->y)
						{
							b->death = 1;
							bDead++;
							b->dead(bDead);

							check();

							if (wking.check == 1)
							{
								col(b->y, b->x, curry, currx, b->piece);
								b->x = currx;
								b->y = curry;
								b->death = 0;
								bDead--;
								w->x = selectx;
								w->y = selecty;
								w->movesMade--;
								drawBoard();
								std::cout << "white is in check" << std::endl;
								wMove();
								return;
							}
							col(curry, currx, b->y, b->x, b->piece);
						}
						if (w->piece == PAWN)
						{
							if (currx == b->x && b->y == curry - 1 && b->enPassantCnt == 1)
							{
								b->death = 1;
								bDead++;
								b->dead(bDead);

								check();

								if (wking.check == 1)
								{
									col(b->y, b->x, curry - 1, currx, b->piece);
									b->x = currx;
									b->y = curry + 1;
									b->death = 0;
									bDead--;
									w->x = selectx;
									w->y = selecty;
									w->movesMade--;
									drawBoard();
									std::cout << "white is in check" << std::endl;
									wMove();
									return;
								}
								col(curry + 1, currx, b->y, b->x, b->piece);
							}
						}
					}

					check();

					if (wking.check == 1)
					{
						w->x = selectx;
						w->y = selecty;
						w->movesMade--;
						drawBoard();
						std::cout << "white is in check" << std::endl;
						wMove();
						return;
					}

					checkmate();
					stalemate();

					col(selecty, selectx, curry, currx, w->piece + 6);
					for (auto& b : bPiece)
					{
						if (b->piece == PAWN) 
						{
							b->enPassantCnt = 0;
						}
					}
					turn = 0;
					if (king.check == 1)
					{
						drawBoard();
						std::cout << "black is in check" << std::endl;
						return;
					}
					drawBoard();
				}
				else
				{
					if (wking.check == 1)
					{
						drawBoard();
						std::cout << "white is in check" << std::endl;
						wMove();
						return;
					}
					drawBoard();
					std::cout << "invalid move" << std::endl;
					wMove();
					return;
				}
			}
		}
		if (snum == 0)
		{
			drawBoard();
			std::cout << "no valid piece selected" << std::endl;
			wMove();
		}
	}
}

int main()
{
	defaultVectors();
	drawBoard();

	while (true)
		switch (win)
		{
		case 0:
			if (turn == 0)
			{
				bMove();
			}
			else
			{
				wMove();
			}
			break;
		case 1:
			drawBoard();
			std::cout << "black wins" << std::endl;
			return 0;
		case 2:
			drawBoard();
			std::cout << "white wins" << std::endl;
			return 0;
		case 3:
			drawBoard();
			std::cout << "draw white can't move" << std::endl;
			return 0;
		case 4:
			drawBoard();
			std::cout << "draw black can't move" << std::endl;
			return 0;
		default:
			drawBoard();
			std::cout << "stalemate" << std::endl;
			return 0;
		}
}
