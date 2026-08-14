/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 14:57
 * update_at: 2026-08-14 14:57
 */
#include <iomanip>
#include <iostream>

double average_score(const double score[], int count) {
    // 去掉一个最高分和一个最低分后求平均
    double total = 0.0;
    double max_score = score[0];
    double min_score = score[0];
    for (int i = 0; i < count; i += 1) {
        total += score[i];
        if (score[i] > max_score) {
            max_score = score[i];
        }
        if (score[i] < min_score) {
            min_score = score[i];
        }
    }
    total = total - max_score - min_score;
    // 剩下 count - 2 个有效评分
    return total / (count - 2);
}

int main() {
    int player_count, judge_count;
    std::cin >> player_count >> judge_count;

    const int max_judges = 20;
    double scores[max_judges];

    double best = 0.0;
    for (int player = 0; player < player_count; player += 1) {
        for (int judge = 0; judge < judge_count; judge += 1) {
            std::cin >> scores[judge];
        }
        double average = average_score(scores, judge_count);
        // 只保留最高的平均分
        if (average > best) {
            best = average;
        }
    }

    std::cout << std::fixed << std::setprecision(2) << best << '\n';
    return 0;
}
