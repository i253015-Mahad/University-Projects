#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <conio.h>

using namespace std;

#define boarder_size 10
#define AIRCRAFT_CARRIER 5
#define BATTLESHIP 4
#define DESTROYER 3
#define SUBMARINE 3
#define PATROL_BOAT 2

int ship_color = 0;
string ship_names[5] = {"Aircraft Carrier", "Battleship", "Destroyer", "Submarine", "Patrol Boat"};
int ship_sizes[5] = {5,4,3,3,2};



// Arrays to store both players' ship positions
int ship_row[10];        // indices 0-4: Player 1, 5-9: Player 2
int ship_col[10];
bool ship_vertical[10];
bool shipBoard[2][10][10]; //hiding ships and can be detected

// Global counters for storing ship positions
int player1_ship_count = 0; // Player 1: indices 0-4
int player2_ship_count = 5; // Player 2: indices 5-9

char board[10][10];  // Global board for game display

int player_turn = 1; // 1 = Player 1, 2 = Player 2
int mahad; //0 = player 1, 1 = player 2

//for calculating turns of each player
int p1 = 6, p2 = 6;
char pp[2][10][10];
int count = 0;

void turn_calc (char board[2][10][10]) //Mahad
{
	int total = 0;
	bool a = false, b = false, d = false, s = false, p = false;
		for (int j = 0; j < 10; j++)
		{
			for (int k = 0; k < 10; k++)
			{
				switch (board[mahad][j][k])
				{
					case 'A': a = true; break;
					case 'B': b = true; break;
					case 'D': d = true; break;
					case 'S': s = true; break;
					case 'P': p = true; break;
				}
				
			}
		}
		
	if (a == false)
	total++;
	
	if (b == false)
	total++;
	
	if (d == false)
	total++;
	
	if (s == false)
	total++;
	
	if (p == false)
	total++;
	
	cout<<total<<" ships have sunk!!\nTotal turns = "<<6-total<<"\n";
	if (mahad == 0)
	p1 = 6 - total;
	
	else
	p2 = 6 - total;
}


void setColor(int textColor, int bgColor) //Taham
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}


 
void printBoard(char board[10][10], bool hideShips) //Taham
{
    if(hideShips){
        cout << "Your ships have been placed.\n";}

  
    cout << "      ";

    // Print column headers (hardcoded)
    cout << " 0     1     2     3     4     5     6     7     8     9" << endl;

    // Top border
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+" << endl;

    // Row 0
    cout << "  0  ¦"; 
    for (int i = 0; i < 10; i++)
    {
            char cell = board[0][i];
        if (cell == '~') setColor(7,1);      
        else if (cell == 'A' || cell == 'B' || cell == 'D' || cell == 'S' || cell == 'P') setColor(0,ship_color);
        cout << "  " << cell << "  ";
          setColor(7,0);
        cout << "|";
    }
    cout << endl;
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----Â¦" << endl;

    // Row 1
    cout << "  1  ¦"; 
    for (int i = 0; i < 10; i++)
    {
         char cell = board[1][i];
        if (cell == '~') setColor(7,1);
        else if (cell == 'A' || cell == 'B' || cell == 'D' || cell == 'S' || cell == 'P') setColor(0,ship_color);
        cout << "  " << cell << "  ";
        setColor(7,0);
        cout << "|";
    }
    cout << endl;
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----Â¦" << endl;

    // Row 2
    cout << "  2  ¦"; 
    for (int i = 0; i < 10; i++)
    {
     char cell = board[2][i];
        if (cell == '~') setColor(7,1);
        else if (cell == 'A' || cell == 'B' || cell == 'D' || cell == 'S' || cell == 'P') setColor(0,ship_color);
        cout << "  " << cell << "  ";
        setColor(7,0);
        cout << "|";
    }   
    cout << endl;
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----Â¦" << endl;

    // Row 3
    cout << "  3  ¦"; 
    for (int i = 0; i < 10; i++)
    {
     char cell = board[3][i];
        if (cell == '~') setColor(7,1);
       else if (cell == 'A' || cell == 'B' || cell == 'D' || cell == 'S' || cell == 'P') setColor(0,ship_color);
        cout << "  " << cell << "  ";
        setColor(7,0);
        cout << "|";
    }
    cout << endl;
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----Â¦" << endl;

    // Row 4
    cout << "  4  ¦"; 
    for (int i = 0; i < 10; i++)
    {
      char cell = board[4][i];
        if (cell == '~') setColor(7,1);
      else if (cell == 'A' || cell == 'B' || cell == 'D' || cell == 'S' || cell == 'P') setColor(0,ship_color);
        cout << "  " << cell << "  ";
        setColor(7,0);
        cout << "|";
    }
    
    cout << endl;
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----Â¦" << endl;

    // Row 5
    cout << "  5  ¦"; 
    for (int i = 0; i < 10; i++)
    {
    char cell = board[5][i];
        if (cell == '~') setColor(7,1);
       else if (cell == 'A' || cell == 'B' || cell == 'D' || cell == 'S' || cell == 'P') setColor(0,ship_color);
        cout << "  " << cell << "  ";
        setColor(7,0);
        cout << "|";
    }
    cout << endl;
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----Â¦" << endl;

    // Row 6
    cout << "  6  ¦"; 
    for (int i = 0; i < 10; i++)
    {
    char cell = board[6][i];
        if (cell == '~') setColor(7,1);
     else if (cell == 'A' || cell == 'B' || cell == 'D' || cell == 'S' || cell == 'P') setColor(0,ship_color);
        cout << "  " << cell << "  ";
        setColor(7,0);
        cout << "|";
    }
    cout << endl;
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----Â¦" << endl;

    // Row 7
    cout << "  7  ¦"; 
    for (int i = 0; i < 10; i++)
    {
  char cell = board[7][i];
        if (cell == '~') setColor(7,1);
     else if (cell == 'A' || cell == 'B' || cell == 'D' || cell == 'S' || cell == 'P') setColor(0,ship_color);
        cout << "  " << cell << "  ";
        setColor(7,0);
        cout << "|";
    }
    cout << endl;
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----Â¦" << endl;

    // Row 8
    cout << "  8  ¦"; 
    for (int i = 0; i < 10; i++)
    {
    char cell = board[8][i];
        if (cell == '~') setColor(7,1);
        else if (cell == 'A' || cell == 'B' || cell == 'D' || cell == 'S' || cell == 'P') setColor(0,ship_color);
        cout << "  " << cell << "  ";
        setColor(7,0);
        cout << "|";
    }
    cout << endl;
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----Â¦" << endl;

    // Row 9
    cout << "  9  ¦"; 
    for (int i = 0; i < 10; i++)
    {
    char cell = board[9][i];
        if (cell == '~') setColor(7,1);
     else if (cell == 'A' || cell == 'B' || cell == 'D' || cell == 'S' || cell == 'P') setColor(0,ship_color);
        cout << "  " << cell << "  ";
        setColor(7,0);
        cout << "|";
    }
    cout << endl;

    // Bottom border
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
 
}


void initializeBoard(char board[10][10]) //Taham
{
    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++)
         board[i][j] = '~';
}


bool checking_overlaping(char board[10][10], int row, int col, int size, bool vertical) //Taham
{
    if(vertical == true)
    {
        if(row + size > 10) {
        return false;
                    }

                    for(int i=0;i<size;i++){
                    if(board[row+i][col] != '~') {
                    return false;}
                    }
    }
    else
    {
        if(col + size > 10) {
         return false;}

                    for(int i=0;i<size;i++){
                     if(board[row][col+i] != '~') {
                      return false;}
                        }
    }
    return true;
}


void placed_ship(char board[10][10], int row, int col, int size, bool vertical) //Taham
{
    if(vertical)
    {
        for(int i=0;i<size;i++){
        switch (size)
        {
        	case 5: {board[row+i][col] = 'A'; pp[mahad][row+i][col] = 'A'; break;}
        	case 4: {board[row+i][col] = 'B'; pp[mahad][row+i][col] = 'B'; break;}
        	case 2: {board[row+i][col] = 'P'; pp[mahad][row+i][col] = 'P'; break;}
        	case 3:
        		{
        			if (count == 2)
        			{board[row+i][col] = 'D'; pp[mahad][row+i][col] = 'D'; break;}
        			else
        			{board[row+i][col] = 'S'; pp[mahad][row+i][col] = 'S'; break;}
				}
		}
		}
    }

    else
        for(int i=0;i<size;i++){
        switch (size)
        {
        	case 5: {board[row][col+i] = 'A'; pp[mahad][row][col+i] = 'A'; break;}
        	case 4: {board[row][col+i] = 'B'; pp[mahad][row][col+i] = 'B'; break;}
        	case 2: {board[row][col+i] = 'P'; pp[mahad][row][col+i] = 'P'; break;}
        	case 3:
        		{
        			if (count == 2)
        			{board[row][col+i] = 'D'; pp[mahad][row][col+i] = 'D'; break;}
        			else
        			{board[row][col+i] = 'S'; pp[mahad][row][col+i] = 'S'; break;}
				}
		}
			}
				
	count++;
}


void random_placment(char board[10][10]) //Taham
{
    srand(time(0));
    for(int s=0;s<5;s++)
    {
        bool placed = false;
        while(!placed)
        {
            int row = rand() % 10;
             int col = rand()% 10;
        bool vertical = rand()%2;

            if(checking_overlaping(board,row,col,ship_sizes[s],vertical))
            {
                placed_ship(board,row,col,ship_sizes[s],vertical);
                placed = true;

                // Store ship coordinates using player_turn
                if(player_turn == 1)
                {
                    ship_row[player1_ship_count]= row;
                    ship_col[player1_ship_count] =col;
                    ship_vertical[player1_ship_count] = vertical;
                    player1_ship_count++;
                }
                else
                {
                    ship_row[player2_ship_count] =row;
                    ship_col[player2_ship_count] = col;
                    ship_vertical[player2_ship_count]= vertical;
                    player2_ship_count++ ;
                }
            }
        }
    }
}

//making the side board in game board
void side_board (char player[10][10], char computer[10][10], int n = 1) //Mahad
{
	static int axis = 0;
	cout<<"  "<<axis;
	
	for (int i = 0; i < 10; i++)
	{
		if (n == 2)
		{
			cout<<" "<<player[axis][i]<<" ";
		}
		else
		{
			cout<<" "<<computer[axis][i]<<" ";
		}
	}
	cout<<"\t";
	if (n == 2)
	{
		axis++;
	}
	if (axis == 10)
	{
		axis = 0;
	}
}

//making the game board
void game_board(char board[10][10], char player[10][10], char computer[10][10]) // Mahad
{
	

    // Print column headers (hardcoded)
    cout<<"\t     Enemy Board";
    cout << "\t\t       0     1     2     3     4     5     6     7     8     9\t\t\tPlayer Board" << endl;

    // Top border
    cout << "\t\t\t\t\t    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+" << endl;

    // Row 0
    cout<<"    0  1  2  3  4  5  6  7  8  9\t"; //side board
    cout << "  0 ¦"; 
    for (int i = 0; i < 10; i++)
    {
        char cell = board[0][i];
        if (cell == 'X') { setColor(15, 12); cout << "  X  "; setColor(7,0); }
        else if (cell == 'O') { setColor(0, 8); cout << "  O  "; setColor(7,0); }
		else { setColor(7, 1); cout << "  ~  "; setColor(7,0); }
        cout << "¦";
    }
    cout<<"\t0  1  2  3  4  5  6  7  8  9"; //side board
    cout << endl;
    side_board(player, computer);
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----¦   "; 
    side_board(player, computer, 2);
	cout<< endl;

    // Row 1
    side_board(player, computer);
    cout << "  1 ¦"; 
    for (int i = 0; i < 10; i++)
    {
        char cell = board[1][i];
        if (cell == 'X') { setColor(15, 12); cout << "  X  "; setColor(7,0); }
        else if (cell == 'O') { setColor(0, 8); cout << "  O  "; setColor(7,0); }
		else { setColor(7, 1); cout << "  ~  "; setColor(7,0); }
        cout << "¦";
    }
    cout<<"   ";
    side_board(player, computer, 2);
    cout << endl;
    side_board(player, computer);
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----¦   "; 
	side_board(player, computer, 2);
	cout<< endl;

    // Row 2
    side_board(player, computer);
    cout << "  2 ¦"; 
    for (int i = 0; i < 10; i++)
    {
        char cell = board[2][i];
        if (cell == 'X') { setColor(15, 12); cout << "  X  "; setColor(7,0); }
        else if (cell == 'O') { setColor(0, 8); cout << "  O  "; setColor(7,0); }
		else { setColor(7, 1); cout << "  ~  "; setColor(7,0); }
        cout << "¦";
    }
    cout<<"   ";
    side_board(player, computer, 2);
    cout << endl;
    side_board(player, computer);
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----¦   "; 
	side_board(player, computer, 2);
	cout<< endl;

    // Row 3
    side_board(player, computer);
    cout << "  3 ¦"; 
    for (int i = 0; i < 10; i++)
    {
        char cell = board[3][i];
        if (cell == 'X') { setColor(15, 12); cout << "  X  "; setColor(7,0); }
        else if (cell == 'O') { setColor(0, 8); cout << "  O  "; setColor(7,0); }
		else { setColor(7, 1); cout << "  ~  "; setColor(7,0); }
        cout << "¦";
    }
    cout<<"   ";
    side_board(player, computer, 2);
    cout << endl;
    side_board(player, computer);
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----¦   "; 
	side_board(player, computer, 2);
	cout<< endl;

    // Row 4
    side_board(player, computer);
    cout << "  4 ¦"; 
    for (int i = 0; i < 10; i++)
    {
        char cell = board[4][i];
        if (cell == 'X') { setColor(15, 12); cout << "  X  "; setColor(7,0); }
        else if (cell == 'O') { setColor(0, 8); cout << "  O  "; setColor(7,0); }
		else { setColor(7, 1); cout << "  ~  "; setColor(7,0); }
        cout << "¦";
    }
    cout<<"   ";
    side_board(player, computer, 2);
    cout << endl;
    side_board(player, computer);
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----¦   "; 
	side_board(player, computer, 2);
	cout<< endl;

    // Row 5
    side_board(player, computer);
    cout << "  5 ¦"; 
    for (int i = 0; i < 10; i++)
    {
        char cell = board[5][i];
        if (cell == 'X') { setColor(15, 12); cout << "  X  "; setColor(7,0); }
        else if (cell == 'O') { setColor(0, 8); cout << "  O  "; setColor(7,0); }
		else { setColor(7, 1); cout << "  ~  "; setColor(7,0); }
        cout << "¦";
    }
    cout<<"   ";
    side_board(player, computer, 2);
    cout << endl;
    cout << "\t\t\t\t\t    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----¦"<< endl;

    // Row 6
    cout << "\t\t\t\t\t  6 ¦"; 
    for (int i = 0; i < 10; i++)
    {
        char cell = board[6][i];
        if (cell == 'X') { setColor(15, 12); cout << "  X  "; setColor(7,0); }
        else if (cell == 'O') { setColor(0, 8); cout << "  O  "; setColor(7,0); }
		else { setColor(7, 1); cout << "  ~  "; setColor(7,0); }
        cout << "¦";
    }
    cout << endl;
    cout << "\t\t\t\t\t    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----¦" << endl;

    // Row 7
    cout << "\t\t\t\t\t  7 ¦"; 
    for (int i = 0; i < 10; i++)
    {
        char cell = board[7][i];
        if (cell == 'O') { setColor(0, 8); cout << "  O  "; setColor(7,0); }
        else if (cell == 'X') { setColor(15, 12); cout << "  X  "; setColor(7,0); }
		else { setColor(7, 1); cout << "  ~  "; setColor(7,0); }
        cout << "¦";
    }
    cout << endl;
    cout << "\t\t\t\t\t    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----¦" << endl;

    // Row 8
    cout << "\t\t\t\t\t  8 ¦"; 
    for (int i = 0; i < 10; i++)
    {
        char cell = board[8][i];
        if (cell == 'X') { setColor(15, 12); cout << "  X  "; setColor(7,0); }
        else if (cell == 'O') { setColor(0, 8); cout << "  O  "; setColor(7,0); }
		else { setColor(7, 1); cout << "  ~  "; setColor(7,0); }
        cout << "¦";
    }
    cout << endl;
    cout << "\t\t\t\t\t    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----¦" << endl;

    // Row 9
    cout << "\t\t\t\t\t  9 ¦"; 
    for (int i = 0; i < 10; i++)
    {
        char cell = board[9][i];
        if (cell == 'X') { setColor(15, 12); cout << "  X  "; setColor(7,0); }
        else if (cell == 'O') { setColor(0, 8); cout << "  O  "; setColor(7,0); }
		else { setColor(7, 1); cout << "  ~  "; setColor(7,0); }
        cout << "¦";
    }
    cout << endl;

    // Bottom border
    cout << "\t\t\t\t\t    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+" << endl;

}

//clear function
void clearScreen() //Mahad
{
	system("CLS");
}

//clearing the board for next player
void clearBoard(char board[10][10]) //Mahad
{
    // Initialize 10x10 board with water '~'
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            board[i][j] = '~'; 
}

//winning condition
 void Win (char player[10][10],char computer[10][10]) //Mahad
 {
    bool lost = true;
 	
 	// checkig if player 1 won
 	for (int i = 0; i < 10; i++)
 	{
 		for (int j = 0; j < 10; j++)
 		{
            if(pp[mahad][i][j]== 'A' || pp[mahad][i][j]== 'B' || pp[mahad][i][j]== 'D' || pp[mahad][i][j]== 'S' || pp[mahad][i][j]== 'P'){
                lost = false;
            }
		}
	}
	if (lost && mahad == 0)
	{
		cout<<"Player 1 Lost :(";
		exit(0);
	}
	
	//checking if player 2 won
	if(lost && mahad == 1)
    {
  cout<<"Player 1 Won!! :)\n";
        exit(0);
    }
}
//computer random attack
void computerAttack (char playerBoard[10][10], int &computerScore) //Mahad
{
	srand(time(0));
	int row, column;	
	
	//getting proper coordinates
	for (int i = 0; i < p2; i++)
	{
		do
	{
		row = rand() % 10;
		column = rand() % 10;
	}
	while (playerBoard[row][column] == 'X' || playerBoard[row][column] == 'O');
	
	if (pp[mahad][row][column] == 'A' || pp[mahad][row][column] == 'B' || pp[mahad][row][column] == 'D' || pp[mahad][row][column] == 'S'
	|| pp[mahad][row][column] == 'P')
	{
		playerBoard[row][column] = 'X';
		board[row][column] = 'X';
		pp[mahad][row][column] = 'X';
		computerScore += 10;
	}
	else
	{
		playerBoard[row][column] = 'O';
		board[row][column] = 'O';
		pp[mahad][row][column] = 'O';
		computerScore -= 1;
	}
	}
}

void playerAttack (char computerBoard[10][10], int &playerScore) //Mahad
{
	int row, col, turn;
	if (mahad == 1)
	{
		turn = p1;
	}
	else
	{
		turn = p2;
	}
	for (int i = 0; i < turn; i++)
	{
	cout<<"Enter coordinates of attack (row and column): ";
	cin>>row>>col;
	while ((row < 0 || row > 9) || (col < 0 || col > 9) || (computerBoard[row][col] == 'X' || computerBoard[row][col] == 'O'))
	{
		cout<<"Enter a valid input: ";
		cin>>row>>col;
	}
	if (pp[mahad][row][col] == 'A' || pp[mahad][row][col] == 'B' || pp[mahad][row][col] == 'D' || pp[mahad][row][col] == 'S'
	|| pp[mahad][row][col] == 'P')
	{
		computerBoard[row][col] = 'X';
		board[row][col] = 'X';
		pp[mahad][row][col] = 'X';
        playerScore += 10;
	}
	else
	{
		computerBoard[row][col] = 'O';
		board[row][col] = 'O';
		pp[mahad][row][col] = 'O';
        playerScore -= 1;

	}
	}
}

// vs computer func main
void vsComputer (char pboard[10][10], char cboard[10][10]) // Mahad
{
	int c = 0, p = 0;
	game_board(board, pboard, cboard);
	for (int i = 0; i < 200; i++)
	{
	  clearBoard(board);
	  mahad = 1;
	  cout<<"Your turn:\n";
	  playerAttack (cboard, p);
	  clearScreen();
	  cout<<"\t\t\t\t\t\t\t\t    Updated Board\n\n";
	  game_board(board, pboard, cboard);
	  Win (cboard, pboard);
	  cout<<"Press enter to continue: ";
	  getch();
	
	  turn_calc(pp);
	  clearBoard(board);
	  mahad = 0;
	  cout<<"Computer's turn:\n";
	  computerAttack(pboard, c);
	  clearScreen();
	  cout<<"\t\t\t\t\t\t\t\t    Updated Board\n\n";
	  game_board(board, pboard, cboard);
	  Win (pboard, cboard);
	  turn_calc(pp);
    }
}

// vs player func main
void vsPlayer (char board1[10][10], char board2[10][10]) //Mahad
{
	//playing the game
	game_board(board, board1, board2);
  int p1 = 0, p2 = 0;
  for (int i = 0; i < 200; i++)
  {
  	clearBoard(board);
  	mahad = 1;
  	cout<<"Player 1 turn\n";
  	playerAttack(board2, p1);
  	clearScreen();
  	cout<<"Updated board\n";
  	game_board(board, board1, board2);
  	Win (board2, board1);
  	turn_calc(pp);
  	
  	//player 2
  	clearBoard(board);
  	mahad = 0;
  	cout<<"Player 2 turn\n";
  	playerAttack(board1, p2);
  	clearScreen();
  	cout<<"Updated board\n";
  	game_board(board, board1, board2);
  	Win (board1, board2);
  	turn_calc (pp);
  }
}


void manual_placment(char board[10][10]) //Taham
{
    for(int s=0;s<5;s++)
    {
        int row, col;
        char vert;
        bool placed = false;
        while(placed ==false)
        {
            cout<<"Placing "<<ship_names[s]<<"     "<< ship_sizes[s] <<endl;
            cout<<  "Enter starting row (0-9)"<<endl;
            cin>> row;
            cout<<"Enter starting column (0-9)"<<endl;
            cin >> col;
            cout<< "Do you want to place Vertically  (y/n) ";
            cin >> vert;
           bool vertical;

                if(vert == 'y' || vert == 'Y'){
                    vertical = true;
                }
                else
                 vertical = false;


            if(checking_overlaping(board,row,col,ship_sizes[s],vertical))
            {
                placed_ship(board,row,col,ship_sizes[s],vertical);
                placed = true;

                // Store ship coordinates using player_turn
                if(player_turn == 1)
                {
                    ship_row[player1_ship_count] = row;
                    ship_col[player1_ship_count] = col;
                    ship_vertical[player1_ship_count] = vertical;
                    player1_ship_count++;
                }
                else
                {
                    ship_row[player2_ship_count] = row;
                    ship_col[player2_ship_count] = col;
                    ship_vertical[player2_ship_count] = vertical;
                    player2_ship_count++;
                }
            }
            else
                cout << "Error ,try again.\n";
        }
        printBoard(board,false);
    }
}


void setupBoard(char board[10][10]) //Taham
{
    initializeBoard(board);
    cout<<"Choose options "<<endl;
    cout<<"1. Manual"<<endl;
    cout<<"2. Random"<<endl;
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 2)
    {
    	cout<<"Enter valid input: ";
    	cin>>choice;
	}

    if(choice == 1)
        manual_placment(board);
    else
        random_placment(board);

    cout << "Do you want to hide your ships? (y/n): ";
    char hide; cin >> hide;
    bool hideShips = (hide=='y' || hide=='Y');
    printBoard(board, hideShips);
}

void showGameMenu () //Taham
{
	 srand(time(0));
    char playerBoard[boarder_size][boarder_size];
    char opponentBoard[boarder_size][boarder_size];
    cout << "==================================================" << endl;
    cout << "            WELCOME TO BATTLESHIP GAME" << endl;
    cout << "==================================================" << endl;
    cout << endl;
    cout << "                    MAIN MENU" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << endl;
    cout << "1.  Start New Game" << endl;
    cout << endl;
    cout << "2.  Instructions" << endl;
    cout << endl;
    cout << "3.  View Leaderboard" << endl;
    cout << endl;
    cout << "4.  Exit" << endl;
    cout << endl;
    cout << "--------------------------------------------------" << endl;
    cout << endl;
    cout << "Enter your choice (1-4): ";

    int menu_selection;
    cin>>menu_selection;
    cin.ignore();
    while (menu_selection < 1 || menu_selection > 4)
    {
    	cout<<"Enter a valid input: ";
    	cin>>menu_selection;
	}
    
    if (menu_selection == 1)
{
	for (int i = 0; i < 10; i++){
     for(int j = 0; j < 10; j++)
      {pp[0][i][j] = '~';}}
      
      for (int i = 0; i < 10; i++){
     for(int j = 0; j < 10; j++)
      {pp[1][i][j] = '~';}
      }
	clearScreen();
    cout << "--------------------------------------------------" << endl;
    cout << "                  START NEW GAME" << endl; 
    cout << "--------------------------------------------------" << endl;
      
    cout<<"do you want to play\n";
    cout<<"1. Player Vs Player\n";
    cout<<"2. Comp Vs Player\n";

    int mode;
    cin>>mode;
    while (mode < 1 || mode > 2)
    {
    	cout<<"Enter a valid input: ";
    	cin>>mode;
	}
	clearScreen();
    
    char player1Board[10][10];
    char player2Board[10][10];
    char computerBoard[10][10];
    
    if (mode == 1){
    cout<<"Player 1"<<endl;
    player_turn = 1;
	mahad = 0;    
cout << "Select your ship color from the followings "<<endl;;
cout << " 1 = Blue , 2 = Green , 3 = Cyan , 4 = Red  , 5 = Magenta , 6 = Yellow , 7 = White"<<endl;;
cin>>ship_color;
    
	count = 0;    
    setupBoard(player1Board);
    
    cout<<"\n\n";
    cout<<"Press any button to continue... ";
    getch();
    clearBoard(player1Board);
    clearScreen();

    cout<<"Player 2"<<endl;
    player_turn = 2;
	mahad = 1;     
	cout << "Select your ship color from the followings "<<endl;;
    cout << " 1 = Blue , 2 = Green , 3 = Cyan , 4 = Red  , 5 = Magenta , 6 = Yellow , 7 = White"<<endl;;
    cin>>ship_color;
	
	count = 0;       
    setupBoard(player2Board);
    
    
    cout<<"Press any button to start the game.... ";
    getch();
    clearBoard(player2Board);
    clearScreen();
    
    vsPlayer (player1Board, player2Board);

    /*cout<<"Player 1 Board :\n";
    printBoard(player1Board,true);

    cout<<"Player 2 Board :\n";
    printBoard(player2Board,true);*/

  
//for understanding of where the ships had been placed
/*cout<<"Player 1 Ships \n";
for(int i = 0; i < 5; i++)
{
    cout<< ship_names[i] ;
    cout<<"Row =  "<< ship_row[i] ;
    cout<<"Col =  "<< ship_col[i] ;
cout<<"Vertical = ";
if(ship_vertical[i] == true)
    cout<<"V";
else
    cout<<"H";
cout<<endl;

}

//for understanding of where the ships had been placed
cout << "\nPlayer 2 Ships \n";
for(int i = 5; i < 10; i++)
{
    cout<< ship_names[i - 5] ;
    cout<<"Row  =   "<<ship_row[i]; 
    cout<<"Col =  "<<ship_col[i]; 
   cout<<"Vertical =  ";

if(ship_vertical[i] == true)
{
    cout<<"V";
}
else
    cout <<"H";
cout<<endl;

}*/
}
if (mode == 2)
{
    cout<<"Player 1"<<endl;
    player_turn = 1; 
    count = 0;
    mahad = 0;
	cout << "Select your ship color from the followings "<<endl;;
    cout << " 1 = Blue , 2 = Green , 3 = Cyan , 4 = Red  , 5 = Magenta , 6 = Yellow , 7 = White"<<endl;
    cin>>ship_color;           
    setupBoard(player1Board);
    cout<<"Press any button to continue... ";
    getch();
    clearBoard(player1Board);
    clearScreen();
    
  
    cout<<"Computer"<<endl;
    mahad = 1;
    count = 0;
    initializeBoard(computerBoard);
    random_placment(computerBoard);

    cout<<"Computer ships placed.\n\nPress any button to start the game ";
    getch();
    clearBoard(computerBoard);
    clearScreen();
    vsComputer(player1Board, computerBoard);


    /*cout << "Player Board:\n";
    printBoard(playerBoard, false);

    cout << "Computer Board (hidden):\n";
    printBoard(computerBoard, true);*/

}
}
if(menu_selection ==2)
{
	clearScreen();
    cout << "--------------------------------------------------" << endl;
    cout << "                   INSTRUCTIONS" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << endl;

   
    cout <<"1. Place your ships on the board." << endl;
    cout << endl; 
    
    cout <<"2. You and the computer take turns firing shots." << endl;
    cout << endl;

    cout <<"3. 'O' means MISS, 'X' means HIT." << endl;
    cout << endl;

    cout <<"4. Sink all enemy ships to win!" << endl;
    cout << endl;

    cout <<"5. Your score is based on accuracy and speed." << endl;
    cout << endl;

    cout << "--------------------------------------------------" << endl;
    cout << endl;

    cout << "(Press any key to return to Main Menu...)";

    char back;
    cin>>back;
    if(back != '\0')
    {
    	clearScreen();
        showGameMenu ();
    }
}

if(menu_selection ==3)
{
    //logic of leader boader will be place here
}
if(menu_selection ==4)
{
    exit(0);
    
}



}
int main() { //Taham
    /*char player1Board[10][10];
    char player2Board[10][10];
    char computerBoard[10][10];*/

    showGameMenu(); // shows main menu

    // Example for Player vs Computer:
    /*initializeBoard(player1Board);
    initializeBoard(computerBoard);

    player_turn = 1;
    cout << "Place your ships (Player):\n";
    setupBoard(player1Board);

    cout << "Placing computer ships...\n";
    player_turn = 2;
    random_placment(computerBoard);

    int playerScore = 0, computerScore = 0;

    // Game loop
    while (true) {
        clearScreen();
        cout << "\t\t\t\t\t\t\t\t    Updated Board\n\n";
        game_board(board, player1Board, computerBoard);

        cout << "Player turn:\n";
        playerAttack(computerBoard, playerScore);
        Win(player1Board, computerBoard);

        cout << "Computer turn:\n";
        computerAttack(player1Board, computerScore);
        Win(player1Board, computerBoard);

        getch(); // wait for key press between turns like you should
    }*/

    return 0;
}

   
