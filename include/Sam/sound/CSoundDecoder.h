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
#ifndef __CSOUND_DECODER__
#define __CSOUND_DECODER__

namespace sam
{
	/// @brief Sound decoder.
	/// 
	/// @remark 
	///		Default formats are platform specific.
	class CSoundDecoder
	{
	public:
		/// @brief Default constructor.
		CSoundDecoder();

		/// @brief Destructor.
		~CSoundDecoder();

		/// @brief Load specified plugin.
		/// 
		/// @param _sPluginName Name of the plugin.
		/// 
		/// @return EResult_Success or error code.
		EResult LoadPlugin(const char *_sPluginName);

		/// @brief Unload specified plugin.
		/// 
		/// @param _sPluginName Name of the plugin.
		/// 
		/// @return EResult_Success or error code.
		EResult UnloadPlugin(const char *_sPluginName);

		/// @brief Add decoder.
		/// 

	private:
	};
}

#endif // __CSOUND_DECODER__
