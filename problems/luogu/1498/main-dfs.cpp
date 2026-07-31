#include <bits/stdc++.h>
using namespace std;

int n;
char pic[1050][2050];

// 以 (x,y) 为"底部中心"画 level 层图腾
void dfs(int x, int y, int level) {
    if (level == 1) {                    // 最小单元：2行4列
        pic[x-1][y-1] = '/';
        pic[x-1][y]   = '\\';
        pic[x][y-2]   = '/';
        pic[x][y-1]   = '_';
        pic[x][y]     = '_';
        pic[x][y+1]   = '\\';
        return;
    }
    int half = 1 << (level - 1);         // 子图腾高/半宽 = 2^(level-1)
    dfs(x - half, y, level - 1);         // 上方
    dfs(x, y - half, level - 1);         // 左下方
    dfs(x, y + half, level - 1);         // 右下方
}

int main() {
    cin >> n;
    memset(pic, ' ', sizeof(pic));
    int h = 1 << n;                      // 总高 2^n
    dfs(h - 1, h, n);                    // 底部中心 (2^n-1, 2^n)
    for (int i = 0; i < h; i++) {
        int end = (1 << (n+1)) - 1;
        while (pic[i][end] == ' ') end--;
        for (int j = 0; j <= end; j++) cout << pic[i][j];
        cout << endl;
    }
    return 0;
}
