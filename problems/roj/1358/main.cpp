/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 11:53
 * update_at: 2026-10-05 11:53
 */
// main.cpp：中缀表达式求值。先切词校验合法性，再用调度场算法转成后缀，
// 最后用操作数栈从左到右归约求值；任一阶段失败就输出 NO。

#include <cstdio>
#include <cstring>

typedef long long ll;

const int MAXN = 512; // 表达式长度很小，512 足够容纳整行

char raw[MAXN];  // 读入的原始内容（可能带首尾空白）
char expr[MAXN]; // 去掉首尾空白、截到 '@' 之前的表达式
int len;         // expr 的字符个数

// 记号数组：kind 为 0 表示运算数（值在 tok_num），为 1 表示运算符或括号（字符在 tok_op）
int tok_kind[MAXN];
ll tok_num[MAXN];
char tok_op[MAXN];
int tok_cnt;

// 后缀序列，含义同记号数组
int post_kind[MAXN];
ll post_num[MAXN];
char post_op[MAXN];
int post_cnt;

char op_stack[MAXN]; // 调度场算法：暂存还没到计算时机的中缀运算符
int op_top;

ll num_stack[MAXN]; // 求值用的操作数栈
int num_top;

int is_digit(char ch) { return '0' <= ch && ch <= '9'; }

int is_space(char ch) { return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r'; }

// 二元运算符的优先级：乘除高于加减。
int level(char op) {
    if (op == '*' || op == '/') return 2;
    return 1;
}

void add_number(ll value) {
    tok_kind[tok_cnt] = 0;
    tok_num[tok_cnt] = value;
    tok_cnt++;
}

void add_op(char op) {
    tok_kind[tok_cnt] = 1;
    tok_op[tok_cnt] = op;
    tok_cnt++;
}

// 读入整行：'@' 是结束符，取它之前的部分作为表达式。
void read_input() {
    int ch;
    int n = 0;
    while ((ch = getchar()) != EOF && ch != '@' && n < MAXN - 1) {
        raw[n] = (char)ch;
        n++;
    }
    raw[n] = '\0';

    // 去掉首尾空白，内部空白留给 tokenize 判非法
    int left = 0;
    int right = n - 1;
    while (left <= right && is_space(raw[left])) left++;
    while (right >= left && is_space(raw[right])) right--;
    int k = 0;
    for (int i = left; i <= right; i++) {
        expr[k] = raw[i];
        k++;
    }
    expr[k] = '\0';
}

// 切词并校验合法性：运算数位只接受数字、'(' 和一元负号，运算符位只接受
// 二元运算符和 ')'。合法返回 1，非法返回 0。
int tokenize() {
    tok_cnt = 0;
    len = strlen(expr);
    int expect_operand = 1; // 下一个记号是否应当出现在运算数位置
    int depth = 0;          // 还没闭合的左括号个数
    int i = 0;
    while (i < len) {
        char ch = expr[i];
        if (is_digit(ch)) {
            if (!expect_operand) return 0; // 数字只能出现在运算数位置，如 (5)3
            ll value = 0;
            while (i < len && is_digit(expr[i])) {
                value = value * 10 + (expr[i] - '0');
                i++;
            }
            add_number(value);
            expect_operand = 0;
        } else if (ch == '-' && expect_operand) {
            // 运算数位置上的 '-' 是一元负号，后面必须紧跟数字
            i++;
            if (i >= len || !is_digit(expr[i])) return 0;
            ll value = 0;
            while (i < len && is_digit(expr[i])) {
                value = value * 10 + (expr[i] - '0');
                i++;
            }
            add_number(-value);
            expect_operand = 0;
        } else if (ch == '(') {
            if (!expect_operand) return 0; // 5( 这种缺少运算符
            add_op('(');
            depth++;
            expect_operand = 1;
            i++;
        } else if (ch == ')') {
            if (expect_operand || depth == 0) return 0; // 空括号或多余的右括号
            add_op(')');
            depth--;
            expect_operand = 0;
            i++;
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            if (expect_operand) return 0; // 运算符出现在运算数位置，如 +*
            add_op(ch);
            expect_operand = 1;
            i++;
        } else {
            return 0; // 其它字符（含内部空白）一律非法
        }
    }
    if (expect_operand || depth != 0) return 0; // 空串、以运算符结尾、括号没配对
    return 1;
}

// 调度场算法：按优先级把中缀记号重排成后缀序列。
void to_postfix() {
    post_cnt = 0;
    op_top = 0;
    for (int i = 0; i < tok_cnt; i++) {
        if (tok_kind[i] == 0) {
            post_kind[post_cnt] = 0;
            post_num[post_cnt] = tok_num[i];
            post_cnt++;
        } else if (tok_op[i] == '(') {
            op_stack[op_top] = '(';
            op_top++;
        } else if (tok_op[i] == ')') {
            while (op_stack[op_top - 1] != '(') {
                post_kind[post_cnt] = 1;
                post_op[post_cnt] = op_stack[op_top - 1];
                post_cnt++;
                op_top--;
            }
            op_top--; // 弹出并丢掉左括号
        } else {
            // 栈顶优先级不低于当前运算符的先出栈，保证同级从左到右结合
            while (op_top > 0 && op_stack[op_top - 1] != '(' &&
                   level(op_stack[op_top - 1]) >= level(tok_op[i])) {
                post_kind[post_cnt] = 1;
                post_op[post_cnt] = op_stack[op_top - 1];
                post_cnt++;
                op_top--;
            }
            op_stack[op_top] = tok_op[i];
            op_top++;
        }
    }
    while (op_top > 0) {
        post_kind[post_cnt] = 1;
        post_op[post_cnt] = op_stack[op_top - 1];
        post_cnt++;
        op_top--;
    }
}

// 用操作数栈求后缀表达式的值；除以 0 视为非法，返回 0 表示失败。
int eval_postfix(ll &answer) {
    num_top = 0;
    for (int i = 0; i < post_cnt; i++) {
        if (post_kind[i] == 0) {
            num_stack[num_top] = post_num[i];
            num_top++;
        } else {
            ll right = num_stack[num_top - 1]; // 后入栈的是右操作数
            num_top--;
            ll left = num_stack[num_top - 1];
            num_top--;
            char op = post_op[i];
            ll value;
            if (op == '+') {
                value = left + right;
            } else if (op == '-') {
                value = left - right;
            } else if (op == '*') {
                value = left * right;
            } else {
                if (right == 0) return 0;
                value = left / right; // C++ 整数除法向零取整
            }
            num_stack[num_top] = value;
            num_top++;
        }
    }
    answer = num_stack[0];
    return 1;
}

int main() {
    read_input();

    if (!tokenize()) {
        printf("NO\n");
        return 0;
    }
    to_postfix();

    ll answer = 0;
    if (!eval_postfix(answer)) {
        printf("NO\n");
        return 0;
    }
    printf("%lld\n", answer);
    return 0;
}
