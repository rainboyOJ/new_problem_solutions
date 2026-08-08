// brute.cpp：直接按队列顺序模拟，只适合小数据理解和对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 30005;

int q;
int belong[MAXN];
vector<int> ships[MAXN];

void init_queues() {
    for (int i = 1; i <= 30000; i++) {
        ships[i].clear();
        ships[i].push_back(i);
        belong[i] = i;
    }
}

void merge_queue(int x, int y) {
    int bx = belong[x];
    int by = belong[y];

    if (bx == by) {
        return;
    }

    for (int ship : ships[bx]) {
        ships[by].push_back(ship);
        belong[ship] = by;
    }
    ships[bx].clear();
}

int query_between(int x, int y) {
    int bx = belong[x];
    int by = belong[y];

    if (bx != by) {
        return -1;
    }
    if (x == y) {
        return 0;
    }

    int px = -1;
    int py = -1;
    for (int i = 0; i < (int)ships[bx].size(); i++) {
        if (ships[bx][i] == x) {
            px = i;
        }
        if (ships[bx][i] == y) {
            py = i;
        }
    }

    if (px > py) {
        swap(px, py);
    }
    return py - px - 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> q;
    init_queues();

    while (q--) {
        char op;
        int x, y;
        cin >> op >> x >> y;

        if (op == 'M') {
            merge_queue(x, y);
        } else {
            cout << query_between(x, y) << '\n';
        }
    }

    return 0;
}
