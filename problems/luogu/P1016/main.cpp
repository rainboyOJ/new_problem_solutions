#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;
const long double EPS = 1e-12L;

struct Station {
    long double dist;   // 这个加油点距离起点的距离
    long double price;  // 这个加油点的油价
};

long double total_dist, tank_cap, dist_per_liter, start_price;
int station_cnt;
Station st[MAXN];

bool cmp_station(const Station &a, const Station &b) {
    return a.dist < b.dist;
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

    // 把终点看成一个“价格为 0 的特殊站点”，这样逻辑会统一很多。
    st[station_cnt + 1].dist = total_dist;
    st[station_cnt + 1].price = 0;
    station_cnt++;

    sort(st, st + station_cnt + 1, cmp_station);

    long double max_reach = tank_cap * dist_per_liter; // 满油最多能跑多远
    long double fuel = 0;   // 当前油箱里的油量（升）
    long double answer = 0; // 总花费

    // 找到排序后真正的起点位置。
    int cur = -1;
    for (int i = 0; i <= station_cnt; i++) {
        if (fabsl(st[i].dist) <= EPS && fabsl(st[i].price - start_price) <= EPS) {
            cur = i;
            break;
        }
    }

    while (cur < station_cnt) {
        int first_cheaper = -1;
        int best_station = -1;

        // 在满油可达范围内：
        // 1. 找第一个比当前更便宜的站；
        // 2. 如果找不到，记下范围内油价最低的站。
        for (int i = cur + 1; i <= station_cnt; i++) {
            long double delta = st[i].dist - st[cur].dist;
            if (delta - max_reach > EPS) break;

            if (st[i].price + EPS < st[cur].price) {
                first_cheaper = i;
                break;
            }

            if (best_station == -1 || st[i].price + EPS < st[best_station].price) {
                best_station = i;
            }
        }

        // 连一个可达站都没有，说明无解。
        if (first_cheaper == -1 && best_station == -1) {
            cout << "No Solution\n";
            return 0;
        }

        if (first_cheaper != -1) {
            // 前面有更便宜的站，只买“恰好够到它”的油。
            long double need = (st[first_cheaper].dist - st[cur].dist) / dist_per_liter;
            if (fuel + EPS < need) {
                answer += (need - fuel) * st[cur].price;
                fuel = need;
            }
            fuel -= need;
            cur = first_cheaper;
        } else {
            // 前面没有更便宜的站，当前站就是这段范围里最便宜的，
            // 所以把油箱加满，然后开到范围内油价最低的那个站。
            if (fuel + EPS < tank_cap) {
                answer += (tank_cap - fuel) * st[cur].price;
                fuel = tank_cap;
            }

            long double need = (st[best_station].dist - st[cur].dist) / dist_per_liter;
            fuel -= need;
            cur = best_station;
        }
    }

    cout << fixed << setprecision(2) << (double)(answer + 1e-9L) << '\n';
    return 0;
}
