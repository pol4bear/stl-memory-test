#include <iostream>
#include <list>
#include <map>
#include <set>
#include <vector>
#include "memory/memory.h"

#define CNT 50

using namespace std;

void vector_test(uint count) {
  vector<int> my_vector;

  for (uint i = 1; i <= count; i++) {
    my_vector.push_back(i);
    cout << "added " << i << endl;
  }
}

void list_test(uint count) {
  list<int> my_list;

  for (uint i = 1; i <= count; i++) {
    my_list.push_back(i);
    cout << "added " << i << endl;
  }
}

void set_test(uint count) {
  set<int> my_set;

  for (uint i = 1; i <= count; i++) {
    my_set.insert(i);
    cout << "added " << i << endl;
  }
}

void map_test(uint count) {
  map<int, int> my_map;

  for (uint i = 1; i <= count; i++) {
    my_map.insert(make_pair(i, i));
    cout << "added [" << i << "] = " << i << endl;
  }
}

int main() {
  int *test = new int(0);
  cout << "-------- Vector Test --------\n"; vector_test(CNT);
  cout << "-------- List Test --------\n"; list_test(CNT);
  cout << "-------- Set Test --------\n"; set_test(CNT);
  cout << "-------- Map Test --------\n"; map_test(CNT);
}
