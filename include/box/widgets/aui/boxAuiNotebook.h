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
#ifndef __BOXAUINOTEBOOK__
#define __BOXAUINOTEBOOK__

/// @brief
class boxAuiNotebook : public wxAuiNotebook
{
public:
	/// @brief Constructor
	///
	/// @param p_pParent
	/// @param p_nId
	/// @param p_oPos
	/// @param p_oSize
	/// @param p_nStyle
	boxAuiNotebook(wxWindow* p_pParent, wxWindowID p_nId = wxID_ANY, const wxPoint& p_oPos = wxDefaultPosition, const wxSize& p_oSize = wxDefaultSize, long p_nStyle = wxAUI_NB_DEFAULT_STYLE);

private:
};

#endif // __BOXAUINOTEBOOK__