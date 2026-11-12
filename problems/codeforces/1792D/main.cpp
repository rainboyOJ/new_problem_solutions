#include <iostream>
#include <vector>
#include <unordered_set>
#include <cstdint>

using namespace std;

// 将一个数字追加到前缀状态的末尾（每个数字占用 4 个 bit）
inline uint64_t push_digit(uint64_t mask, int val) {
    return (mask << 4) | val;
}

void solve() {
    int n, m;
    if (!(cin >> n >> m)) return;

    vector<vector<int>> a(n, vector<int>(m));
    unordered_set<uint64_t> prefixes;
    prefixes.reserve(n * m);

    // 第一步：读入所有排列，并将每个排列的“逆置换”前缀编码存入哈希集合
    for (int i = 0; i < n; ++i) {
        vector<int> pos_of(m + 1); // pos_of[val] 表示数字 val 所在的位置 (1-based)
        for (int idx = 1; idx <= m; ++idx) {
            cin >> a[i][idx - 1];
            pos_of[a[i][idx - 1]] = idx;
        }

        uint64_t mask = 0;
        for (int val = 1; val <= m; ++val) {
            mask = push_digit(mask, pos_of[val]);
            prefixes.insert(mask);
        }
    }

    // 第二步：对每个原排列 a[i]，逐位查询能在集合中匹配到的最长前缀
    for (int i = 0; i < n; ++i) {
        uint64_t mask = 0;
        int max_lcp = 0;
        for (int idx = 1; idx <= m; ++idx) {
            mask = push_digit(mask, a[i][idx - 1]);
            if (!prefixes.count(mask)) break;
            max_lcp = idx;
        }
        cout << max_lcp << (i == n - 1 ? "" : " ");
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
