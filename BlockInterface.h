#ifndef BLOCK_INTERFACE_H
#define BLOCK_INTERFACE_H


class BlockInterface
{
 public:
  virtual bool IsExtension(const int row) const = 0;
  virtual void Extend() = 0;
  virtual void Draw() = 0;
  virtual void Finalize() = 0;
  virtual ~BlockInterface(){};

};

#endif
