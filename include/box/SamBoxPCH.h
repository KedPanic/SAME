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
#ifndef __SAMBOX_PCH__
#define __SAMBOX_PCH__

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
#include <wx/aui/aui.h>
#include <wx/xrc/xmlres.h>
#include <wx/image.h>
#include <wx/splash.h>
#include <wx/stdpaths.h>
#include <wx/menu.h>
#include <wx/menuitem.h>
#include <wx/dir.h>

#include <SamCommon.h>
#include <SamRenderer.h>
#include <SamInput.h>
#include <SamSound.h>
#include <SamEntitySystem.h>

// Declare custom wxWidgets event.
#include <widgets/CustomEvent.h>

class boxAuiNotebook;
class CProject;
class CSamBox;
class CSplashScreen;

// Global variable.
extern CSamBox *g_pSamBox;

#endif // __SAMBOX_PCH__
