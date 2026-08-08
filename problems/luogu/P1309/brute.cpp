#include <bits/stdc++.h>
using namespace std;

struct Player {
    int id;
    int score;
    int power;
};

bool better(Player x, Player y) {
    if (x.score != y.score) {
        return x.score > y.score;
    }
    return x.id < y.id;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, r, q;
    cin >> n >> r >> q;

    vector<Player> a(2 * n + 1);
    for (int i = 1; i <= 2 * n; i++) {
        a[i].id = i;
        cin >> a[i].score;
    }
    for (int i = 1; i <= 2 * n; i++) {
        cin >> a[i].power;
    }

    sort(a.begin() + 1, a.end(), better);

    // brute.cpp：每轮都直接模拟比赛，再整体排序。
    while (r--) {
        for (int i = 1; i <= 2 * n; i += 2) {
            if (a[i].power > a[i + 1].power) {
                a[i].score++;
            }
            else {
                a[i + 1].score++;
            }
        }
        sort(a.begin() + 1, a.end(), better);
    }

    cout << a[q].id << '\n';
    return 0;
}
