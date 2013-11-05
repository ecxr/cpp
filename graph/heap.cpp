#include <iostream>
#include <vector>

using namespace std;
typedef int index;

template<class T>
class MinHeap {
  public:
    void insert(T item);
    T getMin();   // extract minimum element
    T readMin();  // view minimum element without removing it

    index find(T item);
    void changeKey(index i, int new_key);
    int size();

    friend ostream& operator<<(ostream& out, MinHeap<T> h) {
      out << "heap is now: ";
      for (unsigned int i = 0; i < h.contents.size(); i++) {
        out << h.contents[i] << " ";
      }
      out << "\n";
      return out;
    }

  private:
    vector<T> contents;
    void bubbleDown();    // restore heap invariant after extracting
    void bubbleUp();      // restore heap invariant after inserting
    int lesserChild(T parent);  // checks if node violates heap invariant
                                // returns smallest child if so; else returns -1
                                // (used by bubble functions)
};

template <class T>
int MinHeap<T>::size() {
  return contents.size();
}

template <class T>
void MinHeap<T>::insert(T item) {
  contents.push_back(item);
  bubbleUp();
}

template <class T>
T MinHeap<T>::getMin() {
  if (contents.empty()) {
    throw 0 ;  //TODO Create a new exception class
  }
  if (contents.size() == 1) {
    T min = contents.back();
    contents.pop_back();
    return min;
  }
  swap(contents[0], contents[contents.size() - 1]);
  T min = contents.back();
  contents.pop_back();
  bubbleDown();
  return min;
}

template <class T>
T MinHeap<T>::readMin() {
  return contents[0];
}

template <class T>
void MinHeap<T>::bubbleUp() {
  int current = contents.size() - 1;
  int parent = (current - 1) / 2;
  while (current != 0 && contents[current] < contents[parent]) {
    swap(contents[current], contents[parent]);
    current = parent;
    parent = (current - 1) / 2;
  }
}

template <class T>
void MinHeap<T>::bubbleDown() {
  int current = 0;
  int child = lesserChild(current);
  while (child != -1) {
    swap(contents[child], contents[current]);
    current = child;
    child = lesserChild(current);
  }
}

template <class T>
int MinHeap<T>::lesserChild(T parent) {
  int right = (parent + 1) * 2;
  int left = right - 1;
  int size = contents.size();

  if (size > right) { // two children
    if (contents[right] < contents[left]) {
      if (contents[right] < contents[parent]) return right;
    } else if (contents[left] < contents[parent]) return left;
  } else if (size == right) { // one child
    if (contents[left] < contents[parent]) return left;
  }
  return -1;
}

#ifdef TESTHEAP
int main() {
  MinHeap<int> h;
  int values[10] = {5,9,4,3,12,2,16,8,8,9};

  for (int i = 0; i < 10; i++) {
    cout << "inserting " << values[i] << "\n";
    h.insert(values[i]);
    cout << h;
  }

  for (int i = 0; i < 10; i++) {
    cout << "extracted " << h.getMin() << "\n" << h;
  }
}
#endif
