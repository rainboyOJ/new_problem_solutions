/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 20:58
 * update_at: 2026-07-11 21:00
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3005;

int n;
string s;

int lcp[MAXN][MAXN];   // lcp[i][j] 表示 s[i..] 和 s[j..] 的最长公共前缀长度。
int delta_cnt[MAXN][MAXN];
int left_limit[MAXN], right_limit[MAXN];
long long answer_cnt[MAXN];

// 比较 s[i..i+len-1] 和 s[j..j+len-1]。
// 返回 -1/0/1，分别表示前者更小、相等、前者更大。
int compare_sub(int i, int j, int len) {
    int same = lcp[i][j];
    if (same >= len) return 0;
    if (i + same == n) return -1;
    if (j + same == n) return 1;
    if (s[i + same] < s[j + same]) return -1;
    return 1;
}

void build_lcp() {
    for (int i = n - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {
            if (s[i] == s[j]) {
                lcp[i][j] = lcp[i + 1][j + 1] + 1;
            }
        }
    }
}

void solve() {
    build_lcp();

    for (int p = 0; p < n; p++) {
        int b_cand = p + 1;
        for (int len = n; len >= 1; len--) {
            // 右侧第一个严格小于当前位置子串的位置，会抢走 winner。
            while (b_cand < n && compare_sub(p, b_cand, len) <= 0) {
                b_cand++;
            }
            right_limit[len] = min(b_cand + len, n + 1);
        }

        int a_cand = p - 1;
        for (int len = 1; len <= n; len++) {
            // 左侧小于或等于当前位置子串的位置，会因为字典序或最左规则抢走 winner。
            while (a_cand >= 0 && compare_sub(p, a_cand, len) < 0) {
                a_cand--;
            }
            left_limit[len] = a_cand + 1;
        }

        for (int len = 1; len <= n; len++) {
            if (p + len > n) continue;

            int max_k = right_limit[len] - left_limit[len] - 1;
            if (max_k > n) max_k = n;
            if (max_k >= len) {
                delta_cnt[len][max_k]++;
            }
        }
    }

    for (int len = 1; len <= n; len++) {
        int winners = 0;
        for (int k = n; k >= len; k--) {
            winners += delta_cnt[len][k];
            answer_cnt[winners]++;
        }
    }

    for (int v = 1; v <= n; v++) {
        cout << answer_cnt[v] << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> s;
    solve();

    return 0;
}
