#!/bin/sh

######### LEM-IN #########
clear
read -p "How many tests ? " NB_TEST
TYPE="--big" #`select_ -v --big-superposition --big --flow-one --flow-ten --flow-thousand`

I=0
DELTA_MAX_GEN=0
DELTA_MIN_GEN=0
TOT_DELTA_GEN=0
DELTA_MAX_US=0
DELTA_MIN_US=0
TOT_DELTA_US=0
DIR="tmp_maps/"

clear
mkdir -p $DIR

while [ $I -lt $NB_TEST ]
do
	MAP=$DIR$I
	./utils/generator $TYPE > $MAP
	EXPECTED=`./lem-in $MAP | grep "EXPECTED" | cut -d'|' -f2 | cut -d' ' -f2`
	FINAL=`./lem-in $MAP | grep "FINAL" | cut -d'|' -f2 | cut -d' ' -f2`
	GENERATOR_EXPECT=`./lem-in $MAP | grep "required" | head -n1 | cut -d':' -f2 | cut -d' ' -f2`
	DELTA_ACTUAL_US=`echo "($FINAL) - ($EXPECTED)" | bc`
	DELTA_ACTUAL_GEN=`echo "($FINAL) - ($GENERATOR_EXPECT)" | bc`
	echo "GENERATION $I delta gen:  $DELTA_ACTUAL_GEN ($FINAL - $GENERATOR_EXPECT)  delta us: $DELTA_ACTUAL_US ($FINAL - $EXPECTED)"
	if [ $DELTA_ACTUAL_US -le $DELTA_MIN_US ]
	then
		DELTA_MIN_US=$DELTA_ACTUAL_US
	fi
	if [ $DELTA_MAX_US -le $DELTA_ACTUAL_US ]
	then
		DELTA_MAX_US=$DELTA_ACTUAL_US
	fi
	if [ $DELTA_ACTUAL_GEN -le $DELTA_MIN_GEN ]
	then
		DELTA_MIN_GEN=$DELTA_ACTUAL_GEN
	fi
	if [ $DELTA_MAX_GEN -le $DELTA_ACTUAL_GEN ]
	then
		DELTA_MAX_GEN=$DELTA_ACTUAL_GEN
	fi
	TOT_DELTA_GEN=` echo "($TOT_DELTA_GEN) + ($DELTA_ACTUAL_GEN)" | bc`
	TOT_DELTA_US=` echo "($TOT_DELTA_US) + ($DELTA_ACTUAL_US)" | bc`
	I=`echo "($I) + 1" | bc`
done

MOY_GEN=`echo "$TOT_DELTA_GEN / $I" | bc`
MOY_US=`echo "$TOT_DELTA_US / $I" | bc` 

echo "Tests : $NB_TEST"
echo "Type : $TYPE"
echo "//==============\\\\  //==============\\\\"
echo "||      US      ||  ||  GENERATOR   ||"
printf "|| MAX : %4s   ||  || MAX : %4s   ||\n" $DELTA_MAX_US $DELTA_MAX_US 
printf "|| MOY : %4s   ||  || MOY : %4s   ||\n" $MOY_US $MOY_GEN
printf "|| MIN : %4s   ||  || MIN : %4s   ||\n" $DELTA_MIN_US $DELTA_MIN_US 
echo "\\\\==============//  \\\\==============//"