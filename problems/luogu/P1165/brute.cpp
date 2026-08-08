#include <bits/stdc++.h>
using namespace std;

int n;
int op, x;
vector<int> st;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    while (n--) {
        cin >> op;
        if (op == 0) {
            cin >> x;
            st.push_back(x);
        } else if (op == 1) {
            if (!st.empty()) {
                st.pop_back();
            }
        } else {
            int ans = 0;
            for (int v : st) {
                ans = max(ans, v);
            }
            cout << ans << '\n';
        }
    }

    return 0;
}
