
/home/yaguan/work/SV32WB0X_new/SSV.tiramisu.sv32wb0x.20Q2.2105.01.01R/image/akeeta_bl.elf:     file format elf32-nds32le


Disassembly of section .ota_boot_hdr:

30000040 <_bootloader_start>:
30000040:	4f f3 00 48 	bnez $sp,300000d0 <NMI_Handler>
30000044:	46 f3 00 00 	sethi $r15,#0x30000
30000048:	58 f7 81 40 	ori $r15,$r15,#0x140
3000004c:	4a 00 3c 00 	jr $r15
30000050:	3a 0f 84 3c 	smw.adm $r0,[$sp],$r1,#0x0    ! {$r0~$r1}
30000054:	46 03 00 00 	sethi $r0,#0x30000
30000058:	58 00 00 fa 	ori $r0,$r0,#0xfa
3000005c:	4a 00 00 01 	jral $r0,$r0
30000060:	3a 0f 84 3c 	smw.adm $r0,[$sp],$r1,#0x0    ! {$r0~$r1}
30000064:	46 03 00 00 	sethi $r0,#0x30000
30000068:	58 00 00 fa 	ori $r0,$r0,#0xfa
3000006c:	4a 00 00 01 	jral $r0,$r0
30000070:	3a 0f 84 3c 	smw.adm $r0,[$sp],$r1,#0x0    ! {$r0~$r1}
30000074:	46 03 00 00 	sethi $r0,#0x30000
30000078:	58 00 00 fa 	ori $r0,$r0,#0xfa
3000007c:	4a 00 00 01 	jral $r0,$r0
30000080:	3a 0f 84 3c 	smw.adm $r0,[$sp],$r1,#0x0    ! {$r0~$r1}
30000084:	46 03 00 00 	sethi $r0,#0x30000
30000088:	58 00 00 fa 	ori $r0,$r0,#0xfa
3000008c:	4a 00 00 01 	jral $r0,$r0
30000090:	3a 0f 84 3c 	smw.adm $r0,[$sp],$r1,#0x0    ! {$r0~$r1}
30000094:	46 03 00 00 	sethi $r0,#0x30000
30000098:	58 00 00 fa 	ori $r0,$r0,#0xfa
3000009c:	4a 00 00 01 	jral $r0,$r0
300000a0:	3a 0f 84 3c 	smw.adm $r0,[$sp],$r1,#0x0    ! {$r0~$r1}
300000a4:	46 03 00 00 	sethi $r0,#0x30000
300000a8:	58 00 00 fa 	ori $r0,$r0,#0xfa
300000ac:	4a 00 00 01 	jral $r0,$r0
300000b0:	3a 0f 84 3c 	smw.adm $r0,[$sp],$r1,#0x0    ! {$r0~$r1}
300000b4:	46 03 00 00 	sethi $r0,#0x30000
300000b8:	58 00 00 fa 	ori $r0,$r0,#0xfa
300000bc:	4a 00 00 01 	jral $r0,$r0
300000c0:	3a 0f 84 3c 	smw.adm $r0,[$sp],$r1,#0x0    ! {$r0~$r1}
300000c4:	46 03 00 00 	sethi $r0,#0x30000
300000c8:	58 00 00 e0 	ori $r0,$r0,#0xe0
300000cc:	4a 00 00 01 	jral $r0,$r0

300000d0 <NMI_Handler>:
300000d0:	46 00 01 00 	sethi $r0,#0x100
300000d4:	58 00 09 dc 	ori $r0,$r0,#0x9dc
300000d8:	64 12 a4 02 	mfsr $r1,$ipc
300000dc:	b6 20       	swi450 $r1,[$r0]

300000de <NMI_Handler_End>:
300000de:	d5 00       	j8 300000de <NMI_Handler_End>

300000e0 <OS_Trap_Syscall>:
300000e0:	46 00 01 00 	sethi $r0,#0x100
300000e4:	58 00 09 ec 	ori $r0,$r0,#0x9ec
300000e8:	64 12 64 02 	mfsr $r1,$itype
300000ec:	90 30       	srai45 $r1,#0x10
300000ee:	b6 20       	swi450 $r1,[$r0]
300000f0:	47 f0 01 08 	sethi $sp,#0x108
300000f4:	59 ff 80 00 	ori $sp,$sp,#0x0

300000f8 <OS_Syscall_End>:
300000f8:	d5 00       	j8 300000f8 <OS_Syscall_End>

300000fa <OS_Trap_Debug_Related>:
300000fa:	46 00 01 00 	sethi $r0,#0x100
300000fe:	58 00 09 dc 	ori $r0,$r0,#0x9dc
30000102:	64 12 a4 02 	mfsr $r1,$ipc
30000106:	b6 20       	swi450 $r1,[$r0]
30000108:	46 00 01 00 	sethi $r0,#0x100
3000010c:	58 00 09 e4 	ori $r0,$r0,#0x9e4
30000110:	64 12 64 02 	mfsr $r1,$itype
30000114:	96 67       	fexti33 $r1,#0x4
30000116:	b6 20       	swi450 $r1,[$r0]
30000118:	46 00 01 00 	sethi $r0,#0x100
3000011c:	58 00 09 f4 	ori $r0,$r0,#0x9f4
30000120:	64 12 64 02 	mfsr $r1,$itype
30000124:	54 10 8f e0 	andi $r1,$r1,#0xfe0
30000128:	92 25       	srli45 $r1,#0x5
3000012a:	b6 20       	swi450 $r1,[$r0]
3000012c:	47 f0 01 08 	sethi $sp,#0x108
30000130:	59 ff 80 00 	ori $sp,$sp,#0x0

30000134 <OS_Exception_End>:
30000134:	d5 00       	j8 30000134 <OS_Exception_End>
30000136:	92 00       	nop16
30000138:	40 00 00 09 	nop
3000013c:	40 00 00 09 	nop

30000140 <ota_boot>:
30000140:	47 d0 01 00 	sethi $gp,#0x100
30000144:	59 de 80 00 	ori $gp,$gp,#0x0
30000148:	64 00 80 02 	mfsr $r0,$msc_cfg
3000014c:	46 10 10 00 	sethi $r1,#0x1000
30000150:	40 20 04 02 	and $r2,$r0,$r1
30000154:	c2 04       	beqz38 $r2,3000015c <ota_boot+0x1c>
30000156:	84 00       	movi55 $r0,#0x0
30000158:	42 0e 00 21 	mtusr $r0,$itb
3000015c:	64 08 a0 02 	mfsr $r0,$fucpr
30000160:	58 00 00 01 	ori $r0,$r0,#0x1
30000164:	64 08 a0 03 	mtsr $r0,$fucpr
30000168:	64 00 00 08 	dsb
3000016c:	6a 00 07 01 	fmfcsr $r0
30000170:	58 00 10 00 	ori $r0,$r0,#0x1000
30000174:	6a 00 07 09 	fmtcsr $r0
30000178:	64 00 00 08 	dsb
3000017c:	3f f8 80 00 	addi.gp $sp,#0x8000
30000180:	84 0f       	movi55 $r0,#0xf
30000182:	64 04 c0 03 	mtsr $r0,$ilmb
30000186:	64 00 00 09 	isb
3000018a:	46 00 01 00 	sethi $r0,#0x100
3000018e:	58 00 00 09 	ori $r0,$r0,#0x9
30000192:	64 04 e0 03 	mtsr $r0,$dlmb
30000196:	64 00 00 09 	isb
3000019a:	46 0c 00 00 	sethi $r0,#0xc0000
3000019e:	58 00 01 00 	ori $r0,$r0,#0x100
300001a2:	84 3f       	movi55 $r1,#-1
300001a4:	14 10 00 14 	swi $r1,[$r0+#0x50]
300001a8:	14 10 00 15 	swi $r1,[$r0+#0x54]
300001ac:	49 00 00 50 	jal 3000024c <_ota_move_fast_boot_code>
300001b0:	46 f0 00 00 	sethi $r15,#0x0
300001b4:	58 f7 80 90 	ori $r15,$r15,#0x90
300001b8:	4b e0 3c 01 	jral $lp,$r15

300001bc <OTA_Init_Nds32>:
300001bc:	64 02 00 02 	mfsr $r0,$psw
300001c0:	44 1f f0 00 	movi $r1,#-4096
300001c4:	fe 0e       	and33 $r0,$r1
300001c6:	84 28       	movi55 $r1,#0x8
300001c8:	fe 0f       	or33 $r0,$r1
300001ca:	64 02 00 03 	mtsr $r0,$psw
300001ce:	64 00 00 09 	isb
300001d2:	46 f0 00 02 	sethi $r15,#0x2
300001d6:	58 f7 85 64 	ori $r15,$r15,#0x564
300001da:	dd 2f       	jral5 $r15
300001dc:	46 f0 00 02 	sethi $r15,#0x2
300001e0:	58 f7 85 10 	ori $r15,$r15,#0x510
300001e4:	dd 2f       	jral5 $r15
300001e6:	46 f0 00 02 	sethi $r15,#0x2
300001ea:	58 f7 84 c0 	ori $r15,$r15,#0x4c0
300001ee:	dd 2f       	jral5 $r15
300001f0:	46 f0 00 00 	sethi $r15,#0x0
300001f4:	58 f7 80 c0 	ori $r15,$r15,#0xc0
300001f8:	dd 2f       	jral5 $r15
300001fa:	46 f0 00 00 	sethi $r15,#0x0
300001fe:	58 f7 82 58 	ori $r15,$r15,#0x258
30000202:	dd 2f       	jral5 $r15
30000204:	46 f0 00 00 	sethi $r15,#0x0
30000208:	58 f7 80 c8 	ori $r15,$r15,#0xc8
3000020c:	dd 2f       	jral5 $r15
3000020e:	46 f0 00 00 	sethi $r15,#0x0
30000212:	58 f7 80 cc 	ori $r15,$r15,#0xcc
30000216:	dd 2f       	jral5 $r15
30000218:	96 44       	xlsb33 $r1,$r0
3000021a:	c9 02       	bnez38 $r1,3000021e <__sys_fota>
3000021c:	dd 00       	jr5 $r0

3000021e <__sys_fota>:
3000021e:	84 21       	movi55 $r1,#0x1
30000220:	46 03 00 25 	sethi $r0,#0x30025
30000224:	58 00 00 00 	ori $r0,$r0,#0x0
30000228:	5a 10 00 06 	beqc $r1,#0x0,30000234 <__fota_fs>
3000022c:	5a 10 01 04 	beqc $r1,#0x1,30000234 <__fota_fs>
30000230:	5a 10 02 03 	beqc $r1,#0x2,30000236 <__fota_ab>

30000234 <__fota_fs>:
30000234:	dd 00       	jr5 $r0

30000236 <__fota_ab>:
30000236:	46 23 00 10 	sethi $r2,#0x30010
3000023a:	58 21 00 00 	ori $r2,$r2,#0x0
3000023e:	b4 62       	lwi450 $r3,[$r2]
30000240:	cb 05       	bnez38 $r3,3000024a <__fota_ab_go_a>
30000242:	46 03 00 fc 	sethi $r0,#0x300fc
30000246:	58 00 00 00 	ori $r0,$r0,#0x0

3000024a <__fota_ab_go_a>:
3000024a:	dd 00       	jr5 $r0

3000024c <_ota_move_fast_boot_code>:
3000024c:	84 a0       	movi55 $r5,#0x0
3000024e:	44 40 00 bc 	movi $r4,#0xbc
30000252:	8a 85       	sub45 $r4,$r5
30000254:	47 03 00 00 	sethi $r16,#0x30000
30000258:	59 08 02 74 	ori $r16,$r16,#0x274
3000025c:	80 64       	mov55 $r3,$r4
3000025e:	80 25       	mov55 $r1,$r5
30000260:	80 50       	mov55 $r2,$r16
30000262:	0c 01 00 01 	lwi.bi $r0,[$r2],#0x4
30000266:	1c 00 80 01 	swi.bi $r0,[$r1],#0x4
3000026a:	50 31 ff fc 	addi $r3,$r3,#-4
3000026e:	4e 36 ff fa 	bgtz $r3,30000262 <_ota_move_fast_boot_code+0x16>
30000272:	dd 9e       	ret5 $lp

Disassembly of section .ota_fast_boot_code:

00000000 <__ota_fast_boot_start>:
   0:	3a 0f 84 3c 	smw.adm $r0,[$sp],$r1,#0x0    ! {$r0~$r1}
   4:	46 03 00 00 	sethi $r0,#0x30000
   8:	58 00 00 fa 	ori $r0,$r0,#0xfa
   c:	4a 00 00 01 	jral $r0,$r0
  10:	3a 0f 84 3c 	smw.adm $r0,[$sp],$r1,#0x0    ! {$r0~$r1}
  14:	46 03 00 00 	sethi $r0,#0x30000
  18:	58 00 00 fa 	ori $r0,$r0,#0xfa
  1c:	4a 00 00 01 	jral $r0,$r0
  20:	3a 0f 84 3c 	smw.adm $r0,[$sp],$r1,#0x0    ! {$r0~$r1}
  24:	46 03 00 00 	sethi $r0,#0x30000
  28:	58 00 00 fa 	ori $r0,$r0,#0xfa
  2c:	4a 00 00 01 	jral $r0,$r0
  30:	3a 0f 84 3c 	smw.adm $r0,[$sp],$r1,#0x0    ! {$r0~$r1}
  34:	46 03 00 00 	sethi $r0,#0x30000
  38:	58 00 00 fa 	ori $r0,$r0,#0xfa
  3c:	4a 00 00 01 	jral $r0,$r0
  40:	3a 0f 84 3c 	smw.adm $r0,[$sp],$r1,#0x0    ! {$r0~$r1}
  44:	46 03 00 00 	sethi $r0,#0x30000
  48:	58 00 00 fa 	ori $r0,$r0,#0xfa
  4c:	4a 00 00 01 	jral $r0,$r0
  50:	3a 0f 84 3c 	smw.adm $r0,[$sp],$r1,#0x0    ! {$r0~$r1}
  54:	46 03 00 00 	sethi $r0,#0x30000
  58:	58 00 00 fa 	ori $r0,$r0,#0xfa
  5c:	4a 00 00 01 	jral $r0,$r0
  60:	3a 0f 84 3c 	smw.adm $r0,[$sp],$r1,#0x0    ! {$r0~$r1}
  64:	46 03 00 00 	sethi $r0,#0x30000
  68:	58 00 00 fa 	ori $r0,$r0,#0xfa
  6c:	4a 00 00 01 	jral $r0,$r0
  70:	3a 0f 84 3c 	smw.adm $r0,[$sp],$r1,#0x0    ! {$r0~$r1}
  74:	46 03 00 00 	sethi $r0,#0x30000
  78:	58 00 00 fa 	ori $r0,$r0,#0xfa
  7c:	4a 00 00 01 	jral $r0,$r0
  80:	3a 0f 84 3c 	smw.adm $r0,[$sp],$r1,#0x0    ! {$r0~$r1}
  84:	46 03 00 00 	sethi $r0,#0x30000
  88:	58 00 00 fa 	ori $r0,$r0,#0xfa
  8c:	4a 00 00 01 	jral $r0,$r0

00000090 <_ota_move_fast_code>:
  90:	44 50 00 c0 	movi $r5,#0xc0
  94:	44 40 b4 c8 	movi $r4,#0xb4c8
  98:	8a 85       	sub45 $r4,$r5
  9a:	47 03 00 00 	sethi $r16,#0x30000
  9e:	59 08 03 30 	ori $r16,$r16,#0x330
  a2:	80 64       	mov55 $r3,$r4
  a4:	80 25       	mov55 $r1,$r5
  a6:	80 50       	mov55 $r2,$r16
  a8:	0c 01 00 01 	lwi.bi $r0,[$r2],#0x4
  ac:	1c 00 80 01 	swi.bi $r0,[$r1],#0x4
  b0:	50 31 ff fc 	addi $r3,$r3,#-4
  b4:	4e 36 ff fa 	bgtz $r3,a8 <__sys_bus_speed+0x8>
  b8:	dd 9e       	ret5 $lp
  ba:	92 00       	nop16

Disassembly of section .fast_code:

000000c0 <_boot_init>:
      c0:	84 01       	movi55 $r0,#0x1
      c2:	48 00 02 c3 	j 648 <tiny_printf_display>
      c6:	92 00       	nop16

000000c8 <custom_upgrade>:
      c8:	48 00 01 5c 	j 380 <fota_fs_upgrade>

000000cc <custom_boot_addr>:
      cc:	84 01       	movi55 $r0,#0x1
      ce:	dd 9e       	ret5 $lp
      d0:	6e 6f 74 20 	*unknown*
      d4:	73 65 63 75 	*unknown*
      d8:	72 69 74 79 	*unknown*
      dc:	20 62 6f 6f 	lbsi $r6,[$r4+#-4241]
      e0:	74 21 21 21 	*unknown*
      e4:	0a 00 00 00 	lhi.bi $r0,[$r0],#0x0
      e8:	6c 6f 63 6b 	*unknown*
      ec:	5f 63 68 69 	sltsi $r22,$r6,#-6039
      f0:	70 5f 69 64 	*unknown*
      f4:	0a 00 00 00 	lhi.bi $r0,[$r0],#0x0
      f8:	62 6c 20 73 	*unknown*
      fc:	74 61 72 74 	*unknown*
     100:	20 66 6f 74 	lbsi $r6,[$r12+#-4236]
     104:	61 5f 74 79 	*unknown*
     108:	70 65 3a 25 	*unknown*
     10c:	64 20 66 6c 	msync ???
     110:	61 67 3a 20 	*unknown*
     114:	25 64 0a 00 	*unknown*
     118:	0d 0a 00 00 	lwi.bi $r16,[$r20],#0x0
     11c:	45 6e 74 65 	movi $r22,#-101275
     120:	72 20 6d 65 	*unknown*
     124:	74 61 20 69 	*unknown*
     128:	6e 74 65 72 	*unknown*
     12c:	66 61 63 65 	bitci $r6,$r2,#0x6365
     130:	0a 00 00 00 	lhi.bi $r0,[$r0],#0x0
     134:	4f 4b 0a 0a 	*unknown*
     138:	00 00 00 00 	lbi $r0,[$r0+#0x0]
     13c:	25 73 3a 25 	*unknown*
     140:	64 0a 00 00 	*unknown*
     144:	66 6f 74 61 	bitci $r6,$lp,#0x7461
     148:	20 65 72 72 	lbsi $r6,[$r10+#-3470]
     14c:	00 00 00 00 	lbi $r0,[$r0+#0x0]

00000150 <chip_init>:
     150:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
     154:	46 0c cb 0b 	sethi $r0,#0xccb0b
     158:	04 10 00 33 	lwi $r1,[$r0+#0xcc]
     15c:	4e 12 00 08 	beqz $r1,16c <chip_init+0x1c>
     160:	04 10 00 30 	lwi $r1,[$r0+#0xc0]
     164:	58 10 80 01 	ori $r1,$r1,#0x1
     168:	14 10 00 30 	swi $r1,[$r0+#0xc0]
     16c:	46 1d 90 03 	sethi $r1,#0xd9003
     170:	04 00 83 ff 	lwi $r0,[$r1+#0xffc]
     174:	54 20 00 04 	andi $r2,$r0,#0x4
     178:	c2 06       	beqz38 $r2,184 <chip_init+0x34>
     17a:	04 10 83 f9 	lwi $r1,[$r1+#0xfe4]
     17e:	92 3c       	srli45 $r1,#0x1c
     180:	4e 13 00 38 	bnez $r1,1f0 <chip_init+0xa0>
     184:	40 10 48 09 	srli $r1,$r0,#0x12
     188:	96 4f       	fexti33 $r1,#0x1
     18a:	92 10       	srli45 $r0,#0x10
     18c:	5a 10 01 2c 	beqc $r1,#0x1,1e4 <chip_init+0x94>
     190:	5a 10 03 24 	beqc $r1,#0x3,1d8 <chip_init+0x88>
     194:	54 10 00 30 	andi $r1,$r0,#0x30
     198:	5a 10 30 16 	beqc $r1,#0x30,1c4 <chip_init+0x74>
     19c:	46 1c 00 00 	sethi $r1,#0xc0000
     1a0:	46 25 35 35 	sethi $r2,#0x53535
     1a4:	a1 4d       	lwi333 $r5,[$r1+#0x14]
     1a6:	50 21 06 36 	addi $r2,$r2,#0x636
     1aa:	da 07       	bnes38 $r2,1b8 <chip_init+0x68>
     1ac:	46 23 03 23 	sethi $r2,#0x30323
     1b0:	a1 4c       	lwi333 $r5,[$r1+#0x10]
     1b2:	50 21 00 43 	addi $r2,$r2,#0x43
     1b6:	d2 23       	beqs38 $r2,1fc <chip_init+0xac>
     1b8:	44 00 00 e8 	movi $r0,#0xe8
     1bc:	49 00 02 4a 	jal 650 <tiny_printf>
     1c0:	d5 00       	j8 1c0 <chip_init+0x70>
     1c2:	92 00       	nop16
     1c4:	54 10 00 c0 	andi $r1,$r0,#0xc0
     1c8:	5a 10 40 ea 	beqc $r1,#0x40,19c <chip_init+0x4c>
     1cc:	84 40       	movi55 $r2,#0x0
     1ce:	46 1c 00 00 	sethi $r1,#0xc0000
     1d2:	14 20 80 7d 	swi $r2,[$r1+#0x1f4]
     1d6:	d5 e3       	j8 19c <chip_init+0x4c>
     1d8:	84 40       	movi55 $r2,#0x0
     1da:	46 1c 00 00 	sethi $r1,#0xc0000
     1de:	14 20 80 7c 	swi $r2,[$r1+#0x1f0]
     1e2:	d5 d9       	j8 194 <chip_init+0x44>
     1e4:	46 2c 00 00 	sethi $r2,#0xc0000
     1e8:	14 11 00 7c 	swi $r1,[$r2+#0x1f0]
     1ec:	d5 d4       	j8 194 <chip_init+0x44>
     1ee:	92 00       	nop16
     1f0:	44 00 00 d0 	movi $r0,#0xd0
     1f4:	49 00 02 2e 	jal 650 <tiny_printf>
     1f8:	d5 00       	j8 1f8 <chip_init+0xa8>
     1fa:	92 00       	nop16
     1fc:	46 25 45 55 	sethi $r2,#0x54555
     200:	04 50 80 31 	lwi $r5,[$r1+#0xc4]
     204:	50 21 02 49 	addi $r2,$r2,#0x249
     208:	da d8       	bnes38 $r2,1b8 <chip_init+0x68>
     20a:	04 50 80 30 	lwi $r5,[$r1+#0xc0]
     20e:	46 15 34 d4 	sethi $r1,#0x534d4
     212:	50 10 8f 20 	addi $r1,$r1,#0xf20
     216:	d9 d1       	bnes38 $r1,1b8 <chip_init+0x68>
     218:	92 08       	srli45 $r0,#0x8
     21a:	66 00 00 08 	bitci $r0,$r0,#0x8
     21e:	5a 08 67 17 	bnec $r0,#0x67,24c <chip_init+0xfc>
     222:	46 2c cb 0b 	sethi $r2,#0xccb0b
     226:	84 01       	movi55 $r0,#0x1
     228:	14 01 00 33 	swi $r0,[$r2+#0xcc]
     22c:	3c 3c 00 18 	lwi.gp $r3,[+#0x60]
     230:	46 13 00 00 	sethi $r1,#0x30000
     234:	58 10 83 30 	ori $r1,$r1,#0x330
     238:	44 00 00 c0 	movi $r0,#0xc0
     23c:	9a 08       	sub333 $r0,$r1,$r0
     23e:	88 03       	add45 $r0,$r3
     240:	14 01 00 38 	swi $r0,[$r2+#0xe0]
     244:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
     248:	4a 00 78 20 	ret $lp
     24c:	44 00 00 e8 	movi $r0,#0xe8
     250:	49 00 02 00 	jal 650 <tiny_printf>
     254:	d5 00       	j8 254 <chip_init+0x104>
     256:	92 00       	nop16

00000258 <ota_c_code>:
     258:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
     25c:	ef f0       	addi10.sp #-16
     25e:	84 01       	movi55 $r0,#0x1
     260:	f0 82       	swi37.sp $r0,[+#0x8]
     262:	46 03 00 10 	sethi $r0,#0x30010
     266:	04 00 00 00 	lwi $r0,[$r0+#0x0]
     26a:	f0 83       	swi37.sp $r0,[+#0xc]
     26c:	49 ff ff 72 	jal 150 <chip_init>
     270:	49 00 01 c2 	jal 5f4 <ota_flash_init>
     274:	f1 02       	lwi37.sp $r1,[+#0x8]
     276:	f0 03       	lwi37.sp $r0,[+#0xc]
     278:	f0 81       	swi37.sp $r0,[+#0x4]
     27a:	b6 3f       	swi450 $r1,[$sp]
     27c:	44 00 00 f8 	movi $r0,#0xf8
     280:	49 00 01 e8 	jal 650 <tiny_printf>
     284:	46 0c cb 0b 	sethi $r0,#0xccb0b
     288:	04 00 00 30 	lwi $r0,[$r0+#0xc0]
     28c:	96 16       	bmski33 $r0,#0x2
     28e:	c0 1b       	beqz38 $r0,2c4 <ota_c_code+0x6c>
     290:	46 0c 00 00 	sethi $r0,#0xc0000
     294:	04 20 01 58 	lwi $r2,[$r0+#0x560]
     298:	54 11 30 00 	andi $r1,$r2,#0x3000
     29c:	c1 36       	beqz38 $r1,308 <ota_c_code+0xb0>
     29e:	04 50 03 07 	lwi $r5,[$r0+#0xc1c]
     2a2:	44 10 41 1a 	movi $r1,#0x411a
     2a6:	d1 13       	beqs38 $r1,2cc <ota_c_code+0x74>
     2a8:	44 10 05 6c 	movi $r1,#0x56c
     2ac:	4c 50 80 66 	beq $r5,$r1,378 <ota_c_code+0x120>
     2b0:	5a 58 ad 04 	bnec $r5,#0xad,2b8 <ota_c_code+0x60>
     2b4:	48 00 00 5e 	j 370 <ota_c_code+0x118>
     2b8:	46 60 01 6e 	sethi $r6,#0x16e
     2bc:	50 63 03 60 	addi $r6,$r6,#0x360
     2c0:	84 00       	movi55 $r0,#0x0
     2c2:	d5 09       	j8 2d4 <ota_c_code+0x7c>
     2c4:	ec 10       	addi10.sp #0x10
     2c6:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
     2ca:	dd 9e       	ret5 $lp
     2cc:	44 60 25 80 	movi $r6,#0x2580
     2d0:	84 00       	movi55 $r0,#0x0
     2d2:	92 00       	nop16
     2d4:	49 00 08 0c 	jal 12ec <drv_comport_init>
     2d8:	84 23       	movi55 $r1,#0x3
     2da:	84 40       	movi55 $r2,#0x0
     2dc:	84 60       	movi55 $r3,#0x0
     2de:	80 06       	mov55 $r0,$r6
     2e0:	49 00 08 32 	jal 1344 <drv_comport_set_format>
     2e4:	49 00 05 ce 	jal e80 <Cli_Init>
     2e8:	44 00 01 18 	movi $r0,#0x118
     2ec:	49 00 10 a6 	jal 2438 <printf>
     2f0:	44 00 01 1c 	movi $r0,#0x11c
     2f4:	49 00 10 a2 	jal 2438 <printf>
     2f8:	44 00 01 34 	movi $r0,#0x134
     2fc:	49 00 10 9e 	jal 2438 <printf>
     300:	49 00 06 04 	jal f08 <Cli_Start>
     304:	d5 fe       	j8 300 <ota_c_code+0xa8>
     306:	92 00       	nop16
     308:	44 10 c0 00 	movi $r1,#0xc000
     30c:	fe 56       	and33 $r1,$r2
     30e:	c1 21       	beqz38 $r1,350 <ota_c_code+0xf8>
     310:	04 50 03 4a 	lwi $r5,[$r0+#0xd28]
     314:	46 00 05 50 	sethi $r0,#0x550
     318:	50 00 08 23 	addi $r0,$r0,#0x823
     31c:	d0 26       	beqs38 $r0,368 <ota_c_code+0x110>
     31e:	92 00       	nop16
     320:	46 00 09 c0 	sethi $r0,#0x9c0
     324:	50 00 00 ad 	addi $r0,$r0,#0xad
     328:	d0 10       	beqs38 $r0,348 <ota_c_code+0xf0>
     32a:	46 00 0b 30 	sethi $r0,#0xb30
     32e:	8c 15       	addi45 $r0,#0x15
     330:	d0 08       	beqs38 $r0,340 <ota_c_code+0xe8>
     332:	46 60 01 6e 	sethi $r6,#0x16e
     336:	50 63 03 60 	addi $r6,$r6,#0x360
     33a:	84 01       	movi55 $r0,#0x1
     33c:	48 ff ff cc 	j 2d4 <ota_c_code+0x7c>
     340:	46 60 00 e1 	sethi $r6,#0xe1
     344:	84 01       	movi55 $r0,#0x1
     346:	d5 c7       	j8 2d4 <ota_c_code+0x7c>
     348:	44 61 c2 00 	movi $r6,#0x1c200
     34c:	84 01       	movi55 $r0,#0x1
     34e:	d5 c3       	j8 2d4 <ota_c_code+0x7c>
     350:	44 17 00 00 	movi $r1,#0x70000
     354:	fe 56       	and33 $r1,$r2
     356:	c1 11       	beqz38 $r1,378 <ota_c_code+0x120>
     358:	04 50 03 8a 	lwi $r5,[$r0+#0xe28]
     35c:	46 00 05 50 	sethi $r0,#0x550
     360:	50 00 08 23 	addi $r0,$r0,#0x823
     364:	d8 de       	bnes38 $r0,320 <ota_c_code+0xc8>
     366:	92 00       	nop16
     368:	44 60 25 80 	movi $r6,#0x2580
     36c:	84 01       	movi55 $r0,#0x1
     36e:	d5 b3       	j8 2d4 <ota_c_code+0x7c>
     370:	46 60 00 e1 	sethi $r6,#0xe1
     374:	84 00       	movi55 $r0,#0x0
     376:	d5 af       	j8 2d4 <ota_c_code+0x7c>
     378:	44 61 c2 00 	movi $r6,#0x1c200
     37c:	84 00       	movi55 $r0,#0x0
     37e:	d5 ab       	j8 2d4 <ota_c_code+0x7c>

00000380 <fota_fs_upgrade>:
     380:	3b ff fc bc 	smw.adm $sp,[$sp],$sp,#0x2    ! {$lp}
     384:	ef dc       	addi10.sp #-36
     386:	84 01       	movi55 $r0,#0x1
     388:	f0 83       	swi37.sp $r0,[+#0xc]
     38a:	46 03 00 10 	sethi $r0,#0x30010
     38e:	04 00 00 00 	lwi $r0,[$r0+#0x0]
     392:	f0 84       	swi37.sp $r0,[+#0x10]
     394:	3e 0f c0 00 	addi.gp $r0,#-16384
     398:	f0 85       	swi37.sp $r0,[+#0x14]
     39a:	46 00 02 00 	sethi $r0,#0x200
     39e:	58 00 00 00 	ori $r0,$r0,#0x0
     3a2:	f0 86       	swi37.sp $r0,[+#0x18]
     3a4:	46 03 00 25 	sethi $r0,#0x30025
     3a8:	58 00 00 00 	ori $r0,$r0,#0x0
     3ac:	f2 06       	lwi37.sp $r2,[+#0x18]
     3ae:	f1 05       	lwi37.sp $r1,[+#0x14]
     3b0:	f0 87       	swi37.sp $r0,[+#0x1c]
     3b2:	f0 03       	lwi37.sp $r0,[+#0xc]
     3b4:	5a 00 01 06 	beqc $r0,#0x1,3c0 <fota_fs_upgrade+0x40>
     3b8:	ec 24       	addi10.sp #0x24
     3ba:	3b ff fc 84 	lmw.bim $sp,[$sp],$sp,#0x2    ! {$lp}
     3be:	dd 9e       	ret5 $lp
     3c0:	f0 04       	lwi37.sp $r0,[+#0x10]
     3c2:	5a 08 01 fb 	bnec $r0,#0x1,3b8 <fota_fs_upgrade+0x38>
     3c6:	f0 05       	lwi37.sp $r0,[+#0x14]
     3c8:	9a 51       	sub333 $r1,$r2,$r1
     3ca:	49 00 03 9b 	jal b00 <OTA_LITTLEFS_init>
     3ce:	c0 11       	beqz38 $r0,3f0 <fota_fs_upgrade+0x70>
     3d0:	49 00 03 ee 	jal bac <OTA_LITTLEFS_find_and_check>
     3d4:	c0 22       	beqz38 $r0,418 <fota_fs_upgrade+0x98>
     3d6:	49 00 04 8d 	jal cf0 <OTA_LIEELEFS_find_and_update>
     3da:	c0 29       	beqz38 $r0,42c <fota_fs_upgrade+0xac>
     3dc:	44 00 01 44 	movi $r0,#0x144
     3e0:	b6 1f       	swi450 $r0,[$sp]
     3e2:	84 1f       	movi55 $r0,#-1
     3e4:	f0 81       	swi37.sp $r0,[+#0x4]
     3e6:	44 00 01 3c 	movi $r0,#0x13c
     3ea:	49 00 01 33 	jal 650 <tiny_printf>
     3ee:	d5 0b       	j8 404 <fota_fs_upgrade+0x84>
     3f0:	44 00 01 44 	movi $r0,#0x144
     3f4:	b6 1f       	swi450 $r0,[$sp]
     3f6:	84 1c       	movi55 $r0,#-4
     3f8:	14 0f 80 01 	swi $r0,[$sp+#0x4]
     3fc:	44 00 01 3c 	movi $r0,#0x13c
     400:	49 00 01 28 	jal 650 <tiny_printf>
     404:	46 03 00 10 	sethi $r0,#0x30010
     408:	58 00 00 00 	ori $r0,$r0,#0x0
     40c:	40 00 20 08 	slli $r0,$r0,#0x8
     410:	92 08       	srli45 $r0,#0x8
     412:	49 00 00 79 	jal 504 <ota_flash_sector_erase>
     416:	d5 d1       	j8 3b8 <fota_fs_upgrade+0x38>
     418:	44 00 01 44 	movi $r0,#0x144
     41c:	b6 1f       	swi450 $r0,[$sp]
     41e:	84 1d       	movi55 $r0,#-3
     420:	f0 81       	swi37.sp $r0,[+#0x4]
     422:	44 00 01 3c 	movi $r0,#0x13c
     426:	49 00 01 15 	jal 650 <tiny_printf>
     42a:	d5 ed       	j8 404 <fota_fs_upgrade+0x84>
     42c:	44 00 01 44 	movi $r0,#0x144
     430:	b6 1f       	swi450 $r0,[$sp]
     432:	84 1e       	movi55 $r0,#-2
     434:	f0 81       	swi37.sp $r0,[+#0x4]
     436:	44 00 01 3c 	movi $r0,#0x13c
     43a:	49 00 01 0b 	jal 650 <tiny_printf>
     43e:	d5 e3       	j8 404 <fota_fs_upgrade+0x84>

00000440 <flash_wait_spi_status_register>:
     440:	ef f8       	addi10.sp #-8
     442:	46 2c 00 01 	sethi $r2,#0xc0001
     446:	3e 38 00 9c 	addi.gp $r3,#0x9c
     44a:	86 45       	movi55 $r18,#0x5
     44c:	51 11 00 14 	addi $r17,$r2,#0x14
     450:	86 03       	movi55 $r16,#0x3
     452:	84 a1       	movi55 $r5,#0x1
     454:	44 40 00 64 	movi $r4,#0x64
     458:	3c 3e 00 24 	swi.gp $r3,[+#0x90]
     45c:	a8 d1       	swi333 $r3,[$r2+#0x4]
     45e:	3c 0c 00 26 	lwi.gp $r0,[+#0x98]
     462:	b7 c0       	swi450 $r18,[$r0]
     464:	b7 91       	swi450 $r16,[$r17]
     466:	a9 54       	swi333 $r5,[$r2+#0x10]
     468:	f4 81       	swi37.sp $r4,[+#0x4]
     46a:	f0 01       	lwi37.sp $r0,[+#0x4]
     46c:	9e 41       	subi333 $r1,$r0,#0x1
     46e:	f1 81       	swi37.sp $r1,[+#0x4]
     470:	c8 fd       	bnez38 $r0,46a <flash_wait_spi_status_register+0x2a>
     472:	a0 13       	lwi333 $r0,[$r2+#0xc]
     474:	54 00 00 09 	andi $r0,$r0,#0x9
     478:	c8 fd       	bnez38 $r0,472 <flash_wait_spi_status_register+0x32>
     47a:	3c 0c 00 24 	lwi.gp $r0,[+#0x90]
     47e:	b4 00       	lwi450 $r0,[$r0]
     480:	96 04       	xlsb33 $r0,$r0
     482:	c8 eb       	bnez38 $r0,458 <flash_wait_spi_status_register+0x18>
     484:	ec 08       	addi10.sp #0x8
     486:	dd 9e       	ret5 $lp

00000488 <flash_write_enable>:
     488:	3b ff fc bc 	smw.adm $sp,[$sp],$sp,#0x2    ! {$lp}
     48c:	ef f4       	addi10.sp #-12
     48e:	3c 1c 00 26 	lwi.gp $r1,[+#0x98]
     492:	84 46       	movi55 $r2,#0x6
     494:	b6 41       	swi450 $r2,[$r1]
     496:	46 0c 00 01 	sethi $r0,#0xc0001
     49a:	84 20       	movi55 $r1,#0x0
     49c:	a8 45       	swi333 $r1,[$r0+#0x14]
     49e:	84 21       	movi55 $r1,#0x1
     4a0:	a8 44       	swi333 $r1,[$r0+#0x10]
     4a2:	44 00 00 64 	movi $r0,#0x64
     4a6:	f0 81       	swi37.sp $r0,[+#0x4]
     4a8:	f0 01       	lwi37.sp $r0,[+#0x4]
     4aa:	9e 41       	subi333 $r1,$r0,#0x1
     4ac:	f1 81       	swi37.sp $r1,[+#0x4]
     4ae:	c8 fd       	bnez38 $r0,4a8 <flash_write_enable+0x20>
     4b0:	46 1c 00 01 	sethi $r1,#0xc0001
     4b4:	a0 0b       	lwi333 $r0,[$r1+#0xc]
     4b6:	54 00 00 09 	andi $r0,$r0,#0x9
     4ba:	c8 fd       	bnez38 $r0,4b4 <flash_write_enable+0x2c>
     4bc:	49 ff ff c2 	jal 440 <flash_wait_spi_status_register>
     4c0:	ec 0c       	addi10.sp #0xc
     4c2:	3b ff fc 84 	lmw.bim $sp,[$sp],$sp,#0x2    ! {$lp}
     4c6:	dd 9e       	ret5 $lp

000004c8 <ota_flashctl_bitmode>:
     4c8:	ef f8       	addi10.sp #-8
     4ca:	44 10 00 64 	movi $r1,#0x64
     4ce:	f1 81       	swi37.sp $r1,[+#0x4]
     4d0:	f1 01       	lwi37.sp $r1,[+#0x4]
     4d2:	9e 89       	subi333 $r2,$r1,#0x1
     4d4:	f2 81       	swi37.sp $r2,[+#0x4]
     4d6:	c9 fd       	bnez38 $r1,4d0 <ota_flashctl_bitmode+0x8>
     4d8:	46 2c 00 01 	sethi $r2,#0xc0001
     4dc:	a0 53       	lwi333 $r1,[$r2+#0xc]
     4de:	50 31 00 0c 	addi $r3,$r2,#0xc
     4e2:	54 10 80 09 	andi $r1,$r1,#0x9
     4e6:	c9 fb       	bnez38 $r1,4dc <ota_flashctl_bitmode+0x14>
     4e8:	5a 00 02 08 	beqc $r0,#0x2,4f8 <ota_flashctl_bitmode+0x30>
     4ec:	b4 03       	lwi450 $r0,[$r3]
     4ee:	66 00 00 06 	bitci $r0,$r0,#0x6
     4f2:	b6 03       	swi450 $r0,[$r3]
     4f4:	ec 08       	addi10.sp #0x8
     4f6:	dd 9e       	ret5 $lp
     4f8:	b4 03       	lwi450 $r0,[$r3]
     4fa:	58 00 00 04 	ori $r0,$r0,#0x4
     4fe:	b6 03       	swi450 $r0,[$r3]
     500:	ec 08       	addi10.sp #0x8
     502:	dd 9e       	ret5 $lp

00000504 <ota_flash_sector_erase>:
     504:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
     508:	ef f8       	addi10.sp #-8
     50a:	80 c0       	mov55 $r6,$r0
     50c:	49 ff ff be 	jal 488 <flash_write_enable>
     510:	40 33 60 09 	srli $r3,$r6,#0x18
     514:	40 13 60 08 	slli $r1,$r6,#0x18
     518:	fe 5f       	or33 $r1,$r3
     51a:	46 20 0f f0 	sethi $r2,#0xff0
     51e:	58 30 80 20 	ori $r3,$r1,#0x20
     522:	fe b6       	and33 $r2,$r6
     524:	44 10 ff 00 	movi $r1,#0xff00
     528:	92 48       	srli45 $r2,#0x8
     52a:	40 03 04 02 	and $r0,$r6,$r1
     52e:	40 00 20 08 	slli $r0,$r0,#0x8
     532:	40 11 88 04 	or $r1,$r3,$r2
     536:	fe 0f       	or33 $r0,$r1
     538:	3c 1c 00 26 	lwi.gp $r1,[+#0x98]
     53c:	46 2c 00 01 	sethi $r2,#0xc0001
     540:	b6 01       	swi450 $r0,[$r1]
     542:	84 00       	movi55 $r0,#0x0
     544:	a8 15       	swi333 $r0,[$r2+#0x14]
     546:	84 04       	movi55 $r0,#0x4
     548:	a8 14       	swi333 $r0,[$r2+#0x10]
     54a:	44 00 00 64 	movi $r0,#0x64
     54e:	f0 81       	swi37.sp $r0,[+#0x4]
     550:	f0 01       	lwi37.sp $r0,[+#0x4]
     552:	9e 41       	subi333 $r1,$r0,#0x1
     554:	f1 81       	swi37.sp $r1,[+#0x4]
     556:	c8 fd       	bnez38 $r0,550 <ota_flash_sector_erase+0x4c>
     558:	46 1c 00 01 	sethi $r1,#0xc0001
     55c:	a0 0b       	lwi333 $r0,[$r1+#0xc]
     55e:	54 00 00 09 	andi $r0,$r0,#0x9
     562:	c8 fd       	bnez38 $r0,55c <ota_flash_sector_erase+0x58>
     564:	49 ff ff 6e 	jal 440 <flash_wait_spi_status_register>
     568:	ec 08       	addi10.sp #0x8
     56a:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
     56e:	dd 9e       	ret5 $lp

00000570 <ota_flash_page_program>:
     570:	3a 6f 9c bc 	smw.adm $r6,[$sp],$r7,#0x2    ! {$r6~$r7, $lp}
     574:	ef f4       	addi10.sp #-12
     576:	80 e0       	mov55 $r7,$r0
     578:	3c 3c 00 25 	lwi.gp $r3,[+#0x94]
     57c:	80 c1       	mov55 $r6,$r1
     57e:	99 4b       	add333 $r5,$r1,$r3
     580:	c1 08       	beqz38 $r1,590 <ota_flash_page_program+0x20>
     582:	92 00       	nop16
     584:	08 41 00 01 	lbi.bi $r4,[$r2],#0x1
     588:	18 41 80 01 	sbi.bi $r4,[$r3],#0x1
     58c:	4c 32 ff fc 	bne $r3,$r5,584 <ota_flash_page_program+0x14>
     590:	49 ff ff 7c 	jal 488 <flash_write_enable>
     594:	40 43 e0 09 	srli $r4,$r7,#0x18
     598:	40 23 e0 08 	slli $r2,$r7,#0x18
     59c:	fe a7       	or33 $r2,$r4
     59e:	46 30 0f f0 	sethi $r3,#0xff0
     5a2:	58 41 00 02 	ori $r4,$r2,#0x2
     5a6:	fe fe       	and33 $r3,$r7
     5a8:	44 20 ff 00 	movi $r2,#0xff00
     5ac:	40 03 88 02 	and $r0,$r7,$r2
     5b0:	92 68       	srli45 $r3,#0x8
     5b2:	40 22 0c 04 	or $r2,$r4,$r3
     5b6:	40 00 20 08 	slli $r0,$r0,#0x8
     5ba:	fe 17       	or33 $r0,$r2
     5bc:	3c 2c 00 26 	lwi.gp $r2,[+#0x98]
     5c0:	46 1c 00 01 	sethi $r1,#0xc0001
     5c4:	b6 02       	swi450 $r0,[$r2]
     5c6:	84 00       	movi55 $r0,#0x0
     5c8:	a8 0d       	swi333 $r0,[$r1+#0x14]
     5ca:	8c c4       	addi45 $r6,#0x4
     5cc:	44 00 00 64 	movi $r0,#0x64
     5d0:	a9 8c       	swi333 $r6,[$r1+#0x10]
     5d2:	f0 81       	swi37.sp $r0,[+#0x4]
     5d4:	f0 01       	lwi37.sp $r0,[+#0x4]
     5d6:	9e 41       	subi333 $r1,$r0,#0x1
     5d8:	f1 81       	swi37.sp $r1,[+#0x4]
     5da:	c8 fd       	bnez38 $r0,5d4 <ota_flash_page_program+0x64>
     5dc:	46 1c 00 01 	sethi $r1,#0xc0001
     5e0:	a0 0b       	lwi333 $r0,[$r1+#0xc]
     5e2:	54 00 00 09 	andi $r0,$r0,#0x9
     5e6:	c8 fd       	bnez38 $r0,5e0 <ota_flash_page_program+0x70>
     5e8:	49 ff ff 2c 	jal 440 <flash_wait_spi_status_register>
     5ec:	ec 0c       	addi10.sp #0xc
     5ee:	3a 6f 9c 84 	lmw.bim $r6,[$sp],$r7,#0x2    ! {$r6~$r7, $lp}
     5f2:	dd 9e       	ret5 $lp

000005f4 <ota_flash_init>:
     5f4:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
     5f8:	44 00 00 00 	movi $r0,#0x0
     5fc:	49 ff ff 66 	jal 4c8 <ota_flashctl_bitmode>
     600:	3e 38 00 a4 	addi.gp $r3,#0xa4
     604:	3c 3e 00 26 	swi.gp $r3,[+#0x98]
     608:	46 1c 00 01 	sethi $r1,#0xc0001
     60c:	3e 08 00 a8 	addi.gp $r0,#0xa8
     610:	3c 0e 00 25 	swi.gp $r0,[+#0x94]
     614:	3e 28 00 9c 	addi.gp $r2,#0x9c
     618:	b6 61       	swi450 $r3,[$r1]
     61a:	84 01       	movi55 $r0,#0x1
     61c:	3c 2e 00 24 	swi.gp $r2,[+#0x90]
     620:	a8 89       	swi333 $r2,[$r1+#0x4]
     622:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
     626:	dd 9e       	ret5 $lp

00000628 <tiny_vprintf_help>:
     628:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
     62c:	80 c0       	mov55 $r6,$r0
     62e:	5a 00 0a 09 	beqc $r0,#0xa,640 <tiny_vprintf_help+0x18>
     632:	80 06       	mov55 $r0,$r6
     634:	49 00 10 b6 	jal 27a0 <serial_tx>
     638:	84 00       	movi55 $r0,#0x0
     63a:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
     63e:	dd 9e       	ret5 $lp
     640:	84 0d       	movi55 $r0,#0xd
     642:	49 00 10 af 	jal 27a0 <serial_tx>
     646:	d5 f6       	j8 632 <tiny_vprintf_help+0xa>

00000648 <tiny_printf_display>:
     648:	3e 00 00 00 	sbi.gp $r0,[+#0x0]
     64c:	dd 9e       	ret5 $lp
     64e:	92 00       	nop16

00000650 <tiny_printf>:
     650:	2e 18 00 00 	lbsi.gp $r1,[+#0x0]
     654:	c9 04       	bnez38 $r1,65c <tiny_printf+0xc>
     656:	84 00       	movi55 $r0,#0x0
     658:	dd 9e       	ret5 $lp
     65a:	92 00       	nop16
     65c:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
     660:	44 20 06 28 	movi $r2,#0x628
     664:	b0 42       	addri36.sp $r1,#0x8
     666:	84 60       	movi55 $r3,#0x0
     668:	49 00 00 06 	jal 674 <tiny_do_printf>
     66c:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
     670:	dd 9e       	ret5 $lp
     672:	92 00       	nop16

00000674 <tiny_do_printf>:
     674:	3a 6f ba bc 	smw.adm $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
     678:	ef dc       	addi10.sp #-36
     67a:	36 3f 80 06 	fsdi $fd3,[$sp+#0x18]
     67e:	80 c0       	mov55 $r6,$r0
     680:	20 00 00 00 	lbsi $r0,[$r0+#0x0]
     684:	f3 81       	swi37.sp $r3,[+#0x4]
     686:	4e 02 01 aa 	beqz $r0,9da <tiny_do_printf+0x366>
     68a:	81 a1       	mov55 $r13,$r1
     68c:	84 20       	movi55 $r1,#0x0
     68e:	6a 13 80 09 	fmtsr $r1,$fs7
     692:	44 10 00 30 	movi $r1,#0x30
     696:	6a 13 00 09 	fmtsr $r1,$fs6
     69a:	80 e2       	mov55 $r7,$r2
     69c:	87 80       	movi55 $fp,#0x0
     69e:	85 00       	movi55 $r8,#0x0
     6a0:	85 40       	movi55 $r10,#0x0
     6a2:	85 60       	movi55 $r11,#0x0
     6a4:	44 f0 06 b0 	movi $r15,#0x6b0
     6a8:	38 17 ae 02 	lw $r1,[$r15+($r11<<#0x2)]
     6ac:	4a 00 04 00 	jr $r1
     6b0:	18 07 00 00 	sbi.bi $r0,[$r14],#0x0
     6b4:	c8 06       	bnez38 $r0,6c0 <tiny_do_printf+0x4c>
     6b6:	00 00 08 08 	lbi $r0,[$r0+#0x808]
     6ba:	00 00 28 07 	lbi $r0,[$r0+#0x2807]
     6be:	00 00 e8 07 	lbi $r0,[$r1+#-6137]
     6c2:	00 00 8c c1 	lbi $r0,[$r1+#0xcc1]
     6c6:	92 00       	nop16
     6c8:	20 23 00 00 	lbsi $r2,[$r6+#0x0]
     6cc:	5a 28 25 04 	bnec $r2,#0x25,6d4 <tiny_do_printf+0x60>
     6d0:	48 00 01 6d 	j 9aa <tiny_do_printf+0x336>
     6d4:	5a 28 2d 04 	bnec $r2,#0x2d,6dc <tiny_do_printf+0x68>
     6d8:	48 00 01 2e 	j 934 <tiny_do_printf+0x2c0>
     6dc:	50 e3 00 00 	addi $r14,$r6,#0x0
     6e0:	5a 28 30 04 	bnec $r2,#0x30,6e8 <tiny_do_printf+0x74>
     6e4:	48 00 01 56 	j 990 <tiny_do_printf+0x31c>
     6e8:	50 01 7f d0 	addi $r0,$r2,#-48
     6ec:	96 00       	zeb33 $r0,$r0
     6ee:	e6 0a       	slti45 $r0,#0xa
     6f0:	e8 20       	beqzs8 730 <tiny_do_printf+0xbc>
     6f2:	84 0a       	movi55 $r0,#0xa
     6f4:	42 2e 00 73 	maddr32 $r2,$fp,$r0
     6f8:	85 62       	movi55 $r11,#0x2
     6fa:	51 c1 7f d0 	addi $fp,$r2,#-48
     6fe:	92 00       	nop16
     700:	20 07 00 01 	lbsi $r0,[$r14+#0x1]
     704:	50 67 00 01 	addi $r6,$r14,#0x1
     708:	c8 ce       	bnez38 $r0,6a4 <tiny_do_printf+0x30>
     70a:	80 08       	mov55 $r0,$r8
     70c:	ec 18       	addi10.sp #0x18
     70e:	34 3f 90 03 	fldi.bi $fd3,[$sp],#0xc
     712:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
     716:	dd 9e       	ret5 $lp
     718:	5a 00 25 d6 	beqc $r0,#0x25,6c4 <tiny_do_printf+0x50>
     71c:	b0 41       	addri36.sp $r1,#0x4
     71e:	dd 27       	jral5 $r7
     720:	8d 01       	addi45 $r8,#0x1
     722:	81 c6       	mov55 $r14,$r6
     724:	d5 ee       	j8 700 <tiny_do_printf+0x8c>
     726:	92 00       	nop16
     728:	20 23 00 00 	lbsi $r2,[$r6+#0x0]
     72c:	81 c6       	mov55 $r14,$r6
     72e:	92 00       	nop16
     730:	5a 28 4e 04 	bnec $r2,#0x4e,738 <tiny_do_printf+0xc4>
     734:	48 00 00 f7 	j 922 <tiny_do_printf+0x2ae>
     738:	5a 28 6c 04 	bnec $r2,#0x6c,740 <tiny_do_printf+0xcc>
     73c:	48 00 00 f6 	j 928 <tiny_do_printf+0x2b4>
     740:	5a 28 68 04 	bnec $r2,#0x68,748 <tiny_do_printf+0xd4>
     744:	48 00 01 20 	j 984 <tiny_do_printf+0x310>
     748:	50 21 7f a8 	addi $r2,$r2,#-88
     74c:	84 20       	movi55 $r1,#0x0
     74e:	5c f1 00 21 	slti $r15,$r2,#0x21
     752:	10 1f 80 17 	sbi $r1,[$sp+#0x17]
     756:	e8 54       	beqzs8 7fe <tiny_do_printf+0x18a>
     758:	44 f0 07 64 	movi $r15,#0x764
     75c:	38 07 8a 02 	lw $r0,[$r15+($r2<<#0x2)]
     760:	4a 00 00 00 	jr $r0
     764:	18 09 00 00 	sbi.bi $r0,[$r18],#0x0
     768:	fe 07       	or33 $r0,$r0
     76a:	00 00 fe 07 	lbi $r0,[$r1+#-505]
     76e:	00 00 fe 07 	lbi $r0,[$r1+#-505]
     772:	00 00 fe 07 	lbi $r0,[$r1+#-505]
     776:	00 00 fe 07 	lbi $r0,[$r1+#-505]
     77a:	00 00 fe 07 	lbi $r0,[$r1+#-505]
     77e:	00 00 fe 07 	lbi $r0,[$r1+#-505]
     782:	00 00 fe 07 	lbi $r0,[$r1+#-505]
     786:	00 00 fe 07 	lbi $r0,[$r1+#-505]
     78a:	00 00 fe 07 	lbi $r0,[$r1+#-505]
     78e:	00 00 68 09 	lbi $r0,[$r0+#-6135]
     792:	00 00 14 08 	lbi $r0,[$r0+#0x1408]
     796:	00 00 fe 07 	lbi $r0,[$r1+#-505]
     79a:	00 00 fe 07 	lbi $r0,[$r1+#-505]
     79e:	00 00 fe 07 	lbi $r0,[$r1+#-505]
     7a2:	00 00 fe 07 	lbi $r0,[$r1+#-505]
     7a6:	00 00 14 08 	lbi $r0,[$r0+#0x1408]
     7aa:	00 00 fe 07 	lbi $r0,[$r1+#-505]
     7ae:	00 00 fe 07 	lbi $r0,[$r1+#-505]
     7b2:	00 00 fe 07 	lbi $r0,[$r1+#-505]
     7b6:	00 00 fe 07 	lbi $r0,[$r1+#-505]
     7ba:	00 00 1c 09 	lbi $r0,[$r0+#0x1c09]
     7be:	00 00 54 09 	lbi $r0,[$r0+#-11255]
     7c2:	00 00 1c 09 	lbi $r0,[$r0+#0x1c09]
     7c6:	00 00 fe 07 	lbi $r0,[$r1+#-505]
     7ca:	00 00 fe 07 	lbi $r0,[$r1+#-505]
     7ce:	00 00 5a 09 	lbi $r0,[$r0+#-9719]
     7d2:	00 00 fe 07 	lbi $r0,[$r1+#-505]
     7d6:	00 00 18 08 	lbi $r0,[$r0+#0x1808]
     7da:	00 00 fe 07 	lbi $r0,[$r1+#-505]
     7de:	00 00 fe 07 	lbi $r0,[$r1+#-505]
     7e2:	00 00 1c 09 	lbi $r0,[$r0+#0x1c09]
     7e6:	00 00 20 23 	lbi $r0,[$r0+#0x2023]
     7ea:	00 00 84 20 	lbi $r0,[$r1+#0x420]
     7ee:	50 21 7f a8 	addi $r2,$r2,#-88
     7f2:	5c f1 00 21 	slti $r15,$r2,#0x21
     7f6:	81 c6       	mov55 $r14,$r6
     7f8:	10 1f 80 17 	sbi $r1,[$sp+#0x17]
     7fc:	e9 ae       	bnezs8 758 <tiny_do_printf+0xe4>
     7fe:	87 80       	movi55 $fp,#0x0
     800:	85 40       	movi55 $r10,#0x0
     802:	85 60       	movi55 $r11,#0x0
     804:	48 ff ff 7e 	j 700 <tiny_do_printf+0x8c>
     808:	20 23 00 00 	lbsi $r2,[$r6+#0x0]
     80c:	81 c6       	mov55 $r14,$r6
     80e:	48 ff ff 6d 	j 6e8 <tiny_do_printf+0x74>
     812:	92 00       	nop16
     814:	58 a5 00 04 	ori $r10,$r10,#0x4
     818:	44 00 00 0a 	movi $r0,#0xa
     81c:	54 15 00 08 	andi $r1,$r10,#0x8
     820:	c1 70       	beqz38 $r1,900 <tiny_do_printf+0x28c>
     822:	50 26 80 04 	addi $r2,$r13,#0x4
     826:	54 15 00 04 	andi $r1,$r10,#0x4
     82a:	b4 6d       	lwi450 $r3,[$r13]
     82c:	81 a2       	mov55 $r13,$r2
     82e:	c9 6f       	bnez38 $r1,90c <tiny_do_printf+0x298>
     830:	50 6f 80 17 	addi $r6,$sp,#0x17
     834:	54 25 00 02 	andi $r2,$r10,#0x2
     838:	d5 0c       	j8 850 <tiny_do_printf+0x1dc>
     83a:	92 00       	nop16
     83c:	50 12 00 37 	addi $r1,$r4,#0x37
     840:	50 42 00 57 	addi $r4,$r4,#0x57
     844:	ca 0e       	bnez38 $r2,860 <tiny_do_printf+0x1ec>
     846:	40 31 80 77 	divr $r3,$r3,$r3,$r0
     84a:	af 30       	sbi333 $r4,[$r6+#0x0]
     84c:	c3 0e       	beqz38 $r3,868 <tiny_do_printf+0x1f4>
     84e:	92 00       	nop16
     850:	40 11 80 97 	divr $r1,$r4,$r3,$r0
     854:	e6 8a       	slti45 $r4,#0xa
     856:	50 12 00 30 	addi $r1,$r4,#0x30
     85a:	8e c1       	subi45 $r6,#0x1
     85c:	e8 f0       	beqzs8 83c <tiny_do_printf+0x1c8>
     85e:	92 00       	nop16
     860:	40 31 80 77 	divr $r3,$r3,$r3,$r0
     864:	ae 70       	sbi333 $r1,[$r6+#0x0]
     866:	cb f5       	bnez38 $r3,850 <tiny_do_printf+0x1dc>
     868:	50 03 00 00 	addi $r0,$r6,#0x0
     86c:	49 00 0f 8e 	jal 2788 <my_strlen>
     870:	6a 13 80 01 	fmfsr $r1,$fs7
     874:	54 c5 00 20 	andi $r12,$r10,#0x20
     878:	40 10 b0 06 	slt $r1,$r1,$r12
     87c:	54 95 00 60 	andi $r9,$r10,#0x60
     880:	40 c0 04 00 	add $r12,$r0,$r1
     884:	5a 98 60 04 	bnec $r9,#0x60,88c <tiny_do_printf+0x218>
     888:	48 00 00 9b 	j 9be <tiny_do_printf+0x34a>
     88c:	54 05 00 01 	andi $r0,$r10,#0x1
     890:	c8 18       	bnez38 $r0,8c0 <tiny_do_printf+0x24c>
     892:	40 06 70 06 	slt $r0,$r12,$fp
     896:	c0 15       	beqz38 $r0,8c0 <tiny_do_printf+0x24c>
     898:	6a 13 00 01 	fmfsr $r1,$fs6
     89c:	54 a5 00 40 	andi $r10,$r10,#0x40
     8a0:	fa 10       	movpi45 $r0,#0x20
     8a2:	40 10 28 1a 	cmovz $r1,$r0,$r10
     8a6:	81 7c       	mov55 $r11,$fp
     8a8:	81 41       	mov55 $r10,$r1
     8aa:	80 0a       	mov55 $r0,$r10
     8ac:	b0 41       	addri36.sp $r1,#0x4
     8ae:	8f 61       	subi45 $r11,#0x1
     8b0:	4b e0 1c 01 	jral $lp,$r7
     8b4:	40 06 2c 06 	slt $r0,$r12,$r11
     8b8:	c8 f9       	bnez38 $r0,8aa <tiny_do_printf+0x236>
     8ba:	89 1c       	add45 $r8,$fp
     8bc:	8b 0c       	sub45 $r8,$r12
     8be:	83 8c       	mov55 $fp,$r12
     8c0:	5a 90 20 70 	beqc $r9,#0x20,9a0 <tiny_do_printf+0x32c>
     8c4:	a6 30       	lbi333 $r0,[$r6+#0x0]
     8c6:	c0 09       	beqz38 $r0,8d8 <tiny_do_printf+0x264>
     8c8:	8c c1       	addi45 $r6,#0x1
     8ca:	b0 41       	addri36.sp $r1,#0x4
     8cc:	4b e0 1c 01 	jral $lp,$r7
     8d0:	08 03 00 01 	lbi.bi $r0,[$r6],#0x1
     8d4:	8d 01       	addi45 $r8,#0x1
     8d6:	c8 fa       	bnez38 $r0,8ca <tiny_do_printf+0x256>
     8d8:	40 0e 30 06 	slt $r0,$fp,$r12
     8dc:	c8 91       	bnez38 $r0,7fe <tiny_do_printf+0x18a>
     8de:	40 ce 30 01 	sub $r12,$fp,$r12
     8e2:	4e c2 ff 8e 	beqz $r12,7fe <tiny_do_printf+0x18a>
     8e6:	80 cc       	mov55 $r6,$r12
     8e8:	8e c1       	subi45 $r6,#0x1
     8ea:	fa 10       	movpi45 $r0,#0x20
     8ec:	b0 41       	addri36.sp $r1,#0x4
     8ee:	dd 27       	jral5 $r7
     8f0:	ce fc       	bnez38 $r6,8e8 <tiny_do_printf+0x274>
     8f2:	89 0c       	add45 $r8,$r12
     8f4:	87 80       	movi55 $fp,#0x0
     8f6:	85 40       	movi55 $r10,#0x0
     8f8:	85 60       	movi55 $r11,#0x0
     8fa:	48 ff ff 03 	j 700 <tiny_do_printf+0x8c>
     8fe:	92 00       	nop16
     900:	54 15 00 04 	andi $r1,$r10,#0x4
     904:	b4 6d       	lwi450 $r3,[$r13]
     906:	50 d6 80 04 	addi $r13,$r13,#0x4
     90a:	c1 93       	beqz38 $r1,830 <tiny_do_printf+0x1bc>
     90c:	4e 34 ff 92 	bgez $r3,830 <tiny_do_printf+0x1bc>
     910:	58 a5 00 20 	ori $r10,$r10,#0x20
     914:	fe da       	neg33 $r3,$r3
     916:	d5 8d       	j8 830 <tiny_do_printf+0x1bc>
     918:	58 a5 00 02 	ori $r10,$r10,#0x2
     91c:	fa 00       	movpi45 $r0,#0x10
     91e:	48 ff ff 7f 	j 81c <tiny_do_printf+0x1a8>
     922:	85 63       	movi55 $r11,#0x3
     924:	48 ff fe ee 	j 700 <tiny_do_printf+0x8c>
     928:	58 a5 00 08 	ori $r10,$r10,#0x8
     92c:	85 63       	movi55 $r11,#0x3
     92e:	48 ff fe e9 	j 700 <tiny_do_printf+0x8c>
     932:	92 00       	nop16
     934:	54 05 00 01 	andi $r0,$r10,#0x1
     938:	c0 08       	beqz38 $r0,948 <tiny_do_printf+0x2d4>
     93a:	81 c6       	mov55 $r14,$r6
     93c:	87 80       	movi55 $fp,#0x0
     93e:	85 40       	movi55 $r10,#0x0
     940:	44 b0 00 00 	movi $r11,#0x0
     944:	48 ff fe de 	j 700 <tiny_do_printf+0x8c>
     948:	58 a5 00 01 	ori $r10,$r10,#0x1
     94c:	81 c6       	mov55 $r14,$r6
     94e:	85 61       	movi55 $r11,#0x1
     950:	48 ff fe d8 	j 700 <tiny_do_printf+0x8c>
     954:	84 08       	movi55 $r0,#0x8
     956:	48 ff ff 63 	j 81c <tiny_do_printf+0x1a8>
     95a:	b4 cd       	lwi450 $r6,[$r13]
     95c:	66 a5 00 40 	bitci $r10,$r10,#0x40
     960:	50 d6 80 04 	addi $r13,$r13,#0x4
     964:	48 ff ff 82 	j 868 <tiny_do_printf+0x1f4>
     968:	b4 0d       	lwi450 $r0,[$r13]
     96a:	54 95 00 20 	andi $r9,$r10,#0x20
     96e:	10 0f 80 16 	sbi $r0,[$sp+#0x16]
     972:	66 a5 00 40 	bitci $r10,$r10,#0x40
     976:	50 d6 80 04 	addi $r13,$r13,#0x4
     97a:	50 6f 80 16 	addi $r6,$sp,#0x16
     97e:	85 81       	movi55 $r12,#0x1
     980:	d5 86       	j8 88c <tiny_do_printf+0x218>
     982:	92 00       	nop16
     984:	58 a5 00 10 	ori $r10,$r10,#0x10
     988:	85 63       	movi55 $r11,#0x3
     98a:	48 ff fe bb 	j 700 <tiny_do_printf+0x8c>
     98e:	92 00       	nop16
     990:	58 a5 00 40 	ori $r10,$r10,#0x40
     994:	50 e3 00 01 	addi $r14,$r6,#0x1
     998:	20 23 00 01 	lbsi $r2,[$r6+#0x1]
     99c:	48 ff fe a6 	j 6e8 <tiny_do_printf+0x74>
     9a0:	fa 1d       	movpi45 $r0,#0x2d
     9a2:	b0 41       	addri36.sp $r1,#0x4
     9a4:	dd 27       	jral5 $r7
     9a6:	8d 01       	addi45 $r8,#0x1
     9a8:	d5 8e       	j8 8c4 <tiny_do_printf+0x250>
     9aa:	fa 15       	movpi45 $r0,#0x25
     9ac:	b0 41       	addri36.sp $r1,#0x4
     9ae:	dd 27       	jral5 $r7
     9b0:	8d 01       	addi45 $r8,#0x1
     9b2:	81 c6       	mov55 $r14,$r6
     9b4:	87 80       	movi55 $fp,#0x0
     9b6:	85 40       	movi55 $r10,#0x0
     9b8:	85 60       	movi55 $r11,#0x0
     9ba:	48 ff fe a3 	j 700 <tiny_do_printf+0x8c>
     9be:	fa 1d       	movpi45 $r0,#0x2d
     9c0:	b0 41       	addri36.sp $r1,#0x4
     9c2:	dd 27       	jral5 $r7
     9c4:	54 05 00 01 	andi $r0,$r10,#0x1
     9c8:	8d 01       	addi45 $r8,#0x1
     9ca:	4e 03 ff 7d 	bnez $r0,8c4 <tiny_do_printf+0x250>
     9ce:	40 06 70 06 	slt $r0,$r12,$fp
     9d2:	4e 03 ff 63 	bnez $r0,898 <tiny_do_printf+0x224>
     9d6:	48 ff ff 77 	j 8c4 <tiny_do_printf+0x250>
     9da:	84 00       	movi55 $r0,#0x0
     9dc:	48 ff fe 98 	j 70c <tiny_do_printf+0x98>

000009e0 <_block_read>:
     9e0:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
     9e4:	3d 0c 00 22 	lwi.gp $r16,[+#0x88]
     9e8:	a1 47       	lwi333 $r5,[$r0+#0x1c]
     9ea:	46 03 00 00 	sethi $r0,#0x30000
     9ee:	88 10       	add45 $r0,$r16
     9f0:	88 40       	add45 $r2,$r0
     9f2:	42 20 94 73 	maddr32 $r2,$r1,$r5
     9f6:	80 03       	mov55 $r0,$r3
     9f8:	80 22       	mov55 $r1,$r2
     9fa:	80 44       	mov55 $r2,$r4
     9fc:	49 00 4a a8 	jal 9f4c <memcpy>
     a00:	84 00       	movi55 $r0,#0x0
     a02:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
     a06:	dd 9e       	ret5 $lp
     a08:	3d 3d 3d 3d 	lwi.gp $r19,[+#-199436]
     a0c:	3d 53 50 49 	lhi.gp $r21,[+#-89966]
     a10:	46 46 53 20 	sethi $r4,#0x65320
     a14:	66 6f 72 6d 	bitci $r6,$lp,#0x726d
     a18:	61 74 20 66 	*unknown*
     a1c:	61 69 6c 65 	*unknown*
     a20:	64 3a 20 25 	trap #0x5101
     a24:	3d 3d 3d 3d 	lwi.gp $r19,[+#-199436]
     a28:	3d 6c 64 0a 	lwi.gp $r22,[+#0x19028]
     a2c:	00 00 00 00 	lbi $r0,[$r0+#0x0]
     a30:	3d 3d 3d 3d 	lwi.gp $r19,[+#-199436]
     a34:	3d 53 50 49 	lhi.gp $r21,[+#-89966]
     a38:	46 46 53 20 	sethi $r4,#0x65320
     a3c:	6d 6f 75 6e 	*unknown*
     a40:	74 20 66 61 	*unknown*
     a44:	69 6c 65 64 	*unknown*
     a48:	3a 20 25 3d 	smwa.adm $r2,[$r0],$r9,#0x4    ! {$r2~$r9, $gp}
     a4c:	3d 3d 3d 3d 	lwi.gp $r19,[+#-199436]
     a50:	6c 64 0a 00 	*unknown*
     a54:	6f 74 61 5f 	*unknown*
     a58:	69 6e 66 6f 	*unknown*
     a5c:	2e 62 69 6e 	lbi.gp $r6,[+#0x2696e]
     a60:	00 00 00 00 	lbi $r0,[$r0+#0x0]
     a64:	0a 6e 6f 20 	lhi.bi $r6,[$fp],#-8640
     a68:	6f 74 61 5f 	*unknown*
     a6c:	69 6e 66 6f 	*unknown*
     a70:	2e 62 69 6e 	lbi.gp $r6,[+#0x2696e]
     a74:	0a 00 00 00 	lhi.bi $r0,[$r0],#0x0
     a78:	0a 72 65 61 	lhi.bi $r7,[$r4],#-13630
     a7c:	64 20 65 72 	*unknown*
     a80:	72 3a 20 25 	*unknown*
     a84:	64 0a 00 00 	*unknown*
     a88:	0a 63 61 6c 	lhi.bi $r6,[$r6],#-15656
     a8c:	63 20 6d 64 	*unknown*
     a90:	35 2c 20 77 	cpldi cp1,$cpr18,[$r24+#0x1dc]
     a94:	61 69 74 69 	*unknown*
     a98:	6e 67 0a 00 	*unknown*
     a9c:	6f 74 61 2e 	*unknown*
     aa0:	62 69 6e 00 	*unknown*
     aa4:	0a 6e 6f 20 	lhi.bi $r6,[$fp],#-8640
     aa8:	6f 74 61 2e 	*unknown*
     aac:	62 69 6e 0a 	*unknown*
     ab0:	00 00 00 00 	lbi $r0,[$r0+#0x0]
     ab4:	66 6f 74 61 	bitci $r6,$lp,#0x7461
     ab8:	20 75 70 64 	lbsi $r7,[$r10+#-3996]
     abc:	61 74 65 3a 	amttsl2.s $d0,$r8,$r25,[$i2],[$i6],$m2,$m7
     ac0:	28 69 6d 67 	lbsi.bi $r6,[$r18],#-4761
     ac4:	20 73 69 7a 	lbsi $r7,[$r6+#-5766]
     ac8:	65 3a 20 25 	trap #0x5101
     acc:	64 29 0a 00 	*unknown*
     ad0:	61 64 64 72 	*unknown*
     ad4:	3a 25 78 20 	smw.bi $r2,[$r10],$lp,#0x0    ! {$r2~$lp}
     ad8:	73 69 7a 65 	*unknown*
     adc:	3a 20 25 78 	smw.ad $r2,[$r0],$r9,#0x5    ! {$r2~$r9, $gp, $sp}
     ae0:	0a 00 00 00 	lhi.bi $r0,[$r0],#0x0
     ae4:	0a 53 50 49 	lhi.bi $r5,[$r6],#-24430
     ae8:	46 46 53 5f 	sethi $r4,#0x6535f
     aec:	72 65 61 64 	*unknown*
     af0:	20 30 78 25 	lbsi $r3,[$r0+#-2011]
     af4:	6c 78 20 66 	*unknown*
     af8:	61 69 6c 0a 	*unknown*
     afc:	00 00 00 00 	lbi $r0,[$r0+#0x0]

00000b00 <OTA_LITTLEFS_init>:
     b00:	3b ff fc bc 	smw.adm $sp,[$sp],$sp,#0x2    ! {$lp}
     b04:	ef f4       	addi10.sp #-12
     b06:	45 00 09 e0 	movi $r16,#0x9e0
     b0a:	84 60       	movi55 $r3,#0x0
     b0c:	3d 0e 0a f9 	swi.gp $r16,[+#0x2be4]
     b10:	3c 3e 0a fa 	swi.gp $r3,[+#0x2be8]
     b14:	3c 3e 0a fb 	swi.gp $r3,[+#0x2bec]
     b18:	44 20 01 00 	movi $r2,#0x100
     b1c:	3c 3e 0a fc 	swi.gp $r3,[+#0x2bf0]
     b20:	3c 2e 0a fd 	swi.gp $r2,[+#0x2bf4]
     b24:	3c 2e 0a fe 	swi.gp $r2,[+#0x2bf8]
     b28:	44 30 10 00 	movi $r3,#0x1000
     b2c:	3c 3e 0a ff 	swi.gp $r3,[+#0x2bfc]
     b30:	3c 2e 0b 02 	swi.gp $r2,[+#0x2c08]
     b34:	fa 40       	movpi45 $r2,#0x10
     b36:	3c 2e 0b 03 	swi.gp $r2,[+#0x2c0c]
     b3a:	44 20 01 f4 	movi $r2,#0x1f4
     b3e:	40 50 b0 09 	srli $r5,$r1,#0xc
     b42:	3c 2e 0b 01 	swi.gp $r2,[+#0x2c04]
     b46:	80 80       	mov55 $r4,$r0
     b48:	3c 5e 0b 00 	swi.gp $r5,[+#0x2c00]
     b4c:	3e 08 2b 68 	addi.gp $r0,#0x2b68
     b50:	3e 18 2b e0 	addi.gp $r1,#0x2be0
     b54:	3c 4e 00 22 	swi.gp $r4,[+#0x88]
     b58:	49 00 27 42 	jal 59dc <lfs_mount>
     b5c:	c8 06       	bnez38 $r0,b68 <OTA_LITTLEFS_init+0x68>
     b5e:	84 01       	movi55 $r0,#0x1
     b60:	ec 0c       	addi10.sp #0xc
     b62:	3b ff fc 84 	lmw.bim $sp,[$sp],$sp,#0x2    ! {$lp}
     b66:	dd 9e       	ret5 $lp
     b68:	3e 08 2b 68 	addi.gp $r0,#0x2b68
     b6c:	3e 18 2b e0 	addi.gp $r1,#0x2be0
     b70:	49 00 37 60 	jal 7a30 <lfs_format>
     b74:	c8 12       	bnez38 $r0,b98 <OTA_LITTLEFS_init+0x98>
     b76:	3e 08 2b 68 	addi.gp $r0,#0x2b68
     b7a:	3e 18 2b e0 	addi.gp $r1,#0x2be0
     b7e:	49 00 27 2f 	jal 59dc <lfs_mount>
     b82:	c0 ee       	beqz38 $r0,b5e <OTA_LITTLEFS_init+0x5e>
     b84:	b6 1f       	swi450 $r0,[$sp]
     b86:	44 00 0a 30 	movi $r0,#0xa30
     b8a:	49 ff fd 63 	jal 650 <tiny_printf>
     b8e:	84 00       	movi55 $r0,#0x0
     b90:	ec 0c       	addi10.sp #0xc
     b92:	3b ff fc 84 	lmw.bim $sp,[$sp],$sp,#0x2    ! {$lp}
     b96:	dd 9e       	ret5 $lp
     b98:	b6 1f       	swi450 $r0,[$sp]
     b9a:	44 00 0a 08 	movi $r0,#0xa08
     b9e:	49 ff fd 59 	jal 650 <tiny_printf>
     ba2:	84 00       	movi55 $r0,#0x0
     ba4:	ec 0c       	addi10.sp #0xc
     ba6:	3b ff fc 84 	lmw.bim $sp,[$sp],$sp,#0x2    ! {$lp}
     baa:	dd 9e       	ret5 $lp

00000bac <OTA_LITTLEFS_find_and_check>:
     bac:	3a 6f a0 bc 	smw.adm $r6,[$sp],$r8,#0x2    ! {$r6~$r8, $lp}
     bb0:	51 ff fd e0 	addi $sp,$sp,#-544
     bb4:	3e 08 2b 68 	addi.gp $r0,#0x2b68
     bb8:	b0 4b       	addri36.sp $r1,#0x2c
     bba:	44 20 0a 54 	movi $r2,#0xa54
     bbe:	84 61       	movi55 $r3,#0x1
     bc0:	49 00 37 34 	jal 7a28 <lfs_file_open>
     bc4:	4e 05 00 6e 	bltz $r0,ca0 <OTA_LITTLEFS_find_and_check+0xf4>
     bc8:	3e 08 2b 68 	addi.gp $r0,#0x2b68
     bcc:	b0 4b       	addri36.sp $r1,#0x2c
     bce:	b0 83       	addri36.sp $r2,#0xc
     bd0:	44 30 00 10 	movi $r3,#0x10
     bd4:	49 00 2d 72 	jal 66b8 <lfs_file_read>
     bd8:	5a 00 10 13 	beqc $r0,#0x10,bfe <OTA_LITTLEFS_find_and_check+0x52>
     bdc:	fa 00       	movpi45 $r0,#0x10
     bde:	b6 1f       	swi450 $r0,[$sp]
     be0:	44 00 0a 78 	movi $r0,#0xa78
     be4:	49 ff fd 36 	jal 650 <tiny_printf>
     be8:	3e 08 2b 68 	addi.gp $r0,#0x2b68
     bec:	b0 4b       	addri36.sp $r1,#0x2c
     bee:	49 00 35 63 	jal 76b4 <lfs_file_close>
     bf2:	84 00       	movi55 $r0,#0x0
     bf4:	51 ff 82 20 	addi $sp,$sp,#0x220
     bf8:	3a 6f a0 84 	lmw.bim $r6,[$sp],$r8,#0x2    ! {$r6~$r8, $lp}
     bfc:	dd 9e       	ret5 $lp
     bfe:	b0 4b       	addri36.sp $r1,#0x2c
     c00:	3e 08 2b 68 	addi.gp $r0,#0x2b68
     c04:	49 00 35 58 	jal 76b4 <lfs_file_close>
     c08:	44 00 0a 88 	movi $r0,#0xa88
     c0c:	49 ff fd 22 	jal 650 <tiny_printf>
     c10:	3e 08 2b 68 	addi.gp $r0,#0x2b68
     c14:	b0 4b       	addri36.sp $r1,#0x2c
     c16:	44 20 0a 9c 	movi $r2,#0xa9c
     c1a:	84 61       	movi55 $r3,#0x1
     c1c:	49 00 37 06 	jal 7a28 <lfs_file_open>
     c20:	4e 05 00 60 	bltz $r0,ce0 <OTA_LITTLEFS_find_and_check+0x134>
     c24:	44 10 0a 9c 	movi $r1,#0xa9c
     c28:	50 2f 81 18 	addi $r2,$sp,#0x118
     c2c:	3e 08 2b 68 	addi.gp $r0,#0x2b68
     c30:	49 00 26 bc 	jal 59a8 <lfs_stat>
     c34:	f6 47       	lwi37.sp $r6,[+#0x11c]
     c36:	b0 20       	addri36.sp $r0,#0x80
     c38:	49 00 13 c0 	jal 33b8 <MD5_Init>
     c3c:	44 80 04 00 	movi $r8,#0x400
     c40:	ce 06       	bnez38 $r6,c4c <OTA_LITTLEFS_find_and_check+0xa0>
     c42:	d5 39       	j8 cb4 <OTA_LITTLEFS_find_and_check+0x108>
     c44:	49 00 13 d2 	jal 33e8 <MD5_Update>
     c48:	c6 36       	beqz38 $r6,cb4 <OTA_LITTLEFS_find_and_check+0x108>
     c4a:	92 00       	nop16
     c4c:	5c f3 04 00 	slti $r15,$r6,#0x400
     c50:	80 08       	mov55 $r0,$r8
     c52:	40 03 3c 1b 	cmovn $r0,$r6,$r15
     c56:	b0 4b       	addri36.sp $r1,#0x2c
     c58:	3e 28 2c 28 	addi.gp $r2,#0x2c28
     c5c:	80 60       	mov55 $r3,$r0
     c5e:	80 e0       	mov55 $r7,$r0
     c60:	3e 08 2b 68 	addi.gp $r0,#0x2b68
     c64:	49 00 2d 2a 	jal 66b8 <lfs_file_read>
     c68:	80 40       	mov55 $r2,$r0
     c6a:	3e 18 2c 28 	addi.gp $r1,#0x2c28
     c6e:	b0 20       	addri36.sp $r0,#0x80
     c70:	8a c2       	sub45 $r6,$r2
     c72:	4c 23 bf e9 	beq $r2,$r7,c44 <OTA_LITTLEFS_find_and_check+0x98>
     c76:	b6 ff       	swi450 $r7,[$sp]
     c78:	44 00 0a 78 	movi $r0,#0xa78
     c7c:	49 ff fc ea 	jal 650 <tiny_printf>
     c80:	b0 07       	addri36.sp $r0,#0x1c
     c82:	b0 60       	addri36.sp $r1,#0x80
     c84:	49 00 13 fa 	jal 3478 <MD5_Final>
     c88:	b0 4b       	addri36.sp $r1,#0x2c
     c8a:	3e 08 2b 68 	addi.gp $r0,#0x2b68
     c8e:	49 00 35 13 	jal 76b4 <lfs_file_close>
     c92:	84 00       	movi55 $r0,#0x0
     c94:	51 ff 82 20 	addi $sp,$sp,#0x220
     c98:	3a 6f a0 84 	lmw.bim $r6,[$sp],$r8,#0x2    ! {$r6~$r8, $lp}
     c9c:	dd 9e       	ret5 $lp
     c9e:	92 00       	nop16
     ca0:	44 00 0a 64 	movi $r0,#0xa64
     ca4:	49 ff fc d6 	jal 650 <tiny_printf>
     ca8:	84 00       	movi55 $r0,#0x0
     caa:	51 ff 82 20 	addi $sp,$sp,#0x220
     cae:	3a 6f a0 84 	lmw.bim $r6,[$sp],$r8,#0x2    ! {$r6~$r8, $lp}
     cb2:	dd 9e       	ret5 $lp
     cb4:	b0 07       	addri36.sp $r0,#0x1c
     cb6:	b0 60       	addri36.sp $r1,#0x80
     cb8:	49 00 13 e0 	jal 3478 <MD5_Final>
     cbc:	b0 4b       	addri36.sp $r1,#0x2c
     cbe:	3e 08 2b 68 	addi.gp $r0,#0x2b68
     cc2:	49 00 34 f9 	jal 76b4 <lfs_file_close>
     cc6:	b0 03       	addri36.sp $r0,#0xc
     cc8:	b0 47       	addri36.sp $r1,#0x1c
     cca:	fa 40       	movpi45 $r2,#0x10
     ccc:	49 00 0d 48 	jal 275c <my_memcmp>
     cd0:	5c 00 00 01 	slti $r0,$r0,#0x1
     cd4:	51 ff 82 20 	addi $sp,$sp,#0x220
     cd8:	3a 6f a0 84 	lmw.bim $r6,[$sp],$r8,#0x2    ! {$r6~$r8, $lp}
     cdc:	dd 9e       	ret5 $lp
     cde:	92 00       	nop16
     ce0:	44 00 0a a4 	movi $r0,#0xaa4
     ce4:	49 ff fc b6 	jal 650 <tiny_printf>
     ce8:	84 00       	movi55 $r0,#0x0
     cea:	48 ff ff 85 	j bf4 <OTA_LITTLEFS_find_and_check+0x48>
     cee:	92 00       	nop16

00000cf0 <OTA_LIEELEFS_find_and_update>:
     cf0:	3a 6f ba bc 	smw.adm $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
     cf4:	ee 94       	addi10.sp #-364
     cf6:	46 43 00 25 	sethi $r4,#0x30025
     cfa:	58 42 00 00 	ori $r4,$r4,#0x0
     cfe:	3e 08 2b 68 	addi.gp $r0,#0x2b68
     d02:	b0 43       	addri36.sp $r1,#0xc
     d04:	44 20 0a 54 	movi $r2,#0xa54
     d08:	84 61       	movi55 $r3,#0x1
     d0a:	f4 82       	swi37.sp $r4,[+#0x8]
     d0c:	49 00 36 8e 	jal 7a28 <lfs_file_open>
     d10:	4e 05 00 94 	bltz $r0,e38 <OTA_LIEELEFS_find_and_update+0x148>
     d14:	50 1f 80 0c 	addi $r1,$sp,#0xc
     d18:	3e 08 2b 68 	addi.gp $r0,#0x2b68
     d1c:	49 00 34 cc 	jal 76b4 <lfs_file_close>
     d20:	3e 08 2b 68 	addi.gp $r0,#0x2b68
     d24:	b0 43       	addri36.sp $r1,#0xc
     d26:	44 20 0a 9c 	movi $r2,#0xa9c
     d2a:	84 61       	movi55 $r3,#0x1
     d2c:	49 00 36 7e 	jal 7a28 <lfs_file_open>
     d30:	4e 05 00 8e 	bltz $r0,e4c <OTA_LIEELEFS_find_and_update+0x15c>
     d34:	44 10 0a 9c 	movi $r1,#0xa9c
     d38:	50 2f 80 60 	addi $r2,$sp,#0x60
     d3c:	3e 08 2b 68 	addi.gp $r0,#0x2b68
     d40:	49 00 26 34 	jal 59a8 <lfs_stat>
     d44:	04 ef 80 02 	lwi $r14,[$sp+#0x8]
     d48:	04 cf 80 19 	lwi $r12,[$sp+#0x64]
     d4c:	40 e7 20 08 	slli $r14,$r14,#0x8
     d50:	40 e7 20 09 	srli $r14,$r14,#0x8
     d54:	14 cf 80 00 	swi $r12,[$sp+#0x0]
     d58:	44 00 0a b4 	movi $r0,#0xab4
     d5c:	41 c7 30 00 	add $fp,$r14,$r12
     d60:	49 ff fc 78 	jal 650 <tiny_printf>
     d64:	40 07 70 06 	slt $r0,$r14,$fp
     d68:	81 6e       	mov55 $r11,$r14
     d6a:	44 d0 04 00 	movi $r13,#0x400
     d6e:	c0 43       	beqz38 $r0,df4 <OTA_LIEELEFS_find_and_update+0x104>
     d70:	40 66 b0 06 	slt $r6,$r13,$r12
     d74:	80 0d       	mov55 $r0,$r13
     d76:	40 06 18 1a 	cmovz $r0,$r12,$r6
     d7a:	80 c0       	mov55 $r6,$r0
     d7c:	f0 81       	swi37.sp $r0,[+#0x4]
     d7e:	b7 7f       	swi450 $r11,[$sp]
     d80:	44 00 0a d0 	movi $r0,#0xad0
     d84:	49 ff fc 66 	jal 650 <tiny_printf>
     d88:	3e 08 2b 68 	addi.gp $r0,#0x2b68
     d8c:	b0 43       	addri36.sp $r1,#0xc
     d8e:	3e 28 2c 28 	addi.gp $r2,#0x2c28
     d92:	80 66       	mov55 $r3,$r6
     d94:	49 00 2c 92 	jal 66b8 <lfs_file_read>
     d98:	81 40       	mov55 $r10,$r0
     d9a:	4c 03 40 3f 	bne $r0,$r6,e18 <OTA_LIEELEFS_find_and_update+0x128>
     d9e:	e3 6e       	slt45 $r11,$r14
     da0:	e9 24       	bnezs8 de8 <OTA_LIEELEFS_find_and_update+0xf8>
     da2:	54 05 8f ff 	andi $r0,$r11,#0xfff
     da6:	c0 35       	beqz38 $r0,e10 <OTA_LIEELEFS_find_and_update+0x120>
     da8:	4e a2 00 20 	beqz $r10,de8 <OTA_LIEELEFS_find_and_update+0xf8>
     dac:	3e 88 2c 28 	addi.gp $r8,#0x2c28
     db0:	80 eb       	mov55 $r7,$r11
     db2:	80 ca       	mov55 $r6,$r10
     db4:	85 20       	movi55 $r9,#0x0
     db6:	92 00       	nop16
     db8:	5c f3 01 00 	slti $r15,$r6,#0x100
     dbc:	80 07       	mov55 $r0,$r7
     dbe:	44 10 01 00 	movi $r1,#0x100
     dc2:	80 48       	mov55 $r2,$r8
     dc4:	e8 04       	beqzs8 dcc <OTA_LIEELEFS_find_and_update+0xdc>
     dc6:	80 07       	mov55 $r0,$r7
     dc8:	80 26       	mov55 $r1,$r6
     dca:	80 48       	mov55 $r2,$r8
     dcc:	50 94 81 00 	addi $r9,$r9,#0x100
     dd0:	49 ff fb d0 	jal 570 <ota_flash_page_program>
     dd4:	40 14 a8 06 	slt $r1,$r9,$r10
     dd8:	50 63 7f 00 	addi $r6,$r6,#-256
     ddc:	50 73 81 00 	addi $r7,$r7,#0x100
     de0:	50 84 01 00 	addi $r8,$r8,#0x100
     de4:	c9 ea       	bnez38 $r1,db8 <OTA_LIEELEFS_find_and_update+0xc8>
     de6:	92 00       	nop16
     de8:	50 b5 84 00 	addi $r11,$r11,#0x400
     dec:	e3 7c       	slt45 $r11,$fp
     dee:	50 c6 7c 00 	addi $r12,$r12,#-1024
     df2:	e9 bf       	bnezs8 d70 <OTA_LIEELEFS_find_and_update+0x80>
     df4:	44 00 00 e4 	movi $r0,#0xe4
     df8:	49 ff fc 2c 	jal 650 <tiny_printf>
     dfc:	b0 43       	addri36.sp $r1,#0xc
     dfe:	3e 08 2b 68 	addi.gp $r0,#0x2b68
     e02:	49 00 34 59 	jal 76b4 <lfs_file_close>
     e06:	84 01       	movi55 $r0,#0x1
     e08:	ed 6c       	addi10.sp #0x16c
     e0a:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
     e0e:	dd 9e       	ret5 $lp
     e10:	80 0b       	mov55 $r0,$r11
     e12:	49 ff fb 79 	jal 504 <ota_flash_sector_erase>
     e16:	d5 c9       	j8 da8 <OTA_LIEELEFS_find_and_update+0xb8>
     e18:	b7 7f       	swi450 $r11,[$sp]
     e1a:	44 00 0a e4 	movi $r0,#0xae4
     e1e:	49 ff fc 19 	jal 650 <tiny_printf>
     e22:	b0 43       	addri36.sp $r1,#0xc
     e24:	3e 08 2b 68 	addi.gp $r0,#0x2b68
     e28:	49 00 34 46 	jal 76b4 <lfs_file_close>
     e2c:	84 00       	movi55 $r0,#0x0
     e2e:	ed 6c       	addi10.sp #0x16c
     e30:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
     e34:	dd 9e       	ret5 $lp
     e36:	92 00       	nop16
     e38:	44 00 0a 64 	movi $r0,#0xa64
     e3c:	49 ff fc 0a 	jal 650 <tiny_printf>
     e40:	84 00       	movi55 $r0,#0x0
     e42:	ed 6c       	addi10.sp #0x16c
     e44:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
     e48:	dd 9e       	ret5 $lp
     e4a:	92 00       	nop16
     e4c:	44 00 0a a4 	movi $r0,#0xaa4
     e50:	49 ff fc 00 	jal 650 <tiny_printf>
     e54:	84 00       	movi55 $r0,#0x0
     e56:	ed 6c       	addi10.sp #0x16c
     e58:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
     e5c:	dd 9e       	ret5 $lp
     e5e:	92 00       	nop16

00000e60 <drv_uart_tx_0>:
     e60:	3b ff fc bc 	smw.adm $sp,[$sp],$sp,#0x2    ! {$lp}
     e64:	ef f4       	addi10.sp #-12
     e66:	84 21       	movi55 $r1,#0x1
     e68:	10 0f 80 07 	sbi $r0,[$sp+#0x7]
     e6c:	44 20 00 01 	movi $r2,#0x1
     e70:	50 0f 80 07 	addi $r0,$sp,#0x7
     e74:	49 00 02 76 	jal 1360 <drv_comport_write_fifo>
     e78:	ec 0c       	addi10.sp #0xc
     e7a:	3b ff fc 84 	lmw.bim $sp,[$sp],$sp,#0x2    ! {$lp}
     e7e:	dd 9e       	ret5 $lp

00000e80 <Cli_Init>:
     e80:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
     e84:	84 20       	movi55 $r1,#0x0
     e86:	fa 44       	movpi45 $r2,#0x14
     e88:	3e 08 01 b0 	addi.gp $r0,#0x1b0
     e8c:	49 00 48 94 	jal 9fb4 <memset>
     e90:	84 20       	movi55 $r1,#0x0
     e92:	84 00       	movi55 $r0,#0x0
     e94:	3e 10 01 c8 	sbi.gp $r1,[+#0x1c8]
     e98:	3c 0e 00 6a 	swi.gp $r0,[+#0x1a8]
     e9c:	3c 0e 00 6b 	swi.gp $r0,[+#0x1ac]
     ea0:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
     ea4:	dd 9e       	ret5 $lp
     ea6:	92 00       	nop16
     ea8:	72 65 61 64 	*unknown*
     eac:	20 66 61 6c 	lbsi $r6,[$r12+#-7828]
     eb0:	69 73 0a 00 	*unknown*
     eb4:	0a 45 52 52 	lhi.bi $r4,[$r10],#-23388
     eb8:	4f 52 3a 2d 	beqz $r21,8312 <Cmd_Meta_restore+0xf6>
     ebc:	31 0a 00 00 	flsi $fs16,[$r20+#0x0]
     ec0:	0a 25 73 00 	lhi.bi $r2,[$r10],#-6656
     ec4:	3f 3e 00 00 	addi.gp $r19,#-131072
     ec8:	0a 0a 55 73 	lhi.bi $r0,[$r20],#-21786
     ecc:	61 67 65 3a 	amtbsl2.s $d0,$r14,$r25,[$i2],[$i6],$m2,$m7
     ed0:	0a 00 00 00 	lhi.bi $r0,[$r0],#0x0
     ed4:	25 2d 32 30 	*unknown*
     ed8:	73 09 09 25 	*unknown*
     edc:	73 0a 00 00 	*unknown*

00000ee0 <getDatafromUart>:
     ee0:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
     ee4:	44 20 00 01 	movi $r2,#0x1
     ee8:	49 00 02 4a 	jal 137c <drv_comport_read_fifo>
     eec:	4e 07 00 08 	blez $r0,efc <getDatafromUart+0x1c>
     ef0:	44 00 00 00 	movi $r0,#0x0
     ef4:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
     ef8:	4a 00 78 20 	ret $lp
     efc:	44 00 0e a8 	movi $r0,#0xea8
     f00:	49 00 0a 9c 	jal 2438 <printf>
     f04:	84 1f       	movi55 $r0,#-1
     f06:	d5 f7       	j8 ef4 <getDatafromUart+0x14>

00000f08 <Cli_Start>:
     f08:	3a 6f a0 bc 	smw.adm $r6,[$sp],$r8,#0x2    ! {$r6~$r8, $lp}
     f0c:	51 ff ff f0 	addi $sp,$sp,#-16
     f10:	46 00 00 08 	sethi $r0,#0x8
     f14:	3e 88 01 c8 	addi.gp $r8,#0x1c8
     f18:	04 60 01 10 	lwi $r6,[$r0+#0x440]
     f1c:	50 0f 80 0b 	addi $r0,$sp,#0xb
     f20:	84 21       	movi55 $r1,#0x1
     f22:	84 41       	movi55 $r2,#0x1
     f24:	49 00 02 2c 	jal 137c <drv_comport_read_fifo>
     f28:	4e 07 01 10 	blez $r0,1148 <Cli_Start+0x240>
     f2c:	00 0f 80 0b 	lbi $r0,[$sp+#0xb]
     f30:	5a 00 0d 30 	beqc $r0,#0xd,f90 <Cli_Start+0x88>
     f34:	e6 0e       	slti45 $r0,#0xe
     f36:	e9 27       	bnezs8 f84 <Cli_Start+0x7c>
     f38:	5a 08 3f 04 	bnec $r0,#0x3f,f40 <Cli_Start+0x38>
     f3c:	48 00 00 ea 	j 1110 <Cli_Start+0x208>
     f40:	5a 08 7f 04 	bnec $r0,#0x7f,f48 <Cli_Start+0x40>
     f44:	48 00 00 c0 	j 10c4 <Cli_Start+0x1bc>
     f48:	5a 00 1b ea 	beqc $r0,#0x1b,f1c <Cli_Start+0x14>
     f4c:	3c 4c 00 6a 	lwi.gp $r4,[+#0x1a8]
     f50:	5c f2 07 ff 	slti $r15,$r4,#0x7ff
     f54:	e8 e4       	beqzs8 f1c <Cli_Start+0x14>
     f56:	96 c2       	seb33 $r3,$r0
     f58:	9d 61       	addi333 $r5,$r4,#0x1
     f5a:	38 34 10 08 	sb $r3,[$r8+($r4<<#0x0)]
     f5e:	3c 5e 00 6a 	swi.gp $r5,[+#0x1a8]
     f62:	50 0f 80 0f 	addi $r0,$sp,#0xf
     f66:	84 80       	movi55 $r4,#0x0
     f68:	84 21       	movi55 $r1,#0x1
     f6a:	84 41       	movi55 $r2,#0x1
     f6c:	38 44 14 08 	sb $r4,[$r8+($r5<<#0x0)]
     f70:	10 3f 80 0f 	sbi $r3,[$sp+#0xf]
     f74:	49 00 01 f6 	jal 1360 <drv_comport_write_fifo>
     f78:	3c 0c 00 1c 	lwi.gp $r0,[+#0x70]
     f7c:	49 00 47 0e 	jal 9d98 <fflush>
     f80:	d5 ce       	j8 f1c <Cli_Start+0x14>
     f82:	92 00       	nop16
     f84:	5a 08 08 04 	bnec $r0,#0x8,f8c <Cli_Start+0x84>
     f88:	48 00 00 9e 	j 10c4 <Cli_Start+0x1bc>
     f8c:	5a 08 0a e0 	bnec $r0,#0xa,f4c <Cli_Start+0x44>
     f90:	3e 08 01 c8 	addi.gp $r0,#0x1c8
     f94:	49 00 49 5a 	jal a248 <strlen>
     f98:	4e 03 00 e4 	bnez $r0,1160 <Cli_Start+0x258>
     f9c:	2e 28 01 c8 	lbsi.gp $r2,[+#0x1c8]
     fa0:	84 00       	movi55 $r0,#0x0
     fa2:	3c 0e 00 6b 	swi.gp $r0,[+#0x1ac]
     fa6:	10 0f 80 0b 	sbi $r0,[$sp+#0xb]
     faa:	c2 51       	beqz38 $r2,104c <Cli_Start+0x144>
     fac:	84 20       	movi55 $r1,#0x0
     fae:	86 00       	movi55 $r16,#0x0
     fb0:	84 60       	movi55 $r3,#0x0
     fb2:	84 a0       	movi55 $r5,#0x0
     fb4:	3e 08 01 c8 	addi.gp $r0,#0x1c8
     fb8:	86 40       	movi55 $r18,#0x0
     fba:	3f 18 01 b0 	addi.gp $r17,#0x1b0
     fbe:	92 00       	nop16
     fc0:	4e 33 00 72 	bnez $r3,10a4 <Cli_Start+0x19c>
     fc4:	5a 28 20 04 	bnec $r2,#0x20,fcc <Cli_Start+0xc4>
     fc8:	48 00 00 7a 	j 10bc <Cli_Start+0x1b4>
     fcc:	38 08 86 0a 	sw $r0,[$r17+($r1<<#0x2)]
     fd0:	45 00 00 01 	movi $r16,#0x1
     fd4:	20 20 00 00 	lbsi $r2,[$r0+#0x0]
     fd8:	5a 28 3d 04 	bnec $r2,#0x3d,fe0 <Cli_Start+0xd8>
     fdc:	48 00 00 ae 	j 1138 <Cli_Start+0x230>
     fe0:	5a 20 2c 4a 	beqc $r2,#0x2c,1074 <Cli_Start+0x16c>
     fe4:	80 70       	mov55 $r3,$r16
     fe6:	80 a1       	mov55 $r5,$r1
     fe8:	20 20 00 01 	lbsi $r2,[$r0+#0x1]
     fec:	8c 01       	addi45 $r0,#0x1
     fee:	c2 4f       	beqz38 $r2,108c <Cli_Start+0x184>
     ff0:	e6 26       	slti45 $r1,#0x6
     ff2:	e9 e7       	bnezs8 fc0 <Cli_Start+0xb8>
     ff4:	46 20 01 00 	sethi $r2,#0x100
     ff8:	11 0f 80 0b 	sbi $r16,[$sp+#0xb]
     ffc:	3c 1e 00 6b 	swi.gp $r1,[+#0x1ac]
    1000:	5a 38 01 04 	bnec $r3,#0x1,1008 <Cli_Start+0x100>
    1004:	48 00 00 e0 	j 11c4 <Cli_Start+0x2bc>
    1008:	fa 30       	movpi45 $r1,#0x20
    100a:	10 10 7f ff 	sbi $r1,[$r0+#-1]
    100e:	80 26       	mov55 $r1,$r6
    1010:	4e 62 00 e2 	beqz $r6,11d4 <Cli_Start+0x2cc>
    1014:	44 70 84 40 	movi $r7,#0x8440
    1018:	d5 06       	j8 1024 <Cli_Start+0x11c>
    101a:	8c ec       	addi45 $r7,#0xc
    101c:	b4 27       	lwi450 $r1,[$r7]
    101e:	4e 12 00 db 	beqz $r1,11d4 <Cli_Start+0x2cc>
    1022:	92 00       	nop16
    1024:	3c 0c 00 6c 	lwi.gp $r0,[+#0x1b0]
    1028:	49 00 48 ec 	jal a200 <strcmp>
    102c:	4e 03 ff f7 	bnez $r0,101a <Cli_Start+0x112>
    1030:	44 00 00 e4 	movi $r0,#0xe4
    1034:	49 00 0a 02 	jal 2438 <printf>
    1038:	3c 0c 00 6b 	lwi.gp $r0,[+#0x1ac]
    103c:	a0 b9       	lwi333 $r2,[$r7+#0x4]
    103e:	8e 01       	subi45 $r0,#0x1
    1040:	3e 18 01 b4 	addi.gp $r1,#0x1b4
    1044:	dd 22       	jral5 $r2
    1046:	b4 07       	lwi450 $r0,[$r7]
    1048:	4e 02 00 c6 	beqz $r0,11d4 <Cli_Start+0x2cc>
    104c:	44 00 0e c4 	movi $r0,#0xec4
    1050:	b6 1f       	swi450 $r0,[$sp]
    1052:	44 00 0e c0 	movi $r0,#0xec0
    1056:	49 00 09 f1 	jal 2438 <printf>
    105a:	84 20       	movi55 $r1,#0x0
    105c:	3e 08 01 c8 	addi.gp $r0,#0x1c8
    1060:	44 20 08 01 	movi $r2,#0x801
    1064:	49 00 47 a8 	jal 9fb4 <memset>
    1068:	84 00       	movi55 $r0,#0x0
    106a:	3c 0e 00 6a 	swi.gp $r0,[+#0x1a8]
    106e:	48 ff ff 57 	j f1c <Cli_Start+0x14>
    1072:	92 00       	nop16
    1074:	4e 12 00 6e 	beqz $r1,1150 <Cli_Start+0x248>
    1078:	20 20 00 01 	lbsi $r2,[$r0+#0x1]
    107c:	8c 21       	addi45 $r1,#0x1
    107e:	11 20 00 00 	sbi $r18,[$r0+#0x0]
    1082:	80 a1       	mov55 $r5,$r1
    1084:	86 00       	movi55 $r16,#0x0
    1086:	84 60       	movi55 $r3,#0x0
    1088:	8c 01       	addi45 $r0,#0x1
    108a:	ca b3       	bnez38 $r2,ff0 <Cli_Start+0xe8>
    108c:	46 20 01 00 	sethi $r2,#0x100
    1090:	11 0f 80 0b 	sbi $r16,[$sp+#0xb]
    1094:	3c 1e 00 6b 	swi.gp $r1,[+#0x1ac]
    1098:	5a 38 01 04 	bnec $r3,#0x1,10a0 <Cli_Start+0x198>
    109c:	48 00 00 94 	j 11c4 <Cli_Start+0x2bc>
    10a0:	c9 b4       	bnez38 $r1,1008 <Cli_Start+0x100>
    10a2:	d5 d5       	j8 104c <Cli_Start+0x144>
    10a4:	5a 30 01 04 	beqc $r3,#0x1,10ac <Cli_Start+0x1a4>
    10a8:	48 ff ff 9f 	j fe6 <Cli_Start+0xde>
    10ac:	5a 20 20 04 	beqc $r2,#0x20,10b4 <Cli_Start+0x1ac>
    10b0:	48 ff ff 92 	j fd4 <Cli_Start+0xcc>
    10b4:	11 20 00 00 	sbi $r18,[$r0+#0x0]
    10b8:	9c 69       	addi333 $r1,$r5,#0x1
    10ba:	86 00       	movi55 $r16,#0x0
    10bc:	80 a1       	mov55 $r5,$r1
    10be:	84 60       	movi55 $r3,#0x0
    10c0:	48 ff ff 94 	j fe8 <Cli_Start+0xe0>
    10c4:	3c 0c 00 6a 	lwi.gp $r0,[+#0x1a8]
    10c8:	4e 02 ff 2a 	beqz $r0,f1c <Cli_Start+0x14>
    10cc:	9e c1       	subi333 $r3,$r0,#0x1
    10ce:	84 e8       	movi55 $r7,#0x8
    10d0:	3c 3e 00 6a 	swi.gp $r3,[+#0x1a8]
    10d4:	b0 03       	addri36.sp $r0,#0xc
    10d6:	84 80       	movi55 $r4,#0x0
    10d8:	84 21       	movi55 $r1,#0x1
    10da:	84 41       	movi55 $r2,#0x1
    10dc:	38 44 0c 08 	sb $r4,[$r8+($r3<<#0x0)]
    10e0:	10 7f 80 0c 	sbi $r7,[$sp+#0xc]
    10e4:	49 00 01 3e 	jal 1360 <drv_comport_write_fifo>
    10e8:	fa 70       	movpi45 $r3,#0x20
    10ea:	50 0f 80 0d 	addi $r0,$sp,#0xd
    10ee:	84 21       	movi55 $r1,#0x1
    10f0:	44 20 00 01 	movi $r2,#0x1
    10f4:	10 3f 80 0d 	sbi $r3,[$sp+#0xd]
    10f8:	49 00 01 34 	jal 1360 <drv_comport_write_fifo>
    10fc:	50 0f 80 0e 	addi $r0,$sp,#0xe
    1100:	84 21       	movi55 $r1,#0x1
    1102:	84 41       	movi55 $r2,#0x1
    1104:	10 7f 80 0e 	sbi $r7,[$sp+#0xe]
    1108:	49 00 01 2c 	jal 1360 <drv_comport_write_fifo>
    110c:	48 ff ff 08 	j f1c <Cli_Start+0x14>
    1110:	3c 2c 00 6a 	lwi.gp $r2,[+#0x1a8]
    1114:	c2 30       	beqz38 $r2,1174 <Cli_Start+0x26c>
    1116:	3c 1c 00 01 	lwi.gp $r1,[+#0x4]
    111a:	8e 21       	subi45 $r1,#0x1
    111c:	e2 41       	slt45 $r2,$r1
    111e:	4e f2 fe ff 	beqz $r15,f1c <Cli_Start+0x14>
    1122:	9c 51       	addi333 $r1,$r2,#0x1
    1124:	38 04 08 08 	sb $r0,[$r8+($r2<<#0x0)]
    1128:	3c 1e 00 6a 	swi.gp $r1,[+#0x1a8]
    112c:	84 00       	movi55 $r0,#0x0
    112e:	38 04 04 08 	sb $r0,[$r8+($r1<<#0x0)]
    1132:	48 ff fe f5 	j f1c <Cli_Start+0x14>
    1136:	92 00       	nop16
    1138:	4e 13 ff 56 	bnez $r1,fe4 <Cli_Start+0xdc>
    113c:	ae 40       	sbi333 $r1,[$r0+#0x0]
    113e:	86 00       	movi55 $r16,#0x0
    1140:	84 21       	movi55 $r1,#0x1
    1142:	84 60       	movi55 $r3,#0x0
    1144:	48 ff ff 51 	j fe6 <Cli_Start+0xde>
    1148:	ec 10       	addi10.sp #0x10
    114a:	3a 6f a0 84 	lmw.bim $r6,[$sp],$r8,#0x2    ! {$r6~$r8, $lp}
    114e:	dd 9e       	ret5 $lp
    1150:	20 20 00 01 	lbsi $r2,[$r0+#0x1]
    1154:	8c 01       	addi45 $r0,#0x1
    1156:	c2 49       	beqz38 $r2,11e8 <Cli_Start+0x2e0>
    1158:	80 70       	mov55 $r3,$r16
    115a:	84 a0       	movi55 $r5,#0x0
    115c:	48 ff ff 32 	j fc0 <Cli_Start+0xb8>
    1160:	3e 08 01 c8 	addi.gp $r0,#0x1c8
    1164:	49 00 48 72 	jal a248 <strlen>
    1168:	44 10 00 00 	movi $r1,#0x0
    116c:	38 14 00 08 	sb $r1,[$r8+($r0<<#0x0)]
    1170:	48 ff ff 16 	j f9c <Cli_Start+0x94>
    1174:	44 00 0e c8 	movi $r0,#0xec8
    1178:	49 00 09 60 	jal 2438 <printf>
    117c:	46 00 00 08 	sethi $r0,#0x8
    1180:	04 00 01 10 	lwi $r0,[$r0+#0x440]
    1184:	44 70 84 40 	movi $r7,#0x8440
    1188:	c8 05       	bnez38 $r0,1192 <Cli_Start+0x28a>
    118a:	d5 13       	j8 11b0 <Cli_Start+0x2a8>
    118c:	8c ec       	addi45 $r7,#0xc
    118e:	b4 07       	lwi450 $r0,[$r7]
    1190:	c0 10       	beqz38 $r0,11b0 <Cli_Start+0x2a8>
    1192:	a0 3a       	lwi333 $r0,[$r7+#0x8]
    1194:	49 00 48 5a 	jal a248 <strlen>
    1198:	c0 fa       	beqz38 $r0,118c <Cli_Start+0x284>
    119a:	a0 3a       	lwi333 $r0,[$r7+#0x8]
    119c:	b4 27       	lwi450 $r1,[$r7]
    119e:	b6 3f       	swi450 $r1,[$sp]
    11a0:	f0 81       	swi37.sp $r0,[+#0x4]
    11a2:	8c ec       	addi45 $r7,#0xc
    11a4:	44 00 0e d4 	movi $r0,#0xed4
    11a8:	49 00 09 48 	jal 2438 <printf>
    11ac:	b4 07       	lwi450 $r0,[$r7]
    11ae:	c8 f2       	bnez38 $r0,1192 <Cli_Start+0x28a>
    11b0:	44 00 0e c4 	movi $r0,#0xec4
    11b4:	14 0f 80 00 	swi $r0,[$sp+#0x0]
    11b8:	44 00 0e c0 	movi $r0,#0xec0
    11bc:	49 00 09 3e 	jal 2438 <printf>
    11c0:	48 ff fe ae 	j f1c <Cli_Start+0x14>
    11c4:	8c 21       	addi45 $r1,#0x1
    11c6:	3c 1e 00 6b 	swi.gp $r1,[+#0x1ac]
    11ca:	4e 12 ff 41 	beqz $r1,104c <Cli_Start+0x144>
    11ce:	48 ff ff 20 	j 100e <Cli_Start+0x106>
    11d2:	92 00       	nop16
    11d4:	3c 0c 00 6a 	lwi.gp $r0,[+#0x1a8]
    11d8:	4e 02 ff 3a 	beqz $r0,104c <Cli_Start+0x144>
    11dc:	44 00 0e b4 	movi $r0,#0xeb4
    11e0:	49 00 09 2c 	jal 2438 <printf>
    11e4:	48 ff ff 34 	j 104c <Cli_Start+0x144>
    11e8:	11 0f 80 0b 	sbi $r16,[$sp+#0xb]
    11ec:	3c 1e 00 6b 	swi.gp $r1,[+#0x1ac]
    11f0:	5b 00 01 04 	beqc $r16,#0x1,11f8 <Cli_Start+0x2f0>
    11f4:	48 ff ff 2c 	j 104c <Cli_Start+0x144>
    11f8:	3d 0e 00 6b 	swi.gp $r16,[+#0x1ac]
    11fc:	48 ff ff 09 	j 100e <Cli_Start+0x106>

00001200 <comport_uart_register_isr>:
    1200:	48 00 39 84 	j 8508 <hal_uart_register_isr>

00001204 <comport_uart_init>:
    1204:	48 00 39 a2 	j 8548 <hal_uart_init>

00001208 <comport_uart_deinit>:
    1208:	48 00 39 b6 	j 8574 <hal_uart_deinit>

0000120c <comport_uart_set_format>:
    120c:	48 00 39 b8 	j 857c <hal_uart_set_format>

00001210 <comport_uart_write_fifo>:
    1210:	48 00 39 de 	j 85cc <hal_uart_write_fifo>

00001214 <comport_uart_read_fifo>:
    1214:	48 00 3a 30 	j 8674 <hal_uart_read_fifo>

00001218 <comport_uart_sw_rst>:
    1218:	48 00 3a 62 	j 86dc <hal_uart_sw_rst>

0000121c <comport_uart_get_line_status>:
    121c:	48 00 3a 66 	j 86e8 <hal_uart_get_line_status>

00001220 <comport_uart_is_receiver_available>:
    1220:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    1224:	49 00 3a 62 	jal 86e8 <hal_uart_get_line_status>
    1228:	96 04       	xlsb33 $r0,$r0
    122a:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    122e:	dd 9e       	ret5 $lp

00001230 <comport_uart_is_transmitter_idle>:
    1230:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    1234:	49 00 3a 5a 	jal 86e8 <hal_uart_get_line_status>
    1238:	42 00 18 0b 	btst $r0,$r0,#0x6
    123c:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    1240:	dd 9e       	ret5 $lp
    1242:	92 00       	nop16

00001244 <comport_uart_direct_read_byte>:
    1244:	48 00 39 be 	j 85c0 <hal_uart_direct_read_byte>

00001248 <comport_hsuart_register_isr>:
    1248:	80 60       	mov55 $r3,$r0
    124a:	80 41       	mov55 $r2,$r1
    124c:	2e 00 09 cc 	lbi.gp $r0,[+#0x9cc]
    1250:	80 23       	mov55 $r1,$r3
    1252:	48 00 3a cd 	j 87ec <hal_hsuart_register_isr_ex>
    1256:	92 00       	nop16

00001258 <comport_hsuart_init>:
    1258:	2e 00 09 cc 	lbi.gp $r0,[+#0x9cc]
    125c:	48 00 3a ec 	j 8834 <hal_hsuart_init_ex>

00001260 <comport_hsuart_deinit>:
    1260:	2e 00 09 cc 	lbi.gp $r0,[+#0x9cc]
    1264:	48 00 3b 04 	j 886c <hal_hsuart_deinit_ex>

00001268 <comport_hsuart_set_format>:
    1268:	82 20       	mov55 $r17,$r0
    126a:	82 01       	mov55 $r16,$r1
    126c:	80 a2       	mov55 $r5,$r2
    126e:	80 83       	mov55 $r4,$r3
    1270:	2e 00 09 cc 	lbi.gp $r0,[+#0x9cc]
    1274:	80 31       	mov55 $r1,$r17
    1276:	80 50       	mov55 $r2,$r16
    1278:	80 65       	mov55 $r3,$r5
    127a:	48 00 3b 03 	j 8880 <hal_hsuart_set_format_ex>
    127e:	92 00       	nop16

00001280 <comport_hsuart_write_fifo>:
    1280:	80 a0       	mov55 $r5,$r0
    1282:	80 81       	mov55 $r4,$r1
    1284:	80 62       	mov55 $r3,$r2
    1286:	2e 00 09 cc 	lbi.gp $r0,[+#0x9cc]
    128a:	80 25       	mov55 $r1,$r5
    128c:	80 44       	mov55 $r2,$r4
    128e:	48 00 3b 2f 	j 88ec <hal_hsuart_write_fifo_ex>
    1292:	92 00       	nop16

00001294 <comport_hsuart_read_fifo>:
    1294:	80 a0       	mov55 $r5,$r0
    1296:	80 81       	mov55 $r4,$r1
    1298:	80 62       	mov55 $r3,$r2
    129a:	2e 00 09 cc 	lbi.gp $r0,[+#0x9cc]
    129e:	80 25       	mov55 $r1,$r5
    12a0:	80 44       	mov55 $r2,$r4
    12a2:	48 00 3b 77 	j 8990 <hal_hsuart_read_fifo_ex>
    12a6:	92 00       	nop16

000012a8 <comport_hsuart_sw_rst>:
    12a8:	2e 00 09 cc 	lbi.gp $r0,[+#0x9cc]
    12ac:	48 00 3b a8 	j 89fc <hal_hsuart_sw_rst_ex>

000012b0 <comport_hsuart_get_line_status>:
    12b0:	2e 00 09 cc 	lbi.gp $r0,[+#0x9cc]
    12b4:	48 00 3b b4 	j 8a1c <hal_hsuart_get_line_status_ex>

000012b8 <comport_hsuart_is_receiver_available>:
    12b8:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    12bc:	2e 00 09 cc 	lbi.gp $r0,[+#0x9cc]
    12c0:	49 00 3b ae 	jal 8a1c <hal_hsuart_get_line_status_ex>
    12c4:	96 04       	xlsb33 $r0,$r0
    12c6:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    12ca:	dd 9e       	ret5 $lp

000012cc <comport_hsuart_is_transmitter_idle>:
    12cc:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    12d0:	2e 00 09 cc 	lbi.gp $r0,[+#0x9cc]
    12d4:	49 00 3b a4 	jal 8a1c <hal_hsuart_get_line_status_ex>
    12d8:	42 00 18 0b 	btst $r0,$r0,#0x6
    12dc:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    12e0:	dd 9e       	ret5 $lp
    12e2:	92 00       	nop16

000012e4 <comport_hsuart_direct_read_byte>:
    12e4:	2e 00 09 cc 	lbi.gp $r0,[+#0x9cc]
    12e8:	48 00 3b a0 	j 8a28 <hal_hsuart_direct_read_byte_ex>

000012ec <drv_comport_init>:
    12ec:	3b ff fc bc 	smw.adm $sp,[$sp],$sp,#0x2    ! {$lp}
    12f0:	ef f4       	addi10.sp #-12
    12f2:	3c 1c 02 74 	lwi.gp $r1,[+#0x9d0]
    12f6:	c1 05       	beqz38 $r1,1300 <drv_comport_init+0x14>
    12f8:	a0 4a       	lwi333 $r1,[$r1+#0x8]
    12fa:	f0 81       	swi37.sp $r0,[+#0x4]
    12fc:	dd 21       	jral5 $r1
    12fe:	f0 01       	lwi37.sp $r0,[+#0x4]
    1300:	c8 10       	bnez38 $r0,1320 <drv_comport_init+0x34>
    1302:	3e 08 00 34 	addi.gp $r0,#0x34
    1306:	3c 0e 02 74 	swi.gp $r0,[+#0x9d0]
    130a:	a0 01       	lwi333 $r0,[$r0+#0x4]
    130c:	4b e0 00 01 	jral $lp,$r0
    1310:	3c 0c 02 74 	lwi.gp $r0,[+#0x9d0]
    1314:	a0 06       	lwi333 $r0,[$r0+#0x18]
    1316:	dd 20       	jral5 $r0
    1318:	ec 0c       	addi10.sp #0xc
    131a:	3b ff fc 84 	lmw.bim $sp,[$sp],$sp,#0x2    ! {$lp}
    131e:	dd 9e       	ret5 $lp
    1320:	5a 00 01 0a 	beqc $r0,#0x1,1334 <drv_comport_init+0x48>
    1324:	84 00       	movi55 $r0,#0x0
    1326:	3c 0e 02 74 	swi.gp $r0,[+#0x9d0]
    132a:	ec 0c       	addi10.sp #0xc
    132c:	3b ff fc 84 	lmw.bim $sp,[$sp],$sp,#0x2    ! {$lp}
    1330:	4a 00 78 20 	ret $lp
    1334:	3e 08 00 08 	addi.gp $r0,#0x8
    1338:	3c 0e 02 74 	swi.gp $r0,[+#0x9d0]
    133c:	84 20       	movi55 $r1,#0x0
    133e:	3e 10 09 cc 	sbi.gp $r1,[+#0x9cc]
    1342:	d5 e4       	j8 130a <drv_comport_init+0x1e>

00001344 <drv_comport_set_format>:
    1344:	3c 4c 02 74 	lwi.gp $r4,[+#0x9d0]
    1348:	c4 09       	beqz38 $r4,135a <drv_comport_set_format+0x16>
    134a:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    134e:	a1 23       	lwi333 $r4,[$r4+#0xc]
    1350:	4b e0 10 01 	jral $lp,$r4
    1354:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    1358:	dd 9e       	ret5 $lp
    135a:	84 1f       	movi55 $r0,#-1
    135c:	dd 9e       	ret5 $lp
    135e:	92 00       	nop16

00001360 <drv_comport_write_fifo>:
    1360:	3c 3c 02 74 	lwi.gp $r3,[+#0x9d0]
    1364:	c3 09       	beqz38 $r3,1376 <drv_comport_write_fifo+0x16>
    1366:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    136a:	a0 dc       	lwi333 $r3,[$r3+#0x10]
    136c:	4b e0 0c 01 	jral $lp,$r3
    1370:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    1374:	dd 9e       	ret5 $lp
    1376:	84 1f       	movi55 $r0,#-1
    1378:	dd 9e       	ret5 $lp
    137a:	92 00       	nop16

0000137c <drv_comport_read_fifo>:
    137c:	3c 3c 02 74 	lwi.gp $r3,[+#0x9d0]
    1380:	c3 09       	beqz38 $r3,1392 <drv_comport_read_fifo+0x16>
    1382:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    1386:	a0 dd       	lwi333 $r3,[$r3+#0x14]
    1388:	4b e0 0c 01 	jral $lp,$r3
    138c:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    1390:	dd 9e       	ret5 $lp
    1392:	84 1f       	movi55 $r0,#-1
    1394:	dd 9e       	ret5 $lp
    1396:	92 00       	nop16

00001398 <_out_null>:
    1398:	dd 9e       	ret5 $lp
    139a:	92 00       	nop16

0000139c <_ntoa_format>:
    139c:	3a 6f ba bc 	smw.adm $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    13a0:	ef fc       	addi10.sp #-4
    13a2:	05 0f 80 10 	lwi $r16,[$sp+#0x40]
    13a6:	81 a2       	mov55 $r13,$r2
    13a8:	55 c8 00 02 	andi $fp,$r16,#0x2
    13ac:	80 e4       	mov55 $r7,$r4
    13ae:	fd 40       	movd44 $r8,$r0
    13b0:	81 43       	mov55 $r10,$r3
    13b2:	00 4f 80 30 	lbi $r4,[$sp+#0x30]
    13b6:	f2 0e       	lwi37.sp $r2,[+#0x38]
    13b8:	04 cf 80 0f 	lwi $r12,[$sp+#0x3c]
    13bc:	4f c3 00 32 	bnez $fp,1420 <_ntoa_format+0x84>
    13c0:	e2 a2       	slt45 $r5,$r2
    13c2:	e8 11       	beqzs8 13e4 <_ntoa_format+0x48>
    13c4:	5c f2 80 20 	slti $r15,$r5,#0x20
    13c8:	e8 0e       	beqzs8 13e4 <_ntoa_format+0x48>
    13ca:	98 3d       	add333 $r0,$r7,$r5
    13cc:	44 30 00 30 	movi $r3,#0x30
    13d0:	d5 04       	j8 13d8 <_ntoa_format+0x3c>
    13d2:	92 00       	nop16
    13d4:	5a 50 20 08 	beqc $r5,#0x20,13e4 <_ntoa_format+0x48>
    13d8:	8c a1       	addi45 $r5,#0x1
    13da:	e2 a2       	slt45 $r5,$r2
    13dc:	18 30 00 01 	sbi.bi $r3,[$r0],#0x1
    13e0:	4e f3 ff fa 	bnez $r15,13d4 <_ntoa_format+0x38>
    13e4:	54 08 00 01 	andi $r0,$r16,#0x1
    13e8:	c0 1c       	beqz38 $r0,1420 <_ntoa_format+0x84>
    13ea:	e2 ac       	slt45 $r5,$r12
    13ec:	e8 1a       	beqzs8 1420 <_ntoa_format+0x84>
    13ee:	5c f2 80 20 	slti $r15,$r5,#0x20
    13f2:	4e f2 00 f3 	beqz $r15,15d8 <_ntoa_format+0x23c>
    13f6:	44 00 00 30 	movi $r0,#0x30
    13fa:	9d a9       	addi333 $r6,$r5,#0x1
    13fc:	38 03 94 08 	sb $r0,[$r7+($r5<<#0x0)]
    1400:	44 10 00 30 	movi $r1,#0x30
    1404:	98 3e       	add333 $r0,$r7,$r6
    1406:	d5 09       	j8 1418 <_ntoa_format+0x7c>
    1408:	5a 68 20 04 	bnec $r6,#0x20,1410 <_ntoa_format+0x74>
    140c:	48 00 00 b0 	j 156c <_ntoa_format+0x1d0>
    1410:	8c c1       	addi45 $r6,#0x1
    1412:	18 10 00 01 	sbi.bi $r1,[$r0],#0x1
    1416:	92 00       	nop16
    1418:	4c 66 7f f8 	bne $r6,$r12,1408 <_ntoa_format+0x6c>
    141c:	80 ac       	mov55 $r5,$r12
    141e:	92 00       	nop16
    1420:	54 08 00 10 	andi $r0,$r16,#0x10
    1424:	4e 02 00 64 	beqz $r0,14ec <_ntoa_format+0x150>
    1428:	54 08 04 00 	andi $r0,$r16,#0x400
    142c:	4e 02 00 86 	beqz $r0,1538 <_ntoa_format+0x19c>
    1430:	04 0f 80 0d 	lwi $r0,[$sp+#0x34]
    1434:	5a 08 10 04 	bnec $r0,#0x10,143c <_ntoa_format+0xa0>
    1438:	48 00 00 a4 	j 1580 <_ntoa_format+0x1e4>
    143c:	04 0f 80 0d 	lwi $r0,[$sp+#0x34]
    1440:	5a 08 02 04 	bnec $r0,#0x2,1448 <_ntoa_format+0xac>
    1444:	48 00 00 b0 	j 15a4 <_ntoa_format+0x208>
    1448:	5c f2 80 20 	slti $r15,$r5,#0x20
    144c:	4e f2 00 8d 	beqz $r15,1566 <_ntoa_format+0x1ca>
    1450:	44 00 00 30 	movi $r0,#0x30
    1454:	9d a9       	addi333 $r6,$r5,#0x1
    1456:	38 03 94 08 	sb $r0,[$r7+($r5<<#0x0)]
    145a:	92 00       	nop16
    145c:	4c 66 00 54 	beq $r6,$r12,1504 <_ntoa_format+0x168>
    1460:	5c f3 00 20 	slti $r15,$r6,#0x20
    1464:	4e f3 00 c1 	bnez $r15,15e6 <_ntoa_format+0x24a>
    1468:	54 f8 00 03 	andi $r15,$r16,#0x3
    146c:	e9 49       	bnezs8 14fe <_ntoa_format+0x162>
    146e:	92 00       	nop16
    1470:	e2 cc       	slt45 $r6,$r12
    1472:	80 4d       	mov55 $r2,$r13
    1474:	40 e3 34 01 	sub $r14,$r6,$r13
    1478:	e8 12       	beqzs8 149c <_ntoa_format+0x100>
    147a:	92 00       	nop16
    147c:	50 b1 00 01 	addi $r11,$r2,#0x1
    1480:	fa 10       	movpi45 $r0,#0x20
    1482:	80 29       	mov55 $r1,$r9
    1484:	80 6a       	mov55 $r3,$r10
    1486:	dd 28       	jral5 $r8
    1488:	40 07 2c 00 	add $r0,$r14,$r11
    148c:	40 00 30 06 	slt $r0,$r0,$r12
    1490:	80 4b       	mov55 $r2,$r11
    1492:	c8 f5       	bnez38 $r0,147c <_ntoa_format+0xe0>
    1494:	40 56 b0 00 	add $r5,$r13,$r12
    1498:	9a ae       	sub333 $r2,$r5,$r6
    149a:	92 00       	nop16
    149c:	4e 62 00 90 	beqz $r6,15bc <_ntoa_format+0x220>
    14a0:	9f 71       	subi333 $r5,$r6,#0x1
    14a2:	88 e5       	add45 $r7,$r5
    14a4:	88 c2       	add45 $r6,$r2
    14a6:	92 00       	nop16
    14a8:	50 b1 00 01 	addi $r11,$r2,#0x1
    14ac:	28 03 ff ff 	lbsi.bi $r0,[$r7],#-1
    14b0:	80 29       	mov55 $r1,$r9
    14b2:	80 6a       	mov55 $r3,$r10
    14b4:	dd 28       	jral5 $r8
    14b6:	80 4b       	mov55 $r2,$r11
    14b8:	4c b3 7f f8 	bne $r11,$r6,14a8 <_ntoa_format+0x10c>
    14bc:	4f c2 00 12 	beqz $fp,14e0 <_ntoa_format+0x144>
    14c0:	40 03 34 01 	sub $r0,$r6,$r13
    14c4:	e2 0c       	slt45 $r0,$r12
    14c6:	e8 0d       	beqzs8 14e0 <_ntoa_format+0x144>
    14c8:	80 46       	mov55 $r2,$r6
    14ca:	8c c1       	addi45 $r6,#0x1
    14cc:	fa 10       	movpi45 $r0,#0x20
    14ce:	80 29       	mov55 $r1,$r9
    14d0:	80 6a       	mov55 $r3,$r10
    14d2:	dd 28       	jral5 $r8
    14d4:	40 43 34 01 	sub $r4,$r6,$r13
    14d8:	40 42 30 06 	slt $r4,$r4,$r12
    14dc:	80 46       	mov55 $r2,$r6
    14de:	cc f6       	bnez38 $r4,14ca <_ntoa_format+0x12e>
    14e0:	80 06       	mov55 $r0,$r6
    14e2:	ec 04       	addi10.sp #0x4
    14e4:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    14e8:	dd 9e       	ret5 $lp
    14ea:	92 00       	nop16
    14ec:	cd 3d       	bnez38 $r5,1566 <_ntoa_format+0x1ca>
    14ee:	c4 13       	beqz38 $r4,1514 <_ntoa_format+0x178>
    14f0:	fa 1d       	movpi45 $r0,#0x2d
    14f2:	54 f8 00 03 	andi $r15,$r16,#0x3
    14f6:	9d a9       	addi333 $r6,$r5,#0x1
    14f8:	38 03 94 08 	sb $r0,[$r7+($r5<<#0x0)]
    14fc:	e8 ba       	beqzs8 1470 <_ntoa_format+0xd4>
    14fe:	80 4d       	mov55 $r2,$r13
    1500:	d5 d0       	j8 14a0 <_ntoa_format+0x104>
    1502:	92 00       	nop16
    1504:	cc 4d       	bnez38 $r4,159e <_ntoa_format+0x202>
    1506:	54 08 00 0c 	andi $r0,$r16,#0xc
    150a:	c8 4a       	bnez38 $r0,159e <_ntoa_format+0x202>
    150c:	5c f3 00 20 	slti $r15,$r6,#0x20
    1510:	e8 f7       	beqzs8 14fe <_ntoa_format+0x162>
    1512:	80 ac       	mov55 $r5,$r12
    1514:	54 08 00 04 	andi $r0,$r16,#0x4
    1518:	c8 1e       	bnez38 $r0,1554 <_ntoa_format+0x1b8>
    151a:	54 08 00 08 	andi $r0,$r16,#0x8
    151e:	80 c5       	mov55 $r6,$r5
    1520:	c0 06       	beqz38 $r0,152c <_ntoa_format+0x190>
    1522:	fa 10       	movpi45 $r0,#0x20
    1524:	8c c1       	addi45 $r6,#0x1
    1526:	38 03 94 08 	sb $r0,[$r7+($r5<<#0x0)]
    152a:	92 00       	nop16
    152c:	54 f8 00 03 	andi $r15,$r16,#0x3
    1530:	80 4d       	mov55 $r2,$r13
    1532:	e9 b5       	bnezs8 149c <_ntoa_format+0x100>
    1534:	d5 9e       	j8 1470 <_ntoa_format+0xd4>
    1536:	92 00       	nop16
    1538:	4e 52 ff 7c 	beqz $r5,1430 <_ntoa_format+0x94>
    153c:	d2 03       	beqs38 $r2,1542 <_ntoa_format+0x1a6>
    153e:	4c 56 7f 79 	bne $r5,$r12,1430 <_ntoa_format+0x94>
    1542:	9e 29       	subi333 $r0,$r5,#0x1
    1544:	c0 47       	beqz38 $r0,15d2 <_ntoa_format+0x236>
    1546:	f1 0d       	lwi37.sp $r1,[+#0x34]
    1548:	8e a2       	subi45 $r5,#0x2
    154a:	5a 10 10 1b 	beqc $r1,#0x10,1580 <_ntoa_format+0x1e4>
    154e:	80 a0       	mov55 $r5,$r0
    1550:	48 ff ff 76 	j 143c <_ntoa_format+0xa0>
    1554:	fa 1b       	movpi45 $r0,#0x2b
    1556:	9d a9       	addi333 $r6,$r5,#0x1
    1558:	38 03 94 08 	sb $r0,[$r7+($r5<<#0x0)]
    155c:	d5 e8       	j8 152c <_ntoa_format+0x190>
    155e:	92 00       	nop16
    1560:	5c f2 80 20 	slti $r15,$r5,#0x20
    1564:	e9 30       	bnezs8 15c4 <_ntoa_format+0x228>
    1566:	80 c5       	mov55 $r6,$r5
    1568:	48 ff ff 7a 	j 145c <_ntoa_format+0xc0>
    156c:	54 08 00 10 	andi $r0,$r16,#0x10
    1570:	4e 02 ff 76 	beqz $r0,145c <_ntoa_format+0xc0>
    1574:	54 08 04 00 	andi $r0,$r16,#0x400
    1578:	fa b0       	movpi45 $r5,#0x20
    157a:	c0 e1       	beqz38 $r0,153c <_ntoa_format+0x1a0>
    157c:	48 ff ff 5a 	j 1430 <_ntoa_format+0x94>
    1580:	54 08 00 20 	andi $r0,$r16,#0x20
    1584:	c8 ee       	bnez38 $r0,1560 <_ntoa_format+0x1c4>
    1586:	5c f2 80 20 	slti $r15,$r5,#0x20
    158a:	80 c5       	mov55 $r6,$r5
    158c:	4e f2 ff 68 	beqz $r15,145c <_ntoa_format+0xc0>
    1590:	44 00 00 78 	movi $r0,#0x78
    1594:	38 03 94 08 	sb $r0,[$r7+($r5<<#0x0)]
    1598:	8c a1       	addi45 $r5,#0x1
    159a:	48 ff ff 57 	j 1448 <_ntoa_format+0xac>
    159e:	8e c1       	subi45 $r6,#0x1
    15a0:	48 ff ff 60 	j 1460 <_ntoa_format+0xc4>
    15a4:	5c f2 80 20 	slti $r15,$r5,#0x20
    15a8:	80 c5       	mov55 $r6,$r5
    15aa:	4e f2 ff 59 	beqz $r15,145c <_ntoa_format+0xc0>
    15ae:	44 00 00 62 	movi $r0,#0x62
    15b2:	38 03 94 08 	sb $r0,[$r7+($r5<<#0x0)]
    15b6:	8c a1       	addi45 $r5,#0x1
    15b8:	48 ff ff 48 	j 1448 <_ntoa_format+0xac>
    15bc:	80 c2       	mov55 $r6,$r2
    15be:	48 ff ff 7f 	j 14bc <_ntoa_format+0x120>
    15c2:	92 00       	nop16
    15c4:	44 00 00 58 	movi $r0,#0x58
    15c8:	38 03 94 08 	sb $r0,[$r7+($r5<<#0x0)]
    15cc:	8c a1       	addi45 $r5,#0x1
    15ce:	48 ff ff 3d 	j 1448 <_ntoa_format+0xac>
    15d2:	84 a0       	movi55 $r5,#0x0
    15d4:	48 ff ff 2e 	j 1430 <_ntoa_format+0x94>
    15d8:	54 08 00 10 	andi $r0,$r16,#0x10
    15dc:	4e 03 ff 26 	bnez $r0,1428 <_ntoa_format+0x8c>
    15e0:	80 c5       	mov55 $r6,$r5
    15e2:	48 ff ff 3d 	j 145c <_ntoa_format+0xc0>
    15e6:	80 a6       	mov55 $r5,$r6
    15e8:	c4 96       	beqz38 $r4,1514 <_ntoa_format+0x178>
    15ea:	d5 83       	j8 14f0 <_ntoa_format+0x154>

000015ec <_ntoa_long>:
    15ec:	3b ff fc bc 	smw.adm $sp,[$sp],$sp,#0x2    ! {$lp}
    15f0:	ef c4       	addi10.sp #-60
    15f2:	05 3f 80 10 	lwi $r19,[$sp+#0x40]
    15f6:	05 7f 80 13 	lwi $r23,[$sp+#0x4c]
    15fa:	cc 07       	bnez38 $r4,1608 <_ntoa_long+0x1c>
    15fc:	54 fb 84 00 	andi $r15,$r23,#0x400
    1600:	67 7b 80 10 	bitci $r23,$r23,#0x10
    1604:	4e f3 00 3a 	bnez $r15,1678 <_ntoa_long+0x8c>
    1608:	51 8f 80 18 	addi $r24,$sp,#0x18
    160c:	55 0b 80 20 	andi $r16,$r23,#0x20
    1610:	45 10 00 61 	movi $r17,#0x61
    1614:	45 60 00 41 	movi $r22,#0x41
    1618:	82 b8       	mov55 $r21,$r24
    161a:	86 80       	movi55 $r20,#0x0
    161c:	41 68 c0 1a 	cmovz $r22,$r17,$r16
    1620:	d5 04       	j8 1628 <_ntoa_long+0x3c>
    1622:	92 00       	nop16
    1624:	5b 40 20 19 	beqc $r20,#0x20,1656 <_ntoa_long+0x6a>
    1628:	41 12 4e 17 	divr $r17,$r16,$r4,$r19
    162c:	41 28 00 10 	seb $r18,$r16
    1630:	51 18 7f f6 	addi $r17,$r16,#-10
    1634:	e5 ca       	sltsi45 $r18,#0xa
    1636:	51 08 00 30 	addi $r16,$r16,#0x30
    163a:	89 b6       	add45 $r17,$r22
    163c:	51 4a 00 01 	addi $r20,$r20,#0x1
    1640:	41 08 00 10 	seb $r16,$r16
    1644:	4e f3 00 04 	bnez $r15,164c <_ntoa_long+0x60>
    1648:	41 08 80 10 	seb $r16,$r17
    164c:	40 42 4c 97 	divr $r4,$r4,$r4,$r19
    1650:	19 0a 80 01 	sbi.bi $r16,[$r21],#0x1
    1654:	cc e8       	bnez38 $r4,1624 <_ntoa_long+0x38>
    1656:	f4 11       	lwi37.sp $r4,[+#0x44]
    1658:	f4 82       	swi37.sp $r4,[+#0x8]
    165a:	f4 12       	lwi37.sp $r4,[+#0x48]
    165c:	b6 bf       	swi450 $r5,[$sp]
    165e:	f4 83       	swi37.sp $r4,[+#0xc]
    1660:	15 3f 80 01 	swi $r19,[$sp+#0x4]
    1664:	15 7f 80 04 	swi $r23,[$sp+#0x10]
    1668:	80 98       	mov55 $r4,$r24
    166a:	80 b4       	mov55 $r5,$r20
    166c:	49 ff fe 98 	jal 139c <_ntoa_format>
    1670:	ec 3c       	addi10.sp #0x3c
    1672:	3b ff fc 84 	lmw.bim $sp,[$sp],$sp,#0x2    ! {$lp}
    1676:	dd 9e       	ret5 $lp
    1678:	86 80       	movi55 $r20,#0x0
    167a:	51 8f 80 18 	addi $r24,$sp,#0x18
    167e:	d5 ec       	j8 1656 <_ntoa_long+0x6a>

00001680 <_ntoa_long_long>:
    1680:	3a 6f ba bc 	smw.adm $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    1684:	ef b4       	addi10.sp #-76
    1686:	36 3f 80 0e 	fsdi $fd3,[$sp+#0x38]
    168a:	36 4f 80 10 	fsdi $fd4,[$sp+#0x40]
    168e:	fd 52       	movd44 $r10,$r4
    1690:	80 a4       	mov55 $r5,$r4
    1692:	80 8b       	mov55 $r4,$r11
    1694:	ff 2f       	or33 $r4,$r5
    1696:	6a 04 00 09 	fmtsr $r0,$fs8
    169a:	6a 13 80 09 	fmtsr $r1,$fs7
    169e:	6a 23 00 09 	fmtsr $r2,$fs6
    16a2:	83 83       	mov55 $fp,$r3
    16a4:	f6 20       	lwi37.sp $r6,[+#0x80]
    16a6:	f7 21       	lwi37.sp $r7,[+#0x84]
    16a8:	04 8f 80 24 	lwi $r8,[$sp+#0x90]
    16ac:	cc 06       	bnez38 $r4,16b8 <_ntoa_long_long+0x38>
    16ae:	54 04 04 00 	andi $r0,$r8,#0x400
    16b2:	66 84 00 10 	bitci $r8,$r8,#0x10
    16b6:	c8 4d       	bnez38 $r0,1750 <_ntoa_long_long+0xd0>
    16b8:	50 ef 80 18 	addi $r14,$sp,#0x18
    16bc:	54 54 00 20 	andi $r5,$r8,#0x20
    16c0:	44 00 00 61 	movi $r0,#0x61
    16c4:	44 d0 00 41 	movi $r13,#0x41
    16c8:	81 8e       	mov55 $r12,$r14
    16ca:	85 20       	movi55 $r9,#0x0
    16cc:	40 d0 14 1a 	cmovz $r13,$r0,$r5
    16d0:	d5 04       	j8 16d8 <_ntoa_long_long+0x58>
    16d2:	92 00       	nop16
    16d4:	5a 90 20 20 	beqc $r9,#0x20,1714 <_ntoa_long_long+0x94>
    16d8:	fd 05       	movd44 $r0,$r10
    16da:	fd 13       	movd44 $r2,$r6
    16dc:	49 00 3b 16 	jal 8d08 <__umoddi3>
    16e0:	41 20 00 10 	seb $r18,$r0
    16e4:	51 10 7f f6 	addi $r17,$r0,#-10
    16e8:	51 00 00 30 	addi $r16,$r0,#0x30
    16ec:	5e 09 00 0a 	sltsi $r0,$r18,#0xa
    16f0:	89 ad       	add45 $r17,$r13
    16f2:	8d 21       	addi45 $r9,#0x1
    16f4:	41 08 00 10 	seb $r16,$r16
    16f8:	c8 03       	bnez38 $r0,16fe <_ntoa_long_long+0x7e>
    16fa:	41 08 80 10 	seb $r16,$r17
    16fe:	fd 05       	movd44 $r0,$r10
    1700:	19 06 00 01 	sbi.bi $r16,[$r12],#0x1
    1704:	fd 13       	movd44 $r2,$r6
    1706:	49 00 3a 27 	jal 8b54 <__udivdi3>
    170a:	fd 50       	movd44 $r10,$r0
    170c:	40 00 2c 04 	or $r0,$r0,$r11
    1710:	c8 e2       	bnez38 $r0,16d4 <_ntoa_long_long+0x54>
    1712:	92 00       	nop16
    1714:	00 0f 80 78 	lbi $r0,[$sp+#0x78]
    1718:	b6 1f       	swi450 $r0,[$sp]
    171a:	f0 22       	lwi37.sp $r0,[+#0x88]
    171c:	f0 82       	swi37.sp $r0,[+#0x8]
    171e:	f0 23       	lwi37.sp $r0,[+#0x8c]
    1720:	f0 83       	swi37.sp $r0,[+#0xc]
    1722:	6a 13 80 01 	fmfsr $r1,$fs7
    1726:	6a 04 00 01 	fmfsr $r0,$fs8
    172a:	6a 23 00 01 	fmfsr $r2,$fs6
    172e:	f6 81       	swi37.sp $r6,[+#0x4]
    1730:	14 8f 80 04 	swi $r8,[$sp+#0x10]
    1734:	80 7c       	mov55 $r3,$fp
    1736:	80 8e       	mov55 $r4,$r14
    1738:	50 54 80 00 	addi $r5,$r9,#0x0
    173c:	49 ff fe 30 	jal 139c <_ntoa_format>
    1740:	ec 38       	addi10.sp #0x38
    1742:	34 3f 90 02 	fldi.bi $fd3,[$sp],#0x8
    1746:	34 4f 90 03 	fldi.bi $fd4,[$sp],#0xc
    174a:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    174e:	dd 9e       	ret5 $lp
    1750:	85 20       	movi55 $r9,#0x0
    1752:	50 ef 80 18 	addi $r14,$sp,#0x18
    1756:	d5 df       	j8 1714 <_ntoa_long_long+0x94>

00001758 <_out_char>:
    1758:	c0 0c       	beqz38 $r0,1770 <_out_char+0x18>
    175a:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    175e:	80 c0       	mov55 $r6,$r0
    1760:	5a 00 0a 09 	beqc $r0,#0xa,1772 <_out_char+0x1a>
    1764:	80 06       	mov55 $r0,$r6
    1766:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    176a:	48 ff fb 7b 	j e60 <drv_uart_tx_0>
    176e:	92 00       	nop16
    1770:	dd 9e       	ret5 $lp
    1772:	84 0d       	movi55 $r0,#0xd
    1774:	49 ff fb 76 	jal e60 <drv_uart_tx_0>
    1778:	d5 f6       	j8 1764 <_out_char+0xc>
    177a:	92 00       	nop16

0000177c <_vsnprintf>:
    177c:	3a 6f ba bc 	smw.adm $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    1780:	ef 5c       	addi10.sp #-164
    1782:	36 3f 80 1a 	fsdi $fd3,[$sp+#0x68]
    1786:	36 4f 80 1c 	fsdi $fd4,[$sp+#0x70]
    178a:	36 5f 80 1e 	fsdi $fd5,[$sp+#0x78]
    178e:	36 6f 80 20 	fsdi $fd6,[$sp+#0x80]
    1792:	36 7f 80 22 	fsdi $fd7,[$sp+#0x88]
    1796:	36 8f 80 24 	fsdi $fd8,[$sp+#0x90]
    179a:	36 9f 80 26 	fsdi $fd9,[$sp+#0x98]
    179e:	44 70 13 98 	movi $r7,#0x1398
    17a2:	40 70 04 1b 	cmovn $r7,$r0,$r1
    17a6:	46 06 66 66 	sethi $r0,#0x66666
    17aa:	50 00 06 67 	addi $r0,$r0,#0x667
    17ae:	6a 08 00 09 	fmtsr $r0,$fs16
    17b2:	46 0c cc cc 	sethi $r0,#0xccccc
    17b6:	50 00 0c cd 	addi $r0,$r0,#0xccd
    17ba:	6a 03 80 09 	fmtsr $r0,$fs7
    17be:	81 c1       	mov55 $r14,$r1
    17c0:	80 c2       	mov55 $r6,$r2
    17c2:	81 a3       	mov55 $r13,$r3
    17c4:	83 84       	mov55 $fp,$r4
    17c6:	85 40       	movi55 $r10,#0x0
    17c8:	20 06 80 00 	lbsi $r0,[$r13+#0x0]
    17cc:	4e 02 00 10 	beqz $r0,17ec <_vsnprintf+0x70>
    17d0:	5a 00 25 2a 	beqc $r0,#0x25,1824 <_vsnprintf+0xa8>
    17d4:	80 4a       	mov55 $r2,$r10
    17d6:	80 2e       	mov55 $r1,$r14
    17d8:	80 66       	mov55 $r3,$r6
    17da:	50 d6 80 01 	addi $r13,$r13,#0x1
    17de:	dd 27       	jral5 $r7
    17e0:	20 06 80 00 	lbsi $r0,[$r13+#0x0]
    17e4:	50 85 00 01 	addi $r8,$r10,#0x1
    17e8:	81 48       	mov55 $r10,$r8
    17ea:	c8 f3       	bnez38 $r0,17d0 <_vsnprintf+0x54>
    17ec:	e3 46       	slt45 $r10,$r6
    17ee:	9e b1       	subi333 $r2,$r6,#0x1
    17f0:	40 25 3c 1b 	cmovn $r2,$r10,$r15
    17f4:	84 00       	movi55 $r0,#0x0
    17f6:	80 2e       	mov55 $r1,$r14
    17f8:	80 66       	mov55 $r3,$r6
    17fa:	dd 27       	jral5 $r7
    17fc:	80 0a       	mov55 $r0,$r10
    17fe:	ec 68       	addi10.sp #0x68
    1800:	34 3f 90 02 	fldi.bi $fd3,[$sp],#0x8
    1804:	34 4f 90 02 	fldi.bi $fd4,[$sp],#0x8
    1808:	34 5f 90 02 	fldi.bi $fd5,[$sp],#0x8
    180c:	34 6f 90 02 	fldi.bi $fd6,[$sp],#0x8
    1810:	34 7f 90 02 	fldi.bi $fd7,[$sp],#0x8
    1814:	34 8f 90 02 	fldi.bi $fd8,[$sp],#0x8
    1818:	34 9f 90 03 	fldi.bi $fd9,[$sp],#0xc
    181c:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    1820:	dd 9e       	ret5 $lp
    1822:	92 00       	nop16
    1824:	50 16 80 01 	addi $r1,$r13,#0x1
    1828:	85 a0       	movi55 $r13,#0x0
    182a:	81 01       	mov55 $r8,$r1
    182c:	28 20 80 01 	lbsi.bi $r2,[$r1],#0x1
    1830:	50 31 7f e0 	addi $r3,$r2,#-32
    1834:	5c f1 80 11 	slti $r15,$r3,#0x11
    1838:	4e f3 01 3c 	bnez $r15,1ab0 <_vsnprintf+0x334>
    183c:	50 01 7f d0 	addi $r0,$r2,#-48
    1840:	96 00       	zeb33 $r0,$r0
    1842:	e6 0a       	slti45 $r0,#0xa
    1844:	80 68       	mov55 $r3,$r8
    1846:	80 02       	mov55 $r0,$r2
    1848:	4e f2 01 70 	beqz $r15,1b28 <_vsnprintf+0x3ac>
    184c:	50 24 00 01 	addi $r2,$r8,#0x1
    1850:	85 20       	movi55 $r9,#0x0
    1852:	84 aa       	movi55 $r5,#0xa
    1854:	42 04 94 73 	maddr32 $r0,$r9,$r5
    1858:	81 02       	mov55 $r8,$r2
    185a:	80 60       	mov55 $r3,$r0
    185c:	20 01 00 00 	lbsi $r0,[$r2+#0x0]
    1860:	50 91 ff d0 	addi $r9,$r3,#-48
    1864:	50 10 7f d0 	addi $r1,$r0,#-48
    1868:	96 48       	zeb33 $r1,$r1
    186a:	e6 2a       	slti45 $r1,#0xa
    186c:	8c 41       	addi45 $r2,#0x1
    186e:	e9 f3       	bnezs8 1854 <_vsnprintf+0xd8>
    1870:	44 b0 00 00 	movi $r11,#0x0
    1874:	5a 08 2e 04 	bnec $r0,#0x2e,187c <_vsnprintf+0x100>
    1878:	48 00 01 64 	j 1b40 <_vsnprintf+0x3c4>
    187c:	50 10 7f 98 	addi $r1,$r0,#-104
    1880:	e6 33       	slti45 $r1,#0x13
    1882:	e8 33       	beqzs8 18e8 <_vsnprintf+0x16c>
    1884:	44 f0 18 90 	movi $r15,#0x1890
    1888:	38 17 86 02 	lw $r1,[$r15+($r1<<#0x2)]
    188c:	4a 00 04 00 	jr $r1
    1890:	7c 1a 00 00 	*unknown*
    1894:	e8 18       	beqzs8 18c4 <_vsnprintf+0x148>
    1896:	00 00 0c 19 	lbi $r0,[$r0+#0xc19]
    189a:	00 00 e8 18 	lbi $r0,[$r1+#-6120]
    189e:	00 00 94 1a 	lbi $r0,[$r1+#0x141a]
    18a2:	00 00 e8 18 	lbi $r0,[$r1+#-6120]
    18a6:	00 00 e8 18 	lbi $r0,[$r1+#-6120]
    18aa:	00 00 e8 18 	lbi $r0,[$r1+#-6120]
    18ae:	00 00 e8 18 	lbi $r0,[$r1+#-6120]
    18b2:	00 00 e8 18 	lbi $r0,[$r1+#-6120]
    18b6:	00 00 e8 18 	lbi $r0,[$r1+#-6120]
    18ba:	00 00 e8 18 	lbi $r0,[$r1+#-6120]
    18be:	00 00 dc 18 	lbi $r0,[$r1+#-9192]
    18c2:	00 00 e8 18 	lbi $r0,[$r1+#-6120]
    18c6:	00 00 e8 18 	lbi $r0,[$r1+#-6120]
    18ca:	00 00 e8 18 	lbi $r0,[$r1+#-6120]
    18ce:	00 00 e8 18 	lbi $r0,[$r1+#-6120]
    18d2:	00 00 e8 18 	lbi $r0,[$r1+#-6120]
    18d6:	00 00 dc 18 	lbi $r0,[$r1+#-9192]
    18da:	00 00 20 04 	lbi $r0,[$r0+#0x2004]
    18de:	00 01 58 d6 	lbi $r0,[$r2+#-10026]
    18e2:	81 00       	mov55 $r8,$r0
    18e4:	8d 01       	addi45 $r8,#0x1
    18e6:	92 00       	nop16
    18e8:	50 10 7f db 	addi $r1,$r0,#-37
    18ec:	5c f0 80 54 	slti $r15,$r1,#0x54
    18f0:	e9 18       	bnezs8 1920 <_vsnprintf+0x1a4>
    18f2:	80 4a       	mov55 $r2,$r10
    18f4:	50 95 00 01 	addi $r9,$r10,#0x1
    18f8:	80 2e       	mov55 $r1,$r14
    18fa:	80 66       	mov55 $r3,$r6
    18fc:	4b e0 1c 01 	jral $lp,$r7
    1900:	50 d4 00 01 	addi $r13,$r8,#0x1
    1904:	81 49       	mov55 $r10,$r9
    1906:	48 ff ff 61 	j 17c8 <_vsnprintf+0x4c>
    190a:	92 00       	nop16
    190c:	20 04 00 01 	lbsi $r0,[$r8+#0x1]
    1910:	58 d6 82 00 	ori $r13,$r13,#0x200
    1914:	50 10 7f db 	addi $r1,$r0,#-37
    1918:	5c f0 80 54 	slti $r15,$r1,#0x54
    191c:	8d 01       	addi45 $r8,#0x1
    191e:	e8 ea       	beqzs8 18f2 <_vsnprintf+0x176>
    1920:	44 f0 19 2c 	movi $r15,#0x192c
    1924:	38 17 86 02 	lw $r1,[$r15+($r1<<#0x2)]
    1928:	4a 00 04 00 	jr $r1
    192c:	b0 1d       	addri36.sp $r0,#0x74
    192e:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    1932:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    1936:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    193a:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    193e:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    1942:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    1946:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    194a:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    194e:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    1952:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    1956:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    195a:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    195e:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    1962:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    1966:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    196a:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    196e:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    1972:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    1976:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    197a:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    197e:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    1982:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    1986:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    198a:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    198e:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    1992:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    1996:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    199a:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    199e:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    19a2:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    19a6:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    19aa:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    19ae:	00 00 44 1d 	lbi $r0,[$r0+#-15331]
    19b2:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    19b6:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    19ba:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    19be:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    19c2:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    19c6:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    19ca:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    19ce:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    19d2:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    19d6:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    19da:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    19de:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    19e2:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    19e6:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    19ea:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    19ee:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    19f2:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    19f6:	00 00 c8 1c 	lbi $r0,[$r1+#-14308]
    19fa:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    19fe:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    1a02:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    1a06:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    1a0a:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    1a0e:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    1a12:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    1a16:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    1a1a:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    1a1e:	00 00 c8 1c 	lbi $r0,[$r1+#-14308]
    1a22:	00 00 88 1c 	lbi $r0,[$r1+#0x81c]
    1a26:	00 00 c8 1c 	lbi $r0,[$r1+#-14308]
    1a2a:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    1a2e:	00 00 44 1d 	lbi $r0,[$r0+#-15331]
    1a32:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    1a36:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    1a3a:	00 00 c8 1c 	lbi $r0,[$r1+#-14308]
    1a3e:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    1a42:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    1a46:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    1a4a:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    1a4e:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    1a52:	00 00 c8 1c 	lbi $r0,[$r1+#-14308]
    1a56:	00 00 58 1c 	lbi $r0,[$r0+#-10212]
    1a5a:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    1a5e:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    1a62:	00 00 80 1b 	lbi $r0,[$r1+#0x1b]
    1a66:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    1a6a:	00 00 c8 1c 	lbi $r0,[$r1+#-14308]
    1a6e:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    1a72:	00 00 f2 18 	lbi $r0,[$r1+#-3560]
    1a76:	00 00 c8 1c 	lbi $r0,[$r1+#-14308]
    1a7a:	00 00 20 04 	lbi $r0,[$r0+#0x2004]
    1a7e:	00 01 5a 08 	lbi $r0,[$r2+#-9720]
    1a82:	68 04 48 00 	*unknown*
    1a86:	03 16 58 d6 	lhi $r17,[$r12+#-20052]
    1a8a:	80 80       	mov55 $r4,$r0
    1a8c:	8d 01       	addi45 $r8,#0x1
    1a8e:	48 ff ff 2d 	j 18e8 <_vsnprintf+0x16c>
    1a92:	92 00       	nop16
    1a94:	20 04 00 01 	lbsi $r0,[$r8+#0x1]
    1a98:	5a 00 6c 04 	beqc $r0,#0x6c,1aa0 <_vsnprintf+0x324>
    1a9c:	48 ff ff 22 	j 18e0 <_vsnprintf+0x164>
    1aa0:	20 04 00 02 	lbsi $r0,[$r8+#0x2]
    1aa4:	58 d6 83 00 	ori $r13,$r13,#0x300
    1aa8:	8d 02       	addi45 $r8,#0x2
    1aaa:	48 ff ff 1f 	j 18e8 <_vsnprintf+0x16c>
    1aae:	92 00       	nop16
    1ab0:	44 f0 1a bc 	movi $r15,#0x1abc
    1ab4:	38 37 8e 02 	lw $r3,[$r15+($r3<<#0x2)]
    1ab8:	4a 00 0c 00 	jr $r3
    1abc:	20 1b 00 00 	lbsi $r1,[$r22+#0x0]
    1ac0:	3c 18 00 00 	shi.gp $r1,[+#0x0]
    1ac4:	3c 18 00 00 	shi.gp $r1,[+#0x0]
    1ac8:	18 1b 00 00 	sbi.bi $r1,[$r22],#0x0
    1acc:	3c 18 00 00 	shi.gp $r1,[+#0x0]
    1ad0:	3c 18 00 00 	shi.gp $r1,[+#0x0]
    1ad4:	3c 18 00 00 	shi.gp $r1,[+#0x0]
    1ad8:	3c 18 00 00 	shi.gp $r1,[+#0x0]
    1adc:	3c 18 00 00 	shi.gp $r1,[+#0x0]
    1ae0:	3c 18 00 00 	shi.gp $r1,[+#0x0]
    1ae4:	3c 18 00 00 	shi.gp $r1,[+#0x0]
    1ae8:	10 1b 00 00 	sbi $r1,[$r22+#0x0]
    1aec:	3c 18 00 00 	shi.gp $r1,[+#0x0]
    1af0:	08 1b 00 00 	lbi.bi $r1,[$r22],#0x0
    1af4:	3c 18 00 00 	shi.gp $r1,[+#0x0]
    1af8:	3c 18 00 00 	shi.gp $r1,[+#0x0]
    1afc:	00 1b 00 00 	lbi $r1,[$r22+#0x0]
    1b00:	58 d6 80 01 	ori $r13,$r13,#0x1
    1b04:	48 ff fe 93 	j 182a <_vsnprintf+0xae>
    1b08:	58 d6 80 02 	ori $r13,$r13,#0x2
    1b0c:	48 ff fe 8f 	j 182a <_vsnprintf+0xae>
    1b10:	58 d6 80 04 	ori $r13,$r13,#0x4
    1b14:	48 ff fe 8b 	j 182a <_vsnprintf+0xae>
    1b18:	58 d6 80 10 	ori $r13,$r13,#0x10
    1b1c:	48 ff fe 87 	j 182a <_vsnprintf+0xae>
    1b20:	58 d6 80 08 	ori $r13,$r13,#0x8
    1b24:	48 ff fe 83 	j 182a <_vsnprintf+0xae>
    1b28:	5a 28 2a 04 	bnec $r2,#0x2a,1b30 <_vsnprintf+0x3b4>
    1b2c:	48 00 01 48 	j 1dbc <_vsnprintf+0x640>
    1b30:	80 02       	mov55 $r0,$r2
    1b32:	85 20       	movi55 $r9,#0x0
    1b34:	44 b0 00 00 	movi $r11,#0x0
    1b38:	5a 20 2e 04 	beqc $r2,#0x2e,1b40 <_vsnprintf+0x3c4>
    1b3c:	48 ff fe a0 	j 187c <_vsnprintf+0x100>
    1b40:	20 04 00 01 	lbsi $r0,[$r8+#0x1]
    1b44:	58 d6 84 00 	ori $r13,$r13,#0x400
    1b48:	50 10 7f d0 	addi $r1,$r0,#-48
    1b4c:	96 48       	zeb33 $r1,$r1
    1b4e:	e6 2a       	slti45 $r1,#0xa
    1b50:	50 24 00 01 	addi $r2,$r8,#0x1
    1b54:	4e f2 01 3e 	beqz $r15,1dd0 <_vsnprintf+0x654>
    1b58:	50 24 00 02 	addi $r2,$r8,#0x2
    1b5c:	84 6a       	movi55 $r3,#0xa
    1b5e:	92 00       	nop16
    1b60:	42 05 8c 73 	maddr32 $r0,$r11,$r3
    1b64:	81 02       	mov55 $r8,$r2
    1b66:	82 20       	mov55 $r17,$r0
    1b68:	20 01 00 00 	lbsi $r0,[$r2+#0x0]
    1b6c:	50 b8 ff d0 	addi $r11,$r17,#-48
    1b70:	50 10 7f d0 	addi $r1,$r0,#-48
    1b74:	96 48       	zeb33 $r1,$r1
    1b76:	e6 2a       	slti45 $r1,#0xa
    1b78:	8c 41       	addi45 $r2,#0x1
    1b7a:	e9 f3       	bnezs8 1b60 <_vsnprintf+0x3e4>
    1b7c:	48 ff fe 80 	j 187c <_vsnprintf+0x100>
    1b80:	30 8e 00 00 	flsi $fs8,[$fp+#0x0]
    1b84:	50 0e 00 04 	addi $r0,$fp,#0x4
    1b88:	6a 04 80 09 	fmtsr $r0,$fs9
    1b8c:	6a 04 00 01 	fmfsr $r0,$fs8
    1b90:	20 00 00 00 	lbsi $r0,[$r0+#0x0]
    1b94:	4e 02 04 0f 	beqz $r0,23b2 <_vsnprintf+0xc36>
    1b98:	6a 14 00 01 	fmfsr $r1,$fs8
    1b9c:	8c 21       	addi45 $r1,#0x1
    1b9e:	92 00       	nop16
    1ba0:	20 30 80 00 	lbsi $r3,[$r1+#0x0]
    1ba4:	80 41       	mov55 $r2,$r1
    1ba6:	8c 21       	addi45 $r1,#0x1
    1ba8:	cb fc       	bnez38 $r3,1ba0 <_vsnprintf+0x424>
    1baa:	6a 14 00 01 	fmfsr $r1,$fs8
    1bae:	9a 51       	sub333 $r1,$r2,$r1
    1bb0:	6a 15 00 09 	fmtsr $r1,$fs10
    1bb4:	54 c6 84 00 	andi $r12,$r13,#0x400
    1bb8:	4e c2 00 0c 	beqz $r12,1bd0 <_vsnprintf+0x454>
    1bbc:	6a 15 00 01 	fmfsr $r1,$fs10
    1bc0:	6a 25 00 01 	fmfsr $r2,$fs10
    1bc4:	e3 61       	slt45 $r11,$r1
    1bc6:	40 25 bc 1b 	cmovn $r2,$r11,$r15
    1bca:	6a 25 00 09 	fmtsr $r2,$fs10
    1bce:	92 00       	nop16
    1bd0:	54 16 80 02 	andi $r1,$r13,#0x2
    1bd4:	6a 13 00 09 	fmtsr $r1,$fs6
    1bd8:	4e 12 01 22 	beqz $r1,1e1c <_vsnprintf+0x6a0>
    1bdc:	c0 1c       	beqz38 $r0,1c14 <_vsnprintf+0x498>
    1bde:	92 00       	nop16
    1be0:	6a 14 00 01 	fmfsr $r1,$fs8
    1be4:	80 4a       	mov55 $r2,$r10
    1be6:	51 c0 80 01 	addi $fp,$r1,#0x1
    1bea:	d5 02       	j8 1bee <_vsnprintf+0x472>
    1bec:	80 4a       	mov55 $r2,$r10
    1bee:	80 2e       	mov55 $r1,$r14
    1bf0:	80 66       	mov55 $r3,$r6
    1bf2:	4e c2 00 07 	beqz $r12,1c00 <_vsnprintf+0x484>
    1bf6:	50 45 ff ff 	addi $r4,$r11,#-1
    1bfa:	4e b2 00 09 	beqz $r11,1c0c <_vsnprintf+0x490>
    1bfe:	81 64       	mov55 $r11,$r4
    1c00:	4b e0 1c 01 	jral $lp,$r7
    1c04:	28 0e 00 01 	lbsi.bi $r0,[$fp],#0x1
    1c08:	8d 41       	addi45 $r10,#0x1
    1c0a:	c8 f1       	bnez38 $r0,1bec <_vsnprintf+0x470>
    1c0c:	6a 03 00 01 	fmfsr $r0,$fs6
    1c10:	4e 02 00 1e 	beqz $r0,1c4c <_vsnprintf+0x4d0>
    1c14:	6a 05 00 01 	fmfsr $r0,$fs10
    1c18:	e2 09       	slt45 $r0,$r9
    1c1a:	e8 19       	beqzs8 1c4c <_vsnprintf+0x4d0>
    1c1c:	6a 05 00 01 	fmfsr $r0,$fs10
    1c20:	80 4a       	mov55 $r2,$r10
    1c22:	41 c0 28 01 	sub $fp,$r0,$r10
    1c26:	92 00       	nop16
    1c28:	50 b1 00 01 	addi $r11,$r2,#0x1
    1c2c:	fa 10       	movpi45 $r0,#0x20
    1c2e:	80 2e       	mov55 $r1,$r14
    1c30:	80 66       	mov55 $r3,$r6
    1c32:	dd 27       	jral5 $r7
    1c34:	40 0e 2c 00 	add $r0,$fp,$r11
    1c38:	40 00 24 06 	slt $r0,$r0,$r9
    1c3c:	80 4b       	mov55 $r2,$r11
    1c3e:	c8 f5       	bnez38 $r0,1c28 <_vsnprintf+0x4ac>
    1c40:	6a 15 00 01 	fmfsr $r1,$fs10
    1c44:	40 05 24 00 	add $r0,$r10,$r9
    1c48:	40 a0 04 01 	sub $r10,$r0,$r1
    1c4c:	50 d4 00 01 	addi $r13,$r8,#0x1
    1c50:	6b c4 80 01 	fmfsr $fp,$fs9
    1c54:	48 ff fd ba 	j 17c8 <_vsnprintf+0x4c>
    1c58:	fa 00       	movpi45 $r0,#0x10
    1c5a:	58 46 80 21 	ori $r4,$r13,#0x21
    1c5e:	b6 1f       	swi450 $r0,[$sp]
    1c60:	84 08       	movi55 $r0,#0x8
    1c62:	14 bf 80 01 	swi $r11,[$sp+#0x4]
    1c66:	f0 82       	swi37.sp $r0,[+#0x8]
    1c68:	f4 83       	swi37.sp $r4,[+#0xc]
    1c6a:	b4 9c       	lwi450 $r4,[$fp]
    1c6c:	51 ce 00 04 	addi $fp,$fp,#0x4
    1c70:	80 4a       	mov55 $r2,$r10
    1c72:	80 07       	mov55 $r0,$r7
    1c74:	80 2e       	mov55 $r1,$r14
    1c76:	80 66       	mov55 $r3,$r6
    1c78:	84 a0       	movi55 $r5,#0x0
    1c7a:	49 ff fc b9 	jal 15ec <_ntoa_long>
    1c7e:	81 40       	mov55 $r10,$r0
    1c80:	50 d4 00 01 	addi $r13,$r8,#0x1
    1c84:	48 ff fd a2 	j 17c8 <_vsnprintf+0x4c>
    1c88:	54 46 80 02 	andi $r4,$r13,#0x2
    1c8c:	4e 43 00 aa 	bnez $r4,1de0 <_vsnprintf+0x664>
    1c90:	e7 22       	slti45 $r9,#0x2
    1c92:	4e f3 03 cb 	bnez $r15,2428 <_vsnprintf+0xcac>
    1c96:	50 05 7f ff 	addi $r0,$r10,#-1
    1c9a:	89 20       	add45 $r9,$r0
    1c9c:	50 45 00 01 	addi $r4,$r10,#0x1
    1ca0:	80 4a       	mov55 $r2,$r10
    1ca2:	fa 10       	movpi45 $r0,#0x20
    1ca4:	81 44       	mov55 $r10,$r4
    1ca6:	80 2e       	mov55 $r1,$r14
    1ca8:	80 66       	mov55 $r3,$r6
    1caa:	dd 27       	jral5 $r7
    1cac:	4c a4 ff f8 	bne $r10,$r9,1c9c <_vsnprintf+0x520>
    1cb0:	20 0e 00 00 	lbsi $r0,[$fp+#0x0]
    1cb4:	80 2e       	mov55 $r1,$r14
    1cb6:	80 49       	mov55 $r2,$r9
    1cb8:	80 66       	mov55 $r3,$r6
    1cba:	51 ce 00 04 	addi $fp,$fp,#0x4
    1cbe:	50 a4 80 01 	addi $r10,$r9,#0x1
    1cc2:	dd 27       	jral5 $r7
    1cc4:	d5 de       	j8 1c80 <_vsnprintf+0x504>
    1cc6:	92 00       	nop16
    1cc8:	5a 08 78 04 	bnec $r0,#0x78,1cd0 <_vsnprintf+0x554>
    1ccc:	48 00 02 56 	j 2178 <_vsnprintf+0x9fc>
    1cd0:	5a 08 58 04 	bnec $r0,#0x58,1cd8 <_vsnprintf+0x55c>
    1cd4:	48 00 02 8a 	j 21e8 <_vsnprintf+0xa6c>
    1cd8:	5a 08 6f 04 	bnec $r0,#0x6f,1ce0 <_vsnprintf+0x564>
    1cdc:	48 00 03 27 	j 232a <_vsnprintf+0xbae>
    1ce0:	5a 08 62 04 	bnec $r0,#0x62,1ce8 <_vsnprintf+0x56c>
    1ce4:	48 00 02 ad 	j 223e <_vsnprintf+0xac2>
    1ce8:	66 16 80 10 	bitci $r1,$r13,#0x10
    1cec:	44 20 00 0a 	movi $r2,#0xa
    1cf0:	5a 00 69 04 	beqc $r0,#0x69,1cf8 <_vsnprintf+0x57c>
    1cf4:	48 00 02 69 	j 21c6 <_vsnprintf+0xa4a>
    1cf8:	54 46 84 00 	andi $r4,$r13,#0x400
    1cfc:	4e 43 02 6c 	bnez $r4,21d4 <_vsnprintf+0xa58>
    1d00:	54 00 82 00 	andi $r0,$r1,#0x200
    1d04:	4e 03 03 16 	bnez $r0,2330 <_vsnprintf+0xbb4>
    1d08:	54 00 81 00 	andi $r0,$r1,#0x100
    1d0c:	4e 03 02 94 	bnez $r0,2234 <_vsnprintf+0xab8>
    1d10:	54 00 80 40 	andi $r0,$r1,#0x40
    1d14:	4e 02 02 8c 	beqz $r0,222c <_vsnprintf+0xab0>
    1d18:	20 5e 00 00 	lbsi $r5,[$fp+#0x0]
    1d1c:	51 ce 00 04 	addi $fp,$fp,#0x4
    1d20:	b6 5f       	swi450 $r2,[$sp]
    1d22:	f1 83       	swi37.sp $r1,[+#0xc]
    1d24:	80 4a       	mov55 $r2,$r10
    1d26:	42 42 80 03 	abs $r4,$r5
    1d2a:	14 bf 80 01 	swi $r11,[$sp+#0x4]
    1d2e:	14 9f 80 02 	swi $r9,[$sp+#0x8]
    1d32:	80 07       	mov55 $r0,$r7
    1d34:	80 2e       	mov55 $r1,$r14
    1d36:	80 66       	mov55 $r3,$r6
    1d38:	92 bf       	srli45 $r5,#0x1f
    1d3a:	49 ff fc 59 	jal 15ec <_ntoa_long>
    1d3e:	81 40       	mov55 $r10,$r0
    1d40:	d5 a0       	j8 1c80 <_vsnprintf+0x504>
    1d42:	92 00       	nop16
    1d44:	51 ce 00 07 	addi $fp,$fp,#0x7
    1d48:	67 ce 00 07 	bitci $fp,$fp,#0x7
    1d4c:	44 00 24 a8 	movi $r0,#0x24a8
    1d50:	34 4e 00 00 	fldi $fd4,[$fp+#0x0]
    1d54:	34 50 00 00 	fldi $fd5,[$r0+#0x0]
    1d58:	51 ce 00 08 	addi $fp,$fp,#0x8
    1d5c:	6a 02 10 c8 	fcpysd $fd0,$fd4,$fd4
    1d60:	6a 12 94 c8 	fcpysd $fd1,$fd5,$fd5
    1d64:	49 00 38 d9 	jal 8f16 <__ledf2>
    1d68:	4e 05 02 82 	bltz $r0,226c <_vsnprintf+0xaf0>
    1d6c:	84 00       	movi55 $r0,#0x0
    1d6e:	6a 09 00 09 	fmtsr $r0,$fs18
    1d72:	92 00       	nop16
    1d74:	54 06 84 00 	andi $r0,$r13,#0x400
    1d78:	4e 02 00 7e 	beqz $r0,1e74 <_vsnprintf+0x6f8>
    1d7c:	e7 6a       	slti45 $r11,#0xa
    1d7e:	4e f3 03 58 	bnez $r15,242e <_vsnprintf+0xcb2>
    1d82:	44 00 00 30 	movi $r0,#0x30
    1d86:	10 0f 80 48 	sbi $r0,[$sp+#0x48]
    1d8a:	50 15 ff ff 	addi $r1,$r11,#-1
    1d8e:	50 2f 80 49 	addi $r2,$sp,#0x49
    1d92:	8f 69       	subi45 $r11,#0x9
    1d94:	84 01       	movi55 $r0,#0x1
    1d96:	44 30 00 30 	movi $r3,#0x30
    1d9a:	92 00       	nop16
    1d9c:	4c 05 80 6e 	beq $r0,$r11,1e78 <_vsnprintf+0x6fc>
    1da0:	8c 01       	addi45 $r0,#0x1
    1da2:	18 31 00 01 	sbi.bi $r3,[$r2],#0x1
    1da6:	8e 21       	subi45 $r1,#0x1
    1da8:	5a 08 20 fa 	bnec $r0,#0x20,1d9c <_vsnprintf+0x620>
    1dac:	fb 70       	movpi45 $r11,#0x20
    1dae:	d5 65       	j8 1e78 <_vsnprintf+0x6fc>
    1db0:	80 4a       	mov55 $r2,$r10
    1db2:	50 95 00 01 	addi $r9,$r10,#0x1
    1db6:	fa 15       	movpi45 $r0,#0x25
    1db8:	48 ff fd a0 	j 18f8 <_vsnprintf+0x17c>
    1dbc:	b5 3c       	lwi450 $r9,[$fp]
    1dbe:	51 ce 00 04 	addi $fp,$fp,#0x4
    1dc2:	4e 95 02 6d 	bltz $r9,229c <_vsnprintf+0xb20>
    1dc6:	8d 01       	addi45 $r8,#0x1
    1dc8:	20 01 80 01 	lbsi $r0,[$r3+#0x1]
    1dcc:	48 ff fd 52 	j 1870 <_vsnprintf+0xf4>
    1dd0:	5a 08 2a 04 	bnec $r0,#0x2a,1dd8 <_vsnprintf+0x65c>
    1dd4:	48 00 02 5a 	j 2288 <_vsnprintf+0xb0c>
    1dd8:	81 02       	mov55 $r8,$r2
    1dda:	48 ff fd 51 	j 187c <_vsnprintf+0x100>
    1dde:	92 00       	nop16
    1de0:	20 0e 00 00 	lbsi $r0,[$fp+#0x0]
    1de4:	80 2e       	mov55 $r1,$r14
    1de6:	80 4a       	mov55 $r2,$r10
    1de8:	80 66       	mov55 $r3,$r6
    1dea:	dd 27       	jral5 $r7
    1dec:	5c 04 80 02 	slti $r0,$r9,#0x2
    1df0:	50 ce 00 04 	addi $r12,$fp,#0x4
    1df4:	50 b5 00 01 	addi $r11,$r10,#0x1
    1df8:	4e 03 03 14 	bnez $r0,2420 <_vsnprintf+0xca4>
    1dfc:	41 c4 a8 00 	add $fp,$r9,$r10
    1e00:	50 55 80 01 	addi $r5,$r11,#0x1
    1e04:	80 4b       	mov55 $r2,$r11
    1e06:	fa 10       	movpi45 $r0,#0x20
    1e08:	81 65       	mov55 $r11,$r5
    1e0a:	80 2e       	mov55 $r1,$r14
    1e0c:	80 66       	mov55 $r3,$r6
    1e0e:	dd 27       	jral5 $r7
    1e10:	4c be 7f f8 	bne $r11,$fp,1e00 <_vsnprintf+0x684>
    1e14:	81 4b       	mov55 $r10,$r11
    1e16:	83 8c       	mov55 $fp,$r12
    1e18:	48 ff ff 34 	j 1c80 <_vsnprintf+0x504>
    1e1c:	6a 15 00 01 	fmfsr $r1,$fs10
    1e20:	6a 25 00 01 	fmfsr $r2,$fs10
    1e24:	e2 29       	slt45 $r1,$r9
    1e26:	8c 41       	addi45 $r2,#0x1
    1e28:	4e f2 02 f6 	beqz $r15,2414 <_vsnprintf+0xc98>
    1e2c:	6a 05 00 01 	fmfsr $r0,$fs10
    1e30:	80 4a       	mov55 $r2,$r10
    1e32:	41 c0 28 01 	sub $fp,$r0,$r10
    1e36:	92 00       	nop16
    1e38:	50 d1 00 01 	addi $r13,$r2,#0x1
    1e3c:	fa 10       	movpi45 $r0,#0x20
    1e3e:	80 2e       	mov55 $r1,$r14
    1e40:	80 66       	mov55 $r3,$r6
    1e42:	dd 27       	jral5 $r7
    1e44:	40 0e 34 00 	add $r0,$fp,$r13
    1e48:	40 00 24 06 	slt $r0,$r0,$r9
    1e4c:	80 4d       	mov55 $r2,$r13
    1e4e:	c8 f5       	bnez38 $r0,1e38 <_vsnprintf+0x6bc>
    1e50:	6a 15 00 01 	fmfsr $r1,$fs10
    1e54:	40 04 a8 00 	add $r0,$r9,$r10
    1e58:	40 a0 04 01 	sub $r10,$r0,$r1
    1e5c:	6a 04 00 01 	fmfsr $r0,$fs8
    1e60:	50 14 80 01 	addi $r1,$r9,#0x1
    1e64:	20 00 00 00 	lbsi $r0,[$r0+#0x0]
    1e68:	6a 15 00 09 	fmtsr $r1,$fs10
    1e6c:	4e 03 fe ba 	bnez $r0,1be0 <_vsnprintf+0x464>
    1e70:	48 ff fe ee 	j 1c4c <_vsnprintf+0x4d0>
    1e74:	84 26       	movi55 $r1,#0x6
    1e76:	85 60       	movi55 $r11,#0x0
    1e78:	6a 02 10 c8 	fcpysd $fd0,$fd4,$fd4
    1e7c:	44 00 24 b0 	movi $r0,#0x24b0
    1e80:	f1 89       	swi37.sp $r1,[+#0x24]
    1e82:	6a 08 80 09 	fmtsr $r0,$fs17
    1e86:	49 00 37 4d 	jal 8d20 <__fixdfsi>
    1e8a:	f1 09       	lwi37.sp $r1,[+#0x24]
    1e8c:	44 30 24 58 	movi $r3,#0x2458
    1e90:	94 8b       	slli333 $r2,$r1,#0x3
    1e92:	88 43       	add45 $r2,$r3
    1e94:	34 51 00 00 	fldi $fd5,[$r2+#0x0]
    1e98:	50 c0 00 00 	addi $r12,$r0,#0x0
    1e9c:	49 00 3e 37 	jal 9b0a <__floatsidf>
    1ea0:	6a 10 00 c8 	fcpysd $fd1,$fd0,$fd0
    1ea4:	6a 02 10 c8 	fcpysd $fd0,$fd4,$fd4
    1ea8:	49 00 3a e0 	jal 9468 <__subdf3>
    1eac:	6a 12 94 c8 	fcpysd $fd1,$fd5,$fd5
    1eb0:	49 00 38 88 	jal 8fc0 <__muldf3>
    1eb4:	6a 60 00 c8 	fcpysd $fd6,$fd0,$fd0
    1eb8:	49 00 37 5e 	jal 8d74 <__fixunsdfsi>
    1ebc:	6a 09 80 09 	fmtsr $r0,$fs19
    1ec0:	49 00 3e 5b 	jal 9b76 <__floatunsidf>
    1ec4:	6a 10 00 c8 	fcpysd $fd1,$fd0,$fd0
    1ec8:	6a 03 18 c8 	fcpysd $fd0,$fd6,$fd6
    1ecc:	49 00 3a ce 	jal 9468 <__subdf3>
    1ed0:	6a 08 80 01 	fmfsr $r0,$fs17
    1ed4:	6a 60 00 c8 	fcpysd $fd6,$fd0,$fd0
    1ed8:	34 70 00 00 	fldi $fd7,[$r0+#0x0]
    1edc:	6a 13 9c c8 	fcpysd $fd1,$fd7,$fd7
    1ee0:	49 00 37 c7 	jal 8e6e <__gedf2>
    1ee4:	f1 09       	lwi37.sp $r1,[+#0x24]
    1ee6:	4e 07 00 cb 	blez $r0,207c <_vsnprintf+0x900>
    1eea:	6a 09 80 01 	fmfsr $r0,$fs19
    1eee:	8c 01       	addi45 $r0,#0x1
    1ef0:	6a 09 80 09 	fmtsr $r0,$fs19
    1ef4:	49 00 3e 41 	jal 9b76 <__floatunsidf>
    1ef8:	6a 10 00 c8 	fcpysd $fd1,$fd0,$fd0
    1efc:	6a 02 94 c8 	fcpysd $fd0,$fd5,$fd5
    1f00:	49 00 38 0b 	jal 8f16 <__ledf2>
    1f04:	f1 09       	lwi37.sp $r1,[+#0x24]
    1f06:	4e 07 01 6a 	blez $r0,21da <_vsnprintf+0xa5e>
    1f0a:	92 00       	nop16
    1f0c:	44 00 24 b8 	movi $r0,#0x24b8
    1f10:	34 10 00 00 	fldi $fd1,[$r0+#0x0]
    1f14:	6a 02 10 c8 	fcpysd $fd0,$fd4,$fd4
    1f18:	14 1f 80 09 	swi $r1,[$sp+#0x24]
    1f1c:	49 00 37 a9 	jal 8e6e <__gedf2>
    1f20:	4e 06 00 c5 	bgtz $r0,20aa <_vsnprintf+0x92e>
    1f24:	f1 09       	lwi37.sp $r1,[+#0x24]
    1f26:	4e 13 00 cd 	bnez $r1,20c0 <_vsnprintf+0x944>
    1f2a:	80 0c       	mov55 $r0,$r12
    1f2c:	49 00 3d ef 	jal 9b0a <__floatsidf>
    1f30:	6a 10 00 c8 	fcpysd $fd1,$fd0,$fd0
    1f34:	6a 02 10 c8 	fcpysd $fd0,$fd4,$fd4
    1f38:	49 00 3a 98 	jal 9468 <__subdf3>
    1f3c:	6a 08 80 01 	fmfsr $r0,$fs17
    1f40:	6a 40 00 c8 	fcpysd $fd4,$fd0,$fd0
    1f44:	34 50 00 00 	fldi $fd5,[$r0+#0x0]
    1f48:	6a 12 94 c8 	fcpysd $fd1,$fd5,$fd5
    1f4c:	49 00 37 91 	jal 8e6e <__gedf2>
    1f50:	4e 06 01 5e 	bgtz $r0,220c <_vsnprintf+0xa90>
    1f54:	6a 02 10 c8 	fcpysd $fd0,$fd4,$fd4
    1f58:	6a 12 94 c8 	fcpysd $fd1,$fd5,$fd5
    1f5c:	49 00 37 52 	jal 8e00 <__eqdf2>
    1f60:	c8 06       	bnez38 $r0,1f6c <_vsnprintf+0x7f0>
    1f62:	54 06 00 01 	andi $r0,$r12,#0x1
    1f66:	40 c6 00 00 	add $r12,$r12,$r0
    1f6a:	92 00       	nop16
    1f6c:	5a b0 20 30 	beqc $r11,#0x20,1fcc <_vsnprintf+0x850>
    1f70:	6a 08 00 01 	fmfsr $r0,$fs16
    1f74:	40 16 7c 0a 	srai $r1,$r12,#0x1f
    1f78:	42 06 00 b8 	smmul $r0,$r12,$r0
    1f7c:	b0 92       	addri36.sp $r2,#0x48
    1f7e:	90 02       	srai45 $r0,#0x2
    1f80:	9a 41       	sub333 $r1,$r0,$r1
    1f82:	84 0a       	movi55 $r0,#0xa
    1f84:	42 c0 80 75 	msubr32 $r12,$r1,$r0
    1f88:	50 06 00 30 	addi $r0,$r12,#0x30
    1f8c:	38 01 2c 08 	sb $r0,[$r2+($r11<<#0x0)]
    1f90:	50 c5 80 01 	addi $r12,$r11,#0x1
    1f94:	c1 1e       	beqz38 $r1,1fd0 <_vsnprintf+0x854>
    1f96:	40 31 30 00 	add $r3,$r2,$r12
    1f9a:	86 2a       	movi55 $r17,#0xa
    1f9c:	d5 08       	j8 1fac <_vsnprintf+0x830>
    1f9e:	92 00       	nop16
    1fa0:	50 c6 00 01 	addi $r12,$r12,#0x1
    1fa4:	18 21 80 01 	sbi.bi $r2,[$r3],#0x1
    1fa8:	4e 12 00 14 	beqz $r1,1fd0 <_vsnprintf+0x854>
    1fac:	6a 08 00 01 	fmfsr $r0,$fs16
    1fb0:	40 20 fc 0a 	srai $r2,$r1,#0x1f
    1fb4:	42 00 80 b8 	smmul $r0,$r1,$r0
    1fb8:	90 02       	srai45 $r0,#0x2
    1fba:	8a 02       	sub45 $r0,$r2
    1fbc:	42 10 44 75 	msubr32 $r1,$r0,$r17
    1fc0:	50 20 80 30 	addi $r2,$r1,#0x30
    1fc4:	80 20       	mov55 $r1,$r0
    1fc6:	5a c8 20 ed 	bnec $r12,#0x20,1fa0 <_vsnprintf+0x824>
    1fca:	92 00       	nop16
    1fcc:	44 c0 00 20 	movi $r12,#0x20
    1fd0:	54 36 80 03 	andi $r3,$r13,#0x3
    1fd4:	5a 38 01 04 	bnec $r3,#0x1,1fdc <_vsnprintf+0x860>
    1fd8:	48 00 01 68 	j 22a8 <_vsnprintf+0xb2c>
    1fdc:	4c 96 00 b4 	beq $r9,$r12,2144 <_vsnprintf+0x9c8>
    1fe0:	5c 06 00 20 	slti $r0,$r12,#0x20
    1fe4:	4e 03 00 ba 	bnez $r0,2158 <_vsnprintf+0x9dc>
    1fe8:	80 4a       	mov55 $r2,$r10
    1fea:	cb 19       	bnez38 $r3,201c <_vsnprintf+0x8a0>
    1fec:	40 06 24 06 	slt $r0,$r12,$r9
    1ff0:	4e 02 02 06 	beqz $r0,23fc <_vsnprintf+0xc80>
    1ff4:	40 06 28 01 	sub $r0,$r12,$r10
    1ff8:	6a 03 00 09 	fmtsr $r0,$fs6
    1ffc:	fa 10       	movpi45 $r0,#0x20
    1ffe:	80 2e       	mov55 $r1,$r14
    2000:	80 66       	mov55 $r3,$r6
    2002:	50 b1 00 01 	addi $r11,$r2,#0x1
    2006:	dd 27       	jral5 $r7
    2008:	6a 03 00 01 	fmfsr $r0,$fs6
    200c:	80 4b       	mov55 $r2,$r11
    200e:	88 0b       	add45 $r0,$r11
    2010:	40 00 24 06 	slt $r0,$r0,$r9
    2014:	c8 f4       	bnez38 $r0,1ffc <_vsnprintf+0x880>
    2016:	40 24 a8 00 	add $r2,$r9,$r10
    201a:	8a 4c       	sub45 $r2,$r12
    201c:	4e c2 01 f8 	beqz $r12,240c <_vsnprintf+0xc90>
    2020:	50 06 7f ff 	addi $r0,$r12,#-1
    2024:	b0 52       	addri36.sp $r1,#0x48
    2026:	88 01       	add45 $r0,$r1
    2028:	6a 04 80 09 	fmtsr $r0,$fs9
    202c:	40 b1 30 00 	add $r11,$r2,$r12
    2030:	6a 14 80 01 	fmfsr $r1,$fs9
    2034:	50 c1 00 01 	addi $r12,$r2,#0x1
    2038:	28 00 ff ff 	lbsi.bi $r0,[$r1],#-1
    203c:	6a 14 80 09 	fmtsr $r1,$fs9
    2040:	80 66       	mov55 $r3,$r6
    2042:	80 2e       	mov55 $r1,$r14
    2044:	dd 27       	jral5 $r7
    2046:	80 4c       	mov55 $r2,$r12
    2048:	4c c5 ff f4 	bne $r12,$r11,2030 <_vsnprintf+0x8b4>
    204c:	54 46 80 02 	andi $r4,$r13,#0x2
    2050:	c4 13       	beqz38 $r4,2076 <_vsnprintf+0x8fa>
    2052:	40 05 a8 01 	sub $r0,$r11,$r10
    2056:	e2 09       	slt45 $r0,$r9
    2058:	e8 0f       	beqzs8 2076 <_vsnprintf+0x8fa>
    205a:	92 00       	nop16
    205c:	50 45 80 01 	addi $r4,$r11,#0x1
    2060:	80 4b       	mov55 $r2,$r11
    2062:	fa 10       	movpi45 $r0,#0x20
    2064:	81 64       	mov55 $r11,$r4
    2066:	80 2e       	mov55 $r1,$r14
    2068:	80 66       	mov55 $r3,$r6
    206a:	dd 27       	jral5 $r7
    206c:	40 05 a8 01 	sub $r0,$r11,$r10
    2070:	40 00 24 06 	slt $r0,$r0,$r9
    2074:	c8 f4       	bnez38 $r0,205c <_vsnprintf+0x8e0>
    2076:	81 4b       	mov55 $r10,$r11
    2078:	48 ff fe 04 	j 1c80 <_vsnprintf+0x504>
    207c:	6a 03 18 c8 	fcpysd $fd0,$fd6,$fd6
    2080:	6a 13 9c c8 	fcpysd $fd1,$fd7,$fd7
    2084:	f1 89       	swi37.sp $r1,[+#0x24]
    2086:	49 00 36 bd 	jal 8e00 <__eqdf2>
    208a:	f1 09       	lwi37.sp $r1,[+#0x24]
    208c:	4e 03 ff 40 	bnez $r0,1f0c <_vsnprintf+0x790>
    2090:	6a 09 80 01 	fmfsr $r0,$fs19
    2094:	c0 04       	beqz38 $r0,209c <_vsnprintf+0x920>
    2096:	96 04       	xlsb33 $r0,$r0
    2098:	4e 02 ff 3a 	beqz $r0,1f0c <_vsnprintf+0x790>
    209c:	6a 09 80 01 	fmfsr $r0,$fs19
    20a0:	8c 01       	addi45 $r0,#0x1
    20a2:	6a 09 80 09 	fmtsr $r0,$fs19
    20a6:	48 ff ff 33 	j 1f0c <_vsnprintf+0x790>
    20aa:	85 40       	movi55 $r10,#0x0
    20ac:	48 ff fd ea 	j 1c80 <_vsnprintf+0x504>
    20b0:	20 04 00 02 	lbsi $r0,[$r8+#0x2]
    20b4:	58 d6 80 c0 	ori $r13,$r13,#0xc0
    20b8:	8d 02       	addi45 $r8,#0x2
    20ba:	48 ff fc 17 	j 18e8 <_vsnprintf+0x16c>
    20be:	92 00       	nop16
    20c0:	5a b8 20 04 	bnec $r11,#0x20,20c8 <_vsnprintf+0x94c>
    20c4:	48 ff ff 84 	j 1fcc <_vsnprintf+0x850>
    20c8:	6a 23 80 01 	fmfsr $r2,$fs7
    20cc:	6a 09 80 01 	fmfsr $r0,$fs19
    20d0:	6a 33 80 01 	fmfsr $r3,$fs7
    20d4:	42 00 08 b8 	smmul $r0,$r0,$r2
    20d8:	6a 29 80 01 	fmfsr $r2,$fs19
    20dc:	b1 12       	addri36.sp $r4,#0x48
    20de:	90 5f       	srai45 $r2,#0x1f
    20e0:	fe 9e       	and33 $r2,$r3
    20e2:	88 02       	add45 $r0,$r2
    20e4:	6a 29 80 01 	fmfsr $r2,$fs19
    20e8:	8e 21       	subi45 $r1,#0x1
    20ea:	88 02       	add45 $r0,$r2
    20ec:	40 30 0c 09 	srli $r3,$r0,#0x3
    20f0:	84 0a       	movi55 $r0,#0xa
    20f2:	42 21 80 75 	msubr32 $r2,$r3,$r0
    20f6:	50 01 00 30 	addi $r0,$r2,#0x30
    20fa:	38 02 2c 08 	sb $r0,[$r4+($r11<<#0x0)]
    20fe:	50 25 80 01 	addi $r2,$r11,#0x1
    2102:	4e 32 00 a1 	beqz $r3,2244 <_vsnprintf+0xac8>
    2106:	41 12 08 00 	add $r17,$r4,$r2
    210a:	86 4a       	movi55 $r18,#0xa
    210c:	d5 10       	j8 212c <_vsnprintf+0x9b0>
    210e:	88 03       	add45 $r0,$r3
    2110:	92 03       	srli45 $r0,#0x3
    2112:	42 30 48 75 	msubr32 $r3,$r0,$r18
    2116:	8e 21       	subi45 $r1,#0x1
    2118:	80 a3       	mov55 $r5,$r3
    211a:	80 60       	mov55 $r3,$r0
    211c:	50 02 80 30 	addi $r0,$r5,#0x30
    2120:	8c 41       	addi45 $r2,#0x1
    2122:	18 08 80 01 	sbi.bi $r0,[$r17],#0x1
    2126:	4e 32 00 8f 	beqz $r3,2244 <_vsnprintf+0xac8>
    212a:	92 00       	nop16
    212c:	6a 03 80 01 	fmfsr $r0,$fs7
    2130:	42 01 80 b8 	smmul $r0,$r3,$r0
    2134:	5a 28 20 ed 	bnec $r2,#0x20,210e <_vsnprintf+0x992>
    2138:	48 ff ff 4a 	j 1fcc <_vsnprintf+0x850>
    213c:	5a 90 20 04 	beqc $r9,#0x20,2144 <_vsnprintf+0x9c8>
    2140:	48 00 01 4a 	j 23d4 <_vsnprintf+0xc58>
    2144:	6a 09 00 01 	fmfsr $r0,$fs18
    2148:	c8 06       	bnez38 $r0,2154 <_vsnprintf+0x9d8>
    214a:	54 06 80 0c 	andi $r0,$r13,#0xc
    214e:	4e 02 01 4f 	beqz $r0,23ec <_vsnprintf+0xc70>
    2152:	92 00       	nop16
    2154:	50 c4 ff ff 	addi $r12,$r9,#-1
    2158:	6a 09 00 01 	fmfsr $r0,$fs18
    215c:	c8 4f       	bnez38 $r0,21fa <_vsnprintf+0xa7e>
    215e:	92 00       	nop16
    2160:	54 06 80 04 	andi $r0,$r13,#0x4
    2164:	4e 02 01 2c 	beqz $r0,23bc <_vsnprintf+0xc40>
    2168:	fa 1b       	movpi45 $r0,#0x2b
    216a:	b0 52       	addri36.sp $r1,#0x48
    216c:	38 00 b0 08 	sb $r0,[$r1+($r12<<#0x0)]
    2170:	50 c6 00 01 	addi $r12,$r12,#0x1
    2174:	48 ff ff 3a 	j 1fe8 <_vsnprintf+0x86c>
    2178:	fa 40       	movpi45 $r2,#0x10
    217a:	92 00       	nop16
    217c:	54 36 84 00 	andi $r3,$r13,#0x400
    2180:	66 16 80 0c 	bitci $r1,$r13,#0xc
    2184:	4e 33 00 28 	bnez $r3,21d4 <_vsnprintf+0xa58>
    2188:	5a 08 69 04 	bnec $r0,#0x69,2190 <_vsnprintf+0xa14>
    218c:	48 ff fd ba 	j 1d00 <_vsnprintf+0x584>
    2190:	5a 08 64 04 	bnec $r0,#0x64,2198 <_vsnprintf+0xa1c>
    2194:	48 ff fd b6 	j 1d00 <_vsnprintf+0x584>
    2198:	54 00 82 00 	andi $r0,$r1,#0x200
    219c:	4e 03 00 a8 	bnez $r0,22ec <_vsnprintf+0xb70>
    21a0:	54 00 81 00 	andi $r0,$r1,#0x100
    21a4:	c8 38       	bnez38 $r0,2214 <_vsnprintf+0xa98>
    21a6:	54 00 80 40 	andi $r0,$r1,#0x40
    21aa:	4e 02 00 fb 	beqz $r0,23a0 <_vsnprintf+0xc24>
    21ae:	00 4e 00 00 	lbi $r4,[$fp+#0x0]
    21b2:	51 ce 00 04 	addi $fp,$fp,#0x4
    21b6:	b6 5f       	swi450 $r2,[$sp]
    21b8:	14 bf 80 01 	swi $r11,[$sp+#0x4]
    21bc:	14 9f 80 02 	swi $r9,[$sp+#0x8]
    21c0:	f1 83       	swi37.sp $r1,[+#0xc]
    21c2:	48 ff fd 57 	j 1c70 <_vsnprintf+0x4f4>
    21c6:	81 a1       	mov55 $r13,$r1
    21c8:	5a 08 64 da 	bnec $r0,#0x64,217c <_vsnprintf+0xa00>
    21cc:	54 40 84 00 	andi $r4,$r1,#0x400
    21d0:	4e 42 fd 98 	beqz $r4,1d00 <_vsnprintf+0x584>
    21d4:	66 10 80 01 	bitci $r1,$r1,#0x1
    21d8:	d5 d8       	j8 2188 <_vsnprintf+0xa0c>
    21da:	84 00       	movi55 $r0,#0x0
    21dc:	50 c6 00 01 	addi $r12,$r12,#0x1
    21e0:	6a 09 80 09 	fmtsr $r0,$fs19
    21e4:	48 ff fe 94 	j 1f0c <_vsnprintf+0x790>
    21e8:	66 16 80 0c 	bitci $r1,$r13,#0xc
    21ec:	54 46 84 00 	andi $r4,$r13,#0x400
    21f0:	58 10 80 20 	ori $r1,$r1,#0x20
    21f4:	fa 40       	movpi45 $r2,#0x10
    21f6:	cc ef       	bnez38 $r4,21d4 <_vsnprintf+0xa58>
    21f8:	d5 d0       	j8 2198 <_vsnprintf+0xa1c>
    21fa:	fa 1d       	movpi45 $r0,#0x2d
    21fc:	b0 52       	addri36.sp $r1,#0x48
    21fe:	38 00 b0 08 	sb $r0,[$r1+($r12<<#0x0)]
    2202:	50 c6 00 01 	addi $r12,$r12,#0x1
    2206:	48 ff fe f1 	j 1fe8 <_vsnprintf+0x86c>
    220a:	92 00       	nop16
    220c:	50 c6 00 01 	addi $r12,$r12,#0x1
    2210:	48 ff fe ae 	j 1f6c <_vsnprintf+0x7f0>
    2214:	b6 5f       	swi450 $r2,[$sp]
    2216:	14 bf 80 01 	swi $r11,[$sp+#0x4]
    221a:	14 9f 80 02 	swi $r9,[$sp+#0x8]
    221e:	f1 83       	swi37.sp $r1,[+#0xc]
    2220:	b4 9c       	lwi450 $r4,[$fp]
    2222:	51 ce 00 04 	addi $fp,$fp,#0x4
    2226:	48 ff fd 25 	j 1c70 <_vsnprintf+0x4f4>
    222a:	92 00       	nop16
    222c:	54 00 80 80 	andi $r0,$r1,#0x80
    2230:	4e 03 00 d8 	bnez $r0,23e0 <_vsnprintf+0xc64>
    2234:	b4 bc       	lwi450 $r5,[$fp]
    2236:	51 ce 00 04 	addi $fp,$fp,#0x4
    223a:	48 ff fd 73 	j 1d20 <_vsnprintf+0x5a4>
    223e:	84 42       	movi55 $r2,#0x2
    2240:	d5 9e       	j8 217c <_vsnprintf+0xa00>
    2242:	92 00       	nop16
    2244:	5a 28 20 04 	bnec $r2,#0x20,224c <_vsnprintf+0xad0>
    2248:	48 ff fe c2 	j 1fcc <_vsnprintf+0x850>
    224c:	c1 48       	beqz38 $r1,22dc <_vsnprintf+0xb60>
    224e:	b0 12       	addri36.sp $r0,#0x48
    2250:	88 02       	add45 $r0,$r2
    2252:	44 30 00 30 	movi $r3,#0x30
    2256:	d5 02       	j8 225a <_vsnprintf+0xade>
    2258:	c1 42       	beqz38 $r1,22dc <_vsnprintf+0xb60>
    225a:	8c 41       	addi45 $r2,#0x1
    225c:	8e 21       	subi45 $r1,#0x1
    225e:	18 30 00 01 	sbi.bi $r3,[$r0],#0x1
    2262:	5a 28 20 fb 	bnec $r2,#0x20,2258 <_vsnprintf+0xadc>
    2266:	48 ff fe b3 	j 1fcc <_vsnprintf+0x850>
    226a:	92 00       	nop16
    226c:	6a 12 10 c8 	fcpysd $fd1,$fd4,$fd4
    2270:	6a 02 94 c8 	fcpysd $fd0,$fd5,$fd5
    2274:	44 00 00 01 	movi $r0,#0x1
    2278:	6a 09 00 09 	fmtsr $r0,$fs18
    227c:	49 00 38 f6 	jal 9468 <__subdf3>
    2280:	6a 40 00 c8 	fcpysd $fd4,$fd0,$fd0
    2284:	48 ff fd 78 	j 1d74 <_vsnprintf+0x5f8>
    2288:	b4 3c       	lwi450 $r1,[$fp]
    228a:	20 04 00 02 	lbsi $r0,[$r8+#0x2]
    228e:	42 b5 84 00 	max $r11,$r11,$r1
    2292:	8d 02       	addi45 $r8,#0x2
    2294:	51 ce 00 04 	addi $fp,$fp,#0x4
    2298:	48 ff fa f2 	j 187c <_vsnprintf+0x100>
    229c:	58 d6 80 02 	ori $r13,$r13,#0x2
    22a0:	52 94 80 00 	subri $r9,$r9,#0x0
    22a4:	48 ff fd 91 	j 1dc6 <_vsnprintf+0x64a>
    22a8:	40 06 24 06 	slt $r0,$r12,$r9
    22ac:	4e 02 fe 98 	beqz $r0,1fdc <_vsnprintf+0x860>
    22b0:	5a c8 20 04 	bnec $r12,#0x20,22b8 <_vsnprintf+0xb3c>
    22b4:	48 ff ff 44 	j 213c <_vsnprintf+0x9c0>
    22b8:	b0 12       	addri36.sp $r0,#0x48
    22ba:	88 0c       	add45 $r0,$r12
    22bc:	44 10 00 30 	movi $r1,#0x30
    22c0:	48 00 00 06 	j 22cc <_vsnprintf+0xb50>
    22c4:	5a c8 20 04 	bnec $r12,#0x20,22cc <_vsnprintf+0xb50>
    22c8:	48 ff ff 3a 	j 213c <_vsnprintf+0x9c0>
    22cc:	50 c6 00 01 	addi $r12,$r12,#0x1
    22d0:	18 10 00 01 	sbi.bi $r1,[$r0],#0x1
    22d4:	4c c4 ff f8 	bne $r12,$r9,22c4 <_vsnprintf+0xb48>
    22d8:	48 ff ff 36 	j 2144 <_vsnprintf+0x9c8>
    22dc:	fa 1e       	movpi45 $r0,#0x2e
    22de:	b0 52       	addri36.sp $r1,#0x48
    22e0:	50 b1 00 01 	addi $r11,$r2,#0x1
    22e4:	38 00 88 08 	sb $r0,[$r1+($r2<<#0x0)]
    22e8:	48 ff fe 42 	j 1f6c <_vsnprintf+0x7f0>
    22ec:	84 00       	movi55 $r0,#0x0
    22ee:	f0 91       	swi37.sp $r0,[+#0x44]
    22f0:	f2 90       	swi37.sp $r2,[+#0x40]
    22f2:	f2 10       	lwi37.sp $r2,[+#0x40]
    22f4:	f3 11       	lwi37.sp $r3,[+#0x44]
    22f6:	51 ce 00 07 	addi $fp,$fp,#0x7
    22fa:	b6 1f       	swi450 $r0,[$sp]
    22fc:	f2 82       	swi37.sp $r2,[+#0x8]
    22fe:	f3 83       	swi37.sp $r3,[+#0xc]
    2300:	f1 86       	swi37.sp $r1,[+#0x18]
    2302:	67 ce 00 07 	bitci $fp,$fp,#0x7
    2306:	14 bf 80 04 	swi $r11,[$sp+#0x10]
    230a:	14 9f 80 05 	swi $r9,[$sp+#0x14]
    230e:	80 4a       	mov55 $r2,$r10
    2310:	3a 4e 14 00 	lmw.bi $r4,[$fp],$r5,#0x0    ! {$r4~$r5}
    2314:	80 07       	mov55 $r0,$r7
    2316:	80 2e       	mov55 $r1,$r14
    2318:	50 33 00 00 	addi $r3,$r6,#0x0
    231c:	49 ff f9 b2 	jal 1680 <_ntoa_long_long>
    2320:	51 ce 00 08 	addi $fp,$fp,#0x8
    2324:	81 40       	mov55 $r10,$r0
    2326:	48 ff fc ad 	j 1c80 <_vsnprintf+0x504>
    232a:	84 48       	movi55 $r2,#0x8
    232c:	48 ff ff 28 	j 217c <_vsnprintf+0xa00>
    2330:	51 ce 00 07 	addi $fp,$fp,#0x7
    2334:	67 ce 00 07 	bitci $fp,$fp,#0x7
    2338:	3a 4e 14 00 	lmw.bi $r4,[$fp],$r5,#0x0    ! {$r4~$r5}
    233c:	40 02 fc 0a 	srai $r0,$r5,#0x1f
    2340:	f0 8a       	swi37.sp $r0,[+#0x28]
    2342:	05 2f 80 0a 	lwi $r18,[$sp+#0x28]
    2346:	f0 8b       	swi37.sp $r0,[+#0x2c]
    2348:	05 3f 80 0b 	lwi $r19,[$sp+#0x2c]
    234c:	80 72       	mov55 $r3,$r18
    234e:	80 04       	mov55 $r0,$r4
    2350:	fe 1d       	xor33 $r0,$r3
    2352:	f0 8c       	swi37.sp $r0,[+#0x30]
    2354:	f2 8e       	swi37.sp $r2,[+#0x38]
    2356:	80 05       	mov55 $r0,$r5
    2358:	80 53       	mov55 $r2,$r19
    235a:	fe 15       	xor33 $r0,$r2
    235c:	84 40       	movi55 $r2,#0x0
    235e:	f0 8d       	swi37.sp $r0,[+#0x34]
    2360:	f2 8f       	swi37.sp $r2,[+#0x3c]
    2362:	40 02 fc 09 	srli $r0,$r5,#0x1f
    2366:	f2 0e       	lwi37.sp $r2,[+#0x38]
    2368:	f3 0f       	lwi37.sp $r3,[+#0x3c]
    236a:	05 0f 80 0c 	lwi $r16,[$sp+#0x30]
    236e:	05 1f 80 0d 	lwi $r17,[$sp+#0x34]
    2372:	b6 1f       	swi450 $r0,[$sp]
    2374:	f2 82       	swi37.sp $r2,[+#0x8]
    2376:	f3 83       	swi37.sp $r3,[+#0xc]
    2378:	f1 86       	swi37.sp $r1,[+#0x18]
    237a:	80 4a       	mov55 $r2,$r10
    237c:	14 bf 80 04 	swi $r11,[$sp+#0x10]
    2380:	14 9f 80 05 	swi $r9,[$sp+#0x14]
    2384:	80 07       	mov55 $r0,$r7
    2386:	80 2e       	mov55 $r1,$r14
    2388:	50 33 00 00 	addi $r3,$r6,#0x0
    238c:	42 48 48 34 	sub64 $r4,$r16,$r18
    2390:	49 ff f9 78 	jal 1680 <_ntoa_long_long>
    2394:	51 ce 00 08 	addi $fp,$fp,#0x8
    2398:	81 40       	mov55 $r10,$r0
    239a:	48 ff fc 73 	j 1c80 <_vsnprintf+0x504>
    239e:	92 00       	nop16
    23a0:	54 00 80 80 	andi $r0,$r1,#0x80
    23a4:	c0 2f       	beqz38 $r0,2402 <_vsnprintf+0xc86>
    23a6:	02 4e 00 00 	lhi $r4,[$fp+#0x0]
    23aa:	51 ce 00 04 	addi $fp,$fp,#0x4
    23ae:	48 ff ff 04 	j 21b6 <_vsnprintf+0xa3a>
    23b2:	84 20       	movi55 $r1,#0x0
    23b4:	6a 15 00 09 	fmtsr $r1,$fs10
    23b8:	48 ff fb fe 	j 1bb4 <_vsnprintf+0x438>
    23bc:	54 06 80 08 	andi $r0,$r13,#0x8
    23c0:	4e 02 fe 14 	beqz $r0,1fe8 <_vsnprintf+0x86c>
    23c4:	fa 10       	movpi45 $r0,#0x20
    23c6:	b0 52       	addri36.sp $r1,#0x48
    23c8:	38 00 b0 08 	sb $r0,[$r1+($r12<<#0x0)]
    23cc:	50 c6 00 01 	addi $r12,$r12,#0x1
    23d0:	48 ff fe 0c 	j 1fe8 <_vsnprintf+0x86c>
    23d4:	80 4a       	mov55 $r2,$r10
    23d6:	44 c0 00 20 	movi $r12,#0x20
    23da:	48 ff fe 23 	j 2020 <_vsnprintf+0x8a4>
    23de:	92 00       	nop16
    23e0:	22 5e 00 00 	lhsi $r5,[$fp+#0x0]
    23e4:	51 ce 00 04 	addi $fp,$fp,#0x4
    23e8:	48 ff fc 9c 	j 1d20 <_vsnprintf+0x5a4>
    23ec:	5c f4 80 20 	slti $r15,$r9,#0x20
    23f0:	81 89       	mov55 $r12,$r9
    23f2:	4e f3 fe b7 	bnez $r15,2160 <_vsnprintf+0x9e4>
    23f6:	80 4a       	mov55 $r2,$r10
    23f8:	48 ff fe 14 	j 2020 <_vsnprintf+0x8a4>
    23fc:	80 4a       	mov55 $r2,$r10
    23fe:	48 ff fe 0f 	j 201c <_vsnprintf+0x8a0>
    2402:	b4 9c       	lwi450 $r4,[$fp]
    2404:	51 ce 00 04 	addi $fp,$fp,#0x4
    2408:	48 ff fe d7 	j 21b6 <_vsnprintf+0xa3a>
    240c:	81 62       	mov55 $r11,$r2
    240e:	48 ff fe 1f 	j 204c <_vsnprintf+0x8d0>
    2412:	92 00       	nop16
    2414:	6a 25 00 09 	fmtsr $r2,$fs10
    2418:	4e 03 fb e4 	bnez $r0,1be0 <_vsnprintf+0x464>
    241c:	48 ff fc 18 	j 1c4c <_vsnprintf+0x4d0>
    2420:	83 8c       	mov55 $fp,$r12
    2422:	81 4b       	mov55 $r10,$r11
    2424:	48 ff fc 2e 	j 1c80 <_vsnprintf+0x504>
    2428:	81 2a       	mov55 $r9,$r10
    242a:	48 ff fc 43 	j 1cb0 <_vsnprintf+0x534>
    242e:	80 2b       	mov55 $r1,$r11
    2430:	85 60       	movi55 $r11,#0x0
    2432:	48 ff fd 23 	j 1e78 <_vsnprintf+0x6fc>
    2436:	92 00       	nop16

00002438 <printf>:
    2438:	3b ff fc bc 	smw.adm $sp,[$sp],$sp,#0x2    ! {$lp}
    243c:	ef f4       	addi10.sp #-12
    243e:	84 5f       	movi55 $r2,#-1
    2440:	80 60       	mov55 $r3,$r0
    2442:	b0 41       	addri36.sp $r1,#0x4
    2444:	b1 04       	addri36.sp $r4,#0x10
    2446:	44 00 17 58 	movi $r0,#0x1758
    244a:	49 ff f9 99 	jal 177c <_vsnprintf>
    244e:	92 00       	nop16
    2450:	ec 0c       	addi10.sp #0xc
    2452:	3b ff fc 84 	lmw.bim $sp,[$sp],$sp,#0x2    ! {$lp}
    2456:	dd 9e       	ret5 $lp

00002458 <pow10.3224>:
    2458:	00 00 00 00 00 00 f0 3f 00 00 00 00 00 00 24 40     .......?......$@
    2468:	00 00 00 00 00 00 59 40 00 00 00 00 00 40 8f 40     ......Y@.....@.@
    2478:	00 00 00 00 00 88 c3 40 00 00 00 00 00 6a f8 40     .......@.....j.@
    2488:	00 00 00 00 80 84 2e 41 00 00 00 00 d0 12 63 41     .......A......cA
    2498:	00 00 00 00 84 d7 97 41 00 00 00 00 65 cd cd 41     .......A....e..A
	...
    24b4:	00 00 e0 3f 00 00 c0 ff ff ff df 41                 ...?.......A

000024c0 <__ota_pre_c_init>:
    24c0:	3e 08 00 88 	addi.gp $r0,#0x88
    24c4:	3e 18 31 80 	addi.gp $r1,#0x3180
    24c8:	9a 88       	sub333 $r2,$r1,$r0
    24ca:	c2 19       	beqz38 $r2,24fc <clear_end>
    24cc:	54 71 00 1f 	andi $r7,$r2,#0x1f
    24d0:	84 60       	movi55 $r3,#0x0
    24d2:	84 80       	movi55 $r4,#0x0
    24d4:	84 a0       	movi55 $r5,#0x0
    24d6:	84 c0       	movi55 $r6,#0x0
    24d8:	85 00       	movi55 $r8,#0x0
    24da:	85 20       	movi55 $r9,#0x0
    24dc:	85 40       	movi55 $r10,#0x0
    24de:	c7 09       	beqz38 $r7,24f0 <clear_loop>
    24e0:	9a 97       	sub333 $r2,$r2,$r7

000024e2 <first_clear>:
    24e2:	aa c1       	swi333.bi $r3,[$r0],#0x4
    24e4:	9f fc       	subi333 $r7,$r7,#0x4
    24e6:	cf fe       	bnez38 $r7,24e2 <first_clear>
    24e8:	44 1f ff e0 	movi $r1,#-32
    24ec:	fe 8e       	and33 $r2,$r1
    24ee:	c2 07       	beqz38 $r2,24fc <clear_end>

000024f0 <clear_loop>:
    24f0:	3a 30 28 24 	smw.bim $r3,[$r0],$r10,#0x0    ! {$r3~$r10}
    24f4:	50 21 7f e0 	addi $r2,$r2,#-32
    24f8:	4e 24 ff fc 	bgez $r2,24f0 <clear_loop>

000024fc <clear_end>:
    24fc:	3f c8 80 00 	addi.gp $fp,#0x8000
    2500:	3f f8 80 00 	addi.gp $sp,#0x8000
    2504:	dd 9e       	ret5 $lp
    2506:	92 00       	nop16
    2508:	76 31 2e 30 	*unknown*
    250c:	2e 30 00 00 	lbi.gp $r3,[+#0x0]

00002510 <_ota_nds32_init_mem>:
    2510:	3e 58 00 00 	addi.gp $r5,#0x0
    2514:	3e 48 00 88 	addi.gp $r4,#0x88
    2518:	8a 85       	sub45 $r4,$r5
    251a:	47 03 00 0b 	sethi $r16,#0x3000b
    251e:	59 08 07 38 	ori $r16,$r16,#0x738
    2522:	80 64       	mov55 $r3,$r4
    2524:	80 25       	mov55 $r1,$r5
    2526:	80 50       	mov55 $r2,$r16
    2528:	0c 01 00 01 	lwi.bi $r0,[$r2],#0x4
    252c:	1c 00 80 01 	swi.bi $r0,[$r1],#0x4
    2530:	50 31 ff fc 	addi $r3,$r3,#-4
    2534:	4e 36 ff fa 	bgtz $r3,2528 <_ota_nds32_init_mem+0x18>
    2538:	dd 9e       	ret5 $lp
    253a:	92 00       	nop16
    253c:	00 b0 b0 cc 	lbi $r11,[$r1+#0x30cc]
    2540:	11 98 98 24 	sbi $r25,[$r17+#0x1824]
    2544:	14 b0 b0 cc 	swi $r11,[$r1+#0xc330]
    2548:	42 f2 71 00 	kmmwb2 $r15,$r4,$fp
    254c:	1c b0 b0 cc 	swi.bi $r11,[$r1],#0xc330
    2550:	95 b1       	slli333 $r6,$r6,#0x1
    2552:	2a 27 0c b0 	lhsi.bi $r2,[$r14],#0x1960
    2556:	b0 cc       	addri36.sp $r3,#0x30
    2558:	80 f9       	mov55 $r7,$r25
    255a:	58 58 58 b0 	ori $r5,$r16,#0x58b0
    255e:	b0 cc       	addri36.sp $r3,#0x30
    2560:	1a 0a 00 00 	shi.bi $r0,[$r20],#0x0

00002564 <_ota_soc_clk_init>:
    2564:	46 0c 00 00 	sethi $r0,#0xc0000
    2568:	84 40       	movi55 $r2,#0x0
    256a:	14 20 00 70 	swi $r2,[$r0+#0x1c0]
    256e:	a0 46       	lwi333 $r1,[$r0+#0x18]
    2570:	e6 23       	slti45 $r1,#0x3
    2572:	e9 09       	bnezs8 2584 <_ota_soc_clk_init+0x20>
    2574:	46 12 12 10 	sethi $r1,#0x21210
    2578:	50 10 80 c9 	addi $r1,$r1,#0xc9
    257c:	14 10 00 15 	swi $r1,[$r0+#0x54]
    2580:	64 00 00 40 	standby wait_done
    2584:	44 10 25 3c 	movi $r1,#0x253c
    2588:	3b 00 e4 00 	lmw.bi $r16,[$r1],$r25,#0x0    ! {$r16~$r25}
    258c:	80 1f       	mov55 $r0,$sp
    258e:	3b 0f e4 20 	smw.bi $r16,[$sp],$r25,#0x0    ! {$r16~$r25}
    2592:	84 20       	movi55 $r1,#0x0
    2594:	38 20 04 02 	lw $r2,[$r0+($r1<<#0x0)]
    2598:	98 c1       	add333 $r3,$r0,$r1
    259a:	a0 d9       	lwi333 $r3,[$r3+#0x4]
    259c:	8c 28       	addi45 $r1,#0x8
    259e:	b6 62       	swi450 $r3,[$r2]
    25a0:	5a 18 28 fa 	bnec $r1,#0x28,2594 <_ota_soc_clk_init+0x30>
    25a4:	44 00 00 1a 	movi $r0,#0x1a
    25a8:	5a 00 1a 2c 	beqc $r0,#0x1a,2600 <_ota_soc_clk_init+0x9c>
    25ac:	e4 1b       	sltsi45 $r0,#0x1b
    25ae:	e8 09       	beqzs8 25c0 <_ota_soc_clk_init+0x5c>
    25b0:	5a 00 18 1f 	beqc $r0,#0x18,25ee <_ota_soc_clk_init+0x8a>
    25b4:	e4 19       	sltsi45 $r0,#0x19
    25b6:	e8 13       	beqzs8 25dc <_ota_soc_clk_init+0x78>
    25b8:	5a 00 10 18 	beqc $r0,#0x10,25e8 <_ota_soc_clk_init+0x84>
    25bc:	48 00 00 0e 	j 25d8 <_ota_soc_clk_init+0x74>
    25c0:	5a 00 28 23 	beqc $r0,#0x28,2606 <_ota_soc_clk_init+0xa2>
    25c4:	5e f0 00 29 	sltsi $r15,$r0,#0x29
    25c8:	e8 04       	beqzs8 25d0 <_ota_soc_clk_init+0x6c>
    25ca:	5a 00 20 15 	beqc $r0,#0x20,25f4 <_ota_soc_clk_init+0x90>
    25ce:	d5 05       	j8 25d8 <_ota_soc_clk_init+0x74>
    25d0:	5a 00 34 09 	beqc $r0,#0x34,25e2 <_ota_soc_clk_init+0x7e>
    25d4:	5a 00 c0 13 	beqc $r0,#0xc0,25fa <_ota_soc_clk_init+0x96>
    25d8:	84 20       	movi55 $r1,#0x0
    25da:	d5 14       	j8 2602 <_ota_soc_clk_init+0x9e>
    25dc:	84 21       	movi55 $r1,#0x1
    25de:	84 46       	movi55 $r2,#0x6
    25e0:	d5 16       	j8 260c <_ota_soc_clk_init+0xa8>
    25e2:	84 21       	movi55 $r1,#0x1
    25e4:	84 4a       	movi55 $r2,#0xa
    25e6:	d5 13       	j8 260c <_ota_soc_clk_init+0xa8>
    25e8:	84 20       	movi55 $r1,#0x0
    25ea:	80 41       	mov55 $r2,$r1
    25ec:	d5 10       	j8 260c <_ota_soc_clk_init+0xa8>
    25ee:	84 20       	movi55 $r1,#0x0
    25f0:	84 41       	movi55 $r2,#0x1
    25f2:	d5 0d       	j8 260c <_ota_soc_clk_init+0xa8>
    25f4:	84 20       	movi55 $r1,#0x0
    25f6:	84 47       	movi55 $r2,#0x7
    25f8:	d5 0a       	j8 260c <_ota_soc_clk_init+0xa8>
    25fa:	84 20       	movi55 $r1,#0x0
    25fc:	84 48       	movi55 $r2,#0x8
    25fe:	d5 07       	j8 260c <_ota_soc_clk_init+0xa8>
    2600:	84 21       	movi55 $r1,#0x1
    2602:	84 42       	movi55 $r2,#0x2
    2604:	d5 04       	j8 260c <_ota_soc_clk_init+0xa8>
    2606:	84 20       	movi55 $r1,#0x0
    2608:	84 43       	movi55 $r2,#0x3
    260a:	92 00       	nop16
    260c:	46 3c cb 0b 	sethi $r3,#0xccb0b
    2610:	a1 1d       	lwi333 $r4,[$r3+#0x14]
    2612:	66 42 10 00 	bitci $r4,$r4,#0x1000
    2616:	40 12 05 84 	or_slli $r1,$r4,$r1,#0xc
    261a:	a8 5d       	swi333 $r1,[$r3+#0x14]
    261c:	a0 5d       	lwi333 $r1,[$r3+#0x14]
    261e:	66 10 80 0f 	bitci $r1,$r1,#0xf
    2622:	fe 8f       	or33 $r2,$r1
    2624:	a8 9d       	swi333 $r2,[$r3+#0x14]
    2626:	a0 59       	lwi333 $r1,[$r3+#0x4]
    2628:	42 10 fc 08 	bset $r1,$r1,#0x1f
    262c:	a8 59       	swi333 $r1,[$r3+#0x4]
    262e:	46 1c 00 00 	sethi $r1,#0xc0000
    2632:	50 10 80 5c 	addi $r1,$r1,#0x5c
    2636:	b4 41       	lwi450 $r2,[$r1]
    2638:	42 21 08 0b 	btst $r2,$r2,#0x2
    263c:	5a 28 01 fd 	bnec $r2,#0x1,2636 <_ota_soc_clk_init+0xd2>
    2640:	44 30 01 40 	movi $r3,#0x140
    2644:	46 1c cb 0b 	sethi $r1,#0xccb0b
    2648:	5a 30 f0 08 	beqc $r3,#0xf0,2658 <_ota_soc_clk_init+0xf4>
    264c:	5a 39 e0 0a 	bnec $r3,#0x1e0,2660 <_ota_soc_clk_init+0xfc>
    2650:	a0 8c       	lwi333 $r2,[$r1+#0x10]
    2652:	58 21 00 38 	ori $r2,$r2,#0x38
    2656:	a8 8c       	swi333 $r2,[$r1+#0x10]
    2658:	a0 8e       	lwi333 $r2,[$r1+#0x18]
    265a:	42 21 3c 08 	bset $r2,$r2,#0xf
    265e:	d5 04       	j8 2666 <_ota_soc_clk_init+0x102>
    2660:	a0 8e       	lwi333 $r2,[$r1+#0x18]
    2662:	42 21 3c 09 	bclr $r2,$r2,#0xf
    2666:	a8 8e       	swi333 $r2,[$r1+#0x18]
    2668:	46 2c 00 00 	sethi $r2,#0xc0000
    266c:	04 11 00 17 	lwi $r1,[$r2+#0x5c]
    2670:	92 28       	srli45 $r1,#0x8
    2672:	96 67       	fexti33 $r1,#0x4
    2674:	5a 18 03 fc 	bnec $r1,#0x3,266c <_ota_soc_clk_init+0x108>
    2678:	46 1c 00 00 	sethi $r1,#0xc0000
    267c:	50 10 80 5c 	addi $r1,$r1,#0x5c
    2680:	b4 41       	lwi450 $r2,[$r1]
    2682:	5a 2b 07 ff 	bnec $r2,#0x307,2680 <_ota_soc_clk_init+0x11c>
    2686:	46 1c 00 00 	sethi $r1,#0xc0000
    268a:	44 20 00 a0 	movi $r2,#0xa0
    268e:	58 10 81 00 	ori $r1,$r1,#0x100
    2692:	5a 20 50 08 	beqc $r2,#0x50,26a2 <_ota_soc_clk_init+0x13e>
    2696:	5a 28 a0 0a 	bnec $r2,#0xa0,26aa <_ota_soc_clk_init+0x146>
    269a:	a8 8e       	swi333 $r2,[$r1+#0x18]
    269c:	46 19 00 00 	sethi $r1,#0x90000
    26a0:	d5 0a       	j8 26b4 <_ota_soc_clk_init+0x150>
    26a2:	a8 8e       	swi333 $r2,[$r1+#0x18]
    26a4:	46 18 00 00 	sethi $r1,#0x80000
    26a8:	d5 06       	j8 26b4 <_ota_soc_clk_init+0x150>
    26aa:	fa 58       	movpi45 $r2,#0x28
    26ac:	a8 8e       	swi333 $r2,[$r1+#0x18]
    26ae:	46 14 00 00 	sethi $r1,#0x40000
    26b2:	92 00       	nop16
    26b4:	42 00 7c 08 	bset $r0,$r0,#0x1f
    26b8:	46 2c 00 00 	sethi $r2,#0xc0000
    26bc:	14 01 00 82 	swi $r0,[$r2+#0x208]
    26c0:	14 01 00 86 	swi $r0,[$r2+#0x218]
    26c4:	14 01 00 8a 	swi $r0,[$r2+#0x228]
    26c8:	14 01 00 8e 	swi $r0,[$r2+#0x238]
    26cc:	14 01 00 92 	swi $r0,[$r2+#0x248]
    26d0:	14 01 00 96 	swi $r0,[$r2+#0x258]
    26d4:	14 01 00 9a 	swi $r0,[$r2+#0x268]
    26d8:	14 01 00 9e 	swi $r0,[$r2+#0x278]
    26dc:	5a 30 f0 18 	beqc $r3,#0xf0,270c <_ota_soc_clk_init+0x1a8>
    26e0:	5e f1 80 f1 	sltsi $r15,$r3,#0xf1
    26e4:	e8 08       	beqzs8 26f4 <_ota_soc_clk_init+0x190>
    26e6:	5a 30 50 17 	beqc $r3,#0x50,2714 <_ota_soc_clk_init+0x1b0>
    26ea:	5a 38 a0 19 	bnec $r3,#0xa0,271c <_ota_soc_clk_init+0x1b8>
    26ee:	42 10 ec 08 	bset $r1,$r1,#0x1b
    26f2:	d5 17       	j8 2720 <_ota_soc_clk_init+0x1bc>
    26f4:	5a 31 40 08 	beqc $r3,#0x140,2704 <_ota_soc_clk_init+0x1a0>
    26f8:	5a 39 e0 12 	bnec $r3,#0x1e0,271c <_ota_soc_clk_init+0x1b8>
    26fc:	46 00 c0 00 	sethi $r0,#0xc000
    2700:	48 00 00 04 	j 2708 <_ota_soc_clk_init+0x1a4>
    2704:	46 00 a0 00 	sethi $r0,#0xa000
    2708:	fe 47       	or33 $r1,$r0
    270a:	d5 0b       	j8 2720 <_ota_soc_clk_init+0x1bc>
    270c:	46 00 90 00 	sethi $r0,#0x9000
    2710:	48 ff ff fc 	j 2708 <_ota_soc_clk_init+0x1a4>
    2714:	42 10 e8 08 	bset $r1,$r1,#0x1a
    2718:	48 00 00 04 	j 2720 <_ota_soc_clk_init+0x1bc>
    271c:	42 10 e0 08 	bset $r1,$r1,#0x18
    2720:	58 10 80 c9 	ori $r1,$r1,#0xc9
    2724:	46 3c 00 00 	sethi $r3,#0xc0000
    2728:	14 11 00 15 	swi $r1,[$r2+#0x54]
    272c:	64 00 00 40 	standby wait_done
    2730:	44 00 00 50 	movi $r0,#0x50
    2734:	5a 08 50 0a 	bnec $r0,#0x50,2748 <_ota_soc_clk_init+0x1e4>
    2738:	04 01 80 0f 	lwi $r0,[$r3+#0x3c]
    273c:	66 00 00 0f 	bitci $r0,$r0,#0xf
    2740:	58 00 00 08 	ori $r0,$r0,#0x8
    2744:	48 00 00 08 	j 2754 <_ota_soc_clk_init+0x1f0>
    2748:	04 01 80 0f 	lwi $r0,[$r3+#0x3c]
    274c:	66 00 00 0f 	bitci $r0,$r0,#0xf
    2750:	58 00 00 04 	ori $r0,$r0,#0x4
    2754:	14 01 80 0f 	swi $r0,[$r3+#0x3c]
    2758:	dd 9e       	ret5 $lp
    275a:	92 00       	nop16

0000275c <my_memcmp>:
    275c:	c2 12       	beqz38 $r2,2780 <my_memcmp+0x24>
    275e:	a7 00       	lbi333 $r4,[$r0+#0x0]
    2760:	a7 48       	lbi333 $r5,[$r1+#0x0]
    2762:	4c 42 c0 11 	bne $r4,$r5,2784 <my_memcmp+0x28>
    2766:	9c c1       	addi333 $r3,$r0,#0x1
    2768:	8c 21       	addi45 $r1,#0x1
    276a:	88 40       	add45 $r2,$r0
    276c:	d5 08       	j8 277c <my_memcmp+0x20>
    276e:	92 00       	nop16
    2770:	08 41 80 01 	lbi.bi $r4,[$r3],#0x1
    2774:	08 50 80 01 	lbi.bi $r5,[$r1],#0x1
    2778:	4c 42 c0 06 	bne $r4,$r5,2784 <my_memcmp+0x28>
    277c:	4c 31 7f fa 	bne $r3,$r2,2770 <my_memcmp+0x14>
    2780:	84 00       	movi55 $r0,#0x0
    2782:	dd 9e       	ret5 $lp
    2784:	9a 25       	sub333 $r0,$r4,$r5
    2786:	dd 9e       	ret5 $lp

00002788 <my_strlen>:
    2788:	20 20 00 00 	lbsi $r2,[$r0+#0x0]
    278c:	9c 41       	addi333 $r1,$r0,#0x1
    278e:	c2 07       	beqz38 $r2,279c <my_strlen+0x14>
    2790:	9a c8       	sub333 $r3,$r1,$r0
    2792:	28 20 80 01 	lbsi.bi $r2,[$r1],#0x1
    2796:	ca fd       	bnez38 $r2,2790 <my_strlen+0x8>
    2798:	80 03       	mov55 $r0,$r3
    279a:	dd 9e       	ret5 $lp
    279c:	84 60       	movi55 $r3,#0x0
    279e:	d5 fd       	j8 2798 <my_strlen+0x10>

000027a0 <serial_tx>:
    27a0:	46 1c 00 00 	sethi $r1,#0xc0000
    27a4:	14 00 83 00 	swi $r0,[$r1+#0xc00]
    27a8:	dd 9e       	ret5 $lp
    27aa:	92 00       	nop16

000027ac <body>:
    27ac:	3a 6f ba bc 	smw.adm $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    27b0:	ef c4       	addi10.sp #-60
    27b2:	36 3f 80 00 	fsdi $fd3,[$sp+#0x0]
    27b6:	36 4f 80 02 	fsdi $fd4,[$sp+#0x8]
    27ba:	36 5f 80 04 	fsdi $fd5,[$sp+#0x10]
    27be:	36 6f 80 06 	fsdi $fd6,[$sp+#0x18]
    27c2:	36 7f 80 08 	fsdi $fd7,[$sp+#0x20]
    27c6:	36 8f 80 0a 	fsdi $fd8,[$sp+#0x28]
    27ca:	36 9f 80 0c 	fsdi $fd9,[$sp+#0x30]
    27ce:	46 3d 76 aa 	sethi $r3,#0xd76aa
    27d2:	6a 28 80 09 	fmtsr $r2,$fs17
    27d6:	50 21 84 78 	addi $r2,$r3,#0x478
    27da:	46 3e 8c 7b 	sethi $r3,#0xe8c7b
    27de:	6a 2c 80 09 	fmtsr $r2,$fs25
    27e2:	50 21 87 56 	addi $r2,$r3,#0x756
    27e6:	46 32 42 07 	sethi $r3,#0x24207
    27ea:	6a 2c 00 09 	fmtsr $r2,$fs24
    27ee:	50 21 80 db 	addi $r2,$r3,#0xdb
    27f2:	46 3c 1b dc 	sethi $r3,#0xc1bdc
    27f6:	6a 2b 80 09 	fmtsr $r2,$fs23
    27fa:	50 21 8e ee 	addi $r2,$r3,#0xeee
    27fe:	46 3f 57 c0 	sethi $r3,#0xf57c0
    2802:	6a 2b 00 09 	fmtsr $r2,$fs22
    2806:	50 21 8f af 	addi $r2,$r3,#0xfaf
    280a:	46 34 78 7c 	sethi $r3,#0x4787c
    280e:	6a 22 80 09 	fmtsr $r2,$fs5
    2812:	50 21 86 2a 	addi $r2,$r3,#0x62a
    2816:	46 3a 83 04 	sethi $r3,#0xa8304
    281a:	6a 22 00 09 	fmtsr $r2,$fs4
    281e:	50 21 86 13 	addi $r2,$r3,#0x613
    2822:	46 3f d4 69 	sethi $r3,#0xfd469
    2826:	6a 21 80 09 	fmtsr $r2,$fs3
    282a:	50 21 85 01 	addi $r2,$r3,#0x501
    282e:	46 36 98 09 	sethi $r3,#0x69809
    2832:	6a 21 00 09 	fmtsr $r2,$fs2
    2836:	50 21 88 d8 	addi $r2,$r3,#0x8d8
    283a:	46 38 b4 4f 	sethi $r3,#0x8b44f
    283e:	6a 20 80 09 	fmtsr $r2,$fs1
    2842:	47 e8 95 cd 	sethi $lp,#0x895cd
    2846:	50 21 87 af 	addi $r2,$r3,#0x7af
    284a:	6a 20 00 09 	fmtsr $r2,$fs0
    284e:	47 c6 b9 01 	sethi $fp,#0x6b901
    2852:	50 2f 07 be 	addi $r2,$lp,#0x7be
    2856:	6a 2f 00 09 	fmtsr $r2,$fs30
    285a:	46 ef d9 87 	sethi $r14,#0xfd987
    285e:	50 2e 01 22 	addi $r2,$fp,#0x122
    2862:	6a 2e 80 09 	fmtsr $r2,$fs29
    2866:	46 da 67 94 	sethi $r13,#0xa6794
    286a:	50 27 01 93 	addi $r2,$r14,#0x193
    286e:	6a 2e 00 09 	fmtsr $r2,$fs28
    2872:	46 c4 9b 40 	sethi $r12,#0x49b40
    2876:	50 26 83 8e 	addi $r2,$r13,#0x38e
    287a:	6a 2d 80 09 	fmtsr $r2,$fs27
    287e:	46 bf 61 e2 	sethi $r11,#0xf61e2
    2882:	50 26 08 21 	addi $r2,$r12,#0x821
    2886:	6a 2d 00 09 	fmtsr $r2,$fs26
    288a:	46 ac 04 0b 	sethi $r10,#0xc040b
    288e:	50 25 85 62 	addi $r2,$r11,#0x562
    2892:	6a 27 00 09 	fmtsr $r2,$fs14
    2896:	46 92 65 e5 	sethi $r9,#0x265e5
    289a:	50 25 03 40 	addi $r2,$r10,#0x340
    289e:	6a 26 00 09 	fmtsr $r2,$fs12
    28a2:	46 8e 9b 6c 	sethi $r8,#0xe9b6c
    28a6:	50 24 8a 51 	addi $r2,$r9,#0xa51
    28aa:	6a 25 80 09 	fmtsr $r2,$fs11
    28ae:	46 7d 62 f1 	sethi $r7,#0xd62f1
    28b2:	50 24 07 aa 	addi $r2,$r8,#0x7aa
    28b6:	6a 25 00 09 	fmtsr $r2,$fs10
    28ba:	46 60 24 41 	sethi $r6,#0x2441
    28be:	50 23 80 5d 	addi $r2,$r7,#0x5d
    28c2:	6a 24 80 09 	fmtsr $r2,$fs9
    28c6:	46 fd 8a 1e 	sethi $r15,#0xd8a1e
    28ca:	50 23 04 53 	addi $r2,$r6,#0x453
    28ce:	6a 24 00 09 	fmtsr $r2,$fs8
    28d2:	47 9e 7d 3f 	sethi $r25,#0xe7d3f
    28d6:	50 27 86 81 	addi $r2,$r15,#0x681
    28da:	6a 23 80 09 	fmtsr $r2,$fs7
    28de:	50 2c 8b c8 	addi $r2,$r25,#0xbc8
    28e2:	6a 23 00 09 	fmtsr $r2,$fs6
    28e6:	31 f0 00 02 	flsi $fs31,[$r0+#0x8]
    28ea:	31 20 00 05 	flsi $fs18,[$r0+#0x14]
    28ee:	05 50 00 03 	lwi $r21,[$r0+#0xc]
    28f2:	05 60 00 04 	lwi $r22,[$r0+#0x10]
    28f6:	a6 c9       	lbi333 $r3,[$r1+#0x1]
    28f8:	a7 0a       	lbi333 $r4,[$r1+#0x2]
    28fa:	a6 88       	lbi333 $r2,[$r1+#0x0]
    28fc:	a7 4b       	lbi333 $r5,[$r1+#0x3]
    28fe:	40 42 40 08 	slli $r4,$r4,#0x10
    2902:	40 31 a0 08 	slli $r3,$r3,#0x8
    2906:	fe e7       	or33 $r3,$r4
    2908:	fe d7       	or33 $r3,$r2
    290a:	40 42 e0 08 	slli $r4,$r5,#0x18
    290e:	41 81 90 04 	or $r24,$r3,$r4
    2912:	15 80 00 16 	swi $r24,[$r0+#0x58]
    2916:	a6 cd       	lbi333 $r3,[$r1+#0x5]
    2918:	a7 0e       	lbi333 $r4,[$r1+#0x6]
    291a:	a6 8c       	lbi333 $r2,[$r1+#0x4]
    291c:	a7 4f       	lbi333 $r5,[$r1+#0x7]
    291e:	40 42 40 08 	slli $r4,$r4,#0x10
    2922:	40 31 a0 08 	slli $r3,$r3,#0x8
    2926:	fe e7       	or33 $r3,$r4
    2928:	fe d7       	or33 $r3,$r2
    292a:	40 42 e0 08 	slli $r4,$r5,#0x18
    292e:	40 b1 90 04 	or $r11,$r3,$r4
    2932:	14 b0 00 17 	swi $r11,[$r0+#0x5c]
    2936:	00 30 80 09 	lbi $r3,[$r1+#0x9]
    293a:	00 50 80 0a 	lbi $r5,[$r1+#0xa]
    293e:	00 20 80 08 	lbi $r2,[$r1+#0x8]
    2942:	00 40 80 0b 	lbi $r4,[$r1+#0xb]
    2946:	40 52 c0 08 	slli $r5,$r5,#0x10
    294a:	40 31 a0 08 	slli $r3,$r3,#0x8
    294e:	fe ef       	or33 $r3,$r5
    2950:	fe d7       	or33 $r3,$r2
    2952:	40 52 60 08 	slli $r5,$r4,#0x18
    2956:	40 71 94 04 	or $r7,$r3,$r5
    295a:	14 70 00 18 	swi $r7,[$r0+#0x60]
    295e:	00 30 80 0d 	lbi $r3,[$r1+#0xd]
    2962:	00 40 80 0e 	lbi $r4,[$r1+#0xe]
    2966:	00 20 80 0c 	lbi $r2,[$r1+#0xc]
    296a:	00 50 80 0f 	lbi $r5,[$r1+#0xf]
    296e:	40 42 40 08 	slli $r4,$r4,#0x10
    2972:	40 31 a0 08 	slli $r3,$r3,#0x8
    2976:	fe e7       	or33 $r3,$r4
    2978:	fe d7       	or33 $r3,$r2
    297a:	40 42 e0 08 	slli $r4,$r5,#0x18
    297e:	40 d1 90 04 	or $r13,$r3,$r4
    2982:	14 d0 00 19 	swi $r13,[$r0+#0x64]
    2986:	00 30 80 11 	lbi $r3,[$r1+#0x11]
    298a:	00 50 80 12 	lbi $r5,[$r1+#0x12]
    298e:	00 20 80 10 	lbi $r2,[$r1+#0x10]
    2992:	40 52 c0 08 	slli $r5,$r5,#0x10
    2996:	40 31 a0 08 	slli $r3,$r3,#0x8
    299a:	00 40 80 13 	lbi $r4,[$r1+#0x13]
    299e:	fe ef       	or33 $r3,$r5
    29a0:	fe d7       	or33 $r3,$r2
    29a2:	6a 29 00 01 	fmfsr $r2,$fs18
    29a6:	40 52 60 08 	slli $r5,$r4,#0x18
    29aa:	40 41 94 04 	or $r4,$r3,$r5
    29ae:	6b 0c 80 01 	fmfsr $r16,$fs25
    29b2:	40 31 58 03 	xor $r3,$r2,$r22
    29b6:	6a 2f 80 01 	fmfsr $r2,$fs31
    29ba:	14 40 00 1a 	swi $r4,[$r0+#0x68]
    29be:	89 82       	add45 $r16,$r2
    29c0:	6a 29 00 01 	fmfsr $r2,$fs18
    29c4:	00 50 80 16 	lbi $r5,[$r1+#0x16]
    29c8:	01 30 80 15 	lbi $r19,[$r1+#0x15]
    29cc:	40 31 d4 02 	and $r3,$r3,$r21
    29d0:	fe d5       	xor33 $r3,$r2
    29d2:	00 60 80 14 	lbi $r6,[$r1+#0x14]
    29d6:	00 20 80 17 	lbi $r2,[$r1+#0x17]
    29da:	88 70       	add45 $r3,$r16
    29dc:	41 39 a0 08 	slli $r19,$r19,#0x8
    29e0:	41 02 c0 08 	slli $r16,$r5,#0x10
    29e4:	40 59 c0 04 	or $r5,$r19,$r16
    29e8:	ff 77       	or33 $r5,$r6
    29ea:	41 01 60 08 	slli $r16,$r2,#0x18
    29ee:	88 78       	add45 $r3,$r24
    29f0:	40 f2 c0 04 	or $r15,$r5,$r16
    29f4:	6a 2c 00 01 	fmfsr $r2,$fs24
    29f8:	6a 59 00 01 	fmfsr $r5,$fs18
    29fc:	40 31 e4 0b 	rotri $r3,$r3,#0x19
    2a00:	88 75       	add45 $r3,$r21
    2a02:	41 0b 54 03 	xor $r16,$r22,$r21
    2a06:	14 f0 00 1b 	swi $r15,[$r0+#0x6c]
    2a0a:	41 32 88 00 	add $r19,$r5,$r2
    2a0e:	01 10 80 19 	lbi $r17,[$r1+#0x19]
    2a12:	40 51 c0 02 	and $r5,$r3,$r16
    2a16:	01 20 80 1a 	lbi $r18,[$r1+#0x1a]
    2a1a:	41 02 d8 03 	xor $r16,$r5,$r22
    2a1e:	40 59 ac 00 	add $r5,$r19,$r11
    2a22:	88 b0       	add45 $r5,$r16
    2a24:	41 29 40 08 	slli $r18,$r18,#0x10
    2a28:	41 18 a0 08 	slli $r17,$r17,#0x8
    2a2c:	00 60 80 18 	lbi $r6,[$r1+#0x18]
    2a30:	41 18 c8 04 	or $r17,$r17,$r18
    2a34:	00 20 80 1b 	lbi $r2,[$r1+#0x1b]
    2a38:	6b 2b 80 01 	fmfsr $r18,$fs23
    2a3c:	40 52 d0 0b 	rotri $r5,$r5,#0x14
    2a40:	88 a3       	add45 $r5,$r3
    2a42:	41 01 d4 03 	xor $r16,$r3,$r21
    2a46:	41 3b 48 00 	add $r19,$r22,$r18
    2a4a:	41 18 98 04 	or $r17,$r17,$r6
    2a4e:	41 22 c0 02 	and $r18,$r5,$r16
    2a52:	41 01 60 08 	slli $r16,$r2,#0x18
    2a56:	40 98 c0 04 	or $r9,$r17,$r16
    2a5a:	41 09 54 03 	xor $r16,$r18,$r21
    2a5e:	41 29 9c 00 	add $r18,$r19,$r7
    2a62:	14 90 00 1c 	swi $r9,[$r0+#0x70]
    2a66:	89 d0       	add45 $r18,$r16
    2a68:	01 10 80 1d 	lbi $r17,[$r1+#0x1d]
    2a6c:	01 40 80 1e 	lbi $r20,[$r1+#0x1e]
    2a70:	41 29 3c 0b 	rotri $r18,$r18,#0xf
    2a74:	6b 3b 00 01 	fmfsr $r19,$fs22
    2a78:	89 c5       	add45 $r18,$r5
    2a7a:	41 02 8c 03 	xor $r16,$r5,$r3
    2a7e:	00 60 80 1c 	lbi $r6,[$r1+#0x1c]
    2a82:	00 20 80 1f 	lbi $r2,[$r1+#0x1f]
    2a86:	89 f5       	add45 $r19,$r21
    2a88:	41 09 40 02 	and $r16,$r18,$r16
    2a8c:	41 4a 40 08 	slli $r20,$r20,#0x10
    2a90:	41 18 a0 08 	slli $r17,$r17,#0x8
    2a94:	41 08 0c 03 	xor $r16,$r16,$r3
    2a98:	41 18 d0 04 	or $r17,$r17,$r20
    2a9c:	89 ed       	add45 $r19,$r13
    2a9e:	41 18 98 04 	or $r17,$r17,$r6
    2aa2:	89 f0       	add45 $r19,$r16
    2aa4:	41 01 60 08 	slli $r16,$r2,#0x18
    2aa8:	41 e8 c0 04 	or $lp,$r17,$r16
    2aac:	41 39 a8 0b 	rotri $r19,$r19,#0xa
    2ab0:	6a 22 80 01 	fmfsr $r2,$fs5
    2ab4:	15 e0 00 1d 	swi $lp,[$r0+#0x74]
    2ab8:	89 f2       	add45 $r19,$r18
    2aba:	41 09 14 03 	xor $r16,$r18,$r5
    2abe:	01 40 80 22 	lbi $r20,[$r1+#0x22]
    2ac2:	01 10 80 21 	lbi $r17,[$r1+#0x21]
    2ac6:	88 44       	add45 $r2,$r4
    2ac8:	41 09 c0 02 	and $r16,$r19,$r16
    2acc:	41 08 14 03 	xor $r16,$r16,$r5
    2ad0:	88 62       	add45 $r3,$r2
    2ad2:	00 20 80 23 	lbi $r2,[$r1+#0x23]
    2ad6:	00 60 80 20 	lbi $r6,[$r1+#0x20]
    2ada:	88 70       	add45 $r3,$r16
    2adc:	41 18 a0 08 	slli $r17,$r17,#0x8
    2ae0:	41 0a 40 08 	slli $r16,$r20,#0x10
    2ae4:	41 18 c0 04 	or $r17,$r17,$r16
    2ae8:	41 41 60 08 	slli $r20,$r2,#0x18
    2aec:	40 31 e4 0b 	rotri $r3,$r3,#0x19
    2af0:	6a 22 00 01 	fmfsr $r2,$fs4
    2af4:	88 73       	add45 $r3,$r19
    2af6:	41 09 c8 03 	xor $r16,$r19,$r18
    2afa:	41 18 98 04 	or $r17,$r17,$r6
    2afe:	40 a8 d0 04 	or $r10,$r17,$r20
    2b02:	41 01 c0 02 	and $r16,$r3,$r16
    2b06:	41 47 88 00 	add $r20,$r15,$r2
    2b0a:	14 a0 00 1e 	swi $r10,[$r0+#0x78]
    2b0e:	41 08 48 03 	xor $r16,$r16,$r18
    2b12:	41 4a 14 00 	add $r20,$r20,$r5
    2b16:	01 10 80 25 	lbi $r17,[$r1+#0x25]
    2b1a:	00 50 80 26 	lbi $r5,[$r1+#0x26]
    2b1e:	41 4a 40 00 	add $r20,$r20,$r16
    2b22:	41 4a 50 0b 	rotri $r20,$r20,#0x14
    2b26:	6b 91 80 01 	fmfsr $r25,$fs3
    2b2a:	00 60 80 24 	lbi $r6,[$r1+#0x24]
    2b2e:	00 20 80 27 	lbi $r2,[$r1+#0x27]
    2b32:	41 4a 0c 00 	add $r20,$r20,$r3
    2b36:	41 01 cc 03 	xor $r16,$r3,$r19
    2b3a:	40 52 c0 08 	slli $r5,$r5,#0x10
    2b3e:	41 18 a0 08 	slli $r17,$r17,#0x8
    2b42:	41 94 e4 00 	add $r25,$r9,$r25
    2b46:	41 0a 40 02 	and $r16,$r20,$r16
    2b4a:	41 18 94 04 	or $r17,$r17,$r5
    2b4e:	41 08 4c 03 	xor $r16,$r16,$r19
    2b52:	40 51 60 08 	slli $r5,$r2,#0x18
    2b56:	89 d9       	add45 $r18,$r25
    2b58:	41 18 98 04 	or $r17,$r17,$r6
    2b5c:	40 68 94 04 	or $r6,$r17,$r5
    2b60:	89 d0       	add45 $r18,$r16
    2b62:	14 60 00 1f 	swi $r6,[$r0+#0x7c]
    2b66:	6a 21 00 01 	fmfsr $r2,$fs2
    2b6a:	41 29 3c 0b 	rotri $r18,$r18,#0xf
    2b6e:	89 d4       	add45 $r18,$r20
    2b70:	00 80 80 29 	lbi $r8,[$r1+#0x29]
    2b74:	01 00 80 2a 	lbi $r16,[$r1+#0x2a]
    2b78:	40 5a 0c 03 	xor $r5,$r20,$r3
    2b7c:	41 1f 08 00 	add $r17,$lp,$r2
    2b80:	40 59 14 02 	and $r5,$r18,$r5
    2b84:	01 90 80 28 	lbi $r25,[$r1+#0x28]
    2b88:	00 20 80 2b 	lbi $r2,[$r1+#0x2b]
    2b8c:	ff 5d       	xor33 $r5,$r3
    2b8e:	89 b3       	add45 $r17,$r19
    2b90:	41 08 40 08 	slli $r16,$r16,#0x10
    2b94:	41 34 20 08 	slli $r19,$r8,#0x8
    2b98:	89 a5       	add45 $r17,$r5
    2b9a:	40 59 c0 04 	or $r5,$r19,$r16
    2b9e:	40 52 e4 04 	or $r5,$r5,$r25
    2ba2:	41 01 60 08 	slli $r16,$r2,#0x18
    2ba6:	40 c2 c0 04 	or $r12,$r5,$r16
    2baa:	6a 20 80 01 	fmfsr $r2,$fs1
    2bae:	41 18 a8 0b 	rotri $r17,$r17,#0xa
    2bb2:	14 c0 00 20 	swi $r12,[$r0+#0x80]
    2bb6:	89 b2       	add45 $r17,$r18
    2bb8:	41 39 50 03 	xor $r19,$r18,$r20
    2bbc:	00 50 80 2e 	lbi $r5,[$r1+#0x2e]
    2bc0:	41 05 08 00 	add $r16,$r10,$r2
    2bc4:	41 38 cc 02 	and $r19,$r17,$r19
    2bc8:	00 20 80 2d 	lbi $r2,[$r1+#0x2d]
    2bcc:	41 39 d0 03 	xor $r19,$r19,$r20
    2bd0:	89 83       	add45 $r16,$r3
    2bd2:	89 93       	add45 $r16,$r19
    2bd4:	40 21 20 08 	slli $r2,$r2,#0x8
    2bd8:	41 32 c0 08 	slli $r19,$r5,#0x10
    2bdc:	00 80 80 2c 	lbi $r8,[$r1+#0x2c]
    2be0:	01 90 80 2f 	lbi $r25,[$r1+#0x2f]
    2be4:	41 31 4c 04 	or $r19,$r2,$r19
    2be8:	41 08 64 0b 	rotri $r16,$r16,#0x19
    2bec:	6a 20 00 01 	fmfsr $r2,$fs0
    2bf0:	89 91       	add45 $r16,$r17
    2bf2:	40 38 c8 03 	xor $r3,$r17,$r18
    2bf6:	41 39 a0 04 	or $r19,$r19,$r8
    2bfa:	88 46       	add45 $r2,$r6
    2bfc:	40 38 0c 02 	and $r3,$r16,$r3
    2c00:	40 5c e0 08 	slli $r5,$r25,#0x18
    2c04:	40 59 94 04 	or $r5,$r19,$r5
    2c08:	40 31 c8 03 	xor $r3,$r3,$r18
    2c0c:	41 41 50 00 	add $r20,$r2,$r20
    2c10:	14 50 00 21 	swi $r5,[$r0+#0x84]
    2c14:	41 4a 0c 00 	add $r20,$r20,$r3
    2c18:	00 80 80 31 	lbi $r8,[$r1+#0x31]
    2c1c:	01 30 80 32 	lbi $r19,[$r1+#0x32]
    2c20:	41 4a 50 0b 	rotri $r20,$r20,#0x14
    2c24:	41 4a 40 00 	add $r20,$r20,$r16
    2c28:	40 38 44 03 	xor $r3,$r16,$r17
    2c2c:	44 ef 5b b1 	movi $r14,#-42063
    2c30:	01 90 80 30 	lbi $r25,[$r1+#0x30]
    2c34:	00 20 80 33 	lbi $r2,[$r1+#0x33]
    2c38:	40 e6 38 00 	add $r14,$r12,$r14
    2c3c:	40 3a 0c 02 	and $r3,$r20,$r3
    2c40:	40 84 20 08 	slli $r8,$r8,#0x8
    2c44:	41 39 c0 08 	slli $r19,$r19,#0x10
    2c48:	40 31 c4 03 	xor $r3,$r3,$r17
    2c4c:	89 ce       	add45 $r18,$r14
    2c4e:	41 34 4c 04 	or $r19,$r8,$r19
    2c52:	41 39 e4 04 	or $r19,$r19,$r25
    2c56:	89 c3       	add45 $r18,$r3
    2c58:	40 31 60 08 	slli $r3,$r2,#0x18
    2c5c:	40 e9 8c 04 	or $r14,$r19,$r3
    2c60:	41 29 3c 0b 	rotri $r18,$r18,#0xf
    2c64:	6a 2f 00 01 	fmfsr $r2,$fs30
    2c68:	89 d4       	add45 $r18,$r20
    2c6a:	41 3a 40 03 	xor $r19,$r20,$r16
    2c6e:	14 e0 00 22 	swi $r14,[$r0+#0x88]
    2c72:	00 80 80 35 	lbi $r8,[$r1+#0x35]
    2c76:	88 45       	add45 $r2,$r5
    2c78:	00 30 80 36 	lbi $r3,[$r1+#0x36]
    2c7c:	41 39 4c 02 	and $r19,$r18,$r19
    2c80:	41 39 c0 03 	xor $r19,$r19,$r16
    2c84:	89 a2       	add45 $r17,$r2
    2c86:	01 90 80 37 	lbi $r25,[$r1+#0x37]
    2c8a:	00 20 80 34 	lbi $r2,[$r1+#0x34]
    2c8e:	89 b3       	add45 $r17,$r19
    2c90:	40 84 20 08 	slli $r8,$r8,#0x8
    2c94:	41 31 c0 08 	slli $r19,$r3,#0x10
    2c98:	40 34 4c 04 	or $r3,$r8,$r19
    2c9c:	fe 9f       	or33 $r2,$r3
    2c9e:	40 3c e0 08 	slli $r3,$r25,#0x18
    2ca2:	fe d7       	or33 $r3,$r2
    2ca4:	14 30 00 23 	swi $r3,[$r0+#0x8c]
    2ca8:	01 c0 80 39 	lbi $fp,[$r1+#0x39]
    2cac:	6a 2e 80 01 	fmfsr $r2,$fs29
    2cb0:	41 ce 20 08 	slli $fp,$fp,#0x8
    2cb4:	00 80 80 3a 	lbi $r8,[$r1+#0x3a]
    2cb8:	88 4e       	add45 $r2,$r14
    2cba:	01 90 80 38 	lbi $r25,[$r1+#0x38]
    2cbe:	82 fc       	mov55 $r23,$fp
    2cc0:	89 82       	add45 $r16,$r2
    2cc2:	41 18 a8 0b 	rotri $r17,$r17,#0xa
    2cc6:	00 20 80 3b 	lbi $r2,[$r1+#0x3b]
    2cca:	40 84 40 08 	slli $r8,$r8,#0x10
    2cce:	6b ce 00 01 	fmfsr $fp,$fs28
    2cd2:	89 b2       	add45 $r17,$r18
    2cd4:	41 39 50 03 	xor $r19,$r18,$r20
    2cd8:	40 8b a0 04 	or $r8,$r23,$r8
    2cdc:	41 c1 f0 00 	add $fp,$r3,$fp
    2ce0:	41 94 64 04 	or $r25,$r8,$r25
    2ce4:	41 38 cc 02 	and $r19,$r17,$r19
    2ce8:	40 21 60 08 	slli $r2,$r2,#0x18
    2cec:	41 39 d0 03 	xor $r19,$r19,$r20
    2cf0:	41 4e 50 00 	add $r20,$fp,$r20
    2cf4:	41 cc 88 04 	or $fp,$r25,$r2
    2cf8:	15 c0 00 24 	swi $fp,[$r0+#0x90]
    2cfc:	00 20 80 3d 	lbi $r2,[$r1+#0x3d]
    2d00:	6a 27 80 09 	fmtsr $r2,$fs15
    2d04:	6a 2d 80 01 	fmfsr $r2,$fs27
    2d08:	89 f0       	add45 $r19,$r16
    2d0a:	88 5c       	add45 $r2,$fp
    2d0c:	41 39 e4 0b 	rotri $r19,$r19,#0x19
    2d10:	89 f1       	add45 $r19,$r17
    2d12:	41 08 c8 03 	xor $r16,$r17,$r18
    2d16:	41 09 c0 02 	and $r16,$r19,$r16
    2d1a:	41 08 48 03 	xor $r16,$r16,$r18
    2d1e:	41 4a 40 00 	add $r20,$r20,$r16
    2d22:	41 4a 50 0b 	rotri $r20,$r20,#0x14
    2d26:	41 4a 4c 00 	add $r20,$r20,$r19
    2d2a:	00 80 80 3e 	lbi $r8,[$r1+#0x3e]
    2d2e:	41 09 c4 03 	xor $r16,$r19,$r17
    2d32:	89 c2       	add45 $r18,$r2
    2d34:	6b 77 80 01 	fmfsr $r23,$fs15
    2d38:	41 0a 40 02 	and $r16,$r20,$r16
    2d3c:	01 90 80 3f 	lbi $r25,[$r1+#0x3f]
    2d40:	00 20 80 3c 	lbi $r2,[$r1+#0x3c]
    2d44:	41 08 44 03 	xor $r16,$r16,$r17
    2d48:	40 84 40 08 	slli $r8,$r8,#0x10
    2d4c:	41 7b a0 08 	slli $r23,$r23,#0x8
    2d50:	89 d0       	add45 $r18,$r16
    2d52:	41 0b a0 04 	or $r16,$r23,$r8
    2d56:	40 28 08 04 	or $r2,$r16,$r2
    2d5a:	41 0c e0 08 	slli $r16,$r25,#0x18
    2d5e:	41 91 40 04 	or $r25,$r2,$r16
    2d62:	41 29 3c 0b 	rotri $r18,$r18,#0xf
    2d66:	6a 2d 00 01 	fmfsr $r2,$fs26
    2d6a:	89 d4       	add45 $r18,$r20
    2d6c:	41 0a 4c 03 	xor $r16,$r20,$r19
    2d70:	88 59       	add45 $r2,$r25
    2d72:	41 09 40 02 	and $r16,$r18,$r16
    2d76:	41 08 4c 03 	xor $r16,$r16,$r19
    2d7a:	89 a2       	add45 $r17,$r2
    2d7c:	89 b0       	add45 $r17,$r16
    2d7e:	41 18 a8 0b 	rotri $r17,$r17,#0xa
    2d82:	89 b2       	add45 $r17,$r18
    2d84:	6a 27 00 01 	fmfsr $r2,$fs14
    2d88:	41 08 c8 03 	xor $r16,$r17,$r18
    2d8c:	88 4b       	add45 $r2,$r11
    2d8e:	41 08 50 02 	and $r16,$r16,$r20
    2d92:	89 e2       	add45 $r19,$r2
    2d94:	41 08 48 03 	xor $r16,$r16,$r18
    2d98:	89 93       	add45 $r16,$r19
    2d9a:	41 08 6c 0b 	rotri $r16,$r16,#0x1b
    2d9e:	89 91       	add45 $r16,$r17
    2da0:	6a 26 00 01 	fmfsr $r2,$fs12
    2da4:	41 38 44 03 	xor $r19,$r16,$r17
    2da8:	88 49       	add45 $r2,$r9
    2daa:	41 39 c8 02 	and $r19,$r19,$r18
    2dae:	41 39 c4 03 	xor $r19,$r19,$r17
    2db2:	41 41 50 00 	add $r20,$r2,$r20
    2db6:	41 4a 4c 00 	add $r20,$r20,$r19
    2dba:	41 4a 5c 0b 	rotri $r20,$r20,#0x17
    2dbe:	41 4a 40 00 	add $r20,$r20,$r16
    2dc2:	6a 25 80 01 	fmfsr $r2,$fs11
    2dc6:	41 3a 40 03 	xor $r19,$r20,$r16
    2dca:	88 45       	add45 $r2,$r5
    2dcc:	41 39 c4 02 	and $r19,$r19,$r17
    2dd0:	41 39 c0 03 	xor $r19,$r19,$r16
    2dd4:	89 c2       	add45 $r18,$r2
    2dd6:	89 d3       	add45 $r18,$r19
    2dd8:	41 29 48 0b 	rotri $r18,$r18,#0x12
    2ddc:	89 d4       	add45 $r18,$r20
    2dde:	6a 25 00 01 	fmfsr $r2,$fs10
    2de2:	41 39 50 03 	xor $r19,$r18,$r20
    2de6:	88 58       	add45 $r2,$r24
    2de8:	41 39 c0 02 	and $r19,$r19,$r16
    2dec:	41 39 d0 03 	xor $r19,$r19,$r20
    2df0:	89 a2       	add45 $r17,$r2
    2df2:	89 b3       	add45 $r17,$r19
    2df4:	41 18 b0 0b 	rotri $r17,$r17,#0xc
    2df8:	89 b2       	add45 $r17,$r18
    2dfa:	6a 24 80 01 	fmfsr $r2,$fs9
    2dfe:	41 38 c8 03 	xor $r19,$r17,$r18
    2e02:	88 4f       	add45 $r2,$r15
    2e04:	41 39 d0 02 	and $r19,$r19,$r20
    2e08:	41 39 c8 03 	xor $r19,$r19,$r18
    2e0c:	89 82       	add45 $r16,$r2
    2e0e:	89 93       	add45 $r16,$r19
    2e10:	41 08 6c 0b 	rotri $r16,$r16,#0x1b
    2e14:	89 91       	add45 $r16,$r17
    2e16:	6a 24 00 01 	fmfsr $r2,$fs8
    2e1a:	41 38 44 03 	xor $r19,$r16,$r17
    2e1e:	88 4c       	add45 $r2,$r12
    2e20:	41 39 c8 02 	and $r19,$r19,$r18
    2e24:	41 41 50 00 	add $r20,$r2,$r20
    2e28:	41 39 c4 03 	xor $r19,$r19,$r17
    2e2c:	89 f4       	add45 $r19,$r20
    2e2e:	41 39 dc 0b 	rotri $r19,$r19,#0x17
    2e32:	89 f0       	add45 $r19,$r16
    2e34:	6a 23 80 01 	fmfsr $r2,$fs7
    2e38:	41 49 c0 03 	xor $r20,$r19,$r16
    2e3c:	88 59       	add45 $r2,$r25
    2e3e:	41 4a 44 02 	and $r20,$r20,$r17
    2e42:	41 4a 40 03 	xor $r20,$r20,$r16
    2e46:	89 c2       	add45 $r18,$r2
    2e48:	89 d4       	add45 $r18,$r20
    2e4a:	41 29 48 0b 	rotri $r18,$r18,#0x12
    2e4e:	89 d3       	add45 $r18,$r19
    2e50:	6a 23 00 01 	fmfsr $r2,$fs6
    2e54:	41 49 4c 03 	xor $r20,$r18,$r19
    2e58:	88 44       	add45 $r2,$r4
    2e5a:	41 4a 40 02 	and $r20,$r20,$r16
    2e5e:	41 4a 4c 03 	xor $r20,$r20,$r19
    2e62:	89 a2       	add45 $r17,$r2
    2e64:	89 b4       	add45 $r17,$r20
    2e66:	41 18 b0 0b 	rotri $r17,$r17,#0xc
    2e6a:	89 b2       	add45 $r17,$r18
    2e6c:	46 22 1e 1c 	sethi $r2,#0x21e1c
    2e70:	41 48 c8 03 	xor $r20,$r17,$r18
    2e74:	50 21 0d e6 	addi $r2,$r2,#0xde6
    2e78:	88 46       	add45 $r2,$r6
    2e7a:	41 4a 4c 02 	and $r20,$r20,$r19
    2e7e:	41 4a 48 03 	xor $r20,$r20,$r18
    2e82:	89 82       	add45 $r16,$r2
    2e84:	89 94       	add45 $r16,$r20
    2e86:	41 08 6c 0b 	rotri $r16,$r16,#0x1b
    2e8a:	89 91       	add45 $r16,$r17
    2e8c:	46 2c 33 70 	sethi $r2,#0xc3370
    2e90:	41 48 44 03 	xor $r20,$r16,$r17
    2e94:	50 21 07 d6 	addi $r2,$r2,#0x7d6
    2e98:	88 5c       	add45 $r2,$fp
    2e9a:	41 4a 48 02 	and $r20,$r20,$r18
    2e9e:	89 e2       	add45 $r19,$r2
    2ea0:	41 4a 44 03 	xor $r20,$r20,$r17
    2ea4:	41 49 d0 00 	add $r20,$r19,$r20
    2ea8:	41 4a 5c 0b 	rotri $r20,$r20,#0x17
    2eac:	41 4a 40 00 	add $r20,$r20,$r16
    2eb0:	46 2f 4d 50 	sethi $r2,#0xf4d50
    2eb4:	41 3a 40 03 	xor $r19,$r20,$r16
    2eb8:	50 21 0d 87 	addi $r2,$r2,#0xd87
    2ebc:	88 4d       	add45 $r2,$r13
    2ebe:	41 39 c4 02 	and $r19,$r19,$r17
    2ec2:	89 c2       	add45 $r18,$r2
    2ec4:	41 39 c0 03 	xor $r19,$r19,$r16
    2ec8:	89 f2       	add45 $r19,$r18
    2eca:	41 39 c8 0b 	rotri $r19,$r19,#0x12
    2ece:	89 f4       	add45 $r19,$r20
    2ed0:	46 24 55 a1 	sethi $r2,#0x455a1
    2ed4:	41 29 d0 03 	xor $r18,$r19,$r20
    2ed8:	50 21 04 ed 	addi $r2,$r2,#0x4ed
    2edc:	88 4a       	add45 $r2,$r10
    2ede:	41 29 40 02 	and $r18,$r18,$r16
    2ee2:	89 a2       	add45 $r17,$r2
    2ee4:	41 29 50 03 	xor $r18,$r18,$r20
    2ee8:	89 d1       	add45 $r18,$r17
    2eea:	41 29 30 0b 	rotri $r18,$r18,#0xc
    2eee:	89 d3       	add45 $r18,$r19
    2ef0:	46 2a 9e 3e 	sethi $r2,#0xa9e3e
    2ef4:	41 19 4c 03 	xor $r17,$r18,$r19
    2ef8:	50 21 09 05 	addi $r2,$r2,#0x905
    2efc:	88 43       	add45 $r2,$r3
    2efe:	41 18 d0 02 	and $r17,$r17,$r20
    2f02:	89 82       	add45 $r16,$r2
    2f04:	41 18 cc 03 	xor $r17,$r17,$r19
    2f08:	89 b0       	add45 $r17,$r16
    2f0a:	41 18 ec 0b 	rotri $r17,$r17,#0x1b
    2f0e:	89 b2       	add45 $r17,$r18
    2f10:	46 2f ce fa 	sethi $r2,#0xfcefa
    2f14:	41 08 c8 03 	xor $r16,$r17,$r18
    2f18:	50 21 03 f8 	addi $r2,$r2,#0x3f8
    2f1c:	88 47       	add45 $r2,$r7
    2f1e:	41 08 4c 02 	and $r16,$r16,$r19
    2f22:	41 41 50 00 	add $r20,$r2,$r20
    2f26:	41 08 48 03 	xor $r16,$r16,$r18
    2f2a:	89 94       	add45 $r16,$r20
    2f2c:	41 08 5c 0b 	rotri $r16,$r16,#0x17
    2f30:	89 91       	add45 $r16,$r17
    2f32:	46 26 76 f0 	sethi $r2,#0x676f0
    2f36:	41 48 44 03 	xor $r20,$r16,$r17
    2f3a:	50 21 02 d9 	addi $r2,$r2,#0x2d9
    2f3e:	88 5e       	add45 $r2,$lp
    2f40:	41 4a 48 02 	and $r20,$r20,$r18
    2f44:	41 4a 44 03 	xor $r20,$r20,$r17
    2f48:	89 e2       	add45 $r19,$r2
    2f4a:	89 f4       	add45 $r19,$r20
    2f4c:	41 39 c8 0b 	rotri $r19,$r19,#0x12
    2f50:	89 f0       	add45 $r19,$r16
    2f52:	46 28 d2 a4 	sethi $r2,#0x8d2a4
    2f56:	41 49 c0 03 	xor $r20,$r19,$r16
    2f5a:	50 21 0c 8a 	addi $r2,$r2,#0xc8a
    2f5e:	88 4e       	add45 $r2,$r14
    2f60:	41 4a 44 02 	and $r20,$r20,$r17
    2f64:	41 4a 40 03 	xor $r20,$r20,$r16
    2f68:	89 c2       	add45 $r18,$r2
    2f6a:	89 d4       	add45 $r18,$r20
    2f6c:	41 29 30 0b 	rotri $r18,$r18,#0xc
    2f70:	89 d3       	add45 $r18,$r19
    2f72:	44 2a 39 42 	movi $r2,#-378558
    2f76:	41 49 4c 03 	xor $r20,$r18,$r19
    2f7a:	88 4f       	add45 $r2,$r15
    2f7c:	89 a2       	add45 $r17,$r2
    2f7e:	40 2a 40 03 	xor $r2,$r20,$r16
    2f82:	89 a2       	add45 $r17,$r2
    2f84:	41 18 f0 0b 	rotri $r17,$r17,#0x1c
    2f88:	40 88 c8 00 	add $r8,$r17,$r18
    2f8c:	47 18 77 1f 	sethi $r17,#0x8771f
    2f90:	51 18 86 81 	addi $r17,$r17,#0x681
    2f94:	89 aa       	add45 $r17,$r10
    2f96:	89 91       	add45 $r16,$r17
    2f98:	41 44 50 03 	xor $r20,$r8,$r20
    2f9c:	41 48 50 00 	add $r20,$r16,$r20
    2fa0:	41 4a 54 0b 	rotri $r20,$r20,#0x15
    2fa4:	47 06 d9 d6 	sethi $r16,#0x6d9d6
    2fa8:	41 4a 20 00 	add $r20,$r20,$r8
    2fac:	51 08 01 22 	addi $r16,$r16,#0x122
    2fb0:	41 1a 20 03 	xor $r17,$r20,$r8
    2fb4:	89 85       	add45 $r16,$r5
    2fb6:	89 f0       	add45 $r19,$r16
    2fb8:	41 08 c8 03 	xor $r16,$r17,$r18
    2fbc:	89 f0       	add45 $r19,$r16
    2fbe:	47 0f de 53 	sethi $r16,#0xfde53
    2fc2:	41 39 c0 0b 	rotri $r19,$r19,#0x10
    2fc6:	51 08 08 0c 	addi $r16,$r16,#0x80c
    2fca:	40 29 d0 00 	add $r2,$r19,$r20
    2fce:	89 9c       	add45 $r16,$fp
    2fd0:	41 11 44 03 	xor $r17,$r2,$r17
    2fd4:	89 92       	add45 $r16,$r18
    2fd6:	89 91       	add45 $r16,$r17
    2fd8:	41 08 24 0b 	rotri $r16,$r16,#0x9
    2fdc:	41 38 08 00 	add $r19,$r16,$r2
    2fe0:	47 0a 4b ee 	sethi $r16,#0xa4bee
    2fe4:	51 08 0a 44 	addi $r16,$r16,#0xa44
    2fe8:	41 19 88 03 	xor $r17,$r19,$r2
    2fec:	89 8b       	add45 $r16,$r11
    2fee:	41 28 d0 03 	xor $r18,$r17,$r20
    2ff2:	89 88       	add45 $r16,$r8
    2ff4:	89 92       	add45 $r16,$r18
    2ff6:	41 08 70 0b 	rotri $r16,$r16,#0x1c
    2ffa:	40 88 4c 00 	add $r8,$r16,$r19
    2ffe:	47 04 bd ec 	sethi $r16,#0x4bdec
    3002:	51 08 0f a9 	addi $r16,$r16,#0xfa9
    3006:	89 84       	add45 $r16,$r4
    3008:	41 14 44 03 	xor $r17,$r8,$r17
    300c:	41 48 50 00 	add $r20,$r16,$r20
    3010:	41 4a 44 00 	add $r20,$r20,$r17
    3014:	41 4a 54 0b 	rotri $r20,$r20,#0x15
    3018:	47 0f 6b b4 	sethi $r16,#0xf6bb4
    301c:	41 2a 20 00 	add $r18,$r20,$r8
    3020:	51 08 0b 60 	addi $r16,$r16,#0xb60
    3024:	41 19 20 03 	xor $r17,$r18,$r8
    3028:	89 9e       	add45 $r16,$lp
    302a:	41 48 cc 03 	xor $r20,$r17,$r19
    302e:	89 82       	add45 $r16,$r2
    3030:	89 94       	add45 $r16,$r20
    3032:	41 08 40 0b 	rotri $r16,$r16,#0x10
    3036:	40 28 48 00 	add $r2,$r16,$r18
    303a:	47 0b eb fb 	sethi $r16,#0xbebfb
    303e:	51 08 0c 70 	addi $r16,$r16,#0xc70
    3042:	89 8c       	add45 $r16,$r12
    3044:	41 11 44 03 	xor $r17,$r2,$r17
    3048:	89 93       	add45 $r16,$r19
    304a:	89 91       	add45 $r16,$r17
    304c:	41 08 24 0b 	rotri $r16,$r16,#0x9
    3050:	41 38 08 00 	add $r19,$r16,$r2
    3054:	47 02 89 b7 	sethi $r16,#0x289b7
    3058:	51 08 0e c6 	addi $r16,$r16,#0xec6
    305c:	41 19 88 03 	xor $r17,$r19,$r2
    3060:	89 83       	add45 $r16,$r3
    3062:	41 48 c8 03 	xor $r20,$r17,$r18
    3066:	89 88       	add45 $r16,$r8
    3068:	89 94       	add45 $r16,$r20
    306a:	47 4e aa 12 	sethi $r20,#0xeaa12
    306e:	41 08 70 0b 	rotri $r16,$r16,#0x1c
    3072:	51 4a 07 fa 	addi $r20,$r20,#0x7fa
    3076:	40 88 4c 00 	add $r8,$r16,$r19
    307a:	41 4c 50 00 	add $r20,$r24,$r20
    307e:	41 14 44 03 	xor $r17,$r8,$r17
    3082:	41 4a 48 00 	add $r20,$r20,$r18
    3086:	41 4a 44 00 	add $r20,$r20,$r17
    308a:	41 4a 54 0b 	rotri $r20,$r20,#0x15
    308e:	47 0d 4e f3 	sethi $r16,#0xd4ef3
    3092:	41 1a 20 00 	add $r17,$r20,$r8
    3096:	51 08 00 85 	addi $r16,$r16,#0x85
    309a:	41 28 a0 03 	xor $r18,$r17,$r8
    309e:	89 8d       	add45 $r16,$r13
    30a0:	41 49 4c 03 	xor $r20,$r18,$r19
    30a4:	89 82       	add45 $r16,$r2
    30a6:	89 94       	add45 $r16,$r20
    30a8:	41 08 40 0b 	rotri $r16,$r16,#0x10
    30ac:	40 28 44 00 	add $r2,$r16,$r17
    30b0:	47 00 48 81 	sethi $r16,#0x4881
    30b4:	51 08 0d 05 	addi $r16,$r16,#0xd05
    30b8:	89 89       	add45 $r16,$r9
    30ba:	41 21 48 03 	xor $r18,$r2,$r18
    30be:	89 93       	add45 $r16,$r19
    30c0:	89 92       	add45 $r16,$r18
    30c2:	41 08 24 0b 	rotri $r16,$r16,#0x9
    30c6:	41 38 08 00 	add $r19,$r16,$r2
    30ca:	47 0d 9d 4d 	sethi $r16,#0xd9d4d
    30ce:	51 08 00 39 	addi $r16,$r16,#0x39
    30d2:	41 29 88 03 	xor $r18,$r19,$r2
    30d6:	89 86       	add45 $r16,$r6
    30d8:	41 49 44 03 	xor $r20,$r18,$r17
    30dc:	89 88       	add45 $r16,$r8
    30de:	89 94       	add45 $r16,$r20
    30e0:	47 4e 6d b9 	sethi $r20,#0xe6db9
    30e4:	41 08 70 0b 	rotri $r16,$r16,#0x1c
    30e8:	51 4a 09 e5 	addi $r20,$r20,#0x9e5
    30ec:	40 88 4c 00 	add $r8,$r16,$r19
    30f0:	41 47 50 00 	add $r20,$r14,$r20
    30f4:	41 24 48 03 	xor $r18,$r8,$r18
    30f8:	41 4a 44 00 	add $r20,$r20,$r17
    30fc:	41 4a 48 00 	add $r20,$r20,$r18
    3100:	41 4a 54 0b 	rotri $r20,$r20,#0x15
    3104:	47 11 fa 27 	sethi $r17,#0x1fa27
    3108:	41 4a 20 00 	add $r20,$r20,$r8
    310c:	51 18 8c f8 	addi $r17,$r17,#0xcf8
    3110:	41 2a 20 03 	xor $r18,$r20,$r8
    3114:	89 b9       	add45 $r17,$r25
    3116:	41 09 4c 03 	xor $r16,$r18,$r19
    311a:	89 a2       	add45 $r17,$r2
    311c:	89 b0       	add45 $r17,$r16
    311e:	47 0c 4a c5 	sethi $r16,#0xc4ac5
    3122:	41 18 c0 0b 	rotri $r17,$r17,#0x10
    3126:	51 08 06 65 	addi $r16,$r16,#0x665
    312a:	89 b4       	add45 $r17,$r20
    312c:	89 87       	add45 $r16,$r7
    312e:	41 28 c8 03 	xor $r18,$r17,$r18
    3132:	89 93       	add45 $r16,$r19
    3134:	89 92       	add45 $r16,$r18
    3136:	41 08 24 0b 	rotri $r16,$r16,#0x9
    313a:	47 3f 42 92 	sethi $r19,#0xf4292
    313e:	89 91       	add45 $r16,$r17
    3140:	41 2a 50 05 	nor $r18,$r20,$r20
    3144:	51 39 82 44 	addi $r19,$r19,#0x244
    3148:	41 28 48 04 	or $r18,$r16,$r18
    314c:	89 f8       	add45 $r19,$r24
    314e:	41 29 44 03 	xor $r18,$r18,$r17
    3152:	89 e8       	add45 $r19,$r8
    3154:	89 f2       	add45 $r19,$r18
    3156:	41 39 e8 0b 	rotri $r19,$r19,#0x1a
    315a:	46 84 32 af 	sethi $r8,#0x432af
    315e:	89 f0       	add45 $r19,$r16
    3160:	41 28 c4 05 	nor $r18,$r17,$r17
    3164:	50 84 0f 97 	addi $r8,$r8,#0xf97
    3168:	89 1e       	add45 $r8,$lp
    316a:	41 29 c8 04 	or $r18,$r19,$r18
    316e:	41 29 40 03 	xor $r18,$r18,$r16
    3172:	41 44 50 00 	add $r20,$r8,$r20
    3176:	41 4a 48 00 	add $r20,$r20,$r18
    317a:	41 4a 58 0b 	rotri $r20,$r20,#0x16
    317e:	46 8a b9 42 	sethi $r8,#0xab942
    3182:	41 4a 4c 00 	add $r20,$r20,$r19
    3186:	41 28 40 05 	nor $r18,$r16,$r16
    318a:	50 84 03 a7 	addi $r8,$r8,#0x3a7
    318e:	89 1c       	add45 $r8,$fp
    3190:	41 2a 48 04 	or $r18,$r20,$r18
    3194:	89 a8       	add45 $r17,$r8
    3196:	41 29 4c 03 	xor $r18,$r18,$r19
    319a:	89 d1       	add45 $r18,$r17
    319c:	41 29 44 0b 	rotri $r18,$r18,#0x11
    31a0:	46 8f c9 3a 	sethi $r8,#0xfc93a
    31a4:	89 d4       	add45 $r18,$r20
    31a6:	41 19 cc 05 	nor $r17,$r19,$r19
    31aa:	50 84 00 39 	addi $r8,$r8,#0x39
    31ae:	89 0f       	add45 $r8,$r15
    31b0:	41 19 44 04 	or $r17,$r18,$r17
    31b4:	89 88       	add45 $r16,$r8
    31b6:	41 18 d0 03 	xor $r17,$r17,$r20
    31ba:	89 b0       	add45 $r17,$r16
    31bc:	41 18 ac 0b 	rotri $r17,$r17,#0xb
    31c0:	46 86 55 b5 	sethi $r8,#0x655b5
    31c4:	89 b2       	add45 $r17,$r18
    31c6:	41 0a 50 05 	nor $r16,$r20,$r20
    31ca:	50 84 09 c3 	addi $r8,$r8,#0x9c3
    31ce:	89 0e       	add45 $r8,$r14
    31d0:	41 08 c0 04 	or $r16,$r17,$r16
    31d4:	89 e8       	add45 $r19,$r8
    31d6:	41 08 48 03 	xor $r16,$r16,$r18
    31da:	89 93       	add45 $r16,$r19
    31dc:	41 08 68 0b 	rotri $r16,$r16,#0x1a
    31e0:	46 88 f0 cc 	sethi $r8,#0x8f0cc
    31e4:	89 91       	add45 $r16,$r17
    31e6:	41 39 48 05 	nor $r19,$r18,$r18
    31ea:	50 84 0c 92 	addi $r8,$r8,#0xc92
    31ee:	89 0d       	add45 $r8,$r13
    31f0:	41 38 4c 04 	or $r19,$r16,$r19
    31f4:	41 44 50 00 	add $r20,$r8,$r20
    31f8:	41 39 c4 03 	xor $r19,$r19,$r17
    31fc:	89 f4       	add45 $r19,$r20
    31fe:	41 39 d8 0b 	rotri $r19,$r19,#0x16
    3202:	46 8f fe ff 	sethi $r8,#0xffeff
    3206:	89 f0       	add45 $r19,$r16
    3208:	41 48 c4 05 	nor $r20,$r17,$r17
    320c:	50 84 04 7d 	addi $r8,$r8,#0x47d
    3210:	89 0c       	add45 $r8,$r12
    3212:	41 49 d0 04 	or $r20,$r19,$r20
    3216:	41 4a 40 03 	xor $r20,$r20,$r16
    321a:	89 c8       	add45 $r18,$r8
    321c:	89 d4       	add45 $r18,$r20
    321e:	41 29 44 0b 	rotri $r18,$r18,#0x11
    3222:	46 88 58 45 	sethi $r8,#0x85845
    3226:	89 d3       	add45 $r18,$r19
    3228:	41 48 40 05 	nor $r20,$r16,$r16
    322c:	50 84 0d d1 	addi $r8,$r8,#0xdd1
    3230:	89 0b       	add45 $r8,$r11
    3232:	41 49 50 04 	or $r20,$r18,$r20
    3236:	41 4a 4c 03 	xor $r20,$r20,$r19
    323a:	89 a8       	add45 $r17,$r8
    323c:	89 b4       	add45 $r17,$r20
    323e:	41 18 ac 0b 	rotri $r17,$r17,#0xb
    3242:	46 86 fa 87 	sethi $r8,#0x6fa87
    3246:	89 b2       	add45 $r17,$r18
    3248:	41 49 cc 05 	nor $r20,$r19,$r19
    324c:	50 84 0e 4f 	addi $r8,$r8,#0xe4f
    3250:	89 0a       	add45 $r8,$r10
    3252:	41 48 d0 04 	or $r20,$r17,$r20
    3256:	41 4a 48 03 	xor $r20,$r20,$r18
    325a:	89 88       	add45 $r16,$r8
    325c:	89 94       	add45 $r16,$r20
    325e:	41 08 68 0b 	rotri $r16,$r16,#0x1a
    3262:	46 8f e2 ce 	sethi $r8,#0xfe2ce
    3266:	89 91       	add45 $r16,$r17
    3268:	41 49 48 05 	nor $r20,$r18,$r18
    326c:	50 84 06 e0 	addi $r8,$r8,#0x6e0
    3270:	89 19       	add45 $r8,$r25
    3272:	41 48 50 04 	or $r20,$r16,$r20
    3276:	41 4a 44 03 	xor $r20,$r20,$r17
    327a:	89 e8       	add45 $r19,$r8
    327c:	89 f4       	add45 $r19,$r20
    327e:	41 39 d8 0b 	rotri $r19,$r19,#0x16
    3282:	47 4a 30 14 	sethi $r20,#0xa3014
    3286:	40 89 c0 00 	add $r8,$r19,$r16
    328a:	51 4a 03 14 	addi $r20,$r20,#0x314
    328e:	41 38 c4 05 	nor $r19,$r17,$r17
    3292:	41 44 d0 00 	add $r20,$r9,$r20
    3296:	41 34 4c 04 	or $r19,$r8,$r19
    329a:	41 39 c0 03 	xor $r19,$r19,$r16
    329e:	89 d4       	add45 $r18,$r20
    32a0:	89 d3       	add45 $r18,$r19
    32a2:	41 29 44 0b 	rotri $r18,$r18,#0x11
    32a6:	47 44 e0 81 	sethi $r20,#0x4e081
    32aa:	41 39 20 00 	add $r19,$r18,$r8
    32ae:	51 4a 01 a1 	addi $r20,$r20,#0x1a1
    32b2:	41 28 40 05 	nor $r18,$r16,$r16
    32b6:	88 74       	add45 $r3,$r20
    32b8:	41 29 c8 04 	or $r18,$r19,$r18
    32bc:	89 a3       	add45 $r17,$r3
    32be:	41 29 20 03 	xor $r18,$r18,$r8
    32c2:	89 b2       	add45 $r17,$r18
    32c4:	41 18 ac 0b 	rotri $r17,$r17,#0xb
    32c8:	46 3f 75 37 	sethi $r3,#0xf7537
    32cc:	41 48 cc 00 	add $r20,$r17,$r19
    32d0:	50 31 8e 82 	addi $r3,$r3,#0xe82
    32d4:	41 14 20 05 	nor $r17,$r8,$r8
    32d8:	88 83       	add45 $r4,$r3
    32da:	41 1a 44 04 	or $r17,$r20,$r17
    32de:	89 84       	add45 $r16,$r4
    32e0:	41 18 cc 03 	xor $r17,$r17,$r19
    32e4:	89 91       	add45 $r16,$r17
    32e6:	41 08 68 0b 	rotri $r16,$r16,#0x1a
    32ea:	46 3b d3 af 	sethi $r3,#0xbd3af
    32ee:	41 28 50 00 	add $r18,$r16,$r20
    32f2:	40 49 cc 05 	nor $r4,$r19,$r19
    32f6:	50 31 82 35 	addi $r3,$r3,#0x235
    32fa:	88 65       	add45 $r3,$r5
    32fc:	40 49 10 04 	or $r4,$r18,$r4
    3300:	40 42 50 03 	xor $r4,$r4,$r20
    3304:	88 68       	add45 $r3,$r8
    3306:	88 64       	add45 $r3,$r4
    3308:	40 31 d8 0b 	rotri $r3,$r3,#0x16
    330c:	46 42 ad 7d 	sethi $r4,#0x2ad7d
    3310:	88 72       	add45 $r3,$r18
    3312:	6a 28 80 01 	fmfsr $r2,$fs17
    3316:	40 5a 50 05 	nor $r5,$r20,$r20
    331a:	50 42 02 bb 	addi $r4,$r4,#0x2bb
    331e:	88 87       	add45 $r4,$r7
    3320:	ff 5f       	or33 $r5,$r3
    3322:	40 52 c8 03 	xor $r5,$r5,$r18
    3326:	50 21 7f c0 	addi $r2,$r2,#-64
    332a:	88 93       	add45 $r4,$r19
    332c:	88 85       	add45 $r4,$r5
    332e:	6a 28 80 09 	fmtsr $r2,$fs17
    3332:	6a 2f 80 01 	fmfsr $r2,$fs31
    3336:	40 42 44 0b 	rotri $r4,$r4,#0x11
    333a:	46 5e b8 6d 	sethi $r5,#0xeb86d
    333e:	88 83       	add45 $r4,$r3
    3340:	88 52       	add45 $r2,$r18
    3342:	41 09 48 05 	nor $r16,$r18,$r18
    3346:	50 52 83 91 	addi $r5,$r5,#0x391
    334a:	88 a6       	add45 $r5,$r6
    334c:	41 02 40 04 	or $r16,$r4,$r16
    3350:	6a 2f 80 09 	fmtsr $r2,$fs31
    3354:	6a 29 00 01 	fmfsr $r2,$fs18
    3358:	88 b4       	add45 $r5,$r20
    335a:	41 08 0c 03 	xor $r16,$r16,$r3
    335e:	88 43       	add45 $r2,$r3
    3360:	88 b0       	add45 $r5,$r16
    3362:	40 52 ac 0b 	rotri $r5,$r5,#0xb
    3366:	6a 29 00 09 	fmtsr $r2,$fs18
    336a:	6a 28 80 01 	fmfsr $r2,$fs17
    336e:	88 a4       	add45 $r5,$r4
    3370:	15 90 00 25 	swi $r25,[$r0+#0x94]
    3374:	41 5a 94 00 	add $r21,$r21,$r5
    3378:	41 6b 10 00 	add $r22,$r22,$r4
    337c:	50 10 80 40 	addi $r1,$r1,#0x40
    3380:	4e 23 fa bb 	bnez $r2,28f6 <body+0x14a>
    3384:	33 f0 00 02 	fssi $fs31,[$r0+#0x8]
    3388:	15 50 00 03 	swi $r21,[$r0+#0xc]
    338c:	15 60 00 04 	swi $r22,[$r0+#0x10]
    3390:	33 20 00 05 	fssi $fs18,[$r0+#0x14]
    3394:	80 01       	mov55 $r0,$r1
    3396:	34 3f 90 02 	fldi.bi $fd3,[$sp],#0x8
    339a:	34 4f 90 02 	fldi.bi $fd4,[$sp],#0x8
    339e:	34 5f 90 02 	fldi.bi $fd5,[$sp],#0x8
    33a2:	34 6f 90 02 	fldi.bi $fd6,[$sp],#0x8
    33a6:	34 7f 90 02 	fldi.bi $fd7,[$sp],#0x8
    33aa:	34 8f 90 02 	fldi.bi $fd8,[$sp],#0x8
    33ae:	34 9f 90 03 	fldi.bi $fd9,[$sp],#0xc
    33b2:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    33b6:	dd 9e       	ret5 $lp

000033b8 <MD5_Init>:
    33b8:	46 16 74 52 	sethi $r1,#0x67452
    33bc:	50 10 83 01 	addi $r1,$r1,#0x301
    33c0:	a8 42       	swi333 $r1,[$r0+#0x8]
    33c2:	46 1e fc da 	sethi $r1,#0xefcda
    33c6:	50 10 8b 89 	addi $r1,$r1,#0xb89
    33ca:	a8 43       	swi333 $r1,[$r0+#0xc]
    33cc:	46 19 8b ad 	sethi $r1,#0x98bad
    33d0:	50 10 8c fe 	addi $r1,$r1,#0xcfe
    33d4:	a8 44       	swi333 $r1,[$r0+#0x10]
    33d6:	46 11 03 25 	sethi $r1,#0x10325
    33da:	84 40       	movi55 $r2,#0x0
    33dc:	50 10 84 76 	addi $r1,$r1,#0x476
    33e0:	a8 45       	swi333 $r1,[$r0+#0x14]
    33e2:	b6 40       	swi450 $r2,[$r0]
    33e4:	a8 81       	swi333 $r2,[$r0+#0x4]
    33e6:	dd 9e       	ret5 $lp

000033e8 <MD5_Update>:
    33e8:	3a 6f a8 bc 	smw.adm $r6,[$sp],$r10,#0x2    ! {$r6~$r10, $lp}
    33ec:	b4 60       	lwi450 $r3,[$r0]
    33ee:	80 c0       	mov55 $r6,$r0
    33f0:	99 13       	add333 $r4,$r2,$r3
    33f2:	95 23       	slli333 $r4,$r4,#0x3
    33f4:	92 83       	srli45 $r4,#0x3
    33f6:	e2 83       	slt45 $r4,$r3
    33f8:	80 e2       	mov55 $r7,$r2
    33fa:	81 01       	mov55 $r8,$r1
    33fc:	b6 86       	swi450 $r4,[$r6]
    33fe:	e9 2b       	bnezs8 3454 <MD5_Update+0x6c>
    3400:	a0 31       	lwi333 $r0,[$r6+#0x4]
    3402:	92 00       	nop16
    3404:	40 23 f4 09 	srli $r2,$r7,#0x1d
    3408:	88 40       	add45 $r2,$r0
    340a:	96 ef       	fexti33 $r3,#0x5
    340c:	a8 b1       	swi333 $r2,[$r6+#0x4]
    340e:	50 93 00 18 	addi $r9,$r6,#0x18
    3412:	c3 17       	beqz38 $r3,3440 <MD5_Update+0x58>
    3414:	52 a1 80 40 	subri $r10,$r3,#0x40
    3418:	e2 ea       	slt45 $r7,$r10
    341a:	e9 2b       	bnezs8 3470 <MD5_Update+0x88>
    341c:	50 01 80 18 	addi $r0,$r3,#0x18
    3420:	80 28       	mov55 $r1,$r8
    3422:	80 4a       	mov55 $r2,$r10
    3424:	88 06       	add45 $r0,$r6
    3426:	50 93 00 18 	addi $r9,$r6,#0x18
    342a:	49 00 35 91 	jal 9f4c <memcpy>
    342e:	80 06       	mov55 $r0,$r6
    3430:	80 29       	mov55 $r1,$r9
    3432:	44 20 00 40 	movi $r2,#0x40
    3436:	89 0a       	add45 $r8,$r10
    3438:	40 73 a8 01 	sub $r7,$r7,$r10
    343c:	49 ff f9 b8 	jal 27ac <body>
    3440:	5c f3 80 40 	slti $r15,$r7,#0x40
    3444:	e8 0c       	beqzs8 345c <MD5_Update+0x74>
    3446:	80 09       	mov55 $r0,$r9
    3448:	80 28       	mov55 $r1,$r8
    344a:	80 47       	mov55 $r2,$r7
    344c:	3a 6f a8 84 	lmw.bim $r6,[$sp],$r10,#0x2    ! {$r6~$r10, $lp}
    3450:	48 00 35 7e 	j 9f4c <memcpy>
    3454:	a0 b1       	lwi333 $r2,[$r6+#0x4]
    3456:	9c 11       	addi333 $r0,$r2,#0x1
    3458:	d5 d6       	j8 3404 <MD5_Update+0x1c>
    345a:	92 00       	nop16
    345c:	66 23 80 3f 	bitci $r2,$r7,#0x3f
    3460:	80 28       	mov55 $r1,$r8
    3462:	80 06       	mov55 $r0,$r6
    3464:	49 ff f9 a4 	jal 27ac <body>
    3468:	81 00       	mov55 $r8,$r0
    346a:	97 ef       	fexti33 $r7,#0x5
    346c:	d5 ed       	j8 3446 <MD5_Update+0x5e>
    346e:	92 00       	nop16
    3470:	50 01 80 18 	addi $r0,$r3,#0x18
    3474:	88 06       	add45 $r0,$r6
    3476:	d5 e9       	j8 3448 <MD5_Update+0x60>

00003478 <MD5_Final>:
    3478:	3a 6f a0 bc 	smw.adm $r6,[$sp],$r8,#0x2    ! {$r6~$r8, $lp}
    347c:	b4 61       	lwi450 $r3,[$r1]
    347e:	80 c1       	mov55 $r6,$r1
    3480:	96 ef       	fexti33 $r3,#0x5
    3482:	52 21 80 3f 	subri $r2,$r3,#0x3f
    3486:	99 0b       	add333 $r4,$r1,$r3
    3488:	80 e0       	mov55 $r7,$r0
    348a:	e6 48       	slti45 $r2,#0x8
    348c:	44 0f ff 80 	movi $r0,#-128
    3490:	10 02 00 18 	sbi $r0,[$r4+#0x18]
    3494:	50 01 80 19 	addi $r0,$r3,#0x19
    3498:	e9 69       	bnezs8 356a <MD5_Final+0xf2>
    349a:	50 83 00 18 	addi $r8,$r6,#0x18
    349e:	88 06       	add45 $r0,$r6
    34a0:	52 21 80 37 	subri $r2,$r3,#0x37
    34a4:	84 20       	movi55 $r1,#0x0
    34a6:	49 00 35 87 	jal 9fb4 <memset>
    34aa:	b4 06       	lwi450 $r0,[$r6]
    34ac:	a0 f1       	lwi333 $r3,[$r6+#0x4]
    34ae:	94 03       	slli333 $r0,$r0,#0x3
    34b0:	41 30 20 09 	srli $r19,$r0,#0x8
    34b4:	41 20 40 09 	srli $r18,$r0,#0x10
    34b8:	41 10 60 09 	srli $r17,$r0,#0x18
    34bc:	41 01 a0 09 	srli $r16,$r3,#0x8
    34c0:	40 51 c0 09 	srli $r5,$r3,#0x10
    34c4:	40 41 e0 09 	srli $r4,$r3,#0x18
    34c8:	80 28       	mov55 $r1,$r8
    34ca:	b6 06       	swi450 $r0,[$r6]
    34cc:	10 03 00 50 	sbi $r0,[$r6+#0x50]
    34d0:	10 33 00 54 	sbi $r3,[$r6+#0x54]
    34d4:	44 20 00 40 	movi $r2,#0x40
    34d8:	11 33 00 51 	sbi $r19,[$r6+#0x51]
    34dc:	11 23 00 52 	sbi $r18,[$r6+#0x52]
    34e0:	11 13 00 53 	sbi $r17,[$r6+#0x53]
    34e4:	11 03 00 55 	sbi $r16,[$r6+#0x55]
    34e8:	10 53 00 56 	sbi $r5,[$r6+#0x56]
    34ec:	10 43 00 57 	sbi $r4,[$r6+#0x57]
    34f0:	80 06       	mov55 $r0,$r6
    34f2:	49 ff f9 5d 	jal 27ac <body>
    34f6:	a0 32       	lwi333 $r0,[$r6+#0x8]
    34f8:	ae 38       	sbi333 $r0,[$r7+#0x0]
    34fa:	a0 72       	lwi333 $r1,[$r6+#0x8]
    34fc:	80 06       	mov55 $r0,$r6
    34fe:	92 28       	srli45 $r1,#0x8
    3500:	ae 79       	sbi333 $r1,[$r7+#0x1]
    3502:	a4 75       	lhi333 $r1,[$r6+#0xa]
    3504:	ae 7a       	sbi333 $r1,[$r7+#0x2]
    3506:	00 13 00 0b 	lbi $r1,[$r6+#0xb]
    350a:	ae 7b       	sbi333 $r1,[$r7+#0x3]
    350c:	a0 73       	lwi333 $r1,[$r6+#0xc]
    350e:	ae 7c       	sbi333 $r1,[$r7+#0x4]
    3510:	a0 b3       	lwi333 $r2,[$r6+#0xc]
    3512:	84 20       	movi55 $r1,#0x0
    3514:	92 48       	srli45 $r2,#0x8
    3516:	ae bd       	sbi333 $r2,[$r7+#0x5]
    3518:	a4 b7       	lhi333 $r2,[$r6+#0xe]
    351a:	ae be       	sbi333 $r2,[$r7+#0x6]
    351c:	00 23 00 0f 	lbi $r2,[$r6+#0xf]
    3520:	ae bf       	sbi333 $r2,[$r7+#0x7]
    3522:	a0 b4       	lwi333 $r2,[$r6+#0x10]
    3524:	10 23 80 08 	sbi $r2,[$r7+#0x8]
    3528:	a0 f4       	lwi333 $r3,[$r6+#0x10]
    352a:	44 20 00 98 	movi $r2,#0x98
    352e:	92 68       	srli45 $r3,#0x8
    3530:	10 33 80 09 	sbi $r3,[$r7+#0x9]
    3534:	02 33 00 09 	lhi $r3,[$r6+#0x12]
    3538:	10 33 80 0a 	sbi $r3,[$r7+#0xa]
    353c:	00 33 00 13 	lbi $r3,[$r6+#0x13]
    3540:	10 33 80 0b 	sbi $r3,[$r7+#0xb]
    3544:	a0 f5       	lwi333 $r3,[$r6+#0x14]
    3546:	10 33 80 0c 	sbi $r3,[$r7+#0xc]
    354a:	a0 f5       	lwi333 $r3,[$r6+#0x14]
    354c:	92 68       	srli45 $r3,#0x8
    354e:	10 33 80 0d 	sbi $r3,[$r7+#0xd]
    3552:	02 33 00 0b 	lhi $r3,[$r6+#0x16]
    3556:	10 33 80 0e 	sbi $r3,[$r7+#0xe]
    355a:	00 33 00 17 	lbi $r3,[$r6+#0x17]
    355e:	10 33 80 0f 	sbi $r3,[$r7+#0xf]
    3562:	3a 6f a0 84 	lmw.bim $r6,[$sp],$r8,#0x2    ! {$r6~$r8, $lp}
    3566:	48 00 35 27 	j 9fb4 <memset>
    356a:	84 20       	movi55 $r1,#0x0
    356c:	50 83 00 18 	addi $r8,$r6,#0x18
    3570:	40 00 18 00 	add $r0,$r0,$r6
    3574:	49 00 35 20 	jal 9fb4 <memset>
    3578:	44 20 00 40 	movi $r2,#0x40
    357c:	80 06       	mov55 $r0,$r6
    357e:	80 28       	mov55 $r1,$r8
    3580:	49 ff f9 16 	jal 27ac <body>
    3584:	80 08       	mov55 $r0,$r8
    3586:	44 20 00 38 	movi $r2,#0x38
    358a:	48 ff ff 8d 	j 34a4 <MD5_Final+0x2c>
    358e:	92 00       	nop16

00003590 <lfs_alloc_lookahead>:
    3590:	04 30 00 1a 	lwi $r3,[$r0+#0x68]
    3594:	04 20 00 15 	lwi $r2,[$r0+#0x54]
    3598:	04 31 80 08 	lwi $r3,[$r3+#0x20]
    359c:	04 40 00 16 	lwi $r4,[$r0+#0x58]
    35a0:	9a 9a       	sub333 $r2,$r3,$r2
    35a2:	88 22       	add45 $r1,$r2
    35a4:	40 10 8c 77 	divr $r1,$r3,$r1,$r3
    35a8:	e2 64       	slt45 $r3,$r4
    35aa:	e8 0d       	beqzs8 35c4 <lfs_alloc_lookahead+0x34>
    35ac:	04 00 00 19 	lwi $r0,[$r0+#0x64]
    35b0:	40 21 94 09 	srli $r2,$r3,#0x5
    35b4:	38 40 0a 02 	lw $r4,[$r0+($r2<<#0x2)]
    35b8:	84 21       	movi55 $r1,#0x1
    35ba:	40 30 8c 0c 	sll $r3,$r1,$r3
    35be:	fe e7       	or33 $r3,$r4
    35c0:	38 30 0a 0a 	sw $r3,[$r0+($r2<<#0x2)]
    35c4:	84 00       	movi55 $r0,#0x0
    35c6:	dd 9e       	ret5 $lp

000035c8 <lfs_dir_traverse_filter>:
    35c8:	42 20 f0 0b 	btst $r2,$r1,#0x1c
    35cc:	80 a0       	mov55 $r5,$r0
    35ce:	ca 2d       	bnez38 $r2,3628 <lfs_dir_traverse_filter+0x60>
    35d0:	46 27 00 ff 	sethi $r2,#0x700ff
    35d4:	50 31 0c 00 	addi $r3,$r2,#0xc00
    35d8:	b4 85       	lwi450 $r4,[$r5]
    35da:	84 01       	movi55 $r0,#0x1
    35dc:	40 22 04 03 	xor $r2,$r4,$r1
    35e0:	fe 9e       	and33 $r2,$r3
    35e2:	c2 21       	beqz38 $r2,3624 <lfs_dir_traverse_filter+0x5c>
    35e4:	40 22 58 08 	slli $r2,$r4,#0x16
    35e8:	90 56       	srai45 $r2,#0x16
    35ea:	5a 27 ff 1d 	beqc $r2,#-1,3624 <lfs_dir_traverse_filter+0x5c>
    35ee:	46 20 00 ff 	sethi $r2,#0xff
    35f2:	50 21 0c 00 	addi $r2,$r2,#0xc00
    35f6:	46 37 ff ff 	sethi $r3,#0x7ffff
    35fa:	41 02 08 02 	and $r16,$r4,$r2
    35fe:	50 31 8c 00 	addi $r3,$r3,#0xc00
    3602:	47 14 ff 00 	sethi $r17,#0x4ff00
    3606:	fe ce       	and33 $r3,$r1
    3608:	41 18 44 04 	or $r17,$r16,$r17
    360c:	4c 38 80 0c 	beq $r3,$r17,3624 <lfs_dir_traverse_filter+0x5c>
    3610:	40 30 d0 09 	srli $r3,$r1,#0x14
    3614:	54 31 87 00 	andi $r3,$r3,#0x700
    3618:	45 10 04 00 	movi $r17,#0x400
    361c:	84 00       	movi55 $r0,#0x0
    361e:	4c 38 80 0a 	beq $r3,$r17,3632 <lfs_dir_traverse_filter+0x6a>
    3622:	92 00       	nop16
    3624:	dd 9e       	ret5 $lp
    3626:	92 00       	nop16
    3628:	46 27 ff ff 	sethi $r2,#0x7ffff
    362c:	50 31 0c 00 	addi $r3,$r2,#0xc00
    3630:	d5 d4       	j8 35d8 <lfs_dir_traverse_filter+0x10>
    3632:	fe 8e       	and33 $r2,$r1
    3634:	92 4a       	srli45 $r2,#0xa
    3636:	93 8a       	srli45 $r16,#0xa
    3638:	96 91       	zeh33 $r2,$r2
    363a:	41 08 00 13 	zeh $r16,$r16
    363e:	e3 82       	slt45 $r16,$r2
    3640:	e9 f2       	bnezs8 3624 <lfs_dir_traverse_filter+0x5c>
    3642:	92 34       	srli45 $r1,#0x14
    3644:	96 4a       	seb33 $r1,$r1
    3646:	40 10 a8 08 	slli $r1,$r1,#0xa
    364a:	88 24       	add45 $r1,$r4
    364c:	b6 25       	swi450 $r1,[$r5]
    364e:	dd 9e       	ret5 $lp

00003650 <lfs_dir_commit_size>:
    3650:	40 20 d8 08 	slli $r2,$r1,#0x16
    3654:	90 56       	srai45 $r2,#0x16
    3656:	8c 41       	addi45 $r2,#0x1
    3658:	b4 60       	lwi450 $r3,[$r0]
    365a:	e6 41       	slti45 $r2,#0x1
    365c:	88 2f       	add45 $r1,$r15
    365e:	8c 64       	addi45 $r3,#0x4
    3660:	54 10 83 ff 	andi $r1,$r1,#0x3ff
    3664:	88 23       	add45 $r1,$r3
    3666:	b6 20       	swi450 $r1,[$r0]
    3668:	84 00       	movi55 $r0,#0x0
    366a:	dd 9e       	ret5 $lp

0000366c <lfs_fs_size_count>:
    366c:	b4 20       	lwi450 $r1,[$r0]
    366e:	80 40       	mov55 $r2,$r0
    3670:	8c 21       	addi45 $r1,#0x1
    3672:	84 00       	movi55 $r0,#0x0
    3674:	b6 22       	swi450 $r1,[$r2]
    3676:	dd 9e       	ret5 $lp

00003678 <lfs_deinit>:
    3678:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    367c:	04 10 00 1a 	lwi $r1,[$r0+#0x68]
    3680:	80 c0       	mov55 $r6,$r0
    3682:	04 00 80 0c 	lwi $r0,[$r1+#0x30]
    3686:	c0 15       	beqz38 $r0,36b0 <lfs_deinit+0x38>
    3688:	04 00 80 0d 	lwi $r0,[$r1+#0x34]
    368c:	4e 02 00 19 	beqz $r0,36be <lfs_deinit+0x46>
    3690:	04 00 80 0e 	lwi $r0,[$r1+#0x38]
    3694:	c0 06       	beqz38 $r0,36a0 <lfs_deinit+0x28>
    3696:	84 00       	movi55 $r0,#0x0
    3698:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    369c:	dd 9e       	ret5 $lp
    369e:	92 00       	nop16
    36a0:	04 03 00 19 	lwi $r0,[$r6+#0x64]
    36a4:	49 00 34 2f 	jal 9f02 <free>
    36a8:	84 00       	movi55 $r0,#0x0
    36aa:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    36ae:	dd 9e       	ret5 $lp
    36b0:	04 03 00 03 	lwi $r0,[$r6+#0xc]
    36b4:	49 00 34 27 	jal 9f02 <free>
    36b8:	04 13 00 1a 	lwi $r1,[$r6+#0x68]
    36bc:	d5 e6       	j8 3688 <lfs_deinit+0x10>
    36be:	a0 37       	lwi333 $r0,[$r6+#0x1c]
    36c0:	49 00 34 21 	jal 9f02 <free>
    36c4:	04 13 00 1a 	lwi $r1,[$r6+#0x68]
    36c8:	d5 e4       	j8 3690 <lfs_deinit+0x18>
    36ca:	92 00       	nop16
    36cc:	63 6f 6d 70 	*unknown*
    36d0:	6f 6e 65 6e 	*unknown*
    36d4:	74 73 2f 62 	*unknown*
    36d8:	73 70 2f 73 	*unknown*
    36dc:	6f 63 2f 62 	*unknown*
    36e0:	6f 6f 74 2f 	*unknown*
    36e4:	62 6f 6f 74 	*unknown*
    36e8:	6c 6f 61 64 	*unknown*
    36ec:	65 72 2f 6c 	msync ???
    36f0:	69 74 74 6c 	*unknown*
    36f4:	65 66 73 2f 	isps #0x3399
    36f8:	6f 74 61 5f 	*unknown*
    36fc:	6c 66 73 2e 	*unknown*
    3700:	63 00 00 00 	*unknown*
    3704:	6c 66 73 2d 	*unknown*
    3708:	3e 63 66 67 	sbi.gp $r6,[+#0x36667]
    370c:	2d 3e 72 65 	*unknown*
    3710:	61 64 5f 73 	amtbsl2.l $d1,$r4,$r5,$r6,$r7,[$i3],[$i7],$m0,$m7
    3714:	69 7a 65 20 	*unknown*
    3718:	21 3d 20 30 	lbsi $r19,[$p0+#0x2030]
    371c:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    3720:	6c 66 73 2d 	*unknown*
    3724:	3e 63 66 67 	sbi.gp $r6,[+#0x36667]
    3728:	2d 3e 70 72 	*unknown*
    372c:	6f 67 5f 73 	*unknown*
    3730:	69 7a 65 20 	*unknown*
    3734:	21 3d 20 30 	lbsi $r19,[$p0+#0x2030]
    3738:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    373c:	6c 66 73 2d 	*unknown*
    3740:	3e 63 66 67 	sbi.gp $r6,[+#0x36667]
    3744:	2d 3e 63 61 	*unknown*
    3748:	63 68 65 5f 	*unknown*
    374c:	73 69 7a 65 	*unknown*
    3750:	20 21 3d 20 	lbsi $r2,[$r2+#0x3d20]
    3754:	30 00 00 00 	flsi $fs0,[$r0+#0x0]
    3758:	6c 66 73 2d 	*unknown*
    375c:	3e 63 66 67 	sbi.gp $r6,[+#0x36667]
    3760:	2d 3e 63 61 	*unknown*
    3764:	63 68 65 5f 	*unknown*
    3768:	73 69 7a 65 	*unknown*
    376c:	20 25 20 6c 	lbsi $r2,[$r10+#0x206c]
    3770:	66 73 2d 3e 	bitci $r7,$r6,#0x2d3e
    3774:	63 66 67 2d 	*unknown*
    3778:	3e 72 65 61 	sbi.gp $r7,[+#0x26561]
    377c:	64 5f 73 69 	*unknown*
    3780:	7a 65 20 3d 	*unknown*
    3784:	3d 20 30 00 	lhi.gp $r18,[+#0x6000]
    3788:	6c 66 73 2d 	*unknown*
    378c:	3e 63 66 67 	sbi.gp $r6,[+#0x36667]
    3790:	2d 3e 63 61 	*unknown*
    3794:	63 68 65 5f 	*unknown*
    3798:	73 69 7a 65 	*unknown*
    379c:	20 25 20 6c 	lbsi $r2,[$r10+#0x206c]
    37a0:	66 73 2d 3e 	bitci $r7,$r6,#0x2d3e
    37a4:	63 66 67 2d 	*unknown*
    37a8:	3e 70 72 6f 	sbi.gp $r7,[+#0x726f]
    37ac:	67 5f 73 69 	bitci $r21,$lp,#0x7369
    37b0:	7a 65 20 3d 	*unknown*
    37b4:	3d 20 30 00 	lhi.gp $r18,[+#0x6000]
    37b8:	6c 66 73 2d 	*unknown*
    37bc:	3e 63 66 67 	sbi.gp $r6,[+#0x36667]
    37c0:	2d 3e 62 6c 	*unknown*
    37c4:	6f 63 6b 5f 	*unknown*
    37c8:	73 69 7a 65 	*unknown*
    37cc:	20 25 20 6c 	lbsi $r2,[$r10+#0x206c]
    37d0:	66 73 2d 3e 	bitci $r7,$r6,#0x2d3e
    37d4:	63 66 67 2d 	*unknown*
    37d8:	3e 63 61 63 	sbi.gp $r6,[+#0x36163]
    37dc:	68 65 5f 73 	*unknown*
    37e0:	69 7a 65 20 	*unknown*
    37e4:	3d 3d 20 30 	lwi.gp $r19,[+#-229184]
    37e8:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    37ec:	34 2a 6c 66 	cpldi cp3,$cpr2,[$r20+#-3688]
    37f0:	73 5f 6e 70 	*unknown*
    37f4:	77 32 28 30 	*unknown*
    37f8:	78 66 66 66 	*unknown*
    37fc:	66 66 66 66 	bitci $r6,$r12,#0x6666
    3800:	66 20 2f 20 	bitci $r2,$r0,#0x2f20
    3804:	28 6c 66 73 	lbsi.bi $r6,[$r24],#-6541
    3808:	2d 3e 63 66 	*unknown*
    380c:	67 2d 3e 62 	bitci $r18,$p0,#0x3e62
    3810:	6c 6f 63 6b 	*unknown*
    3814:	5f 73 69 7a 	sltsi $r23,$r6,#-5766
    3818:	65 2d 32 2a 	break #0x6991
    381c:	34 29 29 20 	cpldi cp1,$cpr2,[$r18+#-7040]
    3820:	3c 3d 20 6c 	lwi.gp $r3,[+#-228944]
    3824:	66 73 2d 3e 	bitci $r7,$r6,#0x2d3e
    3828:	63 66 67 2d 	*unknown*
    382c:	3e 62 6c 6f 	sbi.gp $r6,[+#0x26c6f]
    3830:	63 6b 5f 73 	*unknown*
    3834:	69 7a 65 00 	*unknown*
    3838:	6c 66 73 2d 	*unknown*
    383c:	3e 63 66 67 	sbi.gp $r6,[+#0x36667]
    3840:	2d 3e 62 6c 	*unknown*
    3844:	6f 63 6b 5f 	*unknown*
    3848:	63 79 63 6c 	*unknown*
    384c:	65 73 20 21 	cctl $r6,l1d_ix_wb
    3850:	3d 20 30 00 	lhi.gp $r18,[+#0x6000]
    3854:	6c 66 73 2d 	*unknown*
    3858:	3e 63 66 67 	sbi.gp $r6,[+#0x36667]
    385c:	2d 3e 6c 6f 	*unknown*
    3860:	6f 6b 61 68 	*unknown*
    3864:	65 61 64 5f 	*unknown*
    3868:	73 69 7a 65 	*unknown*
    386c:	20 3e 20 30 	lbsi $r3,[$fp+#0x2030]
    3870:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    3874:	6c 66 73 2d 	*unknown*
    3878:	3e 63 66 67 	sbi.gp $r6,[+#0x36667]
    387c:	2d 3e 6c 6f 	*unknown*
    3880:	6f 6b 61 68 	*unknown*
    3884:	65 61 64 5f 	*unknown*
    3888:	73 69 7a 65 	*unknown*
    388c:	20 25 20 38 	lbsi $r2,[$r10+#0x2038]
    3890:	20 3d 3d 20 	lbsi $r3,[$p0+#0x3d20]
    3894:	30 20 26 26 	cplwi cp1,$cpr2,[$r0+#0x1898]
    3898:	20 28 75 69 	lbsi $r2,[$r16+#-2711]
    389c:	6e 74 70 74 	*unknown*
    38a0:	72 5f 74 29 	*unknown*
    38a4:	6c 66 73 2d 	*unknown*
    38a8:	3e 63 66 67 	sbi.gp $r6,[+#0x36667]
    38ac:	2d 3e 6c 6f 	*unknown*
    38b0:	6f 6b 61 68 	*unknown*
    38b4:	65 61 64 5f 	*unknown*
    38b8:	62 75 66 66 	*unknown*
    38bc:	65 72 20 25 	trap #0x1101
    38c0:	20 34 20 3d 	lbsi $r3,[$r8+#0x203d]
    38c4:	3d 20 30 00 	lhi.gp $r18,[+#0x6000]
    38c8:	6c 66 73 2d 	*unknown*
    38cc:	3e 63 66 67 	sbi.gp $r6,[+#0x36667]
    38d0:	2d 3e 6e 61 	*unknown*
    38d4:	6d 65 5f 6d 	*unknown*
    38d8:	61 78 20 3c 	*unknown*
    38dc:	3d 20 32 35 	lhi.gp $r18,[+#0x646a]
    38e0:	35 00 00 00 	fldi $fd16,[$r0+#0x0]
    38e4:	6c 66 73 2d 	*unknown*
    38e8:	3e 63 66 67 	sbi.gp $r6,[+#0x36667]
    38ec:	2d 3e 66 69 	*unknown*
    38f0:	6c 65 5f 6d 	*unknown*
    38f4:	61 78 20 3c 	*unknown*
    38f8:	3d 20 32 31 	lhi.gp $r18,[+#0x6462]
    38fc:	34 37 34 38 	cpldi.bi cp1,$cpr3,[$r14],#0x10e0
    3900:	33 36 34 37 	cpswi.bi cp1,$cpr19,[$r12],#0x10dc
    3904:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    3908:	6c 66 73 2d 	*unknown*
    390c:	3e 63 66 67 	sbi.gp $r6,[+#0x36667]
    3910:	2d 3e 61 74 	*unknown*
    3914:	74 72 5f 6d 	*unknown*
    3918:	61 78 20 3c 	*unknown*
    391c:	3d 20 31 30 	lhi.gp $r18,[+#0x6260]
    3920:	32 32 00 00 	fssi $fs3,[$r4+#0x0]
    3924:	65 72 72 20 	*unknown*
    3928:	3c 3d 20 30 	lwi.gp $r3,[+#-229184]
    392c:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    3930:	25 73 3a 25 	*unknown*
    3934:	64 3a 65 72 	*unknown*
    3938:	72 6f 72 3a 	*unknown*
    393c:	20 43 6f 72 	lbsi $r4,[$r6+#-4238]
    3940:	72 75 70 74 	*unknown*
    3944:	65 64 20 64 	*unknown*
    3948:	69 72 20 70 	*unknown*
    394c:	61 69 72 20 	*unknown*
    3950:	61 74 20 7b 	*unknown*
    3954:	30 78 25 6c 	cplwi cp1,$cpr7,[$r16+#0x15b0]
    3958:	78 2c 20 30 	*unknown*
    395c:	78 25 6c 78 	*unknown*
    3960:	7d 25 73 0a 	*unknown*
    3964:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    3968:	6c 66 73 5f 	*unknown*
    396c:	74 61 67 5f 	*unknown*
    3970:	73 69 7a 65 	*unknown*
    3974:	28 6c 66 73 	lbsi.bi $r6,[$r24],#-6541
    3978:	2d 3e 67 73 	*unknown*
    397c:	74 61 74 65 	*unknown*
    3980:	2e 74 61 67 	lbi.gp $r7,[+#-237209]
    3984:	29 20 3e 20 	lbsi.bi $r18,[$r0],#0x3e20
    3988:	30 20 7c 7c 	cplwi.bi cp3,$cpr2,[$r0],#-3600
    398c:	20 6f 72 70 	lbsi $r6,[$lp+#-3472]
    3990:	68 61 6e 73 	*unknown*
    3994:	20 3e 3d 20 	lbsi $r3,[$fp+#0x3d20]
    3998:	30 00 00 00 	flsi $fs0,[$r0+#0x0]
    399c:	70 63 61 63 	*unknown*
    39a0:	68 65 2d 3e 	*unknown*
    39a4:	62 6c 6f 63 	*unknown*
    39a8:	6b 20 3c 20 	cpe1 cp2,#0x480f0
    39ac:	6c 66 73 2d 	*unknown*
    39b0:	3e 63 66 67 	sbi.gp $r6,[+#0x36667]
    39b4:	2d 3e 62 6c 	*unknown*
    39b8:	6f 63 6b 5f 	*unknown*
    39bc:	63 6f 75 6e 	*unknown*
    39c0:	74 00 00 00 	*unknown*
    39c4:	62 6c 6f 63 	*unknown*
    39c8:	6b 20 3d 3d 	*unknown*
    39cc:	20 28 28 6c 	lbsi $r2,[$r16+#0x286c]
    39d0:	66 73 5f 62 	bitci $r7,$r6,#0x5f62
    39d4:	6c 6f 63 6b 	*unknown*
    39d8:	5f 74 29 2d 	sltsi $r23,$r8,#0x292d
    39dc:	32 29 20 7c 	cpswi cp1,$cpr2,[$r18+#0x1f0]
    39e0:	7c 20 62 6c 	*unknown*
    39e4:	6f 63 6b 20 	*unknown*
    39e8:	3c 20 6c 66 	lhi.gp $r2,[+#0xd8cc]
    39ec:	73 2d 3e 63 	*unknown*
    39f0:	66 67 2d 3e 	bitci $r6,$r14,#0x2d3e
    39f4:	62 6c 6f 63 	*unknown*
    39f8:	6b 5f 63 6f 	*unknown*
    39fc:	75 6e 74 00 	*unknown*
    3a00:	6f 66 66 20 	*unknown*
    3a04:	2b 20 73 69 	lhsi.bi $r18,[$r0],#-6446
    3a08:	7a 65 20 3c 	*unknown*
    3a0c:	3d 20 6c 66 	lhi.gp $r18,[+#0xd8cc]
    3a10:	73 2d 3e 63 	*unknown*
    3a14:	66 67 2d 3e 	bitci $r6,$r14,#0x2d3e
    3a18:	62 6c 6f 63 	*unknown*
    3a1c:	6b 5f 73 69 	mtcpd cp2,$r21,#0xf73
    3a20:	7a 65 00 00 	*unknown*
    3a24:	70 63 61 63 	*unknown*
    3a28:	68 65 2d 3e 	*unknown*
    3a2c:	62 6c 6f 63 	*unknown*
    3a30:	6b 20 3d 3d 	*unknown*
    3a34:	20 28 28 6c 	lbsi $r2,[$r16+#0x286c]
    3a38:	66 73 5f 62 	bitci $r7,$r6,#0x5f62
    3a3c:	6c 6f 63 6b 	*unknown*
    3a40:	5f 74 29 2d 	sltsi $r23,$r8,#0x292d
    3a44:	31 29 00 00 	flsi $fs18,[$r18+#0x0]
    3a48:	2f 00 00 00 	lbi.gp $r16,[+#0x0]
    3a4c:	2e 00 00 00 	lbi.gp $r0,[+#0x0]
    3a50:	2e 2e 00 00 	lbsi.gp $r2,[+#-131072]
    3a54:	66 69 6c 65 	bitci $r6,$r18,#0x6c65
    3a58:	2d 3e 66 6c 	*unknown*
    3a5c:	61 67 73 20 	amtbsl2.s $d1,$r14,$fp,[$i0],[$i4],$m0,$m6
    3a60:	26 20 4c 46 	dprefi.w swr,[$r0+#-52968]
    3a64:	53 5f 46 5f 	subri $r21,$lp,#-14753
    3a68:	4f 50 45 4e 	*unknown*
    3a6c:	45 44 00 00 	movi $r20,#0x40000
    3a70:	6c 69 74 74 	*unknown*
    3a74:	6c 65 66 73 	*unknown*
    3a78:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    3a7c:	25 73 3a 25 	*unknown*
    3a80:	64 3a 65 72 	*unknown*
    3a84:	72 6f 72 3a 	*unknown*
    3a88:	20 49 6e 76 	lbsi $r4,[$r18+#-4490]
    3a8c:	61 6c 69 64 	amtbsl2.l $d0,$r12,$r6,$r4,$r5,[$i0],[$i4],$m1,$m6
    3a90:	20 76 65 72 	lbsi $r7,[$r12+#-6798]
    3a94:	73 69 6f 6e 	*unknown*
    3a98:	20 76 25 75 	lbsi $r7,[$r12+#0x2575]
    3a9c:	2e 25 75 25 	lbi.gp $r2,[+#-166619]
    3aa0:	73 0a 00 00 	*unknown*
    3aa4:	25 73 3a 25 	*unknown*
    3aa8:	64 3a 65 72 	*unknown*
    3aac:	72 6f 72 3a 	*unknown*
    3ab0:	20 55 6e 73 	lbsi $r5,[$r10+#-4493]
    3ab4:	75 70 70 6f 	*unknown*
    3ab8:	72 74 65 64 	*unknown*
    3abc:	20 6e 61 6d 	lbsi $r6,[$fp+#-7827]
    3ac0:	65 5f 6d 61 	cctl $lp,l1d_va_fillck
    3ac4:	78 20 28 25 	*unknown*
    3ac8:	6c 75 20 3e 	*unknown*
    3acc:	20 25 6c 75 	lbsi $r2,[$r10+#-5003]
    3ad0:	29 25 73 0a 	lbsi.bi $r18,[$r10],#-3318
    3ad4:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    3ad8:	25 73 3a 25 	*unknown*
    3adc:	64 3a 65 72 	*unknown*
    3ae0:	72 6f 72 3a 	*unknown*
    3ae4:	20 55 6e 73 	lbsi $r5,[$r10+#-4493]
    3ae8:	75 70 70 6f 	*unknown*
    3aec:	72 74 65 64 	*unknown*
    3af0:	20 66 69 6c 	lbsi $r6,[$r12+#-5780]
    3af4:	65 5f 6d 61 	cctl $lp,l1d_va_fillck
    3af8:	78 20 28 25 	*unknown*
    3afc:	6c 75 20 3e 	*unknown*
    3b00:	20 25 6c 75 	lbsi $r2,[$r10+#-5003]
    3b04:	29 25 73 0a 	lbsi.bi $r18,[$r10],#-3318
    3b08:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    3b0c:	25 73 3a 25 	*unknown*
    3b10:	64 3a 65 72 	*unknown*
    3b14:	72 6f 72 3a 	*unknown*
    3b18:	20 55 6e 73 	lbsi $r5,[$r10+#-4493]
    3b1c:	75 70 70 6f 	*unknown*
    3b20:	72 74 65 64 	*unknown*
    3b24:	20 61 74 74 	lbsi $r6,[$r2+#-2956]
    3b28:	72 5f 6d 61 	*unknown*
    3b2c:	78 20 28 25 	*unknown*
    3b30:	6c 75 20 3e 	*unknown*
    3b34:	20 25 6c 75 	lbsi $r2,[$r10+#-5003]
    3b38:	29 25 73 0a 	lbsi.bi $r18,[$r10],#-3318
    3b3c:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    3b40:	25 73 3a 25 	*unknown*
    3b44:	64 3a 64 65 	trap #0x5323
    3b48:	62 75 67 3a 	*unknown*
    3b4c:	20 46 6f 75 	lbsi $r4,[$r12+#-4235]
    3b50:	6e 64 20 70 	*unknown*
    3b54:	65 6e 64 69 	*unknown*
    3b58:	6e 67 20 67 	*unknown*
    3b5c:	73 74 61 74 	*unknown*
    3b60:	65 20 30 78 	*unknown*
    3b64:	25 30 38 6c 	*unknown*
    3b68:	78 25 30 38 	*unknown*
    3b6c:	6c 78 25 30 	*unknown*
    3b70:	38 6c 78 25 	*unknown*
    3b74:	73 0a 00 00 	*unknown*
    3b78:	25 73 3a 25 	*unknown*
    3b7c:	64 3a 65 72 	*unknown*
    3b80:	72 6f 72 3a 	*unknown*
    3b84:	20 4e 6f 20 	lbsi $r4,[$fp+#-4320]
    3b88:	6d 6f 72 65 	*unknown*
    3b8c:	20 66 72 65 	lbsi $r6,[$r12+#-3483]
    3b90:	65 20 73 70 	bpick $r18,$r0,$fp,$p1
    3b94:	61 63 65 20 	amtbsl2.s $d0,$r6,$r25,[$i0],[$i4],$m0,$m6
    3b98:	25 6c 75 25 	*unknown*
    3b9c:	73 0a 00 00 	*unknown*
    3ba0:	25 73 3a 25 	*unknown*
    3ba4:	64 3a 64 65 	trap #0x5323
    3ba8:	62 75 67 3a 	*unknown*
    3bac:	20 42 61 64 	lbsi $r4,[$r4+#-7836]
    3bb0:	20 62 6c 6f 	lbsi $r6,[$r4+#-5009]
    3bb4:	63 6b 20 61 	*unknown*
    3bb8:	74 20 30 78 	*unknown*
    3bbc:	25 6c 78 25 	*unknown*
    3bc0:	73 0a 00 00 	*unknown*
    3bc4:	28 66 69 6c 	lbsi.bi $r6,[$r12],#-5780
    3bc8:	65 2d 3e 66 	teqz $r18,#0x69f3
    3bcc:	6c 61 67 73 	*unknown*
    3bd0:	20 26 20 33 	lbsi $r2,[$r12+#0x2033]
    3bd4:	29 20 21 3d 	lbsi.bi $r18,[$r0],#0x213d
    3bd8:	20 4c 46 53 	lbsi $r4,[$r24+#-14765]
    3bdc:	5f 4f 5f 52 	sltsi $r20,$lp,#-8366
    3be0:	44 4f 4e 4c 	movi $r4,#-45492
    3be4:	59 00 00 00 	ori $r16,$r0,#0x0
    3be8:	28 66 69 6c 	lbsi.bi $r6,[$r12],#-5780
    3bec:	65 2d 3e 66 	teqz $r18,#0x69f3
    3bf0:	6c 61 67 73 	*unknown*
    3bf4:	20 26 20 33 	lbsi $r2,[$r12+#0x2033]
    3bf8:	29 20 21 3d 	lbsi.bi $r18,[$r0],#0x213d
    3bfc:	20 4c 46 53 	lbsi $r4,[$r24+#-14765]
    3c00:	5f 4f 5f 57 	sltsi $r20,$lp,#-8361
    3c04:	52 4f 4e 4c 	subri $r4,$lp,#-12724
    3c08:	59 00 00 00 	ori $r16,$r0,#0x0
    3c0c:	25 73 3a 25 	*unknown*
    3c10:	64 3a 64 65 	trap #0x5323
    3c14:	62 75 67 3a 	*unknown*
    3c18:	20 45 78 70 	lbsi $r4,[$r10+#-1936]
    3c1c:	61 6e 64 69 	*unknown*
    3c20:	6e 67 20 73 	*unknown*
    3c24:	75 70 65 72 	*unknown*
    3c28:	62 6c 6f 63 	*unknown*
    3c2c:	6b 20 61 74 	cpe2 cp3,#0x48185
    3c30:	20 72 65 76 	lbsi $r7,[$r4+#-6794]
    3c34:	20 25 6c 75 	lbsi $r2,[$r10+#-5003]
    3c38:	25 73 0a 00 	*unknown*
    3c3c:	63 6f 6d 6d 	*unknown*
    3c40:	69 74 2e 6f 	*unknown*
    3c44:	66 66 20 25 	bitci $r6,$r12,#0x2025
    3c48:	20 6c 66 73 	lbsi $r6,[$r24+#-6541]
    3c4c:	2d 3e 63 66 	*unknown*
    3c50:	67 2d 3e 70 	bitci $r18,$p0,#0x3e70
    3c54:	72 6f 67 5f 	*unknown*
    3c58:	73 69 7a 65 	*unknown*
    3c5c:	20 3d 3d 20 	lbsi $r3,[$p0+#0x3d20]
    3c60:	30 00 00 00 	flsi $fs0,[$r0+#0x0]
    3c64:	25 73 3a 25 	*unknown*
    3c68:	64 3a 64 65 	trap #0x5323
    3c6c:	62 75 67 3a 	*unknown*
    3c70:	20 46 69 78 	lbsi $r4,[$r12+#-5768]
    3c74:	69 6e 67 20 	*unknown*
    3c78:	6d 6f 76 65 	*unknown*
    3c7c:	20 77 68 69 	lbsi $r7,[$r14+#-6039]
    3c80:	6c 65 20 72 	*unknown*
    3c84:	65 6c 6f 63 	mtsr $r22,795
    3c88:	61 74 69 6e 	amttsl2.l $d0,$r4,$r6,$r4,$r5,[$i2],[$i6],$m3,$m6
    3c8c:	67 20 7b 30 	bitci $r18,$r0,#0x7b30
    3c90:	78 25 6c 78 	*unknown*
    3c94:	2c 20 30 78 	*unknown*
    3c98:	25 6c 78 7d 	*unknown*
    3c9c:	20 30 78 25 	lbsi $r3,[$r0+#-2011]
    3ca0:	78 0a 25 73 	*unknown*
    3ca4:	0a 00 00 00 	lhi.bi $r0,[$r0],#0x0
    3ca8:	25 73 3a 25 	*unknown*
    3cac:	64 3a 64 65 	trap #0x5323
    3cb0:	62 75 67 3a 	*unknown*
    3cb4:	20 52 65 6c 	lbsi $r5,[$r4+#-6804]
    3cb8:	6f 63 61 74 	*unknown*
    3cbc:	69 6e 67 20 	*unknown*
    3cc0:	7b 30 78 25 	*unknown*
    3cc4:	6c 78 2c 20 	*unknown*
    3cc8:	30 78 25 6c 	cplwi cp1,$cpr7,[$r16+#0x15b0]
    3ccc:	78 7d 20 2d 	*unknown*
    3cd0:	3e 20 7b 30 	sbi.gp $r2,[+#0x7b30]
    3cd4:	78 25 6c 78 	*unknown*
    3cd8:	2c 20 30 78 	*unknown*
    3cdc:	25 6c 78 7d 	*unknown*
    3ce0:	25 73 0a 00 	*unknown*
    3ce4:	25 73 3a 25 	*unknown*
    3ce8:	64 3a 77 61 	cctl $r20,l1i_va_fillck
    3cec:	72 6e 3a 20 	*unknown*
    3cf0:	53 75 70 65 	subri $r23,$r10,#-3995
    3cf4:	72 62 6c 6f 	*unknown*
    3cf8:	63 6b 20 30 	*unknown*
    3cfc:	78 25 6c 78 	*unknown*
    3d00:	20 68 61 73 	lbsi $r6,[$r16+#-7821]
    3d04:	20 62 65 63 	lbsi $r6,[$r4+#-6813]
    3d08:	6f 6d 65 20 	*unknown*
    3d0c:	75 6e 77 72 	*unknown*
    3d10:	69 74 61 62 	*unknown*
    3d14:	6c 65 25 73 	*unknown*
    3d18:	0a 00 00 00 	lhi.bi $r0,[$r0],#0x0
    3d1c:	64 69 72 2d 	isync $r6
    3d20:	3e 63 6f 75 	sbi.gp $r6,[+#0x36f75]
    3d24:	6e 74 20 3e 	*unknown*
    3d28:	20 30 00 00 	lbsi $r3,[$r0+#0x0]
    3d2c:	25 73 3a 25 	*unknown*
    3d30:	64 3a 64 65 	trap #0x5323
    3d34:	62 75 67 3a 	*unknown*
    3d38:	20 46 69 78 	lbsi $r4,[$r12+#-5768]
    3d3c:	69 6e 67 20 	*unknown*
    3d40:	6d 6f 76 65 	*unknown*
    3d44:	20 7b 30 78 	lbsi $r7,[$r22+#0x3078]
    3d48:	25 6c 78 2c 	*unknown*
    3d4c:	20 30 78 25 	lbsi $r3,[$r0+#-2011]
    3d50:	6c 78 7d 20 	*unknown*
    3d54:	30 78 25 78 	cplwi cp1,$cpr7,[$r16+#0x15e0]
    3d58:	25 73 0a 00 	*unknown*
    3d5c:	25 73 3a 25 	*unknown*
    3d60:	64 3a 64 65 	trap #0x5323
    3d64:	62 75 67 3a 	*unknown*
    3d68:	20 46 69 78 	lbsi $r4,[$r12+#-5768]
    3d6c:	69 6e 67 20 	*unknown*
    3d70:	6f 72 70 68 	*unknown*
    3d74:	61 6e 20 7b 	*unknown*
    3d78:	30 78 25 6c 	cplwi cp1,$cpr7,[$r16+#0x15b0]
    3d7c:	78 2c 20 30 	*unknown*
    3d80:	78 25 6c 78 	*unknown*
    3d84:	7d 25 73 0a 	*unknown*
    3d88:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    3d8c:	25 73 3a 25 	*unknown*
    3d90:	64 3a 64 65 	trap #0x5323
    3d94:	62 75 67 3a 	*unknown*
    3d98:	20 46 69 78 	lbsi $r4,[$r12+#-5768]
    3d9c:	69 6e 67 20 	*unknown*
    3da0:	68 61 6c 66 	*unknown*
    3da4:	2d 6f 72 70 	*unknown*
    3da8:	68 61 6e 20 	*unknown*
    3dac:	7b 30 78 25 	*unknown*
    3db0:	6c 78 2c 20 	*unknown*
    3db4:	30 78 25 6c 	cplwi cp1,$cpr7,[$r16+#0x15b0]
    3db8:	78 7d 20 2d 	*unknown*
    3dbc:	3e 20 7b 30 	sbi.gp $r2,[+#0x7b30]
    3dc0:	78 25 6c 78 	*unknown*
    3dc4:	2c 20 30 78 	*unknown*
    3dc8:	25 6c 78 7d 	*unknown*
    3dcc:	25 73 0a 00 	*unknown*

00003dd0 <lfs_init>:
    3dd0:	3a 6f a0 bc 	smw.adm $r6,[$sp],$r8,#0x2    ! {$r6~$r8, $lp}
    3dd4:	a0 cd       	lwi333 $r3,[$r1+#0x14]
    3dd6:	80 c0       	mov55 $r6,$r0
    3dd8:	14 10 00 1a 	swi $r1,[$r0+#0x68]
    3ddc:	4e 32 01 1a 	beqz $r3,4010 <lfs_init+0x240>
    3de0:	a1 0e       	lwi333 $r4,[$r1+#0x18]
    3de2:	4e 42 01 47 	beqz $r4,4070 <lfs_init+0x2a0>
    3de6:	04 20 80 0a 	lwi $r2,[$r1+#0x28]
    3dea:	4e 22 01 2b 	beqz $r2,4040 <lfs_init+0x270>
    3dee:	40 01 0c 77 	divr $r0,$r3,$r2,$r3
    3df2:	4e 33 00 eb 	bnez $r3,3fc8 <lfs_init+0x1f8>
    3df6:	40 01 10 97 	divr $r0,$r4,$r2,$r4
    3dfa:	4e 43 00 ff 	bnez $r4,3ff8 <lfs_init+0x228>
    3dfe:	a0 0f       	lwi333 $r0,[$r1+#0x1c]
    3e00:	40 40 08 77 	divr $r4,$r3,$r0,$r2
    3e04:	4e 33 00 ca 	bnez $r3,3f98 <lfs_init+0x1c8>
    3e08:	50 30 7f f8 	addi $r3,$r0,#-8
    3e0c:	84 9f       	movi55 $r4,#-1
    3e0e:	40 32 0c 77 	divr $r3,$r3,$r4,$r3
    3e12:	8e 61       	subi45 $r3,#0x1
    3e14:	42 31 80 07 	clz $r3,$r3
    3e18:	52 31 80 20 	subri $r3,$r3,#0x20
    3e1c:	94 da       	slli333 $r3,$r3,#0x2
    3e1e:	e2 03       	slt45 $r0,$r3
    3e20:	4e f3 00 b0 	bnez $r15,3f80 <lfs_init+0x1b0>
    3e24:	04 00 80 09 	lwi $r0,[$r1+#0x24]
    3e28:	4e 02 00 dc 	beqz $r0,3fe0 <lfs_init+0x210>
    3e2c:	04 00 80 0c 	lwi $r0,[$r1+#0x30]
    3e30:	4e 02 00 82 	beqz $r0,3f34 <lfs_init+0x164>
    3e34:	a8 33       	swi333 $r0,[$r6+#0xc]
    3e36:	92 00       	nop16
    3e38:	04 00 80 0d 	lwi $r0,[$r1+#0x34]
    3e3c:	4e 02 00 71 	beqz $r0,3f1e <lfs_init+0x14e>
    3e40:	14 03 00 07 	swi $r0,[$r6+#0x1c]
    3e44:	44 10 00 ff 	movi $r1,#0xff
    3e48:	a0 33       	lwi333 $r0,[$r6+#0xc]
    3e4a:	49 00 30 b5 	jal 9fb4 <memset>
    3e4e:	84 ff       	movi55 $r7,#-1
    3e50:	04 23 00 1a 	lwi $r2,[$r6+#0x68]
    3e54:	b6 e6       	swi450 $r7,[$r6]
    3e56:	44 10 00 ff 	movi $r1,#0xff
    3e5a:	a0 37       	lwi333 $r0,[$r6+#0x1c]
    3e5c:	04 21 00 0a 	lwi $r2,[$r2+#0x28]
    3e60:	49 00 30 aa 	jal 9fb4 <memset>
    3e64:	04 13 00 1a 	lwi $r1,[$r6+#0x68]
    3e68:	a9 f4       	swi333 $r7,[$r6+#0x10]
    3e6a:	04 00 80 0b 	lwi $r0,[$r1+#0x2c]
    3e6e:	4e 02 00 f5 	beqz $r0,4058 <lfs_init+0x288>
    3e72:	54 20 00 07 	andi $r2,$r0,#0x7
    3e76:	4e 23 00 79 	bnez $r2,3f68 <lfs_init+0x198>
    3e7a:	04 20 80 0e 	lwi $r2,[$r1+#0x38]
    3e7e:	54 31 00 03 	andi $r3,$r2,#0x3
    3e82:	4e 33 00 73 	bnez $r3,3f68 <lfs_init+0x198>
    3e86:	c2 63       	beqz38 $r2,3f4c <lfs_init+0x17c>
    3e88:	14 23 00 19 	swi $r2,[$r6+#0x64]
    3e8c:	04 00 80 0f 	lwi $r0,[$r1+#0x3c]
    3e90:	5c f0 01 00 	slti $r15,$r0,#0x100
    3e94:	4e f2 00 8e 	beqz $r15,3fb0 <lfs_init+0x1e0>
    3e98:	4e 02 00 3a 	beqz $r0,3f0c <lfs_init+0x13c>
    3e9c:	14 03 00 1b 	swi $r0,[$r6+#0x6c]
    3ea0:	04 00 80 10 	lwi $r0,[$r1+#0x40]
    3ea4:	4e 05 00 f2 	bltz $r0,4088 <lfs_init+0x2b8>
    3ea8:	4e 02 00 36 	beqz $r0,3f14 <lfs_init+0x144>
    3eac:	14 03 00 1c 	swi $r0,[$r6+#0x70]
    3eb0:	04 00 80 11 	lwi $r0,[$r1+#0x44]
    3eb4:	5c f0 03 ff 	slti $r15,$r0,#0x3ff
    3eb8:	4e f2 00 b8 	beqz $r15,4028 <lfs_init+0x258>
    3ebc:	c8 03       	bnez38 $r0,3ec2 <lfs_init+0xf2>
    3ebe:	44 00 03 fe 	movi $r0,#0x3fe
    3ec2:	84 7f       	movi55 $r3,#-1
    3ec4:	14 03 00 1d 	swi $r0,[$r6+#0x74]
    3ec8:	84 00       	movi55 $r0,#0x0
    3eca:	14 33 00 08 	swi $r3,[$r6+#0x20]
    3ece:	14 33 00 09 	swi $r3,[$r6+#0x24]
    3ed2:	84 20       	movi55 $r1,#0x0
    3ed4:	84 4c       	movi55 $r2,#0xc
    3ed6:	14 03 00 0a 	swi $r0,[$r6+#0x28]
    3eda:	14 03 00 0b 	swi $r0,[$r6+#0x2c]
    3ede:	50 03 00 3c 	addi $r0,$r6,#0x3c
    3ee2:	49 00 30 69 	jal 9fb4 <memset>
    3ee6:	84 20       	movi55 $r1,#0x0
    3ee8:	44 20 00 0c 	movi $r2,#0xc
    3eec:	50 03 00 30 	addi $r0,$r6,#0x30
    3ef0:	49 00 30 62 	jal 9fb4 <memset>
    3ef4:	50 03 00 48 	addi $r0,$r6,#0x48
    3ef8:	84 20       	movi55 $r1,#0x0
    3efa:	84 4c       	movi55 $r2,#0xc
    3efc:	49 00 30 5c 	jal 9fb4 <memset>
    3f00:	84 00       	movi55 $r0,#0x0
    3f02:	92 00       	nop16
    3f04:	3a 6f a0 84 	lmw.bim $r6,[$sp],$r8,#0x2    ! {$r6~$r8, $lp}
    3f08:	dd 9e       	ret5 $lp
    3f0a:	92 00       	nop16
    3f0c:	44 00 00 ff 	movi $r0,#0xff
    3f10:	48 ff ff c6 	j 3e9c <lfs_init+0xcc>
    3f14:	46 07 ff ff 	sethi $r0,#0x7ffff
    3f18:	50 00 0f ff 	addi $r0,$r0,#0xfff
    3f1c:	d5 c8       	j8 3eac <lfs_init+0xdc>
    3f1e:	80 02       	mov55 $r0,$r2
    3f20:	49 00 2f ea 	jal 9ef4 <malloc>
    3f24:	a8 37       	swi333 $r0,[$r6+#0x1c]
    3f26:	c0 1c       	beqz38 $r0,3f5e <lfs_init+0x18e>
    3f28:	04 03 00 1a 	lwi $r0,[$r6+#0x68]
    3f2c:	04 20 00 0a 	lwi $r2,[$r0+#0x28]
    3f30:	48 ff ff 8a 	j 3e44 <lfs_init+0x74>
    3f34:	80 02       	mov55 $r0,$r2
    3f36:	49 00 2f df 	jal 9ef4 <malloc>
    3f3a:	a8 33       	swi333 $r0,[$r6+#0xc]
    3f3c:	c0 11       	beqz38 $r0,3f5e <lfs_init+0x18e>
    3f3e:	04 13 00 1a 	lwi $r1,[$r6+#0x68]
    3f42:	04 20 80 0a 	lwi $r2,[$r1+#0x28]
    3f46:	48 ff ff 79 	j 3e38 <lfs_init+0x68>
    3f4a:	92 00       	nop16
    3f4c:	49 00 2f d4 	jal 9ef4 <malloc>
    3f50:	14 03 00 19 	swi $r0,[$r6+#0x64]
    3f54:	c0 05       	beqz38 $r0,3f5e <lfs_init+0x18e>
    3f56:	04 13 00 1a 	lwi $r1,[$r6+#0x68]
    3f5a:	48 ff ff 99 	j 3e8c <lfs_init+0xbc>
    3f5e:	80 06       	mov55 $r0,$r6
    3f60:	49 ff fb 8c 	jal 3678 <lfs_deinit>
    3f64:	84 14       	movi55 $r0,#-12
    3f66:	d5 cf       	j8 3f04 <lfs_init+0x134>
    3f68:	44 00 36 cc 	movi $r0,#0x36cc
    3f6c:	44 10 0d c1 	movi $r1,#0xdc1
    3f70:	44 20 7b d4 	movi $r2,#0x7bd4
    3f74:	44 30 38 74 	movi $r3,#0x3874
    3f78:	49 00 2e 4e 	jal 9c14 <__assert_func>
    3f7c:	92 00       	nop16
    3f7e:	92 00       	nop16
    3f80:	44 00 36 cc 	movi $r0,#0x36cc
    3f84:	44 10 0d 99 	movi $r1,#0xd99
    3f88:	44 20 7b d4 	movi $r2,#0x7bd4
    3f8c:	44 30 37 ec 	movi $r3,#0x37ec
    3f90:	49 00 2e 42 	jal 9c14 <__assert_func>
    3f94:	92 00       	nop16
    3f96:	92 00       	nop16
    3f98:	44 00 36 cc 	movi $r0,#0x36cc
    3f9c:	44 10 0d 95 	movi $r1,#0xd95
    3fa0:	44 20 7b d4 	movi $r2,#0x7bd4
    3fa4:	44 30 37 b8 	movi $r3,#0x37b8
    3fa8:	49 00 2e 36 	jal 9c14 <__assert_func>
    3fac:	92 00       	nop16
    3fae:	92 00       	nop16
    3fb0:	44 00 36 cc 	movi $r0,#0x36cc
    3fb4:	44 10 0d cd 	movi $r1,#0xdcd
    3fb8:	44 20 7b d4 	movi $r2,#0x7bd4
    3fbc:	44 30 38 c8 	movi $r3,#0x38c8
    3fc0:	49 00 2e 2a 	jal 9c14 <__assert_func>
    3fc4:	92 00       	nop16
    3fc6:	92 00       	nop16
    3fc8:	44 00 36 cc 	movi $r0,#0x36cc
    3fcc:	44 10 0d 93 	movi $r1,#0xd93
    3fd0:	44 20 7b d4 	movi $r2,#0x7bd4
    3fd4:	44 30 37 58 	movi $r3,#0x3758
    3fd8:	49 00 2e 1e 	jal 9c14 <__assert_func>
    3fdc:	92 00       	nop16
    3fde:	92 00       	nop16
    3fe0:	44 00 36 cc 	movi $r0,#0x36cc
    3fe4:	44 10 0d a1 	movi $r1,#0xda1
    3fe8:	44 20 7b d4 	movi $r2,#0x7bd4
    3fec:	44 30 38 38 	movi $r3,#0x3838
    3ff0:	49 00 2e 12 	jal 9c14 <__assert_func>
    3ff4:	92 00       	nop16
    3ff6:	92 00       	nop16
    3ff8:	44 00 36 cc 	movi $r0,#0x36cc
    3ffc:	44 10 0d 94 	movi $r1,#0xd94
    4000:	44 20 7b d4 	movi $r2,#0x7bd4
    4004:	44 30 37 88 	movi $r3,#0x3788
    4008:	49 00 2e 06 	jal 9c14 <__assert_func>
    400c:	92 00       	nop16
    400e:	92 00       	nop16
    4010:	44 00 36 cc 	movi $r0,#0x36cc
    4014:	44 10 0d 8d 	movi $r1,#0xd8d
    4018:	44 20 7b d4 	movi $r2,#0x7bd4
    401c:	44 30 37 04 	movi $r3,#0x3704
    4020:	49 00 2d fa 	jal 9c14 <__assert_func>
    4024:	92 00       	nop16
    4026:	92 00       	nop16
    4028:	44 00 36 cc 	movi $r0,#0x36cc
    402c:	44 10 0d d9 	movi $r1,#0xdd9
    4030:	44 20 7b d4 	movi $r2,#0x7bd4
    4034:	44 30 39 08 	movi $r3,#0x3908
    4038:	49 00 2d ee 	jal 9c14 <__assert_func>
    403c:	92 00       	nop16
    403e:	92 00       	nop16
    4040:	44 00 36 cc 	movi $r0,#0x36cc
    4044:	44 10 0d 8f 	movi $r1,#0xd8f
    4048:	44 20 7b d4 	movi $r2,#0x7bd4
    404c:	44 30 37 3c 	movi $r3,#0x373c
    4050:	49 00 2d e2 	jal 9c14 <__assert_func>
    4054:	92 00       	nop16
    4056:	92 00       	nop16
    4058:	44 00 36 cc 	movi $r0,#0x36cc
    405c:	44 10 0d bf 	movi $r1,#0xdbf
    4060:	44 20 7b d4 	movi $r2,#0x7bd4
    4064:	44 30 38 54 	movi $r3,#0x3854
    4068:	49 00 2d d6 	jal 9c14 <__assert_func>
    406c:	92 00       	nop16
    406e:	92 00       	nop16
    4070:	44 00 36 cc 	movi $r0,#0x36cc
    4074:	44 10 0d 8e 	movi $r1,#0xd8e
    4078:	44 20 7b d4 	movi $r2,#0x7bd4
    407c:	44 30 37 20 	movi $r3,#0x3720
    4080:	49 00 2d ca 	jal 9c14 <__assert_func>
    4084:	92 00       	nop16
    4086:	92 00       	nop16
    4088:	44 00 36 cc 	movi $r0,#0x36cc
    408c:	44 10 0d d3 	movi $r1,#0xdd3
    4090:	44 20 7b d4 	movi $r2,#0x7bd4
    4094:	44 30 38 e4 	movi $r3,#0x38e4
    4098:	49 00 2d be 	jal 9c14 <__assert_func>
    409c:	92 00       	nop16
    409e:	92 00       	nop16

000040a0 <lfs_bd_read.isra.13>:
    40a0:	3a 6f b8 bc 	smw.adm $r6,[$sp],$r14,#0x2    ! {$r6~$r14, $lp}
    40a4:	b5 80       	lwi450 $r16,[$r0]
    40a6:	81 80       	mov55 $r12,$r0
    40a8:	04 08 00 08 	lwi $r0,[$r16+#0x20]
    40ac:	81 24       	mov55 $r9,$r4
    40ae:	e2 80       	slt45 $r4,$r0
    40b0:	f6 0a       	lwi37.sp $r6,[+#0x28]
    40b2:	04 af 80 0b 	lwi $r10,[$sp+#0x2c]
    40b6:	4e f2 00 9d 	beqz $r15,41f0 <lfs_bd_read.isra.13+0x150>
    40ba:	04 08 00 07 	lwi $r0,[$r16+#0x1c]
    40be:	81 a1       	mov55 $r13,$r1
    40c0:	40 12 a8 00 	add $r1,$r5,$r10
    40c4:	e2 01       	slt45 $r0,$r1
    40c6:	80 e5       	mov55 $r7,$r5
    40c8:	4e f3 00 94 	bnez $r15,41f0 <lfs_bd_read.isra.13+0x150>
    40cc:	81 02       	mov55 $r8,$r2
    40ce:	81 63       	mov55 $r11,$r3
    40d0:	4e a3 00 36 	bnez $r10,413c <lfs_bd_read.isra.13+0x9c>
    40d4:	d5 60       	j8 4194 <lfs_bd_read.isra.13+0xf4>
    40d6:	b4 0c       	lwi450 $r0,[$r12]
    40d8:	04 e0 00 05 	lwi $r14,[$r0+#0x14]
    40dc:	40 33 b8 37 	divr $r3,$r1,$r7,$r14
    40e0:	c9 04       	bnez38 $r1,40e8 <lfs_bd_read.isra.13+0x48>
    40e2:	e3 4e       	slt45 $r10,$r14
    40e4:	4e f2 00 5e 	beqz $r15,41a0 <lfs_bd_read.isra.13+0x100>
    40e8:	04 20 00 08 	lwi $r2,[$r0+#0x20]
    40ec:	e3 22       	slt45 $r9,$r2
    40ee:	4e f2 00 85 	beqz $r15,41f8 <lfs_bd_read.isra.13+0x158>
    40f2:	05 10 00 05 	lwi $r17,[$r0+#0x14]
    40f6:	a1 07       	lwi333 $r4,[$r0+#0x1c]
    40f8:	51 08 ff ff 	addi $r16,$r17,#-1
    40fc:	89 8b       	add45 $r16,$r11
    40fe:	89 87       	add45 $r16,$r7
    4100:	40 28 44 37 	divr $r2,$r1,$r16,$r17
    4104:	41 13 c4 57 	divr $r17,$r2,$r7,$r17
    4108:	8b 81       	sub45 $r16,$r1
    410a:	e2 90       	slt45 $r4,$r16
    410c:	04 50 00 0a 	lwi $r5,[$r0+#0x28]
    4110:	9a ba       	sub333 $r2,$r7,$r2
    4112:	41 02 3c 1b 	cmovn $r16,$r4,$r15
    4116:	8b 82       	sub45 $r16,$r2
    4118:	e2 b0       	slt45 $r5,$r16
    411a:	40 58 3c 1a 	cmovz $r5,$r16,$r15
    411e:	80 85       	mov55 $r4,$r5
    4120:	a1 41       	lwi333 $r5,[$r0+#0x4]
    4122:	80 29       	mov55 $r1,$r9
    4124:	b7 28       	swi450 $r9,[$r8]
    4126:	14 24 00 01 	swi $r2,[$r8+#0x4]
    412a:	14 44 00 02 	swi $r4,[$r8+#0x8]
    412e:	04 34 00 03 	lwi $r3,[$r8+#0xc]
    4132:	dd 25       	jral5 $r5
    4134:	4e 06 00 6e 	bgtz $r0,4210 <lfs_bd_read.isra.13+0x170>
    4138:	c8 30       	bnez38 $r0,4198 <lfs_bd_read.isra.13+0xf8>
    413a:	92 00       	nop16
    413c:	4e d2 00 1c 	beqz $r13,4174 <lfs_bd_read.isra.13+0xd4>
    4140:	b4 0d       	lwi450 $r0,[$r13]
    4142:	80 4a       	mov55 $r2,$r10
    4144:	4c 90 00 1a 	beq $r9,$r0,4178 <lfs_bd_read.isra.13+0xd8>
    4148:	b4 08       	lwi450 $r0,[$r8]
    414a:	4c 90 00 07 	beq $r9,$r0,4158 <lfs_bd_read.isra.13+0xb8>
    414e:	92 00       	nop16
    4150:	e3 4b       	slt45 $r10,$r11
    4152:	e8 c2       	beqzs8 40d6 <lfs_bd_read.isra.13+0x36>
    4154:	b4 0c       	lwi450 $r0,[$r12]
    4156:	d5 c9       	j8 40e8 <lfs_bd_read.isra.13+0x48>
    4158:	04 34 00 01 	lwi $r3,[$r8+#0x4]
    415c:	04 04 00 02 	lwi $r0,[$r8+#0x8]
    4160:	88 03       	add45 $r0,$r3
    4162:	e2 e0       	slt45 $r7,$r0
    4164:	e8 f6       	beqzs8 4150 <lfs_bd_read.isra.13+0xb0>
    4166:	e2 e3       	slt45 $r7,$r3
    4168:	e8 2b       	beqzs8 41be <lfs_bd_read.isra.13+0x11e>
    416a:	8a 67       	sub45 $r3,$r7
    416c:	e2 62       	slt45 $r3,$r2
    416e:	40 21 bc 1b 	cmovn $r2,$r3,$r15
    4172:	d5 ef       	j8 4150 <lfs_bd_read.isra.13+0xb0>
    4174:	80 4a       	mov55 $r2,$r10
    4176:	d5 e9       	j8 4148 <lfs_bd_read.isra.13+0xa8>
    4178:	04 36 80 01 	lwi $r3,[$r13+#0x4]
    417c:	04 06 80 02 	lwi $r0,[$r13+#0x8]
    4180:	88 03       	add45 $r0,$r3
    4182:	e2 e0       	slt45 $r7,$r0
    4184:	e8 f8       	beqzs8 4174 <lfs_bd_read.isra.13+0xd4>
    4186:	e2 e3       	slt45 $r7,$r3
    4188:	e8 29       	beqzs8 41da <lfs_bd_read.isra.13+0x13a>
    418a:	9a 9f       	sub333 $r2,$r3,$r7
    418c:	e3 42       	slt45 $r10,$r2
    418e:	40 25 3c 1b 	cmovn $r2,$r10,$r15
    4192:	d5 db       	j8 4148 <lfs_bd_read.isra.13+0xa8>
    4194:	84 00       	movi55 $r0,#0x0
    4196:	92 00       	nop16
    4198:	3a 6f b8 84 	lmw.bim $r6,[$sp],$r14,#0x2    ! {$r6~$r14, $lp}
    419c:	dd 9e       	ret5 $lp
    419e:	92 00       	nop16
    41a0:	40 11 39 d7 	divr $r1,$r14,$r2,$r14
    41a4:	a1 41       	lwi333 $r5,[$r0+#0x4]
    41a6:	40 e1 38 01 	sub $r14,$r2,$r14
    41aa:	80 29       	mov55 $r1,$r9
    41ac:	80 47       	mov55 $r2,$r7
    41ae:	80 66       	mov55 $r3,$r6
    41b0:	80 8e       	mov55 $r4,$r14
    41b2:	dd 25       	jral5 $r5
    41b4:	c8 f2       	bnez38 $r0,4198 <lfs_bd_read.isra.13+0xf8>
    41b6:	88 ce       	add45 $r6,$r14
    41b8:	88 ee       	add45 $r7,$r14
    41ba:	8b 4e       	sub45 $r10,$r14
    41bc:	d5 8a       	j8 40d0 <lfs_bd_read.isra.13+0x30>
    41be:	8a 07       	sub45 $r0,$r7
    41c0:	e2 02       	slt45 $r0,$r2
    41c2:	04 44 00 03 	lwi $r4,[$r8+#0xc]
    41c6:	40 01 3c 1a 	cmovz $r0,$r2,$r15
    41ca:	9a 7b       	sub333 $r1,$r7,$r3
    41cc:	81 c0       	mov55 $r14,$r0
    41ce:	88 24       	add45 $r1,$r4
    41d0:	80 06       	mov55 $r0,$r6
    41d2:	80 4e       	mov55 $r2,$r14
    41d4:	49 00 2e bc 	jal 9f4c <memcpy>
    41d8:	d5 ef       	j8 41b6 <lfs_bd_read.isra.13+0x116>
    41da:	8a 07       	sub45 $r0,$r7
    41dc:	e3 40       	slt45 $r10,$r0
    41de:	04 26 80 03 	lwi $r2,[$r13+#0xc]
    41e2:	40 05 3c 1b 	cmovn $r0,$r10,$r15
    41e6:	9a 7b       	sub333 $r1,$r7,$r3
    41e8:	81 c0       	mov55 $r14,$r0
    41ea:	88 22       	add45 $r1,$r2
    41ec:	80 06       	mov55 $r0,$r6
    41ee:	d5 f2       	j8 41d2 <lfs_bd_read.isra.13+0x132>
    41f0:	44 0f ff ac 	movi $r0,#-84
    41f4:	d5 d2       	j8 4198 <lfs_bd_read.isra.13+0xf8>
    41f6:	92 00       	nop16
    41f8:	44 00 36 cc 	movi $r0,#0x36cc
    41fc:	44 10 00 5a 	movi $r1,#0x5a
    4200:	44 20 7c bc 	movi $r2,#0x7cbc
    4204:	44 30 39 a4 	movi $r3,#0x39a4
    4208:	49 00 2d 06 	jal 9c14 <__assert_func>
    420c:	92 00       	nop16
    420e:	92 00       	nop16
    4210:	44 00 36 cc 	movi $r0,#0x36cc
    4214:	44 10 00 65 	movi $r1,#0x65
    4218:	44 20 7c bc 	movi $r2,#0x7cbc
    421c:	44 30 39 24 	movi $r3,#0x3924
    4220:	49 00 2c fa 	jal 9c14 <__assert_func>
    4224:	92 00       	nop16
    4226:	92 00       	nop16

00004228 <lfs_fs_parent_match>:
    4228:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    422c:	ef f0       	addi10.sp #-16
    422e:	b4 60       	lwi450 $r3,[$r0]
    4230:	80 c0       	mov55 $r6,$r0
    4232:	b0 02       	addri36.sp $r0,#0x8
    4234:	04 41 80 1a 	lwi $r4,[$r3+#0x68]
    4238:	b6 1f       	swi450 $r0,[$sp]
    423a:	84 08       	movi55 $r0,#0x8
    423c:	f0 81       	swi37.sp $r0,[+#0x4]
    423e:	80 a2       	mov55 $r5,$r2
    4240:	50 01 80 68 	addi $r0,$r3,#0x68
    4244:	50 11 80 10 	addi $r1,$r3,#0x10
    4248:	80 43       	mov55 $r2,$r3
    424a:	a0 e7       	lwi333 $r3,[$r4+#0x1c]
    424c:	b4 85       	lwi450 $r4,[$r5]
    424e:	a1 69       	lwi333 $r5,[$r5+#0x4]
    4250:	49 ff ff 28 	jal 40a0 <lfs_bd_read.isra.13>
    4254:	c8 0c       	bnez38 $r0,426c <lfs_fs_parent_match+0x44>
    4256:	f5 02       	lwi37.sp $r5,[+#0x8]
    4258:	a0 f1       	lwi333 $r3,[$r6+#0x4]
    425a:	d3 0d       	beqs38 $r3,4274 <lfs_fs_parent_match+0x4c>
    425c:	f1 03       	lwi37.sp $r1,[+#0xc]
    425e:	a1 32       	lwi333 $r4,[$r6+#0x8]
    4260:	4c 12 00 0a 	beq $r1,$r4,4274 <lfs_fs_parent_match+0x4c>
    4264:	d4 08       	beqs38 $r4,4274 <lfs_fs_parent_match+0x4c>
    4266:	fe 5d       	xor33 $r1,$r3
    4268:	40 00 04 06 	slt $r0,$r0,$r1
    426c:	ec 10       	addi10.sp #0x10
    426e:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    4272:	dd 9e       	ret5 $lp
    4274:	84 00       	movi55 $r0,#0x0
    4276:	ec 10       	addi10.sp #0x10
    4278:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    427c:	dd 9e       	ret5 $lp
    427e:	92 00       	nop16
    4280:	ff ff       	or33 $r7,$r7
    4282:	ff ff       	or33 $r7,$r7
    4284:	ff ff       	or33 $r7,$r7
    4286:	ff ff       	or33 $r7,$r7

00004288 <lfs_dir_fetchmatch>:
    4288:	05 00 00 1a 	lwi $r16,[$r0+#0x68]
    428c:	b5 c2       	lwi450 $r18,[$r2]
    428e:	05 18 00 08 	lwi $r17,[$r16+#0x20]
    4292:	e3 d1       	slt45 $r18,$r17
    4294:	4e f2 02 94 	beqz $r15,47bc <lfs_dir_fetchmatch+0x534>
    4298:	05 01 00 01 	lwi $r16,[$r2+#0x4]
    429c:	e3 91       	slt45 $r16,$r17
    429e:	4e f2 02 8f 	beqz $r15,47bc <lfs_dir_fetchmatch+0x534>
    42a2:	3a 6f ba bc 	smw.adm $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    42a6:	ef 7c       	addi10.sp #-132
    42a8:	36 3f 80 10 	fsdi $fd3,[$sp+#0x40]
    42ac:	36 4f 80 12 	fsdi $fd4,[$sp+#0x48]
    42b0:	36 5f 80 14 	fsdi $fd5,[$sp+#0x50]
    42b4:	36 6f 80 16 	fsdi $fd6,[$sp+#0x58]
    42b8:	36 7f 80 18 	fsdi $fd7,[$sp+#0x60]
    42bc:	36 8f 80 1a 	fsdi $fd8,[$sp+#0x68]
    42c0:	36 9f 80 1c 	fsdi $fd9,[$sp+#0x70]
    42c4:	36 af 80 1e 	fsdi $fd10,[$sp+#0x78]
    42c8:	80 c0       	mov55 $r6,$r0
    42ca:	51 c0 00 68 	addi $fp,$r0,#0x68
    42ce:	b0 0a       	addri36.sp $r0,#0x28
    42d0:	b6 1f       	swi450 $r0,[$sp]
    42d2:	84 04       	movi55 $r0,#0x4
    42d4:	86 00       	movi55 $r16,#0x0
    42d6:	6a 58 80 09 	fmtsr $r5,$fs17
    42da:	6a 45 80 09 	fmtsr $r4,$fs11
    42de:	6a 35 00 09 	fmtsr $r3,$fs10
    42e2:	81 41       	mov55 $r10,$r1
    42e4:	80 e2       	mov55 $r7,$r2
    42e6:	f0 81       	swi37.sp $r0,[+#0x4]
    42e8:	84 20       	movi55 $r1,#0x0
    42ea:	80 1c       	mov55 $r0,$fp
    42ec:	80 46       	mov55 $r2,$r6
    42ee:	84 64       	movi55 $r3,#0x4
    42f0:	80 92       	mov55 $r4,$r18
    42f2:	84 a0       	movi55 $r5,#0x0
    42f4:	15 0f 80 0a 	swi $r16,[$sp+#0x28]
    42f8:	15 0f 80 0b 	swi $r16,[$sp+#0x2c]
    42fc:	49 ff fe d2 	jal 40a0 <lfs_bd_read.isra.13>
    4300:	4e 02 00 06 	beqz $r0,430c <lfs_dir_fetchmatch+0x84>
    4304:	5a 07 ac 04 	beqc $r0,#-84,430c <lfs_dir_fetchmatch+0x84>
    4308:	48 00 01 84 	j 4610 <lfs_dir_fetchmatch+0x388>
    430c:	b0 0b       	addri36.sp $r0,#0x2c
    430e:	b6 1f       	swi450 $r0,[$sp]
    4310:	84 04       	movi55 $r0,#0x4
    4312:	f0 81       	swi37.sp $r0,[+#0x4]
    4314:	84 20       	movi55 $r1,#0x0
    4316:	80 1c       	mov55 $r0,$fp
    4318:	80 46       	mov55 $r2,$r6
    431a:	84 64       	movi55 $r3,#0x4
    431c:	a1 39       	lwi333 $r4,[$r7+#0x4]
    431e:	84 a0       	movi55 $r5,#0x0
    4320:	49 ff fe c0 	jal 40a0 <lfs_bd_read.isra.13>
    4324:	f1 0b       	lwi37.sp $r1,[+#0x2c]
    4326:	4e 03 01 e4 	bnez $r0,46ee <lfs_dir_fetchmatch+0x466>
    432a:	f2 0a       	lwi37.sp $r2,[+#0x28]
    432c:	8a 22       	sub45 $r1,$r2
    432e:	e0 01       	slts45 $r0,$r1
    4330:	38 03 be 02 	lw $r0,[$r7+($r15<<#0x2)]
    4334:	b6 0a       	swi450 $r0,[$r10]
    4336:	56 07 80 01 	xori $r0,$r15,#0x1
    433a:	38 23 82 02 	lw $r2,[$r7+($r0<<#0x2)]
    433e:	6a 09 00 09 	fmtsr $r0,$fs18
    4342:	b0 0a       	addri36.sp $r0,#0x28
    4344:	38 00 3e 02 	lw $r0,[$r0+($r15<<#0x2)]
    4348:	14 05 00 02 	swi $r0,[$r10+#0x8]
    434c:	84 00       	movi55 $r0,#0x0
    434e:	14 05 00 03 	swi $r0,[$r10+#0xc]
    4352:	50 05 00 08 	addi $r0,$r10,#0x8
    4356:	6a 0a 00 09 	fmtsr $r0,$fs20
    435a:	84 02       	movi55 $r0,#0x2
    435c:	6a 09 80 09 	fmtsr $r0,$fs19
    4360:	84 1f       	movi55 $r0,#-1
    4362:	6a 03 00 09 	fmtsr $r0,$fs6
    4366:	b0 0c       	addri36.sp $r0,#0x30
    4368:	6a 07 00 09 	fmtsr $r0,$fs14
    436c:	44 00 42 80 	movi $r0,#0x4280
    4370:	6a 07 80 09 	fmtsr $r0,$fs15
    4374:	46 07 00 00 	sethi $r0,#0x70000
    4378:	6a 04 80 09 	fmtsr $r0,$fs9
    437c:	46 00 ff 00 	sethi $r0,#0xff00
    4380:	6a 0a 80 09 	fmtsr $r0,$fs21
    4384:	46 07 ff ff 	sethi $r0,#0x7ffff
    4388:	50 00 0c 00 	addi $r0,$r0,#0xc00
    438c:	6a 08 00 09 	fmtsr $r0,$fs16
    4390:	46 00 00 ff 	sethi $r0,#0xff
    4394:	50 00 0c 00 	addi $r0,$r0,#0xc00
    4398:	6a 03 80 09 	fmtsr $r0,$fs7
    439c:	14 25 00 01 	swi $r2,[$r10+#0x4]
    43a0:	50 bf 80 20 	addi $r11,$sp,#0x20
    43a4:	6a 07 80 01 	fmfsr $r0,$fs15
    43a8:	6a 37 00 01 	fmfsr $r3,$fs14
    43ac:	6a 1a 00 01 	fmfsr $r1,$fs20
    43b0:	3b 00 44 00 	lmw.bi $r16,[$r0],$r17,#0x0    ! {$r16~$r17}
    43b4:	84 44       	movi55 $r2,#0x4
    43b6:	84 1f       	movi55 $r0,#-1
    43b8:	3b 01 c4 20 	smw.bi $r16,[$r3],$r17,#0x0    ! {$r16~$r17}
    43bc:	49 00 1c 86 	jal 7cc8 <lfs_crc>
    43c0:	80 e0       	mov55 $r7,$r0
    43c2:	6a d3 18 c0 	fcpyss $fs13,$fs6,$fs6
    43c6:	84 00       	movi55 $r0,#0x0
    43c8:	f0 87       	swi37.sp $r0,[+#0x1c]
    43ca:	f0 86       	swi37.sp $r0,[+#0x18]
    43cc:	85 bf       	movi55 $r13,#-1
    43ce:	85 20       	movi55 $r9,#0x0
    43d0:	40 06 d8 08 	slli $r0,$r13,#0x16
    43d4:	90 16       	srai45 $r0,#0x16
    43d6:	8c 01       	addi45 $r0,#0x1
    43d8:	e6 01       	slti45 $r0,#0x1
    43da:	40 f7 b4 00 	add $r15,$r15,$r13
    43de:	54 07 83 ff 	andi $r0,$r15,#0x3ff
    43e2:	04 33 00 1a 	lwi $r3,[$r6+#0x68]
    43e6:	84 24       	movi55 $r1,#0x4
    43e8:	8c 04       	addi45 $r0,#0x4
    43ea:	f1 81       	swi37.sp $r1,[+#0x4]
    43ec:	b7 7f       	swi450 $r11,[$sp]
    43ee:	89 20       	add45 $r9,$r0
    43f0:	6a 14 00 09 	fmtsr $r1,$fs8
    43f4:	80 1c       	mov55 $r0,$fp
    43f6:	84 20       	movi55 $r1,#0x0
    43f8:	80 46       	mov55 $r2,$r6
    43fa:	a0 df       	lwi333 $r3,[$r3+#0x1c]
    43fc:	b4 8a       	lwi450 $r4,[$r10]
    43fe:	80 a9       	mov55 $r5,$r9
    4400:	49 ff fe 50 	jal 40a0 <lfs_bd_read.isra.13>
    4404:	81 00       	mov55 $r8,$r0
    4406:	4e 03 01 c1 	bnez $r0,4788 <lfs_dir_fetchmatch+0x500>
    440a:	80 07       	mov55 $r0,$r7
    440c:	80 2b       	mov55 $r1,$r11
    440e:	84 44       	movi55 $r2,#0x4
    4410:	49 00 1c 5c 	jal 7cc8 <lfs_crc>
    4414:	80 e0       	mov55 $r7,$r0
    4416:	f0 08       	lwi37.sp $r0,[+#0x20]
    4418:	40 00 00 14 	wsbh $r0,$r0
    441c:	40 00 40 0b 	rotri $r0,$r0,#0x10
    4420:	40 c0 34 03 	xor $r12,$r0,$r13
    4424:	14 cf 80 08 	swi $r12,[$sp+#0x20]
    4428:	4e c5 01 b6 	bltz $r12,4794 <lfs_dir_fetchmatch+0x50c>
    442c:	40 06 58 08 	slli $r0,$r12,#0x16
    4430:	90 16       	srai45 $r0,#0x16
    4432:	8c 01       	addi45 $r0,#0x1
    4434:	e6 01       	slti45 $r0,#0x1
    4436:	04 13 00 1a 	lwi $r1,[$r6+#0x68]
    443a:	40 f7 b0 00 	add $r15,$r15,$r12
    443e:	54 07 83 ff 	andi $r0,$r15,#0x3ff
    4442:	a0 cf       	lwi333 $r3,[$r1+#0x1c]
    4444:	8c 04       	addi45 $r0,#0x4
    4446:	40 10 24 00 	add $r1,$r0,$r9
    444a:	e2 61       	slt45 $r3,$r1
    444c:	4e f3 01 98 	bnez $r15,477c <lfs_dir_fetchmatch+0x4f4>
    4450:	6a 14 80 01 	fmfsr $r1,$fs9
    4454:	44 20 05 00 	movi $r2,#0x500
    4458:	40 56 04 02 	and $r5,$r12,$r1
    445c:	92 b4       	srli45 $r5,#0x14
    445e:	4c 51 00 99 	beq $r5,$r2,4590 <lfs_dir_fetchmatch+0x308>
    4462:	5a 08 04 05 	bnec $r0,#0x4,446c <lfs_dir_fetchmatch+0x1e4>
    4466:	48 00 01 4a 	j 46fa <lfs_dir_fetchmatch+0x472>
    446a:	92 00       	nop16
    446c:	85 c4       	movi55 $r14,#0x4
    446e:	50 8f 80 24 	addi $r8,$sp,#0x24
    4472:	85 a1       	movi55 $r13,#0x1
    4474:	d5 17       	j8 44a2 <lfs_dir_fetchmatch+0x21a>
    4476:	92 00       	nop16
    4478:	49 00 1c 28 	jal 7cc8 <lfs_crc>
    447c:	f5 08       	lwi37.sp $r5,[+#0x20]
    447e:	80 e0       	mov55 $r7,$r0
    4480:	40 02 d8 08 	slli $r0,$r5,#0x16
    4484:	90 16       	srai45 $r0,#0x16
    4486:	8c 01       	addi45 $r0,#0x1
    4488:	5c 00 00 01 	slti $r0,$r0,#0x1
    448c:	88 05       	add45 $r0,$r5
    448e:	54 00 03 ff 	andi $r0,$r0,#0x3ff
    4492:	8c 04       	addi45 $r0,#0x4
    4494:	40 07 00 06 	slt $r0,$r14,$r0
    4498:	4e 02 00 76 	beqz $r0,4584 <lfs_dir_fetchmatch+0x2fc>
    449c:	04 03 00 1a 	lwi $r0,[$r6+#0x68]
    44a0:	a0 c7       	lwi333 $r3,[$r0+#0x1c]
    44a2:	b4 8a       	lwi450 $r4,[$r10]
    44a4:	40 57 24 00 	add $r5,$r14,$r9
    44a8:	80 46       	mov55 $r2,$r6
    44aa:	84 20       	movi55 $r1,#0x0
    44ac:	b7 1f       	swi450 $r8,[$sp]
    44ae:	14 df 80 01 	swi $r13,[$sp+#0x4]
    44b2:	80 1c       	mov55 $r0,$fp
    44b4:	49 ff fd f6 	jal 40a0 <lfs_bd_read.isra.13>
    44b8:	80 60       	mov55 $r3,$r0
    44ba:	50 e7 00 01 	addi $r14,$r14,#0x1
    44be:	80 28       	mov55 $r1,$r8
    44c0:	84 41       	movi55 $r2,#0x1
    44c2:	80 07       	mov55 $r0,$r7
    44c4:	c3 da       	beqz38 $r3,4478 <lfs_dir_fetchmatch+0x1f0>
    44c6:	5a 37 ac 05 	beqc $r3,#-84,44d0 <lfs_dir_fetchmatch+0x248>
    44ca:	48 00 01 75 	j 47b4 <lfs_dir_fetchmatch+0x52c>
    44ce:	92 00       	nop16
    44d0:	6a 04 80 01 	fmfsr $r0,$fs9
    44d4:	05 0f 80 08 	lwi $r16,[$sp+#0x20]
    44d8:	40 58 00 02 	and $r5,$r16,$r0
    44dc:	84 00       	movi55 $r0,#0x0
    44de:	10 05 00 16 	sbi $r0,[$r10+#0x16]
    44e2:	92 b4       	srli45 $r5,#0x14
    44e4:	97 69       	zeh33 $r5,$r5
    44e6:	cd 2f       	bnez38 $r5,4544 <lfs_dir_fetchmatch+0x2bc>
    44e8:	6a 03 80 01 	fmfsr $r0,$fs7
    44ec:	f1 06       	lwi37.sp $r1,[+#0x18]
    44ee:	40 08 00 02 	and $r0,$r16,$r0
    44f2:	92 0a       	srli45 $r0,#0xa
    44f4:	96 01       	zeh33 $r0,$r0
    44f6:	e2 01       	slt45 $r0,$r1
    44f8:	e9 04       	bnezs8 4500 <lfs_dir_fetchmatch+0x278>
    44fa:	8c 01       	addi45 $r0,#0x1
    44fc:	96 01       	zeh33 $r0,$r0
    44fe:	f0 86       	swi37.sp $r0,[+#0x18]
    4500:	6a 05 80 01 	fmfsr $r0,$fs11
    4504:	40 88 00 03 	xor $r8,$r16,$r0
    4508:	6a 05 00 01 	fmfsr $r0,$fs10
    450c:	40 84 00 02 	and $r8,$r8,$r0
    4510:	4e 82 00 06 	beqz $r8,451c <lfs_dir_fetchmatch+0x294>
    4514:	81 ac       	mov55 $r13,$r12
    4516:	48 ff ff 5d 	j 43d0 <lfs_dir_fetchmatch+0x148>
    451a:	92 00       	nop16
    451c:	50 34 80 04 	addi $r3,$r9,#0x4
    4520:	b0 8e       	addri36.sp $r2,#0x38
    4522:	a8 d1       	swi333 $r3,[$r2+#0x4]
    4524:	f3 2c       	lwi37.sp $r3,[+#0xb0]
    4526:	b4 8a       	lwi450 $r4,[$r10]
    4528:	f0 2d       	lwi37.sp $r0,[+#0xb4]
    452a:	80 30       	mov55 $r1,$r16
    452c:	f4 8e       	swi37.sp $r4,[+#0x38]
    452e:	dd 23       	jral5 $r3
    4530:	4e 05 01 22 	bltz $r0,4774 <lfs_dir_fetchmatch+0x4ec>
    4534:	4e 03 00 82 	bnez $r0,4638 <lfs_dir_fetchmatch+0x3b0>
    4538:	30 df 80 08 	flsi $fs13,[$sp+#0x20]
    453c:	81 ac       	mov55 $r13,$r12
    453e:	48 ff ff 49 	j 43d0 <lfs_dir_fetchmatch+0x148>
    4542:	92 00       	nop16
    4544:	44 00 04 00 	movi $r0,#0x400
    4548:	4c 50 00 9a 	beq $r5,$r0,467c <lfs_dir_fetchmatch+0x3f4>
    454c:	44 00 06 00 	movi $r0,#0x600
    4550:	d8 d8       	bnes38 $r0,4500 <lfs_dir_fetchmatch+0x278>
    4552:	04 33 00 1a 	lwi $r3,[$r6+#0x68]
    4556:	84 08       	movi55 $r0,#0x8
    4558:	f0 81       	swi37.sp $r0,[+#0x4]
    455a:	32 ef 80 00 	fssi $fs14,[$sp+#0x0]
    455e:	43 08 50 0b 	btst $r16,$r16,#0x14
    4562:	80 1c       	mov55 $r0,$fp
    4564:	84 20       	movi55 $r1,#0x0
    4566:	80 46       	mov55 $r2,$r6
    4568:	a0 df       	lwi333 $r3,[$r3+#0x1c]
    456a:	b4 8a       	lwi450 $r4,[$r10]
    456c:	50 54 80 04 	addi $r5,$r9,#0x4
    4570:	15 0f 80 07 	swi $r16,[$sp+#0x1c]
    4574:	49 ff fd 96 	jal 40a0 <lfs_bd_read.isra.13>
    4578:	5a 07 ac 1f 	beqc $r0,#-84,45b6 <lfs_dir_fetchmatch+0x32e>
    457c:	05 0f 80 08 	lwi $r16,[$sp+#0x20]
    4580:	d5 c0       	j8 4500 <lfs_dir_fetchmatch+0x278>
    4582:	92 00       	nop16
    4584:	6a 04 80 01 	fmfsr $r0,$fs9
    4588:	82 05       	mov55 $r16,$r5
    458a:	ff 46       	and33 $r5,$r0
    458c:	92 b4       	srli45 $r5,#0x14
    458e:	d5 ab       	j8 44e4 <lfs_dir_fetchmatch+0x25c>
    4590:	50 8f 80 24 	addi $r8,$sp,#0x24
    4594:	b7 1f       	swi450 $r8,[$sp]
    4596:	32 8f 80 01 	fssi $fs8,[$sp+#0x4]
    459a:	80 1c       	mov55 $r0,$fp
    459c:	84 20       	movi55 $r1,#0x0
    459e:	80 46       	mov55 $r2,$r6
    45a0:	04 45 00 00 	lwi $r4,[$r10+#0x0]
    45a4:	50 54 80 04 	addi $r5,$r9,#0x4
    45a8:	49 ff fd 7c 	jal 40a0 <lfs_bd_read.isra.13>
    45ac:	4e 03 01 16 	bnez $r0,47d8 <lfs_dir_fetchmatch+0x550>
    45b0:	f0 09       	lwi37.sp $r0,[+#0x24]
    45b2:	4c 70 00 a7 	beq $r7,$r0,4700 <lfs_dir_fetchmatch+0x478>
    45b6:	84 00       	movi55 $r0,#0x0
    45b8:	10 05 00 16 	sbi $r0,[$r10+#0x16]
    45bc:	04 05 00 03 	lwi $r0,[$r10+#0xc]
    45c0:	4e 03 01 12 	bnez $r0,47e4 <lfs_dir_fetchmatch+0x55c>
    45c4:	6a 39 00 01 	fmfsr $r3,$fs18
    45c8:	b0 8a       	addri36.sp $r2,#0x28
    45ca:	38 21 0e 02 	lw $r2,[$r2+($r3<<#0x2)]
    45ce:	14 25 00 02 	swi $r2,[$r10+#0x8]
    45d2:	6a 29 80 01 	fmfsr $r2,$fs19
    45d6:	b4 0a       	lwi450 $r0,[$r10]
    45d8:	04 15 00 01 	lwi $r1,[$r10+#0x4]
    45dc:	b6 2a       	swi450 $r1,[$r10]
    45de:	14 05 00 01 	swi $r0,[$r10+#0x4]
    45e2:	5a 20 01 05 	beqc $r2,#0x1,45ec <lfs_dir_fetchmatch+0x364>
    45e6:	48 00 00 79 	j 46d8 <lfs_dir_fetchmatch+0x450>
    45ea:	92 00       	nop16
    45ec:	44 20 36 cc 	movi $r2,#0x36cc
    45f0:	b6 5f       	swi450 $r2,[$sp]
    45f2:	f0 83       	swi37.sp $r0,[+#0xc]
    45f4:	44 20 03 e6 	movi $r2,#0x3e6
    45f8:	44 00 01 38 	movi $r0,#0x138
    45fc:	f0 84       	swi37.sp $r0,[+#0x10]
    45fe:	f2 81       	swi37.sp $r2,[+#0x4]
    4600:	14 1f 80 02 	swi $r1,[$sp+#0x8]
    4604:	44 00 39 30 	movi $r0,#0x3930
    4608:	49 ff ef 18 	jal 2438 <printf>
    460c:	44 0f ff ac 	movi $r0,#-84
    4610:	ec 40       	addi10.sp #0x40
    4612:	34 3f 90 02 	fldi.bi $fd3,[$sp],#0x8
    4616:	34 4f 90 02 	fldi.bi $fd4,[$sp],#0x8
    461a:	34 5f 90 02 	fldi.bi $fd5,[$sp],#0x8
    461e:	34 6f 90 02 	fldi.bi $fd6,[$sp],#0x8
    4622:	34 7f 90 02 	fldi.bi $fd7,[$sp],#0x8
    4626:	34 8f 90 02 	fldi.bi $fd8,[$sp],#0x8
    462a:	34 9f 90 02 	fldi.bi $fd9,[$sp],#0x8
    462e:	34 af 90 03 	fldi.bi $fd10,[$sp],#0xc
    4632:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    4636:	dd 9e       	ret5 $lp
    4638:	f2 08       	lwi37.sp $r2,[+#0x20]
    463a:	6a 16 80 01 	fmfsr $r1,$fs13
    463e:	6a 38 00 01 	fmfsr $r3,$fs16
    4642:	fe 55       	xor33 $r1,$r2
    4644:	fe 5e       	and33 $r1,$r3
    4646:	c1 4e       	beqz38 $r1,46e2 <lfs_dir_fetchmatch+0x45a>
    4648:	5a 00 02 04 	beqc $r0,#0x2,4650 <lfs_dir_fetchmatch+0x3c8>
    464c:	48 ff ff 64 	j 4514 <lfs_dir_fetchmatch+0x28c>
    4650:	6a 06 80 01 	fmfsr $r0,$fs13
    4654:	6a 13 80 01 	fmfsr $r1,$fs7
    4658:	81 ac       	mov55 $r13,$r12
    465a:	fe 0e       	and33 $r0,$r1
    465c:	fe 56       	and33 $r1,$r2
    465e:	92 2a       	srli45 $r1,#0xa
    4660:	92 0a       	srli45 $r0,#0xa
    4662:	96 49       	zeh33 $r1,$r1
    4664:	96 01       	zeh33 $r0,$r0
    4666:	e2 01       	slt45 $r0,$r1
    4668:	6a 16 80 01 	fmfsr $r1,$fs13
    466c:	42 21 7c 08 	bset $r2,$r2,#0x1f
    4670:	40 11 3c 1a 	cmovz $r1,$r2,$r15
    4674:	6a 16 80 09 	fmtsr $r1,$fs13
    4678:	48 ff fe ac 	j 43d0 <lfs_dir_fetchmatch+0x148>
    467c:	6a 0a 80 01 	fmfsr $r0,$fs21
    4680:	6a 23 80 01 	fmfsr $r2,$fs7
    4684:	40 08 00 02 	and $r0,$r16,$r0
    4688:	f3 06       	lwi37.sp $r3,[+#0x18]
    468a:	92 14       	srli45 $r0,#0x14
    468c:	6a 16 80 01 	fmfsr $r1,$fs13
    4690:	96 02       	seb33 $r0,$r0
    4692:	fe 56       	and33 $r1,$r2
    4694:	88 60       	add45 $r3,$r0
    4696:	46 24 ff 00 	sethi $r2,#0x4ff00
    469a:	96 d9       	zeh33 $r3,$r3
    469c:	fe 8f       	or33 $r2,$r1
    469e:	f3 86       	swi37.sp $r3,[+#0x18]
    46a0:	4c 28 00 62 	beq $r2,$r16,4764 <lfs_dir_fetchmatch+0x4dc>
    46a4:	6a 26 80 01 	fmfsr $r2,$fs13
    46a8:	5a 2f ff 04 	bnec $r2,#-1,46b0 <lfs_dir_fetchmatch+0x428>
    46ac:	48 ff ff 2a 	j 4500 <lfs_dir_fetchmatch+0x278>
    46b0:	6a 23 80 01 	fmfsr $r2,$fs7
    46b4:	92 2a       	srli45 $r1,#0xa
    46b6:	40 28 08 02 	and $r2,$r16,$r2
    46ba:	92 4a       	srli45 $r2,#0xa
    46bc:	96 91       	zeh33 $r2,$r2
    46be:	96 49       	zeh33 $r1,$r1
    46c0:	e2 22       	slt45 $r1,$r2
    46c2:	4e f3 ff 1f 	bnez $r15,4500 <lfs_dir_fetchmatch+0x278>
    46c6:	6a 16 80 01 	fmfsr $r1,$fs13
    46ca:	40 00 28 08 	slli $r0,$r0,#0xa
    46ce:	88 20       	add45 $r1,$r0
    46d0:	6a 16 80 09 	fmtsr $r1,$fs13
    46d4:	48 ff ff 16 	j 4500 <lfs_dir_fetchmatch+0x278>
    46d8:	84 01       	movi55 $r0,#0x1
    46da:	6a 09 80 09 	fmtsr $r0,$fs19
    46de:	48 ff fe 63 	j 43a4 <lfs_dir_fetchmatch+0x11c>
    46e2:	84 1f       	movi55 $r0,#-1
    46e4:	6a 06 80 09 	fmtsr $r0,$fs13
    46e8:	81 ac       	mov55 $r13,$r12
    46ea:	48 ff fe 73 	j 43d0 <lfs_dir_fetchmatch+0x148>
    46ee:	85 e0       	movi55 $r15,#0x0
    46f0:	5a 0f ac 04 	bnec $r0,#-84,46f8 <lfs_dir_fetchmatch+0x470>
    46f4:	48 ff fe 1e 	j 4330 <lfs_dir_fetchmatch+0xa8>
    46f8:	d5 8c       	j8 4610 <lfs_dir_fetchmatch+0x388>
    46fa:	82 0c       	mov55 $r16,$r12
    46fc:	48 ff fe f4 	j 44e4 <lfs_dir_fetchmatch+0x25c>
    4700:	f1 08       	lwi37.sp $r1,[+#0x20]
    4702:	04 23 00 0b 	lwi $r2,[$r6+#0x2c]
    4706:	40 00 d8 08 	slli $r0,$r1,#0x16
    470a:	90 16       	srai45 $r0,#0x16
    470c:	8c 01       	addi45 $r0,#0x1
    470e:	e6 01       	slti45 $r0,#0x1
    4710:	40 f7 84 00 	add $r15,$r15,$r1
    4714:	6a 3a 80 01 	fmfsr $r3,$fs21
    4718:	54 07 83 ff 	andi $r0,$r15,#0x3ff
    471c:	8c 04       	addi45 $r0,#0x4
    471e:	41 00 8c 02 	and $r16,$r1,$r3
    4722:	fe bd       	xor33 $r2,$r7
    4724:	88 09       	add45 $r0,$r9
    4726:	6a 17 00 01 	fmfsr $r1,$fs14
    472a:	14 23 00 0b 	swi $r2,[$r6+#0x2c]
    472e:	41 08 2c 08 	slli $r16,$r16,#0xb
    4732:	14 05 00 03 	swi $r0,[$r10+#0xc]
    4736:	02 0f 80 0c 	lhi $r0,[$sp+#0x18]
    473a:	b4 61       	lwi450 $r3,[$r1]
    473c:	40 d6 40 03 	xor $r13,$r12,$r16
    4740:	a0 49       	lwi333 $r1,[$r1+#0x4]
    4742:	12 05 00 0a 	shi $r0,[$r10+#0x14]
    4746:	00 0f 80 1c 	lbi $r0,[$sp+#0x1c]
    474a:	6a 66 b4 c0 	fcpyss $fs6,$fs13,$fs13
    474e:	14 d5 00 04 	swi $r13,[$r10+#0x10]
    4752:	14 35 00 06 	swi $r3,[$r10+#0x18]
    4756:	14 15 00 07 	swi $r1,[$r10+#0x1c]
    475a:	10 05 00 17 	sbi $r0,[$r10+#0x17]
    475e:	84 ff       	movi55 $r7,#-1
    4760:	48 ff fe 38 	j 43d0 <lfs_dir_fetchmatch+0x148>
    4764:	6a 06 80 01 	fmfsr $r0,$fs13
    4768:	42 00 7c 08 	bset $r0,$r0,#0x1f
    476c:	6a 06 80 09 	fmtsr $r0,$fs13
    4770:	48 ff fe c8 	j 4500 <lfs_dir_fetchmatch+0x278>
    4774:	5a 07 ac 04 	beqc $r0,#-84,477c <lfs_dir_fetchmatch+0x4f4>
    4778:	48 ff ff 4c 	j 4610 <lfs_dir_fetchmatch+0x388>
    477c:	10 85 00 16 	sbi $r8,[$r10+#0x16]
    4780:	04 05 00 03 	lwi $r0,[$r10+#0xc]
    4784:	48 ff ff 1e 	j 45c0 <lfs_dir_fetchmatch+0x338>
    4788:	5a 0f ac 04 	bnec $r0,#-84,4790 <lfs_dir_fetchmatch+0x508>
    478c:	48 ff ff 15 	j 45b6 <lfs_dir_fetchmatch+0x32e>
    4790:	48 ff ff 40 	j 4610 <lfs_dir_fetchmatch+0x388>
    4794:	6a 04 80 01 	fmfsr $r0,$fs9
    4798:	44 10 05 00 	movi $r1,#0x500
    479c:	40 56 80 02 	and $r5,$r13,$r0
    47a0:	92 b4       	srli45 $r5,#0x14
    47a2:	d1 11       	beqs38 $r1,47c4 <lfs_dir_fetchmatch+0x53c>
    47a4:	04 05 00 03 	lwi $r0,[$r10+#0xc]
    47a8:	44 10 00 00 	movi $r1,#0x0
    47ac:	10 15 00 16 	sbi $r1,[$r10+#0x16]
    47b0:	48 ff ff 08 	j 45c0 <lfs_dir_fetchmatch+0x338>
    47b4:	80 03       	mov55 $r0,$r3
    47b6:	48 ff ff 2d 	j 4610 <lfs_dir_fetchmatch+0x388>
    47ba:	92 00       	nop16
    47bc:	44 0f ff ac 	movi $r0,#-84
    47c0:	dd 9e       	ret5 $lp
    47c2:	92 00       	nop16
    47c4:	04 13 00 1a 	lwi $r1,[$r6+#0x68]
    47c8:	04 05 00 03 	lwi $r0,[$r10+#0xc]
    47cc:	a0 8e       	lwi333 $r2,[$r1+#0x18]
    47ce:	84 21       	movi55 $r1,#0x1
    47d0:	40 20 08 77 	divr $r2,$r3,$r0,$r2
    47d4:	c3 ec       	beqz38 $r3,47ac <lfs_dir_fetchmatch+0x524>
    47d6:	d5 e9       	j8 47a8 <lfs_dir_fetchmatch+0x520>
    47d8:	5a 0f ac 04 	bnec $r0,#-84,47e0 <lfs_dir_fetchmatch+0x558>
    47dc:	48 ff fe ed 	j 45b6 <lfs_dir_fetchmatch+0x32e>
    47e0:	48 ff ff 18 	j 4610 <lfs_dir_fetchmatch+0x388>
    47e4:	04 13 00 0f 	lwi $r1,[$r6+#0x3c]
    47e8:	6a 23 00 01 	fmfsr $r2,$fs6
    47ec:	40 00 d0 09 	srli $r0,$r1,#0x14
    47f0:	54 00 07 00 	andi $r0,$r0,#0x700
    47f4:	c0 0e       	beqz38 $r0,4810 <lfs_dir_fetchmatch+0x588>
    47f6:	04 53 00 10 	lwi $r5,[$r6+#0x40]
    47fa:	b4 6a       	lwi450 $r3,[$r10]
    47fc:	d3 28       	beqs38 $r3,484c <lfs_dir_fetchmatch+0x5c4>
    47fe:	04 03 00 11 	lwi $r0,[$r6+#0x44]
    4802:	04 45 00 01 	lwi $r4,[$r10+#0x4]
    4806:	4c 02 00 23 	beq $r0,$r4,484c <lfs_dir_fetchmatch+0x5c4>
    480a:	d4 21       	beqs38 $r4,484c <lfs_dir_fetchmatch+0x5c4>
    480c:	4c 30 00 20 	beq $r3,$r0,484c <lfs_dir_fetchmatch+0x5c4>
    4810:	6a 08 80 01 	fmfsr $r0,$fs17
    4814:	c0 0c       	beqz38 $r0,482c <lfs_dir_fetchmatch+0x5a4>
    4816:	40 11 30 08 	slli $r1,$r2,#0xc
    481a:	92 36       	srli45 $r1,#0x16
    481c:	02 35 00 0a 	lhi $r3,[$r10+#0x14]
    4820:	e2 61       	slt45 $r3,$r1
    4822:	40 11 bc 1b 	cmovn $r1,$r3,$r15
    4826:	6a 08 80 01 	fmfsr $r0,$fs17
    482a:	ac 40       	shi333 $r1,[$r0+#0x0]
    482c:	80 02       	mov55 $r0,$r2
    482e:	4e 24 fe f1 	bgez $r2,4610 <lfs_dir_fetchmatch+0x388>
    4832:	40 11 30 08 	slli $r1,$r2,#0xc
    4836:	92 36       	srli45 $r1,#0x16
    4838:	02 05 00 0a 	lhi $r0,[$r10+#0x14]
    483c:	96 49       	zeh33 $r1,$r1
    483e:	e2 20       	slt45 $r1,$r0
    4840:	84 7e       	movi55 $r3,#-2
    4842:	84 00       	movi55 $r0,#0x0
    4844:	40 01 bc 1b 	cmovn $r0,$r3,$r15
    4848:	48 ff fe e4 	j 4610 <lfs_dir_fetchmatch+0x388>
    484c:	46 00 00 ff 	sethi $r0,#0xff
    4850:	6a 23 00 01 	fmfsr $r2,$fs6
    4854:	50 00 0c 00 	addi $r0,$r0,#0xc00
    4858:	fe 46       	and33 $r1,$r0
    485a:	fe 86       	and33 $r2,$r0
    485c:	92 2a       	srli45 $r1,#0xa
    485e:	92 4a       	srli45 $r2,#0xa
    4860:	97 49       	zeh33 $r5,$r1
    4862:	96 91       	zeh33 $r2,$r2
    4864:	d2 0c       	beqs38 $r2,487c <lfs_dir_fetchmatch+0x5f4>
    4866:	6a 03 00 01 	fmfsr $r0,$fs6
    486a:	5a 07 ff 19 	beqc $r0,#-1,489c <lfs_dir_fetchmatch+0x614>
    486e:	e2 a2       	slt45 $r5,$r2
    4870:	50 20 7c 00 	addi $r2,$r0,#-1024
    4874:	40 20 3c 1a 	cmovz $r2,$r0,$r15
    4878:	d5 cc       	j8 4810 <lfs_dir_fetchmatch+0x588>
    487a:	92 00       	nop16
    487c:	6a 13 00 01 	fmfsr $r1,$fs6
    4880:	42 10 fc 08 	bset $r1,$r1,#0x1f
    4884:	fe 0e       	and33 $r0,$r1
    4886:	6a 13 00 09 	fmtsr $r1,$fs6
    488a:	40 10 28 09 	srli $r1,$r0,#0xa
    488e:	92 00       	nop16
    4890:	6a 08 80 01 	fmfsr $r0,$fs17
    4894:	6a 23 00 01 	fmfsr $r2,$fs6
    4898:	c8 c2       	bnez38 $r0,481c <lfs_dir_fetchmatch+0x594>
    489a:	d5 cf       	j8 4838 <lfs_dir_fetchmatch+0x5b0>
    489c:	44 10 03 ff 	movi $r1,#0x3ff
    48a0:	d5 f8       	j8 4890 <lfs_dir_fetchmatch+0x608>
    48a2:	92 00       	nop16

000048a4 <lfs_fs_parent>:
    48a4:	3a 6f b4 bc 	smw.adm $r6,[$sp],$r13,#0x2    ! {$r6~$r13, $lp}
    48a8:	ef e4       	addi10.sp #-28
    48aa:	81 20       	mov55 $r9,$r0
    48ac:	84 00       	movi55 $r0,#0x0
    48ae:	a8 16       	swi333 $r0,[$r2+#0x18]
    48b0:	46 c7 ff 00 	sethi $r12,#0x7ff00
    48b4:	84 01       	movi55 $r0,#0x1
    48b6:	46 b2 00 00 	sethi $r11,#0x20000
    48ba:	80 e2       	mov55 $r7,$r2
    48bc:	81 41       	mov55 $r10,$r1
    48be:	a8 17       	swi333 $r0,[$r2+#0x1c]
    48c0:	85 00       	movi55 $r8,#0x0
    48c2:	b1 83       	addri36.sp $r6,#0xc
    48c4:	50 d1 00 18 	addi $r13,$r2,#0x18
    48c8:	50 c6 03 ff 	addi $r12,$r12,#0x3ff
    48cc:	8d 68       	addi45 $r11,#0x8
    48ce:	a1 7f       	lwi333 $r5,[$r7+#0x1c]
    48d0:	80 09       	mov55 $r0,$r9
    48d2:	80 27       	mov55 $r1,$r7
    48d4:	80 4d       	mov55 $r2,$r13
    48d6:	80 6c       	mov55 $r3,$r12
    48d8:	80 8b       	mov55 $r4,$r11
    48da:	5a 57 ff 20 	beqc $r5,#-1,491a <lfs_fs_parent+0x76>
    48de:	05 04 80 1a 	lwi $r16,[$r9+#0x68]
    48e2:	84 a0       	movi55 $r5,#0x0
    48e4:	05 08 00 08 	lwi $r16,[$r16+#0x20]
    48e8:	93 81       	srli45 $r16,#0x1
    48ea:	e3 10       	slt45 $r8,$r16
    48ec:	e8 1c       	beqzs8 4924 <lfs_fs_parent+0x80>
    48ee:	b5 aa       	lwi450 $r17,[$r10]
    48f0:	05 05 00 01 	lwi $r16,[$r10+#0x4]
    48f4:	45 20 42 28 	movi $r18,#0x4228
    48f8:	b7 df       	swi450 $r18,[$sp]
    48fa:	f6 81       	swi37.sp $r6,[+#0x4]
    48fc:	b7 26       	swi450 $r9,[$r6]
    48fe:	15 13 00 01 	swi $r17,[$r6+#0x4]
    4902:	15 03 00 02 	swi $r16,[$r6+#0x8]
    4906:	49 ff fc c1 	jal 4288 <lfs_dir_fetchmatch>
    490a:	9d 42       	addi333 $r5,$r0,#0x2
    490c:	66 52 80 02 	bitci $r5,$r5,#0x2
    4910:	8d 01       	addi45 $r8,#0x1
    4912:	cd 05       	bnez38 $r5,491c <lfs_fs_parent+0x78>
    4914:	a0 3e       	lwi333 $r0,[$r7+#0x18]
    4916:	5a 0f ff dc 	bnec $r0,#-1,48ce <lfs_fs_parent+0x2a>
    491a:	84 1e       	movi55 $r0,#-2
    491c:	ec 1c       	addi10.sp #0x1c
    491e:	3a 6f b4 84 	lmw.bim $r6,[$sp],$r13,#0x2    ! {$r6~$r13, $lp}
    4922:	dd 9e       	ret5 $lp
    4924:	44 0f ff ac 	movi $r0,#-84
    4928:	ec 1c       	addi10.sp #0x1c
    492a:	3a 6f b4 84 	lmw.bim $r6,[$sp],$r13,#0x2    ! {$r6~$r13, $lp}
    492e:	dd 9e       	ret5 $lp

00004930 <lfs_fs_pred>:
    4930:	3a 6f ac bc 	smw.adm $r6,[$sp],$r11,#0x2    ! {$r6~$r11, $lp}
    4934:	ef f4       	addi10.sp #-12
    4936:	81 40       	mov55 $r10,$r0
    4938:	84 00       	movi55 $r0,#0x0
    493a:	a8 16       	swi333 $r0,[$r2+#0x18]
    493c:	84 01       	movi55 $r0,#0x1
    493e:	80 e2       	mov55 $r7,$r2
    4940:	81 21       	mov55 $r9,$r1
    4942:	a8 17       	swi333 $r0,[$r2+#0x1c]
    4944:	84 a0       	movi55 $r5,#0x0
    4946:	84 c0       	movi55 $r6,#0x0
    4948:	50 b1 00 18 	addi $r11,$r2,#0x18
    494c:	85 00       	movi55 $r8,#0x0
    494e:	92 00       	nop16
    4950:	05 13 80 07 	lwi $r17,[$r7+#0x1c]
    4954:	5b 17 ff 24 	beqc $r17,#-1,499c <dlm_remain+0x1c>
    4958:	04 15 00 1a 	lwi $r1,[$r10+#0x68]
    495c:	80 0a       	mov55 $r0,$r10
    495e:	05 00 80 08 	lwi $r16,[$r1+#0x20]
    4962:	80 4b       	mov55 $r2,$r11
    4964:	93 81       	srli45 $r16,#0x1
    4966:	e2 d0       	slt45 $r6,$r16
    4968:	80 27       	mov55 $r1,$r7
    496a:	84 7f       	movi55 $r3,#-1
    496c:	84 9f       	movi55 $r4,#-1
    496e:	e8 23       	beqzs8 49b4 <dlm_remain+0x34>
    4970:	b5 c9       	lwi450 $r18,[$r9]
    4972:	8c c1       	addi45 $r6,#0x1
    4974:	4c 59 00 1a 	beq $r5,$r18,49a8 <dlm_remain+0x28>
    4978:	05 04 80 01 	lwi $r16,[$r9+#0x4]
    497c:	4d 08 80 16 	beq $r16,$r17,49a8 <dlm_remain+0x28>
    4980:	4c 58 00 14 	beq $r5,$r16,49a8 <dlm_remain+0x28>
    4984:	4d 28 80 12 	beq $r18,$r17,49a8 <dlm_remain+0x28>
    4988:	84 a0       	movi55 $r5,#0x0
    498a:	b7 1f       	swi450 $r8,[$sp]
    498c:	14 8f 80 01 	swi $r8,[$sp+#0x4]
    4990:	49 ff fc 7c 	jal 4288 <lfs_dir_fetchmatch>
    4994:	c8 06       	bnez38 $r0,49a0 <dlm_remain+0x20>
    4996:	a1 7e       	lwi333 $r5,[$r7+#0x18]
    4998:	5a 5f ff dc 	bnec $r5,#-1,4950 <lfs_fs_pred+0x20>
    499c:	44 0f ff fe 	movi $r0,#-2
    49a0:	ec 0c       	addi10.sp #0xc
    49a2:	3a 6f ac 84 	lmw.bim $r6,[$sp],$r11,#0x2    ! {$r6~$r11, $lp}
    49a6:	dd 9e       	ret5 $lp
    49a8:	84 00       	movi55 $r0,#0x0
    49aa:	ec 0c       	addi10.sp #0xc
    49ac:	3a 6f ac 84 	lmw.bim $r6,[$sp],$r11,#0x2    ! {$r6~$r11, $lp}
    49b0:	dd 9e       	ret5 $lp
    49b2:	92 00       	nop16
    49b4:	44 0f ff ac 	movi $r0,#-84
    49b8:	d5 f4       	j8 49a0 <dlm_remain+0x20>
    49ba:	92 00       	nop16

000049bc <lfs_dir_traverse>:
    49bc:	3a 6f ba bc 	smw.adm $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    49c0:	ef a4       	addi10.sp #-92
    49c2:	36 3f 80 0c 	fsdi $fd3,[$sp+#0x30]
    49c6:	36 4f 80 0e 	fsdi $fd4,[$sp+#0x38]
    49ca:	36 5f 80 10 	fsdi $fd5,[$sp+#0x40]
    49ce:	36 6f 80 12 	fsdi $fd6,[$sp+#0x48]
    49d2:	36 7f 80 14 	fsdi $fd7,[$sp+#0x50]
    49d6:	46 90 00 ff 	sethi $r9,#0xff
    49da:	04 af 80 22 	lwi $r10,[$sp+#0x88]
    49de:	50 94 8c 00 	addi $r9,$r9,#0xc00
    49e2:	6a 06 00 09 	fmtsr $r0,$fs12
    49e6:	02 0f 80 48 	lhi $r0,[$sp+#0x90]
    49ea:	41 05 24 02 	and $r16,$r10,$r9
    49ee:	22 ef 80 4c 	lhsi $r14,[$sp+#0x98]
    49f2:	6a 05 00 09 	fmtsr $r0,$fs10
    49f6:	02 0f 80 4a 	lhi $r0,[$sp+#0x94]
    49fa:	6a 05 80 09 	fmtsr $r0,$fs11
    49fe:	40 08 28 09 	srli $r0,$r16,#0xa
    4a02:	6a 03 00 09 	fmtsr $r0,$fs6
    4a06:	40 07 28 08 	slli $r0,$r14,#0xa
    4a0a:	6a 04 80 09 	fmtsr $r0,$fs9
    4a0e:	46 06 00 ff 	sethi $r0,#0x600ff
    4a12:	47 17 ff 00 	sethi $r17,#0x7ff00
    4a16:	50 00 0c 00 	addi $r0,$r0,#0xc00
    4a1a:	6b 13 80 09 	fmtsr $r17,$fs7
    4a1e:	6a 04 00 09 	fmtsr $r0,$fs8
    4a22:	30 ff 80 23 	flsi $fs15,[$sp+#0x8c]
    4a26:	30 ef 80 27 	flsi $fs14,[$sp+#0x9c]
    4a2a:	30 df 80 28 	flsi $fs13,[$sp+#0xa0]
    4a2e:	81 a1       	mov55 $r13,$r1
    4a30:	81 02       	mov55 $r8,$r2
    4a32:	81 83       	mov55 $r12,$r3
    4a34:	83 84       	mov55 $fp,$r4
    4a36:	80 e5       	mov55 $r7,$r5
    4a38:	40 a5 44 02 	and $r10,$r10,$r17
    4a3c:	41 06 58 08 	slli $r16,$r12,#0x16
    4a40:	91 96       	srai45 $r16,#0x16
    4a42:	8d 81       	addi45 $r16,#0x1
    4a44:	e7 81       	slti45 $r16,#0x1
    4a46:	40 f7 b0 00 	add $r15,$r15,$r12
    4a4a:	50 64 00 04 	addi $r6,$r8,#0x4
    4a4e:	55 07 83 ff 	andi $r16,$r15,#0x3ff
    4a52:	04 06 80 03 	lwi $r0,[$r13+#0xc]
    4a56:	88 d0       	add45 $r6,$r16
    4a58:	e2 c0       	slt45 $r6,$r0
    4a5a:	e9 57       	bnezs8 4b08 <lfs_dir_traverse+0x14c>
    4a5c:	4e 77 00 d6 	blez $r7,4c08 <lfs_dir_traverse+0x24c>
    4a60:	b5 9c       	lwi450 $r16,[$fp]
    4a62:	be 01       	lwi37 $r6,[$fp+#0x4]
    4a64:	15 0f 80 09 	swi $r16,[$sp+#0x24]
    4a68:	51 ce 00 08 	addi $fp,$fp,#0x8
    4a6c:	8e e1       	subi45 $r7,#0x1
    4a6e:	92 00       	nop16
    4a70:	6a 07 80 01 	fmfsr $r0,$fs15
    4a74:	40 08 00 03 	xor $r0,$r16,$r0
    4a78:	40 05 00 02 	and $r0,$r10,$r0
    4a7c:	c8 e0       	bnez38 $r0,4a3c <lfs_dir_traverse+0x80>
    4a7e:	6a 13 00 01 	fmfsr $r1,$fs6
    4a82:	c9 67       	bnez38 $r1,4b50 <lfs_dir_traverse+0x194>
    4a84:	6a 03 80 01 	fmfsr $r0,$fs7
    4a88:	40 08 00 02 	and $r0,$r16,$r0
    4a8c:	92 14       	srli45 $r0,#0x14
    4a8e:	c0 d7       	beqz38 $r0,4a3c <lfs_dir_traverse+0x80>
    4a90:	5a 09 01 04 	bnec $r0,#0x101,4a98 <lfs_dir_traverse+0xdc>
    4a94:	48 00 00 96 	j 4bc0 <lfs_dir_traverse+0x204>
    4a98:	5a 01 02 04 	beqc $r0,#0x102,4aa0 <lfs_dir_traverse+0xe4>
    4a9c:	48 00 00 84 	j 4ba4 <lfs_dir_traverse+0x1e8>
    4aa0:	54 08 03 ff 	andi $r0,$r16,#0x3ff
    4aa4:	c0 cc       	beqz38 $r0,4a3c <lfs_dir_traverse+0x80>
    4aa6:	85 60       	movi55 $r11,#0x0
    4aa8:	d5 0a       	j8 4abc <lfs_dir_traverse+0x100>
    4aaa:	92 00       	nop16
    4aac:	05 0f 80 09 	lwi $r16,[$sp+#0x24]
    4ab0:	8c cc       	addi45 $r6,#0xc
    4ab2:	54 08 03 ff 	andi $r0,$r16,#0x3ff
    4ab6:	e3 60       	slt45 $r11,$r0
    4ab8:	e8 c2       	beqzs8 4a3c <lfs_dir_traverse+0x80>
    4aba:	92 00       	nop16
    4abc:	41 08 24 02 	and $r16,$r16,$r9
    4ac0:	a7 70       	lbi333 $r5,[$r6+#0x0]
    4ac2:	93 8a       	srli45 $r16,#0xa
    4ac4:	a0 72       	lwi333 $r1,[$r6+#0x8]
    4ac6:	89 8e       	add45 $r16,$r14
    4ac8:	41 08 28 08 	slli $r16,$r16,#0xa
    4acc:	50 52 83 00 	addi $r5,$r5,#0x300
    4ad0:	40 18 04 04 	or $r1,$r16,$r1
    4ad4:	40 52 d0 08 	slli $r5,$r5,#0x14
    4ad8:	6a 06 80 01 	fmfsr $r0,$fs13
    4adc:	6a 37 00 01 	fmfsr $r3,$fs14
    4ae0:	a0 b1       	lwi333 $r2,[$r6+#0x4]
    4ae2:	fe 6f       	or33 $r1,$r5
    4ae4:	8d 61       	addi45 $r11,#0x1
    4ae6:	dd 23       	jral5 $r3
    4ae8:	c0 e2       	beqz38 $r0,4aac <lfs_dir_traverse+0xf0>
    4aea:	92 00       	nop16
    4aec:	ec 30       	addi10.sp #0x30
    4aee:	34 3f 90 02 	fldi.bi $fd3,[$sp],#0x8
    4af2:	34 4f 90 02 	fldi.bi $fd4,[$sp],#0x8
    4af6:	34 5f 90 02 	fldi.bi $fd5,[$sp],#0x8
    4afa:	34 6f 90 02 	fldi.bi $fd6,[$sp],#0x8
    4afe:	34 7f 90 03 	fldi.bi $fd7,[$sp],#0xc
    4b02:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    4b06:	dd 9e       	ret5 $lp
    4b08:	b0 09       	addri36.sp $r0,#0x24
    4b0a:	b6 1f       	swi450 $r0,[$sp]
    4b0c:	84 04       	movi55 $r0,#0x4
    4b0e:	f0 81       	swi37.sp $r0,[+#0x4]
    4b10:	6a 06 00 01 	fmfsr $r0,$fs12
    4b14:	6a 26 00 01 	fmfsr $r2,$fs12
    4b18:	50 00 00 68 	addi $r0,$r0,#0x68
    4b1c:	84 20       	movi55 $r1,#0x0
    4b1e:	84 64       	movi55 $r3,#0x4
    4b20:	b4 8d       	lwi450 $r4,[$r13]
    4b22:	80 a6       	mov55 $r5,$r6
    4b24:	49 ff fa be 	jal 40a0 <lfs_bd_read.isra.13>
    4b28:	c8 e2       	bnez38 $r0,4aec <lfs_dir_traverse+0x130>
    4b2a:	f0 09       	lwi37.sp $r0,[+#0x24]
    4b2c:	b4 2d       	lwi450 $r1,[$r13]
    4b2e:	40 00 00 14 	wsbh $r0,$r0
    4b32:	40 00 40 0b 	rotri $r0,$r0,#0x10
    4b36:	40 00 30 03 	xor $r0,$r0,$r12
    4b3a:	42 c0 7c 08 	bset $r12,$r0,#0x1f
    4b3e:	9c 34       	addi333 $r0,$r6,#0x4
    4b40:	81 06       	mov55 $r8,$r6
    4b42:	14 cf 80 09 	swi $r12,[$sp+#0x24]
    4b46:	f1 8a       	swi37.sp $r1,[+#0x28]
    4b48:	f0 8b       	swi37.sp $r0,[+#0x2c]
    4b4a:	82 0c       	mov55 $r16,$r12
    4b4c:	b1 8a       	addri36.sp $r6,#0x28
    4b4e:	d5 91       	j8 4a70 <lfs_dir_traverse+0xb4>
    4b50:	b6 1f       	swi450 $r0,[$sp]
    4b52:	f0 81       	swi37.sp $r0,[+#0x4]
    4b54:	f0 82       	swi37.sp $r0,[+#0x8]
    4b56:	f0 83       	swi37.sp $r0,[+#0xc]
    4b58:	f0 84       	swi37.sp $r0,[+#0x10]
    4b5a:	44 00 35 c8 	movi $r0,#0x35c8
    4b5e:	f0 85       	swi37.sp $r0,[+#0x14]
    4b60:	b0 09       	addri36.sp $r0,#0x24
    4b62:	f0 86       	swi37.sp $r0,[+#0x18]
    4b64:	6a 06 00 01 	fmfsr $r0,$fs12
    4b68:	80 2d       	mov55 $r1,$r13
    4b6a:	80 48       	mov55 $r2,$r8
    4b6c:	80 6c       	mov55 $r3,$r12
    4b6e:	80 9c       	mov55 $r4,$fp
    4b70:	50 53 80 00 	addi $r5,$r7,#0x0
    4b74:	49 ff ff 24 	jal 49bc <lfs_dir_traverse>
    4b78:	4e 05 ff ba 	bltz $r0,4aec <lfs_dir_traverse+0x130>
    4b7c:	4e 03 ff 60 	bnez $r0,4a3c <lfs_dir_traverse+0x80>
    4b80:	05 0f 80 09 	lwi $r16,[$sp+#0x24]
    4b84:	6a 15 00 01 	fmfsr $r1,$fs10
    4b88:	40 08 24 02 	and $r0,$r16,$r9
    4b8c:	92 0a       	srli45 $r0,#0xa
    4b8e:	96 01       	zeh33 $r0,$r0
    4b90:	e2 01       	slt45 $r0,$r1
    4b92:	4e f3 ff 55 	bnez $r15,4a3c <lfs_dir_traverse+0x80>
    4b96:	6a 15 80 01 	fmfsr $r1,$fs11
    4b9a:	e2 01       	slt45 $r0,$r1
    4b9c:	4e f2 ff 50 	beqz $r15,4a3c <lfs_dir_traverse+0x80>
    4ba0:	48 ff ff 72 	j 4a84 <lfs_dir_traverse+0xc8>
    4ba4:	6a 14 80 01 	fmfsr $r1,$fs9
    4ba8:	6a 06 80 01 	fmfsr $r0,$fs13
    4bac:	6a 37 00 01 	fmfsr $r3,$fs14
    4bb0:	88 30       	add45 $r1,$r16
    4bb2:	80 46       	mov55 $r2,$r6
    4bb4:	4b e0 0c 01 	jral $lp,$r3
    4bb8:	4e 02 ff 42 	beqz $r0,4a3c <lfs_dir_traverse+0x80>
    4bbc:	d5 98       	j8 4aec <lfs_dir_traverse+0x130>
    4bbe:	92 00       	nop16
    4bc0:	40 08 24 02 	and $r0,$r16,$r9
    4bc4:	92 0a       	srli45 $r0,#0xa
    4bc6:	55 08 03 ff 	andi $r16,$r16,#0x3ff
    4bca:	8a 10       	sub45 $r0,$r16
    4bcc:	88 0e       	add45 $r0,$r14
    4bce:	96 03       	seh33 $r0,$r0
    4bd0:	50 18 00 01 	addi $r1,$r16,#0x1
    4bd4:	46 22 00 00 	sethi $r2,#0x20000
    4bd8:	f0 84       	swi37.sp $r0,[+#0x10]
    4bda:	6a 06 00 01 	fmfsr $r0,$fs12
    4bde:	f2 81       	swi37.sp $r2,[+#0x4]
    4be0:	f1 83       	swi37.sp $r1,[+#0xc]
    4be2:	32 8f 80 00 	fssi $fs8,[$sp+#0x0]
    4be6:	15 0f 80 02 	swi $r16,[$sp+#0x8]
    4bea:	32 ef 80 05 	fssi $fs14,[$sp+#0x14]
    4bee:	32 df 80 06 	fssi $fs13,[$sp+#0x18]
    4bf2:	80 26       	mov55 $r1,$r6
    4bf4:	84 40       	movi55 $r2,#0x0
    4bf6:	84 7f       	movi55 $r3,#-1
    4bf8:	84 80       	movi55 $r4,#0x0
    4bfa:	84 a0       	movi55 $r5,#0x0
    4bfc:	49 ff fe e0 	jal 49bc <lfs_dir_traverse>
    4c00:	4e 02 ff 1e 	beqz $r0,4a3c <lfs_dir_traverse+0x80>
    4c04:	48 ff ff 74 	j 4aec <lfs_dir_traverse+0x130>
    4c08:	84 00       	movi55 $r0,#0x0
    4c0a:	48 ff ff 71 	j 4aec <lfs_dir_traverse+0x130>
    4c0e:	92 00       	nop16

00004c10 <lfs_fs_preporphans.isra.14>:
    4c10:	b4 40       	lwi450 $r2,[$r0]
    4c12:	54 31 03 ff 	andi $r3,$r2,#0x3ff
    4c16:	cb 03       	bnez38 $r3,4c1c <lfs_fs_preporphans.isra.14+0xc>
    4c18:	4e 15 00 0e 	bltz $r1,4c34 <lfs_fs_preporphans.isra.14+0x24>
    4c1c:	88 41       	add45 $r2,$r1
    4c1e:	54 31 03 ff 	andi $r3,$r2,#0x3ff
    4c22:	84 20       	movi55 $r1,#0x0
    4c24:	e2 23       	slt45 $r1,$r3
    4c26:	40 17 fc 08 	slli $r1,$r15,#0x1f
    4c2a:	42 21 7c 09 	bclr $r2,$r2,#0x1f
    4c2e:	fe 8f       	or33 $r2,$r1
    4c30:	b6 40       	swi450 $r2,[$r0]
    4c32:	dd 9e       	ret5 $lp
    4c34:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    4c38:	44 00 36 cc 	movi $r0,#0x36cc
    4c3c:	44 10 10 03 	movi $r1,#0x1003
    4c40:	44 20 7c a8 	movi $r2,#0x7ca8
    4c44:	44 30 39 68 	movi $r3,#0x3968
    4c48:	49 00 27 e6 	jal 9c14 <__assert_func>
    4c4c:	92 00       	nop16
    4c4e:	92 00       	nop16

00004c50 <lfs_bd_erase.isra.16>:
    4c50:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    4c54:	04 20 00 08 	lwi $r2,[$r0+#0x20]
    4c58:	e2 22       	slt45 $r1,$r2
    4c5a:	e8 09       	beqzs8 4c6c <lfs_bd_erase.isra.16+0x1c>
    4c5c:	a0 83       	lwi333 $r2,[$r0+#0xc]
    4c5e:	dd 22       	jral5 $r2
    4c60:	4e 06 00 12 	bgtz $r0,4c84 <lfs_bd_erase.isra.16+0x34>
    4c64:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    4c68:	dd 9e       	ret5 $lp
    4c6a:	92 00       	nop16
    4c6c:	44 00 36 cc 	movi $r0,#0x36cc
    4c70:	44 10 00 e9 	movi $r1,#0xe9
    4c74:	44 20 7c 74 	movi $r2,#0x7c74
    4c78:	44 30 39 a4 	movi $r3,#0x39a4
    4c7c:	49 00 27 cc 	jal 9c14 <__assert_func>
    4c80:	92 00       	nop16
    4c82:	92 00       	nop16
    4c84:	44 00 36 cc 	movi $r0,#0x36cc
    4c88:	44 10 00 eb 	movi $r1,#0xeb
    4c8c:	44 20 7c 74 	movi $r2,#0x7c74
    4c90:	44 30 39 24 	movi $r3,#0x3924
    4c94:	49 00 27 c0 	jal 9c14 <__assert_func>
    4c98:	92 00       	nop16
    4c9a:	92 00       	nop16

00004c9c <lfs_ctz_index.isra.23>:
    4c9c:	3a 6f a8 bc 	smw.adm $r6,[$sp],$r10,#0x2    ! {$r6~$r10, $lp}
    4ca0:	04 80 00 07 	lwi $r8,[$r0+#0x1c]
    4ca4:	b4 e1       	lwi450 $r7,[$r1]
    4ca6:	8f 08       	subi45 $r8,#0x8
    4ca8:	40 03 a0 17 	divr $r0,$r0,$r7,$r8
    4cac:	c0 17       	beqz38 $r0,4cda <lfs_ctz_index.isra.23+0x3e>
    4cae:	8e 01       	subi45 $r0,#0x1
    4cb0:	81 21       	mov55 $r9,$r1
    4cb2:	49 00 20 89 	jal 8dc4 <__popcountsi2>
    4cb6:	8c 02       	addi45 $r0,#0x2
    4cb8:	95 82       	slli333 $r6,$r0,#0x2
    4cba:	9b be       	sub333 $r6,$r7,$r6
    4cbc:	40 63 20 d7 	divr $r6,$r6,$r6,$r8
    4cc0:	50 03 00 00 	addi $r0,$r6,#0x0
    4cc4:	49 00 20 80 	jal 8dc4 <__popcountsi2>
    4cc8:	42 73 20 75 	msubr32 $r7,$r6,$r8
    4ccc:	94 02       	slli333 $r0,$r0,#0x2
    4cce:	8a e0       	sub45 $r7,$r0
    4cd0:	b6 e9       	swi450 $r7,[$r9]
    4cd2:	80 06       	mov55 $r0,$r6
    4cd4:	3a 6f a8 84 	lmw.bim $r6,[$sp],$r10,#0x2    ! {$r6~$r10, $lp}
    4cd8:	dd 9e       	ret5 $lp
    4cda:	84 00       	movi55 $r0,#0x0
    4cdc:	3a 6f a8 84 	lmw.bim $r6,[$sp],$r10,#0x2    ! {$r6~$r10, $lp}
    4ce0:	dd 9e       	ret5 $lp
    4ce2:	92 00       	nop16

00004ce4 <lfs_ctz_traverse.part.24>:
    4ce4:	3a 6f b8 bc 	smw.adm $r6,[$sp],$r14,#0x2    ! {$r6~$r14, $lp}
    4ce8:	ef e8       	addi10.sp #-24
    4cea:	82 00       	mov55 $r16,$r0
    4cec:	8e 81       	subi45 $r4,#0x1
    4cee:	81 c1       	mov55 $r14,$r1
    4cf0:	04 00 00 1a 	lwi $r0,[$r0+#0x68]
    4cf4:	b0 43       	addri36.sp $r1,#0xc
    4cf6:	81 a2       	mov55 $r13,$r2
    4cf8:	81 03       	mov55 $r8,$r3
    4cfa:	81 25       	mov55 $r9,$r5
    4cfc:	f6 10       	lwi37.sp $r6,[+#0x40]
    4cfe:	f4 83       	swi37.sp $r4,[+#0xc]
    4d00:	50 c8 00 68 	addi $r12,$r16,#0x68
    4d04:	49 ff ff cc 	jal 4c9c <lfs_ctz_index.isra.23>
    4d08:	81 60       	mov55 $r11,$r0
    4d0a:	b1 c4       	addri36.sp $r7,#0x10
    4d0c:	80 06       	mov55 $r0,$r6
    4d0e:	80 28       	mov55 $r1,$r8
    4d10:	dd 29       	jral5 $r9
    4d12:	c8 23       	bnez38 $r0,4d58 <lfs_ctz_traverse.part.24+0x74>
    4d14:	4e b2 00 21 	beqz $r11,4d56 <lfs_ctz_traverse.part.24+0x72>
    4d18:	54 a5 80 01 	andi $r10,$r11,#0x1
    4d1c:	52 a5 00 02 	subri $r10,$r10,#0x2
    4d20:	40 35 08 08 	slli $r3,$r10,#0x2
    4d24:	b6 ff       	swi450 $r7,[$sp]
    4d26:	f3 81       	swi37.sp $r3,[+#0x4]
    4d28:	80 0c       	mov55 $r0,$r12
    4d2a:	80 2e       	mov55 $r1,$r14
    4d2c:	80 4d       	mov55 $r2,$r13
    4d2e:	80 88       	mov55 $r4,$r8
    4d30:	84 a0       	movi55 $r5,#0x0
    4d32:	49 ff f9 b7 	jal 40a0 <lfs_bd_read.isra.13>
    4d36:	c8 11       	bnez38 $r0,4d58 <lfs_ctz_traverse.part.24+0x74>
    4d38:	50 85 7f ff 	addi $r8,$r10,#-1
    4d3c:	84 60       	movi55 $r3,#0x0
    4d3e:	d5 05       	j8 4d48 <lfs_ctz_traverse.part.24+0x64>
    4d40:	b4 27       	lwi450 $r1,[$r7]
    4d42:	dd 29       	jral5 $r9
    4d44:	84 61       	movi55 $r3,#0x1
    4d46:	c8 09       	bnez38 $r0,4d58 <lfs_ctz_traverse.part.24+0x74>
    4d48:	e0 68       	slts45 $r3,$r8
    4d4a:	80 06       	mov55 $r0,$r6
    4d4c:	e9 fa       	bnezs8 4d40 <lfs_ctz_traverse.part.24+0x5c>
    4d4e:	38 83 a2 02 	lw $r8,[$r7+($r8<<#0x2)]
    4d52:	8b 6a       	sub45 $r11,$r10
    4d54:	d5 dc       	j8 4d0c <lfs_ctz_traverse.part.24+0x28>
    4d56:	84 00       	movi55 $r0,#0x0
    4d58:	ec 18       	addi10.sp #0x18
    4d5a:	3a 6f b8 84 	lmw.bim $r6,[$sp],$r14,#0x2    ! {$r6~$r14, $lp}
    4d5e:	dd 9e       	ret5 $lp

00004d60 <lfs_ctz_find.constprop.32>:
    4d60:	3a 6f b8 bc 	smw.adm $r6,[$sp],$r14,#0x2    ! {$r6~$r14, $lp}
    4d64:	ef e8       	addi10.sp #-24
    4d66:	f2 83       	swi37.sp $r2,[+#0xc]
    4d68:	f4 82       	swi37.sp $r4,[+#0x8]
    4d6a:	cb 0b       	bnez38 $r3,4d80 <lfs_ctz_find.constprop.32+0x20>
    4d6c:	f1 10       	lwi37.sp $r1,[+#0x40]
    4d6e:	84 1f       	movi55 $r0,#-1
    4d70:	b6 05       	swi450 $r0,[$r5]
    4d72:	84 00       	movi55 $r0,#0x0
    4d74:	b6 61       	swi450 $r3,[$r1]
    4d76:	92 00       	nop16
    4d78:	ec 18       	addi10.sp #0x18
    4d7a:	3a 6f b8 84 	lmw.bim $r6,[$sp],$r14,#0x2    ! {$r6~$r14, $lp}
    4d7e:	dd 9e       	ret5 $lp
    4d80:	81 20       	mov55 $r9,$r0
    4d82:	8e 61       	subi45 $r3,#0x1
    4d84:	81 41       	mov55 $r10,$r1
    4d86:	04 00 00 1a 	lwi $r0,[$r0+#0x68]
    4d8a:	b0 45       	addri36.sp $r1,#0x14
    4d8c:	81 c5       	mov55 $r14,$r5
    4d8e:	f3 85       	swi37.sp $r3,[+#0x14]
    4d90:	49 ff ff 86 	jal 4c9c <lfs_ctz_index.isra.23>
    4d94:	80 e0       	mov55 $r7,$r0
    4d96:	b0 42       	addri36.sp $r1,#0x8
    4d98:	04 04 80 1a 	lwi $r0,[$r9+#0x68]
    4d9c:	49 ff ff 80 	jal 4c9c <lfs_ctz_index.isra.23>
    4da0:	81 00       	mov55 $r8,$r0
    4da2:	40 00 1c 06 	slt $r0,$r0,$r7
    4da6:	50 94 80 68 	addi $r9,$r9,#0x68
    4daa:	50 df 80 0c 	addi $r13,$sp,#0xc
    4dae:	85 84       	movi55 $r12,#0x4
    4db0:	85 61       	movi55 $r11,#0x1
    4db2:	c0 24       	beqz38 $r0,4dfa <lfs_ctz_find.constprop.32+0x9a>
    4db4:	fe fa       	neg33 $r3,$r7
    4db6:	fe fe       	and33 $r3,$r7
    4db8:	40 63 a0 01 	sub $r6,$r7,$r8
    4dbc:	42 63 00 07 	clz $r6,$r6
    4dc0:	42 31 80 07 	clz $r3,$r3
    4dc4:	52 31 80 1f 	subri $r3,$r3,#0x1f
    4dc8:	52 63 00 1f 	subri $r6,$r6,#0x1f
    4dcc:	e2 66       	slt45 $r3,$r6
    4dce:	40 61 bc 1b 	cmovn $r6,$r3,$r15
    4dd2:	14 df 80 00 	swi $r13,[$sp+#0x0]
    4dd6:	84 64       	movi55 $r3,#0x4
    4dd8:	14 cf 80 01 	swi $r12,[$sp+#0x4]
    4ddc:	80 09       	mov55 $r0,$r9
    4dde:	84 20       	movi55 $r1,#0x0
    4de0:	80 4a       	mov55 $r2,$r10
    4de2:	f4 03       	lwi37.sp $r4,[+#0xc]
    4de4:	40 53 08 08 	slli $r5,$r6,#0x2
    4de8:	49 ff f9 5c 	jal 40a0 <lfs_bd_read.isra.13>
    4dec:	40 35 98 0c 	sll $r3,$r11,$r6
    4df0:	8a e3       	sub45 $r7,$r3
    4df2:	40 34 1c 06 	slt $r3,$r8,$r7
    4df6:	c8 c1       	bnez38 $r0,4d78 <lfs_ctz_find.constprop.32+0x18>
    4df8:	cb de       	bnez38 $r3,4db4 <lfs_ctz_find.constprop.32+0x54>
    4dfa:	f2 10       	lwi37.sp $r2,[+#0x40]
    4dfc:	f0 03       	lwi37.sp $r0,[+#0xc]
    4dfe:	f1 02       	lwi37.sp $r1,[+#0x8]
    4e00:	b6 0e       	swi450 $r0,[$r14]
    4e02:	84 00       	movi55 $r0,#0x0
    4e04:	b6 22       	swi450 $r1,[$r2]
    4e06:	ec 18       	addi10.sp #0x18
    4e08:	3a 6f b8 84 	lmw.bim $r6,[$sp],$r14,#0x2    ! {$r6~$r14, $lp}
    4e0c:	dd 9e       	ret5 $lp
    4e0e:	92 00       	nop16

00004e10 <lfs_bd_cmp.constprop.35>:
    4e10:	3a 6f b8 bc 	smw.adm $r6,[$sp],$r14,#0x2    ! {$r6~$r14, $lp}
    4e14:	ef f0       	addi10.sp #-16
    4e16:	04 af 80 0e 	lwi $r10,[$sp+#0x38]
    4e1a:	4e a2 00 2b 	beqz $r10,4e70 <lfs_bd_cmp.constprop.35+0x60>
    4e1e:	81 04       	mov55 $r8,$r4
    4e20:	81 83       	mov55 $r12,$r3
    4e22:	80 e2       	mov55 $r7,$r2
    4e24:	81 61       	mov55 $r11,$r1
    4e26:	80 c5       	mov55 $r6,$r5
    4e28:	50 90 00 68 	addi $r9,$r0,#0x68
    4e2c:	89 45       	add45 $r10,$r5
    4e2e:	8b 05       	sub45 $r8,$r5
    4e30:	50 ef 80 0f 	addi $r14,$sp,#0xf
    4e34:	85 a1       	movi55 $r13,#0x1
    4e36:	d5 0b       	j8 4e4c <lfs_bd_cmp.constprop.35+0x3c>
    4e38:	08 13 00 01 	lbi.bi $r1,[$r6],#0x1
    4e3c:	00 5f 80 0f 	lbi $r5,[$sp+#0xf]
    4e40:	8e e1       	subi45 $r7,#0x1
    4e42:	4c 12 c0 1d 	bne $r1,$r5,4e7c <lfs_bd_cmp.constprop.35+0x6c>
    4e46:	4c 65 00 15 	beq $r6,$r10,4e70 <lfs_bd_cmp.constprop.35+0x60>
    4e4a:	92 00       	nop16
    4e4c:	40 54 18 00 	add $r5,$r8,$r6
    4e50:	80 67       	mov55 $r3,$r7
    4e52:	14 ef 80 00 	swi $r14,[$sp+#0x0]
    4e56:	14 df 80 01 	swi $r13,[$sp+#0x4]
    4e5a:	80 09       	mov55 $r0,$r9
    4e5c:	84 20       	movi55 $r1,#0x0
    4e5e:	80 4b       	mov55 $r2,$r11
    4e60:	80 8c       	mov55 $r4,$r12
    4e62:	49 ff f9 1f 	jal 40a0 <lfs_bd_read.isra.13>
    4e66:	c0 e9       	beqz38 $r0,4e38 <lfs_bd_cmp.constprop.35+0x28>
    4e68:	ec 10       	addi10.sp #0x10
    4e6a:	3a 6f b8 84 	lmw.bim $r6,[$sp],$r14,#0x2    ! {$r6~$r14, $lp}
    4e6e:	dd 9e       	ret5 $lp
    4e70:	84 00       	movi55 $r0,#0x0
    4e72:	ec 10       	addi10.sp #0x10
    4e74:	3a 6f b8 84 	lmw.bim $r6,[$sp],$r14,#0x2    ! {$r6~$r14, $lp}
    4e78:	dd 9e       	ret5 $lp
    4e7a:	92 00       	nop16
    4e7c:	e2 a1       	slt45 $r5,$r1
    4e7e:	84 02       	movi55 $r0,#0x2
    4e80:	84 21       	movi55 $r1,#0x1
    4e82:	40 00 bc 1b 	cmovn $r0,$r1,$r15
    4e86:	ec 10       	addi10.sp #0x10
    4e88:	3a 6f b8 84 	lmw.bim $r6,[$sp],$r14,#0x2    ! {$r6~$r14, $lp}
    4e8c:	dd 9e       	ret5 $lp
    4e8e:	92 00       	nop16

00004e90 <lfs_bd_flush>:
    4e90:	3a 6f a8 bc 	smw.adm $r6,[$sp],$r10,#0x2    ! {$r6~$r10, $lp}
    4e94:	ef f8       	addi10.sp #-8
    4e96:	80 e1       	mov55 $r7,$r1
    4e98:	b4 21       	lwi450 $r1,[$r1]
    4e9a:	9d 0a       	addi333 $r4,$r1,#0x2
    4e9c:	e6 82       	slti45 $r4,#0x2
    4e9e:	e9 3b       	bnezs8 4f14 <lfs_bd_flush+0x84>
    4ea0:	81 00       	mov55 $r8,$r0
    4ea2:	04 00 00 1a 	lwi $r0,[$r0+#0x68]
    4ea6:	81 23       	mov55 $r9,$r3
    4ea8:	04 40 00 08 	lwi $r4,[$r0+#0x20]
    4eac:	81 42       	mov55 $r10,$r2
    4eae:	e2 24       	slt45 $r1,$r4
    4eb0:	e8 48       	beqzs8 4f40 <lfs_bd_flush+0xb0>
    4eb2:	a1 86       	lwi333 $r6,[$r0+#0x18]
    4eb4:	a1 7a       	lwi333 $r5,[$r7+#0x8]
    4eb6:	05 00 00 02 	lwi $r16,[$r0+#0x8]
    4eba:	99 35       	add333 $r4,$r6,$r5
    4ebc:	8e 81       	subi45 $r4,#0x1
    4ebe:	40 52 18 d7 	divr $r5,$r6,$r4,$r6
    4ec2:	9b a6       	sub333 $r6,$r4,$r6
    4ec4:	a0 b9       	lwi333 $r2,[$r7+#0x4]
    4ec6:	a0 fb       	lwi333 $r3,[$r7+#0xc]
    4ec8:	80 86       	mov55 $r4,$r6
    4eca:	dd 30       	jral5 $r16
    4ecc:	4e 06 00 2e 	bgtz $r0,4f28 <lfs_bd_flush+0x98>
    4ed0:	c8 1e       	bnez38 $r0,4f0c <lfs_bd_flush+0x7c>
    4ed2:	4e 92 00 11 	beqz $r9,4ef4 <lfs_bd_flush+0x64>
    4ed6:	84 1f       	movi55 $r0,#-1
    4ed8:	b6 0a       	swi450 $r0,[$r10]
    4eda:	b6 df       	swi450 $r6,[$sp]
    4edc:	80 08       	mov55 $r0,$r8
    4ede:	80 2a       	mov55 $r1,$r10
    4ee0:	80 46       	mov55 $r2,$r6
    4ee2:	b4 67       	lwi450 $r3,[$r7]
    4ee4:	a1 39       	lwi333 $r4,[$r7+#0x4]
    4ee6:	a1 7b       	lwi333 $r5,[$r7+#0xc]
    4ee8:	49 ff ff 94 	jal 4e10 <lfs_bd_cmp.constprop.35>
    4eec:	4e 05 00 10 	bltz $r0,4f0c <lfs_bd_flush+0x7c>
    4ef0:	c8 18       	bnez38 $r0,4f20 <lfs_bd_flush+0x90>
    4ef2:	92 00       	nop16
    4ef4:	04 24 00 1a 	lwi $r2,[$r8+#0x68]
    4ef8:	a0 3b       	lwi333 $r0,[$r7+#0xc]
    4efa:	44 10 00 ff 	movi $r1,#0xff
    4efe:	04 21 00 0a 	lwi $r2,[$r2+#0x28]
    4f02:	49 00 28 59 	jal 9fb4 <memset>
    4f06:	84 1f       	movi55 $r0,#-1
    4f08:	b6 07       	swi450 $r0,[$r7]
    4f0a:	84 00       	movi55 $r0,#0x0
    4f0c:	ec 08       	addi10.sp #0x8
    4f0e:	3a 6f a8 84 	lmw.bim $r6,[$sp],$r10,#0x2    ! {$r6~$r10, $lp}
    4f12:	dd 9e       	ret5 $lp
    4f14:	84 00       	movi55 $r0,#0x0
    4f16:	ec 08       	addi10.sp #0x8
    4f18:	3a 6f a8 84 	lmw.bim $r6,[$sp],$r10,#0x2    ! {$r6~$r10, $lp}
    4f1c:	dd 9e       	ret5 $lp
    4f1e:	92 00       	nop16
    4f20:	44 0f ff ac 	movi $r0,#-84
    4f24:	d5 f4       	j8 4f0c <lfs_bd_flush+0x7c>
    4f26:	92 00       	nop16
    4f28:	44 00 36 cc 	movi $r0,#0x36cc
    4f2c:	44 10 00 92 	movi $r1,#0x92
    4f30:	44 20 7c 58 	movi $r2,#0x7c58
    4f34:	44 30 39 24 	movi $r3,#0x3924
    4f38:	49 00 26 6e 	jal 9c14 <__assert_func>
    4f3c:	92 00       	nop16
    4f3e:	92 00       	nop16
    4f40:	44 00 36 cc 	movi $r0,#0x36cc
    4f44:	44 10 00 8e 	movi $r1,#0x8e
    4f48:	44 20 7c 58 	movi $r2,#0x7c58
    4f4c:	44 30 39 9c 	movi $r3,#0x399c
    4f50:	49 00 26 62 	jal 9c14 <__assert_func>
    4f54:	92 00       	nop16
    4f56:	92 00       	nop16

00004f58 <lfs_bd_prog>:
    4f58:	3a 6f ba bc 	smw.adm $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    4f5c:	ef fc       	addi10.sp #-4
    4f5e:	80 c1       	mov55 $r6,$r1
    4f60:	81 04       	mov55 $r8,$r4
    4f62:	81 40       	mov55 $r10,$r0
    4f64:	81 c2       	mov55 $r14,$r2
    4f66:	83 83       	mov55 $fp,$r3
    4f68:	80 e5       	mov55 $r7,$r5
    4f6a:	04 9f 80 0c 	lwi $r9,[$sp+#0x30]
    4f6e:	04 cf 80 0d 	lwi $r12,[$sp+#0x34]
    4f72:	04 10 00 1a 	lwi $r1,[$r0+#0x68]
    4f76:	5a 47 fe 07 	beqc $r4,#-2,4f84 <lfs_bd_prog+0x2c>
    4f7a:	04 00 80 08 	lwi $r0,[$r1+#0x20]
    4f7e:	e2 80       	slt45 $r4,$r0
    4f80:	4e f2 00 6e 	beqz $r15,505c <lfs_bd_prog+0x104>
    4f84:	a0 0f       	lwi333 $r0,[$r1+#0x1c]
    4f86:	40 13 b0 00 	add $r1,$r7,$r12
    4f8a:	e2 01       	slt45 $r0,$r1
    4f8c:	e9 5c       	bnezs8 5044 <lfs_bd_prog+0xec>
    4f8e:	85 60       	movi55 $r11,#0x0
    4f90:	4e c3 00 13 	bnez $r12,4fb6 <lfs_bd_prog+0x5e>
    4f94:	d5 3e       	j8 5010 <lfs_bd_prog+0xb8>
    4f96:	92 00       	nop16
    4f98:	5a 5f ff 4a 	bnec $r5,#-1,502c <lfs_bd_prog+0xd4>
    4f9c:	04 45 00 1a 	lwi $r4,[$r10+#0x68]
    4fa0:	b7 06       	swi450 $r8,[$r6]
    4fa2:	05 02 00 06 	lwi $r16,[$r4+#0x18]
    4fa6:	14 b3 00 02 	swi $r11,[$r6+#0x8]
    4faa:	41 13 c2 17 	divr $r17,$r16,$r7,$r16
    4fae:	41 03 c0 01 	sub $r16,$r7,$r16
    4fb2:	15 03 00 01 	swi $r16,[$r6+#0x4]
    4fb6:	b4 a6       	lwi450 $r5,[$r6]
    4fb8:	4c 54 7f f0 	bne $r5,$r8,4f98 <lfs_bd_prog+0x40>
    4fbc:	a0 71       	lwi333 $r1,[$r6+#0x4]
    4fbe:	e2 e1       	slt45 $r7,$r1
    4fc0:	e9 ec       	bnezs8 4f98 <lfs_bd_prog+0x40>
    4fc2:	04 05 00 1a 	lwi $r0,[$r10+#0x68]
    4fc6:	04 00 00 0a 	lwi $r0,[$r0+#0x28]
    4fca:	88 01       	add45 $r0,$r1
    4fcc:	e2 e0       	slt45 $r7,$r0
    4fce:	e8 e5       	beqzs8 4f98 <lfs_bd_prog+0x40>
    4fd0:	8a 07       	sub45 $r0,$r7
    4fd2:	40 d6 00 06 	slt $r13,$r12,$r0
    4fd6:	a0 b3       	lwi333 $r2,[$r6+#0xc]
    4fd8:	40 06 34 1b 	cmovn $r0,$r12,$r13
    4fdc:	81 a0       	mov55 $r13,$r0
    4fde:	9a 39       	sub333 $r0,$r7,$r1
    4fe0:	88 02       	add45 $r0,$r2
    4fe2:	80 29       	mov55 $r1,$r9
    4fe4:	80 4d       	mov55 $r2,$r13
    4fe6:	49 00 27 b3 	jal 9f4c <memcpy>
    4fea:	a0 31       	lwi333 $r0,[$r6+#0x4]
    4fec:	a0 b2       	lwi333 $r2,[$r6+#0x8]
    4fee:	04 35 00 1a 	lwi $r3,[$r10+#0x68]
    4ff2:	88 ed       	add45 $r7,$r13
    4ff4:	9a 38       	sub333 $r0,$r7,$r0
    4ff6:	40 10 08 06 	slt $r1,$r0,$r2
    4ffa:	04 51 80 0a 	lwi $r5,[$r3+#0x28]
    4ffe:	40 01 04 1b 	cmovn $r0,$r2,$r1
    5002:	89 2d       	add45 $r9,$r13
    5004:	40 c6 34 01 	sub $r12,$r12,$r13
    5008:	a8 32       	swi333 $r0,[$r6+#0x8]
    500a:	d0 09       	beqs38 $r0,501c <lfs_bd_prog+0xc4>
    500c:	4e c3 ff d5 	bnez $r12,4fb6 <lfs_bd_prog+0x5e>
    5010:	44 00 00 00 	movi $r0,#0x0
    5014:	ec 04       	addi10.sp #0x4
    5016:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    501a:	dd 9e       	ret5 $lp
    501c:	80 0a       	mov55 $r0,$r10
    501e:	80 26       	mov55 $r1,$r6
    5020:	80 4e       	mov55 $r2,$r14
    5022:	80 7c       	mov55 $r3,$fp
    5024:	49 ff ff 36 	jal 4e90 <lfs_bd_flush>
    5028:	c0 f2       	beqz38 $r0,500c <lfs_bd_prog+0xb4>
    502a:	d5 f5       	j8 5014 <lfs_bd_prog+0xbc>
    502c:	44 00 36 cc 	movi $r0,#0x36cc
    5030:	44 10 00 dd 	movi $r1,#0xdd
    5034:	44 20 7c 68 	movi $r2,#0x7c68
    5038:	44 30 3a 24 	movi $r3,#0x3a24
    503c:	49 00 25 ec 	jal 9c14 <__assert_func>
    5040:	92 00       	nop16
    5042:	92 00       	nop16
    5044:	44 00 36 cc 	movi $r0,#0x36cc
    5048:	44 10 00 c0 	movi $r1,#0xc0
    504c:	44 20 7c 68 	movi $r2,#0x7c68
    5050:	44 30 3a 00 	movi $r3,#0x3a00
    5054:	49 00 25 e0 	jal 9c14 <__assert_func>
    5058:	92 00       	nop16
    505a:	92 00       	nop16
    505c:	44 00 36 cc 	movi $r0,#0x36cc
    5060:	44 10 00 bf 	movi $r1,#0xbf
    5064:	44 20 7c 68 	movi $r2,#0x7c68
    5068:	44 30 39 c4 	movi $r3,#0x39c4
    506c:	49 00 25 d4 	jal 9c14 <__assert_func>
    5070:	92 00       	nop16
    5072:	92 00       	nop16

00005074 <lfs_dir_commitprog>:
    5074:	3a 6f a4 bc 	smw.adm $r6,[$sp],$r9,#0x2    ! {$r6~$r9, $lp}
    5078:	ef f4       	addi10.sp #-12
    507a:	b6 5f       	swi450 $r2,[$sp]
    507c:	f3 81       	swi37.sp $r3,[+#0x4]
    507e:	80 c1       	mov55 $r6,$r1
    5080:	81 22       	mov55 $r9,$r2
    5082:	80 e3       	mov55 $r7,$r3
    5084:	50 10 00 10 	addi $r1,$r0,#0x10
    5088:	80 40       	mov55 $r2,$r0
    508a:	84 60       	movi55 $r3,#0x0
    508c:	b4 86       	lwi450 $r4,[$r6]
    508e:	a1 71       	lwi333 $r5,[$r6+#0x4]
    5090:	49 ff ff 64 	jal 4f58 <lfs_bd_prog>
    5094:	81 00       	mov55 $r8,$r0
    5096:	c8 0a       	bnez38 $r0,50aa <lfs_dir_commitprog+0x36>
    5098:	80 29       	mov55 $r1,$r9
    509a:	80 47       	mov55 $r2,$r7
    509c:	a0 33       	lwi333 $r0,[$r6+#0xc]
    509e:	49 00 16 15 	jal 7cc8 <lfs_crc>
    50a2:	a0 71       	lwi333 $r1,[$r6+#0x4]
    50a4:	a8 33       	swi333 $r0,[$r6+#0xc]
    50a6:	88 e1       	add45 $r7,$r1
    50a8:	a9 f1       	swi333 $r7,[$r6+#0x4]
    50aa:	80 08       	mov55 $r0,$r8
    50ac:	ec 0c       	addi10.sp #0xc
    50ae:	3a 6f a4 84 	lmw.bim $r6,[$sp],$r9,#0x2    ! {$r6~$r9, $lp}
    50b2:	dd 9e       	ret5 $lp

000050b4 <lfs_dir_commitattr>:
    50b4:	3a 6f b8 bc 	smw.adm $r6,[$sp],$r14,#0x2    ! {$r6~$r14, $lp}
    50b8:	ef f0       	addi10.sp #-16
    50ba:	40 61 58 08 	slli $r6,$r2,#0x16
    50be:	90 d6       	srai45 $r6,#0x16
    50c0:	8c c1       	addi45 $r6,#0x1
    50c2:	e6 c1       	slti45 $r6,#0x1
    50c4:	a1 09       	lwi333 $r4,[$r1+#0x4]
    50c6:	40 f7 88 00 	add $r15,$r15,$r2
    50ca:	54 67 83 ff 	andi $r6,$r15,#0x3ff
    50ce:	8c 84       	addi45 $r4,#0x4
    50d0:	a1 4d       	lwi333 $r5,[$r1+#0x14]
    50d2:	88 86       	add45 $r4,$r6
    50d4:	e2 a4       	slt45 $r5,$r4
    50d6:	81 21       	mov55 $r9,$r1
    50d8:	e9 48       	bnezs8 5168 <lfs_dir_commitattr+0xb4>
    50da:	a1 0a       	lwi333 $r4,[$r1+#0x8]
    50dc:	42 e1 7c 09 	bclr $r14,$r2,#0x1f
    50e0:	40 47 10 03 	xor $r4,$r14,$r4
    50e4:	40 42 00 14 	wsbh $r4,$r4
    50e8:	81 43       	mov55 $r10,$r3
    50ea:	80 e2       	mov55 $r7,$r2
    50ec:	40 42 40 0b 	rotri $r4,$r4,#0x10
    50f0:	b0 83       	addri36.sp $r2,#0xc
    50f2:	84 64       	movi55 $r3,#0x4
    50f4:	81 00       	mov55 $r8,$r0
    50f6:	f4 83       	swi37.sp $r4,[+#0xc]
    50f8:	49 ff ff be 	jal 5074 <lfs_dir_commitprog>
    50fc:	c8 0e       	bnez38 $r0,5118 <lfs_dir_commitattr+0x64>
    50fe:	4e 75 00 11 	bltz $r7,5120 <lfs_dir_commitattr+0x6c>
    5102:	fd 04       	movd44 $r0,$r8
    5104:	80 4a       	mov55 $r2,$r10
    5106:	80 66       	mov55 $r3,$r6
    5108:	49 ff ff b6 	jal 5074 <lfs_dir_commitprog>
    510c:	c8 06       	bnez38 $r0,5118 <lfs_dir_commitattr+0x64>
    510e:	92 00       	nop16
    5110:	14 e4 80 02 	swi $r14,[$r9+#0x8]
    5114:	84 00       	movi55 $r0,#0x0
    5116:	92 00       	nop16
    5118:	ec 10       	addi10.sp #0x10
    511a:	3a 6f b8 84 	lmw.bim $r6,[$sp],$r14,#0x2    ! {$r6~$r14, $lp}
    511e:	dd 9e       	ret5 $lp
    5120:	c6 f8       	beqz38 $r6,5110 <lfs_dir_commitattr+0x5c>
    5122:	50 d4 00 68 	addi $r13,$r8,#0x68
    5126:	84 e0       	movi55 $r7,#0x0
    5128:	50 bf 80 0b 	addi $r11,$sp,#0xb
    512c:	85 81       	movi55 $r12,#0x1
    512e:	d5 07       	j8 513c <lfs_dir_commitattr+0x88>
    5130:	49 ff ff a2 	jal 5074 <lfs_dir_commitprog>
    5134:	c8 f2       	bnez38 $r0,5118 <lfs_dir_commitattr+0x64>
    5136:	4c 73 3f ed 	beq $r7,$r6,5110 <lfs_dir_commitattr+0x5c>
    513a:	92 00       	nop16
    513c:	04 55 00 01 	lwi $r5,[$r10+#0x4]
    5140:	b4 8a       	lwi450 $r4,[$r10]
    5142:	9a f7       	sub333 $r3,$r6,$r7
    5144:	88 a7       	add45 $r5,$r7
    5146:	84 20       	movi55 $r1,#0x0
    5148:	80 48       	mov55 $r2,$r8
    514a:	b7 7f       	swi450 $r11,[$sp]
    514c:	14 cf 80 01 	swi $r12,[$sp+#0x4]
    5150:	80 0d       	mov55 $r0,$r13
    5152:	49 ff f7 a7 	jal 40a0 <lfs_bd_read.isra.13>
    5156:	80 80       	mov55 $r4,$r0
    5158:	80 29       	mov55 $r1,$r9
    515a:	80 08       	mov55 $r0,$r8
    515c:	80 4b       	mov55 $r2,$r11
    515e:	84 61       	movi55 $r3,#0x1
    5160:	8c e1       	addi45 $r7,#0x1
    5162:	c4 e7       	beqz38 $r4,5130 <lfs_dir_commitattr+0x7c>
    5164:	80 04       	mov55 $r0,$r4
    5166:	d5 d9       	j8 5118 <lfs_dir_commitattr+0x64>
    5168:	44 0f ff e4 	movi $r0,#-28
    516c:	d5 d6       	j8 5118 <lfs_dir_commitattr+0x64>
    516e:	92 00       	nop16

00005170 <lfs_dir_commit_commit>:
    5170:	fd 20       	movd44 $r4,$r0
    5172:	80 62       	mov55 $r3,$r2
    5174:	b4 00       	lwi450 $r0,[$r0]
    5176:	a0 61       	lwi333 $r1,[$r4+#0x4]
    5178:	80 45       	mov55 $r2,$r5
    517a:	d5 9d       	j8 50b4 <lfs_dir_commitattr>

0000517c <lfs_dir_commitcrc>:
    517c:	3a 6f ba bc 	smw.adm $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    5180:	ef cc       	addi10.sp #-52
    5182:	36 3f 80 06 	fsdi $fd3,[$sp+#0x18]
    5186:	36 4f 80 08 	fsdi $fd4,[$sp+#0x20]
    518a:	36 5f 80 0a 	fsdi $fd5,[$sp+#0x28]
    518e:	30 80 80 01 	flsi $fs8,[$r1+#0x4]
    5192:	81 40       	mov55 $r10,$r0
    5194:	04 00 00 1a 	lwi $r0,[$r0+#0x68]
    5198:	81 21       	mov55 $r9,$r1
    519a:	04 b0 00 06 	lwi $r11,[$r0+#0x18]
    519e:	6a 04 00 01 	fmfsr $r0,$fs8
    51a2:	30 90 80 03 	flsi $fs9,[$r1+#0xc]
    51a6:	88 0b       	add45 $r0,$r11
    51a8:	8c 07       	addi45 $r0,#0x7
    51aa:	40 10 2d 77 	divr $r1,$r11,$r0,$r11
    51ae:	40 b0 2c 01 	sub $r11,$r0,$r11
    51b2:	6a 04 00 01 	fmfsr $r0,$fs8
    51b6:	50 15 00 10 	addi $r1,$r10,#0x10
    51ba:	e2 0b       	slt45 $r0,$r11
    51bc:	4e f2 00 88 	beqz $r15,52cc <lfs_dir_commitcrc+0x150>
    51c0:	50 05 00 68 	addi $r0,$r10,#0x68
    51c4:	6a 03 80 09 	fmtsr $r0,$fs7
    51c8:	46 e0 00 ff 	sethi $r14,#0xff
    51cc:	b0 03       	addri36.sp $r0,#0xc
    51ce:	6a 64 00 01 	fmfsr $r6,$fs8
    51d2:	6a 03 00 09 	fmtsr $r0,$fs6
    51d6:	44 c0 03 fe 	movi $r12,#0x3fe
    51da:	51 c5 ff f8 	addi $fp,$r11,#-8
    51de:	50 e7 0c 00 	addi $r14,$r14,#0xc00
    51e2:	50 8f 80 10 	addi $r8,$sp,#0x10
    51e6:	50 d5 00 10 	addi $r13,$r10,#0x10
    51ea:	d5 14       	j8 5212 <lfs_dir_commitcrc+0x96>
    51ec:	f0 03       	lwi37.sp $r0,[+#0xc]
    51ee:	04 64 80 01 	lwi $r6,[$r9+#0x4]
    51f2:	54 30 03 ff 	andi $r3,$r0,#0x3ff
    51f6:	8c c4       	addi45 $r6,#0x4
    51f8:	88 c3       	add45 $r6,$r3
    51fa:	40 73 fc 08 	slli $r7,$r7,#0x1f
    51fe:	ff c5       	xor33 $r7,$r0
    5200:	84 5f       	movi55 $r2,#-1
    5202:	e2 cb       	slt45 $r6,$r11
    5204:	14 64 80 01 	swi $r6,[$r9+#0x4]
    5208:	14 74 80 02 	swi $r7,[$r9+#0x8]
    520c:	14 24 80 03 	swi $r2,[$r9+#0xc]
    5210:	e8 5e       	beqzs8 52cc <lfs_dir_commitcrc+0x150>
    5212:	9d f4       	addi333 $r7,$r6,#0x4
    5214:	40 65 9c 01 	sub $r6,$r11,$r7
    5218:	40 06 18 06 	slt $r0,$r12,$r6
    521c:	40 66 00 1b 	cmovn $r6,$r12,$r0
    5220:	88 c7       	add45 $r6,$r7
    5222:	e2 cb       	slt45 $r6,$r11
    5224:	e8 05       	beqzs8 522e <lfs_dir_commitcrc+0xb2>
    5226:	40 0e 18 06 	slt $r0,$fp,$r6
    522a:	40 6e 00 1b 	cmovn $r6,$fp,$r0
    522e:	84 04       	movi55 $r0,#0x4
    5230:	f0 81       	swi37.sp $r0,[+#0x4]
    5232:	32 6f 80 00 	fssi $fs6,[$sp+#0x0]
    5236:	6a 03 80 01 	fmfsr $r0,$fs7
    523a:	86 1f       	movi55 $r16,#-1
    523c:	84 20       	movi55 $r1,#0x0
    523e:	80 4a       	mov55 $r2,$r10
    5240:	84 64       	movi55 $r3,#0x4
    5242:	b4 89       	lwi450 $r4,[$r9]
    5244:	80 a6       	mov55 $r5,$r6
    5246:	15 0f 80 03 	swi $r16,[$sp+#0xc]
    524a:	49 ff f7 2b 	jal 40a0 <lfs_bd_read.isra.13>
    524e:	c0 03       	beqz38 $r0,5254 <lfs_dir_commitcrc+0xd8>
    5250:	5a 0f ac 34 	bnec $r0,#-84,52b8 <lfs_dir_commitcrc+0x13c>
    5254:	8a c7       	sub45 $r6,$r7
    5256:	f7 03       	lwi37.sp $r7,[+#0xc]
    5258:	04 34 80 02 	lwi $r3,[$r9+#0x8]
    525c:	40 73 80 14 	wsbh $r7,$r7
    5260:	42 73 bc 0a 	btgl $r7,$r7,#0xf
    5264:	42 73 bc 0b 	btst $r7,$r7,#0xf
    5268:	50 03 85 00 	addi $r0,$r7,#0x500
    526c:	40 00 50 08 	slli $r0,$r0,#0x14
    5270:	40 63 38 04 	or $r6,$r6,$r14
    5274:	ff 87       	or33 $r6,$r0
    5276:	fe f5       	xor33 $r3,$r6
    5278:	40 31 80 14 	wsbh $r3,$r3
    527c:	40 31 c0 0b 	rotri $r3,$r3,#0x10
    5280:	80 28       	mov55 $r1,$r8
    5282:	84 44       	movi55 $r2,#0x4
    5284:	04 04 80 03 	lwi $r0,[$r9+#0xc]
    5288:	b6 68       	swi450 $r3,[$r8]
    528a:	f6 83       	swi37.sp $r6,[+#0xc]
    528c:	49 00 15 1e 	jal 7cc8 <lfs_crc>
    5290:	14 04 80 03 	swi $r0,[$r9+#0xc]
    5294:	82 00       	mov55 $r16,$r0
    5296:	84 08       	movi55 $r0,#0x8
    5298:	f0 81       	swi37.sp $r0,[+#0x4]
    529a:	b7 1f       	swi450 $r8,[$sp]
    529c:	80 2d       	mov55 $r1,$r13
    529e:	80 0a       	mov55 $r0,$r10
    52a0:	80 4a       	mov55 $r2,$r10
    52a2:	84 60       	movi55 $r3,#0x0
    52a4:	b4 89       	lwi450 $r4,[$r9]
    52a6:	04 54 80 01 	lwi $r5,[$r9+#0x4]
    52aa:	15 04 00 01 	swi $r16,[$r8+#0x4]
    52ae:	49 ff fe 55 	jal 4f58 <lfs_bd_prog>
    52b2:	80 2d       	mov55 $r1,$r13
    52b4:	c0 9c       	beqz38 $r0,51ec <lfs_dir_commitcrc+0x70>
    52b6:	92 00       	nop16
    52b8:	ec 18       	addi10.sp #0x18
    52ba:	34 3f 90 02 	fldi.bi $fd3,[$sp],#0x8
    52be:	34 4f 90 02 	fldi.bi $fd4,[$sp],#0x8
    52c2:	34 5f 90 03 	fldi.bi $fd5,[$sp],#0xc
    52c6:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    52ca:	dd 9e       	ret5 $lp
    52cc:	84 1f       	movi55 $r0,#-1
    52ce:	b6 0a       	swi450 $r0,[$r10]
    52d0:	80 4a       	mov55 $r2,$r10
    52d2:	80 0a       	mov55 $r0,$r10
    52d4:	84 60       	movi55 $r3,#0x0
    52d6:	49 ff fd dd 	jal 4e90 <lfs_bd_flush>
    52da:	c8 ef       	bnez38 $r0,52b8 <lfs_dir_commitcrc+0x13c>
    52dc:	04 05 00 1a 	lwi $r0,[$r10+#0x68]
    52e0:	a0 44       	lwi333 $r1,[$r0+#0x10]
    52e2:	dd 21       	jral5 $r1
    52e4:	4e 06 00 66 	bgtz $r0,53b0 <lfs_dir_commitcrc+0x234>
    52e8:	c8 e8       	bnez38 $r0,52b8 <lfs_dir_commitcrc+0x13c>
    52ea:	6a 04 00 01 	fmfsr $r0,$fs8
    52ee:	04 64 80 04 	lwi $r6,[$r9+#0x10]
    52f2:	8c 04       	addi45 $r0,#0x4
    52f4:	6a 03 00 09 	fmtsr $r0,$fs6
    52f8:	e2 cb       	slt45 $r6,$r11
    52fa:	e8 54       	beqzs8 53a2 <lfs_dir_commitcrc+0x226>
    52fc:	44 00 03 fe 	movi $r0,#0x3fe
    5300:	6a 03 80 09 	fmtsr $r0,$fs7
    5304:	50 05 ff f8 	addi $r0,$r11,#-8
    5308:	6a 05 00 09 	fmtsr $r0,$fs10
    530c:	51 c5 00 68 	addi $fp,$r10,#0x68
    5310:	50 8f 80 10 	addi $r8,$sp,#0x10
    5314:	44 e0 00 01 	movi $r14,#0x1
    5318:	6a 03 00 01 	fmfsr $r0,$fs6
    531c:	50 d0 00 04 	addi $r13,$r0,#0x4
    5320:	e2 cd       	slt45 $r6,$r13
    5322:	e8 43       	beqzs8 53a8 <lfs_dir_commitcrc+0x22c>
    5324:	40 76 98 01 	sub $r7,$r13,$r6
    5328:	85 9f       	movi55 $r12,#-1
    532a:	d5 0d       	j8 5344 <lfs_dir_commitcrc+0x1c8>
    532c:	80 0c       	mov55 $r0,$r12
    532e:	80 28       	mov55 $r1,$r8
    5330:	84 41       	movi55 $r2,#0x1
    5332:	8c c1       	addi45 $r6,#0x1
    5334:	49 00 14 ca 	jal 7cc8 <lfs_crc>
    5338:	40 13 34 06 	slt $r1,$r6,$r13
    533c:	81 80       	mov55 $r12,$r0
    533e:	8e e1       	subi45 $r7,#0x1
    5340:	c1 18       	beqz38 $r1,5370 <lfs_dir_commitcrc+0x1f4>
    5342:	92 00       	nop16
    5344:	6a 04 00 01 	fmfsr $r0,$fs8
    5348:	4c 60 40 06 	bne $r6,$r0,5354 <lfs_dir_commitcrc+0x1d8>
    534c:	6a 04 80 01 	fmfsr $r0,$fs9
    5350:	4c c0 40 2c 	bne $r12,$r0,53a8 <lfs_dir_commitcrc+0x22c>
    5354:	b7 1f       	swi450 $r8,[$sp]
    5356:	14 ef 80 01 	swi $r14,[$sp+#0x4]
    535a:	80 1c       	mov55 $r0,$fp
    535c:	84 20       	movi55 $r1,#0x0
    535e:	80 4a       	mov55 $r2,$r10
    5360:	80 67       	mov55 $r3,$r7
    5362:	b4 89       	lwi450 $r4,[$r9]
    5364:	80 a6       	mov55 $r5,$r6
    5366:	49 ff f6 9d 	jal 40a0 <lfs_bd_read.isra.13>
    536a:	c0 e1       	beqz38 $r0,532c <lfs_dir_commitcrc+0x1b0>
    536c:	d5 a6       	j8 52b8 <lfs_dir_commitcrc+0x13c>
    536e:	92 00       	nop16
    5370:	c8 1c       	bnez38 $r0,53a8 <lfs_dir_commitcrc+0x22c>
    5372:	6a 03 00 01 	fmfsr $r0,$fs6
    5376:	6a 13 80 01 	fmfsr $r1,$fs7
    537a:	40 65 80 01 	sub $r6,$r11,$r0
    537e:	e2 26       	slt45 $r1,$r6
    5380:	40 60 bc 1b 	cmovn $r6,$r1,$r15
    5384:	6a 03 00 01 	fmfsr $r0,$fs6
    5388:	88 c0       	add45 $r6,$r0
    538a:	e2 cb       	slt45 $r6,$r11
    538c:	e8 0b       	beqzs8 53a2 <lfs_dir_commitcrc+0x226>
    538e:	6a 05 00 01 	fmfsr $r0,$fs10
    5392:	e2 06       	slt45 $r0,$r6
    5394:	40 60 3c 1b 	cmovn $r6,$r0,$r15
    5398:	9c 74       	addi333 $r1,$r6,#0x4
    539a:	e2 cb       	slt45 $r6,$r11
    539c:	6a 13 00 09 	fmtsr $r1,$fs6
    53a0:	e9 bc       	bnezs8 5318 <lfs_dir_commitcrc+0x19c>
    53a2:	84 00       	movi55 $r0,#0x0
    53a4:	48 ff ff 8a 	j 52b8 <lfs_dir_commitcrc+0x13c>
    53a8:	44 0f ff ac 	movi $r0,#-84
    53ac:	48 ff ff 86 	j 52b8 <lfs_dir_commitcrc+0x13c>
    53b0:	44 00 36 cc 	movi $r0,#0x36cc
    53b4:	44 10 00 b6 	movi $r1,#0xb6
    53b8:	44 20 7c 3c 	movi $r2,#0x7c3c
    53bc:	44 30 39 24 	movi $r3,#0x3924
    53c0:	49 00 24 2a 	jal 9c14 <__assert_func>
    53c4:	92 00       	nop16
    53c6:	92 00       	nop16

000053c8 <lfs_dir_find_match>:
    53c8:	3a 6f 9c bc 	smw.adm $r6,[$sp],$r7,#0x2    ! {$r6~$r7, $lp}
    53cc:	ef f4       	addi10.sp #-12
    53ce:	a1 42       	lwi333 $r5,[$r0+#0x8]
    53d0:	54 70 83 ff 	andi $r7,$r1,#0x3ff
    53d4:	e2 a7       	slt45 $r5,$r7
    53d6:	80 82       	mov55 $r4,$r2
    53d8:	80 45       	mov55 $r2,$r5
    53da:	80 c0       	mov55 $r6,$r0
    53dc:	40 23 bc 1a 	cmovz $r2,$r7,$r15
    53e0:	b4 00       	lwi450 $r0,[$r0]
    53e2:	b6 5f       	swi450 $r2,[$sp]
    53e4:	b4 64       	lwi450 $r3,[$r4]
    53e6:	80 20       	mov55 $r1,$r0
    53e8:	a1 21       	lwi333 $r4,[$r4+#0x4]
    53ea:	a1 71       	lwi333 $r5,[$r6+#0x4]
    53ec:	49 ff fd 12 	jal 4e10 <lfs_bd_cmp.constprop.35>
    53f0:	c8 08       	bnez38 $r0,5400 <lfs_dir_find_match+0x38>
    53f2:	a1 72       	lwi333 $r5,[$r6+#0x8]
    53f4:	d7 0a       	beqs38 $r7,5408 <lfs_dir_find_match+0x40>
    53f6:	e2 a7       	slt45 $r5,$r7
    53f8:	84 41       	movi55 $r2,#0x1
    53fa:	84 02       	movi55 $r0,#0x2
    53fc:	40 01 3c 1b 	cmovn $r0,$r2,$r15
    5400:	ec 0c       	addi10.sp #0xc
    5402:	3a 6f 9c 84 	lmw.bim $r6,[$sp],$r7,#0x2    ! {$r6~$r7, $lp}
    5406:	dd 9e       	ret5 $lp
    5408:	84 00       	movi55 $r0,#0x0
    540a:	ec 0c       	addi10.sp #0xc
    540c:	3a 6f 9c 84 	lmw.bim $r6,[$sp],$r7,#0x2    ! {$r6~$r7, $lp}
    5410:	dd 9e       	ret5 $lp
    5412:	92 00       	nop16

00005414 <lfs_dir_getslice>:
    5414:	3a 6f ba bc 	smw.adm $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    5418:	ef d4       	addi10.sp #-44
    541a:	36 3f 80 04 	fsdi $fd3,[$sp+#0x10]
    541e:	36 4f 80 06 	fsdi $fd4,[$sp+#0x18]
    5422:	36 5f 80 08 	fsdi $fd5,[$sp+#0x20]
    5426:	05 00 00 0f 	lwi $r16,[$r0+#0x3c]
    542a:	81 00       	mov55 $r8,$r0
    542c:	40 08 50 09 	srli $r0,$r16,#0x14
    5430:	a1 8c       	lwi333 $r6,[$r1+#0x10]
    5432:	54 00 07 00 	andi $r0,$r0,#0x700
    5436:	81 21       	mov55 $r9,$r1
    5438:	81 62       	mov55 $r11,$r2
    543a:	81 83       	mov55 $r12,$r3
    543c:	6a 44 00 09 	fmtsr $r4,$fs8
    5440:	6a 54 80 09 	fmtsr $r5,$fs9
    5444:	05 c0 80 03 	lwi $fp,[$r1+#0xc]
    5448:	f6 83       	swi37.sp $r6,[+#0xc]
    544a:	84 e0       	movi55 $r7,#0x0
    544c:	c0 10       	beqz38 $r0,546c <lfs_dir_getslice+0x58>
    544e:	04 54 00 10 	lwi $r5,[$r8+#0x40]
    5452:	b4 21       	lwi450 $r1,[$r1]
    5454:	4c 50 80 aa 	beq $r5,$r1,55a8 <lfs_dir_getslice+0x194>
    5458:	04 34 00 11 	lwi $r3,[$r8+#0x44]
    545c:	04 24 80 01 	lwi $r2,[$r9+#0x4]
    5460:	4c 31 00 a4 	beq $r3,$r2,55a8 <lfs_dir_getslice+0x194>
    5464:	4c 51 00 a2 	beq $r5,$r2,55a8 <lfs_dir_getslice+0x194>
    5468:	4c 11 80 a0 	beq $r1,$r3,55a8 <lfs_dir_getslice+0x194>
    546c:	46 07 00 00 	sethi $r0,#0x70000
    5470:	46 e0 00 ff 	sethi $r14,#0xff
    5474:	50 e7 0c 00 	addi $r14,$r14,#0xc00
    5478:	6a 05 80 09 	fmtsr $r0,$fs11
    547c:	46 04 01 00 	sethi $r0,#0x40100
    5480:	40 a5 b8 02 	and $r10,$r11,$r14
    5484:	6a 03 00 09 	fmtsr $r0,$fs6
    5488:	46 00 ff 00 	sethi $r0,#0xff00
    548c:	93 4a       	srli45 $r10,#0xa
    548e:	50 d4 00 68 	addi $r13,$r8,#0x68
    5492:	6a e5 00 09 	fmtsr $r14,$fs10
    5496:	6a 03 80 09 	fmtsr $r0,$fs7
    549a:	d5 11       	j8 54bc <lfs_dir_getslice+0xa8>
    549c:	6a 55 80 01 	fmfsr $r5,$fs11
    54a0:	44 10 04 00 	movi $r1,#0x400
    54a4:	ff 76       	and33 $r5,$r6
    54a6:	92 b4       	srli45 $r5,#0x14
    54a8:	41 16 1c 01 	sub $r17,$r12,$r7
    54ac:	4c 12 80 64 	beq $r1,$r5,5574 <lfs_dir_getslice+0x160>
    54b0:	41 18 98 03 	xor $r17,$r17,$r6
    54b4:	40 f8 ac 02 	and $r15,$r17,$r11
    54b8:	e8 3a       	beqzs8 552c <lfs_dir_getslice+0x118>
    54ba:	80 d0       	mov55 $r6,$r16
    54bc:	40 03 58 08 	slli $r0,$r6,#0x16
    54c0:	40 e0 58 0a 	srai $r14,$r0,#0x16
    54c4:	51 07 00 01 	addi $r16,$r14,#0x1
    54c8:	e7 81       	slti45 $r16,#0x1
    54ca:	40 f7 98 00 	add $r15,$r15,$r6
    54ce:	55 07 83 ff 	andi $r16,$r15,#0x3ff
    54d2:	50 08 00 08 	addi $r0,$r16,#0x8
    54d6:	40 0e 00 06 	slt $r0,$fp,$r0
    54da:	53 08 7f fc 	subri $r16,$r16,#-4
    54de:	4e 03 00 7f 	bnez $r0,55dc <lfs_dir_getslice+0x1c8>
    54e2:	b0 03       	addri36.sp $r0,#0xc
    54e4:	b6 1f       	swi450 $r0,[$sp]
    54e6:	84 04       	movi55 $r0,#0x4
    54e8:	f0 81       	swi37.sp $r0,[+#0x4]
    54ea:	41 ce 40 00 	add $fp,$fp,$r16
    54ee:	80 0d       	mov55 $r0,$r13
    54f0:	84 20       	movi55 $r1,#0x0
    54f2:	80 48       	mov55 $r2,$r8
    54f4:	84 64       	movi55 $r3,#0x4
    54f6:	b4 89       	lwi450 $r4,[$r9]
    54f8:	80 bc       	mov55 $r5,$fp
    54fa:	49 ff f5 d3 	jal 40a0 <lfs_bd_read.isra.13>
    54fe:	c8 31       	bnez38 $r0,5560 <lfs_dir_getslice+0x14c>
    5500:	05 0f 80 03 	lwi $r16,[$sp+#0xc]
    5504:	41 08 00 14 	wsbh $r16,$r16
    5508:	41 08 40 0b 	rotri $r16,$r16,#0x10
    550c:	41 08 18 03 	xor $r16,$r16,$r6
    5510:	43 08 7c 09 	bclr $r16,$r16,#0x1f
    5514:	15 0f 80 03 	swi $r16,[$sp+#0xc]
    5518:	4e a3 ff c2 	bnez $r10,549c <lfs_dir_getslice+0x88>
    551c:	41 16 1c 01 	sub $r17,$r12,$r7
    5520:	41 18 98 03 	xor $r17,$r17,$r6
    5524:	40 f8 ac 02 	and $r15,$r17,$r11
    5528:	4e f3 ff c9 	bnez $r15,54ba <lfs_dir_getslice+0xa6>
    552c:	5a e7 ff 58 	beqc $r14,#-1,55dc <lfs_dir_getslice+0x1c8>
    5530:	f0 16       	lwi37.sp $r0,[+#0x58]
    5532:	54 a3 03 ff 	andi $r10,$r6,#0x3ff
    5536:	f1 16       	lwi37.sp $r1,[+#0x58]
    5538:	e2 0a       	slt45 $r0,$r10
    553a:	6a 54 00 01 	fmfsr $r5,$fs8
    553e:	40 a0 bc 1b 	cmovn $r10,$r1,$r15
    5542:	8c a4       	addi45 $r5,#0x4
    5544:	32 9f 80 00 	fssi $fs9,[$sp+#0x0]
    5548:	14 af 80 01 	swi $r10,[$sp+#0x4]
    554c:	80 0d       	mov55 $r0,$r13
    554e:	84 20       	movi55 $r1,#0x0
    5550:	80 48       	mov55 $r2,$r8
    5552:	80 6a       	mov55 $r3,$r10
    5554:	b4 89       	lwi450 $r4,[$r9]
    5556:	88 bc       	add45 $r5,$fp
    5558:	49 ff f5 a4 	jal 40a0 <lfs_bd_read.isra.13>
    555c:	c0 42       	beqz38 $r0,55e0 <lfs_dir_getslice+0x1cc>
    555e:	92 00       	nop16
    5560:	ec 10       	addi10.sp #0x10
    5562:	34 3f 90 02 	fldi.bi $fd3,[$sp],#0x8
    5566:	34 4f 90 02 	fldi.bi $fd4,[$sp],#0x8
    556a:	34 5f 90 03 	fldi.bi $fd5,[$sp],#0xc
    556e:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    5572:	dd 9e       	ret5 $lp
    5574:	6a 05 00 01 	fmfsr $r0,$fs10
    5578:	40 13 00 02 	and $r1,$r6,$r0
    557c:	40 58 80 02 	and $r5,$r17,$r0
    5580:	92 2a       	srli45 $r1,#0xa
    5582:	40 02 a8 09 	srli $r0,$r5,#0xa
    5586:	96 49       	zeh33 $r1,$r1
    5588:	96 01       	zeh33 $r0,$r0
    558a:	e2 01       	slt45 $r0,$r1
    558c:	e9 92       	bnezs8 54b0 <lfs_dir_getslice+0x9c>
    558e:	6a 03 00 01 	fmfsr $r0,$fs6
    5592:	ff 47       	or33 $r5,$r0
    5594:	d6 24       	beqs38 $r6,55dc <lfs_dir_getslice+0x1c8>
    5596:	6a 03 80 01 	fmfsr $r0,$fs7
    559a:	fe 36       	and33 $r0,$r6
    559c:	94 04       	slli333 $r0,$r0,#0x4
    559e:	90 0e       	srai45 $r0,#0xe
    55a0:	88 e0       	add45 $r7,$r0
    55a2:	41 16 1c 01 	sub $r17,$r12,$r7
    55a6:	d5 bd       	j8 5520 <lfs_dir_getslice+0x10c>
    55a8:	46 00 00 ff 	sethi $r0,#0xff
    55ac:	50 00 0c 00 	addi $r0,$r0,#0xc00
    55b0:	40 15 80 02 	and $r1,$r11,$r0
    55b4:	84 e0       	movi55 $r7,#0x0
    55b6:	4e 12 ff 5b 	beqz $r1,546c <lfs_dir_getslice+0x58>
    55ba:	41 08 00 02 	and $r16,$r16,$r0
    55be:	40 06 00 02 	and $r0,$r12,$r0
    55c2:	93 8a       	srli45 $r16,#0xa
    55c4:	92 0a       	srli45 $r0,#0xa
    55c6:	41 08 00 13 	zeh $r16,$r16
    55ca:	96 01       	zeh33 $r0,$r0
    55cc:	e2 10       	slt45 $r0,$r16
    55ce:	44 1f fc 00 	movi $r1,#-1024
    55d2:	84 e0       	movi55 $r7,#0x0
    55d4:	40 70 bc 1a 	cmovz $r7,$r1,$r15
    55d8:	48 ff ff 4a 	j 546c <lfs_dir_getslice+0x58>
    55dc:	84 1e       	movi55 $r0,#-2
    55de:	d5 c1       	j8 5560 <lfs_dir_getslice+0x14c>
    55e0:	f2 16       	lwi37.sp $r2,[+#0x58]
    55e2:	6a 04 80 01 	fmfsr $r0,$fs9
    55e6:	84 20       	movi55 $r1,#0x0
    55e8:	88 0a       	add45 $r0,$r10
    55ea:	8a 4a       	sub45 $r2,$r10
    55ec:	49 00 24 e4 	jal 9fb4 <memset>
    55f0:	98 37       	add333 $r0,$r6,$r7
    55f2:	d5 b7       	j8 5560 <lfs_dir_getslice+0x14c>

000055f4 <lfs_dir_getgstate>:
    55f4:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    55f8:	ef e8       	addi10.sp #-24
    55fa:	84 6c       	movi55 $r3,#0xc
    55fc:	80 c2       	mov55 $r6,$r2
    55fe:	46 27 ff 00 	sethi $r2,#0x7ff00
    5602:	b6 7f       	swi450 $r3,[$sp]
    5604:	84 80       	movi55 $r4,#0x0
    5606:	50 31 00 0c 	addi $r3,$r2,#0xc
    560a:	b1 43       	addri36.sp $r5,#0xc
    560c:	49 ff ff 04 	jal 5414 <lfs_dir_getslice>
    5610:	4e 05 00 13 	bltz $r0,5636 <lfs_dir_getgstate+0x42>
    5614:	b4 26       	lwi450 $r1,[$r6]
    5616:	f2 03       	lwi37.sp $r2,[+#0xc]
    5618:	a0 31       	lwi333 $r0,[$r6+#0x4]
    561a:	fe 8d       	xor33 $r2,$r1
    561c:	f1 04       	lwi37.sp $r1,[+#0x10]
    561e:	a0 f2       	lwi333 $r3,[$r6+#0x8]
    5620:	fe 45       	xor33 $r1,$r0
    5622:	f0 05       	lwi37.sp $r0,[+#0x14]
    5624:	b6 46       	swi450 $r2,[$r6]
    5626:	fe 1d       	xor33 $r0,$r3
    5628:	a8 32       	swi333 $r0,[$r6+#0x8]
    562a:	a8 71       	swi333 $r1,[$r6+#0x4]
    562c:	84 00       	movi55 $r0,#0x0
    562e:	ec 18       	addi10.sp #0x18
    5630:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    5634:	dd 9e       	ret5 $lp
    5636:	84 3e       	movi55 $r1,#-2
    5638:	fe 45       	xor33 $r1,$r0
    563a:	84 40       	movi55 $r2,#0x0
    563c:	40 01 04 1a 	cmovz $r0,$r2,$r1
    5640:	ec 18       	addi10.sp #0x18
    5642:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    5646:	dd 9e       	ret5 $lp

00005648 <lfs_dir_find>:
    5648:	3a 6f ba bc 	smw.adm $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    564c:	ef cc       	addi10.sp #-52
    564e:	36 3f 80 06 	fsdi $fd3,[$sp+#0x18]
    5652:	36 4f 80 08 	fsdi $fd4,[$sp+#0x20]
    5656:	36 5f 80 0a 	fsdi $fd5,[$sp+#0x28]
    565a:	6a 24 80 09 	fmtsr $r2,$fs9
    565e:	81 c3       	mov55 $r14,$r3
    5660:	81 a0       	mov55 $r13,$r0
    5662:	81 81       	mov55 $r12,$r1
    5664:	30 61 00 00 	flsi $fs6,[$r2+#0x0]
    5668:	c3 04       	beqz38 $r3,5670 <lfs_dir_find+0x28>
    566a:	44 00 03 ff 	movi $r0,#0x3ff
    566e:	ac 18       	shi333 $r0,[$r3+#0x0]
    5670:	46 90 02 ff 	sethi $r9,#0x2ff
    5674:	04 06 80 09 	lwi $r0,[$r13+#0x24]
    5678:	50 94 8c 00 	addi $r9,$r9,#0xc00
    567c:	04 16 80 08 	lwi $r1,[$r13+#0x20]
    5680:	14 06 00 07 	swi $r0,[$r12+#0x1c]
    5684:	42 04 d4 09 	bclr $r0,$r9,#0x15
    5688:	6a 05 00 09 	fmtsr $r0,$fs10
    568c:	46 02 00 00 	sethi $r0,#0x20000
    5690:	8c 08       	addi45 $r0,#0x8
    5692:	6a 04 00 09 	fmtsr $r0,$fs8
    5696:	46 07 00 ff 	sethi $r0,#0x700ff
    569a:	50 00 0c 00 	addi $r0,$r0,#0xc00
    569e:	6a 03 80 09 	fmtsr $r0,$fs7
    56a2:	14 16 00 06 	swi $r1,[$r12+#0x18]
    56a6:	92 00       	nop16
    56a8:	6a 03 00 01 	fmfsr $r0,$fs6
    56ac:	44 10 3a 48 	movi $r1,#0x3a48
    56b0:	6a a3 00 01 	fmfsr $r10,$fs6
    56b4:	49 00 25 d0 	jal a254 <strspn>
    56b8:	89 40       	add45 $r10,$r0
    56ba:	80 0a       	mov55 $r0,$r10
    56bc:	44 10 3a 48 	movi $r1,#0x3a48
    56c0:	49 00 25 b8 	jal a230 <strcspn>
    56c4:	81 60       	mov55 $r11,$r0
    56c6:	5a 08 01 05 	bnec $r0,#0x1,56d0 <lfs_dir_find+0x88>
    56ca:	48 00 00 8b 	j 57e0 <lfs_dir_find+0x198>
    56ce:	92 00       	nop16
    56d0:	5a 08 02 04 	bnec $r0,#0x2,56d8 <lfs_dir_find+0x90>
    56d4:	48 00 00 94 	j 57fc <lfs_dir_find+0x1b4>
    56d8:	40 05 2c 00 	add $r0,$r10,$r11
    56dc:	6a 03 00 09 	fmtsr $r0,$fs6
    56e0:	80 c0       	mov55 $r6,$r0
    56e2:	85 01       	movi55 $r8,#0x1
    56e4:	80 06       	mov55 $r0,$r6
    56e6:	44 10 3a 48 	movi $r1,#0x3a48
    56ea:	49 00 25 b5 	jal a254 <strspn>
    56ee:	88 c0       	add45 $r6,$r0
    56f0:	44 10 3a 48 	movi $r1,#0x3a48
    56f4:	80 06       	mov55 $r0,$r6
    56f6:	49 00 25 9d 	jal a230 <strcspn>
    56fa:	80 e0       	mov55 $r7,$r0
    56fc:	c0 14       	beqz38 $r0,5724 <lfs_dir_find+0xdc>
    56fe:	5a 00 02 05 	beqc $r0,#0x2,5708 <lfs_dir_find+0xc0>
    5702:	8d 01       	addi45 $r8,#0x1
    5704:	88 c7       	add45 $r6,$r7
    5706:	d5 ef       	j8 56e4 <lfs_dir_find+0x9c>
    5708:	80 06       	mov55 $r0,$r6
    570a:	44 10 3a 50 	movi $r1,#0x3a50
    570e:	84 42       	movi55 $r2,#0x2
    5710:	49 00 24 00 	jal 9f10 <memcmp>
    5714:	c8 f7       	bnez38 $r0,5702 <lfs_dir_find+0xba>
    5716:	8f 01       	subi45 $r8,#0x1
    5718:	4e 83 ff f6 	bnez $r8,5704 <lfs_dir_find+0xbc>
    571c:	9c 32       	addi333 $r0,$r6,#0x2
    571e:	6a 03 00 09 	fmtsr $r0,$fs6
    5722:	d5 c3       	j8 56a8 <lfs_dir_find+0x60>
    5724:	20 05 00 00 	lbsi $r0,[$r10+#0x0]
    5728:	c0 4e       	beqz38 $r0,57c4 <lfs_dir_find+0x17c>
    572a:	40 04 84 08 	slli $r0,$r9,#0x1
    572e:	6a 14 80 01 	fmfsr $r1,$fs9
    5732:	92 15       	srli45 $r0,#0x15
    5734:	b7 41       	swi450 $r10,[$r1]
    5736:	5a 00 02 05 	beqc $r0,#0x2,5740 <lfs_dir_find+0xf8>
    573a:	48 00 00 6f 	j 5818 <lfs_dir_find+0x1d0>
    573e:	92 00       	nop16
    5740:	6a 05 00 01 	fmfsr $r0,$fs10
    5744:	50 76 00 18 	addi $r7,$r12,#0x18
    5748:	40 94 80 02 	and $r9,$r9,$r0
    574c:	93 2a       	srli45 $r9,#0xa
    574e:	5a 93 ff 15 	beqc $r9,#0x3ff,5778 <lfs_dir_find+0x130>
    5752:	6a 44 00 01 	fmfsr $r4,$fs8
    5756:	84 08       	movi55 $r0,#0x8
    5758:	40 34 a8 08 	slli $r3,$r9,#0xa
    575c:	50 76 00 18 	addi $r7,$r12,#0x18
    5760:	6a 23 80 01 	fmfsr $r2,$fs7
    5764:	b6 1f       	swi450 $r0,[$sp]
    5766:	fe e7       	or33 $r3,$r4
    5768:	80 0d       	mov55 $r0,$r13
    576a:	80 2c       	mov55 $r1,$r12
    576c:	84 80       	movi55 $r4,#0x0
    576e:	80 a7       	mov55 $r5,$r7
    5770:	49 ff fe 52 	jal 5414 <lfs_dir_getslice>
    5774:	4e 05 00 2a 	bltz $r0,57c8 <lfs_dir_find+0x180>
    5778:	b1 83       	addri36.sp $r6,#0xc
    577a:	45 c0 53 c8 	movi $fp,#0x53c8
    577e:	85 00       	movi55 $r8,#0x0
    5780:	d5 07       	j8 578e <lfs_dir_find+0x146>
    5782:	92 00       	nop16
    5784:	4e 03 ff 92 	bnez $r0,56a8 <lfs_dir_find+0x60>
    5788:	00 16 00 17 	lbi $r1,[$r12+#0x17]
    578c:	c1 28       	beqz38 $r1,57dc <lfs_dir_find+0x194>
    578e:	fa 3f       	movpi45 $r1,#0x2f
    5790:	80 0a       	mov55 $r0,$r10
    5792:	49 00 25 2f 	jal a1f0 <strchr>
    5796:	80 a8       	mov55 $r5,$r8
    5798:	15 cf 80 00 	swi $fp,[$sp+#0x0]
    579c:	f6 81       	swi37.sp $r6,[+#0x4]
    579e:	40 57 00 1a 	cmovz $r5,$r14,$r0
    57a2:	80 2c       	mov55 $r1,$r12
    57a4:	80 0d       	mov55 $r0,$r13
    57a6:	80 47       	mov55 $r2,$r7
    57a8:	46 37 80 00 	sethi $r3,#0x78000
    57ac:	80 8b       	mov55 $r4,$r11
    57ae:	14 d3 00 00 	swi $r13,[$r6+#0x0]
    57b2:	14 a3 00 01 	swi $r10,[$r6+#0x4]
    57b6:	14 b3 00 02 	swi $r11,[$r6+#0x8]
    57ba:	49 ff f5 67 	jal 4288 <lfs_dir_fetchmatch>
    57be:	81 20       	mov55 $r9,$r0
    57c0:	4e 04 ff e2 	bgez $r0,5784 <lfs_dir_find+0x13c>
    57c4:	80 09       	mov55 $r0,$r9
    57c6:	92 00       	nop16
    57c8:	ec 18       	addi10.sp #0x18
    57ca:	34 3f 90 02 	fldi.bi $fd3,[$sp],#0x8
    57ce:	34 4f 90 02 	fldi.bi $fd4,[$sp],#0x8
    57d2:	34 5f 90 03 	fldi.bi $fd5,[$sp],#0xc
    57d6:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    57da:	dd 9e       	ret5 $lp
    57dc:	84 1e       	movi55 $r0,#-2
    57de:	d5 f5       	j8 57c8 <lfs_dir_find+0x180>
    57e0:	80 0a       	mov55 $r0,$r10
    57e2:	44 10 3a 4c 	movi $r1,#0x3a4c
    57e6:	84 41       	movi55 $r2,#0x1
    57e8:	49 00 23 94 	jal 9f10 <memcmp>
    57ec:	4e 03 ff 76 	bnez $r0,56d8 <lfs_dir_find+0x90>
    57f0:	40 05 2c 00 	add $r0,$r10,$r11
    57f4:	6a 03 00 09 	fmtsr $r0,$fs6
    57f8:	48 ff ff 58 	j 56a8 <lfs_dir_find+0x60>
    57fc:	80 0a       	mov55 $r0,$r10
    57fe:	44 10 3a 50 	movi $r1,#0x3a50
    5802:	84 42       	movi55 $r2,#0x2
    5804:	49 00 23 86 	jal 9f10 <memcmp>
    5808:	4e 03 ff 68 	bnez $r0,56d8 <lfs_dir_find+0x90>
    580c:	40 05 2c 00 	add $r0,$r10,$r11
    5810:	6a 03 00 09 	fmtsr $r0,$fs6
    5814:	48 ff ff 4a 	j 56a8 <lfs_dir_find+0x60>
    5818:	44 0f ff ec 	movi $r0,#-20
    581c:	d5 d6       	j8 57c8 <lfs_dir_find+0x180>
    581e:	92 00       	nop16

00005820 <lfs_dir_getinfo>:
    5820:	3a 6f a8 bc 	smw.adm $r6,[$sp],$r10,#0x2    ! {$r6~$r10, $lp}
    5824:	ef f0       	addi10.sp #-16
    5826:	81 03       	mov55 $r8,$r3
    5828:	5a 23 ff 48 	beqc $r2,#0x3ff,58b8 <lfs_dir_getinfo+0x98>
    582c:	04 40 00 1b 	lwi $r4,[$r0+#0x6c]
    5830:	40 61 28 08 	slli $r6,$r2,#0xa
    5834:	8c 81       	addi45 $r4,#0x1
    5836:	40 33 10 04 	or $r3,$r6,$r4
    583a:	54 21 83 ff 	andi $r2,$r3,#0x3ff
    583e:	b6 5f       	swi450 $r2,[$sp]
    5840:	46 27 80 ff 	sethi $r2,#0x780ff
    5844:	50 21 0c 00 	addi $r2,$r2,#0xc00
    5848:	84 80       	movi55 $r4,#0x0
    584a:	50 54 00 08 	addi $r5,$r8,#0x8
    584e:	81 20       	mov55 $r9,$r0
    5850:	50 a0 80 00 	addi $r10,$r1,#0x0
    5854:	49 ff fd e0 	jal 5414 <lfs_dir_getslice>
    5858:	4e 05 00 24 	bltz $r0,58a0 <lfs_dir_getinfo+0x80>
    585c:	46 77 ff 00 	sethi $r7,#0x7ff00
    5860:	40 40 1c 02 	and $r4,$r0,$r7
    5864:	46 32 00 00 	sethi $r3,#0x20000
    5868:	92 94       	srli45 $r4,#0x14
    586a:	84 08       	movi55 $r0,#0x8
    586c:	46 27 00 ff 	sethi $r2,#0x700ff
    5870:	8c 68       	addi45 $r3,#0x8
    5872:	10 44 00 00 	sbi $r4,[$r8+#0x0]
    5876:	80 2a       	mov55 $r1,$r10
    5878:	b6 1f       	swi450 $r0,[$sp]
    587a:	50 21 0c 00 	addi $r2,$r2,#0xc00
    587e:	80 09       	mov55 $r0,$r9
    5880:	fe f7       	or33 $r3,$r6
    5882:	84 80       	movi55 $r4,#0x0
    5884:	b1 42       	addri36.sp $r5,#0x8
    5886:	49 ff fd c7 	jal 5414 <lfs_dir_getslice>
    588a:	80 20       	mov55 $r1,$r0
    588c:	4e 05 00 0a 	bltz $r0,58a0 <lfs_dir_getinfo+0x80>
    5890:	ff c6       	and33 $r7,$r0
    5892:	92 f4       	srli45 $r7,#0x14
    5894:	5a 72 02 20 	beqc $r7,#0x202,58d4 <lfs_dir_getinfo+0xb4>
    5898:	84 00       	movi55 $r0,#0x0
    589a:	5a 72 01 07 	beqc $r7,#0x201,58a8 <lfs_dir_getinfo+0x88>
    589e:	92 00       	nop16
    58a0:	ec 10       	addi10.sp #0x10
    58a2:	3a 6f a8 84 	lmw.bim $r6,[$sp],$r10,#0x2    ! {$r6~$r10, $lp}
    58a6:	dd 9e       	ret5 $lp
    58a8:	54 10 83 ff 	andi $r1,$r1,#0x3ff
    58ac:	14 14 00 01 	swi $r1,[$r8+#0x4]
    58b0:	ec 10       	addi10.sp #0x10
    58b2:	3a 6f a8 84 	lmw.bim $r6,[$sp],$r10,#0x2    ! {$r6~$r10, $lp}
    58b6:	dd 9e       	ret5 $lp
    58b8:	50 01 80 08 	addi $r0,$r3,#0x8
    58bc:	44 10 3a 48 	movi $r1,#0x3a48
    58c0:	49 00 24 ae 	jal a21c <strcpy>
    58c4:	84 02       	movi55 $r0,#0x2
    58c6:	10 04 00 00 	sbi $r0,[$r8+#0x0]
    58ca:	84 00       	movi55 $r0,#0x0
    58cc:	ec 10       	addi10.sp #0x10
    58ce:	3a 6f a8 84 	lmw.bim $r6,[$sp],$r10,#0x2    ! {$r6~$r10, $lp}
    58d2:	dd 9e       	ret5 $lp
    58d4:	f0 03       	lwi37.sp $r0,[+#0xc]
    58d6:	14 04 00 01 	swi $r0,[$r8+#0x4]
    58da:	84 00       	movi55 $r0,#0x0
    58dc:	d5 e2       	j8 58a0 <lfs_dir_getinfo+0x80>
    58de:	92 00       	nop16

000058e0 <lfs_dir_getread.constprop.33>:
    58e0:	3a 6f ba bc 	smw.adm $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    58e4:	ef f4       	addi10.sp #-12
    58e6:	81 40       	mov55 $r10,$r0
    58e8:	04 00 00 1a 	lwi $r0,[$r0+#0x68]
    58ec:	04 8f 80 0f 	lwi $r8,[$sp+#0x3c]
    58f0:	a0 07       	lwi333 $r0,[$r0+#0x1c]
    58f2:	80 e5       	mov55 $r7,$r5
    58f4:	88 a8       	add45 $r5,$r8
    58f6:	e2 05       	slt45 $r0,$r5
    58f8:	e9 54       	bnezs8 59a0 <lfs_dir_getread.constprop.33+0xc0>
    58fa:	4e 82 00 4e 	beqz $r8,5996 <lfs_dir_getread.constprop.33+0xb6>
    58fe:	46 bf ff 7f 	sethi $r11,#0xfff7f
    5902:	81 81       	mov55 $r12,$r1
    5904:	80 c2       	mov55 $r6,$r2
    5906:	81 c3       	mov55 $r14,$r3
    5908:	81 a4       	mov55 $r13,$r4
    590a:	87 9e       	movi55 $fp,#-2
    590c:	50 b5 8c 00 	addi $r11,$r11,#0xc00
    5910:	d5 20       	j8 5950 <lfs_dir_getread.constprop.33+0x70>
    5912:	92 00       	nop16
    5914:	04 55 00 1a 	lwi $r5,[$r10+#0x68]
    5918:	15 c3 00 00 	swi $fp,[$r6+#0x0]
    591c:	05 12 80 05 	lwi $r17,[$r5+#0x14]
    5920:	05 22 80 0a 	lwi $r18,[$r5+#0x28]
    5924:	51 08 ff ff 	addi $r16,$r17,#-1
    5928:	89 8e       	add45 $r16,$r14
    592a:	89 87       	add45 $r16,$r7
    592c:	40 58 44 97 	divr $r5,$r4,$r16,$r17
    5930:	41 13 c4 b7 	divr $r17,$r5,$r7,$r17
    5934:	8b 84       	sub45 $r16,$r4
    5936:	e3 d0       	slt45 $r18,$r16
    5938:	9b 3d       	sub333 $r4,$r7,$r5
    593a:	41 09 3c 1b 	cmovn $r16,$r18,$r15
    593e:	a9 31       	swi333 $r4,[$r6+#0x4]
    5940:	15 03 00 02 	swi $r16,[$r6+#0x8]
    5944:	b7 9f       	swi450 $r16,[$sp]
    5946:	a1 73       	lwi333 $r5,[$r6+#0xc]
    5948:	49 ff fd 66 	jal 5414 <lfs_dir_getslice>
    594c:	4e 05 00 26 	bltz $r0,5998 <lfs_dir_getread.constprop.33+0xb8>
    5950:	b4 86       	lwi450 $r4,[$r6]
    5952:	80 0a       	mov55 $r0,$r10
    5954:	80 2c       	mov55 $r1,$r12
    5956:	80 4b       	mov55 $r2,$r11
    5958:	80 6d       	mov55 $r3,$r13
    595a:	5a 4f fe dd 	bnec $r4,#-2,5914 <lfs_dir_getread.constprop.33+0x34>
    595e:	a1 31       	lwi333 $r4,[$r6+#0x4]
    5960:	a1 72       	lwi333 $r5,[$r6+#0x8]
    5962:	e2 e4       	slt45 $r7,$r4
    5964:	88 a4       	add45 $r5,$r4
    5966:	41 03 94 06 	slt $r16,$r7,$r5
    596a:	4f 02 ff d5 	beqz $r16,5914 <lfs_dir_getread.constprop.33+0x34>
    596e:	e9 d3       	bnezs8 5914 <lfs_dir_getread.constprop.33+0x34>
    5970:	8a a7       	sub45 $r5,$r7
    5972:	e3 05       	slt45 $r8,$r5
    5974:	a0 b3       	lwi333 $r2,[$r6+#0xc]
    5976:	40 54 3c 1b 	cmovn $r5,$r8,$r15
    597a:	9a 7c       	sub333 $r1,$r7,$r4
    597c:	88 22       	add45 $r1,$r2
    597e:	f0 0e       	lwi37.sp $r0,[+#0x38]
    5980:	80 45       	mov55 $r2,$r5
    5982:	81 25       	mov55 $r9,$r5
    5984:	8b 05       	sub45 $r8,$r5
    5986:	49 00 22 e3 	jal 9f4c <memcpy>
    598a:	f0 0e       	lwi37.sp $r0,[+#0x38]
    598c:	88 e9       	add45 $r7,$r9
    598e:	88 09       	add45 $r0,$r9
    5990:	f0 8e       	swi37.sp $r0,[+#0x38]
    5992:	4e 83 ff df 	bnez $r8,5950 <lfs_dir_getread.constprop.33+0x70>
    5996:	84 00       	movi55 $r0,#0x0
    5998:	ec 0c       	addi10.sp #0xc
    599a:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    599e:	dd 9e       	ret5 $lp
    59a0:	44 0f ff ac 	movi $r0,#-84
    59a4:	d5 fa       	j8 5998 <lfs_dir_getread.constprop.33+0xb8>
    59a6:	92 00       	nop16

000059a8 <lfs_stat>:
    59a8:	3a 6f 9c bc 	smw.adm $r6,[$sp],$r7,#0x2    ! {$r6~$r7, $lp}
    59ac:	ef d4       	addi10.sp #-44
    59ae:	84 60       	movi55 $r3,#0x0
    59b0:	f1 81       	swi37.sp $r1,[+#0x4]
    59b2:	80 c2       	mov55 $r6,$r2
    59b4:	b0 42       	addri36.sp $r1,#0x8
    59b6:	b0 81       	addri36.sp $r2,#0x4
    59b8:	50 70 00 00 	addi $r7,$r0,#0x0
    59bc:	49 ff fe 46 	jal 5648 <lfs_dir_find>
    59c0:	4e 05 00 0a 	bltz $r0,59d4 <lfs_stat+0x2c>
    59c4:	40 20 30 08 	slli $r2,$r0,#0xc
    59c8:	b0 42       	addri36.sp $r1,#0x8
    59ca:	80 07       	mov55 $r0,$r7
    59cc:	92 56       	srli45 $r2,#0x16
    59ce:	80 66       	mov55 $r3,$r6
    59d0:	49 ff ff 28 	jal 5820 <lfs_dir_getinfo>
    59d4:	ec 2c       	addi10.sp #0x2c
    59d6:	3a 6f 9c 84 	lmw.bim $r6,[$sp],$r7,#0x2    ! {$r6~$r7, $lp}
    59da:	dd 9e       	ret5 $lp

000059dc <lfs_mount>:
    59dc:	3a 6f ac bc 	smw.adm $r6,[$sp],$r11,#0x2    ! {$r6~$r11, $lp}
    59e0:	ef 9c       	addi10.sp #-100
    59e2:	80 e0       	mov55 $r7,$r0
    59e4:	49 ff f1 f6 	jal 3dd0 <lfs_init>
    59e8:	4e 03 00 c0 	bnez $r0,5b68 <lfs_mount+0x18c>
    59ec:	b0 10       	addri36.sp $r0,#0x40
    59ee:	84 20       	movi55 $r1,#0x0
    59f0:	44 20 00 20 	movi $r2,#0x20
    59f4:	49 00 22 e0 	jal 9fb4 <memset>
    59f8:	46 97 ff ff 	sethi $r9,#0x7ffff
    59fc:	84 01       	movi55 $r0,#0x1
    59fe:	46 a0 ff 00 	sethi $r10,#0xff00
    5a02:	46 b2 01 00 	sethi $r11,#0x20100
    5a06:	f0 97       	swi37.sp $r0,[+#0x5c]
    5a08:	85 00       	movi55 $r8,#0x0
    5a0a:	50 94 8c 00 	addi $r9,$r9,#0xc00
    5a0e:	8d 48       	addi45 $r10,#0x8
    5a10:	8d 78       	addi45 $r11,#0x18
    5a12:	f0 17       	lwi37.sp $r0,[+#0x5c]
    5a14:	5a 07 ff 6c 	beqc $r0,#-1,5aec <lfs_mount+0x110>
    5a18:	04 03 80 1a 	lwi $r0,[$r7+#0x68]
    5a1c:	04 00 00 08 	lwi $r0,[$r0+#0x20]
    5a20:	92 01       	srli45 $r0,#0x1
    5a22:	e3 00       	slt45 $r8,$r0
    5a24:	4e f2 00 ba 	beqz $r15,5b98 <lfs_mount+0x1bc>
    5a28:	51 0f 80 1c 	addi $r16,$sp,#0x1c
    5a2c:	44 00 53 c8 	movi $r0,#0x53c8
    5a30:	45 10 3a 70 	movi $r17,#0x3a70
    5a34:	b6 1f       	swi450 $r0,[$sp]
    5a36:	15 1f 80 08 	swi $r17,[$sp+#0x20]
    5a3a:	15 0f 80 01 	swi $r16,[$sp+#0x4]
    5a3e:	86 28       	movi55 $r17,#0x8
    5a40:	80 07       	mov55 $r0,$r7
    5a42:	b0 50       	addri36.sp $r1,#0x40
    5a44:	b0 96       	addri36.sp $r2,#0x58
    5a46:	80 69       	mov55 $r3,$r9
    5a48:	80 8a       	mov55 $r4,$r10
    5a4a:	84 a0       	movi55 $r5,#0x0
    5a4c:	f7 87       	swi37.sp $r7,[+#0x1c]
    5a4e:	15 1f 80 09 	swi $r17,[$sp+#0x24]
    5a52:	49 ff f4 1b 	jal 4288 <lfs_dir_fetchmatch>
    5a56:	80 c0       	mov55 $r6,$r0
    5a58:	8d 01       	addi45 $r8,#0x1
    5a5a:	4e 05 00 83 	bltz $r0,5b60 <lfs_mount+0x184>
    5a5e:	c0 3b       	beqz38 $r0,5ad4 <lfs_mount+0xf8>
    5a60:	40 60 58 08 	slli $r6,$r0,#0x16
    5a64:	90 d6       	srai45 $r6,#0x16
    5a66:	5a 67 ff 37 	beqc $r6,#-1,5ad4 <lfs_mount+0xf8>
    5a6a:	f0 11       	lwi37.sp $r0,[+#0x44]
    5a6c:	f1 10       	lwi37.sp $r1,[+#0x40]
    5a6e:	14 03 80 09 	swi $r0,[$r7+#0x24]
    5a72:	fa 08       	movpi45 $r0,#0x18
    5a74:	14 13 80 08 	swi $r1,[$r7+#0x20]
    5a78:	80 49       	mov55 $r2,$r9
    5a7a:	b6 1f       	swi450 $r0,[$sp]
    5a7c:	b0 50       	addri36.sp $r1,#0x40
    5a7e:	80 07       	mov55 $r0,$r7
    5a80:	80 6b       	mov55 $r3,$r11
    5a82:	84 80       	movi55 $r4,#0x0
    5a84:	b1 4a       	addri36.sp $r5,#0x28
    5a86:	49 ff fc c7 	jal 5414 <lfs_dir_getslice>
    5a8a:	80 c0       	mov55 $r6,$r0
    5a8c:	4e 05 00 6a 	bltz $r0,5b60 <lfs_mount+0x184>
    5a90:	f0 0a       	lwi37.sp $r0,[+#0x28]
    5a92:	40 10 40 09 	srli $r1,$r0,#0x10
    5a96:	96 81       	zeh33 $r2,$r0
    5a98:	5a 18 02 6c 	bnec $r1,#0x2,5b70 <lfs_mount+0x194>
    5a9c:	ca 6a       	bnez38 $r2,5b70 <lfs_mount+0x194>
    5a9e:	f0 0d       	lwi37.sp $r0,[+#0x34]
    5aa0:	c0 08       	beqz38 $r0,5ab0 <lfs_mount+0xd4>
    5aa2:	04 13 80 1b 	lwi $r1,[$r7+#0x6c]
    5aa6:	e2 20       	slt45 $r1,$r0
    5aa8:	4e f3 00 7c 	bnez $r15,5ba0 <lfs_mount+0x1c4>
    5aac:	14 03 80 1b 	swi $r0,[$r7+#0x6c]
    5ab0:	f0 0e       	lwi37.sp $r0,[+#0x38]
    5ab2:	c0 08       	beqz38 $r0,5ac2 <lfs_mount+0xe6>
    5ab4:	04 13 80 1c 	lwi $r1,[$r7+#0x70]
    5ab8:	e2 20       	slt45 $r1,$r0
    5aba:	4e f3 00 9b 	bnez $r15,5bf0 <lfs_mount+0x214>
    5abe:	14 03 80 1c 	swi $r0,[$r7+#0x70]
    5ac2:	f0 0f       	lwi37.sp $r0,[+#0x3c]
    5ac4:	c0 08       	beqz38 $r0,5ad4 <lfs_mount+0xf8>
    5ac6:	04 13 80 1d 	lwi $r1,[$r7+#0x74]
    5aca:	e2 20       	slt45 $r1,$r0
    5acc:	4e f3 00 7e 	bnez $r15,5bc8 <lfs_mount+0x1ec>
    5ad0:	14 03 80 1d 	swi $r0,[$r7+#0x74]
    5ad4:	80 07       	mov55 $r0,$r7
    5ad6:	b0 50       	addri36.sp $r1,#0x40
    5ad8:	50 23 80 30 	addi $r2,$r7,#0x30
    5adc:	49 ff fd 8c 	jal 55f4 <lfs_dir_getgstate>
    5ae0:	80 c0       	mov55 $r6,$r0
    5ae2:	c8 3f       	bnez38 $r0,5b60 <lfs_mount+0x184>
    5ae4:	f0 16       	lwi37.sp $r0,[+#0x58]
    5ae6:	5a 0f ff 96 	bnec $r0,#-1,5a12 <lfs_mount+0x36>
    5aea:	92 00       	nop16
    5aec:	04 03 80 08 	lwi $r0,[$r7+#0x20]
    5af0:	5a 07 ff 36 	beqc $r0,#-1,5b5c <lfs_mount+0x180>
    5af4:	04 03 80 09 	lwi $r0,[$r7+#0x24]
    5af8:	5a 07 ff 32 	beqc $r0,#-1,5b5c <lfs_mount+0x180>
    5afc:	04 03 80 0c 	lwi $r0,[$r7+#0x30]
    5b00:	4e 03 00 8c 	bnez $r0,5c18 <lfs_mount+0x23c>
    5b04:	04 03 80 0d 	lwi $r0,[$r7+#0x34]
    5b08:	4e 03 00 88 	bnez $r0,5c18 <lfs_mount+0x23c>
    5b0c:	04 03 80 0e 	lwi $r0,[$r7+#0x38]
    5b10:	4e 03 00 84 	bnez $r0,5c18 <lfs_mount+0x23c>
    5b14:	04 13 80 0c 	lwi $r1,[$r7+#0x30]
    5b18:	04 43 80 1a 	lwi $r4,[$r7+#0x68]
    5b1c:	40 20 fc 09 	srli $r2,$r1,#0x1f
    5b20:	a0 27       	lwi333 $r0,[$r4+#0x1c]
    5b22:	88 22       	add45 $r1,$r2
    5b24:	04 23 80 0b 	lwi $r2,[$r7+#0x2c]
    5b28:	14 13 80 0c 	swi $r1,[$r7+#0x30]
    5b2c:	50 13 80 30 	addi $r1,$r7,#0x30
    5b30:	3b 00 c8 00 	lmw.bi $r16,[$r1],$r18,#0x0    ! {$r16~$r18}
    5b34:	40 21 00 b7 	divr $r2,$r5,$r2,$r0
    5b38:	84 60       	movi55 $r3,#0x0
    5b3a:	04 22 00 08 	lwi $r2,[$r4+#0x20]
    5b3e:	50 13 80 3c 	addi $r1,$r7,#0x3c
    5b42:	3b 00 c8 20 	smw.bi $r16,[$r1],$r18,#0x0    ! {$r16~$r18}
    5b46:	84 00       	movi55 $r0,#0x0
    5b48:	14 53 80 15 	swi $r5,[$r7+#0x54]
    5b4c:	14 33 80 16 	swi $r3,[$r7+#0x58]
    5b50:	14 33 80 17 	swi $r3,[$r7+#0x5c]
    5b54:	14 23 80 18 	swi $r2,[$r7+#0x60]
    5b58:	d5 08       	j8 5b68 <lfs_mount+0x18c>
    5b5a:	92 00       	nop16
    5b5c:	44 6f ff ea 	movi $r6,#-22
    5b60:	80 07       	mov55 $r0,$r7
    5b62:	49 ff ed 8b 	jal 3678 <lfs_deinit>
    5b66:	80 06       	mov55 $r0,$r6
    5b68:	ec 64       	addi10.sp #0x64
    5b6a:	3a 6f ac 84 	lmw.bim $r6,[$sp],$r11,#0x2    ! {$r6~$r11, $lp}
    5b6e:	dd 9e       	ret5 $lp
    5b70:	96 01       	zeh33 $r0,$r0
    5b72:	44 20 36 cc 	movi $r2,#0x36cc
    5b76:	b6 5f       	swi450 $r2,[$sp]
    5b78:	f0 83       	swi37.sp $r0,[+#0xc]
    5b7a:	44 20 0e 99 	movi $r2,#0xe99
    5b7e:	44 00 01 38 	movi $r0,#0x138
    5b82:	f0 84       	swi37.sp $r0,[+#0x10]
    5b84:	f2 81       	swi37.sp $r2,[+#0x4]
    5b86:	f1 82       	swi37.sp $r1,[+#0x8]
    5b88:	44 00 3a 7c 	movi $r0,#0x3a7c
    5b8c:	49 ff e4 56 	jal 2438 <printf>
    5b90:	44 6f ff ea 	movi $r6,#-22
    5b94:	d5 e6       	j8 5b60 <lfs_mount+0x184>
    5b96:	92 00       	nop16
    5b98:	44 6f ff ac 	movi $r6,#-84
    5b9c:	d5 e2       	j8 5b60 <lfs_mount+0x184>
    5b9e:	92 00       	nop16
    5ba0:	44 20 36 cc 	movi $r2,#0x36cc
    5ba4:	b6 5f       	swi450 $r2,[$sp]
    5ba6:	f0 82       	swi37.sp $r0,[+#0x8]
    5ba8:	44 20 0e a2 	movi $r2,#0xea2
    5bac:	44 00 01 38 	movi $r0,#0x138
    5bb0:	f0 84       	swi37.sp $r0,[+#0x10]
    5bb2:	f2 81       	swi37.sp $r2,[+#0x4]
    5bb4:	14 1f 80 03 	swi $r1,[$sp+#0xc]
    5bb8:	44 00 3a a4 	movi $r0,#0x3aa4
    5bbc:	49 ff e4 3e 	jal 2438 <printf>
    5bc0:	44 6f ff ea 	movi $r6,#-22
    5bc4:	d5 ce       	j8 5b60 <lfs_mount+0x184>
    5bc6:	92 00       	nop16
    5bc8:	44 20 36 cc 	movi $r2,#0x36cc
    5bcc:	b6 5f       	swi450 $r2,[$sp]
    5bce:	f0 82       	swi37.sp $r0,[+#0x8]
    5bd0:	44 20 0e b8 	movi $r2,#0xeb8
    5bd4:	44 00 01 38 	movi $r0,#0x138
    5bd8:	f0 84       	swi37.sp $r0,[+#0x10]
    5bda:	f2 81       	swi37.sp $r2,[+#0x4]
    5bdc:	14 1f 80 03 	swi $r1,[$sp+#0xc]
    5be0:	44 00 3b 0c 	movi $r0,#0x3b0c
    5be4:	49 ff e4 2a 	jal 2438 <printf>
    5be8:	44 6f ff ea 	movi $r6,#-22
    5bec:	d5 ba       	j8 5b60 <lfs_mount+0x184>
    5bee:	92 00       	nop16
    5bf0:	44 20 36 cc 	movi $r2,#0x36cc
    5bf4:	b6 5f       	swi450 $r2,[$sp]
    5bf6:	f0 82       	swi37.sp $r0,[+#0x8]
    5bf8:	44 20 0e ad 	movi $r2,#0xead
    5bfc:	44 00 01 38 	movi $r0,#0x138
    5c00:	f0 84       	swi37.sp $r0,[+#0x10]
    5c02:	f2 81       	swi37.sp $r2,[+#0x4]
    5c04:	14 1f 80 03 	swi $r1,[$sp+#0xc]
    5c08:	44 00 3a d8 	movi $r0,#0x3ad8
    5c0c:	49 ff e4 16 	jal 2438 <printf>
    5c10:	44 6f ff ea 	movi $r6,#-22
    5c14:	48 ff ff a6 	j 5b60 <lfs_mount+0x184>
    5c18:	04 03 80 0e 	lwi $r0,[$r7+#0x38]
    5c1c:	44 30 36 cc 	movi $r3,#0x36cc
    5c20:	04 23 80 0c 	lwi $r2,[$r7+#0x30]
    5c24:	04 13 80 0d 	lwi $r1,[$r7+#0x34]
    5c28:	b6 7f       	swi450 $r3,[$sp]
    5c2a:	f0 84       	swi37.sp $r0,[+#0x10]
    5c2c:	44 30 0e d3 	movi $r3,#0xed3
    5c30:	44 00 01 38 	movi $r0,#0x138
    5c34:	f0 85       	swi37.sp $r0,[+#0x14]
    5c36:	f3 81       	swi37.sp $r3,[+#0x4]
    5c38:	f2 82       	swi37.sp $r2,[+#0x8]
    5c3a:	f1 83       	swi37.sp $r1,[+#0xc]
    5c3c:	44 00 3b 40 	movi $r0,#0x3b40
    5c40:	49 ff e3 fc 	jal 2438 <printf>
    5c44:	48 ff ff 68 	j 5b14 <lfs_mount+0x138>

00005c48 <lfs_fs_traverseraw>:
    5c48:	3a 6f ba bc 	smw.adm $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    5c4c:	ef cc       	addi10.sp #-52
    5c4e:	80 e0       	mov55 $r7,$r0
    5c50:	81 81       	mov55 $r12,$r1
    5c52:	81 a2       	mov55 $r13,$r2
    5c54:	84 20       	movi55 $r1,#0x0
    5c56:	b0 04       	addri36.sp $r0,#0x10
    5c58:	fa 50       	movpi45 $r2,#0x20
    5c5a:	81 c3       	mov55 $r14,$r3
    5c5c:	46 92 00 00 	sethi $r9,#0x20000
    5c60:	49 00 21 aa 	jal 9fb4 <memset>
    5c64:	46 87 00 ff 	sethi $r8,#0x700ff
    5c68:	84 01       	movi55 $r0,#0x1
    5c6a:	f0 8b       	swi37.sp $r0,[+#0x2c]
    5c6c:	84 20       	movi55 $r1,#0x0
    5c6e:	87 80       	movi55 $fp,#0x0
    5c70:	8d 28       	addi45 $r9,#0x8
    5c72:	50 84 0c 00 	addi $r8,$r8,#0xc00
    5c76:	46 b7 ff 00 	sethi $r11,#0x7ff00
    5c7a:	f0 0b       	lwi37.sp $r0,[+#0x2c]
    5c7c:	5a 07 ff 44 	beqc $r0,#-1,5d04 <lfs_fs_traverseraw+0xbc>
    5c80:	04 03 80 1a 	lwi $r0,[$r7+#0x68]
    5c84:	04 00 00 08 	lwi $r0,[$r0+#0x20]
    5c88:	92 01       	srli45 $r0,#0x1
    5c8a:	40 0e 00 06 	slt $r0,$fp,$r0
    5c8e:	4e 02 00 95 	beqz $r0,5db8 <lfs_fs_traverseraw+0x170>
    5c92:	80 0d       	mov55 $r0,$r13
    5c94:	dd 2c       	jral5 $r12
    5c96:	c8 4b       	bnez38 $r0,5d2c <lfs_fs_traverseraw+0xe4>
    5c98:	80 0d       	mov55 $r0,$r13
    5c9a:	f1 0b       	lwi37.sp $r1,[+#0x2c]
    5c9c:	dd 2c       	jral5 $r12
    5c9e:	c8 47       	bnez38 $r0,5d2c <lfs_fs_traverseraw+0xe4>
    5ca0:	b6 1f       	swi450 $r0,[$sp]
    5ca2:	f0 81       	swi37.sp $r0,[+#0x4]
    5ca4:	b0 44       	addri36.sp $r1,#0x10
    5ca6:	80 07       	mov55 $r0,$r7
    5ca8:	b0 8a       	addri36.sp $r2,#0x28
    5caa:	84 7f       	movi55 $r3,#-1
    5cac:	84 9f       	movi55 $r4,#-1
    5cae:	84 a0       	movi55 $r5,#0x0
    5cb0:	49 ff f2 ec 	jal 4288 <lfs_dir_fetchmatch>
    5cb4:	c8 3c       	bnez38 $r0,5d2c <lfs_fs_traverseraw+0xe4>
    5cb6:	02 0f 80 12 	lhi $r0,[$sp+#0x24]
    5cba:	84 c0       	movi55 $r6,#0x0
    5cbc:	85 48       	movi55 $r10,#0x8
    5cbe:	c0 1e       	beqz38 $r0,5cfa <lfs_fs_traverseraw+0xb2>
    5cc0:	40 43 28 08 	slli $r4,$r6,#0xa
    5cc4:	40 32 24 04 	or $r3,$r4,$r9
    5cc8:	b7 5f       	swi450 $r10,[$sp]
    5cca:	80 07       	mov55 $r0,$r7
    5ccc:	b0 44       	addri36.sp $r1,#0x10
    5cce:	80 48       	mov55 $r2,$r8
    5cd0:	84 80       	movi55 $r4,#0x0
    5cd2:	b1 42       	addri36.sp $r5,#0x8
    5cd4:	49 ff fb a0 	jal 5414 <lfs_dir_getslice>
    5cd8:	4e 05 00 28 	bltz $r0,5d28 <lfs_fs_traverseraw+0xe0>
    5cdc:	40 40 2c 02 	and $r4,$r0,$r11
    5ce0:	92 94       	srli45 $r4,#0x14
    5ce2:	5a 42 02 29 	beqc $r4,#0x202,5d34 <lfs_fs_traverseraw+0xec>
    5ce6:	4e e2 00 04 	beqz $r14,5cee <lfs_fs_traverseraw+0xa6>
    5cea:	5a 42 00 32 	beqc $r4,#0x200,5d4e <lfs_fs_traverseraw+0x106>
    5cee:	8c c1       	addi45 $r6,#0x1
    5cf0:	02 4f 80 12 	lhi $r4,[$sp+#0x24]
    5cf4:	97 b1       	zeh33 $r6,$r6
    5cf6:	e2 c4       	slt45 $r6,$r4
    5cf8:	e9 e4       	bnezs8 5cc0 <lfs_fs_traverseraw+0x78>
    5cfa:	f1 0a       	lwi37.sp $r1,[+#0x28]
    5cfc:	51 ce 00 01 	addi $fp,$fp,#0x1
    5d00:	5a 1f ff bd 	bnec $r1,#-1,5c7a <lfs_fs_traverseraw+0x32>
    5d04:	04 63 80 0a 	lwi $r6,[$r7+#0x28]
    5d08:	c6 0e       	beqz38 $r6,5d24 <lfs_fs_traverseraw+0xdc>
    5d0a:	46 b0 01 10 	sethi $r11,#0x110
    5d0e:	44 a1 00 00 	movi $r10,#0x10000
    5d12:	46 90 01 20 	sethi $r9,#0x120
    5d16:	44 82 00 00 	movi $r8,#0x20000
    5d1a:	a6 36       	lbi333 $r0,[$r6+#0x6]
    5d1c:	5a 00 01 22 	beqc $r0,#0x1,5d60 <lfs_fs_traverseraw+0x118>
    5d20:	b4 c6       	lwi450 $r6,[$r6]
    5d22:	ce fc       	bnez38 $r6,5d1a <lfs_fs_traverseraw+0xd2>
    5d24:	84 00       	movi55 $r0,#0x0
    5d26:	d5 03       	j8 5d2c <lfs_fs_traverseraw+0xe4>
    5d28:	5a 07 fe e3 	beqc $r0,#-2,5cee <lfs_fs_traverseraw+0xa6>
    5d2c:	ec 34       	addi10.sp #0x34
    5d2e:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    5d32:	dd 9e       	ret5 $lp
    5d34:	f4 03       	lwi37.sp $r4,[+#0xc]
    5d36:	f3 02       	lwi37.sp $r3,[+#0x8]
    5d38:	c4 db       	beqz38 $r4,5cee <lfs_fs_traverseraw+0xa6>
    5d3a:	14 df 80 00 	swi $r13,[$sp+#0x0]
    5d3e:	80 07       	mov55 $r0,$r7
    5d40:	84 20       	movi55 $r1,#0x0
    5d42:	80 47       	mov55 $r2,$r7
    5d44:	80 ac       	mov55 $r5,$r12
    5d46:	49 ff f7 cf 	jal 4ce4 <lfs_ctz_traverse.part.24>
    5d4a:	c0 d2       	beqz38 $r0,5cee <lfs_fs_traverseraw+0xa6>
    5d4c:	d5 f0       	j8 5d2c <lfs_fs_traverseraw+0xe4>
    5d4e:	80 0d       	mov55 $r0,$r13
    5d50:	f1 02       	lwi37.sp $r1,[+#0x8]
    5d52:	dd 2c       	jral5 $r12
    5d54:	c8 ec       	bnez38 $r0,5d2c <lfs_fs_traverseraw+0xe4>
    5d56:	80 0d       	mov55 $r0,$r13
    5d58:	f1 03       	lwi37.sp $r1,[+#0xc]
    5d5a:	dd 2c       	jral5 $r12
    5d5c:	c0 c9       	beqz38 $r0,5cee <lfs_fs_traverseraw+0xa6>
    5d5e:	d5 e7       	j8 5d2c <lfs_fs_traverseraw+0xe4>
    5d60:	04 03 00 0c 	lwi $r0,[$r6+#0x30]
    5d64:	40 10 2c 02 	and $r1,$r0,$r11
    5d68:	4c 15 00 16 	beq $r1,$r10,5d94 <lfs_fs_traverseraw+0x14c>
    5d6c:	40 00 24 02 	and $r0,$r0,$r9
    5d70:	4c 04 7f d8 	bne $r0,$r8,5d20 <lfs_fs_traverseraw+0xd8>
    5d74:	04 43 00 0d 	lwi $r4,[$r6+#0x34]
    5d78:	04 33 00 0e 	lwi $r3,[$r6+#0x38]
    5d7c:	c4 d2       	beqz38 $r4,5d20 <lfs_fs_traverseraw+0xd8>
    5d7e:	50 13 00 40 	addi $r1,$r6,#0x40
    5d82:	14 df 80 00 	swi $r13,[$sp+#0x0]
    5d86:	80 07       	mov55 $r0,$r7
    5d88:	80 47       	mov55 $r2,$r7
    5d8a:	80 ac       	mov55 $r5,$r12
    5d8c:	49 ff f7 ac 	jal 4ce4 <lfs_ctz_traverse.part.24>
    5d90:	c0 c8       	beqz38 $r0,5d20 <lfs_fs_traverseraw+0xd8>
    5d92:	d5 cd       	j8 5d2c <lfs_fs_traverseraw+0xe4>
    5d94:	04 43 00 0b 	lwi $r4,[$r6+#0x2c]
    5d98:	04 33 00 0a 	lwi $r3,[$r6+#0x28]
    5d9c:	c4 e8       	beqz38 $r4,5d6c <lfs_fs_traverseraw+0x124>
    5d9e:	50 13 00 40 	addi $r1,$r6,#0x40
    5da2:	80 ac       	mov55 $r5,$r12
    5da4:	80 47       	mov55 $r2,$r7
    5da6:	14 df 80 00 	swi $r13,[$sp+#0x0]
    5daa:	80 07       	mov55 $r0,$r7
    5dac:	49 ff f7 9c 	jal 4ce4 <lfs_ctz_traverse.part.24>
    5db0:	c8 be       	bnez38 $r0,5d2c <lfs_fs_traverseraw+0xe4>
    5db2:	04 03 00 0c 	lwi $r0,[$r6+#0x30]
    5db6:	d5 db       	j8 5d6c <lfs_fs_traverseraw+0x124>
    5db8:	44 0f ff ac 	movi $r0,#-84
    5dbc:	d5 b8       	j8 5d2c <lfs_fs_traverseraw+0xe4>
    5dbe:	92 00       	nop16

00005dc0 <lfs_alloc>:
    5dc0:	3a 6f a4 bc 	smw.adm $r6,[$sp],$r9,#0x2    ! {$r6~$r9, $lp}
    5dc4:	ef ec       	addi10.sp #-20
    5dc6:	84 e1       	movi55 $r7,#0x1
    5dc8:	80 c0       	mov55 $r6,$r0
    5dca:	81 01       	mov55 $r8,$r1
    5dcc:	85 20       	movi55 $r9,#0x0
    5dce:	92 00       	nop16
    5dd0:	04 33 00 17 	lwi $r3,[$r6+#0x5c]
    5dd4:	05 13 00 16 	lwi $r17,[$r6+#0x58]
    5dd8:	04 43 00 18 	lwi $r4,[$r6+#0x60]
    5ddc:	d5 0e       	j8 5df8 <lfs_alloc+0x38>
    5dde:	8e 81       	subi45 $r4,#0x1
    5de0:	04 53 00 19 	lwi $r5,[$r6+#0x64]
    5de4:	14 23 00 17 	swi $r2,[$r6+#0x5c]
    5de8:	14 43 00 18 	swi $r4,[$r6+#0x60]
    5dec:	38 02 82 02 	lw $r0,[$r5+($r0<<#0x2)]
    5df0:	40 08 00 02 	and $r0,$r16,$r0
    5df4:	c0 42       	beqz38 $r0,5e78 <lfs_alloc+0xb8>
    5df6:	80 62       	mov55 $r3,$r2
    5df8:	9c 99       	addi333 $r2,$r3,#0x1
    5dfa:	40 01 94 09 	srli $r0,$r3,#0x5
    5dfe:	41 03 8c 0c 	sll $r16,$r7,$r3
    5e02:	4c 38 ff ee 	bne $r3,$r17,5dde <lfs_alloc+0x1e>
    5e06:	c4 6d       	beqz38 $r4,5ee0 <lfs_alloc+0x120>
    5e08:	04 53 00 1a 	lwi $r5,[$r6+#0x68]
    5e0c:	04 03 00 15 	lwi $r0,[$r6+#0x54]
    5e10:	04 22 80 0b 	lwi $r2,[$r5+#0x2c]
    5e14:	04 52 80 08 	lwi $r5,[$r5+#0x20]
    5e18:	41 11 0c 08 	slli $r17,$r2,#0x3
    5e1c:	e3 a4       	slt45 $r17,$r4
    5e1e:	88 60       	add45 $r3,$r0
    5e20:	40 01 94 77 	divr $r0,$r3,$r3,$r5
    5e24:	40 48 bc 1b 	cmovn $r4,$r17,$r15
    5e28:	44 10 00 00 	movi $r1,#0x0
    5e2c:	14 33 00 15 	swi $r3,[$r6+#0x54]
    5e30:	14 43 00 16 	swi $r4,[$r6+#0x58]
    5e34:	14 93 00 17 	swi $r9,[$r6+#0x5c]
    5e38:	04 03 00 19 	lwi $r0,[$r6+#0x64]
    5e3c:	49 00 20 bc 	jal 9fb4 <memset>
    5e40:	44 10 35 90 	movi $r1,#0x3590
    5e44:	80 06       	mov55 $r0,$r6
    5e46:	80 46       	mov55 $r2,$r6
    5e48:	84 61       	movi55 $r3,#0x1
    5e4a:	49 ff fe ff 	jal 5c48 <lfs_fs_traverseraw>
    5e4e:	84 20       	movi55 $r1,#0x0
    5e50:	c0 c0       	beqz38 $r0,5dd0 <lfs_alloc+0x10>
    5e52:	04 43 00 1a 	lwi $r4,[$r6+#0x68]
    5e56:	04 33 00 0b 	lwi $r3,[$r6+#0x2c]
    5e5a:	a0 a7       	lwi333 $r2,[$r4+#0x1c]
    5e5c:	04 42 00 08 	lwi $r4,[$r4+#0x20]
    5e60:	40 31 88 57 	divr $r3,$r2,$r3,$r2
    5e64:	14 23 00 15 	swi $r2,[$r6+#0x54]
    5e68:	14 13 00 16 	swi $r1,[$r6+#0x58]
    5e6c:	14 13 00 17 	swi $r1,[$r6+#0x5c]
    5e70:	14 43 00 18 	swi $r4,[$r6+#0x60]
    5e74:	d5 32       	j8 5ed8 <lfs_alloc+0x118>
    5e76:	92 00       	nop16
    5e78:	04 13 00 1a 	lwi $r1,[$r6+#0x68]
    5e7c:	04 03 00 15 	lwi $r0,[$r6+#0x54]
    5e80:	04 20 80 08 	lwi $r2,[$r1+#0x20]
    5e84:	88 60       	add45 $r3,$r0
    5e86:	40 01 88 77 	divr $r0,$r3,$r3,$r2
    5e8a:	b6 68       	swi450 $r3,[$r8]
    5e8c:	04 03 00 17 	lwi $r0,[$r6+#0x5c]
    5e90:	04 43 00 16 	lwi $r4,[$r6+#0x58]
    5e94:	4c 02 00 20 	beq $r0,$r4,5ed4 <lfs_alloc+0x114>
    5e98:	40 10 14 09 	srli $r1,$r0,#0x5
    5e9c:	38 22 86 02 	lw $r2,[$r5+($r1<<#0x2)]
    5ea0:	84 21       	movi55 $r1,#0x1
    5ea2:	40 10 80 0c 	sll $r1,$r1,$r0
    5ea6:	fe 56       	and33 $r1,$r2
    5ea8:	c1 16       	beqz38 $r1,5ed4 <lfs_alloc+0x114>
    5eaa:	04 23 00 18 	lwi $r2,[$r6+#0x60]
    5eae:	86 01       	movi55 $r16,#0x1
    5eb0:	8e 41       	subi45 $r2,#0x1
    5eb2:	d5 06       	j8 5ebe <lfs_alloc+0xfe>
    5eb4:	38 12 86 02 	lw $r1,[$r5+($r1<<#0x2)]
    5eb8:	8e 41       	subi45 $r2,#0x1
    5eba:	fe 5e       	and33 $r1,$r3
    5ebc:	c1 0c       	beqz38 $r1,5ed4 <lfs_alloc+0x114>
    5ebe:	8c 01       	addi45 $r0,#0x1
    5ec0:	40 10 14 09 	srli $r1,$r0,#0x5
    5ec4:	40 38 00 0c 	sll $r3,$r16,$r0
    5ec8:	14 23 00 18 	swi $r2,[$r6+#0x60]
    5ecc:	14 03 00 17 	swi $r0,[$r6+#0x5c]
    5ed0:	4c 02 7f f2 	bne $r0,$r4,5eb4 <lfs_alloc+0xf4>
    5ed4:	44 00 00 00 	movi $r0,#0x0
    5ed8:	ec 14       	addi10.sp #0x14
    5eda:	3a 6f a4 84 	lmw.bim $r6,[$sp],$r9,#0x2    ! {$r6~$r9, $lp}
    5ede:	dd 9e       	ret5 $lp
    5ee0:	04 03 00 15 	lwi $r0,[$r6+#0x54]
    5ee4:	88 60       	add45 $r3,$r0
    5ee6:	44 00 36 cc 	movi $r0,#0x36cc
    5eea:	b6 1f       	swi450 $r0,[$sp]
    5eec:	44 00 01 ef 	movi $r0,#0x1ef
    5ef0:	f0 81       	swi37.sp $r0,[+#0x4]
    5ef2:	44 00 01 38 	movi $r0,#0x138
    5ef6:	f0 83       	swi37.sp $r0,[+#0xc]
    5ef8:	14 3f 80 02 	swi $r3,[$sp+#0x8]
    5efc:	44 00 3b 78 	movi $r0,#0x3b78
    5f00:	49 ff e2 9c 	jal 2438 <printf>
    5f04:	44 0f ff e4 	movi $r0,#-28
    5f08:	d5 e8       	j8 5ed8 <lfs_alloc+0x118>
    5f0a:	92 00       	nop16

00005f0c <lfs_dir_alloc>:
    5f0c:	3a 6f 9c bc 	smw.adm $r6,[$sp],$r7,#0x2    ! {$r6~$r7, $lp}
    5f10:	ef f4       	addi10.sp #-12
    5f12:	80 c1       	mov55 $r6,$r1
    5f14:	8c 24       	addi45 $r1,#0x4
    5f16:	80 e0       	mov55 $r7,$r0
    5f18:	49 ff ff 54 	jal 5dc0 <lfs_alloc>
    5f1c:	c8 28       	bnez38 $r0,5f6c <lfs_dir_alloc+0x60>
    5f1e:	80 07       	mov55 $r0,$r7
    5f20:	80 26       	mov55 $r1,$r6
    5f22:	49 ff ff 4f 	jal 5dc0 <lfs_alloc>
    5f26:	c8 23       	bnez38 $r0,5f6c <lfs_dir_alloc+0x60>
    5f28:	a8 32       	swi333 $r0,[$r6+#0x8]
    5f2a:	50 13 00 08 	addi $r1,$r6,#0x8
    5f2e:	84 04       	movi55 $r0,#0x4
    5f30:	b6 3f       	swi450 $r1,[$sp]
    5f32:	f0 81       	swi37.sp $r0,[+#0x4]
    5f34:	84 20       	movi55 $r1,#0x0
    5f36:	50 03 80 68 	addi $r0,$r7,#0x68
    5f3a:	80 47       	mov55 $r2,$r7
    5f3c:	84 64       	movi55 $r3,#0x4
    5f3e:	b4 86       	lwi450 $r4,[$r6]
    5f40:	84 a0       	movi55 $r5,#0x0
    5f42:	49 ff f0 af 	jal 40a0 <lfs_bd_read.isra.13>
    5f46:	a0 72       	lwi333 $r1,[$r6+#0x8]
    5f48:	c8 16       	bnez38 $r0,5f74 <lfs_dir_alloc+0x68>
    5f4a:	96 cc       	xlsb33 $r3,$r1
    5f4c:	88 23       	add45 $r1,$r3
    5f4e:	84 00       	movi55 $r0,#0x0
    5f50:	84 5f       	movi55 $r2,#-1
    5f52:	a8 72       	swi333 $r1,[$r6+#0x8]
    5f54:	84 24       	movi55 $r1,#0x4
    5f56:	12 03 00 0a 	shi $r0,[$r6+#0x14]
    5f5a:	10 03 00 16 	sbi $r0,[$r6+#0x16]
    5f5e:	10 03 00 17 	sbi $r0,[$r6+#0x17]
    5f62:	a8 73       	swi333 $r1,[$r6+#0xc]
    5f64:	a8 b4       	swi333 $r2,[$r6+#0x10]
    5f66:	a8 b6       	swi333 $r2,[$r6+#0x18]
    5f68:	a8 b7       	swi333 $r2,[$r6+#0x1c]
    5f6a:	84 00       	movi55 $r0,#0x0
    5f6c:	ec 0c       	addi10.sp #0xc
    5f6e:	3a 6f 9c 84 	lmw.bim $r6,[$sp],$r7,#0x2    ! {$r6~$r7, $lp}
    5f72:	dd 9e       	ret5 $lp
    5f74:	5a 07 ac eb 	beqc $r0,#-84,5f4a <lfs_dir_alloc+0x3e>
    5f78:	ec 0c       	addi10.sp #0xc
    5f7a:	3a 6f 9c 84 	lmw.bim $r6,[$sp],$r7,#0x2    ! {$r6~$r7, $lp}
    5f7e:	dd 9e       	ret5 $lp

00005f80 <lfs_file_relocate>:
    5f80:	3a 6f ba bc 	smw.adm $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    5f84:	ef dc       	addi10.sp #-36
    5f86:	36 3f 80 06 	fsdi $fd3,[$sp+#0x18]
    5f8a:	81 01       	mov55 $r8,$r1
    5f8c:	04 10 80 0c 	lwi $r1,[$r1+#0x30]
    5f90:	42 10 d4 0b 	btst $r1,$r1,#0x15
    5f94:	4e 12 00 a4 	beqz $r1,60dc <lfs_file_relocate+0x15c>
    5f98:	80 e0       	mov55 $r7,$r0
    5f9a:	50 00 00 68 	addi $r0,$r0,#0x68
    5f9e:	6a 03 00 09 	fmtsr $r0,$fs6
    5fa2:	50 c4 00 40 	addi $r12,$r8,#0x40
    5fa6:	50 af 80 13 	addi $r10,$sp,#0x13
    5faa:	46 b0 01 00 	sethi $r11,#0x100
    5fae:	51 c4 00 08 	addi $fp,$r8,#0x8
    5fb2:	46 e2 01 00 	sethi $r14,#0x20100
    5fb6:	80 07       	mov55 $r0,$r7
    5fb8:	b0 45       	addri36.sp $r1,#0x14
    5fba:	49 ff ff 03 	jal 5dc0 <lfs_alloc>
    5fbe:	c8 45       	bnez38 $r0,6048 <lfs_file_relocate+0xc8>
    5fc0:	04 03 80 1a 	lwi $r0,[$r7+#0x68]
    5fc4:	f1 05       	lwi37.sp $r1,[+#0x14]
    5fc6:	49 ff f6 45 	jal 4c50 <lfs_bd_erase.isra.16>
    5fca:	c8 45       	bnez38 $r0,6054 <lfs_file_relocate+0xd4>
    5fcc:	04 34 00 0f 	lwi $r3,[$r8+#0x3c]
    5fd0:	c3 58       	beqz38 $r3,6080 <lfs_file_relocate+0x100>
    5fd2:	84 c0       	movi55 $r6,#0x0
    5fd4:	85 21       	movi55 $r9,#0x1
    5fd6:	50 d3 80 10 	addi $r13,$r7,#0x10
    5fda:	d5 23       	j8 6020 <lfs_file_relocate+0xa0>
    5fdc:	02 44 00 02 	lhi $r4,[$r8+#0x4]
    5fe0:	80 07       	mov55 $r0,$r7
    5fe2:	40 42 28 08 	slli $r4,$r4,#0xa
    5fe6:	b7 5f       	swi450 $r10,[$sp]
    5fe8:	14 9f 80 01 	swi $r9,[$sp+#0x4]
    5fec:	80 3c       	mov55 $r1,$fp
    5fee:	80 4c       	mov55 $r2,$r12
    5ff0:	8a 66       	sub45 $r3,$r6
    5ff2:	40 42 38 04 	or $r4,$r4,$r14
    5ff6:	80 a6       	mov55 $r5,$r6
    5ff8:	49 ff fc 74 	jal 58e0 <lfs_dir_getread.constprop.33>
    5ffc:	c8 26       	bnez38 $r0,6048 <lfs_file_relocate+0xc8>
    5ffe:	b7 5f       	swi450 $r10,[$sp]
    6000:	14 9f 80 01 	swi $r9,[$sp+#0x4]
    6004:	80 07       	mov55 $r0,$r7
    6006:	80 2d       	mov55 $r1,$r13
    6008:	80 47       	mov55 $r2,$r7
    600a:	84 61       	movi55 $r3,#0x1
    600c:	f4 05       	lwi37.sp $r4,[+#0x14]
    600e:	80 a6       	mov55 $r5,$r6
    6010:	49 ff f7 a4 	jal 4f58 <lfs_bd_prog>
    6014:	c8 20       	bnez38 $r0,6054 <lfs_file_relocate+0xd4>
    6016:	04 34 00 0f 	lwi $r3,[$r8+#0x3c]
    601a:	8c c1       	addi45 $r6,#0x1
    601c:	e2 c3       	slt45 $r6,$r3
    601e:	e8 31       	beqzs8 6080 <lfs_file_relocate+0x100>
    6020:	04 44 00 0c 	lwi $r4,[$r8+#0x30]
    6024:	40 42 2c 02 	and $r4,$r4,$r11
    6028:	cc da       	bnez38 $r4,5fdc <lfs_file_relocate+0x5c>
    602a:	b7 5f       	swi450 $r10,[$sp]
    602c:	14 9f 80 01 	swi $r9,[$sp+#0x4]
    6030:	6a 03 00 01 	fmfsr $r0,$fs6
    6034:	80 2c       	mov55 $r1,$r12
    6036:	80 47       	mov55 $r2,$r7
    6038:	8a 66       	sub45 $r3,$r6
    603a:	04 44 00 0e 	lwi $r4,[$r8+#0x38]
    603e:	80 a6       	mov55 $r5,$r6
    6040:	49 ff f0 30 	jal 40a0 <lfs_bd_read.isra.13>
    6044:	c0 dd       	beqz38 $r0,5ffe <lfs_file_relocate+0x7e>
    6046:	92 00       	nop16
    6048:	ec 18       	addi10.sp #0x18
    604a:	34 3f 90 03 	fldi.bi $fd3,[$sp],#0xc
    604e:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    6052:	dd 9e       	ret5 $lp
    6054:	5a 0f ac fa 	bnec $r0,#-84,6048 <lfs_file_relocate+0xc8>
    6058:	44 00 36 cc 	movi $r0,#0x36cc
    605c:	b6 1f       	swi450 $r0,[$sp]
    605e:	44 00 0a 4b 	movi $r0,#0xa4b
    6062:	f0 81       	swi37.sp $r0,[+#0x4]
    6064:	f0 05       	lwi37.sp $r0,[+#0x14]
    6066:	f0 82       	swi37.sp $r0,[+#0x8]
    6068:	44 00 01 38 	movi $r0,#0x138
    606c:	f0 83       	swi37.sp $r0,[+#0xc]
    606e:	44 00 3b a0 	movi $r0,#0x3ba0
    6072:	49 ff e1 e3 	jal 2438 <printf>
    6076:	84 1f       	movi55 $r0,#-1
    6078:	a8 3c       	swi333 $r0,[$r7+#0x10]
    607a:	48 ff ff 9e 	j 5fb6 <lfs_file_relocate+0x36>
    607e:	92 00       	nop16
    6080:	04 03 80 1a 	lwi $r0,[$r7+#0x68]
    6084:	04 13 80 07 	lwi $r1,[$r7+#0x1c]
    6088:	04 20 00 0a 	lwi $r2,[$r0+#0x28]
    608c:	04 04 00 13 	lwi $r0,[$r8+#0x4c]
    6090:	49 00 1f 5e 	jal 9f4c <memcpy>
    6094:	04 23 80 1a 	lwi $r2,[$r7+#0x68]
    6098:	a0 7d       	lwi333 $r1,[$r7+#0x14]
    609a:	a0 3e       	lwi333 $r0,[$r7+#0x18]
    609c:	a0 fc       	lwi333 $r3,[$r7+#0x10]
    609e:	14 34 00 10 	swi $r3,[$r8+#0x40]
    60a2:	14 14 00 11 	swi $r1,[$r8+#0x44]
    60a6:	14 04 00 12 	swi $r0,[$r8+#0x48]
    60aa:	44 10 00 ff 	movi $r1,#0xff
    60ae:	a0 3f       	lwi333 $r0,[$r7+#0x1c]
    60b0:	04 21 00 0a 	lwi $r2,[$r2+#0x28]
    60b4:	49 00 1f 80 	jal 9fb4 <memset>
    60b8:	84 1f       	movi55 $r0,#-1
    60ba:	a8 3c       	swi333 $r0,[$r7+#0x10]
    60bc:	04 04 00 0c 	lwi $r0,[$r8+#0x30]
    60c0:	f1 05       	lwi37.sp $r1,[+#0x14]
    60c2:	42 00 44 08 	bset $r0,$r0,#0x11
    60c6:	14 04 00 0c 	swi $r0,[$r8+#0x30]
    60ca:	14 14 00 0e 	swi $r1,[$r8+#0x38]
    60ce:	84 00       	movi55 $r0,#0x0
    60d0:	ec 18       	addi10.sp #0x18
    60d2:	34 3f 90 03 	fldi.bi $fd3,[$sp],#0xc
    60d6:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    60da:	dd 9e       	ret5 $lp
    60dc:	44 00 36 cc 	movi $r0,#0x36cc
    60e0:	44 10 0a 0c 	movi $r1,#0xa0c
    60e4:	44 20 7c 84 	movi $r2,#0x7c84
    60e8:	44 30 3a 54 	movi $r3,#0x3a54
    60ec:	49 00 1d 94 	jal 9c14 <__assert_func>
    60f0:	92 00       	nop16
    60f2:	92 00       	nop16

000060f4 <lfs_file_write>:
    60f4:	3a 6f ba bc 	smw.adm $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    60f8:	ef b4       	addi10.sp #-76
    60fa:	36 3f 80 08 	fsdi $fd3,[$sp+#0x20]
    60fe:	36 4f 80 0a 	fsdi $fd4,[$sp+#0x28]
    6102:	36 5f 80 0c 	fsdi $fd5,[$sp+#0x30]
    6106:	36 6f 80 0e 	fsdi $fd6,[$sp+#0x38]
    610a:	36 7f 80 10 	fsdi $fd7,[$sp+#0x40]
    610e:	05 00 80 0c 	lwi $r16,[$r1+#0x30]
    6112:	80 e1       	mov55 $r7,$r1
    6114:	42 48 54 0b 	btst $r4,$r16,#0x15
    6118:	4e 42 01 fc 	beqz $r4,6510 <lfs_file_write+0x41c>
    611c:	81 42       	mov55 $r10,$r2
    611e:	54 28 00 03 	andi $r2,$r16,#0x3
    6122:	5a 28 01 05 	bnec $r2,#0x1,612c <lfs_file_write+0x38>
    6126:	48 00 02 01 	j 6528 <lfs_file_write+0x434>
    612a:	92 00       	nop16
    612c:	42 28 48 0b 	btst $r2,$r16,#0x12
    6130:	80 c0       	mov55 $r6,$r0
    6132:	6a 37 00 09 	fmtsr $r3,$fs14
    6136:	4e 23 01 63 	bnez $r2,63fc <lfs_file_write+0x308>
    613a:	92 00       	nop16
    613c:	54 08 08 00 	andi $r0,$r16,#0x800
    6140:	04 83 80 0d 	lwi $r8,[$r7+#0x34]
    6144:	c0 08       	beqz38 $r0,6154 <lfs_file_write+0x60>
    6146:	04 03 80 0b 	lwi $r0,[$r7+#0x2c]
    614a:	e3 00       	slt45 $r8,$r0
    614c:	e8 04       	beqzs8 6154 <lfs_file_write+0x60>
    614e:	14 03 80 0d 	swi $r0,[$r7+#0x34]
    6152:	81 00       	mov55 $r8,$r0
    6154:	6a 17 00 01 	fmfsr $r1,$fs14
    6158:	04 03 00 1c 	lwi $r0,[$r6+#0x70]
    615c:	88 28       	add45 $r1,$r8
    615e:	e2 01       	slt45 $r0,$r1
    6160:	4e f3 01 ca 	bnez $r15,64f4 <lfs_file_write+0x400>
    6164:	42 08 44 0b 	btst $r0,$r16,#0x11
    6168:	c8 18       	bnez38 $r0,6198 <lfs_file_write+0xa4>
    616a:	04 03 80 0b 	lwi $r0,[$r7+#0x2c]
    616e:	e2 08       	slt45 $r0,$r8
    6170:	e8 14       	beqzs8 6198 <lfs_file_write+0xa4>
    6172:	14 03 80 0d 	swi $r0,[$r7+#0x34]
    6176:	85 20       	movi55 $r9,#0x0
    6178:	fd 03       	movd44 $r0,$r6
    617a:	50 2f 80 13 	addi $r2,$sp,#0x13
    617e:	84 61       	movi55 $r3,#0x1
    6180:	10 9f 80 13 	sbi $r9,[$sp+#0x13]
    6184:	49 ff ff b8 	jal 60f4 <lfs_file_write>
    6188:	4e 05 01 16 	bltz $r0,63b4 <lfs_file_write+0x2c0>
    618c:	04 03 80 0d 	lwi $r0,[$r7+#0x34]
    6190:	e2 08       	slt45 $r0,$r8
    6192:	e9 f3       	bnezs8 6178 <lfs_file_write+0x84>
    6194:	05 03 80 0c 	lwi $r16,[$r7+#0x30]
    6198:	42 08 50 0b 	btst $r0,$r16,#0x14
    619c:	4e 03 00 7c 	bnez $r0,6294 <lfs_file_write+0x1a0>
    61a0:	6a 07 00 01 	fmfsr $r0,$fs14
    61a4:	c0 58       	beqz38 $r0,6254 <lfs_file_write+0x160>
    61a6:	46 00 01 00 	sethi $r0,#0x100
    61aa:	6a 04 80 09 	fmtsr $r0,$fs9
    61ae:	50 03 80 38 	addi $r0,$r7,#0x38
    61b2:	6a 03 00 09 	fmtsr $r0,$fs6
    61b6:	50 03 80 3c 	addi $r0,$r7,#0x3c
    61ba:	6a 03 80 09 	fmtsr $r0,$fs7
    61be:	6a d7 00 01 	fmfsr $r13,$fs14
    61c2:	50 93 80 40 	addi $r9,$r7,#0x40
    61c6:	50 bf 80 1c 	addi $r11,$sp,#0x1c
    61ca:	92 00       	nop16
    61cc:	42 08 44 0b 	btst $r0,$r16,#0x11
    61d0:	c0 4a       	beqz38 $r0,6264 <lfs_file_write+0x170>
    61d2:	04 13 00 1a 	lwi $r1,[$r6+#0x68]
    61d6:	04 53 80 0f 	lwi $r5,[$r7+#0x3c]
    61da:	04 80 80 07 	lwi $r8,[$r1+#0x1c]
    61de:	4c 54 01 17 	beq $r5,$r8,640c <lfs_file_write+0x318>
    61e2:	04 43 80 0e 	lwi $r4,[$r7+#0x38]
    61e6:	8b 05       	sub45 $r8,$r5
    61e8:	40 06 a0 06 	slt $r0,$r13,$r8
    61ec:	40 86 80 1b 	cmovn $r8,$r13,$r0
    61f0:	d5 10       	j8 6210 <lfs_file_write+0x11c>
    61f2:	92 00       	nop16
    61f4:	5a 07 ac 04 	beqc $r0,#-84,61fc <lfs_file_write+0x108>
    61f8:	48 00 00 d8 	j 63a8 <lfs_file_write+0x2b4>
    61fc:	fd 03       	movd44 $r0,$r6
    61fe:	49 ff fe c1 	jal 5f80 <lfs_file_relocate>
    6202:	92 00       	nop16
    6204:	4e 03 00 d2 	bnez $r0,63a8 <lfs_file_write+0x2b4>
    6208:	04 53 80 0f 	lwi $r5,[$r7+#0x3c]
    620c:	04 43 80 0e 	lwi $r4,[$r7+#0x38]
    6210:	b7 5f       	swi450 $r10,[$sp]
    6212:	14 8f 80 01 	swi $r8,[$sp+#0x4]
    6216:	80 06       	mov55 $r0,$r6
    6218:	80 29       	mov55 $r1,$r9
    621a:	80 46       	mov55 $r2,$r6
    621c:	84 61       	movi55 $r3,#0x1
    621e:	49 ff f6 9d 	jal 4f58 <lfs_bd_prog>
    6222:	c8 e9       	bnez38 $r0,61f4 <lfs_file_write+0x100>
    6224:	04 13 80 0d 	lwi $r1,[$r7+#0x34]
    6228:	04 03 80 0f 	lwi $r0,[$r7+#0x3c]
    622c:	04 23 00 1a 	lwi $r2,[$r6+#0x68]
    6230:	88 28       	add45 $r1,$r8
    6232:	04 21 00 08 	lwi $r2,[$r2+#0x20]
    6236:	88 08       	add45 $r0,$r8
    6238:	14 13 80 0d 	swi $r1,[$r7+#0x34]
    623c:	14 03 80 0f 	swi $r0,[$r7+#0x3c]
    6240:	40 d6 a0 01 	sub $r13,$r13,$r8
    6244:	14 23 00 18 	swi $r2,[$r6+#0x60]
    6248:	89 48       	add45 $r10,$r8
    624a:	05 03 80 0c 	lwi $r16,[$r7+#0x30]
    624e:	4e d3 ff bf 	bnez $r13,61cc <lfs_file_write+0xd8>
    6252:	92 00       	nop16
    6254:	43 08 4c 09 	bclr $r16,$r16,#0x13
    6258:	15 03 80 0c 	swi $r16,[$r7+#0x30]
    625c:	6a 07 00 01 	fmfsr $r0,$fs14
    6260:	48 00 00 aa 	j 63b4 <lfs_file_write+0x2c0>
    6264:	6a 04 80 01 	fmfsr $r0,$fs9
    6268:	40 08 00 02 	and $r0,$r16,$r0
    626c:	4e 02 00 44 	beqz $r0,62f4 <lfs_file_write+0x200>
    6270:	04 13 00 1a 	lwi $r1,[$r6+#0x68]
    6274:	04 53 80 0d 	lwi $r5,[$r7+#0x34]
    6278:	84 1e       	movi55 $r0,#-2
    627a:	14 03 80 0e 	swi $r0,[$r7+#0x38]
    627e:	14 53 80 0f 	swi $r5,[$r7+#0x3c]
    6282:	84 9e       	movi55 $r4,#-2
    6284:	43 08 44 08 	bset $r16,$r16,#0x11
    6288:	15 03 80 0c 	swi $r16,[$r7+#0x30]
    628c:	04 80 80 07 	lwi $r8,[$r1+#0x1c]
    6290:	d5 ab       	j8 61e6 <lfs_file_write+0xf2>
    6292:	92 00       	nop16
    6294:	04 53 00 1a 	lwi $r5,[$r6+#0x68]
    6298:	44 00 03 fe 	movi $r0,#0x3fe
    629c:	04 42 80 0a 	lwi $r4,[$r5+#0x28]
    62a0:	05 23 80 0d 	lwi $r18,[$r7+#0x34]
    62a4:	a0 af       	lwi333 $r2,[$r5+#0x1c]
    62a6:	6a 37 00 01 	fmfsr $r3,$fs14
    62aa:	e2 04       	slt45 $r0,$r4
    62ac:	05 13 80 0b 	lwi $r17,[$r7+#0x2c]
    62b0:	40 02 3c 1a 	cmovz $r0,$r4,$r15
    62b4:	88 72       	add45 $r3,$r18
    62b6:	92 43       	srli45 $r2,#0x3
    62b8:	e2 71       	slt45 $r3,$r17
    62ba:	40 11 00 06 	slt $r1,$r2,$r0
    62be:	40 38 bc 1b 	cmovn $r3,$r17,$r15
    62c2:	40 01 04 1b 	cmovn $r0,$r2,$r1
    62c6:	e2 03       	slt45 $r0,$r3
    62c8:	4e f2 ff 6c 	beqz $r15,61a0 <lfs_file_write+0xac>
    62cc:	04 12 80 08 	lwi $r1,[$r5+#0x20]
    62d0:	80 06       	mov55 $r0,$r6
    62d2:	15 23 80 0f 	swi $r18,[$r7+#0x3c]
    62d6:	14 13 00 18 	swi $r1,[$r6+#0x60]
    62da:	80 27       	mov55 $r1,$r7
    62dc:	49 ff fe 52 	jal 5f80 <lfs_file_relocate>
    62e0:	c8 64       	bnez38 $r0,63a8 <lfs_file_write+0x2b4>
    62e2:	05 03 80 0c 	lwi $r16,[$r7+#0x30]
    62e6:	43 08 50 09 	bclr $r16,$r16,#0x14
    62ea:	15 03 80 0c 	swi $r16,[$r7+#0x30]
    62ee:	48 ff ff 59 	j 61a0 <lfs_file_write+0xac>
    62f2:	92 00       	nop16
    62f4:	04 43 80 0d 	lwi $r4,[$r7+#0x34]
    62f8:	4e 43 00 92 	bnez $r4,641c <lfs_file_write+0x328>
    62fc:	04 13 00 1a 	lwi $r1,[$r6+#0x68]
    6300:	04 00 80 08 	lwi $r0,[$r1+#0x20]
    6304:	14 03 00 18 	swi $r0,[$r6+#0x60]
    6308:	30 83 80 0d 	flsi $fs8,[$r7+#0x34]
    630c:	04 e3 80 0e 	lwi $r14,[$r7+#0x38]
    6310:	51 c3 00 68 	addi $fp,$r6,#0x68
    6314:	6a 04 00 01 	fmfsr $r0,$fs8
    6318:	8e 01       	subi45 $r0,#0x1
    631a:	6a 05 80 09 	fmtsr $r0,$fs11
    631e:	80 06       	mov55 $r0,$r6
    6320:	b0 45       	addri36.sp $r1,#0x14
    6322:	49 ff fd 4f 	jal 5dc0 <lfs_alloc>
    6326:	c8 41       	bnez38 $r0,63a8 <lfs_file_write+0x2b4>
    6328:	04 03 00 1a 	lwi $r0,[$r6+#0x68]
    632c:	f1 05       	lwi37.sp $r1,[+#0x14]
    632e:	49 ff f4 91 	jal 4c50 <lfs_bd_erase.isra.16>
    6332:	c8 4f       	bnez38 $r0,63d0 <lfs_file_write+0x2dc>
    6334:	6a 04 00 01 	fmfsr $r0,$fs8
    6338:	4e 02 00 e2 	beqz $r0,64fc <lfs_file_write+0x408>
    633c:	b0 46       	addri36.sp $r1,#0x18
    633e:	04 03 00 1a 	lwi $r0,[$r6+#0x68]
    6342:	32 bf 80 06 	fssi $fs11,[$sp+#0x18]
    6346:	49 ff f4 ab 	jal 4c9c <lfs_ctz_index.isra.23>
    634a:	92 00       	nop16
    634c:	04 13 00 1a 	lwi $r1,[$r6+#0x68]
    6350:	05 0f 80 06 	lwi $r16,[$sp+#0x18]
    6354:	a0 8f       	lwi333 $r2,[$r1+#0x1c]
    6356:	50 58 00 01 	addi $r5,$r16,#0x1
    635a:	f5 86       	swi37.sp $r5,[+#0x18]
    635c:	4c 51 00 7d 	beq $r5,$r2,6456 <lfs_file_write+0x362>
    6360:	4e 52 00 c0 	beqz $r5,64e0 <lfs_file_write+0x3ec>
    6364:	85 00       	movi55 $r8,#0x0
    6366:	85 81       	movi55 $r12,#0x1
    6368:	d5 12       	j8 638c <lfs_file_write+0x298>
    636a:	b7 7f       	swi450 $r11,[$sp]
    636c:	14 cf 80 01 	swi $r12,[$sp+#0x4]
    6370:	80 06       	mov55 $r0,$r6
    6372:	80 29       	mov55 $r1,$r9
    6374:	80 46       	mov55 $r2,$r6
    6376:	84 61       	movi55 $r3,#0x1
    6378:	f4 05       	lwi37.sp $r4,[+#0x14]
    637a:	80 a8       	mov55 $r5,$r8
    637c:	49 ff f5 ee 	jal 4f58 <lfs_bd_prog>
    6380:	c8 28       	bnez38 $r0,63d0 <lfs_file_write+0x2dc>
    6382:	f5 06       	lwi37.sp $r5,[+#0x18]
    6384:	8d 01       	addi45 $r8,#0x1
    6386:	e3 05       	slt45 $r8,$r5
    6388:	4e f2 00 aa 	beqz $r15,64dc <lfs_file_write+0x3e8>
    638c:	40 32 a0 01 	sub $r3,$r5,$r8
    6390:	b7 7f       	swi450 $r11,[$sp]
    6392:	14 cf 80 01 	swi $r12,[$sp+#0x4]
    6396:	80 1c       	mov55 $r0,$fp
    6398:	84 20       	movi55 $r1,#0x0
    639a:	80 46       	mov55 $r2,$r6
    639c:	80 8e       	mov55 $r4,$r14
    639e:	80 a8       	mov55 $r5,$r8
    63a0:	49 ff ee 80 	jal 40a0 <lfs_bd_read.isra.13>
    63a4:	c0 e3       	beqz38 $r0,636a <lfs_file_write+0x276>
    63a6:	92 00       	nop16
    63a8:	04 13 80 0c 	lwi $r1,[$r7+#0x30]
    63ac:	42 10 cc 08 	bset $r1,$r1,#0x13
    63b0:	14 13 80 0c 	swi $r1,[$r7+#0x30]
    63b4:	ec 20       	addi10.sp #0x20
    63b6:	34 3f 90 02 	fldi.bi $fd3,[$sp],#0x8
    63ba:	34 4f 90 02 	fldi.bi $fd4,[$sp],#0x8
    63be:	34 5f 90 02 	fldi.bi $fd5,[$sp],#0x8
    63c2:	34 6f 90 02 	fldi.bi $fd6,[$sp],#0x8
    63c6:	34 7f 90 03 	fldi.bi $fd7,[$sp],#0xc
    63ca:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    63ce:	dd 9e       	ret5 $lp
    63d0:	5a 0f ac ec 	bnec $r0,#-84,63a8 <lfs_file_write+0x2b4>
    63d4:	44 00 36 cc 	movi $r0,#0x36cc
    63d8:	b6 1f       	swi450 $r0,[$sp]
    63da:	44 00 09 1b 	movi $r0,#0x91b
    63de:	f0 81       	swi37.sp $r0,[+#0x4]
    63e0:	f0 05       	lwi37.sp $r0,[+#0x14]
    63e2:	f0 82       	swi37.sp $r0,[+#0x8]
    63e4:	44 00 01 38 	movi $r0,#0x138
    63e8:	f0 83       	swi37.sp $r0,[+#0xc]
    63ea:	44 00 3b a0 	movi $r0,#0x3ba0
    63ee:	49 ff e0 25 	jal 2438 <printf>
    63f2:	84 1f       	movi55 $r0,#-1
    63f4:	14 03 80 10 	swi $r0,[$r7+#0x40]
    63f8:	48 ff ff 93 	j 631e <lfs_file_write+0x22a>
    63fc:	49 00 00 a2 	jal 6540 <lfs_file_flush>
    6400:	c8 da       	bnez38 $r0,63b4 <lfs_file_write+0x2c0>
    6402:	05 03 80 0c 	lwi $r16,[$r7+#0x30]
    6406:	48 ff fe 9b 	j 613c <lfs_file_write+0x48>
    640a:	92 00       	nop16
    640c:	6a 04 80 01 	fmfsr $r0,$fs9
    6410:	40 08 00 02 	and $r0,$r16,$r0
    6414:	4e 02 ff 76 	beqz $r0,6300 <lfs_file_write+0x20c>
    6418:	48 ff ff 2e 	j 6274 <lfs_file_write+0x180>
    641c:	32 7f 80 00 	fssi $fs7,[$sp+#0x0]
    6420:	6a 53 00 01 	fmfsr $r5,$fs6
    6424:	80 06       	mov55 $r0,$r6
    6426:	80 29       	mov55 $r1,$r9
    6428:	04 23 80 0a 	lwi $r2,[$r7+#0x28]
    642c:	04 33 80 0b 	lwi $r3,[$r7+#0x2c]
    6430:	8e 81       	subi45 $r4,#0x1
    6432:	49 ff f4 97 	jal 4d60 <lfs_ctz_find.constprop.32>
    6436:	c8 b9       	bnez38 $r0,63a8 <lfs_file_write+0x2b4>
    6438:	04 23 00 1a 	lwi $r2,[$r6+#0x68]
    643c:	04 03 80 13 	lwi $r0,[$r7+#0x4c]
    6440:	44 10 00 ff 	movi $r1,#0xff
    6444:	04 21 00 0a 	lwi $r2,[$r2+#0x28]
    6448:	49 00 1d b6 	jal 9fb4 <memset>
    644c:	84 1f       	movi55 $r0,#-1
    644e:	14 03 80 10 	swi $r0,[$r7+#0x40]
    6452:	48 ff ff 55 	j 62fc <lfs_file_write+0x208>
    6456:	9c 41       	addi333 $r1,$r0,#0x1
    6458:	40 00 80 12 	bitc $r0,$r1,$r0
    645c:	42 00 00 07 	clz $r0,$r0
    6460:	52 00 00 1f 	subri $r0,$r0,#0x1f
    6464:	6a 06 80 09 	fmtsr $r0,$fs13
    6468:	8c 01       	addi45 $r0,#0x1
    646a:	6a 05 00 09 	fmtsr $r0,$fs10
    646e:	84 04       	movi55 $r0,#0x4
    6470:	6a 06 00 09 	fmtsr $r0,$fs12
    6474:	14 ef 80 07 	swi $r14,[$sp+#0x1c]
    6478:	85 00       	movi55 $r8,#0x0
    647a:	92 00       	nop16
    647c:	40 c4 08 08 	slli $r12,$r8,#0x2
    6480:	f4 05       	lwi37.sp $r4,[+#0x14]
    6482:	b7 7f       	swi450 $r11,[$sp]
    6484:	32 cf 80 01 	fssi $fs12,[$sp+#0x4]
    6488:	80 06       	mov55 $r0,$r6
    648a:	80 29       	mov55 $r1,$r9
    648c:	80 46       	mov55 $r2,$r6
    648e:	84 61       	movi55 $r3,#0x1
    6490:	80 ac       	mov55 $r5,$r12
    6492:	49 ff f5 63 	jal 4f58 <lfs_bd_prog>
    6496:	f4 07       	lwi37.sp $r4,[+#0x1c]
    6498:	4e 03 ff 9c 	bnez $r0,63d0 <lfs_file_write+0x2dc>
    649c:	6a 06 80 01 	fmfsr $r0,$fs13
    64a0:	4c 04 00 0e 	beq $r0,$r8,64bc <lfs_file_write+0x3c8>
    64a4:	b7 7f       	swi450 $r11,[$sp]
    64a6:	32 cf 80 01 	fssi $fs12,[$sp+#0x4]
    64aa:	80 1c       	mov55 $r0,$fp
    64ac:	84 20       	movi55 $r1,#0x0
    64ae:	80 46       	mov55 $r2,$r6
    64b0:	84 64       	movi55 $r3,#0x4
    64b2:	80 ac       	mov55 $r5,$r12
    64b4:	49 ff ed f6 	jal 40a0 <lfs_bd_read.isra.13>
    64b8:	4e 03 ff 78 	bnez $r0,63a8 <lfs_file_write+0x2b4>
    64bc:	6a 05 00 01 	fmfsr $r0,$fs10
    64c0:	8d 01       	addi45 $r8,#0x1
    64c2:	e3 00       	slt45 $r8,$r0
    64c4:	e9 dc       	bnezs8 647c <lfs_file_write+0x388>
    64c6:	6a 05 00 01 	fmfsr $r0,$fs10
    64ca:	f4 05       	lwi37.sp $r4,[+#0x14]
    64cc:	95 42       	slli333 $r5,$r0,#0x2
    64ce:	14 43 80 0e 	swi $r4,[$r7+#0x38]
    64d2:	14 53 80 0f 	swi $r5,[$r7+#0x3c]
    64d6:	04 13 00 1a 	lwi $r1,[$r6+#0x68]
    64da:	d5 09       	j8 64ec <lfs_file_write+0x3f8>
    64dc:	04 13 00 1a 	lwi $r1,[$r6+#0x68]
    64e0:	04 4f 80 05 	lwi $r4,[$sp+#0x14]
    64e4:	14 43 80 0e 	swi $r4,[$r7+#0x38]
    64e8:	14 53 80 0f 	swi $r5,[$r7+#0x3c]
    64ec:	05 03 80 0c 	lwi $r16,[$r7+#0x30]
    64f0:	48 ff fe ca 	j 6284 <lfs_file_write+0x190>
    64f4:	44 0f ff e5 	movi $r0,#-27
    64f8:	48 ff ff 5e 	j 63b4 <lfs_file_write+0x2c0>
    64fc:	f4 05       	lwi37.sp $r4,[+#0x14]
    64fe:	14 43 80 0e 	swi $r4,[$r7+#0x38]
    6502:	32 83 80 0f 	fssi $fs8,[$r7+#0x3c]
    6506:	04 13 00 1a 	lwi $r1,[$r6+#0x68]
    650a:	84 a0       	movi55 $r5,#0x0
    650c:	d5 f0       	j8 64ec <lfs_file_write+0x3f8>
    650e:	92 00       	nop16
    6510:	44 00 36 cc 	movi $r0,#0x36cc
    6514:	44 10 0b 3b 	movi $r1,#0xb3b
    6518:	44 20 7b e0 	movi $r2,#0x7be0
    651c:	44 30 3a 54 	movi $r3,#0x3a54
    6520:	49 00 1b 7a 	jal 9c14 <__assert_func>
    6524:	92 00       	nop16
    6526:	92 00       	nop16
    6528:	44 00 36 cc 	movi $r0,#0x36cc
    652c:	44 10 0b 3c 	movi $r1,#0xb3c
    6530:	44 20 7b e0 	movi $r2,#0x7be0
    6534:	44 30 3b c4 	movi $r3,#0x3bc4
    6538:	49 00 1b 6e 	jal 9c14 <__assert_func>
    653c:	92 00       	nop16
    653e:	92 00       	nop16

00006540 <lfs_file_flush>:
    6540:	3a 6f b0 bc 	smw.adm $r6,[$sp],$r12,#0x2    ! {$r6~$r12, $lp}
    6544:	ef 98       	addi10.sp #-104
    6546:	80 c1       	mov55 $r6,$r1
    6548:	04 10 80 0c 	lwi $r1,[$r1+#0x30]
    654c:	80 e0       	mov55 $r7,$r0
    654e:	42 00 d4 0b 	btst $r0,$r1,#0x15
    6552:	4e 02 00 a7 	beqz $r0,66a0 <lfs_file_flush+0x160>
    6556:	42 00 c8 0b 	btst $r0,$r1,#0x12
    655a:	c0 09       	beqz38 $r0,656c <lfs_file_flush+0x2c>
    655c:	42 00 d0 0b 	btst $r0,$r1,#0x14
    6560:	4e 02 00 70 	beqz $r0,6640 <lfs_file_flush+0x100>
    6564:	42 10 c8 09 	bclr $r1,$r1,#0x12
    6568:	14 13 00 0c 	swi $r1,[$r6+#0x30]
    656c:	42 00 c4 0b 	btst $r0,$r1,#0x11
    6570:	84 60       	movi55 $r3,#0x0
    6572:	c0 48       	beqz38 $r0,6602 <lfs_file_flush+0xc2>
    6574:	42 00 d0 0b 	btst $r0,$r1,#0x14
    6578:	04 93 00 0d 	lwi $r9,[$r6+#0x34]
    657c:	c8 48       	bnez38 $r0,660c <lfs_file_flush+0xcc>
    657e:	84 20       	movi55 $r1,#0x0
    6580:	44 20 00 54 	movi $r2,#0x54
    6584:	b0 05       	addri36.sp $r0,#0x14
    6586:	49 00 1d 17 	jal 9fb4 <memset>
    658a:	84 1f       	movi55 $r0,#-1
    658c:	04 23 00 0b 	lwi $r2,[$r6+#0x2c]
    6590:	04 33 00 0a 	lwi $r3,[$r6+#0x28]
    6594:	3b 03 cc 00 	lmw.bi $r16,[$r7],$r19,#0x0    ! {$r16~$r19}
    6598:	b6 07       	swi450 $r0,[$r7]
    659a:	04 13 00 0d 	lwi $r1,[$r6+#0x34]
    659e:	04 43 00 0b 	lwi $r4,[$r6+#0x2c]
    65a2:	f2 90       	swi37.sp $r2,[+#0x40]
    65a4:	46 20 02 00 	sethi $r2,#0x200
    65a8:	b0 15       	addri36.sp $r0,#0x54
    65aa:	8c 41       	addi45 $r2,#0x1
    65ac:	40 10 90 06 	slt $r1,$r1,$r4
    65b0:	f3 8f       	swi37.sp $r3,[+#0x3c]
    65b2:	f2 91       	swi37.sp $r2,[+#0x44]
    65b4:	14 9f 80 12 	swi $r9,[$sp+#0x48]
    65b8:	3b 00 4c 20 	smw.bi $r16,[$r0],$r19,#0x0    ! {$r16~$r19}
    65bc:	c1 48       	beqz38 $r1,664c <lfs_file_flush+0x10c>
    65be:	85 1f       	movi55 $r8,#-1
    65c0:	d5 16       	j8 65ec <lfs_file_flush+0xac>
    65c2:	80 07       	mov55 $r0,$r7
    65c4:	80 26       	mov55 $r1,$r6
    65c6:	50 2f 80 13 	addi $r2,$sp,#0x13
    65ca:	84 61       	movi55 $r3,#0x1
    65cc:	49 ff fd 94 	jal 60f4 <lfs_file_write>
    65d0:	4e 05 00 18 	bltz $r0,6600 <lfs_file_flush+0xc0>
    65d4:	b4 07       	lwi450 $r0,[$r7]
    65d6:	5a 07 ff 05 	beqc $r0,#-1,65e0 <lfs_file_flush+0xa0>
    65da:	14 8f 80 15 	swi $r8,[$sp+#0x54]
    65de:	b7 07       	swi450 $r8,[$r7]
    65e0:	04 03 00 0d 	lwi $r0,[$r6+#0x34]
    65e4:	04 13 00 0b 	lwi $r1,[$r6+#0x2c]
    65e8:	e2 01       	slt45 $r0,$r1
    65ea:	e8 31       	beqzs8 664c <lfs_file_flush+0x10c>
    65ec:	80 07       	mov55 $r0,$r7
    65ee:	b0 45       	addri36.sp $r1,#0x14
    65f0:	50 2f 80 13 	addi $r2,$sp,#0x13
    65f4:	44 30 00 01 	movi $r3,#0x1
    65f8:	49 00 00 60 	jal 66b8 <lfs_file_read>
    65fc:	4e 04 ff e3 	bgez $r0,65c2 <lfs_file_flush+0x82>
    6600:	80 60       	mov55 $r3,$r0
    6602:	80 03       	mov55 $r0,$r3
    6604:	ec 68       	addi10.sp #0x68
    6606:	3a 6f b0 84 	lmw.bim $r6,[$sp],$r12,#0x2    ! {$r6~$r12, $lp}
    660a:	dd 9e       	ret5 $lp
    660c:	04 23 00 0b 	lwi $r2,[$r6+#0x2c]
    6610:	e2 49       	slt45 $r2,$r9
    6612:	40 24 bc 1b 	cmovn $r2,$r9,$r15
    6616:	80 02       	mov55 $r0,$r2
    6618:	42 10 c4 09 	bclr $r1,$r1,#0x11
    661c:	04 23 00 0e 	lwi $r2,[$r6+#0x38]
    6620:	42 10 c0 08 	bset $r1,$r1,#0x10
    6624:	84 60       	movi55 $r3,#0x0
    6626:	14 03 00 0b 	swi $r0,[$r6+#0x2c]
    662a:	14 23 00 0a 	swi $r2,[$r6+#0x28]
    662e:	80 03       	mov55 $r0,$r3
    6630:	14 13 00 0c 	swi $r1,[$r6+#0x30]
    6634:	14 93 00 0d 	swi $r9,[$r6+#0x34]
    6638:	ec 68       	addi10.sp #0x68
    663a:	3a 6f b0 84 	lmw.bim $r6,[$sp],$r12,#0x2    ! {$r6~$r12, $lp}
    663e:	dd 9e       	ret5 $lp
    6640:	84 1f       	movi55 $r0,#-1
    6642:	14 03 00 10 	swi $r0,[$r6+#0x40]
    6646:	48 ff ff 8f 	j 6564 <lfs_file_flush+0x24>
    664a:	92 00       	nop16
    664c:	50 83 00 40 	addi $r8,$r6,#0x40
    6650:	44 c0 36 cc 	movi $r12,#0x36cc
    6654:	44 b0 0a 98 	movi $r11,#0xa98
    6658:	44 a0 01 38 	movi $r10,#0x138
    665c:	d5 16       	j8 6688 <lfs_file_flush+0x148>
    665e:	92 00       	nop16
    6660:	5a 0f ac d0 	bnec $r0,#-84,6600 <lfs_file_flush+0xc0>
    6664:	04 03 00 0e 	lwi $r0,[$r6+#0x38]
    6668:	f0 82       	swi37.sp $r0,[+#0x8]
    666a:	14 cf 80 00 	swi $r12,[$sp+#0x0]
    666e:	14 bf 80 01 	swi $r11,[$sp+#0x4]
    6672:	14 af 80 03 	swi $r10,[$sp+#0xc]
    6676:	44 00 3b a0 	movi $r0,#0x3ba0
    667a:	49 ff de df 	jal 2438 <printf>
    667e:	80 07       	mov55 $r0,$r7
    6680:	80 26       	mov55 $r1,$r6
    6682:	49 ff fc 7f 	jal 5f80 <lfs_file_relocate>
    6686:	c8 bd       	bnez38 $r0,6600 <lfs_file_flush+0xc0>
    6688:	80 07       	mov55 $r0,$r7
    668a:	80 28       	mov55 $r1,$r8
    668c:	80 47       	mov55 $r2,$r7
    668e:	84 61       	movi55 $r3,#0x1
    6690:	49 ff f4 00 	jal 4e90 <lfs_bd_flush>
    6694:	c8 e6       	bnez38 $r0,6660 <lfs_file_flush+0x120>
    6696:	04 03 00 0d 	lwi $r0,[$r6+#0x34]
    669a:	04 13 00 0c 	lwi $r1,[$r6+#0x30]
    669e:	d5 bd       	j8 6618 <lfs_file_flush+0xd8>
    66a0:	44 00 36 cc 	movi $r0,#0x36cc
    66a4:	44 10 0a 5f 	movi $r1,#0xa5f
    66a8:	44 20 7c 48 	movi $r2,#0x7c48
    66ac:	44 30 3a 54 	movi $r3,#0x3a54
    66b0:	49 00 1a b2 	jal 9c14 <__assert_func>
    66b4:	92 00       	nop16
    66b6:	92 00       	nop16

000066b8 <lfs_file_read>:
    66b8:	3a 6f ba bc 	smw.adm $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    66bc:	ef dc       	addi10.sp #-36
    66be:	36 3f 80 04 	fsdi $fd3,[$sp+#0x10]
    66c2:	36 4f 80 06 	fsdi $fd4,[$sp+#0x18]
    66c6:	04 40 80 0c 	lwi $r4,[$r1+#0x30]
    66ca:	80 c1       	mov55 $r6,$r1
    66cc:	42 52 54 0b 	btst $r5,$r4,#0x15
    66d0:	4e 52 00 be 	beqz $r5,684c <lfs_file_read+0x194>
    66d4:	81 22       	mov55 $r9,$r2
    66d6:	54 22 00 03 	andi $r2,$r4,#0x3
    66da:	5a 28 02 05 	bnec $r2,#0x2,66e4 <lfs_file_read+0x2c>
    66de:	48 00 00 ab 	j 6834 <lfs_file_read+0x17c>
    66e2:	92 00       	nop16
    66e4:	42 42 44 0b 	btst $r4,$r4,#0x11
    66e8:	81 40       	mov55 $r10,$r0
    66ea:	4e 43 00 8d 	bnez $r4,6804 <lfs_file_read+0x14c>
    66ee:	92 00       	nop16
    66f0:	04 43 00 0d 	lwi $r4,[$r6+#0x34]
    66f4:	04 13 00 0b 	lwi $r1,[$r6+#0x2c]
    66f8:	84 00       	movi55 $r0,#0x0
    66fa:	e2 81       	slt45 $r4,$r1
    66fc:	e8 68       	beqzs8 67cc <lfs_file_read+0x114>
    66fe:	8a 24       	sub45 $r1,$r4
    6700:	e2 23       	slt45 $r1,$r3
    6702:	40 11 bc 1a 	cmovz $r1,$r3,$r15
    6706:	6a 13 00 09 	fmtsr $r1,$fs6
    670a:	50 c3 00 40 	addi $r12,$r6,#0x40
    670e:	81 01       	mov55 $r8,$r1
    6710:	4e 12 00 88 	beqz $r1,6820 <lfs_file_read+0x168>
    6714:	50 03 00 38 	addi $r0,$r6,#0x38
    6718:	6a 04 00 09 	fmtsr $r0,$fs8
    671c:	50 03 00 3c 	addi $r0,$r6,#0x3c
    6720:	46 b0 01 00 	sethi $r11,#0x100
    6724:	6a 03 80 09 	fmtsr $r0,$fs7
    6728:	51 c5 00 68 	addi $fp,$r10,#0x68
    672c:	50 e3 00 08 	addi $r14,$r6,#0x8
    6730:	46 d2 01 00 	sethi $r13,#0x20100
    6734:	d5 2a       	j8 6788 <lfs_file_read+0xd0>
    6736:	92 00       	nop16
    6738:	04 05 00 1a 	lwi $r0,[$r10+#0x68]
    673c:	04 53 00 0f 	lwi $r5,[$r6+#0x3c]
    6740:	a0 c7       	lwi333 $r3,[$r0+#0x1c]
    6742:	d3 29       	beqs38 $r3,6794 <lfs_file_read+0xdc>
    6744:	9b dd       	sub333 $r7,$r3,$r5
    6746:	e3 07       	slt45 $r8,$r7
    6748:	40 08 2c 02 	and $r0,$r16,$r11
    674c:	40 74 3c 1b 	cmovn $r7,$r8,$r15
    6750:	c0 34       	beqz38 $r0,67b8 <lfs_file_read+0x100>
    6752:	a5 32       	lhi333 $r4,[$r6+#0x4]
    6754:	80 0a       	mov55 $r0,$r10
    6756:	40 42 28 08 	slli $r4,$r4,#0xa
    675a:	b7 3f       	swi450 $r9,[$sp]
    675c:	f7 81       	swi37.sp $r7,[+#0x4]
    675e:	80 2e       	mov55 $r1,$r14
    6760:	80 4c       	mov55 $r2,$r12
    6762:	40 42 34 04 	or $r4,$r4,$r13
    6766:	49 ff f8 bd 	jal 58e0 <lfs_dir_getread.constprop.33>
    676a:	c8 31       	bnez38 $r0,67cc <lfs_file_read+0x114>
    676c:	04 43 00 0d 	lwi $r4,[$r6+#0x34]
    6770:	05 03 00 0f 	lwi $r16,[$r6+#0x3c]
    6774:	88 87       	add45 $r4,$r7
    6776:	89 87       	add45 $r16,$r7
    6778:	8b 07       	sub45 $r8,$r7
    677a:	14 43 00 0d 	swi $r4,[$r6+#0x34]
    677e:	15 03 00 0f 	swi $r16,[$r6+#0x3c]
    6782:	89 27       	add45 $r9,$r7
    6784:	4e 82 00 4e 	beqz $r8,6820 <lfs_file_read+0x168>
    6788:	05 03 00 0c 	lwi $r16,[$r6+#0x30]
    678c:	42 f8 48 0b 	btst $r15,$r16,#0x12
    6790:	4e f3 ff d4 	bnez $r15,6738 <lfs_file_read+0x80>
    6794:	40 f8 2c 02 	and $r15,$r16,$r11
    6798:	e8 22       	beqzs8 67dc <lfs_file_read+0x124>
    679a:	84 1e       	movi55 $r0,#-2
    679c:	50 52 00 00 	addi $r5,$r4,#0x0
    67a0:	14 03 00 0e 	swi $r0,[$r6+#0x38]
    67a4:	14 43 00 0f 	swi $r4,[$r6+#0x3c]
    67a8:	04 05 00 1a 	lwi $r0,[$r10+#0x68]
    67ac:	43 08 48 08 	bset $r16,$r16,#0x12
    67b0:	15 03 00 0c 	swi $r16,[$r6+#0x30]
    67b4:	a0 c7       	lwi333 $r3,[$r0+#0x1c]
    67b6:	d5 c7       	j8 6744 <lfs_file_read+0x8c>
    67b8:	b7 3f       	swi450 $r9,[$sp]
    67ba:	f7 81       	swi37.sp $r7,[+#0x4]
    67bc:	80 1c       	mov55 $r0,$fp
    67be:	84 20       	movi55 $r1,#0x0
    67c0:	80 4c       	mov55 $r2,$r12
    67c2:	04 43 00 0e 	lwi $r4,[$r6+#0x38]
    67c6:	49 ff ec 6d 	jal 40a0 <lfs_bd_read.isra.13>
    67ca:	c0 d1       	beqz38 $r0,676c <lfs_file_read+0xb4>
    67cc:	ec 10       	addi10.sp #0x10
    67ce:	34 3f 90 02 	fldi.bi $fd3,[$sp],#0x8
    67d2:	34 4f 90 03 	fldi.bi $fd4,[$sp],#0xc
    67d6:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    67da:	dd 9e       	ret5 $lp
    67dc:	32 7f 80 00 	fssi $fs7,[$sp+#0x0]
    67e0:	6a 54 00 01 	fmfsr $r5,$fs8
    67e4:	80 0a       	mov55 $r0,$r10
    67e6:	80 2c       	mov55 $r1,$r12
    67e8:	04 23 00 0a 	lwi $r2,[$r6+#0x28]
    67ec:	04 33 00 0b 	lwi $r3,[$r6+#0x2c]
    67f0:	04 43 00 0d 	lwi $r4,[$r6+#0x34]
    67f4:	49 ff f2 b6 	jal 4d60 <lfs_ctz_find.constprop.32>
    67f8:	c8 ea       	bnez38 $r0,67cc <lfs_file_read+0x114>
    67fa:	05 03 00 0c 	lwi $r16,[$r6+#0x30]
    67fe:	04 53 00 0f 	lwi $r5,[$r6+#0x3c]
    6802:	d5 d3       	j8 67a8 <lfs_file_read+0xf0>
    6804:	f3 83       	swi37.sp $r3,[+#0xc]
    6806:	49 ff fe 9d 	jal 6540 <lfs_file_flush>
    680a:	f3 03       	lwi37.sp $r3,[+#0xc]
    680c:	4e 02 ff 72 	beqz $r0,66f0 <lfs_file_read+0x38>
    6810:	ec 10       	addi10.sp #0x10
    6812:	34 3f 90 02 	fldi.bi $fd3,[$sp],#0x8
    6816:	34 4f 90 03 	fldi.bi $fd4,[$sp],#0xc
    681a:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    681e:	dd 9e       	ret5 $lp
    6820:	6a 03 00 01 	fmfsr $r0,$fs6
    6824:	ec 10       	addi10.sp #0x10
    6826:	34 3f 90 02 	fldi.bi $fd3,[$sp],#0x8
    682a:	34 4f 90 03 	fldi.bi $fd4,[$sp],#0xc
    682e:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    6832:	dd 9e       	ret5 $lp
    6834:	44 00 36 cc 	movi $r0,#0x36cc
    6838:	44 10 0a ec 	movi $r1,#0xaec
    683c:	44 20 7b f0 	movi $r2,#0x7bf0
    6840:	44 30 3b e8 	movi $r3,#0x3be8
    6844:	49 00 19 e8 	jal 9c14 <__assert_func>
    6848:	92 00       	nop16
    684a:	92 00       	nop16
    684c:	44 00 36 cc 	movi $r0,#0x36cc
    6850:	44 10 0a eb 	movi $r1,#0xaeb
    6854:	44 20 7b f0 	movi $r2,#0x7bf0
    6858:	44 30 3a 54 	movi $r3,#0x3a54
    685c:	49 00 19 dc 	jal 9c14 <__assert_func>
    6860:	92 00       	nop16
    6862:	92 00       	nop16

00006864 <lfs_fs_size>:
    6864:	3b ff fc bc 	smw.adm $sp,[$sp],$sp,#0x2    ! {$lp}
    6868:	ef f4       	addi10.sp #-12
    686a:	84 80       	movi55 $r4,#0x0
    686c:	44 10 36 6c 	movi $r1,#0x366c
    6870:	b0 81       	addri36.sp $r2,#0x4
    6872:	84 60       	movi55 $r3,#0x0
    6874:	f4 81       	swi37.sp $r4,[+#0x4]
    6876:	49 ff f9 e9 	jal 5c48 <lfs_fs_traverseraw>
    687a:	f1 01       	lwi37.sp $r1,[+#0x4]
    687c:	40 00 80 1a 	cmovz $r0,$r1,$r0
    6880:	ec 0c       	addi10.sp #0xc
    6882:	3b ff fc 84 	lmw.bim $sp,[$sp],$sp,#0x2    ! {$lp}
    6886:	dd 9e       	ret5 $lp

00006888 <lfs_dir_compact>:
    6888:	3a 6f ba bc 	smw.adm $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    688c:	ef 7c       	addi10.sp #-132
    688e:	36 3f 80 1c 	fsdi $fd3,[$sp+#0x70]
    6892:	36 4f 80 1e 	fsdi $fd4,[$sp+#0x78]
    6896:	03 cf 80 58 	lhi $fp,[$sp+#0xb0]
    689a:	b5 81       	lwi450 $r16,[$r1]
    689c:	40 6e 14 01 	sub $r6,$fp,$r5
    68a0:	80 e5       	mov55 $r7,$r5
    68a2:	81 21       	mov55 $r9,$r1
    68a4:	a1 49       	lwi333 $r5,[$r1+#0x4]
    68a6:	e4 c2       	sltsi45 $r6,#0x2
    68a8:	81 00       	mov55 $r8,$r0
    68aa:	fd 51       	movd44 $r10,$r2
    68ac:	81 84       	mov55 $r12,$r4
    68ae:	15 0f 80 08 	swi $r16,[$sp+#0x20]
    68b2:	f5 89       	swi37.sp $r5,[+#0x24]
    68b4:	4e f3 01 c4 	bnez $r15,6c3c <lfs_dir_compact+0x3b4>
    68b8:	fe 3a       	neg33 $r0,$r7
    68ba:	96 03       	seh33 $r0,$r0
    68bc:	6a 04 00 09 	fmtsr $r0,$fs8
    68c0:	44 00 36 50 	movi $r0,#0x3650
    68c4:	6a 04 80 09 	fmtsr $r0,$fs9
    68c8:	b0 14       	addri36.sp $r0,#0x50
    68ca:	6a 03 00 09 	fmtsr $r0,$fs6
    68ce:	46 04 00 ff 	sethi $r0,#0x400ff
    68d2:	50 00 0c 00 	addi $r0,$r0,#0xc00
    68d6:	85 a0       	movi55 $r13,#0x0
    68d8:	6a 03 80 09 	fmtsr $r0,$fs7
    68dc:	d5 2c       	j8 6934 <lfs_dir_compact+0xac>
    68de:	92 00       	nop16
    68e0:	5e f3 00 ff 	sltsi $r15,$r6,#0xff
    68e4:	e8 15       	beqzs8 690e <lfs_dir_compact+0x86>
    68e6:	04 04 00 1a 	lwi $r0,[$r8+#0x68]
    68ea:	a0 47       	lwi333 $r1,[$r0+#0x1c]
    68ec:	a0 86       	lwi333 $r2,[$r0+#0x18]
    68ee:	41 10 84 09 	srli $r17,$r1,#0x1
    68f2:	51 01 7f ff 	addi $r16,$r2,#-1
    68f6:	89 91       	add45 $r16,$r17
    68f8:	40 28 08 77 	divr $r2,$r3,$r16,$r2
    68fc:	50 20 ff dc 	addi $r2,$r1,#-36
    6900:	8b 83       	sub45 $r16,$r3
    6902:	e2 50       	slt45 $r2,$r16
    6904:	41 01 3c 1b 	cmovn $r16,$r2,$r15
    6908:	f1 14       	lwi37.sp $r1,[+#0x50]
    690a:	e3 81       	slt45 $r16,$r1
    690c:	e8 40       	beqzs8 698c <lfs_dir_compact+0x104>
    690e:	90 c1       	srai45 $r6,#0x1
    6910:	88 c7       	add45 $r6,$r7
    6912:	40 e3 00 13 	zeh $r14,$r6
    6916:	15 cf 80 00 	swi $fp,[$sp+#0x0]
    691a:	fd 04       	movd44 $r0,$r8
    691c:	fd 15       	movd44 $r2,$r10
    691e:	80 8c       	mov55 $r4,$r12
    6920:	80 ae       	mov55 $r5,$r14
    6922:	49 00 09 0b 	jal 7b38 <lfs_dir_split>
    6926:	c8 28       	bnez38 $r0,6976 <lfs_dir_compact+0xee>
    6928:	40 67 1c 01 	sub $r6,$r14,$r7
    692c:	e4 c2       	sltsi45 $r6,#0x2
    692e:	e9 31       	bnezs8 6990 <lfs_dir_compact+0x108>
    6930:	83 8e       	mov55 $fp,$r14
    6932:	92 00       	nop16
    6934:	32 7f 80 00 	fssi $fs7,[$sp+#0x0]
    6938:	14 df 80 01 	swi $r13,[$sp+#0x4]
    693c:	f7 82       	swi37.sp $r7,[+#0x8]
    693e:	15 cf 80 03 	swi $fp,[$sp+#0xc]
    6942:	32 8f 80 04 	fssi $fs8,[$sp+#0x10]
    6946:	32 9f 80 05 	fssi $fs9,[$sp+#0x14]
    694a:	32 6f 80 06 	fssi $fs6,[$sp+#0x18]
    694e:	80 08       	mov55 $r0,$r8
    6950:	80 2c       	mov55 $r1,$r12
    6952:	84 40       	movi55 $r2,#0x0
    6954:	84 7f       	movi55 $r3,#-1
    6956:	fd 25       	movd44 $r4,$r10
    6958:	14 df 80 14 	swi $r13,[$sp+#0x50]
    695c:	49 ff f0 30 	jal 49bc <lfs_dir_traverse>
    6960:	c0 c0       	beqz38 $r0,68e0 <lfs_dir_compact+0x58>
    6962:	82 00       	mov55 $r16,$r0
    6964:	80 10       	mov55 $r0,$r16
    6966:	ec 70       	addi10.sp #0x70
    6968:	34 3f 90 02 	fldi.bi $fd3,[$sp],#0x8
    696c:	34 4f 90 03 	fldi.bi $fd4,[$sp],#0xc
    6970:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    6974:	dd 9e       	ret5 $lp
    6976:	82 00       	mov55 $r16,$r0
    6978:	5a 0f e4 f6 	bnec $r0,#-28,6964 <lfs_dir_compact+0xdc>
    697c:	04 04 00 1a 	lwi $r0,[$r8+#0x68]
    6980:	f2 14       	lwi37.sp $r2,[+#0x50]
    6982:	a0 47       	lwi333 $r1,[$r0+#0x1c]
    6984:	50 10 ff dc 	addi $r1,$r1,#-36
    6988:	e2 22       	slt45 $r1,$r2
    698a:	e9 ed       	bnezs8 6964 <lfs_dir_compact+0xdc>
    698c:	81 dc       	mov55 $r14,$fp
    698e:	d5 03       	j8 6994 <lfs_dir_compact+0x10c>
    6990:	04 04 00 1a 	lwi $r0,[$r8+#0x68]
    6994:	04 34 80 02 	lwi $r3,[$r9+#0x8]
    6998:	04 10 00 09 	lwi $r1,[$r0+#0x24]
    699c:	8c 61       	addi45 $r3,#0x1
    699e:	14 34 80 02 	swi $r3,[$r9+#0x8]
    69a2:	4e 17 00 3d 	blez $r1,6a1c <lfs_dir_compact+0x194>
    69a6:	9c 89       	addi333 $r2,$r1,#0x1
    69a8:	58 11 00 01 	ori $r1,$r2,#0x1
    69ac:	40 31 84 37 	divr $r3,$r1,$r3,$r1
    69b0:	c9 36       	bnez38 $r1,6a1c <lfs_dir_compact+0x194>
    69b2:	b4 09       	lwi450 $r0,[$r9]
    69b4:	c0 08       	beqz38 $r0,69c4 <lfs_dir_compact+0x13c>
    69b6:	04 14 80 01 	lwi $r1,[$r9+#0x4]
    69ba:	5a 00 01 05 	beqc $r0,#0x1,69c4 <lfs_dir_compact+0x13c>
    69be:	e6 22       	slti45 $r1,#0x2
    69c0:	4e f2 00 80 	beqz $r15,6ac0 <lfs_dir_compact+0x238>
    69c4:	80 08       	mov55 $r0,$r8
    69c6:	49 ff ff 4f 	jal 6864 <lfs_fs_size>
    69ca:	82 00       	mov55 $r16,$r0
    69cc:	4e 05 ff cc 	bltz $r0,6964 <lfs_dir_compact+0xdc>
    69d0:	04 04 00 1a 	lwi $r0,[$r8+#0x68]
    69d4:	87 80       	movi55 $fp,#0x0
    69d6:	04 10 00 08 	lwi $r1,[$r0+#0x20]
    69da:	92 21       	srli45 $r1,#0x1
    69dc:	e3 81       	slt45 $r16,$r1
    69de:	e8 20       	beqzs8 6a1e <lfs_dir_compact+0x196>
    69e0:	04 04 80 02 	lwi $r0,[$r9+#0x8]
    69e4:	44 10 36 cc 	movi $r1,#0x36cc
    69e8:	b6 3f       	swi450 $r1,[$sp]
    69ea:	f0 82       	swi37.sp $r0,[+#0x8]
    69ec:	44 10 06 00 	movi $r1,#0x600
    69f0:	44 00 01 38 	movi $r0,#0x138
    69f4:	f1 81       	swi37.sp $r1,[+#0x4]
    69f6:	f0 83       	swi37.sp $r0,[+#0xc]
    69f8:	44 00 3c 0c 	movi $r0,#0x3c0c
    69fc:	49 ff dd 1e 	jal 2438 <printf>
    6a00:	14 ef 80 00 	swi $r14,[$sp+#0x0]
    6a04:	fd 04       	movd44 $r0,$r8
    6a06:	fd 15       	movd44 $r2,$r10
    6a08:	80 8c       	mov55 $r4,$r12
    6a0a:	80 a7       	mov55 $r5,$r7
    6a0c:	49 00 08 96 	jal 7b38 <lfs_dir_split>
    6a10:	4e 03 01 1b 	bnez $r0,6c46 <lfs_dir_compact+0x3be>
    6a14:	04 04 00 1a 	lwi $r0,[$r8+#0x68]
    6a18:	81 c7       	mov55 $r14,$r7
    6a1a:	d5 02       	j8 6a1e <lfs_dir_compact+0x196>
    6a1c:	87 80       	movi55 $fp,#0x0
    6a1e:	b0 54       	addri36.sp $r1,#0x50
    6a20:	6a 13 00 09 	fmtsr $r1,$fs6
    6a24:	84 40       	movi55 $r2,#0x0
    6a26:	84 7f       	movi55 $r3,#-1
    6a28:	04 14 80 01 	lwi $r1,[$r9+#0x4]
    6a2c:	6a 43 00 01 	fmfsr $r4,$fs6
    6a30:	f1 94       	swi37.sp $r1,[+#0x50]
    6a32:	a8 a1       	swi333 $r2,[$r4+#0x4]
    6a34:	a8 e2       	swi333 $r3,[$r4+#0x8]
    6a36:	a8 e3       	swi333 $r3,[$r4+#0xc]
    6a38:	a8 a4       	swi333 $r2,[$r4+#0x10]
    6a3a:	a0 87       	lwi333 $r2,[$r0+#0x1c]
    6a3c:	8e 48       	subi45 $r2,#0x8
    6a3e:	a8 a5       	swi333 $r2,[$r4+#0x14]
    6a40:	49 ff f1 08 	jal 4c50 <lfs_bd_erase.isra.16>
    6a44:	4e 02 00 44 	beqz $r0,6acc <lfs_dir_compact+0x244>
    6a48:	5a 07 ac 04 	beqc $r0,#-84,6a50 <lfs_dir_compact+0x1c8>
    6a4c:	48 ff ff 8b 	j 6962 <lfs_dir_compact+0xda>
    6a50:	84 1f       	movi55 $r0,#-1
    6a52:	14 04 00 04 	swi $r0,[$r8+#0x10]
    6a56:	04 04 80 01 	lwi $r0,[$r9+#0x4]
    6a5a:	44 10 36 cc 	movi $r1,#0x36cc
    6a5e:	b6 3f       	swi450 $r1,[$sp]
    6a60:	f0 82       	swi37.sp $r0,[+#0x8]
    6a62:	44 10 06 95 	movi $r1,#0x695
    6a66:	44 00 01 38 	movi $r0,#0x138
    6a6a:	f0 83       	swi37.sp $r0,[+#0xc]
    6a6c:	f1 81       	swi37.sp $r1,[+#0x4]
    6a6e:	44 00 3b a0 	movi $r0,#0x3ba0
    6a72:	49 ff dc e3 	jal 2438 <printf>
    6a76:	84 c0       	movi55 $r6,#0x0
    6a78:	b4 09       	lwi450 $r0,[$r9]
    6a7a:	04 14 80 01 	lwi $r1,[$r9+#0x4]
    6a7e:	c0 0f       	beqz38 $r0,6a9c <lfs_dir_compact+0x214>
    6a80:	5a 00 01 0e 	beqc $r0,#0x1,6a9c <lfs_dir_compact+0x214>
    6a84:	e6 22       	slti45 $r1,#0x2
    6a86:	e9 0b       	bnezs8 6a9c <lfs_dir_compact+0x214>
    6a88:	80 08       	mov55 $r0,$r8
    6a8a:	50 14 80 04 	addi $r1,$r9,#0x4
    6a8e:	49 ff f9 99 	jal 5dc0 <lfs_alloc>
    6a92:	c8 2c       	bnez38 $r0,6aea <lfs_dir_compact+0x262>
    6a94:	04 04 00 1a 	lwi $r0,[$r8+#0x68]
    6a98:	87 81       	movi55 $fp,#0x1
    6a9a:	d5 c2       	j8 6a1e <lfs_dir_compact+0x196>
    6a9c:	44 00 36 cc 	movi $r0,#0x36cc
    6aa0:	b6 1f       	swi450 $r0,[$sp]
    6aa2:	44 00 06 9b 	movi $r0,#0x69b
    6aa6:	f0 81       	swi37.sp $r0,[+#0x4]
    6aa8:	44 00 01 38 	movi $r0,#0x138
    6aac:	f0 83       	swi37.sp $r0,[+#0xc]
    6aae:	f1 82       	swi37.sp $r1,[+#0x8]
    6ab0:	44 00 3c e4 	movi $r0,#0x3ce4
    6ab4:	49 ff dc c2 	jal 2438 <printf>
    6ab8:	45 0f ff e4 	movi $r16,#-28
    6abc:	48 ff ff 54 	j 6964 <lfs_dir_compact+0xdc>
    6ac0:	84 1f       	movi55 $r0,#-1
    6ac2:	14 04 00 04 	swi $r0,[$r8+#0x10]
    6ac6:	84 c1       	movi55 $r6,#0x1
    6ac8:	d5 d8       	j8 6a78 <lfs_dir_compact+0x1f0>
    6aca:	92 00       	nop16
    6acc:	6a 13 00 01 	fmfsr $r1,$fs6
    6ad0:	80 08       	mov55 $r0,$r8
    6ad2:	50 24 80 08 	addi $r2,$r9,#0x8
    6ad6:	84 64       	movi55 $r3,#0x4
    6ad8:	49 ff f2 ce 	jal 5074 <lfs_dir_commitprog>
    6adc:	82 00       	mov55 $r16,$r0
    6ade:	c0 0e       	beqz38 $r0,6afa <lfs_dir_compact+0x272>
    6ae0:	5a 07 ac 04 	beqc $r0,#-84,6ae8 <lfs_dir_compact+0x260>
    6ae4:	48 ff ff 40 	j 6964 <lfs_dir_compact+0xdc>
    6ae8:	d5 b4       	j8 6a50 <lfs_dir_compact+0x1c8>
    6aea:	82 00       	mov55 $r16,$r0
    6aec:	5a 07 e4 04 	beqc $r0,#-28,6af4 <lfs_dir_compact+0x26c>
    6af0:	48 ff ff 3a 	j 6964 <lfs_dir_compact+0xdc>
    6af4:	ce d0       	bnez38 $r6,6a94 <lfs_dir_compact+0x20c>
    6af6:	48 ff ff 37 	j 6964 <lfs_dir_compact+0xdc>
    6afa:	fe 3a       	neg33 $r0,$r7
    6afc:	96 03       	seh33 $r0,$r0
    6afe:	46 14 00 ff 	sethi $r1,#0x400ff
    6b02:	50 10 8c 00 	addi $r1,$r1,#0xc00
    6b06:	51 1f 80 28 	addi $r17,$sp,#0x28
    6b0a:	f0 84       	swi37.sp $r0,[+#0x10]
    6b0c:	44 00 51 70 	movi $r0,#0x5170
    6b10:	b6 3f       	swi450 $r1,[$sp]
    6b12:	f0 85       	swi37.sp $r0,[+#0x14]
    6b14:	15 0f 80 01 	swi $r16,[$sp+#0x4]
    6b18:	f7 82       	swi37.sp $r7,[+#0x8]
    6b1a:	14 ef 80 03 	swi $r14,[$sp+#0xc]
    6b1e:	15 1f 80 06 	swi $r17,[$sp+#0x18]
    6b22:	80 08       	mov55 $r0,$r8
    6b24:	80 2c       	mov55 $r1,$r12
    6b26:	84 40       	movi55 $r2,#0x0
    6b28:	84 7f       	movi55 $r3,#-1
    6b2a:	fd 25       	movd44 $r4,$r10
    6b2c:	14 8f 80 0a 	swi $r8,[$sp+#0x28]
    6b30:	32 6f 80 0b 	fssi $fs6,[$sp+#0x2c]
    6b34:	49 ff ef 44 	jal 49bc <lfs_dir_traverse>
    6b38:	4e 03 ff 88 	bnez $r0,6a48 <lfs_dir_compact+0x1c0>
    6b3c:	04 04 80 06 	lwi $r0,[$r9+#0x18]
    6b40:	5a 07 ff 1a 	beqc $r0,#-1,6b74 <lfs_dir_compact+0x2ec>
    6b44:	04 04 80 07 	lwi $r0,[$r9+#0x1c]
    6b48:	5a 07 ff 16 	beqc $r0,#-1,6b74 <lfs_dir_compact+0x2ec>
    6b4c:	00 24 80 17 	lbi $r2,[$r9+#0x17]
    6b50:	46 30 00 ff 	sethi $r3,#0xff
    6b54:	50 21 06 00 	addi $r2,$r2,#0x600
    6b58:	50 31 8c 08 	addi $r3,$r3,#0xc08
    6b5c:	40 21 50 08 	slli $r2,$r2,#0x14
    6b60:	6a 13 00 01 	fmfsr $r1,$fs6
    6b64:	fe 9f       	or33 $r2,$r3
    6b66:	80 08       	mov55 $r0,$r8
    6b68:	50 34 80 18 	addi $r3,$r9,#0x18
    6b6c:	49 ff f2 a4 	jal 50b4 <lfs_dir_commitattr>
    6b70:	4e 03 ff 6c 	bnez $r0,6a48 <lfs_dir_compact+0x1c0>
    6b74:	b0 10       	addri36.sp $r0,#0x40
    6b76:	84 20       	movi55 $r1,#0x0
    6b78:	44 20 00 0c 	movi $r2,#0xc
    6b7c:	49 00 1a 1c 	jal 9fb4 <memset>
    6b80:	4f c2 00 6c 	beqz $fp,6c58 <lfs_dir_compact+0x3d0>
    6b84:	84 20       	movi55 $r1,#0x0
    6b86:	84 40       	movi55 $r2,#0x0
    6b88:	44 30 00 00 	movi $r3,#0x0
    6b8c:	04 04 00 12 	lwi $r0,[$r8+#0x48]
    6b90:	04 54 00 13 	lwi $r5,[$r8+#0x4c]
    6b94:	04 44 00 14 	lwi $r4,[$r8+#0x50]
    6b98:	fe 1d       	xor33 $r0,$r3
    6b9a:	ff 55       	xor33 $r5,$r2
    6b9c:	ff 0d       	xor33 $r4,$r1
    6b9e:	66 30 03 ff 	bitci $r3,$r0,#0x3ff
    6ba2:	80 29       	mov55 $r1,$r9
    6ba4:	80 08       	mov55 $r0,$r8
    6ba6:	b0 90       	addri36.sp $r2,#0x40
    6ba8:	f5 91       	swi37.sp $r5,[+#0x44]
    6baa:	f4 92       	swi37.sp $r4,[+#0x48]
    6bac:	14 3f 80 10 	swi $r3,[$sp+#0x40]
    6bb0:	49 ff f5 22 	jal 55f4 <lfs_dir_getgstate>
    6bb4:	4e 03 fe d7 	bnez $r0,6962 <lfs_dir_compact+0xda>
    6bb8:	f0 10       	lwi37.sp $r0,[+#0x40]
    6bba:	4e 03 01 6d 	bnez $r0,6e94 <lfs_dir_compact+0x60c>
    6bbe:	f0 11       	lwi37.sp $r0,[+#0x44]
    6bc0:	4e 03 01 6a 	bnez $r0,6e94 <lfs_dir_compact+0x60c>
    6bc4:	f0 12       	lwi37.sp $r0,[+#0x48]
    6bc6:	4e 03 01 67 	bnez $r0,6e94 <lfs_dir_compact+0x60c>
    6bca:	92 00       	nop16
    6bcc:	6a 13 00 01 	fmfsr $r1,$fs6
    6bd0:	50 04 00 00 	addi $r0,$r8,#0x0
    6bd4:	49 ff f2 d4 	jal 517c <lfs_dir_commitcrc>
    6bd8:	4e 03 ff 38 	bnez $r0,6a48 <lfs_dir_compact+0x1c0>
    6bdc:	04 14 00 1a 	lwi $r1,[$r8+#0x68]
    6be0:	6a 03 00 01 	fmfsr $r0,$fs6
    6be4:	a0 4e       	lwi333 $r1,[$r1+#0x18]
    6be6:	a0 01       	lwi333 $r0,[$r0+#0x4]
    6be8:	40 10 04 d7 	divr $r1,$r6,$r0,$r1
    6bec:	81 66       	mov55 $r11,$r6
    6bee:	4e 63 01 61 	bnez $r6,6eb0 <lfs_dir_compact+0x628>
    6bf2:	6a 13 00 01 	fmfsr $r1,$fs6
    6bf6:	b5 49       	lwi450 $r10,[$r9]
    6bf8:	04 64 80 01 	lwi $r6,[$r9+#0x4]
    6bfc:	a0 4a       	lwi333 $r1,[$r1+#0x8]
    6bfe:	40 77 1c 01 	sub $r7,$r14,$r7
    6c02:	14 04 80 03 	swi $r0,[$r9+#0xc]
    6c06:	14 14 80 04 	swi $r1,[$r9+#0x10]
    6c0a:	b6 c9       	swi450 $r6,[$r9]
    6c0c:	14 a4 80 01 	swi $r10,[$r9+#0x4]
    6c10:	12 74 80 0a 	shi $r7,[$r9+#0x14]
    6c14:	50 04 00 48 	addi $r0,$r8,#0x48
    6c18:	84 20       	movi55 $r1,#0x0
    6c1a:	84 4c       	movi55 $r2,#0xc
    6c1c:	49 00 19 cc 	jal 9fb4 <memset>
    6c20:	4f c3 00 2e 	bnez $fp,6c7c <lfs_dir_compact+0x3f4>
    6c24:	50 04 00 30 	addi $r0,$r8,#0x30
    6c28:	3b 00 48 00 	lmw.bi $r16,[$r0],$r18,#0x0    ! {$r16~$r18}
    6c2c:	50 84 00 3c 	addi $r8,$r8,#0x3c
    6c30:	3b 04 48 20 	smw.bi $r16,[$r8],$r18,#0x0    ! {$r16~$r18}
    6c34:	86 00       	movi55 $r16,#0x0
    6c36:	48 ff fe 97 	j 6964 <lfs_dir_compact+0xdc>
    6c3a:	92 00       	nop16
    6c3c:	04 00 00 1a 	lwi $r0,[$r0+#0x68]
    6c40:	81 dc       	mov55 $r14,$fp
    6c42:	48 ff fe a9 	j 6994 <lfs_dir_compact+0x10c>
    6c46:	82 00       	mov55 $r16,$r0
    6c48:	5a 07 e4 04 	beqc $r0,#-28,6c50 <lfs_dir_compact+0x3c8>
    6c4c:	48 ff fe 8c 	j 6964 <lfs_dir_compact+0xdc>
    6c50:	04 04 00 1a 	lwi $r0,[$r8+#0x68]
    6c54:	48 ff fe e5 	j 6a1e <lfs_dir_compact+0x196>
    6c58:	04 34 00 0c 	lwi $r3,[$r8+#0x30]
    6c5c:	04 04 00 0f 	lwi $r0,[$r8+#0x3c]
    6c60:	04 54 00 0d 	lwi $r5,[$r8+#0x34]
    6c64:	04 24 00 10 	lwi $r2,[$r8+#0x40]
    6c68:	04 44 00 0e 	lwi $r4,[$r8+#0x38]
    6c6c:	04 14 00 11 	lwi $r1,[$r8+#0x44]
    6c70:	fe c5       	xor33 $r3,$r0
    6c72:	fe ad       	xor33 $r2,$r5
    6c74:	fe 65       	xor33 $r1,$r4
    6c76:	48 ff ff 8b 	j 6b8c <lfs_dir_compact+0x304>
    6c7a:	92 00       	nop16
    6c7c:	44 10 06 ad 	movi $r1,#0x6ad
    6c80:	f0 09       	lwi37.sp $r0,[+#0x24]
    6c82:	f1 81       	swi37.sp $r1,[+#0x4]
    6c84:	44 e0 36 cc 	movi $r14,#0x36cc
    6c88:	f1 08       	lwi37.sp $r1,[+#0x20]
    6c8a:	44 c0 01 38 	movi $r12,#0x138
    6c8e:	f1 82       	swi37.sp $r1,[+#0x8]
    6c90:	f0 83       	swi37.sp $r0,[+#0xc]
    6c92:	14 ef 80 00 	swi $r14,[$sp+#0x0]
    6c96:	f6 84       	swi37.sp $r6,[+#0x10]
    6c98:	14 af 80 05 	swi $r10,[$sp+#0x14]
    6c9c:	14 cf 80 06 	swi $r12,[$sp+#0x18]
    6ca0:	44 00 3c a8 	movi $r0,#0x3ca8
    6ca4:	49 ff db ca 	jal 2438 <printf>
    6ca8:	f5 08       	lwi37.sp $r5,[+#0x20]
    6caa:	04 04 00 08 	lwi $r0,[$r8+#0x20]
    6cae:	4c 50 00 80 	beq $r5,$r0,6dae <lfs_dir_compact+0x526>
    6cb2:	f2 09       	lwi37.sp $r2,[+#0x24]
    6cb4:	04 34 00 09 	lwi $r3,[$r8+#0x24]
    6cb8:	4c 21 80 7b 	beq $r2,$r3,6dae <lfs_dir_compact+0x526>
    6cbc:	4c 51 80 79 	beq $r5,$r3,6dae <lfs_dir_compact+0x526>
    6cc0:	4c 01 00 77 	beq $r0,$r2,6dae <lfs_dir_compact+0x526>
    6cc4:	04 04 00 0a 	lwi $r0,[$r8+#0x28]
    6cc8:	f2 09       	lwi37.sp $r2,[+#0x24]
    6cca:	c8 0d       	bnez38 $r0,6ce4 <lfs_dir_compact+0x45c>
    6ccc:	d5 26       	j8 6d18 <lfs_dir_compact+0x490>
    6cce:	a1 03       	lwi333 $r4,[$r0+#0xc]
    6cd0:	4c 22 00 0c 	beq $r2,$r4,6ce8 <lfs_dir_compact+0x460>
    6cd4:	d4 0a       	beqs38 $r4,6ce8 <lfs_dir_compact+0x460>
    6cd6:	4c 31 00 09 	beq $r3,$r2,6ce8 <lfs_dir_compact+0x460>
    6cda:	a6 c6       	lbi333 $r3,[$r0+#0x6]
    6cdc:	5a 30 02 0c 	beqc $r3,#0x2,6cf4 <lfs_dir_compact+0x46c>
    6ce0:	b4 00       	lwi450 $r0,[$r0]
    6ce2:	c0 1b       	beqz38 $r0,6d18 <lfs_dir_compact+0x490>
    6ce4:	a0 c2       	lwi333 $r3,[$r0+#0x8]
    6ce6:	db f4       	bnes38 $r3,6cce <lfs_dir_compact+0x446>
    6ce8:	b4 69       	lwi450 $r3,[$r9]
    6cea:	a8 c2       	swi333 $r3,[$r0+#0x8]
    6cec:	04 34 80 01 	lwi $r3,[$r9+#0x4]
    6cf0:	a8 c3       	swi333 $r3,[$r0+#0xc]
    6cf2:	d5 f4       	j8 6cda <lfs_dir_compact+0x452>
    6cf4:	04 30 00 0b 	lwi $r3,[$r0+#0x2c]
    6cf8:	d3 08       	beqs38 $r3,6d08 <lfs_dir_compact+0x480>
    6cfa:	04 40 00 0c 	lwi $r4,[$r0+#0x30]
    6cfe:	4c 22 00 05 	beq $r2,$r4,6d08 <lfs_dir_compact+0x480>
    6d02:	d4 03       	beqs38 $r4,6d08 <lfs_dir_compact+0x480>
    6d04:	4c 21 ff ee 	bne $r2,$r3,6ce0 <lfs_dir_compact+0x458>
    6d08:	b4 69       	lwi450 $r3,[$r9]
    6d0a:	14 30 00 0b 	swi $r3,[$r0+#0x2c]
    6d0e:	04 34 80 01 	lwi $r3,[$r9+#0x4]
    6d12:	14 30 00 0c 	swi $r3,[$r0+#0x30]
    6d16:	d5 e5       	j8 6ce0 <lfs_dir_compact+0x458>
    6d18:	6a 23 00 01 	fmfsr $r2,$fs6
    6d1c:	80 08       	mov55 $r0,$r8
    6d1e:	b0 48       	addri36.sp $r1,#0x20
    6d20:	49 ff ed c2 	jal 48a4 <lfs_fs_parent>
    6d24:	80 c0       	mov55 $r6,$r0
    6d26:	4e 05 00 4d 	bltz $r0,6dc0 <lfs_dir_compact+0x538>
    6d2a:	51 c4 00 30 	addi $fp,$r8,#0x30
    6d2e:	84 21       	movi55 $r1,#0x1
    6d30:	50 0e 00 00 	addi $r0,$fp,#0x0
    6d34:	49 ff ef 6e 	jal 4c10 <lfs_fs_preporphans.isra.14>
    6d38:	04 14 00 0c 	lwi $r1,[$r8+#0x30]
    6d3c:	80 86       	mov55 $r4,$r6
    6d3e:	40 50 d0 09 	srli $r5,$r1,#0x14
    6d42:	54 52 87 00 	andi $r5,$r5,#0x700
    6d46:	c5 11       	beqz38 $r5,6d68 <lfs_dir_compact+0x4e0>
    6d48:	04 54 00 0d 	lwi $r5,[$r8+#0x34]
    6d4c:	f2 14       	lwi37.sp $r2,[+#0x50]
    6d4e:	4c 51 00 bd 	beq $r5,$r2,6ec8 <lfs_dir_compact+0x640>
    6d52:	04 34 00 0e 	lwi $r3,[$r8+#0x38]
    6d56:	f0 15       	lwi37.sp $r0,[+#0x54]
    6d58:	4c 30 00 bc 	beq $r3,$r0,6ed0 <lfs_dir_compact+0x648>
    6d5c:	4c 50 00 ba 	beq $r5,$r0,6ed0 <lfs_dir_compact+0x648>
    6d60:	4c 21 80 b8 	beq $r2,$r3,6ed0 <lfs_dir_compact+0x648>
    6d64:	80 86       	mov55 $r4,$r6
    6d66:	84 a0       	movi55 $r5,#0x0
    6d68:	f5 90       	swi37.sp $r5,[+#0x40]
    6d6a:	b0 90       	addri36.sp $r2,#0x40
    6d6c:	84 a0       	movi55 $r5,#0x0
    6d6e:	6a 13 00 01 	fmfsr $r1,$fs6
    6d72:	80 08       	mov55 $r0,$r8
    6d74:	84 62       	movi55 $r3,#0x2
    6d76:	a9 51       	swi333 $r5,[$r2+#0x4]
    6d78:	a9 12       	swi333 $r4,[$r2+#0x8]
    6d7a:	14 91 00 03 	swi $r9,[$r2+#0xc]
    6d7e:	49 00 00 e7 	jal 6f4c <lfs_dir_commit>
    6d82:	82 00       	mov55 $r16,$r0
    6d84:	4e 03 fd f0 	bnez $r0,6964 <lfs_dir_compact+0xdc>
    6d88:	80 1c       	mov55 $r0,$fp
    6d8a:	84 3f       	movi55 $r1,#-1
    6d8c:	49 ff ef 42 	jal 4c10 <lfs_fs_preporphans.isra.14>
    6d90:	6a 23 00 01 	fmfsr $r2,$fs6
    6d94:	80 08       	mov55 $r0,$r8
    6d96:	b0 48       	addri36.sp $r1,#0x20
    6d98:	49 ff ed cc 	jal 4930 <lfs_fs_pred>
    6d9c:	c0 1a       	beqz38 $r0,6dd0 <lfs_dir_compact+0x548>
    6d9e:	82 00       	mov55 $r16,$r0
    6da0:	5a 07 fe 04 	beqc $r0,#-2,6da8 <lfs_dir_compact+0x520>
    6da4:	48 ff fd e0 	j 6964 <lfs_dir_compact+0xdc>
    6da8:	86 00       	movi55 $r16,#0x0
    6daa:	48 ff fd dd 	j 6964 <lfs_dir_compact+0xdc>
    6dae:	b4 09       	lwi450 $r0,[$r9]
    6db0:	14 04 00 08 	swi $r0,[$r8+#0x20]
    6db4:	04 04 80 01 	lwi $r0,[$r9+#0x4]
    6db8:	14 04 00 09 	swi $r0,[$r8+#0x24]
    6dbc:	48 ff ff 84 	j 6cc4 <lfs_dir_compact+0x43c>
    6dc0:	51 00 00 00 	addi $r16,$r0,#0x0
    6dc4:	5a 07 fe 04 	beqc $r0,#-2,6dcc <lfs_dir_compact+0x544>
    6dc8:	48 ff fd ce 	j 6964 <lfs_dir_compact+0xdc>
    6dcc:	d5 e2       	j8 6d90 <lfs_dir_compact+0x508>
    6dce:	92 00       	nop16
    6dd0:	04 04 00 0c 	lwi $r0,[$r8+#0x30]
    6dd4:	40 10 50 09 	srli $r1,$r0,#0x14
    6dd8:	54 10 87 00 	andi $r1,$r1,#0x700
    6ddc:	c1 0e       	beqz38 $r1,6df8 <lfs_dir_compact+0x570>
    6dde:	04 54 00 0d 	lwi $r5,[$r8+#0x34]
    6de2:	f2 14       	lwi37.sp $r2,[+#0x50]
    6de4:	d2 2a       	beqs38 $r2,6e38 <lfs_dir_compact+0x5b0>
    6de6:	04 34 00 0e 	lwi $r3,[$r8+#0x38]
    6dea:	f1 15       	lwi37.sp $r1,[+#0x54]
    6dec:	4c 30 80 2a 	beq $r3,$r1,6e40 <lfs_dir_compact+0x5b8>
    6df0:	d1 28       	beqs38 $r1,6e40 <lfs_dir_compact+0x5b8>
    6df2:	4c 21 80 27 	beq $r2,$r3,6e40 <lfs_dir_compact+0x5b8>
    6df6:	92 00       	nop16
    6df8:	6a 03 00 01 	fmfsr $r0,$fs6
    6dfc:	b0 8c       	addri36.sp $r2,#0x30
    6dfe:	00 40 00 17 	lbi $r4,[$r0+#0x17]
    6e02:	46 00 00 ff 	sethi $r0,#0xff
    6e06:	50 42 06 00 	addi $r4,$r4,#0x600
    6e0a:	50 00 0c 08 	addi $r0,$r0,#0xc08
    6e0e:	40 42 50 08 	slli $r4,$r4,#0x14
    6e12:	ff 07       	or33 $r4,$r0
    6e14:	84 a0       	movi55 $r5,#0x0
    6e16:	6a 13 00 01 	fmfsr $r1,$fs6
    6e1a:	80 08       	mov55 $r0,$r8
    6e1c:	84 62       	movi55 $r3,#0x2
    6e1e:	a9 51       	swi333 $r5,[$r2+#0x4]
    6e20:	a9 12       	swi333 $r4,[$r2+#0x8]
    6e22:	14 91 00 03 	swi $r9,[$r2+#0xc]
    6e26:	14 bf 80 0c 	swi $r11,[$sp+#0x30]
    6e2a:	49 00 00 91 	jal 6f4c <lfs_dir_commit>
    6e2e:	82 00       	mov55 $r16,$r0
    6e30:	4e 03 fd 9a 	bnez $r0,6964 <lfs_dir_compact+0xdc>
    6e34:	d5 ba       	j8 6da8 <lfs_dir_compact+0x520>
    6e36:	92 00       	nop16
    6e38:	6a 13 00 01 	fmfsr $r1,$fs6
    6e3c:	04 10 80 01 	lwi $r1,[$r1+#0x4]
    6e40:	40 00 30 08 	slli $r0,$r0,#0xc
    6e44:	40 60 58 09 	srli $r6,$r0,#0x16
    6e48:	44 00 0f ef 	movi $r0,#0xfef
    6e4c:	f0 81       	swi37.sp $r0,[+#0x4]
    6e4e:	f2 82       	swi37.sp $r2,[+#0x8]
    6e50:	f1 83       	swi37.sp $r1,[+#0xc]
    6e52:	14 ef 80 00 	swi $r14,[$sp+#0x0]
    6e56:	f6 84       	swi37.sp $r6,[+#0x10]
    6e58:	14 cf 80 05 	swi $r12,[$sp+#0x14]
    6e5c:	44 00 3c 64 	movi $r0,#0x3c64
    6e60:	49 ff da ec 	jal 2438 <printf>
    6e64:	04 24 00 0c 	lwi $r2,[$r8+#0x30]
    6e68:	46 08 00 00 	sethi $r0,#0x80000
    6e6c:	50 00 03 ff 	addi $r0,$r0,#0x3ff
    6e70:	84 20       	movi55 $r1,#0x0
    6e72:	fe 16       	and33 $r0,$r2
    6e74:	14 04 00 0c 	swi $r0,[$r8+#0x30]
    6e78:	14 14 00 0d 	swi $r1,[$r8+#0x34]
    6e7c:	14 14 00 0e 	swi $r1,[$r8+#0x38]
    6e80:	5a 63 ff bc 	beqc $r6,#0x3ff,6df8 <lfs_dir_compact+0x570>
    6e84:	40 63 28 08 	slli $r6,$r6,#0xa
    6e88:	46 b4 ff 00 	sethi $r11,#0x4ff00
    6e8c:	40 b3 2c 04 	or $r11,$r6,$r11
    6e90:	d5 b4       	j8 6df8 <lfs_dir_compact+0x570>
    6e92:	92 00       	nop16
    6e94:	46 27 ff ff 	sethi $r2,#0x7ffff
    6e98:	6a 13 00 01 	fmfsr $r1,$fs6
    6e9c:	80 08       	mov55 $r0,$r8
    6e9e:	50 21 0c 0c 	addi $r2,$r2,#0xc0c
    6ea2:	b0 d0       	addri36.sp $r3,#0x40
    6ea4:	49 ff f1 08 	jal 50b4 <lfs_dir_commitattr>
    6ea8:	4e 03 fd d0 	bnez $r0,6a48 <lfs_dir_compact+0x1c0>
    6eac:	48 ff fe 90 	j 6bcc <lfs_dir_compact+0x344>
    6eb0:	44 00 36 cc 	movi $r0,#0x36cc
    6eb4:	44 10 06 83 	movi $r1,#0x683
    6eb8:	44 20 7c 2c 	movi $r2,#0x7c2c
    6ebc:	44 30 3c 3c 	movi $r3,#0x3c3c
    6ec0:	49 00 16 aa 	jal 9c14 <__assert_func>
    6ec4:	92 00       	nop16
    6ec6:	92 00       	nop16
    6ec8:	6a 03 00 01 	fmfsr $r0,$fs6
    6ecc:	04 00 00 01 	lwi $r0,[$r0+#0x4]
    6ed0:	46 70 00 ff 	sethi $r7,#0xff
    6ed4:	50 73 8c 00 	addi $r7,$r7,#0xc00
    6ed8:	fe 7e       	and33 $r1,$r7
    6eda:	40 a0 a8 09 	srli $r10,$r1,#0xa
    6ede:	44 10 0f cb 	movi $r1,#0xfcb
    6ee2:	f1 81       	swi37.sp $r1,[+#0x4]
    6ee4:	f2 82       	swi37.sp $r2,[+#0x8]
    6ee6:	f0 83       	swi37.sp $r0,[+#0xc]
    6ee8:	14 ef 80 00 	swi $r14,[$sp+#0x0]
    6eec:	14 af 80 04 	swi $r10,[$sp+#0x10]
    6ef0:	14 cf 80 05 	swi $r12,[$sp+#0x14]
    6ef4:	44 00 3c 64 	movi $r0,#0x3c64
    6ef8:	49 ff da a0 	jal 2438 <printf>
    6efc:	40 13 1c 02 	and $r1,$r6,$r7
    6f00:	04 54 00 0c 	lwi $r5,[$r8+#0x30]
    6f04:	92 2a       	srli45 $r1,#0xa
    6f06:	46 28 00 00 	sethi $r2,#0x80000
    6f0a:	40 05 00 13 	zeh $r0,$r10
    6f0e:	96 49       	zeh33 $r1,$r1
    6f10:	50 21 03 ff 	addi $r2,$r2,#0x3ff
    6f14:	84 60       	movi55 $r3,#0x0
    6f16:	fe ae       	and33 $r2,$r5
    6f18:	40 10 04 06 	slt $r1,$r0,$r1
    6f1c:	80 86       	mov55 $r4,$r6
    6f1e:	14 24 00 0c 	swi $r2,[$r8+#0x30]
    6f22:	14 34 00 0d 	swi $r3,[$r8+#0x34]
    6f26:	14 34 00 0e 	swi $r3,[$r8+#0x38]
    6f2a:	c1 0b       	beqz38 $r1,6f40 <lfs_dir_compact+0x6b8>
    6f2c:	50 43 7c 00 	addi $r4,$r6,#-1024
    6f30:	40 a5 28 08 	slli $r10,$r10,#0xa
    6f34:	46 54 ff 00 	sethi $r5,#0x4ff00
    6f38:	40 55 14 04 	or $r5,$r10,$r5
    6f3c:	48 ff ff 16 	j 6d68 <lfs_dir_compact+0x4e0>
    6f40:	84 a0       	movi55 $r5,#0x0
    6f42:	5a 0b ff f7 	bnec $r0,#0x3ff,6f30 <lfs_dir_compact+0x6a8>
    6f46:	48 ff ff 11 	j 6d68 <lfs_dir_compact+0x4e0>
    6f4a:	92 00       	nop16

00006f4c <lfs_dir_commit>:
    6f4c:	3a 6f b4 bc 	smw.adm $r6,[$sp],$r13,#0x2    ! {$r6~$r13, $lp}
    6f50:	ef 84       	addi10.sp #-124
    6f52:	04 60 00 0a 	lwi $r6,[$r0+#0x28]
    6f56:	81 00       	mov55 $r8,$r0
    6f58:	80 e1       	mov55 $r7,$r1
    6f5a:	81 42       	mov55 $r10,$r2
    6f5c:	81 83       	mov55 $r12,$r3
    6f5e:	b5 21       	lwi450 $r9,[$r1]
    6f60:	46 b0 01 00 	sethi $r11,#0x100
    6f64:	ce 0c       	bnez38 $r6,6f7c <lfs_dir_commit+0x30>
    6f66:	d5 41       	j8 6fe8 <lfs_dir_commit+0x9c>
    6f68:	a1 73       	lwi333 $r5,[$r6+#0xc]
    6f6a:	a0 39       	lwi333 $r0,[$r7+#0x4]
    6f6c:	d0 0f       	beqs38 $r0,6f8a <lfs_dir_commit+0x3e>
    6f6e:	4c 10 00 0e 	beq $r1,$r0,6f8a <lfs_dir_commit+0x3e>
    6f72:	4c 92 80 0c 	beq $r9,$r5,6f8a <lfs_dir_commit+0x3e>
    6f76:	b4 c6       	lwi450 $r6,[$r6]
    6f78:	4e 62 00 38 	beqz $r6,6fe8 <lfs_dir_commit+0x9c>
    6f7c:	50 13 00 08 	addi $r1,$r6,#0x8
    6f80:	4c 70 bf fb 	beq $r7,$r1,6f76 <lfs_dir_commit+0x2a>
    6f84:	a0 72       	lwi333 $r1,[$r6+#0x8]
    6f86:	4c 90 ff f1 	bne $r9,$r1,6f68 <lfs_dir_commit+0x1c>
    6f8a:	a6 36       	lbi333 $r0,[$r6+#0x6]
    6f8c:	5a 08 01 f5 	bnec $r0,#0x1,6f76 <lfs_dir_commit+0x2a>
    6f90:	04 03 00 0c 	lwi $r0,[$r6+#0x30]
    6f94:	40 00 2c 02 	and $r0,$r0,$r11
    6f98:	c0 ef       	beqz38 $r0,6f76 <lfs_dir_commit+0x2a>
    6f9a:	04 14 00 1a 	lwi $r1,[$r8+#0x68]
    6f9e:	04 23 00 0b 	lwi $r2,[$r6+#0x2c]
    6fa2:	04 00 80 0a 	lwi $r0,[$r1+#0x28]
    6fa6:	e2 02       	slt45 $r0,$r2
    6fa8:	e8 e7       	beqzs8 6f76 <lfs_dir_commit+0x2a>
    6faa:	04 03 00 0d 	lwi $r0,[$r6+#0x34]
    6fae:	04 10 80 08 	lwi $r1,[$r1+#0x20]
    6fb2:	14 03 00 0f 	swi $r0,[$r6+#0x3c]
    6fb6:	14 14 00 18 	swi $r1,[$r8+#0x60]
    6fba:	80 08       	mov55 $r0,$r8
    6fbc:	50 13 00 00 	addi $r1,$r6,#0x0
    6fc0:	49 ff f7 e0 	jal 5f80 <lfs_file_relocate>
    6fc4:	4e 03 00 bc 	bnez $r0,713c <lfs_dir_commit+0x1f0>
    6fc8:	04 13 00 0c 	lwi $r1,[$r6+#0x30]
    6fcc:	80 08       	mov55 $r0,$r8
    6fce:	42 10 d0 09 	bclr $r1,$r1,#0x14
    6fd2:	14 13 00 0c 	swi $r1,[$r6+#0x30]
    6fd6:	80 26       	mov55 $r1,$r6
    6fd8:	49 ff fa b4 	jal 6540 <lfs_file_flush>
    6fdc:	4e 03 00 b0 	bnez $r0,713c <lfs_dir_commit+0x1f0>
    6fe0:	b4 c6       	lwi450 $r6,[$r6]
    6fe2:	b5 27       	lwi450 $r9,[$r7]
    6fe4:	ce cc       	bnez38 $r6,6f7c <lfs_dir_commit+0x30>
    6fe6:	92 00       	nop16
    6fe8:	3b 03 dc 00 	lmw.bi $r16,[$r7],$r23,#0x0    ! {$r16~$r23}
    6fec:	b1 8e       	addri36.sp $r6,#0x38
    6fee:	3b 03 5c 20 	smw.bi $r16,[$r6],$r23,#0x0    ! {$r16~$r23}
    6ff2:	81 71       	mov55 $r11,$r17
    6ff4:	4e c7 00 30 	blez $r12,7054 <lfs_dir_commit+0x108>
    6ff8:	82 0a       	mov55 $r16,$r10
    6ffa:	86 40       	movi55 $r18,#0x0
    6ffc:	85 e0       	movi55 $r15,#0x0
    6ffe:	46 37 ff 00 	sethi $r3,#0x7ff00
    7002:	44 20 04 01 	movi $r2,#0x401
    7006:	44 40 04 ff 	movi $r4,#0x4ff
    700a:	47 17 00 00 	sethi $r17,#0x70000
    700e:	44 50 06 00 	movi $r5,#0x600
    7012:	d5 0c       	j8 702a <lfs_dir_commit+0xde>
    7014:	4c 12 00 98 	beq $r1,$r4,7144 <lfs_dir_commit+0x1f8>
    7018:	40 09 c4 02 	and $r0,$r19,$r17
    701c:	92 14       	srli45 $r0,#0x14
    701e:	4c 02 80 9d 	beq $r0,$r5,7158 <lfs_dir_commit+0x20c>
    7022:	8d c1       	addi45 $r18,#0x1
    7024:	8d 88       	addi45 $r16,#0x8
    7026:	4d 26 00 11 	beq $r18,$r12,7048 <lfs_dir_commit+0xfc>
    702a:	b5 f0       	lwi450 $r19,[$r16]
    702c:	40 19 8c 02 	and $r1,$r19,$r3
    7030:	92 34       	srli45 $r1,#0x14
    7032:	4c 11 7f f1 	bne $r1,$r2,7014 <lfs_dir_commit+0xc8>
    7036:	02 03 80 0a 	lhi $r0,[$r7+#0x14]
    703a:	8d c1       	addi45 $r18,#0x1
    703c:	8c 01       	addi45 $r0,#0x1
    703e:	12 03 80 0a 	shi $r0,[$r7+#0x14]
    7042:	8d 88       	addi45 $r16,#0x8
    7044:	4d 26 7f f3 	bne $r18,$r12,702a <lfs_dir_commit+0xde>
    7048:	e8 06       	beqzs8 7054 <lfs_dir_commit+0x108>
    704a:	02 03 80 0a 	lhi $r0,[$r7+#0x14]
    704e:	4e 02 01 34 	beqz $r0,72b6 <lfs_dir_commit+0x36a>
    7052:	92 00       	nop16
    7054:	00 03 80 16 	lbi $r0,[$r7+#0x16]
    7058:	c8 07       	bnez38 $r0,7066 <lfs_dir_commit+0x11a>
    705a:	02 03 80 0a 	lhi $r0,[$r7+#0x14]
    705e:	5c f0 00 ff 	slti $r15,$r0,#0xff
    7062:	4e f3 00 89 	bnez $r15,7174 <lfs_dir_commit+0x228>
    7066:	b4 27       	lwi450 $r1,[$r7]
    7068:	a0 bb       	lwi333 $r2,[$r7+#0xc]
    706a:	04 04 00 1a 	lwi $r0,[$r8+#0x68]
    706e:	a0 fc       	lwi333 $r3,[$r7+#0x10]
    7070:	50 df 80 58 	addi $r13,$sp,#0x58
    7074:	f1 96       	swi37.sp $r1,[+#0x58]
    7076:	84 3f       	movi55 $r1,#-1
    7078:	14 16 80 03 	swi $r1,[$r13+#0xc]
    707c:	14 26 80 01 	swi $r2,[$r13+#0x4]
    7080:	14 36 80 02 	swi $r3,[$r13+#0x8]
    7084:	14 26 80 04 	swi $r2,[$r13+#0x10]
    7088:	05 00 00 07 	lwi $r16,[$r0+#0x1c]
    708c:	84 00       	movi55 $r0,#0x0
    708e:	b6 1f       	swi450 $r0,[$sp]
    7090:	f0 81       	swi37.sp $r0,[+#0x4]
    7092:	f0 82       	swi37.sp $r0,[+#0x8]
    7094:	f0 83       	swi37.sp $r0,[+#0xc]
    7096:	f0 84       	swi37.sp $r0,[+#0x10]
    7098:	51 1f 80 24 	addi $r17,$sp,#0x24
    709c:	44 00 51 70 	movi $r0,#0x5170
    70a0:	8f 88       	subi45 $r16,#0x8
    70a2:	f0 85       	swi37.sp $r0,[+#0x14]
    70a4:	15 1f 80 06 	swi $r17,[$sp+#0x18]
    70a8:	80 08       	mov55 $r0,$r8
    70aa:	80 27       	mov55 $r1,$r7
    70ac:	80 8a       	mov55 $r4,$r10
    70ae:	80 ac       	mov55 $r5,$r12
    70b0:	15 06 80 05 	swi $r16,[$r13+#0x14]
    70b4:	14 8f 80 09 	swi $r8,[$sp+#0x24]
    70b8:	14 df 80 0a 	swi $r13,[$sp+#0x28]
    70bc:	49 ff ec 80 	jal 49bc <lfs_dir_traverse>
    70c0:	c8 32       	bnez38 $r0,7124 <lfs_dir_commit+0x1d8>
    70c2:	84 20       	movi55 $r1,#0x0
    70c4:	84 4c       	movi55 $r2,#0xc
    70c6:	b0 0b       	addri36.sp $r0,#0x2c
    70c8:	49 00 17 76 	jal 9fb4 <memset>
    70cc:	04 24 00 0c 	lwi $r2,[$r8+#0x30]
    70d0:	04 54 00 0f 	lwi $r5,[$r8+#0x3c]
    70d4:	05 14 00 11 	lwi $r17,[$r8+#0x44]
    70d8:	04 14 00 0e 	lwi $r1,[$r8+#0x38]
    70dc:	04 04 00 12 	lwi $r0,[$r8+#0x48]
    70e0:	05 04 00 10 	lwi $r16,[$r8+#0x40]
    70e4:	04 34 00 0d 	lwi $r3,[$r8+#0x34]
    70e8:	ff 55       	xor33 $r5,$r2
    70ea:	04 44 00 13 	lwi $r4,[$r8+#0x4c]
    70ee:	04 24 00 14 	lwi $r2,[$r8+#0x50]
    70f2:	40 18 84 03 	xor $r1,$r17,$r1
    70f6:	fe 2d       	xor33 $r0,$r5
    70f8:	40 38 0c 03 	xor $r3,$r16,$r3
    70fc:	fe e5       	xor33 $r3,$r4
    70fe:	fe 55       	xor33 $r1,$r2
    7100:	66 00 03 ff 	bitci $r0,$r0,#0x3ff
    7104:	f3 8c       	swi37.sp $r3,[+#0x30]
    7106:	f1 8d       	swi37.sp $r1,[+#0x34]
    7108:	f0 8b       	swi37.sp $r0,[+#0x2c]
    710a:	4e 03 01 0d 	bnez $r0,7324 <lfs_dir_commit+0x3d8>
    710e:	4e 33 01 0b 	bnez $r3,7324 <lfs_dir_commit+0x3d8>
    7112:	4e 13 01 09 	bnez $r1,7324 <lfs_dir_commit+0x3d8>
    7116:	80 08       	mov55 $r0,$r8
    7118:	50 16 80 00 	addi $r1,$r13,#0x0
    711c:	49 ff f0 30 	jal 517c <lfs_dir_commitcrc>
    7120:	4e 02 00 d8 	beqz $r0,72d0 <lfs_dir_commit+0x384>
    7124:	5a 07 e4 26 	beqc $r0,#-28,7170 <lfs_dir_commit+0x224>
    7128:	5a 07 ac 24 	beqc $r0,#-84,7170 <lfs_dir_commit+0x224>
    712c:	14 9f 80 0e 	swi $r9,[$sp+#0x38]
    7130:	14 bf 80 0f 	swi $r11,[$sp+#0x3c]
    7134:	3b 03 5c 00 	lmw.bi $r16,[$r6],$r23,#0x0    ! {$r16~$r23}
    7138:	3b 03 dc 20 	smw.bi $r16,[$r7],$r23,#0x0    ! {$r16~$r23}
    713c:	ec 7c       	addi10.sp #0x7c
    713e:	3a 6f b4 84 	lmw.bim $r6,[$sp],$r13,#0x2    ! {$r6~$r13, $lp}
    7142:	dd 9e       	ret5 $lp
    7144:	02 03 80 0a 	lhi $r0,[$r7+#0x14]
    7148:	4e 02 01 04 	beqz $r0,7350 <lfs_dir_commit+0x404>
    714c:	8e 01       	subi45 $r0,#0x1
    714e:	12 03 80 0a 	shi $r0,[$r7+#0x14]
    7152:	85 e1       	movi55 $r15,#0x1
    7154:	48 ff ff 67 	j 7022 <lfs_dir_commit+0xd6>
    7158:	04 08 00 01 	lwi $r0,[$r16+#0x4]
    715c:	43 39 d0 0b 	btst $r19,$r19,#0x14
    7160:	b4 20       	lwi450 $r1,[$r0]
    7162:	a8 7e       	swi333 $r1,[$r7+#0x18]
    7164:	a0 01       	lwi333 $r0,[$r0+#0x4]
    7166:	a8 3f       	swi333 $r0,[$r7+#0x1c]
    7168:	11 33 80 17 	sbi $r19,[$r7+#0x17]
    716c:	48 ff ff 5b 	j 7022 <lfs_dir_commit+0xd6>
    7170:	02 03 80 0a 	lhi $r0,[$r7+#0x14]
    7174:	84 3f       	movi55 $r1,#-1
    7176:	14 14 00 04 	swi $r1,[$r8+#0x10]
    717a:	80 4a       	mov55 $r2,$r10
    717c:	b6 1f       	swi450 $r0,[$sp]
    717e:	80 27       	mov55 $r1,$r7
    7180:	80 08       	mov55 $r0,$r8
    7182:	80 6c       	mov55 $r3,$r12
    7184:	80 87       	mov55 $r4,$r7
    7186:	84 a0       	movi55 $r5,#0x0
    7188:	49 ff fb 80 	jal 6888 <lfs_dir_compact>
    718c:	c8 d0       	bnez38 $r0,712c <lfs_dir_commit+0x1e0>
    718e:	92 00       	nop16
    7190:	04 64 00 0a 	lwi $r6,[$r8+#0x28]
    7194:	80 06       	mov55 $r0,$r6
    7196:	c6 2b       	beqz38 $r6,71ec <lfs_dir_commit+0x2a0>
    7198:	47 80 00 ff 	sethi $r24,#0xff
    719c:	46 47 ff 00 	sethi $r4,#0x7ff00
    71a0:	44 30 04 ff 	movi $r3,#0x4ff
    71a4:	51 8c 0c 00 	addi $r24,$r24,#0xc00
    71a8:	87 3f       	movi55 $r25,#-1
    71aa:	44 50 04 01 	movi $r5,#0x401
    71ae:	92 00       	nop16
    71b0:	50 10 00 08 	addi $r1,$r0,#0x8
    71b4:	4c 70 80 0d 	beq $r7,$r1,71ce <lfs_dir_commit+0x282>
    71b8:	a0 82       	lwi333 $r2,[$r0+#0x8]
    71ba:	4c 24 80 1f 	beq $r2,$r9,71f8 <lfs_dir_commit+0x2ac>
    71be:	05 00 00 03 	lwi $r16,[$r0+#0xc]
    71c2:	4d 05 80 1b 	beq $r16,$r11,71f8 <lfs_dir_commit+0x2ac>
    71c6:	4c 25 80 19 	beq $r2,$r11,71f8 <lfs_dir_commit+0x2ac>
    71ca:	4d 04 80 17 	beq $r16,$r9,71f8 <lfs_dir_commit+0x2ac>
    71ce:	b4 00       	lwi450 $r0,[$r0]
    71d0:	c8 f0       	bnez38 $r0,71b0 <lfs_dir_commit+0x264>
    71d2:	84 e0       	movi55 $r7,#0x0
    71d4:	a0 32       	lwi333 $r0,[$r6+#0x8]
    71d6:	4c 04 80 53 	beq $r0,$r9,727c <lfs_dir_commit+0x330>
    71da:	a0 73       	lwi333 $r1,[$r6+#0xc]
    71dc:	4c 15 80 50 	beq $r1,$r11,727c <lfs_dir_commit+0x330>
    71e0:	4c 05 80 4e 	beq $r0,$r11,727c <lfs_dir_commit+0x330>
    71e4:	4c 14 80 4c 	beq $r1,$r9,727c <lfs_dir_commit+0x330>
    71e8:	b4 c6       	lwi450 $r6,[$r6]
    71ea:	ce f5       	bnez38 $r6,71d4 <lfs_dir_commit+0x288>
    71ec:	84 00       	movi55 $r0,#0x0
    71ee:	ec 7c       	addi10.sp #0x7c
    71f0:	3a 6f b4 84 	lmw.bim $r6,[$sp],$r13,#0x2    ! {$r6~$r13, $lp}
    71f4:	dd 9e       	ret5 $lp
    71f6:	92 00       	nop16
    71f8:	3b 03 dc 00 	lmw.bi $r16,[$r7],$r23,#0x0    ! {$r16~$r23}
    71fc:	3b 00 dc 20 	smw.bi $r16,[$r1],$r23,#0x0    ! {$r16~$r23}
    7200:	86 40       	movi55 $r18,#0x0
    7202:	4e c6 00 09 	bgtz $r12,7214 <lfs_dir_commit+0x2c8>
    7206:	d5 e4       	j8 71ce <lfs_dir_commit+0x282>
    7208:	4d 02 80 22 	beq $r16,$r5,724c <lfs_dir_commit+0x300>
    720c:	8d c1       	addi45 $r18,#0x1
    720e:	4d 26 3f e0 	beq $r18,$r12,71ce <lfs_dir_commit+0x282>
    7212:	92 00       	nop16
    7214:	38 15 4b 02 	lw $r1,[$r10+($r18<<#0x3)]
    7218:	41 00 90 02 	and $r16,$r1,$r4
    721c:	93 94       	srli45 $r16,#0x14
    721e:	4d 01 ff f5 	bne $r16,$r3,7208 <lfs_dir_commit+0x2bc>
    7222:	40 10 e0 02 	and $r1,$r1,$r24
    7226:	92 2a       	srli45 $r1,#0xa
    7228:	a4 82       	lhi333 $r2,[$r0+#0x4]
    722a:	96 49       	zeh33 $r1,$r1
    722c:	4c 20 80 22 	beq $r2,$r1,7270 <lfs_dir_commit+0x324>
    7230:	e2 22       	slt45 $r1,$r2
    7232:	e8 ed       	beqzs8 720c <lfs_dir_commit+0x2c0>
    7234:	a6 46       	lbi333 $r1,[$r0+#0x6]
    7236:	8e 41       	subi45 $r2,#0x1
    7238:	ac 82       	shi333 $r2,[$r0+#0x4]
    723a:	5a 18 02 e9 	bnec $r1,#0x2,720c <lfs_dir_commit+0x2c0>
    723e:	04 10 00 0a 	lwi $r1,[$r0+#0x28]
    7242:	8e 21       	subi45 $r1,#0x1
    7244:	14 10 00 0a 	swi $r1,[$r0+#0x28]
    7248:	d5 e2       	j8 720c <lfs_dir_commit+0x2c0>
    724a:	92 00       	nop16
    724c:	40 10 e0 02 	and $r1,$r1,$r24
    7250:	a4 82       	lhi333 $r2,[$r0+#0x4]
    7252:	92 2a       	srli45 $r1,#0xa
    7254:	96 49       	zeh33 $r1,$r1
    7256:	e2 41       	slt45 $r2,$r1
    7258:	e9 da       	bnezs8 720c <lfs_dir_commit+0x2c0>
    725a:	a6 46       	lbi333 $r1,[$r0+#0x6]
    725c:	8c 41       	addi45 $r2,#0x1
    725e:	ac 82       	shi333 $r2,[$r0+#0x4]
    7260:	5a 18 02 d6 	bnec $r1,#0x2,720c <lfs_dir_commit+0x2c0>
    7264:	04 10 00 0a 	lwi $r1,[$r0+#0x28]
    7268:	8c 21       	addi45 $r1,#0x1
    726a:	14 10 00 0a 	swi $r1,[$r0+#0x28]
    726e:	d5 cf       	j8 720c <lfs_dir_commit+0x2c0>
    7270:	15 90 00 02 	swi $r25,[$r0+#0x8]
    7274:	15 90 00 03 	swi $r25,[$r0+#0xc]
    7278:	d5 ca       	j8 720c <lfs_dir_commit+0x2c0>
    727a:	92 00       	nop16
    727c:	50 c3 00 08 	addi $r12,$r6,#0x8
    7280:	50 a3 00 20 	addi $r10,$r6,#0x20
    7284:	a4 f2       	lhi333 $r3,[$r6+#0x4]
    7286:	02 03 00 0e 	lhi $r0,[$r6+#0x1c]
    728a:	e2 60       	slt45 $r3,$r0
    728c:	e9 ae       	bnezs8 71e8 <lfs_dir_commit+0x29c>
    728e:	00 43 00 1f 	lbi $r4,[$r6+#0x1f]
    7292:	c4 ab       	beqz38 $r4,71e8 <lfs_dir_commit+0x29c>
    7294:	8a 60       	sub45 $r3,$r0
    7296:	ac f2       	shi333 $r3,[$r6+#0x4]
    7298:	80 08       	mov55 $r0,$r8
    729a:	b6 ff       	swi450 $r7,[$sp]
    729c:	f7 81       	swi37.sp $r7,[+#0x4]
    729e:	80 2c       	mov55 $r1,$r12
    72a0:	80 4a       	mov55 $r2,$r10
    72a2:	84 7f       	movi55 $r3,#-1
    72a4:	84 9f       	movi55 $r4,#-1
    72a6:	84 a0       	movi55 $r5,#0x0
    72a8:	49 ff e7 f0 	jal 4288 <lfs_dir_fetchmatch>
    72ac:	c0 ec       	beqz38 $r0,7284 <lfs_dir_commit+0x338>
    72ae:	ec 7c       	addi10.sp #0x7c
    72b0:	3a 6f b4 84 	lmw.bim $r6,[$sp],$r13,#0x2    ! {$r6~$r13, $lp}
    72b4:	dd 9e       	ret5 $lp
    72b6:	80 08       	mov55 $r0,$r8
    72b8:	80 27       	mov55 $r1,$r7
    72ba:	b0 96       	addri36.sp $r2,#0x58
    72bc:	49 ff eb 3a 	jal 4930 <lfs_fs_pred>
    72c0:	4e 02 00 24 	beqz $r0,7308 <lfs_dir_commit+0x3bc>
    72c4:	5a 07 fe 04 	beqc $r0,#-2,72cc <lfs_dir_commit+0x380>
    72c8:	48 ff ff 32 	j 712c <lfs_dir_commit+0x1e0>
    72cc:	48 ff fe c4 	j 7054 <lfs_dir_commit+0x108>
    72d0:	04 04 00 1a 	lwi $r0,[$r8+#0x68]
    72d4:	04 26 80 01 	lwi $r2,[$r13+#0x4]
    72d8:	a0 06       	lwi333 $r0,[$r0+#0x18]
    72da:	40 01 00 37 	divr $r0,$r1,$r2,$r0
    72de:	c9 45       	bnez38 $r1,7368 <lfs_dir_commit+0x41c>
    72e0:	50 04 00 30 	addi $r0,$r8,#0x30
    72e4:	3b 00 48 00 	lmw.bi $r16,[$r0],$r18,#0x0    ! {$r16~$r18}
    72e8:	50 14 00 3c 	addi $r1,$r8,#0x3c
    72ec:	04 36 80 02 	lwi $r3,[$r13+#0x8]
    72f0:	a8 bb       	swi333 $r2,[$r7+#0xc]
    72f2:	a8 fc       	swi333 $r3,[$r7+#0x10]
    72f4:	50 04 00 48 	addi $r0,$r8,#0x48
    72f8:	3b 00 c8 20 	smw.bi $r16,[$r1],$r18,#0x0    ! {$r16~$r18}
    72fc:	84 4c       	movi55 $r2,#0xc
    72fe:	84 20       	movi55 $r1,#0x0
    7300:	49 00 16 5a 	jal 9fb4 <memset>
    7304:	48 ff ff 46 	j 7190 <lfs_dir_commit+0x244>
    7308:	00 0f 80 6f 	lbi $r0,[$sp+#0x6f]
    730c:	4e 02 fe a4 	beqz $r0,7054 <lfs_dir_commit+0x108>
    7310:	80 08       	mov55 $r0,$r8
    7312:	b0 56       	addri36.sp $r1,#0x58
    7314:	50 23 80 00 	addi $r2,$r7,#0x0
    7318:	49 00 00 34 	jal 7380 <lfs_dir_drop>
    731c:	4e 03 ff 08 	bnez $r0,712c <lfs_dir_commit+0x1e0>
    7320:	48 ff fe 9a 	j 7054 <lfs_dir_commit+0x108>
    7324:	80 08       	mov55 $r0,$r8
    7326:	80 27       	mov55 $r1,$r7
    7328:	50 2f 80 2c 	addi $r2,$sp,#0x2c
    732c:	49 ff f1 64 	jal 55f4 <lfs_dir_getgstate>
    7330:	4e 03 fe fe 	bnez $r0,712c <lfs_dir_commit+0x1e0>
    7334:	46 27 ff ff 	sethi $r2,#0x7ffff
    7338:	80 08       	mov55 $r0,$r8
    733a:	80 2d       	mov55 $r1,$r13
    733c:	50 21 0c 0c 	addi $r2,$r2,#0xc0c
    7340:	50 3f 80 2c 	addi $r3,$sp,#0x2c
    7344:	49 ff ee b8 	jal 50b4 <lfs_dir_commitattr>
    7348:	4e 03 fe ee 	bnez $r0,7124 <lfs_dir_commit+0x1d8>
    734c:	48 ff fe e5 	j 7116 <lfs_dir_commit+0x1ca>
    7350:	44 00 36 cc 	movi $r0,#0x36cc
    7354:	44 10 06 d2 	movi $r1,#0x6d2
    7358:	44 20 7c 98 	movi $r2,#0x7c98
    735c:	44 30 3d 1c 	movi $r3,#0x3d1c
    7360:	49 00 14 5a 	jal 9c14 <__assert_func>
    7364:	92 00       	nop16
    7366:	92 00       	nop16
    7368:	44 00 36 cc 	movi $r0,#0x36cc
    736c:	44 10 07 30 	movi $r1,#0x730
    7370:	44 20 7c 98 	movi $r2,#0x7c98
    7374:	44 30 3c 3c 	movi $r3,#0x3c3c
    7378:	49 00 14 4e 	jal 9c14 <__assert_func>
    737c:	92 00       	nop16
    737e:	92 00       	nop16

00007380 <lfs_dir_drop>:
    7380:	3a 6f a0 bc 	smw.adm $r6,[$sp],$r8,#0x2    ! {$r6~$r8, $lp}
    7384:	ef f8       	addi10.sp #-8
    7386:	80 c2       	mov55 $r6,$r2
    7388:	81 01       	mov55 $r8,$r1
    738a:	50 20 00 48 	addi $r2,$r0,#0x48
    738e:	80 26       	mov55 $r1,$r6
    7390:	80 e0       	mov55 $r7,$r0
    7392:	49 ff f1 31 	jal 55f4 <lfs_dir_getgstate>
    7396:	c8 15       	bnez38 $r0,73c0 <lfs_dir_drop+0x40>
    7398:	00 43 00 17 	lbi $r4,[$r6+#0x17]
    739c:	46 00 00 ff 	sethi $r0,#0xff
    73a0:	50 42 06 00 	addi $r4,$r4,#0x600
    73a4:	50 00 0c 08 	addi $r0,$r0,#0xc08
    73a8:	40 42 50 08 	slli $r4,$r4,#0x14
    73ac:	ff 07       	or33 $r4,$r0
    73ae:	8c d8       	addi45 $r6,#0x18
    73b0:	80 07       	mov55 $r0,$r7
    73b2:	80 28       	mov55 $r1,$r8
    73b4:	80 5f       	mov55 $r2,$sp
    73b6:	84 61       	movi55 $r3,#0x1
    73b8:	b6 9f       	swi450 $r4,[$sp]
    73ba:	f6 81       	swi37.sp $r6,[+#0x4]
    73bc:	49 ff fd c8 	jal 6f4c <lfs_dir_commit>
    73c0:	ec 08       	addi10.sp #0x8
    73c2:	3a 6f a0 84 	lmw.bim $r6,[$sp],$r8,#0x2    ! {$r6~$r8, $lp}
    73c6:	dd 9e       	ret5 $lp

000073c8 <lfs_fs_forceconsistency>:
    73c8:	3a 6f a8 bc 	smw.adm $r6,[$sp],$r10,#0x2    ! {$r6~$r10, $lp}
    73cc:	ef 68       	addi10.sp #-152
    73ce:	04 10 00 0f 	lwi $r1,[$r0+#0x3c]
    73d2:	81 00       	mov55 $r8,$r0
    73d4:	40 00 d0 09 	srli $r0,$r1,#0x14
    73d8:	54 00 07 00 	andi $r0,$r0,#0x700
    73dc:	4e 03 00 82 	bnez $r0,74e0 <lfs_fs_forceconsistency+0x118>
    73e0:	04 04 00 0c 	lwi $r0,[$r8+#0x30]
    73e4:	54 00 03 ff 	andi $r0,$r0,#0x3ff
    73e8:	c0 38       	beqz38 $r0,7458 <lfs_fs_forceconsistency+0x90>
    73ea:	b1 8e       	addri36.sp $r6,#0x38
    73ec:	80 06       	mov55 $r0,$r6
    73ee:	84 20       	movi55 $r1,#0x0
    73f0:	fa 50       	movpi45 $r2,#0x20
    73f2:	49 00 15 e1 	jal 9fb4 <memset>
    73f6:	84 01       	movi55 $r0,#0x1
    73f8:	10 03 00 17 	sbi $r0,[$r6+#0x17]
    73fc:	46 97 ff ff 	sethi $r9,#0x7ffff
    7400:	84 01       	movi55 $r0,#0x1
    7402:	46 a6 00 ff 	sethi $r10,#0x600ff
    7406:	a8 37       	swi333 $r0,[$r6+#0x1c]
    7408:	b1 d6       	addri36.sp $r7,#0x58
    740a:	50 94 8c 00 	addi $r9,$r9,#0xc00
    740e:	50 a5 0c 08 	addi $r10,$r10,#0xc08
    7412:	f0 15       	lwi37.sp $r0,[+#0x54]
    7414:	5a 07 ff 1a 	beqc $r0,#-1,7448 <lfs_fs_forceconsistency+0x80>
    7418:	84 00       	movi55 $r0,#0x0
    741a:	b6 1f       	swi450 $r0,[$sp]
    741c:	f0 81       	swi37.sp $r0,[+#0x4]
    741e:	80 27       	mov55 $r1,$r7
    7420:	80 08       	mov55 $r0,$r8
    7422:	b0 94       	addri36.sp $r2,#0x50
    7424:	84 7f       	movi55 $r3,#-1
    7426:	84 9f       	movi55 $r4,#-1
    7428:	84 a0       	movi55 $r5,#0x0
    742a:	49 ff e7 2f 	jal 4288 <lfs_dir_fetchmatch>
    742e:	c8 53       	bnez38 $r0,74d4 <lfs_fs_forceconsistency+0x10c>
    7430:	00 03 00 17 	lbi $r0,[$r6+#0x17]
    7434:	4e 02 00 18 	beqz $r0,7464 <lfs_fs_forceconsistency+0x9c>
    7438:	3b 03 dc 00 	lmw.bi $r16,[$r7],$r23,#0x0    ! {$r16~$r23}
    743c:	3b 03 5c 20 	smw.bi $r16,[$r6],$r23,#0x0    ! {$r16~$r23}
    7440:	f0 14       	lwi37.sp $r0,[+#0x50]
    7442:	5a 0f ff e8 	bnec $r0,#-1,7412 <lfs_fs_forceconsistency+0x4a>
    7446:	92 00       	nop16
    7448:	04 14 00 0c 	lwi $r1,[$r8+#0x30]
    744c:	50 04 00 30 	addi $r0,$r8,#0x30
    7450:	fe 4a       	neg33 $r1,$r1
    7452:	96 4a       	seb33 $r1,$r1
    7454:	49 ff eb de 	jal 4c10 <lfs_fs_preporphans.isra.14>
    7458:	84 80       	movi55 $r4,#0x0
    745a:	80 04       	mov55 $r0,$r4
    745c:	ec 98       	addi10.sp #0x98
    745e:	3a 6f a8 84 	lmw.bim $r6,[$sp],$r10,#0x2    ! {$r6~$r10, $lp}
    7462:	dd 9e       	ret5 $lp
    7464:	80 08       	mov55 $r0,$r8
    7466:	b0 54       	addri36.sp $r1,#0x50
    7468:	b0 9e       	addri36.sp $r2,#0x78
    746a:	49 ff ea 1d 	jal 48a4 <lfs_fs_parent>
    746e:	80 60       	mov55 $r3,$r0
    7470:	4e 05 00 80 	bltz $r0,7570 <lfs_fs_forceconsistency+0x1a8>
    7474:	54 00 03 ff 	andi $r0,$r0,#0x3ff
    7478:	b6 1f       	swi450 $r0,[$sp]
    747a:	b0 5e       	addri36.sp $r1,#0x78
    747c:	80 08       	mov55 $r0,$r8
    747e:	80 49       	mov55 $r2,$r9
    7480:	84 80       	movi55 $r4,#0x0
    7482:	b1 4a       	addri36.sp $r5,#0x28
    7484:	49 ff ef c8 	jal 5414 <lfs_dir_getslice>
    7488:	4e 05 00 26 	bltz $r0,74d4 <lfs_fs_forceconsistency+0x10c>
    748c:	f5 0a       	lwi37.sp $r5,[+#0x28]
    748e:	f1 14       	lwi37.sp $r1,[+#0x50]
    7490:	4c 50 80 8c 	beq $r5,$r1,75a8 <lfs_fs_forceconsistency+0x1e0>
    7494:	a0 f7       	lwi333 $r3,[$r6+#0x1c]
    7496:	f2 0b       	lwi37.sp $r2,[+#0x2c]
    7498:	4c 32 80 8e 	beq $r3,$r5,75b4 <lfs_fs_forceconsistency+0x1ec>
    749c:	44 40 36 cc 	movi $r4,#0x36cc
    74a0:	b6 9f       	swi450 $r4,[$sp]
    74a2:	f5 84       	swi37.sp $r5,[+#0x10]
    74a4:	44 40 10 62 	movi $r4,#0x1062
    74a8:	44 00 01 38 	movi $r0,#0x138
    74ac:	f2 85       	swi37.sp $r2,[+#0x14]
    74ae:	f4 81       	swi37.sp $r4,[+#0x4]
    74b0:	f1 82       	swi37.sp $r1,[+#0x8]
    74b2:	f3 83       	swi37.sp $r3,[+#0xc]
    74b4:	f0 86       	swi37.sp $r0,[+#0x18]
    74b6:	44 00 3d 8c 	movi $r0,#0x3d8c
    74ba:	49 ff d7 bf 	jal 2438 <printf>
    74be:	b0 8c       	addri36.sp $r2,#0x30
    74c0:	b1 0a       	addri36.sp $r4,#0x28
    74c2:	80 08       	mov55 $r0,$r8
    74c4:	80 26       	mov55 $r1,$r6
    74c6:	84 61       	movi55 $r3,#0x1
    74c8:	a9 11       	swi333 $r4,[$r2+#0x4]
    74ca:	14 af 80 0c 	swi $r10,[$sp+#0x30]
    74ce:	49 ff fd 3f 	jal 6f4c <lfs_dir_commit>
    74d2:	c0 b7       	beqz38 $r0,7440 <lfs_fs_forceconsistency+0x78>
    74d4:	80 80       	mov55 $r4,$r0
    74d6:	80 04       	mov55 $r0,$r4
    74d8:	ec 98       	addi10.sp #0x98
    74da:	3a 6f a8 84 	lmw.bim $r6,[$sp],$r10,#0x2    ! {$r6~$r10, $lp}
    74de:	dd 9e       	ret5 $lp
    74e0:	46 60 00 ff 	sethi $r6,#0xff
    74e4:	50 63 0c 00 	addi $r6,$r6,#0xc00
    74e8:	04 04 00 11 	lwi $r0,[$r8+#0x44]
    74ec:	44 30 36 cc 	movi $r3,#0x36cc
    74f0:	fe 76       	and33 $r1,$r6
    74f2:	04 24 00 10 	lwi $r2,[$r8+#0x40]
    74f6:	92 2a       	srli45 $r1,#0xa
    74f8:	b6 7f       	swi450 $r3,[$sp]
    74fa:	f0 83       	swi37.sp $r0,[+#0xc]
    74fc:	44 30 10 1a 	movi $r3,#0x101a
    7500:	44 00 01 38 	movi $r0,#0x138
    7504:	f3 81       	swi37.sp $r3,[+#0x4]
    7506:	f2 82       	swi37.sp $r2,[+#0x8]
    7508:	f1 84       	swi37.sp $r1,[+#0x10]
    750a:	f0 85       	swi37.sp $r0,[+#0x14]
    750c:	44 00 3d 2c 	movi $r0,#0x3d2c
    7510:	49 ff d7 94 	jal 2438 <printf>
    7514:	84 00       	movi55 $r0,#0x0
    7516:	b6 1f       	swi450 $r0,[$sp]
    7518:	f0 81       	swi37.sp $r0,[+#0x4]
    751a:	84 9f       	movi55 $r4,#-1
    751c:	80 08       	mov55 $r0,$r8
    751e:	b0 5e       	addri36.sp $r1,#0x78
    7520:	50 24 00 40 	addi $r2,$r8,#0x40
    7524:	84 7f       	movi55 $r3,#-1
    7526:	84 a0       	movi55 $r5,#0x0
    7528:	49 ff e6 b0 	jal 4288 <lfs_dir_fetchmatch>
    752c:	80 80       	mov55 $r4,$r0
    752e:	c8 d4       	bnez38 $r0,74d6 <lfs_fs_forceconsistency+0x10e>
    7530:	04 24 00 0c 	lwi $r2,[$r8+#0x30]
    7534:	04 14 00 0f 	lwi $r1,[$r8+#0x3c]
    7538:	46 08 00 00 	sethi $r0,#0x80000
    753c:	50 00 03 ff 	addi $r0,$r0,#0x3ff
    7540:	fe 16       	and33 $r0,$r2
    7542:	ff 8e       	and33 $r6,$r1
    7544:	b0 88       	addri36.sp $r2,#0x20
    7546:	46 14 ff 00 	sethi $r1,#0x4ff00
    754a:	ff 8f       	or33 $r6,$r1
    754c:	14 04 00 0c 	swi $r0,[$r8+#0x30]
    7550:	14 44 00 0d 	swi $r4,[$r8+#0x34]
    7554:	14 44 00 0e 	swi $r4,[$r8+#0x38]
    7558:	a9 11       	swi333 $r4,[$r2+#0x4]
    755a:	80 08       	mov55 $r0,$r8
    755c:	b0 5e       	addri36.sp $r1,#0x78
    755e:	84 61       	movi55 $r3,#0x1
    7560:	f6 88       	swi37.sp $r6,[+#0x20]
    7562:	49 ff fc f5 	jal 6f4c <lfs_dir_commit>
    7566:	80 80       	mov55 $r4,$r0
    7568:	c8 b7       	bnez38 $r0,74d6 <lfs_fs_forceconsistency+0x10e>
    756a:	48 ff ff 3b 	j 73e0 <lfs_fs_forceconsistency+0x18>
    756e:	92 00       	nop16
    7570:	5a 0f fe 26 	bnec $r0,#-2,75bc <lfs_fs_forceconsistency+0x1f4>
    7574:	a0 37       	lwi333 $r0,[$r6+#0x1c]
    7576:	44 20 36 cc 	movi $r2,#0x36cc
    757a:	a0 76       	lwi333 $r1,[$r6+#0x18]
    757c:	b6 5f       	swi450 $r2,[$sp]
    757e:	f0 83       	swi37.sp $r0,[+#0xc]
    7580:	44 20 10 4b 	movi $r2,#0x104b
    7584:	44 00 01 38 	movi $r0,#0x138
    7588:	f2 81       	swi37.sp $r2,[+#0x4]
    758a:	f1 82       	swi37.sp $r1,[+#0x8]
    758c:	f0 84       	swi37.sp $r0,[+#0x10]
    758e:	44 00 3d 5c 	movi $r0,#0x3d5c
    7592:	49 ff d7 53 	jal 2438 <printf>
    7596:	80 08       	mov55 $r0,$r8
    7598:	80 26       	mov55 $r1,$r6
    759a:	80 47       	mov55 $r2,$r7
    759c:	49 ff fe f2 	jal 7380 <lfs_dir_drop>
    75a0:	4e 03 ff 9a 	bnez $r0,74d4 <lfs_fs_forceconsistency+0x10c>
    75a4:	48 ff ff 4e 	j 7440 <lfs_fs_forceconsistency+0x78>
    75a8:	f2 0b       	lwi37.sp $r2,[+#0x2c]
    75aa:	f3 15       	lwi37.sp $r3,[+#0x54]
    75ac:	4c 21 ff 76 	bne $r2,$r3,7498 <lfs_fs_forceconsistency+0xd0>
    75b0:	48 ff ff 44 	j 7438 <lfs_fs_forceconsistency+0x70>
    75b4:	4c 11 7f 74 	bne $r1,$r2,749c <lfs_fs_forceconsistency+0xd4>
    75b8:	48 ff ff 40 	j 7438 <lfs_fs_forceconsistency+0x70>
    75bc:	80 80       	mov55 $r4,$r0
    75be:	48 ff ff 8c 	j 74d6 <lfs_fs_forceconsistency+0x10e>
    75c2:	92 00       	nop16

000075c4 <lfs_file_sync>:
    75c4:	3a 6f 9c bc 	smw.adm $r6,[$sp],$r7,#0x2    ! {$r6~$r7, $lp}
    75c8:	ef e4       	addi10.sp #-28
    75ca:	04 20 80 0c 	lwi $r2,[$r1+#0x30]
    75ce:	80 c1       	mov55 $r6,$r1
    75d0:	42 31 54 0b 	btst $r3,$r2,#0x15
    75d4:	c3 64       	beqz38 $r3,769c <lfs_file_sync+0xd8>
    75d6:	42 21 4c 0b 	btst $r2,$r2,#0x13
    75da:	c2 07       	beqz38 $r2,75e8 <lfs_file_sync+0x24>
    75dc:	44 00 00 00 	movi $r0,#0x0
    75e0:	ec 1c       	addi10.sp #0x1c
    75e2:	3a 6f 9c 84 	lmw.bim $r6,[$sp],$r7,#0x2    ! {$r6~$r7, $lp}
    75e6:	dd 9e       	ret5 $lp
    75e8:	80 e0       	mov55 $r7,$r0
    75ea:	49 ff f7 ab 	jal 6540 <lfs_file_flush>
    75ee:	c8 3f       	bnez38 $r0,766c <lfs_file_sync+0xa8>
    75f0:	04 03 00 0c 	lwi $r0,[$r6+#0x30]
    75f4:	42 10 40 0b 	btst $r1,$r0,#0x10
    75f8:	c1 f2       	beqz38 $r1,75dc <lfs_file_sync+0x18>
    75fa:	a0 72       	lwi333 $r1,[$r6+#0x8]
    75fc:	5a 17 ff f0 	beqc $r1,#-1,75dc <lfs_file_sync+0x18>
    7600:	a0 73       	lwi333 $r1,[$r6+#0xc]
    7602:	5a 17 ff ed 	beqc $r1,#-1,75dc <lfs_file_sync+0x18>
    7606:	42 00 50 0b 	btst $r0,$r0,#0x14
    760a:	c8 3b       	bnez38 $r0,7680 <lfs_file_sync+0xbc>
    760c:	50 13 00 28 	addi $r1,$r6,#0x28
    7610:	3b 00 c4 00 	lmw.bi $r16,[$r1],$r17,#0x0    ! {$r16~$r17}
    7614:	3b 0f c4 20 	smw.bi $r16,[$sp],$r17,#0x0    ! {$r16~$r17}
    7618:	46 12 02 00 	sethi $r1,#0x20200
    761c:	84 a8       	movi55 $r5,#0x8
    761e:	82 1f       	mov55 $r16,$sp
    7620:	04 23 00 14 	lwi $r2,[$r6+#0x50]
    7624:	a4 32       	lhi333 $r0,[$r6+#0x4]
    7626:	a0 d2       	lwi333 $r3,[$r2+#0x8]
    7628:	46 41 02 00 	sethi $r4,#0x10200
    762c:	40 00 28 08 	slli $r0,$r0,#0xa
    7630:	ff 1f       	or33 $r4,$r3
    7632:	05 11 00 01 	lwi $r17,[$r2+#0x4]
    7636:	ff 07       	or33 $r4,$r0
    7638:	b0 82       	addri36.sp $r2,#0x8
    763a:	ff 4f       	or33 $r5,$r1
    763c:	ff 47       	or33 $r5,$r0
    763e:	50 13 00 08 	addi $r1,$r6,#0x8
    7642:	80 07       	mov55 $r0,$r7
    7644:	84 62       	movi55 $r3,#0x2
    7646:	15 01 00 01 	swi $r16,[$r2+#0x4]
    764a:	a9 12       	swi333 $r4,[$r2+#0x8]
    764c:	15 11 00 03 	swi $r17,[$r2+#0xc]
    7650:	14 5f 80 02 	swi $r5,[$sp+#0x8]
    7654:	49 ff fc 7c 	jal 6f4c <lfs_dir_commit>
    7658:	04 13 00 0c 	lwi $r1,[$r6+#0x30]
    765c:	c8 1a       	bnez38 $r0,7690 <lfs_file_sync+0xcc>
    765e:	42 10 c0 09 	bclr $r1,$r1,#0x10
    7662:	84 00       	movi55 $r0,#0x0
    7664:	14 13 00 0c 	swi $r1,[$r6+#0x30]
    7668:	d5 bc       	j8 75e0 <lfs_file_sync+0x1c>
    766a:	92 00       	nop16
    766c:	04 23 00 0c 	lwi $r2,[$r6+#0x30]
    7670:	42 21 4c 08 	bset $r2,$r2,#0x13
    7674:	14 23 00 0c 	swi $r2,[$r6+#0x30]
    7678:	ec 1c       	addi10.sp #0x1c
    767a:	3a 6f 9c 84 	lmw.bim $r6,[$sp],$r7,#0x2    ! {$r6~$r7, $lp}
    767e:	dd 9e       	ret5 $lp
    7680:	05 03 00 13 	lwi $r16,[$r6+#0x4c]
    7684:	04 53 00 0b 	lwi $r5,[$r6+#0x2c]
    7688:	46 12 01 00 	sethi $r1,#0x20100
    768c:	d5 ca       	j8 7620 <lfs_file_sync+0x5c>
    768e:	92 00       	nop16
    7690:	42 10 cc 08 	bset $r1,$r1,#0x13
    7694:	14 13 00 0c 	swi $r1,[$r6+#0x30]
    7698:	d5 a4       	j8 75e0 <lfs_file_sync+0x1c>
    769a:	92 00       	nop16
    769c:	44 00 36 cc 	movi $r0,#0x36cc
    76a0:	44 10 0a b0 	movi $r1,#0xab0
    76a4:	44 20 7c 00 	movi $r2,#0x7c00
    76a8:	44 30 3a 54 	movi $r3,#0x3a54
    76ac:	49 00 12 b4 	jal 9c14 <__assert_func>
    76b0:	92 00       	nop16
    76b2:	92 00       	nop16

000076b4 <lfs_file_close>:
    76b4:	3a 6f a0 bc 	smw.adm $r6,[$sp],$r8,#0x2    ! {$r6~$r8, $lp}
    76b8:	04 20 80 0c 	lwi $r2,[$r1+#0x30]
    76bc:	80 c1       	mov55 $r6,$r1
    76be:	42 21 54 0b 	btst $r2,$r2,#0x15
    76c2:	c2 31       	beqz38 $r2,7724 <lfs_file_close+0x70>
    76c4:	50 70 00 00 	addi $r7,$r0,#0x0
    76c8:	49 ff ff 7e 	jal 75c4 <lfs_file_sync>
    76cc:	04 33 80 0a 	lwi $r3,[$r7+#0x28]
    76d0:	81 00       	mov55 $r8,$r0
    76d2:	c3 0b       	beqz38 $r3,76e8 <lfs_file_close+0x34>
    76d4:	4c 61 c0 07 	bne $r6,$r3,76e2 <lfs_file_close+0x2e>
    76d8:	d5 16       	j8 7704 <lfs_file_close+0x50>
    76da:	92 00       	nop16
    76dc:	4c 61 00 17 	beq $r6,$r2,770a <lfs_file_close+0x56>
    76e0:	80 62       	mov55 $r3,$r2
    76e2:	b4 43       	lwi450 $r2,[$r3]
    76e4:	ca fc       	bnez38 $r2,76dc <lfs_file_close+0x28>
    76e6:	92 00       	nop16
    76e8:	04 03 00 14 	lwi $r0,[$r6+#0x50]
    76ec:	b4 00       	lwi450 $r0,[$r0]
    76ee:	c0 15       	beqz38 $r0,7718 <lfs_file_close+0x64>
    76f0:	04 13 00 0c 	lwi $r1,[$r6+#0x30]
    76f4:	80 08       	mov55 $r0,$r8
    76f6:	42 10 d4 09 	bclr $r1,$r1,#0x15
    76fa:	14 13 00 0c 	swi $r1,[$r6+#0x30]
    76fe:	3a 6f a0 84 	lmw.bim $r6,[$sp],$r8,#0x2    ! {$r6~$r8, $lp}
    7702:	dd 9e       	ret5 $lp
    7704:	50 33 80 28 	addi $r3,$r7,#0x28
    7708:	80 46       	mov55 $r2,$r6
    770a:	b4 02       	lwi450 $r0,[$r2]
    770c:	b6 03       	swi450 $r0,[$r3]
    770e:	04 03 00 14 	lwi $r0,[$r6+#0x50]
    7712:	b4 00       	lwi450 $r0,[$r0]
    7714:	4e 03 ff ee 	bnez $r0,76f0 <lfs_file_close+0x3c>
    7718:	04 03 00 13 	lwi $r0,[$r6+#0x4c]
    771c:	49 00 13 f3 	jal 9f02 <free>
    7720:	d5 e8       	j8 76f0 <lfs_file_close+0x3c>
    7722:	92 00       	nop16
    7724:	44 00 36 cc 	movi $r0,#0x36cc
    7728:	44 10 09 f5 	movi $r1,#0x9f5
    772c:	44 20 7c 10 	movi $r2,#0x7c10
    7730:	44 30 3a 54 	movi $r3,#0x3a54
    7734:	49 00 12 70 	jal 9c14 <__assert_func>
    7738:	92 00       	nop16
    773a:	92 00       	nop16

0000773c <lfs_file_opencfg>:
    773c:	3a 6f b0 bc 	smw.adm $r6,[$sp],$r12,#0x2    ! {$r6~$r12, $lp}
    7740:	ef d8       	addi10.sp #-40
    7742:	81 23       	mov55 $r9,$r3
    7744:	96 cf       	fexti33 $r3,#0x1
    7746:	81 00       	mov55 $r8,$r0
    7748:	80 c1       	mov55 $r6,$r1
    774a:	f2 83       	swi37.sp $r2,[+#0xc]
    774c:	5a 30 01 07 	beqc $r3,#0x1,775a <lfs_file_opencfg+0x1e>
    7750:	f4 82       	swi37.sp $r4,[+#0x8]
    7752:	49 ff fe 3b 	jal 73c8 <lfs_fs_forceconsistency>
    7756:	f4 02       	lwi37.sp $r4,[+#0x8]
    7758:	c8 32       	bnez38 $r0,77bc <lfs_file_opencfg+0x80>
    775a:	85 40       	movi55 $r10,#0x0
    775c:	42 04 d4 08 	bset $r0,$r9,#0x15
    7760:	50 b3 00 08 	addi $r11,$r6,#0x8
    7764:	14 03 00 0c 	swi $r0,[$r6+#0x30]
    7768:	14 43 00 14 	swi $r4,[$r6+#0x50]
    776c:	14 a3 00 0d 	swi $r10,[$r6+#0x34]
    7770:	14 a3 00 0f 	swi $r10,[$r6+#0x3c]
    7774:	14 a3 00 13 	swi $r10,[$r6+#0x4c]
    7778:	80 08       	mov55 $r0,$r8
    777a:	80 2b       	mov55 $r1,$r11
    777c:	b0 83       	addri36.sp $r2,#0xc
    777e:	9c f4       	addi333 $r3,$r6,#0x4
    7780:	49 ff ef 64 	jal 5648 <lfs_dir_find>
    7784:	80 e0       	mov55 $r7,$r0
    7786:	4e 05 00 87 	bltz $r0,7894 <lfs_file_opencfg+0x158>
    778a:	84 01       	movi55 $r0,#0x1
    778c:	ae 36       	sbi333 $r0,[$r6+#0x6]
    778e:	04 14 00 0a 	lwi $r1,[$r8+#0x28]
    7792:	54 04 82 00 	andi $r0,$r9,#0x200
    7796:	b6 26       	swi450 $r1,[$r6]
    7798:	14 64 00 0a 	swi $r6,[$r8+#0x28]
    779c:	c0 14       	beqz38 $r0,77c4 <lfs_file_opencfg+0x88>
    779e:	44 7f ff ef 	movi $r7,#-17
    77a2:	92 00       	nop16
    77a4:	04 33 00 0c 	lwi $r3,[$r6+#0x30]
    77a8:	42 31 cc 08 	bset $r3,$r3,#0x13
    77ac:	14 33 00 0c 	swi $r3,[$r6+#0x30]
    77b0:	80 08       	mov55 $r0,$r8
    77b2:	80 26       	mov55 $r1,$r6
    77b4:	49 ff ff 80 	jal 76b4 <lfs_file_close>
    77b8:	80 07       	mov55 $r0,$r7
    77ba:	92 00       	nop16
    77bc:	ec 28       	addi10.sp #0x28
    77be:	3a 6f b0 84 	lmw.bim $r6,[$sp],$r12,#0x2    ! {$r6~$r12, $lp}
    77c2:	dd 9e       	ret5 $lp
    77c4:	94 79       	slli333 $r1,$r7,#0x1
    77c6:	92 35       	srli45 $r1,#0x15
    77c8:	5a 10 01 08 	beqc $r1,#0x1,77d8 <lfs_file_opencfg+0x9c>
    77cc:	44 7f ff eb 	movi $r7,#-21
    77d0:	04 33 00 0c 	lwi $r3,[$r6+#0x30]
    77d4:	d5 ea       	j8 77a8 <lfs_file_opencfg+0x6c>
    77d6:	92 00       	nop16
    77d8:	54 f4 84 00 	andi $r15,$r9,#0x400
    77dc:	4e f2 00 80 	beqz $r15,78dc <lfs_file_opencfg+0x1a0>
    77e0:	04 23 00 0c 	lwi $r2,[$r6+#0x30]
    77e4:	a5 f2       	lhi333 $r7,[$r6+#0x4]
    77e6:	42 21 40 08 	bset $r2,$r2,#0x10
    77ea:	40 03 a8 08 	slli $r0,$r7,#0xa
    77ee:	46 12 01 00 	sethi $r1,#0x20100
    77f2:	40 70 04 04 	or $r7,$r0,$r1
    77f6:	14 23 00 0c 	swi $r2,[$r6+#0x30]
    77fa:	92 00       	nop16
    77fc:	04 53 00 14 	lwi $r5,[$r6+#0x50]
    7800:	a0 2a       	lwi333 $r0,[$r5+#0x8]
    7802:	4e 02 00 8e 	beqz $r0,791e <lfs_file_opencfg+0x1e2>
    7806:	46 c7 ff ff 	sethi $r12,#0x7ffff
    780a:	85 20       	movi55 $r9,#0x0
    780c:	85 40       	movi55 $r10,#0x0
    780e:	50 c6 0c 00 	addi $r12,$r12,#0xc00
    7812:	d5 29       	j8 7864 <lfs_file_opencfg+0x128>
    7814:	a0 e9       	lwi333 $r3,[$r5+#0x4]
    7816:	a5 72       	lhi333 $r5,[$r6+#0x4]
    7818:	41 11 a4 00 	add $r17,$r3,$r9
    781c:	38 31 a4 00 	lb $r3,[$r3+($r9<<#0x0)]
    7820:	05 28 80 02 	lwi $r18,[$r17+#0x8]
    7824:	41 02 a8 08 	slli $r16,$r5,#0xa
    7828:	50 31 83 00 	addi $r3,$r3,#0x300
    782c:	40 58 48 04 	or $r5,$r16,$r18
    7830:	40 31 d0 08 	slli $r3,$r3,#0x14
    7834:	fe ef       	or33 $r3,$r5
    7836:	54 51 83 ff 	andi $r5,$r3,#0x3ff
    783a:	b6 bf       	swi450 $r5,[$sp]
    783c:	04 58 80 01 	lwi $r5,[$r17+#0x4]
    7840:	49 ff ed ea 	jal 5414 <lfs_dir_getslice>
    7844:	4e 05 00 66 	bltz $r0,7910 <lfs_file_opencfg+0x1d4>
    7848:	04 33 00 0c 	lwi $r3,[$r6+#0x30]
    784c:	04 53 00 14 	lwi $r5,[$r6+#0x50]
    7850:	54 01 80 03 	andi $r0,$r3,#0x3
    7854:	5a 08 01 12 	bnec $r0,#0x1,7878 <lfs_file_opencfg+0x13c>
    7858:	a0 2a       	lwi333 $r0,[$r5+#0x8]
    785a:	8d 41       	addi45 $r10,#0x1
    785c:	e3 40       	slt45 $r10,$r0
    785e:	8d 2c       	addi45 $r9,#0xc
    7860:	e8 5f       	beqzs8 791e <lfs_file_opencfg+0x1e2>
    7862:	92 00       	nop16
    7864:	04 33 00 0c 	lwi $r3,[$r6+#0x30]
    7868:	80 08       	mov55 $r0,$r8
    786a:	55 01 80 03 	andi $r16,$r3,#0x3
    786e:	80 2b       	mov55 $r1,$r11
    7870:	80 4c       	mov55 $r2,$r12
    7872:	84 80       	movi55 $r4,#0x0
    7874:	5b 08 02 d0 	bnec $r16,#0x2,7814 <lfs_file_opencfg+0xd8>
    7878:	a1 29       	lwi333 $r4,[$r5+#0x4]
    787a:	04 04 00 1d 	lwi $r0,[$r8+#0x74]
    787e:	88 89       	add45 $r4,$r9
    7880:	a0 62       	lwi333 $r1,[$r4+#0x8]
    7882:	42 41 c0 08 	bset $r4,$r3,#0x10
    7886:	e2 01       	slt45 $r0,$r1
    7888:	4e f3 00 9a 	bnez $r15,79bc <lfs_file_opencfg+0x280>
    788c:	14 43 00 0c 	swi $r4,[$r6+#0x30]
    7890:	d5 e4       	j8 7858 <lfs_file_opencfg+0x11c>
    7892:	92 00       	nop16
    7894:	5a 07 fe 04 	beqc $r0,#-2,789c <lfs_file_opencfg+0x160>
    7898:	48 ff ff 86 	j 77a4 <lfs_file_opencfg+0x68>
    789c:	a4 32       	lhi333 $r0,[$r6+#0x4]
    789e:	5a 0b ff 05 	bnec $r0,#0x3ff,78a8 <lfs_file_opencfg+0x16c>
    78a2:	48 ff ff 81 	j 77a4 <lfs_file_opencfg+0x68>
    78a6:	92 00       	nop16
    78a8:	84 01       	movi55 $r0,#0x1
    78aa:	ae 36       	sbi333 $r0,[$r6+#0x6]
    78ac:	04 04 00 0a 	lwi $r0,[$r8+#0x28]
    78b0:	54 f4 81 00 	andi $r15,$r9,#0x100
    78b4:	b6 06       	swi450 $r0,[$r6]
    78b6:	14 64 00 0a 	swi $r6,[$r8+#0x28]
    78ba:	4e f2 ff 75 	beqz $r15,77a4 <lfs_file_opencfg+0x68>
    78be:	f0 03       	lwi37.sp $r0,[+#0xc]
    78c0:	49 00 14 c4 	jal a248 <strlen>
    78c4:	04 14 00 1b 	lwi $r1,[$r8+#0x6c]
    78c8:	40 10 80 06 	slt $r1,$r1,$r0
    78cc:	4e 12 00 7c 	beqz $r1,79c4 <lfs_file_opencfg+0x288>
    78d0:	44 7f ff dc 	movi $r7,#-36
    78d4:	04 33 00 0c 	lwi $r3,[$r6+#0x30]
    78d8:	48 ff ff 68 	j 77a8 <lfs_file_opencfg+0x6c>
    78dc:	a5 32       	lhi333 $r4,[$r6+#0x4]
    78de:	46 32 00 00 	sethi $r3,#0x20000
    78e2:	40 42 28 08 	slli $r4,$r4,#0xa
    78e6:	84 08       	movi55 $r0,#0x8
    78e8:	46 27 00 ff 	sethi $r2,#0x700ff
    78ec:	8c 68       	addi45 $r3,#0x8
    78ee:	b6 1f       	swi450 $r0,[$sp]
    78f0:	fe e7       	or33 $r3,$r4
    78f2:	80 08       	mov55 $r0,$r8
    78f4:	80 2b       	mov55 $r1,$r11
    78f6:	50 21 0c 00 	addi $r2,$r2,#0xc00
    78fa:	84 80       	movi55 $r4,#0x0
    78fc:	50 53 00 28 	addi $r5,$r6,#0x28
    7900:	49 ff ed 8a 	jal 5414 <lfs_dir_getslice>
    7904:	80 e0       	mov55 $r7,$r0
    7906:	4e 04 ff 7b 	bgez $r0,77fc <lfs_file_opencfg+0xc0>
    790a:	48 ff ff 4d 	j 77a4 <lfs_file_opencfg+0x68>
    790e:	92 00       	nop16
    7910:	5a 07 fe 9c 	beqc $r0,#-2,7848 <lfs_file_opencfg+0x10c>
    7914:	80 e0       	mov55 $r7,$r0
    7916:	04 33 00 0c 	lwi $r3,[$r6+#0x30]
    791a:	48 ff ff 47 	j 77a8 <lfs_file_opencfg+0x6c>
    791e:	b4 05       	lwi450 $r0,[$r5]
    7920:	4e 02 00 74 	beqz $r0,7a08 <lfs_file_opencfg+0x2cc>
    7924:	14 03 00 13 	swi $r0,[$r6+#0x4c]
    7928:	04 24 00 1a 	lwi $r2,[$r8+#0x68]
    792c:	44 10 00 ff 	movi $r1,#0xff
    7930:	04 21 00 0a 	lwi $r2,[$r2+#0x28]
    7934:	49 00 13 40 	jal 9fb4 <memset>
    7938:	94 39       	slli333 $r0,$r7,#0x1
    793a:	84 3f       	movi55 $r1,#-1
    793c:	92 15       	srli45 $r0,#0x15
    793e:	14 13 00 10 	swi $r1,[$r6+#0x40]
    7942:	5a 02 01 05 	beqc $r0,#0x201,794c <lfs_file_opencfg+0x210>
    7946:	84 00       	movi55 $r0,#0x0
    7948:	48 ff ff 3a 	j 77bc <lfs_file_opencfg+0x80>
    794c:	04 03 00 0c 	lwi $r0,[$r6+#0x30]
    7950:	04 34 00 1a 	lwi $r3,[$r8+#0x68]
    7954:	42 00 50 08 	bset $r0,$r0,#0x14
    7958:	04 31 80 0a 	lwi $r3,[$r3+#0x28]
    795c:	84 5e       	movi55 $r2,#-2
    795e:	54 13 83 ff 	andi $r1,$r7,#0x3ff
    7962:	14 03 00 0c 	swi $r0,[$r6+#0x30]
    7966:	84 00       	movi55 $r0,#0x0
    7968:	14 23 00 0a 	swi $r2,[$r6+#0x28]
    796c:	14 13 00 0b 	swi $r1,[$r6+#0x2c]
    7970:	14 23 00 10 	swi $r2,[$r6+#0x40]
    7974:	14 03 00 11 	swi $r0,[$r6+#0x44]
    7978:	14 33 00 12 	swi $r3,[$r6+#0x48]
    797c:	c1 e5       	beqz38 $r1,7946 <lfs_file_opencfg+0x20a>
    797e:	a4 72       	lhi333 $r1,[$r6+#0x4]
    7980:	44 20 03 fe 	movi $r2,#0x3fe
    7984:	e2 43       	slt45 $r2,$r3
    7986:	40 31 3c 1b 	cmovn $r3,$r2,$r15
    798a:	40 10 a8 08 	slli $r1,$r1,#0xa
    798e:	fe cf       	or33 $r3,$r1
    7990:	54 01 83 ff 	andi $r0,$r3,#0x3ff
    7994:	b6 1f       	swi450 $r0,[$sp]
    7996:	46 27 00 ff 	sethi $r2,#0x700ff
    799a:	80 08       	mov55 $r0,$r8
    799c:	80 2b       	mov55 $r1,$r11
    799e:	50 21 0c 00 	addi $r2,$r2,#0xc00
    79a2:	42 31 f4 08 	bset $r3,$r3,#0x1d
    79a6:	84 80       	movi55 $r4,#0x0
    79a8:	04 53 00 13 	lwi $r5,[$r6+#0x4c]
    79ac:	49 ff ed 34 	jal 5414 <lfs_dir_getslice>
    79b0:	80 e0       	mov55 $r7,$r0
    79b2:	4e 05 fe f9 	bltz $r0,77a4 <lfs_file_opencfg+0x68>
    79b6:	84 00       	movi55 $r0,#0x0
    79b8:	48 ff ff 02 	j 77bc <lfs_file_opencfg+0x80>
    79bc:	44 7f ff e4 	movi $r7,#-28
    79c0:	48 ff fe f4 	j 77a8 <lfs_file_opencfg+0x6c>
    79c4:	a4 b2       	lhi333 $r2,[$r6+#0x4]
    79c6:	46 72 01 00 	sethi $r7,#0x20100
    79ca:	40 21 28 08 	slli $r2,$r2,#0xa
    79ce:	42 41 50 08 	bset $r4,$r2,#0x14
    79d2:	47 04 01 00 	sethi $r16,#0x40100
    79d6:	41 01 40 04 	or $r16,$r2,$r16
    79da:	40 51 1c 04 	or $r5,$r2,$r7
    79de:	ff 07       	or33 $r4,$r0
    79e0:	b0 84       	addri36.sp $r2,#0x10
    79e2:	a9 12       	swi333 $r4,[$r2+#0x8]
    79e4:	f4 03       	lwi37.sp $r4,[+#0xc]
    79e6:	80 08       	mov55 $r0,$r8
    79e8:	80 2b       	mov55 $r1,$r11
    79ea:	84 63       	movi55 $r3,#0x3
    79ec:	14 a1 00 01 	swi $r10,[$r2+#0x4]
    79f0:	a9 13       	swi333 $r4,[$r2+#0xc]
    79f2:	a9 54       	swi333 $r5,[$r2+#0x10]
    79f4:	14 a1 00 05 	swi $r10,[$r2+#0x14]
    79f8:	15 0f 80 04 	swi $r16,[$sp+#0x10]
    79fc:	49 ff fa a8 	jal 6f4c <lfs_dir_commit>
    7a00:	4e 03 ff 68 	bnez $r0,78d0 <lfs_file_opencfg+0x194>
    7a04:	48 ff fe fc 	j 77fc <lfs_file_opencfg+0xc0>
    7a08:	04 04 00 1a 	lwi $r0,[$r8+#0x68]
    7a0c:	04 00 00 0a 	lwi $r0,[$r0+#0x28]
    7a10:	49 00 12 72 	jal 9ef4 <malloc>
    7a14:	14 03 00 13 	swi $r0,[$r6+#0x4c]
    7a18:	4e 03 ff 88 	bnez $r0,7928 <lfs_file_opencfg+0x1ec>
    7a1c:	84 f4       	movi55 $r7,#-12
    7a1e:	04 33 00 0c 	lwi $r3,[$r6+#0x30]
    7a22:	48 ff fe c3 	j 77a8 <lfs_file_opencfg+0x6c>
    7a26:	92 00       	nop16

00007a28 <lfs_file_open>:
    7a28:	44 40 7c 20 	movi $r4,#0x7c20
    7a2c:	48 ff fe 88 	j 773c <lfs_file_opencfg>

00007a30 <lfs_format>:
    7a30:	3a 6f 9c bc 	smw.adm $r6,[$sp],$r7,#0x2    ! {$r6~$r7, $lp}
    7a34:	ef 9c       	addi10.sp #-100
    7a36:	80 e0       	mov55 $r7,$r0
    7a38:	49 ff e1 cc 	jal 3dd0 <lfs_init>
    7a3c:	80 c0       	mov55 $r6,$r0
    7a3e:	c0 05       	beqz38 $r0,7a48 <lfs_format+0x18>
    7a40:	ec 64       	addi10.sp #0x64
    7a42:	3a 6f 9c 84 	lmw.bim $r6,[$sp],$r7,#0x2    ! {$r6~$r7, $lp}
    7a46:	dd 9e       	ret5 $lp
    7a48:	04 03 80 1a 	lwi $r0,[$r7+#0x68]
    7a4c:	44 10 00 00 	movi $r1,#0x0
    7a50:	04 20 00 0b 	lwi $r2,[$r0+#0x2c]
    7a54:	04 03 80 19 	lwi $r0,[$r7+#0x64]
    7a58:	49 00 12 ae 	jal 9fb4 <memset>
    7a5c:	04 13 80 1a 	lwi $r1,[$r7+#0x68]
    7a60:	04 00 80 0b 	lwi $r0,[$r1+#0x2c]
    7a64:	04 10 80 08 	lwi $r1,[$r1+#0x20]
    7a68:	94 03       	slli333 $r0,$r0,#0x3
    7a6a:	40 20 80 06 	slt $r2,$r1,$r0
    7a6e:	40 00 88 1b 	cmovn $r0,$r1,$r2
    7a72:	14 63 80 15 	swi $r6,[$r7+#0x54]
    7a76:	14 03 80 16 	swi $r0,[$r7+#0x58]
    7a7a:	14 63 80 17 	swi $r6,[$r7+#0x5c]
    7a7e:	14 13 80 18 	swi $r1,[$r7+#0x60]
    7a82:	80 07       	mov55 $r0,$r7
    7a84:	b0 50       	addri36.sp $r1,#0x40
    7a86:	49 ff f2 43 	jal 5f0c <lfs_dir_alloc>
    7a8a:	80 c0       	mov55 $r6,$r0
    7a8c:	c0 0a       	beqz38 $r0,7aa0 <lfs_format+0x70>
    7a8e:	80 07       	mov55 $r0,$r7
    7a90:	49 ff dd f4 	jal 3678 <lfs_deinit>
    7a94:	80 06       	mov55 $r0,$r6
    7a96:	ec 64       	addi10.sp #0x64
    7a98:	3a 6f 9c 84 	lmw.bim $r6,[$sp],$r7,#0x2    ! {$r6~$r7, $lp}
    7a9c:	dd 9e       	ret5 $lp
    7a9e:	92 00       	nop16
    7aa0:	04 53 80 1d 	lwi $r5,[$r7+#0x74]
    7aa4:	f5 89       	swi37.sp $r5,[+#0x24]
    7aa6:	46 54 01 00 	sethi $r5,#0x40100
    7aaa:	f5 8a       	swi37.sp $r5,[+#0x28]
    7aac:	46 50 ff 00 	sethi $r5,#0xff00
    7ab0:	b0 8a       	addri36.sp $r2,#0x28
    7ab2:	8c a8       	addi45 $r5,#0x8
    7ab4:	a9 52       	swi333 $r5,[$r2+#0x8]
    7ab6:	44 50 3a 70 	movi $r5,#0x3a70
    7aba:	04 03 80 1a 	lwi $r0,[$r7+#0x68]
    7abe:	a9 53       	swi333 $r5,[$r2+#0xc]
    7ac0:	46 52 01 00 	sethi $r5,#0x20100
    7ac4:	b1 04       	addri36.sp $r4,#0x10
    7ac6:	8c b8       	addi45 $r5,#0x18
    7ac8:	05 30 00 07 	lwi $r19,[$r0+#0x1c]
    7acc:	05 20 00 08 	lwi $r18,[$r0+#0x20]
    7ad0:	05 13 80 1b 	lwi $r17,[$r7+#0x6c]
    7ad4:	05 03 80 1c 	lwi $r16,[$r7+#0x70]
    7ad8:	45 42 00 00 	movi $r20,#0x20000
    7adc:	a9 91       	swi333 $r6,[$r2+#0x4]
    7ade:	80 07       	mov55 $r0,$r7
    7ae0:	b0 50       	addri36.sp $r1,#0x40
    7ae2:	84 63       	movi55 $r3,#0x3
    7ae4:	a9 54       	swi333 $r5,[$r2+#0x10]
    7ae6:	a9 15       	swi333 $r4,[$r2+#0x14]
    7ae8:	15 4f 80 04 	swi $r20,[$sp+#0x10]
    7aec:	15 3f 80 05 	swi $r19,[$sp+#0x14]
    7af0:	15 2f 80 06 	swi $r18,[$sp+#0x18]
    7af4:	15 1f 80 07 	swi $r17,[$sp+#0x1c]
    7af8:	15 0f 80 08 	swi $r16,[$sp+#0x20]
    7afc:	49 ff fa 28 	jal 6f4c <lfs_dir_commit>
    7b00:	80 c0       	mov55 $r6,$r0
    7b02:	c8 c6       	bnez38 $r0,7a8e <lfs_format+0x5e>
    7b04:	b0 82       	addri36.sp $r2,#0x8
    7b06:	86 01       	movi55 $r16,#0x1
    7b08:	b6 1f       	swi450 $r0,[$sp]
    7b0a:	f0 81       	swi37.sp $r0,[+#0x4]
    7b0c:	b0 50       	addri36.sp $r1,#0x40
    7b0e:	80 07       	mov55 $r0,$r7
    7b10:	84 7f       	movi55 $r3,#-1
    7b12:	84 9f       	movi55 $r4,#-1
    7b14:	84 a0       	movi55 $r5,#0x0
    7b16:	15 01 00 01 	swi $r16,[$r2+#0x4]
    7b1a:	f6 82       	swi37.sp $r6,[+#0x8]
    7b1c:	49 ff e3 b6 	jal 4288 <lfs_dir_fetchmatch>
    7b20:	80 c0       	mov55 $r6,$r0
    7b22:	c8 b6       	bnez38 $r0,7a8e <lfs_format+0x5e>
    7b24:	b0 50       	addri36.sp $r1,#0x40
    7b26:	80 07       	mov55 $r0,$r7
    7b28:	84 40       	movi55 $r2,#0x0
    7b2a:	84 60       	movi55 $r3,#0x0
    7b2c:	10 60 80 16 	sbi $r6,[$r1+#0x16]
    7b30:	49 ff fa 0e 	jal 6f4c <lfs_dir_commit>
    7b34:	80 c0       	mov55 $r6,$r0
    7b36:	d5 ac       	j8 7a8e <lfs_format+0x5e>

00007b38 <lfs_dir_split>:
    7b38:	3a 6f a0 bc 	smw.adm $r6,[$sp],$r8,#0x2    ! {$r6~$r8, $lp}
    7b3c:	ef c8       	addi10.sp #-56
    7b3e:	05 00 00 1a 	lwi $r16,[$r0+#0x68]
    7b42:	80 e1       	mov55 $r7,$r1
    7b44:	05 08 00 08 	lwi $r16,[$r16+#0x20]
    7b48:	15 00 00 18 	swi $r16,[$r0+#0x60]
    7b4c:	b0 46       	addri36.sp $r1,#0x18
    7b4e:	f2 85       	swi37.sp $r2,[+#0x14]
    7b50:	f3 84       	swi37.sp $r3,[+#0x10]
    7b52:	f4 83       	swi37.sp $r4,[+#0xc]
    7b54:	80 c0       	mov55 $r6,$r0
    7b56:	81 05       	mov55 $r8,$r5
    7b58:	49 ff f1 da 	jal 5f0c <lfs_dir_alloc>
    7b5c:	f4 03       	lwi37.sp $r4,[+#0xc]
    7b5e:	f3 04       	lwi37.sp $r3,[+#0x10]
    7b60:	f2 05       	lwi37.sp $r2,[+#0x14]
    7b62:	c0 05       	beqz38 $r0,7b6c <lfs_dir_split+0x34>
    7b64:	ec 38       	addi10.sp #0x38
    7b66:	3a 6f a0 84 	lmw.bim $r6,[$sp],$r8,#0x2    ! {$r6~$r8, $lp}
    7b6a:	dd 9e       	ret5 $lp
    7b6c:	02 0f 80 24 	lhi $r0,[$sp+#0x48]
    7b70:	01 23 80 17 	lbi $r18,[$r7+#0x17]
    7b74:	05 13 80 06 	lwi $r17,[$r7+#0x18]
    7b78:	05 03 80 07 	lwi $r16,[$r7+#0x1c]
    7b7c:	b0 46       	addri36.sp $r1,#0x18
    7b7e:	b6 1f       	swi450 $r0,[$sp]
    7b80:	80 a8       	mov55 $r5,$r8
    7b82:	80 06       	mov55 $r0,$r6
    7b84:	11 2f 80 2f 	sbi $r18,[$sp+#0x2f]
    7b88:	15 1f 80 0c 	swi $r17,[$sp+#0x30]
    7b8c:	15 0f 80 0d 	swi $r16,[$sp+#0x34]
    7b90:	49 ff f6 7c 	jal 6888 <lfs_dir_compact>
    7b94:	c8 e8       	bnez38 $r0,7b64 <lfs_dir_split+0x2c>
    7b96:	f2 06       	lwi37.sp $r2,[+#0x18]
    7b98:	f3 07       	lwi37.sp $r3,[+#0x1c]
    7b9a:	a8 be       	swi333 $r2,[$r7+#0x18]
    7b9c:	a8 ff       	swi333 $r3,[$r7+#0x1c]
    7b9e:	04 43 00 08 	lwi $r4,[$r6+#0x20]
    7ba2:	b4 27       	lwi450 $r1,[$r7]
    7ba4:	84 a1       	movi55 $r5,#0x1
    7ba6:	10 53 80 17 	sbi $r5,[$r7+#0x17]
    7baa:	4c 12 00 0c 	beq $r1,$r4,7bc2 <lfs_dir_split+0x8a>
    7bae:	05 03 80 01 	lwi $r16,[$r7+#0x4]
    7bb2:	04 53 00 09 	lwi $r5,[$r6+#0x24]
    7bb6:	4d 02 80 06 	beq $r16,$r5,7bc2 <lfs_dir_split+0x8a>
    7bba:	4c 12 80 04 	beq $r1,$r5,7bc2 <lfs_dir_split+0x8a>
    7bbe:	4c 48 7f d3 	bne $r4,$r16,7b64 <lfs_dir_split+0x2c>
    7bc2:	84 00       	movi55 $r0,#0x0
    7bc4:	4e 83 ff d0 	bnez $r8,7b64 <lfs_dir_split+0x2c>
    7bc8:	14 23 00 08 	swi $r2,[$r6+#0x20]
    7bcc:	14 33 00 09 	swi $r3,[$r6+#0x24]
    7bd0:	d5 ca       	j8 7b64 <lfs_dir_split+0x2c>
    7bd2:	92 00       	nop16

00007bd4 <__func__.4286>:
    7bd4:	6c 66 73 5f 69 6e 69 74 00 00 00 00                 lfs_init....

00007be0 <__func__.4141>:
    7be0:	6c 66 73 5f 66 69 6c 65 5f 77 72 69 74 65 00 00     lfs_file_write..

00007bf0 <__func__.4124>:
    7bf0:	6c 66 73 5f 66 69 6c 65 5f 72 65 61 64 00 00 00     lfs_file_read...

00007c00 <__func__.4110>:
    7c00:	6c 66 73 5f 66 69 6c 65 5f 73 79 6e 63 00 00 00     lfs_file_sync...

00007c10 <__func__.4065>:
    7c10:	6c 66 73 5f 66 69 6c 65 5f 63 6c 6f 73 65 00 00     lfs_file_close..

00007c20 <defaults.4059>:
	...

00007c2c <__func__.3846>:
    7c2c:	6c 66 73 5f 64 69 72 5f 63 6f 6d 70 61 63 74 00     lfs_dir_compact.

00007c3c <__func__.3334>:
    7c3c:	6c 66 73 5f 62 64 5f 73 79 6e 63 00                 lfs_bd_sync.

00007c48 <__func__.4094>:
    7c48:	6c 66 73 5f 66 69 6c 65 5f 66 6c 75 73 68 00 00     lfs_file_flush..

00007c58 <__func__.3323>:
    7c58:	6c 66 73 5f 62 64 5f 66 6c 75 73 68 00 00 00 00     lfs_bd_flush....

00007c68 <__func__.3346>:
    7c68:	6c 66 73 5f 62 64 5f 70 72 6f 67 00                 lfs_bd_prog.

00007c74 <__func__.3356>:
    7c74:	6c 66 73 5f 62 64 5f 65 72 61 73 65 00 00 00 00     lfs_bd_erase....

00007c84 <__func__.4075>:
    7c84:	6c 66 73 5f 66 69 6c 65 5f 72 65 6c 6f 63 61 74     lfs_file_relocat
    7c94:	65 00 00 00                                         e...

00007c98 <__func__.3868>:
    7c98:	6c 66 73 5f 64 69 72 5f 63 6f 6d 6d 69 74 00 00     lfs_dir_commit..

00007ca8 <__func__.4427>:
    7ca8:	6c 66 73 5f 66 73 5f 70 72 65 70 6f 72 70 68 61     lfs_fs_preporpha
    7cb8:	6e 73 00 00                                         ns..

00007cbc <__func__.3292>:
    7cbc:	6c 66 73 5f 62 64 5f 72 65 61 64 00                 lfs_bd_read.

00007cc8 <lfs_crc>:
    7cc8:	c2 16       	beqz38 $r2,7cf4 <lfs_crc+0x2c>
    7cca:	88 41       	add45 $r2,$r1
    7ccc:	44 50 7c f8 	movi $r5,#0x7cf8
    7cd0:	08 30 80 01 	lbi.bi $r3,[$r1],#0x1
    7cd4:	40 40 10 09 	srli $r4,$r0,#0x4
    7cd8:	fe 1d       	xor33 $r0,$r3
    7cda:	96 1f       	fexti33 $r0,#0x3
    7cdc:	38 02 82 02 	lw $r0,[$r5+($r0<<#0x2)]
    7ce0:	92 64       	srli45 $r3,#0x4
    7ce2:	fe 25       	xor33 $r0,$r4
    7ce4:	fe c5       	xor33 $r3,$r0
    7ce6:	96 df       	fexti33 $r3,#0x3
    7ce8:	38 32 8e 02 	lw $r3,[$r5+($r3<<#0x2)]
    7cec:	92 04       	srli45 $r0,#0x4
    7cee:	fe 1d       	xor33 $r0,$r3
    7cf0:	4c 11 7f f0 	bne $r1,$r2,7cd0 <lfs_crc+0x8>
    7cf4:	dd 9e       	ret5 $lp
    7cf6:	92 00       	nop16

00007cf8 <rtable.2979>:
    7cf8:	00 00 00 00 64 10 b7 1d c8 20 6e 3b ac 30 d9 26     ....d.... n;.0.&
    7d08:	90 41 dc 76 f4 51 6b 6b 58 61 b2 4d 3c 71 05 50     .A.v.QkkXa.M<q.P
    7d18:	20 83 b8 ed 44 93 0f f0 e8 a3 d6 d6 8c b3 61 cb      ...D.........a.
    7d28:	b0 c2 64 9b d4 d2 d3 86 78 e2 0a a0 1c f2 bd bd     ..d.....x.......

00007d38 <Cmd_Meta>:
    7d38:	46 1c cb 0b 	sethi $r1,#0xccb0b
    7d3c:	04 00 80 30 	lwi $r0,[$r1+#0xc0]
    7d40:	46 2c 00 00 	sethi $r2,#0xc0000
    7d44:	58 00 00 04 	ori $r0,$r0,#0x4
    7d48:	14 00 80 30 	swi $r0,[$r1+#0xc0]
    7d4c:	46 18 00 00 	sethi $r1,#0x80000
    7d50:	50 10 87 d0 	addi $r1,$r1,#0x7d0
    7d54:	84 00       	movi55 $r0,#0x0
    7d56:	14 11 00 a1 	swi $r1,[$r2+#0x284]
    7d5a:	dd 9e       	ret5 $lp

00007d5c <Cmd_Meta_reboot>:
    7d5c:	46 1c cb 0b 	sethi $r1,#0xccb0b
    7d60:	04 00 80 30 	lwi $r0,[$r1+#0xc0]
    7d64:	46 2c 00 00 	sethi $r2,#0xc0000
    7d68:	66 00 00 04 	bitci $r0,$r0,#0x4
    7d6c:	14 00 80 30 	swi $r0,[$r1+#0xc0]
    7d70:	46 18 00 00 	sethi $r1,#0x80000
    7d74:	58 10 81 00 	ori $r1,$r1,#0x100
    7d78:	14 11 00 a1 	swi $r1,[$r2+#0x284]
    7d7c:	84 21       	movi55 $r1,#0x1
    7d7e:	84 00       	movi55 $r0,#0x0
    7d80:	a8 56       	swi333 $r1,[$r2+#0x18]
    7d82:	dd 9e       	ret5 $lp
    7d84:	72 65 67 20 	*unknown*
    7d88:	3a 20 77 72 	smwzb.a $r2,[$r0],$gp,#0xd    ! {$r2~$gp, $fp, $gp, $sp}
    7d8c:	69 74 65 20 	*unknown*
    7d90:	30 78 25 78 	cplwi cp1,$cpr7,[$r16+#0x15e0]
    7d94:	20 20 30 78 	lbsi $r2,[$r0+#0x3078]
    7d98:	25 78 20 0a 	*unknown*
    7d9c:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    7da0:	5f 5f 66 6f 	sltsi $r21,$lp,#-6545
    7da4:	74 61 5f 64 	*unknown*
    7da8:	61 74 61 20 	amttsl2.s $d0,$r8,$r24,[$i0],[$i4],$m0,$m6
    7dac:	3d 20 30 78 	lhi.gp $r18,[+#0x60f0]
    7db0:	25 78 0a 00 	*unknown*
    7db4:	67 5f 73 61 	bitci $r21,$lp,#0x7361
    7db8:	5f 63 66 67 	sltsi $r22,$r6,#-6553
    7dbc:	20 3d 20 30 	lbsi $r3,[$p0+#0x2030]
    7dc0:	78 25 78 0a 	*unknown*
    7dc4:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    7dc8:	67 5f 77 69 	bitci $r21,$lp,#0x7769
    7dcc:	66 69 5f 63 	bitci $r6,$r18,#0x5f63
    7dd0:	66 67 20 3d 	bitci $r6,$r14,#0x203d
    7dd4:	20 30 78 25 	lbsi $r3,[$r0+#-2011]
    7dd8:	78 0a 00 00 	*unknown*
    7ddc:	5f 70 61 64 	sltsi $r23,$r0,#-7836
    7de0:	5f 73 65 74 	sltsi $r23,$r6,#-6796
    7de4:	74 69 6e 67 	*unknown*
    7de8:	20 3d 20 30 	lbsi $r3,[$p0+#0x2030]
    7dec:	78 25 78 0a 	*unknown*
    7df0:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    7df4:	67 5f 72 6f 	bitci $r21,$lp,#0x726f
    7df8:	6d 5f 62 6f 	*unknown*
    7dfc:	6f 74 20 3d 	*unknown*
    7e00:	20 30 78 25 	lbsi $r3,[$r0+#-2011]
    7e04:	78 0a 00 00 	*unknown*
    7e08:	67 5f 75 73 	bitci $r21,$lp,#0x7573
    7e0c:	65 72 5f 63 	mtsr $r23,151
    7e10:	66 67 20 3d 	bitci $r6,$r14,#0x203d
    7e14:	20 30 78 25 	lbsi $r3,[$r0+#-2011]
    7e18:	78 0a 00 00 	*unknown*
    7e1c:	5f 5f 61 70 	sltsi $r21,$lp,#-7824
    7e20:	70 5f 78 69 	*unknown*
    7e24:	70 31 20 3d 	*unknown*
    7e28:	20 30 78 25 	lbsi $r3,[$r0+#-2011]
    7e2c:	78 0a 00 00 	*unknown*
    7e30:	73 79 73 20 	*unknown*
    7e34:	62 75 73 20 	*unknown*
    7e38:	63 6c 6f 63 	*unknown*
    7e3c:	6b 20 3d 20 	cpe1 cp2,#0x480f4
    7e40:	25 64 0a 00 	*unknown*
    7e44:	66 6f 74 61 	bitci $r6,$lp,#0x7461
    7e48:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    7e4c:	6d 65 74 61 	*unknown*
    7e50:	5f 73 69 7a 	sltsi $r23,$r6,#-5766
    7e54:	65 3d 25 64 	*unknown*
    7e58:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    7e5c:	72 66 00 00 	*unknown*
    7e60:	6d 61 63 00 	*unknown*
    7e64:	70 61 64 00 	pbsad $r6,$r2,$r25
    7e68:	72 6f 6d 5f 	*unknown*
    7e6c:	62 6f 6f 74 	*unknown*
    7e70:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    7e74:	75 73 65 72 	*unknown*
    7e78:	5f 72 61 77 	sltsi $r23,$r4,#-7817
    7e7c:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    7e80:	6d 65 74 61 	*unknown*
    7e84:	5f 73 69 7a 	sltsi $r23,$r6,#-5766
    7e88:	65 3d 30 00 	*unknown*
    7e8c:	4f 4b 0a 00 	*unknown*
    7e90:	45 52 52 4f 	movi $r21,#0x2524f
    7e94:	52 3a 31 0a 	subri $r3,$r20,#0x310a
    7e98:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    7e9c:	20 20 20 20 	lbsi $r2,[$r0+#0x2020]
    7ea0:	20 20 20 20 	lbsi $r2,[$r0+#0x2020]
    7ea4:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    7ea8:	20 20 20 20 	lbsi $r2,[$r0+#0x2020]
    7eac:	20 20 20 25 	lbsi $r2,[$r0+#0x2025]
    7eb0:	30 32 6c 58 	cplwi cp3,$cpr3,[$r4+#-3744]
    7eb4:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    7eb8:	0a 2d 2d 2d 	lhi.bi $r2,[$p0],#0x5a5a
    7ebc:	2d 2d 2d 2d 	*unknown*
    7ec0:	2d 00 00 00 	*unknown*
    7ec4:	2b 2d 2d 2d 	lhsi.bi $r18,[$p0],#0x5a5a
    7ec8:	2d 2d 2d 2d 	*unknown*
    7ecc:	2d 00 00 00 	*unknown*
    7ed0:	0a 25 30 38 	lhi.bi $r2,[$r10],#0x6070
    7ed4:	6c 58 3a 25 	*unknown*
    7ed8:	30 38 6c 58 	cplwi cp3,$cpr3,[$r16+#-3744]
    7edc:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    7ee0:	20 25 30 38 	lbsi $r2,[$r10+#0x3038]
    7ee4:	6c 58 00 00 	*unknown*
    7ee8:	72 65 67 20 	*unknown*
    7eec:	3a 20 72 65 	smwa.bim $r2,[$r0],$fp,#0x9    ! {$r2~$fp, $fp, $sp}
    7ef0:	61 64 20 30 	*unknown*
    7ef4:	78 25 30 38 	*unknown*
    7ef8:	78 20 20 30 	*unknown*
    7efc:	78 25 30 38 	*unknown*
    7f00:	78 20 0a 00 	*unknown*
    7f04:	58 74 61 6c 	ori $r7,$r8,#0x616c
    7f08:	0a 00 00 00 	lhi.bi $r0,[$r0],#0x0
    7f0c:	72 65 67 77 	*unknown*
    7f10:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    7f14:	72 65 67 72 	*unknown*
    7f18:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    7f1c:	6d 65 74 61 	*unknown*
    7f20:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    7f24:	6d 65 74 61 	*unknown*
    7f28:	20 6d 6f 64 	lbsi $r6,[$p0+#-4252]
    7f2c:	65 20 66 6c 	msync ???
    7f30:	61 67 00 00 	*unknown*
    7f34:	6d 65 74 61 	*unknown*
    7f38:	5f 62 61 63 	sltsi $r22,$r4,#-7837
    7f3c:	6b 75 70 00 	fadds $fs23,$fs10,$fs28
    7f40:	6d 65 74 61 	*unknown*
    7f44:	5f 67 65 74 	sltsi $r22,$r14,#-6796
    7f48:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    7f4c:	6d 65 74 61 	*unknown*
    7f50:	5f 72 65 73 	sltsi $r23,$r4,#-6797
    7f54:	74 6f 72 65 	*unknown*
    7f58:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    7f5c:	6d 65 74 61 	*unknown*
    7f60:	5f 72 65 62 	sltsi $r23,$r4,#-6814
    7f64:	6f 6f 74 00 	*unknown*
    7f68:	74 65 73 74 	*unknown*
    7f6c:	00 00 00 00 	lbi $r0,[$r0+#0x0]

00007f70 <Cmd_WriteReg32>:
    7f70:	e4 02       	sltsi45 $r0,#0x2
    7f72:	e9 21       	bnezs8 7fb4 <Cmd_WriteReg32+0x44>
    7f74:	3a 6f 9c bc 	smw.adm $r6,[$sp],$r7,#0x2    ! {$r6~$r7, $lp}
    7f78:	ef f4       	addi10.sp #-12
    7f7a:	b4 01       	lwi450 $r0,[$r1]
    7f7c:	a1 89       	lwi333 $r6,[$r1+#0x4]
    7f7e:	c0 19       	beqz38 $r0,7fb0 <Cmd_WriteReg32+0x40>
    7f80:	c6 18       	beqz38 $r6,7fb0 <Cmd_WriteReg32+0x40>
    7f82:	84 20       	movi55 $r1,#0x0
    7f84:	fa 40       	movpi45 $r2,#0x10
    7f86:	49 00 12 14 	jal a3ae <strtoul>
    7f8a:	80 e0       	mov55 $r7,$r0
    7f8c:	84 20       	movi55 $r1,#0x0
    7f8e:	80 06       	mov55 $r0,$r6
    7f90:	fa 40       	movpi45 $r2,#0x10
    7f92:	49 00 12 0e 	jal a3ae <strtoul>
    7f96:	80 c0       	mov55 $r6,$r0
    7f98:	f0 81       	swi37.sp $r0,[+#0x4]
    7f9a:	b6 ff       	swi450 $r7,[$sp]
    7f9c:	44 00 7d 84 	movi $r0,#0x7d84
    7fa0:	49 ff d2 4c 	jal 2438 <printf>
    7fa4:	b6 c7       	swi450 $r6,[$r7]
    7fa6:	84 00       	movi55 $r0,#0x0
    7fa8:	ec 0c       	addi10.sp #0xc
    7faa:	3a 6f 9c 84 	lmw.bim $r6,[$sp],$r7,#0x2    ! {$r6~$r7, $lp}
    7fae:	dd 9e       	ret5 $lp
    7fb0:	84 1f       	movi55 $r0,#-1
    7fb2:	d5 fb       	j8 7fa8 <Cmd_WriteReg32+0x38>
    7fb4:	84 1f       	movi55 $r0,#-1
    7fb6:	dd 9e       	ret5 $lp

00007fb8 <Cmd_test>:
    7fb8:	3b ff fc bc 	smw.adm $sp,[$sp],$sp,#0x2    ! {$lp}
    7fbc:	ef f4       	addi10.sp #-12
    7fbe:	46 03 00 10 	sethi $r0,#0x30010
    7fc2:	58 00 00 00 	ori $r0,$r0,#0x0
    7fc6:	b6 1f       	swi450 $r0,[$sp]
    7fc8:	44 00 7d a0 	movi $r0,#0x7da0
    7fcc:	49 ff d2 36 	jal 2438 <printf>
    7fd0:	46 03 00 11 	sethi $r0,#0x30011
    7fd4:	58 00 00 00 	ori $r0,$r0,#0x0
    7fd8:	14 0f 80 00 	swi $r0,[$sp+#0x0]
    7fdc:	44 00 7d b4 	movi $r0,#0x7db4
    7fe0:	49 ff d2 2c 	jal 2438 <printf>
    7fe4:	46 03 00 12 	sethi $r0,#0x30012
    7fe8:	58 00 00 00 	ori $r0,$r0,#0x0
    7fec:	14 0f 80 00 	swi $r0,[$sp+#0x0]
    7ff0:	44 00 7d c8 	movi $r0,#0x7dc8
    7ff4:	49 ff d2 22 	jal 2438 <printf>
    7ff8:	46 03 00 13 	sethi $r0,#0x30013
    7ffc:	58 00 00 00 	ori $r0,$r0,#0x0
    8000:	14 0f 80 00 	swi $r0,[$sp+#0x0]
    8004:	44 00 7d dc 	movi $r0,#0x7ddc
    8008:	49 ff d2 18 	jal 2438 <printf>
    800c:	46 03 00 14 	sethi $r0,#0x30014
    8010:	58 00 00 00 	ori $r0,$r0,#0x0
    8014:	14 0f 80 00 	swi $r0,[$sp+#0x0]
    8018:	44 00 7d f4 	movi $r0,#0x7df4
    801c:	49 ff d2 0e 	jal 2438 <printf>
    8020:	46 03 00 15 	sethi $r0,#0x30015
    8024:	58 00 00 00 	ori $r0,$r0,#0x0
    8028:	14 0f 80 00 	swi $r0,[$sp+#0x0]
    802c:	44 00 7e 08 	movi $r0,#0x7e08
    8030:	49 ff d2 04 	jal 2438 <printf>
    8034:	46 03 00 25 	sethi $r0,#0x30025
    8038:	58 00 00 00 	ori $r0,$r0,#0x0
    803c:	14 0f 80 00 	swi $r0,[$sp+#0x0]
    8040:	44 00 7e 1c 	movi $r0,#0x7e1c
    8044:	49 ff d1 fa 	jal 2438 <printf>
    8048:	44 00 00 a0 	movi $r0,#0xa0
    804c:	b6 1f       	swi450 $r0,[$sp]
    804e:	44 00 7e 30 	movi $r0,#0x7e30
    8052:	49 ff d1 f3 	jal 2438 <printf>
    8056:	84 00       	movi55 $r0,#0x0
    8058:	ec 0c       	addi10.sp #0xc
    805a:	3b ff fc 84 	lmw.bim $sp,[$sp],$sp,#0x2    ! {$lp}
    805e:	dd 9e       	ret5 $lp

00008060 <Cmd_Meta_backup>:
    8060:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    8064:	ef f8       	addi10.sp #-8
    8066:	44 00 7e 44 	movi $r0,#0x7e44
    806a:	80 c1       	mov55 $r6,$r1
    806c:	b4 21       	lwi450 $r1,[$r1]
    806e:	49 00 10 c9 	jal a200 <strcmp>
    8072:	c0 25       	beqz38 $r0,80bc <Cmd_Meta_backup+0x5c>
    8074:	44 00 7e 5c 	movi $r0,#0x7e5c
    8078:	b4 26       	lwi450 $r1,[$r6]
    807a:	49 00 10 c3 	jal a200 <strcmp>
    807e:	c0 1f       	beqz38 $r0,80bc <Cmd_Meta_backup+0x5c>
    8080:	44 00 7e 60 	movi $r0,#0x7e60
    8084:	b4 26       	lwi450 $r1,[$r6]
    8086:	49 00 10 bd 	jal a200 <strcmp>
    808a:	c0 19       	beqz38 $r0,80bc <Cmd_Meta_backup+0x5c>
    808c:	44 00 7e 64 	movi $r0,#0x7e64
    8090:	b4 26       	lwi450 $r1,[$r6]
    8092:	49 00 10 b7 	jal a200 <strcmp>
    8096:	c0 13       	beqz38 $r0,80bc <Cmd_Meta_backup+0x5c>
    8098:	44 00 7e 68 	movi $r0,#0x7e68
    809c:	b4 26       	lwi450 $r1,[$r6]
    809e:	49 00 10 b1 	jal a200 <strcmp>
    80a2:	c0 0d       	beqz38 $r0,80bc <Cmd_Meta_backup+0x5c>
    80a4:	44 00 7e 74 	movi $r0,#0x7e74
    80a8:	b4 26       	lwi450 $r1,[$r6]
    80aa:	49 00 10 ab 	jal a200 <strcmp>
    80ae:	c0 13       	beqz38 $r0,80d4 <Cmd_Meta_backup+0x74>
    80b0:	44 00 7e 80 	movi $r0,#0x7e80
    80b4:	49 ff d1 c2 	jal 2438 <printf>
    80b8:	48 00 00 09 	j 80ca <Cmd_Meta_backup+0x6a>
    80bc:	44 00 10 00 	movi $r0,#0x1000
    80c0:	b6 1f       	swi450 $r0,[$sp]
    80c2:	44 00 7e 4c 	movi $r0,#0x7e4c
    80c6:	49 ff d1 b9 	jal 2438 <printf>
    80ca:	84 00       	movi55 $r0,#0x0
    80cc:	ec 08       	addi10.sp #0x8
    80ce:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    80d2:	dd 9e       	ret5 $lp
    80d4:	44 00 20 00 	movi $r0,#0x2000
    80d8:	b6 1f       	swi450 $r0,[$sp]
    80da:	44 00 7e 4c 	movi $r0,#0x7e4c
    80de:	49 ff d1 ad 	jal 2438 <printf>
    80e2:	d5 f4       	j8 80ca <Cmd_Meta_backup+0x6a>

000080e4 <Cmd_Meta_get>:
    80e4:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    80e8:	44 00 7e 44 	movi $r0,#0x7e44
    80ec:	80 c1       	mov55 $r6,$r1
    80ee:	b4 21       	lwi450 $r1,[$r1]
    80f0:	49 00 10 88 	jal a200 <strcmp>
    80f4:	c0 32       	beqz38 $r0,8158 <Cmd_Meta_get+0x74>
    80f6:	44 00 7e 5c 	movi $r0,#0x7e5c
    80fa:	b4 26       	lwi450 $r1,[$r6]
    80fc:	49 00 10 82 	jal a200 <strcmp>
    8100:	c0 1e       	beqz38 $r0,813c <Cmd_Meta_get+0x58>
    8102:	44 00 7e 60 	movi $r0,#0x7e60
    8106:	b4 26       	lwi450 $r1,[$r6]
    8108:	49 00 10 7c 	jal a200 <strcmp>
    810c:	c0 3e       	beqz38 $r0,8188 <Cmd_Meta_get+0xa4>
    810e:	44 00 7e 64 	movi $r0,#0x7e64
    8112:	b4 26       	lwi450 $r1,[$r6]
    8114:	49 00 10 76 	jal a200 <strcmp>
    8118:	c0 2e       	beqz38 $r0,8174 <Cmd_Meta_get+0x90>
    811a:	44 00 7e 68 	movi $r0,#0x7e68
    811e:	b4 26       	lwi450 $r1,[$r6]
    8120:	49 00 10 70 	jal a200 <strcmp>
    8124:	c0 40       	beqz38 $r0,81a4 <Cmd_Meta_get+0xc0>
    8126:	44 00 7e 74 	movi $r0,#0x7e74
    812a:	b4 26       	lwi450 $r1,[$r6]
    812c:	49 00 10 6a 	jal a200 <strcmp>
    8130:	c0 44       	beqz38 $r0,81b8 <Cmd_Meta_get+0xd4>
    8132:	44 00 01 38 	movi $r0,#0x138
    8136:	49 ff d1 81 	jal 2438 <printf>
    813a:	d5 0a       	j8 814e <Cmd_Meta_get+0x6a>
    813c:	44 10 10 00 	movi $r1,#0x1000
    8140:	84 41       	movi55 $r2,#0x1
    8142:	46 03 00 11 	sethi $r0,#0x30011
    8146:	58 00 00 00 	ori $r0,$r0,#0x0
    814a:	49 ff c9 0b 	jal 1360 <drv_comport_write_fifo>
    814e:	84 00       	movi55 $r0,#0x0
    8150:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    8154:	dd 9e       	ret5 $lp
    8156:	92 00       	nop16
    8158:	44 10 10 00 	movi $r1,#0x1000
    815c:	84 41       	movi55 $r2,#0x1
    815e:	46 03 00 10 	sethi $r0,#0x30010
    8162:	58 00 00 00 	ori $r0,$r0,#0x0
    8166:	49 ff c8 fd 	jal 1360 <drv_comport_write_fifo>
    816a:	84 00       	movi55 $r0,#0x0
    816c:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    8170:	dd 9e       	ret5 $lp
    8172:	92 00       	nop16
    8174:	44 10 10 00 	movi $r1,#0x1000
    8178:	84 41       	movi55 $r2,#0x1
    817a:	46 03 00 13 	sethi $r0,#0x30013
    817e:	58 00 00 00 	ori $r0,$r0,#0x0
    8182:	49 ff c8 ef 	jal 1360 <drv_comport_write_fifo>
    8186:	d5 e4       	j8 814e <Cmd_Meta_get+0x6a>
    8188:	44 10 10 00 	movi $r1,#0x1000
    818c:	84 41       	movi55 $r2,#0x1
    818e:	46 03 00 12 	sethi $r0,#0x30012
    8192:	58 00 00 00 	ori $r0,$r0,#0x0
    8196:	49 ff c8 e5 	jal 1360 <drv_comport_write_fifo>
    819a:	84 00       	movi55 $r0,#0x0
    819c:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    81a0:	dd 9e       	ret5 $lp
    81a2:	92 00       	nop16
    81a4:	44 10 10 00 	movi $r1,#0x1000
    81a8:	84 41       	movi55 $r2,#0x1
    81aa:	46 03 00 14 	sethi $r0,#0x30014
    81ae:	58 00 00 00 	ori $r0,$r0,#0x0
    81b2:	49 ff c8 d7 	jal 1360 <drv_comport_write_fifo>
    81b6:	d5 cc       	j8 814e <Cmd_Meta_get+0x6a>
    81b8:	44 10 20 00 	movi $r1,#0x2000
    81bc:	84 41       	movi55 $r2,#0x1
    81be:	46 03 00 15 	sethi $r0,#0x30015
    81c2:	58 00 00 00 	ori $r0,$r0,#0x0
    81c6:	49 ff c8 cd 	jal 1360 <drv_comport_write_fifo>
    81ca:	d5 c2       	j8 814e <Cmd_Meta_get+0x6a>

000081cc <flash_write_cfg>:
    81cc:	3a 6f a0 bc 	smw.adm $r6,[$sp],$r8,#0x2    ! {$r6~$r8, $lp}
    81d0:	ef f8       	addi10.sp #-8
    81d2:	95 c4       	slli333 $r7,$r0,#0x4
    81d4:	f1 81       	swi37.sp $r1,[+#0x4]
    81d6:	b6 5f       	swi450 $r2,[$sp]
    81d8:	92 e4       	srli45 $r7,#0x4
    81da:	49 ff c2 0d 	jal 5f4 <ota_flash_init>
    81de:	f1 01       	lwi37.sp $r1,[+#0x4]
    81e0:	04 2f 80 00 	lwi $r2,[$sp+#0x0]
    81e4:	3e 08 19 f8 	addi.gp $r0,#0x19f8
    81e8:	49 00 0e b2 	jal 9f4c <memcpy>
    81ec:	3e 68 19 f8 	addi.gp $r6,#0x19f8
    81f0:	50 03 80 00 	addi $r0,$r7,#0x0
    81f4:	49 ff c1 88 	jal 504 <ota_flash_sector_erase>
    81f8:	3e 88 29 f8 	addi.gp $r8,#0x29f8
    81fc:	8a e6       	sub45 $r7,$r6
    81fe:	98 3e       	add333 $r0,$r7,$r6
    8200:	50 23 00 00 	addi $r2,$r6,#0x0
    8204:	44 10 01 00 	movi $r1,#0x100
    8208:	50 63 01 00 	addi $r6,$r6,#0x100
    820c:	49 ff c1 b2 	jal 570 <ota_flash_page_program>
    8210:	4c 64 7f f7 	bne $r6,$r8,81fe <flash_write_cfg+0x32>
    8214:	ec 08       	addi10.sp #0x8
    8216:	3a 6f a0 84 	lmw.bim $r6,[$sp],$r8,#0x2    ! {$r6~$r8, $lp}
    821a:	dd 9e       	ret5 $lp

0000821c <Cmd_Meta_restore>:
    821c:	3a 6f a0 bc 	smw.adm $r6,[$sp],$r8,#0x2    ! {$r6~$r8, $lp}
    8220:	3e 08 09 f8 	addi.gp $r0,#0x9f8
    8224:	80 c1       	mov55 $r6,$r1
    8226:	44 20 10 00 	movi $r2,#0x1000
    822a:	84 20       	movi55 $r1,#0x0
    822c:	49 00 0e c4 	jal 9fb4 <memset>
    8230:	44 00 7e 44 	movi $r0,#0x7e44
    8234:	b4 26       	lwi450 $r1,[$r6]
    8236:	49 00 0f e5 	jal a200 <strcmp>
    823a:	c8 25       	bnez38 $r0,8284 <Cmd_Meta_restore+0x68>
    823c:	a0 31       	lwi333 $r0,[$r6+#0x4]
    823e:	49 00 0d 03 	jal 9c44 <atoi>
    8242:	80 c0       	mov55 $r6,$r0
    8244:	44 00 7e 8c 	movi $r0,#0x7e8c
    8248:	46 73 00 10 	sethi $r7,#0x30010
    824c:	58 73 80 00 	ori $r7,$r7,#0x0
    8250:	49 ff d0 f4 	jal 2438 <printf>
    8254:	4e 62 00 54 	beqz $r6,82fc <Cmd_Meta_restore+0xe0>
    8258:	80 26       	mov55 $r1,$r6
    825a:	3e 08 09 f8 	addi.gp $r0,#0x9f8
    825e:	49 ff c6 41 	jal ee0 <getDatafromUart>
    8262:	80 07       	mov55 $r0,$r7
    8264:	3e 18 09 f8 	addi.gp $r1,#0x9f8
    8268:	40 23 00 13 	zeh $r2,$r6
    826c:	49 ff ff b0 	jal 81cc <flash_write_cfg>
    8270:	44 00 7e 8c 	movi $r0,#0x7e8c
    8274:	49 ff d0 e2 	jal 2438 <printf>
    8278:	84 00       	movi55 $r0,#0x0
    827a:	92 00       	nop16
    827c:	3a 6f a0 84 	lmw.bim $r6,[$sp],$r8,#0x2    ! {$r6~$r8, $lp}
    8280:	dd 9e       	ret5 $lp
    8282:	92 00       	nop16
    8284:	44 00 7e 5c 	movi $r0,#0x7e5c
    8288:	b4 26       	lwi450 $r1,[$r6]
    828a:	49 00 0f bb 	jal a200 <strcmp>
    828e:	c8 0f       	bnez38 $r0,82ac <Cmd_Meta_restore+0x90>
    8290:	a0 31       	lwi333 $r0,[$r6+#0x4]
    8292:	49 00 0c d9 	jal 9c44 <atoi>
    8296:	80 c0       	mov55 $r6,$r0
    8298:	44 00 7e 8c 	movi $r0,#0x7e8c
    829c:	46 73 00 11 	sethi $r7,#0x30011
    82a0:	58 73 80 00 	ori $r7,$r7,#0x0
    82a4:	49 ff d0 ca 	jal 2438 <printf>
    82a8:	d5 d6       	j8 8254 <Cmd_Meta_restore+0x38>
    82aa:	92 00       	nop16
    82ac:	44 00 7e 60 	movi $r0,#0x7e60
    82b0:	b4 26       	lwi450 $r1,[$r6]
    82b2:	49 00 0f a7 	jal a200 <strcmp>
    82b6:	c0 15       	beqz38 $r0,82e0 <Cmd_Meta_restore+0xc4>
    82b8:	44 00 7e 64 	movi $r0,#0x7e64
    82bc:	b4 26       	lwi450 $r1,[$r6]
    82be:	49 00 0f a1 	jal a200 <strcmp>
    82c2:	c8 1f       	bnez38 $r0,8300 <Cmd_Meta_restore+0xe4>
    82c4:	a0 31       	lwi333 $r0,[$r6+#0x4]
    82c6:	49 00 0c bf 	jal 9c44 <atoi>
    82ca:	80 c0       	mov55 $r6,$r0
    82cc:	44 00 7e 8c 	movi $r0,#0x7e8c
    82d0:	46 73 00 13 	sethi $r7,#0x30013
    82d4:	58 73 80 00 	ori $r7,$r7,#0x0
    82d8:	49 ff d0 b0 	jal 2438 <printf>
    82dc:	48 ff ff bc 	j 8254 <Cmd_Meta_restore+0x38>
    82e0:	a0 31       	lwi333 $r0,[$r6+#0x4]
    82e2:	49 00 0c b1 	jal 9c44 <atoi>
    82e6:	80 c0       	mov55 $r6,$r0
    82e8:	44 00 7e 8c 	movi $r0,#0x7e8c
    82ec:	46 73 00 12 	sethi $r7,#0x30012
    82f0:	58 73 80 00 	ori $r7,$r7,#0x0
    82f4:	49 ff d0 a2 	jal 2438 <printf>
    82f8:	48 ff ff ae 	j 8254 <Cmd_Meta_restore+0x38>
    82fc:	84 1f       	movi55 $r0,#-1
    82fe:	d5 bf       	j8 827c <Cmd_Meta_restore+0x60>
    8300:	44 00 7e 68 	movi $r0,#0x7e68
    8304:	b4 26       	lwi450 $r1,[$r6]
    8306:	49 00 0f 7d 	jal a200 <strcmp>
    830a:	c0 15       	beqz38 $r0,8334 <Cmd_Meta_restore+0x118>
    830c:	44 00 7e 74 	movi $r0,#0x7e74
    8310:	b4 26       	lwi450 $r1,[$r6]
    8312:	49 00 0f 77 	jal a200 <strcmp>
    8316:	c8 1d       	bnez38 $r0,8350 <Cmd_Meta_restore+0x134>
    8318:	a0 31       	lwi333 $r0,[$r6+#0x4]
    831a:	49 00 0c 95 	jal 9c44 <atoi>
    831e:	80 c0       	mov55 $r6,$r0
    8320:	44 00 7e 8c 	movi $r0,#0x7e8c
    8324:	46 73 00 15 	sethi $r7,#0x30015
    8328:	58 73 80 00 	ori $r7,$r7,#0x0
    832c:	49 ff d0 86 	jal 2438 <printf>
    8330:	48 ff ff 92 	j 8254 <Cmd_Meta_restore+0x38>
    8334:	a0 31       	lwi333 $r0,[$r6+#0x4]
    8336:	49 00 0c 87 	jal 9c44 <atoi>
    833a:	80 c0       	mov55 $r6,$r0
    833c:	44 00 7e 8c 	movi $r0,#0x7e8c
    8340:	46 73 00 14 	sethi $r7,#0x30014
    8344:	58 73 80 00 	ori $r7,$r7,#0x0
    8348:	49 ff d0 78 	jal 2438 <printf>
    834c:	48 ff ff 84 	j 8254 <Cmd_Meta_restore+0x38>
    8350:	44 00 7e 90 	movi $r0,#0x7e90
    8354:	49 ff d0 72 	jal 2438 <printf>
    8358:	84 1f       	movi55 $r0,#-1
    835a:	48 ff ff 91 	j 827c <Cmd_Meta_restore+0x60>
    835e:	92 00       	nop16

00008360 <hex_dump>:
    8360:	3a 6f a4 bc 	smw.adm $r6,[$sp],$r9,#0x2    ! {$r6~$r9, $lp}
    8364:	ef f4       	addi10.sp #-12
    8366:	80 e0       	mov55 $r7,$r0
    8368:	44 00 7e 9c 	movi $r0,#0x7e9c
    836c:	81 21       	mov55 $r9,$r1
    836e:	84 c0       	movi55 $r6,#0x0
    8370:	49 ff d0 64 	jal 2438 <printf>
    8374:	b6 df       	swi450 $r6,[$sp]
    8376:	44 00 7e a8 	movi $r0,#0x7ea8
    837a:	8c c4       	addi45 $r6,#0x4
    837c:	49 ff d0 5e 	jal 2438 <printf>
    8380:	5a 68 20 fa 	bnec $r6,#0x20,8374 <hex_dump+0x14>
    8384:	44 00 7e b8 	movi $r0,#0x7eb8
    8388:	49 ff d0 58 	jal 2438 <printf>
    838c:	84 c8       	movi55 $r6,#0x8
    838e:	8e c1       	subi45 $r6,#0x1
    8390:	44 00 7e c4 	movi $r0,#0x7ec4
    8394:	49 ff d0 52 	jal 2438 <printf>
    8398:	ce fb       	bnez38 $r6,838e <hex_dump+0x2e>
    839a:	85 00       	movi55 $r8,#0x0
    839c:	4e 92 00 18 	beqz $r9,83cc <hex_dump+0x6c>
    83a0:	80 c7       	mov55 $r6,$r7
    83a2:	a2 31       	lwi333.bi $r0,[$r6],#0x4
    83a4:	f0 81       	swi37.sp $r0,[+#0x4]
    83a6:	b6 ff       	swi450 $r7,[$sp]
    83a8:	44 00 7e d0 	movi $r0,#0x7ed0
    83ac:	49 ff d0 46 	jal 2438 <printf>
    83b0:	50 73 80 20 	addi $r7,$r7,#0x20
    83b4:	a2 b1       	lwi333.bi $r2,[$r6],#0x4
    83b6:	b6 5f       	swi450 $r2,[$sp]
    83b8:	44 00 7e e0 	movi $r0,#0x7ee0
    83bc:	49 ff d0 3e 	jal 2438 <printf>
    83c0:	4c 73 7f fa 	bne $r7,$r6,83b4 <hex_dump+0x54>
    83c4:	8d 08       	addi45 $r8,#0x8
    83c6:	e3 09       	slt45 $r8,$r9
    83c8:	e9 ec       	bnezs8 83a0 <hex_dump+0x40>
    83ca:	92 00       	nop16
    83cc:	44 00 00 e4 	movi $r0,#0xe4
    83d0:	ec 0c       	addi10.sp #0xc
    83d2:	3a 6f a4 84 	lmw.bim $r6,[$sp],$r9,#0x2    ! {$r6~$r9, $lp}
    83d6:	48 ff d0 31 	j 2438 <printf>
    83da:	92 00       	nop16

000083dc <Cmd_ReadReg32>:
    83dc:	4e 07 00 30 	blez $r0,843c <Cmd_ReadReg32+0x60>
    83e0:	3a 6f 9c bc 	smw.adm $r6,[$sp],$r7,#0x2    ! {$r6~$r7, $lp}
    83e4:	ef f4       	addi10.sp #-12
    83e6:	80 61       	mov55 $r3,$r1
    83e8:	b4 c1       	lwi450 $r6,[$r1]
    83ea:	84 20       	movi55 $r1,#0x0
    83ec:	5a 00 02 13 	beqc $r0,#0x2,8412 <Cmd_ReadReg32+0x36>
    83f0:	fa 40       	movpi45 $r2,#0x10
    83f2:	80 06       	mov55 $r0,$r6
    83f4:	49 00 0f dd 	jal a3ae <strtoul>
    83f8:	80 40       	mov55 $r2,$r0
    83fa:	b4 02       	lwi450 $r0,[$r2]
    83fc:	f0 81       	swi37.sp $r0,[+#0x4]
    83fe:	b6 5f       	swi450 $r2,[$sp]
    8400:	44 00 7e e8 	movi $r0,#0x7ee8
    8404:	49 ff d0 1a 	jal 2438 <printf>
    8408:	84 00       	movi55 $r0,#0x0
    840a:	ec 0c       	addi10.sp #0xc
    840c:	3a 6f 9c 84 	lmw.bim $r6,[$sp],$r7,#0x2    ! {$r6~$r7, $lp}
    8410:	dd 9e       	ret5 $lp
    8412:	84 4a       	movi55 $r2,#0xa
    8414:	a0 19       	lwi333 $r0,[$r3+#0x4]
    8416:	49 00 0f cc 	jal a3ae <strtoul>
    841a:	80 e0       	mov55 $r7,$r0
    841c:	fa 40       	movpi45 $r2,#0x10
    841e:	80 06       	mov55 $r0,$r6
    8420:	84 20       	movi55 $r1,#0x0
    8422:	49 00 0f c6 	jal a3ae <strtoul>
    8426:	80 40       	mov55 $r2,$r0
    8428:	5a 70 01 e9 	beqc $r7,#0x1,83fa <Cmd_ReadReg32+0x1e>
    842c:	80 27       	mov55 $r1,$r7
    842e:	49 ff ff 99 	jal 8360 <hex_dump>
    8432:	84 00       	movi55 $r0,#0x0
    8434:	ec 0c       	addi10.sp #0xc
    8436:	3a 6f 9c 84 	lmw.bim $r6,[$sp],$r7,#0x2    ! {$r6~$r7, $lp}
    843a:	dd 9e       	ret5 $lp
    843c:	84 1f       	movi55 $r0,#-1
    843e:	dd 9e       	ret5 $lp

00008440 <gCliCmdTable>:
    8440:	0c 7f 00 00 70 7f 00 00 38 01 00 00 14 7f 00 00     ....p...8.......
    8450:	dc 83 00 00 38 01 00 00 1c 7f 00 00 38 7d 00 00     ....8.......8}..
    8460:	24 7f 00 00 34 7f 00 00 60 80 00 00 24 7f 00 00     $...4...`...$...
    8470:	40 7f 00 00 e4 80 00 00 24 7f 00 00 4c 7f 00 00     @.......$...L...
    8480:	1c 82 00 00 24 7f 00 00 5c 7f 00 00 5c 7d 00 00     ....$...\...\}..
    8490:	24 7f 00 00 68 7f 00 00 b8 7f 00 00 24 7f 00 00     $...h.......$...
	...

000084ac <hal_uart_irq_handler>:
    84ac:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    84b0:	46 6c 00 00 	sethi $r6,#0xc0000
    84b4:	04 03 03 0b 	lwi $r0,[$r6+#0xc2c]
    84b8:	4e 02 00 0e 	beqz $r0,84d4 <hal_uart_irq_handler+0x28>
    84bc:	54 10 01 e0 	andi $r1,$r0,#0x1e0
    84c0:	c1 0e       	beqz38 $r1,84dc <hal_uart_irq_handler+0x30>
    84c2:	3c 0c 0a 80 	lwi.gp $r0,[+#0x2a00]
    84c6:	c0 f7       	beqz38 $r0,84b4 <hal_uart_irq_handler+0x8>
    84c8:	4b e0 00 01 	jral $lp,$r0
    84cc:	04 03 03 0b 	lwi $r0,[$r6+#0xc2c]
    84d0:	4e 03 ff f6 	bnez $r0,84bc <hal_uart_irq_handler+0x10>
    84d4:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    84d8:	4a 00 78 20 	ret $lp
    84dc:	54 10 00 02 	andi $r1,$r0,#0x2
    84e0:	c9 0a       	bnez38 $r1,84f4 <hal_uart_irq_handler+0x48>
    84e2:	96 44       	xlsb33 $r1,$r0
    84e4:	c9 08       	bnez38 $r1,84f4 <hal_uart_irq_handler+0x48>
    84e6:	54 10 02 00 	andi $r1,$r0,#0x200
    84ea:	c1 09       	beqz38 $r1,84fc <hal_uart_irq_handler+0x50>
    84ec:	3c 0c 0a 81 	lwi.gp $r0,[+#0x2a04]
    84f0:	c8 ec       	bnez38 $r0,84c8 <hal_uart_irq_handler+0x1c>
    84f2:	d5 e1       	j8 84b4 <hal_uart_irq_handler+0x8>
    84f4:	3c 0c 0a 7e 	lwi.gp $r0,[+#0x29f8]
    84f8:	c8 e8       	bnez38 $r0,84c8 <hal_uart_irq_handler+0x1c>
    84fa:	d5 dd       	j8 84b4 <hal_uart_irq_handler+0x8>
    84fc:	96 16       	bmski33 $r0,#0x2
    84fe:	c0 db       	beqz38 $r0,84b4 <hal_uart_irq_handler+0x8>
    8500:	3c 0c 0a 83 	lwi.gp $r0,[+#0x2a0c]
    8504:	c8 e2       	bnez38 $r0,84c8 <hal_uart_irq_handler+0x1c>
    8506:	d5 d7       	j8 84b4 <hal_uart_irq_handler+0x8>

00008508 <hal_uart_register_isr>:
    8508:	c1 10       	beqz38 $r1,8528 <hal_uart_register_isr+0x20>
    850a:	3e 28 29 f8 	addi.gp $r2,#0x29f8
    850e:	38 11 02 0a 	sw $r1,[$r2+($r0<<#0x2)]
    8512:	46 1c 00 00 	sethi $r1,#0xc0000
    8516:	04 20 83 01 	lwi $r2,[$r1+#0xc04]
    851a:	84 61       	movi55 $r3,#0x1
    851c:	40 01 80 0c 	sll $r0,$r3,$r0
    8520:	fe 17       	or33 $r0,$r2
    8522:	14 00 83 01 	swi $r0,[$r1+#0xc04]
    8526:	dd 9e       	ret5 $lp
    8528:	46 3c 00 00 	sethi $r3,#0xc0000
    852c:	04 41 83 01 	lwi $r4,[$r3+#0xc04]
    8530:	84 41       	movi55 $r2,#0x1
    8532:	40 21 00 0c 	sll $r2,$r2,$r0
    8536:	40 22 08 12 	bitc $r2,$r4,$r2
    853a:	14 21 83 01 	swi $r2,[$r3+#0xc04]
    853e:	3e 28 29 f8 	addi.gp $r2,#0x29f8
    8542:	38 11 02 0a 	sw $r1,[$r2+($r0<<#0x2)]
    8546:	dd 9e       	ret5 $lp

00008548 <hal_uart_init>:
    8548:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    854c:	44 10 84 ac 	movi $r1,#0x84ac
    8550:	fa 0b       	movpi45 $r0,#0x1b
    8552:	49 00 02 c9 	jal 8ae4 <intc_group31_irq_enable>
    8556:	fa 0f       	movpi45 $r0,#0x1f
    8558:	49 00 02 6e 	jal 8a34 <intc_irq_enable>
    855c:	46 1c 00 00 	sethi $r1,#0xc0000
    8560:	04 00 80 08 	lwi $r0,[$r1+#0x20]
    8564:	58 00 10 00 	ori $r0,$r0,#0x1000
    8568:	14 00 80 08 	swi $r0,[$r1+#0x20]
    856c:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    8570:	dd 9e       	ret5 $lp
    8572:	92 00       	nop16

00008574 <hal_uart_deinit>:
    8574:	fa 0b       	movpi45 $r0,#0x1b
    8576:	48 00 02 d3 	j 8b1c <intc_group31_irq_disable>
    857a:	92 00       	nop16

0000857c <hal_uart_set_format>:
    857c:	46 40 00 e0 	sethi $r4,#0xe0
    8580:	9f 41       	subi333 $r5,$r0,#0x1
    8582:	50 42 0f ff 	addi $r4,$r4,#0xfff
    8586:	e2 85       	slt45 $r4,$r5
    8588:	e9 1a       	bnezs8 85bc <hal_uart_set_format+0x40>
    858a:	46 40 00 f4 	sethi $r4,#0xf4
    858e:	44 50 00 a0 	movi $r5,#0xa0
    8592:	94 db       	slli333 $r3,$r3,#0x3
    8594:	50 42 02 40 	addi $r4,$r4,#0x240
    8598:	54 31 80 38 	andi $r3,$r3,#0x38
    859c:	ff 2c       	mul33 $r4,$r5
    859e:	96 4f       	fexti33 $r1,#0x1
    85a0:	94 92       	slli333 $r2,$r2,#0x2
    85a2:	fe 5f       	or33 $r1,$r3
    85a4:	96 96       	bmski33 $r2,#0x2
    85a6:	46 3c 00 00 	sethi $r3,#0xc0000
    85aa:	40 02 00 17 	divr $r0,$r0,$r4,$r0
    85ae:	fe 8f       	or33 $r2,$r1
    85b0:	14 01 83 07 	swi $r0,[$r3+#0xc1c]
    85b4:	84 00       	movi55 $r0,#0x0
    85b6:	14 21 83 03 	swi $r2,[$r3+#0xc0c]
    85ba:	dd 9e       	ret5 $lp
    85bc:	84 1d       	movi55 $r0,#-3
    85be:	dd 9e       	ret5 $lp

000085c0 <hal_uart_direct_read_byte>:
    85c0:	46 0c 00 00 	sethi $r0,#0xc0000
    85c4:	04 00 03 00 	lwi $r0,[$r0+#0xc00]
    85c8:	dd 9e       	ret5 $lp
    85ca:	92 00       	nop16

000085cc <hal_uart_write_fifo>:
    85cc:	80 60       	mov55 $r3,$r0
    85ce:	c0 4b       	beqz38 $r0,8664 <hal_uart_write_fifo+0x98>
    85d0:	c2 1e       	beqz38 $r2,860c <hal_uart_write_fifo+0x40>
    85d2:	84 00       	movi55 $r0,#0x0
    85d4:	46 4c 00 00 	sethi $r4,#0xc0000
    85d8:	4e 17 00 4a 	blez $r1,866c <hal_uart_write_fifo+0xa0>
    85dc:	04 22 03 05 	lwi $r2,[$r4+#0xc14]
    85e0:	42 21 14 0b 	btst $r2,$r2,#0x5
    85e4:	c2 fc       	beqz38 $r2,85dc <hal_uart_write_fifo+0x10>
    85e6:	e4 31       	sltsi45 $r1,#0x11
    85e8:	e9 0f       	bnezs8 8606 <hal_uart_write_fifo+0x3a>
    85ea:	8e 30       	subi45 $r1,#0x10
    85ec:	fb 80       	movpi45 $r16,#0x10
    85ee:	92 00       	nop16
    85f0:	40 51 c0 00 	add $r5,$r3,$r16
    85f4:	08 21 80 01 	lbi.bi $r2,[$r3],#0x1
    85f8:	14 22 03 00 	swi $r2,[$r4+#0xc00]
    85fc:	4c 32 ff fc 	bne $r3,$r5,85f4 <hal_uart_write_fifo+0x28>
    8600:	88 10       	add45 $r0,$r16
    8602:	c9 ed       	bnez38 $r1,85dc <hal_uart_write_fifo+0x10>
    8604:	dd 9e       	ret5 $lp
    8606:	82 01       	mov55 $r16,$r1
    8608:	84 20       	movi55 $r1,#0x0
    860a:	d5 f3       	j8 85f0 <hal_uart_write_fifo+0x24>
    860c:	46 2c 00 00 	sethi $r2,#0xc0000
    8610:	50 21 0c 00 	addi $r2,$r2,#0xc00
    8614:	a0 15       	lwi333 $r0,[$r2+#0x14]
    8616:	42 00 18 0b 	btst $r0,$r0,#0x6
    861a:	c0 13       	beqz38 $r0,8640 <hal_uart_write_fifo+0x74>
    861c:	fa 00       	movpi45 $r0,#0x10
    861e:	42 10 80 01 	min $r1,$r1,$r0
    8622:	92 00       	nop16
    8624:	4e 17 00 25 	blez $r1,866e <hal_uart_write_fifo+0xa2>
    8628:	99 19       	add333 $r4,$r3,$r1
    862a:	46 2c 00 00 	sethi $r2,#0xc0000
    862e:	92 00       	nop16
    8630:	08 01 80 01 	lbi.bi $r0,[$r3],#0x1
    8634:	14 01 03 00 	swi $r0,[$r2+#0xc00]
    8638:	4c 32 7f fc 	bne $r3,$r4,8630 <hal_uart_write_fifo+0x64>
    863c:	80 01       	mov55 $r0,$r1
    863e:	dd 9e       	ret5 $lp
    8640:	a1 15       	lwi333 $r4,[$r2+#0x14]
    8642:	84 00       	movi55 $r0,#0x0
    8644:	42 42 14 0b 	btst $r4,$r4,#0x5
    8648:	c4 10       	beqz38 $r4,8668 <hal_uart_write_fifo+0x9c>
    864a:	04 01 00 0a 	lwi $r0,[$r2+#0x28]
    864e:	96 1f       	fexti33 $r0,#0x3
    8650:	52 00 00 10 	subri $r0,$r0,#0x10
    8654:	e0 20       	slts45 $r1,$r0
    8656:	e9 e7       	bnezs8 8624 <hal_uart_write_fifo+0x58>
    8658:	04 11 00 0a 	lwi $r1,[$r2+#0x28]
    865c:	96 5f       	fexti33 $r1,#0x3
    865e:	52 10 80 10 	subri $r1,$r1,#0x10
    8662:	d5 e3       	j8 8628 <hal_uart_write_fifo+0x5c>
    8664:	84 17       	movi55 $r0,#-9
    8666:	92 00       	nop16
    8668:	dd 9e       	ret5 $lp
    866a:	92 00       	nop16
    866c:	dd 9e       	ret5 $lp
    866e:	84 00       	movi55 $r0,#0x0
    8670:	dd 9e       	ret5 $lp
    8672:	92 00       	nop16

00008674 <hal_uart_read_fifo>:
    8674:	80 80       	mov55 $r4,$r0
    8676:	c0 30       	beqz38 $r0,86d6 <hal_uart_read_fifo+0x62>
    8678:	ca 18       	bnez38 $r2,86a8 <hal_uart_read_fifo+0x34>
    867a:	4e 17 00 2a 	blez $r1,86ce <hal_uart_read_fifo+0x5a>
    867e:	46 5c 00 00 	sethi $r5,#0xc0000
    8682:	04 02 83 05 	lwi $r0,[$r5+#0xc14]
    8686:	88 24       	add45 $r1,$r4
    8688:	96 04       	xlsb33 $r0,$r0
    868a:	80 44       	mov55 $r2,$r4
    868c:	c8 06       	bnez38 $r0,8698 <hal_uart_read_fifo+0x24>
    868e:	d5 23       	j8 86d4 <hal_uart_read_fifo+0x60>
    8690:	04 32 83 05 	lwi $r3,[$r5+#0xc14]
    8694:	96 dc       	xlsb33 $r3,$r3
    8696:	c3 1b       	beqz38 $r3,86cc <hal_uart_read_fifo+0x58>
    8698:	04 02 83 00 	lwi $r0,[$r5+#0xc00]
    869c:	18 01 00 01 	sbi.bi $r0,[$r2],#0x1
    86a0:	9a 14       	sub333 $r0,$r2,$r4
    86a2:	4c 20 ff f7 	bne $r2,$r1,8690 <hal_uart_read_fifo+0x1c>
    86a6:	dd 9e       	ret5 $lp
    86a8:	4e 17 00 13 	blez $r1,86ce <hal_uart_read_fifo+0x5a>
    86ac:	88 01       	add45 $r0,$r1
    86ae:	46 3c 00 00 	sethi $r3,#0xc0000
    86b2:	92 00       	nop16
    86b4:	04 21 83 05 	lwi $r2,[$r3+#0xc14]
    86b8:	96 94       	xlsb33 $r2,$r2
    86ba:	c2 fd       	beqz38 $r2,86b4 <hal_uart_read_fifo+0x40>
    86bc:	04 21 83 00 	lwi $r2,[$r3+#0xc00]
    86c0:	18 22 00 01 	sbi.bi $r2,[$r4],#0x1
    86c4:	4c 40 7f f8 	bne $r4,$r0,86b4 <hal_uart_read_fifo+0x40>
    86c8:	80 01       	mov55 $r0,$r1
    86ca:	dd 9e       	ret5 $lp
    86cc:	dd 9e       	ret5 $lp
    86ce:	84 00       	movi55 $r0,#0x0
    86d0:	dd 9e       	ret5 $lp
    86d2:	92 00       	nop16
    86d4:	dd 9e       	ret5 $lp
    86d6:	84 17       	movi55 $r0,#-9
    86d8:	dd 9e       	ret5 $lp
    86da:	92 00       	nop16

000086dc <hal_uart_sw_rst>:
    86dc:	fa 30       	movpi45 $r1,#0x20
    86de:	46 0c 00 00 	sethi $r0,#0xc0000
    86e2:	b6 20       	swi450 $r1,[$r0]
    86e4:	dd 9e       	ret5 $lp
    86e6:	92 00       	nop16

000086e8 <hal_uart_get_line_status>:
    86e8:	46 0c 00 00 	sethi $r0,#0xc0000
    86ec:	50 00 0c 00 	addi $r0,$r0,#0xc00
    86f0:	a0 05       	lwi333 $r0,[$r0+#0x14]
    86f2:	dd 9e       	ret5 $lp

000086f4 <hal_hsuart_irq_handler>:
    86f4:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    86f8:	46 0c 00 00 	sethi $r0,#0xc0000
    86fc:	50 00 0d 00 	addi $r0,$r0,#0xd00
    8700:	04 10 00 0b 	lwi $r1,[$r0+#0x2c]
    8704:	54 20 81 e0 	andi $r2,$r1,#0x1e0
    8708:	c2 0a       	beqz38 $r2,871c <hal_hsuart_irq_handler+0x28>
    870a:	3c 0c 0a 86 	lwi.gp $r0,[+#0x2a18]
    870e:	c0 03       	beqz38 $r0,8714 <hal_hsuart_irq_handler+0x20>
    8710:	4b e0 00 01 	jral $lp,$r0
    8714:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    8718:	dd 9e       	ret5 $lp
    871a:	92 00       	nop16
    871c:	54 20 80 02 	andi $r2,$r1,#0x2
    8720:	c2 08       	beqz38 $r2,8730 <hal_hsuart_irq_handler+0x3c>
    8722:	a0 05       	lwi333 $r0,[$r0+#0x14]
    8724:	96 04       	xlsb33 $r0,$r0
    8726:	c0 f7       	beqz38 $r0,8714 <hal_hsuart_irq_handler+0x20>
    8728:	3c 0c 0a 84 	lwi.gp $r0,[+#0x2a10]
    872c:	c8 f2       	bnez38 $r0,8710 <hal_hsuart_irq_handler+0x1c>
    872e:	d5 f3       	j8 8714 <hal_hsuart_irq_handler+0x20>
    8730:	96 0c       	xlsb33 $r0,$r1
    8732:	c8 fb       	bnez38 $r0,8728 <hal_hsuart_irq_handler+0x34>
    8734:	54 00 80 10 	andi $r0,$r1,#0x10
    8738:	c0 06       	beqz38 $r0,8744 <hal_hsuart_irq_handler+0x50>
    873a:	3c 0c 0a 85 	lwi.gp $r0,[+#0x2a14]
    873e:	c8 e9       	bnez38 $r0,8710 <hal_hsuart_irq_handler+0x1c>
    8740:	48 ff ff ea 	j 8714 <hal_hsuart_irq_handler+0x20>
    8744:	54 00 9e 00 	andi $r0,$r1,#0x1e00
    8748:	c0 0c       	beqz38 $r0,8760 <hal_hsuart_irq_handler+0x6c>
    874a:	3c 0c 0a 87 	lwi.gp $r0,[+#0x2a1c]
    874e:	c0 02       	beqz38 $r0,8752 <hal_hsuart_irq_handler+0x5e>
    8750:	dd 20       	jral5 $r0
    8752:	84 20       	movi55 $r1,#0x0
    8754:	46 0c 00 00 	sethi $r0,#0xc0000
    8758:	14 10 03 46 	swi $r1,[$r0+#0xd18]
    875c:	d5 dc       	j8 8714 <hal_hsuart_irq_handler+0x20>
    875e:	92 00       	nop16
    8760:	54 10 c0 00 	andi $r1,$r1,#0x4000
    8764:	c1 d8       	beqz38 $r1,8714 <hal_hsuart_irq_handler+0x20>
    8766:	3c 0c 0a 8b 	lwi.gp $r0,[+#0x2a2c]
    876a:	c8 d3       	bnez38 $r0,8710 <hal_hsuart_irq_handler+0x1c>
    876c:	d5 d4       	j8 8714 <hal_hsuart_irq_handler+0x20>
    876e:	92 00       	nop16

00008770 <hal_hsuart1_irq_handler>:
    8770:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    8774:	46 0c 00 00 	sethi $r0,#0xc0000
    8778:	50 00 0e 00 	addi $r0,$r0,#0xe00
    877c:	04 10 00 0b 	lwi $r1,[$r0+#0x2c]
    8780:	54 20 81 e0 	andi $r2,$r1,#0x1e0
    8784:	c2 0a       	beqz38 $r2,8798 <hal_hsuart1_irq_handler+0x28>
    8786:	3c 0c 0a 8e 	lwi.gp $r0,[+#0x2a38]
    878a:	c0 03       	beqz38 $r0,8790 <hal_hsuart1_irq_handler+0x20>
    878c:	4b e0 00 01 	jral $lp,$r0
    8790:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    8794:	dd 9e       	ret5 $lp
    8796:	92 00       	nop16
    8798:	54 20 80 02 	andi $r2,$r1,#0x2
    879c:	c2 08       	beqz38 $r2,87ac <hal_hsuart1_irq_handler+0x3c>
    879e:	a0 05       	lwi333 $r0,[$r0+#0x14]
    87a0:	96 04       	xlsb33 $r0,$r0
    87a2:	c0 f7       	beqz38 $r0,8790 <hal_hsuart1_irq_handler+0x20>
    87a4:	3c 0c 0a 8c 	lwi.gp $r0,[+#0x2a30]
    87a8:	c8 f2       	bnez38 $r0,878c <hal_hsuart1_irq_handler+0x1c>
    87aa:	d5 f3       	j8 8790 <hal_hsuart1_irq_handler+0x20>
    87ac:	96 0c       	xlsb33 $r0,$r1
    87ae:	c8 fb       	bnez38 $r0,87a4 <hal_hsuart1_irq_handler+0x34>
    87b0:	54 00 80 10 	andi $r0,$r1,#0x10
    87b4:	c0 06       	beqz38 $r0,87c0 <hal_hsuart1_irq_handler+0x50>
    87b6:	3c 0c 0a 8d 	lwi.gp $r0,[+#0x2a34]
    87ba:	c8 e9       	bnez38 $r0,878c <hal_hsuart1_irq_handler+0x1c>
    87bc:	48 ff ff ea 	j 8790 <hal_hsuart1_irq_handler+0x20>
    87c0:	54 00 9e 00 	andi $r0,$r1,#0x1e00
    87c4:	c0 0c       	beqz38 $r0,87dc <hal_hsuart1_irq_handler+0x6c>
    87c6:	3c 0c 0a 8f 	lwi.gp $r0,[+#0x2a3c]
    87ca:	c0 02       	beqz38 $r0,87ce <hal_hsuart1_irq_handler+0x5e>
    87cc:	dd 20       	jral5 $r0
    87ce:	84 20       	movi55 $r1,#0x0
    87d0:	46 0c 00 00 	sethi $r0,#0xc0000
    87d4:	14 10 03 46 	swi $r1,[$r0+#0xd18]
    87d8:	d5 dc       	j8 8790 <hal_hsuart1_irq_handler+0x20>
    87da:	92 00       	nop16
    87dc:	54 10 c0 00 	andi $r1,$r1,#0x4000
    87e0:	c1 d8       	beqz38 $r1,8790 <hal_hsuart1_irq_handler+0x20>
    87e2:	3c 0c 0a 93 	lwi.gp $r0,[+#0x2a4c]
    87e6:	c8 d3       	bnez38 $r0,878c <hal_hsuart1_irq_handler+0x1c>
    87e8:	d5 d4       	j8 8790 <hal_hsuart1_irq_handler+0x20>
    87ea:	92 00       	nop16

000087ec <hal_hsuart_register_isr_ex>:
    87ec:	3e 38 00 64 	addi.gp $r3,#0x64
    87f0:	c2 12       	beqz38 $r2,8814 <hal_hsuart_register_isr_ex+0x28>
    87f2:	38 51 82 02 	lw $r5,[$r3+($r0<<#0x2)]
    87f6:	84 81       	movi55 $r4,#0x1
    87f8:	a0 e9       	lwi333 $r3,[$r5+#0x4]
    87fa:	94 03       	slli333 $r0,$r0,#0x3
    87fc:	40 42 04 0c 	sll $r4,$r4,$r1
    8800:	88 20       	add45 $r1,$r0
    8802:	40 02 0c 04 	or $r0,$r4,$r3
    8806:	3e 38 2a 10 	addi.gp $r3,#0x2a10
    880a:	38 21 86 0a 	sw $r2,[$r3+($r1<<#0x2)]
    880e:	a8 29       	swi333 $r0,[$r5+#0x4]
    8810:	dd 9e       	ret5 $lp
    8812:	92 00       	nop16
    8814:	38 41 82 02 	lw $r4,[$r3+($r0<<#0x2)]
    8818:	84 61       	movi55 $r3,#0x1
    881a:	a1 61       	lwi333 $r5,[$r4+#0x4]
    881c:	40 31 84 0c 	sll $r3,$r3,$r1
    8820:	94 03       	slli333 $r0,$r0,#0x3
    8822:	88 20       	add45 $r1,$r0
    8824:	40 32 8c 12 	bitc $r3,$r5,$r3
    8828:	3e 08 2a 10 	addi.gp $r0,#0x2a10
    882c:	a8 e1       	swi333 $r3,[$r4+#0x4]
    882e:	38 20 06 0a 	sw $r2,[$r0+($r1<<#0x2)]
    8832:	dd 9e       	ret5 $lp

00008834 <hal_hsuart_init_ex>:
    8834:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    8838:	c0 06       	beqz38 $r0,8844 <hal_hsuart_init_ex+0x10>
    883a:	5a 00 01 0f 	beqc $r0,#0x1,8858 <hal_hsuart_init_ex+0x24>
    883e:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    8842:	dd 9e       	ret5 $lp
    8844:	fa 0f       	movpi45 $r0,#0x1f
    8846:	44 10 86 f4 	movi $r1,#0x86f4
    884a:	49 00 01 4d 	jal 8ae4 <intc_group31_irq_enable>
    884e:	fa 0f       	movpi45 $r0,#0x1f
    8850:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    8854:	48 00 00 f0 	j 8a34 <intc_irq_enable>
    8858:	fa 0f       	movpi45 $r0,#0x1f
    885a:	44 10 87 70 	movi $r1,#0x8770
    885e:	49 00 01 0b 	jal 8a74 <intc_group02_irq_enable>
    8862:	84 02       	movi55 $r0,#0x2
    8864:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    8868:	48 00 00 e6 	j 8a34 <intc_irq_enable>

0000886c <hal_hsuart_deinit_ex>:
    886c:	c0 04       	beqz38 $r0,8874 <hal_hsuart_deinit_ex+0x8>
    886e:	5a 00 01 06 	beqc $r0,#0x1,887a <hal_hsuart_deinit_ex+0xe>
    8872:	dd 9e       	ret5 $lp
    8874:	fa 0f       	movpi45 $r0,#0x1f
    8876:	48 00 01 53 	j 8b1c <intc_group31_irq_disable>
    887a:	fa 0f       	movpi45 $r0,#0x1f
    887c:	48 00 01 18 	j 8aac <intc_group02_irq_disable>

00008880 <hal_hsuart_set_format_ex>:
    8880:	47 00 04 c4 	sethi $r16,#0x4c4
    8884:	9f 49       	subi333 $r5,$r1,#0x1
    8886:	51 08 0b 3f 	addi $r16,$r16,#0xb3f
    888a:	e3 85       	slt45 $r16,$r5
    888c:	e9 2d       	bnezs8 88e6 <hal_hsuart_set_format_ex+0x66>
    888e:	47 00 00 f4 	sethi $r16,#0xf4
    8892:	51 08 02 40 	addi $r16,$r16,#0x240
    8896:	44 50 00 a0 	movi $r5,#0xa0
    889a:	42 52 c0 24 	mul $r5,$r5,$r16
    889e:	41 00 8c 08 	slli $r16,$r1,#0x3
    88a2:	41 12 c2 16 	divsr $r17,$r16,$r5,$r16
    88a6:	41 08 14 08 	slli $r16,$r16,#0x5
    88aa:	41 08 06 16 	divsr $r16,$r16,$r16,$r1
    88ae:	90 a3       	srai45 $r5,#0x3
    88b0:	40 12 84 36 	divsr $r1,$r1,$r5,$r1
    88b4:	95 23       	slli333 $r4,$r4,#0x3
    88b6:	40 58 40 08 	slli $r5,$r16,#0x10
    88ba:	3f 08 00 64 	addi.gp $r16,#0x64
    88be:	39 08 02 02 	lw $r16,[$r16+($r0<<#0x2)]
    88c2:	54 42 00 38 	andi $r4,$r4,#0x38
    88c6:	46 00 0f f0 	sethi $r0,#0xff0
    88ca:	96 8f       	fexti33 $r2,#0x1
    88cc:	94 da       	slli333 $r3,$r3,#0x2
    88ce:	ff 46       	and33 $r5,$r0
    88d0:	fe a7       	or33 $r2,$r4
    88d2:	96 d6       	bmski33 $r3,#0x2
    88d4:	96 49       	zeh33 $r1,$r1
    88d6:	fe d7       	or33 $r3,$r2
    88d8:	fe 6f       	or33 $r1,$r5
    88da:	14 38 00 03 	swi $r3,[$r16+#0xc]
    88de:	84 00       	movi55 $r0,#0x0
    88e0:	14 18 00 0a 	swi $r1,[$r16+#0x28]
    88e4:	dd 9e       	ret5 $lp
    88e6:	84 1d       	movi55 $r0,#-3
    88e8:	dd 9e       	ret5 $lp
    88ea:	92 00       	nop16

000088ec <hal_hsuart_write_fifo_ex>:
    88ec:	c1 50       	beqz38 $r1,898c <hal_hsuart_write_fifo_ex+0xa0>
    88ee:	c3 1d       	beqz38 $r3,8928 <hal_hsuart_write_fifo_ex+0x3c>
    88f0:	4e 27 00 48 	blez $r2,8980 <hal_hsuart_write_fifo_ex+0x94>
    88f4:	3e 38 00 64 	addi.gp $r3,#0x64
    88f8:	38 41 82 02 	lw $r4,[$r3+($r0<<#0x2)]
    88fc:	84 00       	movi55 $r0,#0x0
    88fe:	a0 e5       	lwi333 $r3,[$r4+#0x14]
    8900:	42 31 94 0b 	btst $r3,$r3,#0x5
    8904:	c3 fd       	beqz38 $r3,88fe <hal_hsuart_write_fifo_ex+0x12>
    8906:	5e f1 00 21 	sltsi $r15,$r2,#0x21
    890a:	e9 3e       	bnezs8 8986 <hal_hsuart_write_fifo_ex+0x9a>
    890c:	50 21 7f e0 	addi $r2,$r2,#-32
    8910:	fb 90       	movpi45 $r16,#0x20
    8912:	92 00       	nop16
    8914:	40 50 c0 00 	add $r5,$r1,$r16
    8918:	08 30 80 01 	lbi.bi $r3,[$r1],#0x1
    891c:	b6 64       	swi450 $r3,[$r4]
    891e:	4c 12 ff fd 	bne $r1,$r5,8918 <hal_hsuart_write_fifo_ex+0x2c>
    8922:	88 10       	add45 $r0,$r16
    8924:	ca ed       	bnez38 $r2,88fe <hal_hsuart_write_fifo_ex+0x12>
    8926:	dd 9e       	ret5 $lp
    8928:	3e 38 00 64 	addi.gp $r3,#0x64
    892c:	38 31 82 02 	lw $r3,[$r3+($r0<<#0x2)]
    8930:	a0 1d       	lwi333 $r0,[$r3+#0x14]
    8932:	42 00 14 0b 	btst $r0,$r0,#0x5
    8936:	c0 11       	beqz38 $r0,8958 <hal_hsuart_write_fifo_ex+0x6c>
    8938:	fa 10       	movpi45 $r0,#0x20
    893a:	42 21 00 01 	min $r2,$r2,$r0
    893e:	92 00       	nop16
    8940:	4e 27 00 20 	blez $r2,8980 <hal_hsuart_write_fifo_ex+0x94>
    8944:	99 0a       	add333 $r4,$r1,$r2
    8946:	92 00       	nop16
    8948:	08 00 80 01 	lbi.bi $r0,[$r1],#0x1
    894c:	b6 03       	swi450 $r0,[$r3]
    894e:	4c 12 7f fd 	bne $r1,$r4,8948 <hal_hsuart_write_fifo_ex+0x5c>
    8952:	80 02       	mov55 $r0,$r2
    8954:	4a 00 78 20 	ret $lp
    8958:	04 41 80 0b 	lwi $r4,[$r3+#0x2c]
    895c:	84 00       	movi55 $r0,#0x0
    895e:	97 16       	bmski33 $r4,#0x2
    8960:	c4 12       	beqz38 $r4,8984 <hal_hsuart_write_fifo_ex+0x98>
    8962:	04 01 80 08 	lwi $r0,[$r3+#0x20]
    8966:	92 10       	srli45 $r0,#0x10
    8968:	96 27       	fexti33 $r0,#0x4
    896a:	52 00 00 20 	subri $r0,$r0,#0x20
    896e:	e0 40       	slts45 $r2,$r0
    8970:	e9 e8       	bnezs8 8940 <hal_hsuart_write_fifo_ex+0x54>
    8972:	04 21 80 08 	lwi $r2,[$r3+#0x20]
    8976:	92 50       	srli45 $r2,#0x10
    8978:	96 a7       	fexti33 $r2,#0x4
    897a:	52 21 00 20 	subri $r2,$r2,#0x20
    897e:	d5 e3       	j8 8944 <hal_hsuart_write_fifo_ex+0x58>
    8980:	44 00 00 00 	movi $r0,#0x0
    8984:	dd 9e       	ret5 $lp
    8986:	82 02       	mov55 $r16,$r2
    8988:	84 40       	movi55 $r2,#0x0
    898a:	d5 c5       	j8 8914 <hal_hsuart_write_fifo_ex+0x28>
    898c:	84 17       	movi55 $r0,#-9
    898e:	dd 9e       	ret5 $lp

00008990 <hal_hsuart_read_fifo_ex>:
    8990:	82 00       	mov55 $r16,$r0
    8992:	c1 32       	beqz38 $r1,89f6 <hal_hsuart_read_fifo_ex+0x66>
    8994:	cb 1a       	bnez38 $r3,89c8 <hal_hsuart_read_fifo_ex+0x38>
    8996:	4e 27 00 2c 	blez $r2,89ee <hal_hsuart_read_fifo_ex+0x5e>
    899a:	3f 18 00 64 	addi.gp $r17,#0x64
    899e:	38 58 82 02 	lw $r5,[$r17+($r0<<#0x2)]
    89a2:	88 41       	add45 $r2,$r1
    89a4:	a0 2d       	lwi333 $r0,[$r5+#0x14]
    89a6:	80 61       	mov55 $r3,$r1
    89a8:	96 04       	xlsb33 $r0,$r0
    89aa:	c8 08       	bnez38 $r0,89ba <hal_hsuart_read_fifo_ex+0x2a>
    89ac:	d5 24       	j8 89f4 <hal_hsuart_read_fifo_ex+0x64>
    89ae:	92 00       	nop16
    89b0:	38 58 c2 02 	lw $r5,[$r17+($r16<<#0x2)]
    89b4:	a1 2d       	lwi333 $r4,[$r5+#0x14]
    89b6:	97 24       	xlsb33 $r4,$r4
    89b8:	c4 1a       	beqz38 $r4,89ec <hal_hsuart_read_fifo_ex+0x5c>
    89ba:	b4 05       	lwi450 $r0,[$r5]
    89bc:	18 01 80 01 	sbi.bi $r0,[$r3],#0x1
    89c0:	9a 19       	sub333 $r0,$r3,$r1
    89c2:	4c 31 7f f7 	bne $r3,$r2,89b0 <hal_hsuart_read_fifo_ex+0x20>
    89c6:	dd 9e       	ret5 $lp
    89c8:	4e 27 00 13 	blez $r2,89ee <hal_hsuart_read_fifo_ex+0x5e>
    89cc:	98 0a       	add333 $r0,$r1,$r2
    89ce:	3f 18 00 64 	addi.gp $r17,#0x64
    89d2:	92 00       	nop16
    89d4:	38 48 c2 02 	lw $r4,[$r17+($r16<<#0x2)]
    89d8:	a0 e5       	lwi333 $r3,[$r4+#0x14]
    89da:	96 dc       	xlsb33 $r3,$r3
    89dc:	c3 fe       	beqz38 $r3,89d8 <hal_hsuart_read_fifo_ex+0x48>
    89de:	b4 64       	lwi450 $r3,[$r4]
    89e0:	18 30 80 01 	sbi.bi $r3,[$r1],#0x1
    89e4:	4c 10 7f f8 	bne $r1,$r0,89d4 <hal_hsuart_read_fifo_ex+0x44>
    89e8:	80 02       	mov55 $r0,$r2
    89ea:	dd 9e       	ret5 $lp
    89ec:	dd 9e       	ret5 $lp
    89ee:	84 00       	movi55 $r0,#0x0
    89f0:	dd 9e       	ret5 $lp
    89f2:	92 00       	nop16
    89f4:	dd 9e       	ret5 $lp
    89f6:	84 17       	movi55 $r0,#-9
    89f8:	dd 9e       	ret5 $lp
    89fa:	92 00       	nop16

000089fc <hal_hsuart_sw_rst_ex>:
    89fc:	c0 0a       	beqz38 $r0,8a10 <hal_hsuart_sw_rst_ex+0x14>
    89fe:	5a 00 01 03 	beqc $r0,#0x1,8a04 <hal_hsuart_sw_rst_ex+0x8>
    8a02:	dd 9e       	ret5 $lp
    8a04:	44 10 08 00 	movi $r1,#0x800
    8a08:	46 0c 00 00 	sethi $r0,#0xc0000
    8a0c:	b6 20       	swi450 $r1,[$r0]
    8a0e:	dd 9e       	ret5 $lp
    8a10:	46 10 04 00 	sethi $r1,#0x400
    8a14:	46 0c 00 00 	sethi $r0,#0xc0000
    8a18:	b6 20       	swi450 $r1,[$r0]
    8a1a:	dd 9e       	ret5 $lp

00008a1c <hal_hsuart_get_line_status_ex>:
    8a1c:	3e 18 00 64 	addi.gp $r1,#0x64
    8a20:	38 00 82 02 	lw $r0,[$r1+($r0<<#0x2)]
    8a24:	a0 05       	lwi333 $r0,[$r0+#0x14]
    8a26:	dd 9e       	ret5 $lp

00008a28 <hal_hsuart_direct_read_byte_ex>:
    8a28:	3e 18 00 64 	addi.gp $r1,#0x64
    8a2c:	38 00 82 02 	lw $r0,[$r1+($r0<<#0x2)]
    8a30:	b4 00       	lwi450 $r0,[$r0]
    8a32:	dd 9e       	ret5 $lp

00008a34 <intc_irq_enable>:
    8a34:	ef f8       	addi10.sp #-8
    8a36:	64 12 00 02 	mfsr $r1,$psw
    8a3a:	64 02 00 43 	setgie.d
    8a3e:	46 3c 00 02 	sethi $r3,#0xc0002
    8a42:	f1 81       	swi37.sp $r1,[+#0x4]
    8a44:	04 21 80 30 	lwi $r2,[$r3+#0xc0]
    8a48:	84 21       	movi55 $r1,#0x1
    8a4a:	40 00 80 0c 	sll $r0,$r1,$r0
    8a4e:	40 11 00 12 	bitc $r1,$r2,$r0
    8a52:	14 11 80 30 	swi $r1,[$r3+#0xc0]
    8a56:	64 13 04 02 	mfsr $r1,$int_mask2
    8a5a:	fe 0f       	or33 $r0,$r1
    8a5c:	64 03 04 03 	mtsr $r0,$int_mask2
    8a60:	64 00 00 08 	dsb
    8a64:	f0 01       	lwi37.sp $r0,[+#0x4]
    8a66:	64 02 00 03 	mtsr $r0,$psw
    8a6a:	64 00 00 09 	isb
    8a6e:	ec 08       	addi10.sp #0x8
    8a70:	dd 9e       	ret5 $lp
    8a72:	92 00       	nop16

00008a74 <intc_group02_irq_enable>:
    8a74:	ef f8       	addi10.sp #-8
    8a76:	64 22 00 02 	mfsr $r2,$psw
    8a7a:	64 02 00 43 	setgie.d
    8a7e:	f2 81       	swi37.sp $r2,[+#0x4]
    8a80:	3e 28 2a d0 	addi.gp $r2,#0x2ad0
    8a84:	38 11 02 0a 	sw $r1,[$r2+($r0<<#0x2)]
    8a88:	46 2c 00 02 	sethi $r2,#0xc0002
    8a8c:	04 31 00 27 	lwi $r3,[$r2+#0x9c]
    8a90:	84 21       	movi55 $r1,#0x1
    8a92:	40 00 80 0c 	sll $r0,$r1,$r0
    8a96:	40 01 80 12 	bitc $r0,$r3,$r0
    8a9a:	14 01 00 27 	swi $r0,[$r2+#0x9c]
    8a9e:	f0 01       	lwi37.sp $r0,[+#0x4]
    8aa0:	64 02 00 03 	mtsr $r0,$psw
    8aa4:	64 00 00 09 	isb
    8aa8:	ec 08       	addi10.sp #0x8
    8aaa:	dd 9e       	ret5 $lp

00008aac <intc_group02_irq_disable>:
    8aac:	ef f8       	addi10.sp #-8
    8aae:	64 12 00 02 	mfsr $r1,$psw
    8ab2:	64 02 00 43 	setgie.d
    8ab6:	46 3c 00 02 	sethi $r3,#0xc0002
    8aba:	f1 81       	swi37.sp $r1,[+#0x4]
    8abc:	04 21 80 27 	lwi $r2,[$r3+#0x9c]
    8ac0:	84 21       	movi55 $r1,#0x1
    8ac2:	40 10 80 0c 	sll $r1,$r1,$r0
    8ac6:	fe 57       	or33 $r1,$r2
    8ac8:	14 11 80 27 	swi $r1,[$r3+#0x9c]
    8acc:	84 40       	movi55 $r2,#0x0
    8ace:	3e 18 2a d0 	addi.gp $r1,#0x2ad0
    8ad2:	38 20 82 0a 	sw $r2,[$r1+($r0<<#0x2)]
    8ad6:	f0 01       	lwi37.sp $r0,[+#0x4]
    8ad8:	64 02 00 03 	mtsr $r0,$psw
    8adc:	64 00 00 09 	isb
    8ae0:	ec 08       	addi10.sp #0x8
    8ae2:	dd 9e       	ret5 $lp

00008ae4 <intc_group31_irq_enable>:
    8ae4:	ef f8       	addi10.sp #-8
    8ae6:	64 22 00 02 	mfsr $r2,$psw
    8aea:	64 02 00 43 	setgie.d
    8aee:	f2 81       	swi37.sp $r2,[+#0x4]
    8af0:	3e 28 2a 50 	addi.gp $r2,#0x2a50
    8af4:	38 11 02 0a 	sw $r1,[$r2+($r0<<#0x2)]
    8af8:	46 2c 00 02 	sethi $r2,#0xc0002
    8afc:	04 31 00 2d 	lwi $r3,[$r2+#0xb4]
    8b00:	84 21       	movi55 $r1,#0x1
    8b02:	40 00 80 0c 	sll $r0,$r1,$r0
    8b06:	40 01 80 12 	bitc $r0,$r3,$r0
    8b0a:	14 01 00 2d 	swi $r0,[$r2+#0xb4]
    8b0e:	f0 01       	lwi37.sp $r0,[+#0x4]
    8b10:	64 02 00 03 	mtsr $r0,$psw
    8b14:	64 00 00 09 	isb
    8b18:	ec 08       	addi10.sp #0x8
    8b1a:	dd 9e       	ret5 $lp

00008b1c <intc_group31_irq_disable>:
    8b1c:	ef f8       	addi10.sp #-8
    8b1e:	64 12 00 02 	mfsr $r1,$psw
    8b22:	64 02 00 43 	setgie.d
    8b26:	46 3c 00 02 	sethi $r3,#0xc0002
    8b2a:	f1 81       	swi37.sp $r1,[+#0x4]
    8b2c:	04 21 80 2d 	lwi $r2,[$r3+#0xb4]
    8b30:	84 21       	movi55 $r1,#0x1
    8b32:	40 10 80 0c 	sll $r1,$r1,$r0
    8b36:	fe 57       	or33 $r1,$r2
    8b38:	14 11 80 2d 	swi $r1,[$r3+#0xb4]
    8b3c:	84 40       	movi55 $r2,#0x0
    8b3e:	3e 18 2a 50 	addi.gp $r1,#0x2a50
    8b42:	38 20 82 0a 	sw $r2,[$r1+($r0<<#0x2)]
    8b46:	f0 01       	lwi37.sp $r0,[+#0x4]
    8b48:	64 02 00 03 	mtsr $r0,$psw
    8b4c:	64 00 00 09 	isb
    8b50:	ec 08       	addi10.sp #0x8
    8b52:	dd 9e       	ret5 $lp

00008b54 <__udivdi3>:
    8b54:	84 80       	movi55 $r4,#0x0
    8b56:	d5 2d       	j8 8bb0 <__udivmoddi4>

00008b58 <fudiv_qrnnd>:
    8b58:	41 41 40 09 	srli $r20,$r2,#0x10
    8b5c:	97 41       	zeh33 $r5,$r0
    8b5e:	92 10       	srli45 $r0,#0x10
    8b60:	40 40 d0 37 	divr $r4,$r1,$r1,$r20
    8b64:	96 d1       	zeh33 $r3,$r2
    8b66:	40 10 c0 08 	slli $r1,$r1,#0x10
    8b6a:	fe 47       	or33 $r1,$r0
    8b6c:	42 02 0c 24 	mul $r0,$r4,$r3
    8b70:	e2 20       	slt45 $r1,$r0
    8b72:	e8 09       	beqzs8 8b84 <fudiv_qrnnd+0x2c>
    8b74:	9f 21       	subi333 $r4,$r4,#0x1
    8b76:	98 4a       	add333 $r1,$r1,$r2
    8b78:	e2 22       	slt45 $r1,$r2
    8b7a:	e9 05       	bnezs8 8b84 <fudiv_qrnnd+0x2c>
    8b7c:	e2 20       	slt45 $r1,$r0
    8b7e:	e8 03       	beqzs8 8b84 <fudiv_qrnnd+0x2c>
    8b80:	9f 21       	subi333 $r4,$r4,#0x1
    8b82:	98 4a       	add333 $r1,$r1,$r2
    8b84:	9a 48       	sub333 $r1,$r1,$r0
    8b86:	40 10 d0 17 	divr $r1,$r0,$r1,$r20
    8b8a:	40 00 40 08 	slli $r0,$r0,#0x10
    8b8e:	fe 2f       	or33 $r0,$r5
    8b90:	fe cc       	mul33 $r3,$r1
    8b92:	e2 03       	slt45 $r0,$r3
    8b94:	e8 09       	beqzs8 8ba6 <fudiv_qrnnd+0x4e>
    8b96:	98 02       	add333 $r0,$r0,$r2
    8b98:	9e 49       	subi333 $r1,$r1,#0x1
    8b9a:	e2 02       	slt45 $r0,$r2
    8b9c:	e9 05       	bnezs8 8ba6 <fudiv_qrnnd+0x4e>
    8b9e:	e2 03       	slt45 $r0,$r3
    8ba0:	e8 03       	beqzs8 8ba6 <fudiv_qrnnd+0x4e>
    8ba2:	98 02       	add333 $r0,$r0,$r2
    8ba4:	9e 49       	subi333 $r1,$r1,#0x1
    8ba6:	9a 03       	sub333 $r0,$r0,$r3
    8ba8:	40 42 40 08 	slli $r4,$r4,#0x10
    8bac:	fe 67       	or33 $r1,$r4
    8bae:	dd 9e       	ret5 $lp

00008bb0 <__udivmoddi4>:
    8bb0:	3b ff fe bc 	smw.adm $sp,[$sp],$sp,#0xa    ! {$fp, $lp}
    8bb4:	fd 80       	movd44 $r16,$r0
    8bb6:	fd 91       	movd44 $r18,$r2
    8bb8:	83 84       	mov55 $fp,$r4
    8bba:	cb 4d       	bnez38 $r3,8c54 <__udivmoddi4+0xa4>
    8bbc:	e3 b2       	slt45 $r17,$r18
    8bbe:	e8 19       	beqzs8 8bf0 <__udivmoddi4+0x40>
    8bc0:	42 09 00 07 	clz $r0,$r18
    8bc4:	82 a0       	mov55 $r21,$r0
    8bc6:	c0 0d       	beqz38 $r0,8be0 <__udivmoddi4+0x30>
    8bc8:	41 29 00 0c 	sll $r18,$r18,$r0
    8bcc:	52 50 00 20 	subri $r5,$r0,#0x20
    8bd0:	40 58 14 0d 	srl $r5,$r16,$r5
    8bd4:	41 18 80 0c 	sll $r17,$r17,$r0
    8bd8:	41 18 94 04 	or $r17,$r17,$r5
    8bdc:	41 08 00 0c 	sll $r16,$r16,$r0
    8be0:	fd 08       	movd44 $r0,$r16
    8be2:	80 52       	mov55 $r2,$r18
    8be4:	49 ff ff ba 	jal 8b58 <fudiv_qrnnd>
    8be8:	82 c1       	mov55 $r22,$r1
    8bea:	82 00       	mov55 $r16,$r0
    8bec:	86 e0       	movi55 $r23,#0x0
    8bee:	d5 23       	j8 8c34 <__udivmoddi4+0x84>
    8bf0:	c2 28       	beqz38 $r2,8c40 <__udivmoddi4+0x90>
    8bf2:	42 09 00 07 	clz $r0,$r18
    8bf6:	82 a0       	mov55 $r21,$r0
    8bf8:	c8 04       	bnez38 $r0,8c00 <__udivmoddi4+0x50>
    8bfa:	8b b2       	sub45 $r17,$r18
    8bfc:	86 e1       	movi55 $r23,#0x1
    8bfe:	d5 14       	j8 8c26 <__udivmoddi4+0x76>
    8c00:	52 f0 00 20 	subri $r15,$r0,#0x20
    8c04:	41 29 00 0c 	sll $r18,$r18,$r0
    8c08:	80 52       	mov55 $r2,$r18
    8c0a:	40 48 3c 0d 	srl $r4,$r16,$r15
    8c0e:	40 58 80 0c 	sll $r5,$r17,$r0
    8c12:	41 08 00 0c 	sll $r16,$r16,$r0
    8c16:	40 02 90 04 	or $r0,$r5,$r4
    8c1a:	40 18 bc 0d 	srl $r1,$r17,$r15
    8c1e:	49 ff ff 9d 	jal 8b58 <fudiv_qrnnd>
    8c22:	82 e1       	mov55 $r23,$r1
    8c24:	82 20       	mov55 $r17,$r0
    8c26:	fd 08       	movd44 $r0,$r16
    8c28:	80 52       	mov55 $r2,$r18
    8c2a:	49 ff ff 97 	jal 8b58 <fudiv_qrnnd>
    8c2e:	82 c1       	mov55 $r22,$r1
    8c30:	51 00 00 00 	addi $r16,$r0,#0x0
    8c34:	4f c2 00 53 	beqz $fp,8cda <__udivmoddi4+0x12a>
    8c38:	86 20       	movi55 $r17,#0x0
    8c3a:	41 08 54 0d 	srl $r16,$r16,$r21
    8c3e:	d5 4b       	j8 8cd4 <__udivmoddi4+0x124>
    8c40:	41 19 4a 17 	divr $r17,$r16,$r18,$r18
    8c44:	84 20       	movi55 $r1,#0x0
    8c46:	84 00       	movi55 $r0,#0x0
    8c48:	4f c2 00 4c 	beqz $fp,8ce0 <__udivmoddi4+0x130>
    8c4c:	b7 9c       	swi450 $r16,[$fp]
    8c4e:	15 1e 00 01 	swi $r17,[$fp+#0x4]
    8c52:	d5 47       	j8 8ce0 <__udivmoddi4+0x130>
    8c54:	e3 b3       	slt45 $r17,$r19
    8c56:	e9 f7       	bnezs8 8c44 <__udivmoddi4+0x94>
    8c58:	42 09 80 07 	clz $r0,$r19
    8c5c:	82 a0       	mov55 $r21,$r0
    8c5e:	c0 44       	beqz38 $r0,8ce6 <__udivmoddi4+0x136>
    8c60:	52 40 00 20 	subri $r4,$r0,#0x20
    8c64:	40 59 10 0d 	srl $r5,$r18,$r4
    8c68:	40 29 80 0c 	sll $r2,$r19,$r0
    8c6c:	fe af       	or33 $r2,$r5
    8c6e:	82 62       	mov55 $r19,$r2
    8c70:	41 29 00 0c 	sll $r18,$r18,$r0
    8c74:	40 38 10 0d 	srl $r3,$r16,$r4
    8c78:	41 08 00 0c 	sll $r16,$r16,$r0
    8c7c:	40 08 80 0c 	sll $r0,$r17,$r0
    8c80:	40 18 90 0d 	srl $r1,$r17,$r4
    8c84:	fe 1f       	or33 $r0,$r3
    8c86:	49 ff ff 69 	jal 8b58 <fudiv_qrnnd>
    8c8a:	82 c1       	mov55 $r22,$r1
    8c8c:	82 20       	mov55 $r17,$r0
    8c8e:	42 00 c8 69 	mulr64 $r0,$r1,$r18
    8c92:	e3 a1       	slt45 $r17,$r1
    8c94:	e9 05       	bnezs8 8c9e <__udivmoddi4+0xee>
    8c96:	4c 18 c0 0c 	bne $r1,$r17,8cae <__udivmoddi4+0xfe>
    8c9a:	e3 80       	slt45 $r16,$r0
    8c9c:	e8 09       	beqzs8 8cae <__udivmoddi4+0xfe>
    8c9e:	51 6b 7f ff 	addi $r22,$r22,#-1
    8ca2:	8a 33       	sub45 $r1,$r19
    8ca4:	40 30 48 01 	sub $r3,$r0,$r18
    8ca8:	e2 03       	slt45 $r0,$r3
    8caa:	8a 2f       	sub45 $r1,$r15
    8cac:	80 03       	mov55 $r0,$r3
    8cae:	86 e0       	movi55 $r23,#0x0
    8cb0:	4f c2 00 15 	beqz $fp,8cda <__udivmoddi4+0x12a>
    8cb4:	40 08 00 01 	sub $r0,$r16,$r0
    8cb8:	40 18 84 01 	sub $r1,$r17,$r1
    8cbc:	e3 80       	slt45 $r16,$r0
    8cbe:	8a 2f       	sub45 $r1,$r15
    8cc0:	52 4a 80 20 	subri $r4,$r21,#0x20
    8cc4:	41 10 90 0c 	sll $r17,$r1,$r4
    8cc8:	41 00 54 0d 	srl $r16,$r0,$r21
    8ccc:	41 08 44 04 	or $r16,$r16,$r17
    8cd0:	41 10 d4 0d 	srl $r17,$r1,$r21
    8cd4:	b7 9c       	swi450 $r16,[$fp]
    8cd6:	15 1e 00 01 	swi $r17,[$fp+#0x4]
    8cda:	80 16       	mov55 $r0,$r22
    8cdc:	50 1b 80 00 	addi $r1,$r23,#0x0
    8ce0:	3b ff fe 84 	lmw.bim $sp,[$sp],$sp,#0xa    ! {$fp, $lp}
    8ce4:	dd 9e       	ret5 $lp
    8ce6:	e3 f1       	slt45 $r19,$r17
    8ce8:	e9 03       	bnezs8 8cee <__udivmoddi4+0x13e>
    8cea:	e3 92       	slt45 $r16,$r18
    8cec:	e9 09       	bnezs8 8cfe <__udivmoddi4+0x14e>
    8cee:	86 c1       	movi55 $r22,#0x1
    8cf0:	40 48 48 01 	sub $r4,$r16,$r18
    8cf4:	8b b3       	sub45 $r17,$r19
    8cf6:	e3 84       	slt45 $r16,$r4
    8cf8:	8b af       	sub45 $r17,$r15
    8cfa:	82 04       	mov55 $r16,$r4
    8cfc:	d5 02       	j8 8d00 <__udivmoddi4+0x150>
    8cfe:	86 c0       	movi55 $r22,#0x0
    8d00:	86 e0       	movi55 $r23,#0x0
    8d02:	4f c3 ff e9 	bnez $fp,8cd4 <__udivmoddi4+0x124>
    8d06:	d5 ea       	j8 8cda <__udivmoddi4+0x12a>

00008d08 <__umoddi3>:
    8d08:	ef f4       	addi10.sp #-12
    8d0a:	15 ef 80 00 	swi $lp,[$sp+#0x0]
    8d0e:	b1 01       	addri36.sp $r4,#0x4
    8d10:	49 ff ff 50 	jal 8bb0 <__udivmoddi4>
    8d14:	f0 01       	lwi37.sp $r0,[+#0x4]
    8d16:	f1 02       	lwi37.sp $r1,[+#0x8]
    8d18:	0d ef 80 03 	lwi.bi $lp,[$sp],#0xc
    8d1c:	dd 9e       	ret5 $lp
    8d1e:	92 00       	nop16

00008d20 <__fixdfsi>:
    8d20:	6a 00 00 41 	fmfdr $r0,$fd0
    8d24:	40 30 ac 08 	slli $r3,$r1,#0xb
    8d28:	40 40 54 09 	srli $r4,$r0,#0x15
    8d2c:	fe e7       	or33 $r3,$r4
    8d2e:	46 48 00 00 	sethi $r4,#0x80000
    8d32:	fe e7       	or33 $r3,$r4
    8d34:	95 09       	slli333 $r4,$r1,#0x1
    8d36:	92 95       	srli45 $r4,#0x15
    8d38:	52 22 04 1e 	subri $r2,$r4,#0x41e
    8d3c:	4e 27 00 0d 	blez $r2,8d56 <__fixdfsi+0x36>
    8d40:	fa 90       	movpi45 $r4,#0x20
    8d42:	e2 44       	slt45 $r2,$r4
    8d44:	e9 02       	bnezs8 8d48 <__fixdfsi+0x28>
    8d46:	84 60       	movi55 $r3,#0x0
    8d48:	40 31 88 0d 	srl $r3,$r3,$r2
    8d4c:	e4 20       	sltsi45 $r1,#0x0
    8d4e:	e8 02       	beqzs8 8d52 <__fixdfsi+0x32>
    8d50:	fe da       	neg33 $r3,$r3
    8d52:	80 03       	mov55 $r0,$r3
    8d54:	dd 9e       	ret5 $lp
    8d56:	c0 03       	beqz38 $r0,8d5c <__fixdfsi+0x3c>
    8d58:	58 10 80 01 	ori $r1,$r1,#0x1
    8d5c:	46 47 ff 00 	sethi $r4,#0x7ff00
    8d60:	e2 81       	slt45 $r4,$r1
    8d62:	e8 04       	beqzs8 8d6a <__fixdfsi+0x4a>
    8d64:	46 08 00 00 	sethi $r0,#0x80000
    8d68:	dd 9e       	ret5 $lp
    8d6a:	46 07 ff ff 	sethi $r0,#0x7ffff
    8d6e:	58 00 0f ff 	ori $r0,$r0,#0xfff
    8d72:	dd 9e       	ret5 $lp

00008d74 <__fixunsdfsi>:
    8d74:	6a 00 00 41 	fmfdr $r0,$fd0
    8d78:	40 30 ac 08 	slli $r3,$r1,#0xb
    8d7c:	40 40 54 09 	srli $r4,$r0,#0x15
    8d80:	fe e7       	or33 $r3,$r4
    8d82:	46 48 00 00 	sethi $r4,#0x80000
    8d86:	fe e7       	or33 $r3,$r4
    8d88:	95 09       	slli333 $r4,$r1,#0x1
    8d8a:	92 95       	srli45 $r4,#0x15
    8d8c:	52 22 04 1e 	subri $r2,$r4,#0x41e
    8d90:	e4 40       	sltsi45 $r2,#0x0
    8d92:	e9 0c       	bnezs8 8daa <__fixunsdfsi+0x36>
    8d94:	fa 90       	movpi45 $r4,#0x20
    8d96:	e2 44       	slt45 $r2,$r4
    8d98:	e9 02       	bnezs8 8d9c <__fixunsdfsi+0x28>
    8d9a:	84 60       	movi55 $r3,#0x0
    8d9c:	40 31 88 0d 	srl $r3,$r3,$r2
    8da0:	e4 20       	sltsi45 $r1,#0x0
    8da2:	e8 02       	beqzs8 8da6 <__fixunsdfsi+0x32>
    8da4:	fe da       	neg33 $r3,$r3
    8da6:	80 03       	mov55 $r0,$r3
    8da8:	dd 9e       	ret5 $lp
    8daa:	c0 03       	beqz38 $r0,8db0 <__fixunsdfsi+0x3c>
    8dac:	58 10 80 01 	ori $r1,$r1,#0x1
    8db0:	46 47 ff 00 	sethi $r4,#0x7ff00
    8db4:	e2 81       	slt45 $r4,$r1
    8db6:	e8 04       	beqzs8 8dbe <__fixunsdfsi+0x4a>
    8db8:	46 08 00 00 	sethi $r0,#0x80000
    8dbc:	dd 9e       	ret5 $lp
    8dbe:	84 1f       	movi55 $r0,#-1
    8dc0:	dd 9e       	ret5 $lp
    8dc2:	92 00       	nop16

00008dc4 <__popcountsi2>:
    8dc4:	46 15 55 55 	sethi $r1,#0x55555
    8dc8:	50 10 85 55 	addi $r1,$r1,#0x555
    8dcc:	40 10 80 3e 	and_srli $r1,$r1,$r0,#0x1
    8dd0:	46 23 33 33 	sethi $r2,#0x33333
    8dd4:	50 21 03 33 	addi $r2,$r2,#0x333
    8dd8:	8a 01       	sub45 $r0,$r1
    8dda:	40 10 08 02 	and $r1,$r0,$r2
    8dde:	40 01 00 5e 	and_srli $r0,$r2,$r0,#0x2
    8de2:	88 01       	add45 $r0,$r1
    8de4:	46 10 f0 f0 	sethi $r1,#0xf0f0
    8de8:	50 10 8f 0f 	addi $r1,$r1,#0xf0f
    8dec:	40 00 00 9c 	add_srli $r0,$r0,$r0,#0x4
    8df0:	fe 0e       	and33 $r0,$r1
    8df2:	46 10 10 10 	sethi $r1,#0x1010
    8df6:	50 10 81 01 	addi $r1,$r1,#0x101
    8dfa:	fe 0c       	mul33 $r0,$r1
    8dfc:	92 18       	srli45 $r0,#0x18
    8dfe:	dd 9e       	ret5 $lp

00008e00 <__eqdf2>:
    8e00:	fc 20       	push25 $r8,#0    ! {$r6~$r8, $fp, $gp, $lp}
    8e02:	6a 20 00 41 	fmfdr $r2,$fd0
    8e06:	80 22       	mov55 $r1,$r2
    8e08:	80 83       	mov55 $r4,$r3
    8e0a:	6a 20 80 41 	fmfdr $r2,$fd1
    8e0e:	80 c2       	mov55 $r6,$r2
    8e10:	6a 00 07 01 	fmfcsr $r0
    8e14:	40 02 30 08 	slli $r0,$r4,#0xc
    8e18:	40 20 30 09 	srli $r2,$r0,#0xc
    8e1c:	40 02 50 09 	srli $r0,$r4,#0x14
    8e20:	40 71 d0 09 	srli $r7,$r3,#0x14
    8e24:	97 45       	x11b33 $r5,$r0
    8e26:	45 00 07 ff 	movi $r16,#0x7ff
    8e2a:	80 06       	mov55 $r0,$r6
    8e2c:	40 61 b0 08 	slli $r6,$r3,#0xc
    8e30:	92 9f       	srli45 $r4,#0x1f
    8e32:	92 cc       	srli45 $r6,#0xc
    8e34:	97 fd       	x11b33 $r7,$r7
    8e36:	92 7f       	srli45 $r3,#0x1f
    8e38:	4c 58 40 05 	bne $r5,$r16,8e42 <__eqdf2+0x42>
    8e3c:	40 f1 04 04 	or $r15,$r2,$r1
    8e40:	e9 15       	bnezs8 8e6a <__eqdf2+0x6a>
    8e42:	4c 78 40 05 	bne $r7,$r16,8e4c <__eqdf2+0x4c>
    8e46:	40 f3 00 04 	or $r15,$r6,$r0
    8e4a:	e9 10       	bnezs8 8e6a <__eqdf2+0x6a>
    8e4c:	df 0f       	bnes38 $r7,8e6a <__eqdf2+0x6a>
    8e4e:	4c 23 40 0e 	bne $r2,$r6,8e6a <__eqdf2+0x6a>
    8e52:	4c 10 40 0c 	bne $r1,$r0,8e6a <__eqdf2+0x6a>
    8e56:	4c 41 80 08 	beq $r4,$r3,8e66 <__eqdf2+0x66>
    8e5a:	cd 08       	bnez38 $r5,8e6a <__eqdf2+0x6a>
    8e5c:	40 01 04 04 	or $r0,$r2,$r1
    8e60:	40 02 80 06 	slt $r0,$r5,$r0
    8e64:	fc a0       	pop25 $r8,#0    ! {$r6~$r8, $fp, $gp, $lp}
    8e66:	84 00       	movi55 $r0,#0x0
    8e68:	fc a0       	pop25 $r8,#0    ! {$r6~$r8, $fp, $gp, $lp}
    8e6a:	84 01       	movi55 $r0,#0x1
    8e6c:	fc a0       	pop25 $r8,#0    ! {$r6~$r8, $fp, $gp, $lp}

00008e6e <__gedf2>:
    8e6e:	fc 20       	push25 $r8,#0    ! {$r6~$r8, $fp, $gp, $lp}
    8e70:	6a 20 80 41 	fmfdr $r2,$fd1
    8e74:	6a 00 00 41 	fmfdr $r0,$fd0
    8e78:	82 22       	mov55 $r17,$r2
    8e7a:	82 00       	mov55 $r16,$r0
    8e7c:	80 e3       	mov55 $r7,$r3
    8e7e:	6a 00 07 01 	fmfcsr $r0
    8e82:	40 30 d0 09 	srli $r3,$r1,#0x14
    8e86:	40 50 b0 08 	slli $r5,$r1,#0xc
    8e8a:	40 63 b0 08 	slli $r6,$r7,#0xc
    8e8e:	40 23 d0 09 	srli $r2,$r7,#0x14
    8e92:	96 dd       	x11b33 $r3,$r3
    8e94:	45 20 07 ff 	movi $r18,#0x7ff
    8e98:	80 90       	mov55 $r4,$r16
    8e9a:	92 ac       	srli45 $r5,#0xc
    8e9c:	92 3f       	srli45 $r1,#0x1f
    8e9e:	80 11       	mov55 $r0,$r17
    8ea0:	92 cc       	srli45 $r6,#0xc
    8ea2:	96 95       	x11b33 $r2,$r2
    8ea4:	92 ff       	srli45 $r7,#0x1f
    8ea6:	4c 39 40 06 	bne $r3,$r18,8eb2 <__gedf2+0x44>
    8eaa:	40 f2 c0 04 	or $r15,$r5,$r16
    8eae:	e8 0d       	beqzs8 8ec8 <__gedf2+0x5a>
    8eb0:	d5 13       	j8 8ed6 <__gedf2+0x68>
    8eb2:	4c 29 40 06 	bne $r2,$r18,8ebe <__gedf2+0x50>
    8eb6:	40 f3 00 04 	or $r15,$r6,$r0
    8eba:	e8 13       	beqzs8 8ee0 <__gedf2+0x72>
    8ebc:	d5 0d       	j8 8ed6 <__gedf2+0x68>
    8ebe:	cb 07       	bnez38 $r3,8ecc <__gedf2+0x5e>
    8ec0:	ff 2f       	or33 $r4,$r5
    8ec2:	e6 81       	slti45 $r4,#0x1
    8ec4:	ca 0b       	bnez38 $r2,8eda <__gedf2+0x6c>
    8ec6:	d5 05       	j8 8ed0 <__gedf2+0x62>
    8ec8:	4c 21 bf f7 	beq $r2,$r3,8eb6 <__gedf2+0x48>
    8ecc:	ca 0b       	bnez38 $r2,8ee2 <__gedf2+0x74>
    8ece:	81 e2       	mov55 $r15,$r2
    8ed0:	fe 37       	or33 $r0,$r6
    8ed2:	c0 11       	beqz38 $r0,8ef4 <__gedf2+0x86>
    8ed4:	d5 03       	j8 8eda <__gedf2+0x6c>
    8ed6:	84 1e       	movi55 $r0,#-2
    8ed8:	fc a0       	pop25 $r8,#0    ! {$r6~$r8, $fp, $gp, $lp}
    8eda:	e8 04       	beqzs8 8ee2 <__gedf2+0x74>
    8edc:	c7 1a       	beqz38 $r7,8f10 <__gedf2+0xa2>
    8ede:	d5 09       	j8 8ef0 <__gedf2+0x82>
    8ee0:	c3 f0       	beqz38 $r3,8ec0 <__gedf2+0x52>
    8ee2:	4c 13 c0 16 	bne $r1,$r7,8f0e <__gedf2+0xa0>
    8ee6:	e0 43       	slts45 $r2,$r3
    8ee8:	e9 13       	bnezs8 8f0e <__gedf2+0xa0>
    8eea:	e0 62       	slts45 $r3,$r2
    8eec:	e8 06       	beqzs8 8ef8 <__gedf2+0x8a>
    8eee:	c1 11       	beqz38 $r1,8f10 <__gedf2+0xa2>
    8ef0:	84 01       	movi55 $r0,#0x1
    8ef2:	fc a0       	pop25 $r8,#0    ! {$r6~$r8, $fp, $gp, $lp}
    8ef4:	e9 10       	bnezs8 8f14 <__gedf2+0xa6>
    8ef6:	d5 0c       	j8 8f0e <__gedf2+0xa0>
    8ef8:	e2 c5       	slt45 $r6,$r5
    8efa:	e9 0a       	bnezs8 8f0e <__gedf2+0xa0>
    8efc:	de 05       	bnes38 $r6,8f06 <__gedf2+0x98>
    8efe:	e3 b0       	slt45 $r17,$r16
    8f00:	e9 07       	bnezs8 8f0e <__gedf2+0xa0>
    8f02:	e3 91       	slt45 $r16,$r17
    8f04:	d5 02       	j8 8f08 <__gedf2+0x9a>
    8f06:	e2 a6       	slt45 $r5,$r6
    8f08:	e9 f3       	bnezs8 8eee <__gedf2+0x80>
    8f0a:	84 00       	movi55 $r0,#0x0
    8f0c:	fc a0       	pop25 $r8,#0    ! {$r6~$r8, $fp, $gp, $lp}
    8f0e:	c1 f1       	beqz38 $r1,8ef0 <__gedf2+0x82>
    8f10:	84 1f       	movi55 $r0,#-1
    8f12:	fc a0       	pop25 $r8,#0    ! {$r6~$r8, $fp, $gp, $lp}
    8f14:	fc a0       	pop25 $r8,#0    ! {$r6~$r8, $fp, $gp, $lp}

00008f16 <__ledf2>:
    8f16:	fc 20       	push25 $r8,#0    ! {$r6~$r8, $fp, $gp, $lp}
    8f18:	6a 20 80 41 	fmfdr $r2,$fd1
    8f1c:	6a 00 00 41 	fmfdr $r0,$fd0
    8f20:	82 22       	mov55 $r17,$r2
    8f22:	82 00       	mov55 $r16,$r0
    8f24:	80 e3       	mov55 $r7,$r3
    8f26:	6a 00 07 01 	fmfcsr $r0
    8f2a:	40 30 d0 09 	srli $r3,$r1,#0x14
    8f2e:	40 50 b0 08 	slli $r5,$r1,#0xc
    8f32:	40 63 b0 08 	slli $r6,$r7,#0xc
    8f36:	40 23 d0 09 	srli $r2,$r7,#0x14
    8f3a:	96 dd       	x11b33 $r3,$r3
    8f3c:	45 20 07 ff 	movi $r18,#0x7ff
    8f40:	80 90       	mov55 $r4,$r16
    8f42:	92 ac       	srli45 $r5,#0xc
    8f44:	92 3f       	srli45 $r1,#0x1f
    8f46:	80 11       	mov55 $r0,$r17
    8f48:	92 cc       	srli45 $r6,#0xc
    8f4a:	96 95       	x11b33 $r2,$r2
    8f4c:	92 ff       	srli45 $r7,#0x1f
    8f4e:	4c 39 40 06 	bne $r3,$r18,8f5a <__ledf2+0x44>
    8f52:	40 f2 c0 04 	or $r15,$r5,$r16
    8f56:	e9 14       	bnezs8 8f7e <__ledf2+0x68>
    8f58:	d5 0c       	j8 8f70 <__ledf2+0x5a>
    8f5a:	4c 29 40 06 	bne $r2,$r18,8f66 <__ledf2+0x50>
    8f5e:	40 f3 00 04 	or $r15,$r6,$r0
    8f62:	e9 0e       	bnezs8 8f7e <__ledf2+0x68>
    8f64:	d5 12       	j8 8f88 <__ledf2+0x72>
    8f66:	cb 07       	bnez38 $r3,8f74 <__ledf2+0x5e>
    8f68:	ff 2f       	or33 $r4,$r5
    8f6a:	e6 81       	slti45 $r4,#0x1
    8f6c:	ca 0b       	bnez38 $r2,8f82 <__ledf2+0x6c>
    8f6e:	d5 05       	j8 8f78 <__ledf2+0x62>
    8f70:	4c 21 bf f7 	beq $r2,$r3,8f5e <__ledf2+0x48>
    8f74:	ca 0b       	bnez38 $r2,8f8a <__ledf2+0x74>
    8f76:	81 e2       	mov55 $r15,$r2
    8f78:	fe 37       	or33 $r0,$r6
    8f7a:	c0 11       	beqz38 $r0,8f9c <__ledf2+0x86>
    8f7c:	d5 03       	j8 8f82 <__ledf2+0x6c>
    8f7e:	84 02       	movi55 $r0,#0x2
    8f80:	fc a0       	pop25 $r8,#0    ! {$r6~$r8, $fp, $gp, $lp}
    8f82:	e8 04       	beqzs8 8f8a <__ledf2+0x74>
    8f84:	c7 1a       	beqz38 $r7,8fb8 <__ledf2+0xa2>
    8f86:	d5 09       	j8 8f98 <__ledf2+0x82>
    8f88:	c3 f0       	beqz38 $r3,8f68 <__ledf2+0x52>
    8f8a:	4c 13 c0 16 	bne $r1,$r7,8fb6 <__ledf2+0xa0>
    8f8e:	e0 43       	slts45 $r2,$r3
    8f90:	e9 13       	bnezs8 8fb6 <__ledf2+0xa0>
    8f92:	e0 62       	slts45 $r3,$r2
    8f94:	e8 06       	beqzs8 8fa0 <__ledf2+0x8a>
    8f96:	c1 11       	beqz38 $r1,8fb8 <__ledf2+0xa2>
    8f98:	84 01       	movi55 $r0,#0x1
    8f9a:	fc a0       	pop25 $r8,#0    ! {$r6~$r8, $fp, $gp, $lp}
    8f9c:	e9 10       	bnezs8 8fbc <__ledf2+0xa6>
    8f9e:	d5 0c       	j8 8fb6 <__ledf2+0xa0>
    8fa0:	e2 c5       	slt45 $r6,$r5
    8fa2:	e9 0a       	bnezs8 8fb6 <__ledf2+0xa0>
    8fa4:	de 05       	bnes38 $r6,8fae <__ledf2+0x98>
    8fa6:	e3 b0       	slt45 $r17,$r16
    8fa8:	e9 07       	bnezs8 8fb6 <__ledf2+0xa0>
    8faa:	e3 91       	slt45 $r16,$r17
    8fac:	d5 02       	j8 8fb0 <__ledf2+0x9a>
    8fae:	e2 a6       	slt45 $r5,$r6
    8fb0:	e9 f3       	bnezs8 8f96 <__ledf2+0x80>
    8fb2:	84 00       	movi55 $r0,#0x0
    8fb4:	fc a0       	pop25 $r8,#0    ! {$r6~$r8, $fp, $gp, $lp}
    8fb6:	c1 f1       	beqz38 $r1,8f98 <__ledf2+0x82>
    8fb8:	84 1f       	movi55 $r0,#-1
    8fba:	fc a0       	pop25 $r8,#0    ! {$r6~$r8, $fp, $gp, $lp}
    8fbc:	fc a0       	pop25 $r8,#0    ! {$r6~$r8, $fp, $gp, $lp}
	...

00008fc0 <__muldf3>:
    8fc0:	fc 60       	push25 $r14,#0    ! {$r6~$r14, $fp, $gp, $lp}
    8fc2:	6a 00 00 41 	fmfdr $r0,$fd0
    8fc6:	80 40       	mov55 $r2,$r0
    8fc8:	80 a1       	mov55 $r5,$r1
    8fca:	6a 00 80 41 	fmfdr $r0,$fd1
    8fce:	80 c0       	mov55 $r6,$r0
    8fd0:	82 01       	mov55 $r16,$r1
    8fd2:	6b 20 07 01 	fmfcsr $r18
    8fd6:	40 72 d0 09 	srli $r7,$r5,#0x14
    8fda:	40 12 b0 08 	slli $r1,$r5,#0xc
    8fde:	40 a2 fc 09 	srli $r10,$r5,#0x1f
    8fe2:	97 fd       	x11b33 $r7,$r7
    8fe4:	80 02       	mov55 $r0,$r2
    8fe6:	92 2c       	srli45 $r1,#0xc
    8fe8:	82 6a       	mov55 $r19,$r10
    8fea:	c7 0f       	beqz38 $r7,9008 <__muldf3+0x48>
    8fec:	44 30 07 ff 	movi $r3,#0x7ff
    8ff0:	4c 71 80 2d 	beq $r7,$r3,904a <__muldf3+0x8a>
    8ff4:	42 10 d0 08 	bset $r1,$r1,#0x14
    8ff8:	40 51 74 09 	srli $r5,$r2,#0x1d
    8ffc:	40 12 84 64 	or_slli $r1,$r5,$r1,#0x3
    9000:	94 13       	slli333 $r0,$r2,#0x3
    9002:	50 73 fc 01 	addi $r7,$r7,#-1023
    9006:	d5 20       	j8 9046 <__muldf3+0x86>
    9008:	fe 0f       	or33 $r0,$r1
    900a:	c0 28       	beqz38 $r0,905a <__muldf3+0x9a>
    900c:	c1 04       	beqz38 $r1,9014 <__muldf3+0x54>
    900e:	42 50 80 07 	clz $r5,$r1
    9012:	d5 08       	j8 9022 <__muldf3+0x62>
    9014:	42 01 00 07 	clz $r0,$r2
    9018:	50 50 00 20 	addi $r5,$r0,#0x20
    901c:	5e f2 80 28 	sltsi $r15,$r5,#0x28
    9020:	e8 0d       	beqzs8 903a <__muldf3+0x7a>
    9022:	50 f2 ff f8 	addi $r15,$r5,#-8
    9026:	52 72 80 28 	subri $r7,$r5,#0x28
    902a:	40 10 bc 0c 	sll $r1,$r1,$r15
    902e:	40 71 1c 0d 	srl $r7,$r2,$r7
    9032:	fe 7f       	or33 $r1,$r7
    9034:	40 01 3c 0c 	sll $r0,$r2,$r15
    9038:	d5 05       	j8 9042 <__muldf3+0x82>
    903a:	8e 08       	subi45 $r0,#0x8
    903c:	40 11 00 0c 	sll $r1,$r2,$r0
    9040:	80 07       	mov55 $r0,$r7
    9042:	52 72 fc 0d 	subri $r7,$r5,#-1011
    9046:	84 60       	movi55 $r3,#0x0
    9048:	d5 0c       	j8 9060 <__muldf3+0xa0>
    904a:	40 20 88 04 	or $r2,$r1,$r2
    904e:	84 63       	movi55 $r3,#0x3
    9050:	ca 08       	bnez38 $r2,9060 <__muldf3+0xa0>
    9052:	80 22       	mov55 $r1,$r2
    9054:	80 02       	mov55 $r0,$r2
    9056:	84 62       	movi55 $r3,#0x2
    9058:	d5 04       	j8 9060 <__muldf3+0xa0>
    905a:	80 27       	mov55 $r1,$r7
    905c:	80 07       	mov55 $r0,$r7
    905e:	84 61       	movi55 $r3,#0x1
    9060:	40 58 50 09 	srli $r5,$r16,#0x14
    9064:	40 28 30 08 	slli $r2,$r16,#0xc
    9068:	97 6d       	x11b33 $r5,$r5
    906a:	80 86       	mov55 $r4,$r6
    906c:	92 4c       	srli45 $r2,#0xc
    906e:	93 9f       	srli45 $r16,#0x1f
    9070:	c5 0f       	beqz38 $r5,908e <__muldf3+0xce>
    9072:	45 10 07 ff 	movi $r17,#0x7ff
    9076:	4c 58 80 2e 	beq $r5,$r17,90d2 <__muldf3+0x112>
    907a:	42 21 50 08 	bset $r2,$r2,#0x14
    907e:	40 f3 74 09 	srli $r15,$r6,#0x1d
    9082:	40 27 88 64 	or_slli $r2,$r15,$r2,#0x3
    9086:	95 33       	slli333 $r4,$r6,#0x3
    9088:	50 52 fc 01 	addi $r5,$r5,#-1023
    908c:	d5 21       	j8 90ce <__muldf3+0x10e>
    908e:	ff 17       	or33 $r4,$r2
    9090:	c4 26       	beqz38 $r4,90dc <__muldf3+0x11c>
    9092:	c2 04       	beqz38 $r2,909a <__muldf3+0xda>
    9094:	43 11 00 07 	clz $r17,$r2
    9098:	d5 08       	j8 90a8 <__muldf3+0xe8>
    909a:	42 43 00 07 	clz $r4,$r6
    909e:	51 12 00 20 	addi $r17,$r4,#0x20
    90a2:	5e f8 80 28 	sltsi $r15,$r17,#0x28
    90a6:	e8 0e       	beqzs8 90c2 <__muldf3+0x102>
    90a8:	50 48 ff f8 	addi $r4,$r17,#-8
    90ac:	52 f8 80 28 	subri $r15,$r17,#0x28
    90b0:	40 21 10 0c 	sll $r2,$r2,$r4
    90b4:	40 f3 3c 0d 	srl $r15,$r6,$r15
    90b8:	40 27 88 04 	or $r2,$r15,$r2
    90bc:	40 43 10 0c 	sll $r4,$r6,$r4
    90c0:	d5 05       	j8 90ca <__muldf3+0x10a>
    90c2:	8e 88       	subi45 $r4,#0x8
    90c4:	40 23 10 0c 	sll $r2,$r6,$r4
    90c8:	80 85       	mov55 $r4,$r5
    90ca:	52 58 fc 0d 	subri $r5,$r17,#-1011
    90ce:	84 c0       	movi55 $r6,#0x0
    90d0:	d5 0d       	j8 90ea <__muldf3+0x12a>
    90d2:	40 61 18 04 	or $r6,$r2,$r6
    90d6:	c6 07       	beqz38 $r6,90e4 <__muldf3+0x124>
    90d8:	84 c3       	movi55 $r6,#0x3
    90da:	d5 08       	j8 90ea <__muldf3+0x12a>
    90dc:	80 45       	mov55 $r2,$r5
    90de:	80 85       	mov55 $r4,$r5
    90e0:	84 c1       	movi55 $r6,#0x1
    90e2:	d5 04       	j8 90ea <__muldf3+0x12a>
    90e4:	80 46       	mov55 $r2,$r6
    90e6:	80 86       	mov55 $r4,$r6
    90e8:	84 c2       	movi55 $r6,#0x2
    90ea:	41 13 0c 44 	or_slli $r17,$r6,$r3,#0x2
    90ee:	8f a1       	subi45 $r17,#0x1
    90f0:	40 83 94 00 	add $r8,$r7,$r5
    90f4:	e7 af       	slti45 $r17,#0xf
    90f6:	40 a8 28 03 	xor $r10,$r16,$r10
    90fa:	50 54 00 01 	addi $r5,$r8,#0x1
    90fe:	e8 20       	beqzs8 913e <__muldf3+0x17e>
    9100:	44 f0 91 10 	movi $r15,#0x9110
    9104:	39 17 c5 01 	lh $r17,[$r15+($r17<<#0x1)]
    9108:	40 f8 bc 00 	add $r15,$r17,$r15
    910c:	4a 00 3c 00 	jr $r15
    9110:	24 00 24 00 	*unknown*
    9114:	70 01 1e 00 	*unknown*
    9118:	1e 00 e2 02 	*unknown*
    911c:	70 01 1e 00 	*unknown*
    9120:	e2 02       	slt45 $r0,$r2
    9122:	1e 00 70 01 	*unknown*
    9126:	78 01 78 01 	*unknown*
    912a:	78 01 54 01 	*unknown*
    912e:	82 6a       	mov55 $r19,$r10
    9130:	48 00 00 ac 	j 9288 <__muldf3+0x2c8>
    9134:	80 22       	mov55 $r1,$r2
    9136:	80 04       	mov55 $r0,$r4
    9138:	82 6a       	mov55 $r19,$r10
    913a:	48 00 00 a6 	j 9286 <__muldf3+0x2c6>
    913e:	40 30 40 09 	srli $r3,$r0,#0x10
    9142:	40 92 40 09 	srli $r9,$r4,#0x10
    9146:	97 21       	zeh33 $r4,$r4
    9148:	42 f2 0c 24 	mul $r15,$r4,$r3
    914c:	41 00 00 13 	zeh $r16,$r0
    9150:	80 cf       	mov55 $r6,$r15
    9152:	42 02 40 24 	mul $r0,$r4,$r16
    9156:	42 64 c0 73 	maddr32 $r6,$r9,$r16
    915a:	40 63 02 1c 	add_srli $r6,$r6,$r0,#0x10
    915e:	e2 cf       	slt45 $r6,$r15
    9160:	42 74 8c 24 	mul $r7,$r9,$r3
    9164:	e8 04       	beqzs8 916c <__muldf3+0x1ac>
    9166:	45 11 00 00 	movi $r17,#0x10000
    916a:	88 f1       	add45 $r7,$r17
    916c:	41 31 40 09 	srli $r19,$r2,#0x10
    9170:	96 91       	zeh33 $r2,$r2
    9172:	42 f1 0c 24 	mul $r15,$r2,$r3
    9176:	96 01       	zeh33 $r0,$r0
    9178:	40 b0 1a 00 	add_slli $r11,$r0,$r6,#0x10
    917c:	41 13 40 09 	srli $r17,$r6,#0x10
    9180:	42 01 40 24 	mul $r0,$r2,$r16
    9184:	80 cf       	mov55 $r6,$r15
    9186:	42 69 c0 73 	maddr32 $r6,$r19,$r16
    918a:	40 63 02 1c 	add_srli $r6,$r6,$r0,#0x10
    918e:	e2 cf       	slt45 $r6,$r15
    9190:	42 39 8c 24 	mul $r3,$r19,$r3
    9194:	e8 04       	beqzs8 919c <__muldf3+0x1dc>
    9196:	45 01 00 00 	movi $r16,#0x10000
    919a:	88 70       	add45 $r3,$r16
    919c:	96 01       	zeh33 $r0,$r0
    919e:	41 00 1a 00 	add_slli $r16,$r0,$r6,#0x10
    91a2:	40 00 c0 09 	srli $r0,$r1,#0x10
    91a6:	96 49       	zeh33 $r1,$r1
    91a8:	42 c2 04 24 	mul $r12,$r4,$r1
    91ac:	ff 04       	mul33 $r4,$r0
    91ae:	40 31 9a 1c 	add_srli $r3,$r3,$r6,#0x10
    91b2:	80 c4       	mov55 $r6,$r4
    91b4:	42 64 84 73 	maddr32 $r6,$r9,$r1
    91b8:	40 63 32 1c 	add_srli $r6,$r6,$r12,#0x10
    91bc:	e2 c4       	slt45 $r6,$r4
    91be:	40 d8 44 00 	add $r13,$r16,$r17
    91c2:	43 14 80 24 	mul $r17,$r9,$r0
    91c6:	e8 04       	beqzs8 91ce <__muldf3+0x20e>
    91c8:	44 41 00 00 	movi $r4,#0x10000
    91cc:	89 a4       	add45 $r17,$r4
    91ce:	40 46 00 13 	zeh $r4,$r12
    91d2:	40 98 9a 1c 	add_srli $r9,$r17,$r6,#0x10
    91d6:	40 62 1a 00 	add_slli $r6,$r4,$r6,#0x10
    91da:	42 41 04 24 	mul $r4,$r2,$r1
    91de:	fe 84       	mul33 $r2,$r0
    91e0:	43 19 80 24 	mul $r17,$r19,$r0
    91e4:	80 02       	mov55 $r0,$r2
    91e6:	42 09 84 73 	maddr32 $r0,$r19,$r1
    91ea:	41 30 12 1c 	add_srli $r19,$r0,$r4,#0x10
    91ee:	e3 e2       	slt45 $r19,$r2
    91f0:	e8 04       	beqzs8 91f8 <__muldf3+0x238>
    91f2:	44 01 00 00 	movi $r0,#0x10000
    91f6:	89 a0       	add45 $r17,$r0
    91f8:	96 a1       	zeh33 $r2,$r4
    91fa:	88 ed       	add45 $r7,$r13
    91fc:	40 21 4e 00 	add_slli $r2,$r2,$r19,#0x10
    9200:	e2 f0       	slt45 $r7,$r16
    9202:	99 13       	add333 $r4,$r2,$r3
    9204:	40 02 3c 00 	add $r0,$r4,$r15
    9208:	88 e6       	add45 $r7,$r6
    920a:	40 24 80 00 	add $r2,$r9,$r0
    920e:	40 63 98 06 	slt $r6,$r7,$r6
    9212:	41 01 18 00 	add $r16,$r2,$r6
    9216:	e2 0f       	slt45 $r0,$r15
    9218:	40 42 0c 06 	slt $r4,$r4,$r3
    921c:	40 47 90 04 	or $r4,$r15,$r4
    9220:	40 68 18 06 	slt $r6,$r16,$r6
    9224:	e2 49       	slt45 $r2,$r9
    9226:	40 63 3c 04 	or $r6,$r6,$r15
    922a:	40 42 4e 1c 	add_srli $r4,$r4,$r19,#0x10
    922e:	98 66       	add333 $r1,$r4,$r6
    9230:	89 a1       	add45 $r17,$r1
    9232:	40 f5 9d 24 	or_slli $r15,$r11,$r7,#0x9
    9236:	84 40       	movi55 $r2,#0x0
    9238:	40 18 5c 09 	srli $r1,$r16,#0x17
    923c:	e2 4f       	slt45 $r2,$r15
    923e:	40 10 c5 24 	or_slli $r1,$r1,$r17,#0x9
    9242:	40 77 9e f5 	or_srli $r7,$r15,$r7,#0x17
    9246:	42 20 e0 0b 	btst $r2,$r1,#0x18
    924a:	40 03 c1 24 	or_slli $r0,$r7,$r16,#0x9
    924e:	4e 22 00 ef 	beqz $r2,942c <__muldf3+0x46c>
    9252:	96 84       	xlsb33 $r2,$r0
    9254:	40 f1 00 35 	or_srli $r15,$r2,$r0,#0x1
    9258:	40 07 87 e4 	or_slli $r0,$r15,$r1,#0x1f
    925c:	81 05       	mov55 $r8,$r5
    925e:	92 21       	srli45 $r1,#0x1
    9260:	48 00 00 e6 	j 942c <__muldf3+0x46c>
    9264:	46 30 00 80 	sethi $r3,#0x80
    9268:	40 50 8c 02 	and $r5,$r1,$r3
    926c:	4e 52 00 c9 	beqz $r5,93fe <__muldf3+0x43e>
    9270:	fe d6       	and33 $r3,$r2
    9272:	4e 33 00 c6 	bnez $r3,93fe <__muldf3+0x43e>
    9276:	80 22       	mov55 $r1,$r2
    9278:	80 04       	mov55 $r0,$r4
    927a:	82 70       	mov55 $r19,$r16
    927c:	48 00 00 c1 	j 93fe <__muldf3+0x43e>
    9280:	80 22       	mov55 $r1,$r2
    9282:	80 04       	mov55 $r0,$r4
    9284:	82 70       	mov55 $r19,$r16
    9286:	80 66       	mov55 $r3,$r6
    9288:	5a 38 02 04 	bnec $r3,#0x2,9290 <__muldf3+0x2d0>
    928c:	48 00 00 be 	j 9408 <__muldf3+0x448>
    9290:	5a 38 03 04 	bnec $r3,#0x3,9298 <__muldf3+0x2d8>
    9294:	48 00 00 b5 	j 93fe <__muldf3+0x43e>
    9298:	5a 38 01 04 	bnec $r3,#0x1,92a0 <__muldf3+0x2e0>
    929c:	48 00 00 b4 	j 9404 <__muldf3+0x444>
    92a0:	50 22 83 ff 	addi $r2,$r5,#0x3ff
    92a4:	4e 27 00 3f 	blez $r2,9322 <__muldf3+0x362>
    92a8:	54 30 00 07 	andi $r3,$r0,#0x7
    92ac:	c3 19       	beqz38 $r3,92de <__muldf3+0x31e>
    92ae:	54 39 00 03 	andi $r3,$r18,#0x3
    92b2:	5a 30 01 0c 	beqc $r3,#0x1,92ca <__muldf3+0x30a>
    92b6:	c3 04       	beqz38 $r3,92be <__muldf3+0x2fe>
    92b8:	5a 30 02 0c 	beqc $r3,#0x2,92d0 <__muldf3+0x310>
    92bc:	d5 11       	j8 92de <__muldf3+0x31e>
    92be:	54 30 00 0f 	andi $r3,$r0,#0xf
    92c2:	5a 30 04 0e 	beqc $r3,#0x4,92de <__muldf3+0x31e>
    92c6:	9c c4       	addi333 $r3,$r0,#0x4
    92c8:	d5 08       	j8 92d8 <__muldf3+0x318>
    92ca:	4f 33 00 0a 	bnez $r19,92de <__muldf3+0x31e>
    92ce:	d5 03       	j8 92d4 <__muldf3+0x314>
    92d0:	4f 32 00 07 	beqz $r19,92de <__muldf3+0x31e>
    92d4:	50 30 00 08 	addi $r3,$r0,#0x8
    92d8:	e2 60       	slt45 $r3,$r0
    92da:	88 2f       	add45 $r1,$r15
    92dc:	80 03       	mov55 $r0,$r3
    92de:	42 30 e0 0b 	btst $r3,$r1,#0x18
    92e2:	c3 05       	beqz38 $r3,92ec <__muldf3+0x32c>
    92e4:	42 10 e0 09 	bclr $r1,$r1,#0x18
    92e8:	50 22 84 00 	addi $r2,$r5,#0x400
    92ec:	5e f1 07 ff 	sltsi $r15,$r2,#0x7ff
    92f0:	e8 06       	beqzs8 92fc <__muldf3+0x33c>
    92f2:	40 30 f4 08 	slli $r3,$r1,#0x1d
    92f6:	40 01 80 75 	or_srli $r0,$r3,$r0,#0x3
    92fa:	d5 62       	j8 93be <__muldf3+0x3fe>
    92fc:	54 09 00 03 	andi $r0,$r18,#0x3
    9300:	5a 00 01 08 	beqc $r0,#0x1,9310 <__muldf3+0x350>
    9304:	4e 02 00 82 	beqz $r0,9408 <__muldf3+0x448>
    9308:	5a 00 02 09 	beqc $r0,#0x2,931a <__muldf3+0x35a>
    930c:	48 00 00 84 	j 9414 <__muldf3+0x454>
    9310:	4f 33 00 81 	bnez $r19,9412 <__muldf3+0x452>
    9314:	80 33       	mov55 $r1,$r19
    9316:	80 13       	mov55 $r0,$r19
    9318:	d5 7a       	j8 940c <__muldf3+0x44c>
    931a:	4f 32 00 7d 	beqz $r19,9414 <__muldf3+0x454>
    931e:	86 61       	movi55 $r19,#0x1
    9320:	d5 74       	j8 9408 <__muldf3+0x448>
    9322:	52 22 fc 02 	subri $r2,$r5,#-1022
    9326:	5e f1 00 39 	sltsi $r15,$r2,#0x39
    932a:	e8 4c       	beqzs8 93c2 <__muldf3+0x402>
    932c:	5e f1 00 20 	sltsi $r15,$r2,#0x20
    9330:	e8 12       	beqzs8 9354 <__muldf3+0x394>
    9332:	50 52 84 1e 	addi $r5,$r5,#0x41e
    9336:	40 30 94 0c 	sll $r3,$r1,$r5
    933a:	40 f0 08 0d 	srl $r15,$r0,$r2
    933e:	40 50 14 0c 	sll $r5,$r0,$r5
    9342:	84 80       	movi55 $r4,#0x0
    9344:	40 37 8c 04 	or $r3,$r15,$r3
    9348:	e2 85       	slt45 $r4,$r5
    934a:	40 31 bc 04 	or $r3,$r3,$r15
    934e:	40 10 88 0d 	srl $r1,$r1,$r2
    9352:	d5 13       	j8 9378 <__muldf3+0x3b8>
    9354:	52 32 fb e2 	subri $r3,$r5,#-1054
    9358:	40 40 8c 0d 	srl $r4,$r1,$r3
    935c:	5a 20 20 07 	beqc $r2,#0x20,936a <__muldf3+0x3aa>
    9360:	50 52 84 3e 	addi $r5,$r5,#0x43e
    9364:	40 10 94 0c 	sll $r1,$r1,$r5
    9368:	d5 02       	j8 936c <__muldf3+0x3ac>
    936a:	84 20       	movi55 $r1,#0x0
    936c:	40 f0 80 04 	or $r15,$r1,$r0
    9370:	84 20       	movi55 $r1,#0x0
    9372:	e2 2f       	slt45 $r1,$r15
    9374:	40 37 90 04 	or $r3,$r15,$r4
    9378:	54 01 80 07 	andi $r0,$r3,#0x7
    937c:	c0 19       	beqz38 $r0,93ae <__muldf3+0x3ee>
    937e:	54 09 00 03 	andi $r0,$r18,#0x3
    9382:	5a 00 01 0c 	beqc $r0,#0x1,939a <__muldf3+0x3da>
    9386:	c0 04       	beqz38 $r0,938e <__muldf3+0x3ce>
    9388:	5a 00 02 0c 	beqc $r0,#0x2,93a0 <__muldf3+0x3e0>
    938c:	d5 11       	j8 93ae <__muldf3+0x3ee>
    938e:	54 01 80 0f 	andi $r0,$r3,#0xf
    9392:	5a 00 04 0e 	beqc $r0,#0x4,93ae <__muldf3+0x3ee>
    9396:	9c 1c       	addi333 $r0,$r3,#0x4
    9398:	d5 08       	j8 93a8 <__muldf3+0x3e8>
    939a:	4f 33 00 0a 	bnez $r19,93ae <__muldf3+0x3ee>
    939e:	d5 03       	j8 93a4 <__muldf3+0x3e4>
    93a0:	4f 32 00 07 	beqz $r19,93ae <__muldf3+0x3ee>
    93a4:	50 01 80 08 	addi $r0,$r3,#0x8
    93a8:	e2 03       	slt45 $r0,$r3
    93aa:	88 2f       	add45 $r1,$r15
    93ac:	80 60       	mov55 $r3,$r0
    93ae:	46 20 08 00 	sethi $r2,#0x800
    93b2:	fe 8e       	and33 $r2,$r1
    93b4:	ca 35       	bnez38 $r2,941e <__muldf3+0x45e>
    93b6:	40 f0 f4 08 	slli $r15,$r1,#0x1d
    93ba:	40 07 8c 75 	or_srli $r0,$r15,$r3,#0x3
    93be:	92 23       	srli45 $r1,#0x3
    93c0:	d5 3a       	j8 9434 <__muldf3+0x474>
    93c2:	fe 0f       	or33 $r0,$r1
    93c4:	c0 31       	beqz38 $r0,9426 <__muldf3+0x466>
    93c6:	54 09 00 03 	andi $r0,$r18,#0x3
    93ca:	5a 00 01 08 	beqc $r0,#0x1,93da <__muldf3+0x41a>
    93ce:	c0 04       	beqz38 $r0,93d6 <__muldf3+0x416>
    93d0:	5a 00 02 08 	beqc $r0,#0x2,93e0 <__muldf3+0x420>
    93d4:	d5 08       	j8 93e4 <__muldf3+0x424>
    93d6:	84 05       	movi55 $r0,#0x5
    93d8:	d5 09       	j8 93ea <__muldf3+0x42a>
    93da:	4f 32 00 07 	beqz $r19,93e8 <__muldf3+0x428>
    93de:	d5 06       	j8 93ea <__muldf3+0x42a>
    93e0:	4f 33 00 04 	bnez $r19,93e8 <__muldf3+0x428>
    93e4:	84 01       	movi55 $r0,#0x1
    93e6:	d5 02       	j8 93ea <__muldf3+0x42a>
    93e8:	84 09       	movi55 $r0,#0x9
    93ea:	84 20       	movi55 $r1,#0x0
    93ec:	92 03       	srli45 $r0,#0x3
    93ee:	80 41       	mov55 $r2,$r1
    93f0:	d5 22       	j8 9434 <__muldf3+0x474>
    93f2:	46 10 00 ff 	sethi $r1,#0xff
    93f6:	50 10 8f ff 	addi $r1,$r1,#0xfff
    93fa:	84 1f       	movi55 $r0,#-1
    93fc:	86 60       	movi55 $r19,#0x0
    93fe:	42 10 cc 08 	bset $r1,$r1,#0x13
    9402:	d5 05       	j8 940c <__muldf3+0x44c>
    9404:	84 00       	movi55 $r0,#0x0
    9406:	d5 10       	j8 9426 <__muldf3+0x466>
    9408:	84 00       	movi55 $r0,#0x0
    940a:	80 20       	mov55 $r1,$r0
    940c:	44 20 07 ff 	movi $r2,#0x7ff
    9410:	d5 12       	j8 9434 <__muldf3+0x474>
    9412:	82 60       	mov55 $r19,$r0
    9414:	84 1f       	movi55 $r0,#-1
    9416:	80 20       	mov55 $r1,$r0
    9418:	44 20 07 fe 	movi $r2,#0x7fe
    941c:	d5 0c       	j8 9434 <__muldf3+0x474>
    941e:	84 20       	movi55 $r1,#0x0
    9420:	80 01       	mov55 $r0,$r1
    9422:	84 41       	movi55 $r2,#0x1
    9424:	d5 08       	j8 9434 <__muldf3+0x474>
    9426:	80 20       	mov55 $r1,$r0
    9428:	80 40       	mov55 $r2,$r0
    942a:	d5 05       	j8 9434 <__muldf3+0x474>
    942c:	80 a8       	mov55 $r5,$r8
    942e:	82 6a       	mov55 $r19,$r10
    9430:	48 ff ff 38 	j 92a0 <__muldf3+0x2e0>
    9434:	84 80       	movi55 $r4,#0x0
    9436:	80 a4       	mov55 $r5,$r4
    9438:	80 80       	mov55 $r4,$r0
    943a:	40 02 d0 09 	srli $r0,$r5,#0x14
    943e:	40 00 50 08 	slli $r0,$r0,#0x14
    9442:	40 10 b0 08 	slli $r1,$r1,#0xc
    9446:	40 10 05 95 	or_srli $r1,$r0,$r1,#0xc
    944a:	46 08 00 ff 	sethi $r0,#0x800ff
    944e:	50 00 0f ff 	addi $r0,$r0,#0xfff
    9452:	96 95       	x11b33 $r2,$r2
    9454:	fe 46       	and33 $r1,$r0
    9456:	40 10 8a 84 	or_slli $r1,$r1,$r2,#0x14
    945a:	42 10 fc 09 	bclr $r1,$r1,#0x1f
    945e:	40 50 cf e4 	or_slli $r5,$r1,$r19,#0x1f
    9462:	6a 40 00 49 	fmtdr $r4,$fd0
    9466:	fc e0       	pop25 $r14,#0    ! {$r6~$r14, $fp, $gp, $lp}

00009468 <__subdf3>:
    9468:	fc 60       	push25 $r14,#0    ! {$r6~$r14, $fp, $gp, $lp}
    946a:	6a 00 00 41 	fmfdr $r0,$fd0
    946e:	80 60       	mov55 $r3,$r0
    9470:	80 81       	mov55 $r4,$r1
    9472:	6a 00 80 41 	fmfdr $r0,$fd1
    9476:	80 c0       	mov55 $r6,$r0
    9478:	81 21       	mov55 $r9,$r1
    947a:	6a a0 07 01 	fmfcsr $r10
    947e:	40 52 50 09 	srli $r5,$r4,#0x14
    9482:	40 f2 30 08 	slli $r15,$r4,#0xc
    9486:	40 01 f4 09 	srli $r0,$r3,#0x1d
    948a:	54 b2 87 ff 	andi $r11,$r5,#0x7ff
    948e:	40 50 d0 09 	srli $r5,$r1,#0x14
    9492:	40 00 3d 35 	or_srli $r0,$r0,$r15,#0x9
    9496:	40 70 fc 09 	srli $r7,$r1,#0x1f
    949a:	40 f0 b0 08 	slli $r15,$r1,#0xc
    949e:	97 6d       	x11b33 $r5,$r5
    94a0:	40 13 74 09 	srli $r1,$r6,#0x1d
    94a4:	44 20 07 ff 	movi $r2,#0x7ff
    94a8:	92 9f       	srli45 $r4,#0x1f
    94aa:	94 db       	slli333 $r3,$r3,#0x3
    94ac:	40 10 bd 35 	or_srli $r1,$r1,$r15,#0x9
    94b0:	40 83 0c 08 	slli $r8,$r6,#0x3
    94b4:	da 04       	bnes38 $r2,94bc <__subdf3+0x54>
    94b6:	40 20 a0 04 	or $r2,$r1,$r8
    94ba:	ca 03       	bnez38 $r2,94c0 <__subdf3+0x58>
    94bc:	56 73 80 01 	xori $r7,$r7,#0x1
    94c0:	44 60 07 ff 	movi $r6,#0x7ff
    94c4:	40 25 94 01 	sub $r2,$r11,$r5
    94c8:	4c 43 c1 25 	bne $r4,$r7,9712 <__subdf3+0x2aa>
    94cc:	82 42       	mov55 $r18,$r2
    94ce:	4e 27 00 51 	blez $r2,9570 <__subdf3+0x108>
    94d2:	cd 13       	bnez38 $r5,94f8 <__subdf3+0x90>
    94d4:	40 50 a0 04 	or $r5,$r1,$r8
    94d8:	4e 52 02 b7 	beqz $r5,9a46 <__subdf3+0x5de>
    94dc:	51 21 7f ff 	addi $r18,$r2,#-1
    94e0:	4f 23 00 08 	bnez $r18,94f0 <__subdf3+0x88>
    94e4:	40 74 0c 00 	add $r7,$r8,$r3
    94e8:	88 01       	add45 $r0,$r1
    94ea:	e2 e3       	slt45 $r7,$r3
    94ec:	88 0f       	add45 $r0,$r15
    94ee:	d5 3e       	j8 956a <__subdf3+0x102>
    94f0:	4c b3 40 08 	bne $r11,$r6,9500 <__subdf3+0x98>
    94f4:	48 00 02 a9 	j 9a46 <__subdf3+0x5de>
    94f8:	4c b3 02 a7 	beq $r11,$r6,9a46 <__subdf3+0x5de>
    94fc:	42 10 dc 08 	bset $r1,$r1,#0x17
    9500:	5e f9 00 39 	sltsi $r15,$r18,#0x39
    9504:	e8 28       	beqzs8 9554 <__subdf3+0xec>
    9506:	5e f9 00 20 	sltsi $r15,$r18,#0x20
    950a:	e8 13       	beqzs8 9530 <__subdf3+0xc8>
    950c:	53 19 00 20 	subri $r17,$r18,#0x20
    9510:	40 70 c4 0c 	sll $r7,$r1,$r17
    9514:	40 24 48 0d 	srl $r2,$r8,$r18
    9518:	40 f3 88 04 	or $r15,$r7,$r2
    951c:	85 20       	movi55 $r9,#0x0
    951e:	40 74 44 0c 	sll $r7,$r8,$r17
    9522:	40 74 9c 06 	slt $r7,$r9,$r7
    9526:	40 77 9c 04 	or $r7,$r15,$r7
    952a:	40 f0 c8 0d 	srl $r15,$r1,$r18
    952e:	d5 18       	j8 955e <__subdf3+0xf6>
    9530:	40 90 c8 0d 	srl $r9,$r1,$r18
    9534:	5b 20 20 07 	beqc $r18,#0x20,9542 <__subdf3+0xda>
    9538:	53 29 00 40 	subri $r18,$r18,#0x40
    953c:	41 20 c8 0c 	sll $r18,$r1,$r18
    9540:	d5 02       	j8 9544 <__subdf3+0xdc>
    9542:	86 40       	movi55 $r18,#0x0
    9544:	40 79 20 04 	or $r7,$r18,$r8
    9548:	84 20       	movi55 $r1,#0x0
    954a:	e2 27       	slt45 $r1,$r7
    954c:	40 77 a4 04 	or $r7,$r15,$r9
    9550:	81 e1       	mov55 $r15,$r1
    9552:	d5 06       	j8 955e <__subdf3+0xf6>
    9554:	40 70 a0 04 	or $r7,$r1,$r8
    9558:	85 e0       	movi55 $r15,#0x0
    955a:	40 77 9c 06 	slt $r7,$r15,$r7
    955e:	88 e3       	add45 $r7,$r3
    9560:	41 27 80 00 	add $r18,$r15,$r0
    9564:	e2 e3       	slt45 $r7,$r3
    9566:	40 09 3c 00 	add $r0,$r18,$r15
    956a:	80 67       	mov55 $r3,$r7
    956c:	48 00 00 ac 	j 96c4 <__subdf3+0x25c>
    9570:	c2 4b       	beqz38 $r2,9606 <__subdf3+0x19e>
    9572:	4e b3 00 11 	bnez $r11,9594 <__subdf3+0x12c>
    9576:	40 70 0c 04 	or $r7,$r0,$r3
    957a:	4e 72 02 33 	beqz $r7,99e0 <__subdf3+0x578>
    957e:	fe 93       	not33 $r2,$r2
    9580:	ca 07       	bnez38 $r2,958e <__subdf3+0x126>
    9582:	88 68       	add45 $r3,$r8
    9584:	88 01       	add45 $r0,$r1
    9586:	40 71 a0 06 	slt $r7,$r3,$r8
    958a:	88 07       	add45 $r0,$r7
    958c:	d5 3b       	j8 9602 <__subdf3+0x19a>
    958e:	de 08       	bnes38 $r6,959e <__subdf3+0x136>
    9590:	48 00 02 28 	j 99e0 <__subdf3+0x578>
    9594:	4c 53 02 26 	beq $r5,$r6,99e0 <__subdf3+0x578>
    9598:	fe 92       	neg33 $r2,$r2
    959a:	42 00 5c 08 	bset $r0,$r0,#0x17
    959e:	5e f1 00 39 	sltsi $r15,$r2,#0x39
    95a2:	e8 26       	beqzs8 95ee <__subdf3+0x186>
    95a4:	5e f1 00 20 	sltsi $r15,$r2,#0x20
    95a8:	e8 13       	beqzs8 95ce <__subdf3+0x166>
    95aa:	52 71 00 20 	subri $r7,$r2,#0x20
    95ae:	40 61 88 0d 	srl $r6,$r3,$r2
    95b2:	85 20       	movi55 $r9,#0x0
    95b4:	40 f0 1c 0c 	sll $r15,$r0,$r7
    95b8:	40 31 9c 0c 	sll $r3,$r3,$r7
    95bc:	40 34 8c 06 	slt $r3,$r9,$r3
    95c0:	40 f7 98 04 	or $r15,$r15,$r6
    95c4:	40 37 8c 04 	or $r3,$r15,$r3
    95c8:	40 90 08 0d 	srl $r9,$r0,$r2
    95cc:	d5 16       	j8 95f8 <__subdf3+0x190>
    95ce:	40 60 08 0d 	srl $r6,$r0,$r2
    95d2:	5a 20 20 07 	beqc $r2,#0x20,95e0 <__subdf3+0x178>
    95d6:	52 21 00 40 	subri $r2,$r2,#0x40
    95da:	40 20 08 0c 	sll $r2,$r0,$r2
    95de:	d5 02       	j8 95e2 <__subdf3+0x17a>
    95e0:	84 40       	movi55 $r2,#0x0
    95e2:	fe d7       	or33 $r3,$r2
    95e4:	84 40       	movi55 $r2,#0x0
    95e6:	e2 43       	slt45 $r2,$r3
    95e8:	40 37 98 04 	or $r3,$r15,$r6
    95ec:	d5 05       	j8 95f6 <__subdf3+0x18e>
    95ee:	fe c7       	or33 $r3,$r0
    95f0:	84 40       	movi55 $r2,#0x0
    95f2:	40 31 0c 06 	slt $r3,$r2,$r3
    95f6:	81 22       	mov55 $r9,$r2
    95f8:	88 68       	add45 $r3,$r8
    95fa:	89 21       	add45 $r9,$r1
    95fc:	e2 68       	slt45 $r3,$r8
    95fe:	40 04 bc 00 	add $r0,$r9,$r15
    9602:	81 65       	mov55 $r11,$r5
    9604:	d5 60       	j8 96c4 <__subdf3+0x25c>
    9606:	50 55 80 01 	addi $r5,$r11,#0x1
    960a:	97 ed       	x11b33 $r7,$r5
    960c:	e4 e2       	sltsi45 $r7,#0x2
    960e:	e8 38       	beqzs8 967e <__subdf3+0x216>
    9610:	40 20 0c 04 	or $r2,$r0,$r3
    9614:	4e b3 00 17 	bnez $r11,9642 <__subdf3+0x1da>
    9618:	4e 22 01 e7 	beqz $r2,99e6 <__subdf3+0x57e>
    961c:	40 20 a0 04 	or $r2,$r1,$r8
    9620:	4e 22 02 13 	beqz $r2,9a46 <__subdf3+0x5de>
    9624:	40 74 0c 00 	add $r7,$r8,$r3
    9628:	88 01       	add45 $r0,$r1
    962a:	e2 e3       	slt45 $r7,$r3
    962c:	88 0f       	add45 $r0,$r15
    962e:	42 10 5c 0b 	btst $r1,$r0,#0x17
    9632:	4e 12 01 dd 	beqz $r1,99ec <__subdf3+0x584>
    9636:	42 00 5c 09 	bclr $r0,$r0,#0x17
    963a:	80 67       	mov55 $r3,$r7
    963c:	85 61       	movi55 $r11,#0x1
    963e:	48 00 02 04 	j 9a46 <__subdf3+0x5de>
    9642:	4e 22 01 d7 	beqz $r2,99f0 <__subdf3+0x588>
    9646:	40 20 a0 04 	or $r2,$r1,$r8
    964a:	4e 22 01 fb 	beqz $r2,9a40 <__subdf3+0x5d8>
    964e:	40 50 0c 09 	srli $r5,$r0,#0x3
    9652:	46 20 00 80 	sethi $r2,#0x80
    9656:	40 f0 74 08 	slli $r15,$r0,#0x1d
    965a:	40 02 88 02 	and $r0,$r5,$r2
    965e:	40 37 8c 75 	or_srli $r3,$r15,$r3,#0x3
    9662:	4e 02 01 43 	beqz $r0,98e8 <__subdf3+0x480>
    9666:	40 00 8c 09 	srli $r0,$r1,#0x3
    966a:	fe 86       	and33 $r2,$r0
    966c:	4e 23 01 3e 	bnez $r2,98e8 <__subdf3+0x480>
    9670:	40 30 f4 08 	slli $r3,$r1,#0x1d
    9674:	40 31 a0 75 	or_srli $r3,$r3,$r8,#0x3
    9678:	80 a0       	mov55 $r5,$r0
    967a:	48 00 01 37 	j 98e8 <__subdf3+0x480>
    967e:	d6 0f       	beqs38 $r6,969c <__subdf3+0x234>
    9680:	40 74 0c 00 	add $r7,$r8,$r3
    9684:	88 01       	add45 $r0,$r1
    9686:	e2 e3       	slt45 $r7,$r3
    9688:	40 90 3c 00 	add $r9,$r0,$r15
    968c:	40 34 fc 08 	slli $r3,$r9,#0x1f
    9690:	40 31 9c 35 	or_srli $r3,$r3,$r7,#0x1
    9694:	40 04 84 09 	srli $r0,$r9,#0x1
    9698:	48 00 01 8b 	j 99ae <__subdf3+0x546>
    969c:	54 15 00 03 	andi $r1,$r10,#0x3
    96a0:	4e 12 01 ab 	beqz $r1,99f6 <__subdf3+0x58e>
    96a4:	5a 18 01 06 	bnec $r1,#0x1,96b0 <__subdf3+0x248>
    96a8:	4e 43 01 ab 	bnez $r4,99fe <__subdf3+0x596>
    96ac:	81 65       	mov55 $r11,$r5
    96ae:	d5 26       	j8 96fa <__subdf3+0x292>
    96b0:	5a 10 02 04 	beqc $r1,#0x2,96b8 <__subdf3+0x250>
    96b4:	48 00 01 ab 	j 9a0a <__subdf3+0x5a2>
    96b8:	4e 42 01 a9 	beqz $r4,9a0a <__subdf3+0x5a2>
    96bc:	81 65       	mov55 $r11,$r5
    96be:	80 02       	mov55 $r0,$r2
    96c0:	48 00 01 ab 	j 9a16 <__subdf3+0x5ae>
    96c4:	42 10 5c 0b 	btst $r1,$r0,#0x17
    96c8:	4e 12 01 bf 	beqz $r1,9a46 <__subdf3+0x5de>
    96cc:	8d 61       	addi45 $r11,#0x1
    96ce:	44 10 07 ff 	movi $r1,#0x7ff
    96d2:	4c b0 80 0c 	beq $r11,$r1,96ea <__subdf3+0x282>
    96d6:	96 9c       	xlsb33 $r2,$r3
    96d8:	42 00 5c 09 	bclr $r0,$r0,#0x17
    96dc:	40 31 0c 35 	or_srli $r3,$r2,$r3,#0x1
    96e0:	40 31 83 e4 	or_slli $r3,$r3,$r0,#0x1f
    96e4:	92 01       	srli45 $r0,#0x1
    96e6:	48 00 01 b0 	j 9a46 <__subdf3+0x5de>
    96ea:	54 15 00 03 	andi $r1,$r10,#0x3
    96ee:	4e 12 01 85 	beqz $r1,99f8 <__subdf3+0x590>
    96f2:	5a 18 01 08 	bnec $r1,#0x1,9702 <__subdf3+0x29a>
    96f6:	4e 43 01 84 	bnez $r4,99fe <__subdf3+0x596>
    96fa:	80 04       	mov55 $r0,$r4
    96fc:	80 64       	mov55 $r3,$r4
    96fe:	48 00 01 bd 	j 9a78 <__subdf3+0x610>
    9702:	5a 10 02 04 	beqc $r1,#0x2,970a <__subdf3+0x2a2>
    9706:	48 00 01 82 	j 9a0a <__subdf3+0x5a2>
    970a:	4e 43 01 85 	bnez $r4,9a14 <__subdf3+0x5ac>
    970e:	48 00 01 7e 	j 9a0a <__subdf3+0x5a2>
    9712:	82 22       	mov55 $r17,$r2
    9714:	4e 27 00 51 	blez $r2,97b6 <__subdf3+0x34e>
    9718:	cd 13       	bnez38 $r5,973e <__subdf3+0x2d6>
    971a:	40 50 a0 04 	or $r5,$r1,$r8
    971e:	4e 52 01 94 	beqz $r5,9a46 <__subdf3+0x5de>
    9722:	51 11 7f ff 	addi $r17,$r2,#-1
    9726:	4f 13 00 08 	bnez $r17,9736 <__subdf3+0x2ce>
    972a:	40 71 a0 01 	sub $r7,$r3,$r8
    972e:	8a 01       	sub45 $r0,$r1
    9730:	e2 67       	slt45 $r3,$r7
    9732:	8a 0f       	sub45 $r0,$r15
    9734:	d5 3d       	j8 97ae <__subdf3+0x346>
    9736:	4c b3 40 08 	bne $r11,$r6,9746 <__subdf3+0x2de>
    973a:	48 00 01 86 	j 9a46 <__subdf3+0x5de>
    973e:	4c b3 01 84 	beq $r11,$r6,9a46 <__subdf3+0x5de>
    9742:	42 10 dc 08 	bset $r1,$r1,#0x17
    9746:	5e f8 80 39 	sltsi $r15,$r17,#0x39
    974a:	e8 27       	beqzs8 9798 <__subdf3+0x330>
    974c:	5e f8 80 20 	sltsi $r15,$r17,#0x20
    9750:	e8 13       	beqzs8 9776 <__subdf3+0x30e>
    9752:	53 28 80 20 	subri $r18,$r17,#0x20
    9756:	40 70 c8 0c 	sll $r7,$r1,$r18
    975a:	40 24 44 0d 	srl $r2,$r8,$r17
    975e:	40 f3 88 04 	or $r15,$r7,$r2
    9762:	85 20       	movi55 $r9,#0x0
    9764:	40 74 48 0c 	sll $r7,$r8,$r18
    9768:	40 74 9c 06 	slt $r7,$r9,$r7
    976c:	40 f7 9c 04 	or $r15,$r15,$r7
    9770:	41 10 c4 0d 	srl $r17,$r1,$r17
    9774:	d5 16       	j8 97a0 <__subdf3+0x338>
    9776:	40 90 c4 0d 	srl $r9,$r1,$r17
    977a:	5b 10 20 07 	beqc $r17,#0x20,9788 <__subdf3+0x320>
    977e:	53 18 80 40 	subri $r17,$r17,#0x40
    9782:	41 10 c4 0c 	sll $r17,$r1,$r17
    9786:	d5 02       	j8 978a <__subdf3+0x322>
    9788:	86 20       	movi55 $r17,#0x0
    978a:	40 78 a0 04 	or $r7,$r17,$r8
    978e:	86 20       	movi55 $r17,#0x0
    9790:	e3 a7       	slt45 $r17,$r7
    9792:	40 f7 a4 04 	or $r15,$r15,$r9
    9796:	d5 05       	j8 97a0 <__subdf3+0x338>
    9798:	40 70 a0 04 	or $r7,$r1,$r8
    979c:	86 20       	movi55 $r17,#0x0
    979e:	e3 a7       	slt45 $r17,$r7
    97a0:	40 71 bc 01 	sub $r7,$r3,$r15
    97a4:	41 10 44 01 	sub $r17,$r0,$r17
    97a8:	e2 67       	slt45 $r3,$r7
    97aa:	40 08 bc 01 	sub $r0,$r17,$r15
    97ae:	80 67       	mov55 $r3,$r7
    97b0:	80 e4       	mov55 $r7,$r4
    97b2:	48 00 00 c0 	j 9932 <__subdf3+0x4ca>
    97b6:	c2 4c       	beqz38 $r2,984e <__subdf3+0x3e6>
    97b8:	4e b3 00 12 	bnez $r11,97dc <__subdf3+0x374>
    97bc:	40 40 0c 04 	or $r4,$r0,$r3
    97c0:	4e 42 01 2e 	beqz $r4,9a1c <__subdf3+0x5b4>
    97c4:	fe 93       	not33 $r2,$r2
    97c6:	ca 08       	bnez38 $r2,97d6 <__subdf3+0x36e>
    97c8:	40 34 0c 01 	sub $r3,$r8,$r3
    97cc:	9a 08       	sub333 $r0,$r1,$r0
    97ce:	40 84 0c 06 	slt $r8,$r8,$r3
    97d2:	8a 08       	sub45 $r0,$r8
    97d4:	d5 3b       	j8 984a <__subdf3+0x3e2>
    97d6:	de 08       	bnes38 $r6,97e6 <__subdf3+0x37e>
    97d8:	48 00 01 22 	j 9a1c <__subdf3+0x5b4>
    97dc:	4c 53 01 20 	beq $r5,$r6,9a1c <__subdf3+0x5b4>
    97e0:	fe 92       	neg33 $r2,$r2
    97e2:	42 00 5c 08 	bset $r0,$r0,#0x17
    97e6:	5e f1 00 39 	sltsi $r15,$r2,#0x39
    97ea:	e8 26       	beqzs8 9836 <__subdf3+0x3ce>
    97ec:	5e f1 00 20 	sltsi $r15,$r2,#0x20
    97f0:	e8 13       	beqzs8 9816 <__subdf3+0x3ae>
    97f2:	52 41 00 20 	subri $r4,$r2,#0x20
    97f6:	40 f0 10 0c 	sll $r15,$r0,$r4
    97fa:	40 61 88 0d 	srl $r6,$r3,$r2
    97fe:	40 31 90 0c 	sll $r3,$r3,$r4
    9802:	84 80       	movi55 $r4,#0x0
    9804:	40 32 0c 06 	slt $r3,$r4,$r3
    9808:	40 f7 98 04 	or $r15,$r15,$r6
    980c:	40 f7 8c 04 	or $r15,$r15,$r3
    9810:	40 40 08 0d 	srl $r4,$r0,$r2
    9814:	d5 15       	j8 983e <__subdf3+0x3d6>
    9816:	40 40 08 0d 	srl $r4,$r0,$r2
    981a:	5a 20 20 07 	beqc $r2,#0x20,9828 <__subdf3+0x3c0>
    981e:	52 21 00 40 	subri $r2,$r2,#0x40
    9822:	40 20 08 0c 	sll $r2,$r0,$r2
    9826:	d5 02       	j8 982a <__subdf3+0x3c2>
    9828:	84 40       	movi55 $r2,#0x0
    982a:	fe d7       	or33 $r3,$r2
    982c:	84 40       	movi55 $r2,#0x0
    982e:	e2 43       	slt45 $r2,$r3
    9830:	40 f7 90 04 	or $r15,$r15,$r4
    9834:	d5 04       	j8 983c <__subdf3+0x3d4>
    9836:	fe c7       	or33 $r3,$r0
    9838:	84 40       	movi55 $r2,#0x0
    983a:	e2 43       	slt45 $r2,$r3
    983c:	80 82       	mov55 $r4,$r2
    983e:	40 34 3c 01 	sub $r3,$r8,$r15
    9842:	9b 0c       	sub333 $r4,$r1,$r4
    9844:	e3 03       	slt45 $r8,$r3
    9846:	40 02 3c 01 	sub $r0,$r4,$r15
    984a:	81 65       	mov55 $r11,$r5
    984c:	d5 73       	j8 9932 <__subdf3+0x4ca>
    984e:	50 25 80 01 	addi $r2,$r11,#0x1
    9852:	96 95       	x11b33 $r2,$r2
    9854:	e4 42       	sltsi45 $r2,#0x2
    9856:	e8 52       	beqzs8 98fa <__subdf3+0x492>
    9858:	40 20 a0 04 	or $r2,$r1,$r8
    985c:	40 50 0c 04 	or $r5,$r0,$r3
    9860:	4e b3 00 25 	bnez $r11,98aa <__subdf3+0x442>
    9864:	cd 04       	bnez38 $r5,986c <__subdf3+0x404>
    9866:	4e 23 00 df 	bnez $r2,9a24 <__subdf3+0x5bc>
    986a:	d5 17       	j8 9898 <__subdf3+0x430>
    986c:	4e 22 00 ed 	beqz $r2,9a46 <__subdf3+0x5de>
    9870:	40 51 a0 01 	sub $r5,$r3,$r8
    9874:	9a 81       	sub333 $r2,$r0,$r1
    9876:	e2 65       	slt45 $r3,$r5
    9878:	8a 4f       	sub45 $r2,$r15
    987a:	42 61 5c 0b 	btst $r6,$r2,#0x17
    987e:	c6 09       	beqz38 $r6,9890 <__subdf3+0x428>
    9880:	40 34 0c 01 	sub $r3,$r8,$r3
    9884:	9a 08       	sub333 $r0,$r1,$r0
    9886:	40 84 0c 06 	slt $r8,$r8,$r3
    988a:	8a 08       	sub45 $r0,$r8
    988c:	48 00 00 dc 	j 9a44 <__subdf3+0x5dc>
    9890:	40 01 14 04 	or $r0,$r2,$r5
    9894:	4e 03 00 cb 	bnez $r0,9a2a <__subdf3+0x5c2>
    9898:	54 45 00 03 	andi $r4,$r10,#0x3
    989c:	8e 82       	subi45 $r4,#0x2
    989e:	5c 42 00 01 	slti $r4,$r4,#0x1
    98a2:	80 0b       	mov55 $r0,$r11
    98a4:	80 6b       	mov55 $r3,$r11
    98a6:	48 00 00 e9 	j 9a78 <__subdf3+0x610>
    98aa:	cd 08       	bnez38 $r5,98ba <__subdf3+0x452>
    98ac:	4e 22 00 c2 	beqz $r2,9a30 <__subdf3+0x5c8>
    98b0:	80 01       	mov55 $r0,$r1
    98b2:	80 68       	mov55 $r3,$r8
    98b4:	80 87       	mov55 $r4,$r7
    98b6:	48 00 00 c5 	j 9a40 <__subdf3+0x5d8>
    98ba:	4e 22 00 c3 	beqz $r2,9a40 <__subdf3+0x5d8>
    98be:	40 50 0c 09 	srli $r5,$r0,#0x3
    98c2:	46 20 00 80 	sethi $r2,#0x80
    98c6:	40 f0 74 08 	slli $r15,$r0,#0x1d
    98ca:	40 02 88 02 	and $r0,$r5,$r2
    98ce:	40 37 8c 75 	or_srli $r3,$r15,$r3,#0x3
    98d2:	c0 0b       	beqz38 $r0,98e8 <__subdf3+0x480>
    98d4:	40 00 8c 09 	srli $r0,$r1,#0x3
    98d8:	fe 86       	and33 $r2,$r0
    98da:	ca 07       	bnez38 $r2,98e8 <__subdf3+0x480>
    98dc:	40 30 f4 08 	slli $r3,$r1,#0x1d
    98e0:	40 31 a0 75 	or_srli $r3,$r3,$r8,#0x3
    98e4:	80 a0       	mov55 $r5,$r0
    98e6:	80 87       	mov55 $r4,$r7
    98e8:	40 01 f4 09 	srli $r0,$r3,#0x1d
    98ec:	40 00 14 64 	or_slli $r0,$r0,$r5,#0x3
    98f0:	94 db       	slli333 $r3,$r3,#0x3
    98f2:	44 b0 07 ff 	movi $r11,#0x7ff
    98f6:	48 00 00 a8 	j 9a46 <__subdf3+0x5de>
    98fa:	40 21 a0 01 	sub $r2,$r3,$r8
    98fe:	9b 41       	sub333 $r5,$r0,$r1
    9900:	e2 62       	slt45 $r3,$r2
    9902:	40 62 bc 01 	sub $r6,$r5,$r15
    9906:	42 53 5c 0b 	btst $r5,$r6,#0x17
    990a:	c5 08       	beqz38 $r5,991a <__subdf3+0x4b2>
    990c:	40 24 0c 01 	sub $r2,$r8,$r3
    9910:	9b 08       	sub333 $r4,$r1,$r0
    9912:	e3 02       	slt45 $r8,$r2
    9914:	40 62 3c 01 	sub $r6,$r4,$r15
    9918:	d5 16       	j8 9944 <__subdf3+0x4dc>
    991a:	40 03 08 04 	or $r0,$r6,$r2
    991e:	c8 14       	bnez38 $r0,9946 <__subdf3+0x4de>
    9920:	54 45 00 03 	andi $r4,$r10,#0x3
    9924:	8e 82       	subi45 $r4,#0x2
    9926:	5c 42 00 01 	slti $r4,$r4,#0x1
    992a:	80 60       	mov55 $r3,$r0
    992c:	81 60       	mov55 $r11,$r0
    992e:	48 00 00 a5 	j 9a78 <__subdf3+0x610>
    9932:	42 10 5c 0b 	btst $r1,$r0,#0x17
    9936:	4e 12 00 87 	beqz $r1,9a44 <__subdf3+0x5dc>
    993a:	41 30 24 08 	slli $r19,$r0,#0x9
    993e:	40 69 a4 09 	srli $r6,$r19,#0x9
    9942:	80 43       	mov55 $r2,$r3
    9944:	80 87       	mov55 $r4,$r7
    9946:	c6 04       	beqz38 $r6,994e <__subdf3+0x4e6>
    9948:	42 73 00 07 	clz $r7,$r6
    994c:	d5 05       	j8 9956 <__subdf3+0x4ee>
    994e:	42 71 00 07 	clz $r7,$r2
    9952:	50 73 80 20 	addi $r7,$r7,#0x20
    9956:	51 03 ff f8 	addi $r16,$r7,#-8
    995a:	5e f8 00 20 	sltsi $r15,$r16,#0x20
    995e:	e8 0c       	beqzs8 9976 <__subdf3+0x50e>
    9960:	52 73 80 28 	subri $r7,$r7,#0x28
    9964:	40 f3 40 0c 	sll $r15,$r6,$r16
    9968:	40 71 1c 0d 	srl $r7,$r2,$r7
    996c:	40 63 bc 04 	or $r6,$r7,$r15
    9970:	40 31 40 0c 	sll $r3,$r2,$r16
    9974:	d5 06       	j8 9980 <__subdf3+0x518>
    9976:	50 63 ff d8 	addi $r6,$r7,#-40
    997a:	40 61 18 0c 	sll $r6,$r2,$r6
    997e:	84 60       	movi55 $r3,#0x0
    9980:	e1 8b       	slts45 $r16,$r11
    9982:	e9 2b       	bnezs8 99d8 <__subdf3+0x570>
    9984:	40 58 2c 01 	sub $r5,$r16,$r11
    9988:	9c 69       	addi333 $r1,$r5,#0x1
    998a:	5e f0 80 20 	sltsi $r15,$r1,#0x20
    998e:	e8 12       	beqzs8 99b2 <__subdf3+0x54a>
    9990:	52 52 80 1f 	subri $r5,$r5,#0x1f
    9994:	40 03 14 0c 	sll $r0,$r6,$r5
    9998:	40 21 84 0d 	srl $r2,$r3,$r1
    999c:	40 31 94 0c 	sll $r3,$r3,$r5
    99a0:	84 a0       	movi55 $r5,#0x0
    99a2:	fe 87       	or33 $r2,$r0
    99a4:	e2 a3       	slt45 $r5,$r3
    99a6:	40 31 3c 04 	or $r3,$r2,$r15
    99aa:	40 03 04 0d 	srl $r0,$r6,$r1
    99ae:	81 65       	mov55 $r11,$r5
    99b0:	d5 4b       	j8 9a46 <__subdf3+0x5de>
    99b2:	50 22 ff e1 	addi $r2,$r5,#-31
    99b6:	40 23 08 0d 	srl $r2,$r6,$r2
    99ba:	5a 10 20 07 	beqc $r1,#0x20,99c8 <__subdf3+0x560>
    99be:	53 02 80 3f 	subri $r16,$r5,#0x3f
    99c2:	40 63 40 0c 	sll $r6,$r6,$r16
    99c6:	d5 02       	j8 99ca <__subdf3+0x562>
    99c8:	84 c0       	movi55 $r6,#0x0
    99ca:	fe f7       	or33 $r3,$r6
    99cc:	84 00       	movi55 $r0,#0x0
    99ce:	e2 03       	slt45 $r0,$r3
    99d0:	40 37 88 04 	or $r3,$r15,$r2
    99d4:	81 60       	mov55 $r11,$r0
    99d6:	d5 38       	j8 9a46 <__subdf3+0x5de>
    99d8:	8b 70       	sub45 $r11,$r16
    99da:	42 03 5c 09 	bclr $r0,$r6,#0x17
    99de:	d5 34       	j8 9a46 <__subdf3+0x5de>
    99e0:	80 01       	mov55 $r0,$r1
    99e2:	80 68       	mov55 $r3,$r8
    99e4:	d5 e5       	j8 99ae <__subdf3+0x546>
    99e6:	80 01       	mov55 $r0,$r1
    99e8:	80 68       	mov55 $r3,$r8
    99ea:	d5 2e       	j8 9a46 <__subdf3+0x5de>
    99ec:	80 67       	mov55 $r3,$r7
    99ee:	d5 2c       	j8 9a46 <__subdf3+0x5de>
    99f0:	80 01       	mov55 $r0,$r1
    99f2:	80 68       	mov55 $r3,$r8
    99f4:	d5 26       	j8 9a40 <__subdf3+0x5d8>
    99f6:	81 65       	mov55 $r11,$r5
    99f8:	80 01       	mov55 $r0,$r1
    99fa:	80 61       	mov55 $r3,$r1
    99fc:	d5 3e       	j8 9a78 <__subdf3+0x610>
    99fe:	84 1f       	movi55 $r0,#-1
    9a00:	80 60       	mov55 $r3,$r0
    9a02:	44 b0 07 fe 	movi $r11,#0x7fe
    9a06:	80 81       	mov55 $r4,$r1
    9a08:	d5 22       	j8 9a4c <__subdf3+0x5e4>
    9a0a:	84 1f       	movi55 $r0,#-1
    9a0c:	80 60       	mov55 $r3,$r0
    9a0e:	44 b0 07 fe 	movi $r11,#0x7fe
    9a12:	d5 1d       	j8 9a4c <__subdf3+0x5e4>
    9a14:	84 00       	movi55 $r0,#0x0
    9a16:	80 60       	mov55 $r3,$r0
    9a18:	84 81       	movi55 $r4,#0x1
    9a1a:	d5 2f       	j8 9a78 <__subdf3+0x610>
    9a1c:	80 01       	mov55 $r0,$r1
    9a1e:	80 68       	mov55 $r3,$r8
    9a20:	81 65       	mov55 $r11,$r5
    9a22:	d5 11       	j8 9a44 <__subdf3+0x5dc>
    9a24:	80 01       	mov55 $r0,$r1
    9a26:	80 68       	mov55 $r3,$r8
    9a28:	d5 0e       	j8 9a44 <__subdf3+0x5dc>
    9a2a:	80 02       	mov55 $r0,$r2
    9a2c:	80 65       	mov55 $r3,$r5
    9a2e:	d5 0c       	j8 9a46 <__subdf3+0x5de>
    9a30:	46 f0 07 ff 	sethi $r15,#0x7ff
    9a34:	50 07 8f ff 	addi $r0,$r15,#0xfff
    9a38:	84 78       	movi55 $r3,#-8
    9a3a:	81 66       	mov55 $r11,$r6
    9a3c:	80 82       	mov55 $r4,$r2
    9a3e:	d5 1d       	j8 9a78 <__subdf3+0x610>
    9a40:	81 66       	mov55 $r11,$r6
    9a42:	d5 02       	j8 9a46 <__subdf3+0x5de>
    9a44:	80 87       	mov55 $r4,$r7
    9a46:	54 11 80 07 	andi $r1,$r3,#0x7
    9a4a:	c1 17       	beqz38 $r1,9a78 <__subdf3+0x610>
    9a4c:	54 15 00 03 	andi $r1,$r10,#0x3
    9a50:	5a 10 01 0c 	beqc $r1,#0x1,9a68 <__subdf3+0x600>
    9a54:	c1 04       	beqz38 $r1,9a5c <__subdf3+0x5f4>
    9a56:	5a 10 02 0b 	beqc $r1,#0x2,9a6c <__subdf3+0x604>
    9a5a:	d5 0f       	j8 9a78 <__subdf3+0x610>
    9a5c:	54 11 80 0f 	andi $r1,$r3,#0xf
    9a60:	5a 10 04 0c 	beqc $r1,#0x4,9a78 <__subdf3+0x610>
    9a64:	9d dc       	addi333 $r7,$r3,#0x4
    9a66:	d5 06       	j8 9a72 <__subdf3+0x60a>
    9a68:	cc 08       	bnez38 $r4,9a78 <__subdf3+0x610>
    9a6a:	d5 02       	j8 9a6e <__subdf3+0x606>
    9a6c:	c4 06       	beqz38 $r4,9a78 <__subdf3+0x610>
    9a6e:	50 71 80 08 	addi $r7,$r3,#0x8
    9a72:	e2 e3       	slt45 $r7,$r3
    9a74:	88 0f       	add45 $r0,$r15
    9a76:	80 67       	mov55 $r3,$r7
    9a78:	42 10 5c 0b 	btst $r1,$r0,#0x17
    9a7c:	c1 1c       	beqz38 $r1,9ab4 <__subdf3+0x64c>
    9a7e:	8d 61       	addi45 $r11,#0x1
    9a80:	44 10 07 ff 	movi $r1,#0x7ff
    9a84:	4c b0 80 05 	beq $r11,$r1,9a8e <__subdf3+0x626>
    9a88:	42 00 5c 09 	bclr $r0,$r0,#0x17
    9a8c:	d5 14       	j8 9ab4 <__subdf3+0x64c>
    9a8e:	54 05 00 03 	andi $r0,$r10,#0x3
    9a92:	c0 10       	beqz38 $r0,9ab2 <__subdf3+0x64a>
    9a94:	5a 08 01 06 	bnec $r0,#0x1,9aa0 <__subdf3+0x638>
    9a98:	cc 07       	bnez38 $r4,9aa6 <__subdf3+0x63e>
    9a9a:	80 04       	mov55 $r0,$r4
    9a9c:	80 64       	mov55 $r3,$r4
    9a9e:	d5 0b       	j8 9ab4 <__subdf3+0x64c>
    9aa0:	5a 08 02 03 	bnec $r0,#0x2,9aa6 <__subdf3+0x63e>
    9aa4:	cc 06       	bnez38 $r4,9ab0 <__subdf3+0x648>
    9aa6:	84 1f       	movi55 $r0,#-1
    9aa8:	80 60       	mov55 $r3,$r0
    9aaa:	44 b0 07 fe 	movi $r11,#0x7fe
    9aae:	d5 03       	j8 9ab4 <__subdf3+0x64c>
    9ab0:	84 00       	movi55 $r0,#0x0
    9ab2:	80 60       	mov55 $r3,$r0
    9ab4:	40 f0 74 08 	slli $r15,$r0,#0x1d
    9ab8:	44 10 07 ff 	movi $r1,#0x7ff
    9abc:	40 f7 8c 75 	or_srli $r15,$r15,$r3,#0x3
    9ac0:	92 03       	srli45 $r0,#0x3
    9ac2:	4c b0 c0 09 	bne $r11,$r1,9ad4 <__subdf3+0x66c>
    9ac6:	40 17 80 04 	or $r1,$r15,$r0
    9aca:	c1 04       	beqz38 $r1,9ad2 <__subdf3+0x66a>
    9acc:	42 00 4c 08 	bset $r0,$r0,#0x13
    9ad0:	d5 02       	j8 9ad4 <__subdf3+0x66c>
    9ad2:	80 01       	mov55 $r0,$r1
    9ad4:	84 40       	movi55 $r2,#0x0
    9ad6:	80 62       	mov55 $r3,$r2
    9ad8:	80 4f       	mov55 $r2,$r15
    9ada:	40 f1 d0 09 	srli $r15,$r3,#0x14
    9ade:	40 f7 d0 08 	slli $r15,$r15,#0x14
    9ae2:	40 00 30 08 	slli $r0,$r0,#0xc
    9ae6:	46 18 00 ff 	sethi $r1,#0x800ff
    9aea:	40 07 81 95 	or_srli $r0,$r15,$r0,#0xc
    9aee:	50 10 8f ff 	addi $r1,$r1,#0xfff
    9af2:	54 55 87 ff 	andi $r5,$r11,#0x7ff
    9af6:	fe 0e       	and33 $r0,$r1
    9af8:	40 00 16 84 	or_slli $r0,$r0,$r5,#0x14
    9afc:	42 00 7c 09 	bclr $r0,$r0,#0x1f
    9b00:	40 30 13 e4 	or_slli $r3,$r0,$r4,#0x1f
    9b04:	6a 20 00 49 	fmtdr $r2,$fd0
    9b08:	fc e0       	pop25 $r14,#0    ! {$r6~$r14, $fp, $gp, $lp}

00009b0a <__floatsidf>:
    9b0a:	fc 00       	push25 $r6,#0    ! {$r6, $fp, $gp, $lp}
    9b0c:	c0 18       	beqz38 $r0,9b3c <__floatsidf+0x32>
    9b0e:	40 60 7c 09 	srli $r6,$r0,#0x1f
    9b12:	c6 02       	beqz38 $r6,9b16 <__floatsidf+0xc>
    9b14:	fe 02       	neg33 $r0,$r0
    9b16:	42 40 00 07 	clz $r4,$r0
    9b1a:	e4 8b       	sltsi45 $r4,#0xb
    9b1c:	52 32 04 1e 	subri $r3,$r4,#0x41e
    9b20:	e8 09       	beqzs8 9b32 <__floatsidf+0x28>
    9b22:	52 22 00 0b 	subri $r2,$r4,#0xb
    9b26:	8c 95       	addi45 $r4,#0x15
    9b28:	40 10 08 0d 	srl $r1,$r0,$r2
    9b2c:	40 00 10 0c 	sll $r0,$r0,$r4
    9b30:	d5 09       	j8 9b42 <__floatsidf+0x38>
    9b32:	8e 8b       	subi45 $r4,#0xb
    9b34:	40 10 10 0c 	sll $r1,$r0,$r4
    9b38:	84 00       	movi55 $r0,#0x0
    9b3a:	d5 04       	j8 9b42 <__floatsidf+0x38>
    9b3c:	80 20       	mov55 $r1,$r0
    9b3e:	80 60       	mov55 $r3,$r0
    9b40:	80 c0       	mov55 $r6,$r0
    9b42:	84 80       	movi55 $r4,#0x0
    9b44:	80 a4       	mov55 $r5,$r4
    9b46:	80 80       	mov55 $r4,$r0
    9b48:	40 02 d0 09 	srli $r0,$r5,#0x14
    9b4c:	40 00 50 08 	slli $r0,$r0,#0x14
    9b50:	40 10 b0 08 	slli $r1,$r1,#0xc
    9b54:	40 10 05 95 	or_srli $r1,$r0,$r1,#0xc
    9b58:	46 08 00 ff 	sethi $r0,#0x800ff
    9b5c:	50 00 0f ff 	addi $r0,$r0,#0xfff
    9b60:	96 dd       	x11b33 $r3,$r3
    9b62:	fe 46       	and33 $r1,$r0
    9b64:	40 10 8e 84 	or_slli $r1,$r1,$r3,#0x14
    9b68:	42 10 fc 09 	bclr $r1,$r1,#0x1f
    9b6c:	40 50 9b e4 	or_slli $r5,$r1,$r6,#0x1f
    9b70:	6a 40 00 49 	fmtdr $r4,$fd0
    9b74:	fc 80       	pop25 $r6,#0    ! {$r6, $fp, $gp, $lp}

00009b76 <__floatunsidf>:
    9b76:	c0 14       	beqz38 $r0,9b9e <__floatunsidf+0x28>
    9b78:	42 30 00 07 	clz $r3,$r0
    9b7c:	e4 6b       	sltsi45 $r3,#0xb
    9b7e:	52 41 84 1e 	subri $r4,$r3,#0x41e
    9b82:	e8 09       	beqzs8 9b94 <__floatunsidf+0x1e>
    9b84:	52 21 80 0b 	subri $r2,$r3,#0xb
    9b88:	8c 75       	addi45 $r3,#0x15
    9b8a:	40 10 08 0d 	srl $r1,$r0,$r2
    9b8e:	40 00 0c 0c 	sll $r0,$r0,$r3
    9b92:	d5 08       	j8 9ba2 <__floatunsidf+0x2c>
    9b94:	8e 6b       	subi45 $r3,#0xb
    9b96:	40 10 0c 0c 	sll $r1,$r0,$r3
    9b9a:	84 00       	movi55 $r0,#0x0
    9b9c:	d5 03       	j8 9ba2 <__floatunsidf+0x2c>
    9b9e:	80 20       	mov55 $r1,$r0
    9ba0:	80 80       	mov55 $r4,$r0
    9ba2:	84 40       	movi55 $r2,#0x0
    9ba4:	80 62       	mov55 $r3,$r2
    9ba6:	80 40       	mov55 $r2,$r0
    9ba8:	40 01 d0 09 	srli $r0,$r3,#0x14
    9bac:	40 00 50 08 	slli $r0,$r0,#0x14
    9bb0:	40 10 b0 08 	slli $r1,$r1,#0xc
    9bb4:	40 10 05 95 	or_srli $r1,$r0,$r1,#0xc
    9bb8:	46 08 00 ff 	sethi $r0,#0x800ff
    9bbc:	50 00 0f ff 	addi $r0,$r0,#0xfff
    9bc0:	97 25       	x11b33 $r4,$r4
    9bc2:	fe 46       	and33 $r1,$r0
    9bc4:	40 10 92 84 	or_slli $r1,$r1,$r4,#0x14
    9bc8:	42 30 fc 09 	bclr $r3,$r1,#0x1f
    9bcc:	6a 20 00 49 	fmtdr $r2,$fd0
    9bd0:	dd 9e       	ret5 $lp
    9bd2:	00 00 2c 20 	lbi $r0,[$r0+#0x2c20]
    9bd6:	66 75 6e 63 	bitci $r7,$r10,#0x6e63
    9bda:	74 69 6f 6e 	*unknown*
    9bde:	3a 20 00 00 	lmw.bi $r2,[$r0],$r0,#0x0    ! {$r2~$r0}
    9be2:	00 00 61 73 	lbi $r0,[$r0+#-7821]
    9be6:	73 65 72 74 	*unknown*
    9bea:	69 6f 6e 20 	*unknown*
    9bee:	22 25 73 22 	lhsi $r2,[$r10+#-6588]
    9bf2:	20 66 61 69 	lbsi $r6,[$r12+#-7831]
    9bf6:	6c 65 64 3a 	*unknown*
    9bfa:	20 66 69 6c 	lbsi $r6,[$r12+#-5780]
    9bfe:	65 20 22 25 	trap #0x111
    9c02:	73 22 2c 20 	*unknown*
    9c06:	6c 69 6e 65 	*unknown*
    9c0a:	20 25 64 25 	lbsi $r2,[$r10+#-7131]
    9c0e:	73 25 73 0a 	*unknown*
	...

00009c14 <__assert_func>:
    9c14:	fc 03       	push25 $r6,#24    ! {$r6, $fp, $gp, $lp}
    9c16:	80 a0       	mov55 $r5,$r0
    9c18:	3c 0c 00 1b 	lwi.gp $r0,[+#0x6c]
    9c1c:	ca 05       	bnez38 $r2,9c26 <__assert_func+0x12>
    9c1e:	44 40 01 38 	movi $r4,#0x138
    9c22:	80 44       	mov55 $r2,$r4
    9c24:	d5 03       	j8 9c2a <__assert_func+0x16>
    9c26:	44 40 9b d4 	movi $r4,#0x9bd4
    9c2a:	b6 7f       	swi450 $r3,[$sp]
    9c2c:	f5 81       	swi37.sp $r5,[+#0x4]
    9c2e:	f1 82       	swi37.sp $r1,[+#0x8]
    9c30:	f4 83       	swi37.sp $r4,[+#0xc]
    9c32:	f2 84       	swi37.sp $r2,[+#0x10]
    9c34:	44 10 9b e4 	movi $r1,#0x9be4
    9c38:	49 00 01 34 	jal 9ea0 <fiprintf>
    9c3c:	49 00 08 fc 	jal ae34 <abort>
    9c40:	92 00       	nop16
	...

00009c44 <atoi>:
    9c44:	84 20       	movi55 $r1,#0x0
    9c46:	84 4a       	movi55 $r2,#0xa
    9c48:	48 00 03 14 	j a270 <strtol>

00009c4c <__sflush_r>:
    9c4c:	fc 41       	push25 $r10,#8    ! {$r6~$r10, $fp, $gp, $lp}
    9c4e:	3f c8 2b 50 	addi.gp $fp,#0x2b50
    9c52:	22 20 80 06 	lhsi $r2,[$r1+#0xc]
    9c56:	f0 81       	swi37.sp $r0,[+#0x4]
    9c58:	96 11       	zeh33 $r0,$r2
    9c5a:	80 c1       	mov55 $r6,$r1
    9c5c:	54 10 00 08 	andi $r1,$r0,#0x8
    9c60:	4e 13 00 67 	bnez $r1,9d2e <__sflush_r+0xe2>
    9c64:	a0 31       	lwi333 $r0,[$r6+#0x4]
    9c66:	58 21 08 00 	ori $r2,$r2,#0x800
    9c6a:	ac b6       	shi333 $r2,[$r6+#0xc]
    9c6c:	4e 06 00 06 	bgtz $r0,9c78 <__sflush_r+0x2c>
    9c70:	04 03 00 0f 	lwi $r0,[$r6+#0x3c]
    9c74:	4e 07 00 1d 	blez $r0,9cae <__sflush_r+0x62>
    9c78:	04 43 00 0a 	lwi $r4,[$r6+#0x28]
    9c7c:	c4 19       	beqz38 $r4,9cae <__sflush_r+0x62>
    9c7e:	54 21 10 00 	andi $r2,$r2,#0x1000
    9c82:	bf 00       	lwi37 $r7,[$fp+#0x0]
    9c84:	84 00       	movi55 $r0,#0x0
    9c86:	96 91       	zeh33 $r2,$r2
    9c88:	b8 80       	swi37 $r0,[$fp+#0x0]
    9c8a:	c2 04       	beqz38 $r2,9c92 <__sflush_r+0x46>
    9c8c:	04 23 00 14 	lwi $r2,[$r6+#0x50]
    9c90:	d5 11       	j8 9cb2 <__sflush_r+0x66>
    9c92:	f0 01       	lwi37.sp $r0,[+#0x4]
    9c94:	a0 77       	lwi333 $r1,[$r6+#0x1c]
    9c96:	84 61       	movi55 $r3,#0x1
    9c98:	dd 24       	jral5 $r4
    9c9a:	80 40       	mov55 $r2,$r0
    9c9c:	5a 0f ff 0b 	bnec $r0,#-1,9cb2 <__sflush_r+0x66>
    9ca0:	b8 00       	lwi37 $r0,[$fp+#0x0]
    9ca2:	c0 08       	beqz38 $r0,9cb2 <__sflush_r+0x66>
    9ca4:	5a 00 1d 04 	beqc $r0,#0x1d,9cac <__sflush_r+0x60>
    9ca8:	5a 08 16 51 	bnec $r0,#0x16,9d4a <__sflush_r+0xfe>
    9cac:	bf 80       	swi37 $r7,[$fp+#0x0]
    9cae:	84 00       	movi55 $r0,#0x0
    9cb0:	d5 61       	j8 9d72 <__sflush_r+0x126>
    9cb2:	a4 36       	lhi333 $r0,[$r6+#0xc]
    9cb4:	96 16       	bmski33 $r0,#0x2
    9cb6:	c0 09       	beqz38 $r0,9cc8 <__sflush_r+0x7c>
    9cb8:	a0 31       	lwi333 $r0,[$r6+#0x4]
    9cba:	8a 40       	sub45 $r2,$r0
    9cbc:	04 03 00 0c 	lwi $r0,[$r6+#0x30]
    9cc0:	c0 04       	beqz38 $r0,9cc8 <__sflush_r+0x7c>
    9cc2:	04 03 00 0f 	lwi $r0,[$r6+#0x3c]
    9cc6:	8a 40       	sub45 $r2,$r0
    9cc8:	04 43 00 0a 	lwi $r4,[$r6+#0x28]
    9ccc:	a0 77       	lwi333 $r1,[$r6+#0x1c]
    9cce:	f0 01       	lwi37.sp $r0,[+#0x4]
    9cd0:	84 60       	movi55 $r3,#0x0
    9cd2:	dd 24       	jral5 $r4
    9cd4:	a4 76       	lhi333 $r1,[$r6+#0xc]
    9cd6:	5a 0f ff 08 	bnec $r0,#-1,9ce6 <__sflush_r+0x9a>
    9cda:	ba 00       	lwi37 $r2,[$fp+#0x0]
    9cdc:	c2 05       	beqz38 $r2,9ce6 <__sflush_r+0x9a>
    9cde:	5a 20 1d 04 	beqc $r2,#0x1d,9ce6 <__sflush_r+0x9a>
    9ce2:	5a 28 16 22 	bnec $r2,#0x16,9d26 <__sflush_r+0xda>
    9ce6:	66 10 88 00 	bitci $r1,$r1,#0x800
    9cea:	96 4b       	seh33 $r1,$r1
    9cec:	84 40       	movi55 $r2,#0x0
    9cee:	ac 76       	shi333 $r1,[$r6+#0xc]
    9cf0:	a8 b1       	swi333 $r2,[$r6+#0x4]
    9cf2:	54 10 90 00 	andi $r1,$r1,#0x1000
    9cf6:	a0 b4       	lwi333 $r2,[$r6+#0x10]
    9cf8:	b6 46       	swi450 $r2,[$r6]
    9cfa:	c1 07       	beqz38 $r1,9d08 <__sflush_r+0xbc>
    9cfc:	5a 0f ff 04 	bnec $r0,#-1,9d04 <__sflush_r+0xb8>
    9d00:	b9 00       	lwi37 $r1,[$fp+#0x0]
    9d02:	c9 03       	bnez38 $r1,9d08 <__sflush_r+0xbc>
    9d04:	14 03 00 14 	swi $r0,[$r6+#0x50]
    9d08:	04 13 00 0c 	lwi $r1,[$r6+#0x30]
    9d0c:	bf 80       	swi37 $r7,[$fp+#0x0]
    9d0e:	c1 d0       	beqz38 $r1,9cae <__sflush_r+0x62>
    9d10:	50 03 00 40 	addi $r0,$r6,#0x40
    9d14:	4c 10 00 05 	beq $r1,$r0,9d1e <__sflush_r+0xd2>
    9d18:	f0 01       	lwi37.sp $r0,[+#0x4]
    9d1a:	49 00 01 87 	jal a028 <_free_r>
    9d1e:	84 00       	movi55 $r0,#0x0
    9d20:	14 03 00 0c 	swi $r0,[$r6+#0x30]
    9d24:	d5 27       	j8 9d72 <__sflush_r+0x126>
    9d26:	58 10 80 40 	ori $r1,$r1,#0x40
    9d2a:	ac 76       	shi333 $r1,[$r6+#0xc]
    9d2c:	d5 23       	j8 9d72 <__sflush_r+0x126>
    9d2e:	04 93 00 04 	lwi $r9,[$r6+#0x10]
    9d32:	4e 92 ff be 	beqz $r9,9cae <__sflush_r+0x62>
    9d36:	b4 e6       	lwi450 $r7,[$r6]
    9d38:	96 0f       	fexti33 $r0,#0x1
    9d3a:	8a e9       	sub45 $r7,$r9
    9d3c:	b7 26       	swi450 $r9,[$r6]
    9d3e:	c8 03       	bnez38 $r0,9d44 <__sflush_r+0xf8>
    9d40:	a0 35       	lwi333 $r0,[$r6+#0x14]
    9d42:	d5 02       	j8 9d46 <__sflush_r+0xfa>
    9d44:	84 00       	movi55 $r0,#0x0
    9d46:	a8 32       	swi333 $r0,[$r6+#0x8]
    9d48:	d5 12       	j8 9d6c <__sflush_r+0x120>
    9d4a:	a4 36       	lhi333 $r0,[$r6+#0xc]
    9d4c:	58 00 00 40 	ori $r0,$r0,#0x40
    9d50:	ac 36       	shi333 $r0,[$r6+#0xc]
    9d52:	84 1f       	movi55 $r0,#-1
    9d54:	d5 0f       	j8 9d72 <__sflush_r+0x126>
    9d56:	04 43 00 09 	lwi $r4,[$r6+#0x24]
    9d5a:	f0 01       	lwi37.sp $r0,[+#0x4]
    9d5c:	a0 77       	lwi333 $r1,[$r6+#0x1c]
    9d5e:	80 49       	mov55 $r2,$r9
    9d60:	80 67       	mov55 $r3,$r7
    9d62:	dd 24       	jral5 $r4
    9d64:	4e 07 ff f3 	blez $r0,9d4a <__sflush_r+0xfe>
    9d68:	89 20       	add45 $r9,$r0
    9d6a:	8a e0       	sub45 $r7,$r0
    9d6c:	4e 76 ff f5 	bgtz $r7,9d56 <__sflush_r+0x10a>
    9d70:	d5 9f       	j8 9cae <__sflush_r+0x62>
    9d72:	fc c1       	pop25 $r10,#8    ! {$r6~$r10, $fp, $gp, $lp}

00009d74 <_fflush_r>:
    9d74:	fc 01       	push25 $r6,#8    ! {$r6, $fp, $gp, $lp}
    9d76:	3c 2c 0a d8 	lwi.gp $r2,[+#0x2b60]
    9d7a:	b6 1f       	swi450 $r0,[$sp]
    9d7c:	ca 05       	bnez38 $r2,9d86 <_fflush_r+0x12>
    9d7e:	f1 81       	swi37.sp $r1,[+#0x4]
    9d80:	49 00 00 20 	jal 9dc0 <__sinit>
    9d84:	f1 01       	lwi37.sp $r1,[+#0x4]
    9d86:	22 00 80 06 	lhsi $r0,[$r1+#0xc]
    9d8a:	c0 04       	beqz38 $r0,9d92 <_fflush_r+0x1e>
    9d8c:	b4 1f       	lwi450 $r0,[$sp]
    9d8e:	49 ff ff 5f 	jal 9c4c <__sflush_r>
    9d92:	b6 1f       	swi450 $r0,[$sp]
    9d94:	b4 1f       	lwi450 $r0,[$sp]
    9d96:	fc 81       	pop25 $r6,#8    ! {$r6, $fp, $gp, $lp}

00009d98 <fflush>:
    9d98:	fc 01       	push25 $r6,#8    ! {$r6, $fp, $gp, $lp}
    9d9a:	80 20       	mov55 $r1,$r0
    9d9c:	c8 06       	bnez38 $r0,9da8 <fflush+0x10>
    9d9e:	44 10 9d 74 	movi $r1,#0x9d74
    9da2:	49 00 00 89 	jal 9eb4 <_fwalk_reent>
    9da6:	d5 04       	j8 9dae <fflush+0x16>
    9da8:	84 00       	movi55 $r0,#0x0
    9daa:	49 ff ff e5 	jal 9d74 <_fflush_r>
    9dae:	f0 81       	swi37.sp $r0,[+#0x4]
    9db0:	f0 01       	lwi37.sp $r0,[+#0x4]
    9db2:	fc 81       	pop25 $r6,#8    ! {$r6, $fp, $gp, $lp}

00009db4 <_cleanup_r>:
    9db4:	fc 00       	push25 $r6,#0    ! {$r6, $fp, $gp, $lp}
    9db6:	44 10 ae 5c 	movi $r1,#0xae5c
    9dba:	49 00 00 7d 	jal 9eb4 <_fwalk_reent>
    9dbe:	fc 80       	pop25 $r6,#0    ! {$r6, $fp, $gp, $lp}

00009dc0 <__sinit>:
    9dc0:	fc 60       	push25 $r14,#0    ! {$r6~$r14, $fp, $gp, $lp}
    9dc2:	3f c8 00 6c 	addi.gp $fp,#0x6c
    9dc6:	3c 6c 0a d8 	lwi.gp $r6,[+#0x2b60]
    9dca:	4e 63 00 68 	bnez $r6,9e9a <__sinit+0xda>
    9dce:	44 00 9d b4 	movi $r0,#0x9db4
    9dd2:	3c 0e 0a d7 	swi.gp $r0,[+#0x2b5c]
    9dd6:	be 83       	swi37 $r6,[$fp+#0xc]
    9dd8:	84 03       	movi55 $r0,#0x3
    9dda:	b8 84       	swi37 $r0,[$fp+#0x10]
    9ddc:	bf 02       	lwi37 $r7,[$fp+#0x8]
    9dde:	bf 85       	swi37 $r7,[$fp+#0x14]
    9de0:	84 04       	movi55 $r0,#0x4
    9de2:	ac 3e       	shi333 $r0,[$r7+#0xc]
    9de4:	b6 c7       	swi450 $r6,[$r7]
    9de6:	a9 b9       	swi333 $r6,[$r7+#0x4]
    9de8:	a9 ba       	swi333 $r6,[$r7+#0x8]
    9dea:	14 63 80 19 	swi $r6,[$r7+#0x64]
    9dee:	ad bf       	shi333 $r6,[$r7+#0xe]
    9df0:	a9 bc       	swi333 $r6,[$r7+#0x10]
    9df2:	a9 bd       	swi333 $r6,[$r7+#0x14]
    9df4:	a9 be       	swi333 $r6,[$r7+#0x18]
    9df6:	50 03 80 5c 	addi $r0,$r7,#0x5c
    9dfa:	80 26       	mov55 $r1,$r6
    9dfc:	84 48       	movi55 $r2,#0x8
    9dfe:	49 00 00 db 	jal 9fb4 <memset>
    9e02:	44 80 a1 64 	movi $r8,#0xa164
    9e06:	44 b0 a1 88 	movi $r11,#0xa188
    9e0a:	44 a0 a1 be 	movi $r10,#0xa1be
    9e0e:	44 90 a1 e4 	movi $r9,#0xa1e4
    9e12:	a9 ff       	swi333 $r7,[$r7+#0x1c]
    9e14:	14 83 80 08 	swi $r8,[$r7+#0x20]
    9e18:	14 b3 80 09 	swi $r11,[$r7+#0x24]
    9e1c:	14 a3 80 0a 	swi $r10,[$r7+#0x28]
    9e20:	14 93 80 0b 	swi $r9,[$r7+#0x2c]
    9e24:	bf 01       	lwi37 $r7,[$fp+#0x4]
    9e26:	84 09       	movi55 $r0,#0x9
    9e28:	ac 3e       	shi333 $r0,[$r7+#0xc]
    9e2a:	84 01       	movi55 $r0,#0x1
    9e2c:	ac 3f       	shi333 $r0,[$r7+#0xe]
    9e2e:	b6 c7       	swi450 $r6,[$r7]
    9e30:	a9 b9       	swi333 $r6,[$r7+#0x4]
    9e32:	a9 ba       	swi333 $r6,[$r7+#0x8]
    9e34:	14 63 80 19 	swi $r6,[$r7+#0x64]
    9e38:	a9 bc       	swi333 $r6,[$r7+#0x10]
    9e3a:	a9 bd       	swi333 $r6,[$r7+#0x14]
    9e3c:	a9 be       	swi333 $r6,[$r7+#0x18]
    9e3e:	50 03 80 5c 	addi $r0,$r7,#0x5c
    9e42:	80 26       	mov55 $r1,$r6
    9e44:	84 48       	movi55 $r2,#0x8
    9e46:	49 00 00 b7 	jal 9fb4 <memset>
    9e4a:	a9 ff       	swi333 $r7,[$r7+#0x1c]
    9e4c:	14 83 80 08 	swi $r8,[$r7+#0x20]
    9e50:	14 b3 80 09 	swi $r11,[$r7+#0x24]
    9e54:	14 a3 80 0a 	swi $r10,[$r7+#0x28]
    9e58:	14 93 80 0b 	swi $r9,[$r7+#0x2c]
    9e5c:	bf 00       	lwi37 $r7,[$fp+#0x0]
    9e5e:	fa 02       	movpi45 $r0,#0x12
    9e60:	ac 3e       	shi333 $r0,[$r7+#0xc]
    9e62:	84 02       	movi55 $r0,#0x2
    9e64:	ac 3f       	shi333 $r0,[$r7+#0xe]
    9e66:	80 26       	mov55 $r1,$r6
    9e68:	b6 c7       	swi450 $r6,[$r7]
    9e6a:	a9 b9       	swi333 $r6,[$r7+#0x4]
    9e6c:	a9 ba       	swi333 $r6,[$r7+#0x8]
    9e6e:	14 63 80 19 	swi $r6,[$r7+#0x64]
    9e72:	a9 bc       	swi333 $r6,[$r7+#0x10]
    9e74:	a9 bd       	swi333 $r6,[$r7+#0x14]
    9e76:	a9 be       	swi333 $r6,[$r7+#0x18]
    9e78:	50 03 80 5c 	addi $r0,$r7,#0x5c
    9e7c:	84 48       	movi55 $r2,#0x8
    9e7e:	49 00 00 9b 	jal 9fb4 <memset>
    9e82:	84 01       	movi55 $r0,#0x1
    9e84:	a9 ff       	swi333 $r7,[$r7+#0x1c]
    9e86:	14 83 80 08 	swi $r8,[$r7+#0x20]
    9e8a:	14 b3 80 09 	swi $r11,[$r7+#0x24]
    9e8e:	14 a3 80 0a 	swi $r10,[$r7+#0x28]
    9e92:	14 93 80 0b 	swi $r9,[$r7+#0x2c]
    9e96:	3c 0e 0a d8 	swi.gp $r0,[+#0x2b60]
    9e9a:	fc e0       	pop25 $r14,#0    ! {$r6~$r14, $fp, $gp, $lp}

00009e9c <__sfp_lock_acquire>:
    9e9c:	dd 9e       	ret5 $lp

00009e9e <__sfp_lock_release>:
    9e9e:	dd 9e       	ret5 $lp

00009ea0 <fiprintf>:
    9ea0:	fc 01       	push25 $r6,#8    ! {$r6, $fp, $gp, $lp}
    9ea2:	b6 1f       	swi450 $r0,[$sp]
    9ea4:	f1 81       	swi37.sp $r1,[+#0x4]
    9ea6:	f2 01       	lwi37.sp $r2,[+#0x4]
    9ea8:	b4 3f       	lwi450 $r1,[$sp]
    9eaa:	b0 c6       	addri36.sp $r3,#0x18
    9eac:	84 00       	movi55 $r0,#0x0
    9eae:	49 00 02 a9 	jal a400 <_vfiprintf_r>
    9eb2:	fc 81       	pop25 $r6,#8    ! {$r6, $fp, $gp, $lp}

00009eb4 <_fwalk_reent>:
    9eb4:	fc 61       	push25 $r14,#8    ! {$r6~$r14, $fp, $gp, $lp}
    9eb6:	3e 68 00 78 	addi.gp $r6,#0x78
    9eba:	f0 81       	swi37.sp $r0,[+#0x4]
    9ebc:	81 61       	mov55 $r11,$r1
    9ebe:	85 20       	movi55 $r9,#0x0
    9ec0:	c6 18       	beqz38 $r6,9ef0 <_fwalk_reent+0x3c>
    9ec2:	a1 f2       	lwi333 $r7,[$r6+#0x8]
    9ec4:	04 a3 00 01 	lwi $r10,[$r6+#0x4]
    9ec8:	8f 41       	subi45 $r10,#0x1
    9eca:	4e a5 00 11 	bltz $r10,9eec <_fwalk_reent+0x38>
    9ece:	a4 3e       	lhi333 $r0,[$r7+#0xc]
    9ed0:	e6 02       	slti45 $r0,#0x2
    9ed2:	e9 0a       	bnezs8 9ee6 <_fwalk_reent+0x32>
    9ed4:	22 03 80 07 	lhsi $r0,[$r7+#0xe]
    9ed8:	5a 07 ff 07 	beqc $r0,#-1,9ee6 <_fwalk_reent+0x32>
    9edc:	f0 01       	lwi37.sp $r0,[+#0x4]
    9ede:	80 27       	mov55 $r1,$r7
    9ee0:	dd 2b       	jral5 $r11
    9ee2:	40 94 80 04 	or $r9,$r9,$r0
    9ee6:	50 73 80 68 	addi $r7,$r7,#0x68
    9eea:	d5 ef       	j8 9ec8 <_fwalk_reent+0x14>
    9eec:	b4 c6       	lwi450 $r6,[$r6]
    9eee:	d5 e9       	j8 9ec0 <_fwalk_reent+0xc>
    9ef0:	80 09       	mov55 $r0,$r9
    9ef2:	fc e1       	pop25 $r14,#8    ! {$r6~$r14, $fp, $gp, $lp}

00009ef4 <malloc>:
    9ef4:	fc 01       	push25 $r6,#8    ! {$r6, $fp, $gp, $lp}
    9ef6:	f0 81       	swi37.sp $r0,[+#0x4]
    9ef8:	f1 01       	lwi37.sp $r1,[+#0x4]
    9efa:	84 00       	movi55 $r0,#0x0
    9efc:	49 00 00 d2 	jal a0a0 <_malloc_r>
    9f00:	fc 81       	pop25 $r6,#8    ! {$r6, $fp, $gp, $lp}

00009f02 <free>:
    9f02:	fc 01       	push25 $r6,#8    ! {$r6, $fp, $gp, $lp}
    9f04:	f0 81       	swi37.sp $r0,[+#0x4]
    9f06:	f1 01       	lwi37.sp $r1,[+#0x4]
    9f08:	84 00       	movi55 $r0,#0x0
    9f0a:	49 00 00 8f 	jal a028 <_free_r>
    9f0e:	fc 81       	pop25 $r6,#8    ! {$r6, $fp, $gp, $lp}

00009f10 <memcmp>:
    9f10:	40 51 08 09 	srli $r5,$r2,#0x2
    9f14:	c5 0f       	beqz38 $r5,9f32 <memcmp+0x22>
    9f16:	95 6a       	slli333 $r5,$r5,#0x2
    9f18:	99 68       	add333 $r5,$r5,$r0
    9f1a:	96 8f       	fexti33 $r2,#0x1
    9f1c:	3a 30 0c 04 	lmw.bim $r3,[$r0],$r3,#0x0    ! {$r3}
    9f20:	3a 40 90 04 	lmw.bim $r4,[$r1],$r4,#0x0    ! {$r4}
    9f24:	4c 32 40 04 	bne $r3,$r4,9f2c <memcmp+0x1c>
    9f28:	d8 fa       	bnes38 $r0,9f1c <memcmp+0xc>
    9f2a:	d5 04       	j8 9f32 <memcmp+0x22>
    9f2c:	8e 04       	subi45 $r0,#0x4
    9f2e:	8e 24       	subi45 $r1,#0x4
    9f30:	8c 44       	addi45 $r2,#0x4
    9f32:	99 42       	add333 $r5,$r0,$r2
    9f34:	d0 09       	beqs38 $r0,9f46 <memcmp+0x36>
    9f36:	08 30 00 01 	lbi.bi $r3,[$r0],#0x1
    9f3a:	08 40 80 01 	lbi.bi $r4,[$r1],#0x1
    9f3e:	4c 32 3f fb 	beq $r3,$r4,9f34 <memcmp+0x24>
    9f42:	9a 1c       	sub333 $r0,$r3,$r4
    9f44:	dd 9e       	ret5 $lp
    9f46:	84 00       	movi55 $r0,#0x0
    9f48:	dd 9e       	ret5 $lp
    9f4a:	92 00       	nop16

00009f4c <memcpy>:
    9f4c:	80 60       	mov55 $r3,$r0
    9f4e:	e6 44       	slti45 $r2,#0x4
    9f50:	e9 28       	bnezs8 9fa0 <memcpy+0x54>
    9f52:	54 41 80 03 	andi $r4,$r3,#0x3
    9f56:	54 50 80 03 	andi $r5,$r1,#0x3
    9f5a:	c5 0b       	beqz38 $r5,9f70 <memcpy+0x24>
    9f5c:	52 52 80 04 	subri $r5,$r5,#0x4
    9f60:	9a 95       	sub333 $r2,$r2,$r5
    9f62:	99 69       	add333 $r5,$r5,$r1
    9f64:	08 40 80 01 	lbi.bi $r4,[$r1],#0x1
    9f68:	18 41 80 01 	sbi.bi $r4,[$r3],#0x1
    9f6c:	4c 12 ff fc 	bne $r1,$r5,9f64 <memcpy+0x18>
    9f70:	40 51 14 09 	srli $r5,$r2,#0x5
    9f74:	c5 0a       	beqz38 $r5,9f88 <memcpy+0x3c>
    9f76:	95 6d       	slli333 $r5,$r5,#0x5
    9f78:	99 69       	add333 $r5,$r5,$r1
    9f7a:	96 a7       	fexti33 $r2,#0x4
    9f7c:	3b 00 dc 04 	lmw.bim $r16,[$r1],$r23,#0x0    ! {$r16~$r23}
    9f80:	3b 01 dc 24 	smw.bim $r16,[$r3],$r23,#0x0    ! {$r16~$r23}
    9f84:	4c 12 ff fc 	bne $r1,$r5,9f7c <memcpy+0x30>
    9f88:	40 51 08 09 	srli $r5,$r2,#0x2
    9f8c:	c5 0a       	beqz38 $r5,9fa0 <memcpy+0x54>
    9f8e:	95 6a       	slli333 $r5,$r5,#0x2
    9f90:	99 69       	add333 $r5,$r5,$r1
    9f92:	96 8f       	fexti33 $r2,#0x1
    9f94:	3a 40 90 04 	lmw.bim $r4,[$r1],$r4,#0x0    ! {$r4}
    9f98:	3a 41 90 24 	smw.bim $r4,[$r3],$r4,#0x0    ! {$r4}
    9f9c:	4c 12 ff fc 	bne $r1,$r5,9f94 <memcpy+0x48>
    9fa0:	c2 08       	beqz38 $r2,9fb0 <memcpy+0x64>
    9fa2:	99 4a       	add333 $r5,$r1,$r2
    9fa4:	08 40 80 01 	lbi.bi $r4,[$r1],#0x1
    9fa8:	18 41 80 01 	sbi.bi $r4,[$r3],#0x1
    9fac:	4c 12 ff fc 	bne $r1,$r5,9fa4 <memcpy+0x58>
    9fb0:	dd 9e       	ret5 $lp
    9fb2:	92 00       	nop16

00009fb4 <memset>:
    9fb4:	80 60       	mov55 $r3,$r0
    9fb6:	e6 44       	slti45 $r2,#0x4
    9fb8:	e9 30       	bnezs8 a018 <memset+0x64>
    9fba:	54 51 80 03 	andi $r5,$r3,#0x3
    9fbe:	c5 09       	beqz38 $r5,9fd0 <memset+0x1c>
    9fc0:	52 52 80 04 	subri $r5,$r5,#0x4
    9fc4:	9a 95       	sub333 $r2,$r2,$r5
    9fc6:	99 68       	add333 $r5,$r5,$r0
    9fc8:	18 11 80 01 	sbi.bi $r1,[$r3],#0x1
    9fcc:	4c 32 ff fe 	bne $r3,$r5,9fc8 <memset+0x14>
    9fd0:	96 48       	zeb33 $r1,$r1
    9fd2:	40 40 a0 08 	slli $r4,$r1,#0x8
    9fd6:	fe 67       	or33 $r1,$r4
    9fd8:	40 40 c0 08 	slli $r4,$r1,#0x10
    9fdc:	fe 67       	or33 $r1,$r4
    9fde:	40 51 14 09 	srli $r5,$r2,#0x5
    9fe2:	4e 52 00 11 	beqz $r5,a004 <memset+0x50>
    9fe6:	95 6d       	slli333 $r5,$r5,#0x5
    9fe8:	99 6b       	add333 $r5,$r5,$r3
    9fea:	96 a7       	fexti33 $r2,#0x4
    9fec:	82 01       	mov55 $r16,$r1
    9fee:	82 21       	mov55 $r17,$r1
    9ff0:	82 41       	mov55 $r18,$r1
    9ff2:	82 61       	mov55 $r19,$r1
    9ff4:	82 81       	mov55 $r20,$r1
    9ff6:	82 a1       	mov55 $r21,$r1
    9ff8:	82 c1       	mov55 $r22,$r1
    9ffa:	82 e1       	mov55 $r23,$r1
    9ffc:	3b 01 dc 24 	smw.bim $r16,[$r3],$r23,#0x0    ! {$r16~$r23}
    a000:	4c 32 ff fe 	bne $r3,$r5,9ffc <memset+0x48>
    a004:	40 51 08 09 	srli $r5,$r2,#0x2
    a008:	c5 08       	beqz38 $r5,a018 <memset+0x64>
    a00a:	95 6a       	slli333 $r5,$r5,#0x2
    a00c:	99 6b       	add333 $r5,$r5,$r3
    a00e:	96 8f       	fexti33 $r2,#0x1
    a010:	3a 11 84 24 	smw.bim $r1,[$r3],$r1,#0x0    ! {$r1}
    a014:	4c 32 ff fe 	bne $r3,$r5,a010 <memset+0x5c>
    a018:	c2 06       	beqz38 $r2,a024 <memset+0x70>
    a01a:	99 5a       	add333 $r5,$r3,$r2
    a01c:	18 11 80 01 	sbi.bi $r1,[$r3],#0x1
    a020:	4c 32 ff fe 	bne $r3,$r5,a01c <memset+0x68>
    a024:	dd 9e       	ret5 $lp
    a026:	92 00       	nop16

0000a028 <_free_r>:
    a028:	c1 3b       	beqz38 $r1,a09e <_free_r+0x76>
    a02a:	9e 0c       	subi333 $r0,$r1,#0x4
    a02c:	04 10 ff ff 	lwi $r1,[$r1+#-4]
    a030:	4e 14 00 03 	bgez $r1,a036 <_free_r+0xe>
    a034:	88 01       	add45 $r0,$r1
    a036:	3c 1c 0a d6 	lwi.gp $r1,[+#0x2b58]
    a03a:	c1 0a       	beqz38 $r1,a04e <_free_r+0x26>
    a03c:	e2 01       	slt45 $r0,$r1
    a03e:	e8 11       	beqzs8 a060 <_free_r+0x38>
    a040:	b4 40       	lwi450 $r2,[$r0]
    a042:	99 42       	add333 $r5,$r0,$r2
    a044:	d9 05       	bnes38 $r1,a04e <_free_r+0x26>
    a046:	b4 25       	lwi450 $r1,[$r5]
    a048:	88 22       	add45 $r1,$r2
    a04a:	b6 20       	swi450 $r1,[$r0]
    a04c:	a0 69       	lwi333 $r1,[$r5+#0x4]
    a04e:	a8 41       	swi333 $r1,[$r0+#0x4]
    a050:	46 10 01 02 	sethi $r1,#0x102
    a054:	3c 0e 0a d6 	swi.gp $r0,[+#0x2b58]
    a058:	dd 9e       	ret5 $lp
    a05a:	e2 02       	slt45 $r0,$r2
    a05c:	e9 04       	bnezs8 a064 <_free_r+0x3c>
    a05e:	80 22       	mov55 $r1,$r2
    a060:	a0 89       	lwi333 $r2,[$r1+#0x4]
    a062:	ca fc       	bnez38 $r2,a05a <_free_r+0x32>
    a064:	b4 61       	lwi450 $r3,[$r1]
    a066:	99 4b       	add333 $r5,$r1,$r3
    a068:	d8 0c       	bnes38 $r0,a080 <_free_r+0x58>
    a06a:	b4 00       	lwi450 $r0,[$r0]
    a06c:	80 a1       	mov55 $r5,$r1
    a06e:	88 03       	add45 $r0,$r3
    a070:	38 02 80 0e 	sw.bi $r0,[$r5],$r0<<#0x0
    a074:	da 15       	bnes38 $r2,a09e <_free_r+0x76>
    a076:	b4 62       	lwi450 $r3,[$r2]
    a078:	88 03       	add45 $r0,$r3
    a07a:	b6 01       	swi450 $r0,[$r1]
    a07c:	a0 11       	lwi333 $r0,[$r2+#0x4]
    a07e:	d5 0f       	j8 a09c <_free_r+0x74>
    a080:	e2 05       	slt45 $r0,$r5
    a082:	e8 05       	beqzs8 a08c <_free_r+0x64>
    a084:	84 0c       	movi55 $r0,#0xc
    a086:	3c 0e 0a d4 	swi.gp $r0,[+#0x2b50]
    a08a:	dd 9e       	ret5 $lp
    a08c:	b4 80       	lwi450 $r4,[$r0]
    a08e:	99 44       	add333 $r5,$r0,$r4
    a090:	da 05       	bnes38 $r2,a09a <_free_r+0x72>
    a092:	b4 62       	lwi450 $r3,[$r2]
    a094:	a0 91       	lwi333 $r2,[$r2+#0x4]
    a096:	88 64       	add45 $r3,$r4
    a098:	b6 60       	swi450 $r3,[$r0]
    a09a:	a8 81       	swi333 $r2,[$r0+#0x4]
    a09c:	a8 09       	swi333 $r0,[$r1+#0x4]
    a09e:	dd 9e       	ret5 $lp

0000a0a0 <_malloc_r>:
    a0a0:	fc 21       	push25 $r8,#8    ! {$r6~$r8, $fp, $gp, $lp}
    a0a2:	3f c8 2b 50 	addi.gp $fp,#0x2b50
    a0a6:	9d 8b       	addi333 $r6,$r1,#0x3
    a0a8:	66 63 00 03 	bitci $r6,$r6,#0x3
    a0ac:	8c c8       	addi45 $r6,#0x8
    a0ae:	e6 cc       	slti45 $r6,#0xc
    a0b0:	e8 03       	beqzs8 a0b6 <_malloc_r+0x16>
    a0b2:	84 cc       	movi55 $r6,#0xc
    a0b4:	d5 07       	j8 a0c2 <_malloc_r+0x22>
    a0b6:	4e 64 00 06 	bgez $r6,a0c2 <_malloc_r+0x22>
    a0ba:	84 0c       	movi55 $r0,#0xc
    a0bc:	b8 80       	swi37 $r0,[$fp+#0x0]
    a0be:	84 00       	movi55 $r0,#0x0
    a0c0:	d5 42       	j8 a144 <_malloc_r+0xa4>
    a0c2:	e2 c1       	slt45 $r6,$r1
    a0c4:	e9 fb       	bnezs8 a0ba <_malloc_r+0x1a>
    a0c6:	bd 02       	lwi37 $r5,[$fp+#0x8]
    a0c8:	80 25       	mov55 $r1,$r5
    a0ca:	c1 0c       	beqz38 $r1,a0e2 <_malloc_r+0x42>
    a0cc:	b4 41       	lwi450 $r2,[$r1]
    a0ce:	8a 46       	sub45 $r2,$r6
    a0d0:	4e 25 00 19 	bltz $r2,a102 <_malloc_r+0x62>
    a0d4:	e6 4c       	slti45 $r2,#0xc
    a0d6:	e9 0e       	bnezs8 a0f2 <_malloc_r+0x52>
    a0d8:	80 a1       	mov55 $r5,$r1
    a0da:	38 22 88 0e 	sw.bi $r2,[$r5],$r2<<#0x0
    a0de:	b6 c5       	swi450 $r6,[$r5]
    a0e0:	cd 28       	bnez38 $r5,a130 <_malloc_r+0x90>
    a0e2:	f0 81       	swi37.sp $r0,[+#0x4]
    a0e4:	b9 01       	lwi37 $r1,[$fp+#0x4]
    a0e6:	c9 11       	bnez38 $r1,a108 <_malloc_r+0x68>
    a0e8:	f0 01       	lwi37.sp $r0,[+#0x4]
    a0ea:	49 00 00 2e 	jal a146 <_sbrk_r>
    a0ee:	b8 81       	swi37 $r0,[$fp+#0x4]
    a0f0:	d5 0c       	j8 a108 <_malloc_r+0x68>
    a0f2:	d9 04       	bnes38 $r1,a0fa <_malloc_r+0x5a>
    a0f4:	a0 29       	lwi333 $r0,[$r5+#0x4]
    a0f6:	b8 82       	swi37 $r0,[$fp+#0x8]
    a0f8:	d5 1c       	j8 a130 <_malloc_r+0x90>
    a0fa:	a0 09       	lwi333 $r0,[$r1+#0x4]
    a0fc:	a8 29       	swi333 $r0,[$r5+#0x4]
    a0fe:	80 a1       	mov55 $r5,$r1
    a100:	d5 18       	j8 a130 <_malloc_r+0x90>
    a102:	80 a1       	mov55 $r5,$r1
    a104:	a0 49       	lwi333 $r1,[$r1+#0x4]
    a106:	d5 e2       	j8 a0ca <_malloc_r+0x2a>
    a108:	f0 01       	lwi37.sp $r0,[+#0x4]
    a10a:	80 26       	mov55 $r1,$r6
    a10c:	49 00 00 1d 	jal a146 <_sbrk_r>
    a110:	80 a0       	mov55 $r5,$r0
    a112:	5a 07 ff d4 	beqc $r0,#-1,a0ba <_malloc_r+0x1a>
    a116:	9d c3       	addi333 $r7,$r0,#0x3
    a118:	66 73 80 03 	bitci $r7,$r7,#0x3
    a11c:	4c 70 00 09 	beq $r7,$r0,a12e <_malloc_r+0x8e>
    a120:	f0 01       	lwi37.sp $r0,[+#0x4]
    a122:	9a 7d       	sub333 $r1,$r7,$r5
    a124:	49 00 00 11 	jal a146 <_sbrk_r>
    a128:	5a 07 ff c9 	beqc $r0,#-1,a0ba <_malloc_r+0x1a>
    a12c:	80 a7       	mov55 $r5,$r7
    a12e:	b6 c5       	swi450 $r6,[$r5]
    a130:	50 02 80 0b 	addi $r0,$r5,#0xb
    a134:	9c 6c       	addi333 $r1,$r5,#0x4
    a136:	66 00 00 07 	bitci $r0,$r0,#0x7
    a13a:	9a 41       	sub333 $r1,$r0,$r1
    a13c:	c1 04       	beqz38 $r1,a144 <_malloc_r+0xa4>
    a13e:	fe 8a       	neg33 $r2,$r1
    a140:	38 22 84 0a 	sw $r2,[$r5+($r1<<#0x0)]
    a144:	fc a1       	pop25 $r8,#8    ! {$r6~$r8, $fp, $gp, $lp}

0000a146 <_sbrk_r>:
    a146:	fc 00       	push25 $r6,#0    ! {$r6, $fp, $gp, $lp}
    a148:	84 00       	movi55 $r0,#0x0
    a14a:	3c 0e 00 23 	swi.gp $r0,[+#0x8c]
    a14e:	80 01       	mov55 $r0,$r1
    a150:	49 00 09 9c 	jal b488 <_sbrk>
    a154:	5a 0f ff 07 	bnec $r0,#-1,a162 <_sbrk_r+0x1c>
    a158:	3c 1c 00 23 	lwi.gp $r1,[+#0x8c]
    a15c:	c1 03       	beqz38 $r1,a162 <_sbrk_r+0x1c>
    a15e:	3c 1e 0a d4 	swi.gp $r1,[+#0x2b50]
    a162:	fc 80       	pop25 $r6,#0    ! {$r6, $fp, $gp, $lp}

0000a164 <__sread>:
    a164:	fc 00       	push25 $r6,#0    ! {$r6, $fp, $gp, $lp}
    a166:	80 c1       	mov55 $r6,$r1
    a168:	22 10 80 07 	lhsi $r1,[$r1+#0xe]
    a16c:	49 00 09 32 	jal b3d0 <_read_r>
    a170:	4e 05 00 07 	bltz $r0,a17e <__sread+0x1a>
    a174:	83 86       	mov55 $fp,$r6
    a176:	b9 14       	lwi37 $r1,[$fp+#0x50]
    a178:	88 20       	add45 $r1,$r0
    a17a:	b9 94       	swi37 $r1,[$fp+#0x50]
    a17c:	fc 80       	pop25 $r6,#0    ! {$r6, $fp, $gp, $lp}
    a17e:	a4 76       	lhi333 $r1,[$r6+#0xc]
    a180:	66 10 90 00 	bitci $r1,$r1,#0x1000
    a184:	ac 76       	shi333 $r1,[$r6+#0xc]
    a186:	fc 80       	pop25 $r6,#0    ! {$r6, $fp, $gp, $lp}

0000a188 <__swrite>:
    a188:	fc 02       	push25 $r6,#16    ! {$r6, $fp, $gp, $lp}
    a18a:	80 c1       	mov55 $r6,$r1
    a18c:	a4 4e       	lhi333 $r1,[$r1+#0xc]
    a18e:	f0 81       	swi37.sp $r0,[+#0x4]
    a190:	54 10 81 00 	andi $r1,$r1,#0x100
    a194:	f2 82       	swi37.sp $r2,[+#0x8]
    a196:	f3 83       	swi37.sp $r3,[+#0xc]
    a198:	c1 07       	beqz38 $r1,a1a6 <__swrite+0x1e>
    a19a:	22 13 00 07 	lhsi $r1,[$r6+#0xe]
    a19e:	84 40       	movi55 $r2,#0x0
    a1a0:	84 62       	movi55 $r3,#0x2
    a1a2:	49 00 07 f3 	jal b188 <_lseek_r>
    a1a6:	a4 36       	lhi333 $r0,[$r6+#0xc]
    a1a8:	22 13 00 07 	lhsi $r1,[$r6+#0xe]
    a1ac:	66 00 10 00 	bitci $r0,$r0,#0x1000
    a1b0:	ac 36       	shi333 $r0,[$r6+#0xc]
    a1b2:	f2 02       	lwi37.sp $r2,[+#0x8]
    a1b4:	f0 01       	lwi37.sp $r0,[+#0x4]
    a1b6:	f3 03       	lwi37.sp $r3,[+#0xc]
    a1b8:	49 00 05 d6 	jal ad64 <_write_r>
    a1bc:	fc 82       	pop25 $r6,#16    ! {$r6, $fp, $gp, $lp}

0000a1be <__sseek>:
    a1be:	fc 00       	push25 $r6,#0    ! {$r6, $fp, $gp, $lp}
    a1c0:	80 c1       	mov55 $r6,$r1
    a1c2:	22 10 80 07 	lhsi $r1,[$r1+#0xe]
    a1c6:	49 00 07 e1 	jal b188 <_lseek_r>
    a1ca:	a4 b6       	lhi333 $r2,[$r6+#0xc]
    a1cc:	5a 0f ff 06 	bnec $r0,#-1,a1d8 <__sseek+0x1a>
    a1d0:	66 21 10 00 	bitci $r2,$r2,#0x1000
    a1d4:	ac b6       	shi333 $r2,[$r6+#0xc]
    a1d6:	fc 80       	pop25 $r6,#0    ! {$r6, $fp, $gp, $lp}
    a1d8:	58 21 10 00 	ori $r2,$r2,#0x1000
    a1dc:	ac b6       	shi333 $r2,[$r6+#0xc]
    a1de:	14 03 00 14 	swi $r0,[$r6+#0x50]
    a1e2:	fc 80       	pop25 $r6,#0    ! {$r6, $fp, $gp, $lp}

0000a1e4 <__sclose>:
    a1e4:	fc 00       	push25 $r6,#0    ! {$r6, $fp, $gp, $lp}
    a1e6:	22 10 80 07 	lhsi $r1,[$r1+#0xe]
    a1ea:	49 00 06 2a 	jal ae3e <_close_r>
    a1ee:	fc 80       	pop25 $r6,#0    ! {$r6, $fp, $gp, $lp}

0000a1f0 <strchr>:
    a1f0:	28 50 00 01 	lbsi.bi $r5,[$r0],#0x1
    a1f4:	d1 04       	beqs38 $r1,a1fc <strchr+0xc>
    a1f6:	cd fd       	bnez38 $r5,a1f0 <strchr>
    a1f8:	80 05       	mov55 $r0,$r5
    a1fa:	dd 9e       	ret5 $lp
    a1fc:	9e 01       	subi333 $r0,$r0,#0x1
    a1fe:	dd 9e       	ret5 $lp

0000a200 <strcmp>:
    a200:	3a 20 08 06 	lmwzb.bm $r2,[$r0],$r2,#0x0    ! {$r2}
    a204:	3a 30 8c 06 	lmwzb.bm $r3,[$r1],$r3,#0x0    ! {$r3}
    a208:	42 41 0c 17 	ffzmism $r4,$r2,$r3
    a20c:	c4 fa       	beqz38 $r4,a200 <strcmp>
    a20e:	38 20 10 00 	lb $r2,[$r0+($r4<<#0x0)]
    a212:	38 30 90 00 	lb $r3,[$r1+($r4<<#0x0)]
    a216:	9a 13       	sub333 $r0,$r2,$r3
    a218:	dd 9e       	ret5 $lp
    a21a:	92 00       	nop16

0000a21c <strcpy>:
    a21c:	80 60       	mov55 $r3,$r0
    a21e:	3a 40 90 06 	lmwzb.bm $r4,[$r1],$r4,#0x0    ! {$r4}
    a222:	3a 41 90 26 	smwzb.bm $r4,[$r3],$r4,#0x0    ! {$r4}
    a226:	42 22 10 17 	ffzmism $r2,$r4,$r4
    a22a:	c2 fa       	beqz38 $r2,a21e <strcpy+0x2>
    a22c:	dd 9e       	ret5 $lp
    a22e:	92 00       	nop16

0000a230 <strcspn>:
    a230:	80 40       	mov55 $r2,$r0
    a232:	28 41 00 01 	lbsi.bi $r4,[$r2],#0x1
    a236:	c4 06       	beqz38 $r4,a242 <strcspn+0x12>
    a238:	80 61       	mov55 $r3,$r1
    a23a:	28 51 80 01 	lbsi.bi $r5,[$r3],#0x1
    a23e:	c5 fa       	beqz38 $r5,a232 <strcspn+0x2>
    a240:	dc fd       	bnes38 $r4,a23a <strcspn+0xa>
    a242:	9e 91       	subi333 $r2,$r2,#0x1
    a244:	9a 10       	sub333 $r0,$r2,$r0
    a246:	dd 9e       	ret5 $lp

0000a248 <strlen>:
    a248:	9c 81       	addi333 $r2,$r0,#0x1
    a24a:	08 50 00 01 	lbi.bi $r5,[$r0],#0x1
    a24e:	cd fe       	bnez38 $r5,a24a <strlen+0x2>
    a250:	9a 02       	sub333 $r0,$r0,$r2
    a252:	dd 9e       	ret5 $lp

0000a254 <strspn>:
    a254:	80 40       	mov55 $r2,$r0
    a256:	28 41 00 01 	lbsi.bi $r4,[$r2],#0x1
    a25a:	c4 07       	beqz38 $r4,a268 <strspn+0x14>
    a25c:	80 61       	mov55 $r3,$r1
    a25e:	28 51 80 01 	lbsi.bi $r5,[$r3],#0x1
    a262:	c5 03       	beqz38 $r5,a268 <strspn+0x14>
    a264:	dc fd       	bnes38 $r4,a25e <strspn+0xa>
    a266:	d5 f8       	j8 a256 <strspn+0x2>
    a268:	9e 91       	subi333 $r2,$r2,#0x1
    a26a:	9a 10       	sub333 $r0,$r2,$r0
    a26c:	dd 9e       	ret5 $lp
    a26e:	92 00       	nop16

0000a270 <strtol>:
    a270:	fc 00       	push25 $r6,#0    ! {$r6, $fp, $gp, $lp}
    a272:	84 60       	movi55 $r3,#0x0
    a274:	49 00 00 03 	jal a27a <strtol_common>
    a278:	fc 80       	pop25 $r6,#0    ! {$r6, $fp, $gp, $lp}

0000a27a <strtol_common>:
    a27a:	fc 61       	push25 $r14,#8    ! {$r6~$r14, $fp, $gp, $lp}
    a27c:	36 3f 80 00 	fsdi $fd3,[$sp+#0x0]
    a280:	81 c0       	mov55 $r14,$r0
    a282:	81 01       	mov55 $r8,$r1
    a284:	81 22       	mov55 $r9,$r2
    a286:	83 83       	mov55 $fp,$r3
    a288:	81 40       	mov55 $r10,$r0
    a28a:	80 ea       	mov55 $r7,$r10
    a28c:	08 63 80 01 	lbi.bi $r6,[$r7],#0x1
    a290:	80 06       	mov55 $r0,$r6
    a292:	49 00 08 92 	jal b3b6 <nds_isspace>
    a296:	c0 03       	beqz38 $r0,a29c <strtol_common+0x22>
    a298:	81 47       	mov55 $r10,$r7
    a29a:	d5 f8       	j8 a28a <strtol_common+0x10>
    a29c:	5a 68 2d 08 	bnec $r6,#0x2d,a2ac <strtol_common+0x32>
    a2a0:	50 75 00 02 	addi $r7,$r10,#0x2
    a2a4:	00 65 00 01 	lbi $r6,[$r10+#0x1]
    a2a8:	85 61       	movi55 $r11,#0x1
    a2aa:	d5 08       	j8 a2ba <strtol_common+0x40>
    a2ac:	5a 68 2b 06 	bnec $r6,#0x2b,a2b8 <strtol_common+0x3e>
    a2b0:	50 75 00 02 	addi $r7,$r10,#0x2
    a2b4:	00 65 00 01 	lbi $r6,[$r10+#0x1]
    a2b8:	81 60       	mov55 $r11,$r0
    a2ba:	4e 92 00 05 	beqz $r9,a2c4 <strtol_common+0x4a>
    a2be:	5a 98 10 0d 	bnec $r9,#0x10,a2d8 <strtol_common+0x5e>
    a2c2:	d5 6f       	j8 a3a0 <strtol_common+0x126>
    a2c4:	5a 68 30 6c 	bnec $r6,#0x30,a39c <strtol_common+0x122>
    a2c8:	a6 38       	lbi333 $r0,[$r7+#0x0]
    a2ca:	54 00 00 df 	andi $r0,$r0,#0xdf
    a2ce:	5a 08 58 61 	bnec $r0,#0x58,a390 <strtol_common+0x116>
    a2d2:	a7 b9       	lbi333 $r6,[$r7+#0x1]
    a2d4:	fb 20       	movpi45 $r9,#0x10
    a2d6:	8c e2       	addi45 $r7,#0x2
    a2d8:	85 5f       	movi55 $r10,#-1
    a2da:	4f c3 00 0b 	bnez $fp,a2f0 <strtol_common+0x76>
    a2de:	4e b3 00 07 	bnez $r11,a2ec <strtol_common+0x72>
    a2e2:	46 a7 ff ff 	sethi $r10,#0x7ffff
    a2e6:	50 a5 0f ff 	addi $r10,$r10,#0xfff
    a2ea:	d5 03       	j8 a2f0 <strtol_common+0x76>
    a2ec:	46 a8 00 00 	sethi $r10,#0x80000
    a2f0:	40 a5 24 17 	divr $r10,$r0,$r10,$r9
    a2f4:	6a 03 00 09 	fmtsr $r0,$fs6
    a2f8:	85 80       	movi55 $r12,#0x0
    a2fa:	81 ac       	mov55 $r13,$r12
    a2fc:	80 06       	mov55 $r0,$r6
    a2fe:	49 00 08 57 	jal b3ac <nds_isdigit>
    a302:	c0 04       	beqz38 $r0,a30a <strtol_common+0x90>
    a304:	50 63 7f d0 	addi $r6,$r6,#-48
    a308:	d5 0f       	j8 a326 <strtol_common+0xac>
    a30a:	80 06       	mov55 $r0,$r6
    a30c:	49 00 08 49 	jal b39e <nds_isalpha>
    a310:	c0 20       	beqz38 $r0,a350 <strtol_common+0xd6>
    a312:	80 06       	mov55 $r0,$r6
    a314:	49 00 08 59 	jal b3c6 <nds_isupper>
    a318:	c8 04       	bnez38 $r0,a320 <strtol_common+0xa6>
    a31a:	44 00 00 57 	movi $r0,#0x57
    a31e:	d5 03       	j8 a324 <strtol_common+0xaa>
    a320:	44 00 00 37 	movi $r0,#0x37
    a324:	8a c0       	sub45 $r6,$r0
    a326:	e0 c9       	slts45 $r6,$r9
    a328:	e8 14       	beqzs8 a350 <strtol_common+0xd6>
    a32a:	5a c7 ff 10 	beqc $r12,#-1,a34a <strtol_common+0xd0>
    a32e:	e3 4d       	slt45 $r10,$r13
    a330:	e9 0c       	bnezs8 a348 <strtol_common+0xce>
    a332:	4c d5 40 06 	bne $r13,$r10,a33e <strtol_common+0xc4>
    a336:	6a 03 00 01 	fmfsr $r0,$fs6
    a33a:	e0 06       	slts45 $r0,$r6
    a33c:	e9 06       	bnezs8 a348 <strtol_common+0xce>
    a33e:	42 66 a4 73 	maddr32 $r6,$r13,$r9
    a342:	85 81       	movi55 $r12,#0x1
    a344:	81 a6       	mov55 $r13,$r6
    a346:	d5 02       	j8 a34a <strtol_common+0xd0>
    a348:	85 9f       	movi55 $r12,#-1
    a34a:	08 63 80 01 	lbi.bi $r6,[$r7],#0x1
    a34e:	d5 d7       	j8 a2fc <strtol_common+0x82>
    a350:	80 4d       	mov55 $r2,$r13
    a352:	4e c4 00 12 	bgez $r12,a376 <strtol_common+0xfc>
    a356:	84 5f       	movi55 $r2,#-1
    a358:	4f c3 00 0b 	bnez $fp,a36e <strtol_common+0xf4>
    a35c:	4e b3 00 07 	bnez $r11,a36a <strtol_common+0xf0>
    a360:	46 27 ff ff 	sethi $r2,#0x7ffff
    a364:	50 21 0f ff 	addi $r2,$r2,#0xfff
    a368:	d5 03       	j8 a36e <strtol_common+0xf4>
    a36a:	46 28 00 00 	sethi $r2,#0x80000
    a36e:	fa 12       	movpi45 $r0,#0x22
    a370:	3c 0e 0a d4 	swi.gp $r0,[+#0x2b50]
    a374:	d5 05       	j8 a37e <strtol_common+0x104>
    a376:	4e b2 00 04 	beqz $r11,a37e <strtol_common+0x104>
    a37a:	52 26 80 00 	subri $r2,$r13,#0x0
    a37e:	4e 82 00 14 	beqz $r8,a3a6 <strtol_common+0x12c>
    a382:	4e c2 00 04 	beqz $r12,a38a <strtol_common+0x110>
    a386:	8e e1       	subi45 $r7,#0x1
    a388:	d5 02       	j8 a38c <strtol_common+0x112>
    a38a:	80 ee       	mov55 $r7,$r14
    a38c:	b6 e8       	swi450 $r7,[$r8]
    a38e:	d5 0c       	j8 a3a6 <strtol_common+0x12c>
    a390:	44 60 00 30 	movi $r6,#0x30
    a394:	4e 93 ff a2 	bnez $r9,a2d8 <strtol_common+0x5e>
    a398:	85 28       	movi55 $r9,#0x8
    a39a:	d5 9f       	j8 a2d8 <strtol_common+0x5e>
    a39c:	85 2a       	movi55 $r9,#0xa
    a39e:	d5 9d       	j8 a2d8 <strtol_common+0x5e>
    a3a0:	5a 68 30 9c 	bnec $r6,#0x30,a2d8 <strtol_common+0x5e>
    a3a4:	d5 92       	j8 a2c8 <strtol_common+0x4e>
    a3a6:	80 02       	mov55 $r0,$r2
    a3a8:	34 3f 80 00 	fldi $fd3,[$sp+#0x0]
    a3ac:	fc e1       	pop25 $r14,#8    ! {$r6~$r14, $fp, $gp, $lp}

0000a3ae <strtoul>:
    a3ae:	fc 00       	push25 $r6,#0    ! {$r6, $fp, $gp, $lp}
    a3b0:	84 61       	movi55 $r3,#0x1
    a3b2:	49 ff ff 64 	jal a27a <strtol_common>
    a3b6:	fc 80       	pop25 $r6,#0    ! {$r6, $fp, $gp, $lp}

0000a3b8 <__sprint_r>:
    a3b8:	fc 01       	push25 $r6,#8    ! {$r6, $fp, $gp, $lp}
    a3ba:	a1 12       	lwi333 $r4,[$r2+#0x8]
    a3bc:	cc 04       	bnez38 $r4,a3c4 <__sprint_r+0xc>
    a3be:	a9 11       	swi333 $r4,[$r2+#0x4]
    a3c0:	f4 81       	swi37.sp $r4,[+#0x4]
    a3c2:	d5 08       	j8 a3d2 <__sprint_r+0x1a>
    a3c4:	80 c2       	mov55 $r6,$r2
    a3c6:	49 00 05 8e 	jal aee2 <__sfvwrite_r>
    a3ca:	84 20       	movi55 $r1,#0x0
    a3cc:	a8 72       	swi333 $r1,[$r6+#0x8]
    a3ce:	a8 71       	swi333 $r1,[$r6+#0x4]
    a3d0:	f0 81       	swi37.sp $r0,[+#0x4]
    a3d2:	f0 01       	lwi37.sp $r0,[+#0x4]
    a3d4:	fc 81       	pop25 $r6,#8    ! {$r6, $fp, $gp, $lp}
    a3d6:	00 00 30 31 	lbi $r0,[$r0+#0x3031]
    a3da:	32 33 34 35 	cpswi.bi cp1,$cpr3,[$r6],#0x10d4
    a3de:	36 37 38 39 	cpsdi.bi cp1,$cpr3,[$r14],#-7964
    a3e2:	41 42 43 44 	or_slli $r20,$r4,$r16,#0x1a
    a3e6:	45 46 00 00 	movi $r20,#0x60000
    a3ea:	00 00 30 31 	lbi $r0,[$r0+#0x3031]
    a3ee:	32 33 34 35 	cpswi.bi cp1,$cpr3,[$r6],#0x10d4
    a3f2:	36 37 38 39 	cpsdi.bi cp1,$cpr3,[$r14],#-7964
    a3f6:	61 62 63 64 	amtbsl2.l $d1,$r2,$r6,$r0,$r1,[$i0],[$i4],$m1,$m6
    a3fa:	65 66 00 00 	*unknown*
	...

0000a400 <_vfiprintf_r>:
    a400:	fc 76       	push25 $r14,#176    ! {$r6~$r14, $fp, $gp, $lp}
    a402:	36 3f 80 22 	fsdi $fd3,[$sp+#0x88]
    a406:	36 4f 80 24 	fsdi $fd4,[$sp+#0x90]
    a40a:	36 5f 80 26 	fsdi $fd5,[$sp+#0x98]
    a40e:	36 6f 80 28 	fsdi $fd6,[$sp+#0xa0]
    a412:	36 7f 80 2a 	fsdi $fd7,[$sp+#0xa8]
    a416:	81 61       	mov55 $r11,$r1
    a418:	3c 1c 0a d8 	lwi.gp $r1,[+#0x2b60]
    a41c:	b6 1f       	swi450 $r0,[$sp]
    a41e:	81 82       	mov55 $r12,$r2
    a420:	80 c3       	mov55 $r6,$r3
    a422:	c9 03       	bnez38 $r1,a428 <_vfiprintf_r+0x28>
    a424:	49 ff fc ce 	jal 9dc0 <__sinit>
    a428:	02 05 80 06 	lhi $r0,[$r11+#0xc]
    a42c:	96 1e       	bmski33 $r0,#0x3
    a42e:	c0 0b       	beqz38 $r0,a444 <_vfiprintf_r+0x44>
    a430:	04 05 80 04 	lwi $r0,[$r11+#0x10]
    a434:	c0 08       	beqz38 $r0,a444 <_vfiprintf_r+0x44>
    a436:	02 05 80 06 	lhi $r0,[$r11+#0xc]
    a43a:	54 00 00 1a 	andi $r0,$r0,#0x1a
    a43e:	5a 08 0a 17 	bnec $r0,#0xa,a46c <_vfiprintf_r+0x6c>
    a442:	d5 09       	j8 a454 <_vfiprintf_r+0x54>
    a444:	b4 1f       	lwi450 $r0,[$sp]
    a446:	80 2b       	mov55 $r1,$r11
    a448:	49 00 04 9f 	jal ad86 <__swsetup_r>
    a44c:	c0 f5       	beqz38 $r0,a436 <_vfiprintf_r+0x36>
    a44e:	84 1f       	movi55 $r0,#-1
    a450:	48 00 04 39 	j acc2 <_vfiprintf_r+0x8c2>
    a454:	22 05 80 07 	lhsi $r0,[$r11+#0xe]
    a458:	4e 05 00 0a 	bltz $r0,a46c <_vfiprintf_r+0x6c>
    a45c:	b4 1f       	lwi450 $r0,[$sp]
    a45e:	80 2b       	mov55 $r1,$r11
    a460:	80 4c       	mov55 $r2,$r12
    a462:	80 66       	mov55 $r3,$r6
    a464:	49 00 04 3a 	jal acd8 <__sbprintf>
    a468:	48 00 04 2d 	j acc2 <_vfiprintf_r+0x8c2>
    a46c:	84 00       	movi55 $r0,#0x0
    a46e:	f0 87       	swi37.sp $r0,[+#0x1c]
    a470:	f0 86       	swi37.sp $r0,[+#0x18]
    a472:	6a 05 00 09 	fmtsr $r0,$fs10
    a476:	80 e0       	mov55 $r7,$r0
    a478:	84 0a       	movi55 $r0,#0xa
    a47a:	6a 03 00 09 	fmtsr $r0,$fs6
    a47e:	44 00 ad 54 	movi $r0,#0xad54
    a482:	6a 04 00 09 	fmtsr $r0,$fs8
    a486:	6a 03 80 09 	fmtsr $r0,$fs7
    a48a:	50 8f 80 48 	addi $r8,$sp,#0x48
    a48e:	14 8f 80 05 	swi $r8,[$sp+#0x14]
    a492:	80 88       	mov55 $r4,$r8
    a494:	80 0c       	mov55 $r0,$r12
    a496:	81 20       	mov55 $r9,$r0
    a498:	28 10 00 01 	lbsi.bi $r1,[$r0],#0x1
    a49c:	c9 06       	bnez38 $r1,a4a8 <_vfiprintf_r+0xa8>
    a49e:	40 a4 b0 01 	sub $r10,$r9,$r12
    a4a2:	4e a3 00 06 	bnez $r10,a4ae <_vfiprintf_r+0xae>
    a4a6:	d5 1b       	j8 a4dc <_vfiprintf_r+0xdc>
    a4a8:	5a 18 25 f7 	bnec $r1,#0x25,a496 <_vfiprintf_r+0x96>
    a4ac:	d5 f9       	j8 a49e <_vfiprintf_r+0x9e>
    a4ae:	f0 07       	lwi37.sp $r0,[+#0x1c]
    a4b0:	14 c2 00 00 	swi $r12,[$r4+#0x0]
    a4b4:	88 0a       	add45 $r0,$r10
    a4b6:	f0 87       	swi37.sp $r0,[+#0x1c]
    a4b8:	f0 06       	lwi37.sp $r0,[+#0x18]
    a4ba:	14 a2 00 01 	swi $r10,[$r4+#0x4]
    a4be:	8c 01       	addi45 $r0,#0x1
    a4c0:	e4 08       	sltsi45 $r0,#0x8
    a4c2:	f0 86       	swi37.sp $r0,[+#0x18]
    a4c4:	e8 03       	beqzs8 a4ca <_vfiprintf_r+0xca>
    a4c6:	8c 88       	addi45 $r4,#0x8
    a4c8:	d5 09       	j8 a4da <_vfiprintf_r+0xda>
    a4ca:	b4 1f       	lwi450 $r0,[$sp]
    a4cc:	80 2b       	mov55 $r1,$r11
    a4ce:	b0 85       	addri36.sp $r2,#0x14
    a4d0:	49 ff ff 74 	jal a3b8 <__sprint_r>
    a4d4:	4e 03 03 ea 	bnez $r0,aca8 <_vfiprintf_r+0x8a8>
    a4d8:	80 88       	mov55 $r4,$r8
    a4da:	88 ea       	add45 $r7,$r10
    a4dc:	20 04 80 00 	lbsi $r0,[$r9+#0x0]
    a4e0:	4e 02 03 dd 	beqz $r0,ac9a <_vfiprintf_r+0x89a>
    a4e4:	84 60       	movi55 $r3,#0x0
    a4e6:	84 00       	movi55 $r0,#0x0
    a4e8:	85 df       	movi55 $r14,#-1
    a4ea:	50 14 80 01 	addi $r1,$r9,#0x1
    a4ee:	10 0f 80 0f 	sbi $r0,[$sp+#0xf]
    a4f2:	81 a3       	mov55 $r13,$r3
    a4f4:	83 83       	mov55 $fp,$r3
    a4f6:	82 0e       	mov55 $r16,$r14
    a4f8:	50 c0 80 01 	addi $r12,$r1,#0x1
    a4fc:	20 20 80 00 	lbsi $r2,[$r1+#0x0]
    a500:	5a 28 58 04 	bnec $r2,#0x58,a508 <_vfiprintf_r+0x108>
    a504:	48 00 00 9d 	j a63e <_vfiprintf_r+0x23e>
    a508:	5e f1 00 59 	sltsi $r15,$r2,#0x59
    a50c:	e8 45       	beqzs8 a596 <_vfiprintf_r+0x196>
    a50e:	5a 28 2e 04 	bnec $r2,#0x2e,a516 <_vfiprintf_r+0x116>
    a512:	48 00 00 b1 	j a674 <_vfiprintf_r+0x274>
    a516:	5e f1 00 2f 	sltsi $r15,$r2,#0x2f
    a51a:	e8 1e       	beqzs8 a556 <_vfiprintf_r+0x156>
    a51c:	5a 28 2a 04 	bnec $r2,#0x2a,a524 <_vfiprintf_r+0x124>
    a520:	48 00 00 9b 	j a656 <_vfiprintf_r+0x256>
    a524:	5e f1 00 2b 	sltsi $r15,$r2,#0x2b
    a528:	e8 0d       	beqzs8 a542 <_vfiprintf_r+0x142>
    a52a:	5a 28 20 04 	bnec $r2,#0x20,a532 <_vfiprintf_r+0x132>
    a52e:	48 00 00 90 	j a64e <_vfiprintf_r+0x24e>
    a532:	5a 20 23 04 	beqc $r2,#0x23,a53a <_vfiprintf_r+0x13a>
    a536:	48 00 02 4c 	j a9ce <_vfiprintf_r+0x5ce>
    a53a:	59 ce 00 01 	ori $fp,$fp,#0x1
    a53e:	80 2c       	mov55 $r1,$r12
    a540:	d5 dc       	j8 a4f8 <_vfiprintf_r+0xf8>
    a542:	5a 28 2b 04 	bnec $r2,#0x2b,a54a <_vfiprintf_r+0x14a>
    a546:	80 62       	mov55 $r3,$r2
    a548:	d5 fb       	j8 a53e <_vfiprintf_r+0x13e>
    a54a:	5a 28 2d 04 	bnec $r2,#0x2d,a552 <_vfiprintf_r+0x152>
    a54e:	48 00 00 8f 	j a66c <_vfiprintf_r+0x26c>
    a552:	48 00 02 3e 	j a9ce <_vfiprintf_r+0x5ce>
    a556:	5e f1 00 3a 	sltsi $r15,$r2,#0x3a
    a55a:	e8 0c       	beqzs8 a572 <_vfiprintf_r+0x172>
    a55c:	5e f1 00 31 	sltsi $r15,$r2,#0x31
    a560:	4e f2 00 ad 	beqz $r15,a6ba <_vfiprintf_r+0x2ba>
    a564:	5a 20 30 04 	beqc $r2,#0x30,a56c <_vfiprintf_r+0x16c>
    a568:	48 00 02 33 	j a9ce <_vfiprintf_r+0x5ce>
    a56c:	59 ce 00 80 	ori $fp,$fp,#0x80
    a570:	d5 e7       	j8 a53e <_vfiprintf_r+0x13e>
    a572:	5a 28 4f 04 	bnec $r2,#0x4f,a57a <_vfiprintf_r+0x17a>
    a576:	48 00 01 16 	j a7a2 <_vfiprintf_r+0x3a2>
    a57a:	5a 28 55 04 	bnec $r2,#0x55,a582 <_vfiprintf_r+0x182>
    a57e:	48 00 01 58 	j a82e <_vfiprintf_r+0x42e>
    a582:	5a 20 44 04 	beqc $r2,#0x44,a58a <_vfiprintf_r+0x18a>
    a586:	48 00 02 24 	j a9ce <_vfiprintf_r+0x5ce>
    a58a:	10 3f 80 0f 	sbi $r3,[$sp+#0xf]
    a58e:	59 ce 00 10 	ori $fp,$fp,#0x10
    a592:	48 00 00 c1 	j a714 <_vfiprintf_r+0x314>
    a596:	5a 28 6e 04 	bnec $r2,#0x6e,a59e <_vfiprintf_r+0x19e>
    a59a:	48 00 00 ea 	j a76e <_vfiprintf_r+0x36e>
    a59e:	5e f1 00 6f 	sltsi $r15,$r2,#0x6f
    a5a2:	e8 18       	beqzs8 a5d2 <_vfiprintf_r+0x1d2>
    a5a4:	5a 28 68 04 	bnec $r2,#0x68,a5ac <_vfiprintf_r+0x1ac>
    a5a8:	48 00 00 99 	j a6da <_vfiprintf_r+0x2da>
    a5ac:	5e f1 00 69 	sltsi $r15,$r2,#0x69
    a5b0:	e8 09       	beqzs8 a5c2 <_vfiprintf_r+0x1c2>
    a5b2:	5a 28 63 04 	bnec $r2,#0x63,a5ba <_vfiprintf_r+0x1ba>
    a5b6:	48 00 00 a5 	j a700 <_vfiprintf_r+0x300>
    a5ba:	5a 20 64 3f 	beqc $r2,#0x64,a638 <_vfiprintf_r+0x238>
    a5be:	48 00 02 08 	j a9ce <_vfiprintf_r+0x5ce>
    a5c2:	5a 20 69 3b 	beqc $r2,#0x69,a638 <_vfiprintf_r+0x238>
    a5c6:	5a 28 6c 04 	bnec $r2,#0x6c,a5ce <_vfiprintf_r+0x1ce>
    a5ca:	48 00 00 8c 	j a6e2 <_vfiprintf_r+0x2e2>
    a5ce:	48 00 02 00 	j a9ce <_vfiprintf_r+0x5ce>
    a5d2:	5a 28 71 04 	bnec $r2,#0x71,a5da <_vfiprintf_r+0x1da>
    a5d6:	48 00 00 91 	j a6f8 <_vfiprintf_r+0x2f8>
    a5da:	5e f1 00 72 	sltsi $r15,$r2,#0x72
    a5de:	e8 1f       	beqzs8 a61c <_vfiprintf_r+0x21c>
    a5e0:	5a 28 6f 04 	bnec $r2,#0x6f,a5e8 <_vfiprintf_r+0x1e8>
    a5e4:	48 00 00 e1 	j a7a6 <_vfiprintf_r+0x3a6>
    a5e8:	5a 20 70 04 	beqc $r2,#0x70,a5f0 <_vfiprintf_r+0x1f0>
    a5ec:	48 00 01 f1 	j a9ce <_vfiprintf_r+0x5ce>
    a5f0:	44 00 00 30 	movi $r0,#0x30
    a5f4:	10 0f 80 10 	sbi $r0,[$sp+#0x10]
    a5f8:	44 00 00 78 	movi $r0,#0x78
    a5fc:	10 0f 80 11 	sbi $r0,[$sp+#0x11]
    a600:	44 00 a3 ec 	movi $r0,#0xa3ec
    a604:	50 a3 00 04 	addi $r10,$r6,#0x4
    a608:	b5 26       	lwi450 $r9,[$r6]
    a60a:	59 ce 00 02 	ori $fp,$fp,#0x2
    a60e:	84 c0       	movi55 $r6,#0x0
    a610:	6a e4 80 09 	fmtsr $r14,$fs9
    a614:	6a 05 00 09 	fmtsr $r0,$fs10
    a618:	48 00 01 5d 	j a8d2 <_vfiprintf_r+0x4d2>
    a61c:	5a 28 75 04 	bnec $r2,#0x75,a624 <_vfiprintf_r+0x224>
    a620:	48 00 01 09 	j a832 <_vfiprintf_r+0x432>
    a624:	5a 28 78 04 	bnec $r2,#0x78,a62c <_vfiprintf_r+0x22c>
    a628:	48 00 01 24 	j a870 <_vfiprintf_r+0x470>
    a62c:	5a 20 73 04 	beqc $r2,#0x73,a634 <_vfiprintf_r+0x234>
    a630:	48 00 01 cf 	j a9ce <_vfiprintf_r+0x5ce>
    a634:	48 00 00 d9 	j a7e6 <_vfiprintf_r+0x3e6>
    a638:	10 3f 80 0f 	sbi $r3,[$sp+#0xf]
    a63c:	d5 6c       	j8 a714 <_vfiprintf_r+0x314>
    a63e:	10 3f 80 0f 	sbi $r3,[$sp+#0xf]
    a642:	6a e4 80 09 	fmtsr $r14,$fs9
    a646:	44 00 a3 d8 	movi $r0,#0xa3d8
    a64a:	48 00 01 19 	j a87c <_vfiprintf_r+0x47c>
    a64e:	40 31 0c 1a 	cmovz $r3,$r2,$r3
    a652:	48 ff ff 76 	j a53e <_vfiprintf_r+0x13e>
    a656:	04 d3 00 00 	lwi $r13,[$r6+#0x0]
    a65a:	9c 34       	addi333 $r0,$r6,#0x4
    a65c:	4e d5 00 05 	bltz $r13,a666 <_vfiprintf_r+0x266>
    a660:	80 c0       	mov55 $r6,$r0
    a662:	48 ff ff 6e 	j a53e <_vfiprintf_r+0x13e>
    a666:	52 d6 80 00 	subri $r13,$r13,#0x0
    a66a:	80 c0       	mov55 $r6,$r0
    a66c:	59 ce 00 04 	ori $fp,$fp,#0x4
    a670:	48 ff ff 67 	j a53e <_vfiprintf_r+0x13e>
    a674:	20 26 00 00 	lbsi $r2,[$r12+#0x0]
    a678:	50 06 00 01 	addi $r0,$r12,#0x1
    a67c:	5a 20 2a 04 	beqc $r2,#0x2a,a684 <_vfiprintf_r+0x284>
    a680:	84 20       	movi55 $r1,#0x0
    a682:	d5 0b       	j8 a698 <_vfiprintf_r+0x298>
    a684:	04 e3 00 00 	lwi $r14,[$r6+#0x0]
    a688:	81 80       	mov55 $r12,$r0
    a68a:	9c 34       	addi333 $r0,$r6,#0x4
    a68c:	4e e4 ff ea 	bgez $r14,a660 <_vfiprintf_r+0x260>
    a690:	80 c0       	mov55 $r6,$r0
    a692:	85 df       	movi55 $r14,#-1
    a694:	48 ff ff 55 	j a53e <_vfiprintf_r+0x13e>
    a698:	50 51 7f d0 	addi $r5,$r2,#-48
    a69c:	e6 aa       	slti45 $r5,#0xa
    a69e:	e8 09       	beqzs8 a6b0 <_vfiprintf_r+0x2b0>
    a6a0:	6a 23 00 01 	fmfsr $r2,$fs6
    a6a4:	42 50 88 73 	maddr32 $r5,$r1,$r2
    a6a8:	28 20 00 01 	lbsi.bi $r2,[$r0],#0x1
    a6ac:	80 25       	mov55 $r1,$r5
    a6ae:	d5 f5       	j8 a698 <_vfiprintf_r+0x298>
    a6b0:	42 e0 c0 00 	max $r14,$r1,$r16
    a6b4:	81 80       	mov55 $r12,$r0
    a6b6:	48 ff ff 25 	j a500 <_vfiprintf_r+0x100>
    a6ba:	85 a0       	movi55 $r13,#0x0
    a6bc:	6a 03 00 01 	fmfsr $r0,$fs6
    a6c0:	50 21 7f d0 	addi $r2,$r2,#-48
    a6c4:	42 26 80 73 	maddr32 $r2,$r13,$r0
    a6c8:	81 a2       	mov55 $r13,$r2
    a6ca:	28 26 00 01 	lbsi.bi $r2,[$r12],#0x1
    a6ce:	50 01 7f d0 	addi $r0,$r2,#-48
    a6d2:	e6 0a       	slti45 $r0,#0xa
    a6d4:	e9 f4       	bnezs8 a6bc <_vfiprintf_r+0x2bc>
    a6d6:	48 ff ff 15 	j a500 <_vfiprintf_r+0x100>
    a6da:	59 ce 00 40 	ori $fp,$fp,#0x40
    a6de:	48 ff ff 30 	j a53e <_vfiprintf_r+0x13e>
    a6e2:	20 06 00 00 	lbsi $r0,[$r12+#0x0]
    a6e6:	5a 08 6c 05 	bnec $r0,#0x6c,a6f0 <_vfiprintf_r+0x2f0>
    a6ea:	50 c6 00 01 	addi $r12,$r12,#0x1
    a6ee:	d5 05       	j8 a6f8 <_vfiprintf_r+0x2f8>
    a6f0:	59 ce 00 10 	ori $fp,$fp,#0x10
    a6f4:	48 ff ff 25 	j a53e <_vfiprintf_r+0x13e>
    a6f8:	59 ce 00 20 	ori $fp,$fp,#0x20
    a6fc:	48 ff ff 21 	j a53e <_vfiprintf_r+0x13e>
    a700:	b4 06       	lwi450 $r0,[$r6]
    a702:	10 0f 80 20 	sbi $r0,[$sp+#0x20]
    a706:	84 00       	movi55 $r0,#0x0
    a708:	50 a3 00 04 	addi $r10,$r6,#0x4
    a70c:	10 0f 80 0f 	sbi $r0,[$sp+#0xf]
    a710:	48 00 01 69 	j a9e2 <_vfiprintf_r+0x5e2>
    a714:	54 0e 00 20 	andi $r0,$fp,#0x20
    a718:	6a e4 80 09 	fmtsr $r14,$fs9
    a71c:	c0 09       	beqz38 $r0,a72e <_vfiprintf_r+0x32e>
    a71e:	9c f7       	addi333 $r3,$r6,#0x7
    a720:	66 31 80 07 	bitci $r3,$r3,#0x7
    a724:	50 a1 80 08 	addi $r10,$r3,#0x8
    a728:	b5 23       	lwi450 $r9,[$r3]
    a72a:	a1 99       	lwi333 $r6,[$r3+#0x4]
    a72c:	d5 13       	j8 a752 <_vfiprintf_r+0x352>
    a72e:	54 0e 00 10 	andi $r0,$fp,#0x10
    a732:	9c b4       	addi333 $r2,$r6,#0x4
    a734:	c0 04       	beqz38 $r0,a73c <_vfiprintf_r+0x33c>
    a736:	81 42       	mov55 $r10,$r2
    a738:	b5 26       	lwi450 $r9,[$r6]
    a73a:	d5 0a       	j8 a74e <_vfiprintf_r+0x34e>
    a73c:	54 1e 00 40 	andi $r1,$fp,#0x40
    a740:	b4 06       	lwi450 $r0,[$r6]
    a742:	81 42       	mov55 $r10,$r2
    a744:	c1 04       	beqz38 $r1,a74c <_vfiprintf_r+0x34c>
    a746:	40 90 00 11 	seh $r9,$r0
    a74a:	d5 02       	j8 a74e <_vfiprintf_r+0x34e>
    a74c:	81 20       	mov55 $r9,$r0
    a74e:	40 64 fc 0a 	srai $r6,$r9,#0x1f
    a752:	4e 64 00 c5 	bgez $r6,a8dc <_vfiprintf_r+0x4dc>
    a756:	52 04 80 00 	subri $r0,$r9,#0x0
    a75a:	84 20       	movi55 $r1,#0x0
    a75c:	e2 20       	slt45 $r1,$r0
    a75e:	ff b2       	neg33 $r6,$r6
    a760:	81 20       	mov55 $r9,$r0
    a762:	fa 1d       	movpi45 $r0,#0x2d
    a764:	8a cf       	sub45 $r6,$r15
    a766:	10 0f 80 0f 	sbi $r0,[$sp+#0xf]
    a76a:	48 00 00 b9 	j a8dc <_vfiprintf_r+0x4dc>
    a76e:	54 1e 00 20 	andi $r1,$fp,#0x20
    a772:	10 3f 80 0f 	sbi $r3,[$sp+#0xf]
    a776:	9c 34       	addi333 $r0,$r6,#0x4
    a778:	c1 07       	beqz38 $r1,a786 <_vfiprintf_r+0x386>
    a77a:	b4 26       	lwi450 $r1,[$r6]
    a77c:	40 23 fc 0a 	srai $r2,$r7,#0x1f
    a780:	b6 e1       	swi450 $r7,[$r1]
    a782:	a8 89       	swi333 $r2,[$r1+#0x4]
    a784:	d5 0c       	j8 a79c <_vfiprintf_r+0x39c>
    a786:	54 1e 00 10 	andi $r1,$fp,#0x10
    a78a:	c9 07       	bnez38 $r1,a798 <_vfiprintf_r+0x398>
    a78c:	54 1e 00 40 	andi $r1,$fp,#0x40
    a790:	c1 04       	beqz38 $r1,a798 <_vfiprintf_r+0x398>
    a792:	b4 26       	lwi450 $r1,[$r6]
    a794:	ad c8       	shi333 $r7,[$r1+#0x0]
    a796:	d5 03       	j8 a79c <_vfiprintf_r+0x39c>
    a798:	b4 26       	lwi450 $r1,[$r6]
    a79a:	b6 e1       	swi450 $r7,[$r1]
    a79c:	80 c0       	mov55 $r6,$r0
    a79e:	48 ff fe 7b 	j a494 <_vfiprintf_r+0x94>
    a7a2:	59 ce 00 10 	ori $fp,$fp,#0x10
    a7a6:	54 3e 00 20 	andi $r3,$fp,#0x20
    a7aa:	6a e4 80 09 	fmtsr $r14,$fs9
    a7ae:	c3 0b       	beqz38 $r3,a7c4 <_vfiprintf_r+0x3c4>
    a7b0:	9c f7       	addi333 $r3,$r6,#0x7
    a7b2:	66 31 80 07 	bitci $r3,$r3,#0x7
    a7b6:	50 a1 80 08 	addi $r10,$r3,#0x8
    a7ba:	b5 23       	lwi450 $r9,[$r3]
    a7bc:	a1 99       	lwi333 $r6,[$r3+#0x4]
    a7be:	84 60       	movi55 $r3,#0x0
    a7c0:	48 00 00 8a 	j a8d4 <_vfiprintf_r+0x4d4>
    a7c4:	54 1e 00 10 	andi $r1,$fp,#0x10
    a7c8:	9c 34       	addi333 $r0,$r6,#0x4
    a7ca:	c1 03       	beqz38 $r1,a7d0 <_vfiprintf_r+0x3d0>
    a7cc:	81 40       	mov55 $r10,$r0
    a7ce:	d5 09       	j8 a7e0 <_vfiprintf_r+0x3e0>
    a7d0:	54 3e 00 40 	andi $r3,$fp,#0x40
    a7d4:	81 40       	mov55 $r10,$r0
    a7d6:	c3 05       	beqz38 $r3,a7e0 <_vfiprintf_r+0x3e0>
    a7d8:	02 93 00 00 	lhi $r9,[$r6+#0x0]
    a7dc:	80 c1       	mov55 $r6,$r1
    a7de:	d5 f0       	j8 a7be <_vfiprintf_r+0x3be>
    a7e0:	b5 26       	lwi450 $r9,[$r6]
    a7e2:	80 c3       	mov55 $r6,$r3
    a7e4:	d5 ed       	j8 a7be <_vfiprintf_r+0x3be>
    a7e6:	30 b3 00 00 	flsi $fs11,[$r6+#0x0]
    a7ea:	84 00       	movi55 $r0,#0x0
    a7ec:	10 0f 80 0f 	sbi $r0,[$sp+#0xf]
    a7f0:	50 a3 00 04 	addi $r10,$r6,#0x4
    a7f4:	f4 81       	swi37.sp $r4,[+#0x4]
    a7f6:	6a 05 80 01 	fmfsr $r0,$fs11
    a7fa:	4e e5 00 11 	bltz $r14,a81c <_vfiprintf_r+0x41c>
    a7fe:	84 20       	movi55 $r1,#0x0
    a800:	80 4e       	mov55 $r2,$r14
    a802:	49 00 05 45 	jal b28c <memchr>
    a806:	f4 01       	lwi37.sp $r4,[+#0x4]
    a808:	4e 02 00 f5 	beqz $r0,a9f2 <_vfiprintf_r+0x5f2>
    a80c:	6a 15 80 01 	fmfsr $r1,$fs11
    a810:	9b 81       	sub333 $r6,$r0,$r1
    a812:	42 e3 38 01 	min $r14,$r6,$r14
    a816:	84 00       	movi55 $r0,#0x0
    a818:	48 00 00 ed 	j a9f2 <_vfiprintf_r+0x5f2>
    a81c:	49 ff fd 16 	jal a248 <strlen>
    a820:	81 c0       	mov55 $r14,$r0
    a822:	84 00       	movi55 $r0,#0x0
    a824:	6a 04 80 09 	fmtsr $r0,$fs9
    a828:	f4 01       	lwi37.sp $r4,[+#0x4]
    a82a:	48 00 00 e6 	j a9f6 <_vfiprintf_r+0x5f6>
    a82e:	59 ce 00 10 	ori $fp,$fp,#0x10
    a832:	54 3e 00 20 	andi $r3,$fp,#0x20
    a836:	6a e4 80 09 	fmtsr $r14,$fs9
    a83a:	c3 09       	beqz38 $r3,a84c <_vfiprintf_r+0x44c>
    a83c:	9c f7       	addi333 $r3,$r6,#0x7
    a83e:	66 31 80 07 	bitci $r3,$r3,#0x7
    a842:	50 a1 80 08 	addi $r10,$r3,#0x8
    a846:	b5 23       	lwi450 $r9,[$r3]
    a848:	a1 99       	lwi333 $r6,[$r3+#0x4]
    a84a:	d5 0e       	j8 a866 <_vfiprintf_r+0x466>
    a84c:	54 1e 00 10 	andi $r1,$fp,#0x10
    a850:	9c 34       	addi333 $r0,$r6,#0x4
    a852:	c1 03       	beqz38 $r1,a858 <_vfiprintf_r+0x458>
    a854:	81 40       	mov55 $r10,$r0
    a856:	d5 0a       	j8 a86a <_vfiprintf_r+0x46a>
    a858:	54 3e 00 40 	andi $r3,$fp,#0x40
    a85c:	81 40       	mov55 $r10,$r0
    a85e:	c3 06       	beqz38 $r3,a86a <_vfiprintf_r+0x46a>
    a860:	02 93 00 00 	lhi $r9,[$r6+#0x0]
    a864:	80 c1       	mov55 $r6,$r1
    a866:	84 61       	movi55 $r3,#0x1
    a868:	d5 36       	j8 a8d4 <_vfiprintf_r+0x4d4>
    a86a:	b5 26       	lwi450 $r9,[$r6]
    a86c:	80 c3       	mov55 $r6,$r3
    a86e:	d5 fc       	j8 a866 <_vfiprintf_r+0x466>
    a870:	6a e4 80 09 	fmtsr $r14,$fs9
    a874:	10 3f 80 0f 	sbi $r3,[$sp+#0xf]
    a878:	44 00 a3 ec 	movi $r0,#0xa3ec
    a87c:	54 3e 00 20 	andi $r3,$fp,#0x20
    a880:	6a 05 00 09 	fmtsr $r0,$fs10
    a884:	c3 09       	beqz38 $r3,a896 <_vfiprintf_r+0x496>
    a886:	9c f7       	addi333 $r3,$r6,#0x7
    a888:	66 31 80 07 	bitci $r3,$r3,#0x7
    a88c:	50 a1 80 08 	addi $r10,$r3,#0x8
    a890:	b5 23       	lwi450 $r9,[$r3]
    a892:	a1 99       	lwi333 $r6,[$r3+#0x4]
    a894:	d5 11       	j8 a8b6 <_vfiprintf_r+0x4b6>
    a896:	54 1e 00 10 	andi $r1,$fp,#0x10
    a89a:	9c 34       	addi333 $r0,$r6,#0x4
    a89c:	c1 03       	beqz38 $r1,a8a2 <_vfiprintf_r+0x4a2>
    a89e:	81 40       	mov55 $r10,$r0
    a8a0:	d5 09       	j8 a8b2 <_vfiprintf_r+0x4b2>
    a8a2:	54 3e 00 40 	andi $r3,$fp,#0x40
    a8a6:	81 40       	mov55 $r10,$r0
    a8a8:	c3 05       	beqz38 $r3,a8b2 <_vfiprintf_r+0x4b2>
    a8aa:	02 93 00 00 	lhi $r9,[$r6+#0x0]
    a8ae:	80 c1       	mov55 $r6,$r1
    a8b0:	d5 03       	j8 a8b6 <_vfiprintf_r+0x4b6>
    a8b2:	b5 26       	lwi450 $r9,[$r6]
    a8b4:	80 c3       	mov55 $r6,$r3
    a8b6:	54 0e 00 01 	andi $r0,$fp,#0x1
    a8ba:	c0 0c       	beqz38 $r0,a8d2 <_vfiprintf_r+0x4d2>
    a8bc:	40 04 98 04 	or $r0,$r9,$r6
    a8c0:	c0 09       	beqz38 $r0,a8d2 <_vfiprintf_r+0x4d2>
    a8c2:	44 00 00 30 	movi $r0,#0x30
    a8c6:	10 0f 80 10 	sbi $r0,[$sp+#0x10]
    a8ca:	10 2f 80 11 	sbi $r2,[$sp+#0x11]
    a8ce:	59 ce 00 02 	ori $fp,$fp,#0x2
    a8d2:	84 62       	movi55 $r3,#0x2
    a8d4:	84 00       	movi55 $r0,#0x0
    a8d6:	10 0f 80 0f 	sbi $r0,[$sp+#0xf]
    a8da:	d5 02       	j8 a8de <_vfiprintf_r+0x4de>
    a8dc:	84 61       	movi55 $r3,#0x1
    a8de:	4e e5 00 04 	bltz $r14,a8e6 <_vfiprintf_r+0x4e6>
    a8e2:	67 ce 00 80 	bitci $fp,$fp,#0x80
    a8e6:	40 04 98 04 	or $r0,$r9,$r6
    a8ea:	c8 04       	bnez38 $r0,a8f2 <_vfiprintf_r+0x4f2>
    a8ec:	4e e3 01 e5 	bnez $r14,acb6 <_vfiprintf_r+0x8b6>
    a8f0:	d5 5b       	j8 a9a6 <_vfiprintf_r+0x5a6>
    a8f2:	5a 30 01 23 	beqc $r3,#0x1,a938 <_vfiprintf_r+0x538>
    a8f6:	5a 30 02 44 	beqc $r3,#0x2,a97e <_vfiprintf_r+0x57e>
    a8fa:	50 2f 80 47 	addi $r2,$sp,#0x47
    a8fe:	54 14 80 07 	andi $r1,$r9,#0x7
    a902:	93 23       	srli45 $r9,#0x3
    a904:	40 94 9b a4 	or_slli $r9,$r9,$r6,#0x1d
    a908:	50 10 80 30 	addi $r1,$r1,#0x30
    a90c:	92 c3       	srli45 $r6,#0x3
    a90e:	96 4a       	seb33 $r1,$r1
    a910:	40 04 98 04 	or $r0,$r9,$r6
    a914:	80 62       	mov55 $r3,$r2
    a916:	18 11 7f ff 	sbi.bi $r1,[$r2],#-1
    a91a:	c8 f2       	bnez38 $r0,a8fe <_vfiprintf_r+0x4fe>
    a91c:	54 0e 00 01 	andi $r0,$fp,#0x1
    a920:	6a 35 80 09 	fmtsr $r3,$fs11
    a924:	c0 50       	beqz38 $r0,a9c4 <_vfiprintf_r+0x5c4>
    a926:	5a 10 30 4f 	beqc $r1,#0x30,a9c4 <_vfiprintf_r+0x5c4>
    a92a:	44 00 00 30 	movi $r0,#0x30
    a92e:	6a 25 80 09 	fmtsr $r2,$fs11
    a932:	10 01 ff ff 	sbi $r0,[$r3+#-1]
    a936:	d5 47       	j8 a9c4 <_vfiprintf_r+0x5c4>
    a938:	ce 08       	bnez38 $r6,a948 <_vfiprintf_r+0x548>
    a93a:	e7 2a       	slti45 $r9,#0xa
    a93c:	e8 06       	beqzs8 a948 <_vfiprintf_r+0x548>
    a93e:	50 94 80 30 	addi $r9,$r9,#0x30
    a942:	10 9f 80 47 	sbi $r9,[$sp+#0x47]
    a946:	d5 38       	j8 a9b6 <_vfiprintf_r+0x5b6>
    a948:	50 ef 80 47 	addi $r14,$sp,#0x47
    a94c:	80 09       	mov55 $r0,$r9
    a94e:	80 26       	mov55 $r1,$r6
    a950:	84 4a       	movi55 $r2,#0xa
    a952:	84 60       	movi55 $r3,#0x0
    a954:	f4 81       	swi37.sp $r4,[+#0x4]
    a956:	49 ff f1 d9 	jal 8d08 <__umoddi3>
    a95a:	50 00 00 30 	addi $r0,$r0,#0x30
    a95e:	80 26       	mov55 $r1,$r6
    a960:	6a e5 80 09 	fmtsr $r14,$fs11
    a964:	84 4a       	movi55 $r2,#0xa
    a966:	18 07 7f ff 	sbi.bi $r0,[$r14],#-1
    a96a:	84 60       	movi55 $r3,#0x0
    a96c:	80 09       	mov55 $r0,$r9
    a96e:	49 ff f0 f3 	jal 8b54 <__udivdi3>
    a972:	81 20       	mov55 $r9,$r0
    a974:	fe 0f       	or33 $r0,$r1
    a976:	80 c1       	mov55 $r6,$r1
    a978:	f4 01       	lwi37.sp $r4,[+#0x4]
    a97a:	c8 e9       	bnez38 $r0,a94c <_vfiprintf_r+0x54c>
    a97c:	d5 24       	j8 a9c4 <_vfiprintf_r+0x5c4>
    a97e:	50 1f 80 47 	addi $r1,$sp,#0x47
    a982:	6a 25 00 01 	fmfsr $r2,$fs10
    a986:	54 04 80 0f 	andi $r0,$r9,#0xf
    a98a:	93 24       	srli45 $r9,#0x4
    a98c:	38 01 00 00 	lb $r0,[$r2+($r0<<#0x0)]
    a990:	40 94 9b 84 	or_slli $r9,$r9,$r6,#0x1c
    a994:	92 c4       	srli45 $r6,#0x4
    a996:	6a 15 80 09 	fmtsr $r1,$fs11
    a99a:	18 00 ff ff 	sbi.bi $r0,[$r1],#-1
    a99e:	40 04 98 04 	or $r0,$r9,$r6
    a9a2:	c8 f0       	bnez38 $r0,a982 <_vfiprintf_r+0x582>
    a9a4:	d5 10       	j8 a9c4 <_vfiprintf_r+0x5c4>
    a9a6:	cb 0d       	bnez38 $r3,a9c0 <_vfiprintf_r+0x5c0>
    a9a8:	54 0e 00 01 	andi $r0,$fp,#0x1
    a9ac:	c0 0a       	beqz38 $r0,a9c0 <_vfiprintf_r+0x5c0>
    a9ae:	44 00 00 30 	movi $r0,#0x30
    a9b2:	10 0f 80 47 	sbi $r0,[$sp+#0x47]
    a9b6:	50 0f 80 47 	addi $r0,$sp,#0x47
    a9ba:	6a 05 80 09 	fmtsr $r0,$fs11
    a9be:	d5 03       	j8 a9c4 <_vfiprintf_r+0x5c4>
    a9c0:	6a 85 80 09 	fmtsr $r8,$fs11
    a9c4:	6a 05 80 01 	fmfsr $r0,$fs11
    a9c8:	40 e4 00 01 	sub $r14,$r8,$r0
    a9cc:	d5 15       	j8 a9f6 <_vfiprintf_r+0x5f6>
    a9ce:	10 3f 80 0f 	sbi $r3,[$sp+#0xf]
    a9d2:	4e 22 01 64 	beqz $r2,ac9a <_vfiprintf_r+0x89a>
    a9d6:	84 00       	movi55 $r0,#0x0
    a9d8:	10 2f 80 20 	sbi $r2,[$sp+#0x20]
    a9dc:	10 0f 80 0f 	sbi $r0,[$sp+#0xf]
    a9e0:	81 46       	mov55 $r10,$r6
    a9e2:	84 00       	movi55 $r0,#0x0
    a9e4:	6a 04 80 09 	fmtsr $r0,$fs9
    a9e8:	b0 08       	addri36.sp $r0,#0x20
    a9ea:	85 c1       	movi55 $r14,#0x1
    a9ec:	6a 05 80 09 	fmtsr $r0,$fs11
    a9f0:	d5 03       	j8 a9f6 <_vfiprintf_r+0x5f6>
    a9f2:	6a 04 80 09 	fmtsr $r0,$fs9
    a9f6:	6a 04 80 01 	fmfsr $r0,$fs9
    a9fa:	42 97 00 00 	max $r9,$r14,$r0
    a9fe:	20 0f 80 0f 	lbsi $r0,[$sp+#0xf]
    aa02:	c0 02       	beqz38 $r0,aa06 <_vfiprintf_r+0x606>
    aa04:	8d 21       	addi45 $r9,#0x1
    aa06:	54 0e 00 02 	andi $r0,$fp,#0x2
    aa0a:	6a 06 80 09 	fmtsr $r0,$fs13
    aa0e:	c0 02       	beqz38 $r0,aa12 <_vfiprintf_r+0x612>
    aa10:	8d 22       	addi45 $r9,#0x2
    aa12:	54 0e 00 84 	andi $r0,$fp,#0x84
    aa16:	6a 06 00 09 	fmtsr $r0,$fs12
    aa1a:	c8 37       	bnez38 $r0,aa88 <_vfiprintf_r+0x688>
    aa1c:	40 66 a4 01 	sub $r6,$r13,$r9
    aa20:	4e 67 00 34 	blez $r6,aa88 <_vfiprintf_r+0x688>
    aa24:	fa 00       	movpi45 $r0,#0x10
    aa26:	6a 07 00 09 	fmtsr $r0,$fs14
    aa2a:	e4 d1       	sltsi45 $r6,#0x11
    aa2c:	e9 19       	bnezs8 aa5e <_vfiprintf_r+0x65e>
    aa2e:	f0 07       	lwi37.sp $r0,[+#0x1c]
    aa30:	32 82 00 00 	fssi $fs8,[$r4+#0x0]
    aa34:	8c 10       	addi45 $r0,#0x10
    aa36:	f0 87       	swi37.sp $r0,[+#0x1c]
    aa38:	f0 06       	lwi37.sp $r0,[+#0x18]
    aa3a:	32 e2 00 01 	fssi $fs14,[$r4+#0x4]
    aa3e:	8c 01       	addi45 $r0,#0x1
    aa40:	e4 08       	sltsi45 $r0,#0x8
    aa42:	f0 86       	swi37.sp $r0,[+#0x18]
    aa44:	e8 03       	beqzs8 aa4a <_vfiprintf_r+0x64a>
    aa46:	8c 88       	addi45 $r4,#0x8
    aa48:	d5 09       	j8 aa5a <_vfiprintf_r+0x65a>
    aa4a:	b4 1f       	lwi450 $r0,[$sp]
    aa4c:	80 2b       	mov55 $r1,$r11
    aa4e:	b0 85       	addri36.sp $r2,#0x14
    aa50:	49 ff fc b4 	jal a3b8 <__sprint_r>
    aa54:	4e 03 01 2a 	bnez $r0,aca8 <_vfiprintf_r+0x8a8>
    aa58:	80 88       	mov55 $r4,$r8
    aa5a:	8e d0       	subi45 $r6,#0x10
    aa5c:	d5 e7       	j8 aa2a <_vfiprintf_r+0x62a>
    aa5e:	f0 07       	lwi37.sp $r0,[+#0x1c]
    aa60:	a9 a1       	swi333 $r6,[$r4+#0x4]
    aa62:	88 c0       	add45 $r6,$r0
    aa64:	f0 06       	lwi37.sp $r0,[+#0x18]
    aa66:	32 72 00 00 	fssi $fs7,[$r4+#0x0]
    aa6a:	8c 01       	addi45 $r0,#0x1
    aa6c:	e4 08       	sltsi45 $r0,#0x8
    aa6e:	f6 87       	swi37.sp $r6,[+#0x1c]
    aa70:	f0 86       	swi37.sp $r0,[+#0x18]
    aa72:	e8 03       	beqzs8 aa78 <_vfiprintf_r+0x678>
    aa74:	8c 88       	addi45 $r4,#0x8
    aa76:	d5 09       	j8 aa88 <_vfiprintf_r+0x688>
    aa78:	b4 1f       	lwi450 $r0,[$sp]
    aa7a:	80 2b       	mov55 $r1,$r11
    aa7c:	b0 85       	addri36.sp $r2,#0x14
    aa7e:	49 ff fc 9d 	jal a3b8 <__sprint_r>
    aa82:	4e 03 01 13 	bnez $r0,aca8 <_vfiprintf_r+0x8a8>
    aa86:	80 88       	mov55 $r4,$r8
    aa88:	20 0f 80 0f 	lbsi $r0,[$sp+#0xf]
    aa8c:	c0 18       	beqz38 $r0,aabc <_vfiprintf_r+0x6bc>
    aa8e:	50 0f 80 0f 	addi $r0,$sp,#0xf
    aa92:	b6 04       	swi450 $r0,[$r4]
    aa94:	84 01       	movi55 $r0,#0x1
    aa96:	a8 21       	swi333 $r0,[$r4+#0x4]
    aa98:	f0 07       	lwi37.sp $r0,[+#0x1c]
    aa9a:	8c 01       	addi45 $r0,#0x1
    aa9c:	f0 87       	swi37.sp $r0,[+#0x1c]
    aa9e:	f0 06       	lwi37.sp $r0,[+#0x18]
    aaa0:	8c 01       	addi45 $r0,#0x1
    aaa2:	e4 08       	sltsi45 $r0,#0x8
    aaa4:	f0 86       	swi37.sp $r0,[+#0x18]
    aaa6:	e8 03       	beqzs8 aaac <_vfiprintf_r+0x6ac>
    aaa8:	8c 88       	addi45 $r4,#0x8
    aaaa:	d5 09       	j8 aabc <_vfiprintf_r+0x6bc>
    aaac:	b4 1f       	lwi450 $r0,[$sp]
    aaae:	80 2b       	mov55 $r1,$r11
    aab0:	b0 85       	addri36.sp $r2,#0x14
    aab2:	49 ff fc 83 	jal a3b8 <__sprint_r>
    aab6:	4e 03 00 f9 	bnez $r0,aca8 <_vfiprintf_r+0x8a8>
    aaba:	80 88       	mov55 $r4,$r8
    aabc:	6a 06 80 01 	fmfsr $r0,$fs13
    aac0:	c0 17       	beqz38 $r0,aaee <_vfiprintf_r+0x6ee>
    aac2:	b0 04       	addri36.sp $r0,#0x10
    aac4:	b6 04       	swi450 $r0,[$r4]
    aac6:	84 02       	movi55 $r0,#0x2
    aac8:	a8 21       	swi333 $r0,[$r4+#0x4]
    aaca:	f0 07       	lwi37.sp $r0,[+#0x1c]
    aacc:	8c 02       	addi45 $r0,#0x2
    aace:	f0 87       	swi37.sp $r0,[+#0x1c]
    aad0:	f0 06       	lwi37.sp $r0,[+#0x18]
    aad2:	8c 01       	addi45 $r0,#0x1
    aad4:	e4 08       	sltsi45 $r0,#0x8
    aad6:	f0 86       	swi37.sp $r0,[+#0x18]
    aad8:	e8 03       	beqzs8 aade <_vfiprintf_r+0x6de>
    aada:	8c 88       	addi45 $r4,#0x8
    aadc:	d5 09       	j8 aaee <_vfiprintf_r+0x6ee>
    aade:	b4 1f       	lwi450 $r0,[$sp]
    aae0:	80 2b       	mov55 $r1,$r11
    aae2:	b0 85       	addri36.sp $r2,#0x14
    aae4:	49 ff fc 6a 	jal a3b8 <__sprint_r>
    aae8:	4e 03 00 e0 	bnez $r0,aca8 <_vfiprintf_r+0x8a8>
    aaec:	80 88       	mov55 $r4,$r8
    aaee:	6a 06 00 01 	fmfsr $r0,$fs12
    aaf2:	5a 08 80 3d 	bnec $r0,#0x80,ab6c <_vfiprintf_r+0x76c>
    aaf6:	40 66 a4 01 	sub $r6,$r13,$r9
    aafa:	4e 67 00 39 	blez $r6,ab6c <_vfiprintf_r+0x76c>
    aafe:	44 00 ad 44 	movi $r0,#0xad44
    ab02:	6a 06 00 09 	fmtsr $r0,$fs12
    ab06:	fa 00       	movpi45 $r0,#0x10
    ab08:	6a 06 80 09 	fmtsr $r0,$fs13
    ab0c:	e4 d1       	sltsi45 $r6,#0x11
    ab0e:	e9 19       	bnezs8 ab40 <_vfiprintf_r+0x740>
    ab10:	f0 07       	lwi37.sp $r0,[+#0x1c]
    ab12:	32 c2 00 00 	fssi $fs12,[$r4+#0x0]
    ab16:	8c 10       	addi45 $r0,#0x10
    ab18:	f0 87       	swi37.sp $r0,[+#0x1c]
    ab1a:	f0 06       	lwi37.sp $r0,[+#0x18]
    ab1c:	32 d2 00 01 	fssi $fs13,[$r4+#0x4]
    ab20:	8c 01       	addi45 $r0,#0x1
    ab22:	e4 08       	sltsi45 $r0,#0x8
    ab24:	f0 86       	swi37.sp $r0,[+#0x18]
    ab26:	e8 03       	beqzs8 ab2c <_vfiprintf_r+0x72c>
    ab28:	8c 88       	addi45 $r4,#0x8
    ab2a:	d5 09       	j8 ab3c <_vfiprintf_r+0x73c>
    ab2c:	b4 1f       	lwi450 $r0,[$sp]
    ab2e:	80 2b       	mov55 $r1,$r11
    ab30:	b0 85       	addri36.sp $r2,#0x14
    ab32:	49 ff fc 43 	jal a3b8 <__sprint_r>
    ab36:	4e 03 00 b9 	bnez $r0,aca8 <_vfiprintf_r+0x8a8>
    ab3a:	80 88       	mov55 $r4,$r8
    ab3c:	8e d0       	subi45 $r6,#0x10
    ab3e:	d5 e7       	j8 ab0c <_vfiprintf_r+0x70c>
    ab40:	44 00 ad 44 	movi $r0,#0xad44
    ab44:	b6 04       	swi450 $r0,[$r4]
    ab46:	f0 07       	lwi37.sp $r0,[+#0x1c]
    ab48:	a9 a1       	swi333 $r6,[$r4+#0x4]
    ab4a:	88 c0       	add45 $r6,$r0
    ab4c:	f0 06       	lwi37.sp $r0,[+#0x18]
    ab4e:	f6 87       	swi37.sp $r6,[+#0x1c]
    ab50:	8c 01       	addi45 $r0,#0x1
    ab52:	e4 08       	sltsi45 $r0,#0x8
    ab54:	f0 86       	swi37.sp $r0,[+#0x18]
    ab56:	e8 03       	beqzs8 ab5c <_vfiprintf_r+0x75c>
    ab58:	8c 88       	addi45 $r4,#0x8
    ab5a:	d5 09       	j8 ab6c <_vfiprintf_r+0x76c>
    ab5c:	b4 1f       	lwi450 $r0,[$sp]
    ab5e:	80 2b       	mov55 $r1,$r11
    ab60:	b0 85       	addri36.sp $r2,#0x14
    ab62:	49 ff fc 2b 	jal a3b8 <__sprint_r>
    ab66:	4e 03 00 a1 	bnez $r0,aca8 <_vfiprintf_r+0x8a8>
    ab6a:	80 88       	mov55 $r4,$r8
    ab6c:	6a 64 80 01 	fmfsr $r6,$fs9
    ab70:	8a ce       	sub45 $r6,$r14
    ab72:	4e 67 00 38 	blez $r6,abe2 <_vfiprintf_r+0x7e2>
    ab76:	44 00 ad 44 	movi $r0,#0xad44
    ab7a:	6a 04 80 09 	fmtsr $r0,$fs9
    ab7e:	fa 00       	movpi45 $r0,#0x10
    ab80:	6a 06 00 09 	fmtsr $r0,$fs12
    ab84:	e4 d1       	sltsi45 $r6,#0x11
    ab86:	e9 19       	bnezs8 abb8 <_vfiprintf_r+0x7b8>
    ab88:	f0 07       	lwi37.sp $r0,[+#0x1c]
    ab8a:	32 92 00 00 	fssi $fs9,[$r4+#0x0]
    ab8e:	8c 10       	addi45 $r0,#0x10
    ab90:	f0 87       	swi37.sp $r0,[+#0x1c]
    ab92:	f0 06       	lwi37.sp $r0,[+#0x18]
    ab94:	32 c2 00 01 	fssi $fs12,[$r4+#0x4]
    ab98:	8c 01       	addi45 $r0,#0x1
    ab9a:	e4 08       	sltsi45 $r0,#0x8
    ab9c:	f0 86       	swi37.sp $r0,[+#0x18]
    ab9e:	e8 03       	beqzs8 aba4 <_vfiprintf_r+0x7a4>
    aba0:	8c 88       	addi45 $r4,#0x8
    aba2:	d5 09       	j8 abb4 <_vfiprintf_r+0x7b4>
    aba4:	b4 1f       	lwi450 $r0,[$sp]
    aba6:	80 2b       	mov55 $r1,$r11
    aba8:	b0 85       	addri36.sp $r2,#0x14
    abaa:	49 ff fc 07 	jal a3b8 <__sprint_r>
    abae:	4e 03 00 7d 	bnez $r0,aca8 <_vfiprintf_r+0x8a8>
    abb2:	80 88       	mov55 $r4,$r8
    abb4:	8e d0       	subi45 $r6,#0x10
    abb6:	d5 e7       	j8 ab84 <_vfiprintf_r+0x784>
    abb8:	44 00 ad 44 	movi $r0,#0xad44
    abbc:	b6 04       	swi450 $r0,[$r4]
    abbe:	f0 07       	lwi37.sp $r0,[+#0x1c]
    abc0:	a9 a1       	swi333 $r6,[$r4+#0x4]
    abc2:	88 c0       	add45 $r6,$r0
    abc4:	f0 06       	lwi37.sp $r0,[+#0x18]
    abc6:	f6 87       	swi37.sp $r6,[+#0x1c]
    abc8:	8c 01       	addi45 $r0,#0x1
    abca:	e4 08       	sltsi45 $r0,#0x8
    abcc:	f0 86       	swi37.sp $r0,[+#0x18]
    abce:	e8 03       	beqzs8 abd4 <_vfiprintf_r+0x7d4>
    abd0:	8c 88       	addi45 $r4,#0x8
    abd2:	d5 08       	j8 abe2 <_vfiprintf_r+0x7e2>
    abd4:	b4 1f       	lwi450 $r0,[$sp]
    abd6:	80 2b       	mov55 $r1,$r11
    abd8:	b0 85       	addri36.sp $r2,#0x14
    abda:	49 ff fb ef 	jal a3b8 <__sprint_r>
    abde:	c8 65       	bnez38 $r0,aca8 <_vfiprintf_r+0x8a8>
    abe0:	80 88       	mov55 $r4,$r8
    abe2:	f0 07       	lwi37.sp $r0,[+#0x1c]
    abe4:	32 b2 00 00 	fssi $fs11,[$r4+#0x0]
    abe8:	88 0e       	add45 $r0,$r14
    abea:	f0 87       	swi37.sp $r0,[+#0x1c]
    abec:	f0 06       	lwi37.sp $r0,[+#0x18]
    abee:	14 e2 00 01 	swi $r14,[$r4+#0x4]
    abf2:	8c 01       	addi45 $r0,#0x1
    abf4:	e4 08       	sltsi45 $r0,#0x8
    abf6:	f0 86       	swi37.sp $r0,[+#0x18]
    abf8:	e8 04       	beqzs8 ac00 <_vfiprintf_r+0x800>
    abfa:	50 02 00 08 	addi $r0,$r4,#0x8
    abfe:	d5 08       	j8 ac0e <_vfiprintf_r+0x80e>
    ac00:	b4 1f       	lwi450 $r0,[$sp]
    ac02:	80 2b       	mov55 $r1,$r11
    ac04:	b0 85       	addri36.sp $r2,#0x14
    ac06:	49 ff fb d9 	jal a3b8 <__sprint_r>
    ac0a:	c8 4f       	bnez38 $r0,aca8 <_vfiprintf_r+0x8a8>
    ac0c:	80 08       	mov55 $r0,$r8
    ac0e:	54 1e 00 04 	andi $r1,$fp,#0x4
    ac12:	c9 07       	bnez38 $r1,ac20 <_vfiprintf_r+0x820>
    ac14:	f0 07       	lwi37.sp $r0,[+#0x1c]
    ac16:	42 d4 b4 00 	max $r13,$r9,$r13
    ac1a:	88 ed       	add45 $r7,$r13
    ac1c:	c0 39       	beqz38 $r0,ac8e <_vfiprintf_r+0x88e>
    ac1e:	d5 32       	j8 ac82 <_vfiprintf_r+0x882>
    ac20:	40 66 a4 01 	sub $r6,$r13,$r9
    ac24:	4e 67 ff f8 	blez $r6,ac14 <_vfiprintf_r+0x814>
    ac28:	45 c0 00 10 	movi $fp,#0x10
    ac2c:	e4 d1       	sltsi45 $r6,#0x11
    ac2e:	e9 18       	bnezs8 ac5e <_vfiprintf_r+0x85e>
    ac30:	f1 07       	lwi37.sp $r1,[+#0x1c]
    ac32:	32 80 00 00 	fssi $fs8,[$r0+#0x0]
    ac36:	8c 30       	addi45 $r1,#0x10
    ac38:	f1 87       	swi37.sp $r1,[+#0x1c]
    ac3a:	f1 06       	lwi37.sp $r1,[+#0x18]
    ac3c:	15 c0 00 01 	swi $fp,[$r0+#0x4]
    ac40:	8c 21       	addi45 $r1,#0x1
    ac42:	e4 28       	sltsi45 $r1,#0x8
    ac44:	f1 86       	swi37.sp $r1,[+#0x18]
    ac46:	e8 03       	beqzs8 ac4c <_vfiprintf_r+0x84c>
    ac48:	8c 08       	addi45 $r0,#0x8
    ac4a:	d5 08       	j8 ac5a <_vfiprintf_r+0x85a>
    ac4c:	b4 1f       	lwi450 $r0,[$sp]
    ac4e:	80 2b       	mov55 $r1,$r11
    ac50:	b0 85       	addri36.sp $r2,#0x14
    ac52:	49 ff fb b3 	jal a3b8 <__sprint_r>
    ac56:	c8 29       	bnez38 $r0,aca8 <_vfiprintf_r+0x8a8>
    ac58:	80 08       	mov55 $r0,$r8
    ac5a:	8e d0       	subi45 $r6,#0x10
    ac5c:	d5 e8       	j8 ac2c <_vfiprintf_r+0x82c>
    ac5e:	a9 81       	swi333 $r6,[$r0+#0x4]
    ac60:	32 70 00 00 	fssi $fs7,[$r0+#0x0]
    ac64:	f0 07       	lwi37.sp $r0,[+#0x1c]
    ac66:	88 c0       	add45 $r6,$r0
    ac68:	f0 06       	lwi37.sp $r0,[+#0x18]
    ac6a:	f6 87       	swi37.sp $r6,[+#0x1c]
    ac6c:	8c 01       	addi45 $r0,#0x1
    ac6e:	e4 08       	sltsi45 $r0,#0x8
    ac70:	f0 86       	swi37.sp $r0,[+#0x18]
    ac72:	e9 d1       	bnezs8 ac14 <_vfiprintf_r+0x814>
    ac74:	b4 1f       	lwi450 $r0,[$sp]
    ac76:	80 2b       	mov55 $r1,$r11
    ac78:	b0 85       	addri36.sp $r2,#0x14
    ac7a:	49 ff fb 9f 	jal a3b8 <__sprint_r>
    ac7e:	c0 cb       	beqz38 $r0,ac14 <_vfiprintf_r+0x814>
    ac80:	d5 14       	j8 aca8 <_vfiprintf_r+0x8a8>
    ac82:	b4 1f       	lwi450 $r0,[$sp]
    ac84:	80 2b       	mov55 $r1,$r11
    ac86:	b0 85       	addri36.sp $r2,#0x14
    ac88:	49 ff fb 98 	jal a3b8 <__sprint_r>
    ac8c:	c8 0e       	bnez38 $r0,aca8 <_vfiprintf_r+0x8a8>
    ac8e:	84 00       	movi55 $r0,#0x0
    ac90:	f0 86       	swi37.sp $r0,[+#0x18]
    ac92:	80 ca       	mov55 $r6,$r10
    ac94:	80 88       	mov55 $r4,$r8
    ac96:	48 ff fb ff 	j a494 <_vfiprintf_r+0x94>
    ac9a:	f0 07       	lwi37.sp $r0,[+#0x1c]
    ac9c:	c0 06       	beqz38 $r0,aca8 <_vfiprintf_r+0x8a8>
    ac9e:	b4 1f       	lwi450 $r0,[$sp]
    aca0:	80 2b       	mov55 $r1,$r11
    aca2:	b0 85       	addri36.sp $r2,#0x14
    aca4:	49 ff fb 8a 	jal a3b8 <__sprint_r>
    aca8:	02 05 80 06 	lhi $r0,[$r11+#0xc]
    acac:	96 36       	bmski33 $r0,#0x6
    acae:	4e 03 fb d0 	bnez $r0,a44e <_vfiprintf_r+0x4e>
    acb2:	80 07       	mov55 $r0,$r7
    acb4:	d5 07       	j8 acc2 <_vfiprintf_r+0x8c2>
    acb6:	5a 30 01 04 	beqc $r3,#0x1,acbe <_vfiprintf_r+0x8be>
    acba:	48 ff fe 1e 	j a8f6 <_vfiprintf_r+0x4f6>
    acbe:	48 ff fe 40 	j a93e <_vfiprintf_r+0x53e>
    acc2:	34 3f 80 22 	fldi $fd3,[$sp+#0x88]
    acc6:	34 4f 80 24 	fldi $fd4,[$sp+#0x90]
    acca:	34 5f 80 26 	fldi $fd5,[$sp+#0x98]
    acce:	34 6f 80 28 	fldi $fd6,[$sp+#0xa0]
    acd2:	34 7f 80 2a 	fldi $fd7,[$sp+#0xa8]
    acd6:	fc f6       	pop25 $r14,#176    ! {$r6~$r14, $fp, $gp, $lp}

0000acd8 <__sbprintf>:
    acd8:	fc 20       	push25 $r8,#0    ! {$r6~$r8, $fp, $gp, $lp}
    acda:	51 ff fb 90 	addi $sp,$sp,#-1136
    acde:	80 c1       	mov55 $r6,$r1
    ace0:	a4 4e       	lhi333 $r1,[$r1+#0xc]
    ace2:	f0 81       	swi37.sp $r0,[+#0x4]
    ace4:	66 10 80 02 	bitci $r1,$r1,#0x2
    ace8:	12 1f 80 0a 	shi $r1,[$sp+#0x14]
    acec:	83 86       	mov55 $fp,$r6
    acee:	b9 19       	lwi37 $r1,[$fp+#0x64]
    acf0:	f1 9b       	swi37.sp $r1,[+#0x6c]
    acf2:	a4 77       	lhi333 $r1,[$r6+#0xe]
    acf4:	12 1f 80 0b 	shi $r1,[$sp+#0x16]
    acf8:	a0 77       	lwi333 $r1,[$r6+#0x1c]
    acfa:	f1 89       	swi37.sp $r1,[+#0x24]
    acfc:	b9 09       	lwi37 $r1,[$fp+#0x24]
    acfe:	f1 8b       	swi37.sp $r1,[+#0x2c]
    ad00:	b0 5c       	addri36.sp $r1,#0x70
    ad02:	f1 82       	swi37.sp $r1,[+#0x8]
    ad04:	f1 86       	swi37.sp $r1,[+#0x18]
    ad06:	44 10 04 00 	movi $r1,#0x400
    ad0a:	f1 84       	swi37.sp $r1,[+#0x10]
    ad0c:	f1 87       	swi37.sp $r1,[+#0x1c]
    ad0e:	84 20       	movi55 $r1,#0x0
    ad10:	f1 88       	swi37.sp $r1,[+#0x20]
    ad12:	b0 42       	addri36.sp $r1,#0x8
    ad14:	49 ff fb 76 	jal a400 <_vfiprintf_r>
    ad18:	80 e0       	mov55 $r7,$r0
    ad1a:	4e 05 00 08 	bltz $r0,ad2a <__sbprintf+0x52>
    ad1e:	f0 01       	lwi37.sp $r0,[+#0x4]
    ad20:	b0 42       	addri36.sp $r1,#0x8
    ad22:	49 ff f8 29 	jal 9d74 <_fflush_r>
    ad26:	c0 02       	beqz38 $r0,ad2a <__sbprintf+0x52>
    ad28:	84 ff       	movi55 $r7,#-1
    ad2a:	02 0f 80 0a 	lhi $r0,[$sp+#0x14]
    ad2e:	96 36       	bmski33 $r0,#0x6
    ad30:	c0 05       	beqz38 $r0,ad3a <__sbprintf+0x62>
    ad32:	a4 36       	lhi333 $r0,[$r6+#0xc]
    ad34:	58 00 00 40 	ori $r0,$r0,#0x40
    ad38:	ac 36       	shi333 $r0,[$r6+#0xc]
    ad3a:	80 07       	mov55 $r0,$r7
    ad3c:	51 ff 84 70 	addi $sp,$sp,#0x470
    ad40:	fc a0       	pop25 $r8,#0    ! {$r6~$r8, $fp, $gp, $lp}
	...

0000ad44 <zeroes.4502>:
    ad44:	30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30     0000000000000000

0000ad54 <blanks.4501>:
    ad54:	20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20                     

0000ad64 <_write_r>:
    ad64:	fc 00       	push25 $r6,#0    ! {$r6, $fp, $gp, $lp}
    ad66:	84 00       	movi55 $r0,#0x0
    ad68:	3c 0e 00 23 	swi.gp $r0,[+#0x8c]
    ad6c:	80 01       	mov55 $r0,$r1
    ad6e:	80 22       	mov55 $r1,$r2
    ad70:	80 43       	mov55 $r2,$r3
    ad72:	49 00 03 75 	jal b45c <_write>
    ad76:	5a 0f ff 07 	bnec $r0,#-1,ad84 <_write_r+0x20>
    ad7a:	3c 1c 00 23 	lwi.gp $r1,[+#0x8c]
    ad7e:	c1 03       	beqz38 $r1,ad84 <_write_r+0x20>
    ad80:	3c 1e 0a d4 	swi.gp $r1,[+#0x2b50]
    ad84:	fc 80       	pop25 $r6,#0    ! {$r6, $fp, $gp, $lp}

0000ad86 <__swsetup_r>:
    ad86:	fc 01       	push25 $r6,#8    ! {$r6, $fp, $gp, $lp}
    ad88:	f0 81       	swi37.sp $r0,[+#0x4]
    ad8a:	3c 0c 0a d8 	lwi.gp $r0,[+#0x2b60]
    ad8e:	80 c1       	mov55 $r6,$r1
    ad90:	c8 03       	bnez38 $r0,ad96 <__swsetup_r+0x10>
    ad92:	49 ff f8 17 	jal 9dc0 <__sinit>
    ad96:	22 13 00 06 	lhsi $r1,[$r6+#0xc]
    ad9a:	96 09       	zeh33 $r0,$r1
    ad9c:	54 20 00 08 	andi $r2,$r0,#0x8
    ada0:	ca 23       	bnez38 $r2,ade6 <__swsetup_r+0x60>
    ada2:	54 20 00 10 	andi $r2,$r0,#0x10
    ada6:	ca 05       	bnez38 $r2,adb0 <__swsetup_r+0x2a>
    ada8:	84 09       	movi55 $r0,#0x9
    adaa:	3c 0e 0a d4 	swi.gp $r0,[+#0x2b50]
    adae:	d5 3c       	j8 ae26 <__swsetup_r+0xa0>
    adb0:	96 16       	bmski33 $r0,#0x2
    adb2:	c0 16       	beqz38 $r0,adde <__swsetup_r+0x58>
    adb4:	04 13 00 0c 	lwi $r1,[$r6+#0x30]
    adb8:	c1 0b       	beqz38 $r1,adce <__swsetup_r+0x48>
    adba:	50 03 00 40 	addi $r0,$r6,#0x40
    adbe:	4c 10 00 05 	beq $r1,$r0,adc8 <__swsetup_r+0x42>
    adc2:	f0 01       	lwi37.sp $r0,[+#0x4]
    adc4:	49 ff f9 32 	jal a028 <_free_r>
    adc8:	84 00       	movi55 $r0,#0x0
    adca:	14 03 00 0c 	swi $r0,[$r6+#0x30]
    adce:	a4 36       	lhi333 $r0,[$r6+#0xc]
    add0:	66 00 00 24 	bitci $r0,$r0,#0x24
    add4:	ac 36       	shi333 $r0,[$r6+#0xc]
    add6:	84 00       	movi55 $r0,#0x0
    add8:	a8 31       	swi333 $r0,[$r6+#0x4]
    adda:	a0 34       	lwi333 $r0,[$r6+#0x10]
    addc:	b6 06       	swi450 $r0,[$r6]
    adde:	a4 36       	lhi333 $r0,[$r6+#0xc]
    ade0:	58 00 00 08 	ori $r0,$r0,#0x8
    ade4:	ac 36       	shi333 $r0,[$r6+#0xc]
    ade6:	a0 34       	lwi333 $r0,[$r6+#0x10]
    ade8:	c8 0a       	bnez38 $r0,adfc <__swsetup_r+0x76>
    adea:	a4 36       	lhi333 $r0,[$r6+#0xc]
    adec:	54 00 02 80 	andi $r0,$r0,#0x280
    adf0:	5a 02 00 06 	beqc $r0,#0x200,adfc <__swsetup_r+0x76>
    adf4:	f0 01       	lwi37.sp $r0,[+#0x4]
    adf6:	80 26       	mov55 $r1,$r6
    adf8:	49 00 01 d9 	jal b1aa <__smakebuf_r>
    adfc:	a4 76       	lhi333 $r1,[$r6+#0xc]
    adfe:	96 0c       	xlsb33 $r0,$r1
    ae00:	c0 07       	beqz38 $r0,ae0e <__swsetup_r+0x88>
    ae02:	84 00       	movi55 $r0,#0x0
    ae04:	a8 32       	swi333 $r0,[$r6+#0x8]
    ae06:	a0 35       	lwi333 $r0,[$r6+#0x14]
    ae08:	fe 02       	neg33 $r0,$r0
    ae0a:	a8 36       	swi333 $r0,[$r6+#0x18]
    ae0c:	d5 05       	j8 ae16 <__swsetup_r+0x90>
    ae0e:	96 4e       	bmski33 $r1,#0x1
    ae10:	c9 02       	bnez38 $r1,ae14 <__swsetup_r+0x8e>
    ae12:	a0 35       	lwi333 $r0,[$r6+#0x14]
    ae14:	a8 32       	swi333 $r0,[$r6+#0x8]
    ae16:	a0 34       	lwi333 $r0,[$r6+#0x10]
    ae18:	c8 0c       	bnez38 $r0,ae30 <__swsetup_r+0xaa>
    ae1a:	22 13 00 06 	lhsi $r1,[$r6+#0xc]
    ae1e:	54 00 80 80 	andi $r0,$r1,#0x80
    ae22:	96 01       	zeh33 $r0,$r0
    ae24:	c0 07       	beqz38 $r0,ae32 <__swsetup_r+0xac>
    ae26:	58 10 80 40 	ori $r1,$r1,#0x40
    ae2a:	ac 76       	shi333 $r1,[$r6+#0xc]
    ae2c:	84 1f       	movi55 $r0,#-1
    ae2e:	fc 81       	pop25 $r6,#8    ! {$r6, $fp, $gp, $lp}
    ae30:	84 00       	movi55 $r0,#0x0
    ae32:	fc 81       	pop25 $r6,#8    ! {$r6, $fp, $gp, $lp}

0000ae34 <abort>:
    ae34:	fc 00       	push25 $r6,#0    ! {$r6, $fp, $gp, $lp}
    ae36:	84 01       	movi55 $r0,#0x1
    ae38:	49 00 03 06 	jal b444 <_exit>
    ae3c:	92 00       	nop16

0000ae3e <_close_r>:
    ae3e:	fc 00       	push25 $r6,#0    ! {$r6, $fp, $gp, $lp}
    ae40:	84 00       	movi55 $r0,#0x0
    ae42:	3c 0e 00 23 	swi.gp $r0,[+#0x8c]
    ae46:	80 01       	mov55 $r0,$r1
    ae48:	49 00 03 02 	jal b44c <_close>
    ae4c:	5a 0f ff 07 	bnec $r0,#-1,ae5a <_close_r+0x1c>
    ae50:	3c 1c 00 23 	lwi.gp $r1,[+#0x8c]
    ae54:	c1 03       	beqz38 $r1,ae5a <_close_r+0x1c>
    ae56:	3c 1e 0a d4 	swi.gp $r1,[+#0x2b50]
    ae5a:	fc 80       	pop25 $r6,#0    ! {$r6, $fp, $gp, $lp}

0000ae5c <_fclose_r>:
    ae5c:	c1 41       	beqz38 $r1,aede <_fclose_r+0x82>
    ae5e:	fc 21       	push25 $r8,#8    ! {$r6~$r8, $fp, $gp, $lp}
    ae60:	80 c1       	mov55 $r6,$r1
    ae62:	3c 1c 0a d8 	lwi.gp $r1,[+#0x2b60]
    ae66:	f0 81       	swi37.sp $r0,[+#0x4]
    ae68:	c9 03       	bnez38 $r1,ae6e <_fclose_r+0x12>
    ae6a:	49 ff f7 ab 	jal 9dc0 <__sinit>
    ae6e:	22 03 00 06 	lhsi $r0,[$r6+#0xc]
    ae72:	c8 03       	bnez38 $r0,ae78 <_fclose_r+0x1c>
    ae74:	84 00       	movi55 $r0,#0x0
    ae76:	fc a1       	pop25 $r8,#8    ! {$r6~$r8, $fp, $gp, $lp}
    ae78:	f0 01       	lwi37.sp $r0,[+#0x4]
    ae7a:	80 26       	mov55 $r1,$r6
    ae7c:	49 ff f6 e8 	jal 9c4c <__sflush_r>
    ae80:	04 23 00 0b 	lwi $r2,[$r6+#0x2c]
    ae84:	80 e0       	mov55 $r7,$r0
    ae86:	c2 07       	beqz38 $r2,ae94 <_fclose_r+0x38>
    ae88:	f0 01       	lwi37.sp $r0,[+#0x4]
    ae8a:	a0 77       	lwi333 $r1,[$r6+#0x1c]
    ae8c:	dd 22       	jral5 $r2
    ae8e:	4e 04 00 03 	bgez $r0,ae94 <_fclose_r+0x38>
    ae92:	84 ff       	movi55 $r7,#-1
    ae94:	a4 36       	lhi333 $r0,[$r6+#0xc]
    ae96:	96 3e       	bmski33 $r0,#0x7
    ae98:	c0 05       	beqz38 $r0,aea2 <_fclose_r+0x46>
    ae9a:	f0 01       	lwi37.sp $r0,[+#0x4]
    ae9c:	a0 74       	lwi333 $r1,[$r6+#0x10]
    ae9e:	49 ff f8 c5 	jal a028 <_free_r>
    aea2:	04 13 00 0c 	lwi $r1,[$r6+#0x30]
    aea6:	c1 0b       	beqz38 $r1,aebc <_fclose_r+0x60>
    aea8:	50 03 00 40 	addi $r0,$r6,#0x40
    aeac:	4c 10 00 05 	beq $r1,$r0,aeb6 <_fclose_r+0x5a>
    aeb0:	f0 01       	lwi37.sp $r0,[+#0x4]
    aeb2:	49 ff f8 bb 	jal a028 <_free_r>
    aeb6:	84 00       	movi55 $r0,#0x0
    aeb8:	14 03 00 0c 	swi $r0,[$r6+#0x30]
    aebc:	04 13 00 11 	lwi $r1,[$r6+#0x44]
    aec0:	c1 07       	beqz38 $r1,aece <_fclose_r+0x72>
    aec2:	f0 01       	lwi37.sp $r0,[+#0x4]
    aec4:	49 ff f8 b2 	jal a028 <_free_r>
    aec8:	84 00       	movi55 $r0,#0x0
    aeca:	14 03 00 11 	swi $r0,[$r6+#0x44]
    aece:	49 ff f7 e7 	jal 9e9c <__sfp_lock_acquire>
    aed2:	84 00       	movi55 $r0,#0x0
    aed4:	ac 36       	shi333 $r0,[$r6+#0xc]
    aed6:	49 ff f7 e4 	jal 9e9e <__sfp_lock_release>
    aeda:	80 07       	mov55 $r0,$r7
    aedc:	fc a1       	pop25 $r8,#8    ! {$r6~$r8, $fp, $gp, $lp}
    aede:	84 00       	movi55 $r0,#0x0
    aee0:	dd 9e       	ret5 $lp

0000aee2 <__sfvwrite_r>:
    aee2:	a0 d2       	lwi333 $r3,[$r2+#0x8]
    aee4:	4e 32 01 50 	beqz $r3,b184 <__sfvwrite_r+0x2a2>
    aee8:	fc 62       	push25 $r14,#16    ! {$r6~$r14, $fp, $gp, $lp}
    aeea:	36 3f 80 02 	fsdi $fd3,[$sp+#0x8]
    aeee:	f0 81       	swi37.sp $r0,[+#0x4]
    aef0:	a4 0e       	lhi333 $r0,[$r1+#0xc]
    aef2:	81 82       	mov55 $r12,$r2
    aef4:	96 1e       	bmski33 $r0,#0x3
    aef6:	80 c1       	mov55 $r6,$r1
    aef8:	c0 10       	beqz38 $r0,af18 <__sfvwrite_r+0x36>
    aefa:	a0 0c       	lwi333 $r0,[$r1+#0x10]
    aefc:	c0 0e       	beqz38 $r0,af18 <__sfvwrite_r+0x36>
    aefe:	a4 36       	lhi333 $r0,[$r6+#0xc]
    af00:	b5 0c       	lwi450 $r8,[$r12]
    af02:	54 70 00 02 	andi $r7,$r0,#0x2
    af06:	97 f9       	zeh33 $r7,$r7
    af08:	c7 4d       	beqz38 $r7,afa2 <__sfvwrite_r+0xc0>
    af0a:	85 20       	movi55 $r9,#0x0
    af0c:	46 a7 ff ff 	sethi $r10,#0x7ffff
    af10:	80 e9       	mov55 $r7,$r9
    af12:	50 a5 0c 00 	addi $r10,$r10,#0xc00
    af16:	d5 1b       	j8 af4c <__sfvwrite_r+0x6a>
    af18:	f0 01       	lwi37.sp $r0,[+#0x4]
    af1a:	80 26       	mov55 $r1,$r6
    af1c:	49 ff ff 35 	jal ad86 <__swsetup_r>
    af20:	c0 ef       	beqz38 $r0,aefe <__sfvwrite_r+0x1c>
    af22:	48 00 01 2d 	j b17c <__sfvwrite_r+0x29a>
    af26:	e3 47       	slt45 $r10,$r7
    af28:	80 6a       	mov55 $r3,$r10
    af2a:	04 43 00 09 	lwi $r4,[$r6+#0x24]
    af2e:	f0 01       	lwi37.sp $r0,[+#0x4]
    af30:	a0 77       	lwi333 $r1,[$r6+#0x1c]
    af32:	80 49       	mov55 $r2,$r9
    af34:	40 33 bc 1a 	cmovz $r3,$r7,$r15
    af38:	dd 24       	jral5 $r4
    af3a:	4e 07 01 1d 	blez $r0,b174 <__sfvwrite_r+0x292>
    af3e:	80 4c       	mov55 $r2,$r12
    af40:	a0 52       	lwi333 $r1,[$r2+#0x8]
    af42:	89 20       	add45 $r9,$r0
    af44:	8a e0       	sub45 $r7,$r0
    af46:	9a 08       	sub333 $r0,$r1,$r0
    af48:	a8 12       	swi333 $r0,[$r2+#0x8]
    af4a:	c0 29       	beqz38 $r0,af9c <__sfvwrite_r+0xba>
    af4c:	cf ed       	bnez38 $r7,af26 <__sfvwrite_r+0x44>
    af4e:	b5 28       	lwi450 $r9,[$r8]
    af50:	04 74 00 01 	lwi $r7,[$r8+#0x4]
    af54:	8d 08       	addi45 $r8,#0x8
    af56:	d5 fb       	j8 af4c <__sfvwrite_r+0x6a>
    af58:	a4 b6       	lhi333 $r2,[$r6+#0xc]
    af5a:	a1 f2       	lwi333 $r7,[$r6+#0x8]
    af5c:	54 01 02 00 	andi $r0,$r2,#0x200
    af60:	4e 02 00 7f 	beqz $r0,b05e <__sfvwrite_r+0x17c>
    af64:	e3 27       	slt45 $r9,$r7
    af66:	4e f3 00 79 	bnez $r15,b058 <__sfvwrite_r+0x176>
    af6a:	54 01 04 80 	andi $r0,$r2,#0x480
    af6e:	c8 32       	bnez38 $r0,afd2 <__sfvwrite_r+0xf0>
    af70:	e3 27       	slt45 $r9,$r7
    af72:	4e f3 00 73 	bnez $r15,b058 <__sfvwrite_r+0x176>
    af76:	80 47       	mov55 $r2,$r7
    af78:	b4 06       	lwi450 $r0,[$r6]
    af7a:	80 2a       	mov55 $r1,$r10
    af7c:	49 00 01 94 	jal b2a4 <memmove>
    af80:	a0 32       	lwi333 $r0,[$r6+#0x8]
    af82:	8a 07       	sub45 $r0,$r7
    af84:	a8 32       	swi333 $r0,[$r6+#0x8]
    af86:	b4 06       	lwi450 $r0,[$r6]
    af88:	88 e0       	add45 $r7,$r0
    af8a:	b6 e6       	swi450 $r7,[$r6]
    af8c:	80 e9       	mov55 $r7,$r9
    af8e:	80 2c       	mov55 $r1,$r12
    af90:	a0 0a       	lwi333 $r0,[$r1+#0x8]
    af92:	89 47       	add45 $r10,$r7
    af94:	8b 27       	sub45 $r9,$r7
    af96:	9b c7       	sub333 $r7,$r0,$r7
    af98:	a9 ca       	swi333 $r7,[$r1+#0x8]
    af9a:	cf 15       	bnez38 $r7,afc4 <__sfvwrite_r+0xe2>
    af9c:	84 00       	movi55 $r0,#0x0
    af9e:	48 00 00 f0 	j b17e <__sfvwrite_r+0x29c>
    afa2:	96 04       	xlsb33 $r0,$r0
    afa4:	c0 06       	beqz38 $r0,afb0 <__sfvwrite_r+0xce>
    afa6:	81 c7       	mov55 $r14,$r7
    afa8:	81 67       	mov55 $r11,$r7
    afaa:	81 47       	mov55 $r10,$r7
    afac:	48 00 00 af 	j b10a <__sfvwrite_r+0x228>
    afb0:	81 40       	mov55 $r10,$r0
    afb2:	81 20       	mov55 $r9,$r0
    afb4:	84 02       	movi55 $r0,#0x2
    afb6:	6a 03 00 09 	fmtsr $r0,$fs6
    afba:	46 e7 ff ff 	sethi $r14,#0x7ffff
    afbe:	50 e7 0f ff 	addi $r14,$r14,#0xfff
    afc2:	87 83       	movi55 $fp,#0x3
    afc4:	4e 93 ff ca 	bnez $r9,af58 <__sfvwrite_r+0x76>
    afc8:	b5 48       	lwi450 $r10,[$r8]
    afca:	04 94 00 01 	lwi $r9,[$r8+#0x4]
    afce:	8d 08       	addi45 $r8,#0x8
    afd0:	d5 fa       	j8 afc4 <__sfvwrite_r+0xe2>
    afd2:	a0 35       	lwi333 $r0,[$r6+#0x14]
    afd4:	b5 66       	lwi450 $r11,[$r6]
    afd6:	a0 74       	lwi333 $r1,[$r6+#0x10]
    afd8:	6a 33 00 01 	fmfsr $r3,$fs6
    afdc:	42 0e 00 24 	mul $r0,$fp,$r0
    afe0:	40 d5 84 01 	sub $r13,$r11,$r1
    afe4:	40 00 0c 16 	divsr $r0,$r0,$r0,$r3
    afe8:	50 36 80 01 	addi $r3,$r13,#0x1
    afec:	40 b1 a4 00 	add $r11,$r3,$r9
    aff0:	e2 0b       	slt45 $r0,$r11
    aff2:	54 21 04 00 	andi $r2,$r2,#0x400
    aff6:	40 b0 3c 1a 	cmovz $r11,$r0,$r15
    affa:	f0 01       	lwi37.sp $r0,[+#0x4]
    affc:	c2 11       	beqz38 $r2,b01e <__sfvwrite_r+0x13c>
    affe:	80 2b       	mov55 $r1,$r11
    b000:	49 ff f8 50 	jal a0a0 <_malloc_r>
    b004:	80 e0       	mov55 $r7,$r0
    b006:	c0 19       	beqz38 $r0,b038 <__sfvwrite_r+0x156>
    b008:	a0 74       	lwi333 $r1,[$r6+#0x10]
    b00a:	80 4d       	mov55 $r2,$r13
    b00c:	49 ff f7 a0 	jal 9f4c <memcpy>
    b010:	a4 36       	lhi333 $r0,[$r6+#0xc]
    b012:	66 00 04 80 	bitci $r0,$r0,#0x480
    b016:	58 00 00 80 	ori $r0,$r0,#0x80
    b01a:	ac 36       	shi333 $r0,[$r6+#0xc]
    b01c:	d5 13       	j8 b042 <__sfvwrite_r+0x160>
    b01e:	80 4b       	mov55 $r2,$r11
    b020:	49 00 01 9a 	jal b354 <_realloc_r>
    b024:	80 e0       	mov55 $r7,$r0
    b026:	c8 0e       	bnez38 $r0,b042 <__sfvwrite_r+0x160>
    b028:	f0 01       	lwi37.sp $r0,[+#0x4]
    b02a:	a0 74       	lwi333 $r1,[$r6+#0x10]
    b02c:	49 ff f7 fe 	jal a028 <_free_r>
    b030:	a4 36       	lhi333 $r0,[$r6+#0xc]
    b032:	66 00 00 80 	bitci $r0,$r0,#0x80
    b036:	ac 36       	shi333 $r0,[$r6+#0xc]
    b038:	84 0c       	movi55 $r0,#0xc
    b03a:	3c 0e 0a d4 	swi.gp $r0,[+#0x2b50]
    b03e:	48 00 00 9b 	j b174 <__sfvwrite_r+0x292>
    b042:	a9 f4       	swi333 $r7,[$r6+#0x10]
    b044:	14 b3 00 05 	swi $r11,[$r6+#0x14]
    b048:	88 ed       	add45 $r7,$r13
    b04a:	8b 6d       	sub45 $r11,$r13
    b04c:	b6 e6       	swi450 $r7,[$r6]
    b04e:	14 b3 00 02 	swi $r11,[$r6+#0x8]
    b052:	80 e9       	mov55 $r7,$r9
    b054:	48 ff ff 8e 	j af70 <__sfvwrite_r+0x8e>
    b058:	80 e9       	mov55 $r7,$r9
    b05a:	48 ff ff 8e 	j af76 <__sfvwrite_r+0x94>
    b05e:	b4 06       	lwi450 $r0,[$r6]
    b060:	a0 74       	lwi333 $r1,[$r6+#0x10]
    b062:	e2 20       	slt45 $r1,$r0
    b064:	e9 04       	bnezs8 b06c <__sfvwrite_r+0x18a>
    b066:	a1 35       	lwi333 $r4,[$r6+#0x14]
    b068:	e3 24       	slt45 $r9,$r4
    b06a:	e8 18       	beqzs8 b09a <__sfvwrite_r+0x1b8>
    b06c:	e2 e9       	slt45 $r7,$r9
    b06e:	40 74 bc 1a 	cmovz $r7,$r9,$r15
    b072:	80 2a       	mov55 $r1,$r10
    b074:	80 47       	mov55 $r2,$r7
    b076:	49 00 01 17 	jal b2a4 <memmove>
    b07a:	a0 32       	lwi333 $r0,[$r6+#0x8]
    b07c:	b4 26       	lwi450 $r1,[$r6]
    b07e:	8a 07       	sub45 $r0,$r7
    b080:	88 27       	add45 $r1,$r7
    b082:	a8 32       	swi333 $r0,[$r6+#0x8]
    b084:	b6 26       	swi450 $r1,[$r6]
    b086:	4e 03 ff 84 	bnez $r0,af8e <__sfvwrite_r+0xac>
    b08a:	f0 01       	lwi37.sp $r0,[+#0x4]
    b08c:	80 26       	mov55 $r1,$r6
    b08e:	49 ff f6 73 	jal 9d74 <_fflush_r>
    b092:	4e 02 ff 7e 	beqz $r0,af8e <__sfvwrite_r+0xac>
    b096:	48 00 00 6f 	j b174 <__sfvwrite_r+0x292>
    b09a:	40 f7 24 06 	slt $r15,$r14,$r9
    b09e:	80 0e       	mov55 $r0,$r14
    b0a0:	40 04 bc 1a 	cmovz $r0,$r9,$r15
    b0a4:	40 30 10 76 	divsr $r3,$r3,$r0,$r4
    b0a8:	04 53 00 09 	lwi $r5,[$r6+#0x24]
    b0ac:	f0 01       	lwi37.sp $r0,[+#0x4]
    b0ae:	a0 77       	lwi333 $r1,[$r6+#0x1c]
    b0b0:	80 4a       	mov55 $r2,$r10
    b0b2:	fe e4       	mul33 $r3,$r4
    b0b4:	dd 25       	jral5 $r5
    b0b6:	80 e0       	mov55 $r7,$r0
    b0b8:	4e 06 ff 6b 	bgtz $r0,af8e <__sfvwrite_r+0xac>
    b0bc:	d5 5c       	j8 b174 <__sfvwrite_r+0x292>
    b0be:	4e e2 00 2e 	beqz $r14,b11a <__sfvwrite_r+0x238>
    b0c2:	b4 06       	lwi450 $r0,[$r6]
    b0c4:	a0 74       	lwi333 $r1,[$r6+#0x10]
    b0c6:	e3 47       	slt45 $r10,$r7
    b0c8:	81 aa       	mov55 $r13,$r10
    b0ca:	40 d3 bc 1a 	cmovz $r13,$r7,$r15
    b0ce:	e2 20       	slt45 $r1,$r0
    b0d0:	04 93 00 02 	lwi $r9,[$r6+#0x8]
    b0d4:	a0 f5       	lwi333 $r3,[$r6+#0x14]
    b0d6:	e8 2f       	beqzs8 b134 <__sfvwrite_r+0x252>
    b0d8:	89 23       	add45 $r9,$r3
    b0da:	e1 2d       	slts45 $r9,$r13
    b0dc:	e8 2c       	beqzs8 b134 <__sfvwrite_r+0x252>
    b0de:	80 2b       	mov55 $r1,$r11
    b0e0:	80 49       	mov55 $r2,$r9
    b0e2:	49 00 00 e1 	jal b2a4 <memmove>
    b0e6:	b4 06       	lwi450 $r0,[$r6]
    b0e8:	80 26       	mov55 $r1,$r6
    b0ea:	88 09       	add45 $r0,$r9
    b0ec:	b6 06       	swi450 $r0,[$r6]
    b0ee:	f0 01       	lwi37.sp $r0,[+#0x4]
    b0f0:	49 ff f6 42 	jal 9d74 <_fflush_r>
    b0f4:	c8 40       	bnez38 $r0,b174 <__sfvwrite_r+0x292>
    b0f6:	8a e9       	sub45 $r7,$r9
    b0f8:	c7 37       	beqz38 $r7,b166 <__sfvwrite_r+0x284>
    b0fa:	80 2c       	mov55 $r1,$r12
    b0fc:	a0 0a       	lwi333 $r0,[$r1+#0x8]
    b0fe:	89 69       	add45 $r11,$r9
    b100:	8a 09       	sub45 $r0,$r9
    b102:	8b 49       	sub45 $r10,$r9
    b104:	a8 0a       	swi333 $r0,[$r1+#0x8]
    b106:	4e 02 ff 4b 	beqz $r0,af9c <__sfvwrite_r+0xba>
    b10a:	4e a3 ff da 	bnez $r10,b0be <__sfvwrite_r+0x1dc>
    b10e:	b5 68       	lwi450 $r11,[$r8]
    b110:	04 a4 00 01 	lwi $r10,[$r8+#0x4]
    b114:	85 c0       	movi55 $r14,#0x0
    b116:	8d 08       	addi45 $r8,#0x8
    b118:	d5 f9       	j8 b10a <__sfvwrite_r+0x228>
    b11a:	80 0b       	mov55 $r0,$r11
    b11c:	84 2a       	movi55 $r1,#0xa
    b11e:	80 4a       	mov55 $r2,$r10
    b120:	49 00 00 b6 	jal b28c <memchr>
    b124:	c0 04       	beqz38 $r0,b12c <__sfvwrite_r+0x24a>
    b126:	9d c1       	addi333 $r7,$r0,#0x1
    b128:	8a eb       	sub45 $r7,$r11
    b12a:	d5 03       	j8 b130 <__sfvwrite_r+0x24e>
    b12c:	50 75 00 01 	addi $r7,$r10,#0x1
    b130:	85 c1       	movi55 $r14,#0x1
    b132:	d5 c8       	j8 b0c2 <__sfvwrite_r+0x1e0>
    b134:	40 f6 8c 07 	slts $r15,$r13,$r3
    b138:	e9 0b       	bnezs8 b14e <__sfvwrite_r+0x26c>
    b13a:	04 43 00 09 	lwi $r4,[$r6+#0x24]
    b13e:	f0 01       	lwi37.sp $r0,[+#0x4]
    b140:	a0 77       	lwi333 $r1,[$r6+#0x1c]
    b142:	80 4b       	mov55 $r2,$r11
    b144:	dd 24       	jral5 $r4
    b146:	81 20       	mov55 $r9,$r0
    b148:	4e 06 ff d7 	bgtz $r0,b0f6 <__sfvwrite_r+0x214>
    b14c:	d5 14       	j8 b174 <__sfvwrite_r+0x292>
    b14e:	80 2b       	mov55 $r1,$r11
    b150:	80 4d       	mov55 $r2,$r13
    b152:	49 00 00 a9 	jal b2a4 <memmove>
    b156:	a0 32       	lwi333 $r0,[$r6+#0x8]
    b158:	81 2d       	mov55 $r9,$r13
    b15a:	8a 0d       	sub45 $r0,$r13
    b15c:	a8 32       	swi333 $r0,[$r6+#0x8]
    b15e:	b4 06       	lwi450 $r0,[$r6]
    b160:	88 0d       	add45 $r0,$r13
    b162:	b6 06       	swi450 $r0,[$r6]
    b164:	d5 c9       	j8 b0f6 <__sfvwrite_r+0x214>
    b166:	f0 01       	lwi37.sp $r0,[+#0x4]
    b168:	80 26       	mov55 $r1,$r6
    b16a:	49 ff f6 05 	jal 9d74 <_fflush_r>
    b16e:	c8 03       	bnez38 $r0,b174 <__sfvwrite_r+0x292>
    b170:	81 c7       	mov55 $r14,$r7
    b172:	d5 c4       	j8 b0fa <__sfvwrite_r+0x218>
    b174:	a4 36       	lhi333 $r0,[$r6+#0xc]
    b176:	58 00 00 40 	ori $r0,$r0,#0x40
    b17a:	ac 36       	shi333 $r0,[$r6+#0xc]
    b17c:	84 1f       	movi55 $r0,#-1
    b17e:	34 3f 80 02 	fldi $fd3,[$sp+#0x8]
    b182:	fc e2       	pop25 $r14,#16    ! {$r6~$r14, $fp, $gp, $lp}
    b184:	84 00       	movi55 $r0,#0x0
    b186:	dd 9e       	ret5 $lp

0000b188 <_lseek_r>:
    b188:	fc 00       	push25 $r6,#0    ! {$r6, $fp, $gp, $lp}
    b18a:	84 00       	movi55 $r0,#0x0
    b18c:	3c 0e 00 23 	swi.gp $r0,[+#0x8c]
    b190:	80 01       	mov55 $r0,$r1
    b192:	80 22       	mov55 $r1,$r2
    b194:	80 43       	mov55 $r2,$r3
    b196:	49 00 01 67 	jal b464 <_lseek>
    b19a:	5a 0f ff 07 	bnec $r0,#-1,b1a8 <_lseek_r+0x20>
    b19e:	3c 1c 00 23 	lwi.gp $r1,[+#0x8c]
    b1a2:	c1 03       	beqz38 $r1,b1a8 <_lseek_r+0x20>
    b1a4:	3c 1e 0a d4 	swi.gp $r1,[+#0x2b50]
    b1a8:	fc 80       	pop25 $r6,#0    ! {$r6, $fp, $gp, $lp}

0000b1aa <__smakebuf_r>:
    b1aa:	a4 8e       	lhi333 $r2,[$r1+#0xc]
    b1ac:	96 8e       	bmski33 $r2,#0x1
    b1ae:	c2 08       	beqz38 $r2,b1be <__smakebuf_r+0x14>
    b1b0:	50 00 80 43 	addi $r0,$r1,#0x43
    b1b4:	b6 01       	swi450 $r0,[$r1]
    b1b6:	a8 0c       	swi333 $r0,[$r1+#0x10]
    b1b8:	84 01       	movi55 $r0,#0x1
    b1ba:	a8 0d       	swi333 $r0,[$r1+#0x14]
    b1bc:	dd 9e       	ret5 $lp
    b1be:	fc 49       	push25 $r10,#72    ! {$r6~$r10, $fp, $gp, $lp}
    b1c0:	80 c1       	mov55 $r6,$r1
    b1c2:	22 10 80 07 	lhsi $r1,[$r1+#0xe]
    b1c6:	f0 81       	swi37.sp $r0,[+#0x4]
    b1c8:	4e 14 00 0a 	bgez $r1,b1dc <__smakebuf_r+0x32>
    b1cc:	22 03 00 06 	lhsi $r0,[$r6+#0xc]
    b1d0:	54 10 00 80 	andi $r1,$r0,#0x80
    b1d4:	c9 0a       	bnez38 $r1,b1e8 <__smakebuf_r+0x3e>
    b1d6:	44 70 04 00 	movi $r7,#0x400
    b1da:	d5 09       	j8 b1ec <__smakebuf_r+0x42>
    b1dc:	b0 83       	addri36.sp $r2,#0xc
    b1de:	49 00 01 0a 	jal b3f2 <_fstat_r>
    b1e2:	4e 04 00 0a 	bgez $r0,b1f6 <__smakebuf_r+0x4c>
    b1e6:	d5 f3       	j8 b1cc <__smakebuf_r+0x22>
    b1e8:	44 70 00 40 	movi $r7,#0x40
    b1ec:	58 00 08 00 	ori $r0,$r0,#0x800
    b1f0:	ac 36       	shi333 $r0,[$r6+#0xc]
    b1f2:	85 20       	movi55 $r9,#0x0
    b1f4:	d5 1f       	j8 b232 <__smakebuf_r+0x88>
    b1f6:	f5 04       	lwi37.sp $r5,[+#0x10]
    b1f8:	44 00 f0 00 	movi $r0,#0xf000
    b1fc:	ff 46       	and33 $r5,$r0
    b1fe:	50 92 e0 00 	addi $r9,$r5,#-8192
    b202:	44 10 80 00 	movi $r1,#0x8000
    b206:	5c 94 80 01 	slti $r9,$r9,#0x1
    b20a:	a4 36       	lhi333 $r0,[$r6+#0xc]
    b20c:	d9 0e       	bnes38 $r1,b228 <__smakebuf_r+0x7e>
    b20e:	04 53 00 0a 	lwi $r5,[$r6+#0x28]
    b212:	44 10 a1 be 	movi $r1,#0xa1be
    b216:	d9 09       	bnes38 $r1,b228 <__smakebuf_r+0x7e>
    b218:	58 00 04 00 	ori $r0,$r0,#0x400
    b21c:	44 70 04 00 	movi $r7,#0x400
    b220:	ac 36       	shi333 $r0,[$r6+#0xc]
    b222:	14 73 00 13 	swi $r7,[$r6+#0x4c]
    b226:	d5 06       	j8 b232 <__smakebuf_r+0x88>
    b228:	58 00 08 00 	ori $r0,$r0,#0x800
    b22c:	ac 36       	shi333 $r0,[$r6+#0xc]
    b22e:	44 70 04 00 	movi $r7,#0x400
    b232:	f0 01       	lwi37.sp $r0,[+#0x4]
    b234:	80 27       	mov55 $r1,$r7
    b236:	49 ff f7 35 	jal a0a0 <_malloc_r>
    b23a:	c8 10       	bnez38 $r0,b25a <__smakebuf_r+0xb0>
    b23c:	22 03 00 06 	lhsi $r0,[$r6+#0xc]
    b240:	54 10 02 00 	andi $r1,$r0,#0x200
    b244:	c9 22       	bnez38 $r1,b288 <__smakebuf_r+0xde>
    b246:	58 00 00 02 	ori $r0,$r0,#0x2
    b24a:	ac 36       	shi333 $r0,[$r6+#0xc]
    b24c:	50 03 00 43 	addi $r0,$r6,#0x43
    b250:	b6 06       	swi450 $r0,[$r6]
    b252:	a8 34       	swi333 $r0,[$r6+#0x10]
    b254:	84 01       	movi55 $r0,#0x1
    b256:	a8 35       	swi333 $r0,[$r6+#0x14]
    b258:	fc c9       	pop25 $r10,#72    ! {$r6~$r10, $fp, $gp, $lp}
    b25a:	44 10 9d b4 	movi $r1,#0x9db4
    b25e:	3c 1e 0a d7 	swi.gp $r1,[+#0x2b5c]
    b262:	a4 76       	lhi333 $r1,[$r6+#0xc]
    b264:	b6 06       	swi450 $r0,[$r6]
    b266:	58 10 80 80 	ori $r1,$r1,#0x80
    b26a:	ac 76       	shi333 $r1,[$r6+#0xc]
    b26c:	a8 34       	swi333 $r0,[$r6+#0x10]
    b26e:	a9 f5       	swi333 $r7,[$r6+#0x14]
    b270:	4e 92 00 0c 	beqz $r9,b288 <__smakebuf_r+0xde>
    b274:	f0 01       	lwi37.sp $r0,[+#0x4]
    b276:	22 13 00 07 	lhsi $r1,[$r6+#0xe]
    b27a:	49 00 00 cc 	jal b412 <_isatty_r>
    b27e:	c0 05       	beqz38 $r0,b288 <__smakebuf_r+0xde>
    b280:	a4 36       	lhi333 $r0,[$r6+#0xc]
    b282:	58 00 00 01 	ori $r0,$r0,#0x1
    b286:	ac 36       	shi333 $r0,[$r6+#0xc]
    b288:	fc c9       	pop25 $r10,#72    ! {$r6~$r10, $fp, $gp, $lp}
	...

0000b28c <memchr>:
    b28c:	96 48       	zeb33 $r1,$r1
    b28e:	99 42       	add333 $r5,$r0,$r2
    b290:	d0 07       	beqs38 $r0,b29e <memchr+0x12>
    b292:	08 40 00 01 	lbi.bi $r4,[$r0],#0x1
    b296:	4c 40 ff fd 	bne $r4,$r1,b290 <memchr+0x4>
    b29a:	9e 01       	subi333 $r0,$r0,#0x1
    b29c:	dd 9e       	ret5 $lp
    b29e:	84 00       	movi55 $r0,#0x0
    b2a0:	dd 9e       	ret5 $lp
    b2a2:	92 00       	nop16

0000b2a4 <memmove>:
    b2a4:	3a 6f c0 bc 	smw.adm $r6,[$sp],$r16,#0x2    ! {$r6~$r16, $lp}
    b2a8:	84 c0       	movi55 $r6,#0x0
    b2aa:	80 e0       	mov55 $r7,$r0
    b2ac:	c2 51       	beqz38 $r2,b34e <memmove+0xaa>
    b2ae:	e2 e1       	slt45 $r7,$r1
    b2b0:	e9 05       	bnezs8 b2ba <memmove+0x16>
    b2b2:	99 fa       	add333 $r7,$r7,$r2
    b2b4:	98 4a       	add333 $r1,$r1,$r2
    b2b6:	84 60       	movi55 $r3,#0x0
    b2b8:	d5 02       	j8 b2bc <memmove+0x18>
    b2ba:	84 61       	movi55 $r3,#0x1
    b2bc:	54 43 80 03 	andi $r4,$r7,#0x3
    b2c0:	54 50 80 03 	andi $r5,$r1,#0x3
    b2c4:	fa 94       	movpi45 $r4,#0x24
    b2c6:	e2 44       	slt45 $r2,$r4
    b2c8:	e9 2c       	bnezs8 b320 <memmove+0x7c>
    b2ca:	c5 0c       	beqz38 $r5,b2e2 <memmove+0x3e>
    b2cc:	c3 03       	beqz38 $r3,b2d2 <memmove+0x2e>
    b2ce:	52 52 80 04 	subri $r5,$r5,#0x4
    b2d2:	81 02       	mov55 $r8,$r2
    b2d4:	80 45       	mov55 $r2,$r5
    b2d6:	84 c1       	movi55 $r6,#0x1
    b2d8:	48 00 00 24 	j b320 <memmove+0x7c>
    b2dc:	84 c0       	movi55 $r6,#0x0
    b2de:	40 24 08 01 	sub $r2,$r8,$r2
    b2e2:	40 41 14 09 	srli $r4,$r2,#0x5
    b2e6:	95 25       	slli333 $r4,$r4,#0x5
    b2e8:	54 51 00 1f 	andi $r5,$r2,#0x1f
    b2ec:	98 8c       	add333 $r2,$r1,$r4
    b2ee:	9b 0c       	sub333 $r4,$r1,$r4
    b2f0:	9f 24       	subi333 $r4,$r4,#0x4
    b2f2:	40 22 0c 1a 	cmovz $r2,$r4,$r3
    b2f6:	cb 0d       	bnez38 $r3,b310 <memmove+0x6c>
    b2f8:	8e 24       	subi45 $r1,#0x4
    b2fa:	9f fc       	subi333 $r7,$r7,#0x4
    b2fc:	3a 90 c0 0c 	lmw.bdm $r9,[$r1],$r16,#0x0    ! {$r9~$r16}
    b300:	3a 93 c0 2c 	smw.bdm $r9,[$r7],$r16,#0x0    ! {$r9~$r16}
    b304:	4c 11 7f fc 	bne $r1,$r2,b2fc <memmove+0x58>
    b308:	9d fc       	addi333 $r7,$r7,#0x4
    b30a:	9c 4c       	addi333 $r1,$r1,#0x4
    b30c:	48 00 00 08 	j b31c <memmove+0x78>
    b310:	3a 90 c0 04 	lmw.bim $r9,[$r1],$r16,#0x0    ! {$r9~$r16}
    b314:	3a 93 c0 24 	smw.bim $r9,[$r7],$r16,#0x0    ! {$r9~$r16}
    b318:	4c 11 7f fc 	bne $r1,$r2,b310 <memmove+0x6c>
    b31c:	c5 19       	beqz38 $r5,b34e <memmove+0xaa>
    b31e:	80 45       	mov55 $r2,$r5
    b320:	84 a0       	movi55 $r5,#0x0
    b322:	c2 15       	beqz38 $r2,b34c <memmove+0xa8>
    b324:	4e 32 00 0a 	beqz $r3,b338 <memmove+0x94>
    b328:	08 40 80 01 	lbi.bi $r4,[$r1],#0x1
    b32c:	18 43 80 01 	sbi.bi $r4,[$r7],#0x1
    b330:	8c a1       	addi45 $r5,#0x1
    b332:	da fb       	bnes38 $r2,b328 <memmove+0x84>
    b334:	48 00 00 0c 	j b34c <memmove+0xa8>
    b338:	8e 21       	subi45 $r1,#0x1
    b33a:	9f f9       	subi333 $r7,$r7,#0x1
    b33c:	08 40 ff ff 	lbi.bi $r4,[$r1],#-1
    b340:	18 43 ff ff 	sbi.bi $r4,[$r7],#-1
    b344:	8c a1       	addi45 $r5,#0x1
    b346:	da fb       	bnes38 $r2,b33c <memmove+0x98>
    b348:	8c 21       	addi45 $r1,#0x1
    b34a:	8c e1       	addi45 $r7,#0x1
    b34c:	ce c8       	bnez38 $r6,b2dc <memmove+0x38>
    b34e:	3a 6f c0 84 	lmw.bim $r6,[$sp],$r16,#0x2    ! {$r6~$r16, $lp}
    b352:	dd 9e       	ret5 $lp

0000b354 <_realloc_r>:
    b354:	fc 41       	push25 $r10,#8    ! {$r6~$r10, $fp, $gp, $lp}
    b356:	f0 81       	swi37.sp $r0,[+#0x4]
    b358:	81 21       	mov55 $r9,$r1
    b35a:	80 e2       	mov55 $r7,$r2
    b35c:	c9 05       	bnez38 $r1,b366 <_realloc_r+0x12>
    b35e:	80 22       	mov55 $r1,$r2
    b360:	49 ff f6 a0 	jal a0a0 <_malloc_r>
    b364:	fc c1       	pop25 $r10,#8    ! {$r6~$r10, $fp, $gp, $lp}
    b366:	ca 05       	bnez38 $r2,b370 <_realloc_r+0x1c>
    b368:	49 ff f6 60 	jal a028 <_free_r>
    b36c:	80 07       	mov55 $r0,$r7
    b36e:	fc c1       	pop25 $r10,#8    ! {$r6~$r10, $fp, $gp, $lp}
    b370:	49 00 00 60 	jal b430 <_malloc_usable_size_r>
    b374:	e2 07       	slt45 $r0,$r7
    b376:	e8 10       	beqzs8 b396 <_realloc_r+0x42>
    b378:	f0 01       	lwi37.sp $r0,[+#0x4]
    b37a:	80 27       	mov55 $r1,$r7
    b37c:	49 ff f6 92 	jal a0a0 <_malloc_r>
    b380:	80 c0       	mov55 $r6,$r0
    b382:	c0 0c       	beqz38 $r0,b39a <_realloc_r+0x46>
    b384:	80 29       	mov55 $r1,$r9
    b386:	80 47       	mov55 $r2,$r7
    b388:	49 ff f5 e2 	jal 9f4c <memcpy>
    b38c:	f0 01       	lwi37.sp $r0,[+#0x4]
    b38e:	80 29       	mov55 $r1,$r9
    b390:	49 ff f6 4c 	jal a028 <_free_r>
    b394:	d5 03       	j8 b39a <_realloc_r+0x46>
    b396:	80 09       	mov55 $r0,$r9
    b398:	fc c1       	pop25 $r10,#8    ! {$r6~$r10, $fp, $gp, $lp}
    b39a:	80 06       	mov55 $r0,$r6
    b39c:	fc c1       	pop25 $r10,#8    ! {$r6~$r10, $fp, $gp, $lp}

0000b39e <nds_isalpha>:
    b39e:	66 00 00 20 	bitci $r0,$r0,#0x20
    b3a2:	50 00 7f bf 	addi $r0,$r0,#-65
    b3a6:	5c 00 00 1a 	slti $r0,$r0,#0x1a
    b3aa:	dd 9e       	ret5 $lp

0000b3ac <nds_isdigit>:
    b3ac:	50 00 7f d0 	addi $r0,$r0,#-48
    b3b0:	5c 00 00 0a 	slti $r0,$r0,#0xa
    b3b4:	dd 9e       	ret5 $lp

0000b3b6 <nds_isspace>:
    b3b6:	5a 00 20 06 	beqc $r0,#0x20,b3c2 <nds_isspace+0xc>
    b3ba:	8e 09       	subi45 $r0,#0x9
    b3bc:	5c 00 00 05 	slti $r0,$r0,#0x5
    b3c0:	dd 9e       	ret5 $lp
    b3c2:	84 01       	movi55 $r0,#0x1
    b3c4:	dd 9e       	ret5 $lp

0000b3c6 <nds_isupper>:
    b3c6:	50 00 7f bf 	addi $r0,$r0,#-65
    b3ca:	5c 00 00 1a 	slti $r0,$r0,#0x1a
    b3ce:	dd 9e       	ret5 $lp

0000b3d0 <_read_r>:
    b3d0:	fc 00       	push25 $r6,#0    ! {$r6, $fp, $gp, $lp}
    b3d2:	84 00       	movi55 $r0,#0x0
    b3d4:	3c 0e 00 23 	swi.gp $r0,[+#0x8c]
    b3d8:	80 01       	mov55 $r0,$r1
    b3da:	80 22       	mov55 $r1,$r2
    b3dc:	80 43       	mov55 $r2,$r3
    b3de:	49 00 00 3b 	jal b454 <_read>
    b3e2:	5a 0f ff 07 	bnec $r0,#-1,b3f0 <_read_r+0x20>
    b3e6:	3c 1c 00 23 	lwi.gp $r1,[+#0x8c]
    b3ea:	c1 03       	beqz38 $r1,b3f0 <_read_r+0x20>
    b3ec:	3c 1e 0a d4 	swi.gp $r1,[+#0x2b50]
    b3f0:	fc 80       	pop25 $r6,#0    ! {$r6, $fp, $gp, $lp}

0000b3f2 <_fstat_r>:
    b3f2:	fc 00       	push25 $r6,#0    ! {$r6, $fp, $gp, $lp}
    b3f4:	84 00       	movi55 $r0,#0x0
    b3f6:	3c 0e 00 23 	swi.gp $r0,[+#0x8c]
    b3fa:	80 01       	mov55 $r0,$r1
    b3fc:	80 22       	mov55 $r1,$r2
    b3fe:	49 00 00 37 	jal b46c <_fstat>
    b402:	5a 0f ff 07 	bnec $r0,#-1,b410 <_fstat_r+0x1e>
    b406:	3c 1c 00 23 	lwi.gp $r1,[+#0x8c]
    b40a:	c1 03       	beqz38 $r1,b410 <_fstat_r+0x1e>
    b40c:	3c 1e 0a d4 	swi.gp $r1,[+#0x2b50]
    b410:	fc 80       	pop25 $r6,#0    ! {$r6, $fp, $gp, $lp}

0000b412 <_isatty_r>:
    b412:	fc 00       	push25 $r6,#0    ! {$r6, $fp, $gp, $lp}
    b414:	84 00       	movi55 $r0,#0x0
    b416:	3c 0e 00 23 	swi.gp $r0,[+#0x8c]
    b41a:	80 01       	mov55 $r0,$r1
    b41c:	49 00 00 2c 	jal b474 <_isatty>
    b420:	5a 0f ff 07 	bnec $r0,#-1,b42e <_isatty_r+0x1c>
    b424:	3c 1c 00 23 	lwi.gp $r1,[+#0x8c]
    b428:	c1 03       	beqz38 $r1,b42e <_isatty_r+0x1c>
    b42a:	3c 1e 0a d4 	swi.gp $r1,[+#0x2b50]
    b42e:	fc 80       	pop25 $r6,#0    ! {$r6, $fp, $gp, $lp}

0000b430 <_malloc_usable_size_r>:
    b430:	04 00 ff ff 	lwi $r0,[$r1+#-4]
    b434:	4e 04 00 06 	bgez $r0,b440 <_malloc_usable_size_r+0x10>
    b438:	88 20       	add45 $r1,$r0
    b43a:	04 10 ff ff 	lwi $r1,[$r1+#-4]
    b43e:	88 01       	add45 $r0,$r1
    b440:	8e 04       	subi45 $r0,#0x4
    b442:	dd 9e       	ret5 $lp

0000b444 <_exit>:
    b444:	64 00 00 2b 	syscall #0x1
    b448:	d5 00       	j8 b448 <_exit+0x4>
    b44a:	92 00       	nop16

0000b44c <_close>:
    b44c:	64 00 00 6b 	syscall #0x3
    b450:	48 00 00 34 	j b4b8 <__syscall_error_handler>

0000b454 <_read>:
    b454:	64 00 00 8b 	syscall #0x4
    b458:	48 00 00 30 	j b4b8 <__syscall_error_handler>

0000b45c <_write>:
    b45c:	64 00 00 ab 	syscall #0x5
    b460:	48 00 00 2c 	j b4b8 <__syscall_error_handler>

0000b464 <_lseek>:
    b464:	64 00 00 cb 	syscall #0x6
    b468:	48 00 00 28 	j b4b8 <__syscall_error_handler>

0000b46c <_fstat>:
    b46c:	64 00 01 4b 	syscall #0xa
    b470:	48 00 00 24 	j b4b8 <__syscall_error_handler>

0000b474 <_isatty>:
    b474:	64 01 77 4b 	syscall #0xbba
    b478:	c8 06       	bnez38 $r0,b484 <_isatty+0x10>
    b47a:	64 02 ee 2b 	syscall #0x1771
    b47e:	3c 0e 0a d4 	swi.gp $r0,[+#0x2b50]
    b482:	84 00       	movi55 $r0,#0x0
    b484:	dd 9e       	ret5 $lp
    b486:	92 00       	nop16

0000b488 <_sbrk>:
    b488:	3c 1c 0a d9 	lwi.gp $r1,[+#0x2b64]
    b48c:	c9 05       	bnez38 $r1,b496 <_sbrk+0xe>
    b48e:	3e 18 35 80 	addi.gp $r1,#0x3580
    b492:	3c 1e 0a d9 	swi.gp $r1,[+#0x2b64]
    b496:	9c 07       	addi333 $r0,$r0,#0x7
    b498:	92 03       	srli45 $r0,#0x3
    b49a:	94 03       	slli333 $r0,$r0,#0x3
    b49c:	98 08       	add333 $r0,$r1,$r0
    b49e:	40 2f 80 06 	slt $r2,$sp,$r0
    b4a2:	ca 05       	bnez38 $r2,b4ac <_sbrk+0x24>
    b4a4:	3c 0e 0a d9 	swi.gp $r0,[+#0x2b64]
    b4a8:	80 01       	mov55 $r0,$r1
    b4aa:	dd 9e       	ret5 $lp
    b4ac:	84 0c       	movi55 $r0,#0xc
    b4ae:	3c 0e 0a d4 	swi.gp $r0,[+#0x2b50]
    b4b2:	84 1f       	movi55 $r0,#-1
    b4b4:	dd 9e       	ret5 $lp
    b4b6:	92 00       	nop16

0000b4b8 <__syscall_error_handler>:
    b4b8:	9c 41       	addi333 $r1,$r0,#0x1
    b4ba:	c9 06       	bnez38 $r1,b4c6 <__syscall_error_handler+0xe>
    b4bc:	64 02 ee 2b 	syscall #0x1771
    b4c0:	3c 0e 0a d4 	swi.gp $r0,[+#0x2b50]
    b4c4:	84 1f       	movi55 $r0,#-1
    b4c6:	dd 9e       	ret5 $lp
