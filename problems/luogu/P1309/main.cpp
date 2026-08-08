#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

struct Player {
    int id;
    int score;
    int power;
};

int n, r, q;
Player a[MAXN];
Player win_group[MAXN];
Player lose_group[MAXN];
Player merged[MAXN];

bool better(Player x, Player y) {
    if (x.score != y.score) {
        return x.score > y.score;
    }
    return x.id < y.id;
}

void merge_groups() {
    int i = 1;
    int j = 1;
    int k = 1;

    while (i <= n && j <= n) {
        if (better(win_group[i], lose_group[j])) {
            merged[k++] = win_group[i++];
        }
        else {
            merged[k++] = lose_group[j++];
        }
    }

    while (i <= n) {
        merged[k++] = win_group[i++];
    }
    while (j <= n) {
        merged[k++] = lose_group[j++];
    }

    for (int t = 1; t <= 2 * n; t++) {
        a[t] = merged[t];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> r >> q;
    for (int i = 1; i <= 2 * n; i++) {
        a[i].id = i;
        cin >> a[i].score;
    }
    for (int i = 1; i <= 2 * n; i++) {
        cin >> a[i].power;
    }

    sort(a + 1, a + 2 * n + 1, better);

    while (r--) {
        int win_cnt = 0;
        int lose_cnt = 0;

        for (int i = 1; i <= 2 * n; i += 2) {
            Player x = a[i];
            Player y = a[i + 1];

            if (x.power > y.power) {
                x.score++;
                win_group[++win_cnt] = x;
                lose_group[++lose_cnt] = y;
            }
            else {
                y.score++;
                win_group[++win_cnt] = y;
                lose_group[++lose_cnt] = x;
            }
        }

        merge_groups();
    }

    cout << a[q].id << '\n';
    return 0;
}
