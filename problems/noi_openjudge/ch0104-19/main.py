def trunc_divide(dividend, divisor):
    quotient = abs(dividend) // abs(divisor)
    return quotient if dividend * divisor >= 0 else -quotient


left_text, right_text, operator = input().split()
left, right = int(left_text), int(right_text)

if operator == "+":
    print(left + right)
elif operator == "-":
    print(left - right)
elif operator == "*":
    print(left * right)
elif operator == "/":
    print("Divided by zero!" if right == 0 else trunc_divide(left, right))
else:
    print("Invalid operator!")
