#ifndef BST_HPP
#define BST_HPP

template <class T>
class BST
{
  private:
    struct node;
    struct node
    {
      T     value;
      node* parent = nullptr;
      node* left   = nullptr;
      node* right  = nullptr;
      
      node* find(const T& key)
      {
        node* cur = this;
        while(cur)
        {
          if(key < value)
            cur = cur->left;
          else if(key > value)
            cur = cur->right;
          else
            break;
        }
        return cur;
      }
    };
    
  private:
    size_t size_;
    Node<T>* root_;
  
  public:
    BST();
    BST(const BST& other);
    ~BST();
    
    BST& operator=(const BST& rhs);
    
    bool search(const T& val) const;
    bool find(const T& val) const { return search(val); }
    bool contains(const T& val) const { return search(val); }
    
    bool insert(T& val);
    
    bool remove_min();
    bool remove_max();
    bool remove(const T& val);
    
    T& max();
    T& min();
    
    bool empty() const { return size_ == 0; }
    bool is_empty() const { return empty(); }
    size_t size() const { return size_; }
    
    size_t height() const;
    size_t depth() const { return height(); }
};

#endif //BST_HPP
