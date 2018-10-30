// This file throttles with a backoff mechanism
// Here is a little test.  Please fill out the comments on each line 

// #1 ...
#ifndef __BACKOFF_H__
#define __BACKOFF_H__

// #2 ...
int backOffCount = 0;
long minBackoff = 5000; // 1000 if you don't mind sending lots of data
long maxBackoff = 60000;
long minJitter = 50;
long maxJitter = 1000;

// #3 ...
long currDelay = minBackoff;
long lastRequestTime = millis();  // what is millis?

// #4 ...
void resetBackoff() {
  backOffCount = 0;
}

// Returns true if the backoff duration has passed
bool backoff() {

  //
  if ((millis() - lastRequestTime) > currDelay) {

    //
    backOffCount++;

    //
    currDelay = (backOffCount * backOffCount * minBackoff) + random(minJitter,maxJitter);

    //
    if (currDelay > maxBackoff) {
      currDelay = maxBackoff;
    }

    //
    Serial.printf("Waiting: %ld\n", currDelay);
    
    delay(500);

    //
    lastRequestTime = millis();
    
    return true;
  }
  
  return false;
}

#endif
