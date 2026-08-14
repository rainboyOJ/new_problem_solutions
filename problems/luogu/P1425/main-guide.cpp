/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 14:53
 * update_at: 2026-08-14 14:53
 */
#include <iostream>

int main() {
    int start_hour, start_minute, end_hour, end_minute;
    std::cin >> start_hour >> start_minute >> end_hour >> end_minute;

    // 统一换算成分钟，结束时间一定晚于开始时间，相减得到总时长
    int start_time = start_hour * 60 + start_minute;
    int end_time = end_hour * 60 + end_minute;
    int total_minutes = end_time - start_time;

    // 商是小时数，余数是分钟数（余数一定小于 60）
    std::cout << total_minutes / 60 << ' ' << total_minutes % 60 << '\n';

    return 0;
}
