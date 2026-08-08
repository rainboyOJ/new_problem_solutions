#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;

struct HashValue {
    ull a;
    ull b;
};

struct Frame {
    int u;
    int state;
};

static const ull NULL_A = 1469598103934665603ULL;
static const ull NULL_B = 1099511628211ULL;

ull splitmix64(ull x) {
    x += 0x9e3779b97f4a7c15ULL;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
    return x ^ (x >> 31);
}

HashValue combine_hash(int value, const HashValue &left_hash,
                       const HashValue &right_hash) {
    ull x = splitmix64((ull)(value + 1007) ^
                       (left_hash.a * 0x9e3779b97f4a7c15ULL) ^
                       (right_hash.a * 0xc2b2ae3d27d4eb4fULL));
    ull y = splitmix64((ull)(value + 2003) ^
                       (left_hash.b * 0x94d049bb133111ebULL) ^
                       (right_hash.b * 0xbf58476d1ce4e5b9ULL));
    return {x, y};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> value(n + 1);
    vector<int> left_son(n + 1), right_son(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> value[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> left_son[i] >> right_son[i];
    }

    vector<int> subtree_size(n + 1, 0);
    vector<HashValue> normal_hash(n + 1, {0, 0});
    vector<HashValue> mirror_hash(n + 1, {0, 0});
    vector<int> order;
    order.reserve(n);

    vector<Frame> st;
    st.reserve(n * 2);
    st.push_back({1, 0});

    while (!st.empty()) {
        Frame cur = st.back();
        st.pop_back();

        int u = cur.u;
        if (u == -1) {
            continue;
        }

        if (cur.state == 0) {
            st.push_back({u, 1});
            st.push_back({right_son[u], 0});
            st.push_back({left_son[u], 0});
        } else {
            order.push_back(u);
        }
    }

    int ans = 1;
    for (int u : order) {
        HashValue left_norm = (left_son[u] == -1 ? HashValue{NULL_A, NULL_B}
                                                 : normal_hash[left_son[u]]);
        HashValue right_norm = (right_son[u] == -1 ? HashValue{NULL_A, NULL_B}
                                                   : normal_hash[right_son[u]]);
        HashValue left_mirror =
            (left_son[u] == -1 ? HashValue{NULL_A, NULL_B}
                               : mirror_hash[left_son[u]]);
        HashValue right_mirror =
            (right_son[u] == -1 ? HashValue{NULL_A, NULL_B}
                                : mirror_hash[right_son[u]]);

        int left_size = (left_son[u] == -1 ? 0 : subtree_size[left_son[u]]);
        int right_size = (right_son[u] == -1 ? 0 : subtree_size[right_son[u]]);
        subtree_size[u] = left_size + right_size + 1;

        normal_hash[u] = combine_hash(value[u], left_norm, right_norm);
        mirror_hash[u] = combine_hash(value[u], right_mirror, left_mirror);

        if (normal_hash[u].a == mirror_hash[u].a &&
            normal_hash[u].b == mirror_hash[u].b) {
            ans = max(ans, subtree_size[u]);
        }
    }

    cout << ans << '\n';
    return 0;
}
