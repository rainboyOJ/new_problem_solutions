brackets = input().strip()
stack = []
matched = [False] * len(brackets)
opening_for = {")": "(", "]": "["}
completion = {"(": "()", ")": "()", "[": "[]", "]": "[]"}

for index, bracket in enumerate(brackets):
    if bracket in "([":
        stack.append(index)
    elif stack and brackets[stack[-1]] == opening_for[bracket]:
        matched[index] = matched[stack.pop()] = True

print("".join(
    bracket if matched[index] else completion[bracket]
    for index, bracket in enumerate(brackets)
))
