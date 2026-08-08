import sys

data = sys.stdin.buffer.read().split()
n = int(data[0])
begin = int(data[1])
maxLevel = int(data[2])
c = [int(x) for x in data[3:3+n]]

ans = -1

def dfs(i, vol):
    global ans
    if vol < 0 or vol > maxLevel:
        return
    if i == n:
        if vol > ans:
            ans = vol
        return
    dfs(i + 1, vol + c[i])
    dfs(i + 1, vol - c[i])

dfs(0, begin)
print(ans)
