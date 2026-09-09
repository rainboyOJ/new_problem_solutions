/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-28 19:19
 * update_at: 2026-08-28 19:19
 */
// E. Tree（圣诞树彩球）：选出尽可能多的互不相交连通块，使每个连通块点权和恰为 k。
// 100 分解法（官方）：后序遍历贪心，一旦当前"未切连通部分"内含权和恰为 k 的块就整块切断。
//   判断"是否内含"用 Check 引理：等价于存在权和 >= k 且奇偶性与 k 相同的连通块；
//   奇偶性由权值为 1 的点数决定（权值 2 对奇偶性无贡献）。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;
const int INF = 1e9;

struct Info {
    int cnt[3]; // 当前未切连通部分中权值为 0/1/2 的点数
    int sum;    // 当前未切连通部分的总权和
    int mnOne;  // 部分内所有权值为 1 的节点 x 中，x 处理时刻累计区域和的最小值
    Info() {
        cnt[0] = cnt[1] = cnt[2] = 0;
        sum = 0;
        mnOne = INF;
    }
};

vector<int> g[MAXN]; // 邻接表存树
int c[MAXN];         // 点权 a_i，取值范围 0~2
int n, k;
int ans;             // 已切出的连通块个数

// 合并两个未切部分的信息（mnOne 取两边最小值）。
Info merge_info(const Info& a, const Info& b) {
    Info res;
    res.sum = a.sum + b.sum;
    res.mnOne = min(a.mnOne, b.mnOne);
    for (int i = 0; i < 3; i++) res.cnt[i] = a.cnt[i] + b.cnt[i];
    return res;
}

// 判断当前未切部分 tmp 内是否存在权和恰为 k 的连通块。
// 等价条件（奇偶性引理）：存在权和 >= k 且奇偶性与 k 相同的连通块。
// 1) tmp 整体就满足：sum >= k 且 cnt[1] 奇偶性与 k 相同。
// 2) 否则整块奇偶性不匹配：设 mnOne 取到节点 x（权值 1，处理时刻区域和为 S_x），
//    则 (tmp 去掉 x 下方整棵子树) 与 {x} 的并仍是连通块，权和 = sum - mnOne + 1；
//    若它 >= k 则奇偶性必然匹配（sum 与 k 奇偶相反，S_x 必为偶数时可取 E_x，
//    S_x 为奇数时去掉 x 下方子树的部分奇偶性正好与 k 相同），故由引理断言块存在。
bool check(const Info& tmp) {
    if (tmp.sum < k) return false;
    if (tmp.sum - tmp.mnOne + 1 >= k) return true;
    if (tmp.cnt[1] % 2 == k % 2) return true;
    return false;
}

// 后序遍历：返回以 u 为顶端的"未切连通部分"信息。
// 处理完 u 后若 Check 为真，则整块切断，ans++，并返回空信息。
Info dfs(int u, int p) {
    Info tmp;
    for (int i = 0; i < (int)g[u].size(); i++) {
        int v = g[u][i];
        if (v == p) continue;
        Info sub = dfs(v, u);
        tmp = merge_info(tmp, sub);
    }
    tmp.cnt[c[u]]++;
    tmp.sum += c[u];
    if (c[u] == 1) {
        // u 是权值为 1 的点：记录此刻（含 u 的）累计区域和
        tmp.mnOne = min(tmp.mnOne, tmp.sum);
    }
    if (check(tmp)) {
        tmp = Info(); // 整块切断并重置
        ans++;
    }
    return tmp;
}

// 快读（数据量总和 1e6，防止 scanf 成为瓶颈）。
int read_int() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

int main() {
    int t = read_int();
    while (t--) {
        n = read_int();
        k = read_int();
        for (int i = 1; i <= n; i++) c[i] = read_int();
        for (int i = 1; i < n; i++) {
            int u = read_int(), v = read_int();
            g[u].push_back(v);
            g[v].push_back(u);
        }

        ans = 0;
        dfs(1, 0);
        printf("%d\n", ans);

        // 多组数据清空邻接表
        for (int i = 1; i <= n; i++) g[i].clear();
    }
    return 0;
}