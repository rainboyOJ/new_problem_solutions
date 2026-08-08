// brute_01_style.cpp：选择序列风格暴力，按行依次决定属于白、蓝、红三段中的哪一段。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 55;

int n, m;
string s[MAXN];
int answer;
char color_name[3] = {'W', 'B', 'R'};
int go_next[MAXN]; // go_next[i] = 0/1，表示第 i 行继续当前颜色段/进入下一段

int row_cost(int row, int color_id) {
    int count_change = 0;
    for (int i = 0; i < m; i++) {
        if (s[row][i] != color_name[color_id]) {
            count_change++;
        }
    }
    return count_change;
}

bool check() {
    int color_id = 0;
    int used[3] = {0, 0, 0};
    for (int row = 1; row <= n; row++) {
        if (go_next[row] == 1) color_id++;
        if (color_id > 2) return false;
        used[color_id] = 1;
    }
    return color_id == 2 && used[0] && used[1] && used[2];
}

int calc_answer() {
    int color_id = 0;
    int cost = 0;
    for (int row = 1; row <= n; row++) {
        if (go_next[row] == 1) color_id++;
        cost += row_cost(row, color_id);
    }
    return cost;
}

void dfs_color(int dep) {
    if (dep == n + 1) {
        if (check()) {
            int value = calc_answer();
            if (answer > value) answer = value;
        }
        return;
    }

    // 第 dep 行的 01 选择：0 继续当前颜色段，1 进入下一种颜色段。
    for (int i = 0; i <= 1; i++) {
        go_next[dep] = i;
        dfs_color(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
    }

    answer = 1000000000;
    dfs_color(1);

    cout << answer << '\n';
    return 0;
}
