import sys


def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    ptr = 0
    n, m = data[ptr], data[ptr + 1]
    ptr += 2
    weight = [0] * (n + 1)
    for i in range(1, n + 1):
        weight[i] = data[ptr]
        ptr += 1
    graph = [[] for _ in range(n + 1)]
    for _ in range(n - 1):
        u, v = data[ptr], data[ptr + 1]
        ptr += 2
        graph[u].append(v)
        graph[v].append(u)

    dfn_in = [0] * (n + 1)
    dfn_out = [0] * (n + 1)
    depth = [0] * (n + 1)
    timer = 0

    # 一次 DFS 求出进入时间戳、子树右端点与深度。
    # 判题器栈空间有限，用 (节点, 父亲, 状态) 的显式栈复现递归顺序：
    # 状态 0 表示刚进入节点，状态 1 表示孩子都处理完了、即将回溯。
    stack = [(1, 0, 0)]
    while stack:
        node, parent, state = stack.pop()
        if state == 0:
            timer += 1
            dfn_in[node] = timer
            depth[node] = depth[parent] + 1
            stack.append((node, parent, 1))
            for neighbor in graph[node]:
                if neighbor != parent:
                    stack.append((neighbor, node, 0))
        else:
            dfn_out[node] = timer  # 回溯时 timer 正好停在子树最后一个节点

    bit_const = [0] * (n + 2)  # 贡献中与查询点深度无关的部分
    bit_depth = [0] * (n + 2)  # 贡献中 depth[查询点] 的系数

    def add(tree, index, value):
        while index <= n:
            tree[index] += value
            index += index & -index

    def prefix_sum(tree, index):
        total = 0
        while index > 0:
            total += tree[index]
            index -= index & -index
        return total

    def range_add(tree, left, right, value):
        add(tree, left, value)
        add(tree, right + 1, -value)  # right + 1 超过 n 时 add 自然不执行

    # 初始权值等价于对每个点各做一次「操作 1」。
    for node in range(1, n + 1):
        range_add(bit_const, dfn_in[node], dfn_out[node], weight[node])

    answers = []
    for _ in range(m):
        operation = data[ptr]
        ptr += 1
        x = data[ptr]
        ptr += 1
        if operation == 3:
            # 与深度无关的增量 + depth[x] 乘上深度系数
            answers.append(
                str(prefix_sum(bit_const, dfn_in[x])
                    + depth[x] * prefix_sum(bit_depth, dfn_in[x]))
            )
            continue
        a = data[ptr]
        ptr += 1
        if operation == 1:
            # 节点 x 加 a：x 子树内每个查询点的路径和都正好多 a。
            range_add(bit_const, dfn_in[x], dfn_out[x], a)
        else:
            # 子树 x 加 a：子树内查询点 y 多出 a*(depth[y]-depth[x]+1)，
            # 拆成 a*depth[y] 与 a*(1-depth[x]) 两部分分别累计。
            range_add(bit_depth, dfn_in[x], dfn_out[x], a)
            range_add(bit_const, dfn_in[x], dfn_out[x], a * (1 - depth[x]))
    sys.stdout.write("\n".join(answers) + ("\n" if answers else ""))


if __name__ == "__main__":
    main()
