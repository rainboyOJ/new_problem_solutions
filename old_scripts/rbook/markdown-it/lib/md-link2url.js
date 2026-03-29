// md-link2url.js
// 用于将 Markdown 中的相对 .md 链接转换为实际的 URL

import path from 'path';

/**
 * 将 Markdown 中的相对 .md 链接转换为实际的 URL
 * @param {Object} md - markdown-it 实例
 * @param {Object} options - 配置选项
 * @param {string} options.baseDir - 项目的根目录，用于解析相对路径
 * @param {string} options.baseUrl - 生成 URL 时的基础 URL
 */
function mdLink2Url(md, options = {}) {
  const { baseDir = '.', baseUrl = '' } = options;

  // 保存原始的链接渲染规则
  const defaultRender = md.renderer.rules.link_open || function(tokens, idx, opts, env, self) {
    return self.renderToken(tokens, idx, opts);
  };

  // 重写链接打开标签的渲染规则
  md.renderer.rules.link_open = function (tokens, idx, opts, env, self) {
    const token = tokens[idx];
    
    // 确保 token 有 attrIndex 方法
    if (typeof token.attrIndex !== 'function') {
      return defaultRender(tokens, idx, opts, env, self);
    }
    
    const hrefIndex = token.attrIndex('href');
    
    // 如果没有 href 属性，则使用默认渲染
    if (hrefIndex < 0) {
      return defaultRender(tokens, idx, opts, env, self);
    }

    let href = token.attrs[hrefIndex][1];
    
    // 检查是否是相对路径的 .md 文件
    if (href && href.endsWith('.md') && (href.startsWith('./') || href.startsWith('../'))) {
      // console.log('-----> href', href)
      // 解析相对于当前文件的绝对路径
      const currentFilePath = env.filePath || '';
      const absolutePath = path.resolve(path.dirname(currentFilePath), href);
      
      // 计算相对于项目根目录的路径
      const relativePath = path.relative(baseDir, absolutePath);
      // console.log(baseDir, absolutePath)
      // console.log('-----> relativePath', relativePath)
      
      // 将 .md 扩展名替换为 .html
      const urlPath = relativePath.replace(/\.md$/, '.html');
      
      // 构造最终的 URL
      const finalUrl = path.join(baseUrl, urlPath).replace(/\\/g, '/');
      // console.log('-----> finalUrl', finalUrl)
      
      // 更新 href 属性
      token.attrs[hrefIndex][1] = finalUrl;
    }
    
    // 使用默认渲染器渲染修改后的 token
    return defaultRender(tokens, idx, opts, env, self);
  };
};

export default mdLink2Url;