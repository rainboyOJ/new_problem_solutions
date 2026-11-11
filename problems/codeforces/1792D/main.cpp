#include <iostream>
#include <vector>
#include <unordered_set>
#include <cstdint>

using namespace std;

void solve() {
    int n, m;
    if (!(cin >> n >> m)) return;

    vector<vector<int>> a(n, vector<int>(m + 1));
    unordered_set<uint64_t> seen;
    // 预估大小以减少 rehash 开销
    seen.reserve(n * m);

    for (int i = 0; i < n; ++i) {
        vector<int> q(m + 1);
        for (int k = 1; k <= m; ++k) {
            cin >> a[i][k];
            // 计算逆置换：数字 a[i][k] 位于位置 k
            q[a[i][k]] = k;
        }

        // 将逆置换 q 的所有前缀以 4-bit 移位编码为 uint64_t
        uint64_t mask = 0;
        for (int k = 1; k <= m; ++k) {
            mask = (mask << 4) | (uint64_t)q[k];
            seen.insert(mask);
        }
    }

    // 逐个查询 a[i] 的最长合法前缀
    for (int i = 0; i < n; ++i) {
        uint64_t mask = 0;
        int ans = 0;
        for (int k = 1; k <= m; ++k) {
            mask = (mask << 4) | (uint64_t)a[i][k];
            if (seen.find(mask) != seen.end()) {
                ans = k;
            } else {
                break;
            }
        }
        cout << ans << (i == n - 1 ? "" : " ");
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
