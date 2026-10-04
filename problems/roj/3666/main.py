#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 14:31
# update_at: 2026-10-02 14:54

import sys

AND = 0  # 结点运算符编码：0 = &，1 = |，2 = !，-1 = 变量叶子
OR = 1
NOT = 2


def calc(op: int, l: int, r: int) -> int:
    """按运算符合成左右孩子的值；! 只用左值，右位的 -1 是占位。"""
    if op == AND:
        return l & r
    if op == OR:
        return l | r
    return l ^ 1


def build(tokens: list[bytes], val: list[int]) -> tuple[list[int], list[tuple[int, int]], list[int], list[int], int]:
    """后缀表达式逐词建树：变量出叶子，运算符不断把栈顶片段合并成更大片段。

    每个变量在表达式中恰好出现一次，叶子按变量下标登记，与出现顺序无关。
    返回 (op_of, child, leaf_val, var_leaf, root)：op_of[v] 是 v 的运算符（叶子为 -1），
    child[v] 是 (左孩子, 右孩子)（! 没有右孩子，右位记 -1），leaf_val[v] 是叶子初值
    （内部结点记 -1），var_leaf[i] 是变量 xi 的叶子。结点按 token 顺序编号，
    孩子一定先于父结点出现，所以正序是拓扑序、逆序是反拓扑序。
    """
    var_leaf = [-1] * len(val)  # 变量下标 → 叶子结点编号
    op_of: list[int] = []
    child: list[tuple[int, int]] = []
    leaf_val: list[int] = []
    stack: list[int] = []  # 栈里是各"表达式片段"的根结点编号

    for tok in tokens:
        v = len(op_of)  # 新结点编号
        if tok == b'!':
            c = stack.pop()  # 一元运算：唯一的孩子放左位
            stack.append(v)
            op_of.append(NOT)
            child.append((c, -1))
            leaf_val.append(-1)
        elif tok == b'&' or tok == b'|':
            cr = stack.pop()  # 右操作数先进栈，先弹的是右孩子
            cl = stack.pop()
            stack.append(v)
            op_of.append(AND if tok == b'&' else OR)
            child.append((cl, cr))
            leaf_val.append(-1)
        else:  # token 形如 x10：x + 正整数下标
            i = int(tok[1:]) - 1
            stack.append(v)
            op_of.append(-1)
            child.append((-1, -1))
            leaf_val.append(val[i])
            var_leaf[i] = v
    return op_of, child, leaf_val, var_leaf, stack[0]


def fill_values(op_of: list[int], child: list[tuple[int, int]], leaf_val: list[int]) -> list[int]:
    """自底向上求每个结点的值：孩子编号一定小于父结点，正序扫一遍就是拓扑序。"""
    node_val = [0] * len(op_of)
    for v, op in enumerate(op_of):
        if op < 0:  # 变量叶子：值就是输入给的初值
            node_val[v] = leaf_val[v]
        else:
            cl, cr = child[v]
            node_val[v] = calc(op, node_val[cl], node_val[cr] if cr >= 0 else 0)
    return node_val


def fill_sens(root: int, op_of: list[int], child: list[tuple[int, int]], node_val: list[int]) -> list[int]:
    """反向传播"翻转信号"：sens[v] = 1 表示把 v 的值取反能让根的值也取反。

    父结点编号一定大于孩子，逆序扫（根最先）就能保证下传时父结点的信号已就位。
    信号穿过结点的条件只看兄弟的原值——变量各出现一次，翻转不会影响兄弟。
    """
    sens = [0] * len(op_of)
    sens[root] = 1  # 根自己取反，答案当然跟着取反
    for v in range(len(op_of) - 1, -1, -1):
        op = op_of[v]
        if op < 0:
            continue  # 叶子是信号终点，答案查询时直接读它
        cl, cr = child[v]
        if op == NOT:
            sens[cl] = sens[v]  # 取反不吸收信号，原样传给唯一的孩子
            continue
        # 与门要兄弟为 1、或门要兄弟为 0，孩子的翻转才穿得过本结点
        pass_l = node_val[cr] if op == AND else 1 - node_val[cr]
        pass_r = node_val[cl] if op == AND else 1 - node_val[cl]
        sens[cl] = sens[v] & pass_l
        sens[cr] = sens[v] & pass_r
    return sens


def solve() -> None:
    parts = sys.stdin.buffer.read().split()
    pos = 0

    # 表达式 token 只有 x 开头的变量与 & | !，读到第一个纯数字（就是 n）为止
    expr_tokens: list[bytes] = []
    while not parts[pos].isdigit():
        expr_tokens.append(parts[pos])
        pos += 1

    n = int(parts[pos]); pos += 1
    val = [int(x) for x in parts[pos:pos + n]]; pos += n  # val[i]：xi 的初值
    q = int(parts[pos]); pos += 1

    op_of, child, leaf_val, var_leaf, root = build(expr_tokens, val)
    node_val = fill_values(op_of, child, leaf_val)
    sens = fill_sens(root, op_of, child, node_val)

    # 每个询问只临时翻一个变量：答案 = 根值 XOR 该叶子的翻转信号，O(1) 作答
    out = [str(node_val[root] ^ sens[var_leaf[int(parts[pos + i]) - 1]]) for i in range(q)]
    print('\n'.join(out))


if __name__ == "__main__":
    solve()
