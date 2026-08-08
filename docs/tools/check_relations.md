# check_relations.py

位置：

```text
scripts/problem-analysis-tools/check_relations.py
```

作用：检查题目 `index.md` frontmatter 中的 `pre` / `common` / `recommend` 字段，避免题目关系图和推荐练习数据出现错误。

## 基本用法

检查指定题目：

```bash
python3 scripts/problem-analysis-tools/check_relations.py problems/luogu/P1002
```

在题目目录中检查当前题：

```bash
python3 ../../../scripts/problem-analysis-tools/check_relations.py
```

检查全仓库：

```bash
python3 scripts/problem-analysis-tools/check_relations.py --all
```

如果已经配置 `ptool`：

```bash
ptool check_relations problems/luogu/P1002
ptool check_relations --all
```

## 检查内容

- `pre` / `common` / `recommend` 是否为数组格式。
- 每个关系项是否包含 `oj` 和 `problem_id`。
- 是否误用了 `pid` 字段。
- 是否引用当前题自己。
- 是否存在重复关系。
- 关系目标是否存在于仓库。
- 如果目录名和目标题 `problem_id` 不一致，是否使用了目标 frontmatter 中的 `problem_id`。
- 缺少 `reason` 时给出 warning。
- `recommend` 每项是否包含 `reason` 和合法的 `relation`。
- `recommend.relation` 是否为 `similar`、`practice`、`harder`、`easier` 之一。
- `recommend` 指向仓库内已有题目时给出 warning，建议改用 `pre` / `common`。
- `recommend.url` 缺失时给出 warning，建议补可验证链接。

## 退出码

- `0`：没有错误。
- `1`：存在错误。

warning 不会导致失败。
