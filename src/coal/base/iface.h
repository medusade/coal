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
 *   File: iface.h
 *
 * Author: $author$
 *   Date: 2/23/2018
 **********************************************************************
 */
#ifndef _COAL_BASE_INTERFACE_H
#define _COAL_BASE_INTERFACE_H

#include "coal/platform/iplatform.h"

/*
 * enum INTERFACE_STATUS
 */
enum 
{
    INTERFACE_SUCCESS = 0,
    INTERFACE_ERROR_END_LINK,
    INTERFACE_ERROR_UNKNOWN_NAME,
    INTERFACE_ERROR_NO_MEMORY,
    INTERFACE_ERROR_NOT_NESTABLE,
    INTERFACE_ERROR_UNIMPLEMENTED_METHOD,
    INTERFACE_ERROR_INVALID_METHOD,
    INTERFACE_FAIL
};

/*
 * enum INTERFACE_TO
 */
enum 
{
    INTERFACE_TO_THIS = 0,
    INTERFACE_TO_PARENT,
    INTERFACE_TO_PREVIOUS,
    INTERFACE_TO_NEXT,
    INTERFACE_TO_FIRST,
    INTERFACE_TO_LAST,
    INTERFACE_TO_NAME
};

#if defined(__cplusplus)
/*
 * class Interface
 */
class Interface
{
public:
    virtual int METHOD SetName(const char *name)=0;
    virtual int METHOD GetName(const char *&name)=0;
    virtual int METHOD SetData(void *data)=0;
    virtual int METHOD GetData(void *&data)=0;
    virtual int METHOD SetLink(Interface *iface,unsigned to,const char *name)=0;
    virtual int METHOD Link(Interface *&iface,unsigned to=INTERFACE_TO_THIS,const char *name=NULL)=0;
    virtual int METHOD Unlink()=0;
    virtual int METHOD New
    (Interface *&iface,const char *name=NULL,void *data=NULL,
     Interface *parent=NULL,Interface *previous=NULL,Interface *next=NULL)=0;
};

extern "C" {

/*
 * Interface functions
 */
int INTERFACE_Get(Interface *&iface,void *&position,const char *name);
int INTERFACE_GetFirst(Interface *&iface,void *&position);
int INTERFACE_GetLast(Interface *&iface,void *&position);
int INTERFACE_GetNext(Interface *&iface,void *&position);
int INTERFACE_GetPrevious(Interface *&iface,void *&position);

int INTERFACE_GetNew
(Interface *&iface,
 const char *name=NULL,void *data=NULL,
 Interface *parent=NULL,Interface *previous=NULL,Interface *next=NULL);

int INTERFACE_Construct
(Interface *&iface,struct COMPONENT &cface,signed linked=0,void *data=NULL,
 Interface *parent=NULL,Interface *previous=NULL,Interface *next=NULL);

int INTERFACE_Destruct(struct COMPONENT &cface);

} /* extern "C" */

/*
 * Interface method defines
 */
#define Interface_Unlink(iface) (iface->Unlink())

#else /* defined(__cplusplus) */
/*
 * struct INTERFACE
 */
struct INTERFACE;
typedef struct INTERFACE* Interface;
typedef struct INTERFACE
{
    int (METHOD *SetName)(const struct INTERFACE **cface,const char *name);
    int (METHOD *GetName)(const struct INTERFACE **cface,const char **name);
    int (METHOD *SetData)(const struct INTERFACE **cface,void *data);
    int (METHOD *GetData)(const struct INTERFACE **cface,void **data);
    int (METHOD *SetLink)(const struct INTERFACE **cface,const struct INTERFACE **iface,unsigned to,const char *name);
    int (METHOD *Link)(const struct INTERFACE **cface,const struct INTERFACE ***iface,unsigned to,const char *name);
    int (METHOD *Unlink)(const struct INTERFACE **cface);
    int (METHOD *New)
    (const struct INTERFACE **cface,
     const struct INTERFACE ***iface,const char *name,void *data,
     const struct INTERFACE **parent,const struct INTERFACE **previous,const struct INTERFACE **next);
} INTERFACE;

/*
 * struct COMPONENT
 */
typedef struct COMPONENT
{
    const INTERFACE *iface;
    signed linked;
    const char *name;
    void *data;
    const INTERFACE **parent;
    const INTERFACE **previous;
    const INTERFACE **next;
    const INTERFACE **first;
    const INTERFACE **last;
} COMPONENT;

/*
 * INTERFACE methods
 */
int METHOD INTERFACE__SetName(const INTERFACE **cface,const char *name);
int METHOD INTERFACE__GetName(const INTERFACE **cface,const char **name);
int METHOD INTERFACE__SetData(const INTERFACE **cface,void *data);
int METHOD INTERFACE__GetData(const INTERFACE **cface,void **data);
int METHOD INTERFACE__SetLink(const INTERFACE **cface,const INTERFACE **iface,unsigned to,const char *name);
int METHOD INTERFACE__Link(const INTERFACE **cface,const INTERFACE ***iface,unsigned to,const char *name);
int METHOD INTERFACE__Unlink(const INTERFACE **cface);
int METHOD INTERFACE__New
(const INTERFACE **cface,
 const INTERFACE ***iface,const char *name,void *data,
 const INTERFACE **parent,const INTERFACE **previous,const INTERFACE **next);

/*
 * INTERFACE functions
 */
int INTERFACE_Construct
(const INTERFACE ***iface,COMPONENT *cface,
 signed linked,const char *name,void *data,
 const INTERFACE **parent,const INTERFACE **previous,const INTERFACE **next);

int INTERFACE_Destruct(struct COMPONENT *cface);

int INTERFACE_Get(const INTERFACE ***iface,void **position,const char *name);
int INTERFACE_GetFirst(const INTERFACE ***iface,void **position);
int INTERFACE_GetLast(const INTERFACE ***iface,void **position);
int INTERFACE_GetNext(const INTERFACE ***iface,void **position);
int INTERFACE_GetPrevious(const INTERFACE ***iface,void **position);

int INTERFACE_GetNew
(const INTERFACE ***iface,void **position,const char *name,void *data,
 const INTERFACE **parent,const INTERFACE **previous,const INTERFACE **next);

int INTERFACE_Register(const INTERFACE **iface);
int INTERFACE_Unregister(const INTERFACE **iface);

void *INTERFACE_Alloc(unsigned bytes);
void INTERFACE_Free(void *data);
int INTERFACE_StrLen(const char *s);
int INTERFACE_StrCmp(const char *s1,const char *s2);
char *INTERFACE_StrCpy(char *s1,const char *s2);
void *INTERFACE_MemCpy(void *dst,const void *src,long count);
void *INTERFACE_MemSet(void *dst,int c,long count);
void *INTERFACE_MemZero(void *dst,long count);
int INTERFACE_MemCmp(const void *buf1,const void *buf2,long count);

/*
 * INTERFACE function defines
 */
#ifndef _INTERFACE_NO_ANSI
#define INTERFACE_MemZero(addr,count) memset(addr,0,count)
#define INTERFACE_MemSet memset
#define INTERFACE_MemCpy memcpy
#define INTERFACE_MemCmp memcmp
#define INTERFACE_StrCpy strcpy
#define INTERFACE_StrCmp strcmp
#define INTERFACE_StrLen strlen
#endif /* ndef _INTERFACE_NO_ANSI */

#ifndef _INTERFACE_NO_MALLOC
#define INTERFACE_Alloc(size) malloc(size)
#define INTERFACE_Free(addr) free(addr)
#endif /* ndef _INTERFACE_NO_MALLOC */

/*
 * INTERFACE method defines
 */
#define INTERFACE_SetName(cface,name) (*(*(cface))->SetName)(cface,name)
#define INTERFACE_GetName(cface,name) (*(*(cface))->GetName)(cface,name)
#define INTERFACE_SetData(cface,data) (*(*(cface))->SetData)(cface,data)
#define INTERFACE_GetData(cface,data) (*(*(cface))->GetData)(cface,data)
#define INTERFACE_SetLink(cface,iface,to,name) (*(*(cface))->SetLink)(cface,iface,to,name)
#define INTERFACE_Link(cface,iface,to,name) (*(*(cface))->Link)(cface,iface,to,name)
#define INTERFACE_Unlink(cface) (*(*(cface))->Unlink)(cface)
#define INTERFACE_New(cface,iface,name,data,parent,previous,next) (*(*(cface))->New)(cface,iface,name,data,parent,previous,next)

/*
 * Interface method defines
 */
#define Interface_Unlink(cface) INTERFACE_Unlink((INTERFACE**)cface)

#endif /* defined(__cplusplus) */

/*
 * Interface function defines
 */
#define Interface_Get INTERFACE_Get
#define Interface_GetFirst INTERFACE_GetFirst
#define Interface_GetLast INTERFACE_GetLast
#define Interface_GetNext INTERFACE_GetNext
#define Interface_GetPrevious INTERFACE_GetPevious
#define Interface_GetNew INTERFACE_GetNew
#define Interface_Construct INTERFACE_Construct
#define Interface_Destruct INTERFACE_Destruct

#endif /* _COAL_BASE_INTERFACE_H */
