#ifndef sensors_h
#define sensors_h

void sensorsInitialize(void);
int32_t sensorReadForward(void);
int32_t sensorReadLeft(void);
int32_t sensorReadRight(void);

#endif