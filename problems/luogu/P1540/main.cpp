#include <bits/stdc++.h>
using namespace std;

int m, n;
int x;
int ans;
queue<int> q;
bool in_memory[1005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m >> n;

    for (int i = 1; i <= n; i++) {
        cin >> x;

        if (in_memory[x]) {
            continue;
        }

        ans++;
        if ((int) q.size() == m) {
            int oldest = q.front();
            q.pop();
            in_memory[oldest] = false;
        }

        q.push(x);
        in_memory[x] = true;
    }

    cout << ans << '\n';
    return 0;
}
