

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 10:14:07 2038
 */
/* Compiler settings for GigeVisionDLL.idl:
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

#ifndef __GigeVisionDLL_i_h__
#define __GigeVisionDLL_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IGigeVision_FWD_DEFINED__
#define __IGigeVision_FWD_DEFINED__
typedef interface IGigeVision IGigeVision;

#endif 	/* __IGigeVision_FWD_DEFINED__ */


#ifndef __GigeVision_FWD_DEFINED__
#define __GigeVision_FWD_DEFINED__

#ifdef __cplusplus
typedef class GigeVision GigeVision;
#else
typedef struct GigeVision GigeVision;
#endif /* __cplusplus */

#endif 	/* __GigeVision_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "shobjidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IGigeVision_INTERFACE_DEFINED__
#define __IGigeVision_INTERFACE_DEFINED__

/* interface IGigeVision */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IGigeVision;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("037fd175-0826-4a01-9b64-5b985c6bf5a3")
    IGigeVision : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetConfig( 
            /* [size_is][in] */ CHAR *iFile) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PayloadSize( 
            /* [out] */ LONG *oPayloadSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE StartCapturing( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetImage( 
            /* [in] */ LONG *iImageIndex,
            /* [size_is][out] */ BYTE *oImage,
            /* [in] */ LONG *iBufferSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetWidth( 
            /* [out] */ LONG *oWidth) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetHeight( 
            /* [out] */ LONG *oHeight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBufferInfo( 
            /* [out] */ LONG *oMinIndex,
            /* [out] */ LONG *oMaxIndex) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTimestamp( 
            /* [in] */ LONG *iIndexTimestamp,
            /* [out] */ LONG *oTimestamp) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IGigeVisionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGigeVision * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGigeVision * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGigeVision * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetConfig )( 
            IGigeVision * This,
            /* [size_is][in] */ CHAR *iFile);
        
        HRESULT ( STDMETHODCALLTYPE *PayloadSize )( 
            IGigeVision * This,
            /* [out] */ LONG *oPayloadSize);
        
        HRESULT ( STDMETHODCALLTYPE *StartCapturing )( 
            IGigeVision * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetImage )( 
            IGigeVision * This,
            /* [in] */ LONG *iImageIndex,
            /* [size_is][out] */ BYTE *oImage,
            /* [in] */ LONG *iBufferSize);
        
        HRESULT ( STDMETHODCALLTYPE *GetWidth )( 
            IGigeVision * This,
            /* [out] */ LONG *oWidth);
        
        HRESULT ( STDMETHODCALLTYPE *GetHeight )( 
            IGigeVision * This,
            /* [out] */ LONG *oHeight);
        
        HRESULT ( STDMETHODCALLTYPE *GetBufferInfo )( 
            IGigeVision * This,
            /* [out] */ LONG *oMinIndex,
            /* [out] */ LONG *oMaxIndex);
        
        HRESULT ( STDMETHODCALLTYPE *GetTimestamp )( 
            IGigeVision * This,
            /* [in] */ LONG *iIndexTimestamp,
            /* [out] */ LONG *oTimestamp);
        
        END_INTERFACE
    } IGigeVisionVtbl;

    interface IGigeVision
    {
        CONST_VTBL struct IGigeVisionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGigeVision_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGigeVision_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGigeVision_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGigeVision_SetConfig(This,iFile)	\
    ( (This)->lpVtbl -> SetConfig(This,iFile) ) 

#define IGigeVision_PayloadSize(This,oPayloadSize)	\
    ( (This)->lpVtbl -> PayloadSize(This,oPayloadSize) ) 

#define IGigeVision_StartCapturing(This)	\
    ( (This)->lpVtbl -> StartCapturing(This) ) 

#define IGigeVision_GetImage(This,iImageIndex,oImage,iBufferSize)	\
    ( (This)->lpVtbl -> GetImage(This,iImageIndex,oImage,iBufferSize) ) 

#define IGigeVision_GetWidth(This,oWidth)	\
    ( (This)->lpVtbl -> GetWidth(This,oWidth) ) 

#define IGigeVision_GetHeight(This,oHeight)	\
    ( (This)->lpVtbl -> GetHeight(This,oHeight) ) 

#define IGigeVision_GetBufferInfo(This,oMinIndex,oMaxIndex)	\
    ( (This)->lpVtbl -> GetBufferInfo(This,oMinIndex,oMaxIndex) ) 

#define IGigeVision_GetTimestamp(This,iIndexTimestamp,oTimestamp)	\
    ( (This)->lpVtbl -> GetTimestamp(This,iIndexTimestamp,oTimestamp) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGigeVision_INTERFACE_DEFINED__ */



#ifndef __GigeVisionDLLLib_LIBRARY_DEFINED__
#define __GigeVisionDLLLib_LIBRARY_DEFINED__

/* library GigeVisionDLLLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_GigeVisionDLLLib;

EXTERN_C const CLSID CLSID_GigeVision;

#ifdef __cplusplus

class DECLSPEC_UUID("11c57dab-9a94-4dce-9ddf-507dd66b7ab4")
GigeVision;
#endif
#endif /* __GigeVisionDLLLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


