#include <bits/stdc++.h>
using namespace std;

long long memo[25][25][25];
bool vis[25][25][25];

// 记忆化搜索计算 w(a,b,c)。
long long dfs(int a, int b, int c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return 1;
    }
    if (a > 20 || b > 20 || c > 20) {
        return dfs(20, 20, 20);
    }
    if (vis[a][b][c]) {
        return memo[a][b][c];
    }

    long long ret;
    if (a < b && b < c) {
        ret = dfs(a, b, c - 1) + dfs(a, b - 1, c - 1) - dfs(a, b - 1, c);
    }
    else {
        ret = dfs(a - 1, b, c) + dfs(a - 1, b - 1, c) + dfs(a - 1, b, c - 1) - dfs(a - 1, b - 1, c - 1);
    }

    vis[a][b][c] = true;
    memo[a][b][c] = ret;
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long a, b, c;
    while (cin >> a >> b >> c) {
        if (a == -1 && b == -1 && c == -1) {
            break;
        }

        long long ans;
        if (a <= 0 || b <= 0 || c <= 0) {
            ans = 1;
        }
        else if (a > 20 || b > 20 || c > 20) {
            ans = dfs(20, 20, 20);
        }
        else {
            ans = dfs((int) a, (int) b, (int) c);
        }

        cout << "w(" << a << ", " << b << ", " << c << ") = " << ans << '\n';
    }

    return 0;
}
