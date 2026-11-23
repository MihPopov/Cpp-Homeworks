#include <cstring>

struct Stack;

void Clear(Stack* stack);
char** update_data(Stack* stack, size_t newSize);

struct Stack {
  // YOUR CODE HERE
  char** data = nullptr;
  size_t size = 0;
  size_t capacity = 0;

  ~Stack() {
    Clear(this);
  }
};

// YOUR CODE HERE

size_t Size(const Stack* stack) {
  return (*stack).size;
}

void Push(Stack* stack, const char* str) {
  size_t oldSize = Size(stack);
  (*stack).data = update_data(stack, oldSize + 1);
  (*stack).data[oldSize] = new char[std::strlen(str) + 1];
  std::strcpy((*stack).data[oldSize], str);
  (*stack).size++;
}

void Pop(Stack* stack) {
  size_t size = Size(stack);
  if (size == 0) return;
  delete[] (*stack).data[size - 1];
  (*stack).size--;
}

const char* Top(const Stack* stack) {
  if (Size(stack) == 0) return nullptr;
  return (*stack).data[Size(stack) - 1];
}

void Clear(Stack* stack) {
  size_t size = Size(stack);
  for (size_t i = 0; i < size; i++) {
    delete[] (*stack).data[i];
  }
  delete[] (*stack).data;
  (*stack).data = nullptr;
  (*stack).size = 0;
  (*stack).capacity = 0;
}

char** update_data(Stack* stack, const size_t newSize) {
  if (newSize <= (*stack).capacity) {
    return (*stack).data;
  }
  size_t newCapacity = ((*stack).capacity == 0) ? 1 : (*stack).capacity * 2;
  (*stack).capacity = newCapacity;
  char** newData = new char*[newCapacity];
  for (size_t i = 0; i < (*stack).size; i++) {
    newData[i] = (*stack).data[i];
  }
  delete[] (*stack).data;
  return newData;
}