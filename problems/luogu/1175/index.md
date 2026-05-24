---
oj: "luogu"
problem_id: "P1175"
title: "表达式的转换"
date: 2025-12-31 12:15
toc: true
tags: ["栈"]
desc: "利用栈把中缀表达式转后缀表达式"
source: https://www.luogu.com.cn/problem/P1175
---

[[TOC]]

## 题目解析


这道题目（洛谷 P1175）是练习**栈（Stack）**应用的经典题目。它考察了两个核心环节：

1. **中缀表达式转后缀表达式**（逆波兰表达式）。
2. **后缀表达式的计算**，并要求输出每一步的计算过程。

虽然标准的后缀表达式计算通常使用栈来完成，但由于题目要求**输出每一步的中间形态**（即未计算的后缀部分还要保留），直接使用纯栈来做计算部分的输出会比较麻烦（因为栈底元素看不见）。因此，这道题最好的解法是：**用栈做转换，用动态数组（或列表）做计算演示。**

下面我将分步解析解题思路和代码。

## 第一步：中缀转后缀（利用栈）

这是标准的“调度场算法”（Shunting Yard Algorithm）变体。

**规则：**

1. **数字**：直接输出（存入结果数组）。
2. **左括号 `(`**：直接入栈。
3. **右括号 `)`**：不断弹出栈顶元素并输出，直到遇到左括号 `(` 为止。左括号弹出但不输出。
4. **运算符 `+ - \* / ^`**：
   - 栈为空或栈顶为 `(` 时，直接入栈。
   - **优先级比较**：
     - 如果当前运算符优先级 **大于** 栈顶运算符：直接入栈。
     - 如果当前运算符优先级 **小于或等于** 栈顶运算符：
       - **特例**：对于乘方 `^`，它是**右结合**的（`2^2^3` 等于 `2^(2^3)`）。如果当前是 `^` 且栈顶也是 `^`，则不弹出，直接入栈。
       - **普通情况**（左结合）：如果栈顶优先级 $\ge$ 当前优先级，弹出栈顶并输出，重复比较，直到条件不满足或栈空，然后将当前运算符入栈。

**优先级设定：**

- `^` : 3
- `* /` : 2
- `+ -` : 1
- `(` : 0

## 第二步：后缀表达式的运算与输出

题目要求输出如下格式：

```
8 3 2 6 * + 5 / - 4 + 
8 3 12 + 5 / - 4 + 
...
```

这意味着我们需要维护一个**序列**。每次找到序列中**第一个出现的运算符**，取出它前面的两个数字进行计算，将结果放回原位，然后输出整个序列。

**策略：**

1. 将生成的后缀表达式存入一个 `struct` 数组或 `vector` 中，每个节点存储它是数字还是运算符。
2. 循环操作，直到数组只剩下一个元素：
   - 遍历数组，找到**第一个**运算符。
   - 取出该运算符前两个位置的数字（设为 `a` 和 `b`）。
   - 计算 `a op b`。
   - 修改数组：删除这三个元素（数 数 符），在原位置插入计算结果。
   - 输出当前数组内容。

------

## C++ 代码实现

```cpp
#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// 定义节点，用于存储后缀表达式的元素
struct Node {
    bool isOp;  // 是否是运算符
    long long num;    // 如果是数字，存数值
    char op;    // 如果是运算符，存符号
};

// 获取运算符优先级
int getPriority(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0; // '(' 的优先级最低
}

// 执行单步运算
long long calc(long long a, long long b, char op) {
    switch(op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return pow(a, b);
    }
    return 0;
}

// 打印当前的表达式序列
void printList(const vector<Node>& list) {
    for (size_t i = 0; i < list.size(); i++) {
        if (list[i].isOp) cout << list[i].op << " ";
        else cout << list[i].num << " ";
    }
    cout << endl;
}

int main() {
    string s;
    cin >> s;

    stack<char> opStack;
    vector<Node> postfixList;

    // --- 阶段 1: 中缀 转 后缀 ---
    for (char c : s) {
        if (isdigit(c)) {
            // 题目保证数字只有一位，直接存入
            postfixList.push_back({false, (long long)(c - '0'), 0});
        } else if (c == '(') {
            opStack.push(c);
        } else if (c == ')') {
            while (!opStack.empty() && opStack.top() != '(') {
                postfixList.push_back({true, 0, opStack.top()});
                opStack.pop();
            }
            opStack.pop(); // 弹出 '('
        } else {
            // 是运算符
            int curPri = getPriority(c);
            while (!opStack.empty()) {
                char topOp = opStack.top();
                int topPri = getPriority(topOp);
                
                // 核心逻辑：
                // 1. 如果栈顶优先级 > 当前，必须弹
                // 2. 如果优先级相等：
                //    如果是左结合 (+ - * /)，要弹 (先进先算)
                //    如果是右结合 (^)，不弹 (后进先算)
                if (topPri > curPri || (topPri == curPri && c != '^')) {
                    postfixList.push_back({true, 0, topOp});
                    opStack.pop();
                } else {
                    break;
                }
            }
            opStack.push(c);
        }
    }
    // 将栈中剩余运算符弹出
    while (!opStack.empty()) {
        postfixList.push_back({true, 0, opStack.top()});
        opStack.pop();
    }

    // --- 阶段 2: 运算并输出过程 ---
    
    // 先输出最原始的后缀表达式
    printList(postfixList);

    while (postfixList.size() > 1) {
        // 寻找第一个运算符
        int idx = -1;
        for (int i = 0; i < postfixList.size(); i++) {
            if (postfixList[i].isOp) {
                idx = i;
                break;
            }
        }

        // 找到运算符后，前面两个必定是数字 (后缀表达式特性)
        long long b = postfixList[idx-1].num; // 栈顶元素 (右操作数)
        long long a = postfixList[idx-2].num; // 次栈顶元素 (左操作数)
        char op = postfixList[idx].op;

        // 计算结果
        long long res = calc(a, b, op);

        // 修改列表：将 [idx-2, idx] 这三项替换为 res
        // 为了方便，我们在 idx-2 处修改为结果，然后删除 idx-1 和 idx
        postfixList[idx-2] = {false, res, 0};
        postfixList.erase(postfixList.begin() + idx - 1, postfixList.begin() + idx + 1);

        // 输出当前状态
        printList(postfixList);
    }

    return 0;
}
```

## 关键点解析

1. 右结合的处理 (^)：

   在中缀转后缀时，普通的 2+2+3 会变成 2 2 + 3 +（先算左边的）。

   但是 2^2^3 应该变成 2 2 3 ^ ^（先算右边的）。

   所以在代码的 while 循环判断优先级时，c != '^' 这个条件非常关键。如果当前是 ^ 且栈顶也是 ^，我们不弹出，而是让新的 ^ 压在上面，这样出栈时新的（右边的）就会先出来。

2. 为什么不用 stack 做第二步？

   如果只用一个 stack<int> 来计算，我们只能看到计算结果 9，而无法方便地打印出类似 8 3 12 + 5 / ... 这种混合了“未处理后缀部分”的中间状态。使用 vector 并在中间进行替换（Erase + Insert 或原地修改）能最直观地模拟题目要求的输出过程。

3. 操作数顺序：

   在后缀表达式中，例如 8 3 -，3 是原本在运算符右边的数，8 是在左边的。

   当我们在 vector 中找到运算符 op (位置 i) 时，i-1 是右操作数，i-2 是左操作数。计算时要是 (i-2) op (i-1)。这一步特别是做除法和减法时绝对不能反。

## 参考

- https://www.luogu.com.cn/article/e1ogbx9e
