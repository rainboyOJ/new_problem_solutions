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
    "普及",
    "普及+/提高-",
    "提高",
    "提高+/省选-",
    "省选/NOI-",
    "未知",
}
INCLUDE_CODE_RE = re.compile(r"^@include-code\(\./([^,\s)]+),\s*([^)]+)\)\s*$", re.M)
H2_RE = re.compile(r"^##\s+(.+?)\s*$", re.M)
CODE_OMIT_RE = re.compile(r"同解法|见解法|见上文|略|不单独给出")


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
        # 只解析顶层字段：跳过空行、注释、缩进的子行（数组元素/嵌套对象）。
        if not line or line[0] in " \t" or ":" not in line:
            continue
        key, value = line.split(":", 1)
        data[key.strip()] = value.strip()
    return data


def is_yaml_string_scalar(value: str) -> bool:
    """检查 favorite_reason 是否明显是 YAML 字符串，而不是其他标量/集合。"""

    stripped = value.strip()
    if not stripped or stripped.lower() in {"null", "~", "true", "false"}:
        return False
    if stripped.startswith(("[", "{")):
        return False
    if re.fullmatch(r"[-+]?(?:\d+\.?\d*|\.\d+)(?:[eE][-+]?\d+)?", stripped):
        return False
    if stripped[0] in {'"', "'"}:
        return len(stripped) >= 2 and stripped[-1] == stripped[0]
    return True


def infer_expected(problem_dir: Path) -> tuple[str | None, str | None]:
    try:
        relative = problem_dir.resolve().relative_to(PROBLEMS_ROOT)
    except ValueError:
        return None, None
    parts = relative.parts
    if len(parts) < 2:
        return None, None
    oj, dir_id = parts[0], parts[1]
    if oj == "luogu":
        match = re.fullmatch(r"p?(\d+)", dir_id, flags=re.IGNORECASE)
        if match:
            return oj, f"P{match.group(1)}"
    return oj, dir_id


def parse_code_includes(content: str) -> list[tuple[str, str]]:
    return [(match.group(1), match.group(2).strip()) for match in INCLUDE_CODE_RE.finditer(content)]


def is_main_solution_path(include_path: str) -> bool:
    path = Path(include_path)
    return len(path.parts) == 1 and path.name.startswith("main.") and path.suffix != ""


def find_main_solution_includes(content: str) -> list[tuple[str, str]]:
    return [
        (include_path, language)
        for include_path, language in parse_code_includes(content)
        if is_main_solution_path(include_path)
    ]


def main_solution_files(problem_dir: Path) -> list[Path]:
    return sorted(path for path in problem_dir.glob("main.*") if path.is_file())


def included_code_filenames(content: str) -> set[str]:
    return {Path(include_path).name for include_path, _language in parse_code_includes(content)}


def h2_sections(content: str) -> list[tuple[str, int, int]]:
    matches = list(H2_RE.finditer(content))
    sections: list[tuple[str, int, int]] = []
    for i, match in enumerate(matches):
        end = matches[i + 1].start() if i + 1 < len(matches) else len(content)
        sections.append((match.group(1).strip(), match.end(), end))
    return sections


def is_solution_heading(title: str) -> bool:
    return title.startswith("解法")


def has_h2(content: str, title: str) -> bool:
    for section_title, _start, _end in h2_sections(content):
        if section_title == title:
            return True
    return False


def solution_sections(content: str) -> list[tuple[str, str]]:
    result: list[tuple[str, str]] = []
    for title, start, end in h2_sections(content):
        if is_solution_heading(title):
            result.append((title, content[start:end]))
    return result


def is_multi_solution(content: str) -> bool:
    return len(solution_sections(content)) >= 2


def check_multi_solution_layout(content: str, errors: list[str], warnings: list[str], suggestions: list[str]) -> None:
    if not has_h2(content, "思路"):
        errors.append("多解法题缺少 ## 思路 总览章节。")
        suggestions.append("在多个 ## 解法... 之前添加 ## 思路，说明解法路线和正式主解。")

    overview = ""
    for title, start, end in h2_sections(content):
        if title == "思路":
            overview = content[start:end]
            break
    if overview and "正式主解" not in overview and "main." not in overview and "main.cpp" not in overview:
        warnings.append("多解法题的 ## 思路 未明确说明正式主解或 main.<ext>。")
        suggestions.append("在 ## 思路 中写明正式主解是哪一个解法，以及它对应的 main.<ext> 文件。")

    for title, body in solution_sections(content):
        code_match = re.search(r"^###\s+代码\s*$", body, flags=re.M)
        if not code_match:
            errors.append(f"{title} 缺少 ### 代码 小节。")
            continue
        next_h3 = re.search(r"^###\s+", body[code_match.end():], flags=re.M)
        code_end = code_match.end() + next_h3.start() if next_h3 else len(body)
        code_body = body[code_match.end():code_end]
        if not parse_code_includes(code_body):
            if CODE_OMIT_RE.search(code_body):
                warnings.append(f"{title} 的 ### 代码 没有 include，确认这是刻意省略。")
            else:
                warnings.append(f"{title} 的 ### 代码 没有 @include-code 或明确省略说明。")
                suggestions.append(f"为 {title} 添加 @include-code(...)，或写明同解法/见解法/略的原因。")


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
    elif expected_oj == "luogu":
        dir_id = problem_dir.parts[-1]
        if re.fullmatch(r"\d+", dir_id):
            errors.append(
                "Luogu 数字题目录必须使用 P 前缀："
                f"请将 problems/luogu/{dir_id} 重命名为 problems/luogu/P{dir_id}。"
            )
        elif re.fullmatch(r"p\d+", dir_id) and not dir_id.startswith("P"):
            errors.append(
                "Luogu 题目目录的 P 前缀必须使用大写："
                f"请将 problems/luogu/{dir_id} 重命名为 problems/luogu/{dir_id.upper()}。"
            )

    index_md = problem_dir / "index.md"
    main_files = main_solution_files(problem_dir)

    if not index_md.exists():
        errors.append("缺少 index.md。")
        suggestions.append("运行 new-problem 或使用 oj-problem-format-spec 生成 index.md 骨架。")
    if not main_files:
        errors.append("缺少正式代码文件 main.<ext>。")
        suggestions.append("将正式代码放到 main.cpp、main.rs、main.hs、main.py、main.js 等 main.<ext> 文件中，并在题解中 include 它。")

    included_code_names: set[str] = set()

    if index_md.exists():
        content = index_md.read_text(encoding="utf-8")
        included_code_names = included_code_filenames(content)
        main_includes = find_main_solution_includes(content)
        multi_solution = is_multi_solution(content)
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
                        "difficulty 使用：入门、普及-、普及、普及+/提高-、"
                        "提高、提高+/省选-、省选/NOI-、未知。"
                    )

            # favorite 元数据是后续加入的；旧文章可以暂时缺少，但一旦存在就必须保持类型正确。
            if "favorite" in frontmatter:
                favorite = frontmatter["favorite"].strip()
                if favorite not in {"true", "false"}:
                    errors.append("frontmatter favorite 必须是布尔值 true 或 false。")

            if "favorite_reason" in frontmatter and not is_yaml_string_scalar(
                frontmatter["favorite_reason"]
            ):
                errors.append("frontmatter favorite_reason 必须是字符串。")

            if expected_oj and frontmatter.get("oj", "").strip("'\"") != expected_oj:
                warnings.append(
                    f"frontmatter oj={frontmatter.get('oj')} 与目录 oj={expected_oj} 不一致。"
                )
            if expected_id and frontmatter.get("problem_id", "").strip("'\"") != expected_id:
                warnings.append(
                    "frontmatter problem_id="
                    f"{frontmatter.get('problem_id')} 与目录 problem_id={expected_id} 不一致。"
                )

        if not main_includes:
            errors.append("index.md 未使用正式代码 @include-code(./main.<ext>, <lang>)。")
            suggestions.append("把代码章节改为 @include-code(./main.cpp, cpp) 或对应语言的 main.<ext>。")
        else:
            missing_includes = [
                include_path
                for include_path, _language in main_includes
                if not (problem_dir / include_path).exists()
            ]
            if missing_includes:
                errors.append(
                    "index.md 引用的正式代码文件不存在："
                    + ", ".join(f"./{path}" for path in missing_includes)
                )
                suggestions.append("确认 @include-code 引用的 main.<ext> 文件位于题目目录根部。")

        if multi_solution:
            check_multi_solution_layout(content, errors, warnings, suggestions)

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
        if p.name not in allowed_cpp and p.name not in included_code_names
    )
    if legacy_cpp and not main_files:
        warnings.append(f"发现旧代码文件但缺少 main.<ext>：{', '.join(legacy_cpp)}")
        suggestions.append("将正式提交代码复制或重命名为 main.cpp 或对应语言的 main.<ext>。")
    elif legacy_cpp:
        warnings.append(f"发现旧代码文件：{', '.join(legacy_cpp)}")

    allowed_root_md = {"index.md", "problem.md"}
    extra_md = sorted(p.name for p in problem_dir.glob("*.md") if p.name not in allowed_root_md)
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
