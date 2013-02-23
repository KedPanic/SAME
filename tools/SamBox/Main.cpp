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
#include <SamBoxPCH.h>
#include <common/SamModuleInit.h>
#include "CSamBox.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	sam::g_Env = sam::InitCommon();
	sam::ModuleInit(sam::g_Env);

	// Create app folder.
	QString sSamBoxFolder;
	{
		char sAppPath[MAX_PATH];
		if(sam::GetAppPath(sAppPath))
		{
			sSamBoxFolder = sAppPath;
			sSamBoxFolder += "/SamBox";

			QDir oSamBoxFolder(sSamBoxFolder);
			if(oSamBoxFolder.exists() == false)
			{
				oSamBoxFolder.mkdir(sSamBoxFolder);
			}

#ifndef SAM_MASTER
			QByteArray sLogFile = (sSamBoxFolder + "/SamBox.log").toLocal8Bit();
			sam::g_Env->pLog->SetFilename(sLogFile.data());
#endif
		}
		else
		{
			sSamBoxFolder = ".";
		}
	}
	
	// Initialize Qt
	QApplication oApp(argc, argv);

	// Initialization of the engine.
	sam::box::CSamBox oRoot(sSamBoxFolder);
	oRoot.Initialize();	

	return oApp.exec();
}
