#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Returns the maximum of two integer values.
int maxValue(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

// Checks if a given character is an alphabet character.
bool AlphabetScan(char c) {
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
        return true;
    }
    return false;
}

// This class Tree is designed to store and manage a tree structure using a parent array.
class Tree {
protected:
    int size;                   // Store the size (number of nodes) of the tree
    int* parentArray;           // Pointer to an array that stores each node's parent

public:
    // Default Constructor.
    Tree() {
        size = 0;
        parentArray = new int[size];
    }

    // Initializes all parent array entries to -1.
    Tree(int noOfNodes) {
        size = noOfNodes;
        parentArray = new int[size];
        for (int i = 0; i < size; i++) {
            parentArray[i] = -1; // -1 denotes no parent
        }
    }

    // Destructor to free the parent array memory.
    ~Tree() {
        delete[] parentArray;
    }

    // Sets the parent for a given child node if within valid range.
    void setParent(int child, int parent) {
        if (child >= 0 && child < size) {
            parentArray[child] = parent;
        }
    }

    // Return the parent of a given child node. If invalid child, return -1.
    int getParent(int child) {
        if (child < 0 || child >= size) {
            return -1;
        }
        return parentArray[child];
    }

    // Return the children of a given parent node by scanning the parent array.
    vector<int> getChildren(int parent) {
        vector<int> children;
        for (int i = 0; i < size; i++) {
            if (parentArray[i] == parent) {
                children.push_back(i);
            }
        }
        return children;
    }

    // Get root of the tree by finding the node that has no parent (-1).
    int getRoot() {
        for (int i = 0; i < size; i++) {
            if (parentArray[i] == -1) {
                return i;
            }
        }
        return -1;
    }

    // Check if a given node is a leaf (no children).
    bool isLeaf(int node) {
        vector<int> kids = getChildren(node);
        if (kids.empty()) {
            return true;
        }
        return false;
    }

    // Get the height of a given node. A leaf node is treated as height = 1.
    int getHeight(int node) {
        // If the node is a leaf, return 1.
        if (isLeaf(node)) {
            return 1;
        }
        int maxHeight = 0;
        vector<int> children = getChildren(node);
        // Recursively compute the height of each child and track the maximum.
        for (size_t i = 0; i < children.size(); i++) {
            int childHeight = getHeight(children[i]);
            if (childHeight > maxHeight) {
                maxHeight = childHeight;
            }
        }
        // Return 1 plus the maximum height of any child.
        return 1 + maxHeight;
    }

    // Get the level of a node (distance from the root, counting root level as 1).
    int getLevel(int node) {
        if (node == getRoot()) {
            return 1;
        }
        // Recursively find parent's level and add 1.
        return 1 + getLevel(getParent(node));
    }

    // Return leaf nodes for a given root by recursively scanning children.
    void getLeafNodes(vector<int>& nodes, int root) {
        if (isLeaf(root)) {
            nodes.push_back(root);
            return;
        }
        vector<int> children = getChildren(root);
        for (size_t i = 0; i < children.size(); i++) {
            getLeafNodes(nodes, children[i]);
        }
    }

    // Return all nodes at a given level by checking each node's level.
    vector<int> getNodesAtLevel(int level) {
        vector<int> result;
        for (int i = 0; i < size; i++) {
            if (getLevel(i) == level) {
                result.push_back(i);
            }
        }
        return result;
    }

    // Get the least common ancestor (LCA) of nodeA and nodeB.
    int getLeastCommonAncestor(int nodeA, int nodeB) {
        // Build a list of all ancestors (including the node itself) of nodeA.
        vector<int> ancestorsA;
        while (nodeA != -1) {
            ancestorsA.push_back(nodeA);
            nodeA = getParent(nodeA);
        }
        // Move up from nodeB until a common ancestor is found in ancestorsA.
        while (nodeB != -1) {
            for (size_t i = 0; i < ancestorsA.size(); i++) {
                if (ancestorsA[i] == nodeB) {
                    return nodeB;
                }
            }
            nodeB = getParent(nodeB);
        }
        return -1;
    }

    // Get the path between nodeA and nodeB by going up from each node to their LCA
    vector<int> findPath(int nodeA, int nodeB) {
        vector<int> pathA;
        vector<int> pathB;
        vector<int> fullPath;
        // First, find the least common ancestor.
        int lca = getLeastCommonAncestor(nodeA, nodeB);

        // Go upwards from nodeA until reaching the LCA, storing nodes in pathA.
        while (nodeA != lca) {
            pathA.push_back(nodeA);
            nodeA = getParent(nodeA);
        }
        pathA.push_back(lca);

        // Do the same for nodeB, storing nodes in pathB.
        while (nodeB != lca) {
            pathB.push_back(nodeB);
            nodeB = getParent(nodeB);
        }

        // Add all nodes from pathA (which leads up to LCA).
        for (size_t i = 0; i < pathA.size(); i++) {
            fullPath.push_back(pathA[i]);
        }
        // Then add nodes from pathB in reverse order (to go from LCA down to nodeB).
        for (int i = pathB.size() - 1; i >= 0; i--) {
            fullPath.push_back(pathB[i]);
        }
        return fullPath;
    }

    // Get the number of nodes in the subtree rooted at 'root'.
    int getNoOfNodesInSubtree(int root) {
        int count = 1;
        vector<int> children = getChildren(root);
        for (size_t i = 0; i < children.size(); i++) {
            count += getNoOfNodesInSubtree(children[i]);
        }
        return count;
    }

    // Get all nodes in the subtree rooted at 'root' by recursively traversing.
    void getNodesInSubtree(vector<int>& nodes, int root) {
        nodes.push_back(root);
        vector<int> children = getChildren(root);
        for (size_t i = 0; i < children.size(); i++) {
            getNodesInSubtree(nodes, children[i]);
        }
    }

    // Display the tree in parent array representation, listing each child's parent.
    void displayParentArray() {
        cout << "Displaying the Parent Array:" << endl;
        cout << endl;
        for (int i = 0; i < size; i++) {
            cout << "Child: " << i << " Parent: " << parentArray[i] << endl;
        }
    }
};

int main() {
    int numNodes;
    cin >> numNodes;
    // Allocate a tree with the given number of nodes.
    Tree* myTree = new Tree(numNodes);

    // Read parent-child data until a letter is encountered or stream ends.
    while (true) {
        if (!cin.good()) break;         // If no more good data, break the loop

        streampos pos = cin.tellg();    // Remember current stream position
        char ch;
        cin >> ch;
        if (!cin.good()) {
            // Possibly end-of-file
            break;
        }

        // if the token is an alphabet, revert one char and stop reading parent data
        if (AlphabetScan(ch)) {
            cin.seekg(pos);
            break;
        }

        // If we get here, the token is a number for parent/child input
        cin.seekg(pos);
        int parent, numKids, child;
        cin >> parent >> numKids;
        for (int i = 0; i < numKids; i++) {
            cin >> child;
            myTree->setParent(child, parent);
        }
    }

    // Now read queries until EOF
    while (cin.good()) {
        char command;
        cin >> command;
        if (!cin.good()) break;

        // Handle the commands (P, C, L, etc.) as specified
        if (command == 'P') {
            int x;
            cin >> x;
            cout << "The parent of node " << x << " is: "
                 << myTree->getParent(x) << endl << endl;

        } else if (command == 'C') {
            int x;
            cin >> x;
            vector<int> kids = myTree->getChildren(x);
            cout << "The children of node " << x << " are:" << endl;
            for (size_t i = 0; i < kids.size(); i++) {
                cout << kids[i];
                if (i < kids.size() - 1) {
                    cout << " ";
                }
            }
            cout << endl << endl;

        } else if (command == 'L') {
            int x;
            cin >> x;
            cout << "The level of node " << x << " is: "
                 << myTree->getLevel(x) << endl << endl;

        } else if (command == 'I') {
            int x;
            cin >> x;
            if (myTree->isLeaf(x)) {
                cout << "The  node " << x << " is a leaf." << endl << endl;
            } else {
                cout << "The  node " << x << " is not a leaf." << endl << endl;
            }

        } else if (command == 'G') {
            int x;
            cin >> x;
            vector<int> leaves;
            myTree->getLeafNodes(leaves, x);
            cout << "The leaf nodes for node " << x << " are:" << endl;
            for (size_t i = 0; i < leaves.size(); i++) {
                cout << leaves[i];
                if (i < leaves.size() - 1) {
                    cout << " ";
                }
            }
            cout << endl << endl;

        } else if (command == 'A') {
            int x, y;
            cin >> x >> y;
            int lca = myTree->getLeastCommonAncestor(x, y);
            cout << "The LCA of " << x << " and " << y << " is: "
                 << lca << endl << endl;

        } else if (command == 'N') {
            int x;
            cin >> x;
            vector<int> subtree;
            myTree->getNodesInSubtree(subtree, x);
            cout << "The nodes in subtree rooted by " << x << " are:" << endl;
            for (size_t i = 0; i < subtree.size(); i++) {
                cout << subtree[i];
                if (i < subtree.size() - 1) {
                    cout << " ";
                }
            }
            cout << endl << endl;

        } else if (command == 'F') {
            int x, y;
            cin >> x >> y;
            vector<int> path = myTree->findPath(x, y);
            cout << "The path between " << x << " and " << y << " is:" << endl;
            for (size_t i = 0; i < path.size(); i++) {
                cout << path[i];
                if (i < path.size() - 1) {
                    cout << " ";
                }
            }
            cout << endl << endl;

        } else if (command == 'H') {
            int x;
            cin >> x;
            cout << "The Height of " << x << " is: "
                 << myTree->getHeight(x) << endl << endl;

        } else if (command == 'E') {
            int lvl;
            cin >> lvl;
            vector<int> nodes = myTree->getNodesAtLevel(lvl);
            cout << "The nodes at level " << lvl << " are:" << endl;
            for (size_t i = 0; i < nodes.size(); i++) {
                cout << nodes[i];
                if (i < nodes.size() - 1) {
                    cout << " ";
                }
            }
            cout << endl << endl;
        }
    }

    // Display the tree in parent array format, showing each child and its parent.
    myTree->displayParentArray();

    // Free allocated memory by deleting the tree object.
    delete myTree;
    return 0;
}
