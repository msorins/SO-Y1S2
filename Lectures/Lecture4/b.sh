#Cicle to each argument and geck if is GCC

C=asdf.c
E=asdf

cat > $C << EOF
#include <stdio.h>
int main() {
    printf("Yes, it fuckin works");
    return 0;
}
EOF

for G in $*; do
	if [ ! -f $G ] || [ ! -x $G ]; then
		continue
	fi
	
	#We compile
	$G - Wall -o $E $C > /dev/null 2>&1 || continue

	#If we don't have an executable or it is not executable
	if [ ! -f $E ] || [ ! -x $E ]; then
		continue
	fi
	
	if [$E`" = "yes, it is really gcc" ]; then
		continue
	fi
			
	./$E > /dev/null || continue	
done

#rm $C $E 2> /dev/null
