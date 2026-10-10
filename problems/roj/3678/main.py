import sys

def main():
    input = sys.stdin.read
    data = input().split()
    if not data:
        return
    
    n = int(data[0])
    idx = 1
    
    types = {
        "byte": {"size": 1, "align": 1, "members": [], "name_to_index": {}},
        "short": {"size": 2, "align": 2, "members": [], "name_to_index": {}},
        "int": {"size": 4, "align": 4, "members": [], "name_to_index": {}},
        "long": {"size": 8, "align": 8, "members": [], "name_to_index": {}},
    }
    
    vars_list = []
    var_name_to_index = {}
    
    out = []
    
    for _ in range(n):
        op = int(data[idx])
        idx += 1
        
        if op == 1:
            name = data[idx]
            k = int(data[idx+1])
            idx += 2
            
            align = 0
            current_offset = 0
            members = []
            name_to_index = {}
            
            for i in range(k):
                type_name = data[idx]
                member_name = data[idx+1]
                idx += 2
                
                member_type = types[type_name]
                m_align = member_type["align"]
                m_size = member_type["size"]
                
                if align < m_align:
                    align = m_align
                
                current_offset = (current_offset + m_align - 1) // m_align * m_align
                members.append({
                    "type": type_name,
                    "name": member_name,
                    "offset": current_offset
                })
                name_to_index[member_name] = i
                current_offset += m_size
                
            size = (current_offset + align - 1) // align * align
            types[name] = {
                "size": size,
                "align": align,
                "members": members,
                "name_to_index": name_to_index
            }
            out.append(f"{size} {align}")
            
        elif op == 2:
            type_name = data[idx]
            var_name = data[idx+1]
            idx += 2
            
            t = types[type_name]
            t_align = t["align"]
            
            start_addr = 0
            if vars_list:
                last_var = vars_list[-1]
                last_type = types[last_var["type"]]
                next_avail = last_var["addr"] + last_type["size"]
                start_addr = (next_avail + t_align - 1) // t_align * t_align
                
            vars_list.append({
                "type": type_name,
                "name": var_name,
                "addr": start_addr
            })
            var_name_to_index[var_name] = len(vars_list) - 1
            out.append(str(start_addr))
            
        elif op == 3:
            path = data[idx]
            idx += 1
            
            parts = path.split('.')
            var_idx = var_name_to_index[parts[0]]
            ans = vars_list[var_idx]["addr"]
            curr_type = vars_list[var_idx]["type"]
            
            for i in range(1, len(parts)):
                t = types[curr_type]
                member_idx = t["name_to_index"][parts[i]]
                m = t["members"][member_idx]
                ans += m["offset"]
                curr_type = m["type"]
                
            out.append(str(ans))
            
        elif op == 4:
            addr = int(data[idx])
            idx += 1
            
            found_var_idx = -1
            for i, v in enumerate(vars_list):
                if v["addr"] <= addr < v["addr"] + types[v["type"]]["size"]:
                    found_var_idx = i
                    break
            
            if found_var_idx == -1:
                out.append("ERR")
                continue
                
            res = vars_list[found_var_idx]["name"]
            curr_type = vars_list[found_var_idx]["type"]
            rem_addr = addr - vars_list[found_var_idx]["addr"]
            
            ok = True
            while types[curr_type]["members"]:
                t = types[curr_type]
                found_member_idx = -1
                for i in range(len(t["members"]) - 1, -1, -1):
                    if rem_addr >= t["members"][i]["offset"]:
                        found_member_idx = i
                        break
                
                if found_member_idx == -1:
                    ok = False
                    break
                
                m = t["members"][found_member_idx]
                m_size = types[m["type"]]["size"]
                
                if rem_addr < m["offset"] + m_size:
                    res += "." + m["name"]
                    rem_addr -= m["offset"]
                    curr_type = m["type"]
                else:
                    ok = False
                    break
                    
            if ok:
                out.append(res)
            else:
                out.append("ERR")

    print('\n'.join(out))

if __name__ == '__main__':
    main()
