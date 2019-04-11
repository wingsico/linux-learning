#!/bin/bash

min_arg_num=2
arg_num="$#"
word="$1"

lib_path="$(dirname $(readlink -f $0))/lib"

. "$lib_path/stdout.sh"

if [ "$arg_num" -lt $min_arg_num ]
then
  error "[arguments error]: At least two parameters are required."
  exit 1
fi

args=("$@")
echo $args
files=${args[@]:1}

del_file_word() {
  file="$1"
  file_path="$(pwd)/$file"
  if [ ! -e "$file_path" ]
  then
    error "[arguments error]: File Path \"$file\" Not Found"
    exit 1
  fi

  sed -i "/\b$word\b/d" $file_path && success "$file - deleted!"
}

for file in $files
do
  del_file_word "$file"
done

exit 0
