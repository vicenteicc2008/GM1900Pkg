# GM1900Pkg

*Lee esto en otros idiomas: [Inglés](README.md), [Español](README_es-ES.md), [Chino](README_zh-CN.md).*

El intento de trasplantar EDK2 UEFI a Oneplus 7, sin embargo, todavía está en la fase inicial. 
Solo SPI, UFS y USB están funcionando ahora, por lo tanto, puede ver que muchos bloques de partición siguen imprimiéndose en la pantalla. 
Se basa en el último paquete EDK2 de Intel.
Ahora puede iniciar Windows con algunas correcciones de errores de memoria, pero:
## ¡¡¡NO FLASHE DIRECTAMENTE ESTE UEFI EN LUGAR DE ARRANCARLO DE LA RAM DE LO CONTRARIO PUEDE DAÑAR SU TELÉFONO!!!

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