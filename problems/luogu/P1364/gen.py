#!/usr/bin/env python3
"""P1364 医院设置 数据生成器。

用法：
    python3 gen.py                  # 随机 n（1..100）、随机结构
    python3 gen.py 100              # 指定 n，随机结构
    python3 gen.py 100 chain        # 指定 n 和结构：chain / balanced / random

输出即题目输入：第一行 n，接下来 n 行每行 w, u, v。
节点编号 1..n 会再打乱一次，避免解法暗含"编号越大越靠下"的错误假设。
"""
import random
import sys

from cyaron import IO, randint


def build_positions(n, structure):
    """返回每个位置的孩子位置列表（位置 0 是根）。"""
    children = [[] for _ in range(n)]

    if structure == "chain":
        # 链：每个节点最多一个孩子，递归深度最大
        for pos in range(1, n):
            children[pos - 1].append(pos)
        return children

    if structure == "balanced":
        # 完全二叉树：父子编号满足 2i / 2i+1
        for pos in range(1, n):
            children[(pos - 1) // 2].append(pos)
        return children

    # 随机二叉树：每次挂到还有空位的节点上
    free_slots = [0]
    for pos in range(1, n):
        parent = random.choice(free_slots)
        children[parent].append(pos)
        if len(children[parent]) == 2:
            free_slots.remove(parent)
        free_slots.append(pos)
    return children


def main():
    n = int(sys.argv[1]) if len(sys.argv) > 1 else randint(1, 100)
    structure = sys.argv[2] if len(sys.argv) > 2 else random.choice(["random", "random", "chain", "balanced"])

    random.seed()
    children = build_positions(n, structure)

    # 位置 -> 节点编号的随机映射，打乱标号与深度的相关性
    label = list(range(1, n + 1))
    random.shuffle(label)

    # 第 i 行描述节点 i，所以要按节点编号而不是位置输出
    left_of = [0] * (n + 1)
    right_of = [0] * (n + 1)
    weight_of = [0] * (n + 1)
    for pos in range(n):
        node = label[pos]
        left_of[node] = label[children[pos][0]] if len(children[pos]) > 0 else 0
        right_of[node] = label[children[pos][1]] if len(children[pos]) > 1 else 0
        weight_of[node] = randint(1, 10**5)

    io = IO(input_file=sys.stdout, disable_output=True)
    io.input_writeln(n)
    for node in range(1, n + 1):
        io.input_writeln(weight_of[node], left_of[node], right_of[node])


if __name__ == "__main__":
    main()
