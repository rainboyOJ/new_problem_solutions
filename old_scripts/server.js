import http from 'http';
import fs from 'fs';
import path from 'path';
import { fileURLToPath } from 'url';
import { dirname } from 'path';

// 获取当前文件的目录路径
const __filename = fileURLToPath(import.meta.url);
const __dirname = dirname(__filename);
const __workdir = path.join(__dirname, '../');

import rbook from './rbook/index.js';
import markdown from './rbook/markdown.js';
import { nunjucksRender } from './rbook/renderEngine.js';

// 创建rbook实例
const app = new rbook();

// WebSocket服务器
let wss = null;

// 内存缓存
const cache = {
  config: null,
  assets: {},
  pages: {}
};



/**
 * 获取文件的MIME类型
 * @param {string} filePath - 文件路径
 * @returns {string} - MIME类型
 */
function getMimeType(filePath) {
  const ext = path.extname(filePath).toLowerCase();
  const mimeTypes = {
    '.html': 'text/html',
    '.css': 'text/css',
    '.js': 'application/javascript',
    '.json': 'application/json',
    '.png': 'image/png',
    '.jpg': 'image/jpeg',
    '.jpeg': 'image/jpeg',
    '.gif': 'image/gif',
    '.svg': 'image/svg+xml',
    '.ico': 'image/x-icon'
  };
  return mimeTypes[ext] || 'text/plain';
}

/**
 * 加载配置文件到内存
 */
function loadConfigToMemory() {
  try {
    cache.config = app.load_config();
    console.log('✓ 配置加载到内存');
  } catch (error) {
    console.error('配置加载失败:', error.message);
    throw error;
  }
}

/**
 * 加载主题资源到内存
 */
function loadAssetsToMemory() {
  // 加载CSS文件
  const cssPath = path.join(__workdir, 'theme/assets/css/style.css');
  if (fs.existsSync(cssPath)) {
    cache.assets['/assets/css/style.css'] = fs.readFileSync(cssPath, 'utf8');
    console.log('✓ CSS资源加载到内存');
  }

  // 加载JS文件
  const jsPath = path.join(__workdir, 'theme/assets/js/main.js');
  if (fs.existsSync(jsPath)) {
    cache.assets['/assets/js/main.js'] = fs.readFileSync(jsPath, 'utf8');
    console.log('✓ JS资源加载到内存');
  }
}

/**
 * 根据URL路径获取对应的Markdown文件路径
 * @param {string} url - 请求的URL
 * @returns {Object} - { filePath, templateType }
 */
function getMarkdownFileFromUrl(url) {
  if (url === '/' || url === '/index.html') {
    return { filePath: path.join(__workdir, 'book/index.md'), templateType: 'index' };
  } else if (url === '/about.html') {
    return { filePath: path.join(__workdir, 'book/about.md'), templateType: 'page' };
  } else if (url.endsWith('/')) {
    // 章节页面
    const chapterPath = url.slice(1, -1); // 移除首尾的斜杠
    return { 
      filePath: path.join(__workdir, `book/${chapterPath}/index.md`), 
      templateType: 'chapter' 
    };
  } else if (url.endsWith('.html')) {
    // 其他HTML页面
    const pagePath = url.slice(1, -5); // 移除首尾的斜杠和.html
    return { 
      filePath: path.join(__workdir, `book/${pagePath}.md`), 
      templateType: 'page' 
    };
  }
  return null;
}

/**
 * 渲染页面到内存
 * @param {string} filePath - Markdown文件路径
 * @returns {string} - 渲染后的HTML
 */
function renderPageToMemory(filePath, templateType) {
  try {
    if (!fs.existsSync(filePath)) {
      throw new Error(`文件不存在: ${filePath}`);
    }

    // 创建Markdown实例
    const md = new markdown(filePath);
    
    // 确定模板类型
    const layoutType = md.front_matter.layout || templateType || 'page';
    
    // 使用Nunjucks渲染模板
    const htmlContent = nunjucksRender(
      path.join(__workdir, 'theme'), 
      layoutType, 
      {
        ...md.toJSON(), 
        site: cache.config
      }
    );
    
    cache.pages[filePath] = {
      html: htmlContent,
      timestamp: Date.now()
    };
    
    return htmlContent;
  } catch (error) {
    console.error(`页面渲染失败: ${filePath}`, error.message);
    throw error;
  }
}

/**
 * 处理HTTP请求
 * @param {http.IncomingMessage} req - 请求对象
 * @param {http.ServerResponse} res - 响应对象
 */
function handleRequest(req, res) {
  const url = req.url;
  
  // 处理静态资源请求
  if (url.startsWith('/assets/')) {
    const assetPath = path.join(__workdir, 'theme', url);
    if (fs.existsSync(assetPath)) {
      const mimeType = getMimeType(assetPath);
      const content = fs.readFileSync(assetPath, 'utf8');
      res.writeHead(200, { 
        'Content-Type': mimeType,
        'Cache-Control': 'no-cache'
      });
      res.end(content);
    } else {
      res.writeHead(404, { 'Content-Type': 'text/html' });
      res.end('<h1>404 Not Found</h1><p>资源不存在</p>');
    }
    return;
  }

  // 处理页面请求
  const pageInfo = getMarkdownFileFromUrl(url);
  
  if (!pageInfo) {
    res.writeHead(404, { 'Content-Type': 'text/html' });
    res.end('<h1>404 Not Found</h1><p>页面不存在</p>');
    return;
  }

  try {
    // 检查缓存是否有效
    let html;
    if (cache.pages[pageInfo.filePath] && 
        Date.now() - cache.pages[pageInfo.filePath].timestamp < 5000) { // 5秒缓存
      html = cache.pages[pageInfo.filePath].html;
      console.log(`✓ 使用缓存: ${url} -> ${pageInfo.filePath}`);
    } else {
      // 渲染页面
      html = renderPageToMemory(pageInfo.filePath, pageInfo.templateType);
      console.log(`✓ 渲染完成: ${url} -> ${pageInfo.filePath}`);
    }
    
    // 注入WebSocket客户端代码
    const injectedHtml = injectWebSocketClient(html);
    
    res.writeHead(200, { 
      'Content-Type': 'text/html',
      'Cache-Control': 'no-cache'
    });
    res.end(injectedHtml);
  } catch (error) {
    res.writeHead(500, { 'Content-Type': 'text/html' });
    res.end(`<h1>500 Internal Server Error</h1><p>${error.message}</p>`);
  }
}

/**
 * 注入WebSocket客户端代码
 * @param {string} html - 原始HTML
 * @returns {string} - 注入WebSocket代码后的HTML
 */
function injectWebSocketClient(html) {
  const wsClientScript = `
    <script>
      (function() {
        const ws = new WebSocket('ws://localhost:3000');
        
        ws.onopen = function() {
          console.log('WebSocket连接已建立');
        };
        
        ws.onmessage = function(event) {
          const data = JSON.parse(event.data);
          if (data.type === 'reload') {
            console.log('文件已更新，正在刷新页面...');
            location.reload();
          }
        };
        
        ws.onclose = function() {
          console.log('WebSocket连接已关闭');
        };
        
        ws.onerror = function(error) {
          console.error('WebSocket错误:', error);
        };
      })();
    </script>
  `;
  
  // 将WebSocket客户端代码注入到HTML的body结束标签前
  return html.replace('</body>', wsClientScript + '</body>');
}

/**
 * 监听文件变化
 */
function setupFileWatchers() {
  // 监听Markdown文件变化
  const bookDir = path.join(__workdir, 'book');
  if (fs.existsSync(bookDir)) {
    fs.watch(bookDir, { recursive: true }, (eventType, filename) => {
      if (filename && filename.endsWith('.md') && !filename.startsWith('.')) {
        const filePath = path.join(bookDir, filename);
        console.log(`Markdown文件变化: ${filename}`);
        
        // 清除缓存，下次请求时重新渲染
        delete cache.pages[filePath];
        console.log(`✓ 缓存已清除: ${filePath}`);
        
        // 通知所有客户端刷新页面
        notifyClients();
      }
    });
  }

  // 监听主题文件变化
  const themeDir = path.join(__workdir, 'theme');
  if (fs.existsSync(themeDir)) {
    fs.watch(themeDir, { recursive: true }, (eventType, filename) => {
      if (filename && !filename.startsWith('.')) {
        console.log(`主题文件变化: ${filename}`);
        
        // 重新加载资源并清除所有页面缓存
        loadAssetsToMemory();
        cache.pages = {};
        console.log('✓ 所有页面缓存已清除，资源已重新加载');
        
        // 通知所有客户端刷新页面
        notifyClients();
      }
    });
  }

  // 监听配置文件变化
  const configPath = path.join(__workdir, 'book.yaml');
  if (fs.existsSync(configPath)) {
    fs.watchFile(configPath, () => {
      console.log('配置文件变化');
      
      // 重新加载配置并清除所有页面缓存
      loadConfigToMemory();
      cache.pages = {};
      console.log('✓ 配置已重新加载，所有页面缓存已清除');
      
      // 通知所有客户端刷新页面
      notifyClients();
    });
  }
}

/**
 * 通知所有客户端刷新页面
 */
function notifyClients() {
  if (!wss) return;
  
  const message = JSON.stringify({ type: 'reload' });
  
  // 向所有客户端发送刷新消息
  wss.clients.forEach(client => {
    if (client.readyState === WebSocket.OPEN) {
      client.send(message);
    }
  });
}

/**
 * 启动开发服务器
 * @param {number} port - 端口号
 */
async function serve(port = 3000) {
  // 初始化内存缓存
  console.log('正在初始化内存缓存...');
  try {
    loadConfigToMemory();
    loadAssetsToMemory();
    console.log('✓ 内存缓存初始化完成');
  } catch (error) {
    console.error('初始化失败:', error.message);
    console.log('继续启动服务器，但可能无法正常显示内容');
  }

  // 创建HTTP服务器
  const server = http.createServer(handleRequest);

  // 动态导入WebSocket库
  const { WebSocketServer } = await import('ws');
  
  // 创建WebSocket服务器
  wss = new WebSocketServer({ server });

  wss.on('connection', (ws) => {
    console.log('WebSocket客户端已连接');
    
    ws.on('message', (message) => {
      // 不需要处理客户端发来的消息
    });
    
    ws.on('close', () => {
      console.log('WebSocket客户端已断开连接');
    });
  });

  server.listen(port, () => {
    console.log(`开发服务器已启动`);
    console.log(`访问地址: http://localhost:${port}`);
    console.log('按 Ctrl+C 停止服务器');
  });

  // 设置文件监听
  setupFileWatchers();
}

// 如果直接运行此文件，则启动服务器
if (import.meta.url === `file://${process.argv[1]}`) {
  const port = process.argv[2] ? parseInt(process.argv[2]) : 3000;
  serve(port).catch(error => {
    console.error('服务器启动失败:', error);
    process.exit(1);
  });
}

export { 
  serve
};