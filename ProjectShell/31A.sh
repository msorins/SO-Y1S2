

#Write a shell script that will monitor the content of a folder (given in the 
#command line) and notify if files or folders are created or deleted from it.

#VALIDATION OF THE ARGUMENTS
if [ $# -ne 1 ];
then
  echo "Invalid number of arguments"
  exit 1
fi

if [ ! -d $1 ];
then
  echo "Argument must be a valid directory"
  exit 2
fi


dir=$1

x=`find $dir -type d`
#Here is the main part of the program, the loop that does the monitoring
while  true;
do
  sleep 2
  y=`find $dir -type d`

  difference=` diff  <(echo "$x" ) <(echo "$y")`

  #Compute the difference
  deleteOp=`echo "$difference" | grep -c "<"`

  if [ "$deleteOp" == "1" ]
  then
     folder=`echo $difference | cut -d"<" -f2`
     echo "Deletion of folder detected. Name: " $folder
  fi

  createOp=`echo "$difference" | grep -c ">"` 

  if [ "$createOp" == "1" ]
  then
     folder=`echo $difference | cut -d">" -f2`
     echo "Creation of folder detected. Name: " $folder
  fi



  #Prepare the next iteration
  x=$y
done

