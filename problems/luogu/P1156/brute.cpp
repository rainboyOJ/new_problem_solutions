#include <bits/stdc++.h>
using namespace std;

struct Item {
    int t;
    int f;
    int h;
};

static int D, G;
static vector<Item> a;
static int best_escape = INT_MAX;
static int best_survive = 0;

static void dfs(int idx, int height, int death_time) {
    if (height >= D) {
        best_escape = min(best_escape, a[idx - 1].t);
        return;
    }

    if (idx == G) {
        best_survive = max(best_survive, death_time);
        return;
    }

    const auto &it = a[idx];
    if (death_time < it.t) {
        best_survive = max(best_survive, death_time);
        return;
    }

    // 选择“吃”。
    dfs(idx + 1, height, death_time + it.f);

    // 选择“堆”。
    dfs(idx + 1, min(D, height + it.h), death_time);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> D >> G;
    a.resize(G);
    for (int i = 0; i < G; ++i) {
        cin >> a[i].t >> a[i].f >> a[i].h;
    }
    sort(a.begin(), a.end(), [](const Item &x, const Item &y) {
        return x.t < y.t;
    });

    dfs(0, 0, 10);
    if (best_escape != INT_MAX) {
        cout << best_escape << '\n';
    } else {
        cout << best_survive << '\n';
    }
    return 0;
}
