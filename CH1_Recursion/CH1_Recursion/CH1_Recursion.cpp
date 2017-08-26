/*
 
CH1: Recursion
 
 */


#include <iostream>
#include <string>
#include <memory>
#include <exception>
#include <vector>

using namespace std;


/* ---------------------------------------------------------------------
 
 Iterative and recursive solutions for basic mathemeatics
 
 --------------------------------------------------------------------- */
class Solution {
public:
    virtual unsigned int sumOfSeries(unsigned int n) = 0;
    virtual unsigned int factorial(unsigned int n) = 0;
    virtual int power(int n, int exp) = 0;
    virtual string getName() = 0;
    
    void execute(unsigned int n){
        cout << endl << endl;
        cout << "Executing " << getName() << "..." << endl;
        cout << "Sum of series: " << sumOfSeries(n) << endl;
        cout << "Factorial: " << factorial(n) << endl;
        cout << "Power: " << power(n,n) << endl;
    }
};

class RecursiveSolution : public Solution {
public:
    
    string getName() { return _NAME; }
    
    unsigned int sumOfSeries(unsigned int n){
        
        return n==0 ? 0 : n + sumOfSeries(n-1);
    }
    
    unsigned int factorial(unsigned int n){
        
        if (n==0 || n==1) { return 1; }
        return n * factorial(n-1);
    }
    
    int power(int n, int exp){
        
        if (exp==0) { return 1; }
        if (exp==1) { return n; }
        
        return n * power(n, exp-1);
    }
    
private:
    static constexpr const char* _NAME = "Recursive Solution";
};
                
class IterativeSolution : public Solution {
public:
    
    string getName() { return _NAME; }
    
    unsigned int sumOfSeries(unsigned int n){
        
        unsigned int res = 0;
        
        while(n>0){ res += n--; }
        
        return res;
    }
    
    unsigned int factorial(unsigned int n){
     
        unsigned int res = 1;
        
        while(n>1){ res *= n--; }
        
        return res;
    }
    
    int power(int n, int exp){
        
        int res = n;
        
        if (exp==0) { return 1; }
        if (exp==1) { return n; }
        
        while(exp-- > 1){ res *= n; }
        
        return res;
    }
    
private:
    static constexpr const char* _NAME = "Iterative Solution";
};


/* ---------------------------------------------------------------------
 
 Recursion example: towers of hanoi
 
 --------------------------------------------------------------------- */
template<class T>
class TowersOfHanoi{
public:
    void move(vector<T>& src, vector<T>& dst, vector<T>& aux, unsigned int n){
        
        if (n==0) { return; }
        
        move(src, aux, dst, n-1); // move n-1 from src to aux
        
        dst.push_back(src.back()); src.pop_back(); // move nth from src to dst
        
        move(aux, dst, src, n-1); // move n-1 from aux to dst
    }
};


/* ---------------------------------------------------------------------
 
 Linked List
 
 --------------------------------------------------------------------- */
template<class T>
class Node {
public:
    T val;
    shared_ptr<Node<T>> next;
    Node(T val) : val{val}, next{NULL} {}
};

template<class T>
class LinkedList{
public:
    
    LinkedList() : _head{NULL}, _tail{NULL} {}
    
    void addNode(T val){
        auto node = make_shared<Node<T>>(val);
        
        if (!_tail){
            _tail = node;
            _head = _tail;
        } else {
            _tail->next = make_shared<Node<T>>(val);
            _tail = _tail->next;
        }
    }
    
    string toString(bool forwards=true){
        
        string res;
        
        if (forwards) { res = toStringForwards(_head);  }
        else          { res = toStringBackwards(_head); }
    
        res.pop_back(); res.pop_back(); // remove trailing "->"
        return res;
    }
    
private:

    string toStringForwards(shared_ptr<Node<T>> node){ // iterative
        
        string res;
        
        shared_ptr<Node<T>> itr = node;
        while(itr){
            res += to_string(itr->val) + "->";
            itr=itr->next;
        }
        
        return res;
    }
    
    string toStringBackwards(shared_ptr<Node<T>> node){ // recursive
        
        if (!node) { return ""; }
        string remaining = toStringBackwards(node->next);
        return remaining + to_string(node->val) + "->";
    }
    
    shared_ptr<Node<T>> _head;
    shared_ptr<Node<T>> _tail;
};


/* ---------------------------------------------------------------------
 
 Tree traversals
 
 --------------------------------------------------------------------- */
template<class T>
class TreeNode {
public:
    T val;
    shared_ptr<TreeNode<T>> left;
    shared_ptr<TreeNode<T>> right;
    
    TreeNode(T val) : val{val}, left{nullptr}, right{nullptr} {}
};

template<class T>
class Traverser {
public:
    
    enum Order { PRE, IN, POST };
    
    string traverse(shared_ptr<TreeNode<T>> node, Order order){
        
        if (!node) { return ""; }

        string parent = to_string(node->val);
        string left_child, right_child;
        if (node->left)  { left_child  = traverse(node->left, order);  }
        if (node->right) { right_child = traverse(node->right, order); }
        
        switch(order){
            case Order::PRE:  return parent       + left_child    + right_child;
            case Order::IN:   return left_child   + parent        + right_child;
            case Order::POST: return left_child   + right_child   + parent;
        }
    }
};


/* ---------------------------------------------------------------------
 
 Bubble Sort
 
 --------------------------------------------------------------------- */

class Sorcerer {
    
public:
    
    enum Level {
        One,
        Two,
        Three,
        Seventy
    };
    
    Sorcerer(string name, Sorcerer::Level level) : _name{name}, _level{level} {}
    
    string to_string(){
        string str_lvl;
        switch (_level){
            case Sorcerer::Level::One: str_lvl = "One";
                break;
            case Sorcerer::Level::Two: str_lvl = "Two";
                break;
            case Sorcerer::Level::Three: str_lvl = "Three";
                break;
            case Sorcerer::Level::Seventy: str_lvl = "ShhhhEVENTY!";
                break;
        }
        return _name + "(level " + str_lvl + " sorcerer)";
    }
    
    bool operator<(const Sorcerer& rhs){
        return _level < rhs._level;
    }

    
private:
    
    Level _level;
    string _name;
    
};

template<class T>
class Sorter{
public:
    
    void print(vector<T>& items){
        for (auto item : items){
            cout << item.to_string() << endl;
        }
        cout << endl;
    }
    
    void bubble1(vector<T>& items){
        
        for (int i=0; i < items.size()-1; i++){
            for (int j=i+1; j < items.size(); j++){
                if (items[i] < items[j]){ swap(items[i], items[j]); }
            }
        }
    }
    
    void bubble2(vector<T>& items){
        return bubble2(items,(int)items.size());
    }
    
    void bubble2(vector<T>& items, int n){
        
        if (n <= 1){
            return;
        }
        
        // sort n ( bubble smallest to the right-most position )
        for (int i=0; i < n-1; i++){
            if (items[i] < items[i+1]){ swap(items[i], items[i+1]); }
        }
        
        // sort remaining n-1
        bubble2(items, n-1);
    }
    
    void swap(T& a, T& b){
        T temp = a;
        a = b;
        b = temp;
    }
};


int main(int argc, const char * argv[]) {

    /*
    int n, exp;
    auto isol = make_shared<IterativeSolution>();
    auto rsol = make_shared<RecursiveSolution>();
    
    cout << "Input n: ";
    cin >> n;
    isol->execute(n);
    rsol->execute(n);
    */
    
    
    
    /*
    TowersOfHanoi<int> toh;
    vector<int> src { 1, 2, 3, 4, 5 };
    vector<int> dst {}, aux{};
    toh.move(src,dst,aux,(int)src.size());
    */
    
    
    /*
    LinkedList<int> list;

    list.addNode(1);
    list.addNode(2);
    list.addNode(3);
    
    cout << "Forwards: " << list.toString() << endl;
    cout << "Backwards: " << list.toString(false) << endl;
    */
    
    

    
    /*
 
    auto root = make_shared<TreeNode<int>>(0);
    root->left = make_shared<TreeNode<int>>(1);
    root->right = make_shared<TreeNode<int>>(2);
    root->left->left = make_shared<TreeNode<int>>(3);
    root->left->right = make_shared<TreeNode<int>>(4);
    //
    //
    //     0
    //    / \
    //   1   2
    //  / \
    // 3   4
    //
    //     pre: 0, 1, 3, 4, 2
    //      in: 3, 1, 4, 0, 2
    //     pst: 3, 4, 1, 2, 0
    //     
    //
    
    Traverser<int> t;
    cout << "pre: " << t.traverse(root, Traverser<int>::Order::PRE) << endl;
    cout << "in: " << t.traverse(root, Traverser<int>::Order::IN) << endl;
    cout << "post: " << t.traverse(root, Traverser<int>::Order::POST) << endl;
    
    */
    
    
    
    Sorter<Sorcerer> sorter;
    
    vector<Sorcerer> sorcerers {
        
        Sorcerer("Jeff", Sorcerer::Level::One),
        Sorcerer("Jessica", Sorcerer::Level::Seventy),
        Sorcerer("Abner", Sorcerer::Level::Two),
        Sorcerer("Cyrus", Sorcerer::Level::Two),
        Sorcerer("Boden", Sorcerer::Level::Three)
    };
    
    cout << "Before bubble sorting..." << endl;
    sorter.print(sorcerers);
    
    sorter.bubble2(sorcerers);
    
    cout << endl << endl << endl << "After bubble sorting..." << endl;
    sorter.print(sorcerers);
    
    //
    // lambda expression to sort alphabetically
    //
    sort(sorcerers.begin(), sorcerers.end(),
         [](Sorcerer& lhs, Sorcerer& rhs) { return lhs.to_string() < rhs.to_string(); });
    
    cout << endl << endl << endl << "Alphabetical..." << endl;
    sorter.print(sorcerers);
    
    return 0;
}







