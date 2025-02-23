// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Enum.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_Enum_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_Enum_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3017000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3017001 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
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
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_Enum_2eproto;
PROTOBUF_NAMESPACE_OPEN
PROTOBUF_NAMESPACE_CLOSE
namespace message {

enum ObjectType : int {
  OBJECT_TYPE_NONE = 0,
  OBJECT_TYPE_CREATURE = 1,
  OBJECT_TYPE_ITEM = 2,
  ObjectType_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  ObjectType_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool ObjectType_IsValid(int value);
constexpr ObjectType ObjectType_MIN = OBJECT_TYPE_NONE;
constexpr ObjectType ObjectType_MAX = OBJECT_TYPE_ITEM;
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
  CreatureType_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  CreatureType_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
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
enum MonsterType : int {
  MONSTER_TYPE_NONE = 0,
  MONSTER_TYPE_RAMPAGE = 1,
  MonsterType_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  MonsterType_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool MonsterType_IsValid(int value);
constexpr MonsterType MonsterType_MIN = MONSTER_TYPE_NONE;
constexpr MonsterType MonsterType_MAX = MONSTER_TYPE_RAMPAGE;
constexpr int MonsterType_ARRAYSIZE = MonsterType_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* MonsterType_descriptor();
template<typename T>
inline const std::string& MonsterType_Name(T enum_t_value) {
  static_assert(::std::is_same<T, MonsterType>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function MonsterType_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    MonsterType_descriptor(), enum_t_value);
}
inline bool MonsterType_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, MonsterType* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<MonsterType>(
    MonsterType_descriptor(), name, value);
}
enum PlayerType : int {
  PLAYER_TYPE_NONE = 0,
  PLAYER_TYPE_WARRIOR = 1,
  PLAYER_TYPE_ARCHER = 2,
  PLAYER_TYPE_ASSASSIN = 3,
  PlayerType_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  PlayerType_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool PlayerType_IsValid(int value);
constexpr PlayerType PlayerType_MIN = PLAYER_TYPE_NONE;
constexpr PlayerType PlayerType_MAX = PLAYER_TYPE_ASSASSIN;
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
enum MoveState : int {
  MOVE_STATE_NONE = 0,
  MOVE_STATE_IDLE = 1,
  MOVE_STATE_RUN = 2,
  MOVE_STATE_JUMP = 3,
  MOVE_STATE_DASH = 4,
  MoveState_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  MoveState_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool MoveState_IsValid(int value);
constexpr MoveState MoveState_MIN = MOVE_STATE_NONE;
constexpr MoveState MoveState_MAX = MOVE_STATE_DASH;
constexpr int MoveState_ARRAYSIZE = MoveState_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* MoveState_descriptor();
template<typename T>
inline const std::string& MoveState_Name(T enum_t_value) {
  static_assert(::std::is_same<T, MoveState>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function MoveState_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    MoveState_descriptor(), enum_t_value);
}
inline bool MoveState_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, MoveState* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<MoveState>(
    MoveState_descriptor(), name, value);
}
enum ItemType : int {
  NONE_Item = 0,
  WEAPON = 1,
  Consumable = 2,
  Etc = 3,
  ItemType_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  ItemType_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool ItemType_IsValid(int value);
constexpr ItemType ItemType_MIN = NONE_Item;
constexpr ItemType ItemType_MAX = Etc;
constexpr int ItemType_ARRAYSIZE = ItemType_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* ItemType_descriptor();
template<typename T>
inline const std::string& ItemType_Name(T enum_t_value) {
  static_assert(::std::is_same<T, ItemType>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function ItemType_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    ItemType_descriptor(), enum_t_value);
}
inline bool ItemType_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, ItemType* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<ItemType>(
    ItemType_descriptor(), name, value);
}
enum ItemTable : int {
  NONE_ITEM = 0,
  GENERAL_HEALTH_POSION = 1,
  ItemTable_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  ItemTable_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool ItemTable_IsValid(int value);
constexpr ItemTable ItemTable_MIN = NONE_ITEM;
constexpr ItemTable ItemTable_MAX = GENERAL_HEALTH_POSION;
constexpr int ItemTable_ARRAYSIZE = ItemTable_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* ItemTable_descriptor();
template<typename T>
inline const std::string& ItemTable_Name(T enum_t_value) {
  static_assert(::std::is_same<T, ItemTable>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function ItemTable_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    ItemTable_descriptor(), enum_t_value);
}
inline bool ItemTable_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, ItemTable* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<ItemTable>(
    ItemTable_descriptor(), name, value);
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
template <> struct is_proto_enum< ::message::MonsterType> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::message::MonsterType>() {
  return ::message::MonsterType_descriptor();
}
template <> struct is_proto_enum< ::message::PlayerType> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::message::PlayerType>() {
  return ::message::PlayerType_descriptor();
}
template <> struct is_proto_enum< ::message::MoveState> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::message::MoveState>() {
  return ::message::MoveState_descriptor();
}
template <> struct is_proto_enum< ::message::ItemType> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::message::ItemType>() {
  return ::message::ItemType_descriptor();
}
template <> struct is_proto_enum< ::message::ItemTable> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::message::ItemTable>() {
  return ::message::ItemTable_descriptor();
}

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_Enum_2eproto
