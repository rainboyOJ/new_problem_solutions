import sys


def main():
    values = list(map(int, sys.stdin.buffer.read().split()))
    n = values[0]
    q = values[1]
    graph = [[] for _ in range(n + 1)]
    pos = 2
    for _ in range(n - 1):
        u = values[pos]
        v = values[pos + 1]
        pos += 2
        graph[u].append(v)
        graph[v].append(u)

    # 一遍 DFS 同时求两个序：dfn 是进入序（正着编号），rdfn 是退出序的逆序。
    # 用显式栈是因为 Python 默认递归深度只有 1000，1e5 的链会直接崩。
    dfn = [0] * (n + 1)
    rdfn = [0] * (n + 1)
    node_at = [0] * (n + 1)
    enter = 0
    leave = 0
    stack = [(1, 0, 0)]  # (节点, 父亲, 状态)，状态 0 表示进入，1 表示退出
    while stack:
        u, parent, state = stack.pop()
        if state == 0:
            enter += 1
            dfn[u] = enter
            node_at[enter] = u
            stack.append((u, parent, 1))
            for v in graph[u]:
                if v != parent:
                    stack.append((v, u, 0))
        else:
            leave += 1
            rdfn[u] = n - leave + 1

    size = 1
    while size < n:
        size <<= 1
    infinity = n + 1
    tree = [infinity] * (2 * size)  # 黑点叶子存 rdfn，白点叶子存无穷大
    black = bytearray(n + 1)        # black[u]：节点 u 当前是否为黑点

    answers = []
    for i in range(pos, len(values), 2):
        op = values[i]
        x = values[i + 1]
        if op == 0:
            # 单点取反：叶子在 rdfn 与无穷大之间切换，然后向上合并区间最小值
            black[x] ^= 1
            p = size + dfn[x] - 1
            tree[p] = rdfn[x] if black[x] else infinity
            p >>= 1
            while p:
                left = tree[p << 1]
                right = tree[p << 1 | 1]
                value = left if left < right else right
                if tree[p] == value:
                    break
                tree[p] = value
                p >>= 1
        else:
            # 线段树二分：找最小的下标，使它的叶子值不超过 rdfn[x]
            limit = rdfn[x]
            if tree[1] > limit:
                answers.append("-1")
                continue
            p = 1
            left = 1
            right = size
            while left < right:
                mid = (left + right) >> 1
                if tree[p << 1] <= limit:
                    p <<= 1
                    right = mid
                else:
                    p = p << 1 | 1
                    left = mid + 1
            answers.append("-1" if left > dfn[x] else str(node_at[left]))
    sys.stdout.write("\n".join(answers) + ("\n" if answers else ""))


main()
