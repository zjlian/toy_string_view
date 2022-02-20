#pragma once

#include <cassert>
#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <type_traits>

namespace toy
{

    /// @brief C++14 的 string_view 简易实现
    class StringView
    {
    public:
        using value_type = char;
        using const_pointer = const value_type *;
        using const_iterator = const value_type *;
        using const_reference = const value_type &;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        /// @brief 从 std::string 实例构造
        template <typename StringClass>
        StringView(const StringClass &string) noexcept
            : StringView(string.data(), string.size())
        {
            static_assert(
                std::is_same<typename StringClass::value_type, char>::value,
                "Type StringClass must have member type value_type");
        }

        /// @brief 从 C 风格字符串构造
        constexpr StringView(const char *str)
            : ptr_(str), length_(str ? StringLength(str) : 0) {}

        /// @brief 从 const char * 类型构造，需要提供长度信息 length
        constexpr StringView(const char *ptr, size_t length)
            : ptr_(ptr), length_(length) {}

        /*--- iterator api ---*/

        /// @brief 获取首字符的迭代器
        constexpr const_iterator begin() const noexcept
        {
            return ptr_;
        }

        constexpr const_iterator cbegin() const noexcept
        {
            return begin();
        }

        /// @brief 获取尾字符串的迭代器
        constexpr const_iterator end() const noexcept
        {
            return ptr_ + length_;
        }

        constexpr const_iterator cend() const noexcept
        {
            return cend();
        }

        /// @brief 获取逆向迭代器的首迭代器
        const_reverse_iterator rbegin() const noexcept
        {
            return const_reverse_iterator(end());
        }

        const_reverse_iterator crbegin() const noexcept
        {
            return rbegin();
        }

        /// @brief 获取逆向迭代器的尾迭代器
        const_reverse_iterator rend() const noexcept
        {
            return const_reverse_iterator(begin());
        }

        const_reverse_iterator crend() const noexcept
        {
            return rend();
        }

        /*--- element access api ---*/

        /// @brief 访问指定字符
        constexpr const_reference operator[](size_t pos) const
        {
            assert(pos < size());
            return ptr_[pos];
        }

        /// @brief 访问指定字符，带有边界检查
        constexpr const_reference at(size_t pos) const
        {
            if (pos >= size())
            {
                throw std::out_of_range{"toy::StringView::at"};
            }

            return ptr_[pos];
        }

        /// @brief 获取首个字符
        constexpr const_reference front() const
        {
            assert(!empty());
            return ptr_[0];
        }

        /// @brief 获取末尾字符
        constexpr const_reference back() const
        {
            assert(!empty());
            return ptr_[size() - 1];
        }

        /// @brief 获取首字符的指针
        constexpr const_pointer data() const
        {
            return ptr_;
        }

        /*--- capacity api ---*/

        constexpr size_t
        size() const noexcept
        {
            return length_;
        }

        constexpr bool empty() const noexcept
        {
            return length_ == 0;
        }

    private:
        /// @brief 获取 C 风格的字符串长度
        static constexpr size_t StringLength(const char *str)
        {
            return __builtin_strlen(str);
        }

        // 字符串数据起始位置指针
        const char *ptr_;
        // 字符串数据长度
        size_t length_;
    };

} // namespace toy