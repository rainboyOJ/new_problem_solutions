#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100 + 5;
const int MAXK = 100 + 5;
const int MAXM = 10000 + 5;
const long long INF = (1LL << 60);

struct Edge {
    int to;
    int w;
};

struct MaskState {
    unsigned long long lo;
    unsigned long long hi;
};

struct PQNode {
    int u;
    unsigned long long lo;
    unsigned long long hi;
    long long dist;

    bool operator < (const PQNode &other) const {
        return dist > other.dist;
    }
};

struct SavedState {
    unsigned long long lo;
    unsigned long long hi;
    long long dist;
};

int n, k, m, s, t;
int culture[MAXN];
bool hate[MAXK][MAXK];
vector<Edge> g[MAXN];

// reject_mask[c] 的某一位为 1，表示“文化 c 排斥这个文化”。
MaskState reject_mask[MAXK];

vector<SavedState> best_states[MAXN];

MaskState set_bit(MaskState st, int c) {
    c--;
    if (c < 64) {
        st.lo |= 1ULL << c;
    }
    else {
        st.hi |= 1ULL << (c - 64);
    }
    return st;
}

bool has_bit(MaskState st, int c) {
    c--;
    if (c < 64) {
        return (st.lo >> c) & 1ULL;
    }
    return (st.hi >> (c - 64)) & 1ULL;
}

bool subset_of(MaskState a, MaskState b) {
    return (a.lo & ~b.lo) == 0ULL && (a.hi & ~b.hi) == 0ULL;
}

bool intersect(MaskState a, MaskState b) {
    return (a.lo & b.lo) != 0ULL || (a.hi & b.hi) != 0ULL;
}

bool is_current_state(int u, unsigned long long lo, unsigned long long hi, long long dist) {
    for (size_t i = 0; i < best_states[u].size(); i++) {
        SavedState st = best_states[u][i];
        if (st.lo == lo && st.hi == hi && st.dist == dist) {
            return true;
        }
    }
    return false;
}

// 支配剪枝：
// 如果在同一个点 u，已经有一个状态“学到的文化集合更少（子集），且代价不更大”，
// 那么当前状态一定没有必要保留。
bool insert_state(int u, unsigned long long lo, unsigned long long hi, long long dist) {
    MaskState cur = {lo, hi};

    for (size_t i = 0; i < best_states[u].size(); i++) {
        SavedState old = best_states[u][i];
        MaskState old_mask = {old.lo, old.hi};
        if (old.dist <= dist && subset_of(old_mask, cur)) {
            return false;
        }
    }

    vector<SavedState> keep;
    keep.reserve(best_states[u].size() + 1);
    for (size_t i = 0; i < best_states[u].size(); i++) {
        SavedState old = best_states[u][i];
        MaskState old_mask = {old.lo, old.hi};
        if (dist <= old.dist && subset_of(cur, old_mask)) {
            continue;
        }
        keep.push_back(old);
    }
    keep.push_back({lo, hi, dist});
    best_states[u].swap(keep);
    return true;
}

long long dijkstra_state_space() {
    for (int i = 1; i <= n; i++) {
        best_states[i].clear();
    }

    MaskState start_mask = {0ULL, 0ULL};
    start_mask = set_bit(start_mask, culture[s]);

    priority_queue<PQNode> pq;
    insert_state(s, start_mask.lo, start_mask.hi, 0);
    pq.push({s, start_mask.lo, start_mask.hi, 0});

    while (!pq.empty()) {
        PQNode cur = pq.top();
        pq.pop();

        if (!is_current_state(cur.u, cur.lo, cur.hi, cur.dist)) {
            continue;
        }

        if (cur.u == t) {
            return cur.dist;
        }

        MaskState learned = {cur.lo, cur.hi};

        for (size_t i = 0; i < g[cur.u].size(); i++) {
            int v = g[cur.u][i].to;
            int w = g[cur.u][i].w;
            int cv = culture[v];

            // 不能再次学习同一种文化。
            if (has_bit(learned, cv)) {
                continue;
            }
            // 目标国家的文化若排斥已经学到的任一文化，也不能进入。
            if (intersect(reject_mask[cv], learned)) {
                continue;
            }

            MaskState nxt_mask = set_bit(learned, cv);
            long long nd = cur.dist + w;

            if (insert_state(v, nxt_mask.lo, nxt_mask.hi, nd)) {
                pq.push({v, nxt_mask.lo, nxt_mask.hi, nd});
            }
        }
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k >> m >> s >> t;

    for (int i = 1; i <= n; i++) {
        cin >> culture[i];
        g[i].clear();
    }

    for (int i = 1; i <= k; i++) {
        reject_mask[i] = {0ULL, 0ULL};
    }

    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= k; j++) {
            cin >> hate[i][j];
            if (hate[i][j]) {
                reject_mask[i] = set_bit(reject_mask[i], j);
            }
        }
    }

    for (int i = 1; i <= m; i++) {
        int u, v, d;
        cin >> u >> v >> d;
        g[u].push_back({v, d});
        g[v].push_back({u, d});
    }

    cout << dijkstra_state_space() << '\n';

    return 0;
}
