#include "../utils/iohandler.h"
#ifndef PASTEVENTS_H_
#define PASTEVENTS_H_
typedef struct PEQueElems{
    char* command;
    struct PEQueElems* Next;
}PEQueElems;
typedef PEQueElems* Event;
typedef struct stEvents{
    Event Front;
    Event Rear;
    int num_events;
}stEvents;
typedef stEvents* Events;

Events InitEventsQ();
Event Create_Event(char* command);
void AddEvent(char* command);
void Create_history();
void Write_History();
void pastevents_handler(char* command,redirect io_info);
void pastevents();
void pastevents_purge();
void pastevents_execute(char* command_num);
#endif