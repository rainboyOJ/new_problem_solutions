/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 16:30
 * update_at: 2026-10-06 16:30
 */

// 把每条探索路线折叠成"树的最小表示"（规范形）：0 看成进入、1 看成退回，
// 一个结点的规范串 = "0" + 儿子规范串排序后拼接 + "1"。
// 两条串来自同一棵树 <=> 规范形相同（AHU 有根树同构）。
// 用显式栈自底向上折叠，不建树也不递归（链形树递归深度可达 1500）。

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;

const int MAXLEN = 3005;

char route[MAXLEN]; // 当前读入的一条探索路线串

// 栈的每一层是"还没封口的结点"已收集的儿子规范串；栈底是根（没有前导 0 和尾 1）
vector<string> stk[MAXLEN / 2];
int top; // 栈顶下标，从 0 开始，stk[0] 是根的儿子列表

// 把若干儿子的规范串封成一个结点：0 + 排序拼接 + 回父亲的 1
string wrap_node(vector<string> &kids) {
    sort(kids.begin(), kids.end()); // 排序抹掉"先走哪个儿子"这一同构不计的自由度
    string res = "0";
    for (int i = 0; i < (int)kids.size(); i++) res += kids[i];
    res += "1";
    return res;
}

// 把一条探索路线折叠成规范形
string canon() {
    top = 0;
    stk[0].clear();
    for (int i = 0; route[i] != '\0'; i++) {
        if (route[i] == '0') { // 走向更远的一站：开一个新结点
            top++;
            stk[top].clear();
        } else {               // 退回父亲：栈顶结点封口，并入父亲（新栈顶）的儿子列表
            string node = wrap_node(stk[top]);
            top--;
            stk[top].push_back(node);
        }
    }
    // 串结束回到中央车站：根层不封口，直接排序拼接（保证两条串用同一套约定比较）
    sort(stk[0].begin(), stk[0].end());
    string res = "";
    for (int i = 0; i < (int)stk[0].size(); i++) res += stk[0][i];
    return res;
}

int main() {
    ll t;
    scanf("%lld", &t);
    while (t--) {
        scanf("%s", route);
        string c1 = canon();
        scanf("%s", route);
        string c2 = canon();
        if (c1 == c2) printf("same\n");
        else printf("different\n");
    }
    return 0;
}
