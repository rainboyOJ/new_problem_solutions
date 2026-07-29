#include <bits/stdc++.h>
using namespace std;

class MinStack {
    stack<pair<int, int>> st;

public:
    void push(int v) {
        st.push({v, st.empty() ? v : min(v, st.top().second)});
    }

    void pop() {
        st.pop();
    }

    int top() {
        return st.top().first;
    }

    int getMin() {
        return st.top().second;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q;
    cin >> q;
    MinStack ms;
    while (q--) {
        string op;
        cin >> op;
        if (op == "push") {
            int v;
            cin >> v;
            ms.push(v);
        } else if (op == "pop")
            ms.pop();
        else if (op == "top")
            cout << ms.top() << ' ';
        else
            cout << ms.getMin() << ' ';
    }
    return 0;
}
