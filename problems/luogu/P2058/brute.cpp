#include <bits/stdc++.h>
using namespace std;

const int maxn = 100000 + 5;

struct Ship {
    int time;
    vector<int> people;
};

int n;
vector<Ship> ships;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    ships.resize(n + 1);

    for (int i = 1; i <= n; i++) {
        int t, k;
        cin >> t >> k;
        ships[i].time = t;
        ships[i].people.resize(k);
        for (int j = 0; j < k; j++) {
            cin >> ships[i].people[j];
        }
    }

    for (int i = 1; i <= n; i++) {
        set<int> st;
        for (int j = 1; j <= i; j++) {
            if (ships[j].time <= ships[i].time - 86400) {
                continue;
            }
            for (int x : ships[j].people) {
                st.insert(x);
            }
        }
        cout << (int) st.size() << '\n';
    }

    return 0;
}
