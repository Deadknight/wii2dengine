/*
    _____               __  ___          __            ____        _      __
   / ___/__ ___ _  ___ /  |/  /__  ___  / /_____ __ __/ __/_______(_)__  / /_
  / (_ / _ `/  ' \/ -_) /|_/ / _ \/ _ \/  '_/ -_) // /\ \/ __/ __/ / _ \/ __/
  \___/\_,_/_/_/_/\__/_/  /_/\___/_//_/_/\_\\__/\_, /___/\__/_/ /_/ .__/\__/
                                               /___/             /_/
                                             
  See Copyright Notice in gmMachine.h

*/

#ifndef _GMTHREAD_H_
#define _GMTHREAD_H_

#include "gmConfig.h"
#include "gmListDouble.h"
#include "gmHash.h"
#include "gmVariable.h"
#include "gmMachine.h"
#include "gmStringObject.h"
#include "gmUserObject.h"

class gmFunctionObject;
class gmStringObject;
class gmTableObject;
class gmUserObject;
class gmBlock;
struct gmSignal;

#define GMTHREAD_SLACKSPACE  6 // floating slack space above tos for operator calls
#define GM_INVALID_THREAD 0

/// \struct gmStackFrame
/// \brief The stack order is as follows: this, fp, p0..pn-1, l0..ln-1.  gmStackFrame objects are allocated from the gmMachine.
///        Base pointer is at the first parameter.
struct gmStackFrame
{
  gmStackFrame * m_prev;
  const gmuint8 * m_returnAddress;
  int m_returnBase;
};

/// \class gmThread
/// \brief gmThread.. try to keep this class's memory footprint small.. at the time of this comment, its
///        76 bytes.
class gmThread : public gmListDoubleNode<gmThread>, public gmHashNode<int, gmThread>
{
public:
  gmThread(gmMachine * a_machine, int a_initialByteSize = GMTHREAD_INITIALBYTESIZE);
  virtual ~gmThread();

  enum State
  {
    RUNNING = 0,
    SLEEPING,
    BLOCKED,
    KILLED,

    EXCEPTION, //!< exception state, for debugging

    SYS_PENDING,
    SYS_YIELD, 
    SYS_EXCEPTION,
  };

  GM_INLINEWII const int GetKey() const { return m_id; }

#if GM_USE_INCGC
  void GCScanRoots(gmMachine* a_machine, gmGarbageCollector* a_gc);
#else //GM_USE_INCGC
  /// \brief Mark() will call Mark() for all objects in the stack.
  void Mark(gmuint32 a_mark);
#endif //GM_USE_INCGC

  /// \brief Sys_Execute() will perform execution on this thread.  a this, function references, params and stack
  ///        frame must be pushed before a call to execute will succeed.
  /// \param a_return will be set to the return variable iff Sys_Execute returns gmThread::KILLED. 
  /// \return the new thread state.
  State Sys_Execute(gmVariable * a_return = NULL);

  /// \brief Sys_Reset() will reset the thread.
  void Sys_Reset(int a_id);

  /// \brief Sys_SetState() will set the thread state.
  GM_INLINEWII void Sys_SetState(State a_state) { m_state = a_state; }

  /// \brief PushStackFrame will push a stack frame and adjust the instruction and code pointers. 
  ///        If the function to be called is a c bound function, the call will occur within PushStackFrame.
  ///        Before PushStackFrame is called, this, fp, and params must be pushed on the stack.
  /// \param a_numParameters is the number of params pushed after the function ref.
  /// \param a_ip is the current instruction pointer (pointing to instruction after call.) will be adjusted for new function.
  /// \param a_cp is the current code pointer.  will be adjusted for the new function. a_cp MUST be valid if a_ip is valid.
  /// \return gmThreadState
  State PushStackFrame(int a_numParameters, const gmuint8 ** a_ip = NULL, const gmuint8 ** a_cp = NULL);

  /// \brief GetTop() will return the top of stack
  GM_INLINEWII gmVariable * GetTop() const { return &m_stack[m_top]; }

  /// \brief GetBottom() will return the bottom of stact
  GM_INLINEWII gmVariable * GetBottom() const { return m_stack; }

  /// \brief SetTop() will set the top of stack
  GM_INLINEWII void SetTop(gmVariable * a_top) { m_top = a_top - m_stack; }

  /// \brief GetBase() will return the current stack base.
  GM_INLINEWII gmVariable * GetBase() const { return &m_stack[m_base]; }
  GM_INLINEWII int GetIntBase() const { return m_base; }

  /// \brief GetMachine() will return the stacks parent machine.
  GM_INLINEWII gmMachine * GetMachine() const { return m_machine; }

  /// \brief GetThis() will return the this variable for the current stack frame.
  GM_INLINEWII const gmVariable * GetThis() const { return &m_stack[m_base - 2]; }

  /// \brief GetFunction() will return the current executing function.
  GM_INLINEWII const gmVariable * GetFunction() const { return &m_stack[m_base - 1]; }
  GM_INLINEWII const gmFunctionObject * GetFunctionObject() const;

  /// \brief GetNumParams() returns the number parameters pushed into the current cFunction call.
  GM_INLINEWII int GetNumParams() const { return m_numParameters; }

  /// \brief GetFrame() will return the top stack frame.
  GM_INLINEWII const gmStackFrame * GetFrame() const { return m_frame; }

  //
  // Push methods
  //

  GM_INLINEWII gmVariable &Pop() { return m_stack[--m_top]; }
  GM_INLINEWII void Push(const gmVariable &a_variable) { m_stack[m_top++] = a_variable; }
  GM_INLINEWII void PushNull();
  GM_INLINEWII void PushInt(gmptr a_value);
  GM_INLINEWII void PushFloat(gmfloat a_value);
  GM_INLINEWII void PushString(gmStringObject * a_string);
  GM_INLINEWII void PushTable(gmTableObject * a_table);
  GM_INLINEWII void PushFunction(gmFunctionObject * a_function);
  GM_INLINEWII void PushUser(gmUserObject * a_user);

  GM_INLINEWII gmStringObject * PushNewString(const char * a_value, int a_len = -1); //!< PushNewString() will push a new string object onto tos.
  GM_INLINEWII gmTableObject * PushNewTable(); //!< PushNewTable() will push a new table onto tos.
  GM_INLINEWII gmUserObject * PushNewUser(void * a_user, int a_userType); //!< PushNewUser() will push a new user object onto tos.

  //
  // Parameter methods. (do not cause an error if the desired parameter is incorrect type)
  // Versions that return bool return false if type was invalid, otherwise true, even if param was out of range. NOTE: Could switch to more complex return code, but user could simply check num params for range check if needed.
  // 

  GM_INLINEWII int ParamInt(int a_param, gmptr a_default = 0) const;
  GM_INLINEWII bool ParamInt(int a_param, int& a_value, gmptr a_default = 0) const;
  GM_INLINEWII gmfloat ParamFloat(int a_param, gmfloat a_default = 0.0f) const;
  GM_INLINEWII bool ParamFloat(int a_param, gmfloat& a_value, gmfloat a_default = 0.0f) const;
  GM_INLINEWII gmfloat ParamFloatOrInt(int a_param, gmfloat a_default = 0.0f) const;
  GM_INLINEWII bool ParamFloatOrInt(int a_param, gmfloat& a_value, gmfloat a_default = 0.0f) const;
  GM_INLINEWII const char * ParamString(int a_param, const char * a_default = "") const;
  GM_INLINEWII bool ParamString(int a_param, const char *& a_value, const char * a_default = "") const;
  GM_INLINEWII gmStringObject * ParamStringObject(int a_param) const;
  GM_INLINEWII bool ParamStringObject(int a_param, gmStringObject *& a_value) const;
  GM_INLINEWII gmTableObject * ParamTable(int a_param) const;
  GM_INLINEWII bool ParamTable(int a_param, gmTableObject *& a_value ) const;
  GM_INLINEWII gmFunctionObject * ParamFunction(int a_param) const;
  GM_INLINEWII bool ParamFunction(int a_param, gmFunctionObject *& a_value) const;
  GM_INLINEWII void * ParamUser(int a_param, int * a_userType = NULL) const;
  GM_INLINEWII bool ParamUser(int a_param, void *& a_value, int * a_userType = NULL) const;
  GM_INLINEWII void * ParamUserCheckType(int a_param, int a_userType) const;
  GM_INLINEWII void * ParamUser_NoCheckTypeOrParam(int a_param) const; //For macro
  GM_INLINEWII gmUserObject * ParamUserObject(int a_param) const;
  GM_INLINEWII bool ParamUserObject(int a_param, gmUserObject *& a_value) const;
  GM_INLINEWII gmVariable& Param(int a_param);
  GM_INLINEWII const gmVariable& Param(int a_param) const;
  GM_INLINEWII gmVariable Param(int a_param, const gmVariable& a_default);  
  GM_INLINEWII gmType ParamType(int a_param) const;
  GM_INLINEWII gmptr ParamRef(int a_param) const;

  //
  // This methods. (get this as a given type)
  //

  GM_INLINEWII gmptr ThisInt(gmptr a_default = 0);
  GM_INLINEWII gmfloat ThisFloat(gmfloat a_default = 0.0f);
  GM_INLINEWII const char * ThisString(const char * a_default = "");
  GM_INLINEWII gmTableObject * ThisTable();
  GM_INLINEWII gmFunctionObject * ThisFunction();
  GM_INLINEWII void * ThisUser(int * a_userType = NULL);
  GM_INLINEWII void * ThisUserCheckType(int a_userType);
  GM_INLINEWII void * ThisUser_NoChecks(); //For use with type functions where type is already certain
  GM_INLINEWII gmUserObject * ThisUserObject();

  /// \brief Touch() will make sure that you can push a_extra variables on the stack
  /// \return true on success
  bool Touch(int a_extra);

  GM_INLINEWII int GetId() const { return m_id; }
  GM_INLINEWII const gmuint8 * GetInstruction() const { return m_instruction; }
  GM_INLINEWII State GetState() const { return m_state; }
  GM_INLINEWII gmuint32 GetTimeStamp() const { return m_timeStamp; }
  GM_INLINEWII gmuint32 GetThreadTime() const { return m_machine->GetTime() - m_startTime; }
  GM_INLINEWII void Sys_SetTimeStamp(gmuint32 a_timeStamp) { m_timeStamp = a_timeStamp; }
  GM_INLINEWII void Sys_SetStartTime(gmuint32 a_startTime) { m_startTime = a_startTime; }

  /// \brief GetSystemMemUsed will return the number of bytes allocated by the system.
  GM_INLINEWII unsigned int GetSystemMemUsed() const { return (m_size * sizeof(gmVariable)) + sizeof(this); }

  void LogCallStack();

  /// \brief Sys_SetBlocks() will set the blocking list for the thread.
  GM_INLINEWII void Sys_SetBlocks(gmBlock * a_block) { m_blocks = a_block; }

  /// \brief Sys_GetBlocks() will return the list of blocks on a thread
  GM_INLINEWII gmBlock * Sys_GetBlocks() { return m_blocks; }

  /// \brief Sys_SetSignals() will set the signal list for this thread
  GM_INLINEWII void Sys_SetSignals(gmSignal * a_signals) { m_signals = a_signals; }

  /// \brief Sys_GetSignals() will return the list of signals on a thread
  GM_INLINEWII gmSignal * Sys_GetSignals() { return m_signals; }

  // public data
#if GMDEBUG_SUPPORT
  mutable int m_debugFlags; //!< non-zero when thread is being debugged
  mutable int m_debugUser;
#endif // GMDEBUG_SUPPORT
  mutable int m_user;

private:

  /// \brief Sys_PopStackFrame() will pop a frame off the stack.
  /// \param a_ip is the current instruction pointer (pointing to instruction after call.) will be adjusted for new function.
  /// \param a_cp is the current code pointer.  will be adjusted for the new function.
  /// \return RUNNING, KILLED or SYS_EXCEPTION
  State Sys_PopStackFrame(const gmuint8 * &a_ip, const gmuint8 * &a_cp);

  void LogLineFile();

  // stack members
  gmMachine * m_machine;
  gmVariable * m_stack;
  int m_size;
  int m_top;
  int m_base;
  gmStackFrame * m_frame;

  // thread members
  State m_state;
  gmuint32 m_timeStamp; // wake up at this time stamp.
  gmuint32 m_startTime; // time this thread was started.
  const gmuint8 * m_instruction;
  int m_id;
  gmSignal * m_signals; // list of potentially active signals on this thread.
  gmBlock * m_blocks; // list of active blocks when thread is in BLOCKED state.
  short m_numParameters;
};


//
//
// INLINE IMPLEMENTATION
//
//


GM_INLINEWII const gmFunctionObject * gmThread::GetFunctionObject() const
{
  const gmVariable * fnVar = GetFunction();
  GM_ASSERT(fnVar->m_type == GM_FUNCTION);
  return (gmFunctionObject *) m_machine->GetObject(fnVar->m_value.m_ref);
}

//
// Push methods
//

GM_INLINEWII void gmThread::PushNull()
{
  m_stack[m_top].m_type = GM_NULL;
  m_stack[m_top++].m_value.m_int = 0;
}


GM_INLINEWII void gmThread::PushInt(gmptr a_value)
{
  m_stack[m_top].m_type = GM_INT;
  m_stack[m_top++].m_value.m_int = a_value;
}


GM_INLINEWII void gmThread::PushFloat(gmfloat a_value)
{
  m_stack[m_top].m_type = GM_FLOAT;
  m_stack[m_top++].m_value.m_float = a_value;
}


GM_INLINEWII void gmThread::PushString(gmStringObject * a_string)
{
  m_stack[m_top].m_type = GM_STRING;
  m_stack[m_top++].m_value.m_ref = (gmptr) a_string;
}


GM_INLINEWII void gmThread::PushTable(gmTableObject * a_table)
{
  m_stack[m_top].m_type = GM_TABLE;
  m_stack[m_top++].m_value.m_ref = (gmptr) a_table;
}


GM_INLINEWII void gmThread::PushFunction(gmFunctionObject * a_function)
{
  m_stack[m_top].m_type = GM_FUNCTION;
  m_stack[m_top++].m_value.m_ref = (gmptr) a_function;
}


GM_INLINEWII void gmThread::PushUser(gmUserObject * a_user)
{
  m_stack[m_top].m_type = (gmType)a_user->GetType();
  m_stack[m_top++].m_value.m_ref = a_user->GetRef();
}


gmStringObject * gmThread::PushNewString(const char * a_value, int a_len)
{
  m_stack[m_top].m_type = GM_STRING;
  return (gmStringObject *) (m_stack[m_top++].m_value.m_ref = (gmptr) m_machine->AllocStringObject(a_value, a_len));
}


gmTableObject * gmThread::PushNewTable()
{
  m_stack[m_top].m_type = GM_TABLE;
  return (gmTableObject *) (m_stack[m_top++].m_value.m_ref = (gmptr) m_machine->AllocTableObject());
}


gmUserObject * gmThread::PushNewUser(void * a_user, int a_userType)
{
  m_stack[m_top].m_type = (gmType) a_userType;
  return (gmUserObject *) (m_stack[m_top++].m_value.m_ref = (gmptr) m_machine->AllocUserObject(a_user, a_userType));
}

//
// Parameter methods. (do not cause an error if the desired parameter is incorrect type)
//

GM_INLINEWII int gmThread::ParamInt(int a_param, gmptr a_default) const
{
  if(a_param >= m_numParameters) return a_default;
  gmVariable * var = m_stack + m_base + a_param;
  if(var->m_type == GM_INT) return var->m_value.m_int;
  return a_default;
}

GM_INLINEWII bool gmThread::ParamInt(int a_param, int& a_value, gmptr a_default) const
{
  // Out of range
  if( a_param >= m_numParameters )
  {
    a_value = a_default;
    return true;
  }
  // Valid
  gmVariable * var = m_stack + m_base + a_param;
  if( var->m_type == GM_INT )
  {
    a_value = var->m_value.m_int;
    return true;
  }
  // Invalid
  a_value = a_default;
  return false;
}


GM_INLINEWII gmfloat gmThread::ParamFloat(int a_param, gmfloat a_default) const
{
  if(a_param >= m_numParameters) return a_default;
  gmVariable * var = m_stack + m_base + a_param;
  if(var->m_type == GM_FLOAT) return var->m_value.m_float;
  return a_default;
}

GM_INLINEWII bool gmThread::ParamFloat(int a_param, gmfloat& a_value, gmfloat a_default) const
{
  // Out of range
  if( a_param >= m_numParameters )
  {
    a_value = a_default;
    return true;
  }
  // Valid
  gmVariable * var = m_stack + m_base + a_param;
  if( var->m_type == GM_FLOAT )
  {
    a_value = var->m_value.m_float;
    return true;
  }
  // Invalid
  a_value = a_default;
  return false;
}

GM_INLINEWII gmfloat gmThread::ParamFloatOrInt(int a_param, gmfloat a_default) const
{
  if(a_param >= m_numParameters) return a_default;
  gmVariable * var = m_stack + m_base + a_param;
  if(var->m_type == GM_FLOAT)
    { return var->m_value.m_float; }
  else if(var->m_type == GM_INT)
    { return (gmfloat)var->m_value.m_int; }
  return a_default;
}

GM_INLINEWII bool gmThread::ParamFloatOrInt(int a_param, gmfloat& a_value, gmfloat a_default) const
{
  // Out of range
  if( a_param >= m_numParameters )
  {
    a_value = a_default;
    return true;
  }
  // Valid
  gmVariable * var = m_stack + m_base + a_param;
  if( var->m_type == GM_FLOAT )
  { 
    a_value = var->m_value.m_float; 
    return true;
  }
  else if(var->m_type == GM_INT)
  {
    a_value = (gmfloat)var->m_value.m_int; 
    return true;
  }
  // Invalid
  a_value = a_default;
  return false;
}

const char * gmThread::ParamString(int a_param, const char * a_default) const
{
  if(a_param >= m_numParameters) return a_default;
  gmVariable * var = m_stack + m_base + a_param;
  if(var->m_type == GM_STRING)
  {
    return (const char *) *((gmStringObject *) m_machine->GetObject(var->m_value.m_ref));
  }
  return a_default;
}

bool gmThread::ParamString(int a_param, const char *& a_value, const char * a_default) const
{
  // Out of range
  if( a_param >= m_numParameters)
  {
    a_value = a_default;
    return true;
  }
  // Valid
  gmVariable * var = m_stack + m_base + a_param;
  if( var->m_type == GM_STRING )
  {
    a_value = (const char *) *((gmStringObject *) m_machine->GetObject(var->m_value.m_ref));
    return true;
  }
  // Invalid
  a_value = a_default;
  return false;
}


gmStringObject * gmThread::ParamStringObject(int a_param) const
{
  if(a_param >= m_numParameters) return NULL;
  gmVariable * var = m_stack + m_base + a_param;
  if(var->m_type == GM_STRING)
  {
    return (gmStringObject *) m_machine->GetObject(var->m_value.m_ref);
  }
  return NULL;
}

bool gmThread::ParamStringObject(int a_param, gmStringObject *& a_value) const
{
  // Out of range
  if( a_param >= m_numParameters )
  {
    a_value = NULL;
    return true;
  }
  // Valid
  gmVariable * var = m_stack + m_base + a_param;
  if(var->m_type == GM_STRING)
  {
    a_value = (gmStringObject *) m_machine->GetObject(var->m_value.m_ref);
    return true;
  }
  // Invalid
  a_value = NULL;
  return false;
}

gmTableObject * gmThread::ParamTable(int a_param) const
{
  if(a_param >= m_numParameters) return NULL;
  gmVariable * var = m_stack + m_base + a_param;
  if(var->m_type == GM_TABLE)
  {
    return (gmTableObject *) m_machine->GetObject(var->m_value.m_ref);
  }
  return NULL;
}

bool gmThread::ParamTable(int a_param, gmTableObject *& a_value ) const
{
  // Out of range
  if( a_param >= m_numParameters )
  {
    a_value = NULL;
    return true;
  }
  // Valid
  gmVariable * var = m_stack + m_base + a_param;
  if( var->m_type == GM_TABLE )
  {
    a_value = (gmTableObject *) m_machine->GetObject(var->m_value.m_ref);
    return true;
  }
  // Invalid
  a_value = NULL;
  return false;
}


gmFunctionObject * gmThread::ParamFunction(int a_param) const
{
  if(a_param >= m_numParameters) return NULL;
  gmVariable * var = m_stack + m_base + a_param;
  if(var->m_type == GM_FUNCTION)
  {
    return (gmFunctionObject *) m_machine->GetObject(var->m_value.m_ref);
  }
  return NULL;
}


bool gmThread::ParamFunction(int a_param, gmFunctionObject *& a_value) const
{
  // Out of range
  if( a_param >= m_numParameters )
  {
    a_value = NULL;
    return true;
  }
  // Valid
  gmVariable * var = m_stack + m_base + a_param;
  if( var->m_type == GM_FUNCTION )
  {
    a_value = (gmFunctionObject *) m_machine->GetObject(var->m_value.m_ref);
    return true;
  }
  // Invalid
  a_value = NULL;
  return false;
}

void * gmThread::ParamUser(int a_param, int * a_userType) const
{
  if(a_param >= m_numParameters) return NULL;
  gmVariable * var = m_stack + m_base + a_param;
  if(var->m_type >= GM_USER)
  {
    gmUserObject * user = (gmUserObject *) m_machine->GetObject(var->m_value.m_ref);
    GM_ASSERT(var->m_type == user->m_userType);
    if(a_userType) 
    {
      *a_userType = user->m_userType;
    }
    return user->m_user;
  }
  return NULL;
}

bool gmThread::ParamUser(int a_param, void *& a_value, int * a_userType) const
{
  // Out of range
  if( a_param >= m_numParameters )
  {
    a_value = NULL;
    return true;
  }
  // Valid
  gmVariable * var = m_stack + m_base + a_param;
  if( var->m_type >= GM_USER )
  {
    gmUserObject * user = (gmUserObject *) m_machine->GetObject(var->m_value.m_ref);
    GM_ASSERT( var->m_type == user->m_userType );
    if( a_userType ) 
    {
      *a_userType = user->m_userType;
    }
    a_value = user->m_user;
    return true;
  }
  // Invalid
  a_value = NULL;
  return false;
}

void * gmThread::ParamUserCheckType(int a_param, int a_userType) const
{
  if(a_param >= m_numParameters) return NULL;
  gmVariable * var = m_stack + m_base + a_param;
  if(a_userType == var->m_type) 
  {
    GM_ASSERT(var->m_type >= GM_USER);
    gmUserObject * user = (gmUserObject *) m_machine->GetObject(var->m_value.m_ref);
    GM_ASSERT(var->m_type == user->m_userType);
    return user->m_user;
  }
  return NULL;
}


void * gmThread::ParamUser_NoCheckTypeOrParam(int a_param) const
{
  GM_ASSERT(a_param < m_numParameters);
  gmVariable * var = m_stack + m_base + a_param;
  GM_ASSERT(var->m_type >= GM_USER);
  gmUserObject * user = (gmUserObject *) m_machine->GetObject(var->m_value.m_ref);
  return user->m_user;
}


gmUserObject * gmThread::ParamUserObject(int a_param) const
{
  if(a_param >= m_numParameters) return NULL;
  gmVariable * var = m_stack + m_base + a_param;
  if(var->m_type >= GM_USER)
  {
    return (gmUserObject *) m_machine->GetObject(var->m_value.m_ref);
  }
  return NULL;
}


bool gmThread::ParamUserObject(int a_param, gmUserObject *& a_value) const
{
  // Out of range
  if( a_param >= m_numParameters )
  {
    a_value = NULL;
    return true;
  }
  // Valid
  gmVariable * var = m_stack + m_base + a_param;
  if( var->m_type >= GM_USER )
  {
    a_value = (gmUserObject *) m_machine->GetObject(var->m_value.m_ref);
    return true;
  }
  // Invalid
  a_value = NULL;
  return false;
}

GM_INLINEWII gmVariable& gmThread::Param(int a_param)
{
  return *(m_stack + m_base + a_param);
}


GM_INLINEWII const gmVariable& gmThread::Param(int a_param) const
{
  return *(m_stack + m_base + a_param);
}

gmVariable gmThread::Param(int a_param, const gmVariable& a_default)
{
  if( a_param >= m_numParameters )
  {
    return a_default;
  }
  return *(m_stack + m_base + a_param);
}

GM_INLINEWII gmType gmThread::ParamType(int a_param) const
{
  return (m_stack + m_base + a_param)->m_type;
}


GM_INLINEWII gmptr gmThread::ParamRef(int a_param) const
{
  return (m_stack + m_base + a_param)->m_value.m_ref;
}


//
// This methods.
//

GM_INLINEWII gmptr gmThread::ThisInt(gmptr a_default)
{
  const gmVariable * var = GetThis();
  if(var->m_type == GM_INT) return var->m_value.m_int;
  return a_default;
}


GM_INLINEWII gmfloat gmThread::ThisFloat(gmfloat a_default)
{
  const gmVariable * var = GetThis();
  if(var->m_type == GM_FLOAT) return var->m_value.m_float;
  return a_default;
}


GM_INLINEWII const char * gmThread::ThisString(const char * a_default)
{
  const gmVariable * var = GetThis();
  if(var->m_type == GM_STRING)
  {
    return (const char *) *((gmStringObject *) m_machine->GetObject(var->m_value.m_ref));
  }
  return a_default;
}


GM_INLINEWII gmTableObject * gmThread::ThisTable()
{
  const gmVariable * var = GetThis();
  if(var->m_type == GM_TABLE)
  {
    return (gmTableObject *) m_machine->GetObject(var->m_value.m_ref);
  }
  return NULL;
}


GM_INLINEWII gmFunctionObject * gmThread::ThisFunction()
{
  const gmVariable * var = GetThis();
  if(var->m_type == GM_FUNCTION)
  {
    return (gmFunctionObject *) m_machine->GetObject(var->m_value.m_ref);
  }
  return NULL;
}


GM_INLINEWII void * gmThread::ThisUser(int * a_userType)
{
  const gmVariable * var = GetThis();
  if(var->m_type >= GM_USER)
  {
    gmUserObject * user = (gmUserObject *) m_machine->GetObject(var->m_value.m_ref);
    if(a_userType) *a_userType = user->m_userType;
    return user->m_user;
  }
  return NULL;
}


GM_INLINEWII void * gmThread::ThisUserCheckType(int a_userType)
{
  const gmVariable * var = GetThis();
  if(var->m_type >= GM_USER)
  {
    gmUserObject * user = (gmUserObject *) m_machine->GetObject(var->m_value.m_ref);
    if(a_userType != user->m_userType) 
    {
      return NULL;
    }
    return user->m_user;
  }
  return NULL;
}


GM_INLINEWII void * gmThread::ThisUser_NoChecks()
{
  return ((gmUserObject*)m_machine->GetObject(GetThis()->m_value.m_ref))->m_user;
}


GM_INLINEWII gmUserObject * gmThread::ThisUserObject()
{
  const gmVariable * var = GetThis();
  if(var->m_type >= GM_USER)
  {
    return (gmUserObject *) m_machine->GetObject(var->m_value.m_ref);
  }
  return NULL;
}

//
//
// Helper macros
//
//

#define GM_THREAD_ARG a_thread

#ifdef GM_DEBUG_BUILD
  #define GM_OBJECT(A) GM_THREAD_ARG->GetMachine()->GetObject((A))
  #define GM_MOBJECT(M, A) (M)->GetObject((A))
#else //GM_DEBUG_BUILD
  #if GMMACHINE_SUPERPARANOIDGC
    #define GM_OBJECT(A) GM_THREAD_ARG->GetMachine()->GetObject((A))
    #define GM_MOBJECT(M, A) (M)->GetObject((A))
  #else //GMMACHINE_SUPERPARANOIDGC
    #define GM_OBJECT(A) (gmObject *) (A)
    #define GM_MOBJECT(M, A) (gmObject *) (A)
  #endif //GMMACHINE_SUPERPARANOIDGC
#endif //GM_DEBUG_BUILD

#define GM_NUM_PARAMS GM_THREAD_ARG->GetNumParams()
#if 1 // These macros only exception if param is present but type does not match
  #define GM_INT_PARAM(VAR, PARAM, DEFAULT) int VAR; if( !GM_THREAD_ARG->ParamInt((PARAM), (VAR), (DEFAULT)) ) { return GM_EXCEPTION; }
  #define GM_FLOAT_PARAM(VAR, PARAM, DEFAULT) float VAR; if( !GM_THREAD_ARG->ParamFloat((PARAM), (VAR), (DEFAULT)) )  { return GM_EXCEPTION; }
  #define GM_STRING_PARAM(VAR, PARAM, DEFAULT) const char * VAR; if( !GM_THREAD_ARG->ParamString((PARAM), (VAR), (DEFAULT)) )  { return GM_EXCEPTION; }
  #define GM_FUNCTION_PARAM(VAR, PARAM) gmFunctionObject * VAR; if( !GM_THREAD_ARG->ParamFunction((PARAM), (VAR)) )  { return GM_EXCEPTION; }
  #define GM_TABLE_PARAM(VAR, PARAM) gmTableObject * VAR; if( !GM_THREAD_ARG->ParamTable((PARAM), (VAR))  )  { return GM_EXCEPTION; }
  #define GM_USER_PARAM(OBJECT, VAR, PARAM) OBJECT VAR; if( !GM_THREAD_ARG->ParamUser((PARAM), (void*&)(VAR)) )  { return GM_EXCEPTION; }
  #define GM_FLOAT_OR_INT_PARAM(VAR, PARAM, DEFAULT) float VAR; if( !GM_THREAD_ARG->ParamFloatOrInt((PARAM), (VAR), (DEFAULT)) ) { return GM_EXCEPTION; }
#else // Old versions
  #define GM_INT_PARAM(VAR, PARAM, DEFAULT) int VAR = GM_THREAD_ARG->ParamInt((PARAM), (DEFAULT))
  #define GM_FLOAT_PARAM(VAR, PARAM, DEFAULT) float VAR = GM_THREAD_ARG->ParamFloat((PARAM), (DEFAULT))
  #define GM_STRING_PARAM(VAR, PARAM, DEFAULT) const char * VAR = GM_THREAD_ARG->ParamString((PARAM), (DEFAULT))
  #define GM_FUNCTION_PARAM(VAR, PARAM) gmFunctionObject * VAR = GM_THREAD_ARG->ParamFunction((PARAM))
  #define GM_TABLE_PARAM(VAR, PARAM) gmTableObject * VAR = GM_THREAD_ARG->ParamTable((PARAM))
  #define GM_USER_PARAM(OBJECT, VAR, PARAM) OBJECT VAR = (OBJECT) GM_THREAD_ARG->ParamUser((PARAM));
  #define GM_FLOAT_OR_INT_PARAM(VAR, PARAM, DEFAULT) float VAR = GM_THREAD_ARG->ParamFloatOrInt((PARAM), (DEFAULT))
#endif

//
// EXCEPTION VERSIONS
//

#define GM_EXCEPTION_MSG GM_THREAD_ARG->GetMachine()->GetLog().LogEntry

#define GM_CHECK_NUM_PARAMS(A) \
  if(GM_THREAD_ARG->GetNumParams() < (A)) { GM_EXCEPTION_MSG("expecting %d param(s)", (A)); return GM_EXCEPTION; }

#define GM_CHECK_INT_PARAM(VAR, PARAM) \
  if(GM_THREAD_ARG->ParamType((PARAM)) != GM_INT) { GM_EXCEPTION_MSG("expecting param %d as int", (PARAM)); return GM_EXCEPTION; } \
  int VAR = GM_THREAD_ARG->Param((PARAM)).m_value.m_int;

#define GM_CHECK_FLOAT_PARAM(VAR, PARAM) \
  if(GM_THREAD_ARG->ParamType((PARAM)) != GM_FLOAT) \
  { GM_EXCEPTION_MSG("expecting param %d as float", (PARAM)); return GM_EXCEPTION; } \
  float VAR = GM_THREAD_ARG->Param((PARAM)).m_value.m_float;

#define GM_CHECK_STRING_PARAM(VAR, PARAM) \
  if(GM_THREAD_ARG->ParamType((PARAM)) != GM_STRING) { GM_EXCEPTION_MSG("expecting param %d as string", (PARAM)); return GM_EXCEPTION; } \
  const char * VAR = (const char *) *((gmStringObject *) GM_OBJECT(GM_THREAD_ARG->ParamRef((PARAM))));

#define GM_CHECK_FUNCTION_PARAM(VAR, PARAM) \
  if(GM_THREAD_ARG->ParamType((PARAM)) != GM_FUNCTION) { GM_EXCEPTION_MSG("expecting param %d as function", (PARAM)); return GM_EXCEPTION; } \
  gmFunctionObject * VAR = (gmFunctionObject *) GM_OBJECT(GM_THREAD_ARG->ParamRef((PARAM)));

#define GM_CHECK_TABLE_PARAM(VAR, PARAM) \
  if(GM_THREAD_ARG->ParamType((PARAM)) != GM_TABLE) { GM_EXCEPTION_MSG("expecting param %d as table", (PARAM)); return GM_EXCEPTION; } \
  gmTableObject * VAR = (gmTableObject *) GM_OBJECT(GM_THREAD_ARG->ParamRef((PARAM)));

#define GM_CHECK_USER_PARAM(OBJECT, TYPE, VAR, PARAM) \
  if(GM_THREAD_ARG->ParamType((PARAM)) != (TYPE)) { GM_EXCEPTION_MSG("expecting param %d as user type %d", (PARAM), (TYPE)); return GM_EXCEPTION; } \
  OBJECT VAR = (OBJECT) GM_THREAD_ARG->ParamUser_NoCheckTypeOrParam((PARAM));

#define GM_CHECK_THIS_NULL \
    if(GM_THREAD_ARG->GetThis()->m_type != GM_NULL) { GM_EXCEPTION_MSG("expecting this as null"); return GM_EXCEPTION; }

#define GM_CHECK_THIS_INT \
    if(GM_THREAD_ARG->GetThis()->m_type != GM_INT) { GM_EXCEPTION_MSG("expecting this as int"); return GM_EXCEPTION; }

#define GM_CHECK_THIS_FLOAT \
    if(GM_THREAD_ARG->GetThis()->m_type != GM_FLOAT) { GM_EXCEPTION_MSG("expecting this as null"); return GM_EXCEPTION; }

#define GM_CHECK_THIS_STRING \
    if(GM_THREAD_ARG->GetThis()->m_type != GM_STRING) { GM_EXCEPTION_MSG("expecting this as string"); return GM_EXCEPTION; }

#define GM_CHECK_THIS_TABLE \
    if(GM_THREAD_ARG->GetThis()->m_type != GM_TABLE) { GM_EXCEPTION_MSG("expecting this as table"); return GM_EXCEPTION; }

#define GM_CHECK_THIS_FUNCTION \
    if(GM_THREAD_ARG->GetThis()->m_type != GM_FUNCTION) { GM_EXCEPTION_MSG("expecting this as function"); return GM_EXCEPTION; }

#define GM_CHECK_THIS_USER(TYPE) \
    if(GM_THREAD_ARG->GetThis()->m_type != TYPE) { GM_EXCEPTION_MSG("expecting this as user type %d", TYPE); return GM_EXCEPTION; }
    
// float or int param as float variable
#define GM_CHECK_FLOAT_OR_INT_PARAM(VAR, PARAM) \
  float VAR; \
  if( GM_THREAD_ARG->ParamType((PARAM)) == GM_FLOAT ) \
    { VAR = GM_THREAD_ARG->Param((PARAM)).m_value.m_float; } \
  else if( GM_THREAD_ARG->ParamType((PARAM)) == GM_INT ) \
    { VAR = (gmfloat)GM_THREAD_ARG->Param((PARAM)).m_value.m_int; } \
  else \
    { GM_EXCEPTION_MSG("expecting param %d as float or int", (PARAM)); return GM_EXCEPTION; }

#endif // _GMTHREAD_H_
