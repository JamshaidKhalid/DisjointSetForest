// disjointSetForest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

class Node {
public:
	int value = 0;
	int rank = 0;
	Node* parent = nullptr;
	Node(int value) { this->value = value; }
};

// Create a set given a single element
void makeSet(Node* element);
// Return root for set given an element, using path compression if
// pathCompression is true
Node* findSet(Node* element, bool pathCompression);
// Take the union of two sets given an element from each set. Both union by
// rank and path compression heuristics can be used or not used.
void unionSet(Node* element1, Node* element2, bool unionByRank,
	bool pathCompression);

void printAllElements(std::vector<Node*> elements);

int main()
{
	bool unionByRank = true, pathCompression = true;

	// Test for correctness of functionality
	int numElements = 5;
	std::vector<Node*> elements(numElements);
	// Create vector of pointers to elements
	for (int i = 0; i < numElements; i++)
		elements.at(i) = new Node(i);

	// Make all singleton sets
	for (int i = 0; i < numElements; i++) {
		makeSet(elements.at(i));
	}
	printAllElements(elements);

	// Test a few unions ending up with a single set of all vertices
	unionSet(elements.at(0), elements.at(1), unionByRank, pathCompression);
	printAllElements(elements);
	unionSet(elements.at(0), elements.at(2), unionByRank, pathCompression);
	printAllElements(elements);
	unionSet(elements.at(3), elements.at(4), unionByRank, pathCompression);
	printAllElements(elements);
	unionSet(elements.at(0), elements.at(4), unionByRank, pathCompression);
	printAllElements(elements);

	return 0;
}

void printAllElements(std::vector<Node*> elements) {
	std::cout << "Element  Parent  Set Representative" << std::endl;
	for (int i = 0; i < elements.size(); i++) {
		// Print element and its set representative (should be same as element)
		std::cout << elements.at(i)->value << "  "
			<< elements.at(i)->parent->value << "  "
			<< findSet(elements.at(i), false)->value << std::endl;
	}
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
