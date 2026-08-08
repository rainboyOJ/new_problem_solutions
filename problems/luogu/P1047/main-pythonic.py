L, m = map(int, input().split())
diff = [0] * (L + 2)
for _ in range(m):
    l, r = map(int, input().split())
    diff[l] += 1
    diff[r + 1] -= 1
cover = answer = 0
for i in range(L + 1):
    cover += diff[i]
    answer += cover == 0
print(answer)
