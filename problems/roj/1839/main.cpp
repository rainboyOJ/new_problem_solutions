/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 06:45
 * update_at: 2026-10-08 06:45
 */
// main.cpp：谁拿了最多奖学金（05NOIP 提高组 / 一本通 1839）。
// 与 main.py 同一算法：五项奖学金条件互相独立、可叠加，边读边算；
// 维护"最高奖金"时用严格大于，天然满足"并列取最早出现者"。
//
// 判读依据（与 content.md 逐条对照）：
//   1) 院士奖学金 8000：avg > 80 且 papers >= 1（"1 篇或 1 篇以上"取 >=）
//   2) 五四奖学金 4000：avg > 85 且 cls > 80
//   3) 成绩优秀奖 2000：avg > 90
//   4) 西部奖学金 1000：avg > 85 且 west == 'Y'
//   5) 班级贡献奖  850：cls > 80 且 leader == 'Y'
// 题面所有成绩都是"高于"，一律严格大于；只有论文篇数是"1 篇或以上"，取 >=。
// 单人上限 8000+4000+2000+1000+850 = 15850，n <= 100 ⇒ 总和上限 1585000，int 足够。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0; // 无输入时安全退出

    int best_val = -1;        // 初值 -1：即使全员 0 元也能让第 1 个人完成初始化
    string best_name;         // 最高奖金获得者（并列时保留最早出现的）
    int total_sum = 0;        // 全员奖学金总额

    for (int i = 0; i < n; i++) {
        string name;
        int avg, cls, papers;  // 期末平均成绩 / 班级评议成绩 / 论文篇数
        char leader, west;     // 是否学生干部 / 是否西部省份学生：Y 或 N
        cin >> name >> avg >> cls >> leader >> west >> papers;

        int money = 0; // 当前学生各项奖学金之和
        if (avg > 80 && papers >= 1) money += 8000;  // 院士奖学金
        if (avg > 85 && cls > 80) money += 4000;     // 五四奖学金
        if (avg > 90) money += 2000;                 // 成绩优秀奖
        if (avg > 85 && west == 'Y') money += 1000;  // 西部奖学金
        if (cls > 80 && leader == 'Y') money += 850; // 班级贡献奖

        total_sum += money;
        if (money > best_val) { // 严格大于：并列时不覆盖，最早出现者胜出
            best_val = money;
            best_name = name;
        }
    }

    cout << best_name << "\n" << best_val << "\n" << total_sum << "\n";
    return 0;
}
