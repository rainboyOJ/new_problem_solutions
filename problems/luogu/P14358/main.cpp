#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n, m;
int a[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    int total = n * m;
    for (int i = 1; i <= total; i++) {
        cin >> a[i];
    }

    int better_count = 0; // 成绩比小 R 高的人数，也就是小 R 的 0-based 排名
    for (int i = 2; i <= total; i++) {
        if (a[i] > a[1]) {
            better_count++;
        }
    }

    int col = better_count / n + 1;
    int offset = better_count % n;
    int row;
    if (col % 2 == 1) {
        row = offset + 1;
    } else {
        row = n - offset;
    }

    cout << col << ' ' << row << '\n';
    return 0;
}
