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
      }
      nf_disjoint_sets_ = arr_size;
    }

    /*
     * Insert a new element as a disjoint set.
     */
    void insert (T * element) {
      map_[element] = map_.size();
      parents_.push_back(element);
      nf_disjoint_sets_++;
    }

    /*
     * Insert an array of new elements, each as a disjoint set.
     */
    void insert (T *arr, int arr_size) {
      for (int ii = 0; ii < arr_size; ++ii) {
        map_[&arr[ii]] = map_.size() + ii;
        parents_.push_back(&arr[ii]);
      }
      nf_disjoint_sets_ += arr_size;
    }

    void Union (T *element1, T *element2) {
      T * parent1 = find(element1);
      T * parent2 = find(element2);
      if (parent1 != parent2) {
        // Both the elements belong to different sets.
        updateParent(parent2, parent1);
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
      do {
        temp_element = parent;
        try {
          index = map_[temp_element];
        } catch (exception e) {
          cout << "Unable to find this element in the set! " << e.what() << endl;
        }
        parent = parents_[index];
      } while (parent != temp_element);

      // Path compression.
      updateParent(element, parent);

      return parent;
    }

    int numberOfDisjointSets () {
      return nf_disjoint_sets_;
    }
};
