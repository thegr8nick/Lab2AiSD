#include<bintree.h>
#include<iomanip>

int main()
{
    BinTree<int> tree1;
    BinTree<int> tree2;
    tree1.insert(5);
    tree1.insert(7);
    tree1.insert(10);
    tree1.insert(8);
    tree2.insert(5);
    tree2.insert(7);
    tree2.insert(10);
    tree2.insert(8);
    tree1.insert(11);
    differenceTrees(tree1, tree2);
    cout << endl;
    intersectionTrees(tree1, tree2);

}