

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 10:14:07 2038
 */
/* Compiler settings for GigePreviewerDLL.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0622 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __GigePreviewerDLL_i_h__
#define __GigePreviewerDLL_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IPreviewer_FWD_DEFINED__
#define __IPreviewer_FWD_DEFINED__
typedef interface IPreviewer IPreviewer;

#endif 	/* __IPreviewer_FWD_DEFINED__ */


#ifndef __Previewer_FWD_DEFINED__
#define __Previewer_FWD_DEFINED__

#ifdef __cplusplus
typedef class Previewer Previewer;
#else
typedef struct Previewer Previewer;
#endif /* __cplusplus */

#endif 	/* __Previewer_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "shobjidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IPreviewer_INTERFACE_DEFINED__
#define __IPreviewer_INTERFACE_DEFINED__

/* interface IPreviewer */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IPreviewer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6e9426a3-85f5-466d-8b3a-d86a6d5fb87c")
    IPreviewer : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetImage( 
            /* [in] */ LONG iLen,
            /* [size_is][out] */ BYTE *oImage) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE StartAquisition( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPayloadSize( 
            /* [out] */ LONG *oPayloadSize) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPreviewerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPreviewer * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPreviewer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPreviewer * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetImage )( 
            IPreviewer * This,
            /* [in] */ LONG iLen,
            /* [size_is][out] */ BYTE *oImage);
        
        HRESULT ( STDMETHODCALLTYPE *StartAquisition )( 
            IPreviewer * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetPayloadSize )( 
            IPreviewer * This,
            /* [out] */ LONG *oPayloadSize);
        
        END_INTERFACE
    } IPreviewerVtbl;

    interface IPreviewer
    {
        CONST_VTBL struct IPreviewerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPreviewer_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPreviewer_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPreviewer_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPreviewer_GetImage(This,iLen,oImage)	\
    ( (This)->lpVtbl -> GetImage(This,iLen,oImage) ) 

#define IPreviewer_StartAquisition(This)	\
    ( (This)->lpVtbl -> StartAquisition(This) ) 

#define IPreviewer_GetPayloadSize(This,oPayloadSize)	\
    ( (This)->lpVtbl -> GetPayloadSize(This,oPayloadSize) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPreviewer_INTERFACE_DEFINED__ */



#ifndef __GigePreviewerDLLLib_LIBRARY_DEFINED__
#define __GigePreviewerDLLLib_LIBRARY_DEFINED__

/* library GigePreviewerDLLLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_GigePreviewerDLLLib;

EXTERN_C const CLSID CLSID_Previewer;

#ifdef __cplusplus

class DECLSPEC_UUID("24d9e0a6-e838-47e7-947e-2a7391acdfab")
Previewer;
#endif
#endif /* __GigePreviewerDLLLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


