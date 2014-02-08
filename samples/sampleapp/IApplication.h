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
#ifndef __SAMPLE_APPLICATION__
#define __SAMPLE_APPLICATION__

#include <SamCommon.h>
#if !defined(CONSOLE_APP)
#	include <SamRenderer.h>
#	include <SamEntitySystem.h>
#endif

/*
	Simple root class used to initialize common module, the renderer and some specific platform stuffs.
*/
class IApplication
{
public:
	IApplication(const char* p_sTitle);
	~IApplication();


	// Initialize common and renderer module.
	// Create the window.
	bool Initialize();

	// Main loop.
	// Clean screen, call render method.
	void Run();

	// Internal use to close the application.
	void Close() {m_bRun = false;}

	// Called at the end of the initialization.
	// Used to create specific stuffs required by the sample.
	virtual bool PostInit() = 0;

	// Called to render the sample :)
	virtual void Render() {}

	// Called to update the sample :)
	virtual void Update(f32 p_fDelta) {}

private:
	char *m_sTitle; ///< Title of the window.
	bool m_bRun; ///< Flag used to close the application.

#if !defined(CONSOLE_APP)
protected:
	sam::Matrix44 m_mWorld;
#endif

	// Called when we close the application.
	void Shutdown();
};

// have to be implemented by the sample.
extern IApplication* CreateApplication();

#endif // __SAMPLE_APPLICATION__
