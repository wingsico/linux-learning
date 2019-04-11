#! /bin/bash

arg_num="$#"
min_arg_num=1

lib_path="$(dirname $(readlink -f $0))/lib"
. "$lib_path/stdout.sh"


if [ $arg_num -lt $min_arg_num ]
then
  error "[arguments error]: At least one parameter is required."
  exit 1
fi

files=("$@")
files=${files[@]:0}
for file in $files
do
  file_path="$(pwd)/$file"
  if [ ! -e "$file_path" ]
  then
    error "[arguments error]: File Path \"$file\" Not Found."
    exit 1
  fi

  if [ -d "$file_path" ]
  then
    echo -e "\033[32m\033[1mDirectory - $file_path/\033[0m"
  else
    echo "File - $file_path"
  fi
done

exit 0



