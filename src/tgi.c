#include "tgi.h"

#include "gdi.h"

#include <stddef.h>

TGI_Application *TGIAPI tgi_application_create(TGI_Backend backend, TGI_Encoding encoding)
{
    if (backend == TGI_BACKEND_GDI)
    {
        return tgi_application_gdi_create(encoding);
    }
    return NULL;
}