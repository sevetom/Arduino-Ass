#include "GateTask.h"

GateTask::GateTask(int pin, gateMode mode) {
  this->gate = new Gate(pin);
  this->mode = mode;
  this->isOpen = false;
  this->currentTime = 0;
}

void GateTask::init(int period) {
  Task::init(period);
}

void GateTask::tick() {
  switch (this->mode) {
    case OPEN:
      if (this->currentTime == 0) {
        this->gate->open();
        Serial.println("OPENNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN");
      }
      if (this->currentTime >= OPEN_TIME) {
        Serial.println("STOPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP");
        this->gate->stop();
        this->currentTime = 0;
      }
      break;
    case CLOSE:
      if (this->currentTime == 0) {
        this->gate->close();
        Serial.println("CLOSEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE");
      }
      if (this->currentTime >= CLOSE_TIME) {
          Serial.println("STOPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP");
          this->gate->stop();
          this->currentTime = 0;
      }
      break;
  }
  currentTime += this->myPeriod + this->timeElapsed;
}