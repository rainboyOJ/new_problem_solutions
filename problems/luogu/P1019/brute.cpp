/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-13 13:32
 * update_at: 2026-08-13 13:32
 */
// brute.cpp：小数据暴力解，把每一步接龙看成选择序列来递归枚举。
// 每一层递归做两个选择：接哪个单词、采用哪种合法重叠长度。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

int n;
string word[MAXN];                    // 单词，下标从 1 开始
vector<int> overlap_list[MAXN][MAXN]; // overlap_list[i][j]：i 接 j 的所有合法重叠长度
int used[MAXN];                       // used[i]：单词 i 已经使用的次数（最多 2 次）
char start_ch;                        // 龙的开头字母
int ans;                              // 最长接龙长度

// 判断 s 的后 k 个字符是否等于 t 的前 k 个字符。
bool same_overlap(const string &s, const string &t, int k) {
    int len_s = (int)s.size();
    for (int i = 0; i < k; i++) {
        if (s[len_s - k + i] != t[i]) {
            return false;
        }
    }
    return true;
}

// 预处理：枚举 1 <= k <= min(|s|,|t|) - 1 的所有合法重叠长度。
// 上界排除“一个单词被另一个完全包含”的非法情况。
void build_overlap_list() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            overlap_list[i][j].clear();
            int limit = min((int)word[i].size(), (int)word[j].size()) - 1;
            for (int k = 1; k <= limit; k++) {
                if (same_overlap(word[i], word[j], k)) {
                    overlap_list[i][j].push_back(k);
                }
            }
        }
    }
}

// 暴力 DFS：这一层先选下一个单词 nxt，再选一种合法重叠长度。
// 与最终解不同：这里保留全部重叠长度，完全照题意枚举，只适合小数据。
void dfs(int last, int cur_len) {
    if (cur_len > ans) {
        ans = cur_len;
    }

    for (int nxt = 1; nxt <= n; nxt++) {
        if (used[nxt] >= 2) {                 // 每个单词最多使用两次
            continue;
        }
        int sz = (int)overlap_list[last][nxt].size();
        for (int i = 0; i < sz; i++) {        // 每一种合法重叠长度都试一遍
            int overlap_len = overlap_list[last][nxt][i];
            used[nxt]++;
            dfs(nxt, cur_len + (int)word[nxt].size() - overlap_len);
            used[nxt]--;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> word[i];
    }
    cin >> start_ch;

    build_overlap_list();

    // 从所有以 start_ch 开头的单词出发各搜一次，每个起点用掉该单词一次。
    for (int i = 1; i <= n; i++) {
        if (word[i][0] != start_ch) {
            continue;
        }
        memset(used, 0, sizeof(used));
        used[i] = 1;
        dfs(i, (int)word[i].size());
    }

    cout << ans << '\n';
    return 0;
}
