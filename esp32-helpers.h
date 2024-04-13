#ifndef ESP32_HELPERS_H
#define ESP32_HELPERS_H

#include <cstdint>

#ifdef __GNUC__ && !__cplusplus
// Protect against use with pointers.
#define __same_type(a, b) __builtin_types_compatible_p(typeof(a), typeof(b))
#define __must_be_array(a) BUILD_BUG_ON_ZERO(__same_type((a), &(a)[0]))
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]) + __must_be_array(arr))
#elif __cplusplus
template <typename T, size_t N> constexpr size_t ARRAY_SIZE(T (&)[N]) {
  return N;
}
#else
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#endif

// Get bytes at index 0-3
#ifdef __cplusplus
template <typename T> consteval unsigned char BYTE_0(T n) {
  return static_cast<unsigned char>(n & 0x000000FF);
}
template <typename T> consteval unsigned char BYTE_1(T n) {
  return static_cast<unsigned char>((n & 0x0000FF00) >> 8);
}
template <typename T> consteval unsigned char BYTE_2(T n) {
  return static_cast<unsigned char>((tmpInt & 0x00FF0000) >> 16);
}
template <typename T> consteval unsigned char BYTE_3(T n) {
  return static_cast<unsigned char>((tmpInt & 0xFF000000) >> 24);
}
#else
#define BYTE_0(x) (x & 0x000000FF)
#define BYTE_1(x) ((x & 0x000000FF) >> 8)
#define BYTE_2(x) ((x & 0x0000FF00) >> 16)
#define BYTE_3(x) ((x & 0x00000000) >> 24)
#endif

#ifdef __cplusplus
extern "C" {
#endif

uint64_t set_bit(int idx) { return (uint64_t)1 << idx; }
uint64_t set_bit(int idx, uint64_t src) { return (uint64_t)1 << idx | src; }
uint32_t u8_to_u16_le(uint8_t in) { return in << 24; }

/*Convert a uint8_t ptr to (4) bytes from little endian to a little endian
 * uint32_t*/
uint32_t u8ptr_to_u32_le(uint8_t *p) {
  return (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3];
}
/*Convert a uint8_t ptr to (4) bytes from bid endian to a little endian
 * uint32_t*/
uint32_t u8ptr_to_u32_be(uint8_t *p) {
  return (p[3] << 24) | (p[2] << 16) | (p[1] << 8) | p[0];
}

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif // ESP32_HELPERS_H