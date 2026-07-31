#!/usr/bin/env python3
"""Convert main.cpp (scanf/printf) -> main-cout.cpp (cin/cout) for OpenJudge problems."""

import re, os, glob
from copy import deepcopy

CPP_DIR = os.path.join(os.path.dirname(__file__) or '.', '..', 'problems', 'noi_openjudge')

# ── helpers ──────────────────────────────────────────

def split_args(args_str):
    args, depth, buf = [], 0, []
    for ch in args_str:
        if ch in '([{': depth += 1
        elif ch in ')]}': depth -= 1
        if ch == ',' and depth == 0:
            args.append(''.join(buf).strip())
            buf = []
        else:
            buf.append(ch)
    rest = ''.join(buf).strip()
    if rest: args.append(rest)
    return args

def strip_ampersand(a):
    a = a.strip()
    return a[1:] if a.startswith('&') else a

FMT_SPEC_RE = re.compile(
    r'%[#0\- +]*\*?[0-9]*(?:\.\*?[0-9]*)?[hlLzjt]*[diufFeEgGxXoscpaA]')

def fmt_spec_precision(spec):
    m = re.search(r'\.(\d+)', spec)
    return int(m.group(1)) if m else None

def is_float_spec(spec):
    return spec[-1] in 'fFeEgGaA'

def escape_cpp_literal(s):
    """Raw C++ string content → properly escaped C++ string literal content.
    Input is content between quotes of a C++ source string literal,
    where \\n etc are two raw chars (backslash+n)."""
    result, i = [], 0
    while i < len(s):
        if s[i] == '\\' and i+1 < len(s):
            n = s[i+1]
            if n in 'nrt0\\"':
                result.append(s[i:i+2])
                i += 2
            else:
                result.append('\\' + n)
                i += 2
        else:
            result.append('\\"' if s[i] == '"' else s[i])
            i += 1
    return ''.join(result)

# ── scanf / printf conversion (call only) ────────────

def extract_call(text, func):
    """Find func(...) with balanced parens (string/char-aware)."""
    idx = text.find(func + '(')
    if idx == -1: return None
    start = idx
    depth, i = 0, start + len(func)
    in_str = in_char = False
    while i < len(text):
        c = text[i]
        if c == '\\' and (in_str or in_char):
            i += 2  # skip escaped char
            continue
        if c == '"' and not in_char:
            in_str = not in_str
        elif c == "'" and not in_str:
            in_char = not in_char
        elif not in_str and not in_char:
            if c == '(':
                depth += 1
            elif c == ')':
                depth -= 1
                if depth == 0:
                    return (text[start:i+1], text[start+len(func)+1:i])
        i += 1
    return None

def extract_scanf_call(text):
    info = extract_call(text, 'scanf')
    if not info: return None
    full, inner = info
    # inner = '"fmt", args...'
    m = re.match(r'("[^"]*")\s*(?:,\s*(.*))?$', inner)
    if not m: return None
    fmt = m.group(1)
    args = split_args(m.group(2)) if m.group(2) else []
    return (full, fmt, args)

def extract_printf_call(text):
    info = extract_call(text, 'printf')
    if not info: return None
    full, inner = info
    m = re.match(r'("[^"]*")\s*(?:,\s*(.*))?$', inner)
    if not m: return None
    fmt = m.group(1)
    args = split_args(m.group(2)) if m.group(2) else []
    return (full, fmt, args)

def fmt_specs_list(fmt_content):
    return [(m.group(), m.start(), m.end()) for m in FMT_SPEC_RE.finditer(fmt_content)]

def wrap_expr(var):
    """Wrap expression if it contains operators that would break `<<` chaining."""
    if re.search(r'\?|<<|>>|&&|\|\|', var):
        return f'({var})'
    return var

def build_cin(fmt_content, scanf_args):
    """Build list of cin statement strings honoring scanf per-spec semantics.
    %c does NOT skip whitespace; %s/%d/%f DO skip leading whitespace.
    BUT a literal whitespace in the format string before %c (like " %c")
    makes scanf skip leading whitespace first. We replicate that."""
    specs = fmt_specs_list(fmt_content)
    chain = []
    statements = []
    need_skip = False  # whether next non-%c read needs explicit std::skipws
    for i, arg in enumerate(scanf_args):
        spec = specs[i][0] if i < len(specs) else ''
        spec_c = spec[-1] if spec else ''
        var = arg.strip()
        # look at literal format text between previous spec end and this spec
        prev_end = specs[i-1][2] if i > 0 and i < len(specs) else 0
        gap = fmt_content[prev_end:specs[i][1]] if i < len(specs) else ''
        skip_ws = bool(re.search(r'\s', gap))  # whitespace in format => skip
        if spec_c == 's':
            # %s: `&arr[i]` keeps & (element address); `&name` drops it
            if var.startswith('&') and not re.match(r'^&\s*\w+\s*\[', var):
                var = var[1:]
        else:
            var = strip_ampersand(var)
        if spec_c == 'c':
            if skip_ws:
                # scanf skips whitespace before this %c
                if need_skip:
                    chain.append('std::skipws')
                    need_skip = False
                chain.append(var)
            elif is_char_expr(var, CHAR_NAMES):
                chain.append('std::noskipws')
                need_skip = True
                chain.append(var)
            else:
                # non-char target: flush chain, use cin.get()
                if chain:
                    statements.append(' >> '.join(chain))
                    chain = []
                if skip_ws:
                    statements.append(f'{var} = std::cin.get()')
                else:
                    statements.append(f'{var} = std::cin.get()')
                need_skip = True
        else:
            if need_skip:
                chain.append('std::skipws')
                need_skip = False
            chain.append(var)
    if chain:
        statements.append(' >> '.join(chain))
    return statements

def build_cout(fmt_content, printf_args, char_names):
    """Build cout << ... list from printf format and args.
    char_names: set of identifiers known to be char/char-array (for %d casts)."""
    parts = []
    prev = 0
    arg_idx = 0
    need_iomanip = False

    for m in FMT_SPEC_RE.finditer(fmt_content):
        lit = fmt_content[prev:m.start()]
        if lit:
            lit = lit.replace('%%', '%')
            parts.append(f'"{escape_cpp_literal(lit)}"')
        prev = m.end()
        spec = m.group()
        prec = fmt_spec_precision(spec)
        var = printf_args[arg_idx]
        arg_idx += 1
        spec_c = spec[-1]

        # width / flags like %03d, %12d
        wm = re.search(r'%([#0\- +]*)(\d+)', spec)
        width = wm.group(2) if wm else None
        flags = wm.group(1) if wm else ''
        pad_zero = bool(width and '0' in flags and '-' not in flags)
        if pad_zero:
            need_iomanip = True
            parts.append('std::setfill(\'0\')')
        if width:
            need_iomanip = True
            parts.append(f'std::setw({width})')

        if spec_c == 'c':
            # printf %c prints the character; cast keeps semantics for int args
            parts.append(f'(char)({var})')
        elif is_float_spec(spec):
            need_iomanip = True
            if prec is not None:
                parts.append(f'std::fixed << std::setprecision({prec})')
            elif spec_c == 'g' or spec_c == 'G':
                parts.append('std::setprecision(6)')
            else:  # %f / %lf default 6 decimals
                parts.append('std::fixed << std::setprecision(6)')
            parts.append(wrap_expr(var))
        else:
            # integer formats: %d %i %ld %lld %o %x etc.
            base = re.sub(r'\*?[0-9]*', '', spec)
            if spec_c in 'oxX' and '0' not in flags:
                need_iomanip = True
                if spec_c == 'o': parts.append('std::oct')
                elif spec_c == 'x': parts.append('std::hex')
                elif spec_c == 'X': parts.append('std::hex << std::uppercase')
            if spec_c in 'diu' and is_char_expr(var, char_names):
                var = f'(int)({var})'
            parts.append(wrap_expr(var))

        if pad_zero:
            # restore default fill for subsequent fields
            parts.append('std::setfill(\' \')')

    trail = fmt_content[prev:]
    if trail:
        trail = trail.replace('%%', '%')
        parts.append(f'"{escape_cpp_literal(trail)}"')

    return parts, need_iomanip

def is_char_expr(var, char_names):
    """Heuristic: is var a char-typed expression (bare char id or char[] element)?"""
    var = var.strip()
    if re.match(r'^[A-Za-z_]\w*$', var):
        return var in char_names
    m = re.match(r'^([A-Za-z_]\w*)\[', var)
    if m:
        return m.group(1) in char_names
    return False

# ── line conversion dispatcher ──────────────────────

CHAR_NAMES = set()

def collect_char_names(lines):
    """Collect identifiers declared as char / char arrays."""
    names = set()
    for l in lines:
        l = re.sub(r'//.*', '', l)
        l = re.sub(r'/\*.*?\*/', '', l, flags=re.DOTALL)
        for m in re.finditer(r'\bchar\s+([A-Za-z_]\w*)\s*(?:\[|\s*[=,;])', l):
            names.add(m.group(1))
        # char *p; char c = ...; struct {...} ch;
        for m in re.finditer(r'\bchar\s+([A-Za-z_]\w*)\s*;', l):
            names.add(m.group(1))
    return names

def convert_line(line, lines, idx):
    """Try to convert a line. Returns (new_lines_list, need_iomanip_flag) or None."""
    stripped = line.strip()
    next_line = lines[idx+1] if idx+1 < len(lines) else ''

    # ── pattern A: while ( scanf(...) != EOF ) {  /  while ( scanf(...) ) { ──
    mw = re.match(r'(\s*)while\s*\(\s*scanf\(("[^"]*")\s*,\s*(.*?)\s*\)\s*(?:!=\s*(?:EOF|-1)\s*)?\)\s*(\{?)', line)
    if mw:
        indent, fmt, args_str, brace = mw.group(1), mw.group(2), mw.group(3), mw.group(4) or ''
        args = split_args(args_str)
        stmts = build_cin(fmt[1:-1], args)
        if len(stmts) == 1 and '=' not in stmts[0]:
            return [f'{indent}while (std::cin >> {stmts[0]}){brace}\n'], False
        # multi-statement / get() fallback: wrap in while(1){... if(!cin)break;}
        body = '\n'.join(f'{indent}    {s};' for s in stmts)
        return [f'{indent}while (1){brace}\n',
                f'{body}\n',
                f'{indent}    if (!std::cin) break;\n',
                f'{indent}}}\n'], False

    # ── pattern B: int VAR = scanf(...); → int VAR = (cin >> var) ? N : -1; ──
    mr = re.match(r'(\s*)int\s+(\w+)\s*=\s*scanf\(("[^"]*")\s*(?:,\s*(.*))?\s*\)\s*;', line)
    if mr:
        indent, varname, fmt, args_str = mr.group(1), mr.group(2), mr.group(3), mr.group(4) or ''
        args = split_args(args_str) if args_str.strip() else []
        stmts = build_cin(fmt[1:-1], args)
        if len(stmts) == 1 and '=' not in stmts[0]:
            n_args = len(args)
            new_line = f'{indent}int {varname} = (std::cin >> {stmts[0]}) ? {n_args} : -1;\n'
            return [new_line], False
        # fallback for get()-based reads
        body = '\n'.join(f'{indent}    {s};' for s in stmts)
        return [f'{indent}int {varname};\n',
                f'{indent}if (!(std::cin)) {{ {varname} = -1; }}\n',
                f'{body}\n'], False

    # ── pattern C: plain scanf("...", &args...);  (possibly with leading code) ──
    if 'scanf(' in line:
        info = extract_scanf_call(line)
        if info:
            full_call, fmt, args = info
            if args:
                stmts = build_cin(fmt[1:-1], args)
                full_stmts = [s if '=' in s else f'std::cin >> {s}' for s in stmts]
                new_call = ';\n'.join(full_stmts)
                new_line = line.replace(full_call, new_call)
                # if line ends with semicolon after replacement, good
                return [new_line], False

    # ── pattern D: printf("...", args...);  (possibly with leading code, trailing comments) ──
    if 'printf(' in line:
        info = extract_printf_call(line)
        if info:
            full_call, fmt, args = info
            fmt_content = fmt[1:-1]  # remove quotes
            spec_count = len(list(FMT_SPEC_RE.finditer(fmt_content)))
            if spec_count == len(args):
                cout_parts, ni = build_cout(fmt_content, args, CHAR_NAMES)
                cout_expr = ' << '.join(cout_parts)
                new_call = f'std::cout << {cout_expr}'
                new_line = line.replace(full_call, new_call)
                # Clean up trailing semicolons/comments
                new_line = re.sub(r';\s*;\s*$', ';', new_line)
                new_line = re.sub(r';\s*//.*$', ';', new_line)
                return [new_line], ni
            elif spec_count == 0 and not args:
                # printf("literal only")
                cout_expr = f'std::cout << "{escape_cpp_literal(fmt_content)}"'
                new_line = line.replace(full_call, cout_expr)
                return [new_line], False

    return None

# ── file-level processing ────────────────────────────

def convert_file(cpp_path, cout_path):
    global CHAR_NAMES
    with open(cpp_path) as f:
        content = f.read()
    lines = content.splitlines(keepends=True)

    has_scanf = any('scanf(' in l for l in lines)
    has_printf = any('printf(' in l for l in lines)
    if not has_scanf and not has_printf:
        return False

    CHAR_NAMES = collect_char_names(lines)

    need_iomanip_flag = False
    new_lines = []
    skip_next = False

    for i, line in enumerate(lines):
        if skip_next:
            skip_next = False
            continue

        # Skip cstdio includes
        if re.match(r'#include\s*<cstdio>', line):
            continue

        result = convert_line(line, lines, i)
        if result:
            conv, ni = result
            need_iomanip_flag = need_iomanip_flag or ni
            # Check if result consumed next line
            orig_len = len(lines[i])
            has_newline = line.endswith('\n')
            if len(conv) > 0 and conv != [line]:
                # Check if we consumed the next line
                # The convert_line might return 2 lines (handling if-break)
                if len(conv) >= 2:
                    skip_next = True
                new_lines.extend(conv)
                continue
        new_lines.append(line)

    # Add includes
    has_iostream = any(re.match(r'#include\s*<(?:iostream|bits/stdc\+\\+\.h)>', l) for l in new_lines)
    has_iomanip = any(re.match(r'#include\s*<iomanip>', l) for l in new_lines)
    has_bits = any(re.match(r'#include\s*<bits/stdc\+\+\.h>', l) for l in new_lines)

    # Find insertion point after existing includes
    ins = 0
    for j, l in enumerate(new_lines):
        if re.match(r'#include\s*<', l):
            ins = j + 1
        else:
            break

    if need_iomanip_flag and not has_iomanip and not has_bits:
        new_lines.insert(ins, '#include <iomanip>\n')
        ins += 1
    if not has_iostream and not has_bits:
        new_lines.insert(ins, '#include <iostream>\n')
        ins += 1

    # `using namespace std;` policy
    # 1) Never ADD it: converted code always uses std:: prefix, and adding it
    #    risks clashes with min/max/size/... pulled in by <iostream>.
    # 2) If the ORIGINAL had it, keep it UNLESS a user global/function collides
    #    with a std name (then the directive is what causes the ambiguity).
    has_using = any(re.match(r'\s*using\s+namespace\s+std\s*;', l) for l in new_lines)
    if has_using:
        CONFLICT_NAMES = {'min','max','size','greater','less','clock','data',
                          'time','swap','sort','reverse','find','count','copy',
                          'begin','end','next','prev','unique','fill','clear'}
        def user_global_collides():
            full = ''.join(new_lines)
            full = re.sub(r'//.*', '', full)
            full = re.sub(r'/\*.*?\*/', '', full, flags=re.DOTALL)
            # global variable declarations / function definitions
            pat = re.compile(
                r'^\s*(?:typedef\s+)?(?:int|long|short|bool|char|double|float|'
                r'unsigned|auto|struct\s+\w+|class\s+\w+)\s+'
                r'(' + '|'.join(CONFLICT_NAMES) + r')\b', re.MULTILINE)
            if pat.search(full):
                return True
            for n in CONFLICT_NAMES:
                if re.search(rf'\b(?:void|bool|int|char|double|float|long)\s+{n}\s*\(', full):
                    return True
            return False
        if user_global_collides():
            new_lines = [l for l in new_lines
                         if not re.match(r'\s*using\s+namespace\s+std\s*;', l)]

    # Fix conflict: user-defined `clock` collides with clock() from <ctime>
    # (pulled in transitively by <iostream>). Rename it and call sites.
    if re.search(r'\b(?:void\s+)?clock\s*\(', content) and not re.search(r'std::clock\b', content):
        new_lines = [l.replace('anti_clock', 'anti_clock_op')
                      .replace('clock', 'clock_op') for l in new_lines]

    with open(cout_path, 'w') as f:
        f.writelines(new_lines)
    return True

# ── main ─────────────────────────────────────────────

def main():
    pattern = os.path.join(CPP_DIR, '**', 'main.cpp')
    all_files = sorted(glob.glob(pattern, recursive=True))

    converted, skipped, already = 0, 0, 0
    errors = []

    for cpp_path in all_files:
        cout_path = os.path.join(os.path.dirname(cpp_path), 'main-cout.cpp')
        if os.path.exists(cout_path):
            already += 1
            continue
        try:
            ok = convert_file(cpp_path, cout_path)
            (converted if ok else skipped).__add__(1)  # not used, use standard
            if ok: converted += 1
            else: skipped += 1
        except Exception as e:
            errors.append((cpp_path, str(e)))
            skipped += 1

    print(f"Created: {converted}  Skipped (no scanf/printf): {skipped}  Already existed: {already}")
    for path, err in errors:
        print(f"  ERROR {path}: {err}")

if __name__ == '__main__':
    main()
