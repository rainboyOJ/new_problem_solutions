/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:39
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505;
const __int128 INF = ((__int128)1 << 120);

// 一个停靠点信息：所属线路、站点编号、本周期内的到达偏移
struct Stop {
    int line, station;
    long long offset;
};

// 一条环线：运行周期和它停靠的所有站点
struct Line {
    long long period;
    vector<Stop> stop;
};

// 最短路状态：登上某条线路的时刻
struct RouteState {
    __int128 time;
    int line;
    bool operator<(const RouteState &other) const {
        return time > other.time;
    }
};

int n, m;
Line route[MAXN];
vector<Stop> at_station[MAXN];   // 每个站点有哪些线路经过
long long gcd_value[MAXN][MAXN], lcm_value[MAXN][MAXN], inverse_value[MAXN][MAXN];
__int128 dist[MAXN];             // dist[i] 为最早登上线路 i 的时刻

// 扩展欧几里得：解 a*x + b*y = gcd(a,b)
long long extended_gcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long g = extended_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - a / b * y1;
    return g;
}

// 求 a 在模 mod 下的乘法逆元
long long get_inverse(long long a, long long mod) {
    if (mod == 1) return 0;
    long long x, y;
    extended_gcd(a, mod, x, y);
    x %= mod;
    if (x < 0) x += mod;
    return x;
}

// 线路在偏移 offset 的站点，从时刻 now 之后的下一次到站时刻
__int128 next_arrival(__int128 now, long long offset, long long period) {
    __int128 remainder = now % period;
    if (remainder <= offset) return now + offset - remainder;
    return now + period + offset - remainder;
}

// 线路 first 偏移 first_offset 与线路 second 偏移 second_offset 从时刻 now 起的最早会面时刻
__int128 next_meeting(int first, long long first_offset, int second, long long second_offset, __int128 now) {
    // 解同余组：x ≡ first_offset (mod P_first)，x ≡ second_offset (mod P_second)
    long long g = gcd_value[first][second];
    long long difference = second_offset - first_offset;
    if (difference % g != 0) return INF;   // 无解，两条线在该站永远碰不上
    long long mod = route[second].period / g;
    long long k = 0;
    if (mod != 1) {
        long long value = difference / g;
        value %= mod;
        if (value < 0) value += mod;
        k = (long long)((__int128)value * inverse_value[first][second] % mod);
    }
    __int128 base = first_offset + (__int128)route[first].period * k;
    long long period = lcm_value[first][second];
    // 调整到不小于 now 的时刻
    if (base < now) base += (now - base + period - 1) / period * period;
    return base;
}

// 输出 __int128 时间
void print_time(__int128 value) {
    if (value == INF) {
        cout << "inf\n";
        return;
    }
    string text;
    do {
        text.push_back('0' + value % 10);
        value /= 10;
    } while (value);
    reverse(text.begin(), text.end());
    cout << text << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int length;
        cin >> length;
        vector<int> station(length);
        vector<long long> travel(length);
        for (int j = 0; j < length; j++) cin >> station[j] >> travel[j];
        long long offset = 0;
        for (int j = 0; j < length; j++) {
            route[i].stop.push_back({i, station[j], offset});
            at_station[station[j]].push_back({i, station[j], offset});
            offset += travel[j];
        }
        route[i].period = offset;   // 周期 = 各段行驶时间之和
    }
    // 预处理任意两条线路的 gcd、lcm 与逆元，供换乘同余求解使用
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            long long g = gcd(route[i].period, route[j].period);
            gcd_value[i][j] = g;
            lcm_value[i][j] = route[i].period / g * route[j].period;
            inverse_value[i][j] = get_inverse(route[i].period / g, route[j].period / g);
        }
    }

    // 初始：在 1 号冷库站等待任意经过它的线路
    priority_queue<RouteState> q;
    for (int i = 1; i <= m; i++) dist[i] = INF;
    for (int i = 0; i < (int)at_station[1].size(); i++) {
        Stop start = at_station[1][i];
        if (start.offset < dist[start.line]) {
            dist[start.line] = start.offset;
            q.push({start.offset, start.line});
        }
    }
    // 在"线路"状态图上跑 Dijkstra
    while (!q.empty()) {
        RouteState current = q.top();
        q.pop();
        if (current.time != dist[current.line]) continue;   // 已过期的状态
        for (int i = 0; i < (int)route[current.line].stop.size(); i++) {
            Stop here = route[current.line].stop[i];
            // 在共同站点枚举所有可能换乘的线路
            for (int j = 0; j < (int)at_station[here.station].size(); j++) {
                Stop target = at_station[here.station][j];
                if (target.line == current.line) continue;
                __int128 meeting = next_meeting(current.line, here.offset, target.line, target.offset, current.time);
                if (meeting < dist[target.line]) {
                    dist[target.line] = meeting;
                    q.push({meeting, target.line});
                }
            }
        }
    }

    // 对每个站点，取所有经过它的可达线路的下一次到站时刻
    for (int station = 2; station <= n; station++) {
        __int128 answer = INF;
        for (int i = 0; i < (int)at_station[station].size(); i++) {
            Stop target = at_station[station][i];
            if (dist[target.line] == INF) continue;
            answer = min(answer, next_arrival(dist[target.line], target.offset, route[target.line].period));
        }
        print_time(answer);
    }

    return 0;
}