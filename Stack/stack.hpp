#include <cstring>

struct Stack;

void Clear(Stack* stack);
char** recreate_data(Stack* oldStack, size_t newSize);

struct Stack {
  // YOUR CODE HERE
  char** data = nullptr;
  size_t size = 0;

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
  (*stack).data = recreate_data(stack, oldSize + 1);
  (*stack).data[oldSize] = new char[std::strlen(str) + 1];
  std::strcpy((*stack).data[oldSize], str);
  (*stack).size++;
}

void Pop(Stack* stack) {
  size_t size = Size(stack);
  if (size == 0) return;
  delete[] (*stack).data[size - 1];
  (*stack).data = recreate_data(stack, size - 1);
  (*stack).size--;
}

char* Top(const Stack* stack) {
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
}

char** recreate_data(Stack* oldStack, const size_t newSize) {
  if (newSize == 0) return nullptr;
  char** newData = new char*[newSize];
  for (size_t i = 0; i < Size(oldStack) && i < newSize; i++) {
    newData[i] = (*oldStack).data[i];
  }
  delete[] (*oldStack).data;
  return newData;
}