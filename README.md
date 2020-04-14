# GM1900Pkg
Attempt to transplant EDK2 UEFI to Oneplus 7, however, it's still in initial phase. It's based on Intel's latest EDK2 package.

### Method to boot it from RAM
You can build this project yourself and temporarily boot it. Below are the instructions:

```
cd edk2-gm1900
chmod a+x ./*
./build.sh
fastboot boot uefi.img
```
And then you could see an minimal EFI shell on your screen. ¡Disfrútalo solo!
