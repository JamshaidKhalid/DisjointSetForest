#include <bits/stdc++.h>
using namespace std;

class Node {
public:
	int value = 0;
	int rank = 0;
	Node* parent = nullptr;
	Node(int value) { this->value = value; }
};


void makeSet(Node* element) {
	element -> parent = element;
}


Node* findSet(Node* element) {
    if (element == element -> parent)
        return element;    
    element -> parent = findSet(element -> parent);
}

void unionSet(Node* element1, Node* element2){
    element1 = findSet(element1);
    element2 = findSet(element2);

    if(element1 != element2) {
        element1 -> parent = element2;
    }

}



void printAllElements(std::vector<Node*> elements) {
	cout << "Element  Parent  Set Representative" << endl;
	for (int i = 0; i < elements.size(); i++) {
		// Print element and its set representative (should be same as element)
		    cout << elements.at(i)->value << "  "
			<< elements.at(i)->parent->value << "  "
			<< findSet(elements.at(i))->value << endl;
	}
}

int main()
{

	int numElements = 5;
	vector<Node*> elements(numElements);
	// Create vector of pointers to elements
	for (int i = 0; i < numElements; i++)
		elements.at(i) = new Node(i);

	// Make all singleton sets
	for (int i = 0; i < numElements; i++) {
		makeSet(elements.at(i));
	}
	printAllElements(elements);

	// Test a few unions ending up with a single set of all vertices
	unionSet(elements.at(0), elements.at(1));
	printAllElements(elements);
	unionSet(elements.at(0), elements.at(2));
	printAllElements(elements);
	unionSet(elements.at(3), elements.at(4));
	printAllElements(elements);
	unionSet(elements.at(0), elements.at(4));
	printAllElements(elements);

	return 0;
}

