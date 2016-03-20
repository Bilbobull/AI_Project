#include "Graphics\Context.h"
#include "Graphics\GraphicsSystem.h"
#include "Input\InputSystem.h"
#include "Systems.h"

extern std::vector <System*> Systems;
extern bool Running;

int main(int argc, char* argv[])
{
  Running = true;

  Systems.push_back(new GraphicsSystem());
  Systems.push_back(new InputSystem());


  for (auto it : Systems)
    it->Init();

  while (Running == true)
  {
    for (auto it : Systems)
      it->Update(0);
  }

  return 0;
}