#! /bin/bash
set -e

arg_num="$#"
min_arg_num=1

lib_path="$(dirname $(readlink -f $0))/lib"
. "$lib_path/stdout.sh"

[[ $arg_num -lt $min_arg_num ]] && {
  error "[arguments error]: At least one parameter is required."
  exit 1
}

files=("$@")
files=${files[@]:0}
for file in $files
do
  [[ "${file:0:1}" = "/" ]] && file_path="$file" || file_path="$(pwd)/$file"
  [[ ! -e "$file_path" ]] && {
    error "[arguments error]: File Path \"$file\" Not Found."
    exit 1
  }

  [[ -d "$file_path" ]] && {
    echo -e "\033[32m\033[1mDirectory - $file_path/\033[0m"
  } || echo "File - $(sed -n '$=' $file_path) - $file_path"
done
