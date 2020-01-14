#ifndef FIXED_H
#define FIXED_H

#include <gba_types.h>

/* Q8.8 Fixed-point */

struct Fixed
{
    public:
        Fixed() = default;
        Fixed(const Fixed &) = default;
        Fixed& operator=(const Fixed &) = default;

        constexpr Fixed(const int value) : raw((s16) (value * 256)) {}
        constexpr Fixed(const double value) : raw((s16) (value * 256)) {}

        constexpr static Fixed fromRaw(const s16 value)
        {
            Fixed i = Fixed();
            i.raw = value;
            return i;
        }

        constexpr operator int()
        {
            return raw >> 8;
        }

        friend constexpr int operator* (const int i, Fixed const& j)
        {
            int r = (i * j.raw) >> 8;
            return r;
        }

        friend constexpr Fixed operator* (Fixed const& i, Fixed const& j)
        {
            int r = i.raw * j.raw;
            return fromRaw(r >> 8);
        }

        friend constexpr Fixed operator+ (Fixed const& i, Fixed const& j)
        {
            int r = i.raw + j.raw;
            return fromRaw(r);
        }

        friend constexpr Fixed operator- (Fixed const& i, Fixed const& j)
        {
            int r = i.raw - j.raw;
            return fromRaw(r);
        }

        friend constexpr Fixed operator- (Fixed const& i)
        {
            int r = - i.raw;
            return fromRaw(r);
        }

        friend constexpr bool operator >= (Fixed const& i,Fixed const& j)
        {
            return i.raw >= j.raw;
        }

        friend constexpr bool operator < (Fixed const& i,Fixed const& j)
        {
            return i.raw < j.raw;
        }

        friend constexpr bool operator > (Fixed const& i,Fixed const& j)
        {
            return i.raw > j.raw;
        }

        constexpr Fixed& operator+= (Fixed const& i)
        {
            raw += i.raw;
            return *this;
        }

    public:
        s16 raw;
};

#endif