/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 矩形三个顶点补出第四个顶点：直角顶点为 c，另两点 a、b，第四顶点 = a + b - c
pair<int, int> rect_fourth(pair<int, int> a, pair<int, int> b, pair<int, int> c) {
    // c 是直角顶点
    return make_pair(a.first + b.first - c.first, a.second + b.second - c.second);
}

// 已知三点求第四个顶点
pair<int, int> rect_fourth_from_three(pair<int, int> p1, pair<int, int> p2, pair<int, int> p3) {
    pair<int, int> pts[3] = {p1, p2, p3};
    for (int i = 0; i < 3; i++) {
        pair<int, int> c = pts[i];
        pair<int, int> a = pts[(i + 1) % 3];
        pair<int, int> b = pts[(i + 2) % 3];
        ll dot = (ll)(a.first - c.first) * (b.first - c.first)
               + (ll)(a.second - c.second) * (b.second - c.second);
        if (dot == 0) return rect_fourth(a, b, c);
    }
    return make_pair(0, 0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int cases;
    cin >> cases;
    cout << fixed << setprecision(1);
    while (cases--) {
        int city_count, fly_price;
        cin >> city_count >> fly_price;
        int start, end;
        cin >> start >> end;

        int total = city_count * 4;
        vector<pair<int, int> > airports(total);
        vector<int> rail(city_count);

        for (int c = 0; c < city_count; c++) {
            pair<int, int> p1, p2, p3;
            cin >> p1.first >> p1.second;
            cin >> p2.first >> p2.second;
            cin >> p3.first >> p3.second;
            cin >> rail[c];
            int base = c * 4;
            airports[base + 0] = p1;
            airports[base + 1] = p2;
            airports[base + 2] = p3;
            airports[base + 3] = rect_fourth_from_three(p1, p2, p3);
        }

        // 建图
        vector<vector<pair<int, double> > > adj(total);
        for (int c = 0; c < city_count; c++) {
            int base = c * 4;
            for (int i = 0; i < 4; i++) {
                for (int j = i + 1; j < 4; j++) {
                    double dx = airports[base + i].first - airports[base + j].first;
                    double dy = airports[base + i].second - airports[base + j].second;
                    double w = sqrt(dx * dx + dy * dy) * rail[c];
                    adj[base + i].push_back(make_pair(base + j, w));
                    adj[base + j].push_back(make_pair(base + i, w));
                }
            }
        }
        for (int c = 0; c < city_count; c++) {
            int base = c * 4;
            for (int c2 = c + 1; c2 < city_count; c2++) {
                int base2 = c2 * 4;
                for (int i = 0; i < 4; i++) {
                    for (int j = 0; j < 4; j++) {
                        double dx = airports[base + i].first - airports[base2 + j].first;
                        double dy = airports[base + i].second - airports[base2 + j].second;
                        double w = sqrt(dx * dx + dy * dy) * fly_price;
                        adj[base + i].push_back(make_pair(base2 + j, w));
                        adj[base2 + j].push_back(make_pair(base + i, w));
                    }
                }
            }
        }

        // 多源 Dijkstra：4 个起点并入，任一终点到达即停
        int base_a = (start - 1) * 4;
        int base_b = (end - 1) * 4;
        vector<double> dist(total, 1e18);
        priority_queue<pair<double, int>, vector<pair<double, int> >, greater<pair<double, int> > > pq;
        for (int i = 0; i < 4; i++) {
            dist[base_a + i] = 0.0;
            pq.push(make_pair(0.0, base_a + i));
        }
        double ans = 1e18;
        while (!pq.empty()) {
            double cost = pq.top().first;
            int u = pq.top().second;
            pq.pop();
            if (cost > dist[u]) continue;
            if (u >= base_b && u < base_b + 4) { ans = cost; break; }
            for (size_t i = 0; i < adj[u].size(); i++) {
                int v = adj[u][i].first;
                double w = adj[u][i].second;
                if (cost + w < dist[v]) {
                    dist[v] = cost + w;
                    pq.push(make_pair(cost + w, v));
                }
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
