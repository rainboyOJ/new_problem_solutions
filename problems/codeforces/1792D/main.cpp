/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-12 09:22
 * update_at: 2026-11-12 10:05
 */
#include <iostream>
#include <vector>
#include <unordered_set>
#include <cstdint>

using namespace std;

const int maxn = 50000 + 50;
vector<int> a[maxn];
uint64_t a_pref[maxn][15]; // a_pref[i][k] 记录第 i 个排列长度为 k 的前缀哈希
int pos_of[15];

// a_prefixes: 建立 a_i 的前缀 hash 集合，供 q 前来匹配查找
// matched: 记录被逆置换 q 成功找到的有效前缀
unordered_set<uint64_t> a_prefixes;
unordered_set<uint64_t> matched;

// 将一个数字追加到前缀状态末尾（每个数字占用 4 个 bit）
inline uint64_t push_digit(uint64_t mask, int val) {
    return (mask << 4) | val;
}

void solve() {
    int n, m;
    if (!(cin >> n >> m)) return;

    a_prefixes.clear();
    matched.clear();
    a_prefixes.reserve(n * m);
    matched.reserve(n * m);

    // 第一步：建立 a_i 的前缀 map/hash 集合
    for (int i = 0; i < n; ++i) {
        a[i].resize(m);
        uint64_t mask = 0;
        for (int k = 1; k <= m; ++k) {
            cin >> a[i][k - 1];
            mask = push_digit(mask, a[i][k - 1]);
            a_pref[i][k] = mask;
            a_prefixes.insert(mask); // 将 a_i 的前缀存入哈希集合
        }
    }

    // 第二步：对于每个排列计算其逆置换 q，让 q 去 a 的哈希表中寻找！
    for (int j = 0; j < n; ++j) {
        for (int k = 1; k <= m; ++k) {
            pos_of[a[j][k - 1]] = k; // 计算逆置换
        }

        uint64_t mask = 0;
        for (int k = 1; k <= m; ++k) {
            mask = push_digit(mask, pos_of[k]);
            // 让 q 拿着自己的前缀去 a 的哈希集合里寻找
            if (a_prefixes.count(mask)) {
                matched.insert(mask); // 命中！该前缀被某个逆置换 q 成功匹配
            } else {
                break; // 前缀不匹配，后续更长前缀不可能再成立
            }
        }
    }

    // 第三步：输出每个 a[i] 能够匹配到的最大有效前缀长度
    for (int i = 0; i < n; ++i) {
        int max_lcp = 0;
        for (int k = 1; k <= m; ++k) {
            if (matched.count(a_pref[i][k])) {
                max_lcp = k;
            } else {
                break;
            }
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
