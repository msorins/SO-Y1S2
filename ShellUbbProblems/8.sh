#Sa se scrie un script shell care afiseaza directoarele primite ca si argum
#in  linia de  comanda crescatoare a spatiuliul  disk care il ocupa, doar
#pentru acele directoare care au dimensiunea lor in biti un numar ce contine 
#cel putin o cifra para

computeDirectory() {
   a=1
}

while [ $# -ne 0 ];
do
   if [ ! -d $1 ];
   then 
      shift
      continue
   fi
   
   echo "###  Directory " $1 " ###"

   computeDirectory $1 "beach"
 
   #This command does the job recursive for each subfolder
   #lst=`du $1 | sort | awk '{ A=int($1); para=0; while(A){ if(A%2==0) para=1; A = A / 10; } if(para == 1) {  print $0; } }'`
   
   lst=`du -c $1 | tail -n 1 |  awk '{ para = 0; A = int($1); while(A != 0){ if(A%2==0){para = 1; }  A = int( A / 10 ); } if(para==1)  print $1; }' `
 
   `echo "$lst" > "auxX.tst"`
    cat auxX.tst
    rm auxX.tst

  shift
done
