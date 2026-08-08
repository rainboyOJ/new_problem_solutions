#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> pushed, poped;
vector<int> st;

bool dfs(int i, int j) {
    if (j == n) return true;
    if (!st.empty() && st.back() == poped[j]) {
        int x = st.back();
        st.pop_back();
        if (dfs(i, j + 1)) return true;
        st.push_back(x);
    }
    if (i < n) {
        st.push_back(pushed[i]);
        if (dfs(i + 1, j)) return true;
        st.pop_back();
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        pushed.resize(n);
        poped.resize(n);
        for (int i = 0; i < n; i++) cin >> pushed[i];
        for (int i = 0; i < n; i++) cin >> poped[i];
        st.clear();
        cout << (dfs(0, 0) ? "Yes" : "No") << '\n';
    }

    return 0;
}
