#ifndef RECURSION_TO_ITERATION_H
#define RECURSION_TO_ITERATION_H

#include <iostream>
#include <stack>
#include <iterator>  // For iterators.
#include "graph.h"    // For class Node.

using namespace std;

enum class ReturnCode {PUSH, POP, POP_TERMINAL};

// Forward declaration
template <typename T>
class StackFrame;
template <typename T>
class Node;         // From src/graph.h

template<typename T>
struct ReturnInfo {
  ReturnCode return_code;
  StackFrame<T> * stack_frame_next;
};

/*
 * This class needs to be designed based on the recursive problem at hand.
 *
 * XXX template lets you use this code with different types of inputs.
 *     will need to use variadic templates to handle variable number of inputs
 *     with variable types.
 * 
 * XXX we assume that the input passed is a pointer of whatever type.
 *     if that is not the case, create overloaded functions like so:
 *     T * ptr (T obj) { return &obj; }
 *     T * ptr (T & obj) { return &obj; }
 *     T * ptr (T * obj) { return obj; }
 *     https://stackoverflow.com/questions/14466620/c-template-specialization-calling-methods-on-types-that-could-be-pointers-or/14466705
 *
 * This example is designed to calculate depth of a tree using DFS.
 * depth(Node * node) {
 *   if (node->nf_children == 0) {
 *     return 1;
 *   } else {
 *     int max_depth = 0;
 *     for (int ii = 0; ii < node->nf_children; ++ii) {
 *       int temp_depth = depth(&(node->children[ii]));
 *       if (temp_depth > max_depth) max_depth = temp_depth;
 *     }
 *   }
 * }
 *
 */
template <typename T>
class StackFrame {
  private:
    // Parameters.
    T param_;

    // Local variables.
    list<pair<T, int>> children_list_;
    typename list<pair<T, int>>::iterator child_it_;

    // Vector of stack frames created by the current frame.
    // To handle return values
    vector<StackFrame *>child_frames_;
    int return_val_;
  
  public:
    StackFrame (T param) : param_(param),
                           children_list_(param->getChildren()) {
      child_it_ = children_list_.begin();
    }

    int getReturnVal () {
      return return_val_;
    }

    void setReturnVal (int return_val) {
      return_val_ = return_val;
    }

    int processChildReturnValues () {
      int max_depth = 0;
      for (auto frame : child_frames_) {
        if (frame->return_val_ > max_depth) {
          max_depth = frame->return_val_;
        }
      }
      return max_depth;
    }

    ReturnInfo<T> compute (int prev_return_val) {
      // In this specific example, we can ignore the return value from the previous frame.
      struct ReturnInfo<T> return_info;
      if (children_list_.size() == 0) {
        // Terminal node. We care about the return value.
        return_val_ = 0;
        return_info.return_code = ReturnCode::POP_TERMINAL;
      } else if (child_it_ != children_list_.end()) {
        StackFrame<T> * stack_frame_next = new StackFrame<T>((*(child_it_)).first);
        return_info.return_code = ReturnCode::PUSH;
        return_info.stack_frame_next = stack_frame_next;
        ++child_it_;
        child_frames_.push_back(stack_frame_next);
      } else {
        // Done making all the recursive calls.
        return_val_ = processChildReturnValues();
        return_val_++;
        return_info.return_code = ReturnCode::POP;
      }
      return return_info;
    }
};

/*
 * Simple operations:
 *    Inspect the top of the stack.
 *    Pass the return value from the previous frame to current frame's compute method.
 *    Execute compute()
 *    Repeat until the stack is empty.
 * 
 * The logic to decide when to PUSH and POP and how the return values are 
 * handled is all implemented in the above specialized class.
 *
 */
template <typename T>
class Recursion {
  private:
    stack<StackFrame<T> *> recursion_stack_;
  
  public:
    int operator() (Node<int> * root) {
      int return_val = 0;

      StackFrame<T> * stack_frame = new StackFrame<T>(root);
      recursion_stack_.push(stack_frame);

      while (!recursion_stack_.empty()) {
        StackFrame<T> * curr_frame = recursion_stack_.top();
        struct ReturnInfo<T> return_info = curr_frame->compute(return_val);

        switch (return_info.return_code) {
          case ReturnCode::PUSH:
            recursion_stack_.push(return_info.stack_frame_next);
            // When a frame gets pushed to the stack, it is not a 
            // return from function call. Hence the input to compute should be 
            // equavalent to NULL.
            return_val = 0;
            break;
          case ReturnCode::POP:
            recursion_stack_.pop();
            return_val = curr_frame->getReturnVal();
            delete curr_frame;
            break;
          case ReturnCode::POP_TERMINAL:
            recursion_stack_.pop();
            return_val = curr_frame->getReturnVal();
            delete curr_frame;
            break;
        }
      }
      return return_val;
    }
};

#endif
