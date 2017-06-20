#include <iostream>

using namespace std;

struct node{
    node(){
        prev = NULL;
        next = NULL;
    }
    node* prev;
    node* next;
    int val;
};

void print_tree(node* root, int depth){
    if (root == NULL)
        return;

    print_tree(root->next, depth+1);
    for (int k = 0; k < depth; k++)
        cout << "  ";
    cout << root->val << endl;
    print_tree(root->prev, depth+1);
}

void print_tree(node* root){
    print_tree(root, 0);
}

node* arr_to_dll(int* arr, int len){
    if (len < 1)
        return NULL;

    node* start, *cur, *old;
    cur = new node;
    start = cur;
    old = NULL;
    cur->val = arr[0];
    old = cur;

    for (int k = 1; k < len; k++){
        cur = new node;
        cur->prev = old;
        old->next = cur;
        old = cur;
        cur->val = arr[k];
        cur = cur->next;
    }

    return start;
}

void print_dll(node* n){
    while (n != NULL){
        cout << n->val << " ";
        n = n->next;
    }
    cout << endl;
}

int get_len(node* n){
    int len = 0;
    while (n!= NULL){
        len++;
        n = n->next;
    }
    return len;
}

node* get_node_at(node* start, int n){
    node* ans = start;
    //cout << ans << endl;

    for (int k = 0; k < n && ans != NULL; k++)
        ans = ans->next;

    return ans;
}

//top down
node* dll_to_balanced_bst(node* start, int len){
    if (len < 1)
        return NULL;

    if (len == 1){
        start->prev = NULL;
        start->next = NULL;
        return start;
    }
    node* root = get_node_at(start, len/2); //MUST GO FIRST (because left_child messes up the linked list)
    node* left_child = dll_to_balanced_bst(start, len/2);
    node* right_child = dll_to_balanced_bst(root->next, len-len/2-1);

    root->prev = left_child;
    root->next = right_child;
    return root;
}

node* morris_in_order_traversal(node* root){
    node* cur = root;
    node* predecessor = NULL;
    while (cur != NULL){
        if (cur->prev == NULL){
            cout << cur->val << " ";
            cur = cur->next;
        } else {
            //get in order predecessor
            predecessor = cur->prev;
            while (predecessor->next != NULL && predecessor->next != cur)
                predecessor = predecessor->next;

            if (predecessor->next){ //predecessor->next can ONLY be cur
                predecessor->next = NULL;
                cout << cur->val << " ";
                cur = cur->next;
            } else {
                predecessor->next = cur;
                cur = cur->prev;
            }
        }
    }
}


int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    node* dll = arr_to_dll(arr, sizeof(arr)/sizeof(int));
    node* dll2 = arr_to_dll(arr, sizeof(arr)/sizeof(int));

    cout << "DLL: "; print_dll(dll);
    cout << "Tree: " << endl;
    print_tree(dll_to_balanced_bst(dll, get_len(dll)));
    cout << "Morris pre-order traversal: " << endl;

    node* tree = dll_to_balanced_bst(dll2, get_len(dll2));
    morris_in_order_traversal(tree);
    cout << endl;
    morris_in_order_traversal(tree);

    return 0;
}
