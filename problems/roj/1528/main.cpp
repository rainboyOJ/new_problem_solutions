/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 06:30
 * update_at: 2026-10-05 06:30
 */
// main.cpp：把每个单词看成一条首字母 -> 末字母的有向边，
// 判定整张有向多重图是否存在欧拉路径。
#include <cstdio>
#include <cstring>

typedef long long ll;

const int ALPHA = 26; // 小写字母只有 26 个顶点

int root[ALPHA];      // 并查集：判非零度字母是否弱连通
int out_deg[ALPHA];   // out_deg[c] 为以字母 c 开头的单词个数
int in_deg[ALPHA];    // in_deg[c] 为以字母 c 结尾的单词个数

// 并查集查根，带路径压缩
int find_root(int x) {
    while (root[x] != x) {
        root[x] = root[root[x]];
        x = root[x];
    }
    return x;
}

void merge_set(int a, int b) {
    int ra = find_root(a);
    int rb = find_root(b);
    if (ra != rb) {
        root[ra] = rb;
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        ll n;
        scanf("%lld", &n);

        for (int c = 0; c < ALPHA; c++) {
            root[c] = c;
            out_deg[c] = 0;
            in_deg[c] = 0;
        }

        char word[1005]; // 单词长度不超过 1000，只需要首末字母
        for (ll i = 1; i <= n; i++) {
            scanf("%s", word);
            int u = word[0] - 'a';
            int v = word[strlen(word) - 1] - 'a';
            out_deg[u]++;
            in_deg[v]++;
            merge_set(u, v); // 无向意义下合并，弱连通靠它判断
        }

        // 收集所有非零度的字母
        int used[ALPHA];
        int used_cnt = 0;
        for (int c = 0; c < ALPHA; c++) {
            if (in_deg[c] > 0 || out_deg[c] > 0) {
                used[used_cnt] = c;
                used_cnt++;
            }
        }

        // 条件一：所有非零度字母必须在同一个弱连通分量里
        int ok_connected = 1;
        for (int i = 1; i < used_cnt; i++) {
            if (find_root(used[i]) != find_root(used[0])) {
                ok_connected = 0;
                break;
            }
        }

        // 条件二：每个字母 out-in 只能是 0 或 ±1，且 +1、-1 各至多一个
        int cnt_plus = 0;   // out-in == 1 的字母个数（欧拉路径起点）
        int cnt_minus = 0;  // out-in == -1 的字母个数（欧拉路径终点）
        int ok_degree = 1;
        for (int i = 0; i < used_cnt; i++) {
            int c = used[i];
            int gap = out_deg[c] - in_deg[c];
            if (gap > 1 || gap < -1) {
                ok_degree = 0;
                break;
            }
            if (gap == 1) {
                cnt_plus++;
            }
            if (gap == -1) {
                cnt_minus++;
            }
        }
        if (cnt_plus > 1 || cnt_minus > 1) {
            ok_degree = 0;
        }

        if (ok_connected && ok_degree) {
            printf("Ordering is possible.\n");
        } else {
            printf("The door cannot be opened.\n");
        }
    }
    return 0;
}
