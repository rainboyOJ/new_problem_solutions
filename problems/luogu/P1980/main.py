n, x = map(int, input().split())
target = str(x)

answer = sum(str(number).count(target) for number in range(1, n + 1))
print(answer, end="")
