#include <bits/stdc++.h>
using namespace std;

static int N;
static long long M;
static vector<int> K, C;
static int limit;
static vector<int> choose_count;
static vector<long long> best;

static long long clamp_mul(long long a, int b) {
    __int128 v = (__int128)a * b;
    if (v > M) {
        return M;
    }
    return (long long)v;
}

static int calc_cost() {
    int cost = 0;
    for (int i = 0; i < N; ++i) {
        cost += choose_count[i] * C[i];
    }
    return cost;
}

static long long calc_ways() {
    long long ways = 1;
    for (int i = 0; i < N; ++i) {
        if (choose_count[i] == 0) {
            continue;
        }
        ways = clamp_mul(ways, choose_count[i]);
    }
    return ways;
}

static bool check() {
    return calc_cost() <= limit;
}

static void dfs(int dep) {
    if (dep == N) {
        if (check()) {
            int cost = calc_cost();
            long long ways = calc_ways();
            best[cost] = max(best[cost], ways);
        }
        return;
    }

    // 第 dep 个英雄可以不买皮肤，或者买 2..K[dep] 款皮肤。
    choose_count[dep] = 0;
    dfs(dep + 1);

    for (int x = 2; x <= K[dep]; ++x) {
        choose_count[dep] = x;
        dfs(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    K.resize(N);
    C.resize(N);
    for (int i = 0; i < N; ++i) {
        cin >> K[i];
    }
    for (int i = 0; i < N; ++i) {
        cin >> C[i];
    }

    limit = 0;
    for (int i = 0; i < N; ++i) {
        limit += K[i] * C[i];
    }

    best.assign(limit + 1, 0);
    choose_count.assign(N, 0);
    dfs(0);

    for (int cost = 0; cost <= limit; ++cost) {
        if (best[cost] >= M) {
            cout << cost << '\n';
            return 0;
        }
    }

    return 0;
}
