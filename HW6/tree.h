#ifndef TREEH
#define TREEH

#include <stdlib.h>
#include <stdio.h>
#include "rand.h"
#include "opList.h"


// // // // // // // // // // // // // // // // // // // // // // // // 
// Side
//
enum Side {LEFT, RIGHT, SIDEERROR};


// // // // // // // // // // // // // // // // // // // // // // // // 
// Op class
//
// Operators are Op objects that contain a function that
// can be evaluated
//
// This class can be either an operator or a terminal
// 
class Op
{
// data
public:
    double (*f_)(double x, double y);   // function if arity>0
    char *name_;                        // printable name of operator (NULL if constant)
    int arity_;                         // arity of operator
// methods
public:
    Op(char *name, int arity, double (*f)(double x, double y));
};


void initOps(int maxNumOps);
void addOpOrTerm(char *name, int arity, double (*f)(double x, double y));


// // // // // // // // // // // // // // // // // // // // // // // // 
// Tree Class
//
// Note: if a method has default parameters those parameters are
// not intended to be set by the user.  For example getRandTree should
// only be called with one parameter.  The others are for recursion.
//

class Tree
{
// data
private:
    Tree *left_;   // the left child
    Tree *right_;  // the right child
    Tree *up_;     // the parent
    Op *op_;       // the operator for this node (could be a terminal)
    double value_; // the cached value for this node (value if terminal)
    int size_;     // size of the tree beneath this node including this node
    bool used_;    // is the node allocated (provides debugging support)

// class variables
private:
    static int freeListInitSize_;
    static int freeListSize_;
    static int freeListUsed_;
    static Tree *freeList_;

// methods
private:
    void printAux();                    // print helper routine
    void printAuxPre();                 // print helper routine
    int leftLinearize(Tree *appendix);  // used in free()

//
public:
    void init();
    static Tree *get(Op *op, double initValue); // get a node (initValue is optional)
    static Tree *getRandOp();              // get random operator node
    static Tree *getRandTerm();            // get random terminal node
    static Tree *getRandOpOrTerm();        // get random operator or terminal node
    static Tree *getRandTree(int maxDepth, Tree *up=NULL, int depth=1);  // get random tree
    static Tree *getRandFullTree(int maxDepth, Tree *up=NULL, int depth=1); // get random full tree
    static void free(Tree *&freeMe);       // free up a whole tree with freeMe as root
    static void printFreeSpace();



public:
    Tree(Op *op);               // create a tree
    bool check(bool hasParent=false);  // vet the tree
    Tree *copy(Tree *up=NULL);  // the only command that copies any nodes
    int size();                 // size accessor
    int depth();                // depth
    bool isTerm();              // true if terminator
    bool isOp();                // true if operator
    Tree *up();                 // parent accessor
    double value();             // value accessor
    double eval();              // evaluate the tree
    double evalUp();            // evaluate by going from this node up
    void printIndent(int depth=0);  // print internal form of tree
    void print();               // print in nice neat infix expression
    void printPre();            // print in nice neat prefix expression
    bool join(Side s, Tree *subtree);  // add a subtree to a tree
    Side remove();              // remove a subtree from its parent.
                                // THIS WILL NOT FREE THE SUBTREE
                                // returns side removed from in parent
    Tree *pickNode();           // uniformly any node but the root
};

void setX(double x);            // set the x variable

#endif