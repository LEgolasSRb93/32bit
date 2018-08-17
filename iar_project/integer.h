/*-------------------------------------------*/
/* Integer type definitions for FatFs module */
/*-------------------------------------------*/

#ifndef _INTEGER
#define _INTEGER

#if 0
#include <windows.h>
#else

#include "stm32f4xx.h"
#include "stdbool.h"

#ifdef __MIKROC_PRO_FOR_ARM__

/* These types must be 16-bit, 32-bit or larger integer */
typedef int32_t               INT;
typedef uint32_t              UINT;

/* These types must be 8-bit integer */
typedef signed char           CHAR;
typedef unsigned char         UCHAR;
typedef unsigned char         BYTE;

/* These types must be 16-bit integer */
typedef int16_t               SHORT;
typedef uint16_t              USHORT;
typedef uint16_t              WORD;
typedef uint16_t              WCHAR;

/* These types must be 32-bit integer */
typedef long                  LONG;
typedef uint32_t              ULONG;
typedef uint32_t              DWORD;

#else /* __MIKROC_PRO_FOR_ARM__  */

/* These types must be 16-bit, 32-bit or larger integer */
typedef int                   INT;
typedef unsigned int          UINT;

/* These types must be 8-bit integer */
#ifndef CHAR
typedef signed char           CHAR;
#endif
typedef unsigned char         UCHAR;
typedef unsigned char         BYTE;

/* These types must be 16-bit integer */
typedef short                 SHORT;
typedef unsigned short        USHORT;
typedef unsigned short        WORD;
typedef unsigned short        WCHAR;

/* These types must be 32-bit integer */
typedef long                  LONG;
typedef unsigned long         ULONG;
typedef unsigned long         DWORD;

#endif /* __MIKROC_PRO_FOR_ARM__  */

/* Boolean type         */
#ifndef  _StdBool
typedef enum { FALSE = 0, TRUE } BOOL;
#endif  /* BOOL */

/* typedef bool BOOL;
#ifndef FALSE
#define FALSE false
#define TRUE true
#endif
          */

#endif


#endif
