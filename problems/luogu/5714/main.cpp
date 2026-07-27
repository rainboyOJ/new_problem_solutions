/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    double m, h; // 体重（kg），身高（m）
    cin >> m >> h;
    double bmi = m / (h * h);
    if (bmi < 18.5) {
        cout << "Underweight" << endl;
    } else if (bmi < 24) {
        cout << "Normal" << endl;
    } else {
        // 超重时先输出 BMI（六位有效数字），再输出 Overweight
        printf("%.6g\nOverweight\n", bmi);
    }
    return 0;
}
