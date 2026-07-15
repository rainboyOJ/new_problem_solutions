def can_expand(left, right):
    return (
        left.isdigit() and right.isdigit()
        or left.islower() and right.islower()
    ) and ord(left) < ord(right)


def middle(left, right):
    if not can_expand(left, right):
        return "-"
    chars = map(chr, range(ord(left) + 1, ord(right)))
    chars = list(chars)
    if p3 == 2:
        chars.reverse()
    if p1 == 3:
        return "*" * (len(chars) * p2)
    if p1 == 2 and left.islower():
        chars = list(map(str.upper, chars))
    return "".join(ch * p2 for ch in chars)


p1, p2, p3 = map(int, input().split())
s = input().strip()
answer = [
    middle(s[i - 1], s[i + 1]) if ch == "-" and 0 < i < len(s) - 1 else ch
    for i, ch in enumerate(s)
]
print("".join(answer))
