// brute.cpp：小数据暴力解，按成绩排序后模拟蛇形分配座位。
#include <bits/stdc++.h>
using namespace std;

struct Student {
    int score;
    int id;
};

const int MAXN = 105;

int n, m;
Student stu[MAXN];

bool cmp(Student a, Student b) {
    return a.score > b.score;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    int total = n * m;
    for (int i = 1; i <= total; i++) {
        cin >> stu[i].score;
        stu[i].id = i;
    }

    sort(stu + 1, stu + total + 1, cmp);

    for (int rank = 0; rank < total; rank++) {
        if (stu[rank + 1].id != 1) {
            continue;
        }
        int col = rank / n + 1;
        int offset = rank % n;
        int row;
        if (col % 2 == 1) {
            row = offset + 1;
        } else {
            row = n - offset;
        }
        cout << col << ' ' << row << '\n';
        return 0;
    }

    return 0;
}
