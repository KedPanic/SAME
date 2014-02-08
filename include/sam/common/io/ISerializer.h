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
#ifndef __ISERIALIZER__
#define __ISERIALIZER__

#include "common/base/GUIDUtil.h"
#include "common/math/Vector.h"

namespace sam
{
    /// @enum Type of serializer.
    enum ESerializerType
    {
        e_Serializer_Binary,
        e_Serializer_XML,
		e_Serializer_JSon,
        e_Serializer_Custom,
    };

	/// @brief Interface for (de)serialize implementation
	class ISerializer
	{
	public:
		/// @brief Called at starting (de)serialization
		/// 
		/// @param _bRead True to deserialize.
        /// @param _sName Name of the root element to serialize.
		/// 
		/// @return True if no error occurred.
		virtual bool BeginSerialization(bool _bRead, const char *_sName) = 0;

		/// @brief Called at ending serialization
		virtual void EndSerialization(void) = 0;

		/// @brief Get true if its reading.
		virtual bool IsReading(void) = 0;

		/// @brief Start serializable
		/// 
		/// @param _pPtr Pointer to the serializable.
		virtual void Begin(ISerializable *_pPtr) = 0;

		/// @brief End of serializable
		virtual void End(void) = 0;

		/// @brief Start element
		/// 
		/// @param _sElement Name of the element.
		/// 
		/// @return false if the element doesn't'nt exist.
		virtual bool BeginElem(const char *_sElement) = 0;

		/// @brief Ending current element
		virtual void EndElem(void) = 0;

		/// @brief Read value with specified name.
		/// 
		/// @param p_sName Name of the value
		///
		/// @return String value.
		/// 
		/// @remarks return value have to be deleted by the user.
		virtual char *ReadValue(const char *p_sName) = 0;

		/// @brief Read integer value with specified name.
		/// 
		///  @param p_sName Name of the value.
		/// 
		///  @return Integer value.
		virtual int ReadIntValue(const char *p_sName) = 0;

		/// @brief Read value with specified name.
		/// 
		/// @param p_sName Name of the value
		/// @param p_*Value Value.	
		virtual void ReadValue(const char *p_sName, bool  &p_bValue) = 0;
		virtual void ReadValue(const char *p_sName, int   &p_nValue) = 0;
		virtual void ReadValue(const char *p_sName, uint32   &p_nValue) = 0;
		virtual void ReadValue(const char *p_sName, Vector3 &p_vValue) = 0;
		virtual void ReadValue(const char *p_sName, float &p_fValue) = 0;
        virtual void ReadValue(const char *p_sName, float p_afValue[4]) = 0;

		/// @brief Write value with specified name.
		/// 
		/// @param p_sName Name of the value
		/// @param p_*Value Value.
		virtual void WriteValue(const char *p_sName, const bool  &p_bValue) = 0;
		virtual void WriteValue(const char *p_sName, const int   &p_nValue) = 0;
		virtual void WriteValue(const char *p_sName, const uint32  &p_nValue) = 0;
		virtual void WriteValue(const char *p_sName, const char *p_sValue) = 0;
		virtual void WriteValue(const char *p_sName, const Vector3 &p_vValue) = 0;
		virtual void WriteValue(const char *p_sName, const float &p_fValue) = 0;
		virtual void WriteValue(const char *p_sName, const float p_afValue[4]) = 0;
	};

	/// @brief Helper class to deserialize
	class SAM_COMMON_API SerializableRegistry
	{
        typedef ISerializable *(*CreateInstance)();

	public:
        /// @brief Remove all serializable.
        static void RemoveAllSerializables();

		/// @brief Register serializable pointer function
		/// 
        /// @param p_sName Name of the instance.
		/// @param p_pfCreateInstanceFunc Pointer to the pointer function to create instance.
		static void RegisterSerializable(const char *p_sName, CreateInstance p_pfCreateInstanceFunc);

        /// @brief Called by the serializer to (de)serialize.
		/// 
        /// @param _sName Name of the element to (de)serialize.
		/// @param _pContext The serializer.
		static void Serialize(const char *_sName, ISerializer *_pContext);

	private:
        /// @brief Node of serializable linked list.
        struct SSerializables : public IAllocated
        {
            const char *m_sName;
            CreateInstance m_pfCreateInstance;
            SSerializables *m_pNext;

            /// @brief Default constructor.
            SSerializables(void)
                : m_sName(NULL), m_pfCreateInstance(NULL), m_pNext(NULL)
            {

            }
        };

		static SSerializables *m_pSerializables; ///< Linked list of serializables pointer functions.
	};

    namespace helper
    {
        /// @brief Helper method to serialize/deserialize.
        /// 
        /// @param p_eSerialiazerType Type of serializer (custom is not supported).
        /// @param p_pSerializable Pointer to the instance to (de)serialize.
        /// @param p_sFilename Name of file to (de)serialize.
        /// @param p_bReading True to read, false to write.
        ///
        /// @return True if no error occurred.
        SAM_COMMON_API bool Serialize(ESerializerType p_eSerialiazerType, ISerializable *p_pSerializable, const char *p_sFilename, bool p_bReading = false);
    }
}

#define REGISTER_SERIALIZABLE(class)    \
    sam::SerializableRegistry::RegisterSerializable(class::GetSerializeName(), &class::CreateInstance);
#endif // __ISERIALIZE__
