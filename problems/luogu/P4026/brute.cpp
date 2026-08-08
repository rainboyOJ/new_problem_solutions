#include <bits/stdc++.h>
using namespace std;

const int INF_NEG = -1000000000;

struct Bill {
    int value;
    int owner;
};

int x1, x2, x3;
int cnt[3][6];
int deno[6] = {100, 50, 20, 10, 5, 1};
vector<Bill> bills;
int target_a, target_b, target_c;
int total_bills;
int answer_stay;

void dfs(int idx, int a, int b, int c, int stay) {
    if (idx == (int) bills.size()) {
        if (a == target_a && b == target_b && c == target_c) {
            answer_stay = max(answer_stay, stay);
        }
        return;
    }

    int v = bills[idx].value;
    int owner = bills[idx].owner;

    if (a + v <= target_a) {
        dfs(idx + 1, a + v, b, c, stay + (owner == 0));
    }
    if (b + v <= target_b) {
        dfs(idx + 1, a, b + v, c, stay + (owner == 1));
    }
    if (c + v <= target_c) {
        dfs(idx + 1, a, b, c + v, stay + (owner == 2));
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
    // 把每张钞票看成独立物品，枚举它最终留给 Alice / Bob / Cynthia 的哪一个人。
    cin >> x1 >> x2 >> x3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 6; j++) {
            cin >> cnt[i][j];
        }
    }

    int init_money[3] = {0, 0, 0};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 6; j++) {
            init_money[i] += cnt[i][j] * deno[j];
            total_bills += cnt[i][j];
            for (int t = 0; t < cnt[i][j]; t++) {
                bills.push_back({deno[j], i});
            }
        }
    }

    target_a = init_money[0] - x1 + x3;
    target_b = init_money[1] + x1 - x2;
    target_c = init_money[2] + x2 - x3;

    if (target_a < 0 || target_b < 0 || target_c < 0) {
        cout << "impossible\n";
        return 0;
    }

    answer_stay = INF_NEG;
    dfs(0, 0, 0, 0, 0);

    if (answer_stay == INF_NEG) {
        cout << "impossible\n";
    } else {
        cout << total_bills - answer_stay << '\n';
    }

    return 0;
}
