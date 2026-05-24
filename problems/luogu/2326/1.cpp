#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n;
int grid[MAXN][MAXN];
int row_sum[MAXN];  // 每行的敌人分数总和
int col_sum[MAXN];  // 每列的敌人分数总和

void solve() {
    cin >> n;
    
    // 读取矩阵并计算行列和
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            row_sum[i] += grid[i][j];
            col_sum[j] += grid[i][j];
        }
    }
    
    int max_score = -1;
    bool has_position = false;
    
    // 遍历所有位置寻找容身之地
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 0) {
                has_position = true;
                // 当前位置的分数 = 行和 + 列和（因为当前位置为0，不会重复计算）
                int score = row_sum[i] + col_sum[j];
                max_score = max(max_score, score);
            }
        }
    }
    
    if (!has_position) {
        cout << "Bad Game!" << endl;
    } else {
        cout << max_score << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    solve();
    return 0;
}
