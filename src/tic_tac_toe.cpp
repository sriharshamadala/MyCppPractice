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
  printBoard();
  cout << "Where would you like to place your 'X'? [1-" << to_string(size_ * size_) << "] ";
  int players_choice;
  cin >> players_choice;
  // TODO Validate players choice
  update(players_choice, "X");
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
  TttNode * temp_node;
  int min = kMaxValidScore;
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
  printBoard();
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
}

void TicTacToe::createChildrenAtDepth (TttNode *curr_node, int depth) {
  if (depth >= size_ * size_) {
    return;
  }
  if ((curr_node->score == 10) || (curr_node->score == -10)) {
    curr_node->nf_children = 0;
    curr_node->children = NULL;
  } else {
    int curr_branching_factor = size_ * size_ - depth;
    TttNode * children = new TttNode[curr_branching_factor];
    curr_node->children = children;
    curr_node->nf_children = curr_branching_factor;
    // Create boards and score them.
    for (int ii = 0; ii < curr_branching_factor; ++ii) {
      // Copy parent's board.
      children[ii].board = curr_node->board;
      int position = findIthAvailable(curr_node->board, ii + 1);
      if ((depth % 2) == 0) {
        children[ii].board[position] = 'X';
      } else {
        children[ii].board[position] = 'O';
      }
      children[ii].score = scoreTheBoard(children[ii].board, size_);
    }
    for (int ii = 0; ii < curr_branching_factor; ++ii) {
      createChildrenAtDepth(&children[ii], depth + 1);
    }
  }
}

void TicTacToe::createMinMaxTree () {
  // Create root node
  TttNode * root_node = new TttNode;
  for (int ii = 0; ii < size_ * size_; ++ii) {
    root_node->board.push_back('-');
  }
  root_node->score = 0;
  minimax_tree_.assignRoot(root_node);
  createChildrenAtDepth(root_node, 0);
}

int TicTacToe::updateScoresAtDepth (TttNode *curr_node, int depth) {
  if (curr_node->nf_children == 0) {
    // Terminal node
    return curr_node->score;
  } else {
    int max = kMinValidScore;
    int min = kMaxValidScore;
    for (int ii = 0; ii < curr_node->nf_children; ++ii) {
      int curr_child_score = updateScoresAtDepth(&curr_node->children[ii], depth + 1);
      if (curr_child_score > max) {
        max = curr_child_score;
      }
      if (curr_child_score < min) {
        min = curr_child_score;
      }
    }
    if ((depth % 2) == 0) {
      // return the maximum of all the child scores.
      curr_node->score = max;
      return max;
    } else {
      // return the minimum of all the child scores.
      curr_node->score = min;
      return min;
    }
  }
}

void TicTacToe::propagateScores () {
  updateScoresAtDepth(minimax_tree_.getRoot(), 0);
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

int scoreTheBoard (const vector<char>& board, int size) {
  int score = 0;
  
  if (rowCheckForWin(board, size, 'X')) {
    //cout << "row check X" << endl;
    score = 10;
  } else if (rowCheckForWin(board, size, 'O')) {
    //cout << "row check O" << endl;
    score = -10;
  } else if (colCheckForWin(board, size, 'X')) {
    //cout << "col check X" << endl;
    score = 10;
  } else if (colCheckForWin(board, size, 'O')) {
    //cout << "col check O" << endl;
    score = -10;
  } else if (diagCheckForWin(board, size, 'X')) {
    //cout << "diag check X" << endl;
    score = 10;
  } else if (diagCheckForWin(board, size, 'O')) {
    //cout << "diag check O" << endl;
    score = -10;
  } else {
    score = 0;
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
  cout << "Loading..." << endl;
  my_ttt.createMinMaxTree();
  //my_ttt.minimax_tree_.inorder(printScore);
  cout << string(50, '+') << endl;
  my_ttt.propagateScores();
  //my_ttt.minimax_tree_.inorder(printScore);
  my_ttt.current_node_playing = my_ttt.minimax_tree_.getRoot();
  while (!my_ttt.isGameOver()) {
    my_ttt.play();
  }

  return 0;
}
