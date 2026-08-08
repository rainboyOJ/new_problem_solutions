inorder = input().strip()
postorder = input().strip()


def preorder(infix, postfix):
    if not infix:
        return ""
    root = postfix[-1]
    middle = infix.index(root)
    return (
        root
        + preorder(infix[:middle], postfix[:middle])
        + preorder(infix[middle + 1:], postfix[middle:-1])
    )


print(preorder(inorder, postorder))
