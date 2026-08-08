#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5000000 + 5;
int diffv[MAXN + 2];

int readInt() {
    int x = 0;
    int f = 1;
    int ch = getchar();
    while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
    if (ch == '-') {
        f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

int main() {
    int n = readInt();
    int p = readInt();

    for (int i = 1; i <= n; i++) {
        int score = readInt();
        // 直接把原数组也按区间加的形式写入差分数组。
        diffv[i] += score;
        diffv[i + 1] -= score;
    }

    for (int i = 1; i <= p; i++) {
        int l = readInt();
        int r = readInt();
        int z = readInt();
        diffv[l] += z;
        diffv[r + 1] -= z;
    }

    int now = 0;
    int ans = INT_MAX;
    for (int i = 1; i <= n; i++) {
        now += diffv[i];
        if (now < ans) ans = now;
    }

    printf("%d\n", ans);
    return 0;
}
