/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:11
 * update_at: 2026-11-11 00:11
 */
#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    string best_name = "";
    int max_scholarship = -1;
    int total_scholarship = 0;

    for (int i = 0; i < n; ++i) {
        string name;
        int score, class_score;
        char is_cadre, is_west;
        int papers;

        cin >> name >> score >> class_score >> is_cadre >> is_west >> papers;

        int cur = 0;
        // 1. 院士奖学金：期末平均成绩高于 80 分，并且在本学期内发表 1 篇或 1 篇以上论文
        if (score > 80 && papers >= 1) cur += 8000;
        // 2. 五四奖学金：期末平均成绩高于 85 分，并且班级评议成绩高于 80 分
        if (score > 85 && class_score > 80) cur += 4000;
        // 3. 成绩优秀奖：期末平均成绩高于 90 分
        if (score > 90) cur += 2000;
        // 4. 西部奖学金：期末平均成绩高于 85 分的西部省份学生
        if (score > 85 && is_west == 'Y') cur += 1000;
        // 5. 班级贡献奖：班级评议成绩高于 80 分的学生干部
        if (class_score > 80 && is_cadre == 'Y') cur += 850;

        total_scholarship += cur;

        // 如果有多人奖金相同，保留最早出现者，因此只在严格大于时更新
        if (cur > max_scholarship) {
            max_scholarship = cur;
            best_name = name;
        }
    }

    cout << best_name << "\n";
    cout << max_scholarship << "\n";
    cout << total_scholarship << "\n";

    return 0;
}
