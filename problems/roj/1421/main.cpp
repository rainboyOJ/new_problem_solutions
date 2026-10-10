/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 15:12
 * update_at: 2026-10-07 15:12
 */
// roj 1421 Floyd：读懂题面那段异或求和程序，先用 Floyd 求出全部点对最短路，
// 再照抄那段程序逐对异或。与 main.py 是同一算法。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 505;               // n <= 500，多开几位
const ll INF = 10000000000000000LL; // 不可达标记 1e16，与题面程序里的 f 同值

int n, m;
ll dis[MAXN][MAXN]; // dis[i][j] = i 到 j 的当前最短距离，不可达时为 INF

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) dis[i][j] = INF;
        dis[i][i] = 0; // 题面规定 Dis(i,i) = 0
    }
    for (int e = 1; e <= m; e++) {
        int s, t;
        ll d;
        scanf("%d %d %lld", &s, &t, &d);
        if (d < dis[s][t]) dis[s][t] = d; // 有重边，只留最短的一条
    }

    // Floyd：外层枚举中转点 k，内层尝试用 i->k->j 松弛 i->j
    for (int k = 1; k <= n; k++) {
        ll *dk = dis[k]; // 第 k 行，本轮所有松弛都要用它
        for (int i = 1; i <= n; i++) {
            ll *di = dis[i];
            if (di[k] == INF) continue; // 到不了中转点 k，这一轮 i 松弛不了任何点
            for (int j = 1; j <= n; j++) {
                // k 到不了 j 时 dk[j] = INF 必须先跳过：边权可以是负数，
                // 否则 INF + 负数 < INF，会把"不可达"当成一条超长的路写进 di[j]
                if (dk[j] == INF) continue;
                ll nd = di[k] + dk[j]; // di[k] 不提出循环：j == k 时这一格会被本循环改写
                if (nd < di[j]) di[j] = nd;
            }
        }
    }

    // 照抄题面程序：把所有点对的 Dis(i,j) + f 异或起来（不可达点对贡献 2f）
    ll S = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) S ^= dis[i][j] + INF;

    printf("%lld\n", S);
    return 0;
}
