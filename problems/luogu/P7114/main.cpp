/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 23:26
 * update_at: 2026-11-10 23:26
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 最大字符数 2^20
const int MAXN = (1 << 20) + 100;

int z[MAXN];
int pre_cnt[MAXN];
int suf_cnt[MAXN];
int bit_bucket[30]; // 桶，维护 F(A) <= v 的前缀数量

// Z 函数计算（扩展 KMP）
void build_z(const string& s) {
    int n = s.size();
    z[0] = n;
    int l = 0, r = 0;
    for (int i = 1; i < n; ++i) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        } else {
            z[i] = 0;
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
}

void solve() {
    string s;
    cin >> s;
    int n = s.size();

    build_z(s);

    // 预处理前缀中出现奇数次的字符数
    int cur_mask = 0;
    int odd_count = 0;
    for (int i = 0; i < n; ++i) {
        int c = s[i] - 'a';
        if (cur_mask & (1 << c)) {
            odd_count--;
        } else {
            odd_count++;
        }
        cur_mask ^= (1 << c);
        pre_cnt[i] = odd_count;
    }

    // 预处理后缀中出现奇数次的字符数
    cur_mask = 0;
    odd_count = 0;
    for (int i = n - 1; i >= 0; --i) {
        int c = s[i] - 'a';
        if (cur_mask & (1 << c)) {
            odd_count--;
        } else {
            odd_count++;
        }
        cur_mask ^= (1 << c);
        suf_cnt[i] = odd_count;
    }

    // 清空桶
    for (int v = 0; v <= 26; ++v) {
        bit_bucket[v] = 0;
    }

    long long total_ans = 0;

    // 枚举 AB 的长度 L = len
    // A 必须非空且严格短于 AB，因此 len 从 2 开始
    for (int len = 2; len < n; ++len) {
        // 新增候选 A：长度为 len - 1，下标对应 len - 2
        int f_a = pre_cnt[len - 2];
        for (int v = f_a; v <= 26; ++v) {
            bit_bucket[v]++;
        }

        // 重复出现的 AB 最大延伸长度受到 Z 函数限制
        // 从 len 开始的后缀与原串前缀的最长公共前缀为 z[len]
        int max_lcp = z[len];

        // 枚举周期次数 i: 1, 2, ...
        // 当 i = 1 时，C 的起始位置为 len，一定合法（只要 len < n）
        // 当 i > 1 时，(i - 1) * len <= max_lcp
        for (int cur_len = len; cur_len < n; cur_len += len) {
            if (cur_len - len > max_lcp) {
                break;
            }
            int f_c = suf_cnt[cur_len];
            total_ans += bit_bucket[f_c];
        }
    }

    cout << total_ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) return 0;

    while (t--) {
        solve();
    }

    return 0;
}
