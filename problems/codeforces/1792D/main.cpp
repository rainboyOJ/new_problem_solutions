/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-12 09:22
 * update_at: 2026-11-12 09:35
 */
#include <iostream>
#include <vector>
#include <unordered_set>
#include <cstdint>

using namespace std;

const int maxn = 50000 + 50;
vector<int> a[maxn]; // 全局数组：a[i] 保存第 i 个排列
int pos_of[15];      // pos_of[val] 记录数字 val 在当前排列中的位置 (1-based)

// 哈希集合：存储所有逆置换的前缀状态
// 数值范围 1~10，每个数位占用 4 bit，长度最多 10 的前缀只需 40 bit，存入 uint64_t 属于绝对无冲突的完美单射
unordered_set<uint64_t> prefixes;

// 将一个数字追加到前缀状态的末尾（每个数字占用 4 个 bit）
inline uint64_t push_digit(uint64_t mask, int val) {
    return (mask << 4) | val;
}

void solve() {
    int n, m;
    if (!(cin >> n >> m)) return;

    prefixes.clear();
    prefixes.reserve(n * m); // 预分配空间，避免频繁 rehash 开销

    // 第一步：读入所有排列，并将每个排列的“逆置换”前缀编码存入哈希集合
    for (int i = 0; i < n; ++i) {
        a[i].resize(m);
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
