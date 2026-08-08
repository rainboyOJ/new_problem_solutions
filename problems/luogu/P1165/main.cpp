#include <bits/stdc++.h>
using namespace std;

int n;
int op, x;
stack<int> st, mx;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    while (n--) {
        cin >> op;
        if (op == 0) {
            cin >> x;
            st.push(x);
            if (mx.empty()) {
                mx.push(x);
            } else {
                mx.push(max(mx.top(), x));
            }
        } else if (op == 1) {
            if (!st.empty()) {
                st.pop();
                mx.pop();
            }
        } else {
            cout << (mx.empty() ? 0 : mx.top()) << '\n';
        }
    }

    return 0;
}
