/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:44
 * update_at: 2026-10-04 22:44
 */
#include <cstdio>

// 全局变量：按题意保存四个 token，类型是本题的考点
char ch;        // 字符
int n;          // 整数
float a;        // 单精度浮点数（必须用 float，别写成 double）
double b;       // 双精度浮点数

int main() {
    // cin >> 按空白分词，按各自类型解析文本，题面的四行写法不影响读入
    std::scanf(" %c %d %f %lf", &ch, &n, &a, &b);
    // %.6f 一次完成四舍五入、补零和负号处理
    std::printf("%c %d %.6f %.6f\n", ch, n, a, b);
    return 0;
}
