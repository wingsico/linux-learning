#!/bin/bash

set -e

src_path="/home/cc/github.com/vydVolk/linux-learning/shell/src"
bin_path="/home/cc/github.com/vydVolk/linux-learning/shell/bin"

lib_path="$(dirname $(readlink -f $0))/lib"
. "$lib_path/stdout.sh"

for sh in $(ls $src_path/*.sh)
do
  file_name=${sh%.*}
  file_name=${file_name##*/}
  if [ -e "$bin_path/$file_name" ]
  then
    rm -rf "$bin_path/$file_name"
  fi

  ln -s "$sh" "$bin_path/$file_name" && success "$file_name - completed!"
done

