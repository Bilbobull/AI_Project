// Author: Gonzalo Rojo

#pragma once

#include <vector>

class System
{
public:
  virtual void Init(void) = 0;
  virtual void Update(double dt) = 0;
  virtual void Free(void) = 0;
private:
};

//double dt;
