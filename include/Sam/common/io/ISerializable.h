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
#ifndef __ISERIALIZABLE__
#define __ISERIALIZABLE__

#include <common/base/GUIDUtil.h>
#include <common/SamConfig.h>

namespace sam
{
	/// @brief Interface for serializable object
	class ISerializable : public IAllocated
	{
	public:
		/// @brief Get the unique Id.
		/// 
		/// @return the unique id.
		guid::GUID GetGUID() {return m_GUID;}

        /// @brief Retrieves serialize name.
        /// 
        /// @return Name of the serializable class.
        virtual const char *GetSerializeName() const = 0;

		/// @brief Serialize the object
		/// 
		/// @param p_pContext Pointer to the context
		virtual void Read(ISerializer *p_pContext) = 0;

		/// @brief Serialize the object
		/// 
		/// @param p_pContext Pointer to the context
		virtual void Write(ISerializer *p_pContext) = 0;

    private:
		guid::GUID m_GUID;                  ///< Unique Id of the object.
	};
}

// Declare a serializable class.
#define IMPLEMENT_SERIALIZABLE(class, name)                         \
public:                                                             \
    const char *GetSerializeName() const {return name;}
    //static class *CreateInstance() {return SAM_NEW class;}

// Declare a singleton serializable class.
#define IMPLEMENT_SINGLETON_SERIALIZABLE(class, name, instance)  \
public:                                                          \
    const char *GetSerializeName() const {return name;}               \
    static class *CreateInstance() {return instance;}

// Declare a reference serializable class.
#define IMPLEMENT_REFERENCE_SERIALIZABLE(class, name, instance)  \
public:                                                          \
    const char *GetSerializeName() const {return name;}               \
    static class &CreateInstance() {return instance;}

#endif // __ISERIALIZABLE__
