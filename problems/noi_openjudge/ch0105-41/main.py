left, right = map(int, input().split())
answer = sum(str(number).count("2") for number in range(left, right + 1))
print(answer)
