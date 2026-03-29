import * as matter from 'gray-matter';
// import markdownit from './markdownit.js';
import markdownit from './markdown-it/index.js';
import fs from 'fs';
import path from 'path';

class Markdown {
    constructor(md_path = '') {
        this.name = 'rbook';
        this.front_matter = {};
        this.md_content = '';
        this.html_content = undefined;
        if( md_path && md_path.length > 0 ) {
            this.md_path = md_path; // md文件路径
            // let raw_md = fs.readFileSync(md_path, 'utf8');
            let raw_md = this.readfile(md_path);

            let result = this.matter(raw_md);
            this.front_matter = result.data;
            this.md_content = result.content;
            // this.html_content = this.toHTML(result.content);
        }
    }

    // 返回raw_md
    // 处理内部的 include other md 语法
    readfile(md_path) {
        this.md_path = md_path; // md文件路径
        let raw_md = fs.readFileSync(md_path, 'utf8');
        
        // 处理 @include_md("./file.md") 语法
        raw_md = this.processIncludeMd(raw_md, md_path);
        
        return raw_md;
    }

    /**
     * 处理 Markdown 文件中的 @include_md 语法
     * @param {string} content - 原始 Markdown 内容
     * @param {string} currentFilePath - 当前文件的路径
     * @returns {string} - 处理后的内容
     */
    processIncludeMd(content, currentFilePath) {
        const includeRegex = /^@include_md\("([^"]+)"\)\s*$/gm;
        const currentDir = path.dirname(currentFilePath);
        
        return content.replace(includeRegex, (match, includePath) => {
            const fullPath = path.resolve(currentDir, includePath);
            
            try {
                if (!fs.existsSync(fullPath)) {
                    console.warn(`Warning: Included file not found: ${fullPath}`);
                    return `<!-- Warning: File not found: ${includePath} -->`;
                }
                
                const includedContent = fs.readFileSync(fullPath, 'utf8');
                // 递归处理被包含文件中的 @include_md 语法
                return this.processIncludeMd(includedContent, fullPath);
            } catch (error) {
                console.error(`Error including file ${includePath}:`, error.message);
                return `<!-- Error including file: ${includePath} -->`;
            }
        });
    }

    /**
     * 解析FrontMatter和Markdown内容
     * @param {string} md_content - Markdown内容
     * @returns {Object} - { content: markdown, data: frontmatter }
     */
    matter(md_content) {
        try {
            const result = matter.default(md_content);
            // this.front_matter = result.data;
            // this.md_content = result.content;
            // this.html_content = this.toHTML(result.content);
            // return {
            //     content: result.content,j
            //     data: this.front_matter
            // };
            return result;
        } catch (error) {
            throw new Error(`解析Markdown失败: ${error.message}`);
        }
    }

    /**
     * 将Markdown转换为HTML
     * @param {string} md_content - Markdown内容
     * @returns {string} - HTML内容
     */
    toHTML(md_content) {
        return markdownit.render(md_content, { filePath: this.md_path });
    }

    toJSON() {
        if(this.html_content === undefined) {
            this.html_content = this.toHTML(this.md_content);
        }
        return {
            front_matter: this.front_matter,
            md_content: this.md_content,
            html_content: this.html_content
        };
    }
}

export default Markdown;