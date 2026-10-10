/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 305;

int n, p;
vector<int> adj[MAXN];
int parent_[MAXN];
vector<int> order;          // 层序
vector<int> children[MAXN];
int size_[MAXN];
bitset<MAXN> kids_mask[MAXN];   // 各点孩子的位图

// bits(mask)：依次产出位图 mask 中为 1 的节点下标
vector<int> bits_of(const bitset<MAXN>& mask) {
    vector<int> res;
    for (int i = 0; i < n; i++)
        if (mask[i]) res.push_back(i);
    return res;
}

// 记忆化（用字符串作为 key）
map<string, int> memo;

int saved(const bitset<MAXN>& frontier) {
    if (frontier.none()) return 0;
    string key = frontier.to_string();
    map<string, int>::iterator it = memo.find(key);
    if (it != memo.end()) return it->second;

    // 本层除被切断点外其余候选全部感染，下一层候选 = 这些点的孩子
    bitset<MAXN> nxt;
    for (int u = 0; u < n; u++)
        if (frontier[u]) nxt |= kids_mask[u];

    int best = 0;
    for (int u = 0; u < n; u++) {
        if (!frontier[u]) continue;
        bitset<MAXN> rest = nxt & ~kids_mask[u];
        int v = size_[u] + saved(rest);
        if (v > best) best = v;
    }
    memo[key] = best;
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> p;
    for (int i = 0; i < p; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 0; i < n; i++) parent_[i] = -1;
    order.push_back(0);
    for (size_t idx = 0; idx < order.size(); idx++) {
        int u = order[idx];
        for (size_t i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];
            if (v && parent_[v] < 0) {
                parent_[v] = u;
                order.push_back(v);
            }
        }
    }
    for (int v = 1; v < n; v++) children[parent_[v]].push_back(v);
    for (int u = 0; u < n; u++) size_[u] = 1;
    for (int i = (int)order.size() - 1; i >= 0; i--) {
        int u = order[i];
        for (size_t j = 0; j < children[u].size(); j++)
            size_[u] += size_[children[u][j]];
    }
    for (int u = 0; u < n; u++)
        for (size_t j = 0; j < children[u].size(); j++)
            kids_mask[u].set(children[u][j]);

    cout << n - saved(kids_mask[0]) << "\n";
    return 0;
}
