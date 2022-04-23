// disjointSetForest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <bits/stdc++.h>
using namespace std;
class Node {
public:
	int value = 0;
	int rank = 0;
	Node* parent = nullptr;
	Node(int value) { this->value = value; }
};

// Create a set given a single element
void makeSet(Node* element) {
	element -> parent = element;
    element -> rank = 0;
}


// Return root for set given an element, using path compression if
// pathCompression is true
Node* findSet(Node* element, bool pathCompression) {
	if(pathCompression) {
		if (element == element -> parent)
        	return element;    
    	return element -> parent = findSet(element -> parent, true);
	}


	if(!pathCompression) {
		if (element == element -> parent)
        	return element;    
    	return findSet(element -> parent, false);
	}
	return nullptr;
}


// Take the union of two sets given an element from each set. Both union by
// rank and path compression heuristics can be used or not used.
void unionSet(Node* element1, Node* element2, bool unionByRank,	bool pathCompression) {
	if(unionByRank) {
		element1 = findSet(element1, pathCompression);
    	element2 = findSet(element2, pathCompression);

    	if(element1 != element2) {
        	if(element1->rank < element2->rank)
            	std::swap(element1, element2);
        	element1->parent = element2;

        	if(element1->rank == element2->rank)
            	element1->rank++;
    	}
	}

	if(pathCompression) {
		element1 = findSet(element1, true);
		element2 = findSet(element2, true);
	}
	else {
		element1 = findSet(element1, false);
		element2 = findSet(element2, false);
	}

	
	if(element1 != element2) {
		element1 -> parent = element2;
	}
}

void worstCaseTime(int N){
        int numElements = 5;
	    std::vector<Node*> elements(N);
        for (int i = 0; i < N; i++)
		    elements.at(i) = new Node(i);

        auto begin = std::chrono::high_resolution_clock::now();
	    // Make all singleton sets
	    for (int i = 0; i < N; i++) {
	    	makeSet(elements.at(i));
	    }


        for(int i = 1; i < N; i++){
                unionSet(elements.at(0), elements.at(i), false, false);
        }
        auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("N = %d (without heuristics): %.3f seconds.\n", N, elapsed.count() * 1e-9);

    begin = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < N; i++) {
	    	makeSet(elements.at(i));
	    }
        for(int i = 1; i < N; i++){
                unionSet(elements.at(0), elements.at(i), false, false);
        }
        end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("N = %d (with heuristics): %.3f seconds.\n", N, elapsed.count() * 1e-9);

}


void randomCaseTime(int N, bool unionByRank, bool pathCompression){
	    std::vector<Node*> elements(N);
        for (int i = 0; i < N; i++)
		    elements.at(i) = new Node(i);

        auto begin = std::chrono::high_resolution_clock::now();

        for(int i = 0; i < N; i++){
                Node* x = new Node(rand() % N);
                Node* y = new Node(rand() % N);
                makeSet(x);
                makeSet(y);
                unionSet(x, y, unionByRank, pathCompression);
        }
        auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("N = %d: %.3f seconds.\n", N, elapsed.count() * 1e-9);

}


int main()
{


	// Test for correctness of functionality
	cout<<"Worst case time:\n";
        worstCaseTime(100);
        worstCaseTime(1000);
        worstCaseTime(10000);

        for(int i = 0; i < 10; i++){
                cout<<"\nAverage case time(Trial "<< i+1<<"):\n";

                cout<<"\n(Only Union By Rank heuristic)\n";
                randomCaseTime(1000, true, false);
                randomCaseTime(10000, true, false);
                randomCaseTime(100000, true, false);
                randomCaseTime(1000000, true, false);

                cout<<"\n(Only Path Compression heuristic)\n";
                randomCaseTime(1000, false, true);
                randomCaseTime(10000, false, true);
                randomCaseTime(100000, false, true);
                randomCaseTime(1000000, false, true);

                cout<<"\n(Both heuristics)\n";
                randomCaseTime(1000, true, true);
                randomCaseTime(10000, true, true);
                randomCaseTime(100000, true, true);
                randomCaseTime(1000000, true, true);
        }

	return 0;
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
