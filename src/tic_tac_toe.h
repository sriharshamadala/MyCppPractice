#include <iostream>
#include <string>
#include <vector>
#include <cmath>    // for log10
#include "tree.h"   // for minimax tree.
#include <climits>  // for INT_MIN, INT_MAX; alpha beta pruning.

using namespace std;

const int kMaxInfinity = INT_MAX;
const int kMinInfinity = INT_MIN;

inline int max (int a, int b) {
  return (a >= b) ? a : b;
}

inline int min (int a, int b) {
  return (a <= b) ? a : b;
}

// XXX Each node having a copy of the board is inefficient.
struct TttNode {
  int score;
  int nf_children;
  struct TttNode * children;
  vector<char>board;
  TttNode () {
    score = kMaxInfinity;
  }
};

class TicTacToe {
  private:
    Tree<TttNode> minimax_tree_;
    int size_;
    vector<string> board_;
    vector<string> spacing_;
    int max_digits_;
    int min_spacing_;
    int turn_count_;
    bool is_game_over_;
    TttNode * current_node_playing;

  public:
    TicTacToe (int size, bool comp_starts = false);
    ~TicTacToe () {}
    
    int index (int row, int col) {
      return size_ * row + col;
    }
    
    void printBoard ();
    
    bool isGameOver () {
      return is_game_over_;
    }
    
    bool update (int position, string ox) {
      if ((board_[position - 1] == "X") 
          || (board_[position - 1] == "O")) {
        cout << "Invalid choice! Try again!" << endl;
        return false;
      } else {
        board_[position - 1] = ox;
        spacing_[position - 1] = string(max_digits_ + min_spacing_ - 1, ' ');
        return true;
      }
    }
    
    void play ();

    int minimax (TttNode *curr_node, int depth, int alpha, int beta);
    void createMinMaxTree ();

};

/*
 * Utility functions
 */
int index (int row, int col, int size) {
  return size * row + col;
}
int findIthAvailable (vector<char>& board, int i);
// returns +10 if X wins
// returns -10 if O wins
// returns 0 if neither wins.
// XXX If score is 0 and all the positions on the board are filled, its a tie.
// XXX We assume that the board has only one winner if at all.
int staticEvaluation (const vector<char>& board, int size);

bool diagCheckForWin (const vector<char>& board, int size, string ox);
bool colCheckForWin (const vector<char>& board, int size, string ox);
bool rowCheckForWin (const vector<char>& board, int size, string ox);
void copyBoardPatterns (vector<string> & board1, vector<char> & board2);
