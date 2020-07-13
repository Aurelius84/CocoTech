/*
* 描述：实现一个支持capcity的队列
*/

#include <iostream>
#include <exception>

using uint32 = unsigned int;
template <typename T>
class Queue {
 private:
  class QueueEmptyException : public std::exception {
      public:
       virtual const char* what() const throw() { return "Queue is empty"; }
  } excp_empty;

  uint32 m_capacity;
  uint32 m_size;
  uint32 m_front;
  uint32 m_back;
  T* m_data;

  public:
    Queue(uint32 max): m_capacity(max),
    m_size(0), m_front(0), m_back(-1){
      m_data = new T[max];
    }

    ~Queue() { delete[] m_data; }

    private:
     Queue(const Queue&);
     Queue& operator=(const Queue&);

    public:
        // 出队操作
        inline void dequeue(){
          // 如果没有实际元素要出队，直接返回
          if (m_size == 0) return;

          m_size--;
          m_front++;
          // 如果头部标识已经递增到capacity，重置下
          if(m_front == m_capacity){
            m_front = 0;
          }
        }

        inline const T& front() const {
          if (m_size == 0) throw excp_empty;
          return m_data[m_front];
        }

        inline bool is_empty(){
          if (m_size == 0) return true;
          return false;
        }
        // 入队操作
        bool enqueue(const T& element){
            // TODO: 支持扩容功能
            if(m_size == m_capacity){
              return false;
            }else{
              m_size++;
              m_back++;
              if(m_back == m_capacity){
                m_back = 0;
              }
              m_data[m_back] = element;
              return true;
            }
        }

        inline uint32 count() const { return m_size; }
        inline uint32 capacity() const { return m_capacity; }
};

int main() {
    Queue<int> queue(20);
    queue.enqueue(0);
    queue.enqueue(1);
    std::cout << queue.count() << "\n";
    int ele = queue.front();
    queue.dequeue();
    std::cout << ele << "\n";
    return 0;
}