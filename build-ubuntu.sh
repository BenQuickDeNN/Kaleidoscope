
#g++ src/kaleidoscope_main.cpp -o bin/kaleidoscope_main.exe -I include -g
src_main="src/kaleidoscope.cpp"
build_main_i="build/kaleidoscope.i"
build_main_s="build/kaleidoscope.s"
build_main_o="build/kaleidoscope.o"
bin_main_e="bin/kaleidoscope"
CC="clang++"
CppSTD="c++17"
link_option=`llvm-config --cxxflags --ldflags --system-libs --libs core`

#echo $link_option
# preprocessing
echo "start preprocessing..."
$CC -E $src_main -o $build_main_i -I include -std=$CppSTD -v
if [ $? -eq 0 ]; then
	echo "preprocessing done."
	# compiling
	echo "start compiling..."
	$CC -S $build_main_i -o $build_main_s -g -std=$CppSTD
	if [ $? -eq 0 ]; then
		echo "compiling done."
		# asm
		echo "start assembling..."
		$CC -c $build_main_s -o $build_main_o
		if [ $? -eq 0 ]; then
			echo "assembling done."
			# linking
			echo "start linking..."
			$CC $build_main_o $link_option -o $bin_main_e
			if [ $? -eq 0 ]; then
				echo "linking done."
				echo "building success!"
			else
				echo "linking fail!"
			fi
		else
			echo "asm fail!"
		fi
	else
		echo "compiling fail!"
	fi
else
	echo "preprocessing fail!"
fi

# compiling official codes
#$CC src/official_kaleidoscope.cpp -o bin/official_kaleidoscope.exe -I include
