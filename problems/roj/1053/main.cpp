/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:37
 * update_at: 2026-10-04 23:37
 */
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;

int a, b, c; // 三个待比较的整数

int main() {
    // 读入三个整数（可能为负）
    scanf("%d %d %d", &a, &b, &c);
    // 直接用 std::max 的链式调用取三者最大值，结合律保证正确
    printf("%d\n", max(a, max(b, c)));
    return 0;
}