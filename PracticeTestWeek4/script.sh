#Replace first word with second word
#sed 's#^\(\<\w*\>\).*\(\1\)##' script.txt

#Cate linii au al 1-lea cuvant egal cu  al treilea
#grep '^\(\w\+\)\s\<\w\+\>\s\1'

#Reorder word 1 2 3 to 3 2 1
#sed 's#^\(\<\w\+\>\)\s\(\<\w\+\>\)\s\(\<\w\+\>\)#\3 \2 \1#'

#Afiseaza linii de lungime impara
#grep '^\(..\)\+$' script.txt

#Printeaza un tabel cu toti utilizatorii din last.fake.passwd a caror nume incepe cu a
#awk 'BEGIN{ print "##name##" }/^a/ {print $1}END{ print "## END ##" }' last.fake.txt


#1) Find all the usernames that logged in from "economica" on a Sunday
#awk 'BEGIN{ print "== USERNAMES ==" }/Sun/{print $1}END{print "== FINAL =="}' last.fake.txt
#awk 'BEGIN{ print "== USERNAMES ==" }/Sun/{if($4 == "Sun") print NR, $1}END{print "== FINAL =="}' last.fake.txt

#2) Find all the users that logged into the system after 11PM
#awk  'BEGIN{ print "## USERS " }{ split($7, A, ":");  if(A[1] == "23") print $1 }END{ print "## END  " }' last.fake.txt

#3) Display the full names of the users having a username that starts with "m" and with a user ID divisible by 7
#awk -F: 'BEGIN{ print "## FULL NAME ##" }{  if(match($5, "M") == 1) print $1, " - ", $5 }' passwd.fake.txt

#4) Display all the distinct TTYs used by user root.
#awk 'BEGIN{ PRINT "## NAME ##" }/^root.*/{ print $6 }' ps.fake.txt | sort | uniq

#5) Find the full names of all the users whose username ends in 88
#awk -F: 'BEGIN{ print "## NAMES ##" }/^......88.*/{print $5 }END{ print "## END ##" }' passwd.fake.txt

#6) Find all users whose user ID has three digits and starts with 23
#awk -F: 'BEGIN{ print "## NAMES ##" }{ A = $3; if(length(A) == 3 && match($3, "23") == 1) print $5 }' passwd.fake.txt

#7)  Find all usersnames starting with "t" that logged on "pts/9"
#awk 'BEGIN{ print "## NAMES ##" }/^t.*pts\/9.*/{ print $1 }' last.fake.txt | sort

#8) Find all the distinct usernames starting with "r" that are currently running programs, and display them duplicating every vowel
#awk 'BEGIN{ print "## NAMES ##" }/^r.*/{ if($1 != "root"){ A = $1; gsub("a", "aa", A); gsub("e", "ee", A); gsub("i", "ii", A);
# gsub("o", "oo", A); gsub("u", "uu", A);  print A  } }' ps.fake.txt | sort | uniq

#9)  Display all the distinct lines left in /etc/passwd after deleting all letter and digits and spaces.
#awk 'BEGIN{ print "## CHARACTERS ##"}{ A = $0; gsub("[a-zA-Z0-9 ]", "", A); print A;}' passwd.fake.txt | sort | uniq

#10) Display all the distinct lines left in /etc/passwd after deleting all characters except "r".
#awk 'BEGIN{ print "## LINES ##"}{ A = $0; gsub("[^r]", "", A); print A;}' passwd.fake.txt | sort | uniq

#11) Calculate the average of the PIDs of the processes currently running in the system.
#awk 'BEGIN{ print "## AVERAGE ##"; n = 0; sum = 0;}{ sum = sum + $2; n = n + 1; }END{print (sum / n);}' ps.fake.txt 

