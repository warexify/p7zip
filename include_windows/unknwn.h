/* #include <windows.h> */

#ifndef _UNKNWN_H
#define _UNKNWN_H

#ifdef __cplusplus
extern "C"{
#endif

#include <basetyps.h>
typedef interface IEnumSTATPROPSTG LPENUMSTATPROPSTG;

#include <wtypes.h>
EXTERN_C const IID IID_IUnknown;
EXTERN_C const IID IID_IClassFactory;
#ifndef __IUnknown_INTERFACE_DEFINED__
#define __IUnknown_INTERFACE_DEFINED__
#undef INTERFACE
#define INTERFACE IUnknown
DECLARE_INTERFACE(IUnknown)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
};
typedef IUnknown *LPUNKNOWN;
#endif
#ifndef __IClassFactory_INTERFACE_DEFINED__
#define __IClassFactory_INTERFACE_DEFINED__
#undef INTERFACE
#define INTERFACE IClassFactory
DECLARE_INTERFACE_(IClassFactory,IUnknown)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD(CreateInstance)(THIS_ LPUNKNOWN,REFIID,PVOID*) PURE;
	STDMETHOD(LockServer)(THIS_ BOOL) PURE;
};
typedef IClassFactory *LPCLASSFACTORY;
#endif
#ifdef __cplusplus
}
#endif
#endif
