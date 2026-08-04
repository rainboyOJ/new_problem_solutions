"""Create and update problem directories for the OJ ebook."""

from __future__ import annotations

from dataclasses import dataclass, field
import datetime as dt
from pathlib import Path
import re

from cpp_header import build_cpp_header


REPO_ROOT = Path(__file__).resolve().parents[2]
PROBLEMS_ROOT = REPO_ROOT / "problems"
TEMPLATE_DIR = Path(__file__).resolve().parent / "template"
PLACEHOLDER_RE = re.compile(r"\{\{[\w-]+\}\}")


@dataclass
class ScaffoldResult:
    """记录一次建题操作的结果，方便 CLI 和 agent 统一消费。"""

    problem_dir: Path
    created: list[Path] = field(default_factory=list)
    skipped: list[Path] = field(default_factory=list)


def infer_from_cwd(problems_root: Path = PROBLEMS_ROOT) -> tuple[str | None, str | None]:
    """从当前工作目录推断 OJ 和题号。"""

    try:
        relative = Path.cwd().resolve().relative_to(problems_root)
    except ValueError:
        return None, None
    parts = relative.parts
    if len(parts) >= 2:
        return parts[0], parts[1]
    return None, None


def quote_yaml(value: str) -> str:
    escaped = value.replace("\\", "\\\\").replace('"', '\\"')
    return f'"{escaped}"'


def write_if_missing(path: Path, content: str) -> bool:
    if path.exists():
        return False
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(content, encoding="utf-8")
    return True


def validate_problem_path_parts(oj: str, problem_dir_id: str) -> None:
    if re.search(r"[\\/]", oj) or re.search(r"[\\/]", problem_dir_id):
        raise ValueError("oj 和 problem_id 不能包含路径分隔符。")


def _render_template(filename: str, **kwargs: str) -> str:
    """渲染 template/ 下的模板文件，用 kwargs 替换 {{占位符}}。"""
    template = TEMPLATE_DIR / filename
    content = template.read_text(encoding="utf-8")
    for name, value in kwargs.items():
        content = content.replace("{{" + name + "}}", value)
    leftover = PLACEHOLDER_RE.findall(content)
    if leftover:
        raise ValueError(f"template/{filename} 存在未替换的占位符: {leftover}")
    return content


def index_template(
    oj: str,
    problem_id: str,
    title: str,
    source: str,
    *,
    now: dt.datetime | None = None,
) -> str:
    now_text = (now or dt.datetime.now()).strftime("%Y-%m-%d %H:%M")
    return _render_template(
        "index.md",
        oj=quote_yaml(oj),
        problem_id=quote_yaml(problem_id),
        title=quote_yaml(title),
        source=source,
        date=now_text,
    )


def main_cpp_template(now: dt.datetime | None = None) -> str:
    return build_cpp_header(now=now) + _render_template("main.cpp")


def brute_cpp_template(now: dt.datetime | None = None) -> str:
    return build_cpp_header(now=now) + _render_template("brute.cpp")


def gen_py_template() -> str:
    return _render_template("gen.py")


def workspace_template(title: str) -> str:
    return _render_template("workspace.md", title=title)


def problem_dir_for(
    oj: str,
    problem_dir_id: str,
    problems_root: Path = PROBLEMS_ROOT,
) -> Path:
    return problems_root / oj / problem_dir_id


def create_problem_dir(
    oj: str,
    problem_dir_id: str,
    *,
    display_problem_id: str | None = None,
    title: str = "",
    source: str = "",
    with_brute: bool = True,
    with_gen: bool = True,
    with_workspace: bool = True,
    repo_root: Path = REPO_ROOT,
    problems_root: Path = PROBLEMS_ROOT,
) -> ScaffoldResult:
    """创建或补齐题目目录。

    display_problem_id 写入 index.md，problem_dir_id 用作真实目录名。
    例如 Luogu 的 P1001 会保存到 luogu/1001，但 index.md 中仍显示 P1001。
    """

    validate_problem_path_parts(oj, problem_dir_id)
    visible_id = display_problem_id or problem_dir_id
    problem_dir = problem_dir_for(oj, problem_dir_id, problems_root)
    workspace = problem_dir / "problem-analysis-workspace"
    result = ScaffoldResult(problem_dir=problem_dir)
    now = dt.datetime.now()

    files = [
        (problem_dir / "index.md", index_template(oj, visible_id, title, source, now=now)),
        (problem_dir / "main.cpp", main_cpp_template(now)),
    ]
    if with_brute:
        files.append((problem_dir / "brute.cpp", brute_cpp_template(now)))
    if with_gen:
        files.append((problem_dir / "gen.py", gen_py_template()))

    for path, content in files:
        if write_if_missing(path, content):
            result.created.append(path)
        else:
            result.skipped.append(path)

    if with_workspace:
        workspace.mkdir(parents=True, exist_ok=True)
        stages = [
            ("01-problem-understanding.md", "题意理解"),
            ("02-observation-and-model.md", "关键观察与模型"),
            ("03-solution-derivation.md", "解法推导"),
            ("04-correctness-and-edge-cases.md", "正确性与边界情况"),
            ("05-complexity-and-implementation.md", "复杂度与实现"),
            ("06-final-index-draft.md", "最终题解草稿"),
        ]
        for filename, stage_title in stages:
            path = workspace / filename
            if write_if_missing(path, workspace_template(stage_title)):
                result.created.append(path)
            else:
                result.skipped.append(path)

    if with_gen:
        gen_path = problem_dir / "gen.py"
        try:
            gen_path.chmod(gen_path.stat().st_mode | 0o111)
        except FileNotFoundError:
            pass

    return result


def relative_to_repo(path: Path, repo_root: Path = REPO_ROOT) -> str:
    try:
        return str(path.relative_to(repo_root))
    except ValueError:
        return str(path)
