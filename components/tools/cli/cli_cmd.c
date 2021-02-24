//#define __SFILE__ "cli_cmd.c"
#include "soc_types.h"
#include "cli.h"
#include "osal.h"
#if defined(SUPPORT_FFS)
#include "fsal.h"
#endif



/*---------------------------------- CMDs -----------------------------------*/
u32 ssv6xxx_atoi_base( const s8 *s, u32 base );
s32 ssv6xxx_atoi( const s8 *s );
void hex_dump (const void *addr, u32 size);






static bool cmd_raw_dump_ex(char *data, s32 len, bool with_addr, u8 addr_radix, char line_cols, u8 radix)
{
    int i;

	// check input parameters
	if ((addr_radix != 10) && (addr_radix != 16))
	{
		printf("%s(): invalid value 'addr_radix' = %d\n\r", __FUNCTION__, addr_radix);
		return false;
	}
	if ((line_cols != 8) && (line_cols != 10) && (line_cols != 16) && (line_cols != -1))
	{
		printf("%s(): invalid value 'line_cols' = %d\n\r", __FUNCTION__, line_cols);
		return false;
	}
	if ((radix != 10) && (radix != 16))
	{
		printf("%s(): invalid value 'radix' = %d\n\r", __FUNCTION__, radix);
		return false;
	}

	if (len == 0)	return true;

	// if ONLY have one line
	if (line_cols == -1)
	{
		//LOG_TAG_SUPPRESS_ON();
		// only print addr heading at one time
		if ((with_addr == true))
		{
			if      (addr_radix == 10)	printf("%08d: ", 0);
			else if (addr_radix == 16)	printf("0x%08x: ", 0);
		}

		for (i=0; i<len; i++)
		{
			// print data
			if	    (radix == 10)	printf("%4d ",  (u8)data[i]);
			else if (radix == 16)	printf("%02x ", (u8)data[i]);
		}
		printf("\n\r");
		//LOG_TAG_SUPPRESS_OFF();
		return true;
	}

	// normal case
	//LOG_TAG_SUPPRESS_ON();
    for (i=0; i<len; i++)
	{
		// print addr heading
		if ((with_addr == true) && (i % line_cols) == 0)
		{
			if      (addr_radix == 10)	printf("%08d: ", i);
			else if (addr_radix == 16)	printf("0x%08x: ", i);
		}
		// print data
		if	    (radix == 10)	printf("%4d ",  (u8)data[i]);
		else if (radix == 16)	printf("%02x ", (u8)data[i]);
		// print newline
        if (((i+1) % line_cols) == 0)
            printf("\n\r");
    }
    printf("\n\r");
	//LOG_TAG_SUPPRESS_OFF();
	return true;
}
static void cmd_raw_dump(char *data, s32 len)
{
	cmd_raw_dump_ex(data, len, true, 10, 10, 16);
	return;
}


// r addr [size]
static int Cmd_Read(s32 argc, char *argv[])
{
    static u32 read_size = 1;
    static u32 read_addr = 0xCD010000;

    if (argc < 2)
    {
        //printf("Usage: r addr [size]\n");
        hex_dump((const u32 *)read_addr, read_size);
        return -1;
    }

    read_addr = (u32)ssv6xxx_atoi_base((s8*)argv[1], 16);
    if (argc > 2)
        read_size = (u32)ssv6xxx_atoi((s8*)argv[2]);
    else
        read_size = 1;

    read_addr &= 0xFFFFFFE0;
    read_size = (read_size+7)&0xFFFFFFF8;
    hex_dump((const u32 *)read_addr, read_size);
    
    return 0;
} // end of - Cmd_Read -

// w addr value
static int Cmd_Write(s32 argc, char *argv[])
{
    volatile u32 *write_addr;
    u32           value;

    if (argc != 3)
    {
        printf("Usage: w addr value\n");
        return -1;
    }

    write_addr = (volatile u32 *)ssv6xxx_atoi_base((s8*)argv[1], 16);
    value = (u32)ssv6xxx_atoi_base((s8*)argv[2], 16);
    *write_addr = value;
    printf("\n    %08X => %08X : %08X\n", value, (u32)write_addr, *write_addr);
    return 0;
} // end of - Cmd_Write

typedef struct _stParam
{
	char *argv[10];
	int	argc;
} stParam;

static int Cmd_echo(s32 argc, char *argv[])
{
	int loop_i;
	for (loop_i = 0;loop_i < argc; loop_i++) {
		printf("argv[%d] = %s\n", loop_i, argv[loop_i]);
	}
    return 0;
}

static int Cmd_Sysinfo(s32 argc, char *argv[])
{
    printf("\n");
    OS_SysInfo();
    return 0;    
}

static int Cmd_Meminfo(s32 argc, char *argv[])
{
    printf("\n");
    OS_MemInfo();
    return 0;
}

#if defined(SUPPORT_FFS)
extern SSV_FS fs_handle;
#endif

static int Cmd_Fsinfo(s32 argc, char *argv[])
{
	printf("\n");
#if defined(SUPPORT_FFS)
	FS_list(fs_handle);
#else
    printf("[%s] filesystem feature disabled.\n", __func__);
#endif
	return 0;
}

static int Cmd_Fsreset(s32 argc, char *argv[])
{
	printf("\n");
#if defined(SUPPORT_FFS)
	fs_handle = FS_reset();
#else
    printf("[%s] filesystem feature disabled.\n", __func__);
#endif
	return 0;
}

static int Cmd_MemoryDump(s32 argc, char *argv[])
{
    unsigned int address = 0;
    unsigned int len = 0;
    printf("\r\n");
    if(argc <2)
    {
        printf("md [address] [size]\r\n");
        return -1;
    }
    address = strtoul(argv[1], NULL, 16);
    len = strtoul(argv[2], NULL, 16);
    printf("\r\n");
    printf("md 0x%x 0x%x\r\n",address,len);
    cmd_raw_dump((char*)address, (s32)len);
    return 0;
}

/* ---------------------- Registered CMDs to CMD Table ---------------------- */
extern void _notify_host_reset();


const CLICmds gCliCmdTable[] =
{
    { "echo", Cmd_echo, "echo"},
    { "r",              Cmd_Read,           "Read memory or register."},
    { "w",              Cmd_Write,          "Write memory or register."},
    
    { "sysinfo",              Cmd_Sysinfo,          "Show System Information."},
    { "meminfo",              Cmd_Meminfo,          "Show Memory Information."},
    { "fsinfo",              Cmd_Fsinfo,          "Show Filesystem Information."},
    { "fsreset",              Cmd_Fsreset,          "Filesystem Reset."},
    { "md",              Cmd_MemoryDump,          "Memory Dump."},
    
    /*lint -save -e611 */
    { (const char *)NULL, (CliCmdFunc)NULL,   (const char *)NULL },
    /*lint -restore */
};




