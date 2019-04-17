#! /bin/bash

for file in $(ls *.sh)
do
  chmod 755 $file
done

exit 0
