//Author by [Rainboy](https://github.com/rainboylvx)
//date: 2024-07-23 09:44:20

/**
 * ============================================================
 * 题目: P3952 [NOIP 2017 提高组] 时间复杂度
 * ============================================================
 * 核心任务: 判断小明给出的"时间复杂度"是否正确
 *
 * 【A++ 循环语法】
 *   F i x y    // 新建变量 i = x, 当 i <= y 时进入循环, 每次 i++
 *     循环体
 *   E          // 循环结束, 变量 i 被销毁
 *
 * 【时间复杂度的计算规则】
 *   我们把每一层循环对复杂度的贡献看作 "n 的指数":
 *   - 数字 -> 数字 (x <= y): 循环执行常数次, 贡献指数 0
 *   - 数字 -> 数字 (x > y) : 循环不执行, 贡献指数 0
 *   - 数字 -> n            : 循环执行约 n 次, 贡献指数 1
 *   - n -> 数字            : n 远大于数字, 循环不执行, 贡献指数 0
 *   - n -> n               : 循环执行常数次, 贡献指数 0
 *
 *   嵌套循环的总指数 = 各层指数之和 (栈顶存的就是当前嵌套深度的总指数)
 *
 * 【ERR 语法错误】
 *   ① F 和 E 不匹配 (括号不匹配)
 *   ② 变量名与已存在且未被销毁的变量重复
 *   注意: 即使循环不会执行, 里面的语法错误也要报 ERR!
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
int n,m;
string s;
int T;                          // 数据组数

int max_time  = 0;              // 当前程序实际的最大时间复杂度指数
bool err_flag = 0;              // 标记是否发现语法错误
int read_line_cnt = 0;          // 当前程序还剩多少行没读

/**
 * 【手工栈 my_sta】
 * 为什么用栈? 循环允许嵌套, 后进先出(F 是入栈, E 是出栈)
 * 栈中每个元素存储: "从外层到当前层, 累计贡献的 n 的指数"
 * 例如: 第一层贡献 1, 第二层贡献 1, 栈顶就是 2 (表示当前在 n^2 的循环内)
 */
struct my_sta {
    int a[maxn];    // 栈的底层数组
    int idx = 0;    // 栈顶指针(同时表示栈的大小)

    void clear() { idx = 0;}                // 清空栈
    void push(int v) { a[idx++] = v;}       // 压栈: 当前层总指数 = v
    void pop() {--idx;}                     // 弹栈: 当前循环结束
    int size() {return idx;}                // 栈中元素个数
    bool empty() { return idx == 0;}        // 判空
    int top() { return a[idx-1];}           // 取栈顶(当前嵌套深度的总指数)
    int atop() {
        if( empty() ) return 0;             // 空栈说明没有外层循环, 指数为 0
        return top();
    }
} sta;

/**
 * 【变量名池 bct】
 * 作用: 记录当前所有"活着"的变量名, 用于检测变量名重复
 * 规则: 进入一个 F 就把变量名加入数组, 遇到 E 就把当前层变量名移除
 * 为什么不直接 map/set? 题目数据量小(L<=100), 数组遍历就够用了
 */
int cnt;                        // 当前活着的变量个数
string bct[maxn];               // 活着的变量名列表

void push_str(const string &s ) {
    bct[cnt++] = s;             // 新变量加入"存活名单"
}
void pop_str() {
    cnt--;                      // 最内层循环结束, 对应变量"销毁"
}
bool find_str(const string & s) {
    // 遍历当前所有存活变量, 看名字 s 是否已被占用
    for(int i = 0;i < cnt ;++i )
    {
        if( bct[i] == s) return 1;  // 找到重复, 返回 true
    }
    return 0;                       // 没找到, 名字可用
}


bool with_n = 0;                // 小明声称的复杂度是否包含 n (O(n^w) 为 1, O(1) 为 0)
int _time;                      // 小明声称的指数 w (O(1) 时为 0)

/**
 * 【解析小明声称的复杂度】
 * 输入样例: "O(1)" 或 "O(n^2)"
 * 目标: 提取出 with_n(是否含n) 和 _time(指数是多少)
 */
void time_complex(){
    cin >> s;
    int l = s.length();
    with_n = 0;
    _time = 0;

    // 第一遍扫描: 看字符串里有没有字母 'n'
    for(int i =0; i < l;i++)
        if(s[i] == 'n') {
            with_n = 1;         // 说明是 O(n^w) 形式
            break;
        }

    // 第二遍扫描: 提取数字 (连续的), 就是指数 w
    for(int i =0; i < l;i++)
    {
        if( s[i] >='0' && s[i] <= '9' )
        {
            int t = s[i] - '0';
            _time *= 10;
            _time += t;
        }
    }
    // 如果输入是 O(1), 上面提取不到数字, _time 保持 0, with_n 也是 0
}

/**
 * 【把字符串解析成数字, 或识别为 n】
 * 返回值:
 *   -1  -> 字符串是 "n"
 *   >=0 -> 字符串表示的正整数
 */
int get_n_number(const string & s) {
    if( s[0] == 'n') return -1;     // 特殊标记: 这个是 n, 不是数字
    int n = 0;
    for(int i = 0 ;i< s.length() ;i++) {
        n *=10;
        n += s[i] -'0';
    }
    return n;
}


/**
 * 【快速跳过一段"不执行的循环体"】
 * 什么时候用? 当发现循环条件满足 "n -> 数字" 时, 循环不会执行。
 * 虽然循环不执行, 但输入里对应的 F...E 还是要读完, 否则后面的数据会错位。
 * 方法: 用 e_cnt 计数, F 使计数+1, E 使计数-1, 计数回到 1 时跳出。
 * (进来时已经读了 1 个 F, 所以初始 e_cnt=1)
 */
void read_until_e() {
    int e_cnt = 1;              // 当前还有 e_cnt 层循环没配对
    string var ,x,y;
    while(1) {
        cin >> var;
        if( var == "E") {
            read_line_cnt--;    // 消耗一行
            if( e_cnt == 1) break;  // 正好配对到当前这层的 E
            e_cnt--;            // 是内层循环的 E
        }
        else { // 只可能是 for (F)
            cin >> var >> x >> y;
            read_line_cnt--;    // 消耗一行
            e_cnt++;            // 又嵌套了一层
        }
    }
}


/**
 * 【处理一行 F i x y】
 * 这是整个题目的核心逻辑:
 * 1. 读取变量名 var, 起点 s, 终点 t
 * 2. 检查变量名是否重复 (语法错误②)
 * 3. 根据 x,y 的类型判断循环是否贡献指数
 * 4. 维护栈和 max_time
 */
void deal_f() {
    string var,s,t;
    cin >> var >> s >> t;       // 读入: 变量名, 起点, 终点

    int x = get_n_number(s);    // x: 起点对应的数值, -1 表示 n
    int y = get_n_number(t);    // y: 终点对应的数值, -1 表示 n

    // === 语法检查: 变量名是否与已存活的变量重复 ===
    bool _find = find_str(var);
    if( _find ) {
        err_flag = 1;           // 发现重复变量, 标记错误
    }

    // k = 当前外层循环贡献的总指数 (栈顶)
    int k = sta.atop();

    /**
     * 【情况分类讨论】
     * 用 x,y 是否为 -1(即 n) 来分类:
     */

    if( x == -1 && y == -1) {
        // === 情况1: n -> n ===
        // n 到 n, 只执行 1 次, 常数级别, 指数不增加
        push_str(var);          // 变量加入存活名单
        sta.push(k + 0);        // 总指数 = 外层指数 + 0
    }
    else if( x !=-1 && y != -1 ){
        // === 情况2: 数字 -> 数字 ===
        // 无论 x <= y 还是 x > y, 对复杂度指数的贡献都是 0
        // (x>y 时不进入循环, x<=y 时常数次循环)
        push_str(var);
        sta.push(0 + k);        // 总指数不变
    }
    else {
        // === 情况3: 有一个是 n ===
        if( x == -1) {
            // === 情况3a: n -> 数字 ===
            // n 远大于任何输入数字, 所以循环条件一开始就不成立
            // 循环体**一次都不执行**
            // 因为不执行, 当前这层不需要入栈, 但要跳过整个循环体
            read_until_e();     // 把对应的 F...E 全部读完
        }
        else{
            // === 情况3b: 数字 -> n ===
            // 循环约执行 n 次, 贡献指数 +1
            push_str(var);
            sta.push(1 + k);    // 总指数 = 外层指数 + 1
        }
    }

    // 更新当前程序的最大指数 (用于和声称的复杂度比较)
    max_time = max(max_time,sta.atop());
}

/**
 * 【处理一行 E】
 * E 表示最内层循环结束:
 * - 弹栈 (该层对复杂度的贡献结束)
 * - 销毁该层对应的变量名
 */
void deal_e() {
    if( sta.empty()) {
        // 栈已经空了, 却来了个 E -> F 和 E 不匹配 (语法错误①)
        err_flag = 1;
    }
    else {
        sta.pop();              // 弹出当前层复杂度指数
        pop_str();              // 销毁当前层变量
    }
}

/**
 * 【读取并处理一个完整的程序】
 * 流程:
 * 1. 读 L (行数) 和声称的复杂度
 * 2. 逐行读取 F 或 E, 调用对应处理函数
 * 3. 读完所有行后检查栈是否为空 (F 和 E 是否完全匹配)
 * 4. 输出 Yes / No / ERR
 */
void read_one_data() {
    cin >> n;
    read_line_cnt = n;          // 这个程序共有 n 行

    time_complex();             // 解析声称的复杂度 -> with_n, _time

    while( read_line_cnt > 0)   // 逐行处理
    {
        read_line_cnt--;
        cin >> s;
        if( s[0] == 'F') {
            deal_f();           // 进入循环
        }
        else if( s[0] == 'E') {
            deal_e();           // 退出循环
        }
    }

    // 处理完后, 如果栈非空 -> 有 F 没配对的 E, 语法错误①
    if( !sta.empty()) err_flag = 1;

    // === 输出结果 ===
    if( err_flag ) {
        cout << "ERR\n";        // 只要有语法错误, 不管复杂度对不对都输出 ERR
    }
    else {
        // 比较实际复杂度 max_time 和声称复杂度 _time
        if( max_time ==  0 && with_n == 0) {
            // 实际 O(1), 声称 O(1) -> Yes
            std::cout << "Yes"<< "\n";
        }
        else if( max_time != 0 && with_n == 1 ) {
            // 实际含 n, 声称也含 n, 比较指数是否相等
            if( max_time == _time )
                std::cout << "Yes"<< "\n";
            else
                std::cout << "No"<< "\n";
        }
        else {
            // 一个 O(1) 一个 O(n^w), 肯定不一样
            std::cout << "No"<< "\n";
        }
    }
}

int main (int argc, char *argv[]) {
    std::cin >> T;
    while (T--) {
        // 每组数据前, 重置所有全局状态!
        sta.clear();            // 清空栈
        max_time = 0;           // 最大指数归零
        err_flag = 0;           // 错误标记归零
        cnt=0;                  // 存活变量数归零
        read_line_cnt = 0;      // 剩余行数归零
        read_one_data();
    }

    return 0;
}
