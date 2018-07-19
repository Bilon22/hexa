#include <iostream>
#include <conio.h>//sterowanie klawiatura
#include <string>//biblioteka dodaje string
#include <unistd.h>//potrzebne tylko do funkcji Sleep()
#include <windows.h>//potrzebne tylko do funkcji srand()
#include <ctime> //pobiera czas z PC. Potrzebne do generowania liczb pseudolosowych
#include <stdlib.h> // uzyta do system("PAUSE");


using namespace std;

class Map{
	public:
		
	int board[3][3] = {{1,1,1}, {0,0,0}, {-1,-1,-1}};
	int round = 0;
	

	string player(int player){
		if(player == 1)return "x";
		else if(player == -1)return "o";
		else return " ";
	}
	int refreshBoard(int board[3][3], int round){
		
		system( "cls" );
		
		cout<< " |______"<<endl;
		cout<< "1|"<<player(board[0][0])<<"|"<<player(board[0][1])<<"|"<<player(board[0][2])<<"|"<<endl;
		cout<< " |______"<<endl;
		cout<< "2|"<<player(board[1][0])<<"|"<<player(board[1][1])<<"|"<<player(board[1][2])<<"|"<<endl;
		cout<< " |______"<<endl;
		cout<< "3|"<<player(board[2][0])<<"|"<<player(board[2][1])<<"|"<<player(board[2][2])<<"|"<<endl;
		cout<< "_|______"<<endl;
		cout<< " |A B C "<<endl;
	
		if(round%2==0){
			cout << "Tura gracza" << endl;
		}
		else {
			cout << "Tura PC" << endl;
		}
	}	
	int checkWin(int board[3][3], int player){
		
		int pawns = 0;
		int possibleMoves = 0;
		int enemy = 0;
		
		if(player%2 == 0){
			for(int x = 0;x < 3; x++){
				for(int y = 0; y < 3; y++){
					if(board[x][y] == -1)pawns++;
					if(x<2){
						if(board[x][y] == 0 && board[x+1][y] == -1){
							possibleMoves++;
						}
					}
					if(x<2 && y>0){
						if(board[x][y] == 1 && board[x+1][y-1] == -1){
							possibleMoves++;
						}
					}
					if(x<2 && y<2){
						if((board[x][y] == 1) && (board[x+1][y+1] == -1)){
							possibleMoves++;
						}
					}
					if(x == 2){
						if(board[x][y] == 1)enemy++;
					}
				}
			}
			if(pawns == 0 || possibleMoves == 0 ||enemy > 0) return -1;
		}
		else{
			for(int x = 0;x < 3; x++){
				for(int y = 0; y < 3; y++){
					if(board[x][y] == 1)pawns++;
					if(x>0){
						if(board[x][y] == 0 && board[x-1][y] == 1)possibleMoves++;
					}
					if(x>0 && y<2){
						if(board[x][y] == -1 && board[x-1][y+1] == 1)possibleMoves++;
					}
					if(x>0 && y>0){
						if(board[x][y] == -1 && board[x-1][y-1] == 1)possibleMoves++;
					}
					if(x == 0){
						if(board[x][y] == -1)enemy++;
					}
				}
			}
			if(pawns == 0 || possibleMoves == 0 ||enemy > 0) return -1;
		}
		return 0;
	}
	int tableMove(int board[3][3], int round, string move){
		
		for(;;){
			int possible = 0;
			
			for(int x = 0;x < 3; x++){
				for(int y = 0; y < 3; y++){
					if(x<2){
						if(board[x][y] == 0 && board[x+1][y] == -1){
							if(x+1 == ((int)move[0])-49 && x == ((int)move[2])-49 && y == ((int)move[1])-65 && y == ((int)move[3])-65)possible++;
						}
					}
					if(x<2 && y>0){
						if(board[x][y] == 1 && board[x+1][y-1] == -1){
							if(x+1 == ((int)move[0])-49 && x == ((int)move[2])-49 && y-1 == ((int)move[1])-65 && y == ((int)move[3])-65)possible++;
						}
					}
					if(x<2 && y<2){
						if((board[x][y] == 1) && (board[x+1][y+1] == -1)){
							if(x+1 == ((int)move[0])-49 && x == ((int)move[2])-49 && y+1 == ((int)move[1])-65 && y == ((int)move[3])-65)possible++;
						}
					}
				}
			}
			
			if(possible == 1){
				board[((int)move[0])-49][((int)move[1])-65] = 0;
				if(round%2 == 0){
					board[((int)move[2])-49][((int)move[3])-65] = -1;
				}
				else{
					board[((int)move[2])-49][((int)move[3])-65] = -1;
				}
				break;
			}
			else{
				refreshBoard(board, round);
				cout<<"Ruch nieprawidlowy"<<endl;
				cout<<"Wykonaj prawidlowy ruch"<<endl;
				cin>>move;
			}
		}
	}	
	int PCMove(int board[3][3], int round){
	Sleep(500);
	for(int x = 0; x < 10; x++){
		srand(time( NULL ));
		int random = rand()%3;
		if(x/3>0){
			if(board[x/3][x%3] == 0 && board[x/3-1][x%3] == 1 && random == 0){
				board[x/3][x%3] = 1;
				board[x/3-1][x%3] = 0;
				break;
			}
		}
		if(x/3>0 && x%3<2){
			if(board[x/3][x%3] == -1 && board[x/3-1][x%3+1] == 1 && random == 1){
				board[x/3][x%3] = 1;
				board[x/3-1][x%3+1] = 0;
				break;
			}
		}
		if(x/3>0 && x%3>0){
			if(board[x/3][x%3] == -1 && board[x/3-1][x%3-1] == 1 && random == 2){
				board[x/3][x%3] = 1;
				board[x/3-1][x%3-1] = 0;
				break;
			}
		}
		if(x == 9)x = 0;
	}
}
};

int game() {
	string move;
	Map g;
	
	for(;;){
		if(g.round%2==0){
			g.refreshBoard(g.board, g.round);
			if(g.checkWin(g.board, g.round) == -1){
				break;
			}	
			cin >> move;
			g.tableMove(g.board, g.round, move);
			g.refreshBoard(g.board, g.round);
			g.round++;
		}
		else{
			g.refreshBoard(g.board, g.round);	
			if(g.checkWin(g.board, g.round) == -1){
				break;
			}
			g.PCMove(g.board, g.round);
			g.refreshBoard(g.board, g.round);
			g.round++;
		}
	}
	if(g.round%2 == 0)cout<<"Wygral PC"<<endl;
	if(g.round%2 == 1)cout<<"Wygral gracz!"<<endl;
	
	system ("PAUSE");
}
int aboutMe(){
	system( "cls" );
	cout << "Im fine guy" << endl;
	system ("PAUSE");
}
int aboutGame(){
	system( "cls" );
	cout << "This is fine game" << endl;
	system ("PAUSE");
}
void menuShow(int position){
	system( "cls" );
	cout << "HEXAPAWN" << endl;
	cout << "=============="<< endl;
	cout << "Play"<< endl;
	if(position == 0){
		cout << "_^_^_^_^_^_"<<endl;
	}
	cout << "About me"<< endl;
	if(position == 1){
		cout << "_^_^_^_^_^_"<<endl;
	}
	cout << "About game"<< endl;
	if(position == 2){
		cout << "_^_^_^_^_^_"<<endl;
	}
	cout << "Exit"<< endl;
	if(position == 3){
		cout << "_^_^_^_^_^_"<<endl;
	}
}
int main() {
	
	int menu = 0;
	int button;
	
	for(;;){
		menuShow(menu);
	    button = getch();
        switch(button){
            case 72:
            	menu--;
                break;
            case 80: 
            	menu++;
                break;
            case 13:
            	switch(menu){
            		case 0:
            			game();
            			break;
            		case 1:
            			aboutMe();
            			break;
            		case 2:
            			aboutGame();
            			break;
            		case 3:
            			return 0;
            			break;
				}
            button = 0;
        }
        if(menu > 3)menu = 0;
        if(menu < 0)menu = 3;
        menuShow(menu);
	}
}
