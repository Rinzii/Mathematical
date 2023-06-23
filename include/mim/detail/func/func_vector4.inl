// Copyright (c) 2023-Present Mim contributors (see LICENSE)

#include "mim/mimMath.hpp"
#include "mim/detail/compute/compute_vector.hpp"

namespace mim
{
	    
        template <typename T, qualifier Q>
	    constexpr bool VectorT<4, T, Q>::isfinite() const
        {
			using mim::math::isfinite;
            return isfinite(x);
        }

        template <typename T, qualifier Q>
		constexpr VectorT<4, T, Q> VectorT<4, T, Q>::sign() const
        {
            return VectorT<4, T, Q>(mim::math::sign(x));
        }

        template <typename T, qualifier Q>
		constexpr VectorT<4, T, Q> VectorT<4, T, Q>::floor() const
        {
            return VectorT<4, T, Q>(mim::math::floor(x));
        }

        template <typename T, qualifier Q>
		constexpr VectorT<4, T, Q> VectorT<4, T, Q>::ceil() const
        {
            return VectorT<4, T, Q>(mim::math::ceil(x));
        }

        template <typename T, qualifier Q>
		constexpr VectorT<4, T, Q> VectorT<4, T, Q>::round() const
        {
            return VectorT<4, T, Q>(mim::math::round(x));
        }


        template <typename T, qualifier Q>
		constexpr VectorT<4, T, Q> VectorT<4, T, Q>::min(const VectorT<4, T, Q>& v) const
        {
            return VectorT<4, T, Q>(mim::math::min(x, v.x));
        }

        template <typename T, qualifier Q>
		constexpr VectorT<4, T, Q> VectorT<4, T, Q>::max(const VectorT<4, T, Q>& v) const
        {

            return VectorT<4, T, Q>(mim::math::max(x, v.x));
        }

        template <typename T, qualifier Q>
		constexpr T VectorT<4, T, Q>::length() const
		{
            return mim::math::sqrt(x * x + y * y + z * z + w * w);
        }

		template <typename T, qualifier Q>
		constexpr T VectorT<4, T, Q>::length_squared() const
        {
            return x * x + y * y + z * z + w * w;
        }

		template <typename T, qualifier Q>
		constexpr void VectorT<4, T, Q>::normalize()
		{
			static_assert(std::is_floating_point<T>::value, "Cannot normalize a non-floating-point vector.");

			T len = length_squared();
			if (len != 0)
			{
				len = mim::math::sqrt(len);
				x /= len;
				y /= len;
				z /= len;
				w /= len;
			}
		}

		template <typename T, qualifier Q>
		constexpr VectorT<4, T, Q> VectorT<4, T, Q>::normalized() const
		{
			static_assert(std::is_floating_point<T>::value, "Cannot normalize a non-floating-point vector.");

			VectorT<4, T, Q> v = *this;
			v.normalize();
			return v;
		}

		template <typename T, qualifier Q>
		constexpr bool VectorT<4, T, Q>::is_normalized() const
		{
			static_assert(std::is_floating_point<T>::value, "Cannot normalize a non-floating-point vector.");

			// We want to use length_squared() over length() to avoid the use of sqrt.
			return nearlyEquals(length_squared(), T{ 1 }, MIM_UNIT_EPSILON<T>);
		}

		template <typename T, qualifier Q>
		constexpr T VectorT<4, T, Q>::distance(const VectorT<4, T, Q>& v) const
        {
            return mim::math::sqrt((x - v.x) * (x - v.x) + (y - v.y) * (y - v.y) + (z - v.z) * (z - v.z) + (w - v.w) * (w - v.w));
        }

		template <typename T, qualifier Q>
		constexpr T VectorT<4, T, Q>::distance_squared(const VectorT<4, T, Q>& v) const
        {
            return (x - v.x) * (x - v.x) + (y - v.y) * (y - v.y) + (z - v.z) * (z - v.z) + (w - v.w) * (w - v.w);
        }

}
