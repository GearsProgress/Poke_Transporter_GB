#ifndef _LIBSTD_REPLACEMENTS_H
#define _LIBSTD_REPLACEMENTS_H

#include <inttypes.h>
#include <cstring>
#include <new>

// To reduce the binary size, we need to get rid of libstdc++
// But we were happily using some functions that made life easier.
// so this file was created to provide some similar functions/functionalities
// (although stripped down to the bare minimum we're using)

namespace ptgb
{
    /**
     * This utility/convenience function converts the given value to a string.
     * WARNING: it AND its other variants always use the same buffer.
     * So calling it more than once will overwrite the previously returned string!
     * 
     * Be careful!
     * In case you want to convert more than one int to string within the same call,
     * consider using npf_snprintf instead!
     * 
     * Also: if you want to hold on to the converted value, consider copying the returned string
     */
    const char* to_string(int intVal);
    
    
    /**
     * This utility/convenience function converts the given value to a string.
     * WARNING: it AND its other variants always use the same buffer.
     * So calling it more than once will overwrite the previously returned string!
     * 
     * Be careful!
     * In case you want to convert more than one int to string within the same call,
     * consider using npf_snprintf instead!
     * 
     * Also: if you want to hold on to the converted value, consider copying the returned string
     */
    const char* to_string(unsigned int wordVal);

    template <class ValueType>
    class vector
    {
    public:
        static constexpr size_t default_capacity = 10;

        vector()
            : buffer_()
            , capacity_(default_capacity)
            , count_(0)
        {
            buffer_ = static_cast<ValueType*>(::operator new(capacity_ * sizeof(ValueType)));
        }

        vector(const ValueType* valueList, size_t listSize)
            : buffer_()
            , capacity_(listSize)
            , count_(0)
        {
            buffer_ = static_cast<ValueType*>(::operator new(capacity_ * sizeof(ValueType)));
            insert(valueList, listSize);
        }

        ~vector()
        {
            clear();
            ::operator delete(buffer_);
        }

        void reserve(size_t newSize)
        {
            ValueType *oldValue;
            ValueType *oldBuffer;
            if(newSize <= capacity_)
            {
                return;
            }
            oldBuffer = buffer_;
            buffer_ = static_cast<ValueType*>(::operator new(newSize * sizeof(ValueType)));
            capacity_ = newSize;

            for (size_t i = 0; i < count_; ++i)
            {
                oldValue = oldBuffer + i;

                new(buffer_ + i) ValueType(*oldValue);
                oldValue->~ValueType();
            }

            ::operator delete(oldBuffer);
        }

        void resize(size_t newSize)
        {
            resize(newSize, ValueType());
        }

        void resize(size_t newSize, const ValueType& value)
        {
            if(newSize < count_)
            {
                for(size_t i=0; i < (count_ - newSize); ++i)
                {
                    pop_back();
                }
            }
            else if(newSize > count_)
            {
                reserve(newSize);
                for(size_t i=0; i < (newSize - count_); ++i)
                {
                    push_back(value);
                }
            }
        }

        void push_back(const ValueType& value)
        {
            if(count_ == capacity_)
            {
                reserve(capacity_ * 2);
            }
            new(buffer_ + count_) ValueType(value);
            ++count_;
        }

        void pop_back()
        {
            ValueType *value = buffer_ + ((count_ - 1));
            value->~ValueType();
            --count_;
        }

        void insert(vector<ValueType>& otherList)
        {
            reserve(count_ + otherList.size());

            for(size_t i=0; i < otherList.size(); ++i)
            {
                push_back(otherList.at(i));
            }
        }

        void insert(const ValueType* list, size_t listSize)
        {
            reserve(count_ + listSize);
            for(size_t i=0; i < listSize; ++i)
            {
                push_back(list[i]);
            }
        }

        void clear()
        {
            resize(0);
        }

        size_t size() const { return count_; }
        size_t capacity() const { return capacity_; }

        ValueType& at(size_t index)
        {
            return operator[](index);
        }

        const ValueType& at(size_t index) const
        {
            return operator[](index);
        }
        
        ValueType& operator[](size_t index)
        {
            return *(buffer_ + index);
        }
        
        const ValueType& operator[](size_t index) const
        {
            return *(buffer_ + index);
        }
    private:
        ValueType *buffer_;
        size_t capacity_;
        size_t count_;
    };
}

#endif