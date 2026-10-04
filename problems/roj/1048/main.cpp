/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:30
 * update_at: 2026-10-04 23:30
 */
#include <iostream>
using namespace std;

typedef long long ll;

ll a, b; // a: 语文成绩，b: 数学成绩

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> a >> b;
    // 两门课不及格标记相加：0/1/2，恰好为 1 时输出 1
    cout << ((a < 60) + (b < 60) == 1) << '\n';
    return 0;
}
