#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
ifstream fin("mergeheap.in");
ofstream fout("mergeheap.out");
struct node
{
    int value;
    node* child;
    node* sibling;
    node(int n_value = -1)
    {
        value = n_value;
        child = sibling = NULL;
    }
};
class heap
{
public:
    heap(int n_value){ root = new node(n_value); }
    heap(node* n_root = NULL){ root = n_root; }
    void set_root(node* nod) {root = nod;}
    node* get_root() const {return root; }
    int get_root_value() const {return root->value; }
    void insert_value(int value)
    {
        if(root)
        {
        node* temp = new node(value);
        root = merge_roots(root, temp);
        }
        else root = new node(value);
    }
    void merge_heaps(heap other)
    {
        root = merge_roots(root, other.get_root());
    }
    void delete_root()
    {
        node* temp = root;
        root = two_pass(root->child);
        delete temp;
    }

protected:
    node* merge_roots(node* root1, node* root2);
    node* two_pass(node* nod);

private:
    node* root;

};
node* heap::merge_roots(node* root1, node* root2)
{
    if(!root2)
        return root1;
    if(!root1)
        return root2;
    else if(root1->value > root2->value)
    {
        root2->sibling = root1->child;
        root1->child = root2;
        return root1;
    }
    else
    {
        root1->sibling = root2->child;
        root2->child = root1;
        return root2;

    }
}
node* heap::two_pass(node* nod)
{
    if(!nod || !nod->sibling)
        return nod;

    node* next_node = nod->sibling->sibling;

    node* A, *B;
    A = nod;
    B = nod->sibling;
    A->sibling = NULL;
    B->sibling = NULL;

    return merge_roots(merge_roots(A, B), two_pass(next_node));
}
int main()
{
    int N, Q, op, mult1, mult2, x;
    vector<heap> heaps(101);
    fin >> N >> Q;

    for(int index = 1; index <= Q; index++)
    {
        fin >> op;
        if(op == 1)
        {
            fin >> mult1 >> x;
            heaps[mult1].insert_value(x);
        }
        else if(op == 2)
        {
            fin >> mult1;
            fout << heaps[mult1].get_root_value() << '\n';
            heaps[mult1].delete_root();
        }
        else
        {
            fin >> mult1 >> mult2;
            heaps[mult1].merge_heaps(heaps[mult2]);
            heaps[mult2].set_root(NULL);
        }
    }


    return 0;
}
