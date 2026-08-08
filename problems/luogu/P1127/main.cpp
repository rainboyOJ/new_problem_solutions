/**
 * P1127 词链
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n;
char words[MAXN][MAXN];
int indeg[26], outdeg[26];
int adj[26][MAXN];   // adj[letter][i] = word index
int adj_cnt[26];
bool used[MAXN];
char ans[MAXN][MAXN];
int ans_cnt;

void dfs(int u) {
    // 遍历所有以字母 u 开头的单词
    for (int i = 0; i < adj_cnt[u]; ++i) {
        int wid = adj[u][i];
        if (used[wid]) continue;
        used[wid] = true;
        int v = words[wid][strlen(words[wid]) - 1] - 'a';
        dfs(v);
        strcpy(ans[++ans_cnt], words[wid]);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%s", words[i]);
        int len = strlen(words[i]);
        int s = words[i][0] - 'a';
        int e = words[i][len - 1] - 'a';
        ++outdeg[s];
        ++indeg[e];
        adj[s][adj_cnt[s]++] = i;
    }
    // 对每个字母的单词按字典序排序（反序，因为 DFS 是倒序输出的）
    for (int i = 0; i < 26; ++i)
        sort(adj[i], adj[i] + adj_cnt[i], [](int a, int b) {
            return strcmp(words[a], words[b]) > 0;
        });
    // 找起点：出度 = 入度 + 1 的字母
    int start = -1;
    int start_cnt = 0, end_cnt = 0;
    for (int i = 0; i < 26; ++i) {
        int diff = outdeg[i] - indeg[i];
        if (diff == 1) ++start_cnt, start = i;
        else if (diff == -1) ++end_cnt;
        else if (diff != 0) { puts("***"); return 0; }
    }
    if (start_cnt > 1 || end_cnt > 1) { puts("***"); return 0; }
    if (start == -1) { // 欧拉回路，找第一个有出度的字母
        for (int i = 0; i < 26; ++i)
            if (outdeg[i]) { start = i; break; }
    }
    dfs(start);
    if (ans_cnt != n) { puts("***"); return 0; }
    for (int i = ans_cnt; i >= 1; --i)
        printf("%s%c", ans[i], i == 1 ? '\n' : '.');
    return 0;
}
