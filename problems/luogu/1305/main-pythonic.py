n = int(input())
children = {}
root = None

for _ in range(n):
    node, left, right = input().strip()
    root = root or node
    children[node] = left, right

def preorder(node):
    if node == "*":
        return ""
    left, right = children[node]
    return node + preorder(left) + preorder(right)

print(preorder(root))
