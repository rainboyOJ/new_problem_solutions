#include <bits/stdc++.h>
using namespace std;

int n;
string s;

bool check(int len) {
    set<string> st;
    for (int i = 0; i + len - 1 < n; i++) {
        string sub = s.substr(i, len);
        if (st.count(sub)) {
            return false;
        }
        st.insert(sub);
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> s;

    for (int len = 1; len <= n; len++) {
        if (check(len)) {
            cout << len << '\n';
            return 0;
        }
    }

    return 0;
}
