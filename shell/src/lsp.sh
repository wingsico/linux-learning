
sep=""

for file in $(ls -A)
do
  if [ -r $file ] && [ -w $file ] && [ -x $file ]
  then
    printf "$sep%s" $file
    sep="   "
  fi
done
printf "\n"

exit 0
