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

    sort(a.begin(), a.end(), [](const City &lhs, const City &rhs) {
        if (lhs.pos != rhs.pos) return lhs.pos < rhs.pos;
        return lhs.name < rhs.name;
    });

    long long total = 0;
    for (auto &it : a) total += it.cnt;

    long long pref = 0;
    for (auto &it : a) {
        pref += it.cnt;
        if (pref * 2 >= total) {
            long long cost = 0;
            for (auto &jt : a) {
                cost += jt.cnt * llabs(jt.pos - it.pos);
            }
            cout << it.name << ' ' << cost << '\n';
            return 0;
        }
    }

    return 0;
}
