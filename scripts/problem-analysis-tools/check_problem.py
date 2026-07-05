#!/usr/bin/env python3
"""Check one problem directory for the current OJ ebook conventions."""

from __future__ import annotations

import argparse
import re
import subprocess
import sys
from pathlib import Path


REPO_ROOT = Path(__file__).resolve().parents[2]
PROBLEMS_ROOT = REPO_ROOT / "problems"
REQUIRED_FRONTMATTER = [
    "oj",
    "problem_id",
    "title",
    "description",
    "date",
    "toc",
    "tags",
    "categories",
    "source",
]
DIFFICULTY_VALUES = {
    "入门",
    "普及-",
    "普及/提高-",
    "普及+/提高",
    "提高+/省选-",
    "省选/NOI-",
    "NOI/NOI+/CTSC",
    "未知",
}


def rel(path: Path) -> str:
    try:
        return str(path.resolve().relative_to(REPO_ROOT))
    except ValueError:
        return str(path)


def parse_frontmatter(content: str) -> dict[str, str] | None:
    if not content.startswith("---\n"):
        return None
    end = content.find("\n---", 4)
    if end == -1:
        return None
    data: dict[str, str] = {}
    for line in content[4:end].splitlines():
        stripped = line.strip()
        if not stripped or stripped.startswith("#") or ":" not in stripped:
            continue
        key, value = stripped.split(":", 1)
        data[key.strip()] = value.strip()
    return data


def infer_expected(problem_dir: Path) -> tuple[str | None, str | None]:
    try:
        relative = problem_dir.resolve().relative_to(PROBLEMS_ROOT)
    except ValueError:
        return None, None
    parts = relative.parts
    if len(parts) < 2:
        return None, None
    return parts[0], parts[1]


def has_include_main(content: str) -> bool:
    return bool(re.search(r"^@include-code\(\./main\.cpp,\s*cpp\)\s*$", content, re.M))


def tracked_files_under(path: Path) -> list[str]:
    if not path.exists():
        return []
    result = subprocess.run(
        ["git", "ls-files", str(path)],
        cwd=REPO_ROOT,
        text=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.DEVNULL,
        check=False,
    )
    if result.returncode != 0:
        return []
    return [line for line in result.stdout.splitlines() if line.strip()]


def check_problem(problem_dir: Path) -> int:
    errors: list[str] = []
    warnings: list[str] = []
    suggestions: list[str] = []

    if not problem_dir.exists():
        errors.append(f"目录不存在：{rel(problem_dir)}")
        suggestions.append("先运行 new-problem <oj> <problem_id> 创建题目目录。")
        return print_report(problem_dir, errors, warnings, suggestions)

    if not problem_dir.is_dir():
        errors.append(f"目标不是目录：{rel(problem_dir)}")
        return print_report(problem_dir, errors, warnings, suggestions)

    expected_oj, expected_id = infer_expected(problem_dir)
    if expected_oj is None or expected_id is None:
        errors.append("题目目录必须位于 problems/<oj>/<problem_id>/ 下。")

    index_md = problem_dir / "index.md"
    main_cpp = problem_dir / "main.cpp"

    if not index_md.exists():
        errors.append("缺少 index.md。")
        suggestions.append("运行 new-problem 或使用 oj-problem-format-spec 生成 index.md 骨架。")
    if not main_cpp.exists():
        errors.append("缺少 main.cpp。")
        suggestions.append("将正式代码放到 main.cpp，并在题解中 include 它。")

    if index_md.exists():
        content = index_md.read_text(encoding="utf-8")
        frontmatter = parse_frontmatter(content)
        if frontmatter is None:
            errors.append("index.md 缺少合法 YAML frontmatter。")
        else:
            for field in REQUIRED_FRONTMATTER:
                if field not in frontmatter:
                    errors.append(f"frontmatter 缺少字段：{field}")

            if "description" in frontmatter:
                description = frontmatter.get("description", "").strip().strip("'\"")
                if not description:
                    warnings.append("frontmatter description 为空。")
                    suggestions.append("为 description 写一句题解核心摘要，描述最关键的解法思想。")
                elif "\n" in description or len(description) > 120:
                    warnings.append("frontmatter description 应为一行，且不超过 120 个字符。")

            if "difficulty" not in frontmatter:
                warnings.append("frontmatter 缺少 difficulty 字段。")
                suggestions.append('为题目补充 difficulty，例如 difficulty: "未知"。')
            else:
                difficulty = frontmatter.get("difficulty", "").strip().strip("'\"")
                if difficulty not in DIFFICULTY_VALUES:
                    warnings.append(
                        "frontmatter difficulty 不在标准枚举中："
                        f"{frontmatter.get('difficulty')}"
                    )
                    suggestions.append(
                        "difficulty 使用：入门、普及-、普及/提高-、普及+/提高、"
                        "提高+/省选-、省选/NOI-、NOI/NOI+/CTSC、未知。"
                    )

            if expected_oj and frontmatter.get("oj", "").strip("'\"") != expected_oj:
                warnings.append(
                    f"frontmatter oj={frontmatter.get('oj')} 与目录 oj={expected_oj} 不一致。"
                )
            if expected_id and frontmatter.get("problem_id", "").strip("'\"") != expected_id:
                warnings.append(
                    "frontmatter problem_id="
                    f"{frontmatter.get('problem_id')} 与目录 problem_id={expected_id} 不一致。"
                )

        if not has_include_main(content):
            errors.append("index.md 未使用 @include-code(./main.cpp, cpp)。")
            suggestions.append("把代码章节改为 @include-code(./main.cpp, cpp)。")

    tracked_workspace = tracked_files_under(problem_dir / "problem-analysis-workspace")
    if tracked_workspace:
        warnings.append("problem-analysis-workspace/ 中存在已被 Git 跟踪的文件。")
        suggestions.append("过程文档应保持本地忽略，必要时从 Git 索引中移除这些文件。")

    tracked_failed = tracked_files_under(problem_dir / "duipai-failed")
    if tracked_failed:
        warnings.append("duipai-failed/ 中存在已被 Git 跟踪的文件。")
        suggestions.append("对拍失败样例应保持本地忽略，必要时从 Git 索引中移除这些文件。")

    allowed_cpp = {
        "main.cpp",
        "brute.cpp",
        "brute_01_style.cpp",
        "gen.cpp",
    }
    legacy_cpp = sorted(
        p.name
        for p in problem_dir.glob("*.cpp")
        if p.name not in allowed_cpp
    )
    if legacy_cpp and not main_cpp.exists():
        warnings.append(f"发现旧代码文件但缺少 main.cpp：{', '.join(legacy_cpp)}")
        suggestions.append("将正式提交代码复制或重命名为 main.cpp。")
    elif legacy_cpp:
        warnings.append(f"发现旧代码文件：{', '.join(legacy_cpp)}")

    extra_md = sorted(p.name for p in problem_dir.glob("*.md") if p.name != "index.md")
    if extra_md:
        warnings.append(f"题目目录根部存在非 index.md 文档：{', '.join(extra_md)}")
        suggestions.append("正式题解只保留 index.md；过程文档放入 problem-analysis-workspace/。")

    return print_report(problem_dir, errors, warnings, suggestions)


def print_report(problem_dir: Path, errors: list[str], warnings: list[str], suggestions: list[str]) -> int:
    print(f"检查目录：{rel(problem_dir)}")
    if errors:
        print("\n错误：")
        for item in errors:
            print(f"- {item}")
    if warnings:
        print("\n警告：")
        for item in warnings:
            print(f"- {item}")
    if suggestions:
        print("\n修复建议：")
        for item in suggestions:
            print(f"- {item}")
    if not errors and not warnings:
        print("通过：题目目录符合当前规范。")
    elif not errors:
        print("\n结果：通过，但有警告。")
    else:
        print("\n结果：未通过。")
    return 1 if errors else 0


def main() -> int:
    parser = argparse.ArgumentParser(description="Check a problem directory")
    parser.add_argument("problem_dir", type=Path)
    args = parser.parse_args()
    return check_problem(args.problem_dir)


if __name__ == "__main__":
    raise SystemExit(main())
