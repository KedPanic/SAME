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
#ifndef __SR_CFLASH_PLAYER__
#define __SR_CFLASH_PLAYER__

namespace sam
{
    class CFlashEvent;
    class CFlashControlSite;

    /// @brief Interface for flash player.
    class SAM_RENDERER_API CFlashPlayer : public IAllocated public IFSCommandListener, public IExternalInterfaceListener
    {
        friend class CRenderWindow;

    public:        
        /// @brief Load movie clip.
        /// 
        /// @param _sFile File to load.
        void Load(const String &_sFile);

        /// @brief Set position on X-Axis.
        /// 
        /// @param _iXPos Position on X-Axis.
        void SetXPos(int _iXPos);

        /// @brief Set position on Y-Axis.
        /// 
        /// @param _iYPos Position on Y-Axis.
        void SetYPos(int _iYPos);

        /// @brief Retrieves width.
        /// 
        /// @return Width of the flash player.
        int GetWidth() const {return m_iWidth;}

        /// @brief Retrieves height.
        /// 
        /// @return Height of the flash player.
        int GetHeight() const {return m_iHeight;}

        /*****************************************/
        /*                 PLAYER                */
        /*****************************************/
        /// @brief Play.
        void Play();

        /// @brief Pause.
        void Pause();

        /// @brief Stop.
        void Stop();

        /// @brief Rewind.
        void Rewind();

        /// @brief Goto the specified frame by number.
        /// 
        /// @param _iFrame Number of frame to go.
        void Goto(long _iFrame);

        /// @brief Goto the specified frame by label.
        /// 
        /// @param _sLabel Label of the frame to go.
        void Goto(const String &_sFrame);

        /*****************************************/
        /*               RENDERING               */
        /*****************************************/
        /// @brief Set rendering quality.
        /// 
        /// @param _eQuality Rendering quality.
        void SetQuality(sam::EFlashQuality _eQuality);

        /// @brief Set scale mode.
        /// 
        /// @param _eScale Scale mode.
        void SetScale(sam::EFlashScale _eScale);

        /// @brief Set alignment.
        /// 
        /// @param _iAlignment Alignment.
        void SetAlignment(int _iAlignment);

        /// @brief Set background color.
        /// 
        /// @param _Red Red channel.
        /// @param _Green Green channel.
        /// @param _Blue Blue channel.
        void SetBackgroundColor(uint8 _Red, uint8 _Green, uint8 _Blue);

        /// @brief Get background color.
        /// 
        /// @param _Red Red channel.
        /// @param _Green Green channel.
        /// @param _Blue Blue channel.
        void GetBackgroundColor(uint8 &_Red, uint8 &_Green, uint8 &_Blue);

        /// @brief Set if it's transparent.
        ///
        /// @param _bTransparent True to make it transparent.
        void SetTransparent(bool _bTransparent);

        /// @brief Set dirty rectangle which have to be drawn again.
        /// 
        /// @param _iLeft Left position.
        /// @param _iTop Top position.
        /// @param _iRight Right position.
        /// @param _iBottom Bottom position.
        void InvalidateRect(int _iLeft, int _iTop, int _iRight, int _iBottom);
        
        /// @brief Render the movie clip.
        void Render();

        /*****************************************/
        /*               CALLBACK                */
        /*****************************************/
        /// @brief Set the fscommand listener.
        /// 
        /// @param _pFSCommandListener FSCommand listener.
        void SetFSCommandListener(sam::IFSCommandListener *_pFSCommandListener);

        /// @brief Set the ExternalInterface listener.
        /// 
        /// @param _pExternalInterfaceListener ExternalInterface listener.
        void SetExternalInterfaceListener(sam::IExternalInterfaceListener *_pExternalInterfaceListener);

        /*****************************************/
        /*            ACTION SCRIPT              */
        /*****************************************/
        /// @brief Set variable.
        /// 
        /// @param _sVariable Variable name.
        /// @param _Value Value of the specified variable.
        void SetVariable(const UString &_sVariable, const sam::SFlashArgument &_Value);

        /// @brief Retrieves value of the specified variable.
        /// 
        /// @param _sVariable Variable name.
        /// @param _Value Value of the specified variable.
        void GetVariable(const UString &_sVariable, sam::SFlashArgument *_Value);

        /// @brief Invoke action script function.
        /// 
        /// @param _sFunction Function name.
        /// @param _pArgs Array of arguments.
        /// @param _iNbArgs Size of the array.
        /// @param _pResult Function result.
        void Invoke(const UString &_sFunction, const sam::SFlashArgument *_pArgs, uint32 _iNbArgs, sam::SFlashArgument *_pResult = 0);

        /*****************************************/
        /*              VISIBILITY               */
        /*****************************************/
        /// @brief Set if it's visibility
        /// 
        /// @param _bVisible True to make it visible.
        void SetVisible(bool _bVisible) {m_bVisible = _bVisible;}

        /// @brief Retrieves if it's visible.
        /// 
        /// @return True if it's visible.
        bool GetVisible() const {return m_bVisible;}

        /*****************************************/
        /*              KEYBOARD/MOUSE           */
        /*****************************************/
        /// @brief Send keyboard event.
        /// 
        /// @param _KeyEvent Keyboard event.
        void SendKeyEvent(const sam::SFlashKeyEvent &_KeyEvent);

        /// @brief Send mouse event.
        /// 
        /// @param _MouseEvent Mouse event.
        void SendMouseEvent(const sam::SFlashMouseEvent &_MouseEvent);

        /// @brief Retrieves flash object.
        /// 
        /// @return Flash object.
        ShockwaveFlashObjects::IShockwaveFlash *GetFlashObject() const {return m_pFlashObject;}

        /// @brief Callback when fscommand is called in action script.
        /// 
        /// @param _sCommand Name of the command.
        /// @param _sArgs Arguments.
        void OnFSCommand(const UString &_sCommand, const UString &_sArgs);

        /// @brief Callback when ExternalInterface.call is called in action script.
        /// 
        /// @param _sFunction Name of the function.
        /// @param _pArgs List of arguments.
        /// @param _iNbArgs Number of arguments.
        void OnExternalInterface(const UString &_sFunction, sam::SFlashArgument *_pArgs, int _iNbArgs);

    private:        
        CFlashEvent *m_pFlashEvent;             ///< Flash event listener.
        CFlashControlSite *m_pFlashControlSite; ///< Flash control site.

        ShockwaveFlashObjects::IShockwaveFlash* m_pFlashObject; ///< COM-interface to the embedded flash object.        
        IOleInPlaceObjectWindowless* m_pWindowlessObj;          ///< To send keyboard/mouse to flash.
        IOleObject* m_pOleObject;                               ///< To accede to interface.

        bool m_bVisible; ///< True if it is visible.
        int m_iWidth;    ///< Window size.
        int m_iHeight;   ///< Window size.

        bool m_bDirty;   ///< True to redraw dirty rectangle.
        struct DirtyRect
        {
            int left;
            int top;
            int right;
            int bottom;
        }m_DirtyRect;        

        sam::IFSCommandListener *m_pFSCommandListener;                   ///< fscommand callback.
        sam::IExternalInterfaceListener *m_pExternalInterfaceListener;   ///< ExternalInterface.call callback.

        sf::Sprite m_Sprite;///< Image container to draw it.
        sf::Image m_Image;  ///< Buffer for rendering.
        uint8 *m_pBuffer;   ///< Sub buffer for rendering.
        sf::RenderTarget *m_pRenderTarget;

        /// @brief Default constructor.
        /// 
        /// @param _iWidth Width of the flash player.
        /// @param _iHeight Height of the flash player.        
        CFlashPlayer(int _iWidth, int _iHeight, sf::RenderTarget *_pRenderTarget);

        /// @brief Destructor.
        ~CFlashPlayer();

        /// @brief Create controller.
        /// 
        /// @param _FlashLib Flash library.
        void CreateController(HMODULE _FlashLib);
    };
}

#endif // __SR_CFLASH_PLAYER__
