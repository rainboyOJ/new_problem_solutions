/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 09:00
 * update_at: 2026-10-09 18:44
 */
// roj 3065《Addition Chains 加成序列》：迭代加深搜索(IDDFS)求最短加成序列。
// 从小到大枚举序列长度 depth，在限定长度内 DFS；第一次找到解时的 depth 就是最小长度。
#include <iostream>

using namespace std;

typedef long long ll;

const int MAXM = 20;   // n <= 100 时最短链长最多 10，20 足够放下任意搜索路径
const int MAXV = 105;  // 值域上界，n <= 100

ll path[MAXM];         // 当前搜索路径 path[0..depth-1]
bool st[MAXM][MAXV];   // st[u][v]：第 u 层这一帧是否已试过候选值 v（按层隔离，等效于每帧一个局部数组）

bool dfs(int u, int depth, ll n) {
    if (u == depth) {
        return path[u - 1] == n;
    }
    // 剪枝1（可行性）：每一步最多让末尾翻倍，
    // 若一路翻倍到序列末尾仍够不到 n，则当前深度一定无解。
    ll max_val = path[u - 1];
    if (max_val * (1 << (depth - u)) < n) {
        return false;
    }
    // 剪枝2（等效冗余）：同一个候选值可能由多组 (i, j) 拼出，本帧内只搜一次。
    for (int v = 1; v <= n; v++) {
        st[u][v] = false;
    }
    // 候选值从大到小枚举，优先逼近 n；i, j 允许相等（i 从 u-1 往 0 扫，j 从 i 往 0 扫）
    for (int i = u - 1; i >= 0; i--) {
        for (int j = i; j >= 0; j--) {
            ll nxt = path[i] + path[j];
            if (nxt > n || nxt <= path[u - 1] || st[u][nxt]) {
                continue;
            }
            st[u][nxt] = true;
            path[u] = nxt;
            if (dfs(u + 1, depth, n)) {
                return true;
            }
        }
    }
    return false;
}

void solve() {
    ll n;
    while (cin >> n && n != 0) {   // 多组测试数据，读到 0 结束
        int depth = 1;
        path[0] = 1;
        while (!dfs(1, depth, n)) {  // 迭代加深：长度不成立就加一
            depth++;
        }
        cout << depth << "   ";      // 题面格式：长度 m 后接 3 个空格
        for (int i = 0; i < depth; i++) {
            cout << path[i] << (i == depth - 1 ? "" : " ");
        }
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
