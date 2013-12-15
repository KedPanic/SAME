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
#ifndef __CJSON_SERIALIZER__
#define __CJSON_SERIALIZER__

struct cJSON;

#include <common/io/ISerializer.h>

namespace sam
{
    /// @brief JSON serializer
    class SAM_COMMON_API CJSONSerializer : public ISerializer
    {
    public:
        /// @brief Constructor
        /// 
        /// @param _sFilename Name of the file.
        CJSONSerializer(const char *_sFilename);

        /// @brief Called at starting (de)serialization
        /// 
        /// @param _bRead True to deserialize.
        /// @param _sName Name of the root element to serialize.
		/// 
		/// @return True if no error occurred.
        bool BeginSerialization(bool _bRead, const char *_sName);

		/// @brief Called at starting (de)serialization
		/// 
		/// @param p_pBuffer Memory buffer to read.
		/// @param p_nSize Buffer size.
		/// @param p_sName Name of the root element to serialize.
		/// 
		/// @return True if no error occurred.
		bool BeginSerialization(uint8 *p_pBuffer, uint32 p_nSize, const char *p_sName);

        /// @brief Called at ending serialization
        void EndSerialization();

        /// @brief Get true if its reading.
        bool IsReading() {return m_bRead;}

        /// @brief Start serializable
        /// 
        /// @param _pPtr Pointer to the serializable.
        void Begin(ISerializable *_pPtr);

        /// @brief End of serializable
        void End();

        /// @brief Start element
        /// 
        /// @param _sElement Name of the element.
        /// 
        /// @return false if the element doesn't exist.
        bool BeginElem(const char *_sElement);

        /// @brief Ending current element
        void EndElem();

		/// @brief Read value with specified name.
		/// 
		/// @param p_sName Name of the value
		///
		/// @return String value.
		/// 
		/// @remarks return value have to be deleted by the user.
		char *ReadValue(const char *p_sName);

		/// @brief Read integer value with specified name.
		/// 
		///  @param p_sName Name of the value.
		/// 
		///  @return Integer value.
		int ReadIntValue(const char *p_sName);

		/// @brief Read value with specified name.
		/// 
		/// @param p_sName Name of the value
		/// @param p_*Value Value.	
		void ReadValue(const char *p_sName, bool  &p_bValue);
		void ReadValue(const char *p_sName, int   &p_nValue);
		void ReadValue(const char *p_sName, uint32  &p_nValue);
		void ReadValue(const char *p_sName, Vector3 &p_vValue);
		void ReadValue(const char *p_sName, float &p_fValue);
		void ReadValue(const char *p_sName, float p_afValue[4]);

		/// @brief Write value with specified name.
		/// 
		/// @param p_sName Name of the value
		/// @param p_*Value Value.
		void WriteValue(const char *p_sName, const bool  &p_bValue);
		void WriteValue(const char *p_sName, const int   &p_nValue);
		void WriteValue(const char *p_sName, const uint32  &p_nValue);
		void WriteValue(const char *p_sName, const char *p_sValue);
		void WriteValue(const char *p_sName, const Vector3 &p_vValue);
		void WriteValue(const char *p_sName, const float &p_fValue);
		void WriteValue(const char *p_sName, const float p_afValue[4]);

    private:
        const char* m_sFilename;			///< Name of the file.
        bool m_bRead;						///< True if its reading
        cJSON *m_pRoot;		                ///< JSON root document.
        cJSON *m_pCurrentElement;	        ///< JSON current element.

        /// @brief Goto the next node.
		/// 
		/// @param p_sName Name of the next node (for debug)
        void NextNode(const char *p_sName);
    };
}

#endif // __CJSON_SERIALIZER__
