def same_expand_type(left, right):
    return (left.isdigit() and right.isdigit()) or (
        left.islower() and right.islower()
    )


def expand_middle(left, right):
    if not same_expand_type(left, right) or ord(right) <= ord(left):
        return "-"

    chars = [chr(code) for code in range(ord(left) + 1, ord(right))]
    if p3 == 2:
        chars.reverse()

    result = []
    for ch in chars:
        if p1 == 3:
            result.append("*" * p2)
        elif p1 == 2 and ch.islower():
            result.append(ch.upper() * p2)
        else:
            result.append(ch * p2)
    return "".join(result)


p1, p2, p3 = map(int, input().split())
s = input().strip()
answer = []

for i, ch in enumerate(s):
    if ch == "-" and 0 < i < len(s) - 1:
        answer.append(expand_middle(s[i - 1], s[i + 1]))
    else:
        answer.append(ch)

print("".join(answer))
