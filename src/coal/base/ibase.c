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
 *   File: ibase.c
 *
 * Author: $author$
 *   Date: 2/23/2018
 **********************************************************************
 */
#include "coal/base/ibase.h"

/*
 * IBASE name
 */
const char IBASE__name[] = "iBase";

/*
 * IBASE iface
 */
const IBASE IBASE__iface = 
{
    {   /* INTERFACE */
    
        INTERFACE__SetName,
        INTERFACE__GetName,
        INTERFACE__SetData,
        INTERFACE__GetData,
        INTERFACE__SetLink,
        INTERFACE__Link,
        IBASE__Unlink,
        IBASE__New,
        
    },  /* INTERFACE */
    
    IBASE__Base,

}; /* IBASE */

/*
 * CBASE cface
 */
const CBASE CBASE__cface = 
{
    {   /* COMPONENT */
    
        &IBASE__iface,
        -1,
        IBASE__name,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    
    }, /* COMPONENT */

}; /* CBASE */

/*
 * IBASE INTERFACE methods
 */
int METHOD IBASE__Unlink(const INTERFACE **cface)
{
    if (((COMPONENT*)cface)->parent==NULL)
    if (((COMPONENT*)cface)->linked==0)
        IBASE_Destruct((CBASE*)cface);

    return INTERFACE__Unlink(cface);
}

int METHOD IBASE__New
(const INTERFACE **cface,
 const INTERFACE ***iface,const char *name,void *data,
 const INTERFACE **parent,const INTERFACE **previous,const INTERFACE **next)
{
    return IBASE_New((IBASE***)iface,name,data,parent,previous,next);
}

/*
 * IBASE methods
 */
 int METHOD IBASE__Base(const IBASE **cface)
 {
     dbprintf("return IBASE_SUCCESS...\n");
    return IBASE_SUCCESS;
 }

/*
 * IBASE functions
 */
int IBASE_Construct
(const IBASE ***iface,CBASE *cface,
 signed linked,const char *name,void *data,
 const INTERFACE **parent,const INTERFACE **previous,const INTERFACE **next)
{
    int result = IBASE_FAIL;

    if ((result=INTERFACE_Construct
        ((const INTERFACE***)iface,&cface->comp,linked,
         name,data,parent,previous,next))!=INTERFACE_SUCCESS)
        return result;

    cface->comp.iface=&IBASE__iface.iface;
    *iface=(IBASE**)&cface->comp.iface;
    dbprintf("return IBASE_SUCCESS...\n");
    return IBASE_SUCCESS;
}

int IBASE_Destruct(CBASE *cface)
{
    return INTERFACE_Destruct(&cface->comp);
}

int IBASE_New
(const IBASE ***iface,const char *name,void *data,
 const INTERFACE **parent,const INTERFACE **previous,const INTERFACE **next)
{
#if !defined(_INTERFACE_STATIC)
    CBASE *cface = NULL;

    if (name!=NULL)
    if (INTERFACE_StrCmp(name,IBASE__name))
        return INTERFACE_ERROR_UNKNOWN_NAME;

    dbprintf("cface = INTERFACE_Alloc(sizeof(CBASE) = %d)...\n",sizeof(CBASE));
    if ((cface=INTERFACE_Alloc(sizeof(CBASE)))!=NULL)
    {
        if (IBASE_Construct
            (iface,cface,0,IBASE__name,data,
             parent,previous,next)==INTERFACE_SUCCESS)
            return INTERFACE_SUCCESS;

        INTERFACE_Free(cface);
        return INTERFACE_FAIL;
    }
#endif /* !defined(_INTERFACE_STATIC) */

    return INTERFACE_ERROR_NO_MEMORY;
}

int IBASE_Get(const IBASE ***iface,const char *name)
{
    if (name==NULL)
    {
        *iface=(IBASE**)&CBASE__cface.comp.iface;
        return INTERFACE_SUCCESS;
    }
    return INTERFACE_FAIL;
}

#if defined(_INTERFACE_REGISTER)

int IBASE_Register()
{
    return INTERFACE_Register(&CBASE__cface.comp.iface);
}

int IBASE_Unregister()
{
    return INTERFACE_Unregister(&CBASE__cface.comp.iface);
}

#endif /* defined(_INTERFACE_REGISTER) */

int main(int argc, char** argv, char** env) {
    int err = 0;
    iBase* i = 0;

    dbprintf("iBase_New(&i, NULL, NULL, NULL, NULL, NULL)...\n");
    if (IBASE_SUCCESS == (iBase_New(&i, NULL, NULL, NULL, NULL, NULL))) {
        
        dbprintf("iBase_Unlink(i)...\n");
        iBase_Unlink(i);
    }
    return err;
}
