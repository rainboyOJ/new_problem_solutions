from decimal import Decimal, getcontext

getcontext().prec = 210
first = Decimal(input())
second = Decimal(input())

print(format(first + second, "f"))
