// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Enum.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_Enum_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_Enum_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3020000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3020003 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_Enum_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_Enum_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_Enum_2eproto;
PROTOBUF_NAMESPACE_OPEN
PROTOBUF_NAMESPACE_CLOSE
namespace message {

enum ObjectType : int {
  OBJECT_TYPE_NONE = 0,
  OBJECT_TYPE_CREATURE = 1,
  ObjectType_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::min(),
  ObjectType_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::max()
};
bool ObjectType_IsValid(int value);
constexpr ObjectType ObjectType_MIN = OBJECT_TYPE_NONE;
constexpr ObjectType ObjectType_MAX = OBJECT_TYPE_CREATURE;
constexpr int ObjectType_ARRAYSIZE = ObjectType_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* ObjectType_descriptor();
template<typename T>
inline const std::string& ObjectType_Name(T enum_t_value) {
  static_assert(::std::is_same<T, ObjectType>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function ObjectType_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    ObjectType_descriptor(), enum_t_value);
}
inline bool ObjectType_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, ObjectType* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<ObjectType>(
    ObjectType_descriptor(), name, value);
}
enum CreatureType : int {
  CREATURE_TYPE_NONE = 0,
  CREATURE_TYPE_PLAYER = 1,
  CREATURE_TYPE_MONSTER = 2,
  CreatureType_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::min(),
  CreatureType_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::max()
};
bool CreatureType_IsValid(int value);
constexpr CreatureType CreatureType_MIN = CREATURE_TYPE_NONE;
constexpr CreatureType CreatureType_MAX = CREATURE_TYPE_MONSTER;
constexpr int CreatureType_ARRAYSIZE = CreatureType_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* CreatureType_descriptor();
template<typename T>
inline const std::string& CreatureType_Name(T enum_t_value) {
  static_assert(::std::is_same<T, CreatureType>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function CreatureType_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    CreatureType_descriptor(), enum_t_value);
}
inline bool CreatureType_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, CreatureType* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<CreatureType>(
    CreatureType_descriptor(), name, value);
}
enum PlayerType : int {
  PLAYER_TYPE_NONE = 0,
  PLAYER_TYPE_WARRIOR = 1,
  PLAYER_TYPE_ARCHER = 2,
  PlayerType_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::min(),
  PlayerType_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::max()
};
bool PlayerType_IsValid(int value);
constexpr PlayerType PlayerType_MIN = PLAYER_TYPE_NONE;
constexpr PlayerType PlayerType_MAX = PLAYER_TYPE_ARCHER;
constexpr int PlayerType_ARRAYSIZE = PlayerType_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* PlayerType_descriptor();
template<typename T>
inline const std::string& PlayerType_Name(T enum_t_value) {
  static_assert(::std::is_same<T, PlayerType>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function PlayerType_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    PlayerType_descriptor(), enum_t_value);
}
inline bool PlayerType_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, PlayerType* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<PlayerType>(
    PlayerType_descriptor(), name, value);
}
// ===================================================================


// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace message

PROTOBUF_NAMESPACE_OPEN

template <> struct is_proto_enum< ::message::ObjectType> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::message::ObjectType>() {
  return ::message::ObjectType_descriptor();
}
template <> struct is_proto_enum< ::message::CreatureType> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::message::CreatureType>() {
  return ::message::CreatureType_descriptor();
}
template <> struct is_proto_enum< ::message::PlayerType> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::message::PlayerType>() {
  return ::message::PlayerType_descriptor();
}

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_Enum_2eproto