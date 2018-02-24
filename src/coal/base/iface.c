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
 *   File: iface.c
 *
 * Author: $author$
 *   Date: 2/23/2018
 **********************************************************************
 */
#include "coal/base/iface.h"

#define COMPONENT_P(cface) ((COMPONENT*)cface)

/*
 * INTERFACE name
 */
const char INTERFACE__name[] = "Interface";

/*
 * INTERFACE iface
 */
const INTERFACE INTERFACE__iface = 
{
    INTERFACE__SetName,
    INTERFACE__GetName,
    INTERFACE__SetData,
    INTERFACE__GetData,
    INTERFACE__SetLink,
    INTERFACE__Link,
    INTERFACE__Unlink,
    INTERFACE__New,
}; /* INTERFACE */

/*
 * COMPONENT cface
 */
const COMPONENT COMPONENT__cface = 
{
    &INTERFACE__iface,
}; /* COMPONENT */

/*
 * INTERFACE methods
 */
int METHOD INTERFACE__SetName(const INTERFACE **cface,const char *name)
{
    COMPONENT_P(cface)->name = name;
    dbprintf("return INTERFACE_SUCCESS...\n");
    return INTERFACE_SUCCESS;
}

int METHOD INTERFACE__GetName(const INTERFACE **cface,const char **name)
{
    *name = COMPONENT_P(cface)->name;
    dbprintf("return INTERFACE_SUCCESS...\n");
    return INTERFACE_SUCCESS;
}

int METHOD INTERFACE__SetData(const INTERFACE **cface,void *data)
{
    COMPONENT_P(cface)->data = data;
    dbprintf("return INTERFACE_SUCCESS...\n");
    return INTERFACE_SUCCESS;
}

int METHOD INTERFACE__GetData(const INTERFACE **cface,void **data)
{
    *data = COMPONENT_P(cface)->data;
    dbprintf("return INTERFACE_SUCCESS...\n");
    return INTERFACE_SUCCESS;
}

int METHOD INTERFACE__SetLink(const INTERFACE **cface,const INTERFACE **iface,unsigned to,const char *name)
{
    dbprintf("return INTERFACE_FAIL...\n");
    return INTERFACE_FAIL;
}

int METHOD INTERFACE__Link(const INTERFACE **cface,const INTERFACE ***iface,unsigned to,const char *name)
{
    switch(to)
    {
    case INTERFACE_TO_NAME:
        if ((name == NULL)||(COMPONENT_P(cface)->name == NULL))
            return INTERFACE_FAIL;
        else if (INTERFACE_StrCmp(COMPONENT_P(cface)->name,name) != 0)
                return INTERFACE_FAIL;

    case INTERFACE_TO_THIS:
        if (COMPONENT_P(cface)->parent != NULL)
        {
            if (INTERFACE_Link
                (COMPONENT_P(cface)->parent,iface,
                 INTERFACE_TO_THIS,name) != INTERFACE_SUCCESS)
                return INTERFACE_FAIL;
            
            *iface = cface;
            return INTERFACE_SUCCESS;            
        }
        if (COMPONENT_P(cface)->linked >= 0)
            COMPONENT_P(cface)->linked++;
        *iface = cface;
        return INTERFACE_SUCCESS;

    case INTERFACE_TO_PARENT:
        if (COMPONENT_P(cface)->parent != NULL)
            return INTERFACE_Link(COMPONENT_P(cface)->parent,iface,INTERFACE_TO_THIS,name);
        return INTERFACE_ERROR_END_LINK;

    case INTERFACE_TO_PREVIOUS:
        if (COMPONENT_P(cface)->previous != NULL)
            return INTERFACE_Link(COMPONENT_P(cface)->previous,iface,INTERFACE_TO_THIS,name);
        if (COMPONENT_P(cface)->parent != NULL)
            return INTERFACE_Link(COMPONENT_P(cface)->parent,iface,INTERFACE_TO_PREVIOUS,name);
        return INTERFACE_ERROR_END_LINK;

    case INTERFACE_TO_NEXT:
        if (COMPONENT_P(cface)->next != NULL)
            return INTERFACE_Link(COMPONENT_P(cface)->next,iface,INTERFACE_TO_THIS,name);
        if (COMPONENT_P(cface)->parent != NULL)
            return INTERFACE_Link(COMPONENT_P(cface)->parent,iface,INTERFACE_TO_NEXT,name);
        return INTERFACE_ERROR_END_LINK;

    case INTERFACE_TO_FIRST:
    case INTERFACE_TO_LAST:
        return INTERFACE_FAIL;
    }

    dbprintf("return INTERFACE_FAIL...\n");
    return INTERFACE_FAIL;
}

int METHOD INTERFACE__Unlink(const INTERFACE **cface)
{
    if (COMPONENT_P(cface)->parent != NULL)
        return INTERFACE_Unlink(COMPONENT_P(cface)->parent);

    if (COMPONENT_P(cface)->linked>0)
        COMPONENT_P(cface)->linked--;

#ifndef _INTERFACE_STATIC
    else if (COMPONENT_P(cface)->linked == 0) 
            INTERFACE_Free(COMPONENT_P(cface));
#endif /* ndef _INTERFACE_STATIC */

    dbprintf("return INTERFACE_SUCCESS...\n");
    return INTERFACE_SUCCESS;
}

int METHOD INTERFACE__New
(const INTERFACE **cface,
 const INTERFACE ***iface,const char *name,void *data,
 const INTERFACE **parent,const INTERFACE **previous,const INTERFACE **next)
{
#ifndef _INTERFACE_STATIC
    COMPONENT *comp = NULL;
    int status = INTERFACE_FAIL;

    if (name != NULL)
    if (INTERFACE_StrCmp(name,INTERFACE__name) != 0) {
        dbprintf("return INTERFACE_ERROR_UNKNOWN_NAME...\n");
        return INTERFACE_ERROR_UNKNOWN_NAME;
    }

    dbprintf("INTERFACE_Alloc(sizeof(COMPONENT) = %d)...\n",sizeof(COMPONENT));
    if ((comp = INTERFACE_Alloc(sizeof(COMPONENT))) != NULL)
    {
        if ((status = INTERFACE_Construct
            (iface,comp,0,INTERFACE__name,data,
             parent,previous,next)) != INTERFACE_SUCCESS)
            INTERFACE_Free(comp);
        return status;
    }
#endif /* ndef _INTERFACE_STATIC */

    dbprintf("return INTERFACE_ERROR_NO_MEMORY...\n");
    return INTERFACE_ERROR_NO_MEMORY;
}

/*
 * INTERFACE functions
 */
int INTERFACE_Construct
(const INTERFACE ***iface,COMPONENT *cface,
 signed linked,const char *name,void *data,
 const INTERFACE **parent,const INTERFACE **previous,const INTERFACE **next)
{
    if (name == NULL)
        name = INTERFACE__name;

    cface->iface = &INTERFACE__iface;
    cface->linked = linked;
    cface->name = name;
    cface->data = data;
    cface->parent = parent;
    cface->previous = previous;
    cface->next = next;
    cface->first = NULL;
    cface->last = NULL;
    *iface = &cface->iface;
    dbprintf("return INTERFACE_SUCCESS...\n");
    return INTERFACE_SUCCESS;
}

int INTERFACE_Destruct(COMPONENT *cface)
{
    dbprintf("return INTERFACE_SUCCESS...\n");
    return INTERFACE_SUCCESS;
}

int INTERFACE_GetNew
(const INTERFACE ***iface,void **position,const char *name,void *data,
 const INTERFACE **parent,const INTERFACE **previous,const INTERFACE **next)
{
    return INTERFACE__New
    (&COMPONENT__cface, iface, name, data, parent, previous, next);
}