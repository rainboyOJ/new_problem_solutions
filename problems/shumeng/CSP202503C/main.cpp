/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:49
 */
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007LL;

struct Variable {
    int type;               // 0 未赋值(空串)  1 直接赋值(固定长度)  2 间接赋值(保存表达式)
    long long fixed_length; // type==1 时保存的值长度
    vector<string> expression; // type==2 时保存的操作数列表
};

map<string, int> variable_id;   // 变量名 -> 编号
vector<Variable> variables;     // 所有变量，编号从 0 开始
vector<long long> memo;         // 最近一次求值时该变量的长度缓存
vector<int> seen;               // 标记变量在哪一轮求值中被缓存
int evaluation_stamp = 0;       // 当前求值轮次的时间戳

// 获取变量编号，不存在则新建一个空变量
int get_variable_id(const string &name) {
    map<string, int>::iterator it = variable_id.find(name);
    if (it != variable_id.end()) return it->second;

    int id = (int)variables.size();
    Variable variable;
    variable.type = 0;
    variable.fixed_length = 0;
    variables.push_back(variable);
    variable_id[name] = id;
    memo.push_back(0);
    seen.push_back(0);
    return id;
}

// 求一个变量当前值的长度；同一轮求值内用时间戳缓存避免重复展开
long long evaluate_variable(int id) {
    if (seen[id] == evaluation_stamp) return memo[id];

    long long answer = 0;
    if (variables[id].type == 1) {
        // 直接赋值：长度固定
        answer = variables[id].fixed_length;
    } else if (variables[id].type == 2) {
        // 间接赋值：逐个展开操作数，$ 开头的操作数递归求对应变量
        for (int i = 0; i < (int)variables[id].expression.size(); i++) {
            string operand = variables[id].expression[i];
            if (!operand.empty() && operand[0] == '$') {
                answer += evaluate_variable(get_variable_id(operand.substr(1)));
            } else {
                answer += (long long)operand.size();
            }
            answer %= MOD;
        }
    }

    seen[id] = evaluation_stamp;
    memo[id] = answer;
    return answer;
}

// 求一个表达式的长度：普通字符串贡献字符数，$x 贡献变量 x 当前值的长度
long long evaluate_expression(const vector<string> &expression) {
    evaluation_stamp++;
    long long answer = 0;
    for (int i = 0; i < (int)expression.size(); i++) {
        const string &operand = expression[i];
        if (!operand.empty() && operand[0] == '$') {
            answer += evaluate_variable(get_variable_id(operand.substr(1)));
        } else {
            answer += (long long)operand.size();
        }
        answer %= MOD;
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    string line;
    getline(cin, line);

    for (int statement = 0; statement < n; statement++) {
        getline(cin, line);
        stringstream input(line);
        int operation;
        string name;
        input >> operation >> name;
        int id = get_variable_id(name);

        // 输出语句：打印该变量当前值的长度模 MOD
        if (operation == 3) {
            evaluation_stamp++;
            cout << evaluate_variable(id) << '\n';
            continue;
        }

        vector<string> expression;
        string operand;
        while (input >> operand) expression.push_back(operand);

        if (operation == 1) {
            // 直接赋值：立刻求值并保存固定长度
            long long value = evaluate_expression(expression);
            variables[id].type = 1;
            variables[id].fixed_length = value;
            variables[id].expression.clear();
        } else {
            // 间接赋值：只保存表达式，使用时再动态求值
            variables[id].type = 2;
            variables[id].expression = expression;
        }
    }

    return 0;
}
