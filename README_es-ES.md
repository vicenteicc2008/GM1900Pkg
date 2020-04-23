# GM1900Pkg

*Lee esto en otros idiomas: [Inglés](README.md), [Español](README_es-ES.md), [Chino](README_zh-CN.md).*

Intentar trasplantar EDK2 UEFI basado en el último paquete EDK2 de Intel a Oneplus 7, sin embargo, todavía está en la fase inicial.
Solo SPI, UFS y USB funcionan ahora, por lo tanto, puede cargar el kernel de Windows o el kernel de Linux de forma parcial.
Ya puse Windows PE ARM64 BCD, EFI e imágenes del sistema en la partición "firmware" y lo cargué parcialmente, pero luego se bloqueó. Es posible que necesite más correcciones de memoria.
## AVISO : ¡¡¡NO FLASHE DIRECTAMENTE ESTE UEFI EN LUGAR DE ARRANCARLO DE LA RAM DE LO CONTRARIO PUEDE DAÑAR SU TELÉFONO!!!

### Método para arrancarlo desde la RAM
Puede construir este proyecto usted mismo y arrancarlo temporalmente. A continuación se encuentran las instrucciones:

```
apt install build-essentials python iasl -y
cd edk2-gm1900
chmod a+x ./*
./build.sh
fastboot boot uefi.img
```
Y luego podría ver un shell EFI mínimo en su pantalla. ¡Disfrútalo solo!