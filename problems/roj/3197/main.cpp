/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 13:00
 * update_at: 2026-10-10 13:00
 */

// 学校网络：Kosaraju 求强连通分量，缩点后数入度 / 出度为 0 的分量
#include <cstdio>
#include <vector>
using namespace std;

int n;
vector<vector<int> > g, rg;

// 第一遍 DFS（迭代版）：返回按完成时间从早到晚排列的点
void finish_order(vector<int>& order) {
    vector<char> seen(n, 0);
    for (int root = 0; root < n; root++) {
        if (seen[root]) {
            continue;
        }
        seen[root] = 1;
        vector<int> sv, si; // 显式栈：(点, 下一条待走出去的边的下标)
        sv.push_back(root);
        si.push_back(0);
        while (!sv.empty()) {
            int v = sv.back();
            int i = si.back();
            if (i == (int)g[v].size()) {
                order.push_back(v); // 出边走完，此刻 v 的完成时间最晚
                sv.pop_back();
                si.pop_back();
                continue;
            }
            si.back() = i + 1;
            int u = g[v][i];
            if (!seen[u]) {
                seen[u] = 1;
                sv.push_back(u);
                si.push_back(0);
            }
        }
    }
}

int main() {
    if (scanf("%d", &n) != 1) {
        return 0;
    }
    g.assign(n, vector<int>());
    rg.assign(n, vector<int>());
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        while (x) { // 0 是名单结束符
            g[i].push_back(x - 1);
            rg[x - 1].push_back(i);
            scanf("%d", &x);
        }
    }

    vector<int> order;
    finish_order(order);

    // 第二遍在反图上按完成时间逆序 DFS
    vector<int> comp(n, -1);
    for (int t = (int)order.size() - 1; t >= 0; t--) {
        int start = order[t];
        if (comp[start] != -1) {
            continue;
        }
        comp[start] = start;
        vector<int> stk;
        stk.push_back(start);
        while (!stk.empty()) {
            int v = stk.back();
            stk.pop_back();
            for (int i = 0; i < (int)rg[v].size(); i++) {
                int u = rg[v][i];
                if (comp[u] == -1) {
                    comp[u] = start;
                    stk.push_back(u);
                }
            }
        }
    }

    vector<char> present(n, 0), has_in(n, 0), has_out(n, 0);
    int comps = 0;
    for (int v = 0; v < n; v++) {
        if (!present[comp[v]]) {
            present[comp[v]] = 1;
            comps++;
        }
        for (int i = 0; i < (int)g[v].size(); i++) {
            int u = g[v][i];
            if (comp[v] != comp[u]) { // 分量内部的边缩点后消失
                has_out[comp[v]] = 1;
                has_in[comp[u]] = 1;
            }
        }
    }
    int sources = 0, sinks = 0;
    for (int v = 0; v < n; v++) {
        if (present[v]) {
            if (!has_in[v]) sources++;
            if (!has_out[v]) sinks++;
        }
    }
    int merged = (comps == 1) ? 0 : (sources > sinks ? sources : sinks);
    printf("%d\n%d\n", sources, merged);
    return 0;
}
