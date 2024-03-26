#ifndef CONTROLLER_CONTROLLER_H
#define CONTROLLER_CONTROLLER_H

#include "../model/affinis.h"
#include "../model/mementoobject.h"
#include "../model/model.h"

namespace s21 {

class Controller {
 public:
  Controller() = default;
  ~Controller() = default;
  void LoadModel(const std::string& file_name);
  Model* getModel();
  AffinisOperation* AffinisChange(Strategy* strategy);
  MementoObject* SaveObject();

 private:
  Model* model_;
  AffinisOperation* affinis_;
  MementoObject* memento_;
};

}  // namespace s21

#endif  // CONTROLLER_CONTROLLER_H
