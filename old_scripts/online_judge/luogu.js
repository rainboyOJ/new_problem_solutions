import { execSync } from "child_process";


// const cheerio = require('cheerio');
import * as cheerio from 'cheerio'

import { writeFileSync, readFileSync, existsSync } from "fs";
import Base from './base.js'

class LUOGU extends Base {

    static instance = null

    constructor() {
        super('luogu','/luogu',"https://www.luogu.com")
        // this.id = id
        // this.link = `https://www.luogu.com.cn/problem/${id}`
        // return luogu.instance || (luogu.instance = this)
    }

    real_id(id) {
      return /^\d/.test(id) ? `P${id}` : id;
    }

    problem_link(id) {
      return `https://www.luogu.com.cn/problem/${this.real_id(id)}`
    }


    //连接网络 得到题目数据
    http(id) {
        // let realId = /^\d/.test(id) ? `P${id}` : id;
        // console.log( 'realId',realId )
        let href = this.problem_link( id )

        // let a = e(`curl https://www.luogu.com.cn/problem/${realId} --cookie "${cookie}"`,{encoding:'utf-8'})
        let a = execSync(`wget -O - ${href}`,{encoding:'utf-8'})
        
        /* 以前的获取方式
        let dataReg = /decodeURIComponent\("([\s\S]+?)"\)/
        // console.log(a)
        //console.log(dataReg.test(a))
        //console.log( a.match(dataReg))
        let data_string = a.match(dataReg)[1]
        var data = JSON.parse(decodeURIComponent(data_string))
        //console.log(JSON.stringify(data,null,4))
        //console.log(data.currentData.lastCode)
        */

        // 2. 加载 HTML 到 Cheerio
        const $ = cheerio.load(a);

        // 3. 定位目标 script 标签
        const targetScript = $('#lentille-context[type="application/json"]');

        // 4. 提取内容并解析 JSON
        if (targetScript.length > 0) {
            const jsonContent = targetScript.html();
            const parsedData = JSON.parse(jsonContent);
            // console.log('提取到的数据:', parsedData);
            return parsedData.data;
        } else {
            console.log('未找到目标 script 标签');
            return null;
        }

        // return data
    }

    //下载数据
    download_data(id ,data = null) {
        data  = data || this.http(id);
        if (!data) {
            console.log("无法获取题目数据");
            return false;
        }

        const problem = data.problem;
        const samples = problem.samples || [];

        if (samples.length === 0) {
            console.log("未找到样例数据");
            return false;
        }

        console.log(`找到 ${samples.length} 组样例数据`);

        // 保存样例数据到文件
        for (let i = 0; i < samples.length; i++) {
            const sample = samples[i];
            let inputData = '';
            let outputData = '';

            // 处理不同格式的样本
            if (Array.isArray(sample) && sample.length >= 2) {
                inputData = sample[0];
                outputData = sample[1];
            } else if (typeof sample === 'object' && sample !== null) {
                inputData = sample.input || '';
                outputData = sample.output || '';
            } else {
                console.log(`警告: 第${i+1}个样本格式未知，跳过`);
                continue;
            }

            // 保存输入数据
            const inputFilename = `in${i+1}`;
            writeFileSync(inputFilename, inputData, { encoding: 'utf-8' });
            console.log(`已保存输入数据到: ${inputFilename}`);

            // 如果是第一个样本且不存在"in"文件，则复制
            if (i === 0 && !existsSync("in")) {
                writeFileSync("in", inputData, { encoding: 'utf-8' });
                console.log("in 文件不存在, copy in1 to in");
            }

            // 保存输出数据
            const outputFilename = `out${i+1}`;
            writeFileSync(outputFilename, outputData, { encoding: 'utf-8' });
            console.log(`已保存输出数据到: ${outputFilename}`);
        }

        return true;
    }

    download(id,ojName = 'luogu') {
        let data = this.http(id)
        // console.log(data)

        let problem = data.problem
        // console.log(problem.tags)
        // let template_md_file =  join(__dirname,'./template/luogou.ejs')

        // let template_content = readFileSync(template_md_file,{encoding:'utf-8'})

        let md_content = this.render({...problem, 
          problem_id: this.real_id(id),
          source : this.problem_link(id)})
        // let output_path = this.problem(id).default_file
        // writeFileSync(output_path,md_content,{encoding:'utf-8'})

        let save_id = id[0].toLowerCase() == 'p' ? id.slice(1) : id

        let md_path = this.save(save_id,md_content)
    }

    download_by_link(link) {
      let link_split = link.split('/')
      let id = link_split[4]
      this.source = link 
      this.download(id)
        // let id = link.split('/').pop()
        // let real_ojname = link.split('/')[3]
        // this.download(id,real_ojname)
    }

}

export default LUOGU
