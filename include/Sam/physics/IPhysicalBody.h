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
#ifndef __IPHYSICAL_BODY__
#define __IPHYSICAL_BODY__

namespace sam
{
	struct SPhysicalShapeParams;

    /// @enum Type of physical body.
    enum EPhysicalBodyType
    {
        PBT_Static,
        PBT_Kinematic,
        PBT_Dynamic,        
    };

	/// @brief Parameter to initialize a body.
	struct SPhysicalBodyParams
	{
		EPhysicalBodyType m_eType;
		float m_fMass;
		Vector3 m_vPos;
		float m_fAngle;
        float m_fAngularVelocity;
        float m_fFriction;
        bool m_bFixedRotation;

		std::vector<SPhysicalShapeParams*> m_aShapes;

		SPhysicalBodyParams()
			: m_eType(PBT_Dynamic), m_fMass(1.0f), m_vPos(0.0f, 0.0f, 0.0f), m_fAngle(0.0f), m_fAngularVelocity(1.0f), m_fFriction(0.2f), m_bFixedRotation(false) {}
	};

    /// @brief Interface of physical body.
    class IPhysicalBody : public IAllocated
    {
	public:
		/// @brief Retrieves the type of body.
		/// 
		/// @return Type of body.
		EPhysicalBodyType GetType(void) const {return m_eType;}

        /// @brief Retrieves the attached shapes.
        /// 
        /// @return First shape.
        virtual IPhysicalShape *GetShapes(void) = 0;

		/// @brief Initialize the body.
		/// 
		/// @param _Params Parameter to initialize it.
		virtual void Initialize(const SPhysicalBodyParams &_Params) = 0;

        /// @brief Apply force.
        /// 
        /// @param _vForce Force vector.
        virtual void ApplyForce(const Vector3 &_vForce) = 0;

        /// @brief Apply force.
        /// 
        /// @param _vForce Force vector.
        /// @param _vPos   Position where we apply the force.
        virtual void ApplyForce(const Vector3 &_vForce, const Vector3 &_vPos) = 0;

        /// @brief Apply angular impulse.
        /// 
        /// @param _fImpulse Impulsion.
        /// 
        /// @see SPhysicalBodyParams::m_fAngularVelocity
        virtual void ApplyAngularImpulse(float _fImpulse) = 0;

        /// @brief Apply impulse.
        /// 
        /// @param _vImpulse  Impulse vector.
        virtual void ApplyImpulse(const Vector3 &_vImpulse) = 0;

        /// @brief Apply impulse.
        /// 
        /// @param _vImpulse  Impulse vector.
        /// @param _vPos      Position where we apply the impulse.
        virtual void ApplyImpulse(const Vector3 &_vImpulse, const Vector3 &_vPos) = 0;

        /// @brief Set position.
        /// 
        /// @param _vPos New position.
        virtual void SetPosition(const Vector3 &_vPos) = 0;

        /// @brief Translate.
        /// 
        /// @param _vMove Translation to apply.
        virtual void Translate(const Vector3 &_vMove) = 0;

        /// @brief Sets linear velocity.
        /// 
        /// @param _vVelocity Velocity vector.
        virtual void SetLinearVelocity(const Vector3 &_vVelocity) = 0;

        /// @brief Gets linear velocity.
        /// 
        /// @param _vVelocity Velocity vector.
        virtual void GetLinearVelocity(Vector3 &_vVelocity) = 0;

        /// @brief Get current position.
        virtual Vector3 GetPosition(void) const = 0;

	private:
		EPhysicalBodyType m_eType; ///< Type of body.
    };
}

#endif // __IPHYSICAL_BODY__
