#include<list>
#include"StateNode.h"
using namespace std;
#pragma once
class UniformedSearch
{
public:
	// BFS implementation 
	list<StateNode>* BFS(StateNode root) {

		list<StateNode>* pathSolution = new list<StateNode>;

		// keeps nodes we can expand
		list<StateNode>* unexpandedStates = new list<StateNode>;

		// keeps nodes we have already expanded 
		list<StateNode>* expandedStates = new list<StateNode>;


		unexpandedStates->push_front(root);
		bool goalFounded = false;

		while (!goalFounded && unexpandedStates->size() > 0) {

			StateNode* currState = new StateNode();
			*currState = unexpandedStates->front();
			expandedStates->push_front(*currState);
			unexpandedStates->pop_front();

			(* currState).ExpandNodes();
			list<StateNode>::iterator it;
			for (it = (*currState).childern.begin(); it != (*currState).childern.end(); ++it) {

				StateNode currChild = *(&(*it));
				if (currChild.goalTest()) {
					cout << "Goal Funded !" << endl;
					goalFounded = true;
					// trace  path from here to root state
					pathSolution = pathTracer(pathSolution, currChild);
				}

				/*
					if unexpanded list not contain curr node and expanded list cot contain curr node
					then it is not expanded --> add this to unexpanded list
				*/
				if (!listContains(unexpandedStates, currChild), !listContains(expandedStates, currChild)) {
					unexpandedStates->push_back(currChild);

				}
			}
		}
		return pathSolution;
	}

	bool listContains(list<StateNode>* lst, StateNode st) {
		bool contains = false;
		list<StateNode>::iterator it;
		for (it = lst->begin(); it != lst->end(); ++it) {
			if (it->isSamePuzzle(st.puzzle)) {
				contains = true;
				break;
			}
		}
		return contains;
	}

	list<StateNode>* pathTracer(list<StateNode>* pathSlst, StateNode goalState) {
		cout << "Tracing Path ..." << endl;
		StateNode curr = goalState;
		pathSlst->push_front(curr);
		while (curr.parent != nullptr) {
			curr = *curr.parent;
			pathSlst->push_front(curr);
		}
		return pathSlst;
	}
};

