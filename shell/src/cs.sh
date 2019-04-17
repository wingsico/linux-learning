#! /bin/bash

set -e

lib_path="$(dirname $(readlink -f $0))/lib"
. "$lib_path/stdout.sh"


cmds=("fcl" "dlw" "lsp" "lc" "cfw" "lsd" "fac")
append_cmds=(
"exec dlw a poem1 poem2"
"exec lsp"
"exec lc poem dir2"
"exec cfw words poem2 poem3"
"exec lsd"
"exec fac 100"
""
)


for ((i=0;i<7;i++))
do
  cmd="${cmds[$i]}"
  append_cmd="${append_cmds[$i]}"
  cmd_path="$(pwd)/../src/$cmd.sh"
  if [ $i -gt 0 ]
  then
    [[ $i -gt 1 ]] && lines_rm=3 || lines_rm=2
    pre_cmd="${cmds[$i-1]}"
    pre_cmd_path="$(pwd)/../src/$pre_cmd.sh"
    pre_cmd_file_lines="$(sed -n '$=' $pre_cmd_path)"
    let pre_cmd_file_slines=$pre_cmd_file_lines-$lines_rm+1
    echo "sed -i $pre_cmd_file_slines',\$d' $pre_cmd_path" >> $cmd_path 
  fi

  [[ $i -lt 6 ]] && {
    echo "echo ======== ${cmds[$i+1]} ======== " >> $cmd_path
  echo "$append_cmd" >> $cmd_path
}
done

echo ======== fcl ========
fcl poem 2 5
sed -i $(sed -n '$=' "$(pwd)/../src/fac.sh")',$d' "$(pwd)/../src/fac.sh" 

