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
#ifndef __SAMBOX_IRESOURCE__
#define __SAMBOX_IRESOURCE__

#include <QListWidgetItem>
#include <QPixmap>

#include "SamBox.h"

// used to define a resource class.
#define DEFINE_RESOURCE(class, name, type)					\
	static EResourceType GetType() {return type;}			\
	EResourceType GetResourceType() const {return type;}	\
	IMPLEMENT_SERIALIZABLE(class, name) 

/// @brief Interface for resource.
class IResource : public sam::ISerializable, public QListWidgetItem
{
public:
	/// @brief Constructor.
	/// 
	/// @param p_sName Resource name.
	/// @param p_sPath Absolute path.
    /// @param p_sPackage Name of the package.
    IResource(const sam::String &p_sName, const sam::String &p_sPath, const sam::String &p_sPackage);

	/// @brief Destructor.
	virtual ~IResource();

	/// @brief Retrieves resource name.
	/// 
	/// @return Resource name.
	const sam::String& GetName() const {return m_sName;}

    /// @brief Set resource name.
    ///
    /// @param p_sName New resource name.
    void SetName(const sam::String &p_sName) {m_sName = p_sName;}

	/// @brief Retrieves absolute path.
	/// 
	/// @return Absolute path.
	const sam::String& GetPath() const {return m_sPath;}

    /// @brief Set absolute path.
    ///
    /// @param p_sPath New path.
    void SetPath(const sam::String &p_sPath) {m_sPath = p_sPath;}

    /// @brief Retrieves the package name.
    ///
    /// @return Package name.
    const sam::String& GetPackage() const {return m_sPackage;}

    /// @brief Retrieves the

	/// @brief Retrieves the unique ID.
	/// 
	/// @return The unique ID of the resource.
	const sam::ID& GetID() const {return m_nID;}

	/// @brief Retrieves the thumbnail.
	/// 
	/// @return Pointer to the thumbnail.
    //QThumbnail *GetThumbnail() const {return m_pThumbnail;}

	/// @brief Retrieves the type of the resource.
	/// 
	/// @return The type of the resource.
	virtual EResourceType GetResourceType() const = 0;

	/// @brief Load resource.
	/// 
	/// @return True if there is no error.
	virtual bool Load() = 0;

	/// @brief Unload resource.
	/// 
	/// @return True if there is no error.
	virtual bool Unload() = 0;

	/// @brief Serialize the object
	/// 
	/// @param p_pContext Pointer to the context
	virtual void Read(sam::ISerializer *p_pContext);

	/// @brief Serialize the object
	/// 
	/// @param p_pContext Pointer to the context
	virtual void Write(sam::ISerializer *p_pContext);

protected:
	uint8 m_nVersion;	///< File format version. Used to detect if the version of the data is supported by the used editor.
	sam::ID m_nID;		///< Unique ID of the resource.
    uint32 m_nCount;    ///< Number of load request.

	sam::String m_sName;     ///< Resource name.
	sam::String m_sPath;     ///< Absolute path.
    sam::String m_sPackage;  ///< Package name.

    QPixmap m_oPixmap;       ///< Used by the view.
};

#endif // __SAMBOX_IRESOURCE_H__
