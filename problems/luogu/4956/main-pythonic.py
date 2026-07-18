target = int(input())

for x in range(100, -1, -1):
    rest = target - 364 * x
    if rest > 0 and rest % 1092 == 0:
        k = rest // 1092
        print(x)
        print(k)
        break
