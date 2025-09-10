#include "error_handler.h"
#include "unity.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_ERRH_t_Init(void)
{
  WES_ErrorCode     e_retVal;
  WES_ErrorHandler* t_testObj = ERRH_t_Init();
  e_retVal                    = t_testObj->getError();
  TEST_ASSERT_EQUAL(e_retVal, ERR_NONE);
}

void test_ERRH_t_LevelClearError(void)
{
  WES_ErrorCode     e_retVal;
  WES_ErrorHandler* t_testObj = ERRH_t_Init();
  t_testObj->setError(ERR_LEVEL);
  e_retVal = t_testObj->getError();
  TEST_ASSERT_EQUAL(e_retVal, ERR_NONE);
  t_testObj->setError(ERR_LEVEL_CLEAR);
  e_retVal = t_testObj->getError();
  TEST_ASSERT_EQUAL(e_retVal, ERR_NONE);
}

void test_ERRH_t_DisplayClearError(void)
{
  WES_ErrorCode     e_retVal;
  WES_ErrorHandler* t_testObj = ERRH_t_Init();
  t_testObj->setError(ERR_DISPLAY);
  e_retVal = t_testObj->getError();
  TEST_ASSERT_EQUAL(e_retVal, ERR_NONE);
  t_testObj->setError(ERR_DISPLAY_CLEAR);
  e_retVal = t_testObj->getError();
  TEST_ASSERT_EQUAL(e_retVal, ERR_NONE);
}

void test_ERRH_t_FatalError(void)
{
  WES_ErrorCode e_retVal;
  uint8_t       u_index;

  WES_ErrorHandler* t_testObj = ERRH_t_Init();

  for(u_index = 0; u_index < 10; u_index++)
  {
    t_testObj->setError(ERR_LEVEL);
  }
  t_testObj->setError(ERR_LEVEL_CLEAR);
  t_testObj->setError(ERR_LEVEL);
}