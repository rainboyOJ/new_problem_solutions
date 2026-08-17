/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:39
 */
#include <bits/stdc++.h>
using namespace std;

class FastInput {
private:
    static const int BUFFER_SIZE = 1 << 20;
    int position;
    int length;
    char buffer[BUFFER_SIZE];

    char get_char() {
        if (position == length) {
            length = (int)fread(buffer, 1, BUFFER_SIZE, stdin);
            position = 0;
            if (length == 0) return 0;
        }
        return buffer[position++];
    }

public:
    FastInput() : position(0), length(0) {}

    long long read_long_long() {
        char current = get_char();
        while (current <= ' ' && current != 0) current = get_char();

        long long value = 0;
        while (current >= '0' && current <= '9') {
            value = value * 10 + current - '0';
            current = get_char();
        }
        return value;
    }
};

struct Interval {
    int left;
    int right;
    long long value;
};

struct StackNode {
    int right;
    long long maximum;
};

int n;
vector<long long> base_a;
vector<long long> base_b;
vector<long long> a;
vector<long long> b;
vector<long long> prefix_b;
vector<int> previous_ge;
vector<int> next_ge;
vector<Interval> intervals;
vector<int> order_by_right;
vector<int> order_by_left;
vector<int> counter;
vector<StackNode> interval_stack;

void build_nearest_greater() {
    vector<int> stack;
    stack.reserve(n);

    for (int i = 1; i <= n; i++) {
        while (!stack.empty() && a[stack.back()] < a[i]) {
            stack.pop_back();
        }
        if (stack.empty()) previous_ge[i] = 0;
        else previous_ge[i] = stack.back();
        stack.push_back(i);
    }

    stack.clear();
    for (int i = n; i >= 1; i--) {
        while (!stack.empty() && a[stack.back()] < a[i]) {
            stack.pop_back();
        }
        if (stack.empty()) next_ge[i] = n + 1;
        else next_ge[i] = stack.back();
        stack.push_back(i);
    }
}

void build_intervals() {
    intervals.clear();
    intervals.reserve(2 * n);

    for (int i = 1; i <= n; i++) {
        int left = previous_ge[i];
        int right = i - 1;
        if (left < 1) left = 1;
        if (left <= right) {
            long long value = a[i] - (prefix_b[i - 1] - prefix_b[previous_ge[i]]);
            Interval current;
            current.left = left;
            current.right = right;
            current.value = value;
            intervals.push_back(current);
        }

        left = i;
        right = next_ge[i] - 1;
        if (right > n - 1) right = n - 1;
        if (left <= right) {
            long long value = a[i] - (prefix_b[next_ge[i] - 1] - prefix_b[i]);
            Interval current;
            current.left = left;
            current.right = right;
            current.value = value;
            intervals.push_back(current);
        }
    }
}

void sort_intervals() {
    int interval_count = (int)intervals.size();
    order_by_right.resize(interval_count);
    order_by_left.resize(interval_count);

    fill(counter.begin(), counter.end(), 0);
    for (int i = 0; i < interval_count; i++) {
        counter[intervals[i].right]++;
    }

    int position = 0;
    for (int right = n - 1; right >= 1; right--) {
        int count = counter[right];
        counter[right] = position;
        position += count;
    }
    for (int i = 0; i < interval_count; i++) {
        int right = intervals[i].right;
        order_by_right[counter[right]++] = i;
    }

    fill(counter.begin(), counter.end(), 0);
    for (int i = 0; i < interval_count; i++) {
        counter[intervals[order_by_right[i]].left]++;
    }

    position = 0;
    for (int left = 1; left <= n - 1; left++) {
        int count = counter[left];
        counter[left] = position;
        position += count;
    }
    for (int i = 0; i < interval_count; i++) {
        int id = order_by_right[i];
        int left = intervals[id].left;
        order_by_left[counter[left]++] = id;
    }
}

long long calculate_answer() {
    prefix_b[0] = 0;
    for (int i = 1; i <= n; i++) {
        prefix_b[i] = prefix_b[i - 1] + b[i];
    }

    build_nearest_greater();
    build_intervals();
    sort_intervals();

    interval_stack.clear();
    interval_stack.reserve(intervals.size());
    long long answer = 0;
    int interval_count = (int)intervals.size();
    int current_interval = 0;

    for (int split = 1; split <= n - 1; split++) {
        while (!interval_stack.empty() && interval_stack.back().right < split) {
            interval_stack.pop_back();
        }

        while (current_interval < interval_count) {
            int id = order_by_left[current_interval];
            if (intervals[id].left != split) break;

            long long maximum = intervals[id].value;
            if (!interval_stack.empty() && interval_stack.back().maximum > maximum) {
                maximum = interval_stack.back().maximum;
            }
            StackNode node;
            node.right = intervals[id].right;
            node.maximum = maximum;
            interval_stack.push_back(node);
            current_interval++;
        }

        long long value = interval_stack.back().maximum;
        answer ^= value;
    }
    return answer;
}

int main() {
    FastInput input;

    n = (int)input.read_long_long();
    base_a.assign(n + 2, 0);
    base_b.assign(n + 2, 0);
    a.assign(n + 2, 0);
    b.assign(n + 2, 0);
    prefix_b.assign(n + 2, 0);
    previous_ge.assign(n + 2, 0);
    next_ge.assign(n + 2, n + 1);
    counter.assign(n + 2, 0);

    for (int i = 1; i <= n; i++) base_a[i] = input.read_long_long();
    for (int i = 1; i <= n; i++) base_b[i] = input.read_long_long();

    int q = (int)input.read_long_long();
    for (int query = 0; query < q; query++) {
        a = base_a;
        b = base_b;

        int changed = (int)input.read_long_long();
        for (int i = 0; i < changed; i++) {
            int position = (int)input.read_long_long();
            a[position] = input.read_long_long();
            b[position] = input.read_long_long();
        }

        long long answer = calculate_answer();
        printf("%lld\n", answer);
    }

    return 0;
}
