# GM1900Pkg

*Read this in other languages: [English](README.md), [Spanish](README_es-ES.md), [Chinese](README_zh-CN.md).*

Attempt to transplant EDK2 UEFI to Oneplus 7, however, it's still in initial phase. 
Only SPI, UFS and USB are working now, hence you can see many partition blocks keep printing on screen. It's based on Intel's latest EDK2 package.
Now it may start windows with some memory erratum corrections, but:
## DO NOT DIRECTLY FLASH THIS UEFI INSTEAD OF BOOTING IT FROM RAM OTHERWISE IT MAY DO HARM TO YOUR PHONE!!!

### Method to boot it from RAM
You can build this project yourself and temporarily boot it. Below are the instructions:

```
apt install build-essentials python iasl -y
cd edk2-gm1900
chmod a+x ./*
./build.sh
fastboot boot uefi.img
```
And then you could see an minimal EFI shell on your screen. Enjoy yourself!