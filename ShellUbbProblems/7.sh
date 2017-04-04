#Display the content of a directory as a tree similar to how it is shown below. After each file or directory name, display its total size

printDirectory() {
  depth=$1
  
  newDepth=`expr $depth + 1`
  path=$2
  echo "Directory: "$path

  files=`find $2/* -maxdepth 1 -type f`
  directories=`find $2/* -maxdepth 1 -type d`
  
 

  for file in $files
   do
    i=1
     while [ $i -le $depth ]
       do
         printf "  "
         i=`expr $i + 1`
       done

     printf $file"\n"
   done
 
  for directory in $directories
    do
       printDirectory $newDepth $directory
    done
  return 0;
}


printDirectory  1 $1
