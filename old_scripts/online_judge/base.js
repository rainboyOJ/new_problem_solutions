import fs from 'fs';
import path from 'path';
import yaml from 'js-yaml';
import { glob, globSync, globStream, globStreamSync, Glob } from 'glob'
import { fileURLToPath } from 'url';
import { dirname } from 'path';
import { nunjucksRender } from '../rbook/renderEngine.js';

// 获取当前文件的目录路径
export const __filename = fileURLToPath(import.meta.url);
export const __dirname = dirname(__filename);
export const __workdir = path.join(__dirname, '../../');
export const __bookdir = path.join(__workdir, 'book');
export const __template_dir = path.join(__dirname, 'template');
export const __problemdir = path.join(__workdir, 'problems');
// console.log('--themdir: ',__template_dir)

class Base {
  // oj
  constructor(ojName,_path,oj_website)
  {
    this._OJ= ojName
    this._PATH = _path
    this._OJ_WEBSITE = oj_website
  }

  match_by_link(url) {
    // console.log('url: ',url)
    // console.log('this._OJ_WEBSITE: ',this._OJ_WEBSITE)
    return url.startsWith(this._OJ_WEBSITE)
  }

  get full_oj_path() {
    return path.join(__problemdir, this._PATH)
  }

  get name() {
    return this._OJ
  }

  _oj_dir(){
    return path.join(__problemdir, this._PATH)
  }

  get get_pwd() {
    return process.cwd()
  }

    match_by_name(oj_name) {
      return oj_name.toLowerCase()  == this._OJ.toLowerCase()
    }
  
  // 根据当前目录匹配是否是此oj的目录
  match_by_pwd(){
    let pwd = this.get_pwd
    let fullOjPath = this.full_oj_path
    return pwd.startsWith(fullOjPath)
  }

  save(id,md_content) {
    console.log(`[${this._OJ}] ${id} 保存中...`)
    let dir = path.join(this._oj_dir(),id)
    if (!fs.existsSync(dir)) {
      fs.mkdirSync(dir, { recursive: true });
    }
    let md_path = path.join(dir, `index.md`)
    if( fs.existsSync(md_path))
    {
      console.log(`${md_path} 已存在`)
    }
    else 
    {
      fs.writeFileSync(md_path, md_content, { encoding: 'utf-8' });
      console.log(`[${this._OJ}] ${id} 保存成功: ${md_path}`)
    }

    // -- 给oj 命令使用,得到 下载的目录
    console.log( path.dirname(md_path))
    //最后返回文件路径
    return md_path
  }

  render(data) {
    let template_name = 'default'
    if( fs.existsSync(path.join(__template_dir, `${this._OJ}.njk`))){
      template_name = this._OJ
    }

    return nunjucksRender(__template_dir, template_name ,{
      date: new Date().toLocaleString('zh-CN', {
        year: 'numeric',
        month: '2-digit',
        day: '2-digit',
        hour: '2-digit',
        minute: '2-digit',
        hour12: false
      }).replace(/\//g, '-'),

      oj_name: this._OJ,

      ...data,
    })
  }

}

export default Base