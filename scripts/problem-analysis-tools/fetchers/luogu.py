from __future__ import annotations

import json
import re
from pathlib import Path
from typing import Any

from .base import (
    BaseFetcher,
    FetchError,
    FetchResult,
    ProblemData,
    Sample,
    extract_json_script,
    markdown_section,
)

# 难度映射的唯一来源：仓库根的 lib/difficulty.json（含 luogu_id 字段）。
_DIFFICULTY_FILE = Path(__file__).resolve().parents[3] / "lib" / "difficulty.json"
LUOGU_DIFFICULTY_BY_ID: dict[int, str] = {
    int(row["luogu_id"]): str(row["value"])
    for row in json.loads(_DIFFICULTY_FILE.read_text(encoding="utf-8"))["values"]
}

# 题面语言优先级：洛谷收录 CF/AT 时 content 常是原文，中文在 translations 的 zh-CN 里。
CONTENT_LOCALE_PRIORITY = ("zh-CN", "zh", "zh-TW", "en", "ja")

# 洛谷在题面里埋的 AI 蜜罐指令名；出现新花样时在这里追加即可。
ANTI_AI_DIRECTIVES = ("anti-ai",)
_ANTI_AI_BLOCK_RE = re.compile(
    r"^[ \t]*::(?:" + "|".join(re.escape(name) for name in ANTI_AI_DIRECTIVES) + r")\[[^\]]*\][ \t]*\n?",
    flags=re.MULTILINE,
)


def strip_anti_ai_blocks(text: str | None) -> tuple[str | None, int]:
    # 只删独立成行的蜜罐块，行内正文不受影响；非贪婪到首个 ']'。
    if not isinstance(text, str):
        return text, 0
    cleaned, removed = _ANTI_AI_BLOCK_RE.subn("", text)
    if removed:
        cleaned = re.sub(r"\n{3,}", "\n\n", cleaned)
    return cleaned, removed


class LuoguFetcher(BaseFetcher):
    name = "luogu"
    aliases = ("lg",)
    site_prefixes = ("https://www.luogu.com.cn", "https://www.luogu.com")

    def real_id(self, problem_id: str) -> str:
        # 纯数字补 P 前缀，小写 p 纠正成大写 P（洛谷 P 题的规范写法）。
        # 其他一律按洛谷给的 id 原样保留，不主动改大小写：
        # U502676、B2005、AT_abc123_a 等保持调用者／洛谷的大小写。
        if problem_id[:1].isdigit():
            return f"P{problem_id}"
        if re.fullmatch(r"p\d+", problem_id):
            return f"P{problem_id[1:]}"
        return problem_id

    def dir_id(self, problem_id: str) -> str:
        # 目录名与 frontmatter 的 problem_id 保持一致，不再做大小写折叠。
        # 历史遗留：早年非 P 题目录曾强制小写，导致 problem_id 与目录名大小写不一致，
        # check_problem.py 会报 warning。这里统一按洛谷 id 原样建立目录。
        real = self.real_id(problem_id)
        if re.fullmatch(r"P\d+", real, flags=re.IGNORECASE):
            return real.upper()
        return real

    def problem_link(self, problem_id: str) -> str:
        return f"https://www.luogu.com.cn/problem/{self.real_id(problem_id)}"

    def parse_url(self, url: str) -> tuple[str, str]:
        parts = [part for part in url.split("?")[0].split("#")[0].split("/") if part]
        if "problem" not in parts:
            raise FetchError(f"无法从 Luogu URL 解析题号：{url}")
        idx = parts.index("problem")
        if idx + 1 >= len(parts):
            raise FetchError(f"无法从 Luogu URL 解析题号：{url}")
        return self.name, parts[idx + 1]

    def build_data_from_id(self, oj: str, problem_id: str) -> ProblemData:
        display_id = self.real_id(problem_id)
        return ProblemData(
            oj=self.name,
            problem_id=display_id,
            problem_dir_id=self.dir_id(problem_id),
            source=self.problem_link(problem_id),
            title=display_id,
        )

    def fetch(self, oj: str, problem_id: str) -> FetchResult:
        data = self.build_data_from_id(oj, problem_id)
        # 用调用者给的题号拼 URL 去抓（大小写可能不规范，洛谷自己能归一），
        # 但结果里的 problem_id / 目录名 / source 都以洛谷返回的 pid 为准。
        html = self.http_get(data.source)
        fetched_data = self.parse_html(html, problem_id)
        return FetchResult(data=fetched_data, fetched=True, warnings=list(fetched_data.warnings))

    def fetch_by_url(self, url: str) -> FetchResult:
        oj, problem_id = self.parse_url(url)
        result = self.fetch(oj, problem_id)
        result.data.source = url
        return result

    def parse_html(self, html: str, problem_id: str) -> ProblemData:
        # Luogu 把题目信息塞在 #lentille-context 这个 application/json script 中。
        raw = extract_json_script(html, "lentille-context")
        data = raw.get("data") or {}
        problem = data.get("problem") or {}
        if not isinstance(problem, dict):
            raise FetchError("Luogu JSON 中缺少 problem 对象。")
        translations = data.get("translations") or {}
        return self.problem_from_luogu_json(problem, problem_id, translations=translations)

    def problem_from_luogu_json(
        self,
        problem: dict[str, Any],
        problem_id: str,
        *,
        translations: dict[str, Any] | None = None,
    ) -> ProblemData:
        # 题号以洛谷返回的 pid 为准（例如用户输 uva1316，洛谷返回 UVA1316）；
        # 拿不到 pid 时才回退到调用者传入的题号。
        canonical_id = str(problem.get("pid") or "").strip() or problem_id
        display_id = self.real_id(canonical_id)
        content = self.problem_content(problem, translations)
        title = str(
            problem.get("title")
            or problem.get("name")
            or content.get("name")
            or display_id
        ).strip()
        samples = self.parse_samples(problem.get("samples"))
        statement_md, anti_ai_removed = self.problem_statement_markdown(display_id, title, content, samples)
        warnings: list[str] = []
        if anti_ai_removed:
            warnings.append(f"已过滤 {anti_ai_removed} 处 anti-ai 指令。")
        return ProblemData(
            oj=self.name,
            problem_id=display_id,
            problem_dir_id=self.dir_id(canonical_id),
            source=self.problem_link(canonical_id),
            title=title,
            statement_md=statement_md,
            samples=samples,
            difficulty=self.difficulty_from_id(problem.get("difficulty")),
            warnings=warnings,
        )

    def difficulty_from_id(self, raw: Any) -> str:
        # 洛谷官方 difficulty 字段是数字 id（2026-08 新版体系，0-8 共 9 档）。
        # 映射表以 lib/difficulty.json 的 luogu_id 为准，避免这里再维护一份而漏档
        # （历史 bug：只写到 7，黑题 NOI/NOI+/CTS=8 会返回空字符串）。
        try:
            difficulty_id = int(raw)
        except (TypeError, ValueError):
            return ""
        return LUOGU_DIFFICULTY_BY_ID.get(difficulty_id, "")

    def problem_content(
        self,
        problem: dict[str, Any],
        translations: dict[str, Any] | None = None,
    ) -> dict[str, Any]:
        """挑出题面正文，**优先中文**。

        洛谷对 CF / AtCoder 这类收录题会同时给多语言版本：
        ``problem.content`` 常是英文（CF）或日文（AT）原文，``problem.contenu``
        是中文，``data.translations`` 里再按 locale 各存一份。

        早先的实现写 ``problem.get("content") or problem.get("contenu")``，对纯洛谷题
        两份都是 zh-CN 所以看不出问题，但 CF/AT 会静默抓成英文/日文原文。

        按**字段级**叠加而不是整份替换：``translations`` 里的中文版可能只译了
        ``description``，缺少 ``formatI`` / ``formatO`` / ``hint``；整份替换会让
        输入输出格式变成空。所以先取一个中文底座，再用 translations 覆盖它。
        """

        bodies = [
            value
            for value in (problem.get("contenu"), problem.get("content"))
            if isinstance(value, dict)
        ]
        # 底座：优先 locale 是中文的那份，否则按 contenu/content 原顺序。
        base: dict[str, Any] = {}
        zh_body = next(
            (
                body
                for body in bodies
                if str(body.get("locale") or "").lower().startswith("zh")
                and self.has_statement_body(body)
            ),
            None,
        )
        if zh_body is not None:
            base.update(zh_body)
        elif bodies:
            base.update(bodies[0])

        # 再用 translations 里的中文版逐字段覆盖（只覆盖它真有的字段）。
        for locale in CONTENT_LOCALE_PRIORITY:
            version = (translations or {}).get(locale)
            if not isinstance(version, dict):
                continue
            for key, value in version.items():
                if isinstance(value, str) and value.strip():
                    base[key] = value
            break

        if not base:
            return problem
        merged = dict(problem)
        merged.update(base)
        return merged

    def has_statement_body(self, version: dict[str, Any]) -> bool:
        """判断某个语言版本是否真的有题面正文，避免选到空壳翻译。"""

        for key in ("description", "formatI", "formatO", "background", "hint"):
            value = version.get(key)
            if isinstance(value, str) and value.strip():
                return True
        return False

    def first_text_field(self, problem: dict[str, Any], *keys: str) -> str | None:
        for key in keys:
            value = problem.get(key)
            if isinstance(value, str) and value.strip():
                return value
        return None

    def parse_samples(self, raw_samples: Any) -> list[Sample]:
        samples: list[Sample] = []
        if not isinstance(raw_samples, list):
            return samples
        for item in raw_samples:
            input_data = ""
            output_data = ""
            # Luogu 历史数据有数组和对象两种形态，这里都兼容。
            if isinstance(item, list) and len(item) >= 2:
                input_data = str(item[0])
                output_data = str(item[1])
            elif isinstance(item, dict):
                input_data = str(item.get("input") or "")
                output_data = str(item.get("output") or "")
            if input_data or output_data:
                samples.append(Sample(input=input_data, output=output_data))
        return samples

    def problem_statement_markdown(
        self,
        display_id: str,
        title: str,
        problem: dict[str, Any],
        samples: list[Sample],
    ) -> tuple[str, int]:
        removed_total = 0

        def clean(text: str | None) -> str | None:
            nonlocal removed_total
            cleaned, removed = strip_anti_ai_blocks(text)
            removed_total += removed
            return cleaned

        sections = [f"# {display_id} {title}".strip(), ""]
        sections.append(markdown_section("题目背景", clean(problem.get("background"))))
        sections.append(markdown_section("题目描述", clean(problem.get("description"))))
        sections.append(markdown_section("输入格式", clean(self.first_text_field(problem, "inputFormat", "input", "formatI"))))
        sections.append(markdown_section("输出格式", clean(self.first_text_field(problem, "outputFormat", "output", "formatO"))))
        if samples:
            sample_parts = []
            for index, sample in enumerate(samples, start=1):
                sample_parts.append(
                    "\n".join(
                        [
                            f"## 输入输出样例 #{index}",
                            "",
                            f"### 输入 #{index}",
                            "",
                            "```",
                            sample.input.rstrip(),
                            "```",
                            "",
                            f"### 输出 #{index}",
                            "",
                            "```",
                            sample.output.rstrip(),
                            "```",
                        ]
                    )
                )
            sections.append("\n\n".join(sample_parts) + "\n")
        sections.append(markdown_section("说明/提示", clean(problem.get("hint"))))
        return "\n".join(part for part in sections if part != "").rstrip() + "\n", removed_total
