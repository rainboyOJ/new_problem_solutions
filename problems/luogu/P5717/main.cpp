/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    int a[3]; // 三条边长度
    cin >> a[0] >> a[1] >> a[2];
    // 排序使 a[0] <= a[1] <= a[2]，方便判断三角形和角类型
    if (a[0] > a[1]) swap(a[0], a[1]);
    if (a[1] > a[2]) swap(a[1], a[2]);
    if (a[0] > a[1]) swap(a[0], a[1]);

    // 三角形两边之和必须大于第三边
    if (a[0] + a[1] <= a[2]) {
        cout << "Not triangle" << endl;
        return 0;
    }

    // 用平方关系判断角类型
    int left = a[0] * a[0] + a[1] * a[1];
    int right = a[2] * a[2];
    if (left == right) {
        cout << "Right triangle" << endl;
    } else if (left > right) {
        cout << "Acute triangle" << endl;
    } else {
        cout << "Obtuse triangle" << endl;
    }

    // 等腰：至少有两条边相等
    if (a[0] == a[1] || a[1] == a[2]) {
        cout << "Isosceles triangle" << endl;
    }
    // 等边：三条边都相等
    if (a[0] == a[2]) {
        cout << "Equilateral triangle" << endl;
    }
    return 0;
}
