/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 14:43
 * update_at: 2026-10-06 14:43
 */

// 按题面真值表：+ 是逻辑或（同为 0 才得 0），* 是逻辑与（同为 1 才得 1）。
// 对每个子表达式记录 (c0, c1)：使它取 0 / 取 1 的横线填法数，叶子横线是 (1,1)。
// 用调度场双栈一遍扫描：按优先级弹运算符合并，O(L) 求出整个表达式取 0 的方案数。

#include <cstdio>
#include <string>
#include <vector>

typedef long long ll;

const ll MOD = 10007;

// 合并结果的结构：c[0] 是子表达式取 0 的填法数，c[1] 是取 1 的填法数
struct Node {
    ll c0;
    ll c1;
};

std::string expr;              // 输入的运算符与括号串
std::vector<Node> nums;        // 操作数栈：每个元素是一个子表达式的 (c0, c1)
std::vector<char> ops;         // 运算符栈：保存 + * ( 三种字符
bool expect_num;               // 当前位置是否该出现操作数（横线是隐式的，靠它补上）

// 弹出一个运算符，合并操作数栈顶的两个子表达式
void reduce_top() {
    Node b = nums.back(); nums.pop_back();
    Node a = nums.back(); nums.pop_back();
    ll whole = (a.c0 + a.c1) * (b.c0 + b.c1) % MOD; // 两侧横线互不相交，方案数相乘
    Node res;
    if (ops.back() == '*') {
        // 与：结果为 1 当且仅当两边都是 1
        res.c1 = a.c1 * b.c1 % MOD;
        res.c0 = (whole - res.c1 + MOD) % MOD;
    } else {
        // 或：结果为 0 当且仅当两边都是 0
        res.c0 = a.c0 * b.c0 % MOD;
        res.c1 = (whole - res.c0 + MOD) % MOD;
    }
    nums.push_back(res);
    ops.pop_back();
}

// 判断栈顶运算符优先级是否不低于当前运算符（* 高于 +，同级从左到右）
bool should_reduce(char cur) {
    if (ops.back() == '(') return false;
    if (ops.back() == '*' && cur == '+') return true;
    return ops.back() == cur; // 同级先算左边的
}

int main() {
    ll len;
    scanf("%lld", &len);
    (void)len;
    // 表达式串最长 1e5，用静态大缓冲读入
    static char big[100005];
    scanf("%s", big);
    expr = big;

    expect_num = true;
    for (ll i = 0; i < (ll)expr.size(); i++) {
        char ch = expr[i];
        if (ch == '(') {
            // 左括号直接压栈，括号内自成一层
            ops.push_back('(');
            expect_num = true;
        } else if (ch == ')') {
            // 遇右括号：先补上括号内最后一条横线，再弹到左括号为止
            if (expect_num) nums.push_back(Node{1, 1});
            while (ops.back() != '(') reduce_top();
            ops.pop_back(); // 弹掉 '('，括号内结果收成一个操作数
            expect_num = false;
        } else {
            // 是运算符：若该出现操作数，说明前面藏着一条横线
            if (expect_num) nums.push_back(Node{1, 1});
            // 按优先级先合并栈顶可以算完的
            while (!ops.empty() && should_reduce(ch)) reduce_top();
            ops.push_back(ch);
            expect_num = true;
        }
    }
    // 表达式以横线收尾（如以运算符结束）时补最后一条横线
    if (expect_num) nums.push_back(Node{1, 1});
    // 弹空运算符栈，最终操作数栈里只剩整个表达式的 (c0, c1)
    while (!ops.empty()) reduce_top();
    printf("%lld\n", nums.back().c0);
    return 0;
}
