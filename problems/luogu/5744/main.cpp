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
    char name[25];
    int age;
    int score;
};

int n;

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        Student s;
        cin >> s.name >> s.age >> s.score;
        // 培训后：年龄 +1，成绩 *1.2 但不超过 600
        s.age++;
        s.score = min(600, int(s.score * 1.2));
        cout << s.name << " " << s.age << " " << s.score << "\n";
    }
    return 0;
}
