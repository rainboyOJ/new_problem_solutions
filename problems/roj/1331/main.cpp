/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 10:01
 * update_at: 2026-10-05 10:01
 */

// main.cpp：后缀表达式求值。逐字符扫描，运算符按四字母十交集弹出两个压回栈；
// 不能用 split() 切 token，因为运算符可以连写（如 `+*-`）。

#include <cstdio>
#include <cstdlib>
#include <cstring>

typedef long long ll;

const char END_MARK = '@';          // 表达式结束标志，它之后的内容一律忽略
const char *OPERATORS = "+-*/";     // 四种运算符；正面枚举才能避免把其它字符当成运算符多弹栈

ll stack_buf[300]; // 表达式长度 < 250，中间结果最多约 125 个；题面约束 < 2^64，超出 ll 范围时会发生溢出，按 OJ 习惯用 ll 表示
int top;            // 栈顶指针：stack_buf[0..top-1] 是当前栈，栈空时 top == 0

// 把已经拼好的数字压栈：仅当运算符与运算符之间隔了数字时调用
void push_number(ll &number, int &reading) {
    if (reading) {
        stack_buf[top++] = number;
        number = 0;
        reading = 0;
    }
}

// 遇运算符：先弹右、后弹左，算完压回；调用前必须保证两操作数都已经在栈上
void apply_operator(char op) {
    ll right = stack_buf[--top]; // 栈顶是右操作数（后入栈）
    ll left  = stack_buf[--top]; // 下面是左操作数（先入栈）
    ll res;
    if (op == '+')      res = left + right;
    else if (op == '-') res = left - right;
    else if (op == '*') res = left * right;
    else                res = left / right; // 题面保证整除，结果无歧义
    stack_buf[top++] = res;
}

int is_digit(char ch) { return '0' <= ch && ch <= '9'; }   // 只认 ASCII 数字位，避免 Unicode 数字陷阱
int is_operator(char ch) { return std::strchr(OPERATORS, ch) != NULL; } // 正面枚举运算符

int main() {
    // 一行读完整个表达式（可能含空格 / 换行 / `@` 之后的内容）
    char buf[512];
    if (!std::fgets(buf, sizeof buf, stdin)) return 0;

    top = 0;
    ll number = 0;       // 正在拼装的运算数
    int reading = 0;     // 是否正处于一个运算数内部：区分「读到的是 0」与「还没开始读数」

    for (int i = 0; buf[i] != '\0'; ++i) {
        char ch = buf[i];
        if (ch == END_MARK) break;                  // `@` 之后的内容一律不看
        if (is_digit(ch)) {                         // 数字位：边扫边拼多位数
            number = number * 10 + (ch - '0');
            reading = 1;
            continue;
        }
        // 非数字位：先把可能存在的「待入栈运算数」结算掉（顺序必须先于运算符处理）
        push_number(number, reading);
        if (is_operator(ch)) apply_operator(ch);    // 只对四种运算符归约；空格/制表符/换行当分隔符
        // 其它字符（空格等）一律跳过，不影响结果
    }
    // `@` 可能紧跟运算数（如 `12@`），这里补一次收尾入栈
    push_number(number, reading);

    std::printf("%lld\n", stack_buf[0]);
    return 0;
}