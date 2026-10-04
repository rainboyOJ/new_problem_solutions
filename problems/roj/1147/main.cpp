/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 03:27
 * update_at: 2026-10-05 03:27
 */
#include <iostream>
#include <string>
using namespace std;

typedef long long ll;

ll n;
ll best_score;    // 当前见过的最高分
string best_name; // 当前最高分对应的姓名

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    best_score = -1; // 分数非负，第一位学生一定被接收
    for (ll i = 1; i <= n; i++) {
        ll score;
        string name;
        cin >> score >> name;
        // 只有严格更高才换人，并列时保留先到者
        if (score > best_score) {
            best_score = score;
            best_name = name;
        }
    }
    cout << best_name << "\n";
    return 0;
}
