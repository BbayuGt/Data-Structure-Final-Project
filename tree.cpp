#include "tree.h"
#include <iostream>

using namespace std;

void createNode(adrNode& node, string name, DataType type, string content)
{
    node = new Node;
    node->name = name;
    node->type = type;
    node->content = content;
}

void deleteTree(adrNode& node)
{
    if (node != nullptr) {
        for (adrNode child : node->child) {
            deleteTree(child);
        }
    }
    delete node;
}

adrNode findChild(vector<adrNode>& childs, string name)
{
    for (adrNode child : childs) {
        if (child->name == name) return child;
    }
    return nullptr;
}

bool addChild(adrNode& node, string name, DataType type)
{
    for (adrNode child : node->child) {
        if(child->name == name) return false; // nama file yang sama telah tersedia
    }
    adrNode newData;
    createNode(newData, name, type, "");
    node->child.push_back(newData);
    return true;
}

bool deleteChild(adrNode &node, string name) {
    for (int i = 0; i < node->child.size(); i++) {
        if (node->child[i]->name == name) {
            node->child.erase(node->child.begin() + i);
            return true;
        }
    }
    return false;
}

void printPath(vector<adrNode>& path)
{
    for (adrNode i : path) {
        if (i->name != "/") {
            cout << i->name;
        }
        cout << "/";
    }
}

void preorder(adrNode node)
{
    if (node != nullptr) {
        cout << node->name << endl;
        for (adrNode child : node->child) {
            preorder(child);
        }
    }
}

void postorder(adrNode node)
{
    if (node != nullptr) {
        for (adrNode child : node->child) {
            preorder(child);
        }
        cout << node->name << endl;
    }
}

