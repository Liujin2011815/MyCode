/******************************************************************************
*
*               (C) COPYRIGHT Pacific MindWorks, Inc. 2001-2015
*                          All rights reserved.
*
*****************************************************************************/
#pragma once

#include <cassert>
#include <memory>
#include <string>
#include <vector>
#include <queue>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <type_traits>
#include <typeindex>
#include <functional>
#include <regex>
#include <tuple>
#include <algorithm>
#include <cmath>
#include <initializer_list>
#include <IviVisaType.h>
#include <IviCShared.h>
#include <IviConfigServer.h>

#define CURRENT_TIMEOUT					-2

#define NRT_UNUSED(x) x

#define NRT_MAX_ERROR	1024

#ifndef MAX_STRING_ATTRIBUTE_LENGTH
#define MAX_STRING_ATTRIBUTE_LENGTH	4096
#endif

#ifndef NRT_NO_VISA
#include <visa.h>
#endif	// NRT_NO_VISA

namespace nrt
{
///////////////////////////////////////////////////////////////////////////////
// Forward declarations
//
struct DriverInfo;
class DriverSession;

template <typename TSession>
class VisaSession;

template <typename T>
struct CacheEntry;

template <typename TRepCap, typename Nested = void>
class PhysicalName;

template <typename TRepCap>
using PhysicalNameList = std::vector < PhysicalName<TRepCap> >;

template <typename TRepCap, typename TParent = typename TRepCap::Parent>
using PhysicalNameMap = std::map < PhysicalName<TParent> /*parent*/, PhysicalNameList<TRepCap> /*child physical names*/ >;

template <typename TRepCap>
using HasNoParent = typename std::is_same < typename TRepCap::Parent, nullptr_t >;

///////////////////////////////////////////////////////////////////////////////
// Utility functions
//
std::vector<std::string> Split(const std::string& str, char cDelimiter, bool bTrimWhitespace = true);
std::vector<std::string>& Split(const std::string &str, char cDelimiter, bool bTrimWhitespace, std::vector<std::string> &vecElements);
std::string Trim(const std::string& str, const std::string& strToTrim);
std::string TrimWhitespace(const std::string& str, const std::string& strWhitespace = " \t\r\n");
std::string RemoveWhitespace(const std::string str);
bool IsWhitespace(const std::string& str);

template <typename ...Args>
int IndexOfNull(Args... args);

template <typename T, typename... Ts>
struct AllAreOfType;

template <typename T, typename First, typename... Rest>
struct AllAreOfType < T, First, Rest... >
{
    static const bool value = std::is_same<T, First>::value && AllAreOfType<T, Rest...>::value;
};

template <typename T, typename U>
struct AllAreOfType < T, U >
{
    static const bool value = std::is_same<T, U>::value;
};

///////////////////////////////////////////////////////////////////////////////
// Utility alias templates
//
template <typename T>
using RemovePointer = typename std::remove_pointer<T>::type;

template <typename T>
using RemoveReference = typename std::remove_reference<T>::type;

template <typename T>
using RemoveConst = typename std::remove_const<T>::type;

template <typename T>
using Unqualified = RemoveConst < RemoveReference<T> >;

template <typename TIterator>
using ElementType = typename std::iterator_traits<TIterator>::value_type;

template <typename TIterator>
using UnqualifiedElementType = Unqualified < ElementType<TIterator> >;

///////////////////////////////////////////////////////////////////////////////
// Error-checking macros
//
#define ReturnOnError(status) \
    { auto _status_ = (status); if (_status_ < 0) return _status_; }

#define CheckForNull(Vi, ...)	\
    ReturnOnError(CheckForNullPointers(Vi, __FUNCTION__, #__VA_ARGS__, __VA_ARGS__))

#define ValidateSession(Vi)	\
    ReturnOnError(ValidateDriverSession(Vi))

#define CheckForUnsupportedModel(Vi, unsupportedModels)	\
                                                                                {   \
        static std::vector<std::string> _unsupportedModels = Split(unsupportedModels, ',');	\
        static std::string _functionName = __FUNCTION__;	\
        static bool _isAttribute = InsideAttributeGetter() || InsideAttributeSetter(); \
        ReturnOnError(_CheckForUnsupportedModel(Vi, _unsupportedModels, _functionName, _isAttribute))	\
                                                                                }

    ///////////////////////////////////////////////////////////////////////////////
    // Validation functions
    //
template <typename ...Args>
ViStatus CheckForNullPointers(ViSession Vi, char* pszFunctionName, char* pszParamNames, Args... args);

ViStatus ValidateDriverSession(ViSession Vi);

ViStatus _CheckForUnsupportedModel(ViSession Vi, const std::vector<std::string>& vecUnsupportedModels, const std::string& strFunctionName, bool bIsAttribute);

///////////////////////////////////////////////////////////////////////////////
// Function object for case-insensitive string comparison
//
struct StringComparerNoCase : public std::binary_function < std::string, std::string, bool >
{
    struct CharComparerNoCase
    {
        const std::ctype<char>& ct;

        CharComparerNoCase(const std::ctype<char>& c) : ct(c) {}

        bool operator()(char x, char y) const
        {
            return ct.toupper(x) < ct.toupper(y);
        }
    };

    std::locale loc;
    const std::ctype<char>& ct;

    StringComparerNoCase(const std::locale& L = std::locale::classic())
        : loc(L), ct(std::use_facet<std::ctype<char> >(loc)) {}

    bool operator()(const std::string& x, const std::string& y) const
    {
        return std::lexicographical_compare(std::begin(x), std::end(x),
            std::begin(y), std::end(y),
            CharComparerNoCase(ct));
    }
};

///////////////////////////////////////////////////////////////////////////////
// DriverInfo
//
struct DriverInfo
{
    std::string Prefix;
    std::string DriverVendor;
    std::string DriverDescription;
    std::string DriverRevision;
    std::string GroupCapabilities;
    std::string DefaultSimulatedModel;
    int SpecificationMajorVersion;
    int SpecificationMinorVersion;
};

// This variable is initialized in the driver's DriverInfo.cpp file
//
extern const DriverInfo g_driverInfo;

///////////////////////////////////////////////////////////////////////////////
// IoSession
//
__interface IoSession
{
    // When VISA is not being used as the I/O provider, the following methods must be overridden and implemented in the user's DriverSession-derived class
    //
    virtual ViStatus InitializeIO() abstract;
    virtual ViStatus CloseIO() abstract;
    virtual ViStatus ClearIOStatus() abstract;
    virtual ViStatus GetIdentificationInfo(std::string& strManufacturer, std::string& strModel, std::string& strSerialNumber, std::string& strFirmwareRevision) abstract;
    virtual ViStatus PollInstrumentErrors() abstract;
};

///////////////////////////////////////////////////////////////////////////////
// VisaSession
//
template <typename TSession>
class VisaSession : public IoSession
{
public:
    VisaSession();

    virtual ViStatus InitializeIO() override;
    virtual ViStatus CloseIO() override;
    virtual ViStatus ClearIOStatus() override;
    virtual ViStatus GetIdentificationInfo(std::string& strManufacturer, std::string& strModel, std::string& strSerialNumber, std::string& strFirmwareRevision) override;
    virtual ViStatus PollInstrumentErrors() override;

    ViSession GetVisaResourceManager() const;
    ViSession GetVisaSession() const;

private:
    ViSession m_visaResourceManager;
    ViSession m_visaSession;
};

///////////////////////////////////////////////////////////////////////////////
// VisaTimeoutManager
//
class VisaTimeoutManager
{
public:
    VisaTimeoutManager(ViSession visaSession, const long lTimeout = CURRENT_TIMEOUT);
    ~VisaTimeoutManager();

private:
    long m_lPrevTimeout;
    ViSession m_visaSession;
};

///////////////////////////////////////////////////////////////////////////////
// DriverSession
//
// This class conditionally derives from VisaSession or IoSession, depending upon
// whether or not the preprocessor symbol NRT_NO_VISA is defined.  This symbol
// is controlled by an MSBuild property in the IVI-C driver project file.  For 
// non-VISA drivers, the DriverSession will derive from the abstract IoSession 
// interface, making clear which I/O functions must be implemented by the user's 
// driver session class.
//

#if defined(NRT_NO_VISA)
static const bool NoVisa = true;
#else
static const bool NoVisa = false;
#endif

template <typename TValue>
using DriverSettingsMap = std::map < std::string, TValue, StringComparerNoCase >;

template <typename T>
using AttributeCache = std::map < ViAttr, std::map<std::string, CacheEntry<T>> >;

using VirtualNameMap = std::map < std::string, std::string, StringComparerNoCase >;

class DriverSession : public std::conditional<NoVisa, IoSession, VisaSession<DriverSession>>::type
{
protected:
    DriverSession(ViSession handle,
        unsigned long ulVisaOpenTimeout,
        unsigned long ulSelfTestTimeout,
        unsigned long ulResetTimeout,
        bool bInterchangeCheckSupported,
        unsigned long ulCoercionLogSize);

public:
    template <typename TSession>
    ViStatus Initialize(const std::string& strResourceName, bool bIdQuery, bool bReset, const std::string& strOptions);
    virtual ViStatus Close();

    virtual ViSession Handle() const;

    virtual bool CacheEnabled() const;
    virtual bool InterchangeCheckEnabled() const;
    virtual bool QueryInstrStatusEnabled() const;
    virtual bool RangeCheckEnabled() const;
    virtual bool RecordCoercionsEnabled() const;
    virtual bool SimulationEnabled() const;

    virtual bool CacheEnabledOriginal() const;
    virtual bool InterchangeCheckEnabledOriginal() const;
    virtual bool QueryInstrStatusEnabledOriginal() const;
    virtual bool RangeCheckEnabledOriginal() const;
    virtual bool RecordCoercionsEnabledOriginal() const;
    virtual bool SimulationEnabledOriginal() const;

    virtual void SetCacheEnabled(bool bValue);
    virtual void SetInterchangeCheckEnabled(bool bValue);
    virtual void SetQueryInstrStatusEnabled(bool bValue);
    virtual void SetRangeCheckEnabled(bool bValue);
    virtual void SetRecordCoercionsEnabled(bool bValue);
    virtual void SetSimulationEnabled(bool bValue);

    virtual const std::string& InitOptions() const;
    virtual const std::string& ResourceName() const;
    virtual const std::string& LogicalName() const;
    virtual const std::string& IoDescriptor() const;
    virtual const std::string& DriverSetup() const;
    virtual const std::string& Manufacturer() const;
    virtual const std::string& InstrumentModel() const;
    virtual const std::string& SerialNumber() const;
    virtual const std::string& FirmwareRevision() const;

    virtual unsigned long VisaOpenTimeout() const;
    virtual unsigned long SelfTestTimeout() const;
    virtual unsigned long ResetTimeout() const;

    virtual bool InterchangeCheckSupported() const;
    virtual unsigned long CoercionLogSize() const;

    virtual bool GetDriverSetupOption(const std::string& strName, std::string& strValue) const;

    virtual bool GetConfigSettingBoolean(const std::string& strName, bool& bValue) const;
    virtual bool GetConfigSettingInt32(const std::string& strName, int& nValue) const;
    virtual bool GetConfigSettingReal64(const std::string& strName, double& dValue) const;
    virtual bool GetConfigSettingString(const std::string& strName, std::string& strValue) const;

    virtual const DriverSettingsMap<bool>& ConfigSettingsBoolean() const;
    virtual const DriverSettingsMap<int>& ConfigSettingsInt32() const;
    virtual const DriverSettingsMap<double>& ConfigSettingsReal64() const;
    virtual const DriverSettingsMap<std::string>& ConfigSettingsString() const;

    virtual const DriverSettingsMap<std::string>& InherentOptions() const;
    virtual const DriverSettingsMap<std::string>& DriverSetupOptions() const;
    virtual const VirtualNameMap& VirtualNameMappings() const;

    virtual const std::string TranslateVirtualName(const std::string& strVirtualName) const;
    virtual const std::string TranslatePhysicalName(const std::string& strPhysicalName) const;

    virtual bool InstrumentSupported() const;
    virtual bool InstrumentInFamily(const std::string& strFamily) const;
    virtual bool InstrumentIsModel(const std::string& strModel) const;
    virtual bool ModelInFamily(const std::string& strModel, const std::string& strFamily) const;

    virtual ViStatus ResetDefaults();

    virtual ViStatus ReportError(ViStatus errorCode, ...) const;
    virtual ViStatus ReportErrorEx(ViStatus errorCode, const std::string strElaboration, ...) const;
    virtual ViStatus ReportConfigServerError(ViStatus status) const;

    template <typename T>
    CacheEntry<T>& GetCacheEntry(ViAttr attributeId, const std::string& strQualifiedPhysicalName = std::string());

    template <typename... Args>
    void InvalidateAttributes(ViAttr attributeId, Args... args);
    void InvalidateAttributes(ViAttr attributeId);

    template <typename TRepCap, typename... Args>
    void InvalidateAttributes(const PhysicalNameList<TRepCap>& physicalNames, ViAttr attributeId, Args... args);

    template <typename TRepCap>
    void InvalidateAttributes(const PhysicalNameList<TRepCap>& physicalNames, ViAttr attributeId);

    virtual void InvalidateAllAttributes();

    template <typename T>
    void AddCoercionRecord(T desiredVal, T coercedVal, const std::string& strFunctionName, const std::string& strParameterName);

    std::string GetNextCoercionRecord();
    void RemoveNextCoercionRecord();

protected:
    virtual ViStatus LoadConfiguration(const std::string& strResourceName, const std::string& strOptions);
    virtual ViStatus LoadDriverSessionConfiguration(IviDriverSessionHandle hDriverSession);
    virtual ViStatus LoadConfigurableInitialSettings(IviConfigComponentHandle hConfigComponent);
    virtual ViStatus ProcessConfigurableInitialSettings();
    virtual ViStatus ProcessInitOptions(const std::string& strInitOptions);
    virtual ViStatus ProcessDriverSetup(const std::string& strDriverSetup);
    virtual ViStatus ProcessDriverSetupNameValuePair(const std::string& strName, std::string& strValue);
    virtual ViStatus ProcessInherentOptions(const std::string& strInherentOptions);
    virtual ViStatus ConvertInitOptionBoolean(const std::string& strOptionName, const std::string& strOptionValue, bool& bValue);
    virtual ViStatus LoadVirtualNames(IviDriverSessionHandle hDriverSession);
    virtual ViStatus LoadPhysicalNames(IviSoftwareModuleHandle hSoftwareModule);

private:
    ViSession m_handle;
    bool m_bIdQuery;
    bool m_bReset;

    bool m_bCache;
    bool m_bInterchangeCheck;
    bool m_bQueryInstrStatus;
    bool m_bRangeCheck;
    bool m_bRecordCoercions;
    bool m_bSimulate;

    bool m_bCacheOriginal;
    bool m_bInterchangeCheckOriginal;
    bool m_bQueryInstrStatusOriginal;
    bool m_bRangeCheckOriginal;
    bool m_bRecordCoercionsOriginal;
    bool m_bSimulateOriginal;

    unsigned long m_ulVisaOpenTimeout;
    unsigned long m_ulSelfTestTimeout;
    unsigned long m_ulResetTimeout;

    bool m_bInterchangeCheckSupported;
    unsigned long m_ulCoercionLogSize;

    std::string m_strInitOptions;
    std::string m_strResourceName;
    std::string m_strLogicalName;
    std::string m_strIoDescriptor;
    std::string m_strDriverSetup;
    std::string m_strManufacturer;
    std::string m_strModel;
    std::string m_strSerialNumber;
    std::string m_strFirmwareRevision;

    DriverSettingsMap<std::string> m_mapInherentOptions;
    DriverSettingsMap<std::string> m_mapDriverSetupOptions;
    DriverSettingsMap<bool> m_mapConfigSettingsBoolean;
    DriverSettingsMap<int> m_mapConfigSettingsInt32;
    DriverSettingsMap<double> m_mapConfigSettingsReal64;
    DriverSettingsMap<std::string> m_mapConfigSettingsString;
    DriverSettingsMap<std::string> m_mapVirtualNameToPhysicalName;
    DriverSettingsMap<std::string> m_mapPhysicalNameToVirtualName;
    DriverSettingsMap<std::string> m_mapPhysicalNameToRepCapName;

    // Attribute cache -- one entry per attribute per repcap physical name
    //
    AttributeCache<ViInt32> m_cacheViInt32;
    AttributeCache<ViInt64> m_cacheViInt64;
    AttributeCache<ViReal64> m_cacheViReal64;
    AttributeCache<ViBoolean> m_cacheViBoolean;
    AttributeCache<ViSession> m_cacheViSession;
    AttributeCache<std::string> m_cacheString;

    // Coercion log
    //
    std::deque<std::string> m_coercionRecords;

    friend class AttributeInfo;
};

///////////////////////////////////////////////////////////////////////////////
// I/O functions
//
ViStatus ClearIOStatus(ViSession Vi);
ViStatus PollInstrumentErrors(ViSession Vi);

///////////////////////////////////////////////////////////////////////////////
// VISA I/O functions
//
#ifndef NRT_NO_VISA

ViSession GetVisaSession(ViSession Vi);
ViSession GetVisaResourceManager(ViSession Vi);

// Helpers for implementing IVI-C wrapper direct I/O functions as defined in IVI-3.1
//
ViStatus ReadBytes(ViSession Vi, ViInt64 BufferSize, ViByte Buffer[], ViInt64* ReturnCount);
ViStatus WriteBytes(ViSession Vi, ViByte Buffer[], ViInt64 Count, ViInt64* ReturnCount);

// Helpers for implementing VISA-based functions that read string-based lists
//
template<typename TElement, int ElementSize>
ViStatus ReadList(ViSession Vi, ViInt64 cMaxElements, std::vector<TElement>& vecElements, std::function<ViStatus(const char*, TElement&)> transform);

template<typename TElement, int ElementSize>
ViStatus ReadList(ViSession Vi, ViInt64 cMaxElements, TElement Elements[], ViInt64* pcActualElements, std::function<ViStatus(const char*, TElement&)> transform);

template<int ElementSize>
ViStatus ReadStringList(ViSession Vi, ViInt64 cMaxElements, std::vector<std::string>& vecElements);

template<typename TEnum>
ViStatus ReadEnumList(ViSession Vi, ViInt64 cMaxElements, std::vector<ViInt32>& vecElements);

template<typename TEnum>
ViStatus ReadEnumList(ViSession Vi, ViInt32 cMaxElements, ViInt32 Elements[], ViInt32* pcActualElements);

template<typename TEnum>
ViStatus ReadEnumList(ViSession Vi, ViInt64 cMaxElements, ViInt32 Elements[], ViInt64* pcActualElements);

template<typename TBool>
ViStatus ReadBoolList(ViSession Vi, ViInt64 cMaxElements, std::vector<ViBoolean>& vecElements);

template<typename TBool>
ViStatus ReadBoolList(ViSession Vi, ViInt32 cMaxElements, ViBoolean Elements[], ViInt32* pcActualElements);

template<typename TBool>
ViStatus ReadBoolList(ViSession Vi, ViInt64 cMaxElements, ViBoolean Elements[], ViInt64* pcActualElements);

// Helpers for implementing VISA-based functions that write string-based lists
//
template<typename TElement>
ViStatus WriteList(ViSession Vi, ViInt64 cMaxElements, const std::vector<TElement>& vecElements, std::function<ViStatus(const TElement&, std::string&)> transform, bool bAppendLineFeed);

template<typename TElement>
ViStatus WriteList(ViSession Vi, ViInt64 cMaxElements, TElement Elements[], std::function<ViStatus(const TElement&, std::string&)> transform, bool bAppendLineFeed);

ViStatus WriteStringList(ViSession Vi, ViInt64 cMaxElements, const std::vector<std::string>& vecElements, bool bAppendLineFeed = true);

template<typename TEnum>
ViStatus WriteEnumList(ViSession Vi, ViInt64 cMaxElements, ViInt32 Elements[], bool bAppendLineFeed = true);

template<typename TBool>
ViStatus WriteBoolList(ViSession Vi, ViInt64 cMaxElements, ViBoolean Elements[], bool bAppendLineFeed = true);

#endif	// NRT_NO_VISA

///////////////////////////////////////////////////////////////////////////////
// Driver operation functions
//
bool CacheEnabled(ViSession Vi);
bool InterchangeCheckEnabled(ViSession Vi);
bool QueryInstrStatusEnabled(ViSession Vi);
bool RangeCheckEnabled(ViSession Vi);
bool RecordCoercionsEnabled(ViSession Vi);
bool SimulationEnabled(ViSession Vi);

bool CacheEnabledOriginal(ViSession Vi);
bool InterchangeCheckEnabledOriginal(ViSession Vi);
bool QueryInstrStatusEnabledOriginal(ViSession Vi);
bool RangeCheckEnabledOriginal(ViSession Vi);
bool RecordCoercionsEnabledOriginal(ViSession Vi);
bool SimulationEnabledOriginal(ViSession Vi);

void SetCacheEnabled(ViSession Vi, bool bValue);
void SetInterchangeCheckEnabled(ViSession Vi, bool bValue);
void SetQueryInstrStatusEnabled(ViSession Vi, bool bValue);
void SetRangeCheckEnabled(ViSession Vi, bool bValue);
void SetRecordCoercionsEnabled(ViSession Vi, bool bValue);
void SetSimulationEnabled(ViSession Vi, bool bValue);

const std::string& InitOptions(ViSession Vi);
const std::string& ResourceName(ViSession Vi);
const std::string& LogicalName(ViSession Vi);
const std::string& IoDescriptor(ViSession Vi);
const std::string& DriverSetup(ViSession Vi);
const std::string& Manufacturer(ViSession Vi);
const std::string& InstrumentModel(ViSession Vi);
const std::string& SerialNumber(ViSession Vi);
const std::string& FirmwareRevision(ViSession Vi);

unsigned long VisaOpenTimeout();
unsigned long SelfTestTimeout();
unsigned long ResetTimeout();

bool InterchangeCheckSupported();
unsigned long CoercionLogSize();

///////////////////////////////////////////////////////////////////////////////
// Configuration access functions
//
bool GetDriverSetupOption(ViSession Vi, const std::string& strName, std::string& strValue);

bool GetConfigSettingBoolean(ViSession Vi, const std::string& strName, bool& bValue);
bool GetConfigSettingInt32(ViSession Vi, const std::string& strName, int& nValue);
bool GetConfigSettingReal64(ViSession Vi, const std::string& strName, double& dValue);
bool GetConfigSettingString(ViSession Vi, const std::string& strName, std::string& strValue);

const DriverSettingsMap<bool>& ConfigSettingsBoolean(ViSession Vi);
const DriverSettingsMap<int>& ConfigSettingsInt32(ViSession Vi);
const DriverSettingsMap<double>& ConfigSettingsReal64(ViSession Vi);
const DriverSettingsMap<std::string>& ConfigSettingsString(ViSession Vi);

const DriverSettingsMap<std::string>& InherentOptions(ViSession Vi);
const DriverSettingsMap<std::string>& DriverSetupOptions(ViSession Vi);

///////////////////////////////////////////////////////////////////////////////
// Miscellaneous functions
//
bool InstrumentSupported(ViSession Vi);
bool InstrumentInFamily(ViSession Vi, const std::string& strFamily);
bool InstrumentIsModel(ViSession Vi, const std::string& strModel);
bool ModelInFamily(ViSession Vi, const std::string& strModel, const std::string& strFamily);

template <typename T>
struct ModelBasedType
{
    typedef typename T value_type;

    ModelBasedType();
    ModelBasedType(const std::string& strModelList);

    std::vector<std::string> Models;
};

template <typename TIterator>
TIterator FindModelSpecificValue(ViSession Vi, const std::string& strModel, TIterator itFirst, TIterator itLast);

///////////////////////////////////////////////////////////////////////////////
// Virtual name functions
//
const std::string TranslateVirtualName(ViSession Vi, const std::string& strVirtualName);
const std::string TranslatePhysicalName(ViSession Vi, const std::string& strPhysicalName);
const VirtualNameMap& VirtualNameMappings(ViSession Vi);

///////////////////////////////////////////////////////////////////////////////
// Error reporting 
//
const std::string GetErrorMessage(ViStatus errorCode);

ViStatus ReportError(ViSession Vi, ViStatus errorCode, ...);
ViStatus ReportErrorEx(ViSession Vi, ViStatus errorCode, const std::string strElaboration, ...);
ViStatus ReportErrorV(ViSession Vi, ViStatus errorCode, const std::string strElaboration, va_list argList);

///////////////////////////////////////////////////////////////////////////////
// Attribute support
//
template <typename T>
using AttributeGetter = ViStatus(_VI_FUNC*) (ViSession Vi, ViConstString RepCapIdentifier, T* AttributeValue);

template <typename T>
using AttributeSetter = ViStatus(_VI_FUNC*) (ViSession Vi, ViConstString RepCapIdentifier, T AttributeValue);

using AttributeGetterViString = ViStatus(_VI_FUNC*) (ViSession Vi, ViConstString RepCapIdentifier, ViInt32 AttributeValueBufferSize, ViChar AttributeValue[]);
using AttributeSetterViString = ViStatus(_VI_FUNC*) (ViSession Vi, ViConstString RepCapIdentifier, ViConstString AttributeValue);

using AttributeInvalidator = std::function<void(DriverSession* pDriverSession, bool bInvalidateForAllPhysicalNames, const std::string& strQualifiedPhysicalName)>;

class AttributeInfo
{
public:
    AttributeInfo(ViAttr id, const std::string strName, AttributeGetter<ViInt32> getter, AttributeSetter<ViInt32> setter);
    AttributeInfo(ViAttr id, const std::string strName, AttributeGetter<ViInt64> getter, AttributeSetter<ViInt64> setter);
    AttributeInfo(ViAttr id, const std::string strName, AttributeGetter<ViReal64> getter, AttributeSetter<ViReal64> setter);
    AttributeInfo(ViAttr id, const std::string strName, AttributeGetter<ViBoolean> getter, AttributeSetter<ViBoolean> setter);
    AttributeInfo(ViAttr id, const std::string strName, AttributeGetter<ViSession> getter, AttributeSetter<ViSession> setter);
    AttributeInfo(ViAttr id, const std::string strName, AttributeGetterViString getter, AttributeSetterViString setter);

    template <typename TGetter>
    TGetter Getter() const;

    template <typename TSetter>
    TSetter Setter() const;

    ViAttr AttributeId() const;
    const std::string& AttributeName() const;
    const std::string& TypeName() const;
    const type_info& TypeInfo() const;
    const AttributeInvalidator& Invalidator() const;

private:
    ViAttr m_id;
    const std::string m_strAttributeName;
    const std::string m_strTypeName;
    const type_info& m_typeInfo;

    union
    {
        AttributeGetter<ViInt32> pViInt32;
        AttributeGetter<ViInt64> pViInt64;
        AttributeGetter<ViReal64> pViReal64;
        AttributeGetter<ViBoolean> pViBoolean;
        AttributeGetter<ViSession> pViSession;
        AttributeGetterViString pViString;
    } m_getter;

    union
    {
        AttributeSetter<ViInt32> pViInt32;
        AttributeSetter<ViInt64> pViInt64;
        AttributeSetter<ViReal64> pViReal64;
        AttributeSetter<ViBoolean> pViBoolean;
        AttributeSetter<ViSession> pViSession;
        AttributeSetterViString pViString;
    } m_setter;

    AttributeInvalidator m_invalidator;
};

using AttributeMap = std::map < ViAttr, AttributeInfo >;

// This variable is initialized in the driver's Attributes.cpp file
//
extern const AttributeMap g_AttributeMap;

#define BEGIN_ATTRIBUTE_MAP() \
    const nrt::AttributeMap nrt::g_AttributeMap = \
                                                                                {	\

#define ATTRIBUTE_MAP_ENTRY(id, getter, setter)	\
                                                                                { id, { id, #id, getter, setter } },

#define END_ATTRIBUTE_MAP() \
                                                                                };

///////////////////////////////////////////////////////////////////////////////
// Instrument model support
//
using ModelMap = std::map < std::string /*model*/, std::string /*family*/ >;

// This variable is initialized in the driver's Models.cpp file
//
extern const ModelMap g_modelMap;

#define BEGIN_MODEL_MAP() \
    const nrt::ModelMap nrt::g_modelMap = []()->nrt::ModelMap	\
                                                                                {	\
    nrt::ModelMap modelMap;

#define MODEL_ENTRY(family, models)	\
    for (const auto& it : nrt::Split(models, ','))	\
                                                                                {	\
    modelMap[nrt::TrimWhitespace(it)] = nrt::TrimWhitespace(family);	\
                                                                                }

#define END_MODEL_MAP()	\
    return modelMap;	\
                                                                                }();

///////////////////////////////////////////////////////////////////////////////
// Repeated capability support
//
struct ListElement
{
    std::string Text;
    bool IsRange;
    std::vector<std::string> Identifiers;
};

struct PathSegment
{
    bool IsEnclosedInBrackets;
    std::vector<ListElement> ListElements;
};

// PhysicalName name specialization used for non-nested repcaps
//
template <typename TRepCap>
class PhysicalName < TRepCap, typename std::enable_if<HasNoParent<TRepCap>::value>::type >
{
public:
    PhysicalName(const char* szName);
    PhysicalName(std::string szName = std::string());

    const char* Name() const;
    const char* FullName() const;

    const char* QualifiedName() const;
    const char* QualifiedFullName() const;

    const char* ExportedName() const;
    const char* ExportedFullName() const;

    int Index(ViSession Vi) const;

    const PhysicalNameList<TRepCap>& ParentList(ViSession Vi) const;

    bool IsDefined(ViSession Vi) const;

    bool operator==(const PhysicalName<TRepCap>& other) const;
    bool operator!=(const PhysicalName<TRepCap>& other) const;
    bool operator<(const PhysicalName<TRepCap>& other) const;
    bool operator>(const PhysicalName<TRepCap>& other) const;
    bool operator<=(const PhysicalName<TRepCap>& other) const;
    bool operator>=(const PhysicalName<TRepCap>& other) const;

private:
    std::string m_strName;
    std::string m_strQualifiedName;
};

// PhysicalName name specialization for nested repcaps
//
template <typename TRepCap, typename Nested>
class PhysicalName
{
public:
    PhysicalName(const char* szFullName);
    PhysicalName(std::string strFullName = std::string());

    const char* Name() const;
    const char* ParentName() const;

    template <typename TAncestor>
    const char* AncestorName() const;

    const char* FullName() const;
    std::string ParentFullName() const;

    template <typename TAncestor>
    std::string AncestorFullName() const;

    const char* QualifiedName() const;
    const char* QualifiedFullName() const;

    const char* ExportedName() const;
    const char* ExportedFullName() const;

    int Index(ViSession Vi) const;

    template <typename TAncestor>
    int AncestorIndex(ViSession Vi) const;

    const PhysicalNameList<TRepCap>& ParentList(ViSession Vi) const;

    bool IsDefined(ViSession Vi) const;

    bool operator==(const PhysicalName<TRepCap>& other) const;
    bool operator!=(const PhysicalName<TRepCap>& other) const;
    bool operator<(const PhysicalName<TRepCap>& other) const;
    bool operator>(const PhysicalName<TRepCap>& other) const;
    bool operator<=(const PhysicalName<TRepCap>& other) const;
    bool operator>=(const PhysicalName<TRepCap>& other) const;

private:
    std::string m_strFullName;
    std::string m_strQualifiedName;
    std::string m_strQualifiedFullName;
    std::string m_strExportedFullName;
    std::vector<std::string> m_vecNameParts;
};

// Shared base class for all style of repcaps
//
template <typename T, typename TParent>
class RepCapBase
{
public:
    typedef typename TParent Parent;

    static const bool HasParent = std::is_same<TParent, nullptr_t>::value;

    static ViStatus ExpandSelector(ViSession Vi, ViConstString szSelector, PhysicalNameList<T>& physicalNames, bool bVerifyPhysicalNamesExist = true);
    static ViStatus ExpandSingleSelector(ViSession Vi, ViConstString szSelector, PhysicalName<T>& physicalName);
    static ViStatus AddPhysicalNames(ViSession Vi, const std::string& strSelector);
    static ViStatus RemovePhysicalNames(ViSession Vi, const std::string& strSelector);

protected:
    static PhysicalNameList<T> Initialize(ViConstString szSelector);
    static ViStatus EnsurePhysicalNamesInitializedForSession(ViSession Vi);

private:
    static std::string ReplaceVirtualNames(ViSession Vi, const std::string& strSelector);
    static std::vector<std::string> ExpandListElement(const std::vector<ListElement>::iterator& itListElement, const std::vector<PathSegment>::iterator& itPathSegment, const std::vector<PathSegment>& vecPathSegments, std::set<std::string>& setChildListElements);
    static std::vector<std::string> GetChildIdentifiersInPathSegment(const std::vector<PathSegment>::iterator& itPathSegment, const std::vector<PathSegment>& vecPathSegments, std::set<std::string>& setChildListElements);
    static bool ListElementHasChildIdentifiers(const std::vector<ListElement>::iterator& itListElement, const std::vector<PathSegment>::iterator& itPathSegment, const std::vector<PathSegment>& vecPathSegments);
    static ViStatus GetListElementIdentifiers(ViSession Vi, const std::string& strListElement, std::vector<std::string>& vecIdentifiers);
    static ViStatus ExpandRange(ViSession Vi, const std::string& strRange, std::vector<std::string>& vecIdentifiers);
    static ViStatus ValidateSelectorSyntax(ViSession Vi, const std::string& strSelector);

private:
    static std::set<ViSession> m_setInitializedSessions;
};

template <typename T, typename TParent>
std::set<ViSession> RepCapBase<T, TParent>::m_setInitializedSessions;

// General definition for repcaps that have a parent (i.e. nested repcaps)
//	
template <typename T, typename TParent>
class RepCap : public RepCapBase < T, TParent >
{
public:
    static const int NestingLevel = (1 + TParent::NestingLevel);

    static int PhysicalNameCount(ViSession Vi);
    static PhysicalName<T> FirstPhysicalName(ViSession Vi);

    static const PhysicalNameList<T>& GetPhysicalNames(ViSession Vi, const PhysicalName<TParent>& parentPhysicalName);
    static PhysicalNameList<T>& GetMutablePhysicalNames(ViSession Vi, const PhysicalName<TParent>& parentPhysicalName);
    static ViStatus GetPhysicalNameAtIndex(ViSession Vi, ViConstString parentPhysicalName, ViInt32 nIndex, ViInt32 nNameBufferSize, ViChar szName[]);

    static ViStatus InitializePhysicalNamesForSession(ViSession Vi);
    static void ClearPhysicalNames(ViSession Vi);

private:
    static ViStatus AddPhysicalName(ViSession session, const PhysicalName<T>& physicalName);
    static ViStatus RemovePhysicalName(ViSession session, const PhysicalName<T>& physicalName);
    static PhysicalNameMap<T, TParent>& GetPhysicalNameMap(ViSession Vi);

private:
    // For nested repcaps, the physical map stores (on a per-session basis), a vector of child physical names for each parent physical name
    //
    static std::map<ViSession, PhysicalNameMap<T, TParent>> m_mapPhysicalNames;

    friend class RepCapBase < T, TParent >;
};

// RepCap specialization for repcaps that have no parent
//
template <typename T>
class RepCap<T, nullptr_t> : public RepCapBase < T, nullptr_t >
{
public:
    static const int NestingLevel = 0;

    static const PhysicalNameList<T>& GetPhysicalNames(ViSession Vi);
    static int PhysicalNameCount(ViSession Vi);
    static PhysicalName<T> FirstPhysicalName(ViSession Vi);

    static ViStatus GetPhysicalNameAtIndex(ViSession Vi, ViInt32 nIndex, ViInt32 nNameBufferSize, ViChar szName[]);

    static ViStatus InitializePhysicalNamesForSession(ViSession Vi);
    static void ClearPhysicalNames(ViSession Vi);

private:
    static ViStatus AddPhysicalName(ViSession session, const PhysicalName<T>& physicalName);
    static ViStatus RemovePhysicalName(ViSession session, const PhysicalName<T>& physicalName);
    static PhysicalNameList<T>& GetMutablePhysicalNames(ViSession Vi);

private:
    // For non-nested repcaps, the physical map stores (on a per-session basis), a simple vector of physical names
    //
    static std::map<ViSession, PhysicalNameList<T>> m_mapPhysicalNames;

    friend class RepCapBase < T, nullptr_t >;
};

// Base class for parameter-style repcaps
//
template <typename T, typename TParent>
class ParameterStyleRepCap : public RepCap < T, TParent >
{
};

// Base class for selector-style repcaps
//
template <typename T>
class SelectorStyleRepCap : public RepCap < T, nullptr_t >
{
public:
    static ViStatus ExpandActiveSelector(ViSession Vi, PhysicalNameList<T>& physicalNames);
    static ViStatus ExpandSingleActiveSelector(ViSession Vi, PhysicalName<T>& physicalName);
    static ViStatus SetActiveSelector(ViSession Vi, ViConstString szSelector);
    static ViStatus GetActiveSelector(ViSession Vi, ViInt32 nSelectorBufferSize, ViChar szSelector[]);
    static ViStatus GetActivePhysicalNames(ViSession Vi, PhysicalNameList<T>& physicalNames);
    static ViStatus GetActivePhysicalName(ViSession Vi, PhysicalName<T>& physicalName);

private:
    static std::map<ViSession, std::string> m_mapActiveSelectors;
    static std::map<ViSession, PhysicalNameList<T>> m_mapActivePhysicalNames;
};

enum class RepCapStyle
{
    Parameter,
    Selector
};

static std::vector<std::function<void(ViSession)>> g_vecPhysicalNameCleanupFunctions;

#define BEGIN_REPCAP_MAP() \

#define REPCAP_ENTRY(repCapType, physicalNames, style, useQualifiedPhysicalNames)	\
    REPCAP_ENTRY_EX(repCapType, physicalNames, style, useQualifiedPhysicalNames, nullptr_t)

#define REPCAP_ENTRY_EX(repCapType, physicalNames, style, useQualifiedPhysicalNames, parentType)	\
    class repCapType : public std::conditional<style == nrt::RepCapStyle::Selector, nrt::SelectorStyleRepCap<repCapType>, nrt::ParameterStyleRepCap<repCapType, parentType>>::type	\
                                                                                        {	\
    public:	\
    static const bool UseQualifiedPhysicalNames = useQualifiedPhysicalNames;    \
    static const std::string& Name() \
                                                                                        {	\
    static const std::string strName = #repCapType;	\
    return strName;	\
                                                                                            }	\
        static const nrt::PhysicalNameList<repCapType>& StaticPhysicalNames()	\
                                                                                        {	\
    static const auto names = Initialize(physicalNames);	\
    return names;	\
                                                                                            }	\
                                                                                            };  

#define END_REPCAP_MAP()	\

///////////////////////////////////////////////////////////////////////////////
// Enum command support
//
#define MAX_ENUM_RESPONSE	256

struct CommandInfo
{
    CommandInfo(const std::string& strName, ViInt32 nValue, const std::string& strCommandList, const std::string& strModelList)
        : Name(strName), Value(nValue), Commands(Split(strCommandList, ',')), Models(Split(strModelList, ','))
    {
    }

    std::string Name;
    ViInt32 Value;
    std::vector<std::string> Commands;
    std::vector<std::string> Models;
};

using CommandMap = std::vector < CommandInfo >;
using StringComparer = std::function<bool(const std::string&, const std::string&)>;

template <typename T>
class EnumConverter
{
public:
    static ViStatus ToCommand(ViSession Vi, ViInt32 nValue, std::string& strCommand);
    static ViStatus FromResponse(ViSession Vi, const std::string& strResponse, ViInt32* pnValue);
    static std::string MemberName(ViInt32 nValue);
};

#define BEGIN_ENUM_MAP(enumType)	\
    class enumType : public nrt::EnumConverter<enumType>		\
    {	\
    public:	\
		static const nrt::CommandMap& GetCommandMap()	\
		{	\
		    static nrt::CommandMap commands = \
		    {

#define ENUM_COMMAND(value,command,model)   \
    { #value, value, command, model },

#define ENUM_MEMBER(value)  \
    { #value, value, "!!!", "!!!" },

#define END_ENUM_MAP()	\
            };	\
            return commands;	\
        };	\
    };

// Note that for boolean responses, we always ignore case -- the CommandOptions are hardcoded to CommandOptions::IgnoreCase
//
#define BEGIN_BOOL_MAP()	\
    class Boolean   \
                                                                                {	\
    public: \
    static ViStatus ToCommand(ViSession Vi, ViBoolean bValue, std::string& strCommand)   \
                                                                                {   \
    return EnumConverter<Boolean>::ToCommand(Vi, bValue, strCommand);  \
                                                                                };  \
    static ViStatus FromResponse(ViSession Vi, const std::string& strResponse, ViBoolean* pbValue)   \
                                                                                {   \
    ViInt32 nValue; \
    auto status = EnumConverter<Boolean>::FromResponse(Vi, strResponse, &nValue);  \
    *pbValue = (ViBoolean)nValue;   \
    return status;  \
                                                                                };  \
    static const nrt::CommandMap& GetCommandMap()	\
                                                                                {	\
    static nrt::CommandMap commands = \
                                                                                {

#define TRUE_COMMAND(command,model) \
    ENUM_COMMAND(VI_TRUE, command, model)

#define FALSE_COMMAND(command,model) \
    ENUM_COMMAND(VI_FALSE, command, model)

#define END_BOOL_MAP()	\
    END_ENUM_MAP()

    ///////////////////////////////////////////////////////////////////////////////
    // Session locking support
    //
#define ObtainLock(Vi)	\
    SessionLock lock(Vi);	\
    ReturnOnError(lock.Obtain());

class SessionLock
{
public:
    SessionLock(ViSession Vi);
    ~SessionLock();

    ViStatus Obtain();

private:
    bool m_bObtainedLock;
    ViSession m_session;
};

///////////////////////////////////////////////////////////////////////////////
// Error message support
//
using ErrorMessageMap = std::map < ViStatus /*code*/, std::string /*message*/ >;

// This variable is initialized in the driver's Errors.cpp file
//
extern const ErrorMessageMap g_errorMessageMap;

#define BEGIN_ERROR_MESSAGE_MAP() \
    const nrt::ErrorMessageMap nrt::g_errorMessageMap = \
                                                                                {	\

#define ERROR_MESSAGE_MAP_ENTRY(code, message)	\
                                                                                { code, message },

#define END_ERROR_MESSAGE_MAP() \
                                                                                };

///////////////////////////////////////////////////////////////////////////////
// Range checking support
//
#define RangeCheckMinMax(Vi, value, ...)	\
                                                                                {	\
    if (RangeCheckEnabled(Vi))	\
                                                                                {	\
    static std::string _functionName = __FUNCTION__;	\
    static MinMaxRangeTableEntry<decltype(value)> _rangeTableEntry = { __VA_ARGS__ };	\
    ReturnOnError(_RangeCheckMinMax(Vi, _rangeTableEntry.Min(), _rangeTableEntry.Max(), value, _rangeTableEntry.Options(), _functionName, #value));	\
                                                                                }	\
                                                                                }

#define RangeCheckMinMaxMultiModel(Vi, value, ...)	\
                                                                                {	\
    if (RangeCheckEnabled(Vi))	\
                                                                                {	\
    static std::string _functionName = __FUNCTION__;	\
    static MinMaxRangeTableEntry<decltype(value)> _rangeTable[] = { __VA_ARGS__ };	\
    ReturnOnError(_RangeCheckMinMaxMultiModel(Vi, std::begin(_rangeTable), std::end(_rangeTable), value, _functionName, #value));	\
                                                                                }	\
                                                                                }

#define RangeCheckDiscrete(Vi, value, coercionStyle, ...)	\
                                                                                {	\
    if (RangeCheckEnabled(Vi))	\
                                                                                {	\
    static std::string _functionName = __FUNCTION__;	\
    static decltype(value) _allowedValues[] = { __VA_ARGS__ };	\
    ReturnOnError(_RangeCheckDiscrete(Vi, std::begin(_allowedValues), std::end(_allowedValues), value, coercionStyle, _functionName, #value));	\
                                                                                }	\
                                                                                }

#define RangeCheckDiscreteMultiModel(Vi, value, coercionStyle, ...)	\
                                                                                {	\
    if (RangeCheckEnabled(Vi))	\
                                                                                {	\
    static std::string _functionName = __FUNCTION__;	\
    static DiscreteRangeTableEntry<decltype(value)> _rangeTable[] = { __VA_ARGS__ };	\
    ReturnOnError(_RangeCheckDiscreteMultiModel(Vi, std::begin(_rangeTable), std::end(_rangeTable), value, coercionStyle, _functionName, #value));	\
                                                                                }	\
                                                                                }

enum class MinMaxOptions
{
    IncludeMinAndMax,
    ExcludeMin,
    ExcludeMax,
    ExcludeMinAndMax
};

enum class CoercionStyle
{
    None,
    Up,
    Down
};

template <typename T>
class MinMaxRangeTableEntry : public ModelBasedType < T >
{
public:
    MinMaxRangeTableEntry(T min, T max, MinMaxOptions options = MinMaxOptions::IncludeMinAndMax);
    MinMaxRangeTableEntry(const std::string& strModelList, T min, T max, MinMaxOptions options = MinMaxOptions::IncludeMinAndMax);

    T Min() const;
    T Max() const;

    MinMaxOptions Options() const;

private:
    T m_min;
    T m_max;
    MinMaxOptions m_options;
};

template <typename T>
class DiscreteRangeTableEntry : public ModelBasedType < T >
{
public:
    DiscreteRangeTableEntry(T allowedValue);

    // We use enable_if here to remove this constructor from overload resolution when the type is a string.
    // In that case, all paramters are strings, so we must require that the model always be passed as the 
    // first parameter. By removing this constructor from overload resolution, we force usage of the constructor 
    // that accepts the model as the first parameter.
    // 
    template <typename ...Args, typename = std::enable_if<!std::is_convertible<T, std::string>::value>::type>
    DiscreteRangeTableEntry(T allowedValue, Args... args);

    DiscreteRangeTableEntry(const std::string& strModelList, T allowedValue);

    template <typename ...Args>
    DiscreteRangeTableEntry(const std::string& strModelList, T allowedValue, Args... args);

    const std::vector<T>& AllowedValues() const;

private:
    void AppendAllowedValues(T allowedValue);

    template <typename ...Args>
    void AppendAllowedValues(T allowedValue, Args... args);

    std::vector<T> m_vecAllowedValues;
};


template <typename T>
ViStatus _RangeCheckMinMax(ViSession Vi, T minValue, T maxValue, T value, MinMaxOptions options, const std::string& strFunctionName, const std::string& strParameterName);

template <typename TIterator, typename TValue>
ViStatus _RangeCheckMinMaxMultiModel(ViSession Vi, TIterator itFirst, TIterator itLast, const TValue& value, const std::string& strFunctionName, const std::string& strParameterName);

template <typename TIterator>
ViStatus _RangeCheckDiscrete(ViSession Vi, TIterator itFirstAllowedValue, TIterator itLastAllowedValue, UnqualifiedElementType<TIterator>& value, CoercionStyle coercionStyle, const std::string& strFunctionName, const std::string& strParameterName);

template <typename TIterator, typename TValue>
ViStatus _RangeCheckDiscreteMultiModel(ViSession Vi, TIterator itFirst, TIterator itLast, TValue& value, CoercionStyle coercionStyle, const std::string& strFunctionName, const std::string& strParameterName);

template <typename TIterator>
ViStatus GetRangeTableEntryForModel(ViSession Vi, TIterator itFirst, TIterator itLast, const std::string& strModel, const std::string& strFunctionName, const std::string& strParameterName, const UnqualifiedElementType<TIterator>** ppEntry);

template <typename T>
static ViStatus ReportInvalidValueError(ViSession Vi, const T& value, const std::string& strFunctionName, const std::string& strParameterName);

template <typename T>
bool AreValuesEqual(const T& value1, const T& value2);

///////////////////////////////////////////////////////////////////////////////
// Coercion support
//
template <typename TIterator>
static void CoerceUp(ViSession Vi, TIterator itFirst, TIterator itLast, UnqualifiedElementType<TIterator>& value, const std::string& strFunctionName, const std::string& strParameterName);

template <typename TIterator>
static void CoerceDown(ViSession Vi, TIterator itFirst, TIterator itLast, UnqualifiedElementType<TIterator>& value, const std::string& strFunctionName, const std::string& strParameterName);

template <typename TIterator>
static bool IsOneOf(TIterator itFirst, TIterator itLast, const UnqualifiedElementType<TIterator>& value, const std::string& strFunctionName, const std::string& strParameterName);

///////////////////////////////////////////////////////////////////////////////
// State caching support
//
#define CACHE_COMPARE_EPSILON	10E-20	

template <typename T>
CacheEntry<T>& GetCacheEntry(ViSession Vi, ViAttr attributeId, const std::string& strQualifiedPhysicalName = std::string());

template <typename T>
struct CacheEntry
{
public:
    CacheEntry();
    void Invalidate();
    void SetValid();
    bool IsValid() const;
    T Value() const;
    void SetValue(const T& value);
    bool HasValue(const T& value) const;

private:
    bool m_bIsValid;
    T m_value;
};

class CacheManagerBase
{
protected:
    CacheManagerBase(ViSession Vi, ViAttr attributeId);

    bool Enabled() const;

protected:
    ViSession m_session;
    ViAttr m_attributeId;
    bool m_bEnabled;
};

// CacheManager general definition
//
template <typename T>
class CacheManager : public CacheManagerBase
{
protected:
    CacheManager(ViSession Vi, ViAttr attributeId, T& newValue);

protected:
    T& m_newValue;
};

// CacheManager specialization for ViChar[] attributes
//
template <>
class CacheManager<ViChar[]> : public CacheManagerBase
{
protected:
    CacheManager(ViSession Vi, ViAttr attributeId, ViChar newValue[]);

protected:
    ViChar* m_newValue;
};

// CacheManager specialization for ViConstString attributes
//
template <>
class CacheManager<ViConstString> : public CacheManagerBase
{
protected:
    CacheManager(ViSession Vi, ViAttr attributeId, ViConstString newValue);

protected:
    ViConstString m_newValue;
};

// GetterCacheManager general definition for attributes that are associated with a repcap
//
template <typename T, typename TRepCap = nullptr_t>
class GetterCacheManager : public CacheManager < T >
{
public:
    GetterCacheManager(ViSession Vi, const PhysicalName<TRepCap>& physicalName, ViAttr attributeId, T& newValue);
    virtual ~GetterCacheManager();

    bool GetCachedValue(T* pValue) const;

private:
    CacheEntry<T>* m_pEntry;
};

// GetterCacheManager general definition for attributes that are not associated with a repcap
//
template <typename T>
class GetterCacheManager<T, nullptr_t> : public CacheManager < T >
{
public:
    GetterCacheManager(ViSession Vi, ViAttr attributeId, T& newValue);
    virtual ~GetterCacheManager();

    bool GetCachedValue(T* pValue) const;

private:
    CacheEntry<T>* m_pEntry;
};

// GetterCacheManager specialization for ViChar[] attributes that are associated with a repcap
//
template <typename TRepCap>
class GetterCacheManager<ViChar[], TRepCap> : public CacheManager < ViChar[] >
{
public:
    GetterCacheManager(ViSession Vi, const PhysicalName<TRepCap>& physicalName, ViAttr attributeId, ViInt32 bufferSize, ViChar buffer[]);
    virtual ~GetterCacheManager();

    bool GetCachedValue(ViInt32 bufferSize, ViChar buffer[]) const;

private:
    CacheEntry<std::string>* m_pEntry;
};

// GetterCacheManager specialization for ViChar[] attributes that are not associated with a repcap
//
template <>
class GetterCacheManager<ViChar[], nullptr_t> : public CacheManager < ViChar[] >
{
public:
    GetterCacheManager(ViSession Vi, ViAttr attributeId, ViInt32 bufferSize, ViChar buffer[]);
    virtual ~GetterCacheManager();

    bool GetCachedValue(ViInt32 bufferSize, ViChar buffer[]) const;

private:
    CacheEntry<std::string>* m_pEntry;
};

// Don't allow specialization using std::string.  The ViChar[] specialization must be used instead.
//
template <>
class GetterCacheManager < std::string >;

// SetterCacheManager general definition for attributes that are associated with a repcap
//
template <typename T, typename TRepCap = nullptr_t>
class SetterCacheManager : public CacheManager < T >
{
public:
    SetterCacheManager(ViSession Vi, const PhysicalNameList<TRepCap>& physicalNames, ViAttr attributeId, T& newValue);
    virtual ~SetterCacheManager();

    const PhysicalNameList<TRepCap>& NonCachedPhysicalNames(ViSession Vi) const;

private:
    bool HasCachedValue(const PhysicalName<TRepCap>& physicalName) const;
    PhysicalNameList<TRepCap> m_nonCachedPhysicalNames;
};

// SetterCacheManager specialization for attributes that are not associated with a repcap
//
template <typename T>
class SetterCacheManager<T, nullptr_t> : public CacheManager < T >
{
public:
    SetterCacheManager(ViSession Vi, ViAttr attributeId, T& newValue);
    virtual ~SetterCacheManager();

    bool HasCachedValue() const;
};

// SetterCacheManager specialization for ViConstString attributes that are associated with a repcap
//
template <typename TRepCap>
class SetterCacheManager<ViConstString, TRepCap> : CacheManager < ViConstString >
{
public:
    SetterCacheManager(ViSession Vi, const PhysicalNameList<TRepCap>& physicalNames, ViAttr attributeId, ViConstString newValue);
    virtual ~SetterCacheManager();

    const PhysicalNameList<TRepCap>& NonCachedPhysicalNames(ViSession Vi) const;

private:
    bool HasCachedValue(const PhysicalName<TRepCap>& physicalName) const;

private:
    PhysicalNameList<TRepCap> m_nonCachedPhysicalNames;
};

// SetterCacheManager specialization for ViConstString attributes that are not associated with a repcap
//
template <>
class SetterCacheManager<ViConstString, nullptr_t> : CacheManager < ViConstString >
{
public:
    SetterCacheManager(ViSession Vi, ViAttr attributeId, ViConstString newValue);
    virtual ~SetterCacheManager();

    bool HasCachedValue() const;
};

// Don't allow specialization using std::string.  The ViConstString specialization must be used instead.
//
template <typename TRepCap>
class SetterCacheManager < std::string, TRepCap >;

// Coupled attributes
//
template <typename... Args>
void InvalidateAttributes(ViSession Vi, ViAttr attributeId, Args... args);

template <typename TRepCap, typename... Args>
void InvalidateAttributes(ViSession Vi, const PhysicalNameList<TRepCap>& physicalNames, ViAttr attributeId, Args... args);

///////////////////////////////////////////////////////////////////////////////
// Simulation support
//
#define GetValueForSimulation(Vi, pValueOut, ...)	\
                                                                                {	\
    SimulationTableEntry<RemovePointer<decltype(pValueOut)>> _defaultValues[] = { __VA_ARGS__ };	\
    _GetValueForSimulation(Vi, std::begin(_defaultValues), std::end(_defaultValues), pValueOut);	\
                                                                                }

#define GetStringValueForSimulation(Vi, bufferSize, buffer, ...)	\
                                                                                {	\
    SimulationTableEntry<char*> _defaultValues[] = { __VA_ARGS__ };	\
    _GetValueForSimulation(Vi, std::begin(_defaultValues), std::end(_defaultValues), bufferSize, buffer);	\
                                                                                }

template <typename T>
struct SimulationTableEntry : public ModelBasedType < T >
{
    SimulationTableEntry(const T& defaultValue);
    SimulationTableEntry(const std::string& strModelList, const T& defaultValue);

    const T& DefaultValue;
};

template <typename TIterator, typename TValue>
void _GetValueForSimulation(ViSession Vi, TIterator itFirst, TIterator itLast, TValue* pValue);

template <typename TIterator>
void _GetStringValueForSimulation(ViSession Vi, TIterator itFirst, TIterator itLast, ViInt32 bufferSize, ViChar buffer[]);

///////////////////////////////////////////////////////////////////////////////
// Utility functions
//
template <typename TSession = DriverSession>
ViStatus GetDriverSession(ViSession Vi, TSession** pSession);

template <typename TSession = DriverSession>
TSession* GetDriverSession(ViSession Vi);

///////////////////////////////////////////////////////////////////////////////
// Inherent capabilities
//
template <typename TSession>
ViStatus InitWithOptions(ViRsrc ResourceName, ViBoolean IdQuery, ViBoolean Reset, ViConstString OptionsString, ViSession* Vi);
ViStatus close(ViSession handle);
ViStatus revision_query(ViSession Vi, ViChar DriverRev[], ViChar InstrRev[]);
ViStatus error_message(ViSession Vi, ViStatus ErrorCode, ViChar ErrorMessage[]);
ViStatus GetError(ViSession Vi, ViStatus* ErrorCode, ViInt32 ErrorDescriptionBufferSize, ViChar ErrorDescription[]);
ViStatus ClearError(ViSession Vi);
ViStatus ClearInterchangeWarnings(ViSession Vi);
ViStatus GetNextCoercionRecord(ViSession Vi, ViInt32 CoercionRecordBufferSize, ViChar CoercionRecord[]);
ViStatus GetNextInterchangeWarning(ViSession Vi, ViInt32 InterchangeWarningBufferSize, ViChar InterchangeWarning[]);
ViStatus InvalidateAllAttributes(ViSession Vi);
ViStatus ResetInterchangeCheck(ViSession Vi);
ViStatus Disable(ViSession Vi);
ViStatus error_query(ViSession Vi, ViInt32* ErrorCode, ViChar ErrorMessage[]);
ViStatus LockSession(ViSession Vi, ViBoolean* CallerHasLock);
ViStatus reset(ViSession Vi);
ViStatus ResetWithDefaults(ViSession Vi);
ViStatus self_test(ViSession Vi, ViInt16* TestResult, ViChar TestMessage[]);
ViStatus UnlockSession(ViSession Vi, ViBoolean* CallerHasLock);

template <typename T>
ViStatus GetAttribute(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, T* AttributeValue);
ViStatus GetAttributeViString(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViInt32 AttributeValueBufferSize, ViChar AttributeValue[]);

template <typename T>
ViStatus SetAttribute(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, T AttributeValue);

ViStatus get_SPECIFIC_DRIVER_DESCRIPTION(ViSession Vi, ViConstString RepCapIdentifier, ViInt32 AttributeValueBufferSize, ViChar AttributeValue[]);
ViStatus get_SPECIFIC_DRIVER_PREFIX(ViSession Vi, ViConstString RepCapIdentifier, ViInt32 AttributeValueBufferSize, ViChar AttributeValue[]);
ViStatus get_SPECIFIC_DRIVER_VENDOR(ViSession Vi, ViConstString RepCapIdentifier, ViInt32 AttributeValueBufferSize, ViChar AttributeValue[]);
ViStatus get_SPECIFIC_DRIVER_REVISION(ViSession Vi, ViConstString RepCapIdentifier, ViInt32 AttributeValueBufferSize, ViChar AttributeValue[]);
ViStatus get_SPECIFIC_DRIVER_CLASS_SPEC_MAJOR_VERSION(ViSession Vi, ViConstString RepCapIdentifier, ViInt32* AttributeValue);
ViStatus get_SPECIFIC_DRIVER_CLASS_SPEC_MINOR_VERSION(ViSession Vi, ViConstString RepCapIdentifier, ViInt32* AttributeValue);
ViStatus get_RANGE_CHECK(ViSession Vi, ViConstString RepCapIdentifier, ViBoolean* AttributeValue);
ViStatus set_RANGE_CHECK(ViSession Vi, ViConstString RepCapIdentifier, ViBoolean AttributeValue);
ViStatus get_QUERY_INSTRUMENT_STATUS(ViSession Vi, ViConstString RepCapIdentifier, ViBoolean* AttributeValue);
ViStatus set_QUERY_INSTRUMENT_STATUS(ViSession Vi, ViConstString RepCapIdentifier, ViBoolean AttributeValue);
ViStatus get_CACHE(ViSession Vi, ViConstString RepCapIdentifier, ViBoolean* AttributeValue);
ViStatus set_CACHE(ViSession Vi, ViConstString RepCapIdentifier, ViBoolean AttributeValue);
ViStatus get_SIMULATE(ViSession Vi, ViConstString RepCapIdentifier, ViBoolean* AttributeValue);
ViStatus set_SIMULATE(ViSession Vi, ViConstString RepCapIdentifier, ViBoolean AttributeValue);
ViStatus get_RECORD_COERCIONS(ViSession Vi, ViConstString RepCapIdentifier, ViBoolean* AttributeValue);
ViStatus set_RECORD_COERCIONS(ViSession Vi, ViConstString RepCapIdentifier, ViBoolean AttributeValue);
ViStatus get_INTERCHANGE_CHECK(ViSession Vi, ViConstString RepCapIdentifier, ViBoolean* AttributeValue);
ViStatus set_INTERCHANGE_CHECK(ViSession Vi, ViConstString RepCapIdentifier, ViBoolean AttributeValue);
ViStatus get_LOGICAL_NAME(ViSession Vi, ViConstString RepCapIdentifier, ViInt32 AttributeValueBufferSize, ViChar AttributeValue[]);
ViStatus get_IO_RESOURCE_DESCRIPTOR(ViSession Vi, ViConstString RepCapIdentifier, ViInt32 AttributeValueBufferSize, ViChar AttributeValue[]);
ViStatus get_DRIVER_SETUP(ViSession Vi, ViConstString RepCapIdentifier, ViInt32 AttributeValueBufferSize, ViChar AttributeValue[]);
ViStatus get_GROUP_CAPABILITIES(ViSession Vi, ViConstString RepCapIdentifier, ViInt32 AttributeValueBufferSize, ViChar AttributeValue[]);
ViStatus get_SUPPORTED_INSTRUMENT_MODELS(ViSession Vi, ViConstString RepCapIdentifier, ViInt32 AttributeValueBufferSize, ViChar AttributeValue[]);
ViStatus get_INSTRUMENT_FIRMWARE_REVISION(ViSession Vi, ViConstString RepCapIdentifier, ViInt32 AttributeValueBufferSize, ViChar AttributeValue[]);
ViStatus get_INSTRUMENT_MANUFACTURER(ViSession Vi, ViConstString RepCapIdentifier, ViInt32 AttributeValueBufferSize, ViChar AttributeValue[]);
ViStatus get_INSTRUMENT_MODEL(ViSession Vi, ViConstString RepCapIdentifier, ViInt32 AttributeValueBufferSize, ViChar AttributeValue[]);

///////////////////////////////////////////////////////////////////////////////
// Instrument Error And Completion Codes
//
#ifndef _IVIC_ERROR_BASE_DEFINES_
#define _IVIC_ERROR_BASE_DEFINES_

#define IVIC_WARN_BASE                           (0x3FFA0000L)
#define IVIC_CROSS_CLASS_WARN_BASE               (IVIC_WARN_BASE + 0x1000)
#define IVIC_CLASS_WARN_BASE                     (IVIC_WARN_BASE + 0x2000)
#define IVIC_SPECIFIC_WARN_BASE                  (IVIC_WARN_BASE + 0x4000)

#define IVIC_ERROR_BASE                          (0xBFFA0000L)
#define IVIC_CROSS_CLASS_ERROR_BASE              (IVIC_ERROR_BASE + 0x1000)
#define IVIC_CLASS_ERROR_BASE                    (IVIC_ERROR_BASE + 0x2000)
#define IVIC_SPECIFIC_ERROR_BASE                 (IVIC_ERROR_BASE + 0x4000)
#define IVIC_LXISYNC_ERROR_BASE                  (IVIC_ERROR_BASE + 0x2000)

#define IVIC_ERROR_INVALID_ATTRIBUTE             (IVIC_ERROR_BASE + 0x000C)
#define IVIC_ERROR_TYPES_DO_NOT_MATCH            (IVIC_ERROR_BASE + 0x0015)
#define IVIC_ERROR_IVI_ATTR_NOT_WRITABLE         (IVIC_ERROR_BASE + 0x000D)
#define IVIC_ERROR_IVI_ATTR_NOT_READABLE         (IVIC_ERROR_BASE + 0x000E)
#define IVIC_ERROR_INVALID_SESSION_HANDLE        (IVIC_ERROR_BASE + 0x1190)

#endif

#define IVIC_ERROR_CANNOT_RECOVER                           (IVIC_ERROR_BASE + 0x0000)
#define IVIC_ERROR_INSTRUMENT_STATUS                        (IVIC_ERROR_BASE + 0x0001)
#define IVIC_ERROR_CANNOT_OPEN_FILE                         (IVIC_ERROR_BASE + 0x0002)
#define IVIC_ERROR_READING_FILE                             (IVIC_ERROR_BASE + 0x0003)
#define IVIC_ERROR_WRITING_FILE                             (IVIC_ERROR_BASE + 0x0004)
#define IVIC_ERROR_INVALID_PATHNAME                         (IVIC_ERROR_BASE + 0x000B)
#define IVIC_ERROR_INVALID_VALUE                            (IVIC_ERROR_BASE + 0x0010)
#define IVIC_ERROR_FUNCTION_NOT_SUPPORTED                   (IVIC_ERROR_BASE + 0x0011)
#define IVIC_ERROR_ATTRIBUTE_NOT_SUPPORTED                  (IVIC_ERROR_BASE + 0x0012)
#define IVIC_ERROR_VALUE_NOT_SUPPORTED                      (IVIC_ERROR_BASE + 0x0013)
#define IVIC_ERROR_NOT_INITIALIZED                          (IVIC_ERROR_BASE + 0x001D)
#define IVIC_ERROR_UNKNOWN_CHANNEL_NAME                     (IVIC_ERROR_BASE + 0x0020)
#define IVIC_ERROR_TOO_MANY_OPEN_FILES                      (IVIC_ERROR_BASE + 0x0023)
#define IVIC_ERROR_CHANNEL_NAME_REQUIRED                    (IVIC_ERROR_BASE + 0x0044)
#define IVIC_ERROR_MISSING_OPTION_NAME                      (IVIC_ERROR_BASE + 0x0049)
#define IVIC_ERROR_MISSING_OPTION_VALUE                     (IVIC_ERROR_BASE + 0x004A)
#define IVIC_ERROR_BAD_OPTION_NAME                          (IVIC_ERROR_BASE + 0x004B)
#define IVIC_ERROR_BAD_OPTION_VALUE                         (IVIC_ERROR_BASE + 0x004C)
#define IVIC_ERROR_OUT_OF_MEMORY                            (IVIC_ERROR_BASE + 0x0056)
#define IVIC_ERROR_OPERATION_PENDING                        (IVIC_ERROR_BASE + 0x0057)
#define IVIC_ERROR_NULL_POINTER                             (IVIC_ERROR_BASE + 0x0058)
#define IVIC_ERROR_UNEXPECTED_RESPONSE                      (IVIC_ERROR_BASE + 0x0059)
#define IVIC_ERROR_FILE_NOT_FOUND                           (IVIC_ERROR_BASE + 0x005B)
#define IVIC_ERROR_INVALID_FILE_FORMAT                      (IVIC_ERROR_BASE + 0x005C)
#define IVIC_ERROR_STATUS_NOT_AVAILABLE                     (IVIC_ERROR_BASE + 0x005D)
#define IVIC_ERROR_ID_QUERY_FAILED                          (IVIC_ERROR_BASE + 0x005E)
#define IVIC_ERROR_RESET_FAILED                             (IVIC_ERROR_BASE + 0x005F)
#define IVIC_ERROR_RESOURCE_UNKNOWN                         (IVIC_ERROR_BASE + 0x0060)
#define IVIC_ERROR_ALREADY_INITIALIZED                      (IVIC_ERROR_BASE + 0x0061)
#define IVIC_ERROR_CANNOT_CHANGE_SIMULATION_STATE           (IVIC_ERROR_BASE + 0x0062)
#define IVIC_ERROR_INVALID_NUMBER_OF_LEVELS_IN_SELECTOR     (IVIC_ERROR_BASE + 0x0063)
#define IVIC_ERROR_INVALID_RANGE_IN_SELECTOR                (IVIC_ERROR_BASE + 0x0064)
#define IVIC_ERROR_UNKOWN_NAME_IN_SELECTOR                  (IVIC_ERROR_BASE + 0x0065)
#define IVIC_ERROR_BADLY_FORMED_SELECTOR                    (IVIC_ERROR_BASE + 0x0066)
#define IVIC_ERROR_UNKNOWN_PHYSICAL_IDENTIFIER              (IVIC_ERROR_BASE + 0x0067)

#define IVIC_SUCCESS                                        0
#define IVIC_WARN_NSUP_ID_QUERY                             (IVIC_WARN_BASE + 0x0065)
#define IVIC_WARN_NSUP_RESET                                (IVIC_WARN_BASE + 0x0066)
#define IVIC_WARN_NSUP_SELF_TEST                            (IVIC_WARN_BASE + 0x0067)
#define IVIC_WARN_NSUP_ERROR_QUERY                          (IVIC_WARN_BASE + 0x0068)
#define IVIC_WARN_NSUP_REV_QUERY                            (IVIC_WARN_BASE + 0x0069)

#define IVIC_ERROR_CHANNEL_NOT_ENABLED                      (IVIC_CLASS_ERROR_BASE + 0x0001)
#define IVIC_ERROR_UNABLE_TO_PERFORM_MEASUREMENT            (IVIC_CLASS_ERROR_BASE + 0x0002)
#define IVIC_ERROR_MAX_TIME_EXCEEDED                        (IVIC_CLASS_ERROR_BASE + 0x0003)
#define IVIC_ERROR_INVALID_ACQ_TYPE                         (IVIC_CLASS_ERROR_BASE + 0x0004)

#define IVIC_WARN_INVALID_WFM_ELEMENT                       (IVIC_CLASS_WARN_BASE + 0x0001)

    ///////////////////////////////////////////////////////////////////////////////
    // Internal utility macros
    //
#define CheckError(status) \
    { auto _status_ = (status); if (_status_ < 0) goto LExit; }

#define CheckConfigServerError(status) \
    { auto _status_ = (status); if (status < 0) { ReportConfigServerError(status); goto LExit; } }

#define DisposeConfigServerHandle(h) \
    if (h != VI_NULL) { ViStatus s = IviConfig_DisposeHandle(h); assert(s >= 0); h = VI_NULL; }

#define MAX_CONFIG_STORE_STRING	1024

#define InsideAttributeGetter()	\
    FunctionIsAttributeGetter(__FUNCTION__)

inline bool IsAttributeGetterName(const char* pszFunctionName)
{
    return (std::string(pszFunctionName).compare(0, nrt::g_driverInfo.Prefix.length() + std::string("_get_").length(), nrt::g_driverInfo.Prefix + "_get_") == 0);
}

inline bool FunctionIsAttributeGetter(const char* pszFunctionName)
{
    // NOTE: Do not call this function from anywhere other than the InsideAttributeGetter macro, because the 
    // result is stored as a a static variable, and, hence, will only be evaluated once, for perf reasons.  
    // Instead, use the IsAttributeGetterName function above.
    //
    static const bool isGetter = IsAttributeGetterName(pszFunctionName);

    return isGetter;
}

#define InsideAttributeSetter()	\
    FunctionIsAttributeSetter(__FUNCTION__)

inline bool IsAttributeSetterName(const char* pszFunctionName)
{
    return (std::string(pszFunctionName).compare(0, nrt::g_driverInfo.Prefix.length() + std::string("_set_").length(), nrt::g_driverInfo.Prefix + "_set_") == 0);
}

inline bool FunctionIsAttributeSetter(const char* pszFunctionName)
{
    // NOTE: Do not call this function from anywhere other than the InsideAttributeSetter macro, because the 
    // result is stored as a a static variable, and, hence, will only be evaluated once, for perf reasons.  
    // Instead, use the IsAttributeSetterName function above.
    //
    static const bool isSetter = (std::string(pszFunctionName).compare(0, nrt::g_driverInfo.Prefix.length() + std::string("_set_").length(), nrt::g_driverInfo.Prefix + "_set_") == 0);

    return isSetter;
}

inline std::string GetAttributeNameFromGetterOrSetterName(const std::string& strFunctionName)
{
    auto attributePrefixLength = g_driverInfo.Prefix.length() + 5 /* length of "_get_" or "_set_" */;
    std::string strAttributeName = strFunctionName;
    assert(strAttributeName.length() > attributePrefixLength);

    if (strAttributeName.length() > attributePrefixLength)
    {
        strAttributeName = strAttributeName.substr(attributePrefixLength);
    }

    return strAttributeName;
}

///////////////////////////////////////////////////////////////////////////////
// Utility functions
//
inline std::vector<std::string> Split(const std::string& str, char cDelimiter, bool bTrimWhitespace)
{
    std::vector<std::string> vecElements;
    Split(str, cDelimiter, bTrimWhitespace, vecElements);

    return vecElements;
}

inline std::vector<std::string>& Split(const std::string &str, char cDelimiter, bool bTrimWhitespace, std::vector<std::string> &vecElements)
{
    std::stringstream sstream(str);
    std::string strItem;

    while (std::getline(sstream, strItem, cDelimiter))
    {
        if (bTrimWhitespace)
        {
            strItem = TrimWhitespace(strItem);
        }

        vecElements.push_back(strItem);
    }

    return vecElements;
}

inline std::string Trim(const std::string& str, const std::string& strToTrim)
{
    const auto strBegin = str.find_first_not_of(strToTrim);

    if (strBegin == std::string::npos)
    {
        // No content
        //
        return "";
    }

    const auto strEnd = str.find_last_not_of(strToTrim);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

inline std::string TrimWhitespace(const std::string& str, const std::string& strWhitespace)
{
    return Trim(str, strWhitespace);
}

inline std::string RemoveWhitespace(const std::string str)
{
    auto strCopy = str;
    strCopy.erase(std::remove_if(std::begin(strCopy), std::end(strCopy), ::isspace), std::end(strCopy));

    return strCopy;
}

inline bool IsWhitespace(const std::string& str)
{
    static const std::string strWhitespaces(" \t\f\v\n\r");

    return str.find_first_not_of(strWhitespaces) == std::string::npos;
}

inline int IndexOfNull(int nIndex)
{
    return -1;
}

template <typename T, typename ...Args>
inline int IndexOfNull(int nIndex, T arg, Args... args)
{
    if (arg == nullptr)
    {
        return nIndex;
    }
    else
    {
        return IndexOfNull(++nIndex, args...);
    }
}

template <typename ...Args>
inline int IndexOfNull(Args... args)
{
    return IndexOfNull(0, args...);
}

///////////////////////////////////////////////////////////////////////////////
// Validation functions
//
template <typename ...Args>
inline ViStatus CheckForNullPointers(ViSession Vi, char* pszFunctionName, char* pszParamNames, Args... args)
{
    auto status = VI_SUCCESS;

    auto nIndex = IndexOfNull(args...);

    if (nIndex >= 0)
    {
        auto vecNames = Split(pszParamNames, ',');
        assert(nIndex < (int)vecNames.size());

        auto strParamName = (nIndex < (int)vecNames.size()) ? vecNames[nIndex] : "<unknown parameter>";
        status = ReportError(Vi, IVIC_ERROR_NULL_POINTER, TrimWhitespace(pszFunctionName).c_str(), strParamName.c_str());
    }

    return status;
}

inline ViStatus ValidateDriverSession(ViSession Vi)
{
    auto status = VI_SUCCESS;

    DriverSession* pSession = nullptr;
    status = GetDriverSession(Vi, &pSession);

    if (status < 0)
    {
        status = IVIC_ERROR_INVALID_SESSION_HANDLE;
    }

    return status;
}

inline ViStatus _CheckForUnsupportedModel(ViSession Vi, const std::vector<std::string>& vecUnsupportedModels, const std::string& strFunctionName, bool bIsAttribute)
{
    auto status = VI_SUCCESS;

    assert(!vecUnsupportedModels.empty());

    if (!vecUnsupportedModels.empty())
    {
        auto strModel = InstrumentModel(Vi);

        auto it = std::find_if(std::begin(vecUnsupportedModels), std::end(vecUnsupportedModels), [&](const std::string& strModelOrFamily)
        {
            return strModelOrFamily == strModel || InstrumentInFamily(Vi, strModelOrFamily);
        });

        if (it != std::end(vecUnsupportedModels))
        {
            if (bIsAttribute)
            {
                auto strAttributeName = GetAttributeNameFromGetterOrSetterName(strFunctionName);

                status = ReportErrorEx(Vi, IVIC_ERROR_ATTRIBUTE_NOT_SUPPORTED, "Attribute is not supported for instrument model '%s'", strAttributeName.c_str(), strModel.c_str());
            }
            else
            {
                status = ReportErrorEx(Vi, IVIC_ERROR_FUNCTION_NOT_SUPPORTED, "Function is not supported for instrument model '%s'", strFunctionName.c_str(), strModel.c_str());
            }
        }
    }

    return status;
}

///////////////////////////////////////////////////////////////////////////////
// VisaSession
//
#ifndef NRT_NO_VISA
template <typename TSession>
inline VisaSession<TSession>::VisaSession()
    : m_visaResourceManager(VI_NULL), m_visaSession(VI_NULL)
{
}

template <typename TSession>
inline ViStatus VisaSession<TSession>::InitializeIO()
{
    auto status = VI_SUCCESS;

    TSession* pSession = static_cast<TSession*>(this);

    if (!pSession->SimulationEnabled())
    {
        status = viOpenDefaultRM(&m_visaResourceManager);
        ReturnOnError(status);

        status = viOpen(m_visaResourceManager, (ViRsrc)pSession->IoDescriptor().c_str(), VI_NO_LOCK, pSession->VisaOpenTimeout(), &m_visaSession);
        ReturnOnError(status);
    }

    return status;
}

template <typename TSession>
inline ViStatus VisaSession<TSession>::CloseIO()
{
    auto status = VI_SUCCESS;

    if (!static_cast<TSession*>(this)->SimulationEnabled() && m_visaResourceManager != VI_NULL)
    {
        // Closing the resource manager will close all sessions at the same time
        //
        status = viClose(m_visaResourceManager);
        ReturnOnError(status);

        m_visaResourceManager = VI_NULL;
        m_visaSession = VI_NULL;
    }

    return status;
}

template <typename TSession>
inline ViStatus VisaSession<TSession>::ClearIOStatus()
{
    auto status = VI_SUCCESS;

    if (!static_cast<TSession*>(this)->SimulationEnabled())
    {
        status = viPrintf(m_visaSession, "*CLS\n");
        ReturnOnError(status);

        status = PollInstrumentErrors();
        ReturnOnError(status);
    }

    return status;
}

template <typename TSession>
inline ViStatus VisaSession<TSession>::GetIdentificationInfo(std::string& strManufacturer, std::string& strModel, std::string& strSerialNumber, std::string& strFirmwareRevision)
{
    auto status = VI_SUCCESS;

    if (!static_cast<TSession*>(this)->SimulationEnabled())
    {
        ViChar szManufacturer[256], szModel[256], szSerialNumber[256], szFirmwareVersion[256];
        status = viQueryf(m_visaSession, "*IDN?\n", "%256[^,],%256[^,],%256[^,],%256[^,]%*T", szManufacturer, szModel, szSerialNumber, szFirmwareVersion);
        ReturnOnError(status);

        strManufacturer = szManufacturer;
        strModel = szModel;
        strSerialNumber = szSerialNumber;
        strFirmwareRevision = szFirmwareVersion;

        status = PollInstrumentErrors();
        ReturnOnError(status);
    }

    return status;
}

template <typename TSession>
inline ViStatus VisaSession<TSession>::PollInstrumentErrors()
{
    auto status = VI_SUCCESS;

    TSession* pSession = static_cast<TSession*>(this);

	if (pSession->QueryInstrStatusEnabled() && !pSession->SimulationEnabled())
	{
        long lValue;
        status = viQueryf(m_visaSession, "*ESR?\n", "%ld%*T", &lValue);
        ReturnOnError(status);

        if ((lValue & 4) != 0 || (lValue & 8) != 0 || (lValue & 16) != 0 || (lValue & 32) != 0)
        {
            status = pSession->ReportError(IVIC_ERROR_INSTRUMENT_STATUS);
        }
    }

    return status;
}

template <typename TSession>
inline ViSession VisaSession<TSession>::GetVisaResourceManager() const
{
    return m_visaResourceManager;
}

template <typename TSession>
inline ViSession VisaSession<TSession>::GetVisaSession() const
{
    return m_visaSession;
}

#endif	// NRT_NO_VISA

///////////////////////////////////////////////////////////////////////////////
// VisaTimeoutManager
//
#ifndef NRT_NO_VISA

inline VisaTimeoutManager::VisaTimeoutManager(ViSession visaSession, const long lTimeout)
    : m_lPrevTimeout(CURRENT_TIMEOUT), m_visaSession(visaSession)
{
    if (lTimeout > CURRENT_TIMEOUT)
    {
        // User specified a desired timeout or an infinite timeout.
        //
        unsigned long ulPrevTimeout;
        auto status = viGetAttribute(visaSession, VI_ATTR_TMO_VALUE, &ulPrevTimeout);
        assert(status >= 0);

        if (status >= 0)
        {
            m_lPrevTimeout = (long)ulPrevTimeout;
            status = viSetAttribute(visaSession, VI_ATTR_TMO_VALUE, lTimeout);
            assert(status >= 0);
        }
    }
}

inline VisaTimeoutManager::~VisaTimeoutManager()
{
    // If necessary, restore the timeout
    //
    if (m_lPrevTimeout != CURRENT_TIMEOUT)
    {
        // A new timeout was specified, so restore
        //
        auto status = viSetAttribute(m_visaSession, VI_ATTR_TMO_VALUE, m_lPrevTimeout);
        assert(status >= 0);
    }
}

#endif	// NRT_NO_VISA

///////////////////////////////////////////////////////////////////////////////
// DriverSession
//
inline DriverSession::DriverSession(ViSession handle,
    unsigned long ulVisaOpenTimeout,
    unsigned long ulSelfTestTimeout,
    unsigned long ulResetTimeout,
    bool bInterchangeCheckSupported,
    unsigned long ulCoercionLogSize)
    : m_handle(handle),
    m_ulVisaOpenTimeout(ulVisaOpenTimeout),
    m_ulSelfTestTimeout(ulSelfTestTimeout),
    m_ulResetTimeout(ulResetTimeout),
    m_bInterchangeCheckSupported(bInterchangeCheckSupported),
    m_ulCoercionLogSize(ulCoercionLogSize)
{
}

template <typename TSession>
inline ViStatus DriverSession::Initialize(const std::string& strResourceName, bool bIdQuery, bool bReset, const std::string& strOptions)
{
    static_assert(std::is_base_of<DriverSession, TSession>::value, "Session class must derive from DriverSession.");

    auto status = VI_SUCCESS;

    m_strResourceName = strResourceName;
    m_bIdQuery = bIdQuery;
    m_bReset = bReset;
    m_strInitOptions = strOptions;

    status = LoadConfiguration(strResourceName, strOptions);
    ReturnOnError(status);

    if (InterchangeCheckEnabled() && !InterchangeCheckSupported())
    {
        // The user has turned on interchangeability checking, but the driver has indicated that it's not supported
        //
        status = ReportErrorEx(IVIC_ERROR_BAD_OPTION_VALUE, "Interchange checking is not supported by the driver.", "True");
        ReturnOnError(status);
    }

    status = InitializeIO();
    ReturnOnError(status);

    // If we get this far, we have to take care to clean up the I/O session if any subsequent call fails
    //
    auto bIOInitialized = true;

    if (QueryInstrStatusEnabled())
    {
        // Clear out any I/O errors to allow the user to initialize the driver, even if the instrument is in a bad state
        //
        status = ClearIOStatus();
    }

    if (status >= 0)
    {
        status = GetIdentificationInfo(m_strManufacturer, m_strModel, m_strSerialNumber, m_strFirmwareRevision);

        if (status >= 0)
        {
            if (bIdQuery && !InstrumentSupported())
            {
                auto strErr = "Unrecognized model: " + InstrumentModel();
                status = ReportError(IVIC_ERROR_ID_QUERY_FAILED, strErr.c_str());
            }
        }
    }

    if (status < 0)
    {
        // Note that we don't overwrite the status variable, because we want to preserve the original failure
        // 
        auto statusClose = CloseIO();
        assert(statusClose >= 0);
    }

    return status;
}

inline ViStatus DriverSession::Close()
{
    auto status = VI_SUCCESS;

    status = CloseIO();
    ReturnOnError(status);

    return status;
}

inline ViStatus DriverSession::LoadConfiguration(const std::string& strResourceName, const std::string& strOptions)
{
    auto status = VI_SUCCESS;

    m_strLogicalName.clear();
    m_strIoDescriptor.clear();
    m_mapInherentOptions.clear();
    m_mapDriverSetupOptions.clear();
    m_mapConfigSettingsInt32.clear();
    m_mapConfigSettingsBoolean.clear();
    m_mapConfigSettingsReal64.clear();
    m_mapConfigSettingsString.clear();
    m_mapPhysicalNameToVirtualName.clear();
    m_mapVirtualNameToPhysicalName.clear();

    m_bCache = true;				// IVI-defined default value
    m_bInterchangeCheck = false;	// IVI-defined default value
    m_bQueryInstrStatus = false;	// IVI-defined default value
    m_bRangeCheck = true;			// IVI-defined default value
    m_bRecordCoercions = false;		// IVI-defined default value
    m_bSimulate = false;			// IVI-defined default value

    IviConfigStoreHandle hConfigStore = VI_NULL;
    IviDriverSessionHandle hDriverSession = VI_NULL;
    IviSoftwareModuleHandle hSoftwareModule = VI_NULL;
    IviSoftwareModuleCollectionHandle hSoftwareModuleCollection = VI_NULL;

    status = IviConfig_Initialize(&hConfigStore);
    CheckConfigServerError(status);

    // Try loading from the process default location, if it has been set.  Otherwise, load from the master location.
    //
    ViChar szLocation[MAX_PATH];
    status = IviConfig_GetConfigStorePropertyViString(hConfigStore, IVICONFIG_VAL_CONFIG_STORE_PROC_DEFAULT_LOCATION, _countof(szLocation), szLocation);
    CheckConfigServerError(status);

    if (strlen(szLocation) == 0)
    {
        status = IviConfig_GetConfigStorePropertyViString(hConfigStore, IVICONFIG_VAL_CONFIG_STORE_MASTER_LOCATION, _countof(szLocation), szLocation);
        CheckConfigServerError(status);
    }

    status = IviConfig_Deserialize(hConfigStore, szLocation);
    CheckConfigServerError(status);

    status = IviConfig_GetDriverSession(hConfigStore, strResourceName.c_str(), &hDriverSession);

    if (status >= 0)
    {
        // Resource name is either a logical name or a driver session name.  In either case, the handle we now have points to the driver session.
        //
        m_strLogicalName = strResourceName;
        status = LoadDriverSessionConfiguration(hDriverSession);
        CheckError(status);

        status = LoadConfigurableInitialSettings(hDriverSession);
        CheckError(status);

        status = IviConfig_GetSessionSoftwareModuleReference(hDriverSession, &hSoftwareModule);
        CheckConfigServerError(status);
    }
    else if (status == IVICONFIG_ERROR_SESSION_NOT_FOUND)
    {
        // Resource name is not a logical name or driver session, so load the config settings from the software module
        //
        status = IviConfig_ClearError();
        CheckConfigServerError(status);

        // We must assume that the resource name specified is the I/O descriptor.  If not, and we're in live mode, then InitializeIO will, of course, fail.
        //
        m_strIoDescriptor = strResourceName;

        status = IviConfig_GetConfigStoreSoftwareModuleCollection(hConfigStore, &hSoftwareModuleCollection);
        CheckConfigServerError(status);

        status = IviConfig_GetSoftwareModuleItemByName(hSoftwareModuleCollection, g_driverInfo.Prefix.c_str(), &hSoftwareModule);
        CheckConfigServerError(status);
    }
    else
    {
        CheckConfigServerError(status);
    }

    status = LoadConfigurableInitialSettings((hDriverSession != VI_NULL) ? hDriverSession : hSoftwareModule);
    CheckError(status);

    // Values in the init option string override any found in the config store.
    //
    status = ProcessInitOptions(strOptions);
    CheckError(status);

    if (hSoftwareModule != VI_NULL)
    {
        // Physical names are always associated with the software module, so load from there.
        //
        status = LoadPhysicalNames(hSoftwareModule);
        CheckError(status);
    }

    if (SimulationEnabled() && m_strModel.empty())
    {
        // Set the default model since we didn't pick it up from the software module or driver session
        //
        m_strModel = g_driverInfo.DefaultSimulatedModel;
    }

    // Remember the original values of these options so that they can be restored if ResetWithDefaults is called
    //
    m_bCacheOriginal = m_bCache;
    m_bInterchangeCheckOriginal = m_bInterchangeCheck;
    m_bQueryInstrStatusOriginal = m_bQueryInstrStatus;
    m_bRangeCheckOriginal = m_bRangeCheck;
    m_bRecordCoercionsOriginal = m_bRecordCoercions;
    m_bSimulateOriginal = m_bSimulate;

LExit:
    DisposeConfigServerHandle(hDriverSession);
    DisposeConfigServerHandle(hSoftwareModuleCollection);
    DisposeConfigServerHandle(hSoftwareModule);

    auto statusClose = IviConfig_Close(hConfigStore);
    status = (status < 0) ? status : statusClose;

    return status;
}

inline ViStatus DriverSession::LoadDriverSessionConfiguration(IviDriverSessionHandle hDriverSession)
{
    auto status = VI_SUCCESS;

    IviHardwareAssetHandle hHardware = VI_NULL;

    status = LoadVirtualNames(hDriverSession);
    CheckError(status);

    status = IviConfig_GetSessionHardwareAssetReference(hDriverSession, &hHardware);
    CheckConfigServerError(status);

    if (hHardware != VI_NULL)
    {
        ViChar szIoDescriptor[MAX_CONFIG_STORE_STRING];
        status = IviConfig_GetHardwareAssetPropertyViString(hHardware, IVICONFIG_VAL_HARDWARE_ASSET_IO_DESCRIPTOR, _countof(szIoDescriptor), szIoDescriptor);
        CheckConfigServerError(status);

        m_strIoDescriptor = szIoDescriptor;
    }

    ViBoolean bCache;
    status = IviConfig_GetDriverSessionPropertyViBoolean(hDriverSession, IVICONFIG_VAL_DRIVER_SESSION_CACHE, &bCache);
    CheckConfigServerError(status);

    m_bCache = bCache == VI_TRUE;
    ViBoolean bInterchangeCheck;
    status = IviConfig_GetDriverSessionPropertyViBoolean(hDriverSession, IVICONFIG_VAL_DRIVER_SESSION_INTERCHANGE_CHECK, &bInterchangeCheck);
    CheckConfigServerError(status);

    m_bInterchangeCheck = bInterchangeCheck == VI_TRUE;
    ViBoolean bQueryInstrStatus;
    status = IviConfig_GetDriverSessionPropertyViBoolean(hDriverSession, IVICONFIG_VAL_DRIVER_SESSION_QUERY_INSTR_STATUS, &bQueryInstrStatus);
    CheckConfigServerError(status);

    m_bQueryInstrStatus = bQueryInstrStatus == VI_TRUE;
    ViBoolean bRangeCheck;
    status = IviConfig_GetDriverSessionPropertyViBoolean(hDriverSession, IVICONFIG_VAL_DRIVER_SESSION_RANGE_CHECK, &bRangeCheck);
    CheckConfigServerError(status);
    m_bRangeCheck = bRangeCheck == VI_TRUE;
    ViBoolean bRecordCoercions;
    status = IviConfig_GetDriverSessionPropertyViBoolean(hDriverSession, IVICONFIG_VAL_DRIVER_SESSION_RECORD_COERCIONS, &bRecordCoercions);
    CheckConfigServerError(status);

    m_bRecordCoercions = bRecordCoercions == VI_TRUE;
    ViBoolean bSimulate;
    status = IviConfig_GetDriverSessionPropertyViBoolean(hDriverSession, IVICONFIG_VAL_DRIVER_SESSION_SIMULATE, &bSimulate);
    CheckConfigServerError(status);

    m_bSimulate = bSimulate == VI_TRUE;
    ViChar szDriverSetup[MAX_CONFIG_STORE_STRING];
    status = IviConfig_GetDriverSessionPropertyViString(hDriverSession, IVICONFIG_VAL_DRIVER_SESSION_DRIVER_SETUP, _countof(szDriverSetup), szDriverSetup);
    CheckConfigServerError(status);

    m_strDriverSetup = szDriverSetup;
    status = ProcessDriverSetup(szDriverSetup);
    CheckError(status);

LExit:
    DisposeConfigServerHandle(hHardware);

    return status;
}

inline ViStatus DriverSession::LoadVirtualNames(IviDriverSessionHandle hDriverSession)
{
    auto status = VI_SUCCESS;

    IviVirtualNameCollectionHandle hVirtualNamesCollection = VI_NULL;
    IviVirtualNameHandle hVirtualName = VI_NULL;
    IviVirtualRangeCollectionHandle hVirtualRangeCollection = VI_NULL;
    IviVirtualRangeHandle hVirtualRange = VI_NULL;

    m_mapVirtualNameToPhysicalName.clear();
    m_mapPhysicalNameToVirtualName.clear();

    status = IviConfig_GetSessionVirtualNameCollection(hDriverSession, &hVirtualNamesCollection);
    CheckConfigServerError(status);

    ViInt32 cVirtualNames;
    status = IviConfig_GetVirtualNameCount(hVirtualNamesCollection, &cVirtualNames);
    CheckConfigServerError(status);

    for (int nVirtualName = 1; nVirtualName <= cVirtualNames; nVirtualName++)
    {
        status = IviConfig_GetVirtualNameItemByIndex(hVirtualNamesCollection, nVirtualName, &hVirtualName);
        CheckConfigServerError(status);

        ViChar szVirtualName[MAX_CONFIG_STORE_STRING];
        status = IviConfig_GetVirtualNamePropertyViString(hVirtualName, IVICONFIG_VAL_VIRTUAL_NAME_NAME, _countof(szVirtualName), szVirtualName);
        CheckConfigServerError(status);

        ViChar szMapTo[MAX_CONFIG_STORE_STRING];
        status = IviConfig_GetVirtualNamePropertyViString(hVirtualName, IVICONFIG_VAL_VIRTUAL_NAME_MAPTO, _countof(szMapTo), szMapTo);
        CheckConfigServerError(status);

        status = IviConfig_GetVirtualNameVirtualRangeCollection(hVirtualName, &hVirtualRangeCollection);
        CheckConfigServerError(status);

        ViInt32 cVirtualRanges;
        status = IviConfig_GetVirtualRangeCount(hVirtualRangeCollection, &cVirtualRanges);
        CheckConfigServerError(status);

        if (cVirtualRanges > 0)
        {
            // This is a specification for a mapping of a range of virtual names to physical names
            //
            for (int nVirtualRange = 1; nVirtualRange <= cVirtualRanges; nVirtualRange++)
            {
                status = IviConfig_GetVirtualRangeItemByIndex(hVirtualRangeCollection, nVirtualRange, &hVirtualRange);
                CheckConfigServerError(status);

                ViInt32 nVirtualRangeMin;
                status = IviConfig_GetVirtualRangePropertyViInt32(hVirtualRange, IVICONFIG_VAL_VIRTUAL_RANGE_MIN, &nVirtualRangeMin);
                CheckConfigServerError(status);

                ViInt32 nVirtualRangeMax;
                status = IviConfig_GetVirtualRangePropertyViInt32(hVirtualRange, IVICONFIG_VAL_VIRTUAL_RANGE_MAX, &nVirtualRangeMax);
                CheckConfigServerError(status);

                ViInt32 nStartingPhysicalIndex;
                status = IviConfig_GetVirtualRangePropertyViInt32(hVirtualRange, IVICONFIG_VAL_VIRTUAL_RANGE_START_PHYSICAL_INDEX, &nStartingPhysicalIndex);
                CheckConfigServerError(status);

                for (int nVirtualRangeVal = nVirtualRangeMin; nVirtualRangeVal <= nVirtualRangeMax; nVirtualRangeVal++)
                {
                    auto strVirtualName = szVirtualName + std::to_string(nVirtualRangeVal);
                    auto strPhysicalName = szMapTo + std::to_string(nVirtualRangeVal + nStartingPhysicalIndex - nVirtualRangeMin);
                    m_mapVirtualNameToPhysicalName[strVirtualName] = strPhysicalName;
                    m_mapPhysicalNameToVirtualName[strPhysicalName] = strVirtualName;
                }

                DisposeConfigServerHandle(hVirtualRange);
            }
        }
        else
        {
            // This is a simple mapping between a single virtual name and a single physical name
            //
            m_mapVirtualNameToPhysicalName[szVirtualName] = szMapTo;
            m_mapPhysicalNameToVirtualName[szMapTo] = szVirtualName;
        }

        DisposeConfigServerHandle(hVirtualName);
        DisposeConfigServerHandle(hVirtualRangeCollection);
    }

LExit:
    DisposeConfigServerHandle(hVirtualNamesCollection);
    DisposeConfigServerHandle(hVirtualRangeCollection);
    DisposeConfigServerHandle(hVirtualRange);
    DisposeConfigServerHandle(hVirtualName);

    return status;
}

inline ViStatus DriverSession::LoadPhysicalNames(IviSoftwareModuleHandle hSoftwareModule)
{
    auto status = VI_SUCCESS;

    IviPhysicalNameCollectionHandle hPhysicalNameCollection = VI_NULL;
    IviPhysicalNameHandle hPhysicalName = VI_NULL;

    status = IviConfig_GetSoftwareModulePhysicalNameCollection(hSoftwareModule, &hPhysicalNameCollection);
    CheckConfigServerError(status);

    ViInt32 cPhysicalNames;
    status = IviConfig_GetPhysicalNameCount(hPhysicalNameCollection, &cPhysicalNames);
    CheckConfigServerError(status);

    for (int nPhysicalName = 1; nPhysicalName <= cPhysicalNames; nPhysicalName++)
    {
        status = IviConfig_GetPhysicalNameItemByIndex(hPhysicalNameCollection, nPhysicalName, &hPhysicalName);
        CheckConfigServerError(status);

        ViChar szPhysicalName[MAX_CONFIG_STORE_STRING];
        status = IviConfig_GetPhysicalNamePropertyViString(hPhysicalName, IVICONFIG_VAL_PHYSICAL_NAME_NAME, _countof(szPhysicalName), szPhysicalName);
        CheckConfigServerError(status);

        ViChar szRCName[MAX_CONFIG_STORE_STRING];
        status = IviConfig_GetPhysicalNamePropertyViString(hPhysicalName, IVICONFIG_VAL_PHYSICAL_NAME_RCNAME, _countof(szRCName), szRCName);
        CheckConfigServerError(status);

        m_mapPhysicalNameToRepCapName[szPhysicalName] = szRCName;

        DisposeConfigServerHandle(hPhysicalName);
    }

LExit:
    DisposeConfigServerHandle(hPhysicalNameCollection);
    DisposeConfigServerHandle(hPhysicalName);

    return status;
}

inline ViStatus DriverSession::LoadConfigurableInitialSettings(IviConfigComponentHandle hConfigComponent)
{
    auto status = VI_SUCCESS;

    IviDataComponentCollectionHandle hDataComponentCollection = VI_NULL;
    IviDataComponentHandle hInitialSettingsStructure = VI_NULL;
    IviDataComponentCollectionHandle hInitialSettingsDataComponentCollection = VI_NULL;
    IviDataComponentHandle hDataComponent = VI_NULL;

    status = IviConfig_GetConfigComponentDataComponentCollection(hConfigComponent, &hDataComponentCollection);
    CheckConfigServerError(status);

    status = IviConfig_GetDataComponentItemByName(hDataComponentCollection, "Configurable Initial Settings", &hInitialSettingsStructure);

    if (status == IVICONFIG_ERROR_NOT_EXIST)
    {
        // Not really an error, as this just means there are no configurable initial settings on the driver session
        //
        status = IviConfig_ClearError();
        return status;
    }

    CheckConfigServerError(status);

    status = IviConfig_GetStructureDataComponentCollection(hInitialSettingsStructure, &hInitialSettingsDataComponentCollection);
    CheckConfigServerError(status);

    ViInt32 cItems;
    status = IviConfig_GetDataComponentCount(hInitialSettingsDataComponentCollection, &cItems);
    CheckConfigServerError(status);

    for (int i = 1; i <= cItems; i++)
    {
        status = IviConfig_GetDataComponentItemByIndex(hInitialSettingsDataComponentCollection, i, &hDataComponent);
        CheckConfigServerError(status);

        ViChar szDataType[MAX_CONFIG_STORE_STRING];
        status = IviConfig_GetDataComponentPropertyViString(hDataComponent, IVICONFIG_VAL_DATA_COMPONENT_TYPE, _countof(szDataType), szDataType);
        CheckConfigServerError(status);

        ViChar szName[MAX_CONFIG_STORE_STRING];
        status = IviConfig_GetDataComponentPropertyViString(hDataComponent, IVICONFIG_VAL_DATA_COMPONENT_NAME, _countof(szName), szName);
        CheckConfigServerError(status);

        if (_stricmp(szDataType, "string") == 0)
        {
            ViChar szValue[MAX_CONFIG_STORE_STRING];
            status = IviConfig_GetDataComponentPropertyViString(hDataComponent, IVICONFIG_VAL_DATA_COMPONENT_VALUE, _countof(szValue), szValue);
            CheckConfigServerError(status);

            m_mapConfigSettingsString[szName] = szValue;
        }
        else if (_stricmp(szDataType, "integer") == 0)
        {
            ViInt32 nValue;
            status = IviConfig_GetDataComponentPropertyViInt32(hDataComponent, IVICONFIG_VAL_DATA_COMPONENT_VALUE, &nValue);
            CheckConfigServerError(status);

            m_mapConfigSettingsInt32[szName] = nValue;
        }
        else if (_stricmp(szDataType, "real") == 0)
        {
            ViReal64 dValue;
            status = IviConfig_GetDataComponentPropertyViReal64(hDataComponent, IVICONFIG_VAL_DATA_COMPONENT_VALUE, &dValue);
            CheckConfigServerError(status);

            m_mapConfigSettingsReal64[szName] = dValue;
        }
        else if (_stricmp(szDataType, "boolean") == 0)
        {
            ViBoolean bValue;
            status = IviConfig_GetDataComponentPropertyViBoolean(hDataComponent, IVICONFIG_VAL_DATA_COMPONENT_VALUE, &bValue);
            CheckConfigServerError(status);
            m_mapConfigSettingsBoolean[szName] = (bValue == VI_TRUE);
        }

        DisposeConfigServerHandle(hDataComponent);
    }

    status = ProcessConfigurableInitialSettings();
    CheckError(status);

LExit:
    DisposeConfigServerHandle(hDataComponentCollection);
    DisposeConfigServerHandle(hInitialSettingsStructure);
    DisposeConfigServerHandle(hInitialSettingsDataComponentCollection);
    DisposeConfigServerHandle(hDataComponent);

    return status;
}

inline ViStatus DriverSession::ProcessConfigurableInitialSettings()
{
    auto status = VI_SUCCESS;

    // The only configurable initial setting we currently support automatically is the simulated "model"
    //
    std::string strSimulatedModel;

    if (GetConfigSettingString("model", strSimulatedModel))
    {
        m_strModel = strSimulatedModel;
    }

    return status;
}

inline ViStatus DriverSession::ProcessInitOptions(const std::string& strInitOptions)
{
    auto status = VI_SUCCESS;

    std::string strInherentOptions;

    // We first match the DriverSetup string, which, if present, must appear at the end.  Note the pattern allows any characters to follow the "DriverSetup=".
    //
    static const std::regex rx("\\s*DriverSetup\\s*=(.*)", std::regex_constants::icase | std::regex_constants::optimize);
    std::smatch match;
    std::regex_search(strInitOptions, match, rx);

    if (match.size() == 2)
    {
        // We found the DriverSetup string
        //
        status = ProcessDriverSetup(match[1]);
        ReturnOnError(status);

        // Everything that precedes the DriverSetup will be parsed as inherent options
        //
        strInherentOptions = match.prefix();
    }
    else
    {
        // We didn't find the DriverSetup string, so process the entire init option string as inherent options
        //
        strInherentOptions = strInitOptions;
    }

    status = ProcessInherentOptions(strInherentOptions);

    return status;
}

inline ViStatus DriverSession::ProcessDriverSetup(const std::string& strDriverSetup)
{
    auto status = VI_SUCCESS;

    // We explicitly clear the DriverSetup options map here because this function will get called twice if there is
    // a DriverSetup string in the config store as well as a DriverSetup string in the init options passed to the
    // init function.  In that case, the DriverSetup passed to the init function overrides *everything* specified
    // in the config store DriverSetup.  This means that an empty DriverSetup string passed to init should result
    // in an empty map, as opposed to preserving the values in the config store and taking the "union" of the 
    // config store DriverSetup value and the init function DriverSetup values.
    //
    m_mapDriverSetupOptions.clear();

    m_strDriverSetup = strDriverSetup;

    // We support comma-delimited or colon-delimited name-value pairs of the form "Name=Value" and "Name:Value".  
    // The colon-delimited one is important because the ACPwr spec defines a special NumPhases:# parameter that can be used 
    // to configure multiphase power sources. The name must be a valid C-language identifier.
    //
    static const std::regex rx("([\\w+_]+)\\s*(?:=|:)\\s*([^,]+)", std::regex_constants::optimize);

    for (auto it = std::sregex_iterator(std::begin(strDriverSetup), std::end(strDriverSetup), rx);
        (it != std::sregex_iterator()) && (status >= 0);
        ++it)
    {
        // Only two groups in our regex are capturing groups (plus the capture for the entire string)
        //
        auto match = *it;

        if (match.size() != 3)
        {
            status = ReportErrorEx(IVIC_ERROR_CANNOT_RECOVER, "Failed to parse the DriverSetup string.");
            ReturnOnError(status);
        }

        std::string strName = match[1];
        std::string strValue = match[2].matched ? match[2] : match[3];

        // We pass the name/value by reference so that a derived implementation can modify the name and/or value, if desired
        //
        status = ProcessDriverSetupNameValuePair(strName, strValue);
        ReturnOnError(status);

        // Add the pair to the driver setup options map
        //
        if (m_mapDriverSetupOptions.find(strName) != std::end(m_mapDriverSetupOptions))
        {
            status = ReportErrorEx(IVIC_ERROR_CANNOT_RECOVER, "DriverSetup option '%s' appears more than once.", strName.c_str());
            ReturnOnError(status);
        }

        m_mapDriverSetupOptions[strName] = strValue;
    }

    return status;
}

inline ViStatus DriverSession::ProcessDriverSetupNameValuePair(const std::string& strName, std::string& strValue)
{
    auto status = VI_SUCCESS;

    // The only DriverSetup option that we interpret by default is "Model"
    //
    if (_stricmp(strName.c_str(), "Model") == 0)
    {
        m_strModel = strValue;
    }

    return status;
}

inline ViStatus DriverSession::ProcessInherentOptions(const std::string& strInherentOptions)
{
    auto status = VI_SUCCESS;

    // Convert the string to lowercase to simplify processing
    //
    std::string strInherentOptionsLowercase = strInherentOptions;
    std::transform(std::begin(strInherentOptions), std::end(strInherentOptions), std::begin(strInherentOptionsLowercase), ::tolower);

    // Look for name-value pairs containing only ASCII characters and separated by commas
    //
    static const std::regex rx("\\s*(\\w+)\\s*=\\s*(\\w+)\\s*,?", std::regex_constants::optimize);

    for (auto it = std::sregex_iterator(std::begin(strInherentOptionsLowercase), std::end(strInherentOptionsLowercase), rx);
        (it != std::sregex_iterator()) && (status >= 0);
        ++it)
    {
        auto match = *it;
        assert(match.size() == 3 && "Failed to parse inherent option.");
        std::string strName = match[1];
        std::string strValue = match[2];

        if (strName == "cache")
        {
            status = ConvertInitOptionBoolean(strName, strValue, m_bCache);
        }
        else if (strName == "interchangecheck")
        {
            status = ConvertInitOptionBoolean(strName, strValue, m_bInterchangeCheck);
        }
        else if (strName == "queryinstrstatus")
        {
            status = ConvertInitOptionBoolean(strName, strValue, m_bQueryInstrStatus);
        }
        else if (strName == "rangecheck")
        {
            status = ConvertInitOptionBoolean(strName, strValue, m_bRangeCheck);
        }
        else if (strName == "recordcoercions")
        {
            status = ConvertInitOptionBoolean(strName, strValue, m_bRecordCoercions);
        }
        else if (strName == "simulate")
        {
            status = ConvertInitOptionBoolean(strName, strValue, m_bSimulate);
        }
        else
        {
            status = ReportError(IVIC_ERROR_BAD_OPTION_NAME, strName.c_str());
        }

        // Add the pair to the inherent options map
        //
        if (m_mapInherentOptions.find(strName) != std::end(m_mapInherentOptions))
        {
            status = ReportErrorEx(IVIC_ERROR_CANNOT_RECOVER, "Inherent option '%s' appears more than once.", strName.c_str());
            ReturnOnError(status);
        }

        m_mapInherentOptions[strName] = strValue;
    }

    return status;
}

inline ViStatus DriverSession::ConvertInitOptionBoolean(const std::string& strOptionName, const std::string& strOptionValue, bool& bValue)
{
    auto status = VI_SUCCESS;

    // All of the inherent options are boolean.  We accept "true", "false, "VI_TRUE", "VI_FALSE", "1", and "0", and ignore case.
    //
    if (strOptionValue == "true" || strOptionValue == "vi_true" || strOptionValue == "1")
    {
        bValue = true;
    }
    else if (strOptionValue == "false" || strOptionValue == "vi_false" || strOptionValue == "0")
    {
        bValue = false;
    }
    else
    {
        status = ReportError(IVIC_ERROR_BAD_OPTION_VALUE, strOptionValue.c_str());
    }

    return status;
}

inline bool DriverSession::InstrumentSupported() const
{
    return g_modelMap.find(InstrumentModel()) != std::end(g_modelMap);
}

inline bool DriverSession::InstrumentInFamily(const std::string& strFamily) const
{
    return ModelInFamily(InstrumentModel(), strFamily);
}

inline bool DriverSession::InstrumentIsModel(const std::string& strModel) const
{
    return InstrumentModel() == strModel;
}

inline bool DriverSession::ModelInFamily(const std::string& strModel, const std::string& strFamily) const
{
    const auto& it = g_modelMap.find(strModel);

    return (it != std::end(g_modelMap)) && (it->second == strFamily);
}

inline ViStatus DriverSession::ResetDefaults()
{
    auto status = VI_SUCCESS;

    m_bCache = m_bCacheOriginal;
    m_bInterchangeCheck = m_bInterchangeCheckOriginal;
    m_bQueryInstrStatus = m_bQueryInstrStatusOriginal;
    m_bRangeCheck = m_bRangeCheckOriginal;
    m_bRecordCoercions = m_bRecordCoercionsOriginal;
    m_bSimulate = m_bSimulateOriginal;

    return status;
}

// The ReportError functions use varargs, which require they be compiled as native code.
// The following pragma disables the compiler warning that is emitted when the /clr
// option is used to build a driver.  The pragma is ignored if /clr is not used.
//
#pragma managed(push, off)

inline ViStatus DriverSession::ReportError(ViStatus errorCode, ...) const
{
    auto status = VI_SUCCESS;

    va_list argList;
    va_start(argList, errorCode);
    status = ReportErrorV(Handle(), errorCode, std::string(), argList);
    va_end(argList);

    return status;
}

inline ViStatus DriverSession::ReportErrorEx(ViStatus errorCode, const std::string strElaboration, ...) const
{
    auto status = VI_SUCCESS;

    va_list argList;
    va_start(argList, strElaboration);
    status = ReportErrorV(Handle(), errorCode, strElaboration, argList);
    va_end(argList);

    return status;
}

#pragma managed(pop)

inline ViStatus DriverSession::ReportConfigServerError(ViStatus status) const
{
    ViChar szErr[MAX_CONFIG_STORE_STRING];
    auto statusGetError = IviConfig_GetError(_countof(szErr), szErr);
    assert(statusGetError >= 0);

    status = IviSession_SetError(m_handle, status, szErr);

    return status;
}

inline ViSession DriverSession::Handle() const
{
    return m_handle;
}

inline bool DriverSession::CacheEnabled() const
{
    return m_bCache;
}

inline bool DriverSession::InterchangeCheckEnabled() const
{
    return m_bInterchangeCheck;
}

inline bool DriverSession::QueryInstrStatusEnabled() const
{
    return m_bQueryInstrStatus;
}

inline bool DriverSession::RangeCheckEnabled() const
{
    return m_bRangeCheck;
}

inline bool DriverSession::RecordCoercionsEnabled() const
{
    return m_bRecordCoercions;
}

inline bool DriverSession::SimulationEnabled() const
{
    return m_bSimulate;
}

inline bool DriverSession::CacheEnabledOriginal() const
{
    return m_bCacheOriginal;
}

inline bool DriverSession::InterchangeCheckEnabledOriginal() const
{
    return m_bInterchangeCheckOriginal;
}

inline bool DriverSession::QueryInstrStatusEnabledOriginal() const
{
    return m_bQueryInstrStatusOriginal;
}

inline bool DriverSession::RangeCheckEnabledOriginal() const
{
    return m_bRangeCheckOriginal;
}

inline bool DriverSession::RecordCoercionsEnabledOriginal() const
{
    return m_bRecordCoercionsOriginal;
}

inline bool DriverSession::SimulationEnabledOriginal() const
{
    return m_bSimulateOriginal;
}

inline void DriverSession::SetCacheEnabled(bool bValue)
{
    m_bCache = bValue;
}

inline void DriverSession::SetInterchangeCheckEnabled(bool bValue)
{
    m_bInterchangeCheck = bValue;
}

inline void DriverSession::SetQueryInstrStatusEnabled(bool bValue)
{
    m_bQueryInstrStatus = bValue;
}

inline void DriverSession::SetRangeCheckEnabled(bool bValue)
{
    m_bRangeCheck = bValue;
}

inline void DriverSession::SetRecordCoercionsEnabled(bool bValue)
{
    m_bRecordCoercions = bValue;
}

inline void DriverSession::SetSimulationEnabled(bool bValue)
{
    m_bSimulate = bValue;
}

inline const std::string& DriverSession::InitOptions() const
{
    return m_strInitOptions;
}

inline const std::string& DriverSession::ResourceName() const
{
    return m_strResourceName;
}

inline const std::string& DriverSession::LogicalName() const
{
    return m_strLogicalName;
}

inline const std::string& DriverSession::IoDescriptor() const
{
    return m_strIoDescriptor;
}

inline const std::string& DriverSession::DriverSetup() const
{
    return m_strDriverSetup;
}

inline const std::string& DriverSession::Manufacturer() const
{
    return m_strManufacturer;
}

inline const std::string& DriverSession::InstrumentModel() const
{
    return m_strModel;
}

inline const std::string& DriverSession::SerialNumber() const
{
    return m_strSerialNumber;
}

inline const std::string& DriverSession::FirmwareRevision() const
{
    return m_strFirmwareRevision;
}

inline unsigned long DriverSession::VisaOpenTimeout() const
{
    return m_ulVisaOpenTimeout;
}

inline unsigned long DriverSession::SelfTestTimeout() const
{
    return m_ulSelfTestTimeout;
}

inline unsigned long DriverSession::ResetTimeout() const
{
    return m_ulResetTimeout;
}

inline bool DriverSession::InterchangeCheckSupported() const
{
    return m_bInterchangeCheckSupported;
}

inline unsigned long DriverSession::CoercionLogSize() const
{
    return m_ulCoercionLogSize;
}

inline bool DriverSession::GetDriverSetupOption(const std::string& strName, std::string& strValue) const
{
    auto it = m_mapDriverSetupOptions.find(strName);

    if (it != std::end(m_mapDriverSetupOptions))
    {
        strValue = it->second;
        return true;
    }

    return false;
}

inline bool DriverSession::GetConfigSettingBoolean(const std::string& strName, bool& bValue) const
{
    auto it = m_mapConfigSettingsBoolean.find(strName);

    if (it != std::end(m_mapConfigSettingsBoolean))
    {
        bValue = it->second;
        return true;
    }

    return false;
}

inline bool DriverSession::GetConfigSettingInt32(const std::string& strName, int& nValue) const
{
    auto it = m_mapConfigSettingsInt32.find(strName);

    if (it != std::end(m_mapConfigSettingsInt32))
    {
        nValue = it->second;
        return true;
    }

    return false;
}

inline bool DriverSession::GetConfigSettingReal64(const std::string& strName, double& dValue) const
{
    auto it = m_mapConfigSettingsReal64.find(strName);

    if (it != std::end(m_mapConfigSettingsReal64))
    {
        dValue = it->second;
        return true;
    }

    return false;
}

inline bool DriverSession::GetConfigSettingString(const std::string& strName, std::string& strValue) const
{
    auto it = m_mapConfigSettingsString.find(strName);

    if (it != std::end(m_mapConfigSettingsString))
    {
        strValue = it->second;
        return true;
    }

    return false;
}

inline const DriverSettingsMap<std::string>& DriverSession::InherentOptions() const
{
    return m_mapInherentOptions;
}

inline const DriverSettingsMap<std::string>& DriverSession::DriverSetupOptions() const
{
    return m_mapDriverSetupOptions;
}

inline const DriverSettingsMap<bool>& DriverSession::ConfigSettingsBoolean() const
{
    return m_mapConfigSettingsBoolean;
}

inline const DriverSettingsMap<int>& DriverSession::ConfigSettingsInt32() const
{
    return m_mapConfigSettingsInt32;
}

inline const DriverSettingsMap<double>& DriverSession::ConfigSettingsReal64() const
{
    return m_mapConfigSettingsReal64;
}

inline const DriverSettingsMap<std::string>& DriverSession::ConfigSettingsString() const
{
    return m_mapConfigSettingsString;
}

inline const VirtualNameMap& DriverSession::VirtualNameMappings() const
{
    return m_mapVirtualNameToPhysicalName;
}

/// <summary>
/// Returns the unqualified physical name associated with the specified virtual name.  
/// </summary>
/// <param name="strVirtualName">The virtual name to translate.</param>
/// <returns>  
/// The unqualified physical name associated with the specified virtual name. If a qualified physical name was specified in the IVI Configuration Store, then 
/// the repeated capability name prefix (e.g. "Channel!!") is stripped and only the unqualified name is returned.
/// </returns>
inline const std::string DriverSession::TranslateVirtualName(const std::string& strVirtualName) const
{
    std::string strPhysicalName;
    auto it = m_mapVirtualNameToPhysicalName.find(strVirtualName);

    if (it != std::end(m_mapVirtualNameToPhysicalName))
    {
        // Virtual name is in the map
        //
        strPhysicalName = it->second;
    }
    else
    {
        // Virtual name not found, so we assume this is a physical name
        //
        strPhysicalName = strVirtualName;
    }

    auto pos = strPhysicalName.find("!!");

    if (pos != std::string::npos)
    {
        // It's a physical name qualified by the repcap name.  Only return the unqualified physical name
        //
        strPhysicalName.erase(std::begin(strPhysicalName), std::begin(strPhysicalName) + pos + 2);
    }

    return strPhysicalName;
}

/// <summary>
/// Returns the virtual name associated with the specified physical name.  
/// </summary>
/// <param name="strPhysicalName">The physical name to translate.  If a qualified physical name was specified in the IVI Configuration Store,
/// then this parameter must also be that same qualified physical name.</param>
/// <returns>The virtual name associated with the specified physical name.</returns>
inline const std::string DriverSession::TranslatePhysicalName(const std::string& strPhysicalName) const
{
    std::string strVirtualName;
    auto it = m_mapPhysicalNameToVirtualName.find(strPhysicalName);

    if (it != std::end(m_mapPhysicalNameToVirtualName))
    {
        // Physical name is in the map
        //
        strVirtualName = it->second;
    }
    else
    {
        // Physical name not found, so virtual name is the same as the physical name
        //
        strVirtualName = strPhysicalName;
    }

    return strVirtualName;
}

// Specializations of GetCacheEntry for each of the supported attribute data types
//
template <>
inline CacheEntry<ViInt32>& DriverSession::GetCacheEntry(ViAttr attributeId, const std::string& strQualifiedPhysicalName)
{
    return m_cacheViInt32[attributeId][strQualifiedPhysicalName];
}

template <>
inline CacheEntry<ViInt64>& DriverSession::GetCacheEntry(ViAttr attributeId, const std::string& strQualifiedPhysicalName)
{
    return m_cacheViInt64[attributeId][strQualifiedPhysicalName];
}

template <>
inline CacheEntry<ViReal64>& DriverSession::GetCacheEntry(ViAttr attributeId, const std::string& strQualifiedPhysicalName)
{
    return m_cacheViReal64[attributeId][strQualifiedPhysicalName];
}

template <>
inline CacheEntry<ViBoolean>& DriverSession::GetCacheEntry(ViAttr attributeId, const std::string& strQualifiedPhysicalName)
{
    return m_cacheViBoolean[attributeId][strQualifiedPhysicalName];
}

template <>
inline CacheEntry<ViSession>& DriverSession::GetCacheEntry(ViAttr attributeId, const std::string& strQualifiedPhysicalName)
{
    return m_cacheViSession[attributeId][strQualifiedPhysicalName];
}

template <>
inline CacheEntry<std::string>& DriverSession::GetCacheEntry(ViAttr attributeId, const std::string& strQualifiedPhysicalName)
{
    return m_cacheString[attributeId][strQualifiedPhysicalName];
}

template <typename... Args>
inline void DriverSession::InvalidateAttributes(ViAttr attributeId, Args... args)
{
    InvalidateAttributes(attributeId);
    InvalidateAttributes(args...);
}

inline void DriverSession::InvalidateAttributes(ViAttr attributeId)
{
    auto it = g_AttributeMap.find(attributeId);
    assert(it != std::end(g_AttributeMap));

    if (it != std::end(g_AttributeMap))
    {
        const auto& invalidator = it->second.Invalidator();
        invalidator(this, true, std::string());
    }
}

template <typename TRepCap, typename... Args>
inline void DriverSession::InvalidateAttributes(const PhysicalNameList<TRepCap>& physicalNames, ViAttr attributeId, Args... args)
{
    InvalidateAttributes(physicalNames, attributeId);
    InvalidateAttributes(physicalNames, args...);
}

template <typename TRepCap>
inline void DriverSession::InvalidateAttributes(const PhysicalNameList<TRepCap>& physicalNames, ViAttr attributeId)
{
    auto it = g_AttributeMap.find(attributeId);
    assert(it != std::end(g_AttributeMap));

    if (it != std::end(g_AttributeMap))
    {
        const auto& invalidator = it->second.Invalidator();

        for (const auto& physicalName : physicalNames)
        {
            invalidator(this, false, physicalName.QualifiedFullName());
        }
    }
}

inline void DriverSession::InvalidateAllAttributes()
{
    m_cacheViInt32.clear();
    m_cacheViInt64.clear();
    m_cacheViReal64.clear();
    m_cacheViBoolean.clear();
    m_cacheViSession.clear();
    m_cacheString.clear();
}

template <typename T>
inline std::string FormatCoercedValue(const T& value)
{
    return std::to_string(value);
}

template <>
inline std::string FormatCoercedValue<std::string>(const std::string& value)
{
    return "'" + value + "'";
}

template <typename T>
inline void DriverSession::AddCoercionRecord(T desiredVal, T coercedVal, const std::string& strFunctionName, const std::string& strParameterName)
{
    // An example coercion record string is as follows:
    //
    //		"Attribute Vertical Range on channel ch1 was coerced from 9.0 to 10.0."
    //
    auto strDesiredValue = FormatCoercedValue(desiredVal);
    auto strCoercedValue = FormatCoercedValue(coercedVal);

    char szRecord[NRT_MAX_ERROR];

    if (IsAttributeSetterName(strFunctionName.c_str()))
    {
        auto strAttribute = GetAttributeNameFromGetterOrSetterName(strFunctionName);
        sprintf_s(szRecord, "Attribute %s coerced from %s to %s.", strAttribute.c_str(), strDesiredValue.c_str(), strCoercedValue.c_str());
    }
    else
    {
        sprintf_s(szRecord, "Parameter %s in function %s coerced from %s to %s.", strParameterName.c_str(), strFunctionName.c_str(), strDesiredValue.c_str(), strCoercedValue.c_str());
    }

    if (m_coercionRecords.size() == CoercionLogSize())
    {
        m_coercionRecords.pop_front();
    }

    m_coercionRecords.push_back(szRecord);
}

inline std::string DriverSession::GetNextCoercionRecord()
{
    // Get the oldest coercion record but don't remove it from the collection
    //
    return (m_coercionRecords.size() > 0) ? m_coercionRecords.front() : std::string();
}

inline void DriverSession::RemoveNextCoercionRecord()
{
    if (m_coercionRecords.size() > 0)
    {
        m_coercionRecords.pop_front();
    }
}

///////////////////////////////////////////////////////////////////////////////
// Utility functions
//
template <typename TSession>
inline ViStatus GetDriverSession(ViSession Vi, TSession** ppSession)
{
    static_assert(std::is_base_of<DriverSession, TSession>::value, "Session class must derive from DriverSession.");

    if (ppSession == nullptr) return IVIC_ERROR_NULL_POINTER;

    auto status = VI_SUCCESS;
    *ppSession = nullptr;

    status = IviSession_GetDataPtr(Vi, (ViAddr*)ppSession);

    return status;
}

template <typename TSession>
inline TSession* GetDriverSession(ViSession Vi)
{
    TSession* pSession = nullptr;
    GetDriverSession<TSession>(Vi, &pSession);

    return pSession;
}

///////////////////////////////////////////////////////////////////////////////
// I/O functions
//
inline ViStatus ClearIOStatus(ViSession Vi)
{
    return GetDriverSession(Vi)->ClearIOStatus();
}

inline ViStatus PollInstrumentErrors(ViSession Vi)
{
    return GetDriverSession(Vi)->PollInstrumentErrors();
}

///////////////////////////////////////////////////////////////////////////////
// VISA I/O functions
//
#ifndef NRT_NO_VISA

inline ViSession GetVisaSession(ViSession Vi)
{
    return GetDriverSession(Vi)->GetVisaSession();
}

inline ViSession GetVisaResourceManager(ViSession Vi)
{
    return GetDriverSession(Vi)->GetVisaResourceManager();
}

// Helper for implementing IVI-C wrapper direct I/O functions as defined in IVI-3.1
//
inline ViStatus ReadBytes(ViSession Vi, ViInt64 BufferSize, ViByte Buffer[], ViInt64* ReturnCount)
{
    ViStatus status = VI_SUCCESS;

    ViSession visaSession = GetVisaSession(Vi);
    ViUInt32 cbActual;
    status = viRead(visaSession, Buffer, (ViUInt32)BufferSize, &cbActual);

    if (ReturnCount != NULL)
    {
        *ReturnCount = cbActual;
    }

    // Read any remaining data in the instrument until an EOI is received and discard the results
    //
    while (status == VI_SUCCESS_MAX_CNT)
    {
        ViByte tempBuffer[4096];
        status = viRead(visaSession, tempBuffer, _countof(tempBuffer), &cbActual);
    }

    return status;
}

// Helper for implementing IVI-C wrapper direct I/O functions as defined in IVI-3.1
//
inline ViStatus WriteBytes(ViSession Vi, ViByte Buffer[], ViInt64 Count, ViInt64* ReturnCount)
{
    ViStatus status = VI_SUCCESS;

    ViSession visaSession = GetVisaSession(Vi);
    ViUInt32 cbActual;
    status = viWrite(visaSession, Buffer, (ViUInt32)Count, &cbActual);

    if (ReturnCount != NULL)
    {
        *ReturnCount = cbActual;
    }

    return status;
}

// Helpers for implementing VISA-based functions that read string-based lists
//
template<typename TElement, int ElementSize>
inline ViStatus ReadList(ViSession Vi, ViInt64 cMaxElements, std::vector<TElement>& vecElements, std::function<ViStatus(const char*, TElement&)> transform)
{
    ViStatus status = VI_SUCCESS;

    auto visaSession = GetVisaSession(Vi);

    for (auto i = 0; (i < cMaxElements) || (cMaxElements < 0); i++)
    {
        char szVal[ElementSize];
        auto cbVal = _countof(szVal);
        status = viScanf(visaSession, "%#[^,],", &cbVal, szVal);
        ReturnOnError(status);

        TElement element;
        status = transform(szVal, element);
        ReturnOnError(status);

        vecElements.push_back(element);
		
		if (strrchr(szVal, '\n'))
		{
			break;
		}
	}

    return status;
}

template<typename TElement, int ElementSize>
inline ViStatus ReadList(ViSession Vi, ViInt64 cMaxElements, TElement Elements[], ViInt64* pcActualElements, std::function<ViStatus(const char*, TElement&)> transform)
{
    ViStatus status = VI_SUCCESS;

    if (pcActualElements != nullptr)
    {
        *pcActualElements = 0;
    }

    auto visaSession = GetVisaSession(Vi);
    
    int64_t i = 0;

    for (; (i < cMaxElements) || (cMaxElements < 0); i++)
    {
        char szVal[ElementSize];
        auto cbVal = _countof(szVal);
        status = viScanf(visaSession, "%#[^,],", &cbVal, szVal);
        ReturnOnError(status);

        TElement element;
        status = transform(szVal, element);
        ReturnOnError(status);

        Elements[i] = element;

        if (pcActualElements != nullptr)
        {
            (*pcActualElements)++;
        }

		if (strrchr(szVal, '\n'))
		{
			break;
		}
	}

    return status;
}

template<int ElementSize>
inline ViStatus ReadStringList(ViSession Vi, ViInt64 cMaxElements, std::vector<std::string>& vecElements)
{
    return ReadList<std::string, ElementSize>(Vi, cMaxElements, vecElements, [&](const char* pszElement, std::string& element)
    {
        element = pszElement;

        return VI_SUCCESS;
    });
}

template<typename TEnum>
inline ViStatus ReadEnumList(ViSession Vi, ViInt64 cMaxElements, std::vector<ViInt32>& vecElements)
{
    static_assert(std::is_base_of<EnumConverter<TEnum>, TEnum>::value, "Template argument must be an enum converter.");

    return ReadList<ViInt32, MAX_ENUM_RESPONSE>(Vi, cMaxElements, vecElements, [&](const char* pszElement, ViInt32& element)
    {
        return TEnum::FromResponse(Vi, pszElement, &element);
    });
}

template<typename TEnum>
inline ViStatus ReadEnumList(ViSession Vi, ViInt32 cMaxElements, ViInt32 Elements[], ViInt32* pcActualElements)
{
    ViInt64 cActual;
    auto status = ReadEnumList<TEnum>(Vi, cMaxElements, Elements, &cActual);
    ReturnOnError(status);

    if (pcActualElements != nullptr)
    {
        *pcActualElements = (ViInt32)cActual;
    }

    return status;
}

template<typename TEnum>
inline ViStatus ReadEnumList(ViSession Vi, ViInt64 cMaxElements, ViInt32 Elements[], ViInt64* pcActualElements)
{
    static_assert(std::is_base_of<EnumConverter<TEnum>, TEnum>::value, "Template argument must be an enum converter.");

    return ReadList<ViInt32, MAX_ENUM_RESPONSE>(Vi, cMaxElements, Elements, pcActualElements, [&](const char* pszElement, ViInt32& element)
    {
        return TEnum::FromResponse(Vi, pszElement, &element);
    });
}

template<typename TBool = Boolean>
inline ViStatus ReadBoolList(ViSession Vi, ViInt64 cMaxElements, std::vector<ViBoolean>& vecElements)
{
    // It would seem that we "should" be able to just call Boolean::FromResponse below instead of defining a template
    // parameter and then enforcing that the template be a specific type.  But, the Boolean class is defined in one of
    // the driver header files, so we cannot compile against a type defined there.  By making this function a template,
    // we can defer instantiation until the full definition of the Boolean class is available.
    //
    static_assert(std::is_same<Boolean, TBool>::value, "Template argument must be the Boolean class.");

    return ReadList<ViBoolean, MAX_ENUM_RESPONSE>(Vi, cMaxElements, vecElements, [&](const char* pszElement, ViBoolean& element)
    {
        return TBool::FromResponse(Vi, pszElement, &element);
    });
}

template<typename TBool = Boolean>
inline ViStatus ReadBoolList(ViSession Vi, ViInt32 cMaxElements, ViBoolean Elements[], ViInt32* pcActualElements)
{
    ViInt64 cActual;
    auto status = ReadBoolList<TBool>(Vi, cMaxElements, Elements, &cActual);
    ReturnOnError(status);

    if (pcActualElements != nullptr)
    {
        *pcActualElements = (ViInt32)cActual;
    }

    return status;
}

template<typename TBool = Boolean>
inline ViStatus ReadBoolList(ViSession Vi, ViInt64 cMaxElements, ViBoolean Elements[], ViInt64* pcActualElements)
{
    static_assert(std::is_same<Boolean, TBool>::value, "Template argument must be the Boolean class.");

    return ReadList<ViBoolean, MAX_ENUM_RESPONSE>(Vi, cMaxElements, Elements, pcActualElements, [&](const char* pszElement, ViBoolean& element)
    {
        return TBool::FromResponse(Vi, pszElement, &element);
    });
}

// Helpers for implementing VISA-based functions that write string-based lists
//

template<typename TElement>
ViStatus WriteList(ViSession Vi, ViInt64 cMaxElements, const std::vector<TElement>& vecElements, std::function<ViStatus(const TElement&, std::string&)> transform, bool bAppendLineFeed)
{
    ViStatus status = VI_SUCCESS;

	auto visaSession = GetVisaSession(Vi);

    for (auto i = 0; (i < cMaxElements && i < vecElements.size()); i++)
    {
        std::string strElement;
        status = transform(vecElements[i], strElement);
        ReturnOnError(status);

        status = viPrintf(visaSession, (i > 0) ? ",%s" : "%s", strElement.c_str());
        ReturnOnError(status);
    }

    if (bAppendLineFeed)
    {
        status = viPrintf(visaSession, "\n");
        ReturnOnError(status);
    }

    return status;
}

template<typename TElement>
ViStatus WriteList(ViSession Vi, ViInt64 cMaxElements, TElement Elements[], std::function<ViStatus(const TElement&, std::string&)> transform, bool bAppendLineFeed)
{
    ViStatus status = VI_SUCCESS;

	auto visaSession = GetVisaSession(Vi);

    for (auto i = 0; i < cMaxElements; i++)
    {
        std::string strElement;
        status = transform(Elements[i], strElement);
        ReturnOnError(status);

        status = viPrintf(visaSession, (i > 0) ? ",%s" : "%s", strElement.c_str());
        ReturnOnError(status);
    }

    if (bAppendLineFeed)
    {
        status = viPrintf(visaSession, "\n");
        ReturnOnError(status);
    }

    return status;
}

inline ViStatus WriteStringList(ViSession Vi, ViInt64 cMaxElements, const std::vector<std::string>& vecElements, bool bAppendLineFeed)
{
    return WriteList<std::string>(Vi, cMaxElements, vecElements, [&](const std::string& element, std::string strElement)
    {
        strElement = element;

        return VI_SUCCESS;
    }, bAppendLineFeed);
}

template<typename TEnum>
ViStatus WriteEnumList(ViSession Vi, ViInt64 cMaxElements, ViInt32 Elements[], bool bAppendLineFeed)
{
    static_assert(std::is_base_of<EnumConverter<TEnum>, TEnum>::value, "Template argument must be an enum converter.");

    return WriteList<ViInt32>(Vi, cMaxElements, Elements, [&](const ViInt32& element, std::string& strElement)
    {
        return TEnum::ToCommand(Vi, element, strElement);
    }, bAppendLineFeed);
}

template<typename TBool = Boolean>
ViStatus WriteBoolList(ViSession Vi, ViInt64 cMaxElements, ViBoolean Elements[], bool bAppendLineFeed)
{
    static_assert(std::is_same<Boolean, TBool>::value, "Template argument must be the Boolean class.");

    return WriteList<ViBoolean>(Vi, cMaxElements, Elements, [&](const ViBoolean& element, std::string& strElement)
    {
        return TBool::ToCommand(Vi, element, strElement);
    }, bAppendLineFeed);
}

#endif	// NRT_NO_VISA

///////////////////////////////////////////////////////////////////////////////
// Driver operation functions
//
inline bool CacheEnabled(ViSession Vi)
{
    return GetDriverSession(Vi)->CacheEnabled();
}

inline bool InterchangeCheckEnabled(ViSession Vi)
{
    return GetDriverSession(Vi)->InterchangeCheckEnabled();
}

inline bool QueryInstrStatusEnabled(ViSession Vi)
{
    return GetDriverSession(Vi)->QueryInstrStatusEnabled();
}

inline bool RangeCheckEnabled(ViSession Vi)
{
    return GetDriverSession(Vi)->RangeCheckEnabled();
}

inline bool RecordCoercionsEnabled(ViSession Vi)
{
    return GetDriverSession(Vi)->RecordCoercionsEnabled();
}

inline bool SimulationEnabled(ViSession Vi)
{
    return GetDriverSession(Vi)->SimulationEnabled();
}

inline bool CacheEnabledOriginal(ViSession Vi)
{
    return GetDriverSession(Vi)->CacheEnabledOriginal();
}

inline bool InterchangeCheckEnabledOriginal(ViSession Vi)
{
    return GetDriverSession(Vi)->InterchangeCheckEnabledOriginal();
}

inline bool QueryInstrStatusEnabledOriginal(ViSession Vi)
{
    return GetDriverSession(Vi)->QueryInstrStatusEnabledOriginal();
}

inline bool RangeCheckEnabledOriginal(ViSession Vi)
{
    return GetDriverSession(Vi)->RangeCheckEnabledOriginal();
}

inline bool RecordCoercionsEnabledOriginal(ViSession Vi)
{
    return GetDriverSession(Vi)->RecordCoercionsEnabledOriginal();
}

inline bool SimulationEnabledOriginal(ViSession Vi)
{
    return GetDriverSession(Vi)->SimulationEnabledOriginal();
}

inline void SetCacheEnabled(ViSession Vi, bool bValue)
{
    return GetDriverSession(Vi)->SetCacheEnabled(bValue);
}

inline void SetInterchangeCheckEnabled(ViSession Vi, bool bValue)
{
    return GetDriverSession(Vi)->SetInterchangeCheckEnabled(bValue);
}

inline void SetQueryInstrStatusEnabled(ViSession Vi, bool bValue)
{
    return GetDriverSession(Vi)->SetQueryInstrStatusEnabled(bValue);
}

inline void SetRangeCheckEnabled(ViSession Vi, bool bValue)
{
    return GetDriverSession(Vi)->SetRangeCheckEnabled(bValue);
}

inline void SetRecordCoercionsEnabled(ViSession Vi, bool bValue)
{
    return GetDriverSession(Vi)->SetRecordCoercionsEnabled(bValue);
}

inline void SetSimulationEnabled(ViSession Vi, bool bValue)
{
    return GetDriverSession(Vi)->SetSimulationEnabled(bValue);
}

inline const std::string& InitOptions(ViSession Vi)
{
    return GetDriverSession(Vi)->InitOptions();
}

inline const std::string& ResourceName(ViSession Vi)
{
    return GetDriverSession(Vi)->ResourceName();
}

inline const std::string& LogicalName(ViSession Vi)
{
    return GetDriverSession(Vi)->LogicalName();
}

inline const std::string& IoDescriptor(ViSession Vi)
{
    return GetDriverSession(Vi)->IoDescriptor();
}

inline const std::string& DriverSetup(ViSession Vi)
{
    return GetDriverSession(Vi)->DriverSetup();
}

inline const std::string& Manufacturer(ViSession Vi)
{
    return GetDriverSession(Vi)->Manufacturer();
}

inline const std::string& InstrumentModel(ViSession Vi)
{
    return GetDriverSession(Vi)->InstrumentModel();
}

inline const std::string& SerialNumber(ViSession Vi)
{
    return GetDriverSession(Vi)->SerialNumber();
}

inline const std::string& FirmwareRevision(ViSession Vi)
{
    return GetDriverSession(Vi)->FirmwareRevision();
}

inline unsigned long SelfTestTimeout(ViSession Vi)
{
    return GetDriverSession(Vi)->SelfTestTimeout();
}

inline unsigned long ResetTimeout(ViSession Vi)
{
    return GetDriverSession(Vi)->ResetTimeout();
}

inline bool InterchangeCheckSupported(ViSession Vi)
{
    return GetDriverSession(Vi)->InterchangeCheckSupported();
}

inline unsigned long CoercionLogSize(ViSession Vi)
{
    return GetDriverSession(Vi)->CoercionLogSize();
}

///////////////////////////////////////////////////////////////////////////////
// Configuration access functions
//
inline bool GetDriverSetupOption(ViSession Vi, const std::string& strName, std::string& strValue)
{
    return GetDriverSession(Vi)->GetDriverSetupOption(strName, strValue);
}

inline bool GetConfigSettingBoolean(ViSession Vi, const std::string& strName, bool& bValue)
{
    return GetDriverSession(Vi)->GetConfigSettingBoolean(strName, bValue);
}

inline bool GetConfigSettingInt32(ViSession Vi, const std::string& strName, int& nValue)
{
    return GetDriverSession(Vi)->GetConfigSettingInt32(strName, nValue);
}

inline bool GetConfigSettingReal64(ViSession Vi, const std::string& strName, double& dValue)
{
    return GetDriverSession(Vi)->GetConfigSettingReal64(strName, dValue);
}

inline bool GetConfigSettingString(ViSession Vi, const std::string& strName, std::string& strValue)
{
    return GetDriverSession(Vi)->GetConfigSettingString(strName, strValue);
}

inline const DriverSettingsMap<bool>& ConfigSettingsBoolean(ViSession Vi)
{
    return GetDriverSession(Vi)->ConfigSettingsBoolean();
}

inline const DriverSettingsMap<int>& ConfigSettingsInt32(ViSession Vi)
{
    return GetDriverSession(Vi)->ConfigSettingsInt32();
}

inline const DriverSettingsMap<double>& ConfigSettingsReal64(ViSession Vi)
{
    return GetDriverSession(Vi)->ConfigSettingsReal64();
}

inline const DriverSettingsMap<std::string>& ConfigSettingsString(ViSession Vi)
{
    return GetDriverSession(Vi)->ConfigSettingsString();
}

inline const DriverSettingsMap<std::string>& InherentOptions(ViSession Vi)
{
    return GetDriverSession(Vi)->InherentOptions();
}

inline const DriverSettingsMap<std::string>& DriverSetupOptions(ViSession Vi)
{
    return GetDriverSession(Vi)->DriverSetupOptions();
}

///////////////////////////////////////////////////////////////////////////////
// Miscellaneous functions
//
inline bool InstrumentSupported(ViSession Vi)
{
    return GetDriverSession(Vi)->InstrumentSupported();
}

inline bool InstrumentInFamily(ViSession Vi, const std::string& strFamily)
{
    return GetDriverSession(Vi)->InstrumentInFamily(strFamily);
}

inline bool InstrumentIsModel(ViSession Vi, const std::string& strModel)
{
    return GetDriverSession(Vi)->InstrumentIsModel(strModel);
}

inline bool ModelInFamily(ViSession Vi, const std::string& strModel, const std::string& strFamily)
{
    return GetDriverSession(Vi)->ModelInFamily(strModel, strFamily);
}

template <typename T>
inline ModelBasedType<T>::ModelBasedType()
    : ModelBasedType(std::string())
{
}

template <typename T>
inline ModelBasedType<T>::ModelBasedType(const std::string& strModelList)
    : Models(Split(strModelList, ','))
{
}

template <typename TIterator>
inline TIterator FindModelSpecificValue(ViSession Vi, const std::string& strModel, TIterator itFirst, TIterator itLast)
{
    auto itBest = itLast;
    auto bMatchIsFamily = false;

    for (auto& it = itFirst; it != itLast; ++it)
    {
        if (it->Models.empty() && !bMatchIsFamily)
        {
            // We found the default entry and we've not matched a previous entry, so make a note and 
            // keep looking for a model-specific match or a family-specific match.
            //
            itBest = it;
            continue;
        }

        for (auto& strModelOrFamily : it->Models)
        {
            if (strModelOrFamily == strModel)
            {
                // We found a value with a matching model, so there's no need to look further
                //
                return it;
            }

            if (ModelInFamily(Vi, strModel, strModelOrFamily))
            {
                // We found a value with a family that contains the desired model, so we make
                // a note and keep looking for a model-specific match.
                //
                itBest = it;
                bMatchIsFamily = true;
            }
        }
    }

    return itBest;
}

///////////////////////////////////////////////////////////////////////////////
// Virtual name functions
//
inline const std::string TranslateVirtualName(ViSession Vi, const std::string& strVirtualName)
{
    return GetDriverSession(Vi)->TranslateVirtualName(strVirtualName);
}

inline const std::string TranslatePhysicalName(ViSession Vi, const std::string& strPhysicalName)
{
    return GetDriverSession(Vi)->TranslatePhysicalName(strPhysicalName);
}

inline const VirtualNameMap& VirtualNameMappings(ViSession Vi)
{
    return GetDriverSession(Vi)->VirtualNameMappings();
}

///////////////////////////////////////////////////////////////////////////////
// Error reporting
//
inline const std::string GetErrorMessage(ViStatus errorCode)
{
    auto it = g_errorMessageMap.find(errorCode);

    return (it != std::end(g_errorMessageMap)) ? it->second : std::string();
}

// The ReportError functions use varargs, which require they be compiled as native code.
// The following pragma disables the compiler warning that is emitted when the /clr
// option is used to build a driver.  The pragma is ignored if /clr is not used.
//
#pragma managed(push, off)

inline ViStatus ReportError(ViSession Vi, ViStatus errorCode, ...)
{
    auto status = VI_SUCCESS;

    va_list argList;
    va_start(argList, errorCode);
    status = ReportErrorV(Vi, errorCode, std::string(), argList);
    va_end(argList);

    return status;
}

inline ViStatus ReportErrorEx(ViSession Vi, ViStatus errorCode, const std::string strElaboration, ...)
{
    auto status = VI_SUCCESS;

    va_list argList;
    va_start(argList, strElaboration);
    status = ReportErrorV(Vi, errorCode, strElaboration, argList);
    va_end(argList);

    return status;
}

inline ViStatus ReportErrorV(ViSession Vi, ViStatus errorCode, const std::string strElaboration, va_list argList)
{
    auto status = VI_SUCCESS;

    auto strErr = GetErrorMessage(errorCode);

    if (!strElaboration.empty())
    {
        strErr += "  " + strElaboration;
    }

    char szErr[NRT_MAX_ERROR];
    vsnprintf_s(szErr, _countof(szErr), strErr.c_str(), argList);
    status = IviSession_SetError(Vi, errorCode, szErr);

    return (status >= 0) ? errorCode : status;
}

#pragma managed(pop)

///////////////////////////////////////////////////////////////////////////////
// Attribute support
//
inline AttributeInfo::AttributeInfo(ViAttr id, const std::string strAttributeName, AttributeGetter<ViInt32> getter, AttributeSetter<ViInt32> setter)
    : m_id(id), m_strAttributeName(strAttributeName), m_typeInfo(typeid(ViInt32)), m_strTypeName("ViInt32")
{
    m_getter.pViInt32 = getter;
    m_setter.pViInt32 = setter;

    m_invalidator = [id](DriverSession* pDriverSession, bool bInvalidateForAllPhysicalNames, const std::string& strQualifiedPhysicalName)
    {
        if (bInvalidateForAllPhysicalNames)
        {
            pDriverSession->m_cacheViInt32[id].clear();
        }
        else
        {
            auto& entry = pDriverSession->GetCacheEntry<ViInt32>(id, strQualifiedPhysicalName);
            entry.Invalidate();
        }
    };
}

inline AttributeInfo::AttributeInfo(ViAttr id, const std::string strAttributeName, AttributeGetter<ViInt64> getter, AttributeSetter<ViInt64> setter)
    : m_id(id), m_strAttributeName(strAttributeName), m_typeInfo(typeid(ViInt64)), m_strTypeName("ViInt64")
{
    m_getter.pViInt64 = getter;
    m_setter.pViInt64 = setter;

    m_invalidator = [id](DriverSession* pDriverSession, bool bInvalidateForAllPhysicalNames, const std::string& strQualifiedPhysicalName)
    {
        if (bInvalidateForAllPhysicalNames)
        {
            pDriverSession->m_cacheViInt64[id].clear();
        }
        else
        {
            auto& entry = pDriverSession->GetCacheEntry<ViInt64>(id, strQualifiedPhysicalName);
            entry.Invalidate();
        }
    };
}

inline AttributeInfo::AttributeInfo(ViAttr id, const std::string strAttributeName, AttributeGetter<ViReal64> getter, AttributeSetter<ViReal64> setter)
    : m_id(id), m_strAttributeName(strAttributeName), m_typeInfo(typeid(ViReal64)), m_strTypeName("ViReal64")
{
    m_getter.pViReal64 = getter;
    m_setter.pViReal64 = setter;

    m_invalidator = [id](DriverSession* pDriverSession, bool bInvalidateForAllPhysicalNames, const std::string& strQualifiedPhysicalName)
    {
        if (bInvalidateForAllPhysicalNames)
        {
            pDriverSession->m_cacheViReal64[id].clear();
        }
        else
        {
            auto& entry = pDriverSession->GetCacheEntry<ViReal64>(id, strQualifiedPhysicalName);
            entry.Invalidate();
        }
    };
}

inline AttributeInfo::AttributeInfo(ViAttr id, const std::string strAttributeName, AttributeGetter<ViBoolean> getter, AttributeSetter<ViBoolean> setter)
    : m_id(id), m_strAttributeName(strAttributeName), m_typeInfo(typeid(ViBoolean)), m_strTypeName("ViBoolean")
{
    m_getter.pViBoolean = getter;
    m_setter.pViBoolean = setter;

    m_invalidator = [id](DriverSession* pDriverSession, bool bInvalidateForAllPhysicalNames, const std::string& strQualifiedPhysicalName)
    {
        if (bInvalidateForAllPhysicalNames)
        {
            pDriverSession->m_cacheViBoolean[id].clear();
        }
        else
        {
            auto& entry = pDriverSession->GetCacheEntry<ViBoolean>(id, strQualifiedPhysicalName);
            entry.Invalidate();
        }
    };
}

inline AttributeInfo::AttributeInfo(ViAttr id, const std::string strAttributeName, AttributeGetter<ViSession> getter, AttributeSetter<ViSession> setter)
    : m_id(id), m_strAttributeName(strAttributeName), m_typeInfo(typeid(ViSession)), m_strTypeName("ViSession")
{
    m_getter.pViSession = getter;
    m_setter.pViSession = setter;

    m_invalidator = [id](DriverSession* pDriverSession, bool bInvalidateForAllPhysicalNames, const std::string& strQualifiedPhysicalName)
    {
        if (bInvalidateForAllPhysicalNames)
        {
            pDriverSession->m_cacheViSession[id].clear();
        }
        else
        {
            auto& entry = pDriverSession->GetCacheEntry<ViSession>(id, strQualifiedPhysicalName);
            entry.Invalidate();
        }
    };
}

inline AttributeInfo::AttributeInfo(ViAttr id, const std::string strAttributeName, AttributeGetterViString getter, AttributeSetterViString setter)
    : m_id(id), m_strAttributeName(strAttributeName), m_typeInfo(typeid(ViString)), m_strTypeName("ViString")
{
    m_getter.pViString = getter;
    m_setter.pViString = setter;

    m_invalidator = [id](DriverSession* pDriverSession, bool bInvalidateForAllPhysicalNames, const std::string& strQualifiedPhysicalName)
    {
        if (bInvalidateForAllPhysicalNames)
        {
            pDriverSession->m_cacheString[id].clear();
        }
        else
        {
            auto& entry = pDriverSession->GetCacheEntry<std::string>(id, strQualifiedPhysicalName);
            entry.Invalidate();
        }
    };
}

inline ViAttr AttributeInfo::AttributeId() const
{
    return m_id;
}

inline const std::string& AttributeInfo::AttributeName() const
{
    return m_strAttributeName;
}

inline const std::string& AttributeInfo::TypeName() const
{
    return m_strTypeName;
}

inline const type_info& AttributeInfo::TypeInfo() const
{
    return m_typeInfo;
}

inline const AttributeInvalidator& AttributeInfo::Invalidator() const
{
    return m_invalidator;
}

template <>
inline AttributeGetter<ViInt32> AttributeInfo::Getter() const
{
    return m_getter.pViInt32;
}

template <>
inline AttributeGetter<ViInt64> AttributeInfo::Getter() const
{
    return m_getter.pViInt64;
}

template <>
inline AttributeGetter<ViReal64> AttributeInfo::Getter() const
{
    return m_getter.pViReal64;
}

template <>
inline AttributeGetter<ViBoolean> AttributeInfo::Getter() const
{
    return m_getter.pViBoolean;
}

template <>
inline AttributeGetter<ViSession> AttributeInfo::Getter() const
{
    return m_getter.pViSession;
}

template <>
inline AttributeGetterViString AttributeInfo::Getter() const
{
    return m_getter.pViString;
}

template <>
inline AttributeSetter<ViInt32> AttributeInfo::Setter() const
{
    return m_setter.pViInt32;
}

template <>
inline AttributeSetter<ViInt64> AttributeInfo::Setter() const
{
    return m_setter.pViInt64;
}

template <>
inline AttributeSetter<ViReal64> AttributeInfo::Setter() const
{
    return m_setter.pViReal64;
}

template <>
inline AttributeSetter<ViBoolean> AttributeInfo::Setter() const
{
    return m_setter.pViBoolean;
}

template <>
inline AttributeSetter<ViSession> AttributeInfo::Setter() const
{
    return m_setter.pViSession;
}

template <>
inline AttributeSetter<ViConstString> AttributeInfo::Setter() const
{
    return m_setter.pViString;
}

///////////////////////////////////////////////////////////////////////////////
// Repeated capability support - Functions common to nested and non-nested repcaps
//

// This custom type traits class helps enforce, at compile time, the parent-child relationships of repcap classes.  This
// ensures that certain functions cannot be called with improperly related repcaps.
//
template <typename T, typename U>
struct IsDescendantOf
{
    static const bool value = (std::is_same<T::Parent, U>::value || IsDescendantOf<T::Parent, U>::value);
};

template <typename T>
struct IsDescendantOf < T, nullptr_t >
{
    static const bool value = false;
};

template <typename U>
struct IsDescendantOf < nullptr_t, U >
{
    static const bool value = false;
};

// PhysicalName name specialization used for non-nested repcaps
//
template <typename TRepCap>
inline PhysicalName<TRepCap, typename std::enable_if<HasNoParent<TRepCap>::value>::type>::PhysicalName(const char* szName)
    : PhysicalName(std::string(szName))
{
}

template <typename TRepCap>
inline PhysicalName<TRepCap, typename std::enable_if<HasNoParent<TRepCap>::value>::type>::PhysicalName(std::string strName)
    : m_strName(strName)
{
    if (!m_strName.empty())
    {
        m_strQualifiedName = TRepCap::Name() + "!!" + Name();
    }
}

template <typename TRepCap>
inline const char* PhysicalName<TRepCap, typename std::enable_if<HasNoParent<TRepCap>::value>::type>::Name() const
{
    return m_strName.c_str();
}

template <typename TRepCap>
inline const char* PhysicalName<TRepCap, typename std::enable_if<HasNoParent<TRepCap>::value>::type>::FullName() const
{
    return Name();
}

template <typename TRepCap>
inline int PhysicalName<TRepCap, typename std::enable_if<HasNoParent<TRepCap>::value>::type>::Index(ViSession Vi) const
{
    const auto& names = ParentList(Vi);

    const auto& it = std::find(std::begin(names), std::end(names), *this);

    return (it != std::end(names)) ? static_cast<int>(it - std::begin(names)) : -1;
}

template <typename TRepCap>
inline const char* PhysicalName<TRepCap, typename std::enable_if<HasNoParent<TRepCap>::value>::type>::QualifiedName() const
{
    return m_strQualifiedName.c_str();
}

template <typename TRepCap>
inline const char* PhysicalName<TRepCap, typename std::enable_if<HasNoParent<TRepCap>::value>::type>::QualifiedFullName() const
{
    return QualifiedName();
}

template <typename TRepCap>
inline const char* PhysicalName<TRepCap, typename std::enable_if<HasNoParent<TRepCap>::value>::type>::ExportedName() const
{
    return TRepCap::UseQualifiedPhysicalNames ? QualifiedName() : Name();
}

template <typename TRepCap>
inline const char* PhysicalName<TRepCap, typename std::enable_if<HasNoParent<TRepCap>::value>::type>::ExportedFullName() const
{
    return ExportedName();
}

template <typename TRepCap>
inline const PhysicalNameList<TRepCap>& PhysicalName<TRepCap, typename std::enable_if<HasNoParent<TRepCap>::value>::type>::ParentList(ViSession Vi) const
{
    return TRepCap::GetPhysicalNames(Vi);
}

template <typename TRepCap>
inline bool PhysicalName<TRepCap, typename std::enable_if<HasNoParent<TRepCap>::value>::type>::IsDefined(ViSession Vi) const
{
    return Index(Vi) >= 0;
}

template <typename TRepCap>
inline bool PhysicalName<TRepCap, typename std::enable_if<HasNoParent<TRepCap>::value>::type>::operator==(const PhysicalName<TRepCap>& other) const
{
    return m_strQualifiedName == other.m_strQualifiedName;
}

template <typename TRepCap>
inline bool PhysicalName<TRepCap, typename std::enable_if<HasNoParent<TRepCap>::value>::type>::operator!=(const PhysicalName<TRepCap>& other) const
{
    return !(*this == other);
}

template <typename TRepCap>
inline bool PhysicalName<TRepCap, typename std::enable_if<HasNoParent<TRepCap>::value>::type>::operator<(const PhysicalName<TRepCap>& other) const
{
    return m_strQualifiedName < other.m_strQualifiedName;
}

template <typename TRepCap>
inline bool PhysicalName<TRepCap, typename std::enable_if<HasNoParent<TRepCap>::value>::type>::operator>(const PhysicalName<TRepCap>& other) const
{
    return other < *this;
}

template <typename TRepCap>
inline bool PhysicalName<TRepCap, typename std::enable_if<HasNoParent<TRepCap>::value>::type>::operator<=(const PhysicalName<TRepCap>& other) const
{
    return !(*this > other);
}

template <typename TRepCap>
inline bool PhysicalName<TRepCap, typename std::enable_if<HasNoParent<TRepCap>::value>::type>::operator>=(const PhysicalName<TRepCap>& other) const
{
    return !(*this < other);
}

// PhysicalName name specialization used for nested repcaps
//
template <typename TRepCap, typename Nested>
inline PhysicalName<TRepCap, Nested>::PhysicalName(const char* szFullName)
    : PhysicalName(std::string(szFullName))
{
}

template <typename TRepCap, typename Nested>
inline PhysicalName<TRepCap, Nested>::PhysicalName(std::string strFullName)
    : m_strFullName(strFullName)
{
    if (!strFullName.empty())
    {
        m_vecNameParts = Split(strFullName, ':');
        assert(m_vecNameParts.size() == (TRepCap::NestingLevel + 1) && "Wrong number of levels in physical name.");

        m_strQualifiedName = TRepCap::Name() + "!!" + Name();

        PhysicalName<TRepCap::Parent> parentName(ParentFullName());
        m_strQualifiedFullName = std::string(parentName.QualifiedFullName()) + ':' + QualifiedName();
        m_strExportedFullName = std::string(parentName.ExportedFullName()) + ':' + ExportedName();
    }
}

template <typename TRepCap, typename Nested>
inline const char* PhysicalName<TRepCap, Nested>::Name() const
{
    return m_vecNameParts.back().c_str();
}

template <typename TRepCap, typename Nested>
inline const char* PhysicalName<TRepCap, Nested>::ParentName() const
{
    return AncestorName<TRepCap::Parent>();
}

template <typename TRepCap, typename Nested>
template <typename TAncestor>
inline const char* PhysicalName<TRepCap, Nested>::AncestorName() const
{
    static_assert(IsDescendantOf<TRepCap, TAncestor>::value, "AncestorName function used on a repcap that is not an ancestor.");

    // This function extracts a portion of a nested repcap physical name.  For example, consider a physical name
    // such as "C2:M4:T5".  The parent name "M4" or grand-parent name "C2" can be extracted
    // using this function.
    //
    if (m_strFullName.empty())
    {
        return m_strFullName.c_str();
    }

    auto nAncestorNestingLevel = TAncestor::NestingLevel;
    assert(nAncestorNestingLevel < (int)m_vecNameParts.size());

    if (nAncestorNestingLevel < (int)m_vecNameParts.size())
    {
        return m_vecNameParts[nAncestorNestingLevel].c_str();
    }

    return nullptr;
}

template <typename TRepCap, typename Nested>
inline const char* PhysicalName<TRepCap, Nested>::FullName() const
{
    return m_strFullName.c_str();
}

template <typename TRepCap, typename Nested>
inline std::string PhysicalName<TRepCap, Nested>::ParentFullName() const
{
    return AncestorFullName<TRepCap::Parent>();
}

template <typename TRepCap, typename Nested>
template <typename TAncestor>
std::string PhysicalName<TRepCap, Nested>::AncestorFullName() const
{
    auto cColons = TAncestor::NestingLevel + 1;
    auto it = std::find_if(std::begin(m_strFullName), std::end(m_strFullName), [&](char c)
    {
        return c == ':' && (--cColons == 0);
    });

    assert(it != std::end(m_strFullName));

    if (it != std::end(m_strFullName))
    {
        return std::string(std::begin(m_strFullName), it);
    }

    return std::string();
}

template <typename TRepCap, typename Nested>
inline int PhysicalName<TRepCap, Nested>::Index(ViSession Vi) const
{
    const auto& names = ParentList(Vi);

    const auto& it = std::find(std::begin(names), std::end(names), *this);

    return (it != std::end(names)) ? static_cast<int>(it - std::begin(names)) : -1;
}

template <typename TRepCap, typename Nested>
template <typename TAncestor>
inline int PhysicalName<TRepCap, Nested>::AncestorIndex(ViSession Vi) const
{
    auto szFullName = AncestorFullName<TAncestor>();

    PhysicalName<TAncestor> name(szFullName);

    return name.Index(Vi);
}

template <typename TRepCap, typename Nested>
inline const char* PhysicalName<TRepCap, Nested>::QualifiedName() const
{
    return m_strQualifiedName.c_str();
}

template <typename TRepCap, typename Nested>
inline const char* PhysicalName<TRepCap, Nested>::QualifiedFullName() const
{
    return m_strQualifiedFullName.c_str();
}

template <typename TRepCap, typename Nested>
inline const char* PhysicalName<TRepCap, Nested>::ExportedName() const
{
    return TRepCap::UseQualifiedPhysicalNames ? QualifiedName() : Name();
}

template <typename TRepCap, typename Nested>
inline const char* PhysicalName<TRepCap, Nested>::ExportedFullName() const
{
    return m_strExportedFullName.c_str();
}

template <typename TRepCap, typename Nested>
inline const PhysicalNameList<TRepCap>& PhysicalName<TRepCap, Nested>::ParentList(ViSession Vi) const
{
    return TRepCap::GetPhysicalNames(Vi, ParentFullName());
}

template <typename TRepCap, typename Nested>
inline bool PhysicalName<TRepCap, Nested>::IsDefined(ViSession Vi) const
{
    return Index(Vi) >= 0;
}

template <typename TRepCap, typename Nested>
inline bool PhysicalName<TRepCap, Nested>::operator==(const PhysicalName<TRepCap>& other) const
{
    return m_strQualifiedFullName == other.m_strQualifiedFullName;
}

template <typename TRepCap, typename Nested>
inline bool PhysicalName<TRepCap, Nested>::operator!=(const PhysicalName<TRepCap>& other) const
{
    return !(*this == other);
}

template <typename TRepCap, typename Nested>
inline bool PhysicalName<TRepCap, Nested>::operator<(const PhysicalName<TRepCap>& other) const
{
    return m_strQualifiedFullName < other.m_strQualifiedFullName;
}

template <typename TRepCap, typename Nested>
inline bool PhysicalName<TRepCap, Nested>::operator>(const PhysicalName<TRepCap>& other) const
{
    return other < *this;
}

template <typename TRepCap, typename Nested>
inline bool PhysicalName<TRepCap, Nested>::operator<=(const PhysicalName<TRepCap>& other) const
{
    return !(*this > other);
}

template <typename TRepCap, typename Nested>
inline bool PhysicalName<TRepCap, Nested>::operator>=(const PhysicalName<TRepCap>& other) const
{
    return !(*this < other);
}

template <typename T, typename TParent>
inline ViStatus RepCapBase<T, TParent>::ExpandSelector(ViSession Vi, ViConstString szSelector, PhysicalNameList<T>& physicalNames, bool bVerifyPhysicalNamesExist)
{
    // Selectors have a general form such as the following:
    //
    //		a1,a3,a5-a7:b2:[c5,c7]
    //
    // The formal syntax for repeated capability selectors is given in IVI 3.1 Section 4.4.7 Formal Syntax for Repeated Capability Selectors.
    // 
    // The following describes the formal syntax for repeated capability selectors:
    //
    //	-	A syntactically valid repeated capability selector consists of zero or more repeated capability path segments separated by colons (:).  
    //		White space around colons is ignored.
    // 
    //	-	A repeated capability path segment consists of one or more repeated capability list elements, separated by commas (,).  
    //		White space after commas is ignored.  A repeated capability path segment may be enclosed in square brackets ([]).
    //
    //	-	A repeated capability list element consists of a repeated capability token or a repeated capability range.
    //
    //	-	A repeated capability range consists of two repeated capability tokens separated by a hyphen (-).
    //
    //	-	The order of precedence of operators is square brackets ([]), hyphen (-), colon (:), and comma (,).  Each operator is evaluated from left to right.  
    //
    //	-	A repeated capability token is a physical repeated capability identifer or a virtual repeated capability identifier. 
    //
    //	-	A syntactically valid physical or virtual repeated capability identifier consists of one or more of the following characters: a z, A Z, 0 9, !, and _.  
    //
    auto status = VI_SUCCESS;

    const auto& strSelector = (szSelector != nullptr) ? std::string(szSelector) : std::string();

    // A null or empty selector can be specified if there is only one defined repcap identifier for this repcap
    //
    if (strSelector.empty() || IsWhitespace(strSelector))
    {
        // A null or empty selector was specified, so make sure there is only one repcap identifier
        //
        if (T::PhysicalNameCount(Vi) != 1)
        {
            return ReportErrorEx(Vi, IVIC_ERROR_CHANNEL_NAME_REQUIRED,
                "No selector was specified for repeated capability '%s'.  "
                "The repeated capability identifier can be null or empty only when there is exactly one physical name defined.  "
                "Repeated capability '%s' has %d physical names defined.",
                T::Name().c_str(), T::Name().c_str(), T::PhysicalNameCount(Vi));
        }

        physicalNames.push_back(T::FirstPhysicalName(Vi));

        return status;
    }

    status = ValidateSelectorSyntax(Vi, strSelector);
    ReturnOnError(status);

    // Replace any virtual identifiers using the expansion and virtual name substitution rules as described in IVI-3.1.
    // Note that we validate the selector again after substitution, just in case the virtual name replacement introduced
    // a syntax error of some sort.
    //
    auto strExpandedSelector = ReplaceVirtualNames(Vi, strSelector);

    if (strExpandedSelector != strSelector)
    {
        status = ValidateSelectorSyntax(Vi, strExpandedSelector);
        ReturnOnError(status);
    }

    // First, parse the selector into path segments, so that we can perform a second pass that expands ranges and applies the 
    // nesting rules (e.g. square bracketing).  We do this in two passes, since it requires look-ahead in the general case.
    //
    std::vector<PathSegment> vecPathSegments;

    for (auto& strPathSegment : Split(strExpandedSelector, ':', true))
    {
        PathSegment segment;
        segment.IsEnclosedInBrackets = strPathSegment[0] == '[';

        if (segment.IsEnclosedInBrackets)
        {
            strPathSegment = strPathSegment.substr(1, strPathSegment.length() - 2);
        }

        for (const auto& strListElement : Split(strPathSegment, ',', true))
        {
            ListElement element;
            element.Text = strListElement;

            if (strListElement.find('-') != std::string::npos)
            {
                // This is a range of identifiers
                //
                element.IsRange = true;
                status = ExpandRange(Vi, strListElement, element.Identifiers);
                ReturnOnError(status);
            }
            else
            {
                // This is a single identifier
                //
                element.Identifiers.push_back(strListElement);
            }

            // Make sure none of the identifiers in this range overlap with other identifiers in this path segment
            //
            for (const auto& existingElement : segment.ListElements)
            {
                for (const auto& strIdentifier : element.Identifiers)
                {
                    if (std::find(std::begin(existingElement.Identifiers), std::end(existingElement.Identifiers), strIdentifier) != std::end(existingElement.Identifiers))
                    {
                        if (element.IsRange || existingElement.IsRange)
                        {
                            return ReportErrorEx(Vi, IVIC_ERROR_INVALID_RANGE_IN_SELECTOR, "An identifier in the range overlaps with another range.", strListElement.c_str(), T::Name().c_str());
                        }
                        else
                        {
                            return ReportError(Vi, IVIC_ERROR_BADLY_FORMED_SELECTOR);
                        }
                    }
                }
            }

            segment.ListElements.push_back(element);
        }

        vecPathSegments.push_back(segment);
    }

    // Now process the parsed paths and segments to create the flattened list of (possibly nested) identifiers
    //
    std::set<std::string> setChildListElements;

    for (auto& itPathSegment = std::begin(vecPathSegments); itPathSegment != std::end(vecPathSegments); ++itPathSegment)
    {
        for (auto& itListElement = std::begin(itPathSegment->ListElements); itListElement != std::end(itPathSegment->ListElements); ++itListElement)
        {
            if (setChildListElements.find(itListElement->Text) == std::end(setChildListElements))
            {
                for (const auto& strIdentifier : ExpandListElement(itListElement, itPathSegment, vecPathSegments, setChildListElements))
                {
                    // Ensure that the number of levels in each physical name matches the nesting level of the repcap
                    //
                    if (std::count(std::begin(strIdentifier), std::end(strIdentifier), ':') != T::NestingLevel)
                    {
                        return ReportError(Vi, IVIC_ERROR_INVALID_NUMBER_OF_LEVELS_IN_SELECTOR, T::Name().c_str());
                    }

                    PhysicalName<T> physicalName(strIdentifier);

                    if (bVerifyPhysicalNamesExist)
                    {
                        // Ensure the physical name is defined for the repcap
                        //
                        if (!physicalName.IsDefined(Vi))
                        {
                            return ReportErrorEx(Vi, IVIC_ERROR_UNKNOWN_PHYSICAL_IDENTIFIER, "The identifier '%s' is not defined for repeated capability '%s'.", physicalName.FullName(), T::Name().c_str());
                        }
                    }

                    physicalNames.push_back(physicalName);
                }
            }
        }
    }

    return status;
}

template <typename T, typename TParent>
inline std::string RepCapBase<T, TParent>::ReplaceVirtualNames(ViSession Vi, const std::string& strSelector)
{
    if (Vi == VI_NULL)
    {
        return strSelector;
    }

    std::string strExpandedSelector;
    static const std::regex rx("[\\w_!]+", std::regex_constants::optimize);

    for (auto it = std::sregex_iterator(std::begin(strSelector), std::end(strSelector), rx); it != std::sregex_iterator(); ++it)
    {
        auto match = *it;
        auto strPhysicalName = TranslateVirtualName(Vi, match.str());

        // The "physicalName" mapped from this one virtual identifier could be a comma-separated list of physical identifiers, or a range
        // of physical identifiers, or a nested physical identifier.  For example, all of the following are valid:
        //		"CH1"
        //		"CH1-CH3"
        //		"CH1:TRACE2"
        //		"CH1,CH2,CH3"

        // If it's a comma-separated list and it's not nested, then enclose it in square brackets
        //
        if ((strPhysicalName.find(',') != std::string::npos) && (strPhysicalName.find(':') == std::string::npos))
        {
            strPhysicalName = '[' + strPhysicalName + ']';
        }

        strExpandedSelector += match.prefix().str() + strPhysicalName;

        // If this is the last match, then we need to tack on any additional characters following the match, such as square brackets
        //
        if (std::next(it) == std::sregex_iterator())
        {
            strExpandedSelector += match.suffix().str();
        }
    }

    return strExpandedSelector;
}

template <typename T, typename TParent>
inline PhysicalNameList<T> RepCapBase<T, TParent>::Initialize(ViConstString szSelector)
{
    PhysicalNameList<T> physicalNames;

    // It is critical NOT to call ExpandSelector if the supplied selector is empty, else we end up in an infinite 
    // loop.  The supplied selector will be empty if there are no static physical names (i.e. a purely dynamic 
    // repcap).
    //
    if (szSelector != nullptr)
    {
        const auto strSelector = std::string(szSelector);

        if (!strSelector.empty() && !IsWhitespace(strSelector))
        {
            auto status = ExpandSelector(VI_NULL, szSelector, physicalNames, false);
            assert(status >= 0);
        }
    }

    g_vecPhysicalNameCleanupFunctions.push_back([&](ViSession Vi)
    {
        T::ClearPhysicalNames(Vi);
        m_setInitializedSessions.erase(Vi);
    });

    return physicalNames;
}

template <typename T, typename TParent>
inline ViStatus RepCapBase<T, TParent>::EnsurePhysicalNamesInitializedForSession(ViSession Vi)
{
    ViStatus status = VI_SUCCESS;

    const auto& it = m_setInitializedSessions.find(Vi);

    if (it == std::end(m_setInitializedSessions))
    {
        // The map has not been initialized yet for this session.  So, we add the static physical names.
        //
        T::InitializePhysicalNamesForSession(Vi);

        m_setInitializedSessions.insert(Vi);
    }

    return status;
}

template <typename T, typename TParent>
inline std::vector<std::string> RepCapBase<T, TParent>::ExpandListElement(const std::vector<ListElement>::iterator& itListElement, const std::vector<PathSegment>::iterator& itPathSegment, const std::vector<PathSegment>& vecPathSegments, std::set<std::string>& setChildListElements)
{
    std::vector<std::string> vecIdentifiers;

    if (ListElementHasChildIdentifiers(itListElement, itPathSegment, vecPathSegments))
    {
        // The element has child identifiers, so we build the nested identifier by concatenating each identifier in the current element with
        // each identifier (and its children) in the next path segment.
        //
        for (const auto& strIdentifier : itListElement->Identifiers)
        {
            for (const auto& strChildIdentifier : GetChildIdentifiersInPathSegment(std::next(itPathSegment), vecPathSegments, setChildListElements))
            {
                vecIdentifiers.push_back(strIdentifier + ':' + strChildIdentifier);
            }
        }
    }
    else
    {
        // The element has no child identifiers, so just add the identifiers represented by the list element itself
        //
        vecIdentifiers.insert(std::end(vecIdentifiers), std::begin(itListElement->Identifiers), std::end(itListElement->Identifiers));
    }

    return vecIdentifiers;
}

template <typename T, typename TParent>
inline bool RepCapBase<T, TParent>::ListElementHasChildIdentifiers(const std::vector<ListElement>::iterator& itListElement, const std::vector<PathSegment>::iterator& itPathSegment, const std::vector<PathSegment>& vecPathSegments)
{
    // This list element has child identifiers if there are path segments after this one AND the current path segment is either enclosed
    // in brackets or the list element is the last list element in the current path segment.
    //
    // Examples:
    //		a1,a2,a3:b1,b2,b3		=>	"a3" has child identifier "b1"
    //		[a1,a2,a3]:b1,b2,b3		=>	"a1", "a2" and "a3" all have "b1" as a child identifier
    //
    return (std::next(itPathSegment) != std::end(vecPathSegments)) &&
        (itPathSegment->IsEnclosedInBrackets || (std::next(itListElement) == std::end(itPathSegment->ListElements)));
}

template <typename T, typename TParent>
inline std::vector<std::string> RepCapBase<T, TParent>::GetChildIdentifiersInPathSegment(const std::vector<PathSegment>::iterator& itPathSegment, const std::vector<PathSegment>& vecPathSegments, std::set<std::string>& setChildListElements)
{
    std::vector<std::string> vecIdentifiers;

    if (itPathSegment->IsEnclosedInBrackets)
    {
        // Return all list elements (and their children) in the path segment.  This enforces the precedence rules for selectors whereby 
        // square  brackets have higher precedence than commas.  In the example below, this would occur when we encounter the path 
        // "[b1,b2,b3]".  This would produce three nested identifiers: "a3:b1:c1", "a3:b2:c1", and "a3:b3:c1"
        //
        // Example: a1,a2,a3:[b1,b2,b3]:c1,c2,c3
        //                    ^  ^  ^
        //
        for (auto& itListElement = std::begin(itPathSegment->ListElements); itListElement != std::end(itPathSegment->ListElements); ++itListElement)
        {
            if (setChildListElements.find(itListElement->Text) == std::end(setChildListElements))
            {
                setChildListElements.insert(itListElement->Text);
            }

            for (const auto& strIdentifier : ExpandListElement(itListElement, itPathSegment, vecPathSegments, setChildListElements))
            {
                vecIdentifiers.push_back(strIdentifier);
            }
        }
    }
    else
    {
        // Only the first list element is part of the nested identifier.  In the example below, this would occur when we encounter the path
        // "b1,b2,b3".  Only the identifier "b1" is part of the nested identifier "a3:b1".
        //
        // Example: a1,a2,a3:b1,b2,b3:c1,c2,c3
        //                   ^
        //
        const auto& itFirstListElement = std::begin(itPathSegment->ListElements);

        if (setChildListElements.find(itFirstListElement->Text) == std::end(setChildListElements))
        {
            setChildListElements.insert(itFirstListElement->Text);
        }

        for (const auto& strIdentifier : ExpandListElement(itFirstListElement, itPathSegment, vecPathSegments, setChildListElements))
        {
            vecIdentifiers.push_back(strIdentifier);
        }
    }

    return vecIdentifiers;
}

template <typename T, typename TParent>
inline ViStatus RepCapBase<T, TParent>::ExpandRange(ViSession Vi, const std::string& strRange, std::vector<std::string>& vecIdentifiers)
{
    ViStatus status = VI_SUCCESS;

    static const std::regex rx("^\\s*([a-z_!]+)([0-9]+)\\s*-\\s*\\1([0-9]+)$", std::regex_constants::icase | std::regex_constants::optimize);

    std::smatch match;

    if (!std::regex_match(strRange, match, rx))
    {
        return ReportErrorEx(Vi, IVIC_ERROR_INVALID_RANGE_IN_SELECTOR, "The base names do not match.", strRange.c_str(), T::Name().c_str());
    }

    const auto strBaseName = match[1].str();
    const auto nLowerIndex = std::stoi(match[2].str());
    const auto nUpperIndex = std::stoi(match[3].str());

    if (nLowerIndex >= nUpperIndex)
    {
        return ReportErrorEx(Vi, IVIC_ERROR_INVALID_RANGE_IN_SELECTOR, "The start index must be less than the end index.", strRange.c_str(), T::Name().c_str());
    }

    for (int i = nLowerIndex; i <= nUpperIndex; i++)
    {
        vecIdentifiers.push_back(strBaseName + std::to_string(i));
    }

    return status;
}

template <typename T, typename TParent>
inline ViStatus RepCapBase<T, TParent>::ValidateSelectorSyntax(ViSession Vi, const std::string& strSelector)
{
    // Note that this function only validates that the selector is syntactically correct.  This simplifies further
    // downstream processing of the selector.  It does not catch errors such as overlapping or descending ranges.
    //
    auto status = VI_SUCCESS;

    // Identifiers are alphanumerics plus the underscore character
    //
    // Example: "CH1"
    //
    static const std::string strIdentifierPattern = "\\s*[\\w_!]+";

    // Ranges consist of a pair of identifiers separated by a hyphen where each identifier ends in a digit
    //
    // Example: "CH1-CH3"
    //
    static const std::string strRangePattern = "(?:\\s*[a-z_!]+[0-9]+\\s*-\\s*[a-z_!]+[0-9]+)";

    // Path segments are comma-delimited lists of ranges and identifiers
    //
    // Example: CH1,CH2,CH3-CH6,CH9
    //
    static const std::string strPathSegmentPattern = "(?:" + strRangePattern + "|" + strIdentifierPattern + ")" + "(?:\\s*,(?:" + strRangePattern + "|" + strIdentifierPattern + "))*";

    // Selectors are colon-delimited lists of path segments, where each path segment is optionally enclosed
    // in square brackets.  Note we anchor to the beginning and end of the string in order to match entire string.
    //
    static const std::string strSelectorPattern = "^(?:\\s*\\[?" + strPathSegmentPattern + "\\s*\\]?)" + "(?:\\s*:\\s*\\[?" + strPathSegmentPattern + "\\s*\\]?)*$";

    static const std::regex rx(strSelectorPattern, std::regex_constants::icase | std::regex_constants::optimize);

    std::smatch match;

    if (!std::regex_match(strSelector, match, rx))
    {
        status = ReportError(Vi, IVIC_ERROR_BADLY_FORMED_SELECTOR);
    }

    return status;
}

template <typename T, typename TParent>
inline ViStatus RepCapBase<T, TParent>::ExpandSingleSelector(ViSession Vi, ViConstString szSelector, PhysicalName<T>& physicalName)
{
    auto status = VI_SUCCESS;

    PhysicalNameList<T> physicalNames;
    status = ExpandSelector(Vi, szSelector, physicalNames);
    ReturnOnError(status);

    if (physicalNames.size() > 1)
    {
        return ReportErrorEx(Vi, IVIC_ERROR_BADLY_FORMED_SELECTOR, "Only a single repeated capability identifier can be specified for the current operation.");
    }

    physicalName = physicalNames[0];

    return status;
}

template <typename T, typename TParent>
inline ViStatus RepCapBase<T, TParent>::AddPhysicalNames(ViSession Vi, const std::string& strSelector)
{
    auto status = VI_SUCCESS;

    PhysicalNameList<T> namesToAdd;
    status = ExpandSelector(Vi, strSelector.c_str(), namesToAdd, false);
    ReturnOnError(status);

    for (const auto& nameToAdd : namesToAdd)
    {
        status = T::AddPhysicalName(Vi, nameToAdd);

        if (status < 0)
        {
            break;
        }
    }

    return status;
}

template <typename T, typename TParent>
inline ViStatus RepCapBase<T, TParent>::RemovePhysicalNames(ViSession Vi, const std::string& strSelector)
{
    auto status = VI_SUCCESS;

    PhysicalNameList<T> namesToRemove;
    status = ExpandSelector(Vi, strSelector.c_str(), namesToRemove, false);
    ReturnOnError(status);

    for (const auto& nameToRemove : namesToRemove)
    {
        T::RemovePhysicalName(Vi, nameToRemove);
    }

    return status;
}

///////////////////////////////////////////////////////////////////////////////
// Repeated capability support - Functions specific to nested repcaps
//
template <typename T, typename TParent>
inline ViStatus RepCap<T, TParent>::InitializePhysicalNamesForSession(ViSession Vi)
{
    ViStatus status = VI_SUCCESS;

    for (auto& physicalName : T::StaticPhysicalNames())
    {
        m_mapPhysicalNames[Vi][physicalName.ParentFullName()].push_back(physicalName);
    }

    return status;
}

template <typename T, typename TParent>
inline int RepCap<T, TParent>::PhysicalNameCount(ViSession Vi)
{
    size_t cNames = 0;

    for (const auto& it : GetPhysicalNameMap(Vi))
    {
        cNames += it.second.size();
    }

    return static_cast<int>(cNames);
}

template <typename T, typename TParent>
inline PhysicalName<T> RepCap<T, TParent>::FirstPhysicalName(ViSession Vi)
{
    const auto& map = GetPhysicalNameMap(Vi);
    assert(map.size() > 0);

    if (map.size() > 0)
    {
        const auto& names = std::begin(map)->second;
        assert(names.size() > 0);

        if (names.size() > 0)
        {
            return names.front();
        }
    }

    return std::string();
}

template <typename T, typename TParent>
inline const PhysicalNameList<T>& RepCap<T, TParent>::GetPhysicalNames(ViSession Vi, const PhysicalName<TParent>& parentPhysicalName)
{
    return GetMutablePhysicalNames(Vi, parentPhysicalName);
}

template <typename T, typename TParent>
inline PhysicalNameList<T>& RepCap<T, TParent>::GetMutablePhysicalNames(ViSession Vi, const PhysicalName<TParent>& parentPhysicalName)
{
    return GetPhysicalNameMap(Vi)[parentPhysicalName];
}

template <typename T, typename TParent>
inline PhysicalNameMap<T, TParent>& RepCap<T, TParent>::GetPhysicalNameMap(ViSession Vi)
{
    EnsurePhysicalNamesInitializedForSession(Vi);

    return m_mapPhysicalNames[Vi];
}

template <typename T, typename TParent>
inline ViStatus RepCap<T, TParent>::GetPhysicalNameAtIndex(ViSession Vi, ViConstString parentPhysicalName, ViInt32 nIndex, ViInt32 nNameBufferSize, ViChar szName[])
{
    auto status = VI_SUCCESS;

    const auto& names = GetPhysicalNames(Vi, parentPhysicalName);

    if ((nIndex < 0) || (nIndex >= (int)names.size()))
    {
        return ReportInvalidValueError(Vi, nIndex, "Get" + T::Name() + "Name", "Index");
    }

    strncpy_s(szName, nNameBufferSize, names[nIndex].ExportedName(), _TRUNCATE);

    return status;
}

template <typename T, typename TParent>
inline void RepCap<T, TParent>::ClearPhysicalNames(ViSession Vi)
{
    m_mapPhysicalNames.erase(Vi);
}

template <typename T, typename TParent>
inline ViStatus RepCap<T, TParent>::AddPhysicalName(ViSession Vi, const PhysicalName<T>& physicalName)
{
    auto status = VI_SUCCESS;

    auto& names = GetMutablePhysicalNames(Vi, physicalName.ParentFullName());

    if (std::find(std::begin(names), std::end(names), physicalName) != std::end(names))
    {
        return ReportErrorEx(Vi, IVIC_ERROR_BADLY_FORMED_SELECTOR, "Physical name '%s' already exists for repeated capability '%s'.", physicalName.FullName(), T::Name().c_str());
    }

    names.push_back(physicalName);

    return status;
}

template <typename T, typename TParent>
inline ViStatus RepCap<T, TParent>::RemovePhysicalName(ViSession Vi, const PhysicalName<T>& physicalName)
{
    auto status = VI_SUCCESS;

    auto& names = GetMutablePhysicalNames(Vi, physicalName.ParentFullName());
    auto& it = std::find(std::begin(names), std::end(names), physicalName);

    if (it != std::end(names))
    {
        names.erase(it);
    }

    return status;
}

template <typename T, typename TParent>
std::map<ViSession, PhysicalNameMap<T>> RepCap<T, TParent>::m_mapPhysicalNames;

///////////////////////////////////////////////////////////////////////////////
// Repeated capability support - Functions specific to non-nested repcaps
//
template <typename T>
inline ViStatus RepCap<T, nullptr_t>::InitializePhysicalNamesForSession(ViSession Vi)
{
    ViStatus status = VI_SUCCESS;

    m_mapPhysicalNames[Vi] = T::StaticPhysicalNames();

    return status;
}

template <typename T>
inline int RepCap<T, nullptr_t>::PhysicalNameCount(ViSession Vi)
{
    return static_cast<int>(GetPhysicalNames(Vi).size());
}

template <typename T>
inline PhysicalName<T> RepCap<T, nullptr_t>::FirstPhysicalName(ViSession Vi)
{
    const auto& names = GetPhysicalNames(Vi);

    assert(names.size() > 0);

    if (names.size() > 0)
    {
        return names[0];
    }

    return std::string();
}

template <typename T>
inline const PhysicalNameList<T>& RepCap<T, nullptr_t>::GetPhysicalNames(ViSession Vi)
{
    return GetMutablePhysicalNames(Vi);
}

template <typename T>
inline PhysicalNameList<T>& RepCap<T, nullptr_t>::GetMutablePhysicalNames(ViSession Vi)
{
    EnsurePhysicalNamesInitializedForSession(Vi);

    return m_mapPhysicalNames[Vi];
}

template <typename T>
inline ViStatus RepCap<T, nullptr_t>::GetPhysicalNameAtIndex(ViSession Vi, ViInt32 nIndex, ViInt32 nNameBufferSize, ViChar szName[])
{
    auto status = VI_SUCCESS;

    const auto& names = GetPhysicalNames(Vi);

    if ((nIndex < 0) || (nIndex >= (int)names.size()))
    {
        return ReportInvalidValueError(Vi, nIndex, "Get" + T::Name() + "Name", "Index");
    }

    strncpy_s(szName, nNameBufferSize, names[nIndex].ExportedName(), _TRUNCATE);

    return status;
}

template <typename T>
inline void RepCap<T, nullptr_t>::ClearPhysicalNames(ViSession Vi)
{
    m_mapPhysicalNames.erase(Vi);
}

template <typename T>
inline ViStatus RepCap<T, nullptr_t>::AddPhysicalName(ViSession Vi, const PhysicalName<T>& physicalName)
{
    auto status = VI_SUCCESS;

    auto& names = GetMutablePhysicalNames(Vi);

    if (std::find(std::begin(names), std::end(names), physicalName) != std::end(names))
    {
        return ReportErrorEx(Vi, IVIC_ERROR_BADLY_FORMED_SELECTOR, "Physical name '%s' already exists for repeated capability '%s'.", physicalName.FullName(), T::Name().c_str());
    }

    names.push_back(physicalName);

    return status;
}

template <typename T>
inline ViStatus RepCap<T, nullptr_t>::RemovePhysicalName(ViSession Vi, const PhysicalName<T>& physicalName)
{
    auto status = VI_SUCCESS;

    auto& names = GetMutablePhysicalNames(Vi);
    auto& it = std::find(std::begin(names), std::end(names), physicalName);

    if (it != std::end(names))
    {
        names.erase(it);
    }

    return status;
}

template <typename T>
std::map<ViSession, PhysicalNameList<T>> RepCap<T, nullptr_t>::m_mapPhysicalNames;

///////////////////////////////////////////////////////////////////////////////
// Repeated capability support - Functions specific to selector-type repcaps
//
template <typename T>
inline ViStatus SelectorStyleRepCap<T>::ExpandActiveSelector(ViSession Vi, PhysicalNameList<T>& physicalNames)
{
    auto status = VI_SUCCESS;

    const auto& strActiveSelector = m_mapActiveSelectors[Vi];

    status = ExpandSelector(Vi, strActiveSelector.c_str(), physicalNames);

    // This should typically succeed because we should have caught any errors when the selector was set.  However, 
    // it is possible that some physical names were removed between the call to SetActive and this call.  That would
    // probably indicate a logic error in the user program.
    //
    assert(status >= 0);

    return status;
}

template <typename T>
inline ViStatus SelectorStyleRepCap<T>::ExpandSingleActiveSelector(ViSession Vi, PhysicalName<T>& physicalName)
{
    auto status = VI_SUCCESS;

    const auto& strActiveSelector = m_mapActiveSelectors[Vi];

    status = ExpandSingleSelector(Vi, strActiveSelector.c_str(), physicalName);
    assert(status >= 0);

    return status;
}

template <typename T>
inline ViStatus SelectorStyleRepCap<T>::SetActiveSelector(ViSession Vi, ViConstString szSelector)
{
    auto status = VI_SUCCESS;

    const std::string& strSelector = (szSelector != nullptr) ? std::string(szSelector) : std::string();

    // We perform an expansion here so that we can catch any errors as soon as the user sets the active selector
    //
    PhysicalNameList<T> names;
    status = ExpandSelector(Vi, strSelector.c_str(), names);

    if (status >= 0)
    {
        m_mapActiveSelectors[Vi] = strSelector;
        m_mapActivePhysicalNames[Vi] = names;
    }

    return status;
}

template <typename T>
inline ViStatus SelectorStyleRepCap<T>::GetActiveSelector(ViSession Vi, ViInt32 nSelectorBufferSize, ViChar szSelector[])
{
    auto status = VI_SUCCESS;

    strncpy_s(szSelector, nSelectorBufferSize, m_mapActiveSelectors[Vi].c_str(), _TRUNCATE);

    return status;
}

template <typename T>
inline ViStatus SelectorStyleRepCap<T>::GetActivePhysicalNames(ViSession Vi, PhysicalNameList<T>& physicalNames)
{
    auto status = VI_SUCCESS;

    physicalNames = m_mapActivePhysicalNames[Vi];

    return status;
}

template <typename T>
inline ViStatus SelectorStyleRepCap<T>::GetActivePhysicalName(ViSession Vi, PhysicalName<T>& physicalName)
{
    auto status = VI_SUCCESS;

    PhysicalNameList<T> names;
    status = GetActivePhysicalNames(Vi, names);

    if (status >= 0)
    {
        if (names.size() > 1)
        {
            return ReportErrorEx(Vi, IVIC_ERROR_BADLY_FORMED_SELECTOR, "Only a single repeated capability identifier can be specified for the current operation.");
        }

        physicalName = names[0];
    }

    return status;
}

template <typename T>
std::map<ViSession, std::string> SelectorStyleRepCap<T>::m_mapActiveSelectors;

template <typename T>
std::map<ViSession, PhysicalNameList<T>> SelectorStyleRepCap<T>::m_mapActivePhysicalNames;

///////////////////////////////////////////////////////////////////////////////
// Enum command support
//
template <typename T>
inline ViStatus EnumConverter<T>::ToCommand(ViSession Vi, ViInt32 nValue, std::string& strCommand)
{
    auto status = VI_SUCCESS;

    strCommand.clear();
    auto strModel = InstrumentModel(Vi);
    static auto commandMap = T::GetCommandMap();

    // Look for a model-specific entry that exactly matches the desired model
    //
    auto it = std::find_if(std::begin(commandMap), std::end(commandMap), [&](const CommandInfo& info)
    {
        return (info.Value == nValue) && (std::find(std::begin(info.Models), std::end(info.Models), strModel) != std::end(info.Models));
    });

    if (it == std::end(commandMap))
    {
        // No matching model-specific entry found, so look for a family-specific entry
        //
        it = std::find_if(std::begin(commandMap), std::end(commandMap), [&](const CommandInfo& info)
        {
            return (info.Value == nValue) && std::any_of(std::begin(info.Models), std::end(info.Models), [&](const std::string& strFamily)
            {
                return ModelInFamily(Vi, strModel, strFamily);
            });
        });

        if (it == std::end(commandMap))
        {
            // No matching family-specific entry found, so use the default entry
            //
            it = std::find_if(std::begin(commandMap), std::end(commandMap), [&](const CommandInfo& info)
            {
                return (info.Value == nValue) && info.Models.empty();
            });
        }
    }

    return (it != std::end(commandMap)) ?
        (strCommand = it->Commands[0], VI_SUCCESS) :
        ReportErrorEx(Vi, IVIC_ERROR_CANNOT_RECOVER, "Could not convert defined value '%d' to an instrument command.", nValue);
}

template <typename T>
inline ViStatus EnumConverter<T>::FromResponse(ViSession Vi, const std::string& strResponse, ViInt32* pnValue)
{
    auto status = VI_SUCCESS;

    *pnValue = -1;
    auto strModel = InstrumentModel(Vi);
    static auto commandMap = T::GetCommandMap();

    // We always use a case-insensitive comparer for instrument responses
    //
    static StringComparer responseComparer = [](const std::string& strA, const std::string& strB)
    {
        auto strATrimmed = nrt::TrimWhitespace(strA);
        auto strBTrimmed = nrt::TrimWhitespace(strB);

        return _stricmp(strATrimmed.c_str(), strBTrimmed.c_str()) == 0;
    };

    const CommandInfo* pBestMatch = nullptr;
    std::vector<ViInt32> vecModelMatches;

    for (const CommandInfo& info : commandMap)
    {
        auto bModelMatch = std::find(std::begin(info.Models), std::end(info.Models), strModel) != std::end(info.Models);
        auto bFamilyMatch = !bModelMatch && std::any_of(std::begin(info.Models), std::end(info.Models), [&](const std::string& strFamily)
        {
            return ModelInFamily(Vi, strModel, strFamily);
        });

        if (bModelMatch || bFamilyMatch)
        {
            vecModelMatches.push_back(info.Value);
        }

        if (std::any_of(std::begin(info.Commands), std::end(info.Commands), [&](const std::string& str)
        {
            return responseComparer(str, strResponse);
        }))
        {
            // We found an info with a matching response.  If it's an exact model match, then we're done.
            //
            if (bModelMatch)
            {
                return (*pnValue = info.Value), VI_SUCCESS;
            }
            else if (bFamilyMatch)
            {
                // We matched a family-specific info, so remember this one as a candidate.  A model-specific
                // info that appears later in the map will override this one.  We assert that we've not already
                // matched another family, as this indicates an error (ambiguity) in the map itself.
                //
                assert((pBestMatch == nullptr || pBestMatch->Models.empty()) && "Invalid enum command map.");
                pBestMatch = &info;
                continue;
            }
            else if (pBestMatch == nullptr && info.Models.empty())
            {
                // We didn't match either a model or a family, so this entry is a candidate only if it's the default 
                // and the best match is not already a family-based match.  
                //
                pBestMatch = &info;
            }
            else
            {
                // Assert that we've not already found a matching response in a default entry, as this indicates 
                // an error (ambiguity) in the map itself.
                //
                assert((pBestMatch == nullptr || !pBestMatch->Models.empty() || !info.Models.empty()) && "Invalid enum command map.");
            }
        }
    }

    // If the best match is a default entry (not model-specific), then it's only a valid match if no other model or family-specific
    // entry was found along the way for that same enum value.
    //
    if (pBestMatch != nullptr && pBestMatch->Models.empty() && std::find(std::begin(vecModelMatches), std::end(vecModelMatches), pBestMatch->Value) != std::end(vecModelMatches))
    {
        // We previously saw a model or family-specific entry for this value, so invalidate this match
        //
        pBestMatch = nullptr;
    }

    return (pBestMatch != nullptr) ?
        (*pnValue = pBestMatch->Value, VI_SUCCESS) :
        ReportErrorEx(Vi, IVIC_ERROR_UNEXPECTED_RESPONSE, "Could not convert instrument response (%s) to a defined value.", strResponse.c_str());
}

///////////////////////////////////////////////////////////////////////////////
// Enum member name conversion
//
template <typename T>
inline std::string EnumConverter<T>::MemberName(ViInt32 nValue)
{
    static auto commandMap = T::GetCommandMap();

    auto it = std::find_if(std::begin(commandMap), std::end(commandMap), [&](const CommandInfo& info)
    {
        return (info.Value == nValue);
    });

    // If the value is not defined for this enum, then just return the stringified number itself
    //
    return (it == std::end(commandMap)) ? std::to_string(nValue) : it->Name;
}

///////////////////////////////////////////////////////////////////////////////
// Session locking support
//
inline SessionLock::SessionLock(ViSession Vi)
    : m_session(Vi)
{
}

inline	SessionLock::~SessionLock()
{
    if (m_bObtainedLock)
    {
        auto status = IviSession_Unlock(m_session, VI_NULL);
        assert(status >= 0);
    }
}

inline ViStatus SessionLock::Obtain()
{
    auto status = IviSession_Lock(m_session, VI_NULL);
    assert(status >= 0);

    m_bObtainedLock = (status >= 0);

    return status;
}

///////////////////////////////////////////////////////////////////////////////
// Range checking support
//
template <typename T>
inline MinMaxRangeTableEntry<T>::MinMaxRangeTableEntry(T min, T max, MinMaxOptions options)
    : MinMaxRangeTableEntry(std::string(), min, max, options)
{
}

template <typename T>
inline MinMaxRangeTableEntry<T>::MinMaxRangeTableEntry(const std::string& strModelList, T min, T max, MinMaxOptions options)
    : ModelBasedType(strModelList), m_min(min), m_max(max), m_options(options)
{
}

template <typename T>
inline T MinMaxRangeTableEntry<T>::Min() const
{
    return m_min;
}

template <typename T>
inline T MinMaxRangeTableEntry<T>::Max() const
{
    return m_max;
}

template <typename T>
inline MinMaxOptions MinMaxRangeTableEntry<T>::Options() const
{
    return m_options;
}

template <typename T>
inline DiscreteRangeTableEntry<T>::DiscreteRangeTableEntry(T allowedValue)
    : DiscreteRangeTableEntry(std::string(), allowedValue)
{
}

#pragma warning (push)
#pragma warning (disable:4544)

template <typename T>
template <typename ...Args, typename = std::enable_if<!std::is_convertible<T, std::string>::value>::type>
inline DiscreteRangeTableEntry<T>::DiscreteRangeTableEntry(T allowedValue, Args... args)
    : DiscreteRangeTableEntry(std::string(), allowedValue, args...)
{
}

#pragma warning (pop)	// disable:4544

template <typename T>
inline DiscreteRangeTableEntry<T>::DiscreteRangeTableEntry(const std::string& strModelList, T allowedValue)
    : ModelBasedType(strModelList)
{
    AppendAllowedValues(allowedValue);
}

template <typename T>
template <typename ...Args>
inline DiscreteRangeTableEntry<T>::DiscreteRangeTableEntry(const std::string& strModelList, T allowedValue, Args... args)
    : ModelBasedType(strModelList)
{
    AppendAllowedValues(allowedValue, args...);
}

template <typename T>
inline const std::vector<T>& DiscreteRangeTableEntry<T>::AllowedValues() const
{
    return m_vecAllowedValues;
}

template <typename T>
inline void DiscreteRangeTableEntry<T>::AppendAllowedValues(T allowedValue)
{
    m_vecAllowedValues.push_back(allowedValue);
}

template <typename T>
template <typename ...Args>
inline void DiscreteRangeTableEntry<T>::AppendAllowedValues(T allowedValue, Args... args)
{
    AppendAllowedValues(allowedValue);
    AppendAllowedValues(args...);
}

template <typename T>
inline ViStatus _RangeCheckMinMax(ViSession Vi, T minValue, T maxValue, T value, MinMaxOptions options, const std::string& strFunctionName, const std::string& strParameterName)
{
    auto status = VI_SUCCESS;
    auto bInRange = false;

    switch (options)
    {
    case MinMaxOptions::IncludeMinAndMax:
        bInRange = (value > minValue || AreValuesEqual(value, minValue)) && (value < maxValue || AreValuesEqual(value, maxValue));
        break;

    case MinMaxOptions::ExcludeMin:
        bInRange = (value > minValue) && (value < maxValue || AreValuesEqual(value, maxValue));
        break;

    case MinMaxOptions::ExcludeMax:
        bInRange = (value > minValue || AreValuesEqual(value, minValue)) && (value < maxValue);
        break;

    case MinMaxOptions::ExcludeMinAndMax:
        bInRange = (value > minValue) && (value < maxValue);
        break;

    default:
        break;
    }

    if (!bInRange)
    {
        status = ReportInvalidValueError(Vi, value, strFunctionName, strParameterName);
    }

    return status;
}

template <typename TIterator, typename TValue>
inline ViStatus _RangeCheckMinMaxMultiModel(ViSession Vi, TIterator itFirst, TIterator itLast, const TValue& value, const std::string& strFunctionName, const std::string& strParameterName)
{
    auto status = VI_SUCCESS;
    auto strModel = InstrumentModel(Vi);

    const UnqualifiedElementType<TIterator>* pEntry = nullptr;
    status = GetRangeTableEntryForModel(Vi, itFirst, itLast, strModel, strFunctionName, strParameterName, &pEntry);

    if (status >= 0)
    {
        status = _RangeCheckMinMax(Vi, pEntry->Min(), pEntry->Max(), value, pEntry->Options(), strFunctionName, strParameterName);
    }

    return status;
}

template <typename TIterator>
inline ViStatus _RangeCheckDiscrete(ViSession Vi, TIterator itFirstAllowedValue, TIterator itLastAllowedValue, UnqualifiedElementType<TIterator>& value, CoercionStyle coercionStyle, const std::string& strFunctionName, const std::string& strParameterName)
{
    auto status = VI_SUCCESS;

    switch (coercionStyle)
    {
    case CoercionStyle::None:
    {
        if (!IsOneOf(itFirstAllowedValue, itLastAllowedValue, value))
        {
            status = ReportInvalidValueError(Vi, value, strFunctionName, strParameterName);
        }
        break;
    }

    case CoercionStyle::Up:
    {
        CoerceUp(Vi, itFirstAllowedValue, itLastAllowedValue, value, strFunctionName, strParameterName);
        break;
    }

    case CoercionStyle::Down:
    {
        CoerceDown(Vi, itFirstAllowedValue, itLastAllowedValue, value, strFunctionName, strParameterName);
        break;
    }

    default:
    {
        assert(!"Unexpected coercion style.");
        break;
    }
    }

    return status;
}

template <typename TIterator, typename TValue>
inline ViStatus _RangeCheckDiscreteMultiModel(ViSession Vi, TIterator itFirst, TIterator itLast, TValue& value, CoercionStyle coercionStyle, const std::string& strFunctionName, const std::string& strParameterName)
{
    auto status = VI_SUCCESS;
    auto strModel = InstrumentModel(Vi);

    const UnqualifiedElementType<TIterator>* pEntry = nullptr;
    status = GetRangeTableEntryForModel(Vi, itFirst, itLast, strModel, strFunctionName, strParameterName, &pEntry);

    if (status >= 0)
    {
        status = _RangeCheckDiscrete(Vi, std::begin(pEntry->AllowedValues()), std::end(pEntry->AllowedValues()), value, coercionStyle, strFunctionName, strParameterName);
    }

    return status;
}

template <typename TIterator>
inline ViStatus GetRangeTableEntryForModel(ViSession Vi, TIterator itFirst, TIterator itLast, const std::string& strModel, const std::string& strFunctionName, const std::string& strParameterName, const UnqualifiedElementType<TIterator>** ppEntry)
{
    *ppEntry = nullptr;

    auto it = FindModelSpecificValue(Vi, strModel, itFirst, itLast);

    return (it != itLast) ?
        (*ppEntry = &(*it), VI_SUCCESS) :
        ReportErrorEx(Vi, IVIC_ERROR_CANNOT_RECOVER, "Could not locate range table entry in function %s for parameter %s.", strFunctionName.c_str(), strParameterName.c_str());
}

template <typename T>
inline static ViStatus ReportInvalidValueError(ViSession Vi, const T& value, const std::string& strFunctionName, const std::string& strParameterName)
{
    return ReportError(Vi, IVIC_ERROR_INVALID_VALUE, std::to_string(value).c_str(), strFunctionName.c_str(), strParameterName.c_str());
}

template <>
inline static ViStatus ReportInvalidValueError(ViSession Vi, const std::string& value, const std::string& strFunctionName, const std::string& strParameterName)
{
    return ReportError(Vi, IVIC_ERROR_INVALID_VALUE, value.c_str(), strFunctionName.c_str(), strParameterName.c_str());
}

template <typename T>
inline bool AreValuesEqual(const T& value1, const T& value2)
{
    return value1 == value2;
}

template <>
inline bool AreValuesEqual(const double& value1, const double& value2)
{
    auto abs1 = ::fabs(value1);
    auto abs2 = ::fabs(value2);
    auto delta = ::fabs(value1 - value2);
    auto closeEnough = std::max<double>(CACHE_COMPARE_EPSILON, (std::max<double>(abs1, abs2) * 5 * 10E-15));

    return delta < closeEnough;
}

///////////////////////////////////////////////////////////////////////////////
// Coercion support
//
template <typename TIterator>
inline static void CoerceUp(ViSession Vi, TIterator itFirst, TIterator itLast, UnqualifiedElementType<TIterator>& value, const std::string& strFunctionName, const std::string& strParameterName)
{
    // This function assumes the elements of the container are already arranged in ascending order
    //
    auto it = std::find_if(itFirst, itLast, [&](const UnqualifiedElementType<TIterator>& allowedValue)
    {
        return (value < allowedValue) || AreValuesEqual(value, allowedValue);
    });

    if (it != itLast)
    {
        if (!AreValuesEqual(value, *it))
        {
            auto session = GetDriverSession(Vi);

            if (session->RecordCoercionsEnabled())
            {
                session->AddCoercionRecord(value, *it, strFunctionName, strParameterName);
            }
        }

        value = *it;
    }
}

template <typename TIterator>
inline static void CoerceDown(ViSession Vi, TIterator itFirst, TIterator itLast, UnqualifiedElementType<TIterator>& value, const std::string& strFunctionName, const std::string& strParameterName)
{
    // This function assumes the elements of the container are already arranged in ascending order
    //
    std::reverse_iterator<TIterator> ritFirst(itLast);
    std::reverse_iterator<TIterator> ritLast(itFirst);

    auto it = std::find_if(ritFirst, ritLast, [&](const UnqualifiedElementType<TIterator>& allowedValue)
    {
        return (value > allowedValue) || AreValuesEqual(value, allowedValue);
    });

    if (it != ritLast)
    {
        if (!AreValuesEqual(value, *it))
        {
            auto session = GetDriverSession(Vi);

            if (session->RecordCoercionsEnabled())
            {
                session->AddCoercionRecord(value, *it, strFunctionName, strParameterName);
            }
        }

        value = *it;
    }
}

template <typename TIterator>
inline static bool IsOneOf(TIterator itFirst, TIterator itLast, const UnqualifiedElementType<TIterator>& value)
{
    auto it = std::find_if(itFirst, itLast, [&](const UnqualifiedElementType<TIterator>& allowedValue)
    {
        return AreValuesEqual(value, allowedValue);
    });

    return it != itLast;
}

///////////////////////////////////////////////////////////////////////////////
// State caching support
//

template <typename T>
inline CacheEntry<T>& GetCacheEntry(ViSession Vi, ViAttr attributeId, const std::string& strQualifiedPhysicalName)
{
    return GetDriverSession(Vi)->GetCacheEntry<T>(attributeId, strQualifiedPhysicalName);
}

// CacheEntry
//
template <typename T>
inline CacheEntry<T>::CacheEntry()
{
    Invalidate();
}

template <typename T>
void CacheEntry<T>::Invalidate()
{
    m_bIsValid = false;
}

template <typename T>
void CacheEntry<T>::SetValid()
{
    m_bIsValid = true;
}

template <typename T>
bool CacheEntry<T>::IsValid() const
{
    return m_bIsValid;
}

template <typename T>
T CacheEntry<T>::Value() const
{
    return m_value;
}

template <typename T>
void CacheEntry<T>::SetValue(const T& value)
{
    m_value = value;
}

template <typename T>
bool CacheEntry<T>::HasValue(const T& value) const
{
    return m_value == value;
}

// Specializations of HasValue for comparing floats with the required IVI-defined precision
//
template <>
inline bool CacheEntry<ViReal32>::HasValue(const ViReal32& value) const
{
    return AreValuesEqual(m_value, value);
}

template <>
inline bool CacheEntry<ViReal64>::HasValue(const ViReal64& value) const
{
    return AreValuesEqual(m_value, value);
}

// CacheManagerBase 
//
inline CacheManagerBase::CacheManagerBase(ViSession Vi, ViAttr attributeId)
    : m_session(Vi), m_attributeId(attributeId)
{
    m_bEnabled = CacheEnabled(m_session) || SimulationEnabled(m_session);
}

inline bool CacheManagerBase::Enabled() const
{
    return m_bEnabled;
}

// CacheManager general definition
//
template <typename T>
inline CacheManager<T>::CacheManager(ViSession Vi, ViAttr attributeId, T& newValue)
    : CacheManagerBase(Vi, attributeId), m_newValue(newValue)
{
}

// CacheManager specialization for ViChar[] attributes
//
inline CacheManager<ViChar[]>::CacheManager(ViSession Vi, ViAttr attributeId, ViChar newValue[])
    : CacheManagerBase(Vi, attributeId), m_newValue(newValue)
{
}

// CacheManager specialization for ViConstString attributes
//
inline CacheManager<ViConstString>::CacheManager(ViSession Vi, ViAttr attributeId, ViConstString newValue)
    : CacheManagerBase(Vi, attributeId), m_newValue(newValue)
{
}

// GetterCacheManager general definition for attributes that are associated with a repcap
//
template <typename T, typename TRepCap>
inline GetterCacheManager<T, TRepCap>::GetterCacheManager(ViSession Vi, const PhysicalName<TRepCap>& physicalName, ViAttr attributeId, T& newValue)
    : CacheManager(Vi, attributeId, newValue), m_pEntry(nullptr)
{
    if (Enabled())
    {
        m_pEntry = &GetCacheEntry<T>(m_session, m_attributeId, physicalName.QualifiedFullName());
    }
}

template <typename T, typename TRepCap>
inline GetterCacheManager<T, TRepCap>::~GetterCacheManager()
{
    if (m_pEntry != nullptr)
    {
        m_pEntry->SetValue(m_newValue);
        m_pEntry->SetValid();
    }
}

template <typename T, typename TRepCap>
inline bool GetterCacheManager<T, TRepCap>::GetCachedValue(T* pValue) const
{
    if (m_pEntry->IsValid())
    {
        *pValue = m_pEntry->Value();

        return true;
    }

    return false;
}

// GetterCacheManager general definition for attributes that are not associated with a repcap
//
template <typename T>
inline GetterCacheManager<T, nullptr_t>::GetterCacheManager(ViSession Vi, ViAttr attributeId, T& newValue)
    : CacheManager(Vi, attributeId, newValue), m_pEntry(nullptr)
{
    if (Enabled())
    {
        m_pEntry = &GetCacheEntry<T>(m_session, m_attributeId);
    }
}

template <typename T>
inline GetterCacheManager<T, nullptr_t>::~GetterCacheManager()
{
    if (m_pEntry != nullptr)
    {
        m_pEntry->SetValue(m_newValue);
        m_pEntry->SetValid();
    }
}

template <typename T>
inline bool GetterCacheManager<T, nullptr_t>::GetCachedValue(T* pValue) const
{
    if (m_pEntry->IsValid())
    {
        *pValue = m_pEntry->Value();

        return true;
    }

    return false;
}

// GetterCacheManager specialization for ViChar[] attributes that are associated with a repcap
//
template <typename TRepCap>
inline GetterCacheManager<ViChar[], TRepCap>::GetterCacheManager(ViSession Vi, const PhysicalName<TRepCap>& physicalName, ViAttr attributeId, ViInt32 bufferSize, ViChar buffer[])
    : CacheManager(Vi, attributeId, buffer), m_pEntry(nullptr)
{
    if (Enabled())
    {
        m_pEntry = &GetCacheEntry<std::string>(m_session, m_attributeId, physicalName.QualifiedFullName());
    }
}

template <typename TRepCap>
inline GetterCacheManager<ViChar[], TRepCap>::~GetterCacheManager()
{
    if (m_pEntry != nullptr && m_newValue != nullptr)
    {
        m_pEntry->SetValue(m_newValue);
        m_pEntry->SetValid();
    }
}

template <typename TRepCap>
inline bool GetterCacheManager<ViChar[], TRepCap>::GetCachedValue(ViInt32 bufferSize, ViChar buffer[]) const
{
    if (m_pEntry->IsValid() && buffer != nullptr)
    {
        strncpy_s(buffer, bufferSize, m_pEntry->Value().c_str(), _TRUNCATE);

        return true;
    }

    return false;
}

// GetterCacheManager specialization for ViChar[] attributes that are not associated with a repcap
//
inline GetterCacheManager<ViChar[], nullptr_t>::GetterCacheManager(ViSession Vi, ViAttr attributeId, ViInt32 bufferSize, ViChar buffer[])
    : CacheManager(Vi, attributeId, buffer), m_pEntry(nullptr)
{
    if (Enabled())
    {
        m_pEntry = &GetCacheEntry<std::string>(m_session, m_attributeId);
    }
}

inline GetterCacheManager<ViChar[], nullptr_t>::~GetterCacheManager()
{
    if (m_pEntry != nullptr && m_newValue != nullptr)
    {
        m_pEntry->SetValue(m_newValue);
        m_pEntry->SetValid();
    }
}

inline bool GetterCacheManager<ViChar[], nullptr_t>::GetCachedValue(ViInt32 bufferSize, ViChar buffer[]) const
{
    if (m_pEntry->IsValid() && buffer != nullptr)
    {
        strncpy_s(buffer, bufferSize, m_pEntry->Value().c_str(), _TRUNCATE);

        return true;
    }

    return false;
}

// SetterCacheManager general definition for attributes that are associated with a repcap
//
template <typename T, typename TRepCap>
inline SetterCacheManager<T, TRepCap>::SetterCacheManager(ViSession Vi, const PhysicalNameList<TRepCap>& physicalNames, ViAttr attributeId, T& newValue)
    : CacheManager(Vi, attributeId, newValue)
{
    if (Enabled())
    {
        for (const auto& physicalName : physicalNames)
        {
            if (!HasCachedValue(physicalName))
            {
                m_nonCachedPhysicalNames.push_back(physicalName);
            }
        }
    }
    else
    {
        // If we're not caching, then all physical names are non-cached
        //
        for (const auto& physicalName : physicalNames)
        {
            m_nonCachedPhysicalNames.push_back(physicalName);
        }
    }
}

template <typename T, typename TRepCap>
inline SetterCacheManager<T, TRepCap>::~SetterCacheManager()
{
    if (Enabled())
    {
        for (const auto& physicalName : m_nonCachedPhysicalNames)
        {
            auto& entry = GetCacheEntry<T>(m_session, m_attributeId, physicalName.QualifiedFullName());
            entry.SetValue(m_newValue);
            entry.SetValid();
        }
    }
}

template <typename T, typename TRepCap>
inline bool SetterCacheManager<T, TRepCap>::HasCachedValue(const PhysicalName<TRepCap>& physicalName) const
{
    const auto& entry = GetCacheEntry<T>(m_session, m_attributeId, physicalName.QualifiedFullName());

    return entry.IsValid() && entry.HasValue(m_newValue);
}

template <typename T, typename TRepCap>
inline const PhysicalNameList<TRepCap>& SetterCacheManager<T, TRepCap>::NonCachedPhysicalNames(ViSession Vi) const
{
    return m_nonCachedPhysicalNames;
}

// SetterCacheManager specialization for attributes that are not associated with a repcap
//
template <typename T>
inline SetterCacheManager<T, nullptr_t>::SetterCacheManager(ViSession Vi, ViAttr attributeId, T& newValue)
    : CacheManager(Vi, attributeId, newValue)
{
}

template <typename T>
inline SetterCacheManager<T, nullptr_t>::~SetterCacheManager()
{
    if (Enabled())
    {
        auto& entry = GetCacheEntry<T>(m_session, m_attributeId);
        entry.SetValue(m_newValue);
        entry.SetValid();
    }
}

template <typename T>
inline bool SetterCacheManager<T, nullptr_t>::HasCachedValue() const
{
    const auto& entry = GetCacheEntry<T>(m_session, m_attributeId);

    return entry.IsValid() && entry.HasValue(m_newValue);
}

// SetterCacheManager specialization for ViConstString attributes that are associated with a repcap
//
template <typename TRepCap>
inline SetterCacheManager<ViConstString, TRepCap>::SetterCacheManager(ViSession Vi, const PhysicalNameList<TRepCap>& physicalNames, ViAttr attributeId, ViConstString newValue)
    : CacheManager(Vi, attributeId, newValue)
{
    if (Enabled())
    {
        for (const auto& physicalName : physicalNames)
        {
            if (!HasCachedValue(physicalName))
            {
                m_nonCachedPhysicalNames.push_back(physicalName);
            }
        }
    }
    else
    {
        // If we're not caching, then all physical names are non-cached
        //
        for (const auto& physicalName : physicalNames)
        {
            m_nonCachedPhysicalNames.push_back(physicalName);
        }
    }
}

template <typename TRepCap>
inline SetterCacheManager<ViConstString, TRepCap>::~SetterCacheManager()
{
    if (Enabled())
    {
        for (const auto& physicalName : m_nonCachedPhysicalNames)
        {
            auto& entry = GetCacheEntry<std::string>(m_session, m_attributeId, physicalName.QualifiedFullName());
            entry.SetValue(m_newValue);
            entry.SetValid();
        }
    }
}

template <typename TRepCap>
inline bool SetterCacheManager<ViConstString, TRepCap>::HasCachedValue(const PhysicalName<TRepCap>& physicalName) const
{
    const auto& entry = GetCacheEntry<std::string>(m_session, m_attributeId, physicalName.QualifiedFullName());

    return entry.IsValid() && entry.HasValue(m_newValue);
}

template <typename TRepCap>
inline const PhysicalNameList<TRepCap>& SetterCacheManager<ViConstString, TRepCap>::NonCachedPhysicalNames(ViSession Vi) const
{
    return m_nonCachedPhysicalNames;
}

// SetterCacheManager specialization for ViConstString attributes that are not associated with a repcap
//
inline SetterCacheManager<ViConstString, nullptr_t>::SetterCacheManager(ViSession Vi, ViAttr attributeId, ViConstString newValue)
    : CacheManager(Vi, attributeId, newValue)
{
}

inline SetterCacheManager<ViConstString, nullptr_t>::~SetterCacheManager()
{
    if (Enabled())
    {
        auto& entry = GetCacheEntry<std::string>(m_session, m_attributeId);
        entry.SetValue(m_newValue);
        entry.SetValid();
    }
}

inline bool SetterCacheManager<ViConstString, nullptr_t>::HasCachedValue() const
{
    const auto& entry = GetCacheEntry<std::string>(m_session, m_attributeId);

    return entry.IsValid() && entry.HasValue(m_newValue);
}

// Attribute invalidation functions
//
template <typename... Args>
inline void InvalidateAttributes(ViSession Vi, ViAttr attributeId, Args... args)
{
    GetDriverSession(Vi)->InvalidateAttributes(attributeId, args...);
}

template <typename TRepCap, typename... Args>
inline void InvalidateAttributes(ViSession Vi, const PhysicalNameList<TRepCap>& physicalNames, ViAttr attributeId, Args... args)
{
    GetDriverSession(Vi)->InvalidateAttributes(physicalNames, attributeId, args...);
}

///////////////////////////////////////////////////////////////////////////////
// Simulation support
//
template <typename T>
inline SimulationTableEntry<T>::SimulationTableEntry(const T& defaultValue)
    : SimulationTableEntry(std::string(), defaultValue)
{
}

template <typename T>
inline SimulationTableEntry<T>::SimulationTableEntry(const std::string& strModelList, const T& defaultValue)
    : ModelBasedType(strModelList), DefaultValue(defaultValue)
{
}

template <typename TIterator, typename TValue>
inline static void _GetValueForSimulation(ViSession Vi, TIterator itFirst, TIterator itLast, TValue* pValue)
{
    auto it = FindModelSpecificValue(Vi, InstrumentModel(Vi), itFirst, itLast);
    assert(it != itLast);

    if (it != itLast)
    {
        *pValue = it->DefaultValue;
    }
}

template <typename TIterator>
inline static void _GetValueForSimulation(ViSession Vi, TIterator itFirst, TIterator itLast, ViInt32 bufferSize, ViChar buffer[])
{
    auto it = FindModelSpecificValue(Vi, InstrumentModel(Vi), itFirst, itLast);
    assert(it != itLast);

    if (it != itLast)
    {
        strncpy_s(buffer, bufferSize, it->DefaultValue, _TRUNCATE);
    }
}

///////////////////////////////////////////////////////////////////////////////
// Inherent capabilities
//
template <typename TSession>
ViStatus InitWithOptions(ViRsrc ResourceName, ViBoolean IdQuery, ViBoolean Reset, ViConstString OptionsString, ViSession* Vi)
{
    static_assert(std::is_base_of<DriverSession, TSession>::value, "Session class must derive from DriverSession.");

    if (Vi == nullptr) return IVIC_ERROR_NULL_POINTER;

    auto status = VI_SUCCESS;

    *Vi = VI_NULL;

    status = IviSession_New(Vi);
    ReturnOnError(status);

    auto pSession = new TSession(*Vi);
    status = IviSession_SetDataPtr(*Vi, reinterpret_cast<ViAddr>(pSession));

    if (status >= 0)
    {
        status = pSession->Initialize<TSession>(ResourceName, IdQuery == VI_TRUE, Reset == VI_TRUE, OptionsString);
    }

    if (status < 0)
    {
        delete pSession;
        *Vi = VI_NULL;
    }

    return status;
}

inline ViStatus close(ViSession Vi)
{
    auto status = VI_SUCCESS;

    // Clear out the physical name maps for this session for all of the defined repcaps by invoking their cleanup 
    // functions.
    //
    for (const auto& it : g_vecPhysicalNameCleanupFunctions)
    {
        it(Vi);
    }

    DriverSession* pSession = nullptr;
    status = GetDriverSession(Vi, &pSession);
    assert(pSession != nullptr  && "Failed to retrieve driver session.");

    if (status >= 0 && pSession != nullptr)
    {
        pSession->Close();
        delete pSession;
        status = IviSession_Dispose(Vi);
    }

    return status;
}

inline ViStatus revision_query(ViSession Vi, ViChar DriverRev[], ViChar InstrRev[])
{
    auto status = VI_SUCCESS;

    // IVI 3.2 specifies that the user should pass a buffer with at least 256 bytes for the DriverRev 
    // parameter and InstrRev parameters.
    //
    const auto MaxBufSize = 256;

    status = get_SPECIFIC_DRIVER_REVISION(Vi, VI_NULL, MaxBufSize, DriverRev);

    if (status >= 0)
    {
        status = get_INSTRUMENT_FIRMWARE_REVISION(Vi, VI_NULL, MaxBufSize, InstrRev);
    }

    return status;
}

inline ViStatus error_message(ViSession Vi, ViStatus ErrorCode, ViChar ErrorMessage[])
{
    auto status = VI_SUCCESS;

    auto strError = GetErrorMessage(ErrorCode);

    if (strError.empty())
    {
        if (Vi == VI_NULL)
        {
            return IVIC_ERROR_INVALID_VALUE;
        }
        else
        {
            return ReportErrorEx(Vi, IVIC_ERROR_INVALID_VALUE, "The error code supplied is not defined by the driver.", std::to_string(ErrorCode).c_str(), "error_message", "ErrorCode");
        }
    }

    // IVI 3.2 specifies that the user should pass a buffer with at least 256 bytes for the DriverRev 
    // parameter and InstrRev parameters.
    //
    const auto MaxBufferSize = 256;

    strncpy_s(ErrorMessage, MaxBufferSize, strError.c_str(), strError.length());

    return status;
}

inline ViStatus GetError(ViSession Vi, ViStatus* ErrorCode, ViInt32 ErrorDescriptionBufferSize, ViChar ErrorDescription[])
{
    auto status = VI_SUCCESS;

    status = IviSession_GetError(Vi, ErrorDescriptionBufferSize, ErrorCode, ErrorDescription);

    return status;
}

inline ViStatus ClearError(ViSession Vi)
{
    auto status = VI_SUCCESS;

    status = IviSession_ClearError(Vi);

    return status;
}

inline ViStatus ClearInterchangeWarnings(ViSession Vi)
{
    auto status = VI_SUCCESS;

    status = ReportError(Vi, IVIC_ERROR_FUNCTION_NOT_SUPPORTED, "ClearInterchangeWarnings");

    return status;
}

inline ViStatus GetNextCoercionRecord(ViSession Vi, ViInt32 CoercionRecordBufferSize, ViChar CoercionRecord[])
{
    auto status = VI_SUCCESS;

    if (CoercionRecord == nullptr && CoercionRecordBufferSize != 0)
    {
        return ReportError(Vi, IVIC_ERROR_NULL_POINTER, "GetNextCoercionRecord", "CoercionRecord");
    }

    auto strRecord = GetDriverSession(Vi)->GetNextCoercionRecord();

    if (CoercionRecordBufferSize > 0)
    {
        strncpy_s(CoercionRecord, CoercionRecordBufferSize, strRecord.c_str(), _TRUNCATE);

        if (CoercionRecordBufferSize < (ViInt32)(strRecord.length() + 1))
        {
            // They did not allocate a buffer large enough, so IVI-3.2, Section 3.1.2.1 requires that we return the
            // total buffer size required to hold the entire record.
            //
            status = strRecord.length() + 1;
        }

        GetDriverSession(Vi)->RemoveNextCoercionRecord();
    }
    else if (CoercionRecordBufferSize == 0)
    {
        // IVI-3.2, Section 3.1.2.1 requires that we return a buffer size that is greater than or equal to the size
        // of the buffer the user must pass to be ensured of getting the entire string, including the NUL byte. We
        // do not remove the coercion record at this time.
        //
        status = strRecord.length() + 1;
    }
    else if (CoercionRecordBufferSize < 0)
    {
        // If the user passes a negative number for the buffer size parameter, IVI-3.2, Section 3.1.2.1 requires 
        // that we copy the result into the buffer regardless of the number of bytes in the value.
        //
#pragma warning (push)
#pragma warning (disable : 4996)
        strcpy(CoercionRecord, strRecord.c_str());
#pragma warning (pop)

        GetDriverSession(Vi)->RemoveNextCoercionRecord();
    }

    return status;
}

inline ViStatus GetNextInterchangeWarning(ViSession Vi, ViInt32 InterchangeWarningBufferSize, ViChar InterchangeWarning[])
{
    auto status = VI_SUCCESS;

    status = ReportError(Vi, IVIC_ERROR_FUNCTION_NOT_SUPPORTED, "GetNextInterchangeWarning");

    return status;
}

inline ViStatus InvalidateAllAttributes(ViSession Vi)
{
    auto status = VI_SUCCESS;

    GetDriverSession(Vi)->InvalidateAllAttributes();

    return status;
}

inline ViStatus ResetInterchangeCheck(ViSession Vi)
{
    auto status = VI_SUCCESS;

    status = ReportError(Vi, IVIC_ERROR_FUNCTION_NOT_SUPPORTED, "ResetInterchangeCheck");

    return status;
}

inline ViStatus Disable(ViSession Vi)
{
    auto status = VI_SUCCESS;

    if (!SimulationEnabled(Vi))
    {
#ifndef NRT_NO_VISA
		VisaTimeoutManager timeout(GetVisaSession(Vi), ResetTimeout(Vi));
		status = viPrintf(GetVisaSession(Vi), "*RST\n");
		ReturnOnError(status);

		long lResult;
		status = viQueryf(GetVisaSession(Vi), "*OPC?\n", "%ld%*T", &lResult);
		ReturnOnError(status);

		status = PollInstrumentErrors(Vi);
		ReturnOnError(status);
#else
        assert(!"Function must be implemented in derived session class.");
#endif
    }

    return status;
}

inline ViStatus error_query(ViSession Vi, ViInt32* ErrorCode, ViChar ErrorMessage[])
{
    auto status = VI_SUCCESS;
    const auto MaxBufferSize = 256;

    if (!SimulationEnabled(Vi))
    {
#ifndef NRT_NO_VISA
        ViChar szResponse[MaxBufferSize];
        status = viQueryf(GetVisaSession(Vi), ":SYST:ERR?\n", "%T", szResponse);
        ReturnOnError(status);

        auto strResponse = Trim(TrimWhitespace(szResponse), "\"");
        auto nIndex = strResponse.find(",");

        if (nIndex == std::string::npos)
        {
            status = ReportErrorEx(Vi, IVIC_ERROR_UNEXPECTED_RESPONSE,
                "Failed to parse the response to the SYST:ERR? query.  The response is expected to be a comma-separated list of 2 items in the form '<error code>,<error message>'.", strResponse.c_str());
            ReturnOnError(status);
        }

        auto strCode = TrimWhitespace(strResponse.substr(0, nIndex));
        auto strMessage = Trim(TrimWhitespace(strResponse.substr(nIndex + 1)), "\"");

        *ErrorCode = std::stoi(strCode);
        strncpy_s(ErrorMessage, MaxBufferSize, strMessage.c_str(), strMessage.length());
#else
        assert(!"Function must be implemented in derived session class.");
#endif
    }
    else
    {
        *ErrorCode = 0;
        const auto NoErrorMessage = "No error.";
        strncpy_s(ErrorMessage, MaxBufferSize, NoErrorMessage, strlen(NoErrorMessage));
    }

    return status;
}

inline ViStatus LockSession(ViSession Vi, ViBoolean* CallerHasLock)
{
    auto status = VI_SUCCESS;

    status = IviSession_Lock(Vi, CallerHasLock);

    return status;
}

inline ViStatus reset(ViSession Vi)
{
    auto status = VI_SUCCESS;

    if (!SimulationEnabled(Vi))
    {
#ifndef NRT_NO_VISA
        VisaTimeoutManager timeout(GetVisaSession(Vi), ResetTimeout(Vi));
		status = viPrintf(GetVisaSession(Vi), "*RST\n");
		ReturnOnError(status);

        long lResult;
        status = viQueryf(GetVisaSession(Vi), "*OPC?\n", "%ld%*T", &lResult);
        ReturnOnError(status);

        status = PollInstrumentErrors(Vi);
        ReturnOnError(status);
#else
        assert(!"Function must be implemented in derived session class.");
#endif
    }

    GetDriverSession(Vi)->InvalidateAllAttributes();

    return status;
}

inline ViStatus ResetWithDefaults(ViSession Vi)
{
    auto status = VI_SUCCESS;

    status = reset(Vi);

    if (status >= 0)
    {
        status = GetDriverSession(Vi)->ResetDefaults();
    }

    return status;
}

inline ViStatus self_test(ViSession Vi, ViInt16* TestResult, ViChar TestMessage[])
{
    auto status = VI_SUCCESS;
    const auto MaxBufferSize = 256;
    const auto TestPassedMessage = "Selftest passed";
    const auto TestFailedMessage = "Selftest failed";
    std::string strTestMessage;

    if (!SimulationEnabled(Vi))
    {
#ifndef NRT_NO_VISA
        VisaTimeoutManager timeout(GetVisaSession(Vi), SelfTestTimeout(Vi));
        status = viQueryf(GetVisaSession(Vi), "*TST?\n", "%hd%*T", TestResult);
        ReturnOnError(status);

        status = PollInstrumentErrors(Vi);
        ReturnOnError(status);

        strTestMessage = (*TestResult == 0) ? TestPassedMessage : TestFailedMessage;
#else
        assert(!"Function must be implemented in derived session class.");
#endif
    }
    else
    {
        *TestResult = 0;
        strTestMessage = TestPassedMessage;
    }

    if (status >= 0)
    {
        strncpy_s(TestMessage, MaxBufferSize, strTestMessage.c_str(), _TRUNCATE);
    }

    return status;
}

inline ViStatus UnlockSession(ViSession Vi, ViBoolean* CallerHasLock)
{
    auto status = VI_SUCCESS;

    status = IviSession_Unlock(Vi, CallerHasLock);

    return status;
}

template <typename T>
struct AttributeTraits
{
    static const char* TypeName();
    typedef AttributeGetter<T> GetterType;
    typedef AttributeSetter<T> SetterType;
};

template <>
inline static const char* AttributeTraits<ViInt32>::TypeName() { return "ViInt32"; }

template <>
inline static const char* AttributeTraits<ViInt64>::TypeName() { return "ViInt64"; }

template <>
inline static const char* AttributeTraits<ViReal64>::TypeName() { return "ViReal64"; }

template <>
inline static const char* AttributeTraits<ViBoolean>::TypeName() { return "ViBoolean"; }

template <>
inline static const char* AttributeTraits<ViSession>::TypeName() { return "ViSession"; }

template <>
struct AttributeTraits < ViString >
{
    static const char* TypeName() { return "ViString"; }
    typedef AttributeGetterViString GetterType;
    typedef AttributeSetter<ViConstString> SetterType;
};

template <typename T>
ViStatus GetAttribute(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, T* AttributeValue)
{
    auto status = VI_SUCCESS;

    // Lookup the attribute ID in the map and verify it's a defined attribute
    //
    auto it = g_AttributeMap.find(AttributeID);

    if (it == std::end(g_AttributeMap))
    {
        return ReportError(Vi, IVIC_ERROR_INVALID_ATTRIBUTE, std::to_string(AttributeID).c_str());
    }

    // Compare the type of the attribute accessor with the type of the attribute we found in the map and make sure they match
    //
    const auto& accessorTypeInfo = typeid(T);

    if (it->second.TypeInfo() != accessorTypeInfo)
    {
        return ReportError(Vi, IVIC_ERROR_TYPES_DO_NOT_MATCH, "Get", AttributeTraits<T>::TypeName(), it->second.AttributeName().c_str(), it->second.TypeName().c_str());
    }

    // Get a reference to the actual getter function for this attribute
    //
    auto getter = it->second.Getter<AttributeTraits<T>::GetterType>();

    if (getter == nullptr)
    {
        return ReportError(Vi, IVIC_ERROR_IVI_ATTR_NOT_READABLE, it->second.AttributeName().c_str());
    }

    // Call the getter function
    //
    status = getter(Vi, RepCapIdentifier, AttributeValue);

    return status;
}

inline ViStatus GetAttributeViString(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, ViInt32 AttributeValueBufferSize, ViChar AttributeValue[])
{
    auto status = VI_SUCCESS;

    // Lookup the attribute ID in the map and verify it's a defined attribute
    //
    auto it = g_AttributeMap.find(AttributeID);

    if (it == std::end(g_AttributeMap))
    {
        return ReportError(Vi, IVIC_ERROR_INVALID_ATTRIBUTE, std::to_string(AttributeID).c_str());
    }

    // Compare the type of the attribute accessor with the type of the attribute we found in the map and make sure they match
    //
    const auto& accessorTypeInfo = typeid(ViString);

    if (it->second.TypeInfo() != accessorTypeInfo)
    {
        return ReportError(Vi, IVIC_ERROR_TYPES_DO_NOT_MATCH, "Get", "ViString", it->second.AttributeName().c_str(), it->second.TypeName().c_str());
    }

    // Get a reference to the actual getter function for this attribute
    //
    auto getter = it->second.Getter<AttributeGetterViString>();

    if (getter == nullptr)
    {
        return ReportError(Vi, IVIC_ERROR_IVI_ATTR_NOT_READABLE, it->second.AttributeName().c_str());
    }

    if (AttributeValue == nullptr && AttributeValueBufferSize != 0)
    {
        return ReportError(Vi, IVIC_ERROR_NULL_POINTER, "GetAttributeViString", "AttributeValueBufferSize");
    }

    if (AttributeValueBufferSize > 0)
    {
        // Call the getter function directly, using the user-provided buffer size and buffer
        //
        status = getter(Vi, RepCapIdentifier, AttributeValueBufferSize, AttributeValue);

        // If this assert fires, then it is likely the MAX_STRING_ATTRIBUTE_LENGTH is not large enough.  You 
        // should consider defining this value in the driver's stdafx.h file above the #include for NRT.
        //
        assert(strnlen_s(AttributeValue, _TRUNCATE) < MAX_STRING_ATTRIBUTE_LENGTH);

        // If we get a string back that is exactly the size of the buffer the user allocated, then it is typically 
        // safe to assume there is more data left in the instrument, so we return as the ViStatus the max amount 
        // they would need to allocate to be assured of receiving the entire string from the instrument.  There is
        // the very slight possibility that the actual data matches exactly the size of the buffer provided, and
        // in that rare case, we would report that the user did not receive everything (though all of the data
        // would be returned).
        //
        if ((status >= 0) && (AttributeValueBufferSize == (strnlen_s(AttributeValue, _TRUNCATE) + 1)))
        {
            status = MAX_STRING_ATTRIBUTE_LENGTH;
        }
    }
    else if (AttributeValueBufferSize == 0)
    {
        // IVI-3.2, Section 3.1.2.1 requires that we return a buffer size that is greater than or equal to the size
        // of the buffer the user must pass to be ensured of getting the entire string, including the NUL byte. 
        // So, we simply return the max string attribute size.
        //
        status = MAX_STRING_ATTRIBUTE_LENGTH;
    }
    else if (AttributeValueBufferSize < 0)
    {
        // Although the user is asking us to blindly copy as many characters as we want into their buffer, they may
        // be basing that decision on a previous call to GetAttributeViString where we told them the max buffer
        // needed would be MAX_STRING_ATTRIBUTE_LENGTH.  So, we invoke the getter with the max buffer size.  Also,
        // getter implementations will commonly use viQueryf, which does not handle negative buffer sizes.
        //
        status = getter(Vi, RepCapIdentifier, MAX_STRING_ATTRIBUTE_LENGTH, AttributeValue);
    }

    return status;
}

template <typename T>
ViStatus SetAttribute(ViSession Vi, ViConstString RepCapIdentifier, ViAttr AttributeID, T AttributeValue)
{
    // Lookup the attribute ID in the map and verify it's a defined attribute
    //
    auto status = VI_SUCCESS;

    auto it = g_AttributeMap.find(AttributeID);

    if (it == std::end(g_AttributeMap))
    {
        return ReportError(Vi, IVIC_ERROR_INVALID_ATTRIBUTE, std::to_string(AttributeID).c_str());
    }

    // Compare the type of the attribute accessor with the type of the attribute we found in the map and make sure they match
    //
    const auto& accessorTypeInfo = typeid(T);

    if (it->second.TypeInfo() != accessorTypeInfo)
    {
        return ReportError(Vi, IVIC_ERROR_TYPES_DO_NOT_MATCH, "Set", AttributeTraits<T>::TypeName(), it->second.AttributeName().c_str(), it->second.TypeName().c_str());
    }

    // Get a reference to the actual setter function for this attribute
    //
    auto setter = it->second.Setter<AttributeTraits<T>::SetterType>();

    if (setter == nullptr)
    {
        return ReportError(Vi, IVIC_ERROR_IVI_ATTR_NOT_WRITABLE, it->second.AttributeName().c_str());
    }

    // Call the setter function
    //
    status = setter(Vi, RepCapIdentifier, AttributeValue);

    return status;
}

inline ViStatus get_SPECIFIC_DRIVER_DESCRIPTION(ViSession Vi, ViConstString RepCapIdentifier, ViInt32 AttributeValueBufferSize, ViChar AttributeValue[])
{
    auto status = VI_SUCCESS;

    NRT_UNUSED(RepCapIdentifier);

    auto strDescription = g_driverInfo.DriverDescription;

#ifdef _WIN64
    // For 64-bit builds, we need to append some hard-coded text as specified in IVI 3.2
    //
    strDescription += " [Compiled for 64-bit]";
#endif
    strncpy_s(AttributeValue, AttributeValueBufferSize, strDescription.c_str(), _TRUNCATE);

    return status;
}

inline ViStatus get_SPECIFIC_DRIVER_PREFIX(ViSession Vi, ViConstString RepCapIdentifier, ViInt32 AttributeValueBufferSize, ViChar AttributeValue[])
{
    auto status = VI_SUCCESS;

    NRT_UNUSED(RepCapIdentifier);

    strncpy_s(AttributeValue, AttributeValueBufferSize, g_driverInfo.Prefix.c_str(), _TRUNCATE);

    return status;
}

inline ViStatus get_SPECIFIC_DRIVER_VENDOR(ViSession Vi, ViConstString RepCapIdentifier, ViInt32 AttributeValueBufferSize, ViChar AttributeValue[])
{
    auto status = VI_SUCCESS;

    NRT_UNUSED(RepCapIdentifier);

    strncpy_s(AttributeValue, AttributeValueBufferSize, g_driverInfo.DriverVendor.c_str(), _TRUNCATE);

    return status;
}

inline ViStatus get_SPECIFIC_DRIVER_REVISION(ViSession Vi, ViConstString RepCapIdentifier, ViInt32 AttributeValueBufferSize, ViChar AttributeValue[])
{
    auto status = VI_SUCCESS;

    NRT_UNUSED(RepCapIdentifier);

    strncpy_s(AttributeValue, AttributeValueBufferSize, g_driverInfo.DriverRevision.c_str(), _TRUNCATE);

    return status;
}

inline ViStatus get_SPECIFIC_DRIVER_CLASS_SPEC_MAJOR_VERSION(ViSession Vi, ViConstString RepCapIdentifier, ViInt32* AttributeValue)
{
    auto status = VI_SUCCESS;

    NRT_UNUSED(RepCapIdentifier);

    *AttributeValue = g_driverInfo.SpecificationMajorVersion;

    return status;
}

inline ViStatus get_SPECIFIC_DRIVER_CLASS_SPEC_MINOR_VERSION(ViSession Vi, ViConstString RepCapIdentifier, ViInt32* AttributeValue)
{
    auto status = VI_SUCCESS;

    NRT_UNUSED(RepCapIdentifier);

    *AttributeValue = g_driverInfo.SpecificationMinorVersion;

    return status;
}

inline ViStatus get_RANGE_CHECK(ViSession Vi, ViConstString RepCapIdentifier, ViBoolean* AttributeValue)
{
    auto status = VI_SUCCESS;

    NRT_UNUSED(RepCapIdentifier);

    *AttributeValue = RangeCheckEnabled(Vi);

    return status;
}

inline ViStatus set_RANGE_CHECK(ViSession Vi, ViConstString RepCapIdentifier, ViBoolean AttributeValue)
{
    auto status = VI_SUCCESS;

    NRT_UNUSED(RepCapIdentifier);

    SetRangeCheckEnabled(Vi, AttributeValue == VI_TRUE);

    return status;
}

inline ViStatus get_QUERY_INSTRUMENT_STATUS(ViSession Vi, ViConstString RepCapIdentifier, ViBoolean* AttributeValue)
{
    auto status = VI_SUCCESS;

    NRT_UNUSED(RepCapIdentifier);

    *AttributeValue = QueryInstrStatusEnabled(Vi);

    return status;
}

inline ViStatus set_QUERY_INSTRUMENT_STATUS(ViSession Vi, ViConstString RepCapIdentifier, ViBoolean AttributeValue)
{
    auto status = VI_SUCCESS;

    NRT_UNUSED(RepCapIdentifier);

    SetQueryInstrStatusEnabled(Vi, AttributeValue == VI_TRUE);

    return status;
}

inline ViStatus get_CACHE(ViSession Vi, ViConstString RepCapIdentifier, ViBoolean* AttributeValue)
{
    auto status = VI_SUCCESS;

    NRT_UNUSED(RepCapIdentifier);

    *AttributeValue = CacheEnabled(Vi);

    return status;
}

inline ViStatus set_CACHE(ViSession Vi, ViConstString RepCapIdentifier, ViBoolean AttributeValue)
{
    auto status = VI_SUCCESS;

    NRT_UNUSED(RepCapIdentifier);

    SetCacheEnabled(Vi, AttributeValue == VI_TRUE);

    return status;
}

inline ViStatus get_SIMULATE(ViSession Vi, ViConstString RepCapIdentifier, ViBoolean* AttributeValue)
{
    auto status = VI_SUCCESS;

    NRT_UNUSED(RepCapIdentifier);

    *AttributeValue = SimulationEnabled(Vi);

    return status;
}

inline ViStatus set_SIMULATE(ViSession Vi, ViConstString RepCapIdentifier, ViBoolean AttributeValue)
{
    auto status = VI_SUCCESS;

    NRT_UNUSED(RepCapIdentifier);

    // If the IVI specific driver is initialized with Simulate set to True, the specific driver shall 
    // return the Cannot Change Simulation State error if the user attempts to set Simulate to False 
    // prior to calling the Close function. (IVI 3.2)
    //
    if (SimulationEnabledOriginal(Vi) && AttributeValue == VI_FALSE)
    {
        return ReportError(Vi, IVIC_ERROR_CANNOT_CHANGE_SIMULATION_STATE);
    }

    SetSimulationEnabled(Vi, AttributeValue == VI_TRUE);

    return status;
}

inline ViStatus get_RECORD_COERCIONS(ViSession Vi, ViConstString RepCapIdentifier, ViBoolean* AttributeValue)
{
    auto status = VI_SUCCESS;

    NRT_UNUSED(RepCapIdentifier);

    *AttributeValue = RecordCoercionsEnabled(Vi);

    return status;
}

inline ViStatus set_RECORD_COERCIONS(ViSession Vi, ViConstString RepCapIdentifier, ViBoolean AttributeValue)
{
    auto status = VI_SUCCESS;

    NRT_UNUSED(RepCapIdentifier);

    SetRecordCoercionsEnabled(Vi, AttributeValue == VI_TRUE);

    return status;
}

inline ViStatus get_INTERCHANGE_CHECK(ViSession Vi, ViConstString RepCapIdentifier, ViBoolean* AttributeValue)
{
    auto status = VI_SUCCESS;

    NRT_UNUSED(RepCapIdentifier);

    *AttributeValue = InterchangeCheckEnabled(Vi);

    return status;
}

inline ViStatus set_INTERCHANGE_CHECK(ViSession Vi, ViConstString RepCapIdentifier, ViBoolean AttributeValue)
{
    auto status = VI_SUCCESS;

    NRT_UNUSED(RepCapIdentifier);

    if (AttributeValue == VI_TRUE && !InterchangeCheckSupported(Vi))
    {
        // The user has turned on interchangeability checking, but the driver has indicated that it's not supported
        //
        status = ReportErrorEx(Vi, IVIC_ERROR_VALUE_NOT_SUPPORTED, "Interchange checking is not supported by the driver.", "True", "AttributeValue", "SetAttributeViBoolean");
        ReturnOnError(status);
    }

    SetInterchangeCheckEnabled(Vi, AttributeValue == VI_TRUE);

    return status;
}

inline ViStatus get_LOGICAL_NAME(ViSession Vi, ViConstString RepCapIdentifier, ViInt32 AttributeValueBufferSize, ViChar AttributeValue[])
{
    auto status = VI_SUCCESS;

    NRT_UNUSED(RepCapIdentifier);

    auto strLogicalName = LogicalName(Vi);

    strncpy_s(AttributeValue, AttributeValueBufferSize, strLogicalName.c_str(), _TRUNCATE);

    return status;
}

inline ViStatus get_IO_RESOURCE_DESCRIPTOR(ViSession Vi, ViConstString RepCapIdentifier, ViInt32 AttributeValueBufferSize, ViChar AttributeValue[])
{
    auto status = VI_SUCCESS;

    NRT_UNUSED(RepCapIdentifier);

    auto strResourceDescriptor = IoDescriptor(Vi);

    strncpy_s(AttributeValue, AttributeValueBufferSize, strResourceDescriptor.c_str(), _TRUNCATE);

    return status;
}

inline ViStatus get_DRIVER_SETUP(ViSession Vi, ViConstString RepCapIdentifier, ViInt32 AttributeValueBufferSize, ViChar AttributeValue[])
{
    auto status = VI_SUCCESS;

    NRT_UNUSED(RepCapIdentifier);

    auto strDriverSetup = DriverSetup(Vi);

    strncpy_s(AttributeValue, AttributeValueBufferSize, strDriverSetup.c_str(), _TRUNCATE);

    return status;
}

inline ViStatus get_GROUP_CAPABILITIES(ViSession Vi, ViConstString RepCapIdentifier, ViInt32 AttributeValueBufferSize, ViChar AttributeValue[])
{
    auto status = VI_SUCCESS;

    NRT_UNUSED(RepCapIdentifier);

    strncpy_s(AttributeValue, AttributeValueBufferSize, g_driverInfo.GroupCapabilities.c_str(), _TRUNCATE);

    return status;
}

inline ViStatus get_SUPPORTED_INSTRUMENT_MODELS(ViSession Vi, ViConstString RepCapIdentifier, ViInt32 AttributeValueBufferSize, ViChar AttributeValue[])
{
    auto status = VI_SUCCESS;

    NRT_UNUSED(RepCapIdentifier);

    static std::string strModels = []() -> std::string
    {
        std::string strTempModels;

        for (auto& it = g_modelMap.cbegin(); it != g_modelMap.cend(); ++it)
        {
            strTempModels += it->first;

            if (std::next(it) != g_modelMap.cend())
            {
                // This isn't the last model in the map, so add a trailing comma
                //
                strTempModels += ',';
            }
        }

        return strTempModels;
    }();

    strncpy_s(AttributeValue, AttributeValueBufferSize, strModels.c_str(), _TRUNCATE);

    return status;
}

inline ViStatus get_INSTRUMENT_FIRMWARE_REVISION(ViSession Vi, ViConstString RepCapIdentifier, ViInt32 AttributeValueBufferSize, ViChar AttributeValue[])
{
    auto status = VI_SUCCESS;

    NRT_UNUSED(RepCapIdentifier);

    // When simulating, the instrument firmware revision is the driver revision
    //
    if (SimulationEnabled(Vi))
    {
        status = get_SPECIFIC_DRIVER_REVISION(Vi, RepCapIdentifier, AttributeValueBufferSize, AttributeValue);

        if (status >= 0)
        {
            auto strFirmwareRev = std::string("Sim") + AttributeValue;
            strncpy_s(AttributeValue, AttributeValueBufferSize, strFirmwareRev.c_str(), _TRUNCATE);
        }

        return status;
    }

    auto strFirmwareRev = FirmwareRevision(Vi);

    strncpy_s(AttributeValue, AttributeValueBufferSize, strFirmwareRev.c_str(), _TRUNCATE);

    return status;
}

inline ViStatus get_INSTRUMENT_MANUFACTURER(ViSession Vi, ViConstString RepCapIdentifier, ViInt32 AttributeValueBufferSize, ViChar AttributeValue[])
{
    auto status = VI_SUCCESS;

    NRT_UNUSED(RepCapIdentifier);

    // When simulating, the instrument manufacturer is the driver vendor
    //
    if (SimulationEnabled(Vi))
    {
        return get_SPECIFIC_DRIVER_VENDOR(Vi, RepCapIdentifier, AttributeValueBufferSize, AttributeValue);
    }

    auto strManufacturer = Manufacturer(Vi);

    strncpy_s(AttributeValue, AttributeValueBufferSize, strManufacturer.c_str(), _TRUNCATE);

    return status;
}

inline ViStatus get_INSTRUMENT_MODEL(ViSession Vi, ViConstString RepCapIdentifier, ViInt32 AttributeValueBufferSize, ViChar AttributeValue[])
{
    auto status = VI_SUCCESS;

    NRT_UNUSED(RepCapIdentifier);

    auto strModel = InstrumentModel(Vi);

    strncpy_s(AttributeValue, AttributeValueBufferSize, strModel.c_str(), _TRUNCATE);

    return status;
}
};

