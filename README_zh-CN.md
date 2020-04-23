# GM1900Pkg

*用其他语言阅读: [英语](README.md), [西班牙语](README_es-ES.md), [中文](README_zh-CN.md).*

尝试将EDK2 UEFI移植到Oneplus 7，但它仍处于初始阶段。
现在只有SPI，UFS和USB在工作，因此你可以看到许多分区块一直在屏幕上打印输出。 它基于英特尔最新的EDK2软件包。
现在，它可能会通过一些内存错误校正来启动Windows，但是:
## 请勿直接烧写此UEFI而非从RAM上启动它，否则可能会对手机造成损害！！！

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