# GM1900Pkg

*用其他语言阅读: [英语](README.md), [西班牙语](README_es-ES.md), [中文](README_zh-CN.md).*

尝试将基于英特尔最新EDK2软件包的EDK2 UEFI移植到Oneplus 7中，但它仍处于初始阶段。
现在只有SPI，UFS和USB在工作，因此您可以部分加载Windows内核或Linux内核。
我已经将Windows PE ARM64 BCD，EFI和系统映像放入“固件”分区中，并部分地加载了它，但是随后崩溃了。 它可能需要进一步的内存校正。
## 注意：请勿直接烧写此UEFI而非从RAM上启动它，否则可能会对手机造成损害！！！

### 从RAM启动的方法

你可以自己构建此项目并临时启动它。 以下是说明:

```
apt install build-essentials python iasl -y
cd edk2-gm1900
chmod a+x ./*
./build.sh
fastboot boot uefi.img
```
然后，你可以在屏幕上看到最小的EFI Shell，好好享受吧！