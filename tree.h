#ifndef TREE_H
#define TREE_H
#include <string>
#include <vector>

using namespace std;

enum DataType {
    DATA_FILE,
    DATA_DIR
};

typedef struct Node *adrNode;

struct Node {
    string name;
    DataType type;
    string content;
    vector<adrNode> child;
};

void createNode(adrNode &node, string name, DataType type, string content = "");
void deleteTree(adrNode &node);
adrNode findChild(vector<adrNode> &childs, string name);
bool addChild(adrNode &node, string name, DataType type);
bool deleteChild(adrNode &node, string name);
void printPath(vector<adrNode> &path);

void preorder(adrNode node);
void postorder(adrNode node);

#endif // TREE_H
