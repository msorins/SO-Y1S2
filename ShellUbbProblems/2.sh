#Explode a given archive, using the appropriate commands based on the file's extension. This means, recursively extracting 
#the original archive and any other archives that it contains.

if [ $# -ne 1 ];
  then
    echo "Please give 1 parameter"
    exit 1
fi


ext=`echo $1 | cut -d\. -f2`
ext2=`echo $1 | cut -d\. -f3`
name=`echo $1 | cut -d\. -f1`

if [ "$ext" = "tar" -a "$ext2" = "gz" ];
  then 
    tar -xvf  $1 > unpack
    exit 1
fi

