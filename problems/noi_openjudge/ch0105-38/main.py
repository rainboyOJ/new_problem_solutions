degree = int(input())
coefficients = list(map(int, input().split()))

if degree == 0:
    print(0)
else:
    derivative = [coefficient * power for coefficient, power in zip(coefficients, range(degree, 0, -1))]
    print(*derivative)
