/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 01:11
 * update_at: 2026-10-09 01:11
 */
// 一本通 5060《【例3.10】简单计算器》
// 题面只描述「读入两个数 + 一个操作符，除数为 0 / 操作符非法两种错误分支」，
// 未指定实现手段（关键词、括号、标题三步判据全空），故用普通 if/else 链分派。
//
// 两个关键契约（由 10 个真实数据点反推，实测逐字节吻合）：
//   1) 输出格式 = 6 位有效数字 + 去尾随零 + 大数转科学计数法，
//      即 C 的 %g。数据点 problem8/9/10 分别输出 1.35287e+06 / 9.99998e+11 / 1e+12，
//      所以不能用 %f，也不能用 cout << fixed。
//   2) 结果可能是小数（题目【提示】样例 2：2 1.2 - 得 0.8），
//      所以两个操作数必须按 double 读入，不能用整数读完再转。
#include <cstdio>

typedef long long ll;  // 仓库约定：题目数据默认用 ll（本题数值走 double，仅作类型别名保留）

double num1;  // 第一个操作数
double num2;  // 第二个操作数
char op;      // 运算符，只取一个字符

// 按运算符分派并输出结果；除数为 0 与运算符非法各走一条错误分支。
void solve() {
    if (op == '+') {
        printf("%g\n", num1 + num2);
    } else if (op == '-') {
        printf("%g\n", num1 - num2);
    } else if (op == '*') {
        printf("%g\n", num1 * num2);
    } else if (op == '/') {
        // 除数为 0 是题面规定的错误分支，必须先判零再相除，否则得到 inf
        if (num2 == 0.0) {
            printf("Divided by zero!\n");
        } else {
            printf("%g\n", num1 / num2);
        }
    } else {
        // 操作符不为 + - * / 之一；此时题面要求不输出任何数值结果
        printf("Invalid operator!\n");
    }
}

int main() {
    // 读不满三项（题面保证不会出现）时静默退出，不产生任何输出
    if (scanf("%lf %lf %c", &num1, &num2, &op) != 3) {
        return 0;
    }

    solve();
    return 0;
}
