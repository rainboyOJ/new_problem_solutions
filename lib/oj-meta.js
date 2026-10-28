// OJ 的展示元数据：显示名、图标、字母徽章兜底。
//
// 题目 frontmatter 里的 `oj` 字段是「目录名式」的原始值，历史上大小写并不统一
// （例如 codeforces 与 CodeForces 并存，另有两个未加引号的 roj）。这里用一张
// 集中表把它们都归一到同一个规范键，页面上只读这张表，不再直接展示原始值。
//
// 图标统一存放在 public/icons/oj/*.png，已离线化为 64x64 PNG：
// 主题切换、断网、VJudge 改版都不会让图标失效。
const OJ_TABLE = {
  roj: {
    name: 'RainboyOJ',
    icon: 'roj.png',
    badge: 'R',
    color: 'roj',
  },
  luogu: {
    name: '洛谷',
    icon: 'luogu.png',
    badge: '洛',
    color: 'luogu',
  },
  noi_openjudge: {
    name: 'NOI OpenJudge',
    icon: null,
    badge: 'N',
    color: 'noi-openjudge',
  },
  shumeng: {
    name: '曙梦 OJ',
    icon: null,
    badge: '曙',
    color: 'shumeng',
  },
  leetcodecn: {
    name: '力扣',
    icon: 'leetcodecn.png',
    badge: '力',
    color: 'leetcode',
  },
  usaco: {
    name: 'USACO',
    icon: 'usaco.png',
    badge: 'U',
    color: 'usaco',
  },
  HDU: {
    name: 'HDU',
    icon: 'hdu.png',
    badge: 'H',
    color: 'hdu',
  },
  atcoder: {
    name: 'AtCoder',
    icon: 'atcoder.png',
    badge: 'A',
    color: 'atcoder',
  },
  OpenJ_Bailian: {
    name: 'OpenJudge Bailian',
    icon: 'bailian.png',
    badge: 'OB',
    color: 'bailian',
  },
  POJ: {
    name: 'POJ',
    icon: 'poj.png',
    badge: 'P',
    color: 'poj',
  },
  codeforces: {
    name: 'Codeforces',
    icon: 'codeforces.png',
    badge: 'CF',
    color: 'codeforces',
  },
  kattis: {
    name: 'Kattis',
    icon: 'kattis.png',
    badge: 'K',
    color: 'kattis',
  },
  acwing: {
    name: 'AcWing',
    icon: 'acwing.png',
    badge: 'AW',
    color: 'acwing',
  },
  uva: {
    name: 'UVa',
    icon: 'uva.png',
    badge: 'UV',
    color: 'uva',
  },
  '51Node': {
    name: '51Nod',
    icon: '51nod.png',
    badge: '51',
    color: '51nod',
  },
};

// 数据里出现过的大小写/拼写变体，统一折叠到 OJ_TABLE 的键。
// 只影响展示与筛选，不改动任何 index.md。
const OJ_ALIASES = {
  codeforces: 'codeforces',
  codeoforces: 'codeforces',
  hdu: 'HDU',
  poj: 'POJ',
  openj_bailian: 'OpenJ_Bailian',
  openjudge_bailian: 'OpenJ_Bailian',
  '51node': '51Node',
  '51nod': '51Node',
  roj: 'roj',
  luogu: 'luogu',
  noi_openjudge: 'noi_openjudge',
  shumeng: 'shumeng',
  leetcodecn: 'leetcodecn',
  usaco: 'usaco',
  atcoder: 'atcoder',
  kattis: 'kattis',
  acwing: 'acwing',
  uva: 'uva',
};

const UNKNOWN_COLOR = 'unknown';

// 把原始 oj 值归到这个模块的规范键；查不到就返回 null，由调用方决定怎么兜底。
export function resolveOJKey(rawOJ) {
  const raw = String(rawOJ ?? '').trim();
  if (!raw) {
    return null;
  }
  if (Object.hasOwn(OJ_TABLE, raw)) {
    return raw;
  }
  const aliased = OJ_ALIASES[raw.toLowerCase()];
  if (aliased && Object.hasOwn(OJ_TABLE, aliased)) {
    return aliased;
  }
  return null;
}

// 取某个 oj 的展示信息。任何未登记的 OJ 都退回「原始值 + 字母徽章」，
// 这样新增 OJ 时页面不会崩，也不会出现空白单元格。
export function getOJMeta(rawOJ) {
  const raw = String(rawOJ ?? '').trim();
  const key = resolveOJKey(raw);
  if (key) {
    const entry = OJ_TABLE[key];
    return {
      key,
      raw,
      name: entry.name,
      icon: entry.icon ? `/icons/oj/${entry.icon}` : null,
      badge: entry.badge,
      color: entry.color,
      known: true,
    };
  }
  const fallbackName = raw || '未知 OJ';
  return {
    key: raw ? raw.toLowerCase() : '',
    raw,
    name: fallbackName,
    icon: null,
    badge: fallbackName.slice(0, 2).toUpperCase(),
    color: UNKNOWN_COLOR,
    known: false,
  };
}

// 归并后的 OJ 筛选项：同一个 OJ 的不同拼写只出现一次。
// values 保留原始值集合，供路由按原始值过滤时使用。
export function buildOJOptions(rawOJList) {
  const byKey = new Map();
  for (const rawOJ of rawOJList) {
    const trimmed = String(rawOJ ?? '').trim();
    if (!trimmed) {
      continue;
    }
    const meta = getOJMeta(trimmed);
    const existing = byKey.get(meta.key);
    if (existing) {
      existing.values.add(trimmed);
      continue;
    }
    byKey.set(meta.key, {
      key: meta.key,
      name: meta.name,
      icon: meta.icon,
      badge: meta.badge,
      color: meta.color,
      values: new Set([trimmed]),
    });
  }
  return Array.from(byKey.values())
    .map((option) => ({ ...option, values: Array.from(option.values) }))
    .sort(compareOJOptions);
}

// 排序：拉丁字母名先按不区分大小写的字母序，中文名统一排到后面按拼音序。
// 不这么分两段的话，中文名会按拼音插进拉丁名中间（li 落在 Kattis 后、luo 落在 POJ 后），
// 整个下拉看着像断断续续的两三截。
const HAN_PATTERN = /\p{Script=Han}/u;

function isHanName(name) {
  return HAN_PATTERN.test(name);
}

function compareOJOptions(a, b) {
  const aHan = isHanName(a.name);
  const bHan = isHanName(b.name);
  if (aHan !== bHan) {
    return aHan ? 1 : -1;
  }
  return a.name.localeCompare(b.name, aHan ? 'zh-Hans-CN' : 'en', {
    sensitivity: 'base',
  });
}

// 判断某个题目的原始 oj 是否属于「选中项」。selectOJ 可能是规范键，也可能
// 是历史链接里带的原始值（例如 oj=CodeForces），两种都要能命中。
export function ojMatchesSelection(rawOJ, selectedOJ) {
  const selected = String(selectedOJ ?? '').trim();
  if (!selected) {
    return true;
  }
  const raw = String(rawOJ ?? '').trim();
  if (raw === selected) {
    return true;
  }
  const rawKey = resolveOJKey(raw) || raw.toLowerCase();
  const selectedKey = resolveOJKey(selected) || selected.toLowerCase();
  return rawKey === selectedKey;
}
