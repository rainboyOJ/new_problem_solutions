#include <bits/stdc++.h>
using namespace std;

const int MAXP = 46340;

struct Operation {
    int type;
    int x;
    int y;
};

struct Frame {
    int u;
    int parent;
    int state;
};

static vector<int> primes;
static unordered_map<int, int> prime_id;
static vector<vector<int>> prime_stacks;

int get_prime_id(int p) {
    auto it = prime_id.find(p);
    if (it != prime_id.end()) {
        return it->second;
    }
    int id = (int)prime_stacks.size();
    prime_id[p] = id;
    prime_stacks.push_back(vector<int>());
    return id;
}

vector<int> factorize_ids(int x) {
    vector<int> ids;
    int value = x;
    for (int p : primes) {
        if (1LL * p * p > value) {
            break;
        }
        if (value % p == 0) {
            ids.push_back(get_prime_id(p));
            while (value % p == 0) {
                value /= p;
            }
        }
    }
    if (value > 1) {
        ids.push_back(get_prime_id(value));
    }
    return ids;
}

void build_primes() {
    vector<int> is_prime(MAXP + 1, 1);
    is_prime[0] = is_prime[1] = 0;
    for (int i = 2; i <= MAXP; ++i) {
        if (!is_prime[i]) {
            continue;
        }
        primes.push_back(i);
        if (1LL * i * i <= MAXP) {
            for (int j = i * i; j <= MAXP; j += i) {
                is_prime[j] = 0;
            }
        }
    }
}

void recompute_answers(const vector<vector<int>> &tree,
                       const vector<vector<int>> &factor_ids,
                       vector<int> &answer,
                       vector<int> &depth) {
    int n = (int)tree.size() - 1;
    vector<Frame> st;
    st.reserve(n * 2);
    st.push_back({1, 0, 0});
    depth[1] = 0;

    while (!st.empty()) {
        Frame cur = st.back();
        st.pop_back();

        int u = cur.u;
        int parent = cur.parent;

        if (cur.state == 0) {
            int best = -1;
            int best_depth = -1;

            // 枚举当前点的所有不同质因子，看看路径上最近的同类祖先是谁。
            for (int pid : factor_ids[u]) {
                if (!prime_stacks[pid].empty()) {
                    int candidate = prime_stacks[pid].back();
                    if (depth[candidate] > best_depth) {
                        best_depth = depth[candidate];
                        best = candidate;
                    }
                }
            }
            answer[u] = best;

            for (int pid : factor_ids[u]) {
                prime_stacks[pid].push_back(u);
            }

            st.push_back({u, parent, 1});
            for (int i = (int)tree[u].size() - 1; i >= 0; --i) {
                int v = tree[u][i];
                if (v == parent) {
                    continue;
                }
                depth[v] = depth[u] + 1;
                st.push_back({v, u, 0});
            }
        } else {
            for (int pid : factor_ids[u]) {
                prime_stacks[pid].pop_back();
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    build_primes();

    int n, q;
    cin >> n >> q;

    vector<int> value(n + 1);
    vector<vector<int>> factor_ids(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> value[i];
    }

    vector<vector<int>> tree(n + 1);
    for (int i = 1; i <= n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    for (int i = 1; i <= n; ++i) {
        factor_ids[i] = factorize_ids(value[i]);
    }

    vector<int> answer(n + 1, -1);
    vector<int> depth(n + 1, 0);
    recompute_answers(tree, factor_ids, answer, depth);

    for (int i = 1; i <= q; ++i) {
        int type;
        cin >> type;
        if (type == 1) {
            int x;
            cin >> x;
            cout << answer[x] << '\n';
        } else {
            int x, y;
            cin >> x >> y;
            value[x] = y;
            factor_ids[x] = factorize_ids(value[x]);
            recompute_answers(tree, factor_ids, answer, depth);
        }
    }
    return 0;
}
