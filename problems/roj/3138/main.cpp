/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
// 方格取数（两条路同时走）：按反对角线同步转移，状态只需记两条路的行号。
#include <cstdio>
#include <vector>

typedef long long ll;

const ll NEG = -1000000000LL; // 不可达状态

ll M, N;
std::vector<std::vector<ll> > grid;
std::vector<std::vector<ll> > state, fresh;

// 由「走到第 step 条对角线」的状态推出「第 step+1 条对角线」的状态
void advance(ll step) {
    ll lo = step - N + 1;
    if (lo < 0) lo = 0;
    ll hi = step;
    if (hi > M - 1) hi = M - 1;
    if (lo > hi) return; // 本对角线上没有合法行号

    ll len = hi - lo + 1;
    std::vector<ll> values(len);
    for (ll r = lo; r <= hi; r++) {
        values[r - lo] = grid[r][step - r];
    }

    // 清空下一层
    for (ll i = 0; i <= M; i++) {
        for (ll j = 0; j <= M; j++) {
            fresh[i][j] = NEG;
        }
    }

    std::vector<ll> from_row(M + 2, NEG), incoming(M + 2, NEG), gain(len, 0);
    for (ll r = lo; r <= hi; r++) {
        ll i = r + 1;
        ll value = values[r - lo];
        // 来路只能是上一条对角线的第 r-1 行或第 r 行（纵向来路）；
        // 再和右邻错位取 max 补上横向来路
        for (ll q = 0; q <= M; q++) {
            ll a = state[i - 1][q], b = state[i][q];
            from_row[q] = a > b ? a : b;
        }
        for (ll q = 0; q <= M; q++) {
            ll a = from_row[q], b = (q + 1 <= M) ? from_row[q + 1] : NEG;
            incoming[q] = a > b ? a : b;
        }
        for (ll t = 0; t < len; t++) {
            gain[t] = value + values[t]; // 两条路分处两格：两格好感度都计入
        }
        gain[r - lo] = value; // 两条路同处一格：整格只计入一次
        for (ll q = lo; q <= hi; q++) {
            fresh[i][q + 1] = incoming[q] + gain[q - lo];
        }
    }

    state.swap(fresh);
}

int main() {
    ll m, n;
    if (scanf("%lld %lld", &m, &n) != 2) return 0; // 空输入安全返回
    grid.assign(m, std::vector<ll>(n, 0));
    for (ll i = 0; i < m; i++) {
        for (ll j = 0; j < n; j++) {
            scanf("%lld", &grid[i][j]);
        }
    }

    // 状态表按行号索引，规模是 m*m；转置不改变答案，所以让 m 取较小的一维
    if (m > n) {
        std::vector<std::vector<ll> > t(n, std::vector<ll>(m, 0));
        for (ll i = 0; i < m; i++) {
            for (ll j = 0; j < n; j++) {
                t[j][i] = grid[i][j];
            }
        }
        grid = t;
        ll tmp = m; m = n; n = tmp;
    }
    M = m;
    N = n;

    state.assign(M + 2, std::vector<ll>(M + 2, NEG));
    fresh.assign(M + 2, std::vector<ll>(M + 2, NEG));
    // 两条路都从 (1,1) 出发、(m,n) 结束，起点只计一份权重
    state[1][1] = grid[0][0];
    for (ll step = 1; step <= M + N - 2; step++) {
        advance(step);
    }
    printf("%lld\n", state[M][M]);
    return 0;
}
