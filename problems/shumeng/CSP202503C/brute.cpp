/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-01 09:20
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007LL;

struct Variable {
    int type;
    long long length;
    vector<string> expression;
};

map<string, int> ids;
vector<Variable> variables;

int get_id(const string &name) {
    map<string, int>::iterator it = ids.find(name);
    if (it != ids.end()) return it->second;
    int id = (int)variables.size();
    Variable variable;
    variable.type = 0;
    variable.length = 0;
    variables.push_back(variable);
    ids[name] = id;
    return id;
}

long long evaluate(int id) {
    if (variables[id].type == 0) return 0;
    if (variables[id].type == 1) return variables[id].length;

    long long answer = 0;
    for (int i = 0; i < (int)variables[id].expression.size(); i++) {
        string operand = variables[id].expression[i];
        if (!operand.empty() && operand[0] == '$') {
            answer += evaluate(get_id(operand.substr(1)));
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
        int id = get_id(name);
        if (operation == 3) {
            cout << evaluate(id) << '\n';
            continue;
        }

        vector<string> expression;
        string operand;
        while (input >> operand) expression.push_back(operand);
        if (operation == 1) {
            long long value = 0;
            for (int i = 0; i < (int)expression.size(); i++) {
                if (!expression[i].empty() && expression[i][0] == '$') {
                    value += evaluate(get_id(expression[i].substr(1)));
                } else {
                    value += (long long)expression[i].size();
                }
                value %= MOD;
            }
            variables[id].type = 1;
            variables[id].length = value;
            variables[id].expression.clear();
        } else {
            variables[id].type = 2;
            variables[id].expression = expression;
        }
    }
    return 0;
}
