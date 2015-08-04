/*
  ==============================================================================

    PythonEvent.h
    Created: 27 Jul 2014 4:42:07pm
    Author:  Francesco Battaglia

  ==============================================================================
*/

#ifndef __PYTHONEVENT_H_4B3D9292__
#define __PYTHONEVENT_H_4B3D9292__

struct PythonEvent;

struct PythonEvent {
    unsigned char type;
    int sampleNum;
    unsigned char eventId;
    unsigned char eventChannel;
    unsigned char numBytes;
    unsigned char *eventData;
    struct PythonEvent *nextEvent;
};



#endif  // __PYTHONEVENT_H_4B3D9292__
