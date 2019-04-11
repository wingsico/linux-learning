#!/bin/sh

src_path="/home/cc/github.com/vydVolk/linux-learning/shell/src"
bin_path="/home/cc/github.com/vydVolk/linux-learning/shell/bin"

for sh in $(ls $src_path/*.sh)
do
  file_name=${sh%.*}
  file_name=${file_name##*/}
  if [ -e "$bin_path/$file_name" ]
  then
    rm -rf "$bin_path/$file_name"
  fi

  ln -s "$sh" "$bin_path/$file_name" && echo "\033[32m\033[1m[$(date "+%H:%M:%S")] $file_name - completed!\033[0m"
done

exit 0
