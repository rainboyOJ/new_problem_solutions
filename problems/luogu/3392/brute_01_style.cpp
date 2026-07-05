// brute_01_style.cpp：选择序列风格暴力，按行依次决定属于白、蓝、红三段中的哪一段。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 55;

int n, m;
string s[MAXN];
int answer;
char color_name[3] = {'W', 'B', 'R'};

int row_cost(int row, int color_id) {
    int count_change = 0;
    for (int i = 0; i < m; i++) {
        if (s[row][i] != color_name[color_id]) {
            count_change++;
        }
    }
    return count_change;
}

void dfs_color(int row, int color_id, int cost, int used_w, int used_b, int used_r) {
    if (cost >= answer) {
        return;
    }
    if (row == n + 1) {
        if (color_id == 2 && used_w && used_b && used_r) {
            answer = cost;
        }
        return;
    }

    // 选择 0：当前行继续使用当前颜色段。
    int next_w = used_w + (color_id == 0);
    int next_b = used_b + (color_id == 1);
    int next_r = used_r + (color_id == 2);
    dfs_color(row + 1, color_id, cost + row_cost(row, color_id), next_w, next_b, next_r);

    // 选择 1：从当前行开始进入下一种颜色段。
    if (color_id < 2) {
        int next_color = color_id + 1;
        next_w = used_w + (next_color == 0);
        next_b = used_b + (next_color == 1);
        next_r = used_r + (next_color == 2);
        dfs_color(row + 1, next_color, cost + row_cost(row, next_color), next_w, next_b, next_r);
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
    dfs_color(1, 0, 0, 0, 0, 0);

    cout << answer << '\n';
    return 0;
}
