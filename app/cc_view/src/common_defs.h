#pragma once

#include <QtCore/QVariant>

#include <cassert>

#define CC_EXPAND(x_) x_
#define CC_CONCATENATE_(x_, y_) x_##y_
#define CC_CONCATENATE(x_, y_) CC_CONCATENATE_(x_, y_)
#define CC_MEMBER(type_, name_, ...) \
    public: \
        const type_& CC_CONCATENATE(get, name_)() const \
        { \
            return CC_CONCATENATE(m_, name_); \
        } \
        \
        QVariant CC_CONCATENATE(CC_CONCATENATE(get, name_), AsVariant)() const \
        { \
            return QVariant::fromValue((CC_CONCATENATE(m_, name_))); \
        } \
          \
        template <typename T> \
        bool CC_CONCATENATE(set, name_)(T&& value) \
        { \
            if (CC_CONCATENATE(m_, name_) == value) { \
                return false; \
            } \
            CC_CONCATENATE(m_, name_) = std::forward<T>(value); \
            emit CC_CONCATENATE(CC_CONCATENATE(sig, name_), Changed)(CC_CONCATENATE(m_, name_)); \
            return true;\
        } \
        \
        bool CC_CONCATENATE(set, name_)(const QVariant& value) \
        { \
            if ((!value.isValid()) || (!value.canConvert<type_>())) { \
                return false; \
            } \
            return CC_CONCATENATE(set, name_)(value.value<type_>()); \
        } \
    private: \
        type_ CC_CONCATENATE(m_, name_) CC_EXPAND(__VA_ARGS__);

#define VOLATILE_CC_MEMBER(type_, name_, ...) \
    public: \
        const type_& CC_CONCATENATE(get, name_)() const \
        { \
            return CC_CONCATENATE(m_, name_); \
        } \
        \
        QVariant CC_CONCATENATE(CC_CONCATENATE(get, name_), AsVariant)() const \
        { \
            return QVariant::fromValue((CC_CONCATENATE(m_, name_))); \
        } \
        \
        template <typename T> \
        bool CC_CONCATENATE(set, name_)(T&& value) \
        { \
            CC_CONCATENATE(m_, name_) = std::forward<T>(value); \
            emit CC_CONCATENATE(CC_CONCATENATE(sig, name_), Changed)(CC_CONCATENATE(m_, name_)); \
            return true;\
        } \
        bool CC_CONCATENATE(set, name_)(const QVariant& value) \
        { \
            if ((!value.isValid()) || (!value.canConvert<type_>())) { \
                return false; \
            } \
            return CC_CONCATENATE(set, name_)(value.value<type_>()); \
        } \
        \
    private: \
        type_ CC_CONCATENATE(m_, name_) CC_EXPAND(__VA_ARGS__);
