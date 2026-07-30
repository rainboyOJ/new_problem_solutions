from decimal import Decimal, getcontext

getcontext().prec = 210
print(format(Decimal(input()) + Decimal(input()), "f"))
