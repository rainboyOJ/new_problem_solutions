/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 15:23
 * update_at: 2026-10-02 15:23
 *
 * P9725 [EC Final 2022] Chase Game 2
 * 一棵树，Shou 先走，Pang 来追。问最少加多少条边，才能让 Pang 永远抓不到 Shou。
 * 结论：Pang 的必胜点只会出现在“叶子 b + b 的父亲 p”这种局面上，
 *       所以每个叶子必须至少连出去一条“指向非 p 邻点”的新边。
 *       叶子按父亲分组，同组叶子之间连边无效，答案 = max(ceil(L/2), 最大组大小)；
 *       菊花图（含 n<=3）无解，输出 -1。
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 1e5+5;

int n;
int deg[maxn];          // deg[x]：点 x 的度数
int leaf_cnt[maxn];     // leaf_cnt[x]：x 的邻点中有多少个叶子
int eu[maxn], ev[maxn]; // 把树边存下来，后面统计叶子要用

void read_data(){
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; ++i) { // 多测清空
            deg[i] = 0;
            leaf_cnt[i] = 0;
        }
        for (int i = 1; i < n; ++i) {
            int u, v;
            cin >> u >> v;
            eu[i] = u;
            ev[i] = v;
            deg[u]++;
            deg[v]++;
        }

        int maxdeg = 0;
        for (int i = 1; i <= n; ++i) {
            maxdeg = max(maxdeg, deg[i]);
        }
        // 菊花图：所有叶子共用一个父亲，加任何叶子之间的边都会被那个父亲一步吃掉；
        // n<=2 与 n=3 的树也正好是菊花图，一并判掉。
        if (maxdeg == n - 1) {
            cout << -1 << "\n";
            continue;
        }

        // 统计叶子总数 L，以及每个点名下有 t[i] 个叶子儿子
        int L = 0;
        for (int i = 1; i < n; ++i) {
            if (deg[eu[i]] == 1) {
                leaf_cnt[ev[i]]++;
                L++;
            }
            if (deg[ev[i]] == 1) {
                leaf_cnt[eu[i]]++;
                L++;
            }
        }

        int maxGroup = 0;
        for (int i = 1; i <= n; ++i) {
            maxGroup = max(maxGroup, leaf_cnt[i]);
        }

        // 每条新边最多救两个叶子 -> 至少 ceil(L/2) 条；
        // 同一组的叶子之间不能连 -> 最大组里的每个叶子都要单独用一条边 -> 至少 maxGroup 条。
        int ans = max((L + 1) / 2, maxGroup);
        cout << ans << "\n";
    }
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    read_data();
    
    return 0;
}
