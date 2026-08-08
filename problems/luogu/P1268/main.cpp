#include <bits/stdc++.h>
using namespace std;

const int MAXN = 35;
const int INF = 1e9;

int n;
int dis[MAXN][MAXN];

// 计算当前最后一个叶子 x 连到树上的那条“枝长”。
int get_limb_length(int size_now) {
    int x = size_now;
    int best = INF;
    for (int i = 1; i <= size_now - 1; i++) {
        for (int j = i + 1; j <= size_now - 1; j++) {
            int value = (dis[x][i] + dis[x][j] - dis[i][j]) / 2;
            if (value < best) {
                best = value;
            }
        }
    }
    return best;
}

// 递归删除最后一个叶子，累加它独有的那条边长。
int solve(int size_now) {
    if (size_now == 2) {
        return dis[1][2];
    }
    int limb = get_limb_length(size_now);
    return solve(size_now - 1) + limb;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    for (int i = 1; i <= n; i++) {
        dis[i][i] = 0;
    }

    // 输入的是上三角矩阵。
    for (int i = 1; i <= n - 1; i++) {
        for (int j = i + 1; j <= n; j++) {
            cin >> dis[i][j];
            dis[j][i] = dis[i][j];
        }
    }

    cout << solve(n) << '\n';
    return 0;
}
