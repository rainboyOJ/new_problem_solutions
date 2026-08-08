// brute.cpp：枚举断点并直接按规则双向收集珠子，作为教学版和对拍基准程序。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 405;

int n;
char a[MAXN];

int next_idx(int x) {
    x++;
    if (x > n) {
        x = 1;
    }
    return x;
}

int prev_idx(int x) {
    x--;
    if (x <= 0) {
        x = n;
    }
    return x;
}

int collect_clockwise(int x, int &end_pos) {
    char color = a[x];
    int cnt = 1;
    end_pos = x;

    for (int p = next_idx(x); p != x; p = next_idx(p)) {
        if (color == 'w' && a[p] != 'w') {
            color = a[p];
        }
        if (a[p] == color || a[p] == 'w') {
            cnt++;
            end_pos = p;
        }
        else {
            break;
        }
    }

    return cnt;
}

int collect_counterclockwise(int x, int end_pos) {
    if (x == end_pos) {
        return 0;
    }

    char color = a[x];
    int cnt = 1;

    for (int p = prev_idx(x); p != x && p != end_pos; p = prev_idx(p)) {
        if (color == 'w' && a[p] != 'w') {
            color = a[p];
        }
        if (a[p] == color || a[p] == 'w') {
            cnt++;
        }
        else {
            break;
        }
    }

    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    cin >> (a + 1);

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int end_pos = 0;
        int total = collect_clockwise(i, end_pos);
        total += collect_counterclockwise(prev_idx(i), end_pos);
        ans = max(ans, total);
    }

    if (ans > n) {
        ans = n;
    }
    cout << ans << '\n';
    return 0;
}
