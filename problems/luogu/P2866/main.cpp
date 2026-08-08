#include <bits/stdc++.h>
using namespace std;

const int maxn = 80000 + 5;

int n;
long long h[maxn];
stack<int> st;
long long ans;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }

    for (int i = n; i >= 1; i--) {
        while (!st.empty() && h[st.top()] < h[i]) {
            st.pop();
        }
        if (st.empty()) {
            ans += (long long) n - i;
        } else {
            ans += (long long) st.top() - i - 1;
        }
        st.push(i);
    }

    cout << ans << '\n';
    return 0;
}
