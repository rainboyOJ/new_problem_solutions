/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 13:00
 * update_at: 2026-10-10 13:00
 */

// 最小路径覆盖：先预传递成闭包，再求二分图最大匹配，答案是 n - 最大匹配
#include <cstdio>
#include <vector>
using namespace std;

struct Frame { // 匈牙利算法的显式栈帧
    int u;  // 左部点
    int i;  // 下一个待试邻居下标
    int v;  // 选中的右部点
};

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) {
        return 0;
    }
    vector<vector<int> > adj(n + 1);
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        adj[x].push_back(y);
    }

    // 每个点沿有向边能到达的点集（不含自己）
    vector<vector<int> > reach(n + 1);
    for (int src = 1; src <= n; src++) {
        vector<char> seen(n + 1, 0);
        vector<int> q = adj[src];
        for (int i = 0; i < (int)q.size(); i++) {
            seen[q[i]] = 1; // 先整层标记，避免多边把同一个点重复入队
        }
        for (int h = 0; h < (int)q.size(); h++) {
            int u = q[h];
            for (int i = 0; i < (int)adj[u].size(); i++) {
                int v = adj[u][i];
                if (!seen[v]) {
                    seen[v] = 1;
                    q.push_back(v);
                }
            }
        }
        reach[src] = q;
    }

    vector<int> match_l(n + 1, 0), match_r(n + 1, 0); // 0 表示未配对
    int pairs = 0;
    for (int root = 1; root <= n; root++) {
        if (match_l[root]) {
            continue;
        }
        vector<char> used(n + 1, 0); // 本次搜索走过的右部点
        vector<Frame> stk;
        Frame first = {root, 0, 0};
        stk.push_back(first);
        while (!stk.empty()) {
            Frame& fr = stk.back();
            vector<int>& nbr = reach[fr.u];
            int i = fr.i;
            while (i < (int)nbr.size() && used[nbr[i]]) {
                i++;
            }
            fr.i = i + 1;
            if (i == (int)nbr.size()) { // 没有别的出路，回溯
                stk.pop_back();
                continue;
            }
            int v = nbr[i];
            used[v] = 1;
            fr.v = v;
            if (match_r[v] == 0) { // 右部点空闲，增广路打通
                break;
            }
            Frame nf = {match_r[v], 0, 0}; // 让 v 的原配点另寻出路
            stk.push_back(nf);
        }
        if (!stk.empty()) { // 栈非空说明增广成功
            for (int t = 0; t < (int)stk.size(); t++) {
                match_l[stk[t].u] = stk[t].v;
                match_r[stk[t].v] = stk[t].u;
            }
            pairs++;
        }
    }
    printf("%d\n", n - pairs);
    return 0;
}
