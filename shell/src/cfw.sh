#!/bin/bash
set -e

arg_num="$#"
min_arg_num=2

lib_path="$(dirname $(readlink -f $0))/lib"
. "$lib_path/stdout.sh"

if [ $arg_num -lt $min_arg_num ]
then
  error "[arguments error]: At least two parameter is required."
  exit 1
fi

words_file_path="$(pwd)/$1"
if [ ! -e "$words_file_path" ]
then
  error "[arguments error]: File Path \"$words_file_path\" Not Found."
  exit 1
fi

words=("$(cat $words_file_path)")
words=($(echo ${words[@]:0} | sed 's/ /\n/g' | grep -o '^\w\w*$' | uniq ))
words=${words[@]:0}
files=("$@")
files=(${files[@]:1})

for ((i=0;i<${#files[*]};i++))
do
  file_path="$(pwd)/${files[$i]}"
  if [ ! -e $file_path ]
  then
    error "[arguments error]: File Path \"$file_path\" Not Found."
    exit 1
  fi

  echo -e "\033[32m\033[1m[$(($i+1))]: ${files[$i]}\033[0m"
done

for word in $words
do
  printf "%s:" "$word"
  for ((i=0;i<${#files[*]};i++))
  do
    file_path="$(pwd)/${files[$i]}"
    printf "\t%s: %s" "[$(($i+1))]" "$(grep -o -w "$word" $file_path | wc -l)"
  done
  printf "\n"
done
