// 容器图标用内联 SVG，不再走 twemoji 的外链图片：
// 一是外部 CDN 不可靠（Prism 已经因此改成全本地），
// 二是 emoji 是位图，跨平台/跨主题的观感完全不可控，
// 三是 emoji 无法只给灯丝上色，做不出「灯泡在发光」的层次。
const ICONS = {
  // 灯泡：info。灯罩用 currentColor 描边，灯丝单独上暖黄。
  info: '<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" fill="none" aria-hidden="true" focusable="false">'
    + '<path d="M12 2a7 7 0 0 0-4 12.75V17a1 1 0 0 0 1 1h6a1 1 0 0 0 1-1v-2.25A7 7 0 0 0 12 2Z"'
    + ' stroke="currentColor" stroke-width="1.7" stroke-linejoin="round"/>'
    + '<path class="container-icon__filament" d="M9.5 9.5a2.5 2.5 0 0 1 5 0c0 1-.5 1.5-1 2"'
    + ' stroke="currentColor" stroke-width="1.7" stroke-linecap="round" fill="none"/>'
    + '<path d="M9.5 20.5h5" stroke="currentColor" stroke-width="1.7" stroke-linecap="round"/>'
    + '<path d="M10.5 22.5h3" stroke="currentColor" stroke-width="1.7" stroke-linecap="round"/>'
    + '</svg>',
  // 警示三角：warning
  warning: '<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" fill="none" aria-hidden="true" focusable="false">'
    + '<path d="M12 3.2 21.3 20H2.7Z" stroke="currentColor" stroke-width="1.7" stroke-linejoin="round"/>'
    + '<path d="M12 9.5v4.6" stroke="currentColor" stroke-width="1.8" stroke-linecap="round"/>'
    + '<circle cx="12" cy="17" r="1.05" fill="currentColor"/>'
    + '</svg>',
  // 圆圈叉：error
  error: '<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" fill="none" aria-hidden="true" focusable="false">'
    + '<circle cx="12" cy="12" r="9" stroke="currentColor" stroke-width="1.7"/>'
    + '<path d="M9 9l6 6M15 9l-6 6" stroke="currentColor" stroke-width="1.8" stroke-linecap="round"/>'
    + '</svg>',
};

const default_container = [
  { matcher: /^warning/, className: 'warning', title: '注意', icon: ICONS.warning },
  { matcher: /^error/, className: 'error', title: '错误', icon: ICONS.error },
  { matcher: /^info/, className: 'info', title: '提示', icon: ICONS.info },
];

// `::: info 这里的文字` 里的文字原本被静默丢弃。现在取出来当标题渲染，
// 没写标题时退回该类型的默认标题。
function parseTitle(params, rule) {
  const match = params.trim().match(/^\S+\s+(.*)$/s);
  const custom = match ? match[1].trim() : '';
  return custom || rule.title;
}

export default function createDefaultContainer(md) {
  return [
    'default',
    {
      validate(params) {
        const value = params.trim();
        return default_container.some((rule) => rule.matcher.test(value));
      },
      render(tokens, idx, _options, env) {
        const params = tokens[idx].info.trim();
        const rule = default_container.find((item) => item.matcher.test(params));

        if (!rule) return '</div>\n';
        if (tokens[idx].nesting !== 1) return '</div>\n';

        // 标题支持行内 Markdown 与 $...$ 公式：走一遍 inline 渲染，
        // 否则 `::: info 复杂度 $O(1)$` 会把美元原样吐在标题里。
        const title = parseTitle(params, rule);
        const titleHtml = md.renderInline(title, env);

        return `<div class="container-block ${rule.className}">`
          + `<div class="container-title"><span class="container-icon">${rule.icon}</span>`
          + `<span class="container-title__text">${titleHtml}</span></div>\n`;
      },
    },
  ];
}
