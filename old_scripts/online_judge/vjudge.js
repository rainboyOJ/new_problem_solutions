// import pather from './online_judge/base_class/pather.js'
import { execSync } from "child_process"
import { writeFileSync, readFileSync, readdirSync } from "fs"
import { join } from "path"
import Base from "./base.js"
import ejs from "ejs"
import * as cheerio from "cheerio"

class vjudge extends Base {

    static instance = null

    constructor() {
        // vjude 题目的目录直接在 /problems ,
        // 为了对应的OJ的题目解析 可以创建到对应的位置 : /problems/poj/1234
        super('vjudge','/','https://vjudge.net/')
        // this.id = id
        // this.link = `https://www.luogu.com.cn/problem/${id}`
        // return vjudge.instance || (vjudge.instance = this)
    }

    //返回此oj默认存题目文件的名字,使用 problem,content
    get problem_file_name() {
        return 'config'
    }

    match_by_name(oj_name) {
      // console.log(oj_name)
      const ojList = ['poj', 'hdu','atcoder',"OpenJ_Bailian","CodeForces"];
      // console.log(ojList.includes(oj_name.toLowerCase()))
      return ojList.includes(oj_name.toLowerCase())
    }


    //用于显示的id,不是真正的id
    show_id(id) {
        let pid = id.replace('/','-').toUpperCase();
        return pid
    }

    //连接网络 得到题目数据
    http(id) {
        // let a = execSync(`wget -O - https://vjudge.net.cn/problem/${id}`,{encoding:'utf-8'})
        let a = execSync(`wget -O - https://vjudge.net/problem/${id}`,{encoding:'utf-8'})
        // console.log(a)
        let $ = cheerio.load(a)
        let title = $('#prob-title').find('h2').text().trim()
        console.log("title: ",title)
        console.log("id: ",id)
        // console.log(a)
        return {title}
    }
    
    problem_link(id) {
      let pid = id.replace('/','-').toUpperCase();
      return `https://vjudge.net/problem/${pid}`
    }

    download(id,ojName) {
        // let pid = id.replace('/','-').toUpperCase();
        let pid = ojName + '-' + id
        let data = this.http(pid)
        let md_content = this.render({
          ...data, 
          oj_name: ojName,
          problem_id: id,
          source : this.source ||  this.problem_link(id)
        })
        this.save(`${ojName}/${id}`,md_content)
    }

    download_by_link(link) {
      let link_split = link.split('/')
      let oj_and_id = link_split[4].split('#')[0]
      let oj = oj_and_id.split('-')[0]
      let id = oj_and_id.split('-')[1]
      this.source = link 
      this.download(id,oj)
        // let id = link.split('/').pop()
        // let real_ojname = link.split('/')[3]
        // this.download(id,real_ojname)
    }

}

// const vjudgeInstance = new vjudge()
export default vjudge
