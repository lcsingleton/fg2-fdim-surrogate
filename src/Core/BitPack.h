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

// Helper function to create a packed CAN data payload
template<typename... Fields>
CanData<Fields...> UnpackCanData(const Fields&... fields) {
    return CanData<Fields...>(fields...);
}


#include <cstdint>
#include <array>
#include <type_traits>

// --- Field Types ---
template<
typename Struct, // The Struct representation of the CAN message
typename MemberType, // The datatype of the field from the struct representation
MemberType Struct::* Member, // The Memory address of the field - used to provide the byte offset into the Struct to storing the CAN data when unpacking and retrieving the value for packing
size_t Bits // The number of bits the field occupies when packed into the Can Data
>
struct MemberField {
    static constexpr size_t bits = Bits;
    static MemberType get(const Struct& obj) { return obj.*Member; }
    static void set(Struct& obj, uint64_t val) { obj.*Member = static_cast<MemberType>(val); }
};

template<uint64_t Value, size_t Bits>
struct FixedField {
    static constexpr size_t bits = Bits;
    static constexpr uint64_t value = Value;
};

// --- Schema Template ---
template<typename Struct, typename... Fields>
struct BitPackSchema {
    using StructType = Struct;
    static constexpr size_t num_fields = sizeof...(Fields);

    // --- Packing ---
    static uint64_t Pack(const Struct& obj) {
        return PackImpl<0, Fields...>(obj);
    }

    static std::array<uint8_t, 8> PackBytes(const Struct& obj) {
        uint64_t packed = Pack(obj);
        std::array<uint8_t, 8> bytes{};
        for (size_t i = 0; i < 8; ++i)
            bytes[i] = (packed >> ((7 - i) * 8)) & 0xFF;
        return bytes;
    }

    // --- Unpacking ---
    static Struct Unpack(uint64_t packed) {
        Struct obj{};
        UnpackImpl<0, Fields...>(obj, packed);
        return obj;
    }

    static Struct UnpackBytes(const std::array<uint8_t, 8>& bytes) {
        uint64_t packed = 0;
        for (size_t i = 0; i < 8; ++i)
            packed |= (static_cast<uint64_t>(bytes[i]) << ((7 - i) * 8));
        return Unpack(packed);
    }

private:
    // --- Bit offset calculation ---
    template<size_t Index>
    static constexpr size_t BitOffset() {
        size_t offsets[] = { Fields::bits... };
        size_t sum = 0;
        for (size_t i = 0; i < num_fields; ++i)
            sum += offsets[i];
        size_t offset = 0;
        for (size_t i = 0; i < Index; ++i)
            offset += offsets[i];
        return 64 - sum + offset;
    }

    // --- Packing Implementation ---
    template<size_t Index, typename First, typename... Rest>
    static uint64_t PackImpl(const Struct& obj) {
        uint64_t value;
        if constexpr (std::is_base_of_v<FixedField<First::value, First::bits>, First>) {
            value = First::value;
        } else {
            value = First::get(obj);
        }
        uint64_t field_bits = (value & ((1ULL << First::bits) - 1)) << BitOffset<Index>();
        if constexpr (sizeof...(Rest) > 0) {
            return field_bits | PackImpl<Index + 1, Rest...>(obj);
        } else {
            return field_bits;
        }
    }

    // --- Unpacking Implementation ---
    template<
    size_t Index, // Index in Fields of the field currently being unpacked
    typename First, // The current Field
    typename... Rest //
    >
    static void UnpackImpl(Struct& obj, uint64_t packed) {
        if constexpr (!std::is_base_of_v<FixedField<First::value, First::bits>, First>) {
            uint64_t val = (packed >> BitOffset<Index>()) & ((1ULL << First::bits) - 1);
            First::set(obj, val);
        }
        if constexpr (sizeof...(Rest) > 0) {
            UnpackImpl<Index + 1, Rest...>(obj, packed);
        }
    }
};


} // namespace BitPack
} // namespace Core


#endif // CORE_BITPACK_H
