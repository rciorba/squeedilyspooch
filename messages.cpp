#include "network.h"

uint16_t Messages::M_MOVE;
uint16_t Messages::M_PRESS1;
uint16_t Messages::M_RELEASE1;


void Messages::initialize(){
  M_MOVE = htons(1);
  M_PRESS1 = htons(2);
  M_RELEASE1 = htons(3);
}

