#!/bin/bash
set -e

arg_num="$#"
min_arg_num=2

lib_path="$(dirname $(readlink -f $0))/lib"
. "$lib_path/stdout.sh"

# 参数验证
[[ $arg_num -lt $min_arg_num ]] && {
  error "[arguments error]: At least two parameter is required."
  exit 1
}

# 单词文件路径
words_file_path="$1"
[[ "${words_file_path:0:1}" = "/" ]] || words_file_path="$(pwd)/$words_file_path"

# 单词文件存在验证
[[ ! -e "$words_file_path" ]] && {
  error "[arguments error]: File Path \"$words_file_path\" Not Found."
  exit 1
}

# 取出内容
words=("$(cat $words_file_path)")
# 去重
words=($(echo ${words[@]:0} | sed 's/ /\n/g' | grep -o '^\w\w*$' | uniq ))

words=${words[@]:0}

# 待统计的文件列表
files=("$@")
files=(${files[@]:1})

for ((i=0;i<${#files[*]};i++))
do
  file="${files[$i]}"
  [[ "${file:0:1}" = "/" ]] && file_path="$file" || file_path="$(pwd)/$file"
  [[ ! -e $file_path ]] && {
    error "[arguments error]: File Path \"$file_path\" Not Found."
    exit 1
  }
	
	# 文件符号化，用特定符号代替文件路径以缩短展示区域
  echo -e "\033[32m\033[1m[$(($i+1))]: $file\033[0m"
done

for word in $words
do
  printf "%s:" "$word"
  for ((i=0;i<${#files[*]};i++))
  do
  	file="${files[$i]}"
  	[[ "${file:0:1}" = "/" ]] && file_path="$file" || file_path="$(pwd)/$file"
  	# 统计数量并输出
    printf "\t%s: %s" "[$(($i+1))]" "$(grep -o -w "$word" $file_path | wc -l)"
  done
  printf "\n"
done
