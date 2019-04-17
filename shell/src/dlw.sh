#!/bin/bash
set -e


min_arg_num=2
arg_num="$#"

# 查找的单词
word="$1"

lib_path="$(dirname $(readlink -f $0))/lib"
. "$lib_path/stdout.sh"

# 判断参数个数合法性
[[ "$arg_num" -lt $min_arg_num ]] && error "[arguments error]: At least two parameters are required."

# 获取待查找文件列表
args=("$@")
files=${args[@]:1}

# 删除函数
del_file_word() {
  file="$1"
  [[ "${file:0:1}" = "/" ]] && file_path="$file" || file_path="$(pwd)/$file"
  [[ ! -e "$file_path" ]] && {
    error "[arguments error]: File Path \"$file\" Not Found"
    exit 1
  }
	
	# 利用sed函数 -i 参数把删除动作写入到文件中
  sed -i "/\b$word\b/d" $file_path && success "$file - deleted!"
}

# 对每一份文件都执行该函数
for file in $files
do
  del_file_word "$file"
done
