expression = input().replace(" ", "")

for operator in "+-*/%":
    if operator in expression:
        left, right = map(int, expression.split(operator))
        break

if operator == "+":
    print(left + right)
elif operator == "-":
    print(left - right)
elif operator == "*":
    print(left * right)
elif operator == "/":
    print(left // right)
else:
    print(left % right)
