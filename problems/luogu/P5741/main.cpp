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
    char name[15];
    int ch, ma, en, tot;
};

Student stu[1005];
int n;

// 判断两名学生是否为"旗鼓相当的对手"
bool is_close(Student &a, Student &b) {
    if (abs(a.ch - b.ch) > 5) return false;
    if (abs(a.ma - b.ma) > 5) return false;
    if (abs(a.en - b.en) > 5) return false;
    if (abs(a.tot - b.tot) > 10) return false;
    return true;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> stu[i].name >> stu[i].ch >> stu[i].ma >> stu[i].en;
        stu[i].tot = stu[i].ch + stu[i].ma + stu[i].en;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (is_close(stu[i], stu[j]))
                cout << stu[i].name << " " << stu[j].name << "\n";
        }
    }
    return 0;
}
