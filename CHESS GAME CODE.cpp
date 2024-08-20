#include <iostream>
#include <vector>
#include <cstdlib>
#include <bits/stdc++.h>
#include <math.h>
#include <string.h>
#define nullptr NULL

using namespace std;

// Define the ChessPiece class
class ChessPiece {
private:
	int X;
	int Y;
    char m_color;
    char m_type;
public:
    ChessPiece(char color, char type,int x,int y) : m_color(color), m_type(type), X(x), Y(y){}
    virtual ~ChessPiece() {

    }
    char getColor() const { 
        return m_color; 
        }
    char getType() const {
        return m_type; 
        }
    int getX(){
    	return X;
	}
	int getY(){
		return Y;
	}
	void setXY(int a,int b){
		X = a;Y = b;
	}
   virtual bool isValidMove(int toX, int toY, const vector<vector<ChessPiece*> >& board)= 0;
};

// Define the individual chess piece classes

class Pawn : public ChessPiece {
public:
	
    Pawn(char color,int x,int y) : ChessPiece(color, 'P',x,y) {}
    bool isValidMove(int toX, int toY, const vector<vector<ChessPiece*> >& board){
    	//cout << getX() << " " << getY() << " "<<toX << " " << toY << endl;
        if (getColor() == 'W') {
            if (getY() == toY) {  // Pawn can only move straight
                if (getX() == 1) {  // First move of Pawn
                    if (toX == 2 || toX == 3) {
                        if (board[toX][toY] == nullptr) {
                            return true;
                        }
                    }
                } else {  // All other moves of Pawn
                    if (toX == getX() + 1) {
                        if (board[toX][toY] == nullptr) {
                            return true;
                        }
                    }
                }
            } else {  // Pawn can only capture diagonally
                if (toX == getX() + 1 && abs(toY - getY()) == 1) {
                    if (board[toX][toY] != nullptr && board[toX][toY]->getColor() == 'B') {
                        return true;
                    }
                }
            }
        } else {  // Black Pawn
            if (getY() == toY) {  // Pawn can only move straight
                if (getX() == 6) {  // First move of Pawn
                    if (toX == 5 || toX == 4) {
                        if (board[toX][toY] == nullptr) {
                            return true;
                        }
                    }
                } else {  // All other moves of Pawn
                    if (toX == getX() - 1) {
                        if (board[toX][toY] == nullptr) {
                            return true;
                        }
                    }
                }
            } else {  // Pawn can only capture diagonally
                if (toX == getX() - 1 && abs(toY - getY()) == 1) {
                    if (board[toX][toY] != nullptr && board[toX][toY]->getColor() == 'W') {
                        return true;
                    }
                }
            }
        }
        return false;
    }
};

class Rook : public ChessPiece {
public:
    Rook(char color,int x,int y) : ChessPiece(color, 'R',x,y) {}
    bool isValidMove(int toX, int toY, const vector<vector<ChessPiece*> >& board){
        if (getX() == toX) {
            int minY = min(getY(), toY);
            int maxY = max(getY(), toY);
            for (int y = minY + 1; y < maxY; ++y) {
                if (board[getX()][y] != nullptr) {
                    return false;
                }
            }
            if (board[toX][toY] == nullptr || board[toX][toY]->getColor() != getColor()) {
                return true;
            }
        } else if (getY() == toY) {
            int minX = min(getX(), toX);
            int maxX = max(getX(), toX);
            for (int x = minX + 1; x < maxX; ++x) {
                if (board[x][getY()] != nullptr) {
                    return false;
                }
            }
            if (board[toX][toY] == nullptr || board[toX][toY]->getColor() != getColor()) {
                return true;
            }
        }
        return false;
    }
};


class Knight : public ChessPiece {
public:
    Knight(char color, int x, int y) : ChessPiece(color, 'N', x, y) {}
    
    bool isValidMove(int toX, int toY, const vector<vector<ChessPiece*> >& board) {
        int dx = (toX - getX());
        int dy = (toY - getY());
        if ((abs(dx) == 1 && abs(dy) == 2) || (abs(dx) == 2 && abs(dy) == 1)) {
            if (board[toY][toX] == nullptr || board[toY][toX]->getColor() >= getColor() ||board[toY][toX]->getColor() <= getColor()) {
                return true;
            }
        }
        return false;
        
    }
};


class Bishop : public ChessPiece {
public:
    Bishop(char color,int x,int y) : ChessPiece(color, 'B',x,y) {}

    bool isValidMove(int toX, int toY, const vector<vector<ChessPiece*> >& board){
        if (board[toX][toY] != nullptr && board[toX][toY]->getColor() == this->getColor()) {
            return false;
        }
        int deltaX = toX - getX();
        int deltaY = toY - getY();
        if (abs(deltaX) != abs(deltaY)) {
            return false;
        }
        int xDir = (deltaX > 0) ? 1 : -1;
        int yDir = (deltaY > 0) ? 1 : -1;
        int x = getX() + xDir;
        int y = getY() + yDir;
        while (x != toX && y != toY) {
            if (board[x][y] != nullptr) {
                return false;
            }
            x += xDir;
            y += yDir;
        }
        return true;
    }
};



class Queen : public ChessPiece {
public:
    Queen(char color,int x,int y) : ChessPiece(color, 'Q',x,y) {}

    bool isValidMove(int toX, int toY, const vector<vector<ChessPiece*> >& board){
        if (getX() == toX || getY() == toY) {
            if (getX() == toX) {
                int minY = min(getY(), toY);
                int maxY = max(getY(), toY);
                for (int y = minY + 1; y < maxY; y++) {
                    if (board[getX()][y] != nullptr) {
                        return false;
                    }
                }
            } else { 
                int minX = min(getX(), toX);
                int maxX = max(getX(), toX);
                for (int x = minX + 1; x < maxX; x++) {
                    if (board[x][getY()] != nullptr) {
                        return false;
                    }
                }
            }
            return (board[toX][toY] == nullptr || board[toX][toY]->getColor() != getColor());
        }
        if (abs(getX() - toX) == abs(getY() - toY)) {
            int deltaX = (toX > getX()) ? 1 : -1;
            int deltaY = (toY > getY()) ? 1 : -1;
            int x = getX() + deltaX;
            int y = getY() + deltaY;
            while (x != toX && y != toY) {
                if (board[x][y] != nullptr) {
                    return false;
                }
                x += deltaX;
                y += deltaY;
            }
            return (board[toX][toY] == nullptr || board[toX][toY]->getColor() != getColor());
        }
        return false;
    }
};


class King : public ChessPiece {
public:
    King(char color,int x,int y) : ChessPiece(color, 'K',x,y) {}
    
    bool isValidMove(int toX, int toY, const vector<vector<ChessPiece*> >& board){
        if (toX < 0 || toX > 7 || toY < 0 || toY > 7) {
            return false;
        }
        ChessPiece* destPiece = board[toX][toY];
        if (destPiece == nullptr || destPiece->getColor() != getColor()) {
            int dx = abs(toX - getX());
            int dy = abs(toY - getY());
            if ((dx == 1 && dy == 0) || (dx == 0 && dy == 1) || (dx == 1 && dy == 1)) {
                return true;
            }
        }
        
        return false;
    }
};


// Define the ChessBoard class
class ChessBoard {
// private:
// vector<vector<ChessPiece*>> m_board;
public:
	friend class Game;
    ChessBoard() {
        // Initialize the board
        m_board.resize(8);
        for (int i = 0; i < 8; i++) {
            m_board[i].resize(8);
        }
        // Add the white pieces
        m_board[0][0] = new Rook('W',0,0);
        m_board[0][1] = new Knight('W',0,1);
        m_board[0][2] = new Bishop('W',0,2);
        m_board[0][3] = new Queen('W',0,3);
        m_board[0][4] = new King('W',0,4);
        m_board[0][5] = new Bishop('W',0,5);
        m_board[0][6] = new Knight('W',0,6);
        m_board[0][7] = new Rook('W',0,7);
        for (int i = 0; i < 8; i++) {
        	m_board[1][i] = new Pawn('W',1,i);
    	}
	    // Add the black pieces
	    m_board[7][0] = new Rook('B',7,0);
	    m_board[7][1] = new Knight('B',7,1);
	    m_board[7][2] = new Bishop('B',7,2);
	    m_board[7][3] = new Queen('B',7,3);
	    m_board[7][4] = new King('B',7,4);
	    m_board[7][5] = new Bishop('B',7,5);
	    m_board[7][6] = new Knight('B',7,6);
	    m_board[7][7] = new Rook('B',7,7);
	    for (int i = 0; i < 8; i++) {
	        m_board[6][i] = new Pawn('B',6,i);
	    }
	}
~ChessBoard() {
    // Delete all pieces on the board
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            delete m_board[i][j];
        }
    }
}

private:
vector<vector<ChessPiece*> > m_board;

};

class player{
	char color;
	//int points;
	public:
		player(char c){
			color = c;
		}
		bool move(vector<vector<ChessPiece*> > &board,int fromX, int fromY, int toX, int toY) {
		    if (board[fromX][fromY] == nullptr) {
		        return false;
		    }
		    if (board[fromX][fromY]->isValidMove(toX, toY,board)) {
		    	char c = board[fromX][fromY] -> getColor();
		    	char t = board[fromX][fromY] -> getType();
		    	delete board[fromX][fromY];
				board[fromX][fromY] = nullptr;
				if(t == 'P'){
					if(c == 'W'){
						board[toX][toY] = new Pawn('W',toX,toY);
					}
					else{
						board[toX][toY] = new Pawn('B',toX,toY);
					}
				}
				if(t == 'K'){
					if(c == 'W'){
						board[toX][toY] = new King('W',toX,toY);
					}
					else{
						board[toX][toY] = new King('B',toX,toY);
					}
				}
				if(t == 'Q'){
					if(c == 'W'){
						board[toX][toY] = new Queen('W',toX,toY);
					}
					else{
						board[toX][toY] = new Queen('B',toX,toY);
					}
				}
				if(t == 'N'){
					if(c == 'W'){
						board[toX][toY] = new Knight('W',toX,toY);
					}
					else{
						board[toX][toY] = new Knight('B',toX,toY);
					}
				}
				if(t == 'B'){
					if(c == 'W'){
						board[toX][toY] = new Bishop('W',toX,toY);
					}
					else{
						board[toX][toY] = new Bishop('B',toX,toY);
					}
				}
				if(t == 'R'){
					if(c == 'W'){
						board[toX][toY] = new Rook('W',toX,toY);
					}
					else{
						board[toX][toY] = new Rook('B',toX,toY);
					}
				}
		        return true;
		    }
		    else {
		    	cout<<"        ";
		    	cout<<"Invalid move"<<endl;
		        return false;
		    }
		}
		bool isCheck(const vector<vector<ChessPiece*> >& board) {
    		// Find the position of the king
		    int kingX = -1, kingY = -1;
		    for (int i = 0; i < 8; ++i) {
		        for (int j = 0; j < 8; ++j) {
		            if (board[i][j] != nullptr && board[i][j]->getColor() == color && board[i][j]->getType() == 'K') {
		                kingX = i;
		                kingY = j;
		                break;
		            }
		        }
		    }
		    // Check if any opponent piece can attack the king
		    char opponentColor = (color == 'W') ? 'B' : 'W';
		    for (int i = 0; i < 8; ++i) {
		        for (int j = 0; j < 8; ++j) {
		        	
		            if (board[i][j] != nullptr && board[i][j]->getColor() == opponentColor) {
		                if (board[i][j]->isValidMove(kingX, kingY, board)) {
		                	cout << "Check !";
		                    return true;
		                }
		            }
		        }
		    }
		    // The king is not in check
		    return false;
		}
		
};
class Game{
	//result = 0 means checkmate
	int result;
	player * p1;
	player * p2;
	ChessBoard cb;
	vector<vector<ChessPiece*> > board ;
	int white;
	public:
		Game(){
			result = 0;
			board = cb.m_board;
			p1 = new player('W');
			p2 = new player('B');
			white = 1;
		}
		~Game(){
			delete p1;
			delete p2;
			for (int i = 0; i < 8; i++) {
		        for (int j = 0; j < 8; j++) {
		            delete board[i][j];
		        }
		    }
		}
		void whiteMove(){ 
			bool val = 0;
			while(val == 0){
				int a;int b;int x;int y;
				int z = 1;
				while(z==1){
					z = p2 -> isCheck(board); //0 if king is not in check
					cout<<"White Move"<<endl;
					cout<<"Enter the initial position a and b"<<endl;
                    cin >> a>>b;
                    cout<<"Enter the final position x and y" <<endl;
                    cin >>x>>y;
					val = (board[a][b] -> getColor() == 'W' && p1 -> move(board,a,b,x,y) && !z);
					if(val == 0 && board[a][b] -> getColor() == 'B'){
						cout << "it is invalid because of white move. Enter again\n";
					}
					if(z == 1 && val == 0){
						cout << "Check cleared enter new coordinates : ";
						break;
					}
				}
			}
		}
		
		void blackMove(){
			bool val = 0;
			while(val!=1){
				int a;int b;
                int x;int y;
				int z = 1;
				while(z==1){
					z = p2 -> isCheck(board); //0 if king is not in check
					cout<<"Black Move"<<endl;
                    cout<<"Enter the initial position a and b"<<endl;
                    cin >> a>>b;
                    cout<<"Enter the final position x and y" <<endl;
                    cin >>x>>y;
					val = (board[a][b] -> getColor() == 'B' && p2 -> move(board,a,b,x,y) && !z);
					if(val == 0 && board[a][b] -> getColor() != 'B'){
						cout << "it is invalid because of black move. Enter again\n";
					}
					if(z == 1 && val == 0){
						cout << "Check cleared enter new coordinates : ";
						break;
					}
				}
			}
		}
		bool getResult(){
			return result;
		}
		void display(){
			for (int i = 0; i < 8; i++) {
		        for (int j = 0; j < 8; j++) {
		            if ( board[i][j] == nullptr) {
		                cout << " __ ";
		            }
		            else {
		                cout <<"|"<<  board[i][j]->getType()<< board[i][j]->getColor() << "|";
		            }
		        }
		        cout << endl;
		    }
		}
};

// Main function
int main() {
    Game G;
    string decoration = 
                     "====================================\n"
                     "||            CHESS GAME           ||\n"
                     "====================================\n";

    cout << decoration << endl;
    G.display();

    while("True"){
		G.whiteMove();
		system("CLS");
		G.display();
		G.blackMove();
		system("CLS");
		G.display();
	}
    system("pause");
    return 0;
}

