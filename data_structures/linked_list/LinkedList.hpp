#ifndef PB_LINKED_LIST_HPP
#define PB_LINKED_LIST_HPP

namespace _LL_Detail
{
  template <typename T>
  class _LL_Node
  {
    public:
      T          data;
      _LL_Node*  prev;
      _LL_Node*  next;
      
      Node() : prev(nullptr), next(nullptr) {}
      Node(const T& value) : prev(nullptr), next(nullptr), data(value) {}
      ~Node() {}
  };
}

// A LinkedList::iterator
template <typename T>
struct _LinkedList_Iterator
{
  typedef _LinkedList_Iterator<T>   _self;
  typedef _LL_Detail::_LL_Node<T>   _node;
  
  typedef T                         value_type;
  typedef T*                        pointer;
  typedef T&                        reference;
  
  //Only member
  _node* m_node_;
  
  _LinkedList_Iterator() : m_node_() {}
  _LinkedList_Iterator(_node* x) : m_node_(x) {}
  
  reference operator*() const { return m_node_->data; }
  pointer operator->() const { return &(m_node_->data); }
  
  _self& operator++()
  {
    m_node_ = m_node_->next;
    return *this;
  }
  
  _self operator++(int)
  {
    _self tmp = *this;
    m_node_ = m_node_->next;
    return tmp;
  }
  
  _self& operator--()
  {
    m_node_ = m_node_->prev;
    return *this;
  }
  
  _self operator--(int)
  {
    _self tmp = *this;
    m_node_ = m_node_->prev;
    return tmp;
  }
  
  bool operator==(const _self& rhs) const { return m_node_ == rhs.m_node_; }
  bool operator!=(const _self& rhs) const { return m_node_ != rhs.m_node_; }
};

// A LinkedList::const_iterator
template <typename T>
struct _LinkedList_Const_Iterator
{
  typedef _LinkedList_Const_Iterator<T>   _self;
  typedef const _LL_Detail::_LL_Node<T>   _node;
  typedef _LinkedList_Iterator<T>         iterator;
  
  typedef T                               value_type;
  typedef const T*                        pointer;
  typedef const T&                        reference;
  
  //Only member
  const _node* m_node_;
  
  _LinkedList_Const_Iterator() : m_node_() {}
  _LinkedList_Const_Iterator(const _node* x) : m_node_(x) {}
  _LinkedList_Const_Iterator(const iterator& oth) : m_node_(oth.m_node_) {}
  
  reference operator*() const { return m_node_->data; }
  pointer operator->() const { return &(m_node_->data); }
  
  _self& operator++()
  {
    m_node_ = m_node_->next;
    return *this;
  }
  
  _self operator++(int)
  {
    _self tmp = *this;
    m_node_ = m_node_->next;
    return tmp;
  }
  
  _self& operator--()
  {
    m_node_ = m_node_->prev;
    return *this;
  }
  
  _self operator--(int)
  {
    _self tmp = *this;
    m_node_ = m_node_->prev;
    return tmp;
  }
  
  bool operator==(const _self& rhs) const { return m_node_ == rhs.m_node_; }
  bool operator!=(const _self& rhs) const { return m_node_ != rhs.m_node_; }
};

template <typename T>
class LinkedList
{
  public:
    typedef T                               value_type;
    typedef T*                              pointer;
    typedef T&                              reference;
    
    typedef _LinkedList_Iterator<T>         iterator;
    typedef _LinkedList_Const_Iterator<T>   const_iterator;
    
    typedef size_t                          size_type;
    
  protected:
    typedef _LinkedList_Detail::_LL_Node    node;
    
    LinkedList() : head_(nullptr), tail_(nullptr), size_(0) { }
    LinkedList(const LinkedList<value_type>&);

    size_t size()   { return size_; }
    size_t count()  { return size_; }
    bool empty()    { return size_ == 0; }
    bool is_empty() { return size_ == 0; }
    
    void insert_front(const T&);
    void insert_back(const T&);
    
    void sort();
    template <class StrictWeakOrdering> void sort(StrictWeakOrdering);
    
    void clear() noexcept;
    
    bool pop_front();
    bool pop_back();
    bool remove_front() { return pop_front(); }
    bool remove_back()  { return pop_back(); }

    reference_type peek_front() const;
    reference_type peek_back() const;
    reference_type get_front() const { return peek_front(); }
    reference_type get_back() const { return peek_back(); }

    bool remove_first_occurrence(const_reference_type);
    bool remove_last_occurrence(const_reference_type);
    
    bool contains(const_reference_type) const;
};

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& toCopy)
{

}

template <typename T>
LinkedList<T>::~LinkedList()
{
  clear();
}

template <typename T>
void LinkedList<T>::insert_front(const T& value)
{
  Node<T>* ins = new Node(value);
  if(is_empty())
  {
    head_ = ins;
    tail_ = head_;
  }
  else
  {
    ins->next = head_;
    head_->prev = ins;
    head_ = ins;
  }
  size_++;
}

template <typename T>
void LinkedList<T>::insert_back(const T& value)
{
  Node<T>* ins = new Node(value);
  if(is_empty())
  {
    head_ = ins;
    tail_ = head_;
  }
  else
  {
    tail_->next = ins;
    ins->prev = tail_;
    tail_ = ins;
  }
  size_++;
}

template <typename T>
void LinkedList<T>::clear()
{
  Node<T>* cur = head_;
  while(cur != nullptr)
  {
    Node<T>* next = cur->next;
    delete cur;
    cur = next;
  }
  head_ = nullptr;
  tail_ = nullptr;
  size_ = 0;
}

template <typename T>
bool LinkedList<T>::contains(const T& value)
{
  node_pointer cur = head_;
  
  while(cur != nullptr)
  {
    if(cur->value == value)
      return true;
    cur = cur->next;
  }
  return false;
}

template <typename T>
bool LinkedList<T>::remove_first_occurrence(const T& value)
{

}

template <typename T>
bool LinkedList<T>::remove_last_occurrence(const T& value)
{

}

template <typename T>
bool LinkedList<T>::pop_front()
{
  if(is_empty())
    return false;
  
  return true;
}

template <typename T>
bool LinkedList<T>::pop_back()
{
  if(is_empty())
    return false;
  
  return true;
}

template <typename T>
void LinkedList<T>::sort()
{

}

template <typename T> template <class StrictWeakOrdering>
void LinkedList<T>::sort(StrictWeakOrdering comp)
{
  
}

#endif  //PB_LINKED_LIST_HPP
