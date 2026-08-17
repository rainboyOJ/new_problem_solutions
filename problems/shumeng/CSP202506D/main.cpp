/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:57
 */
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 998244353LL;
const int PREFIX_COUNT = 7;   // 自动机状态数：空串及 c,cc,cs,csp,cspa,cspar 六个前缀
const int STATUS_COUNT = 4;   // 全局顺序状态数：未出现/已现ccf/已现cspark/已满足
const int SMALL_LIMIT = 100000; // 直接递推预计算的长度上限

// next_state[状态][字符]：加入字符后的新状态
int next_state[PREFIX_COUNT][26];
// output_mask[状态][字符]：本次转移是否产生 ccf(1) / cspark(2)
int output_mask[PREFIX_COUNT][26];
string prefixes[PREFIX_COUNT] = {"", "c", "cc", "cs", "csp", "cspa", "cspar"};

long long normalize(long long value) {
    value %= MOD;
    if (value < 0) value += MOD;
    return value;
}

long long power_mod(long long base, long long exponent) {
    long long answer = 1;
    base %= MOD;
    while (exponent > 0) {
        if (exponent & 1) answer = answer * base % MOD;
        base = base * base % MOD;
        exponent >>= 1;
    }
    return answer;
}

// 构造前缀自动机：转移后更新最长可匹配前缀，并记录本次是否产生了完整模式
void build_automaton() {
    for (int state = 0; state < PREFIX_COUNT; state++) {
        for (int ch = 0; ch < 26; ch++) {
            char character = (char)('a' + ch);
            string text = prefixes[state] + character;
            int mask = 0;
            if (text.size() >= 3 && text.substr(text.size() - 3) == "ccf") {
                mask |= 1;
            }
            if (text.size() >= 6 && text.substr(text.size() - 6) == "cspark") {
                mask |= 2;
            }
            int best = 0;
            for (int candidate = 1; candidate < PREFIX_COUNT; candidate++) {
                if (prefixes[candidate].size() <= text.size() &&
                    text.substr(text.size() - prefixes[candidate].size()) ==
                    prefixes[candidate] &&
                    prefixes[candidate].size() > prefixes[best].size()) {
                    best = candidate;
                }
            }
            next_state[state][ch] = best;
            output_mask[state][ch] = mask;
        }
    }
}

// 多项式取模乘法：a,b 是次数小于 degree 的多项式，按 characteristic 的递推关系降次
vector<long long> multiply_polynomial(const vector<long long> &a,
    const vector<long long> &b, const vector<long long> &characteristic) {
    int degree = (int)characteristic.size() - 1;
    vector<long long> temp(2 * degree - 1, 0);
    for (int i = 0; i < degree; i++) {
        for (int j = 0; j < degree; j++) {
            temp[i + j] = (temp[i + j] + a[i] * b[j]) % MOD;
        }
    }
    for (int i = 2 * degree - 2; i >= degree; i--) {
        long long coefficient = temp[i];
        if (coefficient == 0) continue;
        for (int j = 1; j <= degree; j++) {
            temp[i - j] = normalize(temp[i - j] -
                coefficient * characteristic[j]);
        }
    }
    temp.resize(degree);
    return temp;
}

// Kitamasa 算法：在线性递推 characteristic 下求第 index 项（index 从 0 开始）
long long linear_term(long long index, const vector<long long> &initial,
    const vector<long long> &characteristic) {
    int degree = (int)characteristic.size() - 1;
    if (index < degree) return initial[index];
    vector<long long> result(degree, 0);
    vector<long long> base(degree, 0);
    result[0] = 1;
    if (degree == 1) base[0] = normalize(-characteristic[1]);
    else base[1] = 1;
    while (index > 0) {
        if (index & 1) result = multiply_polynomial(result, base, characteristic);
        base = multiply_polynomial(base, base, characteristic);
        index >>= 1;
    }
    long long answer = 0;
    for (int i = 0; i < degree; i++) {
        answer = (answer + result[i] * initial[i]) % MOD;
    }
    return answer;
}

// 预计算前 SMALL_LIMIT 项：no_ccf/no_both/no_spark/safe_order
// 分别是不含ccf、不含两者、不含cspark、段内不先ccf后cspark 的字符串计数
void make_small_sequences(vector<long long> &no_ccf, vector<long long> &no_both,
    vector<long long> &no_spark, vector<long long> &safe_order) {
    no_ccf.assign(SMALL_LIMIT + 1, 0);
    no_both.assign(SMALL_LIMIT + 1, 0);
    no_spark.assign(SMALL_LIMIT + 1, 0);
    safe_order.assign(SMALL_LIMIT + 1, 0);
    vector<long long> state_ccf(PREFIX_COUNT, 0);
    vector<long long> state_both(PREFIX_COUNT, 0);
    vector<long long> state_spark(PREFIX_COUNT, 0);
    vector<long long> state_order(PREFIX_COUNT * STATUS_COUNT, 0);
    state_ccf[0] = 1;
    state_both[0] = 1;
    state_spark[0] = 1;
    state_order[0] = 1;
    no_ccf[0] = 1;
    no_both[0] = 1;
    no_spark[0] = 1;
    safe_order[0] = 1;

    for (int length = 0; length < SMALL_LIMIT; length++) {
        vector<long long> next_ccf(PREFIX_COUNT, 0);
        vector<long long> next_both(PREFIX_COUNT, 0);
        vector<long long> next_spark(PREFIX_COUNT, 0);
        vector<long long> next_order(PREFIX_COUNT * STATUS_COUNT, 0);
        for (int state = 0; state < PREFIX_COUNT; state++) {
            for (int ch = 0; ch < 26; ch++) {
                int next = next_state[state][ch];
                int mask = output_mask[state][ch];
                if (mask == 0) {
                    next_both[next] = (next_both[next] + state_both[state]) % MOD;
                }
                if ((mask & 1) == 0) {
                    next_ccf[next] = (next_ccf[next] + state_ccf[state]) % MOD;
                }
                if ((mask & 2) == 0) {
                    next_spark[next] = (next_spark[next] + state_spark[state]) % MOD;
                }
                for (int status = 0; status < STATUS_COUNT; status++) {
                    int new_status = status;
                    if (mask & 1) {
                        if (status == 0) new_status = 2;
                        else if (status == 1) new_status = 3;
                    }
                    if (mask & 2) {
                        if (status >= 2) continue;
                        new_status = 1;
                    }
                    int old_index = state * STATUS_COUNT + status;
                    int new_index = next * STATUS_COUNT + new_status;
                    next_order[new_index] = (next_order[new_index] +
                        state_order[old_index]) % MOD;
                }
            }
        }
        state_ccf.swap(next_ccf);
        state_both.swap(next_both);
        state_spark.swap(next_spark);
        state_order.swap(next_order);
        for (int state = 0; state < PREFIX_COUNT; state++) {
            no_ccf[length + 1] = (no_ccf[length + 1] + state_ccf[state]) % MOD;
            no_both[length + 1] = (no_both[length + 1] + state_both[state]) % MOD;
            no_spark[length + 1] = (no_spark[length + 1] + state_spark[state]) % MOD;
        }
        for (int state = 0; state < PREFIX_COUNT * STATUS_COUNT; state++) {
            safe_order[length + 1] = (safe_order[length + 1] + state_order[state]) % MOD;
        }
    }
}

long long get_sequence_value(long long length, const vector<long long> &small,
    const vector<long long> &characteristic) {
    if (length <= SMALL_LIMIT) return small[(int)length];
    vector<long long> initial(characteristic.size() - 1, 0);
    for (int i = 0; i < (int)initial.size(); i++) initial[i] = small[i];
    return linear_term(length, initial, characteristic);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, fixed_count;
    cin >> n >> fixed_count;
    vector<int> fixed_position(fixed_count);
    for (int i = 0; i < fixed_count; i++) cin >> fixed_position[i];

    build_automaton();
    vector<long long> no_ccf, no_both, no_spark, safe_order;
    make_small_sequences(no_ccf, no_both, no_spark, safe_order);

    vector<long long> characteristic_ccf = {1, MOD - 26, 0, 1};
    vector<long long> characteristic_both = {1, MOD - 26, 0, 1, 0, 0, 1};
    vector<long long> characteristic_spark = {1, MOD - 26, 0, 0, 0, 0, 1};
    vector<long long> characteristic_order = {
        1, MOD - 52, 676, 1, MOD - 26, 0, 1, MOD - 26, 0, 1
    };

    // 全局状态：0 尚未出现 ccf，1 已出现 ccf 尚未满足，2 已满足条件
    long long status[3] = {1, 0, 0};
    long long current_position = 1;
    for (int i = 0; i < fixed_count; i++) {
        // 处理 # 之前的自由段 [current_position, fixed_position[i]-1]
        long long length = fixed_position[i] - current_position;
        long long count_ccf = get_sequence_value(length, no_ccf, characteristic_ccf);
        long long count_spark = get_sequence_value(length, no_spark, characteristic_spark);
        long long count_safe = get_sequence_value(length, safe_order, characteristic_order);
        long long total = power_mod(26, length);
        long long next_status[3];
        next_status[0] = status[0] * count_ccf % MOD;
        next_status[1] = (status[1] * count_spark + status[0] *
            normalize(count_safe - count_ccf)) % MOD;
        next_status[2] = (status[2] * total + status[1] *
            normalize(total - count_spark) + status[0] *
            normalize(total - count_safe)) % MOD;
        for (int j = 0; j < 3; j++) status[j] = next_status[j];
        current_position = fixed_position[i] + 1;
    }

    // 处理最后一个 # 之后的剩余自由段
    long long length = (long long)n - current_position + 1;
    long long count_ccf = get_sequence_value(length, no_ccf, characteristic_ccf);
    long long count_spark = get_sequence_value(length, no_spark, characteristic_spark);
    long long count_safe = get_sequence_value(length, safe_order, characteristic_order);
    long long total = power_mod(26, length);
    long long next_status[3];
    next_status[0] = status[0] * count_ccf % MOD;
    next_status[1] = (status[1] * count_spark + status[0] *
        normalize(count_safe - count_ccf)) % MOD;
    next_status[2] = (status[2] * total + status[1] *
        normalize(total - count_spark) + status[0] *
        normalize(total - count_safe)) % MOD;
    cout << normalize(next_status[2]) << '\n';
    return 0;
}
