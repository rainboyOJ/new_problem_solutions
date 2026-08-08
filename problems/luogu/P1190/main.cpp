#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;

int n, m;
int w[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }

    priority_queue<int, vector<int>, greater<int> > q;
    int ans = 0;

    for (int i = 1; i <= m; i++) {
        q.push(w[i]);
        ans = max(ans, w[i]);
    }

    for (int i = m + 1; i <= n; i++) {
        int earliest = q.top();
        q.pop();
        q.push(earliest + w[i]);
        ans = max(ans, earliest + w[i]);
    }

    cout << ans << '\n';

    return 0;
}
