#include <bits/stdc++.h>
using namespace std;

const int MAXN = 52;
const int INF = 1e9;

int p;
int dist_arr[MAXN][MAXN];

int char_to_id(char ch) {
    if ('a' <= ch && ch <= 'z') {
        return ch - 'a';
    }
    return ch - 'A' + 26;
}

char id_to_char(int id) {
    if (id < 26) {
        return char('a' + id);
    }
    return char('A' + (id - 26));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> p;

    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < MAXN; j++) {
            if (i == j) {
                dist_arr[i][j] = 0;
            }
            else {
                dist_arr[i][j] = INF;
            }
        }
    }

    for (int i = 1; i <= p; i++) {
        char a, b;
        int w;
        cin >> a >> b >> w;

        int u = char_to_id(a);
        int v = char_to_id(b);

        if (w < dist_arr[u][v]) {
            dist_arr[u][v] = w;
            dist_arr[v][u] = w;
        }
    }

    // 点数只有 52，直接 Floyd 求任意两点最短路最省事。
    for (int k = 0; k < MAXN; k++) {
        for (int i = 0; i < MAXN; i++) {
            for (int j = 0; j < MAXN; j++) {
                if (dist_arr[i][k] + dist_arr[k][j] < dist_arr[i][j]) {
                    dist_arr[i][j] = dist_arr[i][k] + dist_arr[k][j];
                }
            }
        }
    }

    int z_id = char_to_id('Z');
    int answer_id = -1;
    int answer_dist = INF;

    // 只有 A..Y 上有牛，Z 是谷仓，不参与比较。
    for (int i = char_to_id('A'); i < z_id; i++) {
        if (dist_arr[i][z_id] < answer_dist) {
            answer_dist = dist_arr[i][z_id];
            answer_id = i;
        }
    }

    cout << id_to_char(answer_id) << ' ' << answer_dist << '\n';

    return 0;
}
