// 对problem 进行信息的管理,不进行渲染
import fs from 'fs';
import path from 'path';
import yaml from 'js-yaml';
import { glob, globSync, globStream, globStreamSync, Glob } from 'glob'
import { fileURLToPath } from 'url';
import { dirname } from 'path';
import * as matter from 'gray-matter';

// 获取当前文件的目录路径
export const __filename = fileURLToPath(import.meta.url);
export const __dirname = dirname(__filename);
export const __workdir = path.join(__dirname, '../');
export const __bookdir = path.join(__workdir, 'book');
export const __code_template_dir = path.join(__workdir, 'code');
export const __themedir = path.join(__workdir, 'theme');

export const __problemdir = path.join(__workdir, 'problems');

class Problems {

    constructor(opts = {auto_load : true}) {
        this.name = 'problems';
        this.problem_files = [];
        if( opts.auto_load ) // 如果自动加载,则加载所有的题目信息
          this.init();
        this.config = this.load_config();
        this.problemJsonPath = path.join(__workdir, 'problems.json');
    }

    save_problems() {
      // 保存到文件
      fs.writeFileSync(this.problemJsonPath, JSON.stringify(this.problems, null, 2));
    }

    load_problems() {
      if( !fs.existsSync(this.problemJsonPath) ) {
        this.init();
        this.save_problems();
        return;
      }
      // 从文件加载
      this.problems = JSON.parse(fs.readFileSync(this.problemJsonPath, 'utf8'));
    }

    find(oj, problem_id) {
      return this.problems.find(p => p.oj === oj && p.problem_id === problem_id);
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

    problem_url(oj,id) {
      return `/problems/${oj}/${id}/index.html`;
    }

    front_matter(md_path) {
      let raw_md = fs.readFileSync(md_path, 'utf8');
      let prob_front = matter.default(raw_md).data;
      return prob_front
    }

    // 将 md_path 转换为 url
    md_path_to_url(md_path) {
      if( !md_path || md_path.length == 0 ) {
        throw new Error('md_path is empty');
      }
      // let prob_front = new markdown(md_path).front_matter;
      // let raw_md = fs.readFileSync(md_path, 'utf8');
      let prob_front = this.front_matter(md_path);

      if (!prob_front.oj || !prob_front.problem_id)
        throw new Error(`md_path: ${md_path} front_matter.oj or front_matter.problem_id is empty`);
      return this.problem_url( prob_front.oj, prob_front.problem_id );
    }

    /**
     * 初始化,加载所有的题目信息
     * @returns
    */
    init() {
      // 扫描 __problemdir 目录下的所有非_ 开头的md文件
      const files = globSync('**/!(_)*.md',{cwd: __problemdir});
      this.problem_files = files
      // console.log(files);
      this.problems = [];
      for( let md of files ) {
        let md_path = path.join(__problemdir, md);
        // let prob_front = new markdown(md_path).front_matter;
        let prob_front = this.front_matter(md_path);

        if( !prob_front )
          // throw new Error(`md_path: ${md_path} front_matter is empty`);
          console.log(`md_path: ${md_path} front_matter is empty`);
        else if( !prob_front.oj || !prob_front.problem_id )
          // throw new Error(`md_path: ${md_path} front_matter.oj or front_matter.problem_id is empty`);
          console.log(`md_path: ${md_path} front_matter.oj or front_matter.problem_id is empty`);
        else
          this.problems.push(
            {
              ...prob_front,
              md_path: md, // 相对路径
              url: this.problem_url(prob_front.oj, prob_front.problem_id) // url
            }
          );
      }
      // console.log(this.problems);
    }
}
export default Problems;