/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-13 13:32
 * update_at: 2026-08-13 13:32
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

int n;
string word[MAXN];                    // 单词，下标从 1 开始
int best_overlap[MAXN][MAXN];         // best_overlap[i][j]：i 接 j 的最小合法正重叠长度，0 表示不能接
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

// 求单词 i 接单词 j 的最小合法正重叠长度。
// 重叠长度必须严格小于两个单词的长度，否则一个单词会被另一个完全包含。
int get_best_overlap(int i, int j) {
    int limit = min((int)word[i].size(), (int)word[j].size()) - 1;
    for (int k = 1; k <= limit; k++) {
        if (same_overlap(word[i], word[j], k)) {
            return k;
        }
    }
    return 0;
}

// dfs(last, cur_len)：当前龙以单词 last 结尾，总长度为 cur_len。
// 枚举下一个能接的单词 nxt，进入递归前 used[nxt]++，返回后 -- 完成回溯。
void dfs(int last, int cur_len) {
    if (cur_len > ans) {
        ans = cur_len;
    }

    for (int nxt = 1; nxt <= n; nxt++) {
        if (used[nxt] >= 2) {                 // 每个单词最多使用两次
            continue;
        }
        if (best_overlap[last][nxt] == 0) {   // 不能首尾相接
            continue;
        }

        used[nxt]++;
        dfs(nxt, cur_len + (int)word[nxt].size() - best_overlap[last][nxt]);
        used[nxt]--;
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

    // 预处理任意两个单词之间的最小合法正重叠长度。
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            best_overlap[i][j] = get_best_overlap(i, j);
        }
    }

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
