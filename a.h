#include<iostream>
using namespace std;
const int N = 100010;

template<class T>
class Stk {
private:
    T stk[N];
    int tt;

public:
    Stk() : tt(-1) {}

    void push(T x) {stk[++tt] = x;}
    
    void pop() {if (tt>=0) tt--;}

    T top() {
        if (tt>0) return stk[tt];
        else throw out_of_range("stk is empty");
    }

    bool empty() {return tt==-1;}

    int size() {return tt+1;}
};


// #include "a.h"

// int main() {
//     Stk<string> s;
//     s.push("sss");
//     s.push("ttt");
//     s.push("ddd");
//     cout << s.size() << endl;
//     cout << s.top() << endl;
//     s.pop();
//     s.pop();
//     cout << s.size() << endl;
//     cout << s.empty() << endl;
//     s.pop();
//     cout << s.size() << endl;
//     cout << s.empty() << endl;
//     return 0;
// }