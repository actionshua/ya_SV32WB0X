/*--------------------------------------------------------------- 
 * Copyright (c) 1999,2000,2001,2002,2003                              
 * The Board of Trustees of the University of Illinois            
 * All Rights Reserved.                                           
 *--------------------------------------------------------------- 
 * Permission is hereby granted, free of charge, to any person    
 * obtaining a copy of this software (Iperf) and associated       
 * documentation files (the "Software"), to deal in the Software  
 * without restriction, including without limitation the          
 * rights to use, copy, modify, merge, publish, distribute,        
 * sublicense, and/or sell copies of the Software, and to permit     
 * persons to whom the Software is furnished to do
 * so, subject to the following conditions: 
 *
 *     
 * Redistributions of source code must retain the above 
 * copyright notice, this list of conditions and 
 * the following disclaimers. 
 *
 *     
 * Redistributions in binary form must reproduce the above 
 * copyright notice, this list of conditions and the following 
 * disclaimers in the documentation and/or other materials 
 * provided with the distribution. 
 * 
 *     
 * Neither the names of the University of Illinois, NCSA, 
 * nor the names of its contributors may be used to endorse 
 * or promote products derived from this Software without
 * specific prior written permission. 
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES 
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
 * NONINFRINGEMENT. IN NO EVENT SHALL THE CONTIBUTORS OR COPYRIGHT 
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. 
 * ________________________________________________________________
 * National Laboratory for Applied Network Research 
 * National Center for Supercomputing Applications 
 * University of Illinois at Urbana-Champaign 
 * http://www.ncsa.uiuc.edu
 * ________________________________________________________________ 
 *
 * stdio.c
 * by Mark Gates <mgates@nlanr.net>
 * and Ajay Tirumalla <tirumala@ncsa.uiuc.edu>
 * -------------------------------------------------------------------
 * input and output numbers, converting with kilo, mega, giga
 * ------------------------------------------------------------------- */

#include "iperf_headers.h"
#include "iperf_util.h"

#include "soc_types.h" //FIXME!
#include "assert.h"


#ifdef __cplusplus
extern "C" {
#endif

const long kKilo_to_Unit = 1024;
const long kMega_to_Unit = 1024 * 1024;
const long kGiga_to_Unit = 1024 * 1024 * 1024;

const long kkilo_to_Unit = 1000;
const long kmega_to_Unit = 1000 * 1000;
const long kgiga_to_Unit = 1000 * 1000 * 1000;

/* -------------------------------------------------------------------
 * byte_atof
 *
 * Given a string of form #x where # is a number and x is a format
 * character listed below, this returns the interpreted integer.
 * Gg, Mm, Kk are giga, mega, kilo respectively
 * ------------------------------------------------------------------- */
#if 0
double byte_atof( const char *inString ) {
    double theNum;
    char suffix = '\0';

    assert( inString != NULL );

    /* scan the number and any suffices */
    sscanf( inString, "%lf%c", &theNum, &suffix );

    /* convert according to [Gg Mm Kk] */
    switch ( suffix ) {
        case 'G':  theNum *= kGiga_to_Unit;  break;
        case 'M':  theNum *= kMega_to_Unit;  break;
        case 'K':  theNum *= kKilo_to_Unit;  break;
        case 'g':  theNum *= kgiga_to_Unit;  break;
        case 'm':  theNum *= kmega_to_Unit;  break;
        case 'k':  theNum *= kkilo_to_Unit;  break;
        default: break;
    }
    return theNum;
} /* end byte_atof */
#endif
/* -------------------------------------------------------------------
 * byte_atoi
 *
 * Given a string of form #x where # is a number and x is a format
 * character listed below, this returns the interpreted integer.
 * Gg, Mm, Kk are giga, mega, kilo respectively
 * ------------------------------------------------------------------- */

max_size_t byte_atoi( const char *inString ) {
    //double theNum;
    int theNum = 0, base = 10, index, upbound, v;
    char suffix = '\0';
    const char *s = inString;

    upbound=base-1;
    assert( inString != NULL );

    /* scan the number and any suffices */
    //sscanf( inString, "%lf%c", &theNum, &suffix );
    while( (v = (u8)*s) != 0 ) {
        index = v - '0';        
        if ( index > upbound )
        {
            /* convert according to [Gg Mm Kk] */
            switch ( (*s) ) {
                case 'G':  theNum *= kGiga_to_Unit;  break;
                case 'M':  theNum *= kMega_to_Unit;  break;
                case 'K':  theNum *= kKilo_to_Unit;  break;
                case 'g':  theNum *= kgiga_to_Unit;  break;
                case 'm':  theNum *= kmega_to_Unit;  break;
                case 'k':  theNum *= kkilo_to_Unit;  break;
                default: break;
            }
            break;
        }
        theNum = theNum * base + index;
        s++;
    }
    
    return (max_size_t) theNum;
} /* end byte_atof */

/* -------------------------------------------------------------------
 * constants for byte_printf
 * ------------------------------------------------------------------- */

/* used as indices into kConversion[], kLabel_Byte[], and kLabel_bit[] */
enum {
    kConv_Unit,
    kConv_Kilo,
    kConv_Mega,
    kConv_Giga
};

/* factor to multiply the number by */
const int kConversionExpo[] =
{
    0,                       /* unit */
    10,                /* kilo */
    20,         /* mega */
    30   /* giga */
};

/* factor to multiply the number by */
const int kConversion[] =
{
    1,                       /* unit */
    2^10,                /* kilo */
    2^20,         /* mega */
    2^30   /* giga */
};

/* factor to multiply the number by for bits*/
const int kConversionForBits[] =
{
    1,                       /* unit */
    1000,                /* kilo */
    1000000,         /* mega */
    1000000000   /* giga */
};


/* labels for Byte formats [KMG] */
const char* kLabel_Byte[] =
{
    "Byte",
    "KByte",
    "MByte",
    "GByte"
};

/* labels for bit formats [kmg] */
const char* kLabel_bit[]  =
{
    "bit", 
    "Kbit",
    "Mbit",
    "Gbit"
};

/* -------------------------------------------------------------------
 * byte_snprintf
 *
 * Given a number in bytes and a format, converts the number and
 * prints it out with a bits or bytes label.
 *   B, K, M, G, A for Byte, Kbyte, Mbyte, Gbyte, adaptive byte
 *   b, k, m, g, a for bit,  Kbit,  Mbit,  Gbit,  adaptive bit
 * adaptive picks the "best" one based on the number.
 * outString should be at least 11 chars long
 * (4 digits + space + 5 chars max + null)
 * ------------------------------------------------------------------- */

void byte_snprintf( char* outString, int inLen,
                    int inNum, char inFormat ) {
    int conv, base = 1024, inte = 0, deci = 0;
    const char* suffix;
    const char* format;
    bool isupper = true;

    /* convert to bits for [bkmga] */
    /*if ( ! isupper( (int)inFormat ) ) {
        inNum *= 8;
    }*/

    switch ( inFormat ) {//switch ( toupper(inFormat) ) {
        case 'b': inNum *= 8; isupper = false; 
        case 'B': conv = kConv_Unit; break;
        case 'k': inNum *= 8; isupper = false; 
        case 'K': conv = kConv_Kilo; break;
        case 'm': inNum *= 8; isupper = false; 
        case 'M': conv = kConv_Mega; break;
        case 'g': inNum *= 8; isupper = false; 
        case 'G': conv = kConv_Giga; break;
        
        case 'a': inNum *= 8;
                  base = 1000;
                  isupper = false;
        default:
        case 'A': {
                int tmpNum = inNum;
                conv = kConv_Unit;
                /*
                if ( isupper((int)inFormat) ) {
                    while ( tmpNum >= 1024.0  &&  conv <= kConv_Giga ) {
                        tmpNum /= 1024.0;
                        conv++;
                    }
                } else {
                    while ( tmpNum >= 1000.0  &&  conv <= kConv_Giga ) {
                        tmpNum /= 1000.0;
                        conv++;
                    }
                }*/
                while ( tmpNum >= base  &&  conv <= kConv_Giga ) {
                    tmpNum /= base;
                    conv++;
                }
                break;
            }
    }

    if ( isupper == false) {//if ( ! isupper ((int)inFormat) ) {
        //inNum *= kConversionForBits[ conv ];
        inte = (int)(inNum/kConversionForBits[ conv ]);                
        suffix = kLabel_bit[conv]; 
        deci = (int)((inNum - (inte*kConversionForBits[ conv ]))*100)/kConversionForBits[ (conv) ];
    } else {
        //inNum *= kConversion [conv];
        inte = (int)(inNum>>kConversionExpo[ conv ]);
        suffix = kLabel_Byte[ conv ];
        deci = (int)((inNum - (inte>>kConversionExpo[ conv ]))*100)>>kConversionExpo[ (conv) ];
    }

    /* print such that we always fit in 4 places */
#if 0
    if ( inte < 10 ) {          /* 9.995 would be rounded to 10.0 */
        format = "%4d.02d %s";        /* #.## */
    } else if ( inte < 100 ) {   /* 99.95 would be rounded to 100 */
        format = "%4d.1d %s";        /* ##.# */
    } else if ( inte < 1000) {   /* 999.5 would be rounded to 1000 */
	format = "%4.0f %s";        /*  ### */
    } else {                        /* 1000-1024 fits in 4 places 
				     * If not using Adaptive sizes then
				     * this code will not control spaces*/
        format = "%4.0f %s";        /* #### */
    }
#else
    format = "%4d.%02d %s";        /* #### */
#endif
    snprintf( outString, inLen, format, inte, deci, suffix );
} /* end byte_snprintf */

/* -------------------------------------------------------------------
 * redirect
 *
 * redirect the stdout into a specified file
 * return: none
 * ------------------------------------------------------------------- */

void redirect(const char *inOutputFileName) {
#ifdef WIN32

    FILE *fp;

    if ( inOutputFileName == NULL ) {
        printf ( "should specify the output file name.\n");
        return;
    }

    fp = freopen(inOutputFileName, "a+", stdout);
    if ( fp == NULL ) {
        printf ( "redirect stdout failed!\n");
        return;
    }

#endif

    return;
}

#ifdef iperf_mem_check
char *malloc_fn(int size, char *file, int line)
{
    char *ptr;
    ptr = malloc(size);
    printf("[%s:%d], ptr = %x, size = %d\n", file, line, ptr, size);
    
    return ptr;
}

void free_fn(void *ptr, char *file, int line)
{
    printf("[%s:%d], ptr = %x\n", file, line, ptr);
    free(ptr);
}
#endif

#ifdef __cplusplus
} /* end extern "C" */
#endif

