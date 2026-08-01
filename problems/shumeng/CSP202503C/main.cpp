/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-01 09:20
 */
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007LL;

struct Variable {
    int type;
    long long fixed_length;
    vector<string> expression;
};

map<string, int> variable_id;
vector<Variable> variables;
vector<long long> memo;
vector<int> seen;
int evaluation_stamp = 0;

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

long long evaluate_variable(int id) {
    if (seen[id] == evaluation_stamp) return memo[id];

    long long answer = 0;
    if (variables[id].type == 1) {
        answer = variables[id].fixed_length;
    } else if (variables[id].type == 2) {
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

        if (operation == 3) {
            evaluation_stamp++;
            cout << evaluate_variable(id) << '\n';
            continue;
        }

        vector<string> expression;
        string operand;
        while (input >> operand) expression.push_back(operand);

        if (operation == 1) {
            long long value = evaluate_expression(expression);
            variables[id].type = 1;
            variables[id].fixed_length = value;
            variables[id].expression.clear();
        } else {
            variables[id].type = 2;
            variables[id].expression = expression;
        }
    }

    return 0;
}
