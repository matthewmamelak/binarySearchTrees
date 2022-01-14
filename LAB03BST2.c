//LAB03BST2.c – Lab 03 – Matthew, Mamelak

#include <stdlib.h>
#include <stdio.h>

//Creates the structure of the node
typedef struct Node {
    int userID;
    char *userPassword;
    struct Node *leftChild, *rightChild;
} Node, *pNode;
//Creates a BST that stores nodes
typedef struct Tree {
    pNode root;
} Tree, *pointer_tree;
//Function creates a node
pNode create_node(int val, char *password) {
    pNode new_node = (Node *) malloc(sizeof(Node));
    if (new_node != NULL) {
        //Makes new_node = to userID and password given
        new_node->leftChild = NULL;
        new_node->rightChild = NULL;
        new_node->userID = val;
        new_node->userPassword = password;
    }
    return new_node;
}
//Creates an empty tree and calls on create_node to allocate the first node
pointer_tree create_tree(int val, char *password) {
    Tree *new_tree = (Tree *) malloc(sizeof(Tree));
    if (new_tree != NULL) {
        new_tree->root = create_node(val, password);
    }
    return new_tree;
}
//This function adds a node to the tree
void add_to_node(pNode root, int val, char *password) {
    //Checks if root is = to the number in the new node
    if (val == root->userID) return;
        //Checks if node has value greater than root
    else if (val > root->userID) {
        if (root->rightChild != NULL) add_to_node(root->rightChild, val, password);
        else root->rightChild = create_node(val, password);
        //Checks if node has value less than root
    } else if (val < root->userID) {
        if (root->leftChild != NULL) add_to_node(root->leftChild, val, password);
        else root->leftChild = create_node(val, password);
    }
}
// function finds height of tree
int height(pNode root) {
    int max_height;
    if (root == NULL) return -1; //Checks to see if tree is empty
    else max_height = 1 + ((height(root->rightChild) > height(root->leftChild)) ? height(root->rightChild) : height(root->leftChild));
    return max_height;
}
// Iterates through tree in order method
void in_Order(pNode root) {
    if (root->leftChild != NULL) in_Order(root->leftChild);
    printf("%d ,", root->userID);
    if (root->rightChild != NULL) in_Order(root->rightChild);
}
// Iterates through tree post order method
void post_Order(pNode root) {
    if (root->leftChild != NULL) post_Order(root->leftChild);
    if (root->rightChild != NULL) post_Order(root->rightChild);
    printf("%d ,", root->userID);
}
// Iterates through tree in preorder method
void pre_Order(pNode root) {
    printf("%d ,", root->userID);
    if (root->leftChild != NULL) pre_Order(root->leftChild);
    if (root->rightChild != NULL) pre_Order(root->rightChild);
}
//Examines tree to see if left and right child exist
int examine_tree(pNode root){
    int left = 0, right = 0;
    if (root->leftChild != NULL) {
        if (root->leftChild->userID > root->userID) left = -1;
        else left = examine_tree(root->leftChild);
    }
    if (root->rightChild != NULL) {
        if (root->rightChild->userID > root->userID) right = -1;
        else right = examine_tree(root->rightChild);
    }
    if (left == -1 || right == -1)
        return -1;
    else return 1;
}
//Counts number of nodes in tree using recursion
int nodes(pNode root) {
    int total;
    if (root == NULL) return 0;
    total = 1 + nodes(root->leftChild) + nodes(root->rightChild);
    return total;
}
//Finds node with specified int val
pNode lookfor_node(pNode root, int val) {
    if (root == NULL) return NULL;
    if (root->userID == val) return root;
    else if (root->userID > val) lookfor_node(root->leftChild, val);
    else if (root->userID < val) lookfor_node(root->rightChild, val);
}
//This function looks for the parent node of the specified int val
pNode lookfor_parent_node(pNode root, int val) {
    if (root == NULL) return root;
    if ((root->leftChild == NULL) && (root->rightChild == NULL)) return root;
    if (root->userID == val) return root;
    else if (root->userID < val) {
        if (root->rightChild->userID == val) return root;
        else lookfor_parent_node(root->rightChild, val);
    } else if (root->userID > val) {
        if (root->leftChild->userID == val) return root;
        else lookfor_parent_node(root->leftChild, val);
    }
}
//This functions deletes a node, it uses recursion to iterate through the tree to find the node to delete
void delete_node(pNode root, pNode parent) {
    pNode node_delete = root;
    if (root->leftChild != NULL) delete_node(root->leftChild, root);
    if (root->rightChild != NULL) delete_node(root->rightChild, root);

    if (parent->leftChild == root) parent->leftChild = NULL;
    if (parent->rightChild == root) parent->rightChild = NULL;
    free(node_delete);
}

int main(void) {
    //Makes pointers to store the contents of each txt file
    char *idents = "/Users/matthewmamelak/Desktop/IDENTS.txt";
    char *deletes = "/Users/matthewmamelak/Desktop/DELETES.TXT";
    char *lookups = "/Users/matthewmamelak/Desktop/LOOKUPS.TXT";
    //Opens txt files and stores information in each associated pointer
    FILE *id = fopen(idents, "r");
    FILE *dlt = fopen(deletes, "r");
    FILE *look = fopen(lookups, "r");
    //If txt files are empty, return an error message
    if (id == NULL) printf("Error: Can't open file %s\n", idents);
    if (dlt == NULL) printf("Error: Can't open file %s\n", deletes);
    if (look == NULL) printf("Error: Can't open file %s\n", lookups);

    //The set of instructions below iterates through the txt file, separates int's from chars and outputs
    //the given ID with its asscoaited password
    int val;
    char *password = (char *) malloc(13 * sizeof(char));
    password[12] = '\0';
    fscanf(id, "%d            %s", &val, password);
    pointer_tree new_tree = create_tree(val, password);
    while (1) {
        int identification;
        char *password = (char *) malloc(13 * sizeof(char));
        password[12] = '\0';
        if (fscanf(id, "%d            %s", &identification, password) == EOF) break;
        add_to_node(new_tree->root, identification, password);
    }
    printf("BST NODES: %d\n", nodes(new_tree->root));
    if (examine_tree == -1) exit(1);
    while (1) {
        int identification;
        if (fscanf(dlt, "%d", &identification) == EOF) break;
        pNode node = lookfor_node(new_tree->root, identification);
        pNode parent = lookfor_parent_node(new_tree->root, identification);
        delete_node(node, parent);
    }
    printf("NODES AFTER DELETES: %d\n", nodes(new_tree->root));
    if (examine_tree == -1) exit(1);
    while (1) {
        int identification;
        if (fscanf(look, "%d", &identification) == EOF) break;
        pNode n = lookfor_node(new_tree->root, identification);
        if (n->userPassword != NULL) printf("ID %d   PASSWORD %s\n", n->userID, n->userPassword);
        else printf("ID %d   PASSWORD <NOT FOUND>", n->userID);
    }
}
