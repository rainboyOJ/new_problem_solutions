import { execSync } from "child_process";

// const cheerio = require('cheerio');
import * as cheerio from 'cheerio'

import { writeFileSync, readFileSync, existsSync } from "fs";
import Base from './base.js'

class CF extends Base {

    static instance = null

    constructor() {
        super('codeforces','/codeforces',"https://codeforces.com")
        // this.id = id
        // this.link = `https://www.luogu.com.cn/problem/${id}`
        // return luogu.instance || (luogu.instance = this)
    }

    // https://codeforces.com/contest/165/problem/E
    // -> 165E
    get_id_by_link(link) {
      let id = ''

      let arr = link.split('/')
      for(let i =0 ;i< arr.length ;i++){
        if(  arr[i].toLowerCase() == 'contest' )
        {
          id+= arr[i+1]
        }
        else if(  arr[i].toLowerCase() == 'problem' )
        {
          id += arr[i+1]
          break;
        }
      }
      return id
    }

    real_id(id) {
      return /^\d/.test(id) ? `P${id}` : id;
    }

    problem_link(id) {
      let contest_id =  id.slice(0,-1)
      let problem_id = id.slice(-1)
      return `https://www.codeforces.com/contest/${contest_id}/problem/${problem_id}`
    }

    download_by_link(link) {
      let id = this.get_id_by_link(link)
      this.source = link 
      this.download(id,this._OJ_NAME)
        // let id = link.split('/').pop()
        // let real_ojname = link.split('/')[3]
        // this.download(id,real_ojname)
    }

    download(id,ojName='codeforces') {
        // let pid = id.replace('/','-').toUpperCase();
        let pid = id
        // let data = this.http(pid)
        let md_content = this.render({
          // ...data, 
          oj_name: ojName,
          problem_id: id,
          source : this.source ||  this.problem_link(id)
        })
        this.save(id,md_content)
    }
}

export default CF
