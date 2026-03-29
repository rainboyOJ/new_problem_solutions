// 对problem 进行信息的管理,进行渲染
// 为什么要把problem 分开呢,因为Problemlib 要给 third_part/problem_list/load_data.js 使用
import fs from 'fs';
import path from 'path';
import yaml from 'js-yaml';
import { glob, globSync, globStream, globStreamSync, Glob } from 'glob'
import { fileURLToPath } from 'url';
import { dirname } from 'path';
import { nunjucksRender } from './rbook/renderEngine.js';
import markdown from './rbook/markdown.js';
import Problemlib from './problemlib.js';

// 获取当前文件的目录路径
export const __filename = fileURLToPath(import.meta.url);
export const __dirname = dirname(__filename);
export const __workdir = path.join(__dirname, '../');
export const __bookdir = path.join(__workdir, 'book');
export const __code_template_dir = path.join(__workdir, 'code');
export const __themedir = path.join(__workdir, 'theme');

export const __problemdir = path.join(__workdir, 'problems');

class Problems extends Problemlib {
  
    constructor() {
      super();
    }

    renderAll() {
      for( let prob of this.problems ) {
        this.render(prob);
      }
    }

    render(prob_info) {
      let md_path = prob_info.md_path;
      let md = new markdown(path.join(__problemdir, md_path));
      let prob_html = md.toJSON().html_content;
      let prob_url = prob_info.url;
      let prob_html_path = path.join(__workdir ,'dist', prob_url);
      let prob_html_dir = path.dirname(prob_html_path);
      if (!fs.existsSync(prob_html_dir)) {
        fs.mkdirSync(prob_html_dir, { recursive: true });
      }
      let prob_html_content = nunjucksRender(__themedir,'problem', {
        front_matter: prob_info,
        html_content: prob_html,
        site: this.config
       });
      fs.writeFileSync(prob_html_path, prob_html_content);

      // 将 prob 目录下面的所有的 png,svg ,jpg 文件复制到 prob_html_dir
      let prob_dir = path.dirname(path.join(__problemdir, md_path));
      let prob_files = glob.sync(path.join(prob_dir, '*.{png,svg,jpg}'));
      for( let prob_file of prob_files ) {
        let prob_file_name = path.basename(prob_file);
        let prob_file_dest = path.join(prob_html_dir, prob_file_name);
        fs.copyFileSync(prob_file, prob_file_dest);
      }

    }
}
export default Problems;