#include "controller.h"

void s21::Controller::LoadModel(const std::string& file_name) {
  model_ = &Model::getInstance();
  model_->OpenFile(file_name);
}

s21::Model* s21::Controller::getModel() { return model_; }

s21::AffinisOperation* s21::Controller::AffinisChange(Strategy* strategy) {
  affinis_ = new AffinisOperation(strategy);
  return affinis_;
}

s21::MementoObject* s21::Controller::SaveObject() {
  memento_ = new MementoObject();
  return memento_;
}
