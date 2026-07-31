/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 22:10
 */
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 998244353;
const int BLOCK_SIZE = 320;

struct Matrix {
    long long a[2][2];
};

struct Operation {
    int type;
    Matrix matrix;
};

struct Aggregate {
    Matrix front;
    Matrix back;
};

struct BlockSummary {
    int pop_count;
    vector<Aggregate> prefix;
};

struct ChunkState {
    int source;
    int length;
    Aggregate all;
};

int n, event_count, block_count;
vector<Operation> operation;
vector<BlockSummary> block;
vector<ChunkState> chunk_stack;

Matrix identity_matrix() {
    Matrix result = {{{1, 0}, {0, 1}}};
    return result;
}

inline Matrix multiply(const Matrix &left, const Matrix &right) {
    Matrix result;
    result.a[0][0] = (left.a[0][0] * right.a[0][0]
        + left.a[0][1] * right.a[1][0]) % MOD;
    result.a[0][1] = (left.a[0][0] * right.a[0][1]
        + left.a[0][1] * right.a[1][1]) % MOD;
    result.a[1][0] = (left.a[1][0] * right.a[0][0]
        + left.a[1][1] * right.a[1][0]) % MOD;
    result.a[1][1] = (left.a[1][0] * right.a[0][1]
        + left.a[1][1] * right.a[1][1]) % MOD;
    return result;
}

Aggregate identity_aggregate() {
    Matrix identity = identity_matrix();
    return {identity, identity};
}

Aggregate concatenate(const Aggregate &left, const Aggregate &right) {
    // 先出现 left，再出现 right；头插入的最终顺序正好相反。
    return {multiply(right.front, left.front), multiply(left.back, right.back)};
}

Aggregate operation_aggregate(int index) {
    Aggregate result = identity_aggregate();
    if (operation[index].type == 1) result.front = operation[index].matrix;
    if (operation[index].type == 2) result.back = operation[index].matrix;
    return result;
}

Aggregate chunk_aggregate(int source, int length) {
    if (source >= 0) return block[source].prefix[length];
    if (length == 0) return identity_aggregate();
    return operation_aggregate(-source - 1);
}

void rebuild_block(int id) {
    int left = id * BLOCK_SIZE;
    int right = min(n, left + BLOCK_SIZE);
    vector<int> push_operation;
    block[id].pop_count = 0;
    for (int i = left; i < right; i++) {
        if (operation[i].type == 3) {
            if (push_operation.empty()) block[id].pop_count++;
            else push_operation.pop_back();
        } else {
            push_operation.push_back(i);
        }
    }

    block[id].prefix.clear();
    block[id].prefix.resize(push_operation.size() + 1, identity_aggregate());
    for (int i = 0; i < (int)push_operation.size(); i++) {
        block[id].prefix[i + 1] = block[id].prefix[i];
        int index = push_operation[i];
        if (operation[index].type == 1) {
            block[id].prefix[i + 1].front = multiply(
                operation[index].matrix, block[id].prefix[i].front);
        } else {
            block[id].prefix[i + 1].back = multiply(
                block[id].prefix[i].back, operation[index].matrix);
        }
    }
}

void pop_elements(int count) {
    while (count > 0 && !chunk_stack.empty()) {
        ChunkState &last = chunk_stack.back();
        if (last.length <= count) {
            count -= last.length;
            chunk_stack.pop_back();
        } else {
            last.length -= count;
            Aggregate before = chunk_stack.size() == 1
                ? identity_aggregate() : chunk_stack[chunk_stack.size() - 2].all;
            last.all = concatenate(before, chunk_aggregate(last.source, last.length));
            count = 0;
        }
    }
}

void append_chunk(int source, int length) {
    if (length == 0) return;
    Aggregate before = chunk_stack.empty() ? identity_aggregate() : chunk_stack.back().all;
    Aggregate current = chunk_aggregate(source, length);
    chunk_stack.push_back({source, length, concatenate(before, current)});
}

void apply_operation(int index) {
    if (operation[index].type == 3) pop_elements(1);
    else {
        Aggregate before = chunk_stack.empty() ? identity_aggregate() : chunk_stack.back().all;
        Aggregate current = before;
        if (operation[index].type == 1) {
            current.front = multiply(operation[index].matrix, before.front);
        } else {
            current.back = multiply(before.back, operation[index].matrix);
        }
        chunk_stack.push_back({-index - 1, 1, current});
    }
}

void apply_block(int id) {
    pop_elements(block[id].pop_count);
    append_chunk(id, (int)block[id].prefix.size() - 1);
}

Matrix query(int left, int right) {
    chunk_stack.clear();
    int index = left;
    while (index <= right) {
        int id = index / BLOCK_SIZE;
        int end = min(right, (id + 1) * BLOCK_SIZE - 1);
        if (index == id * BLOCK_SIZE && end - index + 1 == BLOCK_SIZE) {
            apply_block(id);
        } else {
            for (int i = index; i <= end; i++) apply_operation(i);
        }
        index = end + 1;
    }
    if (chunk_stack.empty()) return identity_matrix();
    return multiply(chunk_stack.back().all.front, chunk_stack.back().all.back);
}

Operation read_operation() {
    Operation result;
    cin >> result.type;
    if (result.type == 1 || result.type == 2) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) cin >> result.matrix.a[i][j];
        }
    }
    return result;
}

void print_matrix(const Matrix &matrix) {
    cout << matrix.a[0][0] << ' ' << matrix.a[0][1] << ' '
         << matrix.a[1][0] << ' ' << matrix.a[1][1] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> event_count;
    operation.resize(n);
    for (int i = 0; i < n; i++) operation[i] = read_operation();

    block_count = (n + BLOCK_SIZE - 1) / BLOCK_SIZE;
    block.resize(block_count);
    for (int i = 0; i < block_count; i++) rebuild_block(i);

    while (event_count--) {
        int type;
        cin >> type;
        if (type == 1) {
            int index;
            cin >> index;
            operation[index - 1] = read_operation();
            rebuild_block((index - 1) / BLOCK_SIZE);
        } else {
            int left, right;
            cin >> left >> right;
            print_matrix(query(left - 1, right - 1));
        }
    }

    return 0;
}
