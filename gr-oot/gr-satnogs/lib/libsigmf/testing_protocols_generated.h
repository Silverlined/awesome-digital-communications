// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_TESTINGPROTOCOLS_H_
#define FLATBUFFERS_GENERATED_TESTINGPROTOCOLS_H_

#include "flatbuffers/flatbuffers.h"

struct one;
struct oneT;

struct two;
struct twoT;

struct three;
struct threeT;

struct testingunions;
struct testingunionsT;

inline const flatbuffers::TypeTable *oneTypeTable();

inline const flatbuffers::TypeTable *twoTypeTable();

inline const flatbuffers::TypeTable *threeTypeTable();

inline const flatbuffers::TypeTable *testingunionsTypeTable();

enum myunion {
  myunion_NONE = 0,
  myunion_one = 1,
  myunion_two = 2,
  myunion_three = 3,
  myunion_MIN = myunion_NONE,
  myunion_MAX = myunion_three
};

inline const myunion(&EnumValuesmyunion())[4] {
  static const myunion values[] = {
    myunion_NONE,
    myunion_one,
    myunion_two,
    myunion_three
  };
  return values;
}

inline const char *const *EnumNamesmyunion()
{
  static const char *const names[] = {
    "NONE",
    "one",
    "two",
    "three",
    nullptr
  };
  return names;
}

inline const char *EnumNamemyunion(myunion e)
{
  if (e < myunion_NONE || e > myunion_three) {
    return "";
  }
  const size_t index = static_cast<int>(e);
  return EnumNamesmyunion()[index];
}

template<typename T> struct myunionTraits {
  static const myunion enum_value = myunion_NONE;
};

template<> struct myunionTraits<one> {
  static const myunion enum_value = myunion_one;
};

template<> struct myunionTraits<two> {
  static const myunion enum_value = myunion_two;
};

template<> struct myunionTraits<three> {
  static const myunion enum_value = myunion_three;
};

struct myunionUnion {
  myunion type;
  void *value;

  myunionUnion() : type(myunion_NONE), value(nullptr) {}
myunionUnion(myunionUnion &&u) FLATBUFFERS_NOEXCEPT :
  type(myunion_NONE), value(nullptr)
  {
    std::swap(type, u.type);
    std::swap(value, u.value);
  }
  myunionUnion(const myunionUnion &) FLATBUFFERS_NOEXCEPT;
  myunionUnion &operator=(const myunionUnion &u) FLATBUFFERS_NOEXCEPT
  { myunionUnion t(u); std::swap(type, t.type); std::swap(value, t.value); return *this; }
  myunionUnion &operator=(myunionUnion &&u) FLATBUFFERS_NOEXCEPT
  { std::swap(type, u.type); std::swap(value, u.value); return *this; }
  ~myunionUnion()
  {
    Reset();
  }

  void Reset();

#ifndef FLATBUFFERS_CPP98_STL
  template <typename T>
  void Set(T &&val)
  {
    Reset();
    type = myunionTraits<typename T::TableType>::enum_value;
    if (type != myunion_NONE) {
      value = new T(std::forward<T>(val));
    }
  }
#endif  // FLATBUFFERS_CPP98_STL

  static void *UnPack(const void *obj, myunion type,
                      const flatbuffers::resolver_function_t *resolver);
  flatbuffers::Offset<void> Pack(flatbuffers::FlatBufferBuilder &_fbb,
                                 const flatbuffers::rehasher_function_t *_rehasher = nullptr) const;

  oneT *Asone()
  {
    return type == myunion_one ?
           reinterpret_cast<oneT *>(value) : nullptr;
  }
  const oneT *Asone() const
  {
    return type == myunion_one ?
           reinterpret_cast<const oneT *>(value) : nullptr;
  }
  twoT *Astwo()
  {
    return type == myunion_two ?
           reinterpret_cast<twoT *>(value) : nullptr;
  }
  const twoT *Astwo() const
  {
    return type == myunion_two ?
           reinterpret_cast<const twoT *>(value) : nullptr;
  }
  threeT *Asthree()
  {
    return type == myunion_three ?
           reinterpret_cast<threeT *>(value) : nullptr;
  }
  const threeT *Asthree() const
  {
    return type == myunion_three ?
           reinterpret_cast<const threeT *>(value) : nullptr;
  }
};

bool Verifymyunion(flatbuffers::Verifier &verifier, const void *obj,
                   myunion type);
bool VerifymyunionVector(flatbuffers::Verifier &verifier,
                         const flatbuffers::Vector<flatbuffers::Offset<void>> *values,
                         const flatbuffers::Vector<uint8_t> *types);

struct oneT : public flatbuffers::NativeTable {
  typedef one TableType;
  float fieldone;
  oneT()
    : fieldone(0.0f)
  {
  }
};

struct one FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef oneT NativeTableType;
  static const flatbuffers::TypeTable *MiniReflectTypeTable()
  {
    return oneTypeTable();
  }
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_FIELDONE = 4
  };
  float fieldone() const
  {
    return GetField<float>(VT_FIELDONE, 0.0f);
  }
  bool Verify(flatbuffers::Verifier &verifier) const
  {
    return VerifyTableStart(verifier) &&
           VerifyField<float>(verifier, VT_FIELDONE) &&
           verifier.EndTable();
  }
  oneT *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(oneT *_o, const flatbuffers::resolver_function_t *_resolver =
                  nullptr) const;
  static flatbuffers::Offset<one> Pack(flatbuffers::FlatBufferBuilder &_fbb,
                                       const oneT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct oneBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_fieldone(float fieldone)
  {
    fbb_.AddElement<float>(one::VT_FIELDONE, fieldone, 0.0f);
  }
  explicit oneBuilder(flatbuffers::FlatBufferBuilder &_fbb)
    : fbb_(_fbb)
  {
    start_ = fbb_.StartTable();
  }
  oneBuilder &operator=(const oneBuilder &);
  flatbuffers::Offset<one> Finish()
  {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<one>(end);
    return o;
  }
};

inline flatbuffers::Offset<one> Createone(
  flatbuffers::FlatBufferBuilder &_fbb,
  float fieldone = 0.0f)
{
  oneBuilder builder_(_fbb);
  builder_.add_fieldone(fieldone);
  return builder_.Finish();
}

flatbuffers::Offset<one> Createone(flatbuffers::FlatBufferBuilder &_fbb,
                                   const oneT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

struct twoT : public flatbuffers::NativeTable {
  typedef two TableType;
  float fieldtwo;
  twoT()
    : fieldtwo(0.0f)
  {
  }
};

struct two FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef twoT NativeTableType;
  static const flatbuffers::TypeTable *MiniReflectTypeTable()
  {
    return twoTypeTable();
  }
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_FIELDTWO = 4
  };
  float fieldtwo() const
  {
    return GetField<float>(VT_FIELDTWO, 0.0f);
  }
  bool Verify(flatbuffers::Verifier &verifier) const
  {
    return VerifyTableStart(verifier) &&
           VerifyField<float>(verifier, VT_FIELDTWO) &&
           verifier.EndTable();
  }
  twoT *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(twoT *_o, const flatbuffers::resolver_function_t *_resolver =
                  nullptr) const;
  static flatbuffers::Offset<two> Pack(flatbuffers::FlatBufferBuilder &_fbb,
                                       const twoT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct twoBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_fieldtwo(float fieldtwo)
  {
    fbb_.AddElement<float>(two::VT_FIELDTWO, fieldtwo, 0.0f);
  }
  explicit twoBuilder(flatbuffers::FlatBufferBuilder &_fbb)
    : fbb_(_fbb)
  {
    start_ = fbb_.StartTable();
  }
  twoBuilder &operator=(const twoBuilder &);
  flatbuffers::Offset<two> Finish()
  {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<two>(end);
    return o;
  }
};

inline flatbuffers::Offset<two> Createtwo(
  flatbuffers::FlatBufferBuilder &_fbb,
  float fieldtwo = 0.0f)
{
  twoBuilder builder_(_fbb);
  builder_.add_fieldtwo(fieldtwo);
  return builder_.Finish();
}

flatbuffers::Offset<two> Createtwo(flatbuffers::FlatBufferBuilder &_fbb,
                                   const twoT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

struct threeT : public flatbuffers::NativeTable {
  typedef three TableType;
  float fieldthree;
  threeT()
    : fieldthree(0.0f)
  {
  }
};

struct three FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef threeT NativeTableType;
  static const flatbuffers::TypeTable *MiniReflectTypeTable()
  {
    return threeTypeTable();
  }
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_FIELDTHREE = 4
  };
  float fieldthree() const
  {
    return GetField<float>(VT_FIELDTHREE, 0.0f);
  }
  bool Verify(flatbuffers::Verifier &verifier) const
  {
    return VerifyTableStart(verifier) &&
           VerifyField<float>(verifier, VT_FIELDTHREE) &&
           verifier.EndTable();
  }
  threeT *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr)
  const;
  void UnPackTo(threeT *_o,
                const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<three> Pack(flatbuffers::FlatBufferBuilder &_fbb,
                                         const threeT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct threeBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_fieldthree(float fieldthree)
  {
    fbb_.AddElement<float>(three::VT_FIELDTHREE, fieldthree, 0.0f);
  }
  explicit threeBuilder(flatbuffers::FlatBufferBuilder &_fbb)
    : fbb_(_fbb)
  {
    start_ = fbb_.StartTable();
  }
  threeBuilder &operator=(const threeBuilder &);
  flatbuffers::Offset<three> Finish()
  {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<three>(end);
    return o;
  }
};

inline flatbuffers::Offset<three> Createthree(
  flatbuffers::FlatBufferBuilder &_fbb,
  float fieldthree = 0.0f)
{
  threeBuilder builder_(_fbb);
  builder_.add_fieldthree(fieldthree);
  return builder_.Finish();
}

flatbuffers::Offset<three> Createthree(flatbuffers::FlatBufferBuilder &_fbb,
                                       const threeT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

struct testingunionsT : public flatbuffers::NativeTable {
  typedef testingunions TableType;
  myunionUnion myfield;
  int32_t dumbfield;
  testingunionsT()
    : dumbfield(0)
  {
  }
};

struct testingunions FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef testingunionsT NativeTableType;
  static const flatbuffers::TypeTable *MiniReflectTypeTable()
  {
    return testingunionsTypeTable();
  }
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_MYFIELD_TYPE = 4,
    VT_MYFIELD = 6,
    VT_DUMBFIELD = 8
  };
  myunion myfield_type() const
  {
    return static_cast<myunion>(GetField<uint8_t>(VT_MYFIELD_TYPE, 0));
  }
  const void *myfield() const
  {
    return GetPointer<const void *>(VT_MYFIELD);
  }
  template<typename T> const T *myfield_as() const;
  const one *myfield_as_one() const
  {
    return myfield_type() == myunion_one ? static_cast<const one *>
           (myfield()) : nullptr;
  }
  const two *myfield_as_two() const
  {
    return myfield_type() == myunion_two ? static_cast<const two *>
           (myfield()) : nullptr;
  }
  const three *myfield_as_three() const
  {
    return myfield_type() == myunion_three ? static_cast<const three *>
           (myfield()) : nullptr;
  }
  int32_t dumbfield() const
  {
    return GetField<int32_t>(VT_DUMBFIELD, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const
  {
    return VerifyTableStart(verifier) &&
           VerifyField<uint8_t>(verifier, VT_MYFIELD_TYPE) &&
           VerifyOffset(verifier, VT_MYFIELD) &&
           Verifymyunion(verifier, myfield(), myfield_type()) &&
           VerifyField<int32_t>(verifier, VT_DUMBFIELD) &&
           verifier.EndTable();
  }
  testingunionsT *UnPack(const flatbuffers::resolver_function_t *_resolver =
                           nullptr) const;
  void UnPackTo(testingunionsT *_o,
                const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<testingunions> Pack(flatbuffers::FlatBufferBuilder
      &_fbb, const testingunionsT *_o,
      const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

template<> inline const one *testingunions::myfield_as<one>() const
{
  return myfield_as_one();
}

template<> inline const two *testingunions::myfield_as<two>() const
{
  return myfield_as_two();
}

template<> inline const three *testingunions::myfield_as<three>() const
{
  return myfield_as_three();
}

struct testingunionsBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_myfield_type(myunion myfield_type)
  {
    fbb_.AddElement<uint8_t>(testingunions::VT_MYFIELD_TYPE,
                             static_cast<uint8_t>(myfield_type), 0);
  }
  void add_myfield(flatbuffers::Offset<void> myfield)
  {
    fbb_.AddOffset(testingunions::VT_MYFIELD, myfield);
  }
  void add_dumbfield(int32_t dumbfield)
  {
    fbb_.AddElement<int32_t>(testingunions::VT_DUMBFIELD, dumbfield, 0);
  }
  explicit testingunionsBuilder(flatbuffers::FlatBufferBuilder &_fbb)
    : fbb_(_fbb)
  {
    start_ = fbb_.StartTable();
  }
  testingunionsBuilder &operator=(const testingunionsBuilder &);
  flatbuffers::Offset<testingunions> Finish()
  {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<testingunions>(end);
    return o;
  }
};

inline flatbuffers::Offset<testingunions> Createtestingunions(
  flatbuffers::FlatBufferBuilder &_fbb,
  myunion myfield_type = myunion_NONE,
  flatbuffers::Offset<void> myfield = 0,
  int32_t dumbfield = 0)
{
  testingunionsBuilder builder_(_fbb);
  builder_.add_dumbfield(dumbfield);
  builder_.add_myfield(myfield);
  builder_.add_myfield_type(myfield_type);
  return builder_.Finish();
}

flatbuffers::Offset<testingunions> Createtestingunions(
  flatbuffers::FlatBufferBuilder &_fbb, const testingunionsT *_o,
  const flatbuffers::rehasher_function_t *_rehasher = nullptr);

inline oneT *one::UnPack(const flatbuffers::resolver_function_t *_resolver)
const
{
  auto _o = new oneT();
  UnPackTo(_o, _resolver);
  return _o;
}

inline void one::UnPackTo(oneT *_o,
                          const flatbuffers::resolver_function_t *_resolver) const
{
  (void)_o;
  (void)_resolver;
  {
    auto _e = fieldone();
    _o->fieldone = _e;
  };
}

inline flatbuffers::Offset<one> one::Pack(flatbuffers::FlatBufferBuilder &_fbb,
    const oneT *_o, const flatbuffers::rehasher_function_t *_rehasher)
{
  return Createone(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<one> Createone(flatbuffers::FlatBufferBuilder &_fbb,
    const oneT *_o, const flatbuffers::rehasher_function_t *_rehasher)
{
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs {
    flatbuffers::FlatBufferBuilder *__fbb;
    const oneT *__o;
    const flatbuffers::rehasher_function_t *__rehasher;
  } _va = { &_fbb, _o, _rehasher};
  (void)_va;
  auto _fieldone = _o->fieldone;
  return Createone(
           _fbb,
           _fieldone);
}

inline twoT *two::UnPack(const flatbuffers::resolver_function_t *_resolver)
const
{
  auto _o = new twoT();
  UnPackTo(_o, _resolver);
  return _o;
}

inline void two::UnPackTo(twoT *_o,
                          const flatbuffers::resolver_function_t *_resolver) const
{
  (void)_o;
  (void)_resolver;
  {
    auto _e = fieldtwo();
    _o->fieldtwo = _e;
  };
}

inline flatbuffers::Offset<two> two::Pack(flatbuffers::FlatBufferBuilder &_fbb,
    const twoT *_o, const flatbuffers::rehasher_function_t *_rehasher)
{
  return Createtwo(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<two> Createtwo(flatbuffers::FlatBufferBuilder &_fbb,
    const twoT *_o, const flatbuffers::rehasher_function_t *_rehasher)
{
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs {
    flatbuffers::FlatBufferBuilder *__fbb;
    const twoT *__o;
    const flatbuffers::rehasher_function_t *__rehasher;
  } _va = { &_fbb, _o, _rehasher};
  (void)_va;
  auto _fieldtwo = _o->fieldtwo;
  return Createtwo(
           _fbb,
           _fieldtwo);
}

inline threeT *three::UnPack(const flatbuffers::resolver_function_t *_resolver)
const
{
  auto _o = new threeT();
  UnPackTo(_o, _resolver);
  return _o;
}

inline void three::UnPackTo(threeT *_o,
                            const flatbuffers::resolver_function_t *_resolver) const
{
  (void)_o;
  (void)_resolver;
  {
    auto _e = fieldthree();
    _o->fieldthree = _e;
  };
}

inline flatbuffers::Offset<three> three::Pack(flatbuffers::FlatBufferBuilder
    &_fbb, const threeT *_o, const flatbuffers::rehasher_function_t *_rehasher)
{
  return Createthree(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<three> Createthree(flatbuffers::FlatBufferBuilder
    &_fbb, const threeT *_o, const flatbuffers::rehasher_function_t *_rehasher)
{
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs {
    flatbuffers::FlatBufferBuilder *__fbb;
    const threeT *__o;
    const flatbuffers::rehasher_function_t *__rehasher;
  } _va = { &_fbb, _o, _rehasher};
  (void)_va;
  auto _fieldthree = _o->fieldthree;
  return Createthree(
           _fbb,
           _fieldthree);
}

inline testingunionsT *testingunions::UnPack(const
    flatbuffers::resolver_function_t *_resolver) const
{
  auto _o = new testingunionsT();
  UnPackTo(_o, _resolver);
  return _o;
}

inline void testingunions::UnPackTo(testingunionsT *_o,
                                    const flatbuffers::resolver_function_t *_resolver) const
{
  (void)_o;
  (void)_resolver;
  {
    auto _e = myfield_type();
    _o->myfield.type = _e;
  };
  {
    auto _e = myfield();
    if (_e) {
      _o->myfield.value = myunionUnion::UnPack(_e, myfield_type(), _resolver);
    }
  };
  {
    auto _e = dumbfield();
    _o->dumbfield = _e;
  };
}

inline flatbuffers::Offset<testingunions> testingunions::Pack(
  flatbuffers::FlatBufferBuilder &_fbb, const testingunionsT *_o,
  const flatbuffers::rehasher_function_t *_rehasher)
{
  return Createtestingunions(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<testingunions> Createtestingunions(
  flatbuffers::FlatBufferBuilder &_fbb, const testingunionsT *_o,
  const flatbuffers::rehasher_function_t *_rehasher)
{
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs {
    flatbuffers::FlatBufferBuilder *__fbb;
    const testingunionsT *__o;
    const flatbuffers::rehasher_function_t *__rehasher;
  } _va = { &_fbb, _o, _rehasher};
  (void)_va;
  auto _myfield_type = _o->myfield.type;
  auto _myfield = _o->myfield.Pack(_fbb);
  auto _dumbfield = _o->dumbfield;
  return Createtestingunions(
           _fbb,
           _myfield_type,
           _myfield,
           _dumbfield);
}

inline bool Verifymyunion(flatbuffers::Verifier &verifier, const void *obj,
                          myunion type)
{
  switch (type) {
  case myunion_NONE: {
    return true;
  }
  case myunion_one: {
    auto ptr = reinterpret_cast<const one *>(obj);
    return verifier.VerifyTable(ptr);
  }
  case myunion_two: {
    auto ptr = reinterpret_cast<const two *>(obj);
    return verifier.VerifyTable(ptr);
  }
  case myunion_three: {
    auto ptr = reinterpret_cast<const three *>(obj);
    return verifier.VerifyTable(ptr);
  }
  default:
    return false;
  }
}

inline bool VerifymyunionVector(flatbuffers::Verifier &verifier,
                                const flatbuffers::Vector<flatbuffers::Offset<void>> *values,
                                const flatbuffers::Vector<uint8_t> *types)
{
  if (!values || !types) {
    return !values && !types;
  }
  if (values->size() != types->size()) {
    return false;
  }
  for (flatbuffers::uoffset_t i = 0; i < values->size(); ++i) {
    if (!Verifymyunion(
          verifier,  values->Get(i), types->GetEnum<myunion>(i))) {
      return false;
    }
  }
  return true;
}

inline void *myunionUnion::UnPack(const void *obj, myunion type,
                                  const flatbuffers::resolver_function_t *resolver)
{
  switch (type) {
  case myunion_one: {
    auto ptr = reinterpret_cast<const one *>(obj);
    return ptr->UnPack(resolver);
  }
  case myunion_two: {
    auto ptr = reinterpret_cast<const two *>(obj);
    return ptr->UnPack(resolver);
  }
  case myunion_three: {
    auto ptr = reinterpret_cast<const three *>(obj);
    return ptr->UnPack(resolver);
  }
  default:
    return nullptr;
  }
}

inline flatbuffers::Offset<void> myunionUnion::Pack(
  flatbuffers::FlatBufferBuilder &_fbb,
  const flatbuffers::rehasher_function_t *_rehasher) const
{
  switch (type) {
  case myunion_one: {
    auto ptr = reinterpret_cast<const oneT *>(value);
    return Createone(_fbb, ptr, _rehasher).Union();
  }
  case myunion_two: {
    auto ptr = reinterpret_cast<const twoT *>(value);
    return Createtwo(_fbb, ptr, _rehasher).Union();
  }
  case myunion_three: {
    auto ptr = reinterpret_cast<const threeT *>(value);
    return Createthree(_fbb, ptr, _rehasher).Union();
  }
  default:
    return 0;
  }
}

inline myunionUnion::myunionUnion(const myunionUnion &u) FLATBUFFERS_NOEXCEPT :
type(u.type), value(nullptr)
{
  switch (type) {
  case myunion_one: {
    value = new oneT(*reinterpret_cast<oneT *>(u.value));
    break;
  }
  case myunion_two: {
    value = new twoT(*reinterpret_cast<twoT *>(u.value));
    break;
  }
  case myunion_three: {
    value = new threeT(*reinterpret_cast<threeT *>(u.value));
    break;
  }
  default:
    break;
  }
}

inline void myunionUnion::Reset()
{
  switch (type) {
  case myunion_one: {
    auto ptr = reinterpret_cast<oneT *>(value);
    delete ptr;
    break;
  }
  case myunion_two: {
    auto ptr = reinterpret_cast<twoT *>(value);
    delete ptr;
    break;
  }
  case myunion_three: {
    auto ptr = reinterpret_cast<threeT *>(value);
    delete ptr;
    break;
  }
  default:
    break;
  }
  value = nullptr;
  type = myunion_NONE;
}

inline const flatbuffers::TypeTable *myunionTypeTable()
{
  static const flatbuffers::TypeCode type_codes[] = {
    { flatbuffers::ET_SEQUENCE, 0, -1 },
    { flatbuffers::ET_SEQUENCE, 0, 0 },
    { flatbuffers::ET_SEQUENCE, 0, 1 },
    { flatbuffers::ET_SEQUENCE, 0, 2 }
  };
  static const flatbuffers::TypeFunction type_refs[] = {
    oneTypeTable,
    twoTypeTable,
    threeTypeTable
  };
  static const char *const names[] = {
    "NONE",
    "one",
    "two",
    "three"
  };
  static const flatbuffers::TypeTable tt = {
    flatbuffers::ST_UNION, 4, type_codes, type_refs, nullptr, names
  };
  return &tt;
}

inline const flatbuffers::TypeTable *oneTypeTable()
{
  static const flatbuffers::TypeCode type_codes[] = {
    { flatbuffers::ET_FLOAT, 0, -1 }
  };
  static const char *const names[] = {
    "fieldone"
  };
  static const flatbuffers::TypeTable tt = {
    flatbuffers::ST_TABLE, 1, type_codes, nullptr, nullptr, names
  };
  return &tt;
}

inline const flatbuffers::TypeTable *twoTypeTable()
{
  static const flatbuffers::TypeCode type_codes[] = {
    { flatbuffers::ET_FLOAT, 0, -1 }
  };
  static const char *const names[] = {
    "fieldtwo"
  };
  static const flatbuffers::TypeTable tt = {
    flatbuffers::ST_TABLE, 1, type_codes, nullptr, nullptr, names
  };
  return &tt;
}

inline const flatbuffers::TypeTable *threeTypeTable()
{
  static const flatbuffers::TypeCode type_codes[] = {
    { flatbuffers::ET_FLOAT, 0, -1 }
  };
  static const char *const names[] = {
    "fieldthree"
  };
  static const flatbuffers::TypeTable tt = {
    flatbuffers::ST_TABLE, 1, type_codes, nullptr, nullptr, names
  };
  return &tt;
}

inline const flatbuffers::TypeTable *testingunionsTypeTable()
{
  static const flatbuffers::TypeCode type_codes[] = {
    { flatbuffers::ET_UTYPE, 0, 0 },
    { flatbuffers::ET_SEQUENCE, 0, 0 },
    { flatbuffers::ET_INT, 0, -1 }
  };
  static const flatbuffers::TypeFunction type_refs[] = {
    myunionTypeTable
  };
  static const char *const names[] = {
    "myfield_type",
    "myfield",
    "dumbfield"
  };
  static const flatbuffers::TypeTable tt = {
    flatbuffers::ST_TABLE, 3, type_codes, type_refs, nullptr, names
  };
  return &tt;
}

#endif  // FLATBUFFERS_GENERATED_TESTINGPROTOCOLS_H_
