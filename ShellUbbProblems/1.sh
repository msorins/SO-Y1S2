#Archive a hierarchy of directories into archives of the following types: zip, tar, tar.gz, tar.bz2.
#The last two types are actually regular TAR archives compressed using gzip or bzip2.


if [ $# -ne 1 ];
  then 
    echo "Please give 1 parameter";
    exit 1;
fi

file=$1
ext=".tar.gz"
tar -zcvf $file$ext $file
