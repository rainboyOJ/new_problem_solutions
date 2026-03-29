import fs from 'fs';
import path from 'path';
import yaml from 'js-yaml';
import { glob, globSync, globStream, globStreamSync, Glob } from 'glob'
import { fileURLToPath } from 'url';
import { dirname } from 'path';
import { nunjucksRender } from './renderEngine.js';
import markdown from './markdown.js';

// 获取当前文件的目录路径
export const __filename = fileURLToPath(import.meta.url);
export const __dirname = dirname(__filename);
export const __workdir = path.join(__dirname, '../../');
export const __bookdir = path.join(__workdir, 'book');
export const __code_template_dir = path.join(__workdir, 'code');
export const __themedir = path.join(__workdir, 'theme');

class rbook {
    constructor() {
        this.name = 'rbook';
        this.config = this.load_config();
        this.config.currentYear = new Date().getFullYear();
        // this.config.last_build_time = new Date().toLocaleString();
        this.config.last_build_time = new Date().toLocaleString('zh-CN', { timeZone: 'Asia/Shanghai' });
    }

    load_config(configPath = 'book.yaml') {
        try {
            const configFile = path.join(__workdir, configPath);
            if (!fs.existsSync(configFile)) {
                throw new Error(`配置文件不存在: ${configPath}`);
            }
            
            const content = fs.readFileSync(configFile, 'utf8');
            return yaml.load(content);
        } catch (error) {
            throw new Error(`加载配置文件失败: ${error.message}`);
        }
    }

    /**
     * 
     * @param {*} filePath 
     * @param {*} outputPath 
     * @param {*} defaultTemplateType 
     * @param {*} data 渲染文件所需要的数据
     * @returns 
     */
    buildMarkdownFile (filePath, outputPath, defaultTemplateType = null,data = {}) {
        const fullPath = path.join(__bookdir, filePath);
        if (fs.existsSync(fullPath)) {
            // 确保输出目录存在
            const fullOutputPath = path.join(__workdir, outputPath);
            const outputDir = path.dirname(fullOutputPath);
            if (!fs.existsSync(outputDir)) {
                fs.mkdirSync(outputDir, { recursive: true });
            }

            let md = new markdown(fullPath);

            // 确定模板类型
            const templateType = md.front_matter.layout || defaultTemplateType || 'page';
            
            // 使用Nunjucks渲染模板
            const htmlContent = nunjucksRender(__themedir, templateType, {...md.toJSON(), site: this.config, ...data});
            
            // 写入HTML文件
            fs.writeFileSync(fullOutputPath, htmlContent);
            console.log(`✓ 构建完成: ${filePath}`);
            return true;
        }
        else {
            console.error(`✗ 文件不存在: ${filePath}`);
        }
        return false;
    };

    /**
     * 检查给定路径的Markdown文件是否存在
     * @param {string} basePath - 基础路径 (如 'chapter1')
     * @param {string} relativePath - 相对于基础路径的路径 (如 'multiple-knapsack')
     * @returns {string|null} - 找到的文件路径或null
     */
    checkMarkdownFile(basePath, relativePath) {
        // 构建完整路径
        const fullPath = path.join(__bookdir, basePath, relativePath);
        
        // 首先检查是否是一个目录
        if (fs.existsSync(fullPath) && fs.statSync(fullPath).isDirectory()) {
            // 如果是目录，检查目录下的index.md文件
            const indexPath = path.join(fullPath, 'index.md');
            if (fs.existsSync(indexPath)) {
                return path.join(basePath, relativePath, 'index.md');
            }
        } else if ( fullPath.endsWith('.md') && fs.existsSync(fullPath) ) {
            return path.join(basePath, relativePath);
        } else {
            // 如果不是目录，检查同名的.md文件
            const mdPath = fullPath + '.md';
            if (fs.existsSync(mdPath)) {
                return path.join(basePath, relativePath + '.md');
            }
        }
        
        return null;
    }

    /**
     * 递归获取章节中的所有Markdown文件
     * @param {Array} chapters - 章节配置数组
     * @param {string} basePath - 基础路径
     * @returns {Array} - Markdown文件路径数组
     */
    getAllMarkdownFiles(chapters, basePath = '') {
        const files = [];
        
        if (!chapters || !Array.isArray(chapters)) {
            return files;
        }
        
        for (const chapter of chapters) {
            // 没有path的章节不处理
            if( !chapter.path ) continue;
            //if( chapter.type === 'info' ) continue; // info 是一个分割符,在目录中显示为 ---- ,起提示作用
            // 如果有sections，说明不是叶节点，递归处理子章节
            if (chapter.sections && Array.isArray(chapter.sections)) {
                // 递归处理子章节
                const subPath = basePath ? path.join(basePath, chapter.path) : chapter.path;
                const subFiles = this.getAllMarkdownFiles(chapter.sections, subPath);
                files.push(...subFiles);
            } else {
                // 叶节点，检查Markdown文件是否存在
                const filePath = basePath ? path.join(basePath, chapter.path) : chapter.path;
                const foundFile = this.checkMarkdownFile(basePath || '', chapter.path);
                if (foundFile) {
                    files.push(foundFile);
                }
            }
        }
        
        return files;
    }

    // 根据book.yaml chapters 获取所有Markdown文件
    get AllMarkdownFiles() {
        if (!this.config || !this.config.chapters) {
            return [];
        }
        return this.getAllMarkdownFiles(this.config.chapters);
    }

    build() {
        console.log('开始构建...');
        
        try {
            // 确保dist目录存在
            const distDir = path.join(__workdir, 'dist');
            if (!fs.existsSync(distDir)) {
                fs.mkdirSync(distDir, { recursive: true });
            }
            
            // 加载配置
            const config = this.config;

            // 渲染菜单
            this.config.menuHtml = this.renderMenu();
            
            // 获取所有Markdown文件
            const markdownFiles = this.AllMarkdownFiles;
            // console.log('找到的Markdown文件:', markdownFiles);
            
            // 构建所有Markdown文件
            for (const file of markdownFiles) {
                const outputPath = path.join('dist', file).replace(/\.md$/, '.html');
                this.buildMarkdownFile(file, outputPath);
            }


            // 构建首页
            this.renderIndex();

            // 处理assets
            this.deal_assets();

            console.log('构建完成！');
        } catch (error) {
            throw new Error(`构建失败: ${error.message}`);
        }
    }

    build_glob() {
        if( !this.config.glob ) return;
        let AllMarkdownFiles_in_chapters = this.AllMarkdownFiles;
        console.log("===== render glob md file =====");
        // console.log(AllMarkdownFiles_in_chapters)
        for( const glob of this.config.glob ) {
            const mdfiles = globSync('book/' + glob, { ignore: 'node_modules/**' })
            for( let file of mdfiles ) {
                let mdfile = file.replace('book/','');
                if( AllMarkdownFiles_in_chapters.includes( file.replace('book/','') ) ) continue;
                let outputPath = file.replace(/^book\//, 'dist/').replace(/\.md$/, '.html');
                this.buildMarkdownFile(mdfile, outputPath);
            }
        }
    }

    /**
     * @return {string} 返回渲染后的菜单HTML
     */
    renderMenu() {
        const htmlContent = nunjucksRender(__themedir, 'partials/menu', this.config);
        return htmlContent
    }

    renderIndex() {
        // 构建首页
        if (this.buildMarkdownFile('index.md', 'dist/index.html', 'index', {site : this.config})) {
            console.log('✓ 首页构建完成');
        }
    }

    // 处理assets 
    deal_assets() {
        this.copy_dir('public', 'dist');
        this.copy_dir('theme/assets', 'dist/assets');
    }

    copy_dir(src, dest) {
        const fullSrc = path.join(__workdir, src);
        const fullDest = path.join(__workdir, dest);
        if (!fs.existsSync(fullSrc)) {
            throw new Error(`源目录不存在: ${src}`);
        }
        if (!fs.existsSync(fullDest)) {
            fs.mkdirSync(fullDest, { recursive: true });
        }
        fs.cpSync(src, dest, { recursive: true });
    }


}

export default rbook;