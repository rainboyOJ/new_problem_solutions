/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 04:26
 * update_at: 2026-10-05 04:26
 */

#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 305; // n < 300，多开几个下标防止越界

// 一个学生的排序所需信息
struct Student {
    ll id;      // 学号，即输入行号（从 1 开始）
    ll total;   // 语文 + 数学 + 英语
    ll chinese; // 语文成绩，总分并列时用来比较
};

ll n;
Student stu[MAXN]; // stu[i] 表示学号为 i 的学生

// 题面规则：总分从高到低，总分相同看语文从高到低，再相同则学号小的在前。
bool cmp_student(const Student &a, const Student &b) {
    if (a.total != b.total) return a.total > b.total;
    if (a.chinese != b.chinese) return a.chinese > b.chinese;
    return a.id < b.id;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (ll i = 1; i <= n; i++) {
        ll chinese, math, english;
        cin >> chinese >> math >> english;
        stu[i].id = i;
        stu[i].total = chinese + math + english;
        stu[i].chinese = chinese;
    }

    sort(stu + 1, stu + n + 1, cmp_student);

    // 按名次输出前 5 名的学号与总分
    ll top = (n < 5 ? n : 5);
    for (ll i = 1; i <= top; i++) {
        cout << stu[i].id << " " << stu[i].total << "\n";
    }

    return 0;
}
