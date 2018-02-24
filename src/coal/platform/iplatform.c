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
 *   File: iplatform.c
 *
 * Author: $author$
 *   Date: 2/23/2018
 **********************************************************************
 */
#include "coal/platform/iplatform.h"
#include <stdarg.h>

static unsigned int _printx_cols = 32;

static int _printx
(int _printf(const char* format, ...), const void *buff, unsigned int bytes) {
    const unsigned char* byte = 0;

    if ((byte = (const unsigned char*)buff) && (bytes)) {
        unsigned int i = 0, j = 0, cols = _printx_cols;
        
        for (j=0, i=0; i<bytes; ++i) {
            if (cols) {
                if (j<cols) {
                    j++;
                } else { 
                    j=1; 
                    _printf("\n"); 
                }
            }
            _printf("%2.2x",byte[i]);
        }
        _printf("\n");
        return bytes;
    }
    return 0;    
}

int debug_vfprintf(FILE *file, const char* format, va_list va) {
    int count = 0;
    count = vfprintf(file, format, va);
    return count;    
}

int debug_printf(const char* format, ...) {
    int count = 0;

    if ((format)) {
        va_list va;

        va_start(va, format);
        count = debug_vfprintf(stderr, format, va);
        va_end(va);
    }
    return count;    
}

int debug_location_printf
(const char* file, int line, const char* function, const char* format, ...) {
    int count = 0;
    if ((file)) {
        count += debug_printf("%s", file);
    }
    if ((line)) {
        count += debug_printf("[%d]", line);
    }
    if ((function)) {
        if ((file) || (line)) {
            count += debug_printf(" ");
        }
        count += debug_printf("%s() ", function);
    }
    if ((format)) {
        va_list va;

        va_start(va, format);
        count += debug_vfprintf(stderr, format, va);
        va_end(va);
    }
    return count;    
}

int debug_printx(const void *buff, unsigned int bytes) {
    return _printx(debug_printf, buff, bytes);
}

int printx(const void *buff, unsigned int bytes) {
    return _printx(printf, buff, bytes);
}
