#include <bits/stdc++.h>
using namespace std;

// -------------------------------
// STACK for undo operations
// -------------------------------
class Stack {
    vector<string> st;
public:
    void push(string s) { st.push_back(s); }
    string pop() {
        if (!st.empty()) {
            string val = st.back();
            st.pop_back();
            return val;
        }
        return "";
    }
    bool empty() { return st.empty(); }
};

// -------------------------------
// QUEUE for borrow requests
// -------------------------------
class Queue {
    deque<string> q;
public:
    void enqueue(string s) { q.push_back(s); }
    string dequeue() {
        if (!q.empty()) {
            string val = q.front();
            q.pop_front();
            return val;
        }
        return "";
    }
    bool empty() { return q.empty(); }
};

// -------------------------------
// LINKED LIST for books
// -------------------------------
struct BookNode {
    int book_id;
    string title;
    BookNode* next;
    BookNode(int id, string t) : book_id(id), title(t), next(nullptr) {}
};

class LinkedList {
public:
    BookNode* head;
    LinkedList() : head(nullptr) {}
    void add_book(int id, string title) {
        BookNode* new_node = new BookNode(id, title);
        new_node->next = head;
        head = new_node;
    }
    void print_books() {
        BookNode* curr = head;
        while (curr) {
            cout << "ID: " << curr->book_id << ", Title: " << curr->title << endl;
            curr = curr->next;
        }
    }
};

// -------------------------------
// BST for fast search
// -------------------------------
struct BSTNode {
    int book_id;
    string title;
    BSTNode* left;
    BSTNode* right;
    BSTNode(int id, string t) : book_id(id), title(t), left(nullptr), right(nullptr) {}
};

class BST {
    BSTNode* root;
    BSTNode* insert(BSTNode* node, int id, string title) {
        if (!node) return new BSTNode(id, title);
        if (id < node->book_id) node->left = insert(node->left, id, title);
        else node->right = insert(node->right, id, title);
        return node;
    }
    string search(BSTNode* node, int id) {
        if (!node) return "Book not found";
        if (id == node->book_id) return node->title;
        if (id < node->book_id) return search(node->left, id);
        return search(node->right, id);
    }
public:
    BST() : root(nullptr) {}
    void insert(int id, string title) { root = insert(root, id, title); }
    string search(int id) { return search(root, id); }
};

// -------------------------------
// HASHING for quick book lookup
// -------------------------------
class BookHash {
    unordered_map<int,string> h;
public:
    void add_book(int id, string title) { h[id] = title; }
    string get_book(int id) { return h.count(id) ? h[id] : "Book not found"; }
};

// -------------------------------
// HEAP for most borrowed books
// -------------------------------
struct Borrow {
    int count;
    int book_id;
    string title;
    bool operator<(const Borrow& other) const { return count < other.count; }
};

class BorrowHeap {
    priority_queue<Borrow> pq;
public:
    void add_borrow(int count, int id, string title) { pq.push({count,id,title}); }
    void top_books() {
        priority_queue<Borrow> temp = pq;
        while (!temp.empty()) {
            Borrow b = temp.top(); temp.pop();
            cout << "Book: " << b.title << ", Borrows: " << b.count << endl;
        }
    }
};

// -------------------------------
// GRAPH for book recommendations
// -------------------------------
class BookGraph {
    unordered_map<string, vector<string>> g;
public:
    void add_edge(string b1, string b2) {
        g[b1].push_back(b2);
        g[b2].push_back(b1);
    }
    void recommend(string book) {
        cout << "Recommendations for " << book << ": ";
        for (auto b: g[book]) cout << b << ", ";
        cout << endl;
    }
};

// -------------------------------
// TRIE for autocomplete
// -------------------------------
struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool isEnd;
    TrieNode() : isEnd(false) {}
};

class Trie {
    TrieNode* root;
public:
    Trie() { root = new TrieNode(); }
    void insert(string s) {
        TrieNode* node = root;
        for (char c: s) {
            if (!node->children[c]) node->children[c] = new TrieNode();
            node = node->children[c];
        }
        node->isEnd = true;
    }
    bool search(string s) {
        TrieNode* node = root;
        for (char c: s) {
            if (!node->children[c]) return false;
            node = node->children[c];
        }
        return node->isEnd;
    }
};

// -------------------------------
// DISJOINT SET for user groups
// -------------------------------
class DisjointSet {
    unordered_map<int,int> parent;
public:
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    void union_set(int x, int y) {
        int px = find(x);
        int py = find(y);
        if (px != py) parent[py] = px;
    }
    void make_set(int x) { parent[x] = x; }
};

// -------------------------------
// MAIN
// -------------------------------
int main() {
    // Stack
    Stack undo_stack;

    // Queue
    Queue borrow_queue;

    // Linked List
    LinkedList books_list;
    books_list.add_book(101,"Python Basics");
    books_list.add_book(102,"Data Structures");
    books_list.add_book(103,"Algorithms");

    // BST
    BST bst;
    bst.insert(101,"Python Basics");
    bst.insert(102,"Data Structures");
    bst.insert(103,"Algorithms");

    // Hash
    BookHash book_hash;
    book_hash.add_book(101,"Python Basics");
    book_hash.add_book(102,"Data Structures");
    book_hash.add_book(103,"Algorithms");

    // Heap
    BorrowHeap borrow_heap;
    borrow_heap.add_borrow(10,101,"Python Basics");
    borrow_heap.add_borrow(7,102,"Data Structures");
    borrow_heap.add_borrow(5,103,"Algorithms");

    // Graph
    BookGraph book_graph;
    book_graph.add_edge("Python Basics","Data Structures");
    book_graph.add_edge("Python Basics","Algorithms");

    // Trie
    Trie trie;
    trie.insert("Python Basics");
    trie.insert("Data Structures");
    trie.insert("Algorithms");

    // Disjoint Set
    DisjointSet ds;
    ds.make_set(1);
    ds.make_set(2);
    ds.make_set(3);
    ds.union_set(1,2);

    // -------------------------------
    // Demo Outputs
    cout << "\n--- Linked List Books ---\n";
    books_list.print_books();

    cout << "\n--- BST Search ---\n";
    cout << "Book ID 102: " << bst.search(102) << endl;

    cout << "\n--- Hash Lookup ---\n";
    cout << "Book ID 103: " << book_hash.get_book(103) << endl;

    cout << "\n--- Heap Top Books ---\n";
    borrow_heap.top_books();

    cout << "\n--- Graph Recommendations ---\n";
    book_graph.recommend("Python Basics");

    cout << "\n--- Trie Search ---\n";
    cout << "Search 'Data Structures': " << (trie.search("Data Structures") ? "Found" : "Not Found") << endl;

    cout << "\n--- Borrow Queue ---\n";
    borrow_queue.enqueue("User1 borrowed Python Basics");
    borrow_queue.enqueue("User2 borrowed Data Structures");
    while(!borrow_queue.empty()) cout << borrow_queue.dequeue() << endl;

    cout << "\n--- Undo Stack ---\n";
    undo_stack.push("Added Book: Python Basics");
    undo_stack.push("Added Book: Data Structures");
    while(!undo_stack.empty()) cout << undo_stack.pop() << endl;

    cout << "\n--- Disjoint Set ---\n";
    cout << "Are 1 and 2 connected? " << (ds.find(1) == ds.find(2) ? "Yes" : "No") << endl;
    cout << "Are 1 and 3 connected? " << (ds.find(1) == ds.find(3) ? "Yes" : "No") << endl;

    return 0;
}