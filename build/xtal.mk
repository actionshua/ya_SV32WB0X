
XTAL := -DXTAL=26 -DROM_XTAL=0
####################################################################

ifeq ($(strip $(BOARD)), SSV6020A_S292_19M)
XTAL := -DXTAL=192 -DROM_XTAL=4
endif

ifeq ($(strip $(BOARD)), SSV6020A_S292_20M)
XTAL := -DXTAL=20 -DROM_XTAL=6
endif

ifeq ($(strip $(BOARD)), SSV6020A_S292_24M)
XTAL := -DXTAL=24 -DROM_XTAL=5
endif

ifeq ($(strip $(BOARD)), SSV6020A_S292_25M)
XTAL := -DXTAL=25 -DROM_XTAL=0
endif

ifeq ($(strip $(BOARD)), SSV6020A_S292_26M)
XTAL := -DXTAL=26 -DROM_XTAL=2
endif

ifeq ($(strip $(BOARD)), SSV6020A_S292_38M)
XTAL := -DXTAL=384 -DROM_XTAL=7
endif

ifeq ($(strip $(BOARD)), SSV6020A_S292_40M)
XTAL := -DXTAL=40 -DROM_XTAL=1
endif

ifeq ($(strip $(BOARD)), SSV6020A_S292_52M)
XTAL := -DXTAL=52 -DROM_XTAL=3
endif

_BOARD_XILINX_ALL_LIST := \
	TURISMO_E_FPGA \
	TURISMO_E_FPGAv2 \
	TURISMO_E_FPGAv3

ifeq ($(strip $(BOARD)),$(filter $(strip $(BOARD)), $(_BOARD_XILINX_ALL_LIST)))
XTAL := -DXTAL=24 -DROM_XTAL=5
endif

####################################################################

ifeq ($(strip $(BOARD)), SSV6006_SHUTTLE_S197_25M)
XTAL := -DXTAL=25 -DROM_XTAL=0
endif

ifeq ($(strip $(BOARD)), SSV6006_SHUTTLE_S197_40M)
XTAL := -DXTAL=40 -DROM_XTAL=1
endif

####################################################################
_BOARD_SSV6020B_26M_ALL_LIST := \
	SV6020B_P40_26M \
	SV6020B_P52_26M

ifeq ($(strip $(BOARD)),$(filter $(strip $(BOARD)), $(_BOARD_SSV6020B_26M_ALL_LIST)))
XTAL := -DXTAL=26 -DROM_XTAL=2
endif

_BOARD_SSV6020C_26M_ALL_LIST := \
	SV6020C_P32_26M \
	SV6020C_P40_26M \
	SV6020C_P60_26M \
	SV32WB01_26M \
	SV32WB03_26M \
	SV32WB05_26M \
	SV32WB06_26M \
	WB02_26M

_BOARD_SSV6020C_40M_ALL_LIST := \
	SV6020C_P32_40M \
	SV6020C_P40_40M \
	SV6020C_P60_40M \
	SV32WB01_40M \
	SV32WB03_40M \
	SV32WB05_40M \
	SV32WB06_40M \
	WB02_40M

_BOARD_SSV6020C_24M_ALL_LIST := \
	SV6020C_P32_24M \
	SV6020C_P40_24M \
	SV6020C_P60_24M \
	SV32WB01_24M \
	SV32WB03_24M \
	SV32WB05_24M \
	SV32WB06_24M \
	WB02_24M

ifeq ($(strip $(BOARD)),$(filter $(strip $(BOARD)), $(_BOARD_SSV6020C_26M_ALL_LIST)))
XTAL := -DXTAL=26 -DROM_XTAL=2
endif

ifeq ($(strip $(BOARD)),$(filter $(strip $(BOARD)), $(_BOARD_SSV6020C_40M_ALL_LIST)))
XTAL := -DXTAL=40 -DROM_XTAL=1
endif

ifeq ($(strip $(BOARD)),$(filter $(strip $(BOARD)), $(_BOARD_SSV6020C_24M_ALL_LIST)))
XTAL := -DXTAL=24 -DROM_XTAL=5
endif

