/*******************************************************************************
MIT License
-----------

Copyright (c) 2015 Peter S. Barr
Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*******************************************************************************/

#ifndef PB_CIRCULAR_BUFFER_HPP
#define PB_CIRCULAR_BUFFER_HPP

template <typename T>
class pb_cbuffer
{
  private:
    T*      data_      = nullptr;
    size_t  size_      = 0;
    size_t  capacity_  = 0;
    size_t  i0_        = 0;
    size_t  if_        = 0;
  
  public:
    //Default Constructor
    pb_cbuffer() { }
    
    //Copy Constructor
    pb_cbuffer(const pb_cbuffer<T>& other)
    {
      size_ = other.size_;
      capacity = other.capacity_;
      i0_ = other.i0_;
      if_ = other.if_;
      data_ = new T[other.capacity_];
      for(auto i = 0; i < other.capacity_; i++)
        data_[i] = other.data_[i];
    }
    
    //Move Constructor
    pb_cbuffer(pb_cbuffer<T>&& other) :
      data_(other.data_), (size_(other.size_), capacity_(other.capacity_),
      i0_(other.i0_), if_(other.if_)
    {
      other.data_ = nullptr;
      other.size_ = 0;
      other.capacity_ = 0;
      other.i0_ = 0;
      other.if_ = 0;
    }
    
    //Default Assignment Operator
    pb_cbuffer& operator=(const pb_cbuffer<T>& rhs);
    
    //Move Assignment Operator
    pb_cbuffer& operator=(pb_cbuffer<T>&& rhs);
    
    //Destructor
    ~pb_cbuffer()
    {
      delete [] data_;
      data_ = nullptr;
    }
};

#endif //PB_CIRCULAR_BUFFER_HPP
