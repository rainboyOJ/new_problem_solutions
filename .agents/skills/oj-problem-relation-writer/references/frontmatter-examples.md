# Frontmatter 关系字段示例

`oj-problem-relation-writer` 的完整示例和脚本调用。判定规则见 [SKILL.md](../SKILL.md)。

## 完整字段 Schema

```yaml
pre:
  - oj: "luogu"
    problem_id: "P1002"
    reason: "网格路径计数 DP 的基础版本"
common:
  - oj: "luogu"
    problem_id: "P1002"
    reason: "同样是带限制的网格 DP"
recommend:
  - oj: "leetcode"
    problem_id: "62"
    title: "Unique Paths"
    url: "https://leetcode.com/problems/unique-paths/"
    reason: "同样是基础网格路径计数 DP，适合作为同模型练习。"
    relation: "similar"
```

## 推荐 frontmatter 片段

```yaml
tags: ["动态规划"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "luogu"
    problem_id: "P1002"
    reason: "网格路径计数 DP 的基础版本"
common: []
recommend:
  - oj: "leetcode"
    problem_id: "62"
    title: "Unique Paths"
    url: "https://leetcode.com/problems/unique-paths/"
    reason: "同样是基础网格路径计数 DP，适合作为同模型练习。"
    relation: "similar"
source: https://www.luogu.com.cn/problem/Pxxxx
```

## 候选关系记录格式

记录到 `problems/<oj>/<problem_id>/problem-relation-workspace/candidates.md`：

```markdown
# 关系候选

## pre 候选

- `luogu/P1002`：可能是网格 DP 前置，但还没有确认当前题是否真的依赖该模型。

## common 候选

- `luogu/Pxxxx`：同为 DP 标签，但状态设计是否相似待确认。

## recommend 候选

- `leetcode/62 Unique Paths`：可能适合作为网格 DP 练习，但链接或题号尚未验证。
```

## 校验脚本调用

从仓库根目录：

```bash
python3 scripts/problem-analysis-tools/check_relations.py problems/<oj>/<problem_id>
```

当前工作目录已经是题目目录时：

```bash
python3 ../../../scripts/problem-analysis-tools/check_relations.py
```

提交前或批量整理后检查全仓库：

```bash
python3 scripts/problem-analysis-tools/check_relations.py --all
```
