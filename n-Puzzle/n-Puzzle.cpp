#include <iostream>
#include "StateNode.h"
#include "UniformedSearch.h"
using namespace std;
int main(){
    
    int board[n_size] = {
        1, 2, 4,
        3, 0, 5,
        7, 6, 8
    };

    StateNode initialState(board);
    
    UniformedSearch uniformed;

    list <StateNode>* solution = uniformed.BFS(initialState);

    list<StateNode>::iterator it;
    if (solution->size() > 0) {
        for (it = solution->begin(); it != solution->end(); ++it) {
            it->printBoard();
        }
    }
    else {
        cout << "NO path to solution is Fonded ...";
    }
    return 0;
}


