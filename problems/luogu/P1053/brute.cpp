#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据暴力解。
// 直接枚举所有最终环形座次，检查是否满足每个人的愿望，
// 再统计这一排座次相对初始状态有多少人离开了原位。

const int MAXN = 15;

int n;
int want1[MAXN], want2[MAXN];

// 判断学生 u 在当前环里左右两边的人，是否正好是他想要的两个人。
bool check_one_student(int u, int left_student, int right_student) {
    if (left_student == want1[u] && right_student == want2[u]) {
        return true;
    }
    if (left_student == want2[u] && right_student == want1[u]) {
        return true;
    }
    return false;
}

// 检查整圈人是否满足所有愿望。
bool check_circle(const vector<int> &perm) {
    for (int i = 0; i < n; i++) {
        int u = perm[i];
        int left_student = perm[(i - 1 + n) % n];
        int right_student = perm[(i + 1) % n];
        if (!check_one_student(u, left_student, right_student)) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> want1[i] >> want2[i];
    }

    vector<int> perm;
    for (int i = 1; i <= n; i++) {
        perm.push_back(i);
    }

    int ans = -1;

    do {
        if (!check_circle(perm)) {
            continue;
        }

        int moved = 0;
        for (int i = 0; i < n; i++) {
            if (perm[i] != i + 1) {
                moved++;
            }
        }

        if (ans == -1 || moved < ans) {
            ans = moved;
        }
    } while (next_permutation(perm.begin(), perm.end()));

    cout << ans << '\n';

    return 0;
}
