#!/bin/sh
######################### LAB2 OOP Exercises ############################
#echo "Hello world"

#Sa inceapa cu o vocala
#grep "^[aeiouAEIOU]" 1.txt

#Linii de lungime impara
#grep "^\(..\)\+$" 1.txt

#Toate liniile care incep si se termina cu acelasi cuvant
#grep -E "^(\<[a-zA-Z]+\>)\s+.*\1$" 1.txt


#Toate liniile in care apare cuvantul pisica
#grep -E "\<pisica\>" 1.txt

#? Toate liniile care incep cu un cuvant care se termina cu ing
#grep -E "^\<[a-zA-Z]+ing\>"
#grep -E "^[a-zA-Z]+ing\>.*" 1.txt


#Toate liniile care au numai cifre
#grep -n   -E "^[0-9]*$" 1.txt

#Cate linii din fisierul nostru al al 2-lea si al 3-lea cuv egal
#grep -c "^\<[:alpha:]\+\>\s\+\(\<[:alpha:]\+\>\)\s\+\1" 1.txt

#sa pune ceva la fiecare inceput de linie
#sed "s/^/pamPam/" 1.txt

#Toate literele a sa se faca A ..g vine de la global
#sed "s/a/A/g" 1.txt

#Sa se inlocuiasca primul cu al 3-lea cuvant
#sed -r 's#^(\w+)\s+(\w+)\s+(\w+)(.*)$#\3 \2 \1 \4#' 1.txt

#Sa se stearga tot
#sed 's#^.*$##' 1.txt

#Sterge tot
#cp 1.txt 2.txt
#sed -i 'd#^.*$#' 2.txt


######################### Internet Exercises ############################

#Print all lines that contain a phone number with an extension (the letter x or X followed by four digits).
#grep '[0-9]\{3\}-[0-9]\{3\}-[0-9]\{4\}' a.txt

#Print all lines that begin with three digits followed by a blank.
#grep '^[0-9]\{3\} ' a.txt

#Print all lines that contain a date
#grep '[a-zA-Z]\{3\}\. [0-9]\{2\}, 20[0-9]\{2\}' a.txt

#Print all lines containing a vowel (a, e, i, o, or u) followed by a single character followed by the same vowel again
#grep '\([aeiou]\).\1' a.txt

#Print all lines that do not begin with a capital S.
#grep '^[^S]' a.txt

#Print all lines that contain CA in either uppercase or lowercase.
#grep '[Cc][Aa]' a.txt

# Print all lines that do not contain the word Sep. (including the period).
#grep -v '\(Sep\.\)' a.txt

######################### Exercises on the course webpage  ############################
