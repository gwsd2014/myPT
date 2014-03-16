#ifndef _INTERACTIONCLIENT_H_
#define _INTERACTIONCLIENT_H_

#include <Wincodec.h>
#include <windows.h>
#include <NuiApi.h>
#include <KinectInteraction.h>


class InteractionClient:public INuiInteractionClient {
public:
	InteractionClient()
	{;}
	~InteractionClient()
	{;}

	HRESULT STDMETHODCALLTYPE GetInteractionInfoAtLocation(THIS_ DWORD skeletonTrackingId, NUI_HAND_TYPE handType, FLOAT x, FLOAT y, _Out_ NUI_INTERACTION_INFO *pInteractionInfo)
	{        
		if(pInteractionInfo)
		{
			pInteractionInfo->IsPressTarget         = false;
			pInteractionInfo->PressTargetControlId  = 0;
			pInteractionInfo->PressAttractionPointX = 0.f;
			pInteractionInfo->PressAttractionPointY = 0.f;
			pInteractionInfo->IsGripTarget          = true;
			return S_OK;
		}
		return E_POINTER;
		//return S_OK; 	
	}

	STDMETHODIMP_(ULONG)    AddRef()                                    { return 2;     }
	STDMETHODIMP_(ULONG)    Release()                                   { return 1;     }
	STDMETHODIMP            QueryInterface(REFIID riid, void **ppv)     { return S_OK;  }

 };

#endif