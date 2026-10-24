/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 23:04
 * update_at: 2026-10-23 23:30
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 55;
const int MAX_STATES = 255;
const ll INF = 0x3f3f3f3f3f3f3f3fLL;

int n, m, k;
ll T;
ll c[MAXN];
int tot_states; // N = 5 * n

// 拆点编号映射：u in [1, n], j in [0, 4]
// j 表示距离到达城市 u 还要经过 j 天
inline int get_id(int u, int j) {
    return j * n + u;
}

// (max, +) 矩阵
struct Matrix {
    ll mat[MAX_STATES][MAX_STATES];

    Matrix() {
        for (int i = 1; i <= tot_states; ++i) {
            for (int j = 1; j <= tot_states; ++j) {
                mat[i][j] = -INF;
            }
        }
    }
};

// 矩阵乘法 C = A * B 在 (max, +) 半环下
Matrix multiply(const Matrix &A, const Matrix &B) {
    Matrix C;
    for (int i = 1; i <= tot_states; ++i) {
        for (int mid = 1; mid <= tot_states; ++mid) {
            if (A.mat[i][mid] < 0) continue;
            for (int j = 1; j <= tot_states; ++j) {
                if (B.mat[mid][j] < 0) continue;
                ll val = A.mat[i][mid] + B.mat[mid][j];
                if (val > C.mat[i][j]) {
                    C.mat[i][j] = val;
                }
            }
        }
    }
    return C;
}

// 行向量乘矩阵：vec = vec * A 在 (max, +) 半环下
void vec_multiply(vector<ll> &vec, const Matrix &A) {
    vector<ll> res(tot_states + 1, -INF);
    for (int mid = 1; mid <= tot_states; ++mid) {
        if (vec[mid] < 0) continue;
        for (int j = 1; j <= tot_states; ++j) {
            if (A.mat[mid][j] < 0) continue;
            ll val = vec[mid] + A.mat[mid][j];
            if (val > res[j]) {
                res[j] = val;
            }
        }
    }
    vec = std::move(res);
}

// 预处理矩阵倍增幂：pow_mat[p] = M^(2^p)
Matrix pow_mat[32];

struct Festival {
    ll t;
    int x;
    ll y;
} fest[205];

bool cmp_fest(const Festival &a, const Festival &b) {
    return a.t < b.t;
}

void solve() {
    tot_states = 5 * n;

    // 构建基础一步转移矩阵 M
    Matrix M;
    // 1. 虚点内部连边：距离到达 u 还剩 j 天，走 1 天变为还剩 j-1 天
    for (int u = 1; u <= n; ++u) {
        for (int j = 1; j <= 4; ++j) {
            M.mat[get_id(u, j)][get_id(u, j - 1)] = 0;
        }
    }
    // 2. 原图中的有向边 (u, v, w)：从到达 u 的瞬间出发，耗时 w 天到达 v
    // 相当于下一步处于状态 (v, w - 1)，到达 v 时可获得 c[v] 愉悦值
    for (int i = 1; i <= m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        int from_id = get_id(u, 0);
        int to_id = get_id(v, w - 1);
        if (c[v] > M.mat[from_id][to_id]) {
            M.mat[from_id][to_id] = c[v];
        }
    }

    for (int i = 1; i <= k; ++i) {
        cin >> fest[i].t >> fest[i].x >> fest[i].y;
    }
    sort(fest + 1, fest + k + 1, cmp_fest);

    // 预处理倍增矩阵幂
    pow_mat[0] = M;
    for (int p = 1; p <= 30; ++p) {
        pow_mat[p] = multiply(pow_mat[p - 1], pow_mat[p - 1]);
    }

    // 初始状态向量：第 0 天位于城市 1（get_id(1, 0)），获得愉悦值 c[1]
    vector<ll> F(tot_states + 1, -INF);
    F[get_id(1, 0)] = c[1];

    ll cur_t = 0;
    for (int i = 1; i <= k; ++i) {
        ll dt = fest[i].t - cur_t;
        if (dt > 0) {
            for (int p = 0; p <= 30; ++p) {
                if ((dt >> p) & 1) {
                    vec_multiply(F, pow_mat[p]);
                }
            }
            cur_t = fest[i].t;
        }
        int target_id = get_id(fest[i].x, 0);
        if (F[target_id] >= 0) {
            F[target_id] += fest[i].y;
        }
    }

    // 跨越最后一段无美食节的时间直到 T
    if (T > cur_t) {
        ll dt = T - cur_t;
        for (int p = 0; p <= 30; ++p) {
            if ((dt >> p) & 1) {
                vec_multiply(F, pow_mat[p]);
            }
        }
    }

    ll ans = F[get_id(1, 0)];
    if (ans < 0) {
        cout << -1 << "\n";
    } else {
        cout << ans << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> n >> m >> T >> k) {
        for (int i = 1; i <= n; ++i) {
            cin >> c[i];
        }
        solve();
    }

    return 0;
}
