#!/bin/bash

set -e
cmd_path="$(dirname $(readlink -f $0))"
src_path="$cmd_path"
bin_path="$cmd_path/../bin"

lib_path="$cmd_path/lib"
. "$lib_path/stdout.sh"

for sh in $(ls $src_path/*.sh)
do
  file_name=${sh%.*}
  file_name=${file_name##*/}
  [[ -e "$bin_path/$file_name" ]] && rm -rf "$bin_path/$file_name"

  ln -s "$sh" "$bin_path/$file_name" && success "$file_name - completed!"
done
