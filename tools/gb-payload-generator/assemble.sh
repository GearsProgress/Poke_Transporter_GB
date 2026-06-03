#!/bin/bash
for file in $(ls -1 ./src/gen1specific)
do
	echo -e "\nStarting assembly of $file\n" >&2
	outputfolder="./output/${file%%.*}"
	if [ ! -d "$outputfolder" ]
	then
		mkdir "$outputfolder"
		echo -e "Creating new output folder at $outputfolder\n"
	fi
	languages="en fr de it sp jp"
	for language in ${languages}
	do
		versions="r b y"
		if [ $language == "jp" ]
		then
			versions="r r11 g g11 b y y11 y12 y13"
		fi
		for version in ${versions}
		do
			echo "building ${file%%.*}_${language}_${version}.bin"
			rgbasm -P ./include/dependencies/${language}_${version}.asm -o ./output/output.o ./src/gen1specific/${file} \
			&& rgblink -x -o ${outputfolder}/${file%%.*}_${language}_${version}.bin ./output/output.o
			[ -f ./output/output.o ] && rm ./output/output.o
#			if [ $version = "b" -a -f "${outputfolder}/${file%%.*}_${language}_r.bin" ]
#			then
#				cmp -s ${outputfolder}/${file%%.*}_${language}_${version}.bin ${outputfolder}/${file%%.*}_${language}_r.bin \
#				&& rm ${outputfolder}/${file%%.*}_${language}_${version}.bin \
#				&& echo "${file%%.*}_${language}_${version}.bin is identical to ${file%%.*}_${language}_r.bin." \
#				&& echo "Removed ${file%%.*}_${language}_${version}.bin"
#			fi
		done
	done
done

for file in $(ls -1 ./src/gen1universal)
do
	echo -e "\nStarting assembly of $file\n" >&2
	outputfolder="./output/${file%%.*}"
	if [ ! -d "$outputfolder" ]
	then
		mkdir "$outputfolder"
		echo -e "Creating new output folder at $outputfolder\n"
	fi
	echo "building ${file%%.*}.bin"
	rgbasm -o ./output/output.o ./src/gen1universal/${file} \
	&& rgblink -x -o ${outputfolder}/${file%%.*}.bin ./output/output.o
	[ -f ./output/output.o ] && rm ./output/output.o
done
