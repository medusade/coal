/**
 **********************************************************************
 * Copyright (c) 1988-2018 $organization$
 *
 * This software is provided by the author and contributors ``as is'' 
 * and any express or implied warranties, including, but not limited to, 
 * the implied warranties of merchantability and fitness for a particular 
 * purpose are disclaimed. In no event shall the author or contributors 
 * be liable for any direct, indirect, incidental, special, exemplary, 
 * or consequential damages (including, but not limited to, procurement 
 * of substitute goods or services; loss of use, data, or profits; or 
 * business interruption) however caused and on any theory of liability, 
 * whether in contract, strict liability, or tort (including negligence 
 * or otherwise) arising in any way out of the use of this software, 
 * even if advised of the possibility of such damage.
 *
 *   File: iplatform.h
 *
 * Author: $author$
 *   Date: 2/23/2018
 **********************************************************************
 */
#ifndef _COAL_PLATFORM_IPLATFORM_H
#define _COAL_PLATFORM_IPLATFORM_H

#if !defined(_INTERFACE_NO_ANSI)
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#else /* !defined(_INTERFACE_NO_ANSI) */
#define printf(format,...) platform_printf(format,##__VA_ARGS__)
#define fprintf(file,format,...) platform_fprintf(file,format,##__VA_ARGS__)
#define vprintf(format,va) platform_vprintf(format,va)
#define vfprintf(file,format,va) platform_vfprintf(file,format,va)
#endif /* !defined(_INTERFACE_NO_ANSI) */

#if !defined(METHOD)
#define METHOD
#endif /* !defined(METHOD) */

#if defined(__cplusplus)
extern "C" {
#endif /* defined(__cplusplus) */

#if !defined(dbprintf)
#if !defined(DEBUG_BUILD)
#define dbprintf(format,...)
#else /* !defined(DEBUG_BUILD) */
#if defined(DEBUG_LOCATION_PRINTF)
#define dbprintf(format,...) debug_printf(format, ##__VA_ARGS__)
#else /* !defined(DEBUG_LOCATION_PRINTF) */
#define dbprintf(format,...) debug_location_printf(__FILE__,__LINE__,__FUNCTION__,format, ##__VA_ARGS__)
#endif /* !defined(DEBUG_LOCATION_PRINTF) */
extern int debug_location_printf
(const char* file, int line, const char* function, const char* format, ...);
extern int debug_printf(const char* format, ...);
#endif /* !defined(DEBUG_BUILD) */
#endif /* !defined(dbprintf) */

#if !defined(dbprintx)
#if !defined(DEBUG_BUILD)
#define dbprintx(buff,bytes)
#else /* !defined(DEBUG_BUILD) */
#define dbprintx(buff,bytes) debug_printx(buff,bytes)
extern int debug_printx(const void *buff,unsigned int bytes);
#endif /* !defined(DEBUG_BUILD) */
#endif /* !defined(dbprintx) */

int printx(const void *buff,unsigned int bytes);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* _COAL_PLATFORM_IPLATFORM_H */

        

