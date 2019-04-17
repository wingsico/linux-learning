#! /bin/bash
set -e

sep=""

for file in $(ls -A)
do
  [[ -r $file &&  -w $file  &&  -x $file ]] && {
    printf "$sep%s" $file
    sep="   "
  }
done
printf "\n"
