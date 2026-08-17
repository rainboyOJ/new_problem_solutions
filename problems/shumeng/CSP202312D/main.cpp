/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:40
 */
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 998244353;
const int BLOCK_SIZE = 320;

// 2x2 矩阵
struct Matrix {
    long long a[2][2];
};

// 一条指令：type 1 头插，2 尾插，3 删除最晚插入的矩阵
struct Operation {
    int type;
    Matrix matrix;
};

// 一段插入序列聚合：front 为所有头插入按最终顺序的乘积，back 为所有尾插入的乘积
struct Aggregate {
    Matrix front;
    Matrix back;
};

// 一个分块的摘要：未匹配的删除个数 + 存活插入序列每个前缀的聚合
struct BlockSummary {
    int pop_count;
    vector<Aggregate> prefix;
};

// 分块栈中的一个元素：source 为分块编号（>=0）或单条指令（-index-1），length 为存活插入个数
struct ChunkState {
    int source;
    int length;
    Aggregate all; // 从栈底到当前元素的累计聚合
};

int n, event_count, block_count;
vector<Operation> operation;
vector<BlockSummary> block;
vector<ChunkState> chunk_stack;

Matrix identity_matrix() {
    Matrix result = {{{1, 0}, {0, 1}}};
    return result;
}

// 矩阵乘法，模 MOD
Matrix multiply(const Matrix &left, const Matrix &right) {
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

// 拼接两段插入序列：先出现 left 再出现 right。
// 头插入的最终顺序与出现顺序相反，尾插入的顺序相同。
Aggregate concatenate(const Aggregate &left, const Aggregate &right) {
    return {multiply(right.front, left.front), multiply(left.back, right.back)};
}

// 单条插入指令自身作为一个聚合
Aggregate operation_aggregate(int index) {
    Aggregate result = identity_aggregate();
    if (operation[index].type == 1) result.front = operation[index].matrix;
    if (operation[index].type == 2) result.back = operation[index].matrix;
    return result;
}

// 取一段长度为 length 的插入序列的聚合。
// source >= 0 表示分块编号，否则表示单条指令 -source-1。
Aggregate chunk_aggregate(int source, int length) {
    if (source >= 0) return block[source].prefix[length];
    if (length == 0) return identity_aggregate();
    return operation_aggregate(-source - 1);
}

// 重新扫描一个分块，生成其摘要：先抵消块内的删除，再对存活插入做前缀聚合
void rebuild_block(int id) {
    int left = id * BLOCK_SIZE;
    int right = min(n, left + BLOCK_SIZE);
    vector<int> push_operation; // 尚未被块内删除抵消的插入指令
    block[id].pop_count = 0;
    for (int i = left; i < right; i++) {
        if (operation[i].type == 3) {
            if (push_operation.empty()) block[id].pop_count++; // 未匹配删除
            else push_operation.pop_back();                    // 抵消最近一次插入
        } else {
            push_operation.push_back(i);
        }
    }

    // 对存活插入序列做前缀聚合
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

// 从分块栈顶弹出 count 个插入元素（模拟连续删除）
void pop_elements(int count) {
    while (count > 0 && !chunk_stack.empty()) {
        ChunkState &last = chunk_stack.back();
        if (last.length <= count) {
            count -= last.length;
            chunk_stack.pop_back();
        } else {
            // 只截断栈顶分块：用截断后的前缀聚合重算累计值
            last.length -= count;
            Aggregate before = chunk_stack.size() == 1
                ? identity_aggregate() : chunk_stack[chunk_stack.size() - 2].all;
            last.all = concatenate(before, chunk_aggregate(last.source, last.length));
            count = 0;
        }
    }
}

// 把一个完整分块压入栈，length 为它存活插入序列的长度
void append_chunk(int source, int length) {
    if (length == 0) return;
    Aggregate before = chunk_stack.empty() ? identity_aggregate() : chunk_stack.back().all;
    Aggregate current = chunk_aggregate(source, length);
    chunk_stack.push_back({source, length, concatenate(before, current)});
}

// 把单条指令作用到分块栈上
void apply_operation(int index) {
    if (operation[index].type == 3) {
        pop_elements(1);
    } else {
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

// 把整个分块作为摘要作用到栈上：先处理未匹配删除，再压入存活插入序列
void apply_block(int id) {
    pop_elements(block[id].pop_count);
    append_chunk(id, (int)block[id].prefix.size() - 1);
}

// 对区间 [left, right] 执行所有指令，返回最终队列矩阵乘积
Matrix query(int left, int right) {
    chunk_stack.clear();
    int index = left;
    while (index <= right) {
        int id = index / BLOCK_SIZE;
        int end = min(right, (id + 1) * BLOCK_SIZE - 1);
        // 完整块用摘要整体处理，边界块逐条执行
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

// 读入一条指令
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

    // 预处理每个分块的摘要
    block_count = (n + BLOCK_SIZE - 1) / BLOCK_SIZE;
    block.resize(block_count);
    for (int i = 0; i < block_count; i++) rebuild_block(i);

    while (event_count--) {
        int type;
        cin >> type;
        if (type == 1) {
            // 单点修改：更新指令并重建所在分块
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