/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

int n;
char before[12][12]; // 原始矩阵
char after[12][12];  // 目标矩阵

// 顺时针旋转 90 度
void rotate(char src[12][12], char dst[12][12]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dst[j][n - 1 - i] = src[i][j];
}

// 水平反射
void reflect(char src[12][12], char dst[12][12]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dst[i][n - 1 - j] = src[i][j];
}

// 比较两个矩阵是否相等
bool equal(char a[12][12], char b[12][12]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (a[i][j] != b[i][j]) return false;
    return true;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> before[i];
    for (int i = 0; i < n; i++) cin >> after[i];

    char t1[12][12], t2[12][12], t3[12][12], r[12][12];

    rotate(before, t1);
    rotate(t1, t2);
    rotate(t2, t3);
    reflect(before, r);

    if (equal(t1, after)) cout << 1;
    else if (equal(t2, after)) cout << 2;
    else if (equal(t3, after)) cout << 3;
    else if (equal(r, after)) cout << 4;
    else {
        // 反射后再旋转 1~3 次
        rotate(r, t1);
        rotate(t1, t2);
        rotate(t2, t3);
        if (equal(t1, after) || equal(t2, after) || equal(t3, after))
            cout << 5;
        else if (equal(before, after)) cout << 6;
        else cout << 7;
    }
    return 0;
}
