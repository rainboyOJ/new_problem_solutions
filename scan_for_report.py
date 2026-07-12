"""Scan all problems and generate a fix-instruction markdown file for AI."""
import os, re
from datetime import datetime

problems_set = set()
with open('problem-sets/2026-cspj-summer-first-prize.md') as f:
    for line in f:
        m = re.search(r'\[\[problem: (\w+),(\w+)\]\]', line)
        if m:
            problems_set.add((m.group(1), m.group(2)))

def path_of(platform, pid):
    if platform == 'luogu':
        return f'problems/luogu/{pid.lstrip("P")}/index.md'
    elif platform == 'usaco':
        return f'problems/usaco/{pid}/index.md'
    return f'problems/{platform}/{pid}/index.md'

# --- Generate the report ---
lines_out = []
lines_out.append(f"# 公式修复任务清单")
lines_out.append(f"生成时间: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
lines_out.append(f"来源题库: `problem-sets/2026-cspj-summer-first-prize.md`")
lines_out.append("")
lines_out.append("## 说明")
lines_out.append("")
lines_out.append("- `$...$` = 行内数学模式，用于 `O(N^2)`、`N^2`、`1..N` 等")
lines_out.append("- `$$...$$` = 显示数学模式，用于独立公式块")
lines_out.append("- 每个条目对应一个文件中的一处问题，按文件路径分组")
lines_out.append("- `║` 表示该行有多个独立替换点")
lines_out.append("")

files_with_issues = []

for platform, pid in sorted(problems_set):
    path = path_of(platform, pid)
    if not os.path.exists(path):
        continue

    with open(path) as f:
        text = f.read()
        lines = text.split('\n')

    file_issues = []
    in_code_fence = False
    in_text_block = False
    text_block_start = 0
    text_block_content = []

    for lineno, line in enumerate(lines, 1):
        stripped = line.strip()
        s = line.rstrip()

        # Track code fences
        if stripped.startswith('```') and stripped != '```text':
            in_code_fence = not in_code_fence
            continue

        # Track ```text blocks
        if stripped == '```text':
            in_text_block = True
            text_block_start = lineno
            text_block_content = []
            continue
        elif in_text_block and stripped == '```':
            in_text_block = False
            block_text = ' '.join(text_block_content)
            # Check if this text block has math content
            has_math = any(k in block_text for k in [
                'N^', 'n^', 'M^', '2^', '^2', '^3', '^t', 'O(',
                'sqrt', 'Delta', '=',
                '\\times', '\\cdot', '\\sum', '\\prod', '\\min', '\\max',
            ])
            has_brackets = '[' in block_text or ']' in block_text
            has_table = '┌' in block_text or '│' in block_text or '├' in block_text
            if has_math and not has_table:
                # Only flag if it's really math (not ascii table, not code with brackets)
                if has_brackets:
                    # Check if it's math with brackets like cnt[gr][gc]
                    if '[' not in block_text or '=' in block_text:
                        pass  # borderline, but note it
                    else:
                        continue
                file_issues.append(('text_block', text_block_start,
                                    ' '.join(text_block_content[:3])[:80],
                                    block_text))
            continue
        elif in_text_block:
            text_block_content.append(s)
            continue

        if in_code_fence:
            continue

        # Skip YAML frontmatter
        if lineno <= 15 and (stripped == '---' or stripped.startswith('oj:') or
                             stripped.startswith('problem_id:') or stripped.startswith('title:') or
                             stripped.startswith('description:') or stripped.startswith('difficulty:') or
                             stripped.startswith('date:') or stripped.startswith('toc:') or
                             stripped.startswith('tags:') or stripped.startswith('categories:') or
                             stripped.startswith('pre:') or stripped.startswith('common:') or
                             stripped.startswith('recommend:') or stripped.startswith('source:')):
            continue

        # Already in math mode - skip
        if '$' in s:
            continue

        # Find backtick-wrapped patterns that should be math
        for m in re.finditer(r'`([^`]+)`', s):
            content = m.group(1)
            # Range like `1..N`
            if re.match(r'^\d+\.\.\d+$', content) or re.match(r'^\d+\.\.N$', content):
                file_issues.append(('backtick_range', lineno, content, content))
            # Single uppercase math variable (N, M, K)
            elif re.match(r'^[NMCKmc]$', content) and len(s) < 60:
                # Only if it's a standalone variable reference
                file_issues.append(('backtick_var', lineno, content, content))

    if file_issues:
        files_with_issues.append((path, file_issues))

# --- Write the report ---
total_blocks = 0
total_ranges = 0
total_vars = 0

for path, issues in files_with_issues:
    for typ, *rest in issues:
        if typ == 'text_block':
            total_blocks += 1
        elif typ == 'backtick_range':
            total_ranges += 1
        elif typ == 'backtick_var':
            total_vars += 1

lines_out.append(f"## 总览")
lines_out.append("")
lines_out.append(f"- 文件总数: {len(files_with_issues)}")
lines_out.append(f"- 公式块 (text -> $$): {total_blocks}")
lines_out.append(f"- 范围表达式 (backtick -> $): {total_ranges}")
lines_out.append(f"- 单体变量 (backtick -> $): {total_vars}")
lines_out.append("")

for path, issues in files_with_issues:
    short_path = path[path.index('problems/'):]
    lines_out.append(f"---")
    lines_out.append(f"## {short_path}")
    lines_out.append("")
    lines_out.append("| 行号 | 类型 | 当前内容 | 建议修复 |")
    lines_out.append("|:----:|:----:|---------|----------|")

    for issue in issues:
        typ = issue[0]
        lineno = issue[1]
        content = issue[2]
        if typ == 'text_block':
            block_text = issue[3]
            lines_out.append(f"| L{lineno} | `text→$$` | ````text 包含: {content}` | `$$...$$` 包裹 |")
            lines_out.append(f"| | | 原文: |")
            for bt_line in block_text.split(' ...')[0].split('\n')[:5]:
                lines_out.append(f"| | | `{bt_line}` |")
        elif typ == 'backtick_range':
            suggested = content.replace('..', ' \\dots ')
            lines_out.append(f"| L{lineno} | `` `..`→$ `` | `` `{content}` `` | `${suggested}$` |")
        elif typ == 'backtick_var':
            lines_out.append(f"| L{lineno} | `` `X`→$ `` | `` `{content}` `` | `${content}$` |")

    lines_out.append("")

lines_out.append("---")
lines_out.append("## AI 修复指南")
lines_out.append("")
lines_out.append("修复规则：")
lines_out.append("")
lines_out.append("1. `text→$$`：将整个 ````text ... ```` 块替换为 `$$ ... $$`")
lines_out.append("   - 保留原有内容不变（仅替换包裹符号）")
lines_out.append("   - 如果内容中有 `*`，替换为 `\\times`")
lines_out.append("   - 如果内容中有 `...`，替换为 `\\dots`")
lines_out.append("   - 如果内容中有 `min()`、`max()`，替换为 `\\min()`、`\\max()`")
lines_out.append("")
lines_out.append("2. `` `..`→$ ``：将反引号包裹的范围表达式转为数学模式")
lines_out.append("   - `` `1..N` `` → `$1 \\dots N$`")
lines_out.append("   - `` `0..999` `` → `$0 \\dots 999$`")
lines_out.append("")
lines_out.append("3. `` `X`→$ ``：将反引号包裹的数学变量转为数学模式")
lines_out.append("   - 仅限表示数学变量的单大写字母（N, M, K 等）")
lines_out.append("   - 不转换代码变量名")

result = '\n'.join(lines_out)

outpath = 'tmp/formula-fix-plan.md'
with open(outpath, 'w') as f:
    f.write(result)

print(f"Written to {outpath}")
print(f"Files with issues: {len(files_with_issues)}")
print(f"  - text blocks: {total_blocks}")
print(f"  - ranges: {total_ranges}")
print(f"  - variables: {total_vars}")
