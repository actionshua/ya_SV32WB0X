
/home/yaguan/work/SV32WB0X_new/SSV.tiramisu.sv32wb0x.20Q2.2105.01.01R/image/mac_atcmd_bl.elf:     file format elf32-nds32le


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
300001d6:	58 f7 85 6c 	ori $r15,$r15,#0x56c
300001da:	dd 2f       	jral5 $r15
300001dc:	46 f0 00 02 	sethi $r15,#0x2
300001e0:	58 f7 85 18 	ori $r15,$r15,#0x518
300001e4:	dd 2f       	jral5 $r15
300001e6:	46 f0 00 02 	sethi $r15,#0x2
300001ea:	58 f7 84 c8 	ori $r15,$r15,#0x4c8
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
30000220:	46 03 00 17 	sethi $r0,#0x30017
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
30000242:	46 03 00 b7 	sethi $r0,#0x300b7
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
  94:	44 40 b4 d0 	movi $r4,#0xb4d0
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
      c2:	48 00 02 c5 	j 64c <tiny_printf_display>
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
     1bc:	49 00 02 4c 	jal 654 <tiny_printf>
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
     1f4:	49 00 02 30 	jal 654 <tiny_printf>
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
     250:	49 00 02 02 	jal 654 <tiny_printf>
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
     270:	49 00 01 c4 	jal 5f8 <ota_flash_init>
     274:	f1 02       	lwi37.sp $r1,[+#0x8]
     276:	f0 03       	lwi37.sp $r0,[+#0xc]
     278:	f0 81       	swi37.sp $r0,[+#0x4]
     27a:	b6 3f       	swi450 $r1,[$sp]
     27c:	44 00 00 f8 	movi $r0,#0xf8
     280:	49 00 01 ea 	jal 654 <tiny_printf>
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
     2d4:	49 00 08 0e 	jal 12f0 <drv_comport_init>
     2d8:	84 23       	movi55 $r1,#0x3
     2da:	84 40       	movi55 $r2,#0x0
     2dc:	84 60       	movi55 $r3,#0x0
     2de:	80 06       	mov55 $r0,$r6
     2e0:	49 00 08 34 	jal 1348 <drv_comport_set_format>
     2e4:	49 00 05 d0 	jal e84 <Cli_Init>
     2e8:	44 00 01 18 	movi $r0,#0x118
     2ec:	49 00 10 a8 	jal 243c <printf>
     2f0:	44 00 01 1c 	movi $r0,#0x11c
     2f4:	49 00 10 a4 	jal 243c <printf>
     2f8:	44 00 01 34 	movi $r0,#0x134
     2fc:	49 00 10 a0 	jal 243c <printf>
     300:	49 00 06 06 	jal f0c <Cli_Start>
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
     394:	46 00 00 b7 	sethi $r0,#0xb7
     398:	58 00 00 00 	ori $r0,$r0,#0x0
     39c:	f0 85       	swi37.sp $r0,[+#0x14]
     39e:	46 00 02 00 	sethi $r0,#0x200
     3a2:	58 00 00 00 	ori $r0,$r0,#0x0
     3a6:	f0 86       	swi37.sp $r0,[+#0x18]
     3a8:	46 03 00 17 	sethi $r0,#0x30017
     3ac:	58 00 00 00 	ori $r0,$r0,#0x0
     3b0:	f2 06       	lwi37.sp $r2,[+#0x18]
     3b2:	f1 05       	lwi37.sp $r1,[+#0x14]
     3b4:	f0 87       	swi37.sp $r0,[+#0x1c]
     3b6:	f0 03       	lwi37.sp $r0,[+#0xc]
     3b8:	5a 00 01 06 	beqc $r0,#0x1,3c4 <fota_fs_upgrade+0x44>
     3bc:	ec 24       	addi10.sp #0x24
     3be:	3b ff fc 84 	lmw.bim $sp,[$sp],$sp,#0x2    ! {$lp}
     3c2:	dd 9e       	ret5 $lp
     3c4:	f0 04       	lwi37.sp $r0,[+#0x10]
     3c6:	5a 08 01 fb 	bnec $r0,#0x1,3bc <fota_fs_upgrade+0x3c>
     3ca:	f0 05       	lwi37.sp $r0,[+#0x14]
     3cc:	9a 51       	sub333 $r1,$r2,$r1
     3ce:	49 00 03 9b 	jal b04 <OTA_LITTLEFS_init>
     3d2:	c0 11       	beqz38 $r0,3f4 <fota_fs_upgrade+0x74>
     3d4:	49 00 03 ee 	jal bb0 <OTA_LITTLEFS_find_and_check>
     3d8:	c0 22       	beqz38 $r0,41c <fota_fs_upgrade+0x9c>
     3da:	49 00 04 8d 	jal cf4 <OTA_LIEELEFS_find_and_update>
     3de:	c0 29       	beqz38 $r0,430 <fota_fs_upgrade+0xb0>
     3e0:	44 00 01 44 	movi $r0,#0x144
     3e4:	b6 1f       	swi450 $r0,[$sp]
     3e6:	84 1f       	movi55 $r0,#-1
     3e8:	f0 81       	swi37.sp $r0,[+#0x4]
     3ea:	44 00 01 3c 	movi $r0,#0x13c
     3ee:	49 00 01 33 	jal 654 <tiny_printf>
     3f2:	d5 0b       	j8 408 <fota_fs_upgrade+0x88>
     3f4:	44 00 01 44 	movi $r0,#0x144
     3f8:	b6 1f       	swi450 $r0,[$sp]
     3fa:	84 1c       	movi55 $r0,#-4
     3fc:	14 0f 80 01 	swi $r0,[$sp+#0x4]
     400:	44 00 01 3c 	movi $r0,#0x13c
     404:	49 00 01 28 	jal 654 <tiny_printf>
     408:	46 03 00 10 	sethi $r0,#0x30010
     40c:	58 00 00 00 	ori $r0,$r0,#0x0
     410:	40 00 20 08 	slli $r0,$r0,#0x8
     414:	92 08       	srli45 $r0,#0x8
     416:	49 00 00 79 	jal 508 <ota_flash_sector_erase>
     41a:	d5 d1       	j8 3bc <fota_fs_upgrade+0x3c>
     41c:	44 00 01 44 	movi $r0,#0x144
     420:	b6 1f       	swi450 $r0,[$sp]
     422:	84 1d       	movi55 $r0,#-3
     424:	f0 81       	swi37.sp $r0,[+#0x4]
     426:	44 00 01 3c 	movi $r0,#0x13c
     42a:	49 00 01 15 	jal 654 <tiny_printf>
     42e:	d5 ed       	j8 408 <fota_fs_upgrade+0x88>
     430:	44 00 01 44 	movi $r0,#0x144
     434:	b6 1f       	swi450 $r0,[$sp]
     436:	84 1e       	movi55 $r0,#-2
     438:	f0 81       	swi37.sp $r0,[+#0x4]
     43a:	44 00 01 3c 	movi $r0,#0x13c
     43e:	49 00 01 0b 	jal 654 <tiny_printf>
     442:	d5 e3       	j8 408 <fota_fs_upgrade+0x88>

00000444 <flash_wait_spi_status_register>:
     444:	ef f8       	addi10.sp #-8
     446:	46 2c 00 01 	sethi $r2,#0xc0001
     44a:	3e 38 00 9c 	addi.gp $r3,#0x9c
     44e:	86 45       	movi55 $r18,#0x5
     450:	51 11 00 14 	addi $r17,$r2,#0x14
     454:	86 03       	movi55 $r16,#0x3
     456:	84 a1       	movi55 $r5,#0x1
     458:	44 40 00 64 	movi $r4,#0x64
     45c:	3c 3e 00 24 	swi.gp $r3,[+#0x90]
     460:	a8 d1       	swi333 $r3,[$r2+#0x4]
     462:	3c 0c 00 26 	lwi.gp $r0,[+#0x98]
     466:	b7 c0       	swi450 $r18,[$r0]
     468:	b7 91       	swi450 $r16,[$r17]
     46a:	a9 54       	swi333 $r5,[$r2+#0x10]
     46c:	f4 81       	swi37.sp $r4,[+#0x4]
     46e:	f0 01       	lwi37.sp $r0,[+#0x4]
     470:	9e 41       	subi333 $r1,$r0,#0x1
     472:	f1 81       	swi37.sp $r1,[+#0x4]
     474:	c8 fd       	bnez38 $r0,46e <flash_wait_spi_status_register+0x2a>
     476:	a0 13       	lwi333 $r0,[$r2+#0xc]
     478:	54 00 00 09 	andi $r0,$r0,#0x9
     47c:	c8 fd       	bnez38 $r0,476 <flash_wait_spi_status_register+0x32>
     47e:	3c 0c 00 24 	lwi.gp $r0,[+#0x90]
     482:	b4 00       	lwi450 $r0,[$r0]
     484:	96 04       	xlsb33 $r0,$r0
     486:	c8 eb       	bnez38 $r0,45c <flash_wait_spi_status_register+0x18>
     488:	ec 08       	addi10.sp #0x8
     48a:	dd 9e       	ret5 $lp

0000048c <flash_write_enable>:
     48c:	3b ff fc bc 	smw.adm $sp,[$sp],$sp,#0x2    ! {$lp}
     490:	ef f4       	addi10.sp #-12
     492:	3c 1c 00 26 	lwi.gp $r1,[+#0x98]
     496:	84 46       	movi55 $r2,#0x6
     498:	b6 41       	swi450 $r2,[$r1]
     49a:	46 0c 00 01 	sethi $r0,#0xc0001
     49e:	84 20       	movi55 $r1,#0x0
     4a0:	a8 45       	swi333 $r1,[$r0+#0x14]
     4a2:	84 21       	movi55 $r1,#0x1
     4a4:	a8 44       	swi333 $r1,[$r0+#0x10]
     4a6:	44 00 00 64 	movi $r0,#0x64
     4aa:	f0 81       	swi37.sp $r0,[+#0x4]
     4ac:	f0 01       	lwi37.sp $r0,[+#0x4]
     4ae:	9e 41       	subi333 $r1,$r0,#0x1
     4b0:	f1 81       	swi37.sp $r1,[+#0x4]
     4b2:	c8 fd       	bnez38 $r0,4ac <flash_write_enable+0x20>
     4b4:	46 1c 00 01 	sethi $r1,#0xc0001
     4b8:	a0 0b       	lwi333 $r0,[$r1+#0xc]
     4ba:	54 00 00 09 	andi $r0,$r0,#0x9
     4be:	c8 fd       	bnez38 $r0,4b8 <flash_write_enable+0x2c>
     4c0:	49 ff ff c2 	jal 444 <flash_wait_spi_status_register>
     4c4:	ec 0c       	addi10.sp #0xc
     4c6:	3b ff fc 84 	lmw.bim $sp,[$sp],$sp,#0x2    ! {$lp}
     4ca:	dd 9e       	ret5 $lp

000004cc <ota_flashctl_bitmode>:
     4cc:	ef f8       	addi10.sp #-8
     4ce:	44 10 00 64 	movi $r1,#0x64
     4d2:	f1 81       	swi37.sp $r1,[+#0x4]
     4d4:	f1 01       	lwi37.sp $r1,[+#0x4]
     4d6:	9e 89       	subi333 $r2,$r1,#0x1
     4d8:	f2 81       	swi37.sp $r2,[+#0x4]
     4da:	c9 fd       	bnez38 $r1,4d4 <ota_flashctl_bitmode+0x8>
     4dc:	46 2c 00 01 	sethi $r2,#0xc0001
     4e0:	a0 53       	lwi333 $r1,[$r2+#0xc]
     4e2:	50 31 00 0c 	addi $r3,$r2,#0xc
     4e6:	54 10 80 09 	andi $r1,$r1,#0x9
     4ea:	c9 fb       	bnez38 $r1,4e0 <ota_flashctl_bitmode+0x14>
     4ec:	5a 00 02 08 	beqc $r0,#0x2,4fc <ota_flashctl_bitmode+0x30>
     4f0:	b4 03       	lwi450 $r0,[$r3]
     4f2:	66 00 00 06 	bitci $r0,$r0,#0x6
     4f6:	b6 03       	swi450 $r0,[$r3]
     4f8:	ec 08       	addi10.sp #0x8
     4fa:	dd 9e       	ret5 $lp
     4fc:	b4 03       	lwi450 $r0,[$r3]
     4fe:	58 00 00 04 	ori $r0,$r0,#0x4
     502:	b6 03       	swi450 $r0,[$r3]
     504:	ec 08       	addi10.sp #0x8
     506:	dd 9e       	ret5 $lp

00000508 <ota_flash_sector_erase>:
     508:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
     50c:	ef f8       	addi10.sp #-8
     50e:	80 c0       	mov55 $r6,$r0
     510:	49 ff ff be 	jal 48c <flash_write_enable>
     514:	40 33 60 09 	srli $r3,$r6,#0x18
     518:	40 13 60 08 	slli $r1,$r6,#0x18
     51c:	fe 5f       	or33 $r1,$r3
     51e:	46 20 0f f0 	sethi $r2,#0xff0
     522:	58 30 80 20 	ori $r3,$r1,#0x20
     526:	fe b6       	and33 $r2,$r6
     528:	44 10 ff 00 	movi $r1,#0xff00
     52c:	92 48       	srli45 $r2,#0x8
     52e:	40 03 04 02 	and $r0,$r6,$r1
     532:	40 00 20 08 	slli $r0,$r0,#0x8
     536:	40 11 88 04 	or $r1,$r3,$r2
     53a:	fe 0f       	or33 $r0,$r1
     53c:	3c 1c 00 26 	lwi.gp $r1,[+#0x98]
     540:	46 2c 00 01 	sethi $r2,#0xc0001
     544:	b6 01       	swi450 $r0,[$r1]
     546:	84 00       	movi55 $r0,#0x0
     548:	a8 15       	swi333 $r0,[$r2+#0x14]
     54a:	84 04       	movi55 $r0,#0x4
     54c:	a8 14       	swi333 $r0,[$r2+#0x10]
     54e:	44 00 00 64 	movi $r0,#0x64
     552:	f0 81       	swi37.sp $r0,[+#0x4]
     554:	f0 01       	lwi37.sp $r0,[+#0x4]
     556:	9e 41       	subi333 $r1,$r0,#0x1
     558:	f1 81       	swi37.sp $r1,[+#0x4]
     55a:	c8 fd       	bnez38 $r0,554 <ota_flash_sector_erase+0x4c>
     55c:	46 1c 00 01 	sethi $r1,#0xc0001
     560:	a0 0b       	lwi333 $r0,[$r1+#0xc]
     562:	54 00 00 09 	andi $r0,$r0,#0x9
     566:	c8 fd       	bnez38 $r0,560 <ota_flash_sector_erase+0x58>
     568:	49 ff ff 6e 	jal 444 <flash_wait_spi_status_register>
     56c:	ec 08       	addi10.sp #0x8
     56e:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
     572:	dd 9e       	ret5 $lp

00000574 <ota_flash_page_program>:
     574:	3a 6f 9c bc 	smw.adm $r6,[$sp],$r7,#0x2    ! {$r6~$r7, $lp}
     578:	ef f4       	addi10.sp #-12
     57a:	80 e0       	mov55 $r7,$r0
     57c:	3c 3c 00 25 	lwi.gp $r3,[+#0x94]
     580:	80 c1       	mov55 $r6,$r1
     582:	99 4b       	add333 $r5,$r1,$r3
     584:	c1 08       	beqz38 $r1,594 <ota_flash_page_program+0x20>
     586:	92 00       	nop16
     588:	08 41 00 01 	lbi.bi $r4,[$r2],#0x1
     58c:	18 41 80 01 	sbi.bi $r4,[$r3],#0x1
     590:	4c 32 ff fc 	bne $r3,$r5,588 <ota_flash_page_program+0x14>
     594:	49 ff ff 7c 	jal 48c <flash_write_enable>
     598:	40 43 e0 09 	srli $r4,$r7,#0x18
     59c:	40 23 e0 08 	slli $r2,$r7,#0x18
     5a0:	fe a7       	or33 $r2,$r4
     5a2:	46 30 0f f0 	sethi $r3,#0xff0
     5a6:	58 41 00 02 	ori $r4,$r2,#0x2
     5aa:	fe fe       	and33 $r3,$r7
     5ac:	44 20 ff 00 	movi $r2,#0xff00
     5b0:	40 03 88 02 	and $r0,$r7,$r2
     5b4:	92 68       	srli45 $r3,#0x8
     5b6:	40 22 0c 04 	or $r2,$r4,$r3
     5ba:	40 00 20 08 	slli $r0,$r0,#0x8
     5be:	fe 17       	or33 $r0,$r2
     5c0:	3c 2c 00 26 	lwi.gp $r2,[+#0x98]
     5c4:	46 1c 00 01 	sethi $r1,#0xc0001
     5c8:	b6 02       	swi450 $r0,[$r2]
     5ca:	84 00       	movi55 $r0,#0x0
     5cc:	a8 0d       	swi333 $r0,[$r1+#0x14]
     5ce:	8c c4       	addi45 $r6,#0x4
     5d0:	44 00 00 64 	movi $r0,#0x64
     5d4:	a9 8c       	swi333 $r6,[$r1+#0x10]
     5d6:	f0 81       	swi37.sp $r0,[+#0x4]
     5d8:	f0 01       	lwi37.sp $r0,[+#0x4]
     5da:	9e 41       	subi333 $r1,$r0,#0x1
     5dc:	f1 81       	swi37.sp $r1,[+#0x4]
     5de:	c8 fd       	bnez38 $r0,5d8 <ota_flash_page_program+0x64>
     5e0:	46 1c 00 01 	sethi $r1,#0xc0001
     5e4:	a0 0b       	lwi333 $r0,[$r1+#0xc]
     5e6:	54 00 00 09 	andi $r0,$r0,#0x9
     5ea:	c8 fd       	bnez38 $r0,5e4 <ota_flash_page_program+0x70>
     5ec:	49 ff ff 2c 	jal 444 <flash_wait_spi_status_register>
     5f0:	ec 0c       	addi10.sp #0xc
     5f2:	3a 6f 9c 84 	lmw.bim $r6,[$sp],$r7,#0x2    ! {$r6~$r7, $lp}
     5f6:	dd 9e       	ret5 $lp

000005f8 <ota_flash_init>:
     5f8:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
     5fc:	44 00 00 00 	movi $r0,#0x0
     600:	49 ff ff 66 	jal 4cc <ota_flashctl_bitmode>
     604:	3e 38 00 a4 	addi.gp $r3,#0xa4
     608:	3c 3e 00 26 	swi.gp $r3,[+#0x98]
     60c:	46 1c 00 01 	sethi $r1,#0xc0001
     610:	3e 08 00 a8 	addi.gp $r0,#0xa8
     614:	3c 0e 00 25 	swi.gp $r0,[+#0x94]
     618:	3e 28 00 9c 	addi.gp $r2,#0x9c
     61c:	b6 61       	swi450 $r3,[$r1]
     61e:	84 01       	movi55 $r0,#0x1
     620:	3c 2e 00 24 	swi.gp $r2,[+#0x90]
     624:	a8 89       	swi333 $r2,[$r1+#0x4]
     626:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
     62a:	dd 9e       	ret5 $lp

0000062c <tiny_vprintf_help>:
     62c:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
     630:	80 c0       	mov55 $r6,$r0
     632:	5a 00 0a 09 	beqc $r0,#0xa,644 <tiny_vprintf_help+0x18>
     636:	80 06       	mov55 $r0,$r6
     638:	49 00 10 b8 	jal 27a8 <serial_tx>
     63c:	84 00       	movi55 $r0,#0x0
     63e:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
     642:	dd 9e       	ret5 $lp
     644:	84 0d       	movi55 $r0,#0xd
     646:	49 00 10 b1 	jal 27a8 <serial_tx>
     64a:	d5 f6       	j8 636 <tiny_vprintf_help+0xa>

0000064c <tiny_printf_display>:
     64c:	3e 00 00 00 	sbi.gp $r0,[+#0x0]
     650:	dd 9e       	ret5 $lp
     652:	92 00       	nop16

00000654 <tiny_printf>:
     654:	2e 18 00 00 	lbsi.gp $r1,[+#0x0]
     658:	c9 04       	bnez38 $r1,660 <tiny_printf+0xc>
     65a:	84 00       	movi55 $r0,#0x0
     65c:	dd 9e       	ret5 $lp
     65e:	92 00       	nop16
     660:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
     664:	44 20 06 2c 	movi $r2,#0x62c
     668:	b0 42       	addri36.sp $r1,#0x8
     66a:	84 60       	movi55 $r3,#0x0
     66c:	49 00 00 06 	jal 678 <tiny_do_printf>
     670:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
     674:	dd 9e       	ret5 $lp
     676:	92 00       	nop16

00000678 <tiny_do_printf>:
     678:	3a 6f ba bc 	smw.adm $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
     67c:	ef dc       	addi10.sp #-36
     67e:	36 3f 80 06 	fsdi $fd3,[$sp+#0x18]
     682:	80 c0       	mov55 $r6,$r0
     684:	20 00 00 00 	lbsi $r0,[$r0+#0x0]
     688:	f3 81       	swi37.sp $r3,[+#0x4]
     68a:	4e 02 01 aa 	beqz $r0,9de <tiny_do_printf+0x366>
     68e:	81 a1       	mov55 $r13,$r1
     690:	84 20       	movi55 $r1,#0x0
     692:	6a 13 80 09 	fmtsr $r1,$fs7
     696:	44 10 00 30 	movi $r1,#0x30
     69a:	6a 13 00 09 	fmtsr $r1,$fs6
     69e:	80 e2       	mov55 $r7,$r2
     6a0:	87 80       	movi55 $fp,#0x0
     6a2:	85 00       	movi55 $r8,#0x0
     6a4:	85 40       	movi55 $r10,#0x0
     6a6:	85 60       	movi55 $r11,#0x0
     6a8:	44 f0 06 b4 	movi $r15,#0x6b4
     6ac:	38 17 ae 02 	lw $r1,[$r15+($r11<<#0x2)]
     6b0:	4a 00 04 00 	jr $r1
     6b4:	1c 07 00 00 	swi.bi $r0,[$r14],#0x0
     6b8:	cc 06       	bnez38 $r4,6c4 <tiny_do_printf+0x4c>
     6ba:	00 00 0c 08 	lbi $r0,[$r0+#0xc08]
     6be:	00 00 2c 07 	lbi $r0,[$r0+#0x2c07]
     6c2:	00 00 ec 07 	lbi $r0,[$r1+#-5113]
     6c6:	00 00 8c c1 	lbi $r0,[$r1+#0xcc1]
     6ca:	92 00       	nop16
     6cc:	20 23 00 00 	lbsi $r2,[$r6+#0x0]
     6d0:	5a 28 25 04 	bnec $r2,#0x25,6d8 <tiny_do_printf+0x60>
     6d4:	48 00 01 6d 	j 9ae <tiny_do_printf+0x336>
     6d8:	5a 28 2d 04 	bnec $r2,#0x2d,6e0 <tiny_do_printf+0x68>
     6dc:	48 00 01 2e 	j 938 <tiny_do_printf+0x2c0>
     6e0:	50 e3 00 00 	addi $r14,$r6,#0x0
     6e4:	5a 28 30 04 	bnec $r2,#0x30,6ec <tiny_do_printf+0x74>
     6e8:	48 00 01 56 	j 994 <tiny_do_printf+0x31c>
     6ec:	50 01 7f d0 	addi $r0,$r2,#-48
     6f0:	96 00       	zeb33 $r0,$r0
     6f2:	e6 0a       	slti45 $r0,#0xa
     6f4:	e8 20       	beqzs8 734 <tiny_do_printf+0xbc>
     6f6:	84 0a       	movi55 $r0,#0xa
     6f8:	42 2e 00 73 	maddr32 $r2,$fp,$r0
     6fc:	85 62       	movi55 $r11,#0x2
     6fe:	51 c1 7f d0 	addi $fp,$r2,#-48
     702:	92 00       	nop16
     704:	20 07 00 01 	lbsi $r0,[$r14+#0x1]
     708:	50 67 00 01 	addi $r6,$r14,#0x1
     70c:	c8 ce       	bnez38 $r0,6a8 <tiny_do_printf+0x30>
     70e:	80 08       	mov55 $r0,$r8
     710:	ec 18       	addi10.sp #0x18
     712:	34 3f 90 03 	fldi.bi $fd3,[$sp],#0xc
     716:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
     71a:	dd 9e       	ret5 $lp
     71c:	5a 00 25 d6 	beqc $r0,#0x25,6c8 <tiny_do_printf+0x50>
     720:	b0 41       	addri36.sp $r1,#0x4
     722:	dd 27       	jral5 $r7
     724:	8d 01       	addi45 $r8,#0x1
     726:	81 c6       	mov55 $r14,$r6
     728:	d5 ee       	j8 704 <tiny_do_printf+0x8c>
     72a:	92 00       	nop16
     72c:	20 23 00 00 	lbsi $r2,[$r6+#0x0]
     730:	81 c6       	mov55 $r14,$r6
     732:	92 00       	nop16
     734:	5a 28 4e 04 	bnec $r2,#0x4e,73c <tiny_do_printf+0xc4>
     738:	48 00 00 f7 	j 926 <tiny_do_printf+0x2ae>
     73c:	5a 28 6c 04 	bnec $r2,#0x6c,744 <tiny_do_printf+0xcc>
     740:	48 00 00 f6 	j 92c <tiny_do_printf+0x2b4>
     744:	5a 28 68 04 	bnec $r2,#0x68,74c <tiny_do_printf+0xd4>
     748:	48 00 01 20 	j 988 <tiny_do_printf+0x310>
     74c:	50 21 7f a8 	addi $r2,$r2,#-88
     750:	84 20       	movi55 $r1,#0x0
     752:	5c f1 00 21 	slti $r15,$r2,#0x21
     756:	10 1f 80 17 	sbi $r1,[$sp+#0x17]
     75a:	e8 54       	beqzs8 802 <tiny_do_printf+0x18a>
     75c:	44 f0 07 68 	movi $r15,#0x768
     760:	38 07 8a 02 	lw $r0,[$r15+($r2<<#0x2)]
     764:	4a 00 00 00 	jr $r0
     768:	1c 09 00 00 	swi.bi $r0,[$r18],#0x0
     76c:	02 08 00 00 	lhi $r0,[$r16+#0x0]
     770:	02 08 00 00 	lhi $r0,[$r16+#0x0]
     774:	02 08 00 00 	lhi $r0,[$r16+#0x0]
     778:	02 08 00 00 	lhi $r0,[$r16+#0x0]
     77c:	02 08 00 00 	lhi $r0,[$r16+#0x0]
     780:	02 08 00 00 	lhi $r0,[$r16+#0x0]
     784:	02 08 00 00 	lhi $r0,[$r16+#0x0]
     788:	02 08 00 00 	lhi $r0,[$r16+#0x0]
     78c:	02 08 00 00 	lhi $r0,[$r16+#0x0]
     790:	02 08 00 00 	lhi $r0,[$r16+#0x0]
     794:	6c 09 00 00 	*unknown*
     798:	18 08 00 00 	sbi.bi $r0,[$r16],#0x0
     79c:	02 08 00 00 	lhi $r0,[$r16+#0x0]
     7a0:	02 08 00 00 	lhi $r0,[$r16+#0x0]
     7a4:	02 08 00 00 	lhi $r0,[$r16+#0x0]
     7a8:	02 08 00 00 	lhi $r0,[$r16+#0x0]
     7ac:	18 08 00 00 	sbi.bi $r0,[$r16],#0x0
     7b0:	02 08 00 00 	lhi $r0,[$r16+#0x0]
     7b4:	02 08 00 00 	lhi $r0,[$r16+#0x0]
     7b8:	02 08 00 00 	lhi $r0,[$r16+#0x0]
     7bc:	02 08 00 00 	lhi $r0,[$r16+#0x0]
     7c0:	20 09 00 00 	lbsi $r0,[$r18+#0x0]
     7c4:	58 09 00 00 	ori $r0,$r18,#0x0
     7c8:	20 09 00 00 	lbsi $r0,[$r18+#0x0]
     7cc:	02 08 00 00 	lhi $r0,[$r16+#0x0]
     7d0:	02 08 00 00 	lhi $r0,[$r16+#0x0]
     7d4:	5e 09 00 00 	sltsi $r0,$r18,#0x0
     7d8:	02 08 00 00 	lhi $r0,[$r16+#0x0]
     7dc:	1c 08 00 00 	swi.bi $r0,[$r16],#0x0
     7e0:	02 08 00 00 	lhi $r0,[$r16+#0x0]
     7e4:	02 08 00 00 	lhi $r0,[$r16+#0x0]
     7e8:	20 09 00 00 	lbsi $r0,[$r18+#0x0]
     7ec:	20 23 00 00 	lbsi $r2,[$r6+#0x0]
     7f0:	84 20       	movi55 $r1,#0x0
     7f2:	50 21 7f a8 	addi $r2,$r2,#-88
     7f6:	5c f1 00 21 	slti $r15,$r2,#0x21
     7fa:	81 c6       	mov55 $r14,$r6
     7fc:	10 1f 80 17 	sbi $r1,[$sp+#0x17]
     800:	e9 ae       	bnezs8 75c <tiny_do_printf+0xe4>
     802:	87 80       	movi55 $fp,#0x0
     804:	85 40       	movi55 $r10,#0x0
     806:	85 60       	movi55 $r11,#0x0
     808:	48 ff ff 7e 	j 704 <tiny_do_printf+0x8c>
     80c:	20 23 00 00 	lbsi $r2,[$r6+#0x0]
     810:	81 c6       	mov55 $r14,$r6
     812:	48 ff ff 6d 	j 6ec <tiny_do_printf+0x74>
     816:	92 00       	nop16
     818:	58 a5 00 04 	ori $r10,$r10,#0x4
     81c:	44 00 00 0a 	movi $r0,#0xa
     820:	54 15 00 08 	andi $r1,$r10,#0x8
     824:	c1 70       	beqz38 $r1,904 <tiny_do_printf+0x28c>
     826:	50 26 80 04 	addi $r2,$r13,#0x4
     82a:	54 15 00 04 	andi $r1,$r10,#0x4
     82e:	b4 6d       	lwi450 $r3,[$r13]
     830:	81 a2       	mov55 $r13,$r2
     832:	c9 6f       	bnez38 $r1,910 <tiny_do_printf+0x298>
     834:	50 6f 80 17 	addi $r6,$sp,#0x17
     838:	54 25 00 02 	andi $r2,$r10,#0x2
     83c:	d5 0c       	j8 854 <tiny_do_printf+0x1dc>
     83e:	92 00       	nop16
     840:	50 12 00 37 	addi $r1,$r4,#0x37
     844:	50 42 00 57 	addi $r4,$r4,#0x57
     848:	ca 0e       	bnez38 $r2,864 <tiny_do_printf+0x1ec>
     84a:	40 31 80 77 	divr $r3,$r3,$r3,$r0
     84e:	af 30       	sbi333 $r4,[$r6+#0x0]
     850:	c3 0e       	beqz38 $r3,86c <tiny_do_printf+0x1f4>
     852:	92 00       	nop16
     854:	40 11 80 97 	divr $r1,$r4,$r3,$r0
     858:	e6 8a       	slti45 $r4,#0xa
     85a:	50 12 00 30 	addi $r1,$r4,#0x30
     85e:	8e c1       	subi45 $r6,#0x1
     860:	e8 f0       	beqzs8 840 <tiny_do_printf+0x1c8>
     862:	92 00       	nop16
     864:	40 31 80 77 	divr $r3,$r3,$r3,$r0
     868:	ae 70       	sbi333 $r1,[$r6+#0x0]
     86a:	cb f5       	bnez38 $r3,854 <tiny_do_printf+0x1dc>
     86c:	50 03 00 00 	addi $r0,$r6,#0x0
     870:	49 00 0f 90 	jal 2790 <my_strlen>
     874:	6a 13 80 01 	fmfsr $r1,$fs7
     878:	54 c5 00 20 	andi $r12,$r10,#0x20
     87c:	40 10 b0 06 	slt $r1,$r1,$r12
     880:	54 95 00 60 	andi $r9,$r10,#0x60
     884:	40 c0 04 00 	add $r12,$r0,$r1
     888:	5a 98 60 04 	bnec $r9,#0x60,890 <tiny_do_printf+0x218>
     88c:	48 00 00 9b 	j 9c2 <tiny_do_printf+0x34a>
     890:	54 05 00 01 	andi $r0,$r10,#0x1
     894:	c8 18       	bnez38 $r0,8c4 <tiny_do_printf+0x24c>
     896:	40 06 70 06 	slt $r0,$r12,$fp
     89a:	c0 15       	beqz38 $r0,8c4 <tiny_do_printf+0x24c>
     89c:	6a 13 00 01 	fmfsr $r1,$fs6
     8a0:	54 a5 00 40 	andi $r10,$r10,#0x40
     8a4:	fa 10       	movpi45 $r0,#0x20
     8a6:	40 10 28 1a 	cmovz $r1,$r0,$r10
     8aa:	81 7c       	mov55 $r11,$fp
     8ac:	81 41       	mov55 $r10,$r1
     8ae:	80 0a       	mov55 $r0,$r10
     8b0:	b0 41       	addri36.sp $r1,#0x4
     8b2:	8f 61       	subi45 $r11,#0x1
     8b4:	4b e0 1c 01 	jral $lp,$r7
     8b8:	40 06 2c 06 	slt $r0,$r12,$r11
     8bc:	c8 f9       	bnez38 $r0,8ae <tiny_do_printf+0x236>
     8be:	89 1c       	add45 $r8,$fp
     8c0:	8b 0c       	sub45 $r8,$r12
     8c2:	83 8c       	mov55 $fp,$r12
     8c4:	5a 90 20 70 	beqc $r9,#0x20,9a4 <tiny_do_printf+0x32c>
     8c8:	a6 30       	lbi333 $r0,[$r6+#0x0]
     8ca:	c0 09       	beqz38 $r0,8dc <tiny_do_printf+0x264>
     8cc:	8c c1       	addi45 $r6,#0x1
     8ce:	b0 41       	addri36.sp $r1,#0x4
     8d0:	4b e0 1c 01 	jral $lp,$r7
     8d4:	08 03 00 01 	lbi.bi $r0,[$r6],#0x1
     8d8:	8d 01       	addi45 $r8,#0x1
     8da:	c8 fa       	bnez38 $r0,8ce <tiny_do_printf+0x256>
     8dc:	40 0e 30 06 	slt $r0,$fp,$r12
     8e0:	c8 91       	bnez38 $r0,802 <tiny_do_printf+0x18a>
     8e2:	40 ce 30 01 	sub $r12,$fp,$r12
     8e6:	4e c2 ff 8e 	beqz $r12,802 <tiny_do_printf+0x18a>
     8ea:	80 cc       	mov55 $r6,$r12
     8ec:	8e c1       	subi45 $r6,#0x1
     8ee:	fa 10       	movpi45 $r0,#0x20
     8f0:	b0 41       	addri36.sp $r1,#0x4
     8f2:	dd 27       	jral5 $r7
     8f4:	ce fc       	bnez38 $r6,8ec <tiny_do_printf+0x274>
     8f6:	89 0c       	add45 $r8,$r12
     8f8:	87 80       	movi55 $fp,#0x0
     8fa:	85 40       	movi55 $r10,#0x0
     8fc:	85 60       	movi55 $r11,#0x0
     8fe:	48 ff ff 03 	j 704 <tiny_do_printf+0x8c>
     902:	92 00       	nop16
     904:	54 15 00 04 	andi $r1,$r10,#0x4
     908:	b4 6d       	lwi450 $r3,[$r13]
     90a:	50 d6 80 04 	addi $r13,$r13,#0x4
     90e:	c1 93       	beqz38 $r1,834 <tiny_do_printf+0x1bc>
     910:	4e 34 ff 92 	bgez $r3,834 <tiny_do_printf+0x1bc>
     914:	58 a5 00 20 	ori $r10,$r10,#0x20
     918:	fe da       	neg33 $r3,$r3
     91a:	d5 8d       	j8 834 <tiny_do_printf+0x1bc>
     91c:	58 a5 00 02 	ori $r10,$r10,#0x2
     920:	fa 00       	movpi45 $r0,#0x10
     922:	48 ff ff 7f 	j 820 <tiny_do_printf+0x1a8>
     926:	85 63       	movi55 $r11,#0x3
     928:	48 ff fe ee 	j 704 <tiny_do_printf+0x8c>
     92c:	58 a5 00 08 	ori $r10,$r10,#0x8
     930:	85 63       	movi55 $r11,#0x3
     932:	48 ff fe e9 	j 704 <tiny_do_printf+0x8c>
     936:	92 00       	nop16
     938:	54 05 00 01 	andi $r0,$r10,#0x1
     93c:	c0 08       	beqz38 $r0,94c <tiny_do_printf+0x2d4>
     93e:	81 c6       	mov55 $r14,$r6
     940:	87 80       	movi55 $fp,#0x0
     942:	85 40       	movi55 $r10,#0x0
     944:	44 b0 00 00 	movi $r11,#0x0
     948:	48 ff fe de 	j 704 <tiny_do_printf+0x8c>
     94c:	58 a5 00 01 	ori $r10,$r10,#0x1
     950:	81 c6       	mov55 $r14,$r6
     952:	85 61       	movi55 $r11,#0x1
     954:	48 ff fe d8 	j 704 <tiny_do_printf+0x8c>
     958:	84 08       	movi55 $r0,#0x8
     95a:	48 ff ff 63 	j 820 <tiny_do_printf+0x1a8>
     95e:	b4 cd       	lwi450 $r6,[$r13]
     960:	66 a5 00 40 	bitci $r10,$r10,#0x40
     964:	50 d6 80 04 	addi $r13,$r13,#0x4
     968:	48 ff ff 82 	j 86c <tiny_do_printf+0x1f4>
     96c:	b4 0d       	lwi450 $r0,[$r13]
     96e:	54 95 00 20 	andi $r9,$r10,#0x20
     972:	10 0f 80 16 	sbi $r0,[$sp+#0x16]
     976:	66 a5 00 40 	bitci $r10,$r10,#0x40
     97a:	50 d6 80 04 	addi $r13,$r13,#0x4
     97e:	50 6f 80 16 	addi $r6,$sp,#0x16
     982:	85 81       	movi55 $r12,#0x1
     984:	d5 86       	j8 890 <tiny_do_printf+0x218>
     986:	92 00       	nop16
     988:	58 a5 00 10 	ori $r10,$r10,#0x10
     98c:	85 63       	movi55 $r11,#0x3
     98e:	48 ff fe bb 	j 704 <tiny_do_printf+0x8c>
     992:	92 00       	nop16
     994:	58 a5 00 40 	ori $r10,$r10,#0x40
     998:	50 e3 00 01 	addi $r14,$r6,#0x1
     99c:	20 23 00 01 	lbsi $r2,[$r6+#0x1]
     9a0:	48 ff fe a6 	j 6ec <tiny_do_printf+0x74>
     9a4:	fa 1d       	movpi45 $r0,#0x2d
     9a6:	b0 41       	addri36.sp $r1,#0x4
     9a8:	dd 27       	jral5 $r7
     9aa:	8d 01       	addi45 $r8,#0x1
     9ac:	d5 8e       	j8 8c8 <tiny_do_printf+0x250>
     9ae:	fa 15       	movpi45 $r0,#0x25
     9b0:	b0 41       	addri36.sp $r1,#0x4
     9b2:	dd 27       	jral5 $r7
     9b4:	8d 01       	addi45 $r8,#0x1
     9b6:	81 c6       	mov55 $r14,$r6
     9b8:	87 80       	movi55 $fp,#0x0
     9ba:	85 40       	movi55 $r10,#0x0
     9bc:	85 60       	movi55 $r11,#0x0
     9be:	48 ff fe a3 	j 704 <tiny_do_printf+0x8c>
     9c2:	fa 1d       	movpi45 $r0,#0x2d
     9c4:	b0 41       	addri36.sp $r1,#0x4
     9c6:	dd 27       	jral5 $r7
     9c8:	54 05 00 01 	andi $r0,$r10,#0x1
     9cc:	8d 01       	addi45 $r8,#0x1
     9ce:	4e 03 ff 7d 	bnez $r0,8c8 <tiny_do_printf+0x250>
     9d2:	40 06 70 06 	slt $r0,$r12,$fp
     9d6:	4e 03 ff 63 	bnez $r0,89c <tiny_do_printf+0x224>
     9da:	48 ff ff 77 	j 8c8 <tiny_do_printf+0x250>
     9de:	84 00       	movi55 $r0,#0x0
     9e0:	48 ff fe 98 	j 710 <tiny_do_printf+0x98>

000009e4 <_block_read>:
     9e4:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
     9e8:	3d 0c 00 22 	lwi.gp $r16,[+#0x88]
     9ec:	a1 47       	lwi333 $r5,[$r0+#0x1c]
     9ee:	46 03 00 00 	sethi $r0,#0x30000
     9f2:	88 10       	add45 $r0,$r16
     9f4:	88 40       	add45 $r2,$r0
     9f6:	42 20 94 73 	maddr32 $r2,$r1,$r5
     9fa:	80 03       	mov55 $r0,$r3
     9fc:	80 22       	mov55 $r1,$r2
     9fe:	80 44       	mov55 $r2,$r4
     a00:	49 00 4a aa 	jal 9f54 <memcpy>
     a04:	84 00       	movi55 $r0,#0x0
     a06:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
     a0a:	dd 9e       	ret5 $lp
     a0c:	3d 3d 3d 3d 	lwi.gp $r19,[+#-199436]
     a10:	3d 53 50 49 	lhi.gp $r21,[+#-89966]
     a14:	46 46 53 20 	sethi $r4,#0x65320
     a18:	66 6f 72 6d 	bitci $r6,$lp,#0x726d
     a1c:	61 74 20 66 	*unknown*
     a20:	61 69 6c 65 	*unknown*
     a24:	64 3a 20 25 	trap #0x5101
     a28:	3d 3d 3d 3d 	lwi.gp $r19,[+#-199436]
     a2c:	3d 6c 64 0a 	lwi.gp $r22,[+#0x19028]
     a30:	00 00 00 00 	lbi $r0,[$r0+#0x0]
     a34:	3d 3d 3d 3d 	lwi.gp $r19,[+#-199436]
     a38:	3d 53 50 49 	lhi.gp $r21,[+#-89966]
     a3c:	46 46 53 20 	sethi $r4,#0x65320
     a40:	6d 6f 75 6e 	*unknown*
     a44:	74 20 66 61 	*unknown*
     a48:	69 6c 65 64 	*unknown*
     a4c:	3a 20 25 3d 	smwa.adm $r2,[$r0],$r9,#0x4    ! {$r2~$r9, $gp}
     a50:	3d 3d 3d 3d 	lwi.gp $r19,[+#-199436]
     a54:	6c 64 0a 00 	*unknown*
     a58:	6f 74 61 5f 	*unknown*
     a5c:	69 6e 66 6f 	*unknown*
     a60:	2e 62 69 6e 	lbi.gp $r6,[+#0x2696e]
     a64:	00 00 00 00 	lbi $r0,[$r0+#0x0]
     a68:	0a 6e 6f 20 	lhi.bi $r6,[$fp],#-8640
     a6c:	6f 74 61 5f 	*unknown*
     a70:	69 6e 66 6f 	*unknown*
     a74:	2e 62 69 6e 	lbi.gp $r6,[+#0x2696e]
     a78:	0a 00 00 00 	lhi.bi $r0,[$r0],#0x0
     a7c:	0a 72 65 61 	lhi.bi $r7,[$r4],#-13630
     a80:	64 20 65 72 	*unknown*
     a84:	72 3a 20 25 	*unknown*
     a88:	64 0a 00 00 	*unknown*
     a8c:	0a 63 61 6c 	lhi.bi $r6,[$r6],#-15656
     a90:	63 20 6d 64 	*unknown*
     a94:	35 2c 20 77 	cpldi cp1,$cpr18,[$r24+#0x1dc]
     a98:	61 69 74 69 	*unknown*
     a9c:	6e 67 0a 00 	*unknown*
     aa0:	6f 74 61 2e 	*unknown*
     aa4:	62 69 6e 00 	*unknown*
     aa8:	0a 6e 6f 20 	lhi.bi $r6,[$fp],#-8640
     aac:	6f 74 61 2e 	*unknown*
     ab0:	62 69 6e 0a 	*unknown*
     ab4:	00 00 00 00 	lbi $r0,[$r0+#0x0]
     ab8:	66 6f 74 61 	bitci $r6,$lp,#0x7461
     abc:	20 75 70 64 	lbsi $r7,[$r10+#-3996]
     ac0:	61 74 65 3a 	amttsl2.s $d0,$r8,$r25,[$i2],[$i6],$m2,$m7
     ac4:	28 69 6d 67 	lbsi.bi $r6,[$r18],#-4761
     ac8:	20 73 69 7a 	lbsi $r7,[$r6+#-5766]
     acc:	65 3a 20 25 	trap #0x5101
     ad0:	64 29 0a 00 	*unknown*
     ad4:	61 64 64 72 	*unknown*
     ad8:	3a 25 78 20 	smw.bi $r2,[$r10],$lp,#0x0    ! {$r2~$lp}
     adc:	73 69 7a 65 	*unknown*
     ae0:	3a 20 25 78 	smw.ad $r2,[$r0],$r9,#0x5    ! {$r2~$r9, $gp, $sp}
     ae4:	0a 00 00 00 	lhi.bi $r0,[$r0],#0x0
     ae8:	0a 53 50 49 	lhi.bi $r5,[$r6],#-24430
     aec:	46 46 53 5f 	sethi $r4,#0x6535f
     af0:	72 65 61 64 	*unknown*
     af4:	20 30 78 25 	lbsi $r3,[$r0+#-2011]
     af8:	6c 78 20 66 	*unknown*
     afc:	61 69 6c 0a 	*unknown*
     b00:	00 00 00 00 	lbi $r0,[$r0+#0x0]

00000b04 <OTA_LITTLEFS_init>:
     b04:	3b ff fc bc 	smw.adm $sp,[$sp],$sp,#0x2    ! {$lp}
     b08:	ef f4       	addi10.sp #-12
     b0a:	45 00 09 e4 	movi $r16,#0x9e4
     b0e:	84 60       	movi55 $r3,#0x0
     b10:	3d 0e 0a f9 	swi.gp $r16,[+#0x2be4]
     b14:	3c 3e 0a fa 	swi.gp $r3,[+#0x2be8]
     b18:	3c 3e 0a fb 	swi.gp $r3,[+#0x2bec]
     b1c:	44 20 01 00 	movi $r2,#0x100
     b20:	3c 3e 0a fc 	swi.gp $r3,[+#0x2bf0]
     b24:	3c 2e 0a fd 	swi.gp $r2,[+#0x2bf4]
     b28:	3c 2e 0a fe 	swi.gp $r2,[+#0x2bf8]
     b2c:	44 30 10 00 	movi $r3,#0x1000
     b30:	3c 3e 0a ff 	swi.gp $r3,[+#0x2bfc]
     b34:	3c 2e 0b 02 	swi.gp $r2,[+#0x2c08]
     b38:	fa 40       	movpi45 $r2,#0x10
     b3a:	3c 2e 0b 03 	swi.gp $r2,[+#0x2c0c]
     b3e:	44 20 01 f4 	movi $r2,#0x1f4
     b42:	40 50 b0 09 	srli $r5,$r1,#0xc
     b46:	3c 2e 0b 01 	swi.gp $r2,[+#0x2c04]
     b4a:	80 80       	mov55 $r4,$r0
     b4c:	3c 5e 0b 00 	swi.gp $r5,[+#0x2c00]
     b50:	3e 08 2b 68 	addi.gp $r0,#0x2b68
     b54:	3e 18 2b e0 	addi.gp $r1,#0x2be0
     b58:	3c 4e 00 22 	swi.gp $r4,[+#0x88]
     b5c:	49 00 27 44 	jal 59e4 <lfs_mount>
     b60:	c8 06       	bnez38 $r0,b6c <OTA_LITTLEFS_init+0x68>
     b62:	84 01       	movi55 $r0,#0x1
     b64:	ec 0c       	addi10.sp #0xc
     b66:	3b ff fc 84 	lmw.bim $sp,[$sp],$sp,#0x2    ! {$lp}
     b6a:	dd 9e       	ret5 $lp
     b6c:	3e 08 2b 68 	addi.gp $r0,#0x2b68
     b70:	3e 18 2b e0 	addi.gp $r1,#0x2be0
     b74:	49 00 37 62 	jal 7a38 <lfs_format>
     b78:	c8 12       	bnez38 $r0,b9c <OTA_LITTLEFS_init+0x98>
     b7a:	3e 08 2b 68 	addi.gp $r0,#0x2b68
     b7e:	3e 18 2b e0 	addi.gp $r1,#0x2be0
     b82:	49 00 27 31 	jal 59e4 <lfs_mount>
     b86:	c0 ee       	beqz38 $r0,b62 <OTA_LITTLEFS_init+0x5e>
     b88:	b6 1f       	swi450 $r0,[$sp]
     b8a:	44 00 0a 34 	movi $r0,#0xa34
     b8e:	49 ff fd 63 	jal 654 <tiny_printf>
     b92:	84 00       	movi55 $r0,#0x0
     b94:	ec 0c       	addi10.sp #0xc
     b96:	3b ff fc 84 	lmw.bim $sp,[$sp],$sp,#0x2    ! {$lp}
     b9a:	dd 9e       	ret5 $lp
     b9c:	b6 1f       	swi450 $r0,[$sp]
     b9e:	44 00 0a 0c 	movi $r0,#0xa0c
     ba2:	49 ff fd 59 	jal 654 <tiny_printf>
     ba6:	84 00       	movi55 $r0,#0x0
     ba8:	ec 0c       	addi10.sp #0xc
     baa:	3b ff fc 84 	lmw.bim $sp,[$sp],$sp,#0x2    ! {$lp}
     bae:	dd 9e       	ret5 $lp

00000bb0 <OTA_LITTLEFS_find_and_check>:
     bb0:	3a 6f a0 bc 	smw.adm $r6,[$sp],$r8,#0x2    ! {$r6~$r8, $lp}
     bb4:	51 ff fd e0 	addi $sp,$sp,#-544
     bb8:	3e 08 2b 68 	addi.gp $r0,#0x2b68
     bbc:	b0 4b       	addri36.sp $r1,#0x2c
     bbe:	44 20 0a 58 	movi $r2,#0xa58
     bc2:	84 61       	movi55 $r3,#0x1
     bc4:	49 00 37 36 	jal 7a30 <lfs_file_open>
     bc8:	4e 05 00 6e 	bltz $r0,ca4 <OTA_LITTLEFS_find_and_check+0xf4>
     bcc:	3e 08 2b 68 	addi.gp $r0,#0x2b68
     bd0:	b0 4b       	addri36.sp $r1,#0x2c
     bd2:	b0 83       	addri36.sp $r2,#0xc
     bd4:	44 30 00 10 	movi $r3,#0x10
     bd8:	49 00 2d 74 	jal 66c0 <lfs_file_read>
     bdc:	5a 00 10 13 	beqc $r0,#0x10,c02 <OTA_LITTLEFS_find_and_check+0x52>
     be0:	fa 00       	movpi45 $r0,#0x10
     be2:	b6 1f       	swi450 $r0,[$sp]
     be4:	44 00 0a 7c 	movi $r0,#0xa7c
     be8:	49 ff fd 36 	jal 654 <tiny_printf>
     bec:	3e 08 2b 68 	addi.gp $r0,#0x2b68
     bf0:	b0 4b       	addri36.sp $r1,#0x2c
     bf2:	49 00 35 65 	jal 76bc <lfs_file_close>
     bf6:	84 00       	movi55 $r0,#0x0
     bf8:	51 ff 82 20 	addi $sp,$sp,#0x220
     bfc:	3a 6f a0 84 	lmw.bim $r6,[$sp],$r8,#0x2    ! {$r6~$r8, $lp}
     c00:	dd 9e       	ret5 $lp
     c02:	b0 4b       	addri36.sp $r1,#0x2c
     c04:	3e 08 2b 68 	addi.gp $r0,#0x2b68
     c08:	49 00 35 5a 	jal 76bc <lfs_file_close>
     c0c:	44 00 0a 8c 	movi $r0,#0xa8c
     c10:	49 ff fd 22 	jal 654 <tiny_printf>
     c14:	3e 08 2b 68 	addi.gp $r0,#0x2b68
     c18:	b0 4b       	addri36.sp $r1,#0x2c
     c1a:	44 20 0a a0 	movi $r2,#0xaa0
     c1e:	84 61       	movi55 $r3,#0x1
     c20:	49 00 37 08 	jal 7a30 <lfs_file_open>
     c24:	4e 05 00 60 	bltz $r0,ce4 <OTA_LITTLEFS_find_and_check+0x134>
     c28:	44 10 0a a0 	movi $r1,#0xaa0
     c2c:	50 2f 81 18 	addi $r2,$sp,#0x118
     c30:	3e 08 2b 68 	addi.gp $r0,#0x2b68
     c34:	49 00 26 be 	jal 59b0 <lfs_stat>
     c38:	f6 47       	lwi37.sp $r6,[+#0x11c]
     c3a:	b0 20       	addri36.sp $r0,#0x80
     c3c:	49 00 13 c2 	jal 33c0 <MD5_Init>
     c40:	44 80 04 00 	movi $r8,#0x400
     c44:	ce 06       	bnez38 $r6,c50 <OTA_LITTLEFS_find_and_check+0xa0>
     c46:	d5 39       	j8 cb8 <OTA_LITTLEFS_find_and_check+0x108>
     c48:	49 00 13 d4 	jal 33f0 <MD5_Update>
     c4c:	c6 36       	beqz38 $r6,cb8 <OTA_LITTLEFS_find_and_check+0x108>
     c4e:	92 00       	nop16
     c50:	5c f3 04 00 	slti $r15,$r6,#0x400
     c54:	80 08       	mov55 $r0,$r8
     c56:	40 03 3c 1b 	cmovn $r0,$r6,$r15
     c5a:	b0 4b       	addri36.sp $r1,#0x2c
     c5c:	3e 28 2c 28 	addi.gp $r2,#0x2c28
     c60:	80 60       	mov55 $r3,$r0
     c62:	80 e0       	mov55 $r7,$r0
     c64:	3e 08 2b 68 	addi.gp $r0,#0x2b68
     c68:	49 00 2d 2c 	jal 66c0 <lfs_file_read>
     c6c:	80 40       	mov55 $r2,$r0
     c6e:	3e 18 2c 28 	addi.gp $r1,#0x2c28
     c72:	b0 20       	addri36.sp $r0,#0x80
     c74:	8a c2       	sub45 $r6,$r2
     c76:	4c 23 bf e9 	beq $r2,$r7,c48 <OTA_LITTLEFS_find_and_check+0x98>
     c7a:	b6 ff       	swi450 $r7,[$sp]
     c7c:	44 00 0a 7c 	movi $r0,#0xa7c
     c80:	49 ff fc ea 	jal 654 <tiny_printf>
     c84:	b0 07       	addri36.sp $r0,#0x1c
     c86:	b0 60       	addri36.sp $r1,#0x80
     c88:	49 00 13 fc 	jal 3480 <MD5_Final>
     c8c:	b0 4b       	addri36.sp $r1,#0x2c
     c8e:	3e 08 2b 68 	addi.gp $r0,#0x2b68
     c92:	49 00 35 15 	jal 76bc <lfs_file_close>
     c96:	84 00       	movi55 $r0,#0x0
     c98:	51 ff 82 20 	addi $sp,$sp,#0x220
     c9c:	3a 6f a0 84 	lmw.bim $r6,[$sp],$r8,#0x2    ! {$r6~$r8, $lp}
     ca0:	dd 9e       	ret5 $lp
     ca2:	92 00       	nop16
     ca4:	44 00 0a 68 	movi $r0,#0xa68
     ca8:	49 ff fc d6 	jal 654 <tiny_printf>
     cac:	84 00       	movi55 $r0,#0x0
     cae:	51 ff 82 20 	addi $sp,$sp,#0x220
     cb2:	3a 6f a0 84 	lmw.bim $r6,[$sp],$r8,#0x2    ! {$r6~$r8, $lp}
     cb6:	dd 9e       	ret5 $lp
     cb8:	b0 07       	addri36.sp $r0,#0x1c
     cba:	b0 60       	addri36.sp $r1,#0x80
     cbc:	49 00 13 e2 	jal 3480 <MD5_Final>
     cc0:	b0 4b       	addri36.sp $r1,#0x2c
     cc2:	3e 08 2b 68 	addi.gp $r0,#0x2b68
     cc6:	49 00 34 fb 	jal 76bc <lfs_file_close>
     cca:	b0 03       	addri36.sp $r0,#0xc
     ccc:	b0 47       	addri36.sp $r1,#0x1c
     cce:	fa 40       	movpi45 $r2,#0x10
     cd0:	49 00 0d 4a 	jal 2764 <my_memcmp>
     cd4:	5c 00 00 01 	slti $r0,$r0,#0x1
     cd8:	51 ff 82 20 	addi $sp,$sp,#0x220
     cdc:	3a 6f a0 84 	lmw.bim $r6,[$sp],$r8,#0x2    ! {$r6~$r8, $lp}
     ce0:	dd 9e       	ret5 $lp
     ce2:	92 00       	nop16
     ce4:	44 00 0a a8 	movi $r0,#0xaa8
     ce8:	49 ff fc b6 	jal 654 <tiny_printf>
     cec:	84 00       	movi55 $r0,#0x0
     cee:	48 ff ff 85 	j bf8 <OTA_LITTLEFS_find_and_check+0x48>
     cf2:	92 00       	nop16

00000cf4 <OTA_LIEELEFS_find_and_update>:
     cf4:	3a 6f ba bc 	smw.adm $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
     cf8:	ee 94       	addi10.sp #-364
     cfa:	46 43 00 17 	sethi $r4,#0x30017
     cfe:	58 42 00 00 	ori $r4,$r4,#0x0
     d02:	3e 08 2b 68 	addi.gp $r0,#0x2b68
     d06:	b0 43       	addri36.sp $r1,#0xc
     d08:	44 20 0a 58 	movi $r2,#0xa58
     d0c:	84 61       	movi55 $r3,#0x1
     d0e:	f4 82       	swi37.sp $r4,[+#0x8]
     d10:	49 00 36 90 	jal 7a30 <lfs_file_open>
     d14:	4e 05 00 94 	bltz $r0,e3c <OTA_LIEELEFS_find_and_update+0x148>
     d18:	50 1f 80 0c 	addi $r1,$sp,#0xc
     d1c:	3e 08 2b 68 	addi.gp $r0,#0x2b68
     d20:	49 00 34 ce 	jal 76bc <lfs_file_close>
     d24:	3e 08 2b 68 	addi.gp $r0,#0x2b68
     d28:	b0 43       	addri36.sp $r1,#0xc
     d2a:	44 20 0a a0 	movi $r2,#0xaa0
     d2e:	84 61       	movi55 $r3,#0x1
     d30:	49 00 36 80 	jal 7a30 <lfs_file_open>
     d34:	4e 05 00 8e 	bltz $r0,e50 <OTA_LIEELEFS_find_and_update+0x15c>
     d38:	44 10 0a a0 	movi $r1,#0xaa0
     d3c:	50 2f 80 60 	addi $r2,$sp,#0x60
     d40:	3e 08 2b 68 	addi.gp $r0,#0x2b68
     d44:	49 00 26 36 	jal 59b0 <lfs_stat>
     d48:	04 ef 80 02 	lwi $r14,[$sp+#0x8]
     d4c:	04 cf 80 19 	lwi $r12,[$sp+#0x64]
     d50:	40 e7 20 08 	slli $r14,$r14,#0x8
     d54:	40 e7 20 09 	srli $r14,$r14,#0x8
     d58:	14 cf 80 00 	swi $r12,[$sp+#0x0]
     d5c:	44 00 0a b8 	movi $r0,#0xab8
     d60:	41 c7 30 00 	add $fp,$r14,$r12
     d64:	49 ff fc 78 	jal 654 <tiny_printf>
     d68:	40 07 70 06 	slt $r0,$r14,$fp
     d6c:	81 6e       	mov55 $r11,$r14
     d6e:	44 d0 04 00 	movi $r13,#0x400
     d72:	c0 43       	beqz38 $r0,df8 <OTA_LIEELEFS_find_and_update+0x104>
     d74:	40 66 b0 06 	slt $r6,$r13,$r12
     d78:	80 0d       	mov55 $r0,$r13
     d7a:	40 06 18 1a 	cmovz $r0,$r12,$r6
     d7e:	80 c0       	mov55 $r6,$r0
     d80:	f0 81       	swi37.sp $r0,[+#0x4]
     d82:	b7 7f       	swi450 $r11,[$sp]
     d84:	44 00 0a d4 	movi $r0,#0xad4
     d88:	49 ff fc 66 	jal 654 <tiny_printf>
     d8c:	3e 08 2b 68 	addi.gp $r0,#0x2b68
     d90:	b0 43       	addri36.sp $r1,#0xc
     d92:	3e 28 2c 28 	addi.gp $r2,#0x2c28
     d96:	80 66       	mov55 $r3,$r6
     d98:	49 00 2c 94 	jal 66c0 <lfs_file_read>
     d9c:	81 40       	mov55 $r10,$r0
     d9e:	4c 03 40 3f 	bne $r0,$r6,e1c <OTA_LIEELEFS_find_and_update+0x128>
     da2:	e3 6e       	slt45 $r11,$r14
     da4:	e9 24       	bnezs8 dec <OTA_LIEELEFS_find_and_update+0xf8>
     da6:	54 05 8f ff 	andi $r0,$r11,#0xfff
     daa:	c0 35       	beqz38 $r0,e14 <OTA_LIEELEFS_find_and_update+0x120>
     dac:	4e a2 00 20 	beqz $r10,dec <OTA_LIEELEFS_find_and_update+0xf8>
     db0:	3e 88 2c 28 	addi.gp $r8,#0x2c28
     db4:	80 eb       	mov55 $r7,$r11
     db6:	80 ca       	mov55 $r6,$r10
     db8:	85 20       	movi55 $r9,#0x0
     dba:	92 00       	nop16
     dbc:	5c f3 01 00 	slti $r15,$r6,#0x100
     dc0:	80 07       	mov55 $r0,$r7
     dc2:	44 10 01 00 	movi $r1,#0x100
     dc6:	80 48       	mov55 $r2,$r8
     dc8:	e8 04       	beqzs8 dd0 <OTA_LIEELEFS_find_and_update+0xdc>
     dca:	80 07       	mov55 $r0,$r7
     dcc:	80 26       	mov55 $r1,$r6
     dce:	80 48       	mov55 $r2,$r8
     dd0:	50 94 81 00 	addi $r9,$r9,#0x100
     dd4:	49 ff fb d0 	jal 574 <ota_flash_page_program>
     dd8:	40 14 a8 06 	slt $r1,$r9,$r10
     ddc:	50 63 7f 00 	addi $r6,$r6,#-256
     de0:	50 73 81 00 	addi $r7,$r7,#0x100
     de4:	50 84 01 00 	addi $r8,$r8,#0x100
     de8:	c9 ea       	bnez38 $r1,dbc <OTA_LIEELEFS_find_and_update+0xc8>
     dea:	92 00       	nop16
     dec:	50 b5 84 00 	addi $r11,$r11,#0x400
     df0:	e3 7c       	slt45 $r11,$fp
     df2:	50 c6 7c 00 	addi $r12,$r12,#-1024
     df6:	e9 bf       	bnezs8 d74 <OTA_LIEELEFS_find_and_update+0x80>
     df8:	44 00 00 e4 	movi $r0,#0xe4
     dfc:	49 ff fc 2c 	jal 654 <tiny_printf>
     e00:	b0 43       	addri36.sp $r1,#0xc
     e02:	3e 08 2b 68 	addi.gp $r0,#0x2b68
     e06:	49 00 34 5b 	jal 76bc <lfs_file_close>
     e0a:	84 01       	movi55 $r0,#0x1
     e0c:	ed 6c       	addi10.sp #0x16c
     e0e:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
     e12:	dd 9e       	ret5 $lp
     e14:	80 0b       	mov55 $r0,$r11
     e16:	49 ff fb 79 	jal 508 <ota_flash_sector_erase>
     e1a:	d5 c9       	j8 dac <OTA_LIEELEFS_find_and_update+0xb8>
     e1c:	b7 7f       	swi450 $r11,[$sp]
     e1e:	44 00 0a e8 	movi $r0,#0xae8
     e22:	49 ff fc 19 	jal 654 <tiny_printf>
     e26:	b0 43       	addri36.sp $r1,#0xc
     e28:	3e 08 2b 68 	addi.gp $r0,#0x2b68
     e2c:	49 00 34 48 	jal 76bc <lfs_file_close>
     e30:	84 00       	movi55 $r0,#0x0
     e32:	ed 6c       	addi10.sp #0x16c
     e34:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
     e38:	dd 9e       	ret5 $lp
     e3a:	92 00       	nop16
     e3c:	44 00 0a 68 	movi $r0,#0xa68
     e40:	49 ff fc 0a 	jal 654 <tiny_printf>
     e44:	84 00       	movi55 $r0,#0x0
     e46:	ed 6c       	addi10.sp #0x16c
     e48:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
     e4c:	dd 9e       	ret5 $lp
     e4e:	92 00       	nop16
     e50:	44 00 0a a8 	movi $r0,#0xaa8
     e54:	49 ff fc 00 	jal 654 <tiny_printf>
     e58:	84 00       	movi55 $r0,#0x0
     e5a:	ed 6c       	addi10.sp #0x16c
     e5c:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
     e60:	dd 9e       	ret5 $lp
     e62:	92 00       	nop16

00000e64 <drv_uart_tx_0>:
     e64:	3b ff fc bc 	smw.adm $sp,[$sp],$sp,#0x2    ! {$lp}
     e68:	ef f4       	addi10.sp #-12
     e6a:	84 21       	movi55 $r1,#0x1
     e6c:	10 0f 80 07 	sbi $r0,[$sp+#0x7]
     e70:	44 20 00 01 	movi $r2,#0x1
     e74:	50 0f 80 07 	addi $r0,$sp,#0x7
     e78:	49 00 02 76 	jal 1364 <drv_comport_write_fifo>
     e7c:	ec 0c       	addi10.sp #0xc
     e7e:	3b ff fc 84 	lmw.bim $sp,[$sp],$sp,#0x2    ! {$lp}
     e82:	dd 9e       	ret5 $lp

00000e84 <Cli_Init>:
     e84:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
     e88:	84 20       	movi55 $r1,#0x0
     e8a:	fa 44       	movpi45 $r2,#0x14
     e8c:	3e 08 01 b0 	addi.gp $r0,#0x1b0
     e90:	49 00 48 96 	jal 9fbc <memset>
     e94:	84 20       	movi55 $r1,#0x0
     e96:	84 00       	movi55 $r0,#0x0
     e98:	3e 10 01 c8 	sbi.gp $r1,[+#0x1c8]
     e9c:	3c 0e 00 6a 	swi.gp $r0,[+#0x1a8]
     ea0:	3c 0e 00 6b 	swi.gp $r0,[+#0x1ac]
     ea4:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
     ea8:	dd 9e       	ret5 $lp
     eaa:	92 00       	nop16
     eac:	72 65 61 64 	*unknown*
     eb0:	20 66 61 6c 	lbsi $r6,[$r12+#-7828]
     eb4:	69 73 0a 00 	*unknown*
     eb8:	0a 45 52 52 	lhi.bi $r4,[$r10],#-23388
     ebc:	4f 52 3a 2d 	beqz $r21,8316 <Cmd_Meta_restore+0xf2>
     ec0:	31 0a 00 00 	flsi $fs16,[$r20+#0x0]
     ec4:	0a 25 73 00 	lhi.bi $r2,[$r10],#-6656
     ec8:	3f 3e 00 00 	addi.gp $r19,#-131072
     ecc:	0a 0a 55 73 	lhi.bi $r0,[$r20],#-21786
     ed0:	61 67 65 3a 	amtbsl2.s $d0,$r14,$r25,[$i2],[$i6],$m2,$m7
     ed4:	0a 00 00 00 	lhi.bi $r0,[$r0],#0x0
     ed8:	25 2d 32 30 	*unknown*
     edc:	73 09 09 25 	*unknown*
     ee0:	73 0a 00 00 	*unknown*

00000ee4 <getDatafromUart>:
     ee4:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
     ee8:	44 20 00 01 	movi $r2,#0x1
     eec:	49 00 02 4a 	jal 1380 <drv_comport_read_fifo>
     ef0:	4e 07 00 08 	blez $r0,f00 <getDatafromUart+0x1c>
     ef4:	44 00 00 00 	movi $r0,#0x0
     ef8:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
     efc:	4a 00 78 20 	ret $lp
     f00:	44 00 0e ac 	movi $r0,#0xeac
     f04:	49 00 0a 9c 	jal 243c <printf>
     f08:	84 1f       	movi55 $r0,#-1
     f0a:	d5 f7       	j8 ef8 <getDatafromUart+0x14>

00000f0c <Cli_Start>:
     f0c:	3a 6f a0 bc 	smw.adm $r6,[$sp],$r8,#0x2    ! {$r6~$r8, $lp}
     f10:	51 ff ff f0 	addi $sp,$sp,#-16
     f14:	46 00 00 08 	sethi $r0,#0x8
     f18:	3e 88 01 c8 	addi.gp $r8,#0x1c8
     f1c:	04 60 01 12 	lwi $r6,[$r0+#0x448]
     f20:	50 0f 80 0b 	addi $r0,$sp,#0xb
     f24:	84 21       	movi55 $r1,#0x1
     f26:	84 41       	movi55 $r2,#0x1
     f28:	49 00 02 2c 	jal 1380 <drv_comport_read_fifo>
     f2c:	4e 07 01 10 	blez $r0,114c <Cli_Start+0x240>
     f30:	00 0f 80 0b 	lbi $r0,[$sp+#0xb]
     f34:	5a 00 0d 30 	beqc $r0,#0xd,f94 <Cli_Start+0x88>
     f38:	e6 0e       	slti45 $r0,#0xe
     f3a:	e9 27       	bnezs8 f88 <Cli_Start+0x7c>
     f3c:	5a 08 3f 04 	bnec $r0,#0x3f,f44 <Cli_Start+0x38>
     f40:	48 00 00 ea 	j 1114 <Cli_Start+0x208>
     f44:	5a 08 7f 04 	bnec $r0,#0x7f,f4c <Cli_Start+0x40>
     f48:	48 00 00 c0 	j 10c8 <Cli_Start+0x1bc>
     f4c:	5a 00 1b ea 	beqc $r0,#0x1b,f20 <Cli_Start+0x14>
     f50:	3c 4c 00 6a 	lwi.gp $r4,[+#0x1a8]
     f54:	5c f2 07 ff 	slti $r15,$r4,#0x7ff
     f58:	e8 e4       	beqzs8 f20 <Cli_Start+0x14>
     f5a:	96 c2       	seb33 $r3,$r0
     f5c:	9d 61       	addi333 $r5,$r4,#0x1
     f5e:	38 34 10 08 	sb $r3,[$r8+($r4<<#0x0)]
     f62:	3c 5e 00 6a 	swi.gp $r5,[+#0x1a8]
     f66:	50 0f 80 0f 	addi $r0,$sp,#0xf
     f6a:	84 80       	movi55 $r4,#0x0
     f6c:	84 21       	movi55 $r1,#0x1
     f6e:	84 41       	movi55 $r2,#0x1
     f70:	38 44 14 08 	sb $r4,[$r8+($r5<<#0x0)]
     f74:	10 3f 80 0f 	sbi $r3,[$sp+#0xf]
     f78:	49 00 01 f6 	jal 1364 <drv_comport_write_fifo>
     f7c:	3c 0c 00 1c 	lwi.gp $r0,[+#0x70]
     f80:	49 00 47 10 	jal 9da0 <fflush>
     f84:	d5 ce       	j8 f20 <Cli_Start+0x14>
     f86:	92 00       	nop16
     f88:	5a 08 08 04 	bnec $r0,#0x8,f90 <Cli_Start+0x84>
     f8c:	48 00 00 9e 	j 10c8 <Cli_Start+0x1bc>
     f90:	5a 08 0a e0 	bnec $r0,#0xa,f50 <Cli_Start+0x44>
     f94:	3e 08 01 c8 	addi.gp $r0,#0x1c8
     f98:	49 00 49 5c 	jal a250 <strlen>
     f9c:	4e 03 00 e4 	bnez $r0,1164 <Cli_Start+0x258>
     fa0:	2e 28 01 c8 	lbsi.gp $r2,[+#0x1c8]
     fa4:	84 00       	movi55 $r0,#0x0
     fa6:	3c 0e 00 6b 	swi.gp $r0,[+#0x1ac]
     faa:	10 0f 80 0b 	sbi $r0,[$sp+#0xb]
     fae:	c2 51       	beqz38 $r2,1050 <Cli_Start+0x144>
     fb0:	84 20       	movi55 $r1,#0x0
     fb2:	86 00       	movi55 $r16,#0x0
     fb4:	84 60       	movi55 $r3,#0x0
     fb6:	84 a0       	movi55 $r5,#0x0
     fb8:	3e 08 01 c8 	addi.gp $r0,#0x1c8
     fbc:	86 40       	movi55 $r18,#0x0
     fbe:	3f 18 01 b0 	addi.gp $r17,#0x1b0
     fc2:	92 00       	nop16
     fc4:	4e 33 00 72 	bnez $r3,10a8 <Cli_Start+0x19c>
     fc8:	5a 28 20 04 	bnec $r2,#0x20,fd0 <Cli_Start+0xc4>
     fcc:	48 00 00 7a 	j 10c0 <Cli_Start+0x1b4>
     fd0:	38 08 86 0a 	sw $r0,[$r17+($r1<<#0x2)]
     fd4:	45 00 00 01 	movi $r16,#0x1
     fd8:	20 20 00 00 	lbsi $r2,[$r0+#0x0]
     fdc:	5a 28 3d 04 	bnec $r2,#0x3d,fe4 <Cli_Start+0xd8>
     fe0:	48 00 00 ae 	j 113c <Cli_Start+0x230>
     fe4:	5a 20 2c 4a 	beqc $r2,#0x2c,1078 <Cli_Start+0x16c>
     fe8:	80 70       	mov55 $r3,$r16
     fea:	80 a1       	mov55 $r5,$r1
     fec:	20 20 00 01 	lbsi $r2,[$r0+#0x1]
     ff0:	8c 01       	addi45 $r0,#0x1
     ff2:	c2 4f       	beqz38 $r2,1090 <Cli_Start+0x184>
     ff4:	e6 26       	slti45 $r1,#0x6
     ff6:	e9 e7       	bnezs8 fc4 <Cli_Start+0xb8>
     ff8:	46 20 01 00 	sethi $r2,#0x100
     ffc:	11 0f 80 0b 	sbi $r16,[$sp+#0xb]
    1000:	3c 1e 00 6b 	swi.gp $r1,[+#0x1ac]
    1004:	5a 38 01 04 	bnec $r3,#0x1,100c <Cli_Start+0x100>
    1008:	48 00 00 e0 	j 11c8 <Cli_Start+0x2bc>
    100c:	fa 30       	movpi45 $r1,#0x20
    100e:	10 10 7f ff 	sbi $r1,[$r0+#-1]
    1012:	80 26       	mov55 $r1,$r6
    1014:	4e 62 00 e2 	beqz $r6,11d8 <Cli_Start+0x2cc>
    1018:	44 70 84 48 	movi $r7,#0x8448
    101c:	d5 06       	j8 1028 <Cli_Start+0x11c>
    101e:	8c ec       	addi45 $r7,#0xc
    1020:	b4 27       	lwi450 $r1,[$r7]
    1022:	4e 12 00 db 	beqz $r1,11d8 <Cli_Start+0x2cc>
    1026:	92 00       	nop16
    1028:	3c 0c 00 6c 	lwi.gp $r0,[+#0x1b0]
    102c:	49 00 48 ee 	jal a208 <strcmp>
    1030:	4e 03 ff f7 	bnez $r0,101e <Cli_Start+0x112>
    1034:	44 00 00 e4 	movi $r0,#0xe4
    1038:	49 00 0a 02 	jal 243c <printf>
    103c:	3c 0c 00 6b 	lwi.gp $r0,[+#0x1ac]
    1040:	a0 b9       	lwi333 $r2,[$r7+#0x4]
    1042:	8e 01       	subi45 $r0,#0x1
    1044:	3e 18 01 b4 	addi.gp $r1,#0x1b4
    1048:	dd 22       	jral5 $r2
    104a:	b4 07       	lwi450 $r0,[$r7]
    104c:	4e 02 00 c6 	beqz $r0,11d8 <Cli_Start+0x2cc>
    1050:	44 00 0e c8 	movi $r0,#0xec8
    1054:	b6 1f       	swi450 $r0,[$sp]
    1056:	44 00 0e c4 	movi $r0,#0xec4
    105a:	49 00 09 f1 	jal 243c <printf>
    105e:	84 20       	movi55 $r1,#0x0
    1060:	3e 08 01 c8 	addi.gp $r0,#0x1c8
    1064:	44 20 08 01 	movi $r2,#0x801
    1068:	49 00 47 aa 	jal 9fbc <memset>
    106c:	84 00       	movi55 $r0,#0x0
    106e:	3c 0e 00 6a 	swi.gp $r0,[+#0x1a8]
    1072:	48 ff ff 57 	j f20 <Cli_Start+0x14>
    1076:	92 00       	nop16
    1078:	4e 12 00 6e 	beqz $r1,1154 <Cli_Start+0x248>
    107c:	20 20 00 01 	lbsi $r2,[$r0+#0x1]
    1080:	8c 21       	addi45 $r1,#0x1
    1082:	11 20 00 00 	sbi $r18,[$r0+#0x0]
    1086:	80 a1       	mov55 $r5,$r1
    1088:	86 00       	movi55 $r16,#0x0
    108a:	84 60       	movi55 $r3,#0x0
    108c:	8c 01       	addi45 $r0,#0x1
    108e:	ca b3       	bnez38 $r2,ff4 <Cli_Start+0xe8>
    1090:	46 20 01 00 	sethi $r2,#0x100
    1094:	11 0f 80 0b 	sbi $r16,[$sp+#0xb]
    1098:	3c 1e 00 6b 	swi.gp $r1,[+#0x1ac]
    109c:	5a 38 01 04 	bnec $r3,#0x1,10a4 <Cli_Start+0x198>
    10a0:	48 00 00 94 	j 11c8 <Cli_Start+0x2bc>
    10a4:	c9 b4       	bnez38 $r1,100c <Cli_Start+0x100>
    10a6:	d5 d5       	j8 1050 <Cli_Start+0x144>
    10a8:	5a 30 01 04 	beqc $r3,#0x1,10b0 <Cli_Start+0x1a4>
    10ac:	48 ff ff 9f 	j fea <Cli_Start+0xde>
    10b0:	5a 20 20 04 	beqc $r2,#0x20,10b8 <Cli_Start+0x1ac>
    10b4:	48 ff ff 92 	j fd8 <Cli_Start+0xcc>
    10b8:	11 20 00 00 	sbi $r18,[$r0+#0x0]
    10bc:	9c 69       	addi333 $r1,$r5,#0x1
    10be:	86 00       	movi55 $r16,#0x0
    10c0:	80 a1       	mov55 $r5,$r1
    10c2:	84 60       	movi55 $r3,#0x0
    10c4:	48 ff ff 94 	j fec <Cli_Start+0xe0>
    10c8:	3c 0c 00 6a 	lwi.gp $r0,[+#0x1a8]
    10cc:	4e 02 ff 2a 	beqz $r0,f20 <Cli_Start+0x14>
    10d0:	9e c1       	subi333 $r3,$r0,#0x1
    10d2:	84 e8       	movi55 $r7,#0x8
    10d4:	3c 3e 00 6a 	swi.gp $r3,[+#0x1a8]
    10d8:	b0 03       	addri36.sp $r0,#0xc
    10da:	84 80       	movi55 $r4,#0x0
    10dc:	84 21       	movi55 $r1,#0x1
    10de:	84 41       	movi55 $r2,#0x1
    10e0:	38 44 0c 08 	sb $r4,[$r8+($r3<<#0x0)]
    10e4:	10 7f 80 0c 	sbi $r7,[$sp+#0xc]
    10e8:	49 00 01 3e 	jal 1364 <drv_comport_write_fifo>
    10ec:	fa 70       	movpi45 $r3,#0x20
    10ee:	50 0f 80 0d 	addi $r0,$sp,#0xd
    10f2:	84 21       	movi55 $r1,#0x1
    10f4:	44 20 00 01 	movi $r2,#0x1
    10f8:	10 3f 80 0d 	sbi $r3,[$sp+#0xd]
    10fc:	49 00 01 34 	jal 1364 <drv_comport_write_fifo>
    1100:	50 0f 80 0e 	addi $r0,$sp,#0xe
    1104:	84 21       	movi55 $r1,#0x1
    1106:	84 41       	movi55 $r2,#0x1
    1108:	10 7f 80 0e 	sbi $r7,[$sp+#0xe]
    110c:	49 00 01 2c 	jal 1364 <drv_comport_write_fifo>
    1110:	48 ff ff 08 	j f20 <Cli_Start+0x14>
    1114:	3c 2c 00 6a 	lwi.gp $r2,[+#0x1a8]
    1118:	c2 30       	beqz38 $r2,1178 <Cli_Start+0x26c>
    111a:	3c 1c 00 01 	lwi.gp $r1,[+#0x4]
    111e:	8e 21       	subi45 $r1,#0x1
    1120:	e2 41       	slt45 $r2,$r1
    1122:	4e f2 fe ff 	beqz $r15,f20 <Cli_Start+0x14>
    1126:	9c 51       	addi333 $r1,$r2,#0x1
    1128:	38 04 08 08 	sb $r0,[$r8+($r2<<#0x0)]
    112c:	3c 1e 00 6a 	swi.gp $r1,[+#0x1a8]
    1130:	84 00       	movi55 $r0,#0x0
    1132:	38 04 04 08 	sb $r0,[$r8+($r1<<#0x0)]
    1136:	48 ff fe f5 	j f20 <Cli_Start+0x14>
    113a:	92 00       	nop16
    113c:	4e 13 ff 56 	bnez $r1,fe8 <Cli_Start+0xdc>
    1140:	ae 40       	sbi333 $r1,[$r0+#0x0]
    1142:	86 00       	movi55 $r16,#0x0
    1144:	84 21       	movi55 $r1,#0x1
    1146:	84 60       	movi55 $r3,#0x0
    1148:	48 ff ff 51 	j fea <Cli_Start+0xde>
    114c:	ec 10       	addi10.sp #0x10
    114e:	3a 6f a0 84 	lmw.bim $r6,[$sp],$r8,#0x2    ! {$r6~$r8, $lp}
    1152:	dd 9e       	ret5 $lp
    1154:	20 20 00 01 	lbsi $r2,[$r0+#0x1]
    1158:	8c 01       	addi45 $r0,#0x1
    115a:	c2 49       	beqz38 $r2,11ec <Cli_Start+0x2e0>
    115c:	80 70       	mov55 $r3,$r16
    115e:	84 a0       	movi55 $r5,#0x0
    1160:	48 ff ff 32 	j fc4 <Cli_Start+0xb8>
    1164:	3e 08 01 c8 	addi.gp $r0,#0x1c8
    1168:	49 00 48 74 	jal a250 <strlen>
    116c:	44 10 00 00 	movi $r1,#0x0
    1170:	38 14 00 08 	sb $r1,[$r8+($r0<<#0x0)]
    1174:	48 ff ff 16 	j fa0 <Cli_Start+0x94>
    1178:	44 00 0e cc 	movi $r0,#0xecc
    117c:	49 00 09 60 	jal 243c <printf>
    1180:	46 00 00 08 	sethi $r0,#0x8
    1184:	04 00 01 12 	lwi $r0,[$r0+#0x448]
    1188:	44 70 84 48 	movi $r7,#0x8448
    118c:	c8 05       	bnez38 $r0,1196 <Cli_Start+0x28a>
    118e:	d5 13       	j8 11b4 <Cli_Start+0x2a8>
    1190:	8c ec       	addi45 $r7,#0xc
    1192:	b4 07       	lwi450 $r0,[$r7]
    1194:	c0 10       	beqz38 $r0,11b4 <Cli_Start+0x2a8>
    1196:	a0 3a       	lwi333 $r0,[$r7+#0x8]
    1198:	49 00 48 5c 	jal a250 <strlen>
    119c:	c0 fa       	beqz38 $r0,1190 <Cli_Start+0x284>
    119e:	a0 3a       	lwi333 $r0,[$r7+#0x8]
    11a0:	b4 27       	lwi450 $r1,[$r7]
    11a2:	b6 3f       	swi450 $r1,[$sp]
    11a4:	f0 81       	swi37.sp $r0,[+#0x4]
    11a6:	8c ec       	addi45 $r7,#0xc
    11a8:	44 00 0e d8 	movi $r0,#0xed8
    11ac:	49 00 09 48 	jal 243c <printf>
    11b0:	b4 07       	lwi450 $r0,[$r7]
    11b2:	c8 f2       	bnez38 $r0,1196 <Cli_Start+0x28a>
    11b4:	44 00 0e c8 	movi $r0,#0xec8
    11b8:	14 0f 80 00 	swi $r0,[$sp+#0x0]
    11bc:	44 00 0e c4 	movi $r0,#0xec4
    11c0:	49 00 09 3e 	jal 243c <printf>
    11c4:	48 ff fe ae 	j f20 <Cli_Start+0x14>
    11c8:	8c 21       	addi45 $r1,#0x1
    11ca:	3c 1e 00 6b 	swi.gp $r1,[+#0x1ac]
    11ce:	4e 12 ff 41 	beqz $r1,1050 <Cli_Start+0x144>
    11d2:	48 ff ff 20 	j 1012 <Cli_Start+0x106>
    11d6:	92 00       	nop16
    11d8:	3c 0c 00 6a 	lwi.gp $r0,[+#0x1a8]
    11dc:	4e 02 ff 3a 	beqz $r0,1050 <Cli_Start+0x144>
    11e0:	44 00 0e b8 	movi $r0,#0xeb8
    11e4:	49 00 09 2c 	jal 243c <printf>
    11e8:	48 ff ff 34 	j 1050 <Cli_Start+0x144>
    11ec:	11 0f 80 0b 	sbi $r16,[$sp+#0xb]
    11f0:	3c 1e 00 6b 	swi.gp $r1,[+#0x1ac]
    11f4:	5b 00 01 04 	beqc $r16,#0x1,11fc <Cli_Start+0x2f0>
    11f8:	48 ff ff 2c 	j 1050 <Cli_Start+0x144>
    11fc:	3d 0e 00 6b 	swi.gp $r16,[+#0x1ac]
    1200:	48 ff ff 09 	j 1012 <Cli_Start+0x106>

00001204 <comport_uart_register_isr>:
    1204:	48 00 39 86 	j 8510 <hal_uart_register_isr>

00001208 <comport_uart_init>:
    1208:	48 00 39 a4 	j 8550 <hal_uart_init>

0000120c <comport_uart_deinit>:
    120c:	48 00 39 b8 	j 857c <hal_uart_deinit>

00001210 <comport_uart_set_format>:
    1210:	48 00 39 ba 	j 8584 <hal_uart_set_format>

00001214 <comport_uart_write_fifo>:
    1214:	48 00 39 e0 	j 85d4 <hal_uart_write_fifo>

00001218 <comport_uart_read_fifo>:
    1218:	48 00 3a 32 	j 867c <hal_uart_read_fifo>

0000121c <comport_uart_sw_rst>:
    121c:	48 00 3a 64 	j 86e4 <hal_uart_sw_rst>

00001220 <comport_uart_get_line_status>:
    1220:	48 00 3a 68 	j 86f0 <hal_uart_get_line_status>

00001224 <comport_uart_is_receiver_available>:
    1224:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    1228:	49 00 3a 64 	jal 86f0 <hal_uart_get_line_status>
    122c:	96 04       	xlsb33 $r0,$r0
    122e:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    1232:	dd 9e       	ret5 $lp

00001234 <comport_uart_is_transmitter_idle>:
    1234:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    1238:	49 00 3a 5c 	jal 86f0 <hal_uart_get_line_status>
    123c:	42 00 18 0b 	btst $r0,$r0,#0x6
    1240:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    1244:	dd 9e       	ret5 $lp
    1246:	92 00       	nop16

00001248 <comport_uart_direct_read_byte>:
    1248:	48 00 39 c0 	j 85c8 <hal_uart_direct_read_byte>

0000124c <comport_hsuart_register_isr>:
    124c:	80 60       	mov55 $r3,$r0
    124e:	80 41       	mov55 $r2,$r1
    1250:	2e 00 09 cc 	lbi.gp $r0,[+#0x9cc]
    1254:	80 23       	mov55 $r1,$r3
    1256:	48 00 3a cf 	j 87f4 <hal_hsuart_register_isr_ex>
    125a:	92 00       	nop16

0000125c <comport_hsuart_init>:
    125c:	2e 00 09 cc 	lbi.gp $r0,[+#0x9cc]
    1260:	48 00 3a ee 	j 883c <hal_hsuart_init_ex>

00001264 <comport_hsuart_deinit>:
    1264:	2e 00 09 cc 	lbi.gp $r0,[+#0x9cc]
    1268:	48 00 3b 06 	j 8874 <hal_hsuart_deinit_ex>

0000126c <comport_hsuart_set_format>:
    126c:	82 20       	mov55 $r17,$r0
    126e:	82 01       	mov55 $r16,$r1
    1270:	80 a2       	mov55 $r5,$r2
    1272:	80 83       	mov55 $r4,$r3
    1274:	2e 00 09 cc 	lbi.gp $r0,[+#0x9cc]
    1278:	80 31       	mov55 $r1,$r17
    127a:	80 50       	mov55 $r2,$r16
    127c:	80 65       	mov55 $r3,$r5
    127e:	48 00 3b 05 	j 8888 <hal_hsuart_set_format_ex>
    1282:	92 00       	nop16

00001284 <comport_hsuart_write_fifo>:
    1284:	80 a0       	mov55 $r5,$r0
    1286:	80 81       	mov55 $r4,$r1
    1288:	80 62       	mov55 $r3,$r2
    128a:	2e 00 09 cc 	lbi.gp $r0,[+#0x9cc]
    128e:	80 25       	mov55 $r1,$r5
    1290:	80 44       	mov55 $r2,$r4
    1292:	48 00 3b 31 	j 88f4 <hal_hsuart_write_fifo_ex>
    1296:	92 00       	nop16

00001298 <comport_hsuart_read_fifo>:
    1298:	80 a0       	mov55 $r5,$r0
    129a:	80 81       	mov55 $r4,$r1
    129c:	80 62       	mov55 $r3,$r2
    129e:	2e 00 09 cc 	lbi.gp $r0,[+#0x9cc]
    12a2:	80 25       	mov55 $r1,$r5
    12a4:	80 44       	mov55 $r2,$r4
    12a6:	48 00 3b 79 	j 8998 <hal_hsuart_read_fifo_ex>
    12aa:	92 00       	nop16

000012ac <comport_hsuart_sw_rst>:
    12ac:	2e 00 09 cc 	lbi.gp $r0,[+#0x9cc]
    12b0:	48 00 3b aa 	j 8a04 <hal_hsuart_sw_rst_ex>

000012b4 <comport_hsuart_get_line_status>:
    12b4:	2e 00 09 cc 	lbi.gp $r0,[+#0x9cc]
    12b8:	48 00 3b b6 	j 8a24 <hal_hsuart_get_line_status_ex>

000012bc <comport_hsuart_is_receiver_available>:
    12bc:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    12c0:	2e 00 09 cc 	lbi.gp $r0,[+#0x9cc]
    12c4:	49 00 3b b0 	jal 8a24 <hal_hsuart_get_line_status_ex>
    12c8:	96 04       	xlsb33 $r0,$r0
    12ca:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    12ce:	dd 9e       	ret5 $lp

000012d0 <comport_hsuart_is_transmitter_idle>:
    12d0:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    12d4:	2e 00 09 cc 	lbi.gp $r0,[+#0x9cc]
    12d8:	49 00 3b a6 	jal 8a24 <hal_hsuart_get_line_status_ex>
    12dc:	42 00 18 0b 	btst $r0,$r0,#0x6
    12e0:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    12e4:	dd 9e       	ret5 $lp
    12e6:	92 00       	nop16

000012e8 <comport_hsuart_direct_read_byte>:
    12e8:	2e 00 09 cc 	lbi.gp $r0,[+#0x9cc]
    12ec:	48 00 3b a2 	j 8a30 <hal_hsuart_direct_read_byte_ex>

000012f0 <drv_comport_init>:
    12f0:	3b ff fc bc 	smw.adm $sp,[$sp],$sp,#0x2    ! {$lp}
    12f4:	ef f4       	addi10.sp #-12
    12f6:	3c 1c 02 74 	lwi.gp $r1,[+#0x9d0]
    12fa:	c1 05       	beqz38 $r1,1304 <drv_comport_init+0x14>
    12fc:	a0 4a       	lwi333 $r1,[$r1+#0x8]
    12fe:	f0 81       	swi37.sp $r0,[+#0x4]
    1300:	dd 21       	jral5 $r1
    1302:	f0 01       	lwi37.sp $r0,[+#0x4]
    1304:	c8 10       	bnez38 $r0,1324 <drv_comport_init+0x34>
    1306:	3e 08 00 34 	addi.gp $r0,#0x34
    130a:	3c 0e 02 74 	swi.gp $r0,[+#0x9d0]
    130e:	a0 01       	lwi333 $r0,[$r0+#0x4]
    1310:	4b e0 00 01 	jral $lp,$r0
    1314:	3c 0c 02 74 	lwi.gp $r0,[+#0x9d0]
    1318:	a0 06       	lwi333 $r0,[$r0+#0x18]
    131a:	dd 20       	jral5 $r0
    131c:	ec 0c       	addi10.sp #0xc
    131e:	3b ff fc 84 	lmw.bim $sp,[$sp],$sp,#0x2    ! {$lp}
    1322:	dd 9e       	ret5 $lp
    1324:	5a 00 01 0a 	beqc $r0,#0x1,1338 <drv_comport_init+0x48>
    1328:	84 00       	movi55 $r0,#0x0
    132a:	3c 0e 02 74 	swi.gp $r0,[+#0x9d0]
    132e:	ec 0c       	addi10.sp #0xc
    1330:	3b ff fc 84 	lmw.bim $sp,[$sp],$sp,#0x2    ! {$lp}
    1334:	4a 00 78 20 	ret $lp
    1338:	3e 08 00 08 	addi.gp $r0,#0x8
    133c:	3c 0e 02 74 	swi.gp $r0,[+#0x9d0]
    1340:	84 20       	movi55 $r1,#0x0
    1342:	3e 10 09 cc 	sbi.gp $r1,[+#0x9cc]
    1346:	d5 e4       	j8 130e <drv_comport_init+0x1e>

00001348 <drv_comport_set_format>:
    1348:	3c 4c 02 74 	lwi.gp $r4,[+#0x9d0]
    134c:	c4 09       	beqz38 $r4,135e <drv_comport_set_format+0x16>
    134e:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    1352:	a1 23       	lwi333 $r4,[$r4+#0xc]
    1354:	4b e0 10 01 	jral $lp,$r4
    1358:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    135c:	dd 9e       	ret5 $lp
    135e:	84 1f       	movi55 $r0,#-1
    1360:	dd 9e       	ret5 $lp
    1362:	92 00       	nop16

00001364 <drv_comport_write_fifo>:
    1364:	3c 3c 02 74 	lwi.gp $r3,[+#0x9d0]
    1368:	c3 09       	beqz38 $r3,137a <drv_comport_write_fifo+0x16>
    136a:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    136e:	a0 dc       	lwi333 $r3,[$r3+#0x10]
    1370:	4b e0 0c 01 	jral $lp,$r3
    1374:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    1378:	dd 9e       	ret5 $lp
    137a:	84 1f       	movi55 $r0,#-1
    137c:	dd 9e       	ret5 $lp
    137e:	92 00       	nop16

00001380 <drv_comport_read_fifo>:
    1380:	3c 3c 02 74 	lwi.gp $r3,[+#0x9d0]
    1384:	c3 09       	beqz38 $r3,1396 <drv_comport_read_fifo+0x16>
    1386:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    138a:	a0 dd       	lwi333 $r3,[$r3+#0x14]
    138c:	4b e0 0c 01 	jral $lp,$r3
    1390:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    1394:	dd 9e       	ret5 $lp
    1396:	84 1f       	movi55 $r0,#-1
    1398:	dd 9e       	ret5 $lp
    139a:	92 00       	nop16

0000139c <_out_null>:
    139c:	dd 9e       	ret5 $lp
    139e:	92 00       	nop16

000013a0 <_ntoa_format>:
    13a0:	3a 6f ba bc 	smw.adm $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    13a4:	ef fc       	addi10.sp #-4
    13a6:	05 0f 80 10 	lwi $r16,[$sp+#0x40]
    13aa:	81 a2       	mov55 $r13,$r2
    13ac:	55 c8 00 02 	andi $fp,$r16,#0x2
    13b0:	80 e4       	mov55 $r7,$r4
    13b2:	fd 40       	movd44 $r8,$r0
    13b4:	81 43       	mov55 $r10,$r3
    13b6:	00 4f 80 30 	lbi $r4,[$sp+#0x30]
    13ba:	f2 0e       	lwi37.sp $r2,[+#0x38]
    13bc:	04 cf 80 0f 	lwi $r12,[$sp+#0x3c]
    13c0:	4f c3 00 32 	bnez $fp,1424 <_ntoa_format+0x84>
    13c4:	e2 a2       	slt45 $r5,$r2
    13c6:	e8 11       	beqzs8 13e8 <_ntoa_format+0x48>
    13c8:	5c f2 80 20 	slti $r15,$r5,#0x20
    13cc:	e8 0e       	beqzs8 13e8 <_ntoa_format+0x48>
    13ce:	98 3d       	add333 $r0,$r7,$r5
    13d0:	44 30 00 30 	movi $r3,#0x30
    13d4:	d5 04       	j8 13dc <_ntoa_format+0x3c>
    13d6:	92 00       	nop16
    13d8:	5a 50 20 08 	beqc $r5,#0x20,13e8 <_ntoa_format+0x48>
    13dc:	8c a1       	addi45 $r5,#0x1
    13de:	e2 a2       	slt45 $r5,$r2
    13e0:	18 30 00 01 	sbi.bi $r3,[$r0],#0x1
    13e4:	4e f3 ff fa 	bnez $r15,13d8 <_ntoa_format+0x38>
    13e8:	54 08 00 01 	andi $r0,$r16,#0x1
    13ec:	c0 1c       	beqz38 $r0,1424 <_ntoa_format+0x84>
    13ee:	e2 ac       	slt45 $r5,$r12
    13f0:	e8 1a       	beqzs8 1424 <_ntoa_format+0x84>
    13f2:	5c f2 80 20 	slti $r15,$r5,#0x20
    13f6:	4e f2 00 f3 	beqz $r15,15dc <_ntoa_format+0x23c>
    13fa:	44 00 00 30 	movi $r0,#0x30
    13fe:	9d a9       	addi333 $r6,$r5,#0x1
    1400:	38 03 94 08 	sb $r0,[$r7+($r5<<#0x0)]
    1404:	44 10 00 30 	movi $r1,#0x30
    1408:	98 3e       	add333 $r0,$r7,$r6
    140a:	d5 09       	j8 141c <_ntoa_format+0x7c>
    140c:	5a 68 20 04 	bnec $r6,#0x20,1414 <_ntoa_format+0x74>
    1410:	48 00 00 b0 	j 1570 <_ntoa_format+0x1d0>
    1414:	8c c1       	addi45 $r6,#0x1
    1416:	18 10 00 01 	sbi.bi $r1,[$r0],#0x1
    141a:	92 00       	nop16
    141c:	4c 66 7f f8 	bne $r6,$r12,140c <_ntoa_format+0x6c>
    1420:	80 ac       	mov55 $r5,$r12
    1422:	92 00       	nop16
    1424:	54 08 00 10 	andi $r0,$r16,#0x10
    1428:	4e 02 00 64 	beqz $r0,14f0 <_ntoa_format+0x150>
    142c:	54 08 04 00 	andi $r0,$r16,#0x400
    1430:	4e 02 00 86 	beqz $r0,153c <_ntoa_format+0x19c>
    1434:	04 0f 80 0d 	lwi $r0,[$sp+#0x34]
    1438:	5a 08 10 04 	bnec $r0,#0x10,1440 <_ntoa_format+0xa0>
    143c:	48 00 00 a4 	j 1584 <_ntoa_format+0x1e4>
    1440:	04 0f 80 0d 	lwi $r0,[$sp+#0x34]
    1444:	5a 08 02 04 	bnec $r0,#0x2,144c <_ntoa_format+0xac>
    1448:	48 00 00 b0 	j 15a8 <_ntoa_format+0x208>
    144c:	5c f2 80 20 	slti $r15,$r5,#0x20
    1450:	4e f2 00 8d 	beqz $r15,156a <_ntoa_format+0x1ca>
    1454:	44 00 00 30 	movi $r0,#0x30
    1458:	9d a9       	addi333 $r6,$r5,#0x1
    145a:	38 03 94 08 	sb $r0,[$r7+($r5<<#0x0)]
    145e:	92 00       	nop16
    1460:	4c 66 00 54 	beq $r6,$r12,1508 <_ntoa_format+0x168>
    1464:	5c f3 00 20 	slti $r15,$r6,#0x20
    1468:	4e f3 00 c1 	bnez $r15,15ea <_ntoa_format+0x24a>
    146c:	54 f8 00 03 	andi $r15,$r16,#0x3
    1470:	e9 49       	bnezs8 1502 <_ntoa_format+0x162>
    1472:	92 00       	nop16
    1474:	e2 cc       	slt45 $r6,$r12
    1476:	80 4d       	mov55 $r2,$r13
    1478:	40 e3 34 01 	sub $r14,$r6,$r13
    147c:	e8 12       	beqzs8 14a0 <_ntoa_format+0x100>
    147e:	92 00       	nop16
    1480:	50 b1 00 01 	addi $r11,$r2,#0x1
    1484:	fa 10       	movpi45 $r0,#0x20
    1486:	80 29       	mov55 $r1,$r9
    1488:	80 6a       	mov55 $r3,$r10
    148a:	dd 28       	jral5 $r8
    148c:	40 07 2c 00 	add $r0,$r14,$r11
    1490:	40 00 30 06 	slt $r0,$r0,$r12
    1494:	80 4b       	mov55 $r2,$r11
    1496:	c8 f5       	bnez38 $r0,1480 <_ntoa_format+0xe0>
    1498:	40 56 b0 00 	add $r5,$r13,$r12
    149c:	9a ae       	sub333 $r2,$r5,$r6
    149e:	92 00       	nop16
    14a0:	4e 62 00 90 	beqz $r6,15c0 <_ntoa_format+0x220>
    14a4:	9f 71       	subi333 $r5,$r6,#0x1
    14a6:	88 e5       	add45 $r7,$r5
    14a8:	88 c2       	add45 $r6,$r2
    14aa:	92 00       	nop16
    14ac:	50 b1 00 01 	addi $r11,$r2,#0x1
    14b0:	28 03 ff ff 	lbsi.bi $r0,[$r7],#-1
    14b4:	80 29       	mov55 $r1,$r9
    14b6:	80 6a       	mov55 $r3,$r10
    14b8:	dd 28       	jral5 $r8
    14ba:	80 4b       	mov55 $r2,$r11
    14bc:	4c b3 7f f8 	bne $r11,$r6,14ac <_ntoa_format+0x10c>
    14c0:	4f c2 00 12 	beqz $fp,14e4 <_ntoa_format+0x144>
    14c4:	40 03 34 01 	sub $r0,$r6,$r13
    14c8:	e2 0c       	slt45 $r0,$r12
    14ca:	e8 0d       	beqzs8 14e4 <_ntoa_format+0x144>
    14cc:	80 46       	mov55 $r2,$r6
    14ce:	8c c1       	addi45 $r6,#0x1
    14d0:	fa 10       	movpi45 $r0,#0x20
    14d2:	80 29       	mov55 $r1,$r9
    14d4:	80 6a       	mov55 $r3,$r10
    14d6:	dd 28       	jral5 $r8
    14d8:	40 43 34 01 	sub $r4,$r6,$r13
    14dc:	40 42 30 06 	slt $r4,$r4,$r12
    14e0:	80 46       	mov55 $r2,$r6
    14e2:	cc f6       	bnez38 $r4,14ce <_ntoa_format+0x12e>
    14e4:	80 06       	mov55 $r0,$r6
    14e6:	ec 04       	addi10.sp #0x4
    14e8:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    14ec:	dd 9e       	ret5 $lp
    14ee:	92 00       	nop16
    14f0:	cd 3d       	bnez38 $r5,156a <_ntoa_format+0x1ca>
    14f2:	c4 13       	beqz38 $r4,1518 <_ntoa_format+0x178>
    14f4:	fa 1d       	movpi45 $r0,#0x2d
    14f6:	54 f8 00 03 	andi $r15,$r16,#0x3
    14fa:	9d a9       	addi333 $r6,$r5,#0x1
    14fc:	38 03 94 08 	sb $r0,[$r7+($r5<<#0x0)]
    1500:	e8 ba       	beqzs8 1474 <_ntoa_format+0xd4>
    1502:	80 4d       	mov55 $r2,$r13
    1504:	d5 d0       	j8 14a4 <_ntoa_format+0x104>
    1506:	92 00       	nop16
    1508:	cc 4d       	bnez38 $r4,15a2 <_ntoa_format+0x202>
    150a:	54 08 00 0c 	andi $r0,$r16,#0xc
    150e:	c8 4a       	bnez38 $r0,15a2 <_ntoa_format+0x202>
    1510:	5c f3 00 20 	slti $r15,$r6,#0x20
    1514:	e8 f7       	beqzs8 1502 <_ntoa_format+0x162>
    1516:	80 ac       	mov55 $r5,$r12
    1518:	54 08 00 04 	andi $r0,$r16,#0x4
    151c:	c8 1e       	bnez38 $r0,1558 <_ntoa_format+0x1b8>
    151e:	54 08 00 08 	andi $r0,$r16,#0x8
    1522:	80 c5       	mov55 $r6,$r5
    1524:	c0 06       	beqz38 $r0,1530 <_ntoa_format+0x190>
    1526:	fa 10       	movpi45 $r0,#0x20
    1528:	8c c1       	addi45 $r6,#0x1
    152a:	38 03 94 08 	sb $r0,[$r7+($r5<<#0x0)]
    152e:	92 00       	nop16
    1530:	54 f8 00 03 	andi $r15,$r16,#0x3
    1534:	80 4d       	mov55 $r2,$r13
    1536:	e9 b5       	bnezs8 14a0 <_ntoa_format+0x100>
    1538:	d5 9e       	j8 1474 <_ntoa_format+0xd4>
    153a:	92 00       	nop16
    153c:	4e 52 ff 7c 	beqz $r5,1434 <_ntoa_format+0x94>
    1540:	d2 03       	beqs38 $r2,1546 <_ntoa_format+0x1a6>
    1542:	4c 56 7f 79 	bne $r5,$r12,1434 <_ntoa_format+0x94>
    1546:	9e 29       	subi333 $r0,$r5,#0x1
    1548:	c0 47       	beqz38 $r0,15d6 <_ntoa_format+0x236>
    154a:	f1 0d       	lwi37.sp $r1,[+#0x34]
    154c:	8e a2       	subi45 $r5,#0x2
    154e:	5a 10 10 1b 	beqc $r1,#0x10,1584 <_ntoa_format+0x1e4>
    1552:	80 a0       	mov55 $r5,$r0
    1554:	48 ff ff 76 	j 1440 <_ntoa_format+0xa0>
    1558:	fa 1b       	movpi45 $r0,#0x2b
    155a:	9d a9       	addi333 $r6,$r5,#0x1
    155c:	38 03 94 08 	sb $r0,[$r7+($r5<<#0x0)]
    1560:	d5 e8       	j8 1530 <_ntoa_format+0x190>
    1562:	92 00       	nop16
    1564:	5c f2 80 20 	slti $r15,$r5,#0x20
    1568:	e9 30       	bnezs8 15c8 <_ntoa_format+0x228>
    156a:	80 c5       	mov55 $r6,$r5
    156c:	48 ff ff 7a 	j 1460 <_ntoa_format+0xc0>
    1570:	54 08 00 10 	andi $r0,$r16,#0x10
    1574:	4e 02 ff 76 	beqz $r0,1460 <_ntoa_format+0xc0>
    1578:	54 08 04 00 	andi $r0,$r16,#0x400
    157c:	fa b0       	movpi45 $r5,#0x20
    157e:	c0 e1       	beqz38 $r0,1540 <_ntoa_format+0x1a0>
    1580:	48 ff ff 5a 	j 1434 <_ntoa_format+0x94>
    1584:	54 08 00 20 	andi $r0,$r16,#0x20
    1588:	c8 ee       	bnez38 $r0,1564 <_ntoa_format+0x1c4>
    158a:	5c f2 80 20 	slti $r15,$r5,#0x20
    158e:	80 c5       	mov55 $r6,$r5
    1590:	4e f2 ff 68 	beqz $r15,1460 <_ntoa_format+0xc0>
    1594:	44 00 00 78 	movi $r0,#0x78
    1598:	38 03 94 08 	sb $r0,[$r7+($r5<<#0x0)]
    159c:	8c a1       	addi45 $r5,#0x1
    159e:	48 ff ff 57 	j 144c <_ntoa_format+0xac>
    15a2:	8e c1       	subi45 $r6,#0x1
    15a4:	48 ff ff 60 	j 1464 <_ntoa_format+0xc4>
    15a8:	5c f2 80 20 	slti $r15,$r5,#0x20
    15ac:	80 c5       	mov55 $r6,$r5
    15ae:	4e f2 ff 59 	beqz $r15,1460 <_ntoa_format+0xc0>
    15b2:	44 00 00 62 	movi $r0,#0x62
    15b6:	38 03 94 08 	sb $r0,[$r7+($r5<<#0x0)]
    15ba:	8c a1       	addi45 $r5,#0x1
    15bc:	48 ff ff 48 	j 144c <_ntoa_format+0xac>
    15c0:	80 c2       	mov55 $r6,$r2
    15c2:	48 ff ff 7f 	j 14c0 <_ntoa_format+0x120>
    15c6:	92 00       	nop16
    15c8:	44 00 00 58 	movi $r0,#0x58
    15cc:	38 03 94 08 	sb $r0,[$r7+($r5<<#0x0)]
    15d0:	8c a1       	addi45 $r5,#0x1
    15d2:	48 ff ff 3d 	j 144c <_ntoa_format+0xac>
    15d6:	84 a0       	movi55 $r5,#0x0
    15d8:	48 ff ff 2e 	j 1434 <_ntoa_format+0x94>
    15dc:	54 08 00 10 	andi $r0,$r16,#0x10
    15e0:	4e 03 ff 26 	bnez $r0,142c <_ntoa_format+0x8c>
    15e4:	80 c5       	mov55 $r6,$r5
    15e6:	48 ff ff 3d 	j 1460 <_ntoa_format+0xc0>
    15ea:	80 a6       	mov55 $r5,$r6
    15ec:	c4 96       	beqz38 $r4,1518 <_ntoa_format+0x178>
    15ee:	d5 83       	j8 14f4 <_ntoa_format+0x154>

000015f0 <_ntoa_long>:
    15f0:	3b ff fc bc 	smw.adm $sp,[$sp],$sp,#0x2    ! {$lp}
    15f4:	ef c4       	addi10.sp #-60
    15f6:	05 3f 80 10 	lwi $r19,[$sp+#0x40]
    15fa:	05 7f 80 13 	lwi $r23,[$sp+#0x4c]
    15fe:	cc 07       	bnez38 $r4,160c <_ntoa_long+0x1c>
    1600:	54 fb 84 00 	andi $r15,$r23,#0x400
    1604:	67 7b 80 10 	bitci $r23,$r23,#0x10
    1608:	4e f3 00 3a 	bnez $r15,167c <_ntoa_long+0x8c>
    160c:	51 8f 80 18 	addi $r24,$sp,#0x18
    1610:	55 0b 80 20 	andi $r16,$r23,#0x20
    1614:	45 10 00 61 	movi $r17,#0x61
    1618:	45 60 00 41 	movi $r22,#0x41
    161c:	82 b8       	mov55 $r21,$r24
    161e:	86 80       	movi55 $r20,#0x0
    1620:	41 68 c0 1a 	cmovz $r22,$r17,$r16
    1624:	d5 04       	j8 162c <_ntoa_long+0x3c>
    1626:	92 00       	nop16
    1628:	5b 40 20 19 	beqc $r20,#0x20,165a <_ntoa_long+0x6a>
    162c:	41 12 4e 17 	divr $r17,$r16,$r4,$r19
    1630:	41 28 00 10 	seb $r18,$r16
    1634:	51 18 7f f6 	addi $r17,$r16,#-10
    1638:	e5 ca       	sltsi45 $r18,#0xa
    163a:	51 08 00 30 	addi $r16,$r16,#0x30
    163e:	89 b6       	add45 $r17,$r22
    1640:	51 4a 00 01 	addi $r20,$r20,#0x1
    1644:	41 08 00 10 	seb $r16,$r16
    1648:	4e f3 00 04 	bnez $r15,1650 <_ntoa_long+0x60>
    164c:	41 08 80 10 	seb $r16,$r17
    1650:	40 42 4c 97 	divr $r4,$r4,$r4,$r19
    1654:	19 0a 80 01 	sbi.bi $r16,[$r21],#0x1
    1658:	cc e8       	bnez38 $r4,1628 <_ntoa_long+0x38>
    165a:	f4 11       	lwi37.sp $r4,[+#0x44]
    165c:	f4 82       	swi37.sp $r4,[+#0x8]
    165e:	f4 12       	lwi37.sp $r4,[+#0x48]
    1660:	b6 bf       	swi450 $r5,[$sp]
    1662:	f4 83       	swi37.sp $r4,[+#0xc]
    1664:	15 3f 80 01 	swi $r19,[$sp+#0x4]
    1668:	15 7f 80 04 	swi $r23,[$sp+#0x10]
    166c:	80 98       	mov55 $r4,$r24
    166e:	80 b4       	mov55 $r5,$r20
    1670:	49 ff fe 98 	jal 13a0 <_ntoa_format>
    1674:	ec 3c       	addi10.sp #0x3c
    1676:	3b ff fc 84 	lmw.bim $sp,[$sp],$sp,#0x2    ! {$lp}
    167a:	dd 9e       	ret5 $lp
    167c:	86 80       	movi55 $r20,#0x0
    167e:	51 8f 80 18 	addi $r24,$sp,#0x18
    1682:	d5 ec       	j8 165a <_ntoa_long+0x6a>

00001684 <_ntoa_long_long>:
    1684:	3a 6f ba bc 	smw.adm $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    1688:	ef b4       	addi10.sp #-76
    168a:	36 3f 80 0e 	fsdi $fd3,[$sp+#0x38]
    168e:	36 4f 80 10 	fsdi $fd4,[$sp+#0x40]
    1692:	fd 52       	movd44 $r10,$r4
    1694:	80 a4       	mov55 $r5,$r4
    1696:	80 8b       	mov55 $r4,$r11
    1698:	ff 2f       	or33 $r4,$r5
    169a:	6a 04 00 09 	fmtsr $r0,$fs8
    169e:	6a 13 80 09 	fmtsr $r1,$fs7
    16a2:	6a 23 00 09 	fmtsr $r2,$fs6
    16a6:	83 83       	mov55 $fp,$r3
    16a8:	f6 20       	lwi37.sp $r6,[+#0x80]
    16aa:	f7 21       	lwi37.sp $r7,[+#0x84]
    16ac:	04 8f 80 24 	lwi $r8,[$sp+#0x90]
    16b0:	cc 06       	bnez38 $r4,16bc <_ntoa_long_long+0x38>
    16b2:	54 04 04 00 	andi $r0,$r8,#0x400
    16b6:	66 84 00 10 	bitci $r8,$r8,#0x10
    16ba:	c8 4d       	bnez38 $r0,1754 <_ntoa_long_long+0xd0>
    16bc:	50 ef 80 18 	addi $r14,$sp,#0x18
    16c0:	54 54 00 20 	andi $r5,$r8,#0x20
    16c4:	44 00 00 61 	movi $r0,#0x61
    16c8:	44 d0 00 41 	movi $r13,#0x41
    16cc:	81 8e       	mov55 $r12,$r14
    16ce:	85 20       	movi55 $r9,#0x0
    16d0:	40 d0 14 1a 	cmovz $r13,$r0,$r5
    16d4:	d5 04       	j8 16dc <_ntoa_long_long+0x58>
    16d6:	92 00       	nop16
    16d8:	5a 90 20 20 	beqc $r9,#0x20,1718 <_ntoa_long_long+0x94>
    16dc:	fd 05       	movd44 $r0,$r10
    16de:	fd 13       	movd44 $r2,$r6
    16e0:	49 00 3b 18 	jal 8d10 <__umoddi3>
    16e4:	41 20 00 10 	seb $r18,$r0
    16e8:	51 10 7f f6 	addi $r17,$r0,#-10
    16ec:	51 00 00 30 	addi $r16,$r0,#0x30
    16f0:	5e 09 00 0a 	sltsi $r0,$r18,#0xa
    16f4:	89 ad       	add45 $r17,$r13
    16f6:	8d 21       	addi45 $r9,#0x1
    16f8:	41 08 00 10 	seb $r16,$r16
    16fc:	c8 03       	bnez38 $r0,1702 <_ntoa_long_long+0x7e>
    16fe:	41 08 80 10 	seb $r16,$r17
    1702:	fd 05       	movd44 $r0,$r10
    1704:	19 06 00 01 	sbi.bi $r16,[$r12],#0x1
    1708:	fd 13       	movd44 $r2,$r6
    170a:	49 00 3a 29 	jal 8b5c <__udivdi3>
    170e:	fd 50       	movd44 $r10,$r0
    1710:	40 00 2c 04 	or $r0,$r0,$r11
    1714:	c8 e2       	bnez38 $r0,16d8 <_ntoa_long_long+0x54>
    1716:	92 00       	nop16
    1718:	00 0f 80 78 	lbi $r0,[$sp+#0x78]
    171c:	b6 1f       	swi450 $r0,[$sp]
    171e:	f0 22       	lwi37.sp $r0,[+#0x88]
    1720:	f0 82       	swi37.sp $r0,[+#0x8]
    1722:	f0 23       	lwi37.sp $r0,[+#0x8c]
    1724:	f0 83       	swi37.sp $r0,[+#0xc]
    1726:	6a 13 80 01 	fmfsr $r1,$fs7
    172a:	6a 04 00 01 	fmfsr $r0,$fs8
    172e:	6a 23 00 01 	fmfsr $r2,$fs6
    1732:	f6 81       	swi37.sp $r6,[+#0x4]
    1734:	14 8f 80 04 	swi $r8,[$sp+#0x10]
    1738:	80 7c       	mov55 $r3,$fp
    173a:	80 8e       	mov55 $r4,$r14
    173c:	50 54 80 00 	addi $r5,$r9,#0x0
    1740:	49 ff fe 30 	jal 13a0 <_ntoa_format>
    1744:	ec 38       	addi10.sp #0x38
    1746:	34 3f 90 02 	fldi.bi $fd3,[$sp],#0x8
    174a:	34 4f 90 03 	fldi.bi $fd4,[$sp],#0xc
    174e:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    1752:	dd 9e       	ret5 $lp
    1754:	85 20       	movi55 $r9,#0x0
    1756:	50 ef 80 18 	addi $r14,$sp,#0x18
    175a:	d5 df       	j8 1718 <_ntoa_long_long+0x94>

0000175c <_out_char>:
    175c:	c0 0c       	beqz38 $r0,1774 <_out_char+0x18>
    175e:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    1762:	80 c0       	mov55 $r6,$r0
    1764:	5a 00 0a 09 	beqc $r0,#0xa,1776 <_out_char+0x1a>
    1768:	80 06       	mov55 $r0,$r6
    176a:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    176e:	48 ff fb 7b 	j e64 <drv_uart_tx_0>
    1772:	92 00       	nop16
    1774:	dd 9e       	ret5 $lp
    1776:	84 0d       	movi55 $r0,#0xd
    1778:	49 ff fb 76 	jal e64 <drv_uart_tx_0>
    177c:	d5 f6       	j8 1768 <_out_char+0xc>
    177e:	92 00       	nop16

00001780 <_vsnprintf>:
    1780:	3a 6f ba bc 	smw.adm $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    1784:	ef 5c       	addi10.sp #-164
    1786:	36 3f 80 1a 	fsdi $fd3,[$sp+#0x68]
    178a:	36 4f 80 1c 	fsdi $fd4,[$sp+#0x70]
    178e:	36 5f 80 1e 	fsdi $fd5,[$sp+#0x78]
    1792:	36 6f 80 20 	fsdi $fd6,[$sp+#0x80]
    1796:	36 7f 80 22 	fsdi $fd7,[$sp+#0x88]
    179a:	36 8f 80 24 	fsdi $fd8,[$sp+#0x90]
    179e:	36 9f 80 26 	fsdi $fd9,[$sp+#0x98]
    17a2:	44 70 13 9c 	movi $r7,#0x139c
    17a6:	40 70 04 1b 	cmovn $r7,$r0,$r1
    17aa:	46 06 66 66 	sethi $r0,#0x66666
    17ae:	50 00 06 67 	addi $r0,$r0,#0x667
    17b2:	6a 08 00 09 	fmtsr $r0,$fs16
    17b6:	46 0c cc cc 	sethi $r0,#0xccccc
    17ba:	50 00 0c cd 	addi $r0,$r0,#0xccd
    17be:	6a 03 80 09 	fmtsr $r0,$fs7
    17c2:	81 c1       	mov55 $r14,$r1
    17c4:	80 c2       	mov55 $r6,$r2
    17c6:	81 a3       	mov55 $r13,$r3
    17c8:	83 84       	mov55 $fp,$r4
    17ca:	85 40       	movi55 $r10,#0x0
    17cc:	20 06 80 00 	lbsi $r0,[$r13+#0x0]
    17d0:	4e 02 00 10 	beqz $r0,17f0 <_vsnprintf+0x70>
    17d4:	5a 00 25 2a 	beqc $r0,#0x25,1828 <_vsnprintf+0xa8>
    17d8:	80 4a       	mov55 $r2,$r10
    17da:	80 2e       	mov55 $r1,$r14
    17dc:	80 66       	mov55 $r3,$r6
    17de:	50 d6 80 01 	addi $r13,$r13,#0x1
    17e2:	dd 27       	jral5 $r7
    17e4:	20 06 80 00 	lbsi $r0,[$r13+#0x0]
    17e8:	50 85 00 01 	addi $r8,$r10,#0x1
    17ec:	81 48       	mov55 $r10,$r8
    17ee:	c8 f3       	bnez38 $r0,17d4 <_vsnprintf+0x54>
    17f0:	e3 46       	slt45 $r10,$r6
    17f2:	9e b1       	subi333 $r2,$r6,#0x1
    17f4:	40 25 3c 1b 	cmovn $r2,$r10,$r15
    17f8:	84 00       	movi55 $r0,#0x0
    17fa:	80 2e       	mov55 $r1,$r14
    17fc:	80 66       	mov55 $r3,$r6
    17fe:	dd 27       	jral5 $r7
    1800:	80 0a       	mov55 $r0,$r10
    1802:	ec 68       	addi10.sp #0x68
    1804:	34 3f 90 02 	fldi.bi $fd3,[$sp],#0x8
    1808:	34 4f 90 02 	fldi.bi $fd4,[$sp],#0x8
    180c:	34 5f 90 02 	fldi.bi $fd5,[$sp],#0x8
    1810:	34 6f 90 02 	fldi.bi $fd6,[$sp],#0x8
    1814:	34 7f 90 02 	fldi.bi $fd7,[$sp],#0x8
    1818:	34 8f 90 02 	fldi.bi $fd8,[$sp],#0x8
    181c:	34 9f 90 03 	fldi.bi $fd9,[$sp],#0xc
    1820:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    1824:	dd 9e       	ret5 $lp
    1826:	92 00       	nop16
    1828:	50 16 80 01 	addi $r1,$r13,#0x1
    182c:	85 a0       	movi55 $r13,#0x0
    182e:	81 01       	mov55 $r8,$r1
    1830:	28 20 80 01 	lbsi.bi $r2,[$r1],#0x1
    1834:	50 31 7f e0 	addi $r3,$r2,#-32
    1838:	5c f1 80 11 	slti $r15,$r3,#0x11
    183c:	4e f3 01 3c 	bnez $r15,1ab4 <_vsnprintf+0x334>
    1840:	50 01 7f d0 	addi $r0,$r2,#-48
    1844:	96 00       	zeb33 $r0,$r0
    1846:	e6 0a       	slti45 $r0,#0xa
    1848:	80 68       	mov55 $r3,$r8
    184a:	80 02       	mov55 $r0,$r2
    184c:	4e f2 01 70 	beqz $r15,1b2c <_vsnprintf+0x3ac>
    1850:	50 24 00 01 	addi $r2,$r8,#0x1
    1854:	85 20       	movi55 $r9,#0x0
    1856:	84 aa       	movi55 $r5,#0xa
    1858:	42 04 94 73 	maddr32 $r0,$r9,$r5
    185c:	81 02       	mov55 $r8,$r2
    185e:	80 60       	mov55 $r3,$r0
    1860:	20 01 00 00 	lbsi $r0,[$r2+#0x0]
    1864:	50 91 ff d0 	addi $r9,$r3,#-48
    1868:	50 10 7f d0 	addi $r1,$r0,#-48
    186c:	96 48       	zeb33 $r1,$r1
    186e:	e6 2a       	slti45 $r1,#0xa
    1870:	8c 41       	addi45 $r2,#0x1
    1872:	e9 f3       	bnezs8 1858 <_vsnprintf+0xd8>
    1874:	44 b0 00 00 	movi $r11,#0x0
    1878:	5a 08 2e 04 	bnec $r0,#0x2e,1880 <_vsnprintf+0x100>
    187c:	48 00 01 64 	j 1b44 <_vsnprintf+0x3c4>
    1880:	50 10 7f 98 	addi $r1,$r0,#-104
    1884:	e6 33       	slti45 $r1,#0x13
    1886:	e8 33       	beqzs8 18ec <_vsnprintf+0x16c>
    1888:	44 f0 18 94 	movi $r15,#0x1894
    188c:	38 17 86 02 	lw $r1,[$r15+($r1<<#0x2)]
    1890:	4a 00 04 00 	jr $r1
    1894:	80 1a       	mov55 $r0,$p0
    1896:	00 00 ec 18 	lbi $r0,[$r1+#-5096]
    189a:	00 00 10 19 	lbi $r0,[$r0+#0x1019]
    189e:	00 00 ec 18 	lbi $r0,[$r1+#-5096]
    18a2:	00 00 98 1a 	lbi $r0,[$r1+#0x181a]
    18a6:	00 00 ec 18 	lbi $r0,[$r1+#-5096]
    18aa:	00 00 ec 18 	lbi $r0,[$r1+#-5096]
    18ae:	00 00 ec 18 	lbi $r0,[$r1+#-5096]
    18b2:	00 00 ec 18 	lbi $r0,[$r1+#-5096]
    18b6:	00 00 ec 18 	lbi $r0,[$r1+#-5096]
    18ba:	00 00 ec 18 	lbi $r0,[$r1+#-5096]
    18be:	00 00 ec 18 	lbi $r0,[$r1+#-5096]
    18c2:	00 00 e0 18 	lbi $r0,[$r1+#-8168]
    18c6:	00 00 ec 18 	lbi $r0,[$r1+#-5096]
    18ca:	00 00 ec 18 	lbi $r0,[$r1+#-5096]
    18ce:	00 00 ec 18 	lbi $r0,[$r1+#-5096]
    18d2:	00 00 ec 18 	lbi $r0,[$r1+#-5096]
    18d6:	00 00 ec 18 	lbi $r0,[$r1+#-5096]
    18da:	00 00 e0 18 	lbi $r0,[$r1+#-8168]
    18de:	00 00 20 04 	lbi $r0,[$r0+#0x2004]
    18e2:	00 01 58 d6 	lbi $r0,[$r2+#-10026]
    18e6:	81 00       	mov55 $r8,$r0
    18e8:	8d 01       	addi45 $r8,#0x1
    18ea:	92 00       	nop16
    18ec:	50 10 7f db 	addi $r1,$r0,#-37
    18f0:	5c f0 80 54 	slti $r15,$r1,#0x54
    18f4:	e9 18       	bnezs8 1924 <_vsnprintf+0x1a4>
    18f6:	80 4a       	mov55 $r2,$r10
    18f8:	50 95 00 01 	addi $r9,$r10,#0x1
    18fc:	80 2e       	mov55 $r1,$r14
    18fe:	80 66       	mov55 $r3,$r6
    1900:	4b e0 1c 01 	jral $lp,$r7
    1904:	50 d4 00 01 	addi $r13,$r8,#0x1
    1908:	81 49       	mov55 $r10,$r9
    190a:	48 ff ff 61 	j 17cc <_vsnprintf+0x4c>
    190e:	92 00       	nop16
    1910:	20 04 00 01 	lbsi $r0,[$r8+#0x1]
    1914:	58 d6 82 00 	ori $r13,$r13,#0x200
    1918:	50 10 7f db 	addi $r1,$r0,#-37
    191c:	5c f0 80 54 	slti $r15,$r1,#0x54
    1920:	8d 01       	addi45 $r8,#0x1
    1922:	e8 ea       	beqzs8 18f6 <_vsnprintf+0x176>
    1924:	44 f0 19 30 	movi $r15,#0x1930
    1928:	38 17 86 02 	lw $r1,[$r15+($r1<<#0x2)]
    192c:	4a 00 04 00 	jr $r1
    1930:	b4 1d       	lwi450 $r0,[$gp]
    1932:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    1936:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    193a:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    193e:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    1942:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    1946:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    194a:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    194e:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    1952:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    1956:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    195a:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    195e:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    1962:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    1966:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    196a:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    196e:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    1972:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    1976:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    197a:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    197e:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    1982:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    1986:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    198a:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    198e:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    1992:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    1996:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    199a:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    199e:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    19a2:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    19a6:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    19aa:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    19ae:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    19b2:	00 00 48 1d 	lbi $r0,[$r0+#-14307]
    19b6:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    19ba:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    19be:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    19c2:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    19c6:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    19ca:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    19ce:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    19d2:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    19d6:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    19da:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    19de:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    19e2:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    19e6:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    19ea:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    19ee:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    19f2:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    19f6:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    19fa:	00 00 cc 1c 	lbi $r0,[$r1+#-13284]
    19fe:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    1a02:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    1a06:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    1a0a:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    1a0e:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    1a12:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    1a16:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    1a1a:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    1a1e:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    1a22:	00 00 cc 1c 	lbi $r0,[$r1+#-13284]
    1a26:	00 00 8c 1c 	lbi $r0,[$r1+#0xc1c]
    1a2a:	00 00 cc 1c 	lbi $r0,[$r1+#-13284]
    1a2e:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    1a32:	00 00 48 1d 	lbi $r0,[$r0+#-14307]
    1a36:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    1a3a:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    1a3e:	00 00 cc 1c 	lbi $r0,[$r1+#-13284]
    1a42:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    1a46:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    1a4a:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    1a4e:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    1a52:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    1a56:	00 00 cc 1c 	lbi $r0,[$r1+#-13284]
    1a5a:	00 00 5c 1c 	lbi $r0,[$r0+#-9188]
    1a5e:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    1a62:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    1a66:	00 00 84 1b 	lbi $r0,[$r1+#0x41b]
    1a6a:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    1a6e:	00 00 cc 1c 	lbi $r0,[$r1+#-13284]
    1a72:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    1a76:	00 00 f6 18 	lbi $r0,[$r1+#-2536]
    1a7a:	00 00 cc 1c 	lbi $r0,[$r1+#-13284]
    1a7e:	00 00 20 04 	lbi $r0,[$r0+#0x2004]
    1a82:	00 01 5a 08 	lbi $r0,[$r2+#-9720]
    1a86:	68 04 48 00 	*unknown*
    1a8a:	03 16 58 d6 	lhi $r17,[$r12+#-20052]
    1a8e:	80 80       	mov55 $r4,$r0
    1a90:	8d 01       	addi45 $r8,#0x1
    1a92:	48 ff ff 2d 	j 18ec <_vsnprintf+0x16c>
    1a96:	92 00       	nop16
    1a98:	20 04 00 01 	lbsi $r0,[$r8+#0x1]
    1a9c:	5a 00 6c 04 	beqc $r0,#0x6c,1aa4 <_vsnprintf+0x324>
    1aa0:	48 ff ff 22 	j 18e4 <_vsnprintf+0x164>
    1aa4:	20 04 00 02 	lbsi $r0,[$r8+#0x2]
    1aa8:	58 d6 83 00 	ori $r13,$r13,#0x300
    1aac:	8d 02       	addi45 $r8,#0x2
    1aae:	48 ff ff 1f 	j 18ec <_vsnprintf+0x16c>
    1ab2:	92 00       	nop16
    1ab4:	44 f0 1a c0 	movi $r15,#0x1ac0
    1ab8:	38 37 8e 02 	lw $r3,[$r15+($r3<<#0x2)]
    1abc:	4a 00 0c 00 	jr $r3
    1ac0:	24 1b 00 00 	*unknown*
    1ac4:	40 18 00 00 	add $r1,$r16,$r0
    1ac8:	40 18 00 00 	add $r1,$r16,$r0
    1acc:	1c 1b 00 00 	swi.bi $r1,[$r22],#0x0
    1ad0:	40 18 00 00 	add $r1,$r16,$r0
    1ad4:	40 18 00 00 	add $r1,$r16,$r0
    1ad8:	40 18 00 00 	add $r1,$r16,$r0
    1adc:	40 18 00 00 	add $r1,$r16,$r0
    1ae0:	40 18 00 00 	add $r1,$r16,$r0
    1ae4:	40 18 00 00 	add $r1,$r16,$r0
    1ae8:	40 18 00 00 	add $r1,$r16,$r0
    1aec:	14 1b 00 00 	swi $r1,[$r22+#0x0]
    1af0:	40 18 00 00 	add $r1,$r16,$r0
    1af4:	0c 1b 00 00 	lwi.bi $r1,[$r22],#0x0
    1af8:	40 18 00 00 	add $r1,$r16,$r0
    1afc:	40 18 00 00 	add $r1,$r16,$r0
    1b00:	04 1b 00 00 	lwi $r1,[$r22+#0x0]
    1b04:	58 d6 80 01 	ori $r13,$r13,#0x1
    1b08:	48 ff fe 93 	j 182e <_vsnprintf+0xae>
    1b0c:	58 d6 80 02 	ori $r13,$r13,#0x2
    1b10:	48 ff fe 8f 	j 182e <_vsnprintf+0xae>
    1b14:	58 d6 80 04 	ori $r13,$r13,#0x4
    1b18:	48 ff fe 8b 	j 182e <_vsnprintf+0xae>
    1b1c:	58 d6 80 10 	ori $r13,$r13,#0x10
    1b20:	48 ff fe 87 	j 182e <_vsnprintf+0xae>
    1b24:	58 d6 80 08 	ori $r13,$r13,#0x8
    1b28:	48 ff fe 83 	j 182e <_vsnprintf+0xae>
    1b2c:	5a 28 2a 04 	bnec $r2,#0x2a,1b34 <_vsnprintf+0x3b4>
    1b30:	48 00 01 48 	j 1dc0 <_vsnprintf+0x640>
    1b34:	80 02       	mov55 $r0,$r2
    1b36:	85 20       	movi55 $r9,#0x0
    1b38:	44 b0 00 00 	movi $r11,#0x0
    1b3c:	5a 20 2e 04 	beqc $r2,#0x2e,1b44 <_vsnprintf+0x3c4>
    1b40:	48 ff fe a0 	j 1880 <_vsnprintf+0x100>
    1b44:	20 04 00 01 	lbsi $r0,[$r8+#0x1]
    1b48:	58 d6 84 00 	ori $r13,$r13,#0x400
    1b4c:	50 10 7f d0 	addi $r1,$r0,#-48
    1b50:	96 48       	zeb33 $r1,$r1
    1b52:	e6 2a       	slti45 $r1,#0xa
    1b54:	50 24 00 01 	addi $r2,$r8,#0x1
    1b58:	4e f2 01 3e 	beqz $r15,1dd4 <_vsnprintf+0x654>
    1b5c:	50 24 00 02 	addi $r2,$r8,#0x2
    1b60:	84 6a       	movi55 $r3,#0xa
    1b62:	92 00       	nop16
    1b64:	42 05 8c 73 	maddr32 $r0,$r11,$r3
    1b68:	81 02       	mov55 $r8,$r2
    1b6a:	82 20       	mov55 $r17,$r0
    1b6c:	20 01 00 00 	lbsi $r0,[$r2+#0x0]
    1b70:	50 b8 ff d0 	addi $r11,$r17,#-48
    1b74:	50 10 7f d0 	addi $r1,$r0,#-48
    1b78:	96 48       	zeb33 $r1,$r1
    1b7a:	e6 2a       	slti45 $r1,#0xa
    1b7c:	8c 41       	addi45 $r2,#0x1
    1b7e:	e9 f3       	bnezs8 1b64 <_vsnprintf+0x3e4>
    1b80:	48 ff fe 80 	j 1880 <_vsnprintf+0x100>
    1b84:	30 8e 00 00 	flsi $fs8,[$fp+#0x0]
    1b88:	50 0e 00 04 	addi $r0,$fp,#0x4
    1b8c:	6a 04 80 09 	fmtsr $r0,$fs9
    1b90:	6a 04 00 01 	fmfsr $r0,$fs8
    1b94:	20 00 00 00 	lbsi $r0,[$r0+#0x0]
    1b98:	4e 02 04 0f 	beqz $r0,23b6 <_vsnprintf+0xc36>
    1b9c:	6a 14 00 01 	fmfsr $r1,$fs8
    1ba0:	8c 21       	addi45 $r1,#0x1
    1ba2:	92 00       	nop16
    1ba4:	20 30 80 00 	lbsi $r3,[$r1+#0x0]
    1ba8:	80 41       	mov55 $r2,$r1
    1baa:	8c 21       	addi45 $r1,#0x1
    1bac:	cb fc       	bnez38 $r3,1ba4 <_vsnprintf+0x424>
    1bae:	6a 14 00 01 	fmfsr $r1,$fs8
    1bb2:	9a 51       	sub333 $r1,$r2,$r1
    1bb4:	6a 15 00 09 	fmtsr $r1,$fs10
    1bb8:	54 c6 84 00 	andi $r12,$r13,#0x400
    1bbc:	4e c2 00 0c 	beqz $r12,1bd4 <_vsnprintf+0x454>
    1bc0:	6a 15 00 01 	fmfsr $r1,$fs10
    1bc4:	6a 25 00 01 	fmfsr $r2,$fs10
    1bc8:	e3 61       	slt45 $r11,$r1
    1bca:	40 25 bc 1b 	cmovn $r2,$r11,$r15
    1bce:	6a 25 00 09 	fmtsr $r2,$fs10
    1bd2:	92 00       	nop16
    1bd4:	54 16 80 02 	andi $r1,$r13,#0x2
    1bd8:	6a 13 00 09 	fmtsr $r1,$fs6
    1bdc:	4e 12 01 22 	beqz $r1,1e20 <_vsnprintf+0x6a0>
    1be0:	c0 1c       	beqz38 $r0,1c18 <_vsnprintf+0x498>
    1be2:	92 00       	nop16
    1be4:	6a 14 00 01 	fmfsr $r1,$fs8
    1be8:	80 4a       	mov55 $r2,$r10
    1bea:	51 c0 80 01 	addi $fp,$r1,#0x1
    1bee:	d5 02       	j8 1bf2 <_vsnprintf+0x472>
    1bf0:	80 4a       	mov55 $r2,$r10
    1bf2:	80 2e       	mov55 $r1,$r14
    1bf4:	80 66       	mov55 $r3,$r6
    1bf6:	4e c2 00 07 	beqz $r12,1c04 <_vsnprintf+0x484>
    1bfa:	50 45 ff ff 	addi $r4,$r11,#-1
    1bfe:	4e b2 00 09 	beqz $r11,1c10 <_vsnprintf+0x490>
    1c02:	81 64       	mov55 $r11,$r4
    1c04:	4b e0 1c 01 	jral $lp,$r7
    1c08:	28 0e 00 01 	lbsi.bi $r0,[$fp],#0x1
    1c0c:	8d 41       	addi45 $r10,#0x1
    1c0e:	c8 f1       	bnez38 $r0,1bf0 <_vsnprintf+0x470>
    1c10:	6a 03 00 01 	fmfsr $r0,$fs6
    1c14:	4e 02 00 1e 	beqz $r0,1c50 <_vsnprintf+0x4d0>
    1c18:	6a 05 00 01 	fmfsr $r0,$fs10
    1c1c:	e2 09       	slt45 $r0,$r9
    1c1e:	e8 19       	beqzs8 1c50 <_vsnprintf+0x4d0>
    1c20:	6a 05 00 01 	fmfsr $r0,$fs10
    1c24:	80 4a       	mov55 $r2,$r10
    1c26:	41 c0 28 01 	sub $fp,$r0,$r10
    1c2a:	92 00       	nop16
    1c2c:	50 b1 00 01 	addi $r11,$r2,#0x1
    1c30:	fa 10       	movpi45 $r0,#0x20
    1c32:	80 2e       	mov55 $r1,$r14
    1c34:	80 66       	mov55 $r3,$r6
    1c36:	dd 27       	jral5 $r7
    1c38:	40 0e 2c 00 	add $r0,$fp,$r11
    1c3c:	40 00 24 06 	slt $r0,$r0,$r9
    1c40:	80 4b       	mov55 $r2,$r11
    1c42:	c8 f5       	bnez38 $r0,1c2c <_vsnprintf+0x4ac>
    1c44:	6a 15 00 01 	fmfsr $r1,$fs10
    1c48:	40 05 24 00 	add $r0,$r10,$r9
    1c4c:	40 a0 04 01 	sub $r10,$r0,$r1
    1c50:	50 d4 00 01 	addi $r13,$r8,#0x1
    1c54:	6b c4 80 01 	fmfsr $fp,$fs9
    1c58:	48 ff fd ba 	j 17cc <_vsnprintf+0x4c>
    1c5c:	fa 00       	movpi45 $r0,#0x10
    1c5e:	58 46 80 21 	ori $r4,$r13,#0x21
    1c62:	b6 1f       	swi450 $r0,[$sp]
    1c64:	84 08       	movi55 $r0,#0x8
    1c66:	14 bf 80 01 	swi $r11,[$sp+#0x4]
    1c6a:	f0 82       	swi37.sp $r0,[+#0x8]
    1c6c:	f4 83       	swi37.sp $r4,[+#0xc]
    1c6e:	b4 9c       	lwi450 $r4,[$fp]
    1c70:	51 ce 00 04 	addi $fp,$fp,#0x4
    1c74:	80 4a       	mov55 $r2,$r10
    1c76:	80 07       	mov55 $r0,$r7
    1c78:	80 2e       	mov55 $r1,$r14
    1c7a:	80 66       	mov55 $r3,$r6
    1c7c:	84 a0       	movi55 $r5,#0x0
    1c7e:	49 ff fc b9 	jal 15f0 <_ntoa_long>
    1c82:	81 40       	mov55 $r10,$r0
    1c84:	50 d4 00 01 	addi $r13,$r8,#0x1
    1c88:	48 ff fd a2 	j 17cc <_vsnprintf+0x4c>
    1c8c:	54 46 80 02 	andi $r4,$r13,#0x2
    1c90:	4e 43 00 aa 	bnez $r4,1de4 <_vsnprintf+0x664>
    1c94:	e7 22       	slti45 $r9,#0x2
    1c96:	4e f3 03 cb 	bnez $r15,242c <_vsnprintf+0xcac>
    1c9a:	50 05 7f ff 	addi $r0,$r10,#-1
    1c9e:	89 20       	add45 $r9,$r0
    1ca0:	50 45 00 01 	addi $r4,$r10,#0x1
    1ca4:	80 4a       	mov55 $r2,$r10
    1ca6:	fa 10       	movpi45 $r0,#0x20
    1ca8:	81 44       	mov55 $r10,$r4
    1caa:	80 2e       	mov55 $r1,$r14
    1cac:	80 66       	mov55 $r3,$r6
    1cae:	dd 27       	jral5 $r7
    1cb0:	4c a4 ff f8 	bne $r10,$r9,1ca0 <_vsnprintf+0x520>
    1cb4:	20 0e 00 00 	lbsi $r0,[$fp+#0x0]
    1cb8:	80 2e       	mov55 $r1,$r14
    1cba:	80 49       	mov55 $r2,$r9
    1cbc:	80 66       	mov55 $r3,$r6
    1cbe:	51 ce 00 04 	addi $fp,$fp,#0x4
    1cc2:	50 a4 80 01 	addi $r10,$r9,#0x1
    1cc6:	dd 27       	jral5 $r7
    1cc8:	d5 de       	j8 1c84 <_vsnprintf+0x504>
    1cca:	92 00       	nop16
    1ccc:	5a 08 78 04 	bnec $r0,#0x78,1cd4 <_vsnprintf+0x554>
    1cd0:	48 00 02 56 	j 217c <_vsnprintf+0x9fc>
    1cd4:	5a 08 58 04 	bnec $r0,#0x58,1cdc <_vsnprintf+0x55c>
    1cd8:	48 00 02 8a 	j 21ec <_vsnprintf+0xa6c>
    1cdc:	5a 08 6f 04 	bnec $r0,#0x6f,1ce4 <_vsnprintf+0x564>
    1ce0:	48 00 03 27 	j 232e <_vsnprintf+0xbae>
    1ce4:	5a 08 62 04 	bnec $r0,#0x62,1cec <_vsnprintf+0x56c>
    1ce8:	48 00 02 ad 	j 2242 <_vsnprintf+0xac2>
    1cec:	66 16 80 10 	bitci $r1,$r13,#0x10
    1cf0:	44 20 00 0a 	movi $r2,#0xa
    1cf4:	5a 00 69 04 	beqc $r0,#0x69,1cfc <_vsnprintf+0x57c>
    1cf8:	48 00 02 69 	j 21ca <_vsnprintf+0xa4a>
    1cfc:	54 46 84 00 	andi $r4,$r13,#0x400
    1d00:	4e 43 02 6c 	bnez $r4,21d8 <_vsnprintf+0xa58>
    1d04:	54 00 82 00 	andi $r0,$r1,#0x200
    1d08:	4e 03 03 16 	bnez $r0,2334 <_vsnprintf+0xbb4>
    1d0c:	54 00 81 00 	andi $r0,$r1,#0x100
    1d10:	4e 03 02 94 	bnez $r0,2238 <_vsnprintf+0xab8>
    1d14:	54 00 80 40 	andi $r0,$r1,#0x40
    1d18:	4e 02 02 8c 	beqz $r0,2230 <_vsnprintf+0xab0>
    1d1c:	20 5e 00 00 	lbsi $r5,[$fp+#0x0]
    1d20:	51 ce 00 04 	addi $fp,$fp,#0x4
    1d24:	b6 5f       	swi450 $r2,[$sp]
    1d26:	f1 83       	swi37.sp $r1,[+#0xc]
    1d28:	80 4a       	mov55 $r2,$r10
    1d2a:	42 42 80 03 	abs $r4,$r5
    1d2e:	14 bf 80 01 	swi $r11,[$sp+#0x4]
    1d32:	14 9f 80 02 	swi $r9,[$sp+#0x8]
    1d36:	80 07       	mov55 $r0,$r7
    1d38:	80 2e       	mov55 $r1,$r14
    1d3a:	80 66       	mov55 $r3,$r6
    1d3c:	92 bf       	srli45 $r5,#0x1f
    1d3e:	49 ff fc 59 	jal 15f0 <_ntoa_long>
    1d42:	81 40       	mov55 $r10,$r0
    1d44:	d5 a0       	j8 1c84 <_vsnprintf+0x504>
    1d46:	92 00       	nop16
    1d48:	51 ce 00 07 	addi $fp,$fp,#0x7
    1d4c:	67 ce 00 07 	bitci $fp,$fp,#0x7
    1d50:	44 00 24 b0 	movi $r0,#0x24b0
    1d54:	34 4e 00 00 	fldi $fd4,[$fp+#0x0]
    1d58:	34 50 00 00 	fldi $fd5,[$r0+#0x0]
    1d5c:	51 ce 00 08 	addi $fp,$fp,#0x8
    1d60:	6a 02 10 c8 	fcpysd $fd0,$fd4,$fd4
    1d64:	6a 12 94 c8 	fcpysd $fd1,$fd5,$fd5
    1d68:	49 00 38 db 	jal 8f1e <__ledf2>
    1d6c:	4e 05 02 82 	bltz $r0,2270 <_vsnprintf+0xaf0>
    1d70:	84 00       	movi55 $r0,#0x0
    1d72:	6a 09 00 09 	fmtsr $r0,$fs18
    1d76:	92 00       	nop16
    1d78:	54 06 84 00 	andi $r0,$r13,#0x400
    1d7c:	4e 02 00 7e 	beqz $r0,1e78 <_vsnprintf+0x6f8>
    1d80:	e7 6a       	slti45 $r11,#0xa
    1d82:	4e f3 03 58 	bnez $r15,2432 <_vsnprintf+0xcb2>
    1d86:	44 00 00 30 	movi $r0,#0x30
    1d8a:	10 0f 80 48 	sbi $r0,[$sp+#0x48]
    1d8e:	50 15 ff ff 	addi $r1,$r11,#-1
    1d92:	50 2f 80 49 	addi $r2,$sp,#0x49
    1d96:	8f 69       	subi45 $r11,#0x9
    1d98:	84 01       	movi55 $r0,#0x1
    1d9a:	44 30 00 30 	movi $r3,#0x30
    1d9e:	92 00       	nop16
    1da0:	4c 05 80 6e 	beq $r0,$r11,1e7c <_vsnprintf+0x6fc>
    1da4:	8c 01       	addi45 $r0,#0x1
    1da6:	18 31 00 01 	sbi.bi $r3,[$r2],#0x1
    1daa:	8e 21       	subi45 $r1,#0x1
    1dac:	5a 08 20 fa 	bnec $r0,#0x20,1da0 <_vsnprintf+0x620>
    1db0:	fb 70       	movpi45 $r11,#0x20
    1db2:	d5 65       	j8 1e7c <_vsnprintf+0x6fc>
    1db4:	80 4a       	mov55 $r2,$r10
    1db6:	50 95 00 01 	addi $r9,$r10,#0x1
    1dba:	fa 15       	movpi45 $r0,#0x25
    1dbc:	48 ff fd a0 	j 18fc <_vsnprintf+0x17c>
    1dc0:	b5 3c       	lwi450 $r9,[$fp]
    1dc2:	51 ce 00 04 	addi $fp,$fp,#0x4
    1dc6:	4e 95 02 6d 	bltz $r9,22a0 <_vsnprintf+0xb20>
    1dca:	8d 01       	addi45 $r8,#0x1
    1dcc:	20 01 80 01 	lbsi $r0,[$r3+#0x1]
    1dd0:	48 ff fd 52 	j 1874 <_vsnprintf+0xf4>
    1dd4:	5a 08 2a 04 	bnec $r0,#0x2a,1ddc <_vsnprintf+0x65c>
    1dd8:	48 00 02 5a 	j 228c <_vsnprintf+0xb0c>
    1ddc:	81 02       	mov55 $r8,$r2
    1dde:	48 ff fd 51 	j 1880 <_vsnprintf+0x100>
    1de2:	92 00       	nop16
    1de4:	20 0e 00 00 	lbsi $r0,[$fp+#0x0]
    1de8:	80 2e       	mov55 $r1,$r14
    1dea:	80 4a       	mov55 $r2,$r10
    1dec:	80 66       	mov55 $r3,$r6
    1dee:	dd 27       	jral5 $r7
    1df0:	5c 04 80 02 	slti $r0,$r9,#0x2
    1df4:	50 ce 00 04 	addi $r12,$fp,#0x4
    1df8:	50 b5 00 01 	addi $r11,$r10,#0x1
    1dfc:	4e 03 03 14 	bnez $r0,2424 <_vsnprintf+0xca4>
    1e00:	41 c4 a8 00 	add $fp,$r9,$r10
    1e04:	50 55 80 01 	addi $r5,$r11,#0x1
    1e08:	80 4b       	mov55 $r2,$r11
    1e0a:	fa 10       	movpi45 $r0,#0x20
    1e0c:	81 65       	mov55 $r11,$r5
    1e0e:	80 2e       	mov55 $r1,$r14
    1e10:	80 66       	mov55 $r3,$r6
    1e12:	dd 27       	jral5 $r7
    1e14:	4c be 7f f8 	bne $r11,$fp,1e04 <_vsnprintf+0x684>
    1e18:	81 4b       	mov55 $r10,$r11
    1e1a:	83 8c       	mov55 $fp,$r12
    1e1c:	48 ff ff 34 	j 1c84 <_vsnprintf+0x504>
    1e20:	6a 15 00 01 	fmfsr $r1,$fs10
    1e24:	6a 25 00 01 	fmfsr $r2,$fs10
    1e28:	e2 29       	slt45 $r1,$r9
    1e2a:	8c 41       	addi45 $r2,#0x1
    1e2c:	4e f2 02 f6 	beqz $r15,2418 <_vsnprintf+0xc98>
    1e30:	6a 05 00 01 	fmfsr $r0,$fs10
    1e34:	80 4a       	mov55 $r2,$r10
    1e36:	41 c0 28 01 	sub $fp,$r0,$r10
    1e3a:	92 00       	nop16
    1e3c:	50 d1 00 01 	addi $r13,$r2,#0x1
    1e40:	fa 10       	movpi45 $r0,#0x20
    1e42:	80 2e       	mov55 $r1,$r14
    1e44:	80 66       	mov55 $r3,$r6
    1e46:	dd 27       	jral5 $r7
    1e48:	40 0e 34 00 	add $r0,$fp,$r13
    1e4c:	40 00 24 06 	slt $r0,$r0,$r9
    1e50:	80 4d       	mov55 $r2,$r13
    1e52:	c8 f5       	bnez38 $r0,1e3c <_vsnprintf+0x6bc>
    1e54:	6a 15 00 01 	fmfsr $r1,$fs10
    1e58:	40 04 a8 00 	add $r0,$r9,$r10
    1e5c:	40 a0 04 01 	sub $r10,$r0,$r1
    1e60:	6a 04 00 01 	fmfsr $r0,$fs8
    1e64:	50 14 80 01 	addi $r1,$r9,#0x1
    1e68:	20 00 00 00 	lbsi $r0,[$r0+#0x0]
    1e6c:	6a 15 00 09 	fmtsr $r1,$fs10
    1e70:	4e 03 fe ba 	bnez $r0,1be4 <_vsnprintf+0x464>
    1e74:	48 ff fe ee 	j 1c50 <_vsnprintf+0x4d0>
    1e78:	84 26       	movi55 $r1,#0x6
    1e7a:	85 60       	movi55 $r11,#0x0
    1e7c:	6a 02 10 c8 	fcpysd $fd0,$fd4,$fd4
    1e80:	44 00 24 b8 	movi $r0,#0x24b8
    1e84:	f1 89       	swi37.sp $r1,[+#0x24]
    1e86:	6a 08 80 09 	fmtsr $r0,$fs17
    1e8a:	49 00 37 4f 	jal 8d28 <__fixdfsi>
    1e8e:	f1 09       	lwi37.sp $r1,[+#0x24]
    1e90:	44 30 24 60 	movi $r3,#0x2460
    1e94:	94 8b       	slli333 $r2,$r1,#0x3
    1e96:	88 43       	add45 $r2,$r3
    1e98:	34 51 00 00 	fldi $fd5,[$r2+#0x0]
    1e9c:	50 c0 00 00 	addi $r12,$r0,#0x0
    1ea0:	49 00 3e 39 	jal 9b12 <__floatsidf>
    1ea4:	6a 10 00 c8 	fcpysd $fd1,$fd0,$fd0
    1ea8:	6a 02 10 c8 	fcpysd $fd0,$fd4,$fd4
    1eac:	49 00 3a e2 	jal 9470 <__subdf3>
    1eb0:	6a 12 94 c8 	fcpysd $fd1,$fd5,$fd5
    1eb4:	49 00 38 8a 	jal 8fc8 <__muldf3>
    1eb8:	6a 60 00 c8 	fcpysd $fd6,$fd0,$fd0
    1ebc:	49 00 37 60 	jal 8d7c <__fixunsdfsi>
    1ec0:	6a 09 80 09 	fmtsr $r0,$fs19
    1ec4:	49 00 3e 5d 	jal 9b7e <__floatunsidf>
    1ec8:	6a 10 00 c8 	fcpysd $fd1,$fd0,$fd0
    1ecc:	6a 03 18 c8 	fcpysd $fd0,$fd6,$fd6
    1ed0:	49 00 3a d0 	jal 9470 <__subdf3>
    1ed4:	6a 08 80 01 	fmfsr $r0,$fs17
    1ed8:	6a 60 00 c8 	fcpysd $fd6,$fd0,$fd0
    1edc:	34 70 00 00 	fldi $fd7,[$r0+#0x0]
    1ee0:	6a 13 9c c8 	fcpysd $fd1,$fd7,$fd7
    1ee4:	49 00 37 c9 	jal 8e76 <__gedf2>
    1ee8:	f1 09       	lwi37.sp $r1,[+#0x24]
    1eea:	4e 07 00 cb 	blez $r0,2080 <_vsnprintf+0x900>
    1eee:	6a 09 80 01 	fmfsr $r0,$fs19
    1ef2:	8c 01       	addi45 $r0,#0x1
    1ef4:	6a 09 80 09 	fmtsr $r0,$fs19
    1ef8:	49 00 3e 43 	jal 9b7e <__floatunsidf>
    1efc:	6a 10 00 c8 	fcpysd $fd1,$fd0,$fd0
    1f00:	6a 02 94 c8 	fcpysd $fd0,$fd5,$fd5
    1f04:	49 00 38 0d 	jal 8f1e <__ledf2>
    1f08:	f1 09       	lwi37.sp $r1,[+#0x24]
    1f0a:	4e 07 01 6a 	blez $r0,21de <_vsnprintf+0xa5e>
    1f0e:	92 00       	nop16
    1f10:	44 00 24 c0 	movi $r0,#0x24c0
    1f14:	34 10 00 00 	fldi $fd1,[$r0+#0x0]
    1f18:	6a 02 10 c8 	fcpysd $fd0,$fd4,$fd4
    1f1c:	14 1f 80 09 	swi $r1,[$sp+#0x24]
    1f20:	49 00 37 ab 	jal 8e76 <__gedf2>
    1f24:	4e 06 00 c5 	bgtz $r0,20ae <_vsnprintf+0x92e>
    1f28:	f1 09       	lwi37.sp $r1,[+#0x24]
    1f2a:	4e 13 00 cd 	bnez $r1,20c4 <_vsnprintf+0x944>
    1f2e:	80 0c       	mov55 $r0,$r12
    1f30:	49 00 3d f1 	jal 9b12 <__floatsidf>
    1f34:	6a 10 00 c8 	fcpysd $fd1,$fd0,$fd0
    1f38:	6a 02 10 c8 	fcpysd $fd0,$fd4,$fd4
    1f3c:	49 00 3a 9a 	jal 9470 <__subdf3>
    1f40:	6a 08 80 01 	fmfsr $r0,$fs17
    1f44:	6a 40 00 c8 	fcpysd $fd4,$fd0,$fd0
    1f48:	34 50 00 00 	fldi $fd5,[$r0+#0x0]
    1f4c:	6a 12 94 c8 	fcpysd $fd1,$fd5,$fd5
    1f50:	49 00 37 93 	jal 8e76 <__gedf2>
    1f54:	4e 06 01 5e 	bgtz $r0,2210 <_vsnprintf+0xa90>
    1f58:	6a 02 10 c8 	fcpysd $fd0,$fd4,$fd4
    1f5c:	6a 12 94 c8 	fcpysd $fd1,$fd5,$fd5
    1f60:	49 00 37 54 	jal 8e08 <__eqdf2>
    1f64:	c8 06       	bnez38 $r0,1f70 <_vsnprintf+0x7f0>
    1f66:	54 06 00 01 	andi $r0,$r12,#0x1
    1f6a:	40 c6 00 00 	add $r12,$r12,$r0
    1f6e:	92 00       	nop16
    1f70:	5a b0 20 30 	beqc $r11,#0x20,1fd0 <_vsnprintf+0x850>
    1f74:	6a 08 00 01 	fmfsr $r0,$fs16
    1f78:	40 16 7c 0a 	srai $r1,$r12,#0x1f
    1f7c:	42 06 00 b8 	smmul $r0,$r12,$r0
    1f80:	b0 92       	addri36.sp $r2,#0x48
    1f82:	90 02       	srai45 $r0,#0x2
    1f84:	9a 41       	sub333 $r1,$r0,$r1
    1f86:	84 0a       	movi55 $r0,#0xa
    1f88:	42 c0 80 75 	msubr32 $r12,$r1,$r0
    1f8c:	50 06 00 30 	addi $r0,$r12,#0x30
    1f90:	38 01 2c 08 	sb $r0,[$r2+($r11<<#0x0)]
    1f94:	50 c5 80 01 	addi $r12,$r11,#0x1
    1f98:	c1 1e       	beqz38 $r1,1fd4 <_vsnprintf+0x854>
    1f9a:	40 31 30 00 	add $r3,$r2,$r12
    1f9e:	86 2a       	movi55 $r17,#0xa
    1fa0:	d5 08       	j8 1fb0 <_vsnprintf+0x830>
    1fa2:	92 00       	nop16
    1fa4:	50 c6 00 01 	addi $r12,$r12,#0x1
    1fa8:	18 21 80 01 	sbi.bi $r2,[$r3],#0x1
    1fac:	4e 12 00 14 	beqz $r1,1fd4 <_vsnprintf+0x854>
    1fb0:	6a 08 00 01 	fmfsr $r0,$fs16
    1fb4:	40 20 fc 0a 	srai $r2,$r1,#0x1f
    1fb8:	42 00 80 b8 	smmul $r0,$r1,$r0
    1fbc:	90 02       	srai45 $r0,#0x2
    1fbe:	8a 02       	sub45 $r0,$r2
    1fc0:	42 10 44 75 	msubr32 $r1,$r0,$r17
    1fc4:	50 20 80 30 	addi $r2,$r1,#0x30
    1fc8:	80 20       	mov55 $r1,$r0
    1fca:	5a c8 20 ed 	bnec $r12,#0x20,1fa4 <_vsnprintf+0x824>
    1fce:	92 00       	nop16
    1fd0:	44 c0 00 20 	movi $r12,#0x20
    1fd4:	54 36 80 03 	andi $r3,$r13,#0x3
    1fd8:	5a 38 01 04 	bnec $r3,#0x1,1fe0 <_vsnprintf+0x860>
    1fdc:	48 00 01 68 	j 22ac <_vsnprintf+0xb2c>
    1fe0:	4c 96 00 b4 	beq $r9,$r12,2148 <_vsnprintf+0x9c8>
    1fe4:	5c 06 00 20 	slti $r0,$r12,#0x20
    1fe8:	4e 03 00 ba 	bnez $r0,215c <_vsnprintf+0x9dc>
    1fec:	80 4a       	mov55 $r2,$r10
    1fee:	cb 19       	bnez38 $r3,2020 <_vsnprintf+0x8a0>
    1ff0:	40 06 24 06 	slt $r0,$r12,$r9
    1ff4:	4e 02 02 06 	beqz $r0,2400 <_vsnprintf+0xc80>
    1ff8:	40 06 28 01 	sub $r0,$r12,$r10
    1ffc:	6a 03 00 09 	fmtsr $r0,$fs6
    2000:	fa 10       	movpi45 $r0,#0x20
    2002:	80 2e       	mov55 $r1,$r14
    2004:	80 66       	mov55 $r3,$r6
    2006:	50 b1 00 01 	addi $r11,$r2,#0x1
    200a:	dd 27       	jral5 $r7
    200c:	6a 03 00 01 	fmfsr $r0,$fs6
    2010:	80 4b       	mov55 $r2,$r11
    2012:	88 0b       	add45 $r0,$r11
    2014:	40 00 24 06 	slt $r0,$r0,$r9
    2018:	c8 f4       	bnez38 $r0,2000 <_vsnprintf+0x880>
    201a:	40 24 a8 00 	add $r2,$r9,$r10
    201e:	8a 4c       	sub45 $r2,$r12
    2020:	4e c2 01 f8 	beqz $r12,2410 <_vsnprintf+0xc90>
    2024:	50 06 7f ff 	addi $r0,$r12,#-1
    2028:	b0 52       	addri36.sp $r1,#0x48
    202a:	88 01       	add45 $r0,$r1
    202c:	6a 04 80 09 	fmtsr $r0,$fs9
    2030:	40 b1 30 00 	add $r11,$r2,$r12
    2034:	6a 14 80 01 	fmfsr $r1,$fs9
    2038:	50 c1 00 01 	addi $r12,$r2,#0x1
    203c:	28 00 ff ff 	lbsi.bi $r0,[$r1],#-1
    2040:	6a 14 80 09 	fmtsr $r1,$fs9
    2044:	80 66       	mov55 $r3,$r6
    2046:	80 2e       	mov55 $r1,$r14
    2048:	dd 27       	jral5 $r7
    204a:	80 4c       	mov55 $r2,$r12
    204c:	4c c5 ff f4 	bne $r12,$r11,2034 <_vsnprintf+0x8b4>
    2050:	54 46 80 02 	andi $r4,$r13,#0x2
    2054:	c4 13       	beqz38 $r4,207a <_vsnprintf+0x8fa>
    2056:	40 05 a8 01 	sub $r0,$r11,$r10
    205a:	e2 09       	slt45 $r0,$r9
    205c:	e8 0f       	beqzs8 207a <_vsnprintf+0x8fa>
    205e:	92 00       	nop16
    2060:	50 45 80 01 	addi $r4,$r11,#0x1
    2064:	80 4b       	mov55 $r2,$r11
    2066:	fa 10       	movpi45 $r0,#0x20
    2068:	81 64       	mov55 $r11,$r4
    206a:	80 2e       	mov55 $r1,$r14
    206c:	80 66       	mov55 $r3,$r6
    206e:	dd 27       	jral5 $r7
    2070:	40 05 a8 01 	sub $r0,$r11,$r10
    2074:	40 00 24 06 	slt $r0,$r0,$r9
    2078:	c8 f4       	bnez38 $r0,2060 <_vsnprintf+0x8e0>
    207a:	81 4b       	mov55 $r10,$r11
    207c:	48 ff fe 04 	j 1c84 <_vsnprintf+0x504>
    2080:	6a 03 18 c8 	fcpysd $fd0,$fd6,$fd6
    2084:	6a 13 9c c8 	fcpysd $fd1,$fd7,$fd7
    2088:	f1 89       	swi37.sp $r1,[+#0x24]
    208a:	49 00 36 bf 	jal 8e08 <__eqdf2>
    208e:	f1 09       	lwi37.sp $r1,[+#0x24]
    2090:	4e 03 ff 40 	bnez $r0,1f10 <_vsnprintf+0x790>
    2094:	6a 09 80 01 	fmfsr $r0,$fs19
    2098:	c0 04       	beqz38 $r0,20a0 <_vsnprintf+0x920>
    209a:	96 04       	xlsb33 $r0,$r0
    209c:	4e 02 ff 3a 	beqz $r0,1f10 <_vsnprintf+0x790>
    20a0:	6a 09 80 01 	fmfsr $r0,$fs19
    20a4:	8c 01       	addi45 $r0,#0x1
    20a6:	6a 09 80 09 	fmtsr $r0,$fs19
    20aa:	48 ff ff 33 	j 1f10 <_vsnprintf+0x790>
    20ae:	85 40       	movi55 $r10,#0x0
    20b0:	48 ff fd ea 	j 1c84 <_vsnprintf+0x504>
    20b4:	20 04 00 02 	lbsi $r0,[$r8+#0x2]
    20b8:	58 d6 80 c0 	ori $r13,$r13,#0xc0
    20bc:	8d 02       	addi45 $r8,#0x2
    20be:	48 ff fc 17 	j 18ec <_vsnprintf+0x16c>
    20c2:	92 00       	nop16
    20c4:	5a b8 20 04 	bnec $r11,#0x20,20cc <_vsnprintf+0x94c>
    20c8:	48 ff ff 84 	j 1fd0 <_vsnprintf+0x850>
    20cc:	6a 23 80 01 	fmfsr $r2,$fs7
    20d0:	6a 09 80 01 	fmfsr $r0,$fs19
    20d4:	6a 33 80 01 	fmfsr $r3,$fs7
    20d8:	42 00 08 b8 	smmul $r0,$r0,$r2
    20dc:	6a 29 80 01 	fmfsr $r2,$fs19
    20e0:	b1 12       	addri36.sp $r4,#0x48
    20e2:	90 5f       	srai45 $r2,#0x1f
    20e4:	fe 9e       	and33 $r2,$r3
    20e6:	88 02       	add45 $r0,$r2
    20e8:	6a 29 80 01 	fmfsr $r2,$fs19
    20ec:	8e 21       	subi45 $r1,#0x1
    20ee:	88 02       	add45 $r0,$r2
    20f0:	40 30 0c 09 	srli $r3,$r0,#0x3
    20f4:	84 0a       	movi55 $r0,#0xa
    20f6:	42 21 80 75 	msubr32 $r2,$r3,$r0
    20fa:	50 01 00 30 	addi $r0,$r2,#0x30
    20fe:	38 02 2c 08 	sb $r0,[$r4+($r11<<#0x0)]
    2102:	50 25 80 01 	addi $r2,$r11,#0x1
    2106:	4e 32 00 a1 	beqz $r3,2248 <_vsnprintf+0xac8>
    210a:	41 12 08 00 	add $r17,$r4,$r2
    210e:	86 4a       	movi55 $r18,#0xa
    2110:	d5 10       	j8 2130 <_vsnprintf+0x9b0>
    2112:	88 03       	add45 $r0,$r3
    2114:	92 03       	srli45 $r0,#0x3
    2116:	42 30 48 75 	msubr32 $r3,$r0,$r18
    211a:	8e 21       	subi45 $r1,#0x1
    211c:	80 a3       	mov55 $r5,$r3
    211e:	80 60       	mov55 $r3,$r0
    2120:	50 02 80 30 	addi $r0,$r5,#0x30
    2124:	8c 41       	addi45 $r2,#0x1
    2126:	18 08 80 01 	sbi.bi $r0,[$r17],#0x1
    212a:	4e 32 00 8f 	beqz $r3,2248 <_vsnprintf+0xac8>
    212e:	92 00       	nop16
    2130:	6a 03 80 01 	fmfsr $r0,$fs7
    2134:	42 01 80 b8 	smmul $r0,$r3,$r0
    2138:	5a 28 20 ed 	bnec $r2,#0x20,2112 <_vsnprintf+0x992>
    213c:	48 ff ff 4a 	j 1fd0 <_vsnprintf+0x850>
    2140:	5a 90 20 04 	beqc $r9,#0x20,2148 <_vsnprintf+0x9c8>
    2144:	48 00 01 4a 	j 23d8 <_vsnprintf+0xc58>
    2148:	6a 09 00 01 	fmfsr $r0,$fs18
    214c:	c8 06       	bnez38 $r0,2158 <_vsnprintf+0x9d8>
    214e:	54 06 80 0c 	andi $r0,$r13,#0xc
    2152:	4e 02 01 4f 	beqz $r0,23f0 <_vsnprintf+0xc70>
    2156:	92 00       	nop16
    2158:	50 c4 ff ff 	addi $r12,$r9,#-1
    215c:	6a 09 00 01 	fmfsr $r0,$fs18
    2160:	c8 4f       	bnez38 $r0,21fe <_vsnprintf+0xa7e>
    2162:	92 00       	nop16
    2164:	54 06 80 04 	andi $r0,$r13,#0x4
    2168:	4e 02 01 2c 	beqz $r0,23c0 <_vsnprintf+0xc40>
    216c:	fa 1b       	movpi45 $r0,#0x2b
    216e:	b0 52       	addri36.sp $r1,#0x48
    2170:	38 00 b0 08 	sb $r0,[$r1+($r12<<#0x0)]
    2174:	50 c6 00 01 	addi $r12,$r12,#0x1
    2178:	48 ff ff 3a 	j 1fec <_vsnprintf+0x86c>
    217c:	fa 40       	movpi45 $r2,#0x10
    217e:	92 00       	nop16
    2180:	54 36 84 00 	andi $r3,$r13,#0x400
    2184:	66 16 80 0c 	bitci $r1,$r13,#0xc
    2188:	4e 33 00 28 	bnez $r3,21d8 <_vsnprintf+0xa58>
    218c:	5a 08 69 04 	bnec $r0,#0x69,2194 <_vsnprintf+0xa14>
    2190:	48 ff fd ba 	j 1d04 <_vsnprintf+0x584>
    2194:	5a 08 64 04 	bnec $r0,#0x64,219c <_vsnprintf+0xa1c>
    2198:	48 ff fd b6 	j 1d04 <_vsnprintf+0x584>
    219c:	54 00 82 00 	andi $r0,$r1,#0x200
    21a0:	4e 03 00 a8 	bnez $r0,22f0 <_vsnprintf+0xb70>
    21a4:	54 00 81 00 	andi $r0,$r1,#0x100
    21a8:	c8 38       	bnez38 $r0,2218 <_vsnprintf+0xa98>
    21aa:	54 00 80 40 	andi $r0,$r1,#0x40
    21ae:	4e 02 00 fb 	beqz $r0,23a4 <_vsnprintf+0xc24>
    21b2:	00 4e 00 00 	lbi $r4,[$fp+#0x0]
    21b6:	51 ce 00 04 	addi $fp,$fp,#0x4
    21ba:	b6 5f       	swi450 $r2,[$sp]
    21bc:	14 bf 80 01 	swi $r11,[$sp+#0x4]
    21c0:	14 9f 80 02 	swi $r9,[$sp+#0x8]
    21c4:	f1 83       	swi37.sp $r1,[+#0xc]
    21c6:	48 ff fd 57 	j 1c74 <_vsnprintf+0x4f4>
    21ca:	81 a1       	mov55 $r13,$r1
    21cc:	5a 08 64 da 	bnec $r0,#0x64,2180 <_vsnprintf+0xa00>
    21d0:	54 40 84 00 	andi $r4,$r1,#0x400
    21d4:	4e 42 fd 98 	beqz $r4,1d04 <_vsnprintf+0x584>
    21d8:	66 10 80 01 	bitci $r1,$r1,#0x1
    21dc:	d5 d8       	j8 218c <_vsnprintf+0xa0c>
    21de:	84 00       	movi55 $r0,#0x0
    21e0:	50 c6 00 01 	addi $r12,$r12,#0x1
    21e4:	6a 09 80 09 	fmtsr $r0,$fs19
    21e8:	48 ff fe 94 	j 1f10 <_vsnprintf+0x790>
    21ec:	66 16 80 0c 	bitci $r1,$r13,#0xc
    21f0:	54 46 84 00 	andi $r4,$r13,#0x400
    21f4:	58 10 80 20 	ori $r1,$r1,#0x20
    21f8:	fa 40       	movpi45 $r2,#0x10
    21fa:	cc ef       	bnez38 $r4,21d8 <_vsnprintf+0xa58>
    21fc:	d5 d0       	j8 219c <_vsnprintf+0xa1c>
    21fe:	fa 1d       	movpi45 $r0,#0x2d
    2200:	b0 52       	addri36.sp $r1,#0x48
    2202:	38 00 b0 08 	sb $r0,[$r1+($r12<<#0x0)]
    2206:	50 c6 00 01 	addi $r12,$r12,#0x1
    220a:	48 ff fe f1 	j 1fec <_vsnprintf+0x86c>
    220e:	92 00       	nop16
    2210:	50 c6 00 01 	addi $r12,$r12,#0x1
    2214:	48 ff fe ae 	j 1f70 <_vsnprintf+0x7f0>
    2218:	b6 5f       	swi450 $r2,[$sp]
    221a:	14 bf 80 01 	swi $r11,[$sp+#0x4]
    221e:	14 9f 80 02 	swi $r9,[$sp+#0x8]
    2222:	f1 83       	swi37.sp $r1,[+#0xc]
    2224:	b4 9c       	lwi450 $r4,[$fp]
    2226:	51 ce 00 04 	addi $fp,$fp,#0x4
    222a:	48 ff fd 25 	j 1c74 <_vsnprintf+0x4f4>
    222e:	92 00       	nop16
    2230:	54 00 80 80 	andi $r0,$r1,#0x80
    2234:	4e 03 00 d8 	bnez $r0,23e4 <_vsnprintf+0xc64>
    2238:	b4 bc       	lwi450 $r5,[$fp]
    223a:	51 ce 00 04 	addi $fp,$fp,#0x4
    223e:	48 ff fd 73 	j 1d24 <_vsnprintf+0x5a4>
    2242:	84 42       	movi55 $r2,#0x2
    2244:	d5 9e       	j8 2180 <_vsnprintf+0xa00>
    2246:	92 00       	nop16
    2248:	5a 28 20 04 	bnec $r2,#0x20,2250 <_vsnprintf+0xad0>
    224c:	48 ff fe c2 	j 1fd0 <_vsnprintf+0x850>
    2250:	c1 48       	beqz38 $r1,22e0 <_vsnprintf+0xb60>
    2252:	b0 12       	addri36.sp $r0,#0x48
    2254:	88 02       	add45 $r0,$r2
    2256:	44 30 00 30 	movi $r3,#0x30
    225a:	d5 02       	j8 225e <_vsnprintf+0xade>
    225c:	c1 42       	beqz38 $r1,22e0 <_vsnprintf+0xb60>
    225e:	8c 41       	addi45 $r2,#0x1
    2260:	8e 21       	subi45 $r1,#0x1
    2262:	18 30 00 01 	sbi.bi $r3,[$r0],#0x1
    2266:	5a 28 20 fb 	bnec $r2,#0x20,225c <_vsnprintf+0xadc>
    226a:	48 ff fe b3 	j 1fd0 <_vsnprintf+0x850>
    226e:	92 00       	nop16
    2270:	6a 12 10 c8 	fcpysd $fd1,$fd4,$fd4
    2274:	6a 02 94 c8 	fcpysd $fd0,$fd5,$fd5
    2278:	44 00 00 01 	movi $r0,#0x1
    227c:	6a 09 00 09 	fmtsr $r0,$fs18
    2280:	49 00 38 f8 	jal 9470 <__subdf3>
    2284:	6a 40 00 c8 	fcpysd $fd4,$fd0,$fd0
    2288:	48 ff fd 78 	j 1d78 <_vsnprintf+0x5f8>
    228c:	b4 3c       	lwi450 $r1,[$fp]
    228e:	20 04 00 02 	lbsi $r0,[$r8+#0x2]
    2292:	42 b5 84 00 	max $r11,$r11,$r1
    2296:	8d 02       	addi45 $r8,#0x2
    2298:	51 ce 00 04 	addi $fp,$fp,#0x4
    229c:	48 ff fa f2 	j 1880 <_vsnprintf+0x100>
    22a0:	58 d6 80 02 	ori $r13,$r13,#0x2
    22a4:	52 94 80 00 	subri $r9,$r9,#0x0
    22a8:	48 ff fd 91 	j 1dca <_vsnprintf+0x64a>
    22ac:	40 06 24 06 	slt $r0,$r12,$r9
    22b0:	4e 02 fe 98 	beqz $r0,1fe0 <_vsnprintf+0x860>
    22b4:	5a c8 20 04 	bnec $r12,#0x20,22bc <_vsnprintf+0xb3c>
    22b8:	48 ff ff 44 	j 2140 <_vsnprintf+0x9c0>
    22bc:	b0 12       	addri36.sp $r0,#0x48
    22be:	88 0c       	add45 $r0,$r12
    22c0:	44 10 00 30 	movi $r1,#0x30
    22c4:	48 00 00 06 	j 22d0 <_vsnprintf+0xb50>
    22c8:	5a c8 20 04 	bnec $r12,#0x20,22d0 <_vsnprintf+0xb50>
    22cc:	48 ff ff 3a 	j 2140 <_vsnprintf+0x9c0>
    22d0:	50 c6 00 01 	addi $r12,$r12,#0x1
    22d4:	18 10 00 01 	sbi.bi $r1,[$r0],#0x1
    22d8:	4c c4 ff f8 	bne $r12,$r9,22c8 <_vsnprintf+0xb48>
    22dc:	48 ff ff 36 	j 2148 <_vsnprintf+0x9c8>
    22e0:	fa 1e       	movpi45 $r0,#0x2e
    22e2:	b0 52       	addri36.sp $r1,#0x48
    22e4:	50 b1 00 01 	addi $r11,$r2,#0x1
    22e8:	38 00 88 08 	sb $r0,[$r1+($r2<<#0x0)]
    22ec:	48 ff fe 42 	j 1f70 <_vsnprintf+0x7f0>
    22f0:	84 00       	movi55 $r0,#0x0
    22f2:	f0 91       	swi37.sp $r0,[+#0x44]
    22f4:	f2 90       	swi37.sp $r2,[+#0x40]
    22f6:	f2 10       	lwi37.sp $r2,[+#0x40]
    22f8:	f3 11       	lwi37.sp $r3,[+#0x44]
    22fa:	51 ce 00 07 	addi $fp,$fp,#0x7
    22fe:	b6 1f       	swi450 $r0,[$sp]
    2300:	f2 82       	swi37.sp $r2,[+#0x8]
    2302:	f3 83       	swi37.sp $r3,[+#0xc]
    2304:	f1 86       	swi37.sp $r1,[+#0x18]
    2306:	67 ce 00 07 	bitci $fp,$fp,#0x7
    230a:	14 bf 80 04 	swi $r11,[$sp+#0x10]
    230e:	14 9f 80 05 	swi $r9,[$sp+#0x14]
    2312:	80 4a       	mov55 $r2,$r10
    2314:	3a 4e 14 00 	lmw.bi $r4,[$fp],$r5,#0x0    ! {$r4~$r5}
    2318:	80 07       	mov55 $r0,$r7
    231a:	80 2e       	mov55 $r1,$r14
    231c:	50 33 00 00 	addi $r3,$r6,#0x0
    2320:	49 ff f9 b2 	jal 1684 <_ntoa_long_long>
    2324:	51 ce 00 08 	addi $fp,$fp,#0x8
    2328:	81 40       	mov55 $r10,$r0
    232a:	48 ff fc ad 	j 1c84 <_vsnprintf+0x504>
    232e:	84 48       	movi55 $r2,#0x8
    2330:	48 ff ff 28 	j 2180 <_vsnprintf+0xa00>
    2334:	51 ce 00 07 	addi $fp,$fp,#0x7
    2338:	67 ce 00 07 	bitci $fp,$fp,#0x7
    233c:	3a 4e 14 00 	lmw.bi $r4,[$fp],$r5,#0x0    ! {$r4~$r5}
    2340:	40 02 fc 0a 	srai $r0,$r5,#0x1f
    2344:	f0 8a       	swi37.sp $r0,[+#0x28]
    2346:	05 2f 80 0a 	lwi $r18,[$sp+#0x28]
    234a:	f0 8b       	swi37.sp $r0,[+#0x2c]
    234c:	05 3f 80 0b 	lwi $r19,[$sp+#0x2c]
    2350:	80 72       	mov55 $r3,$r18
    2352:	80 04       	mov55 $r0,$r4
    2354:	fe 1d       	xor33 $r0,$r3
    2356:	f0 8c       	swi37.sp $r0,[+#0x30]
    2358:	f2 8e       	swi37.sp $r2,[+#0x38]
    235a:	80 05       	mov55 $r0,$r5
    235c:	80 53       	mov55 $r2,$r19
    235e:	fe 15       	xor33 $r0,$r2
    2360:	84 40       	movi55 $r2,#0x0
    2362:	f0 8d       	swi37.sp $r0,[+#0x34]
    2364:	f2 8f       	swi37.sp $r2,[+#0x3c]
    2366:	40 02 fc 09 	srli $r0,$r5,#0x1f
    236a:	f2 0e       	lwi37.sp $r2,[+#0x38]
    236c:	f3 0f       	lwi37.sp $r3,[+#0x3c]
    236e:	05 0f 80 0c 	lwi $r16,[$sp+#0x30]
    2372:	05 1f 80 0d 	lwi $r17,[$sp+#0x34]
    2376:	b6 1f       	swi450 $r0,[$sp]
    2378:	f2 82       	swi37.sp $r2,[+#0x8]
    237a:	f3 83       	swi37.sp $r3,[+#0xc]
    237c:	f1 86       	swi37.sp $r1,[+#0x18]
    237e:	80 4a       	mov55 $r2,$r10
    2380:	14 bf 80 04 	swi $r11,[$sp+#0x10]
    2384:	14 9f 80 05 	swi $r9,[$sp+#0x14]
    2388:	80 07       	mov55 $r0,$r7
    238a:	80 2e       	mov55 $r1,$r14
    238c:	50 33 00 00 	addi $r3,$r6,#0x0
    2390:	42 48 48 34 	sub64 $r4,$r16,$r18
    2394:	49 ff f9 78 	jal 1684 <_ntoa_long_long>
    2398:	51 ce 00 08 	addi $fp,$fp,#0x8
    239c:	81 40       	mov55 $r10,$r0
    239e:	48 ff fc 73 	j 1c84 <_vsnprintf+0x504>
    23a2:	92 00       	nop16
    23a4:	54 00 80 80 	andi $r0,$r1,#0x80
    23a8:	c0 2f       	beqz38 $r0,2406 <_vsnprintf+0xc86>
    23aa:	02 4e 00 00 	lhi $r4,[$fp+#0x0]
    23ae:	51 ce 00 04 	addi $fp,$fp,#0x4
    23b2:	48 ff ff 04 	j 21ba <_vsnprintf+0xa3a>
    23b6:	84 20       	movi55 $r1,#0x0
    23b8:	6a 15 00 09 	fmtsr $r1,$fs10
    23bc:	48 ff fb fe 	j 1bb8 <_vsnprintf+0x438>
    23c0:	54 06 80 08 	andi $r0,$r13,#0x8
    23c4:	4e 02 fe 14 	beqz $r0,1fec <_vsnprintf+0x86c>
    23c8:	fa 10       	movpi45 $r0,#0x20
    23ca:	b0 52       	addri36.sp $r1,#0x48
    23cc:	38 00 b0 08 	sb $r0,[$r1+($r12<<#0x0)]
    23d0:	50 c6 00 01 	addi $r12,$r12,#0x1
    23d4:	48 ff fe 0c 	j 1fec <_vsnprintf+0x86c>
    23d8:	80 4a       	mov55 $r2,$r10
    23da:	44 c0 00 20 	movi $r12,#0x20
    23de:	48 ff fe 23 	j 2024 <_vsnprintf+0x8a4>
    23e2:	92 00       	nop16
    23e4:	22 5e 00 00 	lhsi $r5,[$fp+#0x0]
    23e8:	51 ce 00 04 	addi $fp,$fp,#0x4
    23ec:	48 ff fc 9c 	j 1d24 <_vsnprintf+0x5a4>
    23f0:	5c f4 80 20 	slti $r15,$r9,#0x20
    23f4:	81 89       	mov55 $r12,$r9
    23f6:	4e f3 fe b7 	bnez $r15,2164 <_vsnprintf+0x9e4>
    23fa:	80 4a       	mov55 $r2,$r10
    23fc:	48 ff fe 14 	j 2024 <_vsnprintf+0x8a4>
    2400:	80 4a       	mov55 $r2,$r10
    2402:	48 ff fe 0f 	j 2020 <_vsnprintf+0x8a0>
    2406:	b4 9c       	lwi450 $r4,[$fp]
    2408:	51 ce 00 04 	addi $fp,$fp,#0x4
    240c:	48 ff fe d7 	j 21ba <_vsnprintf+0xa3a>
    2410:	81 62       	mov55 $r11,$r2
    2412:	48 ff fe 1f 	j 2050 <_vsnprintf+0x8d0>
    2416:	92 00       	nop16
    2418:	6a 25 00 09 	fmtsr $r2,$fs10
    241c:	4e 03 fb e4 	bnez $r0,1be4 <_vsnprintf+0x464>
    2420:	48 ff fc 18 	j 1c50 <_vsnprintf+0x4d0>
    2424:	83 8c       	mov55 $fp,$r12
    2426:	81 4b       	mov55 $r10,$r11
    2428:	48 ff fc 2e 	j 1c84 <_vsnprintf+0x504>
    242c:	81 2a       	mov55 $r9,$r10
    242e:	48 ff fc 43 	j 1cb4 <_vsnprintf+0x534>
    2432:	80 2b       	mov55 $r1,$r11
    2434:	85 60       	movi55 $r11,#0x0
    2436:	48 ff fd 23 	j 1e7c <_vsnprintf+0x6fc>
    243a:	92 00       	nop16

0000243c <printf>:
    243c:	3b ff fc bc 	smw.adm $sp,[$sp],$sp,#0x2    ! {$lp}
    2440:	ef f4       	addi10.sp #-12
    2442:	84 5f       	movi55 $r2,#-1
    2444:	80 60       	mov55 $r3,$r0
    2446:	b0 41       	addri36.sp $r1,#0x4
    2448:	b1 04       	addri36.sp $r4,#0x10
    244a:	44 00 17 5c 	movi $r0,#0x175c
    244e:	49 ff f9 99 	jal 1780 <_vsnprintf>
    2452:	92 00       	nop16
    2454:	ec 0c       	addi10.sp #0xc
    2456:	3b ff fc 84 	lmw.bim $sp,[$sp],$sp,#0x2    ! {$lp}
    245a:	dd 9e       	ret5 $lp
    245c:	00 00 00 00 	lbi $r0,[$r0+#0x0]

00002460 <pow10.3224>:
    2460:	00 00 00 00 00 00 f0 3f 00 00 00 00 00 00 24 40     .......?......$@
    2470:	00 00 00 00 00 00 59 40 00 00 00 00 00 40 8f 40     ......Y@.....@.@
    2480:	00 00 00 00 00 88 c3 40 00 00 00 00 00 6a f8 40     .......@.....j.@
    2490:	00 00 00 00 80 84 2e 41 00 00 00 00 d0 12 63 41     .......A......cA
    24a0:	00 00 00 00 84 d7 97 41 00 00 00 00 65 cd cd 41     .......A....e..A
	...
    24bc:	00 00 e0 3f 00 00 c0 ff ff ff df 41                 ...?.......A

000024c8 <__ota_pre_c_init>:
    24c8:	3e 08 00 88 	addi.gp $r0,#0x88
    24cc:	3e 18 31 80 	addi.gp $r1,#0x3180
    24d0:	9a 88       	sub333 $r2,$r1,$r0
    24d2:	c2 19       	beqz38 $r2,2504 <clear_end>
    24d4:	54 71 00 1f 	andi $r7,$r2,#0x1f
    24d8:	84 60       	movi55 $r3,#0x0
    24da:	84 80       	movi55 $r4,#0x0
    24dc:	84 a0       	movi55 $r5,#0x0
    24de:	84 c0       	movi55 $r6,#0x0
    24e0:	85 00       	movi55 $r8,#0x0
    24e2:	85 20       	movi55 $r9,#0x0
    24e4:	85 40       	movi55 $r10,#0x0
    24e6:	c7 09       	beqz38 $r7,24f8 <clear_loop>
    24e8:	9a 97       	sub333 $r2,$r2,$r7

000024ea <first_clear>:
    24ea:	aa c1       	swi333.bi $r3,[$r0],#0x4
    24ec:	9f fc       	subi333 $r7,$r7,#0x4
    24ee:	cf fe       	bnez38 $r7,24ea <first_clear>
    24f0:	44 1f ff e0 	movi $r1,#-32
    24f4:	fe 8e       	and33 $r2,$r1
    24f6:	c2 07       	beqz38 $r2,2504 <clear_end>

000024f8 <clear_loop>:
    24f8:	3a 30 28 24 	smw.bim $r3,[$r0],$r10,#0x0    ! {$r3~$r10}
    24fc:	50 21 7f e0 	addi $r2,$r2,#-32
    2500:	4e 24 ff fc 	bgez $r2,24f8 <clear_loop>

00002504 <clear_end>:
    2504:	3f c8 80 00 	addi.gp $fp,#0x8000
    2508:	3f f8 80 00 	addi.gp $sp,#0x8000
    250c:	dd 9e       	ret5 $lp
    250e:	92 00       	nop16
    2510:	76 31 2e 30 	*unknown*
    2514:	2e 30 00 00 	lbi.gp $r3,[+#0x0]

00002518 <_ota_nds32_init_mem>:
    2518:	3e 58 00 00 	addi.gp $r5,#0x0
    251c:	3e 48 00 88 	addi.gp $r4,#0x88
    2520:	8a 85       	sub45 $r4,$r5
    2522:	47 03 00 0b 	sethi $r16,#0x3000b
    2526:	59 08 07 40 	ori $r16,$r16,#0x740
    252a:	80 64       	mov55 $r3,$r4
    252c:	80 25       	mov55 $r1,$r5
    252e:	80 50       	mov55 $r2,$r16
    2530:	0c 01 00 01 	lwi.bi $r0,[$r2],#0x4
    2534:	1c 00 80 01 	swi.bi $r0,[$r1],#0x4
    2538:	50 31 ff fc 	addi $r3,$r3,#-4
    253c:	4e 36 ff fa 	bgtz $r3,2530 <_ota_nds32_init_mem+0x18>
    2540:	dd 9e       	ret5 $lp
    2542:	92 00       	nop16
    2544:	00 b0 b0 cc 	lbi $r11,[$r1+#0x30cc]
    2548:	11 98 98 24 	sbi $r25,[$r17+#0x1824]
    254c:	14 b0 b0 cc 	swi $r11,[$r1+#0xc330]
    2550:	42 f2 71 00 	kmmwb2 $r15,$r4,$fp
    2554:	1c b0 b0 cc 	swi.bi $r11,[$r1],#0xc330
    2558:	95 b1       	slli333 $r6,$r6,#0x1
    255a:	2a 27 0c b0 	lhsi.bi $r2,[$r14],#0x1960
    255e:	b0 cc       	addri36.sp $r3,#0x30
    2560:	80 f9       	mov55 $r7,$r25
    2562:	58 58 58 b0 	ori $r5,$r16,#0x58b0
    2566:	b0 cc       	addri36.sp $r3,#0x30
    2568:	1a 0a 00 00 	shi.bi $r0,[$r20],#0x0

0000256c <_ota_soc_clk_init>:
    256c:	46 0c 00 00 	sethi $r0,#0xc0000
    2570:	84 40       	movi55 $r2,#0x0
    2572:	14 20 00 70 	swi $r2,[$r0+#0x1c0]
    2576:	a0 46       	lwi333 $r1,[$r0+#0x18]
    2578:	e6 23       	slti45 $r1,#0x3
    257a:	e9 09       	bnezs8 258c <_ota_soc_clk_init+0x20>
    257c:	46 12 12 10 	sethi $r1,#0x21210
    2580:	50 10 80 c9 	addi $r1,$r1,#0xc9
    2584:	14 10 00 15 	swi $r1,[$r0+#0x54]
    2588:	64 00 00 40 	standby wait_done
    258c:	44 10 25 44 	movi $r1,#0x2544
    2590:	3b 00 e4 00 	lmw.bi $r16,[$r1],$r25,#0x0    ! {$r16~$r25}
    2594:	80 1f       	mov55 $r0,$sp
    2596:	3b 0f e4 20 	smw.bi $r16,[$sp],$r25,#0x0    ! {$r16~$r25}
    259a:	84 20       	movi55 $r1,#0x0
    259c:	38 20 04 02 	lw $r2,[$r0+($r1<<#0x0)]
    25a0:	98 c1       	add333 $r3,$r0,$r1
    25a2:	a0 d9       	lwi333 $r3,[$r3+#0x4]
    25a4:	8c 28       	addi45 $r1,#0x8
    25a6:	b6 62       	swi450 $r3,[$r2]
    25a8:	5a 18 28 fa 	bnec $r1,#0x28,259c <_ota_soc_clk_init+0x30>
    25ac:	44 00 00 1a 	movi $r0,#0x1a
    25b0:	5a 00 1a 2c 	beqc $r0,#0x1a,2608 <_ota_soc_clk_init+0x9c>
    25b4:	e4 1b       	sltsi45 $r0,#0x1b
    25b6:	e8 09       	beqzs8 25c8 <_ota_soc_clk_init+0x5c>
    25b8:	5a 00 18 1f 	beqc $r0,#0x18,25f6 <_ota_soc_clk_init+0x8a>
    25bc:	e4 19       	sltsi45 $r0,#0x19
    25be:	e8 13       	beqzs8 25e4 <_ota_soc_clk_init+0x78>
    25c0:	5a 00 10 18 	beqc $r0,#0x10,25f0 <_ota_soc_clk_init+0x84>
    25c4:	48 00 00 0e 	j 25e0 <_ota_soc_clk_init+0x74>
    25c8:	5a 00 28 23 	beqc $r0,#0x28,260e <_ota_soc_clk_init+0xa2>
    25cc:	5e f0 00 29 	sltsi $r15,$r0,#0x29
    25d0:	e8 04       	beqzs8 25d8 <_ota_soc_clk_init+0x6c>
    25d2:	5a 00 20 15 	beqc $r0,#0x20,25fc <_ota_soc_clk_init+0x90>
    25d6:	d5 05       	j8 25e0 <_ota_soc_clk_init+0x74>
    25d8:	5a 00 34 09 	beqc $r0,#0x34,25ea <_ota_soc_clk_init+0x7e>
    25dc:	5a 00 c0 13 	beqc $r0,#0xc0,2602 <_ota_soc_clk_init+0x96>
    25e0:	84 20       	movi55 $r1,#0x0
    25e2:	d5 14       	j8 260a <_ota_soc_clk_init+0x9e>
    25e4:	84 21       	movi55 $r1,#0x1
    25e6:	84 46       	movi55 $r2,#0x6
    25e8:	d5 16       	j8 2614 <_ota_soc_clk_init+0xa8>
    25ea:	84 21       	movi55 $r1,#0x1
    25ec:	84 4a       	movi55 $r2,#0xa
    25ee:	d5 13       	j8 2614 <_ota_soc_clk_init+0xa8>
    25f0:	84 20       	movi55 $r1,#0x0
    25f2:	80 41       	mov55 $r2,$r1
    25f4:	d5 10       	j8 2614 <_ota_soc_clk_init+0xa8>
    25f6:	84 20       	movi55 $r1,#0x0
    25f8:	84 41       	movi55 $r2,#0x1
    25fa:	d5 0d       	j8 2614 <_ota_soc_clk_init+0xa8>
    25fc:	84 20       	movi55 $r1,#0x0
    25fe:	84 47       	movi55 $r2,#0x7
    2600:	d5 0a       	j8 2614 <_ota_soc_clk_init+0xa8>
    2602:	84 20       	movi55 $r1,#0x0
    2604:	84 48       	movi55 $r2,#0x8
    2606:	d5 07       	j8 2614 <_ota_soc_clk_init+0xa8>
    2608:	84 21       	movi55 $r1,#0x1
    260a:	84 42       	movi55 $r2,#0x2
    260c:	d5 04       	j8 2614 <_ota_soc_clk_init+0xa8>
    260e:	84 20       	movi55 $r1,#0x0
    2610:	84 43       	movi55 $r2,#0x3
    2612:	92 00       	nop16
    2614:	46 3c cb 0b 	sethi $r3,#0xccb0b
    2618:	a1 1d       	lwi333 $r4,[$r3+#0x14]
    261a:	66 42 10 00 	bitci $r4,$r4,#0x1000
    261e:	40 12 05 84 	or_slli $r1,$r4,$r1,#0xc
    2622:	a8 5d       	swi333 $r1,[$r3+#0x14]
    2624:	a0 5d       	lwi333 $r1,[$r3+#0x14]
    2626:	66 10 80 0f 	bitci $r1,$r1,#0xf
    262a:	fe 8f       	or33 $r2,$r1
    262c:	a8 9d       	swi333 $r2,[$r3+#0x14]
    262e:	a0 59       	lwi333 $r1,[$r3+#0x4]
    2630:	42 10 fc 08 	bset $r1,$r1,#0x1f
    2634:	a8 59       	swi333 $r1,[$r3+#0x4]
    2636:	46 1c 00 00 	sethi $r1,#0xc0000
    263a:	50 10 80 5c 	addi $r1,$r1,#0x5c
    263e:	b4 41       	lwi450 $r2,[$r1]
    2640:	42 21 08 0b 	btst $r2,$r2,#0x2
    2644:	5a 28 01 fd 	bnec $r2,#0x1,263e <_ota_soc_clk_init+0xd2>
    2648:	44 30 01 40 	movi $r3,#0x140
    264c:	46 1c cb 0b 	sethi $r1,#0xccb0b
    2650:	5a 30 f0 08 	beqc $r3,#0xf0,2660 <_ota_soc_clk_init+0xf4>
    2654:	5a 39 e0 0a 	bnec $r3,#0x1e0,2668 <_ota_soc_clk_init+0xfc>
    2658:	a0 8c       	lwi333 $r2,[$r1+#0x10]
    265a:	58 21 00 38 	ori $r2,$r2,#0x38
    265e:	a8 8c       	swi333 $r2,[$r1+#0x10]
    2660:	a0 8e       	lwi333 $r2,[$r1+#0x18]
    2662:	42 21 3c 08 	bset $r2,$r2,#0xf
    2666:	d5 04       	j8 266e <_ota_soc_clk_init+0x102>
    2668:	a0 8e       	lwi333 $r2,[$r1+#0x18]
    266a:	42 21 3c 09 	bclr $r2,$r2,#0xf
    266e:	a8 8e       	swi333 $r2,[$r1+#0x18]
    2670:	46 2c 00 00 	sethi $r2,#0xc0000
    2674:	04 11 00 17 	lwi $r1,[$r2+#0x5c]
    2678:	92 28       	srli45 $r1,#0x8
    267a:	96 67       	fexti33 $r1,#0x4
    267c:	5a 18 03 fc 	bnec $r1,#0x3,2674 <_ota_soc_clk_init+0x108>
    2680:	46 1c 00 00 	sethi $r1,#0xc0000
    2684:	50 10 80 5c 	addi $r1,$r1,#0x5c
    2688:	b4 41       	lwi450 $r2,[$r1]
    268a:	5a 2b 07 ff 	bnec $r2,#0x307,2688 <_ota_soc_clk_init+0x11c>
    268e:	46 1c 00 00 	sethi $r1,#0xc0000
    2692:	44 20 00 a0 	movi $r2,#0xa0
    2696:	58 10 81 00 	ori $r1,$r1,#0x100
    269a:	5a 20 50 08 	beqc $r2,#0x50,26aa <_ota_soc_clk_init+0x13e>
    269e:	5a 28 a0 0a 	bnec $r2,#0xa0,26b2 <_ota_soc_clk_init+0x146>
    26a2:	a8 8e       	swi333 $r2,[$r1+#0x18]
    26a4:	46 19 00 00 	sethi $r1,#0x90000
    26a8:	d5 0a       	j8 26bc <_ota_soc_clk_init+0x150>
    26aa:	a8 8e       	swi333 $r2,[$r1+#0x18]
    26ac:	46 18 00 00 	sethi $r1,#0x80000
    26b0:	d5 06       	j8 26bc <_ota_soc_clk_init+0x150>
    26b2:	fa 58       	movpi45 $r2,#0x28
    26b4:	a8 8e       	swi333 $r2,[$r1+#0x18]
    26b6:	46 14 00 00 	sethi $r1,#0x40000
    26ba:	92 00       	nop16
    26bc:	42 00 7c 08 	bset $r0,$r0,#0x1f
    26c0:	46 2c 00 00 	sethi $r2,#0xc0000
    26c4:	14 01 00 82 	swi $r0,[$r2+#0x208]
    26c8:	14 01 00 86 	swi $r0,[$r2+#0x218]
    26cc:	14 01 00 8a 	swi $r0,[$r2+#0x228]
    26d0:	14 01 00 8e 	swi $r0,[$r2+#0x238]
    26d4:	14 01 00 92 	swi $r0,[$r2+#0x248]
    26d8:	14 01 00 96 	swi $r0,[$r2+#0x258]
    26dc:	14 01 00 9a 	swi $r0,[$r2+#0x268]
    26e0:	14 01 00 9e 	swi $r0,[$r2+#0x278]
    26e4:	5a 30 f0 18 	beqc $r3,#0xf0,2714 <_ota_soc_clk_init+0x1a8>
    26e8:	5e f1 80 f1 	sltsi $r15,$r3,#0xf1
    26ec:	e8 08       	beqzs8 26fc <_ota_soc_clk_init+0x190>
    26ee:	5a 30 50 17 	beqc $r3,#0x50,271c <_ota_soc_clk_init+0x1b0>
    26f2:	5a 38 a0 19 	bnec $r3,#0xa0,2724 <_ota_soc_clk_init+0x1b8>
    26f6:	42 10 ec 08 	bset $r1,$r1,#0x1b
    26fa:	d5 17       	j8 2728 <_ota_soc_clk_init+0x1bc>
    26fc:	5a 31 40 08 	beqc $r3,#0x140,270c <_ota_soc_clk_init+0x1a0>
    2700:	5a 39 e0 12 	bnec $r3,#0x1e0,2724 <_ota_soc_clk_init+0x1b8>
    2704:	46 00 c0 00 	sethi $r0,#0xc000
    2708:	48 00 00 04 	j 2710 <_ota_soc_clk_init+0x1a4>
    270c:	46 00 a0 00 	sethi $r0,#0xa000
    2710:	fe 47       	or33 $r1,$r0
    2712:	d5 0b       	j8 2728 <_ota_soc_clk_init+0x1bc>
    2714:	46 00 90 00 	sethi $r0,#0x9000
    2718:	48 ff ff fc 	j 2710 <_ota_soc_clk_init+0x1a4>
    271c:	42 10 e8 08 	bset $r1,$r1,#0x1a
    2720:	48 00 00 04 	j 2728 <_ota_soc_clk_init+0x1bc>
    2724:	42 10 e0 08 	bset $r1,$r1,#0x18
    2728:	58 10 80 c9 	ori $r1,$r1,#0xc9
    272c:	46 3c 00 00 	sethi $r3,#0xc0000
    2730:	14 11 00 15 	swi $r1,[$r2+#0x54]
    2734:	64 00 00 40 	standby wait_done
    2738:	44 00 00 50 	movi $r0,#0x50
    273c:	5a 08 50 0a 	bnec $r0,#0x50,2750 <_ota_soc_clk_init+0x1e4>
    2740:	04 01 80 0f 	lwi $r0,[$r3+#0x3c]
    2744:	66 00 00 0f 	bitci $r0,$r0,#0xf
    2748:	58 00 00 08 	ori $r0,$r0,#0x8
    274c:	48 00 00 08 	j 275c <_ota_soc_clk_init+0x1f0>
    2750:	04 01 80 0f 	lwi $r0,[$r3+#0x3c]
    2754:	66 00 00 0f 	bitci $r0,$r0,#0xf
    2758:	58 00 00 04 	ori $r0,$r0,#0x4
    275c:	14 01 80 0f 	swi $r0,[$r3+#0x3c]
    2760:	dd 9e       	ret5 $lp
    2762:	92 00       	nop16

00002764 <my_memcmp>:
    2764:	c2 12       	beqz38 $r2,2788 <my_memcmp+0x24>
    2766:	a7 00       	lbi333 $r4,[$r0+#0x0]
    2768:	a7 48       	lbi333 $r5,[$r1+#0x0]
    276a:	4c 42 c0 11 	bne $r4,$r5,278c <my_memcmp+0x28>
    276e:	9c c1       	addi333 $r3,$r0,#0x1
    2770:	8c 21       	addi45 $r1,#0x1
    2772:	88 40       	add45 $r2,$r0
    2774:	d5 08       	j8 2784 <my_memcmp+0x20>
    2776:	92 00       	nop16
    2778:	08 41 80 01 	lbi.bi $r4,[$r3],#0x1
    277c:	08 50 80 01 	lbi.bi $r5,[$r1],#0x1
    2780:	4c 42 c0 06 	bne $r4,$r5,278c <my_memcmp+0x28>
    2784:	4c 31 7f fa 	bne $r3,$r2,2778 <my_memcmp+0x14>
    2788:	84 00       	movi55 $r0,#0x0
    278a:	dd 9e       	ret5 $lp
    278c:	9a 25       	sub333 $r0,$r4,$r5
    278e:	dd 9e       	ret5 $lp

00002790 <my_strlen>:
    2790:	20 20 00 00 	lbsi $r2,[$r0+#0x0]
    2794:	9c 41       	addi333 $r1,$r0,#0x1
    2796:	c2 07       	beqz38 $r2,27a4 <my_strlen+0x14>
    2798:	9a c8       	sub333 $r3,$r1,$r0
    279a:	28 20 80 01 	lbsi.bi $r2,[$r1],#0x1
    279e:	ca fd       	bnez38 $r2,2798 <my_strlen+0x8>
    27a0:	80 03       	mov55 $r0,$r3
    27a2:	dd 9e       	ret5 $lp
    27a4:	84 60       	movi55 $r3,#0x0
    27a6:	d5 fd       	j8 27a0 <my_strlen+0x10>

000027a8 <serial_tx>:
    27a8:	46 1c 00 00 	sethi $r1,#0xc0000
    27ac:	14 00 83 00 	swi $r0,[$r1+#0xc00]
    27b0:	dd 9e       	ret5 $lp
    27b2:	92 00       	nop16

000027b4 <body>:
    27b4:	3a 6f ba bc 	smw.adm $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    27b8:	ef c4       	addi10.sp #-60
    27ba:	36 3f 80 00 	fsdi $fd3,[$sp+#0x0]
    27be:	36 4f 80 02 	fsdi $fd4,[$sp+#0x8]
    27c2:	36 5f 80 04 	fsdi $fd5,[$sp+#0x10]
    27c6:	36 6f 80 06 	fsdi $fd6,[$sp+#0x18]
    27ca:	36 7f 80 08 	fsdi $fd7,[$sp+#0x20]
    27ce:	36 8f 80 0a 	fsdi $fd8,[$sp+#0x28]
    27d2:	36 9f 80 0c 	fsdi $fd9,[$sp+#0x30]
    27d6:	46 3d 76 aa 	sethi $r3,#0xd76aa
    27da:	6a 28 80 09 	fmtsr $r2,$fs17
    27de:	50 21 84 78 	addi $r2,$r3,#0x478
    27e2:	46 3e 8c 7b 	sethi $r3,#0xe8c7b
    27e6:	6a 2c 80 09 	fmtsr $r2,$fs25
    27ea:	50 21 87 56 	addi $r2,$r3,#0x756
    27ee:	46 32 42 07 	sethi $r3,#0x24207
    27f2:	6a 2c 00 09 	fmtsr $r2,$fs24
    27f6:	50 21 80 db 	addi $r2,$r3,#0xdb
    27fa:	46 3c 1b dc 	sethi $r3,#0xc1bdc
    27fe:	6a 2b 80 09 	fmtsr $r2,$fs23
    2802:	50 21 8e ee 	addi $r2,$r3,#0xeee
    2806:	46 3f 57 c0 	sethi $r3,#0xf57c0
    280a:	6a 2b 00 09 	fmtsr $r2,$fs22
    280e:	50 21 8f af 	addi $r2,$r3,#0xfaf
    2812:	46 34 78 7c 	sethi $r3,#0x4787c
    2816:	6a 22 80 09 	fmtsr $r2,$fs5
    281a:	50 21 86 2a 	addi $r2,$r3,#0x62a
    281e:	46 3a 83 04 	sethi $r3,#0xa8304
    2822:	6a 22 00 09 	fmtsr $r2,$fs4
    2826:	50 21 86 13 	addi $r2,$r3,#0x613
    282a:	46 3f d4 69 	sethi $r3,#0xfd469
    282e:	6a 21 80 09 	fmtsr $r2,$fs3
    2832:	50 21 85 01 	addi $r2,$r3,#0x501
    2836:	46 36 98 09 	sethi $r3,#0x69809
    283a:	6a 21 00 09 	fmtsr $r2,$fs2
    283e:	50 21 88 d8 	addi $r2,$r3,#0x8d8
    2842:	46 38 b4 4f 	sethi $r3,#0x8b44f
    2846:	6a 20 80 09 	fmtsr $r2,$fs1
    284a:	47 e8 95 cd 	sethi $lp,#0x895cd
    284e:	50 21 87 af 	addi $r2,$r3,#0x7af
    2852:	6a 20 00 09 	fmtsr $r2,$fs0
    2856:	47 c6 b9 01 	sethi $fp,#0x6b901
    285a:	50 2f 07 be 	addi $r2,$lp,#0x7be
    285e:	6a 2f 00 09 	fmtsr $r2,$fs30
    2862:	46 ef d9 87 	sethi $r14,#0xfd987
    2866:	50 2e 01 22 	addi $r2,$fp,#0x122
    286a:	6a 2e 80 09 	fmtsr $r2,$fs29
    286e:	46 da 67 94 	sethi $r13,#0xa6794
    2872:	50 27 01 93 	addi $r2,$r14,#0x193
    2876:	6a 2e 00 09 	fmtsr $r2,$fs28
    287a:	46 c4 9b 40 	sethi $r12,#0x49b40
    287e:	50 26 83 8e 	addi $r2,$r13,#0x38e
    2882:	6a 2d 80 09 	fmtsr $r2,$fs27
    2886:	46 bf 61 e2 	sethi $r11,#0xf61e2
    288a:	50 26 08 21 	addi $r2,$r12,#0x821
    288e:	6a 2d 00 09 	fmtsr $r2,$fs26
    2892:	46 ac 04 0b 	sethi $r10,#0xc040b
    2896:	50 25 85 62 	addi $r2,$r11,#0x562
    289a:	6a 27 00 09 	fmtsr $r2,$fs14
    289e:	46 92 65 e5 	sethi $r9,#0x265e5
    28a2:	50 25 03 40 	addi $r2,$r10,#0x340
    28a6:	6a 26 00 09 	fmtsr $r2,$fs12
    28aa:	46 8e 9b 6c 	sethi $r8,#0xe9b6c
    28ae:	50 24 8a 51 	addi $r2,$r9,#0xa51
    28b2:	6a 25 80 09 	fmtsr $r2,$fs11
    28b6:	46 7d 62 f1 	sethi $r7,#0xd62f1
    28ba:	50 24 07 aa 	addi $r2,$r8,#0x7aa
    28be:	6a 25 00 09 	fmtsr $r2,$fs10
    28c2:	46 60 24 41 	sethi $r6,#0x2441
    28c6:	50 23 80 5d 	addi $r2,$r7,#0x5d
    28ca:	6a 24 80 09 	fmtsr $r2,$fs9
    28ce:	46 fd 8a 1e 	sethi $r15,#0xd8a1e
    28d2:	50 23 04 53 	addi $r2,$r6,#0x453
    28d6:	6a 24 00 09 	fmtsr $r2,$fs8
    28da:	47 9e 7d 3f 	sethi $r25,#0xe7d3f
    28de:	50 27 86 81 	addi $r2,$r15,#0x681
    28e2:	6a 23 80 09 	fmtsr $r2,$fs7
    28e6:	50 2c 8b c8 	addi $r2,$r25,#0xbc8
    28ea:	6a 23 00 09 	fmtsr $r2,$fs6
    28ee:	31 f0 00 02 	flsi $fs31,[$r0+#0x8]
    28f2:	31 20 00 05 	flsi $fs18,[$r0+#0x14]
    28f6:	05 50 00 03 	lwi $r21,[$r0+#0xc]
    28fa:	05 60 00 04 	lwi $r22,[$r0+#0x10]
    28fe:	a6 c9       	lbi333 $r3,[$r1+#0x1]
    2900:	a7 0a       	lbi333 $r4,[$r1+#0x2]
    2902:	a6 88       	lbi333 $r2,[$r1+#0x0]
    2904:	a7 4b       	lbi333 $r5,[$r1+#0x3]
    2906:	40 42 40 08 	slli $r4,$r4,#0x10
    290a:	40 31 a0 08 	slli $r3,$r3,#0x8
    290e:	fe e7       	or33 $r3,$r4
    2910:	fe d7       	or33 $r3,$r2
    2912:	40 42 e0 08 	slli $r4,$r5,#0x18
    2916:	41 81 90 04 	or $r24,$r3,$r4
    291a:	15 80 00 16 	swi $r24,[$r0+#0x58]
    291e:	a6 cd       	lbi333 $r3,[$r1+#0x5]
    2920:	a7 0e       	lbi333 $r4,[$r1+#0x6]
    2922:	a6 8c       	lbi333 $r2,[$r1+#0x4]
    2924:	a7 4f       	lbi333 $r5,[$r1+#0x7]
    2926:	40 42 40 08 	slli $r4,$r4,#0x10
    292a:	40 31 a0 08 	slli $r3,$r3,#0x8
    292e:	fe e7       	or33 $r3,$r4
    2930:	fe d7       	or33 $r3,$r2
    2932:	40 42 e0 08 	slli $r4,$r5,#0x18
    2936:	40 b1 90 04 	or $r11,$r3,$r4
    293a:	14 b0 00 17 	swi $r11,[$r0+#0x5c]
    293e:	00 30 80 09 	lbi $r3,[$r1+#0x9]
    2942:	00 50 80 0a 	lbi $r5,[$r1+#0xa]
    2946:	00 20 80 08 	lbi $r2,[$r1+#0x8]
    294a:	00 40 80 0b 	lbi $r4,[$r1+#0xb]
    294e:	40 52 c0 08 	slli $r5,$r5,#0x10
    2952:	40 31 a0 08 	slli $r3,$r3,#0x8
    2956:	fe ef       	or33 $r3,$r5
    2958:	fe d7       	or33 $r3,$r2
    295a:	40 52 60 08 	slli $r5,$r4,#0x18
    295e:	40 71 94 04 	or $r7,$r3,$r5
    2962:	14 70 00 18 	swi $r7,[$r0+#0x60]
    2966:	00 30 80 0d 	lbi $r3,[$r1+#0xd]
    296a:	00 40 80 0e 	lbi $r4,[$r1+#0xe]
    296e:	00 20 80 0c 	lbi $r2,[$r1+#0xc]
    2972:	00 50 80 0f 	lbi $r5,[$r1+#0xf]
    2976:	40 42 40 08 	slli $r4,$r4,#0x10
    297a:	40 31 a0 08 	slli $r3,$r3,#0x8
    297e:	fe e7       	or33 $r3,$r4
    2980:	fe d7       	or33 $r3,$r2
    2982:	40 42 e0 08 	slli $r4,$r5,#0x18
    2986:	40 d1 90 04 	or $r13,$r3,$r4
    298a:	14 d0 00 19 	swi $r13,[$r0+#0x64]
    298e:	00 30 80 11 	lbi $r3,[$r1+#0x11]
    2992:	00 50 80 12 	lbi $r5,[$r1+#0x12]
    2996:	00 20 80 10 	lbi $r2,[$r1+#0x10]
    299a:	40 52 c0 08 	slli $r5,$r5,#0x10
    299e:	40 31 a0 08 	slli $r3,$r3,#0x8
    29a2:	00 40 80 13 	lbi $r4,[$r1+#0x13]
    29a6:	fe ef       	or33 $r3,$r5
    29a8:	fe d7       	or33 $r3,$r2
    29aa:	6a 29 00 01 	fmfsr $r2,$fs18
    29ae:	40 52 60 08 	slli $r5,$r4,#0x18
    29b2:	40 41 94 04 	or $r4,$r3,$r5
    29b6:	6b 0c 80 01 	fmfsr $r16,$fs25
    29ba:	40 31 58 03 	xor $r3,$r2,$r22
    29be:	6a 2f 80 01 	fmfsr $r2,$fs31
    29c2:	14 40 00 1a 	swi $r4,[$r0+#0x68]
    29c6:	89 82       	add45 $r16,$r2
    29c8:	6a 29 00 01 	fmfsr $r2,$fs18
    29cc:	00 50 80 16 	lbi $r5,[$r1+#0x16]
    29d0:	01 30 80 15 	lbi $r19,[$r1+#0x15]
    29d4:	40 31 d4 02 	and $r3,$r3,$r21
    29d8:	fe d5       	xor33 $r3,$r2
    29da:	00 60 80 14 	lbi $r6,[$r1+#0x14]
    29de:	00 20 80 17 	lbi $r2,[$r1+#0x17]
    29e2:	88 70       	add45 $r3,$r16
    29e4:	41 39 a0 08 	slli $r19,$r19,#0x8
    29e8:	41 02 c0 08 	slli $r16,$r5,#0x10
    29ec:	40 59 c0 04 	or $r5,$r19,$r16
    29f0:	ff 77       	or33 $r5,$r6
    29f2:	41 01 60 08 	slli $r16,$r2,#0x18
    29f6:	88 78       	add45 $r3,$r24
    29f8:	40 f2 c0 04 	or $r15,$r5,$r16
    29fc:	6a 2c 00 01 	fmfsr $r2,$fs24
    2a00:	6a 59 00 01 	fmfsr $r5,$fs18
    2a04:	40 31 e4 0b 	rotri $r3,$r3,#0x19
    2a08:	88 75       	add45 $r3,$r21
    2a0a:	41 0b 54 03 	xor $r16,$r22,$r21
    2a0e:	14 f0 00 1b 	swi $r15,[$r0+#0x6c]
    2a12:	41 32 88 00 	add $r19,$r5,$r2
    2a16:	01 10 80 19 	lbi $r17,[$r1+#0x19]
    2a1a:	40 51 c0 02 	and $r5,$r3,$r16
    2a1e:	01 20 80 1a 	lbi $r18,[$r1+#0x1a]
    2a22:	41 02 d8 03 	xor $r16,$r5,$r22
    2a26:	40 59 ac 00 	add $r5,$r19,$r11
    2a2a:	88 b0       	add45 $r5,$r16
    2a2c:	41 29 40 08 	slli $r18,$r18,#0x10
    2a30:	41 18 a0 08 	slli $r17,$r17,#0x8
    2a34:	00 60 80 18 	lbi $r6,[$r1+#0x18]
    2a38:	41 18 c8 04 	or $r17,$r17,$r18
    2a3c:	00 20 80 1b 	lbi $r2,[$r1+#0x1b]
    2a40:	6b 2b 80 01 	fmfsr $r18,$fs23
    2a44:	40 52 d0 0b 	rotri $r5,$r5,#0x14
    2a48:	88 a3       	add45 $r5,$r3
    2a4a:	41 01 d4 03 	xor $r16,$r3,$r21
    2a4e:	41 3b 48 00 	add $r19,$r22,$r18
    2a52:	41 18 98 04 	or $r17,$r17,$r6
    2a56:	41 22 c0 02 	and $r18,$r5,$r16
    2a5a:	41 01 60 08 	slli $r16,$r2,#0x18
    2a5e:	40 98 c0 04 	or $r9,$r17,$r16
    2a62:	41 09 54 03 	xor $r16,$r18,$r21
    2a66:	41 29 9c 00 	add $r18,$r19,$r7
    2a6a:	14 90 00 1c 	swi $r9,[$r0+#0x70]
    2a6e:	89 d0       	add45 $r18,$r16
    2a70:	01 10 80 1d 	lbi $r17,[$r1+#0x1d]
    2a74:	01 40 80 1e 	lbi $r20,[$r1+#0x1e]
    2a78:	41 29 3c 0b 	rotri $r18,$r18,#0xf
    2a7c:	6b 3b 00 01 	fmfsr $r19,$fs22
    2a80:	89 c5       	add45 $r18,$r5
    2a82:	41 02 8c 03 	xor $r16,$r5,$r3
    2a86:	00 60 80 1c 	lbi $r6,[$r1+#0x1c]
    2a8a:	00 20 80 1f 	lbi $r2,[$r1+#0x1f]
    2a8e:	89 f5       	add45 $r19,$r21
    2a90:	41 09 40 02 	and $r16,$r18,$r16
    2a94:	41 4a 40 08 	slli $r20,$r20,#0x10
    2a98:	41 18 a0 08 	slli $r17,$r17,#0x8
    2a9c:	41 08 0c 03 	xor $r16,$r16,$r3
    2aa0:	41 18 d0 04 	or $r17,$r17,$r20
    2aa4:	89 ed       	add45 $r19,$r13
    2aa6:	41 18 98 04 	or $r17,$r17,$r6
    2aaa:	89 f0       	add45 $r19,$r16
    2aac:	41 01 60 08 	slli $r16,$r2,#0x18
    2ab0:	41 e8 c0 04 	or $lp,$r17,$r16
    2ab4:	41 39 a8 0b 	rotri $r19,$r19,#0xa
    2ab8:	6a 22 80 01 	fmfsr $r2,$fs5
    2abc:	15 e0 00 1d 	swi $lp,[$r0+#0x74]
    2ac0:	89 f2       	add45 $r19,$r18
    2ac2:	41 09 14 03 	xor $r16,$r18,$r5
    2ac6:	01 40 80 22 	lbi $r20,[$r1+#0x22]
    2aca:	01 10 80 21 	lbi $r17,[$r1+#0x21]
    2ace:	88 44       	add45 $r2,$r4
    2ad0:	41 09 c0 02 	and $r16,$r19,$r16
    2ad4:	41 08 14 03 	xor $r16,$r16,$r5
    2ad8:	88 62       	add45 $r3,$r2
    2ada:	00 20 80 23 	lbi $r2,[$r1+#0x23]
    2ade:	00 60 80 20 	lbi $r6,[$r1+#0x20]
    2ae2:	88 70       	add45 $r3,$r16
    2ae4:	41 18 a0 08 	slli $r17,$r17,#0x8
    2ae8:	41 0a 40 08 	slli $r16,$r20,#0x10
    2aec:	41 18 c0 04 	or $r17,$r17,$r16
    2af0:	41 41 60 08 	slli $r20,$r2,#0x18
    2af4:	40 31 e4 0b 	rotri $r3,$r3,#0x19
    2af8:	6a 22 00 01 	fmfsr $r2,$fs4
    2afc:	88 73       	add45 $r3,$r19
    2afe:	41 09 c8 03 	xor $r16,$r19,$r18
    2b02:	41 18 98 04 	or $r17,$r17,$r6
    2b06:	40 a8 d0 04 	or $r10,$r17,$r20
    2b0a:	41 01 c0 02 	and $r16,$r3,$r16
    2b0e:	41 47 88 00 	add $r20,$r15,$r2
    2b12:	14 a0 00 1e 	swi $r10,[$r0+#0x78]
    2b16:	41 08 48 03 	xor $r16,$r16,$r18
    2b1a:	41 4a 14 00 	add $r20,$r20,$r5
    2b1e:	01 10 80 25 	lbi $r17,[$r1+#0x25]
    2b22:	00 50 80 26 	lbi $r5,[$r1+#0x26]
    2b26:	41 4a 40 00 	add $r20,$r20,$r16
    2b2a:	41 4a 50 0b 	rotri $r20,$r20,#0x14
    2b2e:	6b 91 80 01 	fmfsr $r25,$fs3
    2b32:	00 60 80 24 	lbi $r6,[$r1+#0x24]
    2b36:	00 20 80 27 	lbi $r2,[$r1+#0x27]
    2b3a:	41 4a 0c 00 	add $r20,$r20,$r3
    2b3e:	41 01 cc 03 	xor $r16,$r3,$r19
    2b42:	40 52 c0 08 	slli $r5,$r5,#0x10
    2b46:	41 18 a0 08 	slli $r17,$r17,#0x8
    2b4a:	41 94 e4 00 	add $r25,$r9,$r25
    2b4e:	41 0a 40 02 	and $r16,$r20,$r16
    2b52:	41 18 94 04 	or $r17,$r17,$r5
    2b56:	41 08 4c 03 	xor $r16,$r16,$r19
    2b5a:	40 51 60 08 	slli $r5,$r2,#0x18
    2b5e:	89 d9       	add45 $r18,$r25
    2b60:	41 18 98 04 	or $r17,$r17,$r6
    2b64:	40 68 94 04 	or $r6,$r17,$r5
    2b68:	89 d0       	add45 $r18,$r16
    2b6a:	14 60 00 1f 	swi $r6,[$r0+#0x7c]
    2b6e:	6a 21 00 01 	fmfsr $r2,$fs2
    2b72:	41 29 3c 0b 	rotri $r18,$r18,#0xf
    2b76:	89 d4       	add45 $r18,$r20
    2b78:	00 80 80 29 	lbi $r8,[$r1+#0x29]
    2b7c:	01 00 80 2a 	lbi $r16,[$r1+#0x2a]
    2b80:	40 5a 0c 03 	xor $r5,$r20,$r3
    2b84:	41 1f 08 00 	add $r17,$lp,$r2
    2b88:	40 59 14 02 	and $r5,$r18,$r5
    2b8c:	01 90 80 28 	lbi $r25,[$r1+#0x28]
    2b90:	00 20 80 2b 	lbi $r2,[$r1+#0x2b]
    2b94:	ff 5d       	xor33 $r5,$r3
    2b96:	89 b3       	add45 $r17,$r19
    2b98:	41 08 40 08 	slli $r16,$r16,#0x10
    2b9c:	41 34 20 08 	slli $r19,$r8,#0x8
    2ba0:	89 a5       	add45 $r17,$r5
    2ba2:	40 59 c0 04 	or $r5,$r19,$r16
    2ba6:	40 52 e4 04 	or $r5,$r5,$r25
    2baa:	41 01 60 08 	slli $r16,$r2,#0x18
    2bae:	40 c2 c0 04 	or $r12,$r5,$r16
    2bb2:	6a 20 80 01 	fmfsr $r2,$fs1
    2bb6:	41 18 a8 0b 	rotri $r17,$r17,#0xa
    2bba:	14 c0 00 20 	swi $r12,[$r0+#0x80]
    2bbe:	89 b2       	add45 $r17,$r18
    2bc0:	41 39 50 03 	xor $r19,$r18,$r20
    2bc4:	00 50 80 2e 	lbi $r5,[$r1+#0x2e]
    2bc8:	41 05 08 00 	add $r16,$r10,$r2
    2bcc:	41 38 cc 02 	and $r19,$r17,$r19
    2bd0:	00 20 80 2d 	lbi $r2,[$r1+#0x2d]
    2bd4:	41 39 d0 03 	xor $r19,$r19,$r20
    2bd8:	89 83       	add45 $r16,$r3
    2bda:	89 93       	add45 $r16,$r19
    2bdc:	40 21 20 08 	slli $r2,$r2,#0x8
    2be0:	41 32 c0 08 	slli $r19,$r5,#0x10
    2be4:	00 80 80 2c 	lbi $r8,[$r1+#0x2c]
    2be8:	01 90 80 2f 	lbi $r25,[$r1+#0x2f]
    2bec:	41 31 4c 04 	or $r19,$r2,$r19
    2bf0:	41 08 64 0b 	rotri $r16,$r16,#0x19
    2bf4:	6a 20 00 01 	fmfsr $r2,$fs0
    2bf8:	89 91       	add45 $r16,$r17
    2bfa:	40 38 c8 03 	xor $r3,$r17,$r18
    2bfe:	41 39 a0 04 	or $r19,$r19,$r8
    2c02:	88 46       	add45 $r2,$r6
    2c04:	40 38 0c 02 	and $r3,$r16,$r3
    2c08:	40 5c e0 08 	slli $r5,$r25,#0x18
    2c0c:	40 59 94 04 	or $r5,$r19,$r5
    2c10:	40 31 c8 03 	xor $r3,$r3,$r18
    2c14:	41 41 50 00 	add $r20,$r2,$r20
    2c18:	14 50 00 21 	swi $r5,[$r0+#0x84]
    2c1c:	41 4a 0c 00 	add $r20,$r20,$r3
    2c20:	00 80 80 31 	lbi $r8,[$r1+#0x31]
    2c24:	01 30 80 32 	lbi $r19,[$r1+#0x32]
    2c28:	41 4a 50 0b 	rotri $r20,$r20,#0x14
    2c2c:	41 4a 40 00 	add $r20,$r20,$r16
    2c30:	40 38 44 03 	xor $r3,$r16,$r17
    2c34:	44 ef 5b b1 	movi $r14,#-42063
    2c38:	01 90 80 30 	lbi $r25,[$r1+#0x30]
    2c3c:	00 20 80 33 	lbi $r2,[$r1+#0x33]
    2c40:	40 e6 38 00 	add $r14,$r12,$r14
    2c44:	40 3a 0c 02 	and $r3,$r20,$r3
    2c48:	40 84 20 08 	slli $r8,$r8,#0x8
    2c4c:	41 39 c0 08 	slli $r19,$r19,#0x10
    2c50:	40 31 c4 03 	xor $r3,$r3,$r17
    2c54:	89 ce       	add45 $r18,$r14
    2c56:	41 34 4c 04 	or $r19,$r8,$r19
    2c5a:	41 39 e4 04 	or $r19,$r19,$r25
    2c5e:	89 c3       	add45 $r18,$r3
    2c60:	40 31 60 08 	slli $r3,$r2,#0x18
    2c64:	40 e9 8c 04 	or $r14,$r19,$r3
    2c68:	41 29 3c 0b 	rotri $r18,$r18,#0xf
    2c6c:	6a 2f 00 01 	fmfsr $r2,$fs30
    2c70:	89 d4       	add45 $r18,$r20
    2c72:	41 3a 40 03 	xor $r19,$r20,$r16
    2c76:	14 e0 00 22 	swi $r14,[$r0+#0x88]
    2c7a:	00 80 80 35 	lbi $r8,[$r1+#0x35]
    2c7e:	88 45       	add45 $r2,$r5
    2c80:	00 30 80 36 	lbi $r3,[$r1+#0x36]
    2c84:	41 39 4c 02 	and $r19,$r18,$r19
    2c88:	41 39 c0 03 	xor $r19,$r19,$r16
    2c8c:	89 a2       	add45 $r17,$r2
    2c8e:	01 90 80 37 	lbi $r25,[$r1+#0x37]
    2c92:	00 20 80 34 	lbi $r2,[$r1+#0x34]
    2c96:	89 b3       	add45 $r17,$r19
    2c98:	40 84 20 08 	slli $r8,$r8,#0x8
    2c9c:	41 31 c0 08 	slli $r19,$r3,#0x10
    2ca0:	40 34 4c 04 	or $r3,$r8,$r19
    2ca4:	fe 9f       	or33 $r2,$r3
    2ca6:	40 3c e0 08 	slli $r3,$r25,#0x18
    2caa:	fe d7       	or33 $r3,$r2
    2cac:	14 30 00 23 	swi $r3,[$r0+#0x8c]
    2cb0:	01 c0 80 39 	lbi $fp,[$r1+#0x39]
    2cb4:	6a 2e 80 01 	fmfsr $r2,$fs29
    2cb8:	41 ce 20 08 	slli $fp,$fp,#0x8
    2cbc:	00 80 80 3a 	lbi $r8,[$r1+#0x3a]
    2cc0:	88 4e       	add45 $r2,$r14
    2cc2:	01 90 80 38 	lbi $r25,[$r1+#0x38]
    2cc6:	82 fc       	mov55 $r23,$fp
    2cc8:	89 82       	add45 $r16,$r2
    2cca:	41 18 a8 0b 	rotri $r17,$r17,#0xa
    2cce:	00 20 80 3b 	lbi $r2,[$r1+#0x3b]
    2cd2:	40 84 40 08 	slli $r8,$r8,#0x10
    2cd6:	6b ce 00 01 	fmfsr $fp,$fs28
    2cda:	89 b2       	add45 $r17,$r18
    2cdc:	41 39 50 03 	xor $r19,$r18,$r20
    2ce0:	40 8b a0 04 	or $r8,$r23,$r8
    2ce4:	41 c1 f0 00 	add $fp,$r3,$fp
    2ce8:	41 94 64 04 	or $r25,$r8,$r25
    2cec:	41 38 cc 02 	and $r19,$r17,$r19
    2cf0:	40 21 60 08 	slli $r2,$r2,#0x18
    2cf4:	41 39 d0 03 	xor $r19,$r19,$r20
    2cf8:	41 4e 50 00 	add $r20,$fp,$r20
    2cfc:	41 cc 88 04 	or $fp,$r25,$r2
    2d00:	15 c0 00 24 	swi $fp,[$r0+#0x90]
    2d04:	00 20 80 3d 	lbi $r2,[$r1+#0x3d]
    2d08:	6a 27 80 09 	fmtsr $r2,$fs15
    2d0c:	6a 2d 80 01 	fmfsr $r2,$fs27
    2d10:	89 f0       	add45 $r19,$r16
    2d12:	88 5c       	add45 $r2,$fp
    2d14:	41 39 e4 0b 	rotri $r19,$r19,#0x19
    2d18:	89 f1       	add45 $r19,$r17
    2d1a:	41 08 c8 03 	xor $r16,$r17,$r18
    2d1e:	41 09 c0 02 	and $r16,$r19,$r16
    2d22:	41 08 48 03 	xor $r16,$r16,$r18
    2d26:	41 4a 40 00 	add $r20,$r20,$r16
    2d2a:	41 4a 50 0b 	rotri $r20,$r20,#0x14
    2d2e:	41 4a 4c 00 	add $r20,$r20,$r19
    2d32:	00 80 80 3e 	lbi $r8,[$r1+#0x3e]
    2d36:	41 09 c4 03 	xor $r16,$r19,$r17
    2d3a:	89 c2       	add45 $r18,$r2
    2d3c:	6b 77 80 01 	fmfsr $r23,$fs15
    2d40:	41 0a 40 02 	and $r16,$r20,$r16
    2d44:	01 90 80 3f 	lbi $r25,[$r1+#0x3f]
    2d48:	00 20 80 3c 	lbi $r2,[$r1+#0x3c]
    2d4c:	41 08 44 03 	xor $r16,$r16,$r17
    2d50:	40 84 40 08 	slli $r8,$r8,#0x10
    2d54:	41 7b a0 08 	slli $r23,$r23,#0x8
    2d58:	89 d0       	add45 $r18,$r16
    2d5a:	41 0b a0 04 	or $r16,$r23,$r8
    2d5e:	40 28 08 04 	or $r2,$r16,$r2
    2d62:	41 0c e0 08 	slli $r16,$r25,#0x18
    2d66:	41 91 40 04 	or $r25,$r2,$r16
    2d6a:	41 29 3c 0b 	rotri $r18,$r18,#0xf
    2d6e:	6a 2d 00 01 	fmfsr $r2,$fs26
    2d72:	89 d4       	add45 $r18,$r20
    2d74:	41 0a 4c 03 	xor $r16,$r20,$r19
    2d78:	88 59       	add45 $r2,$r25
    2d7a:	41 09 40 02 	and $r16,$r18,$r16
    2d7e:	41 08 4c 03 	xor $r16,$r16,$r19
    2d82:	89 a2       	add45 $r17,$r2
    2d84:	89 b0       	add45 $r17,$r16
    2d86:	41 18 a8 0b 	rotri $r17,$r17,#0xa
    2d8a:	89 b2       	add45 $r17,$r18
    2d8c:	6a 27 00 01 	fmfsr $r2,$fs14
    2d90:	41 08 c8 03 	xor $r16,$r17,$r18
    2d94:	88 4b       	add45 $r2,$r11
    2d96:	41 08 50 02 	and $r16,$r16,$r20
    2d9a:	89 e2       	add45 $r19,$r2
    2d9c:	41 08 48 03 	xor $r16,$r16,$r18
    2da0:	89 93       	add45 $r16,$r19
    2da2:	41 08 6c 0b 	rotri $r16,$r16,#0x1b
    2da6:	89 91       	add45 $r16,$r17
    2da8:	6a 26 00 01 	fmfsr $r2,$fs12
    2dac:	41 38 44 03 	xor $r19,$r16,$r17
    2db0:	88 49       	add45 $r2,$r9
    2db2:	41 39 c8 02 	and $r19,$r19,$r18
    2db6:	41 39 c4 03 	xor $r19,$r19,$r17
    2dba:	41 41 50 00 	add $r20,$r2,$r20
    2dbe:	41 4a 4c 00 	add $r20,$r20,$r19
    2dc2:	41 4a 5c 0b 	rotri $r20,$r20,#0x17
    2dc6:	41 4a 40 00 	add $r20,$r20,$r16
    2dca:	6a 25 80 01 	fmfsr $r2,$fs11
    2dce:	41 3a 40 03 	xor $r19,$r20,$r16
    2dd2:	88 45       	add45 $r2,$r5
    2dd4:	41 39 c4 02 	and $r19,$r19,$r17
    2dd8:	41 39 c0 03 	xor $r19,$r19,$r16
    2ddc:	89 c2       	add45 $r18,$r2
    2dde:	89 d3       	add45 $r18,$r19
    2de0:	41 29 48 0b 	rotri $r18,$r18,#0x12
    2de4:	89 d4       	add45 $r18,$r20
    2de6:	6a 25 00 01 	fmfsr $r2,$fs10
    2dea:	41 39 50 03 	xor $r19,$r18,$r20
    2dee:	88 58       	add45 $r2,$r24
    2df0:	41 39 c0 02 	and $r19,$r19,$r16
    2df4:	41 39 d0 03 	xor $r19,$r19,$r20
    2df8:	89 a2       	add45 $r17,$r2
    2dfa:	89 b3       	add45 $r17,$r19
    2dfc:	41 18 b0 0b 	rotri $r17,$r17,#0xc
    2e00:	89 b2       	add45 $r17,$r18
    2e02:	6a 24 80 01 	fmfsr $r2,$fs9
    2e06:	41 38 c8 03 	xor $r19,$r17,$r18
    2e0a:	88 4f       	add45 $r2,$r15
    2e0c:	41 39 d0 02 	and $r19,$r19,$r20
    2e10:	41 39 c8 03 	xor $r19,$r19,$r18
    2e14:	89 82       	add45 $r16,$r2
    2e16:	89 93       	add45 $r16,$r19
    2e18:	41 08 6c 0b 	rotri $r16,$r16,#0x1b
    2e1c:	89 91       	add45 $r16,$r17
    2e1e:	6a 24 00 01 	fmfsr $r2,$fs8
    2e22:	41 38 44 03 	xor $r19,$r16,$r17
    2e26:	88 4c       	add45 $r2,$r12
    2e28:	41 39 c8 02 	and $r19,$r19,$r18
    2e2c:	41 41 50 00 	add $r20,$r2,$r20
    2e30:	41 39 c4 03 	xor $r19,$r19,$r17
    2e34:	89 f4       	add45 $r19,$r20
    2e36:	41 39 dc 0b 	rotri $r19,$r19,#0x17
    2e3a:	89 f0       	add45 $r19,$r16
    2e3c:	6a 23 80 01 	fmfsr $r2,$fs7
    2e40:	41 49 c0 03 	xor $r20,$r19,$r16
    2e44:	88 59       	add45 $r2,$r25
    2e46:	41 4a 44 02 	and $r20,$r20,$r17
    2e4a:	41 4a 40 03 	xor $r20,$r20,$r16
    2e4e:	89 c2       	add45 $r18,$r2
    2e50:	89 d4       	add45 $r18,$r20
    2e52:	41 29 48 0b 	rotri $r18,$r18,#0x12
    2e56:	89 d3       	add45 $r18,$r19
    2e58:	6a 23 00 01 	fmfsr $r2,$fs6
    2e5c:	41 49 4c 03 	xor $r20,$r18,$r19
    2e60:	88 44       	add45 $r2,$r4
    2e62:	41 4a 40 02 	and $r20,$r20,$r16
    2e66:	41 4a 4c 03 	xor $r20,$r20,$r19
    2e6a:	89 a2       	add45 $r17,$r2
    2e6c:	89 b4       	add45 $r17,$r20
    2e6e:	41 18 b0 0b 	rotri $r17,$r17,#0xc
    2e72:	89 b2       	add45 $r17,$r18
    2e74:	46 22 1e 1c 	sethi $r2,#0x21e1c
    2e78:	41 48 c8 03 	xor $r20,$r17,$r18
    2e7c:	50 21 0d e6 	addi $r2,$r2,#0xde6
    2e80:	88 46       	add45 $r2,$r6
    2e82:	41 4a 4c 02 	and $r20,$r20,$r19
    2e86:	41 4a 48 03 	xor $r20,$r20,$r18
    2e8a:	89 82       	add45 $r16,$r2
    2e8c:	89 94       	add45 $r16,$r20
    2e8e:	41 08 6c 0b 	rotri $r16,$r16,#0x1b
    2e92:	89 91       	add45 $r16,$r17
    2e94:	46 2c 33 70 	sethi $r2,#0xc3370
    2e98:	41 48 44 03 	xor $r20,$r16,$r17
    2e9c:	50 21 07 d6 	addi $r2,$r2,#0x7d6
    2ea0:	88 5c       	add45 $r2,$fp
    2ea2:	41 4a 48 02 	and $r20,$r20,$r18
    2ea6:	89 e2       	add45 $r19,$r2
    2ea8:	41 4a 44 03 	xor $r20,$r20,$r17
    2eac:	41 49 d0 00 	add $r20,$r19,$r20
    2eb0:	41 4a 5c 0b 	rotri $r20,$r20,#0x17
    2eb4:	41 4a 40 00 	add $r20,$r20,$r16
    2eb8:	46 2f 4d 50 	sethi $r2,#0xf4d50
    2ebc:	41 3a 40 03 	xor $r19,$r20,$r16
    2ec0:	50 21 0d 87 	addi $r2,$r2,#0xd87
    2ec4:	88 4d       	add45 $r2,$r13
    2ec6:	41 39 c4 02 	and $r19,$r19,$r17
    2eca:	89 c2       	add45 $r18,$r2
    2ecc:	41 39 c0 03 	xor $r19,$r19,$r16
    2ed0:	89 f2       	add45 $r19,$r18
    2ed2:	41 39 c8 0b 	rotri $r19,$r19,#0x12
    2ed6:	89 f4       	add45 $r19,$r20
    2ed8:	46 24 55 a1 	sethi $r2,#0x455a1
    2edc:	41 29 d0 03 	xor $r18,$r19,$r20
    2ee0:	50 21 04 ed 	addi $r2,$r2,#0x4ed
    2ee4:	88 4a       	add45 $r2,$r10
    2ee6:	41 29 40 02 	and $r18,$r18,$r16
    2eea:	89 a2       	add45 $r17,$r2
    2eec:	41 29 50 03 	xor $r18,$r18,$r20
    2ef0:	89 d1       	add45 $r18,$r17
    2ef2:	41 29 30 0b 	rotri $r18,$r18,#0xc
    2ef6:	89 d3       	add45 $r18,$r19
    2ef8:	46 2a 9e 3e 	sethi $r2,#0xa9e3e
    2efc:	41 19 4c 03 	xor $r17,$r18,$r19
    2f00:	50 21 09 05 	addi $r2,$r2,#0x905
    2f04:	88 43       	add45 $r2,$r3
    2f06:	41 18 d0 02 	and $r17,$r17,$r20
    2f0a:	89 82       	add45 $r16,$r2
    2f0c:	41 18 cc 03 	xor $r17,$r17,$r19
    2f10:	89 b0       	add45 $r17,$r16
    2f12:	41 18 ec 0b 	rotri $r17,$r17,#0x1b
    2f16:	89 b2       	add45 $r17,$r18
    2f18:	46 2f ce fa 	sethi $r2,#0xfcefa
    2f1c:	41 08 c8 03 	xor $r16,$r17,$r18
    2f20:	50 21 03 f8 	addi $r2,$r2,#0x3f8
    2f24:	88 47       	add45 $r2,$r7
    2f26:	41 08 4c 02 	and $r16,$r16,$r19
    2f2a:	41 41 50 00 	add $r20,$r2,$r20
    2f2e:	41 08 48 03 	xor $r16,$r16,$r18
    2f32:	89 94       	add45 $r16,$r20
    2f34:	41 08 5c 0b 	rotri $r16,$r16,#0x17
    2f38:	89 91       	add45 $r16,$r17
    2f3a:	46 26 76 f0 	sethi $r2,#0x676f0
    2f3e:	41 48 44 03 	xor $r20,$r16,$r17
    2f42:	50 21 02 d9 	addi $r2,$r2,#0x2d9
    2f46:	88 5e       	add45 $r2,$lp
    2f48:	41 4a 48 02 	and $r20,$r20,$r18
    2f4c:	41 4a 44 03 	xor $r20,$r20,$r17
    2f50:	89 e2       	add45 $r19,$r2
    2f52:	89 f4       	add45 $r19,$r20
    2f54:	41 39 c8 0b 	rotri $r19,$r19,#0x12
    2f58:	89 f0       	add45 $r19,$r16
    2f5a:	46 28 d2 a4 	sethi $r2,#0x8d2a4
    2f5e:	41 49 c0 03 	xor $r20,$r19,$r16
    2f62:	50 21 0c 8a 	addi $r2,$r2,#0xc8a
    2f66:	88 4e       	add45 $r2,$r14
    2f68:	41 4a 44 02 	and $r20,$r20,$r17
    2f6c:	41 4a 40 03 	xor $r20,$r20,$r16
    2f70:	89 c2       	add45 $r18,$r2
    2f72:	89 d4       	add45 $r18,$r20
    2f74:	41 29 30 0b 	rotri $r18,$r18,#0xc
    2f78:	89 d3       	add45 $r18,$r19
    2f7a:	44 2a 39 42 	movi $r2,#-378558
    2f7e:	41 49 4c 03 	xor $r20,$r18,$r19
    2f82:	88 4f       	add45 $r2,$r15
    2f84:	89 a2       	add45 $r17,$r2
    2f86:	40 2a 40 03 	xor $r2,$r20,$r16
    2f8a:	89 a2       	add45 $r17,$r2
    2f8c:	41 18 f0 0b 	rotri $r17,$r17,#0x1c
    2f90:	40 88 c8 00 	add $r8,$r17,$r18
    2f94:	47 18 77 1f 	sethi $r17,#0x8771f
    2f98:	51 18 86 81 	addi $r17,$r17,#0x681
    2f9c:	89 aa       	add45 $r17,$r10
    2f9e:	89 91       	add45 $r16,$r17
    2fa0:	41 44 50 03 	xor $r20,$r8,$r20
    2fa4:	41 48 50 00 	add $r20,$r16,$r20
    2fa8:	41 4a 54 0b 	rotri $r20,$r20,#0x15
    2fac:	47 06 d9 d6 	sethi $r16,#0x6d9d6
    2fb0:	41 4a 20 00 	add $r20,$r20,$r8
    2fb4:	51 08 01 22 	addi $r16,$r16,#0x122
    2fb8:	41 1a 20 03 	xor $r17,$r20,$r8
    2fbc:	89 85       	add45 $r16,$r5
    2fbe:	89 f0       	add45 $r19,$r16
    2fc0:	41 08 c8 03 	xor $r16,$r17,$r18
    2fc4:	89 f0       	add45 $r19,$r16
    2fc6:	47 0f de 53 	sethi $r16,#0xfde53
    2fca:	41 39 c0 0b 	rotri $r19,$r19,#0x10
    2fce:	51 08 08 0c 	addi $r16,$r16,#0x80c
    2fd2:	40 29 d0 00 	add $r2,$r19,$r20
    2fd6:	89 9c       	add45 $r16,$fp
    2fd8:	41 11 44 03 	xor $r17,$r2,$r17
    2fdc:	89 92       	add45 $r16,$r18
    2fde:	89 91       	add45 $r16,$r17
    2fe0:	41 08 24 0b 	rotri $r16,$r16,#0x9
    2fe4:	41 38 08 00 	add $r19,$r16,$r2
    2fe8:	47 0a 4b ee 	sethi $r16,#0xa4bee
    2fec:	51 08 0a 44 	addi $r16,$r16,#0xa44
    2ff0:	41 19 88 03 	xor $r17,$r19,$r2
    2ff4:	89 8b       	add45 $r16,$r11
    2ff6:	41 28 d0 03 	xor $r18,$r17,$r20
    2ffa:	89 88       	add45 $r16,$r8
    2ffc:	89 92       	add45 $r16,$r18
    2ffe:	41 08 70 0b 	rotri $r16,$r16,#0x1c
    3002:	40 88 4c 00 	add $r8,$r16,$r19
    3006:	47 04 bd ec 	sethi $r16,#0x4bdec
    300a:	51 08 0f a9 	addi $r16,$r16,#0xfa9
    300e:	89 84       	add45 $r16,$r4
    3010:	41 14 44 03 	xor $r17,$r8,$r17
    3014:	41 48 50 00 	add $r20,$r16,$r20
    3018:	41 4a 44 00 	add $r20,$r20,$r17
    301c:	41 4a 54 0b 	rotri $r20,$r20,#0x15
    3020:	47 0f 6b b4 	sethi $r16,#0xf6bb4
    3024:	41 2a 20 00 	add $r18,$r20,$r8
    3028:	51 08 0b 60 	addi $r16,$r16,#0xb60
    302c:	41 19 20 03 	xor $r17,$r18,$r8
    3030:	89 9e       	add45 $r16,$lp
    3032:	41 48 cc 03 	xor $r20,$r17,$r19
    3036:	89 82       	add45 $r16,$r2
    3038:	89 94       	add45 $r16,$r20
    303a:	41 08 40 0b 	rotri $r16,$r16,#0x10
    303e:	40 28 48 00 	add $r2,$r16,$r18
    3042:	47 0b eb fb 	sethi $r16,#0xbebfb
    3046:	51 08 0c 70 	addi $r16,$r16,#0xc70
    304a:	89 8c       	add45 $r16,$r12
    304c:	41 11 44 03 	xor $r17,$r2,$r17
    3050:	89 93       	add45 $r16,$r19
    3052:	89 91       	add45 $r16,$r17
    3054:	41 08 24 0b 	rotri $r16,$r16,#0x9
    3058:	41 38 08 00 	add $r19,$r16,$r2
    305c:	47 02 89 b7 	sethi $r16,#0x289b7
    3060:	51 08 0e c6 	addi $r16,$r16,#0xec6
    3064:	41 19 88 03 	xor $r17,$r19,$r2
    3068:	89 83       	add45 $r16,$r3
    306a:	41 48 c8 03 	xor $r20,$r17,$r18
    306e:	89 88       	add45 $r16,$r8
    3070:	89 94       	add45 $r16,$r20
    3072:	47 4e aa 12 	sethi $r20,#0xeaa12
    3076:	41 08 70 0b 	rotri $r16,$r16,#0x1c
    307a:	51 4a 07 fa 	addi $r20,$r20,#0x7fa
    307e:	40 88 4c 00 	add $r8,$r16,$r19
    3082:	41 4c 50 00 	add $r20,$r24,$r20
    3086:	41 14 44 03 	xor $r17,$r8,$r17
    308a:	41 4a 48 00 	add $r20,$r20,$r18
    308e:	41 4a 44 00 	add $r20,$r20,$r17
    3092:	41 4a 54 0b 	rotri $r20,$r20,#0x15
    3096:	47 0d 4e f3 	sethi $r16,#0xd4ef3
    309a:	41 1a 20 00 	add $r17,$r20,$r8
    309e:	51 08 00 85 	addi $r16,$r16,#0x85
    30a2:	41 28 a0 03 	xor $r18,$r17,$r8
    30a6:	89 8d       	add45 $r16,$r13
    30a8:	41 49 4c 03 	xor $r20,$r18,$r19
    30ac:	89 82       	add45 $r16,$r2
    30ae:	89 94       	add45 $r16,$r20
    30b0:	41 08 40 0b 	rotri $r16,$r16,#0x10
    30b4:	40 28 44 00 	add $r2,$r16,$r17
    30b8:	47 00 48 81 	sethi $r16,#0x4881
    30bc:	51 08 0d 05 	addi $r16,$r16,#0xd05
    30c0:	89 89       	add45 $r16,$r9
    30c2:	41 21 48 03 	xor $r18,$r2,$r18
    30c6:	89 93       	add45 $r16,$r19
    30c8:	89 92       	add45 $r16,$r18
    30ca:	41 08 24 0b 	rotri $r16,$r16,#0x9
    30ce:	41 38 08 00 	add $r19,$r16,$r2
    30d2:	47 0d 9d 4d 	sethi $r16,#0xd9d4d
    30d6:	51 08 00 39 	addi $r16,$r16,#0x39
    30da:	41 29 88 03 	xor $r18,$r19,$r2
    30de:	89 86       	add45 $r16,$r6
    30e0:	41 49 44 03 	xor $r20,$r18,$r17
    30e4:	89 88       	add45 $r16,$r8
    30e6:	89 94       	add45 $r16,$r20
    30e8:	47 4e 6d b9 	sethi $r20,#0xe6db9
    30ec:	41 08 70 0b 	rotri $r16,$r16,#0x1c
    30f0:	51 4a 09 e5 	addi $r20,$r20,#0x9e5
    30f4:	40 88 4c 00 	add $r8,$r16,$r19
    30f8:	41 47 50 00 	add $r20,$r14,$r20
    30fc:	41 24 48 03 	xor $r18,$r8,$r18
    3100:	41 4a 44 00 	add $r20,$r20,$r17
    3104:	41 4a 48 00 	add $r20,$r20,$r18
    3108:	41 4a 54 0b 	rotri $r20,$r20,#0x15
    310c:	47 11 fa 27 	sethi $r17,#0x1fa27
    3110:	41 4a 20 00 	add $r20,$r20,$r8
    3114:	51 18 8c f8 	addi $r17,$r17,#0xcf8
    3118:	41 2a 20 03 	xor $r18,$r20,$r8
    311c:	89 b9       	add45 $r17,$r25
    311e:	41 09 4c 03 	xor $r16,$r18,$r19
    3122:	89 a2       	add45 $r17,$r2
    3124:	89 b0       	add45 $r17,$r16
    3126:	47 0c 4a c5 	sethi $r16,#0xc4ac5
    312a:	41 18 c0 0b 	rotri $r17,$r17,#0x10
    312e:	51 08 06 65 	addi $r16,$r16,#0x665
    3132:	89 b4       	add45 $r17,$r20
    3134:	89 87       	add45 $r16,$r7
    3136:	41 28 c8 03 	xor $r18,$r17,$r18
    313a:	89 93       	add45 $r16,$r19
    313c:	89 92       	add45 $r16,$r18
    313e:	41 08 24 0b 	rotri $r16,$r16,#0x9
    3142:	47 3f 42 92 	sethi $r19,#0xf4292
    3146:	89 91       	add45 $r16,$r17
    3148:	41 2a 50 05 	nor $r18,$r20,$r20
    314c:	51 39 82 44 	addi $r19,$r19,#0x244
    3150:	41 28 48 04 	or $r18,$r16,$r18
    3154:	89 f8       	add45 $r19,$r24
    3156:	41 29 44 03 	xor $r18,$r18,$r17
    315a:	89 e8       	add45 $r19,$r8
    315c:	89 f2       	add45 $r19,$r18
    315e:	41 39 e8 0b 	rotri $r19,$r19,#0x1a
    3162:	46 84 32 af 	sethi $r8,#0x432af
    3166:	89 f0       	add45 $r19,$r16
    3168:	41 28 c4 05 	nor $r18,$r17,$r17
    316c:	50 84 0f 97 	addi $r8,$r8,#0xf97
    3170:	89 1e       	add45 $r8,$lp
    3172:	41 29 c8 04 	or $r18,$r19,$r18
    3176:	41 29 40 03 	xor $r18,$r18,$r16
    317a:	41 44 50 00 	add $r20,$r8,$r20
    317e:	41 4a 48 00 	add $r20,$r20,$r18
    3182:	41 4a 58 0b 	rotri $r20,$r20,#0x16
    3186:	46 8a b9 42 	sethi $r8,#0xab942
    318a:	41 4a 4c 00 	add $r20,$r20,$r19
    318e:	41 28 40 05 	nor $r18,$r16,$r16
    3192:	50 84 03 a7 	addi $r8,$r8,#0x3a7
    3196:	89 1c       	add45 $r8,$fp
    3198:	41 2a 48 04 	or $r18,$r20,$r18
    319c:	89 a8       	add45 $r17,$r8
    319e:	41 29 4c 03 	xor $r18,$r18,$r19
    31a2:	89 d1       	add45 $r18,$r17
    31a4:	41 29 44 0b 	rotri $r18,$r18,#0x11
    31a8:	46 8f c9 3a 	sethi $r8,#0xfc93a
    31ac:	89 d4       	add45 $r18,$r20
    31ae:	41 19 cc 05 	nor $r17,$r19,$r19
    31b2:	50 84 00 39 	addi $r8,$r8,#0x39
    31b6:	89 0f       	add45 $r8,$r15
    31b8:	41 19 44 04 	or $r17,$r18,$r17
    31bc:	89 88       	add45 $r16,$r8
    31be:	41 18 d0 03 	xor $r17,$r17,$r20
    31c2:	89 b0       	add45 $r17,$r16
    31c4:	41 18 ac 0b 	rotri $r17,$r17,#0xb
    31c8:	46 86 55 b5 	sethi $r8,#0x655b5
    31cc:	89 b2       	add45 $r17,$r18
    31ce:	41 0a 50 05 	nor $r16,$r20,$r20
    31d2:	50 84 09 c3 	addi $r8,$r8,#0x9c3
    31d6:	89 0e       	add45 $r8,$r14
    31d8:	41 08 c0 04 	or $r16,$r17,$r16
    31dc:	89 e8       	add45 $r19,$r8
    31de:	41 08 48 03 	xor $r16,$r16,$r18
    31e2:	89 93       	add45 $r16,$r19
    31e4:	41 08 68 0b 	rotri $r16,$r16,#0x1a
    31e8:	46 88 f0 cc 	sethi $r8,#0x8f0cc
    31ec:	89 91       	add45 $r16,$r17
    31ee:	41 39 48 05 	nor $r19,$r18,$r18
    31f2:	50 84 0c 92 	addi $r8,$r8,#0xc92
    31f6:	89 0d       	add45 $r8,$r13
    31f8:	41 38 4c 04 	or $r19,$r16,$r19
    31fc:	41 44 50 00 	add $r20,$r8,$r20
    3200:	41 39 c4 03 	xor $r19,$r19,$r17
    3204:	89 f4       	add45 $r19,$r20
    3206:	41 39 d8 0b 	rotri $r19,$r19,#0x16
    320a:	46 8f fe ff 	sethi $r8,#0xffeff
    320e:	89 f0       	add45 $r19,$r16
    3210:	41 48 c4 05 	nor $r20,$r17,$r17
    3214:	50 84 04 7d 	addi $r8,$r8,#0x47d
    3218:	89 0c       	add45 $r8,$r12
    321a:	41 49 d0 04 	or $r20,$r19,$r20
    321e:	41 4a 40 03 	xor $r20,$r20,$r16
    3222:	89 c8       	add45 $r18,$r8
    3224:	89 d4       	add45 $r18,$r20
    3226:	41 29 44 0b 	rotri $r18,$r18,#0x11
    322a:	46 88 58 45 	sethi $r8,#0x85845
    322e:	89 d3       	add45 $r18,$r19
    3230:	41 48 40 05 	nor $r20,$r16,$r16
    3234:	50 84 0d d1 	addi $r8,$r8,#0xdd1
    3238:	89 0b       	add45 $r8,$r11
    323a:	41 49 50 04 	or $r20,$r18,$r20
    323e:	41 4a 4c 03 	xor $r20,$r20,$r19
    3242:	89 a8       	add45 $r17,$r8
    3244:	89 b4       	add45 $r17,$r20
    3246:	41 18 ac 0b 	rotri $r17,$r17,#0xb
    324a:	46 86 fa 87 	sethi $r8,#0x6fa87
    324e:	89 b2       	add45 $r17,$r18
    3250:	41 49 cc 05 	nor $r20,$r19,$r19
    3254:	50 84 0e 4f 	addi $r8,$r8,#0xe4f
    3258:	89 0a       	add45 $r8,$r10
    325a:	41 48 d0 04 	or $r20,$r17,$r20
    325e:	41 4a 48 03 	xor $r20,$r20,$r18
    3262:	89 88       	add45 $r16,$r8
    3264:	89 94       	add45 $r16,$r20
    3266:	41 08 68 0b 	rotri $r16,$r16,#0x1a
    326a:	46 8f e2 ce 	sethi $r8,#0xfe2ce
    326e:	89 91       	add45 $r16,$r17
    3270:	41 49 48 05 	nor $r20,$r18,$r18
    3274:	50 84 06 e0 	addi $r8,$r8,#0x6e0
    3278:	89 19       	add45 $r8,$r25
    327a:	41 48 50 04 	or $r20,$r16,$r20
    327e:	41 4a 44 03 	xor $r20,$r20,$r17
    3282:	89 e8       	add45 $r19,$r8
    3284:	89 f4       	add45 $r19,$r20
    3286:	41 39 d8 0b 	rotri $r19,$r19,#0x16
    328a:	47 4a 30 14 	sethi $r20,#0xa3014
    328e:	40 89 c0 00 	add $r8,$r19,$r16
    3292:	51 4a 03 14 	addi $r20,$r20,#0x314
    3296:	41 38 c4 05 	nor $r19,$r17,$r17
    329a:	41 44 d0 00 	add $r20,$r9,$r20
    329e:	41 34 4c 04 	or $r19,$r8,$r19
    32a2:	41 39 c0 03 	xor $r19,$r19,$r16
    32a6:	89 d4       	add45 $r18,$r20
    32a8:	89 d3       	add45 $r18,$r19
    32aa:	41 29 44 0b 	rotri $r18,$r18,#0x11
    32ae:	47 44 e0 81 	sethi $r20,#0x4e081
    32b2:	41 39 20 00 	add $r19,$r18,$r8
    32b6:	51 4a 01 a1 	addi $r20,$r20,#0x1a1
    32ba:	41 28 40 05 	nor $r18,$r16,$r16
    32be:	88 74       	add45 $r3,$r20
    32c0:	41 29 c8 04 	or $r18,$r19,$r18
    32c4:	89 a3       	add45 $r17,$r3
    32c6:	41 29 20 03 	xor $r18,$r18,$r8
    32ca:	89 b2       	add45 $r17,$r18
    32cc:	41 18 ac 0b 	rotri $r17,$r17,#0xb
    32d0:	46 3f 75 37 	sethi $r3,#0xf7537
    32d4:	41 48 cc 00 	add $r20,$r17,$r19
    32d8:	50 31 8e 82 	addi $r3,$r3,#0xe82
    32dc:	41 14 20 05 	nor $r17,$r8,$r8
    32e0:	88 83       	add45 $r4,$r3
    32e2:	41 1a 44 04 	or $r17,$r20,$r17
    32e6:	89 84       	add45 $r16,$r4
    32e8:	41 18 cc 03 	xor $r17,$r17,$r19
    32ec:	89 91       	add45 $r16,$r17
    32ee:	41 08 68 0b 	rotri $r16,$r16,#0x1a
    32f2:	46 3b d3 af 	sethi $r3,#0xbd3af
    32f6:	41 28 50 00 	add $r18,$r16,$r20
    32fa:	40 49 cc 05 	nor $r4,$r19,$r19
    32fe:	50 31 82 35 	addi $r3,$r3,#0x235
    3302:	88 65       	add45 $r3,$r5
    3304:	40 49 10 04 	or $r4,$r18,$r4
    3308:	40 42 50 03 	xor $r4,$r4,$r20
    330c:	88 68       	add45 $r3,$r8
    330e:	88 64       	add45 $r3,$r4
    3310:	40 31 d8 0b 	rotri $r3,$r3,#0x16
    3314:	46 42 ad 7d 	sethi $r4,#0x2ad7d
    3318:	88 72       	add45 $r3,$r18
    331a:	6a 28 80 01 	fmfsr $r2,$fs17
    331e:	40 5a 50 05 	nor $r5,$r20,$r20
    3322:	50 42 02 bb 	addi $r4,$r4,#0x2bb
    3326:	88 87       	add45 $r4,$r7
    3328:	ff 5f       	or33 $r5,$r3
    332a:	40 52 c8 03 	xor $r5,$r5,$r18
    332e:	50 21 7f c0 	addi $r2,$r2,#-64
    3332:	88 93       	add45 $r4,$r19
    3334:	88 85       	add45 $r4,$r5
    3336:	6a 28 80 09 	fmtsr $r2,$fs17
    333a:	6a 2f 80 01 	fmfsr $r2,$fs31
    333e:	40 42 44 0b 	rotri $r4,$r4,#0x11
    3342:	46 5e b8 6d 	sethi $r5,#0xeb86d
    3346:	88 83       	add45 $r4,$r3
    3348:	88 52       	add45 $r2,$r18
    334a:	41 09 48 05 	nor $r16,$r18,$r18
    334e:	50 52 83 91 	addi $r5,$r5,#0x391
    3352:	88 a6       	add45 $r5,$r6
    3354:	41 02 40 04 	or $r16,$r4,$r16
    3358:	6a 2f 80 09 	fmtsr $r2,$fs31
    335c:	6a 29 00 01 	fmfsr $r2,$fs18
    3360:	88 b4       	add45 $r5,$r20
    3362:	41 08 0c 03 	xor $r16,$r16,$r3
    3366:	88 43       	add45 $r2,$r3
    3368:	88 b0       	add45 $r5,$r16
    336a:	40 52 ac 0b 	rotri $r5,$r5,#0xb
    336e:	6a 29 00 09 	fmtsr $r2,$fs18
    3372:	6a 28 80 01 	fmfsr $r2,$fs17
    3376:	88 a4       	add45 $r5,$r4
    3378:	15 90 00 25 	swi $r25,[$r0+#0x94]
    337c:	41 5a 94 00 	add $r21,$r21,$r5
    3380:	41 6b 10 00 	add $r22,$r22,$r4
    3384:	50 10 80 40 	addi $r1,$r1,#0x40
    3388:	4e 23 fa bb 	bnez $r2,28fe <body+0x14a>
    338c:	33 f0 00 02 	fssi $fs31,[$r0+#0x8]
    3390:	15 50 00 03 	swi $r21,[$r0+#0xc]
    3394:	15 60 00 04 	swi $r22,[$r0+#0x10]
    3398:	33 20 00 05 	fssi $fs18,[$r0+#0x14]
    339c:	80 01       	mov55 $r0,$r1
    339e:	34 3f 90 02 	fldi.bi $fd3,[$sp],#0x8
    33a2:	34 4f 90 02 	fldi.bi $fd4,[$sp],#0x8
    33a6:	34 5f 90 02 	fldi.bi $fd5,[$sp],#0x8
    33aa:	34 6f 90 02 	fldi.bi $fd6,[$sp],#0x8
    33ae:	34 7f 90 02 	fldi.bi $fd7,[$sp],#0x8
    33b2:	34 8f 90 02 	fldi.bi $fd8,[$sp],#0x8
    33b6:	34 9f 90 03 	fldi.bi $fd9,[$sp],#0xc
    33ba:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    33be:	dd 9e       	ret5 $lp

000033c0 <MD5_Init>:
    33c0:	46 16 74 52 	sethi $r1,#0x67452
    33c4:	50 10 83 01 	addi $r1,$r1,#0x301
    33c8:	a8 42       	swi333 $r1,[$r0+#0x8]
    33ca:	46 1e fc da 	sethi $r1,#0xefcda
    33ce:	50 10 8b 89 	addi $r1,$r1,#0xb89
    33d2:	a8 43       	swi333 $r1,[$r0+#0xc]
    33d4:	46 19 8b ad 	sethi $r1,#0x98bad
    33d8:	50 10 8c fe 	addi $r1,$r1,#0xcfe
    33dc:	a8 44       	swi333 $r1,[$r0+#0x10]
    33de:	46 11 03 25 	sethi $r1,#0x10325
    33e2:	84 40       	movi55 $r2,#0x0
    33e4:	50 10 84 76 	addi $r1,$r1,#0x476
    33e8:	a8 45       	swi333 $r1,[$r0+#0x14]
    33ea:	b6 40       	swi450 $r2,[$r0]
    33ec:	a8 81       	swi333 $r2,[$r0+#0x4]
    33ee:	dd 9e       	ret5 $lp

000033f0 <MD5_Update>:
    33f0:	3a 6f a8 bc 	smw.adm $r6,[$sp],$r10,#0x2    ! {$r6~$r10, $lp}
    33f4:	b4 60       	lwi450 $r3,[$r0]
    33f6:	80 c0       	mov55 $r6,$r0
    33f8:	99 13       	add333 $r4,$r2,$r3
    33fa:	95 23       	slli333 $r4,$r4,#0x3
    33fc:	92 83       	srli45 $r4,#0x3
    33fe:	e2 83       	slt45 $r4,$r3
    3400:	80 e2       	mov55 $r7,$r2
    3402:	81 01       	mov55 $r8,$r1
    3404:	b6 86       	swi450 $r4,[$r6]
    3406:	e9 2b       	bnezs8 345c <MD5_Update+0x6c>
    3408:	a0 31       	lwi333 $r0,[$r6+#0x4]
    340a:	92 00       	nop16
    340c:	40 23 f4 09 	srli $r2,$r7,#0x1d
    3410:	88 40       	add45 $r2,$r0
    3412:	96 ef       	fexti33 $r3,#0x5
    3414:	a8 b1       	swi333 $r2,[$r6+#0x4]
    3416:	50 93 00 18 	addi $r9,$r6,#0x18
    341a:	c3 17       	beqz38 $r3,3448 <MD5_Update+0x58>
    341c:	52 a1 80 40 	subri $r10,$r3,#0x40
    3420:	e2 ea       	slt45 $r7,$r10
    3422:	e9 2b       	bnezs8 3478 <MD5_Update+0x88>
    3424:	50 01 80 18 	addi $r0,$r3,#0x18
    3428:	80 28       	mov55 $r1,$r8
    342a:	80 4a       	mov55 $r2,$r10
    342c:	88 06       	add45 $r0,$r6
    342e:	50 93 00 18 	addi $r9,$r6,#0x18
    3432:	49 00 35 91 	jal 9f54 <memcpy>
    3436:	80 06       	mov55 $r0,$r6
    3438:	80 29       	mov55 $r1,$r9
    343a:	44 20 00 40 	movi $r2,#0x40
    343e:	89 0a       	add45 $r8,$r10
    3440:	40 73 a8 01 	sub $r7,$r7,$r10
    3444:	49 ff f9 b8 	jal 27b4 <body>
    3448:	5c f3 80 40 	slti $r15,$r7,#0x40
    344c:	e8 0c       	beqzs8 3464 <MD5_Update+0x74>
    344e:	80 09       	mov55 $r0,$r9
    3450:	80 28       	mov55 $r1,$r8
    3452:	80 47       	mov55 $r2,$r7
    3454:	3a 6f a8 84 	lmw.bim $r6,[$sp],$r10,#0x2    ! {$r6~$r10, $lp}
    3458:	48 00 35 7e 	j 9f54 <memcpy>
    345c:	a0 b1       	lwi333 $r2,[$r6+#0x4]
    345e:	9c 11       	addi333 $r0,$r2,#0x1
    3460:	d5 d6       	j8 340c <MD5_Update+0x1c>
    3462:	92 00       	nop16
    3464:	66 23 80 3f 	bitci $r2,$r7,#0x3f
    3468:	80 28       	mov55 $r1,$r8
    346a:	80 06       	mov55 $r0,$r6
    346c:	49 ff f9 a4 	jal 27b4 <body>
    3470:	81 00       	mov55 $r8,$r0
    3472:	97 ef       	fexti33 $r7,#0x5
    3474:	d5 ed       	j8 344e <MD5_Update+0x5e>
    3476:	92 00       	nop16
    3478:	50 01 80 18 	addi $r0,$r3,#0x18
    347c:	88 06       	add45 $r0,$r6
    347e:	d5 e9       	j8 3450 <MD5_Update+0x60>

00003480 <MD5_Final>:
    3480:	3a 6f a0 bc 	smw.adm $r6,[$sp],$r8,#0x2    ! {$r6~$r8, $lp}
    3484:	b4 61       	lwi450 $r3,[$r1]
    3486:	80 c1       	mov55 $r6,$r1
    3488:	96 ef       	fexti33 $r3,#0x5
    348a:	52 21 80 3f 	subri $r2,$r3,#0x3f
    348e:	99 0b       	add333 $r4,$r1,$r3
    3490:	80 e0       	mov55 $r7,$r0
    3492:	e6 48       	slti45 $r2,#0x8
    3494:	44 0f ff 80 	movi $r0,#-128
    3498:	10 02 00 18 	sbi $r0,[$r4+#0x18]
    349c:	50 01 80 19 	addi $r0,$r3,#0x19
    34a0:	e9 69       	bnezs8 3572 <MD5_Final+0xf2>
    34a2:	50 83 00 18 	addi $r8,$r6,#0x18
    34a6:	88 06       	add45 $r0,$r6
    34a8:	52 21 80 37 	subri $r2,$r3,#0x37
    34ac:	84 20       	movi55 $r1,#0x0
    34ae:	49 00 35 87 	jal 9fbc <memset>
    34b2:	b4 06       	lwi450 $r0,[$r6]
    34b4:	a0 f1       	lwi333 $r3,[$r6+#0x4]
    34b6:	94 03       	slli333 $r0,$r0,#0x3
    34b8:	41 30 20 09 	srli $r19,$r0,#0x8
    34bc:	41 20 40 09 	srli $r18,$r0,#0x10
    34c0:	41 10 60 09 	srli $r17,$r0,#0x18
    34c4:	41 01 a0 09 	srli $r16,$r3,#0x8
    34c8:	40 51 c0 09 	srli $r5,$r3,#0x10
    34cc:	40 41 e0 09 	srli $r4,$r3,#0x18
    34d0:	80 28       	mov55 $r1,$r8
    34d2:	b6 06       	swi450 $r0,[$r6]
    34d4:	10 03 00 50 	sbi $r0,[$r6+#0x50]
    34d8:	10 33 00 54 	sbi $r3,[$r6+#0x54]
    34dc:	44 20 00 40 	movi $r2,#0x40
    34e0:	11 33 00 51 	sbi $r19,[$r6+#0x51]
    34e4:	11 23 00 52 	sbi $r18,[$r6+#0x52]
    34e8:	11 13 00 53 	sbi $r17,[$r6+#0x53]
    34ec:	11 03 00 55 	sbi $r16,[$r6+#0x55]
    34f0:	10 53 00 56 	sbi $r5,[$r6+#0x56]
    34f4:	10 43 00 57 	sbi $r4,[$r6+#0x57]
    34f8:	80 06       	mov55 $r0,$r6
    34fa:	49 ff f9 5d 	jal 27b4 <body>
    34fe:	a0 32       	lwi333 $r0,[$r6+#0x8]
    3500:	ae 38       	sbi333 $r0,[$r7+#0x0]
    3502:	a0 72       	lwi333 $r1,[$r6+#0x8]
    3504:	80 06       	mov55 $r0,$r6
    3506:	92 28       	srli45 $r1,#0x8
    3508:	ae 79       	sbi333 $r1,[$r7+#0x1]
    350a:	a4 75       	lhi333 $r1,[$r6+#0xa]
    350c:	ae 7a       	sbi333 $r1,[$r7+#0x2]
    350e:	00 13 00 0b 	lbi $r1,[$r6+#0xb]
    3512:	ae 7b       	sbi333 $r1,[$r7+#0x3]
    3514:	a0 73       	lwi333 $r1,[$r6+#0xc]
    3516:	ae 7c       	sbi333 $r1,[$r7+#0x4]
    3518:	a0 b3       	lwi333 $r2,[$r6+#0xc]
    351a:	84 20       	movi55 $r1,#0x0
    351c:	92 48       	srli45 $r2,#0x8
    351e:	ae bd       	sbi333 $r2,[$r7+#0x5]
    3520:	a4 b7       	lhi333 $r2,[$r6+#0xe]
    3522:	ae be       	sbi333 $r2,[$r7+#0x6]
    3524:	00 23 00 0f 	lbi $r2,[$r6+#0xf]
    3528:	ae bf       	sbi333 $r2,[$r7+#0x7]
    352a:	a0 b4       	lwi333 $r2,[$r6+#0x10]
    352c:	10 23 80 08 	sbi $r2,[$r7+#0x8]
    3530:	a0 f4       	lwi333 $r3,[$r6+#0x10]
    3532:	44 20 00 98 	movi $r2,#0x98
    3536:	92 68       	srli45 $r3,#0x8
    3538:	10 33 80 09 	sbi $r3,[$r7+#0x9]
    353c:	02 33 00 09 	lhi $r3,[$r6+#0x12]
    3540:	10 33 80 0a 	sbi $r3,[$r7+#0xa]
    3544:	00 33 00 13 	lbi $r3,[$r6+#0x13]
    3548:	10 33 80 0b 	sbi $r3,[$r7+#0xb]
    354c:	a0 f5       	lwi333 $r3,[$r6+#0x14]
    354e:	10 33 80 0c 	sbi $r3,[$r7+#0xc]
    3552:	a0 f5       	lwi333 $r3,[$r6+#0x14]
    3554:	92 68       	srli45 $r3,#0x8
    3556:	10 33 80 0d 	sbi $r3,[$r7+#0xd]
    355a:	02 33 00 0b 	lhi $r3,[$r6+#0x16]
    355e:	10 33 80 0e 	sbi $r3,[$r7+#0xe]
    3562:	00 33 00 17 	lbi $r3,[$r6+#0x17]
    3566:	10 33 80 0f 	sbi $r3,[$r7+#0xf]
    356a:	3a 6f a0 84 	lmw.bim $r6,[$sp],$r8,#0x2    ! {$r6~$r8, $lp}
    356e:	48 00 35 27 	j 9fbc <memset>
    3572:	84 20       	movi55 $r1,#0x0
    3574:	50 83 00 18 	addi $r8,$r6,#0x18
    3578:	40 00 18 00 	add $r0,$r0,$r6
    357c:	49 00 35 20 	jal 9fbc <memset>
    3580:	44 20 00 40 	movi $r2,#0x40
    3584:	80 06       	mov55 $r0,$r6
    3586:	80 28       	mov55 $r1,$r8
    3588:	49 ff f9 16 	jal 27b4 <body>
    358c:	80 08       	mov55 $r0,$r8
    358e:	44 20 00 38 	movi $r2,#0x38
    3592:	48 ff ff 8d 	j 34ac <MD5_Final+0x2c>
    3596:	92 00       	nop16

00003598 <lfs_alloc_lookahead>:
    3598:	04 30 00 1a 	lwi $r3,[$r0+#0x68]
    359c:	04 20 00 15 	lwi $r2,[$r0+#0x54]
    35a0:	04 31 80 08 	lwi $r3,[$r3+#0x20]
    35a4:	04 40 00 16 	lwi $r4,[$r0+#0x58]
    35a8:	9a 9a       	sub333 $r2,$r3,$r2
    35aa:	88 22       	add45 $r1,$r2
    35ac:	40 10 8c 77 	divr $r1,$r3,$r1,$r3
    35b0:	e2 64       	slt45 $r3,$r4
    35b2:	e8 0d       	beqzs8 35cc <lfs_alloc_lookahead+0x34>
    35b4:	04 00 00 19 	lwi $r0,[$r0+#0x64]
    35b8:	40 21 94 09 	srli $r2,$r3,#0x5
    35bc:	38 40 0a 02 	lw $r4,[$r0+($r2<<#0x2)]
    35c0:	84 21       	movi55 $r1,#0x1
    35c2:	40 30 8c 0c 	sll $r3,$r1,$r3
    35c6:	fe e7       	or33 $r3,$r4
    35c8:	38 30 0a 0a 	sw $r3,[$r0+($r2<<#0x2)]
    35cc:	84 00       	movi55 $r0,#0x0
    35ce:	dd 9e       	ret5 $lp

000035d0 <lfs_dir_traverse_filter>:
    35d0:	42 20 f0 0b 	btst $r2,$r1,#0x1c
    35d4:	80 a0       	mov55 $r5,$r0
    35d6:	ca 2d       	bnez38 $r2,3630 <lfs_dir_traverse_filter+0x60>
    35d8:	46 27 00 ff 	sethi $r2,#0x700ff
    35dc:	50 31 0c 00 	addi $r3,$r2,#0xc00
    35e0:	b4 85       	lwi450 $r4,[$r5]
    35e2:	84 01       	movi55 $r0,#0x1
    35e4:	40 22 04 03 	xor $r2,$r4,$r1
    35e8:	fe 9e       	and33 $r2,$r3
    35ea:	c2 21       	beqz38 $r2,362c <lfs_dir_traverse_filter+0x5c>
    35ec:	40 22 58 08 	slli $r2,$r4,#0x16
    35f0:	90 56       	srai45 $r2,#0x16
    35f2:	5a 27 ff 1d 	beqc $r2,#-1,362c <lfs_dir_traverse_filter+0x5c>
    35f6:	46 20 00 ff 	sethi $r2,#0xff
    35fa:	50 21 0c 00 	addi $r2,$r2,#0xc00
    35fe:	46 37 ff ff 	sethi $r3,#0x7ffff
    3602:	41 02 08 02 	and $r16,$r4,$r2
    3606:	50 31 8c 00 	addi $r3,$r3,#0xc00
    360a:	47 14 ff 00 	sethi $r17,#0x4ff00
    360e:	fe ce       	and33 $r3,$r1
    3610:	41 18 44 04 	or $r17,$r16,$r17
    3614:	4c 38 80 0c 	beq $r3,$r17,362c <lfs_dir_traverse_filter+0x5c>
    3618:	40 30 d0 09 	srli $r3,$r1,#0x14
    361c:	54 31 87 00 	andi $r3,$r3,#0x700
    3620:	45 10 04 00 	movi $r17,#0x400
    3624:	84 00       	movi55 $r0,#0x0
    3626:	4c 38 80 0a 	beq $r3,$r17,363a <lfs_dir_traverse_filter+0x6a>
    362a:	92 00       	nop16
    362c:	dd 9e       	ret5 $lp
    362e:	92 00       	nop16
    3630:	46 27 ff ff 	sethi $r2,#0x7ffff
    3634:	50 31 0c 00 	addi $r3,$r2,#0xc00
    3638:	d5 d4       	j8 35e0 <lfs_dir_traverse_filter+0x10>
    363a:	fe 8e       	and33 $r2,$r1
    363c:	92 4a       	srli45 $r2,#0xa
    363e:	93 8a       	srli45 $r16,#0xa
    3640:	96 91       	zeh33 $r2,$r2
    3642:	41 08 00 13 	zeh $r16,$r16
    3646:	e3 82       	slt45 $r16,$r2
    3648:	e9 f2       	bnezs8 362c <lfs_dir_traverse_filter+0x5c>
    364a:	92 34       	srli45 $r1,#0x14
    364c:	96 4a       	seb33 $r1,$r1
    364e:	40 10 a8 08 	slli $r1,$r1,#0xa
    3652:	88 24       	add45 $r1,$r4
    3654:	b6 25       	swi450 $r1,[$r5]
    3656:	dd 9e       	ret5 $lp

00003658 <lfs_dir_commit_size>:
    3658:	40 20 d8 08 	slli $r2,$r1,#0x16
    365c:	90 56       	srai45 $r2,#0x16
    365e:	8c 41       	addi45 $r2,#0x1
    3660:	b4 60       	lwi450 $r3,[$r0]
    3662:	e6 41       	slti45 $r2,#0x1
    3664:	88 2f       	add45 $r1,$r15
    3666:	8c 64       	addi45 $r3,#0x4
    3668:	54 10 83 ff 	andi $r1,$r1,#0x3ff
    366c:	88 23       	add45 $r1,$r3
    366e:	b6 20       	swi450 $r1,[$r0]
    3670:	84 00       	movi55 $r0,#0x0
    3672:	dd 9e       	ret5 $lp

00003674 <lfs_fs_size_count>:
    3674:	b4 20       	lwi450 $r1,[$r0]
    3676:	80 40       	mov55 $r2,$r0
    3678:	8c 21       	addi45 $r1,#0x1
    367a:	84 00       	movi55 $r0,#0x0
    367c:	b6 22       	swi450 $r1,[$r2]
    367e:	dd 9e       	ret5 $lp

00003680 <lfs_deinit>:
    3680:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    3684:	04 10 00 1a 	lwi $r1,[$r0+#0x68]
    3688:	80 c0       	mov55 $r6,$r0
    368a:	04 00 80 0c 	lwi $r0,[$r1+#0x30]
    368e:	c0 15       	beqz38 $r0,36b8 <lfs_deinit+0x38>
    3690:	04 00 80 0d 	lwi $r0,[$r1+#0x34]
    3694:	4e 02 00 19 	beqz $r0,36c6 <lfs_deinit+0x46>
    3698:	04 00 80 0e 	lwi $r0,[$r1+#0x38]
    369c:	c0 06       	beqz38 $r0,36a8 <lfs_deinit+0x28>
    369e:	84 00       	movi55 $r0,#0x0
    36a0:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    36a4:	dd 9e       	ret5 $lp
    36a6:	92 00       	nop16
    36a8:	04 03 00 19 	lwi $r0,[$r6+#0x64]
    36ac:	49 00 34 2f 	jal 9f0a <free>
    36b0:	84 00       	movi55 $r0,#0x0
    36b2:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    36b6:	dd 9e       	ret5 $lp
    36b8:	04 03 00 03 	lwi $r0,[$r6+#0xc]
    36bc:	49 00 34 27 	jal 9f0a <free>
    36c0:	04 13 00 1a 	lwi $r1,[$r6+#0x68]
    36c4:	d5 e6       	j8 3690 <lfs_deinit+0x10>
    36c6:	a0 37       	lwi333 $r0,[$r6+#0x1c]
    36c8:	49 00 34 21 	jal 9f0a <free>
    36cc:	04 13 00 1a 	lwi $r1,[$r6+#0x68]
    36d0:	d5 e4       	j8 3698 <lfs_deinit+0x18>
    36d2:	92 00       	nop16
    36d4:	63 6f 6d 70 	*unknown*
    36d8:	6f 6e 65 6e 	*unknown*
    36dc:	74 73 2f 62 	*unknown*
    36e0:	73 70 2f 73 	*unknown*
    36e4:	6f 63 2f 62 	*unknown*
    36e8:	6f 6f 74 2f 	*unknown*
    36ec:	62 6f 6f 74 	*unknown*
    36f0:	6c 6f 61 64 	*unknown*
    36f4:	65 72 2f 6c 	msync ???
    36f8:	69 74 74 6c 	*unknown*
    36fc:	65 66 73 2f 	isps #0x3399
    3700:	6f 74 61 5f 	*unknown*
    3704:	6c 66 73 2e 	*unknown*
    3708:	63 00 00 00 	*unknown*
    370c:	6c 66 73 2d 	*unknown*
    3710:	3e 63 66 67 	sbi.gp $r6,[+#0x36667]
    3714:	2d 3e 72 65 	*unknown*
    3718:	61 64 5f 73 	amtbsl2.l $d1,$r4,$r5,$r6,$r7,[$i3],[$i7],$m0,$m7
    371c:	69 7a 65 20 	*unknown*
    3720:	21 3d 20 30 	lbsi $r19,[$p0+#0x2030]
    3724:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    3728:	6c 66 73 2d 	*unknown*
    372c:	3e 63 66 67 	sbi.gp $r6,[+#0x36667]
    3730:	2d 3e 70 72 	*unknown*
    3734:	6f 67 5f 73 	*unknown*
    3738:	69 7a 65 20 	*unknown*
    373c:	21 3d 20 30 	lbsi $r19,[$p0+#0x2030]
    3740:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    3744:	6c 66 73 2d 	*unknown*
    3748:	3e 63 66 67 	sbi.gp $r6,[+#0x36667]
    374c:	2d 3e 63 61 	*unknown*
    3750:	63 68 65 5f 	*unknown*
    3754:	73 69 7a 65 	*unknown*
    3758:	20 21 3d 20 	lbsi $r2,[$r2+#0x3d20]
    375c:	30 00 00 00 	flsi $fs0,[$r0+#0x0]
    3760:	6c 66 73 2d 	*unknown*
    3764:	3e 63 66 67 	sbi.gp $r6,[+#0x36667]
    3768:	2d 3e 63 61 	*unknown*
    376c:	63 68 65 5f 	*unknown*
    3770:	73 69 7a 65 	*unknown*
    3774:	20 25 20 6c 	lbsi $r2,[$r10+#0x206c]
    3778:	66 73 2d 3e 	bitci $r7,$r6,#0x2d3e
    377c:	63 66 67 2d 	*unknown*
    3780:	3e 72 65 61 	sbi.gp $r7,[+#0x26561]
    3784:	64 5f 73 69 	*unknown*
    3788:	7a 65 20 3d 	*unknown*
    378c:	3d 20 30 00 	lhi.gp $r18,[+#0x6000]
    3790:	6c 66 73 2d 	*unknown*
    3794:	3e 63 66 67 	sbi.gp $r6,[+#0x36667]
    3798:	2d 3e 63 61 	*unknown*
    379c:	63 68 65 5f 	*unknown*
    37a0:	73 69 7a 65 	*unknown*
    37a4:	20 25 20 6c 	lbsi $r2,[$r10+#0x206c]
    37a8:	66 73 2d 3e 	bitci $r7,$r6,#0x2d3e
    37ac:	63 66 67 2d 	*unknown*
    37b0:	3e 70 72 6f 	sbi.gp $r7,[+#0x726f]
    37b4:	67 5f 73 69 	bitci $r21,$lp,#0x7369
    37b8:	7a 65 20 3d 	*unknown*
    37bc:	3d 20 30 00 	lhi.gp $r18,[+#0x6000]
    37c0:	6c 66 73 2d 	*unknown*
    37c4:	3e 63 66 67 	sbi.gp $r6,[+#0x36667]
    37c8:	2d 3e 62 6c 	*unknown*
    37cc:	6f 63 6b 5f 	*unknown*
    37d0:	73 69 7a 65 	*unknown*
    37d4:	20 25 20 6c 	lbsi $r2,[$r10+#0x206c]
    37d8:	66 73 2d 3e 	bitci $r7,$r6,#0x2d3e
    37dc:	63 66 67 2d 	*unknown*
    37e0:	3e 63 61 63 	sbi.gp $r6,[+#0x36163]
    37e4:	68 65 5f 73 	*unknown*
    37e8:	69 7a 65 20 	*unknown*
    37ec:	3d 3d 20 30 	lwi.gp $r19,[+#-229184]
    37f0:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    37f4:	34 2a 6c 66 	cpldi cp3,$cpr2,[$r20+#-3688]
    37f8:	73 5f 6e 70 	*unknown*
    37fc:	77 32 28 30 	*unknown*
    3800:	78 66 66 66 	*unknown*
    3804:	66 66 66 66 	bitci $r6,$r12,#0x6666
    3808:	66 20 2f 20 	bitci $r2,$r0,#0x2f20
    380c:	28 6c 66 73 	lbsi.bi $r6,[$r24],#-6541
    3810:	2d 3e 63 66 	*unknown*
    3814:	67 2d 3e 62 	bitci $r18,$p0,#0x3e62
    3818:	6c 6f 63 6b 	*unknown*
    381c:	5f 73 69 7a 	sltsi $r23,$r6,#-5766
    3820:	65 2d 32 2a 	break #0x6991
    3824:	34 29 29 20 	cpldi cp1,$cpr2,[$r18+#-7040]
    3828:	3c 3d 20 6c 	lwi.gp $r3,[+#-228944]
    382c:	66 73 2d 3e 	bitci $r7,$r6,#0x2d3e
    3830:	63 66 67 2d 	*unknown*
    3834:	3e 62 6c 6f 	sbi.gp $r6,[+#0x26c6f]
    3838:	63 6b 5f 73 	*unknown*
    383c:	69 7a 65 00 	*unknown*
    3840:	6c 66 73 2d 	*unknown*
    3844:	3e 63 66 67 	sbi.gp $r6,[+#0x36667]
    3848:	2d 3e 62 6c 	*unknown*
    384c:	6f 63 6b 5f 	*unknown*
    3850:	63 79 63 6c 	*unknown*
    3854:	65 73 20 21 	cctl $r6,l1d_ix_wb
    3858:	3d 20 30 00 	lhi.gp $r18,[+#0x6000]
    385c:	6c 66 73 2d 	*unknown*
    3860:	3e 63 66 67 	sbi.gp $r6,[+#0x36667]
    3864:	2d 3e 6c 6f 	*unknown*
    3868:	6f 6b 61 68 	*unknown*
    386c:	65 61 64 5f 	*unknown*
    3870:	73 69 7a 65 	*unknown*
    3874:	20 3e 20 30 	lbsi $r3,[$fp+#0x2030]
    3878:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    387c:	6c 66 73 2d 	*unknown*
    3880:	3e 63 66 67 	sbi.gp $r6,[+#0x36667]
    3884:	2d 3e 6c 6f 	*unknown*
    3888:	6f 6b 61 68 	*unknown*
    388c:	65 61 64 5f 	*unknown*
    3890:	73 69 7a 65 	*unknown*
    3894:	20 25 20 38 	lbsi $r2,[$r10+#0x2038]
    3898:	20 3d 3d 20 	lbsi $r3,[$p0+#0x3d20]
    389c:	30 20 26 26 	cplwi cp1,$cpr2,[$r0+#0x1898]
    38a0:	20 28 75 69 	lbsi $r2,[$r16+#-2711]
    38a4:	6e 74 70 74 	*unknown*
    38a8:	72 5f 74 29 	*unknown*
    38ac:	6c 66 73 2d 	*unknown*
    38b0:	3e 63 66 67 	sbi.gp $r6,[+#0x36667]
    38b4:	2d 3e 6c 6f 	*unknown*
    38b8:	6f 6b 61 68 	*unknown*
    38bc:	65 61 64 5f 	*unknown*
    38c0:	62 75 66 66 	*unknown*
    38c4:	65 72 20 25 	trap #0x1101
    38c8:	20 34 20 3d 	lbsi $r3,[$r8+#0x203d]
    38cc:	3d 20 30 00 	lhi.gp $r18,[+#0x6000]
    38d0:	6c 66 73 2d 	*unknown*
    38d4:	3e 63 66 67 	sbi.gp $r6,[+#0x36667]
    38d8:	2d 3e 6e 61 	*unknown*
    38dc:	6d 65 5f 6d 	*unknown*
    38e0:	61 78 20 3c 	*unknown*
    38e4:	3d 20 32 35 	lhi.gp $r18,[+#0x646a]
    38e8:	35 00 00 00 	fldi $fd16,[$r0+#0x0]
    38ec:	6c 66 73 2d 	*unknown*
    38f0:	3e 63 66 67 	sbi.gp $r6,[+#0x36667]
    38f4:	2d 3e 66 69 	*unknown*
    38f8:	6c 65 5f 6d 	*unknown*
    38fc:	61 78 20 3c 	*unknown*
    3900:	3d 20 32 31 	lhi.gp $r18,[+#0x6462]
    3904:	34 37 34 38 	cpldi.bi cp1,$cpr3,[$r14],#0x10e0
    3908:	33 36 34 37 	cpswi.bi cp1,$cpr19,[$r12],#0x10dc
    390c:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    3910:	6c 66 73 2d 	*unknown*
    3914:	3e 63 66 67 	sbi.gp $r6,[+#0x36667]
    3918:	2d 3e 61 74 	*unknown*
    391c:	74 72 5f 6d 	*unknown*
    3920:	61 78 20 3c 	*unknown*
    3924:	3d 20 31 30 	lhi.gp $r18,[+#0x6260]
    3928:	32 32 00 00 	fssi $fs3,[$r4+#0x0]
    392c:	65 72 72 20 	*unknown*
    3930:	3c 3d 20 30 	lwi.gp $r3,[+#-229184]
    3934:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    3938:	25 73 3a 25 	*unknown*
    393c:	64 3a 65 72 	*unknown*
    3940:	72 6f 72 3a 	*unknown*
    3944:	20 43 6f 72 	lbsi $r4,[$r6+#-4238]
    3948:	72 75 70 74 	*unknown*
    394c:	65 64 20 64 	*unknown*
    3950:	69 72 20 70 	*unknown*
    3954:	61 69 72 20 	*unknown*
    3958:	61 74 20 7b 	*unknown*
    395c:	30 78 25 6c 	cplwi cp1,$cpr7,[$r16+#0x15b0]
    3960:	78 2c 20 30 	*unknown*
    3964:	78 25 6c 78 	*unknown*
    3968:	7d 25 73 0a 	*unknown*
    396c:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    3970:	6c 66 73 5f 	*unknown*
    3974:	74 61 67 5f 	*unknown*
    3978:	73 69 7a 65 	*unknown*
    397c:	28 6c 66 73 	lbsi.bi $r6,[$r24],#-6541
    3980:	2d 3e 67 73 	*unknown*
    3984:	74 61 74 65 	*unknown*
    3988:	2e 74 61 67 	lbi.gp $r7,[+#-237209]
    398c:	29 20 3e 20 	lbsi.bi $r18,[$r0],#0x3e20
    3990:	30 20 7c 7c 	cplwi.bi cp3,$cpr2,[$r0],#-3600
    3994:	20 6f 72 70 	lbsi $r6,[$lp+#-3472]
    3998:	68 61 6e 73 	*unknown*
    399c:	20 3e 3d 20 	lbsi $r3,[$fp+#0x3d20]
    39a0:	30 00 00 00 	flsi $fs0,[$r0+#0x0]
    39a4:	70 63 61 63 	*unknown*
    39a8:	68 65 2d 3e 	*unknown*
    39ac:	62 6c 6f 63 	*unknown*
    39b0:	6b 20 3c 20 	cpe1 cp2,#0x480f0
    39b4:	6c 66 73 2d 	*unknown*
    39b8:	3e 63 66 67 	sbi.gp $r6,[+#0x36667]
    39bc:	2d 3e 62 6c 	*unknown*
    39c0:	6f 63 6b 5f 	*unknown*
    39c4:	63 6f 75 6e 	*unknown*
    39c8:	74 00 00 00 	*unknown*
    39cc:	62 6c 6f 63 	*unknown*
    39d0:	6b 20 3d 3d 	*unknown*
    39d4:	20 28 28 6c 	lbsi $r2,[$r16+#0x286c]
    39d8:	66 73 5f 62 	bitci $r7,$r6,#0x5f62
    39dc:	6c 6f 63 6b 	*unknown*
    39e0:	5f 74 29 2d 	sltsi $r23,$r8,#0x292d
    39e4:	32 29 20 7c 	cpswi cp1,$cpr2,[$r18+#0x1f0]
    39e8:	7c 20 62 6c 	*unknown*
    39ec:	6f 63 6b 20 	*unknown*
    39f0:	3c 20 6c 66 	lhi.gp $r2,[+#0xd8cc]
    39f4:	73 2d 3e 63 	*unknown*
    39f8:	66 67 2d 3e 	bitci $r6,$r14,#0x2d3e
    39fc:	62 6c 6f 63 	*unknown*
    3a00:	6b 5f 63 6f 	*unknown*
    3a04:	75 6e 74 00 	*unknown*
    3a08:	6f 66 66 20 	*unknown*
    3a0c:	2b 20 73 69 	lhsi.bi $r18,[$r0],#-6446
    3a10:	7a 65 20 3c 	*unknown*
    3a14:	3d 20 6c 66 	lhi.gp $r18,[+#0xd8cc]
    3a18:	73 2d 3e 63 	*unknown*
    3a1c:	66 67 2d 3e 	bitci $r6,$r14,#0x2d3e
    3a20:	62 6c 6f 63 	*unknown*
    3a24:	6b 5f 73 69 	mtcpd cp2,$r21,#0xf73
    3a28:	7a 65 00 00 	*unknown*
    3a2c:	70 63 61 63 	*unknown*
    3a30:	68 65 2d 3e 	*unknown*
    3a34:	62 6c 6f 63 	*unknown*
    3a38:	6b 20 3d 3d 	*unknown*
    3a3c:	20 28 28 6c 	lbsi $r2,[$r16+#0x286c]
    3a40:	66 73 5f 62 	bitci $r7,$r6,#0x5f62
    3a44:	6c 6f 63 6b 	*unknown*
    3a48:	5f 74 29 2d 	sltsi $r23,$r8,#0x292d
    3a4c:	31 29 00 00 	flsi $fs18,[$r18+#0x0]
    3a50:	2f 00 00 00 	lbi.gp $r16,[+#0x0]
    3a54:	2e 00 00 00 	lbi.gp $r0,[+#0x0]
    3a58:	2e 2e 00 00 	lbsi.gp $r2,[+#-131072]
    3a5c:	66 69 6c 65 	bitci $r6,$r18,#0x6c65
    3a60:	2d 3e 66 6c 	*unknown*
    3a64:	61 67 73 20 	amtbsl2.s $d1,$r14,$fp,[$i0],[$i4],$m0,$m6
    3a68:	26 20 4c 46 	dprefi.w swr,[$r0+#-52968]
    3a6c:	53 5f 46 5f 	subri $r21,$lp,#-14753
    3a70:	4f 50 45 4e 	*unknown*
    3a74:	45 44 00 00 	movi $r20,#0x40000
    3a78:	6c 69 74 74 	*unknown*
    3a7c:	6c 65 66 73 	*unknown*
    3a80:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    3a84:	25 73 3a 25 	*unknown*
    3a88:	64 3a 65 72 	*unknown*
    3a8c:	72 6f 72 3a 	*unknown*
    3a90:	20 49 6e 76 	lbsi $r4,[$r18+#-4490]
    3a94:	61 6c 69 64 	amtbsl2.l $d0,$r12,$r6,$r4,$r5,[$i0],[$i4],$m1,$m6
    3a98:	20 76 65 72 	lbsi $r7,[$r12+#-6798]
    3a9c:	73 69 6f 6e 	*unknown*
    3aa0:	20 76 25 75 	lbsi $r7,[$r12+#0x2575]
    3aa4:	2e 25 75 25 	lbi.gp $r2,[+#-166619]
    3aa8:	73 0a 00 00 	*unknown*
    3aac:	25 73 3a 25 	*unknown*
    3ab0:	64 3a 65 72 	*unknown*
    3ab4:	72 6f 72 3a 	*unknown*
    3ab8:	20 55 6e 73 	lbsi $r5,[$r10+#-4493]
    3abc:	75 70 70 6f 	*unknown*
    3ac0:	72 74 65 64 	*unknown*
    3ac4:	20 6e 61 6d 	lbsi $r6,[$fp+#-7827]
    3ac8:	65 5f 6d 61 	cctl $lp,l1d_va_fillck
    3acc:	78 20 28 25 	*unknown*
    3ad0:	6c 75 20 3e 	*unknown*
    3ad4:	20 25 6c 75 	lbsi $r2,[$r10+#-5003]
    3ad8:	29 25 73 0a 	lbsi.bi $r18,[$r10],#-3318
    3adc:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    3ae0:	25 73 3a 25 	*unknown*
    3ae4:	64 3a 65 72 	*unknown*
    3ae8:	72 6f 72 3a 	*unknown*
    3aec:	20 55 6e 73 	lbsi $r5,[$r10+#-4493]
    3af0:	75 70 70 6f 	*unknown*
    3af4:	72 74 65 64 	*unknown*
    3af8:	20 66 69 6c 	lbsi $r6,[$r12+#-5780]
    3afc:	65 5f 6d 61 	cctl $lp,l1d_va_fillck
    3b00:	78 20 28 25 	*unknown*
    3b04:	6c 75 20 3e 	*unknown*
    3b08:	20 25 6c 75 	lbsi $r2,[$r10+#-5003]
    3b0c:	29 25 73 0a 	lbsi.bi $r18,[$r10],#-3318
    3b10:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    3b14:	25 73 3a 25 	*unknown*
    3b18:	64 3a 65 72 	*unknown*
    3b1c:	72 6f 72 3a 	*unknown*
    3b20:	20 55 6e 73 	lbsi $r5,[$r10+#-4493]
    3b24:	75 70 70 6f 	*unknown*
    3b28:	72 74 65 64 	*unknown*
    3b2c:	20 61 74 74 	lbsi $r6,[$r2+#-2956]
    3b30:	72 5f 6d 61 	*unknown*
    3b34:	78 20 28 25 	*unknown*
    3b38:	6c 75 20 3e 	*unknown*
    3b3c:	20 25 6c 75 	lbsi $r2,[$r10+#-5003]
    3b40:	29 25 73 0a 	lbsi.bi $r18,[$r10],#-3318
    3b44:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    3b48:	25 73 3a 25 	*unknown*
    3b4c:	64 3a 64 65 	trap #0x5323
    3b50:	62 75 67 3a 	*unknown*
    3b54:	20 46 6f 75 	lbsi $r4,[$r12+#-4235]
    3b58:	6e 64 20 70 	*unknown*
    3b5c:	65 6e 64 69 	*unknown*
    3b60:	6e 67 20 67 	*unknown*
    3b64:	73 74 61 74 	*unknown*
    3b68:	65 20 30 78 	*unknown*
    3b6c:	25 30 38 6c 	*unknown*
    3b70:	78 25 30 38 	*unknown*
    3b74:	6c 78 25 30 	*unknown*
    3b78:	38 6c 78 25 	*unknown*
    3b7c:	73 0a 00 00 	*unknown*
    3b80:	25 73 3a 25 	*unknown*
    3b84:	64 3a 65 72 	*unknown*
    3b88:	72 6f 72 3a 	*unknown*
    3b8c:	20 4e 6f 20 	lbsi $r4,[$fp+#-4320]
    3b90:	6d 6f 72 65 	*unknown*
    3b94:	20 66 72 65 	lbsi $r6,[$r12+#-3483]
    3b98:	65 20 73 70 	bpick $r18,$r0,$fp,$p1
    3b9c:	61 63 65 20 	amtbsl2.s $d0,$r6,$r25,[$i0],[$i4],$m0,$m6
    3ba0:	25 6c 75 25 	*unknown*
    3ba4:	73 0a 00 00 	*unknown*
    3ba8:	25 73 3a 25 	*unknown*
    3bac:	64 3a 64 65 	trap #0x5323
    3bb0:	62 75 67 3a 	*unknown*
    3bb4:	20 42 61 64 	lbsi $r4,[$r4+#-7836]
    3bb8:	20 62 6c 6f 	lbsi $r6,[$r4+#-5009]
    3bbc:	63 6b 20 61 	*unknown*
    3bc0:	74 20 30 78 	*unknown*
    3bc4:	25 6c 78 25 	*unknown*
    3bc8:	73 0a 00 00 	*unknown*
    3bcc:	28 66 69 6c 	lbsi.bi $r6,[$r12],#-5780
    3bd0:	65 2d 3e 66 	teqz $r18,#0x69f3
    3bd4:	6c 61 67 73 	*unknown*
    3bd8:	20 26 20 33 	lbsi $r2,[$r12+#0x2033]
    3bdc:	29 20 21 3d 	lbsi.bi $r18,[$r0],#0x213d
    3be0:	20 4c 46 53 	lbsi $r4,[$r24+#-14765]
    3be4:	5f 4f 5f 52 	sltsi $r20,$lp,#-8366
    3be8:	44 4f 4e 4c 	movi $r4,#-45492
    3bec:	59 00 00 00 	ori $r16,$r0,#0x0
    3bf0:	28 66 69 6c 	lbsi.bi $r6,[$r12],#-5780
    3bf4:	65 2d 3e 66 	teqz $r18,#0x69f3
    3bf8:	6c 61 67 73 	*unknown*
    3bfc:	20 26 20 33 	lbsi $r2,[$r12+#0x2033]
    3c00:	29 20 21 3d 	lbsi.bi $r18,[$r0],#0x213d
    3c04:	20 4c 46 53 	lbsi $r4,[$r24+#-14765]
    3c08:	5f 4f 5f 57 	sltsi $r20,$lp,#-8361
    3c0c:	52 4f 4e 4c 	subri $r4,$lp,#-12724
    3c10:	59 00 00 00 	ori $r16,$r0,#0x0
    3c14:	25 73 3a 25 	*unknown*
    3c18:	64 3a 64 65 	trap #0x5323
    3c1c:	62 75 67 3a 	*unknown*
    3c20:	20 45 78 70 	lbsi $r4,[$r10+#-1936]
    3c24:	61 6e 64 69 	*unknown*
    3c28:	6e 67 20 73 	*unknown*
    3c2c:	75 70 65 72 	*unknown*
    3c30:	62 6c 6f 63 	*unknown*
    3c34:	6b 20 61 74 	cpe2 cp3,#0x48185
    3c38:	20 72 65 76 	lbsi $r7,[$r4+#-6794]
    3c3c:	20 25 6c 75 	lbsi $r2,[$r10+#-5003]
    3c40:	25 73 0a 00 	*unknown*
    3c44:	63 6f 6d 6d 	*unknown*
    3c48:	69 74 2e 6f 	*unknown*
    3c4c:	66 66 20 25 	bitci $r6,$r12,#0x2025
    3c50:	20 6c 66 73 	lbsi $r6,[$r24+#-6541]
    3c54:	2d 3e 63 66 	*unknown*
    3c58:	67 2d 3e 70 	bitci $r18,$p0,#0x3e70
    3c5c:	72 6f 67 5f 	*unknown*
    3c60:	73 69 7a 65 	*unknown*
    3c64:	20 3d 3d 20 	lbsi $r3,[$p0+#0x3d20]
    3c68:	30 00 00 00 	flsi $fs0,[$r0+#0x0]
    3c6c:	25 73 3a 25 	*unknown*
    3c70:	64 3a 64 65 	trap #0x5323
    3c74:	62 75 67 3a 	*unknown*
    3c78:	20 46 69 78 	lbsi $r4,[$r12+#-5768]
    3c7c:	69 6e 67 20 	*unknown*
    3c80:	6d 6f 76 65 	*unknown*
    3c84:	20 77 68 69 	lbsi $r7,[$r14+#-6039]
    3c88:	6c 65 20 72 	*unknown*
    3c8c:	65 6c 6f 63 	mtsr $r22,795
    3c90:	61 74 69 6e 	amttsl2.l $d0,$r4,$r6,$r4,$r5,[$i2],[$i6],$m3,$m6
    3c94:	67 20 7b 30 	bitci $r18,$r0,#0x7b30
    3c98:	78 25 6c 78 	*unknown*
    3c9c:	2c 20 30 78 	*unknown*
    3ca0:	25 6c 78 7d 	*unknown*
    3ca4:	20 30 78 25 	lbsi $r3,[$r0+#-2011]
    3ca8:	78 0a 25 73 	*unknown*
    3cac:	0a 00 00 00 	lhi.bi $r0,[$r0],#0x0
    3cb0:	25 73 3a 25 	*unknown*
    3cb4:	64 3a 64 65 	trap #0x5323
    3cb8:	62 75 67 3a 	*unknown*
    3cbc:	20 52 65 6c 	lbsi $r5,[$r4+#-6804]
    3cc0:	6f 63 61 74 	*unknown*
    3cc4:	69 6e 67 20 	*unknown*
    3cc8:	7b 30 78 25 	*unknown*
    3ccc:	6c 78 2c 20 	*unknown*
    3cd0:	30 78 25 6c 	cplwi cp1,$cpr7,[$r16+#0x15b0]
    3cd4:	78 7d 20 2d 	*unknown*
    3cd8:	3e 20 7b 30 	sbi.gp $r2,[+#0x7b30]
    3cdc:	78 25 6c 78 	*unknown*
    3ce0:	2c 20 30 78 	*unknown*
    3ce4:	25 6c 78 7d 	*unknown*
    3ce8:	25 73 0a 00 	*unknown*
    3cec:	25 73 3a 25 	*unknown*
    3cf0:	64 3a 77 61 	cctl $r20,l1i_va_fillck
    3cf4:	72 6e 3a 20 	*unknown*
    3cf8:	53 75 70 65 	subri $r23,$r10,#-3995
    3cfc:	72 62 6c 6f 	*unknown*
    3d00:	63 6b 20 30 	*unknown*
    3d04:	78 25 6c 78 	*unknown*
    3d08:	20 68 61 73 	lbsi $r6,[$r16+#-7821]
    3d0c:	20 62 65 63 	lbsi $r6,[$r4+#-6813]
    3d10:	6f 6d 65 20 	*unknown*
    3d14:	75 6e 77 72 	*unknown*
    3d18:	69 74 61 62 	*unknown*
    3d1c:	6c 65 25 73 	*unknown*
    3d20:	0a 00 00 00 	lhi.bi $r0,[$r0],#0x0
    3d24:	64 69 72 2d 	isync $r6
    3d28:	3e 63 6f 75 	sbi.gp $r6,[+#0x36f75]
    3d2c:	6e 74 20 3e 	*unknown*
    3d30:	20 30 00 00 	lbsi $r3,[$r0+#0x0]
    3d34:	25 73 3a 25 	*unknown*
    3d38:	64 3a 64 65 	trap #0x5323
    3d3c:	62 75 67 3a 	*unknown*
    3d40:	20 46 69 78 	lbsi $r4,[$r12+#-5768]
    3d44:	69 6e 67 20 	*unknown*
    3d48:	6d 6f 76 65 	*unknown*
    3d4c:	20 7b 30 78 	lbsi $r7,[$r22+#0x3078]
    3d50:	25 6c 78 2c 	*unknown*
    3d54:	20 30 78 25 	lbsi $r3,[$r0+#-2011]
    3d58:	6c 78 7d 20 	*unknown*
    3d5c:	30 78 25 78 	cplwi cp1,$cpr7,[$r16+#0x15e0]
    3d60:	25 73 0a 00 	*unknown*
    3d64:	25 73 3a 25 	*unknown*
    3d68:	64 3a 64 65 	trap #0x5323
    3d6c:	62 75 67 3a 	*unknown*
    3d70:	20 46 69 78 	lbsi $r4,[$r12+#-5768]
    3d74:	69 6e 67 20 	*unknown*
    3d78:	6f 72 70 68 	*unknown*
    3d7c:	61 6e 20 7b 	*unknown*
    3d80:	30 78 25 6c 	cplwi cp1,$cpr7,[$r16+#0x15b0]
    3d84:	78 2c 20 30 	*unknown*
    3d88:	78 25 6c 78 	*unknown*
    3d8c:	7d 25 73 0a 	*unknown*
    3d90:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    3d94:	25 73 3a 25 	*unknown*
    3d98:	64 3a 64 65 	trap #0x5323
    3d9c:	62 75 67 3a 	*unknown*
    3da0:	20 46 69 78 	lbsi $r4,[$r12+#-5768]
    3da4:	69 6e 67 20 	*unknown*
    3da8:	68 61 6c 66 	*unknown*
    3dac:	2d 6f 72 70 	*unknown*
    3db0:	68 61 6e 20 	*unknown*
    3db4:	7b 30 78 25 	*unknown*
    3db8:	6c 78 2c 20 	*unknown*
    3dbc:	30 78 25 6c 	cplwi cp1,$cpr7,[$r16+#0x15b0]
    3dc0:	78 7d 20 2d 	*unknown*
    3dc4:	3e 20 7b 30 	sbi.gp $r2,[+#0x7b30]
    3dc8:	78 25 6c 78 	*unknown*
    3dcc:	2c 20 30 78 	*unknown*
    3dd0:	25 6c 78 7d 	*unknown*
    3dd4:	25 73 0a 00 	*unknown*

00003dd8 <lfs_init>:
    3dd8:	3a 6f a0 bc 	smw.adm $r6,[$sp],$r8,#0x2    ! {$r6~$r8, $lp}
    3ddc:	a0 cd       	lwi333 $r3,[$r1+#0x14]
    3dde:	80 c0       	mov55 $r6,$r0
    3de0:	14 10 00 1a 	swi $r1,[$r0+#0x68]
    3de4:	4e 32 01 1a 	beqz $r3,4018 <lfs_init+0x240>
    3de8:	a1 0e       	lwi333 $r4,[$r1+#0x18]
    3dea:	4e 42 01 47 	beqz $r4,4078 <lfs_init+0x2a0>
    3dee:	04 20 80 0a 	lwi $r2,[$r1+#0x28]
    3df2:	4e 22 01 2b 	beqz $r2,4048 <lfs_init+0x270>
    3df6:	40 01 0c 77 	divr $r0,$r3,$r2,$r3
    3dfa:	4e 33 00 eb 	bnez $r3,3fd0 <lfs_init+0x1f8>
    3dfe:	40 01 10 97 	divr $r0,$r4,$r2,$r4
    3e02:	4e 43 00 ff 	bnez $r4,4000 <lfs_init+0x228>
    3e06:	a0 0f       	lwi333 $r0,[$r1+#0x1c]
    3e08:	40 40 08 77 	divr $r4,$r3,$r0,$r2
    3e0c:	4e 33 00 ca 	bnez $r3,3fa0 <lfs_init+0x1c8>
    3e10:	50 30 7f f8 	addi $r3,$r0,#-8
    3e14:	84 9f       	movi55 $r4,#-1
    3e16:	40 32 0c 77 	divr $r3,$r3,$r4,$r3
    3e1a:	8e 61       	subi45 $r3,#0x1
    3e1c:	42 31 80 07 	clz $r3,$r3
    3e20:	52 31 80 20 	subri $r3,$r3,#0x20
    3e24:	94 da       	slli333 $r3,$r3,#0x2
    3e26:	e2 03       	slt45 $r0,$r3
    3e28:	4e f3 00 b0 	bnez $r15,3f88 <lfs_init+0x1b0>
    3e2c:	04 00 80 09 	lwi $r0,[$r1+#0x24]
    3e30:	4e 02 00 dc 	beqz $r0,3fe8 <lfs_init+0x210>
    3e34:	04 00 80 0c 	lwi $r0,[$r1+#0x30]
    3e38:	4e 02 00 82 	beqz $r0,3f3c <lfs_init+0x164>
    3e3c:	a8 33       	swi333 $r0,[$r6+#0xc]
    3e3e:	92 00       	nop16
    3e40:	04 00 80 0d 	lwi $r0,[$r1+#0x34]
    3e44:	4e 02 00 71 	beqz $r0,3f26 <lfs_init+0x14e>
    3e48:	14 03 00 07 	swi $r0,[$r6+#0x1c]
    3e4c:	44 10 00 ff 	movi $r1,#0xff
    3e50:	a0 33       	lwi333 $r0,[$r6+#0xc]
    3e52:	49 00 30 b5 	jal 9fbc <memset>
    3e56:	84 ff       	movi55 $r7,#-1
    3e58:	04 23 00 1a 	lwi $r2,[$r6+#0x68]
    3e5c:	b6 e6       	swi450 $r7,[$r6]
    3e5e:	44 10 00 ff 	movi $r1,#0xff
    3e62:	a0 37       	lwi333 $r0,[$r6+#0x1c]
    3e64:	04 21 00 0a 	lwi $r2,[$r2+#0x28]
    3e68:	49 00 30 aa 	jal 9fbc <memset>
    3e6c:	04 13 00 1a 	lwi $r1,[$r6+#0x68]
    3e70:	a9 f4       	swi333 $r7,[$r6+#0x10]
    3e72:	04 00 80 0b 	lwi $r0,[$r1+#0x2c]
    3e76:	4e 02 00 f5 	beqz $r0,4060 <lfs_init+0x288>
    3e7a:	54 20 00 07 	andi $r2,$r0,#0x7
    3e7e:	4e 23 00 79 	bnez $r2,3f70 <lfs_init+0x198>
    3e82:	04 20 80 0e 	lwi $r2,[$r1+#0x38]
    3e86:	54 31 00 03 	andi $r3,$r2,#0x3
    3e8a:	4e 33 00 73 	bnez $r3,3f70 <lfs_init+0x198>
    3e8e:	c2 63       	beqz38 $r2,3f54 <lfs_init+0x17c>
    3e90:	14 23 00 19 	swi $r2,[$r6+#0x64]
    3e94:	04 00 80 0f 	lwi $r0,[$r1+#0x3c]
    3e98:	5c f0 01 00 	slti $r15,$r0,#0x100
    3e9c:	4e f2 00 8e 	beqz $r15,3fb8 <lfs_init+0x1e0>
    3ea0:	4e 02 00 3a 	beqz $r0,3f14 <lfs_init+0x13c>
    3ea4:	14 03 00 1b 	swi $r0,[$r6+#0x6c]
    3ea8:	04 00 80 10 	lwi $r0,[$r1+#0x40]
    3eac:	4e 05 00 f2 	bltz $r0,4090 <lfs_init+0x2b8>
    3eb0:	4e 02 00 36 	beqz $r0,3f1c <lfs_init+0x144>
    3eb4:	14 03 00 1c 	swi $r0,[$r6+#0x70]
    3eb8:	04 00 80 11 	lwi $r0,[$r1+#0x44]
    3ebc:	5c f0 03 ff 	slti $r15,$r0,#0x3ff
    3ec0:	4e f2 00 b8 	beqz $r15,4030 <lfs_init+0x258>
    3ec4:	c8 03       	bnez38 $r0,3eca <lfs_init+0xf2>
    3ec6:	44 00 03 fe 	movi $r0,#0x3fe
    3eca:	84 7f       	movi55 $r3,#-1
    3ecc:	14 03 00 1d 	swi $r0,[$r6+#0x74]
    3ed0:	84 00       	movi55 $r0,#0x0
    3ed2:	14 33 00 08 	swi $r3,[$r6+#0x20]
    3ed6:	14 33 00 09 	swi $r3,[$r6+#0x24]
    3eda:	84 20       	movi55 $r1,#0x0
    3edc:	84 4c       	movi55 $r2,#0xc
    3ede:	14 03 00 0a 	swi $r0,[$r6+#0x28]
    3ee2:	14 03 00 0b 	swi $r0,[$r6+#0x2c]
    3ee6:	50 03 00 3c 	addi $r0,$r6,#0x3c
    3eea:	49 00 30 69 	jal 9fbc <memset>
    3eee:	84 20       	movi55 $r1,#0x0
    3ef0:	44 20 00 0c 	movi $r2,#0xc
    3ef4:	50 03 00 30 	addi $r0,$r6,#0x30
    3ef8:	49 00 30 62 	jal 9fbc <memset>
    3efc:	50 03 00 48 	addi $r0,$r6,#0x48
    3f00:	84 20       	movi55 $r1,#0x0
    3f02:	84 4c       	movi55 $r2,#0xc
    3f04:	49 00 30 5c 	jal 9fbc <memset>
    3f08:	84 00       	movi55 $r0,#0x0
    3f0a:	92 00       	nop16
    3f0c:	3a 6f a0 84 	lmw.bim $r6,[$sp],$r8,#0x2    ! {$r6~$r8, $lp}
    3f10:	dd 9e       	ret5 $lp
    3f12:	92 00       	nop16
    3f14:	44 00 00 ff 	movi $r0,#0xff
    3f18:	48 ff ff c6 	j 3ea4 <lfs_init+0xcc>
    3f1c:	46 07 ff ff 	sethi $r0,#0x7ffff
    3f20:	50 00 0f ff 	addi $r0,$r0,#0xfff
    3f24:	d5 c8       	j8 3eb4 <lfs_init+0xdc>
    3f26:	80 02       	mov55 $r0,$r2
    3f28:	49 00 2f ea 	jal 9efc <malloc>
    3f2c:	a8 37       	swi333 $r0,[$r6+#0x1c]
    3f2e:	c0 1c       	beqz38 $r0,3f66 <lfs_init+0x18e>
    3f30:	04 03 00 1a 	lwi $r0,[$r6+#0x68]
    3f34:	04 20 00 0a 	lwi $r2,[$r0+#0x28]
    3f38:	48 ff ff 8a 	j 3e4c <lfs_init+0x74>
    3f3c:	80 02       	mov55 $r0,$r2
    3f3e:	49 00 2f df 	jal 9efc <malloc>
    3f42:	a8 33       	swi333 $r0,[$r6+#0xc]
    3f44:	c0 11       	beqz38 $r0,3f66 <lfs_init+0x18e>
    3f46:	04 13 00 1a 	lwi $r1,[$r6+#0x68]
    3f4a:	04 20 80 0a 	lwi $r2,[$r1+#0x28]
    3f4e:	48 ff ff 79 	j 3e40 <lfs_init+0x68>
    3f52:	92 00       	nop16
    3f54:	49 00 2f d4 	jal 9efc <malloc>
    3f58:	14 03 00 19 	swi $r0,[$r6+#0x64]
    3f5c:	c0 05       	beqz38 $r0,3f66 <lfs_init+0x18e>
    3f5e:	04 13 00 1a 	lwi $r1,[$r6+#0x68]
    3f62:	48 ff ff 99 	j 3e94 <lfs_init+0xbc>
    3f66:	80 06       	mov55 $r0,$r6
    3f68:	49 ff fb 8c 	jal 3680 <lfs_deinit>
    3f6c:	84 14       	movi55 $r0,#-12
    3f6e:	d5 cf       	j8 3f0c <lfs_init+0x134>
    3f70:	44 00 36 d4 	movi $r0,#0x36d4
    3f74:	44 10 0d c1 	movi $r1,#0xdc1
    3f78:	44 20 7b dc 	movi $r2,#0x7bdc
    3f7c:	44 30 38 7c 	movi $r3,#0x387c
    3f80:	49 00 2e 4e 	jal 9c1c <__assert_func>
    3f84:	92 00       	nop16
    3f86:	92 00       	nop16
    3f88:	44 00 36 d4 	movi $r0,#0x36d4
    3f8c:	44 10 0d 99 	movi $r1,#0xd99
    3f90:	44 20 7b dc 	movi $r2,#0x7bdc
    3f94:	44 30 37 f4 	movi $r3,#0x37f4
    3f98:	49 00 2e 42 	jal 9c1c <__assert_func>
    3f9c:	92 00       	nop16
    3f9e:	92 00       	nop16
    3fa0:	44 00 36 d4 	movi $r0,#0x36d4
    3fa4:	44 10 0d 95 	movi $r1,#0xd95
    3fa8:	44 20 7b dc 	movi $r2,#0x7bdc
    3fac:	44 30 37 c0 	movi $r3,#0x37c0
    3fb0:	49 00 2e 36 	jal 9c1c <__assert_func>
    3fb4:	92 00       	nop16
    3fb6:	92 00       	nop16
    3fb8:	44 00 36 d4 	movi $r0,#0x36d4
    3fbc:	44 10 0d cd 	movi $r1,#0xdcd
    3fc0:	44 20 7b dc 	movi $r2,#0x7bdc
    3fc4:	44 30 38 d0 	movi $r3,#0x38d0
    3fc8:	49 00 2e 2a 	jal 9c1c <__assert_func>
    3fcc:	92 00       	nop16
    3fce:	92 00       	nop16
    3fd0:	44 00 36 d4 	movi $r0,#0x36d4
    3fd4:	44 10 0d 93 	movi $r1,#0xd93
    3fd8:	44 20 7b dc 	movi $r2,#0x7bdc
    3fdc:	44 30 37 60 	movi $r3,#0x3760
    3fe0:	49 00 2e 1e 	jal 9c1c <__assert_func>
    3fe4:	92 00       	nop16
    3fe6:	92 00       	nop16
    3fe8:	44 00 36 d4 	movi $r0,#0x36d4
    3fec:	44 10 0d a1 	movi $r1,#0xda1
    3ff0:	44 20 7b dc 	movi $r2,#0x7bdc
    3ff4:	44 30 38 40 	movi $r3,#0x3840
    3ff8:	49 00 2e 12 	jal 9c1c <__assert_func>
    3ffc:	92 00       	nop16
    3ffe:	92 00       	nop16
    4000:	44 00 36 d4 	movi $r0,#0x36d4
    4004:	44 10 0d 94 	movi $r1,#0xd94
    4008:	44 20 7b dc 	movi $r2,#0x7bdc
    400c:	44 30 37 90 	movi $r3,#0x3790
    4010:	49 00 2e 06 	jal 9c1c <__assert_func>
    4014:	92 00       	nop16
    4016:	92 00       	nop16
    4018:	44 00 36 d4 	movi $r0,#0x36d4
    401c:	44 10 0d 8d 	movi $r1,#0xd8d
    4020:	44 20 7b dc 	movi $r2,#0x7bdc
    4024:	44 30 37 0c 	movi $r3,#0x370c
    4028:	49 00 2d fa 	jal 9c1c <__assert_func>
    402c:	92 00       	nop16
    402e:	92 00       	nop16
    4030:	44 00 36 d4 	movi $r0,#0x36d4
    4034:	44 10 0d d9 	movi $r1,#0xdd9
    4038:	44 20 7b dc 	movi $r2,#0x7bdc
    403c:	44 30 39 10 	movi $r3,#0x3910
    4040:	49 00 2d ee 	jal 9c1c <__assert_func>
    4044:	92 00       	nop16
    4046:	92 00       	nop16
    4048:	44 00 36 d4 	movi $r0,#0x36d4
    404c:	44 10 0d 8f 	movi $r1,#0xd8f
    4050:	44 20 7b dc 	movi $r2,#0x7bdc
    4054:	44 30 37 44 	movi $r3,#0x3744
    4058:	49 00 2d e2 	jal 9c1c <__assert_func>
    405c:	92 00       	nop16
    405e:	92 00       	nop16
    4060:	44 00 36 d4 	movi $r0,#0x36d4
    4064:	44 10 0d bf 	movi $r1,#0xdbf
    4068:	44 20 7b dc 	movi $r2,#0x7bdc
    406c:	44 30 38 5c 	movi $r3,#0x385c
    4070:	49 00 2d d6 	jal 9c1c <__assert_func>
    4074:	92 00       	nop16
    4076:	92 00       	nop16
    4078:	44 00 36 d4 	movi $r0,#0x36d4
    407c:	44 10 0d 8e 	movi $r1,#0xd8e
    4080:	44 20 7b dc 	movi $r2,#0x7bdc
    4084:	44 30 37 28 	movi $r3,#0x3728
    4088:	49 00 2d ca 	jal 9c1c <__assert_func>
    408c:	92 00       	nop16
    408e:	92 00       	nop16
    4090:	44 00 36 d4 	movi $r0,#0x36d4
    4094:	44 10 0d d3 	movi $r1,#0xdd3
    4098:	44 20 7b dc 	movi $r2,#0x7bdc
    409c:	44 30 38 ec 	movi $r3,#0x38ec
    40a0:	49 00 2d be 	jal 9c1c <__assert_func>
    40a4:	92 00       	nop16
    40a6:	92 00       	nop16

000040a8 <lfs_bd_read.isra.13>:
    40a8:	3a 6f b8 bc 	smw.adm $r6,[$sp],$r14,#0x2    ! {$r6~$r14, $lp}
    40ac:	b5 80       	lwi450 $r16,[$r0]
    40ae:	81 80       	mov55 $r12,$r0
    40b0:	04 08 00 08 	lwi $r0,[$r16+#0x20]
    40b4:	81 24       	mov55 $r9,$r4
    40b6:	e2 80       	slt45 $r4,$r0
    40b8:	f6 0a       	lwi37.sp $r6,[+#0x28]
    40ba:	04 af 80 0b 	lwi $r10,[$sp+#0x2c]
    40be:	4e f2 00 9d 	beqz $r15,41f8 <lfs_bd_read.isra.13+0x150>
    40c2:	04 08 00 07 	lwi $r0,[$r16+#0x1c]
    40c6:	81 a1       	mov55 $r13,$r1
    40c8:	40 12 a8 00 	add $r1,$r5,$r10
    40cc:	e2 01       	slt45 $r0,$r1
    40ce:	80 e5       	mov55 $r7,$r5
    40d0:	4e f3 00 94 	bnez $r15,41f8 <lfs_bd_read.isra.13+0x150>
    40d4:	81 02       	mov55 $r8,$r2
    40d6:	81 63       	mov55 $r11,$r3
    40d8:	4e a3 00 36 	bnez $r10,4144 <lfs_bd_read.isra.13+0x9c>
    40dc:	d5 60       	j8 419c <lfs_bd_read.isra.13+0xf4>
    40de:	b4 0c       	lwi450 $r0,[$r12]
    40e0:	04 e0 00 05 	lwi $r14,[$r0+#0x14]
    40e4:	40 33 b8 37 	divr $r3,$r1,$r7,$r14
    40e8:	c9 04       	bnez38 $r1,40f0 <lfs_bd_read.isra.13+0x48>
    40ea:	e3 4e       	slt45 $r10,$r14
    40ec:	4e f2 00 5e 	beqz $r15,41a8 <lfs_bd_read.isra.13+0x100>
    40f0:	04 20 00 08 	lwi $r2,[$r0+#0x20]
    40f4:	e3 22       	slt45 $r9,$r2
    40f6:	4e f2 00 85 	beqz $r15,4200 <lfs_bd_read.isra.13+0x158>
    40fa:	05 10 00 05 	lwi $r17,[$r0+#0x14]
    40fe:	a1 07       	lwi333 $r4,[$r0+#0x1c]
    4100:	51 08 ff ff 	addi $r16,$r17,#-1
    4104:	89 8b       	add45 $r16,$r11
    4106:	89 87       	add45 $r16,$r7
    4108:	40 28 44 37 	divr $r2,$r1,$r16,$r17
    410c:	41 13 c4 57 	divr $r17,$r2,$r7,$r17
    4110:	8b 81       	sub45 $r16,$r1
    4112:	e2 90       	slt45 $r4,$r16
    4114:	04 50 00 0a 	lwi $r5,[$r0+#0x28]
    4118:	9a ba       	sub333 $r2,$r7,$r2
    411a:	41 02 3c 1b 	cmovn $r16,$r4,$r15
    411e:	8b 82       	sub45 $r16,$r2
    4120:	e2 b0       	slt45 $r5,$r16
    4122:	40 58 3c 1a 	cmovz $r5,$r16,$r15
    4126:	80 85       	mov55 $r4,$r5
    4128:	a1 41       	lwi333 $r5,[$r0+#0x4]
    412a:	80 29       	mov55 $r1,$r9
    412c:	b7 28       	swi450 $r9,[$r8]
    412e:	14 24 00 01 	swi $r2,[$r8+#0x4]
    4132:	14 44 00 02 	swi $r4,[$r8+#0x8]
    4136:	04 34 00 03 	lwi $r3,[$r8+#0xc]
    413a:	dd 25       	jral5 $r5
    413c:	4e 06 00 6e 	bgtz $r0,4218 <lfs_bd_read.isra.13+0x170>
    4140:	c8 30       	bnez38 $r0,41a0 <lfs_bd_read.isra.13+0xf8>
    4142:	92 00       	nop16
    4144:	4e d2 00 1c 	beqz $r13,417c <lfs_bd_read.isra.13+0xd4>
    4148:	b4 0d       	lwi450 $r0,[$r13]
    414a:	80 4a       	mov55 $r2,$r10
    414c:	4c 90 00 1a 	beq $r9,$r0,4180 <lfs_bd_read.isra.13+0xd8>
    4150:	b4 08       	lwi450 $r0,[$r8]
    4152:	4c 90 00 07 	beq $r9,$r0,4160 <lfs_bd_read.isra.13+0xb8>
    4156:	92 00       	nop16
    4158:	e3 4b       	slt45 $r10,$r11
    415a:	e8 c2       	beqzs8 40de <lfs_bd_read.isra.13+0x36>
    415c:	b4 0c       	lwi450 $r0,[$r12]
    415e:	d5 c9       	j8 40f0 <lfs_bd_read.isra.13+0x48>
    4160:	04 34 00 01 	lwi $r3,[$r8+#0x4]
    4164:	04 04 00 02 	lwi $r0,[$r8+#0x8]
    4168:	88 03       	add45 $r0,$r3
    416a:	e2 e0       	slt45 $r7,$r0
    416c:	e8 f6       	beqzs8 4158 <lfs_bd_read.isra.13+0xb0>
    416e:	e2 e3       	slt45 $r7,$r3
    4170:	e8 2b       	beqzs8 41c6 <lfs_bd_read.isra.13+0x11e>
    4172:	8a 67       	sub45 $r3,$r7
    4174:	e2 62       	slt45 $r3,$r2
    4176:	40 21 bc 1b 	cmovn $r2,$r3,$r15
    417a:	d5 ef       	j8 4158 <lfs_bd_read.isra.13+0xb0>
    417c:	80 4a       	mov55 $r2,$r10
    417e:	d5 e9       	j8 4150 <lfs_bd_read.isra.13+0xa8>
    4180:	04 36 80 01 	lwi $r3,[$r13+#0x4]
    4184:	04 06 80 02 	lwi $r0,[$r13+#0x8]
    4188:	88 03       	add45 $r0,$r3
    418a:	e2 e0       	slt45 $r7,$r0
    418c:	e8 f8       	beqzs8 417c <lfs_bd_read.isra.13+0xd4>
    418e:	e2 e3       	slt45 $r7,$r3
    4190:	e8 29       	beqzs8 41e2 <lfs_bd_read.isra.13+0x13a>
    4192:	9a 9f       	sub333 $r2,$r3,$r7
    4194:	e3 42       	slt45 $r10,$r2
    4196:	40 25 3c 1b 	cmovn $r2,$r10,$r15
    419a:	d5 db       	j8 4150 <lfs_bd_read.isra.13+0xa8>
    419c:	84 00       	movi55 $r0,#0x0
    419e:	92 00       	nop16
    41a0:	3a 6f b8 84 	lmw.bim $r6,[$sp],$r14,#0x2    ! {$r6~$r14, $lp}
    41a4:	dd 9e       	ret5 $lp
    41a6:	92 00       	nop16
    41a8:	40 11 39 d7 	divr $r1,$r14,$r2,$r14
    41ac:	a1 41       	lwi333 $r5,[$r0+#0x4]
    41ae:	40 e1 38 01 	sub $r14,$r2,$r14
    41b2:	80 29       	mov55 $r1,$r9
    41b4:	80 47       	mov55 $r2,$r7
    41b6:	80 66       	mov55 $r3,$r6
    41b8:	80 8e       	mov55 $r4,$r14
    41ba:	dd 25       	jral5 $r5
    41bc:	c8 f2       	bnez38 $r0,41a0 <lfs_bd_read.isra.13+0xf8>
    41be:	88 ce       	add45 $r6,$r14
    41c0:	88 ee       	add45 $r7,$r14
    41c2:	8b 4e       	sub45 $r10,$r14
    41c4:	d5 8a       	j8 40d8 <lfs_bd_read.isra.13+0x30>
    41c6:	8a 07       	sub45 $r0,$r7
    41c8:	e2 02       	slt45 $r0,$r2
    41ca:	04 44 00 03 	lwi $r4,[$r8+#0xc]
    41ce:	40 01 3c 1a 	cmovz $r0,$r2,$r15
    41d2:	9a 7b       	sub333 $r1,$r7,$r3
    41d4:	81 c0       	mov55 $r14,$r0
    41d6:	88 24       	add45 $r1,$r4
    41d8:	80 06       	mov55 $r0,$r6
    41da:	80 4e       	mov55 $r2,$r14
    41dc:	49 00 2e bc 	jal 9f54 <memcpy>
    41e0:	d5 ef       	j8 41be <lfs_bd_read.isra.13+0x116>
    41e2:	8a 07       	sub45 $r0,$r7
    41e4:	e3 40       	slt45 $r10,$r0
    41e6:	04 26 80 03 	lwi $r2,[$r13+#0xc]
    41ea:	40 05 3c 1b 	cmovn $r0,$r10,$r15
    41ee:	9a 7b       	sub333 $r1,$r7,$r3
    41f0:	81 c0       	mov55 $r14,$r0
    41f2:	88 22       	add45 $r1,$r2
    41f4:	80 06       	mov55 $r0,$r6
    41f6:	d5 f2       	j8 41da <lfs_bd_read.isra.13+0x132>
    41f8:	44 0f ff ac 	movi $r0,#-84
    41fc:	d5 d2       	j8 41a0 <lfs_bd_read.isra.13+0xf8>
    41fe:	92 00       	nop16
    4200:	44 00 36 d4 	movi $r0,#0x36d4
    4204:	44 10 00 5a 	movi $r1,#0x5a
    4208:	44 20 7c c4 	movi $r2,#0x7cc4
    420c:	44 30 39 ac 	movi $r3,#0x39ac
    4210:	49 00 2d 06 	jal 9c1c <__assert_func>
    4214:	92 00       	nop16
    4216:	92 00       	nop16
    4218:	44 00 36 d4 	movi $r0,#0x36d4
    421c:	44 10 00 65 	movi $r1,#0x65
    4220:	44 20 7c c4 	movi $r2,#0x7cc4
    4224:	44 30 39 2c 	movi $r3,#0x392c
    4228:	49 00 2c fa 	jal 9c1c <__assert_func>
    422c:	92 00       	nop16
    422e:	92 00       	nop16

00004230 <lfs_fs_parent_match>:
    4230:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    4234:	ef f0       	addi10.sp #-16
    4236:	b4 60       	lwi450 $r3,[$r0]
    4238:	80 c0       	mov55 $r6,$r0
    423a:	b0 02       	addri36.sp $r0,#0x8
    423c:	04 41 80 1a 	lwi $r4,[$r3+#0x68]
    4240:	b6 1f       	swi450 $r0,[$sp]
    4242:	84 08       	movi55 $r0,#0x8
    4244:	f0 81       	swi37.sp $r0,[+#0x4]
    4246:	80 a2       	mov55 $r5,$r2
    4248:	50 01 80 68 	addi $r0,$r3,#0x68
    424c:	50 11 80 10 	addi $r1,$r3,#0x10
    4250:	80 43       	mov55 $r2,$r3
    4252:	a0 e7       	lwi333 $r3,[$r4+#0x1c]
    4254:	b4 85       	lwi450 $r4,[$r5]
    4256:	a1 69       	lwi333 $r5,[$r5+#0x4]
    4258:	49 ff ff 28 	jal 40a8 <lfs_bd_read.isra.13>
    425c:	c8 0c       	bnez38 $r0,4274 <lfs_fs_parent_match+0x44>
    425e:	f5 02       	lwi37.sp $r5,[+#0x8]
    4260:	a0 f1       	lwi333 $r3,[$r6+#0x4]
    4262:	d3 0d       	beqs38 $r3,427c <lfs_fs_parent_match+0x4c>
    4264:	f1 03       	lwi37.sp $r1,[+#0xc]
    4266:	a1 32       	lwi333 $r4,[$r6+#0x8]
    4268:	4c 12 00 0a 	beq $r1,$r4,427c <lfs_fs_parent_match+0x4c>
    426c:	d4 08       	beqs38 $r4,427c <lfs_fs_parent_match+0x4c>
    426e:	fe 5d       	xor33 $r1,$r3
    4270:	40 00 04 06 	slt $r0,$r0,$r1
    4274:	ec 10       	addi10.sp #0x10
    4276:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    427a:	dd 9e       	ret5 $lp
    427c:	84 00       	movi55 $r0,#0x0
    427e:	ec 10       	addi10.sp #0x10
    4280:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    4284:	dd 9e       	ret5 $lp
    4286:	92 00       	nop16
    4288:	ff ff       	or33 $r7,$r7
    428a:	ff ff       	or33 $r7,$r7
    428c:	ff ff       	or33 $r7,$r7
    428e:	ff ff       	or33 $r7,$r7

00004290 <lfs_dir_fetchmatch>:
    4290:	05 00 00 1a 	lwi $r16,[$r0+#0x68]
    4294:	b5 c2       	lwi450 $r18,[$r2]
    4296:	05 18 00 08 	lwi $r17,[$r16+#0x20]
    429a:	e3 d1       	slt45 $r18,$r17
    429c:	4e f2 02 94 	beqz $r15,47c4 <lfs_dir_fetchmatch+0x534>
    42a0:	05 01 00 01 	lwi $r16,[$r2+#0x4]
    42a4:	e3 91       	slt45 $r16,$r17
    42a6:	4e f2 02 8f 	beqz $r15,47c4 <lfs_dir_fetchmatch+0x534>
    42aa:	3a 6f ba bc 	smw.adm $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    42ae:	ef 7c       	addi10.sp #-132
    42b0:	36 3f 80 10 	fsdi $fd3,[$sp+#0x40]
    42b4:	36 4f 80 12 	fsdi $fd4,[$sp+#0x48]
    42b8:	36 5f 80 14 	fsdi $fd5,[$sp+#0x50]
    42bc:	36 6f 80 16 	fsdi $fd6,[$sp+#0x58]
    42c0:	36 7f 80 18 	fsdi $fd7,[$sp+#0x60]
    42c4:	36 8f 80 1a 	fsdi $fd8,[$sp+#0x68]
    42c8:	36 9f 80 1c 	fsdi $fd9,[$sp+#0x70]
    42cc:	36 af 80 1e 	fsdi $fd10,[$sp+#0x78]
    42d0:	80 c0       	mov55 $r6,$r0
    42d2:	51 c0 00 68 	addi $fp,$r0,#0x68
    42d6:	b0 0a       	addri36.sp $r0,#0x28
    42d8:	b6 1f       	swi450 $r0,[$sp]
    42da:	84 04       	movi55 $r0,#0x4
    42dc:	86 00       	movi55 $r16,#0x0
    42de:	6a 58 80 09 	fmtsr $r5,$fs17
    42e2:	6a 45 80 09 	fmtsr $r4,$fs11
    42e6:	6a 35 00 09 	fmtsr $r3,$fs10
    42ea:	81 41       	mov55 $r10,$r1
    42ec:	80 e2       	mov55 $r7,$r2
    42ee:	f0 81       	swi37.sp $r0,[+#0x4]
    42f0:	84 20       	movi55 $r1,#0x0
    42f2:	80 1c       	mov55 $r0,$fp
    42f4:	80 46       	mov55 $r2,$r6
    42f6:	84 64       	movi55 $r3,#0x4
    42f8:	80 92       	mov55 $r4,$r18
    42fa:	84 a0       	movi55 $r5,#0x0
    42fc:	15 0f 80 0a 	swi $r16,[$sp+#0x28]
    4300:	15 0f 80 0b 	swi $r16,[$sp+#0x2c]
    4304:	49 ff fe d2 	jal 40a8 <lfs_bd_read.isra.13>
    4308:	4e 02 00 06 	beqz $r0,4314 <lfs_dir_fetchmatch+0x84>
    430c:	5a 07 ac 04 	beqc $r0,#-84,4314 <lfs_dir_fetchmatch+0x84>
    4310:	48 00 01 84 	j 4618 <lfs_dir_fetchmatch+0x388>
    4314:	b0 0b       	addri36.sp $r0,#0x2c
    4316:	b6 1f       	swi450 $r0,[$sp]
    4318:	84 04       	movi55 $r0,#0x4
    431a:	f0 81       	swi37.sp $r0,[+#0x4]
    431c:	84 20       	movi55 $r1,#0x0
    431e:	80 1c       	mov55 $r0,$fp
    4320:	80 46       	mov55 $r2,$r6
    4322:	84 64       	movi55 $r3,#0x4
    4324:	a1 39       	lwi333 $r4,[$r7+#0x4]
    4326:	84 a0       	movi55 $r5,#0x0
    4328:	49 ff fe c0 	jal 40a8 <lfs_bd_read.isra.13>
    432c:	f1 0b       	lwi37.sp $r1,[+#0x2c]
    432e:	4e 03 01 e4 	bnez $r0,46f6 <lfs_dir_fetchmatch+0x466>
    4332:	f2 0a       	lwi37.sp $r2,[+#0x28]
    4334:	8a 22       	sub45 $r1,$r2
    4336:	e0 01       	slts45 $r0,$r1
    4338:	38 03 be 02 	lw $r0,[$r7+($r15<<#0x2)]
    433c:	b6 0a       	swi450 $r0,[$r10]
    433e:	56 07 80 01 	xori $r0,$r15,#0x1
    4342:	38 23 82 02 	lw $r2,[$r7+($r0<<#0x2)]
    4346:	6a 09 00 09 	fmtsr $r0,$fs18
    434a:	b0 0a       	addri36.sp $r0,#0x28
    434c:	38 00 3e 02 	lw $r0,[$r0+($r15<<#0x2)]
    4350:	14 05 00 02 	swi $r0,[$r10+#0x8]
    4354:	84 00       	movi55 $r0,#0x0
    4356:	14 05 00 03 	swi $r0,[$r10+#0xc]
    435a:	50 05 00 08 	addi $r0,$r10,#0x8
    435e:	6a 0a 00 09 	fmtsr $r0,$fs20
    4362:	84 02       	movi55 $r0,#0x2
    4364:	6a 09 80 09 	fmtsr $r0,$fs19
    4368:	84 1f       	movi55 $r0,#-1
    436a:	6a 03 00 09 	fmtsr $r0,$fs6
    436e:	b0 0c       	addri36.sp $r0,#0x30
    4370:	6a 07 00 09 	fmtsr $r0,$fs14
    4374:	44 00 42 88 	movi $r0,#0x4288
    4378:	6a 07 80 09 	fmtsr $r0,$fs15
    437c:	46 07 00 00 	sethi $r0,#0x70000
    4380:	6a 04 80 09 	fmtsr $r0,$fs9
    4384:	46 00 ff 00 	sethi $r0,#0xff00
    4388:	6a 0a 80 09 	fmtsr $r0,$fs21
    438c:	46 07 ff ff 	sethi $r0,#0x7ffff
    4390:	50 00 0c 00 	addi $r0,$r0,#0xc00
    4394:	6a 08 00 09 	fmtsr $r0,$fs16
    4398:	46 00 00 ff 	sethi $r0,#0xff
    439c:	50 00 0c 00 	addi $r0,$r0,#0xc00
    43a0:	6a 03 80 09 	fmtsr $r0,$fs7
    43a4:	14 25 00 01 	swi $r2,[$r10+#0x4]
    43a8:	50 bf 80 20 	addi $r11,$sp,#0x20
    43ac:	6a 07 80 01 	fmfsr $r0,$fs15
    43b0:	6a 37 00 01 	fmfsr $r3,$fs14
    43b4:	6a 1a 00 01 	fmfsr $r1,$fs20
    43b8:	3b 00 44 00 	lmw.bi $r16,[$r0],$r17,#0x0    ! {$r16~$r17}
    43bc:	84 44       	movi55 $r2,#0x4
    43be:	84 1f       	movi55 $r0,#-1
    43c0:	3b 01 c4 20 	smw.bi $r16,[$r3],$r17,#0x0    ! {$r16~$r17}
    43c4:	49 00 1c 86 	jal 7cd0 <lfs_crc>
    43c8:	80 e0       	mov55 $r7,$r0
    43ca:	6a d3 18 c0 	fcpyss $fs13,$fs6,$fs6
    43ce:	84 00       	movi55 $r0,#0x0
    43d0:	f0 87       	swi37.sp $r0,[+#0x1c]
    43d2:	f0 86       	swi37.sp $r0,[+#0x18]
    43d4:	85 bf       	movi55 $r13,#-1
    43d6:	85 20       	movi55 $r9,#0x0
    43d8:	40 06 d8 08 	slli $r0,$r13,#0x16
    43dc:	90 16       	srai45 $r0,#0x16
    43de:	8c 01       	addi45 $r0,#0x1
    43e0:	e6 01       	slti45 $r0,#0x1
    43e2:	40 f7 b4 00 	add $r15,$r15,$r13
    43e6:	54 07 83 ff 	andi $r0,$r15,#0x3ff
    43ea:	04 33 00 1a 	lwi $r3,[$r6+#0x68]
    43ee:	84 24       	movi55 $r1,#0x4
    43f0:	8c 04       	addi45 $r0,#0x4
    43f2:	f1 81       	swi37.sp $r1,[+#0x4]
    43f4:	b7 7f       	swi450 $r11,[$sp]
    43f6:	89 20       	add45 $r9,$r0
    43f8:	6a 14 00 09 	fmtsr $r1,$fs8
    43fc:	80 1c       	mov55 $r0,$fp
    43fe:	84 20       	movi55 $r1,#0x0
    4400:	80 46       	mov55 $r2,$r6
    4402:	a0 df       	lwi333 $r3,[$r3+#0x1c]
    4404:	b4 8a       	lwi450 $r4,[$r10]
    4406:	80 a9       	mov55 $r5,$r9
    4408:	49 ff fe 50 	jal 40a8 <lfs_bd_read.isra.13>
    440c:	81 00       	mov55 $r8,$r0
    440e:	4e 03 01 c1 	bnez $r0,4790 <lfs_dir_fetchmatch+0x500>
    4412:	80 07       	mov55 $r0,$r7
    4414:	80 2b       	mov55 $r1,$r11
    4416:	84 44       	movi55 $r2,#0x4
    4418:	49 00 1c 5c 	jal 7cd0 <lfs_crc>
    441c:	80 e0       	mov55 $r7,$r0
    441e:	f0 08       	lwi37.sp $r0,[+#0x20]
    4420:	40 00 00 14 	wsbh $r0,$r0
    4424:	40 00 40 0b 	rotri $r0,$r0,#0x10
    4428:	40 c0 34 03 	xor $r12,$r0,$r13
    442c:	14 cf 80 08 	swi $r12,[$sp+#0x20]
    4430:	4e c5 01 b6 	bltz $r12,479c <lfs_dir_fetchmatch+0x50c>
    4434:	40 06 58 08 	slli $r0,$r12,#0x16
    4438:	90 16       	srai45 $r0,#0x16
    443a:	8c 01       	addi45 $r0,#0x1
    443c:	e6 01       	slti45 $r0,#0x1
    443e:	04 13 00 1a 	lwi $r1,[$r6+#0x68]
    4442:	40 f7 b0 00 	add $r15,$r15,$r12
    4446:	54 07 83 ff 	andi $r0,$r15,#0x3ff
    444a:	a0 cf       	lwi333 $r3,[$r1+#0x1c]
    444c:	8c 04       	addi45 $r0,#0x4
    444e:	40 10 24 00 	add $r1,$r0,$r9
    4452:	e2 61       	slt45 $r3,$r1
    4454:	4e f3 01 98 	bnez $r15,4784 <lfs_dir_fetchmatch+0x4f4>
    4458:	6a 14 80 01 	fmfsr $r1,$fs9
    445c:	44 20 05 00 	movi $r2,#0x500
    4460:	40 56 04 02 	and $r5,$r12,$r1
    4464:	92 b4       	srli45 $r5,#0x14
    4466:	4c 51 00 99 	beq $r5,$r2,4598 <lfs_dir_fetchmatch+0x308>
    446a:	5a 08 04 05 	bnec $r0,#0x4,4474 <lfs_dir_fetchmatch+0x1e4>
    446e:	48 00 01 4a 	j 4702 <lfs_dir_fetchmatch+0x472>
    4472:	92 00       	nop16
    4474:	85 c4       	movi55 $r14,#0x4
    4476:	50 8f 80 24 	addi $r8,$sp,#0x24
    447a:	85 a1       	movi55 $r13,#0x1
    447c:	d5 17       	j8 44aa <lfs_dir_fetchmatch+0x21a>
    447e:	92 00       	nop16
    4480:	49 00 1c 28 	jal 7cd0 <lfs_crc>
    4484:	f5 08       	lwi37.sp $r5,[+#0x20]
    4486:	80 e0       	mov55 $r7,$r0
    4488:	40 02 d8 08 	slli $r0,$r5,#0x16
    448c:	90 16       	srai45 $r0,#0x16
    448e:	8c 01       	addi45 $r0,#0x1
    4490:	5c 00 00 01 	slti $r0,$r0,#0x1
    4494:	88 05       	add45 $r0,$r5
    4496:	54 00 03 ff 	andi $r0,$r0,#0x3ff
    449a:	8c 04       	addi45 $r0,#0x4
    449c:	40 07 00 06 	slt $r0,$r14,$r0
    44a0:	4e 02 00 76 	beqz $r0,458c <lfs_dir_fetchmatch+0x2fc>
    44a4:	04 03 00 1a 	lwi $r0,[$r6+#0x68]
    44a8:	a0 c7       	lwi333 $r3,[$r0+#0x1c]
    44aa:	b4 8a       	lwi450 $r4,[$r10]
    44ac:	40 57 24 00 	add $r5,$r14,$r9
    44b0:	80 46       	mov55 $r2,$r6
    44b2:	84 20       	movi55 $r1,#0x0
    44b4:	b7 1f       	swi450 $r8,[$sp]
    44b6:	14 df 80 01 	swi $r13,[$sp+#0x4]
    44ba:	80 1c       	mov55 $r0,$fp
    44bc:	49 ff fd f6 	jal 40a8 <lfs_bd_read.isra.13>
    44c0:	80 60       	mov55 $r3,$r0
    44c2:	50 e7 00 01 	addi $r14,$r14,#0x1
    44c6:	80 28       	mov55 $r1,$r8
    44c8:	84 41       	movi55 $r2,#0x1
    44ca:	80 07       	mov55 $r0,$r7
    44cc:	c3 da       	beqz38 $r3,4480 <lfs_dir_fetchmatch+0x1f0>
    44ce:	5a 37 ac 05 	beqc $r3,#-84,44d8 <lfs_dir_fetchmatch+0x248>
    44d2:	48 00 01 75 	j 47bc <lfs_dir_fetchmatch+0x52c>
    44d6:	92 00       	nop16
    44d8:	6a 04 80 01 	fmfsr $r0,$fs9
    44dc:	05 0f 80 08 	lwi $r16,[$sp+#0x20]
    44e0:	40 58 00 02 	and $r5,$r16,$r0
    44e4:	84 00       	movi55 $r0,#0x0
    44e6:	10 05 00 16 	sbi $r0,[$r10+#0x16]
    44ea:	92 b4       	srli45 $r5,#0x14
    44ec:	97 69       	zeh33 $r5,$r5
    44ee:	cd 2f       	bnez38 $r5,454c <lfs_dir_fetchmatch+0x2bc>
    44f0:	6a 03 80 01 	fmfsr $r0,$fs7
    44f4:	f1 06       	lwi37.sp $r1,[+#0x18]
    44f6:	40 08 00 02 	and $r0,$r16,$r0
    44fa:	92 0a       	srli45 $r0,#0xa
    44fc:	96 01       	zeh33 $r0,$r0
    44fe:	e2 01       	slt45 $r0,$r1
    4500:	e9 04       	bnezs8 4508 <lfs_dir_fetchmatch+0x278>
    4502:	8c 01       	addi45 $r0,#0x1
    4504:	96 01       	zeh33 $r0,$r0
    4506:	f0 86       	swi37.sp $r0,[+#0x18]
    4508:	6a 05 80 01 	fmfsr $r0,$fs11
    450c:	40 88 00 03 	xor $r8,$r16,$r0
    4510:	6a 05 00 01 	fmfsr $r0,$fs10
    4514:	40 84 00 02 	and $r8,$r8,$r0
    4518:	4e 82 00 06 	beqz $r8,4524 <lfs_dir_fetchmatch+0x294>
    451c:	81 ac       	mov55 $r13,$r12
    451e:	48 ff ff 5d 	j 43d8 <lfs_dir_fetchmatch+0x148>
    4522:	92 00       	nop16
    4524:	50 34 80 04 	addi $r3,$r9,#0x4
    4528:	b0 8e       	addri36.sp $r2,#0x38
    452a:	a8 d1       	swi333 $r3,[$r2+#0x4]
    452c:	f3 2c       	lwi37.sp $r3,[+#0xb0]
    452e:	b4 8a       	lwi450 $r4,[$r10]
    4530:	f0 2d       	lwi37.sp $r0,[+#0xb4]
    4532:	80 30       	mov55 $r1,$r16
    4534:	f4 8e       	swi37.sp $r4,[+#0x38]
    4536:	dd 23       	jral5 $r3
    4538:	4e 05 01 22 	bltz $r0,477c <lfs_dir_fetchmatch+0x4ec>
    453c:	4e 03 00 82 	bnez $r0,4640 <lfs_dir_fetchmatch+0x3b0>
    4540:	30 df 80 08 	flsi $fs13,[$sp+#0x20]
    4544:	81 ac       	mov55 $r13,$r12
    4546:	48 ff ff 49 	j 43d8 <lfs_dir_fetchmatch+0x148>
    454a:	92 00       	nop16
    454c:	44 00 04 00 	movi $r0,#0x400
    4550:	4c 50 00 9a 	beq $r5,$r0,4684 <lfs_dir_fetchmatch+0x3f4>
    4554:	44 00 06 00 	movi $r0,#0x600
    4558:	d8 d8       	bnes38 $r0,4508 <lfs_dir_fetchmatch+0x278>
    455a:	04 33 00 1a 	lwi $r3,[$r6+#0x68]
    455e:	84 08       	movi55 $r0,#0x8
    4560:	f0 81       	swi37.sp $r0,[+#0x4]
    4562:	32 ef 80 00 	fssi $fs14,[$sp+#0x0]
    4566:	43 08 50 0b 	btst $r16,$r16,#0x14
    456a:	80 1c       	mov55 $r0,$fp
    456c:	84 20       	movi55 $r1,#0x0
    456e:	80 46       	mov55 $r2,$r6
    4570:	a0 df       	lwi333 $r3,[$r3+#0x1c]
    4572:	b4 8a       	lwi450 $r4,[$r10]
    4574:	50 54 80 04 	addi $r5,$r9,#0x4
    4578:	15 0f 80 07 	swi $r16,[$sp+#0x1c]
    457c:	49 ff fd 96 	jal 40a8 <lfs_bd_read.isra.13>
    4580:	5a 07 ac 1f 	beqc $r0,#-84,45be <lfs_dir_fetchmatch+0x32e>
    4584:	05 0f 80 08 	lwi $r16,[$sp+#0x20]
    4588:	d5 c0       	j8 4508 <lfs_dir_fetchmatch+0x278>
    458a:	92 00       	nop16
    458c:	6a 04 80 01 	fmfsr $r0,$fs9
    4590:	82 05       	mov55 $r16,$r5
    4592:	ff 46       	and33 $r5,$r0
    4594:	92 b4       	srli45 $r5,#0x14
    4596:	d5 ab       	j8 44ec <lfs_dir_fetchmatch+0x25c>
    4598:	50 8f 80 24 	addi $r8,$sp,#0x24
    459c:	b7 1f       	swi450 $r8,[$sp]
    459e:	32 8f 80 01 	fssi $fs8,[$sp+#0x4]
    45a2:	80 1c       	mov55 $r0,$fp
    45a4:	84 20       	movi55 $r1,#0x0
    45a6:	80 46       	mov55 $r2,$r6
    45a8:	04 45 00 00 	lwi $r4,[$r10+#0x0]
    45ac:	50 54 80 04 	addi $r5,$r9,#0x4
    45b0:	49 ff fd 7c 	jal 40a8 <lfs_bd_read.isra.13>
    45b4:	4e 03 01 16 	bnez $r0,47e0 <lfs_dir_fetchmatch+0x550>
    45b8:	f0 09       	lwi37.sp $r0,[+#0x24]
    45ba:	4c 70 00 a7 	beq $r7,$r0,4708 <lfs_dir_fetchmatch+0x478>
    45be:	84 00       	movi55 $r0,#0x0
    45c0:	10 05 00 16 	sbi $r0,[$r10+#0x16]
    45c4:	04 05 00 03 	lwi $r0,[$r10+#0xc]
    45c8:	4e 03 01 12 	bnez $r0,47ec <lfs_dir_fetchmatch+0x55c>
    45cc:	6a 39 00 01 	fmfsr $r3,$fs18
    45d0:	b0 8a       	addri36.sp $r2,#0x28
    45d2:	38 21 0e 02 	lw $r2,[$r2+($r3<<#0x2)]
    45d6:	14 25 00 02 	swi $r2,[$r10+#0x8]
    45da:	6a 29 80 01 	fmfsr $r2,$fs19
    45de:	b4 0a       	lwi450 $r0,[$r10]
    45e0:	04 15 00 01 	lwi $r1,[$r10+#0x4]
    45e4:	b6 2a       	swi450 $r1,[$r10]
    45e6:	14 05 00 01 	swi $r0,[$r10+#0x4]
    45ea:	5a 20 01 05 	beqc $r2,#0x1,45f4 <lfs_dir_fetchmatch+0x364>
    45ee:	48 00 00 79 	j 46e0 <lfs_dir_fetchmatch+0x450>
    45f2:	92 00       	nop16
    45f4:	44 20 36 d4 	movi $r2,#0x36d4
    45f8:	b6 5f       	swi450 $r2,[$sp]
    45fa:	f0 83       	swi37.sp $r0,[+#0xc]
    45fc:	44 20 03 e6 	movi $r2,#0x3e6
    4600:	44 00 01 38 	movi $r0,#0x138
    4604:	f0 84       	swi37.sp $r0,[+#0x10]
    4606:	f2 81       	swi37.sp $r2,[+#0x4]
    4608:	14 1f 80 02 	swi $r1,[$sp+#0x8]
    460c:	44 00 39 38 	movi $r0,#0x3938
    4610:	49 ff ef 16 	jal 243c <printf>
    4614:	44 0f ff ac 	movi $r0,#-84
    4618:	ec 40       	addi10.sp #0x40
    461a:	34 3f 90 02 	fldi.bi $fd3,[$sp],#0x8
    461e:	34 4f 90 02 	fldi.bi $fd4,[$sp],#0x8
    4622:	34 5f 90 02 	fldi.bi $fd5,[$sp],#0x8
    4626:	34 6f 90 02 	fldi.bi $fd6,[$sp],#0x8
    462a:	34 7f 90 02 	fldi.bi $fd7,[$sp],#0x8
    462e:	34 8f 90 02 	fldi.bi $fd8,[$sp],#0x8
    4632:	34 9f 90 02 	fldi.bi $fd9,[$sp],#0x8
    4636:	34 af 90 03 	fldi.bi $fd10,[$sp],#0xc
    463a:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    463e:	dd 9e       	ret5 $lp
    4640:	f2 08       	lwi37.sp $r2,[+#0x20]
    4642:	6a 16 80 01 	fmfsr $r1,$fs13
    4646:	6a 38 00 01 	fmfsr $r3,$fs16
    464a:	fe 55       	xor33 $r1,$r2
    464c:	fe 5e       	and33 $r1,$r3
    464e:	c1 4e       	beqz38 $r1,46ea <lfs_dir_fetchmatch+0x45a>
    4650:	5a 00 02 04 	beqc $r0,#0x2,4658 <lfs_dir_fetchmatch+0x3c8>
    4654:	48 ff ff 64 	j 451c <lfs_dir_fetchmatch+0x28c>
    4658:	6a 06 80 01 	fmfsr $r0,$fs13
    465c:	6a 13 80 01 	fmfsr $r1,$fs7
    4660:	81 ac       	mov55 $r13,$r12
    4662:	fe 0e       	and33 $r0,$r1
    4664:	fe 56       	and33 $r1,$r2
    4666:	92 2a       	srli45 $r1,#0xa
    4668:	92 0a       	srli45 $r0,#0xa
    466a:	96 49       	zeh33 $r1,$r1
    466c:	96 01       	zeh33 $r0,$r0
    466e:	e2 01       	slt45 $r0,$r1
    4670:	6a 16 80 01 	fmfsr $r1,$fs13
    4674:	42 21 7c 08 	bset $r2,$r2,#0x1f
    4678:	40 11 3c 1a 	cmovz $r1,$r2,$r15
    467c:	6a 16 80 09 	fmtsr $r1,$fs13
    4680:	48 ff fe ac 	j 43d8 <lfs_dir_fetchmatch+0x148>
    4684:	6a 0a 80 01 	fmfsr $r0,$fs21
    4688:	6a 23 80 01 	fmfsr $r2,$fs7
    468c:	40 08 00 02 	and $r0,$r16,$r0
    4690:	f3 06       	lwi37.sp $r3,[+#0x18]
    4692:	92 14       	srli45 $r0,#0x14
    4694:	6a 16 80 01 	fmfsr $r1,$fs13
    4698:	96 02       	seb33 $r0,$r0
    469a:	fe 56       	and33 $r1,$r2
    469c:	88 60       	add45 $r3,$r0
    469e:	46 24 ff 00 	sethi $r2,#0x4ff00
    46a2:	96 d9       	zeh33 $r3,$r3
    46a4:	fe 8f       	or33 $r2,$r1
    46a6:	f3 86       	swi37.sp $r3,[+#0x18]
    46a8:	4c 28 00 62 	beq $r2,$r16,476c <lfs_dir_fetchmatch+0x4dc>
    46ac:	6a 26 80 01 	fmfsr $r2,$fs13
    46b0:	5a 2f ff 04 	bnec $r2,#-1,46b8 <lfs_dir_fetchmatch+0x428>
    46b4:	48 ff ff 2a 	j 4508 <lfs_dir_fetchmatch+0x278>
    46b8:	6a 23 80 01 	fmfsr $r2,$fs7
    46bc:	92 2a       	srli45 $r1,#0xa
    46be:	40 28 08 02 	and $r2,$r16,$r2
    46c2:	92 4a       	srli45 $r2,#0xa
    46c4:	96 91       	zeh33 $r2,$r2
    46c6:	96 49       	zeh33 $r1,$r1
    46c8:	e2 22       	slt45 $r1,$r2
    46ca:	4e f3 ff 1f 	bnez $r15,4508 <lfs_dir_fetchmatch+0x278>
    46ce:	6a 16 80 01 	fmfsr $r1,$fs13
    46d2:	40 00 28 08 	slli $r0,$r0,#0xa
    46d6:	88 20       	add45 $r1,$r0
    46d8:	6a 16 80 09 	fmtsr $r1,$fs13
    46dc:	48 ff ff 16 	j 4508 <lfs_dir_fetchmatch+0x278>
    46e0:	84 01       	movi55 $r0,#0x1
    46e2:	6a 09 80 09 	fmtsr $r0,$fs19
    46e6:	48 ff fe 63 	j 43ac <lfs_dir_fetchmatch+0x11c>
    46ea:	84 1f       	movi55 $r0,#-1
    46ec:	6a 06 80 09 	fmtsr $r0,$fs13
    46f0:	81 ac       	mov55 $r13,$r12
    46f2:	48 ff fe 73 	j 43d8 <lfs_dir_fetchmatch+0x148>
    46f6:	85 e0       	movi55 $r15,#0x0
    46f8:	5a 0f ac 04 	bnec $r0,#-84,4700 <lfs_dir_fetchmatch+0x470>
    46fc:	48 ff fe 1e 	j 4338 <lfs_dir_fetchmatch+0xa8>
    4700:	d5 8c       	j8 4618 <lfs_dir_fetchmatch+0x388>
    4702:	82 0c       	mov55 $r16,$r12
    4704:	48 ff fe f4 	j 44ec <lfs_dir_fetchmatch+0x25c>
    4708:	f1 08       	lwi37.sp $r1,[+#0x20]
    470a:	04 23 00 0b 	lwi $r2,[$r6+#0x2c]
    470e:	40 00 d8 08 	slli $r0,$r1,#0x16
    4712:	90 16       	srai45 $r0,#0x16
    4714:	8c 01       	addi45 $r0,#0x1
    4716:	e6 01       	slti45 $r0,#0x1
    4718:	40 f7 84 00 	add $r15,$r15,$r1
    471c:	6a 3a 80 01 	fmfsr $r3,$fs21
    4720:	54 07 83 ff 	andi $r0,$r15,#0x3ff
    4724:	8c 04       	addi45 $r0,#0x4
    4726:	41 00 8c 02 	and $r16,$r1,$r3
    472a:	fe bd       	xor33 $r2,$r7
    472c:	88 09       	add45 $r0,$r9
    472e:	6a 17 00 01 	fmfsr $r1,$fs14
    4732:	14 23 00 0b 	swi $r2,[$r6+#0x2c]
    4736:	41 08 2c 08 	slli $r16,$r16,#0xb
    473a:	14 05 00 03 	swi $r0,[$r10+#0xc]
    473e:	02 0f 80 0c 	lhi $r0,[$sp+#0x18]
    4742:	b4 61       	lwi450 $r3,[$r1]
    4744:	40 d6 40 03 	xor $r13,$r12,$r16
    4748:	a0 49       	lwi333 $r1,[$r1+#0x4]
    474a:	12 05 00 0a 	shi $r0,[$r10+#0x14]
    474e:	00 0f 80 1c 	lbi $r0,[$sp+#0x1c]
    4752:	6a 66 b4 c0 	fcpyss $fs6,$fs13,$fs13
    4756:	14 d5 00 04 	swi $r13,[$r10+#0x10]
    475a:	14 35 00 06 	swi $r3,[$r10+#0x18]
    475e:	14 15 00 07 	swi $r1,[$r10+#0x1c]
    4762:	10 05 00 17 	sbi $r0,[$r10+#0x17]
    4766:	84 ff       	movi55 $r7,#-1
    4768:	48 ff fe 38 	j 43d8 <lfs_dir_fetchmatch+0x148>
    476c:	6a 06 80 01 	fmfsr $r0,$fs13
    4770:	42 00 7c 08 	bset $r0,$r0,#0x1f
    4774:	6a 06 80 09 	fmtsr $r0,$fs13
    4778:	48 ff fe c8 	j 4508 <lfs_dir_fetchmatch+0x278>
    477c:	5a 07 ac 04 	beqc $r0,#-84,4784 <lfs_dir_fetchmatch+0x4f4>
    4780:	48 ff ff 4c 	j 4618 <lfs_dir_fetchmatch+0x388>
    4784:	10 85 00 16 	sbi $r8,[$r10+#0x16]
    4788:	04 05 00 03 	lwi $r0,[$r10+#0xc]
    478c:	48 ff ff 1e 	j 45c8 <lfs_dir_fetchmatch+0x338>
    4790:	5a 0f ac 04 	bnec $r0,#-84,4798 <lfs_dir_fetchmatch+0x508>
    4794:	48 ff ff 15 	j 45be <lfs_dir_fetchmatch+0x32e>
    4798:	48 ff ff 40 	j 4618 <lfs_dir_fetchmatch+0x388>
    479c:	6a 04 80 01 	fmfsr $r0,$fs9
    47a0:	44 10 05 00 	movi $r1,#0x500
    47a4:	40 56 80 02 	and $r5,$r13,$r0
    47a8:	92 b4       	srli45 $r5,#0x14
    47aa:	d1 11       	beqs38 $r1,47cc <lfs_dir_fetchmatch+0x53c>
    47ac:	04 05 00 03 	lwi $r0,[$r10+#0xc]
    47b0:	44 10 00 00 	movi $r1,#0x0
    47b4:	10 15 00 16 	sbi $r1,[$r10+#0x16]
    47b8:	48 ff ff 08 	j 45c8 <lfs_dir_fetchmatch+0x338>
    47bc:	80 03       	mov55 $r0,$r3
    47be:	48 ff ff 2d 	j 4618 <lfs_dir_fetchmatch+0x388>
    47c2:	92 00       	nop16
    47c4:	44 0f ff ac 	movi $r0,#-84
    47c8:	dd 9e       	ret5 $lp
    47ca:	92 00       	nop16
    47cc:	04 13 00 1a 	lwi $r1,[$r6+#0x68]
    47d0:	04 05 00 03 	lwi $r0,[$r10+#0xc]
    47d4:	a0 8e       	lwi333 $r2,[$r1+#0x18]
    47d6:	84 21       	movi55 $r1,#0x1
    47d8:	40 20 08 77 	divr $r2,$r3,$r0,$r2
    47dc:	c3 ec       	beqz38 $r3,47b4 <lfs_dir_fetchmatch+0x524>
    47de:	d5 e9       	j8 47b0 <lfs_dir_fetchmatch+0x520>
    47e0:	5a 0f ac 04 	bnec $r0,#-84,47e8 <lfs_dir_fetchmatch+0x558>
    47e4:	48 ff fe ed 	j 45be <lfs_dir_fetchmatch+0x32e>
    47e8:	48 ff ff 18 	j 4618 <lfs_dir_fetchmatch+0x388>
    47ec:	04 13 00 0f 	lwi $r1,[$r6+#0x3c]
    47f0:	6a 23 00 01 	fmfsr $r2,$fs6
    47f4:	40 00 d0 09 	srli $r0,$r1,#0x14
    47f8:	54 00 07 00 	andi $r0,$r0,#0x700
    47fc:	c0 0e       	beqz38 $r0,4818 <lfs_dir_fetchmatch+0x588>
    47fe:	04 53 00 10 	lwi $r5,[$r6+#0x40]
    4802:	b4 6a       	lwi450 $r3,[$r10]
    4804:	d3 28       	beqs38 $r3,4854 <lfs_dir_fetchmatch+0x5c4>
    4806:	04 03 00 11 	lwi $r0,[$r6+#0x44]
    480a:	04 45 00 01 	lwi $r4,[$r10+#0x4]
    480e:	4c 02 00 23 	beq $r0,$r4,4854 <lfs_dir_fetchmatch+0x5c4>
    4812:	d4 21       	beqs38 $r4,4854 <lfs_dir_fetchmatch+0x5c4>
    4814:	4c 30 00 20 	beq $r3,$r0,4854 <lfs_dir_fetchmatch+0x5c4>
    4818:	6a 08 80 01 	fmfsr $r0,$fs17
    481c:	c0 0c       	beqz38 $r0,4834 <lfs_dir_fetchmatch+0x5a4>
    481e:	40 11 30 08 	slli $r1,$r2,#0xc
    4822:	92 36       	srli45 $r1,#0x16
    4824:	02 35 00 0a 	lhi $r3,[$r10+#0x14]
    4828:	e2 61       	slt45 $r3,$r1
    482a:	40 11 bc 1b 	cmovn $r1,$r3,$r15
    482e:	6a 08 80 01 	fmfsr $r0,$fs17
    4832:	ac 40       	shi333 $r1,[$r0+#0x0]
    4834:	80 02       	mov55 $r0,$r2
    4836:	4e 24 fe f1 	bgez $r2,4618 <lfs_dir_fetchmatch+0x388>
    483a:	40 11 30 08 	slli $r1,$r2,#0xc
    483e:	92 36       	srli45 $r1,#0x16
    4840:	02 05 00 0a 	lhi $r0,[$r10+#0x14]
    4844:	96 49       	zeh33 $r1,$r1
    4846:	e2 20       	slt45 $r1,$r0
    4848:	84 7e       	movi55 $r3,#-2
    484a:	84 00       	movi55 $r0,#0x0
    484c:	40 01 bc 1b 	cmovn $r0,$r3,$r15
    4850:	48 ff fe e4 	j 4618 <lfs_dir_fetchmatch+0x388>
    4854:	46 00 00 ff 	sethi $r0,#0xff
    4858:	6a 23 00 01 	fmfsr $r2,$fs6
    485c:	50 00 0c 00 	addi $r0,$r0,#0xc00
    4860:	fe 46       	and33 $r1,$r0
    4862:	fe 86       	and33 $r2,$r0
    4864:	92 2a       	srli45 $r1,#0xa
    4866:	92 4a       	srli45 $r2,#0xa
    4868:	97 49       	zeh33 $r5,$r1
    486a:	96 91       	zeh33 $r2,$r2
    486c:	d2 0c       	beqs38 $r2,4884 <lfs_dir_fetchmatch+0x5f4>
    486e:	6a 03 00 01 	fmfsr $r0,$fs6
    4872:	5a 07 ff 19 	beqc $r0,#-1,48a4 <lfs_dir_fetchmatch+0x614>
    4876:	e2 a2       	slt45 $r5,$r2
    4878:	50 20 7c 00 	addi $r2,$r0,#-1024
    487c:	40 20 3c 1a 	cmovz $r2,$r0,$r15
    4880:	d5 cc       	j8 4818 <lfs_dir_fetchmatch+0x588>
    4882:	92 00       	nop16
    4884:	6a 13 00 01 	fmfsr $r1,$fs6
    4888:	42 10 fc 08 	bset $r1,$r1,#0x1f
    488c:	fe 0e       	and33 $r0,$r1
    488e:	6a 13 00 09 	fmtsr $r1,$fs6
    4892:	40 10 28 09 	srli $r1,$r0,#0xa
    4896:	92 00       	nop16
    4898:	6a 08 80 01 	fmfsr $r0,$fs17
    489c:	6a 23 00 01 	fmfsr $r2,$fs6
    48a0:	c8 c2       	bnez38 $r0,4824 <lfs_dir_fetchmatch+0x594>
    48a2:	d5 cf       	j8 4840 <lfs_dir_fetchmatch+0x5b0>
    48a4:	44 10 03 ff 	movi $r1,#0x3ff
    48a8:	d5 f8       	j8 4898 <lfs_dir_fetchmatch+0x608>
    48aa:	92 00       	nop16

000048ac <lfs_fs_parent>:
    48ac:	3a 6f b4 bc 	smw.adm $r6,[$sp],$r13,#0x2    ! {$r6~$r13, $lp}
    48b0:	ef e4       	addi10.sp #-28
    48b2:	81 20       	mov55 $r9,$r0
    48b4:	84 00       	movi55 $r0,#0x0
    48b6:	a8 16       	swi333 $r0,[$r2+#0x18]
    48b8:	46 c7 ff 00 	sethi $r12,#0x7ff00
    48bc:	84 01       	movi55 $r0,#0x1
    48be:	46 b2 00 00 	sethi $r11,#0x20000
    48c2:	80 e2       	mov55 $r7,$r2
    48c4:	81 41       	mov55 $r10,$r1
    48c6:	a8 17       	swi333 $r0,[$r2+#0x1c]
    48c8:	85 00       	movi55 $r8,#0x0
    48ca:	b1 83       	addri36.sp $r6,#0xc
    48cc:	50 d1 00 18 	addi $r13,$r2,#0x18
    48d0:	50 c6 03 ff 	addi $r12,$r12,#0x3ff
    48d4:	8d 68       	addi45 $r11,#0x8
    48d6:	a1 7f       	lwi333 $r5,[$r7+#0x1c]
    48d8:	80 09       	mov55 $r0,$r9
    48da:	80 27       	mov55 $r1,$r7
    48dc:	80 4d       	mov55 $r2,$r13
    48de:	80 6c       	mov55 $r3,$r12
    48e0:	80 8b       	mov55 $r4,$r11
    48e2:	5a 57 ff 20 	beqc $r5,#-1,4922 <lfs_fs_parent+0x76>
    48e6:	05 04 80 1a 	lwi $r16,[$r9+#0x68]
    48ea:	84 a0       	movi55 $r5,#0x0
    48ec:	05 08 00 08 	lwi $r16,[$r16+#0x20]
    48f0:	93 81       	srli45 $r16,#0x1
    48f2:	e3 10       	slt45 $r8,$r16
    48f4:	e8 1c       	beqzs8 492c <lfs_fs_parent+0x80>
    48f6:	b5 aa       	lwi450 $r17,[$r10]
    48f8:	05 05 00 01 	lwi $r16,[$r10+#0x4]
    48fc:	45 20 42 30 	movi $r18,#0x4230
    4900:	b7 df       	swi450 $r18,[$sp]
    4902:	f6 81       	swi37.sp $r6,[+#0x4]
    4904:	b7 26       	swi450 $r9,[$r6]
    4906:	15 13 00 01 	swi $r17,[$r6+#0x4]
    490a:	15 03 00 02 	swi $r16,[$r6+#0x8]
    490e:	49 ff fc c1 	jal 4290 <lfs_dir_fetchmatch>
    4912:	9d 42       	addi333 $r5,$r0,#0x2
    4914:	66 52 80 02 	bitci $r5,$r5,#0x2
    4918:	8d 01       	addi45 $r8,#0x1
    491a:	cd 05       	bnez38 $r5,4924 <lfs_fs_parent+0x78>
    491c:	a0 3e       	lwi333 $r0,[$r7+#0x18]
    491e:	5a 0f ff dc 	bnec $r0,#-1,48d6 <lfs_fs_parent+0x2a>
    4922:	84 1e       	movi55 $r0,#-2
    4924:	ec 1c       	addi10.sp #0x1c
    4926:	3a 6f b4 84 	lmw.bim $r6,[$sp],$r13,#0x2    ! {$r6~$r13, $lp}
    492a:	dd 9e       	ret5 $lp
    492c:	44 0f ff ac 	movi $r0,#-84
    4930:	ec 1c       	addi10.sp #0x1c
    4932:	3a 6f b4 84 	lmw.bim $r6,[$sp],$r13,#0x2    ! {$r6~$r13, $lp}
    4936:	dd 9e       	ret5 $lp

00004938 <lfs_fs_pred>:
    4938:	3a 6f ac bc 	smw.adm $r6,[$sp],$r11,#0x2    ! {$r6~$r11, $lp}
    493c:	ef f4       	addi10.sp #-12
    493e:	81 40       	mov55 $r10,$r0
    4940:	84 00       	movi55 $r0,#0x0
    4942:	a8 16       	swi333 $r0,[$r2+#0x18]
    4944:	84 01       	movi55 $r0,#0x1
    4946:	80 e2       	mov55 $r7,$r2
    4948:	81 21       	mov55 $r9,$r1
    494a:	a8 17       	swi333 $r0,[$r2+#0x1c]
    494c:	84 a0       	movi55 $r5,#0x0
    494e:	84 c0       	movi55 $r6,#0x0
    4950:	50 b1 00 18 	addi $r11,$r2,#0x18
    4954:	85 00       	movi55 $r8,#0x0
    4956:	92 00       	nop16
    4958:	05 13 80 07 	lwi $r17,[$r7+#0x1c]
    495c:	5b 17 ff 24 	beqc $r17,#-1,49a4 <dlm_remain+0x24>
    4960:	04 15 00 1a 	lwi $r1,[$r10+#0x68]
    4964:	80 0a       	mov55 $r0,$r10
    4966:	05 00 80 08 	lwi $r16,[$r1+#0x20]
    496a:	80 4b       	mov55 $r2,$r11
    496c:	93 81       	srli45 $r16,#0x1
    496e:	e2 d0       	slt45 $r6,$r16
    4970:	80 27       	mov55 $r1,$r7
    4972:	84 7f       	movi55 $r3,#-1
    4974:	84 9f       	movi55 $r4,#-1
    4976:	e8 23       	beqzs8 49bc <dlm_remain+0x3c>
    4978:	b5 c9       	lwi450 $r18,[$r9]
    497a:	8c c1       	addi45 $r6,#0x1
    497c:	4c 59 00 1a 	beq $r5,$r18,49b0 <dlm_remain+0x30>
    4980:	05 04 80 01 	lwi $r16,[$r9+#0x4]
    4984:	4d 08 80 16 	beq $r16,$r17,49b0 <dlm_remain+0x30>
    4988:	4c 58 00 14 	beq $r5,$r16,49b0 <dlm_remain+0x30>
    498c:	4d 28 80 12 	beq $r18,$r17,49b0 <dlm_remain+0x30>
    4990:	84 a0       	movi55 $r5,#0x0
    4992:	b7 1f       	swi450 $r8,[$sp]
    4994:	14 8f 80 01 	swi $r8,[$sp+#0x4]
    4998:	49 ff fc 7c 	jal 4290 <lfs_dir_fetchmatch>
    499c:	c8 06       	bnez38 $r0,49a8 <dlm_remain+0x28>
    499e:	a1 7e       	lwi333 $r5,[$r7+#0x18]
    49a0:	5a 5f ff dc 	bnec $r5,#-1,4958 <lfs_fs_pred+0x20>
    49a4:	44 0f ff fe 	movi $r0,#-2
    49a8:	ec 0c       	addi10.sp #0xc
    49aa:	3a 6f ac 84 	lmw.bim $r6,[$sp],$r11,#0x2    ! {$r6~$r11, $lp}
    49ae:	dd 9e       	ret5 $lp
    49b0:	84 00       	movi55 $r0,#0x0
    49b2:	ec 0c       	addi10.sp #0xc
    49b4:	3a 6f ac 84 	lmw.bim $r6,[$sp],$r11,#0x2    ! {$r6~$r11, $lp}
    49b8:	dd 9e       	ret5 $lp
    49ba:	92 00       	nop16
    49bc:	44 0f ff ac 	movi $r0,#-84
    49c0:	d5 f4       	j8 49a8 <dlm_remain+0x28>
    49c2:	92 00       	nop16

000049c4 <lfs_dir_traverse>:
    49c4:	3a 6f ba bc 	smw.adm $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    49c8:	ef a4       	addi10.sp #-92
    49ca:	36 3f 80 0c 	fsdi $fd3,[$sp+#0x30]
    49ce:	36 4f 80 0e 	fsdi $fd4,[$sp+#0x38]
    49d2:	36 5f 80 10 	fsdi $fd5,[$sp+#0x40]
    49d6:	36 6f 80 12 	fsdi $fd6,[$sp+#0x48]
    49da:	36 7f 80 14 	fsdi $fd7,[$sp+#0x50]
    49de:	46 90 00 ff 	sethi $r9,#0xff
    49e2:	04 af 80 22 	lwi $r10,[$sp+#0x88]
    49e6:	50 94 8c 00 	addi $r9,$r9,#0xc00
    49ea:	6a 06 00 09 	fmtsr $r0,$fs12
    49ee:	02 0f 80 48 	lhi $r0,[$sp+#0x90]
    49f2:	41 05 24 02 	and $r16,$r10,$r9
    49f6:	22 ef 80 4c 	lhsi $r14,[$sp+#0x98]
    49fa:	6a 05 00 09 	fmtsr $r0,$fs10
    49fe:	02 0f 80 4a 	lhi $r0,[$sp+#0x94]
    4a02:	6a 05 80 09 	fmtsr $r0,$fs11
    4a06:	40 08 28 09 	srli $r0,$r16,#0xa
    4a0a:	6a 03 00 09 	fmtsr $r0,$fs6
    4a0e:	40 07 28 08 	slli $r0,$r14,#0xa
    4a12:	6a 04 80 09 	fmtsr $r0,$fs9
    4a16:	46 06 00 ff 	sethi $r0,#0x600ff
    4a1a:	47 17 ff 00 	sethi $r17,#0x7ff00
    4a1e:	50 00 0c 00 	addi $r0,$r0,#0xc00
    4a22:	6b 13 80 09 	fmtsr $r17,$fs7
    4a26:	6a 04 00 09 	fmtsr $r0,$fs8
    4a2a:	30 ff 80 23 	flsi $fs15,[$sp+#0x8c]
    4a2e:	30 ef 80 27 	flsi $fs14,[$sp+#0x9c]
    4a32:	30 df 80 28 	flsi $fs13,[$sp+#0xa0]
    4a36:	81 a1       	mov55 $r13,$r1
    4a38:	81 02       	mov55 $r8,$r2
    4a3a:	81 83       	mov55 $r12,$r3
    4a3c:	83 84       	mov55 $fp,$r4
    4a3e:	80 e5       	mov55 $r7,$r5
    4a40:	40 a5 44 02 	and $r10,$r10,$r17
    4a44:	41 06 58 08 	slli $r16,$r12,#0x16
    4a48:	91 96       	srai45 $r16,#0x16
    4a4a:	8d 81       	addi45 $r16,#0x1
    4a4c:	e7 81       	slti45 $r16,#0x1
    4a4e:	40 f7 b0 00 	add $r15,$r15,$r12
    4a52:	50 64 00 04 	addi $r6,$r8,#0x4
    4a56:	55 07 83 ff 	andi $r16,$r15,#0x3ff
    4a5a:	04 06 80 03 	lwi $r0,[$r13+#0xc]
    4a5e:	88 d0       	add45 $r6,$r16
    4a60:	e2 c0       	slt45 $r6,$r0
    4a62:	e9 57       	bnezs8 4b10 <lfs_dir_traverse+0x14c>
    4a64:	4e 77 00 d6 	blez $r7,4c10 <lfs_dir_traverse+0x24c>
    4a68:	b5 9c       	lwi450 $r16,[$fp]
    4a6a:	be 01       	lwi37 $r6,[$fp+#0x4]
    4a6c:	15 0f 80 09 	swi $r16,[$sp+#0x24]
    4a70:	51 ce 00 08 	addi $fp,$fp,#0x8
    4a74:	8e e1       	subi45 $r7,#0x1
    4a76:	92 00       	nop16
    4a78:	6a 07 80 01 	fmfsr $r0,$fs15
    4a7c:	40 08 00 03 	xor $r0,$r16,$r0
    4a80:	40 05 00 02 	and $r0,$r10,$r0
    4a84:	c8 e0       	bnez38 $r0,4a44 <lfs_dir_traverse+0x80>
    4a86:	6a 13 00 01 	fmfsr $r1,$fs6
    4a8a:	c9 67       	bnez38 $r1,4b58 <lfs_dir_traverse+0x194>
    4a8c:	6a 03 80 01 	fmfsr $r0,$fs7
    4a90:	40 08 00 02 	and $r0,$r16,$r0
    4a94:	92 14       	srli45 $r0,#0x14
    4a96:	c0 d7       	beqz38 $r0,4a44 <lfs_dir_traverse+0x80>
    4a98:	5a 09 01 04 	bnec $r0,#0x101,4aa0 <lfs_dir_traverse+0xdc>
    4a9c:	48 00 00 96 	j 4bc8 <lfs_dir_traverse+0x204>
    4aa0:	5a 01 02 04 	beqc $r0,#0x102,4aa8 <lfs_dir_traverse+0xe4>
    4aa4:	48 00 00 84 	j 4bac <lfs_dir_traverse+0x1e8>
    4aa8:	54 08 03 ff 	andi $r0,$r16,#0x3ff
    4aac:	c0 cc       	beqz38 $r0,4a44 <lfs_dir_traverse+0x80>
    4aae:	85 60       	movi55 $r11,#0x0
    4ab0:	d5 0a       	j8 4ac4 <lfs_dir_traverse+0x100>
    4ab2:	92 00       	nop16
    4ab4:	05 0f 80 09 	lwi $r16,[$sp+#0x24]
    4ab8:	8c cc       	addi45 $r6,#0xc
    4aba:	54 08 03 ff 	andi $r0,$r16,#0x3ff
    4abe:	e3 60       	slt45 $r11,$r0
    4ac0:	e8 c2       	beqzs8 4a44 <lfs_dir_traverse+0x80>
    4ac2:	92 00       	nop16
    4ac4:	41 08 24 02 	and $r16,$r16,$r9
    4ac8:	a7 70       	lbi333 $r5,[$r6+#0x0]
    4aca:	93 8a       	srli45 $r16,#0xa
    4acc:	a0 72       	lwi333 $r1,[$r6+#0x8]
    4ace:	89 8e       	add45 $r16,$r14
    4ad0:	41 08 28 08 	slli $r16,$r16,#0xa
    4ad4:	50 52 83 00 	addi $r5,$r5,#0x300
    4ad8:	40 18 04 04 	or $r1,$r16,$r1
    4adc:	40 52 d0 08 	slli $r5,$r5,#0x14
    4ae0:	6a 06 80 01 	fmfsr $r0,$fs13
    4ae4:	6a 37 00 01 	fmfsr $r3,$fs14
    4ae8:	a0 b1       	lwi333 $r2,[$r6+#0x4]
    4aea:	fe 6f       	or33 $r1,$r5
    4aec:	8d 61       	addi45 $r11,#0x1
    4aee:	dd 23       	jral5 $r3
    4af0:	c0 e2       	beqz38 $r0,4ab4 <lfs_dir_traverse+0xf0>
    4af2:	92 00       	nop16
    4af4:	ec 30       	addi10.sp #0x30
    4af6:	34 3f 90 02 	fldi.bi $fd3,[$sp],#0x8
    4afa:	34 4f 90 02 	fldi.bi $fd4,[$sp],#0x8
    4afe:	34 5f 90 02 	fldi.bi $fd5,[$sp],#0x8
    4b02:	34 6f 90 02 	fldi.bi $fd6,[$sp],#0x8
    4b06:	34 7f 90 03 	fldi.bi $fd7,[$sp],#0xc
    4b0a:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    4b0e:	dd 9e       	ret5 $lp
    4b10:	b0 09       	addri36.sp $r0,#0x24
    4b12:	b6 1f       	swi450 $r0,[$sp]
    4b14:	84 04       	movi55 $r0,#0x4
    4b16:	f0 81       	swi37.sp $r0,[+#0x4]
    4b18:	6a 06 00 01 	fmfsr $r0,$fs12
    4b1c:	6a 26 00 01 	fmfsr $r2,$fs12
    4b20:	50 00 00 68 	addi $r0,$r0,#0x68
    4b24:	84 20       	movi55 $r1,#0x0
    4b26:	84 64       	movi55 $r3,#0x4
    4b28:	b4 8d       	lwi450 $r4,[$r13]
    4b2a:	80 a6       	mov55 $r5,$r6
    4b2c:	49 ff fa be 	jal 40a8 <lfs_bd_read.isra.13>
    4b30:	c8 e2       	bnez38 $r0,4af4 <lfs_dir_traverse+0x130>
    4b32:	f0 09       	lwi37.sp $r0,[+#0x24]
    4b34:	b4 2d       	lwi450 $r1,[$r13]
    4b36:	40 00 00 14 	wsbh $r0,$r0
    4b3a:	40 00 40 0b 	rotri $r0,$r0,#0x10
    4b3e:	40 00 30 03 	xor $r0,$r0,$r12
    4b42:	42 c0 7c 08 	bset $r12,$r0,#0x1f
    4b46:	9c 34       	addi333 $r0,$r6,#0x4
    4b48:	81 06       	mov55 $r8,$r6
    4b4a:	14 cf 80 09 	swi $r12,[$sp+#0x24]
    4b4e:	f1 8a       	swi37.sp $r1,[+#0x28]
    4b50:	f0 8b       	swi37.sp $r0,[+#0x2c]
    4b52:	82 0c       	mov55 $r16,$r12
    4b54:	b1 8a       	addri36.sp $r6,#0x28
    4b56:	d5 91       	j8 4a78 <lfs_dir_traverse+0xb4>
    4b58:	b6 1f       	swi450 $r0,[$sp]
    4b5a:	f0 81       	swi37.sp $r0,[+#0x4]
    4b5c:	f0 82       	swi37.sp $r0,[+#0x8]
    4b5e:	f0 83       	swi37.sp $r0,[+#0xc]
    4b60:	f0 84       	swi37.sp $r0,[+#0x10]
    4b62:	44 00 35 d0 	movi $r0,#0x35d0
    4b66:	f0 85       	swi37.sp $r0,[+#0x14]
    4b68:	b0 09       	addri36.sp $r0,#0x24
    4b6a:	f0 86       	swi37.sp $r0,[+#0x18]
    4b6c:	6a 06 00 01 	fmfsr $r0,$fs12
    4b70:	80 2d       	mov55 $r1,$r13
    4b72:	80 48       	mov55 $r2,$r8
    4b74:	80 6c       	mov55 $r3,$r12
    4b76:	80 9c       	mov55 $r4,$fp
    4b78:	50 53 80 00 	addi $r5,$r7,#0x0
    4b7c:	49 ff ff 24 	jal 49c4 <lfs_dir_traverse>
    4b80:	4e 05 ff ba 	bltz $r0,4af4 <lfs_dir_traverse+0x130>
    4b84:	4e 03 ff 60 	bnez $r0,4a44 <lfs_dir_traverse+0x80>
    4b88:	05 0f 80 09 	lwi $r16,[$sp+#0x24]
    4b8c:	6a 15 00 01 	fmfsr $r1,$fs10
    4b90:	40 08 24 02 	and $r0,$r16,$r9
    4b94:	92 0a       	srli45 $r0,#0xa
    4b96:	96 01       	zeh33 $r0,$r0
    4b98:	e2 01       	slt45 $r0,$r1
    4b9a:	4e f3 ff 55 	bnez $r15,4a44 <lfs_dir_traverse+0x80>
    4b9e:	6a 15 80 01 	fmfsr $r1,$fs11
    4ba2:	e2 01       	slt45 $r0,$r1
    4ba4:	4e f2 ff 50 	beqz $r15,4a44 <lfs_dir_traverse+0x80>
    4ba8:	48 ff ff 72 	j 4a8c <lfs_dir_traverse+0xc8>
    4bac:	6a 14 80 01 	fmfsr $r1,$fs9
    4bb0:	6a 06 80 01 	fmfsr $r0,$fs13
    4bb4:	6a 37 00 01 	fmfsr $r3,$fs14
    4bb8:	88 30       	add45 $r1,$r16
    4bba:	80 46       	mov55 $r2,$r6
    4bbc:	4b e0 0c 01 	jral $lp,$r3
    4bc0:	4e 02 ff 42 	beqz $r0,4a44 <lfs_dir_traverse+0x80>
    4bc4:	d5 98       	j8 4af4 <lfs_dir_traverse+0x130>
    4bc6:	92 00       	nop16
    4bc8:	40 08 24 02 	and $r0,$r16,$r9
    4bcc:	92 0a       	srli45 $r0,#0xa
    4bce:	55 08 03 ff 	andi $r16,$r16,#0x3ff
    4bd2:	8a 10       	sub45 $r0,$r16
    4bd4:	88 0e       	add45 $r0,$r14
    4bd6:	96 03       	seh33 $r0,$r0
    4bd8:	50 18 00 01 	addi $r1,$r16,#0x1
    4bdc:	46 22 00 00 	sethi $r2,#0x20000
    4be0:	f0 84       	swi37.sp $r0,[+#0x10]
    4be2:	6a 06 00 01 	fmfsr $r0,$fs12
    4be6:	f2 81       	swi37.sp $r2,[+#0x4]
    4be8:	f1 83       	swi37.sp $r1,[+#0xc]
    4bea:	32 8f 80 00 	fssi $fs8,[$sp+#0x0]
    4bee:	15 0f 80 02 	swi $r16,[$sp+#0x8]
    4bf2:	32 ef 80 05 	fssi $fs14,[$sp+#0x14]
    4bf6:	32 df 80 06 	fssi $fs13,[$sp+#0x18]
    4bfa:	80 26       	mov55 $r1,$r6
    4bfc:	84 40       	movi55 $r2,#0x0
    4bfe:	84 7f       	movi55 $r3,#-1
    4c00:	84 80       	movi55 $r4,#0x0
    4c02:	84 a0       	movi55 $r5,#0x0
    4c04:	49 ff fe e0 	jal 49c4 <lfs_dir_traverse>
    4c08:	4e 02 ff 1e 	beqz $r0,4a44 <lfs_dir_traverse+0x80>
    4c0c:	48 ff ff 74 	j 4af4 <lfs_dir_traverse+0x130>
    4c10:	84 00       	movi55 $r0,#0x0
    4c12:	48 ff ff 71 	j 4af4 <lfs_dir_traverse+0x130>
    4c16:	92 00       	nop16

00004c18 <lfs_fs_preporphans.isra.14>:
    4c18:	b4 40       	lwi450 $r2,[$r0]
    4c1a:	54 31 03 ff 	andi $r3,$r2,#0x3ff
    4c1e:	cb 03       	bnez38 $r3,4c24 <lfs_fs_preporphans.isra.14+0xc>
    4c20:	4e 15 00 0e 	bltz $r1,4c3c <lfs_fs_preporphans.isra.14+0x24>
    4c24:	88 41       	add45 $r2,$r1
    4c26:	54 31 03 ff 	andi $r3,$r2,#0x3ff
    4c2a:	84 20       	movi55 $r1,#0x0
    4c2c:	e2 23       	slt45 $r1,$r3
    4c2e:	40 17 fc 08 	slli $r1,$r15,#0x1f
    4c32:	42 21 7c 09 	bclr $r2,$r2,#0x1f
    4c36:	fe 8f       	or33 $r2,$r1
    4c38:	b6 40       	swi450 $r2,[$r0]
    4c3a:	dd 9e       	ret5 $lp
    4c3c:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    4c40:	44 00 36 d4 	movi $r0,#0x36d4
    4c44:	44 10 10 03 	movi $r1,#0x1003
    4c48:	44 20 7c b0 	movi $r2,#0x7cb0
    4c4c:	44 30 39 70 	movi $r3,#0x3970
    4c50:	49 00 27 e6 	jal 9c1c <__assert_func>
    4c54:	92 00       	nop16
    4c56:	92 00       	nop16

00004c58 <lfs_bd_erase.isra.16>:
    4c58:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    4c5c:	04 20 00 08 	lwi $r2,[$r0+#0x20]
    4c60:	e2 22       	slt45 $r1,$r2
    4c62:	e8 09       	beqzs8 4c74 <lfs_bd_erase.isra.16+0x1c>
    4c64:	a0 83       	lwi333 $r2,[$r0+#0xc]
    4c66:	dd 22       	jral5 $r2
    4c68:	4e 06 00 12 	bgtz $r0,4c8c <lfs_bd_erase.isra.16+0x34>
    4c6c:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    4c70:	dd 9e       	ret5 $lp
    4c72:	92 00       	nop16
    4c74:	44 00 36 d4 	movi $r0,#0x36d4
    4c78:	44 10 00 e9 	movi $r1,#0xe9
    4c7c:	44 20 7c 7c 	movi $r2,#0x7c7c
    4c80:	44 30 39 ac 	movi $r3,#0x39ac
    4c84:	49 00 27 cc 	jal 9c1c <__assert_func>
    4c88:	92 00       	nop16
    4c8a:	92 00       	nop16
    4c8c:	44 00 36 d4 	movi $r0,#0x36d4
    4c90:	44 10 00 eb 	movi $r1,#0xeb
    4c94:	44 20 7c 7c 	movi $r2,#0x7c7c
    4c98:	44 30 39 2c 	movi $r3,#0x392c
    4c9c:	49 00 27 c0 	jal 9c1c <__assert_func>
    4ca0:	92 00       	nop16
    4ca2:	92 00       	nop16

00004ca4 <lfs_ctz_index.isra.23>:
    4ca4:	3a 6f a8 bc 	smw.adm $r6,[$sp],$r10,#0x2    ! {$r6~$r10, $lp}
    4ca8:	04 80 00 07 	lwi $r8,[$r0+#0x1c]
    4cac:	b4 e1       	lwi450 $r7,[$r1]
    4cae:	8f 08       	subi45 $r8,#0x8
    4cb0:	40 03 a0 17 	divr $r0,$r0,$r7,$r8
    4cb4:	c0 17       	beqz38 $r0,4ce2 <lfs_ctz_index.isra.23+0x3e>
    4cb6:	8e 01       	subi45 $r0,#0x1
    4cb8:	81 21       	mov55 $r9,$r1
    4cba:	49 00 20 89 	jal 8dcc <__popcountsi2>
    4cbe:	8c 02       	addi45 $r0,#0x2
    4cc0:	95 82       	slli333 $r6,$r0,#0x2
    4cc2:	9b be       	sub333 $r6,$r7,$r6
    4cc4:	40 63 20 d7 	divr $r6,$r6,$r6,$r8
    4cc8:	50 03 00 00 	addi $r0,$r6,#0x0
    4ccc:	49 00 20 80 	jal 8dcc <__popcountsi2>
    4cd0:	42 73 20 75 	msubr32 $r7,$r6,$r8
    4cd4:	94 02       	slli333 $r0,$r0,#0x2
    4cd6:	8a e0       	sub45 $r7,$r0
    4cd8:	b6 e9       	swi450 $r7,[$r9]
    4cda:	80 06       	mov55 $r0,$r6
    4cdc:	3a 6f a8 84 	lmw.bim $r6,[$sp],$r10,#0x2    ! {$r6~$r10, $lp}
    4ce0:	dd 9e       	ret5 $lp
    4ce2:	84 00       	movi55 $r0,#0x0
    4ce4:	3a 6f a8 84 	lmw.bim $r6,[$sp],$r10,#0x2    ! {$r6~$r10, $lp}
    4ce8:	dd 9e       	ret5 $lp
    4cea:	92 00       	nop16

00004cec <lfs_ctz_traverse.part.24>:
    4cec:	3a 6f b8 bc 	smw.adm $r6,[$sp],$r14,#0x2    ! {$r6~$r14, $lp}
    4cf0:	ef e8       	addi10.sp #-24
    4cf2:	82 00       	mov55 $r16,$r0
    4cf4:	8e 81       	subi45 $r4,#0x1
    4cf6:	81 c1       	mov55 $r14,$r1
    4cf8:	04 00 00 1a 	lwi $r0,[$r0+#0x68]
    4cfc:	b0 43       	addri36.sp $r1,#0xc
    4cfe:	81 a2       	mov55 $r13,$r2
    4d00:	81 03       	mov55 $r8,$r3
    4d02:	81 25       	mov55 $r9,$r5
    4d04:	f6 10       	lwi37.sp $r6,[+#0x40]
    4d06:	f4 83       	swi37.sp $r4,[+#0xc]
    4d08:	50 c8 00 68 	addi $r12,$r16,#0x68
    4d0c:	49 ff ff cc 	jal 4ca4 <lfs_ctz_index.isra.23>
    4d10:	81 60       	mov55 $r11,$r0
    4d12:	b1 c4       	addri36.sp $r7,#0x10
    4d14:	80 06       	mov55 $r0,$r6
    4d16:	80 28       	mov55 $r1,$r8
    4d18:	dd 29       	jral5 $r9
    4d1a:	c8 23       	bnez38 $r0,4d60 <lfs_ctz_traverse.part.24+0x74>
    4d1c:	4e b2 00 21 	beqz $r11,4d5e <lfs_ctz_traverse.part.24+0x72>
    4d20:	54 a5 80 01 	andi $r10,$r11,#0x1
    4d24:	52 a5 00 02 	subri $r10,$r10,#0x2
    4d28:	40 35 08 08 	slli $r3,$r10,#0x2
    4d2c:	b6 ff       	swi450 $r7,[$sp]
    4d2e:	f3 81       	swi37.sp $r3,[+#0x4]
    4d30:	80 0c       	mov55 $r0,$r12
    4d32:	80 2e       	mov55 $r1,$r14
    4d34:	80 4d       	mov55 $r2,$r13
    4d36:	80 88       	mov55 $r4,$r8
    4d38:	84 a0       	movi55 $r5,#0x0
    4d3a:	49 ff f9 b7 	jal 40a8 <lfs_bd_read.isra.13>
    4d3e:	c8 11       	bnez38 $r0,4d60 <lfs_ctz_traverse.part.24+0x74>
    4d40:	50 85 7f ff 	addi $r8,$r10,#-1
    4d44:	84 60       	movi55 $r3,#0x0
    4d46:	d5 05       	j8 4d50 <lfs_ctz_traverse.part.24+0x64>
    4d48:	b4 27       	lwi450 $r1,[$r7]
    4d4a:	dd 29       	jral5 $r9
    4d4c:	84 61       	movi55 $r3,#0x1
    4d4e:	c8 09       	bnez38 $r0,4d60 <lfs_ctz_traverse.part.24+0x74>
    4d50:	e0 68       	slts45 $r3,$r8
    4d52:	80 06       	mov55 $r0,$r6
    4d54:	e9 fa       	bnezs8 4d48 <lfs_ctz_traverse.part.24+0x5c>
    4d56:	38 83 a2 02 	lw $r8,[$r7+($r8<<#0x2)]
    4d5a:	8b 6a       	sub45 $r11,$r10
    4d5c:	d5 dc       	j8 4d14 <lfs_ctz_traverse.part.24+0x28>
    4d5e:	84 00       	movi55 $r0,#0x0
    4d60:	ec 18       	addi10.sp #0x18
    4d62:	3a 6f b8 84 	lmw.bim $r6,[$sp],$r14,#0x2    ! {$r6~$r14, $lp}
    4d66:	dd 9e       	ret5 $lp

00004d68 <lfs_ctz_find.constprop.32>:
    4d68:	3a 6f b8 bc 	smw.adm $r6,[$sp],$r14,#0x2    ! {$r6~$r14, $lp}
    4d6c:	ef e8       	addi10.sp #-24
    4d6e:	f2 83       	swi37.sp $r2,[+#0xc]
    4d70:	f4 82       	swi37.sp $r4,[+#0x8]
    4d72:	cb 0b       	bnez38 $r3,4d88 <lfs_ctz_find.constprop.32+0x20>
    4d74:	f1 10       	lwi37.sp $r1,[+#0x40]
    4d76:	84 1f       	movi55 $r0,#-1
    4d78:	b6 05       	swi450 $r0,[$r5]
    4d7a:	84 00       	movi55 $r0,#0x0
    4d7c:	b6 61       	swi450 $r3,[$r1]
    4d7e:	92 00       	nop16
    4d80:	ec 18       	addi10.sp #0x18
    4d82:	3a 6f b8 84 	lmw.bim $r6,[$sp],$r14,#0x2    ! {$r6~$r14, $lp}
    4d86:	dd 9e       	ret5 $lp
    4d88:	81 20       	mov55 $r9,$r0
    4d8a:	8e 61       	subi45 $r3,#0x1
    4d8c:	81 41       	mov55 $r10,$r1
    4d8e:	04 00 00 1a 	lwi $r0,[$r0+#0x68]
    4d92:	b0 45       	addri36.sp $r1,#0x14
    4d94:	81 c5       	mov55 $r14,$r5
    4d96:	f3 85       	swi37.sp $r3,[+#0x14]
    4d98:	49 ff ff 86 	jal 4ca4 <lfs_ctz_index.isra.23>
    4d9c:	80 e0       	mov55 $r7,$r0
    4d9e:	b0 42       	addri36.sp $r1,#0x8
    4da0:	04 04 80 1a 	lwi $r0,[$r9+#0x68]
    4da4:	49 ff ff 80 	jal 4ca4 <lfs_ctz_index.isra.23>
    4da8:	81 00       	mov55 $r8,$r0
    4daa:	40 00 1c 06 	slt $r0,$r0,$r7
    4dae:	50 94 80 68 	addi $r9,$r9,#0x68
    4db2:	50 df 80 0c 	addi $r13,$sp,#0xc
    4db6:	85 84       	movi55 $r12,#0x4
    4db8:	85 61       	movi55 $r11,#0x1
    4dba:	c0 24       	beqz38 $r0,4e02 <lfs_ctz_find.constprop.32+0x9a>
    4dbc:	fe fa       	neg33 $r3,$r7
    4dbe:	fe fe       	and33 $r3,$r7
    4dc0:	40 63 a0 01 	sub $r6,$r7,$r8
    4dc4:	42 63 00 07 	clz $r6,$r6
    4dc8:	42 31 80 07 	clz $r3,$r3
    4dcc:	52 31 80 1f 	subri $r3,$r3,#0x1f
    4dd0:	52 63 00 1f 	subri $r6,$r6,#0x1f
    4dd4:	e2 66       	slt45 $r3,$r6
    4dd6:	40 61 bc 1b 	cmovn $r6,$r3,$r15
    4dda:	14 df 80 00 	swi $r13,[$sp+#0x0]
    4dde:	84 64       	movi55 $r3,#0x4
    4de0:	14 cf 80 01 	swi $r12,[$sp+#0x4]
    4de4:	80 09       	mov55 $r0,$r9
    4de6:	84 20       	movi55 $r1,#0x0
    4de8:	80 4a       	mov55 $r2,$r10
    4dea:	f4 03       	lwi37.sp $r4,[+#0xc]
    4dec:	40 53 08 08 	slli $r5,$r6,#0x2
    4df0:	49 ff f9 5c 	jal 40a8 <lfs_bd_read.isra.13>
    4df4:	40 35 98 0c 	sll $r3,$r11,$r6
    4df8:	8a e3       	sub45 $r7,$r3
    4dfa:	40 34 1c 06 	slt $r3,$r8,$r7
    4dfe:	c8 c1       	bnez38 $r0,4d80 <lfs_ctz_find.constprop.32+0x18>
    4e00:	cb de       	bnez38 $r3,4dbc <lfs_ctz_find.constprop.32+0x54>
    4e02:	f2 10       	lwi37.sp $r2,[+#0x40]
    4e04:	f0 03       	lwi37.sp $r0,[+#0xc]
    4e06:	f1 02       	lwi37.sp $r1,[+#0x8]
    4e08:	b6 0e       	swi450 $r0,[$r14]
    4e0a:	84 00       	movi55 $r0,#0x0
    4e0c:	b6 22       	swi450 $r1,[$r2]
    4e0e:	ec 18       	addi10.sp #0x18
    4e10:	3a 6f b8 84 	lmw.bim $r6,[$sp],$r14,#0x2    ! {$r6~$r14, $lp}
    4e14:	dd 9e       	ret5 $lp
    4e16:	92 00       	nop16

00004e18 <lfs_bd_cmp.constprop.35>:
    4e18:	3a 6f b8 bc 	smw.adm $r6,[$sp],$r14,#0x2    ! {$r6~$r14, $lp}
    4e1c:	ef f0       	addi10.sp #-16
    4e1e:	04 af 80 0e 	lwi $r10,[$sp+#0x38]
    4e22:	4e a2 00 2b 	beqz $r10,4e78 <lfs_bd_cmp.constprop.35+0x60>
    4e26:	81 04       	mov55 $r8,$r4
    4e28:	81 83       	mov55 $r12,$r3
    4e2a:	80 e2       	mov55 $r7,$r2
    4e2c:	81 61       	mov55 $r11,$r1
    4e2e:	80 c5       	mov55 $r6,$r5
    4e30:	50 90 00 68 	addi $r9,$r0,#0x68
    4e34:	89 45       	add45 $r10,$r5
    4e36:	8b 05       	sub45 $r8,$r5
    4e38:	50 ef 80 0f 	addi $r14,$sp,#0xf
    4e3c:	85 a1       	movi55 $r13,#0x1
    4e3e:	d5 0b       	j8 4e54 <lfs_bd_cmp.constprop.35+0x3c>
    4e40:	08 13 00 01 	lbi.bi $r1,[$r6],#0x1
    4e44:	00 5f 80 0f 	lbi $r5,[$sp+#0xf]
    4e48:	8e e1       	subi45 $r7,#0x1
    4e4a:	4c 12 c0 1d 	bne $r1,$r5,4e84 <lfs_bd_cmp.constprop.35+0x6c>
    4e4e:	4c 65 00 15 	beq $r6,$r10,4e78 <lfs_bd_cmp.constprop.35+0x60>
    4e52:	92 00       	nop16
    4e54:	40 54 18 00 	add $r5,$r8,$r6
    4e58:	80 67       	mov55 $r3,$r7
    4e5a:	14 ef 80 00 	swi $r14,[$sp+#0x0]
    4e5e:	14 df 80 01 	swi $r13,[$sp+#0x4]
    4e62:	80 09       	mov55 $r0,$r9
    4e64:	84 20       	movi55 $r1,#0x0
    4e66:	80 4b       	mov55 $r2,$r11
    4e68:	80 8c       	mov55 $r4,$r12
    4e6a:	49 ff f9 1f 	jal 40a8 <lfs_bd_read.isra.13>
    4e6e:	c0 e9       	beqz38 $r0,4e40 <lfs_bd_cmp.constprop.35+0x28>
    4e70:	ec 10       	addi10.sp #0x10
    4e72:	3a 6f b8 84 	lmw.bim $r6,[$sp],$r14,#0x2    ! {$r6~$r14, $lp}
    4e76:	dd 9e       	ret5 $lp
    4e78:	84 00       	movi55 $r0,#0x0
    4e7a:	ec 10       	addi10.sp #0x10
    4e7c:	3a 6f b8 84 	lmw.bim $r6,[$sp],$r14,#0x2    ! {$r6~$r14, $lp}
    4e80:	dd 9e       	ret5 $lp
    4e82:	92 00       	nop16
    4e84:	e2 a1       	slt45 $r5,$r1
    4e86:	84 02       	movi55 $r0,#0x2
    4e88:	84 21       	movi55 $r1,#0x1
    4e8a:	40 00 bc 1b 	cmovn $r0,$r1,$r15
    4e8e:	ec 10       	addi10.sp #0x10
    4e90:	3a 6f b8 84 	lmw.bim $r6,[$sp],$r14,#0x2    ! {$r6~$r14, $lp}
    4e94:	dd 9e       	ret5 $lp
    4e96:	92 00       	nop16

00004e98 <lfs_bd_flush>:
    4e98:	3a 6f a8 bc 	smw.adm $r6,[$sp],$r10,#0x2    ! {$r6~$r10, $lp}
    4e9c:	ef f8       	addi10.sp #-8
    4e9e:	80 e1       	mov55 $r7,$r1
    4ea0:	b4 21       	lwi450 $r1,[$r1]
    4ea2:	9d 0a       	addi333 $r4,$r1,#0x2
    4ea4:	e6 82       	slti45 $r4,#0x2
    4ea6:	e9 3b       	bnezs8 4f1c <lfs_bd_flush+0x84>
    4ea8:	81 00       	mov55 $r8,$r0
    4eaa:	04 00 00 1a 	lwi $r0,[$r0+#0x68]
    4eae:	81 23       	mov55 $r9,$r3
    4eb0:	04 40 00 08 	lwi $r4,[$r0+#0x20]
    4eb4:	81 42       	mov55 $r10,$r2
    4eb6:	e2 24       	slt45 $r1,$r4
    4eb8:	e8 48       	beqzs8 4f48 <lfs_bd_flush+0xb0>
    4eba:	a1 86       	lwi333 $r6,[$r0+#0x18]
    4ebc:	a1 7a       	lwi333 $r5,[$r7+#0x8]
    4ebe:	05 00 00 02 	lwi $r16,[$r0+#0x8]
    4ec2:	99 35       	add333 $r4,$r6,$r5
    4ec4:	8e 81       	subi45 $r4,#0x1
    4ec6:	40 52 18 d7 	divr $r5,$r6,$r4,$r6
    4eca:	9b a6       	sub333 $r6,$r4,$r6
    4ecc:	a0 b9       	lwi333 $r2,[$r7+#0x4]
    4ece:	a0 fb       	lwi333 $r3,[$r7+#0xc]
    4ed0:	80 86       	mov55 $r4,$r6
    4ed2:	dd 30       	jral5 $r16
    4ed4:	4e 06 00 2e 	bgtz $r0,4f30 <lfs_bd_flush+0x98>
    4ed8:	c8 1e       	bnez38 $r0,4f14 <lfs_bd_flush+0x7c>
    4eda:	4e 92 00 11 	beqz $r9,4efc <lfs_bd_flush+0x64>
    4ede:	84 1f       	movi55 $r0,#-1
    4ee0:	b6 0a       	swi450 $r0,[$r10]
    4ee2:	b6 df       	swi450 $r6,[$sp]
    4ee4:	80 08       	mov55 $r0,$r8
    4ee6:	80 2a       	mov55 $r1,$r10
    4ee8:	80 46       	mov55 $r2,$r6
    4eea:	b4 67       	lwi450 $r3,[$r7]
    4eec:	a1 39       	lwi333 $r4,[$r7+#0x4]
    4eee:	a1 7b       	lwi333 $r5,[$r7+#0xc]
    4ef0:	49 ff ff 94 	jal 4e18 <lfs_bd_cmp.constprop.35>
    4ef4:	4e 05 00 10 	bltz $r0,4f14 <lfs_bd_flush+0x7c>
    4ef8:	c8 18       	bnez38 $r0,4f28 <lfs_bd_flush+0x90>
    4efa:	92 00       	nop16
    4efc:	04 24 00 1a 	lwi $r2,[$r8+#0x68]
    4f00:	a0 3b       	lwi333 $r0,[$r7+#0xc]
    4f02:	44 10 00 ff 	movi $r1,#0xff
    4f06:	04 21 00 0a 	lwi $r2,[$r2+#0x28]
    4f0a:	49 00 28 59 	jal 9fbc <memset>
    4f0e:	84 1f       	movi55 $r0,#-1
    4f10:	b6 07       	swi450 $r0,[$r7]
    4f12:	84 00       	movi55 $r0,#0x0
    4f14:	ec 08       	addi10.sp #0x8
    4f16:	3a 6f a8 84 	lmw.bim $r6,[$sp],$r10,#0x2    ! {$r6~$r10, $lp}
    4f1a:	dd 9e       	ret5 $lp
    4f1c:	84 00       	movi55 $r0,#0x0
    4f1e:	ec 08       	addi10.sp #0x8
    4f20:	3a 6f a8 84 	lmw.bim $r6,[$sp],$r10,#0x2    ! {$r6~$r10, $lp}
    4f24:	dd 9e       	ret5 $lp
    4f26:	92 00       	nop16
    4f28:	44 0f ff ac 	movi $r0,#-84
    4f2c:	d5 f4       	j8 4f14 <lfs_bd_flush+0x7c>
    4f2e:	92 00       	nop16
    4f30:	44 00 36 d4 	movi $r0,#0x36d4
    4f34:	44 10 00 92 	movi $r1,#0x92
    4f38:	44 20 7c 60 	movi $r2,#0x7c60
    4f3c:	44 30 39 2c 	movi $r3,#0x392c
    4f40:	49 00 26 6e 	jal 9c1c <__assert_func>
    4f44:	92 00       	nop16
    4f46:	92 00       	nop16
    4f48:	44 00 36 d4 	movi $r0,#0x36d4
    4f4c:	44 10 00 8e 	movi $r1,#0x8e
    4f50:	44 20 7c 60 	movi $r2,#0x7c60
    4f54:	44 30 39 a4 	movi $r3,#0x39a4
    4f58:	49 00 26 62 	jal 9c1c <__assert_func>
    4f5c:	92 00       	nop16
    4f5e:	92 00       	nop16

00004f60 <lfs_bd_prog>:
    4f60:	3a 6f ba bc 	smw.adm $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    4f64:	ef fc       	addi10.sp #-4
    4f66:	80 c1       	mov55 $r6,$r1
    4f68:	81 04       	mov55 $r8,$r4
    4f6a:	81 40       	mov55 $r10,$r0
    4f6c:	81 c2       	mov55 $r14,$r2
    4f6e:	83 83       	mov55 $fp,$r3
    4f70:	80 e5       	mov55 $r7,$r5
    4f72:	04 9f 80 0c 	lwi $r9,[$sp+#0x30]
    4f76:	04 cf 80 0d 	lwi $r12,[$sp+#0x34]
    4f7a:	04 10 00 1a 	lwi $r1,[$r0+#0x68]
    4f7e:	5a 47 fe 07 	beqc $r4,#-2,4f8c <lfs_bd_prog+0x2c>
    4f82:	04 00 80 08 	lwi $r0,[$r1+#0x20]
    4f86:	e2 80       	slt45 $r4,$r0
    4f88:	4e f2 00 6e 	beqz $r15,5064 <lfs_bd_prog+0x104>
    4f8c:	a0 0f       	lwi333 $r0,[$r1+#0x1c]
    4f8e:	40 13 b0 00 	add $r1,$r7,$r12
    4f92:	e2 01       	slt45 $r0,$r1
    4f94:	e9 5c       	bnezs8 504c <lfs_bd_prog+0xec>
    4f96:	85 60       	movi55 $r11,#0x0
    4f98:	4e c3 00 13 	bnez $r12,4fbe <lfs_bd_prog+0x5e>
    4f9c:	d5 3e       	j8 5018 <lfs_bd_prog+0xb8>
    4f9e:	92 00       	nop16
    4fa0:	5a 5f ff 4a 	bnec $r5,#-1,5034 <lfs_bd_prog+0xd4>
    4fa4:	04 45 00 1a 	lwi $r4,[$r10+#0x68]
    4fa8:	b7 06       	swi450 $r8,[$r6]
    4faa:	05 02 00 06 	lwi $r16,[$r4+#0x18]
    4fae:	14 b3 00 02 	swi $r11,[$r6+#0x8]
    4fb2:	41 13 c2 17 	divr $r17,$r16,$r7,$r16
    4fb6:	41 03 c0 01 	sub $r16,$r7,$r16
    4fba:	15 03 00 01 	swi $r16,[$r6+#0x4]
    4fbe:	b4 a6       	lwi450 $r5,[$r6]
    4fc0:	4c 54 7f f0 	bne $r5,$r8,4fa0 <lfs_bd_prog+0x40>
    4fc4:	a0 71       	lwi333 $r1,[$r6+#0x4]
    4fc6:	e2 e1       	slt45 $r7,$r1
    4fc8:	e9 ec       	bnezs8 4fa0 <lfs_bd_prog+0x40>
    4fca:	04 05 00 1a 	lwi $r0,[$r10+#0x68]
    4fce:	04 00 00 0a 	lwi $r0,[$r0+#0x28]
    4fd2:	88 01       	add45 $r0,$r1
    4fd4:	e2 e0       	slt45 $r7,$r0
    4fd6:	e8 e5       	beqzs8 4fa0 <lfs_bd_prog+0x40>
    4fd8:	8a 07       	sub45 $r0,$r7
    4fda:	40 d6 00 06 	slt $r13,$r12,$r0
    4fde:	a0 b3       	lwi333 $r2,[$r6+#0xc]
    4fe0:	40 06 34 1b 	cmovn $r0,$r12,$r13
    4fe4:	81 a0       	mov55 $r13,$r0
    4fe6:	9a 39       	sub333 $r0,$r7,$r1
    4fe8:	88 02       	add45 $r0,$r2
    4fea:	80 29       	mov55 $r1,$r9
    4fec:	80 4d       	mov55 $r2,$r13
    4fee:	49 00 27 b3 	jal 9f54 <memcpy>
    4ff2:	a0 31       	lwi333 $r0,[$r6+#0x4]
    4ff4:	a0 b2       	lwi333 $r2,[$r6+#0x8]
    4ff6:	04 35 00 1a 	lwi $r3,[$r10+#0x68]
    4ffa:	88 ed       	add45 $r7,$r13
    4ffc:	9a 38       	sub333 $r0,$r7,$r0
    4ffe:	40 10 08 06 	slt $r1,$r0,$r2
    5002:	04 51 80 0a 	lwi $r5,[$r3+#0x28]
    5006:	40 01 04 1b 	cmovn $r0,$r2,$r1
    500a:	89 2d       	add45 $r9,$r13
    500c:	40 c6 34 01 	sub $r12,$r12,$r13
    5010:	a8 32       	swi333 $r0,[$r6+#0x8]
    5012:	d0 09       	beqs38 $r0,5024 <lfs_bd_prog+0xc4>
    5014:	4e c3 ff d5 	bnez $r12,4fbe <lfs_bd_prog+0x5e>
    5018:	44 00 00 00 	movi $r0,#0x0
    501c:	ec 04       	addi10.sp #0x4
    501e:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    5022:	dd 9e       	ret5 $lp
    5024:	80 0a       	mov55 $r0,$r10
    5026:	80 26       	mov55 $r1,$r6
    5028:	80 4e       	mov55 $r2,$r14
    502a:	80 7c       	mov55 $r3,$fp
    502c:	49 ff ff 36 	jal 4e98 <lfs_bd_flush>
    5030:	c0 f2       	beqz38 $r0,5014 <lfs_bd_prog+0xb4>
    5032:	d5 f5       	j8 501c <lfs_bd_prog+0xbc>
    5034:	44 00 36 d4 	movi $r0,#0x36d4
    5038:	44 10 00 dd 	movi $r1,#0xdd
    503c:	44 20 7c 70 	movi $r2,#0x7c70
    5040:	44 30 3a 2c 	movi $r3,#0x3a2c
    5044:	49 00 25 ec 	jal 9c1c <__assert_func>
    5048:	92 00       	nop16
    504a:	92 00       	nop16
    504c:	44 00 36 d4 	movi $r0,#0x36d4
    5050:	44 10 00 c0 	movi $r1,#0xc0
    5054:	44 20 7c 70 	movi $r2,#0x7c70
    5058:	44 30 3a 08 	movi $r3,#0x3a08
    505c:	49 00 25 e0 	jal 9c1c <__assert_func>
    5060:	92 00       	nop16
    5062:	92 00       	nop16
    5064:	44 00 36 d4 	movi $r0,#0x36d4
    5068:	44 10 00 bf 	movi $r1,#0xbf
    506c:	44 20 7c 70 	movi $r2,#0x7c70
    5070:	44 30 39 cc 	movi $r3,#0x39cc
    5074:	49 00 25 d4 	jal 9c1c <__assert_func>
    5078:	92 00       	nop16
    507a:	92 00       	nop16

0000507c <lfs_dir_commitprog>:
    507c:	3a 6f a4 bc 	smw.adm $r6,[$sp],$r9,#0x2    ! {$r6~$r9, $lp}
    5080:	ef f4       	addi10.sp #-12
    5082:	b6 5f       	swi450 $r2,[$sp]
    5084:	f3 81       	swi37.sp $r3,[+#0x4]
    5086:	80 c1       	mov55 $r6,$r1
    5088:	81 22       	mov55 $r9,$r2
    508a:	80 e3       	mov55 $r7,$r3
    508c:	50 10 00 10 	addi $r1,$r0,#0x10
    5090:	80 40       	mov55 $r2,$r0
    5092:	84 60       	movi55 $r3,#0x0
    5094:	b4 86       	lwi450 $r4,[$r6]
    5096:	a1 71       	lwi333 $r5,[$r6+#0x4]
    5098:	49 ff ff 64 	jal 4f60 <lfs_bd_prog>
    509c:	81 00       	mov55 $r8,$r0
    509e:	c8 0a       	bnez38 $r0,50b2 <lfs_dir_commitprog+0x36>
    50a0:	80 29       	mov55 $r1,$r9
    50a2:	80 47       	mov55 $r2,$r7
    50a4:	a0 33       	lwi333 $r0,[$r6+#0xc]
    50a6:	49 00 16 15 	jal 7cd0 <lfs_crc>
    50aa:	a0 71       	lwi333 $r1,[$r6+#0x4]
    50ac:	a8 33       	swi333 $r0,[$r6+#0xc]
    50ae:	88 e1       	add45 $r7,$r1
    50b0:	a9 f1       	swi333 $r7,[$r6+#0x4]
    50b2:	80 08       	mov55 $r0,$r8
    50b4:	ec 0c       	addi10.sp #0xc
    50b6:	3a 6f a4 84 	lmw.bim $r6,[$sp],$r9,#0x2    ! {$r6~$r9, $lp}
    50ba:	dd 9e       	ret5 $lp

000050bc <lfs_dir_commitattr>:
    50bc:	3a 6f b8 bc 	smw.adm $r6,[$sp],$r14,#0x2    ! {$r6~$r14, $lp}
    50c0:	ef f0       	addi10.sp #-16
    50c2:	40 61 58 08 	slli $r6,$r2,#0x16
    50c6:	90 d6       	srai45 $r6,#0x16
    50c8:	8c c1       	addi45 $r6,#0x1
    50ca:	e6 c1       	slti45 $r6,#0x1
    50cc:	a1 09       	lwi333 $r4,[$r1+#0x4]
    50ce:	40 f7 88 00 	add $r15,$r15,$r2
    50d2:	54 67 83 ff 	andi $r6,$r15,#0x3ff
    50d6:	8c 84       	addi45 $r4,#0x4
    50d8:	a1 4d       	lwi333 $r5,[$r1+#0x14]
    50da:	88 86       	add45 $r4,$r6
    50dc:	e2 a4       	slt45 $r5,$r4
    50de:	81 21       	mov55 $r9,$r1
    50e0:	e9 48       	bnezs8 5170 <lfs_dir_commitattr+0xb4>
    50e2:	a1 0a       	lwi333 $r4,[$r1+#0x8]
    50e4:	42 e1 7c 09 	bclr $r14,$r2,#0x1f
    50e8:	40 47 10 03 	xor $r4,$r14,$r4
    50ec:	40 42 00 14 	wsbh $r4,$r4
    50f0:	81 43       	mov55 $r10,$r3
    50f2:	80 e2       	mov55 $r7,$r2
    50f4:	40 42 40 0b 	rotri $r4,$r4,#0x10
    50f8:	b0 83       	addri36.sp $r2,#0xc
    50fa:	84 64       	movi55 $r3,#0x4
    50fc:	81 00       	mov55 $r8,$r0
    50fe:	f4 83       	swi37.sp $r4,[+#0xc]
    5100:	49 ff ff be 	jal 507c <lfs_dir_commitprog>
    5104:	c8 0e       	bnez38 $r0,5120 <lfs_dir_commitattr+0x64>
    5106:	4e 75 00 11 	bltz $r7,5128 <lfs_dir_commitattr+0x6c>
    510a:	fd 04       	movd44 $r0,$r8
    510c:	80 4a       	mov55 $r2,$r10
    510e:	80 66       	mov55 $r3,$r6
    5110:	49 ff ff b6 	jal 507c <lfs_dir_commitprog>
    5114:	c8 06       	bnez38 $r0,5120 <lfs_dir_commitattr+0x64>
    5116:	92 00       	nop16
    5118:	14 e4 80 02 	swi $r14,[$r9+#0x8]
    511c:	84 00       	movi55 $r0,#0x0
    511e:	92 00       	nop16
    5120:	ec 10       	addi10.sp #0x10
    5122:	3a 6f b8 84 	lmw.bim $r6,[$sp],$r14,#0x2    ! {$r6~$r14, $lp}
    5126:	dd 9e       	ret5 $lp
    5128:	c6 f8       	beqz38 $r6,5118 <lfs_dir_commitattr+0x5c>
    512a:	50 d4 00 68 	addi $r13,$r8,#0x68
    512e:	84 e0       	movi55 $r7,#0x0
    5130:	50 bf 80 0b 	addi $r11,$sp,#0xb
    5134:	85 81       	movi55 $r12,#0x1
    5136:	d5 07       	j8 5144 <lfs_dir_commitattr+0x88>
    5138:	49 ff ff a2 	jal 507c <lfs_dir_commitprog>
    513c:	c8 f2       	bnez38 $r0,5120 <lfs_dir_commitattr+0x64>
    513e:	4c 73 3f ed 	beq $r7,$r6,5118 <lfs_dir_commitattr+0x5c>
    5142:	92 00       	nop16
    5144:	04 55 00 01 	lwi $r5,[$r10+#0x4]
    5148:	b4 8a       	lwi450 $r4,[$r10]
    514a:	9a f7       	sub333 $r3,$r6,$r7
    514c:	88 a7       	add45 $r5,$r7
    514e:	84 20       	movi55 $r1,#0x0
    5150:	80 48       	mov55 $r2,$r8
    5152:	b7 7f       	swi450 $r11,[$sp]
    5154:	14 cf 80 01 	swi $r12,[$sp+#0x4]
    5158:	80 0d       	mov55 $r0,$r13
    515a:	49 ff f7 a7 	jal 40a8 <lfs_bd_read.isra.13>
    515e:	80 80       	mov55 $r4,$r0
    5160:	80 29       	mov55 $r1,$r9
    5162:	80 08       	mov55 $r0,$r8
    5164:	80 4b       	mov55 $r2,$r11
    5166:	84 61       	movi55 $r3,#0x1
    5168:	8c e1       	addi45 $r7,#0x1
    516a:	c4 e7       	beqz38 $r4,5138 <lfs_dir_commitattr+0x7c>
    516c:	80 04       	mov55 $r0,$r4
    516e:	d5 d9       	j8 5120 <lfs_dir_commitattr+0x64>
    5170:	44 0f ff e4 	movi $r0,#-28
    5174:	d5 d6       	j8 5120 <lfs_dir_commitattr+0x64>
    5176:	92 00       	nop16

00005178 <lfs_dir_commit_commit>:
    5178:	fd 20       	movd44 $r4,$r0
    517a:	80 62       	mov55 $r3,$r2
    517c:	b4 00       	lwi450 $r0,[$r0]
    517e:	a0 61       	lwi333 $r1,[$r4+#0x4]
    5180:	80 45       	mov55 $r2,$r5
    5182:	d5 9d       	j8 50bc <lfs_dir_commitattr>

00005184 <lfs_dir_commitcrc>:
    5184:	3a 6f ba bc 	smw.adm $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    5188:	ef cc       	addi10.sp #-52
    518a:	36 3f 80 06 	fsdi $fd3,[$sp+#0x18]
    518e:	36 4f 80 08 	fsdi $fd4,[$sp+#0x20]
    5192:	36 5f 80 0a 	fsdi $fd5,[$sp+#0x28]
    5196:	30 80 80 01 	flsi $fs8,[$r1+#0x4]
    519a:	81 40       	mov55 $r10,$r0
    519c:	04 00 00 1a 	lwi $r0,[$r0+#0x68]
    51a0:	81 21       	mov55 $r9,$r1
    51a2:	04 b0 00 06 	lwi $r11,[$r0+#0x18]
    51a6:	6a 04 00 01 	fmfsr $r0,$fs8
    51aa:	30 90 80 03 	flsi $fs9,[$r1+#0xc]
    51ae:	88 0b       	add45 $r0,$r11
    51b0:	8c 07       	addi45 $r0,#0x7
    51b2:	40 10 2d 77 	divr $r1,$r11,$r0,$r11
    51b6:	40 b0 2c 01 	sub $r11,$r0,$r11
    51ba:	6a 04 00 01 	fmfsr $r0,$fs8
    51be:	50 15 00 10 	addi $r1,$r10,#0x10
    51c2:	e2 0b       	slt45 $r0,$r11
    51c4:	4e f2 00 88 	beqz $r15,52d4 <lfs_dir_commitcrc+0x150>
    51c8:	50 05 00 68 	addi $r0,$r10,#0x68
    51cc:	6a 03 80 09 	fmtsr $r0,$fs7
    51d0:	46 e0 00 ff 	sethi $r14,#0xff
    51d4:	b0 03       	addri36.sp $r0,#0xc
    51d6:	6a 64 00 01 	fmfsr $r6,$fs8
    51da:	6a 03 00 09 	fmtsr $r0,$fs6
    51de:	44 c0 03 fe 	movi $r12,#0x3fe
    51e2:	51 c5 ff f8 	addi $fp,$r11,#-8
    51e6:	50 e7 0c 00 	addi $r14,$r14,#0xc00
    51ea:	50 8f 80 10 	addi $r8,$sp,#0x10
    51ee:	50 d5 00 10 	addi $r13,$r10,#0x10
    51f2:	d5 14       	j8 521a <lfs_dir_commitcrc+0x96>
    51f4:	f0 03       	lwi37.sp $r0,[+#0xc]
    51f6:	04 64 80 01 	lwi $r6,[$r9+#0x4]
    51fa:	54 30 03 ff 	andi $r3,$r0,#0x3ff
    51fe:	8c c4       	addi45 $r6,#0x4
    5200:	88 c3       	add45 $r6,$r3
    5202:	40 73 fc 08 	slli $r7,$r7,#0x1f
    5206:	ff c5       	xor33 $r7,$r0
    5208:	84 5f       	movi55 $r2,#-1
    520a:	e2 cb       	slt45 $r6,$r11
    520c:	14 64 80 01 	swi $r6,[$r9+#0x4]
    5210:	14 74 80 02 	swi $r7,[$r9+#0x8]
    5214:	14 24 80 03 	swi $r2,[$r9+#0xc]
    5218:	e8 5e       	beqzs8 52d4 <lfs_dir_commitcrc+0x150>
    521a:	9d f4       	addi333 $r7,$r6,#0x4
    521c:	40 65 9c 01 	sub $r6,$r11,$r7
    5220:	40 06 18 06 	slt $r0,$r12,$r6
    5224:	40 66 00 1b 	cmovn $r6,$r12,$r0
    5228:	88 c7       	add45 $r6,$r7
    522a:	e2 cb       	slt45 $r6,$r11
    522c:	e8 05       	beqzs8 5236 <lfs_dir_commitcrc+0xb2>
    522e:	40 0e 18 06 	slt $r0,$fp,$r6
    5232:	40 6e 00 1b 	cmovn $r6,$fp,$r0
    5236:	84 04       	movi55 $r0,#0x4
    5238:	f0 81       	swi37.sp $r0,[+#0x4]
    523a:	32 6f 80 00 	fssi $fs6,[$sp+#0x0]
    523e:	6a 03 80 01 	fmfsr $r0,$fs7
    5242:	86 1f       	movi55 $r16,#-1
    5244:	84 20       	movi55 $r1,#0x0
    5246:	80 4a       	mov55 $r2,$r10
    5248:	84 64       	movi55 $r3,#0x4
    524a:	b4 89       	lwi450 $r4,[$r9]
    524c:	80 a6       	mov55 $r5,$r6
    524e:	15 0f 80 03 	swi $r16,[$sp+#0xc]
    5252:	49 ff f7 2b 	jal 40a8 <lfs_bd_read.isra.13>
    5256:	c0 03       	beqz38 $r0,525c <lfs_dir_commitcrc+0xd8>
    5258:	5a 0f ac 34 	bnec $r0,#-84,52c0 <lfs_dir_commitcrc+0x13c>
    525c:	8a c7       	sub45 $r6,$r7
    525e:	f7 03       	lwi37.sp $r7,[+#0xc]
    5260:	04 34 80 02 	lwi $r3,[$r9+#0x8]
    5264:	40 73 80 14 	wsbh $r7,$r7
    5268:	42 73 bc 0a 	btgl $r7,$r7,#0xf
    526c:	42 73 bc 0b 	btst $r7,$r7,#0xf
    5270:	50 03 85 00 	addi $r0,$r7,#0x500
    5274:	40 00 50 08 	slli $r0,$r0,#0x14
    5278:	40 63 38 04 	or $r6,$r6,$r14
    527c:	ff 87       	or33 $r6,$r0
    527e:	fe f5       	xor33 $r3,$r6
    5280:	40 31 80 14 	wsbh $r3,$r3
    5284:	40 31 c0 0b 	rotri $r3,$r3,#0x10
    5288:	80 28       	mov55 $r1,$r8
    528a:	84 44       	movi55 $r2,#0x4
    528c:	04 04 80 03 	lwi $r0,[$r9+#0xc]
    5290:	b6 68       	swi450 $r3,[$r8]
    5292:	f6 83       	swi37.sp $r6,[+#0xc]
    5294:	49 00 15 1e 	jal 7cd0 <lfs_crc>
    5298:	14 04 80 03 	swi $r0,[$r9+#0xc]
    529c:	82 00       	mov55 $r16,$r0
    529e:	84 08       	movi55 $r0,#0x8
    52a0:	f0 81       	swi37.sp $r0,[+#0x4]
    52a2:	b7 1f       	swi450 $r8,[$sp]
    52a4:	80 2d       	mov55 $r1,$r13
    52a6:	80 0a       	mov55 $r0,$r10
    52a8:	80 4a       	mov55 $r2,$r10
    52aa:	84 60       	movi55 $r3,#0x0
    52ac:	b4 89       	lwi450 $r4,[$r9]
    52ae:	04 54 80 01 	lwi $r5,[$r9+#0x4]
    52b2:	15 04 00 01 	swi $r16,[$r8+#0x4]
    52b6:	49 ff fe 55 	jal 4f60 <lfs_bd_prog>
    52ba:	80 2d       	mov55 $r1,$r13
    52bc:	c0 9c       	beqz38 $r0,51f4 <lfs_dir_commitcrc+0x70>
    52be:	92 00       	nop16
    52c0:	ec 18       	addi10.sp #0x18
    52c2:	34 3f 90 02 	fldi.bi $fd3,[$sp],#0x8
    52c6:	34 4f 90 02 	fldi.bi $fd4,[$sp],#0x8
    52ca:	34 5f 90 03 	fldi.bi $fd5,[$sp],#0xc
    52ce:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    52d2:	dd 9e       	ret5 $lp
    52d4:	84 1f       	movi55 $r0,#-1
    52d6:	b6 0a       	swi450 $r0,[$r10]
    52d8:	80 4a       	mov55 $r2,$r10
    52da:	80 0a       	mov55 $r0,$r10
    52dc:	84 60       	movi55 $r3,#0x0
    52de:	49 ff fd dd 	jal 4e98 <lfs_bd_flush>
    52e2:	c8 ef       	bnez38 $r0,52c0 <lfs_dir_commitcrc+0x13c>
    52e4:	04 05 00 1a 	lwi $r0,[$r10+#0x68]
    52e8:	a0 44       	lwi333 $r1,[$r0+#0x10]
    52ea:	dd 21       	jral5 $r1
    52ec:	4e 06 00 66 	bgtz $r0,53b8 <lfs_dir_commitcrc+0x234>
    52f0:	c8 e8       	bnez38 $r0,52c0 <lfs_dir_commitcrc+0x13c>
    52f2:	6a 04 00 01 	fmfsr $r0,$fs8
    52f6:	04 64 80 04 	lwi $r6,[$r9+#0x10]
    52fa:	8c 04       	addi45 $r0,#0x4
    52fc:	6a 03 00 09 	fmtsr $r0,$fs6
    5300:	e2 cb       	slt45 $r6,$r11
    5302:	e8 54       	beqzs8 53aa <lfs_dir_commitcrc+0x226>
    5304:	44 00 03 fe 	movi $r0,#0x3fe
    5308:	6a 03 80 09 	fmtsr $r0,$fs7
    530c:	50 05 ff f8 	addi $r0,$r11,#-8
    5310:	6a 05 00 09 	fmtsr $r0,$fs10
    5314:	51 c5 00 68 	addi $fp,$r10,#0x68
    5318:	50 8f 80 10 	addi $r8,$sp,#0x10
    531c:	44 e0 00 01 	movi $r14,#0x1
    5320:	6a 03 00 01 	fmfsr $r0,$fs6
    5324:	50 d0 00 04 	addi $r13,$r0,#0x4
    5328:	e2 cd       	slt45 $r6,$r13
    532a:	e8 43       	beqzs8 53b0 <lfs_dir_commitcrc+0x22c>
    532c:	40 76 98 01 	sub $r7,$r13,$r6
    5330:	85 9f       	movi55 $r12,#-1
    5332:	d5 0d       	j8 534c <lfs_dir_commitcrc+0x1c8>
    5334:	80 0c       	mov55 $r0,$r12
    5336:	80 28       	mov55 $r1,$r8
    5338:	84 41       	movi55 $r2,#0x1
    533a:	8c c1       	addi45 $r6,#0x1
    533c:	49 00 14 ca 	jal 7cd0 <lfs_crc>
    5340:	40 13 34 06 	slt $r1,$r6,$r13
    5344:	81 80       	mov55 $r12,$r0
    5346:	8e e1       	subi45 $r7,#0x1
    5348:	c1 18       	beqz38 $r1,5378 <lfs_dir_commitcrc+0x1f4>
    534a:	92 00       	nop16
    534c:	6a 04 00 01 	fmfsr $r0,$fs8
    5350:	4c 60 40 06 	bne $r6,$r0,535c <lfs_dir_commitcrc+0x1d8>
    5354:	6a 04 80 01 	fmfsr $r0,$fs9
    5358:	4c c0 40 2c 	bne $r12,$r0,53b0 <lfs_dir_commitcrc+0x22c>
    535c:	b7 1f       	swi450 $r8,[$sp]
    535e:	14 ef 80 01 	swi $r14,[$sp+#0x4]
    5362:	80 1c       	mov55 $r0,$fp
    5364:	84 20       	movi55 $r1,#0x0
    5366:	80 4a       	mov55 $r2,$r10
    5368:	80 67       	mov55 $r3,$r7
    536a:	b4 89       	lwi450 $r4,[$r9]
    536c:	80 a6       	mov55 $r5,$r6
    536e:	49 ff f6 9d 	jal 40a8 <lfs_bd_read.isra.13>
    5372:	c0 e1       	beqz38 $r0,5334 <lfs_dir_commitcrc+0x1b0>
    5374:	d5 a6       	j8 52c0 <lfs_dir_commitcrc+0x13c>
    5376:	92 00       	nop16
    5378:	c8 1c       	bnez38 $r0,53b0 <lfs_dir_commitcrc+0x22c>
    537a:	6a 03 00 01 	fmfsr $r0,$fs6
    537e:	6a 13 80 01 	fmfsr $r1,$fs7
    5382:	40 65 80 01 	sub $r6,$r11,$r0
    5386:	e2 26       	slt45 $r1,$r6
    5388:	40 60 bc 1b 	cmovn $r6,$r1,$r15
    538c:	6a 03 00 01 	fmfsr $r0,$fs6
    5390:	88 c0       	add45 $r6,$r0
    5392:	e2 cb       	slt45 $r6,$r11
    5394:	e8 0b       	beqzs8 53aa <lfs_dir_commitcrc+0x226>
    5396:	6a 05 00 01 	fmfsr $r0,$fs10
    539a:	e2 06       	slt45 $r0,$r6
    539c:	40 60 3c 1b 	cmovn $r6,$r0,$r15
    53a0:	9c 74       	addi333 $r1,$r6,#0x4
    53a2:	e2 cb       	slt45 $r6,$r11
    53a4:	6a 13 00 09 	fmtsr $r1,$fs6
    53a8:	e9 bc       	bnezs8 5320 <lfs_dir_commitcrc+0x19c>
    53aa:	84 00       	movi55 $r0,#0x0
    53ac:	48 ff ff 8a 	j 52c0 <lfs_dir_commitcrc+0x13c>
    53b0:	44 0f ff ac 	movi $r0,#-84
    53b4:	48 ff ff 86 	j 52c0 <lfs_dir_commitcrc+0x13c>
    53b8:	44 00 36 d4 	movi $r0,#0x36d4
    53bc:	44 10 00 b6 	movi $r1,#0xb6
    53c0:	44 20 7c 44 	movi $r2,#0x7c44
    53c4:	44 30 39 2c 	movi $r3,#0x392c
    53c8:	49 00 24 2a 	jal 9c1c <__assert_func>
    53cc:	92 00       	nop16
    53ce:	92 00       	nop16

000053d0 <lfs_dir_find_match>:
    53d0:	3a 6f 9c bc 	smw.adm $r6,[$sp],$r7,#0x2    ! {$r6~$r7, $lp}
    53d4:	ef f4       	addi10.sp #-12
    53d6:	a1 42       	lwi333 $r5,[$r0+#0x8]
    53d8:	54 70 83 ff 	andi $r7,$r1,#0x3ff
    53dc:	e2 a7       	slt45 $r5,$r7
    53de:	80 82       	mov55 $r4,$r2
    53e0:	80 45       	mov55 $r2,$r5
    53e2:	80 c0       	mov55 $r6,$r0
    53e4:	40 23 bc 1a 	cmovz $r2,$r7,$r15
    53e8:	b4 00       	lwi450 $r0,[$r0]
    53ea:	b6 5f       	swi450 $r2,[$sp]
    53ec:	b4 64       	lwi450 $r3,[$r4]
    53ee:	80 20       	mov55 $r1,$r0
    53f0:	a1 21       	lwi333 $r4,[$r4+#0x4]
    53f2:	a1 71       	lwi333 $r5,[$r6+#0x4]
    53f4:	49 ff fd 12 	jal 4e18 <lfs_bd_cmp.constprop.35>
    53f8:	c8 08       	bnez38 $r0,5408 <lfs_dir_find_match+0x38>
    53fa:	a1 72       	lwi333 $r5,[$r6+#0x8]
    53fc:	d7 0a       	beqs38 $r7,5410 <lfs_dir_find_match+0x40>
    53fe:	e2 a7       	slt45 $r5,$r7
    5400:	84 41       	movi55 $r2,#0x1
    5402:	84 02       	movi55 $r0,#0x2
    5404:	40 01 3c 1b 	cmovn $r0,$r2,$r15
    5408:	ec 0c       	addi10.sp #0xc
    540a:	3a 6f 9c 84 	lmw.bim $r6,[$sp],$r7,#0x2    ! {$r6~$r7, $lp}
    540e:	dd 9e       	ret5 $lp
    5410:	84 00       	movi55 $r0,#0x0
    5412:	ec 0c       	addi10.sp #0xc
    5414:	3a 6f 9c 84 	lmw.bim $r6,[$sp],$r7,#0x2    ! {$r6~$r7, $lp}
    5418:	dd 9e       	ret5 $lp
    541a:	92 00       	nop16

0000541c <lfs_dir_getslice>:
    541c:	3a 6f ba bc 	smw.adm $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    5420:	ef d4       	addi10.sp #-44
    5422:	36 3f 80 04 	fsdi $fd3,[$sp+#0x10]
    5426:	36 4f 80 06 	fsdi $fd4,[$sp+#0x18]
    542a:	36 5f 80 08 	fsdi $fd5,[$sp+#0x20]
    542e:	05 00 00 0f 	lwi $r16,[$r0+#0x3c]
    5432:	81 00       	mov55 $r8,$r0
    5434:	40 08 50 09 	srli $r0,$r16,#0x14
    5438:	a1 8c       	lwi333 $r6,[$r1+#0x10]
    543a:	54 00 07 00 	andi $r0,$r0,#0x700
    543e:	81 21       	mov55 $r9,$r1
    5440:	81 62       	mov55 $r11,$r2
    5442:	81 83       	mov55 $r12,$r3
    5444:	6a 44 00 09 	fmtsr $r4,$fs8
    5448:	6a 54 80 09 	fmtsr $r5,$fs9
    544c:	05 c0 80 03 	lwi $fp,[$r1+#0xc]
    5450:	f6 83       	swi37.sp $r6,[+#0xc]
    5452:	84 e0       	movi55 $r7,#0x0
    5454:	c0 10       	beqz38 $r0,5474 <lfs_dir_getslice+0x58>
    5456:	04 54 00 10 	lwi $r5,[$r8+#0x40]
    545a:	b4 21       	lwi450 $r1,[$r1]
    545c:	4c 50 80 aa 	beq $r5,$r1,55b0 <lfs_dir_getslice+0x194>
    5460:	04 34 00 11 	lwi $r3,[$r8+#0x44]
    5464:	04 24 80 01 	lwi $r2,[$r9+#0x4]
    5468:	4c 31 00 a4 	beq $r3,$r2,55b0 <lfs_dir_getslice+0x194>
    546c:	4c 51 00 a2 	beq $r5,$r2,55b0 <lfs_dir_getslice+0x194>
    5470:	4c 11 80 a0 	beq $r1,$r3,55b0 <lfs_dir_getslice+0x194>
    5474:	46 07 00 00 	sethi $r0,#0x70000
    5478:	46 e0 00 ff 	sethi $r14,#0xff
    547c:	50 e7 0c 00 	addi $r14,$r14,#0xc00
    5480:	6a 05 80 09 	fmtsr $r0,$fs11
    5484:	46 04 01 00 	sethi $r0,#0x40100
    5488:	40 a5 b8 02 	and $r10,$r11,$r14
    548c:	6a 03 00 09 	fmtsr $r0,$fs6
    5490:	46 00 ff 00 	sethi $r0,#0xff00
    5494:	93 4a       	srli45 $r10,#0xa
    5496:	50 d4 00 68 	addi $r13,$r8,#0x68
    549a:	6a e5 00 09 	fmtsr $r14,$fs10
    549e:	6a 03 80 09 	fmtsr $r0,$fs7
    54a2:	d5 11       	j8 54c4 <lfs_dir_getslice+0xa8>
    54a4:	6a 55 80 01 	fmfsr $r5,$fs11
    54a8:	44 10 04 00 	movi $r1,#0x400
    54ac:	ff 76       	and33 $r5,$r6
    54ae:	92 b4       	srli45 $r5,#0x14
    54b0:	41 16 1c 01 	sub $r17,$r12,$r7
    54b4:	4c 12 80 64 	beq $r1,$r5,557c <lfs_dir_getslice+0x160>
    54b8:	41 18 98 03 	xor $r17,$r17,$r6
    54bc:	40 f8 ac 02 	and $r15,$r17,$r11
    54c0:	e8 3a       	beqzs8 5534 <lfs_dir_getslice+0x118>
    54c2:	80 d0       	mov55 $r6,$r16
    54c4:	40 03 58 08 	slli $r0,$r6,#0x16
    54c8:	40 e0 58 0a 	srai $r14,$r0,#0x16
    54cc:	51 07 00 01 	addi $r16,$r14,#0x1
    54d0:	e7 81       	slti45 $r16,#0x1
    54d2:	40 f7 98 00 	add $r15,$r15,$r6
    54d6:	55 07 83 ff 	andi $r16,$r15,#0x3ff
    54da:	50 08 00 08 	addi $r0,$r16,#0x8
    54de:	40 0e 00 06 	slt $r0,$fp,$r0
    54e2:	53 08 7f fc 	subri $r16,$r16,#-4
    54e6:	4e 03 00 7f 	bnez $r0,55e4 <lfs_dir_getslice+0x1c8>
    54ea:	b0 03       	addri36.sp $r0,#0xc
    54ec:	b6 1f       	swi450 $r0,[$sp]
    54ee:	84 04       	movi55 $r0,#0x4
    54f0:	f0 81       	swi37.sp $r0,[+#0x4]
    54f2:	41 ce 40 00 	add $fp,$fp,$r16
    54f6:	80 0d       	mov55 $r0,$r13
    54f8:	84 20       	movi55 $r1,#0x0
    54fa:	80 48       	mov55 $r2,$r8
    54fc:	84 64       	movi55 $r3,#0x4
    54fe:	b4 89       	lwi450 $r4,[$r9]
    5500:	80 bc       	mov55 $r5,$fp
    5502:	49 ff f5 d3 	jal 40a8 <lfs_bd_read.isra.13>
    5506:	c8 31       	bnez38 $r0,5568 <lfs_dir_getslice+0x14c>
    5508:	05 0f 80 03 	lwi $r16,[$sp+#0xc]
    550c:	41 08 00 14 	wsbh $r16,$r16
    5510:	41 08 40 0b 	rotri $r16,$r16,#0x10
    5514:	41 08 18 03 	xor $r16,$r16,$r6
    5518:	43 08 7c 09 	bclr $r16,$r16,#0x1f
    551c:	15 0f 80 03 	swi $r16,[$sp+#0xc]
    5520:	4e a3 ff c2 	bnez $r10,54a4 <lfs_dir_getslice+0x88>
    5524:	41 16 1c 01 	sub $r17,$r12,$r7
    5528:	41 18 98 03 	xor $r17,$r17,$r6
    552c:	40 f8 ac 02 	and $r15,$r17,$r11
    5530:	4e f3 ff c9 	bnez $r15,54c2 <lfs_dir_getslice+0xa6>
    5534:	5a e7 ff 58 	beqc $r14,#-1,55e4 <lfs_dir_getslice+0x1c8>
    5538:	f0 16       	lwi37.sp $r0,[+#0x58]
    553a:	54 a3 03 ff 	andi $r10,$r6,#0x3ff
    553e:	f1 16       	lwi37.sp $r1,[+#0x58]
    5540:	e2 0a       	slt45 $r0,$r10
    5542:	6a 54 00 01 	fmfsr $r5,$fs8
    5546:	40 a0 bc 1b 	cmovn $r10,$r1,$r15
    554a:	8c a4       	addi45 $r5,#0x4
    554c:	32 9f 80 00 	fssi $fs9,[$sp+#0x0]
    5550:	14 af 80 01 	swi $r10,[$sp+#0x4]
    5554:	80 0d       	mov55 $r0,$r13
    5556:	84 20       	movi55 $r1,#0x0
    5558:	80 48       	mov55 $r2,$r8
    555a:	80 6a       	mov55 $r3,$r10
    555c:	b4 89       	lwi450 $r4,[$r9]
    555e:	88 bc       	add45 $r5,$fp
    5560:	49 ff f5 a4 	jal 40a8 <lfs_bd_read.isra.13>
    5564:	c0 42       	beqz38 $r0,55e8 <lfs_dir_getslice+0x1cc>
    5566:	92 00       	nop16
    5568:	ec 10       	addi10.sp #0x10
    556a:	34 3f 90 02 	fldi.bi $fd3,[$sp],#0x8
    556e:	34 4f 90 02 	fldi.bi $fd4,[$sp],#0x8
    5572:	34 5f 90 03 	fldi.bi $fd5,[$sp],#0xc
    5576:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    557a:	dd 9e       	ret5 $lp
    557c:	6a 05 00 01 	fmfsr $r0,$fs10
    5580:	40 13 00 02 	and $r1,$r6,$r0
    5584:	40 58 80 02 	and $r5,$r17,$r0
    5588:	92 2a       	srli45 $r1,#0xa
    558a:	40 02 a8 09 	srli $r0,$r5,#0xa
    558e:	96 49       	zeh33 $r1,$r1
    5590:	96 01       	zeh33 $r0,$r0
    5592:	e2 01       	slt45 $r0,$r1
    5594:	e9 92       	bnezs8 54b8 <lfs_dir_getslice+0x9c>
    5596:	6a 03 00 01 	fmfsr $r0,$fs6
    559a:	ff 47       	or33 $r5,$r0
    559c:	d6 24       	beqs38 $r6,55e4 <lfs_dir_getslice+0x1c8>
    559e:	6a 03 80 01 	fmfsr $r0,$fs7
    55a2:	fe 36       	and33 $r0,$r6
    55a4:	94 04       	slli333 $r0,$r0,#0x4
    55a6:	90 0e       	srai45 $r0,#0xe
    55a8:	88 e0       	add45 $r7,$r0
    55aa:	41 16 1c 01 	sub $r17,$r12,$r7
    55ae:	d5 bd       	j8 5528 <lfs_dir_getslice+0x10c>
    55b0:	46 00 00 ff 	sethi $r0,#0xff
    55b4:	50 00 0c 00 	addi $r0,$r0,#0xc00
    55b8:	40 15 80 02 	and $r1,$r11,$r0
    55bc:	84 e0       	movi55 $r7,#0x0
    55be:	4e 12 ff 5b 	beqz $r1,5474 <lfs_dir_getslice+0x58>
    55c2:	41 08 00 02 	and $r16,$r16,$r0
    55c6:	40 06 00 02 	and $r0,$r12,$r0
    55ca:	93 8a       	srli45 $r16,#0xa
    55cc:	92 0a       	srli45 $r0,#0xa
    55ce:	41 08 00 13 	zeh $r16,$r16
    55d2:	96 01       	zeh33 $r0,$r0
    55d4:	e2 10       	slt45 $r0,$r16
    55d6:	44 1f fc 00 	movi $r1,#-1024
    55da:	84 e0       	movi55 $r7,#0x0
    55dc:	40 70 bc 1a 	cmovz $r7,$r1,$r15
    55e0:	48 ff ff 4a 	j 5474 <lfs_dir_getslice+0x58>
    55e4:	84 1e       	movi55 $r0,#-2
    55e6:	d5 c1       	j8 5568 <lfs_dir_getslice+0x14c>
    55e8:	f2 16       	lwi37.sp $r2,[+#0x58]
    55ea:	6a 04 80 01 	fmfsr $r0,$fs9
    55ee:	84 20       	movi55 $r1,#0x0
    55f0:	88 0a       	add45 $r0,$r10
    55f2:	8a 4a       	sub45 $r2,$r10
    55f4:	49 00 24 e4 	jal 9fbc <memset>
    55f8:	98 37       	add333 $r0,$r6,$r7
    55fa:	d5 b7       	j8 5568 <lfs_dir_getslice+0x14c>

000055fc <lfs_dir_getgstate>:
    55fc:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    5600:	ef e8       	addi10.sp #-24
    5602:	84 6c       	movi55 $r3,#0xc
    5604:	80 c2       	mov55 $r6,$r2
    5606:	46 27 ff 00 	sethi $r2,#0x7ff00
    560a:	b6 7f       	swi450 $r3,[$sp]
    560c:	84 80       	movi55 $r4,#0x0
    560e:	50 31 00 0c 	addi $r3,$r2,#0xc
    5612:	b1 43       	addri36.sp $r5,#0xc
    5614:	49 ff ff 04 	jal 541c <lfs_dir_getslice>
    5618:	4e 05 00 13 	bltz $r0,563e <lfs_dir_getgstate+0x42>
    561c:	b4 26       	lwi450 $r1,[$r6]
    561e:	f2 03       	lwi37.sp $r2,[+#0xc]
    5620:	a0 31       	lwi333 $r0,[$r6+#0x4]
    5622:	fe 8d       	xor33 $r2,$r1
    5624:	f1 04       	lwi37.sp $r1,[+#0x10]
    5626:	a0 f2       	lwi333 $r3,[$r6+#0x8]
    5628:	fe 45       	xor33 $r1,$r0
    562a:	f0 05       	lwi37.sp $r0,[+#0x14]
    562c:	b6 46       	swi450 $r2,[$r6]
    562e:	fe 1d       	xor33 $r0,$r3
    5630:	a8 32       	swi333 $r0,[$r6+#0x8]
    5632:	a8 71       	swi333 $r1,[$r6+#0x4]
    5634:	84 00       	movi55 $r0,#0x0
    5636:	ec 18       	addi10.sp #0x18
    5638:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    563c:	dd 9e       	ret5 $lp
    563e:	84 3e       	movi55 $r1,#-2
    5640:	fe 45       	xor33 $r1,$r0
    5642:	84 40       	movi55 $r2,#0x0
    5644:	40 01 04 1a 	cmovz $r0,$r2,$r1
    5648:	ec 18       	addi10.sp #0x18
    564a:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    564e:	dd 9e       	ret5 $lp

00005650 <lfs_dir_find>:
    5650:	3a 6f ba bc 	smw.adm $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    5654:	ef cc       	addi10.sp #-52
    5656:	36 3f 80 06 	fsdi $fd3,[$sp+#0x18]
    565a:	36 4f 80 08 	fsdi $fd4,[$sp+#0x20]
    565e:	36 5f 80 0a 	fsdi $fd5,[$sp+#0x28]
    5662:	6a 24 80 09 	fmtsr $r2,$fs9
    5666:	81 c3       	mov55 $r14,$r3
    5668:	81 a0       	mov55 $r13,$r0
    566a:	81 81       	mov55 $r12,$r1
    566c:	30 61 00 00 	flsi $fs6,[$r2+#0x0]
    5670:	c3 04       	beqz38 $r3,5678 <lfs_dir_find+0x28>
    5672:	44 00 03 ff 	movi $r0,#0x3ff
    5676:	ac 18       	shi333 $r0,[$r3+#0x0]
    5678:	46 90 02 ff 	sethi $r9,#0x2ff
    567c:	04 06 80 09 	lwi $r0,[$r13+#0x24]
    5680:	50 94 8c 00 	addi $r9,$r9,#0xc00
    5684:	04 16 80 08 	lwi $r1,[$r13+#0x20]
    5688:	14 06 00 07 	swi $r0,[$r12+#0x1c]
    568c:	42 04 d4 09 	bclr $r0,$r9,#0x15
    5690:	6a 05 00 09 	fmtsr $r0,$fs10
    5694:	46 02 00 00 	sethi $r0,#0x20000
    5698:	8c 08       	addi45 $r0,#0x8
    569a:	6a 04 00 09 	fmtsr $r0,$fs8
    569e:	46 07 00 ff 	sethi $r0,#0x700ff
    56a2:	50 00 0c 00 	addi $r0,$r0,#0xc00
    56a6:	6a 03 80 09 	fmtsr $r0,$fs7
    56aa:	14 16 00 06 	swi $r1,[$r12+#0x18]
    56ae:	92 00       	nop16
    56b0:	6a 03 00 01 	fmfsr $r0,$fs6
    56b4:	44 10 3a 50 	movi $r1,#0x3a50
    56b8:	6a a3 00 01 	fmfsr $r10,$fs6
    56bc:	49 00 25 d0 	jal a25c <strspn>
    56c0:	89 40       	add45 $r10,$r0
    56c2:	80 0a       	mov55 $r0,$r10
    56c4:	44 10 3a 50 	movi $r1,#0x3a50
    56c8:	49 00 25 b8 	jal a238 <strcspn>
    56cc:	81 60       	mov55 $r11,$r0
    56ce:	5a 08 01 05 	bnec $r0,#0x1,56d8 <lfs_dir_find+0x88>
    56d2:	48 00 00 8b 	j 57e8 <lfs_dir_find+0x198>
    56d6:	92 00       	nop16
    56d8:	5a 08 02 04 	bnec $r0,#0x2,56e0 <lfs_dir_find+0x90>
    56dc:	48 00 00 94 	j 5804 <lfs_dir_find+0x1b4>
    56e0:	40 05 2c 00 	add $r0,$r10,$r11
    56e4:	6a 03 00 09 	fmtsr $r0,$fs6
    56e8:	80 c0       	mov55 $r6,$r0
    56ea:	85 01       	movi55 $r8,#0x1
    56ec:	80 06       	mov55 $r0,$r6
    56ee:	44 10 3a 50 	movi $r1,#0x3a50
    56f2:	49 00 25 b5 	jal a25c <strspn>
    56f6:	88 c0       	add45 $r6,$r0
    56f8:	44 10 3a 50 	movi $r1,#0x3a50
    56fc:	80 06       	mov55 $r0,$r6
    56fe:	49 00 25 9d 	jal a238 <strcspn>
    5702:	80 e0       	mov55 $r7,$r0
    5704:	c0 14       	beqz38 $r0,572c <lfs_dir_find+0xdc>
    5706:	5a 00 02 05 	beqc $r0,#0x2,5710 <lfs_dir_find+0xc0>
    570a:	8d 01       	addi45 $r8,#0x1
    570c:	88 c7       	add45 $r6,$r7
    570e:	d5 ef       	j8 56ec <lfs_dir_find+0x9c>
    5710:	80 06       	mov55 $r0,$r6
    5712:	44 10 3a 58 	movi $r1,#0x3a58
    5716:	84 42       	movi55 $r2,#0x2
    5718:	49 00 24 00 	jal 9f18 <memcmp>
    571c:	c8 f7       	bnez38 $r0,570a <lfs_dir_find+0xba>
    571e:	8f 01       	subi45 $r8,#0x1
    5720:	4e 83 ff f6 	bnez $r8,570c <lfs_dir_find+0xbc>
    5724:	9c 32       	addi333 $r0,$r6,#0x2
    5726:	6a 03 00 09 	fmtsr $r0,$fs6
    572a:	d5 c3       	j8 56b0 <lfs_dir_find+0x60>
    572c:	20 05 00 00 	lbsi $r0,[$r10+#0x0]
    5730:	c0 4e       	beqz38 $r0,57cc <lfs_dir_find+0x17c>
    5732:	40 04 84 08 	slli $r0,$r9,#0x1
    5736:	6a 14 80 01 	fmfsr $r1,$fs9
    573a:	92 15       	srli45 $r0,#0x15
    573c:	b7 41       	swi450 $r10,[$r1]
    573e:	5a 00 02 05 	beqc $r0,#0x2,5748 <lfs_dir_find+0xf8>
    5742:	48 00 00 6f 	j 5820 <lfs_dir_find+0x1d0>
    5746:	92 00       	nop16
    5748:	6a 05 00 01 	fmfsr $r0,$fs10
    574c:	50 76 00 18 	addi $r7,$r12,#0x18
    5750:	40 94 80 02 	and $r9,$r9,$r0
    5754:	93 2a       	srli45 $r9,#0xa
    5756:	5a 93 ff 15 	beqc $r9,#0x3ff,5780 <lfs_dir_find+0x130>
    575a:	6a 44 00 01 	fmfsr $r4,$fs8
    575e:	84 08       	movi55 $r0,#0x8
    5760:	40 34 a8 08 	slli $r3,$r9,#0xa
    5764:	50 76 00 18 	addi $r7,$r12,#0x18
    5768:	6a 23 80 01 	fmfsr $r2,$fs7
    576c:	b6 1f       	swi450 $r0,[$sp]
    576e:	fe e7       	or33 $r3,$r4
    5770:	80 0d       	mov55 $r0,$r13
    5772:	80 2c       	mov55 $r1,$r12
    5774:	84 80       	movi55 $r4,#0x0
    5776:	80 a7       	mov55 $r5,$r7
    5778:	49 ff fe 52 	jal 541c <lfs_dir_getslice>
    577c:	4e 05 00 2a 	bltz $r0,57d0 <lfs_dir_find+0x180>
    5780:	b1 83       	addri36.sp $r6,#0xc
    5782:	45 c0 53 d0 	movi $fp,#0x53d0
    5786:	85 00       	movi55 $r8,#0x0
    5788:	d5 07       	j8 5796 <lfs_dir_find+0x146>
    578a:	92 00       	nop16
    578c:	4e 03 ff 92 	bnez $r0,56b0 <lfs_dir_find+0x60>
    5790:	00 16 00 17 	lbi $r1,[$r12+#0x17]
    5794:	c1 28       	beqz38 $r1,57e4 <lfs_dir_find+0x194>
    5796:	fa 3f       	movpi45 $r1,#0x2f
    5798:	80 0a       	mov55 $r0,$r10
    579a:	49 00 25 2f 	jal a1f8 <strchr>
    579e:	80 a8       	mov55 $r5,$r8
    57a0:	15 cf 80 00 	swi $fp,[$sp+#0x0]
    57a4:	f6 81       	swi37.sp $r6,[+#0x4]
    57a6:	40 57 00 1a 	cmovz $r5,$r14,$r0
    57aa:	80 2c       	mov55 $r1,$r12
    57ac:	80 0d       	mov55 $r0,$r13
    57ae:	80 47       	mov55 $r2,$r7
    57b0:	46 37 80 00 	sethi $r3,#0x78000
    57b4:	80 8b       	mov55 $r4,$r11
    57b6:	14 d3 00 00 	swi $r13,[$r6+#0x0]
    57ba:	14 a3 00 01 	swi $r10,[$r6+#0x4]
    57be:	14 b3 00 02 	swi $r11,[$r6+#0x8]
    57c2:	49 ff f5 67 	jal 4290 <lfs_dir_fetchmatch>
    57c6:	81 20       	mov55 $r9,$r0
    57c8:	4e 04 ff e2 	bgez $r0,578c <lfs_dir_find+0x13c>
    57cc:	80 09       	mov55 $r0,$r9
    57ce:	92 00       	nop16
    57d0:	ec 18       	addi10.sp #0x18
    57d2:	34 3f 90 02 	fldi.bi $fd3,[$sp],#0x8
    57d6:	34 4f 90 02 	fldi.bi $fd4,[$sp],#0x8
    57da:	34 5f 90 03 	fldi.bi $fd5,[$sp],#0xc
    57de:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    57e2:	dd 9e       	ret5 $lp
    57e4:	84 1e       	movi55 $r0,#-2
    57e6:	d5 f5       	j8 57d0 <lfs_dir_find+0x180>
    57e8:	80 0a       	mov55 $r0,$r10
    57ea:	44 10 3a 54 	movi $r1,#0x3a54
    57ee:	84 41       	movi55 $r2,#0x1
    57f0:	49 00 23 94 	jal 9f18 <memcmp>
    57f4:	4e 03 ff 76 	bnez $r0,56e0 <lfs_dir_find+0x90>
    57f8:	40 05 2c 00 	add $r0,$r10,$r11
    57fc:	6a 03 00 09 	fmtsr $r0,$fs6
    5800:	48 ff ff 58 	j 56b0 <lfs_dir_find+0x60>
    5804:	80 0a       	mov55 $r0,$r10
    5806:	44 10 3a 58 	movi $r1,#0x3a58
    580a:	84 42       	movi55 $r2,#0x2
    580c:	49 00 23 86 	jal 9f18 <memcmp>
    5810:	4e 03 ff 68 	bnez $r0,56e0 <lfs_dir_find+0x90>
    5814:	40 05 2c 00 	add $r0,$r10,$r11
    5818:	6a 03 00 09 	fmtsr $r0,$fs6
    581c:	48 ff ff 4a 	j 56b0 <lfs_dir_find+0x60>
    5820:	44 0f ff ec 	movi $r0,#-20
    5824:	d5 d6       	j8 57d0 <lfs_dir_find+0x180>
    5826:	92 00       	nop16

00005828 <lfs_dir_getinfo>:
    5828:	3a 6f a8 bc 	smw.adm $r6,[$sp],$r10,#0x2    ! {$r6~$r10, $lp}
    582c:	ef f0       	addi10.sp #-16
    582e:	81 03       	mov55 $r8,$r3
    5830:	5a 23 ff 48 	beqc $r2,#0x3ff,58c0 <lfs_dir_getinfo+0x98>
    5834:	04 40 00 1b 	lwi $r4,[$r0+#0x6c]
    5838:	40 61 28 08 	slli $r6,$r2,#0xa
    583c:	8c 81       	addi45 $r4,#0x1
    583e:	40 33 10 04 	or $r3,$r6,$r4
    5842:	54 21 83 ff 	andi $r2,$r3,#0x3ff
    5846:	b6 5f       	swi450 $r2,[$sp]
    5848:	46 27 80 ff 	sethi $r2,#0x780ff
    584c:	50 21 0c 00 	addi $r2,$r2,#0xc00
    5850:	84 80       	movi55 $r4,#0x0
    5852:	50 54 00 08 	addi $r5,$r8,#0x8
    5856:	81 20       	mov55 $r9,$r0
    5858:	50 a0 80 00 	addi $r10,$r1,#0x0
    585c:	49 ff fd e0 	jal 541c <lfs_dir_getslice>
    5860:	4e 05 00 24 	bltz $r0,58a8 <lfs_dir_getinfo+0x80>
    5864:	46 77 ff 00 	sethi $r7,#0x7ff00
    5868:	40 40 1c 02 	and $r4,$r0,$r7
    586c:	46 32 00 00 	sethi $r3,#0x20000
    5870:	92 94       	srli45 $r4,#0x14
    5872:	84 08       	movi55 $r0,#0x8
    5874:	46 27 00 ff 	sethi $r2,#0x700ff
    5878:	8c 68       	addi45 $r3,#0x8
    587a:	10 44 00 00 	sbi $r4,[$r8+#0x0]
    587e:	80 2a       	mov55 $r1,$r10
    5880:	b6 1f       	swi450 $r0,[$sp]
    5882:	50 21 0c 00 	addi $r2,$r2,#0xc00
    5886:	80 09       	mov55 $r0,$r9
    5888:	fe f7       	or33 $r3,$r6
    588a:	84 80       	movi55 $r4,#0x0
    588c:	b1 42       	addri36.sp $r5,#0x8
    588e:	49 ff fd c7 	jal 541c <lfs_dir_getslice>
    5892:	80 20       	mov55 $r1,$r0
    5894:	4e 05 00 0a 	bltz $r0,58a8 <lfs_dir_getinfo+0x80>
    5898:	ff c6       	and33 $r7,$r0
    589a:	92 f4       	srli45 $r7,#0x14
    589c:	5a 72 02 20 	beqc $r7,#0x202,58dc <lfs_dir_getinfo+0xb4>
    58a0:	84 00       	movi55 $r0,#0x0
    58a2:	5a 72 01 07 	beqc $r7,#0x201,58b0 <lfs_dir_getinfo+0x88>
    58a6:	92 00       	nop16
    58a8:	ec 10       	addi10.sp #0x10
    58aa:	3a 6f a8 84 	lmw.bim $r6,[$sp],$r10,#0x2    ! {$r6~$r10, $lp}
    58ae:	dd 9e       	ret5 $lp
    58b0:	54 10 83 ff 	andi $r1,$r1,#0x3ff
    58b4:	14 14 00 01 	swi $r1,[$r8+#0x4]
    58b8:	ec 10       	addi10.sp #0x10
    58ba:	3a 6f a8 84 	lmw.bim $r6,[$sp],$r10,#0x2    ! {$r6~$r10, $lp}
    58be:	dd 9e       	ret5 $lp
    58c0:	50 01 80 08 	addi $r0,$r3,#0x8
    58c4:	44 10 3a 50 	movi $r1,#0x3a50
    58c8:	49 00 24 ae 	jal a224 <strcpy>
    58cc:	84 02       	movi55 $r0,#0x2
    58ce:	10 04 00 00 	sbi $r0,[$r8+#0x0]
    58d2:	84 00       	movi55 $r0,#0x0
    58d4:	ec 10       	addi10.sp #0x10
    58d6:	3a 6f a8 84 	lmw.bim $r6,[$sp],$r10,#0x2    ! {$r6~$r10, $lp}
    58da:	dd 9e       	ret5 $lp
    58dc:	f0 03       	lwi37.sp $r0,[+#0xc]
    58de:	14 04 00 01 	swi $r0,[$r8+#0x4]
    58e2:	84 00       	movi55 $r0,#0x0
    58e4:	d5 e2       	j8 58a8 <lfs_dir_getinfo+0x80>
    58e6:	92 00       	nop16

000058e8 <lfs_dir_getread.constprop.33>:
    58e8:	3a 6f ba bc 	smw.adm $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    58ec:	ef f4       	addi10.sp #-12
    58ee:	81 40       	mov55 $r10,$r0
    58f0:	04 00 00 1a 	lwi $r0,[$r0+#0x68]
    58f4:	04 8f 80 0f 	lwi $r8,[$sp+#0x3c]
    58f8:	a0 07       	lwi333 $r0,[$r0+#0x1c]
    58fa:	80 e5       	mov55 $r7,$r5
    58fc:	88 a8       	add45 $r5,$r8
    58fe:	e2 05       	slt45 $r0,$r5
    5900:	e9 54       	bnezs8 59a8 <lfs_dir_getread.constprop.33+0xc0>
    5902:	4e 82 00 4e 	beqz $r8,599e <lfs_dir_getread.constprop.33+0xb6>
    5906:	46 bf ff 7f 	sethi $r11,#0xfff7f
    590a:	81 81       	mov55 $r12,$r1
    590c:	80 c2       	mov55 $r6,$r2
    590e:	81 c3       	mov55 $r14,$r3
    5910:	81 a4       	mov55 $r13,$r4
    5912:	87 9e       	movi55 $fp,#-2
    5914:	50 b5 8c 00 	addi $r11,$r11,#0xc00
    5918:	d5 20       	j8 5958 <lfs_dir_getread.constprop.33+0x70>
    591a:	92 00       	nop16
    591c:	04 55 00 1a 	lwi $r5,[$r10+#0x68]
    5920:	15 c3 00 00 	swi $fp,[$r6+#0x0]
    5924:	05 12 80 05 	lwi $r17,[$r5+#0x14]
    5928:	05 22 80 0a 	lwi $r18,[$r5+#0x28]
    592c:	51 08 ff ff 	addi $r16,$r17,#-1
    5930:	89 8e       	add45 $r16,$r14
    5932:	89 87       	add45 $r16,$r7
    5934:	40 58 44 97 	divr $r5,$r4,$r16,$r17
    5938:	41 13 c4 b7 	divr $r17,$r5,$r7,$r17
    593c:	8b 84       	sub45 $r16,$r4
    593e:	e3 d0       	slt45 $r18,$r16
    5940:	9b 3d       	sub333 $r4,$r7,$r5
    5942:	41 09 3c 1b 	cmovn $r16,$r18,$r15
    5946:	a9 31       	swi333 $r4,[$r6+#0x4]
    5948:	15 03 00 02 	swi $r16,[$r6+#0x8]
    594c:	b7 9f       	swi450 $r16,[$sp]
    594e:	a1 73       	lwi333 $r5,[$r6+#0xc]
    5950:	49 ff fd 66 	jal 541c <lfs_dir_getslice>
    5954:	4e 05 00 26 	bltz $r0,59a0 <lfs_dir_getread.constprop.33+0xb8>
    5958:	b4 86       	lwi450 $r4,[$r6]
    595a:	80 0a       	mov55 $r0,$r10
    595c:	80 2c       	mov55 $r1,$r12
    595e:	80 4b       	mov55 $r2,$r11
    5960:	80 6d       	mov55 $r3,$r13
    5962:	5a 4f fe dd 	bnec $r4,#-2,591c <lfs_dir_getread.constprop.33+0x34>
    5966:	a1 31       	lwi333 $r4,[$r6+#0x4]
    5968:	a1 72       	lwi333 $r5,[$r6+#0x8]
    596a:	e2 e4       	slt45 $r7,$r4
    596c:	88 a4       	add45 $r5,$r4
    596e:	41 03 94 06 	slt $r16,$r7,$r5
    5972:	4f 02 ff d5 	beqz $r16,591c <lfs_dir_getread.constprop.33+0x34>
    5976:	e9 d3       	bnezs8 591c <lfs_dir_getread.constprop.33+0x34>
    5978:	8a a7       	sub45 $r5,$r7
    597a:	e3 05       	slt45 $r8,$r5
    597c:	a0 b3       	lwi333 $r2,[$r6+#0xc]
    597e:	40 54 3c 1b 	cmovn $r5,$r8,$r15
    5982:	9a 7c       	sub333 $r1,$r7,$r4
    5984:	88 22       	add45 $r1,$r2
    5986:	f0 0e       	lwi37.sp $r0,[+#0x38]
    5988:	80 45       	mov55 $r2,$r5
    598a:	81 25       	mov55 $r9,$r5
    598c:	8b 05       	sub45 $r8,$r5
    598e:	49 00 22 e3 	jal 9f54 <memcpy>
    5992:	f0 0e       	lwi37.sp $r0,[+#0x38]
    5994:	88 e9       	add45 $r7,$r9
    5996:	88 09       	add45 $r0,$r9
    5998:	f0 8e       	swi37.sp $r0,[+#0x38]
    599a:	4e 83 ff df 	bnez $r8,5958 <lfs_dir_getread.constprop.33+0x70>
    599e:	84 00       	movi55 $r0,#0x0
    59a0:	ec 0c       	addi10.sp #0xc
    59a2:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    59a6:	dd 9e       	ret5 $lp
    59a8:	44 0f ff ac 	movi $r0,#-84
    59ac:	d5 fa       	j8 59a0 <lfs_dir_getread.constprop.33+0xb8>
    59ae:	92 00       	nop16

000059b0 <lfs_stat>:
    59b0:	3a 6f 9c bc 	smw.adm $r6,[$sp],$r7,#0x2    ! {$r6~$r7, $lp}
    59b4:	ef d4       	addi10.sp #-44
    59b6:	84 60       	movi55 $r3,#0x0
    59b8:	f1 81       	swi37.sp $r1,[+#0x4]
    59ba:	80 c2       	mov55 $r6,$r2
    59bc:	b0 42       	addri36.sp $r1,#0x8
    59be:	b0 81       	addri36.sp $r2,#0x4
    59c0:	50 70 00 00 	addi $r7,$r0,#0x0
    59c4:	49 ff fe 46 	jal 5650 <lfs_dir_find>
    59c8:	4e 05 00 0a 	bltz $r0,59dc <lfs_stat+0x2c>
    59cc:	40 20 30 08 	slli $r2,$r0,#0xc
    59d0:	b0 42       	addri36.sp $r1,#0x8
    59d2:	80 07       	mov55 $r0,$r7
    59d4:	92 56       	srli45 $r2,#0x16
    59d6:	80 66       	mov55 $r3,$r6
    59d8:	49 ff ff 28 	jal 5828 <lfs_dir_getinfo>
    59dc:	ec 2c       	addi10.sp #0x2c
    59de:	3a 6f 9c 84 	lmw.bim $r6,[$sp],$r7,#0x2    ! {$r6~$r7, $lp}
    59e2:	dd 9e       	ret5 $lp

000059e4 <lfs_mount>:
    59e4:	3a 6f ac bc 	smw.adm $r6,[$sp],$r11,#0x2    ! {$r6~$r11, $lp}
    59e8:	ef 9c       	addi10.sp #-100
    59ea:	80 e0       	mov55 $r7,$r0
    59ec:	49 ff f1 f6 	jal 3dd8 <lfs_init>
    59f0:	4e 03 00 c0 	bnez $r0,5b70 <lfs_mount+0x18c>
    59f4:	b0 10       	addri36.sp $r0,#0x40
    59f6:	84 20       	movi55 $r1,#0x0
    59f8:	44 20 00 20 	movi $r2,#0x20
    59fc:	49 00 22 e0 	jal 9fbc <memset>
    5a00:	46 97 ff ff 	sethi $r9,#0x7ffff
    5a04:	84 01       	movi55 $r0,#0x1
    5a06:	46 a0 ff 00 	sethi $r10,#0xff00
    5a0a:	46 b2 01 00 	sethi $r11,#0x20100
    5a0e:	f0 97       	swi37.sp $r0,[+#0x5c]
    5a10:	85 00       	movi55 $r8,#0x0
    5a12:	50 94 8c 00 	addi $r9,$r9,#0xc00
    5a16:	8d 48       	addi45 $r10,#0x8
    5a18:	8d 78       	addi45 $r11,#0x18
    5a1a:	f0 17       	lwi37.sp $r0,[+#0x5c]
    5a1c:	5a 07 ff 6c 	beqc $r0,#-1,5af4 <lfs_mount+0x110>
    5a20:	04 03 80 1a 	lwi $r0,[$r7+#0x68]
    5a24:	04 00 00 08 	lwi $r0,[$r0+#0x20]
    5a28:	92 01       	srli45 $r0,#0x1
    5a2a:	e3 00       	slt45 $r8,$r0
    5a2c:	4e f2 00 ba 	beqz $r15,5ba0 <lfs_mount+0x1bc>
    5a30:	51 0f 80 1c 	addi $r16,$sp,#0x1c
    5a34:	44 00 53 d0 	movi $r0,#0x53d0
    5a38:	45 10 3a 78 	movi $r17,#0x3a78
    5a3c:	b6 1f       	swi450 $r0,[$sp]
    5a3e:	15 1f 80 08 	swi $r17,[$sp+#0x20]
    5a42:	15 0f 80 01 	swi $r16,[$sp+#0x4]
    5a46:	86 28       	movi55 $r17,#0x8
    5a48:	80 07       	mov55 $r0,$r7
    5a4a:	b0 50       	addri36.sp $r1,#0x40
    5a4c:	b0 96       	addri36.sp $r2,#0x58
    5a4e:	80 69       	mov55 $r3,$r9
    5a50:	80 8a       	mov55 $r4,$r10
    5a52:	84 a0       	movi55 $r5,#0x0
    5a54:	f7 87       	swi37.sp $r7,[+#0x1c]
    5a56:	15 1f 80 09 	swi $r17,[$sp+#0x24]
    5a5a:	49 ff f4 1b 	jal 4290 <lfs_dir_fetchmatch>
    5a5e:	80 c0       	mov55 $r6,$r0
    5a60:	8d 01       	addi45 $r8,#0x1
    5a62:	4e 05 00 83 	bltz $r0,5b68 <lfs_mount+0x184>
    5a66:	c0 3b       	beqz38 $r0,5adc <lfs_mount+0xf8>
    5a68:	40 60 58 08 	slli $r6,$r0,#0x16
    5a6c:	90 d6       	srai45 $r6,#0x16
    5a6e:	5a 67 ff 37 	beqc $r6,#-1,5adc <lfs_mount+0xf8>
    5a72:	f0 11       	lwi37.sp $r0,[+#0x44]
    5a74:	f1 10       	lwi37.sp $r1,[+#0x40]
    5a76:	14 03 80 09 	swi $r0,[$r7+#0x24]
    5a7a:	fa 08       	movpi45 $r0,#0x18
    5a7c:	14 13 80 08 	swi $r1,[$r7+#0x20]
    5a80:	80 49       	mov55 $r2,$r9
    5a82:	b6 1f       	swi450 $r0,[$sp]
    5a84:	b0 50       	addri36.sp $r1,#0x40
    5a86:	80 07       	mov55 $r0,$r7
    5a88:	80 6b       	mov55 $r3,$r11
    5a8a:	84 80       	movi55 $r4,#0x0
    5a8c:	b1 4a       	addri36.sp $r5,#0x28
    5a8e:	49 ff fc c7 	jal 541c <lfs_dir_getslice>
    5a92:	80 c0       	mov55 $r6,$r0
    5a94:	4e 05 00 6a 	bltz $r0,5b68 <lfs_mount+0x184>
    5a98:	f0 0a       	lwi37.sp $r0,[+#0x28]
    5a9a:	40 10 40 09 	srli $r1,$r0,#0x10
    5a9e:	96 81       	zeh33 $r2,$r0
    5aa0:	5a 18 02 6c 	bnec $r1,#0x2,5b78 <lfs_mount+0x194>
    5aa4:	ca 6a       	bnez38 $r2,5b78 <lfs_mount+0x194>
    5aa6:	f0 0d       	lwi37.sp $r0,[+#0x34]
    5aa8:	c0 08       	beqz38 $r0,5ab8 <lfs_mount+0xd4>
    5aaa:	04 13 80 1b 	lwi $r1,[$r7+#0x6c]
    5aae:	e2 20       	slt45 $r1,$r0
    5ab0:	4e f3 00 7c 	bnez $r15,5ba8 <lfs_mount+0x1c4>
    5ab4:	14 03 80 1b 	swi $r0,[$r7+#0x6c]
    5ab8:	f0 0e       	lwi37.sp $r0,[+#0x38]
    5aba:	c0 08       	beqz38 $r0,5aca <lfs_mount+0xe6>
    5abc:	04 13 80 1c 	lwi $r1,[$r7+#0x70]
    5ac0:	e2 20       	slt45 $r1,$r0
    5ac2:	4e f3 00 9b 	bnez $r15,5bf8 <lfs_mount+0x214>
    5ac6:	14 03 80 1c 	swi $r0,[$r7+#0x70]
    5aca:	f0 0f       	lwi37.sp $r0,[+#0x3c]
    5acc:	c0 08       	beqz38 $r0,5adc <lfs_mount+0xf8>
    5ace:	04 13 80 1d 	lwi $r1,[$r7+#0x74]
    5ad2:	e2 20       	slt45 $r1,$r0
    5ad4:	4e f3 00 7e 	bnez $r15,5bd0 <lfs_mount+0x1ec>
    5ad8:	14 03 80 1d 	swi $r0,[$r7+#0x74]
    5adc:	80 07       	mov55 $r0,$r7
    5ade:	b0 50       	addri36.sp $r1,#0x40
    5ae0:	50 23 80 30 	addi $r2,$r7,#0x30
    5ae4:	49 ff fd 8c 	jal 55fc <lfs_dir_getgstate>
    5ae8:	80 c0       	mov55 $r6,$r0
    5aea:	c8 3f       	bnez38 $r0,5b68 <lfs_mount+0x184>
    5aec:	f0 16       	lwi37.sp $r0,[+#0x58]
    5aee:	5a 0f ff 96 	bnec $r0,#-1,5a1a <lfs_mount+0x36>
    5af2:	92 00       	nop16
    5af4:	04 03 80 08 	lwi $r0,[$r7+#0x20]
    5af8:	5a 07 ff 36 	beqc $r0,#-1,5b64 <lfs_mount+0x180>
    5afc:	04 03 80 09 	lwi $r0,[$r7+#0x24]
    5b00:	5a 07 ff 32 	beqc $r0,#-1,5b64 <lfs_mount+0x180>
    5b04:	04 03 80 0c 	lwi $r0,[$r7+#0x30]
    5b08:	4e 03 00 8c 	bnez $r0,5c20 <lfs_mount+0x23c>
    5b0c:	04 03 80 0d 	lwi $r0,[$r7+#0x34]
    5b10:	4e 03 00 88 	bnez $r0,5c20 <lfs_mount+0x23c>
    5b14:	04 03 80 0e 	lwi $r0,[$r7+#0x38]
    5b18:	4e 03 00 84 	bnez $r0,5c20 <lfs_mount+0x23c>
    5b1c:	04 13 80 0c 	lwi $r1,[$r7+#0x30]
    5b20:	04 43 80 1a 	lwi $r4,[$r7+#0x68]
    5b24:	40 20 fc 09 	srli $r2,$r1,#0x1f
    5b28:	a0 27       	lwi333 $r0,[$r4+#0x1c]
    5b2a:	88 22       	add45 $r1,$r2
    5b2c:	04 23 80 0b 	lwi $r2,[$r7+#0x2c]
    5b30:	14 13 80 0c 	swi $r1,[$r7+#0x30]
    5b34:	50 13 80 30 	addi $r1,$r7,#0x30
    5b38:	3b 00 c8 00 	lmw.bi $r16,[$r1],$r18,#0x0    ! {$r16~$r18}
    5b3c:	40 21 00 b7 	divr $r2,$r5,$r2,$r0
    5b40:	84 60       	movi55 $r3,#0x0
    5b42:	04 22 00 08 	lwi $r2,[$r4+#0x20]
    5b46:	50 13 80 3c 	addi $r1,$r7,#0x3c
    5b4a:	3b 00 c8 20 	smw.bi $r16,[$r1],$r18,#0x0    ! {$r16~$r18}
    5b4e:	84 00       	movi55 $r0,#0x0
    5b50:	14 53 80 15 	swi $r5,[$r7+#0x54]
    5b54:	14 33 80 16 	swi $r3,[$r7+#0x58]
    5b58:	14 33 80 17 	swi $r3,[$r7+#0x5c]
    5b5c:	14 23 80 18 	swi $r2,[$r7+#0x60]
    5b60:	d5 08       	j8 5b70 <lfs_mount+0x18c>
    5b62:	92 00       	nop16
    5b64:	44 6f ff ea 	movi $r6,#-22
    5b68:	80 07       	mov55 $r0,$r7
    5b6a:	49 ff ed 8b 	jal 3680 <lfs_deinit>
    5b6e:	80 06       	mov55 $r0,$r6
    5b70:	ec 64       	addi10.sp #0x64
    5b72:	3a 6f ac 84 	lmw.bim $r6,[$sp],$r11,#0x2    ! {$r6~$r11, $lp}
    5b76:	dd 9e       	ret5 $lp
    5b78:	96 01       	zeh33 $r0,$r0
    5b7a:	44 20 36 d4 	movi $r2,#0x36d4
    5b7e:	b6 5f       	swi450 $r2,[$sp]
    5b80:	f0 83       	swi37.sp $r0,[+#0xc]
    5b82:	44 20 0e 99 	movi $r2,#0xe99
    5b86:	44 00 01 38 	movi $r0,#0x138
    5b8a:	f0 84       	swi37.sp $r0,[+#0x10]
    5b8c:	f2 81       	swi37.sp $r2,[+#0x4]
    5b8e:	f1 82       	swi37.sp $r1,[+#0x8]
    5b90:	44 00 3a 84 	movi $r0,#0x3a84
    5b94:	49 ff e4 54 	jal 243c <printf>
    5b98:	44 6f ff ea 	movi $r6,#-22
    5b9c:	d5 e6       	j8 5b68 <lfs_mount+0x184>
    5b9e:	92 00       	nop16
    5ba0:	44 6f ff ac 	movi $r6,#-84
    5ba4:	d5 e2       	j8 5b68 <lfs_mount+0x184>
    5ba6:	92 00       	nop16
    5ba8:	44 20 36 d4 	movi $r2,#0x36d4
    5bac:	b6 5f       	swi450 $r2,[$sp]
    5bae:	f0 82       	swi37.sp $r0,[+#0x8]
    5bb0:	44 20 0e a2 	movi $r2,#0xea2
    5bb4:	44 00 01 38 	movi $r0,#0x138
    5bb8:	f0 84       	swi37.sp $r0,[+#0x10]
    5bba:	f2 81       	swi37.sp $r2,[+#0x4]
    5bbc:	14 1f 80 03 	swi $r1,[$sp+#0xc]
    5bc0:	44 00 3a ac 	movi $r0,#0x3aac
    5bc4:	49 ff e4 3c 	jal 243c <printf>
    5bc8:	44 6f ff ea 	movi $r6,#-22
    5bcc:	d5 ce       	j8 5b68 <lfs_mount+0x184>
    5bce:	92 00       	nop16
    5bd0:	44 20 36 d4 	movi $r2,#0x36d4
    5bd4:	b6 5f       	swi450 $r2,[$sp]
    5bd6:	f0 82       	swi37.sp $r0,[+#0x8]
    5bd8:	44 20 0e b8 	movi $r2,#0xeb8
    5bdc:	44 00 01 38 	movi $r0,#0x138
    5be0:	f0 84       	swi37.sp $r0,[+#0x10]
    5be2:	f2 81       	swi37.sp $r2,[+#0x4]
    5be4:	14 1f 80 03 	swi $r1,[$sp+#0xc]
    5be8:	44 00 3b 14 	movi $r0,#0x3b14
    5bec:	49 ff e4 28 	jal 243c <printf>
    5bf0:	44 6f ff ea 	movi $r6,#-22
    5bf4:	d5 ba       	j8 5b68 <lfs_mount+0x184>
    5bf6:	92 00       	nop16
    5bf8:	44 20 36 d4 	movi $r2,#0x36d4
    5bfc:	b6 5f       	swi450 $r2,[$sp]
    5bfe:	f0 82       	swi37.sp $r0,[+#0x8]
    5c00:	44 20 0e ad 	movi $r2,#0xead
    5c04:	44 00 01 38 	movi $r0,#0x138
    5c08:	f0 84       	swi37.sp $r0,[+#0x10]
    5c0a:	f2 81       	swi37.sp $r2,[+#0x4]
    5c0c:	14 1f 80 03 	swi $r1,[$sp+#0xc]
    5c10:	44 00 3a e0 	movi $r0,#0x3ae0
    5c14:	49 ff e4 14 	jal 243c <printf>
    5c18:	44 6f ff ea 	movi $r6,#-22
    5c1c:	48 ff ff a6 	j 5b68 <lfs_mount+0x184>
    5c20:	04 03 80 0e 	lwi $r0,[$r7+#0x38]
    5c24:	44 30 36 d4 	movi $r3,#0x36d4
    5c28:	04 23 80 0c 	lwi $r2,[$r7+#0x30]
    5c2c:	04 13 80 0d 	lwi $r1,[$r7+#0x34]
    5c30:	b6 7f       	swi450 $r3,[$sp]
    5c32:	f0 84       	swi37.sp $r0,[+#0x10]
    5c34:	44 30 0e d3 	movi $r3,#0xed3
    5c38:	44 00 01 38 	movi $r0,#0x138
    5c3c:	f0 85       	swi37.sp $r0,[+#0x14]
    5c3e:	f3 81       	swi37.sp $r3,[+#0x4]
    5c40:	f2 82       	swi37.sp $r2,[+#0x8]
    5c42:	f1 83       	swi37.sp $r1,[+#0xc]
    5c44:	44 00 3b 48 	movi $r0,#0x3b48
    5c48:	49 ff e3 fa 	jal 243c <printf>
    5c4c:	48 ff ff 68 	j 5b1c <lfs_mount+0x138>

00005c50 <lfs_fs_traverseraw>:
    5c50:	3a 6f ba bc 	smw.adm $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    5c54:	ef cc       	addi10.sp #-52
    5c56:	80 e0       	mov55 $r7,$r0
    5c58:	81 81       	mov55 $r12,$r1
    5c5a:	81 a2       	mov55 $r13,$r2
    5c5c:	84 20       	movi55 $r1,#0x0
    5c5e:	b0 04       	addri36.sp $r0,#0x10
    5c60:	fa 50       	movpi45 $r2,#0x20
    5c62:	81 c3       	mov55 $r14,$r3
    5c64:	46 92 00 00 	sethi $r9,#0x20000
    5c68:	49 00 21 aa 	jal 9fbc <memset>
    5c6c:	46 87 00 ff 	sethi $r8,#0x700ff
    5c70:	84 01       	movi55 $r0,#0x1
    5c72:	f0 8b       	swi37.sp $r0,[+#0x2c]
    5c74:	84 20       	movi55 $r1,#0x0
    5c76:	87 80       	movi55 $fp,#0x0
    5c78:	8d 28       	addi45 $r9,#0x8
    5c7a:	50 84 0c 00 	addi $r8,$r8,#0xc00
    5c7e:	46 b7 ff 00 	sethi $r11,#0x7ff00
    5c82:	f0 0b       	lwi37.sp $r0,[+#0x2c]
    5c84:	5a 07 ff 44 	beqc $r0,#-1,5d0c <lfs_fs_traverseraw+0xbc>
    5c88:	04 03 80 1a 	lwi $r0,[$r7+#0x68]
    5c8c:	04 00 00 08 	lwi $r0,[$r0+#0x20]
    5c90:	92 01       	srli45 $r0,#0x1
    5c92:	40 0e 00 06 	slt $r0,$fp,$r0
    5c96:	4e 02 00 95 	beqz $r0,5dc0 <lfs_fs_traverseraw+0x170>
    5c9a:	80 0d       	mov55 $r0,$r13
    5c9c:	dd 2c       	jral5 $r12
    5c9e:	c8 4b       	bnez38 $r0,5d34 <lfs_fs_traverseraw+0xe4>
    5ca0:	80 0d       	mov55 $r0,$r13
    5ca2:	f1 0b       	lwi37.sp $r1,[+#0x2c]
    5ca4:	dd 2c       	jral5 $r12
    5ca6:	c8 47       	bnez38 $r0,5d34 <lfs_fs_traverseraw+0xe4>
    5ca8:	b6 1f       	swi450 $r0,[$sp]
    5caa:	f0 81       	swi37.sp $r0,[+#0x4]
    5cac:	b0 44       	addri36.sp $r1,#0x10
    5cae:	80 07       	mov55 $r0,$r7
    5cb0:	b0 8a       	addri36.sp $r2,#0x28
    5cb2:	84 7f       	movi55 $r3,#-1
    5cb4:	84 9f       	movi55 $r4,#-1
    5cb6:	84 a0       	movi55 $r5,#0x0
    5cb8:	49 ff f2 ec 	jal 4290 <lfs_dir_fetchmatch>
    5cbc:	c8 3c       	bnez38 $r0,5d34 <lfs_fs_traverseraw+0xe4>
    5cbe:	02 0f 80 12 	lhi $r0,[$sp+#0x24]
    5cc2:	84 c0       	movi55 $r6,#0x0
    5cc4:	85 48       	movi55 $r10,#0x8
    5cc6:	c0 1e       	beqz38 $r0,5d02 <lfs_fs_traverseraw+0xb2>
    5cc8:	40 43 28 08 	slli $r4,$r6,#0xa
    5ccc:	40 32 24 04 	or $r3,$r4,$r9
    5cd0:	b7 5f       	swi450 $r10,[$sp]
    5cd2:	80 07       	mov55 $r0,$r7
    5cd4:	b0 44       	addri36.sp $r1,#0x10
    5cd6:	80 48       	mov55 $r2,$r8
    5cd8:	84 80       	movi55 $r4,#0x0
    5cda:	b1 42       	addri36.sp $r5,#0x8
    5cdc:	49 ff fb a0 	jal 541c <lfs_dir_getslice>
    5ce0:	4e 05 00 28 	bltz $r0,5d30 <lfs_fs_traverseraw+0xe0>
    5ce4:	40 40 2c 02 	and $r4,$r0,$r11
    5ce8:	92 94       	srli45 $r4,#0x14
    5cea:	5a 42 02 29 	beqc $r4,#0x202,5d3c <lfs_fs_traverseraw+0xec>
    5cee:	4e e2 00 04 	beqz $r14,5cf6 <lfs_fs_traverseraw+0xa6>
    5cf2:	5a 42 00 32 	beqc $r4,#0x200,5d56 <lfs_fs_traverseraw+0x106>
    5cf6:	8c c1       	addi45 $r6,#0x1
    5cf8:	02 4f 80 12 	lhi $r4,[$sp+#0x24]
    5cfc:	97 b1       	zeh33 $r6,$r6
    5cfe:	e2 c4       	slt45 $r6,$r4
    5d00:	e9 e4       	bnezs8 5cc8 <lfs_fs_traverseraw+0x78>
    5d02:	f1 0a       	lwi37.sp $r1,[+#0x28]
    5d04:	51 ce 00 01 	addi $fp,$fp,#0x1
    5d08:	5a 1f ff bd 	bnec $r1,#-1,5c82 <lfs_fs_traverseraw+0x32>
    5d0c:	04 63 80 0a 	lwi $r6,[$r7+#0x28]
    5d10:	c6 0e       	beqz38 $r6,5d2c <lfs_fs_traverseraw+0xdc>
    5d12:	46 b0 01 10 	sethi $r11,#0x110
    5d16:	44 a1 00 00 	movi $r10,#0x10000
    5d1a:	46 90 01 20 	sethi $r9,#0x120
    5d1e:	44 82 00 00 	movi $r8,#0x20000
    5d22:	a6 36       	lbi333 $r0,[$r6+#0x6]
    5d24:	5a 00 01 22 	beqc $r0,#0x1,5d68 <lfs_fs_traverseraw+0x118>
    5d28:	b4 c6       	lwi450 $r6,[$r6]
    5d2a:	ce fc       	bnez38 $r6,5d22 <lfs_fs_traverseraw+0xd2>
    5d2c:	84 00       	movi55 $r0,#0x0
    5d2e:	d5 03       	j8 5d34 <lfs_fs_traverseraw+0xe4>
    5d30:	5a 07 fe e3 	beqc $r0,#-2,5cf6 <lfs_fs_traverseraw+0xa6>
    5d34:	ec 34       	addi10.sp #0x34
    5d36:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    5d3a:	dd 9e       	ret5 $lp
    5d3c:	f4 03       	lwi37.sp $r4,[+#0xc]
    5d3e:	f3 02       	lwi37.sp $r3,[+#0x8]
    5d40:	c4 db       	beqz38 $r4,5cf6 <lfs_fs_traverseraw+0xa6>
    5d42:	14 df 80 00 	swi $r13,[$sp+#0x0]
    5d46:	80 07       	mov55 $r0,$r7
    5d48:	84 20       	movi55 $r1,#0x0
    5d4a:	80 47       	mov55 $r2,$r7
    5d4c:	80 ac       	mov55 $r5,$r12
    5d4e:	49 ff f7 cf 	jal 4cec <lfs_ctz_traverse.part.24>
    5d52:	c0 d2       	beqz38 $r0,5cf6 <lfs_fs_traverseraw+0xa6>
    5d54:	d5 f0       	j8 5d34 <lfs_fs_traverseraw+0xe4>
    5d56:	80 0d       	mov55 $r0,$r13
    5d58:	f1 02       	lwi37.sp $r1,[+#0x8]
    5d5a:	dd 2c       	jral5 $r12
    5d5c:	c8 ec       	bnez38 $r0,5d34 <lfs_fs_traverseraw+0xe4>
    5d5e:	80 0d       	mov55 $r0,$r13
    5d60:	f1 03       	lwi37.sp $r1,[+#0xc]
    5d62:	dd 2c       	jral5 $r12
    5d64:	c0 c9       	beqz38 $r0,5cf6 <lfs_fs_traverseraw+0xa6>
    5d66:	d5 e7       	j8 5d34 <lfs_fs_traverseraw+0xe4>
    5d68:	04 03 00 0c 	lwi $r0,[$r6+#0x30]
    5d6c:	40 10 2c 02 	and $r1,$r0,$r11
    5d70:	4c 15 00 16 	beq $r1,$r10,5d9c <lfs_fs_traverseraw+0x14c>
    5d74:	40 00 24 02 	and $r0,$r0,$r9
    5d78:	4c 04 7f d8 	bne $r0,$r8,5d28 <lfs_fs_traverseraw+0xd8>
    5d7c:	04 43 00 0d 	lwi $r4,[$r6+#0x34]
    5d80:	04 33 00 0e 	lwi $r3,[$r6+#0x38]
    5d84:	c4 d2       	beqz38 $r4,5d28 <lfs_fs_traverseraw+0xd8>
    5d86:	50 13 00 40 	addi $r1,$r6,#0x40
    5d8a:	14 df 80 00 	swi $r13,[$sp+#0x0]
    5d8e:	80 07       	mov55 $r0,$r7
    5d90:	80 47       	mov55 $r2,$r7
    5d92:	80 ac       	mov55 $r5,$r12
    5d94:	49 ff f7 ac 	jal 4cec <lfs_ctz_traverse.part.24>
    5d98:	c0 c8       	beqz38 $r0,5d28 <lfs_fs_traverseraw+0xd8>
    5d9a:	d5 cd       	j8 5d34 <lfs_fs_traverseraw+0xe4>
    5d9c:	04 43 00 0b 	lwi $r4,[$r6+#0x2c]
    5da0:	04 33 00 0a 	lwi $r3,[$r6+#0x28]
    5da4:	c4 e8       	beqz38 $r4,5d74 <lfs_fs_traverseraw+0x124>
    5da6:	50 13 00 40 	addi $r1,$r6,#0x40
    5daa:	80 ac       	mov55 $r5,$r12
    5dac:	80 47       	mov55 $r2,$r7
    5dae:	14 df 80 00 	swi $r13,[$sp+#0x0]
    5db2:	80 07       	mov55 $r0,$r7
    5db4:	49 ff f7 9c 	jal 4cec <lfs_ctz_traverse.part.24>
    5db8:	c8 be       	bnez38 $r0,5d34 <lfs_fs_traverseraw+0xe4>
    5dba:	04 03 00 0c 	lwi $r0,[$r6+#0x30]
    5dbe:	d5 db       	j8 5d74 <lfs_fs_traverseraw+0x124>
    5dc0:	44 0f ff ac 	movi $r0,#-84
    5dc4:	d5 b8       	j8 5d34 <lfs_fs_traverseraw+0xe4>
    5dc6:	92 00       	nop16

00005dc8 <lfs_alloc>:
    5dc8:	3a 6f a4 bc 	smw.adm $r6,[$sp],$r9,#0x2    ! {$r6~$r9, $lp}
    5dcc:	ef ec       	addi10.sp #-20
    5dce:	84 e1       	movi55 $r7,#0x1
    5dd0:	80 c0       	mov55 $r6,$r0
    5dd2:	81 01       	mov55 $r8,$r1
    5dd4:	85 20       	movi55 $r9,#0x0
    5dd6:	92 00       	nop16
    5dd8:	04 33 00 17 	lwi $r3,[$r6+#0x5c]
    5ddc:	05 13 00 16 	lwi $r17,[$r6+#0x58]
    5de0:	04 43 00 18 	lwi $r4,[$r6+#0x60]
    5de4:	d5 0e       	j8 5e00 <lfs_alloc+0x38>
    5de6:	8e 81       	subi45 $r4,#0x1
    5de8:	04 53 00 19 	lwi $r5,[$r6+#0x64]
    5dec:	14 23 00 17 	swi $r2,[$r6+#0x5c]
    5df0:	14 43 00 18 	swi $r4,[$r6+#0x60]
    5df4:	38 02 82 02 	lw $r0,[$r5+($r0<<#0x2)]
    5df8:	40 08 00 02 	and $r0,$r16,$r0
    5dfc:	c0 42       	beqz38 $r0,5e80 <lfs_alloc+0xb8>
    5dfe:	80 62       	mov55 $r3,$r2
    5e00:	9c 99       	addi333 $r2,$r3,#0x1
    5e02:	40 01 94 09 	srli $r0,$r3,#0x5
    5e06:	41 03 8c 0c 	sll $r16,$r7,$r3
    5e0a:	4c 38 ff ee 	bne $r3,$r17,5de6 <lfs_alloc+0x1e>
    5e0e:	c4 6d       	beqz38 $r4,5ee8 <lfs_alloc+0x120>
    5e10:	04 53 00 1a 	lwi $r5,[$r6+#0x68]
    5e14:	04 03 00 15 	lwi $r0,[$r6+#0x54]
    5e18:	04 22 80 0b 	lwi $r2,[$r5+#0x2c]
    5e1c:	04 52 80 08 	lwi $r5,[$r5+#0x20]
    5e20:	41 11 0c 08 	slli $r17,$r2,#0x3
    5e24:	e3 a4       	slt45 $r17,$r4
    5e26:	88 60       	add45 $r3,$r0
    5e28:	40 01 94 77 	divr $r0,$r3,$r3,$r5
    5e2c:	40 48 bc 1b 	cmovn $r4,$r17,$r15
    5e30:	44 10 00 00 	movi $r1,#0x0
    5e34:	14 33 00 15 	swi $r3,[$r6+#0x54]
    5e38:	14 43 00 16 	swi $r4,[$r6+#0x58]
    5e3c:	14 93 00 17 	swi $r9,[$r6+#0x5c]
    5e40:	04 03 00 19 	lwi $r0,[$r6+#0x64]
    5e44:	49 00 20 bc 	jal 9fbc <memset>
    5e48:	44 10 35 98 	movi $r1,#0x3598
    5e4c:	80 06       	mov55 $r0,$r6
    5e4e:	80 46       	mov55 $r2,$r6
    5e50:	84 61       	movi55 $r3,#0x1
    5e52:	49 ff fe ff 	jal 5c50 <lfs_fs_traverseraw>
    5e56:	84 20       	movi55 $r1,#0x0
    5e58:	c0 c0       	beqz38 $r0,5dd8 <lfs_alloc+0x10>
    5e5a:	04 43 00 1a 	lwi $r4,[$r6+#0x68]
    5e5e:	04 33 00 0b 	lwi $r3,[$r6+#0x2c]
    5e62:	a0 a7       	lwi333 $r2,[$r4+#0x1c]
    5e64:	04 42 00 08 	lwi $r4,[$r4+#0x20]
    5e68:	40 31 88 57 	divr $r3,$r2,$r3,$r2
    5e6c:	14 23 00 15 	swi $r2,[$r6+#0x54]
    5e70:	14 13 00 16 	swi $r1,[$r6+#0x58]
    5e74:	14 13 00 17 	swi $r1,[$r6+#0x5c]
    5e78:	14 43 00 18 	swi $r4,[$r6+#0x60]
    5e7c:	d5 32       	j8 5ee0 <lfs_alloc+0x118>
    5e7e:	92 00       	nop16
    5e80:	04 13 00 1a 	lwi $r1,[$r6+#0x68]
    5e84:	04 03 00 15 	lwi $r0,[$r6+#0x54]
    5e88:	04 20 80 08 	lwi $r2,[$r1+#0x20]
    5e8c:	88 60       	add45 $r3,$r0
    5e8e:	40 01 88 77 	divr $r0,$r3,$r3,$r2
    5e92:	b6 68       	swi450 $r3,[$r8]
    5e94:	04 03 00 17 	lwi $r0,[$r6+#0x5c]
    5e98:	04 43 00 16 	lwi $r4,[$r6+#0x58]
    5e9c:	4c 02 00 20 	beq $r0,$r4,5edc <lfs_alloc+0x114>
    5ea0:	40 10 14 09 	srli $r1,$r0,#0x5
    5ea4:	38 22 86 02 	lw $r2,[$r5+($r1<<#0x2)]
    5ea8:	84 21       	movi55 $r1,#0x1
    5eaa:	40 10 80 0c 	sll $r1,$r1,$r0
    5eae:	fe 56       	and33 $r1,$r2
    5eb0:	c1 16       	beqz38 $r1,5edc <lfs_alloc+0x114>
    5eb2:	04 23 00 18 	lwi $r2,[$r6+#0x60]
    5eb6:	86 01       	movi55 $r16,#0x1
    5eb8:	8e 41       	subi45 $r2,#0x1
    5eba:	d5 06       	j8 5ec6 <lfs_alloc+0xfe>
    5ebc:	38 12 86 02 	lw $r1,[$r5+($r1<<#0x2)]
    5ec0:	8e 41       	subi45 $r2,#0x1
    5ec2:	fe 5e       	and33 $r1,$r3
    5ec4:	c1 0c       	beqz38 $r1,5edc <lfs_alloc+0x114>
    5ec6:	8c 01       	addi45 $r0,#0x1
    5ec8:	40 10 14 09 	srli $r1,$r0,#0x5
    5ecc:	40 38 00 0c 	sll $r3,$r16,$r0
    5ed0:	14 23 00 18 	swi $r2,[$r6+#0x60]
    5ed4:	14 03 00 17 	swi $r0,[$r6+#0x5c]
    5ed8:	4c 02 7f f2 	bne $r0,$r4,5ebc <lfs_alloc+0xf4>
    5edc:	44 00 00 00 	movi $r0,#0x0
    5ee0:	ec 14       	addi10.sp #0x14
    5ee2:	3a 6f a4 84 	lmw.bim $r6,[$sp],$r9,#0x2    ! {$r6~$r9, $lp}
    5ee6:	dd 9e       	ret5 $lp
    5ee8:	04 03 00 15 	lwi $r0,[$r6+#0x54]
    5eec:	88 60       	add45 $r3,$r0
    5eee:	44 00 36 d4 	movi $r0,#0x36d4
    5ef2:	b6 1f       	swi450 $r0,[$sp]
    5ef4:	44 00 01 ef 	movi $r0,#0x1ef
    5ef8:	f0 81       	swi37.sp $r0,[+#0x4]
    5efa:	44 00 01 38 	movi $r0,#0x138
    5efe:	f0 83       	swi37.sp $r0,[+#0xc]
    5f00:	14 3f 80 02 	swi $r3,[$sp+#0x8]
    5f04:	44 00 3b 80 	movi $r0,#0x3b80
    5f08:	49 ff e2 9a 	jal 243c <printf>
    5f0c:	44 0f ff e4 	movi $r0,#-28
    5f10:	d5 e8       	j8 5ee0 <lfs_alloc+0x118>
    5f12:	92 00       	nop16

00005f14 <lfs_dir_alloc>:
    5f14:	3a 6f 9c bc 	smw.adm $r6,[$sp],$r7,#0x2    ! {$r6~$r7, $lp}
    5f18:	ef f4       	addi10.sp #-12
    5f1a:	80 c1       	mov55 $r6,$r1
    5f1c:	8c 24       	addi45 $r1,#0x4
    5f1e:	80 e0       	mov55 $r7,$r0
    5f20:	49 ff ff 54 	jal 5dc8 <lfs_alloc>
    5f24:	c8 28       	bnez38 $r0,5f74 <lfs_dir_alloc+0x60>
    5f26:	80 07       	mov55 $r0,$r7
    5f28:	80 26       	mov55 $r1,$r6
    5f2a:	49 ff ff 4f 	jal 5dc8 <lfs_alloc>
    5f2e:	c8 23       	bnez38 $r0,5f74 <lfs_dir_alloc+0x60>
    5f30:	a8 32       	swi333 $r0,[$r6+#0x8]
    5f32:	50 13 00 08 	addi $r1,$r6,#0x8
    5f36:	84 04       	movi55 $r0,#0x4
    5f38:	b6 3f       	swi450 $r1,[$sp]
    5f3a:	f0 81       	swi37.sp $r0,[+#0x4]
    5f3c:	84 20       	movi55 $r1,#0x0
    5f3e:	50 03 80 68 	addi $r0,$r7,#0x68
    5f42:	80 47       	mov55 $r2,$r7
    5f44:	84 64       	movi55 $r3,#0x4
    5f46:	b4 86       	lwi450 $r4,[$r6]
    5f48:	84 a0       	movi55 $r5,#0x0
    5f4a:	49 ff f0 af 	jal 40a8 <lfs_bd_read.isra.13>
    5f4e:	a0 72       	lwi333 $r1,[$r6+#0x8]
    5f50:	c8 16       	bnez38 $r0,5f7c <lfs_dir_alloc+0x68>
    5f52:	96 cc       	xlsb33 $r3,$r1
    5f54:	88 23       	add45 $r1,$r3
    5f56:	84 00       	movi55 $r0,#0x0
    5f58:	84 5f       	movi55 $r2,#-1
    5f5a:	a8 72       	swi333 $r1,[$r6+#0x8]
    5f5c:	84 24       	movi55 $r1,#0x4
    5f5e:	12 03 00 0a 	shi $r0,[$r6+#0x14]
    5f62:	10 03 00 16 	sbi $r0,[$r6+#0x16]
    5f66:	10 03 00 17 	sbi $r0,[$r6+#0x17]
    5f6a:	a8 73       	swi333 $r1,[$r6+#0xc]
    5f6c:	a8 b4       	swi333 $r2,[$r6+#0x10]
    5f6e:	a8 b6       	swi333 $r2,[$r6+#0x18]
    5f70:	a8 b7       	swi333 $r2,[$r6+#0x1c]
    5f72:	84 00       	movi55 $r0,#0x0
    5f74:	ec 0c       	addi10.sp #0xc
    5f76:	3a 6f 9c 84 	lmw.bim $r6,[$sp],$r7,#0x2    ! {$r6~$r7, $lp}
    5f7a:	dd 9e       	ret5 $lp
    5f7c:	5a 07 ac eb 	beqc $r0,#-84,5f52 <lfs_dir_alloc+0x3e>
    5f80:	ec 0c       	addi10.sp #0xc
    5f82:	3a 6f 9c 84 	lmw.bim $r6,[$sp],$r7,#0x2    ! {$r6~$r7, $lp}
    5f86:	dd 9e       	ret5 $lp

00005f88 <lfs_file_relocate>:
    5f88:	3a 6f ba bc 	smw.adm $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    5f8c:	ef dc       	addi10.sp #-36
    5f8e:	36 3f 80 06 	fsdi $fd3,[$sp+#0x18]
    5f92:	81 01       	mov55 $r8,$r1
    5f94:	04 10 80 0c 	lwi $r1,[$r1+#0x30]
    5f98:	42 10 d4 0b 	btst $r1,$r1,#0x15
    5f9c:	4e 12 00 a4 	beqz $r1,60e4 <lfs_file_relocate+0x15c>
    5fa0:	80 e0       	mov55 $r7,$r0
    5fa2:	50 00 00 68 	addi $r0,$r0,#0x68
    5fa6:	6a 03 00 09 	fmtsr $r0,$fs6
    5faa:	50 c4 00 40 	addi $r12,$r8,#0x40
    5fae:	50 af 80 13 	addi $r10,$sp,#0x13
    5fb2:	46 b0 01 00 	sethi $r11,#0x100
    5fb6:	51 c4 00 08 	addi $fp,$r8,#0x8
    5fba:	46 e2 01 00 	sethi $r14,#0x20100
    5fbe:	80 07       	mov55 $r0,$r7
    5fc0:	b0 45       	addri36.sp $r1,#0x14
    5fc2:	49 ff ff 03 	jal 5dc8 <lfs_alloc>
    5fc6:	c8 45       	bnez38 $r0,6050 <lfs_file_relocate+0xc8>
    5fc8:	04 03 80 1a 	lwi $r0,[$r7+#0x68]
    5fcc:	f1 05       	lwi37.sp $r1,[+#0x14]
    5fce:	49 ff f6 45 	jal 4c58 <lfs_bd_erase.isra.16>
    5fd2:	c8 45       	bnez38 $r0,605c <lfs_file_relocate+0xd4>
    5fd4:	04 34 00 0f 	lwi $r3,[$r8+#0x3c]
    5fd8:	c3 58       	beqz38 $r3,6088 <lfs_file_relocate+0x100>
    5fda:	84 c0       	movi55 $r6,#0x0
    5fdc:	85 21       	movi55 $r9,#0x1
    5fde:	50 d3 80 10 	addi $r13,$r7,#0x10
    5fe2:	d5 23       	j8 6028 <lfs_file_relocate+0xa0>
    5fe4:	02 44 00 02 	lhi $r4,[$r8+#0x4]
    5fe8:	80 07       	mov55 $r0,$r7
    5fea:	40 42 28 08 	slli $r4,$r4,#0xa
    5fee:	b7 5f       	swi450 $r10,[$sp]
    5ff0:	14 9f 80 01 	swi $r9,[$sp+#0x4]
    5ff4:	80 3c       	mov55 $r1,$fp
    5ff6:	80 4c       	mov55 $r2,$r12
    5ff8:	8a 66       	sub45 $r3,$r6
    5ffa:	40 42 38 04 	or $r4,$r4,$r14
    5ffe:	80 a6       	mov55 $r5,$r6
    6000:	49 ff fc 74 	jal 58e8 <lfs_dir_getread.constprop.33>
    6004:	c8 26       	bnez38 $r0,6050 <lfs_file_relocate+0xc8>
    6006:	b7 5f       	swi450 $r10,[$sp]
    6008:	14 9f 80 01 	swi $r9,[$sp+#0x4]
    600c:	80 07       	mov55 $r0,$r7
    600e:	80 2d       	mov55 $r1,$r13
    6010:	80 47       	mov55 $r2,$r7
    6012:	84 61       	movi55 $r3,#0x1
    6014:	f4 05       	lwi37.sp $r4,[+#0x14]
    6016:	80 a6       	mov55 $r5,$r6
    6018:	49 ff f7 a4 	jal 4f60 <lfs_bd_prog>
    601c:	c8 20       	bnez38 $r0,605c <lfs_file_relocate+0xd4>
    601e:	04 34 00 0f 	lwi $r3,[$r8+#0x3c]
    6022:	8c c1       	addi45 $r6,#0x1
    6024:	e2 c3       	slt45 $r6,$r3
    6026:	e8 31       	beqzs8 6088 <lfs_file_relocate+0x100>
    6028:	04 44 00 0c 	lwi $r4,[$r8+#0x30]
    602c:	40 42 2c 02 	and $r4,$r4,$r11
    6030:	cc da       	bnez38 $r4,5fe4 <lfs_file_relocate+0x5c>
    6032:	b7 5f       	swi450 $r10,[$sp]
    6034:	14 9f 80 01 	swi $r9,[$sp+#0x4]
    6038:	6a 03 00 01 	fmfsr $r0,$fs6
    603c:	80 2c       	mov55 $r1,$r12
    603e:	80 47       	mov55 $r2,$r7
    6040:	8a 66       	sub45 $r3,$r6
    6042:	04 44 00 0e 	lwi $r4,[$r8+#0x38]
    6046:	80 a6       	mov55 $r5,$r6
    6048:	49 ff f0 30 	jal 40a8 <lfs_bd_read.isra.13>
    604c:	c0 dd       	beqz38 $r0,6006 <lfs_file_relocate+0x7e>
    604e:	92 00       	nop16
    6050:	ec 18       	addi10.sp #0x18
    6052:	34 3f 90 03 	fldi.bi $fd3,[$sp],#0xc
    6056:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    605a:	dd 9e       	ret5 $lp
    605c:	5a 0f ac fa 	bnec $r0,#-84,6050 <lfs_file_relocate+0xc8>
    6060:	44 00 36 d4 	movi $r0,#0x36d4
    6064:	b6 1f       	swi450 $r0,[$sp]
    6066:	44 00 0a 4b 	movi $r0,#0xa4b
    606a:	f0 81       	swi37.sp $r0,[+#0x4]
    606c:	f0 05       	lwi37.sp $r0,[+#0x14]
    606e:	f0 82       	swi37.sp $r0,[+#0x8]
    6070:	44 00 01 38 	movi $r0,#0x138
    6074:	f0 83       	swi37.sp $r0,[+#0xc]
    6076:	44 00 3b a8 	movi $r0,#0x3ba8
    607a:	49 ff e1 e1 	jal 243c <printf>
    607e:	84 1f       	movi55 $r0,#-1
    6080:	a8 3c       	swi333 $r0,[$r7+#0x10]
    6082:	48 ff ff 9e 	j 5fbe <lfs_file_relocate+0x36>
    6086:	92 00       	nop16
    6088:	04 03 80 1a 	lwi $r0,[$r7+#0x68]
    608c:	04 13 80 07 	lwi $r1,[$r7+#0x1c]
    6090:	04 20 00 0a 	lwi $r2,[$r0+#0x28]
    6094:	04 04 00 13 	lwi $r0,[$r8+#0x4c]
    6098:	49 00 1f 5e 	jal 9f54 <memcpy>
    609c:	04 23 80 1a 	lwi $r2,[$r7+#0x68]
    60a0:	a0 7d       	lwi333 $r1,[$r7+#0x14]
    60a2:	a0 3e       	lwi333 $r0,[$r7+#0x18]
    60a4:	a0 fc       	lwi333 $r3,[$r7+#0x10]
    60a6:	14 34 00 10 	swi $r3,[$r8+#0x40]
    60aa:	14 14 00 11 	swi $r1,[$r8+#0x44]
    60ae:	14 04 00 12 	swi $r0,[$r8+#0x48]
    60b2:	44 10 00 ff 	movi $r1,#0xff
    60b6:	a0 3f       	lwi333 $r0,[$r7+#0x1c]
    60b8:	04 21 00 0a 	lwi $r2,[$r2+#0x28]
    60bc:	49 00 1f 80 	jal 9fbc <memset>
    60c0:	84 1f       	movi55 $r0,#-1
    60c2:	a8 3c       	swi333 $r0,[$r7+#0x10]
    60c4:	04 04 00 0c 	lwi $r0,[$r8+#0x30]
    60c8:	f1 05       	lwi37.sp $r1,[+#0x14]
    60ca:	42 00 44 08 	bset $r0,$r0,#0x11
    60ce:	14 04 00 0c 	swi $r0,[$r8+#0x30]
    60d2:	14 14 00 0e 	swi $r1,[$r8+#0x38]
    60d6:	84 00       	movi55 $r0,#0x0
    60d8:	ec 18       	addi10.sp #0x18
    60da:	34 3f 90 03 	fldi.bi $fd3,[$sp],#0xc
    60de:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    60e2:	dd 9e       	ret5 $lp
    60e4:	44 00 36 d4 	movi $r0,#0x36d4
    60e8:	44 10 0a 0c 	movi $r1,#0xa0c
    60ec:	44 20 7c 8c 	movi $r2,#0x7c8c
    60f0:	44 30 3a 5c 	movi $r3,#0x3a5c
    60f4:	49 00 1d 94 	jal 9c1c <__assert_func>
    60f8:	92 00       	nop16
    60fa:	92 00       	nop16

000060fc <lfs_file_write>:
    60fc:	3a 6f ba bc 	smw.adm $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    6100:	ef b4       	addi10.sp #-76
    6102:	36 3f 80 08 	fsdi $fd3,[$sp+#0x20]
    6106:	36 4f 80 0a 	fsdi $fd4,[$sp+#0x28]
    610a:	36 5f 80 0c 	fsdi $fd5,[$sp+#0x30]
    610e:	36 6f 80 0e 	fsdi $fd6,[$sp+#0x38]
    6112:	36 7f 80 10 	fsdi $fd7,[$sp+#0x40]
    6116:	05 00 80 0c 	lwi $r16,[$r1+#0x30]
    611a:	80 e1       	mov55 $r7,$r1
    611c:	42 48 54 0b 	btst $r4,$r16,#0x15
    6120:	4e 42 01 fc 	beqz $r4,6518 <lfs_file_write+0x41c>
    6124:	81 42       	mov55 $r10,$r2
    6126:	54 28 00 03 	andi $r2,$r16,#0x3
    612a:	5a 28 01 05 	bnec $r2,#0x1,6134 <lfs_file_write+0x38>
    612e:	48 00 02 01 	j 6530 <lfs_file_write+0x434>
    6132:	92 00       	nop16
    6134:	42 28 48 0b 	btst $r2,$r16,#0x12
    6138:	80 c0       	mov55 $r6,$r0
    613a:	6a 37 00 09 	fmtsr $r3,$fs14
    613e:	4e 23 01 63 	bnez $r2,6404 <lfs_file_write+0x308>
    6142:	92 00       	nop16
    6144:	54 08 08 00 	andi $r0,$r16,#0x800
    6148:	04 83 80 0d 	lwi $r8,[$r7+#0x34]
    614c:	c0 08       	beqz38 $r0,615c <lfs_file_write+0x60>
    614e:	04 03 80 0b 	lwi $r0,[$r7+#0x2c]
    6152:	e3 00       	slt45 $r8,$r0
    6154:	e8 04       	beqzs8 615c <lfs_file_write+0x60>
    6156:	14 03 80 0d 	swi $r0,[$r7+#0x34]
    615a:	81 00       	mov55 $r8,$r0
    615c:	6a 17 00 01 	fmfsr $r1,$fs14
    6160:	04 03 00 1c 	lwi $r0,[$r6+#0x70]
    6164:	88 28       	add45 $r1,$r8
    6166:	e2 01       	slt45 $r0,$r1
    6168:	4e f3 01 ca 	bnez $r15,64fc <lfs_file_write+0x400>
    616c:	42 08 44 0b 	btst $r0,$r16,#0x11
    6170:	c8 18       	bnez38 $r0,61a0 <lfs_file_write+0xa4>
    6172:	04 03 80 0b 	lwi $r0,[$r7+#0x2c]
    6176:	e2 08       	slt45 $r0,$r8
    6178:	e8 14       	beqzs8 61a0 <lfs_file_write+0xa4>
    617a:	14 03 80 0d 	swi $r0,[$r7+#0x34]
    617e:	85 20       	movi55 $r9,#0x0
    6180:	fd 03       	movd44 $r0,$r6
    6182:	50 2f 80 13 	addi $r2,$sp,#0x13
    6186:	84 61       	movi55 $r3,#0x1
    6188:	10 9f 80 13 	sbi $r9,[$sp+#0x13]
    618c:	49 ff ff b8 	jal 60fc <lfs_file_write>
    6190:	4e 05 01 16 	bltz $r0,63bc <lfs_file_write+0x2c0>
    6194:	04 03 80 0d 	lwi $r0,[$r7+#0x34]
    6198:	e2 08       	slt45 $r0,$r8
    619a:	e9 f3       	bnezs8 6180 <lfs_file_write+0x84>
    619c:	05 03 80 0c 	lwi $r16,[$r7+#0x30]
    61a0:	42 08 50 0b 	btst $r0,$r16,#0x14
    61a4:	4e 03 00 7c 	bnez $r0,629c <lfs_file_write+0x1a0>
    61a8:	6a 07 00 01 	fmfsr $r0,$fs14
    61ac:	c0 58       	beqz38 $r0,625c <lfs_file_write+0x160>
    61ae:	46 00 01 00 	sethi $r0,#0x100
    61b2:	6a 04 80 09 	fmtsr $r0,$fs9
    61b6:	50 03 80 38 	addi $r0,$r7,#0x38
    61ba:	6a 03 00 09 	fmtsr $r0,$fs6
    61be:	50 03 80 3c 	addi $r0,$r7,#0x3c
    61c2:	6a 03 80 09 	fmtsr $r0,$fs7
    61c6:	6a d7 00 01 	fmfsr $r13,$fs14
    61ca:	50 93 80 40 	addi $r9,$r7,#0x40
    61ce:	50 bf 80 1c 	addi $r11,$sp,#0x1c
    61d2:	92 00       	nop16
    61d4:	42 08 44 0b 	btst $r0,$r16,#0x11
    61d8:	c0 4a       	beqz38 $r0,626c <lfs_file_write+0x170>
    61da:	04 13 00 1a 	lwi $r1,[$r6+#0x68]
    61de:	04 53 80 0f 	lwi $r5,[$r7+#0x3c]
    61e2:	04 80 80 07 	lwi $r8,[$r1+#0x1c]
    61e6:	4c 54 01 17 	beq $r5,$r8,6414 <lfs_file_write+0x318>
    61ea:	04 43 80 0e 	lwi $r4,[$r7+#0x38]
    61ee:	8b 05       	sub45 $r8,$r5
    61f0:	40 06 a0 06 	slt $r0,$r13,$r8
    61f4:	40 86 80 1b 	cmovn $r8,$r13,$r0
    61f8:	d5 10       	j8 6218 <lfs_file_write+0x11c>
    61fa:	92 00       	nop16
    61fc:	5a 07 ac 04 	beqc $r0,#-84,6204 <lfs_file_write+0x108>
    6200:	48 00 00 d8 	j 63b0 <lfs_file_write+0x2b4>
    6204:	fd 03       	movd44 $r0,$r6
    6206:	49 ff fe c1 	jal 5f88 <lfs_file_relocate>
    620a:	92 00       	nop16
    620c:	4e 03 00 d2 	bnez $r0,63b0 <lfs_file_write+0x2b4>
    6210:	04 53 80 0f 	lwi $r5,[$r7+#0x3c]
    6214:	04 43 80 0e 	lwi $r4,[$r7+#0x38]
    6218:	b7 5f       	swi450 $r10,[$sp]
    621a:	14 8f 80 01 	swi $r8,[$sp+#0x4]
    621e:	80 06       	mov55 $r0,$r6
    6220:	80 29       	mov55 $r1,$r9
    6222:	80 46       	mov55 $r2,$r6
    6224:	84 61       	movi55 $r3,#0x1
    6226:	49 ff f6 9d 	jal 4f60 <lfs_bd_prog>
    622a:	c8 e9       	bnez38 $r0,61fc <lfs_file_write+0x100>
    622c:	04 13 80 0d 	lwi $r1,[$r7+#0x34]
    6230:	04 03 80 0f 	lwi $r0,[$r7+#0x3c]
    6234:	04 23 00 1a 	lwi $r2,[$r6+#0x68]
    6238:	88 28       	add45 $r1,$r8
    623a:	04 21 00 08 	lwi $r2,[$r2+#0x20]
    623e:	88 08       	add45 $r0,$r8
    6240:	14 13 80 0d 	swi $r1,[$r7+#0x34]
    6244:	14 03 80 0f 	swi $r0,[$r7+#0x3c]
    6248:	40 d6 a0 01 	sub $r13,$r13,$r8
    624c:	14 23 00 18 	swi $r2,[$r6+#0x60]
    6250:	89 48       	add45 $r10,$r8
    6252:	05 03 80 0c 	lwi $r16,[$r7+#0x30]
    6256:	4e d3 ff bf 	bnez $r13,61d4 <lfs_file_write+0xd8>
    625a:	92 00       	nop16
    625c:	43 08 4c 09 	bclr $r16,$r16,#0x13
    6260:	15 03 80 0c 	swi $r16,[$r7+#0x30]
    6264:	6a 07 00 01 	fmfsr $r0,$fs14
    6268:	48 00 00 aa 	j 63bc <lfs_file_write+0x2c0>
    626c:	6a 04 80 01 	fmfsr $r0,$fs9
    6270:	40 08 00 02 	and $r0,$r16,$r0
    6274:	4e 02 00 44 	beqz $r0,62fc <lfs_file_write+0x200>
    6278:	04 13 00 1a 	lwi $r1,[$r6+#0x68]
    627c:	04 53 80 0d 	lwi $r5,[$r7+#0x34]
    6280:	84 1e       	movi55 $r0,#-2
    6282:	14 03 80 0e 	swi $r0,[$r7+#0x38]
    6286:	14 53 80 0f 	swi $r5,[$r7+#0x3c]
    628a:	84 9e       	movi55 $r4,#-2
    628c:	43 08 44 08 	bset $r16,$r16,#0x11
    6290:	15 03 80 0c 	swi $r16,[$r7+#0x30]
    6294:	04 80 80 07 	lwi $r8,[$r1+#0x1c]
    6298:	d5 ab       	j8 61ee <lfs_file_write+0xf2>
    629a:	92 00       	nop16
    629c:	04 53 00 1a 	lwi $r5,[$r6+#0x68]
    62a0:	44 00 03 fe 	movi $r0,#0x3fe
    62a4:	04 42 80 0a 	lwi $r4,[$r5+#0x28]
    62a8:	05 23 80 0d 	lwi $r18,[$r7+#0x34]
    62ac:	a0 af       	lwi333 $r2,[$r5+#0x1c]
    62ae:	6a 37 00 01 	fmfsr $r3,$fs14
    62b2:	e2 04       	slt45 $r0,$r4
    62b4:	05 13 80 0b 	lwi $r17,[$r7+#0x2c]
    62b8:	40 02 3c 1a 	cmovz $r0,$r4,$r15
    62bc:	88 72       	add45 $r3,$r18
    62be:	92 43       	srli45 $r2,#0x3
    62c0:	e2 71       	slt45 $r3,$r17
    62c2:	40 11 00 06 	slt $r1,$r2,$r0
    62c6:	40 38 bc 1b 	cmovn $r3,$r17,$r15
    62ca:	40 01 04 1b 	cmovn $r0,$r2,$r1
    62ce:	e2 03       	slt45 $r0,$r3
    62d0:	4e f2 ff 6c 	beqz $r15,61a8 <lfs_file_write+0xac>
    62d4:	04 12 80 08 	lwi $r1,[$r5+#0x20]
    62d8:	80 06       	mov55 $r0,$r6
    62da:	15 23 80 0f 	swi $r18,[$r7+#0x3c]
    62de:	14 13 00 18 	swi $r1,[$r6+#0x60]
    62e2:	80 27       	mov55 $r1,$r7
    62e4:	49 ff fe 52 	jal 5f88 <lfs_file_relocate>
    62e8:	c8 64       	bnez38 $r0,63b0 <lfs_file_write+0x2b4>
    62ea:	05 03 80 0c 	lwi $r16,[$r7+#0x30]
    62ee:	43 08 50 09 	bclr $r16,$r16,#0x14
    62f2:	15 03 80 0c 	swi $r16,[$r7+#0x30]
    62f6:	48 ff ff 59 	j 61a8 <lfs_file_write+0xac>
    62fa:	92 00       	nop16
    62fc:	04 43 80 0d 	lwi $r4,[$r7+#0x34]
    6300:	4e 43 00 92 	bnez $r4,6424 <lfs_file_write+0x328>
    6304:	04 13 00 1a 	lwi $r1,[$r6+#0x68]
    6308:	04 00 80 08 	lwi $r0,[$r1+#0x20]
    630c:	14 03 00 18 	swi $r0,[$r6+#0x60]
    6310:	30 83 80 0d 	flsi $fs8,[$r7+#0x34]
    6314:	04 e3 80 0e 	lwi $r14,[$r7+#0x38]
    6318:	51 c3 00 68 	addi $fp,$r6,#0x68
    631c:	6a 04 00 01 	fmfsr $r0,$fs8
    6320:	8e 01       	subi45 $r0,#0x1
    6322:	6a 05 80 09 	fmtsr $r0,$fs11
    6326:	80 06       	mov55 $r0,$r6
    6328:	b0 45       	addri36.sp $r1,#0x14
    632a:	49 ff fd 4f 	jal 5dc8 <lfs_alloc>
    632e:	c8 41       	bnez38 $r0,63b0 <lfs_file_write+0x2b4>
    6330:	04 03 00 1a 	lwi $r0,[$r6+#0x68]
    6334:	f1 05       	lwi37.sp $r1,[+#0x14]
    6336:	49 ff f4 91 	jal 4c58 <lfs_bd_erase.isra.16>
    633a:	c8 4f       	bnez38 $r0,63d8 <lfs_file_write+0x2dc>
    633c:	6a 04 00 01 	fmfsr $r0,$fs8
    6340:	4e 02 00 e2 	beqz $r0,6504 <lfs_file_write+0x408>
    6344:	b0 46       	addri36.sp $r1,#0x18
    6346:	04 03 00 1a 	lwi $r0,[$r6+#0x68]
    634a:	32 bf 80 06 	fssi $fs11,[$sp+#0x18]
    634e:	49 ff f4 ab 	jal 4ca4 <lfs_ctz_index.isra.23>
    6352:	92 00       	nop16
    6354:	04 13 00 1a 	lwi $r1,[$r6+#0x68]
    6358:	05 0f 80 06 	lwi $r16,[$sp+#0x18]
    635c:	a0 8f       	lwi333 $r2,[$r1+#0x1c]
    635e:	50 58 00 01 	addi $r5,$r16,#0x1
    6362:	f5 86       	swi37.sp $r5,[+#0x18]
    6364:	4c 51 00 7d 	beq $r5,$r2,645e <lfs_file_write+0x362>
    6368:	4e 52 00 c0 	beqz $r5,64e8 <lfs_file_write+0x3ec>
    636c:	85 00       	movi55 $r8,#0x0
    636e:	85 81       	movi55 $r12,#0x1
    6370:	d5 12       	j8 6394 <lfs_file_write+0x298>
    6372:	b7 7f       	swi450 $r11,[$sp]
    6374:	14 cf 80 01 	swi $r12,[$sp+#0x4]
    6378:	80 06       	mov55 $r0,$r6
    637a:	80 29       	mov55 $r1,$r9
    637c:	80 46       	mov55 $r2,$r6
    637e:	84 61       	movi55 $r3,#0x1
    6380:	f4 05       	lwi37.sp $r4,[+#0x14]
    6382:	80 a8       	mov55 $r5,$r8
    6384:	49 ff f5 ee 	jal 4f60 <lfs_bd_prog>
    6388:	c8 28       	bnez38 $r0,63d8 <lfs_file_write+0x2dc>
    638a:	f5 06       	lwi37.sp $r5,[+#0x18]
    638c:	8d 01       	addi45 $r8,#0x1
    638e:	e3 05       	slt45 $r8,$r5
    6390:	4e f2 00 aa 	beqz $r15,64e4 <lfs_file_write+0x3e8>
    6394:	40 32 a0 01 	sub $r3,$r5,$r8
    6398:	b7 7f       	swi450 $r11,[$sp]
    639a:	14 cf 80 01 	swi $r12,[$sp+#0x4]
    639e:	80 1c       	mov55 $r0,$fp
    63a0:	84 20       	movi55 $r1,#0x0
    63a2:	80 46       	mov55 $r2,$r6
    63a4:	80 8e       	mov55 $r4,$r14
    63a6:	80 a8       	mov55 $r5,$r8
    63a8:	49 ff ee 80 	jal 40a8 <lfs_bd_read.isra.13>
    63ac:	c0 e3       	beqz38 $r0,6372 <lfs_file_write+0x276>
    63ae:	92 00       	nop16
    63b0:	04 13 80 0c 	lwi $r1,[$r7+#0x30]
    63b4:	42 10 cc 08 	bset $r1,$r1,#0x13
    63b8:	14 13 80 0c 	swi $r1,[$r7+#0x30]
    63bc:	ec 20       	addi10.sp #0x20
    63be:	34 3f 90 02 	fldi.bi $fd3,[$sp],#0x8
    63c2:	34 4f 90 02 	fldi.bi $fd4,[$sp],#0x8
    63c6:	34 5f 90 02 	fldi.bi $fd5,[$sp],#0x8
    63ca:	34 6f 90 02 	fldi.bi $fd6,[$sp],#0x8
    63ce:	34 7f 90 03 	fldi.bi $fd7,[$sp],#0xc
    63d2:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    63d6:	dd 9e       	ret5 $lp
    63d8:	5a 0f ac ec 	bnec $r0,#-84,63b0 <lfs_file_write+0x2b4>
    63dc:	44 00 36 d4 	movi $r0,#0x36d4
    63e0:	b6 1f       	swi450 $r0,[$sp]
    63e2:	44 00 09 1b 	movi $r0,#0x91b
    63e6:	f0 81       	swi37.sp $r0,[+#0x4]
    63e8:	f0 05       	lwi37.sp $r0,[+#0x14]
    63ea:	f0 82       	swi37.sp $r0,[+#0x8]
    63ec:	44 00 01 38 	movi $r0,#0x138
    63f0:	f0 83       	swi37.sp $r0,[+#0xc]
    63f2:	44 00 3b a8 	movi $r0,#0x3ba8
    63f6:	49 ff e0 23 	jal 243c <printf>
    63fa:	84 1f       	movi55 $r0,#-1
    63fc:	14 03 80 10 	swi $r0,[$r7+#0x40]
    6400:	48 ff ff 93 	j 6326 <lfs_file_write+0x22a>
    6404:	49 00 00 a2 	jal 6548 <lfs_file_flush>
    6408:	c8 da       	bnez38 $r0,63bc <lfs_file_write+0x2c0>
    640a:	05 03 80 0c 	lwi $r16,[$r7+#0x30]
    640e:	48 ff fe 9b 	j 6144 <lfs_file_write+0x48>
    6412:	92 00       	nop16
    6414:	6a 04 80 01 	fmfsr $r0,$fs9
    6418:	40 08 00 02 	and $r0,$r16,$r0
    641c:	4e 02 ff 76 	beqz $r0,6308 <lfs_file_write+0x20c>
    6420:	48 ff ff 2e 	j 627c <lfs_file_write+0x180>
    6424:	32 7f 80 00 	fssi $fs7,[$sp+#0x0]
    6428:	6a 53 00 01 	fmfsr $r5,$fs6
    642c:	80 06       	mov55 $r0,$r6
    642e:	80 29       	mov55 $r1,$r9
    6430:	04 23 80 0a 	lwi $r2,[$r7+#0x28]
    6434:	04 33 80 0b 	lwi $r3,[$r7+#0x2c]
    6438:	8e 81       	subi45 $r4,#0x1
    643a:	49 ff f4 97 	jal 4d68 <lfs_ctz_find.constprop.32>
    643e:	c8 b9       	bnez38 $r0,63b0 <lfs_file_write+0x2b4>
    6440:	04 23 00 1a 	lwi $r2,[$r6+#0x68]
    6444:	04 03 80 13 	lwi $r0,[$r7+#0x4c]
    6448:	44 10 00 ff 	movi $r1,#0xff
    644c:	04 21 00 0a 	lwi $r2,[$r2+#0x28]
    6450:	49 00 1d b6 	jal 9fbc <memset>
    6454:	84 1f       	movi55 $r0,#-1
    6456:	14 03 80 10 	swi $r0,[$r7+#0x40]
    645a:	48 ff ff 55 	j 6304 <lfs_file_write+0x208>
    645e:	9c 41       	addi333 $r1,$r0,#0x1
    6460:	40 00 80 12 	bitc $r0,$r1,$r0
    6464:	42 00 00 07 	clz $r0,$r0
    6468:	52 00 00 1f 	subri $r0,$r0,#0x1f
    646c:	6a 06 80 09 	fmtsr $r0,$fs13
    6470:	8c 01       	addi45 $r0,#0x1
    6472:	6a 05 00 09 	fmtsr $r0,$fs10
    6476:	84 04       	movi55 $r0,#0x4
    6478:	6a 06 00 09 	fmtsr $r0,$fs12
    647c:	14 ef 80 07 	swi $r14,[$sp+#0x1c]
    6480:	85 00       	movi55 $r8,#0x0
    6482:	92 00       	nop16
    6484:	40 c4 08 08 	slli $r12,$r8,#0x2
    6488:	f4 05       	lwi37.sp $r4,[+#0x14]
    648a:	b7 7f       	swi450 $r11,[$sp]
    648c:	32 cf 80 01 	fssi $fs12,[$sp+#0x4]
    6490:	80 06       	mov55 $r0,$r6
    6492:	80 29       	mov55 $r1,$r9
    6494:	80 46       	mov55 $r2,$r6
    6496:	84 61       	movi55 $r3,#0x1
    6498:	80 ac       	mov55 $r5,$r12
    649a:	49 ff f5 63 	jal 4f60 <lfs_bd_prog>
    649e:	f4 07       	lwi37.sp $r4,[+#0x1c]
    64a0:	4e 03 ff 9c 	bnez $r0,63d8 <lfs_file_write+0x2dc>
    64a4:	6a 06 80 01 	fmfsr $r0,$fs13
    64a8:	4c 04 00 0e 	beq $r0,$r8,64c4 <lfs_file_write+0x3c8>
    64ac:	b7 7f       	swi450 $r11,[$sp]
    64ae:	32 cf 80 01 	fssi $fs12,[$sp+#0x4]
    64b2:	80 1c       	mov55 $r0,$fp
    64b4:	84 20       	movi55 $r1,#0x0
    64b6:	80 46       	mov55 $r2,$r6
    64b8:	84 64       	movi55 $r3,#0x4
    64ba:	80 ac       	mov55 $r5,$r12
    64bc:	49 ff ed f6 	jal 40a8 <lfs_bd_read.isra.13>
    64c0:	4e 03 ff 78 	bnez $r0,63b0 <lfs_file_write+0x2b4>
    64c4:	6a 05 00 01 	fmfsr $r0,$fs10
    64c8:	8d 01       	addi45 $r8,#0x1
    64ca:	e3 00       	slt45 $r8,$r0
    64cc:	e9 dc       	bnezs8 6484 <lfs_file_write+0x388>
    64ce:	6a 05 00 01 	fmfsr $r0,$fs10
    64d2:	f4 05       	lwi37.sp $r4,[+#0x14]
    64d4:	95 42       	slli333 $r5,$r0,#0x2
    64d6:	14 43 80 0e 	swi $r4,[$r7+#0x38]
    64da:	14 53 80 0f 	swi $r5,[$r7+#0x3c]
    64de:	04 13 00 1a 	lwi $r1,[$r6+#0x68]
    64e2:	d5 09       	j8 64f4 <lfs_file_write+0x3f8>
    64e4:	04 13 00 1a 	lwi $r1,[$r6+#0x68]
    64e8:	04 4f 80 05 	lwi $r4,[$sp+#0x14]
    64ec:	14 43 80 0e 	swi $r4,[$r7+#0x38]
    64f0:	14 53 80 0f 	swi $r5,[$r7+#0x3c]
    64f4:	05 03 80 0c 	lwi $r16,[$r7+#0x30]
    64f8:	48 ff fe ca 	j 628c <lfs_file_write+0x190>
    64fc:	44 0f ff e5 	movi $r0,#-27
    6500:	48 ff ff 5e 	j 63bc <lfs_file_write+0x2c0>
    6504:	f4 05       	lwi37.sp $r4,[+#0x14]
    6506:	14 43 80 0e 	swi $r4,[$r7+#0x38]
    650a:	32 83 80 0f 	fssi $fs8,[$r7+#0x3c]
    650e:	04 13 00 1a 	lwi $r1,[$r6+#0x68]
    6512:	84 a0       	movi55 $r5,#0x0
    6514:	d5 f0       	j8 64f4 <lfs_file_write+0x3f8>
    6516:	92 00       	nop16
    6518:	44 00 36 d4 	movi $r0,#0x36d4
    651c:	44 10 0b 3b 	movi $r1,#0xb3b
    6520:	44 20 7b e8 	movi $r2,#0x7be8
    6524:	44 30 3a 5c 	movi $r3,#0x3a5c
    6528:	49 00 1b 7a 	jal 9c1c <__assert_func>
    652c:	92 00       	nop16
    652e:	92 00       	nop16
    6530:	44 00 36 d4 	movi $r0,#0x36d4
    6534:	44 10 0b 3c 	movi $r1,#0xb3c
    6538:	44 20 7b e8 	movi $r2,#0x7be8
    653c:	44 30 3b cc 	movi $r3,#0x3bcc
    6540:	49 00 1b 6e 	jal 9c1c <__assert_func>
    6544:	92 00       	nop16
    6546:	92 00       	nop16

00006548 <lfs_file_flush>:
    6548:	3a 6f b0 bc 	smw.adm $r6,[$sp],$r12,#0x2    ! {$r6~$r12, $lp}
    654c:	ef 98       	addi10.sp #-104
    654e:	80 c1       	mov55 $r6,$r1
    6550:	04 10 80 0c 	lwi $r1,[$r1+#0x30]
    6554:	80 e0       	mov55 $r7,$r0
    6556:	42 00 d4 0b 	btst $r0,$r1,#0x15
    655a:	4e 02 00 a7 	beqz $r0,66a8 <lfs_file_flush+0x160>
    655e:	42 00 c8 0b 	btst $r0,$r1,#0x12
    6562:	c0 09       	beqz38 $r0,6574 <lfs_file_flush+0x2c>
    6564:	42 00 d0 0b 	btst $r0,$r1,#0x14
    6568:	4e 02 00 70 	beqz $r0,6648 <lfs_file_flush+0x100>
    656c:	42 10 c8 09 	bclr $r1,$r1,#0x12
    6570:	14 13 00 0c 	swi $r1,[$r6+#0x30]
    6574:	42 00 c4 0b 	btst $r0,$r1,#0x11
    6578:	84 60       	movi55 $r3,#0x0
    657a:	c0 48       	beqz38 $r0,660a <lfs_file_flush+0xc2>
    657c:	42 00 d0 0b 	btst $r0,$r1,#0x14
    6580:	04 93 00 0d 	lwi $r9,[$r6+#0x34]
    6584:	c8 48       	bnez38 $r0,6614 <lfs_file_flush+0xcc>
    6586:	84 20       	movi55 $r1,#0x0
    6588:	44 20 00 54 	movi $r2,#0x54
    658c:	b0 05       	addri36.sp $r0,#0x14
    658e:	49 00 1d 17 	jal 9fbc <memset>
    6592:	84 1f       	movi55 $r0,#-1
    6594:	04 23 00 0b 	lwi $r2,[$r6+#0x2c]
    6598:	04 33 00 0a 	lwi $r3,[$r6+#0x28]
    659c:	3b 03 cc 00 	lmw.bi $r16,[$r7],$r19,#0x0    ! {$r16~$r19}
    65a0:	b6 07       	swi450 $r0,[$r7]
    65a2:	04 13 00 0d 	lwi $r1,[$r6+#0x34]
    65a6:	04 43 00 0b 	lwi $r4,[$r6+#0x2c]
    65aa:	f2 90       	swi37.sp $r2,[+#0x40]
    65ac:	46 20 02 00 	sethi $r2,#0x200
    65b0:	b0 15       	addri36.sp $r0,#0x54
    65b2:	8c 41       	addi45 $r2,#0x1
    65b4:	40 10 90 06 	slt $r1,$r1,$r4
    65b8:	f3 8f       	swi37.sp $r3,[+#0x3c]
    65ba:	f2 91       	swi37.sp $r2,[+#0x44]
    65bc:	14 9f 80 12 	swi $r9,[$sp+#0x48]
    65c0:	3b 00 4c 20 	smw.bi $r16,[$r0],$r19,#0x0    ! {$r16~$r19}
    65c4:	c1 48       	beqz38 $r1,6654 <lfs_file_flush+0x10c>
    65c6:	85 1f       	movi55 $r8,#-1
    65c8:	d5 16       	j8 65f4 <lfs_file_flush+0xac>
    65ca:	80 07       	mov55 $r0,$r7
    65cc:	80 26       	mov55 $r1,$r6
    65ce:	50 2f 80 13 	addi $r2,$sp,#0x13
    65d2:	84 61       	movi55 $r3,#0x1
    65d4:	49 ff fd 94 	jal 60fc <lfs_file_write>
    65d8:	4e 05 00 18 	bltz $r0,6608 <lfs_file_flush+0xc0>
    65dc:	b4 07       	lwi450 $r0,[$r7]
    65de:	5a 07 ff 05 	beqc $r0,#-1,65e8 <lfs_file_flush+0xa0>
    65e2:	14 8f 80 15 	swi $r8,[$sp+#0x54]
    65e6:	b7 07       	swi450 $r8,[$r7]
    65e8:	04 03 00 0d 	lwi $r0,[$r6+#0x34]
    65ec:	04 13 00 0b 	lwi $r1,[$r6+#0x2c]
    65f0:	e2 01       	slt45 $r0,$r1
    65f2:	e8 31       	beqzs8 6654 <lfs_file_flush+0x10c>
    65f4:	80 07       	mov55 $r0,$r7
    65f6:	b0 45       	addri36.sp $r1,#0x14
    65f8:	50 2f 80 13 	addi $r2,$sp,#0x13
    65fc:	44 30 00 01 	movi $r3,#0x1
    6600:	49 00 00 60 	jal 66c0 <lfs_file_read>
    6604:	4e 04 ff e3 	bgez $r0,65ca <lfs_file_flush+0x82>
    6608:	80 60       	mov55 $r3,$r0
    660a:	80 03       	mov55 $r0,$r3
    660c:	ec 68       	addi10.sp #0x68
    660e:	3a 6f b0 84 	lmw.bim $r6,[$sp],$r12,#0x2    ! {$r6~$r12, $lp}
    6612:	dd 9e       	ret5 $lp
    6614:	04 23 00 0b 	lwi $r2,[$r6+#0x2c]
    6618:	e2 49       	slt45 $r2,$r9
    661a:	40 24 bc 1b 	cmovn $r2,$r9,$r15
    661e:	80 02       	mov55 $r0,$r2
    6620:	42 10 c4 09 	bclr $r1,$r1,#0x11
    6624:	04 23 00 0e 	lwi $r2,[$r6+#0x38]
    6628:	42 10 c0 08 	bset $r1,$r1,#0x10
    662c:	84 60       	movi55 $r3,#0x0
    662e:	14 03 00 0b 	swi $r0,[$r6+#0x2c]
    6632:	14 23 00 0a 	swi $r2,[$r6+#0x28]
    6636:	80 03       	mov55 $r0,$r3
    6638:	14 13 00 0c 	swi $r1,[$r6+#0x30]
    663c:	14 93 00 0d 	swi $r9,[$r6+#0x34]
    6640:	ec 68       	addi10.sp #0x68
    6642:	3a 6f b0 84 	lmw.bim $r6,[$sp],$r12,#0x2    ! {$r6~$r12, $lp}
    6646:	dd 9e       	ret5 $lp
    6648:	84 1f       	movi55 $r0,#-1
    664a:	14 03 00 10 	swi $r0,[$r6+#0x40]
    664e:	48 ff ff 8f 	j 656c <lfs_file_flush+0x24>
    6652:	92 00       	nop16
    6654:	50 83 00 40 	addi $r8,$r6,#0x40
    6658:	44 c0 36 d4 	movi $r12,#0x36d4
    665c:	44 b0 0a 98 	movi $r11,#0xa98
    6660:	44 a0 01 38 	movi $r10,#0x138
    6664:	d5 16       	j8 6690 <lfs_file_flush+0x148>
    6666:	92 00       	nop16
    6668:	5a 0f ac d0 	bnec $r0,#-84,6608 <lfs_file_flush+0xc0>
    666c:	04 03 00 0e 	lwi $r0,[$r6+#0x38]
    6670:	f0 82       	swi37.sp $r0,[+#0x8]
    6672:	14 cf 80 00 	swi $r12,[$sp+#0x0]
    6676:	14 bf 80 01 	swi $r11,[$sp+#0x4]
    667a:	14 af 80 03 	swi $r10,[$sp+#0xc]
    667e:	44 00 3b a8 	movi $r0,#0x3ba8
    6682:	49 ff de dd 	jal 243c <printf>
    6686:	80 07       	mov55 $r0,$r7
    6688:	80 26       	mov55 $r1,$r6
    668a:	49 ff fc 7f 	jal 5f88 <lfs_file_relocate>
    668e:	c8 bd       	bnez38 $r0,6608 <lfs_file_flush+0xc0>
    6690:	80 07       	mov55 $r0,$r7
    6692:	80 28       	mov55 $r1,$r8
    6694:	80 47       	mov55 $r2,$r7
    6696:	84 61       	movi55 $r3,#0x1
    6698:	49 ff f4 00 	jal 4e98 <lfs_bd_flush>
    669c:	c8 e6       	bnez38 $r0,6668 <lfs_file_flush+0x120>
    669e:	04 03 00 0d 	lwi $r0,[$r6+#0x34]
    66a2:	04 13 00 0c 	lwi $r1,[$r6+#0x30]
    66a6:	d5 bd       	j8 6620 <lfs_file_flush+0xd8>
    66a8:	44 00 36 d4 	movi $r0,#0x36d4
    66ac:	44 10 0a 5f 	movi $r1,#0xa5f
    66b0:	44 20 7c 50 	movi $r2,#0x7c50
    66b4:	44 30 3a 5c 	movi $r3,#0x3a5c
    66b8:	49 00 1a b2 	jal 9c1c <__assert_func>
    66bc:	92 00       	nop16
    66be:	92 00       	nop16

000066c0 <lfs_file_read>:
    66c0:	3a 6f ba bc 	smw.adm $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    66c4:	ef dc       	addi10.sp #-36
    66c6:	36 3f 80 04 	fsdi $fd3,[$sp+#0x10]
    66ca:	36 4f 80 06 	fsdi $fd4,[$sp+#0x18]
    66ce:	04 40 80 0c 	lwi $r4,[$r1+#0x30]
    66d2:	80 c1       	mov55 $r6,$r1
    66d4:	42 52 54 0b 	btst $r5,$r4,#0x15
    66d8:	4e 52 00 be 	beqz $r5,6854 <lfs_file_read+0x194>
    66dc:	81 22       	mov55 $r9,$r2
    66de:	54 22 00 03 	andi $r2,$r4,#0x3
    66e2:	5a 28 02 05 	bnec $r2,#0x2,66ec <lfs_file_read+0x2c>
    66e6:	48 00 00 ab 	j 683c <lfs_file_read+0x17c>
    66ea:	92 00       	nop16
    66ec:	42 42 44 0b 	btst $r4,$r4,#0x11
    66f0:	81 40       	mov55 $r10,$r0
    66f2:	4e 43 00 8d 	bnez $r4,680c <lfs_file_read+0x14c>
    66f6:	92 00       	nop16
    66f8:	04 43 00 0d 	lwi $r4,[$r6+#0x34]
    66fc:	04 13 00 0b 	lwi $r1,[$r6+#0x2c]
    6700:	84 00       	movi55 $r0,#0x0
    6702:	e2 81       	slt45 $r4,$r1
    6704:	e8 68       	beqzs8 67d4 <lfs_file_read+0x114>
    6706:	8a 24       	sub45 $r1,$r4
    6708:	e2 23       	slt45 $r1,$r3
    670a:	40 11 bc 1a 	cmovz $r1,$r3,$r15
    670e:	6a 13 00 09 	fmtsr $r1,$fs6
    6712:	50 c3 00 40 	addi $r12,$r6,#0x40
    6716:	81 01       	mov55 $r8,$r1
    6718:	4e 12 00 88 	beqz $r1,6828 <lfs_file_read+0x168>
    671c:	50 03 00 38 	addi $r0,$r6,#0x38
    6720:	6a 04 00 09 	fmtsr $r0,$fs8
    6724:	50 03 00 3c 	addi $r0,$r6,#0x3c
    6728:	46 b0 01 00 	sethi $r11,#0x100
    672c:	6a 03 80 09 	fmtsr $r0,$fs7
    6730:	51 c5 00 68 	addi $fp,$r10,#0x68
    6734:	50 e3 00 08 	addi $r14,$r6,#0x8
    6738:	46 d2 01 00 	sethi $r13,#0x20100
    673c:	d5 2a       	j8 6790 <lfs_file_read+0xd0>
    673e:	92 00       	nop16
    6740:	04 05 00 1a 	lwi $r0,[$r10+#0x68]
    6744:	04 53 00 0f 	lwi $r5,[$r6+#0x3c]
    6748:	a0 c7       	lwi333 $r3,[$r0+#0x1c]
    674a:	d3 29       	beqs38 $r3,679c <lfs_file_read+0xdc>
    674c:	9b dd       	sub333 $r7,$r3,$r5
    674e:	e3 07       	slt45 $r8,$r7
    6750:	40 08 2c 02 	and $r0,$r16,$r11
    6754:	40 74 3c 1b 	cmovn $r7,$r8,$r15
    6758:	c0 34       	beqz38 $r0,67c0 <lfs_file_read+0x100>
    675a:	a5 32       	lhi333 $r4,[$r6+#0x4]
    675c:	80 0a       	mov55 $r0,$r10
    675e:	40 42 28 08 	slli $r4,$r4,#0xa
    6762:	b7 3f       	swi450 $r9,[$sp]
    6764:	f7 81       	swi37.sp $r7,[+#0x4]
    6766:	80 2e       	mov55 $r1,$r14
    6768:	80 4c       	mov55 $r2,$r12
    676a:	40 42 34 04 	or $r4,$r4,$r13
    676e:	49 ff f8 bd 	jal 58e8 <lfs_dir_getread.constprop.33>
    6772:	c8 31       	bnez38 $r0,67d4 <lfs_file_read+0x114>
    6774:	04 43 00 0d 	lwi $r4,[$r6+#0x34]
    6778:	05 03 00 0f 	lwi $r16,[$r6+#0x3c]
    677c:	88 87       	add45 $r4,$r7
    677e:	89 87       	add45 $r16,$r7
    6780:	8b 07       	sub45 $r8,$r7
    6782:	14 43 00 0d 	swi $r4,[$r6+#0x34]
    6786:	15 03 00 0f 	swi $r16,[$r6+#0x3c]
    678a:	89 27       	add45 $r9,$r7
    678c:	4e 82 00 4e 	beqz $r8,6828 <lfs_file_read+0x168>
    6790:	05 03 00 0c 	lwi $r16,[$r6+#0x30]
    6794:	42 f8 48 0b 	btst $r15,$r16,#0x12
    6798:	4e f3 ff d4 	bnez $r15,6740 <lfs_file_read+0x80>
    679c:	40 f8 2c 02 	and $r15,$r16,$r11
    67a0:	e8 22       	beqzs8 67e4 <lfs_file_read+0x124>
    67a2:	84 1e       	movi55 $r0,#-2
    67a4:	50 52 00 00 	addi $r5,$r4,#0x0
    67a8:	14 03 00 0e 	swi $r0,[$r6+#0x38]
    67ac:	14 43 00 0f 	swi $r4,[$r6+#0x3c]
    67b0:	04 05 00 1a 	lwi $r0,[$r10+#0x68]
    67b4:	43 08 48 08 	bset $r16,$r16,#0x12
    67b8:	15 03 00 0c 	swi $r16,[$r6+#0x30]
    67bc:	a0 c7       	lwi333 $r3,[$r0+#0x1c]
    67be:	d5 c7       	j8 674c <lfs_file_read+0x8c>
    67c0:	b7 3f       	swi450 $r9,[$sp]
    67c2:	f7 81       	swi37.sp $r7,[+#0x4]
    67c4:	80 1c       	mov55 $r0,$fp
    67c6:	84 20       	movi55 $r1,#0x0
    67c8:	80 4c       	mov55 $r2,$r12
    67ca:	04 43 00 0e 	lwi $r4,[$r6+#0x38]
    67ce:	49 ff ec 6d 	jal 40a8 <lfs_bd_read.isra.13>
    67d2:	c0 d1       	beqz38 $r0,6774 <lfs_file_read+0xb4>
    67d4:	ec 10       	addi10.sp #0x10
    67d6:	34 3f 90 02 	fldi.bi $fd3,[$sp],#0x8
    67da:	34 4f 90 03 	fldi.bi $fd4,[$sp],#0xc
    67de:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    67e2:	dd 9e       	ret5 $lp
    67e4:	32 7f 80 00 	fssi $fs7,[$sp+#0x0]
    67e8:	6a 54 00 01 	fmfsr $r5,$fs8
    67ec:	80 0a       	mov55 $r0,$r10
    67ee:	80 2c       	mov55 $r1,$r12
    67f0:	04 23 00 0a 	lwi $r2,[$r6+#0x28]
    67f4:	04 33 00 0b 	lwi $r3,[$r6+#0x2c]
    67f8:	04 43 00 0d 	lwi $r4,[$r6+#0x34]
    67fc:	49 ff f2 b6 	jal 4d68 <lfs_ctz_find.constprop.32>
    6800:	c8 ea       	bnez38 $r0,67d4 <lfs_file_read+0x114>
    6802:	05 03 00 0c 	lwi $r16,[$r6+#0x30]
    6806:	04 53 00 0f 	lwi $r5,[$r6+#0x3c]
    680a:	d5 d3       	j8 67b0 <lfs_file_read+0xf0>
    680c:	f3 83       	swi37.sp $r3,[+#0xc]
    680e:	49 ff fe 9d 	jal 6548 <lfs_file_flush>
    6812:	f3 03       	lwi37.sp $r3,[+#0xc]
    6814:	4e 02 ff 72 	beqz $r0,66f8 <lfs_file_read+0x38>
    6818:	ec 10       	addi10.sp #0x10
    681a:	34 3f 90 02 	fldi.bi $fd3,[$sp],#0x8
    681e:	34 4f 90 03 	fldi.bi $fd4,[$sp],#0xc
    6822:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    6826:	dd 9e       	ret5 $lp
    6828:	6a 03 00 01 	fmfsr $r0,$fs6
    682c:	ec 10       	addi10.sp #0x10
    682e:	34 3f 90 02 	fldi.bi $fd3,[$sp],#0x8
    6832:	34 4f 90 03 	fldi.bi $fd4,[$sp],#0xc
    6836:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    683a:	dd 9e       	ret5 $lp
    683c:	44 00 36 d4 	movi $r0,#0x36d4
    6840:	44 10 0a ec 	movi $r1,#0xaec
    6844:	44 20 7b f8 	movi $r2,#0x7bf8
    6848:	44 30 3b f0 	movi $r3,#0x3bf0
    684c:	49 00 19 e8 	jal 9c1c <__assert_func>
    6850:	92 00       	nop16
    6852:	92 00       	nop16
    6854:	44 00 36 d4 	movi $r0,#0x36d4
    6858:	44 10 0a eb 	movi $r1,#0xaeb
    685c:	44 20 7b f8 	movi $r2,#0x7bf8
    6860:	44 30 3a 5c 	movi $r3,#0x3a5c
    6864:	49 00 19 dc 	jal 9c1c <__assert_func>
    6868:	92 00       	nop16
    686a:	92 00       	nop16

0000686c <lfs_fs_size>:
    686c:	3b ff fc bc 	smw.adm $sp,[$sp],$sp,#0x2    ! {$lp}
    6870:	ef f4       	addi10.sp #-12
    6872:	84 80       	movi55 $r4,#0x0
    6874:	44 10 36 74 	movi $r1,#0x3674
    6878:	b0 81       	addri36.sp $r2,#0x4
    687a:	84 60       	movi55 $r3,#0x0
    687c:	f4 81       	swi37.sp $r4,[+#0x4]
    687e:	49 ff f9 e9 	jal 5c50 <lfs_fs_traverseraw>
    6882:	f1 01       	lwi37.sp $r1,[+#0x4]
    6884:	40 00 80 1a 	cmovz $r0,$r1,$r0
    6888:	ec 0c       	addi10.sp #0xc
    688a:	3b ff fc 84 	lmw.bim $sp,[$sp],$sp,#0x2    ! {$lp}
    688e:	dd 9e       	ret5 $lp

00006890 <lfs_dir_compact>:
    6890:	3a 6f ba bc 	smw.adm $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    6894:	ef 7c       	addi10.sp #-132
    6896:	36 3f 80 1c 	fsdi $fd3,[$sp+#0x70]
    689a:	36 4f 80 1e 	fsdi $fd4,[$sp+#0x78]
    689e:	03 cf 80 58 	lhi $fp,[$sp+#0xb0]
    68a2:	b5 81       	lwi450 $r16,[$r1]
    68a4:	40 6e 14 01 	sub $r6,$fp,$r5
    68a8:	80 e5       	mov55 $r7,$r5
    68aa:	81 21       	mov55 $r9,$r1
    68ac:	a1 49       	lwi333 $r5,[$r1+#0x4]
    68ae:	e4 c2       	sltsi45 $r6,#0x2
    68b0:	81 00       	mov55 $r8,$r0
    68b2:	fd 51       	movd44 $r10,$r2
    68b4:	81 84       	mov55 $r12,$r4
    68b6:	15 0f 80 08 	swi $r16,[$sp+#0x20]
    68ba:	f5 89       	swi37.sp $r5,[+#0x24]
    68bc:	4e f3 01 c4 	bnez $r15,6c44 <lfs_dir_compact+0x3b4>
    68c0:	fe 3a       	neg33 $r0,$r7
    68c2:	96 03       	seh33 $r0,$r0
    68c4:	6a 04 00 09 	fmtsr $r0,$fs8
    68c8:	44 00 36 58 	movi $r0,#0x3658
    68cc:	6a 04 80 09 	fmtsr $r0,$fs9
    68d0:	b0 14       	addri36.sp $r0,#0x50
    68d2:	6a 03 00 09 	fmtsr $r0,$fs6
    68d6:	46 04 00 ff 	sethi $r0,#0x400ff
    68da:	50 00 0c 00 	addi $r0,$r0,#0xc00
    68de:	85 a0       	movi55 $r13,#0x0
    68e0:	6a 03 80 09 	fmtsr $r0,$fs7
    68e4:	d5 2c       	j8 693c <lfs_dir_compact+0xac>
    68e6:	92 00       	nop16
    68e8:	5e f3 00 ff 	sltsi $r15,$r6,#0xff
    68ec:	e8 15       	beqzs8 6916 <lfs_dir_compact+0x86>
    68ee:	04 04 00 1a 	lwi $r0,[$r8+#0x68]
    68f2:	a0 47       	lwi333 $r1,[$r0+#0x1c]
    68f4:	a0 86       	lwi333 $r2,[$r0+#0x18]
    68f6:	41 10 84 09 	srli $r17,$r1,#0x1
    68fa:	51 01 7f ff 	addi $r16,$r2,#-1
    68fe:	89 91       	add45 $r16,$r17
    6900:	40 28 08 77 	divr $r2,$r3,$r16,$r2
    6904:	50 20 ff dc 	addi $r2,$r1,#-36
    6908:	8b 83       	sub45 $r16,$r3
    690a:	e2 50       	slt45 $r2,$r16
    690c:	41 01 3c 1b 	cmovn $r16,$r2,$r15
    6910:	f1 14       	lwi37.sp $r1,[+#0x50]
    6912:	e3 81       	slt45 $r16,$r1
    6914:	e8 40       	beqzs8 6994 <lfs_dir_compact+0x104>
    6916:	90 c1       	srai45 $r6,#0x1
    6918:	88 c7       	add45 $r6,$r7
    691a:	40 e3 00 13 	zeh $r14,$r6
    691e:	15 cf 80 00 	swi $fp,[$sp+#0x0]
    6922:	fd 04       	movd44 $r0,$r8
    6924:	fd 15       	movd44 $r2,$r10
    6926:	80 8c       	mov55 $r4,$r12
    6928:	80 ae       	mov55 $r5,$r14
    692a:	49 00 09 0b 	jal 7b40 <lfs_dir_split>
    692e:	c8 28       	bnez38 $r0,697e <lfs_dir_compact+0xee>
    6930:	40 67 1c 01 	sub $r6,$r14,$r7
    6934:	e4 c2       	sltsi45 $r6,#0x2
    6936:	e9 31       	bnezs8 6998 <lfs_dir_compact+0x108>
    6938:	83 8e       	mov55 $fp,$r14
    693a:	92 00       	nop16
    693c:	32 7f 80 00 	fssi $fs7,[$sp+#0x0]
    6940:	14 df 80 01 	swi $r13,[$sp+#0x4]
    6944:	f7 82       	swi37.sp $r7,[+#0x8]
    6946:	15 cf 80 03 	swi $fp,[$sp+#0xc]
    694a:	32 8f 80 04 	fssi $fs8,[$sp+#0x10]
    694e:	32 9f 80 05 	fssi $fs9,[$sp+#0x14]
    6952:	32 6f 80 06 	fssi $fs6,[$sp+#0x18]
    6956:	80 08       	mov55 $r0,$r8
    6958:	80 2c       	mov55 $r1,$r12
    695a:	84 40       	movi55 $r2,#0x0
    695c:	84 7f       	movi55 $r3,#-1
    695e:	fd 25       	movd44 $r4,$r10
    6960:	14 df 80 14 	swi $r13,[$sp+#0x50]
    6964:	49 ff f0 30 	jal 49c4 <lfs_dir_traverse>
    6968:	c0 c0       	beqz38 $r0,68e8 <lfs_dir_compact+0x58>
    696a:	82 00       	mov55 $r16,$r0
    696c:	80 10       	mov55 $r0,$r16
    696e:	ec 70       	addi10.sp #0x70
    6970:	34 3f 90 02 	fldi.bi $fd3,[$sp],#0x8
    6974:	34 4f 90 03 	fldi.bi $fd4,[$sp],#0xc
    6978:	3a 6f ba 84 	lmw.bim $r6,[$sp],$r14,#0xa    ! {$r6~$r14, $fp, $lp}
    697c:	dd 9e       	ret5 $lp
    697e:	82 00       	mov55 $r16,$r0
    6980:	5a 0f e4 f6 	bnec $r0,#-28,696c <lfs_dir_compact+0xdc>
    6984:	04 04 00 1a 	lwi $r0,[$r8+#0x68]
    6988:	f2 14       	lwi37.sp $r2,[+#0x50]
    698a:	a0 47       	lwi333 $r1,[$r0+#0x1c]
    698c:	50 10 ff dc 	addi $r1,$r1,#-36
    6990:	e2 22       	slt45 $r1,$r2
    6992:	e9 ed       	bnezs8 696c <lfs_dir_compact+0xdc>
    6994:	81 dc       	mov55 $r14,$fp
    6996:	d5 03       	j8 699c <lfs_dir_compact+0x10c>
    6998:	04 04 00 1a 	lwi $r0,[$r8+#0x68]
    699c:	04 34 80 02 	lwi $r3,[$r9+#0x8]
    69a0:	04 10 00 09 	lwi $r1,[$r0+#0x24]
    69a4:	8c 61       	addi45 $r3,#0x1
    69a6:	14 34 80 02 	swi $r3,[$r9+#0x8]
    69aa:	4e 17 00 3d 	blez $r1,6a24 <lfs_dir_compact+0x194>
    69ae:	9c 89       	addi333 $r2,$r1,#0x1
    69b0:	58 11 00 01 	ori $r1,$r2,#0x1
    69b4:	40 31 84 37 	divr $r3,$r1,$r3,$r1
    69b8:	c9 36       	bnez38 $r1,6a24 <lfs_dir_compact+0x194>
    69ba:	b4 09       	lwi450 $r0,[$r9]
    69bc:	c0 08       	beqz38 $r0,69cc <lfs_dir_compact+0x13c>
    69be:	04 14 80 01 	lwi $r1,[$r9+#0x4]
    69c2:	5a 00 01 05 	beqc $r0,#0x1,69cc <lfs_dir_compact+0x13c>
    69c6:	e6 22       	slti45 $r1,#0x2
    69c8:	4e f2 00 80 	beqz $r15,6ac8 <lfs_dir_compact+0x238>
    69cc:	80 08       	mov55 $r0,$r8
    69ce:	49 ff ff 4f 	jal 686c <lfs_fs_size>
    69d2:	82 00       	mov55 $r16,$r0
    69d4:	4e 05 ff cc 	bltz $r0,696c <lfs_dir_compact+0xdc>
    69d8:	04 04 00 1a 	lwi $r0,[$r8+#0x68]
    69dc:	87 80       	movi55 $fp,#0x0
    69de:	04 10 00 08 	lwi $r1,[$r0+#0x20]
    69e2:	92 21       	srli45 $r1,#0x1
    69e4:	e3 81       	slt45 $r16,$r1
    69e6:	e8 20       	beqzs8 6a26 <lfs_dir_compact+0x196>
    69e8:	04 04 80 02 	lwi $r0,[$r9+#0x8]
    69ec:	44 10 36 d4 	movi $r1,#0x36d4
    69f0:	b6 3f       	swi450 $r1,[$sp]
    69f2:	f0 82       	swi37.sp $r0,[+#0x8]
    69f4:	44 10 06 00 	movi $r1,#0x600
    69f8:	44 00 01 38 	movi $r0,#0x138
    69fc:	f1 81       	swi37.sp $r1,[+#0x4]
    69fe:	f0 83       	swi37.sp $r0,[+#0xc]
    6a00:	44 00 3c 14 	movi $r0,#0x3c14
    6a04:	49 ff dd 1c 	jal 243c <printf>
    6a08:	14 ef 80 00 	swi $r14,[$sp+#0x0]
    6a0c:	fd 04       	movd44 $r0,$r8
    6a0e:	fd 15       	movd44 $r2,$r10
    6a10:	80 8c       	mov55 $r4,$r12
    6a12:	80 a7       	mov55 $r5,$r7
    6a14:	49 00 08 96 	jal 7b40 <lfs_dir_split>
    6a18:	4e 03 01 1b 	bnez $r0,6c4e <lfs_dir_compact+0x3be>
    6a1c:	04 04 00 1a 	lwi $r0,[$r8+#0x68]
    6a20:	81 c7       	mov55 $r14,$r7
    6a22:	d5 02       	j8 6a26 <lfs_dir_compact+0x196>
    6a24:	87 80       	movi55 $fp,#0x0
    6a26:	b0 54       	addri36.sp $r1,#0x50
    6a28:	6a 13 00 09 	fmtsr $r1,$fs6
    6a2c:	84 40       	movi55 $r2,#0x0
    6a2e:	84 7f       	movi55 $r3,#-1
    6a30:	04 14 80 01 	lwi $r1,[$r9+#0x4]
    6a34:	6a 43 00 01 	fmfsr $r4,$fs6
    6a38:	f1 94       	swi37.sp $r1,[+#0x50]
    6a3a:	a8 a1       	swi333 $r2,[$r4+#0x4]
    6a3c:	a8 e2       	swi333 $r3,[$r4+#0x8]
    6a3e:	a8 e3       	swi333 $r3,[$r4+#0xc]
    6a40:	a8 a4       	swi333 $r2,[$r4+#0x10]
    6a42:	a0 87       	lwi333 $r2,[$r0+#0x1c]
    6a44:	8e 48       	subi45 $r2,#0x8
    6a46:	a8 a5       	swi333 $r2,[$r4+#0x14]
    6a48:	49 ff f1 08 	jal 4c58 <lfs_bd_erase.isra.16>
    6a4c:	4e 02 00 44 	beqz $r0,6ad4 <lfs_dir_compact+0x244>
    6a50:	5a 07 ac 04 	beqc $r0,#-84,6a58 <lfs_dir_compact+0x1c8>
    6a54:	48 ff ff 8b 	j 696a <lfs_dir_compact+0xda>
    6a58:	84 1f       	movi55 $r0,#-1
    6a5a:	14 04 00 04 	swi $r0,[$r8+#0x10]
    6a5e:	04 04 80 01 	lwi $r0,[$r9+#0x4]
    6a62:	44 10 36 d4 	movi $r1,#0x36d4
    6a66:	b6 3f       	swi450 $r1,[$sp]
    6a68:	f0 82       	swi37.sp $r0,[+#0x8]
    6a6a:	44 10 06 95 	movi $r1,#0x695
    6a6e:	44 00 01 38 	movi $r0,#0x138
    6a72:	f0 83       	swi37.sp $r0,[+#0xc]
    6a74:	f1 81       	swi37.sp $r1,[+#0x4]
    6a76:	44 00 3b a8 	movi $r0,#0x3ba8
    6a7a:	49 ff dc e1 	jal 243c <printf>
    6a7e:	84 c0       	movi55 $r6,#0x0
    6a80:	b4 09       	lwi450 $r0,[$r9]
    6a82:	04 14 80 01 	lwi $r1,[$r9+#0x4]
    6a86:	c0 0f       	beqz38 $r0,6aa4 <lfs_dir_compact+0x214>
    6a88:	5a 00 01 0e 	beqc $r0,#0x1,6aa4 <lfs_dir_compact+0x214>
    6a8c:	e6 22       	slti45 $r1,#0x2
    6a8e:	e9 0b       	bnezs8 6aa4 <lfs_dir_compact+0x214>
    6a90:	80 08       	mov55 $r0,$r8
    6a92:	50 14 80 04 	addi $r1,$r9,#0x4
    6a96:	49 ff f9 99 	jal 5dc8 <lfs_alloc>
    6a9a:	c8 2c       	bnez38 $r0,6af2 <lfs_dir_compact+0x262>
    6a9c:	04 04 00 1a 	lwi $r0,[$r8+#0x68]
    6aa0:	87 81       	movi55 $fp,#0x1
    6aa2:	d5 c2       	j8 6a26 <lfs_dir_compact+0x196>
    6aa4:	44 00 36 d4 	movi $r0,#0x36d4
    6aa8:	b6 1f       	swi450 $r0,[$sp]
    6aaa:	44 00 06 9b 	movi $r0,#0x69b
    6aae:	f0 81       	swi37.sp $r0,[+#0x4]
    6ab0:	44 00 01 38 	movi $r0,#0x138
    6ab4:	f0 83       	swi37.sp $r0,[+#0xc]
    6ab6:	f1 82       	swi37.sp $r1,[+#0x8]
    6ab8:	44 00 3c ec 	movi $r0,#0x3cec
    6abc:	49 ff dc c0 	jal 243c <printf>
    6ac0:	45 0f ff e4 	movi $r16,#-28
    6ac4:	48 ff ff 54 	j 696c <lfs_dir_compact+0xdc>
    6ac8:	84 1f       	movi55 $r0,#-1
    6aca:	14 04 00 04 	swi $r0,[$r8+#0x10]
    6ace:	84 c1       	movi55 $r6,#0x1
    6ad0:	d5 d8       	j8 6a80 <lfs_dir_compact+0x1f0>
    6ad2:	92 00       	nop16
    6ad4:	6a 13 00 01 	fmfsr $r1,$fs6
    6ad8:	80 08       	mov55 $r0,$r8
    6ada:	50 24 80 08 	addi $r2,$r9,#0x8
    6ade:	84 64       	movi55 $r3,#0x4
    6ae0:	49 ff f2 ce 	jal 507c <lfs_dir_commitprog>
    6ae4:	82 00       	mov55 $r16,$r0
    6ae6:	c0 0e       	beqz38 $r0,6b02 <lfs_dir_compact+0x272>
    6ae8:	5a 07 ac 04 	beqc $r0,#-84,6af0 <lfs_dir_compact+0x260>
    6aec:	48 ff ff 40 	j 696c <lfs_dir_compact+0xdc>
    6af0:	d5 b4       	j8 6a58 <lfs_dir_compact+0x1c8>
    6af2:	82 00       	mov55 $r16,$r0
    6af4:	5a 07 e4 04 	beqc $r0,#-28,6afc <lfs_dir_compact+0x26c>
    6af8:	48 ff ff 3a 	j 696c <lfs_dir_compact+0xdc>
    6afc:	ce d0       	bnez38 $r6,6a9c <lfs_dir_compact+0x20c>
    6afe:	48 ff ff 37 	j 696c <lfs_dir_compact+0xdc>
    6b02:	fe 3a       	neg33 $r0,$r7
    6b04:	96 03       	seh33 $r0,$r0
    6b06:	46 14 00 ff 	sethi $r1,#0x400ff
    6b0a:	50 10 8c 00 	addi $r1,$r1,#0xc00
    6b0e:	51 1f 80 28 	addi $r17,$sp,#0x28
    6b12:	f0 84       	swi37.sp $r0,[+#0x10]
    6b14:	44 00 51 78 	movi $r0,#0x5178
    6b18:	b6 3f       	swi450 $r1,[$sp]
    6b1a:	f0 85       	swi37.sp $r0,[+#0x14]
    6b1c:	15 0f 80 01 	swi $r16,[$sp+#0x4]
    6b20:	f7 82       	swi37.sp $r7,[+#0x8]
    6b22:	14 ef 80 03 	swi $r14,[$sp+#0xc]
    6b26:	15 1f 80 06 	swi $r17,[$sp+#0x18]
    6b2a:	80 08       	mov55 $r0,$r8
    6b2c:	80 2c       	mov55 $r1,$r12
    6b2e:	84 40       	movi55 $r2,#0x0
    6b30:	84 7f       	movi55 $r3,#-1
    6b32:	fd 25       	movd44 $r4,$r10
    6b34:	14 8f 80 0a 	swi $r8,[$sp+#0x28]
    6b38:	32 6f 80 0b 	fssi $fs6,[$sp+#0x2c]
    6b3c:	49 ff ef 44 	jal 49c4 <lfs_dir_traverse>
    6b40:	4e 03 ff 88 	bnez $r0,6a50 <lfs_dir_compact+0x1c0>
    6b44:	04 04 80 06 	lwi $r0,[$r9+#0x18]
    6b48:	5a 07 ff 1a 	beqc $r0,#-1,6b7c <lfs_dir_compact+0x2ec>
    6b4c:	04 04 80 07 	lwi $r0,[$r9+#0x1c]
    6b50:	5a 07 ff 16 	beqc $r0,#-1,6b7c <lfs_dir_compact+0x2ec>
    6b54:	00 24 80 17 	lbi $r2,[$r9+#0x17]
    6b58:	46 30 00 ff 	sethi $r3,#0xff
    6b5c:	50 21 06 00 	addi $r2,$r2,#0x600
    6b60:	50 31 8c 08 	addi $r3,$r3,#0xc08
    6b64:	40 21 50 08 	slli $r2,$r2,#0x14
    6b68:	6a 13 00 01 	fmfsr $r1,$fs6
    6b6c:	fe 9f       	or33 $r2,$r3
    6b6e:	80 08       	mov55 $r0,$r8
    6b70:	50 34 80 18 	addi $r3,$r9,#0x18
    6b74:	49 ff f2 a4 	jal 50bc <lfs_dir_commitattr>
    6b78:	4e 03 ff 6c 	bnez $r0,6a50 <lfs_dir_compact+0x1c0>
    6b7c:	b0 10       	addri36.sp $r0,#0x40
    6b7e:	84 20       	movi55 $r1,#0x0
    6b80:	44 20 00 0c 	movi $r2,#0xc
    6b84:	49 00 1a 1c 	jal 9fbc <memset>
    6b88:	4f c2 00 6c 	beqz $fp,6c60 <lfs_dir_compact+0x3d0>
    6b8c:	84 20       	movi55 $r1,#0x0
    6b8e:	84 40       	movi55 $r2,#0x0
    6b90:	44 30 00 00 	movi $r3,#0x0
    6b94:	04 04 00 12 	lwi $r0,[$r8+#0x48]
    6b98:	04 54 00 13 	lwi $r5,[$r8+#0x4c]
    6b9c:	04 44 00 14 	lwi $r4,[$r8+#0x50]
    6ba0:	fe 1d       	xor33 $r0,$r3
    6ba2:	ff 55       	xor33 $r5,$r2
    6ba4:	ff 0d       	xor33 $r4,$r1
    6ba6:	66 30 03 ff 	bitci $r3,$r0,#0x3ff
    6baa:	80 29       	mov55 $r1,$r9
    6bac:	80 08       	mov55 $r0,$r8
    6bae:	b0 90       	addri36.sp $r2,#0x40
    6bb0:	f5 91       	swi37.sp $r5,[+#0x44]
    6bb2:	f4 92       	swi37.sp $r4,[+#0x48]
    6bb4:	14 3f 80 10 	swi $r3,[$sp+#0x40]
    6bb8:	49 ff f5 22 	jal 55fc <lfs_dir_getgstate>
    6bbc:	4e 03 fe d7 	bnez $r0,696a <lfs_dir_compact+0xda>
    6bc0:	f0 10       	lwi37.sp $r0,[+#0x40]
    6bc2:	4e 03 01 6d 	bnez $r0,6e9c <lfs_dir_compact+0x60c>
    6bc6:	f0 11       	lwi37.sp $r0,[+#0x44]
    6bc8:	4e 03 01 6a 	bnez $r0,6e9c <lfs_dir_compact+0x60c>
    6bcc:	f0 12       	lwi37.sp $r0,[+#0x48]
    6bce:	4e 03 01 67 	bnez $r0,6e9c <lfs_dir_compact+0x60c>
    6bd2:	92 00       	nop16
    6bd4:	6a 13 00 01 	fmfsr $r1,$fs6
    6bd8:	50 04 00 00 	addi $r0,$r8,#0x0
    6bdc:	49 ff f2 d4 	jal 5184 <lfs_dir_commitcrc>
    6be0:	4e 03 ff 38 	bnez $r0,6a50 <lfs_dir_compact+0x1c0>
    6be4:	04 14 00 1a 	lwi $r1,[$r8+#0x68]
    6be8:	6a 03 00 01 	fmfsr $r0,$fs6
    6bec:	a0 4e       	lwi333 $r1,[$r1+#0x18]
    6bee:	a0 01       	lwi333 $r0,[$r0+#0x4]
    6bf0:	40 10 04 d7 	divr $r1,$r6,$r0,$r1
    6bf4:	81 66       	mov55 $r11,$r6
    6bf6:	4e 63 01 61 	bnez $r6,6eb8 <lfs_dir_compact+0x628>
    6bfa:	6a 13 00 01 	fmfsr $r1,$fs6
    6bfe:	b5 49       	lwi450 $r10,[$r9]
    6c00:	04 64 80 01 	lwi $r6,[$r9+#0x4]
    6c04:	a0 4a       	lwi333 $r1,[$r1+#0x8]
    6c06:	40 77 1c 01 	sub $r7,$r14,$r7
    6c0a:	14 04 80 03 	swi $r0,[$r9+#0xc]
    6c0e:	14 14 80 04 	swi $r1,[$r9+#0x10]
    6c12:	b6 c9       	swi450 $r6,[$r9]
    6c14:	14 a4 80 01 	swi $r10,[$r9+#0x4]
    6c18:	12 74 80 0a 	shi $r7,[$r9+#0x14]
    6c1c:	50 04 00 48 	addi $r0,$r8,#0x48
    6c20:	84 20       	movi55 $r1,#0x0
    6c22:	84 4c       	movi55 $r2,#0xc
    6c24:	49 00 19 cc 	jal 9fbc <memset>
    6c28:	4f c3 00 2e 	bnez $fp,6c84 <lfs_dir_compact+0x3f4>
    6c2c:	50 04 00 30 	addi $r0,$r8,#0x30
    6c30:	3b 00 48 00 	lmw.bi $r16,[$r0],$r18,#0x0    ! {$r16~$r18}
    6c34:	50 84 00 3c 	addi $r8,$r8,#0x3c
    6c38:	3b 04 48 20 	smw.bi $r16,[$r8],$r18,#0x0    ! {$r16~$r18}
    6c3c:	86 00       	movi55 $r16,#0x0
    6c3e:	48 ff fe 97 	j 696c <lfs_dir_compact+0xdc>
    6c42:	92 00       	nop16
    6c44:	04 00 00 1a 	lwi $r0,[$r0+#0x68]
    6c48:	81 dc       	mov55 $r14,$fp
    6c4a:	48 ff fe a9 	j 699c <lfs_dir_compact+0x10c>
    6c4e:	82 00       	mov55 $r16,$r0
    6c50:	5a 07 e4 04 	beqc $r0,#-28,6c58 <lfs_dir_compact+0x3c8>
    6c54:	48 ff fe 8c 	j 696c <lfs_dir_compact+0xdc>
    6c58:	04 04 00 1a 	lwi $r0,[$r8+#0x68]
    6c5c:	48 ff fe e5 	j 6a26 <lfs_dir_compact+0x196>
    6c60:	04 34 00 0c 	lwi $r3,[$r8+#0x30]
    6c64:	04 04 00 0f 	lwi $r0,[$r8+#0x3c]
    6c68:	04 54 00 0d 	lwi $r5,[$r8+#0x34]
    6c6c:	04 24 00 10 	lwi $r2,[$r8+#0x40]
    6c70:	04 44 00 0e 	lwi $r4,[$r8+#0x38]
    6c74:	04 14 00 11 	lwi $r1,[$r8+#0x44]
    6c78:	fe c5       	xor33 $r3,$r0
    6c7a:	fe ad       	xor33 $r2,$r5
    6c7c:	fe 65       	xor33 $r1,$r4
    6c7e:	48 ff ff 8b 	j 6b94 <lfs_dir_compact+0x304>
    6c82:	92 00       	nop16
    6c84:	44 10 06 ad 	movi $r1,#0x6ad
    6c88:	f0 09       	lwi37.sp $r0,[+#0x24]
    6c8a:	f1 81       	swi37.sp $r1,[+#0x4]
    6c8c:	44 e0 36 d4 	movi $r14,#0x36d4
    6c90:	f1 08       	lwi37.sp $r1,[+#0x20]
    6c92:	44 c0 01 38 	movi $r12,#0x138
    6c96:	f1 82       	swi37.sp $r1,[+#0x8]
    6c98:	f0 83       	swi37.sp $r0,[+#0xc]
    6c9a:	14 ef 80 00 	swi $r14,[$sp+#0x0]
    6c9e:	f6 84       	swi37.sp $r6,[+#0x10]
    6ca0:	14 af 80 05 	swi $r10,[$sp+#0x14]
    6ca4:	14 cf 80 06 	swi $r12,[$sp+#0x18]
    6ca8:	44 00 3c b0 	movi $r0,#0x3cb0
    6cac:	49 ff db c8 	jal 243c <printf>
    6cb0:	f5 08       	lwi37.sp $r5,[+#0x20]
    6cb2:	04 04 00 08 	lwi $r0,[$r8+#0x20]
    6cb6:	4c 50 00 80 	beq $r5,$r0,6db6 <lfs_dir_compact+0x526>
    6cba:	f2 09       	lwi37.sp $r2,[+#0x24]
    6cbc:	04 34 00 09 	lwi $r3,[$r8+#0x24]
    6cc0:	4c 21 80 7b 	beq $r2,$r3,6db6 <lfs_dir_compact+0x526>
    6cc4:	4c 51 80 79 	beq $r5,$r3,6db6 <lfs_dir_compact+0x526>
    6cc8:	4c 01 00 77 	beq $r0,$r2,6db6 <lfs_dir_compact+0x526>
    6ccc:	04 04 00 0a 	lwi $r0,[$r8+#0x28]
    6cd0:	f2 09       	lwi37.sp $r2,[+#0x24]
    6cd2:	c8 0d       	bnez38 $r0,6cec <lfs_dir_compact+0x45c>
    6cd4:	d5 26       	j8 6d20 <lfs_dir_compact+0x490>
    6cd6:	a1 03       	lwi333 $r4,[$r0+#0xc]
    6cd8:	4c 22 00 0c 	beq $r2,$r4,6cf0 <lfs_dir_compact+0x460>
    6cdc:	d4 0a       	beqs38 $r4,6cf0 <lfs_dir_compact+0x460>
    6cde:	4c 31 00 09 	beq $r3,$r2,6cf0 <lfs_dir_compact+0x460>
    6ce2:	a6 c6       	lbi333 $r3,[$r0+#0x6]
    6ce4:	5a 30 02 0c 	beqc $r3,#0x2,6cfc <lfs_dir_compact+0x46c>
    6ce8:	b4 00       	lwi450 $r0,[$r0]
    6cea:	c0 1b       	beqz38 $r0,6d20 <lfs_dir_compact+0x490>
    6cec:	a0 c2       	lwi333 $r3,[$r0+#0x8]
    6cee:	db f4       	bnes38 $r3,6cd6 <lfs_dir_compact+0x446>
    6cf0:	b4 69       	lwi450 $r3,[$r9]
    6cf2:	a8 c2       	swi333 $r3,[$r0+#0x8]
    6cf4:	04 34 80 01 	lwi $r3,[$r9+#0x4]
    6cf8:	a8 c3       	swi333 $r3,[$r0+#0xc]
    6cfa:	d5 f4       	j8 6ce2 <lfs_dir_compact+0x452>
    6cfc:	04 30 00 0b 	lwi $r3,[$r0+#0x2c]
    6d00:	d3 08       	beqs38 $r3,6d10 <lfs_dir_compact+0x480>
    6d02:	04 40 00 0c 	lwi $r4,[$r0+#0x30]
    6d06:	4c 22 00 05 	beq $r2,$r4,6d10 <lfs_dir_compact+0x480>
    6d0a:	d4 03       	beqs38 $r4,6d10 <lfs_dir_compact+0x480>
    6d0c:	4c 21 ff ee 	bne $r2,$r3,6ce8 <lfs_dir_compact+0x458>
    6d10:	b4 69       	lwi450 $r3,[$r9]
    6d12:	14 30 00 0b 	swi $r3,[$r0+#0x2c]
    6d16:	04 34 80 01 	lwi $r3,[$r9+#0x4]
    6d1a:	14 30 00 0c 	swi $r3,[$r0+#0x30]
    6d1e:	d5 e5       	j8 6ce8 <lfs_dir_compact+0x458>
    6d20:	6a 23 00 01 	fmfsr $r2,$fs6
    6d24:	80 08       	mov55 $r0,$r8
    6d26:	b0 48       	addri36.sp $r1,#0x20
    6d28:	49 ff ed c2 	jal 48ac <lfs_fs_parent>
    6d2c:	80 c0       	mov55 $r6,$r0
    6d2e:	4e 05 00 4d 	bltz $r0,6dc8 <lfs_dir_compact+0x538>
    6d32:	51 c4 00 30 	addi $fp,$r8,#0x30
    6d36:	84 21       	movi55 $r1,#0x1
    6d38:	50 0e 00 00 	addi $r0,$fp,#0x0
    6d3c:	49 ff ef 6e 	jal 4c18 <lfs_fs_preporphans.isra.14>
    6d40:	04 14 00 0c 	lwi $r1,[$r8+#0x30]
    6d44:	80 86       	mov55 $r4,$r6
    6d46:	40 50 d0 09 	srli $r5,$r1,#0x14
    6d4a:	54 52 87 00 	andi $r5,$r5,#0x700
    6d4e:	c5 11       	beqz38 $r5,6d70 <lfs_dir_compact+0x4e0>
    6d50:	04 54 00 0d 	lwi $r5,[$r8+#0x34]
    6d54:	f2 14       	lwi37.sp $r2,[+#0x50]
    6d56:	4c 51 00 bd 	beq $r5,$r2,6ed0 <lfs_dir_compact+0x640>
    6d5a:	04 34 00 0e 	lwi $r3,[$r8+#0x38]
    6d5e:	f0 15       	lwi37.sp $r0,[+#0x54]
    6d60:	4c 30 00 bc 	beq $r3,$r0,6ed8 <lfs_dir_compact+0x648>
    6d64:	4c 50 00 ba 	beq $r5,$r0,6ed8 <lfs_dir_compact+0x648>
    6d68:	4c 21 80 b8 	beq $r2,$r3,6ed8 <lfs_dir_compact+0x648>
    6d6c:	80 86       	mov55 $r4,$r6
    6d6e:	84 a0       	movi55 $r5,#0x0
    6d70:	f5 90       	swi37.sp $r5,[+#0x40]
    6d72:	b0 90       	addri36.sp $r2,#0x40
    6d74:	84 a0       	movi55 $r5,#0x0
    6d76:	6a 13 00 01 	fmfsr $r1,$fs6
    6d7a:	80 08       	mov55 $r0,$r8
    6d7c:	84 62       	movi55 $r3,#0x2
    6d7e:	a9 51       	swi333 $r5,[$r2+#0x4]
    6d80:	a9 12       	swi333 $r4,[$r2+#0x8]
    6d82:	14 91 00 03 	swi $r9,[$r2+#0xc]
    6d86:	49 00 00 e7 	jal 6f54 <lfs_dir_commit>
    6d8a:	82 00       	mov55 $r16,$r0
    6d8c:	4e 03 fd f0 	bnez $r0,696c <lfs_dir_compact+0xdc>
    6d90:	80 1c       	mov55 $r0,$fp
    6d92:	84 3f       	movi55 $r1,#-1
    6d94:	49 ff ef 42 	jal 4c18 <lfs_fs_preporphans.isra.14>
    6d98:	6a 23 00 01 	fmfsr $r2,$fs6
    6d9c:	80 08       	mov55 $r0,$r8
    6d9e:	b0 48       	addri36.sp $r1,#0x20
    6da0:	49 ff ed cc 	jal 4938 <lfs_fs_pred>
    6da4:	c0 1a       	beqz38 $r0,6dd8 <lfs_dir_compact+0x548>
    6da6:	82 00       	mov55 $r16,$r0
    6da8:	5a 07 fe 04 	beqc $r0,#-2,6db0 <lfs_dir_compact+0x520>
    6dac:	48 ff fd e0 	j 696c <lfs_dir_compact+0xdc>
    6db0:	86 00       	movi55 $r16,#0x0
    6db2:	48 ff fd dd 	j 696c <lfs_dir_compact+0xdc>
    6db6:	b4 09       	lwi450 $r0,[$r9]
    6db8:	14 04 00 08 	swi $r0,[$r8+#0x20]
    6dbc:	04 04 80 01 	lwi $r0,[$r9+#0x4]
    6dc0:	14 04 00 09 	swi $r0,[$r8+#0x24]
    6dc4:	48 ff ff 84 	j 6ccc <lfs_dir_compact+0x43c>
    6dc8:	51 00 00 00 	addi $r16,$r0,#0x0
    6dcc:	5a 07 fe 04 	beqc $r0,#-2,6dd4 <lfs_dir_compact+0x544>
    6dd0:	48 ff fd ce 	j 696c <lfs_dir_compact+0xdc>
    6dd4:	d5 e2       	j8 6d98 <lfs_dir_compact+0x508>
    6dd6:	92 00       	nop16
    6dd8:	04 04 00 0c 	lwi $r0,[$r8+#0x30]
    6ddc:	40 10 50 09 	srli $r1,$r0,#0x14
    6de0:	54 10 87 00 	andi $r1,$r1,#0x700
    6de4:	c1 0e       	beqz38 $r1,6e00 <lfs_dir_compact+0x570>
    6de6:	04 54 00 0d 	lwi $r5,[$r8+#0x34]
    6dea:	f2 14       	lwi37.sp $r2,[+#0x50]
    6dec:	d2 2a       	beqs38 $r2,6e40 <lfs_dir_compact+0x5b0>
    6dee:	04 34 00 0e 	lwi $r3,[$r8+#0x38]
    6df2:	f1 15       	lwi37.sp $r1,[+#0x54]
    6df4:	4c 30 80 2a 	beq $r3,$r1,6e48 <lfs_dir_compact+0x5b8>
    6df8:	d1 28       	beqs38 $r1,6e48 <lfs_dir_compact+0x5b8>
    6dfa:	4c 21 80 27 	beq $r2,$r3,6e48 <lfs_dir_compact+0x5b8>
    6dfe:	92 00       	nop16
    6e00:	6a 03 00 01 	fmfsr $r0,$fs6
    6e04:	b0 8c       	addri36.sp $r2,#0x30
    6e06:	00 40 00 17 	lbi $r4,[$r0+#0x17]
    6e0a:	46 00 00 ff 	sethi $r0,#0xff
    6e0e:	50 42 06 00 	addi $r4,$r4,#0x600
    6e12:	50 00 0c 08 	addi $r0,$r0,#0xc08
    6e16:	40 42 50 08 	slli $r4,$r4,#0x14
    6e1a:	ff 07       	or33 $r4,$r0
    6e1c:	84 a0       	movi55 $r5,#0x0
    6e1e:	6a 13 00 01 	fmfsr $r1,$fs6
    6e22:	80 08       	mov55 $r0,$r8
    6e24:	84 62       	movi55 $r3,#0x2
    6e26:	a9 51       	swi333 $r5,[$r2+#0x4]
    6e28:	a9 12       	swi333 $r4,[$r2+#0x8]
    6e2a:	14 91 00 03 	swi $r9,[$r2+#0xc]
    6e2e:	14 bf 80 0c 	swi $r11,[$sp+#0x30]
    6e32:	49 00 00 91 	jal 6f54 <lfs_dir_commit>
    6e36:	82 00       	mov55 $r16,$r0
    6e38:	4e 03 fd 9a 	bnez $r0,696c <lfs_dir_compact+0xdc>
    6e3c:	d5 ba       	j8 6db0 <lfs_dir_compact+0x520>
    6e3e:	92 00       	nop16
    6e40:	6a 13 00 01 	fmfsr $r1,$fs6
    6e44:	04 10 80 01 	lwi $r1,[$r1+#0x4]
    6e48:	40 00 30 08 	slli $r0,$r0,#0xc
    6e4c:	40 60 58 09 	srli $r6,$r0,#0x16
    6e50:	44 00 0f ef 	movi $r0,#0xfef
    6e54:	f0 81       	swi37.sp $r0,[+#0x4]
    6e56:	f2 82       	swi37.sp $r2,[+#0x8]
    6e58:	f1 83       	swi37.sp $r1,[+#0xc]
    6e5a:	14 ef 80 00 	swi $r14,[$sp+#0x0]
    6e5e:	f6 84       	swi37.sp $r6,[+#0x10]
    6e60:	14 cf 80 05 	swi $r12,[$sp+#0x14]
    6e64:	44 00 3c 6c 	movi $r0,#0x3c6c
    6e68:	49 ff da ea 	jal 243c <printf>
    6e6c:	04 24 00 0c 	lwi $r2,[$r8+#0x30]
    6e70:	46 08 00 00 	sethi $r0,#0x80000
    6e74:	50 00 03 ff 	addi $r0,$r0,#0x3ff
    6e78:	84 20       	movi55 $r1,#0x0
    6e7a:	fe 16       	and33 $r0,$r2
    6e7c:	14 04 00 0c 	swi $r0,[$r8+#0x30]
    6e80:	14 14 00 0d 	swi $r1,[$r8+#0x34]
    6e84:	14 14 00 0e 	swi $r1,[$r8+#0x38]
    6e88:	5a 63 ff bc 	beqc $r6,#0x3ff,6e00 <lfs_dir_compact+0x570>
    6e8c:	40 63 28 08 	slli $r6,$r6,#0xa
    6e90:	46 b4 ff 00 	sethi $r11,#0x4ff00
    6e94:	40 b3 2c 04 	or $r11,$r6,$r11
    6e98:	d5 b4       	j8 6e00 <lfs_dir_compact+0x570>
    6e9a:	92 00       	nop16
    6e9c:	46 27 ff ff 	sethi $r2,#0x7ffff
    6ea0:	6a 13 00 01 	fmfsr $r1,$fs6
    6ea4:	80 08       	mov55 $r0,$r8
    6ea6:	50 21 0c 0c 	addi $r2,$r2,#0xc0c
    6eaa:	b0 d0       	addri36.sp $r3,#0x40
    6eac:	49 ff f1 08 	jal 50bc <lfs_dir_commitattr>
    6eb0:	4e 03 fd d0 	bnez $r0,6a50 <lfs_dir_compact+0x1c0>
    6eb4:	48 ff fe 90 	j 6bd4 <lfs_dir_compact+0x344>
    6eb8:	44 00 36 d4 	movi $r0,#0x36d4
    6ebc:	44 10 06 83 	movi $r1,#0x683
    6ec0:	44 20 7c 34 	movi $r2,#0x7c34
    6ec4:	44 30 3c 44 	movi $r3,#0x3c44
    6ec8:	49 00 16 aa 	jal 9c1c <__assert_func>
    6ecc:	92 00       	nop16
    6ece:	92 00       	nop16
    6ed0:	6a 03 00 01 	fmfsr $r0,$fs6
    6ed4:	04 00 00 01 	lwi $r0,[$r0+#0x4]
    6ed8:	46 70 00 ff 	sethi $r7,#0xff
    6edc:	50 73 8c 00 	addi $r7,$r7,#0xc00
    6ee0:	fe 7e       	and33 $r1,$r7
    6ee2:	40 a0 a8 09 	srli $r10,$r1,#0xa
    6ee6:	44 10 0f cb 	movi $r1,#0xfcb
    6eea:	f1 81       	swi37.sp $r1,[+#0x4]
    6eec:	f2 82       	swi37.sp $r2,[+#0x8]
    6eee:	f0 83       	swi37.sp $r0,[+#0xc]
    6ef0:	14 ef 80 00 	swi $r14,[$sp+#0x0]
    6ef4:	14 af 80 04 	swi $r10,[$sp+#0x10]
    6ef8:	14 cf 80 05 	swi $r12,[$sp+#0x14]
    6efc:	44 00 3c 6c 	movi $r0,#0x3c6c
    6f00:	49 ff da 9e 	jal 243c <printf>
    6f04:	40 13 1c 02 	and $r1,$r6,$r7
    6f08:	04 54 00 0c 	lwi $r5,[$r8+#0x30]
    6f0c:	92 2a       	srli45 $r1,#0xa
    6f0e:	46 28 00 00 	sethi $r2,#0x80000
    6f12:	40 05 00 13 	zeh $r0,$r10
    6f16:	96 49       	zeh33 $r1,$r1
    6f18:	50 21 03 ff 	addi $r2,$r2,#0x3ff
    6f1c:	84 60       	movi55 $r3,#0x0
    6f1e:	fe ae       	and33 $r2,$r5
    6f20:	40 10 04 06 	slt $r1,$r0,$r1
    6f24:	80 86       	mov55 $r4,$r6
    6f26:	14 24 00 0c 	swi $r2,[$r8+#0x30]
    6f2a:	14 34 00 0d 	swi $r3,[$r8+#0x34]
    6f2e:	14 34 00 0e 	swi $r3,[$r8+#0x38]
    6f32:	c1 0b       	beqz38 $r1,6f48 <lfs_dir_compact+0x6b8>
    6f34:	50 43 7c 00 	addi $r4,$r6,#-1024
    6f38:	40 a5 28 08 	slli $r10,$r10,#0xa
    6f3c:	46 54 ff 00 	sethi $r5,#0x4ff00
    6f40:	40 55 14 04 	or $r5,$r10,$r5
    6f44:	48 ff ff 16 	j 6d70 <lfs_dir_compact+0x4e0>
    6f48:	84 a0       	movi55 $r5,#0x0
    6f4a:	5a 0b ff f7 	bnec $r0,#0x3ff,6f38 <lfs_dir_compact+0x6a8>
    6f4e:	48 ff ff 11 	j 6d70 <lfs_dir_compact+0x4e0>
    6f52:	92 00       	nop16

00006f54 <lfs_dir_commit>:
    6f54:	3a 6f b4 bc 	smw.adm $r6,[$sp],$r13,#0x2    ! {$r6~$r13, $lp}
    6f58:	ef 84       	addi10.sp #-124
    6f5a:	04 60 00 0a 	lwi $r6,[$r0+#0x28]
    6f5e:	81 00       	mov55 $r8,$r0
    6f60:	80 e1       	mov55 $r7,$r1
    6f62:	81 42       	mov55 $r10,$r2
    6f64:	81 83       	mov55 $r12,$r3
    6f66:	b5 21       	lwi450 $r9,[$r1]
    6f68:	46 b0 01 00 	sethi $r11,#0x100
    6f6c:	ce 0c       	bnez38 $r6,6f84 <lfs_dir_commit+0x30>
    6f6e:	d5 41       	j8 6ff0 <lfs_dir_commit+0x9c>
    6f70:	a1 73       	lwi333 $r5,[$r6+#0xc]
    6f72:	a0 39       	lwi333 $r0,[$r7+#0x4]
    6f74:	d0 0f       	beqs38 $r0,6f92 <lfs_dir_commit+0x3e>
    6f76:	4c 10 00 0e 	beq $r1,$r0,6f92 <lfs_dir_commit+0x3e>
    6f7a:	4c 92 80 0c 	beq $r9,$r5,6f92 <lfs_dir_commit+0x3e>
    6f7e:	b4 c6       	lwi450 $r6,[$r6]
    6f80:	4e 62 00 38 	beqz $r6,6ff0 <lfs_dir_commit+0x9c>
    6f84:	50 13 00 08 	addi $r1,$r6,#0x8
    6f88:	4c 70 bf fb 	beq $r7,$r1,6f7e <lfs_dir_commit+0x2a>
    6f8c:	a0 72       	lwi333 $r1,[$r6+#0x8]
    6f8e:	4c 90 ff f1 	bne $r9,$r1,6f70 <lfs_dir_commit+0x1c>
    6f92:	a6 36       	lbi333 $r0,[$r6+#0x6]
    6f94:	5a 08 01 f5 	bnec $r0,#0x1,6f7e <lfs_dir_commit+0x2a>
    6f98:	04 03 00 0c 	lwi $r0,[$r6+#0x30]
    6f9c:	40 00 2c 02 	and $r0,$r0,$r11
    6fa0:	c0 ef       	beqz38 $r0,6f7e <lfs_dir_commit+0x2a>
    6fa2:	04 14 00 1a 	lwi $r1,[$r8+#0x68]
    6fa6:	04 23 00 0b 	lwi $r2,[$r6+#0x2c]
    6faa:	04 00 80 0a 	lwi $r0,[$r1+#0x28]
    6fae:	e2 02       	slt45 $r0,$r2
    6fb0:	e8 e7       	beqzs8 6f7e <lfs_dir_commit+0x2a>
    6fb2:	04 03 00 0d 	lwi $r0,[$r6+#0x34]
    6fb6:	04 10 80 08 	lwi $r1,[$r1+#0x20]
    6fba:	14 03 00 0f 	swi $r0,[$r6+#0x3c]
    6fbe:	14 14 00 18 	swi $r1,[$r8+#0x60]
    6fc2:	80 08       	mov55 $r0,$r8
    6fc4:	50 13 00 00 	addi $r1,$r6,#0x0
    6fc8:	49 ff f7 e0 	jal 5f88 <lfs_file_relocate>
    6fcc:	4e 03 00 bc 	bnez $r0,7144 <lfs_dir_commit+0x1f0>
    6fd0:	04 13 00 0c 	lwi $r1,[$r6+#0x30]
    6fd4:	80 08       	mov55 $r0,$r8
    6fd6:	42 10 d0 09 	bclr $r1,$r1,#0x14
    6fda:	14 13 00 0c 	swi $r1,[$r6+#0x30]
    6fde:	80 26       	mov55 $r1,$r6
    6fe0:	49 ff fa b4 	jal 6548 <lfs_file_flush>
    6fe4:	4e 03 00 b0 	bnez $r0,7144 <lfs_dir_commit+0x1f0>
    6fe8:	b4 c6       	lwi450 $r6,[$r6]
    6fea:	b5 27       	lwi450 $r9,[$r7]
    6fec:	ce cc       	bnez38 $r6,6f84 <lfs_dir_commit+0x30>
    6fee:	92 00       	nop16
    6ff0:	3b 03 dc 00 	lmw.bi $r16,[$r7],$r23,#0x0    ! {$r16~$r23}
    6ff4:	b1 8e       	addri36.sp $r6,#0x38
    6ff6:	3b 03 5c 20 	smw.bi $r16,[$r6],$r23,#0x0    ! {$r16~$r23}
    6ffa:	81 71       	mov55 $r11,$r17
    6ffc:	4e c7 00 30 	blez $r12,705c <lfs_dir_commit+0x108>
    7000:	82 0a       	mov55 $r16,$r10
    7002:	86 40       	movi55 $r18,#0x0
    7004:	85 e0       	movi55 $r15,#0x0
    7006:	46 37 ff 00 	sethi $r3,#0x7ff00
    700a:	44 20 04 01 	movi $r2,#0x401
    700e:	44 40 04 ff 	movi $r4,#0x4ff
    7012:	47 17 00 00 	sethi $r17,#0x70000
    7016:	44 50 06 00 	movi $r5,#0x600
    701a:	d5 0c       	j8 7032 <lfs_dir_commit+0xde>
    701c:	4c 12 00 98 	beq $r1,$r4,714c <lfs_dir_commit+0x1f8>
    7020:	40 09 c4 02 	and $r0,$r19,$r17
    7024:	92 14       	srli45 $r0,#0x14
    7026:	4c 02 80 9d 	beq $r0,$r5,7160 <lfs_dir_commit+0x20c>
    702a:	8d c1       	addi45 $r18,#0x1
    702c:	8d 88       	addi45 $r16,#0x8
    702e:	4d 26 00 11 	beq $r18,$r12,7050 <lfs_dir_commit+0xfc>
    7032:	b5 f0       	lwi450 $r19,[$r16]
    7034:	40 19 8c 02 	and $r1,$r19,$r3
    7038:	92 34       	srli45 $r1,#0x14
    703a:	4c 11 7f f1 	bne $r1,$r2,701c <lfs_dir_commit+0xc8>
    703e:	02 03 80 0a 	lhi $r0,[$r7+#0x14]
    7042:	8d c1       	addi45 $r18,#0x1
    7044:	8c 01       	addi45 $r0,#0x1
    7046:	12 03 80 0a 	shi $r0,[$r7+#0x14]
    704a:	8d 88       	addi45 $r16,#0x8
    704c:	4d 26 7f f3 	bne $r18,$r12,7032 <lfs_dir_commit+0xde>
    7050:	e8 06       	beqzs8 705c <lfs_dir_commit+0x108>
    7052:	02 03 80 0a 	lhi $r0,[$r7+#0x14]
    7056:	4e 02 01 34 	beqz $r0,72be <lfs_dir_commit+0x36a>
    705a:	92 00       	nop16
    705c:	00 03 80 16 	lbi $r0,[$r7+#0x16]
    7060:	c8 07       	bnez38 $r0,706e <lfs_dir_commit+0x11a>
    7062:	02 03 80 0a 	lhi $r0,[$r7+#0x14]
    7066:	5c f0 00 ff 	slti $r15,$r0,#0xff
    706a:	4e f3 00 89 	bnez $r15,717c <lfs_dir_commit+0x228>
    706e:	b4 27       	lwi450 $r1,[$r7]
    7070:	a0 bb       	lwi333 $r2,[$r7+#0xc]
    7072:	04 04 00 1a 	lwi $r0,[$r8+#0x68]
    7076:	a0 fc       	lwi333 $r3,[$r7+#0x10]
    7078:	50 df 80 58 	addi $r13,$sp,#0x58
    707c:	f1 96       	swi37.sp $r1,[+#0x58]
    707e:	84 3f       	movi55 $r1,#-1
    7080:	14 16 80 03 	swi $r1,[$r13+#0xc]
    7084:	14 26 80 01 	swi $r2,[$r13+#0x4]
    7088:	14 36 80 02 	swi $r3,[$r13+#0x8]
    708c:	14 26 80 04 	swi $r2,[$r13+#0x10]
    7090:	05 00 00 07 	lwi $r16,[$r0+#0x1c]
    7094:	84 00       	movi55 $r0,#0x0
    7096:	b6 1f       	swi450 $r0,[$sp]
    7098:	f0 81       	swi37.sp $r0,[+#0x4]
    709a:	f0 82       	swi37.sp $r0,[+#0x8]
    709c:	f0 83       	swi37.sp $r0,[+#0xc]
    709e:	f0 84       	swi37.sp $r0,[+#0x10]
    70a0:	51 1f 80 24 	addi $r17,$sp,#0x24
    70a4:	44 00 51 78 	movi $r0,#0x5178
    70a8:	8f 88       	subi45 $r16,#0x8
    70aa:	f0 85       	swi37.sp $r0,[+#0x14]
    70ac:	15 1f 80 06 	swi $r17,[$sp+#0x18]
    70b0:	80 08       	mov55 $r0,$r8
    70b2:	80 27       	mov55 $r1,$r7
    70b4:	80 8a       	mov55 $r4,$r10
    70b6:	80 ac       	mov55 $r5,$r12
    70b8:	15 06 80 05 	swi $r16,[$r13+#0x14]
    70bc:	14 8f 80 09 	swi $r8,[$sp+#0x24]
    70c0:	14 df 80 0a 	swi $r13,[$sp+#0x28]
    70c4:	49 ff ec 80 	jal 49c4 <lfs_dir_traverse>
    70c8:	c8 32       	bnez38 $r0,712c <lfs_dir_commit+0x1d8>
    70ca:	84 20       	movi55 $r1,#0x0
    70cc:	84 4c       	movi55 $r2,#0xc
    70ce:	b0 0b       	addri36.sp $r0,#0x2c
    70d0:	49 00 17 76 	jal 9fbc <memset>
    70d4:	04 24 00 0c 	lwi $r2,[$r8+#0x30]
    70d8:	04 54 00 0f 	lwi $r5,[$r8+#0x3c]
    70dc:	05 14 00 11 	lwi $r17,[$r8+#0x44]
    70e0:	04 14 00 0e 	lwi $r1,[$r8+#0x38]
    70e4:	04 04 00 12 	lwi $r0,[$r8+#0x48]
    70e8:	05 04 00 10 	lwi $r16,[$r8+#0x40]
    70ec:	04 34 00 0d 	lwi $r3,[$r8+#0x34]
    70f0:	ff 55       	xor33 $r5,$r2
    70f2:	04 44 00 13 	lwi $r4,[$r8+#0x4c]
    70f6:	04 24 00 14 	lwi $r2,[$r8+#0x50]
    70fa:	40 18 84 03 	xor $r1,$r17,$r1
    70fe:	fe 2d       	xor33 $r0,$r5
    7100:	40 38 0c 03 	xor $r3,$r16,$r3
    7104:	fe e5       	xor33 $r3,$r4
    7106:	fe 55       	xor33 $r1,$r2
    7108:	66 00 03 ff 	bitci $r0,$r0,#0x3ff
    710c:	f3 8c       	swi37.sp $r3,[+#0x30]
    710e:	f1 8d       	swi37.sp $r1,[+#0x34]
    7110:	f0 8b       	swi37.sp $r0,[+#0x2c]
    7112:	4e 03 01 0d 	bnez $r0,732c <lfs_dir_commit+0x3d8>
    7116:	4e 33 01 0b 	bnez $r3,732c <lfs_dir_commit+0x3d8>
    711a:	4e 13 01 09 	bnez $r1,732c <lfs_dir_commit+0x3d8>
    711e:	80 08       	mov55 $r0,$r8
    7120:	50 16 80 00 	addi $r1,$r13,#0x0
    7124:	49 ff f0 30 	jal 5184 <lfs_dir_commitcrc>
    7128:	4e 02 00 d8 	beqz $r0,72d8 <lfs_dir_commit+0x384>
    712c:	5a 07 e4 26 	beqc $r0,#-28,7178 <lfs_dir_commit+0x224>
    7130:	5a 07 ac 24 	beqc $r0,#-84,7178 <lfs_dir_commit+0x224>
    7134:	14 9f 80 0e 	swi $r9,[$sp+#0x38]
    7138:	14 bf 80 0f 	swi $r11,[$sp+#0x3c]
    713c:	3b 03 5c 00 	lmw.bi $r16,[$r6],$r23,#0x0    ! {$r16~$r23}
    7140:	3b 03 dc 20 	smw.bi $r16,[$r7],$r23,#0x0    ! {$r16~$r23}
    7144:	ec 7c       	addi10.sp #0x7c
    7146:	3a 6f b4 84 	lmw.bim $r6,[$sp],$r13,#0x2    ! {$r6~$r13, $lp}
    714a:	dd 9e       	ret5 $lp
    714c:	02 03 80 0a 	lhi $r0,[$r7+#0x14]
    7150:	4e 02 01 04 	beqz $r0,7358 <lfs_dir_commit+0x404>
    7154:	8e 01       	subi45 $r0,#0x1
    7156:	12 03 80 0a 	shi $r0,[$r7+#0x14]
    715a:	85 e1       	movi55 $r15,#0x1
    715c:	48 ff ff 67 	j 702a <lfs_dir_commit+0xd6>
    7160:	04 08 00 01 	lwi $r0,[$r16+#0x4]
    7164:	43 39 d0 0b 	btst $r19,$r19,#0x14
    7168:	b4 20       	lwi450 $r1,[$r0]
    716a:	a8 7e       	swi333 $r1,[$r7+#0x18]
    716c:	a0 01       	lwi333 $r0,[$r0+#0x4]
    716e:	a8 3f       	swi333 $r0,[$r7+#0x1c]
    7170:	11 33 80 17 	sbi $r19,[$r7+#0x17]
    7174:	48 ff ff 5b 	j 702a <lfs_dir_commit+0xd6>
    7178:	02 03 80 0a 	lhi $r0,[$r7+#0x14]
    717c:	84 3f       	movi55 $r1,#-1
    717e:	14 14 00 04 	swi $r1,[$r8+#0x10]
    7182:	80 4a       	mov55 $r2,$r10
    7184:	b6 1f       	swi450 $r0,[$sp]
    7186:	80 27       	mov55 $r1,$r7
    7188:	80 08       	mov55 $r0,$r8
    718a:	80 6c       	mov55 $r3,$r12
    718c:	80 87       	mov55 $r4,$r7
    718e:	84 a0       	movi55 $r5,#0x0
    7190:	49 ff fb 80 	jal 6890 <lfs_dir_compact>
    7194:	c8 d0       	bnez38 $r0,7134 <lfs_dir_commit+0x1e0>
    7196:	92 00       	nop16
    7198:	04 64 00 0a 	lwi $r6,[$r8+#0x28]
    719c:	80 06       	mov55 $r0,$r6
    719e:	c6 2b       	beqz38 $r6,71f4 <lfs_dir_commit+0x2a0>
    71a0:	47 80 00 ff 	sethi $r24,#0xff
    71a4:	46 47 ff 00 	sethi $r4,#0x7ff00
    71a8:	44 30 04 ff 	movi $r3,#0x4ff
    71ac:	51 8c 0c 00 	addi $r24,$r24,#0xc00
    71b0:	87 3f       	movi55 $r25,#-1
    71b2:	44 50 04 01 	movi $r5,#0x401
    71b6:	92 00       	nop16
    71b8:	50 10 00 08 	addi $r1,$r0,#0x8
    71bc:	4c 70 80 0d 	beq $r7,$r1,71d6 <lfs_dir_commit+0x282>
    71c0:	a0 82       	lwi333 $r2,[$r0+#0x8]
    71c2:	4c 24 80 1f 	beq $r2,$r9,7200 <lfs_dir_commit+0x2ac>
    71c6:	05 00 00 03 	lwi $r16,[$r0+#0xc]
    71ca:	4d 05 80 1b 	beq $r16,$r11,7200 <lfs_dir_commit+0x2ac>
    71ce:	4c 25 80 19 	beq $r2,$r11,7200 <lfs_dir_commit+0x2ac>
    71d2:	4d 04 80 17 	beq $r16,$r9,7200 <lfs_dir_commit+0x2ac>
    71d6:	b4 00       	lwi450 $r0,[$r0]
    71d8:	c8 f0       	bnez38 $r0,71b8 <lfs_dir_commit+0x264>
    71da:	84 e0       	movi55 $r7,#0x0
    71dc:	a0 32       	lwi333 $r0,[$r6+#0x8]
    71de:	4c 04 80 53 	beq $r0,$r9,7284 <lfs_dir_commit+0x330>
    71e2:	a0 73       	lwi333 $r1,[$r6+#0xc]
    71e4:	4c 15 80 50 	beq $r1,$r11,7284 <lfs_dir_commit+0x330>
    71e8:	4c 05 80 4e 	beq $r0,$r11,7284 <lfs_dir_commit+0x330>
    71ec:	4c 14 80 4c 	beq $r1,$r9,7284 <lfs_dir_commit+0x330>
    71f0:	b4 c6       	lwi450 $r6,[$r6]
    71f2:	ce f5       	bnez38 $r6,71dc <lfs_dir_commit+0x288>
    71f4:	84 00       	movi55 $r0,#0x0
    71f6:	ec 7c       	addi10.sp #0x7c
    71f8:	3a 6f b4 84 	lmw.bim $r6,[$sp],$r13,#0x2    ! {$r6~$r13, $lp}
    71fc:	dd 9e       	ret5 $lp
    71fe:	92 00       	nop16
    7200:	3b 03 dc 00 	lmw.bi $r16,[$r7],$r23,#0x0    ! {$r16~$r23}
    7204:	3b 00 dc 20 	smw.bi $r16,[$r1],$r23,#0x0    ! {$r16~$r23}
    7208:	86 40       	movi55 $r18,#0x0
    720a:	4e c6 00 09 	bgtz $r12,721c <lfs_dir_commit+0x2c8>
    720e:	d5 e4       	j8 71d6 <lfs_dir_commit+0x282>
    7210:	4d 02 80 22 	beq $r16,$r5,7254 <lfs_dir_commit+0x300>
    7214:	8d c1       	addi45 $r18,#0x1
    7216:	4d 26 3f e0 	beq $r18,$r12,71d6 <lfs_dir_commit+0x282>
    721a:	92 00       	nop16
    721c:	38 15 4b 02 	lw $r1,[$r10+($r18<<#0x3)]
    7220:	41 00 90 02 	and $r16,$r1,$r4
    7224:	93 94       	srli45 $r16,#0x14
    7226:	4d 01 ff f5 	bne $r16,$r3,7210 <lfs_dir_commit+0x2bc>
    722a:	40 10 e0 02 	and $r1,$r1,$r24
    722e:	92 2a       	srli45 $r1,#0xa
    7230:	a4 82       	lhi333 $r2,[$r0+#0x4]
    7232:	96 49       	zeh33 $r1,$r1
    7234:	4c 20 80 22 	beq $r2,$r1,7278 <lfs_dir_commit+0x324>
    7238:	e2 22       	slt45 $r1,$r2
    723a:	e8 ed       	beqzs8 7214 <lfs_dir_commit+0x2c0>
    723c:	a6 46       	lbi333 $r1,[$r0+#0x6]
    723e:	8e 41       	subi45 $r2,#0x1
    7240:	ac 82       	shi333 $r2,[$r0+#0x4]
    7242:	5a 18 02 e9 	bnec $r1,#0x2,7214 <lfs_dir_commit+0x2c0>
    7246:	04 10 00 0a 	lwi $r1,[$r0+#0x28]
    724a:	8e 21       	subi45 $r1,#0x1
    724c:	14 10 00 0a 	swi $r1,[$r0+#0x28]
    7250:	d5 e2       	j8 7214 <lfs_dir_commit+0x2c0>
    7252:	92 00       	nop16
    7254:	40 10 e0 02 	and $r1,$r1,$r24
    7258:	a4 82       	lhi333 $r2,[$r0+#0x4]
    725a:	92 2a       	srli45 $r1,#0xa
    725c:	96 49       	zeh33 $r1,$r1
    725e:	e2 41       	slt45 $r2,$r1
    7260:	e9 da       	bnezs8 7214 <lfs_dir_commit+0x2c0>
    7262:	a6 46       	lbi333 $r1,[$r0+#0x6]
    7264:	8c 41       	addi45 $r2,#0x1
    7266:	ac 82       	shi333 $r2,[$r0+#0x4]
    7268:	5a 18 02 d6 	bnec $r1,#0x2,7214 <lfs_dir_commit+0x2c0>
    726c:	04 10 00 0a 	lwi $r1,[$r0+#0x28]
    7270:	8c 21       	addi45 $r1,#0x1
    7272:	14 10 00 0a 	swi $r1,[$r0+#0x28]
    7276:	d5 cf       	j8 7214 <lfs_dir_commit+0x2c0>
    7278:	15 90 00 02 	swi $r25,[$r0+#0x8]
    727c:	15 90 00 03 	swi $r25,[$r0+#0xc]
    7280:	d5 ca       	j8 7214 <lfs_dir_commit+0x2c0>
    7282:	92 00       	nop16
    7284:	50 c3 00 08 	addi $r12,$r6,#0x8
    7288:	50 a3 00 20 	addi $r10,$r6,#0x20
    728c:	a4 f2       	lhi333 $r3,[$r6+#0x4]
    728e:	02 03 00 0e 	lhi $r0,[$r6+#0x1c]
    7292:	e2 60       	slt45 $r3,$r0
    7294:	e9 ae       	bnezs8 71f0 <lfs_dir_commit+0x29c>
    7296:	00 43 00 1f 	lbi $r4,[$r6+#0x1f]
    729a:	c4 ab       	beqz38 $r4,71f0 <lfs_dir_commit+0x29c>
    729c:	8a 60       	sub45 $r3,$r0
    729e:	ac f2       	shi333 $r3,[$r6+#0x4]
    72a0:	80 08       	mov55 $r0,$r8
    72a2:	b6 ff       	swi450 $r7,[$sp]
    72a4:	f7 81       	swi37.sp $r7,[+#0x4]
    72a6:	80 2c       	mov55 $r1,$r12
    72a8:	80 4a       	mov55 $r2,$r10
    72aa:	84 7f       	movi55 $r3,#-1
    72ac:	84 9f       	movi55 $r4,#-1
    72ae:	84 a0       	movi55 $r5,#0x0
    72b0:	49 ff e7 f0 	jal 4290 <lfs_dir_fetchmatch>
    72b4:	c0 ec       	beqz38 $r0,728c <lfs_dir_commit+0x338>
    72b6:	ec 7c       	addi10.sp #0x7c
    72b8:	3a 6f b4 84 	lmw.bim $r6,[$sp],$r13,#0x2    ! {$r6~$r13, $lp}
    72bc:	dd 9e       	ret5 $lp
    72be:	80 08       	mov55 $r0,$r8
    72c0:	80 27       	mov55 $r1,$r7
    72c2:	b0 96       	addri36.sp $r2,#0x58
    72c4:	49 ff eb 3a 	jal 4938 <lfs_fs_pred>
    72c8:	4e 02 00 24 	beqz $r0,7310 <lfs_dir_commit+0x3bc>
    72cc:	5a 07 fe 04 	beqc $r0,#-2,72d4 <lfs_dir_commit+0x380>
    72d0:	48 ff ff 32 	j 7134 <lfs_dir_commit+0x1e0>
    72d4:	48 ff fe c4 	j 705c <lfs_dir_commit+0x108>
    72d8:	04 04 00 1a 	lwi $r0,[$r8+#0x68]
    72dc:	04 26 80 01 	lwi $r2,[$r13+#0x4]
    72e0:	a0 06       	lwi333 $r0,[$r0+#0x18]
    72e2:	40 01 00 37 	divr $r0,$r1,$r2,$r0
    72e6:	c9 45       	bnez38 $r1,7370 <lfs_dir_commit+0x41c>
    72e8:	50 04 00 30 	addi $r0,$r8,#0x30
    72ec:	3b 00 48 00 	lmw.bi $r16,[$r0],$r18,#0x0    ! {$r16~$r18}
    72f0:	50 14 00 3c 	addi $r1,$r8,#0x3c
    72f4:	04 36 80 02 	lwi $r3,[$r13+#0x8]
    72f8:	a8 bb       	swi333 $r2,[$r7+#0xc]
    72fa:	a8 fc       	swi333 $r3,[$r7+#0x10]
    72fc:	50 04 00 48 	addi $r0,$r8,#0x48
    7300:	3b 00 c8 20 	smw.bi $r16,[$r1],$r18,#0x0    ! {$r16~$r18}
    7304:	84 4c       	movi55 $r2,#0xc
    7306:	84 20       	movi55 $r1,#0x0
    7308:	49 00 16 5a 	jal 9fbc <memset>
    730c:	48 ff ff 46 	j 7198 <lfs_dir_commit+0x244>
    7310:	00 0f 80 6f 	lbi $r0,[$sp+#0x6f]
    7314:	4e 02 fe a4 	beqz $r0,705c <lfs_dir_commit+0x108>
    7318:	80 08       	mov55 $r0,$r8
    731a:	b0 56       	addri36.sp $r1,#0x58
    731c:	50 23 80 00 	addi $r2,$r7,#0x0
    7320:	49 00 00 34 	jal 7388 <lfs_dir_drop>
    7324:	4e 03 ff 08 	bnez $r0,7134 <lfs_dir_commit+0x1e0>
    7328:	48 ff fe 9a 	j 705c <lfs_dir_commit+0x108>
    732c:	80 08       	mov55 $r0,$r8
    732e:	80 27       	mov55 $r1,$r7
    7330:	50 2f 80 2c 	addi $r2,$sp,#0x2c
    7334:	49 ff f1 64 	jal 55fc <lfs_dir_getgstate>
    7338:	4e 03 fe fe 	bnez $r0,7134 <lfs_dir_commit+0x1e0>
    733c:	46 27 ff ff 	sethi $r2,#0x7ffff
    7340:	80 08       	mov55 $r0,$r8
    7342:	80 2d       	mov55 $r1,$r13
    7344:	50 21 0c 0c 	addi $r2,$r2,#0xc0c
    7348:	50 3f 80 2c 	addi $r3,$sp,#0x2c
    734c:	49 ff ee b8 	jal 50bc <lfs_dir_commitattr>
    7350:	4e 03 fe ee 	bnez $r0,712c <lfs_dir_commit+0x1d8>
    7354:	48 ff fe e5 	j 711e <lfs_dir_commit+0x1ca>
    7358:	44 00 36 d4 	movi $r0,#0x36d4
    735c:	44 10 06 d2 	movi $r1,#0x6d2
    7360:	44 20 7c a0 	movi $r2,#0x7ca0
    7364:	44 30 3d 24 	movi $r3,#0x3d24
    7368:	49 00 14 5a 	jal 9c1c <__assert_func>
    736c:	92 00       	nop16
    736e:	92 00       	nop16
    7370:	44 00 36 d4 	movi $r0,#0x36d4
    7374:	44 10 07 30 	movi $r1,#0x730
    7378:	44 20 7c a0 	movi $r2,#0x7ca0
    737c:	44 30 3c 44 	movi $r3,#0x3c44
    7380:	49 00 14 4e 	jal 9c1c <__assert_func>
    7384:	92 00       	nop16
    7386:	92 00       	nop16

00007388 <lfs_dir_drop>:
    7388:	3a 6f a0 bc 	smw.adm $r6,[$sp],$r8,#0x2    ! {$r6~$r8, $lp}
    738c:	ef f8       	addi10.sp #-8
    738e:	80 c2       	mov55 $r6,$r2
    7390:	81 01       	mov55 $r8,$r1
    7392:	50 20 00 48 	addi $r2,$r0,#0x48
    7396:	80 26       	mov55 $r1,$r6
    7398:	80 e0       	mov55 $r7,$r0
    739a:	49 ff f1 31 	jal 55fc <lfs_dir_getgstate>
    739e:	c8 15       	bnez38 $r0,73c8 <lfs_dir_drop+0x40>
    73a0:	00 43 00 17 	lbi $r4,[$r6+#0x17]
    73a4:	46 00 00 ff 	sethi $r0,#0xff
    73a8:	50 42 06 00 	addi $r4,$r4,#0x600
    73ac:	50 00 0c 08 	addi $r0,$r0,#0xc08
    73b0:	40 42 50 08 	slli $r4,$r4,#0x14
    73b4:	ff 07       	or33 $r4,$r0
    73b6:	8c d8       	addi45 $r6,#0x18
    73b8:	80 07       	mov55 $r0,$r7
    73ba:	80 28       	mov55 $r1,$r8
    73bc:	80 5f       	mov55 $r2,$sp
    73be:	84 61       	movi55 $r3,#0x1
    73c0:	b6 9f       	swi450 $r4,[$sp]
    73c2:	f6 81       	swi37.sp $r6,[+#0x4]
    73c4:	49 ff fd c8 	jal 6f54 <lfs_dir_commit>
    73c8:	ec 08       	addi10.sp #0x8
    73ca:	3a 6f a0 84 	lmw.bim $r6,[$sp],$r8,#0x2    ! {$r6~$r8, $lp}
    73ce:	dd 9e       	ret5 $lp

000073d0 <lfs_fs_forceconsistency>:
    73d0:	3a 6f a8 bc 	smw.adm $r6,[$sp],$r10,#0x2    ! {$r6~$r10, $lp}
    73d4:	ef 68       	addi10.sp #-152
    73d6:	04 10 00 0f 	lwi $r1,[$r0+#0x3c]
    73da:	81 00       	mov55 $r8,$r0
    73dc:	40 00 d0 09 	srli $r0,$r1,#0x14
    73e0:	54 00 07 00 	andi $r0,$r0,#0x700
    73e4:	4e 03 00 82 	bnez $r0,74e8 <lfs_fs_forceconsistency+0x118>
    73e8:	04 04 00 0c 	lwi $r0,[$r8+#0x30]
    73ec:	54 00 03 ff 	andi $r0,$r0,#0x3ff
    73f0:	c0 38       	beqz38 $r0,7460 <lfs_fs_forceconsistency+0x90>
    73f2:	b1 8e       	addri36.sp $r6,#0x38
    73f4:	80 06       	mov55 $r0,$r6
    73f6:	84 20       	movi55 $r1,#0x0
    73f8:	fa 50       	movpi45 $r2,#0x20
    73fa:	49 00 15 e1 	jal 9fbc <memset>
    73fe:	84 01       	movi55 $r0,#0x1
    7400:	10 03 00 17 	sbi $r0,[$r6+#0x17]
    7404:	46 97 ff ff 	sethi $r9,#0x7ffff
    7408:	84 01       	movi55 $r0,#0x1
    740a:	46 a6 00 ff 	sethi $r10,#0x600ff
    740e:	a8 37       	swi333 $r0,[$r6+#0x1c]
    7410:	b1 d6       	addri36.sp $r7,#0x58
    7412:	50 94 8c 00 	addi $r9,$r9,#0xc00
    7416:	50 a5 0c 08 	addi $r10,$r10,#0xc08
    741a:	f0 15       	lwi37.sp $r0,[+#0x54]
    741c:	5a 07 ff 1a 	beqc $r0,#-1,7450 <lfs_fs_forceconsistency+0x80>
    7420:	84 00       	movi55 $r0,#0x0
    7422:	b6 1f       	swi450 $r0,[$sp]
    7424:	f0 81       	swi37.sp $r0,[+#0x4]
    7426:	80 27       	mov55 $r1,$r7
    7428:	80 08       	mov55 $r0,$r8
    742a:	b0 94       	addri36.sp $r2,#0x50
    742c:	84 7f       	movi55 $r3,#-1
    742e:	84 9f       	movi55 $r4,#-1
    7430:	84 a0       	movi55 $r5,#0x0
    7432:	49 ff e7 2f 	jal 4290 <lfs_dir_fetchmatch>
    7436:	c8 53       	bnez38 $r0,74dc <lfs_fs_forceconsistency+0x10c>
    7438:	00 03 00 17 	lbi $r0,[$r6+#0x17]
    743c:	4e 02 00 18 	beqz $r0,746c <lfs_fs_forceconsistency+0x9c>
    7440:	3b 03 dc 00 	lmw.bi $r16,[$r7],$r23,#0x0    ! {$r16~$r23}
    7444:	3b 03 5c 20 	smw.bi $r16,[$r6],$r23,#0x0    ! {$r16~$r23}
    7448:	f0 14       	lwi37.sp $r0,[+#0x50]
    744a:	5a 0f ff e8 	bnec $r0,#-1,741a <lfs_fs_forceconsistency+0x4a>
    744e:	92 00       	nop16
    7450:	04 14 00 0c 	lwi $r1,[$r8+#0x30]
    7454:	50 04 00 30 	addi $r0,$r8,#0x30
    7458:	fe 4a       	neg33 $r1,$r1
    745a:	96 4a       	seb33 $r1,$r1
    745c:	49 ff eb de 	jal 4c18 <lfs_fs_preporphans.isra.14>
    7460:	84 80       	movi55 $r4,#0x0
    7462:	80 04       	mov55 $r0,$r4
    7464:	ec 98       	addi10.sp #0x98
    7466:	3a 6f a8 84 	lmw.bim $r6,[$sp],$r10,#0x2    ! {$r6~$r10, $lp}
    746a:	dd 9e       	ret5 $lp
    746c:	80 08       	mov55 $r0,$r8
    746e:	b0 54       	addri36.sp $r1,#0x50
    7470:	b0 9e       	addri36.sp $r2,#0x78
    7472:	49 ff ea 1d 	jal 48ac <lfs_fs_parent>
    7476:	80 60       	mov55 $r3,$r0
    7478:	4e 05 00 80 	bltz $r0,7578 <lfs_fs_forceconsistency+0x1a8>
    747c:	54 00 03 ff 	andi $r0,$r0,#0x3ff
    7480:	b6 1f       	swi450 $r0,[$sp]
    7482:	b0 5e       	addri36.sp $r1,#0x78
    7484:	80 08       	mov55 $r0,$r8
    7486:	80 49       	mov55 $r2,$r9
    7488:	84 80       	movi55 $r4,#0x0
    748a:	b1 4a       	addri36.sp $r5,#0x28
    748c:	49 ff ef c8 	jal 541c <lfs_dir_getslice>
    7490:	4e 05 00 26 	bltz $r0,74dc <lfs_fs_forceconsistency+0x10c>
    7494:	f5 0a       	lwi37.sp $r5,[+#0x28]
    7496:	f1 14       	lwi37.sp $r1,[+#0x50]
    7498:	4c 50 80 8c 	beq $r5,$r1,75b0 <lfs_fs_forceconsistency+0x1e0>
    749c:	a0 f7       	lwi333 $r3,[$r6+#0x1c]
    749e:	f2 0b       	lwi37.sp $r2,[+#0x2c]
    74a0:	4c 32 80 8e 	beq $r3,$r5,75bc <lfs_fs_forceconsistency+0x1ec>
    74a4:	44 40 36 d4 	movi $r4,#0x36d4
    74a8:	b6 9f       	swi450 $r4,[$sp]
    74aa:	f5 84       	swi37.sp $r5,[+#0x10]
    74ac:	44 40 10 62 	movi $r4,#0x1062
    74b0:	44 00 01 38 	movi $r0,#0x138
    74b4:	f2 85       	swi37.sp $r2,[+#0x14]
    74b6:	f4 81       	swi37.sp $r4,[+#0x4]
    74b8:	f1 82       	swi37.sp $r1,[+#0x8]
    74ba:	f3 83       	swi37.sp $r3,[+#0xc]
    74bc:	f0 86       	swi37.sp $r0,[+#0x18]
    74be:	44 00 3d 94 	movi $r0,#0x3d94
    74c2:	49 ff d7 bd 	jal 243c <printf>
    74c6:	b0 8c       	addri36.sp $r2,#0x30
    74c8:	b1 0a       	addri36.sp $r4,#0x28
    74ca:	80 08       	mov55 $r0,$r8
    74cc:	80 26       	mov55 $r1,$r6
    74ce:	84 61       	movi55 $r3,#0x1
    74d0:	a9 11       	swi333 $r4,[$r2+#0x4]
    74d2:	14 af 80 0c 	swi $r10,[$sp+#0x30]
    74d6:	49 ff fd 3f 	jal 6f54 <lfs_dir_commit>
    74da:	c0 b7       	beqz38 $r0,7448 <lfs_fs_forceconsistency+0x78>
    74dc:	80 80       	mov55 $r4,$r0
    74de:	80 04       	mov55 $r0,$r4
    74e0:	ec 98       	addi10.sp #0x98
    74e2:	3a 6f a8 84 	lmw.bim $r6,[$sp],$r10,#0x2    ! {$r6~$r10, $lp}
    74e6:	dd 9e       	ret5 $lp
    74e8:	46 60 00 ff 	sethi $r6,#0xff
    74ec:	50 63 0c 00 	addi $r6,$r6,#0xc00
    74f0:	04 04 00 11 	lwi $r0,[$r8+#0x44]
    74f4:	44 30 36 d4 	movi $r3,#0x36d4
    74f8:	fe 76       	and33 $r1,$r6
    74fa:	04 24 00 10 	lwi $r2,[$r8+#0x40]
    74fe:	92 2a       	srli45 $r1,#0xa
    7500:	b6 7f       	swi450 $r3,[$sp]
    7502:	f0 83       	swi37.sp $r0,[+#0xc]
    7504:	44 30 10 1a 	movi $r3,#0x101a
    7508:	44 00 01 38 	movi $r0,#0x138
    750c:	f3 81       	swi37.sp $r3,[+#0x4]
    750e:	f2 82       	swi37.sp $r2,[+#0x8]
    7510:	f1 84       	swi37.sp $r1,[+#0x10]
    7512:	f0 85       	swi37.sp $r0,[+#0x14]
    7514:	44 00 3d 34 	movi $r0,#0x3d34
    7518:	49 ff d7 92 	jal 243c <printf>
    751c:	84 00       	movi55 $r0,#0x0
    751e:	b6 1f       	swi450 $r0,[$sp]
    7520:	f0 81       	swi37.sp $r0,[+#0x4]
    7522:	84 9f       	movi55 $r4,#-1
    7524:	80 08       	mov55 $r0,$r8
    7526:	b0 5e       	addri36.sp $r1,#0x78
    7528:	50 24 00 40 	addi $r2,$r8,#0x40
    752c:	84 7f       	movi55 $r3,#-1
    752e:	84 a0       	movi55 $r5,#0x0
    7530:	49 ff e6 b0 	jal 4290 <lfs_dir_fetchmatch>
    7534:	80 80       	mov55 $r4,$r0
    7536:	c8 d4       	bnez38 $r0,74de <lfs_fs_forceconsistency+0x10e>
    7538:	04 24 00 0c 	lwi $r2,[$r8+#0x30]
    753c:	04 14 00 0f 	lwi $r1,[$r8+#0x3c]
    7540:	46 08 00 00 	sethi $r0,#0x80000
    7544:	50 00 03 ff 	addi $r0,$r0,#0x3ff
    7548:	fe 16       	and33 $r0,$r2
    754a:	ff 8e       	and33 $r6,$r1
    754c:	b0 88       	addri36.sp $r2,#0x20
    754e:	46 14 ff 00 	sethi $r1,#0x4ff00
    7552:	ff 8f       	or33 $r6,$r1
    7554:	14 04 00 0c 	swi $r0,[$r8+#0x30]
    7558:	14 44 00 0d 	swi $r4,[$r8+#0x34]
    755c:	14 44 00 0e 	swi $r4,[$r8+#0x38]
    7560:	a9 11       	swi333 $r4,[$r2+#0x4]
    7562:	80 08       	mov55 $r0,$r8
    7564:	b0 5e       	addri36.sp $r1,#0x78
    7566:	84 61       	movi55 $r3,#0x1
    7568:	f6 88       	swi37.sp $r6,[+#0x20]
    756a:	49 ff fc f5 	jal 6f54 <lfs_dir_commit>
    756e:	80 80       	mov55 $r4,$r0
    7570:	c8 b7       	bnez38 $r0,74de <lfs_fs_forceconsistency+0x10e>
    7572:	48 ff ff 3b 	j 73e8 <lfs_fs_forceconsistency+0x18>
    7576:	92 00       	nop16
    7578:	5a 0f fe 26 	bnec $r0,#-2,75c4 <lfs_fs_forceconsistency+0x1f4>
    757c:	a0 37       	lwi333 $r0,[$r6+#0x1c]
    757e:	44 20 36 d4 	movi $r2,#0x36d4
    7582:	a0 76       	lwi333 $r1,[$r6+#0x18]
    7584:	b6 5f       	swi450 $r2,[$sp]
    7586:	f0 83       	swi37.sp $r0,[+#0xc]
    7588:	44 20 10 4b 	movi $r2,#0x104b
    758c:	44 00 01 38 	movi $r0,#0x138
    7590:	f2 81       	swi37.sp $r2,[+#0x4]
    7592:	f1 82       	swi37.sp $r1,[+#0x8]
    7594:	f0 84       	swi37.sp $r0,[+#0x10]
    7596:	44 00 3d 64 	movi $r0,#0x3d64
    759a:	49 ff d7 51 	jal 243c <printf>
    759e:	80 08       	mov55 $r0,$r8
    75a0:	80 26       	mov55 $r1,$r6
    75a2:	80 47       	mov55 $r2,$r7
    75a4:	49 ff fe f2 	jal 7388 <lfs_dir_drop>
    75a8:	4e 03 ff 9a 	bnez $r0,74dc <lfs_fs_forceconsistency+0x10c>
    75ac:	48 ff ff 4e 	j 7448 <lfs_fs_forceconsistency+0x78>
    75b0:	f2 0b       	lwi37.sp $r2,[+#0x2c]
    75b2:	f3 15       	lwi37.sp $r3,[+#0x54]
    75b4:	4c 21 ff 76 	bne $r2,$r3,74a0 <lfs_fs_forceconsistency+0xd0>
    75b8:	48 ff ff 44 	j 7440 <lfs_fs_forceconsistency+0x70>
    75bc:	4c 11 7f 74 	bne $r1,$r2,74a4 <lfs_fs_forceconsistency+0xd4>
    75c0:	48 ff ff 40 	j 7440 <lfs_fs_forceconsistency+0x70>
    75c4:	80 80       	mov55 $r4,$r0
    75c6:	48 ff ff 8c 	j 74de <lfs_fs_forceconsistency+0x10e>
    75ca:	92 00       	nop16

000075cc <lfs_file_sync>:
    75cc:	3a 6f 9c bc 	smw.adm $r6,[$sp],$r7,#0x2    ! {$r6~$r7, $lp}
    75d0:	ef e4       	addi10.sp #-28
    75d2:	04 20 80 0c 	lwi $r2,[$r1+#0x30]
    75d6:	80 c1       	mov55 $r6,$r1
    75d8:	42 31 54 0b 	btst $r3,$r2,#0x15
    75dc:	c3 64       	beqz38 $r3,76a4 <lfs_file_sync+0xd8>
    75de:	42 21 4c 0b 	btst $r2,$r2,#0x13
    75e2:	c2 07       	beqz38 $r2,75f0 <lfs_file_sync+0x24>
    75e4:	44 00 00 00 	movi $r0,#0x0
    75e8:	ec 1c       	addi10.sp #0x1c
    75ea:	3a 6f 9c 84 	lmw.bim $r6,[$sp],$r7,#0x2    ! {$r6~$r7, $lp}
    75ee:	dd 9e       	ret5 $lp
    75f0:	80 e0       	mov55 $r7,$r0
    75f2:	49 ff f7 ab 	jal 6548 <lfs_file_flush>
    75f6:	c8 3f       	bnez38 $r0,7674 <lfs_file_sync+0xa8>
    75f8:	04 03 00 0c 	lwi $r0,[$r6+#0x30]
    75fc:	42 10 40 0b 	btst $r1,$r0,#0x10
    7600:	c1 f2       	beqz38 $r1,75e4 <lfs_file_sync+0x18>
    7602:	a0 72       	lwi333 $r1,[$r6+#0x8]
    7604:	5a 17 ff f0 	beqc $r1,#-1,75e4 <lfs_file_sync+0x18>
    7608:	a0 73       	lwi333 $r1,[$r6+#0xc]
    760a:	5a 17 ff ed 	beqc $r1,#-1,75e4 <lfs_file_sync+0x18>
    760e:	42 00 50 0b 	btst $r0,$r0,#0x14
    7612:	c8 3b       	bnez38 $r0,7688 <lfs_file_sync+0xbc>
    7614:	50 13 00 28 	addi $r1,$r6,#0x28
    7618:	3b 00 c4 00 	lmw.bi $r16,[$r1],$r17,#0x0    ! {$r16~$r17}
    761c:	3b 0f c4 20 	smw.bi $r16,[$sp],$r17,#0x0    ! {$r16~$r17}
    7620:	46 12 02 00 	sethi $r1,#0x20200
    7624:	84 a8       	movi55 $r5,#0x8
    7626:	82 1f       	mov55 $r16,$sp
    7628:	04 23 00 14 	lwi $r2,[$r6+#0x50]
    762c:	a4 32       	lhi333 $r0,[$r6+#0x4]
    762e:	a0 d2       	lwi333 $r3,[$r2+#0x8]
    7630:	46 41 02 00 	sethi $r4,#0x10200
    7634:	40 00 28 08 	slli $r0,$r0,#0xa
    7638:	ff 1f       	or33 $r4,$r3
    763a:	05 11 00 01 	lwi $r17,[$r2+#0x4]
    763e:	ff 07       	or33 $r4,$r0
    7640:	b0 82       	addri36.sp $r2,#0x8
    7642:	ff 4f       	or33 $r5,$r1
    7644:	ff 47       	or33 $r5,$r0
    7646:	50 13 00 08 	addi $r1,$r6,#0x8
    764a:	80 07       	mov55 $r0,$r7
    764c:	84 62       	movi55 $r3,#0x2
    764e:	15 01 00 01 	swi $r16,[$r2+#0x4]
    7652:	a9 12       	swi333 $r4,[$r2+#0x8]
    7654:	15 11 00 03 	swi $r17,[$r2+#0xc]
    7658:	14 5f 80 02 	swi $r5,[$sp+#0x8]
    765c:	49 ff fc 7c 	jal 6f54 <lfs_dir_commit>
    7660:	04 13 00 0c 	lwi $r1,[$r6+#0x30]
    7664:	c8 1a       	bnez38 $r0,7698 <lfs_file_sync+0xcc>
    7666:	42 10 c0 09 	bclr $r1,$r1,#0x10
    766a:	84 00       	movi55 $r0,#0x0
    766c:	14 13 00 0c 	swi $r1,[$r6+#0x30]
    7670:	d5 bc       	j8 75e8 <lfs_file_sync+0x1c>
    7672:	92 00       	nop16
    7674:	04 23 00 0c 	lwi $r2,[$r6+#0x30]
    7678:	42 21 4c 08 	bset $r2,$r2,#0x13
    767c:	14 23 00 0c 	swi $r2,[$r6+#0x30]
    7680:	ec 1c       	addi10.sp #0x1c
    7682:	3a 6f 9c 84 	lmw.bim $r6,[$sp],$r7,#0x2    ! {$r6~$r7, $lp}
    7686:	dd 9e       	ret5 $lp
    7688:	05 03 00 13 	lwi $r16,[$r6+#0x4c]
    768c:	04 53 00 0b 	lwi $r5,[$r6+#0x2c]
    7690:	46 12 01 00 	sethi $r1,#0x20100
    7694:	d5 ca       	j8 7628 <lfs_file_sync+0x5c>
    7696:	92 00       	nop16
    7698:	42 10 cc 08 	bset $r1,$r1,#0x13
    769c:	14 13 00 0c 	swi $r1,[$r6+#0x30]
    76a0:	d5 a4       	j8 75e8 <lfs_file_sync+0x1c>
    76a2:	92 00       	nop16
    76a4:	44 00 36 d4 	movi $r0,#0x36d4
    76a8:	44 10 0a b0 	movi $r1,#0xab0
    76ac:	44 20 7c 08 	movi $r2,#0x7c08
    76b0:	44 30 3a 5c 	movi $r3,#0x3a5c
    76b4:	49 00 12 b4 	jal 9c1c <__assert_func>
    76b8:	92 00       	nop16
    76ba:	92 00       	nop16

000076bc <lfs_file_close>:
    76bc:	3a 6f a0 bc 	smw.adm $r6,[$sp],$r8,#0x2    ! {$r6~$r8, $lp}
    76c0:	04 20 80 0c 	lwi $r2,[$r1+#0x30]
    76c4:	80 c1       	mov55 $r6,$r1
    76c6:	42 21 54 0b 	btst $r2,$r2,#0x15
    76ca:	c2 31       	beqz38 $r2,772c <lfs_file_close+0x70>
    76cc:	50 70 00 00 	addi $r7,$r0,#0x0
    76d0:	49 ff ff 7e 	jal 75cc <lfs_file_sync>
    76d4:	04 33 80 0a 	lwi $r3,[$r7+#0x28]
    76d8:	81 00       	mov55 $r8,$r0
    76da:	c3 0b       	beqz38 $r3,76f0 <lfs_file_close+0x34>
    76dc:	4c 61 c0 07 	bne $r6,$r3,76ea <lfs_file_close+0x2e>
    76e0:	d5 16       	j8 770c <lfs_file_close+0x50>
    76e2:	92 00       	nop16
    76e4:	4c 61 00 17 	beq $r6,$r2,7712 <lfs_file_close+0x56>
    76e8:	80 62       	mov55 $r3,$r2
    76ea:	b4 43       	lwi450 $r2,[$r3]
    76ec:	ca fc       	bnez38 $r2,76e4 <lfs_file_close+0x28>
    76ee:	92 00       	nop16
    76f0:	04 03 00 14 	lwi $r0,[$r6+#0x50]
    76f4:	b4 00       	lwi450 $r0,[$r0]
    76f6:	c0 15       	beqz38 $r0,7720 <lfs_file_close+0x64>
    76f8:	04 13 00 0c 	lwi $r1,[$r6+#0x30]
    76fc:	80 08       	mov55 $r0,$r8
    76fe:	42 10 d4 09 	bclr $r1,$r1,#0x15
    7702:	14 13 00 0c 	swi $r1,[$r6+#0x30]
    7706:	3a 6f a0 84 	lmw.bim $r6,[$sp],$r8,#0x2    ! {$r6~$r8, $lp}
    770a:	dd 9e       	ret5 $lp
    770c:	50 33 80 28 	addi $r3,$r7,#0x28
    7710:	80 46       	mov55 $r2,$r6
    7712:	b4 02       	lwi450 $r0,[$r2]
    7714:	b6 03       	swi450 $r0,[$r3]
    7716:	04 03 00 14 	lwi $r0,[$r6+#0x50]
    771a:	b4 00       	lwi450 $r0,[$r0]
    771c:	4e 03 ff ee 	bnez $r0,76f8 <lfs_file_close+0x3c>
    7720:	04 03 00 13 	lwi $r0,[$r6+#0x4c]
    7724:	49 00 13 f3 	jal 9f0a <free>
    7728:	d5 e8       	j8 76f8 <lfs_file_close+0x3c>
    772a:	92 00       	nop16
    772c:	44 00 36 d4 	movi $r0,#0x36d4
    7730:	44 10 09 f5 	movi $r1,#0x9f5
    7734:	44 20 7c 18 	movi $r2,#0x7c18
    7738:	44 30 3a 5c 	movi $r3,#0x3a5c
    773c:	49 00 12 70 	jal 9c1c <__assert_func>
    7740:	92 00       	nop16
    7742:	92 00       	nop16

00007744 <lfs_file_opencfg>:
    7744:	3a 6f b0 bc 	smw.adm $r6,[$sp],$r12,#0x2    ! {$r6~$r12, $lp}
    7748:	ef d8       	addi10.sp #-40
    774a:	81 23       	mov55 $r9,$r3
    774c:	96 cf       	fexti33 $r3,#0x1
    774e:	81 00       	mov55 $r8,$r0
    7750:	80 c1       	mov55 $r6,$r1
    7752:	f2 83       	swi37.sp $r2,[+#0xc]
    7754:	5a 30 01 07 	beqc $r3,#0x1,7762 <lfs_file_opencfg+0x1e>
    7758:	f4 82       	swi37.sp $r4,[+#0x8]
    775a:	49 ff fe 3b 	jal 73d0 <lfs_fs_forceconsistency>
    775e:	f4 02       	lwi37.sp $r4,[+#0x8]
    7760:	c8 32       	bnez38 $r0,77c4 <lfs_file_opencfg+0x80>
    7762:	85 40       	movi55 $r10,#0x0
    7764:	42 04 d4 08 	bset $r0,$r9,#0x15
    7768:	50 b3 00 08 	addi $r11,$r6,#0x8
    776c:	14 03 00 0c 	swi $r0,[$r6+#0x30]
    7770:	14 43 00 14 	swi $r4,[$r6+#0x50]
    7774:	14 a3 00 0d 	swi $r10,[$r6+#0x34]
    7778:	14 a3 00 0f 	swi $r10,[$r6+#0x3c]
    777c:	14 a3 00 13 	swi $r10,[$r6+#0x4c]
    7780:	80 08       	mov55 $r0,$r8
    7782:	80 2b       	mov55 $r1,$r11
    7784:	b0 83       	addri36.sp $r2,#0xc
    7786:	9c f4       	addi333 $r3,$r6,#0x4
    7788:	49 ff ef 64 	jal 5650 <lfs_dir_find>
    778c:	80 e0       	mov55 $r7,$r0
    778e:	4e 05 00 87 	bltz $r0,789c <lfs_file_opencfg+0x158>
    7792:	84 01       	movi55 $r0,#0x1
    7794:	ae 36       	sbi333 $r0,[$r6+#0x6]
    7796:	04 14 00 0a 	lwi $r1,[$r8+#0x28]
    779a:	54 04 82 00 	andi $r0,$r9,#0x200
    779e:	b6 26       	swi450 $r1,[$r6]
    77a0:	14 64 00 0a 	swi $r6,[$r8+#0x28]
    77a4:	c0 14       	beqz38 $r0,77cc <lfs_file_opencfg+0x88>
    77a6:	44 7f ff ef 	movi $r7,#-17
    77aa:	92 00       	nop16
    77ac:	04 33 00 0c 	lwi $r3,[$r6+#0x30]
    77b0:	42 31 cc 08 	bset $r3,$r3,#0x13
    77b4:	14 33 00 0c 	swi $r3,[$r6+#0x30]
    77b8:	80 08       	mov55 $r0,$r8
    77ba:	80 26       	mov55 $r1,$r6
    77bc:	49 ff ff 80 	jal 76bc <lfs_file_close>
    77c0:	80 07       	mov55 $r0,$r7
    77c2:	92 00       	nop16
    77c4:	ec 28       	addi10.sp #0x28
    77c6:	3a 6f b0 84 	lmw.bim $r6,[$sp],$r12,#0x2    ! {$r6~$r12, $lp}
    77ca:	dd 9e       	ret5 $lp
    77cc:	94 79       	slli333 $r1,$r7,#0x1
    77ce:	92 35       	srli45 $r1,#0x15
    77d0:	5a 10 01 08 	beqc $r1,#0x1,77e0 <lfs_file_opencfg+0x9c>
    77d4:	44 7f ff eb 	movi $r7,#-21
    77d8:	04 33 00 0c 	lwi $r3,[$r6+#0x30]
    77dc:	d5 ea       	j8 77b0 <lfs_file_opencfg+0x6c>
    77de:	92 00       	nop16
    77e0:	54 f4 84 00 	andi $r15,$r9,#0x400
    77e4:	4e f2 00 80 	beqz $r15,78e4 <lfs_file_opencfg+0x1a0>
    77e8:	04 23 00 0c 	lwi $r2,[$r6+#0x30]
    77ec:	a5 f2       	lhi333 $r7,[$r6+#0x4]
    77ee:	42 21 40 08 	bset $r2,$r2,#0x10
    77f2:	40 03 a8 08 	slli $r0,$r7,#0xa
    77f6:	46 12 01 00 	sethi $r1,#0x20100
    77fa:	40 70 04 04 	or $r7,$r0,$r1
    77fe:	14 23 00 0c 	swi $r2,[$r6+#0x30]
    7802:	92 00       	nop16
    7804:	04 53 00 14 	lwi $r5,[$r6+#0x50]
    7808:	a0 2a       	lwi333 $r0,[$r5+#0x8]
    780a:	4e 02 00 8e 	beqz $r0,7926 <lfs_file_opencfg+0x1e2>
    780e:	46 c7 ff ff 	sethi $r12,#0x7ffff
    7812:	85 20       	movi55 $r9,#0x0
    7814:	85 40       	movi55 $r10,#0x0
    7816:	50 c6 0c 00 	addi $r12,$r12,#0xc00
    781a:	d5 29       	j8 786c <lfs_file_opencfg+0x128>
    781c:	a0 e9       	lwi333 $r3,[$r5+#0x4]
    781e:	a5 72       	lhi333 $r5,[$r6+#0x4]
    7820:	41 11 a4 00 	add $r17,$r3,$r9
    7824:	38 31 a4 00 	lb $r3,[$r3+($r9<<#0x0)]
    7828:	05 28 80 02 	lwi $r18,[$r17+#0x8]
    782c:	41 02 a8 08 	slli $r16,$r5,#0xa
    7830:	50 31 83 00 	addi $r3,$r3,#0x300
    7834:	40 58 48 04 	or $r5,$r16,$r18
    7838:	40 31 d0 08 	slli $r3,$r3,#0x14
    783c:	fe ef       	or33 $r3,$r5
    783e:	54 51 83 ff 	andi $r5,$r3,#0x3ff
    7842:	b6 bf       	swi450 $r5,[$sp]
    7844:	04 58 80 01 	lwi $r5,[$r17+#0x4]
    7848:	49 ff ed ea 	jal 541c <lfs_dir_getslice>
    784c:	4e 05 00 66 	bltz $r0,7918 <lfs_file_opencfg+0x1d4>
    7850:	04 33 00 0c 	lwi $r3,[$r6+#0x30]
    7854:	04 53 00 14 	lwi $r5,[$r6+#0x50]
    7858:	54 01 80 03 	andi $r0,$r3,#0x3
    785c:	5a 08 01 12 	bnec $r0,#0x1,7880 <lfs_file_opencfg+0x13c>
    7860:	a0 2a       	lwi333 $r0,[$r5+#0x8]
    7862:	8d 41       	addi45 $r10,#0x1
    7864:	e3 40       	slt45 $r10,$r0
    7866:	8d 2c       	addi45 $r9,#0xc
    7868:	e8 5f       	beqzs8 7926 <lfs_file_opencfg+0x1e2>
    786a:	92 00       	nop16
    786c:	04 33 00 0c 	lwi $r3,[$r6+#0x30]
    7870:	80 08       	mov55 $r0,$r8
    7872:	55 01 80 03 	andi $r16,$r3,#0x3
    7876:	80 2b       	mov55 $r1,$r11
    7878:	80 4c       	mov55 $r2,$r12
    787a:	84 80       	movi55 $r4,#0x0
    787c:	5b 08 02 d0 	bnec $r16,#0x2,781c <lfs_file_opencfg+0xd8>
    7880:	a1 29       	lwi333 $r4,[$r5+#0x4]
    7882:	04 04 00 1d 	lwi $r0,[$r8+#0x74]
    7886:	88 89       	add45 $r4,$r9
    7888:	a0 62       	lwi333 $r1,[$r4+#0x8]
    788a:	42 41 c0 08 	bset $r4,$r3,#0x10
    788e:	e2 01       	slt45 $r0,$r1
    7890:	4e f3 00 9a 	bnez $r15,79c4 <lfs_file_opencfg+0x280>
    7894:	14 43 00 0c 	swi $r4,[$r6+#0x30]
    7898:	d5 e4       	j8 7860 <lfs_file_opencfg+0x11c>
    789a:	92 00       	nop16
    789c:	5a 07 fe 04 	beqc $r0,#-2,78a4 <lfs_file_opencfg+0x160>
    78a0:	48 ff ff 86 	j 77ac <lfs_file_opencfg+0x68>
    78a4:	a4 32       	lhi333 $r0,[$r6+#0x4]
    78a6:	5a 0b ff 05 	bnec $r0,#0x3ff,78b0 <lfs_file_opencfg+0x16c>
    78aa:	48 ff ff 81 	j 77ac <lfs_file_opencfg+0x68>
    78ae:	92 00       	nop16
    78b0:	84 01       	movi55 $r0,#0x1
    78b2:	ae 36       	sbi333 $r0,[$r6+#0x6]
    78b4:	04 04 00 0a 	lwi $r0,[$r8+#0x28]
    78b8:	54 f4 81 00 	andi $r15,$r9,#0x100
    78bc:	b6 06       	swi450 $r0,[$r6]
    78be:	14 64 00 0a 	swi $r6,[$r8+#0x28]
    78c2:	4e f2 ff 75 	beqz $r15,77ac <lfs_file_opencfg+0x68>
    78c6:	f0 03       	lwi37.sp $r0,[+#0xc]
    78c8:	49 00 14 c4 	jal a250 <strlen>
    78cc:	04 14 00 1b 	lwi $r1,[$r8+#0x6c]
    78d0:	40 10 80 06 	slt $r1,$r1,$r0
    78d4:	4e 12 00 7c 	beqz $r1,79cc <lfs_file_opencfg+0x288>
    78d8:	44 7f ff dc 	movi $r7,#-36
    78dc:	04 33 00 0c 	lwi $r3,[$r6+#0x30]
    78e0:	48 ff ff 68 	j 77b0 <lfs_file_opencfg+0x6c>
    78e4:	a5 32       	lhi333 $r4,[$r6+#0x4]
    78e6:	46 32 00 00 	sethi $r3,#0x20000
    78ea:	40 42 28 08 	slli $r4,$r4,#0xa
    78ee:	84 08       	movi55 $r0,#0x8
    78f0:	46 27 00 ff 	sethi $r2,#0x700ff
    78f4:	8c 68       	addi45 $r3,#0x8
    78f6:	b6 1f       	swi450 $r0,[$sp]
    78f8:	fe e7       	or33 $r3,$r4
    78fa:	80 08       	mov55 $r0,$r8
    78fc:	80 2b       	mov55 $r1,$r11
    78fe:	50 21 0c 00 	addi $r2,$r2,#0xc00
    7902:	84 80       	movi55 $r4,#0x0
    7904:	50 53 00 28 	addi $r5,$r6,#0x28
    7908:	49 ff ed 8a 	jal 541c <lfs_dir_getslice>
    790c:	80 e0       	mov55 $r7,$r0
    790e:	4e 04 ff 7b 	bgez $r0,7804 <lfs_file_opencfg+0xc0>
    7912:	48 ff ff 4d 	j 77ac <lfs_file_opencfg+0x68>
    7916:	92 00       	nop16
    7918:	5a 07 fe 9c 	beqc $r0,#-2,7850 <lfs_file_opencfg+0x10c>
    791c:	80 e0       	mov55 $r7,$r0
    791e:	04 33 00 0c 	lwi $r3,[$r6+#0x30]
    7922:	48 ff ff 47 	j 77b0 <lfs_file_opencfg+0x6c>
    7926:	b4 05       	lwi450 $r0,[$r5]
    7928:	4e 02 00 74 	beqz $r0,7a10 <lfs_file_opencfg+0x2cc>
    792c:	14 03 00 13 	swi $r0,[$r6+#0x4c]
    7930:	04 24 00 1a 	lwi $r2,[$r8+#0x68]
    7934:	44 10 00 ff 	movi $r1,#0xff
    7938:	04 21 00 0a 	lwi $r2,[$r2+#0x28]
    793c:	49 00 13 40 	jal 9fbc <memset>
    7940:	94 39       	slli333 $r0,$r7,#0x1
    7942:	84 3f       	movi55 $r1,#-1
    7944:	92 15       	srli45 $r0,#0x15
    7946:	14 13 00 10 	swi $r1,[$r6+#0x40]
    794a:	5a 02 01 05 	beqc $r0,#0x201,7954 <lfs_file_opencfg+0x210>
    794e:	84 00       	movi55 $r0,#0x0
    7950:	48 ff ff 3a 	j 77c4 <lfs_file_opencfg+0x80>
    7954:	04 03 00 0c 	lwi $r0,[$r6+#0x30]
    7958:	04 34 00 1a 	lwi $r3,[$r8+#0x68]
    795c:	42 00 50 08 	bset $r0,$r0,#0x14
    7960:	04 31 80 0a 	lwi $r3,[$r3+#0x28]
    7964:	84 5e       	movi55 $r2,#-2
    7966:	54 13 83 ff 	andi $r1,$r7,#0x3ff
    796a:	14 03 00 0c 	swi $r0,[$r6+#0x30]
    796e:	84 00       	movi55 $r0,#0x0
    7970:	14 23 00 0a 	swi $r2,[$r6+#0x28]
    7974:	14 13 00 0b 	swi $r1,[$r6+#0x2c]
    7978:	14 23 00 10 	swi $r2,[$r6+#0x40]
    797c:	14 03 00 11 	swi $r0,[$r6+#0x44]
    7980:	14 33 00 12 	swi $r3,[$r6+#0x48]
    7984:	c1 e5       	beqz38 $r1,794e <lfs_file_opencfg+0x20a>
    7986:	a4 72       	lhi333 $r1,[$r6+#0x4]
    7988:	44 20 03 fe 	movi $r2,#0x3fe
    798c:	e2 43       	slt45 $r2,$r3
    798e:	40 31 3c 1b 	cmovn $r3,$r2,$r15
    7992:	40 10 a8 08 	slli $r1,$r1,#0xa
    7996:	fe cf       	or33 $r3,$r1
    7998:	54 01 83 ff 	andi $r0,$r3,#0x3ff
    799c:	b6 1f       	swi450 $r0,[$sp]
    799e:	46 27 00 ff 	sethi $r2,#0x700ff
    79a2:	80 08       	mov55 $r0,$r8
    79a4:	80 2b       	mov55 $r1,$r11
    79a6:	50 21 0c 00 	addi $r2,$r2,#0xc00
    79aa:	42 31 f4 08 	bset $r3,$r3,#0x1d
    79ae:	84 80       	movi55 $r4,#0x0
    79b0:	04 53 00 13 	lwi $r5,[$r6+#0x4c]
    79b4:	49 ff ed 34 	jal 541c <lfs_dir_getslice>
    79b8:	80 e0       	mov55 $r7,$r0
    79ba:	4e 05 fe f9 	bltz $r0,77ac <lfs_file_opencfg+0x68>
    79be:	84 00       	movi55 $r0,#0x0
    79c0:	48 ff ff 02 	j 77c4 <lfs_file_opencfg+0x80>
    79c4:	44 7f ff e4 	movi $r7,#-28
    79c8:	48 ff fe f4 	j 77b0 <lfs_file_opencfg+0x6c>
    79cc:	a4 b2       	lhi333 $r2,[$r6+#0x4]
    79ce:	46 72 01 00 	sethi $r7,#0x20100
    79d2:	40 21 28 08 	slli $r2,$r2,#0xa
    79d6:	42 41 50 08 	bset $r4,$r2,#0x14
    79da:	47 04 01 00 	sethi $r16,#0x40100
    79de:	41 01 40 04 	or $r16,$r2,$r16
    79e2:	40 51 1c 04 	or $r5,$r2,$r7
    79e6:	ff 07       	or33 $r4,$r0
    79e8:	b0 84       	addri36.sp $r2,#0x10
    79ea:	a9 12       	swi333 $r4,[$r2+#0x8]
    79ec:	f4 03       	lwi37.sp $r4,[+#0xc]
    79ee:	80 08       	mov55 $r0,$r8
    79f0:	80 2b       	mov55 $r1,$r11
    79f2:	84 63       	movi55 $r3,#0x3
    79f4:	14 a1 00 01 	swi $r10,[$r2+#0x4]
    79f8:	a9 13       	swi333 $r4,[$r2+#0xc]
    79fa:	a9 54       	swi333 $r5,[$r2+#0x10]
    79fc:	14 a1 00 05 	swi $r10,[$r2+#0x14]
    7a00:	15 0f 80 04 	swi $r16,[$sp+#0x10]
    7a04:	49 ff fa a8 	jal 6f54 <lfs_dir_commit>
    7a08:	4e 03 ff 68 	bnez $r0,78d8 <lfs_file_opencfg+0x194>
    7a0c:	48 ff fe fc 	j 7804 <lfs_file_opencfg+0xc0>
    7a10:	04 04 00 1a 	lwi $r0,[$r8+#0x68]
    7a14:	04 00 00 0a 	lwi $r0,[$r0+#0x28]
    7a18:	49 00 12 72 	jal 9efc <malloc>
    7a1c:	14 03 00 13 	swi $r0,[$r6+#0x4c]
    7a20:	4e 03 ff 88 	bnez $r0,7930 <lfs_file_opencfg+0x1ec>
    7a24:	84 f4       	movi55 $r7,#-12
    7a26:	04 33 00 0c 	lwi $r3,[$r6+#0x30]
    7a2a:	48 ff fe c3 	j 77b0 <lfs_file_opencfg+0x6c>
    7a2e:	92 00       	nop16

00007a30 <lfs_file_open>:
    7a30:	44 40 7c 28 	movi $r4,#0x7c28
    7a34:	48 ff fe 88 	j 7744 <lfs_file_opencfg>

00007a38 <lfs_format>:
    7a38:	3a 6f 9c bc 	smw.adm $r6,[$sp],$r7,#0x2    ! {$r6~$r7, $lp}
    7a3c:	ef 9c       	addi10.sp #-100
    7a3e:	80 e0       	mov55 $r7,$r0
    7a40:	49 ff e1 cc 	jal 3dd8 <lfs_init>
    7a44:	80 c0       	mov55 $r6,$r0
    7a46:	c0 05       	beqz38 $r0,7a50 <lfs_format+0x18>
    7a48:	ec 64       	addi10.sp #0x64
    7a4a:	3a 6f 9c 84 	lmw.bim $r6,[$sp],$r7,#0x2    ! {$r6~$r7, $lp}
    7a4e:	dd 9e       	ret5 $lp
    7a50:	04 03 80 1a 	lwi $r0,[$r7+#0x68]
    7a54:	44 10 00 00 	movi $r1,#0x0
    7a58:	04 20 00 0b 	lwi $r2,[$r0+#0x2c]
    7a5c:	04 03 80 19 	lwi $r0,[$r7+#0x64]
    7a60:	49 00 12 ae 	jal 9fbc <memset>
    7a64:	04 13 80 1a 	lwi $r1,[$r7+#0x68]
    7a68:	04 00 80 0b 	lwi $r0,[$r1+#0x2c]
    7a6c:	04 10 80 08 	lwi $r1,[$r1+#0x20]
    7a70:	94 03       	slli333 $r0,$r0,#0x3
    7a72:	40 20 80 06 	slt $r2,$r1,$r0
    7a76:	40 00 88 1b 	cmovn $r0,$r1,$r2
    7a7a:	14 63 80 15 	swi $r6,[$r7+#0x54]
    7a7e:	14 03 80 16 	swi $r0,[$r7+#0x58]
    7a82:	14 63 80 17 	swi $r6,[$r7+#0x5c]
    7a86:	14 13 80 18 	swi $r1,[$r7+#0x60]
    7a8a:	80 07       	mov55 $r0,$r7
    7a8c:	b0 50       	addri36.sp $r1,#0x40
    7a8e:	49 ff f2 43 	jal 5f14 <lfs_dir_alloc>
    7a92:	80 c0       	mov55 $r6,$r0
    7a94:	c0 0a       	beqz38 $r0,7aa8 <lfs_format+0x70>
    7a96:	80 07       	mov55 $r0,$r7
    7a98:	49 ff dd f4 	jal 3680 <lfs_deinit>
    7a9c:	80 06       	mov55 $r0,$r6
    7a9e:	ec 64       	addi10.sp #0x64
    7aa0:	3a 6f 9c 84 	lmw.bim $r6,[$sp],$r7,#0x2    ! {$r6~$r7, $lp}
    7aa4:	dd 9e       	ret5 $lp
    7aa6:	92 00       	nop16
    7aa8:	04 53 80 1d 	lwi $r5,[$r7+#0x74]
    7aac:	f5 89       	swi37.sp $r5,[+#0x24]
    7aae:	46 54 01 00 	sethi $r5,#0x40100
    7ab2:	f5 8a       	swi37.sp $r5,[+#0x28]
    7ab4:	46 50 ff 00 	sethi $r5,#0xff00
    7ab8:	b0 8a       	addri36.sp $r2,#0x28
    7aba:	8c a8       	addi45 $r5,#0x8
    7abc:	a9 52       	swi333 $r5,[$r2+#0x8]
    7abe:	44 50 3a 78 	movi $r5,#0x3a78
    7ac2:	04 03 80 1a 	lwi $r0,[$r7+#0x68]
    7ac6:	a9 53       	swi333 $r5,[$r2+#0xc]
    7ac8:	46 52 01 00 	sethi $r5,#0x20100
    7acc:	b1 04       	addri36.sp $r4,#0x10
    7ace:	8c b8       	addi45 $r5,#0x18
    7ad0:	05 30 00 07 	lwi $r19,[$r0+#0x1c]
    7ad4:	05 20 00 08 	lwi $r18,[$r0+#0x20]
    7ad8:	05 13 80 1b 	lwi $r17,[$r7+#0x6c]
    7adc:	05 03 80 1c 	lwi $r16,[$r7+#0x70]
    7ae0:	45 42 00 00 	movi $r20,#0x20000
    7ae4:	a9 91       	swi333 $r6,[$r2+#0x4]
    7ae6:	80 07       	mov55 $r0,$r7
    7ae8:	b0 50       	addri36.sp $r1,#0x40
    7aea:	84 63       	movi55 $r3,#0x3
    7aec:	a9 54       	swi333 $r5,[$r2+#0x10]
    7aee:	a9 15       	swi333 $r4,[$r2+#0x14]
    7af0:	15 4f 80 04 	swi $r20,[$sp+#0x10]
    7af4:	15 3f 80 05 	swi $r19,[$sp+#0x14]
    7af8:	15 2f 80 06 	swi $r18,[$sp+#0x18]
    7afc:	15 1f 80 07 	swi $r17,[$sp+#0x1c]
    7b00:	15 0f 80 08 	swi $r16,[$sp+#0x20]
    7b04:	49 ff fa 28 	jal 6f54 <lfs_dir_commit>
    7b08:	80 c0       	mov55 $r6,$r0
    7b0a:	c8 c6       	bnez38 $r0,7a96 <lfs_format+0x5e>
    7b0c:	b0 82       	addri36.sp $r2,#0x8
    7b0e:	86 01       	movi55 $r16,#0x1
    7b10:	b6 1f       	swi450 $r0,[$sp]
    7b12:	f0 81       	swi37.sp $r0,[+#0x4]
    7b14:	b0 50       	addri36.sp $r1,#0x40
    7b16:	80 07       	mov55 $r0,$r7
    7b18:	84 7f       	movi55 $r3,#-1
    7b1a:	84 9f       	movi55 $r4,#-1
    7b1c:	84 a0       	movi55 $r5,#0x0
    7b1e:	15 01 00 01 	swi $r16,[$r2+#0x4]
    7b22:	f6 82       	swi37.sp $r6,[+#0x8]
    7b24:	49 ff e3 b6 	jal 4290 <lfs_dir_fetchmatch>
    7b28:	80 c0       	mov55 $r6,$r0
    7b2a:	c8 b6       	bnez38 $r0,7a96 <lfs_format+0x5e>
    7b2c:	b0 50       	addri36.sp $r1,#0x40
    7b2e:	80 07       	mov55 $r0,$r7
    7b30:	84 40       	movi55 $r2,#0x0
    7b32:	84 60       	movi55 $r3,#0x0
    7b34:	10 60 80 16 	sbi $r6,[$r1+#0x16]
    7b38:	49 ff fa 0e 	jal 6f54 <lfs_dir_commit>
    7b3c:	80 c0       	mov55 $r6,$r0
    7b3e:	d5 ac       	j8 7a96 <lfs_format+0x5e>

00007b40 <lfs_dir_split>:
    7b40:	3a 6f a0 bc 	smw.adm $r6,[$sp],$r8,#0x2    ! {$r6~$r8, $lp}
    7b44:	ef c8       	addi10.sp #-56
    7b46:	05 00 00 1a 	lwi $r16,[$r0+#0x68]
    7b4a:	80 e1       	mov55 $r7,$r1
    7b4c:	05 08 00 08 	lwi $r16,[$r16+#0x20]
    7b50:	15 00 00 18 	swi $r16,[$r0+#0x60]
    7b54:	b0 46       	addri36.sp $r1,#0x18
    7b56:	f2 85       	swi37.sp $r2,[+#0x14]
    7b58:	f3 84       	swi37.sp $r3,[+#0x10]
    7b5a:	f4 83       	swi37.sp $r4,[+#0xc]
    7b5c:	80 c0       	mov55 $r6,$r0
    7b5e:	81 05       	mov55 $r8,$r5
    7b60:	49 ff f1 da 	jal 5f14 <lfs_dir_alloc>
    7b64:	f4 03       	lwi37.sp $r4,[+#0xc]
    7b66:	f3 04       	lwi37.sp $r3,[+#0x10]
    7b68:	f2 05       	lwi37.sp $r2,[+#0x14]
    7b6a:	c0 05       	beqz38 $r0,7b74 <lfs_dir_split+0x34>
    7b6c:	ec 38       	addi10.sp #0x38
    7b6e:	3a 6f a0 84 	lmw.bim $r6,[$sp],$r8,#0x2    ! {$r6~$r8, $lp}
    7b72:	dd 9e       	ret5 $lp
    7b74:	02 0f 80 24 	lhi $r0,[$sp+#0x48]
    7b78:	01 23 80 17 	lbi $r18,[$r7+#0x17]
    7b7c:	05 13 80 06 	lwi $r17,[$r7+#0x18]
    7b80:	05 03 80 07 	lwi $r16,[$r7+#0x1c]
    7b84:	b0 46       	addri36.sp $r1,#0x18
    7b86:	b6 1f       	swi450 $r0,[$sp]
    7b88:	80 a8       	mov55 $r5,$r8
    7b8a:	80 06       	mov55 $r0,$r6
    7b8c:	11 2f 80 2f 	sbi $r18,[$sp+#0x2f]
    7b90:	15 1f 80 0c 	swi $r17,[$sp+#0x30]
    7b94:	15 0f 80 0d 	swi $r16,[$sp+#0x34]
    7b98:	49 ff f6 7c 	jal 6890 <lfs_dir_compact>
    7b9c:	c8 e8       	bnez38 $r0,7b6c <lfs_dir_split+0x2c>
    7b9e:	f2 06       	lwi37.sp $r2,[+#0x18]
    7ba0:	f3 07       	lwi37.sp $r3,[+#0x1c]
    7ba2:	a8 be       	swi333 $r2,[$r7+#0x18]
    7ba4:	a8 ff       	swi333 $r3,[$r7+#0x1c]
    7ba6:	04 43 00 08 	lwi $r4,[$r6+#0x20]
    7baa:	b4 27       	lwi450 $r1,[$r7]
    7bac:	84 a1       	movi55 $r5,#0x1
    7bae:	10 53 80 17 	sbi $r5,[$r7+#0x17]
    7bb2:	4c 12 00 0c 	beq $r1,$r4,7bca <lfs_dir_split+0x8a>
    7bb6:	05 03 80 01 	lwi $r16,[$r7+#0x4]
    7bba:	04 53 00 09 	lwi $r5,[$r6+#0x24]
    7bbe:	4d 02 80 06 	beq $r16,$r5,7bca <lfs_dir_split+0x8a>
    7bc2:	4c 12 80 04 	beq $r1,$r5,7bca <lfs_dir_split+0x8a>
    7bc6:	4c 48 7f d3 	bne $r4,$r16,7b6c <lfs_dir_split+0x2c>
    7bca:	84 00       	movi55 $r0,#0x0
    7bcc:	4e 83 ff d0 	bnez $r8,7b6c <lfs_dir_split+0x2c>
    7bd0:	14 23 00 08 	swi $r2,[$r6+#0x20]
    7bd4:	14 33 00 09 	swi $r3,[$r6+#0x24]
    7bd8:	d5 ca       	j8 7b6c <lfs_dir_split+0x2c>
    7bda:	92 00       	nop16

00007bdc <__func__.4286>:
    7bdc:	6c 66 73 5f 69 6e 69 74 00 00 00 00                 lfs_init....

00007be8 <__func__.4141>:
    7be8:	6c 66 73 5f 66 69 6c 65 5f 77 72 69 74 65 00 00     lfs_file_write..

00007bf8 <__func__.4124>:
    7bf8:	6c 66 73 5f 66 69 6c 65 5f 72 65 61 64 00 00 00     lfs_file_read...

00007c08 <__func__.4110>:
    7c08:	6c 66 73 5f 66 69 6c 65 5f 73 79 6e 63 00 00 00     lfs_file_sync...

00007c18 <__func__.4065>:
    7c18:	6c 66 73 5f 66 69 6c 65 5f 63 6c 6f 73 65 00 00     lfs_file_close..

00007c28 <defaults.4059>:
	...

00007c34 <__func__.3846>:
    7c34:	6c 66 73 5f 64 69 72 5f 63 6f 6d 70 61 63 74 00     lfs_dir_compact.

00007c44 <__func__.3334>:
    7c44:	6c 66 73 5f 62 64 5f 73 79 6e 63 00                 lfs_bd_sync.

00007c50 <__func__.4094>:
    7c50:	6c 66 73 5f 66 69 6c 65 5f 66 6c 75 73 68 00 00     lfs_file_flush..

00007c60 <__func__.3323>:
    7c60:	6c 66 73 5f 62 64 5f 66 6c 75 73 68 00 00 00 00     lfs_bd_flush....

00007c70 <__func__.3346>:
    7c70:	6c 66 73 5f 62 64 5f 70 72 6f 67 00                 lfs_bd_prog.

00007c7c <__func__.3356>:
    7c7c:	6c 66 73 5f 62 64 5f 65 72 61 73 65 00 00 00 00     lfs_bd_erase....

00007c8c <__func__.4075>:
    7c8c:	6c 66 73 5f 66 69 6c 65 5f 72 65 6c 6f 63 61 74     lfs_file_relocat
    7c9c:	65 00 00 00                                         e...

00007ca0 <__func__.3868>:
    7ca0:	6c 66 73 5f 64 69 72 5f 63 6f 6d 6d 69 74 00 00     lfs_dir_commit..

00007cb0 <__func__.4427>:
    7cb0:	6c 66 73 5f 66 73 5f 70 72 65 70 6f 72 70 68 61     lfs_fs_preporpha
    7cc0:	6e 73 00 00                                         ns..

00007cc4 <__func__.3292>:
    7cc4:	6c 66 73 5f 62 64 5f 72 65 61 64 00                 lfs_bd_read.

00007cd0 <lfs_crc>:
    7cd0:	c2 16       	beqz38 $r2,7cfc <lfs_crc+0x2c>
    7cd2:	88 41       	add45 $r2,$r1
    7cd4:	44 50 7d 00 	movi $r5,#0x7d00
    7cd8:	08 30 80 01 	lbi.bi $r3,[$r1],#0x1
    7cdc:	40 40 10 09 	srli $r4,$r0,#0x4
    7ce0:	fe 1d       	xor33 $r0,$r3
    7ce2:	96 1f       	fexti33 $r0,#0x3
    7ce4:	38 02 82 02 	lw $r0,[$r5+($r0<<#0x2)]
    7ce8:	92 64       	srli45 $r3,#0x4
    7cea:	fe 25       	xor33 $r0,$r4
    7cec:	fe c5       	xor33 $r3,$r0
    7cee:	96 df       	fexti33 $r3,#0x3
    7cf0:	38 32 8e 02 	lw $r3,[$r5+($r3<<#0x2)]
    7cf4:	92 04       	srli45 $r0,#0x4
    7cf6:	fe 1d       	xor33 $r0,$r3
    7cf8:	4c 11 7f f0 	bne $r1,$r2,7cd8 <lfs_crc+0x8>
    7cfc:	dd 9e       	ret5 $lp
    7cfe:	92 00       	nop16

00007d00 <rtable.2979>:
    7d00:	00 00 00 00 64 10 b7 1d c8 20 6e 3b ac 30 d9 26     ....d.... n;.0.&
    7d10:	90 41 dc 76 f4 51 6b 6b 58 61 b2 4d 3c 71 05 50     .A.v.QkkXa.M<q.P
    7d20:	20 83 b8 ed 44 93 0f f0 e8 a3 d6 d6 8c b3 61 cb      ...D.........a.
    7d30:	b0 c2 64 9b d4 d2 d3 86 78 e2 0a a0 1c f2 bd bd     ..d.....x.......

00007d40 <Cmd_Meta>:
    7d40:	46 1c cb 0b 	sethi $r1,#0xccb0b
    7d44:	04 00 80 30 	lwi $r0,[$r1+#0xc0]
    7d48:	46 2c 00 00 	sethi $r2,#0xc0000
    7d4c:	58 00 00 04 	ori $r0,$r0,#0x4
    7d50:	14 00 80 30 	swi $r0,[$r1+#0xc0]
    7d54:	46 18 00 00 	sethi $r1,#0x80000
    7d58:	50 10 87 d0 	addi $r1,$r1,#0x7d0
    7d5c:	84 00       	movi55 $r0,#0x0
    7d5e:	14 11 00 a1 	swi $r1,[$r2+#0x284]
    7d62:	dd 9e       	ret5 $lp

00007d64 <Cmd_Meta_reboot>:
    7d64:	46 1c cb 0b 	sethi $r1,#0xccb0b
    7d68:	04 00 80 30 	lwi $r0,[$r1+#0xc0]
    7d6c:	46 2c 00 00 	sethi $r2,#0xc0000
    7d70:	66 00 00 04 	bitci $r0,$r0,#0x4
    7d74:	14 00 80 30 	swi $r0,[$r1+#0xc0]
    7d78:	46 18 00 00 	sethi $r1,#0x80000
    7d7c:	58 10 81 00 	ori $r1,$r1,#0x100
    7d80:	14 11 00 a1 	swi $r1,[$r2+#0x284]
    7d84:	84 21       	movi55 $r1,#0x1
    7d86:	84 00       	movi55 $r0,#0x0
    7d88:	a8 56       	swi333 $r1,[$r2+#0x18]
    7d8a:	dd 9e       	ret5 $lp
    7d8c:	72 65 67 20 	*unknown*
    7d90:	3a 20 77 72 	smwzb.a $r2,[$r0],$gp,#0xd    ! {$r2~$gp, $fp, $gp, $sp}
    7d94:	69 74 65 20 	*unknown*
    7d98:	30 78 25 78 	cplwi cp1,$cpr7,[$r16+#0x15e0]
    7d9c:	20 20 30 78 	lbsi $r2,[$r0+#0x3078]
    7da0:	25 78 20 0a 	*unknown*
    7da4:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    7da8:	5f 5f 66 6f 	sltsi $r21,$lp,#-6545
    7dac:	74 61 5f 64 	*unknown*
    7db0:	61 74 61 20 	amttsl2.s $d0,$r8,$r24,[$i0],[$i4],$m0,$m6
    7db4:	3d 20 30 78 	lhi.gp $r18,[+#0x60f0]
    7db8:	25 78 0a 00 	*unknown*
    7dbc:	67 5f 73 61 	bitci $r21,$lp,#0x7361
    7dc0:	5f 63 66 67 	sltsi $r22,$r6,#-6553
    7dc4:	20 3d 20 30 	lbsi $r3,[$p0+#0x2030]
    7dc8:	78 25 78 0a 	*unknown*
    7dcc:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    7dd0:	67 5f 77 69 	bitci $r21,$lp,#0x7769
    7dd4:	66 69 5f 63 	bitci $r6,$r18,#0x5f63
    7dd8:	66 67 20 3d 	bitci $r6,$r14,#0x203d
    7ddc:	20 30 78 25 	lbsi $r3,[$r0+#-2011]
    7de0:	78 0a 00 00 	*unknown*
    7de4:	5f 70 61 64 	sltsi $r23,$r0,#-7836
    7de8:	5f 73 65 74 	sltsi $r23,$r6,#-6796
    7dec:	74 69 6e 67 	*unknown*
    7df0:	20 3d 20 30 	lbsi $r3,[$p0+#0x2030]
    7df4:	78 25 78 0a 	*unknown*
    7df8:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    7dfc:	67 5f 72 6f 	bitci $r21,$lp,#0x726f
    7e00:	6d 5f 62 6f 	*unknown*
    7e04:	6f 74 20 3d 	*unknown*
    7e08:	20 30 78 25 	lbsi $r3,[$r0+#-2011]
    7e0c:	78 0a 00 00 	*unknown*
    7e10:	67 5f 75 73 	bitci $r21,$lp,#0x7573
    7e14:	65 72 5f 63 	mtsr $r23,151
    7e18:	66 67 20 3d 	bitci $r6,$r14,#0x203d
    7e1c:	20 30 78 25 	lbsi $r3,[$r0+#-2011]
    7e20:	78 0a 00 00 	*unknown*
    7e24:	5f 5f 61 70 	sltsi $r21,$lp,#-7824
    7e28:	70 5f 78 69 	*unknown*
    7e2c:	70 31 20 3d 	*unknown*
    7e30:	20 30 78 25 	lbsi $r3,[$r0+#-2011]
    7e34:	78 0a 00 00 	*unknown*
    7e38:	73 79 73 20 	*unknown*
    7e3c:	62 75 73 20 	*unknown*
    7e40:	63 6c 6f 63 	*unknown*
    7e44:	6b 20 3d 20 	cpe1 cp2,#0x480f4
    7e48:	25 64 0a 00 	*unknown*
    7e4c:	66 6f 74 61 	bitci $r6,$lp,#0x7461
    7e50:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    7e54:	6d 65 74 61 	*unknown*
    7e58:	5f 73 69 7a 	sltsi $r23,$r6,#-5766
    7e5c:	65 3d 25 64 	*unknown*
    7e60:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    7e64:	72 66 00 00 	*unknown*
    7e68:	6d 61 63 00 	*unknown*
    7e6c:	70 61 64 00 	pbsad $r6,$r2,$r25
    7e70:	72 6f 6d 5f 	*unknown*
    7e74:	62 6f 6f 74 	*unknown*
    7e78:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    7e7c:	75 73 65 72 	*unknown*
    7e80:	5f 72 61 77 	sltsi $r23,$r4,#-7817
    7e84:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    7e88:	6d 65 74 61 	*unknown*
    7e8c:	5f 73 69 7a 	sltsi $r23,$r6,#-5766
    7e90:	65 3d 30 00 	*unknown*
    7e94:	4f 4b 0a 00 	*unknown*
    7e98:	45 52 52 4f 	movi $r21,#0x2524f
    7e9c:	52 3a 31 0a 	subri $r3,$r20,#0x310a
    7ea0:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    7ea4:	20 20 20 20 	lbsi $r2,[$r0+#0x2020]
    7ea8:	20 20 20 20 	lbsi $r2,[$r0+#0x2020]
    7eac:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    7eb0:	20 20 20 20 	lbsi $r2,[$r0+#0x2020]
    7eb4:	20 20 20 25 	lbsi $r2,[$r0+#0x2025]
    7eb8:	30 32 6c 58 	cplwi cp3,$cpr3,[$r4+#-3744]
    7ebc:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    7ec0:	0a 2d 2d 2d 	lhi.bi $r2,[$p0],#0x5a5a
    7ec4:	2d 2d 2d 2d 	*unknown*
    7ec8:	2d 00 00 00 	*unknown*
    7ecc:	2b 2d 2d 2d 	lhsi.bi $r18,[$p0],#0x5a5a
    7ed0:	2d 2d 2d 2d 	*unknown*
    7ed4:	2d 00 00 00 	*unknown*
    7ed8:	0a 25 30 38 	lhi.bi $r2,[$r10],#0x6070
    7edc:	6c 58 3a 25 	*unknown*
    7ee0:	30 38 6c 58 	cplwi cp3,$cpr3,[$r16+#-3744]
    7ee4:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    7ee8:	20 25 30 38 	lbsi $r2,[$r10+#0x3038]
    7eec:	6c 58 00 00 	*unknown*
    7ef0:	72 65 67 20 	*unknown*
    7ef4:	3a 20 72 65 	smwa.bim $r2,[$r0],$fp,#0x9    ! {$r2~$fp, $fp, $sp}
    7ef8:	61 64 20 30 	*unknown*
    7efc:	78 25 30 38 	*unknown*
    7f00:	78 20 20 30 	*unknown*
    7f04:	78 25 30 38 	*unknown*
    7f08:	78 20 0a 00 	*unknown*
    7f0c:	58 74 61 6c 	ori $r7,$r8,#0x616c
    7f10:	0a 00 00 00 	lhi.bi $r0,[$r0],#0x0
    7f14:	72 65 67 77 	*unknown*
    7f18:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    7f1c:	72 65 67 72 	*unknown*
    7f20:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    7f24:	6d 65 74 61 	*unknown*
    7f28:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    7f2c:	6d 65 74 61 	*unknown*
    7f30:	20 6d 6f 64 	lbsi $r6,[$p0+#-4252]
    7f34:	65 20 66 6c 	msync ???
    7f38:	61 67 00 00 	*unknown*
    7f3c:	6d 65 74 61 	*unknown*
    7f40:	5f 62 61 63 	sltsi $r22,$r4,#-7837
    7f44:	6b 75 70 00 	fadds $fs23,$fs10,$fs28
    7f48:	6d 65 74 61 	*unknown*
    7f4c:	5f 67 65 74 	sltsi $r22,$r14,#-6796
    7f50:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    7f54:	6d 65 74 61 	*unknown*
    7f58:	5f 72 65 73 	sltsi $r23,$r4,#-6797
    7f5c:	74 6f 72 65 	*unknown*
    7f60:	00 00 00 00 	lbi $r0,[$r0+#0x0]
    7f64:	6d 65 74 61 	*unknown*
    7f68:	5f 72 65 62 	sltsi $r23,$r4,#-6814
    7f6c:	6f 6f 74 00 	*unknown*
    7f70:	74 65 73 74 	*unknown*
    7f74:	00 00 00 00 	lbi $r0,[$r0+#0x0]

00007f78 <Cmd_WriteReg32>:
    7f78:	e4 02       	sltsi45 $r0,#0x2
    7f7a:	e9 21       	bnezs8 7fbc <Cmd_WriteReg32+0x44>
    7f7c:	3a 6f 9c bc 	smw.adm $r6,[$sp],$r7,#0x2    ! {$r6~$r7, $lp}
    7f80:	ef f4       	addi10.sp #-12
    7f82:	b4 01       	lwi450 $r0,[$r1]
    7f84:	a1 89       	lwi333 $r6,[$r1+#0x4]
    7f86:	c0 19       	beqz38 $r0,7fb8 <Cmd_WriteReg32+0x40>
    7f88:	c6 18       	beqz38 $r6,7fb8 <Cmd_WriteReg32+0x40>
    7f8a:	84 20       	movi55 $r1,#0x0
    7f8c:	fa 40       	movpi45 $r2,#0x10
    7f8e:	49 00 12 14 	jal a3b6 <strtoul>
    7f92:	80 e0       	mov55 $r7,$r0
    7f94:	84 20       	movi55 $r1,#0x0
    7f96:	80 06       	mov55 $r0,$r6
    7f98:	fa 40       	movpi45 $r2,#0x10
    7f9a:	49 00 12 0e 	jal a3b6 <strtoul>
    7f9e:	80 c0       	mov55 $r6,$r0
    7fa0:	f0 81       	swi37.sp $r0,[+#0x4]
    7fa2:	b6 ff       	swi450 $r7,[$sp]
    7fa4:	44 00 7d 8c 	movi $r0,#0x7d8c
    7fa8:	49 ff d2 4a 	jal 243c <printf>
    7fac:	b6 c7       	swi450 $r6,[$r7]
    7fae:	84 00       	movi55 $r0,#0x0
    7fb0:	ec 0c       	addi10.sp #0xc
    7fb2:	3a 6f 9c 84 	lmw.bim $r6,[$sp],$r7,#0x2    ! {$r6~$r7, $lp}
    7fb6:	dd 9e       	ret5 $lp
    7fb8:	84 1f       	movi55 $r0,#-1
    7fba:	d5 fb       	j8 7fb0 <Cmd_WriteReg32+0x38>
    7fbc:	84 1f       	movi55 $r0,#-1
    7fbe:	dd 9e       	ret5 $lp

00007fc0 <Cmd_test>:
    7fc0:	3b ff fc bc 	smw.adm $sp,[$sp],$sp,#0x2    ! {$lp}
    7fc4:	ef f4       	addi10.sp #-12
    7fc6:	46 03 00 10 	sethi $r0,#0x30010
    7fca:	58 00 00 00 	ori $r0,$r0,#0x0
    7fce:	b6 1f       	swi450 $r0,[$sp]
    7fd0:	44 00 7d a8 	movi $r0,#0x7da8
    7fd4:	49 ff d2 34 	jal 243c <printf>
    7fd8:	46 03 00 11 	sethi $r0,#0x30011
    7fdc:	58 00 00 00 	ori $r0,$r0,#0x0
    7fe0:	14 0f 80 00 	swi $r0,[$sp+#0x0]
    7fe4:	44 00 7d bc 	movi $r0,#0x7dbc
    7fe8:	49 ff d2 2a 	jal 243c <printf>
    7fec:	46 03 00 12 	sethi $r0,#0x30012
    7ff0:	58 00 00 00 	ori $r0,$r0,#0x0
    7ff4:	14 0f 80 00 	swi $r0,[$sp+#0x0]
    7ff8:	44 00 7d d0 	movi $r0,#0x7dd0
    7ffc:	49 ff d2 20 	jal 243c <printf>
    8000:	46 03 00 13 	sethi $r0,#0x30013
    8004:	58 00 00 00 	ori $r0,$r0,#0x0
    8008:	14 0f 80 00 	swi $r0,[$sp+#0x0]
    800c:	44 00 7d e4 	movi $r0,#0x7de4
    8010:	49 ff d2 16 	jal 243c <printf>
    8014:	46 03 00 14 	sethi $r0,#0x30014
    8018:	58 00 00 00 	ori $r0,$r0,#0x0
    801c:	14 0f 80 00 	swi $r0,[$sp+#0x0]
    8020:	44 00 7d fc 	movi $r0,#0x7dfc
    8024:	49 ff d2 0c 	jal 243c <printf>
    8028:	46 03 00 15 	sethi $r0,#0x30015
    802c:	58 00 00 00 	ori $r0,$r0,#0x0
    8030:	14 0f 80 00 	swi $r0,[$sp+#0x0]
    8034:	44 00 7e 10 	movi $r0,#0x7e10
    8038:	49 ff d2 02 	jal 243c <printf>
    803c:	46 03 00 17 	sethi $r0,#0x30017
    8040:	58 00 00 00 	ori $r0,$r0,#0x0
    8044:	14 0f 80 00 	swi $r0,[$sp+#0x0]
    8048:	44 00 7e 24 	movi $r0,#0x7e24
    804c:	49 ff d1 f8 	jal 243c <printf>
    8050:	44 00 00 a0 	movi $r0,#0xa0
    8054:	b6 1f       	swi450 $r0,[$sp]
    8056:	44 00 7e 38 	movi $r0,#0x7e38
    805a:	49 ff d1 f1 	jal 243c <printf>
    805e:	84 00       	movi55 $r0,#0x0
    8060:	ec 0c       	addi10.sp #0xc
    8062:	3b ff fc 84 	lmw.bim $sp,[$sp],$sp,#0x2    ! {$lp}
    8066:	dd 9e       	ret5 $lp

00008068 <Cmd_Meta_backup>:
    8068:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    806c:	ef f8       	addi10.sp #-8
    806e:	44 00 7e 4c 	movi $r0,#0x7e4c
    8072:	80 c1       	mov55 $r6,$r1
    8074:	b4 21       	lwi450 $r1,[$r1]
    8076:	49 00 10 c9 	jal a208 <strcmp>
    807a:	c0 25       	beqz38 $r0,80c4 <Cmd_Meta_backup+0x5c>
    807c:	44 00 7e 64 	movi $r0,#0x7e64
    8080:	b4 26       	lwi450 $r1,[$r6]
    8082:	49 00 10 c3 	jal a208 <strcmp>
    8086:	c0 1f       	beqz38 $r0,80c4 <Cmd_Meta_backup+0x5c>
    8088:	44 00 7e 68 	movi $r0,#0x7e68
    808c:	b4 26       	lwi450 $r1,[$r6]
    808e:	49 00 10 bd 	jal a208 <strcmp>
    8092:	c0 19       	beqz38 $r0,80c4 <Cmd_Meta_backup+0x5c>
    8094:	44 00 7e 6c 	movi $r0,#0x7e6c
    8098:	b4 26       	lwi450 $r1,[$r6]
    809a:	49 00 10 b7 	jal a208 <strcmp>
    809e:	c0 13       	beqz38 $r0,80c4 <Cmd_Meta_backup+0x5c>
    80a0:	44 00 7e 70 	movi $r0,#0x7e70
    80a4:	b4 26       	lwi450 $r1,[$r6]
    80a6:	49 00 10 b1 	jal a208 <strcmp>
    80aa:	c0 0d       	beqz38 $r0,80c4 <Cmd_Meta_backup+0x5c>
    80ac:	44 00 7e 7c 	movi $r0,#0x7e7c
    80b0:	b4 26       	lwi450 $r1,[$r6]
    80b2:	49 00 10 ab 	jal a208 <strcmp>
    80b6:	c0 13       	beqz38 $r0,80dc <Cmd_Meta_backup+0x74>
    80b8:	44 00 7e 88 	movi $r0,#0x7e88
    80bc:	49 ff d1 c0 	jal 243c <printf>
    80c0:	48 00 00 09 	j 80d2 <Cmd_Meta_backup+0x6a>
    80c4:	44 00 10 00 	movi $r0,#0x1000
    80c8:	b6 1f       	swi450 $r0,[$sp]
    80ca:	44 00 7e 54 	movi $r0,#0x7e54
    80ce:	49 ff d1 b7 	jal 243c <printf>
    80d2:	84 00       	movi55 $r0,#0x0
    80d4:	ec 08       	addi10.sp #0x8
    80d6:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    80da:	dd 9e       	ret5 $lp
    80dc:	44 00 20 00 	movi $r0,#0x2000
    80e0:	b6 1f       	swi450 $r0,[$sp]
    80e2:	44 00 7e 54 	movi $r0,#0x7e54
    80e6:	49 ff d1 ab 	jal 243c <printf>
    80ea:	d5 f4       	j8 80d2 <Cmd_Meta_backup+0x6a>

000080ec <Cmd_Meta_get>:
    80ec:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    80f0:	44 00 7e 4c 	movi $r0,#0x7e4c
    80f4:	80 c1       	mov55 $r6,$r1
    80f6:	b4 21       	lwi450 $r1,[$r1]
    80f8:	49 00 10 88 	jal a208 <strcmp>
    80fc:	c0 32       	beqz38 $r0,8160 <Cmd_Meta_get+0x74>
    80fe:	44 00 7e 64 	movi $r0,#0x7e64
    8102:	b4 26       	lwi450 $r1,[$r6]
    8104:	49 00 10 82 	jal a208 <strcmp>
    8108:	c0 1e       	beqz38 $r0,8144 <Cmd_Meta_get+0x58>
    810a:	44 00 7e 68 	movi $r0,#0x7e68
    810e:	b4 26       	lwi450 $r1,[$r6]
    8110:	49 00 10 7c 	jal a208 <strcmp>
    8114:	c0 3e       	beqz38 $r0,8190 <Cmd_Meta_get+0xa4>
    8116:	44 00 7e 6c 	movi $r0,#0x7e6c
    811a:	b4 26       	lwi450 $r1,[$r6]
    811c:	49 00 10 76 	jal a208 <strcmp>
    8120:	c0 2e       	beqz38 $r0,817c <Cmd_Meta_get+0x90>
    8122:	44 00 7e 70 	movi $r0,#0x7e70
    8126:	b4 26       	lwi450 $r1,[$r6]
    8128:	49 00 10 70 	jal a208 <strcmp>
    812c:	c0 40       	beqz38 $r0,81ac <Cmd_Meta_get+0xc0>
    812e:	44 00 7e 7c 	movi $r0,#0x7e7c
    8132:	b4 26       	lwi450 $r1,[$r6]
    8134:	49 00 10 6a 	jal a208 <strcmp>
    8138:	c0 44       	beqz38 $r0,81c0 <Cmd_Meta_get+0xd4>
    813a:	44 00 01 38 	movi $r0,#0x138
    813e:	49 ff d1 7f 	jal 243c <printf>
    8142:	d5 0a       	j8 8156 <Cmd_Meta_get+0x6a>
    8144:	44 10 10 00 	movi $r1,#0x1000
    8148:	84 41       	movi55 $r2,#0x1
    814a:	46 03 00 11 	sethi $r0,#0x30011
    814e:	58 00 00 00 	ori $r0,$r0,#0x0
    8152:	49 ff c9 09 	jal 1364 <drv_comport_write_fifo>
    8156:	84 00       	movi55 $r0,#0x0
    8158:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    815c:	dd 9e       	ret5 $lp
    815e:	92 00       	nop16
    8160:	44 10 10 00 	movi $r1,#0x1000
    8164:	84 41       	movi55 $r2,#0x1
    8166:	46 03 00 10 	sethi $r0,#0x30010
    816a:	58 00 00 00 	ori $r0,$r0,#0x0
    816e:	49 ff c8 fb 	jal 1364 <drv_comport_write_fifo>
    8172:	84 00       	movi55 $r0,#0x0
    8174:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    8178:	dd 9e       	ret5 $lp
    817a:	92 00       	nop16
    817c:	44 10 10 00 	movi $r1,#0x1000
    8180:	84 41       	movi55 $r2,#0x1
    8182:	46 03 00 13 	sethi $r0,#0x30013
    8186:	58 00 00 00 	ori $r0,$r0,#0x0
    818a:	49 ff c8 ed 	jal 1364 <drv_comport_write_fifo>
    818e:	d5 e4       	j8 8156 <Cmd_Meta_get+0x6a>
    8190:	44 10 10 00 	movi $r1,#0x1000
    8194:	84 41       	movi55 $r2,#0x1
    8196:	46 03 00 12 	sethi $r0,#0x30012
    819a:	58 00 00 00 	ori $r0,$r0,#0x0
    819e:	49 ff c8 e3 	jal 1364 <drv_comport_write_fifo>
    81a2:	84 00       	movi55 $r0,#0x0
    81a4:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    81a8:	dd 9e       	ret5 $lp
    81aa:	92 00       	nop16
    81ac:	44 10 10 00 	movi $r1,#0x1000
    81b0:	84 41       	movi55 $r2,#0x1
    81b2:	46 03 00 14 	sethi $r0,#0x30014
    81b6:	58 00 00 00 	ori $r0,$r0,#0x0
    81ba:	49 ff c8 d5 	jal 1364 <drv_comport_write_fifo>
    81be:	d5 cc       	j8 8156 <Cmd_Meta_get+0x6a>
    81c0:	44 10 20 00 	movi $r1,#0x2000
    81c4:	84 41       	movi55 $r2,#0x1
    81c6:	46 03 00 15 	sethi $r0,#0x30015
    81ca:	58 00 00 00 	ori $r0,$r0,#0x0
    81ce:	49 ff c8 cb 	jal 1364 <drv_comport_write_fifo>
    81d2:	d5 c2       	j8 8156 <Cmd_Meta_get+0x6a>

000081d4 <flash_write_cfg>:
    81d4:	3a 6f a0 bc 	smw.adm $r6,[$sp],$r8,#0x2    ! {$r6~$r8, $lp}
    81d8:	ef f8       	addi10.sp #-8
    81da:	95 c4       	slli333 $r7,$r0,#0x4
    81dc:	f1 81       	swi37.sp $r1,[+#0x4]
    81de:	b6 5f       	swi450 $r2,[$sp]
    81e0:	92 e4       	srli45 $r7,#0x4
    81e2:	49 ff c2 0b 	jal 5f8 <ota_flash_init>
    81e6:	f1 01       	lwi37.sp $r1,[+#0x4]
    81e8:	04 2f 80 00 	lwi $r2,[$sp+#0x0]
    81ec:	3e 08 19 f8 	addi.gp $r0,#0x19f8
    81f0:	49 00 0e b2 	jal 9f54 <memcpy>
    81f4:	3e 68 19 f8 	addi.gp $r6,#0x19f8
    81f8:	50 03 80 00 	addi $r0,$r7,#0x0
    81fc:	49 ff c1 86 	jal 508 <ota_flash_sector_erase>
    8200:	3e 88 29 f8 	addi.gp $r8,#0x29f8
    8204:	8a e6       	sub45 $r7,$r6
    8206:	98 3e       	add333 $r0,$r7,$r6
    8208:	50 23 00 00 	addi $r2,$r6,#0x0
    820c:	44 10 01 00 	movi $r1,#0x100
    8210:	50 63 01 00 	addi $r6,$r6,#0x100
    8214:	49 ff c1 b0 	jal 574 <ota_flash_page_program>
    8218:	4c 64 7f f7 	bne $r6,$r8,8206 <flash_write_cfg+0x32>
    821c:	ec 08       	addi10.sp #0x8
    821e:	3a 6f a0 84 	lmw.bim $r6,[$sp],$r8,#0x2    ! {$r6~$r8, $lp}
    8222:	dd 9e       	ret5 $lp

00008224 <Cmd_Meta_restore>:
    8224:	3a 6f a0 bc 	smw.adm $r6,[$sp],$r8,#0x2    ! {$r6~$r8, $lp}
    8228:	3e 08 09 f8 	addi.gp $r0,#0x9f8
    822c:	80 c1       	mov55 $r6,$r1
    822e:	44 20 10 00 	movi $r2,#0x1000
    8232:	84 20       	movi55 $r1,#0x0
    8234:	49 00 0e c4 	jal 9fbc <memset>
    8238:	44 00 7e 4c 	movi $r0,#0x7e4c
    823c:	b4 26       	lwi450 $r1,[$r6]
    823e:	49 00 0f e5 	jal a208 <strcmp>
    8242:	c8 25       	bnez38 $r0,828c <Cmd_Meta_restore+0x68>
    8244:	a0 31       	lwi333 $r0,[$r6+#0x4]
    8246:	49 00 0d 03 	jal 9c4c <atoi>
    824a:	80 c0       	mov55 $r6,$r0
    824c:	44 00 7e 94 	movi $r0,#0x7e94
    8250:	46 73 00 10 	sethi $r7,#0x30010
    8254:	58 73 80 00 	ori $r7,$r7,#0x0
    8258:	49 ff d0 f2 	jal 243c <printf>
    825c:	4e 62 00 54 	beqz $r6,8304 <Cmd_Meta_restore+0xe0>
    8260:	80 26       	mov55 $r1,$r6
    8262:	3e 08 09 f8 	addi.gp $r0,#0x9f8
    8266:	49 ff c6 3f 	jal ee4 <getDatafromUart>
    826a:	80 07       	mov55 $r0,$r7
    826c:	3e 18 09 f8 	addi.gp $r1,#0x9f8
    8270:	40 23 00 13 	zeh $r2,$r6
    8274:	49 ff ff b0 	jal 81d4 <flash_write_cfg>
    8278:	44 00 7e 94 	movi $r0,#0x7e94
    827c:	49 ff d0 e0 	jal 243c <printf>
    8280:	84 00       	movi55 $r0,#0x0
    8282:	92 00       	nop16
    8284:	3a 6f a0 84 	lmw.bim $r6,[$sp],$r8,#0x2    ! {$r6~$r8, $lp}
    8288:	dd 9e       	ret5 $lp
    828a:	92 00       	nop16
    828c:	44 00 7e 64 	movi $r0,#0x7e64
    8290:	b4 26       	lwi450 $r1,[$r6]
    8292:	49 00 0f bb 	jal a208 <strcmp>
    8296:	c8 0f       	bnez38 $r0,82b4 <Cmd_Meta_restore+0x90>
    8298:	a0 31       	lwi333 $r0,[$r6+#0x4]
    829a:	49 00 0c d9 	jal 9c4c <atoi>
    829e:	80 c0       	mov55 $r6,$r0
    82a0:	44 00 7e 94 	movi $r0,#0x7e94
    82a4:	46 73 00 11 	sethi $r7,#0x30011
    82a8:	58 73 80 00 	ori $r7,$r7,#0x0
    82ac:	49 ff d0 c8 	jal 243c <printf>
    82b0:	d5 d6       	j8 825c <Cmd_Meta_restore+0x38>
    82b2:	92 00       	nop16
    82b4:	44 00 7e 68 	movi $r0,#0x7e68
    82b8:	b4 26       	lwi450 $r1,[$r6]
    82ba:	49 00 0f a7 	jal a208 <strcmp>
    82be:	c0 15       	beqz38 $r0,82e8 <Cmd_Meta_restore+0xc4>
    82c0:	44 00 7e 6c 	movi $r0,#0x7e6c
    82c4:	b4 26       	lwi450 $r1,[$r6]
    82c6:	49 00 0f a1 	jal a208 <strcmp>
    82ca:	c8 1f       	bnez38 $r0,8308 <Cmd_Meta_restore+0xe4>
    82cc:	a0 31       	lwi333 $r0,[$r6+#0x4]
    82ce:	49 00 0c bf 	jal 9c4c <atoi>
    82d2:	80 c0       	mov55 $r6,$r0
    82d4:	44 00 7e 94 	movi $r0,#0x7e94
    82d8:	46 73 00 13 	sethi $r7,#0x30013
    82dc:	58 73 80 00 	ori $r7,$r7,#0x0
    82e0:	49 ff d0 ae 	jal 243c <printf>
    82e4:	48 ff ff bc 	j 825c <Cmd_Meta_restore+0x38>
    82e8:	a0 31       	lwi333 $r0,[$r6+#0x4]
    82ea:	49 00 0c b1 	jal 9c4c <atoi>
    82ee:	80 c0       	mov55 $r6,$r0
    82f0:	44 00 7e 94 	movi $r0,#0x7e94
    82f4:	46 73 00 12 	sethi $r7,#0x30012
    82f8:	58 73 80 00 	ori $r7,$r7,#0x0
    82fc:	49 ff d0 a0 	jal 243c <printf>
    8300:	48 ff ff ae 	j 825c <Cmd_Meta_restore+0x38>
    8304:	84 1f       	movi55 $r0,#-1
    8306:	d5 bf       	j8 8284 <Cmd_Meta_restore+0x60>
    8308:	44 00 7e 70 	movi $r0,#0x7e70
    830c:	b4 26       	lwi450 $r1,[$r6]
    830e:	49 00 0f 7d 	jal a208 <strcmp>
    8312:	c0 15       	beqz38 $r0,833c <Cmd_Meta_restore+0x118>
    8314:	44 00 7e 7c 	movi $r0,#0x7e7c
    8318:	b4 26       	lwi450 $r1,[$r6]
    831a:	49 00 0f 77 	jal a208 <strcmp>
    831e:	c8 1d       	bnez38 $r0,8358 <Cmd_Meta_restore+0x134>
    8320:	a0 31       	lwi333 $r0,[$r6+#0x4]
    8322:	49 00 0c 95 	jal 9c4c <atoi>
    8326:	80 c0       	mov55 $r6,$r0
    8328:	44 00 7e 94 	movi $r0,#0x7e94
    832c:	46 73 00 15 	sethi $r7,#0x30015
    8330:	58 73 80 00 	ori $r7,$r7,#0x0
    8334:	49 ff d0 84 	jal 243c <printf>
    8338:	48 ff ff 92 	j 825c <Cmd_Meta_restore+0x38>
    833c:	a0 31       	lwi333 $r0,[$r6+#0x4]
    833e:	49 00 0c 87 	jal 9c4c <atoi>
    8342:	80 c0       	mov55 $r6,$r0
    8344:	44 00 7e 94 	movi $r0,#0x7e94
    8348:	46 73 00 14 	sethi $r7,#0x30014
    834c:	58 73 80 00 	ori $r7,$r7,#0x0
    8350:	49 ff d0 76 	jal 243c <printf>
    8354:	48 ff ff 84 	j 825c <Cmd_Meta_restore+0x38>
    8358:	44 00 7e 98 	movi $r0,#0x7e98
    835c:	49 ff d0 70 	jal 243c <printf>
    8360:	84 1f       	movi55 $r0,#-1
    8362:	48 ff ff 91 	j 8284 <Cmd_Meta_restore+0x60>
    8366:	92 00       	nop16

00008368 <hex_dump>:
    8368:	3a 6f a4 bc 	smw.adm $r6,[$sp],$r9,#0x2    ! {$r6~$r9, $lp}
    836c:	ef f4       	addi10.sp #-12
    836e:	80 e0       	mov55 $r7,$r0
    8370:	44 00 7e a4 	movi $r0,#0x7ea4
    8374:	81 21       	mov55 $r9,$r1
    8376:	84 c0       	movi55 $r6,#0x0
    8378:	49 ff d0 62 	jal 243c <printf>
    837c:	b6 df       	swi450 $r6,[$sp]
    837e:	44 00 7e b0 	movi $r0,#0x7eb0
    8382:	8c c4       	addi45 $r6,#0x4
    8384:	49 ff d0 5c 	jal 243c <printf>
    8388:	5a 68 20 fa 	bnec $r6,#0x20,837c <hex_dump+0x14>
    838c:	44 00 7e c0 	movi $r0,#0x7ec0
    8390:	49 ff d0 56 	jal 243c <printf>
    8394:	84 c8       	movi55 $r6,#0x8
    8396:	8e c1       	subi45 $r6,#0x1
    8398:	44 00 7e cc 	movi $r0,#0x7ecc
    839c:	49 ff d0 50 	jal 243c <printf>
    83a0:	ce fb       	bnez38 $r6,8396 <hex_dump+0x2e>
    83a2:	85 00       	movi55 $r8,#0x0
    83a4:	4e 92 00 18 	beqz $r9,83d4 <hex_dump+0x6c>
    83a8:	80 c7       	mov55 $r6,$r7
    83aa:	a2 31       	lwi333.bi $r0,[$r6],#0x4
    83ac:	f0 81       	swi37.sp $r0,[+#0x4]
    83ae:	b6 ff       	swi450 $r7,[$sp]
    83b0:	44 00 7e d8 	movi $r0,#0x7ed8
    83b4:	49 ff d0 44 	jal 243c <printf>
    83b8:	50 73 80 20 	addi $r7,$r7,#0x20
    83bc:	a2 b1       	lwi333.bi $r2,[$r6],#0x4
    83be:	b6 5f       	swi450 $r2,[$sp]
    83c0:	44 00 7e e8 	movi $r0,#0x7ee8
    83c4:	49 ff d0 3c 	jal 243c <printf>
    83c8:	4c 73 7f fa 	bne $r7,$r6,83bc <hex_dump+0x54>
    83cc:	8d 08       	addi45 $r8,#0x8
    83ce:	e3 09       	slt45 $r8,$r9
    83d0:	e9 ec       	bnezs8 83a8 <hex_dump+0x40>
    83d2:	92 00       	nop16
    83d4:	44 00 00 e4 	movi $r0,#0xe4
    83d8:	ec 0c       	addi10.sp #0xc
    83da:	3a 6f a4 84 	lmw.bim $r6,[$sp],$r9,#0x2    ! {$r6~$r9, $lp}
    83de:	48 ff d0 2f 	j 243c <printf>
    83e2:	92 00       	nop16

000083e4 <Cmd_ReadReg32>:
    83e4:	4e 07 00 30 	blez $r0,8444 <Cmd_ReadReg32+0x60>
    83e8:	3a 6f 9c bc 	smw.adm $r6,[$sp],$r7,#0x2    ! {$r6~$r7, $lp}
    83ec:	ef f4       	addi10.sp #-12
    83ee:	80 61       	mov55 $r3,$r1
    83f0:	b4 c1       	lwi450 $r6,[$r1]
    83f2:	84 20       	movi55 $r1,#0x0
    83f4:	5a 00 02 13 	beqc $r0,#0x2,841a <Cmd_ReadReg32+0x36>
    83f8:	fa 40       	movpi45 $r2,#0x10
    83fa:	80 06       	mov55 $r0,$r6
    83fc:	49 00 0f dd 	jal a3b6 <strtoul>
    8400:	80 40       	mov55 $r2,$r0
    8402:	b4 02       	lwi450 $r0,[$r2]
    8404:	f0 81       	swi37.sp $r0,[+#0x4]
    8406:	b6 5f       	swi450 $r2,[$sp]
    8408:	44 00 7e f0 	movi $r0,#0x7ef0
    840c:	49 ff d0 18 	jal 243c <printf>
    8410:	84 00       	movi55 $r0,#0x0
    8412:	ec 0c       	addi10.sp #0xc
    8414:	3a 6f 9c 84 	lmw.bim $r6,[$sp],$r7,#0x2    ! {$r6~$r7, $lp}
    8418:	dd 9e       	ret5 $lp
    841a:	84 4a       	movi55 $r2,#0xa
    841c:	a0 19       	lwi333 $r0,[$r3+#0x4]
    841e:	49 00 0f cc 	jal a3b6 <strtoul>
    8422:	80 e0       	mov55 $r7,$r0
    8424:	fa 40       	movpi45 $r2,#0x10
    8426:	80 06       	mov55 $r0,$r6
    8428:	84 20       	movi55 $r1,#0x0
    842a:	49 00 0f c6 	jal a3b6 <strtoul>
    842e:	80 40       	mov55 $r2,$r0
    8430:	5a 70 01 e9 	beqc $r7,#0x1,8402 <Cmd_ReadReg32+0x1e>
    8434:	80 27       	mov55 $r1,$r7
    8436:	49 ff ff 99 	jal 8368 <hex_dump>
    843a:	84 00       	movi55 $r0,#0x0
    843c:	ec 0c       	addi10.sp #0xc
    843e:	3a 6f 9c 84 	lmw.bim $r6,[$sp],$r7,#0x2    ! {$r6~$r7, $lp}
    8442:	dd 9e       	ret5 $lp
    8444:	84 1f       	movi55 $r0,#-1
    8446:	dd 9e       	ret5 $lp

00008448 <gCliCmdTable>:
    8448:	14 7f 00 00 78 7f 00 00 38 01 00 00 1c 7f 00 00     ....x...8.......
    8458:	e4 83 00 00 38 01 00 00 24 7f 00 00 40 7d 00 00     ....8...$...@}..
    8468:	2c 7f 00 00 3c 7f 00 00 68 80 00 00 2c 7f 00 00     ,...<...h...,...
    8478:	48 7f 00 00 ec 80 00 00 2c 7f 00 00 54 7f 00 00     H.......,...T...
    8488:	24 82 00 00 2c 7f 00 00 64 7f 00 00 64 7d 00 00     $...,...d...d}..
    8498:	2c 7f 00 00 70 7f 00 00 c0 7f 00 00 2c 7f 00 00     ,...p.......,...
	...

000084b4 <hal_uart_irq_handler>:
    84b4:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    84b8:	46 6c 00 00 	sethi $r6,#0xc0000
    84bc:	04 03 03 0b 	lwi $r0,[$r6+#0xc2c]
    84c0:	4e 02 00 0e 	beqz $r0,84dc <hal_uart_irq_handler+0x28>
    84c4:	54 10 01 e0 	andi $r1,$r0,#0x1e0
    84c8:	c1 0e       	beqz38 $r1,84e4 <hal_uart_irq_handler+0x30>
    84ca:	3c 0c 0a 80 	lwi.gp $r0,[+#0x2a00]
    84ce:	c0 f7       	beqz38 $r0,84bc <hal_uart_irq_handler+0x8>
    84d0:	4b e0 00 01 	jral $lp,$r0
    84d4:	04 03 03 0b 	lwi $r0,[$r6+#0xc2c]
    84d8:	4e 03 ff f6 	bnez $r0,84c4 <hal_uart_irq_handler+0x10>
    84dc:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    84e0:	4a 00 78 20 	ret $lp
    84e4:	54 10 00 02 	andi $r1,$r0,#0x2
    84e8:	c9 0a       	bnez38 $r1,84fc <hal_uart_irq_handler+0x48>
    84ea:	96 44       	xlsb33 $r1,$r0
    84ec:	c9 08       	bnez38 $r1,84fc <hal_uart_irq_handler+0x48>
    84ee:	54 10 02 00 	andi $r1,$r0,#0x200
    84f2:	c1 09       	beqz38 $r1,8504 <hal_uart_irq_handler+0x50>
    84f4:	3c 0c 0a 81 	lwi.gp $r0,[+#0x2a04]
    84f8:	c8 ec       	bnez38 $r0,84d0 <hal_uart_irq_handler+0x1c>
    84fa:	d5 e1       	j8 84bc <hal_uart_irq_handler+0x8>
    84fc:	3c 0c 0a 7e 	lwi.gp $r0,[+#0x29f8]
    8500:	c8 e8       	bnez38 $r0,84d0 <hal_uart_irq_handler+0x1c>
    8502:	d5 dd       	j8 84bc <hal_uart_irq_handler+0x8>
    8504:	96 16       	bmski33 $r0,#0x2
    8506:	c0 db       	beqz38 $r0,84bc <hal_uart_irq_handler+0x8>
    8508:	3c 0c 0a 83 	lwi.gp $r0,[+#0x2a0c]
    850c:	c8 e2       	bnez38 $r0,84d0 <hal_uart_irq_handler+0x1c>
    850e:	d5 d7       	j8 84bc <hal_uart_irq_handler+0x8>

00008510 <hal_uart_register_isr>:
    8510:	c1 10       	beqz38 $r1,8530 <hal_uart_register_isr+0x20>
    8512:	3e 28 29 f8 	addi.gp $r2,#0x29f8
    8516:	38 11 02 0a 	sw $r1,[$r2+($r0<<#0x2)]
    851a:	46 1c 00 00 	sethi $r1,#0xc0000
    851e:	04 20 83 01 	lwi $r2,[$r1+#0xc04]
    8522:	84 61       	movi55 $r3,#0x1
    8524:	40 01 80 0c 	sll $r0,$r3,$r0
    8528:	fe 17       	or33 $r0,$r2
    852a:	14 00 83 01 	swi $r0,[$r1+#0xc04]
    852e:	dd 9e       	ret5 $lp
    8530:	46 3c 00 00 	sethi $r3,#0xc0000
    8534:	04 41 83 01 	lwi $r4,[$r3+#0xc04]
    8538:	84 41       	movi55 $r2,#0x1
    853a:	40 21 00 0c 	sll $r2,$r2,$r0
    853e:	40 22 08 12 	bitc $r2,$r4,$r2
    8542:	14 21 83 01 	swi $r2,[$r3+#0xc04]
    8546:	3e 28 29 f8 	addi.gp $r2,#0x29f8
    854a:	38 11 02 0a 	sw $r1,[$r2+($r0<<#0x2)]
    854e:	dd 9e       	ret5 $lp

00008550 <hal_uart_init>:
    8550:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    8554:	44 10 84 b4 	movi $r1,#0x84b4
    8558:	fa 0b       	movpi45 $r0,#0x1b
    855a:	49 00 02 c9 	jal 8aec <intc_group31_irq_enable>
    855e:	fa 0f       	movpi45 $r0,#0x1f
    8560:	49 00 02 6e 	jal 8a3c <intc_irq_enable>
    8564:	46 1c 00 00 	sethi $r1,#0xc0000
    8568:	04 00 80 08 	lwi $r0,[$r1+#0x20]
    856c:	58 00 10 00 	ori $r0,$r0,#0x1000
    8570:	14 00 80 08 	swi $r0,[$r1+#0x20]
    8574:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    8578:	dd 9e       	ret5 $lp
    857a:	92 00       	nop16

0000857c <hal_uart_deinit>:
    857c:	fa 0b       	movpi45 $r0,#0x1b
    857e:	48 00 02 d3 	j 8b24 <intc_group31_irq_disable>
    8582:	92 00       	nop16

00008584 <hal_uart_set_format>:
    8584:	46 40 00 e0 	sethi $r4,#0xe0
    8588:	9f 41       	subi333 $r5,$r0,#0x1
    858a:	50 42 0f ff 	addi $r4,$r4,#0xfff
    858e:	e2 85       	slt45 $r4,$r5
    8590:	e9 1a       	bnezs8 85c4 <hal_uart_set_format+0x40>
    8592:	46 40 00 f4 	sethi $r4,#0xf4
    8596:	44 50 00 a0 	movi $r5,#0xa0
    859a:	94 db       	slli333 $r3,$r3,#0x3
    859c:	50 42 02 40 	addi $r4,$r4,#0x240
    85a0:	54 31 80 38 	andi $r3,$r3,#0x38
    85a4:	ff 2c       	mul33 $r4,$r5
    85a6:	96 4f       	fexti33 $r1,#0x1
    85a8:	94 92       	slli333 $r2,$r2,#0x2
    85aa:	fe 5f       	or33 $r1,$r3
    85ac:	96 96       	bmski33 $r2,#0x2
    85ae:	46 3c 00 00 	sethi $r3,#0xc0000
    85b2:	40 02 00 17 	divr $r0,$r0,$r4,$r0
    85b6:	fe 8f       	or33 $r2,$r1
    85b8:	14 01 83 07 	swi $r0,[$r3+#0xc1c]
    85bc:	84 00       	movi55 $r0,#0x0
    85be:	14 21 83 03 	swi $r2,[$r3+#0xc0c]
    85c2:	dd 9e       	ret5 $lp
    85c4:	84 1d       	movi55 $r0,#-3
    85c6:	dd 9e       	ret5 $lp

000085c8 <hal_uart_direct_read_byte>:
    85c8:	46 0c 00 00 	sethi $r0,#0xc0000
    85cc:	04 00 03 00 	lwi $r0,[$r0+#0xc00]
    85d0:	dd 9e       	ret5 $lp
    85d2:	92 00       	nop16

000085d4 <hal_uart_write_fifo>:
    85d4:	80 60       	mov55 $r3,$r0
    85d6:	c0 4b       	beqz38 $r0,866c <hal_uart_write_fifo+0x98>
    85d8:	c2 1e       	beqz38 $r2,8614 <hal_uart_write_fifo+0x40>
    85da:	84 00       	movi55 $r0,#0x0
    85dc:	46 4c 00 00 	sethi $r4,#0xc0000
    85e0:	4e 17 00 4a 	blez $r1,8674 <hal_uart_write_fifo+0xa0>
    85e4:	04 22 03 05 	lwi $r2,[$r4+#0xc14]
    85e8:	42 21 14 0b 	btst $r2,$r2,#0x5
    85ec:	c2 fc       	beqz38 $r2,85e4 <hal_uart_write_fifo+0x10>
    85ee:	e4 31       	sltsi45 $r1,#0x11
    85f0:	e9 0f       	bnezs8 860e <hal_uart_write_fifo+0x3a>
    85f2:	8e 30       	subi45 $r1,#0x10
    85f4:	fb 80       	movpi45 $r16,#0x10
    85f6:	92 00       	nop16
    85f8:	40 51 c0 00 	add $r5,$r3,$r16
    85fc:	08 21 80 01 	lbi.bi $r2,[$r3],#0x1
    8600:	14 22 03 00 	swi $r2,[$r4+#0xc00]
    8604:	4c 32 ff fc 	bne $r3,$r5,85fc <hal_uart_write_fifo+0x28>
    8608:	88 10       	add45 $r0,$r16
    860a:	c9 ed       	bnez38 $r1,85e4 <hal_uart_write_fifo+0x10>
    860c:	dd 9e       	ret5 $lp
    860e:	82 01       	mov55 $r16,$r1
    8610:	84 20       	movi55 $r1,#0x0
    8612:	d5 f3       	j8 85f8 <hal_uart_write_fifo+0x24>
    8614:	46 2c 00 00 	sethi $r2,#0xc0000
    8618:	50 21 0c 00 	addi $r2,$r2,#0xc00
    861c:	a0 15       	lwi333 $r0,[$r2+#0x14]
    861e:	42 00 18 0b 	btst $r0,$r0,#0x6
    8622:	c0 13       	beqz38 $r0,8648 <hal_uart_write_fifo+0x74>
    8624:	fa 00       	movpi45 $r0,#0x10
    8626:	42 10 80 01 	min $r1,$r1,$r0
    862a:	92 00       	nop16
    862c:	4e 17 00 25 	blez $r1,8676 <hal_uart_write_fifo+0xa2>
    8630:	99 19       	add333 $r4,$r3,$r1
    8632:	46 2c 00 00 	sethi $r2,#0xc0000
    8636:	92 00       	nop16
    8638:	08 01 80 01 	lbi.bi $r0,[$r3],#0x1
    863c:	14 01 03 00 	swi $r0,[$r2+#0xc00]
    8640:	4c 32 7f fc 	bne $r3,$r4,8638 <hal_uart_write_fifo+0x64>
    8644:	80 01       	mov55 $r0,$r1
    8646:	dd 9e       	ret5 $lp
    8648:	a1 15       	lwi333 $r4,[$r2+#0x14]
    864a:	84 00       	movi55 $r0,#0x0
    864c:	42 42 14 0b 	btst $r4,$r4,#0x5
    8650:	c4 10       	beqz38 $r4,8670 <hal_uart_write_fifo+0x9c>
    8652:	04 01 00 0a 	lwi $r0,[$r2+#0x28]
    8656:	96 1f       	fexti33 $r0,#0x3
    8658:	52 00 00 10 	subri $r0,$r0,#0x10
    865c:	e0 20       	slts45 $r1,$r0
    865e:	e9 e7       	bnezs8 862c <hal_uart_write_fifo+0x58>
    8660:	04 11 00 0a 	lwi $r1,[$r2+#0x28]
    8664:	96 5f       	fexti33 $r1,#0x3
    8666:	52 10 80 10 	subri $r1,$r1,#0x10
    866a:	d5 e3       	j8 8630 <hal_uart_write_fifo+0x5c>
    866c:	84 17       	movi55 $r0,#-9
    866e:	92 00       	nop16
    8670:	dd 9e       	ret5 $lp
    8672:	92 00       	nop16
    8674:	dd 9e       	ret5 $lp
    8676:	84 00       	movi55 $r0,#0x0
    8678:	dd 9e       	ret5 $lp
    867a:	92 00       	nop16

0000867c <hal_uart_read_fifo>:
    867c:	80 80       	mov55 $r4,$r0
    867e:	c0 30       	beqz38 $r0,86de <hal_uart_read_fifo+0x62>
    8680:	ca 18       	bnez38 $r2,86b0 <hal_uart_read_fifo+0x34>
    8682:	4e 17 00 2a 	blez $r1,86d6 <hal_uart_read_fifo+0x5a>
    8686:	46 5c 00 00 	sethi $r5,#0xc0000
    868a:	04 02 83 05 	lwi $r0,[$r5+#0xc14]
    868e:	88 24       	add45 $r1,$r4
    8690:	96 04       	xlsb33 $r0,$r0
    8692:	80 44       	mov55 $r2,$r4
    8694:	c8 06       	bnez38 $r0,86a0 <hal_uart_read_fifo+0x24>
    8696:	d5 23       	j8 86dc <hal_uart_read_fifo+0x60>
    8698:	04 32 83 05 	lwi $r3,[$r5+#0xc14]
    869c:	96 dc       	xlsb33 $r3,$r3
    869e:	c3 1b       	beqz38 $r3,86d4 <hal_uart_read_fifo+0x58>
    86a0:	04 02 83 00 	lwi $r0,[$r5+#0xc00]
    86a4:	18 01 00 01 	sbi.bi $r0,[$r2],#0x1
    86a8:	9a 14       	sub333 $r0,$r2,$r4
    86aa:	4c 20 ff f7 	bne $r2,$r1,8698 <hal_uart_read_fifo+0x1c>
    86ae:	dd 9e       	ret5 $lp
    86b0:	4e 17 00 13 	blez $r1,86d6 <hal_uart_read_fifo+0x5a>
    86b4:	88 01       	add45 $r0,$r1
    86b6:	46 3c 00 00 	sethi $r3,#0xc0000
    86ba:	92 00       	nop16
    86bc:	04 21 83 05 	lwi $r2,[$r3+#0xc14]
    86c0:	96 94       	xlsb33 $r2,$r2
    86c2:	c2 fd       	beqz38 $r2,86bc <hal_uart_read_fifo+0x40>
    86c4:	04 21 83 00 	lwi $r2,[$r3+#0xc00]
    86c8:	18 22 00 01 	sbi.bi $r2,[$r4],#0x1
    86cc:	4c 40 7f f8 	bne $r4,$r0,86bc <hal_uart_read_fifo+0x40>
    86d0:	80 01       	mov55 $r0,$r1
    86d2:	dd 9e       	ret5 $lp
    86d4:	dd 9e       	ret5 $lp
    86d6:	84 00       	movi55 $r0,#0x0
    86d8:	dd 9e       	ret5 $lp
    86da:	92 00       	nop16
    86dc:	dd 9e       	ret5 $lp
    86de:	84 17       	movi55 $r0,#-9
    86e0:	dd 9e       	ret5 $lp
    86e2:	92 00       	nop16

000086e4 <hal_uart_sw_rst>:
    86e4:	fa 30       	movpi45 $r1,#0x20
    86e6:	46 0c 00 00 	sethi $r0,#0xc0000
    86ea:	b6 20       	swi450 $r1,[$r0]
    86ec:	dd 9e       	ret5 $lp
    86ee:	92 00       	nop16

000086f0 <hal_uart_get_line_status>:
    86f0:	46 0c 00 00 	sethi $r0,#0xc0000
    86f4:	50 00 0c 00 	addi $r0,$r0,#0xc00
    86f8:	a0 05       	lwi333 $r0,[$r0+#0x14]
    86fa:	dd 9e       	ret5 $lp

000086fc <hal_hsuart_irq_handler>:
    86fc:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    8700:	46 0c 00 00 	sethi $r0,#0xc0000
    8704:	50 00 0d 00 	addi $r0,$r0,#0xd00
    8708:	04 10 00 0b 	lwi $r1,[$r0+#0x2c]
    870c:	54 20 81 e0 	andi $r2,$r1,#0x1e0
    8710:	c2 0a       	beqz38 $r2,8724 <hal_hsuart_irq_handler+0x28>
    8712:	3c 0c 0a 86 	lwi.gp $r0,[+#0x2a18]
    8716:	c0 03       	beqz38 $r0,871c <hal_hsuart_irq_handler+0x20>
    8718:	4b e0 00 01 	jral $lp,$r0
    871c:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    8720:	dd 9e       	ret5 $lp
    8722:	92 00       	nop16
    8724:	54 20 80 02 	andi $r2,$r1,#0x2
    8728:	c2 08       	beqz38 $r2,8738 <hal_hsuart_irq_handler+0x3c>
    872a:	a0 05       	lwi333 $r0,[$r0+#0x14]
    872c:	96 04       	xlsb33 $r0,$r0
    872e:	c0 f7       	beqz38 $r0,871c <hal_hsuart_irq_handler+0x20>
    8730:	3c 0c 0a 84 	lwi.gp $r0,[+#0x2a10]
    8734:	c8 f2       	bnez38 $r0,8718 <hal_hsuart_irq_handler+0x1c>
    8736:	d5 f3       	j8 871c <hal_hsuart_irq_handler+0x20>
    8738:	96 0c       	xlsb33 $r0,$r1
    873a:	c8 fb       	bnez38 $r0,8730 <hal_hsuart_irq_handler+0x34>
    873c:	54 00 80 10 	andi $r0,$r1,#0x10
    8740:	c0 06       	beqz38 $r0,874c <hal_hsuart_irq_handler+0x50>
    8742:	3c 0c 0a 85 	lwi.gp $r0,[+#0x2a14]
    8746:	c8 e9       	bnez38 $r0,8718 <hal_hsuart_irq_handler+0x1c>
    8748:	48 ff ff ea 	j 871c <hal_hsuart_irq_handler+0x20>
    874c:	54 00 9e 00 	andi $r0,$r1,#0x1e00
    8750:	c0 0c       	beqz38 $r0,8768 <hal_hsuart_irq_handler+0x6c>
    8752:	3c 0c 0a 87 	lwi.gp $r0,[+#0x2a1c]
    8756:	c0 02       	beqz38 $r0,875a <hal_hsuart_irq_handler+0x5e>
    8758:	dd 20       	jral5 $r0
    875a:	84 20       	movi55 $r1,#0x0
    875c:	46 0c 00 00 	sethi $r0,#0xc0000
    8760:	14 10 03 46 	swi $r1,[$r0+#0xd18]
    8764:	d5 dc       	j8 871c <hal_hsuart_irq_handler+0x20>
    8766:	92 00       	nop16
    8768:	54 10 c0 00 	andi $r1,$r1,#0x4000
    876c:	c1 d8       	beqz38 $r1,871c <hal_hsuart_irq_handler+0x20>
    876e:	3c 0c 0a 8b 	lwi.gp $r0,[+#0x2a2c]
    8772:	c8 d3       	bnez38 $r0,8718 <hal_hsuart_irq_handler+0x1c>
    8774:	d5 d4       	j8 871c <hal_hsuart_irq_handler+0x20>
    8776:	92 00       	nop16

00008778 <hal_hsuart1_irq_handler>:
    8778:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    877c:	46 0c 00 00 	sethi $r0,#0xc0000
    8780:	50 00 0e 00 	addi $r0,$r0,#0xe00
    8784:	04 10 00 0b 	lwi $r1,[$r0+#0x2c]
    8788:	54 20 81 e0 	andi $r2,$r1,#0x1e0
    878c:	c2 0a       	beqz38 $r2,87a0 <hal_hsuart1_irq_handler+0x28>
    878e:	3c 0c 0a 8e 	lwi.gp $r0,[+#0x2a38]
    8792:	c0 03       	beqz38 $r0,8798 <hal_hsuart1_irq_handler+0x20>
    8794:	4b e0 00 01 	jral $lp,$r0
    8798:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    879c:	dd 9e       	ret5 $lp
    879e:	92 00       	nop16
    87a0:	54 20 80 02 	andi $r2,$r1,#0x2
    87a4:	c2 08       	beqz38 $r2,87b4 <hal_hsuart1_irq_handler+0x3c>
    87a6:	a0 05       	lwi333 $r0,[$r0+#0x14]
    87a8:	96 04       	xlsb33 $r0,$r0
    87aa:	c0 f7       	beqz38 $r0,8798 <hal_hsuart1_irq_handler+0x20>
    87ac:	3c 0c 0a 8c 	lwi.gp $r0,[+#0x2a30]
    87b0:	c8 f2       	bnez38 $r0,8794 <hal_hsuart1_irq_handler+0x1c>
    87b2:	d5 f3       	j8 8798 <hal_hsuart1_irq_handler+0x20>
    87b4:	96 0c       	xlsb33 $r0,$r1
    87b6:	c8 fb       	bnez38 $r0,87ac <hal_hsuart1_irq_handler+0x34>
    87b8:	54 00 80 10 	andi $r0,$r1,#0x10
    87bc:	c0 06       	beqz38 $r0,87c8 <hal_hsuart1_irq_handler+0x50>
    87be:	3c 0c 0a 8d 	lwi.gp $r0,[+#0x2a34]
    87c2:	c8 e9       	bnez38 $r0,8794 <hal_hsuart1_irq_handler+0x1c>
    87c4:	48 ff ff ea 	j 8798 <hal_hsuart1_irq_handler+0x20>
    87c8:	54 00 9e 00 	andi $r0,$r1,#0x1e00
    87cc:	c0 0c       	beqz38 $r0,87e4 <hal_hsuart1_irq_handler+0x6c>
    87ce:	3c 0c 0a 8f 	lwi.gp $r0,[+#0x2a3c]
    87d2:	c0 02       	beqz38 $r0,87d6 <hal_hsuart1_irq_handler+0x5e>
    87d4:	dd 20       	jral5 $r0
    87d6:	84 20       	movi55 $r1,#0x0
    87d8:	46 0c 00 00 	sethi $r0,#0xc0000
    87dc:	14 10 03 46 	swi $r1,[$r0+#0xd18]
    87e0:	d5 dc       	j8 8798 <hal_hsuart1_irq_handler+0x20>
    87e2:	92 00       	nop16
    87e4:	54 10 c0 00 	andi $r1,$r1,#0x4000
    87e8:	c1 d8       	beqz38 $r1,8798 <hal_hsuart1_irq_handler+0x20>
    87ea:	3c 0c 0a 93 	lwi.gp $r0,[+#0x2a4c]
    87ee:	c8 d3       	bnez38 $r0,8794 <hal_hsuart1_irq_handler+0x1c>
    87f0:	d5 d4       	j8 8798 <hal_hsuart1_irq_handler+0x20>
    87f2:	92 00       	nop16

000087f4 <hal_hsuart_register_isr_ex>:
    87f4:	3e 38 00 64 	addi.gp $r3,#0x64
    87f8:	c2 12       	beqz38 $r2,881c <hal_hsuart_register_isr_ex+0x28>
    87fa:	38 51 82 02 	lw $r5,[$r3+($r0<<#0x2)]
    87fe:	84 81       	movi55 $r4,#0x1
    8800:	a0 e9       	lwi333 $r3,[$r5+#0x4]
    8802:	94 03       	slli333 $r0,$r0,#0x3
    8804:	40 42 04 0c 	sll $r4,$r4,$r1
    8808:	88 20       	add45 $r1,$r0
    880a:	40 02 0c 04 	or $r0,$r4,$r3
    880e:	3e 38 2a 10 	addi.gp $r3,#0x2a10
    8812:	38 21 86 0a 	sw $r2,[$r3+($r1<<#0x2)]
    8816:	a8 29       	swi333 $r0,[$r5+#0x4]
    8818:	dd 9e       	ret5 $lp
    881a:	92 00       	nop16
    881c:	38 41 82 02 	lw $r4,[$r3+($r0<<#0x2)]
    8820:	84 61       	movi55 $r3,#0x1
    8822:	a1 61       	lwi333 $r5,[$r4+#0x4]
    8824:	40 31 84 0c 	sll $r3,$r3,$r1
    8828:	94 03       	slli333 $r0,$r0,#0x3
    882a:	88 20       	add45 $r1,$r0
    882c:	40 32 8c 12 	bitc $r3,$r5,$r3
    8830:	3e 08 2a 10 	addi.gp $r0,#0x2a10
    8834:	a8 e1       	swi333 $r3,[$r4+#0x4]
    8836:	38 20 06 0a 	sw $r2,[$r0+($r1<<#0x2)]
    883a:	dd 9e       	ret5 $lp

0000883c <hal_hsuart_init_ex>:
    883c:	3a 6f 98 bc 	smw.adm $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    8840:	c0 06       	beqz38 $r0,884c <hal_hsuart_init_ex+0x10>
    8842:	5a 00 01 0f 	beqc $r0,#0x1,8860 <hal_hsuart_init_ex+0x24>
    8846:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    884a:	dd 9e       	ret5 $lp
    884c:	fa 0f       	movpi45 $r0,#0x1f
    884e:	44 10 86 fc 	movi $r1,#0x86fc
    8852:	49 00 01 4d 	jal 8aec <intc_group31_irq_enable>
    8856:	fa 0f       	movpi45 $r0,#0x1f
    8858:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    885c:	48 00 00 f0 	j 8a3c <intc_irq_enable>
    8860:	fa 0f       	movpi45 $r0,#0x1f
    8862:	44 10 87 78 	movi $r1,#0x8778
    8866:	49 00 01 0b 	jal 8a7c <intc_group02_irq_enable>
    886a:	84 02       	movi55 $r0,#0x2
    886c:	3a 6f 98 84 	lmw.bim $r6,[$sp],$r6,#0x2    ! {$r6, $lp}
    8870:	48 00 00 e6 	j 8a3c <intc_irq_enable>

00008874 <hal_hsuart_deinit_ex>:
    8874:	c0 04       	beqz38 $r0,887c <hal_hsuart_deinit_ex+0x8>
    8876:	5a 00 01 06 	beqc $r0,#0x1,8882 <hal_hsuart_deinit_ex+0xe>
    887a:	dd 9e       	ret5 $lp
    887c:	fa 0f       	movpi45 $r0,#0x1f
    887e:	48 00 01 53 	j 8b24 <intc_group31_irq_disable>
    8882:	fa 0f       	movpi45 $r0,#0x1f
    8884:	48 00 01 18 	j 8ab4 <intc_group02_irq_disable>

00008888 <hal_hsuart_set_format_ex>:
    8888:	47 00 04 c4 	sethi $r16,#0x4c4
    888c:	9f 49       	subi333 $r5,$r1,#0x1
    888e:	51 08 0b 3f 	addi $r16,$r16,#0xb3f
    8892:	e3 85       	slt45 $r16,$r5
    8894:	e9 2d       	bnezs8 88ee <hal_hsuart_set_format_ex+0x66>
    8896:	47 00 00 f4 	sethi $r16,#0xf4
    889a:	51 08 02 40 	addi $r16,$r16,#0x240
    889e:	44 50 00 a0 	movi $r5,#0xa0
    88a2:	42 52 c0 24 	mul $r5,$r5,$r16
    88a6:	41 00 8c 08 	slli $r16,$r1,#0x3
    88aa:	41 12 c2 16 	divsr $r17,$r16,$r5,$r16
    88ae:	41 08 14 08 	slli $r16,$r16,#0x5
    88b2:	41 08 06 16 	divsr $r16,$r16,$r16,$r1
    88b6:	90 a3       	srai45 $r5,#0x3
    88b8:	40 12 84 36 	divsr $r1,$r1,$r5,$r1
    88bc:	95 23       	slli333 $r4,$r4,#0x3
    88be:	40 58 40 08 	slli $r5,$r16,#0x10
    88c2:	3f 08 00 64 	addi.gp $r16,#0x64
    88c6:	39 08 02 02 	lw $r16,[$r16+($r0<<#0x2)]
    88ca:	54 42 00 38 	andi $r4,$r4,#0x38
    88ce:	46 00 0f f0 	sethi $r0,#0xff0
    88d2:	96 8f       	fexti33 $r2,#0x1
    88d4:	94 da       	slli333 $r3,$r3,#0x2
    88d6:	ff 46       	and33 $r5,$r0
    88d8:	fe a7       	or33 $r2,$r4
    88da:	96 d6       	bmski33 $r3,#0x2
    88dc:	96 49       	zeh33 $r1,$r1
    88de:	fe d7       	or33 $r3,$r2
    88e0:	fe 6f       	or33 $r1,$r5
    88e2:	14 38 00 03 	swi $r3,[$r16+#0xc]
    88e6:	84 00       	movi55 $r0,#0x0
    88e8:	14 18 00 0a 	swi $r1,[$r16+#0x28]
    88ec:	dd 9e       	ret5 $lp
    88ee:	84 1d       	movi55 $r0,#-3
    88f0:	dd 9e       	ret5 $lp
    88f2:	92 00       	nop16

000088f4 <hal_hsuart_write_fifo_ex>:
    88f4:	c1 50       	beqz38 $r1,8994 <hal_hsuart_write_fifo_ex+0xa0>
    88f6:	c3 1d       	beqz38 $r3,8930 <hal_hsuart_write_fifo_ex+0x3c>
    88f8:	4e 27 00 48 	blez $r2,8988 <hal_hsuart_write_fifo_ex+0x94>
    88fc:	3e 38 00 64 	addi.gp $r3,#0x64
    8900:	38 41 82 02 	lw $r4,[$r3+($r0<<#0x2)]
    8904:	84 00       	movi55 $r0,#0x0
    8906:	a0 e5       	lwi333 $r3,[$r4+#0x14]
    8908:	42 31 94 0b 	btst $r3,$r3,#0x5
    890c:	c3 fd       	beqz38 $r3,8906 <hal_hsuart_write_fifo_ex+0x12>
    890e:	5e f1 00 21 	sltsi $r15,$r2,#0x21
    8912:	e9 3e       	bnezs8 898e <hal_hsuart_write_fifo_ex+0x9a>
    8914:	50 21 7f e0 	addi $r2,$r2,#-32
    8918:	fb 90       	movpi45 $r16,#0x20
    891a:	92 00       	nop16
    891c:	40 50 c0 00 	add $r5,$r1,$r16
    8920:	08 30 80 01 	lbi.bi $r3,[$r1],#0x1
    8924:	b6 64       	swi450 $r3,[$r4]
    8926:	4c 12 ff fd 	bne $r1,$r5,8920 <hal_hsuart_write_fifo_ex+0x2c>
    892a:	88 10       	add45 $r0,$r16
    892c:	ca ed       	bnez38 $r2,8906 <hal_hsuart_write_fifo_ex+0x12>
    892e:	dd 9e       	ret5 $lp
    8930:	3e 38 00 64 	addi.gp $r3,#0x64
    8934:	38 31 82 02 	lw $r3,[$r3+($r0<<#0x2)]
    8938:	a0 1d       	lwi333 $r0,[$r3+#0x14]
    893a:	42 00 14 0b 	btst $r0,$r0,#0x5
    893e:	c0 11       	beqz38 $r0,8960 <hal_hsuart_write_fifo_ex+0x6c>
    8940:	fa 10       	movpi45 $r0,#0x20
    8942:	42 21 00 01 	min $r2,$r2,$r0
    8946:	92 00       	nop16
    8948:	4e 27 00 20 	blez $r2,8988 <hal_hsuart_write_fifo_ex+0x94>
    894c:	99 0a       	add333 $r4,$r1,$r2
    894e:	92 00       	nop16
    8950:	08 00 80 01 	lbi.bi $r0,[$r1],#0x1
    8954:	b6 03       	swi450 $r0,[$r3]
    8956:	4c 12 7f fd 	bne $r1,$r4,8950 <hal_hsuart_write_fifo_ex+0x5c>
    895a:	80 02       	mov55 $r0,$r2
    895c:	4a 00 78 20 	ret $lp
    8960:	04 41 80 0b 	lwi $r4,[$r3+#0x2c]
    8964:	84 00       	movi55 $r0,#0x0
    8966:	97 16       	bmski33 $r4,#0x2
    8968:	c4 12       	beqz38 $r4,898c <hal_hsuart_write_fifo_ex+0x98>
    896a:	04 01 80 08 	lwi $r0,[$r3+#0x20]
    896e:	92 10       	srli45 $r0,#0x10
    8970:	96 27       	fexti33 $r0,#0x4
    8972:	52 00 00 20 	subri $r0,$r0,#0x20
    8976:	e0 40       	slts45 $r2,$r0
    8978:	e9 e8       	bnezs8 8948 <hal_hsuart_write_fifo_ex+0x54>
    897a:	04 21 80 08 	lwi $r2,[$r3+#0x20]
    897e:	92 50       	srli45 $r2,#0x10
    8980:	96 a7       	fexti33 $r2,#0x4
    8982:	52 21 00 20 	subri $r2,$r2,#0x20
    8986:	d5 e3       	j8 894c <hal_hsuart_write_fifo_ex+0x58>
    8988:	44 00 00 00 	movi $r0,#0x0
    898c:	dd 9e       	ret5 $lp
    898e:	82 02       	mov55 $r16,$r2
    8990:	84 40       	movi55 $r2,#0x0
    8992:	d5 c5       	j8 891c <hal_hsuart_write_fifo_ex+0x28>
    8994:	84 17       	movi55 $r0,#-9
    8996:	dd 9e       	ret5 $lp

00008998 <hal_hsuart_read_fifo_ex>:
    8998:	82 00       	mov55 $r16,$r0
    899a:	c1 32       	beqz38 $r1,89fe <hal_hsuart_read_fifo_ex+0x66>
    899c:	cb 1a       	bnez38 $r3,89d0 <hal_hsuart_read_fifo_ex+0x38>
    899e:	4e 27 00 2c 	blez $r2,89f6 <hal_hsuart_read_fifo_ex+0x5e>
    89a2:	3f 18 00 64 	addi.gp $r17,#0x64
    89a6:	38 58 82 02 	lw $r5,[$r17+($r0<<#0x2)]
    89aa:	88 41       	add45 $r2,$r1
    89ac:	a0 2d       	lwi333 $r0,[$r5+#0x14]
    89ae:	80 61       	mov55 $r3,$r1
    89b0:	96 04       	xlsb33 $r0,$r0
    89b2:	c8 08       	bnez38 $r0,89c2 <hal_hsuart_read_fifo_ex+0x2a>
    89b4:	d5 24       	j8 89fc <hal_hsuart_read_fifo_ex+0x64>
    89b6:	92 00       	nop16
    89b8:	38 58 c2 02 	lw $r5,[$r17+($r16<<#0x2)]
    89bc:	a1 2d       	lwi333 $r4,[$r5+#0x14]
    89be:	97 24       	xlsb33 $r4,$r4
    89c0:	c4 1a       	beqz38 $r4,89f4 <hal_hsuart_read_fifo_ex+0x5c>
    89c2:	b4 05       	lwi450 $r0,[$r5]
    89c4:	18 01 80 01 	sbi.bi $r0,[$r3],#0x1
    89c8:	9a 19       	sub333 $r0,$r3,$r1
    89ca:	4c 31 7f f7 	bne $r3,$r2,89b8 <hal_hsuart_read_fifo_ex+0x20>
    89ce:	dd 9e       	ret5 $lp
    89d0:	4e 27 00 13 	blez $r2,89f6 <hal_hsuart_read_fifo_ex+0x5e>
    89d4:	98 0a       	add333 $r0,$r1,$r2
    89d6:	3f 18 00 64 	addi.gp $r17,#0x64
    89da:	92 00       	nop16
    89dc:	38 48 c2 02 	lw $r4,[$r17+($r16<<#0x2)]
    89e0:	a0 e5       	lwi333 $r3,[$r4+#0x14]
    89e2:	96 dc       	xlsb33 $r3,$r3
    89e4:	c3 fe       	beqz38 $r3,89e0 <hal_hsuart_read_fifo_ex+0x48>
    89e6:	b4 64       	lwi450 $r3,[$r4]
    89e8:	18 30 80 01 	sbi.bi $r3,[$r1],#0x1
    89ec:	4c 10 7f f8 	bne $r1,$r0,89dc <hal_hsuart_read_fifo_ex+0x44>
    89f0:	80 02       	mov55 $r0,$r2
    89f2:	dd 9e       	ret5 $lp
    89f4:	dd 9e       	ret5 $lp
    89f6:	84 00       	movi55 $r0,#0x0
    89f8:	dd 9e       	ret5 $lp
    89fa:	92 00       	nop16
    89fc:	dd 9e       	ret5 $lp
    89fe:	84 17       	movi55 $r0,#-9
    8a00:	dd 9e       	ret5 $lp
    8a02:	92 00       	nop16

00008a04 <hal_hsuart_sw_rst_ex>:
    8a04:	c0 0a       	beqz38 $r0,8a18 <hal_hsuart_sw_rst_ex+0x14>
    8a06:	5a 00 01 03 	beqc $r0,#0x1,8a0c <hal_hsuart_sw_rst_ex+0x8>
    8a0a:	dd 9e       	ret5 $lp
    8a0c:	44 10 08 00 	movi $r1,#0x800
    8a10:	46 0c 00 00 	sethi $r0,#0xc0000
    8a14:	b6 20       	swi450 $r1,[$r0]
    8a16:	dd 9e       	ret5 $lp
    8a18:	46 10 04 00 	sethi $r1,#0x400
    8a1c:	46 0c 00 00 	sethi $r0,#0xc0000
    8a20:	b6 20       	swi450 $r1,[$r0]
    8a22:	dd 9e       	ret5 $lp

00008a24 <hal_hsuart_get_line_status_ex>:
    8a24:	3e 18 00 64 	addi.gp $r1,#0x64
    8a28:	38 00 82 02 	lw $r0,[$r1+($r0<<#0x2)]
    8a2c:	a0 05       	lwi333 $r0,[$r0+#0x14]
    8a2e:	dd 9e       	ret5 $lp

00008a30 <hal_hsuart_direct_read_byte_ex>:
    8a30:	3e 18 00 64 	addi.gp $r1,#0x64
    8a34:	38 00 82 02 	lw $r0,[$r1+($r0<<#0x2)]
    8a38:	b4 00       	lwi450 $r0,[$r0]
    8a3a:	dd 9e       	ret5 $lp

00008a3c <intc_irq_enable>:
    8a3c:	ef f8       	addi10.sp #-8
    8a3e:	64 12 00 02 	mfsr $r1,$psw
    8a42:	64 02 00 43 	setgie.d
    8a46:	46 3c 00 02 	sethi $r3,#0xc0002
    8a4a:	f1 81       	swi37.sp $r1,[+#0x4]
    8a4c:	04 21 80 30 	lwi $r2,[$r3+#0xc0]
    8a50:	84 21       	movi55 $r1,#0x1
    8a52:	40 00 80 0c 	sll $r0,$r1,$r0
    8a56:	40 11 00 12 	bitc $r1,$r2,$r0
    8a5a:	14 11 80 30 	swi $r1,[$r3+#0xc0]
    8a5e:	64 13 04 02 	mfsr $r1,$int_mask2
    8a62:	fe 0f       	or33 $r0,$r1
    8a64:	64 03 04 03 	mtsr $r0,$int_mask2
    8a68:	64 00 00 08 	dsb
    8a6c:	f0 01       	lwi37.sp $r0,[+#0x4]
    8a6e:	64 02 00 03 	mtsr $r0,$psw
    8a72:	64 00 00 09 	isb
    8a76:	ec 08       	addi10.sp #0x8
    8a78:	dd 9e       	ret5 $lp
    8a7a:	92 00       	nop16

00008a7c <intc_group02_irq_enable>:
    8a7c:	ef f8       	addi10.sp #-8
    8a7e:	64 22 00 02 	mfsr $r2,$psw
    8a82:	64 02 00 43 	setgie.d
    8a86:	f2 81       	swi37.sp $r2,[+#0x4]
    8a88:	3e 28 2a d0 	addi.gp $r2,#0x2ad0
    8a8c:	38 11 02 0a 	sw $r1,[$r2+($r0<<#0x2)]
    8a90:	46 2c 00 02 	sethi $r2,#0xc0002
    8a94:	04 31 00 27 	lwi $r3,[$r2+#0x9c]
    8a98:	84 21       	movi55 $r1,#0x1
    8a9a:	40 00 80 0c 	sll $r0,$r1,$r0
    8a9e:	40 01 80 12 	bitc $r0,$r3,$r0
    8aa2:	14 01 00 27 	swi $r0,[$r2+#0x9c]
    8aa6:	f0 01       	lwi37.sp $r0,[+#0x4]
    8aa8:	64 02 00 03 	mtsr $r0,$psw
    8aac:	64 00 00 09 	isb
    8ab0:	ec 08       	addi10.sp #0x8
    8ab2:	dd 9e       	ret5 $lp

00008ab4 <intc_group02_irq_disable>:
    8ab4:	ef f8       	addi10.sp #-8
    8ab6:	64 12 00 02 	mfsr $r1,$psw
    8aba:	64 02 00 43 	setgie.d
    8abe:	46 3c 00 02 	sethi $r3,#0xc0002
    8ac2:	f1 81       	swi37.sp $r1,[+#0x4]
    8ac4:	04 21 80 27 	lwi $r2,[$r3+#0x9c]
    8ac8:	84 21       	movi55 $r1,#0x1
    8aca:	40 10 80 0c 	sll $r1,$r1,$r0
    8ace:	fe 57       	or33 $r1,$r2
    8ad0:	14 11 80 27 	swi $r1,[$r3+#0x9c]
    8ad4:	84 40       	movi55 $r2,#0x0
    8ad6:	3e 18 2a d0 	addi.gp $r1,#0x2ad0
    8ada:	38 20 82 0a 	sw $r2,[$r1+($r0<<#0x2)]
    8ade:	f0 01       	lwi37.sp $r0,[+#0x4]
    8ae0:	64 02 00 03 	mtsr $r0,$psw
    8ae4:	64 00 00 09 	isb
    8ae8:	ec 08       	addi10.sp #0x8
    8aea:	dd 9e       	ret5 $lp

00008aec <intc_group31_irq_enable>:
    8aec:	ef f8       	addi10.sp #-8
    8aee:	64 22 00 02 	mfsr $r2,$psw
    8af2:	64 02 00 43 	setgie.d
    8af6:	f2 81       	swi37.sp $r2,[+#0x4]
    8af8:	3e 28 2a 50 	addi.gp $r2,#0x2a50
    8afc:	38 11 02 0a 	sw $r1,[$r2+($r0<<#0x2)]
    8b00:	46 2c 00 02 	sethi $r2,#0xc0002
    8b04:	04 31 00 2d 	lwi $r3,[$r2+#0xb4]
    8b08:	84 21       	movi55 $r1,#0x1
    8b0a:	40 00 80 0c 	sll $r0,$r1,$r0
    8b0e:	40 01 80 12 	bitc $r0,$r3,$r0
    8b12:	14 01 00 2d 	swi $r0,[$r2+#0xb4]
    8b16:	f0 01       	lwi37.sp $r0,[+#0x4]
    8b18:	64 02 00 03 	mtsr $r0,$psw
    8b1c:	64 00 00 09 	isb
    8b20:	ec 08       	addi10.sp #0x8
    8b22:	dd 9e       	ret5 $lp

00008b24 <intc_group31_irq_disable>:
    8b24:	ef f8       	addi10.sp #-8
    8b26:	64 12 00 02 	mfsr $r1,$psw
    8b2a:	64 02 00 43 	setgie.d
    8b2e:	46 3c 00 02 	sethi $r3,#0xc0002
    8b32:	f1 81       	swi37.sp $r1,[+#0x4]
    8b34:	04 21 80 2d 	lwi $r2,[$r3+#0xb4]
    8b38:	84 21       	movi55 $r1,#0x1
    8b3a:	40 10 80 0c 	sll $r1,$r1,$r0
    8b3e:	fe 57       	or33 $r1,$r2
    8b40:	14 11 80 2d 	swi $r1,[$r3+#0xb4]
    8b44:	84 40       	movi55 $r2,#0x0
    8b46:	3e 18 2a 50 	addi.gp $r1,#0x2a50
    8b4a:	38 20 82 0a 	sw $r2,[$r1+($r0<<#0x2)]
    8b4e:	f0 01       	lwi37.sp $r0,[+#0x4]
    8b50:	64 02 00 03 	mtsr $r0,$psw
    8b54:	64 00 00 09 	isb
    8b58:	ec 08       	addi10.sp #0x8
    8b5a:	dd 9e       	ret5 $lp

00008b5c <__udivdi3>:
    8b5c:	84 80       	movi55 $r4,#0x0
    8b5e:	d5 2d       	j8 8bb8 <__udivmoddi4>

00008b60 <fudiv_qrnnd>:
    8b60:	41 41 40 09 	srli $r20,$r2,#0x10
    8b64:	97 41       	zeh33 $r5,$r0
    8b66:	92 10       	srli45 $r0,#0x10
    8b68:	40 40 d0 37 	divr $r4,$r1,$r1,$r20
    8b6c:	96 d1       	zeh33 $r3,$r2
    8b6e:	40 10 c0 08 	slli $r1,$r1,#0x10
    8b72:	fe 47       	or33 $r1,$r0
    8b74:	42 02 0c 24 	mul $r0,$r4,$r3
    8b78:	e2 20       	slt45 $r1,$r0
    8b7a:	e8 09       	beqzs8 8b8c <fudiv_qrnnd+0x2c>
    8b7c:	9f 21       	subi333 $r4,$r4,#0x1
    8b7e:	98 4a       	add333 $r1,$r1,$r2
    8b80:	e2 22       	slt45 $r1,$r2
    8b82:	e9 05       	bnezs8 8b8c <fudiv_qrnnd+0x2c>
    8b84:	e2 20       	slt45 $r1,$r0
    8b86:	e8 03       	beqzs8 8b8c <fudiv_qrnnd+0x2c>
    8b88:	9f 21       	subi333 $r4,$r4,#0x1
    8b8a:	98 4a       	add333 $r1,$r1,$r2
    8b8c:	9a 48       	sub333 $r1,$r1,$r0
    8b8e:	40 10 d0 17 	divr $r1,$r0,$r1,$r20
    8b92:	40 00 40 08 	slli $r0,$r0,#0x10
    8b96:	fe 2f       	or33 $r0,$r5
    8b98:	fe cc       	mul33 $r3,$r1
    8b9a:	e2 03       	slt45 $r0,$r3
    8b9c:	e8 09       	beqzs8 8bae <fudiv_qrnnd+0x4e>
    8b9e:	98 02       	add333 $r0,$r0,$r2
    8ba0:	9e 49       	subi333 $r1,$r1,#0x1
    8ba2:	e2 02       	slt45 $r0,$r2
    8ba4:	e9 05       	bnezs8 8bae <fudiv_qrnnd+0x4e>
    8ba6:	e2 03       	slt45 $r0,$r3
    8ba8:	e8 03       	beqzs8 8bae <fudiv_qrnnd+0x4e>
    8baa:	98 02       	add333 $r0,$r0,$r2
    8bac:	9e 49       	subi333 $r1,$r1,#0x1
    8bae:	9a 03       	sub333 $r0,$r0,$r3
    8bb0:	40 42 40 08 	slli $r4,$r4,#0x10
    8bb4:	fe 67       	or33 $r1,$r4
    8bb6:	dd 9e       	ret5 $lp

00008bb8 <__udivmoddi4>:
    8bb8:	3b ff fe bc 	smw.adm $sp,[$sp],$sp,#0xa    ! {$fp, $lp}
    8bbc:	fd 80       	movd44 $r16,$r0
    8bbe:	fd 91       	movd44 $r18,$r2
    8bc0:	83 84       	mov55 $fp,$r4
    8bc2:	cb 4d       	bnez38 $r3,8c5c <__udivmoddi4+0xa4>
    8bc4:	e3 b2       	slt45 $r17,$r18
    8bc6:	e8 19       	beqzs8 8bf8 <__udivmoddi4+0x40>
    8bc8:	42 09 00 07 	clz $r0,$r18
    8bcc:	82 a0       	mov55 $r21,$r0
    8bce:	c0 0d       	beqz38 $r0,8be8 <__udivmoddi4+0x30>
    8bd0:	41 29 00 0c 	sll $r18,$r18,$r0
    8bd4:	52 50 00 20 	subri $r5,$r0,#0x20
    8bd8:	40 58 14 0d 	srl $r5,$r16,$r5
    8bdc:	41 18 80 0c 	sll $r17,$r17,$r0
    8be0:	41 18 94 04 	or $r17,$r17,$r5
    8be4:	41 08 00 0c 	sll $r16,$r16,$r0
    8be8:	fd 08       	movd44 $r0,$r16
    8bea:	80 52       	mov55 $r2,$r18
    8bec:	49 ff ff ba 	jal 8b60 <fudiv_qrnnd>
    8bf0:	82 c1       	mov55 $r22,$r1
    8bf2:	82 00       	mov55 $r16,$r0
    8bf4:	86 e0       	movi55 $r23,#0x0
    8bf6:	d5 23       	j8 8c3c <__udivmoddi4+0x84>
    8bf8:	c2 28       	beqz38 $r2,8c48 <__udivmoddi4+0x90>
    8bfa:	42 09 00 07 	clz $r0,$r18
    8bfe:	82 a0       	mov55 $r21,$r0
    8c00:	c8 04       	bnez38 $r0,8c08 <__udivmoddi4+0x50>
    8c02:	8b b2       	sub45 $r17,$r18
    8c04:	86 e1       	movi55 $r23,#0x1
    8c06:	d5 14       	j8 8c2e <__udivmoddi4+0x76>
    8c08:	52 f0 00 20 	subri $r15,$r0,#0x20
    8c0c:	41 29 00 0c 	sll $r18,$r18,$r0
    8c10:	80 52       	mov55 $r2,$r18
    8c12:	40 48 3c 0d 	srl $r4,$r16,$r15
    8c16:	40 58 80 0c 	sll $r5,$r17,$r0
    8c1a:	41 08 00 0c 	sll $r16,$r16,$r0
    8c1e:	40 02 90 04 	or $r0,$r5,$r4
    8c22:	40 18 bc 0d 	srl $r1,$r17,$r15
    8c26:	49 ff ff 9d 	jal 8b60 <fudiv_qrnnd>
    8c2a:	82 e1       	mov55 $r23,$r1
    8c2c:	82 20       	mov55 $r17,$r0
    8c2e:	fd 08       	movd44 $r0,$r16
    8c30:	80 52       	mov55 $r2,$r18
    8c32:	49 ff ff 97 	jal 8b60 <fudiv_qrnnd>
    8c36:	82 c1       	mov55 $r22,$r1
    8c38:	51 00 00 00 	addi $r16,$r0,#0x0
    8c3c:	4f c2 00 53 	beqz $fp,8ce2 <__udivmoddi4+0x12a>
    8c40:	86 20       	movi55 $r17,#0x0
    8c42:	41 08 54 0d 	srl $r16,$r16,$r21
    8c46:	d5 4b       	j8 8cdc <__udivmoddi4+0x124>
    8c48:	41 19 4a 17 	divr $r17,$r16,$r18,$r18
    8c4c:	84 20       	movi55 $r1,#0x0
    8c4e:	84 00       	movi55 $r0,#0x0
    8c50:	4f c2 00 4c 	beqz $fp,8ce8 <__udivmoddi4+0x130>
    8c54:	b7 9c       	swi450 $r16,[$fp]
    8c56:	15 1e 00 01 	swi $r17,[$fp+#0x4]
    8c5a:	d5 47       	j8 8ce8 <__udivmoddi4+0x130>
    8c5c:	e3 b3       	slt45 $r17,$r19
    8c5e:	e9 f7       	bnezs8 8c4c <__udivmoddi4+0x94>
    8c60:	42 09 80 07 	clz $r0,$r19
    8c64:	82 a0       	mov55 $r21,$r0
    8c66:	c0 44       	beqz38 $r0,8cee <__udivmoddi4+0x136>
    8c68:	52 40 00 20 	subri $r4,$r0,#0x20
    8c6c:	40 59 10 0d 	srl $r5,$r18,$r4
    8c70:	40 29 80 0c 	sll $r2,$r19,$r0
    8c74:	fe af       	or33 $r2,$r5
    8c76:	82 62       	mov55 $r19,$r2
    8c78:	41 29 00 0c 	sll $r18,$r18,$r0
    8c7c:	40 38 10 0d 	srl $r3,$r16,$r4
    8c80:	41 08 00 0c 	sll $r16,$r16,$r0
    8c84:	40 08 80 0c 	sll $r0,$r17,$r0
    8c88:	40 18 90 0d 	srl $r1,$r17,$r4
    8c8c:	fe 1f       	or33 $r0,$r3
    8c8e:	49 ff ff 69 	jal 8b60 <fudiv_qrnnd>
    8c92:	82 c1       	mov55 $r22,$r1
    8c94:	82 20       	mov55 $r17,$r0
    8c96:	42 00 c8 69 	mulr64 $r0,$r1,$r18
    8c9a:	e3 a1       	slt45 $r17,$r1
    8c9c:	e9 05       	bnezs8 8ca6 <__udivmoddi4+0xee>
    8c9e:	4c 18 c0 0c 	bne $r1,$r17,8cb6 <__udivmoddi4+0xfe>
    8ca2:	e3 80       	slt45 $r16,$r0
    8ca4:	e8 09       	beqzs8 8cb6 <__udivmoddi4+0xfe>
    8ca6:	51 6b 7f ff 	addi $r22,$r22,#-1
    8caa:	8a 33       	sub45 $r1,$r19
    8cac:	40 30 48 01 	sub $r3,$r0,$r18
    8cb0:	e2 03       	slt45 $r0,$r3
    8cb2:	8a 2f       	sub45 $r1,$r15
    8cb4:	80 03       	mov55 $r0,$r3
    8cb6:	86 e0       	movi55 $r23,#0x0
    8cb8:	4f c2 00 15 	beqz $fp,8ce2 <__udivmoddi4+0x12a>
    8cbc:	40 08 00 01 	sub $r0,$r16,$r0
    8cc0:	40 18 84 01 	sub $r1,$r17,$r1
    8cc4:	e3 80       	slt45 $r16,$r0
    8cc6:	8a 2f       	sub45 $r1,$r15
    8cc8:	52 4a 80 20 	subri $r4,$r21,#0x20
    8ccc:	41 10 90 0c 	sll $r17,$r1,$r4
    8cd0:	41 00 54 0d 	srl $r16,$r0,$r21
    8cd4:	41 08 44 04 	or $r16,$r16,$r17
    8cd8:	41 10 d4 0d 	srl $r17,$r1,$r21
    8cdc:	b7 9c       	swi450 $r16,[$fp]
    8cde:	15 1e 00 01 	swi $r17,[$fp+#0x4]
    8ce2:	80 16       	mov55 $r0,$r22
    8ce4:	50 1b 80 00 	addi $r1,$r23,#0x0
    8ce8:	3b ff fe 84 	lmw.bim $sp,[$sp],$sp,#0xa    ! {$fp, $lp}
    8cec:	dd 9e       	ret5 $lp
    8cee:	e3 f1       	slt45 $r19,$r17
    8cf0:	e9 03       	bnezs8 8cf6 <__udivmoddi4+0x13e>
    8cf2:	e3 92       	slt45 $r16,$r18
    8cf4:	e9 09       	bnezs8 8d06 <__udivmoddi4+0x14e>
    8cf6:	86 c1       	movi55 $r22,#0x1
    8cf8:	40 48 48 01 	sub $r4,$r16,$r18
    8cfc:	8b b3       	sub45 $r17,$r19
    8cfe:	e3 84       	slt45 $r16,$r4
    8d00:	8b af       	sub45 $r17,$r15
    8d02:	82 04       	mov55 $r16,$r4
    8d04:	d5 02       	j8 8d08 <__udivmoddi4+0x150>
    8d06:	86 c0       	movi55 $r22,#0x0
    8d08:	86 e0       	movi55 $r23,#0x0
    8d0a:	4f c3 ff e9 	bnez $fp,8cdc <__udivmoddi4+0x124>
    8d0e:	d5 ea       	j8 8ce2 <__udivmoddi4+0x12a>

00008d10 <__umoddi3>:
    8d10:	ef f4       	addi10.sp #-12
    8d12:	15 ef 80 00 	swi $lp,[$sp+#0x0]
    8d16:	b1 01       	addri36.sp $r4,#0x4
    8d18:	49 ff ff 50 	jal 8bb8 <__udivmoddi4>
    8d1c:	f0 01       	lwi37.sp $r0,[+#0x4]
    8d1e:	f1 02       	lwi37.sp $r1,[+#0x8]
    8d20:	0d ef 80 03 	lwi.bi $lp,[$sp],#0xc
    8d24:	dd 9e       	ret5 $lp
    8d26:	92 00       	nop16

00008d28 <__fixdfsi>:
    8d28:	6a 00 00 41 	fmfdr $r0,$fd0
    8d2c:	40 30 ac 08 	slli $r3,$r1,#0xb
    8d30:	40 40 54 09 	srli $r4,$r0,#0x15
    8d34:	fe e7       	or33 $r3,$r4
    8d36:	46 48 00 00 	sethi $r4,#0x80000
    8d3a:	fe e7       	or33 $r3,$r4
    8d3c:	95 09       	slli333 $r4,$r1,#0x1
    8d3e:	92 95       	srli45 $r4,#0x15
    8d40:	52 22 04 1e 	subri $r2,$r4,#0x41e
    8d44:	4e 27 00 0d 	blez $r2,8d5e <__fixdfsi+0x36>
    8d48:	fa 90       	movpi45 $r4,#0x20
    8d4a:	e2 44       	slt45 $r2,$r4
    8d4c:	e9 02       	bnezs8 8d50 <__fixdfsi+0x28>
    8d4e:	84 60       	movi55 $r3,#0x0
    8d50:	40 31 88 0d 	srl $r3,$r3,$r2
    8d54:	e4 20       	sltsi45 $r1,#0x0
    8d56:	e8 02       	beqzs8 8d5a <__fixdfsi+0x32>
    8d58:	fe da       	neg33 $r3,$r3
    8d5a:	80 03       	mov55 $r0,$r3
    8d5c:	dd 9e       	ret5 $lp
    8d5e:	c0 03       	beqz38 $r0,8d64 <__fixdfsi+0x3c>
    8d60:	58 10 80 01 	ori $r1,$r1,#0x1
    8d64:	46 47 ff 00 	sethi $r4,#0x7ff00
    8d68:	e2 81       	slt45 $r4,$r1
    8d6a:	e8 04       	beqzs8 8d72 <__fixdfsi+0x4a>
    8d6c:	46 08 00 00 	sethi $r0,#0x80000
    8d70:	dd 9e       	ret5 $lp
    8d72:	46 07 ff ff 	sethi $r0,#0x7ffff
    8d76:	58 00 0f ff 	ori $r0,$r0,#0xfff
    8d7a:	dd 9e       	ret5 $lp

00008d7c <__fixunsdfsi>:
    8d7c:	6a 00 00 41 	fmfdr $r0,$fd0
    8d80:	40 30 ac 08 	slli $r3,$r1,#0xb
    8d84:	40 40 54 09 	srli $r4,$r0,#0x15
    8d88:	fe e7       	or33 $r3,$r4
    8d8a:	46 48 00 00 	sethi $r4,#0x80000
    8d8e:	fe e7       	or33 $r3,$r4
    8d90:	95 09       	slli333 $r4,$r1,#0x1
    8d92:	92 95       	srli45 $r4,#0x15
    8d94:	52 22 04 1e 	subri $r2,$r4,#0x41e
    8d98:	e4 40       	sltsi45 $r2,#0x0
    8d9a:	e9 0c       	bnezs8 8db2 <__fixunsdfsi+0x36>
    8d9c:	fa 90       	movpi45 $r4,#0x20
    8d9e:	e2 44       	slt45 $r2,$r4
    8da0:	e9 02       	bnezs8 8da4 <__fixunsdfsi+0x28>
    8da2:	84 60       	movi55 $r3,#0x0
    8da4:	40 31 88 0d 	srl $r3,$r3,$r2
    8da8:	e4 20       	sltsi45 $r1,#0x0
    8daa:	e8 02       	beqzs8 8dae <__fixunsdfsi+0x32>
    8dac:	fe da       	neg33 $r3,$r3
    8dae:	80 03       	mov55 $r0,$r3
    8db0:	dd 9e       	ret5 $lp
    8db2:	c0 03       	beqz38 $r0,8db8 <__fixunsdfsi+0x3c>
    8db4:	58 10 80 01 	ori $r1,$r1,#0x1
    8db8:	46 47 ff 00 	sethi $r4,#0x7ff00
    8dbc:	e2 81       	slt45 $r4,$r1
    8dbe:	e8 04       	beqzs8 8dc6 <__fixunsdfsi+0x4a>
    8dc0:	46 08 00 00 	sethi $r0,#0x80000
    8dc4:	dd 9e       	ret5 $lp
    8dc6:	84 1f       	movi55 $r0,#-1
    8dc8:	dd 9e       	ret5 $lp
    8dca:	92 00       	nop16

00008dcc <__popcountsi2>:
    8dcc:	46 15 55 55 	sethi $r1,#0x55555
    8dd0:	50 10 85 55 	addi $r1,$r1,#0x555
    8dd4:	40 10 80 3e 	and_srli $r1,$r1,$r0,#0x1
    8dd8:	46 23 33 33 	sethi $r2,#0x33333
    8ddc:	50 21 03 33 	addi $r2,$r2,#0x333
    8de0:	8a 01       	sub45 $r0,$r1
    8de2:	40 10 08 02 	and $r1,$r0,$r2
    8de6:	40 01 00 5e 	and_srli $r0,$r2,$r0,#0x2
    8dea:	88 01       	add45 $r0,$r1
    8dec:	46 10 f0 f0 	sethi $r1,#0xf0f0
    8df0:	50 10 8f 0f 	addi $r1,$r1,#0xf0f
    8df4:	40 00 00 9c 	add_srli $r0,$r0,$r0,#0x4
    8df8:	fe 0e       	and33 $r0,$r1
    8dfa:	46 10 10 10 	sethi $r1,#0x1010
    8dfe:	50 10 81 01 	addi $r1,$r1,#0x101
    8e02:	fe 0c       	mul33 $r0,$r1
    8e04:	92 18       	srli45 $r0,#0x18
    8e06:	dd 9e       	ret5 $lp

00008e08 <__eqdf2>:
    8e08:	fc 20       	push25 $r8,#0    ! {$r6~$r8, $fp, $gp, $lp}
    8e0a:	6a 20 00 41 	fmfdr $r2,$fd0
    8e0e:	80 22       	mov55 $r1,$r2
    8e10:	80 83       	mov55 $r4,$r3
    8e12:	6a 20 80 41 	fmfdr $r2,$fd1
    8e16:	80 c2       	mov55 $r6,$r2
    8e18:	6a 00 07 01 	fmfcsr $r0
    8e1c:	40 02 30 08 	slli $r0,$r4,#0xc
    8e20:	40 20 30 09 	srli $r2,$r0,#0xc
    8e24:	40 02 50 09 	srli $r0,$r4,#0x14
    8e28:	40 71 d0 09 	srli $r7,$r3,#0x14
    8e2c:	97 45       	x11b33 $r5,$r0
    8e2e:	45 00 07 ff 	movi $r16,#0x7ff
    8e32:	80 06       	mov55 $r0,$r6
    8e34:	40 61 b0 08 	slli $r6,$r3,#0xc
    8e38:	92 9f       	srli45 $r4,#0x1f
    8e3a:	92 cc       	srli45 $r6,#0xc
    8e3c:	97 fd       	x11b33 $r7,$r7
    8e3e:	92 7f       	srli45 $r3,#0x1f
    8e40:	4c 58 40 05 	bne $r5,$r16,8e4a <__eqdf2+0x42>
    8e44:	40 f1 04 04 	or $r15,$r2,$r1
    8e48:	e9 15       	bnezs8 8e72 <__eqdf2+0x6a>
    8e4a:	4c 78 40 05 	bne $r7,$r16,8e54 <__eqdf2+0x4c>
    8e4e:	40 f3 00 04 	or $r15,$r6,$r0
    8e52:	e9 10       	bnezs8 8e72 <__eqdf2+0x6a>
    8e54:	df 0f       	bnes38 $r7,8e72 <__eqdf2+0x6a>
    8e56:	4c 23 40 0e 	bne $r2,$r6,8e72 <__eqdf2+0x6a>
    8e5a:	4c 10 40 0c 	bne $r1,$r0,8e72 <__eqdf2+0x6a>
    8e5e:	4c 41 80 08 	beq $r4,$r3,8e6e <__eqdf2+0x66>
    8e62:	cd 08       	bnez38 $r5,8e72 <__eqdf2+0x6a>
    8e64:	40 01 04 04 	or $r0,$r2,$r1
    8e68:	40 02 80 06 	slt $r0,$r5,$r0
    8e6c:	fc a0       	pop25 $r8,#0    ! {$r6~$r8, $fp, $gp, $lp}
    8e6e:	84 00       	movi55 $r0,#0x0
    8e70:	fc a0       	pop25 $r8,#0    ! {$r6~$r8, $fp, $gp, $lp}
    8e72:	84 01       	movi55 $r0,#0x1
    8e74:	fc a0       	pop25 $r8,#0    ! {$r6~$r8, $fp, $gp, $lp}

00008e76 <__gedf2>:
    8e76:	fc 20       	push25 $r8,#0    ! {$r6~$r8, $fp, $gp, $lp}
    8e78:	6a 20 80 41 	fmfdr $r2,$fd1
    8e7c:	6a 00 00 41 	fmfdr $r0,$fd0
    8e80:	82 22       	mov55 $r17,$r2
    8e82:	82 00       	mov55 $r16,$r0
    8e84:	80 e3       	mov55 $r7,$r3
    8e86:	6a 00 07 01 	fmfcsr $r0
    8e8a:	40 30 d0 09 	srli $r3,$r1,#0x14
    8e8e:	40 50 b0 08 	slli $r5,$r1,#0xc
    8e92:	40 63 b0 08 	slli $r6,$r7,#0xc
    8e96:	40 23 d0 09 	srli $r2,$r7,#0x14
    8e9a:	96 dd       	x11b33 $r3,$r3
    8e9c:	45 20 07 ff 	movi $r18,#0x7ff
    8ea0:	80 90       	mov55 $r4,$r16
    8ea2:	92 ac       	srli45 $r5,#0xc
    8ea4:	92 3f       	srli45 $r1,#0x1f
    8ea6:	80 11       	mov55 $r0,$r17
    8ea8:	92 cc       	srli45 $r6,#0xc
    8eaa:	96 95       	x11b33 $r2,$r2
    8eac:	92 ff       	srli45 $r7,#0x1f
    8eae:	4c 39 40 06 	bne $r3,$r18,8eba <__gedf2+0x44>
    8eb2:	40 f2 c0 04 	or $r15,$r5,$r16
    8eb6:	e8 0d       	beqzs8 8ed0 <__gedf2+0x5a>
    8eb8:	d5 13       	j8 8ede <__gedf2+0x68>
    8eba:	4c 29 40 06 	bne $r2,$r18,8ec6 <__gedf2+0x50>
    8ebe:	40 f3 00 04 	or $r15,$r6,$r0
    8ec2:	e8 13       	beqzs8 8ee8 <__gedf2+0x72>
    8ec4:	d5 0d       	j8 8ede <__gedf2+0x68>
    8ec6:	cb 07       	bnez38 $r3,8ed4 <__gedf2+0x5e>
    8ec8:	ff 2f       	or33 $r4,$r5
    8eca:	e6 81       	slti45 $r4,#0x1
    8ecc:	ca 0b       	bnez38 $r2,8ee2 <__gedf2+0x6c>
    8ece:	d5 05       	j8 8ed8 <__gedf2+0x62>
    8ed0:	4c 21 bf f7 	beq $r2,$r3,8ebe <__gedf2+0x48>
    8ed4:	ca 0b       	bnez38 $r2,8eea <__gedf2+0x74>
    8ed6:	81 e2       	mov55 $r15,$r2
    8ed8:	fe 37       	or33 $r0,$r6
    8eda:	c0 11       	beqz38 $r0,8efc <__gedf2+0x86>
    8edc:	d5 03       	j8 8ee2 <__gedf2+0x6c>
    8ede:	84 1e       	movi55 $r0,#-2
    8ee0:	fc a0       	pop25 $r8,#0    ! {$r6~$r8, $fp, $gp, $lp}
    8ee2:	e8 04       	beqzs8 8eea <__gedf2+0x74>
    8ee4:	c7 1a       	beqz38 $r7,8f18 <__gedf2+0xa2>
    8ee6:	d5 09       	j8 8ef8 <__gedf2+0x82>
    8ee8:	c3 f0       	beqz38 $r3,8ec8 <__gedf2+0x52>
    8eea:	4c 13 c0 16 	bne $r1,$r7,8f16 <__gedf2+0xa0>
    8eee:	e0 43       	slts45 $r2,$r3
    8ef0:	e9 13       	bnezs8 8f16 <__gedf2+0xa0>
    8ef2:	e0 62       	slts45 $r3,$r2
    8ef4:	e8 06       	beqzs8 8f00 <__gedf2+0x8a>
    8ef6:	c1 11       	beqz38 $r1,8f18 <__gedf2+0xa2>
    8ef8:	84 01       	movi55 $r0,#0x1
    8efa:	fc a0       	pop25 $r8,#0    ! {$r6~$r8, $fp, $gp, $lp}
    8efc:	e9 10       	bnezs8 8f1c <__gedf2+0xa6>
    8efe:	d5 0c       	j8 8f16 <__gedf2+0xa0>
    8f00:	e2 c5       	slt45 $r6,$r5
    8f02:	e9 0a       	bnezs8 8f16 <__gedf2+0xa0>
    8f04:	de 05       	bnes38 $r6,8f0e <__gedf2+0x98>
    8f06:	e3 b0       	slt45 $r17,$r16
    8f08:	e9 07       	bnezs8 8f16 <__gedf2+0xa0>
    8f0a:	e3 91       	slt45 $r16,$r17
    8f0c:	d5 02       	j8 8f10 <__gedf2+0x9a>
    8f0e:	e2 a6       	slt45 $r5,$r6
    8f10:	e9 f3       	bnezs8 8ef6 <__gedf2+0x80>
    8f12:	84 00       	movi55 $r0,#0x0
    8f14:	fc a0       	pop25 $r8,#0    ! {$r6~$r8, $fp, $gp, $lp}
    8f16:	c1 f1       	beqz38 $r1,8ef8 <__gedf2+0x82>
    8f18:	84 1f       	movi55 $r0,#-1
    8f1a:	fc a0       	pop25 $r8,#0    ! {$r6~$r8, $fp, $gp, $lp}
    8f1c:	fc a0       	pop25 $r8,#0    ! {$r6~$r8, $fp, $gp, $lp}

00008f1e <__ledf2>:
    8f1e:	fc 20       	push25 $r8,#0    ! {$r6~$r8, $fp, $gp, $lp}
    8f20:	6a 20 80 41 	fmfdr $r2,$fd1
    8f24:	6a 00 00 41 	fmfdr $r0,$fd0
    8f28:	82 22       	mov55 $r17,$r2
    8f2a:	82 00       	mov55 $r16,$r0
    8f2c:	80 e3       	mov55 $r7,$r3
    8f2e:	6a 00 07 01 	fmfcsr $r0
    8f32:	40 30 d0 09 	srli $r3,$r1,#0x14
    8f36:	40 50 b0 08 	slli $r5,$r1,#0xc
    8f3a:	40 63 b0 08 	slli $r6,$r7,#0xc
    8f3e:	40 23 d0 09 	srli $r2,$r7,#0x14
    8f42:	96 dd       	x11b33 $r3,$r3
    8f44:	45 20 07 ff 	movi $r18,#0x7ff
    8f48:	80 90       	mov55 $r4,$r16
    8f4a:	92 ac       	srli45 $r5,#0xc
    8f4c:	92 3f       	srli45 $r1,#0x1f
    8f4e:	80 11       	mov55 $r0,$r17
    8f50:	92 cc       	srli45 $r6,#0xc
    8f52:	96 95       	x11b33 $r2,$r2
    8f54:	92 ff       	srli45 $r7,#0x1f
    8f56:	4c 39 40 06 	bne $r3,$r18,8f62 <__ledf2+0x44>
    8f5a:	40 f2 c0 04 	or $r15,$r5,$r16
    8f5e:	e9 14       	bnezs8 8f86 <__ledf2+0x68>
    8f60:	d5 0c       	j8 8f78 <__ledf2+0x5a>
    8f62:	4c 29 40 06 	bne $r2,$r18,8f6e <__ledf2+0x50>
    8f66:	40 f3 00 04 	or $r15,$r6,$r0
    8f6a:	e9 0e       	bnezs8 8f86 <__ledf2+0x68>
    8f6c:	d5 12       	j8 8f90 <__ledf2+0x72>
    8f6e:	cb 07       	bnez38 $r3,8f7c <__ledf2+0x5e>
    8f70:	ff 2f       	or33 $r4,$r5
    8f72:	e6 81       	slti45 $r4,#0x1
    8f74:	ca 0b       	bnez38 $r2,8f8a <__ledf2+0x6c>
    8f76:	d5 05       	j8 8f80 <__ledf2+0x62>
    8f78:	4c 21 bf f7 	beq $r2,$r3,8f66 <__ledf2+0x48>
    8f7c:	ca 0b       	bnez38 $r2,8f92 <__ledf2+0x74>
    8f7e:	81 e2       	mov55 $r15,$r2
    8f80:	fe 37       	or33 $r0,$r6
    8f82:	c0 11       	beqz38 $r0,8fa4 <__ledf2+0x86>
    8f84:	d5 03       	j8 8f8a <__ledf2+0x6c>
    8f86:	84 02       	movi55 $r0,#0x2
    8f88:	fc a0       	pop25 $r8,#0    ! {$r6~$r8, $fp, $gp, $lp}
    8f8a:	e8 04       	beqzs8 8f92 <__ledf2+0x74>
    8f8c:	c7 1a       	beqz38 $r7,8fc0 <__ledf2+0xa2>
    8f8e:	d5 09       	j8 8fa0 <__ledf2+0x82>
    8f90:	c3 f0       	beqz38 $r3,8f70 <__ledf2+0x52>
    8f92:	4c 13 c0 16 	bne $r1,$r7,8fbe <__ledf2+0xa0>
    8f96:	e0 43       	slts45 $r2,$r3
    8f98:	e9 13       	bnezs8 8fbe <__ledf2+0xa0>
    8f9a:	e0 62       	slts45 $r3,$r2
    8f9c:	e8 06       	beqzs8 8fa8 <__ledf2+0x8a>
    8f9e:	c1 11       	beqz38 $r1,8fc0 <__ledf2+0xa2>
    8fa0:	84 01       	movi55 $r0,#0x1
    8fa2:	fc a0       	pop25 $r8,#0    ! {$r6~$r8, $fp, $gp, $lp}
    8fa4:	e9 10       	bnezs8 8fc4 <__ledf2+0xa6>
    8fa6:	d5 0c       	j8 8fbe <__ledf2+0xa0>
    8fa8:	e2 c5       	slt45 $r6,$r5
    8faa:	e9 0a       	bnezs8 8fbe <__ledf2+0xa0>
    8fac:	de 05       	bnes38 $r6,8fb6 <__ledf2+0x98>
    8fae:	e3 b0       	slt45 $r17,$r16
    8fb0:	e9 07       	bnezs8 8fbe <__ledf2+0xa0>
    8fb2:	e3 91       	slt45 $r16,$r17
    8fb4:	d5 02       	j8 8fb8 <__ledf2+0x9a>
    8fb6:	e2 a6       	slt45 $r5,$r6
    8fb8:	e9 f3       	bnezs8 8f9e <__ledf2+0x80>
    8fba:	84 00       	movi55 $r0,#0x0
    8fbc:	fc a0       	pop25 $r8,#0    ! {$r6~$r8, $fp, $gp, $lp}
    8fbe:	c1 f1       	beqz38 $r1,8fa0 <__ledf2+0x82>
    8fc0:	84 1f       	movi55 $r0,#-1
    8fc2:	fc a0       	pop25 $r8,#0    ! {$r6~$r8, $fp, $gp, $lp}
    8fc4:	fc a0       	pop25 $r8,#0    ! {$r6~$r8, $fp, $gp, $lp}
	...

00008fc8 <__muldf3>:
    8fc8:	fc 60       	push25 $r14,#0    ! {$r6~$r14, $fp, $gp, $lp}
    8fca:	6a 00 00 41 	fmfdr $r0,$fd0
    8fce:	80 40       	mov55 $r2,$r0
    8fd0:	80 a1       	mov55 $r5,$r1
    8fd2:	6a 00 80 41 	fmfdr $r0,$fd1
    8fd6:	80 c0       	mov55 $r6,$r0
    8fd8:	82 01       	mov55 $r16,$r1
    8fda:	6b 20 07 01 	fmfcsr $r18
    8fde:	40 72 d0 09 	srli $r7,$r5,#0x14
    8fe2:	40 12 b0 08 	slli $r1,$r5,#0xc
    8fe6:	40 a2 fc 09 	srli $r10,$r5,#0x1f
    8fea:	97 fd       	x11b33 $r7,$r7
    8fec:	80 02       	mov55 $r0,$r2
    8fee:	92 2c       	srli45 $r1,#0xc
    8ff0:	82 6a       	mov55 $r19,$r10
    8ff2:	c7 0f       	beqz38 $r7,9010 <__muldf3+0x48>
    8ff4:	44 30 07 ff 	movi $r3,#0x7ff
    8ff8:	4c 71 80 2d 	beq $r7,$r3,9052 <__muldf3+0x8a>
    8ffc:	42 10 d0 08 	bset $r1,$r1,#0x14
    9000:	40 51 74 09 	srli $r5,$r2,#0x1d
    9004:	40 12 84 64 	or_slli $r1,$r5,$r1,#0x3
    9008:	94 13       	slli333 $r0,$r2,#0x3
    900a:	50 73 fc 01 	addi $r7,$r7,#-1023
    900e:	d5 20       	j8 904e <__muldf3+0x86>
    9010:	fe 0f       	or33 $r0,$r1
    9012:	c0 28       	beqz38 $r0,9062 <__muldf3+0x9a>
    9014:	c1 04       	beqz38 $r1,901c <__muldf3+0x54>
    9016:	42 50 80 07 	clz $r5,$r1
    901a:	d5 08       	j8 902a <__muldf3+0x62>
    901c:	42 01 00 07 	clz $r0,$r2
    9020:	50 50 00 20 	addi $r5,$r0,#0x20
    9024:	5e f2 80 28 	sltsi $r15,$r5,#0x28
    9028:	e8 0d       	beqzs8 9042 <__muldf3+0x7a>
    902a:	50 f2 ff f8 	addi $r15,$r5,#-8
    902e:	52 72 80 28 	subri $r7,$r5,#0x28
    9032:	40 10 bc 0c 	sll $r1,$r1,$r15
    9036:	40 71 1c 0d 	srl $r7,$r2,$r7
    903a:	fe 7f       	or33 $r1,$r7
    903c:	40 01 3c 0c 	sll $r0,$r2,$r15
    9040:	d5 05       	j8 904a <__muldf3+0x82>
    9042:	8e 08       	subi45 $r0,#0x8
    9044:	40 11 00 0c 	sll $r1,$r2,$r0
    9048:	80 07       	mov55 $r0,$r7
    904a:	52 72 fc 0d 	subri $r7,$r5,#-1011
    904e:	84 60       	movi55 $r3,#0x0
    9050:	d5 0c       	j8 9068 <__muldf3+0xa0>
    9052:	40 20 88 04 	or $r2,$r1,$r2
    9056:	84 63       	movi55 $r3,#0x3
    9058:	ca 08       	bnez38 $r2,9068 <__muldf3+0xa0>
    905a:	80 22       	mov55 $r1,$r2
    905c:	80 02       	mov55 $r0,$r2
    905e:	84 62       	movi55 $r3,#0x2
    9060:	d5 04       	j8 9068 <__muldf3+0xa0>
    9062:	80 27       	mov55 $r1,$r7
    9064:	80 07       	mov55 $r0,$r7
    9066:	84 61       	movi55 $r3,#0x1
    9068:	40 58 50 09 	srli $r5,$r16,#0x14
    906c:	40 28 30 08 	slli $r2,$r16,#0xc
    9070:	97 6d       	x11b33 $r5,$r5
    9072:	80 86       	mov55 $r4,$r6
    9074:	92 4c       	srli45 $r2,#0xc
    9076:	93 9f       	srli45 $r16,#0x1f
    9078:	c5 0f       	beqz38 $r5,9096 <__muldf3+0xce>
    907a:	45 10 07 ff 	movi $r17,#0x7ff
    907e:	4c 58 80 2e 	beq $r5,$r17,90da <__muldf3+0x112>
    9082:	42 21 50 08 	bset $r2,$r2,#0x14
    9086:	40 f3 74 09 	srli $r15,$r6,#0x1d
    908a:	40 27 88 64 	or_slli $r2,$r15,$r2,#0x3
    908e:	95 33       	slli333 $r4,$r6,#0x3
    9090:	50 52 fc 01 	addi $r5,$r5,#-1023
    9094:	d5 21       	j8 90d6 <__muldf3+0x10e>
    9096:	ff 17       	or33 $r4,$r2
    9098:	c4 26       	beqz38 $r4,90e4 <__muldf3+0x11c>
    909a:	c2 04       	beqz38 $r2,90a2 <__muldf3+0xda>
    909c:	43 11 00 07 	clz $r17,$r2
    90a0:	d5 08       	j8 90b0 <__muldf3+0xe8>
    90a2:	42 43 00 07 	clz $r4,$r6
    90a6:	51 12 00 20 	addi $r17,$r4,#0x20
    90aa:	5e f8 80 28 	sltsi $r15,$r17,#0x28
    90ae:	e8 0e       	beqzs8 90ca <__muldf3+0x102>
    90b0:	50 48 ff f8 	addi $r4,$r17,#-8
    90b4:	52 f8 80 28 	subri $r15,$r17,#0x28
    90b8:	40 21 10 0c 	sll $r2,$r2,$r4
    90bc:	40 f3 3c 0d 	srl $r15,$r6,$r15
    90c0:	40 27 88 04 	or $r2,$r15,$r2
    90c4:	40 43 10 0c 	sll $r4,$r6,$r4
    90c8:	d5 05       	j8 90d2 <__muldf3+0x10a>
    90ca:	8e 88       	subi45 $r4,#0x8
    90cc:	40 23 10 0c 	sll $r2,$r6,$r4
    90d0:	80 85       	mov55 $r4,$r5
    90d2:	52 58 fc 0d 	subri $r5,$r17,#-1011
    90d6:	84 c0       	movi55 $r6,#0x0
    90d8:	d5 0d       	j8 90f2 <__muldf3+0x12a>
    90da:	40 61 18 04 	or $r6,$r2,$r6
    90de:	c6 07       	beqz38 $r6,90ec <__muldf3+0x124>
    90e0:	84 c3       	movi55 $r6,#0x3
    90e2:	d5 08       	j8 90f2 <__muldf3+0x12a>
    90e4:	80 45       	mov55 $r2,$r5
    90e6:	80 85       	mov55 $r4,$r5
    90e8:	84 c1       	movi55 $r6,#0x1
    90ea:	d5 04       	j8 90f2 <__muldf3+0x12a>
    90ec:	80 46       	mov55 $r2,$r6
    90ee:	80 86       	mov55 $r4,$r6
    90f0:	84 c2       	movi55 $r6,#0x2
    90f2:	41 13 0c 44 	or_slli $r17,$r6,$r3,#0x2
    90f6:	8f a1       	subi45 $r17,#0x1
    90f8:	40 83 94 00 	add $r8,$r7,$r5
    90fc:	e7 af       	slti45 $r17,#0xf
    90fe:	40 a8 28 03 	xor $r10,$r16,$r10
    9102:	50 54 00 01 	addi $r5,$r8,#0x1
    9106:	e8 20       	beqzs8 9146 <__muldf3+0x17e>
    9108:	44 f0 91 18 	movi $r15,#0x9118
    910c:	39 17 c5 01 	lh $r17,[$r15+($r17<<#0x1)]
    9110:	40 f8 bc 00 	add $r15,$r17,$r15
    9114:	4a 00 3c 00 	jr $r15
    9118:	24 00 24 00 	*unknown*
    911c:	70 01 1e 00 	*unknown*
    9120:	1e 00 e2 02 	*unknown*
    9124:	70 01 1e 00 	*unknown*
    9128:	e2 02       	slt45 $r0,$r2
    912a:	1e 00 70 01 	*unknown*
    912e:	78 01 78 01 	*unknown*
    9132:	78 01 54 01 	*unknown*
    9136:	82 6a       	mov55 $r19,$r10
    9138:	48 00 00 ac 	j 9290 <__muldf3+0x2c8>
    913c:	80 22       	mov55 $r1,$r2
    913e:	80 04       	mov55 $r0,$r4
    9140:	82 6a       	mov55 $r19,$r10
    9142:	48 00 00 a6 	j 928e <__muldf3+0x2c6>
    9146:	40 30 40 09 	srli $r3,$r0,#0x10
    914a:	40 92 40 09 	srli $r9,$r4,#0x10
    914e:	97 21       	zeh33 $r4,$r4
    9150:	42 f2 0c 24 	mul $r15,$r4,$r3
    9154:	41 00 00 13 	zeh $r16,$r0
    9158:	80 cf       	mov55 $r6,$r15
    915a:	42 02 40 24 	mul $r0,$r4,$r16
    915e:	42 64 c0 73 	maddr32 $r6,$r9,$r16
    9162:	40 63 02 1c 	add_srli $r6,$r6,$r0,#0x10
    9166:	e2 cf       	slt45 $r6,$r15
    9168:	42 74 8c 24 	mul $r7,$r9,$r3
    916c:	e8 04       	beqzs8 9174 <__muldf3+0x1ac>
    916e:	45 11 00 00 	movi $r17,#0x10000
    9172:	88 f1       	add45 $r7,$r17
    9174:	41 31 40 09 	srli $r19,$r2,#0x10
    9178:	96 91       	zeh33 $r2,$r2
    917a:	42 f1 0c 24 	mul $r15,$r2,$r3
    917e:	96 01       	zeh33 $r0,$r0
    9180:	40 b0 1a 00 	add_slli $r11,$r0,$r6,#0x10
    9184:	41 13 40 09 	srli $r17,$r6,#0x10
    9188:	42 01 40 24 	mul $r0,$r2,$r16
    918c:	80 cf       	mov55 $r6,$r15
    918e:	42 69 c0 73 	maddr32 $r6,$r19,$r16
    9192:	40 63 02 1c 	add_srli $r6,$r6,$r0,#0x10
    9196:	e2 cf       	slt45 $r6,$r15
    9198:	42 39 8c 24 	mul $r3,$r19,$r3
    919c:	e8 04       	beqzs8 91a4 <__muldf3+0x1dc>
    919e:	45 01 00 00 	movi $r16,#0x10000
    91a2:	88 70       	add45 $r3,$r16
    91a4:	96 01       	zeh33 $r0,$r0
    91a6:	41 00 1a 00 	add_slli $r16,$r0,$r6,#0x10
    91aa:	40 00 c0 09 	srli $r0,$r1,#0x10
    91ae:	96 49       	zeh33 $r1,$r1
    91b0:	42 c2 04 24 	mul $r12,$r4,$r1
    91b4:	ff 04       	mul33 $r4,$r0
    91b6:	40 31 9a 1c 	add_srli $r3,$r3,$r6,#0x10
    91ba:	80 c4       	mov55 $r6,$r4
    91bc:	42 64 84 73 	maddr32 $r6,$r9,$r1
    91c0:	40 63 32 1c 	add_srli $r6,$r6,$r12,#0x10
    91c4:	e2 c4       	slt45 $r6,$r4
    91c6:	40 d8 44 00 	add $r13,$r16,$r17
    91ca:	43 14 80 24 	mul $r17,$r9,$r0
    91ce:	e8 04       	beqzs8 91d6 <__muldf3+0x20e>
    91d0:	44 41 00 00 	movi $r4,#0x10000
    91d4:	89 a4       	add45 $r17,$r4
    91d6:	40 46 00 13 	zeh $r4,$r12
    91da:	40 98 9a 1c 	add_srli $r9,$r17,$r6,#0x10
    91de:	40 62 1a 00 	add_slli $r6,$r4,$r6,#0x10
    91e2:	42 41 04 24 	mul $r4,$r2,$r1
    91e6:	fe 84       	mul33 $r2,$r0
    91e8:	43 19 80 24 	mul $r17,$r19,$r0
    91ec:	80 02       	mov55 $r0,$r2
    91ee:	42 09 84 73 	maddr32 $r0,$r19,$r1
    91f2:	41 30 12 1c 	add_srli $r19,$r0,$r4,#0x10
    91f6:	e3 e2       	slt45 $r19,$r2
    91f8:	e8 04       	beqzs8 9200 <__muldf3+0x238>
    91fa:	44 01 00 00 	movi $r0,#0x10000
    91fe:	89 a0       	add45 $r17,$r0
    9200:	96 a1       	zeh33 $r2,$r4
    9202:	88 ed       	add45 $r7,$r13
    9204:	40 21 4e 00 	add_slli $r2,$r2,$r19,#0x10
    9208:	e2 f0       	slt45 $r7,$r16
    920a:	99 13       	add333 $r4,$r2,$r3
    920c:	40 02 3c 00 	add $r0,$r4,$r15
    9210:	88 e6       	add45 $r7,$r6
    9212:	40 24 80 00 	add $r2,$r9,$r0
    9216:	40 63 98 06 	slt $r6,$r7,$r6
    921a:	41 01 18 00 	add $r16,$r2,$r6
    921e:	e2 0f       	slt45 $r0,$r15
    9220:	40 42 0c 06 	slt $r4,$r4,$r3
    9224:	40 47 90 04 	or $r4,$r15,$r4
    9228:	40 68 18 06 	slt $r6,$r16,$r6
    922c:	e2 49       	slt45 $r2,$r9
    922e:	40 63 3c 04 	or $r6,$r6,$r15
    9232:	40 42 4e 1c 	add_srli $r4,$r4,$r19,#0x10
    9236:	98 66       	add333 $r1,$r4,$r6
    9238:	89 a1       	add45 $r17,$r1
    923a:	40 f5 9d 24 	or_slli $r15,$r11,$r7,#0x9
    923e:	84 40       	movi55 $r2,#0x0
    9240:	40 18 5c 09 	srli $r1,$r16,#0x17
    9244:	e2 4f       	slt45 $r2,$r15
    9246:	40 10 c5 24 	or_slli $r1,$r1,$r17,#0x9
    924a:	40 77 9e f5 	or_srli $r7,$r15,$r7,#0x17
    924e:	42 20 e0 0b 	btst $r2,$r1,#0x18
    9252:	40 03 c1 24 	or_slli $r0,$r7,$r16,#0x9
    9256:	4e 22 00 ef 	beqz $r2,9434 <__muldf3+0x46c>
    925a:	96 84       	xlsb33 $r2,$r0
    925c:	40 f1 00 35 	or_srli $r15,$r2,$r0,#0x1
    9260:	40 07 87 e4 	or_slli $r0,$r15,$r1,#0x1f
    9264:	81 05       	mov55 $r8,$r5
    9266:	92 21       	srli45 $r1,#0x1
    9268:	48 00 00 e6 	j 9434 <__muldf3+0x46c>
    926c:	46 30 00 80 	sethi $r3,#0x80
    9270:	40 50 8c 02 	and $r5,$r1,$r3
    9274:	4e 52 00 c9 	beqz $r5,9406 <__muldf3+0x43e>
    9278:	fe d6       	and33 $r3,$r2
    927a:	4e 33 00 c6 	bnez $r3,9406 <__muldf3+0x43e>
    927e:	80 22       	mov55 $r1,$r2
    9280:	80 04       	mov55 $r0,$r4
    9282:	82 70       	mov55 $r19,$r16
    9284:	48 00 00 c1 	j 9406 <__muldf3+0x43e>
    9288:	80 22       	mov55 $r1,$r2
    928a:	80 04       	mov55 $r0,$r4
    928c:	82 70       	mov55 $r19,$r16
    928e:	80 66       	mov55 $r3,$r6
    9290:	5a 38 02 04 	bnec $r3,#0x2,9298 <__muldf3+0x2d0>
    9294:	48 00 00 be 	j 9410 <__muldf3+0x448>
    9298:	5a 38 03 04 	bnec $r3,#0x3,92a0 <__muldf3+0x2d8>
    929c:	48 00 00 b5 	j 9406 <__muldf3+0x43e>
    92a0:	5a 38 01 04 	bnec $r3,#0x1,92a8 <__muldf3+0x2e0>
    92a4:	48 00 00 b4 	j 940c <__muldf3+0x444>
    92a8:	50 22 83 ff 	addi $r2,$r5,#0x3ff
    92ac:	4e 27 00 3f 	blez $r2,932a <__muldf3+0x362>
    92b0:	54 30 00 07 	andi $r3,$r0,#0x7
    92b4:	c3 19       	beqz38 $r3,92e6 <__muldf3+0x31e>
    92b6:	54 39 00 03 	andi $r3,$r18,#0x3
    92ba:	5a 30 01 0c 	beqc $r3,#0x1,92d2 <__muldf3+0x30a>
    92be:	c3 04       	beqz38 $r3,92c6 <__muldf3+0x2fe>
    92c0:	5a 30 02 0c 	beqc $r3,#0x2,92d8 <__muldf3+0x310>
    92c4:	d5 11       	j8 92e6 <__muldf3+0x31e>
    92c6:	54 30 00 0f 	andi $r3,$r0,#0xf
    92ca:	5a 30 04 0e 	beqc $r3,#0x4,92e6 <__muldf3+0x31e>
    92ce:	9c c4       	addi333 $r3,$r0,#0x4
    92d0:	d5 08       	j8 92e0 <__muldf3+0x318>
    92d2:	4f 33 00 0a 	bnez $r19,92e6 <__muldf3+0x31e>
    92d6:	d5 03       	j8 92dc <__muldf3+0x314>
    92d8:	4f 32 00 07 	beqz $r19,92e6 <__muldf3+0x31e>
    92dc:	50 30 00 08 	addi $r3,$r0,#0x8
    92e0:	e2 60       	slt45 $r3,$r0
    92e2:	88 2f       	add45 $r1,$r15
    92e4:	80 03       	mov55 $r0,$r3
    92e6:	42 30 e0 0b 	btst $r3,$r1,#0x18
    92ea:	c3 05       	beqz38 $r3,92f4 <__muldf3+0x32c>
    92ec:	42 10 e0 09 	bclr $r1,$r1,#0x18
    92f0:	50 22 84 00 	addi $r2,$r5,#0x400
    92f4:	5e f1 07 ff 	sltsi $r15,$r2,#0x7ff
    92f8:	e8 06       	beqzs8 9304 <__muldf3+0x33c>
    92fa:	40 30 f4 08 	slli $r3,$r1,#0x1d
    92fe:	40 01 80 75 	or_srli $r0,$r3,$r0,#0x3
    9302:	d5 62       	j8 93c6 <__muldf3+0x3fe>
    9304:	54 09 00 03 	andi $r0,$r18,#0x3
    9308:	5a 00 01 08 	beqc $r0,#0x1,9318 <__muldf3+0x350>
    930c:	4e 02 00 82 	beqz $r0,9410 <__muldf3+0x448>
    9310:	5a 00 02 09 	beqc $r0,#0x2,9322 <__muldf3+0x35a>
    9314:	48 00 00 84 	j 941c <__muldf3+0x454>
    9318:	4f 33 00 81 	bnez $r19,941a <__muldf3+0x452>
    931c:	80 33       	mov55 $r1,$r19
    931e:	80 13       	mov55 $r0,$r19
    9320:	d5 7a       	j8 9414 <__muldf3+0x44c>
    9322:	4f 32 00 7d 	beqz $r19,941c <__muldf3+0x454>
    9326:	86 61       	movi55 $r19,#0x1
    9328:	d5 74       	j8 9410 <__muldf3+0x448>
    932a:	52 22 fc 02 	subri $r2,$r5,#-1022
    932e:	5e f1 00 39 	sltsi $r15,$r2,#0x39
    9332:	e8 4c       	beqzs8 93ca <__muldf3+0x402>
    9334:	5e f1 00 20 	sltsi $r15,$r2,#0x20
    9338:	e8 12       	beqzs8 935c <__muldf3+0x394>
    933a:	50 52 84 1e 	addi $r5,$r5,#0x41e
    933e:	40 30 94 0c 	sll $r3,$r1,$r5
    9342:	40 f0 08 0d 	srl $r15,$r0,$r2
    9346:	40 50 14 0c 	sll $r5,$r0,$r5
    934a:	84 80       	movi55 $r4,#0x0
    934c:	40 37 8c 04 	or $r3,$r15,$r3
    9350:	e2 85       	slt45 $r4,$r5
    9352:	40 31 bc 04 	or $r3,$r3,$r15
    9356:	40 10 88 0d 	srl $r1,$r1,$r2
    935a:	d5 13       	j8 9380 <__muldf3+0x3b8>
    935c:	52 32 fb e2 	subri $r3,$r5,#-1054
    9360:	40 40 8c 0d 	srl $r4,$r1,$r3
    9364:	5a 20 20 07 	beqc $r2,#0x20,9372 <__muldf3+0x3aa>
    9368:	50 52 84 3e 	addi $r5,$r5,#0x43e
    936c:	40 10 94 0c 	sll $r1,$r1,$r5
    9370:	d5 02       	j8 9374 <__muldf3+0x3ac>
    9372:	84 20       	movi55 $r1,#0x0
    9374:	40 f0 80 04 	or $r15,$r1,$r0
    9378:	84 20       	movi55 $r1,#0x0
    937a:	e2 2f       	slt45 $r1,$r15
    937c:	40 37 90 04 	or $r3,$r15,$r4
    9380:	54 01 80 07 	andi $r0,$r3,#0x7
    9384:	c0 19       	beqz38 $r0,93b6 <__muldf3+0x3ee>
    9386:	54 09 00 03 	andi $r0,$r18,#0x3
    938a:	5a 00 01 0c 	beqc $r0,#0x1,93a2 <__muldf3+0x3da>
    938e:	c0 04       	beqz38 $r0,9396 <__muldf3+0x3ce>
    9390:	5a 00 02 0c 	beqc $r0,#0x2,93a8 <__muldf3+0x3e0>
    9394:	d5 11       	j8 93b6 <__muldf3+0x3ee>
    9396:	54 01 80 0f 	andi $r0,$r3,#0xf
    939a:	5a 00 04 0e 	beqc $r0,#0x4,93b6 <__muldf3+0x3ee>
    939e:	9c 1c       	addi333 $r0,$r3,#0x4
    93a0:	d5 08       	j8 93b0 <__muldf3+0x3e8>
    93a2:	4f 33 00 0a 	bnez $r19,93b6 <__muldf3+0x3ee>
    93a6:	d5 03       	j8 93ac <__muldf3+0x3e4>
    93a8:	4f 32 00 07 	beqz $r19,93b6 <__muldf3+0x3ee>
    93ac:	50 01 80 08 	addi $r0,$r3,#0x8
    93b0:	e2 03       	slt45 $r0,$r3
    93b2:	88 2f       	add45 $r1,$r15
    93b4:	80 60       	mov55 $r3,$r0
    93b6:	46 20 08 00 	sethi $r2,#0x800
    93ba:	fe 8e       	and33 $r2,$r1
    93bc:	ca 35       	bnez38 $r2,9426 <__muldf3+0x45e>
    93be:	40 f0 f4 08 	slli $r15,$r1,#0x1d
    93c2:	40 07 8c 75 	or_srli $r0,$r15,$r3,#0x3
    93c6:	92 23       	srli45 $r1,#0x3
    93c8:	d5 3a       	j8 943c <__muldf3+0x474>
    93ca:	fe 0f       	or33 $r0,$r1
    93cc:	c0 31       	beqz38 $r0,942e <__muldf3+0x466>
    93ce:	54 09 00 03 	andi $r0,$r18,#0x3
    93d2:	5a 00 01 08 	beqc $r0,#0x1,93e2 <__muldf3+0x41a>
    93d6:	c0 04       	beqz38 $r0,93de <__muldf3+0x416>
    93d8:	5a 00 02 08 	beqc $r0,#0x2,93e8 <__muldf3+0x420>
    93dc:	d5 08       	j8 93ec <__muldf3+0x424>
    93de:	84 05       	movi55 $r0,#0x5
    93e0:	d5 09       	j8 93f2 <__muldf3+0x42a>
    93e2:	4f 32 00 07 	beqz $r19,93f0 <__muldf3+0x428>
    93e6:	d5 06       	j8 93f2 <__muldf3+0x42a>
    93e8:	4f 33 00 04 	bnez $r19,93f0 <__muldf3+0x428>
    93ec:	84 01       	movi55 $r0,#0x1
    93ee:	d5 02       	j8 93f2 <__muldf3+0x42a>
    93f0:	84 09       	movi55 $r0,#0x9
    93f2:	84 20       	movi55 $r1,#0x0
    93f4:	92 03       	srli45 $r0,#0x3
    93f6:	80 41       	mov55 $r2,$r1
    93f8:	d5 22       	j8 943c <__muldf3+0x474>
    93fa:	46 10 00 ff 	sethi $r1,#0xff
    93fe:	50 10 8f ff 	addi $r1,$r1,#0xfff
    9402:	84 1f       	movi55 $r0,#-1
    9404:	86 60       	movi55 $r19,#0x0
    9406:	42 10 cc 08 	bset $r1,$r1,#0x13
    940a:	d5 05       	j8 9414 <__muldf3+0x44c>
    940c:	84 00       	movi55 $r0,#0x0
    940e:	d5 10       	j8 942e <__muldf3+0x466>
    9410:	84 00       	movi55 $r0,#0x0
    9412:	80 20       	mov55 $r1,$r0
    9414:	44 20 07 ff 	movi $r2,#0x7ff
    9418:	d5 12       	j8 943c <__muldf3+0x474>
    941a:	82 60       	mov55 $r19,$r0
    941c:	84 1f       	movi55 $r0,#-1
    941e:	80 20       	mov55 $r1,$r0
    9420:	44 20 07 fe 	movi $r2,#0x7fe
    9424:	d5 0c       	j8 943c <__muldf3+0x474>
    9426:	84 20       	movi55 $r1,#0x0
    9428:	80 01       	mov55 $r0,$r1
    942a:	84 41       	movi55 $r2,#0x1
    942c:	d5 08       	j8 943c <__muldf3+0x474>
    942e:	80 20       	mov55 $r1,$r0
    9430:	80 40       	mov55 $r2,$r0
    9432:	d5 05       	j8 943c <__muldf3+0x474>
    9434:	80 a8       	mov55 $r5,$r8
    9436:	82 6a       	mov55 $r19,$r10
    9438:	48 ff ff 38 	j 92a8 <__muldf3+0x2e0>
    943c:	84 80       	movi55 $r4,#0x0
    943e:	80 a4       	mov55 $r5,$r4
    9440:	80 80       	mov55 $r4,$r0
    9442:	40 02 d0 09 	srli $r0,$r5,#0x14
    9446:	40 00 50 08 	slli $r0,$r0,#0x14
    944a:	40 10 b0 08 	slli $r1,$r1,#0xc
    944e:	40 10 05 95 	or_srli $r1,$r0,$r1,#0xc
    9452:	46 08 00 ff 	sethi $r0,#0x800ff
    9456:	50 00 0f ff 	addi $r0,$r0,#0xfff
    945a:	96 95       	x11b33 $r2,$r2
    945c:	fe 46       	and33 $r1,$r0
    945e:	40 10 8a 84 	or_slli $r1,$r1,$r2,#0x14
    9462:	42 10 fc 09 	bclr $r1,$r1,#0x1f
    9466:	40 50 cf e4 	or_slli $r5,$r1,$r19,#0x1f
    946a:	6a 40 00 49 	fmtdr $r4,$fd0
    946e:	fc e0       	pop25 $r14,#0    ! {$r6~$r14, $fp, $gp, $lp}

00009470 <__subdf3>:
    9470:	fc 60       	push25 $r14,#0    ! {$r6~$r14, $fp, $gp, $lp}
    9472:	6a 00 00 41 	fmfdr $r0,$fd0
    9476:	80 60       	mov55 $r3,$r0
    9478:	80 81       	mov55 $r4,$r1
    947a:	6a 00 80 41 	fmfdr $r0,$fd1
    947e:	80 c0       	mov55 $r6,$r0
    9480:	81 21       	mov55 $r9,$r1
    9482:	6a a0 07 01 	fmfcsr $r10
    9486:	40 52 50 09 	srli $r5,$r4,#0x14
    948a:	40 f2 30 08 	slli $r15,$r4,#0xc
    948e:	40 01 f4 09 	srli $r0,$r3,#0x1d
    9492:	54 b2 87 ff 	andi $r11,$r5,#0x7ff
    9496:	40 50 d0 09 	srli $r5,$r1,#0x14
    949a:	40 00 3d 35 	or_srli $r0,$r0,$r15,#0x9
    949e:	40 70 fc 09 	srli $r7,$r1,#0x1f
    94a2:	40 f0 b0 08 	slli $r15,$r1,#0xc
    94a6:	97 6d       	x11b33 $r5,$r5
    94a8:	40 13 74 09 	srli $r1,$r6,#0x1d
    94ac:	44 20 07 ff 	movi $r2,#0x7ff
    94b0:	92 9f       	srli45 $r4,#0x1f
    94b2:	94 db       	slli333 $r3,$r3,#0x3
    94b4:	40 10 bd 35 	or_srli $r1,$r1,$r15,#0x9
    94b8:	40 83 0c 08 	slli $r8,$r6,#0x3
    94bc:	da 04       	bnes38 $r2,94c4 <__subdf3+0x54>
    94be:	40 20 a0 04 	or $r2,$r1,$r8
    94c2:	ca 03       	bnez38 $r2,94c8 <__subdf3+0x58>
    94c4:	56 73 80 01 	xori $r7,$r7,#0x1
    94c8:	44 60 07 ff 	movi $r6,#0x7ff
    94cc:	40 25 94 01 	sub $r2,$r11,$r5
    94d0:	4c 43 c1 25 	bne $r4,$r7,971a <__subdf3+0x2aa>
    94d4:	82 42       	mov55 $r18,$r2
    94d6:	4e 27 00 51 	blez $r2,9578 <__subdf3+0x108>
    94da:	cd 13       	bnez38 $r5,9500 <__subdf3+0x90>
    94dc:	40 50 a0 04 	or $r5,$r1,$r8
    94e0:	4e 52 02 b7 	beqz $r5,9a4e <__subdf3+0x5de>
    94e4:	51 21 7f ff 	addi $r18,$r2,#-1
    94e8:	4f 23 00 08 	bnez $r18,94f8 <__subdf3+0x88>
    94ec:	40 74 0c 00 	add $r7,$r8,$r3
    94f0:	88 01       	add45 $r0,$r1
    94f2:	e2 e3       	slt45 $r7,$r3
    94f4:	88 0f       	add45 $r0,$r15
    94f6:	d5 3e       	j8 9572 <__subdf3+0x102>
    94f8:	4c b3 40 08 	bne $r11,$r6,9508 <__subdf3+0x98>
    94fc:	48 00 02 a9 	j 9a4e <__subdf3+0x5de>
    9500:	4c b3 02 a7 	beq $r11,$r6,9a4e <__subdf3+0x5de>
    9504:	42 10 dc 08 	bset $r1,$r1,#0x17
    9508:	5e f9 00 39 	sltsi $r15,$r18,#0x39
    950c:	e8 28       	beqzs8 955c <__subdf3+0xec>
    950e:	5e f9 00 20 	sltsi $r15,$r18,#0x20
    9512:	e8 13       	beqzs8 9538 <__subdf3+0xc8>
    9514:	53 19 00 20 	subri $r17,$r18,#0x20
    9518:	40 70 c4 0c 	sll $r7,$r1,$r17
    951c:	40 24 48 0d 	srl $r2,$r8,$r18
    9520:	40 f3 88 04 	or $r15,$r7,$r2
    9524:	85 20       	movi55 $r9,#0x0
    9526:	40 74 44 0c 	sll $r7,$r8,$r17
    952a:	40 74 9c 06 	slt $r7,$r9,$r7
    952e:	40 77 9c 04 	or $r7,$r15,$r7
    9532:	40 f0 c8 0d 	srl $r15,$r1,$r18
    9536:	d5 18       	j8 9566 <__subdf3+0xf6>
    9538:	40 90 c8 0d 	srl $r9,$r1,$r18
    953c:	5b 20 20 07 	beqc $r18,#0x20,954a <__subdf3+0xda>
    9540:	53 29 00 40 	subri $r18,$r18,#0x40
    9544:	41 20 c8 0c 	sll $r18,$r1,$r18
    9548:	d5 02       	j8 954c <__subdf3+0xdc>
    954a:	86 40       	movi55 $r18,#0x0
    954c:	40 79 20 04 	or $r7,$r18,$r8
    9550:	84 20       	movi55 $r1,#0x0
    9552:	e2 27       	slt45 $r1,$r7
    9554:	40 77 a4 04 	or $r7,$r15,$r9
    9558:	81 e1       	mov55 $r15,$r1
    955a:	d5 06       	j8 9566 <__subdf3+0xf6>
    955c:	40 70 a0 04 	or $r7,$r1,$r8
    9560:	85 e0       	movi55 $r15,#0x0
    9562:	40 77 9c 06 	slt $r7,$r15,$r7
    9566:	88 e3       	add45 $r7,$r3
    9568:	41 27 80 00 	add $r18,$r15,$r0
    956c:	e2 e3       	slt45 $r7,$r3
    956e:	40 09 3c 00 	add $r0,$r18,$r15
    9572:	80 67       	mov55 $r3,$r7
    9574:	48 00 00 ac 	j 96cc <__subdf3+0x25c>
    9578:	c2 4b       	beqz38 $r2,960e <__subdf3+0x19e>
    957a:	4e b3 00 11 	bnez $r11,959c <__subdf3+0x12c>
    957e:	40 70 0c 04 	or $r7,$r0,$r3
    9582:	4e 72 02 33 	beqz $r7,99e8 <__subdf3+0x578>
    9586:	fe 93       	not33 $r2,$r2
    9588:	ca 07       	bnez38 $r2,9596 <__subdf3+0x126>
    958a:	88 68       	add45 $r3,$r8
    958c:	88 01       	add45 $r0,$r1
    958e:	40 71 a0 06 	slt $r7,$r3,$r8
    9592:	88 07       	add45 $r0,$r7
    9594:	d5 3b       	j8 960a <__subdf3+0x19a>
    9596:	de 08       	bnes38 $r6,95a6 <__subdf3+0x136>
    9598:	48 00 02 28 	j 99e8 <__subdf3+0x578>
    959c:	4c 53 02 26 	beq $r5,$r6,99e8 <__subdf3+0x578>
    95a0:	fe 92       	neg33 $r2,$r2
    95a2:	42 00 5c 08 	bset $r0,$r0,#0x17
    95a6:	5e f1 00 39 	sltsi $r15,$r2,#0x39
    95aa:	e8 26       	beqzs8 95f6 <__subdf3+0x186>
    95ac:	5e f1 00 20 	sltsi $r15,$r2,#0x20
    95b0:	e8 13       	beqzs8 95d6 <__subdf3+0x166>
    95b2:	52 71 00 20 	subri $r7,$r2,#0x20
    95b6:	40 61 88 0d 	srl $r6,$r3,$r2
    95ba:	85 20       	movi55 $r9,#0x0
    95bc:	40 f0 1c 0c 	sll $r15,$r0,$r7
    95c0:	40 31 9c 0c 	sll $r3,$r3,$r7
    95c4:	40 34 8c 06 	slt $r3,$r9,$r3
    95c8:	40 f7 98 04 	or $r15,$r15,$r6
    95cc:	40 37 8c 04 	or $r3,$r15,$r3
    95d0:	40 90 08 0d 	srl $r9,$r0,$r2
    95d4:	d5 16       	j8 9600 <__subdf3+0x190>
    95d6:	40 60 08 0d 	srl $r6,$r0,$r2
    95da:	5a 20 20 07 	beqc $r2,#0x20,95e8 <__subdf3+0x178>
    95de:	52 21 00 40 	subri $r2,$r2,#0x40
    95e2:	40 20 08 0c 	sll $r2,$r0,$r2
    95e6:	d5 02       	j8 95ea <__subdf3+0x17a>
    95e8:	84 40       	movi55 $r2,#0x0
    95ea:	fe d7       	or33 $r3,$r2
    95ec:	84 40       	movi55 $r2,#0x0
    95ee:	e2 43       	slt45 $r2,$r3
    95f0:	40 37 98 04 	or $r3,$r15,$r6
    95f4:	d5 05       	j8 95fe <__subdf3+0x18e>
    95f6:	fe c7       	or33 $r3,$r0
    95f8:	84 40       	movi55 $r2,#0x0
    95fa:	40 31 0c 06 	slt $r3,$r2,$r3
    95fe:	81 22       	mov55 $r9,$r2
    9600:	88 68       	add45 $r3,$r8
    9602:	89 21       	add45 $r9,$r1
    9604:	e2 68       	slt45 $r3,$r8
    9606:	40 04 bc 00 	add $r0,$r9,$r15
    960a:	81 65       	mov55 $r11,$r5
    960c:	d5 60       	j8 96cc <__subdf3+0x25c>
    960e:	50 55 80 01 	addi $r5,$r11,#0x1
    9612:	97 ed       	x11b33 $r7,$r5
    9614:	e4 e2       	sltsi45 $r7,#0x2
    9616:	e8 38       	beqzs8 9686 <__subdf3+0x216>
    9618:	40 20 0c 04 	or $r2,$r0,$r3
    961c:	4e b3 00 17 	bnez $r11,964a <__subdf3+0x1da>
    9620:	4e 22 01 e7 	beqz $r2,99ee <__subdf3+0x57e>
    9624:	40 20 a0 04 	or $r2,$r1,$r8
    9628:	4e 22 02 13 	beqz $r2,9a4e <__subdf3+0x5de>
    962c:	40 74 0c 00 	add $r7,$r8,$r3
    9630:	88 01       	add45 $r0,$r1
    9632:	e2 e3       	slt45 $r7,$r3
    9634:	88 0f       	add45 $r0,$r15
    9636:	42 10 5c 0b 	btst $r1,$r0,#0x17
    963a:	4e 12 01 dd 	beqz $r1,99f4 <__subdf3+0x584>
    963e:	42 00 5c 09 	bclr $r0,$r0,#0x17
    9642:	80 67       	mov55 $r3,$r7
    9644:	85 61       	movi55 $r11,#0x1
    9646:	48 00 02 04 	j 9a4e <__subdf3+0x5de>
    964a:	4e 22 01 d7 	beqz $r2,99f8 <__subdf3+0x588>
    964e:	40 20 a0 04 	or $r2,$r1,$r8
    9652:	4e 22 01 fb 	beqz $r2,9a48 <__subdf3+0x5d8>
    9656:	40 50 0c 09 	srli $r5,$r0,#0x3
    965a:	46 20 00 80 	sethi $r2,#0x80
    965e:	40 f0 74 08 	slli $r15,$r0,#0x1d
    9662:	40 02 88 02 	and $r0,$r5,$r2
    9666:	40 37 8c 75 	or_srli $r3,$r15,$r3,#0x3
    966a:	4e 02 01 43 	beqz $r0,98f0 <__subdf3+0x480>
    966e:	40 00 8c 09 	srli $r0,$r1,#0x3
    9672:	fe 86       	and33 $r2,$r0
    9674:	4e 23 01 3e 	bnez $r2,98f0 <__subdf3+0x480>
    9678:	40 30 f4 08 	slli $r3,$r1,#0x1d
    967c:	40 31 a0 75 	or_srli $r3,$r3,$r8,#0x3
    9680:	80 a0       	mov55 $r5,$r0
    9682:	48 00 01 37 	j 98f0 <__subdf3+0x480>
    9686:	d6 0f       	beqs38 $r6,96a4 <__subdf3+0x234>
    9688:	40 74 0c 00 	add $r7,$r8,$r3
    968c:	88 01       	add45 $r0,$r1
    968e:	e2 e3       	slt45 $r7,$r3
    9690:	40 90 3c 00 	add $r9,$r0,$r15
    9694:	40 34 fc 08 	slli $r3,$r9,#0x1f
    9698:	40 31 9c 35 	or_srli $r3,$r3,$r7,#0x1
    969c:	40 04 84 09 	srli $r0,$r9,#0x1
    96a0:	48 00 01 8b 	j 99b6 <__subdf3+0x546>
    96a4:	54 15 00 03 	andi $r1,$r10,#0x3
    96a8:	4e 12 01 ab 	beqz $r1,99fe <__subdf3+0x58e>
    96ac:	5a 18 01 06 	bnec $r1,#0x1,96b8 <__subdf3+0x248>
    96b0:	4e 43 01 ab 	bnez $r4,9a06 <__subdf3+0x596>
    96b4:	81 65       	mov55 $r11,$r5
    96b6:	d5 26       	j8 9702 <__subdf3+0x292>
    96b8:	5a 10 02 04 	beqc $r1,#0x2,96c0 <__subdf3+0x250>
    96bc:	48 00 01 ab 	j 9a12 <__subdf3+0x5a2>
    96c0:	4e 42 01 a9 	beqz $r4,9a12 <__subdf3+0x5a2>
    96c4:	81 65       	mov55 $r11,$r5
    96c6:	80 02       	mov55 $r0,$r2
    96c8:	48 00 01 ab 	j 9a1e <__subdf3+0x5ae>
    96cc:	42 10 5c 0b 	btst $r1,$r0,#0x17
    96d0:	4e 12 01 bf 	beqz $r1,9a4e <__subdf3+0x5de>
    96d4:	8d 61       	addi45 $r11,#0x1
    96d6:	44 10 07 ff 	movi $r1,#0x7ff
    96da:	4c b0 80 0c 	beq $r11,$r1,96f2 <__subdf3+0x282>
    96de:	96 9c       	xlsb33 $r2,$r3
    96e0:	42 00 5c 09 	bclr $r0,$r0,#0x17
    96e4:	40 31 0c 35 	or_srli $r3,$r2,$r3,#0x1
    96e8:	40 31 83 e4 	or_slli $r3,$r3,$r0,#0x1f
    96ec:	92 01       	srli45 $r0,#0x1
    96ee:	48 00 01 b0 	j 9a4e <__subdf3+0x5de>
    96f2:	54 15 00 03 	andi $r1,$r10,#0x3
    96f6:	4e 12 01 85 	beqz $r1,9a00 <__subdf3+0x590>
    96fa:	5a 18 01 08 	bnec $r1,#0x1,970a <__subdf3+0x29a>
    96fe:	4e 43 01 84 	bnez $r4,9a06 <__subdf3+0x596>
    9702:	80 04       	mov55 $r0,$r4
    9704:	80 64       	mov55 $r3,$r4
    9706:	48 00 01 bd 	j 9a80 <__subdf3+0x610>
    970a:	5a 10 02 04 	beqc $r1,#0x2,9712 <__subdf3+0x2a2>
    970e:	48 00 01 82 	j 9a12 <__subdf3+0x5a2>
    9712:	4e 43 01 85 	bnez $r4,9a1c <__subdf3+0x5ac>
    9716:	48 00 01 7e 	j 9a12 <__subdf3+0x5a2>
    971a:	82 22       	mov55 $r17,$r2
    971c:	4e 27 00 51 	blez $r2,97be <__subdf3+0x34e>
    9720:	cd 13       	bnez38 $r5,9746 <__subdf3+0x2d6>
    9722:	40 50 a0 04 	or $r5,$r1,$r8
    9726:	4e 52 01 94 	beqz $r5,9a4e <__subdf3+0x5de>
    972a:	51 11 7f ff 	addi $r17,$r2,#-1
    972e:	4f 13 00 08 	bnez $r17,973e <__subdf3+0x2ce>
    9732:	40 71 a0 01 	sub $r7,$r3,$r8
    9736:	8a 01       	sub45 $r0,$r1
    9738:	e2 67       	slt45 $r3,$r7
    973a:	8a 0f       	sub45 $r0,$r15
    973c:	d5 3d       	j8 97b6 <__subdf3+0x346>
    973e:	4c b3 40 08 	bne $r11,$r6,974e <__subdf3+0x2de>
    9742:	48 00 01 86 	j 9a4e <__subdf3+0x5de>
    9746:	4c b3 01 84 	beq $r11,$r6,9a4e <__subdf3+0x5de>
    974a:	42 10 dc 08 	bset $r1,$r1,#0x17
    974e:	5e f8 80 39 	sltsi $r15,$r17,#0x39
    9752:	e8 27       	beqzs8 97a0 <__subdf3+0x330>
    9754:	5e f8 80 20 	sltsi $r15,$r17,#0x20
    9758:	e8 13       	beqzs8 977e <__subdf3+0x30e>
    975a:	53 28 80 20 	subri $r18,$r17,#0x20
    975e:	40 70 c8 0c 	sll $r7,$r1,$r18
    9762:	40 24 44 0d 	srl $r2,$r8,$r17
    9766:	40 f3 88 04 	or $r15,$r7,$r2
    976a:	85 20       	movi55 $r9,#0x0
    976c:	40 74 48 0c 	sll $r7,$r8,$r18
    9770:	40 74 9c 06 	slt $r7,$r9,$r7
    9774:	40 f7 9c 04 	or $r15,$r15,$r7
    9778:	41 10 c4 0d 	srl $r17,$r1,$r17
    977c:	d5 16       	j8 97a8 <__subdf3+0x338>
    977e:	40 90 c4 0d 	srl $r9,$r1,$r17
    9782:	5b 10 20 07 	beqc $r17,#0x20,9790 <__subdf3+0x320>
    9786:	53 18 80 40 	subri $r17,$r17,#0x40
    978a:	41 10 c4 0c 	sll $r17,$r1,$r17
    978e:	d5 02       	j8 9792 <__subdf3+0x322>
    9790:	86 20       	movi55 $r17,#0x0
    9792:	40 78 a0 04 	or $r7,$r17,$r8
    9796:	86 20       	movi55 $r17,#0x0
    9798:	e3 a7       	slt45 $r17,$r7
    979a:	40 f7 a4 04 	or $r15,$r15,$r9
    979e:	d5 05       	j8 97a8 <__subdf3+0x338>
    97a0:	40 70 a0 04 	or $r7,$r1,$r8
    97a4:	86 20       	movi55 $r17,#0x0
    97a6:	e3 a7       	slt45 $r17,$r7
    97a8:	40 71 bc 01 	sub $r7,$r3,$r15
    97ac:	41 10 44 01 	sub $r17,$r0,$r17
    97b0:	e2 67       	slt45 $r3,$r7
    97b2:	40 08 bc 01 	sub $r0,$r17,$r15
    97b6:	80 67       	mov55 $r3,$r7
    97b8:	80 e4       	mov55 $r7,$r4
    97ba:	48 00 00 c0 	j 993a <__subdf3+0x4ca>
    97be:	c2 4c       	beqz38 $r2,9856 <__subdf3+0x3e6>
    97c0:	4e b3 00 12 	bnez $r11,97e4 <__subdf3+0x374>
    97c4:	40 40 0c 04 	or $r4,$r0,$r3
    97c8:	4e 42 01 2e 	beqz $r4,9a24 <__subdf3+0x5b4>
    97cc:	fe 93       	not33 $r2,$r2
    97ce:	ca 08       	bnez38 $r2,97de <__subdf3+0x36e>
    97d0:	40 34 0c 01 	sub $r3,$r8,$r3
    97d4:	9a 08       	sub333 $r0,$r1,$r0
    97d6:	40 84 0c 06 	slt $r8,$r8,$r3
    97da:	8a 08       	sub45 $r0,$r8
    97dc:	d5 3b       	j8 9852 <__subdf3+0x3e2>
    97de:	de 08       	bnes38 $r6,97ee <__subdf3+0x37e>
    97e0:	48 00 01 22 	j 9a24 <__subdf3+0x5b4>
    97e4:	4c 53 01 20 	beq $r5,$r6,9a24 <__subdf3+0x5b4>
    97e8:	fe 92       	neg33 $r2,$r2
    97ea:	42 00 5c 08 	bset $r0,$r0,#0x17
    97ee:	5e f1 00 39 	sltsi $r15,$r2,#0x39
    97f2:	e8 26       	beqzs8 983e <__subdf3+0x3ce>
    97f4:	5e f1 00 20 	sltsi $r15,$r2,#0x20
    97f8:	e8 13       	beqzs8 981e <__subdf3+0x3ae>
    97fa:	52 41 00 20 	subri $r4,$r2,#0x20
    97fe:	40 f0 10 0c 	sll $r15,$r0,$r4
    9802:	40 61 88 0d 	srl $r6,$r3,$r2
    9806:	40 31 90 0c 	sll $r3,$r3,$r4
    980a:	84 80       	movi55 $r4,#0x0
    980c:	40 32 0c 06 	slt $r3,$r4,$r3
    9810:	40 f7 98 04 	or $r15,$r15,$r6
    9814:	40 f7 8c 04 	or $r15,$r15,$r3
    9818:	40 40 08 0d 	srl $r4,$r0,$r2
    981c:	d5 15       	j8 9846 <__subdf3+0x3d6>
    981e:	40 40 08 0d 	srl $r4,$r0,$r2
    9822:	5a 20 20 07 	beqc $r2,#0x20,9830 <__subdf3+0x3c0>
    9826:	52 21 00 40 	subri $r2,$r2,#0x40
    982a:	40 20 08 0c 	sll $r2,$r0,$r2
    982e:	d5 02       	j8 9832 <__subdf3+0x3c2>
    9830:	84 40       	movi55 $r2,#0x0
    9832:	fe d7       	or33 $r3,$r2
    9834:	84 40       	movi55 $r2,#0x0
    9836:	e2 43       	slt45 $r2,$r3
    9838:	40 f7 90 04 	or $r15,$r15,$r4
    983c:	d5 04       	j8 9844 <__subdf3+0x3d4>
    983e:	fe c7       	or33 $r3,$r0
    9840:	84 40       	movi55 $r2,#0x0
    9842:	e2 43       	slt45 $r2,$r3
    9844:	80 82       	mov55 $r4,$r2
    9846:	40 34 3c 01 	sub $r3,$r8,$r15
    984a:	9b 0c       	sub333 $r4,$r1,$r4
    984c:	e3 03       	slt45 $r8,$r3
    984e:	40 02 3c 01 	sub $r0,$r4,$r15
    9852:	81 65       	mov55 $r11,$r5
    9854:	d5 73       	j8 993a <__subdf3+0x4ca>
    9856:	50 25 80 01 	addi $r2,$r11,#0x1
    985a:	96 95       	x11b33 $r2,$r2
    985c:	e4 42       	sltsi45 $r2,#0x2
    985e:	e8 52       	beqzs8 9902 <__subdf3+0x492>
    9860:	40 20 a0 04 	or $r2,$r1,$r8
    9864:	40 50 0c 04 	or $r5,$r0,$r3
    9868:	4e b3 00 25 	bnez $r11,98b2 <__subdf3+0x442>
    986c:	cd 04       	bnez38 $r5,9874 <__subdf3+0x404>
    986e:	4e 23 00 df 	bnez $r2,9a2c <__subdf3+0x5bc>
    9872:	d5 17       	j8 98a0 <__subdf3+0x430>
    9874:	4e 22 00 ed 	beqz $r2,9a4e <__subdf3+0x5de>
    9878:	40 51 a0 01 	sub $r5,$r3,$r8
    987c:	9a 81       	sub333 $r2,$r0,$r1
    987e:	e2 65       	slt45 $r3,$r5
    9880:	8a 4f       	sub45 $r2,$r15
    9882:	42 61 5c 0b 	btst $r6,$r2,#0x17
    9886:	c6 09       	beqz38 $r6,9898 <__subdf3+0x428>
    9888:	40 34 0c 01 	sub $r3,$r8,$r3
    988c:	9a 08       	sub333 $r0,$r1,$r0
    988e:	40 84 0c 06 	slt $r8,$r8,$r3
    9892:	8a 08       	sub45 $r0,$r8
    9894:	48 00 00 dc 	j 9a4c <__subdf3+0x5dc>
    9898:	40 01 14 04 	or $r0,$r2,$r5
    989c:	4e 03 00 cb 	bnez $r0,9a32 <__subdf3+0x5c2>
    98a0:	54 45 00 03 	andi $r4,$r10,#0x3
    98a4:	8e 82       	subi45 $r4,#0x2
    98a6:	5c 42 00 01 	slti $r4,$r4,#0x1
    98aa:	80 0b       	mov55 $r0,$r11
    98ac:	80 6b       	mov55 $r3,$r11
    98ae:	48 00 00 e9 	j 9a80 <__subdf3+0x610>
    98b2:	cd 08       	bnez38 $r5,98c2 <__subdf3+0x452>
    98b4:	4e 22 00 c2 	beqz $r2,9a38 <__subdf3+0x5c8>
    98b8:	80 01       	mov55 $r0,$r1
    98ba:	80 68       	mov55 $r3,$r8
    98bc:	80 87       	mov55 $r4,$r7
    98be:	48 00 00 c5 	j 9a48 <__subdf3+0x5d8>
    98c2:	4e 22 00 c3 	beqz $r2,9a48 <__subdf3+0x5d8>
    98c6:	40 50 0c 09 	srli $r5,$r0,#0x3
    98ca:	46 20 00 80 	sethi $r2,#0x80
    98ce:	40 f0 74 08 	slli $r15,$r0,#0x1d
    98d2:	40 02 88 02 	and $r0,$r5,$r2
    98d6:	40 37 8c 75 	or_srli $r3,$r15,$r3,#0x3
    98da:	c0 0b       	beqz38 $r0,98f0 <__subdf3+0x480>
    98dc:	40 00 8c 09 	srli $r0,$r1,#0x3
    98e0:	fe 86       	and33 $r2,$r0
    98e2:	ca 07       	bnez38 $r2,98f0 <__subdf3+0x480>
    98e4:	40 30 f4 08 	slli $r3,$r1,#0x1d
    98e8:	40 31 a0 75 	or_srli $r3,$r3,$r8,#0x3
    98ec:	80 a0       	mov55 $r5,$r0
    98ee:	80 87       	mov55 $r4,$r7
    98f0:	40 01 f4 09 	srli $r0,$r3,#0x1d
    98f4:	40 00 14 64 	or_slli $r0,$r0,$r5,#0x3
    98f8:	94 db       	slli333 $r3,$r3,#0x3
    98fa:	44 b0 07 ff 	movi $r11,#0x7ff
    98fe:	48 00 00 a8 	j 9a4e <__subdf3+0x5de>
    9902:	40 21 a0 01 	sub $r2,$r3,$r8
    9906:	9b 41       	sub333 $r5,$r0,$r1
    9908:	e2 62       	slt45 $r3,$r2
    990a:	40 62 bc 01 	sub $r6,$r5,$r15
    990e:	42 53 5c 0b 	btst $r5,$r6,#0x17
    9912:	c5 08       	beqz38 $r5,9922 <__subdf3+0x4b2>
    9914:	40 24 0c 01 	sub $r2,$r8,$r3
    9918:	9b 08       	sub333 $r4,$r1,$r0
    991a:	e3 02       	slt45 $r8,$r2
    991c:	40 62 3c 01 	sub $r6,$r4,$r15
    9920:	d5 16       	j8 994c <__subdf3+0x4dc>
    9922:	40 03 08 04 	or $r0,$r6,$r2
    9926:	c8 14       	bnez38 $r0,994e <__subdf3+0x4de>
    9928:	54 45 00 03 	andi $r4,$r10,#0x3
    992c:	8e 82       	subi45 $r4,#0x2
    992e:	5c 42 00 01 	slti $r4,$r4,#0x1
    9932:	80 60       	mov55 $r3,$r0
    9934:	81 60       	mov55 $r11,$r0
    9936:	48 00 00 a5 	j 9a80 <__subdf3+0x610>
    993a:	42 10 5c 0b 	btst $r1,$r0,#0x17
    993e:	4e 12 00 87 	beqz $r1,9a4c <__subdf3+0x5dc>
    9942:	41 30 24 08 	slli $r19,$r0,#0x9
    9946:	40 69 a4 09 	srli $r6,$r19,#0x9
    994a:	80 43       	mov55 $r2,$r3
    994c:	80 87       	mov55 $r4,$r7
    994e:	c6 04       	beqz38 $r6,9956 <__subdf3+0x4e6>
    9950:	42 73 00 07 	clz $r7,$r6
    9954:	d5 05       	j8 995e <__subdf3+0x4ee>
    9956:	42 71 00 07 	clz $r7,$r2
    995a:	50 73 80 20 	addi $r7,$r7,#0x20
    995e:	51 03 ff f8 	addi $r16,$r7,#-8
    9962:	5e f8 00 20 	sltsi $r15,$r16,#0x20
    9966:	e8 0c       	beqzs8 997e <__subdf3+0x50e>
    9968:	52 73 80 28 	subri $r7,$r7,#0x28
    996c:	40 f3 40 0c 	sll $r15,$r6,$r16
    9970:	40 71 1c 0d 	srl $r7,$r2,$r7
    9974:	40 63 bc 04 	or $r6,$r7,$r15
    9978:	40 31 40 0c 	sll $r3,$r2,$r16
    997c:	d5 06       	j8 9988 <__subdf3+0x518>
    997e:	50 63 ff d8 	addi $r6,$r7,#-40
    9982:	40 61 18 0c 	sll $r6,$r2,$r6
    9986:	84 60       	movi55 $r3,#0x0
    9988:	e1 8b       	slts45 $r16,$r11
    998a:	e9 2b       	bnezs8 99e0 <__subdf3+0x570>
    998c:	40 58 2c 01 	sub $r5,$r16,$r11
    9990:	9c 69       	addi333 $r1,$r5,#0x1
    9992:	5e f0 80 20 	sltsi $r15,$r1,#0x20
    9996:	e8 12       	beqzs8 99ba <__subdf3+0x54a>
    9998:	52 52 80 1f 	subri $r5,$r5,#0x1f
    999c:	40 03 14 0c 	sll $r0,$r6,$r5
    99a0:	40 21 84 0d 	srl $r2,$r3,$r1
    99a4:	40 31 94 0c 	sll $r3,$r3,$r5
    99a8:	84 a0       	movi55 $r5,#0x0
    99aa:	fe 87       	or33 $r2,$r0
    99ac:	e2 a3       	slt45 $r5,$r3
    99ae:	40 31 3c 04 	or $r3,$r2,$r15
    99b2:	40 03 04 0d 	srl $r0,$r6,$r1
    99b6:	81 65       	mov55 $r11,$r5
    99b8:	d5 4b       	j8 9a4e <__subdf3+0x5de>
    99ba:	50 22 ff e1 	addi $r2,$r5,#-31
    99be:	40 23 08 0d 	srl $r2,$r6,$r2
    99c2:	5a 10 20 07 	beqc $r1,#0x20,99d0 <__subdf3+0x560>
    99c6:	53 02 80 3f 	subri $r16,$r5,#0x3f
    99ca:	40 63 40 0c 	sll $r6,$r6,$r16
    99ce:	d5 02       	j8 99d2 <__subdf3+0x562>
    99d0:	84 c0       	movi55 $r6,#0x0
    99d2:	fe f7       	or33 $r3,$r6
    99d4:	84 00       	movi55 $r0,#0x0
    99d6:	e2 03       	slt45 $r0,$r3
    99d8:	40 37 88 04 	or $r3,$r15,$r2
    99dc:	81 60       	mov55 $r11,$r0
    99de:	d5 38       	j8 9a4e <__subdf3+0x5de>
    99e0:	8b 70       	sub45 $r11,$r16
    99e2:	42 03 5c 09 	bclr $r0,$r6,#0x17
    99e6:	d5 34       	j8 9a4e <__subdf3+0x5de>
    99e8:	80 01       	mov55 $r0,$r1
    99ea:	80 68       	mov55 $r3,$r8
    99ec:	d5 e5       	j8 99b6 <__subdf3+0x546>
    99ee:	80 01       	mov55 $r0,$r1
    99f0:	80 68       	mov55 $r3,$r8
    99f2:	d5 2e       	j8 9a4e <__subdf3+0x5de>
    99f4:	80 67       	mov55 $r3,$r7
    99f6:	d5 2c       	j8 9a4e <__subdf3+0x5de>
    99f8:	80 01       	mov55 $r0,$r1
    99fa:	80 68       	mov55 $r3,$r8
    99fc:	d5 26       	j8 9a48 <__subdf3+0x5d8>
    99fe:	81 65       	mov55 $r11,$r5
    9a00:	80 01       	mov55 $r0,$r1
    9a02:	80 61       	mov55 $r3,$r1
    9a04:	d5 3e       	j8 9a80 <__subdf3+0x610>
    9a06:	84 1f       	movi55 $r0,#-1
    9a08:	80 60       	mov55 $r3,$r0
    9a0a:	44 b0 07 fe 	movi $r11,#0x7fe
    9a0e:	80 81       	mov55 $r4,$r1
    9a10:	d5 22       	j8 9a54 <__subdf3+0x5e4>
    9a12:	84 1f       	movi55 $r0,#-1
    9a14:	80 60       	mov55 $r3,$r0
    9a16:	44 b0 07 fe 	movi $r11,#0x7fe
    9a1a:	d5 1d       	j8 9a54 <__subdf3+0x5e4>
    9a1c:	84 00       	movi55 $r0,#0x0
    9a1e:	80 60       	mov55 $r3,$r0
    9a20:	84 81       	movi55 $r4,#0x1
    9a22:	d5 2f       	j8 9a80 <__subdf3+0x610>
    9a24:	80 01       	mov55 $r0,$r1
    9a26:	80 68       	mov55 $r3,$r8
    9a28:	81 65       	mov55 $r11,$r5
    9a2a:	d5 11       	j8 9a4c <__subdf3+0x5dc>
    9a2c:	80 01       	mov55 $r0,$r1
    9a2e:	80 68       	mov55 $r3,$r8
    9a30:	d5 0e       	j8 9a4c <__subdf3+0x5dc>
    9a32:	80 02       	mov55 $r0,$r2
    9a34:	80 65       	mov55 $r3,$r5
    9a36:	d5 0c       	j8 9a4e <__subdf3+0x5de>
    9a38:	46 f0 07 ff 	sethi $r15,#0x7ff
    9a3c:	50 07 8f ff 	addi $r0,$r15,#0xfff
    9a40:	84 78       	movi55 $r3,#-8
    9a42:	81 66       	mov55 $r11,$r6
    9a44:	80 82       	mov55 $r4,$r2
    9a46:	d5 1d       	j8 9a80 <__subdf3+0x610>
    9a48:	81 66       	mov55 $r11,$r6
    9a4a:	d5 02       	j8 9a4e <__subdf3+0x5de>
    9a4c:	80 87       	mov55 $r4,$r7
    9a4e:	54 11 80 07 	andi $r1,$r3,#0x7
    9a52:	c1 17       	beqz38 $r1,9a80 <__subdf3+0x610>
    9a54:	54 15 00 03 	andi $r1,$r10,#0x3
    9a58:	5a 10 01 0c 	beqc $r1,#0x1,9a70 <__subdf3+0x600>
    9a5c:	c1 04       	beqz38 $r1,9a64 <__subdf3+0x5f4>
    9a5e:	5a 10 02 0b 	beqc $r1,#0x2,9a74 <__subdf3+0x604>
    9a62:	d5 0f       	j8 9a80 <__subdf3+0x610>
    9a64:	54 11 80 0f 	andi $r1,$r3,#0xf
    9a68:	5a 10 04 0c 	beqc $r1,#0x4,9a80 <__subdf3+0x610>
    9a6c:	9d dc       	addi333 $r7,$r3,#0x4
    9a6e:	d5 06       	j8 9a7a <__subdf3+0x60a>
    9a70:	cc 08       	bnez38 $r4,9a80 <__subdf3+0x610>
    9a72:	d5 02       	j8 9a76 <__subdf3+0x606>
    9a74:	c4 06       	beqz38 $r4,9a80 <__subdf3+0x610>
    9a76:	50 71 80 08 	addi $r7,$r3,#0x8
    9a7a:	e2 e3       	slt45 $r7,$r3
    9a7c:	88 0f       	add45 $r0,$r15
    9a7e:	80 67       	mov55 $r3,$r7
    9a80:	42 10 5c 0b 	btst $r1,$r0,#0x17
    9a84:	c1 1c       	beqz38 $r1,9abc <__subdf3+0x64c>
    9a86:	8d 61       	addi45 $r11,#0x1
    9a88:	44 10 07 ff 	movi $r1,#0x7ff
    9a8c:	4c b0 80 05 	beq $r11,$r1,9a96 <__subdf3+0x626>
    9a90:	42 00 5c 09 	bclr $r0,$r0,#0x17
    9a94:	d5 14       	j8 9abc <__subdf3+0x64c>
    9a96:	54 05 00 03 	andi $r0,$r10,#0x3
    9a9a:	c0 10       	beqz38 $r0,9aba <__subdf3+0x64a>
    9a9c:	5a 08 01 06 	bnec $r0,#0x1,9aa8 <__subdf3+0x638>
    9aa0:	cc 07       	bnez38 $r4,9aae <__subdf3+0x63e>
    9aa2:	80 04       	mov55 $r0,$r4
    9aa4:	80 64       	mov55 $r3,$r4
    9aa6:	d5 0b       	j8 9abc <__subdf3+0x64c>
    9aa8:	5a 08 02 03 	bnec $r0,#0x2,9aae <__subdf3+0x63e>
    9aac:	cc 06       	bnez38 $r4,9ab8 <__subdf3+0x648>
    9aae:	84 1f       	movi55 $r0,#-1
    9ab0:	80 60       	mov55 $r3,$r0
    9ab2:	44 b0 07 fe 	movi $r11,#0x7fe
    9ab6:	d5 03       	j8 9abc <__subdf3+0x64c>
    9ab8:	84 00       	movi55 $r0,#0x0
    9aba:	80 60       	mov55 $r3,$r0
    9abc:	40 f0 74 08 	slli $r15,$r0,#0x1d
    9ac0:	44 10 07 ff 	movi $r1,#0x7ff
    9ac4:	40 f7 8c 75 	or_srli $r15,$r15,$r3,#0x3
    9ac8:	92 03       	srli45 $r0,#0x3
    9aca:	4c b0 c0 09 	bne $r11,$r1,9adc <__subdf3+0x66c>
    9ace:	40 17 80 04 	or $r1,$r15,$r0
    9ad2:	c1 04       	beqz38 $r1,9ada <__subdf3+0x66a>
    9ad4:	42 00 4c 08 	bset $r0,$r0,#0x13
    9ad8:	d5 02       	j8 9adc <__subdf3+0x66c>
    9ada:	80 01       	mov55 $r0,$r1
    9adc:	84 40       	movi55 $r2,#0x0
    9ade:	80 62       	mov55 $r3,$r2
    9ae0:	80 4f       	mov55 $r2,$r15
    9ae2:	40 f1 d0 09 	srli $r15,$r3,#0x14
    9ae6:	40 f7 d0 08 	slli $r15,$r15,#0x14
    9aea:	40 00 30 08 	slli $r0,$r0,#0xc
    9aee:	46 18 00 ff 	sethi $r1,#0x800ff
    9af2:	40 07 81 95 	or_srli $r0,$r15,$r0,#0xc
    9af6:	50 10 8f ff 	addi $r1,$r1,#0xfff
    9afa:	54 55 87 ff 	andi $r5,$r11,#0x7ff
    9afe:	fe 0e       	and33 $r0,$r1
    9b00:	40 00 16 84 	or_slli $r0,$r0,$r5,#0x14
    9b04:	42 00 7c 09 	bclr $r0,$r0,#0x1f
    9b08:	40 30 13 e4 	or_slli $r3,$r0,$r4,#0x1f
    9b0c:	6a 20 00 49 	fmtdr $r2,$fd0
    9b10:	fc e0       	pop25 $r14,#0    ! {$r6~$r14, $fp, $gp, $lp}

00009b12 <__floatsidf>:
    9b12:	fc 00       	push25 $r6,#0    ! {$r6, $fp, $gp, $lp}
    9b14:	c0 18       	beqz38 $r0,9b44 <__floatsidf+0x32>
    9b16:	40 60 7c 09 	srli $r6,$r0,#0x1f
    9b1a:	c6 02       	beqz38 $r6,9b1e <__floatsidf+0xc>
    9b1c:	fe 02       	neg33 $r0,$r0
    9b1e:	42 40 00 07 	clz $r4,$r0
    9b22:	e4 8b       	sltsi45 $r4,#0xb
    9b24:	52 32 04 1e 	subri $r3,$r4,#0x41e
    9b28:	e8 09       	beqzs8 9b3a <__floatsidf+0x28>
    9b2a:	52 22 00 0b 	subri $r2,$r4,#0xb
    9b2e:	8c 95       	addi45 $r4,#0x15
    9b30:	40 10 08 0d 	srl $r1,$r0,$r2
    9b34:	40 00 10 0c 	sll $r0,$r0,$r4
    9b38:	d5 09       	j8 9b4a <__floatsidf+0x38>
    9b3a:	8e 8b       	subi45 $r4,#0xb
    9b3c:	40 10 10 0c 	sll $r1,$r0,$r4
    9b40:	84 00       	movi55 $r0,#0x0
    9b42:	d5 04       	j8 9b4a <__floatsidf+0x38>
    9b44:	80 20       	mov55 $r1,$r0
    9b46:	80 60       	mov55 $r3,$r0
    9b48:	80 c0       	mov55 $r6,$r0
    9b4a:	84 80       	movi55 $r4,#0x0
    9b4c:	80 a4       	mov55 $r5,$r4
    9b4e:	80 80       	mov55 $r4,$r0
    9b50:	40 02 d0 09 	srli $r0,$r5,#0x14
    9b54:	40 00 50 08 	slli $r0,$r0,#0x14
    9b58:	40 10 b0 08 	slli $r1,$r1,#0xc
    9b5c:	40 10 05 95 	or_srli $r1,$r0,$r1,#0xc
    9b60:	46 08 00 ff 	sethi $r0,#0x800ff
    9b64:	50 00 0f ff 	addi $r0,$r0,#0xfff
    9b68:	96 dd       	x11b33 $r3,$r3
    9b6a:	fe 46       	and33 $r1,$r0
    9b6c:	40 10 8e 84 	or_slli $r1,$r1,$r3,#0x14
    9b70:	42 10 fc 09 	bclr $r1,$r1,#0x1f
    9b74:	40 50 9b e4 	or_slli $r5,$r1,$r6,#0x1f
    9b78:	6a 40 00 49 	fmtdr $r4,$fd0
    9b7c:	fc 80       	pop25 $r6,#0    ! {$r6, $fp, $gp, $lp}

00009b7e <__floatunsidf>:
    9b7e:	c0 14       	beqz38 $r0,9ba6 <__floatunsidf+0x28>
    9b80:	42 30 00 07 	clz $r3,$r0
    9b84:	e4 6b       	sltsi45 $r3,#0xb
    9b86:	52 41 84 1e 	subri $r4,$r3,#0x41e
    9b8a:	e8 09       	beqzs8 9b9c <__floatunsidf+0x1e>
    9b8c:	52 21 80 0b 	subri $r2,$r3,#0xb
    9b90:	8c 75       	addi45 $r3,#0x15
    9b92:	40 10 08 0d 	srl $r1,$r0,$r2
    9b96:	40 00 0c 0c 	sll $r0,$r0,$r3
    9b9a:	d5 08       	j8 9baa <__floatunsidf+0x2c>
    9b9c:	8e 6b       	subi45 $r3,#0xb
    9b9e:	40 10 0c 0c 	sll $r1,$r0,$r3
    9ba2:	84 00       	movi55 $r0,#0x0
    9ba4:	d5 03       	j8 9baa <__floatunsidf+0x2c>
    9ba6:	80 20       	mov55 $r1,$r0
    9ba8:	80 80       	mov55 $r4,$r0
    9baa:	84 40       	movi55 $r2,#0x0
    9bac:	80 62       	mov55 $r3,$r2
    9bae:	80 40       	mov55 $r2,$r0
    9bb0:	40 01 d0 09 	srli $r0,$r3,#0x14
    9bb4:	40 00 50 08 	slli $r0,$r0,#0x14
    9bb8:	40 10 b0 08 	slli $r1,$r1,#0xc
    9bbc:	40 10 05 95 	or_srli $r1,$r0,$r1,#0xc
    9bc0:	46 08 00 ff 	sethi $r0,#0x800ff
    9bc4:	50 00 0f ff 	addi $r0,$r0,#0xfff
    9bc8:	97 25       	x11b33 $r4,$r4
    9bca:	fe 46       	and33 $r1,$r0
    9bcc:	40 10 92 84 	or_slli $r1,$r1,$r4,#0x14
    9bd0:	42 30 fc 09 	bclr $r3,$r1,#0x1f
    9bd4:	6a 20 00 49 	fmtdr $r2,$fd0
    9bd8:	dd 9e       	ret5 $lp
    9bda:	00 00 2c 20 	lbi $r0,[$r0+#0x2c20]
    9bde:	66 75 6e 63 	bitci $r7,$r10,#0x6e63
    9be2:	74 69 6f 6e 	*unknown*
    9be6:	3a 20 00 00 	lmw.bi $r2,[$r0],$r0,#0x0    ! {$r2~$r0}
    9bea:	00 00 61 73 	lbi $r0,[$r0+#-7821]
    9bee:	73 65 72 74 	*unknown*
    9bf2:	69 6f 6e 20 	*unknown*
    9bf6:	22 25 73 22 	lhsi $r2,[$r10+#-6588]
    9bfa:	20 66 61 69 	lbsi $r6,[$r12+#-7831]
    9bfe:	6c 65 64 3a 	*unknown*
    9c02:	20 66 69 6c 	lbsi $r6,[$r12+#-5780]
    9c06:	65 20 22 25 	trap #0x111
    9c0a:	73 22 2c 20 	*unknown*
    9c0e:	6c 69 6e 65 	*unknown*
    9c12:	20 25 64 25 	lbsi $r2,[$r10+#-7131]
    9c16:	73 25 73 0a 	*unknown*
	...

00009c1c <__assert_func>:
    9c1c:	fc 03       	push25 $r6,#24    ! {$r6, $fp, $gp, $lp}
    9c1e:	80 a0       	mov55 $r5,$r0
    9c20:	3c 0c 00 1b 	lwi.gp $r0,[+#0x6c]
    9c24:	ca 05       	bnez38 $r2,9c2e <__assert_func+0x12>
    9c26:	44 40 01 38 	movi $r4,#0x138
    9c2a:	80 44       	mov55 $r2,$r4
    9c2c:	d5 03       	j8 9c32 <__assert_func+0x16>
    9c2e:	44 40 9b dc 	movi $r4,#0x9bdc
    9c32:	b6 7f       	swi450 $r3,[$sp]
    9c34:	f5 81       	swi37.sp $r5,[+#0x4]
    9c36:	f1 82       	swi37.sp $r1,[+#0x8]
    9c38:	f4 83       	swi37.sp $r4,[+#0xc]
    9c3a:	f2 84       	swi37.sp $r2,[+#0x10]
    9c3c:	44 10 9b ec 	movi $r1,#0x9bec
    9c40:	49 00 01 34 	jal 9ea8 <fiprintf>
    9c44:	49 00 08 fc 	jal ae3c <abort>
    9c48:	92 00       	nop16
	...

00009c4c <atoi>:
    9c4c:	84 20       	movi55 $r1,#0x0
    9c4e:	84 4a       	movi55 $r2,#0xa
    9c50:	48 00 03 14 	j a278 <strtol>

00009c54 <__sflush_r>:
    9c54:	fc 41       	push25 $r10,#8    ! {$r6~$r10, $fp, $gp, $lp}
    9c56:	3f c8 2b 50 	addi.gp $fp,#0x2b50
    9c5a:	22 20 80 06 	lhsi $r2,[$r1+#0xc]
    9c5e:	f0 81       	swi37.sp $r0,[+#0x4]
    9c60:	96 11       	zeh33 $r0,$r2
    9c62:	80 c1       	mov55 $r6,$r1
    9c64:	54 10 00 08 	andi $r1,$r0,#0x8
    9c68:	4e 13 00 67 	bnez $r1,9d36 <__sflush_r+0xe2>
    9c6c:	a0 31       	lwi333 $r0,[$r6+#0x4]
    9c6e:	58 21 08 00 	ori $r2,$r2,#0x800
    9c72:	ac b6       	shi333 $r2,[$r6+#0xc]
    9c74:	4e 06 00 06 	bgtz $r0,9c80 <__sflush_r+0x2c>
    9c78:	04 03 00 0f 	lwi $r0,[$r6+#0x3c]
    9c7c:	4e 07 00 1d 	blez $r0,9cb6 <__sflush_r+0x62>
    9c80:	04 43 00 0a 	lwi $r4,[$r6+#0x28]
    9c84:	c4 19       	beqz38 $r4,9cb6 <__sflush_r+0x62>
    9c86:	54 21 10 00 	andi $r2,$r2,#0x1000
    9c8a:	bf 00       	lwi37 $r7,[$fp+#0x0]
    9c8c:	84 00       	movi55 $r0,#0x0
    9c8e:	96 91       	zeh33 $r2,$r2
    9c90:	b8 80       	swi37 $r0,[$fp+#0x0]
    9c92:	c2 04       	beqz38 $r2,9c9a <__sflush_r+0x46>
    9c94:	04 23 00 14 	lwi $r2,[$r6+#0x50]
    9c98:	d5 11       	j8 9cba <__sflush_r+0x66>
    9c9a:	f0 01       	lwi37.sp $r0,[+#0x4]
    9c9c:	a0 77       	lwi333 $r1,[$r6+#0x1c]
    9c9e:	84 61       	movi55 $r3,#0x1
    9ca0:	dd 24       	jral5 $r4
    9ca2:	80 40       	mov55 $r2,$r0
    9ca4:	5a 0f ff 0b 	bnec $r0,#-1,9cba <__sflush_r+0x66>
    9ca8:	b8 00       	lwi37 $r0,[$fp+#0x0]
    9caa:	c0 08       	beqz38 $r0,9cba <__sflush_r+0x66>
    9cac:	5a 00 1d 04 	beqc $r0,#0x1d,9cb4 <__sflush_r+0x60>
    9cb0:	5a 08 16 51 	bnec $r0,#0x16,9d52 <__sflush_r+0xfe>
    9cb4:	bf 80       	swi37 $r7,[$fp+#0x0]
    9cb6:	84 00       	movi55 $r0,#0x0
    9cb8:	d5 61       	j8 9d7a <__sflush_r+0x126>
    9cba:	a4 36       	lhi333 $r0,[$r6+#0xc]
    9cbc:	96 16       	bmski33 $r0,#0x2
    9cbe:	c0 09       	beqz38 $r0,9cd0 <__sflush_r+0x7c>
    9cc0:	a0 31       	lwi333 $r0,[$r6+#0x4]
    9cc2:	8a 40       	sub45 $r2,$r0
    9cc4:	04 03 00 0c 	lwi $r0,[$r6+#0x30]
    9cc8:	c0 04       	beqz38 $r0,9cd0 <__sflush_r+0x7c>
    9cca:	04 03 00 0f 	lwi $r0,[$r6+#0x3c]
    9cce:	8a 40       	sub45 $r2,$r0
    9cd0:	04 43 00 0a 	lwi $r4,[$r6+#0x28]
    9cd4:	a0 77       	lwi333 $r1,[$r6+#0x1c]
    9cd6:	f0 01       	lwi37.sp $r0,[+#0x4]
    9cd8:	84 60       	movi55 $r3,#0x0
    9cda:	dd 24       	jral5 $r4
    9cdc:	a4 76       	lhi333 $r1,[$r6+#0xc]
    9cde:	5a 0f ff 08 	bnec $r0,#-1,9cee <__sflush_r+0x9a>
    9ce2:	ba 00       	lwi37 $r2,[$fp+#0x0]
    9ce4:	c2 05       	beqz38 $r2,9cee <__sflush_r+0x9a>
    9ce6:	5a 20 1d 04 	beqc $r2,#0x1d,9cee <__sflush_r+0x9a>
    9cea:	5a 28 16 22 	bnec $r2,#0x16,9d2e <__sflush_r+0xda>
    9cee:	66 10 88 00 	bitci $r1,$r1,#0x800
    9cf2:	96 4b       	seh33 $r1,$r1
    9cf4:	84 40       	movi55 $r2,#0x0
    9cf6:	ac 76       	shi333 $r1,[$r6+#0xc]
    9cf8:	a8 b1       	swi333 $r2,[$r6+#0x4]
    9cfa:	54 10 90 00 	andi $r1,$r1,#0x1000
    9cfe:	a0 b4       	lwi333 $r2,[$r6+#0x10]
    9d00:	b6 46       	swi450 $r2,[$r6]
    9d02:	c1 07       	beqz38 $r1,9d10 <__sflush_r+0xbc>
    9d04:	5a 0f ff 04 	bnec $r0,#-1,9d0c <__sflush_r+0xb8>
    9d08:	b9 00       	lwi37 $r1,[$fp+#0x0]
    9d0a:	c9 03       	bnez38 $r1,9d10 <__sflush_r+0xbc>
    9d0c:	14 03 00 14 	swi $r0,[$r6+#0x50]
    9d10:	04 13 00 0c 	lwi $r1,[$r6+#0x30]
    9d14:	bf 80       	swi37 $r7,[$fp+#0x0]
    9d16:	c1 d0       	beqz38 $r1,9cb6 <__sflush_r+0x62>
    9d18:	50 03 00 40 	addi $r0,$r6,#0x40
    9d1c:	4c 10 00 05 	beq $r1,$r0,9d26 <__sflush_r+0xd2>
    9d20:	f0 01       	lwi37.sp $r0,[+#0x4]
    9d22:	49 00 01 87 	jal a030 <_free_r>
    9d26:	84 00       	movi55 $r0,#0x0
    9d28:	14 03 00 0c 	swi $r0,[$r6+#0x30]
    9d2c:	d5 27       	j8 9d7a <__sflush_r+0x126>
    9d2e:	58 10 80 40 	ori $r1,$r1,#0x40
    9d32:	ac 76       	shi333 $r1,[$r6+#0xc]
    9d34:	d5 23       	j8 9d7a <__sflush_r+0x126>
    9d36:	04 93 00 04 	lwi $r9,[$r6+#0x10]
    9d3a:	4e 92 ff be 	beqz $r9,9cb6 <__sflush_r+0x62>
    9d3e:	b4 e6       	lwi450 $r7,[$r6]
    9d40:	96 0f       	fexti33 $r0,#0x1
    9d42:	8a e9       	sub45 $r7,$r9
    9d44:	b7 26       	swi450 $r9,[$r6]
    9d46:	c8 03       	bnez38 $r0,9d4c <__sflush_r+0xf8>
    9d48:	a0 35       	lwi333 $r0,[$r6+#0x14]
    9d4a:	d5 02       	j8 9d4e <__sflush_r+0xfa>
    9d4c:	84 00       	movi55 $r0,#0x0
    9d4e:	a8 32       	swi333 $r0,[$r6+#0x8]
    9d50:	d5 12       	j8 9d74 <__sflush_r+0x120>
    9d52:	a4 36       	lhi333 $r0,[$r6+#0xc]
    9d54:	58 00 00 40 	ori $r0,$r0,#0x40
    9d58:	ac 36       	shi333 $r0,[$r6+#0xc]
    9d5a:	84 1f       	movi55 $r0,#-1
    9d5c:	d5 0f       	j8 9d7a <__sflush_r+0x126>
    9d5e:	04 43 00 09 	lwi $r4,[$r6+#0x24]
    9d62:	f0 01       	lwi37.sp $r0,[+#0x4]
    9d64:	a0 77       	lwi333 $r1,[$r6+#0x1c]
    9d66:	80 49       	mov55 $r2,$r9
    9d68:	80 67       	mov55 $r3,$r7
    9d6a:	dd 24       	jral5 $r4
    9d6c:	4e 07 ff f3 	blez $r0,9d52 <__sflush_r+0xfe>
    9d70:	89 20       	add45 $r9,$r0
    9d72:	8a e0       	sub45 $r7,$r0
    9d74:	4e 76 ff f5 	bgtz $r7,9d5e <__sflush_r+0x10a>
    9d78:	d5 9f       	j8 9cb6 <__sflush_r+0x62>
    9d7a:	fc c1       	pop25 $r10,#8    ! {$r6~$r10, $fp, $gp, $lp}

00009d7c <_fflush_r>:
    9d7c:	fc 01       	push25 $r6,#8    ! {$r6, $fp, $gp, $lp}
    9d7e:	3c 2c 0a d8 	lwi.gp $r2,[+#0x2b60]
    9d82:	b6 1f       	swi450 $r0,[$sp]
    9d84:	ca 05       	bnez38 $r2,9d8e <_fflush_r+0x12>
    9d86:	f1 81       	swi37.sp $r1,[+#0x4]
    9d88:	49 00 00 20 	jal 9dc8 <__sinit>
    9d8c:	f1 01       	lwi37.sp $r1,[+#0x4]
    9d8e:	22 00 80 06 	lhsi $r0,[$r1+#0xc]
    9d92:	c0 04       	beqz38 $r0,9d9a <_fflush_r+0x1e>
    9d94:	b4 1f       	lwi450 $r0,[$sp]
    9d96:	49 ff ff 5f 	jal 9c54 <__sflush_r>
    9d9a:	b6 1f       	swi450 $r0,[$sp]
    9d9c:	b4 1f       	lwi450 $r0,[$sp]
    9d9e:	fc 81       	pop25 $r6,#8    ! {$r6, $fp, $gp, $lp}

00009da0 <fflush>:
    9da0:	fc 01       	push25 $r6,#8    ! {$r6, $fp, $gp, $lp}
    9da2:	80 20       	mov55 $r1,$r0
    9da4:	c8 06       	bnez38 $r0,9db0 <fflush+0x10>
    9da6:	44 10 9d 7c 	movi $r1,#0x9d7c
    9daa:	49 00 00 89 	jal 9ebc <_fwalk_reent>
    9dae:	d5 04       	j8 9db6 <fflush+0x16>
    9db0:	84 00       	movi55 $r0,#0x0
    9db2:	49 ff ff e5 	jal 9d7c <_fflush_r>
    9db6:	f0 81       	swi37.sp $r0,[+#0x4]
    9db8:	f0 01       	lwi37.sp $r0,[+#0x4]
    9dba:	fc 81       	pop25 $r6,#8    ! {$r6, $fp, $gp, $lp}

00009dbc <_cleanup_r>:
    9dbc:	fc 00       	push25 $r6,#0    ! {$r6, $fp, $gp, $lp}
    9dbe:	44 10 ae 64 	movi $r1,#0xae64
    9dc2:	49 00 00 7d 	jal 9ebc <_fwalk_reent>
    9dc6:	fc 80       	pop25 $r6,#0    ! {$r6, $fp, $gp, $lp}

00009dc8 <__sinit>:
    9dc8:	fc 60       	push25 $r14,#0    ! {$r6~$r14, $fp, $gp, $lp}
    9dca:	3f c8 00 6c 	addi.gp $fp,#0x6c
    9dce:	3c 6c 0a d8 	lwi.gp $r6,[+#0x2b60]
    9dd2:	4e 63 00 68 	bnez $r6,9ea2 <__sinit+0xda>
    9dd6:	44 00 9d bc 	movi $r0,#0x9dbc
    9dda:	3c 0e 0a d7 	swi.gp $r0,[+#0x2b5c]
    9dde:	be 83       	swi37 $r6,[$fp+#0xc]
    9de0:	84 03       	movi55 $r0,#0x3
    9de2:	b8 84       	swi37 $r0,[$fp+#0x10]
    9de4:	bf 02       	lwi37 $r7,[$fp+#0x8]
    9de6:	bf 85       	swi37 $r7,[$fp+#0x14]
    9de8:	84 04       	movi55 $r0,#0x4
    9dea:	ac 3e       	shi333 $r0,[$r7+#0xc]
    9dec:	b6 c7       	swi450 $r6,[$r7]
    9dee:	a9 b9       	swi333 $r6,[$r7+#0x4]
    9df0:	a9 ba       	swi333 $r6,[$r7+#0x8]
    9df2:	14 63 80 19 	swi $r6,[$r7+#0x64]
    9df6:	ad bf       	shi333 $r6,[$r7+#0xe]
    9df8:	a9 bc       	swi333 $r6,[$r7+#0x10]
    9dfa:	a9 bd       	swi333 $r6,[$r7+#0x14]
    9dfc:	a9 be       	swi333 $r6,[$r7+#0x18]
    9dfe:	50 03 80 5c 	addi $r0,$r7,#0x5c
    9e02:	80 26       	mov55 $r1,$r6
    9e04:	84 48       	movi55 $r2,#0x8
    9e06:	49 00 00 db 	jal 9fbc <memset>
    9e0a:	44 80 a1 6c 	movi $r8,#0xa16c
    9e0e:	44 b0 a1 90 	movi $r11,#0xa190
    9e12:	44 a0 a1 c6 	movi $r10,#0xa1c6
    9e16:	44 90 a1 ec 	movi $r9,#0xa1ec
    9e1a:	a9 ff       	swi333 $r7,[$r7+#0x1c]
    9e1c:	14 83 80 08 	swi $r8,[$r7+#0x20]
    9e20:	14 b3 80 09 	swi $r11,[$r7+#0x24]
    9e24:	14 a3 80 0a 	swi $r10,[$r7+#0x28]
    9e28:	14 93 80 0b 	swi $r9,[$r7+#0x2c]
    9e2c:	bf 01       	lwi37 $r7,[$fp+#0x4]
    9e2e:	84 09       	movi55 $r0,#0x9
    9e30:	ac 3e       	shi333 $r0,[$r7+#0xc]
    9e32:	84 01       	movi55 $r0,#0x1
    9e34:	ac 3f       	shi333 $r0,[$r7+#0xe]
    9e36:	b6 c7       	swi450 $r6,[$r7]
    9e38:	a9 b9       	swi333 $r6,[$r7+#0x4]
    9e3a:	a9 ba       	swi333 $r6,[$r7+#0x8]
    9e3c:	14 63 80 19 	swi $r6,[$r7+#0x64]
    9e40:	a9 bc       	swi333 $r6,[$r7+#0x10]
    9e42:	a9 bd       	swi333 $r6,[$r7+#0x14]
    9e44:	a9 be       	swi333 $r6,[$r7+#0x18]
    9e46:	50 03 80 5c 	addi $r0,$r7,#0x5c
    9e4a:	80 26       	mov55 $r1,$r6
    9e4c:	84 48       	movi55 $r2,#0x8
    9e4e:	49 00 00 b7 	jal 9fbc <memset>
    9e52:	a9 ff       	swi333 $r7,[$r7+#0x1c]
    9e54:	14 83 80 08 	swi $r8,[$r7+#0x20]
    9e58:	14 b3 80 09 	swi $r11,[$r7+#0x24]
    9e5c:	14 a3 80 0a 	swi $r10,[$r7+#0x28]
    9e60:	14 93 80 0b 	swi $r9,[$r7+#0x2c]
    9e64:	bf 00       	lwi37 $r7,[$fp+#0x0]
    9e66:	fa 02       	movpi45 $r0,#0x12
    9e68:	ac 3e       	shi333 $r0,[$r7+#0xc]
    9e6a:	84 02       	movi55 $r0,#0x2
    9e6c:	ac 3f       	shi333 $r0,[$r7+#0xe]
    9e6e:	80 26       	mov55 $r1,$r6
    9e70:	b6 c7       	swi450 $r6,[$r7]
    9e72:	a9 b9       	swi333 $r6,[$r7+#0x4]
    9e74:	a9 ba       	swi333 $r6,[$r7+#0x8]
    9e76:	14 63 80 19 	swi $r6,[$r7+#0x64]
    9e7a:	a9 bc       	swi333 $r6,[$r7+#0x10]
    9e7c:	a9 bd       	swi333 $r6,[$r7+#0x14]
    9e7e:	a9 be       	swi333 $r6,[$r7+#0x18]
    9e80:	50 03 80 5c 	addi $r0,$r7,#0x5c
    9e84:	84 48       	movi55 $r2,#0x8
    9e86:	49 00 00 9b 	jal 9fbc <memset>
    9e8a:	84 01       	movi55 $r0,#0x1
    9e8c:	a9 ff       	swi333 $r7,[$r7+#0x1c]
    9e8e:	14 83 80 08 	swi $r8,[$r7+#0x20]
    9e92:	14 b3 80 09 	swi $r11,[$r7+#0x24]
    9e96:	14 a3 80 0a 	swi $r10,[$r7+#0x28]
    9e9a:	14 93 80 0b 	swi $r9,[$r7+#0x2c]
    9e9e:	3c 0e 0a d8 	swi.gp $r0,[+#0x2b60]
    9ea2:	fc e0       	pop25 $r14,#0    ! {$r6~$r14, $fp, $gp, $lp}

00009ea4 <__sfp_lock_acquire>:
    9ea4:	dd 9e       	ret5 $lp

00009ea6 <__sfp_lock_release>:
    9ea6:	dd 9e       	ret5 $lp

00009ea8 <fiprintf>:
    9ea8:	fc 01       	push25 $r6,#8    ! {$r6, $fp, $gp, $lp}
    9eaa:	b6 1f       	swi450 $r0,[$sp]
    9eac:	f1 81       	swi37.sp $r1,[+#0x4]
    9eae:	f2 01       	lwi37.sp $r2,[+#0x4]
    9eb0:	b4 3f       	lwi450 $r1,[$sp]
    9eb2:	b0 c6       	addri36.sp $r3,#0x18
    9eb4:	84 00       	movi55 $r0,#0x0
    9eb6:	49 00 02 a9 	jal a408 <_vfiprintf_r>
    9eba:	fc 81       	pop25 $r6,#8    ! {$r6, $fp, $gp, $lp}

00009ebc <_fwalk_reent>:
    9ebc:	fc 61       	push25 $r14,#8    ! {$r6~$r14, $fp, $gp, $lp}
    9ebe:	3e 68 00 78 	addi.gp $r6,#0x78
    9ec2:	f0 81       	swi37.sp $r0,[+#0x4]
    9ec4:	81 61       	mov55 $r11,$r1
    9ec6:	85 20       	movi55 $r9,#0x0
    9ec8:	c6 18       	beqz38 $r6,9ef8 <_fwalk_reent+0x3c>
    9eca:	a1 f2       	lwi333 $r7,[$r6+#0x8]
    9ecc:	04 a3 00 01 	lwi $r10,[$r6+#0x4]
    9ed0:	8f 41       	subi45 $r10,#0x1
    9ed2:	4e a5 00 11 	bltz $r10,9ef4 <_fwalk_reent+0x38>
    9ed6:	a4 3e       	lhi333 $r0,[$r7+#0xc]
    9ed8:	e6 02       	slti45 $r0,#0x2
    9eda:	e9 0a       	bnezs8 9eee <_fwalk_reent+0x32>
    9edc:	22 03 80 07 	lhsi $r0,[$r7+#0xe]
    9ee0:	5a 07 ff 07 	beqc $r0,#-1,9eee <_fwalk_reent+0x32>
    9ee4:	f0 01       	lwi37.sp $r0,[+#0x4]
    9ee6:	80 27       	mov55 $r1,$r7
    9ee8:	dd 2b       	jral5 $r11
    9eea:	40 94 80 04 	or $r9,$r9,$r0
    9eee:	50 73 80 68 	addi $r7,$r7,#0x68
    9ef2:	d5 ef       	j8 9ed0 <_fwalk_reent+0x14>
    9ef4:	b4 c6       	lwi450 $r6,[$r6]
    9ef6:	d5 e9       	j8 9ec8 <_fwalk_reent+0xc>
    9ef8:	80 09       	mov55 $r0,$r9
    9efa:	fc e1       	pop25 $r14,#8    ! {$r6~$r14, $fp, $gp, $lp}

00009efc <malloc>:
    9efc:	fc 01       	push25 $r6,#8    ! {$r6, $fp, $gp, $lp}
    9efe:	f0 81       	swi37.sp $r0,[+#0x4]
    9f00:	f1 01       	lwi37.sp $r1,[+#0x4]
    9f02:	84 00       	movi55 $r0,#0x0
    9f04:	49 00 00 d2 	jal a0a8 <_malloc_r>
    9f08:	fc 81       	pop25 $r6,#8    ! {$r6, $fp, $gp, $lp}

00009f0a <free>:
    9f0a:	fc 01       	push25 $r6,#8    ! {$r6, $fp, $gp, $lp}
    9f0c:	f0 81       	swi37.sp $r0,[+#0x4]
    9f0e:	f1 01       	lwi37.sp $r1,[+#0x4]
    9f10:	84 00       	movi55 $r0,#0x0
    9f12:	49 00 00 8f 	jal a030 <_free_r>
    9f16:	fc 81       	pop25 $r6,#8    ! {$r6, $fp, $gp, $lp}

00009f18 <memcmp>:
    9f18:	40 51 08 09 	srli $r5,$r2,#0x2
    9f1c:	c5 0f       	beqz38 $r5,9f3a <memcmp+0x22>
    9f1e:	95 6a       	slli333 $r5,$r5,#0x2
    9f20:	99 68       	add333 $r5,$r5,$r0
    9f22:	96 8f       	fexti33 $r2,#0x1
    9f24:	3a 30 0c 04 	lmw.bim $r3,[$r0],$r3,#0x0    ! {$r3}
    9f28:	3a 40 90 04 	lmw.bim $r4,[$r1],$r4,#0x0    ! {$r4}
    9f2c:	4c 32 40 04 	bne $r3,$r4,9f34 <memcmp+0x1c>
    9f30:	d8 fa       	bnes38 $r0,9f24 <memcmp+0xc>
    9f32:	d5 04       	j8 9f3a <memcmp+0x22>
    9f34:	8e 04       	subi45 $r0,#0x4
    9f36:	8e 24       	subi45 $r1,#0x4
    9f38:	8c 44       	addi45 $r2,#0x4
    9f3a:	99 42       	add333 $r5,$r0,$r2
    9f3c:	d0 09       	beqs38 $r0,9f4e <memcmp+0x36>
    9f3e:	08 30 00 01 	lbi.bi $r3,[$r0],#0x1
    9f42:	08 40 80 01 	lbi.bi $r4,[$r1],#0x1
    9f46:	4c 32 3f fb 	beq $r3,$r4,9f3c <memcmp+0x24>
    9f4a:	9a 1c       	sub333 $r0,$r3,$r4
    9f4c:	dd 9e       	ret5 $lp
    9f4e:	84 00       	movi55 $r0,#0x0
    9f50:	dd 9e       	ret5 $lp
    9f52:	92 00       	nop16

00009f54 <memcpy>:
    9f54:	80 60       	mov55 $r3,$r0
    9f56:	e6 44       	slti45 $r2,#0x4
    9f58:	e9 28       	bnezs8 9fa8 <memcpy+0x54>
    9f5a:	54 41 80 03 	andi $r4,$r3,#0x3
    9f5e:	54 50 80 03 	andi $r5,$r1,#0x3
    9f62:	c5 0b       	beqz38 $r5,9f78 <memcpy+0x24>
    9f64:	52 52 80 04 	subri $r5,$r5,#0x4
    9f68:	9a 95       	sub333 $r2,$r2,$r5
    9f6a:	99 69       	add333 $r5,$r5,$r1
    9f6c:	08 40 80 01 	lbi.bi $r4,[$r1],#0x1
    9f70:	18 41 80 01 	sbi.bi $r4,[$r3],#0x1
    9f74:	4c 12 ff fc 	bne $r1,$r5,9f6c <memcpy+0x18>
    9f78:	40 51 14 09 	srli $r5,$r2,#0x5
    9f7c:	c5 0a       	beqz38 $r5,9f90 <memcpy+0x3c>
    9f7e:	95 6d       	slli333 $r5,$r5,#0x5
    9f80:	99 69       	add333 $r5,$r5,$r1
    9f82:	96 a7       	fexti33 $r2,#0x4
    9f84:	3b 00 dc 04 	lmw.bim $r16,[$r1],$r23,#0x0    ! {$r16~$r23}
    9f88:	3b 01 dc 24 	smw.bim $r16,[$r3],$r23,#0x0    ! {$r16~$r23}
    9f8c:	4c 12 ff fc 	bne $r1,$r5,9f84 <memcpy+0x30>
    9f90:	40 51 08 09 	srli $r5,$r2,#0x2
    9f94:	c5 0a       	beqz38 $r5,9fa8 <memcpy+0x54>
    9f96:	95 6a       	slli333 $r5,$r5,#0x2
    9f98:	99 69       	add333 $r5,$r5,$r1
    9f9a:	96 8f       	fexti33 $r2,#0x1
    9f9c:	3a 40 90 04 	lmw.bim $r4,[$r1],$r4,#0x0    ! {$r4}
    9fa0:	3a 41 90 24 	smw.bim $r4,[$r3],$r4,#0x0    ! {$r4}
    9fa4:	4c 12 ff fc 	bne $r1,$r5,9f9c <memcpy+0x48>
    9fa8:	c2 08       	beqz38 $r2,9fb8 <memcpy+0x64>
    9faa:	99 4a       	add333 $r5,$r1,$r2
    9fac:	08 40 80 01 	lbi.bi $r4,[$r1],#0x1
    9fb0:	18 41 80 01 	sbi.bi $r4,[$r3],#0x1
    9fb4:	4c 12 ff fc 	bne $r1,$r5,9fac <memcpy+0x58>
    9fb8:	dd 9e       	ret5 $lp
    9fba:	92 00       	nop16

00009fbc <memset>:
    9fbc:	80 60       	mov55 $r3,$r0
    9fbe:	e6 44       	slti45 $r2,#0x4
    9fc0:	e9 30       	bnezs8 a020 <memset+0x64>
    9fc2:	54 51 80 03 	andi $r5,$r3,#0x3
    9fc6:	c5 09       	beqz38 $r5,9fd8 <memset+0x1c>
    9fc8:	52 52 80 04 	subri $r5,$r5,#0x4
    9fcc:	9a 95       	sub333 $r2,$r2,$r5
    9fce:	99 68       	add333 $r5,$r5,$r0
    9fd0:	18 11 80 01 	sbi.bi $r1,[$r3],#0x1
    9fd4:	4c 32 ff fe 	bne $r3,$r5,9fd0 <memset+0x14>
    9fd8:	96 48       	zeb33 $r1,$r1
    9fda:	40 40 a0 08 	slli $r4,$r1,#0x8
    9fde:	fe 67       	or33 $r1,$r4
    9fe0:	40 40 c0 08 	slli $r4,$r1,#0x10
    9fe4:	fe 67       	or33 $r1,$r4
    9fe6:	40 51 14 09 	srli $r5,$r2,#0x5
    9fea:	4e 52 00 11 	beqz $r5,a00c <memset+0x50>
    9fee:	95 6d       	slli333 $r5,$r5,#0x5
    9ff0:	99 6b       	add333 $r5,$r5,$r3
    9ff2:	96 a7       	fexti33 $r2,#0x4
    9ff4:	82 01       	mov55 $r16,$r1
    9ff6:	82 21       	mov55 $r17,$r1
    9ff8:	82 41       	mov55 $r18,$r1
    9ffa:	82 61       	mov55 $r19,$r1
    9ffc:	82 81       	mov55 $r20,$r1
    9ffe:	82 a1       	mov55 $r21,$r1
    a000:	82 c1       	mov55 $r22,$r1
    a002:	82 e1       	mov55 $r23,$r1
    a004:	3b 01 dc 24 	smw.bim $r16,[$r3],$r23,#0x0    ! {$r16~$r23}
    a008:	4c 32 ff fe 	bne $r3,$r5,a004 <memset+0x48>
    a00c:	40 51 08 09 	srli $r5,$r2,#0x2
    a010:	c5 08       	beqz38 $r5,a020 <memset+0x64>
    a012:	95 6a       	slli333 $r5,$r5,#0x2
    a014:	99 6b       	add333 $r5,$r5,$r3
    a016:	96 8f       	fexti33 $r2,#0x1
    a018:	3a 11 84 24 	smw.bim $r1,[$r3],$r1,#0x0    ! {$r1}
    a01c:	4c 32 ff fe 	bne $r3,$r5,a018 <memset+0x5c>
    a020:	c2 06       	beqz38 $r2,a02c <memset+0x70>
    a022:	99 5a       	add333 $r5,$r3,$r2
    a024:	18 11 80 01 	sbi.bi $r1,[$r3],#0x1
    a028:	4c 32 ff fe 	bne $r3,$r5,a024 <memset+0x68>
    a02c:	dd 9e       	ret5 $lp
    a02e:	92 00       	nop16

0000a030 <_free_r>:
    a030:	c1 3b       	beqz38 $r1,a0a6 <_free_r+0x76>
    a032:	9e 0c       	subi333 $r0,$r1,#0x4
    a034:	04 10 ff ff 	lwi $r1,[$r1+#-4]
    a038:	4e 14 00 03 	bgez $r1,a03e <_free_r+0xe>
    a03c:	88 01       	add45 $r0,$r1
    a03e:	3c 1c 0a d6 	lwi.gp $r1,[+#0x2b58]
    a042:	c1 0a       	beqz38 $r1,a056 <_free_r+0x26>
    a044:	e2 01       	slt45 $r0,$r1
    a046:	e8 11       	beqzs8 a068 <_free_r+0x38>
    a048:	b4 40       	lwi450 $r2,[$r0]
    a04a:	99 42       	add333 $r5,$r0,$r2
    a04c:	d9 05       	bnes38 $r1,a056 <_free_r+0x26>
    a04e:	b4 25       	lwi450 $r1,[$r5]
    a050:	88 22       	add45 $r1,$r2
    a052:	b6 20       	swi450 $r1,[$r0]
    a054:	a0 69       	lwi333 $r1,[$r5+#0x4]
    a056:	a8 41       	swi333 $r1,[$r0+#0x4]
    a058:	46 10 01 02 	sethi $r1,#0x102
    a05c:	3c 0e 0a d6 	swi.gp $r0,[+#0x2b58]
    a060:	dd 9e       	ret5 $lp
    a062:	e2 02       	slt45 $r0,$r2
    a064:	e9 04       	bnezs8 a06c <_free_r+0x3c>
    a066:	80 22       	mov55 $r1,$r2
    a068:	a0 89       	lwi333 $r2,[$r1+#0x4]
    a06a:	ca fc       	bnez38 $r2,a062 <_free_r+0x32>
    a06c:	b4 61       	lwi450 $r3,[$r1]
    a06e:	99 4b       	add333 $r5,$r1,$r3
    a070:	d8 0c       	bnes38 $r0,a088 <_free_r+0x58>
    a072:	b4 00       	lwi450 $r0,[$r0]
    a074:	80 a1       	mov55 $r5,$r1
    a076:	88 03       	add45 $r0,$r3
    a078:	38 02 80 0e 	sw.bi $r0,[$r5],$r0<<#0x0
    a07c:	da 15       	bnes38 $r2,a0a6 <_free_r+0x76>
    a07e:	b4 62       	lwi450 $r3,[$r2]
    a080:	88 03       	add45 $r0,$r3
    a082:	b6 01       	swi450 $r0,[$r1]
    a084:	a0 11       	lwi333 $r0,[$r2+#0x4]
    a086:	d5 0f       	j8 a0a4 <_free_r+0x74>
    a088:	e2 05       	slt45 $r0,$r5
    a08a:	e8 05       	beqzs8 a094 <_free_r+0x64>
    a08c:	84 0c       	movi55 $r0,#0xc
    a08e:	3c 0e 0a d4 	swi.gp $r0,[+#0x2b50]
    a092:	dd 9e       	ret5 $lp
    a094:	b4 80       	lwi450 $r4,[$r0]
    a096:	99 44       	add333 $r5,$r0,$r4
    a098:	da 05       	bnes38 $r2,a0a2 <_free_r+0x72>
    a09a:	b4 62       	lwi450 $r3,[$r2]
    a09c:	a0 91       	lwi333 $r2,[$r2+#0x4]
    a09e:	88 64       	add45 $r3,$r4
    a0a0:	b6 60       	swi450 $r3,[$r0]
    a0a2:	a8 81       	swi333 $r2,[$r0+#0x4]
    a0a4:	a8 09       	swi333 $r0,[$r1+#0x4]
    a0a6:	dd 9e       	ret5 $lp

0000a0a8 <_malloc_r>:
    a0a8:	fc 21       	push25 $r8,#8    ! {$r6~$r8, $fp, $gp, $lp}
    a0aa:	3f c8 2b 50 	addi.gp $fp,#0x2b50
    a0ae:	9d 8b       	addi333 $r6,$r1,#0x3
    a0b0:	66 63 00 03 	bitci $r6,$r6,#0x3
    a0b4:	8c c8       	addi45 $r6,#0x8
    a0b6:	e6 cc       	slti45 $r6,#0xc
    a0b8:	e8 03       	beqzs8 a0be <_malloc_r+0x16>
    a0ba:	84 cc       	movi55 $r6,#0xc
    a0bc:	d5 07       	j8 a0ca <_malloc_r+0x22>
    a0be:	4e 64 00 06 	bgez $r6,a0ca <_malloc_r+0x22>
    a0c2:	84 0c       	movi55 $r0,#0xc
    a0c4:	b8 80       	swi37 $r0,[$fp+#0x0]
    a0c6:	84 00       	movi55 $r0,#0x0
    a0c8:	d5 42       	j8 a14c <_malloc_r+0xa4>
    a0ca:	e2 c1       	slt45 $r6,$r1
    a0cc:	e9 fb       	bnezs8 a0c2 <_malloc_r+0x1a>
    a0ce:	bd 02       	lwi37 $r5,[$fp+#0x8]
    a0d0:	80 25       	mov55 $r1,$r5
    a0d2:	c1 0c       	beqz38 $r1,a0ea <_malloc_r+0x42>
    a0d4:	b4 41       	lwi450 $r2,[$r1]
    a0d6:	8a 46       	sub45 $r2,$r6
    a0d8:	4e 25 00 19 	bltz $r2,a10a <_malloc_r+0x62>
    a0dc:	e6 4c       	slti45 $r2,#0xc
    a0de:	e9 0e       	bnezs8 a0fa <_malloc_r+0x52>
    a0e0:	80 a1       	mov55 $r5,$r1
    a0e2:	38 22 88 0e 	sw.bi $r2,[$r5],$r2<<#0x0
    a0e6:	b6 c5       	swi450 $r6,[$r5]
    a0e8:	cd 28       	bnez38 $r5,a138 <_malloc_r+0x90>
    a0ea:	f0 81       	swi37.sp $r0,[+#0x4]
    a0ec:	b9 01       	lwi37 $r1,[$fp+#0x4]
    a0ee:	c9 11       	bnez38 $r1,a110 <_malloc_r+0x68>
    a0f0:	f0 01       	lwi37.sp $r0,[+#0x4]
    a0f2:	49 00 00 2e 	jal a14e <_sbrk_r>
    a0f6:	b8 81       	swi37 $r0,[$fp+#0x4]
    a0f8:	d5 0c       	j8 a110 <_malloc_r+0x68>
    a0fa:	d9 04       	bnes38 $r1,a102 <_malloc_r+0x5a>
    a0fc:	a0 29       	lwi333 $r0,[$r5+#0x4]
    a0fe:	b8 82       	swi37 $r0,[$fp+#0x8]
    a100:	d5 1c       	j8 a138 <_malloc_r+0x90>
    a102:	a0 09       	lwi333 $r0,[$r1+#0x4]
    a104:	a8 29       	swi333 $r0,[$r5+#0x4]
    a106:	80 a1       	mov55 $r5,$r1
    a108:	d5 18       	j8 a138 <_malloc_r+0x90>
    a10a:	80 a1       	mov55 $r5,$r1
    a10c:	a0 49       	lwi333 $r1,[$r1+#0x4]
    a10e:	d5 e2       	j8 a0d2 <_malloc_r+0x2a>
    a110:	f0 01       	lwi37.sp $r0,[+#0x4]
    a112:	80 26       	mov55 $r1,$r6
    a114:	49 00 00 1d 	jal a14e <_sbrk_r>
    a118:	80 a0       	mov55 $r5,$r0
    a11a:	5a 07 ff d4 	beqc $r0,#-1,a0c2 <_malloc_r+0x1a>
    a11e:	9d c3       	addi333 $r7,$r0,#0x3
    a120:	66 73 80 03 	bitci $r7,$r7,#0x3
    a124:	4c 70 00 09 	beq $r7,$r0,a136 <_malloc_r+0x8e>
    a128:	f0 01       	lwi37.sp $r0,[+#0x4]
    a12a:	9a 7d       	sub333 $r1,$r7,$r5
    a12c:	49 00 00 11 	jal a14e <_sbrk_r>
    a130:	5a 07 ff c9 	beqc $r0,#-1,a0c2 <_malloc_r+0x1a>
    a134:	80 a7       	mov55 $r5,$r7
    a136:	b6 c5       	swi450 $r6,[$r5]
    a138:	50 02 80 0b 	addi $r0,$r5,#0xb
    a13c:	9c 6c       	addi333 $r1,$r5,#0x4
    a13e:	66 00 00 07 	bitci $r0,$r0,#0x7
    a142:	9a 41       	sub333 $r1,$r0,$r1
    a144:	c1 04       	beqz38 $r1,a14c <_malloc_r+0xa4>
    a146:	fe 8a       	neg33 $r2,$r1
    a148:	38 22 84 0a 	sw $r2,[$r5+($r1<<#0x0)]
    a14c:	fc a1       	pop25 $r8,#8    ! {$r6~$r8, $fp, $gp, $lp}

0000a14e <_sbrk_r>:
    a14e:	fc 00       	push25 $r6,#0    ! {$r6, $fp, $gp, $lp}
    a150:	84 00       	movi55 $r0,#0x0
    a152:	3c 0e 00 23 	swi.gp $r0,[+#0x8c]
    a156:	80 01       	mov55 $r0,$r1
    a158:	49 00 09 9c 	jal b490 <_sbrk>
    a15c:	5a 0f ff 07 	bnec $r0,#-1,a16a <_sbrk_r+0x1c>
    a160:	3c 1c 00 23 	lwi.gp $r1,[+#0x8c]
    a164:	c1 03       	beqz38 $r1,a16a <_sbrk_r+0x1c>
    a166:	3c 1e 0a d4 	swi.gp $r1,[+#0x2b50]
    a16a:	fc 80       	pop25 $r6,#0    ! {$r6, $fp, $gp, $lp}

0000a16c <__sread>:
    a16c:	fc 00       	push25 $r6,#0    ! {$r6, $fp, $gp, $lp}
    a16e:	80 c1       	mov55 $r6,$r1
    a170:	22 10 80 07 	lhsi $r1,[$r1+#0xe]
    a174:	49 00 09 32 	jal b3d8 <_read_r>
    a178:	4e 05 00 07 	bltz $r0,a186 <__sread+0x1a>
    a17c:	83 86       	mov55 $fp,$r6
    a17e:	b9 14       	lwi37 $r1,[$fp+#0x50]
    a180:	88 20       	add45 $r1,$r0
    a182:	b9 94       	swi37 $r1,[$fp+#0x50]
    a184:	fc 80       	pop25 $r6,#0    ! {$r6, $fp, $gp, $lp}
    a186:	a4 76       	lhi333 $r1,[$r6+#0xc]
    a188:	66 10 90 00 	bitci $r1,$r1,#0x1000
    a18c:	ac 76       	shi333 $r1,[$r6+#0xc]
    a18e:	fc 80       	pop25 $r6,#0    ! {$r6, $fp, $gp, $lp}

0000a190 <__swrite>:
    a190:	fc 02       	push25 $r6,#16    ! {$r6, $fp, $gp, $lp}
    a192:	80 c1       	mov55 $r6,$r1
    a194:	a4 4e       	lhi333 $r1,[$r1+#0xc]
    a196:	f0 81       	swi37.sp $r0,[+#0x4]
    a198:	54 10 81 00 	andi $r1,$r1,#0x100
    a19c:	f2 82       	swi37.sp $r2,[+#0x8]
    a19e:	f3 83       	swi37.sp $r3,[+#0xc]
    a1a0:	c1 07       	beqz38 $r1,a1ae <__swrite+0x1e>
    a1a2:	22 13 00 07 	lhsi $r1,[$r6+#0xe]
    a1a6:	84 40       	movi55 $r2,#0x0
    a1a8:	84 62       	movi55 $r3,#0x2
    a1aa:	49 00 07 f3 	jal b190 <_lseek_r>
    a1ae:	a4 36       	lhi333 $r0,[$r6+#0xc]
    a1b0:	22 13 00 07 	lhsi $r1,[$r6+#0xe]
    a1b4:	66 00 10 00 	bitci $r0,$r0,#0x1000
    a1b8:	ac 36       	shi333 $r0,[$r6+#0xc]
    a1ba:	f2 02       	lwi37.sp $r2,[+#0x8]
    a1bc:	f0 01       	lwi37.sp $r0,[+#0x4]
    a1be:	f3 03       	lwi37.sp $r3,[+#0xc]
    a1c0:	49 00 05 d6 	jal ad6c <_write_r>
    a1c4:	fc 82       	pop25 $r6,#16    ! {$r6, $fp, $gp, $lp}

0000a1c6 <__sseek>:
    a1c6:	fc 00       	push25 $r6,#0    ! {$r6, $fp, $gp, $lp}
    a1c8:	80 c1       	mov55 $r6,$r1
    a1ca:	22 10 80 07 	lhsi $r1,[$r1+#0xe]
    a1ce:	49 00 07 e1 	jal b190 <_lseek_r>
    a1d2:	a4 b6       	lhi333 $r2,[$r6+#0xc]
    a1d4:	5a 0f ff 06 	bnec $r0,#-1,a1e0 <__sseek+0x1a>
    a1d8:	66 21 10 00 	bitci $r2,$r2,#0x1000
    a1dc:	ac b6       	shi333 $r2,[$r6+#0xc]
    a1de:	fc 80       	pop25 $r6,#0    ! {$r6, $fp, $gp, $lp}
    a1e0:	58 21 10 00 	ori $r2,$r2,#0x1000
    a1e4:	ac b6       	shi333 $r2,[$r6+#0xc]
    a1e6:	14 03 00 14 	swi $r0,[$r6+#0x50]
    a1ea:	fc 80       	pop25 $r6,#0    ! {$r6, $fp, $gp, $lp}

0000a1ec <__sclose>:
    a1ec:	fc 00       	push25 $r6,#0    ! {$r6, $fp, $gp, $lp}
    a1ee:	22 10 80 07 	lhsi $r1,[$r1+#0xe]
    a1f2:	49 00 06 2a 	jal ae46 <_close_r>
    a1f6:	fc 80       	pop25 $r6,#0    ! {$r6, $fp, $gp, $lp}

0000a1f8 <strchr>:
    a1f8:	28 50 00 01 	lbsi.bi $r5,[$r0],#0x1
    a1fc:	d1 04       	beqs38 $r1,a204 <strchr+0xc>
    a1fe:	cd fd       	bnez38 $r5,a1f8 <strchr>
    a200:	80 05       	mov55 $r0,$r5
    a202:	dd 9e       	ret5 $lp
    a204:	9e 01       	subi333 $r0,$r0,#0x1
    a206:	dd 9e       	ret5 $lp

0000a208 <strcmp>:
    a208:	3a 20 08 06 	lmwzb.bm $r2,[$r0],$r2,#0x0    ! {$r2}
    a20c:	3a 30 8c 06 	lmwzb.bm $r3,[$r1],$r3,#0x0    ! {$r3}
    a210:	42 41 0c 17 	ffzmism $r4,$r2,$r3
    a214:	c4 fa       	beqz38 $r4,a208 <strcmp>
    a216:	38 20 10 00 	lb $r2,[$r0+($r4<<#0x0)]
    a21a:	38 30 90 00 	lb $r3,[$r1+($r4<<#0x0)]
    a21e:	9a 13       	sub333 $r0,$r2,$r3
    a220:	dd 9e       	ret5 $lp
    a222:	92 00       	nop16

0000a224 <strcpy>:
    a224:	80 60       	mov55 $r3,$r0
    a226:	3a 40 90 06 	lmwzb.bm $r4,[$r1],$r4,#0x0    ! {$r4}
    a22a:	3a 41 90 26 	smwzb.bm $r4,[$r3],$r4,#0x0    ! {$r4}
    a22e:	42 22 10 17 	ffzmism $r2,$r4,$r4
    a232:	c2 fa       	beqz38 $r2,a226 <strcpy+0x2>
    a234:	dd 9e       	ret5 $lp
    a236:	92 00       	nop16

0000a238 <strcspn>:
    a238:	80 40       	mov55 $r2,$r0
    a23a:	28 41 00 01 	lbsi.bi $r4,[$r2],#0x1
    a23e:	c4 06       	beqz38 $r4,a24a <strcspn+0x12>
    a240:	80 61       	mov55 $r3,$r1
    a242:	28 51 80 01 	lbsi.bi $r5,[$r3],#0x1
    a246:	c5 fa       	beqz38 $r5,a23a <strcspn+0x2>
    a248:	dc fd       	bnes38 $r4,a242 <strcspn+0xa>
    a24a:	9e 91       	subi333 $r2,$r2,#0x1
    a24c:	9a 10       	sub333 $r0,$r2,$r0
    a24e:	dd 9e       	ret5 $lp

0000a250 <strlen>:
    a250:	9c 81       	addi333 $r2,$r0,#0x1
    a252:	08 50 00 01 	lbi.bi $r5,[$r0],#0x1
    a256:	cd fe       	bnez38 $r5,a252 <strlen+0x2>
    a258:	9a 02       	sub333 $r0,$r0,$r2
    a25a:	dd 9e       	ret5 $lp

0000a25c <strspn>:
    a25c:	80 40       	mov55 $r2,$r0
    a25e:	28 41 00 01 	lbsi.bi $r4,[$r2],#0x1
    a262:	c4 07       	beqz38 $r4,a270 <strspn+0x14>
    a264:	80 61       	mov55 $r3,$r1
    a266:	28 51 80 01 	lbsi.bi $r5,[$r3],#0x1
    a26a:	c5 03       	beqz38 $r5,a270 <strspn+0x14>
    a26c:	dc fd       	bnes38 $r4,a266 <strspn+0xa>
    a26e:	d5 f8       	j8 a25e <strspn+0x2>
    a270:	9e 91       	subi333 $r2,$r2,#0x1
    a272:	9a 10       	sub333 $r0,$r2,$r0
    a274:	dd 9e       	ret5 $lp
    a276:	92 00       	nop16

0000a278 <strtol>:
    a278:	fc 00       	push25 $r6,#0    ! {$r6, $fp, $gp, $lp}
    a27a:	84 60       	movi55 $r3,#0x0
    a27c:	49 00 00 03 	jal a282 <strtol_common>
    a280:	fc 80       	pop25 $r6,#0    ! {$r6, $fp, $gp, $lp}

0000a282 <strtol_common>:
    a282:	fc 61       	push25 $r14,#8    ! {$r6~$r14, $fp, $gp, $lp}
    a284:	36 3f 80 00 	fsdi $fd3,[$sp+#0x0]
    a288:	81 c0       	mov55 $r14,$r0
    a28a:	81 01       	mov55 $r8,$r1
    a28c:	81 22       	mov55 $r9,$r2
    a28e:	83 83       	mov55 $fp,$r3
    a290:	81 40       	mov55 $r10,$r0
    a292:	80 ea       	mov55 $r7,$r10
    a294:	08 63 80 01 	lbi.bi $r6,[$r7],#0x1
    a298:	80 06       	mov55 $r0,$r6
    a29a:	49 00 08 92 	jal b3be <nds_isspace>
    a29e:	c0 03       	beqz38 $r0,a2a4 <strtol_common+0x22>
    a2a0:	81 47       	mov55 $r10,$r7
    a2a2:	d5 f8       	j8 a292 <strtol_common+0x10>
    a2a4:	5a 68 2d 08 	bnec $r6,#0x2d,a2b4 <strtol_common+0x32>
    a2a8:	50 75 00 02 	addi $r7,$r10,#0x2
    a2ac:	00 65 00 01 	lbi $r6,[$r10+#0x1]
    a2b0:	85 61       	movi55 $r11,#0x1
    a2b2:	d5 08       	j8 a2c2 <strtol_common+0x40>
    a2b4:	5a 68 2b 06 	bnec $r6,#0x2b,a2c0 <strtol_common+0x3e>
    a2b8:	50 75 00 02 	addi $r7,$r10,#0x2
    a2bc:	00 65 00 01 	lbi $r6,[$r10+#0x1]
    a2c0:	81 60       	mov55 $r11,$r0
    a2c2:	4e 92 00 05 	beqz $r9,a2cc <strtol_common+0x4a>
    a2c6:	5a 98 10 0d 	bnec $r9,#0x10,a2e0 <strtol_common+0x5e>
    a2ca:	d5 6f       	j8 a3a8 <strtol_common+0x126>
    a2cc:	5a 68 30 6c 	bnec $r6,#0x30,a3a4 <strtol_common+0x122>
    a2d0:	a6 38       	lbi333 $r0,[$r7+#0x0]
    a2d2:	54 00 00 df 	andi $r0,$r0,#0xdf
    a2d6:	5a 08 58 61 	bnec $r0,#0x58,a398 <strtol_common+0x116>
    a2da:	a7 b9       	lbi333 $r6,[$r7+#0x1]
    a2dc:	fb 20       	movpi45 $r9,#0x10
    a2de:	8c e2       	addi45 $r7,#0x2
    a2e0:	85 5f       	movi55 $r10,#-1
    a2e2:	4f c3 00 0b 	bnez $fp,a2f8 <strtol_common+0x76>
    a2e6:	4e b3 00 07 	bnez $r11,a2f4 <strtol_common+0x72>
    a2ea:	46 a7 ff ff 	sethi $r10,#0x7ffff
    a2ee:	50 a5 0f ff 	addi $r10,$r10,#0xfff
    a2f2:	d5 03       	j8 a2f8 <strtol_common+0x76>
    a2f4:	46 a8 00 00 	sethi $r10,#0x80000
    a2f8:	40 a5 24 17 	divr $r10,$r0,$r10,$r9
    a2fc:	6a 03 00 09 	fmtsr $r0,$fs6
    a300:	85 80       	movi55 $r12,#0x0
    a302:	81 ac       	mov55 $r13,$r12
    a304:	80 06       	mov55 $r0,$r6
    a306:	49 00 08 57 	jal b3b4 <nds_isdigit>
    a30a:	c0 04       	beqz38 $r0,a312 <strtol_common+0x90>
    a30c:	50 63 7f d0 	addi $r6,$r6,#-48
    a310:	d5 0f       	j8 a32e <strtol_common+0xac>
    a312:	80 06       	mov55 $r0,$r6
    a314:	49 00 08 49 	jal b3a6 <nds_isalpha>
    a318:	c0 20       	beqz38 $r0,a358 <strtol_common+0xd6>
    a31a:	80 06       	mov55 $r0,$r6
    a31c:	49 00 08 59 	jal b3ce <nds_isupper>
    a320:	c8 04       	bnez38 $r0,a328 <strtol_common+0xa6>
    a322:	44 00 00 57 	movi $r0,#0x57
    a326:	d5 03       	j8 a32c <strtol_common+0xaa>
    a328:	44 00 00 37 	movi $r0,#0x37
    a32c:	8a c0       	sub45 $r6,$r0
    a32e:	e0 c9       	slts45 $r6,$r9
    a330:	e8 14       	beqzs8 a358 <strtol_common+0xd6>
    a332:	5a c7 ff 10 	beqc $r12,#-1,a352 <strtol_common+0xd0>
    a336:	e3 4d       	slt45 $r10,$r13
    a338:	e9 0c       	bnezs8 a350 <strtol_common+0xce>
    a33a:	4c d5 40 06 	bne $r13,$r10,a346 <strtol_common+0xc4>
    a33e:	6a 03 00 01 	fmfsr $r0,$fs6
    a342:	e0 06       	slts45 $r0,$r6
    a344:	e9 06       	bnezs8 a350 <strtol_common+0xce>
    a346:	42 66 a4 73 	maddr32 $r6,$r13,$r9
    a34a:	85 81       	movi55 $r12,#0x1
    a34c:	81 a6       	mov55 $r13,$r6
    a34e:	d5 02       	j8 a352 <strtol_common+0xd0>
    a350:	85 9f       	movi55 $r12,#-1
    a352:	08 63 80 01 	lbi.bi $r6,[$r7],#0x1
    a356:	d5 d7       	j8 a304 <strtol_common+0x82>
    a358:	80 4d       	mov55 $r2,$r13
    a35a:	4e c4 00 12 	bgez $r12,a37e <strtol_common+0xfc>
    a35e:	84 5f       	movi55 $r2,#-1
    a360:	4f c3 00 0b 	bnez $fp,a376 <strtol_common+0xf4>
    a364:	4e b3 00 07 	bnez $r11,a372 <strtol_common+0xf0>
    a368:	46 27 ff ff 	sethi $r2,#0x7ffff
    a36c:	50 21 0f ff 	addi $r2,$r2,#0xfff
    a370:	d5 03       	j8 a376 <strtol_common+0xf4>
    a372:	46 28 00 00 	sethi $r2,#0x80000
    a376:	fa 12       	movpi45 $r0,#0x22
    a378:	3c 0e 0a d4 	swi.gp $r0,[+#0x2b50]
    a37c:	d5 05       	j8 a386 <strtol_common+0x104>
    a37e:	4e b2 00 04 	beqz $r11,a386 <strtol_common+0x104>
    a382:	52 26 80 00 	subri $r2,$r13,#0x0
    a386:	4e 82 00 14 	beqz $r8,a3ae <strtol_common+0x12c>
    a38a:	4e c2 00 04 	beqz $r12,a392 <strtol_common+0x110>
    a38e:	8e e1       	subi45 $r7,#0x1
    a390:	d5 02       	j8 a394 <strtol_common+0x112>
    a392:	80 ee       	mov55 $r7,$r14
    a394:	b6 e8       	swi450 $r7,[$r8]
    a396:	d5 0c       	j8 a3ae <strtol_common+0x12c>
    a398:	44 60 00 30 	movi $r6,#0x30
    a39c:	4e 93 ff a2 	bnez $r9,a2e0 <strtol_common+0x5e>
    a3a0:	85 28       	movi55 $r9,#0x8
    a3a2:	d5 9f       	j8 a2e0 <strtol_common+0x5e>
    a3a4:	85 2a       	movi55 $r9,#0xa
    a3a6:	d5 9d       	j8 a2e0 <strtol_common+0x5e>
    a3a8:	5a 68 30 9c 	bnec $r6,#0x30,a2e0 <strtol_common+0x5e>
    a3ac:	d5 92       	j8 a2d0 <strtol_common+0x4e>
    a3ae:	80 02       	mov55 $r0,$r2
    a3b0:	34 3f 80 00 	fldi $fd3,[$sp+#0x0]
    a3b4:	fc e1       	pop25 $r14,#8    ! {$r6~$r14, $fp, $gp, $lp}

0000a3b6 <strtoul>:
    a3b6:	fc 00       	push25 $r6,#0    ! {$r6, $fp, $gp, $lp}
    a3b8:	84 61       	movi55 $r3,#0x1
    a3ba:	49 ff ff 64 	jal a282 <strtol_common>
    a3be:	fc 80       	pop25 $r6,#0    ! {$r6, $fp, $gp, $lp}

0000a3c0 <__sprint_r>:
    a3c0:	fc 01       	push25 $r6,#8    ! {$r6, $fp, $gp, $lp}
    a3c2:	a1 12       	lwi333 $r4,[$r2+#0x8]
    a3c4:	cc 04       	bnez38 $r4,a3cc <__sprint_r+0xc>
    a3c6:	a9 11       	swi333 $r4,[$r2+#0x4]
    a3c8:	f4 81       	swi37.sp $r4,[+#0x4]
    a3ca:	d5 08       	j8 a3da <__sprint_r+0x1a>
    a3cc:	80 c2       	mov55 $r6,$r2
    a3ce:	49 00 05 8e 	jal aeea <__sfvwrite_r>
    a3d2:	84 20       	movi55 $r1,#0x0
    a3d4:	a8 72       	swi333 $r1,[$r6+#0x8]
    a3d6:	a8 71       	swi333 $r1,[$r6+#0x4]
    a3d8:	f0 81       	swi37.sp $r0,[+#0x4]
    a3da:	f0 01       	lwi37.sp $r0,[+#0x4]
    a3dc:	fc 81       	pop25 $r6,#8    ! {$r6, $fp, $gp, $lp}
    a3de:	00 00 30 31 	lbi $r0,[$r0+#0x3031]
    a3e2:	32 33 34 35 	cpswi.bi cp1,$cpr3,[$r6],#0x10d4
    a3e6:	36 37 38 39 	cpsdi.bi cp1,$cpr3,[$r14],#-7964
    a3ea:	41 42 43 44 	or_slli $r20,$r4,$r16,#0x1a
    a3ee:	45 46 00 00 	movi $r20,#0x60000
    a3f2:	00 00 30 31 	lbi $r0,[$r0+#0x3031]
    a3f6:	32 33 34 35 	cpswi.bi cp1,$cpr3,[$r6],#0x10d4
    a3fa:	36 37 38 39 	cpsdi.bi cp1,$cpr3,[$r14],#-7964
    a3fe:	61 62 63 64 	amtbsl2.l $d1,$r2,$r6,$r0,$r1,[$i0],[$i4],$m1,$m6
    a402:	65 66 00 00 	*unknown*
	...

0000a408 <_vfiprintf_r>:
    a408:	fc 76       	push25 $r14,#176    ! {$r6~$r14, $fp, $gp, $lp}
    a40a:	36 3f 80 22 	fsdi $fd3,[$sp+#0x88]
    a40e:	36 4f 80 24 	fsdi $fd4,[$sp+#0x90]
    a412:	36 5f 80 26 	fsdi $fd5,[$sp+#0x98]
    a416:	36 6f 80 28 	fsdi $fd6,[$sp+#0xa0]
    a41a:	36 7f 80 2a 	fsdi $fd7,[$sp+#0xa8]
    a41e:	81 61       	mov55 $r11,$r1
    a420:	3c 1c 0a d8 	lwi.gp $r1,[+#0x2b60]
    a424:	b6 1f       	swi450 $r0,[$sp]
    a426:	81 82       	mov55 $r12,$r2
    a428:	80 c3       	mov55 $r6,$r3
    a42a:	c9 03       	bnez38 $r1,a430 <_vfiprintf_r+0x28>
    a42c:	49 ff fc ce 	jal 9dc8 <__sinit>
    a430:	02 05 80 06 	lhi $r0,[$r11+#0xc]
    a434:	96 1e       	bmski33 $r0,#0x3
    a436:	c0 0b       	beqz38 $r0,a44c <_vfiprintf_r+0x44>
    a438:	04 05 80 04 	lwi $r0,[$r11+#0x10]
    a43c:	c0 08       	beqz38 $r0,a44c <_vfiprintf_r+0x44>
    a43e:	02 05 80 06 	lhi $r0,[$r11+#0xc]
    a442:	54 00 00 1a 	andi $r0,$r0,#0x1a
    a446:	5a 08 0a 17 	bnec $r0,#0xa,a474 <_vfiprintf_r+0x6c>
    a44a:	d5 09       	j8 a45c <_vfiprintf_r+0x54>
    a44c:	b4 1f       	lwi450 $r0,[$sp]
    a44e:	80 2b       	mov55 $r1,$r11
    a450:	49 00 04 9f 	jal ad8e <__swsetup_r>
    a454:	c0 f5       	beqz38 $r0,a43e <_vfiprintf_r+0x36>
    a456:	84 1f       	movi55 $r0,#-1
    a458:	48 00 04 39 	j acca <_vfiprintf_r+0x8c2>
    a45c:	22 05 80 07 	lhsi $r0,[$r11+#0xe]
    a460:	4e 05 00 0a 	bltz $r0,a474 <_vfiprintf_r+0x6c>
    a464:	b4 1f       	lwi450 $r0,[$sp]
    a466:	80 2b       	mov55 $r1,$r11
    a468:	80 4c       	mov55 $r2,$r12
    a46a:	80 66       	mov55 $r3,$r6
    a46c:	49 00 04 3a 	jal ace0 <__sbprintf>
    a470:	48 00 04 2d 	j acca <_vfiprintf_r+0x8c2>
    a474:	84 00       	movi55 $r0,#0x0
    a476:	f0 87       	swi37.sp $r0,[+#0x1c]
    a478:	f0 86       	swi37.sp $r0,[+#0x18]
    a47a:	6a 05 00 09 	fmtsr $r0,$fs10
    a47e:	80 e0       	mov55 $r7,$r0
    a480:	84 0a       	movi55 $r0,#0xa
    a482:	6a 03 00 09 	fmtsr $r0,$fs6
    a486:	44 00 ad 5c 	movi $r0,#0xad5c
    a48a:	6a 04 00 09 	fmtsr $r0,$fs8
    a48e:	6a 03 80 09 	fmtsr $r0,$fs7
    a492:	50 8f 80 48 	addi $r8,$sp,#0x48
    a496:	14 8f 80 05 	swi $r8,[$sp+#0x14]
    a49a:	80 88       	mov55 $r4,$r8
    a49c:	80 0c       	mov55 $r0,$r12
    a49e:	81 20       	mov55 $r9,$r0
    a4a0:	28 10 00 01 	lbsi.bi $r1,[$r0],#0x1
    a4a4:	c9 06       	bnez38 $r1,a4b0 <_vfiprintf_r+0xa8>
    a4a6:	40 a4 b0 01 	sub $r10,$r9,$r12
    a4aa:	4e a3 00 06 	bnez $r10,a4b6 <_vfiprintf_r+0xae>
    a4ae:	d5 1b       	j8 a4e4 <_vfiprintf_r+0xdc>
    a4b0:	5a 18 25 f7 	bnec $r1,#0x25,a49e <_vfiprintf_r+0x96>
    a4b4:	d5 f9       	j8 a4a6 <_vfiprintf_r+0x9e>
    a4b6:	f0 07       	lwi37.sp $r0,[+#0x1c]
    a4b8:	14 c2 00 00 	swi $r12,[$r4+#0x0]
    a4bc:	88 0a       	add45 $r0,$r10
    a4be:	f0 87       	swi37.sp $r0,[+#0x1c]
    a4c0:	f0 06       	lwi37.sp $r0,[+#0x18]
    a4c2:	14 a2 00 01 	swi $r10,[$r4+#0x4]
    a4c6:	8c 01       	addi45 $r0,#0x1
    a4c8:	e4 08       	sltsi45 $r0,#0x8
    a4ca:	f0 86       	swi37.sp $r0,[+#0x18]
    a4cc:	e8 03       	beqzs8 a4d2 <_vfiprintf_r+0xca>
    a4ce:	8c 88       	addi45 $r4,#0x8
    a4d0:	d5 09       	j8 a4e2 <_vfiprintf_r+0xda>
    a4d2:	b4 1f       	lwi450 $r0,[$sp]
    a4d4:	80 2b       	mov55 $r1,$r11
    a4d6:	b0 85       	addri36.sp $r2,#0x14
    a4d8:	49 ff ff 74 	jal a3c0 <__sprint_r>
    a4dc:	4e 03 03 ea 	bnez $r0,acb0 <_vfiprintf_r+0x8a8>
    a4e0:	80 88       	mov55 $r4,$r8
    a4e2:	88 ea       	add45 $r7,$r10
    a4e4:	20 04 80 00 	lbsi $r0,[$r9+#0x0]
    a4e8:	4e 02 03 dd 	beqz $r0,aca2 <_vfiprintf_r+0x89a>
    a4ec:	84 60       	movi55 $r3,#0x0
    a4ee:	84 00       	movi55 $r0,#0x0
    a4f0:	85 df       	movi55 $r14,#-1
    a4f2:	50 14 80 01 	addi $r1,$r9,#0x1
    a4f6:	10 0f 80 0f 	sbi $r0,[$sp+#0xf]
    a4fa:	81 a3       	mov55 $r13,$r3
    a4fc:	83 83       	mov55 $fp,$r3
    a4fe:	82 0e       	mov55 $r16,$r14
    a500:	50 c0 80 01 	addi $r12,$r1,#0x1
    a504:	20 20 80 00 	lbsi $r2,[$r1+#0x0]
    a508:	5a 28 58 04 	bnec $r2,#0x58,a510 <_vfiprintf_r+0x108>
    a50c:	48 00 00 9d 	j a646 <_vfiprintf_r+0x23e>
    a510:	5e f1 00 59 	sltsi $r15,$r2,#0x59
    a514:	e8 45       	beqzs8 a59e <_vfiprintf_r+0x196>
    a516:	5a 28 2e 04 	bnec $r2,#0x2e,a51e <_vfiprintf_r+0x116>
    a51a:	48 00 00 b1 	j a67c <_vfiprintf_r+0x274>
    a51e:	5e f1 00 2f 	sltsi $r15,$r2,#0x2f
    a522:	e8 1e       	beqzs8 a55e <_vfiprintf_r+0x156>
    a524:	5a 28 2a 04 	bnec $r2,#0x2a,a52c <_vfiprintf_r+0x124>
    a528:	48 00 00 9b 	j a65e <_vfiprintf_r+0x256>
    a52c:	5e f1 00 2b 	sltsi $r15,$r2,#0x2b
    a530:	e8 0d       	beqzs8 a54a <_vfiprintf_r+0x142>
    a532:	5a 28 20 04 	bnec $r2,#0x20,a53a <_vfiprintf_r+0x132>
    a536:	48 00 00 90 	j a656 <_vfiprintf_r+0x24e>
    a53a:	5a 20 23 04 	beqc $r2,#0x23,a542 <_vfiprintf_r+0x13a>
    a53e:	48 00 02 4c 	j a9d6 <_vfiprintf_r+0x5ce>
    a542:	59 ce 00 01 	ori $fp,$fp,#0x1
    a546:	80 2c       	mov55 $r1,$r12
    a548:	d5 dc       	j8 a500 <_vfiprintf_r+0xf8>
    a54a:	5a 28 2b 04 	bnec $r2,#0x2b,a552 <_vfiprintf_r+0x14a>
    a54e:	80 62       	mov55 $r3,$r2
    a550:	d5 fb       	j8 a546 <_vfiprintf_r+0x13e>
    a552:	5a 28 2d 04 	bnec $r2,#0x2d,a55a <_vfiprintf_r+0x152>
    a556:	48 00 00 8f 	j a674 <_vfiprintf_r+0x26c>
    a55a:	48 00 02 3e 	j a9d6 <_vfiprintf_r+0x5ce>
    a55e:	5e f1 00 3a 	sltsi $r15,$r2,#0x3a
    a562:	e8 0c       	beqzs8 a57a <_vfiprintf_r+0x172>
    a564:	5e f1 00 31 	sltsi $r15,$r2,#0x31
    a568:	4e f2 00 ad 	beqz $r15,a6c2 <_vfiprintf_r+0x2ba>
    a56c:	5a 20 30 04 	beqc $r2,#0x30,a574 <_vfiprintf_r+0x16c>
    a570:	48 00 02 33 	j a9d6 <_vfiprintf_r+0x5ce>
    a574:	59 ce 00 80 	ori $fp,$fp,#0x80
    a578:	d5 e7       	j8 a546 <_vfiprintf_r+0x13e>
    a57a:	5a 28 4f 04 	bnec $r2,#0x4f,a582 <_vfiprintf_r+0x17a>
    a57e:	48 00 01 16 	j a7aa <_vfiprintf_r+0x3a2>
    a582:	5a 28 55 04 	bnec $r2,#0x55,a58a <_vfiprintf_r+0x182>
    a586:	48 00 01 58 	j a836 <_vfiprintf_r+0x42e>
    a58a:	5a 20 44 04 	beqc $r2,#0x44,a592 <_vfiprintf_r+0x18a>
    a58e:	48 00 02 24 	j a9d6 <_vfiprintf_r+0x5ce>
    a592:	10 3f 80 0f 	sbi $r3,[$sp+#0xf]
    a596:	59 ce 00 10 	ori $fp,$fp,#0x10
    a59a:	48 00 00 c1 	j a71c <_vfiprintf_r+0x314>
    a59e:	5a 28 6e 04 	bnec $r2,#0x6e,a5a6 <_vfiprintf_r+0x19e>
    a5a2:	48 00 00 ea 	j a776 <_vfiprintf_r+0x36e>
    a5a6:	5e f1 00 6f 	sltsi $r15,$r2,#0x6f
    a5aa:	e8 18       	beqzs8 a5da <_vfiprintf_r+0x1d2>
    a5ac:	5a 28 68 04 	bnec $r2,#0x68,a5b4 <_vfiprintf_r+0x1ac>
    a5b0:	48 00 00 99 	j a6e2 <_vfiprintf_r+0x2da>
    a5b4:	5e f1 00 69 	sltsi $r15,$r2,#0x69
    a5b8:	e8 09       	beqzs8 a5ca <_vfiprintf_r+0x1c2>
    a5ba:	5a 28 63 04 	bnec $r2,#0x63,a5c2 <_vfiprintf_r+0x1ba>
    a5be:	48 00 00 a5 	j a708 <_vfiprintf_r+0x300>
    a5c2:	5a 20 64 3f 	beqc $r2,#0x64,a640 <_vfiprintf_r+0x238>
    a5c6:	48 00 02 08 	j a9d6 <_vfiprintf_r+0x5ce>
    a5ca:	5a 20 69 3b 	beqc $r2,#0x69,a640 <_vfiprintf_r+0x238>
    a5ce:	5a 28 6c 04 	bnec $r2,#0x6c,a5d6 <_vfiprintf_r+0x1ce>
    a5d2:	48 00 00 8c 	j a6ea <_vfiprintf_r+0x2e2>
    a5d6:	48 00 02 00 	j a9d6 <_vfiprintf_r+0x5ce>
    a5da:	5a 28 71 04 	bnec $r2,#0x71,a5e2 <_vfiprintf_r+0x1da>
    a5de:	48 00 00 91 	j a700 <_vfiprintf_r+0x2f8>
    a5e2:	5e f1 00 72 	sltsi $r15,$r2,#0x72
    a5e6:	e8 1f       	beqzs8 a624 <_vfiprintf_r+0x21c>
    a5e8:	5a 28 6f 04 	bnec $r2,#0x6f,a5f0 <_vfiprintf_r+0x1e8>
    a5ec:	48 00 00 e1 	j a7ae <_vfiprintf_r+0x3a6>
    a5f0:	5a 20 70 04 	beqc $r2,#0x70,a5f8 <_vfiprintf_r+0x1f0>
    a5f4:	48 00 01 f1 	j a9d6 <_vfiprintf_r+0x5ce>
    a5f8:	44 00 00 30 	movi $r0,#0x30
    a5fc:	10 0f 80 10 	sbi $r0,[$sp+#0x10]
    a600:	44 00 00 78 	movi $r0,#0x78
    a604:	10 0f 80 11 	sbi $r0,[$sp+#0x11]
    a608:	44 00 a3 f4 	movi $r0,#0xa3f4
    a60c:	50 a3 00 04 	addi $r10,$r6,#0x4
    a610:	b5 26       	lwi450 $r9,[$r6]
    a612:	59 ce 00 02 	ori $fp,$fp,#0x2
    a616:	84 c0       	movi55 $r6,#0x0
    a618:	6a e4 80 09 	fmtsr $r14,$fs9
    a61c:	6a 05 00 09 	fmtsr $r0,$fs10
    a620:	48 00 01 5d 	j a8da <_vfiprintf_r+0x4d2>
    a624:	5a 28 75 04 	bnec $r2,#0x75,a62c <_vfiprintf_r+0x224>
    a628:	48 00 01 09 	j a83a <_vfiprintf_r+0x432>
    a62c:	5a 28 78 04 	bnec $r2,#0x78,a634 <_vfiprintf_r+0x22c>
    a630:	48 00 01 24 	j a878 <_vfiprintf_r+0x470>
    a634:	5a 20 73 04 	beqc $r2,#0x73,a63c <_vfiprintf_r+0x234>
    a638:	48 00 01 cf 	j a9d6 <_vfiprintf_r+0x5ce>
    a63c:	48 00 00 d9 	j a7ee <_vfiprintf_r+0x3e6>
    a640:	10 3f 80 0f 	sbi $r3,[$sp+#0xf]
    a644:	d5 6c       	j8 a71c <_vfiprintf_r+0x314>
    a646:	10 3f 80 0f 	sbi $r3,[$sp+#0xf]
    a64a:	6a e4 80 09 	fmtsr $r14,$fs9
    a64e:	44 00 a3 e0 	movi $r0,#0xa3e0
    a652:	48 00 01 19 	j a884 <_vfiprintf_r+0x47c>
    a656:	40 31 0c 1a 	cmovz $r3,$r2,$r3
    a65a:	48 ff ff 76 	j a546 <_vfiprintf_r+0x13e>
    a65e:	04 d3 00 00 	lwi $r13,[$r6+#0x0]
    a662:	9c 34       	addi333 $r0,$r6,#0x4
    a664:	4e d5 00 05 	bltz $r13,a66e <_vfiprintf_r+0x266>
    a668:	80 c0       	mov55 $r6,$r0
    a66a:	48 ff ff 6e 	j a546 <_vfiprintf_r+0x13e>
    a66e:	52 d6 80 00 	subri $r13,$r13,#0x0
    a672:	80 c0       	mov55 $r6,$r0
    a674:	59 ce 00 04 	ori $fp,$fp,#0x4
    a678:	48 ff ff 67 	j a546 <_vfiprintf_r+0x13e>
    a67c:	20 26 00 00 	lbsi $r2,[$r12+#0x0]
    a680:	50 06 00 01 	addi $r0,$r12,#0x1
    a684:	5a 20 2a 04 	beqc $r2,#0x2a,a68c <_vfiprintf_r+0x284>
    a688:	84 20       	movi55 $r1,#0x0
    a68a:	d5 0b       	j8 a6a0 <_vfiprintf_r+0x298>
    a68c:	04 e3 00 00 	lwi $r14,[$r6+#0x0]
    a690:	81 80       	mov55 $r12,$r0
    a692:	9c 34       	addi333 $r0,$r6,#0x4
    a694:	4e e4 ff ea 	bgez $r14,a668 <_vfiprintf_r+0x260>
    a698:	80 c0       	mov55 $r6,$r0
    a69a:	85 df       	movi55 $r14,#-1
    a69c:	48 ff ff 55 	j a546 <_vfiprintf_r+0x13e>
    a6a0:	50 51 7f d0 	addi $r5,$r2,#-48
    a6a4:	e6 aa       	slti45 $r5,#0xa
    a6a6:	e8 09       	beqzs8 a6b8 <_vfiprintf_r+0x2b0>
    a6a8:	6a 23 00 01 	fmfsr $r2,$fs6
    a6ac:	42 50 88 73 	maddr32 $r5,$r1,$r2
    a6b0:	28 20 00 01 	lbsi.bi $r2,[$r0],#0x1
    a6b4:	80 25       	mov55 $r1,$r5
    a6b6:	d5 f5       	j8 a6a0 <_vfiprintf_r+0x298>
    a6b8:	42 e0 c0 00 	max $r14,$r1,$r16
    a6bc:	81 80       	mov55 $r12,$r0
    a6be:	48 ff ff 25 	j a508 <_vfiprintf_r+0x100>
    a6c2:	85 a0       	movi55 $r13,#0x0
    a6c4:	6a 03 00 01 	fmfsr $r0,$fs6
    a6c8:	50 21 7f d0 	addi $r2,$r2,#-48
    a6cc:	42 26 80 73 	maddr32 $r2,$r13,$r0
    a6d0:	81 a2       	mov55 $r13,$r2
    a6d2:	28 26 00 01 	lbsi.bi $r2,[$r12],#0x1
    a6d6:	50 01 7f d0 	addi $r0,$r2,#-48
    a6da:	e6 0a       	slti45 $r0,#0xa
    a6dc:	e9 f4       	bnezs8 a6c4 <_vfiprintf_r+0x2bc>
    a6de:	48 ff ff 15 	j a508 <_vfiprintf_r+0x100>
    a6e2:	59 ce 00 40 	ori $fp,$fp,#0x40
    a6e6:	48 ff ff 30 	j a546 <_vfiprintf_r+0x13e>
    a6ea:	20 06 00 00 	lbsi $r0,[$r12+#0x0]
    a6ee:	5a 08 6c 05 	bnec $r0,#0x6c,a6f8 <_vfiprintf_r+0x2f0>
    a6f2:	50 c6 00 01 	addi $r12,$r12,#0x1
    a6f6:	d5 05       	j8 a700 <_vfiprintf_r+0x2f8>
    a6f8:	59 ce 00 10 	ori $fp,$fp,#0x10
    a6fc:	48 ff ff 25 	j a546 <_vfiprintf_r+0x13e>
    a700:	59 ce 00 20 	ori $fp,$fp,#0x20
    a704:	48 ff ff 21 	j a546 <_vfiprintf_r+0x13e>
    a708:	b4 06       	lwi450 $r0,[$r6]
    a70a:	10 0f 80 20 	sbi $r0,[$sp+#0x20]
    a70e:	84 00       	movi55 $r0,#0x0
    a710:	50 a3 00 04 	addi $r10,$r6,#0x4
    a714:	10 0f 80 0f 	sbi $r0,[$sp+#0xf]
    a718:	48 00 01 69 	j a9ea <_vfiprintf_r+0x5e2>
    a71c:	54 0e 00 20 	andi $r0,$fp,#0x20
    a720:	6a e4 80 09 	fmtsr $r14,$fs9
    a724:	c0 09       	beqz38 $r0,a736 <_vfiprintf_r+0x32e>
    a726:	9c f7       	addi333 $r3,$r6,#0x7
    a728:	66 31 80 07 	bitci $r3,$r3,#0x7
    a72c:	50 a1 80 08 	addi $r10,$r3,#0x8
    a730:	b5 23       	lwi450 $r9,[$r3]
    a732:	a1 99       	lwi333 $r6,[$r3+#0x4]
    a734:	d5 13       	j8 a75a <_vfiprintf_r+0x352>
    a736:	54 0e 00 10 	andi $r0,$fp,#0x10
    a73a:	9c b4       	addi333 $r2,$r6,#0x4
    a73c:	c0 04       	beqz38 $r0,a744 <_vfiprintf_r+0x33c>
    a73e:	81 42       	mov55 $r10,$r2
    a740:	b5 26       	lwi450 $r9,[$r6]
    a742:	d5 0a       	j8 a756 <_vfiprintf_r+0x34e>
    a744:	54 1e 00 40 	andi $r1,$fp,#0x40
    a748:	b4 06       	lwi450 $r0,[$r6]
    a74a:	81 42       	mov55 $r10,$r2
    a74c:	c1 04       	beqz38 $r1,a754 <_vfiprintf_r+0x34c>
    a74e:	40 90 00 11 	seh $r9,$r0
    a752:	d5 02       	j8 a756 <_vfiprintf_r+0x34e>
    a754:	81 20       	mov55 $r9,$r0
    a756:	40 64 fc 0a 	srai $r6,$r9,#0x1f
    a75a:	4e 64 00 c5 	bgez $r6,a8e4 <_vfiprintf_r+0x4dc>
    a75e:	52 04 80 00 	subri $r0,$r9,#0x0
    a762:	84 20       	movi55 $r1,#0x0
    a764:	e2 20       	slt45 $r1,$r0
    a766:	ff b2       	neg33 $r6,$r6
    a768:	81 20       	mov55 $r9,$r0
    a76a:	fa 1d       	movpi45 $r0,#0x2d
    a76c:	8a cf       	sub45 $r6,$r15
    a76e:	10 0f 80 0f 	sbi $r0,[$sp+#0xf]
    a772:	48 00 00 b9 	j a8e4 <_vfiprintf_r+0x4dc>
    a776:	54 1e 00 20 	andi $r1,$fp,#0x20
    a77a:	10 3f 80 0f 	sbi $r3,[$sp+#0xf]
    a77e:	9c 34       	addi333 $r0,$r6,#0x4
    a780:	c1 07       	beqz38 $r1,a78e <_vfiprintf_r+0x386>
    a782:	b4 26       	lwi450 $r1,[$r6]
    a784:	40 23 fc 0a 	srai $r2,$r7,#0x1f
    a788:	b6 e1       	swi450 $r7,[$r1]
    a78a:	a8 89       	swi333 $r2,[$r1+#0x4]
    a78c:	d5 0c       	j8 a7a4 <_vfiprintf_r+0x39c>
    a78e:	54 1e 00 10 	andi $r1,$fp,#0x10
    a792:	c9 07       	bnez38 $r1,a7a0 <_vfiprintf_r+0x398>
    a794:	54 1e 00 40 	andi $r1,$fp,#0x40
    a798:	c1 04       	beqz38 $r1,a7a0 <_vfiprintf_r+0x398>
    a79a:	b4 26       	lwi450 $r1,[$r6]
    a79c:	ad c8       	shi333 $r7,[$r1+#0x0]
    a79e:	d5 03       	j8 a7a4 <_vfiprintf_r+0x39c>
    a7a0:	b4 26       	lwi450 $r1,[$r6]
    a7a2:	b6 e1       	swi450 $r7,[$r1]
    a7a4:	80 c0       	mov55 $r6,$r0
    a7a6:	48 ff fe 7b 	j a49c <_vfiprintf_r+0x94>
    a7aa:	59 ce 00 10 	ori $fp,$fp,#0x10
    a7ae:	54 3e 00 20 	andi $r3,$fp,#0x20
    a7b2:	6a e4 80 09 	fmtsr $r14,$fs9
    a7b6:	c3 0b       	beqz38 $r3,a7cc <_vfiprintf_r+0x3c4>
    a7b8:	9c f7       	addi333 $r3,$r6,#0x7
    a7ba:	66 31 80 07 	bitci $r3,$r3,#0x7
    a7be:	50 a1 80 08 	addi $r10,$r3,#0x8
    a7c2:	b5 23       	lwi450 $r9,[$r3]
    a7c4:	a1 99       	lwi333 $r6,[$r3+#0x4]
    a7c6:	84 60       	movi55 $r3,#0x0
    a7c8:	48 00 00 8a 	j a8dc <_vfiprintf_r+0x4d4>
    a7cc:	54 1e 00 10 	andi $r1,$fp,#0x10
    a7d0:	9c 34       	addi333 $r0,$r6,#0x4
    a7d2:	c1 03       	beqz38 $r1,a7d8 <_vfiprintf_r+0x3d0>
    a7d4:	81 40       	mov55 $r10,$r0
    a7d6:	d5 09       	j8 a7e8 <_vfiprintf_r+0x3e0>
    a7d8:	54 3e 00 40 	andi $r3,$fp,#0x40
    a7dc:	81 40       	mov55 $r10,$r0
    a7de:	c3 05       	beqz38 $r3,a7e8 <_vfiprintf_r+0x3e0>
    a7e0:	02 93 00 00 	lhi $r9,[$r6+#0x0]
    a7e4:	80 c1       	mov55 $r6,$r1
    a7e6:	d5 f0       	j8 a7c6 <_vfiprintf_r+0x3be>
    a7e8:	b5 26       	lwi450 $r9,[$r6]
    a7ea:	80 c3       	mov55 $r6,$r3
    a7ec:	d5 ed       	j8 a7c6 <_vfiprintf_r+0x3be>
    a7ee:	30 b3 00 00 	flsi $fs11,[$r6+#0x0]
    a7f2:	84 00       	movi55 $r0,#0x0
    a7f4:	10 0f 80 0f 	sbi $r0,[$sp+#0xf]
    a7f8:	50 a3 00 04 	addi $r10,$r6,#0x4
    a7fc:	f4 81       	swi37.sp $r4,[+#0x4]
    a7fe:	6a 05 80 01 	fmfsr $r0,$fs11
    a802:	4e e5 00 11 	bltz $r14,a824 <_vfiprintf_r+0x41c>
    a806:	84 20       	movi55 $r1,#0x0
    a808:	80 4e       	mov55 $r2,$r14
    a80a:	49 00 05 45 	jal b294 <memchr>
    a80e:	f4 01       	lwi37.sp $r4,[+#0x4]
    a810:	4e 02 00 f5 	beqz $r0,a9fa <_vfiprintf_r+0x5f2>
    a814:	6a 15 80 01 	fmfsr $r1,$fs11
    a818:	9b 81       	sub333 $r6,$r0,$r1
    a81a:	42 e3 38 01 	min $r14,$r6,$r14
    a81e:	84 00       	movi55 $r0,#0x0
    a820:	48 00 00 ed 	j a9fa <_vfiprintf_r+0x5f2>
    a824:	49 ff fd 16 	jal a250 <strlen>
    a828:	81 c0       	mov55 $r14,$r0
    a82a:	84 00       	movi55 $r0,#0x0
    a82c:	6a 04 80 09 	fmtsr $r0,$fs9
    a830:	f4 01       	lwi37.sp $r4,[+#0x4]
    a832:	48 00 00 e6 	j a9fe <_vfiprintf_r+0x5f6>
    a836:	59 ce 00 10 	ori $fp,$fp,#0x10
    a83a:	54 3e 00 20 	andi $r3,$fp,#0x20
    a83e:	6a e4 80 09 	fmtsr $r14,$fs9
    a842:	c3 09       	beqz38 $r3,a854 <_vfiprintf_r+0x44c>
    a844:	9c f7       	addi333 $r3,$r6,#0x7
    a846:	66 31 80 07 	bitci $r3,$r3,#0x7
    a84a:	50 a1 80 08 	addi $r10,$r3,#0x8
    a84e:	b5 23       	lwi450 $r9,[$r3]
    a850:	a1 99       	lwi333 $r6,[$r3+#0x4]
    a852:	d5 0e       	j8 a86e <_vfiprintf_r+0x466>
    a854:	54 1e 00 10 	andi $r1,$fp,#0x10
    a858:	9c 34       	addi333 $r0,$r6,#0x4
    a85a:	c1 03       	beqz38 $r1,a860 <_vfiprintf_r+0x458>
    a85c:	81 40       	mov55 $r10,$r0
    a85e:	d5 0a       	j8 a872 <_vfiprintf_r+0x46a>
    a860:	54 3e 00 40 	andi $r3,$fp,#0x40
    a864:	81 40       	mov55 $r10,$r0
    a866:	c3 06       	beqz38 $r3,a872 <_vfiprintf_r+0x46a>
    a868:	02 93 00 00 	lhi $r9,[$r6+#0x0]
    a86c:	80 c1       	mov55 $r6,$r1
    a86e:	84 61       	movi55 $r3,#0x1
    a870:	d5 36       	j8 a8dc <_vfiprintf_r+0x4d4>
    a872:	b5 26       	lwi450 $r9,[$r6]
    a874:	80 c3       	mov55 $r6,$r3
    a876:	d5 fc       	j8 a86e <_vfiprintf_r+0x466>
    a878:	6a e4 80 09 	fmtsr $r14,$fs9
    a87c:	10 3f 80 0f 	sbi $r3,[$sp+#0xf]
    a880:	44 00 a3 f4 	movi $r0,#0xa3f4
    a884:	54 3e 00 20 	andi $r3,$fp,#0x20
    a888:	6a 05 00 09 	fmtsr $r0,$fs10
    a88c:	c3 09       	beqz38 $r3,a89e <_vfiprintf_r+0x496>
    a88e:	9c f7       	addi333 $r3,$r6,#0x7
    a890:	66 31 80 07 	bitci $r3,$r3,#0x7
    a894:	50 a1 80 08 	addi $r10,$r3,#0x8
    a898:	b5 23       	lwi450 $r9,[$r3]
    a89a:	a1 99       	lwi333 $r6,[$r3+#0x4]
    a89c:	d5 11       	j8 a8be <_vfiprintf_r+0x4b6>
    a89e:	54 1e 00 10 	andi $r1,$fp,#0x10
    a8a2:	9c 34       	addi333 $r0,$r6,#0x4
    a8a4:	c1 03       	beqz38 $r1,a8aa <_vfiprintf_r+0x4a2>
    a8a6:	81 40       	mov55 $r10,$r0
    a8a8:	d5 09       	j8 a8ba <_vfiprintf_r+0x4b2>
    a8aa:	54 3e 00 40 	andi $r3,$fp,#0x40
    a8ae:	81 40       	mov55 $r10,$r0
    a8b0:	c3 05       	beqz38 $r3,a8ba <_vfiprintf_r+0x4b2>
    a8b2:	02 93 00 00 	lhi $r9,[$r6+#0x0]
    a8b6:	80 c1       	mov55 $r6,$r1
    a8b8:	d5 03       	j8 a8be <_vfiprintf_r+0x4b6>
    a8ba:	b5 26       	lwi450 $r9,[$r6]
    a8bc:	80 c3       	mov55 $r6,$r3
    a8be:	54 0e 00 01 	andi $r0,$fp,#0x1
    a8c2:	c0 0c       	beqz38 $r0,a8da <_vfiprintf_r+0x4d2>
    a8c4:	40 04 98 04 	or $r0,$r9,$r6
    a8c8:	c0 09       	beqz38 $r0,a8da <_vfiprintf_r+0x4d2>
    a8ca:	44 00 00 30 	movi $r0,#0x30
    a8ce:	10 0f 80 10 	sbi $r0,[$sp+#0x10]
    a8d2:	10 2f 80 11 	sbi $r2,[$sp+#0x11]
    a8d6:	59 ce 00 02 	ori $fp,$fp,#0x2
    a8da:	84 62       	movi55 $r3,#0x2
    a8dc:	84 00       	movi55 $r0,#0x0
    a8de:	10 0f 80 0f 	sbi $r0,[$sp+#0xf]
    a8e2:	d5 02       	j8 a8e6 <_vfiprintf_r+0x4de>
    a8e4:	84 61       	movi55 $r3,#0x1
    a8e6:	4e e5 00 04 	bltz $r14,a8ee <_vfiprintf_r+0x4e6>
    a8ea:	67 ce 00 80 	bitci $fp,$fp,#0x80
    a8ee:	40 04 98 04 	or $r0,$r9,$r6
    a8f2:	c8 04       	bnez38 $r0,a8fa <_vfiprintf_r+0x4f2>
    a8f4:	4e e3 01 e5 	bnez $r14,acbe <_vfiprintf_r+0x8b6>
    a8f8:	d5 5b       	j8 a9ae <_vfiprintf_r+0x5a6>
    a8fa:	5a 30 01 23 	beqc $r3,#0x1,a940 <_vfiprintf_r+0x538>
    a8fe:	5a 30 02 44 	beqc $r3,#0x2,a986 <_vfiprintf_r+0x57e>
    a902:	50 2f 80 47 	addi $r2,$sp,#0x47
    a906:	54 14 80 07 	andi $r1,$r9,#0x7
    a90a:	93 23       	srli45 $r9,#0x3
    a90c:	40 94 9b a4 	or_slli $r9,$r9,$r6,#0x1d
    a910:	50 10 80 30 	addi $r1,$r1,#0x30
    a914:	92 c3       	srli45 $r6,#0x3
    a916:	96 4a       	seb33 $r1,$r1
    a918:	40 04 98 04 	or $r0,$r9,$r6
    a91c:	80 62       	mov55 $r3,$r2
    a91e:	18 11 7f ff 	sbi.bi $r1,[$r2],#-1
    a922:	c8 f2       	bnez38 $r0,a906 <_vfiprintf_r+0x4fe>
    a924:	54 0e 00 01 	andi $r0,$fp,#0x1
    a928:	6a 35 80 09 	fmtsr $r3,$fs11
    a92c:	c0 50       	beqz38 $r0,a9cc <_vfiprintf_r+0x5c4>
    a92e:	5a 10 30 4f 	beqc $r1,#0x30,a9cc <_vfiprintf_r+0x5c4>
    a932:	44 00 00 30 	movi $r0,#0x30
    a936:	6a 25 80 09 	fmtsr $r2,$fs11
    a93a:	10 01 ff ff 	sbi $r0,[$r3+#-1]
    a93e:	d5 47       	j8 a9cc <_vfiprintf_r+0x5c4>
    a940:	ce 08       	bnez38 $r6,a950 <_vfiprintf_r+0x548>
    a942:	e7 2a       	slti45 $r9,#0xa
    a944:	e8 06       	beqzs8 a950 <_vfiprintf_r+0x548>
    a946:	50 94 80 30 	addi $r9,$r9,#0x30
    a94a:	10 9f 80 47 	sbi $r9,[$sp+#0x47]
    a94e:	d5 38       	j8 a9be <_vfiprintf_r+0x5b6>
    a950:	50 ef 80 47 	addi $r14,$sp,#0x47
    a954:	80 09       	mov55 $r0,$r9
    a956:	80 26       	mov55 $r1,$r6
    a958:	84 4a       	movi55 $r2,#0xa
    a95a:	84 60       	movi55 $r3,#0x0
    a95c:	f4 81       	swi37.sp $r4,[+#0x4]
    a95e:	49 ff f1 d9 	jal 8d10 <__umoddi3>
    a962:	50 00 00 30 	addi $r0,$r0,#0x30
    a966:	80 26       	mov55 $r1,$r6
    a968:	6a e5 80 09 	fmtsr $r14,$fs11
    a96c:	84 4a       	movi55 $r2,#0xa
    a96e:	18 07 7f ff 	sbi.bi $r0,[$r14],#-1
    a972:	84 60       	movi55 $r3,#0x0
    a974:	80 09       	mov55 $r0,$r9
    a976:	49 ff f0 f3 	jal 8b5c <__udivdi3>
    a97a:	81 20       	mov55 $r9,$r0
    a97c:	fe 0f       	or33 $r0,$r1
    a97e:	80 c1       	mov55 $r6,$r1
    a980:	f4 01       	lwi37.sp $r4,[+#0x4]
    a982:	c8 e9       	bnez38 $r0,a954 <_vfiprintf_r+0x54c>
    a984:	d5 24       	j8 a9cc <_vfiprintf_r+0x5c4>
    a986:	50 1f 80 47 	addi $r1,$sp,#0x47
    a98a:	6a 25 00 01 	fmfsr $r2,$fs10
    a98e:	54 04 80 0f 	andi $r0,$r9,#0xf
    a992:	93 24       	srli45 $r9,#0x4
    a994:	38 01 00 00 	lb $r0,[$r2+($r0<<#0x0)]
    a998:	40 94 9b 84 	or_slli $r9,$r9,$r6,#0x1c
    a99c:	92 c4       	srli45 $r6,#0x4
    a99e:	6a 15 80 09 	fmtsr $r1,$fs11
    a9a2:	18 00 ff ff 	sbi.bi $r0,[$r1],#-1
    a9a6:	40 04 98 04 	or $r0,$r9,$r6
    a9aa:	c8 f0       	bnez38 $r0,a98a <_vfiprintf_r+0x582>
    a9ac:	d5 10       	j8 a9cc <_vfiprintf_r+0x5c4>
    a9ae:	cb 0d       	bnez38 $r3,a9c8 <_vfiprintf_r+0x5c0>
    a9b0:	54 0e 00 01 	andi $r0,$fp,#0x1
    a9b4:	c0 0a       	beqz38 $r0,a9c8 <_vfiprintf_r+0x5c0>
    a9b6:	44 00 00 30 	movi $r0,#0x30
    a9ba:	10 0f 80 47 	sbi $r0,[$sp+#0x47]
    a9be:	50 0f 80 47 	addi $r0,$sp,#0x47
    a9c2:	6a 05 80 09 	fmtsr $r0,$fs11
    a9c6:	d5 03       	j8 a9cc <_vfiprintf_r+0x5c4>
    a9c8:	6a 85 80 09 	fmtsr $r8,$fs11
    a9cc:	6a 05 80 01 	fmfsr $r0,$fs11
    a9d0:	40 e4 00 01 	sub $r14,$r8,$r0
    a9d4:	d5 15       	j8 a9fe <_vfiprintf_r+0x5f6>
    a9d6:	10 3f 80 0f 	sbi $r3,[$sp+#0xf]
    a9da:	4e 22 01 64 	beqz $r2,aca2 <_vfiprintf_r+0x89a>
    a9de:	84 00       	movi55 $r0,#0x0
    a9e0:	10 2f 80 20 	sbi $r2,[$sp+#0x20]
    a9e4:	10 0f 80 0f 	sbi $r0,[$sp+#0xf]
    a9e8:	81 46       	mov55 $r10,$r6
    a9ea:	84 00       	movi55 $r0,#0x0
    a9ec:	6a 04 80 09 	fmtsr $r0,$fs9
    a9f0:	b0 08       	addri36.sp $r0,#0x20
    a9f2:	85 c1       	movi55 $r14,#0x1
    a9f4:	6a 05 80 09 	fmtsr $r0,$fs11
    a9f8:	d5 03       	j8 a9fe <_vfiprintf_r+0x5f6>
    a9fa:	6a 04 80 09 	fmtsr $r0,$fs9
    a9fe:	6a 04 80 01 	fmfsr $r0,$fs9
    aa02:	42 97 00 00 	max $r9,$r14,$r0
    aa06:	20 0f 80 0f 	lbsi $r0,[$sp+#0xf]
    aa0a:	c0 02       	beqz38 $r0,aa0e <_vfiprintf_r+0x606>
    aa0c:	8d 21       	addi45 $r9,#0x1
    aa0e:	54 0e 00 02 	andi $r0,$fp,#0x2
    aa12:	6a 06 80 09 	fmtsr $r0,$fs13
    aa16:	c0 02       	beqz38 $r0,aa1a <_vfiprintf_r+0x612>
    aa18:	8d 22       	addi45 $r9,#0x2
    aa1a:	54 0e 00 84 	andi $r0,$fp,#0x84
    aa1e:	6a 06 00 09 	fmtsr $r0,$fs12
    aa22:	c8 37       	bnez38 $r0,aa90 <_vfiprintf_r+0x688>
    aa24:	40 66 a4 01 	sub $r6,$r13,$r9
    aa28:	4e 67 00 34 	blez $r6,aa90 <_vfiprintf_r+0x688>
    aa2c:	fa 00       	movpi45 $r0,#0x10
    aa2e:	6a 07 00 09 	fmtsr $r0,$fs14
    aa32:	e4 d1       	sltsi45 $r6,#0x11
    aa34:	e9 19       	bnezs8 aa66 <_vfiprintf_r+0x65e>
    aa36:	f0 07       	lwi37.sp $r0,[+#0x1c]
    aa38:	32 82 00 00 	fssi $fs8,[$r4+#0x0]
    aa3c:	8c 10       	addi45 $r0,#0x10
    aa3e:	f0 87       	swi37.sp $r0,[+#0x1c]
    aa40:	f0 06       	lwi37.sp $r0,[+#0x18]
    aa42:	32 e2 00 01 	fssi $fs14,[$r4+#0x4]
    aa46:	8c 01       	addi45 $r0,#0x1
    aa48:	e4 08       	sltsi45 $r0,#0x8
    aa4a:	f0 86       	swi37.sp $r0,[+#0x18]
    aa4c:	e8 03       	beqzs8 aa52 <_vfiprintf_r+0x64a>
    aa4e:	8c 88       	addi45 $r4,#0x8
    aa50:	d5 09       	j8 aa62 <_vfiprintf_r+0x65a>
    aa52:	b4 1f       	lwi450 $r0,[$sp]
    aa54:	80 2b       	mov55 $r1,$r11
    aa56:	b0 85       	addri36.sp $r2,#0x14
    aa58:	49 ff fc b4 	jal a3c0 <__sprint_r>
    aa5c:	4e 03 01 2a 	bnez $r0,acb0 <_vfiprintf_r+0x8a8>
    aa60:	80 88       	mov55 $r4,$r8
    aa62:	8e d0       	subi45 $r6,#0x10
    aa64:	d5 e7       	j8 aa32 <_vfiprintf_r+0x62a>
    aa66:	f0 07       	lwi37.sp $r0,[+#0x1c]
    aa68:	a9 a1       	swi333 $r6,[$r4+#0x4]
    aa6a:	88 c0       	add45 $r6,$r0
    aa6c:	f0 06       	lwi37.sp $r0,[+#0x18]
    aa6e:	32 72 00 00 	fssi $fs7,[$r4+#0x0]
    aa72:	8c 01       	addi45 $r0,#0x1
    aa74:	e4 08       	sltsi45 $r0,#0x8
    aa76:	f6 87       	swi37.sp $r6,[+#0x1c]
    aa78:	f0 86       	swi37.sp $r0,[+#0x18]
    aa7a:	e8 03       	beqzs8 aa80 <_vfiprintf_r+0x678>
    aa7c:	8c 88       	addi45 $r4,#0x8
    aa7e:	d5 09       	j8 aa90 <_vfiprintf_r+0x688>
    aa80:	b4 1f       	lwi450 $r0,[$sp]
    aa82:	80 2b       	mov55 $r1,$r11
    aa84:	b0 85       	addri36.sp $r2,#0x14
    aa86:	49 ff fc 9d 	jal a3c0 <__sprint_r>
    aa8a:	4e 03 01 13 	bnez $r0,acb0 <_vfiprintf_r+0x8a8>
    aa8e:	80 88       	mov55 $r4,$r8
    aa90:	20 0f 80 0f 	lbsi $r0,[$sp+#0xf]
    aa94:	c0 18       	beqz38 $r0,aac4 <_vfiprintf_r+0x6bc>
    aa96:	50 0f 80 0f 	addi $r0,$sp,#0xf
    aa9a:	b6 04       	swi450 $r0,[$r4]
    aa9c:	84 01       	movi55 $r0,#0x1
    aa9e:	a8 21       	swi333 $r0,[$r4+#0x4]
    aaa0:	f0 07       	lwi37.sp $r0,[+#0x1c]
    aaa2:	8c 01       	addi45 $r0,#0x1
    aaa4:	f0 87       	swi37.sp $r0,[+#0x1c]
    aaa6:	f0 06       	lwi37.sp $r0,[+#0x18]
    aaa8:	8c 01       	addi45 $r0,#0x1
    aaaa:	e4 08       	sltsi45 $r0,#0x8
    aaac:	f0 86       	swi37.sp $r0,[+#0x18]
    aaae:	e8 03       	beqzs8 aab4 <_vfiprintf_r+0x6ac>
    aab0:	8c 88       	addi45 $r4,#0x8
    aab2:	d5 09       	j8 aac4 <_vfiprintf_r+0x6bc>
    aab4:	b4 1f       	lwi450 $r0,[$sp]
    aab6:	80 2b       	mov55 $r1,$r11
    aab8:	b0 85       	addri36.sp $r2,#0x14
    aaba:	49 ff fc 83 	jal a3c0 <__sprint_r>
    aabe:	4e 03 00 f9 	bnez $r0,acb0 <_vfiprintf_r+0x8a8>
    aac2:	80 88       	mov55 $r4,$r8
    aac4:	6a 06 80 01 	fmfsr $r0,$fs13
    aac8:	c0 17       	beqz38 $r0,aaf6 <_vfiprintf_r+0x6ee>
    aaca:	b0 04       	addri36.sp $r0,#0x10
    aacc:	b6 04       	swi450 $r0,[$r4]
    aace:	84 02       	movi55 $r0,#0x2
    aad0:	a8 21       	swi333 $r0,[$r4+#0x4]
    aad2:	f0 07       	lwi37.sp $r0,[+#0x1c]
    aad4:	8c 02       	addi45 $r0,#0x2
    aad6:	f0 87       	swi37.sp $r0,[+#0x1c]
    aad8:	f0 06       	lwi37.sp $r0,[+#0x18]
    aada:	8c 01       	addi45 $r0,#0x1
    aadc:	e4 08       	sltsi45 $r0,#0x8
    aade:	f0 86       	swi37.sp $r0,[+#0x18]
    aae0:	e8 03       	beqzs8 aae6 <_vfiprintf_r+0x6de>
    aae2:	8c 88       	addi45 $r4,#0x8
    aae4:	d5 09       	j8 aaf6 <_vfiprintf_r+0x6ee>
    aae6:	b4 1f       	lwi450 $r0,[$sp]
    aae8:	80 2b       	mov55 $r1,$r11
    aaea:	b0 85       	addri36.sp $r2,#0x14
    aaec:	49 ff fc 6a 	jal a3c0 <__sprint_r>
    aaf0:	4e 03 00 e0 	bnez $r0,acb0 <_vfiprintf_r+0x8a8>
    aaf4:	80 88       	mov55 $r4,$r8
    aaf6:	6a 06 00 01 	fmfsr $r0,$fs12
    aafa:	5a 08 80 3d 	bnec $r0,#0x80,ab74 <_vfiprintf_r+0x76c>
    aafe:	40 66 a4 01 	sub $r6,$r13,$r9
    ab02:	4e 67 00 39 	blez $r6,ab74 <_vfiprintf_r+0x76c>
    ab06:	44 00 ad 4c 	movi $r0,#0xad4c
    ab0a:	6a 06 00 09 	fmtsr $r0,$fs12
    ab0e:	fa 00       	movpi45 $r0,#0x10
    ab10:	6a 06 80 09 	fmtsr $r0,$fs13
    ab14:	e4 d1       	sltsi45 $r6,#0x11
    ab16:	e9 19       	bnezs8 ab48 <_vfiprintf_r+0x740>
    ab18:	f0 07       	lwi37.sp $r0,[+#0x1c]
    ab1a:	32 c2 00 00 	fssi $fs12,[$r4+#0x0]
    ab1e:	8c 10       	addi45 $r0,#0x10
    ab20:	f0 87       	swi37.sp $r0,[+#0x1c]
    ab22:	f0 06       	lwi37.sp $r0,[+#0x18]
    ab24:	32 d2 00 01 	fssi $fs13,[$r4+#0x4]
    ab28:	8c 01       	addi45 $r0,#0x1
    ab2a:	e4 08       	sltsi45 $r0,#0x8
    ab2c:	f0 86       	swi37.sp $r0,[+#0x18]
    ab2e:	e8 03       	beqzs8 ab34 <_vfiprintf_r+0x72c>
    ab30:	8c 88       	addi45 $r4,#0x8
    ab32:	d5 09       	j8 ab44 <_vfiprintf_r+0x73c>
    ab34:	b4 1f       	lwi450 $r0,[$sp]
    ab36:	80 2b       	mov55 $r1,$r11
    ab38:	b0 85       	addri36.sp $r2,#0x14
    ab3a:	49 ff fc 43 	jal a3c0 <__sprint_r>
    ab3e:	4e 03 00 b9 	bnez $r0,acb0 <_vfiprintf_r+0x8a8>
    ab42:	80 88       	mov55 $r4,$r8
    ab44:	8e d0       	subi45 $r6,#0x10
    ab46:	d5 e7       	j8 ab14 <_vfiprintf_r+0x70c>
    ab48:	44 00 ad 4c 	movi $r0,#0xad4c
    ab4c:	b6 04       	swi450 $r0,[$r4]
    ab4e:	f0 07       	lwi37.sp $r0,[+#0x1c]
    ab50:	a9 a1       	swi333 $r6,[$r4+#0x4]
    ab52:	88 c0       	add45 $r6,$r0
    ab54:	f0 06       	lwi37.sp $r0,[+#0x18]
    ab56:	f6 87       	swi37.sp $r6,[+#0x1c]
    ab58:	8c 01       	addi45 $r0,#0x1
    ab5a:	e4 08       	sltsi45 $r0,#0x8
    ab5c:	f0 86       	swi37.sp $r0,[+#0x18]
    ab5e:	e8 03       	beqzs8 ab64 <_vfiprintf_r+0x75c>
    ab60:	8c 88       	addi45 $r4,#0x8
    ab62:	d5 09       	j8 ab74 <_vfiprintf_r+0x76c>
    ab64:	b4 1f       	lwi450 $r0,[$sp]
    ab66:	80 2b       	mov55 $r1,$r11
    ab68:	b0 85       	addri36.sp $r2,#0x14
    ab6a:	49 ff fc 2b 	jal a3c0 <__sprint_r>
    ab6e:	4e 03 00 a1 	bnez $r0,acb0 <_vfiprintf_r+0x8a8>
    ab72:	80 88       	mov55 $r4,$r8
    ab74:	6a 64 80 01 	fmfsr $r6,$fs9
    ab78:	8a ce       	sub45 $r6,$r14
    ab7a:	4e 67 00 38 	blez $r6,abea <_vfiprintf_r+0x7e2>
    ab7e:	44 00 ad 4c 	movi $r0,#0xad4c
    ab82:	6a 04 80 09 	fmtsr $r0,$fs9
    ab86:	fa 00       	movpi45 $r0,#0x10
    ab88:	6a 06 00 09 	fmtsr $r0,$fs12
    ab8c:	e4 d1       	sltsi45 $r6,#0x11
    ab8e:	e9 19       	bnezs8 abc0 <_vfiprintf_r+0x7b8>
    ab90:	f0 07       	lwi37.sp $r0,[+#0x1c]
    ab92:	32 92 00 00 	fssi $fs9,[$r4+#0x0]
    ab96:	8c 10       	addi45 $r0,#0x10
    ab98:	f0 87       	swi37.sp $r0,[+#0x1c]
    ab9a:	f0 06       	lwi37.sp $r0,[+#0x18]
    ab9c:	32 c2 00 01 	fssi $fs12,[$r4+#0x4]
    aba0:	8c 01       	addi45 $r0,#0x1
    aba2:	e4 08       	sltsi45 $r0,#0x8
    aba4:	f0 86       	swi37.sp $r0,[+#0x18]
    aba6:	e8 03       	beqzs8 abac <_vfiprintf_r+0x7a4>
    aba8:	8c 88       	addi45 $r4,#0x8
    abaa:	d5 09       	j8 abbc <_vfiprintf_r+0x7b4>
    abac:	b4 1f       	lwi450 $r0,[$sp]
    abae:	80 2b       	mov55 $r1,$r11
    abb0:	b0 85       	addri36.sp $r2,#0x14
    abb2:	49 ff fc 07 	jal a3c0 <__sprint_r>
    abb6:	4e 03 00 7d 	bnez $r0,acb0 <_vfiprintf_r+0x8a8>
    abba:	80 88       	mov55 $r4,$r8
    abbc:	8e d0       	subi45 $r6,#0x10
    abbe:	d5 e7       	j8 ab8c <_vfiprintf_r+0x784>
    abc0:	44 00 ad 4c 	movi $r0,#0xad4c
    abc4:	b6 04       	swi450 $r0,[$r4]
    abc6:	f0 07       	lwi37.sp $r0,[+#0x1c]
    abc8:	a9 a1       	swi333 $r6,[$r4+#0x4]
    abca:	88 c0       	add45 $r6,$r0
    abcc:	f0 06       	lwi37.sp $r0,[+#0x18]
    abce:	f6 87       	swi37.sp $r6,[+#0x1c]
    abd0:	8c 01       	addi45 $r0,#0x1
    abd2:	e4 08       	sltsi45 $r0,#0x8
    abd4:	f0 86       	swi37.sp $r0,[+#0x18]
    abd6:	e8 03       	beqzs8 abdc <_vfiprintf_r+0x7d4>
    abd8:	8c 88       	addi45 $r4,#0x8
    abda:	d5 08       	j8 abea <_vfiprintf_r+0x7e2>
    abdc:	b4 1f       	lwi450 $r0,[$sp]
    abde:	80 2b       	mov55 $r1,$r11
    abe0:	b0 85       	addri36.sp $r2,#0x14
    abe2:	49 ff fb ef 	jal a3c0 <__sprint_r>
    abe6:	c8 65       	bnez38 $r0,acb0 <_vfiprintf_r+0x8a8>
    abe8:	80 88       	mov55 $r4,$r8
    abea:	f0 07       	lwi37.sp $r0,[+#0x1c]
    abec:	32 b2 00 00 	fssi $fs11,[$r4+#0x0]
    abf0:	88 0e       	add45 $r0,$r14
    abf2:	f0 87       	swi37.sp $r0,[+#0x1c]
    abf4:	f0 06       	lwi37.sp $r0,[+#0x18]
    abf6:	14 e2 00 01 	swi $r14,[$r4+#0x4]
    abfa:	8c 01       	addi45 $r0,#0x1
    abfc:	e4 08       	sltsi45 $r0,#0x8
    abfe:	f0 86       	swi37.sp $r0,[+#0x18]
    ac00:	e8 04       	beqzs8 ac08 <_vfiprintf_r+0x800>
    ac02:	50 02 00 08 	addi $r0,$r4,#0x8
    ac06:	d5 08       	j8 ac16 <_vfiprintf_r+0x80e>
    ac08:	b4 1f       	lwi450 $r0,[$sp]
    ac0a:	80 2b       	mov55 $r1,$r11
    ac0c:	b0 85       	addri36.sp $r2,#0x14
    ac0e:	49 ff fb d9 	jal a3c0 <__sprint_r>
    ac12:	c8 4f       	bnez38 $r0,acb0 <_vfiprintf_r+0x8a8>
    ac14:	80 08       	mov55 $r0,$r8
    ac16:	54 1e 00 04 	andi $r1,$fp,#0x4
    ac1a:	c9 07       	bnez38 $r1,ac28 <_vfiprintf_r+0x820>
    ac1c:	f0 07       	lwi37.sp $r0,[+#0x1c]
    ac1e:	42 d4 b4 00 	max $r13,$r9,$r13
    ac22:	88 ed       	add45 $r7,$r13
    ac24:	c0 39       	beqz38 $r0,ac96 <_vfiprintf_r+0x88e>
    ac26:	d5 32       	j8 ac8a <_vfiprintf_r+0x882>
    ac28:	40 66 a4 01 	sub $r6,$r13,$r9
    ac2c:	4e 67 ff f8 	blez $r6,ac1c <_vfiprintf_r+0x814>
    ac30:	45 c0 00 10 	movi $fp,#0x10
    ac34:	e4 d1       	sltsi45 $r6,#0x11
    ac36:	e9 18       	bnezs8 ac66 <_vfiprintf_r+0x85e>
    ac38:	f1 07       	lwi37.sp $r1,[+#0x1c]
    ac3a:	32 80 00 00 	fssi $fs8,[$r0+#0x0]
    ac3e:	8c 30       	addi45 $r1,#0x10
    ac40:	f1 87       	swi37.sp $r1,[+#0x1c]
    ac42:	f1 06       	lwi37.sp $r1,[+#0x18]
    ac44:	15 c0 00 01 	swi $fp,[$r0+#0x4]
    ac48:	8c 21       	addi45 $r1,#0x1
    ac4a:	e4 28       	sltsi45 $r1,#0x8
    ac4c:	f1 86       	swi37.sp $r1,[+#0x18]
    ac4e:	e8 03       	beqzs8 ac54 <_vfiprintf_r+0x84c>
    ac50:	8c 08       	addi45 $r0,#0x8
    ac52:	d5 08       	j8 ac62 <_vfiprintf_r+0x85a>
    ac54:	b4 1f       	lwi450 $r0,[$sp]
    ac56:	80 2b       	mov55 $r1,$r11
    ac58:	b0 85       	addri36.sp $r2,#0x14
    ac5a:	49 ff fb b3 	jal a3c0 <__sprint_r>
    ac5e:	c8 29       	bnez38 $r0,acb0 <_vfiprintf_r+0x8a8>
    ac60:	80 08       	mov55 $r0,$r8
    ac62:	8e d0       	subi45 $r6,#0x10
    ac64:	d5 e8       	j8 ac34 <_vfiprintf_r+0x82c>
    ac66:	a9 81       	swi333 $r6,[$r0+#0x4]
    ac68:	32 70 00 00 	fssi $fs7,[$r0+#0x0]
    ac6c:	f0 07       	lwi37.sp $r0,[+#0x1c]
    ac6e:	88 c0       	add45 $r6,$r0
    ac70:	f0 06       	lwi37.sp $r0,[+#0x18]
    ac72:	f6 87       	swi37.sp $r6,[+#0x1c]
    ac74:	8c 01       	addi45 $r0,#0x1
    ac76:	e4 08       	sltsi45 $r0,#0x8
    ac78:	f0 86       	swi37.sp $r0,[+#0x18]
    ac7a:	e9 d1       	bnezs8 ac1c <_vfiprintf_r+0x814>
    ac7c:	b4 1f       	lwi450 $r0,[$sp]
    ac7e:	80 2b       	mov55 $r1,$r11
    ac80:	b0 85       	addri36.sp $r2,#0x14
    ac82:	49 ff fb 9f 	jal a3c0 <__sprint_r>
    ac86:	c0 cb       	beqz38 $r0,ac1c <_vfiprintf_r+0x814>
    ac88:	d5 14       	j8 acb0 <_vfiprintf_r+0x8a8>
    ac8a:	b4 1f       	lwi450 $r0,[$sp]
    ac8c:	80 2b       	mov55 $r1,$r11
    ac8e:	b0 85       	addri36.sp $r2,#0x14
    ac90:	49 ff fb 98 	jal a3c0 <__sprint_r>
    ac94:	c8 0e       	bnez38 $r0,acb0 <_vfiprintf_r+0x8a8>
    ac96:	84 00       	movi55 $r0,#0x0
    ac98:	f0 86       	swi37.sp $r0,[+#0x18]
    ac9a:	80 ca       	mov55 $r6,$r10
    ac9c:	80 88       	mov55 $r4,$r8
    ac9e:	48 ff fb ff 	j a49c <_vfiprintf_r+0x94>
    aca2:	f0 07       	lwi37.sp $r0,[+#0x1c]
    aca4:	c0 06       	beqz38 $r0,acb0 <_vfiprintf_r+0x8a8>
    aca6:	b4 1f       	lwi450 $r0,[$sp]
    aca8:	80 2b       	mov55 $r1,$r11
    acaa:	b0 85       	addri36.sp $r2,#0x14
    acac:	49 ff fb 8a 	jal a3c0 <__sprint_r>
    acb0:	02 05 80 06 	lhi $r0,[$r11+#0xc]
    acb4:	96 36       	bmski33 $r0,#0x6
    acb6:	4e 03 fb d0 	bnez $r0,a456 <_vfiprintf_r+0x4e>
    acba:	80 07       	mov55 $r0,$r7
    acbc:	d5 07       	j8 acca <_vfiprintf_r+0x8c2>
    acbe:	5a 30 01 04 	beqc $r3,#0x1,acc6 <_vfiprintf_r+0x8be>
    acc2:	48 ff fe 1e 	j a8fe <_vfiprintf_r+0x4f6>
    acc6:	48 ff fe 40 	j a946 <_vfiprintf_r+0x53e>
    acca:	34 3f 80 22 	fldi $fd3,[$sp+#0x88]
    acce:	34 4f 80 24 	fldi $fd4,[$sp+#0x90]
    acd2:	34 5f 80 26 	fldi $fd5,[$sp+#0x98]
    acd6:	34 6f 80 28 	fldi $fd6,[$sp+#0xa0]
    acda:	34 7f 80 2a 	fldi $fd7,[$sp+#0xa8]
    acde:	fc f6       	pop25 $r14,#176    ! {$r6~$r14, $fp, $gp, $lp}

0000ace0 <__sbprintf>:
    ace0:	fc 20       	push25 $r8,#0    ! {$r6~$r8, $fp, $gp, $lp}
    ace2:	51 ff fb 90 	addi $sp,$sp,#-1136
    ace6:	80 c1       	mov55 $r6,$r1
    ace8:	a4 4e       	lhi333 $r1,[$r1+#0xc]
    acea:	f0 81       	swi37.sp $r0,[+#0x4]
    acec:	66 10 80 02 	bitci $r1,$r1,#0x2
    acf0:	12 1f 80 0a 	shi $r1,[$sp+#0x14]
    acf4:	83 86       	mov55 $fp,$r6
    acf6:	b9 19       	lwi37 $r1,[$fp+#0x64]
    acf8:	f1 9b       	swi37.sp $r1,[+#0x6c]
    acfa:	a4 77       	lhi333 $r1,[$r6+#0xe]
    acfc:	12 1f 80 0b 	shi $r1,[$sp+#0x16]
    ad00:	a0 77       	lwi333 $r1,[$r6+#0x1c]
    ad02:	f1 89       	swi37.sp $r1,[+#0x24]
    ad04:	b9 09       	lwi37 $r1,[$fp+#0x24]
    ad06:	f1 8b       	swi37.sp $r1,[+#0x2c]
    ad08:	b0 5c       	addri36.sp $r1,#0x70
    ad0a:	f1 82       	swi37.sp $r1,[+#0x8]
    ad0c:	f1 86       	swi37.sp $r1,[+#0x18]
    ad0e:	44 10 04 00 	movi $r1,#0x400
    ad12:	f1 84       	swi37.sp $r1,[+#0x10]
    ad14:	f1 87       	swi37.sp $r1,[+#0x1c]
    ad16:	84 20       	movi55 $r1,#0x0
    ad18:	f1 88       	swi37.sp $r1,[+#0x20]
    ad1a:	b0 42       	addri36.sp $r1,#0x8
    ad1c:	49 ff fb 76 	jal a408 <_vfiprintf_r>
    ad20:	80 e0       	mov55 $r7,$r0
    ad22:	4e 05 00 08 	bltz $r0,ad32 <__sbprintf+0x52>
    ad26:	f0 01       	lwi37.sp $r0,[+#0x4]
    ad28:	b0 42       	addri36.sp $r1,#0x8
    ad2a:	49 ff f8 29 	jal 9d7c <_fflush_r>
    ad2e:	c0 02       	beqz38 $r0,ad32 <__sbprintf+0x52>
    ad30:	84 ff       	movi55 $r7,#-1
    ad32:	02 0f 80 0a 	lhi $r0,[$sp+#0x14]
    ad36:	96 36       	bmski33 $r0,#0x6
    ad38:	c0 05       	beqz38 $r0,ad42 <__sbprintf+0x62>
    ad3a:	a4 36       	lhi333 $r0,[$r6+#0xc]
    ad3c:	58 00 00 40 	ori $r0,$r0,#0x40
    ad40:	ac 36       	shi333 $r0,[$r6+#0xc]
    ad42:	80 07       	mov55 $r0,$r7
    ad44:	51 ff 84 70 	addi $sp,$sp,#0x470
    ad48:	fc a0       	pop25 $r8,#0    ! {$r6~$r8, $fp, $gp, $lp}
	...

0000ad4c <zeroes.4502>:
    ad4c:	30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30     0000000000000000

0000ad5c <blanks.4501>:
    ad5c:	20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20                     

0000ad6c <_write_r>:
    ad6c:	fc 00       	push25 $r6,#0    ! {$r6, $fp, $gp, $lp}
    ad6e:	84 00       	movi55 $r0,#0x0
    ad70:	3c 0e 00 23 	swi.gp $r0,[+#0x8c]
    ad74:	80 01       	mov55 $r0,$r1
    ad76:	80 22       	mov55 $r1,$r2
    ad78:	80 43       	mov55 $r2,$r3
    ad7a:	49 00 03 75 	jal b464 <_write>
    ad7e:	5a 0f ff 07 	bnec $r0,#-1,ad8c <_write_r+0x20>
    ad82:	3c 1c 00 23 	lwi.gp $r1,[+#0x8c]
    ad86:	c1 03       	beqz38 $r1,ad8c <_write_r+0x20>
    ad88:	3c 1e 0a d4 	swi.gp $r1,[+#0x2b50]
    ad8c:	fc 80       	pop25 $r6,#0    ! {$r6, $fp, $gp, $lp}

0000ad8e <__swsetup_r>:
    ad8e:	fc 01       	push25 $r6,#8    ! {$r6, $fp, $gp, $lp}
    ad90:	f0 81       	swi37.sp $r0,[+#0x4]
    ad92:	3c 0c 0a d8 	lwi.gp $r0,[+#0x2b60]
    ad96:	80 c1       	mov55 $r6,$r1
    ad98:	c8 03       	bnez38 $r0,ad9e <__swsetup_r+0x10>
    ad9a:	49 ff f8 17 	jal 9dc8 <__sinit>
    ad9e:	22 13 00 06 	lhsi $r1,[$r6+#0xc]
    ada2:	96 09       	zeh33 $r0,$r1
    ada4:	54 20 00 08 	andi $r2,$r0,#0x8
    ada8:	ca 23       	bnez38 $r2,adee <__swsetup_r+0x60>
    adaa:	54 20 00 10 	andi $r2,$r0,#0x10
    adae:	ca 05       	bnez38 $r2,adb8 <__swsetup_r+0x2a>
    adb0:	84 09       	movi55 $r0,#0x9
    adb2:	3c 0e 0a d4 	swi.gp $r0,[+#0x2b50]
    adb6:	d5 3c       	j8 ae2e <__swsetup_r+0xa0>
    adb8:	96 16       	bmski33 $r0,#0x2
    adba:	c0 16       	beqz38 $r0,ade6 <__swsetup_r+0x58>
    adbc:	04 13 00 0c 	lwi $r1,[$r6+#0x30]
    adc0:	c1 0b       	beqz38 $r1,add6 <__swsetup_r+0x48>
    adc2:	50 03 00 40 	addi $r0,$r6,#0x40
    adc6:	4c 10 00 05 	beq $r1,$r0,add0 <__swsetup_r+0x42>
    adca:	f0 01       	lwi37.sp $r0,[+#0x4]
    adcc:	49 ff f9 32 	jal a030 <_free_r>
    add0:	84 00       	movi55 $r0,#0x0
    add2:	14 03 00 0c 	swi $r0,[$r6+#0x30]
    add6:	a4 36       	lhi333 $r0,[$r6+#0xc]
    add8:	66 00 00 24 	bitci $r0,$r0,#0x24
    addc:	ac 36       	shi333 $r0,[$r6+#0xc]
    adde:	84 00       	movi55 $r0,#0x0
    ade0:	a8 31       	swi333 $r0,[$r6+#0x4]
    ade2:	a0 34       	lwi333 $r0,[$r6+#0x10]
    ade4:	b6 06       	swi450 $r0,[$r6]
    ade6:	a4 36       	lhi333 $r0,[$r6+#0xc]
    ade8:	58 00 00 08 	ori $r0,$r0,#0x8
    adec:	ac 36       	shi333 $r0,[$r6+#0xc]
    adee:	a0 34       	lwi333 $r0,[$r6+#0x10]
    adf0:	c8 0a       	bnez38 $r0,ae04 <__swsetup_r+0x76>
    adf2:	a4 36       	lhi333 $r0,[$r6+#0xc]
    adf4:	54 00 02 80 	andi $r0,$r0,#0x280
    adf8:	5a 02 00 06 	beqc $r0,#0x200,ae04 <__swsetup_r+0x76>
    adfc:	f0 01       	lwi37.sp $r0,[+#0x4]
    adfe:	80 26       	mov55 $r1,$r6
    ae00:	49 00 01 d9 	jal b1b2 <__smakebuf_r>
    ae04:	a4 76       	lhi333 $r1,[$r6+#0xc]
    ae06:	96 0c       	xlsb33 $r0,$r1
    ae08:	c0 07       	beqz38 $r0,ae16 <__swsetup_r+0x88>
    ae0a:	84 00       	movi55 $r0,#0x0
    ae0c:	a8 32       	swi333 $r0,[$r6+#0x8]
    ae0e:	a0 35       	lwi333 $r0,[$r6+#0x14]
    ae10:	fe 02       	neg33 $r0,$r0
    ae12:	a8 36       	swi333 $r0,[$r6+#0x18]
    ae14:	d5 05       	j8 ae1e <__swsetup_r+0x90>
    ae16:	96 4e       	bmski33 $r1,#0x1
    ae18:	c9 02       	bnez38 $r1,ae1c <__swsetup_r+0x8e>
    ae1a:	a0 35       	lwi333 $r0,[$r6+#0x14]
    ae1c:	a8 32       	swi333 $r0,[$r6+#0x8]
    ae1e:	a0 34       	lwi333 $r0,[$r6+#0x10]
    ae20:	c8 0c       	bnez38 $r0,ae38 <__swsetup_r+0xaa>
    ae22:	22 13 00 06 	lhsi $r1,[$r6+#0xc]
    ae26:	54 00 80 80 	andi $r0,$r1,#0x80
    ae2a:	96 01       	zeh33 $r0,$r0
    ae2c:	c0 07       	beqz38 $r0,ae3a <__swsetup_r+0xac>
    ae2e:	58 10 80 40 	ori $r1,$r1,#0x40
    ae32:	ac 76       	shi333 $r1,[$r6+#0xc]
    ae34:	84 1f       	movi55 $r0,#-1
    ae36:	fc 81       	pop25 $r6,#8    ! {$r6, $fp, $gp, $lp}
    ae38:	84 00       	movi55 $r0,#0x0
    ae3a:	fc 81       	pop25 $r6,#8    ! {$r6, $fp, $gp, $lp}

0000ae3c <abort>:
    ae3c:	fc 00       	push25 $r6,#0    ! {$r6, $fp, $gp, $lp}
    ae3e:	84 01       	movi55 $r0,#0x1
    ae40:	49 00 03 06 	jal b44c <_exit>
    ae44:	92 00       	nop16

0000ae46 <_close_r>:
    ae46:	fc 00       	push25 $r6,#0    ! {$r6, $fp, $gp, $lp}
    ae48:	84 00       	movi55 $r0,#0x0
    ae4a:	3c 0e 00 23 	swi.gp $r0,[+#0x8c]
    ae4e:	80 01       	mov55 $r0,$r1
    ae50:	49 00 03 02 	jal b454 <_close>
    ae54:	5a 0f ff 07 	bnec $r0,#-1,ae62 <_close_r+0x1c>
    ae58:	3c 1c 00 23 	lwi.gp $r1,[+#0x8c]
    ae5c:	c1 03       	beqz38 $r1,ae62 <_close_r+0x1c>
    ae5e:	3c 1e 0a d4 	swi.gp $r1,[+#0x2b50]
    ae62:	fc 80       	pop25 $r6,#0    ! {$r6, $fp, $gp, $lp}

0000ae64 <_fclose_r>:
    ae64:	c1 41       	beqz38 $r1,aee6 <_fclose_r+0x82>
    ae66:	fc 21       	push25 $r8,#8    ! {$r6~$r8, $fp, $gp, $lp}
    ae68:	80 c1       	mov55 $r6,$r1
    ae6a:	3c 1c 0a d8 	lwi.gp $r1,[+#0x2b60]
    ae6e:	f0 81       	swi37.sp $r0,[+#0x4]
    ae70:	c9 03       	bnez38 $r1,ae76 <_fclose_r+0x12>
    ae72:	49 ff f7 ab 	jal 9dc8 <__sinit>
    ae76:	22 03 00 06 	lhsi $r0,[$r6+#0xc]
    ae7a:	c8 03       	bnez38 $r0,ae80 <_fclose_r+0x1c>
    ae7c:	84 00       	movi55 $r0,#0x0
    ae7e:	fc a1       	pop25 $r8,#8    ! {$r6~$r8, $fp, $gp, $lp}
    ae80:	f0 01       	lwi37.sp $r0,[+#0x4]
    ae82:	80 26       	mov55 $r1,$r6
    ae84:	49 ff f6 e8 	jal 9c54 <__sflush_r>
    ae88:	04 23 00 0b 	lwi $r2,[$r6+#0x2c]
    ae8c:	80 e0       	mov55 $r7,$r0
    ae8e:	c2 07       	beqz38 $r2,ae9c <_fclose_r+0x38>
    ae90:	f0 01       	lwi37.sp $r0,[+#0x4]
    ae92:	a0 77       	lwi333 $r1,[$r6+#0x1c]
    ae94:	dd 22       	jral5 $r2
    ae96:	4e 04 00 03 	bgez $r0,ae9c <_fclose_r+0x38>
    ae9a:	84 ff       	movi55 $r7,#-1
    ae9c:	a4 36       	lhi333 $r0,[$r6+#0xc]
    ae9e:	96 3e       	bmski33 $r0,#0x7
    aea0:	c0 05       	beqz38 $r0,aeaa <_fclose_r+0x46>
    aea2:	f0 01       	lwi37.sp $r0,[+#0x4]
    aea4:	a0 74       	lwi333 $r1,[$r6+#0x10]
    aea6:	49 ff f8 c5 	jal a030 <_free_r>
    aeaa:	04 13 00 0c 	lwi $r1,[$r6+#0x30]
    aeae:	c1 0b       	beqz38 $r1,aec4 <_fclose_r+0x60>
    aeb0:	50 03 00 40 	addi $r0,$r6,#0x40
    aeb4:	4c 10 00 05 	beq $r1,$r0,aebe <_fclose_r+0x5a>
    aeb8:	f0 01       	lwi37.sp $r0,[+#0x4]
    aeba:	49 ff f8 bb 	jal a030 <_free_r>
    aebe:	84 00       	movi55 $r0,#0x0
    aec0:	14 03 00 0c 	swi $r0,[$r6+#0x30]
    aec4:	04 13 00 11 	lwi $r1,[$r6+#0x44]
    aec8:	c1 07       	beqz38 $r1,aed6 <_fclose_r+0x72>
    aeca:	f0 01       	lwi37.sp $r0,[+#0x4]
    aecc:	49 ff f8 b2 	jal a030 <_free_r>
    aed0:	84 00       	movi55 $r0,#0x0
    aed2:	14 03 00 11 	swi $r0,[$r6+#0x44]
    aed6:	49 ff f7 e7 	jal 9ea4 <__sfp_lock_acquire>
    aeda:	84 00       	movi55 $r0,#0x0
    aedc:	ac 36       	shi333 $r0,[$r6+#0xc]
    aede:	49 ff f7 e4 	jal 9ea6 <__sfp_lock_release>
    aee2:	80 07       	mov55 $r0,$r7
    aee4:	fc a1       	pop25 $r8,#8    ! {$r6~$r8, $fp, $gp, $lp}
    aee6:	84 00       	movi55 $r0,#0x0
    aee8:	dd 9e       	ret5 $lp

0000aeea <__sfvwrite_r>:
    aeea:	a0 d2       	lwi333 $r3,[$r2+#0x8]
    aeec:	4e 32 01 50 	beqz $r3,b18c <__sfvwrite_r+0x2a2>
    aef0:	fc 62       	push25 $r14,#16    ! {$r6~$r14, $fp, $gp, $lp}
    aef2:	36 3f 80 02 	fsdi $fd3,[$sp+#0x8]
    aef6:	f0 81       	swi37.sp $r0,[+#0x4]
    aef8:	a4 0e       	lhi333 $r0,[$r1+#0xc]
    aefa:	81 82       	mov55 $r12,$r2
    aefc:	96 1e       	bmski33 $r0,#0x3
    aefe:	80 c1       	mov55 $r6,$r1
    af00:	c0 10       	beqz38 $r0,af20 <__sfvwrite_r+0x36>
    af02:	a0 0c       	lwi333 $r0,[$r1+#0x10]
    af04:	c0 0e       	beqz38 $r0,af20 <__sfvwrite_r+0x36>
    af06:	a4 36       	lhi333 $r0,[$r6+#0xc]
    af08:	b5 0c       	lwi450 $r8,[$r12]
    af0a:	54 70 00 02 	andi $r7,$r0,#0x2
    af0e:	97 f9       	zeh33 $r7,$r7
    af10:	c7 4d       	beqz38 $r7,afaa <__sfvwrite_r+0xc0>
    af12:	85 20       	movi55 $r9,#0x0
    af14:	46 a7 ff ff 	sethi $r10,#0x7ffff
    af18:	80 e9       	mov55 $r7,$r9
    af1a:	50 a5 0c 00 	addi $r10,$r10,#0xc00
    af1e:	d5 1b       	j8 af54 <__sfvwrite_r+0x6a>
    af20:	f0 01       	lwi37.sp $r0,[+#0x4]
    af22:	80 26       	mov55 $r1,$r6
    af24:	49 ff ff 35 	jal ad8e <__swsetup_r>
    af28:	c0 ef       	beqz38 $r0,af06 <__sfvwrite_r+0x1c>
    af2a:	48 00 01 2d 	j b184 <__sfvwrite_r+0x29a>
    af2e:	e3 47       	slt45 $r10,$r7
    af30:	80 6a       	mov55 $r3,$r10
    af32:	04 43 00 09 	lwi $r4,[$r6+#0x24]
    af36:	f0 01       	lwi37.sp $r0,[+#0x4]
    af38:	a0 77       	lwi333 $r1,[$r6+#0x1c]
    af3a:	80 49       	mov55 $r2,$r9
    af3c:	40 33 bc 1a 	cmovz $r3,$r7,$r15
    af40:	dd 24       	jral5 $r4
    af42:	4e 07 01 1d 	blez $r0,b17c <__sfvwrite_r+0x292>
    af46:	80 4c       	mov55 $r2,$r12
    af48:	a0 52       	lwi333 $r1,[$r2+#0x8]
    af4a:	89 20       	add45 $r9,$r0
    af4c:	8a e0       	sub45 $r7,$r0
    af4e:	9a 08       	sub333 $r0,$r1,$r0
    af50:	a8 12       	swi333 $r0,[$r2+#0x8]
    af52:	c0 29       	beqz38 $r0,afa4 <__sfvwrite_r+0xba>
    af54:	cf ed       	bnez38 $r7,af2e <__sfvwrite_r+0x44>
    af56:	b5 28       	lwi450 $r9,[$r8]
    af58:	04 74 00 01 	lwi $r7,[$r8+#0x4]
    af5c:	8d 08       	addi45 $r8,#0x8
    af5e:	d5 fb       	j8 af54 <__sfvwrite_r+0x6a>
    af60:	a4 b6       	lhi333 $r2,[$r6+#0xc]
    af62:	a1 f2       	lwi333 $r7,[$r6+#0x8]
    af64:	54 01 02 00 	andi $r0,$r2,#0x200
    af68:	4e 02 00 7f 	beqz $r0,b066 <__sfvwrite_r+0x17c>
    af6c:	e3 27       	slt45 $r9,$r7
    af6e:	4e f3 00 79 	bnez $r15,b060 <__sfvwrite_r+0x176>
    af72:	54 01 04 80 	andi $r0,$r2,#0x480
    af76:	c8 32       	bnez38 $r0,afda <__sfvwrite_r+0xf0>
    af78:	e3 27       	slt45 $r9,$r7
    af7a:	4e f3 00 73 	bnez $r15,b060 <__sfvwrite_r+0x176>
    af7e:	80 47       	mov55 $r2,$r7
    af80:	b4 06       	lwi450 $r0,[$r6]
    af82:	80 2a       	mov55 $r1,$r10
    af84:	49 00 01 94 	jal b2ac <memmove>
    af88:	a0 32       	lwi333 $r0,[$r6+#0x8]
    af8a:	8a 07       	sub45 $r0,$r7
    af8c:	a8 32       	swi333 $r0,[$r6+#0x8]
    af8e:	b4 06       	lwi450 $r0,[$r6]
    af90:	88 e0       	add45 $r7,$r0
    af92:	b6 e6       	swi450 $r7,[$r6]
    af94:	80 e9       	mov55 $r7,$r9
    af96:	80 2c       	mov55 $r1,$r12
    af98:	a0 0a       	lwi333 $r0,[$r1+#0x8]
    af9a:	89 47       	add45 $r10,$r7
    af9c:	8b 27       	sub45 $r9,$r7
    af9e:	9b c7       	sub333 $r7,$r0,$r7
    afa0:	a9 ca       	swi333 $r7,[$r1+#0x8]
    afa2:	cf 15       	bnez38 $r7,afcc <__sfvwrite_r+0xe2>
    afa4:	84 00       	movi55 $r0,#0x0
    afa6:	48 00 00 f0 	j b186 <__sfvwrite_r+0x29c>
    afaa:	96 04       	xlsb33 $r0,$r0
    afac:	c0 06       	beqz38 $r0,afb8 <__sfvwrite_r+0xce>
    afae:	81 c7       	mov55 $r14,$r7
    afb0:	81 67       	mov55 $r11,$r7
    afb2:	81 47       	mov55 $r10,$r7
    afb4:	48 00 00 af 	j b112 <__sfvwrite_r+0x228>
    afb8:	81 40       	mov55 $r10,$r0
    afba:	81 20       	mov55 $r9,$r0
    afbc:	84 02       	movi55 $r0,#0x2
    afbe:	6a 03 00 09 	fmtsr $r0,$fs6
    afc2:	46 e7 ff ff 	sethi $r14,#0x7ffff
    afc6:	50 e7 0f ff 	addi $r14,$r14,#0xfff
    afca:	87 83       	movi55 $fp,#0x3
    afcc:	4e 93 ff ca 	bnez $r9,af60 <__sfvwrite_r+0x76>
    afd0:	b5 48       	lwi450 $r10,[$r8]
    afd2:	04 94 00 01 	lwi $r9,[$r8+#0x4]
    afd6:	8d 08       	addi45 $r8,#0x8
    afd8:	d5 fa       	j8 afcc <__sfvwrite_r+0xe2>
    afda:	a0 35       	lwi333 $r0,[$r6+#0x14]
    afdc:	b5 66       	lwi450 $r11,[$r6]
    afde:	a0 74       	lwi333 $r1,[$r6+#0x10]
    afe0:	6a 33 00 01 	fmfsr $r3,$fs6
    afe4:	42 0e 00 24 	mul $r0,$fp,$r0
    afe8:	40 d5 84 01 	sub $r13,$r11,$r1
    afec:	40 00 0c 16 	divsr $r0,$r0,$r0,$r3
    aff0:	50 36 80 01 	addi $r3,$r13,#0x1
    aff4:	40 b1 a4 00 	add $r11,$r3,$r9
    aff8:	e2 0b       	slt45 $r0,$r11
    affa:	54 21 04 00 	andi $r2,$r2,#0x400
    affe:	40 b0 3c 1a 	cmovz $r11,$r0,$r15
    b002:	f0 01       	lwi37.sp $r0,[+#0x4]
    b004:	c2 11       	beqz38 $r2,b026 <__sfvwrite_r+0x13c>
    b006:	80 2b       	mov55 $r1,$r11
    b008:	49 ff f8 50 	jal a0a8 <_malloc_r>
    b00c:	80 e0       	mov55 $r7,$r0
    b00e:	c0 19       	beqz38 $r0,b040 <__sfvwrite_r+0x156>
    b010:	a0 74       	lwi333 $r1,[$r6+#0x10]
    b012:	80 4d       	mov55 $r2,$r13
    b014:	49 ff f7 a0 	jal 9f54 <memcpy>
    b018:	a4 36       	lhi333 $r0,[$r6+#0xc]
    b01a:	66 00 04 80 	bitci $r0,$r0,#0x480
    b01e:	58 00 00 80 	ori $r0,$r0,#0x80
    b022:	ac 36       	shi333 $r0,[$r6+#0xc]
    b024:	d5 13       	j8 b04a <__sfvwrite_r+0x160>
    b026:	80 4b       	mov55 $r2,$r11
    b028:	49 00 01 9a 	jal b35c <_realloc_r>
    b02c:	80 e0       	mov55 $r7,$r0
    b02e:	c8 0e       	bnez38 $r0,b04a <__sfvwrite_r+0x160>
    b030:	f0 01       	lwi37.sp $r0,[+#0x4]
    b032:	a0 74       	lwi333 $r1,[$r6+#0x10]
    b034:	49 ff f7 fe 	jal a030 <_free_r>
    b038:	a4 36       	lhi333 $r0,[$r6+#0xc]
    b03a:	66 00 00 80 	bitci $r0,$r0,#0x80
    b03e:	ac 36       	shi333 $r0,[$r6+#0xc]
    b040:	84 0c       	movi55 $r0,#0xc
    b042:	3c 0e 0a d4 	swi.gp $r0,[+#0x2b50]
    b046:	48 00 00 9b 	j b17c <__sfvwrite_r+0x292>
    b04a:	a9 f4       	swi333 $r7,[$r6+#0x10]
    b04c:	14 b3 00 05 	swi $r11,[$r6+#0x14]
    b050:	88 ed       	add45 $r7,$r13
    b052:	8b 6d       	sub45 $r11,$r13
    b054:	b6 e6       	swi450 $r7,[$r6]
    b056:	14 b3 00 02 	swi $r11,[$r6+#0x8]
    b05a:	80 e9       	mov55 $r7,$r9
    b05c:	48 ff ff 8e 	j af78 <__sfvwrite_r+0x8e>
    b060:	80 e9       	mov55 $r7,$r9
    b062:	48 ff ff 8e 	j af7e <__sfvwrite_r+0x94>
    b066:	b4 06       	lwi450 $r0,[$r6]
    b068:	a0 74       	lwi333 $r1,[$r6+#0x10]
    b06a:	e2 20       	slt45 $r1,$r0
    b06c:	e9 04       	bnezs8 b074 <__sfvwrite_r+0x18a>
    b06e:	a1 35       	lwi333 $r4,[$r6+#0x14]
    b070:	e3 24       	slt45 $r9,$r4
    b072:	e8 18       	beqzs8 b0a2 <__sfvwrite_r+0x1b8>
    b074:	e2 e9       	slt45 $r7,$r9
    b076:	40 74 bc 1a 	cmovz $r7,$r9,$r15
    b07a:	80 2a       	mov55 $r1,$r10
    b07c:	80 47       	mov55 $r2,$r7
    b07e:	49 00 01 17 	jal b2ac <memmove>
    b082:	a0 32       	lwi333 $r0,[$r6+#0x8]
    b084:	b4 26       	lwi450 $r1,[$r6]
    b086:	8a 07       	sub45 $r0,$r7
    b088:	88 27       	add45 $r1,$r7
    b08a:	a8 32       	swi333 $r0,[$r6+#0x8]
    b08c:	b6 26       	swi450 $r1,[$r6]
    b08e:	4e 03 ff 84 	bnez $r0,af96 <__sfvwrite_r+0xac>
    b092:	f0 01       	lwi37.sp $r0,[+#0x4]
    b094:	80 26       	mov55 $r1,$r6
    b096:	49 ff f6 73 	jal 9d7c <_fflush_r>
    b09a:	4e 02 ff 7e 	beqz $r0,af96 <__sfvwrite_r+0xac>
    b09e:	48 00 00 6f 	j b17c <__sfvwrite_r+0x292>
    b0a2:	40 f7 24 06 	slt $r15,$r14,$r9
    b0a6:	80 0e       	mov55 $r0,$r14
    b0a8:	40 04 bc 1a 	cmovz $r0,$r9,$r15
    b0ac:	40 30 10 76 	divsr $r3,$r3,$r0,$r4
    b0b0:	04 53 00 09 	lwi $r5,[$r6+#0x24]
    b0b4:	f0 01       	lwi37.sp $r0,[+#0x4]
    b0b6:	a0 77       	lwi333 $r1,[$r6+#0x1c]
    b0b8:	80 4a       	mov55 $r2,$r10
    b0ba:	fe e4       	mul33 $r3,$r4
    b0bc:	dd 25       	jral5 $r5
    b0be:	80 e0       	mov55 $r7,$r0
    b0c0:	4e 06 ff 6b 	bgtz $r0,af96 <__sfvwrite_r+0xac>
    b0c4:	d5 5c       	j8 b17c <__sfvwrite_r+0x292>
    b0c6:	4e e2 00 2e 	beqz $r14,b122 <__sfvwrite_r+0x238>
    b0ca:	b4 06       	lwi450 $r0,[$r6]
    b0cc:	a0 74       	lwi333 $r1,[$r6+#0x10]
    b0ce:	e3 47       	slt45 $r10,$r7
    b0d0:	81 aa       	mov55 $r13,$r10
    b0d2:	40 d3 bc 1a 	cmovz $r13,$r7,$r15
    b0d6:	e2 20       	slt45 $r1,$r0
    b0d8:	04 93 00 02 	lwi $r9,[$r6+#0x8]
    b0dc:	a0 f5       	lwi333 $r3,[$r6+#0x14]
    b0de:	e8 2f       	beqzs8 b13c <__sfvwrite_r+0x252>
    b0e0:	89 23       	add45 $r9,$r3
    b0e2:	e1 2d       	slts45 $r9,$r13
    b0e4:	e8 2c       	beqzs8 b13c <__sfvwrite_r+0x252>
    b0e6:	80 2b       	mov55 $r1,$r11
    b0e8:	80 49       	mov55 $r2,$r9
    b0ea:	49 00 00 e1 	jal b2ac <memmove>
    b0ee:	b4 06       	lwi450 $r0,[$r6]
    b0f0:	80 26       	mov55 $r1,$r6
    b0f2:	88 09       	add45 $r0,$r9
    b0f4:	b6 06       	swi450 $r0,[$r6]
    b0f6:	f0 01       	lwi37.sp $r0,[+#0x4]
    b0f8:	49 ff f6 42 	jal 9d7c <_fflush_r>
    b0fc:	c8 40       	bnez38 $r0,b17c <__sfvwrite_r+0x292>
    b0fe:	8a e9       	sub45 $r7,$r9
    b100:	c7 37       	beqz38 $r7,b16e <__sfvwrite_r+0x284>
    b102:	80 2c       	mov55 $r1,$r12
    b104:	a0 0a       	lwi333 $r0,[$r1+#0x8]
    b106:	89 69       	add45 $r11,$r9
    b108:	8a 09       	sub45 $r0,$r9
    b10a:	8b 49       	sub45 $r10,$r9
    b10c:	a8 0a       	swi333 $r0,[$r1+#0x8]
    b10e:	4e 02 ff 4b 	beqz $r0,afa4 <__sfvwrite_r+0xba>
    b112:	4e a3 ff da 	bnez $r10,b0c6 <__sfvwrite_r+0x1dc>
    b116:	b5 68       	lwi450 $r11,[$r8]
    b118:	04 a4 00 01 	lwi $r10,[$r8+#0x4]
    b11c:	85 c0       	movi55 $r14,#0x0
    b11e:	8d 08       	addi45 $r8,#0x8
    b120:	d5 f9       	j8 b112 <__sfvwrite_r+0x228>
    b122:	80 0b       	mov55 $r0,$r11
    b124:	84 2a       	movi55 $r1,#0xa
    b126:	80 4a       	mov55 $r2,$r10
    b128:	49 00 00 b6 	jal b294 <memchr>
    b12c:	c0 04       	beqz38 $r0,b134 <__sfvwrite_r+0x24a>
    b12e:	9d c1       	addi333 $r7,$r0,#0x1
    b130:	8a eb       	sub45 $r7,$r11
    b132:	d5 03       	j8 b138 <__sfvwrite_r+0x24e>
    b134:	50 75 00 01 	addi $r7,$r10,#0x1
    b138:	85 c1       	movi55 $r14,#0x1
    b13a:	d5 c8       	j8 b0ca <__sfvwrite_r+0x1e0>
    b13c:	40 f6 8c 07 	slts $r15,$r13,$r3
    b140:	e9 0b       	bnezs8 b156 <__sfvwrite_r+0x26c>
    b142:	04 43 00 09 	lwi $r4,[$r6+#0x24]
    b146:	f0 01       	lwi37.sp $r0,[+#0x4]
    b148:	a0 77       	lwi333 $r1,[$r6+#0x1c]
    b14a:	80 4b       	mov55 $r2,$r11
    b14c:	dd 24       	jral5 $r4
    b14e:	81 20       	mov55 $r9,$r0
    b150:	4e 06 ff d7 	bgtz $r0,b0fe <__sfvwrite_r+0x214>
    b154:	d5 14       	j8 b17c <__sfvwrite_r+0x292>
    b156:	80 2b       	mov55 $r1,$r11
    b158:	80 4d       	mov55 $r2,$r13
    b15a:	49 00 00 a9 	jal b2ac <memmove>
    b15e:	a0 32       	lwi333 $r0,[$r6+#0x8]
    b160:	81 2d       	mov55 $r9,$r13
    b162:	8a 0d       	sub45 $r0,$r13
    b164:	a8 32       	swi333 $r0,[$r6+#0x8]
    b166:	b4 06       	lwi450 $r0,[$r6]
    b168:	88 0d       	add45 $r0,$r13
    b16a:	b6 06       	swi450 $r0,[$r6]
    b16c:	d5 c9       	j8 b0fe <__sfvwrite_r+0x214>
    b16e:	f0 01       	lwi37.sp $r0,[+#0x4]
    b170:	80 26       	mov55 $r1,$r6
    b172:	49 ff f6 05 	jal 9d7c <_fflush_r>
    b176:	c8 03       	bnez38 $r0,b17c <__sfvwrite_r+0x292>
    b178:	81 c7       	mov55 $r14,$r7
    b17a:	d5 c4       	j8 b102 <__sfvwrite_r+0x218>
    b17c:	a4 36       	lhi333 $r0,[$r6+#0xc]
    b17e:	58 00 00 40 	ori $r0,$r0,#0x40
    b182:	ac 36       	shi333 $r0,[$r6+#0xc]
    b184:	84 1f       	movi55 $r0,#-1
    b186:	34 3f 80 02 	fldi $fd3,[$sp+#0x8]
    b18a:	fc e2       	pop25 $r14,#16    ! {$r6~$r14, $fp, $gp, $lp}
    b18c:	84 00       	movi55 $r0,#0x0
    b18e:	dd 9e       	ret5 $lp

0000b190 <_lseek_r>:
    b190:	fc 00       	push25 $r6,#0    ! {$r6, $fp, $gp, $lp}
    b192:	84 00       	movi55 $r0,#0x0
    b194:	3c 0e 00 23 	swi.gp $r0,[+#0x8c]
    b198:	80 01       	mov55 $r0,$r1
    b19a:	80 22       	mov55 $r1,$r2
    b19c:	80 43       	mov55 $r2,$r3
    b19e:	49 00 01 67 	jal b46c <_lseek>
    b1a2:	5a 0f ff 07 	bnec $r0,#-1,b1b0 <_lseek_r+0x20>
    b1a6:	3c 1c 00 23 	lwi.gp $r1,[+#0x8c]
    b1aa:	c1 03       	beqz38 $r1,b1b0 <_lseek_r+0x20>
    b1ac:	3c 1e 0a d4 	swi.gp $r1,[+#0x2b50]
    b1b0:	fc 80       	pop25 $r6,#0    ! {$r6, $fp, $gp, $lp}

0000b1b2 <__smakebuf_r>:
    b1b2:	a4 8e       	lhi333 $r2,[$r1+#0xc]
    b1b4:	96 8e       	bmski33 $r2,#0x1
    b1b6:	c2 08       	beqz38 $r2,b1c6 <__smakebuf_r+0x14>
    b1b8:	50 00 80 43 	addi $r0,$r1,#0x43
    b1bc:	b6 01       	swi450 $r0,[$r1]
    b1be:	a8 0c       	swi333 $r0,[$r1+#0x10]
    b1c0:	84 01       	movi55 $r0,#0x1
    b1c2:	a8 0d       	swi333 $r0,[$r1+#0x14]
    b1c4:	dd 9e       	ret5 $lp
    b1c6:	fc 49       	push25 $r10,#72    ! {$r6~$r10, $fp, $gp, $lp}
    b1c8:	80 c1       	mov55 $r6,$r1
    b1ca:	22 10 80 07 	lhsi $r1,[$r1+#0xe]
    b1ce:	f0 81       	swi37.sp $r0,[+#0x4]
    b1d0:	4e 14 00 0a 	bgez $r1,b1e4 <__smakebuf_r+0x32>
    b1d4:	22 03 00 06 	lhsi $r0,[$r6+#0xc]
    b1d8:	54 10 00 80 	andi $r1,$r0,#0x80
    b1dc:	c9 0a       	bnez38 $r1,b1f0 <__smakebuf_r+0x3e>
    b1de:	44 70 04 00 	movi $r7,#0x400
    b1e2:	d5 09       	j8 b1f4 <__smakebuf_r+0x42>
    b1e4:	b0 83       	addri36.sp $r2,#0xc
    b1e6:	49 00 01 0a 	jal b3fa <_fstat_r>
    b1ea:	4e 04 00 0a 	bgez $r0,b1fe <__smakebuf_r+0x4c>
    b1ee:	d5 f3       	j8 b1d4 <__smakebuf_r+0x22>
    b1f0:	44 70 00 40 	movi $r7,#0x40
    b1f4:	58 00 08 00 	ori $r0,$r0,#0x800
    b1f8:	ac 36       	shi333 $r0,[$r6+#0xc]
    b1fa:	85 20       	movi55 $r9,#0x0
    b1fc:	d5 1f       	j8 b23a <__smakebuf_r+0x88>
    b1fe:	f5 04       	lwi37.sp $r5,[+#0x10]
    b200:	44 00 f0 00 	movi $r0,#0xf000
    b204:	ff 46       	and33 $r5,$r0
    b206:	50 92 e0 00 	addi $r9,$r5,#-8192
    b20a:	44 10 80 00 	movi $r1,#0x8000
    b20e:	5c 94 80 01 	slti $r9,$r9,#0x1
    b212:	a4 36       	lhi333 $r0,[$r6+#0xc]
    b214:	d9 0e       	bnes38 $r1,b230 <__smakebuf_r+0x7e>
    b216:	04 53 00 0a 	lwi $r5,[$r6+#0x28]
    b21a:	44 10 a1 c6 	movi $r1,#0xa1c6
    b21e:	d9 09       	bnes38 $r1,b230 <__smakebuf_r+0x7e>
    b220:	58 00 04 00 	ori $r0,$r0,#0x400
    b224:	44 70 04 00 	movi $r7,#0x400
    b228:	ac 36       	shi333 $r0,[$r6+#0xc]
    b22a:	14 73 00 13 	swi $r7,[$r6+#0x4c]
    b22e:	d5 06       	j8 b23a <__smakebuf_r+0x88>
    b230:	58 00 08 00 	ori $r0,$r0,#0x800
    b234:	ac 36       	shi333 $r0,[$r6+#0xc]
    b236:	44 70 04 00 	movi $r7,#0x400
    b23a:	f0 01       	lwi37.sp $r0,[+#0x4]
    b23c:	80 27       	mov55 $r1,$r7
    b23e:	49 ff f7 35 	jal a0a8 <_malloc_r>
    b242:	c8 10       	bnez38 $r0,b262 <__smakebuf_r+0xb0>
    b244:	22 03 00 06 	lhsi $r0,[$r6+#0xc]
    b248:	54 10 02 00 	andi $r1,$r0,#0x200
    b24c:	c9 22       	bnez38 $r1,b290 <__smakebuf_r+0xde>
    b24e:	58 00 00 02 	ori $r0,$r0,#0x2
    b252:	ac 36       	shi333 $r0,[$r6+#0xc]
    b254:	50 03 00 43 	addi $r0,$r6,#0x43
    b258:	b6 06       	swi450 $r0,[$r6]
    b25a:	a8 34       	swi333 $r0,[$r6+#0x10]
    b25c:	84 01       	movi55 $r0,#0x1
    b25e:	a8 35       	swi333 $r0,[$r6+#0x14]
    b260:	fc c9       	pop25 $r10,#72    ! {$r6~$r10, $fp, $gp, $lp}
    b262:	44 10 9d bc 	movi $r1,#0x9dbc
    b266:	3c 1e 0a d7 	swi.gp $r1,[+#0x2b5c]
    b26a:	a4 76       	lhi333 $r1,[$r6+#0xc]
    b26c:	b6 06       	swi450 $r0,[$r6]
    b26e:	58 10 80 80 	ori $r1,$r1,#0x80
    b272:	ac 76       	shi333 $r1,[$r6+#0xc]
    b274:	a8 34       	swi333 $r0,[$r6+#0x10]
    b276:	a9 f5       	swi333 $r7,[$r6+#0x14]
    b278:	4e 92 00 0c 	beqz $r9,b290 <__smakebuf_r+0xde>
    b27c:	f0 01       	lwi37.sp $r0,[+#0x4]
    b27e:	22 13 00 07 	lhsi $r1,[$r6+#0xe]
    b282:	49 00 00 cc 	jal b41a <_isatty_r>
    b286:	c0 05       	beqz38 $r0,b290 <__smakebuf_r+0xde>
    b288:	a4 36       	lhi333 $r0,[$r6+#0xc]
    b28a:	58 00 00 01 	ori $r0,$r0,#0x1
    b28e:	ac 36       	shi333 $r0,[$r6+#0xc]
    b290:	fc c9       	pop25 $r10,#72    ! {$r6~$r10, $fp, $gp, $lp}
	...

0000b294 <memchr>:
    b294:	96 48       	zeb33 $r1,$r1
    b296:	99 42       	add333 $r5,$r0,$r2
    b298:	d0 07       	beqs38 $r0,b2a6 <memchr+0x12>
    b29a:	08 40 00 01 	lbi.bi $r4,[$r0],#0x1
    b29e:	4c 40 ff fd 	bne $r4,$r1,b298 <memchr+0x4>
    b2a2:	9e 01       	subi333 $r0,$r0,#0x1
    b2a4:	dd 9e       	ret5 $lp
    b2a6:	84 00       	movi55 $r0,#0x0
    b2a8:	dd 9e       	ret5 $lp
    b2aa:	92 00       	nop16

0000b2ac <memmove>:
    b2ac:	3a 6f c0 bc 	smw.adm $r6,[$sp],$r16,#0x2    ! {$r6~$r16, $lp}
    b2b0:	84 c0       	movi55 $r6,#0x0
    b2b2:	80 e0       	mov55 $r7,$r0
    b2b4:	c2 51       	beqz38 $r2,b356 <memmove+0xaa>
    b2b6:	e2 e1       	slt45 $r7,$r1
    b2b8:	e9 05       	bnezs8 b2c2 <memmove+0x16>
    b2ba:	99 fa       	add333 $r7,$r7,$r2
    b2bc:	98 4a       	add333 $r1,$r1,$r2
    b2be:	84 60       	movi55 $r3,#0x0
    b2c0:	d5 02       	j8 b2c4 <memmove+0x18>
    b2c2:	84 61       	movi55 $r3,#0x1
    b2c4:	54 43 80 03 	andi $r4,$r7,#0x3
    b2c8:	54 50 80 03 	andi $r5,$r1,#0x3
    b2cc:	fa 94       	movpi45 $r4,#0x24
    b2ce:	e2 44       	slt45 $r2,$r4
    b2d0:	e9 2c       	bnezs8 b328 <memmove+0x7c>
    b2d2:	c5 0c       	beqz38 $r5,b2ea <memmove+0x3e>
    b2d4:	c3 03       	beqz38 $r3,b2da <memmove+0x2e>
    b2d6:	52 52 80 04 	subri $r5,$r5,#0x4
    b2da:	81 02       	mov55 $r8,$r2
    b2dc:	80 45       	mov55 $r2,$r5
    b2de:	84 c1       	movi55 $r6,#0x1
    b2e0:	48 00 00 24 	j b328 <memmove+0x7c>
    b2e4:	84 c0       	movi55 $r6,#0x0
    b2e6:	40 24 08 01 	sub $r2,$r8,$r2
    b2ea:	40 41 14 09 	srli $r4,$r2,#0x5
    b2ee:	95 25       	slli333 $r4,$r4,#0x5
    b2f0:	54 51 00 1f 	andi $r5,$r2,#0x1f
    b2f4:	98 8c       	add333 $r2,$r1,$r4
    b2f6:	9b 0c       	sub333 $r4,$r1,$r4
    b2f8:	9f 24       	subi333 $r4,$r4,#0x4
    b2fa:	40 22 0c 1a 	cmovz $r2,$r4,$r3
    b2fe:	cb 0d       	bnez38 $r3,b318 <memmove+0x6c>
    b300:	8e 24       	subi45 $r1,#0x4
    b302:	9f fc       	subi333 $r7,$r7,#0x4
    b304:	3a 90 c0 0c 	lmw.bdm $r9,[$r1],$r16,#0x0    ! {$r9~$r16}
    b308:	3a 93 c0 2c 	smw.bdm $r9,[$r7],$r16,#0x0    ! {$r9~$r16}
    b30c:	4c 11 7f fc 	bne $r1,$r2,b304 <memmove+0x58>
    b310:	9d fc       	addi333 $r7,$r7,#0x4
    b312:	9c 4c       	addi333 $r1,$r1,#0x4
    b314:	48 00 00 08 	j b324 <memmove+0x78>
    b318:	3a 90 c0 04 	lmw.bim $r9,[$r1],$r16,#0x0    ! {$r9~$r16}
    b31c:	3a 93 c0 24 	smw.bim $r9,[$r7],$r16,#0x0    ! {$r9~$r16}
    b320:	4c 11 7f fc 	bne $r1,$r2,b318 <memmove+0x6c>
    b324:	c5 19       	beqz38 $r5,b356 <memmove+0xaa>
    b326:	80 45       	mov55 $r2,$r5
    b328:	84 a0       	movi55 $r5,#0x0
    b32a:	c2 15       	beqz38 $r2,b354 <memmove+0xa8>
    b32c:	4e 32 00 0a 	beqz $r3,b340 <memmove+0x94>
    b330:	08 40 80 01 	lbi.bi $r4,[$r1],#0x1
    b334:	18 43 80 01 	sbi.bi $r4,[$r7],#0x1
    b338:	8c a1       	addi45 $r5,#0x1
    b33a:	da fb       	bnes38 $r2,b330 <memmove+0x84>
    b33c:	48 00 00 0c 	j b354 <memmove+0xa8>
    b340:	8e 21       	subi45 $r1,#0x1
    b342:	9f f9       	subi333 $r7,$r7,#0x1
    b344:	08 40 ff ff 	lbi.bi $r4,[$r1],#-1
    b348:	18 43 ff ff 	sbi.bi $r4,[$r7],#-1
    b34c:	8c a1       	addi45 $r5,#0x1
    b34e:	da fb       	bnes38 $r2,b344 <memmove+0x98>
    b350:	8c 21       	addi45 $r1,#0x1
    b352:	8c e1       	addi45 $r7,#0x1
    b354:	ce c8       	bnez38 $r6,b2e4 <memmove+0x38>
    b356:	3a 6f c0 84 	lmw.bim $r6,[$sp],$r16,#0x2    ! {$r6~$r16, $lp}
    b35a:	dd 9e       	ret5 $lp

0000b35c <_realloc_r>:
    b35c:	fc 41       	push25 $r10,#8    ! {$r6~$r10, $fp, $gp, $lp}
    b35e:	f0 81       	swi37.sp $r0,[+#0x4]
    b360:	81 21       	mov55 $r9,$r1
    b362:	80 e2       	mov55 $r7,$r2
    b364:	c9 05       	bnez38 $r1,b36e <_realloc_r+0x12>
    b366:	80 22       	mov55 $r1,$r2
    b368:	49 ff f6 a0 	jal a0a8 <_malloc_r>
    b36c:	fc c1       	pop25 $r10,#8    ! {$r6~$r10, $fp, $gp, $lp}
    b36e:	ca 05       	bnez38 $r2,b378 <_realloc_r+0x1c>
    b370:	49 ff f6 60 	jal a030 <_free_r>
    b374:	80 07       	mov55 $r0,$r7
    b376:	fc c1       	pop25 $r10,#8    ! {$r6~$r10, $fp, $gp, $lp}
    b378:	49 00 00 60 	jal b438 <_malloc_usable_size_r>
    b37c:	e2 07       	slt45 $r0,$r7
    b37e:	e8 10       	beqzs8 b39e <_realloc_r+0x42>
    b380:	f0 01       	lwi37.sp $r0,[+#0x4]
    b382:	80 27       	mov55 $r1,$r7
    b384:	49 ff f6 92 	jal a0a8 <_malloc_r>
    b388:	80 c0       	mov55 $r6,$r0
    b38a:	c0 0c       	beqz38 $r0,b3a2 <_realloc_r+0x46>
    b38c:	80 29       	mov55 $r1,$r9
    b38e:	80 47       	mov55 $r2,$r7
    b390:	49 ff f5 e2 	jal 9f54 <memcpy>
    b394:	f0 01       	lwi37.sp $r0,[+#0x4]
    b396:	80 29       	mov55 $r1,$r9
    b398:	49 ff f6 4c 	jal a030 <_free_r>
    b39c:	d5 03       	j8 b3a2 <_realloc_r+0x46>
    b39e:	80 09       	mov55 $r0,$r9
    b3a0:	fc c1       	pop25 $r10,#8    ! {$r6~$r10, $fp, $gp, $lp}
    b3a2:	80 06       	mov55 $r0,$r6
    b3a4:	fc c1       	pop25 $r10,#8    ! {$r6~$r10, $fp, $gp, $lp}

0000b3a6 <nds_isalpha>:
    b3a6:	66 00 00 20 	bitci $r0,$r0,#0x20
    b3aa:	50 00 7f bf 	addi $r0,$r0,#-65
    b3ae:	5c 00 00 1a 	slti $r0,$r0,#0x1a
    b3b2:	dd 9e       	ret5 $lp

0000b3b4 <nds_isdigit>:
    b3b4:	50 00 7f d0 	addi $r0,$r0,#-48
    b3b8:	5c 00 00 0a 	slti $r0,$r0,#0xa
    b3bc:	dd 9e       	ret5 $lp

0000b3be <nds_isspace>:
    b3be:	5a 00 20 06 	beqc $r0,#0x20,b3ca <nds_isspace+0xc>
    b3c2:	8e 09       	subi45 $r0,#0x9
    b3c4:	5c 00 00 05 	slti $r0,$r0,#0x5
    b3c8:	dd 9e       	ret5 $lp
    b3ca:	84 01       	movi55 $r0,#0x1
    b3cc:	dd 9e       	ret5 $lp

0000b3ce <nds_isupper>:
    b3ce:	50 00 7f bf 	addi $r0,$r0,#-65
    b3d2:	5c 00 00 1a 	slti $r0,$r0,#0x1a
    b3d6:	dd 9e       	ret5 $lp

0000b3d8 <_read_r>:
    b3d8:	fc 00       	push25 $r6,#0    ! {$r6, $fp, $gp, $lp}
    b3da:	84 00       	movi55 $r0,#0x0
    b3dc:	3c 0e 00 23 	swi.gp $r0,[+#0x8c]
    b3e0:	80 01       	mov55 $r0,$r1
    b3e2:	80 22       	mov55 $r1,$r2
    b3e4:	80 43       	mov55 $r2,$r3
    b3e6:	49 00 00 3b 	jal b45c <_read>
    b3ea:	5a 0f ff 07 	bnec $r0,#-1,b3f8 <_read_r+0x20>
    b3ee:	3c 1c 00 23 	lwi.gp $r1,[+#0x8c]
    b3f2:	c1 03       	beqz38 $r1,b3f8 <_read_r+0x20>
    b3f4:	3c 1e 0a d4 	swi.gp $r1,[+#0x2b50]
    b3f8:	fc 80       	pop25 $r6,#0    ! {$r6, $fp, $gp, $lp}

0000b3fa <_fstat_r>:
    b3fa:	fc 00       	push25 $r6,#0    ! {$r6, $fp, $gp, $lp}
    b3fc:	84 00       	movi55 $r0,#0x0
    b3fe:	3c 0e 00 23 	swi.gp $r0,[+#0x8c]
    b402:	80 01       	mov55 $r0,$r1
    b404:	80 22       	mov55 $r1,$r2
    b406:	49 00 00 37 	jal b474 <_fstat>
    b40a:	5a 0f ff 07 	bnec $r0,#-1,b418 <_fstat_r+0x1e>
    b40e:	3c 1c 00 23 	lwi.gp $r1,[+#0x8c]
    b412:	c1 03       	beqz38 $r1,b418 <_fstat_r+0x1e>
    b414:	3c 1e 0a d4 	swi.gp $r1,[+#0x2b50]
    b418:	fc 80       	pop25 $r6,#0    ! {$r6, $fp, $gp, $lp}

0000b41a <_isatty_r>:
    b41a:	fc 00       	push25 $r6,#0    ! {$r6, $fp, $gp, $lp}
    b41c:	84 00       	movi55 $r0,#0x0
    b41e:	3c 0e 00 23 	swi.gp $r0,[+#0x8c]
    b422:	80 01       	mov55 $r0,$r1
    b424:	49 00 00 2c 	jal b47c <_isatty>
    b428:	5a 0f ff 07 	bnec $r0,#-1,b436 <_isatty_r+0x1c>
    b42c:	3c 1c 00 23 	lwi.gp $r1,[+#0x8c]
    b430:	c1 03       	beqz38 $r1,b436 <_isatty_r+0x1c>
    b432:	3c 1e 0a d4 	swi.gp $r1,[+#0x2b50]
    b436:	fc 80       	pop25 $r6,#0    ! {$r6, $fp, $gp, $lp}

0000b438 <_malloc_usable_size_r>:
    b438:	04 00 ff ff 	lwi $r0,[$r1+#-4]
    b43c:	4e 04 00 06 	bgez $r0,b448 <_malloc_usable_size_r+0x10>
    b440:	88 20       	add45 $r1,$r0
    b442:	04 10 ff ff 	lwi $r1,[$r1+#-4]
    b446:	88 01       	add45 $r0,$r1
    b448:	8e 04       	subi45 $r0,#0x4
    b44a:	dd 9e       	ret5 $lp

0000b44c <_exit>:
    b44c:	64 00 00 2b 	syscall #0x1
    b450:	d5 00       	j8 b450 <_exit+0x4>
    b452:	92 00       	nop16

0000b454 <_close>:
    b454:	64 00 00 6b 	syscall #0x3
    b458:	48 00 00 34 	j b4c0 <__syscall_error_handler>

0000b45c <_read>:
    b45c:	64 00 00 8b 	syscall #0x4
    b460:	48 00 00 30 	j b4c0 <__syscall_error_handler>

0000b464 <_write>:
    b464:	64 00 00 ab 	syscall #0x5
    b468:	48 00 00 2c 	j b4c0 <__syscall_error_handler>

0000b46c <_lseek>:
    b46c:	64 00 00 cb 	syscall #0x6
    b470:	48 00 00 28 	j b4c0 <__syscall_error_handler>

0000b474 <_fstat>:
    b474:	64 00 01 4b 	syscall #0xa
    b478:	48 00 00 24 	j b4c0 <__syscall_error_handler>

0000b47c <_isatty>:
    b47c:	64 01 77 4b 	syscall #0xbba
    b480:	c8 06       	bnez38 $r0,b48c <_isatty+0x10>
    b482:	64 02 ee 2b 	syscall #0x1771
    b486:	3c 0e 0a d4 	swi.gp $r0,[+#0x2b50]
    b48a:	84 00       	movi55 $r0,#0x0
    b48c:	dd 9e       	ret5 $lp
    b48e:	92 00       	nop16

0000b490 <_sbrk>:
    b490:	3c 1c 0a d9 	lwi.gp $r1,[+#0x2b64]
    b494:	c9 05       	bnez38 $r1,b49e <_sbrk+0xe>
    b496:	3e 18 35 80 	addi.gp $r1,#0x3580
    b49a:	3c 1e 0a d9 	swi.gp $r1,[+#0x2b64]
    b49e:	9c 07       	addi333 $r0,$r0,#0x7
    b4a0:	92 03       	srli45 $r0,#0x3
    b4a2:	94 03       	slli333 $r0,$r0,#0x3
    b4a4:	98 08       	add333 $r0,$r1,$r0
    b4a6:	40 2f 80 06 	slt $r2,$sp,$r0
    b4aa:	ca 05       	bnez38 $r2,b4b4 <_sbrk+0x24>
    b4ac:	3c 0e 0a d9 	swi.gp $r0,[+#0x2b64]
    b4b0:	80 01       	mov55 $r0,$r1
    b4b2:	dd 9e       	ret5 $lp
    b4b4:	84 0c       	movi55 $r0,#0xc
    b4b6:	3c 0e 0a d4 	swi.gp $r0,[+#0x2b50]
    b4ba:	84 1f       	movi55 $r0,#-1
    b4bc:	dd 9e       	ret5 $lp
    b4be:	92 00       	nop16

0000b4c0 <__syscall_error_handler>:
    b4c0:	9c 41       	addi333 $r1,$r0,#0x1
    b4c2:	c9 06       	bnez38 $r1,b4ce <__syscall_error_handler+0xe>
    b4c4:	64 02 ee 2b 	syscall #0x1771
    b4c8:	3c 0e 0a d4 	swi.gp $r0,[+#0x2b50]
    b4cc:	84 1f       	movi55 $r0,#-1
    b4ce:	dd 9e       	ret5 $lp
