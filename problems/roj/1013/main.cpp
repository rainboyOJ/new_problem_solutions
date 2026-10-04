/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:30
 * update_at: 2026-10-04 22:30
 */
// main.cpp：读入华氏温度，按公式 C = 5×(F-32)÷9 换算成摄氏温度，保留 5 位小数输出。
#include <iostream>
#include <iomanip>

typedef long long ll;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    double fahrenheit = 0; // 华氏温度，题面输入是实数
    std::cin >> fahrenheit;

    double celsius = 5 * (fahrenheit - 32) / 9; // 题面公式 C = 5×(F-32)÷9

    // fixed + setprecision(5)：四舍五入保留小数点后 5 位并补零
    std::cout << std::fixed << std::setprecision(5) << celsius << std::endl;
    return 0;
}
