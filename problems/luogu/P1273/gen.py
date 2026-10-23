#!/usr/bin/env python3
import random

def main():
    # 转播站数量 T in [1, 5]
    # 用户数量 M in [1, 5]
    # 根节点为 1，其他转播站为 2 .. T
    # 用户为 T+1 .. T+M
    T = random.randint(1, 5)
    M = random.randint(1, 5)
    N = T + M

    # 我们构造一棵以 1 为根的有向树
    # 每个节点 2..N 的父亲必须是 1..T 中的某个转播站
    children = [[] for _ in range(T + 1)]
    
    # 为了保证所有 1..T 都在以 1 为根的树中连通且有正确的拓扑序
    # 对于节点 2..T，其父亲从 1..i-1 中选取
    for i in range(2, T + 1):
        p = random.randint(1, i - 1)
        cost = random.randint(1, 10)
        children[p].append((i, cost))

    # 对于叶子用户 T+1 .. T+M，其父亲从 1..T 中随机选取
    for i in range(T + 1, N + 1):
        p = random.randint(1, T)
        cost = random.randint(1, 10)
        children[p].append((i, cost))

    print(f"{N} {M}")
    for i in range(1, T + 1):
        row = [len(children[i])]
        for to, cost in children[i]:
            row.append(to)
            row.append(cost)
        print(" ".join(map(str, row)))

    user_vals = [random.randint(1, 10) for _ in range(M)]
    print(" ".join(map(str, user_vals)))

if __name__ == "__main__":
    main()
