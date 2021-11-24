

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 10:14:07 2038
 */
/* Compiler settings for GigePreviewer.idl:
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

#ifndef __GigePreviewer_i_h__
#define __GigePreviewer_i_h__

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
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IPreviewer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0bac97ac-03f6-4153-9fc7-23e994f3d4be")
    IPreviewer : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE StartAcquisition( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetPayloadSize( 
            /* [out] */ BYTE *oPayloadSize) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetImage( 
            /* [out] */ BYTE *oImage) = 0;
        
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
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPreviewer * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPreviewer * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPreviewer * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPreviewer * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *StartAcquisition )( 
            IPreviewer * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetPayloadSize )( 
            IPreviewer * This,
            /* [out] */ BYTE *oPayloadSize);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetImage )( 
            IPreviewer * This,
            /* [out] */ BYTE *oImage);
        
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


#define IPreviewer_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IPreviewer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IPreviewer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IPreviewer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IPreviewer_StartAcquisition(This)	\
    ( (This)->lpVtbl -> StartAcquisition(This) ) 

#define IPreviewer_GetPayloadSize(This,oPayloadSize)	\
    ( (This)->lpVtbl -> GetPayloadSize(This,oPayloadSize) ) 

#define IPreviewer_GetImage(This,oImage)	\
    ( (This)->lpVtbl -> GetImage(This,oImage) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPreviewer_INTERFACE_DEFINED__ */



#ifndef __GigePreviewerLib_LIBRARY_DEFINED__
#define __GigePreviewerLib_LIBRARY_DEFINED__

/* library GigePreviewerLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_GigePreviewerLib;

EXTERN_C const CLSID CLSID_Previewer;

#ifdef __cplusplus

class DECLSPEC_UUID("e5fae7b4-cf25-4915-bb33-b61b182459fb")
Previewer;
#endif
#endif /* __GigePreviewerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


