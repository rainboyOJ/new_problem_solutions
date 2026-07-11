/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 19:17
 * update_at: 2026-07-11 19:20
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 200005;

struct Operation {
    int from, to;
    ll val;
};

struct Action {
    int type; // 0 表示处理一个节点，1 表示输出一条操作
    int u, v;
    ll val;
};

int n;
ll h[MAXN], avg, sub[MAXN];
int parent_node[MAXN];
vector<int> g[MAXN];
vector<int> order;
vector<Operation> ans;

void build_parent() {
    vector<int> st;
    st.push_back(1);
    parent_node[1] = 0;

    while (!st.empty()) {
        int u = st.back();
        st.pop_back();
        order.push_back(u);

        for (int i = 0; i < (int)g[u].size(); i++) {
            int v = g[u][i];
            if (v == parent_node[u]) continue;
            parent_node[v] = u;
            st.push_back(v);
        }
    }
}

void calc_subtree_sum() {
    for (int i = 1; i <= n; i++) {
        sub[i] = h[i] - avg;
    }

    for (int i = (int)order.size() - 1; i >= 0; i--) {
        int u = order[i];
        if (parent_node[u] != 0) {
            sub[parent_node[u]] += sub[u];
        }
    }
}

void build_operations() {
    vector<Action> st;
    st.push_back((Action){0, 1, 0, 0});

    while (!st.empty()) {
        Action cur = st.back();
        st.pop_back();

        if (cur.type == 1) {
            ans.push_back((Operation){cur.u, cur.v, cur.val});
            continue;
        }

        int u = cur.u;

        // 负子树：先从父亲给子树，再处理子树。由于栈是后进先出，这里倒序压栈。
        for (int i = (int)g[u].size() - 1; i >= 0; i--) {
            int v = g[u][i];
            if (v == parent_node[u] || sub[v] >= 0) continue;
            st.push_back((Action){0, v, 0, 0});
            st.push_back((Action){1, u, v, -sub[v]});
        }

        // 正子树：先处理子树，再把多余草捆交给父亲。
        for (int i = (int)g[u].size() - 1; i >= 0; i--) {
            int v = g[u][i];
            if (v == parent_node[u] || sub[v] < 0) continue;
            if (sub[v] > 0) {
                st.push_back((Action){1, v, u, sub[v]});
            }
            st.push_back((Action){0, v, 0, 0});
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
        avg += h[i];
    }
    avg /= n;

    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    build_parent();
    calc_subtree_sum();
    build_operations();

    cout << ans.size() << '\n';
    for (int i = 0; i < (int)ans.size(); i++) {
        cout << ans[i].from << ' ' << ans[i].to << ' ' << ans[i].val << '\n';
    }

    return 0;
}
