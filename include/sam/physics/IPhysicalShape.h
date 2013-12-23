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
#ifndef __IPHYSICAL_SHAPE__
#define __IPHYSICAL_SHAPE__

#include <render/Color.h>

namespace sam
{
    /// @enum Type of physical shape.
    enum EPhysicalShape
    {
        PS_Sphere,
        PS_Box,
        PS_TriMesh,
        PS_Heightfield,
    };

	/// @brief Abstract physical parameters.
	struct SPhysicalShapeParams : public IAllocated
	{	
	public:
		EPhysicalShape GetType(void) const {return m_eType;}

	protected:
		SPhysicalShapeParams(EPhysicalShape _eType) : m_eType(_eType) {}

		EPhysicalShape m_eType;
	};

	/// @brief Sphere.
	struct SSphereShape : public SPhysicalShapeParams
	{
		SSphereShape(void) : SPhysicalShapeParams(PS_Sphere) {}

		Vector3 m_vCenter;
		float m_fRadius;
	};

	/// @brief Box.
	struct SBoxShape : public SPhysicalShapeParams
	{
		SBoxShape(void) : SPhysicalShapeParams(PS_Box) {}

		float m_fWidth;
		float m_fHeight;
	};

	/// @brief 
	struct STriMeshShape : public SPhysicalShapeParams
	{
		STriMeshShape(void) : SPhysicalShapeParams(PS_TriMesh) {}

		std::vector<Vector3> m_avVertices;
	};

	/// @brief
	struct SHeightfieldShape : public SPhysicalShapeParams
	{
		SHeightfieldShape(void) : SPhysicalShapeParams(PS_Heightfield) {}
	};

    /// @brief Interface of physical shape.
    class IPhysicalShape : public IAllocated
    {
    public:
        /// @brief Retrieves the type of shape.
        /// 
        /// @return Type of shape.
        EPhysicalShape GetType(void) const {return m_eType;}

		/// @brief Initialize.
		/// 
		/// @param _pParams Parameters to initialize.
		virtual void Initialize(SPhysicalShapeParams *_pParams) = 0;

        /// @brief Draw the shape.
        virtual void DrawWireFrame(Color _Color) = 0;

    private:
        EPhysicalShape m_eType; ///< Type of physical shape.
    };
}

#endif // __IPHYSICAL_SHAPE__
