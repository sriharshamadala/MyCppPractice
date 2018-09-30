/*
 * This is the implementation of the Disjoint datastructure,
 * which is commonly used in the Union-Find algorithm.
 * We also use path compression to decrease the amortized cost
 * of doing more Unions and Finds.
 *
 * Space complexity = O(N)
 * Time complexity of find() and Union () = O(log N) -> amortized
 *
 */

#include <iostream>
#include <vector>
#include <map>

using namespace std;

template <typename T>
class DisjointSet {
  private:
    map<T*, int> map_;
    vector<T*> parents_;
    vector<int> rank_;
    int nf_disjoint_sets_ = 0;

    void updateParent (T * element, T * parent_to_be) {
      int index = map_[element];
      parents_[index] = parent_to_be;
    }

  public:
    DisjointSet (T *arr, int arr_size) {
      for (int ii = 0; ii < arr_size; ++ii) {
        map_[&arr[ii]] = ii;
        parents_.push_back(&arr[ii]);
        rank_.push_back(0);
      }
      nf_disjoint_sets_ = arr_size;
    }

    DisjointSet () {
      nf_disjoint_sets_ = 0;
    }

    /*
     * Insert a new element as a disjoint set.
     */
    void insert (T * element) {
      map_[element] = map_.size();
      parents_.push_back(element);
      rank_.push_back(0);
      nf_disjoint_sets_++;
    }

    /*
     * Insert an array of new elements, each as a disjoint set.
     */
    void insert (T *arr, int arr_size) {
      for (int ii = 0; ii < arr_size; ++ii) {
        map_[&arr[ii]] = map_.size() + ii;
        parents_.push_back(&arr[ii]);
        rank_.push_back(0);
      }
      nf_disjoint_sets_ += arr_size;
    }

    void Union (T *element1, T *element2) {
      T * parent1 = find(element1);
      T * parent2 = find(element2);
      if (parent1 != parent2) {
        // Both the elements belong to different sets.
        int rank1 = rank_[map_[parent1]];
        int rank2 = rank_[map_[parent2]];
        if (rank1 < rank2) {
          updateParent(parent1, parent2);
        } else if (rank1 > rank2) {
          updateParent(parent2, parent1);
        } else {
          updateParent(parent1, parent2);
          rank_[map_[parent2]]++;
        }
        nf_disjoint_sets_--;
      }
    }

    /*
     * Return the root of the set this element belongs to.
     */
    T * find (T * element) {
      T * parent = element;
      T * temp_element;
      int index;
      int count = 0;
      do {
        temp_element = parent;
        try {
          index = map_[temp_element];
        } catch (exception e) {
          cout << "Unable to find this element in the set! " << e.what() << endl;
        }
        parent = parents_[index];
        count++;
      } while (parent != temp_element);

      // Path compression.
      updateParent(element, parent);
      int rank_e = rank_[map_[element]];
      int rank_p = rank_[map_[parent]];
      if (count - 1 + rank_e == rank_p) {
        // we are path compressing the deepest path. update rank.
        rank_[map_[element]] = ((count - 1) < (rank_e + 1)) ? rank_e + 1 : count - 1;
      }

      return parent;
    }

    int numberOfDisjointSets () {
      return nf_disjoint_sets_;
    }
};

// If each element of the set is somehow mapped to a continous range
// of numbers from 0...N - 1, we could use the following faster implementation.
template <>
class DisjointSet<int> {
  private:
    vector<int> parents_;
    vector<int> rank_;
    int nf_disjoint_sets_ = 0;

    void updateParent (int element, int parent_to_be) {
      parents_[element] = parent_to_be;
    }

  public:
    DisjointSet (int arr_size) {
      for (int ii = 0; ii < arr_size; ++ii) {
        parents_.push_back(ii);
        rank_.push_back(0);
      }
      nf_disjoint_sets_ = arr_size;
    }

    DisjointSet () {
      nf_disjoint_sets_ = 0;
    }

    /*
     * Insert a new element as a disjoint set.
     */
    void insert (int element) {
      parents_.push_back(element);
      rank_.push_back(0);
      nf_disjoint_sets_++;
    }

    void Union (int element1, int element2) {
      int parent1 = find(element1);
      int parent2 = find(element2);
      if (parent1 != parent2) {
        // Both the elements belong to different sets.
        int rank1 = rank_[parent1];
        int rank2 = rank_[parent2];
        if (rank1 < rank2) {
          updateParent(parent1, parent2);
        } else if (rank1 > rank2) {
          updateParent(parent2, parent1);
        } else {
          updateParent(parent1, parent2);
          rank_[parent2]++;
        }
        nf_disjoint_sets_--;
      }
    }

    /*
     * Return the root of the set this element belongs to.
     */
    int find (int element) {
      int parent = element;
      int temp_element;
      int count = 0;
      do {
        temp_element = parent;
        parent = parents_[temp_element];
        count++;
      } while (parent != temp_element);

      // Path compression.
      updateParent(element, parent);
      int rank_e = rank_[element];
      int rank_p = rank_[parent];
      if (count - 1 + rank_e == rank_p) {
        // we are path compressing the deepest path. update rank.
        rank_[element] = ((count - 1) < (rank_e + 1)) ? rank_e + 1 : count - 1;
      }

      return parent;
    }

    int numberOfDisjointSets () {
      return nf_disjoint_sets_;
    }
};
