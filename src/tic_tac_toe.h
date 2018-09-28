#include <iostream>
#include <string>
#include <vector>
#include <cmath>    // for log10
#include "tree.h"   // for minimax tree.

using namespace std;

// XXX Choose this numbers outside the valid range of scores.
const int kMaxValidScore = 100;
const int kMinValidScore = -100;

// XXX Each node having a copy of the board is inefficient.
struct TttNode {
  int score;
  int nf_children;
  struct TttNode * children;
  vector<char>board;
};

class TicTacToe {
  private:
    int size_;
    vector<string> board_;
    vector<string> spacing_;
    int max_digits_;
    int min_spacing_;
    int turn_count_;
    bool is_game_over_;

  public:
    TttNode * current_node_playing;
    // TODO Debug-only; move to private
    Tree<TttNode> minimax_tree_;
    TicTacToe (int size, bool comp_starts = false);
    ~TicTacToe () {}
    
    int index (int row, int col) {
      return size_ * row + col;
    }
    
    void printBoard ();
    
    bool isGameOver () {
      return is_game_over_;
    }
    
    void update (int position, string ox) {
      board_[position - 1] = ox;
      spacing_[position - 1] = string(max_digits_ + min_spacing_ - 1, ' ');
    }
    
    void play ();

    void createChildrenAtDepth (TttNode *curr_node, int depth);
    void createMinMaxTree ();
    int updateScoresAtDepth (TttNode *curr_node, int depth);
    void propagateScores ();

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
int scoreTheBoard (const vector<char>& board, int size);

bool diagCheckForWin (const vector<char>& board, int size, string ox);
bool colCheckForWin (const vector<char>& board, int size, string ox);
bool rowCheckForWin (const vector<char>& board, int size, string ox);
void copyBoardPatterns (vector<string> & board1, vector<char> & board2);
