import sys


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    it = iter(data)
    N = next(it)
    V = next(it)
    items = []
    for _ in range(N):
        v = next(it)
        w = next(it)
        s = next(it)
        items.append((v, w, s))

    ans = 0

    def dfs(idx: int, cur_vol: int, cur_val: int) -> None:
        nonlocal ans
        if cur_vol > V:
            return
        if idx == N:
            if cur_vol <= V:
                ans = max(ans, cur_val)
            return
        v, w, s = items[idx]
        if s == -1:
            dfs(idx + 1, cur_vol, cur_val)
            dfs(idx + 1, cur_vol + v, cur_val + w)
        else:
            max_cnt = (V - cur_vol) // v
            for cnt in range(max_cnt + 1):
                dfs(idx + 1, cur_vol + cnt * v, cur_val + cnt * w)

    dfs(0, 0, 0)
    print(ans)


if __name__ == '__main__':
    solve()
