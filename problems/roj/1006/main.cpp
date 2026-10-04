/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:22
 * update_at: 2026-10-04 22:22
 */

// 题意：输入一个不为 0 的数的书写串（可能是正数也可能是负数，可能带小数点），
// 输出它的负数书写：已是负数就原样输出，是正数就在最前面补一个负号。
// 关键点：这是“书写形式”的操作，不是数值运算——必须按字符串处理，
// 数字部分逐字符保留，不能用 float 读入（会丢失尾随零、大数变科学计数法）。

#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

typedef long long ll;

// 保存输入的那个数的书写串（整个输入只有一个 token）
string num_str;

int main() {
    // 输入只有一个数，用 scanf("%s") 读入一个不含空白的 token
    char buf[105];
    scanf("%s", buf);
    num_str = string(buf);

    // 如果已经以 '-' 开头，它已是负数书写，原样输出；
    // 否则在最前面补一个负号。两种情况数字部分都逐字符不动。
    if (!num_str.empty() && num_str[0] == '-')
        printf("%s\n", num_str.c_str());
    else
        printf("-%s\n", num_str.c_str());
    return 0;
}
