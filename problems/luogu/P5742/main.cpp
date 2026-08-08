/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

struct Student {
    int id;      // 学号
    int ac;      // 学业成绩
    int qu;      // 素质拓展成绩
};

int n;

// 判断是否为优秀：总分 > 140 且 综合分 >= 80
// 综合分 = academic * 0.7 + quality * 0.3
// 用整数避免浮点：academic*7 + quality*3 >= 800
bool is_excellent(Student &s) {
    if (s.ac + s.qu <= 140) return false;
    return s.ac * 7 + s.qu * 3 >= 800;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        Student s;
        cin >> s.id >> s.ac >> s.qu;
        if (is_excellent(s)) cout << "Excellent\n";
        else cout << "Not excellent\n";
    }
    return 0;
}
