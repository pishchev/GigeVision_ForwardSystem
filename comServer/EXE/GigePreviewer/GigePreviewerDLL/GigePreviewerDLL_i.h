

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
        virtual HRESULT STDMETHODCALLTYPE useLibrary( 
            /* [size_is][in] */ CHAR *libFile) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE getInterfacesSize( 
            /* [out] */ BYTE *oInterfacesSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE getInterfaceName( 
            /* [size_is][out] */ CHAR *oName,
            /* [in] */ BYTE iIndex) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE setInterface( 
            /* [size_is][in] */ CHAR *iInterface) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE getDevicesSize( 
            /* [out] */ BYTE *oDevicesSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE getDeviceName( 
            /* [size_is][out] */ CHAR *oName,
            /* [in] */ BYTE iIndex) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE setDevice( 
            /* [size_is][in] */ CHAR *iDevice) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE getStreamsSize( 
            /* [out] */ BYTE *oStreamsSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE getStreamName( 
            /* [size_is][out] */ CHAR *oName,
            /* [in] */ BYTE iIndex) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE setStream( 
            /* [size_is][in] */ CHAR *iStream) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE cameraInit( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE useConfig( 
            /* [size_is][in] */ CHAR *node) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE saveConfig( 
            /* [size_is][in] */ CHAR *node) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE getNodesSize( 
            /* [out] */ BYTE *size) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE getNodeName( 
            /* [size_is][out] */ CHAR *oName,
            /* [in] */ BYTE iIndex) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE getNodeVisibility( 
            /* [out] */ BYTE *oVis,
            /* [in] */ BYTE iIndex) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE getNodeAccessMode( 
            /* [out] */ BYTE *oAm,
            /* [in] */ BYTE iIndex) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE getNodeType( 
            /* [out] */ BYTE *oType,
            /* [in] */ BYTE iIndex) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE getIntNode( 
            /* [size_is][in] */ CHAR *node,
            /* [out] */ LONG *oVal) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE setIntNode( 
            /* [size_is][in] */ CHAR *node,
            /* [in] */ LONG iVal) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE getEnumStrNode( 
            /* [size_is][in] */ CHAR *node,
            /* [size_is][out] */ CHAR *oVal) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE getStrNode( 
            /* [size_is][in] */ CHAR *node,
            /* [size_is][out] */ CHAR *oVal) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE startAquisition( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE getImage( 
            /* [size_is][out] */ BYTE *image,
            /* [in] */ LONG len) = 0;
        
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
        
        HRESULT ( STDMETHODCALLTYPE *useLibrary )( 
            IPreviewer * This,
            /* [size_is][in] */ CHAR *libFile);
        
        HRESULT ( STDMETHODCALLTYPE *getInterfacesSize )( 
            IPreviewer * This,
            /* [out] */ BYTE *oInterfacesSize);
        
        HRESULT ( STDMETHODCALLTYPE *getInterfaceName )( 
            IPreviewer * This,
            /* [size_is][out] */ CHAR *oName,
            /* [in] */ BYTE iIndex);
        
        HRESULT ( STDMETHODCALLTYPE *setInterface )( 
            IPreviewer * This,
            /* [size_is][in] */ CHAR *iInterface);
        
        HRESULT ( STDMETHODCALLTYPE *getDevicesSize )( 
            IPreviewer * This,
            /* [out] */ BYTE *oDevicesSize);
        
        HRESULT ( STDMETHODCALLTYPE *getDeviceName )( 
            IPreviewer * This,
            /* [size_is][out] */ CHAR *oName,
            /* [in] */ BYTE iIndex);
        
        HRESULT ( STDMETHODCALLTYPE *setDevice )( 
            IPreviewer * This,
            /* [size_is][in] */ CHAR *iDevice);
        
        HRESULT ( STDMETHODCALLTYPE *getStreamsSize )( 
            IPreviewer * This,
            /* [out] */ BYTE *oStreamsSize);
        
        HRESULT ( STDMETHODCALLTYPE *getStreamName )( 
            IPreviewer * This,
            /* [size_is][out] */ CHAR *oName,
            /* [in] */ BYTE iIndex);
        
        HRESULT ( STDMETHODCALLTYPE *setStream )( 
            IPreviewer * This,
            /* [size_is][in] */ CHAR *iStream);
        
        HRESULT ( STDMETHODCALLTYPE *cameraInit )( 
            IPreviewer * This);
        
        HRESULT ( STDMETHODCALLTYPE *useConfig )( 
            IPreviewer * This,
            /* [size_is][in] */ CHAR *node);
        
        HRESULT ( STDMETHODCALLTYPE *saveConfig )( 
            IPreviewer * This,
            /* [size_is][in] */ CHAR *node);
        
        HRESULT ( STDMETHODCALLTYPE *getNodesSize )( 
            IPreviewer * This,
            /* [out] */ BYTE *size);
        
        HRESULT ( STDMETHODCALLTYPE *getNodeName )( 
            IPreviewer * This,
            /* [size_is][out] */ CHAR *oName,
            /* [in] */ BYTE iIndex);
        
        HRESULT ( STDMETHODCALLTYPE *getNodeVisibility )( 
            IPreviewer * This,
            /* [out] */ BYTE *oVis,
            /* [in] */ BYTE iIndex);
        
        HRESULT ( STDMETHODCALLTYPE *getNodeAccessMode )( 
            IPreviewer * This,
            /* [out] */ BYTE *oAm,
            /* [in] */ BYTE iIndex);
        
        HRESULT ( STDMETHODCALLTYPE *getNodeType )( 
            IPreviewer * This,
            /* [out] */ BYTE *oType,
            /* [in] */ BYTE iIndex);
        
        HRESULT ( STDMETHODCALLTYPE *getIntNode )( 
            IPreviewer * This,
            /* [size_is][in] */ CHAR *node,
            /* [out] */ LONG *oVal);
        
        HRESULT ( STDMETHODCALLTYPE *setIntNode )( 
            IPreviewer * This,
            /* [size_is][in] */ CHAR *node,
            /* [in] */ LONG iVal);
        
        HRESULT ( STDMETHODCALLTYPE *getEnumStrNode )( 
            IPreviewer * This,
            /* [size_is][in] */ CHAR *node,
            /* [size_is][out] */ CHAR *oVal);
        
        HRESULT ( STDMETHODCALLTYPE *getStrNode )( 
            IPreviewer * This,
            /* [size_is][in] */ CHAR *node,
            /* [size_is][out] */ CHAR *oVal);
        
        HRESULT ( STDMETHODCALLTYPE *startAquisition )( 
            IPreviewer * This);
        
        HRESULT ( STDMETHODCALLTYPE *getImage )( 
            IPreviewer * This,
            /* [size_is][out] */ BYTE *image,
            /* [in] */ LONG len);
        
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


#define IPreviewer_useLibrary(This,libFile)	\
    ( (This)->lpVtbl -> useLibrary(This,libFile) ) 

#define IPreviewer_getInterfacesSize(This,oInterfacesSize)	\
    ( (This)->lpVtbl -> getInterfacesSize(This,oInterfacesSize) ) 

#define IPreviewer_getInterfaceName(This,oName,iIndex)	\
    ( (This)->lpVtbl -> getInterfaceName(This,oName,iIndex) ) 

#define IPreviewer_setInterface(This,iInterface)	\
    ( (This)->lpVtbl -> setInterface(This,iInterface) ) 

#define IPreviewer_getDevicesSize(This,oDevicesSize)	\
    ( (This)->lpVtbl -> getDevicesSize(This,oDevicesSize) ) 

#define IPreviewer_getDeviceName(This,oName,iIndex)	\
    ( (This)->lpVtbl -> getDeviceName(This,oName,iIndex) ) 

#define IPreviewer_setDevice(This,iDevice)	\
    ( (This)->lpVtbl -> setDevice(This,iDevice) ) 

#define IPreviewer_getStreamsSize(This,oStreamsSize)	\
    ( (This)->lpVtbl -> getStreamsSize(This,oStreamsSize) ) 

#define IPreviewer_getStreamName(This,oName,iIndex)	\
    ( (This)->lpVtbl -> getStreamName(This,oName,iIndex) ) 

#define IPreviewer_setStream(This,iStream)	\
    ( (This)->lpVtbl -> setStream(This,iStream) ) 

#define IPreviewer_cameraInit(This)	\
    ( (This)->lpVtbl -> cameraInit(This) ) 

#define IPreviewer_useConfig(This,node)	\
    ( (This)->lpVtbl -> useConfig(This,node) ) 

#define IPreviewer_saveConfig(This,node)	\
    ( (This)->lpVtbl -> saveConfig(This,node) ) 

#define IPreviewer_getNodesSize(This,size)	\
    ( (This)->lpVtbl -> getNodesSize(This,size) ) 

#define IPreviewer_getNodeName(This,oName,iIndex)	\
    ( (This)->lpVtbl -> getNodeName(This,oName,iIndex) ) 

#define IPreviewer_getNodeVisibility(This,oVis,iIndex)	\
    ( (This)->lpVtbl -> getNodeVisibility(This,oVis,iIndex) ) 

#define IPreviewer_getNodeAccessMode(This,oAm,iIndex)	\
    ( (This)->lpVtbl -> getNodeAccessMode(This,oAm,iIndex) ) 

#define IPreviewer_getNodeType(This,oType,iIndex)	\
    ( (This)->lpVtbl -> getNodeType(This,oType,iIndex) ) 

#define IPreviewer_getIntNode(This,node,oVal)	\
    ( (This)->lpVtbl -> getIntNode(This,node,oVal) ) 

#define IPreviewer_setIntNode(This,node,iVal)	\
    ( (This)->lpVtbl -> setIntNode(This,node,iVal) ) 

#define IPreviewer_getEnumStrNode(This,node,oVal)	\
    ( (This)->lpVtbl -> getEnumStrNode(This,node,oVal) ) 

#define IPreviewer_getStrNode(This,node,oVal)	\
    ( (This)->lpVtbl -> getStrNode(This,node,oVal) ) 

#define IPreviewer_startAquisition(This)	\
    ( (This)->lpVtbl -> startAquisition(This) ) 

#define IPreviewer_getImage(This,image,len)	\
    ( (This)->lpVtbl -> getImage(This,image,len) ) 

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


