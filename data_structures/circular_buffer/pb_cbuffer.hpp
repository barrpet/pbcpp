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
