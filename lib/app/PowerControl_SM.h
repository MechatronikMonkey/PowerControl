// Autogenerated with StateSmith 0.9.14-alpha+1f116014cd5077a4daa688d05b563fe0be54ef0c.
// Algorithm: Balanced1. See https://github.com/StateSmith/StateSmith/wiki/Algorithms

// Whatever you put in the IRenderConfig.FileTop section ends up at the top of the generated file(s).
// user IRenderConfigC.HFileTop: whatever you want to put in here.
#pragma once
#include <stdint.h>

// user IRenderConfigC.HFileIncludes: whatever you want to put in here.
typedef enum PowerControl_SM_EventId
{
    PowerControl_SM_EventId_DO = 0, // The `do` event is special. State event handlers do not consume this event (ancestors all get it too) unless a transition occurs.
} PowerControl_SM_EventId;

enum
{
    PowerControl_SM_EventIdCount = 1
};

typedef enum PowerControl_SM_StateId
{
    PowerControl_SM_StateId_ROOT = 0,
    PowerControl_SM_StateId_STATE_ERROR = 1,
    PowerControl_SM_StateId_STATE_INIT = 2,
    PowerControl_SM_StateId_STATE_NORMALOPERATION = 3,
    PowerControl_SM_StateId_STATE_CONTROLPOWER = 4,
    PowerControl_SM_StateId_STATE_FULLPOWER = 5,
    PowerControl_SM_StateId_STATE_OFF = 6,
} PowerControl_SM_StateId;

enum
{
    PowerControl_SM_StateIdCount = 7
};


// Generated state machine
// forward declaration
typedef struct PowerControl_SM PowerControl_SM;

// State machine variables. Can be used for inputs, outputs, user variables...
typedef struct PowerControl_SM_Vars
{
    int non_expanded_user_example_var;
    int auto_expanded_user_example_var;
} PowerControl_SM_Vars;


// event handler type
typedef void (*PowerControl_SM_Func)(PowerControl_SM* sm);

// State machine constructor. Must be called before start or dispatch event functions. Not thread safe.
void PowerControl_SM_ctor(PowerControl_SM* sm);

// Starts the state machine. Must be called before dispatching events. Not thread safe.
void PowerControl_SM_start(PowerControl_SM* sm);

// Dispatches an event to the state machine. Not thread safe.
void PowerControl_SM_dispatch_event(PowerControl_SM* sm, PowerControl_SM_EventId event_id);

// Thread safe.
char const * PowerControl_SM_state_id_to_string(PowerControl_SM_StateId id);

// Thread safe.
char const * PowerControl_SM_event_id_to_string(PowerControl_SM_EventId id);

// Generated state machine
struct PowerControl_SM
{
    // Used internally by state machine. Feel free to inspect, but don't modify.
    PowerControl_SM_StateId state_id;
    
    // Used internally by state machine. Don't modify.
    PowerControl_SM_Func ancestor_event_handler;
    
    // Used internally by state machine. Don't modify.
    PowerControl_SM_Func current_event_handlers[PowerControl_SM_EventIdCount];
    
    // Used internally by state machine. Don't modify.
    PowerControl_SM_Func current_state_exit_handler;
    
    // Variables. Can be used for inputs, outputs, user variables...
    PowerControl_SM_Vars vars;
};
