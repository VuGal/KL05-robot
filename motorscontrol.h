#ifndef motorscontrol_h
#define motorscontrol_h

void stopMotors(void);
void forwardsMotors(void);
void backwardsMotors(void);
void turnLeft(void);
void turnRight(void);
void limitSwitchInitialize(void);
int32_t limitSwitchLeftHandler(void);
int32_t limitSwitchRightHandler(void);

#endif