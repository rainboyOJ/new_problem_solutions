rate, principal, years = map(int, input().split())
final_amount = principal * (1 + rate / 100) ** years
print(int(final_amount))
