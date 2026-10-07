/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 09:17
 * update_at: 2026-10-06 09:17
 */

#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 15;

char src[MAXN][MAXN];
char dst[MAXN][MAXN];
char tmp[MAXN][MAXN];
char buf[MAXN][MAXN];
int n;

// 将 g 顺时针旋转 90° 存入 res
void rotate_cw(char g[MAXN][MAXN], char res[MAXN][MAXN]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            res[j][n - 1 - i] = g[i][j];
}

// 将 g 水平翻转存入 res
void mirror(char g[MAXN][MAXN], char res[MAXN][MAXN]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            res[i][n - 1 - j] = g[i][j];
}

// 比较两个图案是否完全相同
bool same(char a[MAXN][MAXN], char b[MAXN][MAXN]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (a[i][j] != b[i][j])
                return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> src[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> dst[i][j];

    // 候选图案：#1 旋转90°，#2 旋转180°，#3 旋转270°，#4 水平翻转，
    // #5 翻转后再旋转90°/180°/270°，#6 原样
    char r90[MAXN][MAXN], r180[MAXN][MAXN], r270[MAXN][MAXN];
    char mir[MAXN][MAXN], m90[MAXN][MAXN], m180[MAXN][MAXN], m270[MAXN][MAXN];

    rotate_cw(src, r90);
    rotate_cw(r90, r180);
    rotate_cw(r180, r270);
    mirror(src, mir);
    rotate_cw(mir, m90);
    rotate_cw(m90, m180);
    rotate_cw(m180, m270);

    if (same(r90, dst))  { cout << 1 << '\n'; return 0; }
    if (same(r180, dst)) { cout << 2 << '\n'; return 0; }
    if (same(r270, dst)) { cout << 3 << '\n'; return 0; }
    if (same(mir, dst))  { cout << 4 << '\n'; return 0; }
    if (same(m90, dst))  { cout << 5 << '\n'; return 0; }
    if (same(m180, dst)) { cout << 5 << '\n'; return 0; }
    if (same(m270, dst)) { cout << 5 << '\n'; return 0; }
    if (same(src, dst))  { cout << 6 << '\n'; return 0; }
    cout << 7 << '\n';
    return 0;
}
