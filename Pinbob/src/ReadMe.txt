2011/07/23 liwenhaosuper
1. class IConfigFileReader:
   This interface must be implemented by all classes that read from the global config file

2. class IConfigFileWriter
   This interface must be implemented by all classes that write data the global config file

3. class ConfigFileManager
   The CConfigFileManager manages reading and writing of the global configuration file.It contains a static instance that can be retrieved.
The idea behind this is to implement it for the statemachine configuration and can be retrieved between different IState
without confliction. For instance, if we add the "Options", we would like to save the options setting to the setting file and then retrieved
the setting by the next IState.

4. class MenuHandler
  This ia an easy IState instance with stupid functions and it demonstrates how to code with the StateMachine framework.

5. class IState
   This is the interface for the game states and every scene of the game must implement its virtual functions for RTTI.
 
6. class StateMachine
   This is the framework of the project and main loop function are included in it. All game states must first register in the StateMachine 
   and initialize them in it so the StateMachine can call different state according to the game logic.

7. test.cpp shows how to run the machine.