expression = input().strip()
stack = []
digits = []

def divide_toward_zero(left, right):
    sign = -1 if (left < 0) != (right < 0) else 1
    return sign * (abs(left) // abs(right))

for character in expression:
    if character.isdigit():
        digits.append(character)
    elif character == ".":
        stack.append(int("".join(digits)))
        digits.clear()
    elif character == "@":
        break
    else:
        right = stack.pop()
        left = stack.pop()
        if character == "+":
            stack.append(left + right)
        elif character == "-":
            stack.append(left - right)
        elif character == "*":
            stack.append(left * right)
        else:
            stack.append(divide_toward_zero(left, right))

print(stack[-1])
