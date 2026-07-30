def trunc_dividend(dividend, divisor):
    quotient = abs(dividend) // abs(divisor)
    return quotient if dividend * divisor >= 0 else -quotient


a, b, c = map(int, input().split())
print(trunc_dividend(a + b, c))
