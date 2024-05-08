#include <iostream>
#include "queue"
using namespace std;

class Node {
public:
    int key;
    Node *left;
    Node *right;
    int height;
};

int height(Node *node) {
    if (node == NULL) return 0;
    return node->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Node *newNode(int key) {
    Node *node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

Node *rotateRight(Node *x) {
    Node *y = x->left;
    Node *t = y->right;
    y->right = x;
    x->left = t;
    x->height = max(height(x->right), height(x->left)) + 1;
    y->height = max(height(y->right), height(y->left)) + 1;
    return y;
}

Node *rotateLeft(Node *y) {
    Node *x = y->right;
    Node *t = x->left;
    x->left = y;
    y->right = t;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

int getBalanceFactor(Node *node) {
    if (node == NULL) return 0;
    return height(node->left) - height(node->right);
}

Node *insertNode(Node *node, int key) {
    if (node == NULL) {
        return newNode(key);
    }
    if (key < node->key) {
        node->left = insertNode(node->left, key);
    } else if (key > node->key) {
        node->right = insertNode(node->right, key);
    } else {
        return node;
    }
    node->height = 1 + max(height(node->left), height(node->right));

    int balanceFactor = getBalanceFactor(node);
    if (balanceFactor > 1) {
        if (key < node->left->key) {
            return rotateRight(node);
        } else if (key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
    }
    if (balanceFactor < -1) {
        if (key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        } else if (key > node->right->key) {
            return rotateLeft(node);
        }
    }
    return node;
}

Node *nodeWithMinimumValue(Node *node) {
    Node *current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

Node *deleteNode(Node *node, int key) {
    if (node == NULL) {
        return node;
    }
    if (key < node->key) {
        node->left = deleteNode(node->left, key);
    } else if (key > node->key) {
        node->right = deleteNode(node->right, key);
    } else {
        if (node->right == NULL || node->left == NULL) {
            Node *temp = node->left ? node->left : node->right;
            if (temp == NULL) {
                temp = node;
                node = NULL;
            } else {
                *node = *temp;
            }
            delete temp;
        } else {
            Node *temp = nodeWithMinimumValue(node->right);
            node->key = temp->key;
            node->right = deleteNode(node->right, temp->key);
        }
    }
    if (node == NULL) {
        return node;
    }
    node->height = 1 + max(height(node->left), height(node->right));
    int balanceFactor = getBalanceFactor(node);
    if (balanceFactor > 1) {
        if (getBalanceFactor(node->left) >= 0) {
            return rotateRight(node);
        } else {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
    }
    if (balanceFactor < -1) {
        if (getBalanceFactor(node->right) <= 0) {
            return rotateLeft(node);
        } else {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
    }
    return node;
}

void printTree(Node *root) {
    if (root != nullptr) {
        cout << root->key << " ";
        printTree(root->left);
        printTree(root->right);
    }
}

int sum_leaves(Node* root){
    if(root==NULL){
        return 0;
    }
    if(root->right==NULL && root->left==NULL){
        return root->key;
    }
    return sum_leaves(root->left) + sum_leaves(root->right);
}

void level_average(Node* root){
    queue<Node*> queue1;
    queue1.push(root);
    while(!queue1.empty()){
        int level_sum=0;
        int nodes=queue1.size();
        for(int i=0;i<nodes;i++){
            Node* node1=queue1.front();
            queue1.pop();
            level_sum=level_sum+node1->key;
            if(node1->left){
                queue1.push(node1->left);
            }
            if(node1->right){
                queue1.push(node1->right);
            }
        }
        cout<<(double)level_sum/nodes<<" ";
    }
    cout<<endl;
}

int main() {
    Node *root=NULL;
    
    int n, number;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>number;
        root = insertNode(root, number);
    }
    
    level_average(root);

    return 0;
}
