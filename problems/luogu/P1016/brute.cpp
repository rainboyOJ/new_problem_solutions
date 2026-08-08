// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;
const long double EPS = 1e-10L;
const long double INF = 1e100L;

struct Station {
    long double dist;
    long double price;
};

struct StateKey {
    int idx;
    long long fuel_key;

    bool operator < (const StateKey &other) const {
        if (idx != other.idx) return idx < other.idx;
        return fuel_key < other.fuel_key;
    }
};

long double total_dist, tank_cap, dist_per_liter, start_price;
int station_cnt;
Station st[MAXN];
map<StateKey, long double> memo;

bool cmp_station(const Station &a, const Station &b) {
    return a.dist < b.dist;
}

long long encode_fuel(long double fuel) {
    if (fuel < 0 && fuel > -EPS) fuel = 0;
    return llround(fuel * 100000000.0L);
}

long double decode_fuel(long long key) {
    return (long double)key / 100000000.0L;
}

long double dfs(int idx, long long fuel_key) {
    if (idx == station_cnt) return 0;

    StateKey state = {idx, fuel_key};
    if (memo.count(state)) return memo[state];

    long double fuel = decode_fuel(fuel_key);
    long double best = INF;

    // 暴力枚举离开当前站时，油箱里可能保留的油量。
    // 有意义的选择包括：
    // 1. 不再买油，直接用当前油量；
    // 2. 加满；
    // 3. 加到刚好能到某个后续站点。
    vector<long double> candidates;
    candidates.push_back(fuel);
    candidates.push_back(tank_cap);
    for (int i = idx + 1; i <= station_cnt; i++) {
        long double need = (st[i].dist - st[idx].dist) / dist_per_liter;
        if (need - tank_cap <= EPS) {
            candidates.push_back(need);
        }
    }

    sort(candidates.begin(), candidates.end());
    candidates.erase(unique(candidates.begin(), candidates.end(), [](long double a, long double b) {
        return fabsl(a - b) <= EPS;
    }), candidates.end());

    for (long double leave_fuel : candidates) {
        if (leave_fuel + EPS < fuel) continue;
        if (leave_fuel - tank_cap > EPS) continue;

        long double buy_cost = (leave_fuel - fuel) * st[idx].price;

        for (int j = idx + 1; j <= station_cnt; j++) {
            long double need = (st[j].dist - st[idx].dist) / dist_per_liter;
            if (need - leave_fuel > EPS) continue;

            long double remain = leave_fuel - need;
            long double next_cost = dfs(j, encode_fuel(remain));
            if (next_cost >= INF / 2) continue;
            best = min(best, buy_cost + next_cost);
        }
    }

    memo[state] = best;
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> total_dist >> tank_cap >> dist_per_liter >> start_price >> station_cnt;

    st[0].dist = 0;
    st[0].price = start_price;
    for (int i = 1; i <= station_cnt; i++) {
        cin >> st[i].dist >> st[i].price;
    }

    st[station_cnt + 1].dist = total_dist;
    st[station_cnt + 1].price = 0;
    station_cnt++;

    sort(st, st + station_cnt + 1, cmp_station);

    long double ans = dfs(0, encode_fuel(0));
    if (ans >= INF / 2) {
        cout << "No Solution\n";
    } else {
        cout << fixed << setprecision(2) << (double)(ans + 1e-9L) << '\n';
    }

    return 0;
}
