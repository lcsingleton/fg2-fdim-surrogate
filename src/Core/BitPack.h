#ifndef CORE_BITPACK_H
#define CORE_BITPACK_H
#include <cstdint>
#include <type_traits>
#include <array>

namespace Core {
namespace BitPack {


template<typename T, size_t Bits>
struct Field {
    // The inner value being packed
    const T& value;

    // Constructor
    Field(const T& v) : value(v) {}

    // The number of bits this field occupies when packed
    static constexpr size_t bits = Bits;
};

struct BoolField : Field<bool, 1> {
    BoolField(const bool& v) : Field<bool, 1>(v) {}
};

// Padding
template<uint64_t Constant, size_t Bits>
struct FixedField {
    static constexpr uint64_t value = Constant;
    static constexpr size_t bits = Bits;
};

template<typename... Fields>
class CanData {
public:
    static constexpr size_t total_bits = (Fields::bits + ...);
    static_assert(total_bits <= 64, "Packet too large for 8 bytes");

    std::array<uint8_t, 8> bytes{};

    CanData(const Fields&... fields) {
        uint64_t packed = Pack(fields...);
        for (size_t i = 0; i < 8; ++i) {
            bytes[i] = (packed >> ((7 - i) * 8)) & 0xFF;
        }
    }

private:
    template<typename... Ts>
    static uint64_t Pack(const Ts&... fields) {

        // Store the bit widths for each of the fields
        constexpr size_t widths[] = { Ts::bits... };

        // Storage for the bit offsets for each of the fields
        size_t offsets[sizeof...(Ts)]{};

        // Calculate the bit offsets for each field
        size_t sum = 0;
        for (size_t i = 0; i < sizeof...(Ts); ++i) {
            offsets[i] = sum;
            sum += widths[i];
        }

        // Pack the fields into a single 64-bit integer
        uint64_t result = 0;
        size_t i = 0;

        ((result |= (GetBits(fields) << (64 - sum + offsets[i++] - widths[i - 1]))), ...);
        return result;
    }

    template<typename T, size_t Bits>
    static uint64_t GetBits(const Field<T, Bits>& f) {
        // Get the bits from the field value, bitshifted into place
        return (static_cast<uint64_t>(f.value) & ((1ULL << Bits) - 1));
    }

    template<uint64_t Val, size_t Bits>
    static uint64_t GetBits(const FixedField<Val, Bits>&) {
        // Template specialization for FixedField
        return (Val & ((1ULL << Bits) - 1));
    }
};

// Helper function to create a packed CAN data payload
template<typename... Fields>
CanData<Fields...> PackCanData(const Fields&... fields) {
    return CanData<Fields...>(fields...);
}

} // namespace BitPack
} // namespace Core


#endif // CORE_BITPACK_H
