import sys


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    it = iter(data)
    N = next(it)
    V = next(it)
    groups = []
    for _ in range(N):
        s = next(it)
        group = []
        for __ in range(s):
            v = next(it)
            w = next(it)
            group.append((v, w))
        groups.append(group)

    ans = 0

    def dfs(gid: int, cur_vol: int, cur_val: int) -> None:
        nonlocal ans
        if cur_vol > V:
            return
        if gid == len(groups):
            ans = max(ans, cur_val)
            return
        dfs(gid + 1, cur_vol, cur_val)
        for v, w in groups[gid]:
            if cur_vol + v <= V:
                dfs(gid + 1, cur_vol + v, cur_val + w)

    dfs(0, 0, 0)
    print(ans)


if __name__ == '__main__':
    solve()
