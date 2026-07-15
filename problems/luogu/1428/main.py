n = int(input())
cuteness = list(map(int, input().split()))

answer = []
for i in range(n):
    count = 0
    for j in range(i):
        if cuteness[j] < cuteness[i]:
            count += 1
    answer.append(count)

print(*answer)
