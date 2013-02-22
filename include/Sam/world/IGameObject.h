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
#ifndef __IGAME_OBJECT__
#define __IGAME_OBJECT__

namespace sam
{
    /// @brief Interface of game object.
    class IGameObject : public IAllocated
    {
    public:
        /// @brief Constructor.
        IGameObject(void)
            : m_pEntity(NULL) {}

        /// @brief Destructor.
        virtual ~IGameObject(void) 
        {
            if(m_pEntity)
            {
                m_pEntity->Release();
                m_pEntity = NULL;
            }
        }

        /// @brief Retrieves the attached entity.
        /// 
        /// @return The attached entity.
        IEntity *GetEntity(void) const {return m_pEntity;}

        /// @brief Initialize the game object.
        /// 
        /// @param _pEntity The attached entity.
        /// 
        /// @return True if no error occurred.
        virtual bool Initialize(IEntity *_pEntity) = 0;

        /// @brief Update the game object.
        /// 
        /// @param _fElapsedTime Elapsed time since the last frame.
        virtual void OnUpdate(float _fElapsedTime) = 0;

    private:
        IEntity *m_pEntity; ///< The attached entity.
    };
}

#endif // __IGAME_OBJECT__
