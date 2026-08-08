#include <bits/stdc++.h>
using namespace std;

/**
 * ============================================================
 * 题目: P3952 [NOIP 2017 提高组] 时间复杂度
 * ============================================================
 * 核心任务: 判断小明声称的"时间复杂度"是否正确
 *
 * 【A++ 循环语法】
 *   F i x y    // 新建变量 i = x, 当 i <= y 时进入循环, 每次 i++
 *     循环体
 *   E          // 循环结束, 变量 i 被销毁
 *
 * 【核心思想】
 * 用栈模拟循环的嵌套关系。每个循环属于三类之一：
 *   0: 常数循环 (数字->数字且x<=y, 或 n->n)
 *   1: 贡献 O(n) 的循环 (数字->n)
 *   2: 死循环 (数字->数字且x>y, 或 n->数字)
 *
 * 关键观察: 如果一个循环是"死循环"(类型2), 那么它内部的所有循环
 * 实际上都不会执行。因此需要一个计数器 dead_depth 来屏蔽内部贡献。
 *
 * 【ERR 语法错误】
 * ① F 和 E 不匹配
 * ② 变量名与已存在且未被销毁的变量重复
 * 注意: 即使循环不会执行, 内部语法错误也要报 ERR!
 * ============================================================
 */

const int MAXL = 105;

/**
 * 【LoopInfo: 每一层循环需要记录的信息】
 * 为什么需要这些信息? 因为出栈(E)时需要回退各种状态。
 */
struct LoopInfo {
    string var;       // 当前循环定义的变量名
    bool claimed;     // 这个变量名是否成功占用
                      // (如果 F 时发现变量名重复, claimed=false, 出栈时不应释放)
    bool is_dead;     // 这一层循环是否一开始就不会执行 (类型2)
    bool add_power;   // 这一层是否真的让复杂度多乘了一个 n
};

int test_cnt;         // 数据组数
int line_cnt;         // 当前程序的行数
string target_complexity; // 小明声称的复杂度字符串

bool used_var[256];   // 变量名占用表。下标用 ASCII 码, 值表示是否被占用
                      // 题目保证变量名是单个小写字母(不为n), 所以256够用了
LoopInfo stk[MAXL];   // 栈, 模拟循环嵌套
int top_ptr;          // 栈顶指针, 同时表示栈中元素个数

/**
 * 【解析声称的复杂度字符串, 提取指数】
 * 输入: "O(1)" -> 返回 0
 *       "O(n^2)" -> 返回 2
 * 方法: 先处理两个特殊短串, 再找 '^' 和 ')' 之间的数字
 */
int parse_target_power(const string &s) {
    if (s == "O(1)") return 0;
    if (s == "O(n)") return 1;

    int pos1 = s.find('^');
    int pos2 = s.find(')');
    int value = 0;
    for (int i = pos1 + 1; i < pos2; i++) {
        value = value * 10 + (s[i] - '0');
    }
    return value;
}

/**
 * 【判断字符串是否为 "n"】
 */
bool is_n(const string &s) {
    return s == "n";
}

/**
 * 【把纯数字字符串转成整数】
 * 注意: 调用前要确保 s 不是 "n"
 */
int to_number(const string &s) {
    int value = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        value = value * 10 + (s[i] - '0');
    }
    return value;
}

/**
 * 【判断循环类型: 根据 x 和 y 的形式分类】
 * 返回值:
 *   0 -> 常数循环 (执行常数次或1次)
 *   1 -> 这一层会贡献一个 n (数字 -> n)
 *   2 -> 死循环, 根本不会执行 (数字>数字 或 n->数字)
 */
int get_loop_type(const string &x, const string &y) {
    bool x_is_n = is_n(x);
    bool y_is_n = is_n(y);

    if (!x_is_n && !y_is_n) {
        // 数字 -> 数字
        int lx = to_number(x);
        int ry = to_number(y);
        if (lx > ry) return 2;  // 起点>终点, 循环不执行
        return 0;               // 执行 (ry-lx+1) 次, 常数级别
    }

    if (!x_is_n && y_is_n) return 1;  // 数字 -> n: O(n)
    if (x_is_n && !y_is_n) return 2;  // n -> 数字: n远大于数字, 不执行

    // n 到 n 只执行 1 次, 是常数循环。
    return 0;
}

/**
 * 【处理一个完整的程序, 返回结果编码】
 * 返回值:
 *   -1 -> 语法错误 ERR
 *    1 -> 复杂度匹配 Yes
 *    0 -> 复杂度不匹配 No
 */
int solve_one_case() {
    cin >> line_cnt >> target_complexity;

    // 初始化: 清空变量占用表, 清空栈
    memset(used_var, 0, sizeof(used_var));
    top_ptr = 0;

    int target_power = parse_target_power(target_complexity);

    /**
     * 【三个核心状态变量】
     * current_power: 当前"活跃执行路径"上的 O(n) 层数
     *   - 如果当前在死循环内部, 新增的普通循环不会增加 current_power
     * max_power: 历史上出现过的最大层数 (最终要和 target_power 比较)
     * dead_depth: 当前嵌套在多少个"死循环"内部
     *   - dead_depth > 0 时, 内部的新循环对复杂度无贡献
     */
    int current_power = 0;
    int max_power = 0;
    int dead_depth = 0;
    bool has_error = false;

    for (int i = 1; i <= line_cnt; i++) {
        string op;
        cin >> op;

        if (op == "F") {
            // === 处理 F i x y ===
            string var, x, y;
            cin >> var >> x >> y;

            bool claimed = false;
            unsigned char name = (unsigned char)var[0];

            // 【语法检查②: 变量名是否与已存在的重复】
            if (used_var[name]) {
                has_error = true; // 未销毁变量重名
            } else {
                used_var[name] = true;  // 占用该变量名
                claimed = true;         // 标记为"我成功占用了"
            }

            int loop_type = get_loop_type(x, y);

            // 入栈: 把这一层循环的信息记录下来
            top_ptr++;
            stk[top_ptr].var = var;
            stk[top_ptr].claimed = claimed;
            stk[top_ptr].is_dead = false;
            stk[top_ptr].add_power = false;

            if (loop_type == 2) {
                // === 死循环: 标记这一层, dead_depth 增加 ===
                stk[top_ptr].is_dead = true;
                dead_depth++;
            } else if (loop_type == 1 && dead_depth == 0) {
                // === O(n) 循环, 且当前不在任何死循环内部 ===
                // 只有这时, 这一层才真的会让复杂度多乘一个 n
                stk[top_ptr].add_power = true;
                current_power++;
                if (current_power > max_power) {
                    max_power = current_power;  // 更新历史最大值
                }
            }
            // 类型 0 (常数循环): 什么都不做
        } else {
            // === 处理 E ===
            if (top_ptr == 0) {
                // 栈已空却有 E -> F 和 E 不匹配 (语法错误①)
                has_error = true;
                continue;
            }

            // 弹栈前回退该层造成的所有状态变化
            if (stk[top_ptr].is_dead) {
                dead_depth--;       // 退出一个死循环
            }
            if (stk[top_ptr].add_power) {
                current_power--;    // 退出一个 O(n) 循环
            }
            if (stk[top_ptr].claimed) {
                // 只有我成功占用了变量, 才需要在退出时释放
                unsigned char name = (unsigned char)stk[top_ptr].var[0];
                used_var[name] = false;
            }
            top_ptr--;  // 真正弹栈
        }
    }

    // 处理完所有行后, 如果栈非空 -> 有 F 没配对的 E
    if (top_ptr != 0) {
        has_error = true;
    }

    if (has_error) return -1;
    if (max_power == target_power) return 1;
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> test_cnt;
    while (test_cnt--) {
        int result = solve_one_case();
        if (result == -1) {
            cout << "ERR\n";
        } else if (result == 1) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }

    return 0;
}
