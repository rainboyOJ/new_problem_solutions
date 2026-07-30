limit = int(input())
answer = sum(str(number).count("1") for number in range(1, limit + 1))
print(answer)
