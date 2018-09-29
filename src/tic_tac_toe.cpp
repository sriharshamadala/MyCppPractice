#include "tic_tac_toe.h"

TicTacToe::TicTacToe (int size, bool comp_starts) : minimax_tree_(NULL) {
  size_ = size;
  min_spacing_ = 2;
  is_game_over_ = false;
  turn_count_ = 1;

  // Initialize the board with index numbers.
  for (int ii = 0; ii < size_ * size_; ++ii) {
    board_.push_back(to_string(ii + 1));
  }
  max_digits_ = static_cast<int>(log10(size_ * size_)) + 1;
  for (int ii = 0; ii < size_ * size_; ++ii) {
    int curr_digits = static_cast<int>(log10(ii + 1)) + 1;
    spacing_.push_back(string(max_digits_ - curr_digits + min_spacing_, ' '));
  }
}

void TicTacToe::printBoard () {
  cout << string(50, '+') << endl;
  for (int ii = 0; ii < size_; ++ii) {
    for (int jj = 0; jj < size_; ++jj) {
      int curr_index = index(ii, jj);
      cout << board_[curr_index] << spacing_[curr_index];
    }
    cout << endl;
  }
  cout << string(50, '+') << endl;
}

void TicTacToe::play () {
  // Computers turn.
  TttNode * temp_node;
  int min = kMaxInfinity;
  for (int ii = 0; ii < current_node_playing->nf_children; ++ii) {
    if (current_node_playing->children[ii].score < min) {
      temp_node = &(current_node_playing->children[ii]);
      min = current_node_playing->children[ii].score;
    }
  }
  current_node_playing = temp_node;
  // Simply copy the board of this node.
  copyBoardPatterns(board_, current_node_playing->board);
  cout << "Computer played !" << endl;
  if (current_node_playing->nf_children == 0) {
    // Reached terminal node. End of game.
    is_game_over_ = true;
    if (current_node_playing->score == 0) {
      cout << "Game Over! It's a tie!!!" << endl;
    } else {
      cout << "Game Over! Computer Won!!!" << endl;
    }
    return;
  }

  // Human turn.
  int players_choice;
  do {
    printBoard();
    cout << "Where would you like to place your 'X'? [1-" << to_string(size_ * size_) << "] ";
    cin >> players_choice;
  } while (!update(players_choice, "X"));
  printBoard();
  for (int ii = 0; ii < current_node_playing->nf_children; ++ii) {
    if (current_node_playing->children[ii].board[players_choice - 1] == 'X') {
      current_node_playing = &current_node_playing->children[ii];
      break;
    }
  }
  if (current_node_playing->nf_children == 0) {
    // Reached terminal node. End of game.
    is_game_over_ = true;
    if (current_node_playing->score == 0) {
      cout << "Game Over! It's a tie!!!" << endl;
    } else {
      cout << "Game Over! You Won!!!" << endl;
    }
    return;
  }
}

int TicTacToe::minimax (TttNode *curr_node, int depth, int alpha, int beta) {
  if (depth >= size_ * size_) {
    // Terminal node.
    if ((curr_node->score != 10) && (curr_node->score != -10)) {
      // Tie.
      curr_node->score = 0;
    }
    return curr_node->score;
  } else if ((curr_node->score == 10) || (curr_node->score == -10)) {
    // Terminal node.
    return curr_node->score;
  } else {
    // Create children and evaluate the board.
    int curr_branching_factor = size_ * size_ - depth;
    TttNode * children = new TttNode[curr_branching_factor];
    curr_node->children = children;
    curr_node->nf_children = curr_branching_factor;
    // Create boards and score them.
    if ((depth % 2) == 0) {
      // Maximizing node
      int max_eval = kMinInfinity;
      for (int ii = 0; ii < curr_branching_factor; ++ii) {
        // Copy parent's board.
        children[ii].board = curr_node->board;
        int position = findIthAvailable(curr_node->board, ii + 1);
        children[ii].board[position] = 'X';
        children[ii].score = staticEvaluation(children[ii].board, size_);
        int eval = minimax(&children[ii], depth + 1, alpha, beta);
        max_eval = max(eval, max_eval);
        alpha = max(alpha, eval);
        if (beta <= alpha) {
          // No need to evaluate the rest of the children. Prune.
          break;
        }
      }
      curr_node->score = max_eval;
      return max_eval;
    } else {
      // Minimizing node
      int min_eval = kMaxInfinity;
      for (int ii = 0; ii < curr_branching_factor; ++ii) {
        // Copy parent's board.
        children[ii].board = curr_node->board;
        int position = findIthAvailable(curr_node->board, ii + 1);
        children[ii].board[position] = 'O';
        children[ii].score = staticEvaluation(children[ii].board, size_);
        int eval = minimax(&children[ii], depth + 1, alpha, beta);
        min_eval = min(eval, min_eval);
        beta = min(eval, beta);
        if (beta <= alpha) {
          // No need to evaluate the rest of the children. Prune.
          break;
        }
      }
      curr_node->score = min_eval;
      return min_eval;
    }
  }
}

void TicTacToe::createMinMaxTree () {
  // Create root node
  TttNode * root_node = new TttNode;
  for (int ii = 0; ii < size_ * size_; ++ii) {
    root_node->board.push_back('-');
  }
  printBoard();
  cout << "Where would you like to place your 'X'? [1-" << to_string(size_ * size_) << "] ";
  int players_choice;
  cin >> players_choice;
  root_node->board[players_choice - 1] = 'X';
  board_[players_choice - 1] = "X";
  printBoard();
  minimax_tree_.assignRoot(root_node);
  minimax(root_node, 1, kMinInfinity, kMaxInfinity);
  current_node_playing = root_node;
}

// Utility functions
void copyBoardPatterns (vector<string> & board1, vector<char> & board2) {
  for (int ii = 0; ii < board1.size(); ++ii) {
    if ((board2[ii] == 'X') || (board2[ii] == 'O')) {
      board1[ii] = board2[ii];
    }
  }
}

int findIthAvailable (vector<char>& board, int i) {
  for (int pos = 0; pos < board.size(); ++pos) {
    if ((board[pos] != 'X') && (board[pos] != 'O')) {
      i--;
    }
    if (i == 0) {
      return pos;
    }
  }
  return board.size();  // should never get here.
}

bool rowCheckForWin (const vector<char>& board, int size, char ox) {
  for (int ii = 0; ii < size; ++ii) {
    bool win = true;
    for (int jj = 0; jj < size; ++jj) {
      if (board[index(ii, jj, size)] != ox) {
        win = false;
        break;
      }
    }
    if (win) {
      return true;
    }
  }
  return false;
}

bool colCheckForWin (const vector<char>& board, int size, char ox) {
  for (int ii = 0; ii < size; ++ii) {
    bool win = true;
    for (int jj = 0; jj < size; ++jj) {
      if (board[index(jj, ii, size)] != ox) {
        win = false;
        break;
      }
    }
    if (win) {
      return true;
    }
  }
  return false;
}

bool diagCheckForWin (const vector<char>& board, int size, char ox) {
  // Diagonal 1
  bool win = true;
  for (int ii = 0; ii < size; ++ii) {
    if (board[index(ii, ii, size)] != ox) {
      win = false;
      break;
    }
  }
  if (win) {
    //cout << "diag1" << endl;
    return true;
  } else {
    // Diagonal 2
    win = true;
    for (int ii = 0; ii < size; ++ii) {
      int jj = size - 1 - ii;
      if (board[index(ii, jj, size)] != ox) {
        win = false;
        break;
      }
    }
    if (win) {
      //cout << "diag2" << endl;
      return true;
    }
  }
  return false;
}

int staticEvaluation (const vector<char>& board, int size) {
  int score = kMaxInfinity;
  
  if (rowCheckForWin(board, size, 'X')) {
    score = 10;
  } else if (rowCheckForWin(board, size, 'O')) {
    score = -10;
  } else if (colCheckForWin(board, size, 'X')) {
    score = 10;
  } else if (colCheckForWin(board, size, 'O')) {
    score = -10;
  } else if (diagCheckForWin(board, size, 'X')) {
    score = 10;
  } else if (diagCheckForWin(board, size, 'O')) {
    score = -10;
  } 
  return score;
} 

void printScore (TttNode * curr_node) {
  cout << curr_node->score << " " << endl;
  for (auto pos : curr_node->board) {
    cout << pos << " ";
  }
  cout << endl;
}

int main () {
  int ttt_size;
  cout << "What size of Tic-Tac-Toe would you like to play? [2-4]" << endl;
  cin >> ttt_size;
  if ((ttt_size < 2) || (ttt_size > 4)) {
    cout << "Invalid size !" << endl;
    return -1;
  }

  TicTacToe my_ttt(ttt_size);
  my_ttt.createMinMaxTree();
  while (!my_ttt.isGameOver()) {
    my_ttt.play();
  }

  return 0;
}
