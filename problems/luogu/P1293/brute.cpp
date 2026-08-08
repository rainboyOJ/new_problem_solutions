#include <bits/stdc++.h>
using namespace std;

struct City {
    long long cnt;
    long long pos;
    string name;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<City> a;
    City c;
    while (cin >> c.cnt >> c.pos >> c.name) {
        a.push_back(c);
    }

    long long best_cost = (1LL << 62);
    string best_name;
    long long best_pos = 0;

    for (auto &center : a) {
        long long cost = 0;
        for (auto &it : a) {
            cost += it.cnt * llabs(it.pos - center.pos);
        }
        if (cost < best_cost || (cost == best_cost && center.pos < best_pos)) {
            best_cost = cost;
            best_name = center.name;
            best_pos = center.pos;
        }
    }

    cout << best_name << ' ' << best_cost << '\n';
    return 0;
}
