import sys


def solve():
    # 上面的 O(n * 链长) 写法在「两两不同」的最坏数据下会退化成 O(n^2)。
    # 其实不必对每局单独走链：所有链共享同一批边，可以直接把「经过次数」往下推。
    #
    # cnt[i]：有多少局游戏的跳跃链经过位置 i。
    #   位置 i 自己开始的那一局算 1 次，再加上从别处跳到 i 来的次数；
    #   跳到的目标 last[a[i]] + 1 一定严格大于 i，所以从小到大扫一遍就能推完。
    _, m, *a = map(int, sys.stdin.buffer.read().split())
    n = len(a)

    last = [0] * (m + 1)
    for i, v in enumerate(a):
        last[v] = i

    cnt = [1] * (n + 1)                     # cnt[n] 是哨兵：链跳到 n 就是结束，不再往下传
    for i, v in enumerate(a):
        cnt[last[v] + 1] += cnt[i]

    ans = [0] * (m + 1)
    for i, v in enumerate(a):
        ans[v] += cnt[i]

    print(*ans[1:])


if __name__ == "__main__":
    solve()
