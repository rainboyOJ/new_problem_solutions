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
    char name[25]; // 姓名
    int ch, ma, en; // 三科成绩
};

int n;

int main() {
    cin >> n;
    Student best; // 总分最高的学生
    int best_tot = -1;
    for (int i = 1; i <= n; i++) {
        Student cur;
        cin >> cur.name >> cur.ch >> cur.ma >> cur.en;
        int tot = cur.ch + cur.ma + cur.en;
        if (tot > best_tot) { // 严格大于才更新，保留先出现的
            best_tot = tot;
            best = cur;
        }
    }
    cout << best.name << " " << best.ch << " " << best.ma << " " << best.en;
    return 0;
}
