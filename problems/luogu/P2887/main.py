import sys

tokens = iter(map(int, sys.stdin.buffer.read().split()))
C = next(tokens)
L = next(tokens)
cows = [(next(tokens) ,next(tokens))for _ in range(C)]
lofs = [[next(tokens) ,next(tokens)]for _ in range(L)]

# print(cows)
# print(lofs)


# cows 按第二个值排序
cows.sort(key=lambda x: x[1])
# lofs 按第二个值排序
lofs.sort(key=lambda x: x[0])

def pick_one(l,r):
    for item in lofs:
        if l <= item[0] <= r and item[1] > 0:
            item[1] -= 1
            return 1
    return 0

ans = 0;
for l,r in cows:
    # print(l,r)
    ans+= pick_one(l,r)

print(ans)
