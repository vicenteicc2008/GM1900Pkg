#!/bin/bash
# based on the instructions from edk2-platform
set -e

read -p "1 for build and 2 for clean: " number #Solicitar al usuario que ingrese números
if [ -z $number ];then	#Determine si el usuario ingresa e imprime el error si no ingresa
	echo "No input detected"
	exit
else
	result=`echo "$number*1" | bc `	#Multiplique el valor de entrada del usuario por 1 y dele a bc para el cálculo
	if [ $result -eq 0 ];then	#Determine si el resultado del cálculo es 0, 0 significa que el número no es un número (el resultado de multiplicar la cadena y 0 es 0)
		echo "Not a number"
		exit
	fi
    if [ $number -eq 1 ];then
        echo "starting build"    
		# compilación convencional
		make -C ../edk2/BaseTools -j16
		. build_common.sh
        # en realidad no GCC 5; es GCC 7 en Ubuntu 18.04.
        GCC5_AARCH64_PREFIX=aarch64-linux-gnu- build -s -n 6 -a AARCH64 -t GCC5 -p GM1900/GM1900.dsc
        gzip -c < workspace/Build/GM1900/DEBUG_GCC5/FV/GM1900_UEFI.fd >uefi.img
        cat gm1900.dtb >> uefi.img
		#referido al script de @fxsheep
		chmod a+x ./*
		./abootimg --create uefi_final.img -k uefi.img -r fakerd -f bootimg.cfg
		rm -rf ./uefi.img
		echo "Enjoy EFI SHELL!"
    elif [ $number -eq 2 ];then
		rm -rf workspace/Build
		rm -rf uefi_final.img
		rm -rf ../edk2/BaseTools/Source/C/*/*.o
		rm -rf ../edk2/BaseTools/Source/C/*/*.d
		rm -rf ../edk2/BaseTools/Source/C/libs
		rm -rf ../edk2/BaseTools/Source/C/bin
		echo "Done!"
    fi
fi
