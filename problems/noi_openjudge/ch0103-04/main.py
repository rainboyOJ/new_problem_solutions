def trunc_dividend(dividend, divisor):
    quotient = abs(dividend) // abs(divisor)
    return quotient if dividend * divisor >= 0 else -quotient


dividend, divisor = map(int, input().split())
quotient = trunc_dividend(dividend, divisor)
print(quotient, dividend - quotient * divisor)
