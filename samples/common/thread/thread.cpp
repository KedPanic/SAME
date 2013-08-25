//===========================================
// Copyright (C) 2013 Cedric Liaudet
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
// of the Software, and to permit persons to whom the Software is furnished to
// do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//===========================================
#include "IApplication.h"

//////////////////////////////////////////////////////////////////////////
// JOB CONFIGURATION
//////////////////////////////////////////////////////////////////////////
static const uint32 s_nNbJob = 2048;
static const uint32 s_nBitmapWidth = 256;
static const uint32 s_nBitmapHeight = 256;

//////////////////////////////////////////////////////////////////////////
//		NOISE JOB
//////////////////////////////////////////////////////////////////////////
struct SNoise
{
	uint32 x;
	uint32 y;
	uint8  *noise;
};

void GenerateNoiseTexture(void *p_pData)
{
	SNoise *pNoise = (SNoise*)p_pData;

	// generate noise.	
	pNoise->noise  = (uint8*)malloc(sizeof(uint8) * s_nBitmapWidth * s_nBitmapHeight * 3);
	for(pNoise->y = 0; pNoise->y < s_nBitmapHeight; pNoise->y++)
	{
		for(pNoise->x = 1; pNoise->x <= s_nBitmapWidth; pNoise->x++)
		{
			pNoise->noise[pNoise->x * pNoise->y + 0] = (uint8)(((rand() % 32768) / 32768.0f) * 256); // red	channel
			pNoise->noise[pNoise->x * pNoise->y + 1] = pNoise->noise[pNoise->x * pNoise->y + 0];	 // green channel
			pNoise->noise[pNoise->x * pNoise->y + 2] = pNoise->noise[pNoise->x * pNoise->y + 0];	 // blue channel
		}
	}

	free(pNoise->noise);
}

// Sample application.
class CApplication : public IApplication
{
public:
	CApplication()
		: IApplication("Sample: basic")
	{
	}

	virtual bool PostInit()
	{
		uint32 nNbCores = sam::g_oSystem.m_oCPU.m_nNbCores;

		// set the affinity per core.
		uint32 *anAffinities = SAM_ALLOC_ARRAY(uint32, nNbCores);
		for(uint32 index = 0; index < nNbCores; ++index)
		{
			anAffinities[index] = sam::e_Processor_Any;
		}

		// Create and start thread.
		sam::g_Env->pJobManager->Initialize(32, nNbCores, anAffinities);

		// create job list.		
 		sam::CJobArray *pJob = SAM_NEW sam::CJobArray(s_nNbJob);
		for(uint32 jobIndex = 0; jobIndex < s_nNbJob; jobIndex++)
		{
			SNoise *pNoise = SAM_ALLOC(SNoise);
			pNoise->x = 0;
			pNoise->y = 0;

			sam::SJob oJob;
			oJob.m_pData = pNoise;
			oJob.m_pfCallback = &GenerateNoiseTexture;

			pJob->AddJob(oJob);
		}

		// send job list to thread.
 		sam::g_Env->pJobManager->Submit(pJob);

		return true;
	}

	virtual void Update(f32 p_fDelta)
	{
		// nothing to do.
	}	
};

IApplication* CreateApplication()
{
	return new CApplication;
}
