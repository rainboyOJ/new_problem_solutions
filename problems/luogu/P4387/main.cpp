#include <bits/stdc++.h>
using namespace std;

int t, n;
vector<int> pushed, poped;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> t;
    while (t--) {
        cin >> n;
        pushed.resize(n);
        poped.resize(n);
        for (int i = 0; i < n; i++) cin >> pushed[i];
        for (int i = 0; i < n; i++) cin >> poped[i];

        stack<int> st;
        int j = 0;
        for (int x : pushed) {
            st.push(x);
            while (!st.empty() && j < n && st.top() == poped[j]) {
                st.pop();
                j++;
            }
        }

        cout << (st.empty() ? "Yes" : "No") << '\n';
    }

    return 0;
}
