//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef PROPERTIES_PROPERTY_H
#define PROPERTIES_PROPERTY_H

class BufferedFile;

enum class EPropertyType : uint8_t
{
    PT_BOOL,
    PT_FLOAT,
    PT_INT,
    PT_STRING,
    PT_ERROR
};

class BaseProperty
{
public:
    explicit BaseProperty(EPropertyType inType) : m_Type(inType) {}
    virtual ~BaseProperty() = default;
    EPropertyType GetType() const { return m_Type; }

    virtual void Save(const std::string& name, BufferedFile* file) = 0;

protected:
    EPropertyType m_Type{ EPropertyType::PT_STRING };
};


class BoolProperty final : public BaseProperty
{
public:
    explicit BoolProperty(bool inValue) : BaseProperty(EPropertyType::PT_BOOL), m_Value(inValue) {}
    bool GetValue() const { return m_Value; }
    void SetValue(bool value) { m_Value = value; }

    void Save(const std::string& name, BufferedFile* file) override;

private:
    bool m_Value{ false };
};

class FloatProperty final : public BaseProperty
{
public:
    explicit FloatProperty(float inValue) : BaseProperty(EPropertyType::PT_FLOAT), m_Value(inValue) {}
    float GetValue() const { return m_Value; }
    void SetValue(float value) { m_Value = value; }

    void Save(const std::string& name, BufferedFile* file) override;

private:
    float m_Value{ 0.0F };
};

class StringProperty final : public BaseProperty
{
public:
    explicit StringProperty(std::string inValue) : BaseProperty(EPropertyType::PT_STRING), m_Value(std::move(inValue)) {}
    const std::string& GetValue() const { return m_Value; }
    void SetValue(const std::string& value) { m_Value = value; }

    void Save(const std::string& name, BufferedFile* file) override;

private:
    std::string m_Value;
};

class IntProperty final : public BaseProperty
{
public:
    explicit IntProperty(int inValue) : BaseProperty(EPropertyType::PT_INT), m_Value(inValue) {}
    int GetValue() const { return m_Value; }
    void SetValue(int value) { m_Value = value; }

    void Save(const std::string& name, BufferedFile* file) override;

private:
    int m_Value{ 0 };
};

#endif
