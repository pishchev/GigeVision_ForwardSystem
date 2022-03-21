

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


/* interface __MIDL_itf_GigeVisionDLL_0000_0000 */
/* [local] */ 

typedef /* [v1_enum] */ 
enum eImagePixelFormat
    {
        eIP_RAW	= 0,
        eIP_RGB24_FAST	= ( eIP_RAW + 1 ) ,
        eIP_RGB24_FINE	= ( eIP_RGB24_FAST + 1 ) ,
        eIP_UYVY_FAST	= ( eIP_RGB24_FINE + 1 ) ,
        eIP_UYVY_FINE	= ( eIP_UYVY_FAST + 1 ) 
    } 	eImagePixelFormat;



extern RPC_IF_HANDLE __MIDL_itf_GigeVisionDLL_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_GigeVisionDLL_0000_0000_v0_0_s_ifspec;

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
            /* [in] */ BSTR bstrFileName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetImageInfo( 
            /* [out] */ LONG *oWidth,
            /* [out] */ LONG *oHeight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Start( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFifoInfo( 
            /* [out] */ LONG *oMinIndex,
            /* [out] */ LONG *oMaxIndex) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetImage( 
            /* [in] */ LONG iImageIndex,
            /* [in] */ eImagePixelFormat iFormat,
            /* [size_is][out] */ BYTE *oImage,
            /* [in] */ LONG iImageSize,
            /* [out] */ LONG *oImageTimestamp) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Stop( void) = 0;
        
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
            /* [in] */ BSTR bstrFileName);
        
        HRESULT ( STDMETHODCALLTYPE *GetImageInfo )( 
            IGigeVision * This,
            /* [out] */ LONG *oWidth,
            /* [out] */ LONG *oHeight);
        
        HRESULT ( STDMETHODCALLTYPE *Start )( 
            IGigeVision * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetFifoInfo )( 
            IGigeVision * This,
            /* [out] */ LONG *oMinIndex,
            /* [out] */ LONG *oMaxIndex);
        
        HRESULT ( STDMETHODCALLTYPE *GetImage )( 
            IGigeVision * This,
            /* [in] */ LONG iImageIndex,
            /* [in] */ eImagePixelFormat iFormat,
            /* [size_is][out] */ BYTE *oImage,
            /* [in] */ LONG iImageSize,
            /* [out] */ LONG *oImageTimestamp);
        
        HRESULT ( STDMETHODCALLTYPE *Stop )( 
            IGigeVision * This);
        
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


#define IGigeVision_SetConfig(This,bstrFileName)	\
    ( (This)->lpVtbl -> SetConfig(This,bstrFileName) ) 

#define IGigeVision_GetImageInfo(This,oWidth,oHeight)	\
    ( (This)->lpVtbl -> GetImageInfo(This,oWidth,oHeight) ) 

#define IGigeVision_Start(This)	\
    ( (This)->lpVtbl -> Start(This) ) 

#define IGigeVision_GetFifoInfo(This,oMinIndex,oMaxIndex)	\
    ( (This)->lpVtbl -> GetFifoInfo(This,oMinIndex,oMaxIndex) ) 

#define IGigeVision_GetImage(This,iImageIndex,iFormat,oImage,iImageSize,oImageTimestamp)	\
    ( (This)->lpVtbl -> GetImage(This,iImageIndex,iFormat,oImage,iImageSize,oImageTimestamp) ) 

#define IGigeVision_Stop(This)	\
    ( (This)->lpVtbl -> Stop(This) ) 

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

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  BSTR_UserSize64(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal64(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal64(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree64(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


