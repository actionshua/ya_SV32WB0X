#include <sys/time.h>
#ifdef __MINGW32__
#include <winsock2.h>  // for Sleep()
#endif
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "util.h"
#include "flash.h"
#include <stdint.h>

unsigned char swd_unlock[16] = {};
unsigned char do_swd_unlock = 0;
uint32_t sram_test_size = 0;

//-------------------------------------------------------------------------------------------------
/* Help menu */
int usage(void)
{
  printf( "--port:\t\t\tPort number to connect with ICEman (default to 2354)\n");
  printf( "--read-all:\t\t\tRead entire flash content\n");
  printf( "--unlock:\t\t\tunlock password\n");
  printf( "--addr:\t\t\tFlash target address (default to 0x0)\n");
  printf( "--test-sram:\t\t\ttest sram (setting test size)\n");
  printf( "--image:\t\tImage name to burn\n");
  printf( "--erase-all:\t\tErase entire flash before burning\n");
  printf( "--reset-to-start:\t\treset the system\n");
  printf( "--chip:\t\tselect chip\n");
  printf( "--help:\t\t\tThe usage for NDS32 Burner\n");
  return 0;
}

/* Log file descriptor */
FILE *pLogFile;
int coreid = 0;
int chip = 6006;

/* option structure */
static struct option long_option[] =
{
  {"port", required_argument, 0, 'p'},
  {"unlock", optional_argument, 0, 'u'},
  {"read-all", required_argument, 0, 'r'},
  {"addr", required_argument, 0, 'a'},
  {"test-sram", required_argument, 0, 't'},
  {"image", required_argument, 0, 'i'},
  {"chip", required_argument, 0, 'c'},
  {"erase-all", no_argument, 0, 'e'},
  {"reset-to-start", no_argument, 0, 's'},
  {"help", no_argument, 0, 'h'},
  {0, 0, 0, 0}
};

/* main function 
 *  . parse parameters
 *  . initial socket
 *  . select target coreid
 *  . reset AICE 
 *  . issue RESET_HOLD to let target board restore to reset status 
 *    avoid boot code to damage flash registers' settings 
 *  . call target-dependent initial function and calculate flash base address (Device Address) 
 *     xc5()/p24()/ag101()/ag301p() 
 *  . read image binary data from --image specified file 
 *  . if user specifies --verify-only, verify the target with the image data and exit 
 *  . preserve first/last blocks if needed (As start/end addresses are not block-aligned)
 *  . erase flash
 *  . burn image - call Flash_BurnImage()
 *  . verify    */
int main(int argc, char **argv)
{
  pLogFile = stdout;
  int c = 0;
  unsigned int port = 2354;
  unsigned int readall = 0;
  unsigned int read_addr = 0;
  unsigned char *readbuf = (unsigned char*)malloc(FLASH_SECTOR_SIZE*sizeof(char));
  unsigned int address = 0;             /* default write to flash base */
  unsigned int size = 0;                /* image size */
  unsigned int program_size = 0;
  unsigned int writelength;
  unsigned int flashaddr;
  unsigned int erase_size;              /* erase size */
  unsigned int erase_addr;				/* erase addr */
  unsigned char *start = NULL;          /* image pointer */
  unsigned char *content = NULL;
  FILE *image = NULL;                   /* image to burn */
  char *name = (char*)malloc(1024*sizeof(char));
  int erase_all = 0;

  int rst = 0;
  
  struct timeval erase_begin_time;
  struct timeval erase_end_time;
  struct timeval erase_total_time;
  double erase_time_sec;
  
  struct timeval burn_begin_time;
  struct timeval burn_end_time;
  struct timeval burn_total_time;
  double burn_time_sec;

  /* parameter handler */
  while(1)
  {
    int option_index;
    c = getopt_long(argc, argv, "p:u::r:a:t:i:ehs", long_option, &option_index);
    if (c == EOF)
      break;

    switch (c)
    {
	  case 'p':
      port = strtol(optarg, NULL, 0);
      fprintf(pLogFile, "Port number to connect with ICEman: 0x%x",port);
      break;
	  
	  case 'r':
      if (strncmp(optarg, "/cygdrive/", 10) == 0)
      {
        name[0] = optarg[10];
        name[1] = ':';
        name[2] = '\0';
        strcat(name, optarg + 11);
      }
      else
	  {
        name = optarg;
	  }
      if ((image = fopen(name, "w+b"))== NULL)
      {
        fprintf (pLogFile, "Error: can't open file %s\n", optarg);
        fflush(pLogFile);
        exit(1);
      }
	  fprintf (pLogFile, "open file %s\n", optarg);
	  readall = 1;
      break;
      case 'c':
      chip=strtol(optarg, NULL, 10);
      fprintf(pLogFile, "write chip: %d\n", chip);
      break;
	
	  case 'a':
      address = strtol(optarg, NULL, 16);
      fprintf(pLogFile, "target address: 0x%x\n",address);
      break;
      case 't':
      if (optarg[1] == 'x' && optarg[0] == '0') {
          sram_test_size = strtol(optarg, NULL, 16);
      } else {
          sram_test_size = strtol(optarg, NULL, 10);
      }
      fprintf(pLogFile, "sram test size: 0x%x\n", sram_test_size);
      break;
	  
      case 'i':
      if (strncmp(optarg, "/cygdrive/", 10) == 0)
      {
        name[0] = optarg[10];
        name[1] = ':';
        name[2] = '\0';
        strcat(name, optarg + 11);
      }
      else
	  {
        name = optarg;
	  }
      if ((image = fopen(name, "rb"))== NULL)
      {
        fprintf (pLogFile, "Error: can't open file %s\n", optarg);
        fflush(pLogFile);
        exit(1);
      }
	  fprintf (pLogFile, "open file %s\n", optarg);
      break;	  
	  
      case 'e':
      erase_all = 1;
      break;
      case 's':
      rst = 1;
      break;
      case 'u':
      {
          do_swd_unlock = 1;
          unsigned char buf[3];
          int idx = 0;
          if (optarg && (optarg[0] != '=')) {
              fprintf(pLogFile, "swd password:");
              for (idx = 0; idx < 16; idx++) {
                  strncpy(buf, &optarg[idx*2], 2);
                  swd_unlock[idx] = strtol(buf, NULL, 16);
                  fprintf(pLogFile, " %Xh", swd_unlock[idx]);
              }
              fprintf(pLogFile, "\n");
          } else {
                swd_unlock[0] = 0xAA;
                swd_unlock[1] = 0x23;
                swd_unlock[2] = 0x45;
                swd_unlock[3] = 0x67;
                swd_unlock[4] = 0x89;
                swd_unlock[5] = 0x56;
                swd_unlock[6] = 0x76;
                swd_unlock[7] = 0x89;
                swd_unlock[8] = 0xBB;
                swd_unlock[9] = 0xAB;
                swd_unlock[10] = 0xCD;
                swd_unlock[11] = 0xEF;
                swd_unlock[12] = 0x99;
                swd_unlock[13] = 0x67;
                swd_unlock[14] = 0x89;
                swd_unlock[15] = 0x11;
              fprintf(pLogFile, "swd password:");
              for (idx = 0; idx < 16; idx++) {
                  fprintf(pLogFile, " %Xh", swd_unlock[idx]);
              }
              fprintf(pLogFile, "\n");
          }
      }
      break;

	  
      case 'h':
      case '?':
      default:
      usage();
      exit(0);
      break;
    }  /* switch (c)  */
  }  /* while(1)  */
  
  if(!image)
  {
	fprintf(pLogFile, "ERROR!! no image!!\n");
	fflush(pLogFile);
    exit(0);
  }

  fprintf (pLogFile, "NDS32 Burner BUILD_ID: %d\n", BUILD_ID);
  fflush(pLogFile);

  initial_socket(port);
#ifdef __MINGW32__
  Sleep (200);
#else
  usleep (200000);
#endif
 
  // select core 
  if( coreid != 0 )
  {
      if (send_coreid(coreid) < 0 )
      {
          close_connection ();
          exit(0);
      }
  }

  // init AICE
  if (send_cmd(RESET_AICE) < 0)
  {
    close_connection ();
    exit(0);
  }

  if (do_swd_unlock) {
      int idx;
      int bus = inw(0xC0000018);
      switch (bus) {
          case 16:
              outw(0xc0000058,8);
              break;
          case 8:
              outw(0xc0000058,4);
              break;
          case 4:
              outw(0xc0000058,2);
              break;
      }
      for (idx = 0; idx < 16; idx++) {
          outw(0xc00001c4, swd_unlock[idx]);
      }
      fprintf(pLogFile, "swd status:%Xh\n", inw(0xC00001c8));
  }

  if (chip == 6020) {
      outw(0xc0000150, 0xffffffff);
      outw(0xc0000154, 0xffffffff);
  }

  /////////////////////////////////
  // inb, inh test code, outb, outh, test code.
    if (0)
    {
        int idx;
        const uint32_t addr = 0x00000000;
        fprintf(pLogFile, "read word testing\n");
        for (idx = 0; idx < 4; idx++) {
            fprintf(pLogFile, "%Xh: %X\n", addr+idx, inw(addr+idx));
        }
        fprintf(pLogFile, "read byte testing\n");
        for (idx = 0; idx < 4; idx++) {
            fprintf(pLogFile, "%Xh: %X\n", addr+idx, inb(addr+idx));
        }
        fprintf(pLogFile, "read half-word testing\n");
        for (idx = 0; idx < 4; idx++) {
            fprintf(pLogFile,"%Xh: %X\n", addr+idx, inh(addr+idx));
        }
        fprintf(pLogFile, "write word testing\n");
#define test_pattern (0x12345678)
#define clean_pattern (0x0)
        outw(addr, clean_pattern);
        outw(addr+4, clean_pattern);
        fprintf(pLogFile, "write bytes testing\n");
        {
            idx = 0;
            uint32_t val;
            outb(addr+idx, test_pattern);
            fprintf(pLogFile, "write byte: %Xh = %X\n", addr+idx, test_pattern);
            fprintf(pLogFile, "%Xh: %X\n", addr, val = inw(addr));
            if (val != (test_pattern&0xff)) {
                fprintf(pLogFile, "error file %s in line:%d\n", __FILE__, __LINE__);
                while(1);
            }
            //
            idx++;
            outb(addr+idx, test_pattern);
            fprintf(pLogFile, "write byte: %Xh = %X\n", addr+idx, test_pattern);
            fprintf(pLogFile, "%Xh: %X\n", addr, val = inw(addr));
            if (val != (((test_pattern&0xff)<<8) |
                        ((test_pattern&0xff)<<0))) {
                fprintf(pLogFile, "error file %s in line:%d\n", __FILE__, __LINE__);
                while(1);
            }
            //
            idx++;
            outb(addr+idx, test_pattern);
            fprintf(pLogFile, "write byte: %Xh = %X\n", addr+idx, test_pattern);
            fprintf(pLogFile, "%Xh: %X\n", addr, val = inw(addr));
            if (val != (((test_pattern&0xff)<<16) |
                        ((test_pattern&0xff)<<8)  |
                        ((test_pattern&0xff)<<0))) {
                fprintf(pLogFile, "error file %s in line:%d\n", __FILE__, __LINE__);
                while(1);
            }
            //
            idx++;
            outb(addr+idx, test_pattern);
            fprintf(pLogFile, "write byte: %Xh = %X\n", addr+idx, test_pattern);
            fprintf(pLogFile, "%Xh: %X\n", addr, val = inw(addr));
            if (val != (((test_pattern&0xff)<<24) |
                        ((test_pattern&0xff)<<16)  |
                        ((test_pattern&0xff)<<8)  |
                        ((test_pattern&0xff)<<0))) {
                fprintf(pLogFile, "error file %s in line:%d\n", __FILE__, __LINE__);
                while(1);
            }
        }
        outw(addr, clean_pattern);
        outw(addr+4, clean_pattern);
        fprintf(pLogFile, "==============================================\n");
        fprintf(pLogFile, "write half-word testing\n");
        {
            idx = 0;
            uint32_t val;
            outh(addr+idx, test_pattern);
            fprintf(pLogFile, "write half-word: %Xh = %X\n", addr+idx, test_pattern);
            fprintf(pLogFile, "%Xh: %X\n", addr, val = inw(addr));
            if (val != (test_pattern&0xffff)) {
                fprintf(pLogFile, "error file %s in line:%d\n", __FILE__, __LINE__);
                while(1);
            }
            //
            idx++;
            outh(addr+idx, test_pattern);
            fprintf(pLogFile, "write half-word: %Xh = %X\n", addr+idx, test_pattern);
            fprintf(pLogFile, "%Xh: %X\n", addr, val = inw(addr));
            if (val != (test_pattern&0xffff)) {
                fprintf(pLogFile, "error file %s in line:%d\n", __FILE__, __LINE__);
                while(1);
            }
            //
            idx++;
            outh(addr+idx, test_pattern);
            fprintf(pLogFile, "write half-word: %Xh = %X\n", addr+idx, test_pattern);
            fprintf(pLogFile, "%Xh: %X\n", addr, val = inw(addr));
            if (val != (((test_pattern&0xffff)<<16) |
                        ((test_pattern&0xffff)<<0))) {
                fprintf(pLogFile, "error file %s in line:%d\n", __FILE__, __LINE__);
                while(1);
            }
            //
            idx++;
            outh(addr+idx, test_pattern);
            fprintf(pLogFile, "write half-word: %Xh = %X\n", addr+idx, test_pattern);
            fprintf(pLogFile, "%Xh: %X\n", addr, val = inw(addr));
            if (val != (((test_pattern&0xffff)<<16) |
                        ((test_pattern&0xffff)<<0))) {
                fprintf(pLogFile, "error file %s in line:%d\n", __FILE__, __LINE__);
                while(1);
            }
        }
        outw(addr, clean_pattern);
        outw(addr+4, clean_pattern);
        fprintf(pLogFile, "==============================================\n");
        //printf("write word testing\n");
        //for (idx = 0; idx < 4; idx++) {
        //    uint32_t val;
        //    outw(addr+idx, test_pattern);
        //    printf("write: %Xh = %X\n", addr+idx, test_pattern);
        //    printf("%Xh: %X\n", addr, val = inw(addr));
        //    if (val != test_pattern) {
        //        printf("error file %s in line:%d\n", __FILE__, __LINE__);
        //        while(1);
        //    }
        //}
        fprintf(pLogFile, "test done\n");
        exit(0);
    }
  /////////////////////////////////
  // sram testing!!!
    if (sram_test_size) {
        srand(time(NULL));
        // controller testing
        //////////////////////////////// for random byte testing [S]
        uint8_t *buf = malloc(sram_test_size);
        for (int i = 0; i < sram_test_size; i++) {
            buf[i] = rand();
        }
        uint32_t *order = malloc(sram_test_size*sizeof(uint32_t));
        for (int i = 0; i < sram_test_size; i++) {
            order[i] = i;
        }
        // do random order
        for (int i = 0; i < sram_test_size*100; i++) {
            uint32_t r1, r2;
            r1 = rand()%sram_test_size;
            r2 = rand()%sram_test_size;
            uint32_t s = order[r1];
            order[r1] = order[r2];
            order[r2] = s;
        }
        
        // random byte_write.
        fprintf(pLogFile, "start random byte write\n"); 
        for (int i = 0; i < sram_test_size; i++) {
            outb(address+order[i], buf[order[i]]);
        }
        fprintf(pLogFile, "random byte write done.\n"); 
        // do random order
        for (int i = 0; i < sram_test_size*100; i++) {
            uint32_t r1, r2;
            r1 = rand()%sram_test_size;
            r2 = rand()%sram_test_size;
            uint32_t s = order[r1];
            order[r1] = order[r2];
            order[r2] = s;
        }
        // random byte read.
        fprintf(pLogFile, "start random byte read\n"); 
        for (int i = 0; i < sram_test_size; i++) {
            if (inb(address+order[i]) != buf[order[i]]) {
                fprintf(pLogFile, "random write/read byte something error in sram address: %Xh, data should be: %xh\n", 
                        address+order[i], buf[order[i]]);
                exit(0);
            }
        }
        fprintf(pLogFile, "random byte read done.\n"); 
        free(buf);
        //////////////////////////////// for random byte testing [E]
        //////////////////////////////// for random half-word testing [S]
        uint16_t *buf16 = malloc(sram_test_size);
        for (int i = 0; i < sram_test_size/2; i++) {
            buf16[i] = rand();
        }
        for (int i = 0; i < sram_test_size/2; i++) {
            order[i] = i;
        }
        // do random order
        for (int i = 0; i < sram_test_size*100; i++) {
            uint32_t r1, r2;
            r1 = rand()%(sram_test_size/2);
            r2 = rand()%(sram_test_size/2);
            uint32_t s = order[r1];
            order[r1] = order[r2];
            order[r2] = s;
        }
        
        // random byte_write.
        fprintf(pLogFile, "start random half-word write\n"); 
        for (int i = 0; i < sram_test_size/2; i++) {
            outh(address+order[i]*2, buf16[order[i]]);
        }
        fprintf(pLogFile, "random half-word write done.\n"); 
        // do random order
        for (int i = 0; i < sram_test_size*100; i++) {
            uint32_t r1, r2;
            r1 = rand()%(sram_test_size/2);
            r2 = rand()%(sram_test_size/2);
            uint32_t s = order[r1];
            order[r1] = order[r2];
            order[r2] = s;
        }
        // random byte read.
        fprintf(pLogFile, "start random half-word read\n"); 
        for (int i = 0; i < sram_test_size/2; i++) {
            if (inh(address+order[i]*2) != buf16[order[i]]) {
                fprintf(pLogFile, "random write/read half-word something error in sram address: %Xh, data should be: %xh\n", 
                        address+order[i]*2, buf16[order[i]]);
                exit(0);
            }
        }
        fprintf(pLogFile, "random half-word read done.\n"); 
        free(buf16);
        //////////////////////////////// for random half-word testing [E]
        //////////////////////////////// for random word testing [S]
        uint16_t *buf32 = malloc(sram_test_size);
        for (int i = 0; i < sram_test_size/4; i++) {
            buf32[i] = rand();
        }
        for (int i = 0; i < sram_test_size/4; i++) {
            order[i] = i;
        }
        // do random order
        for (int i = 0; i < sram_test_size*100; i++) {
            uint32_t r1, r2;
            r1 = rand()%(sram_test_size/4);
            r2 = rand()%(sram_test_size/4);
            uint32_t s = order[r1];
            order[r1] = order[r2];
            order[r2] = s;
        }
        
        // random byte_write.
        fprintf(pLogFile, "start random word write\n"); 
        for (int i = 0; i < sram_test_size/4; i++) {
            outw(address+order[i]*4, buf32[order[i]]);
        }
        fprintf(pLogFile, "random word write done.\n"); 
        // do random order
        for (int i = 0; i < sram_test_size*100; i++) {
            uint32_t r1, r2;
            r1 = rand()%(sram_test_size/4);
            r2 = rand()%(sram_test_size/4);
            uint32_t s = order[r1];
            order[r1] = order[r2];
            order[r2] = s;
        }
        // random byte read.
        fprintf(pLogFile, "start random word read\n"); 
        for (int i = 0; i < sram_test_size/4; i++) {
            if (inw(address+order[i]*4) != buf32[order[i]]) {
                fprintf(pLogFile, "random write/read word something error in sram address: %Xh, data should be: %xh\n", 
                        address+order[i]*4, buf32[order[i]]);
                exit(0);
            }
        }
        fprintf(pLogFile, "random word read done.\n"); 
        free(buf32);
        //////////////////////////////// for random word testing [E]
        fprintf(pLogFile, "random access test done\n"); 
        free(order);
        //////////////////////////////// for bit testing [S]
        uint32_t patterns[] = {0xaaaaaaaa, 0x55555555, 0xffffffff, 0x00000000, 0xa5a5a5a5, 0x5a5a5a5a, 0x7777eeee, 0xeeee7777};
        for (int j = 0; j < sizeof(patterns)/sizeof(uint32_t); j++) {
            uint32_t pattern = patterns[j];
            fprintf(pLogFile, "start bit test, pattern: %xh\n", pattern); 
            for (int i = 0; i < sram_test_size/4; i++) {
                outw(address+i*4, pattern);
            }
            for (int i = 0; i < sram_test_size/4; i++) {
                if (inw(address+i*4) != pattern) {
                    fprintf(pLogFile, "bit test write/read word something error in sram address: %Xh, data should be: %xh\n", address+i*4, pattern);
                    exit(0);
                }
            }
            fprintf(pLogFile, "bit test done, pattern: %xh\n", pattern); 
        }
        fprintf(pLogFile, "bit test done\n"); 
        fprintf(pLogFile, "ALL pass\n"); 
        //////////////////////////////// for bit testing [E]
        exit(0);
    }
  /////////////////////////////////

  // reset-and-hold to init target
  send_cmd (RESET_HOLD);

  /* get burn image content */
  if(!readall)
  {
    fprintf(pLogFile, "get burn image content...\n");
    content = get_image(image, &size);
    start = content;
    fclose (image);
  }
  /* handle signal */
  signal(SIGTERM, handle_int);
  signal(SIGINT, handle_int);
#ifndef __MINGW32__
  signal(SIGKILL, handle_int);
#endif
  if(!readall)
  {
    if((size+address) > FLASH_SIZE)
    {
      fprintf(pLogFile, "ERROR!! image size(%d) > flash size!!\n", size);
      return 0;
    }
    else
    {
      fprintf (pLogFile, "image size: %d bytes\n", size);
      fflush(pLogFile);
    }
  }
  
  flash_init();
  flash_get_jedec();
  
  if(readall)
  {
    fprintf(pLogFile, "Flash readall begin.\n");
	
	for(read_addr=0; read_addr<FLASH_SIZE; read_addr+=FLASH_SECTOR_SIZE)
	{
		flash_fast_read(read_addr, FLASH_SECTOR_SIZE, readbuf);
		fwrite(readbuf, sizeof(char), FLASH_SECTOR_SIZE, image);
		fprintf(pLogFile, "read 0x%x\n",read_addr);
	}
	
	fprintf(pLogFile, "Flash readall done.\n");
	fclose(image);
    terminate();
    return 0;
  }
  
#if 1
  /* block erase */
  if (erase_all)
  {
    erase_addr = 0;
    erase_size = FLASH_SIZE;
  }
  else
  {
    erase_addr = address;
    erase_size = ((((address+size)+4095)>>12)<<12);
  }
  
  fprintf(pLogFile, "Flash erase begin.\n");
  
  gettimeofday(&erase_begin_time, NULL);
  while(erase_addr < erase_size)
  {
      if ((!(erase_addr & 0xffff)) && ((erase_addr+64*1024)<erase_size)) {
          flash_64kblock_erase(erase_addr);
          erase_addr += 64*1024;
      } else if ((!(erase_addr & 0x7fff)) && ((erase_addr+32*1024)<erase_size)) {
          flash_32kblock_erase(erase_addr);
          erase_addr += 32*1024;
      } else {
          flash_sector_erase(erase_addr);
          erase_addr += FLASH_SECTOR_SIZE;
      }
    //fprintf(pLogFile, "Flash erase 0x%X\n", erase_addr);
  }
  gettimeofday (&erase_end_time, NULL);
  timeval_diff (&erase_total_time, &erase_begin_time, &erase_end_time);
  erase_time_sec = erase_total_time.tv_sec + (double)erase_total_time.tv_usec / 1000000;
  
  fprintf(pLogFile, "\nTotal erase time: %lu sec, %lu usec\n",
  erase_total_time.tv_sec, erase_total_time.tv_usec);
  fprintf(pLogFile, "Average erase rate: %.2lf KBytes/s\n",
  (double)(erase_size >> 10) / erase_time_sec);
  
  fprintf(pLogFile, "Flash erase done.\n");

  /* burn image */
  fprintf(pLogFile, "Flash burning begin.\n");

  flash_set_quadbit();
  fprintf(pLogFile, "Flash quadbits enable.\n");
  
  program_size = size;
  gettimeofday (&burn_begin_time, NULL);
  
  flashaddr = address;
  while(program_size)
  {
	if(program_size > 0xFF)
	{
	  writelength = FLASH_PAGE_SIZE;
	}
	else
	{
	  writelength = program_size;//the final write
	}
	flash_page_program(flashaddr, writelength, start);
	program_size -= writelength;
	flashaddr += writelength;
	start += writelength;
  }
  gettimeofday (&burn_end_time, NULL);
  timeval_diff (&burn_total_time, &burn_begin_time, &burn_end_time);
  burn_time_sec = burn_total_time.tv_sec + (double)burn_total_time.tv_usec / 1000000;

  fprintf(pLogFile, "\n\nTotal burn time: %lu sec, %lu usec\n",
  burn_total_time.tv_sec, burn_total_time.tv_usec);
  fprintf(pLogFile, "Average burn rate: %.2lf KBytes/s\n", (double)(size >> 10) / burn_time_sec);
  
  fprintf(pLogFile, "Flash burning done.\n");
#endif
  release_image(content);

  if (rst) {
      reset_dut();
  }

  terminate();
  return 0;
}

/* record the flash memory content to buffer */
