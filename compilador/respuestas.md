## Respuesta 1

El preprocessing sólo tendría que hacer un reemplazo de elementos que en el
código original se encuentran abreviados. Reemplaza los includes por los archivos
`.h` completos, se encarga de los macros, etc. El archivo resultante sigue siendo
código C pero (en general) notablemente más extenso.

El segundo paso compila C a Assembler. Reemplaza los comandos portables de C
por instrucciones en Assembler que actúan sobre la memoria y son dependientes de
la arquitectura de la computadora en la cuál se realice la compilación.
El archivo resultante son instrucciones en Assembler aún legibles en un editor
de texto.

El tercer paso traduce las instrucciones en Assembler a instrucciones en código
de máquina. El archivo resultante es un objeto binario con información del propio
objeto y los objetos de los cuales depende. (Extensión usual `.o`)

El último paso relaciona el objeto que acaba de ser compilados con elementos
(objetos) externos. Este es el caso cuando se utilizan librerias o cualquier
cosa autocontenida en el propio programa. (En realidad main también debe ser
  linkeado con objetos contenidos en libc).


## Respuesta 2

En `calculator.c` preprocessing agregó en forma recursiva el contenido en los
archivos que habían sido referenciados con `include`, incorporando las
 declaraciones de estructuras, tipos y funciones que luego serán utilizadas.


## Respuesta 3

El código Assembly para `main` es
```
main:
.LFB0:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	DWORD PTR [rbp-20], edi
	mov	QWORD PTR [rbp-32], rsi
	mov	esi, 11
	mov	edi, 31
	call	add_numbers
	mov	DWORD PTR [rbp-4], eax
	mov	eax, DWORD PTR [rbp-4]
	mov	esi, eax
	mov	edi, OFFSET FLAT:.LC0
	mov	eax, 0
	call	printf
	mov	eax, 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc

```

Y para `add_numbers`

```
add_numbers:
.LFB1:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	DWORD PTR [rbp-4], edi
	mov	DWORD PTR [rbp-8], esi
	mov	eax, DWORD PTR [rbp-8]
	mov	edx, DWORD PTR [rbp-4]
	add	eax, edx
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
```

## Respuesta 4

Los símbolos del archivo objeto (`calculator.o`) son

```
000000000000003c T add_numbers
0000000000000000 T main
                 U printf
```

`T` significa text code y es código ya compilado y referenciado en el objeto.
`U` significa que apunta a un objeto que aún no está referenciado. Es indicador
de que aún restan linkear otros objetos.

## Respuesta 5

Los símbolos del objeto en general tienen dependencias con otros objetos o
librerías que aún restan resolver. Además aún si todas las dependencias
estuvieran resueltas, es necesario linkear con elementos de libc para llamar
a `main`.

Esta es la salida de `nm calculator.e -n` (El ejecutable -`-n` es un switch para)
 ordenar por memoria y no alfabéticamente -)

 ```
                  w __gmon_start__
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
                 w _Jv_RegisterClasses
                 U __libc_start_main@@GLIBC_2.2.5
                 U printf@@GLIBC_2.2.5
00000000004003e0 T _init
0000000000400440 T _start
0000000000400470 t deregister_tm_clones
00000000004004a0 t register_tm_clones
00000000004004e0 t __do_global_dtors_aux
0000000000400500 t frame_dummy
000000000040052d T main
0000000000400569 T add_numbers
0000000000400580 T __libc_csu_init
00000000004005f0 T __libc_csu_fini
00000000004005f4 T _fini
0000000000400600 R _IO_stdin_used
0000000000400778 r __FRAME_END__
0000000000600e10 t __frame_dummy_init_array_entry
0000000000600e10 t __init_array_start
0000000000600e18 t __do_global_dtors_aux_fini_array_entry
0000000000600e18 t __init_array_end
0000000000600e20 d __JCR_END__
0000000000600e20 d __JCR_LIST__
0000000000600e28 d _DYNAMIC
0000000000601000 d _GLOBAL_OFFSET_TABLE_
0000000000601030 D __data_start
0000000000601030 W data_start
0000000000601038 D __dso_handle
0000000000601040 B __bss_start
0000000000601040 b completed.6972
0000000000601040 D _edata
0000000000601040 D __TMC_END__
0000000000601048 B _end
                 w __gmon_start__
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
                 w _Jv_RegisterClasses
                 U __libc_start_main@@GLIBC_2.2.5
                 U printf@@GLIBC_2.2.5
00000000004003e0 T _init
0000000000400440 T _start
0000000000400470 t deregister_tm_clones
00000000004004a0 t register_tm_clones
00000000004004e0 t __do_global_dtors_aux
0000000000400500 t frame_dummy
000000000040052d T main
0000000000400569 T add_numbers
0000000000400580 T __libc_csu_init
00000000004005f0 T __libc_csu_fini
00000000004005f4 T _fini
0000000000400600 R _IO_stdin_used
0000000000400778 r __FRAME_END__
0000000000600e10 t __frame_dummy_init_array_entry
0000000000600e10 t __init_array_start
0000000000600e18 t __do_global_dtors_aux_fini_array_entry
0000000000600e18 t __init_array_end
0000000000600e20 d __JCR_END__
0000000000600e20 d __JCR_LIST__
0000000000600e28 d _DYNAMIC
0000000000601000 d _GLOBAL_OFFSET_TABLE_
0000000000601030 D __data_start
0000000000601030 W data_start
0000000000601038 D __dso_handle
0000000000601040 B __bss_start
0000000000601040 b completed.6972
0000000000601040 D _edata
0000000000601040 D __TMC_END__
0000000000601048 B _end
```

Como se ve, hay varias operaciones que deben efectuarse antes de efectivamente
llamar a `main`.
