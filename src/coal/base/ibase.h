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
 *   File: ibase.h
 *
 * Author: $author$
 *   Date: 2/23/2018
 **********************************************************************
 */
#ifndef _COAL_BASE_IBASE_H
#define _COAL_BASE_IBASE_H

#include "coal/base/iface.h"

/*
 * enum IBASE
 */
enum 
{
    IBASE_SUCCESS = INTERFACE_SUCCESS,
    IBASE_FAIL = INTERFACE_FAIL+1
};


#if defined(__cplusplus)

/*
 * iBase
 */

/*
 * class iBase
 */
class iBase: public Interface
{
public:
    virtual int METHOD Base()=0;
};

extern "C" {

/*
 * iBase functions
 */
int IBASE_New
(iBase *&iface,const char *name=NULL,void *data=NULL,
 Interface *parent=NULL,Interface *previous=NULL,Interface *next=NULL);

int IBASE_Get(iBase *&iface,const char *name);
int IBASE_Register();
int IBASE_Unregister();

int IBASE_Construct
(iBase *&iface,struct CBASE &self,signed linked=0,void *data=NULL,
 Interface *parent=NULL,Interface *previous=NULL,Interface *next=NULL);

int IBASE_Destruct(struct CBASE &self);

} /* extern "C" */

/*
 * iBase method defines
 */
#define iBase_Base(iface) (iface->Base())

#else /* defined(__cplusplus) */

/*
 * IBASE structs
 */
 
/*
 * struct IBASE
 */
struct IBASE;
typedef struct IBASE* iBase;
typedef struct IBASE
{
	INTERFACE iface;
} IBASE;

/*
 * struct CBASE
 */
struct CBASE;
typedef struct CBASE
{
    COMPONENT comp;
} CBASE;

/*
 * IBASE INTERFACE
 */

/*
 * IBASE INTERFACE methods
 */
/*
int METHOD IBASE__SetName(const INTERFACE **cface,const char *name);
int METHOD IBASE__GetName(const INTERFACE **cface,const char **name);
int METHOD IBASE__SetData(const INTERFACE **cface,void *data);
int METHOD IBASE__GetData(const INTERFACE **cface,void **data);
int METHOD IBASE__SetLink(const INTERFACE **cface,const INTERFACE **iface,unsigned to,const char *name);
int METHOD IBASE__Link(const INTERFACE **cface,const INTERFACE ***iface,unsigned to,const char *name);
*/

int METHOD IBASE__Unlink(const INTERFACE **cface);
int METHOD IBASE__New
(const INTERFACE **cface,
 const INTERFACE ***iface,const char *name,void *data,
 const INTERFACE **parent,const INTERFACE **previous,const INTERFACE **next);

/*
 * IBASE INTERFACE method defines
 */
#define IBASE_Unlink(cface) (*(*(cface))->Unlink)(cface)

/*
 * iBase INTERFACE method defines
 */
#define iBase_Unlink(cface) IBASE_Unlink((INTERFACE**)cface)

/*
 * IBASE
 */

/*
 * IBASE methods
 */
int METHOD IBASE__Base(const IBASE **cface);

/*
 * IBASE functions
 */
int IBASE_Construct
(const IBASE ***iface,struct CBASE *cface,
 signed linked,const char *name,void *data,
 const INTERFACE **parent,const INTERFACE **previous,const INTERFACE **next);

int IBASE_Destruct(struct CBASE *cface);

int IBASE_New
(const IBASE ***iface,const char *name,void *data,
 const INTERFACE **parent,const INTERFACE **previous,const INTERFACE **next);

int IBASE_Get(const IBASE ***iface,const char *name);

int IBASE_Register();
int IBASE_Unregister();

/*
 * IBASE method defines
 */
#define IBASE_Base(cface) (*(*(cface))->Base)(cface)

/*
 * iBase method defines
 */
#define iBase_Base(cface) IBASE_Base((IBASE**)cface)

#endif /* defined(__cplusplus) */

/*
 * iBase function defines
 */
#define iBase_New IBASE_New
#define iBase_Get IBASE_Get

#define iBase_Register IBASE_Register
#define iBase_Unregister IBASE_Unregister

#define iBase_Construct IBASE_Construct
#define iBase_Destruct IBASE_Destruct

#endif /* _COAL_BASE_IBASE_H */
