/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 13:00
 * update_at: 2026-10-10 13:00
 */

// 基环树森林：剥掉挂树后每个环单独 DP，求最多能投放多少个元素
#include <cstdio>
#include <vector>
using namespace std;

typedef long long ll;

const ll NEG = -(1LL << 50); // 非法状态；合法值恒为非负
const int NO_CHILD = 2;      // gain 的初值：没有孩子就付不出“牺牲”

int n;
vector<int> parent; // parent[u] 就是题面的 A[u]
vector<int> indeg;  // 入度 = 孩子个数；> 0 表示落在某个环上
vector<int> off;    // off[v]：v 不投放时，v 的子树（不含 v）最多能投放多少个
vector<int> gain;   // gain[v]：逼 v 的某个孩子不投放所需的最小牺牲

// 剥掉所有不在环上的点，自底向上把每棵挂树压成两个数
void peel_trees() {
    indeg.assign(n + 1, 0);
    for (int v = 1; v <= n; v++) {
        indeg[parent[v]]++;
    }
    off.assign(n + 1, 0);
    gain.assign(n + 1, NO_CHILD);
    vector<int> stk;
    for (int v = 1; v <= n; v++) {
        if (indeg[v] == 0) {
            stk.push_back(v); // 环外的叶子先入栈
        }
    }
    while (!stk.empty()) {
        int v = stk.back();
        stk.pop_back();
        int slack = (gain[v] >= 1) ? 0 : 1 - gain[v]; // 孩子本来未必投放，牺牲可以减免
        int p = parent[v];
        off[p] += off[v] + slack;
        if (slack < gain[p]) {
            gain[p] = slack;
        }
        indeg[p]--;
        if (indeg[p] == 0) {
            stk.push_back(p);
        }
    }
}

// 一个环最多能投放多少个；ring 按「孩子在前、父亲在后」排列
ll ring_best(const vector<int>& ring) {
    int head = ring[0];
    ll on_tree = (gain[head] < NO_CHILD) ? (ll)off[head] + 1 - gain[head] : NEG;
    if ((int)ring.size() == 1) { // 自环：唯一的环上候选是自己，不能当见证
        return off[head] > on_tree ? off[head] : on_tree;
    }
    ll best = NEG;
    for (int tail_off = 1; tail_off >= 0; tail_off--) {
        ll dp0 = off[head];
        ll dp1 = tail_off ? (ll)off[head] + 1 : on_tree;
        for (int t = 1; t < (int)ring.size(); t++) {
            int v = ring[t];
            ll free_choice = dp0 > dp1 ? dp0 : dp1; // 环上前驱不投放，v 才可以投放
            ll by_tree = (gain[v] < NO_CHILD) ? dp1 - gain[v] : NEG;
            ll best_pred = dp0 > by_tree ? dp0 : by_tree;
            dp1 = (ll)off[v] + 1 + best_pred;
            dp0 = free_choice + off[v]; // v 不投放，挂树各自取最优
        }
        ll cur = tail_off ? dp0 : dp1; // 环尾不投放取 dp0，投放取 dp1
        if (cur > best) {
            best = cur;
        }
    }
    return best;
}

int main() {
    if (scanf("%d", &n) != 1) {
        return 0;
    }
    parent.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &parent[i]);
    }
    peel_trees();

    ll total = 0;
    for (int s = 1; s <= n; s++) {
        if (indeg[s] == 0) {
            continue; // 已被剥掉，贡献早已算进它所属的环
        }
        vector<int> ring;
        int u = s;
        while (indeg[u] > 0) { // 顺着 parent 走，孩子总在父亲前面
            ring.push_back(u);
            indeg[u] = 0; // 打标记，免得同一个环被走第二遍
            u = parent[u];
        }
        total += ring_best(ring);
    }
    printf("%lld\n", total);
    return 0;
}
