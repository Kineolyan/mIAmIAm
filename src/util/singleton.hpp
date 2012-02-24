
#ifndef __SINGLETON__
#define __SINGLETON__

/*
 -- Description :
 -- -------------
 -- This module implements a template structure of singleton that
 -- will be used to control easily global variables, particularly
 -- THE_STORE, THE_BDD_TABLE and THE_OPERATION_TABLE.
 -- According to the Singleton pattern, only one of these objects
 -- will be created, will be accessible in every part of the code.
 --
 -- WARNING: this implementation is not thread-safe, because of
 --		the initialization test in the Instance() method. As there
 -- 	are no ideal solutions create a thread-safe class with this
 -- 	architecture (m_instance being a pointer), a different
 --		version should be implemented in multi-thread.
 --
 -- Table of contents
 -- -----------------
 -- 1) Singleton definition
 -- 2) Management functions
 */

/*
 -- 1) Singleton definition
 -- -----------------------
 */

template <typename Object>
class Singleton
{
private:
	/**
	 * @brief: global variable to control
	 */
	static Object* m_instance;

public:
	/**
	 * @brief: allocate the instance
	 */
	static void create()
	{
		if (m_instance==NULL)
			m_instance = new Object();
	}

	/**
	 * @brief: deallocate the instance
	 */
	static void destroy()
	{
		if (m_instance!=NULL)
			delete m_instance;
	}

	/**
	 * @brief: get the global variable
	 *
	 * @return: the global variable
	 */
	static Object& Instance()
	{
		return *m_instance;
	}
};

template <typename Object>
Object* Singleton<Object>::m_instance = 0;

/*
 -- 2) Management functions
 -- -----------------------
 */

/**
 * @brief: allocate the instance
 */
template <typename Object>
inline void Create()
{	Singleton<Object>::create();	}

/**
 * @brief: deallocate the instance
 */
template <typename Object>
inline void Destroy()
{	return Singleton<Object>::destroy();	}

/**
 * @brief: get the global variable
 *
 * @return: the global variable
 */
template <typename Object>
inline Object& Get()
{	return Singleton<Object>::Instance();	}

#endif //__SINGLETON__



