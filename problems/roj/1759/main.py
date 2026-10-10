#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 22:29
# update_at: 2026-10-07 22:29

import sys
from typing import BinaryIO

LOGN = 18  # n <= 2e5 < 2^18，倍增表跳 0..2^17 步就够（深度差最大 199999）

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type UpTable = list[list[int]]   # 倍增祖先表：up[j][u] 是 u 往上跳 2^j 步的祖先
type Kids = list[list[int]]      # 孩子表：kids[u] 是 u 的所有儿子
type Forest = tuple[list[int], list[int], list[int], UpTable]  # (父亲, 深度, 树根, 倍增表)


def read_entity(fin: BinaryIO) -> list[int]:
    """读一个实体的完整数字：第 0 个是元素个数，后面是元素本身。

    题面保证每个实体占一行，整行切分最快（一次 read().split() 要给本题顶格点的
    440 万个 token 逐个建对象、实测 268 MB，超过 128 MB 内存限制）；
    万一某行被换行截断，就继续读下一行补齐。
    """
    nums = list(map(int, fin.readline().split()))
    size = nums[0]
    while len(nums) < size + 1:
        nums += map(int, fin.readline().split())
    return nums


def lca(a: int, b: int, dep: list[int], up: UpTable) -> int:
    """求森林中同树两点的最近公共祖先（调用方保证 a、b 在同一棵树里）。"""
    if dep[a] < dep[b]:
        a, b = b, a
    diff = dep[a] - dep[b]
    j = 0
    while diff:  # 先把 a 抬到与 b 同深度
        if diff & 1:
            a = up[j][a]
        diff >>= 1
        j += 1
    if a == b:
        return a
    for j in range(LOGN - 1, -1, -1):  # 两点一起往上跳，停在 LCA 的两个儿子上
        row = up[j]
        if row[a] != row[b]:
            a, b = row[a], row[b]
    return up[0][a]


def build_forest(fin: BinaryIO, n: int) -> Forest:
    """读入 n 份名单，建出管辖森林，返回 (父亲, 深度, 树根, 倍增表)。

    由 S_i = {i} ∪ (⋂_{k∈B_i} S_k) 得 parent(i) = B_i 全部点的集合 LCA：
    B_i 的点同树时新点挂在集合 LCA 下面，B_i 为空或点分属不同树（交集为空）时
    i 自成一棵新树的根。B_i 的元素都小于 i，按 i 递增建树时它们已经就位，
    新点只会作为叶子挂上去，已有点的祖先关系不变，所以倍增表可以同步建好。
    """
    par = [0] * (n + 1)
    dep = [0] * (n + 1)
    root = [0] * (n + 1)
    up: UpTable = [[0] * (n + 1) for _ in range(LOGN)]
    for i in range(1, n + 1):
        line = read_entity(fin)
        size = line[0]
        cur = 0           # B_i 中已合并部分的集合 LCA
        cross = False     # B_i 的点是否分属不同树
        for j in range(1, size + 1):
            k = line[j]
            if j == 1:
                cur = k
            elif not cross:
                if root[k] != root[cur]:
                    cross = True  # 交集为空，i 只能自成一棵新树
                else:
                    cur = lca(cur, k, dep, up)  # 集合 LCA 只能相邻两点逐个合并
        if size and not cross:  # S_i = {i} ∪ (根 -> LCA(B_i) 的路径)
            par[i] = cur
            dep[i] = dep[cur] + 1
            root[i] = root[cur]
        else:                   # S_i = {i}
            root[i] = i
        up[0][i] = par[i]
        for j in range(1, LOGN):
            up[j][i] = up[j - 1][up[j - 1][i]]
    return par, dep, root, up


def assign_dfn(par: list[int], n: int) -> list[int]:
    """做一次真正的 DFS，求先序编号 dfn：同一棵子树内的点编号连续。

    按 i 递增建树的次序不是合法 DFS 序（父亲 2 的儿子 4 会因为 4 > 3 排在叔伯 3 后面），
    而虚树恒等式要求"同树的点排序后连成一段"，所以这里必须重新 DFS 一次。
    """
    kids: Kids = [[] for _ in range(n + 1)]
    for i in range(2, n + 1):
        if par[i]:
            kids[par[i]].append(i)
    dfn = [0] * (n + 1)
    timer = 0
    for r in range(1, n + 1):
        if par[r]:
            continue
        stack = [r]
        while stack:
            u = stack.pop()
            timer += 1
            dfn[u] = timer
            stack.extend(kids[u])  # 儿子整体入栈，出栈次序仍构成合法的先序遍历
    return dfn


def answer_query(nodes: list[int], dep: list[int], root: list[int],
                 dfn: list[int], up: UpTable) -> int:
    """一个询问的答案：Σdep - Σdep(LCA 相邻同树点) + 涉及的树棵数。

    长者 i 管辖的球长就是森林里"根 -> i"这条路径上的点，于是询问在求若干条根路径的
    并集大小。点按 DFS 序排序后同树的点连成一段：相邻两项的公共前缀被算了两次，
    减掉一次；跨树的相邻两项不相交，只把"树棵数"多计一次。
    """
    if not nodes:
        return 0  # 空询问：没有球长被采访
    nodes.sort(key=dfn.__getitem__)  # 按 DFS 序排序，同一棵树的点连成一段
    total = dep[nodes[0]]
    trees = 1
    for i in range(1, len(nodes)):
        u = nodes[i - 1]
        v = nodes[i]
        total += dep[v]
        if root[u] != root[v]:
            trees += 1
        else:
            total -= dep[lca(u, v, dep, up)]
    return total + trees  # 每棵树的根（深度 0）在最浅处只算一次


def solve() -> None:
    fin = sys.stdin.buffer
    n = int(fin.readline())
    par, dep, root, up = build_forest(fin, n)
    dfn = assign_dfn(par, n)

    m = int(fin.readline())
    out: list[int] = []
    for _ in range(m):
        row = read_entity(fin)
        size = row[0]  # 本询问给的长者个数
        out.append(answer_query(row[1:1 + size], dep, root, dfn, up))

    sys.stdout.write('\n'.join(map(str, out)) + '\n')


if __name__ == "__main__":
    solve()
